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

#ifndef __HAL_SLEEP_MANAGER_INTERNAL_H__
#define __HAL_SLEEP_MANAGER_INTERNAL_H__
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_platform.h"

#ifdef HAL_SLEEP_MANAGER_ENABLED

#ifdef __cplusplus
extern "C" {
#endif

#include "memory_attribute.h"
#include "core_cm33.h"
#include "memory_attribute.h"
#include "hal_spm.h"
#include "hal_log.h"
#include "hal_gpt.h"
#include "air_chip.h"
#include "hal_cross_core_config.h"
//#include "hal_core_status.h"
//#include "reg_def_misc_cfg.h"
//#define SLEEP_MANAGEMENT_DEBUG_ENABLE
//#define SLEEP_MANAGEMENT_DEBUG_SLEEP_WAKEUP_LOG_ENABLE

//#define CM33_SYSTEM_CONTROL         ((volatile uint32_t*)0xE000ED10)

//uint32_t sleep_manager;
//#define AO_BACKUP_BASE_ADDR CROSS_CORE_MEM_DEFINE(sleep_manager, 4000) /* Value: 0xDEAD */
/* RTC_BASE is defined in air_chip.h */
#define AO_BACKUP_RESTORE_SPACE          (volatile uint32_t*)(RTC_BASE + 0x7030)
#define AO_BACKUP_SPACE_LENGTH           0x400
#define AO_BACKUP_BASE_ADDR              (*AO_BACKUP_RESTORE_SPACE)
#define AO_BACKUP_MAX_ADDR               (AO_BACKUP_BASE_ADDR + (3*AO_BACKUP_SPACE_LENGTH))
#define BACKUP_FORMAT_TABLE_START        (volatile uint32_t*)(AO_BACKUP_BASE_ADDR)
#define FIRST_BACKUP_FORMAT_REGISTER     (volatile uint32_t*)(AO_BACKUP_BASE_ADDR + 0x0004)
#define END_BACKUP_FORMAT_REGISTER

#define IP_BASE_ADDR_START_BIT             0
#define IP_BACKUP_LEN_START_BIT            16
#define IP_BACKUP_EN_START_BIT             28

typedef enum{
    SLEEP_MANAGEMENT_AO_BACKUP_TOP_MISC                  =  0,
    SLEEP_MANAGEMENT_AO_BACKUP_CKSYS                     =  1,
    SLEEP_MANAGEMENT_AO_BACKUP_CKSYS_XO_CLK              =  2,
    SLEEP_MANAGEMENT_AO_BACKUP_MIXED                     =  3,
    SLEEP_MANAGEMENT_AO_BACKUP_GPIO                      =  4,
    SLEEP_MANAGEMENT_AO_BACKUP_SPI_SLV                   =  5,
    SLEEP_MANAGEMENT_AO_BACKUP_SPM                       =  6,
    SLEEP_MANAGEMENT_AO_BACKUP_SPM_CFG                   =  7,
    SLEEP_MANAGEMENT_AO_BACKUP_EINT                      =  8,
    SLEEP_MANAGEMENT_AO_BACKUP_KEY_SCAN                  =  9,
    SLEEP_MANAGEMENT_AO_BACKUP_SPI_MST0                  = 10,
    SLEEP_MANAGEMENT_AO_BACKUP_SPI_MST1                  = 11,
    SLEEP_MANAGEMENT_AO_BACKUP_UART_0                    = 12,
    SLEEP_MANAGEMENT_AO_BACKUP_UART_1                    = 13,
    SLEEP_MANAGEMENT_AO_BACKUP_UART_2                    = 14,
    SLEEP_MANAGEMENT_AO_BACKUP_I3C0                      = 15,
    SLEEP_MANAGEMENT_AO_BACKUP_I3C0_DMA                  = 16,
    SLEEP_MANAGEMENT_AO_BACKUP_SMPH                      = 17,
    SLEEP_MANAGEMENT_AO_BACKUP_CKSYS_BUS_CLK             = 18,
    SLEEP_MANAGEMENT_AO_BACKUP_MCU_CFG                   = 19,
    SLEEP_MANAGEMENT_AO_BACKUP_SECURITY_TOP              = 20,
    SLEEP_MANAGEMENT_AO_BACKUP_DCXO_CFG                  = 21,
    SLEEP_MANAGEMENT_AO_BACKUP_PWM_0                     = 22,
    SLEEP_MANAGEMENT_AO_BACKUP_PWM_1                     = 23,
    SLEEP_MANAGEMENT_AO_BACKUP_PWM_2                     = 24,
    SLEEP_MANAGEMENT_AO_BACKUP_MAX
} sleep_management_ao_backup_restore_module_t;

typedef struct{
    uint32_t ao_backup_addr;      /* SRAM address */
    uint32_t ao_backup_value;     /* AO Backup Format Table Value (Header value) */
    uint32_t enable_count;        /* backup enable count */
    uint32_t ao_backup_register;  /* register status */
} ao_backup_status_t;

typedef struct{
	uint32_t module_base_addr; /* Must be 0x42120000 */
	uint32_t module_end_addr;
	uint8_t module_backup_enable;
} ao_backup_format_table_t;

typedef enum {
    AO_BACKUP_RESTORE_DISABLE   = 0,
    AO_BACKUP_RESTORE_ENABLE    = 1,
} sleep_management_ao_backup_restore_type_t;

typedef enum {
	BACKUP_FORMAT_REGISTER_ERROR   =    -1,
	BACKUP_FORMAT_REGISTER_FINISH  =    0x1,
	BACKUP_FORMAT_REGISTER_START   =    0xDEAD,
	BACKUP_FORMAT_REGISTER_END     =    0xDEADBEEF
} sleep_management_format_table_type_t;

void sleep_management_enter_deep_sleep(hal_sleep_mode_t mode);
#if (defined (AIR_CPU_IN_SECURITY_MODE)) /* Limited Trust Zone Environment */
ATTR_NSC_TEXT void sleep_management_enter_deep_sleep_in_secure(hal_sleep_mode_t mode);
#endif

typedef struct {
    volatile uint32_t PSR;      /* ASOR,IRSR,EPSR */
    volatile uint32_t PRIMASK;
    volatile uint32_t FAULTMASK;
    volatile uint32_t BASEPRI;
    volatile uint32_t CONTROL;
} CPU_CORE_BAKEUP_REG_T;

#if (defined (AIR_CPU_IN_SECURITY_MODE))
typedef struct {
    volatile uint32_t PRIMASK_NS;
    volatile uint32_t FAULTMASK_NS;
    volatile uint32_t BASEPRI_NS;
    volatile uint32_t CONTROL_NS;
} CPU_CORE_BAKEUP_REG_NS_T;
#endif


#if (defined (__GNUC__) || defined (__ICCARM__))    /* GCC,IAR compiler */

#define __CPU_CORE_REG_BACKUP(ptr) __asm volatile(  \
    "PUSH   {r0-r12, lr}                \n"\
    "MOV    r2,         %0              \n"\
    "MOV    r0,         r2              \n"\
    "MRS    r1,         psr             \n"\
    "STR    r1,         [r0],#4         \n"\
    "MRS    r1,         primask         \n"\
    "STR    r1,         [r0],#4         \n"\
    "MRS    r1,         faultmask       \n"\
    "STR    r1,         [r0],#4         \n"\
    "MRS    r1,         basepri         \n"\
    "STR    r1,         [r0],#4         \n"\
    "MRS    r1,         control         \n"\
    "STR    r1,         [r0]            \n"\
    "POP    {r0-r12,lr}                   "\
    : :"r" (ptr):                          \
);

