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
#include <zephyr/devicetree.h>
#include <zephyr/sys/__assert.h>        /* add for __ASSERT */

#include <assert.h>                     /* add for static_assert */

#include "air_chip.h"
#include "memory_attribute.h"

#ifdef AIR_SWLA_ENABLE
#include "swla.h"
#endif

#ifdef CONFIG_RUNTIME_NMI
extern void z_arm_nmi_init(void);
#define NMI_INIT() z_arm_nmi_init()
#else
#define NMI_INIT()
#endif

#define LOG_LEVEL CONFIG_SOC_LOG_LEVEL
LOG_MODULE_REGISTER(soc);

extern int arch_printk_char_out(int);

/* Temporarily provided API for printing log,
 * it is expected to be implemented by UART driver in the future.
 * Override the default weak function in zephyr/lib/os/printk.c.
 */
ATTR_EXCEPTION_CODE int arch_printk_char_out(int c)
{
    UART_REGISTER_T* uartx = (UART_REGISTER_T*)(UART0_BASE);
    volatile uint32_t LSR = uartx->LSR;

    while (1) {
        LSR = uartx->LSR;
        if (LSR & UART_LSR_THRE_MASK) {
            uartx->THR = (uint8_t)c;
            break;
        }
    }
    return 0;
}

#define MAX_LOG_SIZE 128
void exception_print(const char *fmt, ...)
{
    char string[MAX_LOG_SIZE];
    int chars, idx;

    va_list ap;
    va_start(ap, fmt);
    chars = vsnprintk(string, MAX_LOG_SIZE, fmt, ap);
    if(chars > MAX_LOG_SIZE){
        chars = MAX_LOG_SIZE;
    }

    for(idx = 0; idx < chars; idx++){
        arch_printk_char_out(string[idx]);
    }

    if(!strstr(fmt, "\r\n")){
        arch_printk_char_out('\r');
        arch_printk_char_out('\n');
    }

    va_end(ap);
}

extern uint32_t _tcm_text_load;
extern uint32_t _tcm_text_start;
extern uint32_t _tcm_text_size;

#if defined(AIR_EXCEPTION_HANDLER_ENABLE)
extern void NMI_Handler(void);
extern void HardFault_Handler(void);
extern void MemManage_Handler(void);
extern void BusFault_Handler(void);
extern void UsageFault_Handler(void);
extern void SecureFault_Handler(void);
extern void SVC_Handler(void);
extern void DebugMon_Handler(void);
#else
/**
 * @brief  This is the code that gets called when the processor
 *         receives an unexpected interrupt.
 *         This simply enters an infinite loop,
 *         preserving the system state for examination by a debugger.
 * @param  None
 * @retval None
*/
ATTR_EXCEPTION_CODE void NMI_Handler(void)
{
    int idx = 0;
    for(idx = 0; idx < 100; idx++){
        arch_printk_char_out('N');
    }
    __asm__("b .");
}


ATTR_EXCEPTION_CODE void HardFault_Handler(void)
{
    int idx = 0;
    for(idx = 0; idx < 100; idx++){
        arch_printk_char_out('H');
    }
    __asm__("b .");
}

ATTR_EXCEPTION_CODE static void printMemoryManagementErrorMsg(uint32_t CFSRValue)
{
    exception_print("Memory Management fault: ");
    CFSRValue &= 0x000000FF; /* mask mem faults */
    if ((CFSRValue & (1 << 5)) != 0) {
        exception_print("A MemManage fault occurred during FP lazy state preservation\r\n");
    }
    if ((CFSRValue & (1 << 4)) != 0) {
        exception_print("A derived MemManage fault occurred on exception entry\r\n");
    }
    if ((CFSRValue & (1 << 3)) != 0) {
        exception_print("A derived MemManage fault occurred on exception return\r\n");
    }
    if ((CFSRValue & (1 << 1)) != 0) { /* Need to check valid bit (bit 7 of CFSR)? */
        exception_print("Data access violation @0x%08x\r\n", (unsigned int)SCB->MMFAR);
    }
    if ((CFSRValue & (1 << 0)) != 0) {
        exception_print("MPU or Execute Never (XN) default memory map access violation\r\n");
    }
    if ((CFSRValue & (1 << 7)) != 0) { /* To review: remove this if redundant */
        exception_print("SCB->MMFAR = 0x%08x\r\n", (unsigned int)SCB->MMFAR);
    }
}

