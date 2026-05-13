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

// #if defined()

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stdint.h"
#include "syslog.h"
#if defined(AIR_COSIM_ENABLE)
#include "cosim_mdm.h"
#endif
#include "hal_spi_master.h"
#include "hal_cross_core_config.h"
#include "pka_share.h"
#include "hal_nvic.h"
#include "pka.h"
/* Private define ------------------------------------------------------------*/
#define AIR_RX_SYNC_BY_RISCV TRUE
#if (AIR_RX_SYNC_BY_RISCV == TRUE)
#define HWM_SYNC_ANCHOR_WINDOW      (10)
#define HWM_SYNC_ANCHOR_CORRECTION  (4)
#define MAX_RiscVHid_RECORDS (10)

#define RBB_REG_NATIVE_CLK_ADDR         0xA0010008
#define RBB_REG_NATIVE_PHASE_ADDR       0xA001000C
#define RBB_REG_SYNC_CLK_ADDR           0xA0010410
#define RBB_REG_SYNC_PHASE_ADDR         0xA0010414
#define RBB_REG_INTERVAL0_PHASE_ADDR    0xA00107C0
#define RBB_REG_INTERVAL2_PHASE_ADDR    0xA00107D0
#define RBB_REG_TICK_CTL_ADDR           0xA00107A0
//! RTC_CONNSYS REGS
#define RTC_CONNSYS_CLK_SWITCH_SLOW_ADDR (0x42106010)
#define RTC_CONNSYS_CLK_ON_XO            (0)
#define RTC_CONNSYS_CLK_ON_LPO           (1)

//! CLOCK_CONTROL REGS
#define XO_PDN_TOP_COND0_ADDR            (0x4204000C)
#define XO_RG_SW_BT_MAC_CONN_CG          (0x40) // 0x4204000C[6]
#define PICO_PHASE_INVALID              0xFFFF


#define RISCV_TXRX_DATARATE_2M          2

#define RISCV_PREI_TARGET_BIT_KEYSCAN   (1 << 0)
#define RISCV_PREI_TARGET_BIT_SPI       (1 << 2)
#endif

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
log_create_module(riscv_pka, PRINT_LEVEL_INFO);

/* Private callbacks ---------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
void riscv_pka_le_tx_post_prepare_callback(uint8_t tx_cnt);
void riscv_pka_rt_tx_post_prepare_callback(uint8_t tx_cnt);
void riscv_pka_rtt_tx_post_prepare_callback(uint8_t tx_cnt);
riscv_pka_info_t riscv_pka_info =
{
    //NULL,
    {
        riscv_pka_le_tx_post_prepare_callback,
        riscv_pka_rt_tx_post_prepare_callback,
        riscv_pka_rtt_tx_post_prepare_callback,
    },
    {0, PICO_PHASE_INVALID}
};
pka_share_info *pka_share_ptr;

typedef struct RiscVCtl{
    bttime_stru  sync_time;
    int32_t  offset;
} RiscVHid, *RiscVHidPTR;

RiscVHid RiscVHID[MAX_RiscVHid_RECORDS];
static uint8_t RiscVHidIdx = 0;
static uint8_t correction_idx =  0xFF;
// typedef enum
// {
//     HID_REPORT_RATE_125_HZ,
//     HID_REPORT_RATE_250_HZ,
//     HID_REPORT_RATE_500_HZ,
//     HID_REPORT_RATE_1K_HZ,
//     HID_REPORT_RATE_2K_HZ,
//     HID_REPORT_RATE_4K_HZ,
//     HID_REPORT_RATE_8K_HZ,
//     HID_REPORT_RATE_TOTAL_NUM,
// }T_HID_REPORT_RATE_E;

/* Private functions ---------------------------------------------------------*/
static inline void pka_share_OS_dlist_init(
    pka_share_DLIST_STRU_PTR plist)
{
    plist->next = plist->prev = plist;
}
static inline bool pka_share_OS_dlist_is_empty(
    pka_share_DLIST_STRU_PTR plist)
{
    return (plist == plist->next);
}
static inline void pka_share_OS_dlist_remove(
    pka_share_DLIST_STRU_PTR list)
{
    list->prev->next = list->next;
    list->next->prev = list->prev;
    pka_share_OS_dlist_init(list);
}
static inline void pka_share_OS_dlist_insert(
    pka_share_DLIST_STRU_PTR list,
    pka_share_DLIST_STRU_PTR prev_list,
    pka_share_DLIST_STRU_PTR next_list)
{
    list->prev = prev_list;
    list->next = next_list;
    prev_list->next = list;
    next_list->prev = list;
}
static inline void pka_share_OS_dlist_append(
    pka_share_DLIST_STRU_PTR newptr,
    pka_share_DLIST_HEAD_PTR head)
{
    pka_share_OS_dlist_insert(newptr, head->prev, head);
}
static inline void pka_share_OS_dlist_prepend(
    pka_share_DLIST_STRU_PTR newptr,
    pka_share_DLIST_HEAD_PTR head)
{
    pka_share_OS_dlist_insert(newptr, head, head->next);
}