#if (defined (AIR_CPU_IN_SECURITY_MODE))
#define __CPU_CORE_REG_BACKUP_NS(ptr) __asm volatile(  \
    "PUSH   {r0-r12, lr}                \n"\
    "MOV    r2,         %0              \n"\
    "MOV    r0,         r2              \n"\
    "MRS    r1,         primask_ns      \n"\
    "STR    r1,         [r0],#4         \n"\
    "MRS    r1,         faultmask_ns    \n"\
    "STR    r1,         [r0],#4         \n"\
    "MRS    r1,         basepri_ns      \n"\
    "STR    r1,         [r0],#4         \n"\
    "MRS    r1,         control_ns      \n"\
    "STR    r1,         [r0]            \n"\
    "POP    {r0-r12,lr}                   "\
    : :"r" (ptr):                          \
);
#endif

#define __CPU_STACK_POINT_BACKUP(psp,msp) {     \
    __asm volatile("MRS %0, psp"  : "=r" (psp) ); \
    __asm volatile("MRS %0, msp"  : "=r" (msp) ); \
}

#if (defined (AIR_CPU_IN_SECURITY_MODE))
#define __CPU_STACK_POINT_BACKUP_NS(psp,msp) {     \
    __asm volatile("MRS %0, psp_ns"  : "=r" (psp) ); \
    __asm volatile("MRS %0, msp_ns"  : "=r" (msp) ); \
}
#endif

