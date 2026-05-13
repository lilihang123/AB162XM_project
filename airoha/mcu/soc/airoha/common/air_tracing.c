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

#include <tracing_user.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/logging/log.h>

#include "hal_nvic.h"

#ifdef AIR_SWLA_ENABLE
#include "swla.h"
#endif

/* weak symbol from tracing_user.h
void __weak sys_trace_thread_create_user(struct k_thread *thread) {}
void __weak sys_trace_thread_abort_user(struct k_thread *thread) {}
void __weak sys_trace_thread_suspend_user(struct k_thread *thread) {}
void __weak sys_trace_thread_resume_user(struct k_thread *thread) {}
void __weak sys_trace_thread_name_set_user(struct k_thread *thread) {}
void __weak sys_trace_thread_switched_in_user(void) {}
void __weak sys_trace_thread_switched_out_user(void) {}
void __weak sys_trace_thread_info_user(struct k_thread *thread) {}
void __weak sys_trace_thread_sched_ready_user(struct k_thread *thread) {}
void __weak sys_trace_thread_pend_user(struct k_thread *thread) {}
void __weak sys_trace_thread_priority_set_user(struct k_thread *thread, int prio) {}
void __weak sys_trace_isr_enter_user(void) {}
void __weak sys_trace_isr_exit_user(void) {}
void __weak sys_trace_idle_user(void) {}
void __weak sys_trace_sys_init_enter_user(const struct init_entry *entry, int level) {}
void __weak sys_trace_sys_init_exit_user(const struct init_entry *entry, int level, int result) {}
*/

#if IS_ENABLED(CONFIG_AIR_LOGGING_ENABLE)
#include "air_logging.h"
log_create_module(air_tracing, PRINT_LEVEL_INFO);
#endif

/* Private define ------------------------------------------------------------*/
typedef struct {
    struct k_thread *thread;
    uint8_t number;
    int8_t priority;
    char name[CONFIG_THREAD_MAX_NAME_LEN];
} __attribute__((packed)) sys_task_info_t;

/* Private macro -------------------------------------------------------------*/
#if IS_ENABLED(CONFIG_AIR_LOGGING_ENABLE)
#define TRACE_LOG(_message,...)             LOG_INF("[air_tracing] "_message,##__VA_ARGS__)
#else
#define TRACE_LOG(_message,...)             printk("[air_tracing] "_message,##__VA_ARGS__)
#endif

#define TRACE_LOCK_IRQ()\
            uint32_t irq_flag; \
            hal_nvic_save_and_set_interrupt_mask(&irq_flag)

#define TRACE_UNLOCK_IRQ()\
            hal_nvic_restore_interrupt_mask(irq_flag)


/* Private variables ---------------------------------------------------------*/
sys_task_info_t sys_task_info[16];
uint32_t g_uxTaskNumber = 0;


/* Private functions ---------------------------------------------------------*/
void sys_trace_sys_init_enter_user(const struct init_entry *entry, int level)
{
    TRACE_LOG("[air_tracing] init level: %d, init_fn: 0x%08X, dev: 0x%08X enter",
        level, (unsigned int)(entry->init_fn.sys), (unsigned int)(entry->dev));
}


void sys_trace_sys_init_exit_user(const struct init_entry *entry, int level, int result)
{
    TRACE_LOG("[air_tracing] init level: %d, init_fn: 0x%08X, dev: 0x%08X exit with result %d",
        level, (unsigned int)(entry->init_fn.sys), (unsigned int)(entry->dev), result);
}

void sys_trace_thread_create_user(struct k_thread *thread)
{
    char default_name[CONFIG_THREAD_MAX_NAME_LEN] = "unknown";
    const char *p_name = NULL, *src_name = NULL;
    uint32_t length;

    TRACE_LOG("thread:0x%x will create, TaskNumber:%d \n", (unsigned int)thread, g_uxTaskNumber);
    TRACE_LOCK_IRQ();

    /* max task number check */
    __ASSERT(g_uxTaskNumber < ARRAY_SIZE(sys_task_info), "Task number overflow");

    /* Return early if thread is NULL or task already initialized */
    if ((thread == NULL) || (sys_task_info[g_uxTaskNumber].thread != NULL)) {
        TRACE_UNLOCK_IRQ();
        return;
    }

    /* check thread had initialization */
    for (uint32_t i = 0; i < g_uxTaskNumber; i++) {
        if (thread == sys_task_info[i].thread) {
            TRACE_LOG("thread:0x%x create, TaskNumber:%d had already create!!! \n", (unsigned int)thread, i);
            TRACE_UNLOCK_IRQ();
            return;
        }
    }

    /* Initialize task info */
    sys_task_info[g_uxTaskNumber].thread = thread;
    sys_task_info[g_uxTaskNumber].number = g_uxTaskNumber;
    sys_task_info[g_uxTaskNumber].priority = thread->base.prio;

    /* Get thread name and copy it, use default if NULL */
    p_name = k_thread_name_get(thread);
    src_name = (p_name != NULL) ? p_name : default_name;
    length = strlen(src_name);
    if (length > CONFIG_THREAD_MAX_NAME_LEN) {
        length = CONFIG_THREAD_MAX_NAME_LEN;
    }
    memcpy(sys_task_info[g_uxTaskNumber].name, src_name, length);

    g_uxTaskNumber += 1;
    TRACE_UNLOCK_IRQ();
}


void sys_trace_thread_name_set_user(struct k_thread *thread)
{
    TRACE_LOCK_IRQ();
    for (uint32_t i = 0; i < g_uxTaskNumber; i++) {
        if (thread == sys_task_info[i].thread) {
            /* clear "unknown" character */
            memset(sys_task_info[i].name, 0, CONFIG_THREAD_MAX_NAME_LEN);
            /* filling thread name */
            memcpy(sys_task_info[i].name, thread->name, CONFIG_THREAD_MAX_NAME_LEN);
            break;
        }
    }
    TRACE_UNLOCK_IRQ();

	TRACE_LOG("thread:0x%x set name:%x %x %x %x \n", (unsigned int)thread, thread->name[0], thread->name[1], thread->name[2], thread->name[3]);
}

uint32_t sys_trace_query_thread_id(struct k_thread *thread)
{
    uint32_t uxTaskID = 0xFF;

    for (uint32_t i = 0; i < g_uxTaskNumber; i++) {
        if (thread == sys_task_info[i].thread) {
            uxTaskID = i;
            break;
        }
    }
    __ASSERT(uxTaskID != 0XFF, "Query task id loop overflow");

    return uxTaskID;
}

void sys_trace_thread_switched_in_user(void)
{
	struct k_thread *thread = k_current_get();

    /* When a new task is created, there will be a dummy context in/out before the task starts running.
        It will not carry thread parameters, so this context needs to be ignored.
        Dummy context in/out is not necessarily scheduled immediately after the task is created, but may be scheduled later than the creation... */
    if (thread != NULL) {
#ifdef AIR_SWLA_ENABLE
        HCLA_RamLogging_V2(SWLA_TYPE_TASK, sys_trace_query_thread_id(thread), SWLA_DIRECTION_LABEL);
#endif  /* AIR_SWLA_ENABLE */
    }

	// TRACE_LOG("contex in, thread: 0x%x \n", thread);
}

void sys_trace_thread_switched_out_user(void)
{
    // Get the current thread
}