ATTR_EXCEPTION_CODE void MemManage_Handler(void)
{
    int idx = 0;
    for(idx = 0; idx < 100; idx++){
        arch_printk_char_out('M');
    }
    exception_print("\r\n");
    exception_print("SCB->HFSR = 0x%08x\r\n", (unsigned int)SCB->HFSR);
    exception_print("SCB->CFSR = 0x%08x\r\n", (unsigned int)SCB->CFSR);
    if ((SCB->HFSR & (1 << 30)) != 0) {
        exception_print("Forced Hard Fault\r\n");
    }
    printMemoryManagementErrorMsg(SCB->CFSR);
    __asm__("b .");
}

ATTR_EXCEPTION_CODE void BusFault_Handler(void)
{
    int idx = 0;
    for(idx = 0; idx < 100; idx++){
        arch_printk_char_out('B');
    }
    __asm__("b .");
}

ATTR_EXCEPTION_CODE void print_hex_value(uint32_t value)
{
    uint32_t i_char;
    uint32_t left_shift_times = 0;
    for(; left_shift_times < 8; left_shift_times++){
        i_char = (value & 0xF0000000) >> 28;
        if(i_char <= 9){
            arch_printk_char_out('0' + i_char);
        } else {
            i_char -= 10;
            arch_printk_char_out('a' + i_char);
        }
        value <<= 4;
    }
}
#include "hal_gpt.h"
ATTR_EXCEPTION_CODE void print_hex_array(uint32_t addr, uint32_t length)
{
    while(length){
        print_hex_value(addr);
        arch_printk_char_out(':');
        print_hex_value(*(uint32_t *)(addr));
        arch_printk_char_out(' ');
        print_hex_value(*(uint32_t *)(addr+4));
        arch_printk_char_out(' ');
        print_hex_value(*(uint32_t *)(addr+8));
        arch_printk_char_out(' ');
        print_hex_value(*(uint32_t *)(addr+0xC));
        arch_printk_char_out('\r');
        arch_printk_char_out('\n');

        length -= 16;
        addr += 16;

        hal_gpt_delay_us(1000);
    }
}

