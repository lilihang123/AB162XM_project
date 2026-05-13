
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

#include "app_hogp_client.h"

#include <zephyr/bluetooth/conn.h>

#include "app_bt_service_le_connection.h"
#include "app_dongle_cm.h"
#include "app_dongle_cm_le_scanner.h"
#include "app_dongle_cm_device_mgr.h"
#include "app_debug.h"
#include "app_dongle_event.h"
#include "app_porting.h"

#include "app_usb_mgr.h"

#include "bt_hogp_client.h"



/**================================================================================*/
/**                              Definition & Structure                            */
/**================================================================================*/
#define LOG_TAG             "[APP_DONGLE][HOGP_CLIENT]"

#define APP_HOGP_CLIENT_POWER_ON_RECONNECT_TIME                     (60 * 1000)     // 60sec, only connect bonded device

#define APP_HOGP_CLIENT_FOUND_LIST_NUM                              (APP_DONGLE_CM_OFFICE_KB_MAX_NUM + APP_DONGLE_CM_OFFICE_MS_MAX_NUM)

typedef struct {
    bool                        used;
    uint8_t                     addr_type;
    uint8_t                     addr[BT_ADDR_SIZE];
    struct bt_conn             *bt_conn;
    app_dongle_cm_conn_state_t  conn_state;
    uint8_t                     device_type;
} PACKED app_hong_client_conn_info_t;
typedef struct {
    bool                        used;
    uint8_t                     device_type;
    uint8_t                     addr_type;
    uint8_t                     addr[BT_ADDR_SIZE];
} PACKED app_hong_client_found_info_t;

static bool                                 app_hong_client_power_on_reconnect_flag = FALSE;

static app_hong_client_conn_info_t          app_hong_client_conn_kb_list[APP_DONGLE_CM_OFFICE_KB_MAX_NUM] = {0};
static app_hong_client_conn_info_t          app_hong_client_conn_ms_list[APP_DONGLE_CM_OFFICE_MS_MAX_NUM] = {0};

static app_hong_client_found_info_t         app_hong_client_scan_found_list[APP_HOGP_CLIENT_FOUND_LIST_NUM] = {0};

static bool app_hogp_client_cm_iface_connect_all(void);
static bool app_hogp_client_cm_iface_connect(uint8_t addr_type, uint8_t *addr);
static bool app_hogp_client_cm_iface_disconnect(uint8_t addr_type, uint8_t *addr);
static bool app_hogp_client_cm_iface_scan(bool start_scan);
static void app_hogp_client_cm_iface_active(uint8_t addr_type, uint8_t *addr);
static void app_hogp_client_cm_iface_inactive(uint8_t addr_type, uint8_t *addr);
static app_dongle_cm_interface_t app_hogp_client_cm_interface = {
    .connect_all_if   = app_hogp_client_cm_iface_connect_all,
    .connect_if       = app_hogp_client_cm_iface_connect,
    .disconnect_if    = app_hogp_client_cm_iface_disconnect,
    .scan_if          = app_hogp_client_cm_iface_scan,
    .active_if        = app_hogp_client_cm_iface_active,
    .inactive_if      = app_hogp_client_cm_iface_inactive,
};

static void app_hogp_client_le_scanner_state_change_cb(uint8_t old_state, uint8_t new_state);
static void app_hogp_client_le_scanner_adv_report_cb(uint8_t addr_type, uint8_t *addr, int8_t rssi,
                                                     uint8_t *adv_data, uint8_t adv_len,
                                                     uint8_t link_type, uint8_t device_type,
                                                     uint8_t *user_param);
static app_dongle_cm_le_scanner_callback_t app_hogp_client_le_scanner_callback = {
    .state_change_cb  = app_hogp_client_le_scanner_state_change_cb,
    .adv_report_cb    = app_hogp_client_le_scanner_adv_report_cb,
};



/**================================================================================*/
/**                                   Internal API                                 */
/**================================================================================*/
static void app_hogp_client_check_connection_status(void);

static void app_hogp_client_print(void)
{
    for (int i = 0; i < APP_DONGLE_CM_OFFICE_KB_MAX_NUM; i++) {
        uint8_t *addr = app_hong_client_conn_kb_list[i].addr;
        APPS_LOG_MSGID_I(LOG_TAG" print KB, [%d] used=%d addr_type=%d addr=%08X%04X conn_state=%d bt_conn=0x%08X",
                         5, i, app_hong_client_conn_kb_list[i].used,
                         app_hong_client_conn_kb_list[i].addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr),
                         app_hong_client_conn_kb_list[i].conn_state, app_hong_client_conn_kb_list[i].bt_conn);
    }

    for (int i = 0; i < APP_DONGLE_CM_OFFICE_MS_MAX_NUM; i++) {
        uint8_t *addr = app_hong_client_conn_ms_list[i].addr;
        APPS_LOG_MSGID_I(LOG_TAG" print MS, [%d] used=%d addr_type=%d addr=%08X%04X conn_state=%d bt_conn=0x%08X",
                         5, i, app_hong_client_conn_ms_list[i].used,
                         app_hong_client_conn_ms_list[i].addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr),
                         app_hong_client_conn_ms_list[i].conn_state, app_hong_client_conn_ms_list[i].bt_conn);
    }
}

