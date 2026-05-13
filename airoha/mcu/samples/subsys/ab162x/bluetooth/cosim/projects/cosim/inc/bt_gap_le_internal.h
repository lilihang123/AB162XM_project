/* Copyright Statement:
 *
 * (C) 2005-2016  MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. ("MediaTek") and/or its licensors.
 * Without the prior written permission of MediaTek and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) MediaTek Software
 * if you have agreed to and been bound by the applicable license agreement with
 * MediaTek ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */
/* MediaTek restricted information */

#ifndef __BT_GAP_LE_INTERNAL_H__
#define __BT_GAP_LE_INTERNAL_H__

#include "bt_debug.h"
#include "bt_hci_internal.h"
#include "bt_type_def.h"

#include "bt_gap_le.h"
#include "bt_hci_spec.h"
#include "bt_hci.h"
#ifdef __cplusplus
extern "C" {
#endif

#define BT_GAP_LE_EVENT_APP_INPUT                      (BT_MODULE_GAP | 0xFFFFF2)
#define BT_GAP_LE_EVENT_INVALID                        (BT_MODULE_GAP | 0xFFFFFF)

#define BT_POWER_STATUS_OFF           0x00
#define BT_POWER_STATUS_ON            0x01
#define BT_POWER_STATUS_SWITCHING_OFF 0x02
#define BT_POWER_STATUS_SWITCHING_ON  0x03
extern uint8_t bt_power_status;

#define BT_GAP_LE_ENCRYPTION                           (0x01 << 0) /**< Remote device support LE Encryption. */
#define BT_GAP_LE_CONNECTION_PARAMETERS_REQUEST        (0x01 << 1) /**< Remote device support Connection Parameters Requset Peocedure. */
#define BT_GAP_LE_EXTEND_REJECT_IND                    (0x01 << 2) /**< Remote device support Extend Reject Indication. */
#define BT_GAP_LE_PERIPHERAL_INITIATED_FEATURE_EXCHANGE     (0x01 << 3) /**< Remote device support Peripheral-initiated Feature Exchange. */
#define BT_GAP_LE_ULL2_0_SUPPORT                       (0x01 << 6) /**< Remote device support Peripheral-initiated Feature Exchange. */

typedef uint8_t bt_gap_remote_feature_t;

#define BT_GAP_POWER_ON_FLAG          (0xEE000000)

extern bt_power_reset_t bt_power_reset_type;

/**
 *  @brief Confirmation on the maximum advertising instances received.
 */
BT_PACKED(
typedef struct {
    bt_hci_status_t  status;                         /**< Status. */
    uint8_t          max_advertising_instances;      /**< The maximum number of advertising instances supported by the controller. */
}) bt_gap_le_get_max_advertising_instances_cnf_t;

BT_PACKED(
typedef struct{
    bt_handle_t handle;
    uint8_t peer_clock_accuracy;
})bt_gap_le_request_peer_sca_complete_t;


typedef struct {
    bt_bd_addr_t random_addr;
    uint8_t new_adv_flag;
    uint8_t addr_type;
    bt_compatible_t compatible_type;
    uint8_t handle;
    int8_t selected_tx_power;
} bt_gap_ext_adv_recored_t;

/**
 * @brief     Gap event callback.
 * @param[in] is_timeout    True means timeout trigger.
 * @param[in] timer_id      Gap timer id
 * @param[in] data          Data or NULL if not required.
 * @param[in] param         Received hci packet.
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 */
bt_status_t bt_gap_le_event_callback(uint32_t is_timeout, uint32_t timer_id,
                                     uint32_t data, const void *param);

/**
 * @brief     Gap initialize callback.
 * @param[in] is_timeout    True means timeout trigger.
 * @param[in] timer_id      Gap timer id
 * @param[in] index         Index in the #bt_gap_le_init_table.
 * @param[in] packet        Received hci packet.
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 *            callback #BT_POWER_ON_CNF to UT after process finished.
 */
bt_status_t bt_gap_le_init_proc(uint32_t is_timeout, uint32_t timer_id,
                                uint32_t index, const void *packet);

/**
 * @brief     Set random address callback.
 * @param[in] is_timeout    True means timeout trigger.
 * @param[in] timer_id      Gap timer id
 * @param[in] packet        Received hci packet.
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 *            callback #BT_GAP_LE_SET_RANDOM_ADDRESS_CNF to UT after process finished.
 */
bt_status_t bt_gap_le_set_random_address_proc(uint32_t is_timeout, uint32_t timer_id,
                                              uint32_t unused, const void *packet);

/**
 * @brief     Set white list callback.
 * @param[in] is_timeout    True means timeout trigger.
 * @param[in] timer_id      Gap timer id
 * @param[in] packet        Received hci packet.
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 *            callback #BT_GAP_LE_SET_WHITE_LIST_CNF to UT after process finished.
 */
bt_status_t bt_gap_le_set_white_list_proc(uint32_t is_timeout, uint32_t timer_id,
                                          uint32_t unused, const void *packet);

/**
 * @brief     Set advertising callback.
 * @param[in] is_timeout    True means timeout trigger.
 * @param[in] timer_id      Gap timer id
 * @param[in] packet        Received hci packet.
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 *            callback #BT_GAP_LE_SET_ADVERTISING_CNF to UT after process finished.
 */
bt_status_t bt_gap_le_set_advertising_proc(uint32_t is_timeout, uint32_t timer_id,
                                           uint32_t enable, const void *packet);

/**
 * @brief     Set scan callback.
 * @param[in] is_timeout    True means timeout trigger.
 * @param[in] timer_id      Gap timer id
 * @param[in] enable        #BT_HCI_CMD_LE_SET_SCAN_ENABLE packet
 * @param[in] packet        Received hci packet or #BT_HCI_CMD_LE_SET_SCAN_PARAMETERS
 *                          packet if timer_id is #BT_GAP_LE_EVENT_INVALID.
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 *            callback #BT_GAP_LE_SET_SCAN_CNF to UT after process finished.
 */
bt_status_t bt_gap_le_set_scan_proc(uint32_t is_timeout, uint32_t timer_id,
                                    uint32_t enable, const void *packet);

bt_status_t bt_gap_le_pairing_user_input_rsp_proc(uint32_t is_timeout, uint32_t timer_id,
                                                  uint32_t unused1, const void *unused2);

/**
 * @brief     Connection callback.
 * @param[in] is_timeout    True means timeout trigger.
 * @param[in] timer_id      Gap timer id
 * @param[in] packet        Received hci packet.
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 *            callback #BT_GAP_LE_CONNECT_CNF, #BT_GAP_LE_CONNECT_CANCEL_CNF or
 *            #BT_GAP_LE_DISCONNECT_CNF to UT after process finished.
 */
bt_status_t bt_gap_le_connection_proc(uint32_t is_timeout, uint32_t timer_id,
                                      uint32_t unused, const void *packet);

/**
 * @brief     Connection upodate callback.
 * @param[in] is_timeout        True means timeout trigger.
 * @param[in] timer_id          Gap timer id
 * @param[in] l2cap_cmd_code    L2cap signaling command opcode
 * @param[in] packet            Received hci packet.
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 *            callback #BT_GAP_LE_CONNECTION_UPDATE_CNF to UT after process finished.
 *            callback #BT_GAP_LE_CONNECTION_UPDATE_IND to UT after connection parameter updated.
 */
bt_status_t bt_gap_le_connection_update_proc(uint32_t is_timeout, uint32_t timer_id,
                                             uint32_t l2cap_cmd_code, const void *packet);

/**
 * @brief     Read rssi callback.
 * @param[in] is_timeout    True means timeout trigger.
 * @param[in] timer_id      Gap timer id
 * @param[in] packet        Received hci packet.
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 *            callback #BT_GAP_LE_READ_RSSI_CNF to UT after process finished.
 */
bt_status_t bt_gap_le_read_rssi_proc(uint32_t is_timeout, uint32_t timer_id,
                                     uint32_t unused, const void *packet);

/**
 * @brief     Update data length callback.
 * @param[in] is_timeout    True means timeout trigger.
 * @param[in] timer_id      Gap timer id
 * @param[in] packet        Received hci packet.
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 *            callback #BT_GAP_LE_UPDATE_DATA_LENGTH_CNF to UT after process finished.
 */
bt_status_t bt_gap_le_update_data_length_proc(uint32_t is_timeout, uint32_t timer_id,
                                              uint32_t unused, const void *packet);

/**
 * @brief     Read remote used features in slave.
 * @param[in] is_timeout    True means timeout trigger.
 * @param[in] timer_id      Gap timer id
 * @param[in] packet        Received hci packet.
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 */
bt_status_t bt_gap_le_slave_read_remote_used_features_proc(uint32_t is_timeout, uint32_t timer_id,
    uint32_t timer_data, const void *packet);

#ifdef BT_USE_DISCONNECT_0X3E_ENHANCE
/**
 * @brief     Read remote used features.
 * @param[in] is_timeout    True means timeout trigger.
 * @param[in] timer_id      Gap timer id
 * @param[in] packet        Received hci packet.
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 */
bt_status_t bt_gap_le_read_remote_used_features_proc(uint32_t is_timeout, uint32_t timer_id,
                                                     uint32_t timer_data, const void *packet);

/**
 * @brief     Read remote used features.
 * @note      This api is only be used on receiving #BT_HCI_SUBEVT_LE_CONNECTION_COMPLETE event.
 *            Just for handling disconnect 0x3e problem.
 * @param[in] handle        connection_handle
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 *            #BT_HCI_SUBEVT_LE_READ_REMOTE_USED_FEATURES_COMPLETE after remote
 *            used features command finished and the connection is normal.
 */
bt_status_t bt_gap_le_read_remote_used_features(
    uint32_t handle);
#endif

/**
 * @brief     Set scan callback.
 * @param[in] is_timeout    True means timeout trigger.
 * @param[in] timer_id      Gap timer id
 * @param[in] enable        #BT_HCI_CMD_LE_SET_SCAN_ENABLE packet
 * @param[in] packet        Received hci packet or #BT_HCI_CMD_LE_SET_SCAN_PARAMETERS
 *                          packet if timer_id is #BT_GAP_LE_EVENT_INVALID.
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 *            callback #BT_GAP_LE_SET_SCAN_CNF to UT after process finished.
 */
bt_status_t bt_gap_le_phy_proc(uint32_t is_timeout, uint32_t timer_id,
                               uint32_t unused, const void *packet);

bt_status_t bt_gap_le_extended_advtersing_event_proc(uint32_t is_timeout, uint32_t timer_id,
                                                     uint32_t data, const void *param);


bt_status_t bt_app_event_callback_wrap(bt_msg_type_t msg, bt_status_t status, void *buf);

bt_status_t bt_config_tx_power_level_by_version(bt_tx_power_config_version_t ver, void *tx_power_info);

bt_connection_t  *bt_gap_le_find_connection(const bt_bd_addr_t *address);

bt_status_t bt_gap_le_request_peer_sca(bt_handle_t handle);

bool bt_gap_le_cmd_is_rho_by_opcode(bt_hci_cmd_op_t opcode, uint8_t *payload);

#ifdef __cplusplus
}
#endif

#endif /* __BT_GAP_LE_INTERNAL_H__ */