ATTR_EXCEPTION_CODE void UsageFault_Handler(void)
{
    int idx = 0;
    for(idx = 0; idx < 100; idx++){
        arch_printk_char_out('U');
    }
#if !IS_ENABLED(CONFIG_MCUBOOT) && !defined(AIR_DOWNLOAD_AGENT)
    uint32_t cfsr = SCB->CFSR;
    arch_printk_char_out('\r');
    arch_printk_char_out('\n');
    arch_printk_char_out('C');
    arch_printk_char_out('F');
    arch_printk_char_out('S');
    arch_printk_char_out('R');
    arch_printk_char_out(':');
    print_hex_value(cfsr);
    arch_printk_char_out('\r');
    arch_printk_char_out('\n');
    uint32_t lr = (uint32_t)__builtin_return_address(0);
    uint32_t *sp;
    if ((lr & 0x4) == 0) {
        __asm__ volatile("mrs %0, msp" : "=r" (sp));
    } else {
        __asm__ volatile("mrs %0, psp" : "=r" (sp));
    }
    uint32_t fault_lr = sp[5];
    uint32_t fault_pc = sp[6];
    uint32_t fault_xpsr = sp[7];

    arch_printk_char_out('S');
    arch_printk_char_out('P');
    arch_printk_char_out(':');
    uint32_t sp_addr = (uint32_t)sp;
    print_hex_value(sp_addr);
    arch_printk_char_out('\r');
    arch_printk_char_out('\n');

    arch_printk_char_out('L');
    arch_printk_char_out('R');
    arch_printk_char_out(':');
    print_hex_value(fault_lr);
    arch_printk_char_out('\r');
    arch_printk_char_out('\n');

    arch_printk_char_out('P');
    arch_printk_char_out('C');
    arch_printk_char_out(':');
    print_hex_value(fault_pc);
    arch_printk_char_out('\r');
    arch_printk_char_out('\n');

    arch_printk_char_out('X');
    arch_printk_char_out('P');
    arch_printk_char_out('S');
    arch_printk_char_out('R');
    arch_printk_char_out(':');
    print_hex_value(fault_xpsr);
    arch_printk_char_out('\r');
    arch_printk_char_out('\n');

    arch_printk_char_out('P');
    arch_printk_char_out('W');
    arch_printk_char_out('R');
    arch_printk_char_out('S');
    arch_printk_char_out(':');
    uint32_t pwr_status = *(volatile uint32_t*)0x4213018C;
    print_hex_value(pwr_status);
    arch_printk_char_out('\r');
    arch_printk_char_out('\n');

    print_hex_array((fault_pc & (~(uint32_t)0x1F)) - 0x80, 0x100);
    uint32_t load_addr = ((uint32_t)&_tcm_text_load) + 0x19E0;
    print_hex_array(load_addr, 0x100);

    /* dump cache register */
    print_hex_array(0xe0180000, 0x80);

    *(volatile uint32_t*)0x42090000 = 0x10;
    *(volatile uint32_t*)0x42090030 = 0x10;

    /* dump ram */
    print_hex_array(TCM_BASE, TCM_LENGTH);
#endif

    __asm__("b .");
}

ATTR_EXCEPTION_CODE void SecureFault_Handler(void)
{
    int idx = 0;
    for(idx = 0; idx < 100; idx++){
        arch_printk_char_out('S');
    }
    __asm__("b .");
}


ATTR_EXCEPTION_CODE static void exception_memory_region_dump(
    uint32_t start_address, uint32_t data_size)
{
    if ((start_address&0x3) != 0)
    {
        /* not 4B align, so we forced to 4B alignment */
        data_size += (start_address&0x3);
        start_address = (start_address&0x3);
    }
    data_size = (data_size+15)/16*16;
    while(data_size >= 16)
    {
        exception_print("0x%08X: %08X %08X %08X %08X\r\n", \
            start_address,
            *((uint32_t *)start_address+0),
            *((uint32_t *)start_address+1),
            *((uint32_t *)start_address+2),
            *((uint32_t *)start_address+3)
        );
        data_size -= 16;
        start_address += 16;
    }
}

ATTR_EXCEPTION_CODE void SVC_Handler(void)
{
    exception_print("\r\n>>>>>> DUMP START >>>>>> DUMP START >>>>>> DUMP START >>>>>> DUMP START >>>>>>\r\n");
    exception_print("\r\nMemory dump begin:\r\n");
#ifdef AIR_SWLA_ENABLE
    /* SWLA memory dump flow */
    if(SLA_MemoryDumpPrepare() == SA_DATA_READY){
        uint32_t swla_base, swla_len;
        SLA_get_region(&swla_base, &swla_len);
        exception_print("####SWLA enabled[0x%08X,0x%08X]####\r\n", (unsigned int)swla_base, (unsigned int)swla_len);
    }
#endif
    exception_memory_region_dump(TCM_BASE, TCM_LENGTH);
    // cache, non-cache...
    // exception_memory_region_dump(SRAM_BASE, SRAM_LENGTH);

    exception_print("\r\nMemory dump end.\r\n");
    exception_print("\r\n>>>>>> DUMP END >>>>>> DUMP END >>>>>> DUMP END >>>>>> DUMP END >>>>>>\r\n");

    __asm__("b .");
}

ATTR_EXCEPTION_CODE void DebugMon_Handler(void)
{
    int idx = 0;
    for(idx = 0; idx < 100; idx++){
        arch_printk_char_out('D');
    }
    __asm__("b .");
}
#endif

