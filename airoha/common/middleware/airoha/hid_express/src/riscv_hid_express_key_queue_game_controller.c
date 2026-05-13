/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
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

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)

/* Includes ------------------------------------------------------------------*/
#include "riscv_hid_express.h"
#include "riscv_hid_express_key_queue_game_controller.h"
#include "hal_eint_internal.h"
#include "riscv_hid_express_2_4G_mode.h"
#include "hal_gpt.h"
#include <stdint.h>

/* Private define ------------------------------------------------------------*/
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER) && defined(AIR_HID_BT_MODE)
#define KEY_EXPIRE_TIME 1000000 //us
// #define KEY_EXPIRE_TIME 10000
#else
#define KEY_EXPIRE_TIME 1000000 //us
#endif

#define SKIP_FIRST_RESULT_AT_8K 0xFF    // 1st tx result of 8K is the result of previous report. Not current report.

/* Private typedef -----------------------------------------------------------*/
typedef enum {
    KEY_DELIVERY_STATE_IDLE,
    KEY_DELIVERY_STATE_TRIGGERED,
    KEY_DELIVERY_STATE_TRIGGERED_COMPLETED,
    KEY_DELIVERY_STATE_SKIP_FIRST_RESULT,
    KEY_DELIVERY_STATE_ACKED,
    KEY_DELIVERY_STATE_ABANDONED,
}T_KEY_DELIVERY_STATUS_E;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


const uint32_t hat_switch_table[16] = {
    0x0,
    0x1, /* UP */
    0x5, /* DOWN */
    0x0,
    0x7, /* LEFT */
    0x8, /* LEFT + UP */
    0x6, /* DOWN + LEFT */
    0x0,
    0x3, /* RIGHT */
    0x2, /* UP + RIGHT */
    0x4, /* RIGHT + DOWN */
    0x0,
    0x0,
    0x0,
    0x0,
    0x0
};

/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** Check if the queue is full */
bool is_queue_full(T_KEY_QUEUE_CTRL_S *kCtrl)
{
    return (((kCtrl->buf_head + 1) & KEY_BUFFER_SIZE_MASK) == kCtrl->buf_tail);
}

bool is_key_expired(uint32_t key_time, uint32_t cur_time)
{
    uint32_t duration = 0;
    hal_gpt_get_duration_count(key_time, cur_time, &duration);

    return (duration > KEY_EXPIRE_TIME);
}

/** Check if the queue is empty */
bool is_queue_empty(T_KEY_QUEUE_CTRL_S *kCtrl)
{
    return kCtrl->buf_head == kCtrl->buf_tail;
}

/** Get queue element count */
int get_queue_count(T_KEY_QUEUE_CTRL_S *kCtrl)
{
    if (kCtrl->buf_tail >= kCtrl->buf_head)
        return kCtrl->buf_tail - kCtrl->buf_head;
    else
        return KEY_BUFFER_SIZE - (kCtrl->buf_head - kCtrl->buf_tail);
}

/** Check if queue has exactly 2 elements */
bool is_queue_num_2(T_KEY_QUEUE_CTRL_S *kCtrl)
{
    return get_queue_count(kCtrl) == 2;
}

void riscv_game_controller_key_push_key_info(T_KEY_QUEUE_CTRL_S *kCtrl, uint32_t type, uint32_t item1, uint32_t item2, uint32_t timestamp) {
    // update buff head first.
    // this allow the item be modifed before next push
    kCtrl->buf_head = (kCtrl->buf_head + 1) & KEY_BUFFER_SIZE_MASK;
    T_KEY_INFO_S *key_info_write = &kCtrl->buffer[kCtrl->buf_head];

    // Reset nack counter
    key_info_write->nack_cnt = 0;

    // Set key info
    key_info_write->key_delivery_status = KEY_DELIVERY_STATE_TRIGGERED;
    key_info_write->items[0] = item1;
    key_info_write->items[1] = item2;
    key_info_write->type = type;
    key_info_write->timestamp = timestamp;
    // HID_DBG_LOG(rv_exp, "push = %x head = %d tail = %d", 3, key_info_write->items[0], kCtrl->buf_head, kCtrl->buf_tail);
}

