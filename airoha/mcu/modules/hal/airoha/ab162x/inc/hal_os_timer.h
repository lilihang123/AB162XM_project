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

#ifndef __HAL_OS_TIMER_H__
#define __HAL_OS_TIMER_H__

typedef enum {
    OS_GPT_TIMER_TYPE_ONE_SHOT  = 0,         /**< Set the GPT oneshot   mode.  */
    OS_GPT_TIMER_TYPE_REPEAT    = 1,         /**< Set the GPT repeat    mode.  */
    OS_GPT_TIMER_TYPE_FREERUN_I = 2,         /**< Set the GPT FREERUN_I mode.  */
    OS_GPT_TIMER_TYPE_FREERUN   = 3,         /**< Set the GPT FREERUN   mode.  */
} os_gpt_timer_type_t;


typedef enum {
    OS_GPT_CLOCK_SOURCE_32K = 0,            /**< Set the GPT clock source to 32kHz, 1 tick = 1/32768 seconds. */
    OS_GPT_CLOCK_SOURCE_1M  = 1             /**< Set the GPT clock source to 1MHz, 1 tick = 1 microsecond.*/
} os_gpt_clock_source_t;


void hal_os_timer_start(uint32_t time_out_us,
    os_gpt_timer_type_t timer_type,
    os_gpt_clock_source_t clock_source,
    float rtc_freq);


uint32_t hal_os_timer_stop(void);

void hal_os_timer_ack_irq(void);

uint32_t hal_os_timer_get_free_run_count(void);

void hal_os_timer_set_compare_value(uint32_t val);

uint32_t hal_os_timer_get_compare_value(void);


#endif //__HAL_OS_TIMER_H__

