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


#ifndef __AIR_SOC_H__
#define __AIR_SOC_H__

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "version.h"                    /* add for KERNELVERSION */
#include "autoconf.h"
#include "air_version.h"
#include "air_sys_init_level.h"         /* add for generated system initialize level information */

#include <zephyr/sys/util.h>
#include <zephyr/toolchain.h>
#include <zephyr/devicetree.h>
#include <zephyr/sys/__assert.h>        /* add for __ASSERT */

/* !!! NOTE !!!
 * Do not modify the definition order of header files here, otherwise there will be many builds
 * !!! NOTE !!!
 */

#include <zephyr/arch/arm/cortex_m/nvic.h>      /* add for NUM_IRQ_PRIO_BITS */

#define __MPU_PRESENT                  1        /*!< MPU present */
#define __FPU_PRESENT                  1        /*!< FPU present */
#define __NVIC_PRIO_BITS               NUM_IRQ_PRIO_BITS
#define __CM33_REV                     0x0000U   /* Core revision r0p1 */
#define __SAUREGION_PRESENT            1U        /* SAU regions present */

/* =========================================================================================================================== */
/* ================                                Interrupt Number Definition                                ================ */
/* =========================================================================================================================== */
typedef enum IRQn {
    /****  CM33 internal exceptions  **********/
    Reset_IRQn                  = -15,  /* Reset */
    NonMaskableInt_IRQn         = -14,  /* NMI */
    HardFault_IRQn              = -13,  /* HarFault */
    MemoryManagement_IRQn       = -12,  /* Memory Management */
    BusFault_IRQn               = -11,  /* Bus Fault  */
    UsageFault_IRQn             = -10,  /* Usage Fault */
    SecureFault_IRQn            = -9,   /* Secure Fault */
    SVCall_IRQn                 = -5,   /* SV Call*/
    DebugMonitor_IRQn           = -4,   /* Debug Monitor */
    PendSV_IRQn                 = -2,   /* Pend SV */
    SysTick_IRQn                = -1,   /* System Tick */

    /****  SOC specific external/peripheral interrupt ****/
    OS_GPT_IRQn         = 0,
    MCU_DMA0_IRQn       = 1,
    MCU_DMA1_IRQn       = 2,
    UART_DMA0_IRQn      = 3,
    UART_DMA1_IRQn      = 4,
    UART_DMA2_IRQn      = 5,
    PWM_DMA0_IRQn       = 6,
    PWM_DMA1_IRQn       = 7,
    I3C_DMA0_IRQn       = 8,
    I3C_DMA1_IRQn       = 9,
    I3C0_IRQn           = 10,
    I3C1_IRQn           = 11,
    SPI_MST0_IRQn       = 12,
    SPI_MST1_IRQn       = 13,
    SPI_MST2_IRQn       = 14,
    SPI_SLV_IRQn        = 15,
    UART0_IRQn          = 16,
    UART1_IRQn          = 17,
    UART2_IRQn          = 18,
    CRYPTO_IRQn         = 19,
    TRNG_IRQn           = 20,
    RTC_IRQn            = 21,
    GPT_IRQn            = 22,
    GPT_SEC_IRQn        = 23,
    SPM_IRQn            = 24,
    WDT_IRQn            = 25,
    EINT_SEC_IRQn       = 26,
    EINT_IRQn           = 27,
    SFC_IRQn            = 28,
    ESC_IRQn            = 29,
    USB_IRQn            = 30,
    RISCV_IRQ_GEN_IRQn   = 31,
    AUDIOSYS_IRQn       = 32,
    BT_IRQn             = 33,
    BT_AURX_IRQn        = 34,
    BT_AUTX_IRQn        = 35,
    BT_TIMER_IRQn       = 36,
    BT_PLAY_EN_IRQn     = 37,
    ZIGBEE_IRQn         = 38,
    SEC_VIOLATION_IRQn  = 39,
    BUS_ERR_IRQn        = 40,
    MEM_ILLEGAL_IRQn    = 41,
    PMU_IRQn            = 42,
    USB_32K_IRQn        = 43,
    ARGB_IRQn           = 44,
    KEYSCAN_IRQn        = 45,
    QDEC_IRQn           = 46,
    RAMBOZ_IRQn         = 47,
    LED_IRQn            = 48,
    AIO_IRQn            = 49,
    IRTX_IRQn           = 50,
    IRRX_IRQn           = 51,
    CM33_reserved0_IRQn = 52,
    IRQ_NUMBER_MAX      = CONFIG_NUM_IRQS
} IRQn_Type;

