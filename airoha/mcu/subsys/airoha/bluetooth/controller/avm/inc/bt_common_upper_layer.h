/* Copyright Statement:
 *
 * (C) 2024  Airoha Technology Corp. All rights reserved.
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
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
 * RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
 * TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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

#ifndef __BT_COMMON_UPPER_LAYER_H__
#define __BT_COMMON_UPPER_LAYER_H__

//#include "bt_config.h"
//#include "bt_type_def.h"
//#include "bt_system.h"
#include "stdbool.h"
#include "avm_memory.h"

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


typedef bt_linknode_t bt_hci_packet_linknode_t;

/*
 * BT packet memory allocateion with linknode.
 * [[bt_linknode_t][bt_hci_le_packet_t]].
 * Give a packet size, and return packet address.
 */
//uint8_t *bt_allocate_packet_with_node(bt_memory_packet_t type, uint32_t size);
//bt_hci_le_packet_t *bt_alloc_rx_packet_with_node(uint32_t size);

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


typedef enum {
    BT_QUEUE_TYPE_RX = 0,
    BT_QUEUE_TYPE_TX_ACL,
    BT_QUEUE_TYPE_TX_CMD,
    BT_QUEUE_TYPE_TX_IF_PACKET
} bt_hb_queue_type_t;

#define BT_HCI_ACL_HEADER_LENGTH       5  //sizeof(bt_uart_t) + sizeof(bt_hci_packet_acl_t) - 1
#define BT_HCI_CMD_HEADER_LENGTH       4  //sizeof(bt_uart_t) + sizeof(bt_hci_Packet_cmd_t) - 1
#define BT_HCI_EVT_HEADER_LENGTH       3  //sizeof(bt_uart_t) + sizeof(bt_hci_Packet_evt_t) - 1
#define BT_HCI_L2CAP_HEADER_LENGTH     4  //sizeof(bt_l2cap_cmd_t) -1


typedef uint16_t bt_hci_cmd_op_t;
typedef uint8_t bt_data_t[1];
typedef uint8_t bt_uart_t;
typedef uint8_t bt_hci_evt_op_t;

/**
 *  @brief      HCI command packet. Please refer to core spec 5.4.1 HCI Command Packet.
 */
BT_PACKED(
typedef struct {
    bt_hci_cmd_op_t     cmd_code; /**< Command code */
    uint8_t             length;   /**< Length of all of the parameters contained in this packet */
    bt_data_t           param;     /**< Parameters */
}) bt_hci_packet_cmd_t;

/**
 *  @brief      HCI event packet. Please refer to core spec 5.4.4 HCI Event Packet.
 */
BT_PACKED(
typedef struct {
    bt_hci_evt_op_t     evt_code; /**< Event code */
    uint8_t             length;   /**< Length of all of the parameters contained in this packet */
    bt_data_t           param;    /**< Parameters */
}) bt_hci_packet_evt_t;

/**
 *  @brief      HCI ACL packet. Please refer to core spec, Please refer to core spec 5.4.2 HCI ACL Data Packets.
 */
BT_PACKED(
typedef struct {
    uint16_t    handle: 12; /**< Handle */
    uint16_t    pb_flag: 2; /**< Packet boundary flag */
    uint16_t    bc_flag: 2; /**< Broadcast flag */
    uint16_t    length;     /**< Data total length */
    bt_data_t   data;       /**< Data */
}) bt_hci_packet_acl_t;

/**
 *  @brief      LE HCI packet.
 */
BT_PACKED(
typedef struct {
    bt_uart_t   indicator;                  /**< Indicate packet is CMD, ACL or EVT */
    BT_PACKED(
    union {
        bt_hci_packet_acl_t acl; /**< ACL packet */
        bt_hci_packet_cmd_t cmd; /**< Command packet */
        bt_hci_packet_evt_t evt; /**< Event packet */
    });
}) bt_hci_le_packet_t;


BT_PACKED(
typedef struct {
    bt_hci_cmd_op_t   cmd_code;
    uint8_t           length;
    const void        *param; /* This is a pointer */
}) bt_hci_cmd_t;


/**
 * @brief                  Timeout callback function prototype
 * @param[in] is_timeout   True : the timeout callback is invoked by timer timeout, False : the timeout callback is invoked by cancel timer
 * @param[in] timer_id     Timer ID
 * @param[in] data         User data saved in timer instance
 * @param[in] arg          Function argument passed when invoke bt_timer_cancel_and_callback()
 * @return                 If the operation was successful, the returned value is #BT_STATUS_SUCCESS, otherwise the returned value is #BT_STATUS_FAIL.
 */
typedef bt_status_t (*bt_timeout_callback_t)(uint32_t is_timeout,
                                             uint32_t timer_id,
                                             uint32_t data,
                                             const void *arg);



bool bt_is_bt_task_running(void);
bt_status_t bt_app_event_callback(bt_msg_type_t msg, bt_status_t status, void *buff);


uint8_t *bt_allocate_packet_with_node(bt_memory_packet_t type, uint32_t size);
#define BT_HCI_CMD_ALLOC(size)  ((bt_hci_le_packet_t *)bt_allocate_packet_with_node(BT_MEMORY_TX_BUFFER,(size)))

/**
 * @brief HCI packet indicator. Refer to the Bluetooth core specifications version 4.2 [Vol 4, Part A] UART Transport Layer, CH2 PROTOCOL.
 */
