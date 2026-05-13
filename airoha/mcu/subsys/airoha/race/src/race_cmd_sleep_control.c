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
#ifdef AIR_BTD_IC_PREMIUM_G1
#include "race_cmd_sleep_control.h"
#include <zephyr/logging/log.h>

#ifdef RACE_SLEEP_CONTROL_ENABLE

#ifdef HAL_SLEEP_MANAGER_ENABLED
#include "hal_spm.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_internal.h"
#include "hal_rtc_internal.h"
#include "hal_clock_internal.h"
#include "memory_attribute.h"
#include "autoconf.h"
#include "hal_deep_sleep.h"
#include "hal_pmu.h"
#include "hal_nvic.h"
#include "hal_gpio.h"
#include "hal_gpio_internal.h"
#include "hal_platform.h"

/* SLEEP CONTROL RACE CMD */
enum {
    SLEEP_CONTROL_UNLOCK_SLP = 0,              /* CMD: 05 5A 03 00 20 02 00 */
    SLEEP_CONTROL_LOCK_SLP,                    /* CMD: 05 5A 03 00 20 02 01 */
    SLEEP_CONTROL_UNLOCK_EXT_SLP,              /* CMD: 05 5A 03 00 20 02 02 */
    SLEEP_CONTROL_LOCK_EXT_SLP,                /* CMD: 05 5A 03 00 20 02 03 */
    SLEEP_CONTROL_ENTER_SLP,                   /* CMD: 05 5A 03 00 20 02 04 */
    SLEEP_CONTROL_ENTER_EXT_SLP,               /* CMD: 05 5A 03 00 20 02 05 */
    SLEEP_CONTROL_MTCMOS_CTRL,                 /* CMD: 05 5A 05 00 20 02 06 XX XX */
    SLEEP_CONTROL_DUMP_LOCK_SLP_STATUS,        /* CMD: 05 5A 03 00 20 02 07 */
    SLEEP_CONTROL_DUMP_LOCK_EXT_SLP_STATUS,    /* CMD: 05 5A 03 00 20 02 08 */
    SLEEP_CONTROL_SET_SPM_DEBUG_IO,            /* CMD: 05 5A 07 00 20 02 09 XX XX XX XX */
    SLEEP_CONTROL_SET_GPIO,                    /* CMD: 05 5A 05 00 20 02 0A XX XX */
    SLEEP_CONTROL_DEBUG_TEST,                  /* CMD: 05 5A 03 00 20 02 0B */
    SLEEP_CONTROL_ENTER_COREMARK,              /* CMD: 05 5A 03 00 20 02 0C */
    SLEEP_CONTROL_ENTER_DEEPSLEEP,             /* CMD: 05 5A 03 00 20 02 0D */
    SLEEP_CONTROL_UNLOCK_IDLE,                 /* CMD: 05 5A 03 00 20 02 0E */
    SLEEP_CONTROL_LOCK_IDLE,                   /* CMD: 05 5A 03 00 20 02 0F */
    SLEEP_CONTROL_DUMP_LOCK_IDLE_STATUS,       /* CMD: 05 5A 03 00 20 02 10 */
    SLEEP_CONTROL_CM33_WFI_SIGNAL,             /* CMD: 05 5A 03 00 20 02 11 */
    SLEEP_CONTROL_RISCV_WFI_SIGNAL,            /* CMD: 05 5A 03 00 20 02 12 */
    SLEEP_CONTROL_TX_RX_SIGNAL,                /* CMD: 05 5A 03 00 20 02 13 */
    SLEEP_CONTROL_MTCMOS_STATUS,               /* CMD: 05 5A 03 00 20 02 14 */
    SLEEP_CONTROL_FORCE_HANDLE_LOCK_SLP,       /* CMD: 05 5A 04 00 20 02 15 XX */
    SLEEP_CONTROL_FORCE_HANDLE_UNLOCK_SLP,     /* CMD: 05 5A 04 00 20 02 16 XX */
    SLEEP_CONTROL_FORCE_HANDLE_LOCK_EXT_SLP,   /* CMD: 05 5A 04 00 20 02 17 XX */
    SLEEP_CONTROL_FORCE_HANDLE_UNLOCK_EXT_SLP, /* CMD: 05 5A 04 00 20 02 18 XX */
    SLEEP_CONTROL_FORCE_HANDLE_LOCK_IDLE,      /* CMD: 05 5A 04 00 20 02 19 XX */
    SLEEP_CONTROL_FORCE_HANDLE_UNLOCK_IDLE,    /* CMD: 05 5A 04 00 20 02 1A XX */
    SLEEP_CONTROL_SLP_WAKEUP_DUMP,             /* CMD: 05 5A 04 00 20 02 1B XX */
    SLEEP_CONTROL_MEMORY_STATUS,               /* CMD: 05 5A 03 00 20 02 1C */
    SLEEP_CONTROL_SLP_FORCE_ON,                /* CMD: 05 5A 05 00 20 02 1D XX XX */
    SLEEP_CONTROL_FORCE_ON_PD                  /* CMD: 05 5A 05 00 20 02 1E XX XX */
};

#ifdef DVT_CACHE_MEMORY_KEEP
#include "hal_cache.h"

uint32_t non_cached_addr = 0x24060000;
uint32_t cached_addr = 0x04060000;

#define CACHED_DATA               *((volatile uint32_t *)cached_addr)
#define NON_CACHED_DATA           *((volatile uint32_t *)non_cached_addr)

#endif /* DVT_CACHE_MEMORY_KEEP */

extern void pmu_rg_dump(void);

#define AO_BACKUP_RESTORE_TABLE
void ao_backup_restore_regitster_dvt(){

    // printk("enter AO BACKUP RESTORE\r\n");
#ifdef AO_BACKUP_RESTORE_TABLE

    ao_backup_format_table_t top_misc_register, cksys, cksys_xo_clk, mixed, cksys_bus_clk, gpio, eint, spm, spm_cfg, mcu_cfg, uart0, uart1, uart2;

    top_misc_register.module_base_addr = 0x42010000;
    top_misc_register.module_end_addr = 0x42010024;
    top_misc_register.module_backup_enable = 0x1;

    cksys.module_base_addr = 0x42030000;
    cksys.module_end_addr = 0x4203005C;
    cksys.module_backup_enable = 0x1;

    cksys_xo_clk.module_base_addr = 0x42040000;
    cksys_xo_clk.module_end_addr = 0x4204001C;
    cksys_xo_clk.module_backup_enable = 0x1;

    mixed.module_base_addr = 0x42050000;
    mixed.module_end_addr = 0x4205001C;
    mixed.module_backup_enable = 0x1;

    cksys_bus_clk.module_base_addr = 0x422D0000;
    cksys_bus_clk.module_end_addr = 0x422D0028;
    cksys_bus_clk.module_backup_enable = 0x1;

    gpio.module_base_addr = 0x420B0000;
    gpio.module_end_addr = 0x420B0050;
    gpio.module_backup_enable = 0x1;

    eint.module_base_addr = 0x42140000;
    eint.module_end_addr = 0x42140130;
    eint.module_backup_enable = 0x1;

    spm.module_base_addr = 0x42120000;
    spm.module_end_addr = 0x42120097;
    spm.module_backup_enable = 0x1;

    spm_cfg.module_base_addr = 0x42130000;
    spm_cfg.module_end_addr = 0x421300EB;
    spm_cfg.module_backup_enable = 0x1;

    mcu_cfg.module_base_addr = 0x422E0000;
    mcu_cfg.module_end_addr = 0x422E0018;
    mcu_cfg.module_backup_enable = 0x1;

    uart0.module_base_addr = 0x42240000;
    uart0.module_end_addr = 0x42240044;
    uart0.module_backup_enable = 0x1;

    uart1.module_base_addr = 0x42250000;
    uart1.module_end_addr = 0x42250044;
    uart1.module_backup_enable = 0x1;

    uart2.module_base_addr = 0x42260000;
    uart2.module_end_addr = 0x42260044;
    uart2.module_backup_enable = 0x1;

    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_TOP_MISC, &top_misc_register);
    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_CKSYS, &cksys);
    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_CKSYS_XO_CLK, &cksys_xo_clk);
    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_MIXED, &mixed);
    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_CKSYS_BUS_CLK, &cksys_bus_clk);
    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_GPIO, &gpio);
    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_EINT, &eint);
    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_SPM, &spm);
    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_SPM_CFG, &spm_cfg);
    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_MCU_CFG, &mcu_cfg);
    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_UART_0, &uart0);
    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_UART_1, &uart1);
    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_UART_2, &uart2);

    //sleep_management_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_TOP_MISC, AO_BACKUP_RESTORE_ENABLE);
    //sleep_management_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_TOP_MISC, AO_BACKUP_RESTORE_ENABLE);
    //sleep_management_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_TOP_MISC, AO_BACKUP_RESTORE_ENABLE);

    //sleep_management_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_TOP_MISC, AO_BACKUP_RESTORE_DISABLE);
    //sleep_management_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_TOP_MISC, AO_BACKUP_RESTORE_DISABLE);
    //sleep_management_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_TOP_MISC, AO_BACKUP_RESTORE_DISABLE);
    //sleep_management_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_TOP_MISC, AO_BACKUP_RESTORE_DISABLE);

    //sleep_management_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_MIXED, AO_BACKUP_RESTORE_ENABLE);
    //sleep_management_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_MIXED, AO_BACKUP_RESTORE_ENABLE);
    //sleep_management_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_MIXED, AO_BACKUP_RESTORE_ENABLE);
    //sleep_management_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_MIXED, AO_BACKUP_RESTORE_ENABLE);

#endif /* AO_BACKUP_RESTORE_TABLE */
}

