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

.section .text

.align 4
reset_handler:
    /* set all registers to zero */
    mv  x1, x0
    mv  x2, x0
    mv  x3, x0
    mv  x4, x0
    mv  x5, x0
    mv  x6, x0
    mv  x7, x0
    mv  x8, x0
    mv  x9, x0
    mv x10, x0
    mv x11, x0
    mv x12, x0
    mv x13, x0
    mv x14, x0
    mv x15, x0
#if 0
    mv x16, x0
    mv x17, x0
    mv x18, x0
    mv x19, x0
    mv x20, x0
    mv x21, x0
    mv x22, x0
    mv x23, x0
    mv x24, x0
    mv x25, x0
    mv x26, x0
    mv x27, x0
    mv x28, x0
    mv x29, x0
    mv x30, x0
    mv x31, x0
#endif

    /* stack initilization, x2 is stack pointer */
    la   x2, _stack_start

_start:
    .global _start

    /* clear BSS */
    la x3, _bss_start
    la x4, _bss_end

    bge x3, x4, zero_loop_end

zero_loop:
    sw x0, 0(x3)
    addi x3, x3, 4
    ble x3, x4, zero_loop
zero_loop_end:

    /* ISR/Thread Stack Initialize */
    li x5, 0xA5A5A5A5
    la x3, _isr_stack_begin
    la x4, _isr_stack_end
    jal x1, fix_data_init

    la x3, _thread_stack_begin
    la x4, _thread_stack_end
    jal x1, fix_data_init

main_entry:
    /* jump to main program entry point (argc = argv = 0) */
    addi x10, x0, 0
    addi x11, x0, 0
    jal x1, main
    j .

/* =================================================== [ exceptions ] === */
/* This section has to be down here, since we have to disable rvc for it  */
.extern aiorha_exc_handler
.extern airoha_int_handler
    .section .vectors, "ax"
    .option norvc;

    // All unimplemented interrupts/exceptions go to the default_exc_handler.
    .org 0x00
    jal x0, aiorha_exc_handler
    .rept 30
    jal x0, airoha_int_handler
    .endr
    jal x0, aiorha_exc_handler

    // reset vector
    .org 0x80
    jal x0, reset_handler


    .global fix_data_init
/* fill x3~x4 will x5 */
fix_data_init:
    bge     x3, x4, fix_data_init_end
    sw      x5, 0(x3)
    addi    x3, x3, 4
    j       fix_data_init
fix_data_init_end:
    ret