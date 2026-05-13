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

#include "hal_nvic.h"
#include "hal_gpt.h"

#ifdef HAL_NVIC_MODULE_ENABLED
#include "hal_eint_internal.h"
#include "hal_nvic_internal.h"
//#include "hal_flash_disk_internal.h"
#include "memory_attribute.h"
#include "hal_log.h"
#if !defined(__EXT_BOOTLOADER__) &&  !defined(__EXT_DA__)
#ifdef AIR_SWLA_ENABLE
#include "swla.h"
#endif /* AIR_SWLA_ENABLE */

#ifdef MTK_SYSTEM_HANG_TRACER_ENABLE
#include "systemhang_tracer.h"
#endif /* MTK_SYSTEM_HANG_TRACER_ENABLE */

#ifdef MTK_MEMORY_MONITOR_ENABLE
#include "memory_monitor.h"
#endif /* MTK_MEMORY_MONITOR_ENABLE */
#endif

#ifdef HAL_TIME_CHECK_ENABLED
#include "hal_time_check.h"
#include "exception_handler.h"
#include "hal_gpt_internal.h"
#endif
#ifndef __UBL__
#include "assert.h"
#endif

#ifdef HAL_ESC_MODULE_ENABLED
#include "hal_esc_internal.h"
#endif

#if defined(AIR_PD_DOMAIN_CONTROL_ENABLE)
// #include "pd_domain_control.h"
#endif /* AIR_PD_DOMAIN_CONTROL_ENABLE */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void (*nvic_callback)(hal_nvic_irq_t irq_number);
} nvic_function_t;


#ifdef HAL_TIME_CHECK_DISABLE_IRQ_ENABLED
ATTR_ZIDATA_IN_TCM uint32_t mask_irq_func = 0;
ATTR_ZIDATA_IN_TCM uint32_t time_check_disbale_irq_start;
ATTR_ZIDATA_IN_TCM uint32_t disable_irq_save_duration_us;
extern bool is_time_check_assert_enabled;
#endif

