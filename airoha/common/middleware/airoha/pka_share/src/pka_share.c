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

#if defined(AIR_PKA_SHARE_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include "pka_share.h"
#include "hal_cross_core_config.h"
#include "assert.h"
#include "hal_nvic.h"
#include "hal_gpt_internal.h"

/* Private define ------------------------------------------------------------*/
#define HW_SEM_RETRY_TIMES 500

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#if 0
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
#endif

//#define OFFSET_OF(type,member) ((unsigned int)&(((type *)0)->member))
//#define CONTAINER_OF(ptr,type,member) ((type *)((U8 *)(ptr) - OFFSET_OF(type,member)))
extern void hid_express_dbg_inc_pka_hid_cnt();
extern void hid_express_dbg_inc_pka_acl_cnt();
extern void hid_express_dbg_inc_pka_hid_drop_cnt();

#if (HWMAC_DBG_PKA_GPIO != false) // debug used
#include "hal_gpio_internal.h"
void pka_gpio_shot(uint8_t BitNum)
{
    uint8_t io_group = BitNum / 32;
    uint8_t io_idx   = BitNum % 32;

    PKA_GPIO_PULL_HIGH(io_group, io_idx);
    PKA_GPIO_PULL_LOW(io_group, io_idx);
}

void pka_gpio_pull_high(uint8_t BitNum)
{
    uint8_t io_group = BitNum / 32;
    uint8_t io_idx   = BitNum % 32;

    PKA_GPIO_PULL_HIGH(io_group, io_idx);
}

void pka_gpio_pull_low(uint8_t BitNum)
{
    uint8_t io_group = BitNum / 32;
    uint8_t io_idx   = BitNum % 32;

    PKA_GPIO_PULL_LOW(io_group, io_idx);
}

void pka_gpio_put_data(uint8_t data, uint8_t gpio_start, uint8_t gpio_end)
{
    uint32_t set_mask = 0x00, clear_mask = 0x00;
    uint8_t gpio_cnt = 0;
    uint8_t io_group = gpio_start / 32;

    for (gpio_cnt = 0; (gpio_start + gpio_cnt) <= gpio_end; gpio_cnt++) {
        if ((data >> gpio_cnt) & 0x01) {
            set_mask |= (0x01 << ((gpio_start + gpio_cnt) % 32));
        } else {
            clear_mask |= (0x01 << ((gpio_start + gpio_cnt) % 32));
        }
    }
    PKA_GPIO_CLR(io_group, clear_mask);
    PKA_GPIO_SET(io_group, set_mask);
}
#endif /* #if (HWMAC_DBG_PKA_GPIO != false) */

/* Private variables ---------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
extern bool g_riscv_ccni_irq_occur;
t_pka_share_tx_hid_buf_ctl pka_share_tx_hid_ctl;
pka_share_bt_info_rt_ptr g_pPkaRtInfo;
uint16_t pka_cb_type = 0;
void *g_pEmptyPktPtr = NULL;

/* Private functions ---------------------------------------------------------*/
void pka_share_hw_semaphore_take(hal_hw_semaphore_id_t hw_sem_id)
{
    uint32_t take_times = 0;

    /* Add hw semaphore to avoid multi-core access */
    while (++take_times) {
        if (HAL_HW_SEMAPHORE_STATUS_OK == hal_hw_semaphore_take(hw_sem_id)) {
            break;
        }

        if (take_times > HW_SEM_RETRY_TIMES) {
            assert(0);
        }
    }
}

void pka_share_hw_semaphore_give(hal_hw_semaphore_id_t hw_sem_id)
{
    if (HAL_HW_SEMAPHORE_STATUS_OK != hal_hw_semaphore_give(hw_sem_id)) {
        assert(0);
    }
}

/* Public functions ----------------------------------------------------------*/
#if 0
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
        assert(list_ptr != NULL);
    } else {
        list_ptr = NULL;
    }

    if (list_ptr != NULL) {
        //uint32_t MemoryType = blk_ptr->header.memory_type & 0xFFFF;
        //OSMEM_MONITOR_PTR osmem_monitor_tmp = pka_query_osmem_monitor_by_type(MemoryType);


        //blk_ptr->header.head_ptr = &(osmem_monitor_tmp->head);

        //OS_dlist_append(list_ptr, &(osmem_monitor_tmp->head));

        //(osmem_monitor_tmp->noB)++;

        //pka_inc_blk_num(blk_ptr->header.memory_type);


        return list_ptr;
    } else {
        return NULL;
	}
}

void *pka_share_OSMQ_Get(
    pka_share_OSMQ_PTR mq_ptr)
{
    void* pGet =NULL;
    pGet = __pka_share_OSMQ_Get(mq_ptr);
    return pGet;
}

void pka_share_OSMQ_Put(pka_share_OSMQ_PTR mq_ptr, void *ptr)
{
    /* check input pointers */
    assert(mq_ptr != NULL);
    assert(ptr != NULL);

    //blk_ptr = (OSMEM_BLK_PTR)(ptr - 7);
    pka_share_OS_dlist_append(ptr, &mq_ptr->head);

    mq_ptr->noB++;

    return;
}

void pka_share_tx_buf_send(uint8_t *ptr)
{
	pka_share_OSMQ_Put(&pka_share_ptr->hid_tx_buf_sending_queue, ptr);
}