static void app_hogp_client_clear(void)
{
    app_hong_client_power_on_reconnect_flag = FALSE;
    memset(&app_hong_client_conn_kb_list[0], 0, sizeof(app_hong_client_conn_info_t) * APP_DONGLE_CM_OFFICE_KB_MAX_NUM);
    memset(&app_hong_client_conn_ms_list[0], 0, sizeof(app_hong_client_conn_info_t) * APP_DONGLE_CM_OFFICE_MS_MAX_NUM);

    memset(&app_hong_client_scan_found_list[0], 0, sizeof(app_hong_client_found_info_t) * APP_HOGP_CLIENT_FOUND_LIST_NUM);
}

static void app_hogp_client_clear_conn(void)
{
    app_hong_client_power_on_reconnect_flag = FALSE;
    for (int i = 0; i < APP_DONGLE_CM_OFFICE_KB_MAX_NUM; i++) {
        if (app_hong_client_conn_kb_list[i].used) {
            app_hong_client_conn_kb_list[i].conn_state = APP_DONGLE_CM_CONN_STATE_DISCONNECTED;
            app_hong_client_conn_kb_list[i].bt_conn = NULL;
        }
    }
    for (int i = 0; i < APP_DONGLE_CM_OFFICE_MS_MAX_NUM; i++) {
        if (app_hong_client_conn_ms_list[i].used) {
            app_hong_client_conn_ms_list[i].conn_state = APP_DONGLE_CM_CONN_STATE_DISCONNECTED;
            app_hong_client_conn_kb_list[i].bt_conn = NULL;
        }
    }
}

static app_hong_client_conn_info_t *app_hogp_client_get_device_info(uint8_t addr_type, uint8_t *addr)
{
    app_hong_client_conn_info_t *info = NULL;
    for (int i = 0; i < APP_DONGLE_CM_OFFICE_KB_MAX_NUM; i++) {
        if (app_hong_client_conn_kb_list[i].used
            && app_hong_client_conn_kb_list[i].addr_type == addr_type
            && memcmp(app_hong_client_conn_kb_list[i].addr, addr, BT_ADDR_SIZE) == 0) {
            info = &app_hong_client_conn_kb_list[i];
            break;
        }
    }

    for (int i = 0; i < APP_DONGLE_CM_OFFICE_MS_MAX_NUM; i++) {
        if (app_hong_client_conn_ms_list[i].used
            && app_hong_client_conn_ms_list[i].addr_type == addr_type
            && memcmp(app_hong_client_conn_ms_list[i].addr, addr, BT_ADDR_SIZE) == 0) {
            info = &app_hong_client_conn_ms_list[i];
            break;
        }
    }

    return info;
}

static app_hong_client_conn_info_t *app_hogp_client_get_device_info_by_conn(struct bt_conn *bt_conn)
{
    if (bt_conn == NULL) {
        return NULL;
    }

    app_hong_client_conn_info_t *info = NULL;
    for (int i = 0; i < APP_DONGLE_CM_OFFICE_KB_MAX_NUM; i++) {
        if (app_hong_client_conn_kb_list[i].used
            && app_hong_client_conn_kb_list[i].bt_conn == bt_conn) {
            info = &app_hong_client_conn_kb_list[i];
            break;
        }
    }

    for (int i = 0; i < APP_DONGLE_CM_OFFICE_MS_MAX_NUM; i++) {
        if (app_hong_client_conn_ms_list[i].used
            && app_hong_client_conn_ms_list[i].bt_conn == bt_conn) {
            info = &app_hong_client_conn_ms_list[i];
            break;
        }
    }

    return info;
}

static uint8_t app_hogp_client_get_device_num(bool check_connect, uint8_t device_type)
{
    uint8_t num = 0;

    if (device_type == APP_DONGLE_CM_DEVICE_TYPE_KB) {
        for (int i = 0; i < APP_DONGLE_CM_OFFICE_KB_MAX_NUM; i++) {
            if (app_hong_client_conn_kb_list[i].used
                && app_porting_bt_check_addr_valid(app_hong_client_conn_kb_list[i].addr)
                && (!check_connect
                    || app_hong_client_conn_kb_list[i].conn_state == APP_DONGLE_CM_CONN_STATE_CONNECTING
                    || app_hong_client_conn_kb_list[i].conn_state == APP_DONGLE_CM_CONN_STATE_CONNECTED)) {
                num++;
            }
        }
    } else if (device_type == APP_DONGLE_CM_DEVICE_TYPE_MS) {
        for (int i = 0; i < APP_DONGLE_CM_OFFICE_MS_MAX_NUM; i++) {
            if (app_hong_client_conn_ms_list[i].used
                && app_porting_bt_check_addr_valid(app_hong_client_conn_ms_list[i].addr)
                && (!check_connect
                    || app_hong_client_conn_ms_list[i].conn_state == APP_DONGLE_CM_CONN_STATE_CONNECTING
                    || app_hong_client_conn_ms_list[i].conn_state == APP_DONGLE_CM_CONN_STATE_CONNECTED)) {
                num++;
            }
        }
    }
    return num;
}