const IRQ_INFO_t irq_info[IRQ_NUMBER_MAX] = {
    [OS_GPT_IRQn]         = { 0,    OS_GPT_IRQ_PRIORITY,            "OS_GPT" },
    [MCU_DMA0_IRQn]       = { 1,    MCU_DMA0_IRQ_PRIORITY,          "MCU_DMA0" },
    [MCU_DMA1_IRQn]       = { 2,    MCU_DMA1_IRQ_PRIORITY,          "MCU_DMA1" },
    [UART_DMA0_IRQn]      = { 3,    UART_DMA0_IRQ_PRIORITY,         "UART_DMA0" },
    [UART_DMA1_IRQn]      = { 4,    UART_DMA1_IRQ_PRIORITY,         "UART_DMA1" },
    [UART_DMA2_IRQn]      = { 5,    UART_DMA2_IRQ_PRIORITY,         "UART_DMA2" },
    [PWM_DMA0_IRQn]       = { 6,    PWM_DMA0_IRQ_PRIORITY,          "PWM_DMA0" },
    [PWM_DMA1_IRQn]       = { 7,    PWM_DMA1_IRQ_PRIORITY,          "PWM_DMA1" },
    [I3C_DMA0_IRQn]       = { 8,    I3C_DMA0_IRQ_PRIORITY,          "I3C_DMA0" },
    [I3C_DMA1_IRQn]       = { 9,    I3C_DMA1_IRQ_PRIORITY,          "I3C_DMA1" },
    [I3C0_IRQn]           = { 10,   I3C0_IRQ_PRIORITY,              "I3C0" },
    [I3C1_IRQn]           = { 11,   I3C1_IRQ_PRIORITY,              "I3C1" },
    [SPI_MST0_IRQn]       = { 12,   SPI_MST0_IRQ_PRIORITY,          "SPI_MST0" },
    [SPI_MST1_IRQn]       = { 13,   SPI_MST1_IRQ_PRIORITY,          "SPI_MST1" },
    [SPI_MST2_IRQn]       = { 14,   SPI_MST2_IRQ_PRIORITY,          "SPI_MST2" },
    [SPI_SLV_IRQn]        = { 15,   SPI_SLV_IRQ_PRIORITY,           "SPI_SLV" },
    [UART0_IRQn]          = { 16,   UART0_IRQ_PRIORITY,             "UART0" },
    [UART1_IRQn]          = { 17,   UART1_IRQ_PRIORITY,             "UART1" },
    [UART2_IRQn]          = { 18,   UART2_IRQ_PRIORITY,             "UART2" },
    [CRYPTO_IRQn]         = { 19,   CRYPTO_IRQ_PRIORITY,            "CRYPTO" },
    [TRNG_IRQn]           = { 20,   TRNG_IRQ_PRIORITY,              "TRNG" },
    [RTC_IRQn]            = { 21,   RTC_IRQ_PRIORITY,               "RTC" },
    [GPT_IRQn]            = { 22,   GPT_IRQ_PRIORITY,               "GPT" },
    [GPT_SEC_IRQn]        = { 23,   GPT_SEC_IRQ_PRIORITY,           "GPT_SEC" },
    [SPM_IRQn]            = { 24,   SPM_IRQ_PRIORITY,               "SPM" },
    [WDT_IRQn]            = { 25,   WDT_IRQ_PRIORITY,               "WDT" },
    [EINT_SEC_IRQn]       = { 26,   EINT_SEC_IRQ_PRIORITY,          "EINT_SEC" },
    [EINT_IRQn]           = { 27,   EINT_IRQ_PRIORITY,              "EINT" },
    [SFC_IRQn]            = { 28,   SFC_IRQ_PRIORITY,               "SFC" },
    [ESC_IRQn]            = { 29,   ESC_IRQ_PRIORITY,               "ESC" },
    [USB_IRQn]            = { 30,   USB_IRQ_PRIORITY,               "USB" },
    [RISCV_IRQ_GEN_IRQn]    { 31,   RISCV_IRQ_GEN_IRQ_PRIORITY,     "RISCV_IRQ_GEN" },
    [AUDIOSYS_IRQn]       = { 32,   AUDIOSYS_IRQ_PRIORITY,          "AUDIOSYS" },
    [BT_IRQn]             = { 33,   BT_IRQ_PRIORITY,                "BT" },
    [BT_AURX_IRQn]        = { 34,   BT_AURX_IRQ_PRIORITY,           "BT_AURX" },
    [BT_AUTX_IRQn]        = { 35,   BT_AUTX_IRQ_PRIORITY,           "BT_AUTX" },
    [BT_TIMER_IRQn]       = { 36,   BT_TIMER_IRQ_PRIORITY,          "BT_TIMER" },
    [BT_PLAY_EN_IRQn]     = { 37,   BT_PLAY_EN_PRIORITY,            "BT_PLAY_EN" },
    [ZIGBEE_IRQn]         = { 38,   ZIGBEE_IRQ_PRIORITY,            "ZIGBEE" },
    [SEC_VIOLATION_IRQn]  = { 39,   SEC_VIOLATION_IRQ_PRIORITY,     "SEC_VIOLATION" },
    [BUS_ERR_IRQn]        = { 40,   BUS_ERR_IRQ_PRIORITY,           "BUS_ERR" },
    [MEM_ILLEGAL_IRQn]    = { 41,   MEM_ILLEGAL_IRQ_PRIORITY,       "MEM_ILLEGAL" },
    [PMU_IRQn]            = { 42,   PMU_IRQ_PRIORITY,               "PMU" },
    [USB_32K_IRQn]        = { 43,   USB_32K_IRQ_PRIORITY,           "USB_32K" },
    [ARGB_IRQn]           = { 44,   ARGB_IRQ_PRIORITY,              "ARGB" },
    [KEYSCAN_IRQn]        = { 45,   KEYSCAN_IRQ_PRIORITY,           "KEYSCAN" },
    [QDEC_IRQn]           = { 46,   QDEC_IRQ_PRIORITY,              "QDEC" },
    [RAMBOZ_IRQn]         = { 47,   RAMBOZ_IRQ_PRIORITY,            "RAMBOZ" },
    [LED_IRQn]            = { 48,   LED_IRQ_PRIORITY,               "LED" },
    [AIO_IRQn]            = { 49,   AIO_IRQ_PRIORITY,               "AIO" },
    [IRTX_IRQn]           = { 50,   IRTX_IRQ_PRIORITY,              "IRTX" },
    [IRRX_IRQn]           = { 51,   IRRX_IRQ_PRIORITY,              "IRRX" },
    [CM33_reserved0_IRQn] = { 52,   CM33_reserved0_IRQ_PRIORITY,    "CM33_reserved0" },
};

