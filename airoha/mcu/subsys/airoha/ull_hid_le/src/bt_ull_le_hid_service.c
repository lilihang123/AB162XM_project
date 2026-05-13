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

#include "hal_gpt.h"
#include "bt_ull_le_hid_service.h"
#include "bt_ull_le_hid_conn_service.h"
#include "bt_ull_le_hid_utility.h"
#include <zephyr/sys/__assert.h>

#include <zephyr/bluetooth/buf.h>
#include <zephyr/bluetooth/conn.h>
#include "zephyr/logging/log.h"
#include "host/conn_internal.h"
#include "host/l2cap_internal.h"
#include "avm_external.h"
#include "nvkey.h"

LOG_MODULE_DECLARE(ULL_HID);

#define BT_ULL_LE_HID_SRV_FIX_CHANNEL_CID          0x0102
#define BT_ULL_LE_HID_SRV_FIX_CHANNEL_MTU          1250

#define BT_ULL_LE_HID_SRV_TIMER_MAX                0x0A
#define BT_ULL_LE_HID_SRV_INVALID_VALUE            0xFF

#define BT_ULL_LE_HID_SRV_TIMEOUT                  1500

#define BT_ULL_HID_LOG     "[ULL][LE][HID] "

typedef uint8_t bt_ull_le_hid_srv_link_state_t;
#define BT_ULL_LE_HID_SRV_LINK_STATE_DISCONNECTED                 0x00
#define BT_ULL_LE_HID_SRV_LINK_STATE_ACL_CONNECTED                0x01
#define BT_ULL_LE_HID_SRV_LINK_STATE_CIS_CONNECTING               0x02
#define BT_ULL_LE_HID_SRV_LINK_STATE_CIS_CONNECTED                0x03
#define BT_ULL_LE_HID_SRV_LINK_STATE_WAITE_PSEUDO_ACL_CONNECTED   0x04
#define BT_ULL_LE_HID_SRV_LINK_STATE_PSEUDO_ACL_CONNECTED         0x05
#define BT_ULL_LE_HID_SRV_LINK_STATE_ULL_HID_SRV_CONNECTED        0x06
#define BT_ULL_LE_HID_SRV_LINK_STATE_DISCONNECTING                0x07

#define BT_ULL_LE_HID_SRV_STATE_NONE                              0x00
typedef uint8_t bt_ull_le_hid_srv_state_t;

typedef struct {
    bt_ull_le_hid_srv_module_t         module;
    bt_ull_callback                    callback;
} bt_ull_le_hid_srv_callback_t;

/* L2CAP signalling channel specific context */
struct bt_fixed_l2cap {
	/* The channel this context is associated with */
	struct bt_l2cap_le_chan	chan;
};
static struct bt_fixed_l2cap bt_fixed_l2cap_pool[2];

bt_ull_le_hid_srv_context_t g_bt_ull_hid_le_ctx;
static bt_ull_le_hid_srv_callback_t      g_bt_ull_le_hid_cb[BT_ULL_LE_HID_SRV_MODULE_MAX] = {0};
static uint8_t g_gp_uni_aa[BT_ULL_LE_HID_DM_UNI_AA_LEN] = {0x6D, 0xEB, 0x98, 0xE9};
static uint8_t g_kb_uni_aa[BT_ULL_LE_HID_DM_UNI_AA_LEN] = {0x6D, 0xEB, 0x98, 0xE9};
static uint8_t g_ms_uni_aa[BT_ULL_LE_HID_DM_UNI_AA_LEN] = {0x6D, 0xEB, 0x98, 0xE9};
static uint32_t g_bt_ull_le_service_connect_timer_handle = 0;
static uint32_t g_bt_ull_le_sync_context_info_timer_handle = 0;
static uint32_t g_bt_ull_le_bonding_req_timer_handle = 0;
static uint32_t g_bt_ull_le_sync_bonding_info_timer_handle = 0;

static bt_addr_le_t g_local_addr = {0};
/**************************************************************************************************
* Prototype
**************************************************************************************************/
#if defined(CONFIG_ULL_HID_LE_CENTRAL)
static int bt_ull_le_hid_srv_send_data_by_device_type(bt_ull_le_hid_srv_device_t device_type, uint8_t *packet, uint16_t packet_size);
static int bt_ull_le_hid_srv_led_control_hdl(bt_ull_le_hid_srv_control_indicater_led_t *led_control);
static int bt_ull_le_hid_srv_create_connection_req(bt_ull_le_hid_srv_connect_t *create_conn);
#endif
// static bool bt_ull_le_hid_srv_is_device_connected(bt_ull_le_hid_srv_device_t dt);
static void bt_ull_le_hid_srv_notify_event(uint8_t module, bt_ull_event_t event, void *param, uint32_t len);
static int bt_ull_le_hid_srv_conn_event_cb(bt_ull_le_hid_conn_srv_msg_t msg, void *data);
static void bt_ull_le_hid_srv_l2cap_rx_hdl(struct bt_conn *conn, struct net_buf *buf, uint16_t len) ;
static int bt_ull_le_hid_srv_disconnect_req(bt_ull_le_hid_srv_disconnect_t *disconnect);
static bt_ull_le_hid_srv_context_t * bt_ull_le_hid_srv_get_ctx(void);

/* Context related functions */
static bt_ull_le_hid_srv_context_t * bt_ull_le_hid_srv_get_ctx(void)
{
    return &g_bt_ull_hid_le_ctx;
}

bt_ull_role_t bt_ull_le_hid_srv_get_role(void)
{
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    return ctx->role;
}
static uint8_t bt_ull_le_hid_srv_get_link_idx_by_handle(uint16_t handle)
{
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    uint8_t i = 0;
    for (i =0; i < BT_ULL_LE_HID_SRV_MAX_LINK_NUM; i ++) {
        if (ctx->link[i].acl_handle == handle) {
            return i;
        }
    }
    LOG_ERR(BT_ULL_HID_LOG"not found handle, handle: %x!!", handle);
    return BT_ULL_LE_HID_SRV_INVALID_VALUE;
}

static uint8_t bt_ull_le_hid_srv_get_link_idx_by_conn(struct bt_conn *conn)
{
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    uint8_t i = 0;
    for (i =0; i < BT_ULL_LE_HID_SRV_MAX_LINK_NUM; i ++) {
        if (ctx->link[i].conn == conn) {
            return i;
        }
    }
    LOG_ERR(BT_ULL_HID_LOG"not found conn, conn: %x!!", conn);
    return BT_ULL_LE_HID_SRV_INVALID_VALUE;
}

static uint8_t bt_ull_le_hid_srv_get_link_idx_by_addr(bt_addr_le_t *addr)
{
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    uint8_t i = 0;
    for (i =0; i < BT_ULL_LE_HID_SRV_MAX_LINK_NUM; i ++) {
        if (!bt_ull_le_srv_memcmp(&ctx->link[i].peer_addr, addr, sizeof(bt_addr_le_t))) {
            return i;
        }
    }
    return BT_ULL_LE_HID_SRV_INVALID_VALUE;
}

static uint8_t bt_ull_le_hid_srv_get_empty_link(void)
{
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    uint8_t i = 0;
    for (i =0; i < BT_ULL_LE_HID_SRV_MAX_LINK_NUM; i ++) {
        if (ctx->link[i].state == BT_ULL_LE_HID_SRV_LINK_STATE_DISCONNECTED) {
            return i;
        }
    }
    return BT_ULL_LE_HID_SRV_INVALID_VALUE;
}
static uint8_t  bt_ull_le_hid_srv_get_link_idx_by_dt(uint8_t device_type)
{
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    uint8_t i = 0;
    for (i =0; i < BT_ULL_LE_HID_SRV_MAX_LINK_NUM; i ++) {
        if (ctx->link[i].device_type == device_type) {
            return i;
        }
    }
    return BT_ULL_LE_HID_SRV_INVALID_VALUE;
}

static void bt_ull_le_hid_srv_clear_link(uint8_t idx)
{
    if (idx >= BT_ULL_LE_HID_SRV_MAX_LINK_NUM) {
        return;
    }
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    bt_ull_le_srv_memset(&ctx->link[idx], 0, sizeof(bt_ull_le_hid_srv_link_info_t));
}

static void bt_ull_le_hid_srv_set_link_state(uint8_t idx, uint8_t state)
{
    if (idx >= BT_ULL_LE_HID_SRV_MAX_LINK_NUM) {
        return;
    }
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    LOG_INF(BT_ULL_HID_LOG"Set link[%d] state: %d->%d!", idx, ctx->link[idx].state, state);
    ctx->link[idx].state = state;
}

static uint8_t bt_ull_le_hid_srv_get_link_state(uint8_t idx)
{
    if (idx >= BT_ULL_LE_HID_SRV_MAX_LINK_NUM) {
        return BT_ULL_LE_HID_SRV_INVALID_VALUE;
    }
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    return ctx->link[idx].state;
}

static void bt_ull_le_hid_srv_set_link_conn(uint8_t idx, struct bt_conn *conn)
{
    if (idx >= BT_ULL_LE_HID_SRV_MAX_LINK_NUM) {
        return;
    }
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    ctx->link[idx].conn = conn;
}

static struct bt_conn *bt_ull_le_hid_srv_get_link_conn(uint8_t idx)
{
    if (idx >= BT_ULL_LE_HID_SRV_MAX_LINK_NUM) {
        return NULL;
    }
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    return ctx->link[idx].conn;
}

static void bt_ull_le_hid_srv_set_link_handle(uint8_t idx, uint16_t handle)
{
    if (idx >= BT_ULL_LE_HID_SRV_MAX_LINK_NUM) {
        return;
    }
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    ctx->link[idx].acl_handle = handle;
}

static uint16_t bt_ull_le_hid_srv_get_link_handle(uint8_t idx)
{
    if (idx >= BT_ULL_LE_HID_SRV_MAX_LINK_NUM) {
        return 0xFFFF;
    }
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    return ctx->link[idx].acl_handle;
}

static void bt_ull_le_hid_srv_set_device_type(uint8_t idx, bt_ull_le_hid_srv_device_t dt)
{
    if (idx >= BT_ULL_LE_HID_SRV_MAX_LINK_NUM) {
        return;
    }
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    ctx->link[idx].device_type = dt;
}

static void bt_ull_le_hid_srv_set_link_mode(uint8_t idx, uint8_t mode)
{
    if (idx >= BT_ULL_LE_HID_SRV_MAX_LINK_NUM) {
        return;
    }
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    ctx->link[idx].mode = mode;
}

static void bt_ull_le_hid_srv_set_rx_att_handle(uint8_t idx, uint16_t rx_att_handle)
{
    if (idx >= BT_ULL_LE_HID_SRV_MAX_LINK_NUM) {
        return;
    }
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    ctx->link[idx].att_handle_rx = rx_att_handle;
}

static void bt_ull_le_hid_srv_set_tx_att_handle(uint8_t idx, uint16_t tx_att_handle)
{
    if (idx >= BT_ULL_LE_HID_SRV_MAX_LINK_NUM) {
        return;
    }
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    ctx->link[idx].att_handle_tx = tx_att_handle;
}

static void bt_ull_le_hid_srv_set_cccd_att_handle(uint8_t idx, uint16_t cccd_att_handle)
{
    if (idx >= BT_ULL_LE_HID_SRV_MAX_LINK_NUM) {
        return;
    }
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    ctx->link[idx].att_handle_cccd = cccd_att_handle;
}

static uint8_t bt_ull_le_hid_srv_get_device_type_by_idx(uint8_t idx)
{
    if (idx >= BT_ULL_LE_HID_SRV_MAX_LINK_NUM) {
        return BT_ULL_LE_HID_SRV_DEVICE_NONE;
    }
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    return ctx->link[idx].device_type;
}

static void bt_ull_le_hid_srv_set_link_addr(uint8_t idx, const bt_addr_le_t *addr)
{
    if (idx >= BT_ULL_LE_HID_SRV_MAX_LINK_NUM || !addr) {
        return;
    }
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    bt_ull_le_srv_memcpy(&ctx->link[idx].peer_addr, addr, sizeof(bt_addr_le_t));
}

/* Connection related functions */
static void bt_ull_le_hid_srv_acl_connect_ind_hdl(struct bt_conn *conn, uint8_t err)
{
    if (!conn) {
        LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_acl_connect_ind_hdl, conn is NULL!");
        return;
    }
    if (!g_bt_ull_hid_le_ctx.initialized) {
        LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_acl_connect_ind_hdl, not initialized!!");
        return;
    }
    struct bt_conn_info info;
    bt_conn_get_info(conn, &info);
    if (0 != err || !conn) {
        LOG_ERR(BT_ULL_HID_LOG"ERR status: %d, conn: 0x%x!!", err, conn);
        return;
    }
    const bt_addr_le_t *addr = bt_conn_get_dst(conn);
    if(info.role == BT_HCI_ROLE_CENTRAL || info.role == BT_HCI_ROLE_PERIPHERAL){/* normal acl link connected */
        uint8_t idx = bt_ull_le_hid_srv_get_empty_link();
        if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx) {
            LOG_ERR(BT_ULL_HID_LOG"bt_ull_le_hid_srv_acl_connect_ind_hdl, not link resource!!");
        }
        bt_ull_le_hid_srv_set_link_handle(idx, conn->handle);
        bt_ull_le_hid_srv_set_link_conn(idx, conn);
        bt_ull_le_hid_srv_set_link_addr(idx, addr);
        bt_ull_le_hid_srv_set_link_state(idx, BT_ULL_LE_HID_SRV_LINK_STATE_ACL_CONNECTED);
        bt_ull_le_hid_srv_set_link_mode(idx, BT_ULL_LE_HID_SRV_LINK_MODE_FOTA);
        LOG_INF(BT_ULL_HID_LOG"BT_GAP_LE_CONNECT_IND, conn: 0x%x, id: %d, idx:%d, addr: %2x-%2x-%2x-%2x-%2x-%2x!", conn, conn->id, idx,\
            addr->a.val[0], addr->a.val[1], addr->a.val[2], \
            addr->a.val[3], addr->a.val[4], addr->a.val[5]);
    } else if (info.role == 0x80 || info.role == 0x81){/* pseduo link connected */
        uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_handle(conn->handle);//conn_handle for pseudo link which mapping cis link
        if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx) {
            LOG_ERR(BT_ULL_HID_LOG"pseudo_link_connected_ind_hdl, not found link!!");
            return;
        }
        bt_ull_le_hid_srv_set_link_conn(idx, conn);
        uint8_t state = bt_ull_le_hid_srv_get_link_state(idx);
        uint8_t device_type = bt_ull_le_hid_srv_get_device_type_by_idx(idx);
        LOG_INF(BT_ULL_HID_LOG"PSEUDO ACL CONNECTED, status: %d, link state: %x, dt: %d, handle: %x, id: %d, idx: %d", err, state, device_type, conn->handle, conn->id, idx);

        if (0 != err) {
            if (BT_ULL_LE_HID_SRV_LINK_STATE_WAITE_PSEUDO_ACL_CONNECTED == state) {
                bt_ull_le_hid_srv_set_link_state(idx, BT_ULL_LE_HID_SRV_LINK_STATE_CIS_CONNECTED);
            }
            return;
        }

        if (BT_ULL_LE_HID_SRV_LINK_STATE_WAITE_PSEUDO_ACL_CONNECTED != state ) {
            LOG_ERR(BT_ULL_HID_LOG"pseudo_acl_connected_ind_hdl, state error!!");
            return;
        }
        bt_ull_le_hid_srv_set_link_state(idx, BT_ULL_LE_HID_SRV_LINK_STATE_PSEUDO_ACL_CONNECTED);
        bt_ull_le_hid_srv_connected_ind_t connection_complete;
        connection_complete.status = err;
        connection_complete.conn = conn;
        connection_complete.device_type = device_type;
        bt_ull_le_srv_memcpy(&connection_complete.peer_addr, addr, sizeof(bt_addr_le_t));
        bt_driver_airoha_get_loacl_addr((bt_bd_addr_t *)&g_local_addr.a);
        bt_ull_le_hid_srv_print_addr(&g_local_addr);
        bt_ull_le_hid_dm_shift_device_front(device_type, addr);
        bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_APP, BT_ULL_EVENT_LE_HID_CONNECTED_IND, &connection_complete, sizeof(bt_ull_le_hid_srv_connected_ind_t));
        bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_AIR_SRV, BT_ULL_EVENT_LE_HID_CONNECTED_IND, &connection_complete, sizeof(bt_ull_le_hid_srv_connected_ind_t));
        bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_AUTO_SWTICHER, BT_ULL_EVENT_LE_HID_CONNECTED_IND, &connection_complete, sizeof(bt_ull_le_hid_srv_connected_ind_t));
    } else {
        LOG_ERR(BT_ULL_HID_LOG" not sopport role: %d!!", info.role);
    }
}

