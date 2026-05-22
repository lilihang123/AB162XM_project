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
#include "app_events.h"
#include "app_pure_gaming_dongle_scenario.h"
#include "race_cmd.h"
#include "race_xport.h"
#include "app_race_cmd_event.h"
#include "app_race_cmd_pure_gaming_dongle.h"
#include "hal_gpt.h"
#if defined(AIR_PURE_GAMING_FAST_PAIR_ENABLE)
#include "app_fast_pair.h"
#endif /* AIR_PURE_GAMING_FAST_PAIR_ENABLE */
#include "errno.h"

/* Private define ------------------------------------------------------------*/
#define thisMODULE app_events
#define thisMOD    "app_events"
LOG_MODULE_DECLARE(thisMODULE);

/* Private typedef -----------------------------------------------------------*/
typedef uint8_t app_evt_pair_sub_state_t;
#define APP_EVT_PAIR_IDLE           0x00
#define APP_EVT_PAIR_RUNNING        0x01
#define APP_EVT_PAIR_ERROR          0x02
#define APP_EVT_PAIR_CANCEL         0x03

/* Private macro -------------------------------------------------------------*/
#define APP_EVENTS_PAIRING_TIMEOUT_MS   30100

/* Private variables ---------------------------------------------------------*/
static uint32_t app_events_pairing_timer;
static bool app_events_pairing_timer_is_enable;
static app_evt_pair_sub_state_t app_events_pair_sub_state = APP_EVT_PAIR_IDLE;

/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void app_events_pairing_timer_cb(void *user_data)
{
    /* send event to alert pair fail */
    app_events_send(EVT_CMD_ACL_PAIR_TIMEOUT, user_data);
}

static int app_events_pairing_timer_start(uint32_t timeout_ms, app_pg_scenario_handle_t *scenario_handle)
{
    int err = 0;

    if (!app_events_pairing_timer_is_enable)
    {
        hal_gpt_sw_get_timer(&app_events_pairing_timer);
        if(HAL_GPT_STATUS_OK != hal_gpt_sw_start_timer_ms(app_events_pairing_timer, timeout_ms, app_events_pairing_timer_cb, scenario_handle))
        {
            assert(0);
        }
        app_events_pairing_timer_is_enable = true;
    }

    LOG_INF("[app_hid_dongle] Pairing Timer successfully start. timer 0x%x, timeout_ms %u", app_events_pairing_timer, timeout_ms);

    return err;
}

static int app_events_pairing_timer_stop(void)
{
    int err = 0;

    if (app_events_pairing_timer_is_enable)
    {
        hal_gpt_sw_stop_timer_ms(app_events_pairing_timer);
        hal_gpt_sw_free_timer(app_events_pairing_timer);
        app_events_pairing_timer_is_enable = false;
    }

    LOG_INF("[app_hid_dongle] Pairing Timer successfully stopped.");

    return err;
}