/* Public functions ----------------------------------------------------------*/
void init_key_ctrl(T_KEY_QUEUE_CTRL_S *kCtrl, uint32_t default_key_status)
{
    kCtrl->valid_key_mask = DEFAULT_VALID_GAME_CONTROLLER_KEY_MASK;
    kCtrl->buf_head = 0;
    kCtrl->buf_tail = 0;
    kCtrl->last_pushed.word = default_key_status;
    kCtrl->last_pushed_kb_std[0] = default_key_status;
    kCtrl->last_pushed_kb_std[1] = default_key_status;
    kCtrl->last_pushed_ms = default_key_status;
    // HID_DBG_LOG(rv_exp, "init_key_ctrl", 0);
}

void riscv_game_controller_key_clear_key_pushed(T_KEY_QUEUE_CTRL_S *kCtrl)
{
    //HID_DBG_LOG(rv_exp, "[Report log]riscv_game_controller_key_clear_key_pushed, key_delivery_status = %d", 1, kCtrl->buffer[kCtrl->buf_head].key_delivery_status);
    kCtrl->valid_key_mask = DEFAULT_VALID_GAME_CONTROLLER_KEY_MASK;
    kCtrl->old_pushed.word = 0;
    kCtrl->last_pushed.word = 0;
}

__attribute__ ((optimize("O3"))) KEY_QUEUE_STATUS riscv_game_controller_key_push(T_KEY_QUEUE_CTRL_S *kCtrl, void *outgoing_data, uint32_t timestamp)
{
    T_OUTGOING_VALUES_S * outgoing = (T_OUTGOING_VALUES_S *)outgoing_data;
    GAME_CONTROLLEER_KEY_INFO_T combined_value;
    uint32_t status = STATUS_NOTHING_CHANGED;
    uint32_t hat_switch = 0;

    combined_value.word = 0;
    if (is_queue_full(kCtrl)) {
        // The queue is full, cannot insert new key info
        HID_DBG_LOG(rv_exp, "riscv_game_controller_key_push STATUS_QUEUE_FULL", 0);
        return STATUS_QUEUE_FULL;
    }

    if (kCtrl->last_pushed.word != outgoing->k.word)
    {
        kCtrl->old_pushed.word = kCtrl->last_pushed.word;
        kCtrl->last_pushed.word = outgoing->k.word;

        /* process hat switch */
        #if 0
        switch ((outgoing->k.word & 0xf))
        {
            /* UP */
            case 0x1:
                hat_switch = 0x1;
                break;

            /* UP + RIGHT */
            case 0x9:
                hat_switch = 0x2;
                break;

            /* RIGHT */
            case 0x8:
                hat_switch = 0x3;
                break;

            /* RIGHT + DOWN */
            case 0xA:
                hat_switch = 0x4;
                break;

            /* DOWN */
            case 0x2:
                hat_switch = 0x5;
                break;

            /* DOWN + LEFT */
            case 0x6:
                hat_switch = 0x6;
                break;

            /* LEFT */
            case 0x4:
                hat_switch = 0x7;
                break;

            /* LEFT + UP */
            case 0x5:
                hat_switch = 0x8;
                break;

            default:
                break;
        }
        #else
        hat_switch = hat_switch_table[(outgoing->k.word & 0xf)];
        #endif

        #if !defined (AIR_HID_DUMMY_REPORT_RATE)
        uint32_t flag = hid_express_get_hid_flag();
        extern uint8_t report_rate_pka;
        if ((GAMING_DATA_GO(flag) && report_rate_pka == HID_REPORT_RATE_8K_HZ))
        #endif /* not AIR_HID_DUMMY_REPORT_RATE */
        {
            /* Note: Each time, all keys must be detected, and it must be ensured that the detected keys are inserted into the queue in group order
            So do not use any 'else if' here */
            /* check key in group 0 is changed or hat switch is changed */
            if ((kCtrl->old_pushed.word & 0x0000ffff) != (outgoing->k.word & 0x0000ffff))
            {
                /* push group 0 key + lt/rt + hat switch value */
                combined_value.word = (outgoing->k.word & 0x0000fff0) | hat_switch;
                riscv_game_controller_key_push_key_info(kCtrl, GAME_CONTROLLER_KEY_GROUP_0, combined_value.word, 0, timestamp);
            }
            /* check key in group 1 is changed  */
            if ((kCtrl->old_pushed.word & 0x00ff0000) != (outgoing->k.word & 0x00ff0000))
            {
                /* push group 1 key + hat switch value */
                combined_value.word = (outgoing->k.word & 0x00ff0000) | hat_switch;
                riscv_game_controller_key_push_key_info(kCtrl, GAME_CONTROLLER_KEY_GROUP_1, combined_value.word, 0, timestamp);
            }
            /* check key in group 2 is changed  */
            if ((kCtrl->old_pushed.word & 0xff000000) != (outgoing->k.word & 0xff000000))
            {
                /* push group 2 key + hat switch value */
                combined_value.word = (outgoing->k.word & 0xff000000) | hat_switch;
                riscv_game_controller_key_push_key_info(kCtrl, GAME_CONTROLLER_KEY_GROUP_2, combined_value.word, 0, timestamp);
            }
        }
        #if !defined (AIR_HID_DUMMY_REPORT_RATE)
        else
        {
            if ((kCtrl->old_pushed.word & 0x00ffffff) != (outgoing->k.word & 0x00ffffff))
            {
                /* push group 0 + 1 key +  lt/rt + hat switch value */
                combined_value.word = (outgoing->k.word & 0x00fffff0) | hat_switch;
                if (GAMING_DATA_GO(flag)){
                    riscv_game_controller_key_push_key_info(kCtrl, REPORT_ID_GAME_CONTROLLER_ALL_IN_ONE, combined_value.word, 0, timestamp);
                } else if (USB_DATA_GO(flag) || BT_DATA_GO(flag)){
                    riscv_game_controller_key_push_key_info(kCtrl, REPORT_ID_GAME_CONTROLLER, combined_value.word, 0, timestamp);
                }
            }
        }
        #endif /* not AIR_HID_DUMMY_REPORT_RATE */

        status = STATUS_SUCCESS;
    }

    #if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    /* Check the MS key, and add them to the queue */
    if (kCtrl->last_pushed_ms != outgoing->ms_k)
    {
        kCtrl->last_pushed_ms = outgoing->ms_k;
        riscv_game_controller_key_push_key_info(kCtrl, MS_KEY_Z, outgoing->ms_k, 0, timestamp);
        status = STATUS_SUCCESS;
        // HID_DBG_LOG(rv_exp, "outgoing->ms_k = %x", 1, outgoing->ms_k);
    }

    /* Check kb std value */
    if((kCtrl->last_pushed_kb_std[0] != outgoing->kb_std[0])
        || (kCtrl->last_pushed_kb_std[1] != outgoing->kb_std[1]))
    {
        kCtrl->last_pushed_kb_std[0] = outgoing->kb_std[0];
        kCtrl->last_pushed_kb_std[1] = outgoing->kb_std[1];
        riscv_game_controller_key_push_key_info(kCtrl, KB_STD, outgoing->kb_std[0], outgoing->kb_std[1], timestamp);
        // HID_DBG_LOG(rv_exp, "push kb_std = %x %x", 2, outgoing->kb_std[0], outgoing->kb_std[1]);
        status = STATUS_SUCCESS;
    }

    /* Check kb consumer value */
    if(kCtrl->last_pushed_kb_consumer != outgoing->kb_consumer)
    {
        kCtrl->last_pushed_kb_consumer = outgoing->kb_consumer;
        riscv_game_controller_key_push_key_info(kCtrl, KB_CONSUMBER, outgoing->kb_consumer, 0, timestamp);
        status = STATUS_SUCCESS;
    }
    #endif

    return status;
}

