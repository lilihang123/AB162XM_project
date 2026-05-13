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
#include"bt_hogp_client.h"
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#define LOG_LEVEL CONFIG_BT_HOGP_CLIENT_LOG_LEVEL
#include <zephyr/logging/log.h>

static struct bt_uuid_16 s_hogp_discover_uuid = BT_UUID_INIT_16(0);
static struct bt_gatt_discover_params s_hogp_discover_params;
struct bt_gatt_subscribe_params s_hogp_subscribe_params;

uint16_t s_hogp_descriptor_start_handle = 0;

struct bt_gatt_discover_params report_sub_disc_params;
//const struct bt_uuid s_hogp_uuid[10] = {BT_UUID_HIDS, BT_UUID_HIDS_INFO, BT_UUID_HIDS_REPORT_MAP, BT_UUID_HIDS_PROTOCOL_MODE};

static int bt_hogp_client_discover_character_start(struct bt_conn *conn, const struct bt_gatt_attr *attr, const struct bt_uuid *next_uuid)
{
    int err = 0xFF;
    struct bt_gatt_service_val *service_val = (struct bt_gatt_service_val*)(attr->user_data);
    //(void)memcpy(&s_hogp_discover_uuid, next_uuid, sizeof(s_hogp_discover_uuid));
    //s_hogp_discover_params.uuid = &s_hogp_discover_uuid.uuid;
    s_hogp_discover_params.uuid = NULL;
    s_hogp_discover_params.start_handle = attr->handle + 1;
    s_hogp_descriptor_start_handle = attr->handle + 2;
    s_hogp_discover_params.end_handle = service_val->end_handle;
    s_hogp_discover_params.type = BT_GATT_DISCOVER_CHARACTERISTIC;
    err = bt_gatt_discover(conn, &s_hogp_discover_params);
    LOG_INF("[BT_HOGP_CLIENT] character_start :%x, att_handle:%x, end_handle:%x", err, attr->handle, service_val->end_handle);
    return err;
}

static void bt_hogp_client_discover_descriptor_start(struct bt_conn *conn, const struct bt_gatt_attr *attr, const struct bt_uuid *next_uuid,struct bt_gatt_discover_params *params)
{
    int err = 0xFF;
    //(void)memcpy(&s_hogp_discover_uuid, next_uuid, sizeof(s_hogp_discover_uuid));
    s_hogp_discover_params.uuid = NULL;
    LOG_INF("[BT_HOGP_CLIENT] descriptor_start:%x", params->start_handle, params->end_handle);
    s_hogp_discover_params.start_handle = s_hogp_descriptor_start_handle + 1;
    s_hogp_discover_params.type = BT_GATT_DISCOVER_DESCRIPTOR;
    //s_hogp_subscribe_params.value_handle = bt_gatt_attr_value_handle(attr);
    err = bt_gatt_discover(conn, &s_hogp_discover_params);
    LOG_INF("[BT_HOGP_CLIENT] descriptor_start :%x, start_handle:%x", err, s_hogp_descriptor_start_handle);
}
#if 0
static void bt_hogp_client_discover_next_character(struct bt_conn *conn,  const struct bt_gatt_attr *attr,
        struct bt_gatt_discover_params *params)
{
    bt_hogp_client_state_t state = bt_hogp_client_get_discovery_state(conn);

