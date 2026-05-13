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

/*****************************************************************************
 *
 *
 * Description:
 * ------------
 * This file implements BLE Air service main function
 *
 ****************************************************************************/

#include <stdint.h>
#include "ble_air_interface.h"
#include "ble_air_internal.h"
#include <zephyr/autoconf.h>
#include <zephyr/bluetooth/gatt.h>



#define BLE_AIR_DEVICE_ID_BASE           0x80

#define BLE_AIR_SRV_MAX_MTU               512

typedef struct {
    bool in_use;
    ble_air_common_callback_t callback;
} ble_air_callback_node_t;

static uint8_t g_rx_buffer[BLE_AIR_RECEIVE_BUFFER_SIZE];
static ble_air_cntx_t g_air_cntx[BT_CONNECTION_MAX];
static ble_air_callback_node_t ble_air_cb_list[BLE_AIR_SUPPORT_CB_MAX_NUM];
static struct k_mutex ble_air_mutex;

#ifdef CONFIG_BT_ULL_HID_LE
static ble_air_ull_cntx_t g_air_ull_cntx[BT_CONNECTION_MAX];
//static uint8_t g_switch_cis_link_flag = false;
#endif


#define BLE_AIR_LINK_UPDATE_STATE_NONE                              (0x00)
#define BLE_AIR_LINK_UPDATE_STATE_OPTIMIZING                        (0x01)
#define BLE_AIR_LINK_UPDATE_STATE_OPTIMIZED                         (0x02)
#define BLE_AIR_LINK_UPDATE_STATE_OPTIMIZE_REVERT                   (0x03)
static uint8_t link_update_state = BLE_AIR_LINK_UPDATE_STATE_NONE;
/************************************************
*   static utilities
*************************************************/
static ssize_t ble_air_tx_char_cccd_callback(struct bt_conn *conn, const struct bt_gatt_attr *attr, uint16_t value);
static void ble_air_cccd_changed(const struct bt_gatt_attr *attr, uint16_t value);
static ssize_t ble_air_rx_write_char_callback(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf, uint16_t len, uint16_t offset, uint8_t flags);

static int32_t ble_air_event_callback(ble_air_event_t event_id, void *param);
static ble_air_status_t ble_air_check_user(void);
static void ble_air_connection_status_notify(ble_air_common_callback_t callback);
static ble_air_status_t ble_air_cb_register(ble_air_common_callback_t callback);
static ble_air_status_t ble_air_cb_deregister(ble_air_common_callback_t callback);
static void ble_air_init_all_cntx(void);
#ifdef MTK_BLE_GAP_SRV_ENABLE
bt_gap_le_srv_link_attribute_t bt_gap_le_srv_get_link_attribute_by_handle(uint16_t handle);
#endif
static void ble_air_disconn_event_callback(ble_air_cntx_t *buffer_t);

#ifdef AIR_BT_SINK_SOURCE_COEXIST_ENABLE
uint8_t ble_air_get_current_bt_mode(void);

uint8_t ble_air_get_current_bt_mode_default(void)
{
    return BT_CIS_SINK_MODE;
}
#pragma weak ble_air_get_current_bt_mode=ble_air_get_current_bt_mode_default
#endif

/**********************************uuid*******************************************/

BT_GATT_SERVICE_DEFINE(ble_air_service,
    BT_GATT_PRIMARY_SERVICE(AIR_SERVICE_UUID),
    BT_GATT_CHARACTERISTIC(AIR_RX_CHAR_UUID, BT_GATT_CHRC_READ|BT_GATT_CHRC_WRITE|BT_GATT_CHRC_WRITE_WITHOUT_RESP,
                           BT_GATT_PERM_READ_ENCRYPT|BT_GATT_PERM_WRITE_ENCRYPT, NULL, ble_air_rx_write_char_callback, NULL),
    BT_GATT_CHARACTERISTIC(AIR_TX_CHAR_UUID, BT_GATT_CHRC_NOTIFY, BT_GATT_PERM_READ_ENCRYPT,
                           NULL, NULL, NULL),
    BT_GATT_CCC_MANAGED(((struct _bt_gatt_ccc[]) {
        BT_GATT_CCC_INITIALIZER(ble_air_cccd_changed, ble_air_tx_char_cccd_callback, NULL)
    }), BT_GATT_PERM_READ_ENCRYPT | BT_GATT_PERM_WRITE_ENCRYPT)
);

#if 0//defined(AIR_PURE_GAMING_DONGLE_ENABLE)
static uint8_t ble_air_notify_handler(struct bt_conn *conn,
                    struct bt_gatt_subscribe_params *params,
                    const void *data, uint16_t length)
{
    uint16_t handle = params->value_handle;
    ble_air_cntx_t *context;
    if (data == NULL || conn == NULL) {
        return BT_GATT_ITER_CONTINUE;
    }

    context = ble_air_get_cntx_by_handle(conn->handle);

    if (handle == context->tx_handle) {
        memcpy((context->receive_buffer + context->receive_buffer_length), data, length);
        context->receive_buffer_length += length;
        if ((0 == ble_air_check_user())) {
            ble_air_ready_to_read_t ready_to_read;
            ready_to_read.conn_handle = conn->handle;
            ble_air_event_callback(BLE_AIR_EVENT_READY_TO_READ_IND, (void *)&ready_to_read);
        }

    }

    return BT_GATT_ITER_CONTINUE;
}

static uint8_t ble_air_discover_func(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
                struct bt_gatt_discover_params *params)
{
    int err = 0;
    struct bt_gatt_chrc *chrc;
    struct bt_gatt_subscribe_params *sub_params = NULL;
    ble_air_cntx_t *context = ble_air_get_cntx_by_handle(conn->handle);

    if (attr == NULL) {
        LOG_INF("[BLE][CLIENT] Setup complete for ble_air_client_cntx_t");
        (void)memset(params, 0, sizeof(*params));
        return BT_GATT_ITER_STOP;
    }

    LOG_INF("[BLE][CLIENT] [ATTRIBUTE] handle 0x%04X", attr->handle);

    if (params->type == BT_GATT_DISCOVER_CHARACTERISTIC) {
        chrc = (struct bt_gatt_chrc *)attr->user_data;

        if (bt_uuid_cmp(chrc->uuid, AIR_TX_CHAR_UUID) == 0) {
            LOG_INF("[BLE][CLIENT] ble air tx handle");
            context->tx_handle = chrc->value_handle;
            sub_params = &context->tx_sub_params;
#if defined(CONFIG_BT_GATT_AUTO_DISCOVER_CCC) || defined(__DOXYGEN__)
            sub_params->disc_params = &context->tx_sub_disc_params;
#endif
        } else if (bt_uuid_cmp(chrc->uuid, AIR_RX_CHAR_UUID) == 0) {
            LOG_INF("[BLE][CLIENT] ble air rx handle");
            context->rx_handle = chrc->value_handle;
        }

        if (sub_params != NULL) {
            sub_params->value = BT_GATT_CCC_NOTIFY;
            sub_params->value_handle = chrc->value_handle;
            sub_params->ccc_handle = 0;
#if defined(CONFIG_BT_GATT_AUTO_DISCOVER_CCC) || defined(__DOXYGEN__)
            sub_params->end_handle = context->end_handle;
#endif
            sub_params->notify = ble_air_notify_handler;
            atomic_set_bit(sub_params->flags, BT_GATT_SUBSCRIBE_FLAG_VOLATILE);

            err = bt_gatt_subscribe(conn, sub_params);
            if (err == 0 || err == -EALREADY) {
                ble_air_srv_notify_connected(context->conn->handle, &context->conn->le.dst.a);
                LOG_INF("[BLE][CLIENT] Subscribed to handle 0x%04X", attr->handle);
            } else {
                LOG_INF("[BLE][CLIENT] Could not subscribe to handle 0x%04X (%d)", attr->handle, err);
                return BT_GATT_ITER_STOP;
            }
        }
    }

    return BT_GATT_ITER_CONTINUE;
}

static uint8_t ble_air_primary_discover_func(struct bt_conn *conn,
                 const struct bt_gatt_attr *attr,
                 struct bt_gatt_discover_params *params)
{
    struct bt_gatt_service_val *prim_service;
    ble_air_cntx_t *context = ble_air_get_cntx_by_handle(conn->handle);

