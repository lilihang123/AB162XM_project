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
#include "hal.h"
#include "hal_platform.h"
#include "hal_sw_irq.h"
#include "hal_queue.h"
#include <string.h>
#include <stdio.h>

#define MAX_SW_IRQ_USER    16

static hal_queue_t g_sw_irq_queue;
static hal_sw_irq_user_info_t g_sw_irq_user_buff[MAX_SW_IRQ_USER] = {0};
static uint8_t g_sw_irq_index = 0;

static void  hal_sw_irq_handle(hal_nvic_irq_t irq_number)
{
    int free_idx = 0;
    int res = 0;

    while (1) {
        /* Pop index from Q */
        res = hal_queue_pop(&g_sw_irq_queue, &free_idx);
        if (res < 0) {
            return;
        }
        /* Call user callback and free buffer item*/
        g_sw_irq_user_buff[free_idx].call_back(g_sw_irq_user_buff[free_idx].user_data);
        g_sw_irq_user_buff[free_idx].used_flag = 0;
    }
}

hal_sw_irq_status_t hal_sw_irq_trigger(hal_sw_irq_t sw_irq_id, hal_sw_irq_callback_t user_callback, void *user_data)
{
    static bool initialized = false;
    uint32_t mask = 0, free_idx = 0;
    int res = 0;
    hal_sw_irq_status_t status = HAL_SW_IRQ_STATUS_OK;

    if (user_callback == NULL || sw_irq_id >= HAL_SW_IRQ_MAX) {
        return HAL_SW_IRQ_STATUS_INVALID_PARAMETER;
    }
    do {
        hal_nvic_save_and_set_interrupt_mask(&mask);
        if (initialized == false) {
            memset(g_sw_irq_user_buff, 0, sizeof(g_sw_irq_user_buff));
            hal_nvic_register_isr_handler(sw_irq_id, hal_sw_irq_handle);
            hal_nvic_enable_irq(sw_irq_id);
            hal_queue_init(&g_sw_irq_queue);
            initialized = true;
        }
        /* find free item for save the user info */
        if (g_sw_irq_user_buff[g_sw_irq_index].used_flag) {
            status = HAL_SW_IRQ_STATUS_ERROR;
            break;
        }
        free_idx = g_sw_irq_index;
        g_sw_irq_index++;
        if (g_sw_irq_index >= MAX_SW_IRQ_USER) {
            g_sw_irq_index = 0;
        }
        g_sw_irq_user_buff[free_idx].call_back = user_callback;
        g_sw_irq_user_buff[free_idx].user_data = user_data;
        g_sw_irq_user_buff[free_idx].used_flag = 1;
        /* Push index to Q */
        res = hal_queue_push(&g_sw_irq_queue, free_idx);
        if (res < 0) {
            status = HAL_SW_IRQ_STATUS_Q_FULL;
            break;
        }
    } while (0);
    hal_nvic_restore_interrupt_mask(mask);

    /*Below code in here is for reduce disable irq time*/
    if (status == HAL_SW_IRQ_STATUS_OK) {
        hal_nvic_set_pending_irq(sw_irq_id);
    }
    return status;
}