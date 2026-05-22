/* Copyright Statement:
 *
 * (C) 2024  Airoha Technology Corp. All rights reserved.
 *
 * This software/firmware and related documentation ("Airoha Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or its licensors.
 * Without the prior written permission of Airoha and/or its licensors,
 * any reproduction, modification, use or disclosure of Airoha Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) Airoha Software
 * if you have agreed to and been bound by the applicable license agreement with
 * Airoha ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of Airoha Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
 * RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
 * TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.
 */


#include <stdint.h>
#include <zephyr/drivers/gpio.h>

#include <hal_gpio.h>
#include <hal_wdt.h>
#include "af_events_declaration.h"
#include "hal_eint.h"
#include "app_usb_port.h"

#if defined (CONFIG_AIR_SUPPORT_IRPT_LR_KEY)
#include "hal_eint_internal.h"
#include "hal_gpio_internal.h"
#endif

#include "gesture.h"
#include "app_pin_config_parser.h"
#include "app_button.h"
#include "app_state.h"
#include "hid_common.h"
#include "app_nvkey.h"
#include "app_labtest.h"
#include "app_rgb.h"
#include "app_battery.h"
#include "app_key_remap.h"

#define thisMODULE buttons
#define thisMOD    "buttons"

LOG_MODULE_REGISTER(thisMODULE);

//#define AF_DELAYABLE_EVT_TEST
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
static uint8_t app_button_set_debounce(uint8_t debounce);
static uint8_t app_button_get_debounce();
static uint32_t app_button_change_profile(uint8_t idx);
static uint32_t app_button_debounce_time_reload(uint8_t profile, bool restore);
static void app_btn_announce_rr_req(uint8_t type, uint16_t rr);
#ifdef M_KEY_DPI
static void app_btn_announce_dpi_req(uint8_t type);
#endif
static void app_button_set_each_key_debounce(uint8_t debounce_time);
static void app_button_set_each_key_extslp_debounce(uint8_t debounce_time);
static void app_btn_key_event_announcement(uint8_t key_id, airoha_key_event_t key_event);
static void app_btn_announce_pairing_request(uint8_t force_key_release_req);
static void app_btn_announce_evt_link_change();

static void app_button_enter_low_power_set_wakeup();
static void app_button_exit_low_power();

#if defined (CONFIG_AIR_SUPPORT_IRPT_LR_KEY)
static bool app_button__combo_key_check(T_AIR_COMBO_KEY_S * combo_cfg, uint32_t ir_key_status);
#endif

/**********************************f********************************************/
/* variables                                                                  */
/******************************************************************************/
#if defined(CONFIG_AIR_M21_SAMPLE)
static uint8_t key_ids[] =
{
    M_KEY_L,
    M_KEY_R,
    #if !defined (CONFIG_AIR_HID_DEBUG_PIN)
    M_KEY_M,
    M_KEY_NK,
    M_KEY_PK,
    #endif
    // M_KEY_DPI,
    M_KEY_PAIRING,
};
uint8_t mouse_LMR45_key_valid_num = sizeof(key_ids) - 2;  // remove M_KEY_DPI,  SCROLL_UP_PIN, and SCROLL_DOWN_PIN

#else
static uint8_t key_ids[] =
{
    M_KEY_L,
    M_KEY_R,
    #if !defined (CONFIG_AIR_HID_DEBUG_PIN)
    M_KEY_M,
    M_KEY_NK,
    M_KEY_PK,
    #endif
    #ifdef M_KEY_DPI
    M_KEY_DPI,
    #endif
    M_KEY_RR,
    M_KEY_PAIRING,
};

uint8_t mouse_LMR45_key_valid_num = sizeof(key_ids) - 3;
#endif
uint8_t mouse_key_num = sizeof(key_ids);


typedef enum{
    COMBO_KEY_PAIRING,
}T_COMBO_KEY_USAGE_E;

typedef enum{
    APP_BUTTON_STATE_NORMAL,
    APP_BUTTON_STATE_LOW_POWER,
}T_APP_BUTTON_STATE_E;

#if defined (CONFIG_AIR_HID_DEBUG_PIN)
T_AIR_COMBO_KEY_S  combo_key_list[] =  // re-Pairing
{
    {COMBO_KEYS(2, M_KEY_L, M_KEY_DPI )},
};

#else
T_AIR_COMBO_KEY_S combo_key_list[] = // re-Pairing
{
    {COMBO_KEYS(3, M_KEY_L, M_KEY_M, M_KEY_R )},

    // test pattern
    #if 0
    {COMBO_KEYS(2, M_KEY_DPI, M_KEY_RR )},
    #endif
};
#endif


#if defined (CONFIG_AIR_SUPPORT_IRPT_LR_KEY)
static void app_button_IR_pairing_key_check_timeout(struct k_timer *timer_id);
struct k_timer app_button_IR_pairing_key_check;
#endif

uint8_t profile_debounce_list[MAX_PROFILE_COUNT] = {DEFAULT_DEBOUNCE_TIME, DEFAULT_DEBOUNCE_TIME, DEFAULT_DEBOUNCE_TIME, DEFAULT_DEBOUNCE_TIME};

#if defined(CONFIG_AIR_SUPPORT_IRPT_LR_KEY)
uint8_t gpio_debounce_list[] =
{
    0,
    #if !defined (CONFIG_AIR_HID_DEBUG_PIN)
    0,
    DEFAULT_DEBOUNCE_TIME,
    DEFAULT_DEBOUNCE_TIME,
    DEFAULT_DEBOUNCE_TIME,
    #endif
    DEFAULT_DEBOUNCE_TIME,
    DEFAULT_DEBOUNCE_TIME,
};
#else
uint8_t gpio_debounce_list[] =
{
    DEFAULT_DEBOUNCE_TIME,
    #if !defined (CONFIG_AIR_HID_DEBUG_PIN)
    DEFAULT_DEBOUNCE_TIME,
    DEFAULT_DEBOUNCE_TIME,
    DEFAULT_DEBOUNCE_TIME,
    DEFAULT_DEBOUNCE_TIME,
    #endif
    DEFAULT_DEBOUNCE_TIME,
    DEFAULT_DEBOUNCE_TIME,
    DEFAULT_DEBOUNCE_TIME,
};
#endif

