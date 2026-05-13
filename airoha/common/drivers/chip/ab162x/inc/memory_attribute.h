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

/*****************************************************
    Usage:
    1. function implementation:
        ATTR_TEXT_IN_TCM int func(int par)
        {
        }
    2. RO data definitions:
        a. ATTR_RODATA_IN_TCM const int b = 8;
    3. RW data definitions:
        a. ATTR_RWDATA_IN_TCM int b = 8;
    4. ZI data definitions:
        a. ATTR_ZIDATA_IN_TCM int b;

    Note: Because the section name contains the file name and line number,
          do not add attribute declarations when variable extern or function declarations.
*****************************************************/

#ifndef __MEMORY_ATTRIBUTE_H__
#define __MEMORY_ATTRIBUTE_H__


#define ATTR_NO_OPTIMIZE                                __attribute__((optimize("O0")))
#define ATTR_WEAK_SYMBOL                                __attribute__((weak))

#define ATTR_NO_INLINE                                  __attribute__ ((noinline))
#define ATTR_ALWAYS_INLINE                              __attribute__ ((always_inline))
#define ATTR_ALIGN(alignment)                           __attribute__ ((__aligned__(alignment)))

/* From gcc manual Chapter 6. Extensions to the C language family:
 * This attribute. attached to a !!! FUNCTION !!!, means that code must be emitted for the function
 * even if appears that the !!! FUNCTION !!! is not referenced.
 *
 * Note: For !!! VARIABLES !!! definitions, this attribute doest not ensure that unused !!! VARIABLES !!! are not optimized.
 *       If necessary, developers can use the KEEP keyword in the linker script to prevent !!! VARIABLES !!! from being optimized.
 */
#define ATTR_USED                                       __attribute__((used))

/* The reason why no inline is added is that some compilers
 * may directly choose inline when processing static functions,
 * so that the specified section will not take effect.
 */
#define ATTR_HELPER(x)                                  #x
#define ATTR_IN_SECTION_TEXT(sec, file, line) \
            __attribute__((section(sec                          \
                                   "." ATTR_HELPER(file)        \
                                   "." ATTR_HELPER(line))))     \
                                   ATTR_NO_INLINE

#define ATTR_IN_SECTION_DATA(sec, file, line) \
            __attribute__((section(sec                          \
                                   "." ATTR_HELPER(file)        \
                                   "." ATTR_HELPER(line))))



#define ATTR_TEXT_DECLARE(sec)                          ATTR_IN_SECTION_TEXT(sec, __FILE__, __LINE__)
#define ATTR_DATA_DECLARE(sec)                          ATTR_IN_SECTION_DATA(sec, __FILE__, __LINE__)

#define ATTR_NAKED_ASM                                  __attribute__((naked))
#define ATTR_ISR_VECTOR                                 __attribute__((__section__(".isr_vector")))
#define ATTR_EXCEPTION_CODE                             ATTR_TEXT_DECLARE(".exception_code")
#define ATTR_CCNI_EVENT_HANDLER(num)                    __attribute__((section(".ccni_event_handler" \
                                                            "." ATTR_HELPER(num))))

#define ATTR_RAM_FUNCTION                               ATTR_TEXT_DECLARE(".ramfunc")
#define ATTR_TEXT_IN_TCM                                ATTR_TEXT_DECLARE(".tcm_code")
#define ATTR_TEXT_IN_TCM_RETENTION                      ATTR_TEXT_DECLARE(".tcm_code_retention")
#define ATTR_RODATA_IN_TCM                              ATTR_DATA_DECLARE(".tcm_rodata") const
#define ATTR_RWDATA_IN_TCM                              ATTR_DATA_DECLARE(".tcm_rwdata")
#define ATTR_RWDATA_IN_TCM_NONE_RETENTION               ATTR_DATA_DECLARE(".tcm_rwdata_none_retention")
#define ATTR_ZIDATA_IN_TCM                              ATTR_DATA_DECLARE(".tcm_zidata")
#define ATTR_ZIDATA_IN_TCM_NONE_RETENTION               ATTR_DATA_DECLARE(".tcm_zidata_none_retention")

#define ATTR_CRITICAL_TEXT_IN_TCM(module)               ATTR_TEXT_DECLARE(".tcm_code.critical." #module)
#define ATTR_CRITICAL_RODATA_IN_TCM(module)             ATTR_DATA_DECLARE(".tcm_rodata.critical." #module) const

