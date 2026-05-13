/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
 *
 * This software/firmware and related documentation ("\r\nAiroha Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to Airoha Technology Corp. ("\r\nAiroha") and/or its licensors.
 * Without the prior written permission of Airoha and/or its licensors,
 * any reproduction, modification, use or disclosure of Airoha Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) Airoha Software
 * if you have agreed to and been bound by the applicable license agreement with
 * Airoha ("\r\nLicense Agreement") and been granted explicit permission to do so within
 * the License Agreement ("\r\nPermitted User").  If you are not a Permitted User,
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


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#define LOG_LEVEL LOG_LEVEL_DEBUG
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main);

#include "air_chip.h"
#include "hal_platform.h"

#if CONFIG_AIR_DAEMON_WORKQUEUE_ENABLE
#include "air_daemon_work_q.h"
#endif

#if defined(HAL_GPT_MODULE_ENABLED)
#include "hal_gpt.h"
#endif

#if defined(HAL_NVIC_MODULE_ENABLED)
#include "hal_nvic.h"
#endif



#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>

#include "memory_attribute.h"

#define THREAD_STACK_SIZE_IN_BYTES         2048
#define THREAD_COUNT                       4

struct k_thread thread[THREAD_COUNT];
K_THREAD_STACK_ARRAY_DEFINE(example_thread_stacks, THREAD_COUNT, THREAD_STACK_SIZE_IN_BYTES);


#ifndef CONFIG_AIR_LOGGING_ENABLE
    #undef LOG_INF
    #define LOG_INF printk
#endif

void print_all_thread_info(void);

void example_work_handler(struct k_work *work)
{
    uint32_t flags = 0;
    if(work != NULL){
        flags = work->flags;
        LOG_INF("work addr: 0x%08X, flags: 0x%08X", (unsigned int)work, (unsigned int)flags);
        if(flags & K_WORK_DELAYABLE){
            LOG_INF("handler was called by a delayable work");
        } else {
            LOG_INF("handler was called by a normal work");
        }
    }
    print_all_thread_info();
}
K_WORK_DEFINE(example_work, example_work_handler);
K_WORK_DELAYABLE_DEFINE(example_delayable_work, example_work_handler);

void print_rgs(uint32_t rg_base, uint32_t range)
{
    __ASSERT_NO_MSG((range % 16) == 0);
    uint32_t idx = 0;
    while(idx < range){
        LOG_INF("[0x%08X]: 0x%08X 0x%08X 0x%08X 0x%08X",
            rg_base + idx,
            *(volatile uint32_t *)(rg_base + idx),
            *(volatile uint32_t *)(rg_base + idx + 0x4),
            *(volatile uint32_t *)(rg_base + idx + 0x8),
            *(volatile uint32_t *)(rg_base + idx + 0xC)
        );
        idx += 0x10;
    }
}


uint32_t example_thread_round[THREAD_COUNT];
void example_thread(void* p1, void* p2, void* p3)
{
    int thread_num = (int)p1;
    for(;;){
        ++example_thread_round[thread_num];
        LOG_INF("thread %d running %d times...", thread_num, example_thread_round[thread_num]);
        LOG_INF("thread %d delay %d ms", thread_num, 1000*(THREAD_COUNT - thread_num));
        if(thread_num == (THREAD_COUNT - 1)){
            print_rgs(0x4000F000, 0x50);
        }

#if defined(AIR_BTD_IC_PREMIUM_G1)
        LOG_INF("RISCV JTAG: 0x%08X", (unsigned int)(*((volatile uint32_t*)0x420B0038)));
        LOG_INF("MCU JTAG: 0x%08X", (unsigned int)(*((volatile uint32_t*)0x420B0030)));
        LOG_INF("MCU JTAG Pull Up Status: 0x%08X", (unsigned int)(*((volatile uint32_t*)0x420C0070)));
        LOG_INF("RTC_IN_EN: 0x%08X", (unsigned int)(*((volatile uint32_t*)0x420C00E0)));
        LOG_INF("RTC_GPIO_MODE0: 0x%08X", (unsigned int)(*((volatile uint32_t*)0x420C00F0)));
#endif
        k_sleep(K_MSEC(1000*(THREAD_COUNT - thread_num)));
    }
}