KEY_QUEUE_STATUS riscv_game_controller_wakeup_key_push(T_KEY_QUEUE_CTRL_S *kCtrl, void *outgoing_data, uint32_t timestamp)
{
    T_OUTGOING_VALUES_S * outgoing = (T_OUTGOING_VALUES_S *)outgoing_data;
    GAME_CONTROLLEER_KEY_INFO_T combined_value;
    uint32_t status = STATUS_NOTHING_CHANGED;
    uint32_t hat_switch = 0;

    combined_value.word = 0;
    if (is_queue_full(kCtrl)) {
        // The queue is full, cannot insert new key info
        HID_DBG_LOG(rv_exp, "riscv_game_controller_wakeup_key_push STATUS_QUEUE_FULL", 0);
        return STATUS_QUEUE_FULL;
    }

    if (kCtrl->last_pushed.word != outgoing->k.word)
    {
        kCtrl->old_pushed.word = kCtrl->last_pushed.word;
        kCtrl->last_pushed.word = outgoing->k.word;

        /* process hat switch */
        #if 0
        switch ((outgoing->k.word & 0xf))
        {
            /* UP */
            case 0x1:
                hat_switch = 0x1;
                break;

            /* UP + RIGHT */
            case 0x9:
                hat_switch = 0x2;
                break;

            /* RIGHT */
            case 0x8:
                hat_switch = 0x3;
                break;

            /* RIGHT + DOWN */
            case 0xA:
                hat_switch = 0x4;
                break;

            /* DOWN */
            case 0x2:
                hat_switch = 0x5;
                break;

            /* DOWN + LEFT */
            case 0x6:
                hat_switch = 0x6;
                break;

            /* LEFT */
            case 0x4:
                hat_switch = 0x7;
                break;

            /* LEFT + UP */
            case 0x5:
                hat_switch = 0x8;
                break;

            default:
                break;
        }
        #else
        hat_switch = hat_switch_table[(outgoing->k.word & 0xf)];
        #endif

        #if !defined (AIR_HID_DUMMY_REPORT_RATE)
        uint8_t mode = hid_express_get_mode();
        extern uint8_t report_rate_pka;
        if ((mode == HID_SCENARIO_GAMING_MODE) && (report_rate_pka == HID_REPORT_RATE_8K_HZ))
        #endif /* not AIR_HID_DUMMY_REPORT_RATE */
        {
            /* Note: Each time, all keys must be detected, and it must be ensured that the detected keys are inserted into the queue in group order
            So do not use any 'else if' here */
            /* check key in group 0 is changed or hat switch is changed */
            if ((kCtrl->old_pushed.word & 0x0000ffff) != (outgoing->k.word & 0x0000ffff))
            {
                /* push group 0 key + lt/rt + hat switch value */
                combined_value.word = (outgoing->k.word & 0x0000fff0) | hat_switch;
                riscv_game_controller_key_push_key_info(kCtrl, GAME_CONTROLLER_KEY_GROUP_0, combined_value.word, 0, timestamp);
            }
            /* check key in group 1 is changed  */
            if ((kCtrl->old_pushed.word & 0x00ff0000) != (outgoing->k.word & 0x00ff0000))
            {
                /* push group 1 key + hat switch value */
                combined_value.word = (outgoing->k.word & 0x00ff0000) | hat_switch;
                riscv_game_controller_key_push_key_info(kCtrl, GAME_CONTROLLER_KEY_GROUP_1, combined_value.word, 0, timestamp);
            }
            /* check key in group 2 is changed  */
            if ((kCtrl->old_pushed.word & 0xff000000) != (outgoing->k.word & 0xff000000))
            {
                /* push group 2 key + hat switch value */
                combined_value.word = (outgoing->k.word & 0xff000000) | hat_switch;
                riscv_game_controller_key_push_key_info(kCtrl, GAME_CONTROLLER_KEY_GROUP_2, combined_value.word, 0, timestamp);
            }
        }
        #if !defined (AIR_HID_DUMMY_REPORT_RATE)
        else
        {
            if ((kCtrl->old_pushed.word & 0x00ffffff) != (outgoing->k.word & 0x00ffffff))
            {
                /* push group 0 + 1 key +  lt/rt + hat switch value */
                combined_value.word = (outgoing->k.word & 0x00fffff0) | hat_switch;
                if (mode == HID_SCENARIO_GAMING_MODE){
                    riscv_game_controller_key_push_key_info(kCtrl, REPORT_ID_GAME_CONTROLLER_ALL_IN_ONE, combined_value.word, 0, timestamp);
                } else {
                    riscv_game_controller_key_push_key_info(kCtrl, REPORT_ID_GAME_CONTROLLER, combined_value.word, 0, timestamp);
                }
            }
        }
        #endif /* not AIR_HID_DUMMY_REPORT_RATE */

        status = STATUS_SUCCESS;
    }

    return status;
}

