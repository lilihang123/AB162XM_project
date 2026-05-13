/* Copyright Statement:
 *
 * (C) 2023  Airoha Technology Corp. All rights reserved.
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

#include "bt_hogp_client.h"
//#include "bt_gatt_discover.h"
#include <zephyr/bluetooth/bluetooth.h>

#define LOG_LEVEL CONFIG_BT_HOGP_CLIENT_LOG_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(hogp);

bt_hogp_client_event_callback hogp_client_callabck;
typedef struct {
    uint8_t cccd_num;
    uint8_t refer_num;

    uint16_t refer_handle;
    uint16_t cccd_handle;
    uint16_t extern_refer_handle;

} bt_hogp_descriptor_t;

typedef struct {
    uint8_t type;
    uint16_t value_handle;
    bt_hogp_descriptor_t descriptor;
} bt_hogp_charater_t;

typedef struct {
    uint8_t chara_num;
    bt_hogp_charater_t  chara[BT_HID_SERVICE_DISCOVERY_CHARACTER_MAX_NUMBER];
} bt_hogp_discover_service_t;

typedef struct {
    bool    bonded;
    bool    rediscovery;
    bool    bond_compelte;
    bt_hogp_client_state_t hogp_discovery_state;
    struct bt_conn *conn;
    bt_addr_le_t   bt_addr;
    bt_hogp_client_report_char_t hogp_report_char;
    bt_hogp_client_handle_t hogp_charc_handle;
    uint8_t report_map_length;
    uint8_t *report_map_value;
    uint8_t report_cccd_handle[BT_HID_SERVICE_DISCOVERY_DESCRIPTOR_MAX_NUMBER];
    bt_hogp_discover_service_t service;
    struct bt_gatt_read_params read_params;
    struct bt_gatt_read_params read_long_params;
    struct bt_gatt_subscribe_params cccd_notify_params[BT_HID_SERVICE_DISCOVERY_DESCRIPTOR_MAX_NUMBER];
} bt_hogp_client_context_t;

static bt_hogp_client_context_t g_hogp_client_ctx[BT_HOGP_CLIENT_MAX_LINK_NUM];

//static struct bt_gatt_read_params *s_read_params_p = NULL;
//static struct bt_gatt_read_params *s_long_read_params_p = NULL;
struct bt_gatt_subscribe_params *s_notify_params_p = NULL;

static void *bt_hogp_client_malloc(size_t size);
static void bt_hogp_client_free(void *addr);
static void bt_hogp_client_notify_user(bt_hogp_client_event_t event, bt_hogp_client_para_t *para, const void *buffer, uint16_t length);
static bool bt_hogp_client_addr_is_bonded(struct bt_conn *conn);
static void bt_hogp_clear_context(void);
static void bt_hogp_client_free_conn(struct bt_conn *conn);
static void bt_hogp_client_update_conn(struct bt_conn *conn);
static void bt_hogp_connected(struct bt_conn *conn, uint8_t err);
static void bt_hogp_disconnected(struct bt_conn *conn, uint8_t reason);
static void bt_hogp_security_changed(struct bt_conn *conn, bt_security_t level, enum bt_security_err err);
static int bt_hogp_client_read(struct bt_conn *conn, uint16_t att_handle, bt_gatt_read_func_t func);
static int bt_hogp_client_read_long(struct bt_conn *conn, uint16_t att_handle, bt_gatt_read_func_t func, size_t offset);
static bt_report_id_t bt_hogp_client_find_report_id(struct bt_conn *conn, uint16_t att_handle);
static uint8_t bt_hogp_client_handle_notification(struct bt_conn *conn,
        struct bt_gatt_subscribe_params *params,
        const void *data, uint16_t length);
static uint8_t bt_hogp_client_hid_info(struct bt_conn *conn, uint8_t err,
                                       struct bt_gatt_read_params *params,
                                       const void *data, uint16_t length);
static uint8_t bt_hogp_client_report_map(struct bt_conn *conn, uint8_t err,
        struct bt_gatt_read_params *params,
        const void *data, uint16_t length);
static uint8_t bt_hogp_client_report_ref(struct bt_conn *conn, uint8_t err,
        struct bt_gatt_read_params *params,
        const void *data, uint16_t length);
static uint8_t bt_hogp_client_protocol_mode(struct bt_conn *conn, uint8_t err,
        struct bt_gatt_read_params *params,
        const void *data, uint16_t length);
static uint8_t bt_hogp_client_report(struct bt_conn *conn, uint8_t err,
                                     struct bt_gatt_read_params *params,
                                     const void *data, uint16_t length);
static void bt_hogp_client_set_cccd(struct bt_conn *conn, uint16_t cccd_handle);
static void bt_hogp_client_get_cccd_handle(uint8_t link_index);
static void bt_hogp_client_get_report_ref_handle_by_uuid(struct bt_conn *conn, struct bt_uuid* char_uuid);
static void bt_hogp_client_action(struct bt_conn *conn);
static void bt_hogp_client_assign_handle(struct bt_conn *conn);
static int bt_hogp_client_start(struct bt_conn *conn);
void bt_hogp_client_init(bt_hogp_client_event_callback callback);
static uint8_t bt_hogp_client_get_charateristic_num_by_type(struct bt_conn *conn, bt_hogp_chara_type_t type);

static void *bt_hogp_client_malloc(size_t size)
{
    void *memory = (void *)k_malloc(size);
    if(memory != NULL) {
        memset(memory, 0, size);
    }
    return memory;
}

static void bt_hogp_client_free(void *addr)
{
    if(addr) {
        k_free(addr);
    }
}

static void bt_hogp_client_notify_user(bt_hogp_client_event_t event, bt_hogp_client_para_t *para, const void *buffer, uint16_t length)
{
    if (hogp_client_callabck == NULL) {
        LOG_ERR("[BT_HOGP_CLIENT] event callback is NULL");
        return;
    }
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_notify_user,event:%x, len:%x", event, length);
    hogp_client_callabck(event, para, (void *)buffer, length);
    return;
}

static bool bt_hogp_client_addr_is_bonded(struct bt_conn *conn)
{
    return false;
}

static void bt_hogp_clear_context(void)
{
    uint8_t i;

    for(i = 0; i < BT_HOGP_CLIENT_MAX_LINK_NUM; i++) {
        if(g_hogp_client_ctx[i].conn == 0) {
            memset(&g_hogp_client_ctx[i], 0, sizeof(bt_hogp_client_context_t));
            g_hogp_client_ctx[i].hogp_discovery_state = HOGP_DISCOVEY_SERVICE_IDLE;
        }
    }
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_clear_context!");
}

static void bt_hogp_client_new_conn(struct bt_conn *conn)
{
    uint8_t i;
    struct bt_conn_info info;
    bt_conn_get_info(conn, &info);
    for(i = 0; i < BT_HOGP_CLIENT_MAX_LINK_NUM; i++) {
        if((g_hogp_client_ctx[i].conn == 0) && (g_hogp_client_ctx[i].bt_addr.a.val[5] == 0)) {
            g_hogp_client_ctx[i].conn = conn;
            g_hogp_client_ctx[i].bonded = 0;
            memcpy(&(g_hogp_client_ctx[i].bt_addr.a), &(info.le.dst->a), sizeof(bt_addr_t));
            g_hogp_client_ctx[i].bt_addr.type = info.le.dst->type;
            LOG_INF("[BT_HOGP_CLIENT]NEW_CONN:link_idx = %d, new_conn: type=%u,addr= %u %u %u %u %u %u, conn=0x%08x ", i, g_hogp_client_ctx[i].bt_addr.type
                    , g_hogp_client_ctx[i].bt_addr.a.val[5]
                    , g_hogp_client_ctx[i].bt_addr.a.val[4]
                    , g_hogp_client_ctx[i].bt_addr.a.val[3]
                    , g_hogp_client_ctx[i].bt_addr.a.val[2]
                    , g_hogp_client_ctx[i].bt_addr.a.val[1]
                    , g_hogp_client_ctx[i].bt_addr.a.val[0], conn);
            break;
        }
        if(i == (BT_HOGP_CLIENT_MAX_LINK_NUM - 1)) {
            LOG_ERR("[BT_HOGP_CLIENT] bt_hogp_client_new_conn max!");
            bt_hogp_clear_context();
            bt_hogp_client_new_conn(conn);
        }
    }
    return;
}

static void bt_hogp_client_free_conn(struct bt_conn *conn)
{
    uint8_t i;
    for(i = 0; i < BT_HOGP_CLIENT_MAX_LINK_NUM; i++) {
        if(g_hogp_client_ctx[i].conn == conn) {
            g_hogp_client_ctx[i].conn = 0;
            g_hogp_client_ctx[i].bonded = 0;
            g_hogp_client_ctx[i].report_map_length = 0;
            g_hogp_client_ctx[i].bond_compelte = 0;
            bt_hogp_client_free(g_hogp_client_ctx[i].report_map_value);
            g_hogp_client_ctx[i].report_map_value = NULL;
            break;
        }
    }
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_free_conn, link_index:%x, conn=0x%08x", i, conn);
    return;
}

uint8_t bt_hogp_client_find_context_by_conn(struct bt_conn *conn)
{
    uint8_t i;
    for(i = 0; i < BT_HOGP_CLIENT_MAX_LINK_NUM; i++) {
        if(g_hogp_client_ctx[i].conn == conn) {
            LOG_INF("[BT_HOGP_CLIENT]find_context index = %d", i);
            break;
        }
        if(i == (BT_HOGP_CLIENT_MAX_LINK_NUM - 1)) {
            LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_find_context_by_conn max!");
        }
    }
    return i;
}

static void bt_hogp_client_update_conn(struct bt_conn *conn)
{
    uint8_t i;
    struct bt_conn_info info;
    bt_conn_get_info(conn, &info);
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_update_conn");
    for(i = 0; i < BT_HOGP_CLIENT_MAX_LINK_NUM; i++) {
        LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_update_conn: type=%x,addr= %x %x %x %x %x %x", g_hogp_client_ctx[i].bt_addr.type
                , g_hogp_client_ctx[i].bt_addr.a.val[5]
                , g_hogp_client_ctx[i].bt_addr.a.val[4]
                , g_hogp_client_ctx[i].bt_addr.a.val[3]
                , g_hogp_client_ctx[i].bt_addr.a.val[2]
                , g_hogp_client_ctx[i].bt_addr.a.val[1]
                , g_hogp_client_ctx[i].bt_addr.a.val[0]);
        if(memcmp(&(info.le.dst->a), &(g_hogp_client_ctx[i].bt_addr.a), sizeof(bt_addr_t)) == 0) {
            g_hogp_client_ctx[i].conn = conn;
            LOG_INF("[BT_HOGP_CLIENT] find addr!");
            break;
        }
    }
    if(i == BT_HOGP_CLIENT_MAX_LINK_NUM) {
        bt_hogp_client_new_conn(conn);
    }
    return;
}

void bt_hogp_client_change_mtu_callback(struct bt_conn *conn, uint8_t err,
                                        struct bt_gatt_exchange_params *params)
{
    uint8_t link_index = bt_hogp_client_find_context_by_conn(conn);
    LOG_INF("[BT_HOGP_CLIENT] change_mtu_callback called, index :%x", link_index);
    if (link_index == BT_HOGP_CLIENT_MAX_LINK_NUM) {
        return;
    }
}

static void bt_hogp_connected(struct bt_conn *conn, uint8_t err)
{
    /* new hogp context */
    if(conn) {
        if(conn == 0) {
            return;
        }
        bt_hogp_client_para_t para;
        para.report_id = 0xFF;
        para.conn = conn;
        bt_hogp_client_notify_user(BT_HOGP_CLIENT_EVENT_CONNECT_IND, &para, NULL, 0);
        if(bt_hogp_client_addr_is_bonded(conn)) {
            bt_hogp_client_update_conn(conn);
        } else {
            bt_hogp_client_new_conn(conn);
            static struct bt_gatt_exchange_params exchange_params;
            exchange_params.func = bt_hogp_client_change_mtu_callback;
            int err = bt_gatt_exchange_mtu(conn, &exchange_params);
            LOG_INF("[BT_HOGP_CLIENT] exchange_mtu %d", err);
        }
    }
    return;
}

static void bt_hogp_disconnected(struct bt_conn *conn, uint8_t reason)
{
    /* free hogp context */
    bt_hogp_client_free_conn(conn);
}

static void bt_hogp_security_changed(struct bt_conn *conn, bt_security_t level, enum bt_security_err err)
{
    /* start gatt discover */
    if (err != BT_SECURITY_ERR_SUCCESS) {
        LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_security_callback, fail, err = 0x%x", err);
        bt_hogp_client_free_conn(conn);
        return;
    }

    uint8_t link_index = bt_hogp_client_find_context_by_conn(conn);
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_security_callback, link_index = 0x%x", link_index);
    if(link_index == BT_HOGP_CLIENT_MAX_LINK_NUM) {

        return;
    }
    g_hogp_client_ctx[link_index].bond_compelte = 1;
    //g_hogp_client_ctx[link_index].bonded = 1;
    bt_hogp_client_start(conn);
    g_hogp_client_ctx[link_index].service.chara_num = 0;
    //s_read_params_p = &g_hogp_client_ctx[link_index].s_read_params;
    //s_long_read_params_p = &g_hogp_client_ctx[link_index].s_long_read_params;
    //LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_security_callback, s_read_params_p = 0x%x, s_long_read_params_p:%x", s_read_params_p,g_hogp_client_ctx );
}

static struct bt_conn_cb bt_hogp_conn_callbacks = {
    .connected = bt_hogp_connected,
    .disconnected = bt_hogp_disconnected,
    .security_changed = bt_hogp_security_changed,
};

static int bt_hogp_client_read(struct bt_conn *conn, uint16_t att_handle, bt_gatt_read_func_t func)
{
    //static struct bt_gatt_read_params read_params;
    uint8_t link_index = bt_hogp_client_find_context_by_conn(conn);
    g_hogp_client_ctx[link_index].read_params.func = func;

    g_hogp_client_ctx[link_index].read_params.handle_count  = 1;
    g_hogp_client_ctx[link_index].read_params.single.handle = att_handle;
    g_hogp_client_ctx[link_index].read_params.single.offset = 0;
    int err = bt_gatt_read(conn, &g_hogp_client_ctx[link_index].read_params);
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_read:index:%x, conn:%x,read_param = 0x%x, att_handle:0x%x,err:%x", link_index, conn, &g_hogp_client_ctx[link_index].read_params,att_handle, err);
    return BT_GATT_ITER_STOP;
}

static int bt_hogp_client_read_long(struct bt_conn *conn, uint16_t att_handle, bt_gatt_read_func_t func, size_t offset)
{
    //static struct bt_gatt_read_params read_params;
    uint8_t link_index = bt_hogp_client_find_context_by_conn(conn);
    g_hogp_client_ctx[link_index].read_long_params.func = func;
    //s_long_read_params_p->func = func;
    g_hogp_client_ctx[link_index].read_long_params.handle_count  = 1;
    g_hogp_client_ctx[link_index].read_long_params.single.handle = att_handle;
    g_hogp_client_ctx[link_index].read_long_params.single.offset = offset;
    int err = bt_gatt_read(conn, &g_hogp_client_ctx[link_index].read_long_params);
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_read_long:index:%x, conn:%x,read_param = 0x%x, att_handle:0x%x, err:%x",link_index, conn, &g_hogp_client_ctx[link_index].read_long_params,att_handle, err);
    return BT_GATT_ITER_STOP;
}

static bt_report_id_t bt_hogp_client_find_report_id(struct bt_conn *conn, uint16_t att_handle)
{
    uint8_t i;
    uint8_t link_index = bt_hogp_client_find_context_by_conn(conn);
    bt_report_id_t report_id = 0xFF;
    struct bt_conn_info info;
    bt_conn_get_info(conn, &info);
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_find_report_id, link_index = 0x%x, att_handle:%x", link_index, att_handle);
    if(link_index == BT_HOGP_CLIENT_MAX_LINK_NUM) {
        report_id = 0xFE;
        return report_id;
    }

    for(i = 0; i < BT_HID_SERVICE_REPORT_REF_MAX_NUMBER; i++) {
        if((g_hogp_client_ctx[link_index].hogp_report_char.value_handle[i] == att_handle)) {
            report_id = g_hogp_client_ctx[link_index].hogp_report_char.report_reference[i].report_id;
            break;
        }
    }
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_find_report_id:%x link_index: %d att_handle: 0x%x i:%d", report_id, link_index, att_handle, i);
    return report_id;
}

static uint8_t bt_hogp_client_handle_notification(struct bt_conn *conn,
        struct bt_gatt_subscribe_params *params,
        const void *data, uint16_t length)
{
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_handle_notification, conn = 0x%08x ", conn);
    if (data == NULL) {
        LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_handle_notification data is null");
        return BT_GATT_ITER_STOP;
    }
    bt_hogp_client_para_t para;
    para.conn = conn;
    para.report_id = bt_hogp_client_find_report_id(conn, params->value_handle);
    if(para.report_id == 0xFE) {
        return BT_GATT_ITER_STOP;
    }
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_handle_notification, len = %d , report id = 0x%x", length, para.report_id);
    bt_hogp_client_notify_user(BT_HOGP_CLIENT_EVENT_INPUT_REPORT_IND, &para, data, length);
    return BT_GATT_ITER_CONTINUE;
}

static uint8_t bt_hogp_client_hid_info(struct bt_conn *conn, uint8_t err,
                                       struct bt_gatt_read_params *params,
                                       const void *data, uint16_t length)
{
    LOG_INF("HID information success: conn0x%08x", conn);
    uint8_t link_index = bt_hogp_client_find_context_by_conn(conn);
    uint8_t state = g_hogp_client_ctx[link_index].hogp_discovery_state;
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_hid_info, link_index = 0x%x, state:%x", link_index, state);
    if(link_index  == BT_HOGP_CLIENT_MAX_LINK_NUM || state != HOGP_DISCOVEY_SERVICE_HID_INFO) {

        return BT_GATT_ITER_STOP;
    }
    g_hogp_client_ctx[link_index].hogp_discovery_state = HOGP_DISCOVEY_SERVICE_REPORT_MAP;
    bt_hogp_client_action(conn);
    return BT_GATT_ITER_STOP;
}

static uint8_t bt_hogp_client_report_map(struct bt_conn *conn, uint8_t err,
        struct bt_gatt_read_params *params,
        const void *data, uint16_t length)
{
    uint8_t link_index = bt_hogp_client_find_context_by_conn(conn);
    uint8_t state = g_hogp_client_ctx[link_index].hogp_discovery_state;
    LOG_INF("[BT_HOGP_CLIENT]  report_map , conn:%x, err= 0x%x, length;%x, link_index = 0x%x, state:%x ", conn, err, length, link_index, state);

    if(link_index == BT_HOGP_CLIENT_MAX_LINK_NUM || state != HOGP_DISCOVEY_SERVICE_REPORT_MAP) {
        return BT_GATT_ITER_STOP;
    }
    if (data == NULL) {
        LOG_INF("[BT_HOGP_CLIENT]  data is null ,read complete, report length = 0x%x", g_hogp_client_ctx[link_index].report_map_length);
        if(g_hogp_client_ctx[link_index].hogp_charc_handle.protocol_mode_handle) {
            g_hogp_client_ctx[link_index].hogp_discovery_state = HOGP_DISCOVEY_SERVICE_PROTOCOL_MODE;
        } else {
            g_hogp_client_ctx[link_index].hogp_discovery_state = HOGP_DISCOVEY_SERVICE_REPORT;
        }
        bt_hogp_client_para_t para;
        para.conn = conn;
        para.report_id = 0xFF;
        bt_hogp_client_notify_user(BT_HOGP_CLIENT_EVENT_REPORT_MAP_IND, &para, g_hogp_client_ctx[link_index].report_map_value, g_hogp_client_ctx[link_index].report_map_length);
        bt_hogp_client_free(g_hogp_client_ctx[link_index].report_map_value);
        g_hogp_client_ctx[link_index].report_map_value = NULL;
        LOG_INF("[BT_HOGP_CLIENT]  Free  report_map_value");
        bt_hogp_client_action(conn);
    }  else {
        size_t offset = params->single.offset;
        LOG_INF("[BT_HOGP_CLIENT]  report_map_continue length = 0x%x, offset = %x", g_hogp_client_ctx[link_index].report_map_length, offset);
        if (g_hogp_client_ctx[link_index].report_map_length >= BT_HID_SERVICE_REPORT_MAP_MAX_LENGTH) {
            return BT_GATT_ITER_STOP;
        }
        memcpy(g_hogp_client_ctx[link_index].report_map_value + g_hogp_client_ctx[link_index].report_map_length, data, length - 1);
        g_hogp_client_ctx[link_index].report_map_length += length - 1;
        //bt_hogp_client_read_long(conn, params->single.handle, params->func, offset);
        return BT_GATT_ITER_CONTINUE;
    }

#if 0
    LOG_INF("[BT_HOGP_CLIENT]  report length = 0x%x", g_hogp_client_ctx[link_index].report_map_length);
    memcpy(g_hogp_client_ctx[link_index].report_map_value + g_hogp_client_ctx[link_index].report_map_length, data, length - 1);
    g_hogp_client_ctx[link_index].report_map_length += length - 1;
    if(err == BT_GATT_ITER_STOP) {
        if(g_hogp_client_ctx[link_index].hogp_charc_handle.protocol_mode_handle) {
            g_hogp_client_ctx[link_index].hogp_discovery_state = HOGP_DISCOVEY_SERVICE_PROTOCOL_MODE;
        } else {
            g_hogp_client_ctx[link_index].hogp_discovery_state = HOGP_DISCOVEY_SERVICE_REPORT;
        }
        bt_hogp_client_para_t para;
        para.conn = conn;
        para.report_id = 0xFF;
        bt_hogp_client_notify_user(BT_HOGP_CLIENT_EVENT_REPORT_MAP_IND, &para, g_hogp_client_ctx[link_index].report_map_value, g_hogp_client_ctx[link_index].report_map_length);
        bt_hogp_client_free(g_hogp_client_ctx[link_index].report_map_value);
        LOG_INF("[BT_HOGP_CLIENT]  Free  report_map_value");
    } else {
        bt_hogp_client_read_long(conn, params->single.handle, params->func, offset);
        return BT_GATT_ITER_CONTINUE;
    }
#endif

    return BT_GATT_ITER_STOP;
}

static uint8_t bt_hogp_client_report_ref(struct bt_conn *conn, uint8_t err,
        struct bt_gatt_read_params *params,
        const void *data, uint16_t length)
{
    LOG_INF("[BT_HOGP_CLIENT] Report reference success: conn:%x, data:%x, len:%x", conn, data, length);
    uint8_t link_index = bt_hogp_client_find_context_by_conn(conn);
    uint8_t state = g_hogp_client_ctx[link_index].hogp_discovery_state;
    LOG_INF("[BT_HOGP_CLIENT] Report reference success: link_index:%x, state:%x", link_index, state);
    if(link_index  == BT_HOGP_CLIENT_MAX_LINK_NUM || state != HOGP_DISCOVEY_SERVICE_REPORT_REF) {
        return BT_GATT_ITER_STOP;
    }
    if (data != NULL) {
        g_hogp_client_ctx[link_index].hogp_report_char.report_reference[g_hogp_client_ctx[link_index].hogp_report_char.ref_num].report_id =  *(uint8_t *)data;
        g_hogp_client_ctx[link_index].hogp_report_char.report_reference[g_hogp_client_ctx[link_index].hogp_report_char.ref_num].report_type =  *((uint8_t *)data + 1);
    }

    if(g_hogp_client_ctx[link_index].hogp_report_char.ref_num == 0) {
        g_hogp_client_ctx[link_index].hogp_discovery_state = HOGP_DISCOVEY_SERVICE_SET_CCCD;
    }
    bt_hogp_client_action(conn);
    return BT_GATT_ITER_STOP;
}

static uint8_t bt_hogp_client_protocol_mode(struct bt_conn *conn, uint8_t err,
        struct bt_gatt_read_params *params,
        const void *data, uint16_t length)
{
    LOG_INF("Protocol mode success:");
    uint8_t link_index = bt_hogp_client_find_context_by_conn(conn);
    uint8_t state = g_hogp_client_ctx[link_index].hogp_discovery_state;
    if(link_index == BT_HOGP_CLIENT_MAX_LINK_NUM || state != HOGP_DISCOVEY_SERVICE_PROTOCOL_MODE) {
        LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_protocol_mode, link_index = 0x%x", link_index);
        return BT_GATT_ITER_STOP;
    }
    g_hogp_client_ctx[link_index].hogp_discovery_state = HOGP_DISCOVEY_SERVICE_REPORT;
    bt_hogp_client_action(conn);
    return BT_GATT_ITER_STOP;
}

static uint8_t bt_hogp_client_report(struct bt_conn *conn, uint8_t err,
                                     struct bt_gatt_read_params *params,
                                     const void *data, uint16_t length)
{
    LOG_INF("Report success:conn:0x%08x", conn);
    uint8_t link_index = bt_hogp_client_find_context_by_conn(conn);
    uint8_t state = g_hogp_client_ctx[link_index].hogp_discovery_state;
    if(link_index == BT_HOGP_CLIENT_MAX_LINK_NUM || state != HOGP_DISCOVEY_SERVICE_REPORT) {
        LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_report, link_index = 0x%x", link_index);
        return BT_GATT_ITER_STOP;
    }
    g_hogp_client_ctx[link_index].hogp_discovery_state = HOGP_DISCOVEY_SERVICE_REPORT_REF;
    bt_hogp_client_action(conn);
    return BT_GATT_ITER_STOP;
}

#if 1
static void bt_hogp_client_set_cccd_subscribe_rsp(struct bt_conn *conn, uint8_t err,
        struct bt_gatt_subscribe_params *params)
{
    uint8_t link_index = bt_hogp_client_find_context_by_conn(conn);
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_set_cccd, subcribe cccd_response,link_index:%x, err:%x",  link_index, err);
    if (link_index == BT_HOGP_CLIENT_MAX_LINK_NUM) {
        LOG_ERR("[BT_HOGP_CLIENT] bt_hogp_client_set_cccd_subscribe_rsp index error");
    }
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_set_cccd, subcribe cccd_response,total_cccd_num:%x", g_hogp_client_ctx[link_index].hogp_report_char.cccd_num);
    if(g_hogp_client_ctx[link_index].hogp_report_char.cccd_num == 0) {
        g_hogp_client_ctx[link_index].hogp_discovery_state = HOGP_DISCOVEY_SERVICE_COMPLETE;
        bt_hogp_client_action(conn);
        return;
    }
    g_hogp_client_ctx[link_index].hogp_report_char.cccd_num--;
    uint8_t report_cccd_num = g_hogp_client_ctx[link_index].hogp_report_char.cccd_num;
    s_notify_params_p = &g_hogp_client_ctx[link_index].cccd_notify_params[report_cccd_num];
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_set_cccd, subcribe cccd_response,index:%x, total_cccd_num:%x, handle:%x", report_cccd_num, g_hogp_client_ctx[link_index].hogp_report_char.cccd_num, g_hogp_client_ctx[link_index].report_cccd_handle[g_hogp_client_ctx[link_index].hogp_report_char.cccd_num]);
    bt_hogp_client_set_cccd(conn, g_hogp_client_ctx[link_index].report_cccd_handle[g_hogp_client_ctx[link_index].hogp_report_char.cccd_num]);
}

static void bt_hogp_client_set_cccd(struct bt_conn *conn, uint16_t cccd_handle)
{
    //notify_params = &cccd1_notify_params;
    s_notify_params_p->notify = bt_hogp_client_handle_notification;
    s_notify_params_p->value = BT_GATT_CCC_NOTIFY;
    s_notify_params_p->value_handle = cccd_handle - 1;
    s_notify_params_p->ccc_handle = cccd_handle;
    s_notify_params_p->subscribe = bt_hogp_client_set_cccd_subscribe_rsp;
    atomic_set_bit(s_notify_params_p->flags, BT_GATT_SUBSCRIBE_FLAG_VOLATILE);
    int err = bt_gatt_subscribe(conn, s_notify_params_p);
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_set_cccd, subcribe cccd:%x, err:%x", cccd_handle, err);
}
#endif

#if 0
static void bt_hogp_client_set_cccd_subscribe_rsp(struct bt_conn *conn, uint8_t err,
        struct bt_gatt_subscribe_params *params)
{
    uint8_t link_index = bt_hogp_client_find_context_by_conn(conn);
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_set_cccd, subcribe cccd_response,link_index:%x, err:%x",  link_index, err);
    if (link_index == BT_HOGP_CLIENT_MAX_LINK_NUM) {
        LOG_ERR("[BT_HOGP_CLIENT] bt_hogp_client_set_cccd_subscribe_rsp index error");
    }
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_set_cccd, subcribe cccd_response,total_cccd_num:%x", g_hogp_client_ctx[link_index].hogp_report_char.cccd_num);
    if(g_hogp_client_ctx[link_index].hogp_report_char.cccd_num == 0) {
        g_hogp_client_ctx[link_index].hogp_discovery_state = HOGP_DISCOVEY_SERVICE_COMPLETE;
        bt_hogp_client_action(conn);
        return;
    }
    g_hogp_client_ctx[link_index].hogp_report_char.cccd_num--;
#if 0
    uint8_t report_cccd_num = g_hogp_client_ctx[link_index].hogp_report_char.cccd_num;
    notify_params = &cccd2_notify_params;
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_set_cccd, subcribe cccd_response,index:%x, total_cccd_num:%x, handle:%x", report_cccd_num, g_hogp_client_ctx[link_index].hogp_report_char.cccd_num, g_hogp_client_ctx[link_index].report_cccd_handle[g_hogp_client_ctx[link_index].hogp_report_char.cccd_num]);
    bt_hogp_client_set_cccd(conn, g_hogp_client_ctx[link_index].report_cccd_handle[g_hogp_client_ctx[link_index].hogp_report_char.cccd_num]);
#endif
}

static void bt_hogp_client_set_cccd(struct bt_conn *conn, uint16_t cccd_handle)
{
    uint8_t link_index;
    //notify_params = &cccd1_notify_params;
    notify_params->notify = bt_hogp_client_handle_notification;
    notify_params->value = BT_GATT_CCC_NOTIFY;
    notify_params->value_handle = cccd_handle - 1;
    notify_params->ccc_handle = cccd_handle;
    notify_params->subscribe = bt_hogp_client_set_cccd_subscribe_rsp;
    atomic_set_bit(notify_params->flags, BT_GATT_SUBSCRIBE_FLAG_VOLATILE);
    int err = bt_gatt_subscribe(conn, notify_params);
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_set_cccd, subcribe cccd:%x, err:%x", cccd_handle, err);
    //g_hogp_client_ctx[link_index].hogp_discovery_state = HOGP_DISCOVEY_SERVICE_COMPLETE;
    //bt_hogp_client_action(conn);
}
#endif

static void bt_hogp_client_get_cccd_handle(uint8_t link_index)
{
    uint8_t i, idx = 0;
    for(i = 0; i < g_hogp_client_ctx[link_index].hogp_report_char.charc_num; i++) {
        if(g_hogp_client_ctx[link_index].hogp_report_char.report_reference[i].cccd_handle) {
            g_hogp_client_ctx[link_index].report_cccd_handle[idx] = g_hogp_client_ctx[link_index].hogp_report_char.report_reference[i].cccd_handle;
            LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_get_cccd_handle, cccd_handle = 0x%x, i = %x, idx = %x", g_hogp_client_ctx[link_index].report_cccd_handle[idx], i, idx);
            idx++;
        }
    }
    for(uint8_t num = 0; num < g_hogp_client_ctx[link_index].hogp_report_char.cccd_num; num++) {
        LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_get_cccd_handle, cccd_handle[%x] = %x", num, g_hogp_client_ctx[link_index].report_cccd_handle[num]);
    }
}

static void bt_hogp_client_get_report_ref_handle_by_uuid(struct bt_conn *conn, struct bt_uuid* char_uuid)
{
    uint8_t i, link_index, report_index = 0;
    uint16_t  handle = 0xFF;
    if((link_index = bt_hogp_client_find_context_by_conn(conn)) == BT_HOGP_CLIENT_MAX_LINK_NUM) {
        LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_get_report_ref_handle_by_uuid, link_index = 0x%x", link_index);
        return;
    }
    bt_hogp_client_report_char_t *report_char = &g_hogp_client_ctx[link_index].hogp_report_char;
    report_char->charc_num = 0;
    report_char->cccd_num = 0;
    report_char->ref_num = 0;
    bt_hogp_discover_service_t *service = &g_hogp_client_ctx[link_index].service;
    size_t report_char_num = bt_hogp_client_get_charateristic_num_by_type(conn, HOGP_CHARC_HID_REPORT);
    uint8_t total_char_num = service->chara_num;
    LOG_INF("[BT_HOGP_CLIENT] get_report_ref_handle_by_uuid, report_char_num: 0x%x, total_char_num: %x", report_char_num, total_char_num);
    for(i = 0; i < total_char_num; i++) {
        //handle = bt_gatt_discover_get_desc_handle_by_uuid(conn, BT_GATT_DISCOVER_USER_HOGP_SERVICE, char_uuid, BT_UUID_GATT_CCC);
        LOG_INF("[BT_HOGP_CLIENT] get_report_ref_handle_by_uuid, char_index:%x,type: %x", i, service->chara[i].type);
        if (service->chara[i].type == HOGP_CHARC_HID_REPORT) {
            handle = service->chara[i].descriptor.cccd_handle;
            LOG_INF("[BT_HOGP_CLIENT] get_report_ref_handle_by_uuid, HID Report, char_index:%x, cccd handle:%x", i, handle);
            if(handle != 0xFF && handle != 0) {
                report_char->report_reference[report_index].cccd_handle = handle;
                report_char->cccd_num++;
            }
            handle = service->chara[i].descriptor.refer_handle;
            LOG_INF("[BT_HOGP_CLIENT] get_report_ref_handle_by_uuid, HID Report, char_index:%x,ref handle:%x", i, handle);
            if(handle != 0xFF && handle != 0) {
                report_char->report_reference[report_index].report_ref_handle = handle;
                report_char->ref_num++;
            }
            report_char->value_handle[report_index] = service->chara[i].value_handle;
            LOG_INF("[BT_HOGP_CLIENT] get_report_ref_handle_by_uuid, report_index: %x, vaule:%x, cccd_handle:%x, refer_handle:%x", report_index, report_char->value_handle[report_index], report_char->report_reference[report_index].cccd_handle,report_char->report_reference[report_index].report_ref_handle);
            report_index++;
        }
    }
    LOG_INF("[BT_HOGP_CLIENT] get_report_ref_handle_by_uuid, ref_port: %x", report_index);
    report_char->charc_num = report_char_num;
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_get_report_ref_handle_by_uuid, cccd_num: 0x%x, ref_num: %x", g_hogp_client_ctx[link_index].hogp_report_char.cccd_num, g_hogp_client_ctx[link_index].hogp_report_char.ref_num);
    bt_hogp_client_get_cccd_handle(link_index);
}

static void bt_hogp_client_action(struct bt_conn *conn)
{
    bt_hogp_client_state_t state;
    uint8_t link_index;
    if((link_index = bt_hogp_client_find_context_by_conn(conn)) == BT_HOGP_CLIENT_MAX_LINK_NUM) {
        LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_action, link_index = 0x%x", link_index);
        return;
    }
    state = g_hogp_client_ctx[link_index].hogp_discovery_state;
    LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_action, state = 0x%x, link_index = %d", state, link_index);
    switch (state) {
    case HOGP_DISCOVEY_SERVICE_IDLE: {
        break;
    }
    case HOGP_DISCOVEY_SERVICE_HID_INFO: {
        bt_hogp_client_read(conn, g_hogp_client_ctx[link_index].hogp_charc_handle.hid_info_handle, bt_hogp_client_hid_info);
        break;
    }
    case HOGP_DISCOVEY_SERVICE_REPORT_MAP: {
        bt_hogp_client_read_long(conn, g_hogp_client_ctx[link_index].hogp_charc_handle.report_map_handle, bt_hogp_client_report_map, 0);
        break;
    }
    case HOGP_DISCOVEY_SERVICE_REPORT_REF: {
        LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_action, ref_num = %d", g_hogp_client_ctx[link_index].hogp_report_char.ref_num);
        g_hogp_client_ctx[link_index].hogp_report_char.ref_num--;
        bt_hogp_client_read(conn,  g_hogp_client_ctx[link_index].hogp_report_char.report_reference[g_hogp_client_ctx[link_index].hogp_report_char.ref_num].report_ref_handle, bt_hogp_client_report_ref);
        break;
    }
    case HOGP_DISCOVEY_SERVICE_PROTOCOL_MODE: {
        bt_hogp_client_read(conn, g_hogp_client_ctx[link_index].hogp_charc_handle.protocol_mode_handle, bt_hogp_client_protocol_mode);
        break;
    }
    case HOGP_DISCOVEY_SERVICE_REPORT: {
        bt_hogp_client_read(conn, g_hogp_client_ctx[link_index].hogp_charc_handle.report_handle, bt_hogp_client_report);
        break;
    }
    case HOGP_DISCOVEY_SERVICE_SET_CCCD: {
        uint8_t report_char_num = g_hogp_client_ctx[link_index].hogp_report_char.cccd_num;
        if(report_char_num == 0) {
            g_hogp_client_ctx[link_index].hogp_discovery_state = HOGP_DISCOVEY_SERVICE_COMPLETE;
            bt_hogp_client_action(conn);
            break;
        }
        LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_action, SET_CCCD: report_cccd_num = %d", report_char_num);
#if 1
        g_hogp_client_ctx[link_index].hogp_report_char.cccd_num--;
        uint8_t index = g_hogp_client_ctx[link_index].hogp_report_char.cccd_num;
        s_notify_params_p = &g_hogp_client_ctx[link_index].cccd_notify_params[index];
        LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_action, SET_CCCD: index = %d, handle:%x", index, g_hogp_client_ctx[link_index].report_cccd_handle[index]);
        bt_hogp_client_set_cccd(conn, g_hogp_client_ctx[link_index].report_cccd_handle[index]);
#endif
#if 0
        for (uint8_t i = 0; i < report_char_num; i++) {
            uint16_t cccd_handle = g_hogp_client_ctx[link_index].report_cccd_handle[i];
            LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_action, SET_CCCD: report_cccd_num = %x", cccd_handle);
            if (cccd_handle) {
                notify_params = &cccd_notify_params[i];
                bt_hogp_client_set_cccd(conn, g_hogp_client_ctx[link_index].report_cccd_handle[i]);
            }
        }
#endif
        break;
    }
    case HOGP_DISCOVEY_SERVICE_COMPLETE: {
        //bt_gattc_discovery_continue(connection_handle);
        LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_action, DISCOVERY_SERVICE_COMPLETE, conn:0x%08x, link_index:%x", conn, link_index);

        break;
    }
    default:
        break;
    }
}

static void bt_hogp_client_assign_handle(struct bt_conn *conn)
{
    uint8_t link_index;
    if((link_index = bt_hogp_client_find_context_by_conn(conn)) == BT_HOGP_CLIENT_MAX_LINK_NUM) {
        LOG_INF("[BT_HOGP_CLIENT] bt_hogp_client_assign_handle, link_index = 0x%x", link_index);
        return;
    }
#if 0
    //g_hogp_client_ctx[link_index].hogp_charc_handle.hid_info_handle = bt_gatt_discover_get_character_handle_by_uuid(conn, BT_GATT_DISCOVER_USER_HOGP_SERVICE, BT_UUID_HIDS_INFO);
    if(g_hogp_client_ctx[link_index].hogp_charc_handle.hid_info_handle == 0) {
        LOG_INF("[BT_HOGP_CLIENT] MISS hid info characteristic");
    }
    //g_hogp_client_ctx[link_index].hogp_charc_handle.report_map_handle = bt_gatt_discover_get_character_handle_by_uuid(conn, BT_GATT_DISCOVER_USER_HOGP_SERVICE, BT_UUID_HIDS_REPORT_MAP);
    if(g_hogp_client_ctx[link_index].hogp_charc_handle.report_map_handle == 0) {
        LOG_INF("[BT_HOGP_CLIENT] MISS report map characteristic");
    }
    //g_hogp_client_ctx[link_index].hogp_charc_handle.protocol_mode_handle= bt_gatt_discover_get_character_handle_by_uuid(conn, BT_GATT_DISCOVER_USER_HOGP_SERVICE, BT_UUID_HIDS_PROTOCOL_MODE);
    if(g_hogp_client_ctx[link_index].hogp_charc_handle.protocol_mode_handle == 0) {
        LOG_INF("[BT_HOGP_CLIENT] MISS protocol mode characteristic");
    }
    //g_hogp_client_ctx[link_index].hogp_charc_handle.report_handle = bt_gatt_discover_get_character_handle_by_uuid(conn, BT_GATT_DISCOVER_USER_HOGP_SERVICE, BT_UUID_HIDS_REPORT);
    if(g_hogp_client_ctx[link_index].hogp_charc_handle.report_handle == 0) {
        LOG_INF("[BT_HOGP_CLIENT] MISS report handle characteristic");
    }
#endif
    LOG_INF("[BT_HOGP_CLIENT] client_assign_handle, report_map:%x", g_hogp_client_ctx[link_index].report_map_value);

    bt_hogp_client_get_report_ref_handle_by_uuid(conn, NULL);
    if(g_hogp_client_ctx[link_index].bonded && (!g_hogp_client_ctx[link_index].rediscovery)) {
        g_hogp_client_ctx[link_index].hogp_discovery_state = HOGP_DISCOVEY_SERVICE_SET_CCCD;
    } else {
        g_hogp_client_ctx[link_index].hogp_discovery_state = HOGP_DISCOVEY_SERVICE_HID_INFO;
        if (g_hogp_client_ctx[link_index].report_map_value == NULL) {
            g_hogp_client_ctx[link_index].report_map_value = bt_hogp_client_malloc(BT_HID_SERVICE_REPORT_MAP_MAX_LENGTH);
        }
    }
    bt_hogp_client_action(conn);
}

static int bt_hogp_client_start(struct bt_conn *conn)
{
    extern int bt_hogp_client_service_discover_start(struct bt_conn *conn);
    return  bt_hogp_client_service_discover_start(conn);
}

#if 0
static bt_gatt_discovery_status_t bt_hogp_discover_complete(bt_gatt_discover_complete_param_t *params)
{
    if((params->event != BT_GATT_DISCOVERY_EVENT_COMPLETE) || (params->status != BT_GATT_DISCOVERY_STATUS_SUCCESS)) {
        return BT_GATT_DISCOVERY_STATUS_FAIL;
    }
    bt_hogp_client_assign_handle(params->conn);
    return BT_GATT_DISCOVERY_STATUS_SUCCESS;
}
#endif
void bt_hogp_client_discovery_commplete_notify(struct bt_conn *conn, uint8_t status)
{
    bt_hogp_client_assign_handle(conn);
}

void bt_hogp_client_init(bt_hogp_client_event_callback callback)
{
    if (hogp_client_callabck != NULL) {
        LOG_INF( "[BT_HOGP_CLIENT] init fail, had init");
        return;
    }
    uint8_t i;
    for(i = 0; i < BT_HOGP_CLIENT_MAX_LINK_NUM; i++) {
        memset(&g_hogp_client_ctx[i], 0, sizeof(bt_hogp_client_context_t));
        g_hogp_client_ctx[i].hogp_discovery_state = HOGP_DISCOVEY_SERVICE_IDLE;
    }
    hogp_client_callabck = callback;
    bt_conn_cb_register(&bt_hogp_conn_callbacks);
    //bt_gatt_discover_register_user(BT_GATT_DISCOVER_USER_HOGP_SERVICE, (bt_gatt_discover_complete_cb *)bt_hogp_discover_complete);
    LOG_INF("[BT_HOGP_CLIENT] init HOGP Client");
    return;
}

bt_hogp_client_state_t bt_hogp_client_get_discovery_state(struct bt_conn *conn)
{
    uint8_t link_index = bt_hogp_client_find_context_by_conn(conn);
    bt_hogp_client_state_t state = g_hogp_client_ctx[link_index].hogp_discovery_state;
    LOG_INF("[BT_HOGP_CLIENT] init HOGP Client, get_state:%d", state);
    return state;
}

void bt_hogp_client_set_discovery_state(struct bt_conn *conn, uint8_t state)
{
    uint8_t link_index = bt_hogp_client_find_context_by_conn(conn);
    g_hogp_client_ctx[link_index].hogp_discovery_state = state;
    LOG_INF("[BT_HOGP_CLIENT] set_state:%d", state);
}

void bt_hogp_client_save_character(struct bt_conn *conn, const struct bt_gatt_attr *attr, bt_hogp_chara_type_t type)
{
    uint8_t link_index = bt_hogp_client_find_context_by_conn(conn);
    uint8_t i = g_hogp_client_ctx[link_index].service.chara_num;
    uint16_t handle = bt_gatt_attr_value_handle(attr);
    LOG_INF("[BT_HOGP_CLIENT] save character, type:%x, con_index:%d", type, link_index);
    switch (type) {
    case HOGP_CHARC_HID_INFO: {
        g_hogp_client_ctx[link_index].hogp_charc_handle.hid_info_handle = handle;
        break;
    }
    case HOGP_CHARC_HID_REPORT_MAP: {
        g_hogp_client_ctx[link_index].hogp_charc_handle.report_map_handle = handle;
        break;
    }
    case HOGP_CHARC_HID_PROTOCOL_MODE: {
        g_hogp_client_ctx[link_index].hogp_charc_handle.protocol_mode_handle = handle;
        break;
    }
    case HOGP_CHARC_HID_REPORT: {
        g_hogp_client_ctx[link_index].hogp_charc_handle.report_handle = handle;
        break;
    }
    case HOGP_CHARC_HID_CONTROL_POINT: {

        break;
    }
    case HOGP_CHARC_HID_BOOT_MOUSE_INTPUT_REPORT: {
        break;
    }
    case HOGP_CHARC_HID_BOOT_KB_OUTPUT_REPORT: {
        break;
    }
    }
    g_hogp_client_ctx[link_index].service.chara[i].type = type;
    g_hogp_client_ctx[link_index].service.chara[i].value_handle = handle;
    g_hogp_client_ctx[link_index].service.chara_num++;
    LOG_INF("[BT_HOGP_CLIENT] save character handle:%x, type:%x, chara_num:%d", handle, type, g_hogp_client_ctx[link_index].service.chara_num);
}

static uint8_t bt_hogp_client_get_charateristic_num_by_type(struct bt_conn *conn, bt_hogp_chara_type_t type)
{
    uint8_t i = 0, count = 0;
    uint8_t link_index = bt_hogp_client_find_context_by_conn(conn);
    uint8_t chara_num = g_hogp_client_ctx[link_index].service.chara_num;
    for (i = 0; i < chara_num; i++)
    {
        if (type == g_hogp_client_ctx[link_index].service.chara[i].type) {
            count++;
        }
    }
    LOG_INF("[BT_HOGP_CLIENT] get_chara_num_by_type character type:%x, chara_num:%d", type, count);
    return count;
}

bt_hogp_charater_t  *bt_hogp_client_get_chara_by_handle(bt_hogp_discover_service_t *service, uint16_t handle)
{
    uint8_t num = service->chara_num;
    uint16_t curr_handle = 0, next_handle = 0;
    LOG_INF("[BT_HOGP_CLIENT] get_chara_by_handle character handle:%x, chara_num:%d", handle, num);
    for (uint8_t i = 0; i < num; i++) {
        curr_handle = service->chara[i].value_handle;
        if (i == (num-1)) {
            next_handle = curr_handle;
        } else {
            next_handle = service->chara[i+1].value_handle;
        }
        LOG_INF("[BT_HOGP_CLIENT] get_chara_by_handle character index:%d, curr_handle:%x, next_handle:%x, handle:%x", i, curr_handle, next_handle, handle);
        if (handle > curr_handle && handle < next_handle) {
            LOG_INF("[BT_HOGP_CLIENT] get_chara_by_handle: found chara index is %d:", i);
            return &service->chara[i];
        }
    }
    LOG_INF("[BT_HOGP_CLIENT] get_chara_by_handle:not found chara:");
    return NULL;
}


void bt_hogp_client_save_descriptor(struct bt_conn *conn, const struct bt_gatt_attr *attr, uint8_t descriptor_type)
{
    uint8_t link_index = bt_hogp_client_find_context_by_conn(conn);
    //uint8_t state = g_hogp_client_ctx[link_index].hogp_discovery_state;
    LOG_INF("[BT_HOGP_CLIENT] save_descriptor: type:%x",descriptor_type);
    //bt_hogp_chara_type_t char_type = bt_hogp_client_get_chara_type_by_state(state);
    bt_hogp_charater_t  *chara = bt_hogp_client_get_chara_by_handle(&(g_hogp_client_ctx[link_index].service), attr->handle);

    if (chara != NULL) {
        if (descriptor_type == HOGP_DESCRIPTOR_TYPE_CCCD) {
            chara->descriptor.cccd_handle = attr->handle;
            chara->descriptor.cccd_num++;
            LOG_INF("[BT_HOGP_CLIENT] save_descriptor:CCD-- CCCD.handle:%x,refer.handle:%x,cccd_num:%x",chara->descriptor.cccd_handle, chara->descriptor.refer_handle, chara->descriptor.cccd_num);
        } else if (descriptor_type == HOGP_DESCRIPTOR_TYPE_REPPORT_REFERENCE) {
            chara->descriptor.refer_handle = attr->handle;
            chara->descriptor.refer_num++;
            LOG_INF("[BT_HOGP_CLIENT] save_descriptor: REFER--CCCD.handle:%x, refer.handle:%x, ref_num:%x",chara->descriptor.cccd_handle, chara->descriptor.refer_handle, chara->descriptor.refer_num);
        } else if (descriptor_type == HOGP_DESCRIPTOR_TYPE_EXTERN_REPORT_REFERENCE) {
            chara->descriptor.extern_refer_handle = attr->handle;
            chara->descriptor.refer_num++;
        }
    } else {
        LOG_INF("[BT_HOGP_CLIENT] save_descriptor:not found matched character");
    }

}