static int app_events_pairing_idle_stage_hdl(struct evt_cmd *event)
{
    app_pg_scenario_handle_t *scenario_handle;
    app_bt_conn_device_found_t *device_pair;
    app_bt_conn_handle_t *link_handle;
    app_bt_conn_handle_t *temp_handle;
    app_bt_conn_device_found_t *dev_found;

    switch (event->cmd)
    {
        /* pair flow area */
        case EVT_CMD_ACL_PAIR_REQ:
        case EVT_CMD_ACL_CONN_REQ:
            device_pair = (app_bt_conn_device_found_t *)(event->param);
            /* update temp link handle */
            temp_handle = app_bt_conn_manager_get_handle(device_pair->role);
            assert(temp_handle != NULL);
            scenario_handle = app_pure_gaming_dongle_scenario_get_handle_by_role(device_pair->role);
            assert(scenario_handle != NULL);
            app_bt_conn_manager_set_handle_addr(temp_handle, APP_BT_CONN_TYPE_ACL, &(device_pair->addr));
            app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_TEMP_BT_HANDLE_UPDATE, temp_handle);
            app_bt_conn_manager_set_scenario_handle(temp_handle, scenario_handle);
            /* disable the current link handle because maybe the the current device address is as the same as the new device address */
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_HANDLE_QEURY, &link_handle);
            app_bt_conn_manager_set_handle_disable(link_handle, APP_BT_CONN_TYPE_ACL, true);
            app_bt_conn_manager_set_handle_disable(link_handle, APP_BT_CONN_TYPE_ULL, true);
            /* try to connect new device */
            app_events_pair_sub_state = APP_EVT_PAIR_RUNNING;
            if (app_bt_ull_connection_remove_cig(temp_handle) == ENXIO)
            {
                app_bt_acl_connection_connect(temp_handle);
            }
            app_events_pairing_timer_start(APP_EVENTS_PAIRING_TIMEOUT_MS, scenario_handle);
            app_bt_conn_manager_free(device_pair);
            break;

        case EVT_CMD_ACL_PAIR_FAIL:
            break;

        case EVT_CMD_ACL_SCAN_START_REQ:
            /* pariing fail, trigger re-scan */
            app_state_change(APP_STATE_SCAN, REASON_SCAN_CMD);
            app_events_send(EVT_CMD_ACL_SCAN_START_REQ, event->param);
            break;
        case EVT_CMD_ACL_SCAN_STOP_REQ:
            /* do nothing */
            break;
        case EVT_CMD_ACL_DEVICE_FOUND:
            /* mutil device found case */
#if defined(AIR_PURE_GAMING_DONGLE_MS_ENABLE)
            dev_found = app_bt_acl_connection_get_found_device(APP_BT_CONN_ROLE_MOUSE, K_NO_WAIT);
#elif defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
            dev_found = app_bt_acl_connection_get_found_device(APP_BT_CONN_ROLE_GAMEPAD, K_NO_WAIT);
#else
            dev_found = app_bt_acl_connection_get_found_device(APP_BT_CONN_ROLE_KEYBOARD, K_NO_WAIT);
#endif /* AIR_PURE_GAMING_DONGLE_MS_ENABLE */
            if(dev_found != NULL)
            {
                LOG_INF("app_events_pairing_idle_stage_hdl get mutil device, address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x, rssi = %d, adv_type = %u",
                        dev_found->addr.a.val[5],
                        dev_found->addr.a.val[4],
                        dev_found->addr.a.val[3],
                        dev_found->addr.a.val[2],
                        dev_found->addr.a.val[1],
                        dev_found->addr.a.val[0],
                        dev_found->rssi,
                        dev_found->adv_type);
                app_bt_conn_manager_free(dev_found);
            }
            break;
        /* usb case */
        case EVT_CMD_USB_PLUGIN:
        case EVT_CMD_USB_PLUGOUT:
        case EVT_CMD_USB_READY:
        case EVT_CMD_USB_SUSPEND:
        case EVT_CMD_USB_RESUME:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_usb_status_update_by_evt(scenario_handle, event->cmd);
            break;

        case EVT_CMD_REPORT_RATE_CHANGE_REQ:
        case EVT_CMD_OUTPUT_REPORT_CHANGE_REQ:
        case EVT_CMD_AUTO_SWITCH_REQ:
        case EVT_CMD_AUTO_SWITCH_CANCEL_REQ:
        case EVT_CMD_CIS_SCAN_DEVICE_FOUND:
            // scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            // /* clear report rate change flag */
            // bool rr_change = false;
            // app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_REPORT_RATE_CHANGE_REQUEST, &rr_change);
            break;

        default:
            assert(0);
            break;
    }

    return 0;
}