uint8_t *pka_share_tx_buf_get_from_q()
{
	return pka_share_OSMQ_Get(&pka_share_ptr->hid_tx_buf_queue);
}
#endif

//common
void pka_share_init(void)
{
    pka_share_ptr = (pka_share_info*)CROSS_CORE_MEM_VARIABLE(pka_share);
    pka_share_tx_hid_ctl.pLeAclTxPtr = NULL;
}

//tx buf
void pka_share_tx_init(pka_share_callback_type_t type, uint16_t size, uint16_t num)
{
    pka_share_ptr->cb_type = type;
    pka_share_ptr->hid_tx_buf_payload_size = size;
    pka_share_ptr->hid_tx_buf_num = num;
}

#if 0
void pka_share_tx_buf_apply_to_HWMT()
{
	// 1. get ptr from sending queue
	uint8_t *ptr = pka_share_OSMQ_Get(&pka_share_ptr->hid_tx_buf_sending_queue);
	if (ptr == NULL) {
		return;
	}
	uint32_t mask;
	PKA_SHARE_ENTER_CRITICAL_AREA(mask, 4);
	// 2. try to put into ptr0
    uint8_t *pNextTxPtr0 = *pka_share_ptr->bt_info.le.NextTxPtr0;
	if (pNextTxPtr0 == NULL) {
        //set to HWMT
		*pka_share_ptr->bt_info.le.NextTxPtr0 = ptr + pka_share_ptr->hid_tx_buf_queue_header_size;
	    pka_share_OSMQ_Put(&pka_share_ptr->hid_tx_buf_ack_pending_queue, ptr);
        //pop new pkt
		ptr = pka_share_OSMQ_Get(&pka_share_ptr->hid_tx_buf_sending_queue);
		if (ptr == NULL) {
			PKA_SHARE_EXIT_CRITICAL_AREA(mask, 4);
			return;
		}
    }
	// 3. try to put into ptr1
    uint8_t *pNextTxPtr1 = *pka_share_ptr->bt_info.le.NextTxPtr1;
	if (pNextTxPtr1 == NULL) {
        //set to HWMT
		*pka_share_ptr->bt_info.le.NextTxPtr1 = ptr + pka_share_ptr->hid_tx_buf_queue_header_size;
	    pka_share_OSMQ_Put(&pka_share_ptr->hid_tx_buf_ack_pending_queue, ptr);
        //*(volatile uint32_t*)(0xa001010c) ^= 0x200;
	} else {
		pka_share_OSMQ_Put(&pka_share_ptr->hid_tx_buf_sending_queue, ptr);
	}
	PKA_SHARE_EXIT_CRITICAL_AREA(mask, 4);
}

void pka_share_tx_buf_ack_pending_check()
{
	uint8_t *ptr;
    int8_t i;
    for (i= pka_share_ptr->hid_tx_buf_ack_pending_queue.noB; i >= 0; i--) {
	    ptr = pka_share_OSMQ_Get(&pka_share_ptr->hid_tx_buf_ack_pending_queue);
        if (pka_share_tx_buf_is_valid(ptr)) {
	        pka_share_OSMQ_Put(&pka_share_ptr->hid_tx_buf_queue, ptr);
            pka_share_tx_buf_clear_valid(ptr);
        } else {
	        pka_share_OSMQ_Put(&pka_share_ptr->hid_tx_buf_ack_pending_queue, ptr);
        }
    }
}
#endif

uint8_t * pka_share_tx_buf_get_by_idx(uint8_t idx)
{
    uint16_t unit_size = (pka_share_ptr->hid_tx_buf_payload_size + pka_share_ptr->hid_tx_buf_payload_offset + 3) & (~3UL);
    return (pka_share_ptr->hid_tx_buf_start_ptr + (unit_size * idx));
}

uint8_t *pka_share_tx_buf_get_payload(uint8_t *ptr)
{
    return ptr + pka_share_ptr->hid_tx_buf_payload_offset;
}

void pka_share_tx_buf_init(uint16_t *ptr)
{
    uint16_t offset = pka_share_ptr->hid_tx_buf_queue_header_size/2;
    ptr[offset] = 0x14;
    ptr[offset + PKA_DATA_LEN_OFFSET_U16] = pka_share_ptr->hid_tx_buf_payload_size;
    ptr[offset + PKA_PDU_LEN_OFFSET_U16] = pka_share_ptr->hid_tx_buf_payload_size;
    ptr[offset + PKA_LLID_OFFSET_U16] = (pka_share_ptr->cb_type == PKA_SHARE_TX_PREPARE_CB_TYPE_LE) ?
                    PKA_LLID_ACLU_START : PKA_LLID_RESERVED;
}

inline uint8_t pka_tx_buf_get_llid(uint8_t *ptr)
{
    return ptr[0xc] & 0x3;
}

void pka_tx_buf_set_active_state(uint8_t *ptr, uint8_t state)
{
    if (state) {
        ptr[0xc] |= (1 << 5);
    } else {
        ptr[0xc] &= ~(1 << 5);
    }
}

inline uint16_t pka_tx_buf_get_data_len(uint16_t *ptr)
{
    return ptr[1];
}

inline void pka_tx_buf_set_hid_data_len(uint16_t *ptr)
{
    ptr[1] = 7;
}