#define __CPU_STACK_POINT_LIMIT_BACKUP(psplim,msplim) {     \
    __asm volatile("MRS %0, psplim"  : "=r" (psplim) ); \
    __asm volatile("MRS %0, msplim"  : "=r" (msplim) ); \
}

#if (defined (AIR_CPU_IN_SECURITY_MODE))
#define __CPU_STACK_POINT_LIMIT_BACKUP_NS(psplim,msplim) {     \
    __asm volatile("MRS %0, psplim_ns"  : "=r" (psplim) ); \
    __asm volatile("MRS %0, msplim_ns"  : "=r" (msplim) ); \
}
#endif

#define __MSP_RESTORE(ptr) __asm volatile(  \
    "MOV    r2,         %0              \n"\
    "MOV    r0,         r2              \n"\
    "LDR    r0,         [r0]            \n"\
    "MSR    msp,        r0                "\
    : :"r"(ptr)                            \
);

#define __MSPLIM_RESTORE(ptr) __asm volatile(  \
    "MOV    r2,         %0              \n"\
    "MOV    r0,         r2              \n"\
    "LDR    r0,         [r0]            \n"\
    "MSR    msplim,     r0                "\
    : :"r"(ptr)                            \
);

#if (defined (AIR_CPU_IN_SECURITY_MODE))
#define __MSP_RESTORE_NS(ptr) __asm volatile(  \
    "MOV    r2,         %0              \n"\
    "MOV    r0,         r2              \n"\
    "LDR    r0,         [r0]            \n"\
    "MSR    msp_ns,     r0                "\
    : :"r"(ptr)                            \
);

#define __MSPLIM_RESTORE_NS(ptr) __asm volatile(  \
    "MOV    r2,         %0              \n"\
    "MOV    r0,         r2              \n"\
    "LDR    r0,         [r0]            \n"\
    "MSR    msplim_ns,  r0                "\
    : :"r"(ptr)                            \
);
#endif

#define __SWITCH_TO_PSP_STACK_POINT() __asm volatile(  \
    "MOV    r0,         #4              \n"\
    "MSR    control,    r0              \n"\
    "DSB                                \n"\
    "MOV    r0,         #6              \n"\
    "MSR    control,    r0              \n"\
    "DSB                                  "\
  );

#define __PSP_RESTORE(ptr) __asm volatile(  \
    "MOV    r2,         %0              \n"\
    "MOV    r0,         r2              \n"\
    "LDR    r0,         [r0]            \n"\
    "MSR    psp,        r0                "\
    : :"r"(ptr)                            \
);

#define __PSPLIM_RESTORE(ptr) __asm volatile(  \
    "MOV    r2,         %0              \n"\
    "MOV    r0,         r2              \n"\
    "LDR    r0,         [r0]            \n"\
    "MSR    psplim,     r0                "\
    : :"r"(ptr)                            \
);

#if (defined (AIR_CPU_IN_SECURITY_MODE))
#define __PSP_RESTORE_NS(ptr) __asm volatile(  \
    "MOV    r2,         %0              \n"\
    "MOV    r0,         r2              \n"\
    "LDR    r0,         [r0]            \n"\
    "MSR    psp_ns,     r0                "\
    : :"r"(ptr)                            \
);

#define __PSPLIM_RESTORE_NS(ptr) __asm volatile(  \
    "MOV    r2,         %0              \n"\
    "MOV    r0,         r2              \n"\
    "LDR    r0,         [r0]            \n"\
    "MSR    psplim_ns,  r0                "\
    : :"r"(ptr)                            \
);
#endif

