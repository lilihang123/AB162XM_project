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

#ifndef __BT_MEMORY_H__
#define __BT_MEMORY_H__

//#include "bt_platform_internal.h"
//#include "bt_timer.h"
//#include "bt_system.h"

//BT_EXTERN_C_BEGIN

/**
 * @addtogroup Bluetooth
 * @{
 * @addtogroup Util
 * @{
 * @defgroup MM MM
 * @{
 * This document describes Memory Manager (MM) APIs.
 * MM is created for Hummingbird internal use only, it provide Tx/Rx packet, connection and Timer.
 * The memory pools should be allocated from outside of MM and assign to MM via initializtion API.
 *
 * @section bt_memory_api_usage How to use MM
 * - Initialize MM:
 *      @code
 *      static char timer_cb_buf[BT_CONTROL_BLOCK_SIZE_OF_TIMER];
 *      static char connection_cb_buf[BT_CONTROL_BLOCK_SIZE_OF_LE_CONNECTION];
 *      static char tx_buf[BT_TX_BUF_SIZE];
 *      static char rx_buf[BT_RX_BUF_SIZE];
 *
 *      bt_memory_init_packet(BT_MEMORY_TX_BUFFER,tx_buf,BT_TX_BUF_SIZE);
 *      bt_memory_init_packet(BT_MEMORY_RX_BUFFER,rx_buf,BT_RX_BUF_SIZE);
 *      bt_memory_init_control_block(BT_MEMORY_CONTROL_BLOCK_TIMER, timer_cb_buf, BT_CONTROL_BLOCK_SIZE_OF_TIMER);
 *      bt_memory_init_control_block(BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION, connection_cb_buf, BT_CONTROL_BLOCK_SIZE_OF_LE_CONNECTION);
 *      @endcode
 *
 * - Allocate and free Tx/Rx packet:
 *      @code
 *      char *tx_packet = bt_mm_allocate_packet(BT_MEMORY_TX_BUFFER, 12);
 *      char *rx_packet = bt_mm_allocate_packet(BT_MEMORY_RX_BUFFER, 12);
 *      bt_mm_free_packet(BT_MEMORY_TX_BUFFER, tx_packet);
 *      bt_mm_free_packet(BT_MEMORY_RX_BUFFER, rx_packet);
 *      @endcode
 *
 * - Allocate and free timer/connection:
 *      @code
 *      bt_timer_t *bt_timer = (bt_timer_t*)bt_mm_allocate_fixed_size_by_type(BT_MEMORY_CONTROL_BLOCK_TIMER);
 *      bt_connection_t bt_conn = (bt_connection_t*) bt_mm_allocate_fixed_size_by_type(BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION);
 *      bt_mm_free_fixed_size_by_type(BT_MEMORY_CONTROL_BLOCK_TIMER, bt_timer);
 *      bt_mm_free_fixed_size_by_type(BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION, bt_conn);
 *      @endcode
 *
 */

#define BT_MM                 0x1000

#define BT_MM_INIT_STATUS     0x0000
#define BT_MM_ALLOCATE_STATUS 0x0100
//----------------------------------------------
#define BT_MM_INIT_STATUS_OK                (BT_MM|BT_MM_INIT_STATUS|0x00)
#define BT_MM_INIT_STATUS_NOT_ALIGNED       (BT_MM|BT_MM_INIT_STATUS|0x01)
#define BT_MM_ALLOCATE_STATUS_OK            (BT_MM|BT_MM_ALLOCATE_STATUS|0x00)
#define BT_MM_ALLOCATE_STATUS_OOM           (BT_MM|BT_MM_ALLOCATE_STATUS|0x01)
typedef uint32_t bt_mm_st_t;
#define BT_MM_SIZE_MASK         0x3FFFFFFF
#define BT_MM_STATE_MASK        0xC0000000
#define BT_MM_SIZE_OFFSET       0
#define BT_MM_STATE_OFFSET      30
#define BT_MM_STATE_FREE        0U
#define BT_MM_STATE_USING       1U
#define BT_MM_SET_INFO(info, size, state)       ((info) = (((state) << BT_MM_STATE_OFFSET)|(size)))
#define BT_MM_SET_SIZE(info, size)              ((info) = (((info) & BT_MM_STATE_MASK)|((size) & BT_MM_SIZE_MASK)))
#define BT_MM_SET_STATE(info, state)            ((info) = (((state) << BT_MM_STATE_OFFSET)|((info) & BT_MM_SIZE_MASK)))
#define BT_MM_GET_SIZE(info)                    ((info) & BT_MM_SIZE_MASK)
#define BT_MM_GET_STATE(info)                   ((info) >>BT_MM_STATE_OFFSET)