inline uint16_t pka_tx_buf_get_pdu_len(uint16_t *ptr)
{
    return ptr[7];
}

inline void pka_tx_buf_set_hid_pdu_len(uint16_t *ptr)
{
    ptr[7] = 7;
}

inline uint8_t pka_tx_buf_is_valid(uint8_t *ptr)
{
    return (ptr[9] & 0x80);
}

inline void pka_tx_buf_set_valid(uint8_t *ptr)
{
    ptr[9] |= 0x80;
}

inline void pka_tx_buf_clear_buf_valid(uint8_t *ptr)
{
    ptr[9] &= 0x7F;
}

inline void pka_tx_buf_enable_gaming_bit(uint8_t *ptr)
{
    ptr[9] |= 0x40;
}

// bt
bool pka_tx_buf_is_hid(uint8_t *ptr)
{
#if 1
    void **pka_hid_tx_pkt_p = &(pka_share_ptr->bt_info.rt.HidTxPktPtr[0]);
    void *CurTxPtr = *pka_share_ptr->bt_info.rt.CurTxPtr;
    return ((CurTxPtr == pka_hid_tx_pkt_p[0]) || (CurTxPtr == pka_hid_tx_pkt_p[1]));
#else
    if ((pka_tx_buf_get_llid(ptr) == 0) && (pka_tx_buf_get_data_len((uint16_t *)ptr) > 0)) {
        return true;
    }
    return false;
#endif
}


uint16_t pka_tx_buf_remain_length(uint8_t *ptr)
{
    return pka_tx_buf_get_data_len((uint16_t *)ptr) - pka_tx_buf_get_pdu_len((uint16_t *)ptr);
}

bool pka_tx_buf_is_empty(uint8_t *ptr)
{
    if (ptr == NULL || pka_tx_buf_get_data_len((uint16_t *)ptr) == 0) {
        return true;
    }
    return false;
}

void pka_flag_set_loading(uint8_t value)
{
    *pka_share_ptr->bt_info.common.flag_ptr &= ~PKA_FLAG_BIT_TX_LOADING;
    if (value != 0) {
        *pka_share_ptr->bt_info.common.flag_ptr |= PKA_FLAG_BIT_TX_LOADING;
    }
}

bool pka_active_state_match(uint16_t state)
{
    return (*pka_share_ptr->bt_info.rt.acl_active_state_ptr == state);
}

/**************************************************************************
 *
 * Function : pka_active_state_set
 *
 * Input : target active state
 *
 * Output : N/A
 *
 * Description: set active state to every in used tx buffer
**************************************************************************/
void pka_active_state_set(uint8_t state)
{
    uint16_t active_state = *pka_share_ptr->bt_info.rt.acl_active_state_ptr;
    active_state = (active_state & 0xFF00) | state;
    *pka_share_ptr->bt_info.rt.acl_active_state_ptr = active_state;
    for(uint8_t idx = 0; idx < pka_share_tx_hid_ctl.HidTxBufNum; idx++) {
        pka_tx_buf_set_active_state(pka_share_tx_hid_ctl.HidTxBuf[idx].pPtr, state);
    }
    pka_tx_buf_set_active_state(g_pEmptyPktPtr, state);
}

/**************************************************************************
 *
 * Function : pka_share_tx_ctrl_init
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description:
**************************************************************************/
void pka_share_tx_ctrl_init(void)
{
    if (pka_share_ptr->req_rscv_ctl_int != false) {
        pka_cb_type = pka_share_ptr->cb_type;
        if (pka_cb_type == PKA_SHARE_TX_PREPARE_CB_TYPE_RT) {
            //@ Tx Buffer Init
            pka_share_tx_hid_ctl.HidTxBufNum = pka_share_ptr->bt_info.rt.MaxHidTxPktByRR;
            for(uint8_t idx = 0; idx < pka_share_tx_hid_ctl.HidTxBufNum; idx++) {
                pka_share_tx_hid_ctl.HidTxBuf[idx].pPtr = pka_share_ptr->bt_info.rt.HidTxPktPtr[idx];
                pka_tx_buf_set_hid_data_len(pka_share_tx_hid_ctl.HidTxBuf[idx].pPtr);
                pka_tx_buf_set_hid_pdu_len(pka_share_tx_hid_ctl.HidTxBuf[idx].pPtr);
                pka_tx_buf_clear_buf_valid(pka_share_tx_hid_ctl.HidTxBuf[idx].pPtr);
                pka_share_tx_hid_ctl.HidTxBuf[idx].valid = true;
                pka_share_tx_hid_ctl.HidTxBuf[idx].state = BUFFER_FREE;
            }
            pka_share_tx_hid_ctl.HidTxBufIdx = 0;
            pka_share_tx_hid_ctl.HidTxBufAllcNum = 0;
            if (pka_share_tx_hid_ctl.HidTxBufNum > PKA_MAX_HID_TX_BUFF) {
                assert(0);
            }

            //@ Other info store to global variable to save time to access sysram
            g_pEmptyPktPtr = pka_share_ptr->bt_info.rt.EmptyPktPtr;
            g_pPkaRtInfo   = &pka_share_ptr->bt_info.rt;
        }
        pka_share_ptr->req_rscv_ctl_int = false;
    }
}

