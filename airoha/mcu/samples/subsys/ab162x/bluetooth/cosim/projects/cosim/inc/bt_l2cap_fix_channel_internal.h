/* Copyright Statement:
 *
 * (C) 2020  Airoha Technology Corp. All rights reserved.
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
#ifndef _BT_L2CAP_FIX_CHANNEL_INTERNAL_H
#define _BT_L2CAP_FIX_CHANNEL_INTERNAL_H

//#include "bt_gap_internal.h"
#include "bt_l2cap_fix_channel.h"

#define BT_L2CAP_FIX_CHANNEL_TYPE_NUM   2

#define BT_L2CAP_FIX_CHANNEL_GEN_TIMER_ID(connection_handle)          (BT_MODULE_L2CAP | (connection_handle))
#define BT_L2CAP_FIX_CHANNEL_GET_CONN_HANDLE_FROM_TIMER_ID(timer_id)  (uint16_t)((timer_id) & 0x0000FFFF)
#define BT_L2CAP_FIX_CHANNEL_DEFAULT_TIMEOUT        100

BT_PACKED(
typedef struct {
    bt_linknode_t node;
    bt_l2cap_fix_cid_t channel_id;
    bt_l2cap_fix_channel_callback_t callback;
})bt_l2cap_fix_channel_context_t;

typedef struct {
    bt_linknode_t le_fix_channel_list;
    bt_linknode_t bredr_fix_channel_list;
} bt_l2cap_fix_channel_context_struct;

typedef struct {
    uint16_t fix_cid_begin;
    uint16_t fix_cid_end;
    uint8_t mm_type;
    bt_linknode_t *fix_channel_list;
} bt_l2cap_fix_channel_info_t;



bt_l2cap_fix_channel_context_t *bt_l2cap_fix_channel_search(bt_l2cap_fix_channel_t type, bt_l2cap_fix_cid_t cid);
void bt_l2cap_fix_channel_link_status_notify(bt_gap_connection_t *conn, bt_status_t link_status);
bt_status_t bt_l2cap_fix_channel_rx_handle(bt_handle_t connection_handle, bt_l2cap_fix_channel_t type, \
                                           bt_l2cap_fix_cid_t cid, uint8_t *data, uint16_t length);
bool bt_l2cap_fix_channel_is_link(bt_gap_connection_t *conn);

#endif