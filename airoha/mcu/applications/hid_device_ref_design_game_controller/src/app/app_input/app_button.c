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

#include "gesture.h"
#include "app_pin_config_parser.h"
#include "app_button.h"
#include "app_state.h"
#include "hid_common.h"
#include "app_nvkey.h"
#include "app_labtest.h"
#include "app_rgb.h"
#include "app_battery.h"
#include "app_usb_port.h"
#include "app_slide_switch.h"

#ifdef CONFIG_IO_EXPANDER_AW95124
#include "io_expander_sensor_mgr.h"
#endif

#if defined(AIR_USB_XINPUT_ENABLE)
#include "air_usb.h"
#include "hid_race_cmd.h"
#include "hal_gpt.h"
#include "hal_nvic.h"
#endif

#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#include "key_remap_backend.h"
#endif

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
static void app_button_set_each_key_debounce(uint8_t debounce_time);
static void app_button_set_each_key_extslp_debounce(uint8_t debounce_time);
static void app_btn_key_event_announcement(uint8_t key_id, airoha_key_event_t key_event);
static void app_btn_announce_pairing_request();

static void app_button_enter_low_power_set_wakeup();
static void app_button_exit_low_power();

#if !defined (CONFIG_IO_EXPANDER_AW95124)
static void app_btn_change_usb_mode_request(void);
#endif

static uint8_t app_change_usb_mode();

/**********************************f********************************************/
/* variables                                                                  */
/******************************************************************************/
static uint8_t key_ids[] =
{
    GC_KEY_D_UP,
    GC_KEY_D_DOWN,
    GC_KEY_D_LEFT,
    GC_KEY_D_RIGHT,
    GC_KEY_LT_SW,
    GC_KEY_RT_SW,
    GC_KEY_LT_MODE,
    GC_KEY_RT_MODE,
    GC_KEY_A,
    GC_KEY_B,
    GC_KEY_X,
    GC_KEY_Y,
    GC_KEY_JOYS_L,
    GC_KEY_JOYS_R,
    GC_KEY_LB,
    GC_KEY_RB,/*  16*/
    GC_KEY_HOME1,
    GC_KEY_MENU,
    GC_KEY_VIEW,
    GC_KEY_M1,
    GC_KEY_M2,
    GC_KEY_M3,
    GC_KEY_M4,
    GC_KEY_M5,
    GC_KEY_M6,
    GC_KEY_G1,
    GC_KEY_G2,
    GC_KEY_G3,
    GC_KEY_G4,
    GC_KEY_G5,
    GC_KEY_PAIR,
    GC_RESERVED_KEY1,
};

uint8_t device_key_num = sizeof(key_ids);

uint8_t profile_debounce_list[MAX_PROFILE_COUNT] = {DEFAULT_DEBOUNCE_TIME, DEFAULT_DEBOUNCE_TIME, DEFAULT_DEBOUNCE_TIME, DEFAULT_DEBOUNCE_TIME};

uint8_t gpio_debounce_list[] =
{
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_D_UP
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_D_DOWN
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_D_LEFT
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_D_RIGHT
    DEFAULT_DEBOUNCE_TIME,  // GC_RESERVED_KEY0
    DEFAULT_DEBOUNCE_TIME,  // GC_RESERVED_KEY1
    DEFAULT_DEBOUNCE_TIME,  // GC_RESERVED_KEY2
    DEFAULT_DEBOUNCE_TIME,  // GC_RESERVED_KEY3
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_A
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_B
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_X
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_Y
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_JOYS_L
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_JOYS_R
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_LB
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_RB
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_HOME1
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_MENU
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_VIEW
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_M1
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_M2
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_M3
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_M3
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_M5
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_M6
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_G1
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_G2
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_G3
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_G4
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_G5
    DEFAULT_DEBOUNCE_TIME,  // GC_KEY_PAIR
    DEFAULT_DEBOUNCE_TIME,  // GC_RESERVED_KEY1
};

