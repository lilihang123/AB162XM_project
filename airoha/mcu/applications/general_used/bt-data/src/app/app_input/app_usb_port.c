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


#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/class/usb_hid.h>

#include "app_usb_port.h"
#include "app_battery.h"
#include "app_state.h"
#include "app_button.h"
#include "app_slide_switch.h"
#include "app_feature_defines.h"
#include "app_power_manager.h"
#include "hid_scenario_USB_mode.h"

#include "hal_sleep_manager.h"
#include "hal_sleep_manager_platform.h"

#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
#include "air_usb.h"
#endif /* defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE) */


#define thisMODULE usb_port
#define thisMOD    "usb_port"
LOG_MODULE_REGISTER(thisMODULE);

/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
bool app_usb_port__get_vbus_ready(void);

#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
void app_usb_port__check_usb_port_status(struct k_timer *timer_id);
void app_usb_port__check_usb_configured_status(struct k_timer *timer_id);
void app_usb_port__change_plugged_status(uint8_t status);

static void app_usb_port__usb_enable_handler(bool status);
static void app_usb_port_announce_usb_status(uint8_t status);
static void app_usb_port__announce_active_status();
static void app_usb_port_set_hid_flag();

/* timers defined ------------------------------------------------------------*/
K_TIMER_DEFINE(check_plugged_timer, app_usb_port__check_usb_port_status, NULL);
K_TIMER_DEFINE(check_configured_timer, app_usb_port__check_usb_configured_status, NULL);

/******************************************************************************/
/* variables                                                          */
/******************************************************************************/
static uint8_t app_usb_plug = APP_USB_PLUG_OUT;
static uint8_t app_usb_enable = 0;
static uint32_t init_configured_time = 0;

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/
void app_usb_port__check_usb_port_status(struct k_timer *timer_id)
{
    uint8_t plug_status = app_usb_plug;
    uint8_t usb_enable_status = app_usb_enable;
    APP_LOGI(thisMOD,"app_usb_port__check_usb_port_status, plug_in = %d, enable = %d", plug_status, usb_enable_status);
    // plug in   configured   ACTION
    //    0          0       if enable, do disable          (plug out when in charger)
    //    0          1       if enable, do disable          (plug out when in PC)
    //    1          0       enable, and check configured   (plug in when in charger)
    //    1          0       enable, and check configured   (plug in when in PC)
    //    1          1       -

    app_usb_port_set_hid_flag();
    if(plug_status == APP_USB_PLUG_IN)
    {
        app_usb_port_announce_usb_status(USB_STATUS_PLUGGED_IN);

        uint8_t state = app_state_current_state();
        #if defined(CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF) || defined(CONFIG_AIR_APP_USB_DISABLE_IN_WIRELESS)
        uint8_t ss_type = SS_MODE_NONE;
        GET_SLIDE_SWITCH_MODE(&ss_type);
        #endif

        #if defined (CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF)
        if(state == APP_STATE_STANDBY && !app_button_get_power_off_status())
        #else
        if(state == APP_STATE_STANDBY)
        #endif
        {
            #if defined(CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF)
            if(ss_type == SS_MODE_BT || ss_type == SS_MODE_2_4G)
            #endif /* CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF */
            {
                app_usb_port__announce_active_status();
            }
        }
        #if defined(CONFIG_AIR_APP_USB_DISABLE_IN_WIRELESS)
        if(ss_type == SS_MODE_OFF)
        #endif /* CONFIG_AIR_APP_USB_DISABLE_IN_WIRELESS */
        {
            app_usb_port__usb_enable_handler(true);
        }
    }
    else
    {
        if(plug_status == APP_USB_CONFIGURED){
            APP_LOGI(thisMOD,"You DIDNOT mount on any device! plug_in = %d, enable = %d", plug_status, usb_enable_status);
        }
        app_usb_port_announce_usb_status(USB_STATUS_PLUGGED_OUT);
        app_usb_port__usb_enable_handler(false);
    }
}

void app_usb_port__check_usb_configured_status(struct k_timer *timer_id)
{
    uint8_t plug_status = app_usb_plug;
    uint8_t usb_enable_status = app_usb_enable;
    APP_LOGI(thisMOD,"app_usb_port__check_usb_configured_status, plug_in = %d, enable = %d", plug_status, usb_enable_status);
    // plug in   configured   ACTION
    //    0          0       if enable, do disable (plug out before configured)
    //    0          1       if enable, do disable (plug out after configured)
    //    1          0       if enable, do disable (plug in but configured fail)
    //    1          1       submit PLUG-IN event  (plug in after configured)
    if(plug_status == APP_USB_CONFIGURED)
    {
        app_usb_port__change_plugged_status(plug_status);  // 2
        return;
    }
    else if(usb_enable_status){
        APP_LOGI(thisMOD,"You CANNOT mount on this device now, keep wait for configured!");
    }
}