static uint8_t profile_idx = DEFAULT_PROFILE_IDX;
bool app_btn_low_battery_check = false;
static uint32_t last_key_status = 0;
static uint32_t last_app_state = APP_STATE_NONE;
uint8_t  app_button_state = APP_BUTTON_STATE_NORMAL;
/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/



/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/

static void app_button__button_irq_ctrl(bool enable)
{
    airo_key_status_t ret ;

    if (enable){
        #if defined (CONFIG_AIR_SUPPORT_IRPT_LR_KEY)
        // Never turn on EINT IRQ of IR-KEY
        ret =  gesture_key_reconfiguration( (uint8_t*)&key_ids[2], mouse_key_num - 2, GESTURE_CFG_OPT_ENABLE_KEY_IRQ);
        #else
        ret =  gesture_key_reconfiguration( (uint8_t*)key_ids, mouse_key_num, GESTURE_CFG_OPT_ENABLE_KEY_IRQ);
        #endif
    }
    else {
        ret =  gesture_key_reconfiguration( (uint8_t*)key_ids, mouse_key_num, GESTURE_CFG_OPT_DISABLE_KEY_IRQ);
    }
    APP_LOGI(thisMOD,"app_button__button_irq_ctrl enable = %d, ret  = 0x%x ", enable , ret );
}

static void app_button__click_check_reset(bool reset_all, bool multi_click_counts_reset)
{
    uint32_t all_key_status_0 = 0, all_key_status_1 = 0;

    if(reset_all)
    {
        gesture_key_all_click_reset((uint8_t*)key_ids, mouse_key_num, multi_click_counts_reset);
    }
    else
    {
        for (uint8_t key_idx = 0 ; key_idx < mouse_key_num ; key_idx++ )
        {
            #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
            uint8_t remap_id = app_key_remap_check(key_idx);
            #ifdef M_KEY_DPI
            if(((remap_id == M_KEY_PAIRING) || (remap_id == M_KEY_DPI)) && gesture_key_click_timer_running(key_idx))
            #else
            if(((remap_id == M_KEY_PAIRING) ) && gesture_key_click_timer_running(key_idx))
            #endif
            {
                /* If the key remap to pairing/DPI key timer is running, set the key status is pressed */
                last_key_status |= 0x01 << key_idx;
                APP_LOGI(thisMOD,"Pairing/DPI key timer is run key_idx = %d, last_key_status = %x", key_idx, last_key_status);
            }
            else
            #endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP*/
            {
                /*
                    Connected doesn't reset multi-click counts, short click will detected.
                    Disconnected reset all multi-click counts
                */
                gesture_key_click_reset(key_idx, multi_click_counts_reset);
            }
        }
    }

    last_key_status = airo_key_read_all_key_status(&all_key_status_0, &all_key_status_1);
}


static bool app_button__evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state* event = (struct evt_app_state*)evt_header;
    APP_LOGI(thisMOD,"app_button__evt_app_state event->app_state = 0x%x " , event->app_state );

    switch(event->app_state)
    {
        case APP_STATE_BT_CONNECTED_IDLE_1:
        case APP_STATE_2_4G_CONNECTED_IDLE_1:
        {
            APP_LOGI(thisMOD,"REG_GPIO_MODE [23_16]= 0x%08X, [15_08]= 0x%08X, [07_00]= 0x%08X", (unsigned int)(*(volatile uint32_t*)0x420b0038) , (unsigned int)(*(volatile uint32_t*)0x420b0034), (unsigned int)(*(volatile uint32_t*)0x420b0030));
            APP_LOGI(thisMOD,"REG_GPIO_MODE [47_40]= 0x%08X, [39_32]= 0x%08X, [31_24]= 0x%08X", (unsigned int)(*(volatile uint32_t*)0x420b0044), (unsigned int)(*(volatile uint32_t*)0x420b0040), (unsigned int)(*(volatile uint32_t*)0x420b003C));
        }
        break;

        case APP_STATE_BT_CONNECTED_IDLE_2:
        case APP_STATE_2_4G_CONNECTED_IDLE_2:
        {

        }
        break;

        case APP_STATE_USB_ACTIVE:
        case APP_STATE_BT_CONNECTED_ACTIVE:
        case APP_STATE_2_4G_CONNECTED_ACTIVE:
        {
            #if !defined(FAKE_REPORT_TRIGGER_BY_MIDDLE_KEY)
            app_button__button_irq_ctrl(false);
            #endif
            app_button__click_check_reset(false, false);
        }
        break;

        case APP_STATE_STANDBY:
        {
            #if defined (CONFIG_AIR_APP_STANDBY_WITH_ADAPTOR_RGB)
            if(app_usb_port__get_usb_plug_status() != APP_USB_PLUG_OUT){

            }
            else
            #endif
            {
                bool power_ok = app_battery__get_battery_power();
                if(power_ok)
                {
                    app_button_set_each_key_extslp_debounce(0); /* 62.5us debounce time */
                    app_button__button_irq_ctrl(true);

                    #if defined (CONFIG_AIR_APP_STANDBY_WAKEUP_BY_IRPT_KEY)
                    airo_key_status_t ret ;
                    ret =  gesture_key_reconfiguration( (uint8_t*)&key_ids[0], 2, GESTURE_CFG_OPT_ENABLE_KEY_IRQ);
                    APP_LOGI(thisMOD,"Enable LR key eint, ret  = 0x%x ", ret );
                    #endif
                }
                app_button_enter_low_power_set_wakeup();
                if(!power_ok){  //action after set wakeup
                    app_btn_low_battery_check = true;
                    gesture_key_reconfiguration((uint8_t*)key_ids, mouse_key_num, GESTURE_CFG_OPT_DISABLE_KEY_IRQ);
                }
            }
        }
        break;

        case APP_STATE_USB_SUSPEND:
        case APP_STATE_DISCONNECTED:
        {
            app_button__click_check_reset(true, true);
            app_button__button_irq_ctrl(true);
        }
        break;

        case APP_STATE_TEST:
        {
            uint8_t type = app_labtest_get_type();
            if(type == APP_LABTEST_TYPE_RELAY_MODE){
                app_button__button_irq_ctrl(false);
            }
            else if(type == APP_LABTEST_TYPE_LAB_TEST)
            {
                app_button__button_irq_ctrl(true);
            }
        }
        break;

        case APP_STATE_CONNECT_PREPARING:
        {
            app_button_set_each_key_debounce(profile_debounce_list[profile_idx]);
            app_button__button_irq_ctrl(true);

            #if defined (CONFIG_AIR_SUPPORT_IRPT_LR_KEY)
            // Never turn on EINT IRQ of IR-KEY, Disable L/R key IRQ
            gesture_key_reconfiguration( (uint8_t*)key_ids, 2, GESTURE_CFG_OPT_DISABLE_KEY_IRQ);
            #endif
        }
        break;

        default:
        break;
    }



    last_app_state = event->app_state;
    return AF_TRAVERSE_NEXT;
}

