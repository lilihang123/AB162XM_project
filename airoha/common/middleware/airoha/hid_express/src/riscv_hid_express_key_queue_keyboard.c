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


#if defined(AIR_PRODUCT_TYPE_KEYBOARD)
/* Includes ------------------------------------------------------------------*/
#include "riscv_hid_express.h"
#include "riscv_hid_express_key_queue_keyboard.h"
#include "hal_eint_internal.h"
#include "riscv_hid_express_2_4G_mode.h"
#include "hal_gpt.h"
#include <stdint.h>


/* Private define ------------------------------------------------------------*/
#define KEY_EXPIRE_TIME 1000000 //ms


/* Private typedef -----------------------------------------------------------*/

typedef enum {
    KEY_DELIVERY_STATE_IDLE,
    KEY_DELIVERY_STATE_TRIGGERED,
    KEY_DELIVERY_STATE_TRIGGERED_COMPLETED,
    KEY_DELIVERY_STATE_SKIP_FIRST_RESULT,
    KEY_DELIVERY_STATE_ACKED,
    KEY_DELIVERY_STATE_ABANDONED,
}T_KEY_DELIVERY_STATUS_E;

#define SKIP_FIRST_RESULT_AT_8K                     0xFF    // 1st tx result of 8K is the result of previous report. Not current report.

/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/



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

void riscv_keyboard_key_push_key_info(T_KEY_QUEUE_CTRL_S *kCtrl, uint32_t type, uint32_t item1, uint32_t item2, uint32_t item3, uint32_t item4, uint32_t timestamp) {
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
    key_info_write->items[2] = item3;
    key_info_write->items[3] = item4;
    key_info_write->type = type;
    key_info_write->timestamp = timestamp;
    // HID_DBG_LOG(rv_exp, "push = %x head = %d tail = %d", 3, key_info_write->items[0], kCtrl->buf_head, kCtrl->buf_tail);
}
/* Public functions ---------------------------------------------------------*/

/** Initialize the key control structure */
void init_key_ctrl(T_KEY_QUEUE_CTRL_S *kCtrl, uint32_t default_key_status)
{
    kCtrl->valid_key_mask = DEFAULT_VALID_KEYBOARD_KEY_MASK;
    kCtrl->buf_head = 0;
    kCtrl->buf_tail = 0;
    kCtrl->last_pushed_nkey[0] = default_key_status;
    kCtrl->last_pushed_nkey[1] = default_key_status;
    kCtrl->last_pushed_nkey[2] = default_key_status;
    kCtrl->last_pushed_nkey[3] = default_key_status;
    kCtrl->last_pushed_ms = default_key_status;
    kCtrl->last_pushed_kb_consumer = default_key_status;

}

void riscv_key_clear_key_pushed(T_KEY_QUEUE_CTRL_S *kCtrl)
{
    //HID_DBG_LOG(rv_exp, "[Report log]riscv_key_clear_key_pushed, key_delivery_status = %d", 1, kCtrl->buffer[kCtrl->buf_head].key_delivery_status);
    kCtrl->valid_key_mask = DEFAULT_VALID_KEYBOARD_KEY_MASK;
    kCtrl->last_pushed_nkey[0] = 0;
    kCtrl->last_pushed_nkey[1] = 0;
    kCtrl->last_pushed_nkey[2] = 0;
    kCtrl->last_pushed_nkey[3] = 0;
    kCtrl->last_pushed_ms = 0;
    kCtrl->last_pushed_kb_consumer = 0;

    kCtrl->old_pushed_nkey[0] = 0;
    kCtrl->old_pushed_nkey[1] = 0;
    kCtrl->old_pushed_nkey[2] = 0;
    kCtrl->old_pushed_nkey[3] = 0;
    kCtrl->old_pushed_ms = 0;
    kCtrl->old_pushed_kb_consumer = 0;
}

/** Push a new key info into the queue */
KEY_QUEUE_STATUS riscv_key_push(T_KEY_QUEUE_CTRL_S *kCtrl, void * outgoing_data , uint32_t timestamp) // uint32_t k, int32_t z1, int32_t z2, uint32_t *kb_std, uint32_t kb_consumer)
{
    T_OUTGOING_VALUES_S * outgoing = (T_OUTGOING_VALUES_S *)outgoing_data;
    uint32_t status = STATUS_NOTHING_CHANGED;

    if (is_queue_full(kCtrl)) {
        // The queue is full, cannot insert new key info
        // HID_DBG_LOG(rv_exp, "riscv_key_push - Queue is full", 0);
        return STATUS_QUEUE_FULL;
    }
    T_KEY_INFO_S *outgoing_key_info = &kCtrl->buffer[kCtrl->outgoing_item_idx];
    /* Note: Each time, all keys must be detected, and it must be ensured that the detected keys are inserted into the queue in group order
       So do not use any 'else if' here */
    uint8_t *cmd_id = (uint8_t *)(outgoing->kb_nkey_map_addr);
    switch (((*cmd_id) & 0xf)){
            /* FN KEY */
            case 0x1:
                *((uint32_t *)&outgoing->kb_nkey_map[0]) = *((uint32_t *)(&cmd_id[1]));
                *((uint32_t *)&outgoing->kb_nkey_map[1]) = *((uint32_t *)(&cmd_id[5]));
                *((uint32_t *)&outgoing->kb_nkey_map[2]) = *((uint32_t *)(&cmd_id[9]));
                *((uint32_t *)&outgoing->kb_nkey_map[3]) = (*((uint32_t *)(&cmd_id[13])) & 0xFFFF);
                break;

            /* MOUSE KEY */
            case 0x2:
            *((uint32_t *)&outgoing->kb_ms) = *((uint32_t *)(&cmd_id[1]));
            break;

            /* CONSUMER KEY */
            case 0x3:
            *((uint32_t *)&outgoing->kb_consumer) = *((uint32_t *)(&cmd_id[1]));
                break;

            default:
                break;
    }

#if 0
    static uint32_t key_cnt = 0;
    key_cnt++;
    if((key_cnt % 500) == 0){
        LOG_MSGID_I(riscv_key, "riscv_key_push kb_nkey = %08X-%08X-%08X-%08x, addr = 0x%08X",
            5,
            *((uint32_t *)(outgoing->kb_nkey_map_addr) + 0),
            *((uint32_t *)(outgoing->kb_nkey_map_addr) + 1),
            *((uint32_t *)(outgoing->kb_nkey_map_addr) + 2),
            *((uint32_t *)(outgoing->kb_nkey_map_addr) + 3),
            outgoing->kb_nkey_map_addr
        );
        LOG_MSGID_I(riscv_key, "riscv_key_push outgoing kb_nkey = %08X-%08X-%08X-%08X, kb_consumer = %08X, kb_ms = %08X",
            6,
            outgoing->kb_nkey_map[0],
            outgoing->kb_nkey_map[1],
            outgoing->kb_nkey_map[2],
            outgoing->kb_nkey_map[3],
            outgoing->kb_consumer,
            outgoing->kb_ms
        );
        LOG_MSGID_I(riscv_key, "riscv_key_push outgoing palyload: group_0 = %x, group_1 = %x, kb_consumer = %x, kb_ms = %x",
            4,
            (kCtrl->last_pushed_nkey[0] != outgoing->kb_nkey_map[0]) || (kCtrl->last_pushed_nkey[1] != outgoing->kb_nkey_map[1]),
            (kCtrl->last_pushed_nkey[2] != outgoing->kb_nkey_map[2]) || (kCtrl->last_pushed_nkey[3] != outgoing->kb_nkey_map[3]),
            (kCtrl->last_pushed_kb_consumer != outgoing->kb_consumer),
            (kCtrl->last_pushed_ms != outgoing->kb_ms)
        );
    }
#endif
    extern uint32_t rr_idx_2_4g;
    uint32_t flag = hid_express_get_hid_flag();
    if((GAMING_DATA_GO(flag) && rr_idx_2_4g == HID_REPORT_RATE_8K_HZ))
    {
        /* check key in group 0 is changed or hat switch is changed */
        if ((kCtrl->last_pushed_nkey[0] != outgoing->kb_nkey_map[0]) || (kCtrl->last_pushed_nkey[1] != outgoing->kb_nkey_map[1]))
        {
            kCtrl->old_pushed_nkey[0]  = kCtrl->last_pushed_nkey[0];
            kCtrl->old_pushed_nkey[1]  = kCtrl->last_pushed_nkey[1];
            kCtrl->last_pushed_nkey[0] = outgoing->kb_nkey_map[0];
            kCtrl->last_pushed_nkey[1] = outgoing->kb_nkey_map[1];
            outgoing_key_info->send_group |= KB_NKEY_SEND_GROUP_0;
            /* push group 0 nkey + combo value */
            riscv_keyboard_key_push_key_info(kCtrl, REPORT_ID_KEYBOARD_GROUP0, outgoing->kb_nkey_map[0], outgoing->kb_nkey_map[1], 0, 0, timestamp);
            status = STATUS_SUCCESS;
        }
        /* check key in group 1 is changed  */
        if ((kCtrl->last_pushed_nkey[2] != outgoing->kb_nkey_map[2]) || (kCtrl->last_pushed_nkey[3] != outgoing->kb_nkey_map[3]))
        {
            /* push group 1 nkey */
            kCtrl->old_pushed_nkey[2]  = kCtrl->last_pushed_nkey[2];
            kCtrl->old_pushed_nkey[3]  = kCtrl->last_pushed_nkey[3];
            kCtrl->last_pushed_nkey[2] = outgoing->kb_nkey_map[2];
            kCtrl->last_pushed_nkey[3] = outgoing->kb_nkey_map[3];
            outgoing_key_info->send_group |= KB_NKEY_SEND_GROUP_1;
            riscv_keyboard_key_push_key_info(kCtrl, REPORT_ID_KEYBOARD_GROUP1, 0, 0, outgoing->kb_nkey_map[2],  outgoing->kb_nkey_map[3], timestamp);
            status = STATUS_SUCCESS;
        }
    }
    else
    {
        /* check key in group 0 & 1 is changed  */
        if ((kCtrl->last_pushed_nkey[0] != outgoing->kb_nkey_map[0]) || (kCtrl->last_pushed_nkey[1] != outgoing->kb_nkey_map[1]) || (kCtrl->last_pushed_nkey[2] != outgoing->kb_nkey_map[2]) || (kCtrl->last_pushed_nkey[3] != outgoing->kb_nkey_map[3]))
        {
            /* push group 0 nkey + combo value */
            kCtrl->old_pushed_nkey[0]  = kCtrl->last_pushed_nkey[0];
            kCtrl->old_pushed_nkey[1]  = kCtrl->last_pushed_nkey[1];
            kCtrl->last_pushed_nkey[0] = outgoing->kb_nkey_map[0];
            kCtrl->last_pushed_nkey[1] = outgoing->kb_nkey_map[1];
            /* push group 1 nkey */
            kCtrl->old_pushed_nkey[2]  = kCtrl->last_pushed_nkey[2];
            kCtrl->old_pushed_nkey[3]  = kCtrl->last_pushed_nkey[3];
            kCtrl->last_pushed_nkey[2] = outgoing->kb_nkey_map[2];
            kCtrl->last_pushed_nkey[3] = outgoing->kb_nkey_map[3];
            outgoing_key_info->send_group = 0;
            riscv_keyboard_key_push_key_info(kCtrl, REPORT_ID_KEYBOARD, outgoing->kb_nkey_map[0], outgoing->kb_nkey_map[1], outgoing->kb_nkey_map[2],  outgoing->kb_nkey_map[3], timestamp);
            status = STATUS_SUCCESS;
        }
    }
    
    /* check key in consumer group is changed  */
    if ((kCtrl->last_pushed_kb_consumer != outgoing->kb_consumer))
    {
        /* push group 2 consumer key */
        kCtrl->old_pushed_kb_consumer  = kCtrl->last_pushed_kb_consumer;
        kCtrl->last_pushed_kb_consumer = outgoing->kb_consumer;
        riscv_keyboard_key_push_key_info(kCtrl, REPORT_ID_KB_CONSUMER, outgoing->kb_consumer, 0, 0, 0, timestamp);
        status = STATUS_SUCCESS;
    }

#if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP) || defined(AIR_KEYBOARD_M607)
    /* Check the MS key and Z value, and add them to the queue */
    if (((kCtrl->last_pushed_ms) != outgoing->kb_ms))
    {
        kCtrl->old_pushed_ms = kCtrl->last_pushed_ms;
        kCtrl->last_pushed_ms =  outgoing->kb_ms;
        riscv_keyboard_key_push_key_info(kCtrl, REPORT_ID_MOUSE, outgoing->kb_ms, 0, 0, 0, timestamp);
        status = STATUS_SUCCESS;
    }
#endif
    return status;
}

/** Pop a key info from the queue */
KEY_QUEUE_STATUS riscv_key_pop_temperory(T_KEY_QUEUE_CTRL_S *kCtrl, void *outgoing_data, uint32_t timestamp)
{
    T_OUTGOING_VALUES_S * outgoing = (T_OUTGOING_VALUES_S *)outgoing_data;
    while (!is_queue_empty(kCtrl))
    {
        kCtrl->outgoing_item_idx = (kCtrl->buf_tail + 1) & KEY_BUFFER_SIZE_MASK;

        T_KEY_INFO_S *outgoing_key_info = &kCtrl->buffer[kCtrl->outgoing_item_idx];
        // T_KEY_INFO_S *old_key_info = &kCtrl->buffer[kCtrl->buf_tail];

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
            if(outgoing_key_info->type == REPORT_ID_KEYBOARD_GROUP0)
            {
                outgoing->type = REPORT_ID_KEYBOARD_GROUP0;
                for (int i = 0; i < 2; ++i) {
                    outgoing->kb_nkey_map[i] = outgoing_key_info->items[i];
                }
                outgoing_key_info->key_delivery_status = KEY_DELIVERY_STATE_TRIGGERED_COMPLETED;
                //HID_DBG_LOG(rv_exp, "pop kb_std= %x %x", 2, outgoing->kb_std[0], outgoing->kb_std[1]);
            }
            else if(outgoing_key_info->type == REPORT_ID_KEYBOARD_GROUP1)
            {
                outgoing->type = REPORT_ID_KEYBOARD_GROUP1;
                for (int i = 2; i < 4; ++i) {
                    outgoing->kb_nkey_map[i] = outgoing_key_info->items[i];
                }
                outgoing_key_info->key_delivery_status = KEY_DELIVERY_STATE_TRIGGERED_COMPLETED;
            }
            else if(outgoing_key_info->type == REPORT_ID_KB_CONSUMER)
            {
                outgoing->type = REPORT_ID_KB_CONSUMER;
                outgoing->kb_consumer = outgoing_key_info->items[0] & HALF;
                outgoing_key_info->key_delivery_status = KEY_DELIVERY_STATE_TRIGGERED_COMPLETED;
            }
            else if(outgoing_key_info->type == REPORT_ID_KEYBOARD)
            {
                outgoing->type = REPORT_ID_KEYBOARD;
                for (int i = 0; i < 4; ++i) {
                    outgoing->kb_nkey_map[i] = outgoing_key_info->items[i];
                }
                outgoing_key_info->key_delivery_status = KEY_DELIVERY_STATE_TRIGGERED_COMPLETED;
            }
#if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
            else if(outgoing_key_info->type == REPORT_ID_MOUSE)
            {
                outgoing->type = REPORT_ID_MOUSE;
                outgoing->kb_ms = outgoing_key_info->items[0] & HALF;
                outgoing_key_info->key_delivery_status = KEY_DELIVERY_STATE_TRIGGERED_COMPLETED;
            }
#endif
            return STATUS_SUCCESS;
        }
    }

    outgoing->type = REPORT_ID_KEYBOARD;
    return STATUS_QUEUE_EMPTY; // All keys were expired
}


KEY_QUEUE_STATUS riscv_key_pop_confirm(T_KEY_QUEUE_CTRL_S *kCtrl )
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

        // HID_DBG_LOG(rv_exp,"Index[%d], type = %d, key = (%08X-%08X <--), retry cnt = %08X, report_process_time = %d, timestamp = %d, trigger time = %d, Tx Residual Time = %d"
        //     , 9
        //     , kCtrl->buf_tail_printed
        //     , outgoing_key_info->type
        //     , outgoing_key_info->items[1]
        //     , outgoing_key_info->items[0]
        //     , outgoing_key_info->nack_cnt
        //     , outgoing_key_info->report_process_time
        //     , outgoing_key_info->timestamp
        //     , riscv_trigger_time
        //     , riscv_trigger_time - outgoing_key_info->report_process_time - SPI_TRIGGER_TO_SPI_CALLBACK_TIME
        //     );
        HID_DBG_LOG(rv_exp,"Index[%d], type = %d, key = (--> %08X-%08X-%08X-%08X <--), retry cnt = %08X, timestamp = %d "
            , 8
            , kCtrl->buf_tail_printed
            , outgoing_key_info->type
            , outgoing_key_info->items[3]
            , outgoing_key_info->items[2]
            , outgoing_key_info->items[1]
            , outgoing_key_info->items[0]
            , outgoing_key_info->nack_cnt
            , outgoing_key_info->timestamp
            );
        kCtrl->buf_tail_printed = (kCtrl->buf_tail_printed + 1) & KEY_BUFFER_SIZE_MASK;
    }

    // DBG_PING_L(DBG_SIGNAL_MAIN_LOOP);
}

