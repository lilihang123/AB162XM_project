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
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/bluetooth/hci_types.h>
#include <zephyr/bluetooth/hci.h>

#if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE)
#include "app_state_mouse.h"
#include "app_wheel.h"
#include "app_motion_sensor.h"
#elif defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
#include "app_state_keyboard.h"
#elif defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
#include "app_state_game_controller.h"
#include "hid_game_controller.h"
#endif /* CONFIG_AIR_PRODUCT_TYPE_MOUSE */

#include "app_state.h"
#include "app_button.h"

#include "app_battery.h"
#include "app_power_manager.h"
#include "app_usb_port.h"
#include "app_links.h"
#include "app_scenario.h"
#include "app_links.h"
#include "app_led.h"
#include "app_rgb.h"
#include "app_race_cmd.h"
#include "app_slide_switch.h"
#if defined(CONFIG_AIR_DUAL_MODE_SLIDE_SWITCH)
#include "app_slide_switch_dual.h"
#endif
#include "app_user_profile.h"
#include "app_gpio.h"
#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#include "app_key_remap.h"
#endif
#include "app_hogp.h"
#include "app_labtest.h"
#include "app_usb_report.h"
#include "app_pin_config_parser.h"
#include "app_fota_status.h"

#include <zephyr/settings/settings.h>
#include <zephyr/bluetooth/bluetooth.h>

#include "hid_scenario_service.h"
#include "hid_common.h"
#include "app_la_debug.h"
#include "nvkey.h"
#include "hal_wdt.h"
#include "hal_clock_internal.h"

#define thisMODULE state_mgr
#define thisMOD    "state_mgr"
LOG_MODULE_REGISTER(thisMODULE);
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
static void app_state_announce_new_state(uint32_t new_app_state);
static void app_state_announce_connect_req(uint32_t conn_type, uint32_t next_state, uint32_t reason);

static void app_state_change(uint32_t new_state, uint32_t reason);
static void app_state__activate_bt(uint32_t conn_type);

static void app_state__inactivate_bt();
static void app_state_set_hid_flag();

#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
static void app_state__do_wired_mode_disconnect();
static void app_state__do_wired_mode_connect();
#endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE */

static void app_state_terminate_wireless_connection(uint32_t next_action);
/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
#define ACTION_NONE                         0
#define ACTION_SWITCH_TO_USB_MODE           1
#define ACTION_SWITCH_TO_LAST_LINK          2
#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
#define ACTION_SWITCH_TO_LAST_BT_LINK       3
#endif
#define ACTION_SWITCH_TO_LAST_GAMING_LINK   4

#define ACTION_SWITCH_TO_PAIRING_MODE       5
#define ACTION_SWITCH_TO_NEXT_LINK          6
#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
#define ACTION_SWITCH_TO_NEXT_BT_LINK       7
#endif
#define ACTION_SWITCH_TO_NEXT_GAMING_LINK   8
#define ACTION_SWITCH_TO_RELAY_MODE         9
#define ACTION_SWITCH_TO_ENTER_STANDBY      10
#define POWER_SAVING_SKIP_THIS_STATE        0xFFFF

uint8_t app_state;
uint8_t app_processing_state = APP_STATE_NONE;
uint16_t app_RR;
uint8_t app_clk;
uint8_t app_state_in_processing_action = ACTION_NONE;

uint16_t app_state__USB_rr;
uint16_t app_state__2_4G_rr;

typedef enum
{
    BT_STATUS_OFF,
    BT_STATUS_INITIALIZING,
    BT_STATUS_READY,
}T_BT_STATUS_E;

typedef struct
{
    uint8_t state;
    T_BT_STATUS_E bt_status;
}T_APP_STATE_CTRL_S;

typedef struct
{
    uint16_t active_timeout;
    uint16_t idle1_timeout;
    uint16_t idle2_timeout;
    uint16_t standby_timeout;
    uint16_t pairing_timeout_2_4G;
    uint16_t reconnect_timeout_2_4G;
    uint16_t pairing_timeout_BT;
    uint16_t reconnect_timeout_BT;
}T_POWER_SAVING_TIMEOUT_S;

T_APP_STATE_CTRL_S app_state_ctrl;
T_POWER_SAVING_TIMEOUT_S power_saving_timeout;

struct k_timer app_state_enter_idle_timer;
struct k_timer app_state_disconnect_req_timer;
struct k_timer app_state_deepsleep_timer;
struct k_timer app_state_pairing_timer;
struct k_timer app_state_reconnect_timer;
/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/
static void app_state_disconnect_req()
{
    APP_LOGI(thisMOD, "app_state_disconnect_req, app_state = %02X", app_state);
    switch (app_state)
    {
        case APP_STATE_BT_CONNECTED_ACTIVE:
        case APP_STATE_BT_CONNECTED_IDLE_1:
        case APP_STATE_BT_CONNECTED_IDLE_2:
        {
            app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_BT_DISCONNECTING, REASON_TIMEOUT);
            break;
        }
        case APP_STATE_2_4G_CONNECTED_ACTIVE:
        case APP_STATE_2_4G_CONNECTED_IDLE_1:
        case APP_STATE_2_4G_CONNECTED_IDLE_2:
        {
            app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_2_4G_DISCONNECTING, REASON_TIMEOUT);
            break;
        }
        default:{
            break;
        }
    }

    if (power_saving_timeout.standby_timeout)
    {
        APP_LOGI(thisMOD, "reset_deep_sleep_timer");
        k_timer_stop(&app_state_deepsleep_timer);
        k_timer_start(&app_state_deepsleep_timer, K_SECONDS(power_saving_timeout.standby_timeout), K_NO_WAIT);
    }
}

static void app_state_disconnect_force_release_req()
{
    struct evt_active_status* event = create_evt_active_status();
    if (event){
        event->active = true;
        event->type = DISCONNECT_REQ_WAKEUP;
        AF_EVT_SUBMIT(event);
    }
    hid_common_set_hid_exp_flag(FLAG_BIT_FORCE_RELEASE_KEY);
    app_state_in_processing_action = ACTION_SWITCH_TO_ENTER_STANDBY;
}

static void app_state_enter_idle2()
{
    APP_LOGI(thisMOD, "app_state_enter_idle2, app_state = %02X", app_state);

    if(!app_fota_status__get_fota_state())
    {
        if(power_saving_timeout.idle2_timeout == POWER_SAVING_SKIP_THIS_STATE)
        {
            APP_LOGI(thisMOD, "Skip idle 2 state, request to disconnect");
            #if !defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
            if(!app_button_is_key_pressed())
            {
                app_state_disconnect_req();
            }
            else
            #endif
            {
                app_state_disconnect_force_release_req();
            }
        }
        else
        {
            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
            if (app_links_read_link_type() == LINKT_TYPE_BT){
                app_state_announce_connect_req(CONN_REQ_IDLE_2, APP_STATE_BT_CONNECTED_ENTERING_IDLE_2, REASON_IDLE_2);
            }
            else
            #endif
            {
                app_state_announce_connect_req(CONN_REQ_IDLE_2, APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_2, REASON_IDLE_2);
            }
            if(power_saving_timeout.idle2_timeout){
                APP_LOGI(thisMOD, "power_saving_timeout.idle2_timeout = %d", power_saving_timeout.idle2_timeout);
                k_timer_stop(&app_state_disconnect_req_timer);
                k_timer_start(&app_state_disconnect_req_timer, K_SECONDS(power_saving_timeout.idle2_timeout), K_NO_WAIT);
            }
        }
    }
}

static void app_state_enter_idle1()
{
    if(power_saving_timeout.idle1_timeout == POWER_SAVING_SKIP_THIS_STATE)
    {
        app_state_enter_idle2();
    }
    else
    {
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        if (app_links_read_link_type() == LINKT_TYPE_BT){
            app_state_announce_connect_req(CONN_REQ_IDLE_1, APP_STATE_BT_CONNECTED_ENTERING_IDLE_1, REASON_IDLE);
        }
        else
        #endif
        {
            app_state_announce_connect_req(CONN_REQ_IDLE_1, APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1, REASON_IDLE);
        }
        if(power_saving_timeout.idle1_timeout){
            APP_LOGI(thisMOD, "power_saving_timeout.idle1_timeout = %d", power_saving_timeout.idle1_timeout);
            k_timer_stop(&app_state_enter_idle_timer);
            k_timer_start(&app_state_enter_idle_timer, K_SECONDS(power_saving_timeout.idle1_timeout), K_NO_WAIT);
        }
    }
}

static void app_state_enter_deepsleep(struct k_timer *timer_id)
{
    APP_LOGI(thisMOD, "app_state_enter_deepsleep");
}

static void app_state_disconnect_req_timeout(struct k_timer *timer_id)
{
    APP_LOGI(thisMOD, "app_state_disconnect_req_timeout");
    #if !defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
    if(!app_button_is_key_pressed())
    {
        app_state_disconnect_req();
    }
    else
    #endif
    {
        app_state_disconnect_force_release_req();
    }
}

static bool app_state_evt_force_key_release_success(const struct af_evt_header *evt_header)
{
    /* All key release successfully, when connected*/
    if(app_state_in_processing_action != ACTION_SWITCH_TO_ENTER_STANDBY)
    {
        APP_LOGI(thisMOD,"Disconnect req to repair");
        app_state_terminate_wireless_connection(ACTION_SWITCH_TO_PAIRING_MODE);
    }
    return AF_TRAVERSE_NEXT;
}

void app_state_stop_state_flow_timers()
{
    k_timer_stop(&app_state_pairing_timer);
    k_timer_stop(&app_state_reconnect_timer);
    k_timer_stop(&app_state_enter_idle_timer);
    k_timer_stop(&app_state_disconnect_req_timer);
}

