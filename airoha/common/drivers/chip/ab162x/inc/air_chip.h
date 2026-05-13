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

#ifndef __AIR_CHIP_H__
#define __AIR_CHIP_H__

#ifdef __cplusplus
extern "C" {
#endif


#if defined(CORE_MCU)

    #include "version.h"                    /* add for KERNELVERSION */

    #if KERNELVERSION == 0x3030000
        /* !!! NOTE !!!
        * Do not modify the definition order of header files here, otherwise there will be many builds
        * !!! NOTE !!!
        */
        #include <zephyr/arch/arm/aarch32/cortex_m/cmsis.h>
        #include "core_cm33.h"                           /*!< ARM Cortex-M33 processor and core peripherals */
    #endif /* KERNELVERSION == 0x3030000 */

    #include "soc.h"
    #include <zephyr/sys/__assert.h>
    #include <zephyr/sys/printk.h>
    #include <zephyr/toolchain/common.h>

    typedef IRQn_Type hal_nvic_irq_t;

    #define NVIC_PRIORITYGROUP_0         0x7 /*!< 0 bits for pre-emption priority   8 bits for subpriority */
    #define NVIC_PRIORITYGROUP_1         0x6 /*!< 1 bits for pre-emption priority   7 bits for subpriority */
    #define NVIC_PRIORITYGROUP_2         0x5 /*!< 2 bits for pre-emption priority   6 bits for subpriority */
    #define NVIC_PRIORITYGROUP_3         0x4 /*!< 3 bits for pre-emption priority   5 bits for subpriority */
    #define NVIC_PRIORITYGROUP_4         0x3 /*!< 4 bits for pre-emption priority   4 bits for subpriority */
    #define NVIC_PRIORITYGROUP_5         0x2 /*!< 5 bits for pre-emption priority   3 bits for subpriority */
    #define NVIC_PRIORITYGROUP_6         0x1 /*!< 6 bits for pre-emption priority   2 bits for subpriority */
    #define NVIC_PRIORITYGROUP_7         0x0 /*!< 7 bits for pre-emption priority   1 bits for subpriority */


    #if (defined(CONFIG_GEN_ISR_TABLES)) && (defined(CONFIG_GEN_SW_ISR_TABLE))
        #error "Features that are not compatible with Airoha SDK !"
    #else
        #define ISR_REGISTER(IRQ_NAME, ISR_CB) hal_nvic_register_isr_handler(IRQ_NAME##_IRQn, ISR_CB)
    #endif

    /* ================================================== */

    #ifdef AIR_CPU_IN_SECURITY_MODE

        /* Hans' suppport (only porting AIR_CPU_IN_SECURITY_MODE)*/
        /* PD CMSYS AHB Peripheral */
        #define CMSYS_CFG_BASE       0xE0100000 /*cmsys_cfg*/
        #define CMSYS_MBIST_BASE     0xE0110000 /*cmsys_mbist*/
        #define CMSYS_CFG_EXT_BASE   0xE00FE000 /*cmsys_cfg_ext*/

        #define CONSYS_CFG_BASE      0xA0010000
        #define MODEM_CFG_BASE       0xA1100000
        #define ZB_CFG_BASE          0xA0060000
        #define RF_CFG_BASE          0xA2001000
        #define CONSYS_SLP_BASE      0xA0000000
        #define CONSYS_RTC_BASE      0x42106000

        #define CONSYS_CFG_SIZE      0x1000
        #define MODEM_CFG_SIZE       0x1300
        #define ZB_CFG_SIZE          0x2000
        #define RF_CFG_SIZE          0x1F00
        #define CONSYS_SLP_SIZE      0x800
        #define CONSYS_RTC_SIZE      0x20

        /*End of Hans' suppport */

        #define OS_GPT_BASE                             DT_REG_ADDR_BY_IDX(DT_NODELABEL(os_timer), 0)
        #define OS_GPT_SIZE                             DT_REG_SIZE_BY_IDX(DT_NODELABEL(os_timer), 0)
        #define CMSYS_L1CACHE_BASE                      DT_REG_ADDR_BY_IDX(DT_NODELABEL(cache_controller), 0)
        #define CMSYS_L1CACHE_SIZE                      DT_REG_SIZE_BY_IDX(DT_NODELABEL(cache_controller), 0)
        #define SFC_BASE                                DT_REG_ADDR_BY_IDX(DT_NODELABEL(flash_controller), 0)
        #define SFC_SIZE                                DT_REG_SIZE_BY_IDX(DT_NODELABEL(flash_controller), 0)
        #define TOP_MISC_CFG_BASE                       DT_REG_ADDR_BY_IDX(DT_NODELABEL(misc_peripheral), 0)
        #define TOP_MISC_CFG_SIZE                       DT_REG_SIZE_BY_IDX(DT_NODELABEL(misc_peripheral), 0)
        #define TOP_MISC_CFG_1_BASE                     DT_REG_ADDR_BY_IDX(DT_NODELABEL(misc_peripheral), 1)
        #define TOP_MISC_CFG_1_SIZE                     DT_REG_SIZE_BY_IDX(DT_NODELABEL(misc_peripheral), 1)
        #define ABB_CFG_BASE                            DT_REG_ADDR_BY_IDX(DT_NODELABEL(misc_peripheral), 2)
        #define ABB_CFG_SIZE                            DT_REG_SIZE_BY_IDX(DT_NODELABEL(misc_peripheral), 2)
        #define MCU_CFG_PRI_BASE                        DT_REG_ADDR_BY_IDX(DT_NODELABEL(misc_peripheral), 3)
        #define MCU_CFG_PRI_SIZE                        DT_REG_SIZE_BY_IDX(DT_NODELABEL(misc_peripheral), 3)
        #define INFRA_MISC_CFG_BASE                     DT_REG_ADDR_BY_IDX(DT_NODELABEL(misc_peripheral), 4)
        #define INFRA_MISC_CFG_SIZE                     DT_REG_SIZE_BY_IDX(DT_NODELABEL(misc_peripheral), 4)
        #define SECURITY_TOP_BASE                       DT_REG_ADDR_BY_IDX(DT_NODELABEL(misc_peripheral), 5)
        #define SECURITY_TOP_SIZE                       DT_REG_SIZE_BY_IDX(DT_NODELABEL(misc_peripheral), 5)
        #define SECURITY_AO_BASE                        DT_REG_ADDR_BY_IDX(DT_NODELABEL(misc_peripheral), 6)
        #define SECURITY_AO_SIZE                        DT_REG_SIZE_BY_IDX(DT_NODELABEL(misc_peripheral), 6)
        #define SECURITY_PD_BASE                        DT_REG_ADDR_BY_IDX(DT_NODELABEL(misc_peripheral), 7)
        #define SECURITY_PD_SIZE                        DT_REG_SIZE_BY_IDX(DT_NODELABEL(misc_peripheral), 7)
        #define SECURITY_PERI_BASE                      DT_REG_ADDR_BY_IDX(DT_NODELABEL(misc_peripheral), 8)
        #define SECURITY_PERI_SIZE                      DT_REG_SIZE_BY_IDX(DT_NODELABEL(misc_peripheral), 8)
        #define WDT_BASE                                DT_REG_ADDR_BY_IDX(DT_NODELABEL(wdt0), 0)
        #define WDT_SIZE                                DT_REG_SIZE_BY_IDX(DT_NODELABEL(wdt0), 0)
        #define RGU_BASE                                WDT_BASE
        #define AIR_DMA_DT_NODE                         DT_NODELABEL(dma)
        #define AIR_DMA_PROP(prop, idx)                 DT_PROP_BY_IDX(AIR_DMA_DT_NODE, prop, idx)
        #define DMA_0_BASE                              AIR_DMA_PROP(dma_ch_base, 0)        /* DMA Controller */
        #define DMA_0_SIZE                              AIR_DMA_PROP(dma_ch_length, 0)      /* DMA Controller */
        #define DMA_1_BASE                              AIR_DMA_PROP(dma_ch_base, 1)        /* DMA Controller */
        #define DMA_1_SIZE                              AIR_DMA_PROP(dma_ch_length, 1)      /* DMA Controller */
        #define UART_DMA_0_BASE                         AIR_DMA_PROP(dma_ch_base, 2)        /* UART_0 DMA Controller */
        #define UART_DMA_0_SIZE                         AIR_DMA_PROP(dma_ch_length, 2)      /* UART_0 DMA Controller */
        #define UART_DMA_1_BASE                         AIR_DMA_PROP(dma_ch_base, 3)        /* UART_1 DMA Controller */
        #define UART_DMA_1_SIZE                         AIR_DMA_PROP(dma_ch_length, 3)      /* UART_1 DMA Controller */
        #define UART_DMA_2_BASE                         AIR_DMA_PROP(dma_ch_base, 4)        /* UART_2 DMA Controller */
        #define UART_DMA_2_SIZE                         AIR_DMA_PROP(dma_ch_length, 4)      /* UART_2 DMA Controller */
        #define I3C0_PDMA_BASE                          AIR_DMA_PROP(dma_ch_base, 5)        /* I3C0 PDMA */
        #define I3C0_PDMA_SIZE                          AIR_DMA_PROP(dma_ch_length, 5)      /* I3C0 PDMA */
        #define I3C1_PDMA_BASE                          AIR_DMA_PROP(dma_ch_base, 6)        /* I3C1 PDMA */
        #define I3C1_PDMA_SIZE                          AIR_DMA_PROP(dma_ch_length, 6)      /* I3C1 PDMA */
        #define MCU_IRQ_GEN_BASE                        DT_REG_ADDR_BY_IDX(DT_NODELABEL(irq_gen), 0)
        #define MCU_IRQ_GEN_SIZE                        DT_REG_SIZE_BY_IDX(DT_NODELABEL(irq_gen), 0)
        #define RISCV_IRQ_GEN_BASE                      DT_REG_ADDR_BY_IDX(DT_NODELABEL(irq_gen), 1)
        #define RISCV_IRQ_GEN_SIZE                      DT_REG_SIZE_BY_IDX(DT_NODELABEL(irq_gen), 1)
        #define ESC_BASE                                DT_REG_ADDR_BY_IDX(DT_NODELABEL(esc), 0)
        #define TRNG_BASE                               DT_REG_ADDR_BY_IDX(DT_NODELABEL(trng), 0)
        #define HW_SEMAPHORE_BASE                       DT_REG_ADDR_BY_IDX(DT_NODELABEL(hw_semaphore), 0)
        #define HW_SEMAPHORE_SIZE                       DT_REG_SIZE_BY_IDX(DT_NODELABEL(hw_semaphore), 0)

        #define I2C_0_BASE                              DT_REG_ADDR_BY_IDX(DT_NODELABEL(i2c0), 0)
        #define I2C_1_BASE                              DT_REG_ADDR_BY_IDX(DT_NODELABEL(i2c1), 0)
        #define GPIO_BASE                               DT_REG_ADDR_BY_IDX(DT_NODELABEL(gpio0), 0)
        #define IO_CFG_0_BASE                           DT_REG_ADDR_BY_IDX(DT_NODELABEL(gpio0), 1)
        #define IO_CFG_1_BASE                           DT_REG_ADDR_BY_IDX(DT_NODELABEL(gpio0), 2)
        #define SPI_MASTER_0_BASE                       DT_REG_ADDR_BY_IDX(DT_NODELABEL(spim0), 0)
        #define SPI_MASTER_1_BASE                       DT_REG_ADDR_BY_IDX(DT_NODELABEL(spim1), 0)
        #define SPI_MASTER_2_BASE                       DT_REG_ADDR_BY_IDX(DT_NODELABEL(spim2), 0)
        #define SPI_SLAVE_BASE                          DT_REG_ADDR_BY_IDX(DT_NODELABEL(spis), 0)
        #define SPI_SLAVE_PAD_BASE                      DT_REG_ADDR_BY_IDX(DT_NODELABEL(spis_pad), 0)
        #define SPI_SLAVE_BYPASS_BASE                   DT_REG_ADDR_BY_IDX(DT_NODELABEL(spis_bypass), 0)  /*SPI_SLAVE_BYPASS*/
        #define IRRX_BASE                               DT_REG_ADDR_BY_IDX(DT_NODELABEL(irrx), 0)
        #define IRTX_BASE                               DT_REG_ADDR_BY_IDX(DT_NODELABEL(irtx), 0)
        #define LED_BASE                                DT_REG_ADDR_BY_IDX(DT_NODELABEL(led), 0)
        #define ARGB_BASE                               DT_REG_ADDR_BY_IDX(DT_NODELABEL(argb), 0)
        #define PWM0_BASE                               DT_REG_ADDR_BY_IDX(DT_NODELABEL(pwm0), 0)
        #define PWM1_BASE                               DT_REG_ADDR_BY_IDX(DT_NODELABEL(pwm1), 0)
        #define PWM2_BASE                               DT_REG_ADDR_BY_IDX(DT_NODELABEL(pwm2), 0)
        #define PWM_DMA0_BASE                           DT_REG_ADDR_BY_IDX(DT_NODELABEL(pwm_dma0), 0)
        #define PWM_DMA1_BASE                           DT_REG_ADDR_BY_IDX(DT_NODELABEL(pwm_dma1), 0)
        #define GPT_BASE                                DT_REG_ADDR_BY_IDX(DT_NODELABEL(gpt), 0) /*General Purpose Timer */
        #define GPT_SIZE                                DT_REG_SIZE_BY_IDX(DT_NODELABEL(gpt), 0) /*General Purpose Timer */
        #define RTC_BASE                                DT_REG_ADDR_BY_IDX(DT_NODELABEL(rtc), 0) /*General Purpose Timer */
        #define IRRX_SIZE                               DT_REG_SIZE_BY_IDX(DT_NODELABEL(irrx), 0)
        #define IRTX_SIZE                               DT_REG_SIZE_BY_IDX(DT_NODELABEL(irtx), 0)
        #define LED_SIZE                                DT_REG_SIZE_BY_IDX(DT_NODELABEL(led), 0)
        #define ARGB_SIZE                               DT_REG_SIZE_BY_IDX(DT_NODELABEL(argb), 0)
        #define UART0_SIZE                              DT_REG_SIZE_BY_IDX(DT_NODELABEL(uart0), 0)
        #define UART1_SIZE                              DT_REG_SIZE_BY_IDX(DT_NODELABEL(uart1), 0)
        #define UART2_SIZE                              DT_REG_SIZE_BY_IDX(DT_NODELABEL(uart2), 0)
        #define QDEC_SIZE                               DT_REG_SIZE_BY_IDX(DT_NODELABEL(qdec), 0)
        #define RAMBOZ_SIZE                             DT_REG_SIZE_BY_IDX(DT_NODELABEL(ramboz), 0)
        #define HW_KEYSCAN_SIZE                         DT_REG_SIZE_BY_IDX(DT_NODELABEL(hw_keyscan), 0)
        #define GPIO_SIZE                               DT_REG_SIZE_BY_IDX(DT_NODELABEL(gpio0), 0)
        #define IO_CFG_0_SIZE                           DT_REG_SIZE_BY_IDX(DT_NODELABEL(gpio0), 1)
        #define IO_CFG_1_SIZE                           DT_REG_SIZE_BY_IDX(DT_NODELABEL(gpio0), 2)
        #define RTC_SIZE                                DT_REG_SIZE_BY_IDX(DT_NODELABEL(rtc), 0)
        #define PWM0_SIZE                               DT_REG_SIZE_BY_IDX(DT_NODELABEL(pwm0), 0)
        #define PWM1_SIZE                               DT_REG_SIZE_BY_IDX(DT_NODELABEL(pwm1), 0)
        #define PWM2_SIZE                               DT_REG_SIZE_BY_IDX(DT_NODELABEL(pwm2), 0)
        #define PWM_DMA0_SIZE                           DT_REG_SIZE_BY_IDX(DT_NODELABEL(pwm_dma0), 0)
        #define PWM_DMA1_SIZE                           DT_REG_SIZE_BY_IDX(DT_NODELABEL(pwm_dma1), 0)
        #define UART0_BASE                              DT_REG_ADDR_BY_IDX(DT_NODELABEL(uart0), 0)
        #define UART1_BASE                              DT_REG_ADDR_BY_IDX(DT_NODELABEL(uart1), 0)
        #define UART2_BASE                              DT_REG_ADDR_BY_IDX(DT_NODELABEL(uart2), 0)
        #define HW_KEYSCAN_BASE                         DT_REG_ADDR_BY_IDX(DT_NODELABEL(hw_keyscan), 0)
        #define QDEC_BASE                               DT_REG_ADDR_BY_IDX(DT_NODELABEL(qdec), 0)
        #define RAMBOZ_BASE                             DT_REG_ADDR_BY_IDX(DT_NODELABEL(ramboz), 0)
        #define SPM_CFG_BASE                            DT_REG_ADDR_BY_IDX(DT_NODELABEL(spmcfg), 0)
        #define SPM_CFG_SIZE                            DT_REG_SIZE_BY_IDX(DT_NODELABEL(spmcfg), 0)
        #define SPM_TOP_BASE                            DT_REG_ADDR_BY_IDX(DT_NODELABEL(spmtop), 0)
        #define SRAM_PWR_CTRL                           DT_REG_ADDR_BY_IDX(DT_NODELABEL(srampwrctrl), 0)
        #define CKSYS_BASE                              DT_REG_ADDR_BY_IDX(DT_NODELABEL(clock_node_label), 0)
        #define CKSYS_XO_CLK_BASE                       DT_REG_ADDR_BY_IDX(DT_NODELABEL(clock_node_label), 1)
        #define CKSYS_BUS_CLK_BASE                      DT_REG_ADDR_BY_IDX(DT_NODELABEL(clock_node_label), 2)
        #define MIXEDSYS_D_BASE                         DT_REG_ADDR_BY_IDX(DT_NODELABEL(clock_node_label), 3)
        #define DCXO_PWR_CTRL_BASE                      DT_REG_ADDR_BY_IDX(DT_NODELABEL(clock_node_label), 4)
        #define DCXO_CFG_BASE                           DT_REG_ADDR_BY_IDX(DT_NODELABEL(clock_node_label), 5)
        #define RTC_DIG_MISC_BASE                       DT_REG_ADDR_BY_IDX(DT_NODELABEL(clock_node_label), 6)
        #define SARADC_BASE                             DT_REG_ADDR_BY_IDX(DT_NODELABEL(saradc0), 0)
        #define PMU_BASE                                DT_REG_ADDR_BY_IDX(DT_NODELABEL(pmu), 0)
        #define PMU_SIZE                                DT_REG_SIZE_BY_IDX(DT_NODELABEL(pmu), 0)
        #define AIOADC_BASE                             DT_REG_ADDR_BY_IDX(DT_NODELABEL(sdadc0), 0)
    #else /* AIR_CPU_IN_SECURITY_MODE */
        #error "Build environment may error !"
    #endif /* AIR_CPU_IN_SECURITY_MODE */


    /* !!! NOTE !!!
    * Because the hardware may not have power, dumping these registers
    * may cause problems with the exception flow, so temporarily remove them.
    * {"i2s_dma", (unsigned int *)(I2S_DMA_BASE), (unsigned int *)(I2S_DMA_BASE + 0x110), 1}, \
    */

    #define HAL_DUMP_MODULE_REGISTER_ENABLE
    /*add your module here only dump RG that not read-update.
    *  Example:  {"<module_name>", <dump_start_address>, <dump_stop_address>, 1},
    *
    */
    #define HAL_DUMP_PERIPHERAL_REGISTER  \
            {"os_timer"          ,   (unsigned int *)(OS_GPT_BASE                 ),   (unsigned int *)(OS_GPT_BASE          + OS_GPT_SIZE                ),  1}, \
            {"gpt"               ,   (unsigned int *)(GPT_BASE                    ),   (unsigned int *)(GPT_BASE             + GPT_SIZE                   ),  1}, \
            {"wdt0"              ,   (unsigned int *)(WDT_BASE                    ),   (unsigned int *)(WDT_BASE             + WDT_SIZE                   ),  1}, \
            {"gdma0"             ,   (unsigned int *)(DMA_0_BASE                  ),   (unsigned int *)(DMA_0_BASE           + DMA_0_SIZE                 ),  1}, \
            {"gdma1"             ,   (unsigned int *)(DMA_1_BASE                  ),   (unsigned int *)(DMA_1_BASE           + DMA_1_SIZE                 ),  1}, \
            {"vdma0"             ,   (unsigned int *)(UART_DMA_0_BASE             ),   (unsigned int *)(UART_DMA_0_BASE      + UART_DMA_0_SIZE            ),  1}, \
            {"vdma1"             ,   (unsigned int *)(UART_DMA_1_BASE             ),   (unsigned int *)(UART_DMA_1_BASE      + UART_DMA_1_SIZE            ),  1}, \
            {"vdma2"             ,   (unsigned int *)(UART_DMA_2_BASE             ),   (unsigned int *)(UART_DMA_2_BASE      + UART_DMA_2_SIZE            ),  1}, \
            {"mcu_irq_gen"       ,   (unsigned int *)(MCU_IRQ_GEN_BASE            ),   (unsigned int *)(MCU_IRQ_GEN_BASE     + MCU_IRQ_GEN_SIZE           ),  1}, \
            {"riscv_irq_gen"     ,   (unsigned int *)(RISCV_IRQ_GEN_BASE          ),   (unsigned int *)(RISCV_IRQ_GEN_BASE   + RISCV_IRQ_GEN_SIZE         ),  1}, \
            {"hw_semaphore"      ,   (unsigned int *)(HW_SEMAPHORE_BASE           ),   (unsigned int *)(HW_SEMAPHORE_BASE    + HW_SEMAPHORE_SIZE          ),  1}, \
            {"cache"             ,   (unsigned int *)(CMSYS_L1CACHE_BASE          ),   (unsigned int *)(CMSYS_L1CACHE_BASE   + CMSYS_L1CACHE_SIZE         ),  1}, \
            {"sfc"               ,   (unsigned int *)(SFC_BASE                    ),   (unsigned int *)(SFC_BASE             + SFC_SIZE                   ),  1}, \
            {"btcon"             ,   (unsigned int *)(CONSYS_CFG_BASE             ),   (unsigned int *)(CONSYS_CFG_BASE      + CONSYS_CFG_SIZE            ),  1}, \
            {"modem"             ,   (unsigned int *)(MODEM_CFG_BASE              ),   (unsigned int *)(MODEM_CFG_BASE       + MODEM_CFG_SIZE             ),  1}, \
            {"zigbee"            ,   (unsigned int *)(ZB_CFG_BASE                 ),   (unsigned int *)(ZB_CFG_BASE          + ZB_CFG_SIZE                ),  1}, \
            {"rf"                ,   (unsigned int *)(RF_CFG_BASE                 ),   (unsigned int *)(RF_CFG_BASE          + RF_CFG_SIZE                ),  1}, \
            {"btcon_slp"         ,   (unsigned int *)(CONSYS_SLP_BASE             ),   (unsigned int *)(CONSYS_SLP_BASE      + CONSYS_SLP_SIZE            ),  1}, \
            {"btcon_rtc"         ,   (unsigned int *)(CONSYS_RTC_BASE             ),   (unsigned int *)(CONSYS_RTC_BASE      + CONSYS_RTC_SIZE            ),  1}, \
            {"spm_cfg"           ,   (unsigned int *)(SPM_CFG_BASE                ),   (unsigned int *)(SPM_CFG_BASE         + SPM_CFG_SIZE               ),  1}, \
            {"cksys"             ,   (unsigned int *)(CKSYS_BASE           + 0x20 ),   (unsigned int *)(CKSYS_BASE           + 0x34                       ),  1}, \
            {"cksys_xo"          ,   (unsigned int *)(CKSYS_XO_CLK_BASE           ),   (unsigned int *)(CKSYS_XO_CLK_BASE    + 0x14                       ),  1}, \
            {"cksys_bus"         ,   (unsigned int *)(CKSYS_BUS_CLK_BASE   + 0x18 ),   (unsigned int *)(CKSYS_BUS_CLK_BASE   + 0x2C                       ),  1}, \
            {"dcxo_pwr_ctrl"     ,   (unsigned int *)(DCXO_PWR_CTRL_BASE   + 0x14 ),   (unsigned int *)(DCXO_PWR_CTRL_BASE   + 0x18                       ),  1}, \
            {"rtc_dig_misc"      ,   (unsigned int *)(RTC_DIG_MISC_BASE    + 0x8  ),   (unsigned int *)(RTC_DIG_MISC_BASE    + 0x2C                       ),  1}, \
            {"mixedsys_d"        ,   (unsigned int *)(MIXEDSYS_D_BASE      + 0x1C ),   (unsigned int *)(MIXEDSYS_D_BASE      + 0x20                       ),  1}, \
            {"spi_master0"       ,   (unsigned int *)(SPI_MASTER_0_BASE           ),   (unsigned int *)(SPI_MASTER_0_BASE    + 0x3C                       ),  1}, \
            {"spi_master1"       ,   (unsigned int *)(SPI_MASTER_1_BASE           ),   (unsigned int *)(SPI_MASTER_1_BASE    + 0x3C                       ),  1}, \
            {"spi_master2"       ,   (unsigned int *)(SPI_MASTER_2_BASE           ),   (unsigned int *)(SPI_MASTER_2_BASE    + 0x3C                       ),  1}, \
            {"top_misc_cfg"      ,   (unsigned int *)(TOP_MISC_CFG_BASE           ),   (unsigned int *)(TOP_MISC_CFG_BASE    + TOP_MISC_CFG_SIZE          ),  1}, \
            {"top_misc_cfg1"     ,   (unsigned int *)(TOP_MISC_CFG_1_BASE         ),   (unsigned int *)(TOP_MISC_CFG_1_BASE  + TOP_MISC_CFG_1_SIZE        ),  1}, \
            {"uart0"             ,   (unsigned int *)(UART0_BASE                  ),   (unsigned int *)(UART0_BASE           + UART0_SIZE                 ),  1}, \
            {"uart1"             ,   (unsigned int *)(UART1_BASE                  ),   (unsigned int *)(UART1_BASE           + UART1_SIZE                 ),  1}, \
            {"uart2"             ,   (unsigned int *)(UART2_BASE                  ),   (unsigned int *)(UART2_BASE           + UART2_SIZE                 ),  1}, \
            {"qdec"              ,   (unsigned int *)(QDEC_BASE                   ),   (unsigned int *)(QDEC_BASE            + QDEC_SIZE                  ),  1}, \
            {"ramboz"            ,   (unsigned int *)(RAMBOZ_BASE                 ),   (unsigned int *)(RAMBOZ_BASE          + RAMBOZ_SIZE                ),  1}, \
            {"hw_keyscan"        ,   (unsigned int *)(HW_KEYSCAN_BASE             ),   (unsigned int *)(HW_KEYSCAN_BASE      + HW_KEYSCAN_SIZE            ),  1}, \
            {"gpio"              ,   (unsigned int *)(GPIO_BASE                   ),   (unsigned int *)(GPIO_BASE            + GPIO_SIZE                  ),  1}, \
            {"io_cfg_0"          ,   (unsigned int *)(IO_CFG_0_BASE               ),   (unsigned int *)(IO_CFG_0_BASE        + IO_CFG_0_SIZE              ),  1}, \
            {"io_cfg_1"          ,   (unsigned int *)(IO_CFG_1_BASE               ),   (unsigned int *)(IO_CFG_1_BASE        + IO_CFG_1_SIZE              ),  1}, \
            {"abb_cfg"           ,   (unsigned int *)(ABB_CFG_BASE                ),   (unsigned int *)(ABB_CFG_BASE         + ABB_CFG_SIZE               ),  1}, \
            {"mcu_cfg_pri"       ,   (unsigned int *)(MCU_CFG_PRI_BASE            ),   (unsigned int *)(MCU_CFG_PRI_BASE     + MCU_CFG_PRI_SIZE           ),  1}, \
            {"infra_misc_cfg"    ,   (unsigned int *)(INFRA_MISC_CFG_BASE         ),   (unsigned int *)(INFRA_MISC_CFG_BASE  + INFRA_MISC_CFG_SIZE        ),  1}, \
            {"rtc"               ,   (unsigned int *)(RTC_BASE                    ),   (unsigned int *)(RTC_BASE             + RTC_SIZE                   ),  1}, \
            {"pwm0"              ,   (unsigned int *)(PWM0_BASE                   ),   (unsigned int *)(PWM0_BASE            + PWM0_SIZE                  ),  1}, \
            {"pwm1"              ,   (unsigned int *)(PWM1_BASE                   ),   (unsigned int *)(PWM1_BASE            + PWM1_SIZE                  ),  1}, \
            {"pwm2"              ,   (unsigned int *)(PWM2_BASE                   ),   (unsigned int *)(PWM2_BASE            + PWM2_SIZE                  ),  1}, \
            {"pwmdma0"           ,   (unsigned int *)(PWM_DMA0_BASE               ),   (unsigned int *)(PWM_DMA0_BASE        + PWM_DMA0_SIZE              ),  1}, \
            {"pwmdma1"           ,   (unsigned int *)(PWM_DMA1_BASE               ),   (unsigned int *)(PWM_DMA1_BASE        + PWM_DMA1_SIZE              ),  1}, \
            {"argb"              ,   (unsigned int *)(ARGB_BASE                   ),   (unsigned int *)(ARGB_BASE            + ARGB_SIZE                  ),  1}, \
            {"irtx"              ,   (unsigned int *)(IRTX_BASE                   ),   (unsigned int *)(IRTX_BASE            + IRTX_SIZE                  ),  1}, \
            {"irrx"              ,   (unsigned int *)(IRRX_BASE                   ),   (unsigned int *)(IRRX_BASE            + IRRX_SIZE                  ),  1}, \
            {"pmu"               ,   (unsigned int *)(PMU_BASE                    ),   (unsigned int *)(PMU_BASE             + PMU_SIZE                   ),  1},

#else
    #define __I                                     volatile const       /*!< Defines 'read only' permissions */
    #define __O                                     volatile             /*!< Defines 'write only' permissions */
    #define __IO                                    volatile             /*!< Defines 'read / write' permissions */

    typedef enum IRQn{
        SW_IRQn                      = 3,
        LED_IRQn                     = 7,
        QDEC_IRQn                    = 11,
        KEYSCAN_IRQn                 = 16,
        UART_IRQn                    = 17,
        SPI_MST1_IRQn                = 18,
        RTC_IRQn                     = 19,
        GPT_IRQn                     = 20,
        UART_DMA_IRQn                = 21,
        PMU_IRQn                     = 22,
        MCU_DMA_IRQn                 = 23,
        EINT_IRQn                    = 24,
        I3C0_IRQn                    = 25,
        I3C0_DMA_IRQn                = 26,
        SPI_MST0_IRQn                = 27,
        IRQ_GEN_IRQn                = 28,
        USB_IRQn                     = 29,
        BT_IRQn                     = 30,
        IRQ_NUMBER_MAX
    } IRQn_Type;

    typedef IRQn_Type hal_nvic_irq_t;

    #define OS_GPT_BASE                             0x42170000
    #define CMSYS_L1CACHE_BASE                      0xE0180000
    #define SFC_BASE                                0x40080000
    #define TOP_MISC_CFG_BASE                       0x42010000
    #define TOP_MISC_CFG_1_BASE                     0x42020000
    #define ABB_CFG_BASE                            0x42080000
    #define MCU_CFG_PRI_BASE                        0x422e0000
    #define INFRA_MISC_CFG_BASE                     0x422f0000
    #define SECURITY_TOP_BASE                       0x42300000
    #define SECURITY_AO_BASE                        0x42310000
    #define SECURITY_PD_BASE                        0x40000000
    #define SECURITY_PERI_BASE                      0x43000000
    #define WDT_BASE                                0x42090000
    #define RGU_BASE                                WDT_BASE
    #define DMA_0_BASE                              0x40040000        /* DMA Controller */
    #define DMA_1_BASE                              0x42230000        /* DMA Controller */
    #define UART_DMA_0_BASE                         0x42270000        /* UART_0 DMA Controller */
    #define UART_DMA_1_BASE                         0x42280000        /* UART_1 DMA Controller */
    #define UART_DMA_2_BASE                         0x42290000        /* UART_2 DMA Controller */
    #define I3C0_PDMA_BASE                          0x42220000        /* I3C0 PDMA */
    #define I3C1_PDMA_BASE                          0x400F0000        /* I3C1 PDMA */
    #define MCU_IRQ_GEN_BASE                        0x422b0000
    #define RISCV_IRQ_GEN_BASE                      0x422c0000
    #define ESC_BASE                                0x40090000
    #define TRNG_BASE                               0x40030000
    #define HW_SEMAPHORE_BASE                       0x422A0000

    #define I2C_0_BASE                              0x42210000
    #define I2C_1_BASE                              0x400e0000
    #define GPIO_BASE                               0x420b0000
    #define IO_CFG_0_BASE                           0x420c0000
    #define IO_CFG_1_BASE                           0x420d0000
    #define SPI_MASTER_0_BASE                       0x421f0000
    #define SPI_MASTER_1_BASE                       0x42200000
    #define SPI_MASTER_2_BASE                       0x400a0000
    #define SPI_SLAVE_BASE                          0x400b0000
    #define SPI_SLAVE_PAD_BASE                      0x420e0000
    #define SPI_SLAVE_BYPASS_BASE                   0xDEADBEEF /* need CODA */
    #define IRRX_BASE                               0x40060000
    #define IRTX_BASE                               0x40050000
    #define LED_BASE                                0x42105000
    #define GPT_BASE                                0x42150000 /*General Purpose Timer */
    #define RTC_BASE                                0x42100000
    #define UART0_BASE                              0x42240000
    #define UART1_BASE                              0x42250000
    #define UART2_BASE                              0x42260000
    #define HW_KEYSCAN_BASE                         0x421E0000
    #define QDEC_BASE                               0x42101000
    #define RAMBOZ_BASE                             0x42102000
    #define CKSYS_BASE                              0x42030000
    #define CKSYS_XO_CLK_BASE                       0x42040000
    #define CKSYS_BUS_CLK_BASE                      0x422d0000
    #define MIXEDSYS_D_BASE                         0x42050000
    #define DCXO_PWR_CTRL_BASE                      0x42060000
    #define DCXO_CFG_BASE                           0x400c0000
    #define RTC_DIG_MISC_BASE                       0x42107000
    #define SARADC_BASE                             0x400D0000
    #define PMU_BASE                                0x42108000
    #define AIOADC_BASE                             0x40070000
#endif /* #if defined(CORE_MCU) */

#include "reg_def/reg_def_of_irq_gen.h"
#include "reg_def/reg_def_of_misc_cfg.h"
#include "reg_def/reg_def_of_smph.h"
#include "reg_def/reg_def_of_uart.h"
#include "reg_def/reg_def_of_usb.h"
#include "reg_def/reg_def_of_sfc.h"
#include "reg_def/reg_def_of_esc.h"
#include "reg_def/reg_def_of_dma.h"
#include "reg_def/reg_def_of_gpt.h"
#include "reg_def/reg_def_of_rtc_timer.h"
#include "reg_def/reg_def_of_cache.h"
#include "reg_def/reg_def_of_adc.h"
#include "reg_def/reg_def_of_clock.h"
#include "reg_def/reg_def_of_spim.h"
#include "reg_def/reg_def_of_spis.h"
#include "reg_def/reg_def_of_eint.h"
#include "reg_def/reg_def_of_rtc.h"
#include "reg_def/reg_def_of_crypto.h"
#include "reg_def/reg_def_of_trng.h"
#include "reg_def/reg_def_of_rgu.h"
#include "reg_def/reg_def_of_pwm.h"
#include "reg_def/reg_def_of_pwm_dma.h"
#include "reg_def/reg_def_of_irrx.h"
#include "reg_def/reg_def_of_irtx.h"
#include "reg_def/reg_def_of_gpio.h"
#include "reg_def/reg_def_of_i3c.h"
#include "reg_def/reg_def_of_led_ctrl.h"
#include "reg_def/reg_def_of_hw_keyscan.h"
#include "reg_def/reg_def_of_qdec.h"
#include "reg_def/reg_def_of_argb.h"
#include "reg_def/reg_def_of_ramboz.h"
#include "reg_def/reg_def_of_spmcfg.h"
#include "reg_def/reg_def_of_spmtop.h"
#include "reg_def/reg_def_of_srampwrctrl.h"
#include "reg_def/reg_def_of_adc.h"
#include "reg_def/reg_def_of_aioadc.h"

/* structure type of CMSYS_CFG
 */
typedef struct {
    __IO uint32_t MISC1;
    __IO uint32_t STCALIB;
    __IO uint32_t AHB_SLAVE_WAY_EN;
    __IO uint32_t AHB_DEC_ERR_EN;
    __IO uint32_t AHB_SIDEBAND;
    __IO uint32_t AHB_BUFFERALBE;
    __IO uint32_t AHB_FIFO_TH;
    __IO uint32_t FORCE_IDLE_OFF;
    uint32_t RESERVED0[1];
    __IO uint32_t CG_FREERUN_EN;
    __IO uint32_t CG_GATE_EN;
    uint32_t RESERVED1[1];
    __IO uint32_t TCM_BUS_CTRL;
    __IO uint32_t INT_ACTIVE_HL0;
    __IO uint32_t INT_ACTIVE_HL1;
    uint32_t RESERVED2[1];
    __IO uint32_t DCM_CTRL_REG;
} CMSYS_CFG_REGISTER_T;

#define CMSYS_CFG   ((CMSYS_CFG_REGISTER_T *)CMSYS_CFG_BASE)

/* structure type of CMSYS_CFG_EXT
 */
typedef struct {
    __IO uint32_t CG_EN;
    __IO uint32_t DCM_EN;
} CMSYS_CFG_EXT_REGISTER_T;

#define CMSYS_CFG_EXT   ((CMSYS_CFG_EXT_REGISTER_T *)CMSYS_CFG_EXT_BASE)


#ifdef __cplusplus
}
#endif

#endif