#define BT_MM_MAX_SIZE         0xFFFF    /** 16bit maximum size **/
/**
 * @defgroup bt_memory_define Define
 * @{
 */
#ifdef BT_DEBUG
#define BT_MM_DBG_RECORD_ADD(type, num)             (bt_mm_cb.allocated_packets[(type)] += (num))
#define BT_MM_DBG_RECORD_DEL(type, num)             (bt_mm_cb.allocated_packets[(type)] -= (num))
#define BT_MM_DBG_RECORD_CLEAR(type)                (bt_mm_cb.allocated_packets[(type)] = 0)
#define BT_MM_DBG_WAIT_TO_FREE_RECORD_ADD(type, size) (bt_mm_cb.size_of_waiting_to_free[(type)] += (size))
#define BT_MM_DBG_WAIT_TO_FREE_RECORD_DEL(type, size) (bt_mm_cb.size_of_waiting_to_free[(type)] -= (size))
#define BT_MM_GET_WAIT_TO_FREE(type)                  (bt_mm_cb.size_of_waiting_to_free[(type)])
#define BT_MM_GET_WAIT_TO_FREE_CLEAR(type)            (bt_mm_cb.size_of_waiting_to_free[(type)] = 0)
#define BT_MM_DBG_RECORD_CB_NUM(type, num)          (bt_mm_cb.cb_num[(type)] = (num))
#define BT_MM_DBG_GET_CB_NUM(type)                  (bt_mm_cb.cb_num[(type)])
#define BT_MM_DBG_RECORD_CB_ALLOCATE(type)          (bt_mm_cb.allocated_cb[(type)] += 1)
#define BT_MM_DBG_RECORD_CB_FREE(type)              (bt_mm_cb.allocated_cb[(type)] -= 1)
#define BT_MM_DBG_PEEK_NUM(type)                    (bt_mm_cb.packet_peek[(type)])
#define BT_MM_DBG_PEEK_NUM_CLEAR(type)              (bt_mm_cb.packet_peek[(type)] = 0)
#define BT_MM_DBG_PEEK_NUM_SET(type, size)          (bt_mm_cb.packet_peek[(type)] = (size))
#else
#define BT_MM_DBG_RECORD_ADD(type, num)
#define BT_MM_DBG_RECORD_DEL(type, num)
#define BT_MM_DBG_RECORD_CLEAR(type)
#define BT_MM_DBG_WAIT_TO_FREE_RECORD_ADD(type, size)
#define BT_MM_DBG_WAIT_TO_FREE_RECORD_DEL(type, size)
#define BT_MM_GET_WAIT_TO_FREE(type)                      0
#define BT_MM_GET_WAIT_TO_FREE_CLEAR(type)
#define BT_MM_DBG_RECORD_CB_NUM(type, num)
#define BT_MM_DBG_GET_CB_NUM(type)                        0
#define BT_MM_DBG_RECORD_CB_ALLOCATE(type)
#define BT_MM_DBG_RECORD_CB_FREE(type)
#define BT_MM_DBG_PEEK_NUM(type)                          0
#define BT_MM_DBG_PEEK_NUM_CLEAR(type)
#define BT_MM_DBG_PEEK_NUM_SET(type, size)
#endif

#define BT_MEMORY_LMP_BUFFER 0x02


#define BT_MEMORY_RESERVED_IMPORTANT_DATA_SIZE     0x64

/**
* @}
*/

//memory block(MB):[memory header(MH)]|[buffer]
//state; 00:Free, 01:using, 10:waiting to free.