void app_state_standby_req()
{
    APP_LOGI(thisMOD, "app_state_standby_req, app_state = %02X", app_state);
    app_state_stop_state_flow_timers();

    switch (app_state)
    {
        case APP_STATE_BT_PAIRING:
        case APP_STATE_2_4G_PAIRING:
        case APP_STATE_BT_RECONNECT:
        case APP_STATE_2_4G_RECONNECT:
        case APP_STATE_2_4G_QUICK_CONNECT:
        {
            app_state_announce_connect_req(CONN_REQ_CANCEL_CONN, APP_STATE_CONNECT_CANCEL, REASON_PAIRING_TIMEOUT);
            break;
        }

        case APP_STATE_BT_CONNECTED:
        case APP_STATE_BT_CONNECTED_ACTIVE:
        case APP_STATE_BT_CONNECTED_IDLE_1:
        case APP_STATE_BT_CONNECTED_IDLE_2:
        case APP_STATE_BT_CONNECTED_IDLE_3:
        case APP_STATE_BT_CONNECTED_ENTERING_ACTIVE:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_1:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_2:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_3:
        {
            app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_BT_DISCONNECTING, REASON_TIMEOUT);
            break;
        }

        case APP_STATE_2_4G_CONNECTED:
        case APP_STATE_2_4G_CONNECTED_ACTIVE:
        case APP_STATE_2_4G_CONNECTED_IDLE_1:
        case APP_STATE_2_4G_CONNECTED_IDLE_2:
        case APP_STATE_2_4G_CONNECTED_IDLE_3:
        case APP_STATE_2_4G_CONNECTED_ENTERING_ACTIVE:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_2:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_3:
        {
            app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_2_4G_DISCONNECTING, REASON_TIMEOUT);
            break;
        }
        default:{
            break;
        }
    }
}

static void app_state_enter_idle2_timeout(struct k_timer *timer_id)
{
    APP_LOGI(thisMOD, "app_state_enter_idle2_timeout");
    app_state_enter_idle2();
}

static void app_state_pairing_timeout(struct k_timer *timer_id)
{
    if(timer_id == &app_state_reconnect_timer){
        APP_LOGI(thisMOD,"Reconnect timeout, app_state_in_processing_action = %d", app_state_in_processing_action);
    }
    else{
        APP_LOGI(thisMOD,"Pairing timeout, app_state_in_processing_action = %d", app_state_in_processing_action);
    }

    app_state_in_processing_action = ACTION_NONE;

    #if defined(CONFIG_AIR_CHARGE_DONT_ENTER_SLEEP)
    if(app_battery__check_bat_charge_and_power_on())
    {
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        if (app_links_read_link_type() == LINKT_TYPE_BT){
            k_timer_start(&app_state_reconnect_timer, K_SECONDS(power_saving_timeout.reconnect_timeout_BT), K_NO_WAIT);
            APP_LOGI(thisMOD,"k_timer_start app_state_reconnect_timer = %d", power_saving_timeout.reconnect_timeout_BT);
        }
        else
        #endif
        {
            k_timer_start(&app_state_reconnect_timer, K_SECONDS(power_saving_timeout.reconnect_timeout_2_4G), K_NO_WAIT);
            APP_LOGI(thisMOD,"k_timer_start app_state_reconnect_timer = %d", power_saving_timeout.reconnect_timeout_2_4G);
        }
    }
    else
    #endif
    {
        /* Close to stop adv*/
        app_state_announce_connect_req(CONN_REQ_CANCEL_CONN, APP_STATE_CONNECT_CANCEL, REASON_PAIRING_TIMEOUT);
    }
}

static bool app_state_in_processing_action_handler()
{
    APP_LOGI(thisMOD,"app_state_in_processing_action = %d", app_state_in_processing_action);

    switch(app_state_in_processing_action)
    {
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
        case ACTION_SWITCH_TO_USB_MODE:
        {
            app_state_announce_connect_req(CONN_REQ_CONN_USB, APP_STATE_CONNECT_PREPARING, REASON_CONNECT_START);
        }
        break;
        #endif /* _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_ */

        case ACTION_SWITCH_TO_LAST_LINK:
        {
            app_state__activate_bt(CONN_REQ_CONN_LAST_LINK);
        }
        break;

        case ACTION_SWITCH_TO_PAIRING_MODE:
        {
            app_state__activate_bt(CONN_REQ_CONN_NEW);
        }
        break;

        case ACTION_SWITCH_TO_NEXT_LINK:
        {
            app_state__activate_bt(CONN_REQ_CONN_LAST_LINK);
        }
        break;

        case ACTION_SWITCH_TO_LAST_GAMING_LINK:
        {
            app_state__activate_bt(CONN_REQ_CONN_LAST_GAMING_LINK);
        }
        break;

        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        case ACTION_SWITCH_TO_LAST_BT_LINK:
        {
            app_state__activate_bt(CONN_REQ_CONN_LAST_BT_LINK);
        }
        break;
        #endif /* _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE_ */

        case ACTION_SWITCH_TO_RELAY_MODE:
        {
            app_state_change(APP_STATE_TEST, REASON_ENTER_LABTEST);
        }
        default: {
            return 1;
        }
    }

    app_state_in_processing_action = ACTION_NONE;
    return 0;
}

static void app_state_disconnected_handle(uint32_t reason)
{
    k_timer_stop(&app_state_pairing_timer);
    k_timer_stop(&app_state_reconnect_timer);
    k_timer_stop(&app_state_enter_idle_timer);
    k_timer_stop(&app_state_disconnect_req_timer);
    APP_LOGI(thisMOD,"k_timer_stop");

    APP_LOGI(thisMOD,"app_state_disconnected_handle, app_state = 0x%02X, reason = 0x%02X", app_state, reason);

    uint32_t current_app_state = app_state; // keep a backup first in case it is changed by app_state_change
    app_state_change(APP_STATE_DISCONNECTED, reason);

    if (app_state_in_processing_action_handler() == 0){
        APP_LOGI(thisMOD,"return at line %d", __LINE__);
        return;
    }

    switch(current_app_state)
    {
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        case APP_STATE_BT_PAIRING:
        #endif
        case APP_STATE_2_4G_PAIRING:
        case APP_STATE_CONNECT_CANCEL:
        {
            /*Pairing timeout. Do nothing*/
            app_state__inactivate_bt();
            app_state_change(APP_STATE_STANDBY, reason);
        }
        break;

        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        case APP_STATE_BT_RECONNECT:
        #endif
        case APP_STATE_2_4G_RECONNECT:
        {
            if ((reason == BT_HCI_ERR_LOCALHOST_TERM_CONN)
            #ifndef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
                || (reason == BT_HCI_ERR_UNSPECIFIED)
            #endif
                )
            {
                app_state__inactivate_bt();
                app_state_change(APP_STATE_STANDBY, reason);
            }
            #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
            else if (reason == BT_HCI_ERR_UNSPECIFIED){
                app_state__activate_bt(CONN_REQ_RESUME_WAIT);
            }
            #endif
            else {
                app_state__activate_bt(CONN_REQ_CONN_LAST_LINK);
            }
        }
        break;

        case APP_STATE_2_4G_QUICK_CONNECT:
        {

        }
        break;

        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
        case APP_STATE_USB_CONNECTED:
        {
            uint8_t usb_plugged_status = app_usb_port__get_usb_plug_status();
            #if defined (CONFIG_AIR_USB_PLUG_AND_PLAY)
            if(usb_plugged_status == APP_USB_CONFIGURED){
                app_state__do_wired_mode_connect();
            }
            else
            #endif /* CONFIG_AIR_USB_PLUG_AND_PLAY */
            {
                uint8_t ss_type = SS_MODE_NONE;
                GET_SLIDE_SWITCH_MODE(&ss_type);
                if(usb_plugged_status && ss_type == SS_MODE_OFF)
                {
                    app_state__do_wired_mode_connect();
                }
                else {
                    app_state__activate_bt(CONN_REQ_CONN_LAST_LINK);
                }
            }
            break;
        }

        case APP_STATE_USB_ACTIVE:
        {

        }
        break;

        case APP_STATE_USB_SUSPEND:
        {

        }
        break;

        case APP_STATE_USB_ENTERING_ACTIVE:
        {
            app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_USB_DISCONNECTING, REASON_DISCONNECT);
            app_state_in_processing_action = ACTION_SWITCH_TO_LAST_LINK;
            break;
        }
        case APP_STATE_USB_DISCONNECTING:
        {
            bool power_ok = app_battery__get_battery_power();
            if(!power_ok)
            {
                APP_LOGI(thisMOD,"No battery power, wired mode disconnection");
                app_state_change(APP_STATE_STANDBY, REASON_LOW_BATTERY);
            }
            #if defined (CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF)
            else if(app_button_get_power_off_status()){
                app_state_change(APP_STATE_STANDBY, reason);
            }
            #endif /* CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF */
            else{
                app_state__activate_bt(CONN_REQ_CONN_LAST_LINK);
            }
            break;
        }
        #endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE */

        //case APP_STATE_USB_SWITCHING:
        //case APP_STATE_USB_SWITCHING_ABORT:
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        case APP_STATE_BT_DISCONNECTING:
        {
            bool power_ok = app_battery__get_battery_power();
            if(!power_ok)
            {
                APP_LOGI(thisMOD,"No battery power, bt mode disconnection");
                app_state__inactivate_bt();
                app_state_change(APP_STATE_STANDBY, REASON_LOW_BATTERY);
                break;
            }
            // if power_ok, continue with the code
        }
        case APP_STATE_BT_CONNECTED:
        case APP_STATE_BT_CONNECTED_ACTIVE:
        case APP_STATE_BT_CONNECTED_IDLE_1:
        case APP_STATE_BT_CONNECTED_IDLE_2:
        case APP_STATE_BT_CONNECTED_IDLE_3:
        case APP_STATE_BT_CONNECTED_ENTERING_ACTIVE:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_1:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_2:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_3:
        {
            if ((reason >= BT_HCI_ERR_REMOTE_USER_TERM_CONN)
                && (reason <= BT_HCI_ERR_LOCALHOST_TERM_CONN))
            {
                // Normal disconnection. Do nothing
                APP_LOGI(thisMOD,"Normal disconnection");

                app_state__inactivate_bt();
                app_state_change(APP_STATE_STANDBY, reason);
            }
            else
            {
                APP_LOGI(thisMOD,"Abnormal disconnection, need to reconnect");
                app_state__activate_bt(CONN_REQ_CONN_LAST_LINK);
            }
        }
        break;
        #endif

        case APP_STATE_2_4G_DISCONNECTING:
        {
            bool power_ok = app_battery__get_battery_power();
            if(!power_ok)
            {
                APP_LOGI(thisMOD,"No battery power, 2.4G mode disconnection");
                app_state__inactivate_bt();
                app_state_change(APP_STATE_STANDBY, REASON_LOW_BATTERY);
                break;
            }
            // if power_ok, continue with the code
        }
        case APP_STATE_2_4G_CONNECTED:
        case APP_STATE_2_4G_CONNECTED_ACTIVE:
        case APP_STATE_2_4G_CONNECTED_IDLE_1:
        case APP_STATE_2_4G_CONNECTED_IDLE_2:
        case APP_STATE_2_4G_CONNECTED_IDLE_3:
        case APP_STATE_2_4G_CONNECTED_ENTERING_ACTIVE:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_2:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_3:
        {
            if ((reason == BT_HCI_ERR_LOCALHOST_TERM_CONN)
            #ifndef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
                || (reason == BT_HCI_ERR_UNSPECIFIED)
            #endif
                )
            {
                app_state__inactivate_bt();
                app_state_change(APP_STATE_STANDBY, reason);
            }
            #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
            else if (reason == BT_HCI_ERR_UNSPECIFIED){
                app_state__activate_bt(CONN_REQ_RESUME_WAIT);
            }
            #endif
            else {
                app_state__activate_bt(CONN_REQ_CONN_LAST_LINK);
            }
        }
        break;

        default:
            break;
    }
}

