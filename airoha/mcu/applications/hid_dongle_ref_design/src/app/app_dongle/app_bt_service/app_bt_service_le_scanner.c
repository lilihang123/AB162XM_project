
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

#include "app_bt_service_le_scanner.h"

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/logging/log.h>
#include "host/conn_internal.h"

#include "app_dongle_cm_config.h"

#include "app_debug.h"
#include "app_dongle_event.h"
#include "app_porting.h"


/**================================================================================*/
/**                              Definition & Structure                            */
/**================================================================================*/
#define LOG_TAG             "[APP_DONGLE][BT_SRV][LE_SCAN]"

static app_bt_service_le_scanner_found_cb_t             app_bt_service_le_scanner_found_cb = NULL;



/**================================================================================*/
/**                                   Internal API                                 */
/**================================================================================*/
static void app_bt_service_le_scanner_found_callback(const bt_addr_le_t *addr, int8_t rssi, uint8_t adv_type, struct net_buf_simple *buf)
{
    if (addr == NULL || buf == NULL) {
        //APPS_LOG_MSGID_E(LOG_TAG" le_scanner_found_cb, error addr=0x%08X buf=0x%08X", 2, addr, buf);
        return;
    } else if (adv_type == BT_GAP_ADV_TYPE_ADV_SCAN_IND || adv_type == BT_GAP_ADV_TYPE_ADV_NONCONN_IND || adv_type == BT_GAP_ADV_TYPE_SCAN_RSP) {
        //APPS_LOG_MSGID_E(LOG_TAG" le_scanner_found_cb, non-connectable adv_type=%d", 1, adv_type);
        return;
    }
#ifdef APP_DONGLE_CM_LE_SCANNER_IGNORE_LONG_DISTANCE_DEVICE
    else if (rssi < APP_DONGLE_CM_LE_SCANNER_LONG_DISTANCE_RSSI) {
        //APPS_LOG_MSGID_E(LOG_TAG" le_scanner_found_cb, rssi %d < %d", 2, rssi, APP_DONGLE_CM_LE_SCANNER_LONG_DISTANCE_RSSI);
        return;
    }
#endif

#if 0
    // Only accept fixed addr
    uint8_t *filter_addr = (uint8_t *)addr->a.val;
    if (filter_addr[5] == 0xC4 && filter_addr[4] == 0x87 && filter_addr[3] == 0xAB
        && filter_addr[2] == 0x34 /*&& filter_addr[1] == 0xBF*/ && filter_addr[0] == 0xDA) {
        APPS_LOG_MSGID_E(LOG_TAG" le_scanner_found_cb, found addr=%02X:%02X:%02X:%02X:%02X:%02X",
                         6, filter_addr[5], filter_addr[4], filter_addr[3], filter_addr[2], filter_addr[1], filter_addr[0]);
    } else {
        APPS_LOG_MSGID_E(LOG_TAG" le_scanner_found_cb, unexpected addr=%02X:%02X:%02X:%02X:%02X:%02X",
                         6, filter_addr[0], filter_addr[1], filter_addr[2], filter_addr[3], filter_addr[4], filter_addr[5]);
        return;
    }
#endif

    if (app_bt_service_le_scanner_found_cb != NULL) {
        app_bt_service_le_scanner_found_cb(addr->type, (uint8_t *)addr->a.val, rssi, buf->data, buf->len);
    }
}



/**================================================================================*/
/**                                     Public API                                 */
/**================================================================================*/
void app_bt_service_le_scanner_init(void)
{
    app_bt_service_le_scanner_found_cb = NULL;
}

bool app_bt_service_le_scanner_start(bool whitelist, bool duplicate_filter,
                                     uint16_t scan_interval, uint16_t scan_window,
                                     uint32_t timeout_ms, app_bt_service_le_scanner_found_cb_t found_cb)
{
    bool success = FALSE;
    if (found_cb == NULL) {
        return FALSE;
    }

    uint32_t scan_option = BT_LE_SCAN_OPT_NONE;
    if (whitelist) {
        scan_option |= BT_LE_SCAN_OPT_FILTER_ACCEPT_LIST;
    }
    if (duplicate_filter) {
        scan_option |= BT_LE_SCAN_OPT_FILTER_DUPLICATE;
    }
    struct bt_le_scan_param scan_param = {
        .type       = BT_HCI_LE_SCAN_PASSIVE,
        .options    = scan_option,
        .interval   = scan_interval,
        .window     = scan_window,
    };

    app_bt_service_le_scanner_found_cb = found_cb;
    int error = bt_le_scan_start(&scan_param, app_bt_service_le_scanner_found_callback);
    APPS_LOG_MSGID_W(LOG_TAG" start, whitelist=%d duplicate_filter=%d scan_interval=%d scan_window=%d timeout_ms=%d error=%d",
                     5, whitelist, duplicate_filter, scan_interval, scan_window, timeout_ms, error);
    success = (error == 0);
    if (success) {
        app_dongle_event_send_event(APP_DONGLE_EVENT_GROUP_BT, APP_DONGLE_EVENT_BT_LE_SCAN_STARTED_IND);
        if (timeout_ms > 0) {
            app_dongle_event_remove_event(APP_DONGLE_EVENT_GROUP_BT, APP_DONGLE_EVENT_BT_LE_SCAN_TIMEOUT);
            app_dongle_event_send_delay_event(APP_DONGLE_EVENT_GROUP_BT, APP_DONGLE_EVENT_BT_LE_SCAN_TIMEOUT, NULL, 0, timeout_ms);
        }
    }
    return success;
}

bool app_bt_service_le_scanner_stop(void)
{
    bool success = FALSE;
    app_bt_service_le_scanner_found_cb = NULL;
    app_dongle_event_remove_event(APP_DONGLE_EVENT_GROUP_BT, APP_DONGLE_EVENT_BT_LE_SCAN_TIMEOUT);
    int error = bt_le_scan_stop();
    APPS_LOG_MSGID_W(LOG_TAG" stop, error=%d", 1, error);
    success = (error == 0);
    if (success) {
        app_dongle_event_send_event(APP_DONGLE_EVENT_GROUP_BT, APP_DONGLE_EVENT_BT_LE_SCAN_STOPPED_IND);
    }
    return success;
}