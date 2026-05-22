
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

#include "app_dongle_cm.h"

#include "app_bt_service_common.h"
#include "app_bt_service_le_connection.h"

#include "app_dongle_cm_device_mgr.h"
#include "app_dongle_cm_le_scanner.h"
#include "app_dongle_cm_race_handler.h"

#include "app_debug.h"
#include "app_dongle_event.h"
#include "app_porting.h"


/**================================================================================*/
/**                              Definition & Structure                            */
/**================================================================================*/
#define LOG_TAG                             "[APP_DONGLE][CM]"

static void app_dongle_cm_link_context_update_and_handle_by_project(uint8_t link_type, bool is_connected);

#define APP_DONGLE_CM_INVALID_INDEX         (-1)

typedef enum {
    APP_DONGLE_CM_DISCONNECT_LINK_ALL,
    APP_DONGLE_CM_DISCONNECT_LINK_DISCONNECT,
    APP_DONGLE_CM_DISCONNECT_LINK_DISCONNECT_OHTER_KEEP,
} app_dongle_cm_disconnect_link_mode_t;
typedef struct {
    bool                                    used;
    uint8_t                                 link_type;
    uint8_t                                 device_type;
    uint8_t                                 addr_type;
    uint8_t                                 addr[BT_ADDR_SIZE];
    uint8_t                                 pre_state;
    uint8_t                                 cur_state;
    bool                                    is_active;
} PACKED app_dongle_cm_conn_info_t;

static app_dongle_cm_conn_info_t            app_dongle_cm_conn_list[APP_DONGLE_CM_MAX_CONN_NUM] = {0};

typedef struct {
    bool                                    used;
    uint8_t                                 link_type;
    bool                                    is_connected;
    uint8_t                                 reserved;
    app_dongle_cm_interface_t              *iface;
} PACKED app_dongle_cm_link_context_t;

static app_dongle_cm_link_context_t         app_dongle_cm_link_ctx[APP_DONGLE_CM_MAX_LINK_CONTEXT_NUM] = {0};



/**================================================================================*/
/**                            Internal API - Conn List                            */
/**================================================================================*/
static void app_dongle_cm_conn_list_print(void)
{
    for (int i = 0; i < APP_DONGLE_CM_MAX_CONN_NUM; i++) {
        if (app_dongle_cm_conn_list[i].used) {
            uint8_t *addr = app_dongle_cm_conn_list[i].addr;
            APPS_LOG_MSGID_I(LOG_TAG" print, [%d] link_type=%d addr=%d %08X%04X state=%d->%d is_active=%d",
                             8, i, app_dongle_cm_conn_list[i].link_type, app_dongle_cm_conn_list[i].addr_type,
                             *((uint32_t *)(addr + 2)), *((uint16_t *)addr), app_dongle_cm_conn_list[i].pre_state,
                             app_dongle_cm_conn_list[i].cur_state, app_dongle_cm_conn_list[i].is_active);
        }
    }
}

static int app_dongle_cm_conn_list_get_index_by_addr(uint8_t addr_type, uint8_t *addr)
{
    int index = APP_DONGLE_CM_INVALID_INDEX;
    if (!app_porting_bt_check_addr_valid(addr)) {
        return index;
    }

    for (int i = 0; i < APP_DONGLE_CM_MAX_CONN_NUM; i++) {
        if (app_dongle_cm_conn_list[i].used
            && app_dongle_cm_conn_list[i].addr_type == addr_type
            && memcmp(app_dongle_cm_conn_list[i].addr, addr, BT_ADDR_SIZE) == 0) {
            index = i;
            break;
        }
    }
    return index;
}

static bool app_dongle_cm_conn_list_is_exit_addr(uint8_t addr_type, uint8_t *addr)
{
    int index = app_dongle_cm_conn_list_get_index_by_addr(addr_type, addr);
    return (index >= 0);
}

