
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

#include "app_bt_service_le_connection.h"

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/logging/log.h>
#include "host/conn_internal.h"

#include "app_debug.h"
#include "app_dongle_event.h"
#include "app_porting.h"



/**================================================================================*/
/**                              Definition & Structure                            */
/**================================================================================*/
#define LOG_TAG             "[APP_DONGLE][BT_SRV][LE_CONN]"

#define APP_BT_SERVICE_LE_CONN_INIT_INTERVAL 0x0010         /* uint:0.625ms, 10 ms */
#define APP_BT_SERVICE_LE_CONN_INIT_WINDOW   0x0010         /* uint:0.625ms, 10 ms */
#define APP_BT_SERVICE_LE_CONN_CONN_INTERVAL 0x0010         /* uint:0.625ms, 10 ms */
#define APP_BT_SERVICE_LE_CONN_CONN_LATENCY  0
#define APP_BT_SERVICE_LE_CONN_CONN_TIMEOUT  500            /* uint:10ms, 5000 ms */

const struct bt_conn_le_create_param app_bt_service_le_create_param = {
    .options = BT_CONN_LE_OPT_NONE,
    .interval = APP_BT_SERVICE_LE_CONN_INIT_INTERVAL,
    .window = APP_BT_SERVICE_LE_CONN_INIT_WINDOW,
    .interval_coded = 0,
    .window_coded = 0,
    .timeout = 0,
};

const struct bt_le_conn_param app_bt_service_le_conn_param = {
    .interval_min = APP_BT_SERVICE_LE_CONN_CONN_INTERVAL,
    .interval_max = APP_BT_SERVICE_LE_CONN_CONN_INTERVAL,
    .latency = APP_BT_SERVICE_LE_CONN_CONN_LATENCY,
    .timeout = APP_BT_SERVICE_LE_CONN_CONN_TIMEOUT,
};

static void app_bt_service_le_connected_cb(struct bt_conn *conn, uint8_t reason);
static void app_bt_service_le_disconnected_cb(struct bt_conn *conn, uint8_t reason);
static void app_bt_service_le_param_updated(struct bt_conn *conn, uint16_t interval, uint16_t latency, uint16_t timeout);
static void app_bt_service_le_identity_resolved(struct bt_conn *conn, const bt_addr_le_t *rpa, const bt_addr_le_t *identity);
static void app_bt_service_le_security_changed_cb(struct bt_conn *conn, bt_security_t level, enum bt_security_err error);

static void app_bt_service_le_auth_passkey_display(struct bt_conn *conn, unsigned int passkey);
static void app_bt_service_le_auth_cancel(struct bt_conn *conn);
static void app_bt_service_le_pairing_complete(struct bt_conn *conn, bool bonded);
static void app_bt_service_le_pairing_failed(struct bt_conn *conn, enum bt_security_err reason);

static struct bt_conn_auth_cb app_bt_service_le_auth_cb_display = {
	.passkey_display = app_bt_service_le_auth_passkey_display,
	.passkey_entry = NULL,
	.cancel = app_bt_service_le_auth_cancel,
};

static struct bt_conn_auth_info_cb app_bt_service_le_auth_cb_info = {
	.pairing_complete = app_bt_service_le_pairing_complete,
	.pairing_failed = app_bt_service_le_pairing_failed,
};

static struct bt_conn_cb app_bt_service_le_callbacks = {
    .connected =                        app_bt_service_le_connected_cb,
    .disconnected =                     app_bt_service_le_disconnected_cb,
#if defined(CONFIG_BT_SMP)
    .le_param_updated =                 app_bt_service_le_param_updated,
    .identity_resolved =                app_bt_service_le_identity_resolved,
    .security_changed =                 app_bt_service_le_security_changed_cb,
#endif
};