#define ATTR_TEXT_IN_SYSRAM                             ATTR_TEXT_DECLARE(".tcm_code")
#define ATTR_RODATA_IN_SYSRAM                           ATTR_DATA_DECLARE(".tcm_rodata") const
#define ATTR_RWDATA_IN_CACHED_SYSRAM                    ATTR_DATA_DECLARE(".tcm_rwdata")
#define ATTR_ZIDATA_IN_CACHED_SYSRAM                    ATTR_DATA_DECLARE(".tcm_zidata")
#define ATTR_RWDATA_IN_NONCACHED_SYSRAM                 ATTR_DATA_DECLARE(".tcm_rwdata")
#define ATTR_ZIDATA_IN_NONCACHED_SYSRAM                 ATTR_DATA_DECLARE(".tcm_zidata")


#define ATTR_RWDATA_IN_NONCACHED_SYSRAM_ALIGN(X)        ATTR_RWDATA_IN_NONCACHED_SYSRAM ATTR_ALIGN(X)
#define ATTR_ZIDATA_IN_NONCACHED_SYSRAM_ALIGN(X)        ATTR_ZIDATA_IN_NONCACHED_SYSRAM ATTR_ALIGN(X)
/* User can specified the alignment of the data in the memory instead of
 * rigidly using these predefined macros. */
#define ATTR_RWDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN     ATTR_RWDATA_IN_NONCACHED_SYSRAM ATTR_ALIGN(4)
#define ATTR_ZIDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN     ATTR_ZIDATA_IN_NONCACHED_SYSRAM ATTR_ALIGN(4)
#define ATTR_RWDATA_IN_NONCACHED_SYSRAM_8BYTE_ALIGN     ATTR_RWDATA_IN_NONCACHED_SYSRAM ATTR_ALIGN(8)
#define ATTR_ZIDATA_IN_NONCACHED_SYSRAM_8BYTE_ALIGN     ATTR_ZIDATA_IN_NONCACHED_SYSRAM ATTR_ALIGN(8)
#define ATTR_RWDATA_IN_NONCACHED_SYSRAM_16BYTE_ALIGN    ATTR_RWDATA_IN_NONCACHED_SYSRAM ATTR_ALIGN(16)
#define ATTR_ZIDATA_IN_NONCACHED_SYSRAM_16BYTE_ALIGN    ATTR_ZIDATA_IN_NONCACHED_SYSRAM ATTR_ALIGN(16)
#define ATTR_RWDATA_IN_NONCACHED_SYSRAM_32BYTE_ALIGN    ATTR_RWDATA_IN_NONCACHED_SYSRAM ATTR_ALIGN(32)
#define ATTR_ZIDATA_IN_NONCACHED_SYSRAM_32BYTE_ALIGN    ATTR_ZIDATA_IN_NONCACHED_SYSRAM ATTR_ALIGN(32)

/* No other alignment request, cross core data not need initialize value */
#define ATTR_SHARE_ZIDATA                               ATTR_DATA_DECLARE(".share_zidata") ATTR_ALIGN(4)

#define ATTR_SHARE_RWBT                                 ATTR_DATA_DECLARE(".share_rwbt")
#define ATTR_SHARE_ZIBT                                 ATTR_DATA_DECLARE(".share_zibt")
#define ATTR_SHARE_RWBT_ALIGN(X)                        ATTR_SHARE_RWBT ATTR_ALIGN(X)
#define ATTR_SHARE_ZIBT_ALIGN(X)                        ATTR_SHARE_ZIBT ATTR_ALIGN(X)
#define ATTR_SHARE_RWBT_4BYTE_ALIGN                     ATTR_SHARE_RWBT ATTR_ALIGN(4)
#define ATTR_SHARE_ZIBT_4BYTE_ALIGN                     ATTR_SHARE_ZIBT ATTR_ALIGN(4)
#define ATTR_SHARE_RWBT_8BYTE_ALIGN                     ATTR_SHARE_RWBT ATTR_ALIGN(8)
#define ATTR_SHARE_ZIBT_8BYTE_ALIGN                     ATTR_SHARE_ZIBT ATTR_ALIGN(8)
#define ATTR_SHARE_RWBT_16BYTE_ALIGN                    ATTR_SHARE_RWBT ATTR_ALIGN(16)
#define ATTR_SHARE_ZIBT_16BYTE_ALIGN                    ATTR_SHARE_ZIBT ATTR_ALIGN(16)
#define ATTR_SHARE_RWBT_32BYTE_ALIGN                    ATTR_SHARE_RWBT ATTR_ALIGN(32)
#define ATTR_SHARE_ZIBT_32BYTE_ALIGN                    ATTR_SHARE_ZIBT ATTR_ALIGN(32)


