/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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

#ifdef AIR_MEMORY_MONITOR_ENABLE

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>

#include "memory_monitor.h"
#include "memory_attribute.h"
#include "hal_nvic.h"
#include "hal_nvic_internal.h"
#include "exception_handler.h"


/* Private define ------------------------------------------------------------*/
typedef struct {
    unsigned int r0;
    unsigned int r1;
    unsigned int r2;
    unsigned int r3;
    unsigned int r4;
    unsigned int r5;
    unsigned int r6;
    unsigned int r7;
    unsigned int r8;
    unsigned int r9;
    unsigned int r10;
    unsigned int r11;
    unsigned int r12;
    unsigned int sp;
    unsigned int lr;
    unsigned int pc;
    unsigned int user;
} memorymonitor_context_t;

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t memorymonitor_context_count = 0;
memorymonitor_context_t memorymonitor_context[MEMORYMONITOR_CONTEXT_COUNT_TOTAL];
extern int memorymonitor_memory_check(void);

/* Public functions ----------------------------------------------------------*/
ATTR_WEAK_SYMBOL int memorymonitor_memory_check(void)
{
    // hal_dwt_request_watchpoint(MEMORYMONITOR_DWT_CHANNEL, ((uint32_t)0x0), 0x2, WDE_DATA_WO);
    // if ( *((int *)0x0 + 4) > 0x10000 )
    // {
    //     return -1;
    // }

    printk("Please override memorymonitor_memory_check() in your application !!!");

    return -1;
}

#ifdef CONFIG_AIR_BYPASS_FLASH_RETURN_READY_ENABLE
ATTR_TEXT_IN_TCM void memorymonitor_interrupt_enter_trace(int irq_number)
#else
void memorymonitor_interrupt_enter_trace(int irq_number)
#endif 
{
    uint32_t saved_mask = 0;

    if (irq_number != 0) {
        hal_nvic_save_and_set_interrupt_mask(&saved_mask);

        if (memorymonitor_memory_check() != 0) {
            assert(0);
        }

        hal_nvic_restore_interrupt_mask(saved_mask);
    }
}
#ifdef CONFIG_AIR_BYPASS_FLASH_RETURN_READY_ENABLE
ATTR_TEXT_IN_TCM void memorymonitor_interrupt_exit_trace(int irq_number)
#else
void memorymonitor_interrupt_exit_trace(int irq_number)
#endif 
{
    uint32_t saved_mask = 0;

    if (irq_number != 0) {
        hal_nvic_save_and_set_interrupt_mask(&saved_mask);

        if (memorymonitor_memory_check() != 0) {
            assert(0);
        }

        hal_nvic_restore_interrupt_mask(saved_mask);
    }
}

void memorymonitor_task_enter_trace(void)
{
    uint32_t saved_mask = 0;

    hal_nvic_save_and_set_interrupt_mask(&saved_mask);

    if (memorymonitor_memory_check() != 0) {
        assert(0);
    }

    hal_nvic_restore_interrupt_mask(saved_mask);
}

void memorymonitor_task_exit_trace(void)
{
    uint32_t saved_mask = 0;

    hal_nvic_save_and_set_interrupt_mask(&saved_mask);

    if (memorymonitor_memory_check() != 0) {
        assert(0);
    }

    hal_nvic_restore_interrupt_mask(saved_mask);
}

int memorymonitor_exception_enter_trace(uint32_t stack0, uint32_t stack1)
{
    uint32_t offset, is_match;
    memorymonitor_context_t *current_context = &memorymonitor_context[memorymonitor_context_count % MEMORYMONITOR_CONTEXT_COUNT_TOTAL];

    // extern void Flash_ReturnReady(void);
    // Flash_ReturnReady();

    offset = (0x10 * MEMORYMONITOR_DWT_CHANNEL) / 4;
    is_match = ((*((uint32_t *)(&DWT->FUNCTION0) + offset)) & DWT_FUNCTION_MATCHED_Msk) >> DWT_FUNCTION_MATCHED_Pos;

    if (is_match) {
        /* memory monitor dwt channel is triggered */

        /* Copy registers r0 to r12 from stack1 */
        memcpy((void*)(&(current_context->r0)), (void *)stack1, 13 * sizeof(uint32_t));

        if (stack0 == stack1) {
            /* exception happens in exception mode */
            current_context->sp = stack1 + 14 * 4;
            current_context->lr = *((uint32_t *)stack1 + 19);
            current_context->pc = *((uint32_t *)stack1 + 20);
            current_context->user = *((uint32_t *)stack1 + 24) & 0x1ff;
        } else {
            /* exception happens in thread mode */
            current_context->sp = stack0;
            current_context->lr = *((uint32_t *)stack0 + 5);
            current_context->pc = *((uint32_t *)stack0 + 6);
            current_context->user = (uint32_t)k_current_get();
        }

        memorymonitor_context_count++;

        return memorymonitor_memory_check();
    } else {
        /* other dwt channel is triggered */
        return -1;
    }
}
#else

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
uint32_t * memorymonitor_exception_enter_trace = NULL;

#endif /* AIR_MEMORY_MONITOR_ENABLE */
