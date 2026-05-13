/* Copyright Statement:
 *
 * (C) 2021  Airoha Technology Corp. All rights reserved.
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
/* Airoha restricted information */

#ifndef __BT_L2CAP_LE_CBFCM_H__
#define __BT_L2CAP_LE_CBFCM_H__

#include "bt_l2cap_le.h"
#include "bt_l2cap_le_coc.h"

#define CBFCM_FLOW_CONTROL_AUTO        0
#define CBFCM_FLOW_CONTROL_MANUAL      1


typedef uint8_t bt_l2cap_le_cbfcm_conn_req_failed_reason;
#define BT_L2CAP_LE_CBFCM_CONN_REQ_FAILED_DUE_TO_INVALID_RESPONSE_FROM_REMOTE         0x00
#define BT_L2CAP_LE_CBFCM_CONN_REQ_REFUSED_BY_REMOTE_PSM_NOT_SUPPORT                  0x02
#define BT_L2CAP_LE_CBFCM_CONN_REQ_REFUSED_BY_REMOTE_RESOURCE_NOT_ENOUGH              0x04
#define BT_L2CAP_LE_CBFCM_CONN_REQ_REFUSED_BY_REMOTE_INSUFFICIENT_AUTHENTICAIOTN      0x05
#define BT_L2CAP_LE_CBFCM_CONN_REQ_REFUSED_BY_REMOTE_INSUFFICIENT_AUTHORIZATION       0x06
#define BT_L2CAP_LE_CBFCM_CONN_REQ_REFUSED_BY_REMOTE_INSUFFICIENT_ENC_KEY_SIZE        0x07
#define BT_L2CAP_LE_CBFCM_CONN_REQ_REFUSED_BY_REMOTE_INSUFFICIENT_ENC                 0x08
#define BT_L2CAP_LE_CBFCM_CONN_REQ_REFUSED_BY_REMOTE_UNACCEPTABLE_PARAMETERS          0x0B


typedef uint8_t bt_l2cap_le_cbfcm_disconnect_reason;
#define BT_L2CAP_LE_CBFCM_CHANNEL_DISCONNECTED_DUE_TO_LOCAL_REQUEST                   0x00
#define BT_L2CAP_LE_CBFCM_CHANNEL_DISCONNECTED_DUE_TO_DUPLICATED_CID                  0x01
#define BT_L2CAP_LE_CBFCM_CHANNEL_DISCONNECTED_DUE_TO_CREDIT_OVERFLOW                 0x02
#define BT_L2CAP_LE_CBFCM_CHANNEL_DISCONNECTED_DUE_TO_CREDIT_UNDERFLOW                0x03
#define BT_L2CAP_LE_CBFCM_CHANNEL_DISCONNECTED_DUE_TO_REMOTE_REQUEST                  0x05
#define BT_L2CAP_LE_CBFCM_CHANNEL_DISCONNECTED_DUE_TO_INVALID_FRAME_RECEIVED          0x06

#define BT_L2CAP_CBFCM_INITIAL_CREDIT       20
#define BT_L2CAP_CBFCM_CREDIT_THRESHOLD     10
#define BT_L2CAP_CBFCM_CREDIT_INCREASE      (BT_L2CAP_CBFCM_INITIAL_CREDIT - BT_L2CAP_CBFCM_CREDIT_THRESHOLD)
#define BT_L2CAP_CBFCM_MINIMUM_MTU          23
#define BT_L2CAP_CBFCM_MINIMUM_MPS          23

#define BT_L2CAP_CBFCM_SUPPRTED_MTU                780     //must >= BT_L2CAP_CBFCM_MINIMUM_MTU
#define BT_L2CAP_CBFCM_SUPPRTED_MPS                23      //must >= BT_L2CAP_CBFCM_MINIMUM_MPS
#define BT_L2CAP_CBFCM_MAXIMUM_SUPPORTED_MTU       0xFFF   //this is for PTS