    if (attr == NULL) {
        LOG_ERR("[BLE][CLIENT] Could not find a ble air instance on the server");
        //vcp_vol_ctlr_discover_complete(vol_ctlr, -ENODATA);

        return BT_GATT_ITER_STOP;
    }

    LOG_INF("[BLE][CLIENT] [ATTRIBUTE] handle 0x%04X", attr->handle);

    if (params->type == BT_GATT_DISCOVER_PRIMARY) {
        int err;

        LOG_INF("[BLE][CLIENT] Primary discover complete");
        prim_service = (struct bt_gatt_service_val *)attr->user_data;

        context->start_handle = attr->handle + 1;
        context->end_handle = prim_service->end_handle;

        /* Discover characteristics */
        context->discover_params.uuid = NULL;
        context->discover_params.start_handle = context->start_handle;
        context->discover_params.end_handle = context->end_handle;
        context->discover_params.type = BT_GATT_DISCOVER_CHARACTERISTIC;
        context->discover_params.func = ble_air_discover_func;

        err = bt_gatt_discover(conn, &context->discover_params);
        if (err != 0) {
            LOG_INF("[BLE][CLIENT] Discover failed (err %d)", err);
            //vcp_vol_ctlr_discover_complete(vol_ctlr, err);
        }

        return BT_GATT_ITER_STOP;
    }

    return BT_GATT_ITER_CONTINUE;
}

static void ble_air_context_reset(const struct bt_conn *conn)
{
    if (conn == NULL) {
        return;
    }
    ble_air_cntx_t *context = ble_air_get_cntx_by_handle(conn->handle);
    if (context == NULL) {
        return;
    }
    context->start_handle = 0;
    context->end_handle = 0;
    context->rx_handle = 0;
    context->tx_handle = 0;
    context->cccd_handle = 0;
    context->cccd_handle = 0;
    memset(&context->tx_sub_params, 0 , sizeof(struct bt_gatt_subscribe_params));
    memset(&context->tx_sub_disc_params, 0 , sizeof(struct bt_gatt_discover_params));
    memset(&context->cccd_sub_params, 0 , sizeof(struct bt_gatt_subscribe_params));
    memset(&context->cccd_sub_disc_params, 0 , sizeof(struct bt_gatt_discover_params));
    memset(&context->write_params, 0 , sizeof(struct bt_gatt_write_params));
    memset(&context->read_params, 0 , sizeof(struct bt_gatt_read_params));
    memset(&context->discover_params, 0 , sizeof(struct bt_gatt_discover_params));
    memset(&context->uuid, 0 , sizeof(struct bt_uuid_16));
}

static void ble_air_exchange_func(struct bt_conn *conn, uint8_t err,
              struct bt_gatt_exchange_params *params)
{
    if (err == 0) {
        /*begin discover*/
        ble_air_cntx_t *ble_client_context;
        if (conn == NULL) {
            LOG_ERR("[BLE][CLIENT] conn is null");
            return;
        }

        ble_client_context = ble_air_get_cntx_by_handle(conn->handle);
        if (ble_client_context == NULL) {
            return;
        }

        ble_air_context_reset(conn);

        memcpy(&ble_client_context->uuid, AIR_SERVICE_UUID, sizeof(ble_client_context->uuid));

        //ble_client_context->conn = bt_conn_ref(conn);
        ble_client_context->discover_params.func = ble_air_primary_discover_func;
        ble_client_context->discover_params.uuid = &ble_client_context->uuid.uuid;
        ble_client_context->discover_params.type = BT_GATT_DISCOVER_PRIMARY;
        ble_client_context->discover_params.start_handle = BT_ATT_FIRST_ATTRIBUTE_HANDLE;
        ble_client_context->discover_params.end_handle = BT_ATT_LAST_ATTRIBUTE_HANDLE;

        bt_gatt_discover(conn, &ble_client_context->discover_params);

    } else {
        LOG_ERR("[BLE][CLIENT] mtu exchange fail");
    }
}
#endif

#if defined(AIR_PURE_GAMING_DONGLE_ENABLE)
ble_air_status_t ble_client_write_data(uint16_t conn_handle, uint8_t *buffer, uint32_t size)
{
    return BLE_AIR_STATUS_FAIL;
#if 0
    ble_air_cntx_t *context = ble_air_get_cntx_by_handle(conn_handle);
    if (context == NULL || buffer == 0) {
        return 0;
    }
    int err;
    //const uint8_t att_write_header_size = 3; /* opcode (1) + handle (2) */
    //const uint16_t max_write_size = bt_gatt_get_mtu(context->conn) - att_write_header_size;
    err = bt_gatt_write_without_response(context->conn, context->rx_handle, buffer, size, false);
    if (err != 0) {
        LOG_INF("[BLE][CLIENT] ble_client_write_data fail \r\n");
        return BLE_AIR_STATUS_FAIL;
    } else {
        return BLE_AIR_STATUS_OK;
    }
#endif
}
#endif
void *bt_air_mem_alloc(uint32_t size)
{
    void *memory = NULL;
    memory = k_malloc(size);
    if (memory != NULL) {
        memset(memory, 0, size);
    }
    return memory;
}

void bt_air_mem_free(void *buf)
{
    if (buf) {
        k_free(buf);
        buf = NULL;
    }
}

//Mutex
int ble_air_mutex_create(void)
{
    return k_mutex_init(&ble_air_mutex);
}

void ble_air_mutex_lock(void)
{
    k_mutex_lock(&ble_air_mutex, K_FOREVER);
}

void ble_air_mutex_unlock(void)
{
    k_mutex_unlock(&ble_air_mutex);
}


/********************Connection Info**************************/
static bool ble_air_has_real_connected(uint16_t connect_handle)
{
    uint8_t i = 0;
    for (i = 0; i < BT_CONNECTION_MAX; i++) {
        if (g_air_cntx[i].is_real_connected && NULL != g_air_cntx[i].conn && g_air_cntx[i].conn_handle == connect_handle && CONNECTION_HANDLE_IS_VALIAD(connect_handle)) {
            LOG_INF("[AIR][LE] air has connected index = %d, conenction handle = %02x", i, g_air_cntx[i].conn_handle);
            return true;
        }
    }
    if (i == BT_CONNECTION_MAX) {
        //LOG_MSGID_I(AIR, "ble_air_has_real_connected,no real connected link!\r\n", 0);
    }
    return false;
}


uint16_t ble_air_get_real_connected_handle(void)
{
    uint8_t i = 0;
    for (i = 0; i < BT_CONNECTION_MAX; i++) {
        if (NULL != g_air_cntx[i].conn && (CONNECTION_HANDLE_IS_VALIAD(g_air_cntx[i].conn_handle)) &&
            (g_air_cntx[i].is_real_connected)) {
            return g_air_cntx[i].conn_handle;
        }
    }
    if (i == BT_CONNECTION_MAX) {
        //LOG_MSGID_I(AIR, "ble_air_get_cntx_by_handle,not connected!\r\n", 0);
    }
    return 0xFFFF;
}

ble_air_cntx_t *ble_air_get_cntx_by_handle(uint16_t conn_handle)
{
    uint8_t i = 0;
    for (i = 0; i < BT_CONNECTION_MAX; i++) {
        if ((CONNECTION_HANDLE_IS_VALIAD(conn_handle)) && (NULL != g_air_cntx[i].conn) && (conn_handle == g_air_cntx[i].conn_handle)) {
            return &(g_air_cntx[i]);
        }
    }
    if (i == BT_CONNECTION_MAX) {
        LOG_ERR("ble_air_get_cntx_by_handle,not connected!\r\n");
    }
    return NULL;
}

ble_air_status_t ble_air_srv_notify_connected(uint16_t connection_handle, bt_addr_t *address)
{
    ble_air_connect_t connect_param;
    struct bt_conn conn;
    bt_addr_le_t addr_le;

    memset(&connect_param, 0x0, sizeof(ble_air_connect_t));
    memset(&conn, 0x0, sizeof(struct bt_conn));
    memset(&addr_le, 0x0, sizeof(bt_addr_le_t));
    conn.handle = connection_handle;
    memcpy(addr_le.a.val, address->val, sizeof(bt_addr_t));
    conn.le.dst = addr_le;
    connect_param.conn = &conn;


    //LOG_INF("ble_air_srv_notify_connected BLE_AIR_EVENT_CONNECT_IND hande:%x, %02x:%02x:%02x:%02x:%02x:%02x", connection_handle, connect_param.conn->le.dst.a.val[0], connect_param.conn->le.dst.a.val[1],
    //    connect_param.conn->le.dst.a.val[2],connect_param.conn->le.dst.a.val[3],connect_param.conn->le.dst.a.val[4],connect_param.conn->le.dst.a.val[5]);

    ble_air_event_callback(BLE_AIR_EVENT_CONNECT_IND, (void *)&connect_param);
    return BLE_AIR_STATUS_OK;
}