#if (HWMAC_DBG_PKA_TXDUMP != false)
#define MAX_PKT_DATA_DUMP      (40)
uint8_t pka_pkt_dump_idx = 0;
pka_share_dump_pkt_data pka_tx_pkt_dump[MAX_PKT_DATA_DUMP];
/**************************************************************************
 *
 * Function : pka_share_txpkt_dump
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description:
**************************************************************************/
__attribute__((optimize("O3"))) void pka_share_txpkt_dump(uint8_t *pPktPtr)
{
    pka_tx_pkt_dump[pka_pkt_dump_idx].PktIdx = pka_pkt_dump_idx;
    pka_tx_pkt_dump[pka_pkt_dump_idx].pPktPtr = pPktPtr;
    memcpy(pka_tx_pkt_dump[pka_pkt_dump_idx].PktData, pPktPtr, 36);
    if (++pka_pkt_dump_idx >= MAX_PKT_DATA_DUMP) {
        assert(0);
        pka_pkt_dump_idx = 0;
    }
}

#define MAX_PKT_TXPTR_DUMP      (80)
uint8_t pka_ptr_dump_idx = 0;
pka_share_dump_tx_ptr pka_tx_ptr_dump[MAX_PKT_TXPTR_DUMP];
/**************************************************************************
 *
 * Function : pka_share_txptr_dump
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description:
**************************************************************************/
__attribute__((optimize("O3"))) void pka_share_txptr_dump(void *pCurTxPtr, void *pAckTxPtr, void *pNakTxPtr)
{
    pka_tx_ptr_dump[pka_ptr_dump_idx].pCurTxPtr = pCurTxPtr;
    pka_tx_ptr_dump[pka_ptr_dump_idx].pAckTxPtr = pAckTxPtr;
    pka_tx_ptr_dump[pka_ptr_dump_idx].pNakTxPtr = pNakTxPtr;
    if (++pka_ptr_dump_idx >= MAX_PKT_TXPTR_DUMP) {
        assert(0);
        pka_ptr_dump_idx = 0;
    }
}
#endif /* #if (HWMAC_DBG_PKA_TXDUMP != false) */

#if (HWMAC_DBG_PKA_TXMONITOR != false)
pka_share_tx_monitor pka_tx_monitor;
/**************************************************************************
 *
 * Function : pka_share_txptr_dump
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description:
**************************************************************************/
__attribute__((optimize("O3"))) void pka_share_tx_monitor_chk(void)
{
    uint32_t CurNatClk = *((volatile uint32_t *)REG_CONN_NATIVE_CLK_ADDR);

    if (pka_tx_monitor.TxMonitorClk == 0) {
        pka_tx_monitor.TxMonitorClk = ((CurNatClk + 3200) & 0x0FFFFFFF);
        pka_tx_monitor.TxLeAclPktCnt = pka_tx_monitor.TxHidPktCnt =\
            pka_tx_monitor.TxTotalPktCnt = pka_tx_monitor.TxEmptyPktCnt = 0;
    } else {
        if ((pka_tx_monitor.TxMonitorClk - CurNatClk) & 0x08000000) {
            LOG_MSGID_I(riscv_pka, "[PKA][TX] TxTotal:%d TxAcl:%d TxHid:%d CurTxEmpty:%d", 4,
                pka_tx_monitor.TxTotalPktCnt,
                pka_tx_monitor.TxLeAclPktCnt,
                pka_tx_monitor.TxHidPktCnt,
                pka_tx_monitor.TxEmptyPktCnt);
            pka_tx_monitor.TxMonitorClk = ((CurNatClk + 3200) & 0x0FFFFFFF);
            pka_tx_monitor.TxLeAclPktCnt = pka_tx_monitor.TxHidPktCnt =\
                pka_tx_monitor.TxTotalPktCnt = pka_tx_monitor.TxEmptyPktCnt = 0;
        }
    }
}
#endif /* HWMAC_DBG_PKA_TXDUMP */

#if defined(AIR_2_4G_RELIABLE_RETRASMISSION)
t_pka_share_tx_hid_ptr g_pLastGetHidTx = NULL;

/**************************************************************************
 *
 * Function : pka_share_updt_hid_tx_ptr
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description:
**************************************************************************/
__attribute__((optimize("O3"))) void pka_share_updt_hid_tx_ptr(void)
{
    if (pka_cb_type == PKA_SHARE_TX_PREPARE_CB_TYPE_RT) {
        t_pka_share_tx_hid_ptr pHidTx = &pka_share_tx_hid_ctl.HidTxBuf[0];

        //@ Clear Data/PDU Len by buffer valid
        for(uint8_t idx = 0; idx < pka_share_tx_hid_ctl.HidTxBufNum; idx++, pHidTx++) {
            if (pHidTx->state == BUFFER_PUSH_TO_HWMAC) {
                pHidTx->valid = pka_tx_buf_is_valid((uint8_t *)pHidTx->pPtr);
                if (pHidTx->valid != false) {
                    pHidTx->state = BUFFER_FREE;
                    pka_share_tx_hid_ctl.HidTxBufAllcNum--;
                }
            }
        }
    }
}