/**================================================================================*/
/**                                   Internal API                                 */
/**================================================================================*/
static void app_bt_service_le_connected_cb(struct bt_conn *conn, uint8_t error)
{
    if (conn == NULL || error != 0 || conn->type != BT_CONN_TYPE_LE) {
        APPS_LOG_MSGID_E(LOG_TAG" le_connected_cb, conn=0x%08X error=%d type=%d", 3, conn, error, (conn != NULL ? conn->type : 0xFF));
        return;
    }

    uint16_t conn_handle = conn->handle;
    uint16_t interval = conn->le.interval;
    uint8_t state = conn->state;
    uint8_t addr_type = conn->le.dst.type;
    uint8_t *addr = conn->le.dst.a.val;
    APPS_LOG_MSGID_W(LOG_TAG" le_connected_cb, conn=0x%08X conn_handle=0x%04X interval=%d state=%d addr_type=%d addr=%08X%04X",
                     7, conn, conn_handle, interval, state, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr));

    int size = sizeof(app_bt_service_le_connection_ind_t);
    app_bt_service_le_connection_ind_t *ind = (app_bt_service_le_connection_ind_t *)app_porting_malloc(size);
    if (ind != NULL) {
        ind->conn_handle = conn_handle;
        ind->addr_type = addr_type;
        memcpy(ind->addr, addr, BT_ADDR_SIZE);
        ind->conn_interval = interval;
        ind->conn = conn;
        app_dongle_event_send_event_data(APP_DONGLE_EVENT_GROUP_BT, APP_DONGLE_EVENT_BT_LE_CONNECTED_IND, ind, size);
    }
}

static void app_bt_service_le_disconnected_cb(struct bt_conn *conn, uint8_t reason)
{
    if (conn == NULL || conn->type != BT_CONN_TYPE_LE) {
        //APPS_LOG_MSGID_E(LOG_TAG" le_disconnected_cb, conn=0x%08X type=%d", 2, conn, (conn != NULL ? conn->type : 0xFF));
        return;
    }

    uint16_t conn_handle = conn->handle;
    uint8_t addr_type = conn->le.dst.type;
    uint8_t *addr = conn->le.dst.a.val;
    APPS_LOG_MSGID_W(LOG_TAG" le_disconnected_cb, conn_handle=0x%04X reason=0x%02X addr_type=%d addr=%08X%04X",
                     5, conn_handle, reason, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr));

    int size = sizeof(app_bt_service_le_disconnect_ind_t);
    app_bt_service_le_disconnect_ind_t *ind = (app_bt_service_le_disconnect_ind_t *)app_porting_malloc(size);
    if (ind != NULL) {
        ind->conn_handle = conn_handle;
        ind->addr_type = addr_type;
        memcpy(ind->addr, addr, BT_ADDR_SIZE);
        ind->disconnect_reason = reason;
        app_dongle_event_send_event_data(APP_DONGLE_EVENT_GROUP_BT, APP_DONGLE_EVENT_BT_LE_DISCONNECTED_IND, ind, size);
    }
}

#if defined(CONFIG_BT_SMP)
static void app_bt_service_le_param_updated(struct bt_conn *conn, uint16_t interval, uint16_t latency, uint16_t timeout)
{
    if (conn == NULL || conn->type != BT_CONN_TYPE_LE) {
        return;
    }

    APPS_LOG_MSGID_W(LOG_TAG" le_param_updated, conn_handle=0x%04X interval=%d", 2, conn->handle, interval);
}

static void app_bt_service_le_identity_resolved(struct bt_conn *conn, const bt_addr_le_t *rpa, const bt_addr_le_t *identity)
{
    if (conn == NULL || conn->type != BT_CONN_TYPE_LE) {
        return;
    }

    uint16_t conn_handle = conn->handle;
    uint8_t rpa_type = rpa->type;
    uint8_t *rpa_addr = (uint8_t *)rpa->a.val;
    uint8_t ida_type = identity->type;
    uint8_t *ida_addr = (uint8_t *)identity->a.val;
    APPS_LOG_MSGID_W(LOG_TAG" le_identity_resolved, conn_handle=0x%04X rpa=%d %08X%04X ida=%d %08X%04X",
                     7, conn_handle,
                     rpa_type, *((uint32_t *)(rpa_addr + 2)), *((uint16_t *)rpa_addr),
                     ida_type, *((uint32_t *)(ida_addr + 2)), *((uint16_t *)ida_addr));
}