#define BT_UART_CMD     0x01
#define BT_UART_ACL     0x02
#define BT_UART_EVT     0x04
#define BT_UART_ISO     0x05

#define BT_HCI_EVT_COMMAND_COMPLETE                        0x0E
#define BT_HCI_CMD_RESET                          0x0C03
#define BT_HCI_CMD_ENABLE_DUT                                0x1803

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

#define BT_TEST_MODE_NONE_IND                   (BT_MODULE_SYSTEM | 0x0010)    /**< Buletooth device enter normal mode event with NULL payload. */
#define BT_TEST_MODE_DUT_MIX_ENABLE_IND         (BT_MODULE_SYSTEM | 0x0011)    /**< Buletooth device DUT mixed mode enable event with NULL payload. */
#define BT_TEST_MODE_DUT_ONLY_ENABLE_IND        (BT_MODULE_SYSTEM | 0x0012)    /**< Buletooth device DUT only mode enable event with NULL payload. */
#define BT_TEST_MODE_DUT_ACTIVE_IND             (BT_MODULE_SYSTEM | 0x0013)    /**< Buletooth device DUT active event with NULL payload. */
#define BT_TEST_MODE_RELAY_ENABLE_IND           (BT_MODULE_SYSTEM | 0x0014)    /**< Buletooth device relay mode enable event with NULL payload. */
#define BT_TEST_MODE_COMMAND_ENABLE_IND         (BT_MODULE_SYSTEM | 0x0015)    /**< Buletooth device command mode enable event with NULL payload. */
#define BT_TEST_MODE_DUT_INACTIVE_IND           (BT_MODULE_SYSTEM | 0x0016)    /**< Buletooth device DUT inactive event with NULL payload. */


#define BT_HCI_PACKET_ACL_SIZE(p)   (*(uint16_t *)((uint8_t *)(p)+3)+BT_HCI_ACL_HEADER_LENGTH)
#define BT_HCI_PACKET_CMD_SIZE(p)   (*(uint8_t *)((uint8_t *)(p)+3)+BT_HCI_CMD_HEADER_LENGTH)
#define BT_HCI_PACKET_EVT_SIZE(p)   (*(uint8_t *)((uint8_t *)(p)+2)+BT_HCI_EVT_HEADER_LENGTH)


#define BT_HCI_PKT_ALLOC(size)  ((bt_hci_le_packet_t *)bt_allocate_packet_with_node(BT_MEMORY_TX_BUFFER,(size)))
#define RELAY_BUFFER_SIZE 2048


/**
 * @brief                  Timeout callback function prototype
 * @param[in] is_timeout   True : the timeout callback is invoked by timer timeout, False : the timeout callback is invoked by cancel timer
 * @param[in] timer_id     Timer ID
 * @param[in] data         User data saved in timer instance
 * @param[in] arg          Function argument passed when invoke bt_timer_cancel_and_callback()
 * @return                 If the operation was successful, the returned value is #BT_STATUS_SUCCESS, otherwise the returned value is #BT_STATUS_FAIL.
 */
typedef bt_status_t (*bt_timeout_callback_t)(uint32_t is_timeout,
                                             uint32_t timer_id,
                                             uint32_t data,
                                             const void *arg);


/**
 * @brief                           Timeout instance structure
 */
typedef struct _bt_timer_t {
    struct _bt_timer_t *front;             /**<  link to next timer instance */
    uint32_t timer_id;              /**<  module id + module defined id */
    uint32_t data;                  /**<  user data */
    uint32_t time_ms;               /**<  timer timeout in ms */
    bt_timeout_callback_t cb;       /**<  timer timeout callback function */
    uint32_t flags_set;             /**<  bt timer related special flags set. */
} bt_timer_t;


bt_timer_t *bt_timer_find(uint32_t timer_id);
/**
 * @brief                   To start a timer, the timer will be inserted  into a timer list sorting by time_ms
 * @param[in] timer_id      Timer ID
 * @param[in] data          User data saved in timer instance
 * @param[in] time_ms       timer timeout in ms
 * @param[in] cb            timer timeout callback function
 * @return                  return  BT_STATUS_SUCCESS if add timer success, return BT_STATUS_OUT_OF_MEMORY if timer reach max count
 */
bt_status_t bt_timer_start(uint32_t timer_id, uint32_t data,
                           uint32_t time_ms, bt_timeout_callback_t cb);

#define BT_DRIVER_HCI_CMD_TIMEOUT   (8000)  //8s to avoid unnessary cmd timeout.



/**
 *  @brief      Command complete event.
 */
BT_PACKED(
typedef struct {
    uint8_t           num_hci_command_packets; /**< Number of HCI command packets which are allowed to be sent to the controller */
    bt_hci_cmd_op_t   cmd_code;                /**< Command code */
    void              *data;                   /**< Return parameters for the command specified in #cmd_code */
}) bt_hci_evt_command_complete_t;


extern void bt_driver_hw_semaphore_lock(void);
extern void bt_driver_hw_semaphore_unlock(void);
extern uint8_t *bt_driver_get_tx_power_config_table(void);




void *bt_memcpy(void *dest, const void *src, uint32_t size);
int bt_memcmp(const void *buf1, const void *buf2, uint32_t size);
void *bt_memset(void *buf, uint8_t ch, uint32_t size);

/* Hummingbird global variable */
//extern bt_hummingbird_t bt_hummingbird;

#if 0 

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

#endif 

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