/**
 * @defgroup memory_struct Struct
 * @{
 */
/**
 * @brief Tx/Rx packet header.
 * @note
 * * info is 32 bits unsigned int, it will be splited to two parts.
 * ||state|size of memory|
 * |:---:|:------:|:--------:|
 * |bits |31~30|29~0|
 * * state.
 * ||comment|
 * |--|:---|
 * |0x00|Free|
 * |0x01|Using|
 * |0x10|Waiting to free|
 */
typedef struct _bt_mm_header_t {
    uint32_t info;  /**<[state] | [size of memory holad by this header] */
} bt_mm_header_t;
/**
 * @brief Tx/Rx packet tailer.
 */
typedef struct _bt_mm_tailer_t {
    uint16_t size;  /** packet size, include tailer self */
    uint16_t footer;
} bt_mm_tailer_t;

/**
 * @brief Memory management control block.
 */
typedef struct {
    uint8_t version;
    uint8_t blk_len;
    uint16_t reserved;                  /** <special request: b0--lock N9 sleep, b1--reject A2DP 1M for special case. */
    //Tx/Rx packet
    bt_mm_header_t *start_mm_h[2];      /**< Starting pointer of #BT_MEMORY_TX_BUFFER/#BT_MEMORY_RX_BUFFER memory pool. */
    uint32_t       pool_size[2];        /**< Size of #BT_MEMORY_TX_BUFFER/#BT_MEMORY_RX_BUFFER memory pool. */
    bt_mm_header_t *search_mm_h[2];     /**< Free memory search pointer of #BT_MEMORY_TX_BUFFER/#BT_MEMORY_RX_BUFFER, which point to current head of free memory blocks, it could be used immediately. */
    bt_linknode_t free_list;
    bt_linknode_t rx_queue;
    bt_linknode_t tx_all_queue;
    bt_mm_header_t *lmp_start_mm_h;     /**< Starting pointer of #BT_MEMORY_LMP_BUFFER memory pool. */
    uint32_t       lmp_pool_size;       /**< Size of #BT_MEMORY_LMP_BUFFER memory pool. */
    bt_mm_header_t *lmp_search_mm_h;    /**< Free memory search pointer of #BT_MEMORY_TX_BUFFER/#BT_MEMORY_RX_BUFFER, which point to current head of free memory blocks, it could be used immediately. */
#ifdef BT_DEBUG
    uint32_t size_of_waiting_to_free[3]; /**< Debug info. indicate how many memory blocks of #BT_MEMORY_TX_BUFFER/#BT_MEMORY_RX_BUFFER are waiting to free. The waiting to free memory blocks will change to free while the memory block is pointed by using_mm_h. */
    uint32_t allocated_packets[3]; /**< Debug info. indicate how many blocks of #BT_MEMORY_TX_BUFFER/#BT_MEMORY_RX_BUFFER are allocated. */
    uint32_t packet_peek[3];       /**< Maximum value of buffer allocate so far.*/
    uint32_t allocated_cb[BT_MEMORY_CONTROL_BLOCK_NUM]; /**< Debug info, indicate how many #BT_MEMORY_CONTROL_BLOCK_TIMER/#BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION/
                 #BT_MEMORY_CONTROL_BLOCK_RFCOMM/#BT_MEMORY_CONTROL_BLOCK_RFCOMM_CHANNEL/#BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION control blocks are allocated. */
    uint32_t cb_num[BT_MEMORY_CONTROL_BLOCK_NUM]; /**< Debug info, indicate how many #BT_MEMORY_CONTROL_BLOCK_TIMER/#BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION/
                 #BT_MEMORY_CONTROL_BLOCK_RFCOMM/#BT_MEMORY_CONTROL_BLOCK_RFCOMM_CHANNEL/#BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION control blocks MM have. */
#endif
#ifdef BT_OOM_TEST_SUPPORT
    uint8_t packet_oom_test[3]; /**< OOM Debug flag for #BT_MEMORY_TX_BUFFER/#BT_MEMORY_RX_BUFFER packet. */
    uint8_t fixed_m_oom_test[BT_MEMORY_CONTROL_BLOCK_NUM];/**< OOM Debug flag for #BT_MEMORY_CONTROL_BLOCK_TIMER/#BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION/
                 #BT_MEMORY_CONTROL_BLOCK_RFCOMM/#BT_MEMORY_CONTROL_BLOCK_RFCOMM_CHANNEL/#BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION  control block. */
#endif
} bt_mm_pool_control_blk_t;