static bool app_dongle_cm_conn_list_add_new_conn(uint8_t link_type, uint8_t device_type, uint8_t addr_type, uint8_t *addr)
{
    if (!app_porting_bt_check_addr_valid(addr)) {
        return FALSE;
    }

    app_dongle_cm_conn_list_print();
    APPS_LOG_MSGID_I(LOG_TAG" add_new_conn, link_type=%d device_type=%d addr=%d %08X%04X",
                     5, link_type, device_type, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr));

    bool success = FALSE;
    for (int i = 0; i < APP_DONGLE_CM_MAX_CONN_NUM; i++) {
        if (!app_dongle_cm_conn_list[i].used) {
            memset(&app_dongle_cm_conn_list[i], 0, sizeof(app_dongle_cm_conn_info_t));
            app_dongle_cm_conn_list[i].used = TRUE;
            app_dongle_cm_conn_list[i].link_type = link_type;
            app_dongle_cm_conn_list[i].device_type = device_type;
            app_dongle_cm_conn_list[i].addr_type = addr_type;
            memcpy(app_dongle_cm_conn_list[i].addr, addr, BT_ADDR_SIZE);
            app_dongle_cm_conn_list[i].pre_state = APP_DONGLE_CM_CONN_STATE_DISCONNECTED;
            app_dongle_cm_conn_list[i].cur_state = APP_DONGLE_CM_CONN_STATE_DISCONNECTED;
            success = TRUE;
            APPS_LOG_MSGID_I(LOG_TAG" add_new_conn, add success [%d]", 1, i);
            break;
        }
    }

    if (!success) {
        for (int i = 0; i < APP_DONGLE_CM_MAX_CONN_NUM; i++) {
            if (app_dongle_cm_conn_list[i].used
                && app_dongle_cm_conn_list[i].link_type == link_type
                && app_dongle_cm_conn_list[i].device_type == device_type
                && !app_dongle_cm_conn_list[i].is_active
                && (app_dongle_cm_conn_list[i].cur_state == APP_DONGLE_CM_CONN_STATE_DISCONNECTED || app_dongle_cm_conn_list[i].cur_state == APP_DONGLE_CM_CONN_STATE_DISCONNECTING)) {
                uint8_t old_addr[BT_ADDR_SIZE] = {0};
                memcpy(old_addr, app_dongle_cm_conn_list[i].addr, BT_ADDR_SIZE);
                APPS_LOG_MSGID_W(LOG_TAG" add_new_conn, change old [%d - addr=%08X%04X]", 3, i, *((uint32_t *)(old_addr + 2)), *((uint16_t *)old_addr));
                app_dongle_cm_conn_list[i].addr_type = addr_type;
                memcpy(app_dongle_cm_conn_list[i].addr, addr, BT_ADDR_SIZE);
                app_dongle_cm_conn_list[i].pre_state = APP_DONGLE_CM_CONN_STATE_DISCONNECTED;
                app_dongle_cm_conn_list[i].cur_state = APP_DONGLE_CM_CONN_STATE_DISCONNECTED;
                success = TRUE;
                break;
            }
        }
    }

    app_dongle_cm_conn_list_print();
    return success;
}

uint8_t *app_dongle_cm_conn_list_get_addr_by_index(int index)
{
    if (index < 0 || index >= APP_DONGLE_CM_MAX_CONN_NUM) {
        return NULL;
    }

    uint8_t *addr = NULL;
    for (int i = 0; i < APP_DONGLE_CM_MAX_CONN_NUM; i++) {
        if (app_dongle_cm_conn_list[i].used
            && app_porting_bt_check_addr_valid(app_dongle_cm_conn_list[i].addr)) {
            addr = app_dongle_cm_conn_list[i].addr;
            break;
        }
    }
    return addr;
}

static void app_dongle_cm_conn_list_init(void)
{
    memset(&app_dongle_cm_conn_list[0], 0, sizeof(app_dongle_cm_conn_info_t) * APP_DONGLE_CM_MAX_CONN_NUM);
}



/**================================================================================*/
/**                         Internal API - Link Context                            */
/**================================================================================*/
static app_dongle_cm_link_context_t *app_dongle_cm_link_context_get_context(uint8_t link_type)
{
    app_dongle_cm_link_context_t *link_ctx = NULL;
    for (int i = 0; i < APP_DONGLE_CM_MAX_LINK_CONTEXT_NUM; i++) {
        if (app_dongle_cm_link_ctx[i].used
            && app_dongle_cm_link_ctx[i].link_type == link_type) {
            link_ctx = &app_dongle_cm_link_ctx[i];
            break;
        }
    }
    return link_ctx;
}

app_dongle_cm_interface_t *app_dongle_cm_link_context_get_iface(uint8_t link_type)
{
    app_dongle_cm_interface_t *iface = NULL;
    app_dongle_cm_link_context_t *link_ctx = app_dongle_cm_link_context_get_context(link_type);
    if (link_ctx != NULL) {
        iface = link_ctx->iface;
    }
    return iface;
}

bool app_dongle_cm_link_context_is_connected_by_link_type(uint8_t link_type)
{
    bool is_connected = FALSE;
    for (int i = 0; i < APP_DONGLE_CM_MAX_CONN_NUM; i++) {
        if (app_dongle_cm_conn_list[i].used
            && app_dongle_cm_conn_list[i].link_type == link_type
            && app_dongle_cm_conn_list[i].cur_state == APP_DONGLE_CM_CONN_STATE_CONNECTED) {
            is_connected = TRUE;
            break;
        }
    }
    return is_connected;
}

static bool app_dongle_cm_start_connect_device(uint8_t link_type, uint8_t addr_type, uint8_t *addr)
{
    bool success = FALSE;
    app_dongle_cm_interface_t *iface = app_dongle_cm_link_context_get_iface(link_type);
    if (iface != NULL && iface->connect_if != NULL) {
        success = iface->connect_if(addr_type, addr);
        APPS_LOG_MSGID_I(LOG_TAG" start_connect_device, link_type=%d addr_type=%d addr=%08X%04X success=%d",
                         4, link_type, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), success);
    } else {
        APPS_LOG_MSGID_E(LOG_TAG" start_connect_device, not link_type=%d interface", 1, link_type);
    }
    return success;
}

static bool app_dongle_cm_start_disconnect_device(uint8_t link_type, uint8_t addr_type, uint8_t *addr)
{
    bool success = FALSE;
    app_dongle_cm_interface_t *iface = app_dongle_cm_link_context_get_iface(link_type);
    if (iface != NULL && iface->disconnect_if != NULL) {
        success = iface->disconnect_if(addr_type, addr);
        APPS_LOG_MSGID_I(LOG_TAG" start_disconnect_device, link_type=%d addr_type=%d addr=%08X%04X success=%d",
                         4, link_type, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), success);
    } else {
        APPS_LOG_MSGID_E(LOG_TAG" start_disconnect_device, not link_type=%d interface", 1, link_type);
    }
    return success;
}

static void app_dongle_cm_disconnect_device_by_link_type(app_dongle_cm_disconnect_link_mode_t disconnect_mode, uint8_t link_type)
{
    uint8_t disconnect_num = 0;
    for (int i = 0; i < APP_DONGLE_CM_MAX_CONN_NUM; i++) {
        uint8_t addr_type = app_dongle_cm_conn_list[i].addr_type;
        uint8_t *addr = app_dongle_cm_conn_list[i].addr;
        bool need_disconnect = FALSE;
        if (app_dongle_cm_conn_list[i].used && app_porting_bt_check_addr_valid(addr)) {
            if (disconnect_mode == APP_DONGLE_CM_DISCONNECT_LINK_ALL) {
                need_disconnect = TRUE;
            } else if (disconnect_mode == APP_DONGLE_CM_DISCONNECT_LINK_DISCONNECT
                       && app_dongle_cm_conn_list[i].link_type == link_type) {
                need_disconnect = TRUE;
            } else if (disconnect_mode == APP_DONGLE_CM_DISCONNECT_LINK_DISCONNECT_OHTER_KEEP
                       && app_dongle_cm_conn_list[i].link_type != link_type) {
                need_disconnect = TRUE;
            }

            if (need_disconnect) {
                bool success = app_dongle_cm_start_disconnect_device(app_dongle_cm_conn_list[i].link_type, addr_type, addr);
                if (success) {
                    disconnect_num++;
                }
            }
        }
    }

    APPS_LOG_MSGID_W(LOG_TAG" disconnect_device_by_link_type, mode=%d link_type=%d num=%d", 3, disconnect_mode, link_type, disconnect_num);
}

static void app_dongle_cm_link_context_update_connected_state(uint8_t link_type)
{
    app_dongle_cm_link_context_t *link_ctx = app_dongle_cm_link_context_get_context(link_type);
    bool is_connected = app_dongle_cm_link_context_is_connected_by_link_type(link_type);
    bool old_is_connected = link_ctx->is_connected;
    app_dongle_cm_conn_list_print();
    APPS_LOG_MSGID_I(LOG_TAG" update_connected_state, link_type=%d is_connected=%d->%d",
                     3, link_type, old_is_connected, is_connected);

    if (old_is_connected != is_connected) {
        link_ctx->is_connected = is_connected;
        app_dongle_cm_link_context_update_and_handle_by_project(link_type, is_connected);
    }
}

static void app_dongle_cm_link_context_init(void)
{
    memset(&app_dongle_cm_link_ctx[0], 0, sizeof(app_dongle_cm_link_context_t) * APP_DONGLE_CM_MAX_LINK_CONTEXT_NUM);
}



/**================================================================================*/
/**                        Handle Source Change by Project                         */
/**================================================================================*/
static void app_dongle_cm_link_context_update_and_handle_by_project(uint8_t link_type, bool is_connected)
{
    // By project, scenario
#ifdef APP_DONGLE_CM_FEATURE_MODE_LE_OFFICE_DONGLE
    if (is_connected) {
        app_dongle_cm_disconnect_device_by_link_type(APP_DONGLE_CM_DISCONNECT_LINK_DISCONNECT_OHTER_KEEP, APP_DONGLE_CM_LINK_TYPE_LE_HOGP);
    } else {
        // ToDo, restart all valid source
    }
#endif
}



/**================================================================================*/
/**                            Connection State Machine                            */
/**================================================================================*/
typedef void (*app_dongle_cm_conn_exit_action_t)(uint8_t index, uint8_t cur_state, uint8_t event);
typedef void (*app_dongle_cm_conn_do_action_t)(uint8_t index, uint8_t pre_state, uint8_t event);

typedef struct {
    app_dongle_cm_conn_state_t                                  cur_state;
    app_dongle_cm_conn_event_t                                  event;
    app_dongle_cm_conn_state_t                                  next_state;
    app_dongle_cm_conn_exit_action_t                            exit_action;
    app_dongle_cm_conn_do_action_t                              do_action;
} app_dongle_cm_conn_transform_t;

static void app_dongle_cm_state_disconnected_do_action(uint8_t index, uint8_t pre_state, uint8_t event);
static void app_dongle_cm_state_connecting_do_action(uint8_t index, uint8_t pre_state, uint8_t event);
static void app_dongle_cm_state_connected_do_action(uint8_t index, uint8_t pre_state, uint8_t event);
static void app_dongle_cm_state_bonded_do_action(uint8_t index, uint8_t pre_state, uint8_t event);
static void app_dongle_cm_state_disconnecting_do_action(uint8_t index, uint8_t pre_state, uint8_t event);

static app_dongle_cm_conn_transform_t       app_dongle_cm_conn_transform_table[] = {
    {APP_DONGLE_CM_CONN_STATE_DISCONNECTED,   APP_DONGLE_CM_CONN_EVENT_REQUEST_CONNECT,    APP_DONGLE_CM_CONN_STATE_CONNECTING,    NULL, app_dongle_cm_state_connecting_do_action},
    {APP_DONGLE_CM_CONN_STATE_DISCONNECTED,   APP_DONGLE_CM_CONN_EVENT_CONNECTED,          APP_DONGLE_CM_CONN_STATE_CONNECTED,     NULL, app_dongle_cm_state_connected_do_action},

    {APP_DONGLE_CM_CONN_STATE_CONNECTING,     APP_DONGLE_CM_CONN_EVENT_CONNECTED,          APP_DONGLE_CM_CONN_STATE_CONNECTED,     NULL, app_dongle_cm_state_connected_do_action},
    {APP_DONGLE_CM_CONN_STATE_CONNECTED,     APP_DONGLE_CM_CONN_EVENT_BONDED,          APP_DONGLE_CM_CONN_STATE_BONDED,     NULL, app_dongle_cm_state_bonded_do_action},

    {APP_DONGLE_CM_CONN_STATE_CONNECTED,      APP_DONGLE_CM_CONN_EVENT_LINK_LOST,          APP_DONGLE_CM_CONN_STATE_DISCONNECTED,  NULL, app_dongle_cm_state_disconnected_do_action},
    {APP_DONGLE_CM_CONN_STATE_CONNECTED,      APP_DONGLE_CM_CONN_EVENT_DISCONNECTED,       APP_DONGLE_CM_CONN_STATE_DISCONNECTED,  NULL, app_dongle_cm_state_disconnected_do_action},
    {APP_DONGLE_CM_CONN_STATE_BONDED,      APP_DONGLE_CM_CONN_EVENT_LINK_LOST,          APP_DONGLE_CM_CONN_STATE_DISCONNECTED,  NULL, app_dongle_cm_state_disconnected_do_action},
    {APP_DONGLE_CM_CONN_STATE_BONDED,      APP_DONGLE_CM_CONN_EVENT_DISCONNECTED,       APP_DONGLE_CM_CONN_STATE_DISCONNECTED,  NULL, app_dongle_cm_state_disconnected_do_action},

    {APP_DONGLE_CM_CONN_STATE_CONNECTED,      APP_DONGLE_CM_CONN_EVENT_REQUEST_DISCONNECT, APP_DONGLE_CM_CONN_STATE_DISCONNECTING, NULL, app_dongle_cm_state_disconnecting_do_action},
    {APP_DONGLE_CM_CONN_STATE_DISCONNECTING,  APP_DONGLE_CM_CONN_EVENT_DISCONNECTED,       APP_DONGLE_CM_CONN_STATE_DISCONNECTED,  NULL, app_dongle_cm_state_disconnected_do_action},
};

#define APP_DONGLE_CM_TRANSFORM_TABLE_SIZE  (sizeof(app_dongle_cm_conn_transform_table) / sizeof(app_dongle_cm_conn_transform_t))

static void app_bt_source_conn_mgr_state_machine_run(uint8_t addr_type, uint8_t *addr, uint8_t event)
{
    APPS_LOG_MSGID_I(LOG_TAG" state_machine_run, addr_type=%d addr=%08X%04X event=%d",
                     4, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), event);
    app_dongle_cm_conn_list_print();

    int index = app_dongle_cm_conn_list_get_index_by_addr(addr_type, addr);
    if (index < 0 || index >= APP_DONGLE_CM_MAX_CONN_NUM) {
        APPS_LOG_MSGID_E(LOG_TAG" state_machine_run, [%d] invalid index=%d", 1, index);
        return;
    }

    app_dongle_cm_conn_transform_t *transform = NULL;
    app_dongle_cm_conn_state_t state = app_dongle_cm_conn_list[index].cur_state;
    for (int i = 0; i < APP_DONGLE_CM_TRANSFORM_TABLE_SIZE; i++) {
        app_dongle_cm_conn_transform_t *temp = &app_dongle_cm_conn_transform_table[i];
        if (temp->cur_state == state && temp->event == event) {
            transform = temp;
            break;
        }
    }

    if (transform == NULL) {
        APPS_LOG_MSGID_E(LOG_TAG" state_machine_run, [%d] invalid state=%d event=%d", 3, index, state, event);
        return;
    }

    app_dongle_cm_conn_state_t next_state = transform->next_state;
    APPS_LOG_MSGID_I(LOG_TAG" state_machine_run, [%d] state=%d->%d event=%d exit_action=0x%08X do_action=0x%08X",
                     6, index, state, next_state, event, transform->exit_action, transform->do_action);
    if (transform->exit_action != NULL) {
        transform->exit_action(index, transform->cur_state, event);
    }
    app_dongle_cm_conn_list[index].pre_state = app_dongle_cm_conn_list[index].cur_state;
    app_dongle_cm_conn_list[index].cur_state = next_state;
    if (transform->do_action != NULL) {
        transform->do_action(index, app_dongle_cm_conn_list[index].pre_state, event);
    }
}

static void app_dongle_cm_state_disconnected_do_action(uint8_t index, uint8_t pre_state, uint8_t event)
{
    uint8_t link_type = app_dongle_cm_conn_list[index].link_type;
    uint8_t addr_type = app_dongle_cm_conn_list[index].addr_type;
    uint8_t *addr = app_dongle_cm_conn_list[index].addr;
    APPS_LOG_MSGID_W(LOG_TAG" state_machine_run, DISCONNECTED [%d] link_type=%d addr=%d %08X%04X pre_state=%d event=%d",
                     7, index, link_type, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), pre_state, event);

    app_dongle_cm_link_context_update_connected_state(link_type);

    if (event == APP_DONGLE_CM_CONN_EVENT_LINK_LOST) {
        APPS_LOG_MSGID_W(LOG_TAG" state_machine_run, LINK_LOST reconnect", 0);
        app_dongle_cm_start_connect_device(link_type, addr_type, addr);
    }
}

static void app_dongle_cm_state_connecting_do_action(uint8_t index, uint8_t pre_state, uint8_t event)
{
    uint8_t link_type = app_dongle_cm_conn_list[index].link_type;
    uint8_t addr_type = app_dongle_cm_conn_list[index].addr_type;
    uint8_t *addr = app_dongle_cm_conn_list[index].addr;
    APPS_LOG_MSGID_W(LOG_TAG" state_machine_run, CONNECTING [%d] link_type=%d addr=%d %08X%04X pre_state=%d event=%d",
                     7, index, link_type, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), pre_state, event);
}

static void app_dongle_cm_state_connected_do_action(uint8_t index, uint8_t pre_state, uint8_t event)
{
    uint8_t link_type = app_dongle_cm_conn_list[index].link_type;
    uint8_t addr_type = app_dongle_cm_conn_list[index].addr_type;
    uint8_t *addr = app_dongle_cm_conn_list[index].addr;
    APPS_LOG_MSGID_W(LOG_TAG" state_machine_run, CONNECTED [%d] link_type=%d addr=%d %08X%04X pre_state=%d event=%d",
                     7, index, link_type, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), pre_state, event);

    app_dongle_cm_link_context_update_connected_state(link_type);
}

static void app_dongle_cm_state_bonded_do_action(uint8_t index, uint8_t pre_state, uint8_t event)
{
    uint8_t link_type = app_dongle_cm_conn_list[index].link_type;
    uint8_t device_type = app_dongle_cm_conn_list[index].device_type;
    uint8_t addr_type = app_dongle_cm_conn_list[index].addr_type;
    uint8_t *addr = app_dongle_cm_conn_list[index].addr;
    APPS_LOG_MSGID_W(LOG_TAG" state_machine_run, BONDED [%d] link_type=%d device_type=%d addr=%d %08X%04X pre_state=%d event=%d",
                     8, index, link_type, device_type, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), pre_state, event);

    app_dongle_cm_device_mgr_add(addr_type, addr, link_type, device_type);
    // ToDo, random addr -> IDA update
}

static void app_dongle_cm_state_disconnecting_do_action(uint8_t index, uint8_t pre_state, uint8_t event)
{
    uint8_t link_type = app_dongle_cm_conn_list[index].link_type;
    uint8_t addr_type = app_dongle_cm_conn_list[index].addr_type;
    uint8_t *addr = app_dongle_cm_conn_list[index].addr;
    APPS_LOG_MSGID_W(LOG_TAG" state_machine_run, DISCONNECTING [%d] link_type=%d addr=%d %08X%04X pre_state=%d event=%d",
                     7, index, link_type, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), pre_state, event);
}



/**================================================================================*/
/**                                  Event Handler                                 */
/**================================================================================*/
static void app_dongle_cm_handle_bt_power_on(void)
{
    //APPS_LOG_MSGID_I(LOG_TAG" handle_bt_power_on", 0);
#ifdef APP_DONGLE_CM_FEATURE_MODE_LE_OFFICE_DONGLE
    // Only LE HOGP link, trigger power on reconnect
    uint8_t le_hogp_device_num = app_dongle_cm_device_mgr_get_num_by_link_type(APP_DONGLE_CM_LINK_TYPE_LE_HOGP);
    app_dongle_cm_interface_t *iface = app_dongle_cm_link_context_get_iface(APP_DONGLE_CM_LINK_TYPE_LE_HOGP);
    if (le_hogp_device_num > 0 && iface != NULL && iface->connect_all_if != NULL) {
        iface->connect_all_if();
    }
    if (iface != NULL && iface->scan_if != NULL) {
        // Always start scan to wait KB/MS found, connect, and switching
        iface->scan_if(TRUE);
    }
#endif
}

static bool app_dongle_cm_handle_bt_event(uint16_t event_id, void *data, uint32_t data_len)
{
    if (event_id == APP_DONGLE_EVENT_BT_ON) {
        app_dongle_cm_handle_bt_power_on();
    }
    return FALSE;
}

static bool app_dongle_cm_handle_usb_event(uint16_t event_id, void *data, uint32_t data_len)
{
    return FALSE;
}

bool app_dongle_cm_event_handler(uint8_t event_group, uint16_t event_id, void *data, uint32_t data_len)
{
    switch (event_group) {
        case APP_DONGLE_EVENT_GROUP_BT: {
            app_dongle_cm_handle_bt_event(event_id, data, data_len);
            break;
        }

        case APP_DONGLE_EVENT_GROUP_USB: {
            app_dongle_cm_handle_usb_event(event_id, data, data_len);
            break;
        }
    }
    return FALSE;
}



/**================================================================================*/
/**                                     Public API                                 */
/**================================================================================*/
void app_dongle_cm_init(void)
{
    app_bt_service_common_init();

    app_dongle_cm_conn_list_init();
    app_dongle_cm_link_context_init();

    app_dongle_cm_device_mgr_init();
    app_dongle_cm_le_scanner_init();
}

void app_dongle_cm_notify_conn_event(uint8_t link_type, app_dongle_cm_conn_event_t event, uint8_t addr_type, uint8_t *addr)
{
    bool is_exist = app_dongle_cm_conn_list_is_exit_addr(addr_type, addr);
    if (!is_exist) {
        uint8_t device_type = app_dongle_cm_device_mgr_get_device_type(addr_type, addr);
        APPS_LOG_MSGID_W(LOG_TAG" notify_conn_event, not exist the addr=%08X%04X device_type=%d",
                         3, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), device_type);
        app_dongle_cm_conn_list_add_new_conn(link_type, device_type, addr_type, addr);
    }

    APPS_LOG_MSGID_I(LOG_TAG" notify_conn_event, link_type=%d event=%d addr_type=%d addr=%08X%04X",
                     5, link_type, event, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr));
    app_bt_source_conn_mgr_state_machine_run(addr_type, addr, event);
}

bool app_dongle_cm_add_found_addr(uint8_t link_type, uint8_t device_type, uint8_t addr_type, uint8_t *addr, bool connect)
{
    bool success = FALSE;
    bool is_exist = app_dongle_cm_conn_list_is_exit_addr(addr_type, addr);
    if (is_exist) {
        APPS_LOG_MSGID_W(LOG_TAG" add_found_addr, already exist the addr", 0);
        int index = app_dongle_cm_conn_list_get_index_by_addr(addr_type, addr);
        if (index != APP_DONGLE_CM_INVALID_INDEX) {
            app_dongle_cm_conn_info_t *conn_info = &app_dongle_cm_conn_list[index];
            if (conn_info->cur_state == APP_DONGLE_CM_CONN_STATE_DISCONNECTED && connect) {
                APPS_LOG_MSGID_W(LOG_TAG" add_found_addr, start connect the addr", 0);
                app_dongle_cm_start_connect_device(link_type, addr_type, addr);
            }
        }
        success = TRUE;
    } else {
        success = app_dongle_cm_conn_list_add_new_conn(link_type, device_type, addr_type, addr);
        if (success && connect) {
            success = app_dongle_cm_start_connect_device(link_type, addr_type, addr);
        }
    }

    APPS_LOG_MSGID_I(LOG_TAG" add_found_addr, link_type=%d device_type=%d addr_type=%d addr=%08X%04X connect=%d success=%d",
                     7, link_type, device_type, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), connect, success);
    return success;
}

void app_dongle_cm_register_link_interface(uint8_t link_type, app_dongle_cm_interface_t *interface)
{
#ifdef APP_DONGLE_CM_FEATURE_MODE_LE_OFFICE_DONGLE
    assert(link_type == APP_DONGLE_CM_LINK_TYPE_LE_HOGP);
#endif

    assert(link_type > APP_DONGLE_CM_LINK_TYPE_NONE && link_type < APP_DONGLE_CM_LINK_TYPE_MAX);
    assert(interface != NULL);

    for (int i = 0; i < APP_DONGLE_CM_MAX_LINK_CONTEXT_NUM; i++) {
        if (!app_dongle_cm_link_ctx[i].used) {
            app_dongle_cm_link_ctx[i].used = TRUE;
            app_dongle_cm_link_ctx[i].link_type = link_type;
            app_dongle_cm_link_ctx[i].iface = interface;
            app_dongle_cm_link_ctx[i].is_connected = FALSE;
        }
    }
}