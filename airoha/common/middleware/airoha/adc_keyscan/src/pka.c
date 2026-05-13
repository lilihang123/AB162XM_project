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
#include "air_logging.h"
#if defined(AIR_COSIM_ENABLE)
#include "cosim_mdm.h"
#endif
#include "hal_spi_master.h"
#include "hal_cross_core_config.h"
#include "pka_share.h"
#include "hal_nvic.h"
#include "pka.h"
#include "memory_attribute.h"

/* Private define ------------------------------------------------------------*/
#define AIR_RX_SYNC_BY_RISCV TRUE
#if (AIR_RX_SYNC_BY_RISCV == TRUE)
#define HWM_SYNC_ANCHOR_OFFSET      ((32 + 27) << 1)    // 32 us PDU + 27 us TIFS
#define HWM_SYNC_ANCHOR_WINDOW      (4)

#define RBB_REG_NATIVE_CLK_ADDR         0xA0010008
#define RBB_REG_NATIVE_PHASE_ADDR       0xA001000C
#define RBB_REG_SYNC_CLK_ADDR           0xA0010410
#define RBB_REG_SYNC_PHASE_ADDR         0xA0010414

#define PICO_PHASE_INVALID              0xFFFF
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
extern pka_share_info *pka_share_ptr;
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

ATTR_TEXT_IN_TCM pka_share_DLIST_STRU_PTR pka_share_OS_dlist_getfront(
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
ATTR_TEXT_IN_TCM void *__pka_share_OSMQ_Get(
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
        assert(list_ptr != NULL);
    } else {
        list_ptr = NULL;
    }

    if (list_ptr != NULL) {
        return list_ptr;
    } else {
        return NULL;
    }
}

ATTR_TEXT_IN_TCM void *pka_share_OSMQ_Peak(pka_share_OSMQ_PTR mq_ptr)
{
    return mq_ptr->head.next;
}

ATTR_TEXT_IN_TCM void *pka_share_OSMQ_Get(pka_share_OSMQ_PTR mq_ptr)
{
    void* pGet =NULL;
    pGet = __pka_share_OSMQ_Get(mq_ptr);
    PKA_LOG(riscv_pka, "pka_share_OSMQ_Get, q = 0x%x, ptr = 0x%x", 2, mq_ptr, pGet);
    return pGet;
}

ATTR_TEXT_IN_TCM void pka_share_OSMQ_Put(pka_share_OSMQ_PTR mq_ptr, void *ptr)
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

ATTR_TEXT_IN_TCM void pka_share_OSMQ_PutFront(pka_share_OSMQ_PTR mq_ptr, void *ptr)
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

ATTR_TEXT_IN_TCM void pka_share_OSMQ_PrintList(pka_share_OSMQ_PTR mq_ptr) {
    pka_share_DLIST_HEAD_PTR head = &mq_ptr->head;
    while (head->next != &mq_ptr->head) {
        pka_share_DLIST_STRU_PTR list = head->next;
        uint8_t *ptr = (void*) list;
        uint8_t *payload = pka_share_tx_buf_get_payload(ptr);
        LOG_MSGID_I(riscv_pka, "pka_share_OSMQ_PrintList, seqn = %02x", 1, payload[14]);
        head = list;
    }
}

ATTR_TEXT_IN_TCM void pka_share_tx_buf_apply_to_HWMT()
{
    /*LOG_MSGID_I(riscv_pka, "pka_share_tx_buf_apply_to_HWMT (PutFront), NextTxPtr0 = %x, NextTxPtr1 = %x", 2,
            *pka_share_ptr->bt_info.le.NextTxPtr0, *pka_share_ptr->bt_info.le.NextTxPtr1);*/
    // 1. get ptr from sending queue
    uint8_t *ptr = pka_share_OSMQ_Get(&pka_share_ptr->hid_tx_buf_sending_queue);
    /*uint8_t *payload = pka_share_tx_buf_get_payload(ptr);
    LOG_MSGID_I(riscv_pka, "pka_share %x get %02x from queue (1st)", 2, ptr, payload[14]);*/
    if (ptr == NULL) {
        return;
    }
    uint32_t mask;
    PKA_SHARE_ENTER_CRITICAL_AREA(mask, 4);
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
    PKA_SHARE_EXIT_CRITICAL_AREA(mask, 4);
}

ATTR_TEXT_IN_TCM void pka_share_tx_buf_ack_pending_check()
{
    PKA_LOG(riscv_pka, "pka_share_tx_buf_ack_pending_check, noB = %d",1,  pka_share_ptr->hid_tx_buf_ack_pending_queue.noB);
    uint8_t *ptr;
    int8_t i;
    for (i= pka_share_ptr->hid_tx_buf_ack_pending_queue.noB; i > 0; i--) {
        ptr = pka_share_OSMQ_Get(&pka_share_ptr->hid_tx_buf_ack_pending_queue);
        if (pka_share_tx_buf_is_valid(ptr)) {
            pka_share_OSMQ_Put(&pka_share_ptr->hid_tx_buf_queue, ptr);
            pka_share_tx_buf_clear_valid(ptr);
            PKA_LOG(riscv_pka, "pka_share_tx_ptr hdr %x %x %x %x", 4, ptr[16], ptr[17], ptr[18], ptr[19]);
        } else {
            pka_share_OSMQ_Put(&pka_share_ptr->hid_tx_buf_ack_pending_queue, ptr);
        }
    }
}

