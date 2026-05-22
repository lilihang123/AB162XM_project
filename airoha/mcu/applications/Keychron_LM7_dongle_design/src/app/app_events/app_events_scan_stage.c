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
#include "app_events.h"
#include "assert.h"
#include "app_pure_gaming_dongle_scenario.h"
#include "race_cmd.h"
#include "race_xport.h"
#include "app_race_cmd_event.h"
#include "app_race_cmd_pure_gaming_dongle.h"
#if defined(AIR_PURE_GAMING_FAST_PAIR_ENABLE)
#include "app_fast_pair.h"
#endif /* AIR_PURE_GAMING_FAST_PAIR_ENABLE */

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
int app_events_scan_stage_hdl(struct evt_cmd *event)
{
    app_bt_conn_device_found_t *dev_found;
    app_pg_scenario_handle_t *scenario_handle;
    uint32_t timeout_ms;

    switch (event->cmd)
    {
        case EVT_CMD_ACL_SCAN_START_REQ:
            timeout_ms = (uint32_t)(event->param);
            app_bt_acl_connection_start_scan(timeout_ms);
            break;

        case EVT_CMD_ACL_SCAN_STOP_REQ:
            app_bt_acl_connection_stop_scan();
#if defined(AIR_PURE_GAMING_FAST_PAIR_ENABLE)
            if (app_fast_pair_mode_is_running())
            {
                if ((app_fast_pair_mode_device_flag_get() & APP_FAST_PAIR_DEVICE_FOUND_FLAG) != 0)
                {
                    app_fast_pair_mode_device_flag_clear(APP_FAST_PAIR_DEVICE_FOUND_FLAG);
                }
                else
                {
                    app_state_change(APP_STATE_DISCONNECTED, REASON_SCAN_CMD);
                    app_fast_pair_mode_exit();
                    /* allow all events at now */
                    app_events_resume_all_events();
                }
            }
#endif /* AIR_PURE_GAMING_FAST_PAIR_ENABLE */
            break;

        /* device found case */
        case EVT_CMD_ACL_DEVICE_FOUND:
#if defined(AIR_PURE_GAMING_DONGLE_MS_ENABLE)
            dev_found = app_bt_acl_connection_get_found_device(APP_BT_CONN_ROLE_MOUSE, K_NO_WAIT);
#elif defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
            dev_found = app_bt_acl_connection_get_found_device(APP_BT_CONN_ROLE_GAMEPAD, K_NO_WAIT);
#else
            dev_found = app_bt_acl_connection_get_found_device(APP_BT_CONN_ROLE_KEYBOARD, K_NO_WAIT);
#endif /* AIR_PURE_GAMING_DONGLE_MS_ENABLE */
            assert(dev_found != NULL);
            LOG_INF("app_events_scan_stage_hdl get device, address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x, rssi = %d, adv_type = %u",
                    dev_found->addr.a.val[5],
                    dev_found->addr.a.val[4],
                    dev_found->addr.a.val[3],
                    dev_found->addr.a.val[2],
                    dev_found->addr.a.val[1],
                    dev_found->addr.a.val[0],
                    dev_found->rssi,
                    dev_found->adv_type);
#if defined(AIR_PURE_GAMING_FAST_PAIR_ENABLE)
            if (app_fast_pair_mode_is_running())
            {
                if (dev_found->rssi >= APP_FAST_PAIR_SCAN_THRESHOLD)
                {
                    app_fast_pair_mode_device_flag_set(APP_FAST_PAIR_DEVICE_FOUND_FLAG);
                    app_events_send(EVT_CMD_ACL_SCAN_STOP_REQ, NULL);
                    /* the device rssi is enough, need to pair this device */
                    app_bt_conn_device_found_t *fast_pair_dev_found = (app_bt_conn_device_found_t *)app_bt_conn_manager_malloc(sizeof(app_bt_conn_device_found_t));
                    memcpy(&(fast_pair_dev_found->addr), &(dev_found->addr), sizeof(bt_addr_le_t));
#if defined(AIR_PURE_GAMING_DONGLE_MS_ENABLE)
                    fast_pair_dev_found->role = APP_BT_CONN_ROLE_MOUSE;
#elif defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
                    fast_pair_dev_found->role = APP_BT_CONN_ROLE_GAMEPAD;
#else
                    fast_pair_dev_found->role = APP_BT_CONN_ROLE_KEYBOARD;
#endif /* AIR_PURE_GAMING_DONGLE_MS_ENABLE */
                    app_events_send(EVT_CMD_ACL_PAIR_REQ, fast_pair_dev_found);
                    fast_pair_dev_found->rssi = dev_found->rssi;
                    LOG_INF("app_events_scan_stage_hdl fast pair get device, address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x, rssi = %d, adv_type = %u",
                            fast_pair_dev_found->addr.a.val[5],
                            fast_pair_dev_found->addr.a.val[4],
                            fast_pair_dev_found->addr.a.val[3],
                            fast_pair_dev_found->addr.a.val[2],
                            fast_pair_dev_found->addr.a.val[1],
                            fast_pair_dev_found->addr.a.val[0],
                            fast_pair_dev_found->rssi,
                            fast_pair_dev_found->adv_type);
                }
                app_bt_conn_manager_free(dev_found);
                break;
            }
#endif /* AIR_PURE_GAMING_FAST_PAIR_ENABLE */
            /* send to PC */
            app_race_pg_dongle_adv_report(dev_found, RACE_SERIAL_PORT_TYPE_USB);
            app_bt_conn_manager_free(dev_found);
            break;

        /* pairing case */
        case EVT_CMD_ACL_PAIR_REQ:
            // app_bt_acl_connection_stop_scan();
            app_state_change(APP_STATE_PAIRING, REASON_PAIR_CMD);
            app_events_send(EVT_CMD_ACL_CONN_REQ, event->param);
            break;

        /* reconnect case */
        case EVT_CMD_RECONNECT_REQ:
            if (app_bt_acl_connection_scan_is_running() == false)
            {
                app_state_change(APP_STATE_RECONNECT, REASON_RECONNECT);
                app_events_send(EVT_CMD_RECONNECT_REQ, event->param);
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

        case EVT_CMD_DISCONNECT_REQ:
            /*ignore disconnect request*/
            LOG_ERR("[app_hid_dongle] app_events_scan_stage_hdl ignore disconnect request");
            break;

        default:
            assert(0);
            break;
    }

    return 0;
}

#endif /* AIR_PURE_GAMING_DONGLE_ENABLE */
