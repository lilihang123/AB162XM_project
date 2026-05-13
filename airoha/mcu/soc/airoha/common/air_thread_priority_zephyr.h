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

#ifndef __AIR_THREAD_PRIORITY_ZEPHYR_H__
#define __AIR_THREAD_PRIORITY_ZEPHYR_H__

#include <stdlib.h>
#include <zephyr/types.h>
#include <zephyr/kernel.h>

#ifdef __cplusplus
extern "C" {
#endif


/* When CONFIG_MULTITHREADING is defined, zephyr kernel will check thread priority by
 * Z_VALID_PRIO in zephyr/kernel/include/ksched.h which was called by z_setup_new_thread.
 * This macro checks if the priority is within the valid range. */

typedef enum {
    PRIO_PREEMPT_LOWEST                 = K_LOWEST_THREAD_PRIO,
    PRIO_PREEMPT_LOW                    = K_LOWEST_THREAD_PRIO + 1,
    PRIO_PREEMPT_BELOW_NORMAL           = K_LOWEST_THREAD_PRIO + 2,
    PRIO_PREEMPT_NORMAL                 = K_LOWEST_THREAD_PRIO + 3,
    PRIO_PREEMPT_ABOVE_NORMAL           = K_LOWEST_THREAD_PRIO + 4,
    PRIO_PREEMPT_HIGH                   = K_LOWEST_THREAD_PRIO + 5,
    PRIO_PREEMPT_SOFT_REALTIME          = K_LOWEST_THREAD_PRIO + 6,
    PRIO_PREEMPT_HARD_REALTIME          = K_LOWEST_THREAD_PRIO + 7,

#if CONFIG_COOP_ENABLED
    PRIO_COOP_LOW                       = K_HIGHEST_THREAD_PRIO + 7,
    PRIO_COOP_BELOW_NORMAL              = K_HIGHEST_THREAD_PRIO + 6,
    PRIO_COOP_NORMAL                    = K_HIGHEST_THREAD_PRIO + 5,
    PRIO_COOP_ABOVE_NORMAL              = K_HIGHEST_THREAD_PRIO + 4,
    PRIO_COOP_HIGH                      = K_HIGHEST_THREAD_PRIO + 3,
    PRIO_COOP_SOFT_REALTIME             = K_HIGHEST_THREAD_PRIO + 2,
    PRIO_COOP_HARD_REALTIME             = K_HIGHEST_THREAD_PRIO + 1,
    PRIO_COOP_HIGHEST                   = K_HIGHEST_THREAD_PRIO
#endif
} air_thread_priority_type_e;


#ifdef __cplusplus
}
#endif

#endif /* __AIR_THREAD_PRIORITY_ZEPHYR_H__ */