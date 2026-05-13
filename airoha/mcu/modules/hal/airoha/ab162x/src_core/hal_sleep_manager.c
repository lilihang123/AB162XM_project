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

#include "hal_sleep_manager.h"
#include <zephyr/pm/pm.h>
#ifdef HAL_SLEEP_MANAGER_ENABLED
#include "hal_rtc.h"
#include "hal_gpt.h"
#include "hal_gpt_internal.h"
#include "hal_sleep_manager_internal.h"
#include "hal_sleep_manager_platform.h"
#include "hal_clock_platform.h"
#include "hal_gpio.h"
//#include "hal_pmu.h"
//#include "hal_resource_assignment.h"
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#ifdef MTK_SWLA_ENABLE
#include "swla.h"
#endif /* MTK_SWLA_ENABLE */

#ifdef CONFIG_PM
const struct pm_state_info state_info[] = PM_STATE_INFO_LIST_FROM_DT_CPU(DT_NODELABEL(cpu0));
const uint32_t num_power_states = DT_NUM_CPU_POWER_STATES(DT_NODELABEL(cpu0));

// static int32_t max_latency_cyc = -1;
//static int64_t next_event_cyc = -1;
static int32_t next_event_cyc = -1;
static bool tickless_sleep_flag = false;

const uint32_t idle_exit_latency_us = state_info[0].exit_latency_us;/* PM_STATE_RUNTIME_IDLE */
const uint32_t sleep_exit_latency_us = state_info[num_power_states-1].exit_latency_us; /* PM_STATE_SUSPEND_TO_RAM */
// const uint32_t idle_exit_latency_us = k_us_to_cyc_ceil32(idle_state->exit_latency_us);
// const uint32_t sleep_exit_latency_us = k_us_to_cyc_ceil32(sleep_state->exit_latency_us);
#endif

static uint32_t sleep_sw_gpt_handle;
#ifdef HAL_RTC_MODULE_ENABLED
uint32_t sleep_sw_gpt_handle_rtc;
#endif
void hal_sleep_manager_sw_gpt_callback()
{
    // *(volatile uint32_t*)( 0x4213007C ) = 0xA3;
    //printk("hal_sleep_manager_sw_gpt_callback\r\n");
    //hal_gpt_sw_stop_timer_ms(sleep_sw_gpt_handle); /* stop timer clear gpt irq */
    hal_gpt_sw_stop_timer_us(sleep_sw_gpt_handle); /* stop timer clear gpt irq */

    hal_sleep_manager_set_sleep_time(5000000);
    //hal_sleep_manager_set_sleep_time(10000);
    // *(volatile uint32_t*)( 0x4213007C ) = 0xA3;
}

void hal_sleep_manager_sw_gpt_callback_rtc()
{
    // *(volatile uint32_t*)( 0x4213007C ) = 0xA3;
    //printk("hal_sleep_manager_sw_gpt_callback_rtc\r\n");
    //hal_gpt_sw_stop_timer_ms(sleep_sw_gpt_handle); /* stop timer clear gpt irq */
#ifdef HAL_RTC_MODULE_ENABLED
    hal_rtc_stop_alarm(sleep_sw_gpt_handle_rtc); /* stop timer clear gpt irq */
#endif
    // hal_sleep_manager_set_sleep_time_rtc(2000);
    //hal_sleep_manager_set_sleep_time(10000);
    *SPM_TOP_STATE_STATUS = 0xA1;
}

ATTR_TEXT_IN_TCM_RETENTION uint8_t hal_sleep_manager_set_sleep_handle(const char *handle_name)
{
    uint8_t index;
    index = sleep_management_get_lock_handle(handle_name);
    return index;
}

ATTR_TEXT_IN_TCM_RETENTION hal_sleep_manager_status_t hal_sleep_manager_lock_sleep(uint8_t handle_index)
{
    sleep_management_lock_sleep(LOCK_SLEEP, handle_index);
    return HAL_SLEEP_MANAGER_OK;
}