T_AIR_COMBO_KEY_S combo_key_list[] =
{
    {COMBO_KEYS(4, GC_KEY_A, GC_KEY_B, GC_KEY_X, GC_KEY_Y)},
    {COMBO_KEYS(4, GC_KEY_D_UP, GC_KEY_D_RIGHT, GC_KEY_A, GC_KEY_B)},
    #ifndef CONFIG_IO_EXPANDER_AW95124
    {COMBO_KEYS(3, GC_KEY_D_UP, GC_KEY_D_LEFT, GC_KEY_JOYS_R)},
    #endif
};

static uint8_t profile_idx = DEFAULT_PROFILE_IDX;
static uint32_t last_key_status = 0;
bool app_btn_low_battery_check = false;
uint8_t app_btn_low_power_state = 0; //0:NORMAL_MODE, 1:LOW_POWER_MODE
uint8_t app_btn_power_off_status = 0;
uint8_t io_expander_off_status = 0;
static T_APP_BUTTON_STATE_E app_button_state = APP_BUTTON_STATE_NORMAL;

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
        ret =  gesture_key_reconfiguration((uint8_t*)key_ids, device_key_num, GESTURE_CFG_OPT_ENABLE_KEY_IRQ);
    }
    else {
        ret =  gesture_key_reconfiguration((uint8_t*)key_ids, device_key_num, GESTURE_CFG_OPT_DISABLE_KEY_IRQ);
    }
    APP_LOGI(thisMOD,"app_button__button_irq_ctrl enable = %d, ret  = 0x%x ", enable , ret );
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
            app_btn_power_off_status = 0;
            #ifdef CONFIG_IO_EXPANDER_AW95124
            if(io_expander_off_status){
                io_expander_mgr_exit_low_power();
                io_expander_off_status = 0;
            }
            #endif
            // #if !defined(FAKE_REPORT_TRIGGER_BY_MIDDLE_KEY)
            // app_button__button_irq_ctrl(false);
            // #endif
            #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
            if (app_button_state == APP_BUTTON_STATE_SUSPEND_RESUME)
            {
                app_button_state = APP_BUTTON_STATE_NORMAL;
                app_button_exit_low_power();
                app_button_set_each_key_debounce(profile_debounce_list[profile_idx]);
            }
            #endif
        }
        break;
        #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
        case APP_STATE_2_4G_RECONNECT_RESUME_WAIT:
        {
            app_button_state = APP_BUTTON_STATE_SUSPEND_RESUME;
        }
        #endif
        case APP_STATE_STANDBY:
        {
            bool bat_power = app_battery__get_battery_power();
            #if defined (CONFIG_AIR_APP_STANDBY_WITH_ADAPTOR_RGB)
            if(app_usb_port__get_usb_plug_status() != APP_USB_PLUG_OUT)
            {

            } else
            #endif
            {
                if(bat_power)
                {
                    app_button_set_each_key_extslp_debounce(0); /* 62.5us debounce time */
                    app_button__button_irq_ctrl(true);
                }
                app_button_enter_low_power_set_wakeup();
                if(!bat_power){  //action after set wakeup
                    app_btn_low_battery_check = true;
                    app_button__button_irq_ctrl(false);
                }
            }
            #if defined (CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF)
            if(app_btn_power_off_status)
            {
                #ifdef CONFIG_IO_EXPANDER_AW95124
                io_expander_mgr_enter_low_power();
                io_expander_off_status = 1;
                #endif
                gesture_key_all_click_reset((uint8_t*)key_ids, device_key_num, true);
                app_button__button_irq_ctrl(false);
                uint8_t temp_ids[] = {GC_KEY_HOME1};
                gesture_key_reconfiguration((uint8_t*)temp_ids, sizeof(temp_ids), GESTURE_CFG_OPT_ENABLE_KEY_IRQ);
                temp_ids[0] = 0;
                gesture_key_reconfiguration((uint8_t*)temp_ids, sizeof(temp_ids), GESTURE_CFG_OPT_DISABLE_KEY_IRQ);
            }
            #endif
        }
        break;

        case APP_STATE_USB_SUSPEND:
        case APP_STATE_DISCONNECTED:
        {
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
            app_btn_power_off_status = 0;
            app_button_set_each_key_debounce(profile_debounce_list[profile_idx]);
            app_button__button_irq_ctrl(true);
            #ifdef CONFIG_IO_EXPANDER_AW95124
            if(io_expander_off_status){
                io_expander_mgr_exit_low_power();
                io_expander_off_status = 0;
            }
            #endif
        }
        break;

        default:
        break;
    }

    return AF_TRAVERSE_NEXT;
}

