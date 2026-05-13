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

#ifndef _PKA_SHARE_H_
#define _PKA_SHARE_H_

#if defined(AIR_PKA_SHARE_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "hal_hw_semaphore.h"
/* Public define -------------------------------------------------------------*/
/*
 * HWMAC TxBuffer Mapping
 */
#define HWMAC_ACK                   0
#define HWMAC_NAK                   1
#define HWMAC_BKUP                  2

/*
 * HWMAC TxBuffer Debug
 */
#define HWMAC_DBG_PKA_GPIO          (false)
#define HWMAC_DBG_PKA_TXDUMP        (false)
#define HWMAC_DBG_PKA_TXMONITOR     (false)

/*
 * Active state
 */
#define PKA_SHARE_ACTIVE_STATE_SWITCHING 0x8000

/*
 * HID TxBuffer Para
 */
#define PKA_MAX_HID_TX_BUFF         (4)
#define PKA_HID_TX_BUFF_WO_RETX     (2)
#define PKA_HID_TX_BUFF_W_RETX      (PKA_MAX_HID_TX_BUFF)

#define PKA_FLAG_BIT_TX_LOADING  0x40
#define PKA_LLID_RESERVED           0
#define PKA_LLID_ACLU_START         2
#define PKA_TX_BUF_HDR_OFFSET_U16   4
#define PKA_DATA_LEN_OFFSET_U16     1
#define PKA_DATA_LEN_OFFSET_U8      (PKA_DATA_LEN_OFFSET_U16 << 1)
#define PKA_LLID_OFFSET_U16         6
#define PKA_PDU_LEN_OFFSET_U16      7
#define PKA_PDU_LEN_OFFSET_U8       (PKA_PDU_LEN_OFFSET_U16 << 1)
#define PKA_TX_BUF_PAYLOAD_SIZE_LE  23
#define PKA_TX_BUF_HID_NUM_LE       10
#define PKA_TX_BUF_UNIT_SIZE        ((PKA_TX_BUF_PAYLOAD_SIZE_LE + LC_TRX_BUF_RSVD_SIZE + sizeof(DLIST_STRU) + 3) & (~3UL))
#define PKA_TX_BUF_MAX_SIZE         (PKA_TX_BUF_UNIT_SIZE*PKA_TX_BUF_HID_NUM_LE)

#define PKA_REPORT_RATE_TOTAL_NUM   7

#define PKA_SHARE_ACTIVE_STATE_BIT_STATE                    0x0001
#define PKA_SHARE_ACTIVE_STATE_BIT_DATA_ONGOING             0x4000
#define PKA_SHARE_ACTIVE_STATE_BIT_SWITCHING                0x8000

#define PKA_SHARE_ENTER_CRITICAL_AREA(mask, sem_id) \
do { \
    hal_nvic_save_and_set_interrupt_mask(&mask); \
    share_buffer_hw_semaphore_take(sem_id); \
} while (0)

#define PKA_SHARE_EXIT_CRITICAL_AREA(mask, sem_id) \
do { \
    share_buffer_hw_semaphore_give(sem_id); \
    hal_nvic_restore_interrupt_mask(mask); \
} while (0)

inline void common_gpio_shot(uint8_t bit) {
    *(volatile uint32_t*)0x420b0140 = (1 << bit);
    *(volatile uint32_t*)0x420b0150 = (1 << bit);
}
/* Public typedef ------------------------------------------------------------*/
typedef enum {
    PKA_SHARE_TX_PREPARE_CB_TYPE_LE = 0,
    PKA_SHARE_TX_PREPARE_CB_TYPE_RT = 1,
    PKA_SHARE_TX_PREPARE_CB_TYPE_RTT = 2,
    //PKA_SHARE_TX_PREPARE_CB_TYPE_RTT1 = 3, // must continue with RTT0
    PKA_SHARE_TX_PREPARE_CB_TYPE_MAX
} pka_share_callback_type_t;

