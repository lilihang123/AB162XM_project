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

#ifndef __BT_L2CAP_LE_COC_H__
#define __BT_L2CAP_LE_COC_H__

#include "bt_l2cap_le.h"


#define BT_L2CAP_LE_BASE_DYNAMIC_CID    0x0040


typedef uint16_t bt_l2cap_le_psm_value;
#define BT_L2CAP_PSM_OTS               0x0025
#define BT_L2CAP_PSM_EATT              0x0027

#define BT_L2CAP_CHANNEL_MODE_CBFCM         5
#define BT_L2CAP_CHANNEL_MODE_ECBFCM        6

typedef bt_status_t (* coc_rx_proc)(bt_connection_t *conn, const bt_l2cap_pdu_packet_t *packet, uint32_t length, void *channel);
typedef bt_status_t (* psm_rx_proc)(bt_connection_t *conn, const bt_l2cap_pdu_packet_t *packet, uint32_t length, void *channel);
typedef void (*acl_disc_proc)(void *channel);

typedef uint8_t l2cap_le_coc_state;
#define BT_L2CAP_LE_COC_IDLE_AVAILABLE          0x00
#define BT_L2CAP_LE_COC_CONNECTING              0x01
#define BT_L2CAP_LE_COC_CONNECTED               0x02
#define BT_L2CAP_LE_COC_DISCONNECTING           0x03

typedef struct {
    bt_linknode_t   next_node;
    coc_rx_proc     rx_proc;
    acl_disc_proc   disc_proc;
    uint16_t        conn_handle;
    uint16_t        local_cid;
    uint16_t        remote_cid;
    uint16_t        channel_local_mtu;
    uint16_t        channel_local_mps;
    uint16_t        channel_remote_mtu;
    uint16_t        channel_remote_mps;
    uint16_t        le_psm;
    uint8_t         le_coc_state;           //l2cap_le_coc_state
    uint8_t         l2cap_mode;             //bt_l2cap_channel_mode_t
} bt_l2cap_le_coc_t;



typedef bool (* coc_intercept_signal_cmd)(bt_connection_t *conn, const bt_l2cap_cmd_t *cmd, uint32_t length, bt_status_t *status);

bt_status_t bt_l2cap_le_increase_available_coc(
    uint16_t le_psm,
    uint8_t channel_mode,
    void *control_block,
    coc_rx_proc  rx_proc,
    acl_disc_proc   disc_proc);

bt_l2cap_le_coc_t *bt_l2cap_le_find_coc_by_remote_cid(
    uint16_t remote_cid,
    uint16_t conn_handle);

bt_l2cap_le_coc_t *bt_l2cap_le_find_next_coc(
    bt_l2cap_le_coc_t *cur_coc,
    uint16_t conn_handle,
    bt_l2cap_le_psm_value le_psm);

void bt_l2cap_le_coc_destroy(bt_connection_t *conn);

bool bt_l2cap_le_coc_intercept_signal_handle(
    bt_connection_t *const conn,
    const bt_l2cap_cmd_t *cmd,
    uint32_t length,
    bt_status_t *status);

bt_status_t bt_l2cap_le_coc_rx_proc(
    bt_connection_t *const conn,
    const bt_l2cap_pdu_packet_t *pdu,
    uint32_t length,
    uint16_t cid);

bt_status_t bt_l2cap_le_coc_send_data(uint16_t conn_handle, uint16_t cid, uint16_t length, uint8_t *buf, uint8_t l2cap_mode);

void bt_l2cap_le_disconnect_coc(
    bt_connection_t *conn,
    bt_l2cap_le_coc_t *coc);

bt_l2cap_le_coc_t *bt_l2cap_le_find_coc_by_local_cid(uint16_t cid);
bt_status_t bt_l2cap_le_coc_send_disconnect_response(
    bt_connection_t *conn,
    bt_l2cap_le_coc_t *coc,
    uint8_t identifier);

bt_l2cap_le_coc_t *bt_l2cap_le_get_available_coc(
    uint8_t channel_mode,
    uint16_t le_psm,
    uint8_t *le_psm_supported);
void bt_l2cap_le_locally_release_coc(bt_l2cap_le_coc_t *coc);
bt_l2cap_le_coc_t *bt_l2cap_le_search_next_coc(
    void *head,
    uint16_t conn_handle);


bt_status_t bt_l2cap_le_coc_send_credit_ind(uint16_t local_cid, bt_connection_t *conn, uint16_t credits);

#endif  //__BT_L2CAP_LE_COC_H__