#define __CPU_CORE_CONTROL_REG_RESTORE(ptr) __asm volatile(  \
    "MOV    r2,         %0              \n"\
    "MOV    r0,         r2              \n"\
    "LDR    r1,         [r0],#0         \n"\
    "MSR    control,    r1              \n"\
    : :"r" (ptr):                          \
);

#if (defined (AIR_CPU_IN_SECURITY_MODE))
#define __CPU_CORE_CONTROL_REG_RESTORE_NS(ptr) __asm volatile(  \
    "MOV    r2,         %0              \n"\
    "MOV    r0,         r2              \n"\
    "LDR    r1,         [r0],#0         \n"\
    "MSR    control_ns,    r1           \n"\
    : :"r" (ptr):                          \
);
#endif

#define __CPU_CORE_REG_RESTORE(ptr) __asm volatile(  \
    "PUSH   {r0-r12, lr}                \n"\
    "MOV    r2,         %0              \n"\
    "MOV    r0,         r2              \n"\
    "LDR    r1, [r0],   #4              \n"\
    "MSR    APSR_nzcvq, r1              \n"\
    "LDR    r1, [r0],   #4              \n"\
    "MSR    primask,    r1              \n"\
    "LDR    r1, [r0],   #4              \n"\
    "MSR    faultmask,  r1              \n"\
    "LDR    r1, [r0],   #4              \n"\
    "MSR    basepri,    r1              \n"\
    "POP    {r0-r12,lr}                   "\
    : :"r" (ptr):                          \
);

#if (defined (AIR_CPU_IN_SECURITY_MODE))
#define __CPU_CORE_REG_RESTORE_NS(ptr) __asm volatile(  \
    "PUSH   {r0-r12, lr}                   \n"\
    "MOV    r2,            %0              \n"\
    "MOV    r0,            r2              \n"\
    "LDR    r1, [r0],      #4              \n"\
    "MSR    primask_ns,    r1              \n"\
    "LDR    r1, [r0],      #4              \n"\
    "MSR    faultmask_ns,  r1              \n"\
    "LDR    r1, [r0],      #4              \n"\
    "MSR    basepri_ns,    r1              \n"\
    "POP    {r0-r12,lr}                      "\
    : :"r" (ptr):                             \
);
#endif

#define __ENTER_DEEP_SLEEP(ptr) __asm volatile(  \
    "MOV    r3,         %0              \n"\
    "MOV    r2,         pc              \n"\
    "ADD    r2,         r2,#16          \n"\
    "ORR    r2,         r2,#1           \n"\
    "STR    r2,         [r3]            \n"\
    "DSB                                \n"\
    "WFI                                \n"\
    "NOP                                \n"\
    "NOP                                \n"\
    "NOP                                \n"\
    "NOP                                \n"\
    "CPSID I                            \n"\
    "ISB                                  "\
    : :"r"(ptr)                            \
  );

#define __POP_CPU_REG() __asm volatile(  \
    "POP    {r0-r12,lr}                 "\
  );

#elif defined (__CC_ARM)    /* MDK compiler */

#define __CPU_CORE_REG_BACKUP(ptr) __asm volatile( \
    "MOV 	r2,         "#ptr"          \n"\
    "MOV 	r0,         r2              \n"\
    "MRS 	r1,         psr             \n"\
    "STR 	r1,         [r0],#4         \n"\
    "MRS 	r1,         primask         \n"\
    "STR 	r1,         [r0],#4         \n"\
    "MRS 	r1,         faultmask       \n"\
    "STR 	r1,         [r0],#4         \n"\
    "MRS 	r1,         basepri         \n"\
    "STR 	r1,         [r0],#4         \n"\
    "MRS 	r1,         control         \n"\
    "STR 	r1,         [r0]            \n"\
  )