__attribute__ ((optimize("O3"))) KEY_QUEUE_STATUS riscv_game_controller_key_pop_temperory(T_KEY_QUEUE_CTRL_S *kCtrl, void *outgoing_data, uint32_t timestamp)
{
    T_OUTGOING_VALUES_S * outgoing = (T_OUTGOING_VALUES_S *)outgoing_data;
    while (!is_queue_empty(kCtrl))
    {
        kCtrl->outgoing_item_idx = (kCtrl->buf_tail + 1) & KEY_BUFFER_SIZE_MASK;

        T_KEY_INFO_S *outgoing_key_info = &kCtrl->buffer[kCtrl->outgoing_item_idx];

        if (is_key_expired (outgoing_key_info->timestamp, timestamp))
        {
            // HID_DBG_LOG(rv_exp, "is_key_expired outgoing_key_info->timestamp = %d, timestamp = %d", 2, outgoing_key_info->timestamp, timestamp);
            outgoing_key_info->key_delivery_status = KEY_DELIVERY_STATE_ABANDONED;
            outgoing_key_info->nack_cnt = (outgoing_key_info->nack_cnt << 16) | outgoing_key_info->nack_cnt;
            outgoing_key_info->report_process_time = timestamp;
            //uint32_t current_timestamp = hal_eint_get_free_counter_value();
            // HID_DBG_LOG(rv_exp,"Key is expired when popped, new_keys(0x%x) is dropped, %d - %d = %d us  "
            // , 4
            // , outgoing_key_info->items[0] & 0xFF
            // , current_timestamp
            // , outgoing_key_info->timestamp
            // , current_timestamp - outgoing_key_info->timestamp
            // );
            // The key is expired, move the tail forward
            kCtrl->buf_tail = (kCtrl->buf_tail + 1) & KEY_BUFFER_SIZE_MASK;
        } else {
            if (outgoing_key_info->type == GAME_CONTROLLER_KEY_GROUP_0)
            {
                outgoing->type = REPORT_ID_GAME_CONTROLLER_GROUP0;
                outgoing->hat_switch_byte = outgoing_key_info->items[0] & 0x000000ff;
                outgoing->key_air_byte = (outgoing_key_info->items[0] & 0x0000ff00)>>8;
                outgoing->lt_rt_digital = (outgoing_key_info->items[0] & 0x000000f0)>>4;
                outgoing_key_info->key_delivery_status = KEY_DELIVERY_STATE_TRIGGERED_COMPLETED;
            }
            else if (outgoing_key_info->type == GAME_CONTROLLER_KEY_GROUP_1)
            {
                outgoing->type = REPORT_ID_GAME_CONTROLLER_GROUP1;
                outgoing->hat_switch_byte = outgoing_key_info->items[0] & 0x000000ff;
                outgoing->key_air_byte = (outgoing_key_info->items[0] & 0x00ff0000)>>16;
                outgoing_key_info->key_delivery_status = KEY_DELIVERY_STATE_TRIGGERED_COMPLETED;
            }
            else if (outgoing_key_info->type == GAME_CONTROLLER_KEY_GROUP_2)
            {
                outgoing->type = REPORT_ID_GAME_CONTROLLER_GROUP2;
                outgoing->hat_switch_byte = outgoing_key_info->items[0] & 0x000000ff;
                outgoing->key_air_byte = (outgoing_key_info->items[0] & 0xff000000)>>24;
                outgoing_key_info->key_delivery_status = KEY_DELIVERY_STATE_TRIGGERED_COMPLETED;
            }
            #if !defined (AIR_HID_DUMMY_REPORT_RATE)
            else if ((outgoing_key_info->type == REPORT_ID_GAME_CONTROLLER)
                    ||outgoing_key_info->type == REPORT_ID_GAME_CONTROLLER_ALL_IN_ONE)
            {
                outgoing->type = outgoing_key_info->type;
                outgoing->hat_switch_byte = outgoing_key_info->items[0] & 0x000000ff;
                outgoing->key_air_byte = (outgoing_key_info->items[0] & 0x00ffff00)>>8;
                outgoing->lt_rt_digital = (outgoing_key_info->items[0] & 0x000000f0)>>4;
                outgoing_key_info->key_delivery_status = KEY_DELIVERY_STATE_TRIGGERED_COMPLETED;
            }
            #endif
            #if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
            else if(outgoing_key_info->type == MS_KEY_Z)
            {
                outgoing->type = REPORT_ID_MOUSE;
                outgoing->ms_k = outgoing_key_info->items[0];
                outgoing_key_info->key_delivery_status = KEY_DELIVERY_STATE_TRIGGERED_COMPLETED;
                // HID_DBG_LOG(rv_exp, "outgoing->ms_k=  %x", 1, outgoing->ms_k);
            }
            else if(outgoing_key_info->type == KB_STD)
            {
                outgoing->type = REPORT_ID_KB_STD;
                outgoing->kb_std[0] = outgoing_key_info->items[0];
                outgoing->kb_std[1] = outgoing_key_info->items[1];
                outgoing_key_info->key_delivery_status = KEY_DELIVERY_STATE_TRIGGERED_COMPLETED;
                // HID_DBG_LOG(rv_exp, "pop kb_std= %x %x", 2, outgoing->kb_std[0], outgoing->kb_std[1]);
            }
            else if(outgoing_key_info->type == KB_CONSUMBER)
            {
                outgoing->type = REPORT_ID_KB_CONSUMER;
                outgoing->kb_consumer = outgoing_key_info->items[0];
                outgoing_key_info->key_delivery_status = KEY_DELIVERY_STATE_TRIGGERED_COMPLETED;
                // HID_DBG_LOG(rv_exp, "pop kb_consumer = %x %x", 2, outgoing_key_info->items[0], outgoing->kb_consumer);
            }
            #endif
            return STATUS_SUCCESS;
        }
    }

    outgoing->type = REPORT_ID_GAME_CONTROLLER;
    return STATUS_QUEUE_EMPTY;
}