ATTR_EXCEPTION_CODE void SysTick_Handler(void)
{
    int idx = 0;
    for(idx = 0; idx < 100; idx++){
        arch_printk_char_out('T');
    }
    __asm__("b .");
}

extern void Flash_ReturnReady(void);
extern void z_arm_pendsv(void);
extern void isrC_main(void);


#if 1
ATTR_EXCEPTION_CODE ATTR_NAKED_ASM void PendSV_Handler(void)
{
    __asm__ volatile (
        /* push/pop lr to preserve the return address so that
         * exception entry flow will correct */
        "push {lr}\n"
#ifdef HAL_FLASH_MODULE_ENABLED
        "bl Flash_ReturnReady\n"
#endif
        "pop {lr}\n"
        /* only jump execution is needed here, because the behavior of returning thread
         * from exception will be simulated in z_arm_pendsv */
        "b z_arm_pendsv\n"
    );
}
#else
ATTR_EXCEPTION_CODE void PendSV_Handler(void)
{
#ifdef HAL_FLASH_MODULE_ENABLED
    Flash_ReturnReady();
#endif
    z_arm_pendsv();
}

#endif

#ifdef CONFIG_CORTEX_M_SYSTICK
#include "hal_gpt.h"
ATTR_EXCEPTION_CODE void Default_Handler_SysTickWrapper(void)
{
    uint32_t count;
    static uint32_t round = 0;
#ifdef HAL_FLASH_MODULE_ENABLED
    Flash_ReturnReady();
#endif
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &count);
    extern void sys_clock_isr(void *arg);
    sys_clock_isr(NULL);
    round++;
    if(0 == (round % 1000)){
        exception_print("sys_clock_isr count: %d\r\n", count);
    }
}
#endif

