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
#include <zephyr/init.h>
#include <zephyr/logging/log.h>

#include "air_chip.h"


#ifdef HAL_MPU_MODULE_ENABLED

#include "hal_mpu.h"
#include "hal_mpu_internal.h"
#if defined(AIR_BTD_IC_PREMIUM_G1)
    extern uint32_t _tcm_text_start;
    extern uint32_t _tcm_text_end;
    extern uint32_t __tcm_text_retention_start;
    extern uint32_t __tcm_text_retention_end;
    /* MAX region number is 16 */
    const hal_mpu_region_config_t mpu_region[] = {
        /* mpu_region_start_address, mpu_region_end_address, mpu_region_access_permission, mpu_subregion_mask, mpu_xn */
#ifdef CONFIG_FLASH_BOOTING
        {(uint32_t) ROM_BASE, (uint32_t)(ROM_BASE + ROM_LENGTH), HAL_MPU_RO_BY_ANY, false}, //Set FLASH region as RO
        {(uint32_t) &_tcm_text_start, (uint32_t) &_tcm_text_end, HAL_MPU_RO_BY_ANY, false}, //TCM code+TCM rodata( non retention part )
        {(uint32_t) &__tcm_text_retention_start, (uint32_t) &__tcm_text_retention_end, HAL_MPU_RO_BY_ANY, false}, //TCM code+TCM rodata( retention part )
#endif
        /* for RAM booting with controller, we need protect less RAM */
        {(uint32_t)0, (uint32_t)TCM_BASE, HAL_MPU_RO_BY_ANY, true},
        {(uint32_t)0, (uint32_t)TCM_BASE, HAL_MPU_RO_BY_ANY, true},
    };

    void __wrap_z_arm_configure_static_mpu_regions(void)
    {
        ;
    }
    void __wrap_z_arm_mpu_init(void)
    {
        ;
    }
#elif defined(AIR_BTD_IC_MANDATORY_G1)
    void __wrap_z_arm_configure_static_mpu_regions(void)
    {
        ;
    }
    void __wrap_z_arm_mpu_init(void)
    {
        ;
    }
#else
    #error "Unkown hardware"
#endif 


#if !defined(AIR_BTD_IC_MANDATORY_G1)
uint32_t get_mpu_region_num(void)
{
    return sizeof(mpu_region)/sizeof(mpu_region[0]);
}

extern uint32_t get_mpu_region_num(void);

#ifdef CONFIG_AIR_BYPASS_FLASH_RETURN_READY_ENABLE
#include <zephyr/device.h>
extern const struct device *__real_z_impl_device_get_binding(const char *name);
ATTR_TEXT_IN_TCM const struct device *__wrap_z_impl_device_get_binding(const char *name)
{
    STRUCT_SECTION_FOREACH_ALTERNATE(ram_device, device, dev) {
        if (z_impl_device_is_ready(dev) && (dev->name == name)) {
            return dev;
        }
    }

    return __real_z_impl_device_get_binding(name);
}

#include "memory_attribute.h"
#include "hal_nvic.h"
#include "hal_gpt.h"
#include "hal_ccni.h"
#include "assert.h"
extern void __ram_assert(const char *expr, const char *file, int line);
extern bool hal_mpu_region_is_enable(hal_mpu_region_t region);
hal_mpu_region_t mpu_flash_protect_region = (hal_mpu_region_t)(sizeof(mpu_region)/sizeof(mpu_region[0]));
ATTR_TEXT_IN_TCM static void air_mpu_flash_access_disable(void)
{
    hal_mpu_region_t region_number;
    region_number = (hal_mpu_region_t)(sizeof(mpu_region)/sizeof(mpu_region[0]));//the last region
    hal_mpu_region_config_t flash_mpu_region = {(uint32_t) ROM_BASE, (uint32_t)(ROM_BASE + ROM_LENGTH), HAL_MPU_RO_BY_ANY, false};

    hal_mpu_disable();
    hal_mpu_region_configure(region_number, &flash_mpu_region);
    hal_mpu_region_enable(region_number);
    hal_mpu_enable();
}

ATTR_TEXT_IN_TCM static void air_mpu_flash_access_enable(void)
{
    hal_mpu_region_t region_number;

    region_number = (hal_mpu_region_t)(sizeof(mpu_region)/sizeof(mpu_region[0]));
    hal_mpu_disable();
    hal_mpu_region_disable(region_number);
    hal_mpu_enable();
}

#ifdef HAL_FLASH_MODULE_ENABLED
extern void Flash_ReturnReady(void);
#endif

#define MAX_IRQ_NEST_DEPTH 16
typedef struct {
    uint32_t irq_num;        // IRQ number
    uint32_t forbid_flash;   // 1: This IRQ is forbidden to access Flash, 0: Allowed
    uint32_t mpu_enabled;    // 1: MPU protection is enabled at this level, 0: Disabled
} irq_stack_entry_t;

