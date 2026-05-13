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
 * Description:
 * ------------
 * This file implements DOGP service service structures and functions
 *
 ****************************************************************************/

#ifndef __BLE_AIR_INTERNAL_H__
#define __BLE_AIR_INTERNAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "ble_air_interface.h"
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/addr.h>
#include <sys/types.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/sys/util.h>


#define BLE_AIR_CCCD_NOTIFICATION  (0x0001)


#define ATT_HEADER_LENGTH          (3) /*3 is the length of opcode and handle in Structure <bt_att_handle_value_notification_t>*/
#define BLE_AIR_UPDATE_RETRY_COUNT          (3)


#ifdef CONFIG_BT_ULL_HID_LE
typedef enum {
    REMOTE_DEVICE_NONE = 0x00,
    REMOTE_DEVICE_HEADSET = 0x01,
    REMOTE_DEVICE_KEYBOARD = 0x02,
    REMOTE_DEVICE_MOUSE = 0x03,
    REMOTE_DEVICE_EARBUDS = 0x04,

    REMOTE_DEVICE_MAX = 0xFF
} ble_air_remote_type;
#endif

/**
 * structure for main cntx.
 */
typedef struct {
    struct bt_conn                  *conn;
    uint16_t                        conn_handle;
    bool                            is_real_connected; //After ACL link connected and first write request had come
    bool                            need_ready2write;
    uint16_t                        notify_enabled;
    uint8_t                         *receive_buffer;
    uint32_t                        receive_buffer_start;
    uint32_t                        receive_buffer_length;
    uint16_t                        revert_interval;
    uint16_t                        revert_supervision_timeout;
    bool                            is_link_optimization;
    uint8_t                         retry_count;
#ifdef CONFIG_BT_ULL_HID_LE
    ble_air_remote_type             remote_type;
    uint16_t                        remote_att_handle_rx;  /**< The attribute handle of remote device air service rx. */
    uint16_t                        remote_att_handle_tx;  /**< The attribute handle of remote device air service tx. */
    uint16_t                        remote_att_handle_cccd;  /**< The attribute handle of remote device air service cccd. */
#endif
#if defined(AIR_PURE_GAMING_DONGLE_ENABLE)
    uint16_t start_handle;
    uint16_t end_handle;
    uint16_t rx_handle;
    uint16_t tx_handle;
    uint16_t cccd_handle;
    struct bt_gatt_subscribe_params tx_sub_params;
    struct bt_gatt_discover_params tx_sub_disc_params;
    struct bt_gatt_subscribe_params cccd_sub_params;
    struct bt_gatt_discover_params cccd_sub_disc_params;
    //bool cp_retried;

    //bool busy;
    struct bt_gatt_write_params write_params;
    struct bt_gatt_read_params read_params;
    struct bt_gatt_discover_params discover_params;
    struct bt_uuid_16 uuid;
#endif
} ble_air_cntx_t;

#ifdef CONFIG_BT_ULL_HID_LE
typedef struct {
    uint16_t                        handle;                       /**< The connection handle. */
    ble_air_remote_type             remote_type;                  /**< The remote device type. */
    uint16_t                        mtu;                          /**< The mtu */
    bt_addr_le_t                    peer_address;                    /**< The remote device address.*/
    uint8_t                         *receive_buffer;
    uint32_t                        receive_buffer_length;
}  ble_air_ull_cntx_t;
#endif

ble_air_cntx_t *ble_air_get_cntx_by_handle(uint16_t conn_handle);
uint16_t ble_air_get_real_connected_handle(void);

ble_air_status_t ble_air_srv_notify_connected(uint16_t connection_handle, bt_addr_t *address);

ble_air_status_t ble_air_srv_notify_disconnected(uint16_t connection_handle, bt_addr_t *address);

#ifdef CONFIG_BT_ULL_HID_LE
ble_air_ull_cntx_t *ble_air_ull_get_cntx_by_handle(uint16_t conn_handle);
#endif
void ble_air_link_performace_optimization(void);
void ble_air_link_performace_optimization_revert(void);
#ifdef __cplusplus
}
#endif

#endif /**__BLE_AIR_INTERNAL_H__*/