/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
static bool app_state__evt_module_init(const struct af_evt_header *evt_header)
{
    APP_LOGI(thisMOD,"app_state__evt_module_init");
    if(app_labtest_get_type()){
        return AF_TRAVERSE_TERMINATED;
    }
    uint8_t usb_plugged_status = app_usb_port__get_vbus_ready();
    uint8_t power_ok = app_battery__get_battery_power();
    uint8_t ss_type = SS_MODE_NONE;
    GET_SLIDE_SWITCH_MODE(&ss_type);
#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
    usb_plugged_status = app_usb_port__check_configured_in_init();
#endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/

    APP_LOGI(thisMOD,"usb_plugged_status = %d, battery = %d, ss_type = %d", usb_plugged_status, power_ok, ss_type);

    if (usb_plugged_status == APP_USB_PLUG_OUT && power_ok == false){
        app_state__activate_bt(CONN_REQ_NONE);  //controller init
        app_state_change(APP_STATE_STANDBY, REASON_LOW_BATTERY);
    }
    #if defined (CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF)
    else if((usb_plugged_status < APP_USB_CONFIGURED) && app_button_get_power_off_status())
    {
        app_state__activate_bt(CONN_REQ_NONE);  //controller init
        app_state_change(APP_STATE_STANDBY, REASON_WAIT_FOR_TRIGGER);
    }
    #endif /* CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF */
    #if defined (CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH) || defined (CONFIG_AIR_DUAL_MODE_SLIDE_SWITCH)
    else if(ss_type == SS_MODE_OFF && usb_plugged_status == APP_USB_PLUG_IN)
    {
        app_state__activate_bt(CONN_REQ_NONE);  //controller init
        app_state_change(APP_STATE_STANDBY, REASON_SLIDE_SWITCH_IN_OFF);
    }
    #endif /* CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH || CONFIG_AIR_DUAL_MODE_SLIDE_SWITCH */
    else
    {
        app_power_mgr_exit_low_power_mode();
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
        if(usb_plugged_status == APP_USB_CONFIGURED){
            app_state__do_wired_mode_connect();
        }
        else
        #endif
        {
            app_state__activate_bt(CONN_REQ_CONN_LAST_LINK);
        }
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_state_evt_active_status(const struct af_evt_header *evt_header)
{
    struct evt_active_status* event = (struct evt_active_status*)evt_header;
    APP_LOGI(thisMOD,"app_state_evt_active_status, app_state = %d, active = %d, type = %d", app_state, event->active, event->type);

    switch(app_state) {
        case APP_STATE_STANDBY:
        {
            bool power_ok = app_battery__get_battery_power();
            if (event->active && power_ok)
            {
                if (app_processing_state != APP_STATE_STANDBY)
                {
                    switch(event->type)
                    {
                        #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
                        case MOTION_SENSOR_WAKEUP:
                        {
                            APP_LOGI(thisMOD,"Activated by motion sensor");
                            app_state__activate_bt(CONN_REQ_CONN_LAST_LINK);
                            break;
                        }
                        #endif /* defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER) */
                        #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE)
                        case WHEEL_WAKEUP:
                        {
                            APP_LOGI(thisMOD,"Activated by wheel");
                            app_state__activate_bt(CONN_REQ_CONN_LAST_LINK);
                            break;
                        }
                        #endif /* CONFIG_AIR_PRODUCT_TYPE_MOUSE */
                        case KEY_WAKEUP:
                        {
                            APP_LOGI(thisMOD,"Activated by key");
                            app_state__activate_bt(CONN_REQ_CONN_LAST_LINK);
                            break;
                        }
                        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
                        case USB_PLUG_WAKEUP:
                        {
                            APP_LOGI(thisMOD,"Activated by USB plug");
                            app_state__activate_bt(CONN_REQ_CONN_LAST_LINK);
                            break;
                        }
                        #endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/
                        #if defined (CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH) || defined (CONFIG_AIR_DUAL_MODE_SLIDE_SWITCH)
                        case SLIDE_SWITCH_WAKEUP:
                        {
                            APP_LOGI(thisMOD,"Activated by slide switch");
                            break;
                        }
                        #endif
                        default:{
                            break;
                        }
                    }
                    k_timer_stop(&app_state_deepsleep_timer);
                    app_processing_state = APP_STATE_STANDBY;
                }
                else{
                    APP_LOGI(thisMOD,"Conn last link is being processed, app_processing_state = %x", app_processing_state);
                }
            }
        }
        break;

        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        case APP_STATE_BT_CONNECTED_ACTIVE:
        {
            #if defined(CONFIG_AIR_CHARGE_DONT_ENTER_SLEEP)
            uint8_t charge = app_battery__get_bat_charge_status();
            if (event->active == false && !charge)
            #else
            if (event->active == false)
            #endif
            {
                app_state_enter_idle1();
            }
            else if(app_state_in_processing_action == ACTION_SWITCH_TO_ENTER_STANDBY)
            {
                /* when next action is enter to standby and state is active, disconnect directly */
                app_state_disconnect_req();
            }
        }
        break;

        case APP_STATE_BT_CONNECTED_IDLE_1:
        case APP_STATE_BT_CONNECTED_IDLE_2:
        case APP_STATE_BT_CONNECTED_IDLE_3:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_1:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_2:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_3:
        {
            if (event->active){
                app_state_announce_connect_req(CONN_REQ_ACTIVE, APP_STATE_BT_CONNECTED_ENTERING_ACTIVE, REASON_ACTIVE);
                //app_state_change(APP_STATE_BT_CONNECTED_ACTIVE, REASON_ACTIVE);
            }
            k_timer_stop(&app_state_enter_idle_timer);
            k_timer_stop(&app_state_disconnect_req_timer);
        }
        break;
        #endif

        case APP_STATE_2_4G_CONNECTED_ACTIVE:
        {
            #if defined(CONFIG_AIR_CHARGE_DONT_ENTER_SLEEP)
            uint8_t charge = app_battery__get_bat_charge_status();
            if (event->active == false && !charge)
            #else
            if (event->active == false)
            #endif
            {
                app_state_enter_idle1();
            }
            else if(app_state_in_processing_action == ACTION_SWITCH_TO_ENTER_STANDBY)
            {
                /* When next action is enter to standby and state is active, disconnect directly */
                app_state_disconnect_req();
            }
        }
        break;

        case APP_STATE_2_4G_CONNECTED_IDLE_1:
        case APP_STATE_2_4G_CONNECTED_IDLE_2:
        case APP_STATE_2_4G_CONNECTED_IDLE_3:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_2:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_3:
        {
            if (event->active){
                app_state_announce_connect_req(CONN_REQ_ACTIVE, APP_STATE_2_4G_CONNECTED_ENTERING_ACTIVE, REASON_ACTIVE);
                //app_state_change(APP_STATE_2_4G_CONNECTED_ACTIVE, REASON_ACTIVE);
            }
            k_timer_stop(&app_state_enter_idle_timer);
            k_timer_stop(&app_state_disconnect_req_timer);
        }
        break;
        #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
        case APP_STATE_2_4G_RECONNECT_RESUME_WAIT:
        {
            if (event->active){
                app_state_in_processing_action = ACTION_SWITCH_TO_LAST_LINK;
                app_state_announce_connect_req(CONN_REQ_CANCEL_CONN, APP_STATE_CONNECT_CANCEL, REASON_2_4G_RECONNECT_RESUME_ACTIVE);
            }
            break;
        }
        #endif
        case APP_STATE_USB_SUSPEND:
        // case APP_STATE_USB_ACTIVE:
        {
            if (event->active){
                APP_LOGI(thisMOD,"app_state_evt_active_status, USB ACTIVE!");
                app_state_announce_connect_req(CONN_REQ_ACTIVE_USB, APP_STATE_USB_ENTERING_ACTIVE, REASON_ACTIVE);
            }
        }
        break;

        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_state_evt_scenario_status(const struct af_evt_header *evt_header)
{
    struct evt_scenario_status* event = (struct evt_scenario_status*)evt_header;
    APP_LOGI(thisMOD,"evt_scenario_status = 0x%02X, reason = 0x%02X, app_state = %02X"
        , event->status
        , event->reason
        , app_state
        );

    switch(event->status)
    {
        case MODE_OPEN_CONNECTED:
        {
            APP_LOGI(thisMOD,"MODE_OPEN_CONNECTED");
            k_timer_stop(&app_state_pairing_timer);
            k_timer_stop(&app_state_reconnect_timer);
            APP_LOGI(thisMOD,"k_timer_stop app_state_reconnect_timer");

            if(app_state == APP_STATE_CONNECT_CANCEL) {
                #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
                if (app_scenario_get_current_device_type() == HID_SCENARIO_BT_MODE){
                    app_state_change(APP_STATE_BT_CONNECTED, REASON_CONNECTED);
                    app_state_announce_connect_req(CONN_REQ_DISC,  APP_STATE_BT_DISCONNECTING, REASON_DISCONNECT);
                }
                else if (app_scenario_get_current_device_type() == HID_SCENARIO_GAMING_MODE)
                #endif
                {
                    app_state_change(APP_STATE_2_4G_CONNECTED, REASON_CONNECTED);
                    app_state_announce_connect_req(CONN_REQ_DISC,  APP_STATE_2_4G_DISCONNECTING, REASON_DISCONNECT);
                }
                APP_LOGI(thisMOD,"Connected when cancel connect, need to disconnect");
            }
            else {
                app_state_in_processing_action = ACTION_NONE;
                #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
                if (app_scenario_get_current_device_type() == HID_SCENARIO_BT_MODE){
                    app_state_change(APP_STATE_BT_CONNECTED, REASON_CONNECTED);
                }
                else if (app_scenario_get_current_device_type() == HID_SCENARIO_GAMING_MODE)
                #endif
                {
                    app_state_change(APP_STATE_2_4G_CONNECTED, REASON_CONNECTED);
                }
            }
        }
        break;

        case MODE_OPEN_USB_CONNECTED:
        {
            APP_LOGI(thisMOD,"MODE_OPEN_USB_CONNECTED");
            app_state__inactivate_bt();
            #if 0
            APP_LOGI(thisMOD,"[SWLA]label_usb_connect STOP");
            HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_usb_connect, SWLA_DIRECTION_STOP);
            #endif
            if(app_state != APP_STATE_USB_CONNECTED){
            app_state_change(APP_STATE_USB_CONNECTED, REASON_CONNECTED);
            }
            #if 0
            APP_LOGI(thisMOD,"[SWLA]label_usb_start START");
            HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_usb_start, SWLA_DIRECTION_START);
            #endif
        }
        break;

        case MODE_OPEN_SPECIFIED:
        {
            APP_LOGI(thisMOD,"MODE_OPEN_SPECIFIED");
            k_timer_stop(&app_state_reconnect_timer);
            APP_LOGI(thisMOD,"k_timer_stop app_state_reconnect_timer");
            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
            if (app_links_read_link_type() == LINKT_TYPE_BT){
                app_state_change(APP_STATE_BT_RECONNECT, REASON_BT_RECONNECT);
                k_timer_start(&app_state_reconnect_timer, K_SECONDS(power_saving_timeout.reconnect_timeout_BT), K_NO_WAIT);
            }
            else
            #endif
            {
                app_state_change(APP_STATE_2_4G_RECONNECT, REASON_2_4G_RECONNECT);
                k_timer_start(&app_state_reconnect_timer, K_SECONDS(power_saving_timeout.reconnect_timeout_2_4G), K_NO_WAIT);
                APP_LOGI(thisMOD,"k_timer_start app_state_reconnect_timer = %d", power_saving_timeout.reconnect_timeout_2_4G);
            }
            #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
            //case for usb configured when 0A
            uint8_t ss_type = SS_MODE_NONE;
            GET_SLIDE_SWITCH_MODE(&ss_type);
            if((ss_type == SS_MODE_OFF || ss_type == SS_MODE_NONE) && (app_usb_port__get_usb_plug_status() == APP_USB_CONFIGURED))
            {
                app_state__do_wired_mode_connect();
            }
            #endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE */
        }
        break;
        #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
        case MODE_OPEN_SPECIFIED_RESUME:
        {
            if(event->reason == REASON_RECONNECTION_RESUME){
                app_state_change(APP_STATE_2_4G_RECONNECT_RESUME_WAIT, REASON_2_4G_RECONNECT_RESUME_WAIT);
            }
        }
        break;
        #endif
        case MODE_OPEN_UNSPECIFIED:
        {
            APP_LOGI(thisMOD,"MODE_OPEN_UNSPECIFIED");
            k_timer_stop(&app_state_pairing_timer);
            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
            if (app_links_read_link_type() == LINKT_TYPE_BT){
                app_state_change(APP_STATE_BT_PAIRING, REASON_PAIR);
                k_timer_start(&app_state_pairing_timer, K_SECONDS(power_saving_timeout.pairing_timeout_BT), K_NO_WAIT);
            }
            else
            #endif
            {
                app_state_change(APP_STATE_2_4G_PAIRING, REASON_PAIR);
                k_timer_start(&app_state_pairing_timer, K_SECONDS(power_saving_timeout.pairing_timeout_2_4G), K_NO_WAIT);
                APP_LOGI(thisMOD,"k_timer_start app_state_pairing_timer = %d", power_saving_timeout.pairing_timeout_2_4G);
            }
            #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
            //case for usb configured when 0A
            uint8_t ss_type = SS_MODE_NONE;
            GET_SLIDE_SWITCH_MODE(&ss_type);
            if((ss_type == SS_MODE_OFF || ss_type == SS_MODE_NONE) && (app_usb_port__get_usb_plug_status() == APP_USB_CONFIGURED))
            {
                app_state__do_wired_mode_connect();
            }
            #endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE */
        }
        break;

        case MODE_STARTED:
        {
            APP_LOGI(thisMOD,"MODE_STARTED");
            if(IS_WIRELESS_CONNECTED_STATE(app_state)){
                if (app_links_read_link_type() == LINKT_TYPE_BT){
                    app_state_change(APP_STATE_BT_CONNECTED_ACTIVE, REASON_CONNECTED);
                }
                else {
                    app_state_change(APP_STATE_2_4G_CONNECTED_ACTIVE, REASON_CONNECTED);
                }

                if(app_state_in_processing_action == ACTION_SWITCH_TO_ENTER_STANDBY)
                {
                    app_state_disconnect_req();
                }
            }
        }
        break;

        case MODE_STOPPED:
        {
            APP_LOGI(thisMOD,"MODE_STOPPED, app_state = %d", app_state);
            switch(app_state)
            {
                case APP_STATE_BT_CONNECTED_ENTERING_IDLE_1:
                {
                    app_state_change(APP_STATE_BT_CONNECTED_IDLE_1, REASON_IDLE);
                }
                break;

                case APP_STATE_BT_CONNECTED_ENTERING_IDLE_2:
                {
                    app_state_change(APP_STATE_BT_CONNECTED_IDLE_2, REASON_IDLE);
                }
                break;

                case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1:
                {
                    app_state_change(APP_STATE_2_4G_CONNECTED_IDLE_1, REASON_IDLE);
                }
                break;

                case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_2:
                {
                    app_state_change(APP_STATE_2_4G_CONNECTED_IDLE_2, REASON_IDLE_2);
                }
                break;

                case APP_STATE_USB_ENTERING_ACTIVE:
                {
                    app_state_change(APP_STATE_USB_SUSPEND, REASON_USB_SUSPEND);
                    break;
                }
                default:{
                    break;
                }
            }
        }
        break;

        case MODE_USB_RESUME:
        {
            APP_LOGI(thisMOD,"MODE_USB_RESUME, app_state = %d", app_state);
            if(app_state_check(TYPE_IN_BT_STATES) || app_state_check(TYPE_IN_GAMING_STATES)){
                APP_LOGI(thisMOD,"Receive device resume in BT/2.4G, wait USB configured!!!");
            }
            else if(app_state == APP_STATE_USB_SUSPEND){
                app_state_announce_connect_req(CONN_REQ_ACTIVE_USB, APP_STATE_USB_ENTERING_ACTIVE, REASON_ACTIVE);
            }
            else{
                APP_LOGI(thisMOD,"Receive device resume in state = %d", app_state);
            }
        }
        break;

        case MODE_USB_STARTED:
        {
            APP_LOGI(thisMOD,"MODE_USB_STARTED");
            if(app_state != APP_STATE_USB_ACTIVE)
            {
                app_state_change(APP_STATE_USB_ACTIVE, REASON_ACTIVE);
            }
            #if 0
            APP_LOGI(thisMOD,"[SWLA]label_usb_start STOP");
            HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_usb_start, SWLA_DIRECTION_STOP);
            #endif
        }
        break;

        case MODE_USB_STOPPED:
        {
            if(app_state_check(TYPE_IN_USB_STATES))
            {
                APP_LOGI(thisMOD,"MODE_USB_STOPPED");
                app_state_change(APP_STATE_USB_SUSPEND, REASON_USB_SUSPEND);
            }
            else{
                APP_LOGI(thisMOD,"MODE_USB_STOPPED, not in USB states!");
            }
        }
        break;

        case MODE_CLOSED:
        {
            #ifdef CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER
                /*temp solution for spi trigger, disable bt spi */
                game_controller_bt_hw_trigger_disable();
            #endif
            if((app_state == APP_STATE_CONNECT_PREPARING) && (event->reason == REASON_RECONNECTION_CREATE_FAIL))
            {
                k_timer_stop(&app_state_pairing_timer);
                k_timer_stop(&app_state_reconnect_timer);
                if(app_state_device_active()) {
                    app_state_change(APP_STATE_INITIALIZED, REASON_RECONNECT_FAIL);
                }
                else {
                    app_state_change(APP_STATE_STANDBY, REASON_RECONNECT_FAIL);
                }
                APP_LOGI(thisMOD,"MODE_CLOSED");
            }
            else {
                APP_LOGI(thisMOD,"MODE_CLOSED, do disconnect handle");
                app_state_disconnected_handle(event->reason);
            }
        }
        break;
    }

    return AF_TRAVERSE_NEXT;
}

static void app_state_terminate_wireless_connection(uint32_t next_action)
{
    if (app_state_check(TYPE_IN_BT_CONNECTED_STATES)){
        app_state_announce_connect_req(CONN_REQ_DISC,  APP_STATE_BT_DISCONNECTING, REASON_DISCONNECT);
    }
    else if (app_state_check(TYPE_IN_GAMING_CONNECTED_STATES)){
        app_state_announce_connect_req(CONN_REQ_DISC,  APP_STATE_2_4G_DISCONNECTING, REASON_DISCONNECT);
    }
    else if(app_state_check(TYPE_IN_BT_PAIRING_RECONNECT) || app_state_check(TYPE_IN_GAMING_PAIRING_RECONNECT)
            #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
            || app_state_check(TYEP_IN_GAMING_RESUME)
            #endif
    ){
        app_state_announce_connect_req(CONN_REQ_DISC,  APP_STATE_CONNECT_CANCEL, REASON_DISCONNECT);
    }

    if (next_action != ACTION_NONE){
        app_state_in_processing_action = next_action;
    }
}

static bool app_state_evt_pairing_request(const struct af_evt_header *evt_header)
{
    struct evt_pairing_request* event = (struct evt_pairing_request*)evt_header;
    APP_LOGI(thisMOD,"app_state_evt_pairing_request , type = %d, force_key_release_req = %d", event->type, event->force_key_release_req);

    if(event->force_key_release_req) {
        switch(event->type)
        {
            case PAIRING_REQ_RECOVERABLE:
            {
                switch(app_state)
                {
                    case APP_STATE_STANDBY:
                    {

                    }
                    break;

                    #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
                    case APP_STATE_BT_PAIRING:
                    case APP_STATE_BT_RECONNECT:
                    #endif
                    case APP_STATE_2_4G_PAIRING:
                    {
                        APP_LOGI(thisMOD,"Stop adv req to repair");
                        app_state_in_processing_action = ACTION_SWITCH_TO_PAIRING_MODE;
                        app_state_announce_connect_req(CONN_REQ_CANCEL_CONN, APP_STATE_CONNECT_CANCEL, REASON_PAIRING_TIMEOUT);
                    }
                    break;

                    case APP_STATE_2_4G_RECONNECT:
                    case APP_STATE_2_4G_QUICK_CONNECT:
                    {
                        APP_LOGI(thisMOD,"Stop gaming re-connect process");
                        app_state_in_processing_action = ACTION_SWITCH_TO_PAIRING_MODE;
                        app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_2_4G_DISCONNECTING, REASON_DISCONNECT);
                    }
                    break;

                    #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
                    case APP_STATE_BT_CONNECTED:
                    case APP_STATE_BT_CONNECTED_ACTIVE:
                    case APP_STATE_BT_CONNECTED_IDLE_1:
                    case APP_STATE_BT_CONNECTED_IDLE_2:
                    case APP_STATE_BT_CONNECTED_IDLE_3:
                    case APP_STATE_BT_CONNECTED_ENTERING_IDLE_1:
                    case APP_STATE_BT_CONNECTED_ENTERING_IDLE_2:
                    case APP_STATE_BT_CONNECTED_ENTERING_IDLE_3:
                    #endif
                    case APP_STATE_2_4G_CONNECTED:
                    case APP_STATE_2_4G_CONNECTED_ACTIVE:
                    case APP_STATE_2_4G_CONNECTED_IDLE_1:
                    case APP_STATE_2_4G_CONNECTED_IDLE_2:
                    case APP_STATE_2_4G_CONNECTED_IDLE_3:
                    case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1:
                    case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_2:
                    case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_3:
                    {
                        hid_common_set_hid_exp_flag(FLAG_BIT_FORCE_RELEASE_KEY);
                    }
                    break;

                    default:
                    break;
                }
            }
            break;

            default:{
                break;
            }
        }
    }
    else
    {
        /* All key release successfully, when connected*/
        APP_LOGI(thisMOD,"Disconnect req to repair");
        app_state_terminate_wireless_connection(ACTION_SWITCH_TO_PAIRING_MODE);
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_state_evt_app_state_change_req(const struct af_evt_header *evt_header)
{
    struct evt_app_state_change_req* event = (struct evt_app_state_change_req*)evt_header;
    APP_LOGI(thisMOD,"app_state_evt_app_state_change_req , state = %d, reason", event->app_state);

    switch(event->app_state)
    {
        case APP_STATE_STANDBY:
        {
            app_state_standby_req();
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_state_evt_link_change(const struct af_evt_header *evt_header)
{
    struct evt_link_change* event = (struct evt_link_change*)evt_header;
    APP_LOGI(thisMOD,"evt_link_change , target_mode = %d", event->type);

    #if defined (CONFIG_AIR_USB_PLUG_AND_PLAY)
    if(app_state_check(TYPE_IN_USB_STATES)){
        APP_LOGI(thisMOD,"evt_link_change is ignored due to CONFIG_AIR_USB_PLUG_AND_PLAY=y and USB plugged");
        return 0;
    }
    #endif /* _CONFIG_AIR_USB_PLUG_AND_PLAY_ */
    if(LINK_NUM == 0x01){
        APP_LOGI(thisMOD,"evt_link_change is ignored due to link num = 1");
        return 0;
    }

    switch(event->type)
    {
        case CHANGE_NEXT_LINK:
        {
            app_state__activate_bt(CONN_REQ_CONN_NEXT_LINK);
            app_state_in_processing_action = ACTION_SWITCH_TO_NEXT_LINK;
        }
        break;

        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        case CHANGE_NEXT_BT_LINK:
        {
            app_state__activate_bt(CONN_REQ_CONN_NEXT_BT_LINK);
            app_state_in_processing_action = ACTION_SWITCH_TO_NEXT_BT_LINK;
        }
        break;
        #endif

        case CHANGE_NEXT_GAMING_LINK:
        {
            app_state__activate_bt(CONN_REQ_CONN_NEXT_GAMING_LINK);
            app_state_in_processing_action = ACTION_SWITCH_TO_NEXT_GAMING_LINK;
        }
        break;
    }

    return AF_TRAVERSE_NEXT;
}

#if defined (CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH) || defined (CONFIG_AIR_DUAL_MODE_SLIDE_SWITCH)
static bool app_state__evt_slide_switch_status(const struct af_evt_header *evt_header)
{
    struct evt_slide_switch_status* event = (struct evt_slide_switch_status*)evt_header;
    APP_LOGI(thisMOD,"app_state__evt_slide_switch_status, position = %d", event->position);

    #if defined (CONFIG_AIR_USB_PLUG_AND_PLAY)
    if(app_state_check(TYPE_IN_USB_STATES)){
        APP_LOGI(thisMOD,"evt_slide_switch_status is ignored due to CONFIG_AIR_USB_PLUG_AND_PLAY=y and USB plugged");
        return 0;
    }
    #endif /* _CONFIG_AIR_USB_PLUG_AND_PLAY_ */

    switch(event->position)
    {
        case SLIDE_SWITCH_POS_OFF:
        {
            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
            if (!app_state_check(TYPE_IN_USB_STATES))
            {
                uint8_t plug_status = app_usb_port__get_usb_plug_status();
                if(plug_status) {
                    if(plug_status == APP_USB_CONFIGURED)
                    {
                        APP_LOGI(thisMOD,"SLIDE_SWITCH_POS_OFF");
                        if((app_state == APP_STATE_STANDBY)
                        #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
                        || (app_state == APP_STATE_2_4G_RECONNECT_RESUME_WAIT)
                        #endif
                        ){
                            app_state_announce_connect_req(CONN_REQ_CONN_USB, APP_STATE_CONNECT_PREPARING, REASON_CONNECT_START);
                        }
                        else{
                            app_state_terminate_wireless_connection(ACTION_SWITCH_TO_USB_MODE);
                        }
                    }
                    else  //plug in but not configured
                    {
                        APP_LOGI(thisMOD,"SLIDE_SWITCH_POS_OFF and plugged in charger or not configured yet!");
                        #if !defined(CONFIG_AIR_CHARGE_DONT_ENTER_SLEEP)
                        app_state_terminate_wireless_connection(ACTION_NONE);
                        #endif
                    }
                }
                else {
                   APP_LOGI(thisMOD,"SLIDE_SWITCH_POS_OFF and USB NOT plugged in PC!");
                }
            }
            #else
            APP_LOGI(thisMOD,"SLIDE_SWITCH_POS_OFF event is ignored due to CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE=n");
            #endif /* _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_ */
            break;
        }
        case SLIDE_SWITCH_POS_BT:
        {
            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
            if (!app_state_check(TYPE_IN_BT_STATES))
            {
                APP_LOGI(thisMOD,"SLIDE_SWITCH_POS_BT");
                if(app_state == APP_STATE_STANDBY){   //BT 2.4 pairing timeout
                    app_state__activate_bt(CONN_REQ_CONN_LAST_BT_LINK);
                }
                #if !defined (CONFIG_AIR_USB_PLUG_AND_PLAY)
                else if(app_state_check(TYPE_IN_USB_STATES))
                {
                    app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_USB_DISCONNECTING, REASON_DISCONNECT);
                    app_state_in_processing_action = ACTION_SWITCH_TO_LAST_BT_LINK;
                }
                #endif /* _CONFIG_AIR_USB_PLUG_AND_PLAY_ */
                else if(app_state_check(TYPE_IN_GAMING_CONNECTED_STATES))
                {
                    app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_2_4G_DISCONNECTING, REASON_DISCONNECT);
                    app_state_in_processing_action = ACTION_SWITCH_TO_LAST_BT_LINK;
                }
                else if(app_state_check(TYPE_IN_GAMING_PAIRING_RECONNECT)
                    #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
                    || app_state_check(TYEP_IN_GAMING_RESUME)
                    #endif
                )
                {
                    app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_CONNECT_CANCEL, REASON_DISCONNECT);
                    app_state_in_processing_action = ACTION_SWITCH_TO_LAST_BT_LINK;
                }
                #if defined (CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF)
                app_state_in_processing_action = ACTION_NONE;
                #endif
            }
            #else
            APP_LOGI(thisMOD,"SLIDE_SWITCH_POS_BT event is ignored due to CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE=n");
            #endif /* _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE_ */
            break;
        }
        case SLIDE_SWITCH_POS_GAMING:
        {
            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_GAMING_MODE)
            if (!app_state_check(TYPE_IN_GAMING_STATES))
            {
                APP_LOGI(thisMOD,"SLIDE_SWITCH_POS_GAMING");
                if(app_state == APP_STATE_STANDBY){
                    app_state__activate_bt(CONN_REQ_CONN_LAST_GAMING_LINK);
                }
                #if !defined (CONFIG_AIR_USB_PLUG_AND_PLAY)
                else if(app_state_check(TYPE_IN_USB_STATES))
                {
                    app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_USB_DISCONNECTING, REASON_DISCONNECT);
                    app_state_in_processing_action = ACTION_SWITCH_TO_LAST_GAMING_LINK;
                }
                #endif /* _CONFIG_AIR_USB_PLUG_AND_PLAY_ */
                else if(app_state_check(TYPE_IN_BT_CONNECTED_STATES))
                {
                    app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_BT_DISCONNECTING, REASON_DISCONNECT);
                    app_state_in_processing_action = ACTION_SWITCH_TO_LAST_GAMING_LINK;
                }
                else if(app_state_check(TYPE_IN_BT_PAIRING_RECONNECT))
                {
                    app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_CONNECT_CANCEL, REASON_DISCONNECT);
                    app_state_in_processing_action = ACTION_SWITCH_TO_LAST_GAMING_LINK;
                }
                #if defined (CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF)
                app_state_in_processing_action = ACTION_NONE;
                #endif
            }
            #else
            APP_LOGI(thisMOD,"SLIDE_SWITCH_POS_BT event is ignored due to CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE=n");
            #endif /* _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_GAMING_MODE_ */
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}
#endif /* CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH || CONFIG_AIR_DUAL_MODE_SLIDE_SWITCH */