/**************************************************************************
 *
 * Function : pka_share_get_hid_tx_ptr
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description:
**************************************************************************/
__attribute__((optimize("O3"))) void *pka_share_get_hid_tx_ptr(void)
{
    if (pka_cb_type == PKA_SHARE_TX_PREPARE_CB_TYPE_RT) {
        if (pka_share_tx_hid_ctl.HidTxBufAllcNum < pka_share_tx_hid_ctl.HidTxBufNum) {
            t_pka_share_tx_hid_ptr pHidTx = NULL;
            t_pka_share_tx_hid_buf_ctl_ptr pPkaShareTxHidCtl = &pka_share_tx_hid_ctl;
            uint8_t max_tx_num = pPkaShareTxHidCtl->HidTxBufNum;
            uint8_t search_start_idx = pPkaShareTxHidCtl->HidTxBufIdx, search_cnt = 0;

            //@ Clear Data/PDU Len by buffer valid
            for (search_cnt = 0; search_cnt < max_tx_num; search_cnt++) {
                pHidTx = &pPkaShareTxHidCtl->HidTxBuf[(search_start_idx + search_cnt) % max_tx_num];
                if (pHidTx->state == BUFFER_FREE) {
                    pHidTx->state = BUFFER_ALLC_BY_APP;
                    pPkaShareTxHidCtl->HidTxBufAllcNum++;
                    g_pLastGetHidTx = pHidTx;
                    return pHidTx->pPtr;
                }
            }
        }
    }
    return NULL;
}

/**************************************************************************
 *
 * Function : pka_share_push_hid_tx_ptr
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description:
**************************************************************************/
__attribute__((optimize("O3"))) void pka_share_push_hid_tx_ptr(void* pTxPtr)
{
    if (pka_cb_type == PKA_SHARE_TX_PREPARE_CB_TYPE_RT) {
        if ((g_pLastGetHidTx->pPtr == pTxPtr) && (g_pLastGetHidTx->state == BUFFER_ALLC_BY_APP)) {
            g_pLastGetHidTx->state = BUFFER_FREE;
            pka_share_tx_hid_ctl.HidTxBufAllcNum--;
        }
//        assert(g_pLastGetHidTx->pPtr == pTxPtr);
    }
    return NULL;
}