pka_share_DLIST_STRU_PTR pka_share_OS_dlist_getfront(
    pka_share_DLIST_HEAD_PTR head)
{
    if (!pka_share_OS_dlist_is_empty(head)) {
        pka_share_DLIST_STRU_PTR list = head->next;
        pka_share_OS_dlist_remove(list);

        return list;
    } else {
        return NULL;
    }
}
void *__pka_share_OSMQ_Get(
    pka_share_OSMQ_PTR mq_ptr)
{
    pka_share_DLIST_STRU_PTR list_ptr;
    //OSMEM_BLK_PTR  blk_ptr;

    /* check input pointer */
    assert(mq_ptr != NULL);

    if (mq_ptr->noB > 0) {
        mq_ptr->noB--;

        list_ptr = pka_share_OS_dlist_getfront(&mq_ptr->head);

        /* anti fatal error */
        // assert(list_ptr != NULL);
    } else {
        list_ptr = NULL;
    }

    if (list_ptr != NULL) {
        return list_ptr;
    } else {
        return NULL;
    }
}

void *pka_share_OSMQ_Peak(pka_share_OSMQ_PTR mq_ptr)
{
    return mq_ptr->head.next;
}

void *pka_share_OSMQ_Get(pka_share_OSMQ_PTR mq_ptr)
{
    void* pGet =NULL;
    pGet = __pka_share_OSMQ_Get(mq_ptr);
    PKA_LOG(riscv_pka, "pka_share_OSMQ_Get, q = 0x%x, ptr = 0x%x", 2, mq_ptr, pGet);
    return pGet;
}

void pka_share_OSMQ_Put(pka_share_OSMQ_PTR mq_ptr, void *ptr)
{
    PKA_LOG(riscv_pka, "pka_share_OSMQ_Put, mq_ptr 0x%x, ptr = 0x%x",2, mq_ptr, ptr);
    /* check input pointers */
    assert(mq_ptr != NULL);
    assert(ptr != NULL);

    //blk_ptr = (OSMEM_BLK_PTR)(ptr - 7);
    pka_share_OS_dlist_append(ptr, &mq_ptr->head);

    mq_ptr->noB++;

    return;
}

void pka_share_OSMQ_PutFront(pka_share_OSMQ_PTR mq_ptr, void *ptr)
{
    PKA_LOG(riscv_pka, "pka_share_OSMQ_PutFront, mq_ptr 0x%x, ptr = 0x%x",2, mq_ptr, ptr);
    /* check input pointers */
    assert(mq_ptr != NULL);
    assert(ptr != NULL);

    //blk_ptr = (OSMEM_BLK_PTR)(ptr - 7);
    pka_share_OS_dlist_prepend(ptr, &mq_ptr->head);

    mq_ptr->noB++;

    return;
}

void pka_share_OSMQ_PrintList(pka_share_OSMQ_PTR mq_ptr) {
    pka_share_DLIST_HEAD_PTR head = &mq_ptr->head;
    while (head->next != &mq_ptr->head) {
        pka_share_DLIST_STRU_PTR list = head->next;
        uint8_t *ptr = (void*) list;
        uint8_t *payload = pka_share_tx_buf_get_payload(ptr);
        LOG_MSGID_I(riscv_pka, "pka_share_OSMQ_PrintList, seqn = %02x", 1, payload[14]);
        head = list;
    }
}

void pka_share_OSMQ_PrintQueue(pka_share_OSMQ_PTR mq_ptr) {
    pka_share_DLIST_HEAD_PTR head = &mq_ptr->head;
    while (head->next != &mq_ptr->head) {
        pka_share_DLIST_STRU_PTR list = head->next;
        uint8_t *ptr = (void*) list;
        uint8_t *payload = pka_share_tx_buf_get_payload(ptr);
        LOG_MSGID_I(riscv_pka, "pka_share_OSMQ_PrintQueue, ptr = %02x, valid = %d, payload[9~14] = %02x %02x %02x %02x %02x %02x", 8,
            ptr, ptr[0x8+0x9] & 0x80, payload[9], payload[10], payload[11], payload[12], payload[13], payload[14]);
        head = list;
    }
}