typedef enum {
    PKA_SHARE_DISABLE = 0,
    PKA_SHARE_ENABLE = 1,
} pka_share_enable_t;

typedef enum {
    PKA_SHARE_STATUS_ERROR = -1,
    PKA_SHARE_STATUS_OK = 0,
} pka_share_status_t;

typedef enum {
    PKA_SHARE_ACTIVE_STATE_ALWAYS = 0,
    PKA_SHARE_ACTIVE_STATE_NORMAL = 1,
} pka_share_active_state_t;

typedef enum {
    BUFFER_FREE          = 0,
    BUFFER_ALLC_BY_APP   = 1,
    BUFFER_PUSH_TO_HWMAC = 2,
} pka_share_tx_hud_buffer_state_t;

typedef struct pka_share_dlist_stru {
    struct pka_share_dlist_stru *prev;
    struct pka_share_dlist_stru *next;

} pka_share_DLIST_STRU, *pka_share_DLIST_STRU_PTR;
typedef pka_share_DLIST_STRU pka_share_DLIST_HEAD;
typedef pka_share_DLIST_STRU_PTR pka_share_DLIST_HEAD_PTR;

/** @brief OSMQ is OS MEMORY QUEUE HEAD */
typedef struct pka_share_osmq_stru {
    /*! 8B, point to list head */
    pka_share_DLIST_HEAD head;
    /*! 4B, number of memory blocks*/
    uint32_t             noB;
} pka_share_OSMQ, *pka_share_OSMQ_PTR;

typedef struct {
    uint32_t *flag_ptr;
    uint32_t *hwmt_pico_offset_ptr;
    uint16_t *hwmt_pico_offset_phase_ptr;
} pka_share_bt_info_common, *pka_share_bt_info_common_ptr;

typedef struct {
    pka_share_bt_info_common common;
    void **NextTxPtr0; // point to NextTxPtr in HWMT
    void **NextTxPtr1; // point to NextTxPtr in HWMT
    uint8_t  *POFlow_ptr;
    //uint16_t  *EventCounter_ptr;
    //uint32_t  *PacketCounter_ptr;
} pka_share_bt_info_le, *pka_share_bt_info_le_ptr;

typedef struct {
    pka_share_bt_info_common common;
    void **CurTxPtr; // point to tx ptr in PLT
    void **NextTxPtr; // point to NextTxPtr in HWMT
    void **CandiTxPtr[3]; //point to NextTxPtr in LTT
    void *HidTxPktPtr[PKA_MAX_HID_TX_BUFF]; // point to HID TX pkt
    void *EmptyPktPtr; // point to Empty pkt
    uint8_t *hwmt_cur_idx_ptr;
    uint32_t *hwmt_last_anchor_ptr;
    uint16_t *hwmt_last_anchor_phase_ptr;
    uint8_t *hwmt_tpollgo_ptr;
    uint16_t *acl_active_state_ptr;
    uint8_t MaxHidTxPktByRR;   // Maximum Hid Tx Pkt by Different Report Rate
    uint8_t TxRxDataRate; // 01: 1M, 02: 2M, 04: 4M
    uint8_t CurrentReportRate;
    uint16_t mp_version;
    uint8_t* max_pdu_len_ptr;
} pka_share_bt_info_rt, *pka_share_bt_info_rt_ptr;

typedef struct {
    pka_share_bt_info_common common;
    void **CurTxPtr; // point to tx ptr in PLT
    void **CandiTxPtr[4]; //point to NextTxPtr in LTT
    void *HidTxPktPtr[5]; // point to HID TX pkt
} pka_share_bt_info_rtt, *pka_share_bt_info_rtt_ptr;

typedef union {
    pka_share_bt_info_le le;
    pka_share_bt_info_rt rt;
    pka_share_bt_info_rtt rtt;
    pka_share_bt_info_common common;
} pka_share_bt_info;