void app_button__announce_key_active_event()
{
    struct evt_active_status* event = create_evt_active_status();
    if (event){
        event->active = true;
        event->type = KEY_WAKEUP;
        AF_EVT_SUBMIT(event);
    }
}

void app_button_key_event_hdl(airoha_key_event_t event, uint8_t key_id)
{
    switch (event)
    {
        case AK_RELEASE:
        {

        }
        break;

        case AK_PRESS:
        {

        }
        break;

        case AK_COMBO_HOLD_LV1_0:
        {
            app_btn_announce_pairing_request(false);
        }
        break;

        case AK_COMBO_HOLD_LV1_1:
        {

        }
        break;

        case AK_COMBO_HOLD_LV1_2:
        {
        }
        break;

        case AK_COMBO_HOLD_LV1_3:
        {

        }
        break;

        case AK_DLONG:
        {
            APP_LOGI(thisMOD,"Key[%d] %d clicks and Long press", key_id, event - AK_CLICK_AND_LONG_PRESS_TYPE_MASK);

            #if defined(CONFIG_AIR_TEST_GESTURE)
            #ifdef M_KEY_DPI
            if(M_KEY_RR == key_id || M_KEY_DPI == key_id)
            #else
            if(M_KEY_RR == key_id)
            #endif
            {
                if(profile_debounce_list[profile_idx])
                {
                    profile_debounce_list[profile_idx] = 0;
                }
                else
                {
                    profile_debounce_list[profile_idx] = 10;
                }
                app_button_set_each_key_debounce(profile_debounce_list[profile_idx]);
                APP_LOGI(thisMOD,"Back door fun: set debounce = %d", profile_debounce_list[profile_idx]);
            }
            #endif

            #if defined (CONFIG_AIR_HID_DEBUG_PIN)
            #ifdef M_KEY_DPI
            else if (M_KEY_DPI == key_id){
                struct evt_pairing_request* evt = create_evt_pairing_request();
                if (evt){
                    APP_LOGI(thisMOD,"Back door fun: PAIRING_REQ_RECOVERABLE");
                    evt->type = PAIRING_REQ_RECOVERABLE;
                    evt->force_key_release_req = true;
                    AF_EVT_SUBMIT(evt);
                }
            }
            #endif
            #endif
        }
        break;

        case AK_TLONG:
        {
            APP_LOGI(thisMOD,"Key[%d] %d clicks and Long press", key_id, event - AK_CLICK_AND_LONG_PRESS_TYPE_MASK);
        }
        break;

        case AK_4LONG:
        {
            APP_LOGI(thisMOD,"Key[%d] %d clicks and Long press", key_id, event - AK_CLICK_AND_LONG_PRESS_TYPE_MASK);
        }
        break;

        case AK_5LONG:
        {
            APP_LOGI(thisMOD,"Key[%d] %d clicks and Long press", key_id, event - AK_CLICK_AND_LONG_PRESS_TYPE_MASK);
        }
        break;

        case AK_6LONG:
        case AK_7LONG:
        case AK_8LONG:
        {
            APP_LOGI(thisMOD,"Key[%d] %d clicks and Long press", key_id, event - AK_CLICK_AND_LONG_PRESS_TYPE_MASK);
        }
        break;

        case AK_9LONG:
        {
            APP_LOGI(thisMOD,"Key[%d] %d clicks and Long press", key_id, event - AK_CLICK_AND_LONG_PRESS_TYPE_MASK);

            #if defined(CONFIG_AIR_TEST_GESTURE)
            if(key_id == M_KEY_RR){
                struct evt_factory_reset* evt = create_evt_factory_reset();
                if (evt){
                    APP_LOGI(thisMOD,"Back door fun: FACTORY_RESET");
                    evt->status = true;
                    AF_EVT_SUBMIT(evt);
                }
            }
            #endif
        }
        break;

        case AK_SHORT_CLICK:
        {
            APP_LOGI(thisMOD,"Key[%d] short clicks", key_id);

            switch(key_id)
            {
                case M_KEY_RR: //Report rate change to next
                {
                    app_btn_announce_rr_req(RR_CHANGE_NEXT, 0);
                    break;
                }
                #ifdef M_KEY_DPI
                case M_KEY_DPI: //DPI change to next loop stage
                {
                    app_btn_announce_dpi_req(DPI_STAGE_LOOP);
                    break;
                }
                #endif
                case M_KEY_PAIRING: //change link or mode
                {
                    app_btn_announce_evt_link_change();
                    break;
                }

                default:{
                    break;
                }
            }
        }
        break;

        case AK_DOUBLE_CLICK:
        {
            APP_LOGI(thisMOD,"Key[%d] Double clicks", key_id);

            #if defined(CONFIG_AIR_TEST_GESTURE)
            if(key_id == M_KEY_RR){ //Report rate change to previous
                app_btn_announce_rr_req(RR_CHANGE_PREV, 0);
            }
            #ifdef M_KEY_DPI
            if(key_id == M_KEY_DPI){ //DPI change to previous
                app_btn_announce_dpi_req(DPI_STAGE_MINUS);
            }
            #endif
            #endif
        }
        break;

        case AK_TRIPLE_CLICK:
        {
            APP_LOGI(thisMOD,"Key[%d] Tripple clicks", key_id);

            switch (key_id )
            {
                case M_KEY_NK:
                {

                }
                break;

                case M_KEY_PK:
                {

                }
                break;
                #ifdef M_KEY_DPI
                case M_KEY_DPI:
                {
                    #if defined (CONFIG_AIR_HID_DEBUG_PIN)
                    APP_LOGI(thisMOD,"Back door fun: change to next RR");
                    app_btn_announce_rr_req(RR_CHANGE_NEXT, 0);
                    #endif
                }
                break;
                #endif
                case M_KEY_RR:
                {
                    #if defined(CONFIG_AIR_TEST_GESTURE)
                    app_btn_announce_rr_req(RR_CHANGE_SPECIFIC, REPORT_RATE_MAX);
                    #endif
                }
                break;
            }
        }
        break;

        case AK_4_CLICK:
        {
            APP_LOGI(thisMOD,"Key[%d] %d clicks", key_id, AK_4_CLICK - AK_CLICK_TYPE_MASK);
        }
        break;

        case AK_5_CLICK:
        case AK_6_CLICK:
        case AK_7_CLICK:
        case AK_8_CLICK:
        case AK_9_CLICK:
        {
            APP_LOGI(thisMOD,"Key[%d] %d clicks", key_id, event - AK_CLICK_TYPE_MASK);
        }
        break;

        case AK_LONG_PRESS_LV_1:
        {
            APP_LOGI(thisMOD,"Key[%d] Press and hold level 1 (2s)", key_id);
            switch(key_id)
            {
                case M_KEY_RR:
                {
                    #if defined(CONFIG_AIR_TEST_GESTURE)
                    struct evt_app_rgb_test* evt = create_evt_app_rgb_test();
                    if (evt){
                        evt->cmd = TEST_FLASH;
                        AF_EVT_SUBMIT(evt);
                    }
                    #endif
                    break;
                }
                default:{
                    break;
                }
            }
        }
        break;

        case AK_LONG_PRESS_LV_2:
        {
            APP_LOGI(thisMOD,"Key[%d] Press and hold level 2 (2+1s)", key_id);
            switch(key_id)
            {
                #ifdef M_KEY_DPI
                case M_KEY_DPI:
                {
                    app_btn_announce_evt_link_change();
                }
                break;
                #endif
                case M_KEY_PAIRING:
                {
                    if(app_state_current_state() & APP_STATE_CONNECTED)
                    {
                        app_btn_announce_pairing_request(true);
                    }
                    else
                    {
                        app_btn_announce_pairing_request(false);
                    }
                }
                break;
            }
        }
        break;
        case AK_LONG_PRESS_LV_3:
        {
            APP_LOGI(thisMOD,"Key[%d] Press and hold level 3 (2+1+2s)", key_id);
        }
        break;

        default:
            break;
    }
}