#if defined (CONFIG_AIR_KEYBOARD_M607)

static bool app_mode_switch__evt_mode_switch_status(const struct af_evt_header *evt_header)
{
    struct evt_mode_switch_status* event = (struct evt_mode_switch_status*)evt_header;
    APP_LOGI(thisMOD,"app_mode_switch__evt_mode_switch_status, position = %d", event->position);

    #if defined (CONFIG_AIR_USB_PLUG_AND_PLAY)
    if(app_state_check(TYPE_IN_USB_STATES)){
        APP_LOGI(thisMOD,"evt_mode_switch_status is ignored due to CONFIG_AIR_USB_PLUG_AND_PLAY=y and USB plugged");
        return 0;
    }
    #endif /* _CONFIG_AIR_USB_PLUG_AND_PLAY_ */

    switch(event->position)
    {
        case SLIDE_SWITCH_POS_OFF:
        {
            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
            if (!app_state_check(TYPE_IN_USB_STATES))
            {
                uint8_t plug_status = app_usb_port__get_usb_plug_status();
                if(plug_status) {
                    if(plug_status == APP_USB_CONFIGURED)
                    {
                        APP_LOGI(thisMOD,"SLIDE_SWITCH_POS_OFF");
                        if(app_state == APP_STATE_STANDBY){
                            app_state_announce_connect_req(CONN_REQ_CONN_USB, APP_STATE_CONNECT_PREPARING, REASON_CONNECT_START);
                        }
                        else{
                            app_state_terminate_wireless_connection(ACTION_SWITCH_TO_USB_MODE);
                        }
                    }
                    else  //plug in but not configured
                    {
                        APP_LOGI(thisMOD,"SLIDE_SWITCH_POS_OFF and plugged in charger or not configured yet!");
                        #if !defined(CONFIG_AIR_CHARGE_DONT_ENTER_SLEEP)
                        app_state_terminate_wireless_connection(ACTION_NONE);
                        #endif
                    }
                }
                else {
                   APP_LOGI(thisMOD,"SLIDE_SWITCH_POS_OFF and USB NOT plugged in PC!");
                }
            }
            #else
            APP_LOGI(thisMOD,"SLIDE_SWITCH_POS_OFF event is ignored due to CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE=n");
            #endif /* _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_ */
            break;
        }
        case SLIDE_SWITCH_POS_BT:
        {
            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
            if (!app_state_check(TYPE_IN_BT_STATES))
            {
                APP_LOGI(thisMOD,"SLIDE_SWITCH_POS_BT");
                if(app_state == APP_STATE_STANDBY){   //BT 2.4 pairing timeout
                    app_state__activate_bt(CONN_REQ_CONN_LAST_BT_LINK);
                }
                #if !defined (CONFIG_AIR_USB_PLUG_AND_PLAY)
                else if(app_state_check(TYPE_IN_USB_STATES))
                {
                    app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_USB_DISCONNECTING, REASON_DISCONNECT);
                    app_state_in_processing_action = ACTION_SWITCH_TO_LAST_BT_LINK;
                }
                #endif /* _CONFIG_AIR_USB_PLUG_AND_PLAY_ */
                else if(app_state_check(TYPE_IN_GAMING_CONNECTED_STATES))
                {
                    app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_2_4G_DISCONNECTING, REASON_DISCONNECT);
                    app_state_in_processing_action = ACTION_SWITCH_TO_LAST_BT_LINK;
                }
                else if(app_state_check(TYPE_IN_GAMING_PAIRING_RECONNECT))
                {
                    app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_CONNECT_CANCEL, REASON_DISCONNECT);
                    app_state_in_processing_action = ACTION_SWITCH_TO_LAST_BT_LINK;
                }
                #if defined (CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF)
                app_state_in_processing_action = ACTION_NONE;
                #endif
            }
            #else
            APP_LOGI(thisMOD,"SLIDE_SWITCH_POS_BT event is ignored due to CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE=n");
            #endif /* _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE_ */
            break;
        }
        case SLIDE_SWITCH_POS_GAMING:
        {
            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_GAMING_MODE)
            if (!app_state_check(TYPE_IN_GAMING_STATES))
            {
                APP_LOGI(thisMOD,"SLIDE_SWITCH_POS_GAMING");
                if(app_state == APP_STATE_STANDBY){
                    app_state__activate_bt(CONN_REQ_CONN_LAST_GAMING_LINK);
                }
                #if !defined (CONFIG_AIR_USB_PLUG_AND_PLAY)
                else if(app_state_check(TYPE_IN_USB_STATES))
                {
                    app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_USB_DISCONNECTING, REASON_DISCONNECT);
                    app_state_in_processing_action = ACTION_SWITCH_TO_LAST_GAMING_LINK;
                }
                #endif /* _CONFIG_AIR_USB_PLUG_AND_PLAY_ */
                else if(app_state_check(TYPE_IN_BT_CONNECTED_STATES))
                {
                    app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_BT_DISCONNECTING, REASON_DISCONNECT);
                    app_state_in_processing_action = ACTION_SWITCH_TO_LAST_GAMING_LINK;
                }
                else if(app_state_check(TYPE_IN_BT_PAIRING_RECONNECT))
                {
                    app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_CONNECT_CANCEL, REASON_DISCONNECT);
                    app_state_in_processing_action = ACTION_SWITCH_TO_LAST_GAMING_LINK;
                }
                #if defined (CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF)
                app_state_in_processing_action = ACTION_NONE;
                #endif
            }
            #else
            APP_LOGI(thisMOD,"SLIDE_SWITCH_POS_BT event is ignored due to CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE=n");
            #endif /* _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_GAMING_MODE_ */
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}
#endif /* CONFIG_AIR_KEYBOARD_M607 */