static void app_hogp_client_update_conn_state(app_hong_client_conn_info_t *info, uint8_t conn_state)
{
    uint8_t addr_type = info->addr_type;
    uint8_t *addr = info->addr;
    APPS_LOG_MSGID_I(LOG_TAG" update_conn_state, addr_type=%d addr=%08X%04X conn=0x%08X conn_state=%d->%d",
                     6, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), info->bt_conn, info->conn_state, conn_state);
    if (info->conn_state != conn_state) {
        info->conn_state = conn_state;
    }
}

static bool app_hogp_client_add_conn_device(uint8_t device_type, uint8_t addr_type, uint8_t *addr)
{
    bool success = FALSE;
    if (device_type == APP_DONGLE_CM_DEVICE_TYPE_KB) {
        for (int i = 0; i < APP_DONGLE_CM_OFFICE_KB_MAX_NUM; i++) {
            if (app_hong_client_conn_kb_list[i].used
                && app_hong_client_conn_kb_list[i].addr_type == addr_type
                && memcmp(app_hong_client_conn_kb_list[i].addr, addr, BT_ADDR_SIZE) == 0) {
                success = TRUE;
                break;
            }

            if (!app_hong_client_conn_kb_list[i].used) {
                app_hong_client_conn_kb_list[i].used = TRUE;
                app_hong_client_conn_kb_list[i].addr_type = addr_type;
                memcpy(app_hong_client_conn_kb_list[i].addr, addr, BT_ADDR_SIZE);
                app_hong_client_conn_kb_list[i].conn_state = APP_DONGLE_CM_CONN_STATE_DISCONNECTED;
                app_hong_client_conn_kb_list[i].bt_conn = NULL;
                app_hong_client_conn_kb_list[i].device_type = APP_DONGLE_CM_DEVICE_TYPE_KB;
                success = TRUE;
                break;
            }
        }
    }

    if (device_type == APP_DONGLE_CM_DEVICE_TYPE_MS) {
        for (int i = 0; i < APP_DONGLE_CM_OFFICE_MS_MAX_NUM; i++) {
            if (app_hong_client_conn_ms_list[i].used
                && app_hong_client_conn_ms_list[i].addr_type == addr_type
                && memcmp(app_hong_client_conn_ms_list[i].addr, addr, BT_ADDR_SIZE) == 0) {
                success = TRUE;
                break;
            }

            if (!app_hong_client_conn_ms_list[i].used) {
                app_hong_client_conn_ms_list[i].used = TRUE;
                app_hong_client_conn_ms_list[i].addr_type = addr_type;
                memcpy(app_hong_client_conn_ms_list[i].addr, addr, BT_ADDR_SIZE);
                app_hong_client_conn_ms_list[i].conn_state = APP_DONGLE_CM_CONN_STATE_DISCONNECTED;
                app_hong_client_conn_ms_list[i].bt_conn = NULL;
                app_hong_client_conn_ms_list[i].device_type = APP_DONGLE_CM_DEVICE_TYPE_MS;
                success = TRUE;
                break;
            }
        }
    }

    APPS_LOG_MSGID_I(LOG_TAG" add_conn_device, success=%d device_type=%d addr_type=%d addr=%08X%04X",
                     5, success, device_type, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr));
    app_hogp_client_print();
    return success;
}

static bool app_hogp_client_add_found_device(uint8_t device_type, uint8_t addr_type, uint8_t *addr)
{
    bool success = FALSE;
    for (int i = 0; i < APP_HOGP_CLIENT_FOUND_LIST_NUM; i++) {
        if (app_hong_client_scan_found_list[i].used
            && app_hong_client_scan_found_list[i].addr_type == addr_type
            && memcmp(app_hong_client_scan_found_list[i].addr, addr, BT_ADDR_SIZE) == 0) {
            success = TRUE;
            break;
        }

        if (!app_hong_client_scan_found_list[i].used) {
            app_hong_client_scan_found_list[i].used = TRUE;
            app_hong_client_scan_found_list[i].device_type = device_type;
            app_hong_client_scan_found_list[i].addr_type = addr_type;
            memcpy(app_hong_client_scan_found_list[i].addr, addr, BT_ADDR_SIZE);
            success = TRUE;
            break;
        }
    }
    return success;
}

static bool app_hogp_client_start_scan(bool scan_kb, bool scan_ms)
{
    app_dongle_cm_le_scanner_scan_parameter_t scan_param = {0};
    scan_param.scan_policy = APP_DONGLE_CM_LE_SCANNER_SCAN_FULL;
    scan_param.scan_link_type_bit_mask = (1 << APP_DONGLE_CM_LINK_TYPE_LE_HOGP);
    if (scan_kb) {
        scan_param.scan_device_type_bit_mask |= (1 << APP_DONGLE_CM_DEVICE_TYPE_KB);
    }
    if (scan_ms) {
        scan_param.scan_device_type_bit_mask |= (1 << APP_DONGLE_CM_DEVICE_TYPE_MS);
    }
    scan_param.scan_interval = APP_DONGLE_CM_LE_SCAN_DEFAULT_INTERVAL;
    scan_param.scan_window = APP_DONGLE_CM_LE_SCAN_DEFAULT_SCAN_WINDOW;
    scan_param.duplicate_filter = TRUE;
    scan_param.timeout_ms = 0;
    bool success = app_dongle_cm_le_scanner_start_scan(APP_DONGLE_CM_LE_SCANNER_USER_LE_HOGP, scan_param);

    if (success) {
        memset(&app_hong_client_scan_found_list[0], 0, sizeof(app_hong_client_found_info_t) * APP_HOGP_CLIENT_FOUND_LIST_NUM);
    }
    return success;
}