static void bt_ull_le_hid_srv_acl_disconnect_ind_hdl(struct bt_conn *conn, uint8_t err)
{
    if (!conn) {
        return;
    }
    struct bt_conn_info info;
    bt_conn_get_info(conn, &info);
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();

    if (!conn) {
        LOG_ERR(BT_ULL_HID_LOG"acl_disconnect_ind_hdl, no conn");
        return;
    }
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_conn(conn);
    if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx) {
        LOG_ERR(BT_ULL_HID_LOG"acl_disconnect_ind_hdl, invalid handle!!");
        return;
    }
    uint8_t dt = bt_ull_le_hid_srv_get_device_type_by_idx(idx);
    uint8_t state = bt_ull_le_hid_srv_get_link_state(idx);
    LOG_INF(BT_ULL_HID_LOG"acl_disconnect_ind_hdl, dt: %d, state: %d, role: %d, idx: %d", dt, state, ctx->role, idx);
    bt_ull_le_hid_srv_print_addr(&ctx->link[idx].peer_addr);
    if (BT_ULL_LE_HID_SRV_LINK_STATE_PSEUDO_ACL_CONNECTED <= state) {
        bt_ull_le_hid_srv_disconnected_ind_t dis;
        dis.status = 0;
        dis.device_type = dt;
        dis.conn = conn;
        dis.reason = err;
        bt_ull_le_srv_memcpy(&dis.peer_addr, &ctx->link[idx].peer_addr, sizeof(bt_addr_le_t));
        bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_APP, BT_ULL_EVENT_LE_HID_DISCONNECTED_IND, &dis, sizeof(bt_ull_le_hid_srv_disconnected_ind_t));
        bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_AIR_SRV, BT_ULL_EVENT_LE_HID_DISCONNECTED_IND, &dis, sizeof(bt_ull_le_hid_srv_disconnect_t));
        bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_AUTO_SWTICHER, BT_ULL_EVENT_LE_HID_DISCONNECTED_IND, &dis, sizeof(bt_ull_le_hid_srv_disconnect_t));
        bt_ull_le_hid_srv_clear_link(idx);
    } else {
        bt_ull_le_hid_srv_clear_link(idx);
        return;
    }
}

static struct bt_conn_cb bt_ull_le_hid_conn_callbacks = {
	.connected = bt_ull_le_hid_srv_acl_connect_ind_hdl,
	.disconnected = bt_ull_le_hid_srv_acl_disconnect_ind_hdl,
};

/*  l2cap related functions */

NET_BUF_POOL_FIXED_DEFINE(ull_le_hid_data_pool, 2, BT_ULL_LE_HID_SRV_FIX_CHANNEL_MTU, 8, NULL);

static void bt_ull_le_hid_srv_l2cap_connected(struct bt_l2cap_chan *chan)
{
	LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_l2cap_connected ch 0x%x cid 0x%04x", BT_L2CAP_LE_CHAN(chan), BT_L2CAP_LE_CHAN(chan)->rx.cid);
}

static void bt_ull_le_hid_srv_l2cap_disconnected(struct bt_l2cap_chan *chan)
{
	struct bt_l2cap_le_chan *le_chan = BT_L2CAP_LE_CHAN(chan);

	LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_l2cap_disconnected ch 0x%x cid 0x%04x", le_chan, le_chan->rx.cid);
}

static int bt_ull_le_hid_srv_l2cap_recv(struct bt_l2cap_chan *chan, struct net_buf *buf)
{
    LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_l2cap_recv, handle is 0x%x",  chan->conn->handle);
    bt_ull_le_hid_srv_l2cap_rx_hdl(chan->conn, buf, buf->len);
	return 0;
}

static int bt_ull_le_hid_l2cap_accept(struct bt_conn *conn, struct bt_l2cap_chan **chan)
{
	int i;
	static const struct bt_l2cap_chan_ops ops = {
		.connected = bt_ull_le_hid_srv_l2cap_connected,
		.disconnected = bt_ull_le_hid_srv_l2cap_disconnected,
		.recv = bt_ull_le_hid_srv_l2cap_recv,
	};

	LOG_INF(BT_ULL_HID_LOG"conn 0x%x handle %u", conn, conn->handle);

	for (i = 0; i < ARRAY_SIZE(bt_fixed_l2cap_pool); i++) {
		struct bt_fixed_l2cap *l2cap = &bt_fixed_l2cap_pool[i];

		if (l2cap->chan.chan.conn) {
			continue;
		}

		l2cap->chan.chan.ops = &ops;
		*chan = &l2cap->chan.chan;

		return 0;
	}

	LOG_ERR("No available L2CAP context for conn 0x%x", conn);

	return -ENOMEM;
}


BT_L2CAP_CHANNEL_DEFINE(ull_le_hid_fixed_chan, BT_ULL_LE_HID_SRV_FIX_CHANNEL_CID, bt_ull_le_hid_l2cap_accept, NULL);
/*  l2cap related functions end*/



void bt_ull_le_hid_srv_print_addr(const bt_addr_le_t *addr)
{
    if (!addr) {
        return;
    }
    LOG_INF(BT_ULL_HID_LOG" PRINT BT ADDR: addr_type: %d, addr: %x-%x-%x-%x-%x-%x!",
        addr->type,
        addr->a.val[0],
        addr->a.val[1],
        addr->a.val[2],
        addr->a.val[3],
        addr->a.val[4],
        addr->a.val[5]
        );
}

static void bt_ull_le_hid_srv_timer_timeout_handler(void *user_data)
{
    LOG_ERR(BT_ULL_HID_LOG"Timer Time out");
    return;
}

int bt_ull_le_hid_srv_start_timer(uint32_t handle, uint32_t timer_period, hal_gpt_callback_t callback, uint32_t data)
{
    if(HAL_GPT_STATUS_OK != hal_gpt_sw_start_timer_ms(handle, timer_period, bt_ull_le_hid_srv_timer_timeout_handler, NULL)) {
        return -EPERM;
    }

    return 0;
}

int bt_ull_le_hid_srv_stop_timer(uint32_t handle)
{
    hal_gpt_status_t t_status = hal_gpt_sw_stop_timer_ms(handle);
    return (HAL_GPT_STATUS_OK == t_status) ? 0 : -EPERM;
}

/* Reserve L2cap header and acl header space before ULL HID service User data */
static struct net_buf *bt_ull_le_hid_srv_create_pdu(void)
{
	struct net_buf *buf;
	k_timeout_t timeout = K_NO_WAIT;

	/* Use smaller timeout if returning an error since that could be
	 * caused by lack of buffers.
	 */
	buf = bt_l2cap_create_pdu_timeout(&ull_le_hid_data_pool, 0, timeout);
	if (!buf) {
        LOG_ERR(BT_ULL_HID_LOG"bt_ull_le_hid_srv_create_pdu fail!!");
		return NULL;
	}

	return buf;
}

static int bt_ull_le_hid_srv_l2cap_tx(struct bt_conn *conn, uint8_t *data, uint16_t len)
{
	struct net_buf *buf;
    uint8_t *tx_data;
	buf = bt_ull_le_hid_srv_create_pdu();
    if (buf == NULL) {
        LOG_ERR(BT_ULL_HID_LOG"bt_ull_le_hid_srv_l2cap_tx: allocate buffer fail");
        return -EPERM;
    }
    tx_data = net_buf_add(buf, len);
	memcpy(tx_data, data, len);
    struct bt_l2cap_le_chan *chan = (struct bt_l2cap_le_chan *) bt_l2cap_le_lookup_tx_cid(conn, BT_ULL_LE_HID_SRV_FIX_CHANNEL_CID);
    if (!chan) {
        LOG_ERR(BT_ULL_HID_LOG"bt_ull_le_hid_srv_l2cap_tx: No ULL HID fixed channel found or chan is NULL!");
        net_buf_unref(buf);
        return -EPERM;
    }
    /* check conn state is connected again, for error handle controller connection lost suddenly */
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_conn(conn);
    uint8_t state = bt_ull_le_hid_srv_get_link_state(idx);
    if (BT_ULL_LE_HID_SRV_LINK_STATE_ACL_CONNECTED > state) {
        LOG_ERR(BT_ULL_HID_LOG"bt_ull_le_hid_srv_l2cap_tx, error state: %d", state);
        net_buf_unref(buf);
        return -EPERM;
    }
    int err = bt_l2cap_send_pdu(chan, buf, NULL, NULL);
    if (err) {
		net_buf_unref(buf);
        LOG_ERR(BT_ULL_HID_LOG"bt_ull_le_hid_srv_l2cap_tx fail: %d", err);
		return -EPERM;
	}
    return 0;
}

static void bt_ull_le_hid_srv_notify_event(uint8_t module, bt_ull_event_t event, void *param, uint32_t len)
{
    LOG_INF(BT_ULL_HID_LOG"notify_event, module: %d, event: %x", module, event);
    if (BT_ULL_LE_HID_SRV_MODULE_MAX <= module) {
        return;
    }
    if (g_bt_ull_le_hid_cb[module].module == module && g_bt_ull_le_hid_cb[module].callback) {
        g_bt_ull_le_hid_cb[module].callback(event, param, len);
    }
}

static int bt_ull_le_hid_srv_l2cap_send_data(struct bt_conn *conn, uint8_t *packet, uint16_t packet_size)
{
    int result = -EPERM;
    uint16_t send_length = 0;
    bool need_resend = false;
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_conn(conn);

    if (!conn || BT_ULL_LE_HID_SRV_INVALID_VALUE == idx) {
        LOG_ERR(BT_ULL_HID_LOG"bt_ull_le_hid_srv_l2cap_send_data, invalid params");
        return -EPERM;
    }
    uint8_t state = bt_ull_le_hid_srv_get_link_state(idx);
    if (BT_ULL_LE_HID_SRV_LINK_STATE_ACL_CONNECTED > state) {
        LOG_ERR(BT_ULL_HID_LOG"bt_ull_le_hid_srv_l2cap_send_data, error state: %d", state);
        return -EPERM;
    }
    if (BT_ULL_LE_HID_SRV_FIX_CHANNEL_MTU < packet_size) {
        need_resend = true;
        send_length = BT_ULL_LE_HID_SRV_FIX_CHANNEL_MTU;
        result = bt_ull_le_hid_srv_l2cap_tx(conn, packet, send_length);
        if ((0 == result) && (need_resend)) {
            need_resend = false;
            result = bt_ull_le_hid_srv_l2cap_send_data(conn, (uint8_t *)(packet + send_length), (packet_size - send_length));
        }
        LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_l2cap_send_data, packet_size: %d, send size: %d, status: %d, need_resend: %d", packet_size, send_length, result, need_resend);
    } else {
        send_length = packet_size;
        result = bt_ull_le_hid_srv_l2cap_tx(conn, packet, packet_size);
    }
    LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_l2cap_send_data, status: 0x%x, handle: 0x%x, packet_len: 0x%x, send_len: 0x%x", result, conn->handle, packet_size, send_length);
    return result;

}

int bt_ull_le_hid_srv_register_callback(bt_ull_le_hid_srv_module_t module, bt_ull_callback cb)
{
    LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_register_callback, module: 0x%x, 0x%x, 0x%x", module, g_bt_ull_le_hid_cb[module].callback, cb);
    if (g_bt_ull_le_hid_cb[module].callback == NULL) {
        g_bt_ull_le_hid_cb[module].callback = cb;
        g_bt_ull_le_hid_cb[module].module = module;
        return 0;
    }
    return -EPERM;
}

int bt_ull_le_hid_srv_init(bt_ull_role_t role, bt_ull_callback cb)
{
    bt_ull_le_srv_memset(&g_bt_ull_hid_le_ctx, 0, sizeof(bt_ull_le_hid_srv_context_t));
    hal_gpt_sw_get_timer(&g_bt_ull_le_service_connect_timer_handle);
    hal_gpt_sw_get_timer(&g_bt_ull_le_sync_context_info_timer_handle);
    hal_gpt_sw_get_timer(&g_bt_ull_le_bonding_req_timer_handle);
    hal_gpt_sw_get_timer(&g_bt_ull_le_sync_bonding_info_timer_handle);
    if (!cb) {
        return -EPERM;
    }
    g_bt_ull_hid_le_ctx.initialized = true;
    g_bt_ull_hid_le_ctx.role = role;
#ifdef CONFIG_AIR_PRODUCT_TYPE_KEYBOARD
    g_bt_ull_hid_le_ctx.scenario = BT_ULL_LE_HID_SRV_APP_SCENARIO_82;
#elif CONFIG_AIR_PRODUCT_TYPE_MOUSE
    g_bt_ull_hid_le_ctx.scenario = BT_ULL_LE_HID_SRV_APP_SCENARIO_81;
#elif CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER
    g_bt_ull_hid_le_ctx.scenario = BT_ULL_LE_HID_SRV_APP_SCENARIO_83;
#endif
    g_bt_ull_hid_le_ctx.report_rate.rr_level = BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_8;
    g_bt_ull_hid_le_ctx.report_rate.phy = BT_ULL_LE_SRV_PHY_LE_4M;
    if (bt_ull_le_hid_dm_init()) {
        LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_dm_init fail", 0);
        return -EPERM;
    }
    bt_ull_le_hid_conn_srv_init(role, (void *)bt_ull_le_hid_srv_conn_event_cb);
    bt_ull_le_hid_srv_register_callback(BT_ULL_LE_HID_SRV_MODULE_APP, cb);
    bt_conn_cb_register(&bt_ull_le_hid_conn_callbacks);
    LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_init, role: %d", role);
    return 0;
}