#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
static bool app_state__evt_usb_status(const struct af_evt_header *evt_header)
{
    struct evt_usb_status* event = (struct evt_usb_status*)evt_header;
    APP_LOGI(thisMOD,"app_state__evt_usb_status, status = %d", event->status);
    switch(event->status)
    {
        case USB_STATUS_PLUGGED_OUT:  //0
        {
            break;
        }
        case USB_STATUS_PLUGGED_IN:  //1
        {
            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE) && defined(CONFIG_AIR_CHARGE_DONT_ENTER_SLEEP)
            if((app_state >= APP_STATE_BT_CONNECTED_IDLE_1 && app_state <= APP_STATE_BT_CONNECTED_IDLE_3) ||
               (app_state >= APP_STATE_BT_CONNECTED_ENTERING_IDLE_1 && app_state <= APP_STATE_BT_CONNECTED_ENTERING_IDLE_3))
            {
                uint8_t charge = app_battery__get_bat_charge_status();
                if(charge)
                {
                    APP_LOGI(thisMOD,"usb plugged now, BT dont enter idle!");
                    app_state_announce_connect_req(CONN_REQ_ACTIVE, APP_STATE_BT_CONNECTED_ENTERING_ACTIVE, REASON_ACTIVE);
                    k_timer_stop(&app_state_enter_idle_timer);
                    k_timer_stop(&app_state_disconnect_req_timer);
                } else{
                    APP_LOGI(thisMOD,"usb plugged out now in BT, please check it!");
                }
            }
            #endif
            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_GAMING_MODE) && defined(CONFIG_AIR_CHARGE_DONT_ENTER_SLEEP)
            if((app_state >= APP_STATE_2_4G_CONNECTED_IDLE_1 && app_state <= APP_STATE_2_4G_CONNECTED_IDLE_3) ||
               (app_state >= APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1 && app_state <= APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_3))
            {
                uint8_t charge = app_battery__get_bat_charge_status();
                if(charge)
                {
                    APP_LOGI(thisMOD,"usb plugged now, 2.4G dont enter idle!");
                    app_state_announce_connect_req(CONN_REQ_ACTIVE, APP_STATE_2_4G_CONNECTED_ENTERING_ACTIVE, REASON_ACTIVE);
                    k_timer_stop(&app_state_enter_idle_timer);
                    k_timer_stop(&app_state_disconnect_req_timer);
                }
                else{
                    APP_LOGI(thisMOD,"usb plugged out now in 2.4G, please check it!");
                }
            }
            #endif
            break;
        }
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
        case USB_STATUS_CONFIGURED:  //4
        {
            #if defined (CONFIG_AIR_USB_PLUG_AND_PLAY)
            app_state__do_wired_mode_connect();
            #else
            uint8_t ss_type = SS_MODE_NONE;
            GET_SLIDE_SWITCH_MODE(&ss_type);
            APP_LOGI(thisMOD,"app_state__evt_usb_status,  USB_STATUS_CONFIGURED, ss_type = %d, curr_state = %02X", ss_type, app_state);

            if(ss_type == SS_MODE_OFF || ss_type == SS_MODE_NONE) {
                app_state__do_wired_mode_connect();
            }
            else if(ss_type == SS_MODE_BT || ss_type == SS_MODE_2_4G) {
                APP_LOGI(thisMOD,"USB_STATUS_CONFIGURED, wait for switch to usb position");
            }
            #endif/* _CONFIG_AIR_USB_PLUG_AND_PLAY_ */
            break;
        }
        case USB_STATUS_DISCONNECT:  //5
        {
            #if defined (CONFIG_AIR_USB_PLUG_AND_PLAY)
            app_state__do_wired_mode_disconnect();
            #else
            uint8_t ss_type = SS_MODE_NONE;
            GET_SLIDE_SWITCH_MODE(&ss_type);
            APP_LOGI(thisMOD,"app_state__evt_usb_status,  USB_STATUS_DISCONNECT, ss_type = %d, curr_state = %02X", ss_type, app_state);

            if(ss_type == SS_MODE_OFF || ss_type == SS_MODE_NONE) {
                app_state__do_wired_mode_disconnect();
            }
            else if(ss_type == SS_MODE_BT || ss_type == SS_MODE_2_4G) {
                APP_LOGI(thisMOD,"USB_STATUS_DISCONNECT");
            }
            #endif/* _CONFIG_AIR_USB_PLUG_AND_PLAY_ */
            break;
        }
        #endif /* _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_ */
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}
#endif /* defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE) */