void app_button_key_event_cb(airoha_key_event_t event, uint8_t key_id)
{
    uint32_t app_state = app_state_current_state();
    uint8_t key_idx = airo_key_get_key_index(key_id);
    #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    uint8_t remap_key_id = app_key_remap_check(key_idx);
    #endif

    if((app_state == APP_STATE_STANDBY) || app_state_check(TYPE_CONNECTED_WO_ACTIVE)){
        app_button__announce_key_active_event();
    }

    if(event == AK_PRESS)
    {
        last_key_status |= (0x01 << key_idx);
    }
    else if(event == AK_RELEASE)
    {
        last_key_status &= ~(0x01 << key_idx);
    }

    app_btn_key_event_announcement(key_id, event);

    #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    APP_LOGI(thisMOD,"app_key_event key_%d remap to key_%d event = 0x%x, last_key_status = %x" , key_id, remap_key_id, event, last_key_status);
    app_button_key_event_hdl(event, remap_key_id);
    #else
    APP_LOGI(thisMOD,"app_key_event key_%d event = 0x%x, last_key_status = %x" , key_id, event, last_key_status);
    app_button_key_event_hdl(event, key_id);
    #endif
}

static bool app_button_evt_active_status(const struct af_evt_header *evt_header)
{
    struct evt_active_status* event = (struct evt_active_status*)evt_header;
    APP_LOGI(thisMOD,"app_button_evt_active_status, active = %d, type = %d", event->active, event->type);
    uint32_t app_state = app_state_current_state();

    if(event->active == false && (app_state == APP_STATE_2_4G_CONNECTED_ACTIVE || app_state == APP_STATE_BT_CONNECTED_ACTIVE))
    {
        uint8_t charge = app_battery__get_bat_charge_status();
        if (!charge){
            app_button__click_check_reset(false, false);
            app_button__button_irq_ctrl(true);
        }
    }
    else if(event->active && app_state == APP_STATE_STANDBY)
    {
        switch(event->type)
        {
            case MOTION_SENSOR_WAKEUP:
            case WHEEL_WAKEUP:
            case KEY_WAKEUP:
            #if defined (CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH) || defined (CONFIG_AIR_DUAL_MODE_SLIDE_SWITCH)
            case SLIDE_SWITCH_WAKEUP:
            #endif
            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
            case USB_PLUG_WAKEUP:
            #endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/
            {
                app_button_exit_low_power();
                if(app_btn_low_battery_check){
                    app_btn_low_battery_check = false;
                    gesture_key_reconfiguration((uint8_t*)key_ids, mouse_key_num, GESTURE_CFG_OPT_ENABLE_KEY_IRQ);
                }
                break;
            }
            default:{
                break;
            }
        }
    }

    return AF_TRAVERSE_NEXT;
}
/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static void app_button_set_each_key_debounce(uint8_t debounce_time)
{
    for (uint8_t idx = 0 ; idx < sizeof(gpio_debounce_list); idx ++ )
    {
        #if defined(CONFIG_AIR_SUPPORT_IRPT_LR_KEY)
        if((idx == 0) || (idx == 1))
        {
            airo_key_gpio_debounce_config(idx, 0); /* disable debounce */
        }
        else
        {
            #if !defined(CONFIG_AIR_HID_DEBUG_PIN)
            gpio_debounce_list[idx] = debounce_time;
            airo_key_gpio_debounce_config(idx, debounce_time);
            #endif
        }
        #else
        gpio_debounce_list[idx] = debounce_time;
        airo_key_gpio_debounce_config(idx, debounce_time);
        #endif
    }
}

