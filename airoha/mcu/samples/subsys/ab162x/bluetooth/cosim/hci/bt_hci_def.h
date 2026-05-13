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

#ifndef __BT_HCI_DEF_H__
#define __BT_HCI_DEF_H__

#include "bt_hci_spec.h"

/* For command complete or command status callback. */
/*
 * +---------+---------+-------------------+
 * |Module ID| Type A  | Command Code      |
 * +---------+---------+-------------------+
 */
#define BT_TIMER_HCI_TYPE_A_MASK  0x00000000

/* For general event or le meta event. */
/*
 * +---------+---------+---------+---------+
 * |Module ID| Type B  | Subevt  |Evt Code |
 * +---------+---------+-------------------+
 */
#define BT_TIMER_HCI_TYPE_B_MASK  0x00010000
#define BT_TIMER_HCI_TYPE_B_SUBEVT_OFFSET    8

#define BT_TIMER_HCI_INVALID_MASK 0x00FFFFFF

#define BT_HCI_EVENT_TYPE_A(cmd_code) \
        (BT_MODULE_HCI | BT_TIMER_HCI_TYPE_A_MASK | (cmd_code))

#define BT_HCI_EVENT_TYPE_B(index) \
        (BT_MODULE_HCI | BT_TIMER_HCI_TYPE_B_MASK | (index))

#define BT_HCI_EVENT_LE_META(evt_code)    \
        BT_HCI_EVT_LE_META_EVENT | \
        ((evt_code) << BT_TIMER_HCI_TYPE_B_SUBEVT_OFFSET)

#define BT_HCI_VENDOR_EVT_META(evt_code)  \
        BT_HCI_EVT_LE_VENDOR_EVENT | \
        ((evt_code) << BT_TIMER_HCI_TYPE_B_SUBEVT_OFFSET)

#ifdef __BT_HB_ENABLE_SLEEP_MODE__
#define BT_TIMER_HCI_SLEEP_MODE_MASK  0x00020000
#define BT_HCI_SLEEP_MODE_TIMER    \
        (BT_MODULE_HCI | BT_TIMER_HCI_SLEEP_MODE_MASK | 0x0000)

/*
 * default timer for host which thought
 * contorller has sleeped after no data exchange
 */
#define BT_HCI_SLEEP_MODE_DEFAULT_TIMEOUT      4000
#endif //__BT_HB_ENABLE_SLEEP_MODE__

#define BT_HCI_ACL_HEADER_LENGTH       5  //sizeof(bt_uart_t) + sizeof(bt_hci_packet_acl_t) - 1
#define BT_HCI_CMD_HEADER_LENGTH       4  //sizeof(bt_uart_t) + sizeof(bt_hci_Packet_cmd_t) - 1
#define BT_HCI_EVT_HEADER_LENGTH       3  //sizeof(bt_uart_t) + sizeof(bt_hci_Packet_evt_t) - 1
#ifdef BT_LE_AUDIO_ENABLE
#define BT_HCI_ISO_HEADER_LENGTH       5  //sizeof(bt_uart_t) + sizeof(bt_hci_Packet_iso_t) - 1
#endif
#define BT_HCI_L2CAP_HEADER_LENGTH     4  //sizeof(bt_l2cap_cmd_t) -1

/* "p" is pointer to #bt_packet_t. */
/* Example usage: BT_HCI_LE_PACKET_TO_EVENT(bt_hci_evt_command_complete_t, packet)->cmd_code. */
#define BT_HCI_LE_PACKET_TO_EVENT(__bt_hci_packet_evt_t,p)            ((__bt_hci_packet_evt_t *)((uint8_t *)(p) + BT_HCI_EVT_HEADER_LENGTH))
#define BT_HCI_LE_PACKET_TO_COMMAND(__bt_hci_packet_cmd_t,p)          ((__bt_hci_packet_cmd_t *)((uint8_t *)(p) + BT_HCI_CMD_HEADER_LENGTH))
#define BT_HCI_LE_PACKET_TO_EVENT_CC(__bt_hci_evt_cc_t,p)      ((__bt_hci_evt_cc_t *)((uint8_t *)(p)+6))
#define BT_HCI_LE_PACKET_TO_SUBEVENT_LE(__bt_hci_subevt_t,p)   ((__bt_hci_subevt_t *)((uint8_t *)(p)+4))

#define BT_HCI_LE_PACKET_TOTAL_SIZE(p) \
    (*(uint16_t *)((uint8_t *)(p)+5) + BT_HCI_ACL_HEADER_LENGTH + BT_HCI_L2CAP_HEADER_LENGTH)
#define BT_HCI_LE_PACKET_TOTAL_SIZE_IS_VALID(received_size) \
    ((received_size)>=(BT_HCI_ACL_HEADER_LENGTH + BT_HCI_L2CAP_HEADER_LENGTH - 2))
#define BT_HCI_PACKET_ACL_SIZE(p)   (*(uint16_t *)((uint8_t *)(p)+3)+BT_HCI_ACL_HEADER_LENGTH)
#define BT_HCI_PACKET_CMD_SIZE(p)   (*(uint8_t *)((uint8_t *)(p)+3)+BT_HCI_CMD_HEADER_LENGTH)
#define BT_HCI_PACKET_EVT_SIZE(p)   (*(uint8_t *)((uint8_t *)(p)+2)+BT_HCI_EVT_HEADER_LENGTH)
#define BT_HCI_PACKET_ACL_RX_IS_FIRST(p)    ((p)->acl.pb_flag == BT_HCI_PB_FIRST_FLUSH)
#ifdef BT_LE_AUDIO_ENABLE
#define BT_HCI_PACKET_ISO_SIZE(p)   (*(uint16_t *)((uint8_t *)(p)+3)+BT_HCI_ISO_HEADER_LENGTH)
#endif

#define BT_HCI_L2CAP_TO_PACKET(p)   ((bt_hci_le_packet_t *)((uint8_t *)(p)-BT_HCI_ACL_HEADER_LENGTH))

#define BT_HCI_CMD_ALLOC(size)  ((bt_hci_le_packet_t *)bt_allocate_packet_with_node(BT_MEMORY_TX_BUFFER,(size)))
#define BT_HCI_ACL_ALLOC(size)  \
        ((void *)((uint8_t *)bt_allocate_packet_with_node(BT_MEMORY_TX_BUFFER, \
        (size)+BT_HCI_ACL_HEADER_LENGTH)+BT_HCI_ACL_HEADER_LENGTH))
#define BT_HCI_PKT_ALLOC(size)  ((bt_hci_le_packet_t *)bt_allocate_packet_with_node(BT_MEMORY_TX_BUFFER,(size)))

#define BT_HCI_LE_MAXIMUM_DATA_LENGTH(__bt_hci_packet_cmd)                  (0xFF - sizeof(__bt_hci_packet_cmd) + 1)
#define BT_HCI_LE_FRAGMENT_DATA_PACKET_NUM(__bt_hci_packet_cmd,all_length)  ((all_length) / BT_HCI_LE_MAXIMUM_DATA_LENGTH(__bt_hci_packet_cmd) \
    + !!(((all_length) ? (all_length) : 1) % BT_HCI_LE_MAXIMUM_DATA_LENGTH(__bt_hci_packet_cmd )))

#endif /* __BT_HCI_DEF_H__ */