ble_air_status_t ble_air_srv_notify_disconnected(uint16_t connection_handle, bt_addr_t *address)
{
    ble_air_disconnect_t *connect_param = bt_air_mem_alloc(sizeof(ble_air_disconnect_t));
    struct bt_conn *conn = bt_air_mem_alloc(sizeof(struct bt_conn));
    bt_addr_le_t *addr_le = bt_air_mem_alloc(sizeof(bt_addr_le_t));

    if (!connect_param || !conn || !addr_le) {
          bt_air_mem_free(connect_param);
          bt_air_mem_free(conn);
          bt_air_mem_free(addr_le);
          return BLE_AIR_STATUS_FAIL;
    }
    memset(connect_param, 0, sizeof(ble_air_disconnect_t));
    memset(conn, 0, sizeof(struct bt_conn));
    memset(addr_le, 0, sizeof(bt_addr_le_t));

    conn->handle = connection_handle;
    memcpy(addr_le->a.val, address->val, sizeof(bt_addr_t));
    conn->le.dst = *addr_le;
    connect_param->conn = conn;
    connect_param->disconnect_reason = BLE_AIR_DISCONNECT_REASON_NORMAL;

    LOG_INF("ble_air_srv_notify_disconnected, %02x:%02x:%02x:%02x:%02x:%02x",
        connect_param->conn->le.dst.a.val[0], connect_param->conn->le.dst.a.val[1],
        connect_param->conn->le.dst.a.val[2], connect_param->conn->le.dst.a.val[3],
        connect_param->conn->le.dst.a.val[4], connect_param->conn->le.dst.a.val[5]);

    ble_air_event_callback(BLE_AIR_EVENT_DISCONNECT_IND, (void *)connect_param);


    bt_air_mem_free(conn);
    bt_air_mem_free(addr_le);
    bt_air_mem_free(connect_param);

    return BLE_AIR_STATUS_OK;
}

static ble_air_status_t ble_air_save_connection_info(struct bt_conn *buff)
{
    uint8_t i = 0;
    ble_air_status_t status = BLE_AIR_STATUS_OK;
    struct bt_conn *conn_ind = buff;

    for (i = 0; i < BT_CONNECTION_MAX; i++) {
        /**< first connect, to save connection info. */
        struct bt_conn b_conn = {0};
        g_air_cntx[i].conn = &b_conn;
        if (g_air_cntx[i].conn_handle == 0xffff) {
            if (CONNECTION_HANDLE_IS_VALIAD(conn_ind->handle)) {
                g_air_cntx[i].conn = conn_ind;
                g_air_cntx[i].conn_handle = conn_ind->handle;
                LOG_INF("[AIR][LE] connect handle:%x, i:%d", g_air_cntx[i].conn->handle, i);
                g_air_cntx[i].revert_interval = conn_ind->le.interval;
                g_air_cntx[i].revert_supervision_timeout = conn_ind->le.timeout;
    #if 0//defined(AIR_PURE_GAMING_DONGLE_ENABLE)
                static struct bt_gatt_exchange_params exchange_params;
                exchange_params.func = ble_air_exchange_func;
                uint8_t err = bt_gatt_exchange_mtu(conn_ind, &exchange_params);
                if (err) {
                    LOG_ERR("[BLE][CLIENT]MTU exchange failed (err %d)", err);
                }
    #endif
            } else {
                LOG_INF("[AIR][LE] conn_ind->Handle error:%x", conn_ind->handle);
            }

            break;
            /**< Reconnect. */
        } else if (conn_ind->handle == g_air_cntx[i].conn_handle) {
            LOG_INF("[AIR][LE] conn_ind->Handle error1:%x, %x, %x", conn_ind->handle, g_air_cntx[i].conn_handle, i);
            break;
        }
    }
    if (i == BT_CONNECTION_MAX) {
        status = BLE_AIR_STATUS_FAIL;
    }
    return status;
}

static ble_air_status_t ble_air_delete_connection_info(struct bt_conn *buff)
{
    uint8_t i;
    ble_air_status_t status = BLE_AIR_STATUS_OK;
    struct bt_conn *disconn_ind = buff;
    for (i = 0; i < BT_CONNECTION_MAX ; i++) {
        if (disconn_ind->handle == g_air_cntx[i].conn_handle) {
            LOG_INF("[AIR][LE] disconnection context:%02x, connection_handle = %02x", &g_air_cntx[i], g_air_cntx[i].conn->handle);
            memset(&(g_air_cntx[i]), 0, sizeof(ble_air_cntx_t));
            memset(&(g_air_cntx[i].conn), 0, sizeof(g_air_cntx[i].conn));
            g_air_cntx[i].conn = NULL;
            g_air_cntx[i].conn_handle = 0xffff;
            g_air_cntx[i].receive_buffer = NULL;

            break;
        }
    }
    if (i == BT_CONNECTION_MAX) {
        status = BLE_AIR_STATUS_FAIL;
    }
    return status;
}

static void ble_air_reset_connection_cntx(void)
{
    uint8_t i;
    for (i = 0; i < BT_CONNECTION_MAX ; i++) {
        memset(&(g_air_cntx[i]), 0, sizeof(ble_air_cntx_t));
        g_air_cntx[i].receive_buffer = NULL;
        g_air_cntx[i].conn = NULL;
        g_air_cntx[i].conn_handle = 0xffff;
    }
}

/**********************************************/

static void ble_air_cccd_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
    LOG_INF("ble_air_cccd_changed:%x", value);
    return;
}

/**
 * @brief Function for handling Client Configuration Characteristisc Descriptor's read and write event.
 *
 * @param[in]   rw                    Flag of Read or Write event.
 * @param[in]   handle                Connection handle.
 * @param[in]   size                  Length of the data.
 * @param[in]   *data                 Data buffer.
 * @param[in]   *data                 Data buffer.
 * @param[in]  offset                 Write or Read offset.
 *
 * @return      Real wrote or read length of the data.
 */
static ssize_t ble_air_tx_char_cccd_callback(struct bt_conn *conn, const struct bt_gatt_attr *attr, uint16_t value)
{
    if (!attr || !conn) {
        LOG_ERR("ble_air_tx_char_cccd_callback attr is null");
        return 0;
    }
    LOG_INF("ble_air_tx_char_cccd_callback, handle = %02x, value = %x \r\n", conn->handle, value);
    uint16_t handle = conn->handle;
    ble_air_cntx_t *temp_cntx = ble_air_get_cntx_by_handle(handle);
    if ((CONNECTION_HANDLE_IS_VALIAD(handle)) && (temp_cntx)) {
        /** record for each connection. */
        //g_air_cntx.notify_enabled = *(uint16_t *)data;
        if ((false == ble_air_has_real_connected(handle)) || (0 == value && true == temp_cntx->is_real_connected)) {
            temp_cntx->notify_enabled = value;
        } else {
            LOG_INF("[AIR][LE] enable air cccd fail, is real connected = %d", ble_air_has_real_connected(handle));
            return 0;
        }
        if ((0 == ble_air_check_user()) && (BT_GATT_CCC_NOTIFY == temp_cntx->notify_enabled)) {
            //ble_air_ready_to_write_t ready_to_write;
            if (false == temp_cntx->is_real_connected) {
                temp_cntx->is_real_connected = true;
                memset(&g_rx_buffer, 0x0, BLE_AIR_RECEIVE_BUFFER_SIZE);
                temp_cntx->receive_buffer = g_rx_buffer;
                LOG_INF("[BLE][AIR]BLE_AIR_EVENT_CONNECT_IND\r\n");
                ble_air_srv_notify_connected(temp_cntx->conn->handle, &temp_cntx->conn->le.dst.a);
            }
        } else if ((0 == ble_air_check_user()) && (0 == temp_cntx->notify_enabled)) {
            if (true == temp_cntx->is_real_connected) {
                //ble_air_disconnect_t disconnect_param;
                temp_cntx->is_real_connected = false;
                temp_cntx->is_link_optimization = false;
                temp_cntx->receive_buffer = NULL;
                memset(&g_rx_buffer, 0x0, BLE_AIR_RECEIVE_BUFFER_SIZE);
                LOG_INF("disconnec handle=0x%04x, because CCCD Disable\r\n", handle);
                ble_air_srv_notify_disconnected(temp_cntx->conn->handle, &temp_cntx->conn->le.dst.a);
            }
        }
        LOG_INF("ble_air_tx_char_cccd_callback, data:%d \r\n", temp_cntx->notify_enabled);
        return sizeof(uint16_t);
    }
    return 0;
}