#define __CPU_CORE_REG_RESTORE(ptr) __asm volatile( \
    "MOV 	r2,         "#ptr"          \n"\
    "MOV 	r0,         r2              \n"\
    "LDR 	r1,         [r0],#4 		\n"\
    "MSR 	APSR_nzcvq, r1              \n"\
    "LDR 	r1,         [r0],#4 		\n"\
    "MSR 	primask,    r1              \n"\
    "LDR 	r1,[r0],    #4              \n"\
    "MSR 	faultmask,  r1              \n"\
    "LDR 	r1,[r0],    #4              \n"\
    "MSR 	basepri,    r1              \n"\
)

#define __CPU_STACK_POINT_BACKUP(psp,msp) {         \
    __asm volatile("MOV "#psp", __current_sp()");   \
    __asm volatile("MOV r0, #0");                   \
    __asm volatile("MSR control, r0");              \
    __asm volatile("MSR control, r0");              \
    __asm volatile("MOV "#msp", __current_sp()");   \
}

#define __MSP_RESTORE(ptr) __asm volatile( \
    "MOV    r2,         "#ptr"          \n"\
    "MOV    r0,         r2              \n"\
    "LDR    r0,         [r0]            \n"\
    "MSR    msp,        r0              \n"\
  )

#define __CPU_CORE_CONTROL_REG_RESTORE(ptr) __asm volatile( \
    "MOV r2, "#ptr" \n"\
    "MOV r0, r2 \n"\
    "LDR r1, [r0],#0 \n"\
    "MSR control, r1 \n"\
)

#define __SWITCH_TO_PSP_STACK_POINT() __asm volatile( \
    "MOV    r0,         #4              \n"\
    "MSR    control,    r0              \n"\
    "DSB                                \n"\
    "MOV    r0,         #6              \n"\
    "MSR    control,    r0              \n"\
    "DSB                                \n"\
  );

#define __PSP_RESTORE(ptr) __asm volatile(  \
    "MOV    r2,         "#ptr"          \n"\
    "MOV    r0,         r2              \n"\
    "LDR    r0,         [r0]            \n"\
    "MSR    psp,        r0              \n"\
  );

#define __ENTER_DEEP_SLEEP(ptr) __asm volatile( \
..
    "MOV 	r3,         "#ptr"          \n"\
    "MOV 	r2,         __current_pc()  \n"\
    "ADD 	r2,         r2,#16          \n"\
    "ORR 	r2,         r2,#1           \n"\
    "STR 	r2,         [r3]            \n"\
    "DSB                                \n"\
    "WFI                                \n"\
    "NOP                                \n"\
    "CPSID I                            \n"\
    "ISB                                \n"\
)

#define __BACKUP_SP(ptr) __asm volatile("MOV "#ptr", __current_sp()\n")

ATTR_TEXT_IN_TCM static __inline __asm volatile void __PUSH_CPU_REG(void)
{
    PRESERVE8
    PUSH    {r0 - r12}
    BX      r14
}

ATTR_TEXT_IN_TCM static __inline __asm volatile void __POP_CPU_REG(void)
{
    PRESERVE8
    POP     {r0 - r12}
    BX      r14
}

ATTR_TEXT_IN_TCM static __inline __asm volatile void __RESTORE_LR(unsigned int return_address)
{
    PRESERVE8
    MOV     lr, r0
    BX      r14
}
#endif  /* MDK compiler */

#define SAVE_PRIORITY_GROUP (IRQ_NUMBER_MAX)
typedef struct {
    uint32_t nvic_iser;                    /**< eint hardware debounce time */
    uint32_t nvic_iser1;
    uint32_t nvic_iser2;
    uint32_t nvic_ip[SAVE_PRIORITY_GROUP];
} nvic_sleep_backup_register_t;

#if (defined (AIR_CPU_IN_SECURITY_MODE))
typedef struct {
    uint32_t nvic_iser;                    /**< eint hardware debounce time */
    uint32_t nvic_iser1;
    uint32_t nvic_iser2;
    uint32_t nvic_ip[SAVE_PRIORITY_GROUP];
} nvic_sleep_backup_register_ns_t;
#endif