KEY_QUEUE_STATUS riscv_game_controller_key_pop_confirm(T_KEY_QUEUE_CTRL_S *kCtrl)
{
    if (!is_queue_empty(kCtrl)) {
        if (kCtrl->buffer[kCtrl->outgoing_item_idx].key_delivery_status == KEY_DELIVERY_STATE_ACKED) {
            DBG_PING_H(DBG_SIGNAL_LATCH_REPORT);
            kCtrl->buf_tail = (kCtrl->buf_tail + 1) & KEY_BUFFER_SIZE_MASK;
            DBG_PING_L(DBG_SIGNAL_LATCH_REPORT);
        }
    }
    return STATUS_SUCCESS;
}

void riscv_hid_express_key_queue_debug_print(T_KEY_QUEUE_CTRL_S *kCtrl, uint32_t riscv_trigger_time)
{
    // DBG_PING_H(DBG_SIGNAL_MAIN_LOOP);

    if ((kCtrl->buf_tail_printed != kCtrl->buf_tail) && (kCtrl->buffer[kCtrl->buf_tail_printed].key_delivery_status == KEY_DELIVERY_STATE_IDLE || kCtrl->buffer[kCtrl->buf_tail_printed].key_delivery_status == KEY_DELIVERY_STATE_ABANDONED))
    {
        #define SPI_TRIGGER_TO_SPI_CALLBACK_TIME  30
        T_KEY_INFO_S *outgoing_key_info = &kCtrl->buffer[(kCtrl->buf_tail_printed + 1) & KEY_BUFFER_SIZE_MASK];

        HID_DBG_LOG(rv_exp,"Index[%d], type = %d, key = (%08X-%08X <--), retry cnt = %08X, report_process_time = %d, timestamp = %d, trigger time = %d, Tx Residual Time = %d"
            , 9
            , kCtrl->buf_tail_printed
            , outgoing_key_info->type
            , outgoing_key_info->items[1]
            , outgoing_key_info->items[0]
            , outgoing_key_info->nack_cnt
            , outgoing_key_info->report_process_time
            , outgoing_key_info->timestamp
            , riscv_trigger_time
            , riscv_trigger_time - outgoing_key_info->report_process_time - SPI_TRIGGER_TO_SPI_CALLBACK_TIME
            );

        kCtrl->buf_tail_printed = (kCtrl->buf_tail_printed + 1) & KEY_BUFFER_SIZE_MASK;
    }

    // DBG_PING_L(DBG_SIGNAL_MAIN_LOOP);
}