/*!< ARM Cortex-M33 processor and core peripherals */
#include <core_cm33.h>

/* !!! NOTE !!!
 * Do not modify the definition order of header files here, otherwise there will be many builds
 * !!! NOTE !!!
 */

#define FLASH_MEMORY_BASE               (uint32_t)(DT_REG_ADDR_BY_IDX(DT_NODELABEL(flash0), 0))
#define FLASH_MEMORY_LENGTH             (uint32_t)(DT_REG_SIZE_BY_IDX(DT_NODELABEL(flash0), 0))

/* The jump address defined in this way cannot be modified,
 * and a service similar to Partition Table is needed to
 * actually parse the partition address and length.
 */
#define PARTITION_TABLE_BASE            FLASH_MEMORY_BASE + (uint32_t)(DT_REG_ADDR_BY_IDX(DT_NODELABEL(partiton_table), 0))
#define PARTITION_TABLE_LENGTH          (uint32_t)(DT_REG_SIZE_BY_IDX(DT_NODELABEL(partiton_table), 0))
#define PARTITION_TABLE_END             (PARTITION_TABLE_BASE + PARTITION_TABLE_LENGTH)

#define FACTORY_DATA_PARTITION_BASE     FLASH_MEMORY_BASE + (uint32_t)(DT_REG_ADDR_BY_IDX(DT_NODELABEL(factory_data), 0))
#define FACTORY_DATA_PARTITION_LENGTH   (uint32_t)(DT_REG_SIZE_BY_IDX(DT_NODELABEL(factory_data), 0))
#define FACTORY_DATA_PARTITION_END      (FACTORY_DATA_PARTITION_BASE + FACTORY_DATA_PARTITION_LENGTH)

#define BOOT_PARTITION_BASE             FLASH_MEMORY_BASE + (uint32_t)(DT_REG_ADDR_BY_IDX(DT_NODELABEL(boot_partition), 0))
#define BOOT_PARTITION_LENGTH           (uint32_t)(DT_REG_SIZE_BY_IDX(DT_NODELABEL(boot_partition), 0))
#define BOOT_PARTITION_END              (BOOT_PARTITION_BASE + BOOT_PARTITION_LENGTH)

#define SLOT0_PARTITION_BASE            FLASH_MEMORY_BASE + (uint32_t)(DT_REG_ADDR_BY_IDX(DT_NODELABEL(slot0_partition), 0))
#define SLOT0_PARTITION_LENGTH          (uint32_t)(DT_REG_SIZE_BY_IDX(DT_NODELABEL(slot0_partition), 0))
#define SLOT0_PARTITION_END             (SLOT0_PARTITION_BASE + SLOT0_PARTITION_LENGTH)

#if DT_NODE_EXISTS(DT_NODELABEL(slot1_partition))
#define SLOT1_PARTITION_BASE            FLASH_MEMORY_BASE + (uint32_t)(DT_REG_ADDR_BY_IDX(DT_NODELABEL(slot1_partition), 0))
#define SLOT1_PARTITION_LENGTH          (uint32_t)(DT_REG_SIZE_BY_IDX(DT_NODELABEL(slot1_partition), 0))
#define SLOT1_PARTITION_END             (SLOT1_PARTITION_BASE + SLOT1_PARTITION_LENGTH)
#endif