/**
 * @}
 */
extern bt_mm_pool_control_blk_t *bt_mm_cb_p;
extern bt_tx_queue_t *bt_mm_cmd_queue_p;
extern bt_tx_queue_t *bt_mm_tx_if_packet_queue_p;
#define bt_mm_cb        (*bt_mm_cb_p)
#define bt_mm_cmd_queue (*bt_mm_cmd_queue_p)
#define bt_mm_tx_if_packet_queue (*bt_mm_tx_if_packet_queue_p)


/**
* @brief     Bluetooth memory control block types.
*/
typedef enum {
    BT_MEMORY_CONTROL_BLOCK_TIMER = 0x00,              /**< Timer. */
    BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION = 0x01,      /**< Bluetooth LE connection. */
    BT_MEMORY_CONTROL_BLOCK_EDR_CONNECTION = 0x02,     /**< BR/EDR connection. */
    BT_MEMORY_CONTROL_BLOCK_RFCOMM = 0x03,             /**< RFCOMM. */
    BT_MEMORY_CONTROL_BLOCK_AVRCP = 0x04,              /**< AVRCP control channel. */
    BT_MEMORY_CONTROL_BLOCK_PBAPC = 0x05,              /**< PBAPC. */
    BT_MEMORY_CONTROL_BLOCK_A2DP_SEP = 0x06,           /**< A2DP SEP. */
    BT_MEMORY_CONTROL_BLOCK_A2DP = 0x07,               /**< A2DP. */
    BT_MEMORY_CONTROL_BLOCK_HFP = 0x08,                /**< HFP. */
    BT_MEMORY_CONTROL_BLOCK_SPP = 0x09,                /**< SPP. */
    BT_MEMORY_CONTROL_BLOCK_AWS = 0x0A,                /**< AWS. */
    BT_MEMORY_CONTROL_BLOCK_GATT = 0x0B,               /**< GATT. */
    BT_MEMORY_CONTROL_BLOCK_HID = 0x0C,                /**< HID. */
    BT_MEMORY_CONTROL_BLOCK_AWS_MCE = 0x0D,            /**< AWS_MCE. */
    BT_MEMORY_CONTROL_BLOCK_HSP = 0x0E,                /**< HSP. */
    BT_MEMORY_CONTROL_BLOCK_AVRCP_EX = 0x0F,           /**< AVRCP control channel and browse channel. */
    BT_MEMORY_CONTROL_BLOCK_AIRUPDATE = 0x10,          /**< AIRUPDATE. */
    BT_MEMORY_CONTROL_BLOCK_LE_ADV_SET = 0x11,         /**< ADV set. */
    BT_MEMORY_CONTROL_BLOCK_CTP = 0x12,                /**< CTP. */
    BT_MEMORY_CONTROL_BLOCK_L2CAP = 0x13,              /**< L2CAP basic mode. */
    BT_MEMORY_CONTROL_BLOCK_LE_L2CAP_FIX_CHANNEL = 0x14,       /**< L2CAP fix channel. */
    BT_MEMORY_CONTROL_BLOCK_BREDR_L2CAP_FIX_CHANNEL = 0x15,    /**< L2CAP fix channel. */
    BT_MEMORY_CONTROL_BLOCK_MAPC = 0x16,               /**< MAP. */
    BT_MEMORY_CONTROL_BLOCK_LE_OTP = 0x18,             /**< LE OTP. */
    BT_MEMORY_CONTROL_BLOCK_LE_ULL = 0x19,             /**< LE ULL. */
    BT_MEMORY_CONTROL_BLOCK_NUM                        /**< The total number of memory control block types. */
} bt_memory_control_block_t;