ATTR_ZIDATA_IN_TCM_NONE_RETENTION static volatile irq_stack_entry_t irq_stack[MAX_IRQ_NEST_DEPTH];
ATTR_ZIDATA_IN_TCM_NONE_RETENTION static volatile uint32_t irq_stack_top = 0;

// #define AIR_MPU_FLASH_ACCESS_DEBUG_ENABLE
#ifdef AIR_MPU_FLASH_ACCESS_DEBUG_ENABLE
#define air_mfa_log(...)    printk(__VA_ARGS__)
#else
#define air_mfa_log(...)
#endif


ATTR_TEXT_IN_TCM static uint32_t is_ccni_forbid_flash_access(hal_ccni_event_t ccni_event) {
    return (ccni_event == HAL_CCNI_EVENT(0));
}

ATTR_TEXT_IN_TCM static uint32_t is_irq_forbid_flash_access(hal_nvic_irq_t irq_num, hal_ccni_event_t ccni_event) {
    uint32_t forbid = 0;
    if (irq_num == USB_IRQn || irq_num == RISCV_IRQ_GEN_IRQn) {
        if (irq_num == RISCV_IRQ_GEN_IRQn) {
            forbid = is_ccni_forbid_flash_access(ccni_event);
        } else {
            forbid = 1;
        }
    }
    return forbid;
}

ATTR_TEXT_IN_TCM void air_mpu_flash_access_debug_check(hal_nvic_irq_t irq_num, hal_ccni_event_t ccni_event)
{
    if (is_irq_forbid_flash_access(irq_num, ccni_event)) {
        if (!hal_mpu_region_is_enable(mpu_flash_protect_region)) {
            __ram_assert("MPU flash access should not be disable", __FILE__, __LINE__);
        }
    } else {
        if (hal_mpu_region_is_enable(mpu_flash_protect_region)) {
            __ram_assert("MPU flash access should not be enable", __FILE__, __LINE__);
        }
    }
}

ATTR_TEXT_IN_TCM void air_mpu_flash_access_check_entry(hal_nvic_irq_t irq_num, hal_ccni_event_t ccni_event)
{
    uint32_t mask;
    // uint32_t start_count;
    // uint32_t end_count;
    // uint32_t duration_count;
    // hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &start_count);
    hal_nvic_save_and_set_interrupt_mask(&mask);
    uint32_t forbid = is_irq_forbid_flash_access(irq_num, ccni_event);
    if (irq_stack_top >= MAX_IRQ_NEST_DEPTH) {
        __ram_assert("MPU flash access irq stack over flow", __FILE__, __LINE__);
        return;
    }
    // Push current IRQ info onto the stack
    irq_stack[irq_stack_top].irq_num = irq_num;
    irq_stack[irq_stack_top].forbid_flash = forbid;
    irq_stack[irq_stack_top].mpu_enabled = 0;

    if (forbid) {
        // If this IRQ is forbidden to access Flash
        // Enable MPU protection only if previous level did not enable it
        if (irq_stack_top == 0 || irq_stack[irq_stack_top-1].mpu_enabled == 0) {
            air_mfa_log("IRQ%d entry1, access flash DISABLE, irq_stack_top=%d", irq_num, irq_stack_top);
            air_mpu_flash_access_disable();
        }
        irq_stack[irq_stack_top].mpu_enabled = 1;
    } else {
        // If this IRQ is allowed to access Flash
        // If previous level had MPU protection, disable it temporarily
        if (irq_stack_top > 0 && irq_stack[irq_stack_top-1].mpu_enabled == 1) {
            air_mpu_flash_access_enable();
            air_mfa_log("IRQ%d entry2, access flash ENABLE , irq_stack_top=%d", irq_num, irq_stack_top);
        }
        #if defined(HAL_FLASH_MODULE_ENABLED)
        Flash_ReturnReady();
        #endif
    }
    irq_stack_top++;
    air_mpu_flash_access_debug_check(irq_num, ccni_event);
    hal_nvic_restore_interrupt_mask(mask);
    // hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &end_count);
    // hal_gpt_get_duration_count(start_count, end_count, &duration_count);
    // printk("air_mpu_flash_access_check_entry disable irq:%dus", duration_count);

}