typedef struct {
    volatile uint32_t ACTLR;    /* Auxiliary Control Register */
    volatile uint32_t VTOR;     /* Vector Table Offset Register */
    volatile uint32_t SCR;      /* System Control Register */
    volatile uint32_t CCR;      /* Configuration Control Register */
    volatile uint8_t SHP[12];   /* System Handlers Priority Registers (4-7, 8-11, 12-15) */
    volatile uint32_t SHCSR;    /* System Handler Control and State Register */
    volatile uint32_t CPACR;    /* Coprocessor Access Control Register */
    volatile uint32_t NSACR;    /* Non-secure Access Control Register */
    volatile uint32_t DHCSR;     /* Debug Halting Control and Status Register */
    volatile uint32_t DEMCR;     /* Debug Exception and Monitor Control Register */
    volatile uint32_t COMP0;     /* DWT Comparator Register 0  */
    volatile uint32_t FUNCTION0; /* DWT Function Register 0 */
    volatile uint32_t COMP1;     /* DWT Comparator Register 1  */
    volatile uint32_t FUNCTION1; /* DWT Function Register 1 */
    volatile uint32_t COMP2;     /* DWT Comparator Register 2  */
    volatile uint32_t FUNCTION2; /* DWT Function Register 2 */
    volatile uint32_t COMP3;     /* DWT Comparator Register 3  */
    volatile uint32_t FUNCTION3;  /* DWT Function Register 3 */
} CM33_SYS_CTRL_BAKEUP_REG_T;

#if (defined (AIR_CPU_IN_SECURITY_MODE))
typedef struct {
    volatile uint32_t ACTLR;    /* Auxiliary Control Register */
    volatile uint32_t VTOR;     /* Vector Table Offset Register */
    volatile uint32_t SCR;      /* System Control Register */
    volatile uint32_t CCR;      /* Configuration Control Register */
    volatile uint8_t SHP[12];   /* System Handlers Priority Registers (4-7, 8-11, 12-15) */
    volatile uint32_t SHCSR;    /* System Handler Control and State Register */
    volatile uint32_t CPACR;    /* Coprocessor Access Control Register */
    volatile uint32_t DHCSR;     /* Debug Halting Control and Status Register */
    volatile uint32_t DEMCR;     /* Debug Exception and Monitor Control Register */
    volatile uint32_t COMP0;     /* DWT Comparator Register 0  */
    volatile uint32_t FUNCTION0; /* DWT Function Register 0 */
    volatile uint32_t COMP1;     /* DWT Comparator Register 1  */
    volatile uint32_t FUNCTION1; /* DWT Function Register 1 */
    volatile uint32_t COMP2;     /* DWT Comparator Register 2  */
    volatile uint32_t FUNCTION2; /* DWT Function Register 2 */
    volatile uint32_t COMP3;     /* DWT Comparator Register 3  */
    volatile uint32_t FUNCTION3;  /* DWT Function Register 3 */
} CM33_SYS_CTRL_BAKEUP_REG_NS_T;
#endif

/* FPU backup register struct */
typedef struct {
    volatile uint32_t FPCCR;
    volatile uint32_t FPCAR;
} FPU_BAKEUP_REG_T;

/* CMSYS_CFG backup register struct */
typedef struct {
    volatile uint32_t STCALIB;
    volatile uint32_t AHB_BUFFERALBE;
    volatile uint32_t AHB_FIFO_TH;
    volatile uint32_t INT_ACTIVE_HL0;
    volatile uint32_t INT_ACTIVE_HL1;
    volatile uint32_t DCM_CTRL_REG;
} CMSYS_CFG_BAKEUP_REG_T;

/* CMSYS_CFG_EXT backup register struct */
typedef struct {
    __IO uint32_t CG_EN;
    __IO uint32_t DCM_EN;
} CMSYS_CFG_EXT_BAKEUP_REG_T;

typedef enum {
    UNLOCK_SLEEP    = 0,
    LOCK_SLEEP      = 1
} sleep_management_lock_sleep_t;

typedef enum {
    UNLOCK_TICKLESS_IDLE    = 0,
    LOCK_TICKLESS_IDLE      = 1
} sleep_management_lock_idle_t;

typedef enum {
    LOCK_EXTSLP      = 0,
    UNLOCK_EXTSLP    = 1
} sleep_management_lock_extslp_t;

typedef enum {
    SLEEP_MANAGEMENT_UNINITIALIZED  = 0,
    SLEEP_MANAGEMENT_INITIALIZED    = 1
} sleep_management_init_status_t;

