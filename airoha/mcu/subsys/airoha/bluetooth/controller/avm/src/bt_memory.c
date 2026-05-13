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

#include "avm_external.h"
#include "bt_linknode.h"
#include "avm_memory.h"
#include "bt_debug.h"
#include "bt_common_upper_layer.h"
#include <zephyr/logging/log.h>
#define thisMODULE btmem
LOG_MODULE_REGISTER(thisMODULE);

#define  BT_MM_BLK_VER      0
#define  BT_MM_FOOTER_NEW   0xBABEC0DE

#if 0
static const uint16_t bt_mm_cb_size_table[] = {
    [BT_MEMORY_CONTROL_BLOCK_TIMER]            = sizeof(bt_timer_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_TIMER
    [BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION]    = sizeof(bt_connection_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION
#ifdef __BT_HB_DUO__
    [BT_MEMORY_CONTROL_BLOCK_EDR_CONNECTION]       = sizeof(bt_gap_connection_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_EDR_CONNECTION
    [BT_MEMORY_CONTROL_BLOCK_GATT]        = sizeof(bt_gatt_over_bredr_channel_t),
    [BT_MEMORY_CONTROL_BLOCK_RFCOMM]      = sizeof(bt_rfcomm_session_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_RFCOMM
    [BT_MEMORY_CONTROL_BLOCK_AVRCP]       = sizeof(bt_avrcp_context_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_AVRCP
    [BT_MEMORY_CONTROL_BLOCK_PBAPC]       = sizeof(bt_pbapc_context_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_PBAPC
    [BT_MEMORY_CONTROL_BLOCK_A2DP_SEP]         = sizeof(bt_a2dp_sep_info_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_A2DP_SEP
    [BT_MEMORY_CONTROL_BLOCK_A2DP]        = sizeof(bt_a2dp_streaming_info_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_A2DP
    [BT_MEMORY_CONTROL_BLOCK_HFP]         = sizeof(bt_hfp_channel_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_HFP
    [BT_MEMORY_CONTROL_BLOCK_AWS]         = sizeof(bt_aws_channel_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_AWS
    [BT_MEMORY_CONTROL_BLOCK_SPP]   = sizeof(bt_spp_connection_t), // one control bloc ksize for BT_MEMORY_CONTROL_BLOCK_SPP
    [BT_MEMORY_CONTROL_BLOCK_HID] = sizeof(bt_hid_context_t),
    [BT_MEMORY_CONTROL_BLOCK_AWS_MCE]         = sizeof(bt_aws_mce_channel_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_AWS_MCE
    [BT_MEMORY_CONTROL_BLOCK_HSP] = sizeof(bt_hsp_channel_t),
    [BT_MEMORY_CONTROL_BLOCK_AVRCP_EX]       = sizeof(bt_avrcp_ex_context_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_AVRCP
    [BT_MEMORY_CONTROL_BLOCK_AIRUPDATE] = sizeof(bt_airupdate_channel_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_AIRUPDATE
    [BT_MEMORY_CONTROL_BLOCK_CTP]         = sizeof(bt_ctp_connection_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_CTP
    [BT_MEMORY_CONTROL_BLOCK_L2CAP]         = sizeof(bt_l2cap_channel_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_L2CAP
#endif
    [BT_MEMORY_CONTROL_BLOCK_LE_ADV_SET]  = sizeof(bt_le_adv_set_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_LE_ADV_SET
    [BT_MEMORY_CONTROL_BLOCK_LE_L2CAP_FIX_CHANNEL] = sizeof(bt_l2cap_fix_channel_context_t),        // one control block size for BT_MEMORY_CONTROL_BLOCK_LE_L2CAP_FIX_CHANNEL
    [BT_MEMORY_CONTROL_BLOCK_BREDR_L2CAP_FIX_CHANNEL] = sizeof(bt_l2cap_fix_channel_context_t),     // one control block size for BT_MEMORY_CONTROL_BLOCK_LE_L2CAP_FIX_CHANNEL
#ifdef __BT_HB_DUO__
    [BT_MEMORY_CONTROL_BLOCK_MAPC]       = sizeof(bt_mapc_context_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_MAPC
#endif
#ifdef BT_LE_AUDIO_ENABLE
    [BT_MEMORY_CONTROL_BLOCK_LE_CIS_CONNECTION]    = sizeof(bt_cis_connection_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_LE_CIS_CONNECTION
#endif
    [BT_MEMORY_CONTROL_BLOCK_LE_OTP]         = sizeof(bt_l2cap_le_cbfcm_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_LE_OTP
    [BT_MEMORY_CONTROL_BLOCK_LE_ULL]         = sizeof(bt_ull_le_air_cis_connection_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_LE_ULL
#ifdef BT_EATT_ENABLE
    [BT_MEMORY_CONTROL_BLOCK_EATT]         = sizeof(bt_le_eatt_t), // one control block size for BT_MEMORY_CONTROL_BLOCK_EATT
#endif
};
#endif

/* Weak symbol declaration */
#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_driver_get_mm_control_blk=_default_bt_driver_get_mm_control_blk")
#pragma comment(linker, "/alternatename:_bt_driver_get_mm_footer_info=_default_bt_driver_get_mm_footer_info")
#pragma comment(linker, "/alternatename:_bt_driver_get_mm_reserve_size=_default_bt_driver_get_mm_reserve_size")
#pragma comment(linker, "/alternatename:_bt_driver_get_mm_tx_if_packet_queue=_default_bt_driver_get_mm_tx_if_packet_queue")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_driver_get_mm_control_blk = default_bt_driver_get_mm_control_blk
#pragma weak bt_driver_get_mm_footer_info = default_bt_driver_get_mm_footer_info
#pragma weak bt_driver_get_mm_reserve_size = default_bt_driver_get_mm_reserve_size
#pragma weak bt_driver_get_mm_tx_if_packet_queue = default_bt_driver_get_mm_tx_if_packet_queue
#else
#error "Unsupported Platform"
#endif


bt_mm_pool_control_blk_t *bt_mm_cb_p = NULL;
bt_tx_queue_t *bt_mm_cmd_queue_p = NULL;
bt_tx_queue_t *bt_mm_tx_if_packet_queue_p = NULL;

static uint8_t BT_MM_FOOTER_SIZE = 0;
static uint32_t BT_MM_FOOTER = 0;
static uint32_t bt_mm_reserve_size[3] = {0};

static uint8_t tx_oom_flag = 0;
static uint32_t tx_req_size = 0;
static uint32_t bt_mm_is_allocatable_packet_internal(bt_memory_packet_t type, uint32_t size);
//extern void bt_driver_hw_semaphore_lock();
//extern void bt_driver_hw_semaphore_unlock();

void default_bt_driver_get_mm_control_blk(bt_mm_pool_control_blk_t **mm_blk, bt_tx_queue_t **tx_queue)
{
    BT_LOGD("BT","default_bt_driver_get_mm_control_blk BT_MEMORY_CONTROL_BLOCK_NUM = %d \n", BT_MEMORY_CONTROL_BLOCK_NUM);

    static bt_mm_pool_control_blk_t bt_mm_cb_temp;
    static bt_tx_queue_t bt_mm_cmd_queue_temp;
    
    BT_LOGD("BT","bt_mm_cb_temp = %p,  bt_mm_cmd_queue_temp = %p \n", &bt_mm_cb_temp, &bt_mm_cmd_queue_temp);    
    BT_LOGD("BT","bt_mm_cb_temp size = %d,  bt_mm_cmd_queue_temp size = %d \n", sizeof(bt_mm_cb_temp), sizeof(bt_mm_cmd_queue_temp));    

    bt_memset(&bt_mm_cb_temp, 0, sizeof(bt_mm_cb_temp));
    bt_memset(&bt_mm_cmd_queue_temp, 0, sizeof(bt_mm_cmd_queue_temp));
    bt_mm_cb_temp.version = BT_MM_BLK_VER;
    bt_mm_cb_temp.blk_len = (uint8_t)sizeof(bt_mm_pool_control_blk_t);

    *mm_blk = &bt_mm_cb_temp;
    *tx_queue = &bt_mm_cmd_queue_temp;
    return;
}

uint32_t default_bt_driver_get_mm_footer_info()
{
    return BT_MM_FOOTER_NEW;
}

uint32_t default_bt_driver_get_mm_reserve_size(bt_memory_packet_t type)
{
    return 0;
}

bt_tx_queue_t *default_bt_driver_get_mm_tx_if_packet_queue()
{
    return NULL;
}
extern void bt_driver_get_mm_control_blk(bt_mm_pool_control_blk_t **mm_blk, bt_tx_queue_t **tx_queue);
extern uint32_t bt_driver_get_mm_footer_info();
extern uint32_t bt_driver_get_mm_reserve_size(bt_memory_packet_t type);
extern bt_tx_queue_t *bt_driver_get_mm_tx_if_packet_queue(void);

void bt_memory_init_packet(bt_memory_packet_t type, char *buf, uint32_t size)
{
    bt_mm_tailer_t *tailer_p = NULL;
    BT_LOGD("BT","bt_memory_init_packet type = %d, size = %d \n", type, size);

    //BT_ASSERT(((uint32_t)buf & 0x03) == 0);
    if (NULL == bt_mm_cb_p || NULL == bt_mm_cmd_queue_p) {
        bt_driver_get_mm_control_blk(&bt_mm_cb_p, &bt_mm_cmd_queue_p);
        BT_MM_FOOTER = bt_driver_get_mm_footer_info();
        BT_MM_FOOTER_SIZE = (0xFFFF0000 & BT_MM_FOOTER) ? 4 : 2;

        BT_LOGD("BT","init ok, BT_MM_FOOTER = 0x%x \n", BT_MM_FOOTER);
    }

    if (4 == BT_MM_FOOTER_SIZE) {
        BT_ASSERT(size < BT_MM_MAX_SIZE);
    }
    BT_ASSERT(type <= BT_MEMORY_LMP_BUFFER);
    BT_ASSERT(bt_mm_cb_p && bt_mm_cmd_queue_p && BT_MM_FOOTER && BT_MM_FOOTER_SIZE);
    BT_ASSERT(!(size % 4) && (size >= (sizeof(bt_mm_header_t) + BT_MM_FOOTER_SIZE)));
    //Add footer.
    memcpy((void *)(buf + size - BT_MM_FOOTER_SIZE), &BT_MM_FOOTER, BT_MM_FOOTER_SIZE);
    bt_mm_reserve_size[type] = bt_driver_get_mm_reserve_size(type);
    bt_mm_tx_if_packet_queue_p = (bt_tx_queue_t *)bt_driver_get_mm_tx_if_packet_queue();

    BT_LOGD("BT","bt_mm_tx_if_packet_queue_p = 0x%x \n", (unsigned int)bt_mm_tx_if_packet_queue_p);

    if (BT_MEMORY_LMP_BUFFER != type) {
        bt_mm_cb.start_mm_h[type] = (bt_mm_header_t *)buf;
        bt_mm_cb.pool_size[type] = size;
        bt_mm_cb.search_mm_h[type] = bt_mm_cb.start_mm_h[type];
        BT_MM_SET_INFO(bt_mm_cb.start_mm_h[type]->info, size - sizeof(bt_mm_header_t), BT_MM_STATE_FREE);
        //Change footer strcuter
        if (4 == BT_MM_FOOTER_SIZE) {
            tailer_p = (bt_mm_tailer_t *)(buf + size - BT_MM_FOOTER_SIZE);
            tailer_p->size = (uint16_t)BT_MM_GET_SIZE(bt_mm_cb.start_mm_h[type]->info);
            tailer_p->footer = (uint16_t)(BT_MM_FOOTER & 0x0000FFFF);
        }
    } else {
        bt_mm_cb.lmp_start_mm_h = (bt_mm_header_t *)buf;
        bt_mm_cb.lmp_pool_size = size;
        bt_mm_cb.lmp_search_mm_h = bt_mm_cb.lmp_start_mm_h;
        BT_MM_SET_INFO(bt_mm_cb.lmp_start_mm_h->info, size - sizeof(bt_mm_header_t), BT_MM_STATE_FREE);
        //Change footer strcuter
        if (4 == BT_MM_FOOTER_SIZE) {
            tailer_p = (bt_mm_tailer_t *)(buf + size - BT_MM_FOOTER_SIZE);
            tailer_p->size = (uint16_t)BT_MM_GET_SIZE(bt_mm_cb.lmp_start_mm_h->info);
            tailer_p->footer = (uint16_t)(BT_MM_FOOTER & 0x0000FFFF);
        }
    }
    BT_MM_DBG_RECORD_CLEAR(type);
    BT_MM_GET_WAIT_TO_FREE_CLEAR(type);
    BT_MM_DBG_WAIT_TO_FREE_RECORD_ADD(type, size);
    BT_MM_DBG_PEEK_NUM_CLEAR(type);
}

uint32_t bt_memory_get_packet_peek(bt_memory_packet_t type)
{
    return BT_MM_DBG_PEEK_NUM(type);
}

void *bt_mm_get_sync_pointer_info(void)
{
    return &bt_mm_cb;
}

uint32_t bt_mm_find_suited_block(bt_memory_packet_t type, uint32_t size)
{
    bt_mm_header_t *tmp_mm = NULL;
    bt_mm_header_t *start_p = NULL;
    bt_mm_header_t **search_p = NULL;
    uint32_t pool_size = 0;

    if (BT_MEMORY_LMP_BUFFER == type) {
        tmp_mm = bt_mm_cb.lmp_start_mm_h;
        start_p = bt_mm_cb.lmp_start_mm_h;
        search_p = &(bt_mm_cb.lmp_search_mm_h);
        pool_size = bt_mm_cb.lmp_pool_size;
    } else {
        tmp_mm = bt_mm_cb.start_mm_h[type];
        start_p = bt_mm_cb.start_mm_h[type];
        search_p = &(bt_mm_cb.search_mm_h[type]);
        pool_size = bt_mm_cb.pool_size[type];
    }

    // traverse the memory list to find the suited block
    while (((char *)tmp_mm - (char *)start_p) < pool_size) {
        if (BT_MM_GET_STATE(tmp_mm->info) == BT_MM_STATE_FREE) {
            // find the match size memory block, then return it.
            if (BT_MM_GET_SIZE(tmp_mm->info) >= size) {
                (*search_p) = tmp_mm;
                return BT_STATUS_SUCCESS;
            }
        }
        tmp_mm = (bt_mm_header_t *)((char *)tmp_mm + BT_MM_GET_SIZE(tmp_mm->info) + sizeof(bt_mm_header_t));
    }
    return BT_STATUS_OUT_OF_MEMORY;
}

#if 0 
uint32_t bt_mm_get_total_free_size(bt_memory_packet_t type)
{
    bt_mm_header_t *start_p = NULL;
    bt_mm_header_t **search_p = NULL;
    uint32_t pool_size = 0;
    uint32_t free_size = 0;

    if (BT_MEMORY_LMP_BUFFER == type) {
        start_p = bt_mm_cb.lmp_start_mm_h;
        search_p = &(bt_mm_cb.lmp_search_mm_h);
        pool_size = bt_mm_cb.lmp_pool_size;
    } else {
        start_p = bt_mm_cb.start_mm_h[type];
        search_p = &(bt_mm_cb.search_mm_h[type]);
        pool_size = bt_mm_cb.pool_size[type];
    }

    bt_mm_header_t *tmp_mm = start_p;

    while (((char *)tmp_mm - (char *)start_p) < pool_size) {
        if (BT_MM_GET_STATE(tmp_mm->info) == BT_MM_STATE_FREE) {
            free_size += BT_MM_GET_SIZE(tmp_mm->info) - bt_mm_reserve_size[type] - BT_MM_FOOTER_SIZE;
        }
        tmp_mm = (bt_mm_header_t *)((char *)tmp_mm + BT_MM_GET_SIZE(tmp_mm->info) + sizeof(bt_mm_header_t));
    }
    return free_size;
}
#endif

void bt_mm_check_and_merge(bt_memory_packet_t type)
{
    bt_mm_header_t *start_p = NULL;
    bt_mm_header_t **search_p = NULL;
    uint32_t pool_size = 0;

    if (BT_MEMORY_LMP_BUFFER == type) {
        start_p = bt_mm_cb.lmp_start_mm_h;
        search_p = &(bt_mm_cb.lmp_search_mm_h);
        pool_size = bt_mm_cb.lmp_pool_size;
    } else {
        start_p = bt_mm_cb.start_mm_h[type];
        search_p = &(bt_mm_cb.search_mm_h[type]);
        pool_size = bt_mm_cb.pool_size[type];
    }

    bt_mm_header_t *tmp_mm = start_p;
    bt_mm_header_t *cur_free_mm = NULL;

    while (((char *)tmp_mm - (char *)start_p) < pool_size) {
        //void *footer = (void *)((char *)tmp_mm + sizeof(bt_mm_header_t) + BT_MM_GET_SIZE(tmp_mm->info) - BT_MM_FOOTER_SIZE);
        //BT_ASSERT(!bt_memcmp(footer, (void*)(&BT_MM_FOOTER), BT_MM_FOOTER_SIZE));

        if (BT_MM_GET_STATE(tmp_mm->info) == BT_MM_STATE_FREE) {
            if (cur_free_mm) {
                // merge.
                BT_MM_SET_SIZE(cur_free_mm->info,
                               BT_MM_GET_SIZE(cur_free_mm->info) + sizeof(bt_mm_header_t) + BT_MM_GET_SIZE(tmp_mm->info));
            } else {
                cur_free_mm = tmp_mm;
            }
            // check if need to update search.
            if (((*search_p) == NULL) || (BT_MM_GET_SIZE(cur_free_mm->info) > BT_MM_GET_SIZE((*search_p)->info))) {
                (*search_p) = cur_free_mm;
            }
        } else {
            cur_free_mm = NULL;
        }
        tmp_mm = (bt_mm_header_t *)((char *)tmp_mm + BT_MM_GET_SIZE(tmp_mm->info) + sizeof(bt_mm_header_t));
    }
}

#if 0
/* TODO: Should add a mutex to protect allocate and free. */
uint32_t bt_mm_is_allocatable_packet(bt_memory_packet_t type, uint32_t size)
{
    uint32_t ret;
    //bt_driver_hw_semaphore_lock();
    size = size + bt_mm_reserve_size[type] + BT_MM_FOOTER_SIZE;/* for footer */
    //TODO: Should we adjst the size to 4 bytes aligment?
    size = (size + 3) & 0xFFFFFFFC;
    ret = bt_mm_is_allocatable_packet_internal(type, size);
    //bt_driver_hw_semaphore_unlock();
    return ret;
}
#endif

static uint32_t bt_mm_is_allocatable_packet_internal(bt_memory_packet_t type, uint32_t size)
{
    bt_mm_header_t *start_p = NULL;
    bt_mm_header_t **search_p = NULL;

    if (BT_MEMORY_LMP_BUFFER == type) {
        start_p = bt_mm_cb.lmp_start_mm_h;
        search_p = &(bt_mm_cb.lmp_search_mm_h);
    } else {
        start_p = bt_mm_cb.start_mm_h[type];
        search_p = &(bt_mm_cb.search_mm_h[type]);
    }
    //Check search pointer
    if (((*search_p) != NULL) && (BT_MM_GET_SIZE((*search_p)->info) >= size)) {
        return BT_STATUS_SUCCESS;
    } else if (4 == BT_MM_FOOTER_SIZE) {
        return bt_mm_find_suited_block(type, size);
        //Check start pointer
    } else {
        bt_mm_check_and_merge(type);
        if (((*search_p) != NULL) && (BT_MM_GET_SIZE((*search_p)->info) >= size)) {
            return BT_STATUS_SUCCESS;
        } else {
            return BT_STATUS_OUT_OF_MEMORY;
        }
    }
}


#if 0
uint32_t bt_memory_get_all_buffer_size(bt_memory_packet_t type)
{
    if (BT_MEMORY_TX_BUFFER == type || BT_MEMORY_RX_BUFFER == type) {
        return bt_mm_cb.pool_size[type];
    } else if (type == BT_MEMORY_LMP_BUFFER) {
        return bt_mm_cb.lmp_pool_size;
    }
    return 0;
}

#ifdef BT_DEBUG
void bt_mm_dump_state(bt_memory_packet_t type)
{
    bt_mm_header_t *start_p = NULL;
    uint32_t pool_size = 0;

    if (BT_MEMORY_LMP_BUFFER == type) {
        start_p = bt_mm_cb.lmp_start_mm_h;
        pool_size = bt_mm_cb.lmp_pool_size;
    } else {
        start_p = bt_mm_cb.start_mm_h[type];
        pool_size = bt_mm_cb.pool_size[type];
    }
    bt_mm_header_t *tmp_mm = start_p;
    while (((char *)tmp_mm - (char *)start_p) < pool_size) {
        //BT_LOG_MSGID_D("MM", BTMM_001, 3, tmp_mm, BT_MM_GET_STATE(tmp_mm->info), BT_MM_GET_SIZE(tmp_mm->info));
        tmp_mm = (bt_mm_header_t *)((char *)tmp_mm + BT_MM_GET_SIZE(tmp_mm->info) + sizeof(bt_mm_header_t));
    }
}
#endif
#endif 

char *bt_mm_allocate_packet_internal(bt_memory_packet_t type, uint32_t size
#ifdef BT_DEBUG
                                     , const char *func_p, uint32_t line_p
#endif
                                    )
{
    bt_mm_header_t *new_mm = NULL;
    bt_mm_tailer_t *new_tailer = NULL;
    uint32_t new_mm_size;
#ifdef BT_DEBUG
    static bool first_oom = false;
#endif
    BT_LOGD("BT","    bt_mm_allocate_packet_internal, size = %d, type = %d, BT_MM_FOOTER_SIZE = %d  \n", size, type, BT_MM_FOOTER_SIZE ); 

    void *footer;
    size = size + bt_mm_reserve_size[type] + BT_MM_FOOTER_SIZE;/* for footer */
    bt_mm_header_t **search_p = NULL;
    bt_mm_header_t *start_p = NULL;
    uint32_t pool_size = 0;

    if (BT_MEMORY_LMP_BUFFER == type) {
        search_p = &(bt_mm_cb.lmp_search_mm_h);
        start_p = bt_mm_cb.lmp_start_mm_h;
        pool_size = bt_mm_cb.lmp_pool_size;
    } else {
        search_p = &(bt_mm_cb.search_mm_h[type]);
        start_p = bt_mm_cb.start_mm_h[type];
        pool_size = bt_mm_cb.pool_size[type];
    }

#ifdef BT_OOM_TEST_SUPPORT
    if (bt_mm_cb.packet_oom_test[type] > 0) {
        if (BT_MEMORY_TX_BUFFER == type) {
            //BT_LOG_MSGID_D("MM", BTMM_002, 0);
        } else {
            //BT_LOG_MSGID_D("MM", BTMM_003, 0);
        }
        return NULL;
    }
#endif

    //TODO: Should we adjst the size to 4 bytes aligment?
    size = (size + 3) & 0xFFFFFFFC;
    //bt_driver_hw_semaphore_lock();
    if (BT_STATUS_SUCCESS == bt_mm_is_allocatable_packet_internal(type, size)) {
        new_mm = *search_p;
    }

    if (NULL == new_mm) {//Out of memory
        //bt_driver_hw_semaphore_unlock();
#ifdef BT_DEBUG
        if (type == BT_MEMORY_TX_BUFFER) {
            //BT_LOG_MSGID_D("MM", BTMM_006, 1, size);
        } else if (type == BT_MEMORY_RX_BUFFER) {
            //BT_LOG_MSGID_D("MM", BTMM_007, 1, size);
        }
#endif
        if (type == BT_MEMORY_TX_BUFFER) {
            tx_oom_flag = 1;
            tx_req_size = size;
        }
#ifdef BT_DEBUG
        if (type == BT_MEMORY_RX_BUFFER) {
            if (!first_oom) {
                bt_mm_dump_state(type);
                first_oom = true;
            }
        }
#endif
        return NULL;
    } else {
        // assert search poniter not over it's range
        BT_ASSERT((BT_MM_GET_SIZE(new_mm->info) + (char *)new_mm) <= ((char *)(start_p) + pool_size));
    }

    //Update search_mm_h
    if (BT_MM_GET_SIZE(new_mm->info) - size >= sizeof(bt_mm_header_t) + bt_mm_reserve_size[type] + BT_MM_FOOTER_SIZE) {
        //remaining buffer size is large than sizeof(bt_mm_header_t)
        *search_p = (bt_mm_header_t *)((char *)new_mm + sizeof(bt_mm_header_t) + size);
        BT_MM_SET_INFO((*search_p)->info, (BT_MM_GET_SIZE(new_mm->info) - size - sizeof(bt_mm_header_t)), BT_MM_STATE_FREE);
        new_mm_size = size;
        // Updater free memory block footer size
        if (4 == BT_MM_FOOTER_SIZE) {
            bt_mm_tailer_t *new_tailer = (bt_mm_tailer_t *)((char *)(*search_p) + sizeof(bt_mm_header_t) + BT_MM_GET_SIZE((*search_p)->info) - BT_MM_FOOTER_SIZE);
            new_tailer->size = (uint16_t)BT_MM_GET_SIZE((*search_p)->info);
            new_tailer->footer = (uint16_t)(BT_MM_FOOTER & 0x0000FFFF);
        }
    } else { //Buffer is completely exhausted
        //printf("[MM] Buffer type[%s] is completely exhausted!", type==BT_MEMORY_TX_BUFFER?"Tx":"Rx");
        *search_p = NULL;
        new_mm_size = BT_MM_GET_SIZE(new_mm->info);
    }
    
    //Update new_mm
    BT_MM_SET_INFO(new_mm->info, new_mm_size, BT_MM_STATE_USING);

#ifdef BT_DEBUG
    first_oom = false;
#endif
    footer = (void *)((char *)new_mm + sizeof(bt_mm_header_t) + new_mm_size - BT_MM_FOOTER_SIZE);
    if (4 == BT_MM_FOOTER_SIZE) {
        new_tailer = (bt_mm_tailer_t *)footer;
        new_tailer->size = (uint16_t)BT_MM_GET_SIZE(new_mm->info);
        new_tailer->footer = (uint16_t)(BT_MM_FOOTER & 0x0000FFFF);
    } else {
        bt_memcpy(footer, (void *)(&BT_MM_FOOTER), BT_MM_FOOTER_SIZE);
    }

    //bt_driver_hw_semaphore_unlock();

    BT_MM_DBG_RECORD_ADD(type, 1);
    BT_MM_DBG_WAIT_TO_FREE_RECORD_DEL(type, BT_MM_GET_SIZE(new_mm->info));
#ifdef BT_DEBUG
    if (pool_size - BT_MM_GET_WAIT_TO_FREE(type) > BT_MM_DBG_PEEK_NUM(type)) {
        BT_MM_DBG_PEEK_NUM_SET(type, pool_size - BT_MM_GET_WAIT_TO_FREE(type));
    }
#endif
    // clear the content to 0;
    if (type == BT_MEMORY_TX_BUFFER) {
        bt_memset(((char *)new_mm + sizeof(bt_mm_header_t)), 0, (new_mm_size - BT_MM_FOOTER_SIZE));
    }

    BT_LOGD("BT","    bt_mm_allocate_packet_internal  new_mm = %p, sizeof(bt_mm_header_t) = %d,   bt_mm_reserve_size[type] = %d  \n", (new_mm) ,  sizeof(bt_mm_header_t) ,  bt_mm_reserve_size[type] ) ; 

    return (char *)new_mm + sizeof(bt_mm_header_t) + bt_mm_reserve_size[type];
}

void bt_mm_free_packet_internal(bt_memory_packet_t type, char *ptr
#ifdef BT_DEBUG
                                , const char *func_p, uint32_t line_p
#endif
                               )
{
    bt_mm_tailer_t *free_tailer = NULL;
    bt_mm_header_t *to_check_mm = NULL;
    BT_ASSERT(ptr);
    char *free_ptr = ptr - bt_mm_reserve_size[type];
    bt_mm_header_t *free_mm = (bt_mm_header_t *)((char *)free_ptr - sizeof(bt_mm_header_t));
    void *footer = (void *)((char *)free_mm + sizeof(bt_mm_header_t) + BT_MM_GET_SIZE(free_mm->info) - BT_MM_FOOTER_SIZE);
    bt_mm_header_t *start_p = NULL;
    uint32_t pool_size = 0;
    uint32_t end_addr = 0;
    if (BT_MEMORY_LMP_BUFFER == type) {
        start_p = bt_mm_cb.lmp_start_mm_h;
        pool_size = bt_mm_cb.lmp_pool_size;
    } else {
        start_p = bt_mm_cb.start_mm_h[type];
        pool_size = bt_mm_cb.pool_size[type];
    }
    end_addr = (uint32_t)((char *)start_p) + pool_size;

    if (4 == BT_MM_FOOTER_SIZE) {
        free_tailer = (bt_mm_tailer_t *)footer;
    }
#if 0 //def BT_DEBUG
    if (4 == BT_MM_FOOTER_SIZE) {
        if (free_tailer->footer != (uint16_t)(BT_MM_FOOTER & 0x0000FFFF) || BT_MM_GET_STATE(free_mm->info) != BT_MM_STATE_USING) {
            BT_LOG_MSGID_I("MM", BTMM_008, 6,
                           ptr, free_mm->info, func_p, line_p, footer, *(uint32_t *)footer);
        }
    } else if (bt_memcmp(footer, (void *)(&BT_MM_FOOTER), BT_MM_FOOTER_SIZE) || BT_MM_GET_STATE(free_mm->info) != BT_MM_STATE_USING) {
        BT_LOG_MSGID_I("MM", BTMM_008, 6,
                       ptr, free_mm->info, func_p, line_p, footer, *(uint32_t *)footer);
    }
#endif
    /* check header validation */
    BT_ASSERT(BT_MM_GET_STATE(free_mm->info) == BT_MM_STATE_USING);
    BT_ASSERT((BT_MM_GET_SIZE(free_mm->info) + (uint32_t)free_ptr) <= end_addr);
    /* check footer validation */
    if (4 == BT_MM_FOOTER_SIZE) {
        BT_ASSERT(free_tailer->footer == (uint16_t)(BT_MM_FOOTER & 0x0000FFFF));
        /* footer size must equal with header size */
        BT_ASSERT(free_tailer->size == (uint16_t)BT_MM_GET_SIZE(free_mm->info));
    } else {
        BT_ASSERT(!bt_memcmp(footer, (void *)(&BT_MM_FOOTER), BT_MM_FOOTER_SIZE));
    }
    //bt_driver_hw_semaphore_lock();

    BT_MM_SET_STATE(free_mm->info, BT_MM_STATE_FREE);
    if (4 == BT_MM_FOOTER_SIZE) {
        // Merge previous and next free block to one free block
        // a). check the next block is free state or not
        if (((uint32_t)((char *)free_mm) + BT_MM_GET_SIZE(free_mm->info) + sizeof(bt_mm_header_t)) < end_addr) {
            // skip to next block header
            to_check_mm = (bt_mm_header_t *)((char *)free_mm + BT_MM_GET_SIZE(free_mm->info) + sizeof(bt_mm_header_t));
            // next block header must less than buffer end
            BT_ASSERT((uint32_t)((char *)to_check_mm) < end_addr);
            if (BT_MM_GET_STATE(to_check_mm->info) == BT_MM_STATE_FREE) {
                BT_MM_SET_INFO(free_mm->info,
                               BT_MM_GET_SIZE(free_mm->info) + sizeof(bt_mm_header_t) + BT_MM_GET_SIZE(to_check_mm->info),
                               BT_MM_STATE_FREE);
                BT_ASSERT(BT_MM_GET_SIZE(free_mm->info) < pool_size);
                // update footer size
                free_tailer = (bt_mm_tailer_t *)((char *)free_mm + sizeof(bt_mm_header_t) + BT_MM_GET_SIZE(free_mm->info) - BT_MM_FOOTER_SIZE);
                free_tailer->size = (uint16_t)BT_MM_GET_SIZE(free_mm->info);
                free_tailer->footer = (uint16_t)(BT_MM_FOOTER & 0x0000FFFF);
                // reassigned search_mm_h pointer
                if (BT_MEMORY_LMP_BUFFER == type) {
                    bt_mm_cb.lmp_search_mm_h = free_mm;
                } else {
                    bt_mm_cb.search_mm_h[type] = free_mm;
                }
            }
        }
        // b). check the previous block is free state or not
        if (((char *)free_mm - (char *)start_p) > (sizeof(bt_mm_header_t) + BT_MM_FOOTER_SIZE)) {
            free_tailer = (bt_mm_tailer_t *)((char *)free_mm - BT_MM_FOOTER_SIZE);
            to_check_mm = (bt_mm_header_t *)((char *)free_mm - free_tailer->size - sizeof(bt_mm_header_t));
            // previous block header must less than or equal buffer start
            BT_ASSERT((char *)to_check_mm >= (char *)start_p);
            if (BT_MM_GET_STATE(to_check_mm->info) == BT_MM_STATE_FREE) {
                BT_MM_SET_SIZE(to_check_mm->info,
                               BT_MM_GET_SIZE(free_mm->info) + sizeof(bt_mm_header_t) + BT_MM_GET_SIZE(to_check_mm->info));

                BT_ASSERT(BT_MM_GET_SIZE(to_check_mm->info) < pool_size);
                // update footer size
                free_tailer = (bt_mm_tailer_t *)((char *)to_check_mm + sizeof(bt_mm_header_t) + BT_MM_GET_SIZE(to_check_mm->info) - BT_MM_FOOTER_SIZE);
                free_tailer->size = (uint16_t)BT_MM_GET_SIZE(to_check_mm->info);
                free_tailer->footer = (uint16_t)(BT_MM_FOOTER & 0x0000FFFF);
                // reassigned search_mm_h pointer
                if (BT_MEMORY_LMP_BUFFER == type) {
                    bt_mm_cb.lmp_search_mm_h = to_check_mm;
                } else {
                    bt_mm_cb.search_mm_h[type] = to_check_mm;
                }
            }
        }
    }
	
    //bt_driver_hw_semaphore_unlock();

    BT_MM_DBG_RECORD_DEL(type, 1);
    BT_MM_DBG_WAIT_TO_FREE_RECORD_ADD(type, (BT_MM_GET_SIZE(free_mm->info)));
    /* controller maybe invoke this function in IRQ, it will be caused crash */
#if 0
    if (type == BT_MEMORY_TX_BUFFER && tx_oom_flag) {
        if (BT_STATUS_SUCCESS == bt_mm_is_allocatable_packet(BT_MEMORY_TX_BUFFER, tx_req_size)) {
            bt_memory_tx_buffer_available_ind_t ind;
            ind.size = tx_req_size;
            bt_app_event_callback(BT_MEMORY_TX_BUFFER_AVAILABLE_IND, BT_STATUS_SUCCESS, (void *)&ind);
            tx_oom_flag = 0;
        }
    }
#endif
}

char *bt_mm_append_packet(char *des, uint32_t des_offset, char *src, uint32_t src_length)
{
#ifdef BT_DEBUG
    bt_mm_header_t *des_mm = (bt_mm_header_t *)((char *)des - sizeof(bt_mm_header_t));
    if (BT_MM_GET_SIZE(des_mm->info) <= (des_offset + src_length)) {
        //BT_LOG_MSGID_I("MM", BTMM_009, 4, des, des_mm->info, des_offset, src_length);
    }
    BT_ASSERT(BT_MM_GET_SIZE(des_mm->info) > (des_offset + src_length));
#endif
    return (char *) bt_memcpy(des + des_offset, src, src_length);
}

#if 0
static void bt_mm_check_size_of_value()
{
    static uint8_t checked = 0;
    if (checked) {
        return;
    }
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_TIMER >= sizeof(bt_timer_t)) && "Wrong BT_SZIE_OF_TIMER value.");
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_LE_CONNECTION >= sizeof(bt_connection_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_LE_CONNECTION value.");
#ifdef __BT_HB_DUO__
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_EDR_CONNECTION >= sizeof(bt_gap_connection_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_EDR_CONNECTION value.");
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_RFCOMM >= sizeof(bt_rfcomm_session_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_RFCOMM value.");
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_AVRCP >= sizeof(bt_avrcp_context_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_AVRCP value.");
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_PBAPC >= sizeof(bt_pbapc_context_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_PBAPC value.");
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_A2DP_SEP >= sizeof(bt_a2dp_sep_info_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_A2DP_SEP value.");
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_A2DP >= sizeof(bt_a2dp_streaming_info_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_A2DP value.");
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_HFP >= sizeof(bt_hfp_channel_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_HFP value.");
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_HSP >= sizeof(bt_hsp_channel_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_HSP value.");
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_AWS >= sizeof(bt_aws_channel_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_AWS value.");
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_SPP >= sizeof(bt_spp_connection_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_SPP value.");
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_HID >= sizeof(bt_hid_context_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_SPP value.");
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_GATT >= sizeof(bt_gatt_over_bredr_channel_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_GATT value.");
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_AWS_MCE >= sizeof(bt_aws_mce_channel_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_AWS_MCE value.");
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_AVRCP_EX >= sizeof(bt_avrcp_ex_context_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_AVRCP_EX value.");
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_CTP >= sizeof(bt_ctp_connection_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_CTP value.");
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_MAPC >= sizeof(bt_mapc_context_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_MAPC value.");
#endif
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_LE_ADV_SET >= sizeof(bt_le_adv_set_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_LE_ADV_SET.");
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_LE_L2CAP_FIX_CHANNEL >= sizeof(bt_l2cap_fix_channel_context_t)) && "Wrong BT_MEMORY_CONTROL_BLOCK_LE_L2CAP_FIX_CHANNEL.");
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_BREDR_L2CAP_FIX_CHANNEL >= sizeof(bt_l2cap_fix_channel_context_t)) && "Wrong BT_MEMORY_CONTROL_BLOCK_BREDR_L2CAP_FIX_CHANNEL.");
#ifdef BT_LE_AUDIO_ENABLE
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_LE_CIS_CONNECTION >= sizeof(bt_cis_connection_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_CIS_CONNECTION.");
#endif
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_LE_OTP >= sizeof(bt_l2cap_le_cbfcm_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_OTP.");
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_LE_ULL >= sizeof(bt_ull_le_air_cis_connection_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_ULL.");
#ifdef BT_EATT_ENABLE
    BT_ASSERT((BT_CONTROL_BLOCK_SIZE_OF_EATT >= sizeof(bt_le_eatt_t)) && "Wrong BT_CONTROL_BLOCK_SIZE_OF_EATT.");
#endif
    checked = 1;
}
#endif 

#if 0 
void bt_memory_init_control_block(bt_memory_control_block_t type, char *buf, uint32_t size)
{
    uint16_t size_of_cb;
    uint16_t i;
    uint32_t num;
    uint32_t fixed_header = type | 0xFFEEDD00;
    //BT_ASSERT(((uint32_t)buf & 0x03) == 0);
    bt_mm_check_size_of_value();
    ////BT_ASSERT(type < BT_MEMORY_CONTROL_BLOCK_NUM);
    //make the size 4-bytes alignment
    size_of_cb = (bt_mm_cb_size_table[type] + 3) & 0xFFFC;
    num = size / size_of_cb;
    //We supposed that should have a control block pointer in head of struct to link next control block.
    for (i = 0; i < num; i++) {
        //bt_mm_free_fixed_size_by_type(type, (void*)(buf + i * size_of_cb));
        *((uint32_t *)(buf + i * size_of_cb + 4)) = fixed_header;
        bt_linknode_insert_node(&bt_mm_cb.free_list, (bt_linknode_t *)(buf + i * size_of_cb), BT_NODE_FRONT);
    }
    BT_MM_DBG_RECORD_CB_NUM(type, num);
}
#endif 

bool bt_linknode_cmp_type(const bt_linknode_t *node, const void *data)
{
    if (node->front) {
        return (*(((uint8_t *)node->front) + 4) == *(const uint8_t *)data);
    } else {
        return true;
    }
}

bool bt_mm_is_fixed_buffer_free(bt_memory_control_block_t type, void *ptr)
{
    uint32_t fixed_header = type | 0xFFEEDD00;
    return *(((uint32_t *)ptr) + 1) == fixed_header;
}

bool bt_mm_is_fixed_size_available_by_type(bt_memory_control_block_t type)
{
    bt_linknode_t *addr;
    bt_linknode_t *head;

    BT_ASSERT(type < BT_MEMORY_CONTROL_BLOCK_NUM);
    head = &bt_mm_cb.free_list;
    addr = bt_linknode_travel_node(head, bt_linknode_cmp_type, (void *)&type);
    if (!addr) {
        return false;
    }
    return (addr->front != NULL);
}


#if 0
void *bt_mm_allocate_fixed_size_by_type_internal(bt_memory_control_block_t type
#ifdef BT_DEBUG
                                                 , const char *func_p, uint32_t line_p
#endif
                                                )
{
    bt_linknode_t *addr;
    uint32_t       alloc_size;

    BT_ASSERT(type < BT_MEMORY_CONTROL_BLOCK_NUM);
    alloc_size = bt_mm_cb_size_table[type];
    addr = bt_linknode_travel_node(&bt_mm_cb.free_list, bt_linknode_cmp_type, (void *)&type);

    if (addr != NULL) {
        addr = bt_linknode_remove_node(addr, BT_NODE_FRONT);
        if (addr != NULL) {
            bt_memset(addr, 0, alloc_size);
#ifdef BT_DEBUG
            BT_MM_DBG_RECORD_CB_ALLOCATE(type);
#endif
        }
    } else {
#ifdef BT_DEBUG
        //BT_LOG_MSGID_D("MM", BTMM_010, 4, type, addr, func_p, line_p);
#endif
    }
    return (void *)addr;
}

void bt_mm_free_fixed_size_by_type_internal(bt_memory_control_block_t type, void *ptr
#ifdef BT_DEBUG
                                            , const char *func_p, uint32_t line_p
#endif
                                           )
{
    bt_linknode_t *head;
    uint32_t fixed_header = type | 0xFFEEDD00;
#ifdef BT_DEBUG
    BT_MM_DBG_RECORD_CB_FREE(type);
#endif
    // The node is already in some list, should remove it from that list first.
    BT_ASSERT(ptr && (((bt_linknode_t *)ptr)->front == NULL));
    *(((uint32_t *)ptr) + 1) = fixed_header;
    BT_ASSERT(type < BT_MEMORY_CONTROL_BLOCK_NUM);
    head = &bt_mm_cb.free_list;
    bt_linknode_insert_node(head, (bt_linknode_t *)ptr, BT_NODE_FRONT);
}
#endif 

uint32_t bt_mm_get_control_block_num(bt_memory_control_block_t type)
{
    BT_ASSERT(type < BT_MEMORY_CONTROL_BLOCK_NUM);
    return BT_MM_DBG_GET_CB_NUM(type);
}


#if 0 //def BT_DEBUG
void bt_mm_debug_dump()
{
    int i;
    int free_num[BT_MEMORY_CONTROL_BLOCK_NUM] = { 0 };
    bt_linknode_t *cur = bt_mm_cb.free_list.front;
    //BT_LOG_MSGID_D("MM", BTMM_011, 0);
    //BT_MEMORY_TX_BUFFER
    //BT_LOG_MSGID_D("MM", BTMM_012, 4,
                   bt_mm_cb.pool_size[BT_MEMORY_TX_BUFFER], bt_mm_cb.start_mm_h[BT_MEMORY_TX_BUFFER], bt_mm_cb.search_mm_h[BT_MEMORY_TX_BUFFER], bt_mm_cb.allocated_packets[BT_MEMORY_TX_BUFFER]);
    //BT_LOG_MSGID_D("MM", BTMM_013, 4,
                   bt_mm_cb.pool_size[BT_MEMORY_RX_BUFFER], bt_mm_cb.start_mm_h[BT_MEMORY_RX_BUFFER], bt_mm_cb.search_mm_h[BT_MEMORY_RX_BUFFER], bt_mm_cb.allocated_packets[BT_MEMORY_RX_BUFFER]);
    //BT_LOG_MSGID_D("MM", BTMM_014, 0);
    for (i = 0; i < BT_MEMORY_CONTROL_BLOCK_NUM; ++i) {
        //BT_LOG_MSGID_D("MM", BTMM_015, 3, i, bt_mm_cb.cb_num[i], bt_mm_cb.allocated_cb[i]);
    }

    //BT_LOG_MSGID_D("MM", BTMM_016, 0);
    cur = bt_mm_cb.free_list.front;
    while (cur) {
        int idx = *(((uint8_t *)cur) + 4);
        BT_ASSERT(idx < BT_MEMORY_CONTROL_BLOCK_NUM);
        free_num[idx]++;
        cur = cur->front;
    }

    for (i = 0; i < BT_MEMORY_CONTROL_BLOCK_NUM; ++i) {
        //BT_LOG_MSGID_D("MM", BTMM_017, 2, i, free_num[i]);
    }
    //BT_LOG_MSGID_D("MM", BTMM_018, 0);
}
#endif

#ifdef BT_OOM_TEST_SUPPORT
void bt_mm_set_packet_oom(bt_memory_packet_t type, uint8_t enable)
{
    bt_mm_cb.packet_oom_test[type] = enable;
    if (BT_MEMORY_TX_BUFFER == type) {
        //BT_LOG_MSGID_D("MM", BTMM_019, 1, enable);
    } else {
        //BT_LOG_MSGID_D("MM", BTMM_020, 1, enable);
    }
}
void bt_mm_set_fixed_memory_oom(bt_memory_control_block_t type, uint8_t enable)
{
    bt_mm_cb.fixed_m_oom_test[type] = enable;
    if (BT_MEMORY_CONTROL_BLOCK_TIMER == type) {
        //BT_LOG_MSGID_D("MM", BTMM_021, 1, enable);
    } else {
        //BT_LOG_MSGID_D("MM", BTMM_022, 1, enable);
    }
}
#endif

bool BT_MM_IS_TIMER_AVAILABLE(void)
{
#ifdef BT_OOM_TEST_SUPPORT
    if (bt_mm_cb.fixed_m_oom_test[BT_MEMORY_CONTROL_BLOCK_TIMER] > 0) {
        return false;
    }
#endif
    return bt_mm_is_fixed_size_available_by_type(BT_MEMORY_CONTROL_BLOCK_TIMER);
}

bool BT_MM_IS_CONNECTION_AVAILABLE(void)
{
#ifdef BT_OOM_TEST_SUPPORT
    if (bt_mm_cb.fixed_m_oom_test[BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION] > 0) {
        return false;
    }
#endif
    return bt_mm_is_fixed_size_available_by_type(BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION);
}

void bt_mm_check_packet_integrity_internal(bt_memory_packet_t type, char *ptr)
{
    bt_mm_header_t *start_p = NULL;
    uint32_t pool_size = 0;
    bt_mm_tailer_t *new_tailer = NULL;

    if (BT_MEMORY_LMP_BUFFER == type) {
        start_p = bt_mm_cb.lmp_start_mm_h;
        pool_size = bt_mm_cb.lmp_pool_size;
    } else {
        start_p = bt_mm_cb.start_mm_h[type];
        pool_size = bt_mm_cb.pool_size[type];
    }
    char *check_ptr = ptr - bt_mm_reserve_size[type];

    bt_mm_header_t *header = (bt_mm_header_t *)((char *)check_ptr - sizeof(bt_mm_header_t));
    void *footer = (void *)((char *)check_ptr + BT_MM_GET_SIZE(header->info) - BT_MM_FOOTER_SIZE);

    /* check header */
    BT_ASSERT(BT_MM_GET_STATE(header->info) == BT_MM_STATE_USING);
    BT_ASSERT((BT_MM_GET_SIZE(header->info) + check_ptr) <= ((char *)(start_p) + pool_size));
    /* check footer */
    if (4 == BT_MM_FOOTER_SIZE) {
        new_tailer = (bt_mm_tailer_t *)footer;
        BT_ASSERT(new_tailer->footer == (uint16_t)(BT_MM_FOOTER & 0x0000FFFF));
        /* footer size must equal with header size */
        BT_ASSERT(new_tailer->size == (uint16_t)BT_MM_GET_SIZE(header->info));
    } else {
        BT_ASSERT(!bt_memcmp(footer, (void *)(&BT_MM_FOOTER), BT_MM_FOOTER_SIZE));
    }
}
void bt_mm_reinit_buffer_internal(bt_memory_packet_t type)
{
    void *footer = NULL;
    bt_mm_header_t *start_p = NULL;
    bt_mm_header_t **search_p = NULL;
    bt_mm_tailer_t *tailer_p = NULL;
    uint32_t pool_size = 0;

    if (NULL == bt_mm_cb_p || NULL == bt_mm_cmd_queue_p) {
        BT_ASSERT(0 && "bt_mm_reinit_buffer fail");
    }

    if (BT_MEMORY_LMP_BUFFER == type) {
        start_p = bt_mm_cb.lmp_start_mm_h;
        search_p = &(bt_mm_cb.lmp_search_mm_h);
        pool_size = bt_mm_cb.lmp_pool_size;
    } else {
        start_p = bt_mm_cb.start_mm_h[type];
        search_p = &(bt_mm_cb.search_mm_h[type]);
        pool_size = bt_mm_cb.pool_size[type];
    }

    //bt_driver_hw_semaphore_lock();
    //reinitial header
    BT_MM_SET_INFO(start_p->info, pool_size - sizeof(bt_mm_header_t), BT_MM_STATE_FREE);
    //Set footer
    footer = (void *)((char *)start_p + pool_size - BT_MM_FOOTER_SIZE);
    if (4 == BT_MM_FOOTER_SIZE) {
        tailer_p = (bt_mm_tailer_t *)(footer);
        tailer_p->size = (uint16_t)BT_MM_GET_SIZE(start_p->info);
        tailer_p->footer = (uint16_t)(BT_MM_FOOTER & 0x0000FFFF);
    } else {
        memcpy((void *)footer, &BT_MM_FOOTER, BT_MM_FOOTER_SIZE);
    }
    //reassign search pointer
    *search_p = start_p;
    //bt_driver_hw_semaphore_unlock();
}

uint32_t bt_mm_get_footer(void)
{
    return BT_MM_FOOTER;
}