typedef struct {
    pka_share_enable_t enable;

    // hid tx buffer
    pka_share_OSMQ hid_tx_buf_queue;
    pka_share_OSMQ hid_tx_buf_sending_queue;
    pka_share_OSMQ hid_tx_buf_ack_pending_queue;
    uint8_t *hid_tx_buf_start_ptr;
    uint16_t hid_tx_buf_queue_header_size;
    uint16_t hid_tx_buf_payload_offset;

    // tx init
    uint8_t *hid_tx_status_ptr;
    uint8_t *hid_forced_nack_status_ptr;
    uint16_t hid_tx_buf_payload_size;
    uint16_t hid_tx_buf_num;
    uint16_t cb_type; // callback type le/tr/trr
    uint8_t  req_rscv_ctl_int;

    // pka bt info
    pka_share_bt_info bt_info;
} pka_share_info;

typedef struct {
    uint8_t PktIdx;
    void *  pPktPtr;
    uint8_t PktData[36];
} pka_share_dump_pkt_data;

typedef struct {
    void *  pCurTxPtr;
    void *  pAckTxPtr;
    void *  pNakTxPtr;
} pka_share_dump_tx_ptr;

typedef struct {
    uint32_t TxMonitorClk;
    uint16_t TxTotalPktCnt;
    uint16_t TxLeAclPktCnt;
    uint16_t TxHidPktCnt;
    uint16_t TxEmptyPktCnt;
} pka_share_tx_monitor;

typedef struct
{
    void * pPtr;
    bool   valid;                               // buffer flow ctrl : rsicv_pka <--> pka_hwmac
    pka_share_tx_hud_buffer_state_t   state;    // buffer flow ctrl : rsicv_app <--> riscv_pka
} t_pka_share_tx_hid, *t_pka_share_tx_hid_ptr;

typedef struct {
    t_pka_share_tx_hid HidTxBuf[PKA_MAX_HID_TX_BUFF];
    uint8_t            HidTxBufIdx;
    uint8_t            HidTxBufNum;     // totoal num
    uint8_t            HidTxBufAllcNum; // app alloc num
    void              *pLeAclTxPtr;
} t_pka_share_tx_hid_buf_ctl, *t_pka_share_tx_hid_buf_ctl_ptr;

/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
extern pka_share_info *pka_share_ptr;
extern t_pka_share_tx_hid_buf_ctl pka_share_tx_hid_ctl;
/* Inline functions ----------------------------------------------------------*/
extern void share_buffer_hw_semaphore_take(hal_hw_semaphore_id_t hw_sem_id);
void share_buffer_hw_semaphore_give(hal_hw_semaphore_id_t hw_sem_id);
inline uint16_t pka_share_tx_buf_avail_num(void) //riscv/cm33
{
    return pka_share_ptr->hid_tx_buf_queue.noB;
}

inline pka_share_enable_t pka_share_enabled(void) //riscv/cm33
{
    return pka_share_ptr->enable;
}

inline uint8_t pka_share_tx_buf_is_valid(uint8_t *ptr)
{
    //common_gpio_shot(28);
    return ptr[0x8+0x9] & 0x80;
}

inline uint8_t pka_share_tx_buf_clear_valid(uint8_t *ptr)
{
    return ptr[0x8+0x9] &= 0x7f;
}

inline uint8_t pka_share_get_tx_payload_offset(void)
{
    return (pka_share_ptr->hid_tx_buf_payload_offset - pka_share_ptr->hid_tx_buf_queue_header_size);
}

inline uint8_t pka_share_get_tx_datalen_offset(void)
{
    return (PKA_DATA_LEN_OFFSET_U8);
}

inline uint8_t pka_share_get_tx_pdulen_offset(void)
{
    return (PKA_PDU_LEN_OFFSET_U8);
}

inline uint8_t pka_share_get_tx_hid_avaliable_num(void)
{
    return (pka_share_tx_hid_ctl.HidTxBufNum - pka_share_tx_hid_ctl.HidTxBufAllcNum);
}

