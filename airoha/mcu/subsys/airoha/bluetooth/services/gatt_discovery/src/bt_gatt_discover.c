/* Copyright Statement:
 *
 * (C) 2022  Airoha Technology Corp. All rights reserved.
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

#include "bt_gatt_discover.h"
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/logging/log.h>

#define LOG_LEVEL CONFIG_BT_HOGP_CLIENT_LOG_LEVEL

#define BT_GATT_DISCOVERY_MEMORY_BLOCK_SIZE         (128)


typedef struct {
    sys_snode_t node;
    uint8_t attr_data[BT_GATT_DISCOVERY_MEMORY_BLOCK_SIZE];
}bt_gatt_discover_attr_data_t;

typedef struct {
    bt_gatt_discover_complete_cb user_cb;
    bt_gatt_discover_user_t user;
}bt_gatt_discover_user_data_t;

typedef struct {
    sys_snode_t node;
    bt_gatt_discover_user_t user;
}bt_gatt_discover_user_triggerd_t;

typedef struct {
    sys_snode_t node;
    struct bt_uuid *attr_type;        //  uuid + bt_gatt_service_val or bt_gatt_chrc
    uint16_t handle;
    uint8_t  permit;
}bt_gatt_discover_attr_t;

typedef struct {
    bt_gatt_discover_user_data_t user_data;
    sys_slist_t attr_list;
    sys_slist_t attr_type_list;
    size_t  attr_type_len;
    bt_gatt_discover_attr_t *attr;
    bt_gatt_discover_state_t discover_state;
}bt_gatt_discover_service_t;

typedef struct {
    bt_gatt_discover_service_t discover_service[BT_GATT_DISCOVERY_MAX_USER_NUM];
    struct bt_conn *conn;
    struct bt_gatt_discover_params *discover_params;
    bt_gatt_discover_user_triggerd_t *user_triggered;
    uint16_t service_num;
}bt_gatt_discover_t;

typedef struct {
    struct bt_uuid *uuid;
    bt_gatt_discover_user_t user;
    bool registered;
}bt_gatt_discover_register_t;

static bt_gatt_discover_t g_gatt_discover_context[BT_GATT_DISCOVERY_MAX_LINK_NUM];
static bt_gatt_discover_register_t g_gatt_discover_register_service[BT_GATT_DISCOVERY_MAX_USER_NUM];

static void *bt_gatt_discover_malloc(size_t size);
static void *bt_gatt_discover_alloc_attr_type_data(bt_gatt_discover_service_t *service_addr, size_t len);
static void bt_gatt_discover_free(void *addr);
static uint8_t bt_gatt_discover_get_register_user_idx(bt_gatt_discover_user_t user);
static bt_gatt_discovery_status_t bt_hogp_discover_complete(bt_gatt_discover_service_t *service_addr, bt_gatt_discover_complete_param_t *params);
static uint8_t bt_gatt_discover_get_empty_link(void);
static uint8_t bt_gatt_discover_get_link_idx_by_conn(struct bt_conn *conn);
static uint8_t bt_gatt_discover_get_empty_service(uint8_t link_idx);
static uint8_t bt_gatt_discover_get_service_idx_by_user(uint8_t link_idx, bt_gatt_discover_user_t user);
static uint8_t bt_gatt_discover_get_user_idx(bt_gatt_discover_user_t user);
static bt_gatt_discover_user_t bt_gatt_discover_get_current_user(uint8_t link_idx);
static size_t bt_gatt_discover_get_uuid_size(const struct bt_uuid *uuid);
static bt_gatt_discover_service_t *bt_gatt_discover_get_service_addr(struct bt_conn *conn);
static bt_gatt_discover_service_t *bt_gatt_discover_get_service_addr_by_user(struct bt_conn *conn, bt_gatt_discover_user_t user);
static bt_gatt_discover_attr_t* bt_gatt_discover_attr_store(struct bt_conn *conn, const struct bt_gatt_attr *attr, size_t size);
static void bt_gatt_discover_conn_free(struct bt_conn * conn);
static void bt_gatt_discover_disconnect_cb(struct bt_conn *conn, uint8_t reason);
static bt_gatt_discover_attr_t *bt_gatt_discover_get_attr_by_handle(bt_gatt_discover_service_t *service_addr, uint8_t handle);
static struct bt_gatt_service_val *bt_gatt_discover_get_service_val(bt_gatt_discover_attr_t *attr);
static struct bt_gatt_chrc *bt_gatt_discover_get_chrc_val(bt_gatt_discover_attr_t *attr);
static void bt_gatt_discover_set_state(bt_gatt_discover_service_t *service_addr, bt_gatt_discover_state_t state);
static bt_gatt_discover_state_t bt_gatt_discover_get_state(bt_gatt_discover_service_t *service_addr);
static uint8_t bt_gatt_discover_character_process(struct bt_conn *conn, const struct bt_gatt_attr *attr, struct bt_gatt_discover_params *params);
static uint8_t bt_gatt_discover_attribute_process(struct bt_conn *conn, const struct bt_gatt_attr *attr, struct bt_gatt_discover_params *params);
static uint8_t bt_gatt_discover_service_process(struct bt_conn *conn, const struct bt_gatt_attr *attr, struct bt_gatt_discover_params *params);
static uint8_t bt_hogp_discover_cb(struct bt_conn *conn, const struct bt_gatt_attr *attr, struct bt_gatt_discover_params *params);
static bt_gatt_discovery_status_t bt_gatt_discover_add_user_tirggered(struct bt_conn *conn, bt_gatt_discover_user_t user);
static bt_gatt_discover_user_t bt_gatt_discover_check_user_tirggered(struct bt_conn *conn);
static bool bt_gatt_discover_user_is_register(bt_gatt_discover_user_t user);


static void *bt_gatt_discover_malloc(size_t size)
{
    void *memory = (void *)k_malloc(size);
    if(memory != NULL){
        memset(memory, 0, size);
    }
    return memory;
}

static void *bt_gatt_discover_alloc_attr_type_data(bt_gatt_discover_service_t *service_addr, size_t len)
{
    bt_gatt_discover_attr_data_t *item;
    uint8_t *attr_type_data;
    if(sys_slist_is_empty(&service_addr->attr_type_list) || ((service_addr->attr_type_len + len) > BT_GATT_DISCOVERY_MEMORY_BLOCK_SIZE)){
        item = bt_gatt_discover_malloc(BT_GATT_DISCOVERY_MEMORY_BLOCK_SIZE);
        if(!item){
            return NULL;
        }
        sys_slist_append(&service_addr->attr_type_list, &item->node);
        service_addr->attr_type_len = 0;
    } else{
        item = SYS_SLIST_PEEK_TAIL_CONTAINER(&service_addr->attr_type_list, item, node);
    }
    attr_type_data = &item->attr_data[service_addr->attr_type_len];
    service_addr->attr_type_len += len;
    return attr_type_data;
}

static void bt_gatt_discover_free(void *addr)
{
    if(addr){
        k_free(addr);
    }
}

static uint8_t bt_gatt_discover_get_register_user_idx(bt_gatt_discover_user_t user)
{
    uint8_t i;
    for( i = 0; i < BT_GATT_DISCOVERY_MAX_USER_NUM; i++){
        if(g_gatt_discover_register_service[i].user == user){
            break;
        }
    }
    return i;
}

static bt_gatt_discovery_status_t bt_hogp_discover_complete(bt_gatt_discover_service_t *service_addr, bt_gatt_discover_complete_param_t *params)
{
   if(service_addr->user_data.user_cb){
        service_addr->user_data.user_cb(params);  
   } else {
        return BT_GATT_DISCOVERY_STATUS_FAIL;
   }
   bt_gatt_discover_user_t user = bt_gatt_discover_check_user_tirggered(params->conn);
   if(user == BT_GATT_DISCOVER_USER_SERVICE_NONE){
        return BT_GATT_DISCOVERY_STATUS_FAIL;
   } else {
        uint8_t register_user_idx = bt_gatt_discover_get_register_user_idx(user);
        if(register_user_idx == 0xFF){
            return BT_GATT_DISCOVERY_STATUS_FULL;
        }
        if(bt_gatt_discover_add_user_tirggered(params->conn, user) != BT_GATT_DISCOVERY_STATUS_SUCCESS){
            return BT_GATT_DISCOVERY_STATUS_FAIL;
        }
        struct bt_uuid *service_uuid = g_gatt_discover_register_service[register_user_idx].uuid;
        bt_gatt_discover_start(params->conn, user, service_uuid);
   }
   return BT_GATT_DISCOVERY_STATUS_SUCCESS;
}

static uint8_t bt_gatt_discover_get_empty_link(void)
{
    uint8_t i;
    for(i = 0; i < BT_GATT_DISCOVERY_MAX_LINK_NUM; i++){
        if(g_gatt_discover_context[i].conn == NULL){
            break;
        }
    }
    return i;
}

static uint8_t bt_gatt_discover_get_link_idx_by_conn(struct bt_conn *conn)
{
    uint8_t i;
    for(i = 0; i < BT_GATT_DISCOVERY_MAX_LINK_NUM; i++){
        if(g_gatt_discover_context[i].conn == conn){
            break;
        }
    }
    return i;
}

static uint8_t bt_gatt_discover_get_empty_service(uint8_t link_idx)
{
    uint8_t i;
    for(i = 0; i < BT_GATT_DISCOVERY_MAX_USER_NUM; i++){
        if(g_gatt_discover_context[link_idx].discover_service[i].user_data.user == BT_GATT_DISCOVER_USER_SERVICE_NONE){
            break;
        }
    }
    return i;
}

static uint8_t bt_gatt_discover_get_service_idx_by_user(uint8_t link_idx, bt_gatt_discover_user_t user)
{
    uint8_t i;
    for(i = 0; i < BT_GATT_DISCOVERY_MAX_USER_NUM; i++){
        if(g_gatt_discover_context[link_idx].discover_service[i].user_data.user == user){
            break;
        }
    }
    return i;
}

static uint8_t bt_gatt_discover_get_user_idx(bt_gatt_discover_user_t user)
{
    uint8_t user_idx = 0xFF;
    uint8_t i;
    if(user == BT_GATT_DISCOVER_USER_SERVICE_NONE){
        return user_idx;
    }
    for(i = 0 ; i < BT_GATT_DISCOVERY_MAX_USER_NUM; i++){
        if(g_gatt_discover_register_service[i].user == user){
            user_idx = i;
            break;
        }
    }
    return user_idx;
}

static bt_gatt_discover_user_t bt_gatt_discover_get_current_user(uint8_t link_idx)
{
    bt_gatt_discover_user_triggerd_t *cur_node = g_gatt_discover_context[link_idx].user_triggered;
    if(!cur_node){
        return BT_GATT_DISCOVER_USER_SERVICE_NONE;
    }
    return cur_node->user;
}

static size_t bt_gatt_discover_get_uuid_size(const struct bt_uuid *uuid)
{
    size_t size;
    if(uuid->type == BT_UUID_TYPE_16){
        size = sizeof(struct bt_uuid_16);
    } else if(uuid->type == BT_UUID_TYPE_32){
        size = sizeof(struct bt_uuid_32);
    } else if(uuid->type == BT_UUID_TYPE_128){
        size = sizeof(struct bt_uuid_128);
    } else{
        return 0;
    }
    return size;
}

static bt_gatt_discover_service_t *bt_gatt_discover_get_service_addr(struct bt_conn *conn)
{
    uint8_t link_idx = bt_gatt_discover_get_link_idx_by_conn(conn);
    if(link_idx == BT_GATT_DISCOVERY_MAX_LINK_NUM){
        return NULL;
    }
    bt_gatt_discover_user_t cur_user = bt_gatt_discover_get_current_user(link_idx);
    uint8_t service_idx = bt_gatt_discover_get_service_idx_by_user(link_idx, cur_user);
    if(service_idx == BT_GATT_DISCOVERY_MAX_USER_NUM){
        return NULL;
    }
    bt_gatt_discover_service_t *service_addr = &g_gatt_discover_context[link_idx].discover_service[service_idx];
    return service_addr;
}

static bt_gatt_discover_service_t *bt_gatt_discover_get_service_addr_by_user(struct bt_conn *conn, bt_gatt_discover_user_t user)
{
    uint8_t link_idx = bt_gatt_discover_get_link_idx_by_conn(conn);
    if(link_idx == BT_GATT_DISCOVERY_MAX_LINK_NUM){
        return NULL;
    }
    uint8_t service_idx = bt_gatt_discover_get_service_idx_by_user(link_idx, user);
    if(service_idx == BT_GATT_DISCOVERY_MAX_USER_NUM){
        return NULL;
    }
    bt_gatt_discover_service_t *service_addr = &g_gatt_discover_context[link_idx].discover_service[service_idx];
    return service_addr;
}

static bt_gatt_discover_attr_t* bt_gatt_discover_attr_store(struct bt_conn *conn, const struct bt_gatt_attr *attr, size_t size)
{
    if(!conn || !attr){
        return NULL;
    }
    size_t uuid_size = bt_gatt_discover_get_uuid_size(attr->uuid);
    if(!uuid_size){
        return NULL;
    }
    bt_gatt_discover_service_t *service_addr = bt_gatt_discover_get_service_addr(conn);
    uint8_t *attr_type_data = bt_gatt_discover_alloc_attr_type_data(service_addr, size + uuid_size);
    bt_gatt_discover_attr_t *cur_attr = (bt_gatt_discover_attr_t *)bt_gatt_discover_malloc(sizeof(bt_gatt_discover_attr_t));
    if(!cur_attr){
        return NULL;
    }
    sys_slist_t cur_attr_list = service_addr->attr_list;
    sys_slist_append(&cur_attr_list, &cur_attr->node);
    cur_attr->handle = attr->handle;
    cur_attr->permit = attr->perm;
    cur_attr->attr_type = (struct bt_uuid *)(attr_type_data + size);
    memcpy(cur_attr->attr_type, attr->uuid, uuid_size);
    return cur_attr;
}

static void bt_gatt_discover_conn_free(struct bt_conn * conn)
{
    uint8_t link_idx = bt_gatt_discover_get_link_idx_by_conn(conn);
    if(link_idx == BT_GATT_DISCOVERY_MAX_LINK_NUM){
        return NULL;
    }
    sys_snode_t *attr_node, *attr_type_node;
    bt_gatt_discover_service_t *service_addr;
    bt_gatt_discover_attr_t *attr;
    bt_gatt_discover_attr_data_t *attr_data;
    for(uint8_t i = 0; i < BT_GATT_DISCOVERY_MAX_USER_NUM; i++){
        service_addr = &g_gatt_discover_context[link_idx].discover_service[i];
        SYS_SLIST_FOR_EACH_NODE(&service_addr->attr_type_list, attr_type_node) {
            attr_data = CONTAINER_OF(attr_type_node, bt_gatt_discover_attr_data_t, node);
            bt_gatt_discover_free(attr_data);
        }
        SYS_SLIST_FOR_EACH_NODE(&service_addr->attr_list, attr_node) {
            attr = CONTAINER_OF(attr_node, bt_gatt_discover_attr_t, node);
            bt_gatt_discover_free(attr);
        }
    }
    memset(&g_gatt_discover_context[link_idx], 0, sizeof(bt_gatt_discover_t));
}


static void bt_gatt_discover_disconnect_cb(struct bt_conn *conn, uint8_t reason)
{
    if(!conn){
        return;
    }
    bt_gatt_discover_conn_free(conn);
}

static bt_gatt_discover_attr_t *bt_gatt_discover_get_attr_by_handle(bt_gatt_discover_service_t *service_addr, uint8_t handle)
{
    bt_gatt_discover_attr_t *attr;
    sys_snode_t *attr_node;
    SYS_SLIST_FOR_EACH_NODE(&service_addr->attr_list, attr_node) {
        attr = CONTAINER_OF(attr_node, bt_gatt_discover_attr_t, node);
        if(attr->handle == handle){
            return attr;
        }
    }
    return NULL;
}

static struct bt_gatt_service_val *bt_gatt_discover_get_service_val(bt_gatt_discover_attr_t *attr)
{
    if((!bt_uuid_cmp(BT_UUID_GATT_PRIMARY, attr->attr_type)) || (!bt_uuid_cmp(BT_UUID_GATT_SECONDARY, attr->attr_type))){
        return (struct bt_gatt_service_val *)((uint8_t *)(attr->attr_type) - sizeof(struct bt_gatt_service_val));
    }
    return NULL;
}

static struct bt_gatt_chrc *bt_gatt_discover_get_chrc_val(bt_gatt_discover_attr_t *attr)
{
    if(!bt_uuid_cmp(BT_UUID_GATT_CHRC, attr->attr_type)){
        return (struct bt_gatt_chrc *)((uint8_t *)(attr->attr_type) - sizeof(struct bt_gatt_chrc));
    }
    return NULL;
}

uint16_t bt_gatt_discover_get_character_handle_by_uuid(struct bt_conn *conn, bt_gatt_discover_user_t user, struct bt_uuid *char_uuid)
{
    bt_gatt_discover_attr_t *attr;
    sys_snode_t *attr_node;
    bt_gatt_discover_service_t *service_addr = bt_gatt_discover_get_service_addr_by_user(conn, user);
    SYS_SLIST_FOR_EACH_NODE(&service_addr->attr_list, attr_node) {
        attr = CONTAINER_OF(attr_node, bt_gatt_discover_attr_t, node);
        if(!bt_uuid_cmp(char_uuid, attr->attr_type)){
            return attr->handle;
        }
    }
    return 0xFF;
}

size_t bt_gatt_discover_get_character_num_by_uuid(struct bt_conn *conn, bt_gatt_discover_user_t user, struct bt_uuid *char_uuid)
{
    bt_gatt_discover_attr_t *attr;
    sys_snode_t *attr_node;
    size_t num = 0;
    bt_gatt_discover_service_t *service_addr = bt_gatt_discover_get_service_addr_by_user(conn, user);
    SYS_SLIST_FOR_EACH_NODE(&service_addr->attr_list, attr_node) {
        attr = CONTAINER_OF(attr_node, bt_gatt_discover_attr_t, node);
        if(!bt_uuid_cmp(char_uuid, attr->attr_type)){
            num++;
        }
    }
    return num; 
}

uint16_t bt_gatt_discover_get_desc_handle_by_uuid(struct bt_conn *conn, bt_gatt_discover_user_t user, struct bt_uuid *char_uuid, struct bt_uuid *desc_uuid)
{
    bt_gatt_discover_attr_t *attr;
    sys_snode_t *attr_node;
    static bool find_charc_flag = false;
    bt_gatt_discover_service_t *service_addr = bt_gatt_discover_get_service_addr_by_user(conn, user);
    SYS_SLIST_FOR_EACH_NODE(&service_addr->attr_list, attr_node) {
        attr = CONTAINER_OF(attr_node, bt_gatt_discover_attr_t, node);
        if(find_charc_flag){
            if(!bt_uuid_cmp(desc_uuid, attr->attr_type)){
                find_charc_flag = false;
                return attr->handle;
            }
        } else {
            if(!bt_uuid_cmp(char_uuid, attr->attr_type)){
                find_charc_flag = true;
                continue;
            }
        }
    }
    return 0xFF;
}

static void bt_gatt_discover_set_state(bt_gatt_discover_service_t *service_addr, bt_gatt_discover_state_t state)
{
    service_addr->discover_state = state;
}

static bt_gatt_discover_state_t bt_gatt_discover_get_state(bt_gatt_discover_service_t *service_addr)
{
    return service_addr->discover_state;
}

static uint8_t bt_gatt_discover_character_process(struct bt_conn *conn, const struct bt_gatt_attr *attr, 
                                                            struct bt_gatt_discover_params *params)
{
    bt_gatt_discover_service_t *service_addr = bt_gatt_discover_get_service_addr(conn);
    bt_gatt_discover_complete_param_t discover_complete_params;
    discover_complete_params.conn = conn;
    
    if(!attr){
        discover_complete_params.event = BT_GATT_DISCOVERY_EVENT_FAIL;
        discover_complete_params.status = BT_GATT_DISCOVERY_STATUS_SUCCESS;
        bt_hogp_discover_complete(service_addr, &discover_complete_params);
        bt_gatt_discover_set_state(service_addr, BT_GATT_DISCOVER_STATE_NONE);
        return BT_GATT_ITER_STOP;
    }
    bt_gatt_discover_set_state(service_addr, BT_GATT_DISCOVER_STATE_CHARACTER);
    struct bt_gatt_chrc *gatt_chrc = (struct bt_gatt_chrc *)attr->user_data;
    bt_gatt_discover_attr_t *cur_attr = bt_gatt_discover_get_attr_by_handle(service_addr, attr->handle);
    struct bt_gatt_chrc *cur_gatt_chrac = bt_gatt_discover_get_chrc_val(cur_attr);
    memcpy(cur_gatt_chrac, gatt_chrc, sizeof(struct bt_gatt_chrc));
    return BT_GATT_ITER_CONTINUE;
}

static uint8_t bt_gatt_discover_attribute_process(struct bt_conn *conn, const struct bt_gatt_attr *attr, 
                                                            struct bt_gatt_discover_params *params)
{
    bt_gatt_discover_service_t *service_addr = bt_gatt_discover_get_service_addr(conn);
    bt_gatt_discover_attr_t *discover_attr;
    uint16_t handle;
    bt_gatt_discover_complete_param_t discover_complete_params;
    discover_complete_params.conn = conn;
    if(!attr){
        /* attribute discover complete,then start discover character */
        
        if(!sys_slist_is_empty(&service_addr->attr_list)){
            discover_attr = SYS_SLIST_PEEK_HEAD_CONTAINER(&service_addr->attr_list, discover_attr, node);
            handle = discover_attr->handle;
            params->start_handle = handle + 1;
            params->type = BT_GATT_DISCOVER_CHARACTERISTIC;
            if(bt_gatt_discover(conn, params)){
                discover_complete_params.event = BT_GATT_DISCOVERY_EVENT_COMPLETE;
                discover_complete_params.status = BT_GATT_DISCOVERY_STATUS_FAIL;
                bt_hogp_discover_complete(service_addr, &discover_complete_params);
                return BT_GATT_ITER_STOP;
            }
        } else {
            discover_complete_params.event = BT_GATT_DISCOVERY_EVENT_COMPLETE;
            discover_complete_params.status = BT_GATT_DISCOVERY_STATUS_SUCCESS;
            bt_hogp_discover_complete(service_addr, &discover_complete_params);
        }
        return BT_GATT_ITER_STOP;
    }
    bt_gatt_discover_set_state(service_addr, BT_GATT_DISCOVER_STATE_ATTRIBUTE);
    bt_gatt_discover_attr_t *cur_attr;
    if (bt_uuid_cmp(attr->uuid, BT_UUID_GATT_CHRC) == 0) {
        cur_attr = bt_gatt_discover_attr_store(conn, attr, sizeof(struct bt_gatt_chrc));
    } else{
        cur_attr = bt_gatt_discover_attr_store(conn, attr, 0);
    }
    return BT_GATT_ITER_CONTINUE;
}

static uint8_t bt_gatt_discover_service_process(struct bt_conn *conn, const struct bt_gatt_attr *attr, 
                                                            struct bt_gatt_discover_params *params)
{
    bt_gatt_discover_service_t *service_addr = bt_gatt_discover_get_service_addr(conn);
    bt_gatt_discover_complete_param_t discover_complete_params;
    discover_complete_params.conn = conn;
    if(!conn || !attr || !params){
        discover_complete_params.event = BT_GATT_DISCOVERY_EVENT_COMPLETE;
        discover_complete_params.status = BT_GATT_DISCOVERY_STATUS_FAIL;
        bt_hogp_discover_complete(service_addr, &discover_complete_params);
        return BT_GATT_DISCOVERY_STATUS_FAIL;
    }
    bt_gatt_discover_set_state(service_addr, BT_GATT_DISCOVER_STATE_SERVICE);
    bt_gatt_discover_attr_t *cur_attr = bt_gatt_discover_attr_store(conn, attr, sizeof(struct bt_gatt_service_val));

    struct bt_gatt_service_val *service_val = (struct bt_gatt_service_val*)(attr->user_data);
    struct bt_gatt_service_val *cur_service_val = bt_gatt_discover_get_service_val(cur_attr);
    memcpy(cur_service_val, service_val, sizeof(struct bt_gatt_service_val));
    params->start_handle = attr->handle + 1;
    params->end_handle = service_val->end_handle;
    params->type = BT_GATT_DISCOVER_ATTRIBUTE;
    params->uuid = NULL;
    if(bt_gatt_discover(conn, params)){
        return BT_GATT_ITER_STOP;
    }
    return BT_GATT_ITER_STOP;
}

static uint8_t bt_hogp_discover_cb(struct bt_conn *conn, const struct bt_gatt_attr *attr, 
                                                            struct bt_gatt_discover_params *params)
{
    bt_gatt_discover_service_t *service_addr = bt_gatt_discover_get_service_addr(conn);
    bt_gatt_discover_complete_param_t discover_complete_params;
    discover_complete_params.conn = conn;
    if(!attr){
        discover_complete_params.event = BT_GATT_DISCOVERY_EVENT_COMPLETE;
        discover_complete_params.status = BT_GATT_DISCOVERY_STATUS_FAIL;
        bt_hogp_discover_complete(service_addr, &discover_complete_params);
    }
    switch (params->type)
    {
    case BT_GATT_DISCOVER_PRIMARY:
    case BT_GATT_DISCOVER_SECONDARY:
        /* code */
        return bt_gatt_discover_service_process(conn, attr, params);
        break;
    case BT_GATT_DISCOVER_ATTRIBUTE:
        /* code */
        return bt_gatt_discover_attribute_process(conn, attr, params);
        break;
    case BT_GATT_DISCOVER_CHARACTERISTIC:
        /* code */
        return bt_gatt_discover_character_process(conn, attr, params);
        break;
    default:
        break;
    }
    return BT_GATT_ITER_STOP;
}

static bt_gatt_discovery_status_t bt_gatt_discover_add_user_tirggered(struct bt_conn *conn, bt_gatt_discover_user_t user)
{
    bt_gatt_discovery_status_t status = BT_GATT_DISCOVERY_STATUS_SUCCESS;
    uint8_t link_idx = bt_gatt_discover_get_link_idx_by_conn(conn);
    bt_gatt_discover_user_triggerd_t *user_triggerd_node = (bt_gatt_discover_user_triggerd_t *)bt_gatt_discover_malloc(sizeof(bt_gatt_discover_user_triggerd_t));
    if(user_triggerd_node == NULL){
        return BT_GATT_DISCOVERY_STATUS_OUT_OF_MEMORY;
    }
    user_triggerd_node->user = user;
    user_triggerd_node->node.next = NULL;
    bt_gatt_discover_user_triggerd_t *cur_node = g_gatt_discover_context[link_idx].user_triggered;
    if(cur_node == NULL){//first node
        cur_node = user_triggerd_node;
    } else{
        while(cur_node->node.next){
            if(cur_node->user == user){
                bt_gatt_discover_free(user_triggerd_node);
                return status;
            }
            cur_node->node = *cur_node->node.next;
        }
        cur_node->node.next = &user_triggerd_node->node;
    }
    return status;
}

static bt_gatt_discover_user_t bt_gatt_discover_check_user_tirggered(struct bt_conn *conn)
{
    bt_gatt_discover_user_t user = BT_GATT_DISCOVER_USER_SERVICE_NONE;
    uint8_t link_idx = bt_gatt_discover_get_link_idx_by_conn(conn);
    if(!g_gatt_discover_context[link_idx].user_triggered){
        return user;
    }
    bt_gatt_discover_user_triggerd_t *cur_node = g_gatt_discover_context[link_idx].user_triggered;
    cur_node->node = *cur_node->node.next;
    user = cur_node->user;
    bt_gatt_discover_free(cur_node);
    return user;
}

static bool bt_gatt_discover_user_is_register(bt_gatt_discover_user_t user)
{
    uint8_t i;
    bool flag = false;
    if(user == BT_GATT_DISCOVER_USER_SERVICE_NONE){
        return flag;
    }
    for(i = 0 ; i < BT_GATT_DISCOVERY_MAX_USER_NUM; i++){
        if(g_gatt_discover_register_service[i].user == user){
            if(g_gatt_discover_register_service[i].registered){
                flag = true;
                break;
            }
        }
    }
    return flag;
}

bt_gatt_discovery_status_t bt_gatt_discover_register_user(bt_gatt_discover_user_t user, bt_gatt_discover_complete_cb *callback)
{
    bt_gatt_discovery_status_t status = BT_GATT_DISCOVERY_STATUS_SUCCESS;
    if((user == BT_GATT_DISCOVER_USER_SERVICE_NONE) || (callback == NULL)){
        return BT_GATT_DISCOVERY_STATUS_INVALIDE_PARAMETER;
    }
    uint8_t user_idx = bt_gatt_discover_get_user_idx(user);
    if(user_idx == 0xFF){
        return BT_GATT_DISCOVERY_STATUS_FULL;
    }
    if(g_gatt_discover_register_service[user_idx].registered){
        return status;
    }
    g_gatt_discover_register_service[user_idx].registered = true;
    uint8_t link_idx = bt_gatt_discover_get_empty_link();
    if(link_idx == BT_GATT_DISCOVERY_MAX_LINK_NUM){
        return BT_GATT_DISCOVERY_STATUS_FULL;
    }
    uint8_t service_idx = bt_gatt_discover_get_empty_service(link_idx);
    if(service_idx == BT_GATT_DISCOVERY_MAX_USER_NUM){
        return BT_GATT_DISCOVERY_STATUS_FULL;
    }
    g_gatt_discover_context[link_idx].discover_service[service_idx].user_data.user = user;
    g_gatt_discover_context[link_idx].discover_service[service_idx].user_data.user_cb = *callback;
    return status;
}

bt_gatt_discovery_status_t bt_gatt_discover_start(struct bt_conn *conn, bt_gatt_discover_user_t user, struct bt_uuid *service_uuid)
{
    bt_gatt_discovery_status_t status = BT_GATT_DISCOVERY_STATUS_SUCCESS;
    if(conn == NULL || user == BT_GATT_DISCOVER_USER_SERVICE_NONE || service_uuid == NULL){
        return BT_GATT_DISCOVERY_STATUS_INVALIDE_PARAMETER;
    }
    if(!bt_gatt_discover_user_is_register(user)){
        return BT_GATT_DISCOVERY_STATUS_FAIL;
    }
    uint8_t link_idx = bt_gatt_discover_get_link_idx_by_conn(conn);
    if(link_idx == BT_GATT_DISCOVERY_MAX_LINK_NUM){
        return BT_GATT_DISCOVERY_STATUS_FULL;
    }
    uint8_t register_user_idx = bt_gatt_discover_get_register_user_idx(user);
    if(register_user_idx == 0xFF){
        return BT_GATT_DISCOVERY_STATUS_FULL;
    }
    if(bt_gatt_discover_add_user_tirggered(conn, user) != BT_GATT_DISCOVERY_STATUS_SUCCESS){
        return BT_GATT_DISCOVERY_STATUS_FAIL;
    }
    g_gatt_discover_register_service[register_user_idx].uuid = service_uuid;
    uint8_t service_idx = bt_gatt_discover_get_service_idx_by_user(link_idx, user);
    if(service_idx == BT_GATT_DISCOVERY_MAX_USER_NUM){
        return BT_GATT_DISCOVERY_STATUS_FULL;
    }
    bt_gatt_discover_service_t *service_addr = &g_gatt_discover_context[link_idx].discover_service[service_idx];
    bt_gatt_discover_set_state(service_addr, BT_GATT_DISCOVER_STATE_START);
    struct bt_gatt_discover_params *discover_params = (struct bt_gatt_discover_params *)bt_gatt_discover_malloc(sizeof(struct bt_gatt_discover_params));//when free
    if(!discover_params){
        return BT_GATT_DISCOVERY_STATUS_OUT_OF_MEMORY;
    }
    g_gatt_discover_context[link_idx].discover_params = discover_params;
    discover_params->func = bt_hogp_discover_cb;
    discover_params->uuid = service_uuid;
    discover_params->start_handle = 0x0001;
    discover_params->end_handle = 0xFFFF;
    discover_params->type = BT_GATT_DISCOVER_PRIMARY;

    bt_gatt_discover(conn, discover_params);
    return status;
}

void bt_gatt_discover_init(void)
{
    memset(&g_gatt_discover_register_service[0], 0, sizeof(bt_gatt_discover_register_t) * BT_GATT_DISCOVERY_MAX_USER_NUM);
    memset(&g_gatt_discover_context[0], 0, sizeof(bt_gatt_discover_t) * BT_GATT_DISCOVERY_MAX_LINK_NUM);
    static struct bt_conn_cb gatt_discover_conn_cb = {
        .disconnected = bt_gatt_discover_disconnect_cb,
    };
    bt_conn_cb_register(&gatt_discover_conn_cb);
    return;
}