void pka_share_tx_buf_apply_to_HWMT()
{
    /*LOG_MSGID_I(riscv_pka, "pka_share_tx_buf_apply_to_HWMT (PutFront), POFlow = %d, NextTxPtr0 = %x, NextTxPtr1 = %x, EventCnt = %d, PacketCnt = %d", 5,
        *pka_share_ptr->bt_info.le.POFlow_ptr, *pka_share_ptr->bt_info.le.NextTxPtr0, *pka_share_ptr->bt_info.le.NextTxPtr1,
        (uint16_t)*pka_share_ptr->bt_info.le.EventCounter_ptr, (uint32_t)*pka_share_ptr->bt_info.le.PacketCounter_ptr);
    LOG_MSGID_I(riscv_pka, "pka_share_tx_buf_sending_check, noB = %d", 1, pka_share_ptr->hid_tx_buf_sending_queue.noB);
    pka_share_OSMQ_PrintQueue(&pka_share_ptr->hid_tx_buf_sending_queue);*/
    // 1. get ptr from sending queue
    uint8_t *ptr = pka_share_OSMQ_Get(&pka_share_ptr->hid_tx_buf_sending_queue);
    /*uint8_t *payload = pka_share_tx_buf_get_payload(ptr);
    LOG_MSGID_I(riscv_pka, "pka_share %x get %02x from queue (1st)", 2, ptr, payload[14]);*/
    if (ptr == NULL) {
        /*LOG_MSGID_I(riscv_pka, "No first PKT in hid_tx_buf_sending_queue, NextTxPtr0 = %x, NextTxPtr1 = %x", 2,
            *pka_share_ptr->bt_info.le.NextTxPtr0, *pka_share_ptr->bt_info.le.NextTxPtr1);*/
        return;
    }
    uint32_t mask;
    PKA_SHARE_ENTER_CRITICAL_AREA(mask, 4);
    //*(volatile uint32_t*)0x420b0140 = (1 << 28); // GPIO_Pull_High(28)
    // 2. try to put into ptr0
    uint8_t *pNextTxPtr0 = *pka_share_ptr->bt_info.le.NextTxPtr0;
    if (*pka_share_ptr->bt_info.le.POFlow_ptr == 1 && pNextTxPtr0 == NULL) {
        //set to HWMT
        *pka_share_ptr->bt_info.le.NextTxPtr0 = ptr + pka_share_ptr->hid_tx_buf_queue_header_size;
        pka_share_OSMQ_Put(&pka_share_ptr->hid_tx_buf_ack_pending_queue, ptr);
        /*payload = pka_share_tx_buf_get_payload(ptr);
        LOG_MSGID_I(riscv_pka, "pka_share %x set %02x to HWMT0", 2, ptr, payload[14]);*/
        //pop new pkt
        ptr = pka_share_OSMQ_Get(&pka_share_ptr->hid_tx_buf_sending_queue);
        /*payload = pka_share_tx_buf_get_payload(ptr);
        LOG_MSGID_I(riscv_pka, "pka_share %x get %02x from queue (2nd)", 2, ptr, payload[14]);*/
        if (ptr == NULL) {
            /*LOG_MSGID_I(riscv_pka, "No second PKT in hid_tx_buf_sending_queue, NextTxPtr0 = %x, NextTxPtr1 = %x", 2,
                *pka_share_ptr->bt_info.le.NextTxPtr0, *pka_share_ptr->bt_info.le.NextTxPtr1);
            *(volatile uint32_t*)0x420b0150 = (1 << 28); // GPIO_Pull_Low(28)*/
            PKA_SHARE_EXIT_CRITICAL_AREA(mask, 4);
            return;
        }
    }
    // 3. try to put into ptr1
    uint8_t *pNextTxPtr1 = *pka_share_ptr->bt_info.le.NextTxPtr1;
    if (*pka_share_ptr->bt_info.le.POFlow_ptr == 1 && pNextTxPtr1 == NULL) {
        //set to HWMT
        *pka_share_ptr->bt_info.le.NextTxPtr1 = ptr + pka_share_ptr->hid_tx_buf_queue_header_size;
        pka_share_OSMQ_Put(&pka_share_ptr->hid_tx_buf_ack_pending_queue, ptr);
        //*(volatile uint32_t*)(0xa001010c) ^= 0x200;
        /*payload = pka_share_tx_buf_get_payload(ptr);
        LOG_MSGID_I(riscv_pka, "pka_share %x set %02x to HWMT1", 2, ptr, payload[14]);*/
    } else {
        // pka_share_OSMQ_Put(&pka_share_ptr->hid_tx_buf_sending_queue, ptr);
        pka_share_OSMQ_PutFront(&pka_share_ptr->hid_tx_buf_sending_queue, ptr);
        /*LOG_MSGID_I(riscv_pka, "pka_share %x put %02x to queue", 2, ptr, payload[14]);*/
    }
    /*pka_share_OSMQ_PrintList(&pka_share_ptr->hid_tx_buf_sending_queue);*/
    /*LOG_MSGID_I(riscv_pka, "pka_share_tx_buf_apply_to_HWMT (PutFront) done, NextTxPtr0 = %x, NextTxPtr1 = %x", 2,
                *pka_share_ptr->bt_info.le.NextTxPtr0, *pka_share_ptr->bt_info.le.NextTxPtr1);
    *(volatile uint32_t*)0x420b0150 = (1 << 28); // GPIO_Pull_Low(28)*/
    PKA_SHARE_EXIT_CRITICAL_AREA(mask, 4);
}

void pka_share_tx_buf_ack_pending_check()
{
    /*LOG_MSGID_I(riscv_pka, "pka_share_tx_buf_ack_pending_check, noB = %d", 1,  pka_share_ptr->hid_tx_buf_ack_pending_queue.noB);
    pka_share_OSMQ_PrintQueue(&pka_share_ptr->hid_tx_buf_ack_pending_queue);*/
    uint8_t *ptr;
    int8_t i;
    //common_gpio_shot(35);
    for (i= pka_share_ptr->hid_tx_buf_ack_pending_queue.noB; i > 0; i--) {
        ptr = pka_share_OSMQ_Get(&pka_share_ptr->hid_tx_buf_ack_pending_queue);
        if (ptr != NULL) {
            if (pka_share_tx_buf_is_valid(ptr)) {
                //common_gpio_shot(28);
                pka_share_OSMQ_Put(&pka_share_ptr->hid_tx_buf_queue, ptr);
                pka_share_tx_buf_clear_valid(ptr);
                //PKA_LOG(riscv_pka, "pka_share_tx_ptr hdr %x %x %x %x", 4, ptr[16], ptr[17], ptr[18], ptr[19]);
                //LOG_MSGID_I(riscv_pka, "pka_share_tx_ptr %02x hdr %02x %02x %02x %02x", 5, ptr, ptr[16], ptr[17], ptr[18], ptr[19]);
            } else {
                //common_gpio_shot(36);
                pka_share_OSMQ_Put(&pka_share_ptr->hid_tx_buf_ack_pending_queue, ptr);
            }
        }
    }
}