// This function is called after new mouse key is pressed and report has been sent to controller
// Post process of hid_express service
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

void rv_hid_exp_key_queue_tx_result_handle(T_KEY_QUEUE_CTRL_S *kCtrl, uint32_t tx_result, uint32_t mode)
{
    // DBG_PING_L(DBG_SIGNAL_DEBUG_1);

    if (tx_result == 0){
        if(mode == MODE_2_4G){
            T_KEY_INFO_S *outgoing_key_info = &kCtrl->buffer[kCtrl->outgoing_item_idx];
            if(outgoing_key_info->send_group == KB_NKEY_SEND_GROUP || outgoing_key_info->type == REPORT_ID_KB_CONSUMER || outgoing_key_info->type == REPORT_ID_MOUSE){
                kCtrl->buffer[kCtrl->outgoing_item_idx].key_delivery_status = KEY_DELIVERY_STATE_ACKED;
                riscv_key_pop_confirm(kCtrl);
            } else if (outgoing_key_info->send_group & KB_NKEY_SEND_GROUP_0)
            {
                outgoing_key_info->send_group &= ~KB_NKEY_SEND_GROUP_0;
            } else if (outgoing_key_info->send_group & KB_NKEY_SEND_GROUP_1)
            {
                outgoing_key_info->send_group &= ~KB_NKEY_SEND_GROUP_1;
            }
        } else {
            kCtrl->buffer[kCtrl->outgoing_item_idx].key_delivery_status = KEY_DELIVERY_STATE_ACKED;
            riscv_key_pop_confirm(kCtrl);
        }
    }
    else {
        DBG_PING_H(DBG_SIGNAL_DEBUG_1);
        kCtrl->buffer[kCtrl->outgoing_item_idx].nack_cnt++;
        DBG_PING_L(DBG_SIGNAL_DEBUG_1);
    }

    // DBG_PING_H(DBG_SIGNAL_DEBUG_1);
}

// This function is called after an acknowledgment is received from the controller
// Pre process of hid_express service
void rv_hid_exp_key_queue_pre_process(T_KEY_QUEUE_CTRL_S *kCtrl, uint32_t tx_result, uint32_t mode)
{
    if (kCtrl->buffer[kCtrl->outgoing_item_idx].key_delivery_status == KEY_DELIVERY_STATE_TRIGGERED_COMPLETED) {
        DBG_PING_H(DBG_SIGNAL_DEBUG_2);
        rv_hid_exp_key_queue_tx_result_handle(kCtrl, tx_result, mode);
        DBG_PING_L(DBG_SIGNAL_DEBUG_2);
    }
}


#endif /*  */
