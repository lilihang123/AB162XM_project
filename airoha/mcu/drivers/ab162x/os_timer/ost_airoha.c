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

#include <zephyr/irq.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/types.h>
#include <stddef.h>
#include <sys/types.h>
#include <zephyr/device.h>
#include <zephyr/sys_clock.h>
#include <zephyr/spinlock.h>
#include <zephyr/logging/log.h>
#include "memory_attribute.h"

#ifdef HAL_SLEEP_MANAGER_ENABLED
#ifdef CONFIG_PM
#include "hal_spm.h"
#include "hal_gpt.h"
#include "hal_rtc.h"
#include "hal_rtc_internal.h"
#include "hal_sleep_manager.h"
#include "hal_platform.h"
#include "hal_nvic_internal.h"
#include "hal_nvic.h"
#endif
#endif

/* Interface required by the zephyr kernel and scheduler. */
#include <zephyr/drivers/timer/system_timer.h>

#include <assert.h>

#include "air_chip.h"
#include "hal_nvic.h"
#include "hal_os_timer.h"

#if IS_ENABLED(CONFIG_TICKLESS_KERNEL)
static uint32_t ost_last_count[2], ost_count_remain_for_tick_calc;
#endif
static uint32_t cycle_count;

#define CYC_PER_TICK            (uint32_t)(CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC/CONFIG_SYS_CLOCK_TICKS_PER_SEC)
#define OS_GPT_TICK_IN_US       (uint32_t)(1000000/CONFIG_SYS_CLOCK_TICKS_PER_SEC)


#ifdef HAL_SLEEP_MANAGER_ENABLED
#ifdef CONFIG_PM
#define REMAINDER_LIMIT                     100*1000    //100ms
#define DEEP_SLEEP_SW_BACKUP_RESTORE_TIME   2
#define WDT_TRIGGER_TIME                    10          //(s)
#define WDT_BUFFER_TIME                     10          //(s)
ATTR_ZIDATA_IN_TCM uint32_t hw_latency_time_ms;

ATTR_ZIDATA_IN_TCM static uint32_t xExpectedIdleTime;
ATTR_ZIDATA_IN_TCM volatile uint32_t systick_change_period = 0;
ATTR_ZIDATA_IN_TCM volatile uint32_t tick_remainder = 0;

ATTR_ZIDATA_IN_TCM static uint32_t ulCompleteTickPeriods, remain, ulAST_Reload_ms, last_remain;
ATTR_ZIDATA_IN_TCM static uint32_t after_sleep_time, before_sleep_time;
ATTR_ZIDATA_IN_TCM static uint32_t sleep_time, tickless_timing;
ATTR_ZIDATA_IN_TCM static uint32_t wdt_sleep_time_ms;
ATTR_ZIDATA_IN_TCM static uint32_t before_time[2], after_time[2], duration_time[2];
ATTR_ZIDATA_IN_TCM static float calculation;
ATTR_RWDATA_IN_TCM float RTC_Freq = 32.768f; /* RTC 32.768KHz Freq*/
extern uint32_t sleep_sw_gpt_handle_rtc;
#endif
#endif
enum pm_state sleep_pm_state;
uint32_t pending_irq_mask1, pending_irq_mask2;
uint32_t enable_irq_mask1, enable_irq_mask2;