static bool app_state__evt_rr_status(const struct af_evt_header *evt_header)
{
    struct evt_rr_status* event = (struct evt_rr_status*)evt_header;
    APP_LOGI(thisMOD,"app_state__evt_rr_status , category = %d, RR = %d", event->category, event->RR);

    if (event->category == 0){
        app_state__USB_rr = event->RR;
    }
    else if (event->category == 1){
        app_state__2_4G_rr = event->RR;
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_state__evt_app_battery(const struct af_evt_header *evt_header)
{
    struct evt_app_battery* event = (struct evt_app_battery*)evt_header;
    APP_LOGI(thisMOD,"app_state__evt_app_battery, val = %d, cmd = %d", event->val, event->status);

    switch(event->status)
    {
        case BAT_EVT_POWER_OFF:
        {
            switch(app_state)
            {
                case APP_STATE_NONE:
                //case APP_STATE_INITIALIZED:
                case APP_STATE_DISCONNECTED:
                case APP_STATE_TEST:
                {
                    app_state_change(APP_STATE_STANDBY , REASON_LOW_BATTERY);
                    break;
                }
                case APP_STATE_USB_CONNECTED:
                case APP_STATE_USB_ACTIVE:
                case APP_STATE_USB_SUSPEND:
                case APP_STATE_USB_ENTERING_ACTIVE:
                case APP_STATE_USB_DISCONNECTING:
                {
                    app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_USB_DISCONNECTING, REASON_LOW_BATTERY);
                    break;
                }
                case APP_STATE_CONNECT_CANCEL:
                case APP_STATE_CONNECT_CANCEL_CHECK:
                case APP_STATE_BT_DISCONNECTING:
                case APP_STATE_2_4G_DISCONNECTING:
                {
                    break;
                }
                default:
                {
                    if(app_state_check(TYPE_IN_BT_STATES)){
                        app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_BT_DISCONNECTING, REASON_LOW_BATTERY);
                    }
                    else if(app_state_check(TYPE_IN_GAMING_STATES)){
                        app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_2_4G_DISCONNECTING, REASON_LOW_BATTERY);
                    }
                    break;
                }
            }
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_state__evt_enter_test(const struct af_evt_header *evt_header)
{
    #if !defined (CONFIG_AIR_HID_DEBUG_PIN)
    struct evt_enter_test* event = (struct evt_enter_test*)evt_header;
    APP_LOGI(thisMOD,"app_state__evt_enter_test, target_mode = %d", event->type);

    switch(event->type)
    {
        case TEST_TYPE_RELAY_MODE:
        {
            if(app_state_check(TYPE_IN_USB_STATES) || app_state == APP_STATE_INITIALIZED){
                app_state_change(APP_STATE_TEST, REASON_ENTER_LABTEST);
            }
            else{
                app_state_terminate_wireless_connection(ACTION_SWITCH_TO_RELAY_MODE);
            }
            break;
        }
        case TEST_TYPE_LAB_TEST:
        {
            app_state__activate_bt(CONN_REQ_NONE);
            app_state_change(APP_STATE_TEST, REASON_ENTER_LABTEST);
        }
        default:{
            break;
        }
    }
    #endif /* _!DEF_CONFIG_AIR_HID_DEBUG_PIN_ */

    return AF_TRAVERSE_NEXT;
}

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static void app_state_timer_init()
{
    k_timer_init(&app_state_pairing_timer , app_state_pairing_timeout, NULL);
    k_timer_init(&app_state_reconnect_timer , app_state_pairing_timeout, NULL);
    k_timer_init(&app_state_enter_idle_timer , app_state_enter_idle2_timeout, NULL);
    k_timer_init(&app_state_deepsleep_timer , app_state_enter_deepsleep, NULL);
    k_timer_init(&app_state_disconnect_req_timer , app_state_disconnect_req_timeout, NULL);
    app_nvkey_read_data(NVID_POWER_SAVING_TIMEOUT, (uint8_t*)&power_saving_timeout, sizeof(power_saving_timeout));
    hid_common->app.inActivity_timeout = power_saving_timeout.active_timeout * 1000;
}


static void app_state__activate_bt(uint32_t conn_type)
{
    APP_LOGI(thisMOD,"app_state__activate_bt, bt_status = %d, conn_type = %d", app_state_ctrl.bt_status, conn_type);

    if (app_state_ctrl.bt_status == BT_STATUS_OFF){
        app_state_ctrl.bt_status = BT_STATUS_INITIALIZING;


        #if defined (AIR_SWLA_ENABLE)
        HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_app_bt_connecting, SWLA_DIRECTION_START);
        #endif

        DBG_PING_H(DBG_SIGNAL_LATCH_REPORT);
        int err = bt_enable(NULL);
        DBG_PING_L(DBG_SIGNAL_LATCH_REPORT);

        if (err) {
            //assert(0 && "Bluetooth init failed");
            APP_LOGI(thisMOD,"app_state enable BT fail");
        }
        else {

            #if defined (AIR_SWLA_ENABLE)
            HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_app_bt_connecting, SWLA_DIRECTION_LABEL);
            #endif

            DBG_PING_H(DBG_SIGNAL_LATCH_REPORT);
            err = settings_load();
            DBG_PING_L(DBG_SIGNAL_LATCH_REPORT);

            if(err){
                APP_LOGI(thisMOD,"settings_load failed (err %d)", err);
            }
            else{
                APP_LOGI(thisMOD,"Bluetooth initialized, settings load");
            }
        }
        app_state_ctrl.bt_status = BT_STATUS_READY;
    }

    if (conn_type){
        switch (app_state)
        {
            case APP_STATE_BT_PAIRING:
            case APP_STATE_2_4G_PAIRING:
            case APP_STATE_BT_RECONNECT:
            case APP_STATE_2_4G_RECONNECT:
            case APP_STATE_2_4G_QUICK_CONNECT:
            {
                app_state_announce_connect_req(conn_type, APP_STATE_CONNECT_CANCEL, REASON_LINK_NEXT);
                break;
            }

            case APP_STATE_USB_CONNECTED:
            case APP_STATE_USB_ACTIVE:
            case APP_STATE_USB_SUSPEND:
            case APP_STATE_USB_ENTERING_ACTIVE:
            {
                app_state_announce_connect_req(conn_type, APP_STATE_USB_DISCONNECTING, REASON_LINK_NEXT);
                break;
            }

            case APP_STATE_BT_CONNECTED:
            case APP_STATE_BT_CONNECTED_ACTIVE:
            case APP_STATE_BT_CONNECTED_IDLE_1:
            case APP_STATE_BT_CONNECTED_IDLE_2:
            case APP_STATE_BT_CONNECTED_IDLE_3:
            case APP_STATE_BT_CONNECTED_ENTERING_ACTIVE:
            case APP_STATE_BT_CONNECTED_ENTERING_IDLE_1:
            case APP_STATE_BT_CONNECTED_ENTERING_IDLE_2:
            case APP_STATE_BT_CONNECTED_ENTERING_IDLE_3:
            {
                app_state_announce_connect_req(conn_type, APP_STATE_BT_DISCONNECTING, REASON_LINK_NEXT);
                break;
            }

            case APP_STATE_2_4G_CONNECTED:
            case APP_STATE_2_4G_CONNECTED_ACTIVE:
            case APP_STATE_2_4G_CONNECTED_IDLE_1:
            case APP_STATE_2_4G_CONNECTED_IDLE_2:
            case APP_STATE_2_4G_CONNECTED_IDLE_3:
            case APP_STATE_2_4G_CONNECTED_ENTERING_ACTIVE:
            case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1:
            case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_2:
            case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_3:
            {
                app_state_announce_connect_req(conn_type, APP_STATE_2_4G_DISCONNECTING, REASON_LINK_NEXT);
                break;
            }

            default:
                app_state_announce_connect_req(conn_type, APP_STATE_CONNECT_PREPARING, REASON_ACTIVE);
                break;
        }
        }
}

