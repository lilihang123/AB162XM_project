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

#ifndef __SRAMPWRCTRL_REG_DEFINITION_H__
#define __SRAMPWRCTRL_REG_DEFINITION_H__
#include <stdint.h>


/*************************** SRAMPWRCTRL register definition start line  ********************************/

/* SRAMPWRCTRL RGs */

#define MEMORY_SYSRAM_STATUS                        (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0000 ) 
#define MEMORY_CHAIN_CONTROL                        (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0004 ) 
#define SYSRAM_PWR_STATUS                           (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0008 ) 
#define SYSRAM_PWR_STATUS_2ND                       (volatile uint32_t*)( SRAM_PWR_CTRL + 0x000C ) 
#define SYSRAM0_PWR_CON                             (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0010 ) 
#define SYSRAM1_PWR_CON                             (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0014 ) 
#define SYSRAM2_PWR_CON                             (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0018 ) 
#define SYSRAM3_PWR_CON                             (volatile uint32_t*)( SRAM_PWR_CTRL + 0x001C ) 
#define SYSRAM4_5_PWR_CON                           (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0020 ) 
#define SYSRAM6_PWR_CON                             (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0024 ) 
#define SYSRAM7_PWR_CON                             (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0028 ) 
#define SYSRAM8_PWR_CON                             (volatile uint32_t*)( SRAM_PWR_CTRL + 0x002C ) 
#define SRAM_PWR_CON0                               (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0030 ) 
#define SRAM_PWR_CON1                               (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0034 ) 
#define SRAM_PWR_CON2                               (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0038 ) 
#define SRAM_PWR_CON3                               (volatile uint32_t*)( SRAM_PWR_CTRL + 0x003C ) 
#define MEMORY_SYSRAM0_CONTROL_0                    (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0100 ) 
#define MEMORY_SYSRAM0_CONTROL_1                    (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0104 ) 
#define MEMORY_SYSRAM0_CONTROL_2                    (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0108 ) 
#define MEMORY_SYSRAM1_5_CONTROL_0                  (volatile uint32_t*)( SRAM_PWR_CTRL + 0x010c ) 
#define MEMORY_SYSRAM1_5_CONTROL_1                  (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0110 ) 
#define MEMORY_SYSRAM1_5_CONTROL_2                  (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0114 ) 
#define MEMORY_SYSRAM6_CONTROL_0                    (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0118 ) 
#define MEMORY_SYSRAM6_CONTROL_1                    (volatile uint32_t*)( SRAM_PWR_CTRL + 0x011c ) 
#define MEMORY_SYSRAM6_CONTROL_2                    (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0120 ) 
#define MEMORY_SPM_CONTROL_0                        (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0124 ) 
#define MEMORY_SPM_CONTROL_1                        (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0128 ) 
#define MEMORY_SPM_CONTROL_2                        (volatile uint32_t*)( SRAM_PWR_CTRL + 0x012c ) 
#define MEMORY_RISCV_CONTROL_0                       (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0130 ) 
#define MEMORY_RISCV_CONTROL_1                       (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0134 ) 
#define MEMORY_RISCV_CONTROL_2                       (volatile uint32_t*)( SRAM_PWR_CTRL + 0x0138 ) 

#endif /* __SRAMPWRCTRL_REG_DEFINITION_H__ */