    switch (state) {
    case HOGP_DISCOVEY_SERVICE_DISCOVERY_HID_INFO: {
        bt_hogp_client_discover_character_start(conn, attr, BT_UUID_HIDS_REPORT_MAP);
        bt_hogp_client_set_discovery_state(conn,HOGP_DISCOVEY_SERVICE_DISCOVERY_HID_REPORT_MAP);
        break;
    }
    case HOGP_DISCOVEY_SERVICE_DISCOVERY_HID_REPORT_MAP: {
        bt_hogp_client_discover_character_start(conn, attr, BT_UUID_HIDS_PROTOCOL_MODE);
        bt_hogp_client_set_discovery_state(conn,HOGP_DISCOVEY_SERVICE_DISCOVERY_HID_PROTOCOL_MODE);
        break;
    }
    case HOGP_DISCOVEY_SERVICE_DISCOVERY_HID_PROTOCOL_MODE: {
        bt_hogp_client_discover_character_start(conn, attr, BT_UUID_HIDS_REPORT);
        bt_hogp_client_set_discovery_state(conn,HOGP_DISCOVEY_SERVICE_DISCOVERY_HID_REPORTS);
        break;
    }
    case HOGP_DISCOVEY_SERVICE_DISCOVERY_HID_REPORTS: {
        bt_hogp_client_discover_character_start(conn, attr, BT_UUID_HIDS_CTRL_POINT);
        bt_hogp_client_set_discovery_state(conn,HOGP_DISCOVEY_SERVICE_DISCOVERY_HID_CONTROL_POINT);
        break;
    }
    case HOGP_DISCOVEY_SERVICE_DISCOVERY_HID_CONTROL_POINT: {
        bt_hogp_client_discover_character_start(conn, attr, BT_UUID_HIDS_BOOT_MOUSE_IN_REPORT);
        bt_hogp_client_set_discovery_state(conn,HOGP_DISCOVEY_SERVICE_DISCOVERY_BOOT_MOUSE_INPUT_REPORT);
        break;
    }
    case HOGP_DISCOVEY_SERVICE_DISCOVERY_BOOT_MOUSE_INPUT_REPORT: {
        bt_hogp_client_discover_character_start(conn, attr, BT_UUID_HIDS_BOOT_KB_IN_REPORT);
        bt_hogp_client_set_discovery_state(conn,HOGP_DISCOVEY_SERVICE_DISCOVERY_BOOT_KB_INPUT_REPORT);
        break;
    }
    case HOGP_DISCOVEY_SERVICE_DISCOVERY_BOOT_KB_INPUT_REPORT: {
        bt_hogp_client_discover_character_start(conn, attr, BT_UUID_HIDS_BOOT_KB_OUT_REPORT);
        bt_hogp_client_set_discovery_state(conn,HOGP_DISCOVEY_SERVICE_DISCOVERY_BOOT_KB_OUTPUT_REPORT);
        break;
    }
    case HOGP_DISCOVEY_SERVICE_DISCOVERY_BOOT_KB_OUTPUT_REPORT: {
        bt_hogp_client_discovery_commplete_notify(conn, 0);
        break;
    }
    }
}
#endif

static uint8_t bt_hogp_client_discover_descriptor_callback_process(struct bt_conn *conn, const struct bt_gatt_attr *attr,
        struct bt_gatt_discover_params *params)
{
    // save service;
    LOG_INF("[BT_HOGP_CLIENT] discover_descriptor_callback,attr:%x", attr);
    if (attr == NULL) {
        //bt_hogp_client_discover_next_character(conn, attr, params);
        LOG_INF("[BT_HOGP_CLIENT] discover_descriptor_callback,complete");
        bt_hogp_client_discovery_commplete_notify(conn, 0);
        return BT_GATT_ITER_STOP;
    } else {
        bt_hogp_descriptor_type_t type = 0;
        if (bt_uuid_cmp(attr->uuid, BT_UUID_GATT_CCC) == 0) {
            LOG_INF("[BT_HOGP_CLIENT] discover_descriptor_callback,GATT_CCCD");
            type = HOGP_DESCRIPTOR_TYPE_CCCD;
        } else if (bt_uuid_cmp(attr->uuid, BT_UUID_HIDS_REPORT_REF) == 0) {
            LOG_INF("[BT_HOGP_CLIENT] discover_descriptor_callback,REPORT_REF");
            type = HOGP_DESCRIPTOR_TYPE_REPPORT_REFERENCE;
        } else if (bt_uuid_cmp(attr->uuid, BT_UUID_HIDS_EXT_REPORT) == 0) {
            LOG_INF("[BT_HOGP_CLIENT] discover_descriptor_callback,EXTERN_REF");
            type = HOGP_DESCRIPTOR_TYPE_EXTERN_REPORT_REFERENCE;
        }
        if (type) {
            bt_hogp_client_save_descriptor(conn, attr, type);
        } else {
            LOG_INF("[BT_HOGP_CLIENT] discover_descriptor_callback,no need save");
        }
    }
    return BT_GATT_ITER_CONTINUE;
}