static bool app_hogp_client_stop_scan(void)
{
    bool success = app_dongle_cm_le_scanner_stop_scan(APP_DONGLE_CM_LE_SCANNER_USER_LE_HOGP);
    if (!success) {
        APPS_LOG_MSGID_E(LOG_TAG" stop_scan, error", 0);
    }
    return success;
}

static uint8_t app_hogp_client_set_reconnect_whitelist(bool connect_kb, bool connect_ms)
{
    bool success = FALSE;
    uint8_t add_wl_num = 0;
    app_bt_service_le_connect_clear_whitelist();

    if (connect_kb) {
        for (int i = 0; i < APP_DONGLE_CM_OFFICE_KB_MAX_NUM; i++) {
            if (app_hong_client_conn_kb_list[i].used
                && app_porting_bt_check_addr_valid(app_hong_client_conn_kb_list[i].addr)) {
                success = app_bt_service_le_connect_set_whitelist(app_hong_client_conn_kb_list[i].addr_type, app_hong_client_conn_kb_list[i].addr);
                if (success) {
                    add_wl_num++;
                }
            }
        }
    }
    if (connect_ms) {
        for (int i = 0; i < APP_DONGLE_CM_OFFICE_MS_MAX_NUM; i++) {
            if (app_hong_client_conn_ms_list[i].used
                && app_porting_bt_check_addr_valid(app_hong_client_conn_ms_list[i].addr)) {
                success = app_bt_service_le_connect_set_whitelist(app_hong_client_conn_ms_list[i].addr_type, app_hong_client_conn_ms_list[i].addr);
                if (success) {
                    add_wl_num++;
                }
            }
        }
    }

    APPS_LOG_MSGID_W(LOG_TAG" set_reconnect_whitelist, connect_kb=%d connect_ms=%d add_wl_num=%d", 3, connect_kb, connect_ms, add_wl_num);
    return add_wl_num;
}

static void app_hogp_client_power_on_reconnect(void)
{
    uint8_t add_wl_num = app_hogp_client_set_reconnect_whitelist(TRUE, TRUE);

    bool success = app_bt_service_le_connect_with_whitelist(TRUE);

    if (add_wl_num > 0 && success) {
        app_hong_client_power_on_reconnect_flag = TRUE;
        app_dongle_event_remove_event(APP_DONGLE_EVENT_GROUP_APP_HOGP, APP_DONGLE_EVENT_HOGP_APP_POWER_ON_RECONNECT_TIMEOUT);
        app_dongle_event_send_delay_event(APP_DONGLE_EVENT_GROUP_APP_HOGP, APP_DONGLE_EVENT_HOGP_APP_POWER_ON_RECONNECT_TIMEOUT,
                                        NULL, 0, APP_HOGP_CLIENT_POWER_ON_RECONNECT_TIME);
    }
}

static bool app_hogp_client_connect_addr(uint8_t device_type, uint8_t addr_type, uint8_t *addr)
{
    APPS_LOG_MSGID_I(LOG_TAG" connect_addr, device_type=%d addr_type=%d addr=%08X%04X",
                     4, device_type, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr));

    bool success = FALSE;
    if (device_type == APP_DONGLE_CM_DEVICE_TYPE_KB) {
        for (int i = 0; i < APP_DONGLE_CM_OFFICE_KB_MAX_NUM; i++) {
            if (app_hong_client_conn_kb_list[i].used
                && app_hong_client_conn_kb_list[i].addr_type == addr_type
                && memcmp(app_hong_client_conn_kb_list[i].addr, addr, BT_ADDR_SIZE) == 0
                && app_hong_client_conn_kb_list[i].conn_state == APP_DONGLE_CM_CONN_STATE_DISCONNECTED) {
                success = app_bt_service_le_connect(addr_type, addr, app_hong_client_conn_kb_list[i].bt_conn);
                if (success) {
                    app_hogp_client_update_conn_state(&app_hong_client_conn_kb_list[i], APP_DONGLE_CM_CONN_STATE_CONNECTING);
                    app_dongle_cm_notify_conn_event(APP_DONGLE_CM_LINK_TYPE_LE_HOGP, APP_DONGLE_CM_CONN_EVENT_REQUEST_CONNECT, addr_type, addr);
                }
                break;
            }
        }
    }

    if (device_type == APP_DONGLE_CM_DEVICE_TYPE_MS) {
        for (int i = 0; i < APP_DONGLE_CM_OFFICE_MS_MAX_NUM; i++) {
            if (app_hong_client_conn_ms_list[i].used
                && app_hong_client_conn_ms_list[i].addr_type == addr_type
                && memcmp(app_hong_client_conn_ms_list[i].addr, addr, BT_ADDR_SIZE) == 0
                && app_hong_client_conn_ms_list[i].conn_state == APP_DONGLE_CM_CONN_STATE_DISCONNECTED) {
                success = app_bt_service_le_connect(addr_type, addr, app_hong_client_conn_ms_list[i].bt_conn);
                if (success) {
                    app_hogp_client_update_conn_state(&app_hong_client_conn_ms_list[i], APP_DONGLE_CM_CONN_STATE_CONNECTING);
                    app_dongle_cm_notify_conn_event(APP_DONGLE_CM_LINK_TYPE_LE_HOGP, APP_DONGLE_CM_CONN_EVENT_REQUEST_CONNECT, addr_type, addr);
                }
                break;
            }
        }
    }
    return success;
}