#define STORAGE_PARTITION_BASE          FLASH_MEMORY_BASE + (uint32_t)(DT_REG_ADDR_BY_IDX(DT_NODELABEL(storage_partition), 0))
#define STORAGE_PARTITION_LENGTH        (uint32_t)(DT_REG_SIZE_BY_IDX(DT_NODELABEL(storage_partition), 0))
#define STORAGE_PARTITION_END           (STORAGE_PARTITION_BASE + STORAGE_PARTITION_LENGTH)

#define CODE_PARTITION_BASE             FLASH_MEMORY_BASE + (uint32_t)(DT_REG_ADDR_BY_IDX(DT_CHOSEN(zephyr_code_partition), 0))
#define CODE_PARTITION_LENGTH           (uint32_t)(DT_REG_SIZE_BY_IDX(DT_CHOSEN(zephyr_code_partition), 0))
#define CODE_PARTITION_END              (CODE_PARTITION_BASE + CODE_PARTITION_LENGTH)


#define ROM_BASE                        FLASH_MEMORY_BASE
#define ROM_LENGTH                      FLASH_MEMORY_LENGTH
#define ROM_END                         (ROM_BASE + ROM_LENGTH)

#ifndef CONFIG_AIR_CACHE_MEMORY_SIZE
#define CONFIG_AIR_CACHE_MEMORY_SIZE 0
#endif /* CONFIG_AIR_CACHE_MEMORY_SIZE */

#define TCM_BASE                        (DT_REG_ADDR_BY_IDX(DT_NODELABEL(tcm), 0))
#define TCM_LENGTH                      (DT_REG_SIZE_BY_IDX(DT_NODELABEL(tcm), 0))
#define TCM_END                         (TCM_BASE + TCM_LENGTH)

#define BT_SYSRAM_BASE                  (DT_REG_ADDR_BY_IDX(DT_NODELABEL(ram_bt), 0))
#define BT_SYSRAM_LENGTH                (DT_REG_SIZE_BY_IDX(DT_NODELABEL(ram_bt), 0))
#define BT_SYSRAM_END                   (BT_SYSRAM_BASE + BT_SYSRAM_LENGTH)

#if DT_NODE_EXISTS(DT_NODELABEL(cross_core_ram))
    /* fixed address from device tree */
    #define CROSS_CORE_MEM_BASE         (DT_REG_ADDR_BY_IDX(DT_NODELABEL(cross_core_ram), 0))
    #define CROSS_CORE_MEM_LENGTH       (DT_REG_SIZE_BY_IDX(DT_NODELABEL(cross_core_ram), 0))
    #define CROSS_CORE_MEM_END          (CROSS_CORE_MEM_BASE + CROSS_CORE_MEM_LENGTH)
#else
    /* dynamic address from symbols in memory map */
    extern uint32_t _cross_core_mem_zi_data_start;
    extern uint32_t _cross_core_mem_size;

    /* special way for using symbols in memory map */
    #define CROSS_CORE_MEM_BASE         (uint32_t)(&_cross_core_mem_zi_data_start)
    #define CROSS_CORE_MEM_LENGTH       (uint32_t)(&_cross_core_mem_size)
    #define CROSS_CORE_MEM_END          (CROSS_CORE_MEM_BASE + CROSS_CORE_MEM_LENGTH)
#endif

#define RISCV_SRAM_BASE                 (DT_REG_ADDR_BY_IDX(DT_NODELABEL(riscv_sram), 0))
#define RISCV_SRAM_LENGTH               (DT_REG_SIZE_BY_IDX(DT_NODELABEL(riscv_sram), 0))
#define RISCV_SRAM_END                  (RISCV_SRAM_BASE + RISCV_SRAM_LENGTH)


void sys_wdt_feed(void);


#endif /* __AIR_SOC_H__ */