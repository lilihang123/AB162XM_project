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

#ifndef _BT_GATT_DISCOVER_H_
#define _BT_GATT_DISCOVER_H_

#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/kernel.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BT_GATT_DISCOVERY_MAX_LINK_NUM       4
#define BT_GATT_DISCOVERY_MAX_USER_NUM       10

#define BT_GATT_DISCOVERY_STATUS_SUCCESS                0x0
#define BT_GATT_DISCOVERY_STATUS_FAIL                   0x01
#define BT_GATT_DISCOVERY_STATUS_OUT_OF_MEMORY          0x02
#define BT_GATT_DISCOVERY_STATUS_INVALIDE_PARAMETER     0x03
#define BT_GATT_DISCOVERY_STATUS_BUSY                   0x04
#define BT_GATT_DISCOVERY_STATUS_FULL                   0x05
typedef uint8_t  bt_gatt_discovery_status_t;

#define BT_GATT_DISCOVER_USER_SERVICE_NONE                 0x00
#define BT_GATT_DISCOVER_USER_HOGP_SERVICE                 0x01
#define BT_GATT_DISCOVER_USER_BATTERY_SERVICE              0x02
#define BT_GATT_DISCOVER_USER_GAP_SERVICE                  0x03
typedef uint8_t  bt_gatt_discover_user_t;

#define BT_GATT_DISCOVERY_EVENT_COMPLETE  0x01
#define BT_GATT_DISCOVERY_EVENT_CONTINUE  0x02
#define BT_GATT_DISCOVERY_EVENT_FAIL      0x03
typedef uint8_t bt_gatt_discover_event_t;

#define BT_GATT_DISCOVER_STATE_NONE                        0x00
#define BT_GATT_DISCOVER_STATE_START                       0x01
#define BT_GATT_DISCOVER_STATE_SERVICE                     0x02
#define BT_GATT_DISCOVER_STATE_ATTRIBUTE                   0x03
#define BT_GATT_DISCOVER_STATE_CHARACTER                   0x04
typedef uint8_t bt_gatt_discover_state_t;

typedef struct {
    struct bt_conn *conn;
    void *param;
    bt_gatt_discover_event_t event;
    bt_gatt_discovery_status_t status;
}bt_gatt_discover_complete_param_t;

typedef bt_gatt_discovery_status_t (*bt_gatt_discover_complete_cb)(bt_gatt_discover_complete_param_t *params);



bt_gatt_discovery_status_t bt_gatt_discover_register_user(bt_gatt_discover_user_t user, bt_gatt_discover_complete_cb *callback);
bt_gatt_discovery_status_t bt_gatt_discover_start(struct bt_conn *conn, bt_gatt_discover_user_t user, struct bt_uuid *service_uuid);
uint16_t bt_gatt_discover_get_character_handle_by_uuid(struct bt_conn *conn, bt_gatt_discover_user_t user, struct bt_uuid *char_uuid);
uint16_t bt_gatt_discover_get_desc_handle_by_uuid(struct bt_conn *conn, bt_gatt_discover_user_t user, struct bt_uuid *char_uuid, struct bt_uuid *desc_uuid);
size_t bt_gatt_discover_get_character_num_by_uuid(struct bt_conn *conn, bt_gatt_discover_user_t user, struct bt_uuid *char_uuid);

#ifdef __cplusplus
}
#endif

#endif /* _BT_GATT_DISCOVER_H_ */