static ssize_t ble_air_rx_write_char_callback(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf, uint16_t len, uint16_t offset, uint8_t flags)
{
    if (NULL == conn || NULL == attr) {
        LOG_ERR("ble_air_rx_write_char_callback NULL\r\n");
        return 0;
    }
    uint16_t handle = conn->handle;
    ble_air_cntx_t *buffer_t = ble_air_get_cntx_by_handle(handle);
    LOG_INF("ble_air_rx_write_char_callback:handle is %d, size is %d, offset is %d \r\n", handle, len, offset);
    //TODO:Should record for each connection handle.
    if ((CONNECTION_HANDLE_IS_VALIAD(handle)) && (buffer_t) && (buffer_t->is_real_connected)) {
        /**remote write & notify app ready to read*/
        LOG_INF("write length= %d\r\n", len);
        if (len > (BLE_AIR_RECEIVE_BUFFER_SIZE - buffer_t->receive_buffer_length)) {
            LOG_INF("write characteristic: buffer full error!\r\n");
            return 0; /**means fail, buffer full*/
        }
        memcpy((uint8_t *)(buffer_t->receive_buffer + buffer_t->receive_buffer_length), buf, len);
        buffer_t->receive_buffer_length += len;
        if ((0 == ble_air_check_user())) {
            ble_air_ready_to_read_t ready_to_read;
            ready_to_read.conn_handle = conn->handle;
            ready_to_read.data_length = len;
            LOG_INF("write characteristic: write size = %d \r\n", len);
            ble_air_event_callback(BLE_AIR_EVENT_READY_TO_READ_IND, (void *)&ready_to_read);
        }
        return len;
    } else {
        LOG_INF("ble_air write characteristic handle = %02x!\r\n", handle);
        if (buffer_t != NULL) {
            //LOG_MSGID_I(AIR, "ble_air write characteristic is_real_connected = %d!\r\n", 1, buffer_t->is_real_connected);
        }
    }
    return 0;
}

static void ble_air_disconn_event_callback(ble_air_cntx_t *buffer_t)
{
    if (NULL == buffer_t) {
        return;
    }
    //LOG_INF("[AIR][LE] notify user disconnect handle=0x%04x", buffer_t->conn->handle);
    ble_air_srv_notify_disconnected(buffer_t->conn->handle, &buffer_t->conn->le.dst.a);
}

static void ble_air_handle_connected(struct bt_conn *conn, uint8_t err)
{
    if (0 != err || conn == NULL) {
        LOG_ERR("[BLE][AIR]ble_air_handle_connected fail:%x", err);
        return;
    }
    ble_air_save_connection_info(conn);
}

static void ble_air_handle_disconnected(struct bt_conn *conn, uint8_t reason)
{
    if (conn == NULL) {
        LOG_ERR("[BLE][AIR]ble_air_handle_disconnected fail");
        return;
    }
    uint16_t conn_handle = conn->handle;
    ble_air_cntx_t *buffer_t = ble_air_get_cntx_by_handle(conn_handle);
    if ((CONNECTION_HANDLE_IS_VALIAD(conn_handle)) && (buffer_t)) {
#if (defined(AIR_PURE_GAMING_DONGLE_ENABLE))
        if (0 == ble_air_check_user()) {
            ble_air_disconn_event_callback(buffer_t);
        }
 #else
        if (0 == ble_air_check_user() && (buffer_t->is_real_connected)) {
            ble_air_disconn_event_callback(buffer_t);
        }
#endif
        ble_air_delete_connection_info(conn);
    }
}

void ble_air_link_performace_optimization_revert(void)
{
    uint32_t i = 0;
    int result = 0;
    for (i = 0; i < BT_CONNECTION_MAX; i++) {
        if (NULL != g_air_cntx[i].conn && (CONNECTION_HANDLE_IS_VALIAD(g_air_cntx[i].conn_handle)) &&
            (g_air_cntx[i].is_link_optimization) && (g_air_cntx[i].is_real_connected)) {
            g_air_cntx[i].is_link_optimization = false;
            link_update_state = BLE_AIR_LINK_UPDATE_STATE_OPTIMIZE_REVERT;
            struct bt_le_conn_param conn_param = {
                .interval_min = g_air_cntx[i].revert_interval,
                .interval_max = g_air_cntx[i].revert_interval,
                .latency      = 0,
                .timeout      = g_air_cntx[i].revert_supervision_timeout
            };
            result = bt_conn_le_param_update(g_air_cntx[i].conn, &conn_param);
            LOG_INF("[AIR][LE] ble_air_link_performace_optimization_revert result = %d", result);
            return;
        }
    }
    link_update_state = BLE_AIR_LINK_UPDATE_STATE_NONE;
    LOG_INF("[BLE][AIR] all link optimization revert complete");
}

void ble_air_link_performace_optimization(void)
{
    uint32_t i = 0;
    int result = 0;
    for (i = 0; i < BT_CONNECTION_MAX; i++) {
        if (NULL != g_air_cntx[i].conn && (CONNECTION_HANDLE_IS_VALIAD(g_air_cntx[i].conn_handle)) &&
            (!g_air_cntx[i].is_link_optimization) && (g_air_cntx[i].is_real_connected)) {
            link_update_state = BLE_AIR_LINK_UPDATE_STATE_OPTIMIZING;
            g_air_cntx[i].is_link_optimization = true;
            /* Update conenction interval to 30ms */
            struct bt_le_conn_param conn_param = {
                .interval_min = 0x0018,
                .interval_max = 0x0018,
                .latency      = 0,
                .timeout      = 0x1F4
            };

            result = bt_conn_le_param_update(g_air_cntx[i].conn, &conn_param);
            LOG_INF("[AIR][LE] ble_air_link_performace_optimization result = %d", result);
            return;
        }
    }
    link_update_state = BLE_AIR_LINK_UPDATE_STATE_OPTIMIZED;
    LOG_INF("[BLE][AIR] all link optimization complete\r\n");
}

static void ble_air_link_performace_optimization_by_handle(struct bt_conn *conn)
{
    if (NULL == conn) {
        LOG_INF("[AIR][LE] ble_air_link_performace_optimization_by_handle conn is null");
        return;
    }
    int result = 0;
    struct bt_le_conn_param conn_param = {
        .interval_min = 0x0018,
        .interval_max = 0x0018,
        .latency      = 0,
        .timeout      = 0x1F4
    };
    result = bt_conn_le_param_update(conn, &conn_param);
    LOG_INF("[AIR][LE] ble_air_link_performace_optimization_by_handle result = %d", result);
}

static void ble_air_handle_le_param_updated(struct bt_conn *conn, uint16_t interval, uint16_t latency, uint16_t timeout)
{
    if (NULL == conn) {
        LOG_INF("[AIR][LE] ble_air_handle_le_param_updated conn is NULL");
        return;
    }
    LOG_INF("[AIR][LE] ble_air_handle_le_param_updated handle:%x, interval:%x, timeout:%x", conn->handle, interval, timeout);
    ble_air_cntx_t *buffer_t = ble_air_get_cntx_by_handle(conn->handle);
    if (NULL != buffer_t && CONNECTION_HANDLE_IS_VALIAD(conn->handle)) {
        if (link_update_state == BLE_AIR_LINK_UPDATE_STATE_OPTIMIZING) {
            ble_air_link_performace_optimization();
        } else if (link_update_state == BLE_AIR_LINK_UPDATE_STATE_OPTIMIZE_REVERT) {
            ble_air_link_performace_optimization_revert();
        } else {
            if (buffer_t->retry_count < BLE_AIR_UPDATE_RETRY_COUNT) {
                if ((buffer_t->is_link_optimization) && (interval != 0x0018)) {
                    ble_air_link_performace_optimization_by_handle(conn);
                }
                buffer_t->revert_interval = interval;
                buffer_t->revert_supervision_timeout = timeout;
                buffer_t->retry_count ++;
            }
        }
    }
    return;
}


