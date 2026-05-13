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

#include <stdbool.h>
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
#include "app_events.h"
#include "app_pure_gaming_dongle_scenario.h"
#include "race_cmd.h"
#include "race_xport.h"
#include "app_race_cmd_event.h"
#include "app_race_cmd_pure_gaming_dongle.h"

/* Private define ------------------------------------------------------------*/
#define thisMODULE app_events
#define thisMOD    "app_events"
LOG_MODULE_DECLARE(thisMODULE);

/* Private typedef -----------------------------------------------------------*/
typedef uint8_t app_evt_reconnect_sub_state_t;
#define APP_EVT_RECONNECT_IDLE           0x00
#define APP_EVT_RECONNECT_RUNNING        0x01
#define APP_EVT_RECONNECT_CANCEL         0x02

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static app_evt_reconnect_sub_state_t app_events_reconnect_sub_state = APP_EVT_RECONNECT_IDLE;

/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static int app_events_reconnect_idle_stage_hdl(struct evt_cmd *event)
{
    app_bt_conn_handle_t *link_handle;
    app_pg_scenario_handle_t *scenario_handle;
    uint16_t report_rate;
    app_pg_scenario_usb_status_t usb_status;
    // bool rr_change;

    switch (event->cmd)
    {
        /* reconnect by local request flow area */
        case EVT_CMD_RECONNECT_REQ:
            app_events_reconnect_sub_state = APP_EVT_RECONNECT_RUNNING;
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_HANDLE_QEURY, &link_handle);
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_GET_REPORT_RATE, &report_rate);
            app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_REPORT_RATE, &report_rate);
            app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_SCENARIO, &report_rate);
            // /* clear report rate change flag */
            // rr_change = false;
            // app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_REPORT_RATE_CHANGE_REQUEST, &rr_change);
            /* start reconnection */
            app_bt_ull_connection_connect_device(link_handle);
            break;

        /* usb case */
        case EVT_CMD_USB_PLUGIN:
        case EVT_CMD_USB_READY:
        case EVT_CMD_USB_RESUME:
        case EVT_CMD_USB_SUSPEND:
        case EVT_CMD_USB_PLUGOUT:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_usb_status_update_by_evt(scenario_handle, event->cmd);
            /* check usb status for next action */
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_USB_STATUS, &usb_status);
            if (usb_status == APP_PG_USB_SUSPEND)
            {
                /* usb suspend case: goto suspend stage */
                app_pure_gaming_dongle_scenario_entry_usb_suspend_case(scenario_handle);
                app_state_change(APP_STATE_SUSPEND, REASON_USB_SUSPEND);
            }
            else if (usb_status == APP_PG_USB_READY)
            {
                /* usb ready case: try to reconnect */
                app_events_send(EVT_CMD_RECONNECT_REQ, event->param);
            }
            break;

        /* ignore scan stop request flow area */
        case EVT_CMD_ACL_SCAN_STOP_REQ:
            LOG_ERR("[app_hid_dongle] app_events_reconnect_idle_stage_hdl ignore stop scan request");
            break;
        /* ignore reconect success flow area  */
        case EVT_CMD_RECONNECT_SUCCESS:
            break;

        case EVT_CMD_REPORT_RATE_CHANGE_REQ:
        case EVT_CMD_OUTPUT_REPORT_CHANGE_REQ:
        case EVT_CMD_AUTO_SWITCH_REQ:
        case EVT_CMD_AUTO_SWITCH_CANCEL_REQ:
        case EVT_CMD_RECONNECT_CANCEL_REQ:
        case EVT_CMD_CIS_SCAN_DEVICE_FOUND:
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