static void race_sleep_control_enter_slp(void)
{
    uint32_t mask, i;
    uint32_t spm_irq;

    // __asm volatile("cpsid i");

    //spm_debug_io(0x43425a44);

    //spm_check_debug_bus();
    printk("Enter Sleep !!!");

    for (i = 0; i < IRQ_NUMBER_MAX; i++) {
        //hal_nvic_disable_irq(i);
        if (hal_nvic_get_pending_irq(i) == 1) {
            // printf("pending_irq:%d\r\n", i);
            hal_nvic_clear_pending_irq(i);
        }
    }

    for (i = 0; i < IRQ_NUMBER_MAX; i++) {
        //hal_nvic_disable_irq(i);
        if (hal_nvic_get_pending_irq(i) == 1) {
            // printf("pending_irq:%d\r\n", i);
            hal_nvic_clear_pending_irq(i);
        }
    }

    *SPM_CFG_IGNORE_CPU_ACTIVE = 0x01010100;    //IGNORE RISCV/INFRA/CONN ACTIVE
    // ao_backup_restore_regitster_dvt();

    // hal_rtc_switch_32k_source(HAL_RTC_OSC32K_EOSC_MODE);
    printk("[SLP][32K] CLK Source=0x%08x\r\n",*(volatile uint32_t*)(0x42105008));

    //hal_nvic_disable_irq(12);

    *SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    *SPM_CFG_INFRA_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    *SPM_CFG_RISCV_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    *SPM_CFG_CONN_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    // *SPM_CFG_CONN_WAKEUP_SOURCE_MASK = 0xFFFFFFFC;

    printk("*SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, *SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK);
    printk("*SPM_CFG_INFRA_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_INFRA_WAKEUP_SOURCE_MASK, *SPM_CFG_INFRA_WAKEUP_SOURCE_MASK);
    printk("*SPM_CFG_RISCV_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_RISCV_WAKEUP_SOURCE_MASK, *SPM_CFG_RISCV_WAKEUP_SOURCE_MASK);
    printk("*SPM_CFG_CONN_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CONN_WAKEUP_SOURCE_MASK, *SPM_CFG_CONN_WAKEUP_SOURCE_MASK);

    //while(1);

    if(*SPM_CFG_SPM_CFG_DUMMY_REG_C == 0x1){
        printk("[SLP] subsys_sram_all_power_down \r\n");
        subsys_sram_all_power_down();
    }
    spm_control_mtcmos_internal(SPM_MTCMOS_AUDIO_SYS, SPM_MTCMOS_PWR_DISABLE);
    spm_control_mtcmos_internal(SPM_MTCMOS_PERISYS, SPM_MTCMOS_PWR_DISABLE);
    spm_control_mtcmos_internal(SPM_MTCMOS_CONN_ZIGBEE, SPM_MTCMOS_PWR_DISABLE);
    spm_control_mtcmos_internal(SPM_MTCMOS_CONN_TOP_OFF, SPM_MTCMOS_PWR_DISABLE);
    printk("[SPM] PWR_STATUS is 0x%08X\r\n", *SPM_CFG_PWR_STATUS_2ND);
    *SPM_TOP_CONN_FAKE_PWR = 0x0;
    printk("*SPM_CFG_IGNORE_CPU_ACTIVE(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_IGNORE_CPU_ACTIVE, *SPM_CFG_IGNORE_CPU_ACTIVE);

    /* RISCV/CMSYS/CONN Ext SLP Flag */
    *SPM_CFG_CMSYS_REQ_EXT_SLP = 0x0;
    *SPM_CFG_RISCV_REQ_EXT_SLP = 0x0;
    *SPM_CFG_CONN_REQ_EXT_SLP = 0x0;
    printk("*SPM_CFG_CMSYS_REQ_EXT_SLP(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CMSYS_REQ_EXT_SLP, *SPM_CFG_CMSYS_REQ_EXT_SLP);
    printk("*SPM_CFG_RISCV_REQ_EXT_SLP(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_RISCV_REQ_EXT_SLP, *SPM_CFG_RISCV_REQ_EXT_SLP);
    printk("*SPM_CFG_CONN_REQ_EXT_SLP(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CONN_REQ_EXT_SLP, *SPM_CFG_CONN_REQ_EXT_SLP);

    /* Lock S1 */
    //*SPM_CFG_SPM_STATE_CONTROL_0 = 0x1;
    /* Lock S3 */
    *SPM_CFG_SPM_STATE_CONTROL_0 = 0x0;
    // printk("*SPM_CFG_SPM_STATE_CONTROL_0(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SPM_STATE_CONTROL_0, *SPM_CFG_SPM_STATE_CONTROL_0);

    /* Debug bus restore */
    *SPM_CFG_SPM_CFG_DUMMY_REG_A = 0x1;
    // printk("*SPM_CFG_SPM_CFG_DUMMY_REG_A(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SPM_CFG_DUMMY_REG_A, *SPM_CFG_SPM_CFG_DUMMY_REG_A);

    /* CMSYS force on */
    //*SPM_CFG_RESOURCE_CONTROL_0 = 0x1;
    // printk("*SPM_CFG_RESOURCE_CONTROL_0(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_RESOURCE_CONTROL_0, *SPM_CFG_RESOURCE_CONTROL_0);

    /* INFRA DEEP SLEEP */
    // *SPM_CFG_PCM_SW_INT_CLEAR_INFRA = 0x1;
    // /* INFRA pwr off requested by SW, flag cleared by SPM */
    // *SPM_CFG_INFRA_DEEP_SLEEP = 0x1;

    /* IBEX DEEP SLEEP */
    *RISCV_DEEP_SLEEP = 0xFFFFFFFF;
    printk("*RISCV_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)RISCV_DEEP_SLEEP, *RISCV_DEEP_SLEEP);

    /* Lock S6 */
    //*SPM_CFG_SPM_STATE_CONTROL_1 = 0x100;
    //*SPM_CFG_SPM_STATE_CONTROL_1 = 0x10000;
    // printk("*SPM_CFG_SPM_STATE_CONTROL_1(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SPM_STATE_CONTROL_1, *SPM_CFG_SPM_STATE_CONTROL_1);

    //*SPM_CFG_SEQUENCER_32K_REG_0 = 0x300; //PMU force on
    // printk("*SPM_CFG_SEQUENCER_32K_REG_0(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SEQUENCER_32K_REG_0, *SPM_CFG_SEQUENCER_32K_REG_0);
    *SPM_CFG_IGNORE_CPU_ACTIVE = 0x01010100;    //IGNORE IBEX/INFRA/CONN ACTIVE
    // printk("*SPM_CFG_IGNORE_CPU_ACTIVE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_IGNORE_CPU_ACTIVE, *SPM_CFG_IGNORE_CPU_ACTIVE);

#if 0
    /* Ridge FMD GPIO setting */
    *(volatile uint32_t*)(0x420B0000) = 0x0;
    *(volatile uint32_t*)(0x420B0004) = 0x0;
    *(volatile uint32_t*)(0x420C0050) = 0x1FE7C3;
    *(volatile uint32_t*)(0x420C0070) = 0x60183C;
    *(volatile uint32_t*)(0x420D0050) = 0x7E6FFF;
    *(volatile uint32_t*)(0x420D0070) = 0x1819000;
    hal_pinmux_set_function(HAL_GPIO_23, GPIO_PMU_MODE3);
    hal_pinmux_set_function(HAL_GPIO_24, GPIO_PMU_MODE3);

    printk("[SLP]*(volatile uint32_t*)(0x420B0000)=0x%08x\r\n", *(volatile uint32_t*)(0x420B0000));
    printk("[SLP]*(volatile uint32_t*)(0x420B0004)=0x%08x\r\n", *(volatile uint32_t*)(0x420B0004));
    printk("[SLP]*(volatile uint32_t*)(0x420C0050)=0x%08x\r\n", *(volatile uint32_t*)(0x420C0050));
    printk("[SLP]*(volatile uint32_t*)(0x420C0070)=0x%08x\r\n", *(volatile uint32_t*)(0x420C0070));
    printk("[SLP]*(volatile uint32_t*)(0x420D0050)=0x%08x\r\n", *(volatile uint32_t*)(0x420D0050));
    printk("[SLP]*(volatile uint32_t*)(0x420D0070)=0x%08x\r\n", *(volatile uint32_t*)(0x420D0070));
#endif

    //hal_sleep_manager_set_sleep_time(5000000); //5s
    // hal_sleep_manager_set_sleep_time_rtc(5000); //5s
    // while(1){

        // printk("[1]*SPM_CFG_INFRA_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_DEEP_SLEEP, *SPM_CFG_INFRA_DEEP_SLEEP);
        // printk("[1]*SPM_TOP_DUMMY_REG_A(0x%08x)=0x%08x\r\n", (uint32_t)SPM_TOP_DUMMY_REG_A, *SPM_TOP_DUMMY_REG_A);
        //printk("[1]*SPM_CFG_INFRA_WAKEUP_EVENT(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_WAKEUP_EVENT, *SPM_CFG_INFRA_WAKEUP_EVENT);
        //printk("[1]*SPM_CFG_PCM_SW_INT_STATE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_PCM_SW_INT_STATE, *SPM_CFG_PCM_SW_INT_STATE);

        //*SPM_CFG_PCM_SW_INT_CLEAR_INFRA = 0x1;
        /* INFRA pwr off requested by SW, flag cleared by SPM */
        //*SPM_CFG_INFRA_DEEP_SLEEP = 0x1;             // INFRA_DEEP_SLEEP=1
        //printk("[1]*SPM_CFG_INFRA_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_DEEP_SLEEP, *SPM_CFG_INFRA_DEEP_SLEEP);
        //hal_gpt_delay_ms(1000);
        //printk("[2]*SPM_CFG_INFRA_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_DEEP_SLEEP, *SPM_CFG_INFRA_DEEP_SLEEP);
        //printk("[2]*SPM_TOP_DUMMY_REG_A(0x%08x)=0x%08x\r\n", (uint32_t)SPM_TOP_DUMMY_REG_A, *SPM_TOP_DUMMY_REG_A);
        //printk("[2]*SPM_CFG_INFRA_WAKEUP_EVENT(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_WAKEUP_EVENT, *SPM_CFG_INFRA_WAKEUP_EVENT);
        //printk("[2]*SPM_CFG_PCM_SW_INT_STATE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_PCM_SW_INT_STATE, *SPM_CFG_PCM_SW_INT_STATE);


        *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND = 0;        //for sleep test, need BT or Audio Control.
        *SPM_TOP_STATE_STATUS = 0xE2;
        printk("SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND(0x%08x)=0x%x \r\n", (uint32_t)SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND, *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND);
        hal_nvic_save_and_set_interrupt_mask(&mask);
        *SPM_TOP_STATE_STATUS = 0xE3;

        //hal_nvic_clear_pending_irq(22); //GPT_TIMER

        __asm volatile("cpsid i");
        printk("[SLP] SPM_CFG_INFRA_IRTX_CONTROL_2[PRDYN][0]= 0x%x", *SPM_CFG_INFRA_IRTX_CONTROL_2);
        printk("[SLP] SPM_CFG_INFRA_IRTX_CONTROL_0[RET2N][0]= 0x%x", *SPM_CFG_INFRA_IRTX_CONTROL_0);
        printk("[SLP] SPM_CFG_PERISYS_USB_CONTROL_2[PRDYN][0]= 0x%x", *SPM_CFG_PERISYS_USB_CONTROL_2);
        printk("[SLP] SPM_CFG_PERISYS_USB_CONTROL_0[RET2N][0]= 0x%x", *SPM_CFG_PERISYS_USB_CONTROL_0);
        printk("[SLP] SPM_CFG_AUDIO_MEMIF_CONTROL_2[PRDYN][0]= 0x%x", *SPM_CFG_AUDIO_MEMIF_CONTROL_2);
        printk("[SLP] SPM_CFG_AUDIO_MEMIF_CONTROL_0[RET2N][0]= 0x%x", *SPM_CFG_AUDIO_MEMIF_CONTROL_0);


        clock_dump_info();
        pmu_rg_dump();

        sleep_management_enter_deep_sleep(HAL_SLEEP_MODE_SLEEP);
        __asm volatile("cpsie i");
        //*SPM_TOP_STATE_STATUS = 0xEE;
        hal_nvic_restore_interrupt_mask(mask);
        //*SPM_TOP_STATE_STATUS = 0xED;

        /* INFRA pwr on requested by SW, flag cleared by SPM */
        //*SPM_CFG_INFRA_WAKEUP_EVENT = 0x1;
        //printk("[2]*SPM_CFG_INFRA_WAKEUP_EVENT(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_WAKEUP_EVENT, *SPM_CFG_INFRA_WAKEUP_EVENT);
       // printk("[2]*SPM_CFG_INFRA_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_DEEP_SLEEP, *SPM_CFG_INFRA_DEEP_SLEEP);
        //hal_gpt_delay_ms(500);
        spm_irq = *SPM_CFG_PCM_SW_INT_STATE;
        if((spm_irq & 0x100) != 0){
            // printk("[spm_irq]*SPM_CFG_INFRA_WAKEUP_EVENT(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_WAKEUP_EVENT, *SPM_CFG_INFRA_WAKEUP_EVENT);
            // printk("[spm_irq]*SPM_TOP_DUMMY_REG_A(0x%08x)=0x%08x\r\n", (uint32_t)SPM_TOP_DUMMY_REG_A, *SPM_TOP_DUMMY_REG_A);
            // printk("[spm_irq]*SPM_CFG_INFRA_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_DEEP_SLEEP, *SPM_CFG_INFRA_DEEP_SLEEP);
            // printk("[spm_irq]*SPM_CFG_PCM_SW_INT_STATE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_PCM_SW_INT_STATE, *SPM_CFG_PCM_SW_INT_STATE);
            *SPM_CFG_PCM_SW_INT_CLEAR_INFRA = 0x1;
        }

        //*SPM_TOP_STATE_STATUS = 0xEF;
        *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND = 0x101;    //for sleep test, need BT or Audio Control.
        //*SPM_TOP_STATE_STATUS = 0xE1;
        // while(1);
    // }
}

static void race_sleep_control_enter_ext_slp(void)
{
    uint32_t mask, i;
    uint32_t spm_irq;

    //spm_debug_io(0x43425a44);

    //spm_check_debug_bus();
    printk("Enter Ext Sleep !!!");

    for (i = 0; i < IRQ_NUMBER_MAX; i++) {
        //hal_nvic_disable_irq(i);
        if (hal_nvic_get_pending_irq(i) == 1) {
            // printf("pending_irq:%d\r\n", i);
            hal_nvic_clear_pending_irq(i);
        }
    }

    // hal_rtc_switch_32k_source(HAL_RTC_OSC32K_XOSC_MODE);
    printk("[SLP][32K] CLK Source=0x%08x\r\n",*(volatile uint32_t*)(0x42105008));

    *SPM_CFG_IGNORE_CPU_ACTIVE = 0x01010100;    //IGNORE RISCV/INFRA/CONN ACTIVE
    // ao_backup_restore_regitster_dvt();

    //hal_nvic_disable_irq(12);

    *SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    *SPM_CFG_INFRA_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    *SPM_CFG_RISCV_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    *SPM_CFG_CONN_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    // *SPM_CFG_CONN_WAKEUP_SOURCE_MASK = 0xFFFFFFFC;

    printk("*SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, *SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK);
    printk("*SPM_CFG_INFRA_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_INFRA_WAKEUP_SOURCE_MASK, *SPM_CFG_INFRA_WAKEUP_SOURCE_MASK);
    printk("*SPM_CFG_RISCV_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_RISCV_WAKEUP_SOURCE_MASK, *SPM_CFG_RISCV_WAKEUP_SOURCE_MASK);
    printk("*SPM_CFG_CONN_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CONN_WAKEUP_SOURCE_MASK, *SPM_CFG_CONN_WAKEUP_SOURCE_MASK);

    if(*SPM_CFG_SPM_CFG_DUMMY_REG_C == 0x1){
        printk("[SLP] subsys_sram_all_power_down \r\n");
        subsys_sram_all_power_down();
    }
    spm_control_mtcmos_internal(SPM_MTCMOS_AUDIO_SYS, SPM_MTCMOS_PWR_DISABLE);
    spm_control_mtcmos_internal(SPM_MTCMOS_PERISYS, SPM_MTCMOS_PWR_DISABLE);
    spm_control_mtcmos_internal(SPM_MTCMOS_CONN_ZIGBEE, SPM_MTCMOS_PWR_DISABLE);
    spm_control_mtcmos_internal(SPM_MTCMOS_CONN_TOP_OFF, SPM_MTCMOS_PWR_DISABLE);
    *SPM_TOP_CONN_FAKE_PWR = 0x0;
    printk("[SPM] PWR_STATUS is 0x%08X\r\n", *SPM_CFG_PWR_STATUS_2ND);

    printk("*SPM_CFG_IGNORE_CPU_ACTIVE(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_IGNORE_CPU_ACTIVE, *SPM_CFG_IGNORE_CPU_ACTIVE);

    /* RISCV/CMSYS/CONN Ext SLP Flag */
    *SPM_CFG_CMSYS_REQ_EXT_SLP = 0xF;
    *SPM_CFG_RISCV_REQ_EXT_SLP = 0xF;
    *SPM_CFG_CONN_REQ_EXT_SLP = 0xF;
    printk("*SPM_CFG_CMSYS_REQ_EXT_SLP(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CMSYS_REQ_EXT_SLP, *SPM_CFG_CMSYS_REQ_EXT_SLP);
    printk("*SPM_CFG_RISCV_REQ_EXT_SLP(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_RISCV_REQ_EXT_SLP, *SPM_CFG_RISCV_REQ_EXT_SLP);
    printk("*SPM_CFG_CONN_REQ_EXT_SLP(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CONN_REQ_EXT_SLP, *SPM_CFG_CONN_REQ_EXT_SLP);

    /* Lock S1 */
    //*SPM_CFG_SPM_STATE_CONTROL_0 = 0x1;
    /* Lock S3 */
    *SPM_CFG_SPM_STATE_CONTROL_0 = 0x0;
    // printk("*SPM_CFG_SPM_STATE_CONTROL_0(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SPM_STATE_CONTROL_0, *SPM_CFG_SPM_STATE_CONTROL_0);

    /* Debug bus restore */
    *SPM_CFG_SPM_CFG_DUMMY_REG_A = 0x1;
    // printk("*SPM_CFG_SPM_CFG_DUMMY_REG_A(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SPM_CFG_DUMMY_REG_A, *SPM_CFG_SPM_CFG_DUMMY_REG_A);

    /* CMSYS force on */
    //*SPM_CFG_RESOURCE_CONTROL_0 = 0x1;
    // printk("*SPM_CFG_RESOURCE_CONTROL_0(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_RESOURCE_CONTROL_0, *SPM_CFG_RESOURCE_CONTROL_0);

    /* INFRA DEEP SLEEP */
    // *SPM_CFG_PCM_SW_INT_CLEAR_INFRA = 0x1;
    // /* INFRA pwr off requested by SW, flag cleared by SPM */
    // *SPM_CFG_INFRA_DEEP_SLEEP = 0x1;

    /* IBEX DEEP SLEEP */
    *RISCV_DEEP_SLEEP = 0xFFFFFFFF;
    printk("*RISCV_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)RISCV_DEEP_SLEEP, *RISCV_DEEP_SLEEP);

    /* Lock S6 */
    //*SPM_CFG_SPM_STATE_CONTROL_1 = 0x100;
    //*SPM_CFG_SPM_STATE_CONTROL_1 = 0x10000;
    // printk("*SPM_CFG_SPM_STATE_CONTROL_1(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SPM_STATE_CONTROL_1, *SPM_CFG_SPM_STATE_CONTROL_1);

    //*SPM_CFG_SEQUENCER_32K_REG_0 = 0x300; //PMU force on
    // printk("*SPM_CFG_SEQUENCER_32K_REG_0(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SEQUENCER_32K_REG_0, *SPM_CFG_SEQUENCER_32K_REG_0);
    *SPM_CFG_IGNORE_CPU_ACTIVE = 0x01010100;    //IGNORE IBEX/INFRA/CONN ACTIVE
    // printk("*SPM_CFG_IGNORE_CPU_ACTIVE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_IGNORE_CPU_ACTIVE, *SPM_CFG_IGNORE_CPU_ACTIVE);

#if 0
    /* Ridge FMD GPIO setting */
    *(volatile uint32_t*)(0x420B0000) = 0x0;
    *(volatile uint32_t*)(0x420B0004) = 0x0;
    *(volatile uint32_t*)(0x420C0050) = 0x1FE7C3;
    *(volatile uint32_t*)(0x420C0070) = 0x60183C;
    *(volatile uint32_t*)(0x420D0050) = 0x7E6FFF;
    *(volatile uint32_t*)(0x420D0070) = 0x1819000;
    hal_pinmux_set_function(HAL_GPIO_23, GPIO_PMU_MODE3);
    hal_pinmux_set_function(HAL_GPIO_24, GPIO_PMU_MODE3);

    printk("[SLP]*(volatile uint32_t*)(0x420B0000)=0x%08x\r\n", *(volatile uint32_t*)(0x420B0000));
    printk("[SLP]*(volatile uint32_t*)(0x420B0004)=0x%08x\r\n", *(volatile uint32_t*)(0x420B0004));
    printk("[SLP]*(volatile uint32_t*)(0x420C0050)=0x%08x\r\n", *(volatile uint32_t*)(0x420C0050));
    printk("[SLP]*(volatile uint32_t*)(0x420C0070)=0x%08x\r\n", *(volatile uint32_t*)(0x420C0070));
    printk("[SLP]*(volatile uint32_t*)(0x420D0050)=0x%08x\r\n", *(volatile uint32_t*)(0x420D0050));
    printk("[SLP]*(volatile uint32_t*)(0x420D0070)=0x%08x\r\n", *(volatile uint32_t*)(0x420D0070));
#endif

    //hal_sleep_manager_set_sleep_time(5000000); //5s
    // hal_sleep_manager_set_sleep_time_rtc(5000); //5s
    // while(1){

        // printk("[1]*SPM_CFG_INFRA_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_DEEP_SLEEP, *SPM_CFG_INFRA_DEEP_SLEEP);
        // printk("[1]*SPM_TOP_DUMMY_REG_A(0x%08x)=0x%08x\r\n", (uint32_t)SPM_TOP_DUMMY_REG_A, *SPM_TOP_DUMMY_REG_A);
        //printk("[1]*SPM_CFG_INFRA_WAKEUP_EVENT(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_WAKEUP_EVENT, *SPM_CFG_INFRA_WAKEUP_EVENT);
        //printk("[1]*SPM_CFG_PCM_SW_INT_STATE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_PCM_SW_INT_STATE, *SPM_CFG_PCM_SW_INT_STATE);

        //*SPM_CFG_PCM_SW_INT_CLEAR_INFRA = 0x1;
        /* INFRA pwr off requested by SW, flag cleared by SPM */
        //*SPM_CFG_INFRA_DEEP_SLEEP = 0x1;             // INFRA_DEEP_SLEEP=1
        //printk("[1]*SPM_CFG_INFRA_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_DEEP_SLEEP, *SPM_CFG_INFRA_DEEP_SLEEP);
        //hal_gpt_delay_ms(1000);
        //printk("[2]*SPM_CFG_INFRA_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_DEEP_SLEEP, *SPM_CFG_INFRA_DEEP_SLEEP);
        //printk("[2]*SPM_TOP_DUMMY_REG_A(0x%08x)=0x%08x\r\n", (uint32_t)SPM_TOP_DUMMY_REG_A, *SPM_TOP_DUMMY_REG_A);
        //printk("[2]*SPM_CFG_INFRA_WAKEUP_EVENT(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_WAKEUP_EVENT, *SPM_CFG_INFRA_WAKEUP_EVENT);
        //printk("[2]*SPM_CFG_PCM_SW_INT_STATE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_PCM_SW_INT_STATE, *SPM_CFG_PCM_SW_INT_STATE);


        *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND = 0;        //for sleep test, need BT or Audio Control.
        // *SPM_TOP_STATE_STATUS = 0xE2;
        printk("SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND(0x%08x)=0x%x \r\n", (uint32_t)SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND, *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND);
        hal_nvic_save_and_set_interrupt_mask(&mask);
        // *SPM_TOP_STATE_STATUS = 0xE3;
        //hal_nvic_clear_pending_irq(22); //GPT_TIMER

        __asm volatile("cpsid i");
        printk("[SLP] SPM_CFG_INFRA_IRTX_CONTROL_2[PRDYN][0]= 0x%x", *SPM_CFG_INFRA_IRTX_CONTROL_2);
        printk("[SLP] SPM_CFG_INFRA_IRTX_CONTROL_0[RET2N][0]= 0x%x", *SPM_CFG_INFRA_IRTX_CONTROL_0);
        printk("[SLP] SPM_CFG_PERISYS_USB_CONTROL_2[PRDYN][0]= 0x%x", *SPM_CFG_PERISYS_USB_CONTROL_2);
        printk("[SLP] SPM_CFG_PERISYS_USB_CONTROL_0[RET2N][0]= 0x%x", *SPM_CFG_PERISYS_USB_CONTROL_0);
        printk("[SLP] SPM_CFG_AUDIO_MEMIF_CONTROL_2[PRDYN][0]= 0x%x", *SPM_CFG_AUDIO_MEMIF_CONTROL_2);
        printk("[SLP] SPM_CFG_AUDIO_MEMIF_CONTROL_0[RET2N][0]= 0x%x", *SPM_CFG_AUDIO_MEMIF_CONTROL_0);

        clock_dump_info();
        pmu_rg_dump();

        sleep_management_enter_deep_sleep(HAL_SLEEP_MODE_SLEEP);
        __asm volatile("cpsie i");
        //*SPM_TOP_STATE_STATUS = 0xEE;
        hal_nvic_restore_interrupt_mask(mask);
        //*SPM_TOP_STATE_STATUS = 0xED;

        /* INFRA pwr on requested by SW, flag cleared by SPM */
        //*SPM_CFG_INFRA_WAKEUP_EVENT = 0x1;
        //printk("[2]*SPM_CFG_INFRA_WAKEUP_EVENT(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_WAKEUP_EVENT, *SPM_CFG_INFRA_WAKEUP_EVENT);
       // printk("[2]*SPM_CFG_INFRA_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_DEEP_SLEEP, *SPM_CFG_INFRA_DEEP_SLEEP);
        //hal_gpt_delay_ms(500);
        spm_irq = *SPM_CFG_PCM_SW_INT_STATE;
        if((spm_irq & 0x100) != 0){
            // printk("[spm_irq]*SPM_CFG_INFRA_WAKEUP_EVENT(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_WAKEUP_EVENT, *SPM_CFG_INFRA_WAKEUP_EVENT);
            // printk("[spm_irq]*SPM_TOP_DUMMY_REG_A(0x%08x)=0x%08x\r\n", (uint32_t)SPM_TOP_DUMMY_REG_A, *SPM_TOP_DUMMY_REG_A);
            // printk("[spm_irq]*SPM_CFG_INFRA_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_DEEP_SLEEP, *SPM_CFG_INFRA_DEEP_SLEEP);
            // printk("[spm_irq]*SPM_CFG_PCM_SW_INT_STATE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_PCM_SW_INT_STATE, *SPM_CFG_PCM_SW_INT_STATE);
            *SPM_CFG_PCM_SW_INT_CLEAR_INFRA = 0x1;
        }

        //*SPM_TOP_STATE_STATUS = 0xEF;
        *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND = 0x101;    //for sleep test, need BT or Audio Control.
        //*SPM_TOP_STATE_STATUS = 0xE1;
        // while(1);
    // }
}


extern ATTR_TEXT_IN_TCM_RETENTION void SF_DAL_DEV_Enter_DPD(void);
static ATTR_TEXT_IN_TCM_RETENTION void race_sleep_control_enter_coremark(void)
{
#if 0
    uint32_t mask, i;
    uint32_t spm_irq;

    //spm_debug_io(0x43425a44);

    //spm_check_debug_bus();
    printk("[SLP] Enter Coremark !!!");

    for (i = 0; i < IRQ_NUMBER_MAX; i++) {
        //hal_nvic_disable_irq(i);
        if (hal_nvic_get_pending_irq(i) == 1) {
            // printf("pending_irq:%d\r\n", i);
            hal_nvic_clear_pending_irq(i);
        }
    }

    // hal_rtc_switch_32k_source(HAL_RTC_OSC32K_XOSC_MODE);
    printk("[SLP][32K] CLK Source=0x%08x\r\n",*(volatile uint32_t*)(0x42105008));

    *SPM_CFG_IGNORE_CPU_ACTIVE = 0;    //IGNORE RISCV/INFRA/CONN ACTIVE
    // ao_backup_restore_regitster_dvt();

    //hal_nvic_disable_irq(12);

    *SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    *SPM_CFG_INFRA_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    *SPM_CFG_RISCV_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    *SPM_CFG_CONN_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    // *SPM_CFG_CONN_WAKEUP_SOURCE_MASK = 0xFFFFFFFC;

    printk("*SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, *SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK);
    printk("*SPM_CFG_INFRA_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_INFRA_WAKEUP_SOURCE_MASK, *SPM_CFG_INFRA_WAKEUP_SOURCE_MASK);
    printk("*SPM_CFG_RISCV_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_RISCV_WAKEUP_SOURCE_MASK, *SPM_CFG_RISCV_WAKEUP_SOURCE_MASK);
    printk("*SPM_CFG_CONN_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CONN_WAKEUP_SOURCE_MASK, *SPM_CFG_CONN_WAKEUP_SOURCE_MASK);

    // if(*SPM_CFG_SPM_CFG_DUMMY_REG_C == 0x1){
        printk("[SLP] subsys_sram_all_power_down \r\n");
        subsys_sram_all_power_down();
    // }
    spm_control_mtcmos_internal(SPM_MTCMOS_AUDIO_SYS, SPM_MTCMOS_PWR_DISABLE);
    spm_control_mtcmos_internal(SPM_MTCMOS_PERISYS, SPM_MTCMOS_PWR_DISABLE);
    spm_control_mtcmos_internal(SPM_MTCMOS_CONN_ZIGBEE, SPM_MTCMOS_PWR_DISABLE);
    spm_control_mtcmos_internal(SPM_MTCMOS_CONN_TOP_OFF, SPM_MTCMOS_PWR_DISABLE);
    *SPM_TOP_CONN_FAKE_PWR = 0x0;
    printk("[SPM] PWR_STATUS is 0x%08X\r\n", *SPM_CFG_PWR_STATUS_2ND);

    printk("*SPM_CFG_IGNORE_CPU_ACTIVE(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_IGNORE_CPU_ACTIVE, *SPM_CFG_IGNORE_CPU_ACTIVE);

    /* RISCV/CMSYS/CONN Ext SLP Flag */
    // *SPM_CFG_CMSYS_REQ_EXT_SLP = 0xF;
    // *SPM_CFG_RISCV_REQ_EXT_SLP = 0xF;
    // *SPM_CFG_CONN_REQ_EXT_SLP = 0xF;
    printk("*SPM_CFG_CMSYS_REQ_EXT_SLP(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CMSYS_REQ_EXT_SLP, *SPM_CFG_CMSYS_REQ_EXT_SLP);
    printk("*SPM_CFG_RISCV_REQ_EXT_SLP(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_RISCV_REQ_EXT_SLP, *SPM_CFG_RISCV_REQ_EXT_SLP);
    printk("*SPM_CFG_CONN_REQ_EXT_SLP(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CONN_REQ_EXT_SLP, *SPM_CFG_CONN_REQ_EXT_SLP);

    /* Lock S1 */
    *SPM_CFG_SPM_STATE_CONTROL_0 = 0x1;
    /* Lock S3 */
    // *SPM_CFG_SPM_STATE_CONTROL_0 = 0x0;
    printk("*SPM_CFG_SPM_STATE_CONTROL_0(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SPM_STATE_CONTROL_0, *SPM_CFG_SPM_STATE_CONTROL_0);

    /* Debug bus restore */
    *SPM_CFG_SPM_CFG_DUMMY_REG_A = 0x1;
    // printk("*SPM_CFG_SPM_CFG_DUMMY_REG_A(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SPM_CFG_DUMMY_REG_A, *SPM_CFG_SPM_CFG_DUMMY_REG_A);

    /* CMSYS force on */
    //*SPM_CFG_RESOURCE_CONTROL_0 = 0x1;
    // printk("*SPM_CFG_RESOURCE_CONTROL_0(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_RESOURCE_CONTROL_0, *SPM_CFG_RESOURCE_CONTROL_0);

    /* INFRA DEEP SLEEP */
    // *SPM_CFG_PCM_SW_INT_CLEAR_INFRA = 0x1;
    // /* INFRA pwr off requested by SW, flag cleared by SPM */
    // *SPM_CFG_INFRA_DEEP_SLEEP = 0x1;

    /* IBEX DEEP SLEEP */
    *RISCV_DEEP_SLEEP = 0xFFFFFFFF;
    printk("*RISCV_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)RISCV_DEEP_SLEEP, *RISCV_DEEP_SLEEP);

    //*SPM_CFG_SEQUENCER_32K_REG_0 = 0x300; //PMU force on
    // printk("*SPM_CFG_SEQUENCER_32K_REG_0(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SEQUENCER_32K_REG_0, *SPM_CFG_SEQUENCER_32K_REG_0);
    *SPM_CFG_IGNORE_CPU_ACTIVE = 0x0;    //IGNORE IBEX/INFRA/CONN ACTIVE
    printk("*SPM_CFG_IGNORE_CPU_ACTIVE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_IGNORE_CPU_ACTIVE, *SPM_CFG_IGNORE_CPU_ACTIVE);

    //hal_sleep_manager_set_sleep_time(5000000); //5s
    // hal_sleep_manager_set_sleep_time_rtc(5000); //5s
    while(1){

        *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND = 0;        //for sleep test, need BT or Audio Control.

        printk("SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND(0x%08x)=0x%x \r\n", (uint32_t)SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND, *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND);
        hal_nvic_save_and_set_interrupt_mask(&mask);

        __asm volatile("cpsid i");
        for (i = 0; i < IRQ_NUMBER_MAX; i++) {
            hal_nvic_disable_irq(i);
            if (hal_nvic_get_pending_irq(i) == 1) {
              // printf("pending_irq:%d\r\n", i);
                hal_nvic_clear_pending_irq(i);
                *SPM_CFG_SW_DBG_STATE_STATUS = i;
            }
        }
        printk("[SLP] SPM_CFG_INFRA_IRTX_CONTROL_2[PRDYN][0]= 0x%x", *SPM_CFG_INFRA_IRTX_CONTROL_2);
        printk("[SLP] SPM_CFG_INFRA_IRTX_CONTROL_0[RET2N][0]= 0x%x", *SPM_CFG_INFRA_IRTX_CONTROL_0);
        printk("[SLP] SPM_CFG_PERISYS_USB_CONTROL_2[PRDYN][0]= 0x%x", *SPM_CFG_PERISYS_USB_CONTROL_2);
        printk("[SLP] SPM_CFG_PERISYS_USB_CONTROL_0[RET2N][0]= 0x%x", *SPM_CFG_PERISYS_USB_CONTROL_0);
        printk("[SLP] SPM_CFG_AUDIO_MEMIF_CONTROL_2[PRDYN][0]= 0x%x", *SPM_CFG_AUDIO_MEMIF_CONTROL_2);
        printk("[SLP] SPM_CFG_AUDIO_MEMIF_CONTROL_0[RET2N][0]= 0x%x", *SPM_CFG_AUDIO_MEMIF_CONTROL_0);

        // clock_cg_init();
        hal_clock_disable(CLK_SPIMST0_SEL);
        hal_clock_disable(CLK_SPIMST1_SEL);
        hal_clock_disable(CLK_SPIMST2_SEL);

        hal_clock_disable(CLK_USB_SEL);
        hal_clock_disable(CLK_I3C_SEL);
        hal_clock_disable(CLK_BT_HOP_SEL);
        hal_clock_disable(HAL_CLOCK_CG_PWM_DMA_0);
        hal_clock_disable(HAL_CLOCK_CG_UART1);
        hal_clock_disable(HAL_CLOCK_CG_UART2);
        hal_clock_disable(HAL_CLOCK_CG_UART_DMA0);
        hal_clock_disable(HAL_CLOCK_CG_UART_DMA1);
        hal_clock_disable(HAL_CLOCK_CG_UART_DMA2);
        hal_clock_disable(HAL_CLOCK_CG_SPIMST0);
        hal_clock_disable(HAL_CLOCK_CG_SPIMST1);
        hal_clock_disable(HAL_CLOCK_CG_SPIMST2);
        hal_clock_disable(HAL_CLOCK_CG_SPIMST0_BUS);
        hal_clock_disable(HAL_CLOCK_CG_SPIMST1_BUS);
        hal_clock_disable(HAL_CLOCK_CG_SPIMST2_BUS);
        hal_clock_disable(HAL_CLOCK_CG_KEY_SCAN_BCLK);
        hal_clock_disable(HAL_CLOCK_CG_KEY_SCAN_F2M);

        hal_clock_disable(HAL_CLOCK_CG_BT_HOP);
        hal_clock_disable(HAL_CLOCK_CG_BT_MAC);
        hal_clock_disable(HAL_CLOCK_CG_BT_MAC_CONN);

        hal_clock_disable(HAL_CLOCK_CG_AUD_INTBUS);
        hal_clock_disable(HAL_CLOCK_CG_AUD_ENGINE);
        hal_clock_disable(HAL_CLOCK_CG_AUD_TEST);

        hal_clock_disable(HAL_CLOCK_CG_ESC);
        hal_clock_disable(HAL_CLOCK_CG_CONN_BUS);
        hal_clock_disable(HAL_CLOCK_CG_SEJ);
        hal_clock_disable(HAL_CLOCK_CG_SEJ);
        hal_clock_disable(HAL_CLOCK_CG_EFUSE);
        hal_clock_disable(HAL_CLOCK_CG_AIO);

        clock_dump_info();
        pmu_rg_dump();

        SF_DAL_DEV_Enter_DPD();
        infra_irtx_sram_power_down();
        *SPM_CFG_INFRA_DEEP_SLEEP = 0x1;
        while(1){
            *SPM_CFG_SW_DBG_STATE_STATUS = 0xEF;
            hal_sleep_manager_enter_sleep_mode(HAL_SLEEP_MODE_IDLE);
            // coremark_main();
            *SPM_CFG_SW_DBG_STATE_STATUS = 0xE6;
        }
        hal_sleep_manager_enter_sleep_mode(HAL_SLEEP_MODE_IDLE);
        __asm volatile("cpsie i");
        //*SPM_TOP_STATE_STATUS = 0xEE;
        hal_nvic_restore_interrupt_mask(mask);
        //*SPM_TOP_STATE_STATUS = 0xED;

        /* INFRA pwr on requested by SW, flag cleared by SPM */
        //*SPM_CFG_INFRA_WAKEUP_EVENT = 0x1;
        //printk("[2]*SPM_CFG_INFRA_WAKEUP_EVENT(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_WAKEUP_EVENT, *SPM_CFG_INFRA_WAKEUP_EVENT);
       // printk("[2]*SPM_CFG_INFRA_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_DEEP_SLEEP, *SPM_CFG_INFRA_DEEP_SLEEP);
        //hal_gpt_delay_ms(500);
        spm_irq = *SPM_CFG_PCM_SW_INT_STATE;
        if((spm_irq & 0x100) != 0){
            // printk("[spm_irq]*SPM_CFG_INFRA_WAKEUP_EVENT(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_WAKEUP_EVENT, *SPM_CFG_INFRA_WAKEUP_EVENT);
            // printk("[spm_irq]*SPM_TOP_DUMMY_REG_A(0x%08x)=0x%08x\r\n", (uint32_t)SPM_TOP_DUMMY_REG_A, *SPM_TOP_DUMMY_REG_A);
            // printk("[spm_irq]*SPM_CFG_INFRA_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_DEEP_SLEEP, *SPM_CFG_INFRA_DEEP_SLEEP);
            // printk("[spm_irq]*SPM_CFG_PCM_SW_INT_STATE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_PCM_SW_INT_STATE, *SPM_CFG_PCM_SW_INT_STATE);
            *SPM_CFG_PCM_SW_INT_CLEAR_INFRA = 0x1;
        }

        //*SPM_TOP_STATE_STATUS = 0xEF;
        *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND = 0x101;    //for sleep test, need BT or Audio Control.
        //*SPM_TOP_STATE_STATUS = 0xE1;
        while(1);
    }
#endif
}

extern uint8_t sleep_manager_handle;
extern uint8_t sleep_manager_extslp_handle;
extern uint8_t sleep_manager_idle_handle;
#endif /* HAL_SLEEP_MANAGER_ENABLED */

void *RACE_CmdHandler_sleep_control(ptr_race_pkt_t pRaceHeaderCmd, uint16_t Length, uint8_t channel_id)
{
    LOG_INF("RACE_CmdHandler_sleep_control, type[0x%X], cmd[0x%X], ch[%d]", 3,
                     pRaceHeaderCmd->hdr.type, pRaceHeaderCmd->hdr.id, channel_id);

    typedef struct {
        uint8_t status;
    } PACKED RACE_SLEEP_CONTROL_RESPONSE;

    RACE_SLEEP_CONTROL_RESPONSE *ptr = RACE_ClaimPacketAppID(pRaceHeaderCmd->hdr.pktId.field.app_id,
                                                              RACE_TYPE_RESPONSE,
                                                              0x0220,
                                                              sizeof(RACE_SLEEP_CONTROL_RESPONSE),
                                                              channel_id);

    if (ptr != NULL) {
        ptr->status = RACE_ERRCODE_SUCCESS;
    } else {
        LOG_ERR("Pack race claim packet failed", 0);
        return NULL;
    }

#ifdef HAL_SLEEP_MANAGER_ENABLED
    uint8_t *pPayload = pRaceHeaderCmd->payload;
    if (pPayload == NULL) {
        LOG_ERR("Lack of RACE CMD payload", 0);
        ptr->status = RACE_ERRCODE_PARAMETER_ERROR;
        return ptr;
    }

    uint16_t cmd_len = pRaceHeaderCmd->hdr.length - 2; /* not count RACE ID */
    switch (pPayload[0]) {
        case SLEEP_CONTROL_UNLOCK_SLP:
            /* CMD: 05 5A 03 00 20 02 00 */
            hal_sleep_manager_unlock_sleep(sleep_manager_handle);
            break;
        case SLEEP_CONTROL_LOCK_SLP:
            /* CMD: 05 5A 03 00 20 02 01 */
            hal_sleep_manager_lock_sleep(sleep_manager_handle);
            break;
        case SLEEP_CONTROL_UNLOCK_EXT_SLP:
            /* CMD: 05 5A 03 00 20 02 02 */
            hal_sleep_manager_unlock_extslp(sleep_manager_extslp_handle);
            break;
        case SLEEP_CONTROL_LOCK_EXT_SLP:
            /* CMD: 05 5A 03 00 20 02 03 */
            hal_sleep_manager_lock_extslp(sleep_manager_extslp_handle);
            break;
        case SLEEP_CONTROL_UNLOCK_IDLE:
            /* CMD: 05 5A 03 00 20 02 0E */
            hal_sleep_manager_unlock_idle(sleep_manager_idle_handle);
            break;
        case SLEEP_CONTROL_LOCK_IDLE:
            /* CMD: 05 5A 03 00 20 02 0F */
            hal_sleep_manager_lock_idle(sleep_manager_idle_handle);
            break;
        case SLEEP_CONTROL_ENTER_SLP:
            /* CMD: 05 5A 03 00 20 02 04 */
            race_sleep_control_enter_slp();
            break;
        case SLEEP_CONTROL_ENTER_EXT_SLP:
            /* CMD: 05 5A 03 00 20 02 05 */
            race_sleep_control_enter_ext_slp();
            break;
        case SLEEP_CONTROL_MTCMOS_CTRL:
            /* CMD: 05 5A 05 00 20 02 06 XX XX */
            if (cmd_len == 3) {
                spm_control_mtcmos(pPayload[1], pPayload[2]);
            } else {
                LOG_ERR("Lack of SLEEP CONTROL arguments", 0);
                ptr->status = RACE_ERRCODE_PARAMETER_ERROR;
            }
            break;
        case SLEEP_CONTROL_DUMP_LOCK_SLP_STATUS:
            /* CMD: 05 5A 03 00 20 02 07 */
            if (hal_sleep_manager_is_sleep_locked()) {
                sleep_management_get_lock_sleep_handle_list();
            } else {
                LOG_INF("Any Sleep Handle not locked", 0);
            }
            break;
        case SLEEP_CONTROL_DUMP_LOCK_EXT_SLP_STATUS:
            /* CMD: 05 5A 03 00 20 02 08 */
            if (hal_sleep_manager_is_extslp_locked()) {
                sleep_management_get_lock_extslp_handle_list();
            } else {
                LOG_INF("Any EXTSLP Handle not locked", 0);
            }
            break;
        case SLEEP_CONTROL_DUMP_LOCK_IDLE_STATUS:
            /* CMD: 05 5A 03 00 20 02 10 */
            if (hal_sleep_manager_is_idle_locked()) {
                sleep_management_get_lock_idle_handle_list();
            } else {
                LOG_INF("Any Idle Handle not locked", 0);
            }
            break;
        case SLEEP_CONTROL_SET_SPM_DEBUG_IO:
            /* CMD: 05 5A 07 00 20 02 09 XX XX XX XX */
            if (cmd_len == 5) {
                unsigned int debug_bus = 0;
                int cmd_index;
                for (cmd_index = 1; cmd_index < 4; cmd_index++) {
                    debug_bus |= pPayload[cmd_index];
                    debug_bus <<= 8;
                }
                debug_bus |= pPayload[cmd_index];
                spm_debug_io(debug_bus);
            } else {
                LOG_ERR("Lack of SLEEP CONTROL arguments", 0);
                ptr->status = RACE_ERRCODE_PARAMETER_ERROR;
            }
            break;
        case SLEEP_CONTROL_SET_GPIO:
            /* CMD: 05 5A 05 00 20 02 0A XX XX */
            if (cmd_len == 3) {
                hal_gpio_init(pPayload[1]);
                hal_pinmux_set_function(pPayload[1], pPayload[2]);
            } else {
                LOG_ERR("Lack of SLEEP CONTROL arguments", 0);
                ptr->status = RACE_ERRCODE_PARAMETER_ERROR;
            }
            break;
        case SLEEP_CONTROL_DEBUG_TEST:
            /* CMD: 05 5A 03 00 20 02 0B */
            spm_check_debug_bus();
            break;
        case SLEEP_CONTROL_ENTER_COREMARK:
            /* CMD: 05 5A 03 00 20 02 0C */
            race_sleep_control_enter_coremark();
            break;

        case SLEEP_CONTROL_ENTER_DEEPSLEEP:
            /* CMD: 05 5A 05 00 20 02 0D */
            // pmu_power_off_sequence(PMU_DEEPSLP);
            // hal_deep_sleep_init();
            // hal_gpt_delay_ms(100);
            // hal_deep_sleep_routine();
            break;

        case SLEEP_CONTROL_CM33_WFI_SIGNAL:
            /* CMD: 05 5A 05 00 20 02 11 XX 0D */
            if (cmd_len == 3) {
                LOG_INF("[SLP] Enable CM33 WFI Signal (GPIO%d)", pPayload[1]);
                *(volatile uint32_t* )(0xE0100070) = 0x1;
                *(volatile uint32_t* )(0x42010108) = 0x12;
                LOG_INF("[SLP] *(volatile uint32_t* )(0x42010108) = 0x%x", *(volatile uint32_t* )(0x42010108) );
                LOG_INF("[SLP] *(volatile uint32_t* )(0xE0100070)  = 0x%x", *(volatile uint32_t* )(0xE0100070) );
                hal_gpio_init(pPayload[1]);
                hal_pinmux_set_function(pPayload[1], pPayload[2]);
                LOG_INF("[SLP] Enable CM33 WFI Signal Done(GPIO%d)", pPayload[1]);
            } else {
                LOG_ERR("Lack of SLEEP CONTROL arguments", 0);
                ptr->status = RACE_ERRCODE_PARAMETER_ERROR;
            }
            break;

        case SLEEP_CONTROL_RISCV_WFI_SIGNAL:
            /* CMD: 05 5A 05 00 20 02 12 XX 0D */
            if (cmd_len == 3) {
                LOG_INF("[SLP] Enable RISCV WFI Signal (GPIO%d)", pPayload[1]);
                *(volatile uint32_t* )(0x80000010) = 0xA01;
                *(volatile uint32_t* )(0x422F0030) = 0xD;
                *(volatile uint32_t* )(0x42010108) = 0x13;
                LOG_INF("[SLP] *(volatile uint32_t* )(0x80000010) = 0x%x", *(volatile uint32_t* )(0x80000010) );
                LOG_INF("[SLP] *(volatile uint32_t* )(0x422F0030)  = 0x%x", *(volatile uint32_t* )(0x422F0030) );
                LOG_INF("[SLP] *(volatile uint32_t* )(0x42010108)  = 0x%x", *(volatile uint32_t* )(0x42010108) );
                hal_gpio_init(pPayload[1]);
                hal_pinmux_set_function(pPayload[1], pPayload[2]);
                LOG_INF("[SLP] Enable RISCV WFI Signal Done(GPIO%d)", pPayload[1]);
            } else {
                LOG_ERR("Lack of SLEEP CONTROL arguments", 0);
                ptr->status = RACE_ERRCODE_PARAMETER_ERROR;
            }
            break;

        case SLEEP_CONTROL_TX_RX_SIGNAL:
            /* CMD: 05 5A 03 00 20 02 13 */
            *(volatile uint32_t* )(0x42010108) = 0x17;

            // GPIO 23 (RX) configure to debug mode.
            *(volatile uint32_t* )(0x420B0308) = 0xF0000000;
            *(volatile uint32_t* )(0x420B0208) = 0xD0000000;

            // GPIO 24 (TX) configure to debug mode.
            *(volatile uint32_t* )(0x420B030C) = 0x0000000F;
            *(volatile uint32_t* )(0x420B020C) = 0x0000000D;
            LOG_INF("[SLP] Enable Tx/Rx Signal (GPIO23, GPIO24)", 0);
            break;

        case SLEEP_CONTROL_MTCMOS_STATUS:
            /* CMD: 05 5A 03 00 20 02 14 */
            uint32_t rtctemp;
            LOG_INF("[SLP] PWR STATUS = 0x%x", *SPM_CFG_PWR_STATUS_2ND);
            rtctemp = ((*RTCSYS_PWR_CTRL >> 16) & 0x1);
            LOG_INF("[SLP] RTC PWR STATUS = 0x%x, value = 0x%x", rtctemp, *RTCSYS_PWR_CTRL);
            break;

        case SLEEP_CONTROL_FORCE_HANDLE_LOCK_SLP:
            /* CMD: 05 5A 04 00 20 02 15 XX */
            if (cmd_len == 2) {
                LOG_INF("[SLP] Force lock sleep handle : %d", pPayload[1]);
                hal_sleep_manager_lock_sleep(pPayload[1]);
            } else {
                LOG_ERR("Lack of SLEEP CONTROL arguments", 0);
                ptr->status = RACE_ERRCODE_PARAMETER_ERROR;
            }
            break;

        case SLEEP_CONTROL_FORCE_HANDLE_UNLOCK_SLP:
            /* CMD: 05 5A 04 00 20 02 16 XX */
            if (cmd_len == 2) {
                LOG_INF("[SLP] Force unlock sleep handle : %d", pPayload[1]);
                hal_sleep_manager_unlock_sleep(pPayload[1]);
            } else {
                LOG_ERR("Lack of SLEEP CONTROL arguments", 0);
                ptr->status = RACE_ERRCODE_PARAMETER_ERROR;
            }
            break;

        case SLEEP_CONTROL_FORCE_HANDLE_LOCK_EXT_SLP:
            /* CMD: 05 5A 04 00 20 02 17 XX */
            if (cmd_len == 2) {
                LOG_INF("[SLP] Force lock ext-sleep handle : %d", pPayload[1]);
                hal_sleep_manager_lock_extslp(pPayload[1]);
            } else {
                LOG_ERR("Lack of SLEEP CONTROL arguments", 0);
                ptr->status = RACE_ERRCODE_PARAMETER_ERROR;
            }
            break;

        case SLEEP_CONTROL_FORCE_HANDLE_UNLOCK_EXT_SLP:
            /* CMD: 05 5A 04 00 20 02 18 XX */
            if (cmd_len == 2) {
                LOG_INF("[SLP] Force unlock ext-sleep handle : %d", pPayload[1]);
                hal_sleep_manager_unlock_extslp(pPayload[1]);
            } else {
                LOG_ERR("Lack of SLEEP CONTROL arguments", 0);
                ptr->status = RACE_ERRCODE_PARAMETER_ERROR;
            }
            break;

        case SLEEP_CONTROL_FORCE_HANDLE_LOCK_IDLE:
            /* CMD: 05 5A 04 00 20 02 19 XX */
            if (cmd_len == 2) {
                LOG_INF("[SLP] Force lock idle handle : %d", pPayload[1]);
                hal_sleep_manager_lock_idle(pPayload[1]);
            } else {
                LOG_ERR("Lack of SLEEP CONTROL arguments", 0);
                ptr->status = RACE_ERRCODE_PARAMETER_ERROR;
            }
            break;

        case SLEEP_CONTROL_FORCE_HANDLE_UNLOCK_IDLE:
            /* CMD: 05 5A 04 00 20 02 1A XX */
            if (cmd_len == 2) {
                LOG_INF("[SLP] Force unlock idle handle : %d", pPayload[1]);
                hal_sleep_manager_unlock_idle(pPayload[1]);
            } else {
                LOG_ERR("Lack of SLEEP CONTROL arguments", 0);
                ptr->status = RACE_ERRCODE_PARAMETER_ERROR;
            }
            break;

        case SLEEP_CONTROL_SLP_WAKEUP_DUMP:
            /* CMD: 05 5A 04 00 20 02 1B XX */
            if (cmd_len == 2) {
                if(pPayload[1] == 0x1){
                    extern volatile bool slp_wakeup_dump_flag;
                    slp_wakeup_dump_flag = true;
                    LOG_INF("[SLP] slp wakeup dump flag set : %d", slp_wakeup_dump_flag);
                }else if(pPayload[1] == 0x0){
                    extern volatile bool slp_wakeup_dump_flag;
                    slp_wakeup_dump_flag = false;
                    LOG_INF("[SLP] slp wakeup dump flag clear : %d", slp_wakeup_dump_flag);
                }else{
                    LOG_ERR("SLP CMD parameter is error", 0);
                }
            } else {
                LOG_ERR("Lack of SLEEP CONTROL arguments", 0);
                ptr->status = RACE_ERRCODE_PARAMETER_ERROR;
            }
            break;

        case SLEEP_CONTROL_MEMORY_STATUS:
            /* CMD: 05 5A 03 00 20 02 1C */
            /* sysram0 status
             */
            LOG_INF("[SLP][Sram0][64K][PRDYN] MEMORY_RISCV_CONTROL_2:0x%x, [RET2N] MEMORY_RISCV_CONTROL_0=0x%x", *MEMORY_RISCV_CONTROL_2, *MEMORY_RISCV_CONTROL_0);
            /* sysram1-5 status
             */
            LOG_INF("[SLP][Sram1-5][320K][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2:0x%x, [RET2N] MEMORY_SYSRAM1_5_CONTROL_0:0x%x", *MEMORY_SYSRAM1_5_CONTROL_2, *MEMORY_SYSRAM1_5_CONTROL_0);
            /* riscv sram status
             */
            LOG_INF("[SLP][Risc][32K][PRDYN] MEMORY_RISCV_CONTROL_2:0x%x, [RET2N] MEMORY_RISCV_CONTROL_0=0x%x", *MEMORY_RISCV_CONTROL_2, *MEMORY_RISCV_CONTROL_0);
            /* bt sram status
             */
            LOG_INF("[SLP][BT][16K][PRDYN] MEMORY_SYSRAM6_CONTROL_2:0x%x, [RET2N] MEMORY_SYSRAM6_CONTROL_0=0x%x", *MEMORY_SYSRAM6_CONTROL_2, *MEMORY_SYSRAM6_CONTROL_0);

            break;

        case SLEEP_CONTROL_SLP_FORCE_ON:
            /* CMD: 05 5A 05 00 20 02 1D XX XX */
            if (cmd_len == 3) {
                spm_mtcmos_force_on(pPayload[1], pPayload[2]);
            } else {
                LOG_ERR("Lack of SLEEP CONTROL arguments", 0);
                ptr->status = RACE_ERRCODE_PARAMETER_ERROR;
            }
            break;

        case SLEEP_CONTROL_FORCE_ON_PD:
            /* CMD: 05 5A 05 00 20 02 1E XX XX */
            if (cmd_len == 3) {
                spm_mtcmos_force_on_infra_pd(pPayload[1], pPayload[2]);
            } else {
                LOG_ERR("Lack of SLEEP CONTROL arguments", 0);
                ptr->status = RACE_ERRCODE_PARAMETER_ERROR;
            }
            break;

        default:
            LOG_ERR("Unknown SLEEP CONTROL RACE CMD", 0);
            ptr->status = RACE_ERRCODE_NOT_SUPPORT;
            break;
    }
#else
    LOG_ERR("SLEEP_MANAGER not enabled", 0);
    ptr->status = RACE_ERRCODE_NOT_SUPPORT;
#endif /* HAL_SLEEP_MANAGER_ENABLED */

    return ptr;
}
#endif /* RACE_SLEEP_CONTROL_ENABLE */
#elif defined (AIR_BTD_IC_MANDATORY_G1)
#include "race_cmd_sleep_control.h"
#include <zephyr/logging/log.h>

#ifdef RACE_SLEEP_CONTROL_ENABLE

#ifdef HAL_SLEEP_MANAGER_ENABLED
//#include "hal_spm.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_internal.h"
#include "hal_rtc_internal.h"
#include "hal_clock_internal.h"
#include "hal_rtc.h"
#include "hal_clock.h"
#include "memory_attribute.h"
#include "autoconf.h"
//#include "hal_deep_sleep.h"
#include "hal_pmu.h"
#include "hal_nvic.h"
#include "hal_gpio.h"
#include "hal_wdt.h"

/* SLEEP CONTROL RACE CMD */
enum {
    SLEEP_CONTROL_UNLOCK_SLP = 0,              /* CMD: 05 5A 03 00 20 02 00 */
    SLEEP_CONTROL_LOCK_SLP,                    /* CMD: 05 5A 03 00 20 02 01 */
    SLEEP_CONTROL_UNLOCK_TO_IDLE,              /* CMD: 05 5A 03 00 20 02 02 */
    SLEEP_CONTROL_LOCK_TO_IDLE,                /* CMD: 05 5A 03 00 20 02 03 */
    SLEEP_CONTROL_UNLOCK_TO_SUSP,              /* CMD: 05 5A 03 00 20 02 04 */
    SLEEP_CONTROL_LOCK_TO_SUSP,                /* CMD: 05 5A 03 00 20 02 05 */
    SLEEP_CONTROL_UNLOCK_TO_SLP_2,             /* CMD: 05 5A 03 00 20 02 06 */
    SLEEP_CONTROL_LOCK_TO_SLP_2,               /* CMD: 05 5A 03 00 20 02 07 */
    SLEEP_CONTROL_UNLOCK_TO_SLP_1,             /* CMD: 05 5A 03 00 20 02 08 */
    SLEEP_CONTROL_LOCK_TO_SLP_1,               /* CMD: 05 5A 03 00 20 02 09 */    

    SLEEP_CONTROL_ENTER_IDLE,                   /* CMD: 05 5A 03 00 20 02 0A */
    SLEEP_CONTROL_ENTER_SUSP,                   /* CMD: 05 5A 03 00 20 02 0B */
    SLEEP_CONTROL_ENTER_SLP_2,                  /* CMD: 05 5A 03 00 20 02 0C */
    SLEEP_CONTROL_ENTER_SLP_1,                  /* CMD: 05 5A 03 00 20 02 0D */
    SLEEP_CONTROL_ENTER_DSLP_2,                 /* CMD: 05 5A 03 00 20 02 0E */
    SLEEP_CONTROL_ENTER_DSLP_1,                 /* CMD: 05 5A 03 00 20 02 0F */


    SLEEP_CONTROL_DUMP_LOCK_SLP_STATUS,        /* CMD: 05 5A 03 00 20 02 10 */
    SLEEP_CONTROL_DUMP_LOCK_IDLE_STATUS,       /* CMD: 05 5A 03 00 20 02 11 */
    SLEEP_CONTROL_DUMP_LOCK_SUSP_STATUS,       /* CMD: 05 5A 03 00 20 02 12 */
    SLEEP_CONTROL_DUMP_LOCK_SLP_2_STATUS,      /* CMD: 05 5A 03 00 20 02 13 */
    SLEEP_CONTROL_DUMP_LOCK_SLP_1_STATUS,      /* CMD: 05 5A 03 00 20 02 14 */
    
    SLEEP_CONTROL_SET_MULTI_GPIOS_FOR_MEASURE, /* CMD: 05 5A 05 00 20 02 15 XX XX */
    SLEEP_CONTROL_DEBUG_SWITCH_SLEEP_PHARE,    /* CMD: 05 5A 04 00 20 02 16 XX*/

    SLEEP_CONTROL_SUSPEND_SIGNAL,              /* CMD: 05 5A 03 00 20 02 17 */
    SLEEP_CONTROL_SLP_2_SIGNAL,                /* CMD: 05 5A 03 00 20 02 18 */
    SLEEP_CONTROL_SLP_1_SIGNAL,                /* CMD: 05 5A 03 00 20 02 19 */
    SLEEP_CONTROL_DSLP_2_SIGNAL,               /* CMD: 05 5A 03 00 20 02 1A */
    SLEEP_CONTROL_SWITCH_SYSLOG_FOR_MEASURE_LOW_POWER, /* CMD: 05 5A 04 00 20 02 1B XX */

    SLEEP_CONTROL_WAKEUP_FROM_SUSP,              /* CMD: 05 5A 04 00 20 02 1C XX */
    SLEEP_CONTROL_WAKEUP_FROM_SLP_2,            /* CMD: 05 5A 04 00 20 02 1D XX */
    SLEEP_CONTROL_WAKEUP_FROM_SLP_1,            /* CMD: 05 5A 04 00 20 02 1E XX */

    SLEEP_CONTROL_32K_SELECTION ,                /* CMD: 05 5A 04 00 20 02 1F XX */

    SLEEP_CONTROL_SLP_WAKEUP_DUMP              /* CMD: 05 5A 04 00 20 02 1F XX */
};


#endif /* DVT_CACHE_MEMORY_KEEP */
extern uint32_t sleep_management_get_lock_sleep_handle_list(sleep_management_mode_t sleep_mode);
volatile uint32_t stack_pointer_race_cmd;
extern void hal_sleep_management_wdt_set_timeout_before_sleep(void);
extern void hal_sleep_management_wdt_disable_timeout_after_sleep(void);
extern void sleep_management_core_and_nvic_rg_back_up(void);
extern void sleep_management_core_and_nvic_rg_restore(void);
/*public macro for entry slp flow*/
#define __CPU_RG_BACKUP_ASM()                                                   \
    __asm__ volatile(                                                           \
        ".syntax unified\n"                                                     \
        /* backup r0~r12 */                                                     \
        "push {r0-r7}\n"                                                        \
        "mov r3, r8\n"                                                          \
        "mov r4, r9\n"                                                          \
        "mov r5, r10\n"                                                         \
        "mov r6, r11\n"                                                         \
        "mov r7, r12\n"                                                         \
        "push {r3-r7}\n"                                                        \
        /* backup msp/psp/xPSR/CONTROL/BASEPRI/FAULTMASK/PRIMASK */             \
        "mrs r1, psp\n"                                                         \
        "mrs r2, xPSR\n"                                                        \
        "mrs r3, CONTROL\n"                                                     \
        "mrs r4, BASEPRI\n"                                                     \
        "mrs r5, FAULTMASK\n"                                                   \
        "mrs r6, PRIMASK\n"                                                     \
        "ldr r0, =0xE000ED08\n"                                                 \
        "ldr r7, [r0]\n"                                                        \
        "mrs r0, msp\n"                                                         \
        "push {r0-r7}\n"                                                        \
    );


#define __CPU_RG_RESTORE_ASM()                                                  \
    __asm__ volatile(                                                           \
        ".syntax unified\n"                                                     \
        /* restore PSP from stack_pointer */                                    \
        "ldr r0, =stack_pointer_race_cmd\n"                                              \
        "ldr r1, [r0]\n"                                                        \
        "msr psp, r1\n"                                                         \
        /* use PSP */                                                           \
        "movs r3, #2\n"                                                         \
        "msr CONTROL, r3\n"                                                     \
        /* restore msp/psp/xPSR/CONTROL/BASEPRI/FAULTMASK/PRIMASK */            \
        "pop {r0-r7}\n"                                                         \
        "msr msp, r0\n"                                                         \
        "msr psp, r1\n"                                                         \
        "msr xPSR, r2\n"                                                        \
        "msr CONTROL, r3\n"                                                     \
        "msr BASEPRI, r4\n"                                                     \
        "msr FAULTMASK, r5\n"                                                   \
        "msr PRIMASK, r6\n"                                                     \
        "ldr r0, =0xE000ED08\n"                                                 \
        "str r7, [r0]\n"                                                        \
        /* restore r0~r12 */                                                    \
        "pop {r3-r7}\n"                                                         \
        "mov r8, r3\n"                                                          \
        "mov r9, r4\n"                                                          \
        "mov r10, r5\n"                                                         \
        "mov r11, r6\n"                                                         \
        "mov r12, r7\n"                                                         \
        "pop {r0-r7}\n"                                                         \
    );

//uint32_t pc_tag_after_sleep;

#define SLEEP_TAG_NAME(X)           X##_pc_tag_after_sleep
#define SLEEP_TAG_STR(X)            #X
#define SLEEP_TAG_STR2(X)           SLEEP_TAG_STR(X)

#define __ENTER_SLEEP_ASM(NAME)                                                 \
    __asm__ volatile(                                                           \
        ".syntax unified\n"                                                     \
        /* *(volatile uint32_t *)0x40003D04 = pc_tag_after_sleep | 0x1 */       \
        "ldr r0, =0x40003D00\n"                                                 \
        "ldr r2, ="                                                             \
        SLEEP_TAG_STR2(SLEEP_TAG_NAME(NAME))                                    \
        "\n"                                                                    \
        "movs r3, #1\n"                                                         \
        "orrs r2, r3\n"                                                         \
        "str r2, [r0, #0x4]\n"                                                  \
        /* *(volatile uint32_t *)0x40003D00 = 0x1; */                           \
        "movs r1, #1\n"                                                         \
        "str r1, [r0, #0x0]\n"                                                  \
        /* save PSP to stack_pointer */                                         \
        "ldr r0, =stack_pointer_race_cmd\n"                                              \
        "mrs r1, psp\n"                                                         \
        "str r1, [r0]\n"                                                        \
        /* flush pipeline */                                                    \
        "dsb\n"                                                                 \
        "isb\n"                                                                 \
        /* trigger enter sleep */                                               \
        "wfi\n"                                                                 \
        /* after sleep, PC will be here */                                      \
        SLEEP_TAG_STR2(SLEEP_TAG_NAME(NAME))                                    \
        ":\n"                                                                   \
        "nop\n"                                                                 \
        "nop\n"                                                                 \
        "nop\n"                                                                 \
        "nop\n"                                                                 \
    );
/*public macro for entry slp flow*/

void race_sleep_control_enter_wdt(void){
#ifdef CONFIG_AIR_WDT
    printk("[race cmd] Enter WDT!!!");
    hal_gpt_delay_ms(500);
    hal_wdt_software_reset();
#endif
}

void race_sleep_control_enter_dslp_1(void)
{
    printk("[race cmd] Enter Sleep DSLP-1!!!");
    pmu_power_off_sequence(PMU_PWR_STA_DSLP1);

}

void race_sleep_control_enter_dslp_2(void){
    printk("[race cmd] Enter Sleep DSLP-2!!!");
    pmu_power_off_sequence(PMU_PWR_STA_DSLP2);
}


void race_sleep_control_enter_slp_2(void)
{
    printk("[race cmd] Enter Sleep SLP-2!!!");
    
    
        /* clear the all irq status */
    for (int i = 0; i < IRQ_NUMBER_MAX; i++) {
        //hal_nvic_disable_irq(i);
        if (hal_nvic_get_pending_irq(i) == 1) {
            // printf("pending_irq:%d\r\n", i);
            hal_nvic_clear_pending_irq(i);
        }
    }
    
    
    __asm__ volatile(
        ".syntax unified\n"
        "cpsid i\n"
        );
    *(volatile uint32_t*)0x4000900C=0x001FFFFF;
    *(volatile uint32_t*)0x40009010=0x0D000008;
    *(volatile uint32_t*)0x40009008=0xFF000000;


        // set ldo to 0.9v
    (*(volatile uint32_t *) (0x40009038)) &= ~(0XF << 16); 

    (*(volatile uint32_t *) (0x40009038)) |= 0XA;

    // disable the LDO PA
    (*(volatile uint32_t *) (0x40009024)) &= ~(1<<4);

    (*(volatile uint32_t *) (0x400070A8)) = 0x001FFFFF;				//RECORD wakeup all enable
    (*(volatile uint32_t *) (0x40007024)) = 0x00000000;				//Clear record wakeup-0 
    (*(volatile uint32_t *) (0x40007028)) = 0x00000000;				//Clear record wakeup-1

    *(volatile uint32_t *)0x40007000 |= (1<<3);      //SLP2

    /* enable the debug gpio status ,default use the gpio-4*/
    (*(volatile uint32_t *)(0x400037E0)) = 0x00000300; //[10:8] Set pmu debug bus
	(*(volatile uint32_t *)(0x40007038)) = 0x00;			 //PMU Debugbus selecttion	
	//(*(volatile uint32_t *)(0x400037E8)) = 0x1B1A1900; //Set GPIO5-PMU_PST_SLP2, GPIO6-PMU_PST_SLP1,
	(*(volatile uint32_t *)(0x400037E8)) = 0x00000019;	// set slp-2 map gpio4
    hal_pinmux_set_function(HAL_GPIO_4, 13);


    hal_sleep_management_wdt_set_timeout_before_sleep();
    sleep_management_core_and_nvic_rg_back_up();
    __CPU_RG_BACKUP_ASM();
    __ENTER_SLEEP_ASM(slp2_race); //enter sleep mode-2
    __CPU_RG_RESTORE_ASM();
    sleep_management_core_and_nvic_rg_restore();
    hal_sleep_management_wdt_disable_timeout_after_sleep();
    __asm__ volatile(
        ".syntax unified\n"
        "cpsie i\n"
    );
    while(1);
}



void race_sleep_control_enter_slp_1(void)
{
    
    
    /* clear the all irq status */
    for (int i = 0; i < IRQ_NUMBER_MAX; i++) {
        //hal_nvic_disable_irq(i);
        if (hal_nvic_get_pending_irq(i) == 1) {
            // printf("pending_irq:%d\r\n", i);
            hal_nvic_clear_pending_irq(i);
        }
    }
    printk("[race cmd] Enter Sleep SLP-1!!!");  

    __asm__ volatile(
        ".syntax unified\n"
        "cpsid i\n"
        );

    *(volatile uint32_t*)0x4000900C=0x001FFFFF;
    *(volatile uint32_t*)0x40009010=0x0D000008;
    *(volatile uint32_t*)0x40009008=0xFF000000;


        // set ldo to 0.9v
    (*(volatile uint32_t *) (0x40009038)) &= ~(0XF << 16); 

    (*(volatile uint32_t *) (0x40009038)) |= 0XA;

    // disable the LDO PA
    (*(volatile uint32_t *) (0x40009024)) &= ~(1<<4);

    (*(volatile uint32_t *) (0x400070A8)) = 0x001FFFFF;				//RECORD wakeup all enable
    (*(volatile uint32_t *) (0x40007024)) = 0x00000000;				//Clear record wakeup-0 
    (*(volatile uint32_t *) (0x40007028)) = 0x00000000;				//Clear record wakeup-1

    *(volatile uint32_t *)0x40007000 |= (1<<2);      //SLP1
    
    /* enable the debug gpio status ,default use the gpio-4*/
    (*(volatile uint32_t *)(0x400037E0)) = 0x00000300; //[10:8] Set pmu debug bus
	(*(volatile uint32_t *)(0x40007038)) = 0x00;			 //PMU Debugbus selecttion	
	//(*(volatile uint32_t *)(0x400037E8)) = 0x1B1A1900; //Set GPIO5-PMU_PST_SLP2, GPIO6-PMU_PST_SLP1,
	(*(volatile uint32_t *)(0x400037E8)) = 0x0000001A;	// set slp-1 map gpio4
    hal_pinmux_set_function(HAL_GPIO_4, 13);

    //hal_sleep_management_wdt_set_timeout_before_sleep();
    sleep_management_core_and_nvic_rg_back_up();
    __CPU_RG_BACKUP_ASM();
    __ENTER_SLEEP_ASM(slp1_race); //enter sleep mode
    __CPU_RG_RESTORE_ASM();
    sleep_management_core_and_nvic_rg_restore();
    hal_sleep_management_wdt_disable_timeout_after_sleep();
    __asm__ volatile(
        ".syntax unified\n"
        "cpsie i\n"
    );
    while(1);
}


void race_sleep_control_enter_slp_sus(void)
{
    printk("[race cmd] Enter Sleep suspend!!!");
    /* clear the all irq status */
    for (int i = 0; i < IRQ_NUMBER_MAX; i++) {
        //hal_nvic_disable_irq(i);
        if (hal_nvic_get_pending_irq(i) == 1) {
            // printf("pending_irq:%d\r\n", i);
            hal_nvic_clear_pending_irq(i);
        }
    }
    __asm__ volatile(
        ".syntax unified\n"
        "cpsid i\n"
        );

    *(volatile uint32_t*)0x4000900C=0x001FFFFF;
    *(volatile uint32_t*)0x40009010=0x0D000008;
    *(volatile uint32_t*)0x40009008=0xFF000000;


        // set ldo to 0.9v
    (*(volatile uint32_t *) (0x40009038)) &= ~(0XF << 16); 

    (*(volatile uint32_t *) (0x40009038)) |= 0XA;

    // disable the LDO PA
    (*(volatile uint32_t *) (0x40009024)) &= ~(1<<4);

    (*(volatile uint32_t *) (0x400070A8)) = 0x001FFFFF;				//RECORD wakeup all enable
    (*(volatile uint32_t *) (0x40007024)) = 0x00000000;				//Clear record wakeup-0 
    (*(volatile uint32_t *) (0x40007028)) = 0x00000000;				//Clear record wakeup-1

    *(volatile uint32_t *)0x40007000 |= (1<<1);      //SUSPEND

        /* enable the debug gpio status ,default use the gpio-4*/
    (*(volatile uint32_t *)(0x400037E0)) = 0x00000300; //[10:8] Set pmu debug bus
	(*(volatile uint32_t *)(0x40007038)) = 0x00;			 //PMU Debugbus selecttion	
	//(*(volatile uint32_t *)(0x400037E8)) = 0x1B1A1900; //Set GPIO5-PMU_PST_SLP2, GPIO6-PMU_PST_SLP1,
	(*(volatile uint32_t *)(0x400037E8)) = 0x00000018;	// set slp-1 map gpio4
    hal_pinmux_set_function(HAL_GPIO_4, 13);
    
    hal_sleep_management_wdt_set_timeout_before_sleep();
    sleep_management_core_and_nvic_rg_back_up();
    __CPU_RG_BACKUP_ASM();
    __ENTER_SLEEP_ASM(sus_race); //enter sleep mode
    __CPU_RG_RESTORE_ASM();
    sleep_management_core_and_nvic_rg_restore();
    hal_sleep_management_wdt_disable_timeout_after_sleep();

    __asm__ volatile(
        ".syntax unified\n"
        "cpsie i\n"
    );

}


void race_sleep_control_enter_slp_idle(void)
{
    printk("[race cmd] Enter Sleep idle!!!");

    uint32_t enter_count = 0;
    /* clear the all irq status */
    for (int i = 0; i < IRQ_NUMBER_MAX; i++) {
        //hal_nvic_disable_irq(i);
        if (hal_nvic_get_pending_irq(i) == 1) {
            // printf("pending_irq:%d\r\n", i);
            hal_nvic_clear_pending_irq(i);
        }
    }

    while(enter_count>100){
    enter_count++;    
    printk("[race cmd] Enter Sleep idle!!!");
    *(volatile uint32_t *)0x40007000 |= (1<<4);      //IDLE
    __disable_irq();
    hal_sleep_management_wdt_set_timeout_before_sleep();
    __asm volatile("dsb");
    __asm volatile("wfi");
    __asm volatile("isb");
    hal_sleep_management_wdt_disable_timeout_after_sleep();
    __enable_irq();
    printk("[race cmd] Wake up from Sleep idle !!!");
    
    }
}



extern uint8_t sleep_manager_handle;
extern uint8_t sleep_manager_slpsus_handle;
extern uint8_t sleep_manager_idle_handle;
extern uint8_t sleep_manager_slp2_handle;
extern uint8_t sleep_manager_slp1_handle;

extern void syslog_port_control_output_log(uint8_t log_switch);
extern bool sleep_management_disable_syslog_flag;
#ifdef HAL_SLEEP_MANAGEMENT_GPIO_MEARSURE_TIME
extern uint8_t measure_active_and_sleep_phase_mode;
#endif
void *RACE_CmdHandler_sleep_control(ptr_race_pkt_t pRaceHeaderCmd, uint16_t Length, uint8_t channel_id)
{
    LOG_INF("RACE_CmdHandler_sleep_control, type[0x%X], cmd[0x%X], ch[%d]", 3,
                     pRaceHeaderCmd->hdr.type, pRaceHeaderCmd->hdr.id, channel_id);
    //(void)race_sleep_control_enter_slp_2;
    //(void)race_sleep_control_enter_slp_1;
    //(void)race_sleep_control_enter_dslp_2;
    //(void)race_sleep_control_enter_dslp_1;
    typedef struct {
        uint8_t status;
    } PACKED RACE_SLEEP_CONTROL_RESPONSE;

    RACE_SLEEP_CONTROL_RESPONSE *ptr = RACE_ClaimPacketAppID(pRaceHeaderCmd->hdr.pktId.field.app_id,
                                                              RACE_TYPE_RESPONSE,
                                                              0x0220,
                                                              sizeof(RACE_SLEEP_CONTROL_RESPONSE),
                                                              channel_id);

    if (ptr != NULL) {
        ptr->status = RACE_ERRCODE_SUCCESS;
    } else {
        LOG_ERR("Pack race claim packet failed", 0);
        return NULL;
    }

#ifdef HAL_SLEEP_MANAGER_ENABLED
    uint8_t *pPayload = pRaceHeaderCmd->payload;
    if (pPayload == NULL) {
        LOG_ERR("Lack of RACE CMD payload", 0);
        ptr->status = RACE_ERRCODE_PARAMETER_ERROR;
        return ptr;
    }

    uint16_t cmd_len = pRaceHeaderCmd->hdr.length - 2; /* not count RACE ID */
    switch (pPayload[0]) {
        case SLEEP_CONTROL_UNLOCK_SLP:
            /* CMD: 05 5A 03 00 20 02 00 */
            hal_sleep_manager_unlock_sleep(sleep_manager_handle);
            break;
        case SLEEP_CONTROL_LOCK_SLP:
            /* CMD: 05 5A 03 00 20 02 01 */
            hal_sleep_manager_lock_sleep(sleep_manager_handle);
            break;
        case SLEEP_CONTROL_UNLOCK_TO_IDLE:
            /* CMD: 05 5A 03 00 20 02 02 */
            hal_sleep_manager_unlock_idle(sleep_manager_idle_handle);
            break;
        case SLEEP_CONTROL_LOCK_TO_IDLE:
            /* CMD: 05 5A 03 00 20 02 03 */
            hal_sleep_manager_lock_idle(sleep_manager_idle_handle);
            break;
        case SLEEP_CONTROL_UNLOCK_TO_SUSP:
            /* CMD: 05 5A 03 00 20 02 04 */
            hal_sleep_manager_unlock_slp_suspend(sleep_manager_slpsus_handle);
            break;
        case SLEEP_CONTROL_LOCK_TO_SUSP:
            /* CMD: 05 5A 03 00 20 02 05 */
            hal_sleep_manager_lock_slp_suspend(sleep_manager_slpsus_handle);
            break;
        case SLEEP_CONTROL_UNLOCK_TO_SLP_2:
            /* CMD: 05 5A 03 00 20 02 06 */
            hal_sleep_manager_unlock_slp_mode_2(sleep_manager_slp2_handle);
            break;
        case SLEEP_CONTROL_LOCK_TO_SLP_2:
            /* CMD: 05 5A 03 00 20 02 07 */
            hal_sleep_manager_lock_slp_mode_2(sleep_manager_slp2_handle);
            break;
        case SLEEP_CONTROL_UNLOCK_TO_SLP_1:
            /* CMD: 05 5A 03 00 20 02 08 */
            hal_sleep_manager_unlock_slp_mode_1(sleep_manager_slp1_handle);
            break;
        case SLEEP_CONTROL_LOCK_TO_SLP_1:
            /* CMD: 05 5A 03 00 20 02 09 */
            hal_sleep_manager_lock_slp_mode_1(sleep_manager_slp1_handle);
            break;
        case SLEEP_CONTROL_ENTER_IDLE:
            /* CMD: 05 5A 03 00 20 02 0A */
            race_sleep_control_enter_slp_idle();
            break;
        case SLEEP_CONTROL_ENTER_SUSP:
            /* CMD: 05 5A 03 00 20 02 0B */
            race_sleep_control_enter_slp_sus();
            break;
        case SLEEP_CONTROL_ENTER_SLP_2:
            /* CMD: 05 5A 03 00 20 02 0C */
            race_sleep_control_enter_slp_2();
            break;
        case SLEEP_CONTROL_ENTER_SLP_1:
            /* CMD: 05 5A 03 00 20 02 0D */
            race_sleep_control_enter_slp_1();
            break;
        case SLEEP_CONTROL_ENTER_DSLP_2:
            /* CMD: 05 5A 03 00 20 02 0E */
            race_sleep_control_enter_dslp_2();
            break;
        case SLEEP_CONTROL_ENTER_DSLP_1:
            /* CMD: 05 5A 03 00 20 02 0F */
            race_sleep_control_enter_dslp_1();
            break;
        case SLEEP_CONTROL_DUMP_LOCK_SLP_STATUS:
            /* CMD: 05 5A 03 00 20 02 10 */
            if (hal_sleep_manager_is_sleep_locked()) {
                sleep_management_get_lock_sleep_handle_list(SLEEP_PURE_WFI_MODE);
            } else {
                LOG_INF("Any Sleep Handle not locked", 0);
            }
            break;
        case SLEEP_CONTROL_DUMP_LOCK_IDLE_STATUS:
            /* CMD: 05 5A 03 00 20 02 11 */
            if (hal_sleep_manager_get_idle_lock_status()) {
                sleep_management_get_lock_sleep_handle_list(SLEEP_TICKLESS_MODE);
            } else {
                LOG_INF("Any Tickless Handle not locked", 0);
            }
            break;
        case SLEEP_CONTROL_DUMP_LOCK_SUSP_STATUS:
            /* CMD: 05 5A 03 00 20 02 12 */
            if (hal_sleep_manager_get_slp_suspend_lock_status()) {
                sleep_management_get_lock_sleep_handle_list(SLEEP_SUSPEND_MODE);
            } else {
                LOG_INF("Any SUSP Handle not locked", 0);
            }
            break;
        case SLEEP_CONTROL_DUMP_LOCK_SLP_2_STATUS:
            /* CMD: 05 5A 03 00 20 02 13 */
            if (hal_sleep_manager_get_slp_2_lock_status()) {
                sleep_management_get_lock_sleep_handle_list(SLEEP_TWO_MODE);
            } else {
                LOG_INF("Any SLP_2 Handle not locked", 0);
            }
            break;
        case SLEEP_CONTROL_DUMP_LOCK_SLP_1_STATUS:
            /* CMD: 05 5A 03 00 20 02 14 */
            if (hal_sleep_manager_get_slp_1_lock_status()) {
                sleep_management_get_lock_sleep_handle_list(SLEEP_ONE_MODE);
            } else {
                LOG_INF("Any SLP_1 Handle not locked", 0);
            }
            break;
        case SLEEP_CONTROL_SET_MULTI_GPIOS_FOR_MEASURE:    // DEFAULT ONLY USE THE TWO GPIO TO Parse Time.
            /* CMD: 05 5A 05 00 20 02 15 XX XX*/
            if (cmd_len == 3) {
                /*add the debug gpio for merasure low power*/
                hal_pinmux_set_function(pPayload[1], 0);
                hal_gpio_set_direction(pPayload[1],1);
                hal_gpio_set_output(pPayload[1],0);
                
                /*add the debug gpio for merasure low power*/
                hal_pinmux_set_function(pPayload[2], 0);
                hal_gpio_set_direction(pPayload[2],1);
                hal_gpio_set_output(pPayload[2],0);
            }else{
                LOG_ERR("[SLEEP_RACE_CMD] Lack of SLEEP SET arguments or Cmd error", 0);
            }
            break; 
        case SLEEP_CONTROL_DEBUG_SWITCH_SLEEP_PHARE:
            /* CMD: 05 5A 04 00 20 02 16 xx*/
            if(pPayload[1] < PHASE_MEASURE_MAX ){
#ifdef HAL_SLEEP_MANAGEMENT_GPIO_MEARSURE_TIME
                if(pPayload[1] == 4)
                {
                    measure_active_and_sleep_phase_mode = 0xFF;
                }else{
                    measure_active_and_sleep_phase_mode = pPayload[1];
                }
                hal_gpio_set_output(23,0);
                hal_gpio_set_output(38,0);
#endif
            }else{
                LOG_INF("[SLEEP_RACE_CMD]: Not find the Mode");
            }
            break;
        case SLEEP_CONTROL_SUSPEND_SIGNAL:
            /* CMD: 05 5A 03 00 20 02 17 */
            //race_sleep_control_enter_coremark();
            break;
        case SLEEP_CONTROL_SLP_2_SIGNAL:
            /* CMD: 05 5A 03 00 20 02 18 */
            //race_sleep_control_enter_coremark();
            break;
        case SLEEP_CONTROL_SLP_1_SIGNAL:
            /* CMD: 05 5A 03 00 20 02 19 */
            //race_sleep_control_enter_coremark();
            break;
        case SLEEP_CONTROL_DSLP_2_SIGNAL:
            /* CMD: 05 5A 03 00 20 02 1A */
            //race_sleep_control_enter_coremark();
            break;
        case SLEEP_CONTROL_SWITCH_SYSLOG_FOR_MEASURE_LOW_POWER:
            /* CMD: 05 5A 04 00 20 02 1B XX */
            if(pPayload[1] == 0)
            {
                LOG_INF("[SLEEP_RACE_CMD][SYSLOG] DISABLE _SYSLOG");
                syslog_port_control_output_log(0); //
                sleep_management_disable_syslog_flag = true;
            }else{
                syslog_port_control_output_log(1);
                sleep_management_disable_syslog_flag = false;
                LOG_INF("[SLEEP_RACE_CMD][SYSLOG] ENABLE _SYSLOG");
            }
            break;
        case SLEEP_CONTROL_WAKEUP_FROM_SUSP:
            /* CMD: 05 5A 04 00 20 02 1C XX */
            // if (cmd_len == 2) {
            //     if(pPayload[1] == 0x1){
            //         extern volatile bool slp_wakeup_dump_flag;
            //         slp_wakeup_dump_flag = true;
            //         LOG_INF("[SLP] slp wakeup dump flag set : %d", slp_wakeup_dump_flag);
            //     }else if(pPayload[1] == 0x0){
            //         extern volatile bool slp_wakeup_dump_flag;
            //         slp_wakeup_dump_flag = false;
            //         LOG_INF("[SLP] slp wakeup dump flag clear : %d", slp_wakeup_dump_flag);
            //     }else{
            //         LOG_ERR("SLP CMD parameter is error", 0);
            //     }
            // } else {
            //     LOG_ERR("Lack of SLEEP CONTROL arguments", 0);
            //     ptr->status = RACE_ERRCODE_PARAMETER_ERROR;
            // }
            break;
        case SLEEP_CONTROL_WAKEUP_FROM_SLP_2:
            /* CMD: 05 5A 04 00 20 02 1D XX */
            // if (cmd_len == 2) {
            //     if(pPayload[1] == 0x1){
            //         extern volatile bool slp_wakeup_dump_flag;
            //         slp_wakeup_dump_flag = true;
            //         LOG_INF("[SLP] slp wakeup dump flag set : %d", slp_wakeup_dump_flag);
            //     }else if(pPayload[1] == 0x0){
            //         extern volatile bool slp_wakeup_dump_flag;
            //         slp_wakeup_dump_flag = false;
            //         LOG_INF("[SLP] slp wakeup dump flag clear : %d", slp_wakeup_dump_flag);
            //     }else{
            //         LOG_ERR("SLP CMD parameter is error", 0);
            //     }
            // } else {
            //     LOG_ERR("Lack of SLEEP CONTROL arguments", 0);
            //     ptr->status = RACE_ERRCODE_PARAMETER_ERROR;
            // }
            break;
        case SLEEP_CONTROL_WAKEUP_FROM_SLP_1:
            /* CMD: 05 5A 04 00 20 02 1E XX */
            // if (cmd_len == 2) {
            //     if(pPayload[1] == 0x1){
            //         extern volatile bool slp_wakeup_dump_flag;
            //         slp_wakeup_dump_flag = true;
            //         LOG_INF("[SLP] slp wakeup dump flag set : %d", slp_wakeup_dump_flag);
            //     }else if(pPayload[1] == 0x0){
            //         extern volatile bool slp_wakeup_dump_flag;
            //         slp_wakeup_dump_flag = false;
            //         LOG_INF("[SLP] slp wakeup dump flag clear : %d", slp_wakeup_dump_flag);
            //     }else{
            //         LOG_ERR("SLP CMD parameter is error", 0);
            //     }
            // } else {
            //     LOG_ERR("Lack of SLEEP CONTROL arguments", 0);
            //     ptr->status = RACE_ERRCODE_PARAMETER_ERROR;
            // }
            break;        
            case SLEEP_CONTROL_32K_SELECTION:
                if(pPayload[1] == 0)
                {
                    LOG_INF("[SLP] SLEEP_CONTROL_32K_SELECTION : XO32K");
                    hal_clock_set_rtc_clk(CLK_RTC_XO32K);

                }else if(pPayload[1] == 1){
                    LOG_INF("[SLP] SLEEP_CONTROL_32K_SELECTION : RCO32K");
                    hal_clock_set_rtc_clk(CLK_RTC_RCO32K);
                    
                }else{
                    LOG_ERR("SLP CMD parameter is error", 0);
                }
            break;
            
        default:
            LOG_ERR("Unknown SLEEP CONTROL RACE CMD", 0);
            ptr->status = RACE_ERRCODE_NOT_SUPPORT;
            break;
    }
#else
    LOG_ERR("SLEEP_MANAGER not enabled", 0);
    ptr->status = RACE_ERRCODE_NOT_SUPPORT;
#endif /* HAL_SLEEP_MANAGER_ENABLED */

    return ptr;
}
#endif /* RACE_SLEEP_CONTROL_ENABLE */
#endif