static int app_events_pairing_running_stage_hdl(struct evt_cmd *event)
{
    app_bt_conn_handle_t *link_handle;
    app_pg_scenario_handle_t *scenario_handle;
    app_bt_conn_device_found_t *dev_found;
    // bool rr_change;

    switch (event->cmd)
    {
        /* pair success case: normal flow area one by one */
        case EVT_CMD_REMOVE_CIG_SUCCESS:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_TEMP_BT_HANDLE_QEURY, &link_handle);
            app_bt_acl_connection_connect(link_handle);
            break;
        case EVT_CMD_ACL_CONN_SUCCESS:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_TEMP_BT_HANDLE_QEURY, &link_handle);
            uint16_t report_rate = CONFIG_AIR_PURE_GAMING_DEFAULT_REPORT_RATE;
            app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_REPORT_RATE, &report_rate);
            app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_SCENARIO, &report_rate);
            app_events_send(EVT_CMD_ACL_SEC_UPDATE_REQ, event->param);
            break;
        case EVT_CMD_ACL_SEC_UPDATE_REQ:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_TEMP_BT_HANDLE_QEURY, &link_handle);
            app_bt_acl_security_change(link_handle);
            break;
        case EVT_CMD_ACL_SEC_UPDATE_SUCCESS:
            app_events_send(EVT_CMD_ULL_BOND_REQ, event->param);
            break;
        case EVT_CMD_ULL_BOND_REQ:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_TEMP_BT_HANDLE_QEURY, &link_handle);
            app_bt_ull_connection_bond(link_handle);
            break;
        case EVT_CMD_ULL_BOND_SUCCESS:
            app_events_send(EVT_CMD_ACL_DISC_REQ, event->param);
            break;
        case EVT_CMD_ACL_DISC_REQ:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_TEMP_BT_HANDLE_QEURY, &link_handle);
            app_bt_acl_connection_disconnect(link_handle);
            break;
        case EVT_CMD_ACL_DISC_SUCCESS:
            /* ACL discconect becauuse need do CIS link */
            app_events_send(EVT_CMD_ULL_CONN_REQ, event->param);
            break;
        case EVT_CMD_ULL_CONN_REQ:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            // /* clear report rate change flag */
            // rr_change = false;
            // app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_REPORT_RATE_CHANGE_REQUEST, &rr_change);
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_TEMP_BT_HANDLE_QEURY, &link_handle);
            app_bt_ull_connection_connect_device(link_handle);
            break;
        case EVT_CMD_ULL_CONN_SUCCESS:
            app_events_send(EVT_CMD_ULL_SERVICE_CONN_REQ, event->param);
            break;
        case EVT_CMD_ULL_SERVICE_CONN_REQ:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            // app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_TEMP_BT_HANDLE_QEURY, &link_handle);
            // app_bt_ull_connection_connect_service(link_handle);
            /* TODO: Temp Solution, sometime connect service is not ready */
            app_events_send(EVT_CMD_ACL_PAIR_SUCCESS, scenario_handle);
            break;
        case EVT_CMD_ULL_SERVICE_CONN_SUCCESS:
            app_events_send(EVT_CMD_ACL_PAIR_SUCCESS, event->param);
            break;
        case EVT_CMD_ACL_PAIR_SUCCESS:
            app_events_pairing_timer_stop();
            app_events_pair_sub_state = APP_EVT_PAIR_IDLE;
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            /* enable the current link handle because it is disabled when pairing is running */
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_HANDLE_QEURY, &link_handle);
            app_bt_conn_manager_set_handle_disable(link_handle, APP_BT_CONN_TYPE_ACL, false);
            app_bt_conn_manager_set_handle_disable(link_handle, APP_BT_CONN_TYPE_ULL, false);
            /* update scenario handle with new connection handle */
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_TEMP_BT_HANDLE_QEURY, &link_handle);
            app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_BT_HANDLE_UPDATE,link_handle);
            bool is_bt_connected = true;
            app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_BT_STATUS, &is_bt_connected);
            /* send connect success notification to PC */
            app_race_pg_dongle_connection_report(link_handle, true, 0, RACE_SERIAL_PORT_TYPE_USB);
            /* trigger the next flow */
            app_state_change(APP_STATE_CONNECTED, REASON_PAIR_CMD);