/* Public functions ----------------------------------------------------------*/
ATTR_TEXT_IN_TCM void pka_share_tx_buf_set_pkt_len(uint16_t *ptr, uint16_t pkt_len)
{
    ptr[PKA_TX_BUF_HDR_OFFSET_U16 + PKA_DATA_LEN_OFFSET_U16] = pkt_len;
    ptr[PKA_TX_BUF_HDR_OFFSET_U16 + PKA_PDU_LEN_OFFSET_U16] = pkt_len;
}

ATTR_TEXT_IN_TCM bool pka_share_hid_need_accmulate(void)
{
    return ((*pka_share_ptr->hid_tx_status_ptr == 0) || (pka_tx_buf_is_hid(*pka_share_ptr->bt_info.rt.CurTxPtr) == false));
}

ATTR_TEXT_IN_TCM uint8_t pka_share_get_tx_status(void)
{
    return *pka_share_ptr->hid_tx_status_ptr;
    //return !((*pka_share_ptr->hid_tx_status_ptr == 0) || (pka_tx_buf_is_hid(*pka_share_ptr->bt_info.rt.CurTxPtr) == false));
}

ATTR_TEXT_IN_TCM uint8_t * pka_share_get_force_nack_ptr(void)
{
    return pka_share_ptr->hid_forced_nack_status_ptr;
}