/**
 * @brief    Bluetooth memory buffer types for the Memory Management module.
 * @{
 */
typedef enum {
    BT_MEMORY_TX_BUFFER = 0,     /**< TX packet buffer.*/
    BT_MEMORY_RX_BUFFER          /**< RX packet buffer.*/
} bt_memory_packet_t;

















//API for Tx/Rx packet
/**
 * @brief   Check MM's free packet buffer is enough to allocate packet of size bytes.
 * @param[in] type #BT_MEMORY_TX_BUFFER or #BT_MEMORY_RX_BUFFER.
 * @param[in] size Size of packet, in bytes.
 * @return  Return status; #BT_STATUS_SUCCESS or #BT_STATUS_OUT_OF_MEMORY.
 */
uint32_t bt_mm_is_allocatable_packet(bt_memory_packet_t type, uint32_t size);

/**
 * @brief   Check MM's free packet buffer size.
 * @param[in] type #BT_MEMORY_TX_BUFFER or #BT_MEMORY_RX_BUFFER.
 * @return  The free buffer value.
 */
uint32_t bt_mm_get_total_free_size(bt_memory_packet_t type);

/**
 * @brief   Allocate packet of size bytes.
 * @param[in] type #BT_MEMORY_TX_BUFFER or #BT_MEMORY_RX_BUFFER.
 * @param[in] size Size of packet, in bytes.
 * @return  Return a pointer to the beginning of the packet, or NULL if out of memory.
 */
//char *bt_mm_allocate_packet(bt_memory_packet_t type, uint32_t size);
char *bt_mm_allocate_packet_internal(bt_memory_packet_t type, uint32_t size
#ifdef BT_DEBUG
                                     , const char *func_p, uint32_t line_p
#endif
                                    );
/**
 * @brief   Free packet previously allocated by bt_mm_allocate_packet().
 * @param[in] type #BT_MEMORY_TX_BUFFER or #BT_MEMORY_RX_BUFFER.
 * @param[in] ptr  A pointer, point to the beginning of the packet.
 *
 */
//void bt_mm_free_packet(bt_memory_packet_t type, char *ptr);
void bt_mm_free_packet_internal(bt_memory_packet_t type, char *ptr
#ifdef BT_DEBUG
                                , const char *func_p, uint32_t line_p
#endif
                               );

/**
 * @brief     This function obtain the peek size of type buffer.
 * @param[in] type is #BT_MEMORY_TX_BUFFER or #BT_MEMORY_RX_BUFFER.
 * @return    The buffer peek value.
 */
uint32_t bt_memory_get_packet_peek(bt_memory_packet_t type);

/**
 * @brief   Copies the values of src_length bytes from src to des+des_offset.
 * @param[in] des destination.
 * @param[in] des_offset destination offset.
 * @param[in] src source.
 * @param[in] src_length Number of bytes to copy.
 * @return  Return destination.
 */
char *bt_mm_append_packet(char *des, uint32_t des_offset, char *src, uint32_t src_length);

//API for connection and timer control block, that are fixed size
/**
 * @brief   Allocate specific control block(Timer/Connection).
 * @param[in] type #BT_MEMORY_CONTROL_BLOCK_TIMER or #BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION.
 * @return  Return a pointer to the control block, or NULL if out of memory.
 */
//void *bt_mm_allocate_fixed_size_by_type(bt_memory_control_block_t type);
void *bt_mm_allocate_fixed_size_by_type_internal(bt_memory_control_block_t type
#ifdef BT_DEBUG
                                                 , const char *func_p, uint32_t line_p
#endif
                                                );
/**
 * @brief   Free control block previously allocated by bt_mm_allocate_fixed_size_by_type().
 * @param[in] type #BT_MEMORY_CONTROL_BLOCK_TIMER or #BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION.
 * @param[in] ptr  A pointer, point to the control block.
 *
 */
//void bt_mm_free_fixed_size_by_type(bt_memory_control_block_t type, void *ptr);
void bt_mm_free_fixed_size_by_type_internal(bt_memory_control_block_t type, void *ptr
#ifdef BT_DEBUG
                                            , const char *func_p, uint32_t line_p
#endif
                                           );