ATTR_TEXT_IN_TCM_RETENTION void ost_isr(hal_nvic_irq_t irq_number)
{
    ARG_UNUSED(irq_number);
    hal_os_timer_ack_irq();

#ifdef HAL_SLEEP_MANAGER_ENABLED
#ifdef CONFIG_PM
    if (systick_change_period != 0) {
        //printk(" Enter hal_os_timer_ack_irq\r\n");
        systick_change_period = 0;
        //hal_os_timer_start(portTICK_PERIOD_MS * 1000 , OS_GPT_TIMER_TYPE_REPEAT , OS_GPT_CLOCK_SOURCE_1M , RTC_Freq);
        hal_os_timer_start(OS_GPT_TICK_IN_US, OS_GPT_TIMER_TYPE_REPEAT , OS_GPT_CLOCK_SOURCE_1M , RTC_Freq);
    }
#endif
#endif

#if IS_ENABLED(CONFIG_TICKLESS_KERNEL)
    uint32_t curr_count = hal_os_timer_get_free_run_count();
    // printk("[OST] ISR was called at %d\r\n", curr_count);
    uint32_t ticks;
    if(curr_count > ost_last_count[1]){
        ticks = (curr_count - ost_last_count[1] + ost_count_remain_for_tick_calc)/OS_GPT_TICK_IN_US;
        ost_count_remain_for_tick_calc = (curr_count - ost_last_count[1] + ost_count_remain_for_tick_calc)%OS_GPT_TICK_IN_US;
    } else if(curr_count < ost_last_count[1]){
        ticks = ((uint32_t)0xFFFFFFFF - ost_last_count[1] + curr_count + ost_count_remain_for_tick_calc)/OS_GPT_TICK_IN_US;
        ost_count_remain_for_tick_calc = ((uint32_t)0xFFFFFFFF - ost_last_count[1] + curr_count + ost_count_remain_for_tick_calc)%OS_GPT_TICK_IN_US;
    } else {
        __ASSERT(curr_count != ost_last_count[1], "Sth error");
        ticks = (ost_count_remain_for_tick_calc)/OS_GPT_TICK_IN_US;
        ost_count_remain_for_tick_calc = ost_count_remain_for_tick_calc%OS_GPT_TICK_IN_US;
    }

    cycle_count += ticks*CYC_PER_TICK;
    ost_last_count[0] = ost_last_count[1];
    ost_last_count[1] = curr_count;
    if(ticks){
        // printk("[OST][Debug] announce %u sys clock ticks", ticks);
        // printk("[OST][Debug] count: %u, %u", ost_last_count[0], ost_last_count[1]);
        sys_clock_announce(ticks);
    }
#else
    sys_clock_announce(1);
    cycle_count += CYC_PER_TICK;
#endif
}

#if KERNELVERSION == 0x3030000
static int ost_init(const struct device *dev)
{
    ARG_UNUSED(dev);
#elif KERNELVERSION >= 0x3070000
static int ost_init(void)
{
#else
#error "Unkown supported kernel version"
#endif
    hal_nvic_disable_irq(OS_GPT_IRQn);
    hal_nvic_clear_pending_irq(OS_GPT_IRQn);
    hal_nvic_register_isr_handler(OS_GPT_IRQn, ost_isr);

#ifdef HAL_SLEEP_MANAGER_ENABLED
#ifdef CONFIG_PM
    uint32_t rtc_freq;

        /* Get RTC_Freq */
    hal_rtc_get_f32k_frequency(&rtc_freq);
    RTC_Freq = (float) (rtc_freq / 1000.0); /* convert to double variable */

    //int int_part = (int)RTC_Freq;
    //int frac_part = (int)((RTC_Freq - int_part) * 1000000);
    //printk("[SLP][RTC_Freq]RTC_Freq = %d.%06d\n", int_part, frac_part);

    //int hw_latency_time_32k = spm_latency_time_checking(); //SPM Latency Time
    //hw_latency_time_ms = (uint32_t)((((double)hw_latency_time_32k) * (1/32.768))) + 1;
#endif
#endif

#if IS_ENABLED(CONFIG_TICKLESS_KERNEL)
    /* Set a fake timeout event, assuming that the kernel will
     * definitely modify this value within 1 hour. */
    hal_os_timer_start(
        (uint32_t)60*60*1000000,
        OS_GPT_TIMER_TYPE_FREERUN_I,
        OS_GPT_CLOCK_SOURCE_1M,
        32.768f
    );
#else
    hal_os_timer_start(
        OS_GPT_TICK_IN_US,
        OS_GPT_TIMER_TYPE_REPEAT,
        OS_GPT_CLOCK_SOURCE_1M,
        32.768f
    );
#endif

    return 0;
}

#ifdef HAL_SLEEP_MANAGER_ENABLED
#ifdef CONFIG_PM
void ost_get_time_before_tickless(hal_gpt_clock_source_t clock_source){
#ifdef HAL_GPT_MODULE_ENABLED
    hal_gpt_get_free_run_count(clock_source, &before_sleep_time);
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&after_time[0]);
#endif
}