#if defined(AIR_PURE_GAMING_FAST_PAIR_ENABLE)
            if (app_fast_pair_mode_is_running())
            {
                /* the device is connected by fast pair, we need to waiting USB Ready for exit fast par mode */
                /* allow all events at now */
                app_events_resume_all_events();
            }
            else
#endif /* AIR_PURE_GAMING_FAST_PAIR_ENABLE */
            {
                app_events_send(EVT_CMD_RUNNING, scenario_handle);
            }
            break;
        /* pair fail case: error handle area */
        case EVT_CMD_REMOVE_CIG_FAIL:
        case EVT_CMD_ACL_CONN_FAIL:
        case EVT_CMD_ACL_SEC_UPDATE_FAIL:
        case EVT_CMD_ACL_DISC_ERR:
        case EVT_CMD_ULL_BOND_FAIL:
        case EVT_CMD_ACL_DISC_FAIL:
        case EVT_CMD_ULL_CONN_FAIL:
        case EVT_CMD_ULL_SERVICE_CONN_FAIL:
        case EVT_CMD_DISCONNECT_BY_TARGET:
            app_events_pairing_timer_stop();
            app_events_pair_sub_state = APP_EVT_PAIR_ERROR;
            app_events_send(EVT_CMD_ACL_PAIR_FAIL, event->param);
            break;
        case EVT_CMD_ACL_PAIR_TIMEOUT:
            app_events_pairing_timer_stop();
            app_events_pair_sub_state = APP_EVT_PAIR_CANCEL;
            app_events_send(EVT_CMD_ACL_PAIR_TIMEOUT, event->param);
            break;

        /* usb case */
        case EVT_CMD_USB_PLUGIN:
        case EVT_CMD_USB_PLUGOUT:
        case EVT_CMD_USB_READY:
        case EVT_CMD_USB_SUSPEND:
        case EVT_CMD_USB_RESUME:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_usb_status_update_by_evt(scenario_handle, event->cmd);
            break;

        case EVT_CMD_ACL_SCAN_START_REQ:
        case EVT_CMD_ACL_SCAN_STOP_REQ:
        case EVT_CMD_ACL_PAIR_REQ:
            /* do nothing */
            break;
        case EVT_CMD_ACL_CONN_REQ:
            /* mutil device found case */
#if defined(AIR_PURE_GAMING_DONGLE_MS_ENABLE)
            dev_found = app_bt_acl_connection_get_found_device(APP_BT_CONN_ROLE_MOUSE, K_NO_WAIT);
#elif defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
            dev_found = app_bt_acl_connection_get_found_device(APP_BT_CONN_ROLE_GAMEPAD, K_NO_WAIT);
#else
            dev_found = app_bt_acl_connection_get_found_device(APP_BT_CONN_ROLE_KEYBOARD, K_NO_WAIT);
#endif /* AIR_PURE_GAMING_DONGLE_MS_ENABLE */
            if(dev_found != NULL)
            {
                LOG_INF("app_events_pairing_idle_stage_hdl get mutil device, address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x, rssi = %d, adv_type = %u",
                        dev_found->addr.a.val[5],
                        dev_found->addr.a.val[4],
                        dev_found->addr.a.val[3],
                        dev_found->addr.a.val[2],
                        dev_found->addr.a.val[1],
                        dev_found->addr.a.val[0],
                        dev_found->rssi,
                        dev_found->adv_type);
                app_bt_conn_manager_free(dev_found);
            }
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