extern uint32_t _stack_end;
extern void Reset_Handler(void);
ATTR_ISR_VECTOR uint32_t g_pfnVectors[] = {
/* ARMv8-M Architecture Reference Manual, Section B3.8 Exception numbers and exception priority numbers */
    (uint32_t)&_stack_end,              /* MSP */
    (uint32_t)&Reset_Handler,           /* PC */
    (uint32_t)&NMI_Handler,             /* IRQ ID: -14, Exception Number: 2; NMI_Handler */
    (uint32_t)&HardFault_Handler,       /* IRQ ID: -13, Exception Number: 3; HardFault_Handler */
    (uint32_t)&MemManage_Handler,       /* IRQ ID: -12, Exception Number: 4; MemManage_Handler */
    (uint32_t)&BusFault_Handler,        /* IRQ ID: -11, Exception Number: 5; BusFault_Handler */
    (uint32_t)&UsageFault_Handler,      /* IRQ ID: -10, Exception Number: 6; UsageFault_Handler */
    (uint32_t)&SecureFault_Handler,     /* IRQ ID: -9,  Exception Number: 7; SecureFault_Handler */
    0,
    0,
    0,
    (uint32_t)&SVC_Handler,             /* IRQ ID: -5,  Exception Number: 11; SVC_Handler */
    (uint32_t)&DebugMon_Handler,        /* IRQ ID: -4,  Exception Number: 12; DebugMon_Handler */
    0,
    (uint32_t)&PendSV_Handler,          /* IRQ ID: -2,  Exception Number: 14; PendSV_Handler */
#ifndef CONFIG_CORTEX_M_SYSTICK
    (uint32_t)&SysTick_Handler,         /* IRQ ID: -1,  Exception Number: 15; SysTick_Handler */
#else
    (uint32_t)&Default_Handler_SysTickWrapper,
#endif

    /* External Interrupts defined by Airoha */
    (uint32_t)&isrC_main,               /* IRQ ID: 0,  Exception Number: 16 */
    (uint32_t)&isrC_main,               /* IRQ ID: 1,  Exception Number: 17 */
    (uint32_t)&isrC_main,               /* IRQ ID: 2,  Exception Number: 18 */
    (uint32_t)&isrC_main,               /* IRQ ID: 3,  Exception Number: 19 */
    (uint32_t)&isrC_main,               /* IRQ ID: 4,  Exception Number: 20 */
    (uint32_t)&isrC_main,               /* IRQ ID: 5,  Exception Number: 21 */
    (uint32_t)&isrC_main,               /* IRQ ID: 6,  Exception Number: 22 */
    (uint32_t)&isrC_main,               /* IRQ ID: 7,  Exception Number: 23 */
    (uint32_t)&isrC_main,               /* IRQ ID: 8,  Exception Number: 24 */
    (uint32_t)&isrC_main,               /* IRQ ID: 9,  Exception Number: 25 */
    (uint32_t)&isrC_main,               /* IRQ ID: 10, Exception Number: 26 */
    (uint32_t)&isrC_main,               /* IRQ ID: 11, Exception Number: 27 */
    (uint32_t)&isrC_main,               /* IRQ ID: 12, Exception Number: 28 */
    (uint32_t)&isrC_main,               /* IRQ ID: 13, Exception Number: 29 */
    (uint32_t)&isrC_main,               /* IRQ ID: 14, Exception Number: 30 */
    (uint32_t)&isrC_main,               /* IRQ ID: 15, Exception Number: 31 */
    (uint32_t)&isrC_main,               /* IRQ ID: 16, Exception Number: 32 */
    (uint32_t)&isrC_main,               /* IRQ ID: 17, Exception Number: 33 */
    (uint32_t)&isrC_main,               /* IRQ ID: 18, Exception Number: 34 */
    (uint32_t)&isrC_main,               /* IRQ ID: 19, Exception Number: 35 */
    (uint32_t)&isrC_main,               /* IRQ ID: 20, Exception Number: 36 */
    (uint32_t)&isrC_main,               /* IRQ ID: 21, Exception Number: 37 */
    (uint32_t)&isrC_main,               /* IRQ ID: 22, Exception Number: 38 */
    (uint32_t)&isrC_main,               /* IRQ ID: 23, Exception Number: 39 */
    (uint32_t)&isrC_main,               /* IRQ ID: 24, Exception Number: 40 */
    (uint32_t)&isrC_main,               /* IRQ ID: 25, Exception Number: 41 */
    (uint32_t)&isrC_main,               /* IRQ ID: 26, Exception Number: 42 */
    (uint32_t)&isrC_main,               /* IRQ ID: 27, Exception Number: 43 */
    (uint32_t)&isrC_main,               /* IRQ ID: 28, Exception Number: 44 */
    (uint32_t)&isrC_main,               /* IRQ ID: 29, Exception Number: 45 */
    (uint32_t)&isrC_main,               /* IRQ ID: 30, Exception Number: 46 */
    (uint32_t)&isrC_main,               /* IRQ ID: 31, Exception Number: 47 */
    (uint32_t)&isrC_main,               /* IRQ ID: 32, Exception Number: 48 */
    (uint32_t)&isrC_main,               /* IRQ ID: 33, Exception Number: 49 */
    (uint32_t)&isrC_main,               /* IRQ ID: 34, Exception Number: 50 */
    (uint32_t)&isrC_main,               /* IRQ ID: 35, Exception Number: 51 */
    (uint32_t)&isrC_main,               /* IRQ ID: 36, Exception Number: 52 */
    (uint32_t)&isrC_main,               /* IRQ ID: 37, Exception Number: 53 */
    (uint32_t)&isrC_main,               /* IRQ ID: 38, Exception Number: 54 */
    (uint32_t)&isrC_main,               /* IRQ ID: 39, Exception Number: 55 */
    (uint32_t)&isrC_main,               /* IRQ ID: 40, Exception Number: 56 */
    (uint32_t)&isrC_main,               /* IRQ ID: 41, Exception Number: 57 */
    (uint32_t)&isrC_main,               /* IRQ ID: 42, Exception Number: 58 */
    (uint32_t)&isrC_main,               /* IRQ ID: 43, Exception Number: 59 */
    (uint32_t)&isrC_main,               /* IRQ ID: 44, Exception Number: 60 */
    (uint32_t)&isrC_main,               /* IRQ ID: 45, Exception Number: 61 */
    (uint32_t)&isrC_main,               /* IRQ ID: 46, Exception Number: 62 */
    (uint32_t)&isrC_main,               /* IRQ ID: 47, Exception Number: 63 */
    (uint32_t)&isrC_main,               /* IRQ ID: 48, Exception Number: 64 */
    (uint32_t)&isrC_main,               /* IRQ ID: 49, Exception Number: 65 */
    (uint32_t)&isrC_main,               /* IRQ ID: 50, Exception Number: 66 */
    (uint32_t)&isrC_main,               /* IRQ ID: 51, Exception Number: 67 */
    (uint32_t)&isrC_main,               /* IRQ ID: 52, Exception Number: 68 */
};
static_assert((sizeof(g_pfnVectors)/4) == (16+CONFIG_NUM_IRQS), \
    "Please check IRQ numbers and its default ISR");