static void app_bt_service_le_security_changed_cb(struct bt_conn *conn, bt_security_t level, enum bt_security_err error)
{
    if (conn == NULL || conn->type != BT_CONN_TYPE_LE || level <= BT_SECURITY_L1) {
        APPS_LOG_MSGID_E(LOG_TAG" le_security_changed_cb, conn=0x%08X type=%d level=%d error=%d",
                         4, conn, (conn != NULL ? conn->type : 0xFF), level, error);
        return;
    } else if (error != BT_SECURITY_ERR_SUCCESS) {
        APPS_LOG_MSGID_E(LOG_TAG" le_security_changed_cb, conn_handle=0x%04X error=%d", 2, conn->handle, error);
        return;
    }

    uint16_t conn_handle = conn->handle;
    uint8_t addr_type = conn->le.dst.type;
    uint8_t *addr = conn->le.dst.a.val;
    APPS_LOG_MSGID_W(LOG_TAG" le_security_changed_cb, conn_handle=0x%04X addr_type=%d addr=%08X%04X level=%d",
                     5, conn_handle, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), level);

    int size = sizeof(app_bt_service_le_bonded_ind_t);
    app_bt_service_le_bonded_ind_t *ind = (app_bt_service_le_bonded_ind_t *)app_porting_malloc(size);
    if (ind != NULL) {
        ind->conn_handle = conn_handle;
        ind->addr_type = addr_type;
        memcpy(ind->addr, addr, BT_ADDR_SIZE);
        app_dongle_event_send_event_data(APP_DONGLE_EVENT_GROUP_BT, APP_DONGLE_EVENT_BT_LE_BOND_COMPLETE_IND, ind, size);
    }
}
#endif

static void app_bt_service_le_auth_passkey_display(struct bt_conn *conn, unsigned int passkey)
{
    uint16_t conn_handle = conn->handle;
    uint8_t addr_type = conn->le.dst.type;
    uint8_t *addr = conn->le.dst.a.val;
    APPS_LOG_MSGID_W(LOG_TAG" le_auth_passkey_display, conn_handle=0x%04X addr_type=%d addr=%08X%04X passkey=%d",
                     5, conn_handle, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), passkey);
}

static void app_bt_service_le_auth_cancel(struct bt_conn *conn)
{
    uint16_t conn_handle = conn->handle;
    uint8_t addr_type = conn->le.dst.type;
    uint8_t *addr = conn->le.dst.a.val;
    APPS_LOG_MSGID_W(LOG_TAG" le_auth_cancel, conn_handle=0x%04X addr_type=%d addr=%08X%04X",
                     4, conn_handle, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr));
}

static void app_bt_service_le_pairing_complete(struct bt_conn *conn, bool bonded)
{
    uint16_t conn_handle = conn->handle;
    uint8_t addr_type = conn->le.dst.type;
    uint8_t *addr = conn->le.dst.a.val;
    APPS_LOG_MSGID_W(LOG_TAG" le_pairing_complete, conn_handle=0x%04X addr_type=%d addr=%08X%04X bonded=%d",
                     5, conn_handle, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), bonded);
}

static void app_bt_service_le_pairing_failed(struct bt_conn *conn, enum bt_security_err reason)
{
    uint8_t addr_type = conn->le.dst.type;
    uint8_t *addr = conn->le.dst.a.val;
    int error = bt_conn_disconnect(conn, BT_HCI_ERR_AUTH_FAIL);
    APPS_LOG_MSGID_W(LOG_TAG" le_pairing_failed, addr_type=%d addr=%08X%04X reason=%d disconnect_error=%d",
                     5, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), reason, error);
}



