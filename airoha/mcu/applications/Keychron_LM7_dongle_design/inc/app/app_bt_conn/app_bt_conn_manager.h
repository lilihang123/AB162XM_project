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

#ifndef _APP_BT_CONN_MANAGER_H_
#define _APP_BT_CONN_MANAGER_H_

#if defined(AIR_PURE_GAMING_DONGLE_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>

/* Public define -------------------------------------------------------------*/
#define APP_BT_CONN_MANAGER_DEVICE_NAME_MAX 20

/* Public typedef ------------------------------------------------------------*/
typedef uint8_t app_bt_conn_role_t;
#define APP_BT_CONN_ROLE_UNKNOWN            0x00
#define APP_BT_CONN_ROLE_MOUSE              0x01
#define APP_BT_CONN_ROLE_KEYBOARD           0x02
#define APP_BT_CONN_ROLE_HEADSET            0x03
#define APP_BT_CONN_ROLE_GAMEPAD            0x04

typedef uint8_t app_bt_conn_status_t;
#define APP_BT_CONN_STATUS_UNKNOWN              0x00
#define APP_BT_CONN_STATUS_BONDED               0x01
#define APP_BT_CONN_STATUS_DISCONNECTED         0x02
#define APP_BT_CONN_STATUS_CONNCETING           0x03
#define APP_BT_CONN_STATUS_CONNECTTED           0x04
#define APP_BT_CONN_STATUS_SERVICE_CONNECTTED   0x05
#define APP_BT_CONN_STATUS_SECURITY_UPDATE      0x06

typedef uint8_t app_bt_conn_type_t;
#define APP_BT_CONN_TYPE_UNKNOWN            0x00
#define APP_BT_CONN_TYPE_ACL                0x01
#define APP_BT_CONN_TYPE_ULL                0x02

typedef struct {
    app_bt_conn_role_t role;
    bool acl_disable;
    bt_addr_le_t acl_addr;
    app_bt_conn_status_t acl_status;
    bool ull_disable;
    bt_addr_le_t ull_addr;
    app_bt_conn_status_t ull_status;
    struct bt_conn *acl_conn;
    struct bt_conn *ull_conn;
    void *scenario_handle;
} app_bt_conn_handle_t;

typedef struct {
    void *fifo_reserved;
    app_bt_conn_role_t role;
    int8_t rssi;
    uint8_t adv_type;
    bt_addr_le_t addr;
    uint8_t name_len;
    uint8_t name[APP_BT_CONN_MANAGER_DEVICE_NAME_MAX];
} app_bt_conn_device_found_t;

/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
extern void *app_bt_conn_manager_malloc(uint32_t size);
extern void app_bt_conn_manager_free(void *ptr);
extern app_bt_conn_handle_t *app_bt_conn_manager_get_handle(app_bt_conn_role_t role);
extern int app_bt_conn_manager_release_handle(app_bt_conn_handle_t *link_handle);
extern int app_bt_conn_manager_set_handle_conn(app_bt_conn_handle_t *link_handle, app_bt_conn_type_t type, struct bt_conn *conn);
extern app_bt_conn_handle_t *app_bt_conn_manager_query_handle_by_conn(app_bt_conn_type_t type, struct bt_conn *conn);
extern int app_bt_conn_manager_set_handle_addr(app_bt_conn_handle_t *link_handle, app_bt_conn_type_t type, bt_addr_le_t *addr);
extern int app_bt_conn_manager_set_handle_disable(app_bt_conn_handle_t *link_handle, app_bt_conn_type_t type, bool is_disable);
extern app_bt_conn_handle_t *app_bt_conn_manager_query_handle_by_addr(app_bt_conn_type_t type, bt_addr_le_t *addr);
extern app_bt_conn_handle_t *app_bt_conn_manager_query_handle_by_role(app_bt_conn_role_t role);
extern int app_bt_conn_manager_set_scenario_handle(app_bt_conn_handle_t *link_handle, void *scenario_handle);
extern void *app_bt_conn_manager_get_scenario_handle(app_bt_conn_handle_t *link_handle);
extern void app_bt_conn_init(void);

#endif /* AIR_PURE_GAMING_DONGLE_ENABLE */

#endif /* _APP_BT_CONN_MANAGER_H_ */