int bt_ull_le_hid_srv_unregister_callback(bt_ull_le_hid_srv_module_t module, bt_ull_callback cb)
{
    LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_unregister_callback, module: 0x%x, 0x%x, 0x%x", module, g_bt_ull_le_hid_cb[module].callback, cb);
    for ( uint8_t i = 0; i < BT_ULL_LE_HID_SRV_MODULE_MAX; i++){
        if (g_bt_ull_le_hid_cb[i].callback == cb && g_bt_ull_le_hid_cb[i].module == module){
            g_bt_ull_le_hid_cb[i].callback = NULL;
            return 0;
        }
    }
    return -EPERM;
}

int bt_ull_le_hid_srv_deinit(bt_ull_role_t role, bt_ull_callback cb)
{
    bt_ull_le_srv_memset(&g_bt_ull_hid_le_ctx, 0, sizeof(bt_ull_le_hid_srv_context_t));
    if (!cb) {
        LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_deinit, cb is NULL!");
        return -EPERM;
    }
    bt_ull_le_hid_conn_srv_deinit();
    bt_ull_le_hid_srv_unregister_callback(BT_ULL_LE_HID_SRV_MODULE_APP, cb);
    bt_conn_cb_unregister(&bt_ull_le_hid_conn_callbacks);
    LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_deinit, role: %d", role);
    return 0;
}

int bt_ull_le_hid_srv_init_device_type(bt_ull_le_hid_srv_device_t device_type)
{
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_init_device_type, device_type: %d", device_type);
    if (device_type == BT_ULL_LE_HID_SRV_DEVICE_NONE || device_type ==  BT_ULL_LE_HID_SRV_DEVICE_HEADSET|| device_type == BT_ULL_LE_HID_SRV_DEVICE_EARBUDS) {
        return -EPERM;
    }
    ctx->device_type = device_type;
    return 0;
}

#if defined(CONFIG_ULL_HID_LE_CENTRAL)
static void bt_ull_le_hid_srv_cig_removed_ind_hdl(bt_ull_le_hid_conn_srv_msg_ind_t *ind)
{
    if (!ind ) {
        LOG_ERR(BT_ULL_HID_LOG"bt_ull_le_hid_srv_cig_removed_ind_hdl, ind is NULL!!");
        return;
    }
    LOG_INF(BT_ULL_HID_LOG"CIG REMOVED, status: %d", ind->status);
    bt_ull_le_hid_srv_cig_removed_ind_t remove_cig_ind;
    remove_cig_ind.status = ind->status;
    bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_APP, BT_ULL_EVENT_LE_HID_CIG_REMOVED, &remove_cig_ind, sizeof(bt_ull_le_hid_srv_cig_removed_ind_t));
}

static void bt_ull_le_hid_srv_cis_cancel_create_ind_hdl(bt_ull_le_hid_conn_srv_msg_ind_t *ind)
{
    if (!ind ) {
        return;
    }
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_dt(ind->cancel_create.device_type);
    if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx) {
        LOG_ERR(BT_ULL_HID_LOG"bt_ull_le_hid_srv_cis_cancel_create_ind_hdl, not found link!!");
        return;
    }
    if (ind->status < 0) {
        LOG_ERR(BT_ULL_HID_LOG"bt_ull_le_hid_srv_cis_cancel_create_ind_hdl, status error!!");
        return;
    }
    uint8_t state = bt_ull_le_hid_srv_get_link_state(idx);
    uint8_t device_type = bt_ull_le_hid_srv_get_device_type_by_idx(idx);
    LOG_INF(BT_ULL_HID_LOG"CANCEL CREATE CIS, status: %d, link state: %x, dt: %d", ind->status, state, device_type);
    if (BT_ULL_LE_HID_SRV_LINK_STATE_CIS_CONNECTING == state) {
        //bt_ull_le_hid_srv_set_link_state(idx, BT_ULL_LE_HID_SRV_LINK_STATE_DISCONNECTED);
        //bt_ull_le_hid_srv_set_device_type(idx, BT_ULL_LE_HID_SRV_DEVICE_NONE);
    }
}

static int bt_ull_le_hid_srv_scenario_changed_ind_hdl(bt_ull_le_hid_conn_srv_msg_ind_t *ind)
{
    int status = -EPERM;
    if (!ind ) {
        return status;
    }
    LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_scenario_changed_ind_hdl, status: %x, kb: %x, ms: %x", \
        ind->status, ind->scenario_changed.kb, ind->scenario_changed.ms);
    bt_ull_le_hid_srv_connect_t conn;
    conn.keyboard = ind->scenario_changed.kb;
    conn.mouse = ind->scenario_changed.ms;
    conn.gamepad = ind->scenario_changed.gp;
    status = bt_ull_le_hid_srv_create_connection_req(&conn);
    return status;
}

static int bt_ull_le_hid_srv_conn_info_ind_hdl(bt_ull_le_hid_conn_srv_msg_ind_t *ind)
{
    int status = -EPERM;

    if (!ind ) {
        return status;
    }
    bt_ull_le_hid_conn_srv_msg_conn_info_t *conn_info = &ind->conn_info;
    LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_conn_info_ind_hdl, status: %x, phy: %x, rr: %d tx_power: %x, conn_info: 0x%x", \
        ind->status, ind->conn_info.phy, g_bt_ull_hid_le_ctx.report_rate.rr_level, ind->conn_info.tx_power, conn_info);
    bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_AUTO_SWTICHER, BT_ULL_EVENT_LE_HID_CONN_QUALITY_INFO_IND, conn_info, sizeof(bt_ull_le_hid_conn_srv_msg_conn_info_t));
    /* test code*/
    // static bool flag = false;
    // if ((g_bt_ull_hid_le_ctx.report_rate.rr_level != BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_8))
    // {
    //     if (flag) {
    //         flag = false;
    //         bt_ull_le_hid_srv_report_rate_t rr_param;
    //         rr_param.rr_level = g_bt_ull_hid_le_ctx.report_rate.rr_level;
    //         rr_param.phy = BT_ULL_LE_SRV_PHY_LE_2M;
    //         bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_SET_REPORT_RATE, &rr_param, sizeof(bt_ull_le_hid_srv_report_rate_t));
    //     } else {
    //         flag = true;
    //         bt_ull_le_hid_srv_report_rate_t rr_param;
    //         rr_param.rr_level = g_bt_ull_hid_le_ctx.report_rate.rr_level;
    //         rr_param.phy = BT_ULL_LE_SRV_PHY_LE_4M;
    //         bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_SET_REPORT_RATE, &rr_param, sizeof(bt_ull_le_hid_srv_report_rate_t));
    //     }
    // }
    return status;
}
#endif

static void bt_ull_le_hid_srv_cis_connected_ind_hdl(bt_ull_le_hid_conn_srv_msg_ind_t *ind)
{
    if (!ind ) {
        LOG_ERR(BT_ULL_HID_LOG"cis_connected_ind_hdl, ind is NULL!!");
        return;
    }
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_dt(ind->cis_connected.device_type);
    if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx) {
        LOG_ERR(BT_ULL_HID_LOG"cis_connected_ind_hdl, not found link!!");
        return;
    }
    uint8_t state = bt_ull_le_hid_srv_get_link_state(idx);
    LOG_INF(BT_ULL_HID_LOG"CIS CONNECTED, status: %d, link state: %x, dt: %d", ind->status, state, ind->cis_connected.device_type);
    if (BT_ULL_LE_HID_SRV_LINK_STATE_CIS_CONNECTING != state) {
        LOG_ERR(BT_ULL_HID_LOG"cis_connected_ind_hdl, state error!!");
        return;
    }
    if (ind->status != 0) {
        LOG_ERR(BT_ULL_HID_LOG"cis_connected_ind_hdl, status error!!");
        bt_conn_exists_le(0, BT_ADDR_LE_NONE);
        bt_ull_le_hid_srv_set_link_state(idx, BT_ULL_LE_HID_SRV_LINK_STATE_DISCONNECTED);
        bt_ull_le_hid_srv_set_device_type(idx, BT_ULL_LE_HID_SRV_DEVICE_NONE);
        bt_ull_le_hid_srv_connected_ind_t connection_complete;
        connection_complete.status = ind->status;
        connection_complete.conn = NULL;
        connection_complete.device_type = ind->cis_connected.device_type;
        bt_ull_le_srv_memcpy(&connection_complete.peer_addr, &ind->cis_connected.peer_addr, sizeof(bt_addr_le_t));
        bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_APP, BT_ULL_EVENT_LE_HID_CONNECTED_IND, &connection_complete, sizeof(bt_ull_le_hid_srv_connected_ind_t));
        bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_AIR_SRV, BT_ULL_EVENT_LE_HID_CONNECTED_IND, &connection_complete, sizeof(bt_ull_le_hid_srv_connected_ind_t));
        return;
    }

    bt_ull_le_hid_srv_set_link_handle(idx, ind->cis_connected.acl_handle);
    bt_ull_le_hid_srv_set_link_addr(idx, &ind->cis_connected.peer_addr);
    bt_ull_le_hid_srv_set_link_state(idx, BT_ULL_LE_HID_SRV_LINK_STATE_CIS_CONNECTED);
    bt_ull_le_hid_srv_set_link_mode(idx, BT_ULL_LE_HID_SRV_LINK_MODE_NORMAL);
    /*waite for the pseudo le link is connected*/
    bt_ull_le_hid_srv_set_link_state(idx, BT_ULL_LE_HID_SRV_LINK_STATE_WAITE_PSEUDO_ACL_CONNECTED);
}

static void bt_ull_le_hid_srv_cis_disconnected_ind_hdl(bt_ull_le_hid_conn_srv_msg_ind_t *ind)
{
    if (!ind ) {
        return;
    }
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_handle(ind->cis_connected.acl_handle);
    if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx) {
        LOG_ERR(BT_ULL_HID_LOG"cis_disconnected_ind_hdl, not found link!!");
        return;
    }
    if (ind->status < 0) {
        LOG_ERR(BT_ULL_HID_LOG"cis_disconnected_ind_hdl, status error!!");
        return;
    }
    uint8_t state = bt_ull_le_hid_srv_get_link_state(idx);
    uint8_t device_type = bt_ull_le_hid_srv_get_device_type_by_idx(idx);
    LOG_INF(BT_ULL_HID_LOG"CIS DISCONNECTED, status: %d, link state: %x, dt: %d", ind->status, state, device_type);
}

static int bt_ull_le_hid_srv_report_rate_change_ind_hdl(bt_ull_le_hid_srv_report_rate_change_ind_t *ind)
{
    int status = -EPERM;
    if (!ind ) {
        return status;
    }
    bt_ull_le_hid_srv_report_rate_change_ind_t report_rate_change;
    report_rate_change.status = ind->status;
    report_rate_change.report_rate.rr_level = ind->report_rate.rr_level;
    report_rate_change.report_rate.phy = ind->report_rate.phy;
    LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_report_rate_change_ind_hdl, status: %x, rr: %x, phy: %x", \
        ind->status, ind->report_rate.rr_level, ind->report_rate.phy);
    bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_APP, BT_ULL_EVENT_LE_HID_REPORT_RATE_CHANGE_IND, &report_rate_change, sizeof(bt_ull_le_hid_srv_report_rate_change_ind_t));
    bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_AUTO_SWTICHER, BT_ULL_EVENT_LE_HID_REPORT_RATE_CHANGE_IND, &report_rate_change, sizeof(bt_ull_le_hid_srv_report_rate_change_ind_t));
    return 0;
}

static int bt_ull_le_hid_srv_adv_report_ind_hdl(bt_ull_le_hid_conn_srv_msg_ind_t *ind)
{
    int status = -EPERM;
    if (!ind ) {
        LOG_ERR(BT_ULL_HID_LOG"bt_ull_le_hid_srv_adv_report_ind_hdl, ind is NULL");
        return status;
    }
    bt_ull_le_hid_conn_srv_msg_adv_report_t *adv_report = (bt_ull_le_hid_conn_srv_msg_adv_report_t *)ind;
    uint16_t len = sizeof(bt_ull_le_hid_conn_srv_msg_adv_report_t) + adv_report->adv_data_len;

    LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_adv_report_ind_hdl, status: %x, len: %d, adv_len: %d", \
        ind->status, len, adv_report->adv_data_len);
    bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_APP, BT_ULL_EVENT_LE_HID_CIS_ADV_REPORT_IND, 
                                    adv_report, len);
    return 0;
}

static int bt_ull_le_hid_srv_conn_event_cb(bt_ull_le_hid_conn_srv_msg_t msg, void *data)
{
    bt_ull_le_hid_conn_srv_msg_ind_t *ind = (bt_ull_le_hid_conn_srv_msg_ind_t *)data;
    switch (msg) {
        #if defined(CONFIG_ULL_HID_LE_CENTRAL)
        case BT_ULL_LE_HID_CONN_SRV_MSG_CIG_REMOVED_IND: {
            bt_ull_le_hid_srv_cig_removed_ind_hdl(ind);
            break;
        }
        case BT_ULL_LE_HID_CONN_SRV_MSG_CIS_CANCEL_CREATE_IND: {
            bt_ull_le_hid_srv_cis_cancel_create_ind_hdl(ind);
            break;
        }
        case BT_ULL_LE_HID_CONN_SRV_MSG_SCENARIO_CHANGED_IND: {
            bt_ull_le_hid_srv_scenario_changed_ind_hdl(ind);
            break;
        }
        case BT_ULL_LE_HID_CONN_SRV_MSG_CONN_INFO_IND: {
            bt_ull_le_hid_srv_conn_info_ind_hdl(ind);
            break;
        }
        #endif
        case BT_ULL_LE_HID_CONN_SRV_MSG_CIS_CONNECTED_IND: {
            bt_ull_le_hid_srv_cis_connected_ind_hdl(ind);
            break;
        }
        case BT_ULL_LE_HID_CONN_SRV_MSG_CIS_DISCONNECTED_IND: {
            bt_ull_le_hid_srv_cis_disconnected_ind_hdl(ind);
            break;
        }
        case BT_ULL_LE_HID_CONN_SRV_MSG_REPORT_RATE_CHANGED_IND: {
            bt_ull_le_hid_srv_report_rate_change_ind_t rate_ind = {0};
            bt_ull_le_srv_memcpy(&rate_ind, ind, sizeof(bt_ull_le_hid_srv_report_rate_change_ind_t));
            bt_ull_le_hid_srv_report_rate_change_ind_hdl(&rate_ind);
            break;
        }
        case BT_ULL_LE_HID_CONN_SRV_MSG_ADV_REPORT_IND: {
            bt_ull_le_hid_srv_adv_report_ind_hdl(ind);
            break;
        }

    }
    return 0;
}