/**================================================================================*/
/**                                     Public API                                 */
/**================================================================================*/
void app_bt_service_le_connection_init(void)
{
    bt_conn_cb_register((struct bt_conn_cb *)(&app_bt_service_le_callbacks));

    bt_conn_auth_cb_register(&app_bt_service_le_auth_cb_display);
	bt_conn_auth_info_cb_register(&app_bt_service_le_auth_cb_info);
}

bool app_bt_service_le_connect_clear_whitelist(void)
{
    int error = bt_le_filter_accept_list_clear();
    APPS_LOG_MSGID_I(LOG_TAG" clear_whitelist, error=%d", 1, error);
    return (error == 0);
}

bool app_bt_service_le_connect_set_whitelist(uint8_t addr_type, uint8_t *addr)
{
    if (addr == NULL) {
        return FALSE;
    }

    bt_addr_le_t le_addr = {0};
    le_addr.type = addr_type;
    memcpy(le_addr.a.val, addr, BT_ADDR_SIZE);
    int error = bt_le_filter_accept_list_add(&le_addr);
    APPS_LOG_MSGID_I(LOG_TAG" set_whitelist, addr_type=%d addr=%08X%04X error=%d",
                     4, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), error);
    return (error == 0);
}

bool app_bt_service_le_connect_with_whitelist(bool start)
{
    int error = 0;
    if (start) {
        error = bt_conn_le_create_auto(&app_bt_service_le_create_param, &app_bt_service_le_conn_param);
    } else {
        error = bt_conn_create_auto_stop();
    }
    APPS_LOG_MSGID_I(LOG_TAG" le_connect_with_whitelist, start=%d error=%d", 2, start, error);
    return (error == 0);
}

bool app_bt_service_le_connect(uint8_t addr_type, uint8_t *addr, void *bt_conn)
{
    if (addr == NULL) {
        return FALSE;
    }

    bt_addr_le_t le_addr = {0};
    le_addr.type = addr_type;
    memcpy(le_addr.a.val, addr, BT_ADDR_SIZE);
    struct bt_conn *bt_le_conn = (struct bt_conn *)bt_conn;
    int error = bt_conn_le_create(&le_addr, &app_bt_service_le_create_param, &app_bt_service_le_conn_param, &bt_le_conn);
    APPS_LOG_MSGID_I(LOG_TAG" le_connect, addr_type=%d addr=%08X%04X bt_conn=0x%08X error=%d",
                     5, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), bt_conn, error);
    return (error == 0);
}

bool app_bt_service_le_bond(void *bt_conn, bool support_sc)
{
    if (bt_conn == NULL) {
        APPS_LOG_MSGID_E(LOG_TAG" le_bond, bt_conn=0x%08X", 1, bt_conn);
        return FALSE;
    }

    int error = bt_conn_set_security(bt_conn, (support_sc ? BT_SECURITY_L4 : BT_SECURITY_L2));
    APPS_LOG_MSGID_I(LOG_TAG" le_bond, bt_conn=0x%08X support_sc=%d error=%d", 3, bt_conn, support_sc, error);
    return (error == 0);
}

bool app_bt_service_le_disconnect(void *bt_conn)
{
    if (bt_conn == NULL) {
        APPS_LOG_MSGID_E(LOG_TAG" le_disconnect, bt_conn=0x%08X", 1, bt_conn);
        return FALSE;
    }

    struct bt_conn *bt_le_conn = (struct bt_conn *)bt_conn;
    int error = bt_conn_disconnect(bt_le_conn, BT_HCI_ERR_REMOTE_USER_TERM_CONN);
    APPS_LOG_MSGID_E(LOG_TAG" le_disconnect, conn_handle=0x%04X bt_conn=0x%08X error=%d", 3, bt_le_conn->handle, bt_conn, error);
    return (error == 0);
}