#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
void app_button_key_remap_process()
{
    key_remap_update_key_status(last_key_status);
    key_remap_backend_process();
}

void app_button__announce_remap_backend_process()
{
    struct evt_remap_backend_process* event = create_evt_remap_backend_process();
    if (event){
        AF_EVT_SUBMIT(event);
    }
}
#endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */

void app_button__announce_key_active_event()
{
    APP_LOGI(thisMOD,"app_button__announce_key_active_event, app_btn_power_off_status = %d" , app_btn_power_off_status);
    if(!app_btn_power_off_status)
    {
        struct evt_active_status* event = create_evt_active_status();
        if (event){
            event->active = true;
            event->type = KEY_WAKEUP;
            AF_EVT_SUBMIT(event);
        }
    }
}

bool app_button__check_key_release_event(airoha_key_event_t event)
{
    if ((event == AK_RELEASE) ||
        (event >= AK_LONG_PRESS_RELEASE_1 && event <= AK_LONG_PRESS_RELEASE_3))
    {
        return true;
    }
    return false;
}

#if defined (CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF)
bool app_button__home_key_event_handler(airoha_key_event_t event,uint8_t key_id)
{
    if(key_id != GC_KEY_HOME1)
    {
        return false;
    }
    switch(event)
    {
        case AK_LONG_PRESS_LV_1:
        {
            uint8_t ss_type = SS_MODE_NONE;
            GET_SLIDE_SWITCH_MODE(&ss_type);
            if(app_btn_power_off_status && (ss_type != SS_MODE_OFF))
            {
                app_btn_power_off_status = 0;
                uint8_t temp_ids[] = {0};
                gesture_key_reconfiguration((uint8_t*)temp_ids, sizeof(temp_ids), GESTURE_CFG_OPT_ENABLE_KEY_IRQ);
                app_button__announce_key_active_event();
            }
            break;
        }
        case AK_LONG_PRESS_LV_3:
        {
            app_btn_power_off_status = 1;
            struct evt_app_state_change_req* evt = (struct evt_app_state_change_req*)create_evt_app_state_change_req();
            if (evt){
                evt->app_state = APP_STATE_STANDBY;
                AF_EVT_SUBMIT(evt);
            }
            break;
        }

        default:{
            return false;
        }
    }
    return true;
}
#endif /* CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF */

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
            if(app_state_check(TYPE_CONNECTED_WO_ACTIVE)){
                app_button__announce_key_active_event();
            }
        }
        break;

        case AK_COMBO_HOLD_LV1_0:
        {
            app_button_set_each_key_debounce(0);
        }
        break;

        case AK_COMBO_HOLD_LV1_1:
        {

        }
        break;

        case AK_COMBO_HOLD_LV1_2:
        {
            #ifndef CONFIG_IO_EXPANDER_AW95124
            app_btn_announce_pairing_request();
            #endif
        }
        break;

        case AK_COMBO_HOLD_LV1_3:
        {

        }
        break;

        case AK_DLONG:
        {
            APP_LOGI(thisMOD,"Key[%d] %d clicks and Long press", key_id, event - AK_CLICK_AND_LONG_PRESS_TYPE_MASK);
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
            if(key_id == GC_KEY_HOME1){
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
        }
        break;

        case AK_DOUBLE_CLICK:
        {
            APP_LOGI(thisMOD,"Key[%d] Double clicks", key_id);
        }
        break;

        case AK_TRIPLE_CLICK:
        {
            APP_LOGI(thisMOD,"Key[%d] Tripple clicks", key_id);
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
            APP_LOGI(thisMOD,"Key[%d] Press and hold level 1 (1.5s)", key_id);
        }
        break;

        case AK_LONG_PRESS_LV_2:
        {
            APP_LOGI(thisMOD,"Key[%d] Press and hold level 2 (1.5+1.5s)", key_id);
            if (key_id == GC_KEY_PAIR)
            {
                app_btn_announce_pairing_request();
            }
            break;
        }
        break;
        case AK_LONG_PRESS_LV_3:
        {
            APP_LOGI(thisMOD,"Key[%d] Press and hold level 3 (1.5+1.5+2s)", key_id);
            #if !defined (CONFIG_IO_EXPANDER_AW95124)
            if (key_id == GC_KEY_MENU)
            {
                app_btn_change_usb_mode_request();
            }
            #endif
        }
        break;

        default:
            break;
    }
}

