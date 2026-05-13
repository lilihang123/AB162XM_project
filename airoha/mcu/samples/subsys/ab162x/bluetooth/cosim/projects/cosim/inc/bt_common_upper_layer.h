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

#ifndef __BT_COMMON_UPPER_LAYER_H__
#define __BT_COMMON_UPPER_LAYER_H__

#include "bt_config.h"
#include "bt_type_def.h"
#include "bt_system.h"
#include "stdbool.h"
#include "bt_memory.h"

BT_EXTERN_C_BEGIN

#ifndef BT_TO_UPPERS
#define BT_TO_UPPERS(ch)  (((ch) >= 'a' && (ch) <= 'z') ? ((ch) - 'a' + 'A') : (ch))
#endif

#define BT_IS_MODULE_MATCH(st, mo)      (((st) & BT_MODULE_NUM)==(mo))  /**< Check st's module is same as mo. */

#define BT_HCI_STATUS_MASK              0x000000FFU

#define BT_GET_CONN_FROM_NODE(p)    ((bt_connection_t *)((uint8_t *)(p)-offsetof(bt_connection_t,next_node)))
#ifdef BT_LE_AUDIO_ENABLE
#define BT_GET_CONN_FROM_CIS_NODE(p)    ((bt_cis_connection_t *)((uint8_t *)(p)-offsetof(bt_cis_connection_t,next_node)))
#endif

#define BT_GET_QUEUE_FROM_TX_CON_QUEUE_NODE(p)  ((bt_linknode_t *)((uint8_t *)(p)+offsetof(bt_tx_queue_t,queue)))
#define BT_GET_CON_FROM_TX_CON_QUEUE(p) ((bt_connection_t *)((uint8_t *)(p)-offsetof(bt_connection_t,tx_con_queue)))

#define BT_QUEUE_INVALID            NULL

#define BT_QUEUE_TX_ALL             (&(bt_mm_cb.tx_all_queue))
#define BT_QUEUE_TX_CMD             (&(bt_mm_cmd_queue.queue))
#define BT_QUEUE_TX_CON(CON)        (&((CON)->tx_con_queue).queue)
#define BT_QUEUE_TX_IF_PACKET       (&(bt_mm_tx_if_packet_queue.queue))

#define BT_QUEUE_TX_CMD_NODE        ((bt_linknode_t *)&bt_mm_cmd_queue)
#define BT_QUEUE_TX_CON_NODE(CON)   ((bt_linknode_t *)&((CON)->tx_con_queue))
#define Bt_QUEUE_TX_IF_PACKET_NODE  ((bt_linknode_t *)&bt_mm_tx_if_packet_queue)



#ifdef __MTK_AWS_MCE_ENABLE__
extern bt_linknode_t g_rho_rx_queue;
#define BT_QUEUE_RHO_RX             (&g_rho_rx_queue)
#endif

#define BT_QUEUE_RX                 (&(bt_mm_cb.rx_queue))
#define BT_QUEUE_EMPTY(q)           ((q)->front == BT_QUEUE_INVALID)

#define BT_QUEUE_POP_FRONT(q)       (bt_linknode_remove_node(q, BT_NODE_FRONT))
#define BT_QUEUE_POP_BACK(q)        (bt_linknode_remove_node(q, BT_NODE_BACK))
#define BT_QUEUE_PUSH_FRONT(q,item) (bt_linknode_insert_node(q, (item), BT_NODE_FRONT))
#define BT_QUEUE_PUSH_BACK(q, item) (bt_linknode_insert_node(q, (item), BT_NODE_BACK))

/*
 * BT packet memory allocateion with linknode.
 * [[bt_linknode_t][bt_hci_le_packet_t]].
 * Give a packet size, and return packet address.
 */
uint8_t *bt_allocate_packet_with_node(bt_memory_packet_t type, uint32_t size);
bt_hci_le_packet_t *bt_alloc_rx_packet_with_node(uint32_t size);

#define BT_IS_ALLOCATED_PACKET_VALID(packet)    ((packet) != NULL)

/* This macro is used to give total size of two continuous memory packet. */
#ifdef BT_DRBUG
#define BT_TOTAL_SIZE_OF_TWO_PACKET(packet1, packet2)   ((packet1)+(packet2)+sizeof(bt_hci_packet_linknode_t)+sizeof(bt_mm_header_t)+2);/* +2 is for footer 2 bytes*/
#else
#define BT_TOTAL_SIZE_OF_TWO_PACKET(packet1, packet2)   ((packet1)+(packet2)+sizeof(bt_hci_packet_linknode_t)+sizeof(bt_mm_header_t));
#endif