void ost_get_time_after_tickless(hal_gpt_clock_source_t clock_source){
#ifdef HAL_GPT_MODULE_ENABLED
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&before_time[1]);
    hal_gpt_get_free_run_count(clock_source, &after_sleep_time);
#endif
}
#endif
#endif


uint32_t sys_clock_elapsed(void)
{
#if IS_ENABLED(CONFIG_TICKLESS_KERNEL)
    uint32_t ticks, curr_count;
    uint32_t irq_flag = arch_irq_lock();
    curr_count = hal_os_timer_get_free_run_count();
    if(ost_last_count[1] > curr_count){
        ticks = (uint32_t)0xFFFFFFFF - ost_last_count[1] + curr_count;
        ticks /= OS_GPT_TICK_IN_US;
    } else if(ost_last_count[1] < curr_count){
        ticks = (curr_count - ost_last_count[1])/OS_GPT_TICK_IN_US;
    } else {
        ticks = 0;
    }
    arch_irq_unlock(irq_flag);
    // printk("[OST] elapsed %u ticks(%u, %u)", ticks, curr_count, ost_last_count[1]);
    return ticks;
#else
    return 0;
#endif
}

uint32_t sys_clock_cycle_get_32(void)
{
    uint32_t irq_flag = arch_irq_lock();
    uint32_t ret = cycle_count;
    arch_irq_unlock(irq_flag);
    return ret;
}
// uint32_t os_tickcount_test;
void sys_clock_set_timeout(int32_t ticks, bool idle)
{
    // __ASSERT(idle != true, "cannot receive idle");
#if IS_ENABLED(CONFIG_TICKLESS_KERNEL)
    // uint32_t lr = (uint32_t)__builtin_return_address(0);
#endif
    uint32_t irq_flag = arch_irq_lock();
#if IS_ENABLED(CONFIG_TICKLESS_KERNEL)
    uint32_t curr_count = 0xDEADBEEF;
#endif

    if( idle == true){ /* Enter Tickless Idle Feature */

#ifdef HAL_SLEEP_MANAGER_ENABLED
#if defined (CONFIG_PM)
    // __asm volatile("cpsid i");

    // os_tickcount_test = hal_os_timer_get_free_run_count();
#ifdef HAL_GPT_MODULE_ENABLED
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&before_time[0]);
#endif
    //printk("[SLP] before_time[0]=%d\r\n", before_time[0]);

    /* Must make sure sleep time is less than WDT max time */
    if (ticks >= (CONFIG_AIR_WDT_TIMEOUT_SEC_MAX - WDT_TRIGGER_TIME - WDT_BUFFER_TIME)*1000)
    {
        ticks = (CONFIG_AIR_WDT_TIMEOUT_SEC_MAX - WDT_TRIGGER_TIME - WDT_BUFFER_TIME)*1000;
    }

#if CONFIG_ARM_ON_ENTER_CPU_IDLE_PREPARE_HOOK
    extern void z_arm_on_enter_cpu_idle_prepare(void);
	z_arm_on_enter_cpu_idle_prepare();
#endif

    xExpectedIdleTime = ticks;
    ulAST_Reload_ms = ticks;

    //printk("[SLP] xExpectedIdleTime=%d\r\n", xExpectedIdleTime);
    //printk("[SLP] ulAST_Reload_ms=%d\r\n", ulAST_Reload_ms);

    if (systick_change_period != 0) {
        systick_change_period = 0;
        tick_remainder += hal_os_timer_stop();
        // tick_remainder = CONFIG_SYS_CLOCK_TICKS_PER_SEC - hal_os_timer_stop();
        tick_remainder += last_remain;
    } else {
        tick_remainder += hal_os_timer_stop();
        // tick_remainder = CONFIG_SYS_CLOCK_TICKS_PER_SEC - hal_os_timer_stop();
    }

    //printk("[SLP] tick_remainder=%d\r\n", tick_remainder);

    /* 1. check ulAST_Reload_ms unit, and method of convert to us
     * 2. reduce exit_latency_us
     * 3. convert to ms/tick
     */
    if(hal_sleep_manager_is_enter_tickless_sleep() == true){
        wdt_sleep_time_ms = ulAST_Reload_ms;
        hal_rtc_set_alarm_ms(sleep_sw_gpt_handle_rtc, ulAST_Reload_ms, (hal_rtc_time_callback_t)hal_sleep_manager_sw_gpt_callback_rtc, NULL);
    }else{
        wdt_sleep_time_ms = ulAST_Reload_ms;
        hal_os_timer_start(ulAST_Reload_ms * 1000 , OS_GPT_TIMER_TYPE_ONE_SHOT , OS_GPT_CLOCK_SOURCE_1M , RTC_Freq);
    }

#endif /* CONFIG_PM */
#endif /* HAL_SLEEP_MANAGER_ENABLED*/

    }else{
        /* tickless Kernel Feature */
#if IS_ENABLED(CONFIG_TICKLESS_KERNEL)
        if(ticks == 0){
            for(int repeat = 0; repeat < 3; repeat++){
                printk("[OST] !!!!!!!!!!!!!!!!!!! input zero !!!!!!!!!!!!!!!!!!!\r\n");
            }
        }
        /* Theoretically ticks equals to zero should not happen,
         * but in practice it does happen.
         * Maybe it's because the system clock is not calibrated ? */
        curr_count = hal_os_timer_get_free_run_count();
        curr_count += MAX((uint32_t)ticks, 1)*OS_GPT_TICK_IN_US;
        hal_os_timer_set_compare_value(curr_count);
#else
        /* No need to do anything special,
         * because every tick will have an interrupt. */
#endif
    }
    arch_irq_unlock(irq_flag);
#if IS_ENABLED(CONFIG_TICKLESS_KERNEL)
    // printk("[OST] ticks: %d, idle: %d, curr_count: %u, lr: 0x%08X, CPR: %u\r\n",
    //     ticks, idle, curr_count, lr, hal_os_timer_get_compare_value());
#endif
}

#ifdef CONFIG_PM
void pm_state_exit_post_ops(enum pm_state state, uint8_t substate_id){ }
#endif

extern uint32_t irq_mask_a, irq_mask_b;
void sys_clock_idle_exit(void)
{
    // uint16_t sleep_time = hal_sleep_manager_get_sleep_time();

    //printk("[SLP] Enter sys_clock_idle_exit\r\n");

#ifndef CONFIG_PM
    hal_os_timer_stop();
#else
#ifdef HAL_SLEEP_MANAGER_ENABLED
    ulCompleteTickPeriods = sleep_time/1000;
    //remain = sleep_time % ( portTICK_PERIOD_MS* 1000);
    /* CONFIG_SYS_CLOCK_TICKS_PER_SEC/1000*1000.
     * CONFIG_SYS_CLOCK_TICKS_PER_SEC/1000 => tickcounts_in_ms/ms
     * CONFIG_SYS_CLOCK_TICKS_PER_SEC/1000*1000 => tickcounts_in_us/ms
     */
    remain = sleep_time % CONFIG_SYS_CLOCK_TICKS_PER_SEC;
    tick_remainder += remain;
    //count_sleep_time_us += sleep_time; /*TODOs*/
    //printk("[SLP] ulCompleteTickPeriods=%d\r\n", ulCompleteTickPeriods);
    //printk("[OSTimer] remain=%d\r\n", remain);
    //printk("[SLP] tick_remainder=%d\r\n", tick_remainder);
#ifdef HAL_GPT_MODULE_ENABLED
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&after_time[1]);
    //printk("[SLP] after_time[1]=%d\r\n", after_time[1]);
    hal_gpt_get_duration_count(before_time[0], after_time[0], &duration_time[0]);
    hal_gpt_get_duration_count(before_time[1], after_time[1], &duration_time[1]);
    hal_gpt_get_duration_count(before_time[0], after_time[1], &tickless_timing);
#endif
    tick_remainder += duration_time[0] + duration_time[1];
    //printk("[SLP] tick_remainder=%d\r\n", tick_remainder);

    //printk("[SLP] CONFIG_SYS_CLOCK_TICKS_PER_SEC=%d\r\n", CONFIG_SYS_CLOCK_TICKS_PER_SEC);
    if (tick_remainder >= (CONFIG_SYS_CLOCK_TICKS_PER_SEC)) {
        tick_remainder -= (CONFIG_SYS_CLOCK_TICKS_PER_SEC);
        ulCompleteTickPeriods++;
        //printk("[SLP] ulCompleteTickPeriods++\r\n");
    }
    //printk("[SLP] ulCompleteTickPeriods=%d\r\n", ulCompleteTickPeriods);
    //printk("[SLP] tick_remainder=%d\r\n", tick_remainder);

    if (tick_remainder > 100) {
        systick_change_period = 1;
        last_remain = (tick_remainder % (CONFIG_SYS_CLOCK_TICKS_PER_SEC)); /* portTICK_PERIOD_MS * 1000 */
        tick_remainder -= last_remain;
        remain = (CONFIG_SYS_CLOCK_TICKS_PER_SEC) - last_remain; /* portTICK_PERIOD_MS * 1000 */
        // remain = last_remain;
        hal_os_timer_start(remain, OS_GPT_TIMER_TYPE_REPEAT , OS_GPT_CLOCK_SOURCE_1M , RTC_Freq);

    } else {
        systick_change_period = 0;
        hal_os_timer_start(OS_GPT_TICK_IN_US, OS_GPT_TIMER_TYPE_REPEAT , OS_GPT_CLOCK_SOURCE_1M , RTC_Freq);
    }
    // printk("[OSTimer][idle_exit] last_remain=%d\r\n", last_remain);
    // printk("[OSTimer][idle_exit] tick_remainder=%d\r\n", tick_remainder);
    // printk("[OSTimer][idle_exit] remain=%d\r\n", remain);
    //printk("[SLP] systick_change_period=%d\r\n", systick_change_period);

    // ToDo think
    // if (tick_remainder >= REMAINDER_LIMIT) {
    //     tick_remainder = REMAINDER_LIMIT;
    // }
    sys_clock_announce(ulCompleteTickPeriods);

    /* Enable all Global Interrupts */
    arch_irq_unlock(0);

#if 1
#else
    printk("[SLP][idle exit][IRQ Pending] sleep_pm_state=%u:%u, sleep_time=%u:%u:%u, irq_mask[0:31]=0x%08x:0x%08x, irq_mask[32:63]=0x%08x:0x%08x\r\n",
            sleep_pm_state,
            systick_change_period,
            sleep_time,
            ulAST_Reload_ms*1000,
            ulCompleteTickPeriods,
            pending_irq_mask1,
            enable_irq_mask1,
            pending_irq_mask2,
            enable_irq_mask2);
#endif
#endif
#endif
}

#ifdef HAL_SLEEP_MANAGER_ENABLED
#ifdef CONFIG_PM
void pm_state_set(enum pm_state state, uint8_t substate_id){

    /* IRQn is Pending. Leave sleep flow. hal_nvic_is_irq_pending() == true*/
    if(hal_nvic_is_irq_pending() == true){
        /* stop os timer or rtc timer */
        if(hal_sleep_manager_is_enter_tickless_sleep() == true){
            hal_rtc_stop_alarm(sleep_sw_gpt_handle_rtc);
            // hal_os_timer_stop();
        }else{
            hal_os_timer_stop();
        }
        hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&after_time[0]);
        /*Get Sleep time*/
        sleep_pm_state = PM_STATE_ACTIVE;
        sleep_time = 0;
        hal_nvic_get_pending_irq_by_mask( &irq_mask_a, &irq_mask_b);
        hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&before_time[1]);
        // printk("[SLP][state set][IRQ Pending] irq_mask[0:31]=0x%08x, irq_mask[32:63]=0x%08x\r\n", irq_mask_a, irq_mask_b);

    }else{ /* Enter Tickless IDLE or Tickless SLEEP mode*/

        //printk("[SLP] state=%d\r\n", state);
        if(state == PM_STATE_RUNTIME_IDLE){

#ifdef HAL_GPT_MODULE_ENABLED
            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &before_sleep_time);
            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&after_time[0]);
            //printk("[SLP] before_sleep_time=%d\r\n", before_sleep_time);
            //printk("[SLP] after_time[0]=%d\r\n", after_time[0]);
#endif

#ifdef HAL_WDT_MODULE_ENABLED
            uint32_t wdt_sleep_time_s = 0;
            if(wdt_sleep_time_ms != 0){
                wdt_sleep_time_s = (wdt_sleep_time_ms/1000+1);
               // printk("[SLP1][IDLE][WDT] (wdt_sleep_time_ms)=%d, (wdt_sleep_time_s)=%d\r\n"
               // , wdt_sleep_time_ms
               // , wdt_sleep_time_s
               // );
                if(wdt_sleep_time_s <= (CONFIG_AIR_WDT_TIMEOUT_SEC_MAX - WDT_TRIGGER_TIME - WDT_BUFFER_TIME + 1)){
                    /* WDT backup & Set WDT timeout timer (sleep time + WDT_TRIGGER_TIME) */
                    extern void hal_wdt_enter_sleep(uint32_t seconds, bool enable);
                    hal_wdt_enter_sleep( wdt_sleep_time_s + WDT_TRIGGER_TIME, true);
                    wdt_sleep_time_ms = 0;
                }
                else
                {
                    assert(0);
                }
            }else{
                /* If sleep time = K_TICKS_FOREVER, disable WDT */
                // printk("[SLP2][IDLE][WDT] (wdt_sleep_time_ms)=%d, (wdt_sleep_time_s)=%d\r\n"
                // , wdt_sleep_time_ms
                // , wdt_sleep_time_s
                // );
#if CONFIG_ARM_ON_ENTER_CPU_IDLE_PREPARE_HOOK
                extern void z_arm_on_enter_cpu_idle_prepare(void);
                z_arm_on_enter_cpu_idle_prepare();
#endif
                hal_os_timer_stop();
                hal_rtc_stop_alarm(sleep_sw_gpt_handle_rtc);
                extern void hal_wdt_enter_sleep(uint32_t seconds, bool enable);
                hal_wdt_enter_sleep(0, false);
            }
#endif

            /* Enter Sleep mode */
            sleep_pm_state = state;
            hal_sleep_manager_enter_sleep_mode(HAL_SLEEP_MODE_IDLE);

#ifdef HAL_WDT_MODULE_ENABLED
            extern void hal_wdt_exit_sleep(void);
            /* WDT restore & feet WDT */
            hal_wdt_exit_sleep();
            wdt_sleep_time_ms = 0;
#endif

            hal_nvic_get_pending_irq_by_mask(&pending_irq_mask1, &pending_irq_mask2);
            extern void hal_nvic_get_enable_irq_by_mask(uint32_t *irq_mask1,uint32_t *irq_mask2);
            hal_nvic_get_enable_irq_by_mask(&enable_irq_mask1, &enable_irq_mask2);

#ifdef HAL_GPT_MODULE_ENABLED
            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&before_time[1]);
            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &after_sleep_time);
            //printk("[SLP] before_time[1]=%d\r\n", before_time[1]);
            //printk("[SLP] after_sleep_time=%d\r\n", after_sleep_time);
#endif
            /* stop os timer */
            hal_os_timer_stop();

#ifdef HAL_GPT_MODULE_ENABLED
            hal_gpt_get_duration_count(before_sleep_time, after_sleep_time, &sleep_time);
            // printk("[SLP] sleep_time=%d\r\n", sleep_time);
#endif
        }
        else if(state == PM_STATE_SUSPEND_TO_RAM){
#ifdef HAL_RTC_MODULE_ENABLED
            before_sleep_time = hal_rtc_get_current(HAL_MCU_RTC_TIME); /* Get RTC 32 tickcount */
#endif
#ifdef HAL_GPT_MODULE_ENABLED
            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&after_time[0]);
#endif
            //printk("[SLP] before_sleep_time=%d\r\n", before_sleep_time);
            //printk("[SLP] after_time[0]=%d\r\n", after_time[0]);

#ifdef HAL_WDT_MODULE_ENABLED
            uint32_t wdt_sleep_time_s = 0;
            if(wdt_sleep_time_ms != 0){
                wdt_sleep_time_s = (wdt_sleep_time_ms/1000+1);
                // printk("[SLP1][SLEEP][WDT] (wdt_sleep_time_ms)=%d, (wdt_sleep_time_s)=%d\r\n"
                // , wdt_sleep_time_ms
                // , wdt_sleep_time_s
                // );
                if(wdt_sleep_time_s <= (CONFIG_AIR_WDT_TIMEOUT_SEC_MAX - WDT_TRIGGER_TIME - WDT_BUFFER_TIME + 1)){
                    /* WDT backup & Set WDT timeout timer (sleep time + WDT_TRIGGER_TIME) */
                    extern void hal_wdt_enter_sleep(uint32_t seconds, bool enable);
                    hal_wdt_enter_sleep( wdt_sleep_time_s + WDT_TRIGGER_TIME, true);
                    wdt_sleep_time_ms = 0;
                }
                else
                {
                    assert(0);
                }
            }else{
                /* If sleep time = K_TICKS_FOREVER, disable WDT */
                // printk("[SLP2][SLEEP][WDT] (wdt_sleep_time_ms)=%d, (wdt_sleep_time_s)=%d\r\n"
                // , wdt_sleep_time_ms
                // , wdt_sleep_time_s
                // );
#if CONFIG_ARM_ON_ENTER_CPU_IDLE_PREPARE_HOOK
                extern void z_arm_on_enter_cpu_idle_prepare(void);
                z_arm_on_enter_cpu_idle_prepare();
#endif
                hal_os_timer_stop();
                hal_rtc_stop_alarm(sleep_sw_gpt_handle_rtc);
                extern void hal_wdt_enter_sleep(uint32_t seconds, bool enable);
                hal_wdt_enter_sleep(0, false);
            }
#endif

            /* Enter Sleep mode */
            sleep_pm_state = state;
            hal_sleep_manager_enter_sleep_mode(HAL_SLEEP_MODE_SLEEP);

#ifdef HAL_WDT_MODULE_ENABLED
            extern void hal_wdt_exit_sleep(void);
            /* WDT restore & feet WDT */
            hal_wdt_exit_sleep();
            wdt_sleep_time_ms = 0;
#endif

            hal_nvic_get_pending_irq_by_mask(&pending_irq_mask1, &pending_irq_mask2);
            extern void hal_nvic_get_enable_irq_by_mask(uint32_t *irq_mask1,uint32_t *irq_mask2);
            hal_nvic_get_enable_irq_by_mask(&enable_irq_mask1, &enable_irq_mask2);

#ifdef HAL_GPT_MODULE_ENABLED
            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&before_time[1]);
#endif

#ifdef HAL_RTC_MODULE_ENABLED
            after_sleep_time = hal_rtc_get_current(HAL_MCU_RTC_TIME); /* Get rtc 32k tickcount */
#endif
            //printk("[SLP] before_time[1]=%d\r\n", before_time[1]);
            //printk("[SLP] after_sleep_time=%d\r\n", after_sleep_time);

            /* stop rtc timer */
            hal_rtc_stop_alarm(sleep_sw_gpt_handle_rtc);

#ifdef HAL_GPT_MODULE_ENABLED
            hal_gpt_get_duration_count(before_sleep_time, after_sleep_time, &sleep_time);
            // printk("[SLP] sleep_time=%d\r\n", sleep_time);
#endif

            /* 32k clock tickcounts convert to 1M tickcounts */
            sleep_time *= 1000;
            calculation = (float)sleep_time;
            calculation /= RTC_Freq;/*us*/

            sleep_time = calculation;
        }
        else{
            //assert!!! No define this low power mode
        }

    }
}
#endif
#else
void pm_state_set(enum pm_state state, uint8_t substate_id){}
#endif

#if !defined(AIR_DVT_TEST_NVIC_AND_ISR)
/* OS timer initialization. In order to ensure that single thread
 * can also use the k_timer class APIs, we cannot use CONFIG_MULTITHREADING
 * to omit this initialization flow.
  */
SYS_INIT(ost_init, CONFIG_OST_INIT_LEVEL, CONFIG_OST_INIT_PRIORITY);
#endif