#if defined(CONFIG_ULL_HID_LE_CENTRAL)
static int bt_ull_le_hid_srv_create_connection_req(bt_ull_le_hid_srv_connect_t *create_conn)
{
    int status = -EPERM;
    if (!create_conn) {
        return -EPERM;
    }
    bt_ull_le_hid_srv_conn_params_t *kb = NULL;
    bt_ull_le_hid_srv_conn_params_t *ms = NULL;
    bt_ull_le_hid_srv_conn_params_t *gp = NULL;
    uint8_t idx_kb = BT_ULL_LE_HID_SRV_INVALID_VALUE;
    uint8_t idx_ms = BT_ULL_LE_HID_SRV_INVALID_VALUE;
    uint8_t idx_gp = BT_ULL_LE_HID_SRV_INVALID_VALUE;
    if (create_conn->keyboard) {
        idx_kb = bt_ull_le_hid_srv_get_empty_link();
        if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx_kb) {
            LOG_ERR(BT_ULL_HID_LOG"create_connection_req_hdl(KB), no link resource!!");
            return -EPERM;
        }
        bt_ull_le_hid_srv_set_link_state(idx_kb, BT_ULL_LE_HID_SRV_LINK_STATE_CIS_CONNECTING);
        bt_ull_le_hid_srv_set_device_type(idx_kb, create_conn->keyboard->device_type);
        kb = create_conn->keyboard;
        LOG_INF(BT_ULL_HID_LOG"create_connection_req_hdl(KB), count: %d", kb->list_num);
        bt_ull_le_hid_srv_print_addr((bt_addr_le_t *)&kb->peer_addr_list);
    }
    if (create_conn->mouse) {
        idx_ms = bt_ull_le_hid_srv_get_empty_link();
        if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx_ms) {
            LOG_ERR(BT_ULL_HID_LOG"create_connection_req_hdl(MS), no link resource!!");
            return -EPERM;
        }
        bt_ull_le_hid_srv_set_link_state(idx_ms, BT_ULL_LE_HID_SRV_LINK_STATE_CIS_CONNECTING);
        bt_ull_le_hid_srv_set_device_type(idx_ms, create_conn->mouse->device_type);
        ms = create_conn->mouse;
        LOG_INF(BT_ULL_HID_LOG"create_connection_req_hdl(MS), count: %d", ms->list_num);
        bt_ull_le_hid_srv_print_addr((bt_addr_le_t *)&ms->peer_addr_list);
    }
    if (create_conn->gamepad) {
        idx_gp = bt_ull_le_hid_srv_get_empty_link();
        if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx_gp) {
            LOG_ERR(BT_ULL_HID_LOG"create_connection_req_hdl(GP), no link resource!!");
            return -EPERM;
        }
        bt_ull_le_hid_srv_set_link_state(idx_gp, BT_ULL_LE_HID_SRV_LINK_STATE_CIS_CONNECTING);
        bt_ull_le_hid_srv_set_device_type(idx_gp, create_conn->gamepad->device_type);
        gp = create_conn->gamepad;
        LOG_INF(BT_ULL_HID_LOG"create_connection_req_hdl(GP), count: %d", gp->list_num);
        bt_ull_le_hid_srv_print_addr((bt_addr_le_t *)&gp->peer_addr_list);
    }
    status = bt_ull_le_hid_conn_srv_create_air_cis(kb, ms, gp);
    if (status < 0 && (EINPROGRESS) != status) {
        if (BT_ULL_LE_HID_SRV_INVALID_VALUE != idx_gp) {
            bt_ull_le_hid_srv_set_link_state(idx_gp, BT_ULL_LE_HID_SRV_LINK_STATE_DISCONNECTED);
            bt_ull_le_hid_srv_set_device_type(idx_gp, BT_ULL_LE_HID_SRV_DEVICE_NONE);
        }
        if (BT_ULL_LE_HID_SRV_INVALID_VALUE != idx_kb) {
            bt_ull_le_hid_srv_set_link_state(idx_kb, BT_ULL_LE_HID_SRV_LINK_STATE_DISCONNECTED);
            bt_ull_le_hid_srv_set_device_type(idx_kb, BT_ULL_LE_HID_SRV_DEVICE_NONE);
        }
        if (BT_ULL_LE_HID_SRV_INVALID_VALUE != idx_ms) {
            bt_ull_le_hid_srv_set_link_state(idx_ms, BT_ULL_LE_HID_SRV_LINK_STATE_DISCONNECTED);
            bt_ull_le_hid_srv_set_device_type(idx_ms, BT_ULL_LE_HID_SRV_DEVICE_NONE);
        }
        LOG_ERR(BT_ULL_HID_LOG"create_connection_req_hdl fail, status: %d!!", status);
    }
    return status;
}

static int bt_ull_le_hid_srv_start_bonding_req(bt_ull_le_hid_srv_bond_t *bonding)
{
    int status = -EPERM;
    if (!bonding) {
        return status;
    }
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_conn(bonding->conn);
    if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx) {
        LOG_ERR(BT_ULL_HID_LOG"start_bonding_req_hdl, no link resource!!");
        return status;
    }
    uint8_t state = bt_ull_le_hid_srv_get_link_state(idx);
    uint8_t device_type = bt_ull_le_hid_srv_get_device_type_by_idx(idx);
    LOG_INF(BT_ULL_HID_LOG"SEND BONDING REQ [SERVER], link state: %x, dt: %d", state, device_type);
    if (BT_ULL_LE_HID_SRV_LINK_STATE_ACL_CONNECTED != state) {
        return status;
    }
    uint8_t pairing_req = BT_ULL_LE_HID_MSG_BONDING_REQ;
    status = bt_ull_le_hid_srv_l2cap_send_data(bonding->conn, &pairing_req, sizeof(bt_ull_le_hid_srv_msg_t));
    if (0 == status) {
        bt_ull_le_hid_srv_start_timer(g_bt_ull_le_bonding_req_timer_handle, BT_ULL_LE_HID_SRV_TIMEOUT, bt_ull_le_hid_srv_timer_timeout_handler, 0);
    } else {
        LOG_ERR(BT_ULL_HID_LOG"SEND BONDING REQ FAIL[SERVER]!!");
    }
    return status;
}

static int bt_ull_le_hid_srv_connect_service_req(bt_ull_le_hid_srv_connect_service_t *req)
{
    int status = -EPERM;
    if (!req) {
        return status;
    }
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_conn(req->conn);
    if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx) {
        LOG_ERR(BT_ULL_HID_LOG"srv_connect_service_req, no link resource!!");
        return status;
    }
    uint8_t state = bt_ull_le_hid_srv_get_link_state(idx);
    uint8_t device_type = bt_ull_le_hid_srv_get_device_type_by_idx(idx);
    if (BT_ULL_LE_HID_SRV_LINK_STATE_PSEUDO_ACL_CONNECTED != state) {
        return status;
    }
    LOG_INF(BT_ULL_HID_LOG"SEND CONNECT SERVICE REQ [SERVER], link state: %x, dt: %d", state, device_type);
    bt_ull_le_hid_srv_msg_t connect_srv_req = BT_ULL_LE_HID_MSG_SERVICE_CONNECT_REQ;
    status = bt_ull_le_hid_srv_l2cap_send_data(req->conn, &connect_srv_req, sizeof(bt_ull_le_hid_srv_msg_t));
    if (0 == status) {
        bt_ull_le_hid_srv_start_timer(g_bt_ull_le_service_connect_timer_handle, BT_ULL_LE_HID_SRV_TIMEOUT, bt_ull_le_hid_srv_timer_timeout_handler, 0);
    } else {
        LOG_ERR(BT_ULL_HID_LOG"SEND CONNECT SERVICE REQ [SERVER] FAIL");
    }
    return status;
}

static int bt_ull_le_hid_srv_switch_link_mode_req(bt_ull_le_hid_srv_switch_link_mode_t *req)
{
    int status = -EPERM;
    if (!req) {
        return -EPERM;
    }
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_conn(req->conn);
    uint8_t state = bt_ull_le_hid_srv_get_link_state(idx);
    LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_switch_link_mode_req, idx: %d, state: %d", idx, state);
    if (state < BT_ULL_LE_HID_SRV_LINK_STATE_ULL_HID_SRV_CONNECTED) {
        return -EPERM;
    }
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    if (BT_ULL_ROLE_SERVER == ctx->role) {
        bt_ull_le_hid_srv_switch_link_mode_ind_t switch_link;
        switch_link.conn = req->conn;
        switch_link.link_mode = req->link_mode;
        bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_APP, BT_ULL_EVENT_LE_HID_SWITCH_LINK_MODE_IND, &switch_link, sizeof(bt_ull_le_hid_srv_switch_link_mode_ind_t));
        return 0;
    }
    uint16_t len = sizeof(bt_ull_le_hid_srv_msg_t) + sizeof(bt_ull_le_hid_srv_change_link_req_t);
    uint8_t *data = (uint8_t *)bt_ull_le_srv_memory_alloc(len);
    __ASSERT(data != NULL, "out of memory");
    
    data[0] = BT_ULL_LE_HID_MSG_SWITCH_LINK_MODE;
    bt_ull_le_hid_srv_change_link_req_t *switch_link = (bt_ull_le_hid_srv_change_link_req_t *)(data + sizeof(bt_ull_le_hid_srv_msg_t));
    switch_link->mode = req->link_mode;
    status = bt_ull_le_hid_srv_l2cap_send_data(req->conn, data, len);
    if (0 == status) {
        
    } else {
        LOG_ERR(BT_ULL_HID_LOG"Switch link mode fail!!");
    }

    bt_ull_le_srv_memory_free(data);
    return status;
}

static int bt_ull_le_hid_srv_set_scenario(bt_ull_le_hid_srv_app_scenario_t scenario)
{
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    LOG_INF("[ULL][LE] bt_ull_le_hid_srv_set_scenario, set scenario :%d, curr scenario: %d", scenario, ctx->scenario);
    if (BT_ULL_ROLE_CLIENT == ctx->role) {
        return -EPERM;
    }
    if (BT_ULL_LE_HID_SRV_APP_SCENARIO_NONE == scenario) {
        return -EPERM;
    }
    ctx->scenario = scenario;
    return bt_ull_le_hid_conn_srv_change_scenario(scenario);
}

static int bt_ull_le_hid_srv_set_idle_time(bt_ull_le_hid_srv_idle_time_t idle_time)
{
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    LOG_INF("[ULL][LE] bt_ull_le_hid_srv_set_idle_time, set idle_time :%d, curr idle_time: %d", idle_time, ctx->idle_time);
    if (BT_ULL_ROLE_CLIENT == ctx->role) {
        return -EPERM;
    }
    if (idle_time == ctx->idle_time) {
        return 0;
    }
    ctx->idle_time = idle_time;
    return bt_ull_le_hid_conn_srv_set_idle_time(idle_time);
}

static int bt_ull_le_hid_srv_remove_cig(void)
{
    return bt_ull_le_hid_conn_srv_remove_air_cig();
}

int bt_ull_le_hid_srv_cancel_connect_hdl(bt_ull_le_hid_srv_cancel_connect_t *cancel)
{
    if (!cancel) {
        return -EPERM;
    }
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_dt(cancel->device_type);
    if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx) {
        LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_cancel_connect_hdl, not found dt: %x", cancel->device_type);
        return -EPERM;
    }
    uint8_t state = bt_ull_le_hid_srv_get_link_state(idx);
    LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_cancel_connect_hdl, dt: %x, state: %d", cancel->device_type, state);
    if (BT_ULL_LE_HID_SRV_LINK_STATE_CIS_CONNECTING != state) {
        LOG_ERR(BT_ULL_HID_LOG"bt_ull_le_hid_srv_cancel_connect_hdl, idx %d, state %d error!", idx, state);
        return -EPERM;
    }
    return bt_ull_le_hid_conn_srv_cancel_create_air_cis(cancel->device_type);
}

static int bt_ull_le_hid_srv_set_output_report(bt_ull_le_hid_srv_set_output_report_t *output_report)
{
    int status = -EPERM;
    if (!output_report) {
        return -EPERM;
    }
    LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_set_output_report , dt: %d, size: %d", output_report->device_type, output_report->size);
    uint16_t len = sizeof(bt_ull_le_hid_srv_msg_t) + sizeof(uint16_t) + output_report->size;
    uint8_t *data = (uint8_t *)bt_ull_le_srv_memory_alloc(len);
    __ASSERT(data != NULL, "out of memory");
    
    data[0] = BT_ULL_LE_HID_MSG_OUT_PUT_DATA;
    bt_ull_le_srv_memcpy(&data[1], &output_report->size, sizeof(uint16_t));
    bt_ull_le_srv_memcpy(&data[3], output_report->data, output_report->size);
    status = bt_ull_le_hid_srv_send_data_by_device_type(output_report->device_type, data, len);
    if (0 == status) {
        
    } else {
        LOG_ERR(BT_ULL_HID_LOG"Send Output data fail!!");
    }

    bt_ull_le_srv_memory_free(data);
    return status;
}
#endif

static int bt_ull_le_hid_srv_disconnect_req(bt_ull_le_hid_srv_disconnect_t *disconnect)
{
    int status = -EPERM;
    if (!disconnect) {
        return status;
    }
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_conn(disconnect->conn);
    if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx) {
        LOG_ERR(BT_ULL_HID_LOG"disconnect_req_hdl, no link resource!!");
        return status;
    }
    uint16_t handle = bt_ull_le_hid_srv_get_link_handle(idx);
    uint8_t state = bt_ull_le_hid_srv_get_link_state(idx);
    uint8_t device_type = bt_ull_le_hid_srv_get_device_type_by_idx(idx);
    LOG_INF(BT_ULL_HID_LOG"DISCONNECT CIS, link state: %x, dt: %d", state, device_type);

    if (BT_ULL_LE_HID_SRV_LINK_STATE_CIS_CONNECTED > state) {
        return status;
    }
    if (BT_ULL_LE_HID_SRV_LINK_STATE_DISCONNECTING == state) {
        return 0;
    }
    bt_ull_le_hid_srv_set_link_state(idx, BT_ULL_LE_HID_SRV_LINK_STATE_DISCONNECTING);
    status = bt_ull_le_hid_conn_srv_disconnect_air_cis(handle, disconnect->reason);
    if (status < 0 && (EINPROGRESS != status)) {
        bt_ull_le_hid_srv_set_link_state(idx, state);
        LOG_ERR(BT_ULL_HID_LOG"disconnect_req_hdl, status error!! status: %x", status);
    }
    return status;
}