static void app_state__inactivate_bt()
{
    APP_LOGI(thisMOD,"app_state__inactivate_bt, bt_status = %d", app_state_ctrl.bt_status);

    if (app_state_ctrl.bt_status == BT_STATUS_READY){
        int err = bt_disable();
        if (err) {
            //assert(0 && "Bluetooth init failed");
            APP_LOGI(thisMOD,"app_state disable BT fail = %d", err);
        }
        app_state_ctrl.bt_status = BT_STATUS_OFF;
    }
}

static void app_state_features_init()
{
    T_HID_APP_FEATURES_S hid_app_feature;

    bool ret = app_nvkey_read_data(NVID_HID_APP_FEATURES, (uint8_t*)&hid_app_feature, sizeof(T_HID_APP_FEATURES_S));

    if (ret) {
        APP_LOGI(thisMOD,"app_state_features_init, hid_app_feature = 0x%02X-%02X-%02X,  ,  ret = %d "
            , hid_app_feature.features_1
            , hid_app_feature.features_2
            , hid_app_feature.features_3
            , hid_app_feature.features_3
            , ret
            );
    }
}

static void app_state_announce_new_state(uint32_t new_app_state)
{
    struct evt_app_state* event = create_evt_app_state();

    if (event){
        event->app_state = new_app_state;
        AF_EVT_SUBMIT(event);
    }
}

static void app_state_announce_connect_req(uint32_t conn_type, uint32_t next_state, uint32_t reason)
{
    struct evt_conn_req* event_conn = create_evt_conn_req();

    if (event_conn){
        if (next_state == APP_STATE_CONNECT_PREPARING){
            // submit APP_STATE_CONNECT_PREPARING event before event_conn
            // app task is a low priority task
            app_state_change(next_state , reason);
        }

        APP_LOGI(thisMOD,"app_state_announce_connect_req, conn_type = %d, next_state = 0x%02X, reason = 0x%02X", conn_type, next_state, reason);
        event_conn->cmd = conn_type;
        AF_EVT_SUBMIT(event_conn);

        if (next_state != APP_STATE_CONNECT_PREPARING){
            app_state_change(next_state , reason);
        }
    }
}