/* Lock Sleep Handle ID : 0~49 */
#define  SLEEP_LOCK_HANDLE_MAX                35
#define  SLEEP_LOCK_HANDLE_USER_MAX                  (SLEEP_LOCK_HANDLE_MAX-SLEEP_LOCK_USER_START_ID)
#define  SLEEP_LOCK_EXTEND_HANDLE_USER_MAX           (SLEEP_LOCK_HANDLE_MAX-SLEEP_LOCK_EXTEND_USER_START_ID)
#define  SLEEP_LOCK_TICKLESS_IDLE_HANDLE_USER_MAX    ((((SLEEP_LOCK_HANDLE_MAX)-(SLEEP_LOCK_TICKLESS_IDLE_USER_START_ID)) > 32) ? 32 : ((SLEEP_LOCK_HANDLE_MAX)-(SLEEP_LOCK_TICKLESS_IDLE_USER_START_ID)))

#define  SLEEP_HANDLE_NAME_LEN                11

typedef struct {
    uint64_t    lock_sleep_request;
    uint32_t    user_handle_resource;
    uint8_t     user_handle_count;
    uint8_t     lock_sleep_request_count[SLEEP_LOCK_HANDLE_MAX];
    uint8_t     user_handle_name[SLEEP_LOCK_HANDLE_USER_MAX][SLEEP_HANDLE_NAME_LEN];
} sleep_management_handle_t;

typedef struct {
    uint64_t    lock_extslp_request;
    uint32_t    user_handle_resource;
    uint8_t     user_handle_count;
    uint8_t     lock_extslp_request_count[SLEEP_LOCK_HANDLE_MAX];
    uint8_t     user_handle_name[SLEEP_LOCK_EXTEND_HANDLE_USER_MAX][SLEEP_HANDLE_NAME_LEN];
} sleep_management_extslp_handle_t;

typedef struct {
    uint64_t    lock_idle_request;
    uint32_t    user_handle_resource;
    uint8_t     user_handle_count;
    uint8_t     lock_idle_request_count[SLEEP_LOCK_HANDLE_MAX];
    uint8_t     user_handle_name[SLEEP_LOCK_TICKLESS_IDLE_HANDLE_USER_MAX][SLEEP_HANDLE_NAME_LEN];
} sleep_management_idle_handle_t;

typedef void(* sleep_management_suspend_callback_t)(void *data);
typedef void(* sleep_management_resume_callback_t)(void *data);

typedef struct {
    sleep_management_suspend_callback_t func;
    void *data;
    bool init_status;
} sleep_management_suspend_callback_func_t;

typedef struct {
    sleep_management_resume_callback_t func;
    void *data;
    bool init_status;
} sleep_management_resume_callback_func_t;

typedef enum {
    SLEEP_MANAGEMENT_DEBUG_LOG_OWNERSHIP_FAIL = 0,
    SLEEP_MANAGEMENT_DEBUG_LOG_MAX = 1,
    SLEEP_MANAGEMENT_DEBUG_LOG_DUMP = 255
} sleep_management_debug_log_index_t;

typedef struct {
    uint32_t wakeup_source;
    uint32_t wakeup_source_2;
    uint32_t bootvector_backup;
    uint32_t wkup_from_extslp;
    uint8_t abort_sleep;
} sleep_management_status_t;
extern sleep_management_status_t sleep_management_status;


void sleep_management_SF_DPD_ctrl(bool enable);
void sleep_management_backup_restore_ctrl(bool enable);
void sleep_management_init(void);
void deep_sleep_cmsys_backup(void);
void deep_sleep_cmsys_restore(void);

void sleep_management_infra_pd_enter_sleep(sleep_management_infra_pd_module_t infra_pd_module);
void sleep_management_infra_pd_exit_sleep(sleep_management_infra_pd_module_t infra_pd_module);
void sleep_management_register_infra_pd_suspend_callback(sleep_management_infra_pd_backup_restore_module_t module, sleep_management_suspend_callback_t callback, void *data);
void sleep_management_register_infra_pd_resume_callback(sleep_management_infra_pd_backup_restore_module_t module, sleep_management_resume_callback_t callback, void *data);
void sleep_management_infra_pd_suspend_callback(void);
void sleep_management_infra_pd_resume_callback(void);