void record_riscV_info(uint32_t sync_time_period, uint16_t sync_time_phase, int32_t offset)
{
    if (RiscVHID[RiscVHidIdx].sync_time.phase == sync_time_phase) {return;}
    RiscVHidIdx = (RiscVHidIdx + 1) % MAX_RiscVHid_RECORDS;
    RiscVHID[RiscVHidIdx].sync_time.period = sync_time_period;
    RiscVHID[RiscVHidIdx].sync_time.phase = sync_time_phase;
    RiscVHID[RiscVHidIdx].offset = offset;
}

/* Public functions ----------------------------------------------------------*/
void pka_share_tx_buf_set_pkt_len(uint16_t *ptr, uint16_t pkt_len)
{
    ptr[PKA_TX_BUF_HDR_OFFSET_U16 + PKA_DATA_LEN_OFFSET_U16] = pkt_len;
    ptr[PKA_TX_BUF_HDR_OFFSET_U16 + PKA_PDU_LEN_OFFSET_U16] = pkt_len;
}

bool pka_share_hid_need_accmulate(void)
{
    return ((*pka_share_ptr->hid_tx_status_ptr == 0) || (pka_tx_buf_is_hid(*pka_share_ptr->bt_info.rt.CurTxPtr) == false));
}

uint8_t pka_share_get_tx_status(void)
{
    //return *pka_share_ptr->hid_tx_status_ptr;
    return ((*pka_share_ptr->hid_tx_status_ptr == 1) || (pka_tx_buf_is_hid(*pka_share_ptr->bt_info.rt.CurTxPtr) == false));
}

uint8_t * pka_share_get_force_nack_ptr(void)
{
    return pka_share_ptr->hid_forced_nack_status_ptr;
}

void riscv_pka_le_tx_post_prepare_callback(uint8_t tx_cnt)
{
    //LOG_MSGID_I(riscv_pka, "riscv_pka_le_tx_post_prepare_callback", 0);

#if 0
    *(volatile uint32_t*)(0xa001010c) ^= 0x10; // debug
    uint8_t *ptr = pka_share_tx_buf_get_from_q();
    pka_share_tx_buf_send(ptr);
    PKA_LOG(app, "post tx, %x", 1, ptr);
#endif
    pka_share_tx_buf_apply_to_HWMT();
    PKA_LOG(riscv_pka, "1peak txQ: %x, sendingQ %x, pendingQ %x", 3,
            pka_share_OSMQ_Peak(&pka_share_ptr->hid_tx_buf_queue),
            pka_share_OSMQ_Peak(&pka_share_ptr->hid_tx_buf_sending_queue),
            pka_share_OSMQ_Peak(&pka_share_ptr->hid_tx_buf_ack_pending_queue));

    //pka_share_tx_buf_ack_pending_check();
    PKA_LOG(riscv_pka, "2peak txQ: %x, sendingQ %x, pendingQ %x", 3,
            pka_share_OSMQ_Peak(&pka_share_ptr->hid_tx_buf_queue),
            pka_share_OSMQ_Peak(&pka_share_ptr->hid_tx_buf_sending_queue),
            pka_share_OSMQ_Peak(&pka_share_ptr->hid_tx_buf_ack_pending_queue));
}

// workaround
uint8_t rtt_counter = 0;
void riscv_pka_rtt_tx_post_prepare_callback(uint8_t tx_cnt)
{
    //LOG_MSGID_I(riscv_pka, "riscv_pka_rtt_tx_post_prepare_callback", 0);
#if 0
    // tx buffer setup
    uint8_t *pHidTxPkt[4];
    pHidTxPkt[0] = pka_share_tx_buf_get_by_idx(0);
    pHidTxPkt[1] = pka_share_tx_buf_get_by_idx(1);
    pHidTxPkt[2] = pka_share_tx_buf_get_by_idx(2);
    pHidTxPkt[3] = pka_share_tx_buf_get_by_idx(3);
    pka_share_tx_buf_init((uint16_t*)pHidTxPkt[0]);
    pka_share_tx_buf_init((uint16_t*)pHidTxPkt[1]);
    pka_share_tx_buf_init((uint16_t*)pHidTxPkt[2]);
    pka_share_tx_buf_init((uint16_t*)pHidTxPkt[3]);

    // custom payload
    uint8_t *pHidTxPktPayload[4];
    pHidTxPktPayload[0] = pka_share_tx_buf_get_payload(pHidTxPkt[0]);
    pHidTxPktPayload[1] = pka_share_tx_buf_get_payload(pHidTxPkt[1]);
    pHidTxPktPayload[2] = pka_share_tx_buf_get_payload(pHidTxPkt[2]);
    pHidTxPktPayload[3] = pka_share_tx_buf_get_payload(pHidTxPkt[3]);
    pHidTxPktPayload[0][0]++;
    pHidTxPktPayload[1][1]++;
    pHidTxPktPayload[2][2]++;
    pHidTxPktPayload[3][3]++;
#endif

    if (tx_cnt == 0) {
        // tx forward prepare
        pka_share_tx_forward_prepare_rtt0();
        //workaround
        rtt_counter = 1;
    } else {
        //workaround
        rtt_counter = 0;
    }

}