void rv_hid_exp_key_queue_post_process(T_KEY_QUEUE_CTRL_S *kCtrl, uint32_t report_process_time)
{
    T_KEY_INFO_S *outgoing_key_info = &kCtrl->buffer[kCtrl->outgoing_item_idx];
    // The post process is designed for the key just pushed into the queue
    // So, we access the data in the buf_head position only

    switch(outgoing_key_info->key_delivery_status)
    {
        case KEY_DELIVERY_STATE_TRIGGERED:
        case KEY_DELIVERY_STATE_SKIP_FIRST_RESULT:
        case KEY_DELIVERY_STATE_ABANDONED:
        break;

        case KEY_DELIVERY_STATE_TRIGGERED_COMPLETED:
        {
            outgoing_key_info->report_process_time = report_process_time;
        }
        break;

        case KEY_DELIVERY_STATE_ACKED:
        {
            outgoing_key_info->key_delivery_status = KEY_DELIVERY_STATE_IDLE;
        }
        break;
    }
}

void rv_hid_exp_key_queue_tx_result_handle(T_KEY_QUEUE_CTRL_S *kCtrl, uint32_t tx_result)
{
    // DBG_PING_L(DBG_SIGNAL_DEBUG_1);

    if (tx_result == 0){
        kCtrl->buffer[kCtrl->outgoing_item_idx].key_delivery_status = KEY_DELIVERY_STATE_ACKED;
        riscv_game_controller_key_pop_confirm(kCtrl);
    }
    else {
        // DBG_PING_H(DBG_SIGNAL_DEBUG_1);
        kCtrl->buffer[kCtrl->outgoing_item_idx].nack_cnt++;
        // DBG_PING_L(DBG_SIGNAL_DEBUG_1);
    }

    // DBG_PING_H(DBG_SIGNAL_DEBUG_1);
}

void rv_hid_exp_key_queue_pre_process(T_KEY_QUEUE_CTRL_S *kCtrl, uint32_t tx_result, uint32_t mode)
{
    if (kCtrl->buffer[kCtrl->outgoing_item_idx].key_delivery_status == KEY_DELIVERY_STATE_TRIGGERED_COMPLETED) {
        DBG_PING_H(DBG_SIGNAL_DEBUG_2);
        rv_hid_exp_key_queue_tx_result_handle(kCtrl, tx_result);
        DBG_PING_L(DBG_SIGNAL_DEBUG_2);
    }
}

#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */
