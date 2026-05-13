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
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
#ifndef _RISCV_HID_EXPRESS_KEY_QUEUE_H_
#define _RISCV_HID_EXPRESS_KEY_QUEUE_H_

/* General return values */
typedef enum {
    STATUS_SUCCESS = 0,
    STATUS_INVALID_PARAMETER,
    STATUS_BUSY,
    STATUS_INSUFFICIENT_MEMORY,
    STATUS_QUEUE_EMPTY,
    STATUS_QUEUE_FULL,
    STATUS_TIMEOUT,
    STATUS_NOTHING_CHANGED,
    STATUS_UNKNOWN,
    // Additional error codes can be added here
} KEY_QUEUE_STATUS;

typedef enum {
    MS_KEY_Z,
    KB_STD,
    KB_CONSUMBER,
    GAME_CONTROLLER_KEY_GROUP_0, /* Hat switch + A/B/X/Y + Joystick buttons * 2 + LB + RB */
    GAME_CONTROLLER_KEY_GROUP_1, /* Hat switch + Home + Menu(Start) + View(Back) + external buttons * 5 */
    GAME_CONTROLLER_KEY_GROUP_2, /* Hat switch + external buttons * 8 */
}T_ITEM_TYPE_E;

typedef enum {
    K_TYPE_K,   // game_controller key
    K_TYPE_Z1,  // wheel
    K_TYPE_Z2,  // ac pan
}T_KEY_QUEUE_VALUE_TYPE_E;

typedef union {
    struct {
        uint32_t hat_switch_byte            :8;    /* bits:0-7, hat_switch */
        uint32_t key_group0_byte            :8;    /* bits:8-15, A/B/X/Y + Joystick buttons * 2 + LB + RB */
        uint32_t key_group1_byte            :8;    /* bits:16-23, Home + Menu(Start) + View(Back) + external buttons * 5 */
        uint32_t key_group2_byte            :8;    /* bits:24-31, external buttons * 8 */
    } field;
    uint32_t word;
} GAME_CONTROLLEER_KEY_INFO_T;

#define KEY_BUFFER_SIZE                              (1<<3)                 /** The size of the buffer used to store the game_controller key info, it should be a power of 2 */
#define KEY_BUFFER_SIZE_MASK                         (KEY_BUFFER_SIZE - 1)  /** The mask of the buffer size  */
#define KEY_EXPIRED_TIME_MS                          (30000)                 /** The key should be expired after this time ms */
#define DEFAULT_VALID_GAME_CONTROLLER_KEY_MASK                 0xFFFFFFFF                   /** The default valid game_controller key mask, 5 bits stand for left, right, middle, page next, and page previous keys  5 bits stand for left, right, middle, page next, and page previous keys*/
#define PUSH_KEY 0
#define PUSH_Z 1

typedef struct {
    uint32_t type;
    uint32_t items[2];                      /** The key value  */
    uint32_t timestamp;                     /** The timestamp when the key was pressed. It is uesed to determine whether the key is expired or not */
    uint32_t latency_key_latch;             /** The latency between key pressed/released and key latch */
    uint32_t report_process_time;                 /** The latency between key pressed/released and key acked by remote device */
    uint32_t nack_cnt;                      /** The number of nack received after the key was send */
    uint32_t key_delivery_status;           /** The delivery status of the key in this item*/
}T_KEY_INFO_S;

typedef struct {
    T_KEY_INFO_S    buffer[KEY_BUFFER_SIZE];        /** The queue buffer of game_controller keys */
    uint32_t        valid_key_mask;                 /** The mask of valid keys */
    GAME_CONTROLLEER_KEY_INFO_T        last_pushed;                 /** The delivered key and z value are used to determine whether the outgoing key has changed and whether a z value is present*/
    GAME_CONTROLLEER_KEY_INFO_T        old_pushed;                  /** game_controller key status is changed, This flag is used to get key latency info after HID report is sent to avoid any delay */
    uint32_t        outgoing_item_idx;

    uint32_t        last_pushed_kb_std[2];
    uint32_t        last_pushed_kb_consumer;
    uint32_t        last_pushed_ms;
    uint32_t        buf_head;                       /** The head index of the queue buffer. It stand for the next position to be pushed into the queue  */
    uint32_t        buf_tail;                       /** The tail index of the queue buffer. It stand for the next position to be popped from the queue  */
    uint32_t        buf_tail_printed;               /** The last tail index of the queue buffer. It is used to determine whether the status is changed or not  */
}T_KEY_QUEUE_CTRL_S;







void init_key_ctrl(T_KEY_QUEUE_CTRL_S *kCtrl, uint32_t default_key_status);
void riscv_game_controller_key_clear_key_pushed(T_KEY_QUEUE_CTRL_S *kCtrl);
KEY_QUEUE_STATUS riscv_game_controller_key_pop_temperory(T_KEY_QUEUE_CTRL_S *kCtrl, void *outgoing_data, uint32_t timestamp);
KEY_QUEUE_STATUS riscv_game_controller_key_push(T_KEY_QUEUE_CTRL_S *kCtrl, void * outgoing_data , uint32_t timestamp);
KEY_QUEUE_STATUS riscv_game_controller_wakeup_key_push(T_KEY_QUEUE_CTRL_S *kCtrl, void * outgoing_data , uint32_t timestamp);
KEY_QUEUE_STATUS riscv_game_controller_key_pop_confirm(T_KEY_QUEUE_CTRL_S *kCtrl);
void riscv_hid_express_key_queue_debug_print(T_KEY_QUEUE_CTRL_S *kCtrl, uint32_t riscv_trigger_time);
void rv_hid_exp_key_queue_post_process(T_KEY_QUEUE_CTRL_S *kCtrl, uint32_t report_process_time);
void rv_hid_exp_key_queue_pre_process(T_KEY_QUEUE_CTRL_S *kCtrl, uint32_t tx_result, uint32_t mode);
bool is_queue_num_2(T_KEY_QUEUE_CTRL_S *kCtrl);
#endif /* _RISCV_HID_EXPRESS_REASSEMBLE_H_ */
#endif
