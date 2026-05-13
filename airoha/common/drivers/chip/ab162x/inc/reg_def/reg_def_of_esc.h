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

#ifndef __ESC_REG_DEFINITION_H__
#define __ESC_REG_DEFINITION_H__


#include <stdint.h>

/* structure type of ESC
 */
#define ESC_GPRAM_BASE  (ESC_BASE + 0x800)
typedef struct {
    __IO uint32_t ESC_MAC_CTL;
    __IO uint32_t ESC_DIRECT_CTL;
    __IO uint32_t ESC_MISC_CTL1;
    __IO uint32_t ESC_MISC_CTL2;
    __IO uint32_t ESC_MAC_OUTL;
    __IO uint32_t ESC_MAC_INL;
    __IO uint32_t ESC_STA1_CTL;
    __IO uint32_t ESC_STA2_CTL;
    __IO uint32_t ESC_DLY_CTL1;
    __IO uint32_t ESC_DLY_CTL2;
    __IO uint32_t ESC_DLY_CTL3;
    __IO uint32_t reserve0[1];
    __IO uint32_t ESC_DMY_BYTE;
    __IO uint32_t reserve1[5];
    __IO uint32_t ESC_STA3;
    __IO uint32_t reserve2[5];
    __IO uint32_t ESC_DEBUG_1;
    __IO uint32_t ESC_DEBUG_2;
    __IO uint32_t reserve3[2];
    __IO uint32_t ESC_DEBUG_MUX;
    __IO uint32_t reserve4[3];
    __IO uint32_t ESC_MISC_CTL3;
    __IO uint32_t ESC_MAC_IRQ;
} ESC_REGISTER_T;

#ifdef AIR_CPU_IN_SECURITY_MODE
#define ESC_GENERIC_MEM_BANK_MASK  (0x07000000)
#else
#define SFC_GENERIC_MEM_BANK_MASK  (0x17000000)
#endif


#endif /* __ESC_REG_DEFINITION_H__ */