static uint8_t bt_hogp_client_discover_character_callback_process(struct bt_conn *conn, const struct bt_gatt_attr *attr,
        struct bt_gatt_discover_params *params)
{
    if (attr == NULL) {
        // handle descriptor discovery
        LOG_INF("[BT_HOGP_CLIENT] discover_character_callback,complete");
        bt_hogp_client_discover_descriptor_start(conn, NULL, NULL, params);
        return BT_GATT_ITER_STOP;
    }

struct bt_gatt_chrc *chrc = (struct bt_gatt_chrc *)attr->user_data;
    if (chrc !=  NULL) {
        LOG_INF("[BT_HOGP_CLIENT] discover_character_callback, value_handle:%x, params->type:%d", chrc->value_handle, params->type);
    }
#if 0
    if (bt_uuid_cmp(&s_hogp_discover_uuid.uuid, BT_UUID_HIDS_INFO) == 0) {
        bt_hogp_client_save_character(conn, attr, HOGP_CHARC_HID_INFO);

    } else if (bt_uuid_cmp(&s_hogp_discover_uuid.uuid, BT_UUID_HIDS_REPORT_MAP) == 0) {
        bt_hogp_client_save_character(conn, attr, HOGP_CHARC_HID_REPORT_MAP);
        LOG_INF("[BT_HOGP_CLIENT] discover_character_callback, attr:%x, params->type:%d");
    } else if (bt_uuid_cmp(&s_hogp_discover_uuid.uuid, BT_UUID_HIDS_PROTOCOL_MODE) == 0) {
        bt_hogp_client_save_character(conn, attr, HOGP_CHARC_HID_PROTOCOL_MODE);
    } else if (bt_uuid_cmp(&s_hogp_discover_uuid.uuid, BT_UUID_HIDS_REPORT) == 0) {
        bt_hogp_client_save_character(conn, attr, HOGP_CHARC_HID_REPORT);
    } else if (bt_uuid_cmp(&s_hogp_discover_uuid.uuid, BT_UUID_HIDS_CTRL_POINT) == 0) {
        bt_hogp_client_save_character(conn, attr, HOGP_CHARC_HID_CONTROL_POINT);
    } else if (bt_uuid_cmp(&s_hogp_discover_uuid.uuid, BT_UUID_HIDS_BOOT_MOUSE_IN_REPORT) == 0) {
        bt_hogp_client_save_character(conn, attr, HOGP_CHARC_HID_BOOT_MOUSE_INTPUT_REPORT);
    } else if (bt_uuid_cmp(&s_hogp_discover_uuid.uuid, BT_UUID_HIDS_BOOT_KB_OUT_REPORT) == 0) {
        bt_hogp_client_save_character(conn, attr, HOGP_CHARC_HID_BOOT_KB_OUTPUT_REPORT);
    } else if (bt_uuid_cmp(&s_hogp_discover_uuid.uuid, BT_UUID_HIDS_BOOT_KB_IN_REPORT) == 0) {
        bt_hogp_client_save_character(conn, attr, HOGP_CHARC_HID_BOOT_KB_INPUT_REPORT);
    }
    bt_hogp_client_discover_descriptor_start(conn, attr, BT_UUID_GATT_CCC);
#endif
#if 1
    if (bt_uuid_cmp(chrc->uuid, BT_UUID_HIDS_INFO) == 0) {
        LOG_INF("[BT_HOGP_CLIENT] discover_chara_callback_func, HIDS_INFO");
        bt_hogp_client_save_character(conn, attr, HOGP_CHARC_HID_INFO);
    } else if (bt_uuid_cmp(chrc->uuid, BT_UUID_HIDS_REPORT_MAP) == 0) {
        LOG_INF("[BT_HOGP_CLIENT] discover_chara_callback_func, REPORT_MAP");
        bt_hogp_client_save_character(conn, attr, HOGP_CHARC_HID_REPORT_MAP);
    } else if (bt_uuid_cmp(chrc->uuid, BT_UUID_HIDS_PROTOCOL_MODE) == 0) {
        LOG_INF("[BT_HOGP_CLIENT] discover_chara_callback_func, PROTOCOL_MODE");
        bt_hogp_client_save_character(conn, attr, HOGP_CHARC_HID_PROTOCOL_MODE);
    } else if (bt_uuid_cmp(chrc->uuid, BT_UUID_HIDS_REPORT) == 0) {
        LOG_INF("[BT_HOGP_CLIENT] discover_chara_callback_func, HIDS_REPORT");
        bt_hogp_client_save_character(conn, attr, HOGP_CHARC_HID_REPORT);
    } else if (bt_uuid_cmp(chrc->uuid, BT_UUID_HIDS_BOOT_MOUSE_IN_REPORT) == 0) {
        LOG_INF("[BT_HOGP_CLIENT] discover_chara_callback_func, MOUSE_INPUT");
        bt_hogp_client_save_character(conn, attr, HOGP_CHARC_HID_BOOT_MOUSE_INTPUT_REPORT);
    } else if (bt_uuid_cmp(chrc->uuid, BT_UUID_HIDS_BOOT_KB_OUT_REPORT) == 0) {
        LOG_INF("[BT_HOGP_CLIENT] discover_chara_callback_func, KB_OUTPUT");
        bt_hogp_client_save_character(conn, attr, HOGP_CHARC_HID_BOOT_KB_OUTPUT_REPORT);
    } else if (bt_uuid_cmp(chrc->uuid, BT_UUID_HIDS_BOOT_KB_OUT_REPORT) == 0) {
        LOG_INF("[BT_HOGP_CLIENT] discover_chara_callback_func, KB_INPUT");
        bt_hogp_client_save_character(conn, attr, HOGP_CHARC_HID_BOOT_KB_INPUT_REPORT);
    } else if (bt_uuid_cmp(chrc->uuid, BT_UUID_HIDS_CTRL_POINT) == 0) {
        bt_hogp_client_save_character(conn, attr, HOGP_CHARC_HID_CONTROL_POINT);
    }
#endif
    return BT_GATT_ITER_CONTINUE;
}