void app_button_key_event_cb(airoha_key_event_t event, uint8_t key_id)
{
    uint8_t app_state = app_state_current_state();
    uint8_t key_idx = airo_key_get_key_index(key_id);

    #if defined (CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF)
    if(key_id == GC_KEY_HOME1 || app_btn_power_off_status)
    {
        if(app_button__home_key_event_handler(event,key_id))
        {
            return;
        }
    }
    #endif /* CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF */

    if((app_state == APP_STATE_STANDBY)
    #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
        || (app_state == APP_STATE_2_4G_RECONNECT_RESUME_WAIT)
    #endif
    )
    {
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
    APP_LOGI(thisMOD,"app_key_event key_%d event = 0x%x, last_key_status = %x" , key_id, event, last_key_status);

    #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    if(((event == AK_PRESS) || (event == AK_RELEASE)))
    {
        if(app_state == APP_STATE_STANDBY)
        {
            app_button__announce_remap_backend_process();
        }
        else if((!(app_state & APP_STATE_CONNECTED)))
        {
            app_button_key_remap_process();
        }
    }
    #endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */
    hid_common_button_lt_rt_mode_update(last_key_status);
    app_btn_key_event_announcement(key_id, event);

    app_button_key_event_hdl(event, key_id);
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
            app_button__button_irq_ctrl(true);
        }
    }
    else if(event->active && 
            ((app_state == APP_STATE_STANDBY)
            #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
            || (app_state == APP_STATE_2_4G_RECONNECT_RESUME_WAIT)
            #endif
            ))
    {
        switch(event->type)
        {
            case MOTION_SENSOR_WAKEUP:
            case WHEEL_WAKEUP:
            case KEY_WAKEUP:
            #if defined (CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH)
            case SLIDE_SWITCH_WAKEUP:
            #endif
            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
            case USB_PLUG_WAKEUP:
            #endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/
            {
                // #ifdef CONFIG_IO_EXPANDER_AW95124
                // if(io_expander_off_status){
                //     io_expander_mgr_exit_low_power();
                //     io_expander_off_status = 0;
                // }
                // #endif
                app_button_exit_low_power();
                if(app_btn_low_battery_check){
                    app_btn_low_battery_check = false;
                    app_button__button_irq_ctrl(true);
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

#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
static bool app_button_evt_remap_backend_process(const struct af_evt_header *evt_header)
{
    APP_LOGI(thisMOD,"app_button_evt_remap_backend_process");
    uint32_t app_state = app_state_current_state();

    if(!(app_state & APP_STATE_CONNECTED))
    {
        app_button_key_remap_process();
    }

    return AF_TRAVERSE_NEXT;
}
#endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */
/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static void app_button_set_each_key_debounce(uint8_t debounce_time)
{
    for (uint8_t idx = 0 ; idx < sizeof(gpio_debounce_list); idx ++ )
    {
        gpio_debounce_list[idx] = debounce_time;
        airo_key_gpio_debounce_config(idx, debounce_time);
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
        gpio_debounce_list[idx] = profile_debounce_list[profile_idx];
    }

    for(idx = 0; idx < MAX_PROFILE_COUNT; idx++){
        APP_LOGI(thisMOD,"debounce time idx = %d, value = %d", idx, profile_debounce_list[idx]);
    }
    return 0;
}

static void app_btn_announce_pairing_request()
{
    struct evt_pairing_request* event = create_evt_pairing_request();
    if (event){
        event->type = PAIRING_REQ_RECOVERABLE;
        event->force_key_release_req = true;
        AF_EVT_SUBMIT(event);
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

        case RACE_CMD_SET_USB_MODE:
        {
            res = app_change_usb_mode();
        }
        break;

        default:
        break;
    }
    return AF_TRAVERSE_NEXT;
}

static bool app_button_evt_slide_switch_status(const struct af_evt_header *evt_header)
{
    struct evt_slide_switch_status* event = (struct evt_slide_switch_status*)evt_header;
    APP_LOGI(thisMOD,"app_state__evt_slide_switch_status, position = %d", event->position);

    switch(event->position)
    {
        case SLIDE_SWITCH_POS_OFF:
        {
            #if defined (CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF)
            app_btn_power_off_status = 1;
            #endif /* CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF */
            break;
        }
        case SLIDE_SWITCH_POS_BT:
        {
            if(!app_state_check(TYPE_IN_BT_STATES))
            {
                #if defined (CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF)
                app_btn_power_off_status = 1;
                #endif /* CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF */
            }
            break;
        }
        case SLIDE_SWITCH_POS_GAMING:
        {
            if(!app_state_check(TYPE_IN_GAMING_STATES))
            {
                #if defined (CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF)
                app_btn_power_off_status = 1;
                #endif /* CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF */
            }
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}

static void app_button_enter_low_power_set_wakeup()
{
    APP_LOGI(thisMOD,"app_button_enter_low_power_set_wakeup, low_power_state = %d, enter_power_off_status = %d", app_btn_low_power_state, app_btn_power_off_status);
    if(!app_btn_low_power_state)
    {
        extern hal_gpio_status_t hal_gpio_wakeup_extend_sleep_config(hal_gpio_pin_t gpio_pin);
        for(uint8_t idx = 0; idx < device_key_num ; idx++)
        {
            hal_gpio_wakeup_extend_sleep_config(key_ids[idx]);
        }
        #ifdef CONFIG_IO_EXPANDER_AW95124
        hal_gpio_wakeup_extend_sleep_config(0);
        #endif
        app_btn_low_power_state = 1;
    }
}

static void app_button_exit_low_power()
{
    APP_LOGI(thisMOD,"app_button_exit_low_power, low_power_state = %d, enter_power_off_status = %d", app_btn_low_power_state, app_btn_power_off_status);
    if(app_btn_low_power_state)
    {
        extern hal_gpio_status_t hal_gpio_wakeup_extend_sleep_clear(hal_gpio_pin_t gpio_pin);
        for(uint8_t idx = 0; idx < device_key_num ; idx++)
        {
            hal_gpio_wakeup_extend_sleep_clear(key_ids[idx]);
        }
        #ifdef CONFIG_IO_EXPANDER_AW95124
        hal_gpio_wakeup_extend_sleep_clear(0);
        #endif
        app_btn_low_power_state = 0;
    }
}

#if !defined (CONFIG_IO_EXPANDER_AW95124)
static void app_btn_change_usb_mode_request(void)
{
    struct evt_race_cmd_req* event = create_evt_race_cmd_req();
    if (event){
        event->cmd = RACE_CMD_SET_USB_MODE;
        AF_EVT_SUBMIT(event);
    }
}
#endif

static uint8_t app_change_usb_mode(void)
{
#if defined(AIR_USB_XINPUT_ENABLE)
    air_usb_mode_t usb_mode = USB_MODE_HID;
    uint32_t nvkey_size = sizeof(air_usb_mode_t);
    nvkey_status_t nvkey_ret = nvkey_read_data(NVID_APP_USB_MODE, (uint8_t *)&usb_mode, &nvkey_size);
    if ((nvkey_size != sizeof(air_usb_mode_t)) || (nvkey_ret != NVKEY_STATUS_OK))
    {
        usb_mode = USB_MODE_HID;
        LOG_INF("app_btn_change_usb_mode_request load usb mode fail, size = %d, ret = %d.", nvkey_size, nvkey_ret);
    }
    else
    {
        if (usb_mode == USB_MODE_HID)
        {
            usb_mode = USB_MODE_XINPUT;
        }
        else
        {
            usb_mode = USB_MODE_HID;
        }
    }

    race_errcode_enum ret = RACE_ERRCODE_SUCCESS;
    nvkey_write_data(NVID_APP_USB_MODE, (uint8_t *)&usb_mode, sizeof(air_usb_mode_t));
    if (app_state_check(TYPE_IN_GAMING_STATES))
    {
        /* send change mode cmd to dongle */
        ret = hid_race_set_usb_mode_req(usb_mode);
    }
    else
    {
        /* reboot device to load new usb mode setting */
        uint32_t mask;
        hal_nvic_save_and_set_interrupt_mask(&mask);
        hal_gpt_delay_ms(10);
        hal_wdt_software_reset();
        hal_nvic_restore_interrupt_mask(mask);
    }
    LOG_INF("app_btn_change_usb_mode_request change usb mode = %d, ret = %d.", usb_mode, ret);
#endif /* AIR_USB_XINPUT_ENABLE */

    return 0;
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
void app_button_init(uint8_t profile_idx, T_DEVICE_KEY_S *config_key_list)
{
    T_AIROHA_KEY_CONFIGURATION_S airo_key_cfg;
    uint32_t all_key_status_0, all_key_status_1;

    if (config_key_list) {
        uint8_t * key_ptr = (uint8_t *)config_key_list;
        uint8_t cnt = 0;
        device_key_num = 0;

        for(uint8_t idx = 0; idx < sizeof(T_DEVICE_KEY_S); idx++)
        {
            if( key_ptr[idx] != GPIO_UNDEFINE){
                key_ids[cnt++] = key_ptr[idx];
                device_key_num++;
            }
        }
        // APP_LOGI(thisMOD,"config_key_list[7-0] = 0x%08X - %08X <=="
        //     , *(uint32_t*)&config_key_list->l_key
        //     , *(uint32_t*)&config_key_list->bw_key
        //     );
    }

    APP_LOGI(thisMOD,"app_button_init: config_key_list = 0x%X, device_key_num =%d"
        , config_key_list
        , device_key_num
        );

    // for (uint32_t idx = 0 ; idx < sizeof(combo_key_list)/sizeof(T_AIR_COMBO_KEY_S); idx ++){
    //     APP_LOGI(thisMOD,"combo_key_list[%d] = 0x%08X-%08X <= "
    //         , idx
    //         , combo_key_list[idx].combo_bit_32_63
    //         , combo_key_list[idx].combo_bit_00_31
    //         );
    // }

    airo_key_cfg.key_handle_cb = app_button_key_event_cb;
    airo_key_cfg.key_list = key_ids;
    airo_key_cfg.key_list_size = device_key_num;
    airo_key_cfg.hold_timeout_ms = PRESS_AND_HOLE_LV_0_TO_1;
    airo_key_cfg.hold_timeout_LP2_ms = PRESS_AND_HOLE_LV_1_TO_2;  //The hold time between LP1 and LP2
    airo_key_cfg.hold_timeout_LP3_ms = PRESS_AND_HOLE_LV_2_TO_3;  //The hold time between LP2 and LP3
    airo_key_cfg.click_timeout_ms = MULTI_CLICK_GUARD_TIME;
    airo_key_cfg.combo_key_list = combo_key_list;
    airo_key_cfg.combo_key_list_size = sizeof(combo_key_list)/sizeof(T_AIR_COMBO_KEY_S);
    // airo_key_cfg.combo_key_list = NULL;
    // airo_key_cfg.combo_key_list_size = 0;
    airo_key_cfg.debounce_time_list = gpio_debounce_list;
//    airo_key_cfg.timer_id_base_for_hold = FIND_MY_DEVICE_TIMER_ID_AK_HOLD_1;
//    airo_key_cfg.timer_id_base_for_multi_click = FIND_MY_DEVICE_TIMER_ID_AK_MULTI_1;;
    app_button_debounce_time_reload(profile_idx, false);
    airo_key_status_t ret = airo_key_init(&airo_key_cfg);
    if(ret){
        APP_LOGI(thisMOD,"airo_key_init fail, ret = %d", ret);
        assert(0 && "airo_key_init fail !");
    }

    last_key_status = airo_key_read_all_key_status(&all_key_status_0, &all_key_status_1);
    hid_common_button_lt_rt_mode_update(last_key_status);

    #if 0
    ret = gesture_key_reconfiguration((uint8_t*)key_ids, device_key_num, GESTURE_CFG_OPT_ENABLE_EINT_COUNTER);
    hid_common_set_combo_key(combo_key_list, sizeof(combo_key_list)/sizeof(T_AIR_COMBO_KEY_S), 3);
    #endif

    hid_common->app.device_key_num = device_key_num;
    memcpy(hid_common->app.device_key_list, key_ids, device_key_num);

    #if defined (CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF)
    uint16_t record_fota = 0;
    app_nvkey_read_data(NVID_APP_FOTA_RECOED_RR, (uint8_t*)&record_fota, sizeof(record_fota));
    app_btn_power_off_status = record_fota ? 0 : 1;
    #endif
    APP_LOGI(thisMOD,"app_button_init: ret = %d, power_off_status = %d", ret, app_btn_power_off_status);
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
    // uint32_t all_key_status_0, all_key_status_1;
    // T_AIR_COMBO_KEY_S labtest_combo = {COMBO_LW(M_KEY_L) | COMBO_LW(M_KEY_NK) | COMBO_LW(M_KEY_PK),
    //                                    COMBO_HW(M_KEY_L) | COMBO_HW(M_KEY_NK) | COMBO_HW(M_KEY_PK)};
    bool is_pressed = false;
    // airo_key_read_all_key_status(&all_key_status_0, &all_key_status_1);
    // if (((labtest_combo.combo_bit_00_31 & all_key_status_0) == labtest_combo.combo_bit_00_31)
    //     && ((labtest_combo.combo_bit_32_63 & all_key_status_1) == labtest_combo.combo_bit_32_63)) {
    //     is_pressed = true;
    // }
    // APP_LOGI(thisMOD,"app_button_labtest_combo_key_pressed = %d", is_pressed);
    return is_pressed;
}

uint8_t app_button_get_power_off_status()
{
    APP_LOGI(thisMOD,"app_btn_power_off_status = %d", app_btn_power_off_status);
    return app_btn_power_off_status;
}

/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_app_state, app_button__evt_app_state);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_active_status, app_button_evt_active_status);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_race_cmd_req, app_button_evt_race_cmd_req);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_slide_switch_status, app_button_evt_slide_switch_status);
#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_remap_backend_process, app_button_evt_remap_backend_process);
#endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */
/*=============================================================================*/