/**
  * @brief  CACHE preinit
  *         Init CACHE to accelerate region init progress.
  * @param  None
  * @retval None
  */
void CachePreInit(void)
{
    __ISB();

    /* ab1620 only has 16K cache memory */
    CACHE->CACHE_CON = 0x20D;

    /* !!! Please note that flush & invalidate all cache lines must be performed
     * on the premise of cache controller enable, otherwise the tag memory
     * may be a random value, which may cause trouble to region init. !!!
     */

    /* Flush all cache lines */
    CACHE->CACHE_OP = 0x13;

    /* Invalidate all cache lines */
    CACHE->CACHE_OP = 0x03;

#ifdef CONFIG_XIP
    /* Set cacheable region */
    CACHE->CACHE_ENTRY_N[0] = ROM_BASE | 0x100;
    CACHE->CACHE_END_ENTRY_N[0] = ROM_BASE + ROM_LENGTH;
    CACHE->CACHE_REGION_EN = 1;
#endif

    __ISB();
}

#ifdef CONFIG_ASSERT_NO_FILE_INFO
    ATTR_EXCEPTION_CODE void assert_post_action(void)
    {
    }
#else
ATTR_EXCEPTION_CODE void assert_post_action(const char *file, unsigned int line)
    {
        exception_print("\r\nassert at %s:%d\r\n", file, line);
        SCB->CCR |=  SCB_CCR_UNALIGN_TRP_Msk;
        *((volatile unsigned int *) 0xFFFFFFF1) = 1;
        for(;;);
    }
#endif

#if 0 // !IS_ENABLED(CONFIG_MCUBOOT)

ATTR_EXCEPTION_CODE void calc_memory_checksum(uint32_t start_addr, uint32_t len, uint32_t* p_result)
{
    uint32_t check_sum = 0;
    uint32_t key = arch_irq_lock();
    uint32_t idx;
    for(idx = 0; idx < len; idx++){
        check_sum += *((volatile uint8_t *)(start_addr + idx));
    }
    arch_irq_unlock(key);
    *p_result = check_sum;
}

uint32_t checksum_startup[2];
ATTR_EXCEPTION_CODE void calc_non_retention_ram_code_checksum_after_startup(void)
{
    uint32_t load_addr, execute_addr, size;
    load_addr = (uint32_t)(&_tcm_text_load);
    execute_addr = (uint32_t)(&_tcm_text_start);
    size = (uint32_t)(&_tcm_text_size);

    calc_memory_checksum(load_addr, size, &checksum_startup[0]);
    calc_memory_checksum(execute_addr, size, &checksum_startup[1]);
    __ASSERT_NO_MSG(checksum_startup[0] == checksum_startup[1]);
}

