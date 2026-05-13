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

#ifndef __BT_L2CAP_LE_H__
#define __BT_L2CAP_LE_H__

#include "bt_hci_internal.h"
#include "bt_type_def.h"
#include "bt_l2cap_spec.h"

BT_EXTERN_C_BEGIN

/* Code(1 byte) + Identifier(1 byte) + Length(2 bytes) */
#define BT_L2CAP_SIGNAL_CMD_HEADER_LENGTH       4

#define BT_L2CAP_PDU_TO_L2CAP_PACKET(p) ((bt_l2cap_packet_t *)((uint8_t *)(p)-BT_HCI_L2CAP_HEADER_LENGTH))
#define BT_L2CAP_SM_TO_L2CAP_PACKET(p)  BT_L2CAP_PDU_TO_L2CAP_PACKET(p)
#define BT_L2CAP_ATT_TO_L2CAP_PACKET(p) BT_L2CAP_PDU_TO_L2CAP_PACKET(p)

#define BT_L2CAP_LE_PDU_ALLOC(size)    \
        ((void *)((uint8_t *)BT_HCI_ACL_ALLOC((size)+BT_HCI_L2CAP_HEADER_LENGTH)+ \
            BT_HCI_L2CAP_HEADER_LENGTH))

#define BT_L2CAP_IS_ALLOCATED_PACKET_VALID(p)      BT_IS_ALLOCATED_PACKET_VALID(BT_HCI_L2CAP_TO_PACKET(p))
#define BT_L2CAP_LE_IS_ALLOCATED_PDU_VALID(p)      BT_IS_ALLOCATED_PACKET_VALID(BT_HCI_L2CAP_TO_PACKET(BT_L2CAP_PDU_TO_L2CAP_PACKET(p)))

/*     8bits           16bits           8bits
 * +----------+----------+----------+----------+
 * |Module ID |   Indication Type   | Ind ID   |
 * +----------+----------+----------+----------+
 */
#define BT_L2CAP_INDICATION_TYPE                0x00FFFF00
#define BT_L2CAP_CONN_UPDATE_REQ_IND \
        (BT_MODULE_L2CAP | BT_L2CAP_INDICATION_TYPE | 0x01)
#ifdef BT_BQB
#define BT_L2CAP_BQB_DISCONNECT_REQ_IND \
        (BT_MODULE_L2CAP | BT_L2CAP_INDICATION_TYPE | 0x02)
#endif

/*     8bits      8bits           16bits
 * +----------+----------+----------+----------+
 * |Module ID |Identifier| Connection Handle   |
 * +----------+----------+----------+----------+
 */
#define BT_L2CAP_TIMERID_IDENTIFIER_OFFSET  16
#define BT_L2CAP_GET_TIMER_ID(idntifier, conn_handle) \
        (BT_MODULE_L2CAP | (idntifier << BT_L2CAP_TIMERID_IDENTIFIER_OFFSET) | (conn_handle))

#define BT_L2CAP_GET_TIMER_GROUP(conn_handle) (BT_MODULE_L2CAP | (conn_handle))

#define BT_L2CAP_MODULE_ID_MASK                 0xFF000000
#define BT_L2CAP_CONNECTION_HANDLE_MASK         0x0000FFFF

#define BT_L2CAP_GET_MODULEID_FROM_TIMERID(timerid) \
        ((timerid) & BT_L2CAP_MODULE_ID_MASK)
#define BT_L2CAP_GET_CONNECTION_HANDLE_FROM_TIMERID(timerid) \
        ((timerid) & BT_L2CAP_CONNECTION_HANDLE_MASK)

typedef bt_timeout_callback_t bt_l2cap_event_callback_t;

#define BT_L2CAP_GET_CMD_REJ_LENGTH(reason) \
        ((reason==BT_L2CAP_CMD_REJ_COMMAND_NOT_UNDERSTAND)? 2: ((reason==BT_L2CAP_CMD_REJ_COMMAND_NOT_UNDERSTAND)? 4:6))

typedef struct {
    uint8_t         identifier;
    uint16_t        connection_handle;
    bt_l2cap_cmd_conn_param_update_req_t param;
} bt_l2cap_ind_conn_param_update_t;