/* Set 0, it will has 62.5us debounce */
static void app_button_set_each_key_extslp_debounce(uint8_t debounce_time)
{
    for (uint8_t idx = 0 ; idx < sizeof(gpio_debounce_list); idx ++ )
    {
        gpio_debounce_list[idx] = debounce_time;
        airo_key_gpio_extslp_debounce_config(idx, debounce_time);
    }
}

static uint8_t app_button_set_debounce(uint8_t debounce)
{
    #define RACE_ERRCODE_SUCCESS 0
    #define RACE_ERRCODE_PARAMETER_ERROR 3
    bool debounce_state = (debounce >> 7);
    uint8_t debounce_time = debounce & 0x7f;
    nvkey_status_t ret;

    if (debounce_time <= 30)
    {
        app_button_set_each_key_debounce(debounce_time);
        profile_debounce_list[profile_idx] = debounce_time;

        if(debounce_state){
            APP_LOGI(thisMOD,"app_button_set_debounce release = %d", debounce_time);
        }
        else{
            APP_LOGI(thisMOD,"app_button_set_debounce press = %d", debounce_time);
        }

        ret = nvkey_write_data(NVID_DEBOUNCE_TIME_LIST , (const uint8_t*)&profile_debounce_list , sizeof(profile_debounce_list));
        if(ret)
        {
            APP_LOGI(thisMOD,"nvkey_write_data NVID_DEBOUNCE_TIME_LIST err = %d", ret);
        }
    }
    else
    {
        return RACE_ERRCODE_PARAMETER_ERROR;
    }

    return RACE_ERRCODE_SUCCESS;
}

static uint8_t app_button_get_debounce()
{
    APP_LOGI(thisMOD,"app_button_get_debounce = %d", profile_debounce_list[profile_idx]);
    return profile_debounce_list[profile_idx];
}

static uint32_t app_button_change_profile(uint8_t idx)
{
    APP_LOGI(thisMOD,"app_button_change_profile idx = %d", idx);
    /* There is no need to read each profile's data from the NVKEY,
    * since they are in RAM and may be newer than the NVKEY.*/
    profile_idx = idx;
    app_button_set_each_key_debounce(profile_debounce_list[profile_idx]);
    return 0;
}

static uint32_t app_button_debounce_time_reload(uint8_t profile, bool restore)
{
    uint8_t idx;
    bool result = false;
    APP_LOGI(thisMOD,"app_button_debounce_time_reload");

    if(!restore)
    {
        result = app_nvkey_read_data((uint16_t) NVID_DEBOUNCE_TIME_LIST, (uint8_t*)&profile_debounce_list, sizeof(profile_debounce_list));
    }

    if (!result)
    {
        for(idx = 0; idx < MAX_PROFILE_COUNT; idx++)
        {
            profile_debounce_list[idx] = DEFAULT_DEBOUNCE_TIME;
        }

        nvkey_status_t ret = nvkey_write_data(NVID_DEBOUNCE_TIME_LIST , (const uint8_t*)&profile_debounce_list , sizeof(profile_debounce_list));
        if(ret)
        {
            APP_LOGI(thisMOD,"nvkey_write_data NVID_DEBOUNCE_TIME_LIST err = %d", ret);
        }
    }

    profile_idx = profile;

    for(idx = 0; idx < sizeof(gpio_debounce_list); idx++)
    {
        #if defined(CONFIG_AIR_SUPPORT_IRPT_LR_KEY)
        if(idx != 0)
        {
            #if !defined (CONFIG_AIR_HID_DEBUG_PIN)
            if(idx != 1)
            #endif
            {
                gpio_debounce_list[idx] = profile_debounce_list[profile_idx];
            }

        }

        #else
        gpio_debounce_list[idx] = profile_debounce_list[profile_idx];
        #endif
    }

    for(idx = 0; idx < MAX_PROFILE_COUNT; idx++){
        APP_LOGI(thisMOD,"debounce time idx = %d, value = %d", idx, profile_debounce_list[idx]);
    }

    if(restore)
    {
        app_button_set_each_key_debounce(profile_debounce_list[profile_idx]);
    }
    return 0;
}

