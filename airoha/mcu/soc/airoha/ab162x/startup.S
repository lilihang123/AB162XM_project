/* Copyright Statement:
 *
 * (C) 2022  Airoha Technology Corp. All rights reserved.
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

.file "startup.S"
.syntax unified
.cpu cortex-m33
.arch	armv8-m.main
.thumb

#ifdef AIR_CPU_IN_SECURITY_MODE 
.equ    WDT_Base,           0x42090000
.equ    WDT1_Base,          0x42090030
#else
.equ    WDT_Base,           0x52090000
.equ    WDT1_Base,          0x52090030
#endif

.equ    WDT_Disable,        0x10
.equ    WDT_Enable,         0x110
.equ    WDT_Length_Value,   0x02000012  /* 15.625*N << 16 | 0x12 = 8s */
.equ    WDT_RST_Key,        0x1456789A
.equ    WDT_RST_Mask,       0x00260000
.equ    WDT1_Disable,       0x40

#ifdef HAL_CACHE_REGION_CONVERT
.equ    Remap_Base,         0xE0181000
.equ    Remap_Entry_HI0,    0x2406000B      /* size: 5 <=> 16KB, enable */
.equ    Remap_Entry_LO0,    0x04060000
.equ    Remap_Entry_HI1,    0x3406000B      /* size: 5 <=> 16KB, enable */
.equ    Remap_Entry_LO1,    0x14060000
#endif

/**
 * @brief  reset_handler is the entry point that processor starts to boot
 * @param  None
 * @retval : None
*/

  .section  .reset_handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:
    /* interrupt disable */
    cpsid i

    /* Clear SP Limit Registers so that we can set SP safely */
    movs  r0, #0
    msr MSPLIM, r0
    msr PSPLIM, r0

    /* Disable MPU */
    ldr r0, =0xE000ED94
    ldr r1, [r0]
    bic r1, r1, #1
    str r1, [r0]

    /* set stack pointer */
    ldr  sp, =_stack_end

    /* make virtual space available */
#ifdef HAL_CACHE_REGION_CONVERT
    ldr  r0, =Remap_Entry_HI0
    ldr  r1, =Remap_Entry_LO0
    ldr  r3, =Remap_Entry_HI1
    ldr  r4, =Remap_Entry_LO1
    ldr  r2, =Remap_Base
    str  r0, [r2], #4
    str  r1, [r2], #4
    str  r3, [r2], #4
    str  r4, [r2, #0]
#endif

/* config watch dog channel-0 */
#ifdef CONFIG_AIR_WDT
    ldr  r0, =WDT_Base
    ldr  r1, =WDT_Enable
    str  r1, [r0, #0x0]
    ldr  r1, =WDT_Length_Value
    str  r1, [r0, #0x4]
    ldr  r1, =WDT_RST_Mask
    str  r1, [r0, #0x84]
    ldr  r1, =WDT_RST_Key
    str  r1, [r0, #0xC]
#else
    ldr  r0, =WDT_Base
    ldr  r1, =WDT_Disable
    str  r1, [r0, #0]
#endif /* MTK_BOOT_UP_DISABLE_WDT */

    /* watch dog channel-1 disable */
    ldr  r0, =WDT1_Base
    ldr  r1, =WDT1_Disable
    str  r1, [r0, #0]

#ifdef CONFIG_MCUBOOT
    /* used for preparing reset firmware or debugging */
    @ b .
    /* placeholder added for possible future debug requirements */
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
#endif

#ifdef CONFIG_FLASH_BOOTING
    /* preinit cache to accelerate region init progress */
    bl CachePreInit
#endif

#ifndef CONFIG_SKIP_ZI
    /* stack space zero init */
    movs  r0, #0
    ldr  r1, =_stack_start
    ldr  r2, =_stack_end
FillZero:
    str  r0, [r1], #4
    cmp  r1, r2
    blo  FillZero
#endif

#ifdef CONFIG_FLASH_BOOTING
    /* tcm section init */
    ldr  r1, =_tcm_text_load
    ldr  r2, =_tcm_text_start
    ldr  r3, =_tcm_text_end
    bl  Data_Init

    ldr  r1, =__tcm_text_retention_load
    ldr  r2, =__tcm_text_retention_start
    ldr  r3, =__tcm_text_retention_end
    bl  Data_Init

    ldr  r1, =_tcm_rw_bt_data_non_retention_load
    ldr  r2, =_tcm_rw_bt_data_non_retention_start
    ldr  r3, =_tcm_rw_bt_data_non_retention_end
    bl  Data_Init

    ldr  r1, =_tcm_rw_data_non_retention_load
    ldr  r2, =_tcm_rw_data_non_retention_start
    ldr  r3, =_tcm_rw_data_non_retention_end
    bl  Data_Init

    ldr  r2, =_tcm_zi_bt_data_non_retention_start
    ldr  r3, =_tcm_zi_bt_data_non_retention_end
    bl  Bss_Init

    ldr  r2, =_tcm_zi_data_non_retention_start
    ldr  r3, =_tcm_zi_data_non_retention_end
    bl  Bss_Init
#endif /* CONFIG_FLASH_BOOTING */

    /* for sram_bt, load view is sram */
    /* bt share data section init */
    ldr  r1, =_bt_sysram_rw_data_load
    ldr  r2, =_bt_sysram_rw_data_start
    ldr  r3, =_bt_sysram_rw_data_end
    bl  Data_Init

#ifndef CONFIG_SKIP_ZI
    /* bt share zidata section init */
    ldr  r2, =_bt_sysram_zi_data_start
    ldr  r3, =_bt_sysram_zi_data_end
    bl  Bss_Init
#endif

    /* Call the zephyr's entry point.*/
    ldr r0, =z_arm_reset
    bx r0
    bx  lr
.size  Reset_Handler, .-Reset_Handler

/**
 * @brief  This is data init sub-function
 * @param  None
 * @retval None
*/
  .global Data_Init
  .section  .reset_handler.Data_Init,"ax",%progbits
Data_Init:
CopyDataLoop:
    cmp     r2, r3
    ittt    lo
    ldrlo   r0, [r1], #4
    strlo   r0, [r2], #4
    blo     CopyDataLoop
    bx  lr
  .size  Data_Init, .-Data_Init

/**
 * @brief  This is bss init sub-function
 * @param  None
 * @retval None
*/
  .global Bss_Init
  .section  .reset_handler.Bss_Init,"ax",%progbits
Bss_Init:
ZeroBssLoop:
    cmp     r2, r3
    ittt    lo
    movlo   r0, #0
    strlo   r0, [r2], #4
    blo     ZeroBssLoop
    bx  lr
  .size  Bss_Init, .-Bss_Init