/**************************************************************************
 *
 * Function : pka_share_advanced_tx_prepare_rt
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description:
**************************************************************************/
__attribute__((optimize("O3"))) uint32_t pka_share_advanced_tx_prepare_rt(void)
{
    #define COMPENSATION_TIME  7
    uint32_t timestamp_key_submitted = COMPENSATION_TIME;
    void *pLeAclTxPtrCandidate;
    void *pHidTxPtrCandidate;
    void *pPkaCandTxPtr[3];
    t_pka_share_tx_hid_buf_ctl_ptr pPkaShareTxHidCtl = &pka_share_tx_hid_ctl;
    t_pka_share_tx_hid_ptr pHidTx = &pPkaShareTxHidCtl->HidTxBuf[pPkaShareTxHidCtl->HidTxBufIdx];
    uint32_t mask;

    //!! Prepare Tx, Critical Section !!//
    hal_nvic_save_and_set_interrupt_mask(&mask);

    if (g_riscv_ccni_irq_occur == false) {
        //@ Pick LeAcl candiate.
        pLeAclTxPtrCandidate = pPkaShareTxHidCtl->pLeAclTxPtr;
        //@ Pick HID candidate if HID len isn't 0
        pHidTxPtrCandidate = (pHidTx->state == BUFFER_ALLC_BY_APP) ? pHidTx->pPtr : NULL;

        //@ Fill Hwmac NAK Tx Ptr (no need, hwamc would move ACK TxPtr to NAK TxPtr itself by Rx Status)

        //@ Fill Hwmac ACK Tx Ptr
        pPkaCandTxPtr[HWMAC_ACK] = *g_pPkaRtInfo->CandiTxPtr[HWMAC_ACK];
        if (pPkaCandTxPtr[HWMAC_ACK] == g_pEmptyPktPtr) { // add riscv ccni interrupt check due to it may influence tx timing.
            if (pLeAclTxPtrCandidate != NULL) {
                *g_pPkaRtInfo->CandiTxPtr[HWMAC_ACK] = pLeAclTxPtrCandidate; // fill HWMAC LT first.
                pPkaCandTxPtr[HWMAC_ACK] = pLeAclTxPtrCandidate;
//                pka_gpio_shot(25);
                pLeAclTxPtrCandidate = pPkaShareTxHidCtl->pLeAclTxPtr = NULL;
                hid_express_dbg_inc_pka_acl_cnt();
            } else {
                if (pHidTxPtrCandidate != NULL) {
                    do {
                        *g_pPkaRtInfo->CandiTxPtr[HWMAC_ACK] = pHidTxPtrCandidate; // fill HWMAC LT first.
//                        pka_gpio_shot(23);
                    } while(*g_pPkaRtInfo->CandiTxPtr[HWMAC_ACK] != pHidTxPtrCandidate); // make sure TxPtr filled successfully
//                    pka_gpio_put_data(pPkaShareTxHidCtl->HidTxBufIdx, 36, 37);

#if defined(AIR_BASIC_LA_DEBUG) || defined(CONFIG_AIR_HID_DEBUG_PIN)
#include "hid_common_debug.h"
                    DBG_LATENCY_H(DBG_SIGNAL_SPI_CB);
#endif

#if defined(AIR_REPORT_DATA_LOG)
                    extern void hid_express_copy_report_for_debug_print(uint8_t* ack, uint8_t* nack);
                    // uint8_t *data = ((uint8_t*)pHidTxPtrCandidate)+20;
                    // *data |= 0x80;
                    hid_express_copy_report_for_debug_print(((uint8_t*)pHidTxPtrCandidate)+20, NULL);
#endif

                    pPkaCandTxPtr[HWMAC_ACK] = pHidTxPtrCandidate;
                    pHidTxPtrCandidate = NULL;

                    //@ change buffer stae due to it push to HWMAC w/ free
                    pHidTx->state = BUFFER_PUSH_TO_HWMAC;

                    //@ Update Tx Buffer Idx;
                    pPkaShareTxHidCtl->HidTxBufIdx++;
                    pPkaShareTxHidCtl->HidTxBufIdx %= pPkaShareTxHidCtl->HidTxBufNum;

                    //@ APP request
                    GPT_GET_FREE_RUN_COUNT_US(timestamp_key_submitted);
                    hid_express_dbg_inc_pka_hid_cnt();
                }
            }
            pka_tx_buf_clear_buf_valid(pPkaCandTxPtr[HWMAC_ACK]);
        }

        //@ Fill Hwmac BKUP Tx Ptr
        pPkaCandTxPtr[HWMAC_NAK] = *g_pPkaRtInfo->CandiTxPtr[HWMAC_NAK];
        pPkaCandTxPtr[HWMAC_BKUP] = *g_pPkaRtInfo->CandiTxPtr[HWMAC_BKUP];

        if (pPkaCandTxPtr[HWMAC_BKUP] == g_pEmptyPktPtr) {
            if (pLeAclTxPtrCandidate != NULL) {
                *g_pPkaRtInfo->CandiTxPtr[HWMAC_BKUP] = pLeAclTxPtrCandidate; // fill HWMAC LT first.
                pPkaCandTxPtr[HWMAC_BKUP] = pLeAclTxPtrCandidate;
//                pka_gpio_shot(25);pka_gpio_shot(25);
                pPkaShareTxHidCtl->pLeAclTxPtr = NULL;
                hid_express_dbg_inc_pka_acl_cnt();
            } else {
                //@ Get new HID packet if need
                if (pHidTxPtrCandidate == NULL) {
                    pHidTx = &pPkaShareTxHidCtl->HidTxBuf[pPkaShareTxHidCtl->HidTxBufIdx];
                    if (pHidTx->state == BUFFER_ALLC_BY_APP) {
                        pHidTxPtrCandidate = pHidTx->pPtr;
                    }
                }
                //@ Push it to HWMAC
                if ((pHidTxPtrCandidate != NULL) &&
                    (pPkaCandTxPtr[HWMAC_ACK] != pHidTxPtrCandidate) &&
                    (pPkaCandTxPtr[HWMAC_NAK] != pHidTxPtrCandidate)) {
                    do {
                        *g_pPkaRtInfo->CandiTxPtr[HWMAC_BKUP] = pHidTxPtrCandidate; // fill HWMAC LT first.
//                      pka_gpio_shot(24);
                    } while (*g_pPkaRtInfo->CandiTxPtr[HWMAC_BKUP] != pHidTxPtrCandidate); // make sure TxPtr filled successfully
//                    pka_gpio_put_data(pPkaShareTxHidCtl->HidTxBufIdx, 36, 37);
                    pPkaCandTxPtr[HWMAC_BKUP] = pHidTxPtrCandidate;
                    *pka_share_ptr->bt_info.rt.hwmt_tpollgo_ptr = 2;

#if defined(AIR_REPORT_DATA_LOG)
                    extern void hid_express_copy_report_for_debug_print(uint8_t* ack, uint8_t* nack);
                    // uint8_t *data = ((uint8_t*)pHidTxPtrCandidate)+20;
                    // *data |= 0xC0;
                    hid_express_copy_report_for_debug_print(((uint8_t*)pHidTxPtrCandidate)+20, NULL);
#endif
                    //@ change buffer stae due to it push to HWMAC w/ free
                    pHidTx->state = BUFFER_PUSH_TO_HWMAC;

                    //@ Update Tx Buffer Idx;
                    pPkaShareTxHidCtl->HidTxBufIdx++;
                    pPkaShareTxHidCtl->HidTxBufIdx %= pPkaShareTxHidCtl->HidTxBufNum;

                    //@ APP request
                    GPT_GET_FREE_RUN_COUNT_US(timestamp_key_submitted);
                    hid_express_dbg_inc_pka_hid_cnt();
                }
            }
            pka_tx_buf_clear_buf_valid(pPkaCandTxPtr[HWMAC_BKUP]);
        }

        //@ Workaround if HWMAC didn't get the hid packet, riscv_pka need to set buf valid manually to drop this packet.
        if ((pPkaCandTxPtr[HWMAC_NAK] == g_pEmptyPktPtr) &&
            (pPkaCandTxPtr[HWMAC_ACK] == g_pEmptyPktPtr) &&
            (pPkaCandTxPtr[HWMAC_BKUP] == g_pEmptyPktPtr) &&
            (pHidTx->state == BUFFER_PUSH_TO_HWMAC)) {
            pka_tx_buf_set_valid(pHidTx->pPtr);
            hid_express_dbg_inc_pka_hid_drop_cnt();
//            pka_gpio_shot(38);
        }
    }

    // Get LE ACL candidate from pka
    if (pPkaShareTxHidCtl->pLeAclTxPtr == NULL) {
        share_buffer_hw_semaphore_take(4);
        pPkaShareTxHidCtl->pLeAclTxPtr = *g_pPkaRtInfo->NextTxPtr;
        *g_pPkaRtInfo->NextTxPtr = NULL;
        share_buffer_hw_semaphore_give(4);
    }
    hal_nvic_restore_interrupt_mask(mask);

    PKA_MONITOR_INC_TX_TOTAL_CNT();
    return timestamp_key_submitted - COMPENSATION_TIME; // compensate for the delay of timestamp latch time.
}