nvic_function_t nvic_function_table[IRQ_NUMBER_MAX];

typedef struct {
    uint32_t callback_addr;
    uint32_t mask_irq_time;
    uint32_t cur_time;
    uint32_t cur_time_32k;
} hal_nvic_debug_t;

#define HAL_NVIC_DEBUG_NUM (20)
ATTR_ZIDATA_IN_TCM hal_nvic_debug_t nvic_debug[HAL_NVIC_DEBUG_NUM];
ATTR_ZIDATA_IN_TCM uint32_t cur_index = 0;

ATTR_TEXT_IN_TCM_RETENTION void hal_nvic_debug_log_save(uint32_t callback_addr, uint32_t time)
{
    uint32_t count = 0;

    nvic_debug[cur_index].callback_addr = callback_addr;
    nvic_debug[cur_index].mask_irq_time = time;
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &(nvic_debug[cur_index].cur_time));
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &count);
    nvic_debug[cur_index].cur_time_32k = (uint32_t)(((uint64_t)count) * 1000 / 32768);

    cur_index ++;
    cur_index = (cur_index < HAL_NVIC_DEBUG_NUM) ? cur_index : 0;
}

hal_nvic_status_t hal_nvic_init(void)
{
    static bool priority_set = false;
    uint8_t i;
    if (!priority_set) {
        /* Set defualt priority only one time */
        for (i = 0; i < IRQ_NUMBER_MAX; i++) {
            if (irq_info[i].priority >= (1 << __NVIC_PRIO_BITS)) {
                log_hal_msgid_info("[NVIC]defualt irq priority config error", 0);
#ifndef __UBL__
                assert(0);
#endif
            }
            NVIC_SetPriority((hal_nvic_irq_t)i, irq_info[i].priority);
        }
        priority_set = true;
    }
    return HAL_NVIC_STATUS_OK;
}

ATTR_TEXT_IN_TCM_RETENTION hal_nvic_status_t hal_nvic_enable_irq(hal_nvic_irq_t irq_number)
{
#if !(defined(__EXT_BOOTLOADER__) || defined(__EXT_DA__))
    /* Check if the IRQ number is valid */
    if (irq_number < (hal_nvic_irq_t)0 || irq_number >= IRQ_NUMBER_MAX) {
        return HAL_NVIC_STATUS_ERROR_IRQ_NUMBER;
    }
    NVIC_EnableIRQ(irq_number);
    return HAL_NVIC_STATUS_OK;
#else
    (void)irq_number;
    return HAL_NVIC_STATUS_OK;
#endif
}

ATTR_TEXT_IN_TCM_RETENTION hal_nvic_status_t hal_nvic_disable_irq(hal_nvic_irq_t irq_number)
{
    if (irq_number < (hal_nvic_irq_t)0 || irq_number >= IRQ_NUMBER_MAX) {
        return HAL_NVIC_STATUS_ERROR_IRQ_NUMBER;
    }

    NVIC_DisableIRQ(irq_number);
    return HAL_NVIC_STATUS_OK;
}