#define BT_L2CAP_CBFCM_CONN_REQ_RESULT_SUCCESSFUL                               0x0000
#define BT_L2CAP_CBFCM_CONN_REQ_RESULT_REFUSED_SPSM_NOT_SUPPORT                 0x0002
#define BT_L2CAP_CBFCM_CONN_REQ_RESULT_REFUSED_RESOURCE_NOT_ENOUGH              0x0004
#define BT_L2CAP_CBFCM_CONN_REQ_RESULT_REFUSED_INSUFFICIENT_AUTHENTICAIOTN      0x0005
#define BT_L2CAP_CBFCM_CONN_REQ_RESULT_REFUSED_INSUFFICIENT_AUTHORIZATION       0x0006
#define BT_L2CAP_CBFCM_CONN_REQ_RESULT_REFUSED_INSUFFICIENT_ENC_KEY_SIZE        0x0007
#define BT_L2CAP_CBFCM_CONN_REQ_RESULT_REFUSED_INSUFFICIENT_ENC                 0x0008
#define BT_L2CAP_CBFCM_CONN_REQ_RESULT_REFUSED_INVALID_CID                      0x0009
#define BT_L2CAP_CBFCM_CONN_REQ_RESULT_REFUSED_CID_ALLOCATED                    0x000A
#define BT_L2CAP_CBFCM_CONN_REQ_RESULT_REFUSED_UNACCEPTABLE_PARAMETERS          0x000B

typedef uint8_t le_cbfcm_event;
#define BT_L2CAP_LE_CBFCM_CHANNEL_CONNECTED                       0x00        //parameter:    bt_l2cap_le_cbfcm_channel_connected_evt_t
#define BT_L2CAP_LE_CBFCM_CONNECTION_REQUEST_FAILED               0x01        //parameter:    bt_l2cap_le_cbfcm_conn_req_failed_evt_t
#define BT_L2CAP_LE_CBFCM_CHANNEL_DISCONNECTED                    0x02        //parameter:    bt_l2cap_le_cbfcm_channel_disconnected_evt_t

typedef void (* le_cbfcm_evt_cb)(le_cbfcm_event event, const void *parameter);

typedef struct {
    bt_l2cap_le_coc_t   coc;
    psm_rx_proc         psm_rx_proc;
    le_cbfcm_evt_cb     evt_callback;
    uint8_t            *rx_sdu_buf;
    uint16_t            rx_sdu_shortage;
    uint16_t            rx_sdu_offset;
    uint16_t            rx_credit;
    uint16_t            tx_credit;
    uint8_t             flow_control_status;
} bt_l2cap_le_cbfcm_t;


typedef struct {
    bt_l2cap_le_cbfcm_t    *channel;
    uint8_t                 is_active;          //indicates whether this connected event is invoked by our side
} bt_l2cap_le_cbfcm_channel_connected_evt_t;

typedef struct {
    bt_handle_t conn_handle;
    uint8_t     reason;                     //bt_l2cap_le_cbfcm_conn_req_failed_reason
} bt_l2cap_le_cbfcm_conn_req_failed_evt_t;

typedef struct {
    bt_l2cap_le_cbfcm_t    *channel;
    uint8_t                 reason;         //bt_l2cap_le_cbfcm_disconnect_reason
} bt_l2cap_le_cbfcm_channel_disconnected_evt_t;


bt_status_t bt_l2cap_le_cbfcm_increase_psm_instance(
    void                   *psm_control_block,
    bt_l2cap_le_psm_value   le_psm,
    psm_rx_proc             rx_proc,
    le_cbfcm_evt_cb         evt_callback);

bt_status_t bt_l2cap_le_cbfcm_psm_connect(
    bt_connection_t *conn,
    uint16_t le_psm);

bt_status_t bt_l2cap_le_cbfcm_disconnect_channel(
    uint16_t conn_handle,
    uint16_t cid);

bt_status_t bt_l2cap_le_cbfcm_send_data(
    uint16_t conn_handle,
    uint16_t cid,
    uint16_t length,
    uint8_t *buf);

bt_status_t bt_l2cap_le_cbfcm_set_credit_return_policy(
    uint16_t conn_handle,
    uint16_t cid,
    bool auto_return_credit,
    bool reset_credit);


bt_status_t bt_l2cap_le_cbfcm_manual_send_credit(
    uint16_t conn_handle,
    uint16_t cid,
    uint16_t credit);


#endif  //__BT_L2CAP_LE_CBFCM_H__