static void app_state_change(uint32_t new_state, uint32_t reason)
{
    if(app_state == APP_STATE_TEST) {
        APP_LOGI(thisMOD,"In test mode, dont need to change state!");
        return;
    }
    switch(new_state)
    {
        case APP_STATE_STANDBY:
        {
            #if defined(CONFIG_AIR_CHARGE_DONT_ENTER_SLEEP)
            if(app_battery__check_bat_charge_and_power_on())
            {
                APP_LOGI(thisMOD,"Cannot enter standby when usb plugged in!");
                app_state__activate_bt(CONN_REQ_CONN_LAST_LINK);
                return;
            }
            #endif
            app_state__inactivate_bt();
            break;
        }
        case APP_STATE_DISCONNECTED:
        {
            app_state__activate_bt(CONN_REQ_NONE);
            break;
        }
        case APP_STATE_CONNECT_PREPARING:
        {
            app_state_set_hid_flag();
            break;
        }
        default:{
            break;
        }
    }

    app_state_announce_new_state(new_state);

    uint32_t link_idx = app_links_get_link_idx();
    uint8_t clk_idx = clock_mux_cur_sel(CLK_SYS_SEL);

    APP_LOGI(thisMOD,"=============================================================================");
    if (app_state_check(TYPE_IN_USB_STATES)){
        APP_LOGI(thisMOD," App State changed from 0x%02X to 0x%02X, reason = 0x%02X,  Wired mode RR = %d, clk_idx = %d (32,26,52,156,78,104)"
            , app_state
            , new_state
            , reason
            , app_state__USB_rr
            , clk_idx
            );
    }else if (app_links_read_link_type() == LINKT_TYPE_2_4G){
        APP_LOGI(thisMOD," App State changed from 0x%02X to 0x%02X, reason = 0x%02X, link_%d is (2.4G Link), RR = %d, clk_idx = %d(32,26,52,156,78,104)"
            , app_state
            , new_state
            , reason
            , link_idx
            , app_state__2_4G_rr
            , clk_idx
            );
    }else {
        APP_LOGI(thisMOD," App State changed from 0x%02X to 0x%02X, reason = 0x%02X, link_%d is (BT link), clk_idx = %d(32,26,52,156,78,104)"
            , app_state
            , new_state
            , reason
            , link_idx
            , clk_idx
            );
    }
    APP_LOGI(thisMOD,"=============================================================================");

    //APP_LOGI(thisMOD, "REG_GPIO_MODE [23_16]= 0x%08X, [15_08]= 0x%08X, [07_00]= 0x%08X", (unsigned int)(*(volatile uint32_t*)0x420b0038) , (unsigned int)(*(volatile uint32_t*)0x420b0034), (unsigned int)(*(volatile uint32_t*)0x420b0030));
    //APP_LOGI(thisMOD, "REG_GPIO_MODE [47_40]= 0x%08X, [39_32]= 0x%08X, [31_24]= 0x%08X", (unsigned int)(*(volatile uint32_t*)0x420b0044), (unsigned int)(*(volatile uint32_t*)0x420b0040), (unsigned int)(*(volatile uint32_t*)0x420b003C));

    app_state = new_state;
    app_processing_state = APP_STATE_NONE;
}

#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
static void app_state__do_wired_mode_disconnect()
{
    uint8_t battery_level = app_battery__get_battery_level();
    APP_LOGI(thisMOD,"app_state__do_wired_mode_disconnect, state = 0x%X, battery level = %d", app_state, battery_level);
    if(battery_level > 1){
        app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_USB_DISCONNECTING, REASON_DISCONNECT);
        app_state_in_processing_action = ACTION_SWITCH_TO_LAST_LINK;
    }
    else{
        app_state_announce_connect_req(CONN_REQ_DISC, APP_STATE_USB_DISCONNECTING, REASON_LOW_BATTERY);
    }
}

static void app_state__do_wired_mode_connect()
{
    APP_LOGI(thisMOD,"app_state__do_wired_mode_connect, state = 0x%X", app_state);
    if(app_state == APP_STATE_CONNECT_PREPARING || app_state == APP_STATE_TEST){
        return;
    }
    if(app_state_check(TYPE_IN_BT_STATES) || app_state_check(TYPE_IN_GAMING_STATES)
    #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
       || app_state_check(TYEP_IN_GAMING_RESUME)
    #endif
    ){
        app_state_terminate_wireless_connection(ACTION_SWITCH_TO_USB_MODE);
    }
    else if(!app_state_check(TYPE_IN_USB_STATES))
    {
        #if 0
        APP_LOGI(thisMOD,"[SWLA]label_app_state_init STOP");
        HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_app_state_init, SWLA_DIRECTION_STOP);
        #endif
        app_state_announce_connect_req(CONN_REQ_CONN_USB, APP_STATE_CONNECT_PREPARING, REASON_CONNECT_START);
    }
    else if(app_state == APP_STATE_USB_SUSPEND){
        app_state_announce_connect_req(CONN_REQ_ACTIVE_USB, APP_STATE_USB_ENTERING_ACTIVE, REASON_ACTIVE);
    }
}
#endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE */

static void app_state_set_hid_flag()
{
    uint8_t scenario_type = app_scenario_get_scenario_type();
    switch(scenario_type)
    {
        case HID_SCENARIO_USB_MODE:  //3
        {
            hid_common_set_hid_exp_flag(FLAG_BIT_SCENARIO_MODE_TYPE);
            hid_common_set_hid_exp_flag(FLAG_BIT2_SCENARIO_MODE_TYPE);
            break;
        }
        case HID_SCENARIO_GAMING_MODE:  //2
        {
            hid_common_clear_hid_exp_flag(FLAG_BIT_SCENARIO_MODE_TYPE);
            hid_common_set_hid_exp_flag(FLAG_BIT2_SCENARIO_MODE_TYPE);
            break;
        }
        case HID_SCENARIO_BT_MODE:  //1
        {
            hid_common_set_hid_exp_flag(FLAG_BIT_SCENARIO_MODE_TYPE);
            hid_common_clear_hid_exp_flag(FLAG_BIT2_SCENARIO_MODE_TYPE);
            break;
        }
        default: {
            break;
        }
    }
    APP_LOGI(thisMOD, "app_state_set_hid_flag = %d", APP_SCENARIO_MODE_TYPE(hid_common->hid.flags));
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
void app_state_init()
{
    app_state_change(APP_STATE_INITIALIZED , REASON_INIT_COMPLETE);
    APP_LOGI(thisMOD,"app_state_init ");
    memset((uint8_t*)&app_state_ctrl, 0, sizeof(app_state_ctrl));

    app_state_features_init();
    app_state_timer_init();
    APP_LOGI(thisMOD,"app_state_init end");
}

uint32_t app_state_current_state()
{
    return app_state;
}

void app_state_get_power_saving_timeout(uint32_t *idle1_timeout, uint32_t *idle2_timeout)
{
    *idle1_timeout = power_saving_timeout.idle1_timeout * 1000;
    *idle2_timeout = power_saving_timeout.idle2_timeout * 1000;
}

uint32_t app_state_check(uint32_t condiction)
{
    uint32_t ret_val = false;
    switch(condiction)
    {
        case TYPE_CONNECTED_WO_ACTIVE:
        {
            if (app_state & (APP_STATE_BT_CONNECTED | APP_STATE_2_4G_CONNECTED)){
                // BT or 2.4G connected
                if (app_state & 0x0E){
                    ret_val = true;
                }
            }
            else if(app_state == APP_STATE_USB_SUSPEND){
                ret_val = true;
                APP_LOGI(thisMOD,"app_state_check, APP_STATE_USB_SUSPEND, ret_val = %d", ret_val);
            }
        }
        break;

        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        case TYPE_IN_BT_PAIRING_RECONNECT:
        {
            if (( app_state == APP_STATE_BT_PAIRING ) || ( app_state == APP_STATE_BT_RECONNECT))
            {
                ret_val = true;
            }
        }
        break;

        case TYPE_IN_BT_CONNECTED_STATES:
        {
            if (((app_state >= APP_STATE_BT_CONNECTED) && (app_state <= APP_STATE_BT_DISCONNECTING))
            )
            {
                ret_val = true;
            }
        }
        break;

        case TYPE_IN_BT_STATES:
        {
            if (    ( app_state == APP_STATE_BT_PAIRING )
                 || ( app_state == APP_STATE_BT_RECONNECT)
                 || ((app_state >= APP_STATE_BT_CONNECTED) && (app_state <= APP_STATE_BT_DISCONNECTING) )
            )
            {
                ret_val = true;
            }
        }
        break;
        #endif

        case TYPE_IN_USB_STATES:
        {
            if ((app_state >= APP_STATE_USB_CONNECTED) && (app_state <= APP_STATE_USB_DISCONNECTING ))
            {
                ret_val = true;
            }
        }
        break;

        case TYPE_IN_GAMING_PAIRING_RECONNECT:
        {
            if (( app_state == APP_STATE_2_4G_PAIRING) || ( app_state == APP_STATE_2_4G_RECONNECT))
            {
                ret_val = true;
            }
        }
        break;

        case TYPE_IN_GAMING_CONNECTED_STATES:
        {
            if (((app_state >= APP_STATE_2_4G_CONNECTED) && (app_state <=  APP_STATE_2_4G_DISCONNECTING))
            )
            {
                ret_val = true;
            }
        }
        break;

        case TYPE_IN_GAMING_CONNECTED_STABLE:
        {
            if (((app_state > APP_STATE_2_4G_CONNECTED) && (app_state <  APP_STATE_2_4G_DISCONNECTING))
            )
            {
                ret_val = true;
            }
        }
        break;

        case TYPE_IN_GAMING_STATES:
        {
            if (    ( app_state == APP_STATE_2_4G_PAIRING)
                 || ( app_state == APP_STATE_2_4G_RECONNECT)
                 || ((app_state >= APP_STATE_2_4G_CONNECTED) && (app_state <=  APP_STATE_2_4G_DISCONNECTING))
            )
            {
                ret_val = true;
            }
        }
        break;

        #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
        case TYEP_IN_GAMING_RESUME:
        {
            if(app_state == APP_STATE_2_4G_RECONNECT_RESUME_WAIT){
                ret_val = true;
            }
        }
        break;
        #endif
    }

    return ret_val;
}

/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN_LAST(thisMODULE, evt_module_init, app_state__evt_module_init);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_app_state_change_req, app_state_evt_app_state_change_req);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_active_status, app_state_evt_active_status);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_app_battery, app_state__evt_app_battery);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_enter_test, app_state__evt_enter_test);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_pairing_request, app_state_evt_pairing_request);

#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_usb_status, app_state__evt_usb_status);
#endif /* defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE) */
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_link_change, app_state_evt_link_change);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_scenario_status, app_state_evt_scenario_status);
#if defined (CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH) || defined (CONFIG_AIR_DUAL_MODE_SLIDE_SWITCH)
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_slide_switch_status, app_state__evt_slide_switch_status);
#endif /* CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH || CONFIG_AIR_DUAL_MODE_SLIDE_SWITCH */
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_rr_status, app_state__evt_rr_status);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_force_key_release_success, app_state_evt_force_key_release_success);

#if defined (CONFIG_AIR_KEYBOARD_M607)
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_mode_switch_status, app_mode_switch__evt_mode_switch_status);
#endif /*END CONFIG_AIR_KEYBOARD_M607*/
/*=============================================================================*/