ATTR_TEXT_IN_TCM_RETENTION hal_sleep_manager_status_t hal_sleep_manager_unlock_sleep(uint8_t handle_index)
{
    sleep_management_lock_sleep(UNLOCK_SLEEP, handle_index);
    return HAL_SLEEP_MANAGER_OK;
}

ATTR_TEXT_IN_TCM_RETENTION hal_sleep_manager_status_t hal_sleep_manager_release_sleep_handle(uint8_t handle_index)
{
    if (hal_sleep_manager_get_lock_status() & (1 << handle_index)) {
        log_hal_msgid_error("handle %d is currently holding a lock, cannot release\n", 1, handle_index);
        return HAL_SLEEP_MANAGER_ERROR;
    }
    sleep_management_release_lock_handle(handle_index);
    return HAL_SLEEP_MANAGER_OK;
}

ATTR_TEXT_IN_TCM_RETENTION uint32_t hal_sleep_manager_get_lock_status(void)
{
    return sleep_management_get_lock_sleep_request_info();
}

ATTR_TEXT_IN_TCM_RETENTION bool hal_sleep_manager_is_sleep_locked(void)
{
    return sleep_management_check_sleep_locks();
}

ATTR_TEXT_IN_TCM_RETENTION bool hal_sleep_manager_is_sleep_handle_alive(uint8_t handle_index)
{
    return sleep_management_check_handle_status(handle_index);
}

#ifdef CONFIG_PM
bool hal_sleep_manager_is_enter_tickless_sleep(void)
{
    return tickless_sleep_flag;
}
#endif

uint8_t hal_sleep_manager_set_idle_handle(const char *handle_name)
{
    uint8_t index;
    index = sleep_management_get_lock_idle_handle(handle_name);
    return index;
}

hal_sleep_manager_status_t hal_sleep_manager_lock_idle(uint8_t handle_index)
{
    sleep_management_lock_idle(LOCK_TICKLESS_IDLE, handle_index);
    return HAL_SLEEP_MANAGER_OK;
}

hal_sleep_manager_status_t hal_sleep_manager_unlock_idle(uint8_t handle_index)
{
    sleep_management_lock_idle(UNLOCK_TICKLESS_IDLE, handle_index);
    return HAL_SLEEP_MANAGER_OK;
}

hal_sleep_manager_status_t hal_sleep_manager_release_idle_handle(uint8_t handle_index)
{
    if (hal_sleep_manager_get_idle_lock_status() & (1 << handle_index)) {
        log_hal_msgid_error("handle %d is currently holding a lock, cannot release\n", 1, handle_index);
        return HAL_SLEEP_MANAGER_ERROR;
    }
    sleep_management_release_lock_idle_handle(handle_index);
    return HAL_SLEEP_MANAGER_OK;
}

uint32_t hal_sleep_manager_get_idle_lock_status(void)
{
    return sleep_management_get_lock_idle_request_info();
}

bool hal_sleep_manager_is_idle_locked(void)
{   
    if(	hal_sleep_manager_is_sleep_handle_alive(SLEEP_LOCK_BT_CONTROLLER) == true
		||  hal_sleep_manager_is_sleep_handle_alive(SLEEP_LOCK_USB) == true
		||  hal_sleep_manager_is_sleep_handle_alive(SLEEP_LOCK_APP_PURE) == true){
        return true;
    }else{
        return sleep_management_check_idle_locks();
    }
}

uint8_t hal_sleep_manager_set_extslp_handle(const char *handle_name)
{
    uint8_t index;
    index = sleep_management_get_lock_extslp_handle(handle_name);
    return index;
}

hal_sleep_manager_status_t hal_sleep_manager_lock_extslp(uint8_t handle_index)
{
    sleep_management_lock_extslp(LOCK_EXTSLP, handle_index);
    return HAL_SLEEP_MANAGER_OK;
}

hal_sleep_manager_status_t hal_sleep_manager_unlock_extslp(uint8_t handle_index)
{
    sleep_management_lock_extslp(UNLOCK_EXTSLP, handle_index);
    return HAL_SLEEP_MANAGER_OK;
}

hal_sleep_manager_status_t hal_sleep_manager_release_extslp_handle(uint8_t handle_index)
{
    if (hal_sleep_manager_get_extslp_lock_status() & (1 << handle_index)) {
        log_hal_msgid_error("handle %d is currently holding a lock, cannot release\n", 1, handle_index);
        return HAL_SLEEP_MANAGER_ERROR;
    }
    sleep_management_release_lock_extslp_handle(handle_index);
    return HAL_SLEEP_MANAGER_OK;
}

uint32_t hal_sleep_manager_get_extslp_lock_status(void)
{
    return sleep_management_get_lock_extslp_request_info();
}

bool hal_sleep_manager_is_extslp_locked(void)
{
    return sleep_management_check_extslp_locks();
}

hal_sleep_manager_status_t hal_sleep_manager_set_sleep_time(uint32_t sleep_time_ms)
{
    hal_gpt_status_t    ret_status;

    if (sleep_time_ms > HAL_GPT_MAXIMUM_MS_TIMER_TIME) {
        sleep_time_ms = HAL_GPT_MAXIMUM_MS_TIMER_TIME;
    }

    //hal_gpt_sw_stop_timer_ms(sleep_sw_gpt_handle); /* hal_gpt_sw_start_timer_ms clk souce = 32k, fpga no 32k */
    //ret_status = hal_gpt_sw_start_timer_ms(sleep_sw_gpt_handle, sleep_time_ms, (hal_gpt_callback_t)hal_sleep_manager_sw_gpt_callback, NULL);

    hal_gpt_sw_stop_timer_us(sleep_sw_gpt_handle); /* hal_gpt_sw_start_timer_ms clk souce = 32M*/
    ret_status = hal_gpt_sw_start_timer_us(sleep_sw_gpt_handle, sleep_time_ms, (hal_gpt_callback_t)hal_sleep_manager_sw_gpt_callback, NULL);

    if (ret_status != HAL_GPT_STATUS_OK) {
        log_hal_error("ERROR : Deep Sleep GPT Start Fail %d", ret_status);
        return HAL_SLEEP_MANAGER_ERROR;
    }

    return HAL_SLEEP_MANAGER_OK;
}

hal_sleep_manager_status_t hal_sleep_manager_set_sleep_time_rtc(uint32_t sleep_time_ms)
{
#ifdef HAL_RTC_MODULE_ENABLED
    hal_rtc_status_t    ret_status;

    //ret_status = hal_rtc_time_enable();
    //printk("[rtc][enable]ret_status=%d \r\n", ret_status);

    //ret_status = hal_rtc_sw_get_timer(&sleep_sw_gpt_handle_rtc);
    //printk("[Get][timer]ret_status=%d \r\n", ret_status);

    //hal_gpt_sw_stop_timer_ms(sleep_sw_gpt_handle); /* hal_gpt_sw_start_timer_ms clk souce = 32k, fpga no 32k */
    //ret_status = hal_gpt_sw_start_timer_ms(sleep_sw_gpt_handle, sleep_time_ms, (hal_gpt_callback_t)hal_sleep_manager_sw_gpt_callback, NULL);

    hal_rtc_stop_alarm(sleep_sw_gpt_handle_rtc); /* hal_gpt_sw_start_timer_ms clk souce = 32M*/
    ret_status = hal_rtc_set_alarm_ms(sleep_sw_gpt_handle_rtc, sleep_time_ms, (hal_rtc_time_callback_t)hal_sleep_manager_sw_gpt_callback_rtc, NULL);

    if (ret_status != HAL_RTC_STATUS_OK) {
        log_hal_error("ERROR : Deep Sleep GPT Start Fail %d", ret_status);
        return HAL_SLEEP_MANAGER_ERROR;
    }
#endif

    return HAL_SLEEP_MANAGER_OK;
}

ATTR_TEXT_IN_TCM_RETENTION void hal_sleep_manager_enter_sleep_mode(hal_sleep_mode_t mode)
{
    //printk("[SPM] enter hal_sleep_manager_enter_sleep_mode\r\n");

    // spm_debug_io(0x44424345);

    if (mode == HAL_SLEEP_MODE_IDLE) {
        //printk("[SPM] enter HAL_SLEEP_MODE_IDLE\r\n");

        /* Feed WDT */
#if CONFIG_ARM_ON_ENTER_CPU_IDLE_PREPARE_HOOK
        extern void z_arm_on_enter_cpu_idle_prepare(void);
        z_arm_on_enter_cpu_idle_prepare();
#endif

#ifdef MTK_SWLA_ENABLE
        HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_wfi, SWLA_DIRECTION_START);
#endif /* MTK_SWLA_ENABLE */
        uint32_t mask;

        __disable_irq();
        mask = __get_BASEPRI();
        __set_BASEPRI(0);
        __asm volatile("dsb");
        __asm volatile("wfi");
        __asm volatile("isb");
        __set_BASEPRI(mask);
        __enable_irq();

#ifdef MTK_SWLA_ENABLE
        HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_wfi, SWLA_DIRECTION_STOP);
#endif /* MTK_SWLA_ENABLE */
    } else if (mode == HAL_SLEEP_MODE_SLEEP) {
        //printk("[SPM] enter HAL_SLEEP_MODE_SLEEP\r\n");
        //spm_debug_io(0x42434243);
#ifdef MTK_SWLA_ENABLE
        HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_dpm, SWLA_DIRECTION_START);
#endif /* MTK_SWLA_ENABLE */
        //hal_core_status_write(HAL_CORE_MCU, HAL_CORE_SLEEP);

        /* NS module backup in Limit TZ*/
#ifndef AIR_CPU_IN_SECURITY_MODE
        sleep_management_ns_suspend_callback();
#endif

#ifdef AIR_CPU_IN_SECURITY_MODE
        // printk("[SPM] enter sleep_management_enter_deep_sleep\r\n");
        /* Sleep in All In Secure*/
        sleep_management_enter_deep_sleep(HAL_SLEEP_MODE_SLEEP);
#else
        /* Switch To S By NSC Fuction In Limit TZ or TCB In All In Secure*/
        sleep_management_enter_deep_sleep_in_secure(HAL_SLEEP_MODE_SLEEP);
#endif

        /* NS module restore in Limit TZ*/
#ifndef AIR_CPU_IN_SECURITY_MODE
        sleep_management_ns_resume_callback();
#endif

        //hal_core_status_write(HAL_CORE_MCU, HAL_CORE_ACTIVE);
#ifdef MTK_SWLA_ENABLE
        HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_dpm, SWLA_DIRECTION_STOP);
#endif /* MTK_SWLA_ENABLE */
    }
}

#ifdef HAL_SLEEP_MANAGER_SUPPORT_WAKEUP_SOURCE_CONFIG
ATTR_TEXT_IN_TCM_RETENTION hal_sleep_manager_status_t hal_sleep_manager_enable_wakeup_pin(hal_sleep_manager_wakeup_source_t pin)
{
    spm_unmask_wakeup_source(pin);
    return HAL_SLEEP_MANAGER_OK;
}

