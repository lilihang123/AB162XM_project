/* Copyright Statement:
 *
 * (C) 2024  Airoha Technology Corp. All rights reserved.
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

// #if defined()

/* Includes ------------------------------------------------------------------*/
#include "hal_nvic.h"

#ifdef AIR_ONLINE_SWLA_ENABLE
#include "swla.h"
#endif

/* Private define ------------------------------------------------------------*/
const IRQ_INFO_t irq_info[IRQ_NUMBER_MAX] = {
    [SW_IRQn]             = { 3,  3,  "SW_IRQn" },
    [LED_IRQn]            = { 7,  7,  "LED" },
    [QDEC_IRQn]           = { 11, 11, "QDEC" },
    [KEYSCAN_IRQn]        = { 16, 16, "KEYSCAN" },
    [UART_IRQn]           = { 17, 17, "UART" },
    [SPI_MST1_IRQn]       = { 18, 18, "SPI_MST1" },
    [RTC_IRQn]            = { 19, 19, "RTC" },
    [GPT_IRQn]            = { 20, 20, "GPT" },
    [UART_DMA_IRQn]       = { 21, 21, "UART_DMA" },
    [PMU_IRQn]            = { 22, 22, "PMU" },
    [MCU_DMA_IRQn]        = { 23, 23, "MCU_DMA" },
    [EINT_IRQn]           = { 24, 24, "EINT" },
    [I3C0_IRQn]           = { 25, 25, "I3C0" },
    [I3C0_DMA_IRQn]       = { 26, 26, "I3C0_DMA" },
    [SPI_MST0_IRQn]       = { 27, 27, "SPI_MST0" },
    [IRQ_GEN_IRQn]        = { 28, 28, "IRQ_GEN" },
    [USB_IRQn]            = { 29, 29, "USB" },
    [BT_IRQn]             = { 30, 30, "BT" },
};

/* Private typedef -----------------------------------------------------------*/
typedef struct {
    void (*nvic_callback)(hal_nvic_irq_t irq_number);
} nvic_function_t;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
nvic_function_t nvic_function_table[32];
uint32_t irq_nest_count = 0;
extern uint32_t exception_interrupt_nesting_flag;
/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void isrC_main(void)
{
    hal_nvic_irq_t irq_num;
    uint32_t is_interrupt;
#ifdef AIR_ONLINE_SWLA_ENABLE
    uint32_t irq_mask;
#endif

    /* get irq number */
    asm volatile ("csrr %0," "mcause" : "=r" (irq_num) );
    is_interrupt = irq_num & 0x80000000;
    irq_num = irq_num & 0x7fffffff;

    /* handle irq */
    if (is_interrupt)
    {
#ifdef AIR_ONLINE_SWLA_ENABLE
        hal_nvic_save_and_set_interrupt_mask(&irq_mask);
        irq_nest_count += 1;
        hal_nvic_restore_interrupt_mask(irq_mask);
        HCLA_RamLogging_V2(SWLA_TYPE_IRQ, irq_num, SWLA_DIRECTION_START);
#endif
        if (nvic_function_table[irq_num].nvic_callback)
        {
            nvic_function_table[irq_num].nvic_callback(irq_num);
        }
#ifdef AIR_ONLINE_SWLA_ENABLE
        HCLA_RamLogging_V2(SWLA_TYPE_IRQ, irq_num, SWLA_DIRECTION_STOP);
        hal_nvic_save_and_set_interrupt_mask(&irq_mask);
        irq_nest_count -= 1;
        hal_nvic_restore_interrupt_mask(irq_mask);
        /* TODO: single thread contex to main thread */
        if (irq_nest_count == 0) {
            HCLA_RamLogging_V2(SWLA_TYPE_TASK, 0x0, SWLA_DIRECTION_START);
        }
#endif
    }
}

/* Public functions ----------------------------------------------------------*/
void hal_nvic_register_isr_handler(hal_nvic_irq_t irq_number, hal_nvic_isr_t callback)
{
    nvic_function_table[irq_number].nvic_callback = callback;
}

void hal_nvic_enable_irq(hal_nvic_irq_t irq_number)
{
    uint32_t temp_value = 0x1<<irq_number;

    asm volatile ("csrrs x0, mie, %0" : : "r" (temp_value));
}

void hal_nvic_disable_irq(hal_nvic_irq_t irq_number)
{
    uint32_t temp_value = 0x1<<irq_number;

    asm volatile ("csrrc x0, mie, %0" : : "r" (temp_value));
}

void hal_nvic_save_and_set_interrupt_mask(uint32_t *mask)
{
    uint32_t mstatus_temp;

    asm volatile ("csrrci %0, mstatus, 0x8" : "=r" (mstatus_temp));
    *mask = mstatus_temp;
}

void hal_nvic_restore_interrupt_mask(uint32_t mask)
{
    mask = mask & 0x8;
    asm volatile ("csrrs x0, mstatus, %0" : : "r" (mask));
}
/**
 * @brief This function is used to return the RISC-V status.
 *        The return value if it is not zero indicates that the RISC-V exception number.
 * @return    To indicate whether this function call is successful.
 *            If the return value is not zero, the RISC-V is executing excetpion handler;
 *            If the return value is zero, the RISC-V is executing normal code.
 */
int32_t hal_nvic_query_exception_number(void)
{
    return (exception_interrupt_nesting_flag > 0);
}
// #endif /*  */