static int app_events_reconnect_running_stage_hdl(struct evt_cmd *event)
{
    app_bt_conn_handle_t *link_handle;
    app_pg_scenario_handle_t *scenario_handle;
    bool is_bt_connected = false;
    app_pg_scenario_usb_status_t usb_status = APP_PG_USB_PLUGOUT;
    app_pg_scenario_scan_request_param_t scan_request = {.request=false, .timeout_ms=0};
    // bool rr_change;

    switch (event->cmd)
    {
        /* reconnect success case: normal flow area one by one */
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
            app_events_reconnect_sub_state = APP_EVT_RECONNECT_IDLE;
            app_events_send(EVT_CMD_RECONNECT_SUCCESS, event->param);
            app_state_change(APP_STATE_CONNECTED, REASON_RECONNECT);
            break;
        /* reconnect fail case: error handle area */
        case EVT_CMD_ULL_CONN_FAIL:
        case EVT_CMD_ULL_SERVICE_CONN_FAIL:
            app_events_send(EVT_CMD_RECONNECT_FAIL, event->param);
            break;
        case EVT_CMD_RECONNECT_FAIL:
            app_events_reconnect_sub_state = APP_EVT_RECONNECT_IDLE;
            /* try to reconnect again */
            app_state_change(APP_STATE_DISCONNECTED, REASON_RECONNECT);
            app_events_send(EVT_CMD_RECONNECT_REQ, event->param);
            break;

        /* reconnect cancel by local request flow, need wait reconnect cancel response to do next operations */
        case EVT_CMD_DISCONNECT_REQ:
        case EVT_CMD_RECONNECT_CANCEL_REQ:
            app_events_reconnect_sub_state = APP_EVT_RECONNECT_CANCEL;
            app_events_send(event->cmd, event->param);
            break;

        /* disconnect by device flow, go to the disconnect stage and try to reconnect */
        case EVT_CMD_DISCONNECT_BY_TARGET:
            app_events_reconnect_sub_state = APP_EVT_RECONNECT_IDLE;
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_HANDLE_QEURY, &link_handle);
            is_bt_connected = false;
            app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_BT_STATUS, &is_bt_connected);
            /* send disconnect notification to PC */
            app_race_pg_dongle_connection_report(link_handle, false, 0, RACE_SERIAL_PORT_TYPE_USB);
            // /* clear report rate change flag */
            // rr_change = false;
            // app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_REPORT_RATE_CHANGE_REQUEST, &rr_change);
            /* check usb status for next action */
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_USB_STATUS, &usb_status);
            if (usb_status == APP_PG_USB_PLUGOUT)
            {
                /* usb plugout case: goto deinit stage */
                app_pure_gaming_dongle_scenario_close(scenario_handle);
                app_state_change(APP_STATE_DEINIT, REASON_USB_PLUGOUT);
                /* clear scan request */
                app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_SCAN_REQUEST, &scan_request);
            }
            else if (usb_status == APP_PG_USB_SUSPEND)
            {
                /* usb suspend case: goto suspend stage */
                app_pure_gaming_dongle_scenario_entry_usb_suspend_case(scenario_handle);
                app_state_change(APP_STATE_SUSPEND, REASON_USB_SUSPEND);
                /* clear scan request */
                app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_SCAN_REQUEST, &scan_request);
            }
            else
            {
                app_state_change(APP_STATE_DISCONNECTED, REASON_DISCONNECTED);
                app_events_send(EVT_CMD_RECONNECT_REQ, scenario_handle);
                /* clear scan request */
                app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_SCAN_REQUEST, &scan_request);
            }
            break;

        /* usb case */
        case EVT_CMD_USB_PLUGIN:
        case EVT_CMD_USB_READY:
        case EVT_CMD_USB_RESUME:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_usb_status_update_by_evt(scenario_handle, event->cmd);
            break;
        /* usb suspend or usb plugout flow, need wait reconnect cancel response to do next operations */
        case EVT_CMD_USB_SUSPEND:
        case EVT_CMD_USB_PLUGOUT:
            app_events_reconnect_sub_state = APP_EVT_RECONNECT_CANCEL;
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_usb_status_update_by_evt(scenario_handle, event->cmd);
            app_events_send(EVT_CMD_RECONNECT_CANCEL_REQ, event->param);
            break;

        /* ignore reconnect by local request flow area */
        case EVT_CMD_RECONNECT_REQ:
            LOG_ERR("[app_hid_dongle] app_events_reconnect_running_stage_hdl ignore reconnect request");
            break;

        /* ignore scan stop request flow area */
        case EVT_CMD_ACL_SCAN_STOP_REQ:
            LOG_ERR("[app_hid_dongle] app_events_reconnect_running_stage_hdl ignore stop scan request");
            break;

        case EVT_CMD_ACL_PAIR_REQ:
            LOG_ERR("[app_hid_dongle] app_events_reconnect_running_stage_hdl ignore acl pair request");
            break;

        case EVT_CMD_REPORT_RATE_CHANGE_REQ:
        case EVT_CMD_OUTPUT_REPORT_CHANGE_REQ:
        case EVT_CMD_ACL_SCAN_START_REQ:
        case EVT_CMD_AUTO_SWITCH_REQ:
        case EVT_CMD_AUTO_SWITCH_CANCEL_REQ:
        case EVT_CMD_CIS_SCAN_DEVICE_FOUND:
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