static uint8_t bt_hogp_client_discover_service_callback_process(struct bt_conn *conn, const struct bt_gatt_attr *attr,
        struct bt_gatt_discover_params *params)
{
    // save service;
    int err = 0;
    if (bt_uuid_cmp(&s_hogp_discover_uuid.uuid, BT_UUID_HIDS) == 0) {
        err = bt_hogp_client_discover_character_start(conn, attr, BT_UUID_HIDS_INFO);
        bt_hogp_client_set_discovery_state(conn,HOGP_DISCOVEY_SERVICE_DISCOVERY_HID_INFO);
    }
    return err;
}

static uint8_t hogp_discover_func(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                                  struct bt_gatt_discover_params *params)
{
    int err = 0xFF;
    LOG_INF("[BT_HOGP_CLIENT] hogp_func_callback, attr:%x, params->type:%d", attr, params->type);
    switch (params->type) {
    case BT_GATT_DISCOVER_PRIMARY:
    case BT_GATT_DISCOVER_SECONDARY: {
        err = bt_hogp_client_discover_service_callback_process(conn, attr, params);
        break;
    }
    case BT_GATT_DISCOVER_CHARACTERISTIC: {
        /* code */
        err = bt_hogp_client_discover_character_callback_process(conn, attr, params);
        break;
    }
    case BT_GATT_DISCOVER_DESCRIPTOR: {
        err = bt_hogp_client_discover_descriptor_callback_process(conn, attr, params);
        break;
    }
    default:
        break;
    }

    return err;
}

int bt_hogp_client_service_discover_start(struct bt_conn *conn)
{
    LOG_INF("[BT_HOGP_CLIENT] discovery_start");
    //bt_gatt_discover_start(conn, BT_GATT_DISCOVER_USER_HOGP_SERVICE, BT_UUID_HIDS);
    (void)memcpy(&s_hogp_discover_uuid, BT_UUID_HIDS, sizeof(s_hogp_discover_uuid));
    s_hogp_discover_params.uuid = &s_hogp_discover_uuid.uuid;
    //s_hogp_discover_params.uuid = NULL;
    s_hogp_discover_params.func = hogp_discover_func;
    s_hogp_discover_params.start_handle = BT_ATT_FIRST_ATTRIBUTE_HANDLE;
    s_hogp_discover_params.end_handle = BT_ATT_LAST_ATTRIBUTE_HANDLE;
    s_hogp_discover_params.type = BT_GATT_DISCOVER_PRIMARY;

    int err = bt_gatt_discover(conn, &s_hogp_discover_params);
    LOG_INF("[BT_HOGP_CLIENT]Discover start(err %d)\n", err);
    if (err == 0) {
        bt_hogp_client_set_discovery_state(conn,HOGP_DISCOVEY_SERVICE_DISCOVERY_HIDS);
    }
    return err;
}