/* Public functions ----------------------------------------------------------*/
//tx buffer
void pka_share_tx_init(pka_share_callback_type_t type, uint16_t size, uint16_t num); //cm33
//uint8_t *pka_share_tx_buf_get_from_q(); //riscv
//void pka_share_tx_buf_send(uint8_t *ptr); //riscv
//void pka_share_tx_buf_apply_to_HWMT(); //riscv
//void pka_share_tx_buf_ack_pending_check(); //riscv
uint8_t *pka_share_tx_buf_get_by_idx(uint8_t idx); //riscv/cm33
uint8_t *pka_share_tx_buf_get_payload(uint8_t *ptr); //riscv/cm33
void pka_share_tx_buf_init(uint16_t *ptr); //riscv/cm33
bool pka_tx_buf_is_hid(uint8_t *ptr);
void pka_tx_buf_set_active_state(uint8_t *ptr, uint8_t state);
extern uint8_t *pka_share_tx_buf_get_txbi_by_idx(uint8_t idx);
void pka_share_updt_hid_tx_ptr(void);
void *pka_share_get_hid_tx_ptr(void);
void pka_share_push_hid_tx_ptr(void* pTxPtr);
void pka_share_tx_ctrl_init(void);

// bt
void pka_flag_set_loading(uint8_t value);
uint32_t pka_share_advanced_tx_prepare_rt(void);
void pka_share_tx_forward_prepare_rtt0(void);
bool pka_active_state_match(uint16_t state);
void pka_active_state_set(uint8_t state);

// 2.4g
uint8_t pka_share_get_current_report_rate(void);
uint8_t pka_share_get_current_max_pdu_len(void);

//common
void pka_share_init(void);
extern void pka_share_enable(uint8_t *pTxStatus, uint8_t *pForcedNackStatus); //cm33
extern void pka_share_disable(void); //cm33

void pka_gpio_shot(uint8_t BitNum);
void pka_gpio_pull_high(uint8_t BitNum);
void pka_gpio_pull_low(uint8_t BitNum);

#if (HWMAC_DBG_PKA_TXMONITOR != false)
#define REG_CONN_NATIVE_CLK_ADDR       (0xA0010008)
extern pka_share_tx_monitor pka_tx_monitor;
/*
 * pka_monitor_inc_tx_total_cnt
 */
inline void pka_monitor_inc_tx_total_cnt(void)
{
    pka_tx_monitor.TxTotalPktCnt++;
}
/*
 * pka_monitor_inc_tx_acl_cnt
 */
inline void pka_monitor_inc_tx_acl_cnt(void)
{
    pka_tx_monitor.TxLeAclPktCnt++;
}
/*
 * pka_monitor_inc_tx_hid_cnt
 */
inline void pka_monitor_inc_tx_hid_cnt(void)
{
    pka_tx_monitor.TxHidPktCnt++;
}
/*
 * pka_monitor_inc_tx_empty_cnt
 */
inline void pka_monitor_inc_tx_empty_cnt(void)
{
    pka_tx_monitor.TxEmptyPktCnt++;
}
void pka_share_tx_monitor_chk(void);
#define PKA_MONITOR_INC_TX_TOTAL_CNT() pka_monitor_inc_tx_total_cnt()
#define PKA_MONITOR_INC_TX_ACL_CNT()   pka_monitor_inc_tx_acl_cnt()
#define PKA_MONITOR_INC_TX_HID_CNT()   pka_monitor_inc_tx_hid_cnt()
#define PKA_MONITOR_INC_TX_EMPTY_CNT() pka_monitor_inc_tx_empty_cnt()
#define PKA_SHARE_TX_MONITOR()         pka_share_tx_monitor_chk()
#else
#define PKA_MONITOR_INC_TX_TOTAL_CNT()
#define PKA_MONITOR_INC_TX_ACL_CNT()
#define PKA_MONITOR_INC_TX_HID_CNT()
#define PKA_MONITOR_INC_TX_EMPTY_CNT()
#define PKA_SHARE_TX_MONITOR()
#endif
#endif /* AIR_PKA_SHARE_ENABLE */
#endif /* _SHARE_BUFFER_H_ */
