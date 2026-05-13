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


#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "air_daemon_work_q.h"

#if IS_ENABLED(CONFIG_AIR_LOGGING_ENABLE)
#include "air_logging.h"
log_create_module(air_daemon, PRINT_LEVEL_INFO);
#endif

/* Private macro -------------------------------------------------------------*/
#if IS_ENABLED(CONFIG_AIR_LOGGING_ENABLE)
#define AIR_DAEMON_LOG(_message,...)             LOG_INF("[air_daemon] "_message,##__VA_ARGS__)
#else
#define AIR_DAEMON_LOG(_message,...)             printk("[air_daemon] "_message,##__VA_ARGS__)
#endif


#if IS_ENABLED(CONFIG_MULTITHREADING)

static K_KERNEL_STACK_DEFINE(daemon_work_q_stack, CONFIG_AIR_DAEMON_WORKQUEUE_STACK_SIZE);

struct k_work_q k_daemon_work_q;

static int k_daemon_work_q_init(void)
{
    const struct k_work_queue_config cfg = {
        .name = "daemon_wq",
        .no_yield = IS_ENABLED(CONFIG_SYSTEM_WORKQUEUE_NO_YIELD),
        .essential = true,
    };

    k_work_queue_start(&k_daemon_work_q,
                daemon_work_q_stack,
                K_KERNEL_STACK_SIZEOF(daemon_work_q_stack),
                K_LOWEST_APPLICATION_THREAD_PRIO, &cfg);
    return 0;
}

int air_daemon_wq_work_submit(struct k_work *work)
{
    uint32_t lr = (uint32_t)__builtin_return_address(0);
    __ASSERT_NO_MSG(work != NULL);
    __ASSERT_NO_MSG(work->handler != NULL);
    int result = k_work_submit_to_queue(&k_daemon_work_q, work);
    AIR_DAEMON_LOG("0x%08X submit a work item(fn: 0x%08X) at 0x%08X with result %d",
        (unsigned int)lr,
        (unsigned int)(work->handler),
        (unsigned int)work,
        result
    );
    return result;
}

int air_daemon_wq_work_schedule(struct k_work_delayable *dwork, k_timeout_t delay)
{
    uint32_t lr = (uint32_t)__builtin_return_address(0);
    __ASSERT_NO_MSG(dwork != NULL);
    __ASSERT_NO_MSG(dwork->work.handler != NULL);
    int result = k_work_schedule_for_queue(&k_daemon_work_q, dwork, delay);
    AIR_DAEMON_LOG("0x%08X schedule a work item(fn: 0x%08X) at 0x%08X with delay %d ticks with result %d",
        (unsigned int)lr,
        (unsigned int)(dwork->work.handler),
        (unsigned int)dwork,
        (int)(delay.ticks),
        result
    );
    return result;
}

int air_daemon_wq_work_reschedule(struct k_work_delayable *dwork, k_timeout_t delay)
{
    uint32_t lr = (uint32_t)__builtin_return_address(0);
    __ASSERT_NO_MSG(dwork != NULL);
    __ASSERT_NO_MSG(dwork->work.handler != NULL);
    int result = k_work_reschedule_for_queue(&k_daemon_work_q, dwork, delay);
    AIR_DAEMON_LOG("0x%08X reschedule a work item(fn: 0x%08X) at 0x%08X with delay %d ticks with result %d",
        (unsigned int)lr,
        (unsigned int)(dwork->work.handler),
        (unsigned int)dwork,
        (int)delay.ticks,
        result
    );
    return result;
}

int air_daemon_wq_drain(bool plug)
{
    uint32_t lr = (uint32_t)__builtin_return_address(0);
    int result = k_work_queue_drain(&k_daemon_work_q, plug);
    AIR_DAEMON_LOG("0x%08X darin the daemon work queue with flag %d with result %d",
        (unsigned int)lr,
        plug,
        result
    );
    return result;
}

int air_daemon_wq_unplug(void)
{
    uint32_t lr = (uint32_t)__builtin_return_address(0);
    int result = k_work_queue_unplug(&k_daemon_work_q);
    AIR_DAEMON_LOG("0x%08X unplug the daemon work queue with result %d", (unsigned int)lr, result);
    return result;
}

SYS_INIT(k_daemon_work_q_init, CONFIG_DAEMON_WORK_Q_INIT_LEVEL, CONFIG_DAEMON_WORK_Q_INIT_PRIORITY);

#else
int air_daemon_wq_work_submit(struct k_work *work)
{
    ARG_UNUSED(work);
    return -1;
}

int air_daemon_wq_work_schedule(struct k_work_delayable *dwork, k_timeout_t delay)
{
    ARG_UNUSED(dwork);
    ARG_UNUSED(delay);
    return -1;
}

int air_daemon_wq_work_reschedule(struct k_work_delayable *dwork, k_timeout_t delay)
{
    ARG_UNUSED(dwork);
    ARG_UNUSED(delay);
    return -1;
}

int air_daemon_wq_drain(bool plug)
{
    ARG_UNUSED(plug);
    return -1;
}

int air_daemon_wq_unplug(void)
{
    return -1;
}
#endif