int main(void)
{
    LOG_INF("multi thread with board name %s", CONFIG_BOARD);

    uint32_t idx;
    uint32_t irq_flag;

#if CONFIG_AIR_DAEMON_WORKQUEUE_ENABLE
    air_daemon_wq_work_submit(&example_work);
    air_daemon_wq_work_schedule(&example_delayable_work, K_SECONDS(3));
#else
    k_work_submit(&example_work);
    k_work_schedule(&example_delayable_work, K_SECONDS(3));
#endif

    /* Thread creation and setting thread name must be in the critical area,
     * otherwise the thread name obtained by SWLA may be 0.
     */
#if defined(HAL_NVIC_MODULE_ENABLED)
    hal_nvic_save_and_set_interrupt_mask(&irq_flag);
#else
    irq_flag = arch_irq_lock();
#endif

    for(idx = 0; idx < THREAD_COUNT; idx++){
#if defined(AIR_BTD_IC_PREMIUM_G1)
        uint32_t option = K_FP_REGS;
#elif defined(AIR_BTD_IC_MANDATORY_G1)
        /* ab161x( use Cortex-M0+ ) has not FPU */
        uint32_t option = 0;
#else
        #error "Unkown hardware"
#endif
        if(idx >= (THREAD_COUNT >> 1)){
            option |= K_ESSENTIAL;
        }

        k_thread_create(
            &thread[idx],                   // thread handle
            example_thread_stacks[idx],     // stack
            THREAD_STACK_SIZE_IN_BYTES,     // stack size
            example_thread,                 // thread entry point
            INT_TO_POINTER(idx),            // thread parameter 1
            NULL,                           // thread parameter 2
            NULL,                           // thread parameter 3
            K_PRIO_PREEMPT(idx),            // thread priority
            option,                         // thread options
            K_NO_WAIT                       // thread delay
        );

        char thread_name[0x20];
        memset(thread_name, 0x0, sizeof(thread_name));
        snprintf(thread_name, sizeof(thread_name), "T%03d", idx);
        k_thread_name_set(&thread[idx], thread_name);
        LOG_INF("thread %d(%s) create success.", idx, k_thread_name_get(&thread[idx]));
    }

#if defined(HAL_NVIC_MODULE_ENABLED)
    hal_nvic_restore_interrupt_mask(irq_flag);
#else
    arch_irq_unlock(irq_flag);
#endif

    for(idx = 0; idx < THREAD_COUNT; idx++){
        LOG_INF("before k_thread_join for thread %d", idx);
        k_thread_join(&thread[idx], K_FOREVER);
        LOG_INF("after k_thread_join for thread %d", idx);
    }

    return 0;
}

void print_thread_info(const struct k_thread *thread, void *user_data)
{
    char state_str[0x10];
    size_t free_stack_in_bytes = 0;
    memset(state_str, 0, sizeof(state_str));
    LOG_INF("thread 0x%08X( %s ):", (unsigned int)thread, k_thread_name_get((k_tid_t)thread));
    LOG_INF("    state: %s", k_thread_state_str((k_tid_t)thread, state_str, sizeof(state_str)));
    k_thread_stack_space_get((k_tid_t)thread, &free_stack_in_bytes);
    LOG_INF("    stack free bytes: %d", free_stack_in_bytes);
    LOG_INF("    priority: %d", k_thread_priority_get((k_tid_t)thread));
}

void print_all_thread_info(void)
{
    LOG_INF("##############print_all_thread_info##############");
    k_thread_foreach(print_thread_info, NULL);
    LOG_INF("#################################################");
}