ATTR_TEXT_IN_TCM_RETENTION hal_sleep_manager_status_t hal_sleep_manager_disable_wakeup_pin(hal_sleep_manager_wakeup_source_t pin)
{
    spm_mask_wakeup_source(pin);
    return HAL_SLEEP_MANAGER_OK;
}
#endif
uint8_t sleep_manager_handle;
uint8_t sleep_manager_extslp_handle;
uint8_t sleep_manager_idle_handle;
hal_sleep_manager_status_t hal_sleep_manager_init()
{
#ifdef HAL_RTC_MODULE_ENABLED
    hal_rtc_status_t    ret_status;
#endif
    printk("[SLP] hal_sleep_manager_init start\r\n");

    // spm_debug_io(0x7f7e4342);

    /* Disable SPM DCM for bring-up, otherwise should enable for power saving */
    *SPM_CLK_SW_CON__RG_CM_FORCE_FAST_BAR = (uint8_t)(0x1);
    hal_gpt_delay_us(3);
    printk("[SLP] SPM_CLK_SW_CON__RG_CM_FORCE_FAST_BAR=0x%08x\r\n", *SPM_CLK_SW_CON__RG_CM_FORCE_FAST_BAR);

#if IS_ENABLED(CONFIG_AIR_RISCV_BUILD)
    *SPM_CFG_RISCV_FAKE_PWR = 0x1;
    printk("[SLP] *SPM_CFG_RISCV_FAKE_PWR(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_RISCV_FAKE_PWR, *SPM_CFG_RISCV_FAKE_PWR);
#else
    /* IBEX DEEP SLEEP & FAKE PWR*/
    *SPM_CFG_RISCV_FAKE_PWR = 0x0;
    *RISCV_DEEP_SLEEP |= 0x100;
    *SPM_CFG_IGNORE_CPU_ACTIVE |= (1 << 16);
    printk("[SLP]*RISCV_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)RISCV_DEEP_SLEEP, *RISCV_DEEP_SLEEP);
    printk("[SLP] *SPM_CFG_RISCV_FAKE_PWR(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_RISCV_FAKE_PWR, *SPM_CFG_RISCV_FAKE_PWR);
    printk("[SLP] *SPM_CFG_IGNORE_CPU_ACTIVE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_IGNORE_CPU_ACTIVE, *SPM_CFG_IGNORE_CPU_ACTIVE);
#endif

    /* Lock S1 */
    // *SPM_CFG_SPM_STATE_CONTROL_0 = 0x1;
    printk("[SLP] *SPM_CFG_SPM_STATE_CONTROL_0(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SPM_STATE_CONTROL_0, *SPM_CFG_SPM_STATE_CONTROL_0);

    /* RISCV Ext SLP Request Always On & CMSYS Ext SLP Request SW default On*/
    *SPM_CFG_RISCV_REQ_EXT_SLP |= 0x1;
    *SPM_CFG_CMSYS_REQ_EXT_SLP |= 0x1;
    printk("[SLP] *SPM_CFG_RISCV_REQ_EXT_SLP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_RISCV_REQ_EXT_SLP, *SPM_CFG_RISCV_REQ_EXT_SLP);
    printk("[SLP] *SPM_CFG_CMSYS_REQ_EXT_SLP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_CMSYS_REQ_EXT_SLP, *SPM_CFG_CMSYS_REQ_EXT_SLP);

    /* MTCMOS SW Default Status  */
    spm_mtcmos_default_init();
    printk("[SLP][SW Default Status] PWR_STATUS is 0x%08X\r\n", *SPM_CFG_PWR_STATUS_2ND);

    spm_init();

#if 0

    /* JTAG GPIO */
    // hal_pinmux_set_function(0, 2);
    // hal_pinmux_set_function(1, 2);
    spm_unmask_wakeup_source(SPM_CFG_CONN_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_ALL);

    // *RISCV_DEEP_SLEEP = 0xFFFFFFFF;
    printk("*RISCV_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)RISCV_DEEP_SLEEP, *RISCV_DEEP_SLEEP);

    // *SPM_CFG_SEQUENCER_32K_REG_0 = 0x00001;
    printk("[SLP] *SPM_CFG_SEQUENCER_32K_REG_0(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SEQUENCER_32K_REG_0, *SPM_CFG_SEQUENCER_32K_REG_0);

    // *SPM_CFG_IGNORE_CPU_ACTIVE = 0x01000000;    //IGNORE IBEX/INFRA/CONN ACTIVE
    printk("[SLP] SPM_CFG_IGNORE_CPU_ACTIVE=0x%08x\r\n", *SPM_CFG_IGNORE_CPU_ACTIVE);
#endif

    /* Disable SPM IRQ */
    hal_nvic_disable_irq(SPM_IRQn);

    sleep_management_init();

    sleep_manager_handle = hal_sleep_manager_set_sleep_handle("slp");
    // hal_sleep_manager_lock_sleep(sleep_manager_handle);

    sleep_manager_extslp_handle = hal_sleep_manager_set_extslp_handle("slp");
    // hal_sleep_manager_lock_extslp(sleep_manager_extslp_handle);

    sleep_manager_idle_handle = hal_sleep_manager_set_idle_handle("slp");
    // hal_sleep_manager_lock_idle(sleep_manager_idle_handle);

#ifdef SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
    log_hal_msgid_info("Disable CM33 Enter Sleep\n", 0);
#endif

#ifdef SPM_DVT_TEST
    /* Ask module owner to turn on MTCMOS by their need after bring-up */
    spm_fpga_mtcmos_all_on();
    printk("[SLP] SPM MTCMOS PWR STATUS: 0x%x\r\n", *SPM_TOP_PWR_STATUS);
#endif

    if (hal_gpt_sw_get_timer(&sleep_sw_gpt_handle) != HAL_GPT_STATUS_OK) {
        log_hal_error("ERROR : Sleep GPT Init Fail");
        return HAL_SLEEP_MANAGER_ERROR;
    }

#ifdef HAL_RTC_MODULE_ENABLED
    ret_status = hal_rtc_enable_time();
    printk("[rtc][enable]ret_status=%d \r\n", ret_status);
    if (hal_rtc_alarm_get_handle(&sleep_sw_gpt_handle_rtc) != HAL_RTC_STATUS_OK) {
        log_hal_error("ERROR : Extended Sleep RTC Init Fail");
        return HAL_SLEEP_MANAGER_ERROR;
    }
#endif

    return HAL_SLEEP_MANAGER_OK;
}

#if KERNELVERSION == 0x3030000
static int air_sleep_manager_init(const struct device *dev)
{
    ARG_UNUSED(dev);
#elif KERNELVERSION >= 0x3070000
static int air_sleep_manager_init(void)
{
#else
#error "Unkown supported kernel version"
#endif

    return hal_sleep_manager_init();
}

SYS_INIT(air_sleep_manager_init, CONFIG_SLEEP_MANAGER_INIT_LEVEL, CONFIG_SLEEP_MANAGER_INIT_PRIORITY);

#endif /* HAL_SLEEP_MANAGER_ENABLED */

uint32_t irq_mask_a, irq_mask_b;

#ifdef HAL_SLEEP_MANAGER_ENABLED
#if defined (CONFIG_PM) && defined (CONFIG_PM_POLICY_CUSTOM)
ATTR_TEXT_IN_TCM_RETENTION const struct pm_state_info *pm_policy_next_state(uint8_t cpu, int32_t ticks){

    int32_t cyc = -1;
    const struct pm_state_info *cpu_states;
    uint8_t num_cpu_states = pm_state_cpu_get_all(_current_cpu->id, &cpu_states);
    //const struct pm_state_info *idle_state = &cpu_states[0]; /* PM_STATE_RUNTIME_IDLE */
    //const struct pm_state_info *sleep_state = &cpu_states[num_cpu_states-1]; /* PM_STATE_SUSPEND_TO_RAM */


    //printk("[SLP] num_cpu_states=%d\r\n", num_cpu_states);
    //printk("[SLP] idle_state->state=%d\r\n", idle_state->state);
    //printk("[SLP] idle_state->min_residency_us=%d\r\n", idle_state->min_residency_us);
    //printk("[SLP] idle_state->exit_latency_us=%d\r\n", idle_state->exit_latency_us);
    //printk("[SLP] sleep_state->state=%d\r\n", sleep_state->state);
    //printk("[SLP] sleep_state->min_residency_us=%d\r\n", sleep_state->min_residency_us);
    //printk("[SLP] sleep_state->exit_latency_us=%d\r\n", sleep_state->exit_latency_us);
    //printk("[SLP] idle_exit_latency_us=%u\r\n", idle_exit_latency_us);
    //printk("[SLP] sleep_exit_latency_us=%u\r\n", sleep_exit_latency_us);
    //printk("[SLP] ticks=%d\r\n", ticks);


    /* Check IRQ status. if IRQ is pending, return PM_STATE_ACTIVE.
     * Check lock tickless idle status.
     */
    /* sleep_management_check_idle_locks need to change APIs. */
    hal_nvic_clear_pending_irq(SPM_IRQn);
    if( (hal_sleep_manager_is_idle_locked() == true
        || hal_sleep_manager_is_sleep_handle_alive(SLEEP_LOCK_BT_CONTROLLER) == true
        ||  hal_sleep_manager_is_sleep_handle_alive(SLEEP_LOCK_USB) == true)){
        
        return NULL;

    } else if(hal_nvic_is_irq_pending() == true){
        hal_nvic_get_pending_irq_by_mask( &irq_mask_a, &irq_mask_b);
        //printk("[SLP][next state][IRQ Pending] irq_mask[0:31]=0x%08x, irq_mask[32:63]=0x%08x\r\n", irq_mask_a, irq_mask_b);
        // printk("[SLP][IRQ Pending] irq_mask[0:31]=0x%08x, irq_mask[32:63]=0x%08x\r\n", irq_mask_a, irq_mask_b);

        return NULL;
    }

    if (ticks != K_TICKS_FOREVER) {
		cyc = k_ticks_to_cyc_ceil32(ticks);
	}
    //printk("[SLP] current_cyc=%d\r\n", cyc);
    //printk("[SLP] next_event_cyc=%d\r\n", next_event_cyc);

    if (next_event_cyc >= 0) {
		uint32_t cyc_curr = k_cycle_get_32();
		//int64_t cyc_evt = next_event_cyc - cyc_curr;
        int32_t cyc_evt = next_event_cyc - cyc_curr;

        //printk("[SLP] cyc_curr=%d\r\n", cyc_curr);
        //printk("[SLP] cyc_evt=%d\r\n", cyc_evt);

		/* event happening after cycle counter max value, pad */
		if (next_event_cyc <= cyc_curr) {
			cyc_evt += UINT32_MAX;
		}

		if (cyc_evt > 0) {
			/* if there's no system wakeup event always wins,
			 * otherwise, who comes earlier wins
			 */
			if (cyc < 0) {
				cyc = cyc_evt;
			} else {
				cyc = MIN(cyc, cyc_evt);
			}
		}
	}

    /* Check lock sleep status & sleep time > exit_latency_us. if user lock sleep, return PM_STATE_RUNTIME_IDLE.
     */
    //printk("[SLP] idle_exit_latency_us=%u\r\n", idle_exit_latency_us);
    //printk("[SLP] sleep_exit_latency_us=%u\r\n", sleep_exit_latency_us);
    //printk("[SLP] final_cyc=%d\r\n", cyc);
    if( cyc <= idle_exit_latency_us ){

        //printk("[SLP] final_cyc=%d, idle_exit_latency_us=%d\r\n", cyc, idle_exit_latency_us);
        //printk("[SLP] enter 0\r\n");
        return NULL;
    }else if (hal_sleep_manager_is_sleep_locked() == true || (cyc <= sleep_exit_latency_us) ){

        //printk("[SLP] final_cyc=%d, sleep_exit_latency_us=%d\r\n", cyc, sleep_exit_latency_us);
        //printk("[SLP] enter %d\r\n",&cpu_states[0]);
        /* Enter Tickless IDLE Mode */
        tickless_sleep_flag = false;

        return &cpu_states[0];
    }else{

        //printk("[SLP] enter %d\r\n",cpu_states[num_cpu_states-1]);
        /* Enter Tickless Sleep Mode */
        tickless_sleep_flag = true;

        return &cpu_states[num_cpu_states-1];
    }
}
#endif /* CONFIG_PM && CONFIG_PM_POLICY_CUSTOM*/
#else
const struct pm_state_info *pm_policy_next_state(uint8_t cpu, int32_t ticks){return NULL;}
#endif /* HAL_SLEEP_MANAGER_ENABLED */