#if defined (CONFIG_ULL_HID_LE_PERIPHERAL)
static int bt_ull_le_hid_srv_create_sync_req(bt_ull_le_hid_srv_create_sync_t *req)
{
    int status;
    if (!req) {
        return -EPERM;
    }
    LOG_INF(BT_ULL_HID_LOG"create_sync_req, dt: %d, addr : %2x-%2x-%2x-%2x-%2x-%2x", req->device_type, \
        req->peer_addr.a.val[0], req->peer_addr.a.val[1], req->peer_addr.a.val[2], req->peer_addr.a.val[3], req->peer_addr.a.val[4], req->peer_addr.a.val[5]);
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_addr(&req->peer_addr);
    if (BT_ULL_LE_HID_SRV_INVALID_VALUE != idx) {
        uint8_t state = bt_ull_le_hid_srv_get_link_state(idx);
        LOG_ERR(BT_ULL_HID_LOG"create_sync_req(HID), state: %d", state);
        if (BT_ULL_LE_HID_SRV_LINK_STATE_ACL_CONNECTED < state) {
            return 0;
        }
    } else {
        idx = bt_ull_le_hid_srv_get_empty_link();
        if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx) {
            LOG_ERR(BT_ULL_HID_LOG"create_sync_req(HID), no link resource!!");
            return -EPERM;
        }
    }

    bt_ull_le_hid_srv_set_link_state(idx, BT_ULL_LE_HID_SRV_LINK_STATE_CIS_CONNECTING);
    bt_ull_le_hid_srv_set_device_type(idx, req->device_type);

    status = bt_ull_le_hid_conn_srv_sync_air_cis(req->device_type, &req->peer_addr);
    if (status < 0) {
        bt_ull_le_hid_srv_set_link_state(idx, BT_ULL_LE_HID_SRV_LINK_STATE_DISCONNECTED);
        bt_ull_le_hid_srv_set_device_type(idx, BT_ULL_LE_HID_SRV_DEVICE_NONE);

    }
    return status;
}

int bt_ull_le_hid_srv_cancel_create_sync_hdl(bt_ull_le_hid_srv_cancel_create_sync_t *cancel)
{
    if (!cancel) {
        return -EPERM;
    }
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_dt(cancel->device_type);
    if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx) {
        LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_cancel_create_sync_hdl, not found dt: %x", cancel->device_type);
        return -EPERM;
    }
    uint8_t state = bt_ull_le_hid_srv_get_link_state(idx);
            LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_cancel_create_sync_hdl, dt: %x, state: %d", cancel->device_type, state);
    if (BT_ULL_LE_HID_SRV_LINK_STATE_CIS_CONNECTING != state) {
        return -EPERM;
    }
    return bt_ull_le_hid_conn_srv_cancel_sync_air_cis(cancel->device_type);
}
#endif

static void bt_ull_le_hid_srv_l2cap_rx_sync_context_info_hdl(struct bt_conn *conn, struct net_buf *buf)
{
    int status;
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_conn(conn);
    bt_ull_le_hid_srv_context_info_req_t *ctx_info = (bt_ull_le_hid_srv_context_info_req_t *)(buf->data);
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();

    if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx || !ctx_info) {
        LOG_ERR(BT_ULL_HID_LOG"l2cap_rx_sync_context_info_hdl, no link resource!!");
        return;
    }
    bt_ull_role_t role = bt_ull_le_hid_srv_get_role();
    if (BT_ULL_ROLE_CLIENT != role) {
        LOG_ERR(BT_ULL_HID_LOG"l2cap_rx_sync_context_info_hdl, error role!!");
        return;
    }

    /*client sync codec rsp to server*/
    uint16_t len = sizeof(bt_ull_le_hid_srv_msg_t) + sizeof(bt_ull_le_hid_srv_rsp_t);
    uint8_t *data = (uint8_t *)bt_ull_le_srv_memory_alloc(len);
    __ASSERT(data != NULL, "out of memory");
    data[0] = BT_ULL_LE_HID_MSG_RESPONSE;
    bt_ull_le_hid_srv_rsp_t *response = (bt_ull_le_hid_srv_rsp_t *)(data + sizeof(bt_ull_le_hid_srv_msg_t));
    response->cmd_id = BT_ULL_LE_HID_MSG_SYNC_CONTEXT_INFO;
    response->status = BT_ULL_LE_HID_SRV_RSP_STATUS_SUCCESS;
    bt_ull_le_srv_memcpy(&response->param.mouse_context_info_rsp.local_addr, &g_local_addr, sizeof(bt_addr_le_t));
    bt_ull_le_hid_srv_print_addr(&response->param.mouse_context_info_rsp.local_addr);
#if defined (CONFIG_ULL_HID_LE_ADDRESS_CHECK)
    bool is_bonded = bt_ull_le_hid_srv_is_bonded_device(ctx->device_type, &ctx_info->info.mouse_info.local_addr);
    bool is_default_pairing = bt_ull_le_hid_dm_is_default_addr(ctx->device_type, &ctx->link[idx].peer_addr);
    LOG_INF(BT_ULL_HID_LOG"is_bonded: %d, is_default_pairing: %d !!", is_bonded, is_default_pairing);
    if (!is_bonded && !is_default_pairing){
        /* Disconnect link */
        bt_ull_le_hid_srv_disconnect_t disconnect;
        disconnect.conn = conn;
        disconnect.reason = BT_HCI_ERR_PAIRING_NOT_ALLOWED;
        bt_ull_le_hid_srv_disconnect_req(&disconnect);
        bt_ull_le_srv_memory_free(data);
        return;
    }
#endif
    status = bt_ull_le_hid_srv_l2cap_send_data(conn, data, len);
    bt_ull_le_srv_memory_free(data);
    if (0 == status) {
        LOG_INF(BT_ULL_HID_LOG"SERVICE CONNECTED [CLIENT]!!");
        bt_ull_le_hid_srv_set_link_state(idx, BT_ULL_LE_HID_SRV_LINK_STATE_ULL_HID_SRV_CONNECTED);
        bt_ull_le_hid_srv_service_connected_ind_t srv_connect_complete;
        srv_connect_complete.conn = conn;
        srv_connect_complete.status = status;
        bt_ull_le_srv_memcpy(&srv_connect_complete.peer_addr, &ctx->link[idx].peer_addr, sizeof(bt_addr_le_t));
        bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_APP, BT_ULL_EVENT_LE_HID_SERVICE_CONNECTED_IND, &srv_connect_complete, sizeof(bt_ull_le_hid_srv_service_connected_ind_t));
        bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_AIR_SRV, BT_ULL_EVENT_LE_HID_SERVICE_CONNECTED_IND, &srv_connect_complete, sizeof(bt_ull_le_hid_srv_service_connected_ind_t));
    } else {
        LOG_ERR(BT_ULL_HID_LOG"SEND SYNC CONTEXT INFO RESPONSE FAIL [CLIENT]!!");
    }
}

static void bt_ull_le_hid_srv_l2cap_rx_sync_bonding_info_hdl(struct bt_conn *conn, struct net_buf *buf)
{
    int status;
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_conn(conn);
    bt_ull_le_hid_srv_bonding_info_t *bonding_info = (bt_ull_le_hid_srv_bonding_info_t *)(buf->data);
    if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx || !bonding_info) {
        LOG_ERR(BT_ULL_HID_LOG"l2cap_rx_sync_bonding_info_hdl, no link resource!!");
        return;
    }
    bt_ull_role_t role = bt_ull_le_hid_srv_get_role();
    if (BT_ULL_ROLE_CLIENT != role) {
        LOG_ERR(BT_ULL_HID_LOG"l2cap_rx_sync_bonding_info_hdl, error role!!");
        return;
    }
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    bt_ull_le_hid_dm_device_info_t device_info = {0};
    device_info.device_type = ctx->device_type;
    device_info.scenario = bonding_info->scenario;
    device_info.report_rate = bonding_info->report_rate;
    device_info.phy = bonding_info->phy;
    bt_ull_le_srv_memcpy(&device_info.addr, &ctx->link[idx].peer_addr, sizeof(bt_addr_le_t));
    bt_ull_le_srv_memcpy(&device_info.uni_aa, &bonding_info->uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN);
    bt_ull_le_srv_memcpy(&device_info.ltk, &bonding_info->ltk, BT_ULL_LE_HID_DM_LTK_LEN);
    bt_ull_le_srv_memcpy(&device_info.skd, &bonding_info->skd, BT_ULL_LE_HID_DM_SKD_LEN);
    bt_ull_le_srv_memcpy(&device_info.iv, &bonding_info->iv, BT_ULL_LE_HID_DM_IV_LEN);
    LOG_INF(BT_ULL_HID_LOG"RECEIVE SYNC BONDING INFO [CLIENT], LTK: %x:%x...%x, UNI AA: %x:%x:%x:%x", bonding_info->ltk[0], bonding_info->ltk[1], bonding_info->ltk[15], \
        bonding_info->uni_aa[0], bonding_info->uni_aa[1], bonding_info->uni_aa[2], bonding_info->uni_aa[3]);
    status = bt_ull_le_hid_dm_write_device_info(&device_info);
    if (status < 0) {
        LOG_ERR(BT_ULL_HID_LOG"l2cap_rx_sync_bonding_info_hdl, save device info fail!!");
    }
    
    uint16_t len = sizeof(bt_ull_le_hid_srv_msg_t) + sizeof(bt_ull_le_hid_srv_rsp_t);
    uint8_t *data = (uint8_t *)bt_ull_le_srv_memory_alloc(len);
    if (!data) {
        return;
    }
    data[0] = BT_ULL_LE_HID_MSG_RESPONSE;
    bt_ull_le_hid_srv_rsp_t *response = (bt_ull_le_hid_srv_rsp_t *)(data + sizeof(bt_ull_le_hid_srv_msg_t));
    response->cmd_id = BT_ULL_LE_HID_MSG_SYNC_BONDING_INFO;
    response->status = (status == 0) ? BT_ULL_LE_HID_SRV_RSP_STATUS_SUCCESS : BT_ULL_LE_HID_SRV_RSP_STATUS_FAIL;

    status = bt_ull_le_hid_srv_l2cap_send_data(conn, data, len);
    bt_ull_le_srv_memory_free(data);
    if (0 == status) {
        LOG_INF(BT_ULL_HID_LOG"BONDING COMPLETE!! [CLIENT], rr: %d, phy:%d", bonding_info->report_rate, bonding_info->phy);
        bt_ull_le_hid_srv_bonding_complete_ind_t bonding_complete;
        bonding_complete.conn = conn;
        bonding_complete.status = status;
        bt_ull_le_srv_memcpy(&bonding_complete.peer_addr, &ctx->link[idx].peer_addr, sizeof(bt_addr_le_t));
        bonding_complete.report_rate.rr_level = bonding_info->report_rate;
        bonding_complete.report_rate.phy = bonding_info->phy;
        bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_APP, BT_ULL_EVENT_LE_HID_BONDING_COMPLETE_IND, &bonding_complete, sizeof(bt_ull_le_hid_srv_bonding_complete_ind_t));
    } else {
        LOG_ERR(BT_ULL_HID_LOG"SEND SYNC BONDING INFO RESPONSE FAIL [CLIENT]!!");
    }
}

static void bt_ull_le_hid_srv_l2cap_rx_bonding_req_hdl(struct bt_conn *conn)
{
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_conn(conn);
    if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx) {
        LOG_ERR(BT_ULL_HID_LOG"l2cap_rx_bonding_req_hdl, no link resource!!");
        return;
    }
    bt_ull_role_t role = bt_ull_le_hid_srv_get_role();
    if (BT_ULL_ROLE_CLIENT != role) {
        LOG_ERR(BT_ULL_HID_LOG"l2cap_rx_bonding_req_hdl, error role!!");
        return;
    }
    LOG_INF(BT_ULL_HID_LOG"RECEIVE BONDING REQ [CLIENT]!!");
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    uint16_t len = sizeof(bt_ull_le_hid_srv_msg_t) + sizeof(bt_ull_le_hid_srv_rsp_t);
    uint8_t *data = (uint8_t *)bt_ull_le_srv_memory_alloc(len);
    __ASSERT(data != NULL, "out of memory");
    data[0] = BT_ULL_LE_HID_MSG_RESPONSE;
    bt_ull_le_hid_srv_rsp_t *response = (bt_ull_le_hid_srv_rsp_t *)(data + sizeof(bt_ull_le_hid_srv_msg_t));
    response->cmd_id = BT_ULL_LE_HID_MSG_BONDING_REQ;
    response->status = BT_ULL_LE_HID_SRV_RSP_STATUS_SUCCESS;
    response->param.connect_rsp.device_type = ctx->device_type;
    LOG_INF(BT_ULL_HID_LOG"SEND BONDING REQ RESPONSE [CLIENT]!!");
    int status = bt_ull_le_hid_srv_l2cap_send_data(conn, data, len);
    if (status < 0) {
        LOG_ERR(BT_ULL_HID_LOG"SEND BONDING REQ RESPONSE FAIL [CLIENT]!!");
    }
    bt_ull_le_srv_memory_free(data);
}