static void app_btn_announce_pairing_request(uint8_t force_key_release_req)
{
    struct evt_pairing_request* event = create_evt_pairing_request();
    if (event){
        event->type = PAIRING_REQ_RECOVERABLE;
        event->force_key_release_req = force_key_release_req;
        AF_EVT_SUBMIT(event);
    }
}

static void app_btn_announce_evt_link_change()
{
    struct evt_link_change* evt = create_evt_link_change();
    if (evt){
        evt->type = CHANGE_NEXT_LINK;
        AF_EVT_SUBMIT(evt);
    }
}

static void app_btn_key_event_announcement(uint8_t key_id, airoha_key_event_t key_event)
{
    struct evt_key_event* event = create_evt_key_event();
    if (event){
        APP_LOGI(thisMOD,"app_btn_key_event_announcement");
        event->key_id = key_id;
        event->key_evt = key_event;
        AF_EVT_SUBMIT(event);
    }
}

static void app_btn_announce_rr_req(uint8_t type, uint16_t rr)
{
    struct evt_rr_change_req* event = create_evt_rr_change_req();
    if (event){
        event->change_type = type;
        event->RR = rr;
        event->restore_or_chg_profile = false;
        AF_EVT_SUBMIT(event);
    }
}
#ifdef M_KEY_DPI
static void app_btn_announce_dpi_req(uint8_t type)
{
    struct evt_dpi_change_req* event = create_evt_dpi_change_req();
    if (event){
        event->change_type = type;
        #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
        event->X_DPI = 0;
        event->Y_DPI = 0;
        #else
        event->DPI = 0;
        #endif
        AF_EVT_SUBMIT(event);
    }
}
#endif

static void app_btn_race_cmd_rsp_announcement(T_RACE_CMD_E cmd, uint8_t result)
{
    APP_LOGI(thisMOD,"app_btn_race_cmd_rsp_announcement , result = %d", result);
    struct evt_race_cmd_rsp* event = create_evt_race_cmd_rsp();
    if (event){
        event->cmd = cmd;
        switch (cmd) {
            case RACE_CMD_SET_DEBOUNCE:
            case RACE_CMD_GET_DEBOUNCE:
                event->DEBOUNCE.result = result;
                break;

            case RACE_CMD_SET_PROFILE:
            case RACE_CMD_SET_RESTORE:
                event->OTHERS.status = result;
                break;

            default:
                break;
        }
        AF_EVT_SUBMIT(event);
    }
}

static bool app_button_evt_race_cmd_req(const struct af_evt_header *evt_header)
{
    struct evt_race_cmd_req* event = (struct evt_race_cmd_req*)evt_header;
    APP_LOGI(thisMOD,"evt_race_cmd_req , cmd = %x", event->cmd);
    uint8_t res;

    switch(event->cmd)
    {
        case RACE_CMD_SET_DEBOUNCE:
        {
            res = app_button_set_debounce(event->DEBOUNCE.time);
            app_btn_race_cmd_rsp_announcement(RACE_CMD_SET_DEBOUNCE, res);
        }
        break;

        case RACE_CMD_GET_DEBOUNCE:
        {
            res = app_button_get_debounce();
            app_btn_race_cmd_rsp_announcement(RACE_CMD_GET_DEBOUNCE, res);
        }
        break;

        case RACE_CMD_SET_PROFILE:
        {
            res = app_button_change_profile(event->PROFILE.id);
            app_btn_race_cmd_rsp_announcement(RACE_CMD_SET_PROFILE, res);
        }
        break;

        case RACE_CMD_SET_RESTORE:
        {
            res = app_button_debounce_time_reload(0, true);
            app_btn_race_cmd_rsp_announcement(RACE_CMD_SET_RESTORE, res);
        }
        break;

        default:
        break;
    }
    return AF_TRAVERSE_NEXT;
}

#if defined (CONFIG_AIR_SUPPORT_IRPT_LR_KEY)
static bool app_button__combo_key_check(T_AIR_COMBO_KEY_S * combo_cfg, uint32_t ir_key_status)
{
    bool ret = false;

    if (combo_cfg ){
        gpio_data_in_mask_t gpio_data_in_mask_temp;
        hal_eint_get_debounce_out_value_by_mask(&gpio_data_in_mask_temp.register0, &gpio_data_in_mask_temp.register1);
        uint32_t all_key_status_0 = ~(gpio_data_in_mask_temp.register0);
        uint32_t all_key_status_1 = ~(gpio_data_in_mask_temp.register1);

        if (ir_key_status & M_5_KEY_BIT_L) {
            // L key is pressed
            if (M_KEY_L < COMBO_BIT_PART_1_MAX ){
                all_key_status_0 |= COMBO_LW(M_KEY_L);
            }
            else {
                all_key_status_1 |= COMBO_HW(M_KEY_L);
            }
        }
        else {
            if (M_KEY_L < COMBO_BIT_PART_1_MAX ){
                all_key_status_0 &= ~COMBO_LW(M_KEY_L);
            }
            else {
                all_key_status_1 &= ~COMBO_HW(M_KEY_L);
            }
        }

        if (ir_key_status & M_5_KEY_BIT_R) {
            // L key is pressed
            if (M_KEY_R < COMBO_BIT_PART_1_MAX ){
                all_key_status_0 |= COMBO_LW(M_KEY_R);
            }
            else {
                all_key_status_1 |= COMBO_HW(M_KEY_R);
            }
        }
        else {
            if (M_KEY_R < COMBO_BIT_PART_1_MAX ){
                all_key_status_0 &= ~COMBO_LW(M_KEY_R);
            }
            else {
                all_key_status_1 &= ~COMBO_HW(M_KEY_R);
            }
        }

        uint32_t comboKey_0 = combo_cfg->combo_bit_00_31;
        uint32_t comboKey_1 = combo_cfg->combo_bit_32_63;

        if (((comboKey_0 & all_key_status_0) == comboKey_0) && ((comboKey_1 & all_key_status_1) == comboKey_1)) {
            ret = true;
        }

        APP_LOGI(thisMOD, "app_button__combo_key_check = 0x%08X-%08X <=,  all_key_status = 0x%08X-%08X <=, ret = %d  "
                , comboKey_1
                , comboKey_0
                , all_key_status_1
                , all_key_status_0
                , ret
                    );
    }
    return ret;
}

static void app_button_IR_pairing_key_check_timeout(struct k_timer *timer_id)
{
    APP_LOGI(thisMOD,"app_button_IR_pairing_key_check_timeout");
    app_btn_announce_pairing_request(true);
}
#endif

static bool app_button__evt_riscv_key(const struct af_evt_header *evt_header)
{
    struct evt_riscv_key* event = (struct evt_riscv_key*)evt_header;
    APP_LOGI(thisMOD,"app_button__evt_riscv_key , key_status = %x", event->key_status);

    #if defined (CONFIG_AIR_SUPPORT_IRPT_LR_KEY)
    if(!IS_APP_STATE_IN_ACTIVE(app_state_current_state()))
    {
        app_button__announce_key_active_event();

        APP_LOGI(thisMOD,"PAIRING_KEY_PAIRING = 0x%08X-%08X <=, PAIRING_KEY_PRESS_AND_HOLD_TIME = %d ms"
            , combo_key_list[COMBO_KEY_PAIRING].combo_bit_32_63
            , combo_key_list[COMBO_KEY_PAIRING].combo_bit_00_31
            , PAIRING_KEY_PRESS_AND_HOLD_TIME);

        if (app_button__combo_key_check(&combo_key_list[COMBO_KEY_PAIRING], event->key_status)){
            k_timer_start(&app_button_IR_pairing_key_check, K_MSEC(PAIRING_KEY_PRESS_AND_HOLD_TIME), K_NO_WAIT);
        }
        else {
            k_timer_stop(&app_button_IR_pairing_key_check);
        }
    }
    else
    #else
    if(IS_APP_STATE_IN_ACTIVE(app_state_current_state()))
    #endif
    {
        for (uint8_t idx = 0; idx < mouse_key_num; idx++) {
            uint8_t current_key_state = (event->key_status >> idx) & 0x01;
            uint8_t previous_key_state = (last_key_status >> idx) & 0x01;
            APP_LOGI(thisMOD,"current_key_state = 0x%02X previous_key_state = 0x%02X"
                , current_key_state
                , previous_key_state
                );
            // Check if the key status has changed at this specific index
            if (current_key_state != previous_key_state) {
                uint8_t gpio_pin = airo_key_get_gpio_id_by_index(idx);

                // DPI/RR key call the handler with the updated status
                gesture_key_changed_handler(gpio_pin,  current_key_state ^ 0x01, idx);
            }
        }
        last_key_status = event->key_status;
    }


    return AF_TRAVERSE_NEXT;
}

static void app_button_enter_low_power_set_wakeup()
{
    if(app_button_state != APP_BUTTON_STATE_LOW_POWER)
    {
        APP_LOGI(thisMOD,"app_button_enter_low_power_set_wakeup");
        extern hal_gpio_status_t hal_gpio_wakeup_extend_sleep_config(hal_gpio_pin_t gpio_pin);
        #if !defined(CONFIG_AIR_M21_SAMPLE)
        hal_gpio_wakeup_extend_sleep_config(M_KEY_L);
        hal_gpio_wakeup_extend_sleep_config(M_KEY_R);
        hal_gpio_wakeup_extend_sleep_config(M_KEY_RR);
        #endif

        hal_gpio_wakeup_extend_sleep_config(M_KEY_M);
        hal_gpio_wakeup_extend_sleep_config(M_KEY_NK);
        hal_gpio_wakeup_extend_sleep_config(M_KEY_PK);
        #ifdef M_KEY_DPI
        hal_gpio_wakeup_extend_sleep_config(M_KEY_DPI);
        #endif

        app_button_state = APP_BUTTON_STATE_LOW_POWER;
    }
}

