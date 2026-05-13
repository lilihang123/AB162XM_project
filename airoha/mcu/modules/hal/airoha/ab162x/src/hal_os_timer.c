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
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
 * RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
 * TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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

/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include "hal_gpt.h"
#include "hal_os_timer.h"
#include <zephyr/logging/log.h>

#include "hal_nvic.h"
#include "memory_attribute.h"

#if CONFIG_AIR_OST

static GPT_REGISTER_T *os_gpt0 = OS_GPT0;
static OS_GPT_REGISTER_GLOABL_T *os_gpt_glb = OS_GPTGLB;

#define OST_COUNT_CLEAR         (uint32_t)(0x1)
#define OST_COUNT_START         (uint32_t)(0x1)
#define OST_IRQ_ENABLE          (uint32_t)(0x1)
#define OST_IRQ_FLAG_ACK        (uint32_t)(0x1)
#define OST_CLOCK_32KHZ         (uint32_t)(0x10)

/* The default clock divider and clock source need to form 1MHz for software to use. */
/* The clock source may be XO( 16MHz ) or OSC( 13MHz ). */
#define DEFAULT_CLOCK           DT_PROP(DT_NODELABEL(os_timer), clock_source)
#define DEFAULT_CLOCK_DIVIDER   DT_PROP(DT_NODELABEL(os_timer), clock_divider)
#define OST_CLOCK_1MHZ          ((DEFAULT_CLOCK << 4) | (DEFAULT_CLOCK_DIVIDER))

#ifdef HAL_SLEEP_MANAGER_ENABLED
#ifdef CONFIG_PM
extern volatile uint32_t systick_change_period;
#endif
#endif


void hal_os_timer_start(uint32_t time_out_us,
    os_gpt_timer_type_t timer_type,
    os_gpt_clock_source_t clock_source,
    float rtc_freq)
{
    os_gpt_timer_type_t ost_type = timer_type;
    os_gpt_clock_source_t ost_source = clock_source;
    uint32_t time_out_us_reload;

    time_out_us_reload = (ost_type == OS_GPT_TIMER_TYPE_ONE_SHOT)? time_out_us : (time_out_us - 1);

    if ((time_out_us_reload / 1000) > HAL_GPT_MAXIMUM_MS_TIMER_TIME) {
        __ASSERT(0, "Sth wrong");
    }
    os_gpt0->GPT_CON_UNION.GPT_CON |= (1 << 16);       // disabled the clock source

    if (ost_source == OS_GPT_CLOCK_SOURCE_32K) {       // set clock source
        os_gpt0->GPT_CON_UNION.GPT_CON |= (1 << 16);   // disable clock before config
        os_gpt0->GPT_CLK = OST_CLOCK_32KHZ;            // set to 32KHz setting
        os_gpt0->GPT_CON_UNION.GPT_CON &= ~(1 << 16);  // enable clock

        os_gpt0->GPT_COMPARE = (uint32_t)(((float)(time_out_us_reload/1000)) *rtc_freq); // calculate the 32k count.

        os_gpt0->GPT_CLR      = 0x1;                   // clear the count
        while (os_gpt_glb->OS_GPT_CLRSTA & (1<<0));
    } else {
        /* set 16 divided with 16M source */
        os_gpt0->GPT_CON_UNION.GPT_CON |= (1 << 16);   // disable clock before config
        os_gpt0->GPT_CLK = OST_CLOCK_1MHZ;             // set to 1MHz setting
        os_gpt0->GPT_CON_UNION.GPT_CON &= ~(1 << 16);  // enable clock

        os_gpt0->GPT_COMPARE = time_out_us_reload;
        os_gpt0->GPT_CLR      = 0x1;                   // clear the count
        while (os_gpt_glb->OS_GPT_CLRSTA & (1<<0));
        (void)rtc_freq;
    }

    while (os_gpt_glb->OS_GPT_WCOMPSTA & (1<<0));

    os_gpt0->GPT_CON_UNION.GPT_CON &= ~(3 << 8);       //clear mode
    if (ost_type == OS_GPT_TIMER_TYPE_ONE_SHOT) {
        // keep one-shot mode
    } else if(ost_type == OS_GPT_TIMER_TYPE_REPEAT) {
        os_gpt0->GPT_CON_UNION.GPT_CON |= 0x100;       // set repeat mode
    } else if(ost_type == OS_GPT_TIMER_TYPE_FREERUN_I) {
        os_gpt0->GPT_CON_UNION.GPT_CON |= 0x200;       // set freerun_i mode
    } else {
        __ASSERT_NO_MSG(0);
        os_gpt0->GPT_CON_UNION.GPT_CON |= 0x300;       // set freerun mode
    }
    os_gpt_glb->OS_GPT_IRQMSK &= 0x2;                  // MCU IRQ enable
    os_gpt_glb->OS_GPT_WAKEUPMSK &= 0x2;               // MCU wakeup enable

    /* enable IRQ */
    os_gpt0->GPT_IRQ_EN = 0x1;
    hal_nvic_enable_irq(OS_GPT_IRQn);

    /* enable os timer */
    os_gpt0->GPT_CON_UNION.GPT_CON |= 0x01;
}


uint32_t hal_os_timer_stop(void)
{
    /*diable interrupt*/
    os_gpt0->GPT_IRQ_EN = ~OST_IRQ_ENABLE  ;
    /* stop timer */
    os_gpt0->GPT_CON_UNION.GPT_CON_CELLS.EN &= ~OST_COUNT_START;
    /* clean interrupt status */
    os_gpt0->GPT_IRQ_ACK = OST_IRQ_FLAG_ACK ;
    /* disable timer */
    os_gpt0->GPT_CON_UNION.GPT_CON = 0;

    hal_nvic_disable_irq(OS_GPT_IRQn);
    hal_nvic_clear_pending_irq(OS_GPT_IRQn);

    return os_gpt0->GPT_COUNT;
}


void hal_os_timer_ack_irq(void)
{
    os_gpt0->GPT_IRQ_ACK = 0x01;
}

uint32_t hal_os_timer_get_free_run_count(void)
{
    return os_gpt0->GPT_COUNT;
}

void hal_os_timer_set_compare_value(uint32_t val)
{
    os_gpt0->GPT_COMPARE = val;
}

uint32_t hal_os_timer_get_compare_value(void)
{
    return os_gpt0->GPT_COMPARE;
}

#endif /* CONFIG_AIR_OST */