static struct bt_conn_cb ble_air_conn_cbs = {
    .connected = ble_air_handle_connected,
    .disconnected = ble_air_handle_disconnected,
    .le_param_updated =ble_air_handle_le_param_updated,
};

/************************************************
*   Functions
*************************************************/
/**
 * @brief Function for sending the Air service tx characteristic value.
 *
 * @param[in]   conn_handle                           connection handle.
 *
 * @return      ble_status_t                              0 means success.
 */
#if !defined(AIR_PURE_GAMING_DONGLE_ENABLE)
static int ble_air_service_tx_send(uint16_t conn_handle, uint8_t *data, uint32_t length)
{
    int status = -1;
    ble_air_cntx_t *buffer_t = ble_air_get_cntx_by_handle(conn_handle);

    if (buffer_t == NULL || buffer_t->conn == NULL) {
        LOG_ERR("ble_air_service_tx_send fail, OOM!\r\n");
        return status;
    }

    if ((CONNECTION_HANDLE_IS_VALIAD(conn_handle)) && (buffer_t) && (buffer_t->is_real_connected) &&
        (BLE_AIR_CCCD_NOTIFICATION == buffer_t->notify_enabled)) {
        status = bt_gatt_notify(buffer_t->conn, &ble_air_service.attrs[4], data, length);
        //LOG_INF("ble_air_service_notify conn_handle is %x, status :%d\r\n", conn_handle, status);
    }
    return status;
}
#endif
 /**
 * @brief Function for application to write data to the send buffer.
 */
uint32_t ble_air_write_data(uint16_t conn_handle, uint8_t *buffer, uint32_t size)
{
    BLEAIR_MUTEX_LOCK();
    uint32_t send_size = 0;
    uint32_t mtu_size;

    ble_air_cntx_t *buffer_t = ble_air_get_cntx_by_handle(conn_handle);
    if (buffer_t == NULL || buffer_t->conn == NULL) {
        LOG_ERR("[BLE][AIR] client send data get conn cntx fail\r\n");
        BLEAIR_MUTEX_UNLOCK();
        return 0;
    }

    mtu_size = bt_gatt_get_mtu(buffer_t->conn);

    LOG_INF("mtu = %d,conn_handle = 0x%x\r\n", mtu_size, conn_handle);
    if (mtu_size <= ATT_HEADER_LENGTH) {
        BLEAIR_MUTEX_UNLOCK();
        return 0;
    }
    if ((mtu_size - ATT_HEADER_LENGTH) < size) {
        send_size = mtu_size - ATT_HEADER_LENGTH;
    } else {
        send_size = size;
    }
    if (0 == send_size) {
        //LOG_MSGID_I(AIR, "[BLE_AIR] ble_air_send_data send_size is 0!\r\n", 0);
        BLEAIR_MUTEX_UNLOCK();
        return 0;
    }
#if defined(AIR_PURE_GAMING_DONGLE_ENABLE)
    if (CONNECTION_HANDLE_IS_VALIAD(conn_handle)) {
        if (BLE_AIR_STATUS_OK == ble_client_write_data(conn_handle, buffer, send_size)) {
            LOG_INF("[BLE][CLIENT] ble_client_write_data: send_size[%ld]\r\n", send_size);
            BLEAIR_MUTEX_UNLOCK();
            return send_size;
        }
    }
#else
    if ((CONNECTION_HANDLE_IS_VALIAD(conn_handle)) && (buffer_t) &&
        (buffer_t->is_real_connected)) {
        if (0 == ble_air_service_tx_send(conn_handle, buffer, send_size)) {
            LOG_INF("[BLE_AIR] ble_air_send_data: send_size[%ld]\r\n", send_size);
            BLEAIR_MUTEX_UNLOCK();
            return send_size;
        }
    }
#endif
    BLEAIR_MUTEX_UNLOCK();
    return 0;
}

uint32_t ble_air_get_rx_available(uint16_t conn_handle)
{
    BLEAIR_MUTEX_LOCK();
    ble_air_cntx_t *buffer_t = ble_air_get_cntx_by_handle(conn_handle);
    if ((CONNECTION_HANDLE_IS_VALIAD(conn_handle)) && (buffer_t) && (buffer_t->is_real_connected)) {
        BLEAIR_MUTEX_UNLOCK();
        return buffer_t->receive_buffer_length;
    }
    BLEAIR_MUTEX_UNLOCK();
    return 0;
}

static uint32_t read_data(ble_air_cntx_t *buffer_t, uint8_t *buffer, uint32_t size)
{
    BLEAIR_MUTEX_LOCK();
    uint32_t read_size = 0;
    if (!buffer_t || !buffer) {
        BLEAIR_MUTEX_UNLOCK();
        return 0;
    }
    if (buffer_t->receive_buffer_length > size) {
        read_size = size;
    } else {
        read_size = buffer_t->receive_buffer_length;
    }
    if (0 == read_size) {
        //LOG_MSGID_I(AIR, "[BLE_AIR] ble_air_read_data: read buffer is null\r\n", 0);
        BLEAIR_MUTEX_UNLOCK();
        return 0;
    }
    memcpy(buffer, buffer_t->receive_buffer, read_size);
    if (buffer_t->receive_buffer_length > read_size) {
        memmove(buffer_t->receive_buffer, (uint8_t *)(buffer_t->receive_buffer + read_size), (buffer_t->receive_buffer_length - read_size));
        buffer_t->receive_buffer_length -= read_size;
    } else {
        buffer_t->receive_buffer_length = 0;
        memset(&g_rx_buffer, 0x0, BLE_AIR_RECEIVE_BUFFER_SIZE);
    }
    LOG_INF("[BLE_AIR] ble_air_read_data: read_size is [%d]\r\n", read_size);
    BLEAIR_MUTEX_UNLOCK();
    return read_size;
}

/**
 * @brief Function for application to read data from the receive buffer.
 */
uint32_t ble_air_read_data(uint16_t conn_handle, uint8_t *buffer, uint32_t size)
{
    ble_air_cntx_t *buffer_t = ble_air_get_cntx_by_handle(conn_handle);
    if (!buffer_t || !buffer) {
        return 0;
    }
#if defined (AIR_PURE_GAMING_DONGLE_ENABLE)
    if (CONNECTION_HANDLE_IS_VALIAD(conn_handle)) {
        return read_data(buffer_t, buffer, size);
    }
#else
    if ((CONNECTION_HANDLE_IS_VALIAD(conn_handle)) && (buffer_t->is_real_connected)) {
        return read_data(buffer_t, buffer, size);
    }
#endif
    return 0;
}

static void ble_air_init_all_cntx(void)
{
    ble_air_reset_connection_cntx();
    memset(&g_rx_buffer, 0x0, BLE_AIR_RECEIVE_BUFFER_SIZE);
}

#ifdef CONFIG_BT_ULL_HID_LE
uint32_t ble_air_srv_read_data(uint16_t conn_handle, uint8_t *buffer, uint32_t size)
{
    if (!buffer) {
        //LOG_MSGID_I(AIR, "[BLE_AIR] ble_air_srv_read_data null\r\n", 0);
        return 0;
    }
    ble_air_ull_cntx_t *buffer_ull = ble_air_ull_get_cntx_by_handle(conn_handle);
    ble_air_cntx_t *buffer_t = ble_air_get_cntx_by_handle(conn_handle);
    if (buffer_ull) {
        return ble_air_ull_read_data(conn_handle, buffer, size);
    }

    if (buffer_t) {
        return ble_air_read_data(conn_handle, buffer, size);
    }
    return 0;
}

static uint32_t read_ull_data(ble_air_ull_cntx_t *buffer_t, uint8_t *buffer, uint32_t size)
{
    BLEAIR_MUTEX_LOCK();
    uint32_t read_size = 0;
    if (!buffer_t || !buffer) {
        BLEAIR_MUTEX_UNLOCK();
        return 0;
    }
    if (buffer_t->receive_buffer_length > size) {
        read_size = size;
    } else {
        read_size = buffer_t->receive_buffer_length;
    }
    if (0 == read_size) {
        //LOG_MSGID_I(AIR, "[BLE_AIR] ull_read_data: read buffer is null\r\n", 0);
        BLEAIR_MUTEX_UNLOCK();
        return 0;
    }
    memcpy(buffer, buffer_t->receive_buffer, read_size);
    if (buffer_t->receive_buffer_length > read_size) {
        memmove(buffer_t->receive_buffer, (uint8_t *)(buffer_t->receive_buffer + read_size), (buffer_t->receive_buffer_length - read_size));
        buffer_t->receive_buffer_length -= read_size;
    } else {
        buffer_t->receive_buffer_length = 0;
        memset(&g_rx_buffer, 0x0, BLE_AIR_RECEIVE_BUFFER_SIZE);
    }
    LOG_INF("[BLE_AIR] ull_read_data: read_size is [%d]\r\n", read_size);
    BLEAIR_MUTEX_UNLOCK();
    return read_size;
}

uint32_t ble_air_ull_read_data(uint16_t conn_handle, uint8_t *buffer, uint32_t size)
{
    ble_air_ull_cntx_t *buffer_t = ble_air_ull_get_cntx_by_handle(conn_handle);
    if (!buffer_t || !buffer) {
        //LOG_MSGID_I(AIR, "[BLE_AIR] ble_air_ull_read_data null\r\n", 0);
        return 0;
    }
    if (CONNECTION_HANDLE_IS_VALIAD(conn_handle)) {
        return read_ull_data(buffer_t, buffer, size);
    }

    //LOG_MSGID_I(AIR, "[BLE_AIR] ble_air_ull_read_data: conn id error [%d]\r\n", 1, conn_handle);
    return 0;
}

uint32_t ble_air_srv_write_data(uint16_t conn_handle, uint8_t *buffer, uint32_t size)
{
    if (NULL == buffer || size == 0) {
        LOG_INF("[BLE_AIR] ble_air_srv_write_data para error,size:%x !!", size);
        return 0;
    }
    ble_air_ull_cntx_t *buffer_ull = ble_air_ull_get_cntx_by_handle(conn_handle);
    ble_air_cntx_t *buffer_t = ble_air_get_cntx_by_handle(conn_handle);
    if (NULL != buffer_ull) {
        return ble_air_ull_write_data(conn_handle, buffer, size);
    }
    if (NULL != buffer_t) {
        return ble_air_write_data(conn_handle, buffer, size);
    }
    return 0;
}


uint32_t ble_air_ull_write_data(uint16_t conn_handle, uint8_t *buffer, uint32_t size)
{
    BLEAIR_MUTEX_LOCK();
    if (NULL == buffer || size == 0) {
        LOG_INF("[BLE_AIR] ble_air_ull_write_data para error,size:%x !!", size);
    }
    uint32_t send_size = 0;
    uint32_t mtu_size;
    //ble_air_status_t status = BLE_AIR_STATUS_FAIL;
    int status = -1;
    ble_air_ull_cntx_t *buffer_t = ble_air_ull_get_cntx_by_handle(conn_handle);
    if (buffer_t == NULL) {
        LOG_INF("[BLE][AIR][ULL] client send data get conn cntx fail\r\n");
        BLEAIR_MUTEX_UNLOCK();
        return 0;
    }
    mtu_size = buffer_t->mtu;
    if (buffer_t->mtu == 0) {
        LOG_INF("[BLE_AIR] ble_air_ull_write_data send fail,mtu is 0");
        BLEAIR_MUTEX_UNLOCK();
        return 0;
    }
    if (size > mtu_size) {
        send_size = mtu_size;
    } else {
        send_size = size;
    }
    bt_ull_user_data_t ull_user_data = {0};
    memcpy(&ull_user_data.remote_address, &buffer_t->peer_address.a, sizeof(bt_addr_t));
    ull_user_data.user_data = buffer;
    ull_user_data.user_data_length = send_size;
    status = bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_TX_RACE_DATA, &ull_user_data, sizeof(bt_ull_user_data_t));
    LOG_INF("[BLE_AIR] ble_air_ull_write_data send status:%d, handle :%x ,send_size:%x,mtu_size:%x", status, conn_handle, send_size, mtu_size);
    if (status == 0) {
        BLEAIR_MUTEX_UNLOCK();
        return send_size;
    }
    BLEAIR_MUTEX_UNLOCK();
    return 0;
}
#if 0
ble_air_status_t ble_air_switch_link(bt_ull_le_hid_srv_link_mode_t mode, bt_addr_le_t *addr)
{
    if (!addr) {
        //LOG_MSGID_E(AIR, "[AIR][LE]ble_air_switch_link mode wrong", 0);
        return BLE_AIR_STATUS_FAIL;
    }
    uint8_t i = 0;
    ble_air_status_t status = BLE_AIR_STATUS_FAIL;
    struct bt_conn tmp_conn;
    memset(&tmp_conn, 0, sizeof(tmp_conn));
    bt_ull_le_hid_srv_switch_link_mode_t link_mode = {0};
    link_mode.conn = &tmp_conn;
    switch (mode) {
        case BT_ULL_LE_HID_SRV_LINK_MODE_FOTA: {
            for (i = 0; i < BT_CONNECTION_MAX; i ++) {
                if (CONNECTION_HANDLE_IS_VALIAD(g_air_ull_cntx[i].handle) &&
                    (memcmp(&g_air_ull_cntx[i].peer_address, addr, sizeof(bt_addr_le_t)) == 0)) {
                    link_mode.conn->handle= g_air_ull_cntx[i].handle;
                    link_mode.link_mode = mode;
                    status = bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_SWITCH_LINK_MODE, &link_mode, sizeof(bt_ull_le_hid_srv_switch_link_mode_t));
                    /*fota switch the link to ble*/
                    if (0 == status) {
                        g_switch_cis_link_flag = true;
                    }
                    LOG_INF("[AIR][LE]BT_ULL_LE_HID_SRV_LINK_MODE_FOTA status = %x", status);
                    break;
                }
            }
            break;
        }
        case BT_ULL_LE_HID_SRV_LINK_MODE_NORMAL: {
            for (i = 0; i < BT_CONNECTION_MAX; i ++) {
                if (CONNECTION_HANDLE_IS_VALIAD(g_air_cntx[i].conn->handle) && (true == g_air_cntx[i].is_real_connected) &&
                    (memcmp(&g_air_cntx[i].conn->le.dst, addr, sizeof(bt_addr_le_t)) == 0)) {
                    link_mode.conn->handle = g_air_cntx[i].conn->handle;
                    link_mode.link_mode = mode;
                    status = bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_SWITCH_LINK_MODE, &link_mode, sizeof(bt_ull_le_hid_srv_switch_link_mode_t));
                    /*fota switch the link to ull*/
                    LOG_INF("[AIR][LE]BT_ULL_LE_HID_SRV_LINK_MODE_NORMAL status = %x", status);
                    break;
                }
            }
            break;
        }
        default: {
            break;
        }
    }
    return status;
}
#endif
static void ble_air_ull_delete_connection_info(void *buff)
{
    uint8_t i;
    bt_ull_le_hid_srv_disconnected_ind_t *disconn_ind = (bt_ull_le_hid_srv_disconnected_ind_t *) buff;
    //LOG_MSGID_I(AIR, "ble_air_ull_delete_connection_info", 0);
    for (i = 0; i < BT_CONNECTION_MAX ; i++) {
        if (disconn_ind->conn->handle == g_air_ull_cntx[i].handle) {
            LOG_INF("[AIR][LE][ULL] disconnection context:%02x, connection_handle = %02x", &g_air_ull_cntx[i], g_air_ull_cntx[i].handle);
            memset(&(g_air_ull_cntx[i]), 0, sizeof(ble_air_ull_cntx_t));
            memset(&g_air_ull_cntx[i].peer_address, 0, sizeof(bt_addr_le_t));
            g_air_ull_cntx[i].handle = 0xffff;
            break;
        }
    }
    if (i >= BT_CONNECTION_MAX) {
        LOG_INF("[AIR][LE][ULL] not find connect handle:%x", disconn_ind->conn->handle);
    }
}