static int app_events_reconnect_cancel_stage_hdl(struct evt_cmd *event)
{
    app_bt_conn_handle_t *link_handle;
    app_pg_scenario_handle_t *scenario_handle;
    bool is_bt_connected = false;
    app_pg_scenario_usb_status_t usb_status = APP_PG_USB_PLUGOUT;
    app_pg_scenario_scan_request_param_t scan_request = {.request=false, .timeout_ms=0};
    // bool rr_change;

    switch (event->cmd)
    {
        /* reconnect cancel by local request flow, need wait reconnect cancel response to do next operations */
        case EVT_CMD_DISCONNECT_REQ:
        case EVT_CMD_RECONNECT_CANCEL_REQ:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_HANDLE_QEURY, &link_handle);
            app_bt_ull_connection_cancel(link_handle);
            app_bt_ull_connection_disconnect(link_handle, BT_HCI_ERR_REMOTE_USER_TERM_CONN);
            break;

        /* reconnect cancel flow or disconnect flow */
        case EVT_CMD_ULL_DISC_SUCCESS:
        case EVT_CMD_RECONNECT_CANCEL_SUCCESS:
        case EVT_CMD_DISCONNECT_BY_TARGET:
            app_events_reconnect_sub_state = APP_EVT_RECONNECT_IDLE;
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_HANDLE_QEURY, &link_handle);
            is_bt_connected = false;
            app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_BT_STATUS, &is_bt_connected);
            /* send disconnect notification to PC */
            app_race_pg_dongle_connection_report(link_handle, false, 0, RACE_SERIAL_PORT_TYPE_USB);
            // /* clear report rate change flag */
            // rr_change = false;
            // app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_REPORT_RATE_CHANGE_REQUEST, &rr_change);
            /* check usb status for next action */
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_USB_STATUS, &usb_status);
            if (usb_status == APP_PG_USB_PLUGOUT)
            {
                /* usb plugout case: goto deinit stage */
                app_pure_gaming_dongle_scenario_close(scenario_handle);
                app_state_change(APP_STATE_DEINIT, REASON_USB_PLUGOUT);
                /* clear scan request */
                app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_SCAN_REQUEST, &scan_request);
            }
            else if (usb_status == APP_PG_USB_SUSPEND)
            {
                /* usb suspend case: goto suspend stage */
                app_pure_gaming_dongle_scenario_entry_usb_suspend_case(scenario_handle);
                app_state_change(APP_STATE_SUSPEND, REASON_USB_SUSPEND);
                /* clear scan request */
                app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_SCAN_REQUEST, &scan_request);
            }
            else
            {
                /* other cases: goto disconnect stage */
                app_state_change(APP_STATE_DISCONNECTED, REASON_RECONNECT);
                /* check if need to do scan */
                app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_GET_SCAN_REQUEST, &scan_request);
                if (scan_request.request)
                {
                    app_events_send(EVT_CMD_ACL_SCAN_START_REQ, (void *)((uint32_t)(scan_request.timeout_ms)));
                    /* clear scan request */
                    scan_request.request = false;
                    scan_request.timeout_ms = 0;
                    app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_SCAN_REQUEST, &scan_request);
                }
            }
            break;
        case EVT_CMD_RECONNECT_CANCEL_FAIL:
            assert(0);
            break;

        /* usb case */
        case EVT_CMD_USB_PLUGIN:
        case EVT_CMD_USB_READY:
        case EVT_CMD_USB_RESUME:
        case EVT_CMD_USB_SUSPEND:
        case EVT_CMD_USB_PLUGOUT:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_usb_status_update_by_evt(scenario_handle, event->cmd);
            break;

        /* ignore reconnect by local request flow area */
        case EVT_CMD_RECONNECT_REQ:
            LOG_ERR("[app_hid_dongle] app_events_reconnect_cancel_stage_hdl ignore reconnect request");
            break;

        case EVT_CMD_ULL_SERVICE_CONN_REQ:
            LOG_ERR("[app_hid_dongle] app_events_reconnect_cancel_stage_hdl ignore ull service connnet request");
            break;

        /* scan request */
        case EVT_CMD_ACL_SCAN_START_REQ:
            /* In some case, dongle is reconnecting but tool considers that the device is disconnected,
               when tool sends scan cmd, we will do disconnect firstly and then pend scan cmd,
               after reconnect is canceld, we will send scan cmd again. */
            LOG_INF("[app_hid_dongle] app_events_reconnect_cancel_stage_hdl pending scan request");
            /* set scan request */
            scenario_handle = app_pure_gaming_dongle_scenario_get_current_context();
            scan_request.request = true;
            scan_request.timeout_ms = (uint32_t)(event->param);
            app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_SCAN_REQUEST, &scan_request);
            break;
        case EVT_CMD_ACL_SCAN_STOP_REQ:
            LOG_ERR("[app_hid_dongle] app_events_reconnect_cancel_stage_hdl ignore stop scan request");
            /* clear scan request */
            scenario_handle = app_pure_gaming_dongle_scenario_get_current_context();
            app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_SCAN_REQUEST, &scan_request);
            break;

        case EVT_CMD_REPORT_RATE_CHANGE_REQ:
        case EVT_CMD_OUTPUT_REPORT_CHANGE_REQ:
        case EVT_CMD_AUTO_SWITCH_REQ:
        case EVT_CMD_AUTO_SWITCH_CANCEL_REQ:
        case EVT_CMD_CIS_SCAN_DEVICE_FOUND:
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

/* Public functions ----------------------------------------------------------*/
int app_events_reconnect_stage_hdl(struct evt_cmd *event)
{
    if (app_events_reconnect_sub_state == APP_EVT_RECONNECT_IDLE)
    {
        /* pairing is not running flow */
        app_events_reconnect_idle_stage_hdl(event);
    }
    else if (app_events_reconnect_sub_state == APP_EVT_RECONNECT_RUNNING)
    {
        /* pairing is running flow */
        app_events_reconnect_running_stage_hdl(event);
    }
    else if (app_events_reconnect_sub_state == APP_EVT_RECONNECT_CANCEL)
    {
        /* pairing is canceling flow */
        app_events_reconnect_cancel_stage_hdl(event);
    }

    return 0;
}

#endif /* AIR_PURE_GAMING_DONGLE_ENABLE */