#define ATTR_TEXT_IN_RAM                                ATTR_TEXT_IN_SYSRAM
#define ATTR_RODATA_IN_RAM                              ATTR_RODATA_IN_SYSRAM
#define ATTR_RWDATA_IN_NONCACHED_RAM                    ATTR_RWDATA_IN_NONCACHED_SYSRAM
#define ATTR_ZIDATA_IN_NONCACHED_RAM                    ATTR_ZIDATA_IN_NONCACHED_SYSRAM
#define ATTR_RWDATA_IN_NONCACHED_RAM_ALIGN(X)           ATTR_RWDATA_IN_NONCACHED_RAM ATTR_ALIGN(X)
#define ATTR_ZIDATA_IN_NONCACHED_RAM_ALIGN(X)           ATTR_ZIDATA_IN_NONCACHED_RAM ATTR_ALIGN(X)

#define ATTR_RWDATA_IN_NONCACHED_RAM_4BYTE_ALIGN        ATTR_RWDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN
#define ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN        ATTR_ZIDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN
#define ATTR_RWDATA_IN_NONCACHED_RAM_8BYTE_ALIGN        ATTR_RWDATA_IN_NONCACHED_SYSRAM_8BYTE_ALIGN
#define ATTR_ZIDATA_IN_NONCACHED_RAM_8BYTE_ALIGN        ATTR_ZIDATA_IN_NONCACHED_SYSRAM_8BYTE_ALIGN
#define ATTR_RWDATA_IN_NONCACHED_RAM_16BYTE_ALIGN       ATTR_RWDATA_IN_NONCACHED_SYSRAM_16BYTE_ALIGN
#define ATTR_ZIDATA_IN_NONCACHED_RAM_16BYTE_ALIGN       ATTR_ZIDATA_IN_NONCACHED_SYSRAM_16BYTE_ALIGN
#define ATTR_RWDATA_IN_NONCACHED_RAM_32BYTE_ALIGN       ATTR_RWDATA_IN_NONCACHED_SYSRAM_32BYTE_ALIGN
#define ATTR_ZIDATA_IN_NONCACHED_RAM_32BYTE_ALIGN       ATTR_ZIDATA_IN_NONCACHED_SYSRAM_32BYTE_ALIGN

#if CONFIG_MCUBOOT
#define ATTR_ROM_PARAMETER                              ATTR_DATA_DECLARE(".rom_parameter") ATTR_ALIGN(0x100)
#endif


#if defined(CORE_MCU)
/*
 * __attribute__((cmse_nonsecure_entry)):
 *    The attribute specified in the GCC document to implement Non-Secure Callable.
 *
 * __attribute__((used)):
 *    Because the Non-Secure Callable function is exported to the Non-Secure executable file, it may not be used in Secure.
 *    To avoid this function from being optimized, this attribute is added.
 *
 * ATTR_TEXT_IN_TCM:
 *    Because the cache-related code needs to be executed on the TCM,
 *    and the b.w jump instruction is used in the code generated by the compiler and linker for the Non-Secure Callable,
 *    the jump has a range of plus or minus 16MB, which requires all Non-Secure Callable code to be placed in the specified same location.
 */
#ifdef AIR_LIMIT_TZ_ENABLE
    #ifdef  AIR_CPU_IN_SECURITY_MODE
        #define ATTR_NSC_TEXT                           __attribute__((cmse_nonsecure_entry)) ATTR_USED ATTR_TEXT_IN_TCM
    #else
        #define ATTR_NSC_TEXT                           "Should not use NSC service without opening CMSE !!!"
    #endif
#else
    #define ATTR_NSC_TEXT                               ATTR_TEXT_IN_TCM
#endif /* AIR_LIMIT_TZ_ENABLE */

#endif /* if defined(CORE_MCU) */

#endif /* __MEMORY_ATTRIBUTE_H__ */