uint32_t hal_nvic_get_pending_irq(hal_nvic_irq_t irq_number)
{
    if ((irq_number < (hal_nvic_irq_t)0) || (irq_number >= IRQ_NUMBER_MAX)) {
        return 0xFF;
    }
    return NVIC_GetPendingIRQ(irq_number);
}

/*pd od*/
void hal_nvic_get_pending_irq_by_mask(uint32_t *irq_mask1,uint32_t *irq_mask2)
{
    *irq_mask1 = NVIC->ISPR[0];
    *irq_mask2 = NVIC->ISPR[1];
}

void hal_nvic_enable_irq_by_mask(uint32_t irq_mask1,uint32_t irq_mask2)
{
    __COMPILER_BARRIER();
    NVIC->ISER[0] = (uint32_t)(irq_mask1);
    NVIC->ISER[1] = (uint32_t)(irq_mask2);
    __COMPILER_BARRIER();
}

void hal_nvic_disable_irq_by_mask(uint32_t irq_mask1,uint32_t irq_mask2)
{
    NVIC->ICER[0] = (uint32_t)(irq_mask1);
    NVIC->ICER[1] = (uint32_t)(irq_mask2);
    __DSB();
    __ISB();
}

void hal_nvic_get_enable_irq_by_mask(uint32_t *irq_mask1,uint32_t *irq_mask2)
{
    *irq_mask1 = NVIC->ISER[0];
    *irq_mask2 = NVIC->ISER[1];
}

bool hal_nvic_is_irq_pending()
{
#if 0
    return ((SCB->ICSR) & 0x400000) == 0x400000;
#else
    uint32_t pending_irq_mask1 = 0, pending_irq_mask2 = 0;
    uint32_t enable_irq_mask1 = 0, enable_irq_mask2 = 0;
    hal_nvic_get_pending_irq_by_mask(&pending_irq_mask1, &pending_irq_mask2);
    hal_nvic_get_enable_irq_by_mask(&enable_irq_mask1, &enable_irq_mask2);
    return (((pending_irq_mask1 & enable_irq_mask1) != 0) || ((pending_irq_mask2 & enable_irq_mask2) != 0));
#endif
}

hal_nvic_status_t hal_nvic_set_pending_irq(hal_nvic_irq_t irq_number)
{
    if (irq_number < (hal_nvic_irq_t)0 || irq_number >= IRQ_NUMBER_MAX) {
        return HAL_NVIC_STATUS_ERROR_IRQ_NUMBER;
    }

    NVIC_SetPendingIRQ(irq_number);
    return HAL_NVIC_STATUS_OK;
}

hal_nvic_status_t hal_nvic_clear_pending_irq(hal_nvic_irq_t irq_number)
{
    // Check for invalid irq_number
    if (irq_number < (hal_nvic_irq_t)0 || irq_number >= IRQ_NUMBER_MAX) {
        return HAL_NVIC_STATUS_ERROR_IRQ_NUMBER;
    }

    NVIC_ClearPendingIRQ(irq_number);
    return HAL_NVIC_STATUS_OK;
}

hal_nvic_status_t hal_nvic_set_priority(hal_nvic_irq_t irq_number, uint32_t priority)
{
    if (irq_number < (hal_nvic_irq_t)0 || irq_number >= IRQ_NUMBER_MAX) {
        return HAL_NVIC_STATUS_ERROR_IRQ_NUMBER;
    }

    NVIC_SetPriority(irq_number, priority);

    return HAL_NVIC_STATUS_OK;
}

uint32_t hal_nvic_get_priority(hal_nvic_irq_t irq_number)
{
    if (irq_number < (hal_nvic_irq_t)0 || irq_number >= IRQ_NUMBER_MAX) {
        return 0xff;
    }
    return NVIC_GetPriority(irq_number);
}

ATTR_TEXT_IN_TCM_RETENTION uint32_t get_current_irq()
{
    return (((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) >> SCB_ICSR_VECTACTIVE_Pos) - 16);
}

#ifdef HAL_FLASH_MODULE_ENABLED
extern void Flash_ReturnReady(void);
#endif

#if defined(HAL_ESC_MODULE_ENABLED) && defined(HAL_ESC_WITH_FLASH)
extern void esc_flash_return_ready(void);
#endif

#ifdef CONFIG_AIR_BYPASS_FLASH_RETURN_READY_ENABLE
#include "hal_ccni.h"
void air_mpu_flash_access_check_entry(hal_nvic_irq_t irq_number, hal_ccni_event_t ccni_event);
void air_mpu_flash_access_check_exit(hal_nvic_irq_t irq_number);
#endif

ATTR_TEXT_IN_TCM_RETENTION hal_nvic_status_t isrC_main()
{
    hal_nvic_status_t status = HAL_NVIC_STATUS_ERROR;
    hal_nvic_irq_t irq_number;

    irq_number = (hal_nvic_irq_t)(get_current_irq());

#ifdef CONFIG_AIR_BYPASS_FLASH_RETURN_READY_ENABLE
    /**
     * if ccni, default enable mpu flash access check, channel 0 must be in ram.
     * then, check if enable mpu flash access check by ccni channel in ccni isr.
     **/
    air_mpu_flash_access_check_entry(irq_number, 0);
#else /*CONFIG_AIR_BYPASS_FLASH_RETURN_READY_ENABLE*/
#if defined(HAL_FLASH_MODULE_ENABLED)
    Flash_ReturnReady();
#endif
#endif /*CONFIG_AIR_BYPASS_FLASH_RETURN_READY_ENABLE*/

#if defined(AIR_PD_DOMAIN_CONTROL_ENABLE)
    // if (pd_domain_control_special_irq_check(irq_number) == 0)
    // {
    //     pd_domain_control_auto_on();
    // }
#endif /* AIR_PD_DOMAIN_CONTROL_ENABLE */

#if defined(HAL_ESC_MODULE_ENABLED) && defined(HAL_ESC_WITH_FLASH)
    esc_flash_return_ready();
#endif

#ifdef MTK_SWLA_ENABLE_O2
    uart_debug_print_byte(UART_LA_PORT, 0x14 + irq_number);
#endif

#if !defined(__EXT_BOOTLOADER__) &&  !defined(__EXT_DA__)
#if defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O1) || defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O2)
    systemhang_tracer_t systemhang_irq_tracer;

    systemhang_interrupt_enter_trace((uint32_t)irq_number, &systemhang_irq_tracer);
#endif
#endif /* defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O1) || defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O2) */
#if !defined(__EXT_BOOTLOADER__) &&  !defined(__EXT_DA__)
#ifdef MTK_MEMORY_MONITOR_ENABLE
    memorymonitor_interrupt_enter_trace(irq_number);
#endif
#endif /* MTK_MEMORY_MONITOR_ENABLE */

#if !defined(__EXT_BOOTLOADER__) &&  !defined(__EXT_DA__)
#ifdef AIR_SWLA_ENABLE
    HCLA_RamLogging_V2(SWLA_TYPE_IRQ, irq_number, SWLA_DIRECTION_START);
#endif /* AIR_SWLA_ENABLE */
#endif

    if (irq_number < (hal_nvic_irq_t)0 || irq_number >= IRQ_NUMBER_MAX) {
        status = HAL_NVIC_STATUS_ERROR_IRQ_NUMBER;

#ifdef MTK_SWLA_ENABLE_O2
        uart_debug_print_byte(UART_LA_PORT, '*');
#endif

        return status;
    } else if (nvic_function_table[irq_number].nvic_callback == NULL) {
        status = HAL_NVIC_STATUS_ERROR_NO_ISR;
#ifdef READY
        log_hal_msgid_error("ERROR: no IRQ handler! \n", 0);
#endif

#ifdef MTK_SWLA_ENABLE_O2
        uart_debug_print_byte(UART_LA_PORT, '*');
#endif

        return status;
    } else {
        nvic_function_table[irq_number].nvic_callback(irq_number);
        status = HAL_NVIC_STATUS_OK;
    }

#if !defined(__EXT_BOOTLOADER__) &&  !defined(__EXT_DA__)
#ifdef AIR_SWLA_ENABLE
    HCLA_RamLogging_V2(SWLA_TYPE_IRQ, irq_number, SWLA_DIRECTION_STOP);
#endif /* AIR_SWLA_ENABLE */
#endif

#if !defined(__EXT_BOOTLOADER__) &&  !defined(__EXT_DA__)
#ifdef MTK_MEMORY_MONITOR_ENABLE
    memorymonitor_interrupt_exit_trace(irq_number);
#endif
#endif /* MTK_MEMORY_MONITOR_ENABLE */
#if !defined(__EXT_BOOTLOADER__) &&  !defined(__EXT_DA__)
#if defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O1) || defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O2)
    systemhang_interrupt_exit_trace((uint32_t)irq_number, &systemhang_irq_tracer);
#endif
#endif /* defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O1) || defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O2) */

#ifndef __UBL__
    if (__get_BASEPRI() != 0) {
        printk("irq_number = %d \n", irq_number);
        assert(0);
    }
#endif

#ifdef MTK_SWLA_ENABLE_O2
    uart_debug_print_byte(UART_LA_PORT, '*');
#endif

    /* !!!NOTE!!!
     * zephyr/arch/arm/core/aarch32/cortex_m/exc_exit.S
     * The directly connected IRQ handler needs to call this function
     * after execution to complete tasks such as switching.
     * Because Airoha's flash driver requires both vector table &
     * Flash_ReturnReady to be on RAM, it must be direct IRQ.
     * If this function is not called, the task cannot be scheduled.
     */
    extern void z_arm_int_exit(void);
    z_arm_int_exit();
#ifdef CONFIG_AIR_BYPASS_FLASH_RETURN_READY_ENABLE
    air_mpu_flash_access_check_exit(irq_number);
#endif

    return status;
}

hal_nvic_status_t hal_nvic_register_isr_handler(hal_nvic_irq_t irq_number, hal_nvic_isr_t callback)
{
    uint32_t mask;

    if (irq_number < (hal_nvic_irq_t)0 || irq_number >= IRQ_NUMBER_MAX || callback == NULL) {
        return HAL_NVIC_STATUS_INVALID_PARAMETER;
    }

    hal_nvic_save_and_set_interrupt_mask(&mask);
    NVIC_ClearPendingIRQ(irq_number);
    nvic_function_table[irq_number].nvic_callback = callback;
    hal_nvic_restore_interrupt_mask(mask);

    return HAL_NVIC_STATUS_OK;
}

ATTR_TEXT_IN_TCM_RETENTION hal_nvic_status_t hal_nvic_save_and_set_interrupt_mask(uint32_t *mask)
{
#if !(defined(__EXT_BOOTLOADER__) || defined(__EXT_DA__))
#ifdef HAL_TIME_CHECK_DISABLE_IRQ_ENABLED
    uint32_t xLinkRegAddr = (uint32_t)__builtin_return_address(0);
#endif

    *mask = __get_BASEPRI();
    if (*mask == 0x10) {
        return HAL_NVIC_STATUS_OK;
    }

    __set_BASEPRI(HAL_NVIC_MASK_IRQ_VALUE);  //set base priority 1, fault can be handled first as priority is default zero.
    __DMB();
    __ISB();

#ifdef HAL_TIME_CHECK_DISABLE_IRQ_ENABLED
    if ((*mask == 0) && (hal_core_status_read(HAL_CORE_MCU) == HAL_CORE_ACTIVE)) {
        time_check_disbale_irq_start = GPT(HAL_GPT_US_PORT)->GPT_COUNT;
        mask_irq_func = xLinkRegAddr;
    }
#endif
#else
    (void)*mask;
#endif
    return HAL_NVIC_STATUS_OK;
}

ATTR_TEXT_IN_TCM_RETENTION hal_nvic_status_t hal_nvic_restore_interrupt_mask(uint32_t mask)
{
#if !(defined(__EXT_BOOTLOADER__) || defined(__EXT_DA__))
#ifdef HAL_TIME_CHECK_DISABLE_IRQ_ENABLED
    uint32_t temp_time_end, temp_duration_us;
    if ((mask == 0) && (HAL_NVIC_MASK_IRQ_VALUE == __get_BASEPRI()) && (hal_core_status_read(HAL_CORE_MCU) == HAL_CORE_ACTIVE)) {
        temp_time_end = GPT(HAL_GPT_US_PORT)->GPT_COUNT;
        temp_duration_us = temp_time_end - time_check_disbale_irq_start;
        if ((temp_duration_us > TIME_CHECK_DISABLE_IRQ_TIME) && (is_time_check_assert_enabled == true)) {
            disable_irq_save_duration_us = temp_duration_us;
            ram_assert(0); /*flash mask irq too long need use ram assert*/
        }
        mask_irq_func = 0x0;
    } else if ((mask != 0) && (__get_BASEPRI() == 0)) {
        ram_assert(0);
    }
#endif
    __set_BASEPRI(mask);
    __DMB();
    __ISB();
#else
    (void)mask;
#endif
    return HAL_NVIC_STATUS_OK;
}

ATTR_TEXT_IN_TCM_RETENTION hal_nvic_status_t hal_nvic_save_and_set_interrupt_mask_special(uint32_t *mask)
{
#if !(defined(__EXT_BOOTLOADER__) || defined(__EXT_DA__))
#ifdef HAL_TIME_CHECK_DISABLE_IRQ_ENABLED
    uint32_t xLinkRegAddr = (uint32_t)__builtin_return_address(0);
#endif

    *mask = __get_BASEPRI();
    if (*mask == 0x10) {
        return HAL_NVIC_STATUS_OK;
    }

    __set_BASEPRI(HAL_NVIC_MASK_IRQ_VALUE); //set base priority 1, fault can be handled first as priority is default zero.
    __DMB();
    __ISB();

#ifdef HAL_TIME_CHECK_DISABLE_IRQ_ENABLED
    if ((*mask == 0) && (hal_core_status_read(HAL_CORE_MCU) == HAL_CORE_ACTIVE)) {
        time_check_disbale_irq_start = GPT(HAL_GPT_US_PORT)->GPT_COUNT;
        mask_irq_func = xLinkRegAddr;
    }
#endif
#else
    (void)*mask;
#endif
    return HAL_NVIC_STATUS_OK;
}

ATTR_TEXT_IN_TCM_RETENTION hal_nvic_status_t hal_nvic_restore_interrupt_mask_special(uint32_t mask)
{
#if !(defined(__EXT_BOOTLOADER__) || defined(__EXT_DA__))
#ifdef HAL_TIME_CHECK_DISABLE_IRQ_ENABLED
    uint32_t temp_time_end, temp_duration_us;
    if ((mask == 0) && (HAL_NVIC_MASK_IRQ_VALUE == __get_BASEPRI()) && (hal_core_status_read(HAL_CORE_MCU) == HAL_CORE_ACTIVE)) {
        temp_time_end = GPT(HAL_GPT_US_PORT)->GPT_COUNT;
        temp_duration_us = temp_time_end - time_check_disbale_irq_start;
        if ((temp_duration_us > TIME_CHECK_DISABLE_IRQ_TIME_SPECIAL) && (is_time_check_assert_enabled == true)) {
            disable_irq_save_duration_us = temp_duration_us;
            ram_assert(0); /*flash mask irq too long need use ram assert*/
        }
        mask_irq_func = 0x0;
    } else if ((mask != 0) && (__get_BASEPRI() == 0)) {
        ram_assert(0);
    }
#endif

    __set_BASEPRI(mask);
    __DMB();
    __ISB();
#else
    (void)mask;
#endif
    return HAL_NVIC_STATUS_OK;
}


#ifdef __cplusplus
}
#endif

#endif /* HAL_NVIC_MODULE_ENABLED */