uint32_t sleep_management_register_infra_ao_backup_restore(sleep_management_ao_backup_restore_module_t module, ao_backup_format_table_t *module_backup_format);
uint32_t sleep_management_infra_ao_backup_restore(sleep_management_ao_backup_restore_module_t module, sleep_management_ao_backup_restore_type_t enable);


void sleep_management_register_suspend_ns_callback(sleep_management_backup_restore_module_t module, sleep_management_suspend_callback_t callback, void *data);
void sleep_management_register_suspend_secure_callback(sleep_management_backup_restore_module_t module, sleep_management_suspend_callback_t callback, void *data);
void sleep_management_register_all_secure_suspend_callback(sleep_management_backup_restore_module_t module, sleep_management_suspend_callback_t callback, void *data);

void sleep_management_register_resume_ns_callback(sleep_management_backup_restore_module_t module, sleep_management_resume_callback_t callback, void *data);
void sleep_management_register_resume_secure_callback(sleep_management_backup_restore_module_t module, sleep_management_resume_callback_t callback, void *data);
void sleep_management_register_all_secure_resume_callback(sleep_management_backup_restore_module_t module, sleep_management_resume_callback_t callback, void *data);

#if (defined AIR_LIMIT_TZ_ENABLE)
void sleep_management_ns_suspend_callback(void);
void sleep_management_secure_suspend_callback(void);
#else
void sleep_management_all_secure_suspend_callback(void);
#endif

#if (defined AIR_LIMIT_TZ_ENABLE)
void sleep_management_ns_resume_callback(void);
void sleep_management_secure_resume_callback(void);
#else
void sleep_management_all_secure_resume_callback(void);
#endif

uint8_t sleep_management_get_lock_handle(const char *handle_name);
void sleep_management_release_lock_handle(uint8_t handle_index);
void sleep_management_lock_sleep(sleep_management_lock_sleep_t lock, uint8_t handle_index);
bool sleep_management_check_sleep_locks(void);
bool sleep_management_check_handle_status(uint8_t handle_index);
uint64_t sleep_management_get_lock_sleep_request_info(void);
uint64_t sleep_management_get_lock_sleep_handle_list(void);
uint8_t sleep_management_get_lock_idle_handle(const char *handle_name);
void sleep_management_release_lock_idle_handle(uint8_t handle_index);
void sleep_management_lock_idle(sleep_management_lock_idle_t lock, uint8_t handle_index);
bool sleep_management_check_idle_locks(void);
uint64_t sleep_management_get_lock_idle_request_info(void);
uint64_t sleep_management_get_lock_idle_handle_list(void);
uint8_t sleep_management_get_lock_extslp_handle(const char *handle_name);
void sleep_management_release_lock_extslp_handle(uint8_t handle_index);
void sleep_management_lock_extslp(sleep_management_lock_extslp_t lock, uint8_t handle_index);
bool sleep_management_check_extslp_locks(void);
uint64_t sleep_management_get_lock_extslp_request_info(void);
uint64_t sleep_management_get_lock_extslp_handle_list(void);
bool sleep_management_check_cmsys_request_extslp_status(void);
bool sleep_management_check_conn_request_extslp_status(void);
void sleep_management_conn_lock_extslp(sleep_management_lock_extslp_t lock);
void sleep_management_low_power_init_setting(void);
int8_t hal_lp_connsys_get_own_enable_int(void);
int8_t hal_lp_connsys_give_n9_own(void);

#ifdef SLEEP_MANAGEMENT_DEBUG_ENABLE
void sleep_management_debug_lock_sleep_timelog(sleep_management_lock_sleep_t lock, uint8_t handle_index);
void sleep_management_debug_backup_restore_fun_timelog(uint32_t type, uint32_t order, uint32_t callback);
void sleep_management_debug_dump_lock_sleep_time(void);
void sleep_management_debug_reset_lock_sleep_time(void);
void sleep_management_debug_dump_backup_restore_time(void);
void sleep_management_dump_wakeup_source(uint32_t eint_num1, uint32_t eint_num2);
#endif

#ifdef __cplusplus
}
#endif

#endif
#endif