static void app_hogp_client_device_info_init(void)
{
    app_hogp_client_clear();

    app_dongle_cm_device_info_t kb_list[APP_DONGLE_CM_DEVICE_LIST_MAX_NUM] = {0};
    app_dongle_cm_device_info_t ms_list[APP_DONGLE_CM_DEVICE_LIST_MAX_NUM] = {0};
    uint8_t kb_num = app_dongle_cm_device_mgr_get_info_by_link_device_type(APP_DONGLE_CM_LINK_TYPE_LE_HOGP, APP_DONGLE_CM_DEVICE_TYPE_KB, kb_list);
    uint8_t ms_num = app_dongle_cm_device_mgr_get_info_by_link_device_type(APP_DONGLE_CM_LINK_TYPE_LE_HOGP, APP_DONGLE_CM_DEVICE_TYPE_MS, ms_list);
    APPS_LOG_MSGID_W(LOG_TAG" device_info_init, kb_num=%d ms_num=%d", 2, kb_num, ms_num);
    int index = 0;
    if (kb_num > 0) {
        for (int i = 0; i < kb_num; i++) {
            app_hong_client_conn_kb_list[index].used = TRUE;
            app_hong_client_conn_kb_list[index].addr_type = kb_list[i].addr_type;
            memcpy(app_hong_client_conn_kb_list[index].addr, kb_list[i].addr, BT_ADDR_SIZE);
            app_hong_client_conn_kb_list[index].conn_state = APP_DONGLE_CM_CONN_STATE_DISCONNECTED;
            app_hong_client_conn_kb_list[index].bt_conn = NULL;
            app_hong_client_conn_kb_list[index].device_type = APP_DONGLE_CM_DEVICE_TYPE_KB;
            index++;
            if (index == APP_DONGLE_CM_OFFICE_KB_MAX_NUM) {
                break;
            }
        }
    }

    index = 0;
    if (ms_num > 0) {
        for (int i = 0; i < ms_num; i++) {
            app_hong_client_conn_ms_list[index].used = TRUE;
            app_hong_client_conn_ms_list[index].addr_type = ms_list[i].addr_type;
            memcpy(app_hong_client_conn_ms_list[index].addr, ms_list[i].addr, BT_ADDR_SIZE);
            app_hong_client_conn_ms_list[index].conn_state = APP_DONGLE_CM_CONN_STATE_DISCONNECTED;
            app_hong_client_conn_ms_list[index].bt_conn = NULL;
            app_hong_client_conn_ms_list[index].device_type = APP_DONGLE_CM_DEVICE_TYPE_MS;
            index++;
            if (index == APP_DONGLE_CM_OFFICE_MS_MAX_NUM) {
                break;
            }
        }
    }

    memset(&app_hong_client_scan_found_list[0], 0, sizeof(app_hong_client_found_info_t) * APP_HOGP_CLIENT_FOUND_LIST_NUM);

    app_hogp_client_print();
}

static void app_hogp_client_handle_bt_power_off(void)
{
    APPS_LOG_MSGID_W(LOG_TAG" handle_bt_power_off", 0);
    app_dongle_event_remove_event(APP_DONGLE_EVENT_GROUP_APP_HOGP, APP_DONGLE_EVENT_HOGP_APP_POWER_ON_RECONNECT_TIMEOUT);
    app_hogp_client_clear_conn();
    memset(&app_hong_client_scan_found_list[0], 0, sizeof(app_hong_client_found_info_t) * APP_HOGP_CLIENT_FOUND_LIST_NUM);
}