uint32_t checksum_sleep[6];
ATTR_EXCEPTION_CODE void calc_non_retention_ram_code_checksum_after_exit_sleep(void)
{
    uint32_t load_addr, execute_addr, size;
    load_addr = (uint32_t)(&_tcm_text_load);
    execute_addr = (uint32_t)(&_tcm_text_start);
    size = (uint32_t)(&_tcm_text_size);

    calc_memory_checksum(load_addr, size, &checksum_sleep[0]);
    calc_memory_checksum(execute_addr, size, &checksum_sleep[1]);

    if(checksum_sleep[0] != checksum_sleep[1]){
#if !IS_ENABLED(CONFIG_AIR_EXCEPTION_HANDLER_ENABLE)
        arch_printk_char_out('\r');
        arch_printk_char_out('\n');

        __DSB();
        __ISB();

        arch_printk_char_out('C');
        arch_printk_char_out('H');
        arch_printk_char_out('S');
        arch_printk_char_out('T');
        arch_printk_char_out(':');
        print_hex_value(checksum_startup[0]);
        arch_printk_char_out(' ');
        print_hex_value(checksum_startup[1]);
        arch_printk_char_out('\r');
        arch_printk_char_out('\n');

        arch_printk_char_out('C');
        arch_printk_char_out('H');
        arch_printk_char_out('S');
        arch_printk_char_out('L');
        arch_printk_char_out(':');
        print_hex_value(checksum_sleep[0]);
        arch_printk_char_out(' ');
        print_hex_value(checksum_sleep[1]);
        arch_printk_char_out(' ');
        print_hex_value(checksum_sleep[2]);
        arch_printk_char_out(' ');
        print_hex_value(checksum_sleep[3]);
        arch_printk_char_out(' ');
        print_hex_value(checksum_sleep[4]);
        arch_printk_char_out(' ');
        print_hex_value(checksum_sleep[5]);
        arch_printk_char_out('\r');
        arch_printk_char_out('\n');

        // arch_printk_char_out('w');
        // arch_printk_char_out(' ');
        // arch_printk_char_out('r');
        // arch_printk_char_out('a');
        // arch_printk_char_out('m');
        // arch_printk_char_out(':');

        // uint32_t w_test_addr = execute_addr;
        // uint32_t w_test_idx;
        // for(w_test_idx = 0; w_test_idx < size; w_test_idx += 4){
        //     *(volatile uint32_t*)(w_test_addr + w_test_idx) = 0xA5A5A5A5;
        //     __DSB();
        //     __ISB();
        //     __ASSERT_NO_MSG(*(volatile uint32_t*)(w_test_addr + w_test_idx) == 0xA5A5A5A5);
        // }
#endif /* !IS_ENABLED(CONFIG_AIR_EXCEPTION_HANDLER_ENABLE) */
        __ASSERT_NO_MSG(checksum_sleep[0] == checksum_sleep[1]);
    }
}

#endif

#if defined(AIR_SOC_CROSS_CORE_MEMORY_ENABLE)

extern uint32_t __padding_before_tcm_text_start;
extern uint32_t __padding_before_tcm_text_end;


#if KERNELVERSION == 0x3030000
static int ccm_init(const struct device *dev)
{
    ARG_UNUSED(dev);
#elif KERNELVERSION >= 0x3070000
static int ccm_init(void)
{
#else
#error "Unkown supported kernel version"
#endif
    memset((void*)CROSS_CORE_MEM_BASE, 0x0, CROSS_CORE_MEM_LENGTH);

    uint32_t start = (uint32_t)&__padding_before_tcm_text_start;
    uint32_t end = (uint32_t)&__padding_before_tcm_text_end;
    uint32_t len = end - start;
    memset((void*)start, 0xA5, len);

    return 0;
}

SYS_INIT(ccm_init, CONFIG_CCM_INIT_LEVEL, CONFIG_CCM_INIT_PRIORITY);
#endif /* defined(AIR_SOC_CROSS_CORE_MEMORY_ENABLE) */


#if IS_ENABLED(CONFIG_AIR_RISCV_BUILD)

#include "hal_riscv_ctl.h"

#if KERNELVERSION == 0x3030000
static int riscv_firmware_load_and_start(const struct device *dev)
{
    ARG_UNUSED(dev);
#elif KERNELVERSION >= 0x3070000
static int riscv_firmware_load_and_start(void)
{
#else
#error "Unkown supported kernel version"
#endif

    bool result = false;
    hal_riscv_stop();
    result = hal_riscv_start(0);
    return (result)?(0):(-1);
}
SYS_INIT(riscv_firmware_load_and_start, CONFIG_START_RISCV_INIT_LEVEL, CONFIG_START_RISCV_INIT_PRIORITY);
#endif


#if defined(FPGA_ENV)
#if KERNELVERSION == 0x3030000
static int fpga_uart_pdn_on(const struct device *dev)
{
    ARG_UNUSED(dev);
#elif KERNELVERSION >= 0x3070000
static int fpga_uart_pdn_on(void)
{
#else
#error "Unkown supported kernel version"
#endif
    // *((volatile uint32_t *)0x422D0320) = 0xFFFFFFFF;
    // *((volatile uint32_t *)0x422D0350) = 0xFFFFFFFF;
    // *((volatile uint32_t *)0x422D0380) = 0xFFFFFFFF;
    // *((volatile uint32_t *)0x42040B20) = 0xFFFFFFFF;
    *((volatile uint32_t *)0x42040B50) = 0xFFFFFFFF;
    // *((volatile uint32_t *)0x42040B54) = 0xFFFFFFFF;
    // *((volatile uint32_t *)0x42040B80) = 0xFFFFFFFF;
    // *((volatile uint32_t *)0x42040BB0) = 0xFFFFFFFF;

    return 0;
}
SYS_INIT(fpga_uart_pdn_on, CONFIG_FPGA_CLOCK_INIT_LEVEL, CONFIG_FPGA_CLOCK_INIT_PRIORITY);
#endif


#if IS_ENABLED(CONFIG_AIR_WDT)
#include "hal_wdt.h"
#include "wdt_airoha.h"
#endif

// void jump_to_reset_handler(void)
// {
//     __asm__ volatile (
//         "movw r0, #0x3009\n"
//         "movt r0, #0x0802\n"
//         "bx r0\n"
//         "b .\n"
//     );
// }


/**
 *
 * @brief Reset the system
 *
 * This routine resets the processor.
 *
 */
void sys_arch_reboot(int type)
{
    /* Overwrite the sys_arch_reboot symbol in the zephyr/arch/arm/core/aarch32/cortex_m/scb.c file
     * to achieve a reset at the SOC level.
     */
    ARG_UNUSED(type);
#if IS_ENABLED(CONFIG_REBOOT) && defined(FPGA_ENV)
    /* let BROM jump to Reset_Handler( 0x0823_0009 ) */
    *(volatile uint32_t*)0x04100000 = 0x0009F243;
    *(volatile uint32_t*)0x04100004 = 0x0002F6C0;
    *(volatile uint32_t*)0x04100008 = 0xE7FE4700;
    *(volatile uint32_t*)0x0410000C = 0xE7FEE7FE;
#endif

#if IS_ENABLED(CONFIG_AIR_WDT)
    hal_wdt_software_reset();
#else
    NVIC_SystemReset();
#endif
}

void sys_wdt_feed(void)
{
#ifdef CONFIG_AIR_WDT
    const struct device *wdt_dev = \
        device_get_binding(DEVICE_DT_NAME(DT_NODELABEL(wdt0)));
    __ASSERT_NO_MSG(wdt_dev != NULL);
    wdt_feed(wdt_dev, ((wdt_air_data_t*)(wdt_dev->data))->m_channel);
#endif

#ifdef CONFIG_AIR_WDT_2ND
    const struct device *wdt_dev_1 = \
        device_get_binding(DEVICE_DT_NAME(DT_NODELABEL(wdt1)));
    __ASSERT_NO_MSG(wdt_dev_1 != NULL);
    wdt_feed(wdt_dev_1, ((wdt_air_data_t*)(wdt_dev_1->data))->m_channel);
#endif
}


#if CONFIG_ARM_ON_ENTER_CPU_IDLE_PREPARE_HOOK
void z_arm_on_enter_cpu_idle_prepare(void)
{
    sys_wdt_feed();
}
#endif