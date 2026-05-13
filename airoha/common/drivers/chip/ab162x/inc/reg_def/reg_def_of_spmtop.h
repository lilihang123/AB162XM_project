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

#ifndef __SPMTOP_REG_DEFINITION_H__
#define __SPMTOP_REG_DEFINITION_H__
#include <stdint.h>


/*************************** SPMTOP register definition start line  ********************************/

/* Internal SPM RGs */
#define SPM_TOP_POWER_ON_VAL0                                                                  (volatile uint32_t*)( SPM_TOP_BASE + 0x0000 )
#define SPM_TOP_POWER_ON_VAL1                                                                  (volatile uint32_t*)( SPM_TOP_BASE + 0x0004 )
#define SPM_TOP_CMSYS_PWR_CON                                                                  (volatile uint32_t*)( SPM_TOP_BASE + 0x0008 )
#define SPM_TOP_INFRA_PWR_CON                                                                  (volatile uint32_t*)( SPM_TOP_BASE + 0x000C )
#define SPM_TOP_CONN_TOP_OFF_PWR_CON                                                           (volatile uint32_t*)( SPM_TOP_BASE + 0x0010 )
#define SPM_TOP_PCM_CON0                                                                       (volatile uint32_t*)( SPM_TOP_BASE + 0x0014 )
#define SPM_TOP_PCM_CON1                                                                       (volatile uint32_t*)( SPM_TOP_BASE + 0x0018 )
#define SPM_TOP_PCM_IM_PTR                                                                     (volatile uint32_t*)( SPM_TOP_BASE + 0x001C )
#define SPM_TOP_PCM_IM_LEN                                                                     (volatile uint32_t*)( SPM_TOP_BASE + 0x0020 )
#define SPM_TOP_PCM_IM_HOST_RW_PTR                                                             (volatile uint32_t*)( SPM_TOP_BASE + 0x0024 )
#define SPM_TOP_PCM_IM_HOST_RW_DAT                                                             (volatile uint32_t*)( SPM_TOP_BASE + 0x0028 )
#define SPM_TOP_PCM_REG_DATA_INI                                                               (volatile uint32_t*)( SPM_TOP_BASE + 0x002C )
#define SPM_TOP_PCM_EVENT_VECTOR0                                                              (volatile uint32_t*)( SPM_TOP_BASE + 0x0030 )
#define SPM_TOP_PCM_EVENT_VECTOR1                                                              (volatile uint32_t*)( SPM_TOP_BASE + 0x0034 )
#define SPM_TOP_PCM_EVENT_VECTOR2                                                              (volatile uint32_t*)( SPM_TOP_BASE + 0x0038 )
#define SPM_TOP_PCM_EVENT_VECTOR3                                                              (volatile uint32_t*)( SPM_TOP_BASE + 0x003C )
#define SPM_TOP_PCM_EVENT_VECTOR4                                                              (volatile uint32_t*)( SPM_TOP_BASE + 0x0040 )
#define SPM_TOP_PCM_EVENT_VECTOR5                                                              (volatile uint32_t*)( SPM_TOP_BASE + 0x0044 )
#define SPM_TOP_PCM_EVENT_VECTOR6                                                              (volatile uint32_t*)( SPM_TOP_BASE + 0x0048 )
#define SPM_TOP_PCM_EVENT_VECTOR7                                                              (volatile uint32_t*)( SPM_TOP_BASE + 0x004C )
#define SPM_TOP_PCM_PWR_IO_EN                                                                  (volatile uint32_t*)( SPM_TOP_BASE + 0x0050 )
#define SPM_TOP_PCM_TIMER_VAL                                                                  (volatile uint32_t*)( SPM_TOP_BASE + 0x0054 )
#define SPM_TOP_PCM_REGC_WAKEUP_MASK                                                           (volatile uint32_t*)( SPM_TOP_BASE + 0x0058 )
#define SPM_TOP_SLEEP_WAKEUP_EVENT_MASK                                                        (volatile uint32_t*)( SPM_TOP_BASE + 0x005C )
#define SPM_TOP_SW_DEEP_SLEEP                                                                  (volatile uint32_t*)( SPM_TOP_BASE + 0x0060 )
#define SPM_TOP_SLEEP_ISR_MASK                                                                 (volatile uint32_t*)( SPM_TOP_BASE + 0x0064 )
#define SPM_TOP_PCM_WDT_TIMER_OUT                                                              (volatile uint32_t*)( SPM_TOP_BASE + 0x0068 )
#define SPM_TOP_CLK_SETTLE                                                                     (volatile uint32_t*)( SPM_TOP_BASE + 0x006C )
#define SPM_TOP_PCM_WDT_TIMER_VAL                                                              (volatile uint32_t*)( SPM_TOP_BASE + 0x0070 )
#define SPM_TOP_PCM_WDT_LATCH                                                                  (volatile uint32_t*)( SPM_TOP_BASE + 0x0074 )
#define SPM_TOP_DUMMY_REG_A                                                                    (volatile uint32_t*)( SPM_TOP_BASE + 0x0078 )
#define SPM_TOP_DUMMY_REG_B                                                                    (volatile uint32_t*)( SPM_TOP_BASE + 0x007C )
#define SPM_TOP_INFRA_FAKE_PWR                                                                 (volatile uint32_t*)( SPM_TOP_BASE + 0x0080 )
#define SPM_TOP_CONN_FAKE_PWR                                                                  (volatile uint32_t*)( SPM_TOP_BASE + 0x0084 )
#define SPM_TOP_CONN_BACKUP_RESTORE_PTR                                                        (volatile uint32_t*)( SPM_TOP_BASE + 0x0088 )
#define SPM_TOP_CONN_MTCMOS_ENABLE_FW                                                          (volatile uint32_t*)( SPM_TOP_BASE + 0x008C )
#define SPM_TOP_CONN_BACKUP_RESTORE_CTL                                                        (volatile uint32_t*)( SPM_TOP_BASE + 0x0090 )
#define SPM_TOP_DUMMY_REG_C                                                                    (volatile uint32_t*)( SPM_TOP_BASE + 0x0094 )
#define SPM_TOP_DUMMY_REG_D                                                                    (volatile uint32_t*)( SPM_TOP_BASE + 0x0098 )
#define SPM_TOP_CLOCK_RDY                                                                      (volatile uint32_t*)( SPM_TOP_BASE + 0x0104 )
#define SPM_TOP_PCM_FLAGS                                                                      (volatile uint32_t*)( SPM_TOP_BASE + 0x0108 )
#define SPM_TOP_SLEEP_ISR_STATUS                                                               (volatile uint32_t*)( SPM_TOP_BASE + 0x010C )
#define SPM_TOP_ALL_WAKEUP_SOURCE_STA_IN_B                                                     (volatile uint32_t*)( SPM_TOP_BASE + 0x0110 )
#define SPM_TOP_PCM_RESERVE                                                                    (volatile uint32_t*)( SPM_TOP_BASE + 0x0114 )
#define SPM_TOP_PCM_RESERVE2                                                                   (volatile uint32_t*)( SPM_TOP_BASE + 0x0118 )
#define SPM_TOP_PCM_REG0_DATA                                                                  (volatile uint32_t*)( SPM_TOP_BASE + 0x011C )
#define SPM_TOP_PCM_REG1_DATA                                                                  (volatile uint32_t*)( SPM_TOP_BASE + 0x0120 )
#define SPM_TOP_PCM_REG2_DATA                                                                  (volatile uint32_t*)( SPM_TOP_BASE + 0x0124 )
#define SPM_TOP_PCM_REG3_DATA                                                                  (volatile uint32_t*)( SPM_TOP_BASE + 0x0128 )
#define SPM_TOP_PCM_REG4_DATA                                                                  (volatile uint32_t*)( SPM_TOP_BASE + 0x012C )
#define SPM_TOP_PCM_REG5_DATA                                                                  (volatile uint32_t*)( SPM_TOP_BASE + 0x0130 )
#define SPM_TOP_PCM_REG6_DATA                                                                  (volatile uint32_t*)( SPM_TOP_BASE + 0x0134 )
#define SPM_TOP_PCM_REG7_DATA                                                                  (volatile uint32_t*)( SPM_TOP_BASE + 0x0138 )
#define SPM_TOP_PCM_REG8_DATA                                                                  (volatile uint32_t*)( SPM_TOP_BASE + 0x013C )
#define SPM_TOP_PCM_REG9_DATA                                                                  (volatile uint32_t*)( SPM_TOP_BASE + 0x0140 )
#define SPM_TOP_PCM_REG10_DATA                                                                 (volatile uint32_t*)( SPM_TOP_BASE + 0x0144 )
#define SPM_TOP_PCM_REG11_DATA                                                                 (volatile uint32_t*)( SPM_TOP_BASE + 0x0148 )
#define SPM_TOP_PCM_REG12_DATA                                                                 (volatile uint32_t*)( SPM_TOP_BASE + 0x014C )
#define SPM_TOP_PCM_REG13_DATA                                                                 (volatile uint32_t*)( SPM_TOP_BASE + 0x0150 )
#define SPM_TOP_PCM_REG14_DATA                                                                 (volatile uint32_t*)( SPM_TOP_BASE + 0x0154 )
#define SPM_TOP_PCM_REG15_DATA                                                                 (volatile uint32_t*)( SPM_TOP_BASE + 0x0158 )
#define SPM_TOP_PCM_SW_INT_SET                                                                 (volatile uint32_t*)( SPM_TOP_BASE + 0x015C )
#define SPM_TOP_PCM_SW_INT_SET_CONN                                                            (volatile uint32_t*)( SPM_TOP_BASE + 0x0160 )
#define SPM_TOP_PCM_SW_INT_SET_INFRA                                                           (volatile uint32_t*)( SPM_TOP_BASE + 0x0164 )
#define SPM_TOP_PCM_SW_INT_SET_RISCV                                                            (volatile uint32_t*)( SPM_TOP_BASE + 0x0168 )
#define SPM_TOP_PCM_RE_INIT                                                                    (volatile uint32_t*)( SPM_TOP_BASE + 0x016C )
#define SPM_TOP_REMAP_ADDR_RG                                                                  (volatile uint32_t*)( SPM_TOP_BASE + 0x0170 )
#define SPM_TOP_PWR_STATUS                                                                     (volatile uint32_t*)( SPM_TOP_BASE + 0x0174 )
#define SPM_TOP_EDGE_WAKEUP_SOURCE                                                             (volatile uint32_t*)( SPM_TOP_BASE + 0x0178 )
#define SPM_TOP_SYS_INTO_EXT_SLP                                                               (volatile uint32_t*)( SPM_TOP_BASE + 0x017C )
#define SPM_TOP_SYSTEM_KEEP_EXTSLP_VALUE                                                       (volatile uint32_t*)( SPM_TOP_BASE + 0x0180 )
#define SPM_TOP_STATE_STATUS                                                                   (volatile uint32_t*)( SPM_TOP_BASE + 0x0184 )
#define SPM_TOP_SPM_26M_CLK_DIV                                                                (volatile uint32_t*)( SPM_TOP_BASE + 0x0188 )
#define SPM_TOP_SPM_AP_SEMA                                                                    (volatile uint32_t*)( SPM_TOP_BASE + 0x018C )
#define SPM_TOP_SPM_SPM_SEMA                                                                   (volatile uint32_t*)( SPM_TOP_BASE + 0x0190 )
#define SPM_TOP_SIDEBAND_CONTROL_0                                                             (volatile uint32_t*)( SPM_TOP_BASE + 0x0194 )
#define SPM_TOP_SLEEP_TWAM_CON_0                                                               (volatile uint32_t*)( SPM_TOP_BASE + 0x0198 )
#define SPM_TOP_SLEEP_TWAM_CON_1                                                               (volatile uint32_t*)( SPM_TOP_BASE + 0x019C )
#define SPM_TOP_SLEEP_TWAM_CON_2                                                               (volatile uint32_t*)( SPM_TOP_BASE + 0x01A0 )
#define SPM_TOP_SLEEP_TWAM_LAST_STATUS0                                                        (volatile uint32_t*)( SPM_TOP_BASE + 0x01A4 )
#define SPM_TOP_SLEEP_TWAM_CURR_STATUS0                                                        (volatile uint32_t*)( SPM_TOP_BASE + 0x01A8 )
#define SPM_TOP_SLEEP_TWAM_TIMER_OUT                                                           (volatile uint32_t*)( SPM_TOP_BASE + 0x01AC )
#define SPM_TOP_SLEEP_TWAM_WINDOW_LEN                                                          (volatile uint32_t*)( SPM_TOP_BASE + 0x01B0 )
#define SPM_TOP_SPM_AO_IDLE                                                                    (volatile uint32_t*)( SPM_TOP_BASE + 0x01B4 )
#define SPM_TOP_SPM_PD_IDLE                                                                    (volatile uint32_t*)( SPM_TOP_BASE + 0x01B8 )

#endif /* __SPMTOP_REG_DEFINITION_H__ */