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

#if IS_ENABLED(CONFIG_AIR_RISCV_BUILD)

#include "air_chip.h"
#include "hal_riscv_ctl.h"
#include "hal_spm.h"
#include "hal_nvic.h"
#include "hal_cache.h"
#include "hal_clock.h"
#include "hal_platform.h"
#include "hal_core_status.h"

/* dynamic address from symbols in memory map */
extern const riscv_scenario_info_t __riscv_firmware_scenario_start[];
extern uint32_t __riscv_firmware_scenario_num;

/* special way for using symbols in memory map */
#define RISCV_FIRMWARE_SCENARIO             (const riscv_scenario_info_t*)(__riscv_firmware_scenario_start)
#define RISCV_FIRMWARE_SCENARIO_NUM         (uint32_t)(&__riscv_firmware_scenario_num)

bool riscv_is_start = false;

bool hal_riscv_stop(void)
{
    uint32_t irq_mask;

    hal_nvic_save_and_set_interrupt_mask(&irq_mask);
    if (!riscv_is_start)
    {
        hal_nvic_restore_interrupt_mask(irq_mask);
        return false;
    }
    riscv_is_start = false;
    hal_nvic_restore_interrupt_mask(irq_mask);

    /* Hold reset */
    RGU_MISC->sw_rst0.word = 0x11b;

#if defined(AIR_SOC_CROSS_CORE_MEMORY_ENABLE)
    hal_core_status_write(HAL_CORE_RISCV, HAL_CORE_OFF);
#endif

    /* power down ram */
    // sysram_riscv_0_sram_power_down();
    // sysram_riscv_1_sram_power_down();
#ifdef HAL_SLEEP_MANAGER_ENABLED
    riscv_sram_all_power_down();
    /* RISCV DEEP SLEEP & FAKE PWR*/
    *SPM_CFG_RISCV_FAKE_PWR = 0x0;
    /* mask all riscv wakeup source */
    *SPM_CFG_RISCV_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    /* RISCV Ext SLP Request On */
    *SPM_CFG_RISCV_REQ_EXT_SLP |= 0x1;
    *RISCV_DEEP_SLEEP |= (0x100);
    *SPM_CFG_IGNORE_CPU_ACTIVE |= (1 << 16);
    printk("[SLP][RISCV Stop] *RISCV_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)RISCV_DEEP_SLEEP, *RISCV_DEEP_SLEEP);
    printk("[SLP][RISCV Stop] *SPM_CFG_RISCV_FAKE_PWR(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_RISCV_FAKE_PWR, *SPM_CFG_RISCV_FAKE_PWR);
    printk("[SLP][RISCV Stop] *SPM_CFG_IGNORE_CPU_ACTIVE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_IGNORE_CPU_ACTIVE, *SPM_CFG_IGNORE_CPU_ACTIVE);
    printk("[SLP][RISCV Stop] *SPM_CFG_RISCV_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_RISCV_WAKEUP_SOURCE_MASK, *SPM_CFG_RISCV_WAKEUP_SOURCE_MASK);
    printk("[SLP][RISCV Stop] *SPM_CFG_RISCV_REQ_EXT_SLP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_RISCV_REQ_EXT_SLP, *SPM_CFG_RISCV_REQ_EXT_SLP);
#endif

    return true;
}

bool hal_riscv_start(uint32_t scenario)
{
    uint32_t irq_mask;

    __ASSERT(RISCV_FIRMWARE_SCENARIO_NUM > scenario, "input scenario(%u) more than maximum(%u)\r\n", scenario, RISCV_FIRMWARE_SCENARIO_NUM);

    if(RISCV_FIRMWARE_SCENARIO_NUM > scenario){
        hal_nvic_save_and_set_interrupt_mask(&irq_mask);
        if (riscv_is_start)
        {
            hal_nvic_restore_interrupt_mask(irq_mask);
            return false;
        }
        riscv_is_start = true;
        hal_nvic_restore_interrupt_mask(irq_mask);

        /* Hold reset */
        RGU_MISC->sw_rst0.word = 0x11b;

        /* TODO: power on ram by length(for example only 16K) */
        // sysram_riscv_0_sram_power_on();
        // sysram_riscv_1_sram_power_on();
#ifdef HAL_SLEEP_MANAGER_ENABLED
        /* RISCV DEEP SLEEP & FAKE PWR*/
        *SPM_CFG_RISCV_FAKE_PWR = 0x1;
        /* No need to restore riscv wakeup source mask */
        /* RISCV Ext SLP Request On */
        *SPM_CFG_RISCV_REQ_EXT_SLP |= 0x1;
        *RISCV_DEEP_SLEEP &= ~(0x100);
        *SPM_CFG_IGNORE_CPU_ACTIVE &= ~(1 << 16);

        printk("[SLP][RISCV Stop] *RISCV_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)RISCV_DEEP_SLEEP, *RISCV_DEEP_SLEEP);
        printk("[SLP][RISCV Stop] *SPM_CFG_RISCV_FAKE_PWR(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_RISCV_FAKE_PWR, *SPM_CFG_RISCV_FAKE_PWR);
        printk("[SLP][RISCV Stop] *SPM_CFG_IGNORE_CPU_ACTIVE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_IGNORE_CPU_ACTIVE, *SPM_CFG_IGNORE_CPU_ACTIVE);
        printk("[SLP][RISCV Stop] *SPM_CFG_RISCV_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_RISCV_WAKEUP_SOURCE_MASK, *SPM_CFG_RISCV_WAKEUP_SOURCE_MASK);
        printk("[SLP][RISCV Stop] *SPM_CFG_RISCV_REQ_EXT_SLP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_RISCV_REQ_EXT_SLP, *SPM_CFG_RISCV_REQ_EXT_SLP);

        riscv_sram_all_power_on();
        printk("[RISCV] power on ram");
#endif
        hal_clock_status_t op_clock = hal_clock_enable(HAL_CLOCK_CG_IBEX);
        bool riscv_clock_status = hal_clock_is_enabled(HAL_CLOCK_CG_IBEX);
        printk("[RISCV] enable clock with result %d and confirmed status %d", op_clock, riscv_clock_status);

        const riscv_scenario_info_t *p_scenario = \
            RISCV_FIRMWARE_SCENARIO + scenario;
        /* Put C code to Ibex SRAM */
        printk("[RISCV] copy data from 0x%08X to 0x%08X with length 0x%08X\r\n",
            (unsigned int)p_scenario->firmware_load_addr,
            (unsigned int)RISCV_SRAM_BASE,
            (unsigned int)p_scenario->firmware_len
        );
        memcpy((void*)RISCV_SRAM_BASE, (void*)p_scenario->firmware_load_addr, p_scenario->firmware_len);
        __ISB();
        uint32_t cmp_len = p_scenario->firmware_len;
        volatile char *src = (volatile char*)(p_scenario->firmware_load_addr);
        volatile char *dest = (volatile char*)RISCV_SRAM_BASE;
        int cmp_fail_times = 0;
        while(cmp_len){
            // *dest = *src;
            // __ISB();
            if(*src != *dest){
                printk("[RISCV] src data 0x%02X(0x%08X) != dest data 0x%02X(0x%08X)",
                    *src, (unsigned int)src,
                    *dest, (unsigned int)dest
                );
                cmp_fail_times++;
            }
            cmp_len--;
            src++;
            dest++;
        }
        if(cmp_fail_times){
            printk("[RISCV] compare failed %d times", cmp_fail_times);
        }
        __ASSERT_NO_MSG(cmp_fail_times == 0);

        /* Set boot vector for Ibex */
        MCU_CFG_PRI->riscv_cfg_boot_vector.field.RISCV_BOOT_VECTOR = RISCV_SRAM_BASE;
        MCU_CFG_PRI->riscv_cfg_boot_vector_select.field.RISCV_BOOT_VECTOR_SELECT = 0x1;

        MCU_CFG_PRI->riscv_deep_sleep.word &= ~(0x100);

        /* Release reset */
        RGU_MISC->sw_rst0.word = 0x1b;
        /* Ibex start to run */

#if defined(AIR_SOC_CROSS_CORE_MEMORY_ENABLE)
        hal_core_status_write(HAL_CORE_RISCV, HAL_CORE_STATUS_MAX);
#endif

        return true;
    } else {
        printk("input scenario(%u) more than maximum(%u)\r\n", scenario, RISCV_FIRMWARE_SCENARIO_NUM);
        return false;
    }
}

#include "hal_sw_dma.h"
static void sw_dma_callback(hal_sw_dma_event_t event, void  *user_data)
{  
    // printf("\r\n ---sw_dma_ctrl callback!!!---\r\n");
    //gdma_callback will be triggered when gdma transfers finished.
    if(event == HAL_SW_DMA_EVENT_TRANSACTION_SUCCESS){
        // hal_gdma_stop(HAL_GDMA_CHANNEL0);
        // hal_gdma_deinit(HAL_GDMA_CHANNEL0);
        // printk("\r\n ---sw_dma_ctrl finished!!!---, user data:%x\r\n",user_data);
        riscv_ctl_t *info = (riscv_ctl_t *)user_data;
        info->call_back();
        __ISB();
        // uint32_t cmp_len = info->scenario->firmware_len;
        // volatile char *src = (volatile char*)(info->scenario->firmware_load_addr);
        // volatile char *dest = (volatile char*)RISCV_SRAM_BASE;
        // int cmp_fail_times = 0;
        // while(cmp_len){
        // // *dest = *src;
        // // __ISB();
        // if(*src != *dest){
        //     printk("[RISCV] src data 0x%02X(0x%08X) != dest data 0x%02X(0x%08X)",
        //         *src, (unsigned int)src,
        //         *dest, (unsigned int)dest
        //     );
        //     cmp_fail_times++;
        // }
        // cmp_len--;
        // src++;
        // dest++;
        // }
        // if(cmp_fail_times){
        //     printk("[RISCV] compare failed %d times", cmp_fail_times);
        // }
        // __ASSERT_NO_MSG(cmp_fail_times == 0);

        /* Set boot vector for Ibex */
        MCU_CFG_PRI->riscv_cfg_boot_vector.field.RISCV_BOOT_VECTOR = RISCV_SRAM_BASE;
        MCU_CFG_PRI->riscv_cfg_boot_vector_select.field.RISCV_BOOT_VECTOR_SELECT = 0x1;
        MCU_CFG_PRI->riscv_deep_sleep.word &= ~(0x100);
        /* Release reset */
        RGU_MISC->sw_rst0.word = 0x1b;
        /* Ibex start to run */

#if defined(AIR_SOC_CROSS_CORE_MEMORY_ENABLE)
        hal_core_status_write(HAL_CORE_RISCV, HAL_CORE_STATUS_MAX);
#endif

    }
    
}
riscv_ctl_t dma_riscv_ctl;
bool hal_riscv_start_async(uint32_t scenario, hal_riscv_ctl_callback_t callback)
{
    uint32_t irq_mask;

    __ASSERT(RISCV_FIRMWARE_SCENARIO_NUM > scenario, "input scenario(%u) more than maximum(%u)\r\n", scenario, RISCV_FIRMWARE_SCENARIO_NUM);
    printk("hal_riscv_start_async api is called, scenario = %d , RISCV_FIRMWARE_SCENARIO_NUM = %d\r\n", scenario,RISCV_FIRMWARE_SCENARIO_NUM );

    if(RISCV_FIRMWARE_SCENARIO_NUM > scenario){
        hal_nvic_save_and_set_interrupt_mask(&irq_mask);
        if (riscv_is_start)
        {
            hal_nvic_restore_interrupt_mask(irq_mask);
            return false;
        }
        riscv_is_start = true;
        hal_nvic_restore_interrupt_mask(irq_mask);

        /* Hold reset */
        RGU_MISC->sw_rst0.word = 0x11b;

        /* TODO: power on ram by length(for example only 16K) */
        // sysram_riscv_0_sram_power_on();
        // sysram_riscv_1_sram_power_on();
#ifdef HAL_SLEEP_MANAGER_ENABLED
        /* RISCV DEEP SLEEP & FAKE PWR*/
        *SPM_CFG_RISCV_FAKE_PWR = 0x1;
        /* No need to restore riscv wakeup source mask */
        /* RISCV Ext SLP Request On */
        *SPM_CFG_RISCV_REQ_EXT_SLP |= 0x1;
        *RISCV_DEEP_SLEEP &= ~(0x100);
        *SPM_CFG_IGNORE_CPU_ACTIVE &= ~(1 << 16);

        printk("[SLP][RISCV Stop] *RISCV_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)RISCV_DEEP_SLEEP, *RISCV_DEEP_SLEEP);
        printk("[SLP][RISCV Stop] *SPM_CFG_RISCV_FAKE_PWR(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_RISCV_FAKE_PWR, *SPM_CFG_RISCV_FAKE_PWR);
        printk("[SLP][RISCV Stop] *SPM_CFG_IGNORE_CPU_ACTIVE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_IGNORE_CPU_ACTIVE, *SPM_CFG_IGNORE_CPU_ACTIVE);
        printk("[SLP][RISCV Stop] *SPM_CFG_RISCV_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_RISCV_WAKEUP_SOURCE_MASK, *SPM_CFG_RISCV_WAKEUP_SOURCE_MASK);
        printk("[SLP][RISCV Stop] *SPM_CFG_RISCV_REQ_EXT_SLP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_RISCV_REQ_EXT_SLP, *SPM_CFG_RISCV_REQ_EXT_SLP);

        riscv_sram_all_power_on();
        printk("[RISCV] power on ram");
#endif
        hal_clock_status_t op_clock = hal_clock_enable(HAL_CLOCK_CG_IBEX);
        bool riscv_clock_status = hal_clock_is_enabled(HAL_CLOCK_CG_IBEX);
        printk("[RISCV] enable clock with result %d and confirmed status %d", op_clock, riscv_clock_status);

        const riscv_scenario_info_t *p_scenario = \
            RISCV_FIRMWARE_SCENARIO + scenario;
        /* Put C code to Ibex SRAM */
        printk("[RISCV] copy data from 0x%08X to 0x%08X with length 0x%08X\r\n",
            (unsigned int)p_scenario->firmware_load_addr,
            (unsigned int)RISCV_SRAM_BASE,
            (unsigned int)p_scenario->firmware_len
        );
        dma_riscv_ctl.call_back = (hal_riscv_ctl_callback_t)callback;
        dma_riscv_ctl.scenario  = (riscv_scenario_info_t *)p_scenario;
        hal_sw_dma_config_info_t sw_dma_cfg;
        hal_sw_gdma_status_t status;
        sw_dma_cfg.source_address = (uint32_t)p_scenario->firmware_load_addr;
        sw_dma_cfg.destination_address = (uint32_t)RISCV_SRAM_BASE;
        sw_dma_cfg.length = (uint32_t)p_scenario->firmware_len;
        sw_dma_cfg.func = (hal_sw_dma_callback_t)sw_dma_callback;
        sw_dma_cfg.argument = &dma_riscv_ctl;
        sw_dma_cfg.h_size = HAL_SW_DMA_WORD;
        sw_dma_cfg.dma_type = HAL_SW_DMA_NORMAL_MODE;
        sw_dma_cfg.transfer_type = HAL_SW_DMA_SINGLE_BURST;
        status = hal_sw_gdma_start(&sw_dma_cfg);
        // printk("input dma_riscv_ctl addr:(%x) \r\n", &dma_riscv_ctl);
        // hal_gdma_init(HAL_GDMA_CHANNEL0); // Initialize the GDMA source clock.
        // hal_gdma_register_callback(HAL_GDMA_CHANNEL0, gdma_callback, callback);  // Register user's callback.
        // hal_gdma_start_interrupt(HAL_GDMA_CHANNEL0,  (void*)RISCV_SRAM_BASE, (void*)p_scenario->firmware_load_addr, p_scenario->firmware_len);  //Enable GDMA to start transferring data.

        // memcpy((void*)RISCV_SRAM_BASE, (void*)p_scenario->firmware_load_addr, p_scenario->firmware_len);
        return true;
    } else {
        printk("input scenario(%u) more than maximum(%u)\r\n", scenario, RISCV_FIRMWARE_SCENARIO_NUM);
        return false;
    }
}

#endif /* IS_ENABLED(CONFIG_AIR_RISCV_BUILD) */