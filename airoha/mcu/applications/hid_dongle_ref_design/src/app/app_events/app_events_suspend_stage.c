/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
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
 * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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

#if defined(AIR_PURE_GAMING_DONGLE_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include "app_debug.h"
#include "af_framework.h"
#include "af_events_declaration.h"
#include "app_state.h"
#include "hid_scenario_dongle.h"
#include "app_bt_conn_manager.h"
#include "app_acl_conn.h"
#include "app_bt_ull_conn.h"
#include "assert.h"
#include "app_pure_gaming_dongle_scenario.h"
#include "app_events.h"
#include "air_usb.h"
#include "air_usb_hid.h"

/* Private define ------------------------------------------------------------*/
#define thisMODULE app_events
#define thisMOD    "app_events"
LOG_MODULE_DECLARE(thisMODULE);

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
int app_events_suspend_stage_hdl(struct evt_cmd *event)
{
    app_bt_conn_handle_t *link_handle;
    app_pg_scenario_handle_t *scenario_handle;
    int ret;
    // bool is_bt_connected = false;
    // app_pg_scenario_usb_status_t usb_status = APP_USB_PLUGOUT;
    // bool rr_change;

    switch (event->cmd)
    {
        /* In USB suspend, we will try to reconnect mouse in a period */
        case EVT_CMD_RECONNECT_REQ:
            app_events_suspend_all_events();
            app_events_allow_special_event(EVT_CMD_ULL_CONN_SUCCESS);
            app_events_allow_special_event(EVT_CMD_ULL_SERVICE_CONN_REQ);
            app_events_allow_special_event(EVT_CMD_ULL_SERVICE_CONN_SUCCESS);
            app_events_allow_special_event(EVT_CMD_RECONNECT_SUCCESS);
            app_events_allow_special_event(EVT_CMD_RECONNECT_CANCEL_REQ);
            app_events_allow_special_event(EVT_CMD_RECONNECT_CANCEL_SUCCESS);
            app_events_allow_special_event(EVT_CMD_RECONNECT_TIMEOUT);
            #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
            app_events_allow_special_event(EVT_CMD_CIS_SCAN_DEVICE_FOUND);
            app_events_allow_special_event(EVT_CMD_USB_READY);
            #endif/*CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE*/
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            // /* clear report rate change flag */
            // rr_change = false;
            // app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_REPORT_RATE_CHANGE_REQUEST, &rr_change);
            /* start reconnection */
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_HANDLE_QEURY, &link_handle);
            #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
            LOG_INF("app_bt_ull_connection_connect_device_suspend");
            app_bt_ull_connection_connect_device_suspend(link_handle);//for pc suspend with rf
            #else
            app_bt_ull_connection_connect_device(link_handle);
            #endif/*CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE*/
            break;
        /* Reconnect success, it means the mouse is moving to wakeup PC */
        case EVT_CMD_ULL_CONN_SUCCESS:
            app_events_send(EVT_CMD_ULL_SERVICE_CONN_REQ, event->param);
            break;
        case EVT_CMD_ULL_SERVICE_CONN_REQ:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            // app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_HANDLE_QEURY, &link_handle);
            // app_bt_ull_connection_connect_service(link_handle);
            /* TODO: Temp Solution, sometime connect service is not ready */
            app_events_send(EVT_CMD_RECONNECT_SUCCESS, scenario_handle);
            break;
        case EVT_CMD_ULL_SERVICE_CONN_SUCCESS:
            app_events_send(EVT_CMD_RECONNECT_SUCCESS, event->param);
            break;
        case EVT_CMD_RECONNECT_SUCCESS:
            app_events_resume_all_events();
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            // app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_HANDLE_QEURY, &link_handle);
            app_pure_gaming_dongle_scenario_exit_usb_suspend_case(scenario_handle);
            #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
            #else
            ret = air_usb_wakeup_request();
            LOG_INF("[app_hid_dongle] pure gaming dongle wakeup usb %d", ret);
            app_pure_gaming_dongle_scenario_wakeup_pc();
            #endif/*CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE*/
            app_state_change(APP_STATE_CONNECTED, REASON_RECONNECT);
            app_events_send(EVT_CMD_RECONNECT_SUCCESS, scenario_handle);
            break;
        case EVT_CMD_RECONNECT_TIMEOUT:
            app_events_resume_all_events();
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_usb_suspend_case_switch_to_idle(scenario_handle);
            break;
        /* Reconnect cancel, it means the mouse is not moving */
        case EVT_CMD_RECONNECT_CANCEL_REQ:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_HANDLE_QEURY, &link_handle);
            #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
            app_bt_ull_connection_disconnect_suspend(link_handle);
            app_events_resume_all_events();
            #else
            app_bt_ull_connection_cancel(link_handle);
            #endif/*CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE*/
            break;
        case EVT_CMD_RECONNECT_CANCEL_SUCCESS:
            app_events_resume_all_events();
            break;

        /* Other device wakeup PC, we need to try to connect mouse */
        case EVT_CMD_USB_RESUME:
        case EVT_CMD_USB_READY:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
            app_events_resume_all_events();
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_HANDLE_QEURY, &link_handle);
            app_bt_ull_connection_disconnect_suspend(link_handle);
            #endif/*CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE*/
            app_pure_gaming_dongle_scenario_exit_usb_suspend_case(scenario_handle);
            app_pure_gaming_dongle_scenario_usb_status_update_by_evt(scenario_handle, event->cmd);
            app_state_change(APP_STATE_RECONNECT, REASON_USB_RESUME);
            app_events_send(EVT_CMD_RECONNECT_REQ, scenario_handle);
            break;

        /* other usb case */
        case EVT_CMD_USB_SUSPEND:
            break;
        case EVT_CMD_USB_PLUGOUT:
            /* usb plugout case: goto deinit stage */
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_usb_status_update_by_evt(scenario_handle, event->cmd);
            app_pure_gaming_dongle_scenario_close(scenario_handle);
            app_state_change(APP_STATE_DEINIT, REASON_USB_PLUGOUT);
            break;

        case EVT_CMD_CIS_SCAN_DEVICE_FOUND:
            #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
            app_events_resume_all_events();
            // scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            // app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_HANDLE_QEURY, &link_handle);
            // app_bt_ull_connection_disconnect_suspend(link_handle);
            ret = air_usb_wakeup_request();
            LOG_INF("[app_hid_dongle] pure gaming dongle wakeup usb %d", ret);
            app_pure_gaming_dongle_scenario_wakeup_pc();
            // app_bt_ull_connection_connect_device(link_handle);
            #endif/*CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE*/
            break;

        case EVT_CMD_REPORT_RATE_CHANGE_REQ:
        case EVT_CMD_OUTPUT_REPORT_CHANGE_REQ:
        case EVT_CMD_AUTO_SWITCH_REQ:
        case EVT_CMD_AUTO_SWITCH_CANCEL_REQ:
            // scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            // /* clear report rate change flag */
            // rr_change = false;
            // app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_REPORT_RATE_CHANGE_REQUEST, &rr_change);
            break;

        default:
            assert(0);
            break;
    }

    return 0;
}

#endif /* AIR_PURE_GAMING_DONGLE_ENABLE */