static void app_button_exit_low_power()
{
    if(app_button_state != APP_BUTTON_STATE_NORMAL)
    {
        APP_LOGI(thisMOD,"app_button_exit_low_power");
        extern hal_gpio_status_t hal_gpio_wakeup_extend_sleep_clear(hal_gpio_pin_t gpio_pin);
        #if !defined(CONFIG_AIR_M21_SAMPLE)
        hal_gpio_wakeup_extend_sleep_clear(M_KEY_L);
        hal_gpio_wakeup_extend_sleep_clear(M_KEY_R);
        hal_gpio_wakeup_extend_sleep_clear(M_KEY_RR);
        #endif

        hal_gpio_wakeup_extend_sleep_clear(M_KEY_M);
        hal_gpio_wakeup_extend_sleep_clear(M_KEY_NK);
        hal_gpio_wakeup_extend_sleep_clear(M_KEY_PK);
        #ifdef M_KEY_DPI
        hal_gpio_wakeup_extend_sleep_clear(M_KEY_DPI);
        #endif
        app_button_state = APP_BUTTON_STATE_NORMAL;
    }
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
uint8_t app_button_ms_key_polling(uint8_t * ms_key)
{
    return 0; //success
}

void app_button_init(uint8_t profile_idx, T_MOUSE_KEY_S *config_key_list)
{
    T_AIROHA_KEY_CONFIGURATION_S airo_key_cfg;

    app_button_state = APP_BUTTON_STATE_NORMAL;

    #if defined (CONFIG_AIR_SUPPORT_IRPT_LR_KEY)
    k_timer_init(&app_button_IR_pairing_key_check , app_button_IR_pairing_key_check_timeout, NULL);
    #endif

    if (config_key_list) {
        uint8_t * key_ptr = (uint8_t *)config_key_list;
        uint8_t cnt=0;
        mouse_LMR45_key_valid_num = 0;
        mouse_key_num = 0;

        for(uint8_t idx = 0; idx < sizeof(T_MOUSE_KEY_S) ; idx++)
        {
            if( key_ptr[idx] != GPIO_UNDEFINE){
                key_ids[cnt++] = key_ptr[idx];

                if(idx<5){
                    // the first 5 parameters are mouse 5 keys
                    mouse_LMR45_key_valid_num++;
                }
                mouse_key_num++;
            }
        }

        APP_LOGI(thisMOD,"config_key_list[7-0] = 0x%08X - %08X <=="
            , *(uint32_t*)&config_key_list->l_key
            , *(uint32_t*)&config_key_list->bw_key
            );
    }

    APP_LOGI(thisMOD,"app_button_init: config_key_list = 0x%X, mouse_key_num =%d , mouse_LMR45_key_valid_num = %d "
        , config_key_list
        , mouse_key_num
        , mouse_LMR45_key_valid_num
        );

    for (uint32_t idx = 0 ; idx < sizeof(combo_key_list)/sizeof(T_AIR_COMBO_KEY_S); idx ++){
        APP_LOGI(thisMOD,"combo_key_list[%d] = 0x%08X-%08X <= "
            , idx
            , combo_key_list[idx].combo_bit_32_63
            , combo_key_list[idx].combo_bit_00_31
            );
    }

    airo_key_cfg.key_handle_cb = app_button_key_event_cb;
    airo_key_cfg.key_list = key_ids;
    airo_key_cfg.key_list_size = mouse_key_num;
    airo_key_cfg.hold_timeout_ms = PRESS_AND_HOLE_LV_0_TO_1;
    airo_key_cfg.hold_timeout_LP2_ms = PRESS_AND_HOLE_LV_1_TO_2;  //The hold time between LP1 and LP2
    airo_key_cfg.hold_timeout_LP3_ms = PRESS_AND_HOLE_LV_2_TO_3;  //The hold time between LP2 and LP3
    airo_key_cfg.click_timeout_ms = MULTI_CLICK_GUARD_TIME;
    airo_key_cfg.combo_key_list = combo_key_list;
    airo_key_cfg.combo_key_list_size = sizeof(combo_key_list)/sizeof(T_AIR_COMBO_KEY_S);
    airo_key_cfg.debounce_time_list = gpio_debounce_list;
//    airo_key_cfg.timer_id_base_for_hold = FIND_MY_DEVICE_TIMER_ID_AK_HOLD_1;
//    airo_key_cfg.timer_id_base_for_multi_click = FIND_MY_DEVICE_TIMER_ID_AK_MULTI_1;;
    app_button_debounce_time_reload(profile_idx, false);
    airo_key_status_t ret = airo_key_init(&airo_key_cfg);
    if(ret){
        assert(0 && "airo_key_init fail !");
    }

    ret = gesture_key_reconfiguration((uint8_t*)key_ids, mouse_LMR45_key_valid_num, GESTURE_CFG_OPT_ENABLE_EINT_COUNTER);

    #if defined (CONFIG_AIR_DISABLE_MOUSE_KEY)
    hid_common->app.mouse_key_num = 0;
    hid_common_set_combo_key(NULL, 0, 0);
    #else
    hid_common_set_combo_key(combo_key_list, sizeof(combo_key_list)/sizeof(T_AIR_COMBO_KEY_S), 3);
    if(mouse_LMR45_key_valid_num > RISCV_MAX_KEY_NUM){
        mouse_LMR45_key_valid_num = RISCV_MAX_KEY_NUM;
        assert(0 && "mouse_key_list memcpy fail !");
    }
    hid_common->app.mouse_key_num = mouse_key_num - 1;  // Pairing key is virtual
    memcpy(hid_common->app.mouse_key_list, key_ids, mouse_key_num - 1);  // Pairing key is virtual
    #endif

    APP_LOGI(thisMOD,"app_button_init: ret = %d ", ret );
}

bool app_button_is_key_pressed()
{
    uint32_t all_key_status_0, all_key_status_1;
    bool is_pressed = false;
    airo_key_read_all_key_status(&all_key_status_0, &all_key_status_1);
    if (all_key_status_0 | all_key_status_1) {
        is_pressed = true;
    }
    APP_LOGI(thisMOD,"app_button_is_key_pressed = %d", is_pressed);
    return is_pressed;
}

bool app_button_labtest_combo_key_pressed()
{
    uint32_t all_key_status_0, all_key_status_1;
    T_AIR_COMBO_KEY_S labtest_combo = {COMBO_LW(M_KEY_L) | COMBO_LW(M_KEY_NK) | COMBO_LW(M_KEY_PK),
                                       COMBO_HW(M_KEY_L) | COMBO_HW(M_KEY_NK) | COMBO_HW(M_KEY_PK)};
    bool is_pressed = false;
    airo_key_read_all_key_status(&all_key_status_0, &all_key_status_1);
    if (((labtest_combo.combo_bit_00_31 & all_key_status_0) == labtest_combo.combo_bit_00_31)
        && ((labtest_combo.combo_bit_32_63 & all_key_status_1) == labtest_combo.combo_bit_32_63)) {
        is_pressed = true;
    }
    APP_LOGI(thisMOD,"app_button_labtest_combo_key_pressed = %d", is_pressed);
    return is_pressed;
}

/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_app_state, app_button__evt_app_state);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_active_status, app_button_evt_active_status);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_race_cmd_req, app_button_evt_race_cmd_req);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_riscv_key, app_button__evt_riscv_key);

/*=============================================================================*/