static int app_events_pairing_error_stage_hdl(struct evt_cmd *event)
{
    app_bt_conn_handle_t *link_handle;
    app_pg_scenario_handle_t *scenario_handle;

    switch (event->cmd)
    {
        /* pair fail case: error handle area */
        case EVT_CMD_REMOVE_CIG_FAIL:
        case EVT_CMD_ACL_CONN_FAIL:
        case EVT_CMD_ACL_SEC_UPDATE_FAIL:
        case EVT_CMD_ACL_DISC_ERR:
        case EVT_CMD_ULL_BOND_FAIL:
        case EVT_CMD_ACL_DISC_FAIL:
        case EVT_CMD_ULL_CONN_FAIL:
        case EVT_CMD_ULL_SERVICE_CONN_FAIL:
            break;

        case EVT_CMD_ACL_PAIR_FAIL:
            app_events_pair_sub_state = APP_EVT_PAIR_IDLE;
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            /* free the temp link handler */
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_TEMP_BT_HANDLE_QEURY, &link_handle);
            app_bt_conn_manager_release_handle(link_handle);
            /* enable the current link handle because it is disabled when pairing is running */
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_HANDLE_QEURY, &link_handle);
            app_bt_conn_manager_set_handle_disable(link_handle, APP_BT_CONN_TYPE_ACL, false);
            app_bt_conn_manager_set_handle_disable(link_handle, APP_BT_CONN_TYPE_ULL, false);
            /* change to the next stage */
            app_state_change(APP_STATE_DISCONNECTED, REASON_PAIR_CMD);
#if defined(AIR_PURE_GAMING_FAST_PAIR_ENABLE)
            if (app_fast_pair_mode_is_running())
            {
                app_fast_pair_mode_exit();
                /* allow all events at now */
                app_events_resume_all_events();
            }
#endif /* AIR_PURE_GAMING_FAST_PAIR_ENABLE */
            break;

        /* usb case */
        case EVT_CMD_USB_PLUGIN:
        case EVT_CMD_USB_PLUGOUT:
        case EVT_CMD_USB_READY:
        case EVT_CMD_USB_SUSPEND:
        case EVT_CMD_USB_RESUME:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_usb_status_update_by_evt(scenario_handle, event->cmd);
            break;

        case EVT_CMD_ACL_SCAN_START_REQ:
        case EVT_CMD_ACL_SCAN_STOP_REQ:
        case EVT_CMD_ACL_PAIR_SUCCESS:
        case EVT_CMD_ULL_SERVICE_CONN_REQ:
            /* do nothing */
            break;

        case EVT_CMD_REPORT_RATE_CHANGE_REQ:
        case EVT_CMD_OUTPUT_REPORT_CHANGE_REQ:
        case EVT_CMD_AUTO_SWITCH_REQ:
        case EVT_CMD_AUTO_SWITCH_CANCEL_REQ:
        case EVT_CMD_CIS_SCAN_DEVICE_FOUND:
            // scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            // /* clear report rate change flag */
            // bool rr_change = false;
            // app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_REPORT_RATE_CHANGE_REQUEST, &rr_change);
            break;

        default:
            assert(0);
            break;
    }

    return 0;
}

