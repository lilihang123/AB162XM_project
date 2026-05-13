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
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
 * RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
 * TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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

/*
 * SPDX-License-Identifier: Apache-2.0
 */

. = ALIGN(4);
_tcm_text_start = .;

/* !!! NOTE !!!
    * From ARMv8-M Architecture Reference Manual:
    * In a PE with a configurable vector table base,
    * the vector table must be naturally aligned to
    * a power of two, with an alignment value that is:
    *    1. A minimum of 128 bytes.
    *    2. Greater than or equal to ( Number of Exceptions supported x4).
    */
. = ALIGN(128);
exception_num = 16 + CONFIG_NUM_IRQS;               /* 16 exceptions + IRQs Airoha defined */
. = ALIGN( 1 << LOG2CEIL(exception_num*4));         /* power of two, round up */

_vector_start = .;

KEEP(*(.isr_vector))
KEEP(*(.gnu.linkonce.irq_vector_table*))
KEEP(*(.vectors))
*(.exception_code*)
/* The scheduler needs pendsv, and the exception handler must be placed in TCM. */
*swap_helper.S.obj(.text*)
*libkernel.a:*.c.obj(.text*)

*(.exception_rodata*)
*(.tcm_code_retention*)
*(.ram_code*)
*(.tcm_code*)
*(.sysram_code*)
*(.tcm_rodata*)
*(.ram_rodata*)
*(.sysram_rodata*)

#if CONFIG_FLASH_BOOTING
*libpka*.a:*.c.obj(.text*)
#endif

. = ALIGN(4);
_tcm_text_end = .;
_vector_end = .;