/* Give a packet address, and call free include linknode. */
#define BT_FREE_PACKET_WITH_NODE(type, ptr)         (bt_mm_free_packet(type, (char *)(ptr) - sizeof(bt_hci_packet_linknode_t)))
#define BT_GET_NODE_FROM_PACKET(ptr)                ((bt_linknode_t*) ((char *)(ptr) - sizeof(bt_hci_packet_linknode_t)) )
#define BT_GET_PACKET_FROM_NODE(ptr)                ((void *) ((char *)(ptr) + sizeof(bt_hci_packet_linknode_t)) )

/* Hummingbird global variable */
extern bt_hummingbird_t bt_hummingbird;

BT_PACKED(
typedef struct {
    uint16_t handle;
    uint32_t offset_nclk;
    uint16_t offset_intra;
}) bt_clock_offset_info_t;

BT_PACKED(
typedef struct {
    bt_clock_offset_info_t *base_addr;
    uint8_t link_num;
}) bt_avm_clk_offset_cmd_t;

void bt_remove_link_node(bt_linknode_t *head, bt_linknode_t *node);

extern uint32_t bt_drvier_get_timconn_base(void);

bt_connection_t *bt_find_conn_by_handle(uint32_t handle, bool remove);
bt_tx_queue_t *bt_find_tx_queue_by_handle(uint32_t handle);

bool bt_is_connection_existing(const bt_addr_t *peer_address);

bool bt_is_hci_cmd_connection_oriented(uint32_t cmd_code);

bt_status_t bt_get_status_from_hci_event_cc(const void *packet);

void bt_reverse_key(uint8_t *dst, const uint8_t *src, uint32_t length);

uint8_t *bt_copy_and_increase(uint8_t *dst, const uint8_t *src, uint32_t length);

void bt_xor_16_byte(bt_key_t output, const bt_key_t input);
extern void bt_module_handle_process(void);
extern void bt_module_add_to_free_list(bt_linknode_t *node);
extern void bt_module_delete_from_free_list(bt_linknode_t *node);
/**
 * @brief                   This function initialize the profiles' context
 * @return                  None
 */
void bt_profiles_init(void);

/*****************************************************************************
 * FUNCTION
 *  bt_store_little_endian_from_16
 * DESCRIPTION
 *  Store 16 bit value into a buffer in Little Endian format.
 * PARAMETERS
 *  buff            [OUT]
 *  le_value        [IN]
 * RETURNS
 *  void
 *****************************************************************************/
void bt_store_little_endian_from_16(uint8_t *buff, uint16_t le_value);
/*****************************************************************************
 * FUNCTION
 *  bt_store_little_endian_from_32
 * DESCRIPTION
 *  Store 32 bit value into a buffer in Little Endian format.
 * PARAMETERS
 *  buff            [OUT]
 *  le_value        [IN]
 * RETURNS
 *  void
 *****************************************************************************/
void bt_store_little_endian_from_32(uint8_t *buff, uint32_t le_value);
/*****************************************************************************
 * FUNCTION
 *  bt_retrieve_little_endian_to_16
 * DESCRIPTION
 *  Retrieve a 16-bit number from the given buffer. The number
 *  is in Little-Endian format.
 * PARAMETERS
 *  ptr     [IN]
 * RETURNS
 *  16-bit number.
 *****************************************************************************/
uint16_t bt_retrieve_little_endian_to_16(const uint8_t *ptr);
/*****************************************************************************
 * FUNCTION
 *  bt_retrieve_little_endian_to_32
 * DESCRIPTION
 *  Retrieve a 32-bit number from the given buffer. The number
 *  is in Little-Endian format.
 * PARAMETERS
 *  ptr     [IN]
 * RETURNS
 *  32-bit number.
 *****************************************************************************/
uint32_t bt_retrieve_little_endian_to_32(const uint8_t *ptr);

/*****************************************************************************
* FUNCTION
*  bt_endian_order_swap
* DESCRIPTION
*  Swap the endian order from src to dest. This can swap little-endian to big
*  -endian or in contrast. Len only support 2 or 4 btyes
* PARAMETERS
*  dest     [IN]
*  src      [IN]
*  len      [IN]
* RETURNS
*  bool to indiacte whether the len is supported.
*****************************************************************************/
bool bt_endian_order_swap(uint8_t *dest, const uint8_t *src, uint8_t len);

BT_EXTERN_C_END

#endif /* __BT_COMMON_UPPER_LAYER_H__ */