#if 0
static void ble_air_ull_disconn_event_callback(uint16_t conn_handle, ble_air_ull_cntx_t *buffer_t)
{
    if (NULL == buffer_t) {
        return;
    }
    ble_air_disconnect_t disconnect_param;
    memset(&disconnect_param, 0, sizeof(ble_air_disconnect_t));
    disconnect_param.conn->handle= conn_handle;
    disconnect_param.disconnect_reason = BLE_AIR_DISCONNECT_REASON_NORMAL;
    memcpy(&disconnect_param.bdaddr, &(buffer_t->peer_address), BT_BD_ADDR_LEN);
    LOG_MSGID_I(AIR, "[AIR][LE][ULL] notify user disconnect handle=0x%04x", 1, conn_handle);
    ble_air_event_callback(BLE_AIR_EVENT_DISCONNECT_IND, (void *)&disconnect_param);
}
#endif

ble_air_ull_cntx_t *ble_air_ull_get_cntx_by_handle(uint16_t conn_handle)
{
    uint8_t i = 0;
    for (i = 0; i < BT_CONNECTION_MAX; i++) {
        if (CONNECTION_HANDLE_IS_VALIAD(conn_handle) && (conn_handle == g_air_ull_cntx[i].handle)) {
            return &(g_air_ull_cntx[i]);
        }
    }
    if (i == BT_CONNECTION_MAX) {
        //LOG_MSGID_I(AIR, "ble_air_ull_get_cntx_by_handle,not connected!\r\n", 0);
    }
    return NULL;
}

static void ble_air_ull_init_all_cntx(void)
{
    uint8_t i;
    //LOG_MSGID_I(AIR, "ble_air_ull_init_all_cntx", 0);
    for (i = 0; i < BT_CONNECTION_MAX ; i++) {
        memset(&(g_air_ull_cntx[i]), 0, sizeof(ble_air_ull_cntx_t));
        memset(&g_air_ull_cntx[i].peer_address, 0, sizeof(g_air_ull_cntx[i].peer_address));
        g_air_ull_cntx[i].handle = 0xffff;
        g_air_ull_cntx[i].receive_buffer = NULL;
    }
    memset(&g_rx_buffer, 0x0, BLE_AIR_RECEIVE_BUFFER_SIZE);
}

#if 0
static void ble_air_ull_set_cccd(uint16_t conn_handle, uint16_t att_handle, uint16_t cccd)
{

    bt_status_t ret;
    uint8_t p_buf[5];

    BT_GATTC_NEW_WRITE_CHARC_REQ(req, p_buf, att_handle, (uint8_t *)&cccd, BLE_AIR_ULL_CCCD_VALUE_LEN);

    if (BT_STATUS_SUCCESS != (ret = bt_gattc_write_charc(handle, &req))) {
        LOG_MSGID_I(AIR, "[BLE][AIR] set_cccd, fail! handle:%x att_handle:%x ret:%x", 3, handle, att_handle, ret);
    }

    return ret;
}
#endif

void ble_air_ull_le_hid_callback(bt_ull_event_t event, void *param, uint32_t param_len)
{
    if (NULL == param) {
        //LOG_MSGID_E(AIR, "ble_air_ull_le_hid_callback param is NULL", 0);
        return;
    }

    LOG_INF("ble_air_ull_le_hid_callback event = %x", event);
    switch (event) {
        /* cis service connected*/
        case BT_ULL_EVENT_LE_HID_SERVICE_CONNECTED_IND: {
            bt_ull_le_hid_srv_service_connected_ind_t *conn_ind = (bt_ull_le_hid_srv_service_connected_ind_t *)param;
            if (conn_ind->status != BT_HCI_ERR_SUCCESS) {
                LOG_INF("ble_air_ull_le_hid_callback param status is wrong:%x", conn_ind->status);
                break;
            }
            bt_ull_le_hid_srv_fota_info b_ull_info = {0};
            //uint8_t  temp_val[BT_ADDR_SIZE] = {0};
            bt_ull_le_hid_srv_get_fota_info(&conn_ind->peer_addr, &b_ull_info);
            /*LOG_INF("ble_air_ull_le_hid_callback addr: %x:%x:%x:%x:%x:%x",
                        conn_ind->peer_addr.addr[0], conn_ind->peer_addr.addr[1], conn_ind->peer_addr.addr[2], conn_ind->peer_addr.addr[3], conn_ind->peer_addr.addr[4], conn_ind->peer_addr.addr[5]);*/
            //uint8_t i = 0;
            uint8_t j = 0;
            /* first check whether LE link connected or not*/
            #if 0
            for (i = 0; i < BT_CONNECTION_MAX; i ++) {
                if (memcmp(&g_air_cntx[i].conn->le.dst.a.val, temp_val, sizeof(bt_addr_t)) != 0 && memcmp(&g_air_cntx[i].conn->le.dst.a.val, conn_ind->peer_addr.a.val, sizeof(bt_addr_t)) == 0) {
                    /*g_air_cntx[i].remote_type = b_ull_info.device_type;
                    g_air_cntx[i].remote_att_handle_rx = b_ull_info.att_handle_rx;
                    g_air_cntx[i].remote_att_handle_tx = b_ull_info.att_handle_tx;
                    g_air_cntx[i].remote_att_handle_cccd = b_ull_info.att_handle_cccd;
                    */
                    LOG_INF("ble_air_ull_le_hid_callback device:%x, %x, %x, %x", b_ull_info.device_type, b_ull_info.att_handle_rx,
                                b_ull_info.att_handle_tx, b_ull_info.att_handle_cccd);
                    /*dongle role*/
                }
            }
            #endif
            //LOG_INF("ble_air_ull_le_hid_callback i:%x,BT_CONNECTION_MAX:%x", i, BT_CONNECTION_MAX);
            /*LE link is not connected, its cis*/
            //if (i >= BT_CONNECTION_MAX) {
                for (j = 0; j < BT_CONNECTION_MAX; j ++) {
                    if (CONNECTION_HANDLE_IS_VALIAD(g_air_ull_cntx[j].handle) && g_air_ull_cntx[j].handle == conn_ind->conn->handle) {
                        g_air_ull_cntx[j].remote_type = b_ull_info.device_type;
                        g_air_ull_cntx[j].mtu = b_ull_info.mtu;
                        LOG_INF("BT_ULL_EVENT_LE_HID_SERVICE_CONNECTED_IND handle:%x, %x, %x", conn_ind->conn->handle, b_ull_info.device_type,
                                    b_ull_info.mtu);

                        memset(&g_rx_buffer, 0x0, BLE_AIR_RECEIVE_BUFFER_SIZE);
                        g_air_ull_cntx[j].receive_buffer = g_rx_buffer;
                        g_air_ull_cntx[j].receive_buffer_length = 0;
                        ble_air_srv_notify_connected(g_air_ull_cntx[j].handle, &g_air_ull_cntx[j].peer_address.a);
                    }
                }
            //}
            break;
        }
        /* cis link connected*/
        case BT_ULL_EVENT_LE_HID_CONNECTED_IND: {
            bt_ull_le_hid_srv_connected_ind_t *conn_ind = (bt_ull_le_hid_srv_connected_ind_t *)param;
            if (conn_ind->status != BT_HCI_ERR_SUCCESS) {
                LOG_INF("ble_air_ull_le_hid_callback param status is wrong:%x", conn_ind->status);
                break;
            }
            uint8_t j = 0;
            for (j = 0; j < BT_CONNECTION_MAX; j ++) {
                if (g_air_ull_cntx[j].handle == 0 || g_air_ull_cntx[j].handle == 0xffff) {
                    g_air_ull_cntx[j].handle = conn_ind->conn->handle;
                    memcpy(&g_air_ull_cntx[j].peer_address, &conn_ind->peer_addr, sizeof(bt_addr_le_t));
                    LOG_INF("ULL BT_ULL_EVENT_LE_HID_CONNECTED_IND,handle:%x\r\n", conn_ind->conn->handle);
                    break;
                }
            }
            break;
        }
        /*cis disconnect*/
        case BT_ULL_EVENT_LE_HID_DISCONNECTED_IND: {
            bt_ull_le_hid_srv_disconnected_ind_t *disconn_ind = (bt_ull_le_hid_srv_disconnected_ind_t *)param;
            LOG_INF("ULL BT_ULL_EVENT_LE_HID_DISCONNECTED_IND handle:%x\r\n", disconn_ind->conn->handle);
            ble_air_ull_cntx_t *buffer_t = ble_air_ull_get_cntx_by_handle(disconn_ind->conn->handle);
            if (CONNECTION_HANDLE_IS_VALIAD(disconn_ind->conn->handle) && (buffer_t)) {
                ble_air_srv_notify_disconnected(disconn_ind->conn->handle, &buffer_t->peer_address.a);
                ble_air_ull_delete_connection_info(disconn_ind);
            }
            break;
        }
        /* received cis data*/
        case BT_ULL_EVENT_LE_HID_RACE_DATA_IND: {
            bt_ull_le_hid_srv_race_data_t *user_data = (bt_ull_le_hid_srv_race_data_t *)param;
            ble_air_ull_cntx_t *buffer_t = NULL;
            uint8_t i = 0;
            for (i = 0; i < BT_CONNECTION_MAX; i ++) {
                if (memcmp(&g_air_ull_cntx[i].peer_address.a.val, user_data->remote_address.val, sizeof(bt_addr_t)) == 0) {
                    buffer_t = ble_air_ull_get_cntx_by_handle(g_air_ull_cntx[i].handle);
                    if (NULL != buffer_t && NULL != buffer_t->receive_buffer) {
                        if (user_data->user_data_length > (BLE_AIR_RECEIVE_BUFFER_SIZE - buffer_t->receive_buffer_length)) {
                            LOG_INF("write buffer full error!\r\n");
                            return; /**means fail, buffer full*/
                        }
                        memcpy((uint8_t *)(buffer_t->receive_buffer + buffer_t->receive_buffer_length), user_data->user_data, user_data->user_data_length);
                        buffer_t->receive_buffer_length += user_data->user_data_length;
                        ble_air_ready_to_read_t ready_to_read;
                        ready_to_read.conn_handle = g_air_ull_cntx[i].handle;
                        ready_to_read.data_length = user_data->user_data_length;
                        ble_air_event_callback(BLE_AIR_EVENT_READY_TO_READ_IND, (void *)&ready_to_read);
                    } else {
                        LOG_INF("ULL ble_air_ull_le_hid_callback ready to read is null\r\n");
                    }
                    break;
                }
            }
            break;
        }

        default: {
            break;
        }
    }
}
#endif