static int app_events_pairing_cancel_stage_hdl(struct evt_cmd *event)
{
    app_bt_conn_handle_t *link_handle;
    app_pg_scenario_handle_t *scenario_handle;
    int ret0 = -1;
    int ret1 = -1;
    int ret2 = -1;

    switch (event->cmd)
    {
        case EVT_CMD_ACL_PAIR_TIMEOUT:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_TEMP_BT_HANDLE_QEURY, &link_handle);
            if (link_handle->ull_status >= APP_BT_CONN_STATUS_BONDED)
            {
                ret0 = app_bt_ull_connection_cancel(link_handle);
                ret1 = app_bt_ull_connection_disconnect(link_handle, BT_HCI_ERR_REMOTE_USER_TERM_CONN);
            }
            if (link_handle->acl_status > APP_BT_CONN_STATUS_DISCONNECTED)
            {
                ret2 = app_bt_acl_connection_disconnect(link_handle);
            }
            if ((ret0 < 0) && (ret1 < 0) && (ret2 < 0))
            {
                app_events_send(EVT_CMD_ACL_PAIR_FAIL, event->param);
            }
            break;

        case EVT_CMD_RECONNECT_CANCEL_SUCCESS:
            app_events_send(EVT_CMD_ACL_PAIR_FAIL, event->param);
            break;

        case EVT_CMD_ACL_SEC_UPDATE_FAIL:
            /* do nothing */
            break;

        case EVT_CMD_ACL_DISC_SUCCESS:
        case EVT_CMD_ULL_DISC_SUCCESS:
            /* ACL or ULL discconect becauuse pairing timeout */
            app_events_send(EVT_CMD_ACL_PAIR_FAIL, event->param);
            break;

        case EVT_CMD_ACL_PAIR_FAIL:
            app_events_pairing_timer_stop();
            app_events_pair_sub_state = APP_EVT_PAIR_IDLE;
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            /* free the temp link handler */
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_TEMP_BT_HANDLE_QEURY, &link_handle);
            app_bt_conn_manager_release_handle(link_handle);
            /* enable the current link handle because it is disabled when pairing is running */
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_HANDLE_QEURY, &link_handle);
            app_bt_conn_manager_set_handle_disable(link_handle, APP_BT_CONN_TYPE_ACL, false);
            app_bt_conn_manager_set_handle_disable(link_handle, APP_BT_CONN_TYPE_ULL, false);
            /* change to the next stage */
            app_state_change(APP_STATE_DISCONNECTED, REASON_PAIR_CMD);
#if defined(AIR_PURE_GAMING_FAST_PAIR_ENABLE)
            if (app_fast_pair_mode_is_running())
            {
                app_fast_pair_mode_exit();
                /* allow all events at now */
                app_events_resume_all_events();
            }
#endif /* AIR_PURE_GAMING_FAST_PAIR_ENABLE */
            break;

        /* usb case */
        case EVT_CMD_USB_PLUGIN:
        case EVT_CMD_USB_PLUGOUT:
        case EVT_CMD_USB_READY:
        case EVT_CMD_USB_SUSPEND:
        case EVT_CMD_USB_RESUME:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_usb_status_update_by_evt(scenario_handle, event->cmd);
            break;

        case EVT_CMD_ACL_SCAN_START_REQ:
        case EVT_CMD_ACL_SCAN_STOP_REQ:
            /* do nothing */
            break;

        case EVT_CMD_REPORT_RATE_CHANGE_REQ:
        case EVT_CMD_OUTPUT_REPORT_CHANGE_REQ:
        case EVT_CMD_AUTO_SWITCH_REQ:
        case EVT_CMD_AUTO_SWITCH_CANCEL_REQ:
        case EVT_CMD_CIS_SCAN_DEVICE_FOUND:
            // scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            // /* clear report rate change flag */
            // bool rr_change = false;
            // app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_REPORT_RATE_CHANGE_REQUEST, &rr_change);
            break;

        default:
            assert(0);
            break;
    }

    return 0;
}

/* Public functions ----------------------------------------------------------*/
int app_events_pairing_stage_hdl(struct evt_cmd *event)
{
    if (app_events_pair_sub_state == APP_EVT_PAIR_IDLE)
    {
        /* pairing is not running flow */
        app_events_pairing_idle_stage_hdl(event);
    }
    else if (app_events_pair_sub_state == APP_EVT_PAIR_RUNNING)
    {
        /* pairing is running flow */
        app_events_pairing_running_stage_hdl(event);
    }
    else if (app_events_pair_sub_state == APP_EVT_PAIR_ERROR)
    {
        /* pairing is canceling flow */
        app_events_pairing_error_stage_hdl(event);
    }
    else if (app_events_pair_sub_state == APP_EVT_PAIR_CANCEL)
    {
        /* pairing is canceling flow */
        app_events_pairing_cancel_stage_hdl(event);
    }

    return 0;
}

#endif /* AIR_PURE_GAMING_DONGLE_ENABLE */