/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
static inline void app_usb_port__start_timer(struct k_timer *timer, int interval_ms)
{
    APP_LOGI(thisMOD,"app_usb_port__start_timer, for %d ms timer", interval_ms);
    k_timer_stop(timer);
    k_timer_start(timer, K_MSEC(interval_ms), K_NO_WAIT);
}

static void app_usb_port__hid_usb_handler(uint8_t event)
{
    switch(event)
    {
        case AIR_USB_EVT_PLUG_IN:
        {
            uint8_t state = app_state_current_state();
            APP_LOGI(thisMOD,"app_usb_port__hid_usb_handler, AIR_USB_EVT_PLUG_IN, app_state = %02X", state);
            if(state == APP_STATE_INITIALIZED){
                APP_LOGI(thisMOD,"Wait for USB to be configured!");
            }
            app_usb_plug = APP_USB_PLUG_IN;
            app_usb_port__start_timer(&check_plugged_timer, USB_CHECKING_PLUGGED_TIMEOUT);
            break;
        }
        case AIR_USB_EVT_PLUG_OUT:
        {
            APP_LOGI(thisMOD,"app_usb_port__hid_usb_handler, AIR_USB_EVT_PLUG_OUT");
            app_usb_plug = APP_USB_PLUG_OUT;

            app_usb_port__start_timer(&check_plugged_timer, USB_CHECKING_PLUGGED_TIMEOUT);
            break;
        }
        case AIR_USB_EVT_CONFIGURED:
        {
            APP_LOGI(thisMOD,"app_usb_port__hid_usb_handler, AIR_USB_EVT_CONFIGURED, plug_in = %d", app_usb_plug);
            app_usb_plug = APP_USB_CONFIGURED;
            app_usb_enable = true;
            uint8_t state = app_state_current_state();

            if(k_timer_remaining_get(&check_plugged_timer)){
                k_timer_stop(&check_plugged_timer);
            }

            if(state == APP_STATE_INITIALIZED){
                uint32_t curr_time = k_uptime_get_32();
                uint16_t delta_time = CALCULATE_DELTA_TIME(curr_time, init_configured_time);
                APP_LOGI(thisMOD, "Check configured in init finish, check configured use %d ms.", delta_time);
            }

            if(state != APP_STATE_USB_ACTIVE){
                app_usb_port__check_usb_configured_status(&check_configured_timer);
                k_timer_stop(&check_configured_timer);
            }
            else{
                APP_LOGI(thisMOD, "Received reset and configured in state USB ACTIVE!");
                hid_scenario_usb_for_applaciton(HID_SCENARIO_APP_USB_SOF_ON);
            }
            break;
        }
        case AIR_USB_EVT_RESET:
        {
            APP_LOGI(thisMOD,"app_usb_port__hid_usb_handler, AIR_USB_EVT_RESET, plug_in = %d", app_usb_plug);
            break;
        }
        case AIR_USB_EVT_SUSPEND:
        {
            APP_LOGI(thisMOD,"app_usb_port__hid_usb_handler, AIR_USB_EVT_SUSPEND, plug_in = %d", app_usb_plug);
            break;
        }
        default:{
            break;
        }
    }
}