#if 0
void riscv_pka_rtt1_tx_prepare_callback(void)
{
    uint8_t *pHidTxPkt;
    pHidTxPkt = pka_share_tx_buf_get_by_idx(4);
    pka_share_tx_buf_init((uint16_t*)pHidTxPkt);
    uint8_t *pHidTxPktPayload = pka_share_tx_buf_get_payload(pHidTxPkt);

    // custom payload
    pHidTxPktPayload[4]++;

    //workaround
    rtt_counter = 0;
}
#endif

uint8_t pka_share_hwmt_get_rxhdr()
{
    return *(pka_share_ptr->bt_info.rt.hwmt_tpollgo_ptr - 4); //The address at tpollgo minus 4 to RxHdr.
}

uint8_t pka_share_hwmt_get_curidx()
{
    return *pka_share_ptr->bt_info.rt.hwmt_cur_idx_ptr;
}

void pka_share_get_hwmt_last_anchor(bttime_stru *last_anchor)
{
    last_anchor->period = *pka_share_ptr->bt_info.rt.hwmt_last_anchor_ptr;
    last_anchor->phase = *pka_share_ptr->bt_info.rt.hwmt_last_anchor_phase_ptr;
}

void pka_share_get_hwmt_pico_offset(bttime_stru *pico_offset)
{
    pico_offset->period = *pka_share_ptr->bt_info.common.hwmt_pico_offset_ptr & 0x03FFFFFF;
    pico_offset->phase = *pka_share_ptr->bt_info.common.hwmt_pico_offset_phase_ptr & 0xFFF;
}

void pka_share_get_sync_clk(bttime_stru *sync_time)
{
    sync_time->period = (*(volatile uint32_t*)RBB_REG_SYNC_CLK_ADDR) >> 2;
    sync_time->phase = *(volatile uint32_t*)RBB_REG_SYNC_PHASE_ADDR;
}

void pka_share_get_cur_pico_clk(bttime_stru_ptr time_ptr)
{
    bttime_stru cur_clk, native_clk;

    do {
        native_clk.period = *(volatile uint32_t*)RBB_REG_NATIVE_CLK_ADDR;
        native_clk.phase = *(volatile uint16_t*)RBB_REG_NATIVE_PHASE_ADDR;
    } while (native_clk.period != *(volatile uint32_t*)RBB_REG_NATIVE_CLK_ADDR);

    native_clk.period &= 0x0FFFFFFC;

    /* Clip CurrCLK */
    pka_share_get_hwmt_pico_offset(&cur_clk);
    cur_clk.period += native_clk.period;
    cur_clk.phase += native_clk.phase;

    if (cur_clk.phase >= 2500) {
        cur_clk.phase -= 2500;
        cur_clk.period += 4;
    }

    time_ptr->period = cur_clk.period;
    time_ptr->phase = cur_clk.phase;
}