/**
 * @brief     Send the received l2cap packet.
 * @param[in] conn          Connection
 * @param[in] packet        L2cap packet
 * @param[in] length        Packet length
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 */
bt_status_t bt_l2cap_rx_loopback(
    bt_connection_t *const conn,
    const bt_l2cap_packet_t *packet,
    uint32_t length);

/**
 * @brief     Check the connection update parameters is valid.
 * @param[in] param         Connection update parameters.
 * @return    #true means parameters are valid, #false are invalid.
 */
bool bt_l2cap_check_valid_conn_update_params(
    const bt_l2cap_cmd_conn_param_update_req_t *param);

/**
 * @brief     L2cap passes a indication to UL for triggering UL to do something.
 * @note      Timeout trigger and only for BQB test.
 * @param[in] is_timeout    Only true.
 * @param[in] timer_id      L2cap timer id
 * @param[in] packet        NULL
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 */
bt_status_t bt_l2cap_bqb_conn_param_update_proc(
    uint32_t is_timeout,
    uint32_t timer_id,
    uint32_t unused,
    const void *packet);

/**
 * @brief     L2cap handle received signaling command.
 * @param[in] conn          Connection
 * @param[in] cmd           L2cap signaling command
 * @param[in] length        L2cap signaling command packet length
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 */
bt_status_t bt_l2cap_le_signal_handle(
    bt_connection_t *const conn,
    const bt_l2cap_cmd_t *cmd,
    uint32_t length);

/**
 * @brief     L2cap handle received packet.
 * @param[in] conn          Connection
 * @param[in] packet        L2cap packet
 * @param[in] length        L2cap packet length
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 */
bt_status_t bt_l2cap_le_rx_proc(
    bt_connection_t *const conn,
    const bt_l2cap_packet_t *packet,
    uint32_t length);

/**
 * @brief     Send l2cap packet.
 * @param[in] conn          Connection
 * @param[in] channel       Should be #BT_L2CAP_CHANNEL_ATT, #BT_L2CAP_CHANNEL_SM
 *                          or #BT_L2CAP_CHANNEL_SIGNAL.
 * @param[in] packet        L2cap pdu packet
 * @param[in] length        L2cap pdu packet length
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 */
bt_status_t bt_l2cap_le_send(
    bt_connection_t *const conn,
    uint16_t channel,
    const bt_l2cap_pdu_packet_t *packet,
    uint32_t length);

/**
 * @brief     Send l2cap signaling command packet.
 * @param[in] conn          Connection
 * @param[in] cmd           L2cap signaling command
 * @param[in] callback      Callback or NULL if not required.
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 */
bt_status_t bt_l2cap_le_cmd_send(
    bt_connection_t *const conn,
    const bt_l2cap_cmd_t *cmd,
    const bt_l2cap_event_callback_t callback);

/**
 * @brief     Send l2cap command reject.
 * @param[in] conn          Connection
 * @param[in] param         Command reject packet
 * @param[in] identifier    Identifier is same with the identifier field in
 *                          the received corresponding request.
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 */
bt_status_t bt_l2cap_le_command_reject(
    bt_connection_t *conn,
    const bt_l2cap_cmd_command_reject_t *param,
    const uint8_t identifier);

/**
 * @brief     Send l2cap connection parameter update request.
 * @param[in] conn          Connection
 * @param[in] param         Connection parameter update request packet
 * @param[in] callback      Callback
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 */
bt_status_t bt_l2cap_conn_param_update_req(
    bt_connection_t *conn,
    const bt_l2cap_cmd_conn_param_update_req_t *param,
    const bt_l2cap_event_callback_t callback);

/**
 * @brief     Send l2cap connection parameter update response.
 * @param[in] conn          Connection
 * @param[in] param         Connection parameter update response packet
 * @param[in] identifier    Identifier is same with the identifier field in
 *                          the received corresponding request.
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 */
bt_status_t bt_l2cap_conn_param_update_rsp(
    bt_connection_t *conn,
    const bt_l2cap_cmd_conn_param_update_rsp_t *param,
    const uint8_t identifier);

bt_status_t bt_l2cap_le_link_disconnect_notify(bt_connection_t *conn);

#ifdef BT_EATT_ENABLE
uint8_t bt_l2cap_le_allocate_sig_id(bt_connection_t *conn);
#endif

BT_EXTERN_C_END

#endif /* __BT_L2CAP_H__ */