static bool app_usb_port__evt_usb_status(const struct af_evt_header *evt_header)
{
    struct evt_usb_status* event = (struct evt_usb_status*)evt_header;
    APP_LOGI(thisMOD,"app_usb_port__evt_usb_status, status = %d, plug_in = %d, enable = %d", event->status, app_usb_plug, app_usb_enable);

    switch(event->status)
    {
        case USB_STATUS_READY_TO_ENABLE:  //2
        {
            if(!app_usb_enable)
            {
                APP_LOGI(thisMOD, "USB ready to enable");
                app_usb_enable = true;
                hid_scenario_usb_for_applaciton(HID_SCENARIO_APP_USB_ENABLE);
            }
            else{
                APP_LOGI(thisMOD, "You cant enable USB again!");
            }
            break;
        }
        case USB_STATUS_READY_TO_DISABLE:  //3
        {
            if(app_usb_enable)
            {
                APP_LOGI(thisMOD, "USB ready to disable");
                app_usb_enable = false;
                app_usb_plug = app_usb_port__get_vbus_ready();
                hid_scenario_usb_for_applaciton(HID_SCENARIO_APP_USB_DISABLE);
            }
            else{
                APP_LOGI(thisMOD, "You cant disable USB when it is not enabled!");
            }
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}

#if defined(CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH)
static bool app_usb_port__evt_slide_switch_status(const struct af_evt_header *evt_header)
{
    struct evt_slide_switch_status* event = (struct evt_slide_switch_status*)evt_header;
    APP_LOGI(thisMOD,"app_usb_port__evt_slide_switch_status, position = %d, plug_in = %d, enable = %d", event->position, app_usb_plug, app_usb_enable);

    switch(event->position)
    {
        case SLIDE_SWITCH_POS_OFF:
        {
            if(!app_usb_enable && app_usb_plug){
                app_usb_port__usb_enable_handler(true);
            }
            break;
        }
        case SLIDE_SWITCH_POS_BT:
        case SLIDE_SWITCH_POS_GAMING:
        {
            #if defined(CONFIG_AIR_APP_USB_DISABLE_IN_WIRELESS)
            if(app_usb_enable && app_usb_plug){
                app_usb_port__usb_enable_handler(false);
            }
            #endif
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}
#endif

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static void app_usb_port__usb_enable_handler(bool status)
{
    APP_LOGI(thisMOD,"app_usb_port__usb_enable_handler, status = %d, plug_in = %d, app_usb_enable = %d", status, app_usb_plug, app_usb_enable);
    bool plug_in_ = app_usb_port__get_vbus_ready();
    if(status)  //do enable
    {
        if(plug_in_)
        {
            app_usb_plug = APP_USB_PLUG_IN;
            if(!app_usb_enable)
            {
                app_usb_port_announce_usb_status(USB_STATUS_READY_TO_ENABLE);
                app_usb_port__start_timer(&check_configured_timer, USB_CHECKING_CONFIGURED_TIMEOUT);
            }
            else{
                APP_LOGI(thisMOD, "Careful that you have already enabled it once.");
            }
        }
    }
    else  //do disable
    {
        if(app_usb_enable)
        {
            app_usb_plug = (plug_in_ == APP_USB_PLUG_IN) ? APP_USB_PLUG_IN : APP_USB_PLUG_OUT;
            app_usb_port_announce_usb_status(USB_STATUS_READY_TO_DISABLE);
            uint8_t state = app_state_current_state();
            if(app_state_check(TYPE_IN_USB_STATES) || state == APP_STATE_INITIALIZED){
                app_usb_port__change_plugged_status(app_usb_plug);  // 0
            }
            else {
                APP_LOGI(thisMOD, "Do disable in other mode/ from charger");
                app_usb_port__announce_active_status();
            }
        }
        else{
            // assert(0 && "Dont do disable, plz enable usb first!");
            APP_LOGI(thisMOD, "Dont do disable, plz enable usb first!");
        }
    }
    return;
}

static void app_usb_port_timer_init()
{
    k_timer_init(&check_plugged_timer , app_usb_port__check_usb_port_status, NULL);
    k_timer_init(&check_configured_timer , app_usb_port__check_usb_configured_status, NULL);
}

static void app_usb_port_announce_usb_status(uint8_t status)
{
    struct evt_usb_status* event = create_evt_usb_status();
    if(event) {
        event->status = status;
        AF_EVT_SUBMIT(event);
    }
}

static void app_usb_port__announce_active_status()
{
    struct evt_active_status* active_evt = create_evt_active_status();
    if (active_evt)
    {
        active_evt->active = true;
        active_evt->type = USB_PLUG_WAKEUP;
        AF_EVT_SUBMIT(active_evt);
    }
}

static void app_usb_port_set_hid_flag()
{
    if(app_usb_plug == APP_USB_PLUG_OUT)
    {
        hid_common_clear_hid_exp_flag(FLAG_BIT_USB_PLUG_STATUS);
    }
    else
    {
        hid_common_set_hid_exp_flag(FLAG_BIT_USB_PLUG_STATUS);
    }
    APP_LOGI(thisMOD, "app_usb_port_set_hid_flag = %d", USB_PLUG_STATUS_CHECK(hid_common->hid.flags));
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
uint8_t app_usb_port_init(void)
{
    APP_LOGI(thisMOD, "app_usb_port_init start");
    app_usb_port_timer_init();

    hid_scenario_usb_callbacks_t app_usb_port_cbs = {
        .usb_cb        = app_usb_port__hid_usb_handler,
    };
    int ret = hid_scenario_usb_register_callbacks(&app_usb_port_cbs);
    if(ret){
        APP_LOGE(thisMOD, "hid_scenario_usb_register_callbacks fail");
    }

    bool app_usb_switch_in_other_mode = false;
    #if defined(CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH)
    uint8_t ss_type = SS_MODE_NONE;
    GET_SLIDE_SWITCH_MODE(&ss_type);
    if(ss_type == SS_MODE_BT || ss_type == SS_MODE_2_4G){
        app_usb_switch_in_other_mode = true;
    }
    #endif /* CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH */

    app_usb_plug = (app_usb_port__get_vbus_ready() == APP_USB_PLUG_IN) ? APP_USB_PLUG_IN : APP_USB_PLUG_OUT;
    app_usb_port_set_hid_flag();
    if(app_usb_plug)
    {
        APP_LOGI(thisMOD, "USB plugging when init.");
        if(!app_usb_switch_in_other_mode)
        {
            app_usb_enable = true;
            hid_scenario_usb_for_applaciton(HID_SCENARIO_APP_USB_ENABLE);
            init_configured_time = k_uptime_get_32();
        }
        else{
            APP_LOGI(thisMOD,"app_usb_port_init finish, wait for switch to usb position");
        }
        app_usb_port_announce_usb_status(USB_STATUS_PLUGGED_IN);
    }
    else{
        APP_LOGI(thisMOD, "app_usb_port_init finish, no USB plugged");
    }
    return app_usb_plug;
}

uint8_t app_usb_port__check_configured_in_init()
{
    #if defined(CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH)
    uint8_t ss_type = SS_MODE_NONE;
    GET_SLIDE_SWITCH_MODE(&ss_type);
    if(ss_type == SS_MODE_BT || ss_type == SS_MODE_2_4G){
        APP_LOGI(thisMOD, "Still need to wait for ss, plug = %d, enable = %d", app_usb_plug, app_usb_enable);
        return 0;
    }
    #endif /* CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH */
    if(app_usb_plug == APP_USB_CONFIGURED)
    {
        APP_LOGI(thisMOD, "USB already configured......");
    }
    else if(app_usb_plug == APP_USB_PLUG_IN)
    {
        APP_LOGI(thisMOD, "Waiting for USB configured......");
        uint32_t curr_time = k_uptime_get_32();

        const uint8_t sleep_ms = 5;
        uint16_t elapsed_time_ms = 0;
        uint16_t target_time = USB_CHECKING_CONFIGURED_TIMEOUT;

        while((elapsed_time_ms <= target_time) && (app_usb_plug != APP_USB_CONFIGURED))
        {
            k_sleep(K_MSEC(sleep_ms));
            elapsed_time_ms += sleep_ms;
        }
        curr_time = k_uptime_get_32();
        uint16_t delta_time = CALCULATE_DELTA_TIME(curr_time, init_configured_time);

        if(elapsed_time_ms > target_time){
            APP_LOGI(thisMOD, "Check configured in init finish, use %d ms to ckech plug in charger.", delta_time);
        }
    }

    return app_usb_plug;
}

uint8_t app_usb_port__get_usb_plug_status()
{
    APP_LOGI(thisMOD, "app_usb_port__get_usb_plug_status, plug_in = %d, enable = %d", app_usb_plug, app_usb_enable);
    return app_usb_plug;
}

void app_usb_port__change_plugged_status(uint8_t status)
{
    APP_LOGI(thisMOD,"app_usb_change_status, status = %d", status);

    switch(status)
    {
        case APP_USB_CONFIGURED:
        {
            if(app_battery__get_battery_power()){
                APP_LOGI(thisMOD,"Send APP_USB_CONFIGURED evt to open wired mode");
                app_usb_port_announce_usb_status(USB_STATUS_CONFIGURED);
            }
            else{
                APP_LOGI(thisMOD,"You need charge your device first before connect to PC");
            }
            break;
        }
        case APP_USB_PLUG_OUT:
        {
            app_usb_port_announce_usb_status(USB_STATUS_DISCONNECT);
            break;
        }
        default:{
            break;
        }
    }
    return;
}
#endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE */

bool app_usb_port__get_vbus_ready(void)
{
#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
    return hid_scenario_usb_get_vbus();
#else
    return 0;
#endif
}

/*============================Application Framework============================*/
#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_usb_status, app_usb_port__evt_usb_status);

#if defined(CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH)
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_slide_switch_status, app_usb_port__evt_slide_switch_status);
#endif /* CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH */
#endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE */
