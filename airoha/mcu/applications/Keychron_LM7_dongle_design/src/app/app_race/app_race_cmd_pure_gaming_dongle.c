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
#include "assert.h"
#include "race_cmd.h"
#include "race_xport.h"
#include "app_race_cmd_event.h"
#include "app_race_cmd_pure_gaming_dongle.h"
#include "app_events.h"
#include "af_events_declaration.h"
#include "app_pure_gaming_dongle_scenario.h"
#include "app_bt_conn_manager.h"
#include"bt_ull_le_hid_device_manager.h"

/* Private define ------------------------------------------------------------*/
#define thisMODULE app_race_cmd
#define thisMOD    "app_race_cmd"
LOG_MODULE_DECLARE(thisMODULE);

#define APP_DONGLE_HID_MS_NAME        "Hid_Mouse"
#define APP_DONGLE_HID_MS_NAME_LEN    (strlen(APP_DONGLE_HID_MS_NAME))

#define APP_DONGLE_HID_KB_NAME        "Hid_Keyboard"
#define APP_DONGLE_HID_KB_NAME_LEN    (strlen(APP_DONGLE_HID_KB_NAME))

#define APP_DONGLE_HID_HS_NAME        "Hid_Headset"
#define APP_DONGLE_HID_HS_NAME_LEN    (strlen(APP_DONGLE_HID_HS_NAME))

#define APP_DONGLE_HID_EB_NAME        "Hid_Earbuds"
#define APP_DONGLE_HID_EB_NAME_LEN    (strlen(APP_DONGLE_HID_EB_NAME))

#define APP_DONGLE_HID_GP_NAME        "Hid_Gamepad"
#define APP_DONGLE_HID_GP_NAME_LEN    (strlen(APP_DONGLE_HID_GP_NAME))

/* Private typedef -----------------------------------------------------------*/
typedef struct {
    uint8_t start_scan;
    uint16_t timeout_seconds;
} PACKED app_dongle_le_race_scan_cmd_t;

typedef struct {
    uint8_t connect;
    uint8_t addr[7];
} PACKED app_dongle_le_race_connect_cmd_t;

typedef struct {
    uint8_t type;
} PACKED app_dongle_le_race_link_type_cmd_t;

typedef struct {
    uint8_t addr[7];
    uint8_t device_id;
    uint8_t group_id;
    uint8_t role;
} PACKED app_dongle_le_race_paired_info_t;

/* Private macro -------------------------------------------------------------*/
#define CONVERT_RACE_DEVICE_TYPE(type)                        \
    ((type) == 0x00 ? BT_ULL_LE_HID_SRV_DEVICE_NONE :    \
    (type) == 0x04 ? BT_ULL_LE_HID_SRV_DEVICE_HEADSET :  \
    (type) == 0x05 ? BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD : \
    (type) == 0x06 ? BT_ULL_LE_HID_SRV_DEVICE_MOUSE :    \
    (type) == 0x07 ? BT_ULL_LE_HID_SRV_DEVICE_EARBUDS :  \
    (type) == 0x0A ? BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD :  \
                    BT_ULL_LE_HID_SRV_DEVICE_NONE)

/* Private variables ---------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void *app_race_pg_dongle_scan(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        app_dongle_le_race_scan_cmd_t scan_cmd;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    CMD *pCmd = (CMD *)pCmdMsg;
    if (pCmd->scan_cmd.start_scan)
    {
        /* disconnect link */
        app_pg_scenario_handle_t *scenario_handle;
        app_bt_conn_status_t link_status = APP_BT_CONN_STATUS_UNKNOWN;
        scenario_handle = app_pure_gaming_dongle_scenario_get_current_context();
        if (scenario_handle->link_handle != NULL)
        {
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_GET_ULL_LINK_STATUS, &link_status);
            if (link_status > APP_BT_CONN_STATUS_DISCONNECTED)
            {
                app_events_send(EVT_CMD_DISCONNECT_REQ, scenario_handle);
            }
        }
        /* start scan */
        app_events_send(EVT_CMD_ACL_SCAN_START_REQ, (void *)((uint32_t)(pCmd->scan_cmd.timeout_seconds*1000)));
    }
    else
    {
        /* stop scan */
        app_events_send(EVT_CMD_ACL_SCAN_STOP_REQ, NULL);
    }

    /* send response */
    RSP *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                 pCmd->cmdhdr.id,
                                 sizeof(RSP),
                                 cid);
    if (pRsp == NULL) {
        LOG_ERR("app_race_pg_dongle_scan RACE_ClaimPacketAppID fail");
        return NULL;
    }
    pRsp->status = 0;
    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    LOG_INF("app_race_pg_dongle_scan start_scan %u, time %u", pCmd->scan_cmd.start_scan, pCmd->scan_cmd.timeout_seconds);

    return NULL;
}

static void *app_race_pg_dongle_connect(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        app_dongle_le_race_connect_cmd_t connect_cmd;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
        app_dongle_le_race_connect_cmd_t connect_cmd;
    } PACKED RSP;

    app_bt_conn_device_found_t *dev_found;
    app_bt_conn_handle_t *link_handle;
    app_pg_scenario_handle_t *scenario_handle;
    int32_t race_ret = RACE_ERRCODE_FAIL;

    CMD *pCmd = (CMD *)pCmdMsg;
    dev_found = (app_bt_conn_device_found_t *)app_bt_conn_manager_malloc(sizeof(app_bt_conn_device_found_t));
#if defined(AIR_PURE_GAMING_DONGLE_MS_ENABLE)
    dev_found->role = APP_BT_CONN_ROLE_MOUSE;
#elif defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
    dev_found->role = APP_BT_CONN_ROLE_GAMEPAD;
#else
    dev_found->role = APP_BT_CONN_ROLE_KEYBOARD;
#endif /* AIR_PURE_GAMING_DONGLE_MS_ENABLE */
    memcpy(&(dev_found->addr), &(pCmd->connect_cmd.addr[0]), sizeof(bt_addr_le_t));
    if (pCmd->connect_cmd.connect)
    {
        app_events_send(EVT_CMD_ACL_PAIR_REQ, dev_found);
    }
    else
    {
        link_handle = app_bt_conn_manager_query_handle_by_addr(APP_BT_CONN_TYPE_ULL, &(dev_found->addr));
        assert(link_handle != NULL);
        scenario_handle = app_bt_conn_manager_get_scenario_handle(link_handle);
        assert(scenario_handle != NULL);
        app_events_send(EVT_CMD_DISCONNECT_REQ, scenario_handle);
    }

    /* send response */
    RSP *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                 pCmd->cmdhdr.id,
                                 sizeof(RSP),
                                 cid);
    if (pRsp == NULL) {
        LOG_ERR("app_race_pg_dongle_scan RACE_ClaimPacketAppID fail");
        return NULL;
    }
    pRsp->status = 0;
    pRsp->connect_cmd.connect = pCmd->connect_cmd.connect;
    memcpy(&(pRsp->connect_cmd.addr[0]), &(pCmd->connect_cmd.addr[0]), sizeof(bt_addr_le_t));
    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    LOG_INF("app_race_pg_dongle_connect operation %u, address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x:0x%x",
            pCmd->connect_cmd.connect,
            pCmd->connect_cmd.addr[6],
            pCmd->connect_cmd.addr[5],
            pCmd->connect_cmd.addr[4],
            pCmd->connect_cmd.addr[3],
            pCmd->connect_cmd.addr[2],
            pCmd->connect_cmd.addr[1],
            pCmd->connect_cmd.addr[0]);

    return NULL;
}

static void *app_race_pg_dongle_set_link_type(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        app_dongle_le_race_link_type_cmd_t type_cmd;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
        app_dongle_le_race_link_type_cmd_t type_cmd;
    } PACKED RSP;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    CMD *pCmd = (CMD *)pCmdMsg;

    if (pCmd->type_cmd.type == 0x6)
    {
        app_pure_gaming_dongle_scenario_set_current_context(APP_BT_CONN_ROLE_MOUSE);
    }
    else if (pCmd->type_cmd.type == 0x5)
    {
        app_pure_gaming_dongle_scenario_set_current_context(APP_BT_CONN_ROLE_KEYBOARD);
    }
    else if (pCmd->type_cmd.type == 0x4)
    {
        app_pure_gaming_dongle_scenario_set_current_context(APP_BT_CONN_ROLE_HEADSET);
    }
    else if (pCmd->type_cmd.type == 0xA)
    {
        app_pure_gaming_dongle_scenario_set_current_context(APP_BT_CONN_ROLE_GAMEPAD);
    }
    else
    {
        LOG_INF("app_race_pg_dongle_set_link_type 0x%x not supported", pCmd->type_cmd.type);
    }

    /* send response */
    RSP *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                 pCmd->cmdhdr.id,
                                 sizeof(RSP),
                                 cid);
    if (pRsp == NULL) {
        LOG_ERR("app_race_pg_dongle_scan RACE_ClaimPacketAppID fail");
        return NULL;
    }
    pRsp->status = 0;
    pRsp->type_cmd.type = pCmd->type_cmd.type;
    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    LOG_INF("app_race_pg_dongle_set_link_type 0x%x", pCmd->type_cmd.type);

    return NULL;
}

static void *app_race_pg_dongle_get_link_type(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
        app_dongle_le_race_link_type_cmd_t type_cmd;
    } PACKED RSP;

    int32_t race_ret = RACE_ERRCODE_FAIL;
    app_pg_scenario_handle_t *scenario_handle;
    app_bt_conn_role_t role;

    CMD *pCmd = (CMD *)pCmdMsg;

    /* send response */
    RSP *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                 pCmd->cmdhdr.id,
                                 sizeof(RSP),
                                 cid);
    if (pRsp == NULL) {
        LOG_ERR("app_race_pg_dongle_scan RACE_ClaimPacketAppID fail");
        return NULL;
    }
    pRsp->status = 0;
    scenario_handle = app_pure_gaming_dongle_scenario_get_current_context();
    role = app_pure_gaming_dongle_scenario_get_role_by_handle(scenario_handle);
    if (role == APP_BT_CONN_ROLE_HEADSET)
    {
        pRsp->type_cmd.type = 0x4;
    }
    else if (role == APP_BT_CONN_ROLE_KEYBOARD)
    {
        pRsp->type_cmd.type = 0x5;
    }
    else if (role == APP_BT_CONN_ROLE_MOUSE)
    {
        pRsp->type_cmd.type = 0x6;
    }
    else if (role == APP_BT_CONN_ROLE_GAMEPAD)
    {
        pRsp->type_cmd.type = 0xA;
    }
    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    LOG_INF("app_race_pg_dongle_get_link_type 0x%x", pRsp->type_cmd.type);

    return NULL;
}

static void *app_race_pg_dongle_get_paired_list(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
        app_dongle_le_race_paired_info_t pair_list[0];
    } PACKED RSP;

    app_pg_scenario_handle_t *scenario_handle;
    app_pg_scenario_paired_list_param_t paired_list_param;
    int32_t race_ret = RACE_ERRCODE_FAIL;
    app_bt_conn_role_t role;
    uint32_t i;

    CMD *pCmd = (CMD *)pCmdMsg;

    /* get pair list */
    scenario_handle = app_pure_gaming_dongle_scenario_get_current_context();
    role = app_pure_gaming_dongle_scenario_get_role_by_handle(scenario_handle);
    app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_GET_BONDED_DEVICE_NUM, &(paired_list_param.dev_cnt));
    assert(paired_list_param.dev_cnt < 2);
    if (paired_list_param.dev_cnt != 0)
    {
        paired_list_param.list = app_bt_conn_manager_malloc(sizeof(bt_addr_le_t) * paired_list_param.dev_cnt);
        app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_GET_PAIRED_DEVICE_LIST, &paired_list_param);
    }
    /* send response */
    RSP *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                 pCmd->cmdhdr.id,
                                 sizeof(RSP) + paired_list_param.dev_cnt * sizeof(app_dongle_le_race_paired_info_t),
                                 cid);
    if (pRsp == NULL) {
        LOG_ERR("app_race_pg_dongle_scan RACE_ClaimPacketAppID fail");
        return NULL;
    }
    pRsp->status = 0;
    if (paired_list_param.dev_cnt != 0)
    {
        for (i = 0; i < paired_list_param.dev_cnt; i++)
        {
            memcpy(&(pRsp->pair_list[i].addr), &(paired_list_param.list[i]), sizeof(bt_addr_le_t));
            pRsp->pair_list[i].device_id = 0x80+i+1;
            pRsp->pair_list[i].group_id = 0x01;
            pRsp->pair_list[i].role = role;
        }
        app_bt_conn_manager_free(paired_list_param.list);
    }
    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    LOG_INF("app_race_pg_dongle_get_paired_list dev cnt %u", paired_list_param.dev_cnt);

    return NULL;
}

static void *app_race_pg_dongle_remove_paired_record(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t addr[7];
    } PACKED CMD;

    typedef struct {
        uint8_t status;
        uint8_t addr[7];
    } PACKED RSP;

    app_pg_scenario_handle_t *scenario_handle;
    int32_t race_ret = RACE_ERRCODE_FAIL;
    app_bt_conn_status_t link_status = APP_BT_CONN_STATUS_UNKNOWN;
    uint8_t status = 0;
    bt_addr_le_t addr;
    bool find_dev = false;

    CMD *pCmd = (CMD *)pCmdMsg;

    scenario_handle = app_pure_gaming_dongle_scenario_get_current_context();
    if (scenario_handle->link_handle != NULL)
    {
        app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_GET_ULL_LINK_STATUS, &link_status);
        if ((link_status == APP_BT_CONN_STATUS_DISCONNECTED)
            || (link_status == APP_BT_CONN_STATUS_BONDED)
            || (link_status == APP_BT_CONN_STATUS_CONNCETING))
        {
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_GET_ULL_LINK_ADDR, &addr);
            if (memcmp(&addr, &(pCmd->addr), 7) == 0)
            {
                find_dev = true;
            }
        }
    }

    if (find_dev)
    {
        if ((link_status == APP_BT_CONN_STATUS_BONDED)
            || (link_status == APP_BT_CONN_STATUS_CONNCETING))
        {
            app_events_send(EVT_CMD_RECONNECT_CANCEL_REQ, scenario_handle);
        }
        app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_BT_REMOVE_ULL_LINK_RECORD, &addr);
    }
    else
    {
        LOG_ERR("app_race_pg_dongle_remove_paired_record device is not found");
        // assert(0);
    }

    /* send response */
    RSP *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                 pCmd->cmdhdr.id,
                                 sizeof(RSP),
                                 cid);
    if (pRsp == NULL) {
        LOG_ERR("app_race_pg_dongle_scan RACE_ClaimPacketAppID fail");
        return NULL;
    }
    pRsp->status = status;
    memcpy(&(pRsp->addr), &(pCmd->addr), 7);
    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    LOG_INF("app_race_pg_dongle_remove_paired_record status %u, address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x",
            pRsp->status,
            pCmd->addr[5],
            pCmd->addr[4],
            pCmd->addr[3],
            pCmd->addr[2],
            pCmd->addr[1],
            pCmd->addr[0]);

    return NULL;
}

static void *app_race_pg_dongle_get_device_list(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
        app_dongle_le_race_paired_info_t pair_list[0];
    } PACKED RSP;

    app_pg_scenario_handle_t *scenario_handle;
    int32_t race_ret = RACE_ERRCODE_FAIL;
    uint8_t dev_cnt = 0;
    app_bt_conn_role_t role;
    app_bt_conn_status_t link_status = APP_BT_CONN_STATUS_UNKNOWN;

    CMD *pCmd = (CMD *)pCmdMsg;

    /* get device list */
    scenario_handle = app_pure_gaming_dongle_scenario_get_current_context();
    role = app_pure_gaming_dongle_scenario_get_role_by_handle(scenario_handle);
    if (scenario_handle->link_handle != NULL)
    {
        app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_GET_ULL_LINK_STATUS, &link_status);
    }
    if (link_status > APP_BT_CONN_STATUS_CONNCETING)
    {
        dev_cnt = 1;
    }
    /* send response */
    RSP *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                 pCmd->cmdhdr.id,
                                 sizeof(RSP) + dev_cnt * sizeof(app_dongle_le_race_paired_info_t),
                                 cid);
    if (pRsp == NULL) {
        LOG_ERR("app_race_pg_dongle_scan RACE_ClaimPacketAppID fail");
        return NULL;
    }
    pRsp->status = 0;
    if (dev_cnt != 0)
    {
        memcpy(&(pRsp->pair_list[0].addr), &(scenario_handle->link_handle->ull_addr), sizeof(bt_addr_le_t));
        pRsp->pair_list[0].device_id = 0x80;
        pRsp->pair_list[0].group_id = 0x01;
        pRsp->pair_list[0].role = role;
    }
    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    LOG_INF("app_race_pg_dongle_get_device_list dev cnt %u", dev_cnt);

    return NULL;
}

static void *app_race_pg_dongle_get_device_name(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t addr[7];
    } PACKED CMD;

    typedef struct {
        uint8_t status;
        uint8_t addr[7];
        uint8_t name[0];
    } PACKED RSP;

    app_pg_scenario_handle_t *scenario_handle;
    int32_t race_ret = RACE_ERRCODE_FAIL;
    app_bt_conn_role_t role;
    uint32_t name_len = 0;

    CMD *pCmd = (CMD *)pCmdMsg;

    /* get role */
    scenario_handle = app_pure_gaming_dongle_scenario_get_current_context();
    role = app_pure_gaming_dongle_scenario_get_role_by_handle(scenario_handle);
    if (role == APP_BT_CONN_ROLE_HEADSET)
    {
        name_len = APP_DONGLE_HID_HS_NAME_LEN;
    }
    else if (role == APP_BT_CONN_ROLE_KEYBOARD)
    {
        name_len = APP_DONGLE_HID_KB_NAME_LEN;
    }
    else if (role == APP_BT_CONN_ROLE_MOUSE)
    {
        name_len = APP_DONGLE_HID_MS_NAME_LEN;
    }
    else if (role == APP_BT_CONN_ROLE_GAMEPAD)
    {
        name_len = APP_DONGLE_HID_GP_NAME_LEN;
    }
    /* send response */
    RSP *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                 pCmd->cmdhdr.id,
                                 sizeof(RSP) + name_len,
                                 cid);
    if (pRsp == NULL) {
        LOG_ERR("app_race_pg_dongle_scan RACE_ClaimPacketAppID fail");
        return NULL;
    }
    pRsp->status = 0;
    memcpy(&(pRsp->addr[0]), &(pCmd->addr[0]), 7);
    if (role == APP_BT_CONN_ROLE_HEADSET)
    {
        memcpy(&(pRsp->name[0]), APP_DONGLE_HID_HS_NAME, APP_DONGLE_HID_HS_NAME_LEN);
    }
    else if (role == APP_BT_CONN_ROLE_KEYBOARD)
    {
        memcpy(&(pRsp->name[0]), APP_DONGLE_HID_KB_NAME, APP_DONGLE_HID_KB_NAME_LEN);
    }
    else if (role == APP_BT_CONN_ROLE_MOUSE)
    {
        memcpy(&(pRsp->name[0]), APP_DONGLE_HID_MS_NAME, APP_DONGLE_HID_MS_NAME_LEN);
    }
    else if (role == APP_BT_CONN_ROLE_GAMEPAD)
    {
        memcpy(&(pRsp->name[0]), APP_DONGLE_HID_GP_NAME, APP_DONGLE_HID_GP_NAME_LEN);
    }
    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    LOG_INF("app_race_pg_dongle_get_device_name %u", role);

    return NULL;
}

static void *app_race_pg_dongle_reconnect(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    app_pg_scenario_handle_t *scenario_handle;
    int32_t race_ret = RACE_ERRCODE_FAIL;
    app_bt_conn_status_t link_status;

    CMD *pCmd = (CMD *)pCmdMsg;

#if defined(AIR_PURE_GAMING_DONGLE_MS_ENABLE)
    scenario_handle = app_pure_gaming_dongle_scenario_get_handle_by_role(APP_BT_CONN_ROLE_MOUSE);
#elif defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
    scenario_handle = app_pure_gaming_dongle_scenario_get_handle_by_role(APP_BT_CONN_ROLE_GAMEPAD);
#else
    scenario_handle = app_pure_gaming_dongle_scenario_get_handle_by_role(APP_BT_CONN_ROLE_KEYBOARD);
#endif /* AIR_PURE_GAMING_DONGLE_MS_ENABLE */
    if (scenario_handle->link_handle != NULL)
    {
        app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_GET_ULL_LINK_STATUS, &link_status);
        if ((link_status == APP_BT_CONN_STATUS_DISCONNECTED) || (link_status == APP_BT_CONN_STATUS_BONDED))
        {
            app_events_send(EVT_CMD_RECONNECT_REQ, scenario_handle);
        }
    }

    scenario_handle = app_pure_gaming_dongle_scenario_get_handle_by_role(APP_BT_CONN_ROLE_KEYBOARD);
    if (scenario_handle->link_handle != NULL)
    {
        app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_GET_ULL_LINK_STATUS, &link_status);
        if ((link_status == APP_BT_CONN_STATUS_DISCONNECTED) || (link_status == APP_BT_CONN_STATUS_BONDED))
        {
            app_events_send(EVT_CMD_RECONNECT_REQ, scenario_handle);
        }
    }

    /* send response */
    RSP *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                 pCmd->cmdhdr.id,
                                 sizeof(RSP),
                                 cid);
    if (pRsp == NULL) {
        LOG_ERR("app_race_pg_dongle_scan RACE_ClaimPacketAppID fail");
        return NULL;
    }
    pRsp->status = 0;
    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    LOG_INF("app_race_pg_dongle_reconnect operation done");

    return NULL;
}

static void *app_race_set_report_rate(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    UNUSED(length);

    int ret = 0;

    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint16_t report_rate;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    CMD *pCmd = (CMD *)pCmdMsg;
    // bool rr_change = false;
    app_pg_scenario_handle_t *scenario_handle;
    uint16_t report_rate = pCmd->report_rate;
    uint16_t report_rate_current;

    scenario_handle = app_pure_gaming_dongle_scenario_get_current_context();
    app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_GET_REPORT_RATE, &report_rate_current);
    if (report_rate_current != report_rate)
    {
        /* set report rate change flag */
        // rr_change = true;
        // app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_REPORT_RATE_CHANGE_REQUEST, &rr_change);
        /* do report rate switch */
        ret = app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_REPORT_RATE, &report_rate);
        LOG_INF("app_race_set_report_rate(rate: %u, scenario: 0x%x) ret = %d", report_rate, scenario_handle, ret);
    }
    else
    {
        LOG_INF("app_race_set_report_rate(rate: %u, scenario: 0x%x) is the same", report_rate, scenario_handle);
    }

    RSP *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                 pCmd->cmdhdr.id,
                                 sizeof(RSP),
                                 cid);
    if (pRsp == NULL) {
        LOG_ERR("app_race_set_report_rate RACE_ClaimPacketAppID fail");
        return NULL;
    }
    pRsp->status = ret;
    race_flush_packet((uint8_t *)pRsp, cid);

    // If the race cmd is not from tool(maybe from mouse), please notify tool newest report rate
    if (ret == 0 && cid != RACE_SERIAL_PORT_TYPE_USB) {
        uint8_t usb_cid = RACE_SERIAL_PORT_TYPE_USB;

        typedef struct {
            uint16_t report_rate_;
        } PACKED CMD;
        CMD *cmd = RACE_ClaimPacket(RACE_TYPE_NOTIFICATION,
                                    pCmd->cmdhdr.id,
                                    sizeof(CMD),
                                    usb_cid);
        if (cmd == NULL) {
            LOG_ERR("app_race_set_report_rate RACE_ClaimPacketAppID fail", 0);
            return NULL;
        }

        cmd->report_rate_ = report_rate;
        race_flush_packet((uint8_t *)cmd, usb_cid);
    }

    return NULL;
}

static void *app_race_get_report_rate(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    UNUSED(length);

    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
        uint16_t report_rate;
    } PACKED RSP;

    CMD *pCmd = (CMD *)pCmdMsg;

    uint16_t report_rate;
    int32_t race_ret = RACE_ERRCODE_FAIL;
    app_pg_scenario_handle_t *scenario_handle;

    scenario_handle = app_pure_gaming_dongle_scenario_get_current_context();
    int ret = app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_GET_REPORT_RATE, &report_rate);

    LOG_INF("app_race_get_report_rate(rate: %u, scenario: 0x%x) ret = %d", report_rate, scenario_handle, ret);

    RSP *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                 pCmd->cmdhdr.id,
                                 sizeof(RSP),
                                 cid);
    if (pRsp == NULL) {
        LOG_ERR("app_race_get_report_rate RACE_ClaimPacketAppID fail", 0);
        return NULL;
    }
    pRsp->status = ret;
    pRsp->report_rate = report_rate;
    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    return pRsp;
}

static void *app_race_set_uniaa(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    UNUSED(length);

    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t pair_device_type;
        uint8_t addr_type;
        uint8_t pair_address[6];
        uint8_t uni_aa[4];
        uint8_t ltk[16];
        uint8_t skd[16];
        uint8_t iv[8];
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    CMD *pCmd = (CMD *)pCmdMsg;
    int32_t race_ret = RACE_ERRCODE_FAIL;

    bt_ull_le_hid_dm_device_info_t *temp_info=(bt_ull_le_hid_dm_device_info_t *)k_malloc(sizeof(bt_ull_le_hid_dm_device_info_t));
    if (temp_info == NULL){
        LOG_ERR("SECNARIO_SRV_CONFIG_SET_UNIAA fail",0);
        return NULL;
    }

#if defined(CONFIG_AIR_PURE_GAMING_DONGLE_KB_ENABLE)
    temp_info->device_type = BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD;
#elif defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
    temp_info->device_type = BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD;
#elif defined(CONFIG_AIR_PURE_GAMING_DONGLE_MS_ENABLE)
    temp_info->device_type = BT_ULL_LE_HID_SRV_DEVICE_MOUSE;
#else
    #error "Unknown product for dongle"
#endif
    temp_info->addr.type = CONVERT_RACE_DEVICE_TYPE(pCmd->addr_type);
    memcpy(&temp_info->addr.a.val,pCmd->pair_address,6);
    memcpy(&temp_info->uni_aa,pCmd->uni_aa,4);
    memcpy(&temp_info->ltk,pCmd->ltk,16);
    memcpy(&temp_info->skd,pCmd->skd,16);
    memcpy(&temp_info->iv,pCmd->iv,8);
#if defined(CONFIG_AIR_PURE_GAMING_DONGLE_KB_ENABLE)
    temp_info->scenario = BT_ULL_LE_HID_SRV_APP_SCENARIO_82;
#elif defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
    temp_info->scenario = BT_ULL_LE_HID_SRV_APP_SCENARIO_83;
#elif defined(CONFIG_AIR_PURE_GAMING_DONGLE_MS_ENABLE)
    temp_info->scenario = BT_ULL_LE_HID_SRV_APP_SCENARIO_81;
#else
    #error "Unknown product for dongle"
#endif
    int ret = bt_ull_le_hid_dm_write_device_info(temp_info);

    RSP *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                 RACE_SET_UNIAA,
                                 sizeof(RSP),
                                 cid);
    if (pRsp == NULL) {
        LOG_ERR("app_race_set_uniaa RACE_ClaimPacketAppID fail", 0);
        return NULL;
    }
    pRsp->status = ret;
    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    return pRsp;
}

static void *app_race_get_uniaa(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    UNUSED(length);

    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t device_type;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
        uint8_t remote_address[7];
        uint8_t uni_aa[4];
        uint8_t ltk[16];
        uint8_t skd[16];
        uint8_t iv[8];
    } PACKED RSP;

    CMD *pCmd = (CMD *)pCmdMsg;
    int32_t race_ret = RACE_ERRCODE_FAIL;
    uint8_t rsp_size = sizeof(RSP);
    bt_addr_le_t address = {0};
    bt_ull_le_hid_dm_device_info_t *temp_info;
    uint8_t device_type = CONVERT_RACE_DEVICE_TYPE(pCmd->device_type);

    bt_ull_le_hid_dm_get_bonded_device_list(device_type, 1, &address);

#if defined(CONFIG_AIR_PURE_GAMING_DONGLE_KB_ENABLE)
    temp_info = bt_ull_le_hid_dm_read_device_info(BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD, &address);
#elif defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
    temp_info = bt_ull_le_hid_dm_read_device_info(BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD, &address);
#else
    temp_info = bt_ull_le_hid_dm_read_device_info(BT_ULL_LE_HID_SRV_DEVICE_MOUSE, &address);
#endif

    if (!temp_info) {
        rsp_size = 1;
    }

    LOG_INF("app_race_get_uniaa ", 0);

    RSP *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                 RACE_GET_UNIAA,
                                 rsp_size,
                                 cid);
    if (pRsp == NULL) {
        LOG_ERR("app_race_get_uniaa RACE_ClaimPacketAppID fail", 0);
        return NULL;
    }

    if(!temp_info)
    {
        pRsp->status = RACE_STATUS_ERROR;

    }else{
        pRsp->status = RACE_STATUS_OK;
        memcpy(pRsp->remote_address,&(temp_info->addr),7);
        memcpy(pRsp->uni_aa,temp_info->uni_aa,4);
        memcpy(pRsp->ltk,temp_info->ltk,16);
        memcpy(pRsp->skd,temp_info->skd,16);
        memcpy(pRsp->iv,temp_info->iv,8);
    }

    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    return pRsp;
}

/* Public functions ----------------------------------------------------------*/
int app_race_pg_dongle_adv_report(app_bt_conn_device_found_t *dev_found, uint8_t cid)
{
    typedef struct {
        uint8_t status;
        uint8_t link_type;
        uint8_t addr[7];
        int8_t rssi;
        uint8_t name[0];
    } PACKED RSP;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send notification */
    RSP *pRsp = RACE_ClaimPacket(RACE_TYPE_NOTIFICATION,
                                 RACE_DONGLE_LE_ADV_REPORT_NOTIFY,
                                 sizeof(RSP)+dev_found->name_len,
                                 cid);
    if (pRsp == NULL) {
        LOG_ERR("app_race_pg_dongle_adv_report RACE_ClaimPacketAppID fail");
        return -1;
    }
    pRsp->status = 0;
    if (dev_found->role == APP_BT_CONN_ROLE_MOUSE)
    {
        pRsp->link_type = 0x06;
    }
    else if (dev_found->role == APP_BT_CONN_ROLE_KEYBOARD)
    {
        pRsp->link_type = 0x05;
    }
    else if (dev_found->role == APP_BT_CONN_ROLE_GAMEPAD)
    {
        pRsp->link_type = 0x0A;
    }
    else
    {
        assert(0);
    }
    memcpy(&(pRsp->addr[0]), &(dev_found->addr), 7);
    pRsp->rssi = dev_found->rssi;
    memcpy(&(pRsp->name[0]), &(dev_found->name[0]), dev_found->name_len);

    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    return 0;
}

int app_race_pg_dongle_connection_response(app_bt_conn_handle_t *link_handle, bool is_connected, uint8_t cid)
{
    typedef struct {
        uint8_t status;
        uint8_t connect;
        uint8_t addr[7];
        uint8_t device_id;
        uint8_t group_id;
    } PACKED RSP;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send notification */
    RSP *pRsp = RACE_ClaimPacket(RACE_TYPE_NOTIFICATION,
                                 RACE_DONGLE_LE_CONNECT,
                                 sizeof(RSP),
                                 cid);
    if (pRsp == NULL) {
        LOG_ERR("app_race_pg_dongle_adv_report RACE_ClaimPacketAppID fail");
        return -1;
    }
    pRsp->status = 0;
    pRsp->connect = is_connected;
    memcpy(&(pRsp->addr[0]), &(link_handle->ull_addr), 7);
    pRsp->device_id = 0x80;
    pRsp->group_id = 0x01;

    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    return 0;
}

void *app_race_get_dpi(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    UNUSED(length);

    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint16_t x_dpi;
        uint16_t y_dpi;
    } PACKED CMD;

    CMD *pCmd = (CMD *)pCmdMsg;
    app_pg_dpi_para_t dpi_para;
    dpi_para.cur_dpi_x= pCmd->x_dpi;
    dpi_para.cur_dpi_y= pCmd->y_dpi;
    app_pg_scenario_handle_t *scenario_handle;

    scenario_handle = app_pure_gaming_dongle_scenario_get_current_context();
    app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_DPI_PARA, &dpi_para);
    LOG_INF("[debug] app_race_set_dpi x= %d,y= %d", dpi_para.cur_dpi_x, dpi_para.cur_dpi_y);
    app_pure_gaming_dongle_scenario_update_critical_device_infe(HID_CRITICAL_PATH_INFO_TYPE_DPI);

    return NULL;
}

void *app_race_get_battery(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    UNUSED(length);

    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t status;
        uint8_t chargering;
        uint8_t battery_status_percent;
    } PACKED CMD;

    CMD *pCmd = (CMD *)pCmdMsg;

    LOG_INF("[debug] app_race_get_battery chargering= %d,battery_status_percent= %d ", pCmd->chargering, pCmd->battery_status_percent);

    app_pg_scenario_handle_t *scenario_handle;
    uint8_t temp_chargering = pCmd->chargering;
    uint8_t temp_battery_status_percent = pCmd->battery_status_percent;
    scenario_handle = app_pure_gaming_dongle_scenario_get_current_context();
    app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_CHARGERING_STATUS, &temp_chargering);
    app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_BATTERY_STATUS, &temp_battery_status_percent);

    return NULL;
}