#if KERNELVERSION == 0x3030000
static int ble_air_main(const struct device *dev)
#elif KERNELVERSION >= 0x3070000
static int ble_air_main(void)
#else
#error "Unkown supported kernel version"
#endif
{
    LOG_INF("ble_air_main init");
    ble_air_init_all_cntx();
    ble_air_mutex_create();
    bt_conn_cb_register(&ble_air_conn_cbs);
#ifdef CONFIG_BT_ULL_HID_LE
    ble_air_ull_init_all_cntx();
    bt_ull_le_hid_srv_register_callback(BT_ULL_LE_HID_SRV_MODULE_AIR_SRV, ble_air_ull_le_hid_callback);
#endif
#ifndef CONFIG_BT_SETTINGS
    bt_set_bondable(false);
#endif
    return 0;
}

/**
 * @brief Function for application main entry.
 */
ble_air_status_t ble_air_init(ble_air_common_callback_t app_callback)
{
    if (NULL == app_callback) {
        return BLE_AIR_STATUS_INVALID_PARAMETER;
    } else {
        /**Initialize.*/
        return ble_air_cb_register(app_callback);
    }
    return BLE_AIR_STATUS_FAIL;
}

ble_air_status_t ble_air_deinit(ble_air_common_callback_t app_callback)
{
    if (NULL == app_callback) {
        return BLE_AIR_STATUS_INVALID_PARAMETER;
    } else {
        /**Initialize.*/
        return ble_air_cb_deregister(app_callback);
    }
    return BLE_AIR_STATUS_FAIL;
}

static int32_t ble_air_event_callback(ble_air_event_t event_id, void *param)
{
    uint8_t i = 0;
    int32_t ret = 0;
    for (i = 0; i < BLE_AIR_SUPPORT_CB_MAX_NUM; i++) {
        if (ble_air_cb_list[i].in_use && ble_air_cb_list[i].callback != NULL) {
            ble_air_cb_list[i].callback(event_id, param);
            ret = 0;
        }
    }
    return ret;
}

static ble_air_status_t ble_air_check_user(void)
{
    uint8_t i = 0;
    ble_air_status_t status = BLE_AIR_STATUS_OK;
    for (i = 0; i < BLE_AIR_SUPPORT_CB_MAX_NUM; i++) {
        if (ble_air_cb_list[i].in_use) {
            return status;
        }
    }
    if (i == BLE_AIR_SUPPORT_CB_MAX_NUM) {
        status = BLE_AIR_STATUS_FAIL;
    }
    return status;
}

static void ble_air_connection_status_notify(ble_air_common_callback_t callback)
{
    uint16_t conn_handle = ble_air_get_real_connected_handle();
    ble_air_cntx_t *buffer_t = ble_air_get_cntx_by_handle(conn_handle);
    if ((CONNECTION_HANDLE_IS_VALIAD(conn_handle)) && (buffer_t)) {
        ble_air_connect_t connect_param;
        struct bt_conn conn;
        bt_addr_le_t addr_le;
        memset(&connect_param, 0x0, sizeof(ble_air_connect_t));
        memset(&conn, 0x0, sizeof(struct bt_conn));
        memset(&addr_le, 0x0, sizeof(bt_addr_le_t));
        conn.handle = conn_handle;
        memcpy(addr_le.a.val, (buffer_t->conn->le.dst.a.val), sizeof(bt_addr_t));
        conn.le.dst = addr_le;
        connect_param.conn = &conn;
        callback(BLE_AIR_EVENT_CONNECT_IND, (void *)&connect_param);
    }
}

static ble_air_status_t ble_air_cb_register(ble_air_common_callback_t callback)
{
    uint8_t i = 0;
    ble_air_status_t status = 0;
    for (i = 0; i < BLE_AIR_SUPPORT_CB_MAX_NUM; i++) {
        if (!ble_air_cb_list[i].in_use) {
            ble_air_cb_list[i].callback = callback;
            ble_air_cb_list[i].in_use = true;
            ble_air_connection_status_notify(callback);
            break;
        }
    }
    if (i == BLE_AIR_SUPPORT_CB_MAX_NUM) {
        status = BLE_AIR_STATUS_FAIL;
    }
    return status;
}

static ble_air_status_t ble_air_cb_deregister(ble_air_common_callback_t callback)
{
    uint8_t i = 0;
    ble_air_status_t status = 0;
    for (i = 0; i < BLE_AIR_SUPPORT_CB_MAX_NUM; i++) {
        if (ble_air_cb_list[i].in_use && ble_air_cb_list[i].callback == callback) {
            ble_air_cb_list[i].callback = NULL;
            ble_air_cb_list[i].in_use = false;
            break;
        }
    }
    if (i == BLE_AIR_SUPPORT_CB_MAX_NUM) {
        status = BLE_AIR_STATUS_FAIL;
    }
    return status;
}

ble_air_device_id_t ble_air_get_device_id_by_address(bt_addr_t *peer_address)
{
    uint32_t i = 0;
    for (i = 0; i < BT_CONNECTION_MAX; i++) {
        if ((NULL != g_air_cntx[i].conn) && (CONNECTION_HANDLE_IS_VALIAD(g_air_cntx[i].conn->handle)) && (memcmp(&g_air_cntx[i].conn->le.dst.a.val, peer_address->val, sizeof(bt_addr_t)) == 0)) {
            //LOG_MSGID_I(AIR, "[AIR][LE] get device id index = %d, addr %x:%x:%x:%x:%x:%x", 7, i,
                        //((uint8_t *)peer_address)[0], ((uint8_t *)peer_address)[1], ((uint8_t *)peer_address)[2], ((uint8_t *)peer_address)[3], ((uint8_t *)peer_address)[4], ((uint8_t *)peer_address)[5]);
            return (BLE_AIR_DEVICE_ID_BASE + i);
        }
    }
    LOG_INF("[AIR][LE]get device id fail by addr %x:%x:%x:%x:%x:%x",
                peer_address->val[0], peer_address->val[0], peer_address->val[0], peer_address->val[0], peer_address->val[0], peer_address->val[0]);
    return BT_AIR_DEVICE_ID_INVAILD;
}

SYS_INIT(ble_air_main, CONFIG_RACE_CMD_INIT_LEVEL, CONFIG_RACE_CMD_INIT_PRIORITY);