#else
__attribute__((optimize("O3"))) uint32_t pka_share_advanced_tx_prepare_rt(void)
{
#if 1
#if 1
    void **pka_hid_tx_pkt_p;
    void **pka_candi_tx_p[2];
    void *CurTxPtr;
    void *NextTxPtr;

    NextTxPtr = *pka_share_ptr->bt_info.rt.NextTxPtr;
    CurTxPtr = *pka_share_ptr->bt_info.rt.CurTxPtr;
    pka_candi_tx_p[0] = pka_share_ptr->bt_info.rt.CandiTxPtr[0];
    pka_candi_tx_p[1] = pka_share_ptr->bt_info.rt.CandiTxPtr[1];
    pka_hid_tx_pkt_p = &(pka_share_ptr->bt_info.rt.HidTxPktPtr[0]);

    bool cur_tx_empty = pka_tx_buf_is_empty(CurTxPtr);
    bool cur_tx_hid = ((CurTxPtr == pka_hid_tx_pkt_p[0]) || (CurTxPtr == pka_hid_tx_pkt_p[1]));
    // Empty
    if (cur_tx_empty) {
        // Empty => ACL
        if (pka_tx_buf_is_empty(NextTxPtr) == false) {
            *pka_candi_tx_p[0] = NextTxPtr;
        // Empty => HID
        } else {
            if (pka_tx_buf_is_empty(pka_hid_tx_pkt_p[0])) {
                *pka_candi_tx_p[0] = pka_share_ptr->bt_info.rt.EmptyPktPtr;
            } else {
                *pka_candi_tx_p[0] = pka_hid_tx_pkt_p[0];
            }
        }
        *pka_candi_tx_p[1] = CurTxPtr;
    // HID => ??
    } else if (cur_tx_hid) {
        // HID => ACL
        if (pka_tx_buf_is_empty(NextTxPtr) == false) {
            *pka_candi_tx_p[0] = NextTxPtr;
        //HID => HID
        } else {
            if (pka_tx_buf_is_empty(pka_hid_tx_pkt_p[0])) {
                *pka_candi_tx_p[0] = pka_share_ptr->bt_info.rt.EmptyPktPtr;
            } else {
                *pka_candi_tx_p[0] = pka_hid_tx_pkt_p[0];
            }
        }
        if (pka_tx_buf_is_empty(pka_hid_tx_pkt_p[1])) {
            *pka_candi_tx_p[1] = pka_share_ptr->bt_info.rt.EmptyPktPtr;
        } else {
            *pka_candi_tx_p[1] = pka_hid_tx_pkt_p[1];
        }
    // ACL => ??
    } else {
            // frag continue
            if (pka_tx_buf_remain_length(CurTxPtr) > 0) {
                *pka_candi_tx_p[0] = CurTxPtr;
            // frag complete
            } else {
                if (pka_tx_buf_is_empty(pka_hid_tx_pkt_p[1])) {
                    *pka_candi_tx_p[0] = pka_share_ptr->bt_info.rt.EmptyPktPtr;
                } else {
                    *pka_candi_tx_p[0] = pka_hid_tx_pkt_p[1];
                }
            }
            *pka_candi_tx_p[1] = CurTxPtr;
    }
#else
    if (pka_tx_buf_is_empty(*pka_share_ptr->bt_info.rt.NextTxPtr) == false) {
        // HID => LE
        if (pka_tx_buf_is_hid(*pka_share_ptr->bt_info.rt.CurTxPtr)) {
            *pka_share_ptr->bt_info.rt.CandiTxPtr[0] = *pka_share_ptr->bt_info.rt.NextTxPtr;
            *pka_share_ptr->bt_info.rt.CandiTxPtr[1] = *pka_share_ptr->bt_info.rt.NextTxPtr;
        // LE => LE
        } else {
            // frag continue
            if (pka_tx_buf_remain_length(*pka_share_ptr->bt_info.rt.CurTxPtr) > 0) {
                *pka_share_ptr->bt_info.rt.CandiTxPtr[0] = *pka_share_ptr->bt_info.rt.CurTxPtr;
            // frag complete
            } else {
                *pka_share_ptr->bt_info.rt.CandiTxPtr[0] = *pka_share_ptr->bt_info.rt.NextTxPtr;
            }
            *pka_share_ptr->bt_info.rt.CandiTxPtr[1] = *pka_share_ptr->bt_info.rt.CurTxPtr;
        }
        pka_flag_set_loading(1);
    } else {
        // HID => HID
        if (pka_tx_buf_is_hid(*pka_share_ptr->bt_info.rt.CurTxPtr)) {
            *pka_share_ptr->bt_info.rt.CandiTxPtr[0] = pka_share_ptr->bt_info.rt.HidTxPktPtr[0];
            *pka_share_ptr->bt_info.rt.CandiTxPtr[1] = pka_share_ptr->bt_info.rt.HidTxPktPtr[1];
        // LE => HID
        } else {
            *pka_share_ptr->bt_info.rt.CandiTxPtr[0] = pka_share_ptr->bt_info.rt.HidTxPktPtr[1];
            *pka_share_ptr->bt_info.rt.CandiTxPtr[1] = *pka_share_ptr->bt_info.rt.CurTxPtr;
        }
    }
#endif
#else
    if (pHwmtLeAcl->NextTxPtr[0] != &gLeEmptyPdu) {
        // HID => LE
        if (LcUllHid_IsHID(pLePkt)) {
            pLTran->UllHidTxPtr[0] = pHwmtLeAcl->NextTxPtr[0];
            pLTran->UllHidTxPtr[1] = pHwmtLeAcl->NextTxPtr[0];
        // LE => LE
        } else {
            pLTran->UllHidTxPtr[0] = pHwmtLeAcl->NextTxPtr[0];
            pLTran->UllHidTxPtr[1] = (uint32_t)pLePkt;
        }
        pLeAclCtl->HwmacCtl.Flag.field.TxLoading = 1;
    } else {
        // HID => HID
        if (LcUllHid_IsHID(pLePkt)) {
            pLTran->UllHidTxPtr[0] = (uint32_t)&AirHidTxPkt[0];
            pLTran->UllHidTxPtr[1] = (uint32_t)&AirHidTxPkt[1];
        // LE => HID
        } else {
            pLTran->UllHidTxPtr[0] = (uint32_t)&AirHidTxPkt[1];
            pLTran->UllHidTxPtr[1] = (uint32_t)pLePkt;
        }
    }
#endif
    return 0;
}
#endif