int app_race_pg_dongle_connection_report(app_bt_conn_handle_t *link_handle, bool is_connected, uint8_t status, uint8_t cid)
{
    typedef struct {
        uint8_t status;
        uint8_t link_type;
        uint8_t connect;
        uint8_t addr[7];
        uint8_t device_id;
        uint8_t group_id;
    } PACKED RSP;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send notification */
    RSP *pRsp = RACE_ClaimPacket(RACE_TYPE_NOTIFICATION,
                                 RACE_DONGLE_LE_CONNECT_NOTIFY,
                                 sizeof(RSP),
                                 cid);
    if (pRsp == NULL) {
        LOG_ERR("app_race_pg_dongle_adv_report RACE_ClaimPacketAppID fail");
        return -1;
    }
    pRsp->status = status;
    if (link_handle->role == APP_BT_CONN_ROLE_MOUSE)
    {
        pRsp->link_type = 0x06;
    }
    else if (link_handle->role == APP_BT_CONN_ROLE_KEYBOARD)
    {
        pRsp->link_type = 0x05;
    }
    else if (link_handle->role == APP_BT_CONN_ROLE_GAMEPAD)
    {
        pRsp->link_type = 0x0A;
    }
    else
    {
        assert(0);
    }
    pRsp->connect = is_connected;
    memcpy(&(pRsp->addr[0]), &(link_handle->ull_addr), 7);
    pRsp->device_id = 0x80;
    pRsp->group_id = 0x01;

    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    LOG_INF("app_race_pg_dongle_connection_report connect %u, address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x",
            pRsp->connect,
            pRsp->addr[5],
            pRsp->addr[4],
            pRsp->addr[3],
            pRsp->addr[2],
            pRsp->addr[1],
            pRsp->addr[0]);

    return 0;
}

void *app_race_pg_dongle_le_race_cmd_handler(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t cid)
{
    void *pEvt = NULL;

    if (pCmdMsg->hdr.type == RACE_TYPE_COMMAND ||
        pCmdMsg->hdr.type == RACE_TYPE_RESPONSE ||
        pCmdMsg->hdr.type == RACE_TYPE_COMMAND_WITHOUT_RSP ||
        pCmdMsg->hdr.type == RACE_TYPE_NOTIFICATION)
    {
        switch (pCmdMsg->hdr.id)
        {
            case RACE_DONGLE_LE_SCAN:
                return app_race_pg_dongle_scan((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);

            case RACE_DONGLE_LE_CONNECT:
                return app_race_pg_dongle_connect((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);

            case RACE_DONGLE_LE_GET_LINK_TYPE:
                return app_race_pg_dongle_get_link_type((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);

            case RACE_DONGLE_LE_SET_LINK_TYPE:
                return app_race_pg_dongle_set_link_type((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);

            case RACE_DONGLE_LE_GET_PAIRED_LIST:
                return app_race_pg_dongle_get_paired_list((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);

            case RACE_DONGLE_LE_REMOVE_PAIRED_RECORD:
                return app_race_pg_dongle_remove_paired_record((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);

            case RACE_DONGLE_LE_GET_DEVICE_LIST:
                return app_race_pg_dongle_get_device_list((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);

            case RACE_DONGLE_LE_GET_DEVICE_NAME:
                return app_race_pg_dongle_get_device_name((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);

            case RACE_DONGLE_LE_GET_DEVICE_STATUS:
            case RACE_DONGLE_LE_SWITCH_ACTIVE_DEVICE:
                LOG_ERR("not support cmd 0x%x", pCmdMsg->hdr.id);
                assert(0);
                break;

            case RACE_HID_RECONNECT:
                return app_race_pg_dongle_reconnect((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);

            case RACE_SET_REPORT_RATE:
                return app_race_set_report_rate((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);

            case RACE_GET_REPORT_RATE:
                return app_race_get_report_rate((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);

            case RACE_GET_CUR_DPI:
                return app_race_get_dpi((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);

            case RACE_GET_BATTERY:
                return app_race_get_battery((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);

            case RACE_SET_UNIAA:
                return app_race_set_uniaa((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);

            case RACE_GET_UNIAA:
                return app_race_get_uniaa((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);

            default:
                LOG_ERR("not support cmd 0x%x", pCmdMsg->hdr.id);
                assert(0);
                break;
        }
    }

    return pEvt;
}

void race_fota_dongle_reconnect_ms_kb()
{
    app_pg_scenario_handle_t *scenario_handle;
    scenario_handle = app_pure_gaming_dongle_scenario_get_current_context();
    if (NULL != scenario_handle && scenario_handle->link_handle != NULL) {
        LOG_INF("dongle disc scenario_handle->link_handle = %x", scenario_handle->link_handle);
        app_events_send(EVT_CMD_RECONNECT_REQ, scenario_handle);
    }
}

void race_fota_dongle_disconnect_ms_kb()
{
    app_pg_scenario_handle_t *scenario_handle;
    scenario_handle = app_pure_gaming_dongle_scenario_get_current_context();
    if (NULL != scenario_handle) {
        app_events_send(EVT_CMD_DISCONNECT_REQ, scenario_handle);
    } else {
        LOG_ERR("dongle reconnect scenario_handle is NULL");
    }
}
#endif /* AIR_PURE_GAMING_DONGLE_ENABLE */