ATTR_TEXT_IN_TCM void riscv_pka_le_tx_post_prepare_callback(uint8_t tx_cnt)
{
    PKA_LOG(riscv_pka, "riscv_pka_le_tx_post_prepare_callback",0);

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
ATTR_TEXT_IN_TCM void riscv_pka_rtt_tx_post_prepare_callback(uint8_t tx_cnt)
{
    PKA_LOG(riscv_pka, "pka_share_tx_buf_apply_to_HWMT",0);
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

ATTR_TEXT_IN_TCM uint8_t pka_share_hwmt_get_curidx()
{
    return *pka_share_ptr->bt_info.rt.hwmt_cur_idx_ptr;
}

ATTR_TEXT_IN_TCM void pka_share_get_hwmt_last_anchor(bttime_stru *last_anchor)
{
    last_anchor->period = *pka_share_ptr->bt_info.rt.hwmt_last_anchor_ptr;
    last_anchor->phase = *pka_share_ptr->bt_info.rt.hwmt_last_anchor_phase_ptr;
}

ATTR_TEXT_IN_TCM void pka_share_get_hwmt_pico_offset(bttime_stru *pico_offset)
{
    pico_offset->period = *pka_share_ptr->bt_info.common.hwmt_pico_offset_ptr & 0x03FFFFFF;
    pico_offset->phase = *pka_share_ptr->bt_info.common.hwmt_pico_offset_phase_ptr & 0xFFF;
}

ATTR_TEXT_IN_TCM void pka_share_get_sync_clk(bttime_stru *sync_time)
{
    sync_time->period = (*(uint32_t*)RBB_REG_SYNC_CLK_ADDR) >> 2;
    sync_time->phase = *(uint32_t*)RBB_REG_SYNC_PHASE_ADDR;
}

ATTR_TEXT_IN_TCM void pka_share_get_cur_pico_clk(bttime_stru_ptr time_ptr)
{
    bttime_stru cur_clk, native_clk;

    do {
        native_clk.period = *(uint32_t*)RBB_REG_NATIVE_CLK_ADDR;
        native_clk.phase = *(uint16_t*)RBB_REG_NATIVE_PHASE_ADDR;
    } while (native_clk.period != *(uint32_t*)RBB_REG_NATIVE_CLK_ADDR);

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

ATTR_TEXT_IN_TCM void riscv_pka_rt_tx_post_prepare_callback(uint8_t tx_cnt)
{
    PKA_LOG(riscv_pka, "riscv_pka_rt_tx_post_prepare_callback",0);
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
    // tx forward prepare
    pka_share_advanced_tx_prepare_rt();

#if (AIR_RX_SYNC_BY_RISCV == TRUE)
    if (pka_share_hwmt_get_curidx() == 1) {
        bttime_stru sync_time, last_anchor, pico_offset;

        // Timing of the last anchor frame
        pka_share_get_hwmt_last_anchor(&sync_time);

        pka_share_get_hwmt_pico_offset(&pico_offset);

        last_anchor.period = (sync_time.period - pico_offset.period) & 0x03FFFFFF;

        if (sync_time.phase >= pico_offset.phase) {
            last_anchor.phase = sync_time.phase - pico_offset.phase;
        } else {
            last_anchor.phase = 2500 + sync_time.phase - pico_offset.phase;
            last_anchor.period -= 1;
        }
        // Timing of access code synced
		pka_share_get_sync_clk(&sync_time);

        //  |8|32us |27us|8|32us |
        //  |P|PDU  |TIFS|P|PDU  |
        //    |<-offset->|
        //    Sync       Last
        int32_t offset;
        if (sync_time.period == last_anchor.period) {
            offset = last_anchor.phase - sync_time.phase;
        } else {
            offset = 2500 - sync_time.phase + last_anchor.phase;
        }
        // rollback to the same sync clk
        uint32_t expslot[8] = {
            256,
            240,
            240,
            272,
            240,
            240,
            240,
            272
        };
        uint32_t i = 0;
        while (offset < 0 && i < 8) {
            offset += expslot[i];
            i++;
        }

        // Check sync position
        if ((offset != HWM_SYNC_ANCHOR_OFFSET) &&
            (offset >= (HWM_SYNC_ANCHOR_OFFSET - HWM_SYNC_ANCHOR_WINDOW)) &&
            (offset <= (HWM_SYNC_ANCHOR_OFFSET + HWM_SYNC_ANCHOR_WINDOW))) {

            if (offset > HWM_SYNC_ANCHOR_OFFSET) {
                // + phase
                pico_offset.phase += (offset - HWM_SYNC_ANCHOR_OFFSET);

                if (pico_offset.phase >= 2500) {
                    pico_offset.phase -= 2500;

                    // + clock
                    pico_offset.period++;
                    pico_offset.period &= 0x3FFFFFF;
                }
            } else {
                // - phase
                uint8_t update_value = HWM_SYNC_ANCHOR_OFFSET - offset;

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
            PKA_LOG(riscv_pka, "[RISCV][HWM_SYNC] offset %d, sync_time = 0x%x %d, last_anchor = 0x%x %d, pico_offset 0x%x %d %x %d", 9,
                    offset,
                    sync_time.period,
                    sync_time.phase,
                    last_anchor.period,
                    last_anchor.phase,
                    pico_offset.period,
                    pico_offset.phase,
                    *pka_share_ptr->bt_info.common.hwmt_pico_offset_ptr,
                    *pka_share_ptr->bt_info.common.hwmt_pico_offset_phase_ptr);
        }
    }
#endif

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
#endif

}

ATTR_TEXT_IN_TCM uint32_t pka_spi_callback_pre_process(pka_share_callback_type_t *type, uint32_t *tx_cn)
{
    *type = pka_share_ptr->cb_type;
    *tx_cn = rtt_counter;

    if (pka_share_enabled() == PKA_SHARE_DISABLE) {
        return 1; // error
    }

#if (AIR_RX_SYNC_BY_RISCV == TRUE)
    // update pico clk offset if offset_phase is not invalid
    if (riscv_pka_info.pico_offset.phase != PICO_PHASE_INVALID) {
        *pka_share_ptr->bt_info.common.hwmt_pico_offset_phase_ptr = riscv_pka_info.pico_offset.phase;
        *pka_share_ptr->bt_info.common.hwmt_pico_offset_ptr &= 0xFC000000;
        *pka_share_ptr->bt_info.common.hwmt_pico_offset_ptr |= riscv_pka_info.pico_offset.period;
        riscv_pka_info.pico_offset.phase = PICO_PHASE_INVALID;
    }
#endif
    pka_share_tx_buf_ack_pending_check();

    return 0; // no problem
}

ATTR_TEXT_IN_TCM void pka_spi_callback_post_process()
{
    if (riscv_pka_info.tx_post_prepare_handler[pka_share_ptr->cb_type]) {
        riscv_pka_info.tx_post_prepare_handler[pka_share_ptr->cb_type](rtt_counter);
    }
}



#if (AIR_HWMAC_TRIGGER_RISCV_ENABLE)
ATTR_TEXT_IN_TCM void bt_hwmac_callback()
{
    *(volatile uint32_t*)(0x422E000c) = 0x7f; // disable hwmac interrupt
}
#endif

ATTR_TEXT_IN_TCM void riscv_pka_init()
{
#if (AIR_HWMAC_TRIGGER_RISCV_ENABLE)
    *(volatile uint32_t*)(0x422E000c) = 0x3f; // enable hwmac interrupt
    hal_nvic_register_isr_handler(30, (hal_nvic_isr_t)bt_hwmac_callback);
    hal_nvic_enable_irq(30);
#endif

    pka_share_init();
}

ATTR_TEXT_IN_TCM void pka_share_tx_buf_send(uint8_t *ptr)
{
    pka_share_OSMQ_Put(&pka_share_ptr->hid_tx_buf_sending_queue, ptr);
}

ATTR_TEXT_IN_TCM uint8_t *pka_share_tx_buf_get_from_q()
{
    return pka_share_OSMQ_Get(&pka_share_ptr->hid_tx_buf_queue);
}