void riscv_pka_rt_tx_post_prepare_callback(uint8_t tx_cnt)
{
    //LOG_MSGID_I(riscv_pka, "riscv_pka_rt_tx_post_prepare_callback", 0);
#if 0
    // tx buffer setup
    uint8_t *pHidTxPkt[2];
    pHidTxPkt[0] = pka_share_tx_buf_get_by_idx(0);
    pHidTxPkt[1] = pka_share_tx_buf_get_by_idx(1);
    pka_share_tx_buf_init((uint16_t*)pHidTxPkt[0]);
    pka_share_tx_buf_init((uint16_t*)pHidTxPkt[1]);

    // custom payload
    uint8_t *pHidTxPktPayload[2];
    pHidTxPktPayload[0] = pka_share_tx_buf_get_payload(pHidTxPkt[0]);
    pHidTxPktPayload[1] = pka_share_tx_buf_get_payload(pHidTxPkt[1]);
    pHidTxPktPayload[0][0]++;
    pHidTxPktPayload[1][0]++;

    if (pka_share_get_tx_status() == 0) {
        common_gpio_shot(17);
    } else {
        common_gpio_shot(18);
        LOG_MSGID_I(app, "nak tx status %x", 1, pka_share_get_tx_status());
    }
#endif

#if (AIR_RX_SYNC_BY_RISCV == TRUE)
    if (pka_share_hwmt_get_curidx() == 0) {
        bttime_stru last_anchor, native_anchor, pico_offset;
        bttime_stru sync_time;
        bool connsys_clk_domain = *((volatile uint32_t *)RTC_CONNSYS_CLK_SWITCH_SLOW_ADDR);
        uint32_t xo_pdn_top_cond0 = *((volatile uint32_t *)XO_PDN_TOP_COND0_ADDR);

        // RxSync start, re-check connsys clk switch to LPO or not, if connsys is on LPO, the RX sync is invalid
        if (((connsys_clk_domain & 0x01) == RTC_CONNSYS_CLK_ON_LPO) || (xo_pdn_top_cond0 & XO_RG_SW_BT_MAC_CONN_CG)) {
            return;
        }

        // Timing of the last anchor frame
        pka_share_get_hwmt_last_anchor(&native_anchor);

        pka_share_get_hwmt_pico_offset(&pico_offset);

        last_anchor.period = (native_anchor.period - pico_offset.period) & 0x03FFFFFF;

        if (native_anchor.phase >= pico_offset.phase) {
            last_anchor.phase = native_anchor.phase - pico_offset.phase;
        } else {
            last_anchor.phase = 2500 + native_anchor.phase - pico_offset.phase;
            last_anchor.period -= 1;
        }
        // Timing of access code synced
		pka_share_get_sync_clk(&sync_time);

        if (sync_time.period == 0) {
            LOG_MSGID_I(riscv_pka, "[RISCV][HWM_SYNC] sync time null", 0);
            return;
        }

        //  |8|32us |27us|8|32us |
        //  |P|PDU  |TIFS|P|PDU  |
        //    |<-offset->|
        //    Sync       Last
        int32_t offset = 0;
        // last anchor < sync clock case. shift to next anchor
        if ((sync_time.period > last_anchor.period) ||
                ((sync_time.period == last_anchor.period) && (sync_time.phase > last_anchor.phase))) {
            offset = 2000 + last_anchor.phase - sync_time.phase;
            if (offset > 2500) {
                offset -= 2500;
            }
        // last anchor > sync clock case.
        } else {
            offset = (last_anchor.period - sync_time.period) * 2500;
            offset = offset + last_anchor.phase - sync_time.phase;
            // shift last anchor to < interval
            while (offset > 2000) {
                offset -= 2000;
            }
        }

        // rollback to the same sync clk
        uint32_t expslot_1[8] = {
            256,
            240,
            240,
            272,
            240,
            240,
            240,
            272
        };
        uint32_t expslot_2[8] = {
            240,
            260,
            240,
            260,
            240,
            260,
            240,
            260,
        };

#if 0
        int32_t anchor_diff[7] = {
            -136, // 8k
            -266, // 4k
            -266, // 2k
            -266, // 1k
            -266, // 500
            -266, // 250
            -266 // 125
        };
        uint32_t interval_group[7] = {
            250,
            500,
            1000,
            2000,
            4000,
            8000,
            16000,
        };
        // get referenced offset of current report rate
        int32_t ref_offset = 0;
        uint32_t interval = *(volatile uint32_t*)RBB_REG_INTERVAL_PHASE_ADDR;
        for (i = 0;i < 7; i++) {
            if (interval == interval_group[i]) {
                ref_offset = anchor_diff[i];
                break;
            }
        }
#else
        // get referenced offset of current report rate
        int32_t ref_offset = 0;
        uint8_t report_rate = pka_share_ptr->bt_info.rt.CurrentReportRate - 1;

        if (pka_share_ptr->bt_info.rt.TxRxDataRate == RISCV_TXRX_DATARATE_2M) {
            ref_offset = (report_rate == 5) ? PKA_EXP_ANCHOR_DIFF_4K_2M : PKA_EXP_ANCHOR_DIFF_LOWER_4K_2M;
        } else {
            if (report_rate == 6) {
                ref_offset = PKA_EXP_ANCHOR_DIFF_8K_4M;
            } else  {
                ref_offset = (pka_share_ptr->bt_info.rt.mp_version == 0) ?
                    PKA_EXP_ANCHOR_DIFF_LOWER_8K_4M_OLD : PKA_EXP_ANCHOR_DIFF_LOWER_8K_4M;
            }
        }
        uint32_t i = 0;
        // if (report_rate == HID_REPORT_RATE_8K_HZ || (report_rate == HID_REPORT_RATE_8K_HZ && pka_share_ptr->bt_info.rt.TxRxDataRate == RISCV_TXRX_DATARATE_2M))
        if (report_rate == 6 ||
                (report_rate == 5 && pka_share_ptr->bt_info.rt.TxRxDataRate == RISCV_TXRX_DATARATE_2M) ||
                (pka_share_ptr->bt_info.rt.mp_version == 0)) {
            /*
                Group1 = {PKA_EXP_ANCHOR_DIFF_8K_4M,
                          PKA_EXP_ANCHOR_DIFF_LOWER_4K_2M}

                A valid value of offset should fall with in +-HWM_SYNC_ANCHOR_WINDOW of the largest element (PKA_EXP_ANCHOR_DIFF_8K_4M) in the Group1.
            */
            while (offset > PKA_EXP_ANCHOR_DIFF_8K_4M + HWM_SYNC_ANCHOR_WINDOW && i < 8) {
                offset -= expslot_1[i];
                i++;
            }
        } else {
            /*
                Group2 = {PKA_EXP_ANCHOR_DIFF_LOWER_8K_4M,
                          PKA_EXP_ANCHOR_DIFF_LOWER_8K_4M_OLD,
                          PKA_EXP_ANCHOR_DIFF_4K_2M}

                A valid value of offset should fall with in +-HWM_SYNC_ANCHOR_WINDOW of the largest element (PKA_EXP_ANCHOR_DIFF_LOWER_8K_4M) in the Group2.
            */

            while (offset > PKA_EXP_ANCHOR_DIFF_LOWER_8K_4M + HWM_SYNC_ANCHOR_WINDOW && i < 8) {
                offset -= expslot_2[i];
                i++;
            }
        }
#if 0
        LOG_MSGID_I(riscv_pka, "[RISCV][HWM_SYNC] riscv_pka_rt_tx_post_prepare_callback ref_offset %d, report_rate %d, Phy %d", 3
                   ,ref_offset
                   ,report_rate
                   ,pka_share_ptr->bt_info.rt.TxRxDataRate);
#endif
#endif
        // Check sync position
        if (offset != ref_offset)
        {
            if((offset >= (ref_offset - HWM_SYNC_ANCHOR_WINDOW)) &&
            (offset <= (ref_offset + HWM_SYNC_ANCHOR_WINDOW))) {
                if(((offset <= (ref_offset - HWM_SYNC_ANCHOR_CORRECTION)) || (offset >= (ref_offset + HWM_SYNC_ANCHOR_CORRECTION)))) {
                    if (correction_idx == 0xFF) {
                        record_riscV_info(sync_time.period, sync_time.phase, offset);
                        correction_idx = RiscVHidIdx;
                        return;
                    }else {
                        if (offset != RiscVHID[correction_idx].offset) {
                            record_riscV_info(sync_time.period, sync_time.phase, offset);
                            correction_idx = RiscVHidIdx;
                            return;
                        }
                    }
                }
                if (offset > ref_offset) {
                    // + phase
                    pico_offset.phase += (offset - ref_offset);

                    if (pico_offset.phase >= 2500) {
                        pico_offset.phase -= 2500;

                        // + clock
                        pico_offset.period++;
                        pico_offset.period &= 0x3FFFFFF;
                    }
                } else {
                    // - phase
                    uint8_t update_value = ref_offset - offset;

                    if (pico_offset.phase >= update_value) {
                        pico_offset.phase -= update_value;
                    } else {
                        pico_offset.phase += (2500 - update_value);

                        // - clock
                        if (pico_offset.period == 0) {
                            pico_offset.period = 0x3FFFFFF;
                        } else {
                            pico_offset.period--;
                        }
                    }
                }
                riscv_pka_info.pico_offset.phase = pico_offset.phase;
                riscv_pka_info.pico_offset.period = pico_offset.period;
            }
        }
        // RxSync End, re-check connsys clk switch to LPO or not, if connsys on LPO, the RX sync is invalid
        connsys_clk_domain = *((volatile uint32_t *)RTC_CONNSYS_CLK_SWITCH_SLOW_ADDR);
        xo_pdn_top_cond0 = *((volatile uint32_t *)XO_PDN_TOP_COND0_ADDR);
        if (((connsys_clk_domain & 0x01) == RTC_CONNSYS_CLK_ON_LPO) || (xo_pdn_top_cond0 & XO_RG_SW_BT_MAC_CONN_CG)) {
            return;
        }

        // update pico clk offset if offset_phase is not invalid
        if (riscv_pka_info.pico_offset.phase != PICO_PHASE_INVALID)
        {
            if (riscv_pka_info.pico_offset.phase == *pka_share_ptr->bt_info.common.hwmt_pico_offset_phase_ptr){
                riscv_pka_info.pico_offset.phase = PICO_PHASE_INVALID;
            } else {
                uint32_t retru = 3;
                while (retru-- > 0) {
                    if (HAL_HW_SEMAPHORE_STATUS_OK == hal_hw_semaphore_take(4)) {
                        *pka_share_ptr->bt_info.common.hwmt_pico_offset_phase_ptr = riscv_pka_info.pico_offset.phase;
                        *pka_share_ptr->bt_info.common.hwmt_pico_offset_ptr = (riscv_pka_info.pico_offset.period | (0x4<<26));
                        share_buffer_hw_semaphore_give(4);
                        break;
                    }
                }
                correction_idx = 0xFF;
                record_riscV_info(sync_time.period, sync_time.phase, offset);
#if 0
                LOG_MSGID_I(riscv_pka, "[RISCV][HWM_SYNC] offset %d, sync_time = 0x%x %d, last_anchor = 0x%x %d, pico_offset 0x%x %d %x %d", 9,
                        offset,
                        sync_time.period,
                        sync_time.phase,
                        last_anchor.period,
                        last_anchor.phase,
                        pico_offset.period,
                        pico_offset.phase,
                        *pka_share_ptr->bt_info.common.hwmt_pico_offset_ptr,
                        *pka_share_ptr->bt_info.common.hwmt_pico_offset_phase_ptr);
#endif
            }
        }
        uint8_t rxhdr = pka_share_hwmt_get_rxhdr();
        pka_active_state_set((rxhdr >> 5) & 1);
    }
#endif
    PKA_SHARE_TX_MONITOR();

#if 0
    uint8_t *pHidTxPkt;
    uint8_t *pHidTxPktPayload;
    pHidTxPkt = pka_share_tx_buf_get_by_idx(0);
    if (pka_share_get_tx_status() == 0) {
        //pHidTxPkt = pka_share_tx_buf_get_by_idx(0);
    } else {
        //pHidTxPkt = pka_share_tx_buf_get_by_idx(1);
        common_gpio_shot(25);
    }
    pHidTxPktPayload = pka_share_tx_buf_get_payload(pHidTxPkt);

    uint32_t set_mask = 0x00, clear_mask = 0x00;
    uint8_t gpio_cnt = 0;
	uint8_t data = pHidTxPktPayload[6];

    for (gpio_cnt = 0; (4 + gpio_cnt) <= 6; gpio_cnt++)
    {
        if ((data >> gpio_cnt) & 0x01) {
            set_mask |= (1 << (4 + gpio_cnt));
        } else {
            clear_mask |= (1 << (4 + gpio_cnt));
        }
    }
    //g_hal_gpio_base->GPIO_DOUT.CLR[0] |= clear_mask;
    //g_hal_gpio_base->GPIO_DOUT.SET[0] |= set_mask;
    *(volatile uint32_t*)0x420b0150 = clear_mask;
    *(volatile uint32_t*)0x420b0140 = set_mask;
//#else
    uint8_t *pHidTxPkt;
    uint32_t set_mask, clear_mask;
    uint8_t gpio_cnt;
	uint8_t data;

    if (pka_share_get_tx_status() != 0) {
        common_gpio_shot(25);
    }

    pHidTxPkt = pka_share_tx_buf_get_by_idx(1);
    set_mask = 0x00;
    clear_mask = 0x00;
    gpio_cnt = 0;
	data = pHidTxPkt[10];

    for (gpio_cnt = 0; (4 + gpio_cnt) <= 4; gpio_cnt++)
    {
        if ((data >> gpio_cnt) & 0x01) {
            set_mask |= (1 << (4 + gpio_cnt));
        } else {
            clear_mask |= (1 << (4 + gpio_cnt));
        }
    }
    *(volatile uint32_t*)0x420b0150 = clear_mask;
    *(volatile uint32_t*)0x420b0140 = set_mask;
    //common_gpio_shot(1);

    pHidTxPkt = pka_share_tx_buf_get_by_idx(0);
    set_mask = 0x00;
    clear_mask = 0x00;
    gpio_cnt = 0;
	data = pHidTxPkt[10];

    for (gpio_cnt = 0; (4 + gpio_cnt) <= 4; gpio_cnt++)
    {
        if ((data >> gpio_cnt) & 0x01) {
            set_mask |= (1 << (4 + gpio_cnt));
        } else {
            clear_mask |= (1 << (4 + gpio_cnt));
        }
    }
    *(volatile uint32_t*)0x420b0150 = clear_mask;
    *(volatile uint32_t*)0x420b0140 = set_mask;


#endif

}