ATTR_TEXT_IN_TCM void air_mpu_flash_access_check_exit(hal_nvic_irq_t irq_num)
{
    uint32_t mask;
    // uint32_t start_count;
    // uint32_t end_count;
    // uint32_t duration_count;
    // hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &start_count);

    hal_nvic_save_and_set_interrupt_mask(&mask);
    irq_stack_top--;
    uint32_t forbid = irq_stack[irq_stack_top].forbid_flash;
    uint32_t mpu_enabled = irq_stack[irq_stack_top].mpu_enabled;

    if (forbid && mpu_enabled) {
        // Exiting a forbidden IRQ that had MPU protection enabled
        // Disable MPU protection
        air_mfa_log("IRQ%d exit0, access flash ENABLE , irq_stack_top=%d", irq_num, irq_stack_top);
        air_mpu_flash_access_enable();
        // If previous level also needs MPU protection, re-enable it
        if (irq_stack_top > 0 && irq_stack[irq_stack_top-1].forbid_flash) {
            air_mfa_log("IRQ%d exit1 , access flash DISABLE, irq_stack_top=%d", irq_num, irq_stack_top);
            air_mpu_flash_access_disable();
            irq_stack[irq_stack_top-1].mpu_enabled = 1;
        }
    } else if (!forbid) {
        // Exiting an allowed IRQ
        // If previous level needs MPU protection, re-enable it
        if (irq_stack_top > 0 && irq_stack[irq_stack_top-1].forbid_flash) {
            air_mfa_log("IRQ%d exit2 , access flash DISABLE, irq_stack_top=%d", irq_num, irq_stack_top);
            air_mpu_flash_access_disable();
            irq_stack[irq_stack_top-1].mpu_enabled = 1;
        }
    }
    hal_nvic_restore_interrupt_mask(mask);
    // hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &end_count);
    // hal_gpt_get_duration_count(start_count, end_count, &duration_count);
    // printk("air_mpu_flash_access_check_exit disable irq:%dus", duration_count);

}

static uint32_t mpu_flash_access_enable_count_with_flash_suspend = 0;
ATTR_TEXT_IN_TCM void air_mpu_flash_access_enable_with_flash_suspend(void)
{
#ifdef HAL_FLASH_MODULE_ENABLED
    Flash_ReturnReady();
#endif
    if (mpu_flash_access_enable_count_with_flash_suspend == 0) {
        air_mpu_flash_access_enable();
    }
    air_mfa_log("flash access enable :%d caller:0x%x", mpu_flash_access_enable_count_with_flash_suspend, __builtin_return_address(0));
    __disable_irq();
    mpu_flash_access_enable_count_with_flash_suspend++;
    __enable_irq();
}

ATTR_TEXT_IN_TCM void air_mpu_flash_access_disable_after_flash_suspend(void)
{
    __disable_irq();
    mpu_flash_access_enable_count_with_flash_suspend--;
    __enable_irq();
    air_mfa_log("flash access disable :%d caller:0x%x", mpu_flash_access_enable_count_with_flash_suspend, __builtin_return_address(0));
    if (mpu_flash_access_enable_count_with_flash_suspend == 0) {
        air_mpu_flash_access_disable();
    }
}
#endif

#if KERNELVERSION == 0x3030000
static int air_mpu_init(const struct device *dev)
{
    ARG_UNUSED(dev);
#elif KERNELVERSION >= 0x3070000
static int air_mpu_init(void)
{
#else
#error "Unkown supported kernel version"
#endif

    hal_mpu_region_t region, region_number;

    hal_mpu_config_t mpu_config = {
        /* PRIVDEFENA, HFNMIENA */
        true, true
    };

    region_number = (hal_mpu_region_t)get_mpu_region_num();

    hal_mpu_init(&mpu_config);
    for (region = HAL_MPU_REGION_0; region < region_number; region++) {

#if defined(AIR_BTD_IC_PREMIUM_G1)
        printk("mpu region %d, [0x%08X, 0x%08X) with permission(%d), XN: %d\r\n",\
            region,\
            mpu_region[region].mpu_region_address,\
            mpu_region[region].mpu_region_end_address,\
            mpu_region[region].mpu_region_access_permission,\
            mpu_region[region].mpu_xn);
        hal_mpu_region_configure(region, &mpu_region[region]);
#else
    #error "Unkown hardware"
#endif
        hal_mpu_region_enable(region);
    }
    /* make sure unused regions are disabled */
    for (; region < HAL_MPU_REGION_MAX; region++) {
        hal_mpu_region_disable(region);
    }
    hal_mpu_enable();
    return 0;
}

/* If the CONFIG_INIT_STACKS feature is turned on,
 * it will actively write some tags to the end of the main thread stack.
 * In order to avoid blocking such allowed writing,
 * put the init of the mpu at the end.
 */
SYS_INIT(air_mpu_init, CONFIG_MPU_INIT_LEVEL, CONFIG_MPU_INIT_PRIORITY);

/* MPU Setting for AIR_BTD_IC_MANDATORY_G1 not ready now */
#endif /* !defined(AIR_BTD_IC_MANDATORY_G1) */

#endif /* HAL_MPU_MODULE_ENABLED */