static void app_hogp_client_check_connection_status(void)
{
    uint8_t kb_num = app_hogp_client_get_device_num(FALSE, APP_DONGLE_CM_DEVICE_TYPE_KB);
    uint8_t ms_num = app_hogp_client_get_device_num(FALSE, APP_DONGLE_CM_DEVICE_TYPE_MS);
    uint8_t kb_connected_num = app_hogp_client_get_device_num(TRUE, APP_DONGLE_CM_DEVICE_TYPE_KB);
    uint8_t ms_connected_num = app_hogp_client_get_device_num(TRUE, APP_DONGLE_CM_DEVICE_TYPE_MS);
    APPS_LOG_MSGID_I(LOG_TAG" check_connection_status, kb_num=%d ms_num=%d kb_connected_num=%d ms_connected_num=%d",
                     4, kb_num, ms_num, kb_connected_num, ms_connected_num);

    if (kb_connected_num > 0) {
        if (ms_num == 0) {
            // Scan new MS
            app_hogp_client_start_scan(FALSE, TRUE);
        } else if (ms_connected_num == 0) {
            // Connect old MS
            app_hogp_client_set_reconnect_whitelist(FALSE, TRUE);
            app_bt_service_le_connect_with_whitelist(TRUE);
        }
    } else if (ms_connected_num > 0) {
        if (kb_num == 0) {
            // Scan new KB
            app_hogp_client_start_scan(TRUE, FALSE);
        } else if (kb_connected_num == 0) {
            // Connect old KB
            app_hogp_client_set_reconnect_whitelist(TRUE, FALSE);
            app_bt_service_le_connect_with_whitelist(TRUE);
        }
    } else {
        app_hogp_client_stop_scan();
        app_hogp_client_power_on_reconnect();
    }
}

static void app_hogp_client_le_scanner_state_change_cb(uint8_t old_state, uint8_t new_state)
{
    APPS_LOG_MSGID_W(LOG_TAG" state_change_cb, scan_state_change %d->%d", 2, old_state, new_state);
}

static void app_hogp_client_le_scanner_adv_report_cb(uint8_t addr_type, uint8_t *addr, int8_t rssi,
                                                     uint8_t *adv_data, uint8_t adv_len,
                                                     uint8_t link_type, uint8_t device_type,
                                                     uint8_t *user_param)
{
    bool add_found_device_success = FALSE;
    // Found LE_HOGP + KB/MS ADV
    if (link_type == APP_DONGLE_CM_LINK_TYPE_LE_HOGP && (device_type == APP_DONGLE_CM_DEVICE_TYPE_KB || device_type == APP_DONGLE_CM_DEVICE_TYPE_MS)) {
        add_found_device_success = app_hogp_client_add_found_device(device_type, addr_type, addr);

        uint8_t kb_num = app_hogp_client_get_device_num(FALSE, APP_DONGLE_CM_DEVICE_TYPE_KB);
        uint8_t ms_num = app_hogp_client_get_device_num(FALSE, APP_DONGLE_CM_DEVICE_TYPE_MS);
        uint8_t kb_connected_num = app_hogp_client_get_device_num(TRUE, APP_DONGLE_CM_DEVICE_TYPE_KB);
        uint8_t ms_connected_num = app_hogp_client_get_device_num(TRUE, APP_DONGLE_CM_DEVICE_TYPE_MS);
        APPS_LOG_MSGID_I(LOG_TAG" adv_report_cb, link_type=%d device_type=%d kb_num=%d ms_num=%d kb_connected_num=%d ms_connected_num=%d",
                         6, link_type, device_type, kb_num, ms_num, kb_connected_num, ms_connected_num);
        if ((device_type == APP_DONGLE_CM_DEVICE_TYPE_KB && kb_num < APP_DONGLE_CM_OFFICE_KB_MAX_NUM)
            || (device_type == APP_DONGLE_CM_DEVICE_TYPE_MS && ms_num < APP_DONGLE_CM_OFFICE_MS_MAX_NUM)) {
            bool add_success = app_hogp_client_add_conn_device(device_type, addr_type, addr);
            app_hogp_client_stop_scan();
            if (add_success
                && ((device_type == APP_DONGLE_CM_DEVICE_TYPE_KB && kb_connected_num == 0)
                    || (device_type == APP_DONGLE_CM_DEVICE_TYPE_MS && ms_connected_num == 0))) {    // ToDo, switching, <2?
                app_dongle_cm_add_found_addr(APP_DONGLE_CM_LINK_TYPE_LE_HOGP, device_type, addr_type, addr, TRUE);
            }
        }
    }

    if (!add_found_device_success) {
        APPS_LOG_MSGID_W(LOG_TAG" adv_report_cb, add_found_device full => stop scan", 0);
        app_dongle_event_remove_event(APP_DONGLE_EVENT_GROUP_APP_HOGP, APP_DONGLE_EVENT_HOGP_APP_POWER_ON_RECONNECT_TIMEOUT);
        app_hogp_client_stop_scan();
        // ToDo
    }
}



/**================================================================================*/
/**                              Dongle CM Interface                               */
/**================================================================================*/
static bool app_hogp_client_cm_iface_connect_all(void)
{
    app_hogp_client_power_on_reconnect();
    return TRUE;
}

static bool app_hogp_client_cm_iface_connect(uint8_t addr_type, uint8_t *addr)
{
    bool success = FALSE;
    app_hong_client_conn_info_t *info = app_hogp_client_get_device_info(addr_type, addr);
    if (info != NULL) {
        uint8_t device_type = info->device_type;
        APPS_LOG_MSGID_I(LOG_TAG" iface_connect, device_type=%d addr_type=%d addr=%08X%04X",
                        4, device_type, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr));
        if (device_type == APP_DONGLE_CM_DEVICE_TYPE_KB || device_type == APP_DONGLE_CM_DEVICE_TYPE_MS) {
            success = app_hogp_client_connect_addr(device_type, addr_type, addr);
        }
    }
    return success;
}