static void bt_ull_le_hid_srv_l2cap_rx_response_hdl(struct bt_conn *conn, struct net_buf *buf)
{
    bt_ull_le_hid_srv_rsp_t *rsp = (bt_ull_le_hid_srv_rsp_t *)buf->data;
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_conn(conn);
    if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx || !buf) {
        LOG_ERR(BT_ULL_HID_LOG"l2cap_rx_response_hdl, no link resource!!");
        return;
    }
    bt_ull_role_t role = bt_ull_le_hid_srv_get_role();
    if (BT_ULL_ROLE_SERVER != role) {
        LOG_ERR(BT_ULL_HID_LOG"l2cap_rx_response_hdl, error role!!");
        return;
    }
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    LOG_INF(BT_ULL_HID_LOG"rx_response_hdl, handle: %x, cmd id: %x, status: %x", conn->handle, rsp->cmd_id, rsp->status);
    switch (rsp->cmd_id) {
        case BT_ULL_LE_HID_MSG_SERVICE_CONNECT_REQ: {
            bt_ull_le_hid_srv_stop_timer(g_bt_ull_le_service_connect_timer_handle);
            LOG_INF(BT_ULL_HID_LOG"RECEIVE CONNECT RSP [SERVER]!![dt: %d]!!", rsp->param.connect_rsp.device_type);
            if (BT_ULL_LE_HID_SRV_RSP_STATUS_SUCCESS == rsp->status) {
                bt_ull_le_hid_srv_set_device_type(idx, rsp->param.connect_rsp.device_type);
                uint16_t len = sizeof(bt_ull_le_hid_srv_msg_t) + sizeof(bt_ull_le_hid_srv_context_info_req_t);
                uint8_t *data = (uint8_t *)bt_ull_le_srv_memory_alloc(len);
                __ASSERT(data != NULL, "out of memory");
                data[0] = BT_ULL_LE_HID_MSG_SYNC_CONTEXT_INFO;
                bt_ull_le_hid_srv_context_info_req_t *sync_data = (bt_ull_le_hid_srv_context_info_req_t *)(data + sizeof(bt_ull_le_hid_srv_msg_t));
                bt_ull_le_srv_memcpy(&sync_data->info.mouse_info.local_addr, &g_local_addr, sizeof(bt_addr_le_t));
                LOG_INF(BT_ULL_HID_LOG"SEND LOCAL ADDR [SERVER]!!: %02X:%02X:%02X:%02X:%02X:%02X", g_local_addr.a.val[5], g_local_addr.a.val[4], 
                    g_local_addr.a.val[3], g_local_addr.a.val[2], g_local_addr.a.val[1], g_local_addr.a.val[0]);
                int status = bt_ull_le_hid_srv_l2cap_send_data(conn, data, len);
                if (0 == status) {
                    bt_ull_le_hid_srv_start_timer(g_bt_ull_le_sync_context_info_timer_handle, BT_ULL_LE_HID_SRV_TIMEOUT, bt_ull_le_hid_srv_timer_timeout_handler, 0);
                }
                LOG_INF(BT_ULL_HID_LOG"SEND SYNC CONTEXT INFO [SERVER]!! status: %x", status);
                bt_ull_le_srv_memory_free(data);
            } else {
                LOG_ERR(BT_ULL_HID_LOG"l2cap_rx_response_hdl, Connect srv fail!!");
                bt_ull_le_hid_srv_service_connected_ind_t srv_complete;
                srv_complete.conn = conn;
                srv_complete.status = -EPERM;
                bt_ull_le_srv_memcpy(&srv_complete.peer_addr, &ctx->link[idx].peer_addr, sizeof(bt_addr_le_t));
                bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_APP, BT_ULL_EVENT_LE_HID_SERVICE_CONNECTED_IND, &srv_complete, sizeof(bt_ull_le_hid_srv_service_connected_ind_t));
                bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_AIR_SRV, BT_ULL_EVENT_LE_HID_SERVICE_CONNECTED_IND, &srv_complete, sizeof(bt_ull_le_hid_srv_service_connected_ind_t));
            }
            break;
        }
        case BT_ULL_LE_HID_MSG_SYNC_CONTEXT_INFO: {
            bt_ull_le_hid_srv_stop_timer(g_bt_ull_le_sync_context_info_timer_handle);
            LOG_INF(BT_ULL_HID_LOG"RECEIVE SYNC CONTEXT INFO RSP [SERVER]!!");
            if (BT_ULL_LE_HID_SRV_RSP_STATUS_SUCCESS == rsp->status) {
                uint8_t device_type = bt_ull_le_hid_srv_get_device_type_by_idx(idx);
                if (BT_ULL_LE_HID_SRV_DEVICE_HEADSET == device_type || BT_ULL_LE_HID_SRV_DEVICE_EARBUDS == device_type) {
                    LOG_ERR(BT_ULL_HID_LOG"Device Type error!,  Not support HS && EB!!");
                } else if (BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD == device_type) {
                    bt_ull_le_hid_srv_set_cccd_att_handle(idx, rsp->param.keboard_context_info_rsp.att_handle_cccd);
                    bt_ull_le_hid_srv_set_rx_att_handle(idx, rsp->param.keboard_context_info_rsp.att_handle_rx);
                    bt_ull_le_hid_srv_set_tx_att_handle(idx, rsp->param.keboard_context_info_rsp.att_handle_tx);
                    bt_ull_le_hid_srv_set_link_state(idx, BT_ULL_LE_HID_SRV_LINK_STATE_ULL_HID_SRV_CONNECTED);
                } else if (BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD == device_type) {
                    bt_ull_le_hid_srv_set_cccd_att_handle(idx, rsp->param.gamepad_context_info_rsp.att_handle_cccd);
                    bt_ull_le_hid_srv_set_rx_att_handle(idx, rsp->param.gamepad_context_info_rsp.att_handle_rx);
                    bt_ull_le_hid_srv_set_tx_att_handle(idx, rsp->param.gamepad_context_info_rsp.att_handle_tx);
                    bt_ull_le_hid_srv_set_link_state(idx, BT_ULL_LE_HID_SRV_LINK_STATE_ULL_HID_SRV_CONNECTED);
                } else if (BT_ULL_LE_HID_SRV_DEVICE_MOUSE == device_type) {
                    bt_ull_le_hid_srv_set_cccd_att_handle(idx, rsp->param.mouse_context_info_rsp.att_handle_cccd);
                    bt_ull_le_hid_srv_set_rx_att_handle(idx, rsp->param.mouse_context_info_rsp.att_handle_rx);
                    bt_ull_le_hid_srv_set_tx_att_handle(idx, rsp->param.mouse_context_info_rsp.att_handle_tx);
#if defined (CONFIG_ULL_HID_LE_ADDRESS_CHECK)
                    bool is_bonded = bt_ull_le_hid_srv_is_bonded_device(device_type, &rsp->param.mouse_context_info_rsp.local_addr);
                    bool is_default_pairing = bt_ull_le_hid_dm_is_default_addr(device_type, &ctx->link[idx].peer_addr);
                    LOG_INF(BT_ULL_HID_LOG"is_bonded: %d, is_default_pairing: %d !!", is_bonded, is_default_pairing);
                    if (!is_bonded && !is_default_pairing){
                        /* Disconnect link */
                        bt_ull_le_hid_srv_disconnect_t disconnect;
                        disconnect.conn = conn;
                        disconnect.reason = BT_HCI_ERR_PAIRING_NOT_ALLOWED;
                        bt_ull_le_hid_srv_disconnect_req(&disconnect);
                        return;
                    }
#endif
                } else {
                    __ASSERT_NO_MSG(0);
                }

                LOG_INF(BT_ULL_HID_LOG"SERVICE CONNECTED [SERVER][dt: %d]!!", device_type);
            }
            bt_ull_le_hid_srv_service_connected_ind_t srv_conn_cmpl;
            srv_conn_cmpl.conn = conn;
            bt_ull_le_srv_memcpy(&srv_conn_cmpl.peer_addr, &ctx->link[idx].peer_addr, sizeof(bt_addr_le_t));
            srv_conn_cmpl.status = (BT_ULL_LE_HID_SRV_RSP_STATUS_SUCCESS == rsp->status) ? 0 : -EPERM;
            bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_APP, BT_ULL_EVENT_LE_HID_SERVICE_CONNECTED_IND, &srv_conn_cmpl, sizeof(bt_ull_le_hid_srv_service_connected_ind_t));
            bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_AIR_SRV, BT_ULL_EVENT_LE_HID_SERVICE_CONNECTED_IND, &srv_conn_cmpl, sizeof(bt_ull_le_hid_srv_service_connected_ind_t));
            break;
        }
        case BT_ULL_LE_HID_MSG_BONDING_REQ: {
            bt_ull_le_hid_srv_stop_timer(g_bt_ull_le_bonding_req_timer_handle);
            LOG_INF(BT_ULL_HID_LOG"RECEIVE BONDING RSP [SERVER]!![dt: %d]!!", rsp->param.bonding_rsp.device_type);
            if (BT_ULL_LE_HID_SRV_RSP_STATUS_SUCCESS == rsp->status) {
                bt_ull_le_hid_srv_set_device_type(idx, rsp->param.bonding_rsp.device_type);
                uint16_t len = sizeof(bt_ull_le_hid_srv_msg_t) + sizeof(bt_ull_le_hid_srv_bonding_info_t);
                uint8_t *data = (uint8_t *)bt_ull_le_srv_memory_alloc(len);
                uint8_t *uni_aa = bt_ull_le_hid_dm_generate_uni_aa();
                __ASSERT(data != NULL && uni_aa != NULL, "out of memory");
                data[0] = BT_ULL_LE_HID_MSG_SYNC_BONDING_INFO;
                bt_ull_le_hid_srv_bonding_info_t *bonding_info = (bt_ull_le_hid_srv_bonding_info_t *)(data + sizeof(bt_ull_le_hid_srv_msg_t));
                bonding_info->scenario = ctx->scenario;
                bonding_info->report_rate = ctx->report_rate.rr_level;
                bonding_info->phy = ctx->report_rate.phy;
                bt_ull_le_srv_memcpy(&bonding_info->uni_aa, uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN);
                bt_ull_le_srv_memcpy(&bonding_info->ltk, bt_ull_le_hid_dm_get_ltk(), BT_ULL_LE_HID_DM_LTK_LEN);
                bt_ull_le_srv_memcpy(&bonding_info->skd, bt_ull_le_hid_dm_get_skd(), BT_ULL_LE_HID_DM_SKD_LEN);
                bt_ull_le_srv_memcpy(&bonding_info->iv, bt_ull_le_hid_dm_get_iv(), BT_ULL_LE_HID_DM_IV_LEN);
                int status = bt_ull_le_hid_srv_l2cap_send_data(conn, data, len);
                bt_ull_le_srv_memory_free(data);
                if (0 == status) {
                    switch (rsp->param.bonding_rsp.device_type) {
                        case BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD: {
                            bt_ull_le_srv_memcpy(&g_gp_uni_aa[0], uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN);
                            break;
                        }
                        case BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD: {
                            bt_ull_le_srv_memcpy(&g_kb_uni_aa[0], uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN);
                            break;
                        }
                        case BT_ULL_LE_HID_SRV_DEVICE_MOUSE: {
                            bt_ull_le_srv_memcpy(&g_ms_uni_aa[0], uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN);
                            break;
                        }
                        default :
                            break;
                    }
                    bt_ull_le_hid_srv_start_timer(g_bt_ull_le_sync_bonding_info_timer_handle, BT_ULL_LE_HID_SRV_TIMEOUT, bt_ull_le_hid_srv_timer_timeout_handler, 0);
                }
                LOG_INF(BT_ULL_HID_LOG"SEND SYNC BONDING INFO [SERVER]!!, status: %x, Uni_AA: %x-%x-%x-%x", status, \
                    uni_aa[0], uni_aa[1], uni_aa[2], uni_aa[3]);
            } else {
                bt_ull_le_hid_srv_bonding_complete_ind_t bonding_complete;
                bonding_complete.conn = conn;
                bt_ull_le_srv_memcpy(&bonding_complete.peer_addr, &ctx->link[idx].peer_addr, sizeof(bt_addr_le_t));
                bonding_complete.status = -EPERM;
                bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_APP, BT_ULL_EVENT_LE_HID_BONDING_COMPLETE_IND, &bonding_complete, sizeof(bt_ull_le_hid_srv_bonding_complete_ind_t));
            }

            break;
        }
        case BT_ULL_LE_HID_MSG_SYNC_BONDING_INFO: {
            bt_ull_le_hid_srv_stop_timer(g_bt_ull_le_sync_bonding_info_timer_handle);
            LOG_INF(BT_ULL_HID_LOG"RECEIVE SYNC BONDING INFO RSP [SERVER]!!");
            if (BT_ULL_LE_HID_SRV_RSP_STATUS_SUCCESS == rsp->status) {
                bt_ull_le_hid_dm_device_info_t device_info;
                bt_ull_le_srv_memset(&device_info, 0, sizeof(bt_ull_le_hid_dm_device_info_t));
                uint8_t device_type = bt_ull_le_hid_srv_get_device_type_by_idx(idx);
                bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
                device_info.device_type = device_type;
                device_info.scenario = ctx->scenario;
                if (BT_ULL_LE_HID_SRV_DEVICE_HEADSET == device_type) {
                    LOG_ERR(BT_ULL_HID_LOG"Device Type error!,  Not support HS && EB!!");
                }
                switch (device_type) {
                    case BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD: {
                        bt_ull_le_srv_memcpy(&device_info.uni_aa, &g_gp_uni_aa[0], BT_ULL_LE_HID_DM_UNI_AA_LEN);
                        break;
                    }
                    case BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD: {
                        bt_ull_le_srv_memcpy(&device_info.uni_aa, &g_kb_uni_aa[0], BT_ULL_LE_HID_DM_UNI_AA_LEN);
                        break;
                    }
                    case BT_ULL_LE_HID_SRV_DEVICE_MOUSE: {
                        bt_ull_le_srv_memcpy(&device_info.uni_aa, &g_ms_uni_aa[0], BT_ULL_LE_HID_DM_UNI_AA_LEN);
                        break;
                    }
                    default :
                        break;
                }
                bt_ull_le_srv_memcpy(&device_info.addr, &ctx->link[idx].peer_addr, sizeof(bt_addr_le_t));
                bt_ull_le_srv_memcpy(&device_info.ltk, bt_ull_le_hid_dm_get_ltk(), BT_ULL_LE_HID_DM_LTK_LEN);
                bt_ull_le_srv_memcpy(&device_info.skd, bt_ull_le_hid_dm_get_skd(), BT_ULL_LE_HID_DM_SKD_LEN);
                bt_ull_le_srv_memcpy(&device_info.iv, bt_ull_le_hid_dm_get_iv(), BT_ULL_LE_HID_DM_IV_LEN);

                int status = bt_ull_le_hid_dm_write_device_info(&device_info);
                if (status < 0) {
                    LOG_ERR(BT_ULL_HID_LOG"l2cap_rx_response_hdl, save device info fail!!");
                }
                bt_ull_le_hid_srv_bonding_complete_ind_t bonding_complete;
                bonding_complete.conn = conn;
                bonding_complete.status = status;
                bt_ull_le_srv_memcpy(&bonding_complete.peer_addr, &ctx->link[idx].peer_addr, sizeof(bt_addr_le_t));
                LOG_INF(BT_ULL_HID_LOG"BONDING COMPLETE!! [SERVER][dt: %d]!!" , device_type);
                bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_APP, BT_ULL_EVENT_LE_HID_BONDING_COMPLETE_IND, &bonding_complete, sizeof(bt_ull_le_hid_srv_bonding_complete_ind_t));

            } else {
                bt_ull_le_hid_srv_bonding_complete_ind_t bonding_complete;
                bonding_complete.conn = conn;
                bonding_complete.status = -EPERM;
                bt_ull_le_srv_memcpy(&bonding_complete.peer_addr, &ctx->link[idx].peer_addr, sizeof(bt_addr_le_t));
                bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_APP, BT_ULL_EVENT_LE_HID_BONDING_COMPLETE_IND, &bonding_complete, sizeof(bt_ull_le_hid_srv_bonding_complete_ind_t));
            }
            break;
        }
        default:
            break;

    }
}

static void bt_ull_le_hid_srv_l2cap_rx_service_connect_req_hdl(struct bt_conn *conn)
{
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_conn(conn);
    if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx) {
        LOG_ERR(BT_ULL_HID_LOG"2cap_rx_service_connect_req_hdl, no link resource!!");
        return;
    }
    bt_ull_role_t role = bt_ull_le_hid_srv_get_role();
    if (BT_ULL_ROLE_CLIENT != role) {
        LOG_ERR(BT_ULL_HID_LOG"2cap_rx_service_connect_req_hdl, error role!!");
        return;
    }
    uint8_t device_type = bt_ull_le_hid_srv_get_device_type_by_idx(idx);
    LOG_INF(BT_ULL_HID_LOG"RECEIVE SERVICE_CONNECT REQ [CLIENT]!!, device_type: %d", device_type);
    uint16_t len = sizeof(bt_ull_le_hid_srv_msg_t) + sizeof(bt_ull_le_hid_srv_rsp_t);
    uint8_t *data = (uint8_t *)bt_ull_le_srv_memory_alloc(len);
    __ASSERT(data != NULL, "out of memory");
    data[0] = BT_ULL_LE_HID_MSG_RESPONSE;
    bt_ull_le_hid_srv_rsp_t *response = (bt_ull_le_hid_srv_rsp_t *)(data + sizeof(bt_ull_le_hid_srv_msg_t));
    response->cmd_id = BT_ULL_LE_HID_MSG_SERVICE_CONNECT_REQ;
    response->status = BT_ULL_LE_HID_SRV_RSP_STATUS_SUCCESS;
    response->param.connect_rsp.device_type = device_type;
    int status = bt_ull_le_hid_srv_l2cap_send_data(conn, data, len);
    bt_ull_le_srv_memory_free(data);
    if (0 == status) {
        LOG_INF(BT_ULL_HID_LOG"SEND SERVICE_CONNECT RESPONSE [CLIENT]!!");
    } else {
        LOG_ERR(BT_ULL_HID_LOG"SEND SERVICE_CONNECT RESPONSE FAIL [CLIENT]!!");
    }

}

static void bt_ull_le_hid_srv_l2cap_rx_data_hdl(struct bt_conn *conn, uint16_t len, struct net_buf *buf, bt_ull_le_hid_srv_msg_t data_type)
{
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_conn(conn);
    if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx || !buf) {
        LOG_ERR(BT_ULL_HID_LOG"l2cap_rx_user_data_hdl, invalid handle!");
        return;
    }
    bt_ull_event_t evt = 0x00;
    uint8_t *data = buf->data;
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    bt_ull_user_data_t user_data;
    bt_ull_le_srv_memcpy(&user_data.remote_address, ctx->link[idx].peer_addr.a.val, sizeof(bt_addr_t));
    switch (data_type) {
        case BT_ULL_LE_HID_EVENT_USER_DATA: {
            evt = BT_ULL_EVENT_USER_DATA_IND;
            user_data.user_data_length = *(uint16_t *)(data);
            data += sizeof(user_data.user_data_length);
            user_data.user_data = data;
            bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_APP, evt, &user_data, sizeof(bt_ull_user_data_t));
            break;
        }
        case BT_ULL_LE_HID_MSG_INPUT_REPORT_DATA: {
            evt = BT_ULL_EVENT_LE_HID_INPUT_REPORT_IND;
            user_data.user_data_length = len;
            user_data.user_data = data;
            bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_APP, evt, &user_data, sizeof(bt_ull_user_data_t));
            break;
        }
        case BT_ULL_LE_HID_MSG_RACE_DATA: {
            evt = BT_ULL_EVENT_LE_HID_RACE_DATA_IND;
            user_data.user_data_length = len;
            user_data.user_data = data;
            bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_AIR_SRV, evt, &user_data, sizeof(bt_ull_user_data_t));
            break;
        }
        default: {
            return;
        }
    }

}

static void bt_ull_le_hid_srv_l2cap_rx_switch_link_hdl(struct bt_conn *conn, struct net_buf *buf)
{
    bt_ull_le_hid_srv_change_link_req_t *change_link = (bt_ull_le_hid_srv_change_link_req_t *)(buf->data);
    if (!change_link) {
        return;
    }
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_conn(conn);
    uint8_t state = bt_ull_le_hid_srv_get_link_state(idx);
    LOG_INF(BT_ULL_HID_LOG"rx_switch_link_hdl! state: 0x%x, idx: 0x%x, dt: %d", state, idx, bt_ull_le_hid_srv_get_device_type_by_idx(idx));
    if (state < BT_ULL_LE_HID_SRV_LINK_STATE_ULL_HID_SRV_CONNECTED) {
        return;
    }
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    if (BT_ULL_ROLE_SERVER == ctx->role) {
        bt_ull_le_hid_srv_switch_link_mode_ind_t switch_link;
        switch_link.conn = conn;
        switch_link.link_mode = change_link->mode;
        bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_APP, BT_ULL_EVENT_LE_HID_SWITCH_LINK_MODE_IND, &switch_link, sizeof(bt_ull_le_hid_srv_switch_link_mode_ind_t));
        bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_AIR_SRV, BT_ULL_EVENT_LE_HID_SWITCH_LINK_MODE_IND, &switch_link, sizeof(bt_ull_le_hid_srv_switch_link_mode_ind_t));
        return;
    }
}

static void bt_ull_le_hid_srv_l2cap_rx_output_report_hdl(struct bt_conn *conn, uint16_t len, struct net_buf *buf, bt_ull_le_hid_srv_msg_t data_type)
{
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_conn(conn);
    if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx || !buf) {
        LOG_ERR(BT_ULL_HID_LOG"l2cap_rx_user_data_hdl, invalid handle!");
        return;
    }
    LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_l2cap_rx_output_report_hdl, len: %d", len);
    uint8_t *report_data = (uint8_t*)bt_ull_le_srv_memory_alloc(len);
    __ASSERT(report_data != NULL, "out of memory");
    bt_ull_le_srv_memcpy(report_data, buf->data, len);
    bt_ull_le_hid_srv_notify_event(BT_ULL_LE_HID_SRV_MODULE_APP, BT_ULL_EVENT_LE_HID_OUTPUT_REPORT_IND, report_data, len);
    bt_ull_le_srv_memory_free(report_data);
}

static void bt_ull_le_hid_srv_l2cap_rx_hdl(struct bt_conn *conn, struct net_buf *buf, uint16_t len) 
{
    if (!conn) {
        LOG_ERR(BT_ULL_HID_LOG"l2cap_rx_data_hdl, invalid conn!");
        return;
    }

    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_conn(conn);
    if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx || !buf || !len) {
        LOG_ERR(BT_ULL_HID_LOG"l2cap_rx_data_hdl, no link resource!!");
        return;
    }
    uint8_t device_type = bt_ull_le_hid_srv_get_device_type_by_idx(idx);
    bt_ull_le_hid_srv_l2cap_hdr *hdr = net_buf_pull_mem(buf, sizeof(*hdr));

    LOG_INF(BT_ULL_HID_LOG"rx data! msg id: 0x%x, conn: 0x%x, dt: %d", hdr->code, conn, device_type);
    switch (hdr->code) {
        case BT_ULL_LE_HID_MSG_RESPONSE: {
            bt_ull_le_hid_srv_l2cap_rx_response_hdl(conn, buf);
            break;
        }
        case BT_ULL_LE_HID_MSG_SERVICE_CONNECT_REQ: {
            bt_ull_le_hid_srv_l2cap_rx_service_connect_req_hdl(conn);
            break;
        }
        case BT_ULL_LE_HID_MSG_SYNC_CONTEXT_INFO: {
            bt_ull_le_hid_srv_l2cap_rx_sync_context_info_hdl(conn, buf);
            break;
        }
        case BT_ULL_LE_HID_MSG_BONDING_REQ: {
            bt_ull_le_hid_srv_l2cap_rx_bonding_req_hdl(conn);
            break;
        }
        case BT_ULL_LE_HID_MSG_SYNC_BONDING_INFO: {
            bt_ull_le_hid_srv_l2cap_rx_sync_bonding_info_hdl(conn, buf);
            break;
        }
        case BT_ULL_LE_HID_MSG_RACE_DATA:
        case BT_ULL_LE_HID_EVENT_USER_DATA: {
            bt_ull_le_hid_srv_l2cap_rx_data_hdl(conn, len - sizeof(bt_ull_le_hid_srv_msg_t), buf, hdr->code);
            break;
        }
        case BT_ULL_LE_HID_MSG_SWITCH_LINK_MODE: {
            bt_ull_le_hid_srv_l2cap_rx_switch_link_hdl(conn, buf);
            break;
        }
        case BT_ULL_LE_HID_MSG_OUT_PUT_DATA: {
            bt_ull_le_hid_srv_l2cap_rx_output_report_hdl(conn, len - sizeof(bt_ull_le_hid_srv_msg_t), buf, hdr->code);
            break;
        }
        default:
            break;

    }

}

static int bt_ull_le_hid_srv_tx_data_req(uint8_t *tx_data, bt_ull_le_hid_srv_msg_t data_type)
{
    int status = -EPERM;
    if (!tx_data) {
        return status;
    }
    bt_ull_user_data_t *user_data = NULL;
    //bt_ull_le_hid_srv_input_report_data_t *hogp_data = NULL;
    bt_ull_le_hid_srv_race_data_t *race_data = NULL;
    uint8_t idx = BT_ULL_LE_HID_SRV_INVALID_VALUE;
    uint8_t i = 0;
    uint8_t *data = NULL;
    uint16_t data_len = 0x0;
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    switch (data_type) {
        case BT_ULL_ACTION_TX_USER_DATA: {
            user_data = (bt_ull_user_data_t *)tx_data;
            for (i =0; i < BT_ULL_LE_HID_SRV_MAX_LINK_NUM; i ++) {
                if (!bt_ull_le_srv_memcmp(&ctx->link[i].peer_addr.a.val, &user_data->remote_address, sizeof(bt_addr_t))) {
                    idx = i;
                }
            }
            data_len = user_data->user_data_length + sizeof(user_data->user_data_length)  + sizeof(bt_ull_le_hid_srv_msg_t);
            data = (uint8_t*)bt_ull_le_srv_memory_alloc(data_len);
            __ASSERT(data != NULL, "out of memory");
            __ASSERT_NO_MSG(user_data->user_data_length && user_data->user_data);
            data[0] = BT_ULL_LE_HID_EVENT_USER_DATA;
            bt_ull_le_srv_memcpy(&data[1], &(user_data->user_data_length), sizeof(user_data->user_data_length));
            bt_ull_le_srv_memcpy(&data[3], user_data->user_data, user_data->user_data_length);
            break;
        }

        case BT_ULL_ACTION_LE_HID_TX_RACE_DATA: {
            race_data = (bt_ull_le_hid_srv_input_report_data_t *)tx_data;
            for (i =0; i < BT_ULL_LE_HID_SRV_MAX_LINK_NUM; i ++) {
                if (!bt_ull_le_srv_memcmp(&ctx->link[i].peer_addr.a.val, &race_data->remote_address, sizeof(bt_addr_t))) {
                    idx = i;
                }
            }
            data_len = race_data->user_data_length + sizeof(bt_ull_le_hid_srv_msg_t);
            data = (uint8_t*)bt_ull_le_srv_memory_alloc(data_len);
            __ASSERT(data != NULL, "out of memory");
            __ASSERT_NO_MSG(race_data->user_data_length && race_data->user_data);
            data[0] = BT_ULL_LE_HID_MSG_RACE_DATA;
            bt_ull_le_srv_memcpy(&data[1], race_data->user_data, race_data->user_data_length);
            break;
        }
        default:
            break;
    }

    if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx || !data) {
        if (data) {
            bt_ull_le_srv_memory_free(data);
        }
        LOG_ERR(BT_ULL_HID_LOG"srv_tx_data_req, idx or data error");
        return status;
    }
    struct bt_conn *conn = bt_ull_le_hid_srv_get_link_conn(idx);
    status = bt_ull_le_hid_srv_l2cap_send_data(conn, data, data_len);
    LOG_INF(BT_ULL_HID_LOG"srv_tx_data_req, status: %d, conn: %x, data_type: %d", status, conn, data_type);
    bt_ull_le_srv_memory_free(data);
    return status;
}

static int bt_ull_le_hid_srv_set_report_rate(bt_ull_le_hid_srv_report_rate_t *report_rate)
{
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();

    LOG_INF("[ULL][LE] bt_ull_le_hid_srv_set_report_rate, set rr :%d, phy: %d, curr rr: %d, phy: %d", report_rate->rr_level, report_rate->phy, ctx->report_rate.rr_level, ctx->report_rate.phy);
    if (BT_ULL_ROLE_CLIENT == ctx->role) {
        return -EPERM;
    }
    if (!report_rate) {
        LOG_INF("[ULL][LE] bt_ull_le_hid_srv_set_report_rate, error param!");
        return -EPERM;
    }
    if (report_rate->rr_level == ctx->report_rate.rr_level && report_rate->phy == ctx->report_rate.phy) {
        LOG_INF("[ULL][LE] bt_ull_le_hid_srv_set_report_rate, same!");
        return 0;
    }
    ctx->report_rate.rr_level = report_rate->rr_level;
    ctx->report_rate.phy = report_rate->phy;
#ifdef CONFIG_AIR_PURE_GAMING_DONGLE_KB_ENABLE
    bt_ull_le_hid_conn_srv_set_report_rate(report_rate, BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD);
#elif CONFIG_AIR_PURE_GAMING_DONGLE_MS_ENABLE
    bt_ull_le_hid_conn_srv_set_report_rate(report_rate, BT_ULL_LE_HID_SRV_DEVICE_MOUSE);
#elif CONFIG_AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE
    bt_ull_le_hid_conn_srv_set_report_rate(report_rate, BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD);
#endif
    return 0;
}

bt_ull_le_hid_srv_app_scenario_t bt_ull_le_hid_srv_get_scenario(void)
{
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    return ctx->scenario;
}

bt_ull_le_hid_srv_report_rate_level_t bt_ull_le_hid_srv_get_report_rate(void)
{
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    return ctx->report_rate.rr_level;
}


#if defined(CONFIG_ULL_HID_LE_CENTRAL)
static int bt_ull_le_hid_srv_send_data_by_device_type(bt_ull_le_hid_srv_device_t device_type, uint8_t *packet, uint16_t packet_size)
{
    LOG_INF("[ULL][LE] bt_ull_le_hid_srv_send_data_by_device_type, device_type :%d, packet_size: %d", device_type, packet_size);
    int result = -EPERM;
    uint8_t i;
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    for (i = 0; i < BT_ULL_LE_HID_SRV_MAX_LINK_NUM; i++) {
        if (BT_ULL_LE_HID_SRV_LINK_STATE_ULL_HID_SRV_CONNECTED <= ctx->link[i].state && (device_type == ctx->link[i].device_type)) {
            struct bt_conn *conn = bt_ull_le_hid_srv_get_link_conn(i);
            result = bt_ull_le_hid_srv_l2cap_send_data(conn, packet, packet_size);
        }
    }
    return result;
}

static int bt_ull_le_hid_srv_led_control_hdl(bt_ull_le_hid_srv_control_indicater_led_t *led_control)
{
    int status = 0;
    uint16_t len = sizeof(bt_ull_le_hid_srv_msg_t) + sizeof(bt_ull_le_hid_srv_control_indicater_led_t);
    uint8_t *data = (uint8_t *)bt_ull_le_srv_memory_alloc(len);
    if (NULL != data) {
        data[0] = BT_ULL_LE_HID_MSG_OUT_PUT_DATA;
        bt_ull_le_hid_srv_control_indicater_led_t *led_control_req = (bt_ull_le_hid_srv_control_indicater_led_t *)(data + sizeof(bt_ull_le_hid_srv_msg_t));
        bt_ull_le_srv_memcpy(led_control_req, led_control, sizeof(bt_ull_le_hid_srv_control_indicater_led_t));
        status = bt_ull_le_hid_srv_send_data_by_device_type(BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD, (uint8_t *)data, len);
        bt_ull_le_srv_memory_free(data);
    }
    LOG_INF(BT_ULL_HID_LOG" bt_ull_le_hid_srv_led_control_hdl, status: 0x%x,led_control:%d", status, led_control->indicater_led);
    return status;
}

static int bt_ull_le_hid_srv_get_conn_quality_info(bt_ull_le_hid_srv_get_conn_quality_info_t *quality_info)
{
    int status = -EPERM;
    if (!quality_info) {
        LOG_ERR(BT_ULL_HID_LOG"bt_ull_le_hid_srv_get_conn_quality_info, params error!!");
        return status;
    }
    LOG_INF(BT_ULL_HID_LOG" bt_ull_le_hid_srv_get_conn_quality_info, device_type: 0x%x, period: %d", quality_info->device_type, quality_info->update_period);
    status = bt_ull_le_hid_conn_srv_get_conn_info(quality_info);
    return status;
}

static int bt_ull_le_hid_srv_enable_cis_scan(bt_ull_le_hid_srv_enable_cis_scan_t *cis_scan)
{
    int status = -EPERM;
    if (!cis_scan) {
        return -EPERM;
    }
    LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_enable_cis_scan , dt: %d, interval: %d, window: %d", 
        cis_scan->device_type, cis_scan->scan_interval, cis_scan->scan_window);
    bt_ull_le_enable_air_hid_cis_scan_t scan_params;
    scan_params.enable = cis_scan->enable;
    scan_params.scan_interval = cis_scan->scan_interval;
    scan_params.scan_window = cis_scan->scan_window;
    bt_ull_le_hid_dm_device_info_t* device_info = bt_ull_le_hid_dm_read_device_info(cis_scan->device_type , &cis_scan->address);
    memcpy(&scan_params.uni_aa[0], &device_info->uni_aa[0], BT_ULL_LE_HID_DM_UNI_AA_LEN);
    status = bt_ull_le_enbale_cis_scan(&scan_params);
    return status;
}

static int bt_ull_le_hid_srv_set_tx_power(bt_ull_le_hid_srv_set_tx_power_t *param)
{
    int status = -EPERM;
    if (!param) {
        return -EPERM;
    }
    if (param->tx_power_type == BT_ULL_LE_HID_SRV_TX_POWER_TYPE_LOCAL) {
        LOG_INF(BT_ULL_HID_LOG"set local tx gc, dt: %d, tx_gc: %d", 
            param->device_type, param->local_tx_gc);
        bt_ull_le_set_air_hid_cis_local_tx_gc_t tx_gc_params;
        tx_gc_params.local_tx_gc = param->local_tx_gc;
        status = bt_ull_le_set_tx_local_tx_gc(&tx_gc_params);
    } else if (param->tx_power_type == BT_ULL_LE_HID_SRV_TX_POWER_TYPE_REMOTE){
        LOG_INF(BT_ULL_HID_LOG"set remote tx power, dt: %d, power: %d", 
            param->device_type, param->remote_tx_power_control);
        status = bt_ull_le_hid_conn_srv_set_tx_power(param);
    }

    return status;
}

static int bt_ull_le_hid_srv_set_vpa_tx_gc(bt_ull_le_hid_srv_set_vpa_tx_gc_t *param)
{
    int status = -EPERM;
    if (!param) {
        return -EPERM;
    }
    LOG_INF(BT_ULL_HID_LOG"set remote tx power, dt: %d, gc: %d, vpa: %d", 
            param->device_type, param->tx_gc, param->pa_vol);
    status = bt_ull_le_hid_conn_srv_set_remote_tx_power(param);
    return status;
}

#endif /* defined(CONFIG_ULL_HID_LE_CENTRAL) */

// static bool bt_ull_le_hid_srv_is_device_connected(bt_ull_le_hid_srv_device_t dt)
// {
//     uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_dt(dt);
//     if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx) {
//         return false;
//     }
//     bt_ull_le_hid_srv_link_state_t state = bt_ull_le_hid_srv_get_link_state(idx);
//     if (BT_ULL_LE_HID_SRV_LINK_STATE_ULL_HID_SRV_CONNECTED <= state) {
//         return true;
//     }
//     return false;
// }

void bt_ull_le_hid_srv_get_fota_info(bt_addr_le_t *addr, bt_ull_le_hid_srv_fota_info *info)
{
    uint8_t idx = bt_ull_le_hid_srv_get_link_idx_by_addr(addr);
    if (BT_ULL_LE_HID_SRV_INVALID_VALUE == idx || !info) {
        return;
    }
    bt_ull_le_hid_srv_context_t *ctx = bt_ull_le_hid_srv_get_ctx();
    info->mtu = BT_ULL_LE_HID_SRV_FIX_CHANNEL_MTU - sizeof(bt_ull_le_hid_srv_msg_t) - 2;
    info->att_handle_rx = ctx->link[idx].att_handle_rx;
    info->att_handle_tx = ctx->link[idx].att_handle_tx;
    info->att_handle_cccd = ctx->link[idx].att_handle_cccd;
    info->device_type = bt_ull_le_hid_srv_get_device_type_by_idx(idx);
}

uint8_t bt_ull_le_hid_srv_get_bonded_device_num(bt_ull_le_hid_srv_device_t device_type)
{
    return bt_ull_le_hid_dm_get_bonded_device_num(device_type);
}
void bt_ull_le_hid_srv_get_bonded_device_list(bt_ull_le_hid_srv_device_t device_type, uint8_t count, bt_addr_le_t *list)
{
    return bt_ull_le_hid_dm_get_bonded_device_list(device_type, count, list);
}

void bt_ull_le_hid_srv_get_local_addr_list(bt_ull_le_hid_srv_device_t device_type, uint8_t count, bt_addr_le_t *list)
{
    uint32_t addr_size = 7;
    if (BT_ULL_LE_HID_SRV_DEVICE_MOUSE != device_type) {
        return;
    }
    nvkey_status_t status = nvkey_read_data(NVID_BT_HOST_ULL_HID_LOCAL_ADDRESS, (uint8_t *)list, &addr_size);
    if (NVKEY_STATUS_OK != status && NVKEY_STATUS_ITEM_NOT_FOUND != status) {
        LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_get_local_addr_list,  error nvkey status: %d, size: %d", status, addr_size);
        return;
    }
}

bool bt_ull_le_hid_srv_is_bonded_device(bt_ull_le_hid_srv_device_t device_type, bt_addr_le_t *addr)
{
    return bt_ull_le_hid_dm_is_bonded_device(device_type, addr);
}

int bt_ull_le_hid_srv_clear_bonded_list(bt_ull_le_hid_srv_device_t device_type)
{
    return bt_ull_le_hid_dm_clear_bonded_list(device_type);
}

int bt_ull_le_hid_srv_action(bt_ull_hid_action_t action, const void *param, uint32_t param_len)
{
    int status = 0;
    LOG_INF(BT_ULL_HID_LOG"bt_ull_le_hid_srv_action, action: %x", action);
    switch (action) {
        #if defined(CONFIG_ULL_HID_LE_CENTRAL)
        case BT_ULL_ACTION_LE_HID_CONNECT: {
            bt_ull_le_hid_srv_connect_t *req = (bt_ull_le_hid_srv_connect_t *)param;
            status = bt_ull_le_hid_srv_create_connection_req(req);
            break;
        }
        case BT_ULL_ACTION_LE_HID_BOND: {
            bt_ull_le_hid_srv_bond_t *req = (bt_ull_le_hid_srv_bond_t *)param;
            status = bt_ull_le_hid_srv_start_bonding_req(req);
            break;
        }
        case BT_ULL_ACTION_LE_HID_CONNECT_SERVICE: {
            bt_ull_le_hid_srv_connect_service_t *req = (bt_ull_le_hid_srv_connect_service_t *)param;
            status = bt_ull_le_hid_srv_connect_service_req(req);
            break;
        }
        case BT_ULL_ACTION_LE_HID_SWITCH_LINK_MODE: {
            bt_ull_le_hid_srv_switch_link_mode_t *req = (bt_ull_le_hid_srv_switch_link_mode_t *)param;
            status = bt_ull_le_hid_srv_switch_link_mode_req(req);
            break;
        }
        case BT_ULL_ACTION_LE_HID_CONTROL_RGB: {
            bt_ull_le_hid_srv_control_indicater_led_t *led_control = (bt_ull_le_hid_srv_control_indicater_led_t *)param;
            status = bt_ull_le_hid_srv_led_control_hdl(led_control);
            break;
        }
        case BT_ULL_ACTION_LE_HID_SET_SCENARIO: {
            bt_ull_le_hid_srv_app_scenario_t *scenario = (bt_ull_le_hid_srv_app_scenario_t *)param;
            status = bt_ull_le_hid_srv_set_scenario(*scenario);
            break;
        }
        case BT_ULL_ACTION_LE_HID_SET_IDLE_TIME: {
            bt_ull_le_hid_srv_idle_time_t *idle_time = (bt_ull_le_hid_srv_idle_time_t *)param;
            status = bt_ull_le_hid_srv_set_idle_time(*idle_time);
            break;
        }
        case BT_ULL_ACTION_LE_HID_REMOVE_CIG: {
            status = bt_ull_le_hid_srv_remove_cig();
            break;
        }
        case BT_ULL_ACTION_LE_HID_CANCEL_CONNECT: {
            bt_ull_le_hid_srv_cancel_connect_t *cancel = (bt_ull_le_hid_srv_cancel_connect_t *)param;
            status = bt_ull_le_hid_srv_cancel_connect_hdl(cancel);
            break;
        }
        case BT_ULL_ACTION_LE_HID_SET_OUTPUT_REPORT: {
            bt_ull_le_hid_srv_set_output_report_t *output_report = (bt_ull_le_hid_srv_set_output_report_t *)param;
            bt_ull_le_hid_srv_set_output_report(output_report);
            break;
        }
        case BT_ULL_ACTION_LE_HID_ENABLE_CIS_SCAN: {
            bt_ull_le_hid_srv_enable_cis_scan_t *cis_scan = (bt_ull_le_hid_srv_enable_cis_scan_t *)param;
            bt_ull_le_hid_srv_enable_cis_scan(cis_scan);
            break;
        }
        case BT_ULL_ACTION_LE_HID_SET_TXPOWER: {
            bt_ull_le_hid_srv_set_tx_power_t *tx_power = (bt_ull_le_hid_srv_set_tx_power_t *)param;
            bt_ull_le_hid_srv_set_tx_power(tx_power);
            break;
        }
        case BT_ULL_ACTION_LE_HID_SET_VPA_TX_GC: {
            bt_ull_le_hid_srv_set_vpa_tx_gc_t *vpa_tx_gc = (bt_ull_le_hid_srv_set_vpa_tx_gc_t *)param;
            bt_ull_le_hid_srv_set_vpa_tx_gc(vpa_tx_gc);
            break;
        }
        case BT_ULL_ACTION_LE_HID_GET_CONNECION_QUALITY_INFO: {
            bt_ull_le_hid_srv_get_conn_quality_info_t *quality_info = (bt_ull_le_hid_srv_get_conn_quality_info_t *)param;
            bt_ull_le_hid_srv_get_conn_quality_info(quality_info);
            break;
        }
        #endif
        #if defined (CONFIG_ULL_HID_LE_PERIPHERAL)
        case BT_ULL_ACTION_LE_HID_CREATE_SYNC: {
            bt_ull_le_hid_srv_create_sync_t *req = (bt_ull_le_hid_srv_create_sync_t *)param;
            status = bt_ull_le_hid_srv_create_sync_req(req);
            break;
        }
        case BT_ULL_ACTION_LE_HID_CANCEL_CREATE_SYNC: {
            bt_ull_le_hid_srv_cancel_create_sync_t *cancel = (bt_ull_le_hid_srv_cancel_create_sync_t *)param;
            status = bt_ull_le_hid_srv_cancel_create_sync_hdl(cancel);
            break;
        }
        #endif
        case BT_ULL_ACTION_LE_HID_DISCONNECT: {
            bt_ull_le_hid_srv_disconnect_t *req = (bt_ull_le_hid_srv_disconnect_t *)param;
            status = bt_ull_le_hid_srv_disconnect_req(req);
            break;
        }
        case BT_ULL_ACTION_LE_HID_SET_REPORT_RATE: {
            bt_ull_le_hid_srv_report_rate_t *report_rate = (bt_ull_le_hid_srv_report_rate_t *)param;
            status = bt_ull_le_hid_srv_set_report_rate(report_rate);
            break;
        }
        case BT_ULL_ACTION_TX_USER_DATA:
        case BT_ULL_ACTION_LE_HID_TX_RACE_DATA: {
            uint8_t *tx_data = (uint8_t *)param;
            status = bt_ull_le_hid_srv_tx_data_req(tx_data, action);
            break;
        }
        default:
            break;
    }
    return status;
}