void pka_share_tx_forward_prepare_rtt0(void)
{
#if 1
    *pka_share_ptr->bt_info.rtt.CandiTxPtr[1] = pka_share_ptr->bt_info.rtt.HidTxPktPtr[1];
    *pka_share_ptr->bt_info.rtt.CandiTxPtr[3] = pka_share_ptr->bt_info.rtt.HidTxPktPtr[3];
    if (pka_tx_buf_is_hid(*pka_share_ptr->bt_info.rtt.CurTxPtr)) {
        *pka_share_ptr->bt_info.rtt.CandiTxPtr[0] = pka_share_ptr->bt_info.rtt.HidTxPktPtr[0];
        *pka_share_ptr->bt_info.rtt.CandiTxPtr[2] = pka_share_ptr->bt_info.rtt.HidTxPktPtr[2];
    } else {
        *pka_share_ptr->bt_info.rtt.CandiTxPtr[0] = pka_share_ptr->bt_info.rtt.HidTxPktPtr[1];
        *pka_share_ptr->bt_info.rtt.CandiTxPtr[2] = pka_share_ptr->bt_info.rtt.HidTxPktPtr[3];
    }
#else
        // set tx ptrs
        pLETXDATA pLePkt = (pLETXDATA)pLTran->TxBufPtr;
        pLTran->UllHidTxPtr[1] = (uint32_t)&AirHidTxPkt[1];
        pLTran->UllHidTxPtr[3] = (uint32_t)&AirHidTxPkt[3];
        if (LcUllHid_IsHID(pLePkt)) {
            pLTran->UllHidTxPtr[0] = (uint32_t)&AirHidTxPkt[0];
            pLTran->UllHidTxPtr[2] = (uint32_t)&AirHidTxPkt[2];
        } else {
            pLTran->UllHidTxPtr[0] = (uint32_t)&AirHidTxPkt[1];
            pLTran->UllHidTxPtr[2] = (uint32_t)&AirHidTxPkt[3];
        }
#endif
}
uint8_t pka_share_get_current_report_rate(void)
{
    // AIRHIDCIS_REPORT_RATE_8K (7) -> HID_REPORT_RATE_8K_HZ (6)
    // AIRHIDCIS_REPORT_RATE_4K (6) -> HID_REPORT_RATE_4K_HZ (5)
    //                              ...
    // AIRHIDCIS_REPORT_RATE_250(2) -> HID_REPORT_RATE_250_HZ(1)
    // AIRHIDCIS_REPORT_RATE_125(1) -> HID_REPORT_RATE_125_HZ(0)
    uint8_t report_rate = pka_share_ptr->bt_info.rt.CurrentReportRate - 1;
    if (report_rate >= PKA_REPORT_RATE_TOTAL_NUM) { // PKA_REPORT_RATE_TOTAL_NUM : 7
        report_rate = 0xF; //invalid value
    }
    return report_rate;
}

uint8_t pka_share_get_current_max_pdu_len(void)
{
    // Return pLeAclCtl->TxBuffer.PreferTxSize
    if (pka_share_ptr != NULL) {
        if (pka_share_ptr->bt_info.rt.max_pdu_len_ptr != NULL) {
            return *pka_share_ptr->bt_info.rt.max_pdu_len_ptr;
        }
    }
    return 0;
}
#endif /* AIR_PKA_SHARE_ENABLE */