static bool app_hogp_client_cm_iface_disconnect(uint8_t addr_type, uint8_t *addr)
{
    bool success = FALSE;
    app_hong_client_conn_info_t *info = app_hogp_client_get_device_info(addr_type, addr);
    APPS_LOG_MSGID_I(LOG_TAG" iface_disconnect, addr_type=%d addr=%08X%04X info=0x%08X conn=0x%08X",
                     5, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), info, (info != NULL ? info->bt_conn : NULL));
    if (info != NULL && info->bt_conn != NULL) {
        success = app_bt_service_le_disconnect(info->bt_conn);
    }
    return success;
}

static bool app_hogp_client_cm_iface_scan(bool start_scan)
{
    bool success = FALSE;
    if (start_scan) {
        success = app_hogp_client_start_scan(TRUE, TRUE);
    } else {
        success = app_hogp_client_stop_scan();
    }
    return success;
}

static void app_hogp_client_cm_iface_active(uint8_t addr_type, uint8_t *addr)
{
    APPS_LOG_MSGID_W(LOG_TAG" iface_active, addr_type=%d addr=%08X%04X",
                     3, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr));
}

static void app_hogp_client_cm_iface_inactive(uint8_t addr_type, uint8_t *addr)
{
    APPS_LOG_MSGID_W(LOG_TAG" iface_inactive, addr_type=%d addr=%08X%04X",
                     3, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr));
}



/**================================================================================*/
/**                               HOGP Callback Handler                            */
/**================================================================================*/
static void app_hogp_client_hogp_event_callback(bt_hogp_client_event_t event, bt_hogp_client_para_t *para, void *buffer, uint16_t length)
{
    switch (event) {
        case BT_HOGP_CLIENT_EVENT_CONNECT_IND: {
            //APPS_LOG_MSGID_W(LOG_TAG" hogp_event_callback, CONNECT_IND", 0);
            break;
        }

        case BT_HOGP_CLIENT_EVENT_DISCONNECT_IND: {
            //APPS_LOG_MSGID_W(LOG_TAG" hogp_event_callback, DISCONNECT_IND", 0);
            break;
        }

        case BT_HOGP_CLIENT_EVENT_REPORT_MAP_IND: {
            uint8_t *data = (uint8_t *)buffer;
            struct bt_conn *bt_conn = (struct bt_conn *)para->conn;
            APPS_LOG_MSGID_W(LOG_TAG" hogp_event_callback, REPORT_MAP_IND conn=0x%08X data[2~3]=%02X %02X", 3, bt_conn, data[2], data[3]);
            app_hong_client_conn_info_t *info = app_hogp_client_get_device_info_by_conn(bt_conn);
            if (info != NULL
                && ((info->device_type == APP_DONGLE_CM_DEVICE_TYPE_KB && data[2] == 0x09 && data[3] == 0x06)
                    || (info->device_type == APP_DONGLE_CM_DEVICE_TYPE_MS && data[2] == 0x09 && data[3] == 0x02))) {
            } else {
                app_hogp_client_print();
                APPS_LOG_MSGID_E(LOG_TAG" hogp_event_callback, REPORT_MAP_IND error", 0);
                //assert(0);
            }
            break;
        }

        case BT_HOGP_CLIENT_EVENT_INPUT_REPORT_IND: {
            bt_report_id_t report_id = para->report_id;
            struct bt_conn *bt_conn = (struct bt_conn *)para->conn;
            app_hong_client_conn_info_t *info = app_hogp_client_get_device_info_by_conn(bt_conn);
            APPS_LOG_MSGID_W(LOG_TAG" hogp_event_callback, INPUT_REPORT_IND report_id=%d info=0x%08X type=%d buffer=0x%08X length=%d",
                             5, report_id, info, (info != NULL ? info->device_type : 0xFF), buffer, length);
            if (info == NULL) {
                break;
            }

            if (info->device_type == APP_DONGLE_CM_DEVICE_TYPE_KB) {
                app_usb_mgr_send_input_report(TRUE, buffer, length);
            } else if (info->device_type == APP_DONGLE_CM_DEVICE_TYPE_MS) {
                app_usb_mgr_send_input_report(FALSE, buffer, length);
            }
            break;
        }
    }
}



/**================================================================================*/
/**                                  Event Handler                                 */
/**================================================================================*/
static bool app_hogp_client_handle_bt_event(uint16_t event_id, void *data, uint32_t data_len)
{
    switch (event_id) {
        case APP_DONGLE_EVENT_BT_ON: {
            break;
        }

        case APP_DONGLE_EVENT_BT_OFF: {
            app_hogp_client_handle_bt_power_off();
            break;
        }

        case APP_DONGLE_EVENT_BT_LE_CONNECTED_IND: {
            app_bt_service_le_connection_ind_t *ind = (app_bt_service_le_connection_ind_t *)data;
            uint8_t addr_type = ind->addr_type;
            uint8_t *addr = ind->addr;
            app_hong_client_conn_info_t *info = app_hogp_client_get_device_info(addr_type, addr);
            if (info != NULL) {
                info->bt_conn = ind->conn;
                APPS_LOG_MSGID_W(LOG_TAG" LE_CONNECTED_IND, bt_conn=0x%08X device_type=%d", 2, ind->conn, info->device_type);

                app_hogp_client_update_conn_state(info, APP_DONGLE_CM_CONN_STATE_CONNECTED);
                app_dongle_cm_notify_conn_event(APP_DONGLE_CM_LINK_TYPE_LE_HOGP, APP_DONGLE_CM_CONN_EVENT_CONNECTED, addr_type, addr);

                // Start LE SM pairing->bond
                if (info->device_type == APP_DONGLE_CM_DEVICE_TYPE_KB) {
                    app_bt_service_le_bond(ind->conn, TRUE);
                } else {
                    app_bt_service_le_bond(ind->conn, FALSE);
                }
            }

            app_dongle_event_remove_event(APP_DONGLE_EVENT_GROUP_APP_HOGP, APP_DONGLE_EVENT_HOGP_APP_POWER_ON_RECONNECT_TIMEOUT);
            break;
        }

        case APP_DONGLE_EVENT_BT_LE_DISCONNECTED_IND: {
            app_bt_service_le_disconnect_ind_t *ind = (app_bt_service_le_disconnect_ind_t *)data;
            uint8_t addr_type = ind->addr_type;
            uint8_t *addr = ind->addr;
            uint8_t reason = ind->disconnect_reason;
            app_hong_client_conn_info_t *info = app_hogp_client_get_device_info(addr_type, addr);
            if (info != NULL) {
                info->bt_conn = NULL;
                app_hogp_client_update_conn_state(info, APP_DONGLE_CM_CONN_STATE_DISCONNECTED);

                app_hogp_client_stop_scan();

                if (reason == BT_HCI_ERR_REMOTE_USER_TERM_CONN || reason == BT_HCI_ERR_REMOTE_POWER_OFF
                    || reason == BT_HCI_ERR_LOCALHOST_TERM_CONN) {
                    app_dongle_cm_notify_conn_event(APP_DONGLE_CM_LINK_TYPE_LE_HOGP, APP_DONGLE_CM_CONN_EVENT_DISCONNECTED, addr_type, addr);
                } else {
                    app_bt_service_le_connect_with_whitelist(FALSE);
                    app_dongle_cm_notify_conn_event(APP_DONGLE_CM_LINK_TYPE_LE_HOGP, APP_DONGLE_CM_CONN_EVENT_LINK_LOST, addr_type, addr);
                }

                app_hogp_client_check_connection_status();
            }
            break;
        }

        case APP_DONGLE_EVENT_BT_LE_BOND_COMPLETE_IND: {
            app_bt_service_le_bonded_ind_t *ind = (app_bt_service_le_bonded_ind_t *)data;
            uint8_t addr_type = ind->addr_type;
            uint8_t *addr = ind->addr;
            app_hong_client_conn_info_t *info = app_hogp_client_get_device_info(addr_type, addr);
            if (info != NULL) {
                app_dongle_cm_notify_conn_event(APP_DONGLE_CM_LINK_TYPE_LE_HOGP, APP_DONGLE_CM_CONN_EVENT_BONDED, addr_type, addr);

                app_hogp_client_check_connection_status();
            }
            break;
        }
    }

    return FALSE;
}

static bool app_hogp_client_handle_usb_event(uint16_t event_id, void *data, uint32_t data_len)
{
    return FALSE;
}

static bool app_hogp_client_handle_hogp_app_event(uint16_t event_id, void *data, uint32_t data_len)
{
    if (event_id == APP_DONGLE_EVENT_HOGP_APP_POWER_ON_RECONNECT_TIMEOUT) {
        app_hong_client_power_on_reconnect_flag = FALSE;
        bool success = app_bt_service_le_connect_with_whitelist(FALSE);
        success += app_hogp_client_start_scan(TRUE, TRUE);
        APPS_LOG_MSGID_W(LOG_TAG" POWER_ON_RECONNECT_TIMEOUT, scan success=%d", 1, success);
    }
    return FALSE;
}

bool app_hogp_client_event_handler(uint8_t event_group, uint16_t event_id, void *data, uint32_t data_len)
{
    switch (event_group) {
        case APP_DONGLE_EVENT_GROUP_BT: {
            app_hogp_client_handle_bt_event(event_id, data, data_len);
            break;
        }

        case APP_DONGLE_EVENT_GROUP_USB: {
            app_hogp_client_handle_usb_event(event_id, data, data_len);
            break;
        }

        case APP_DONGLE_EVENT_GROUP_APP_HOGP: {
            app_hogp_client_handle_hogp_app_event(event_id, data, data_len);
            break;
        }
    }
    return FALSE;
}



/**================================================================================*/
/**                                     Public API                                 */
/**================================================================================*/
void app_hogp_client_init(void)
{
    app_hogp_client_device_info_init();
    app_dongle_cm_register_link_interface(APP_DONGLE_CM_LINK_TYPE_LE_HOGP, &app_hogp_client_cm_interface);
    app_dongle_cm_le_scanner_register(APP_DONGLE_CM_LE_SCANNER_USER_LE_HOGP, app_hogp_client_le_scanner_callback, NULL);
    bt_hogp_client_init(app_hogp_client_hogp_event_callback);
}