/**
 * @brief   Checks whether the control block indicated by ptr is in free status.
 * @param[in] type #BT_MEMORY_CONTROL_BLOCK_TIMER or #BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION.
 * @param[in] ptr  A pointer, point to the control block.
 *
 */
bool bt_mm_is_fixed_buffer_free(bt_memory_control_block_t type, void *ptr);

/**
 * @brief   Get specific control block number(Timer/Connection).
 * @param[in] type #bt_memory_control_block_t.
 * @return  Return the number of indicated control block.
 */
uint32_t bt_mm_get_control_block_num(bt_memory_control_block_t type);

/**
* @brief Checks whether MM have free timer can be allocated.
* @return
*      * BT_TRUE: if that have free timer.
*      * BT_FALSE: if no free timer.
*/
bool BT_MM_IS_TIMER_AVAILABLE(void);

/**
* @brief Checks whether MM have free connection can be allocated.
* @return
*      * BT_TRUE: if that have free connection.
*      * BT_FALSE: if no free connection.
*/
bool BT_MM_IS_CONNECTION_AVAILABLE(void);
void bt_mm_check_packet_integrity_internal(bt_memory_packet_t type, char *ptr);
void bt_mm_free_packet_internal(bt_memory_packet_t type, char *ptr
#ifdef BT_DEBUG
                                , const char *func_p, uint32_t line_p
#endif
                               );


#ifdef BT_DEBUG
#define bt_mm_allocate_packet(type, size)           bt_mm_allocate_packet_internal(type, size, __FUNCTION__, __LINE__)
#define bt_mm_free_packet(type, ptr)               bt_mm_free_packet_internal(type, ptr, __FUNCTION__, __LINE__)
#define bt_mm_allocate_fixed_size_by_type(type)     bt_mm_allocate_fixed_size_by_type_internal(type, __FUNCTION__, __LINE__)
#define bt_mm_free_fixed_size_by_type(type, ptr)    bt_mm_free_fixed_size_by_type_internal(type, ptr, __FUNCTION__, __LINE__)
#else
#define bt_mm_allocate_packet(type, size)           bt_mm_allocate_packet_internal(type, size)
#define bt_mm_free_packet(type, ptr)               bt_mm_free_packet_internal(type, ptr)
#define bt_mm_allocate_fixed_size_by_type(type)     bt_mm_allocate_fixed_size_by_type_internal(type)
#define bt_mm_free_fixed_size_by_type(type, ptr)    bt_mm_free_fixed_size_by_type_internal(type, ptr)
#endif

#define bt_mm_check_packet_integrity(type, ptr)               bt_mm_check_packet_integrity_internal(type, ptr)
#define bt_mm_reinit_buffer(type)               bt_mm_reinit_buffer_internal(type)

#ifdef BT_DEBUG
/**
 * @brief   Dump MM debug info.
 */
void bt_mm_debug_dump(void);
#endif

#ifdef BT_OOM_TEST_SUPPORT
/**
 * @brief   Set packet out of memory test.
 * @param[in] type    is #BT_MEMORY_TX_BUFFER, or #BT_MEMORY_RX_BUFFER.
 * @param[in] enable  is 0(disable) or 1(enable).
 * @return    void.
 */
void bt_mm_set_packet_oom(bt_memory_packet_t type, uint8_t enable);
/**
 * @brief   Set control block out of memory test.
 * @param[in] type    is #BT_MEMORY_CONTROL_BLOCK_TIMER or #BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION,.
 * @param[in] enable  is 0(disable) or 1(enable).
 * @return    void.
 */
void bt_mm_set_fixed_memory_oom(bt_memory_control_block_t type, uint8_t enable);
#endif

/** @}
* @}
* @}
*/

uint32_t bt_mm_get_footer(void);

/*
uint32_t bt_mm_allocate_connection(void);
bt_connection_t *bt_mm_get_connection(uint32_t id);
void bt_mm_free_connection(uint32_t id);
*/
//BT_EXTERN_C_END

#endif /*__BT_MEMORY_H__*/
