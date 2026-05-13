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
#include "rv_application.h"
#include "riscv_wheel_queue.h"

#define WHEEL_BUFFER_SIZE                                               (1<<3)  /** The size of the buffer used to store the mouse z1 info, it should be a power of 2 */
#define WHEEL_BUFFER_SIZE_MASK                         (WHEEL_BUFFER_SIZE - 1)  /** The mask of the buffer size  */

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef struct {
    int16_t    buffer[WHEEL_BUFFER_SIZE];        /** The queue buffer of wheel values */
    uint32_t   buf_head;                       /** The head index of the queue buffer. It stand for the next position to be pushed into the queue  */
    uint32_t   buf_tail;                       /** The tail index of the queue buffer. It stand for the next position to be popped from the queue  */
}T_WHEEL_QUEUE_CTRL_S;

/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
T_WHEEL_QUEUE_CTRL_S wheel_q_Ctrl;

/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void riscv_wheel_queue_init_q_ctrl(void) 
{
    wheel_q_Ctrl.buf_head = 0;
    wheel_q_Ctrl.buf_tail = 0;
}

bool riscv_wheel_queue_is_full() 
{
    return ((wheel_q_Ctrl.buf_head + 1) & WHEEL_BUFFER_SIZE_MASK) == wheel_q_Ctrl.buf_tail;
}

bool riscv_wheel_queue_is_empty() 
{
    return wheel_q_Ctrl.buf_head == wheel_q_Ctrl.buf_tail;
}

void riscv_wheel_queue_push(int16_t wheel_data)
{
    if (riscv_wheel_queue_is_full()) {
        HID_DBG_LOG(riscv_ps, "riscv_wheel_queue_push - Queue is full", 0);
        return;
    }
    
    if(wheel_data != 0)
    {
        wheel_q_Ctrl.buffer[wheel_q_Ctrl.buf_head] = wheel_data;
        wheel_q_Ctrl.buf_head = (wheel_q_Ctrl.buf_head + 1) & WHEEL_BUFFER_SIZE_MASK;
    }
}

void riscv_wheel_queue_pop(int16_t* num)
{
    if(!riscv_wheel_queue_is_empty()) 
    {
        *num = wheel_q_Ctrl.buffer[wheel_q_Ctrl.buf_tail];
        wheel_q_Ctrl.buf_tail = (wheel_q_Ctrl.buf_tail + 1) & WHEEL_BUFFER_SIZE_MASK;
    }
    else {
        *num = 0;
    }
}

void riscv_wheel_queue_pop_temp(int16_t* num)
{
    if(!riscv_wheel_queue_is_empty()) 
    {
        *num = wheel_q_Ctrl.buffer[wheel_q_Ctrl.buf_tail];
    }
    else {
        *num = 0;
    }
}

void riscv_wheel_queue_pop_confirm()
{
    wheel_q_Ctrl.buf_tail = (wheel_q_Ctrl.buf_tail + 1) & WHEEL_BUFFER_SIZE_MASK;
}

void riscv_wheel_queue_update(int16_t num)
{
    wheel_q_Ctrl.buffer[wheel_q_Ctrl.buf_tail] += num;
}