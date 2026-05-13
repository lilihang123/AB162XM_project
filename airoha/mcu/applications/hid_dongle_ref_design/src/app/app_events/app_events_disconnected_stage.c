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
#include "app_pure_gaming_dongle_scenario.h"
#include "app_bt_conn_manager.h"
#include "app_acl_conn.h"
#include "app_bt_ull_conn.h"
#include "assert.h"
#include "app_events.h"
#include "errno.h"

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
int app_events_disconnected_stage_hdl(struct evt_cmd *event)
{
    // app_bt_conn_handle_t *link_handle;
    app_pg_scenario_handle_t *scenario_handle;
    app_bt_conn_status_t link_status;
    app_bt_conn_device_found_t *dev_found;
    // bool rr_change;

    switch (event->cmd)
    {
        /* scan case */
        case EVT_CMD_ACL_SCAN_START_REQ:
            app_pure_gaming_dongle_scenario_suspend_timer_stop();
            app_state_change(APP_STATE_SCAN, REASON_SCAN_CMD);
            app_events_send(EVT_CMD_ACL_SCAN_START_REQ, event->param);
            break;
        case EVT_CMD_ACL_SCAN_STOP_REQ:
            app_pure_gaming_dongle_scenario_suspend_timer_stop();
            /* do nothing */
            break;
        case EVT_CMD_ACL_DEVICE_FOUND:
            app_pure_gaming_dongle_scenario_suspend_timer_stop();
            /* device found is not late case */
#if defined(AIR_PURE_GAMING_DONGLE_MS_ENABLE)
            dev_found = app_bt_acl_connection_get_found_device(APP_BT_CONN_ROLE_MOUSE, K_NO_WAIT);
#elif defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
            dev_found = app_bt_acl_connection_get_found_device(APP_BT_CONN_ROLE_GAMEPAD, K_NO_WAIT);
#else
            dev_found = app_bt_acl_connection_get_found_device(APP_BT_CONN_ROLE_KEYBOARD, K_NO_WAIT);
#endif /* AIR_PURE_GAMING_DONGLE_MS_ENABLE */
            assert(dev_found != NULL);
            LOG_INF("app_events_disconnected_stage_hdl get device is too late, address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x, rssi = %d, adv_type = %u",
                    dev_found->addr.a.val[5],
                    dev_found->addr.a.val[4],
                    dev_found->addr.a.val[3],
                    dev_found->addr.a.val[2],
                    dev_found->addr.a.val[1],
                    dev_found->addr.a.val[0],
                    dev_found->rssi,
                    dev_found->adv_type);
            app_bt_conn_manager_free(dev_found);
            break;

        /* pairing case */
        case EVT_CMD_ACL_PAIR_REQ:
            app_pure_gaming_dongle_scenario_suspend_timer_stop();
            // app_bt_acl_connection_stop_scan();
            app_state_change(APP_STATE_PAIRING, REASON_PAIR_CMD);
            app_events_send(EVT_CMD_ACL_CONN_REQ, event->param);
            break;

        /* reconnect case */
        case EVT_CMD_RECONNECT_REQ:
            app_pure_gaming_dongle_scenario_suspend_timer_stop();
            app_state_change(APP_STATE_RECONNECT, REASON_RECONNECT);
            app_events_send(EVT_CMD_RECONNECT_REQ, event->param);
            break;

        /* usb ready case */
        case EVT_CMD_USB_READY:
            app_pure_gaming_dongle_scenario_suspend_timer_stop();
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_usb_status_update_by_evt(scenario_handle, event->cmd);
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_GET_ULL_LINK_STATUS, &link_status);
            if (link_status == APP_BT_CONN_STATUS_BONDED)
            {
                /* if has bonded address, try to reconnect */
                app_events_send(EVT_CMD_RECONNECT_REQ, scenario_handle);
            }
            break;

        /* usb plugout case */
        case EVT_CMD_USB_PLUGOUT:
            app_pure_gaming_dongle_scenario_suspend_timer_stop();
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_usb_status_update_by_evt(scenario_handle, event->cmd);
            app_pure_gaming_dongle_scenario_close(scenario_handle);
            app_state_change(APP_STATE_DEINIT, REASON_USB_PLUGOUT);
            break;

        /* usb case */
        case EVT_CMD_USB_SUSPEND:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_usb_status_update_by_evt(scenario_handle, event->cmd);
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_GET_ULL_LINK_STATUS, &link_status);
            if (link_status == APP_BT_CONN_STATUS_BONDED)
            {
                /* if has bonded address, start suspend check timer */
                app_pure_gaming_dongle_scenario_suspend_timer_start();
            }
            break;

        case EVT_CMD_USB_PLUGIN:
        case EVT_CMD_USB_RESUME:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_usb_status_update_by_evt(scenario_handle, event->cmd);
            break;

#if 0
        /* old flow: report rate changed will need disconnect link */
        /* report rate change case: normal flow area one by one */
        case EVT_CMD_REPORT_RATE_CHANGE_REQ:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_HANDLE_QEURY, &link_handle);
            if (app_bt_ull_connection_remove_cig(link_handle) == ENXIO)
            {
                /* clear report rate change flag */
                rr_change = false;
                app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_REPORT_RATE_CHANGE_REQUEST, &rr_change);
                /* trigger reconnet */
                app_state_change(APP_STATE_RECONNECT, REASON_RECONNECT);
                app_events_send(EVT_CMD_RECONNECT_REQ, event->param);
            }
            break;
        case EVT_CMD_REMOVE_CIG_SUCCESS:
            scenario_handle = (app_pg_scenario_handle_t *)(event->param);
            /* clear report rate change flag */
            rr_change = false;
            app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_REPORT_RATE_CHANGE_REQUEST, &rr_change);
            /* trigger reconnet */
            app_state_change(APP_STATE_RECONNECT, REASON_RECONNECT);
            app_events_send(EVT_CMD_RECONNECT_REQ, event->param);
            break;
        /* report rate change fail case: error handle area */
        case EVT_CMD_REMOVE_CIG_FAIL:
            assert(0);
            break;
#else
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
#endif

        /* disconnect case */
        case EVT_CMD_DISCONNECT_REQ:
        case EVT_CMD_RECONNECT_SUCCESS:
        case EVT_CMD_RUNNING:
        case EVT_CMD_ULL_CONN_REQ:
        case EVT_CMD_ULL_SERVICE_CONN_REQ:
            /* ignore this event because has been disconnected */
            break;

        default:
            assert(0);
            break;
    }

    return 0;
}

#endif /* AIR_PURE_GAMING_DONGLE_ENABLE */