uint32_t pka_spi_callback_pre_process(pka_share_callback_type_t *type, uint32_t *tx_cn)
{
    //LOG_MSGID_I(riscv_pka, "pka_spi_callback_pre_process", 0);

    *type = pka_share_ptr->cb_type;
    *tx_cn = rtt_counter;

    if (pka_share_enabled() == PKA_SHARE_DISABLE) {
        return 1; // error
    }
    pka_share_tx_ctrl_init();
#if defined(AIR_2_4G_RELIABLE_RETRASMISSION)
    pka_share_updt_hid_tx_ptr();
#endif
    pka_share_tx_buf_ack_pending_check();

    return 0; // no problem
}

uint32_t pka_spi_callback_post_process()
{
    //LOG_MSGID_I(riscv_pka, "pka_spi_callback_post_process", 0);

    uint16_t cb_type = pka_share_ptr->cb_type;
    uint32_t complete_time = 0;
    if (cb_type == PKA_SHARE_TX_PREPARE_CB_TYPE_RT) {
        complete_time = pka_share_advanced_tx_prepare_rt();
        riscv_pka_rt_tx_post_prepare_callback(0);
    } else if (cb_type == PKA_SHARE_TX_PREPARE_CB_TYPE_LE) {
        riscv_pka_le_tx_post_prepare_callback(0);
    } else if (cb_type == PKA_SHARE_TX_PREPARE_CB_TYPE_RTT) {
        riscv_pka_rtt_tx_post_prepare_callback(rtt_counter);
    }

    return complete_time;
}



#if (AIR_HWMAC_TRIGGER_RISCV_ENABLE)
void bt_hwmac_callback()
{
    *(volatile uint32_t*)(0x422E000c) = 0x7f; // disable hwmac interrupt
}
#endif

void riscv_pka_init()
{
#if (AIR_HWMAC_TRIGGER_RISCV_ENABLE)
    *(volatile uint32_t*)(0x422E000c) = 0x3f; // enable hwmac interrupt
    hal_nvic_register_isr_handler(30, (hal_nvic_isr_t)bt_hwmac_callback);
    hal_nvic_enable_irq(30);
#endif

    pka_share_init();
}

void pka_share_tx_buf_send(uint8_t *ptr)
{
    pka_share_OSMQ_Put(&pka_share_ptr->hid_tx_buf_sending_queue, ptr);
}

uint8_t *pka_share_tx_buf_get_from_q()
{
    return pka_share_OSMQ_Get(&pka_share_ptr->hid_tx_buf_queue);
}

