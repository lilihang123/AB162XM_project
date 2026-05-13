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

#ifndef __SPMCFG_REG_DEFINITION_H__
#define __SPMCFG_REG_DEFINITION_H__
#include <stdint.h>


/*************************** SPMTOP register definition start line  ********************************/

/* External SPM RGs */
#define SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK                                                       (volatile uint32_t*)( SPM_CFG_BASE + 0x0000 )
#define SPM_CFG_INFRA_WAKEUP_SOURCE_MASK                                                       (volatile uint32_t*)( SPM_CFG_BASE + 0x0004 )
#define SPM_CFG_RISCV_WAKEUP_SOURCE_MASK                                                        (volatile uint32_t*)( SPM_CFG_BASE + 0x0008 )
#define SPM_CFG_CONN_WAKEUP_SOURCE_MASK                                                        (volatile uint32_t*)( SPM_CFG_BASE + 0x000C )
#define SPM_CFG_SEQUENCER_32K_REG_1                                                            (volatile uint32_t*)( SPM_CFG_BASE + 0x0010 )
#define SPM_CFG_SEQUENCER_32K_REG_2                                                            (volatile uint32_t*)( SPM_CFG_BASE + 0x0014 )
#define SPM_CFG_SEQUENCER_32K_REG_3                                                            (volatile uint32_t*)( SPM_CFG_BASE + 0x0018 )
#define SPM_CFG_SEQUENCER_32K_REG_4                                                            (volatile uint32_t*)( SPM_CFG_BASE + 0x001C )
#define SPM_CFG_SEQUENCER_32K_REG_5                                                            (volatile uint32_t*)( SPM_CFG_BASE + 0x0020 )
#define SPM_CFG_FSM_XO_REG_6                                                                   (volatile uint32_t*)( SPM_CFG_BASE + 0x0024 )
#define SPM_CFG_SEQUENCER_26M_REG_0                                                            (volatile uint32_t*)( SPM_CFG_BASE + 0x0028 )
#define SPM_CFG_SEQUENCER_26M_REG_1                                                            (volatile uint32_t*)( SPM_CFG_BASE + 0x002C )
#define SPM_CFG_REQUEST_XO_MASK                                                                (volatile uint32_t*)( SPM_CFG_BASE + 0x0030 )
#define SPM_CFG_REQUEST_XO_GATE                                                                (volatile uint32_t*)( SPM_CFG_BASE + 0x0034 )
#define SPM_CFG_SELECT_XO_RDY_SRC                                                              (volatile uint32_t*)( SPM_CFG_BASE + 0x0038 )
#define SPM_CFG_XO_SETTLE_TIME                                                                 (volatile uint32_t*)( SPM_CFG_BASE + 0x003C )
#define SPM_CFG_XO_RESOURCE_TIMING                                                             (volatile uint32_t*)( SPM_CFG_BASE + 0x0040 )
#define SPM_CFG_XO_OUT_OFF_SETTLE_32K_SEL                                                      (volatile uint32_t*)( SPM_CFG_BASE + 0x0044 )
#define SPM_CFG_PERISYS_PWR_CON                                                                (volatile uint32_t*)( SPM_CFG_BASE + 0x0048 )
#define SPM_CFG_SPM_32K_CLKMUX_CONTROL                                                         (volatile uint32_t*)( SPM_CFG_BASE + 0x004C )
#define SPM_CFG_SPM_DEBUG_SELECT                                                               (volatile uint32_t*)( SPM_CFG_BASE + 0x0050 )
#define SPM_CFG_SPM_DEBUG_CON                                                                  (volatile uint32_t*)( SPM_CFG_BASE + 0x0054 )
#define SPM_CFG_CONN_AUDIO_ABB_SIDEBAND_MASK                                                   (volatile uint32_t*)( SPM_CFG_BASE + 0x0058 )
#define SPM_CFG_CONN_SRCLKENA_ACK_SW_CON                                                       (volatile uint32_t*)( SPM_CFG_BASE + 0x005C )
#define SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND                                                     (volatile uint32_t*)( SPM_CFG_BASE + 0x0060 )
#define SPM_CFG_INFRA_DEEP_SLEEP                                                               (volatile uint32_t*)( SPM_CFG_BASE + 0x0064 )
#define SPM_CFG_MASK_PCM_SW_INT_STATE                                                          (volatile uint32_t*)( SPM_CFG_BASE + 0x0068 )
#define SPM_CFG_CMSYS_REQ_EXT_SLP                                                              (volatile uint32_t*)( SPM_CFG_BASE + 0x006C )
#define SPM_CFG_RISCV_REQ_EXT_SLP                                                               (volatile uint32_t*)( SPM_CFG_BASE + 0x0070 )
#define SPM_CFG_CONN_REQ_EXT_SLP                                                               (volatile uint32_t*)( SPM_CFG_BASE + 0x0074 )
#define SPM_CFG_CONN_SLEEP_SET_CFG                                                             (volatile uint32_t*)( SPM_CFG_BASE + 0x0078 )
#define SPM_CFG_SW_DBG_STATE_STATUS                                                            (volatile uint32_t*)( SPM_CFG_BASE + 0x007C )
#define SPM_CFG_CMSYS_ROM_CONTROL                                                              (volatile uint32_t*)( SPM_CFG_BASE + 0x0080 )
#define SPM_CFG_CMSYS_TAGRAM_CONTROL_0                                                         (volatile uint32_t*)( SPM_CFG_BASE + 0x0084 )
#define SPM_CFG_CMSYS_TAGRAM_CONTROL_1                                                         (volatile uint32_t*)( SPM_CFG_BASE + 0x0088 )
#define SPM_CFG_CMSYS_TCM2K_CONTROL_0                                                          (volatile uint32_t*)( SPM_CFG_BASE + 0x008C )
#define SPM_CFG_CMSYS_TCM2K_CONTROL_1                                                          (volatile uint32_t*)( SPM_CFG_BASE + 0x0090 )
#define SPM_CFG_CMSYS_TCM4K_CONTROL_0                                                          (volatile uint32_t*)( SPM_CFG_BASE + 0x0094 )
#define SPM_CFG_CMSYS_TCM4K_CONTROL_1                                                          (volatile uint32_t*)( SPM_CFG_BASE + 0x0098 )
#define SPM_CFG_INFRA_IRTX_CONTROL_0                                                           (volatile uint32_t*)( SPM_CFG_BASE + 0x009C )
#define SPM_CFG_INFRA_IRTX_CONTROL_1                                                           (volatile uint32_t*)( SPM_CFG_BASE + 0x00A0 )
#define SPM_CFG_PERISYS_USB_CONTROL_0                                                          (volatile uint32_t*)( SPM_CFG_BASE + 0x00A4 )
#define SPM_CFG_PERISYS_USB_CONTROL_1                                                          (volatile uint32_t*)( SPM_CFG_BASE + 0x00A8 )
#define SPM_CFG_CONN_MTCMOS_ENABLE                                                             (volatile uint32_t*)( SPM_CFG_BASE + 0x00AC )
#define SPM_CFG_SPM_STATE_CONTROL_0                                                            (volatile uint32_t*)( SPM_CFG_BASE + 0x00B0 )
#define SPM_CFG_SPM_STATE_CONTROL_1                                                            (volatile uint32_t*)( SPM_CFG_BASE + 0x00B4 )
#define SPM_CFG_SLEEP_CMSYS_PWR_MASK_B                                                         (volatile uint32_t*)( SPM_CFG_BASE + 0x00B8 )
#define SPM_CFG_SLEEP_INFRA_PWR_MASK_B                                                         (volatile uint32_t*)( SPM_CFG_BASE + 0x00BC )
#define SPM_CFG_SLEEP_CONN_TOP_OFF_PWR_MASK_B                                                  (volatile uint32_t*)( SPM_CFG_BASE + 0x00C0 )
#define SPM_CFG_SLEEP_AUDIO_PWR_MASK_B                                                         (volatile uint32_t*)( SPM_CFG_BASE + 0x00C4 )
#define SPM_CFG_SLEEP_PERISYS_PWR_MASK_B                                                       (volatile uint32_t*)( SPM_CFG_BASE + 0x00C8 )
#define SPM_CFG_SLEEP_CONN_ZIGBEE_PWR_MASK_B                                                   (volatile uint32_t*)( SPM_CFG_BASE + 0x00CC )
#define SPM_CFG_SPM_ERROR_FLAG                                                                 (volatile uint32_t*)( SPM_CFG_BASE + 0x00D0 )
#define SPM_CFG_RISCV_FAKE_PWR                                                                  (volatile uint32_t*)( SPM_CFG_BASE + 0x00D4 )
#define SPM_CFG_SPM_CFG_DUMMY_REG_A                                                            (volatile uint32_t*)( SPM_CFG_BASE + 0x00D8 )
#define SPM_CFG_SPM_CFG_DUMMY_REG_B                                                            (volatile uint32_t*)( SPM_CFG_BASE + 0x00DC )
#define SPM_CFG_SPM_CFG_DUMMY_REG_C                                                            (volatile uint32_t*)( SPM_CFG_BASE + 0x00E0 )
#define SPM_CFG_SPM_CFG_DUMMY_REG_D                                                            (volatile uint32_t*)( SPM_CFG_BASE + 0x00E4 )
#define SPM_CFG_CLK_HANDLE_SELECT                                                              (volatile uint32_t*)( SPM_CFG_BASE + 0x00E8 )
#define SPM_CFG_CMSYS_WAKEUP_EVENT                                                             (volatile uint32_t*)( SPM_CFG_BASE + 0x0100 )
#define SPM_CFG_INFRA_WAKEUP_EVENT                                                             (volatile uint32_t*)( SPM_CFG_BASE + 0x0104 )
#define SPM_CFG_RISCV_WAKEUP_EVENT                                                              (volatile uint32_t*)( SPM_CFG_BASE + 0x0108 )
#define SPM_CFG_CONN_WAKEUP_EVENT                                                              (volatile uint32_t*)( SPM_CFG_BASE + 0x010C )
#define SPM_CFG_RESOURCE_CONTROL_0                                                             (volatile uint32_t*)( SPM_CFG_BASE + 0x0110 )
#define SPM_CFG_SEQUENCER_32K_REG_0                                                            (volatile uint32_t*)( SPM_CFG_BASE + 0x0114 )
#define SPM_CFG_SIDEBAND_CONTROL_1                                                             (volatile uint32_t*)( SPM_CFG_BASE + 0x0118 )
#define SPM_CFG_SIDEBAND_CONTROL_2                                                             (volatile uint32_t*)( SPM_CFG_BASE + 0x011C )
#define SPM_CFG_IGNORE_CPU_ACTIVE                                                              (volatile uint32_t*)( SPM_CFG_BASE + 0x0120 )
#define SPM_CFG_EVENT_CONTROL_0                                                                (volatile uint32_t*)( SPM_CFG_BASE + 0x0124 )
#define SPM_CFG_EVENT_CONTROL_1                                                                (volatile uint32_t*)( SPM_CFG_BASE + 0x0128 )
#define SPM_CFG_CMSYS_ABORT_FLAG                                                               (volatile uint32_t*)( SPM_CFG_BASE + 0x012C )
#define SPM_CFG_INFRA_ABORT_FLAG                                                               (volatile uint32_t*)( SPM_CFG_BASE + 0x0130 )
#define SPM_CFG_CONN_ABORT_FLAG                                                                (volatile uint32_t*)( SPM_CFG_BASE + 0x0134 )
#define SPM_CFG_RISCV_ABORT_FLAG                                                                (volatile uint32_t*)( SPM_CFG_BASE + 0x0138 )
#define SPM_CFG_PCM_SW_INT_CLEAR                                                               (volatile uint32_t*)( SPM_CFG_BASE + 0x013C )
#define SPM_CFG_PCM_SW_INT_CLEAR_CONN                                                          (volatile uint32_t*)( SPM_CFG_BASE + 0x0140 )
#define SPM_CFG_PCM_SW_INT_CLEAR_INFRA                                                         (volatile uint32_t*)( SPM_CFG_BASE + 0x0144 )
#define SPM_CFG_PCM_SW_INT_CLEAR_RISCV                                                          (volatile uint32_t*)( SPM_CFG_BASE + 0x0148 )
#define SPM_CFG_PCM_SW_INT_STATE                                                               (volatile uint32_t*)( SPM_CFG_BASE + 0x014C )
#define SPM_CFG_AUDIO_PWR_CON                                                                  (volatile uint32_t*)( SPM_CFG_BASE + 0x0150 )
#define SPM_CFG_CONN_ZIGBEE_PWR_CON                                                            (volatile uint32_t*)( SPM_CFG_BASE + 0x0154 )
#define SPM_CFG_CMSYS_WAKEUP_SOURCE_STA_IN_B                                                   (volatile uint32_t*)( SPM_CFG_BASE + 0x0158 )
#define SPM_CFG_CMSYS_WAKEUP_SOURCE_STA                                                        (volatile uint32_t*)( SPM_CFG_BASE + 0x015C )
#define SPM_CFG_CMSYS_WAKEUP_SOURCE_STA_32K                                                    (volatile uint32_t*)( SPM_CFG_BASE + 0x0160 )
#define SPM_CFG_INFRA_WAKEUP_SOURCE_STA_IN_B                                                   (volatile uint32_t*)( SPM_CFG_BASE + 0x0164 )
#define SPM_CFG_INFRA_WAKEUP_SOURCE_STA                                                        (volatile uint32_t*)( SPM_CFG_BASE + 0x0168 )
#define SPM_CFG_INFRA_WAKEUP_SOURCE_STA_32K                                                    (volatile uint32_t*)( SPM_CFG_BASE + 0x016C )
#define SPM_CFG_RISCV_WAKEUP_SOURCE_STA_IN_B                                                    (volatile uint32_t*)( SPM_CFG_BASE + 0x0170 )
#define SPM_CFG_RISCV_WAKEUP_SOURCE_STA                                                         (volatile uint32_t*)( SPM_CFG_BASE + 0x0174 )
#define SPM_CFG_RISCV_WAKEUP_SOURCE_STA_32K                                                     (volatile uint32_t*)( SPM_CFG_BASE + 0x0178 )
#define SPM_CFG_CONN_WAKEUP_SOURCE_STA_IN_B                                                    (volatile uint32_t*)( SPM_CFG_BASE + 0x017C )
#define SPM_CFG_CONN_WAKEUP_SOURCE_STA                                                         (volatile uint32_t*)( SPM_CFG_BASE + 0x0180 )
#define SPM_CFG_CONN_WAKEUP_SOURCE_STA_32K                                                     (volatile uint32_t*)( SPM_CFG_BASE + 0x0184 )
#define SPM_CFG_ALL_WAKEUP_SOURCE_STA_IN_B                                                     (volatile uint32_t*)( SPM_CFG_BASE + 0x0188 )
#define SPM_CFG_PWR_STATUS                                                                     (volatile uint32_t*)( SPM_CFG_BASE + 0x018C )
#define SPM_CFG_PWR_STATUS_2ND                                                                 (volatile uint32_t*)( SPM_CFG_BASE + 0x0190 )
#define SPM_CFG_CONN_SLEEP_INFO                                                                (volatile uint32_t*)( SPM_CFG_BASE + 0x0194 )
#define SPM_CFG_SPM_26M_CLK_FORCE_ON                                                           (volatile uint32_t*)( SPM_CFG_BASE + 0x0198 )
#define SPM_CFG_BUS_CLK_IDLE                                                                   (volatile uint32_t*)( SPM_CFG_BASE + 0x019C )
#define SPM_CFG_BUS_IDLE_STATUS                                                                (volatile uint32_t*)( SPM_CFG_BASE + 0x01A0 )
#define SPM_CFG_SLEEP_ISR_RAW_STA                                                              (volatile uint32_t*)( SPM_CFG_BASE + 0x01A4 )
#define SPM_CFG_CONN_SIDEBAND_0                                                                (volatile uint32_t*)( SPM_CFG_BASE + 0x01A8 )
#define SPM_CFG_CONN_SIDEBAND_1                                                                (volatile uint32_t*)( SPM_CFG_BASE + 0x01AC )
#define SPM_CFG_PCM_TIMER_OUT                                                                  (volatile uint32_t*)( SPM_CFG_BASE + 0x01B0 )
#define SPM_CFG_PCM_EVENT_REG_STA                                                              (volatile uint32_t*)( SPM_CFG_BASE + 0x01B4 )
#define SPM_CFG_PCM_FSM_STA                                                                    (volatile uint32_t*)( SPM_CFG_BASE + 0x01B8 )
#define SPM_CFG_CLOCK_RDY                                                                      (volatile uint32_t*)( SPM_CFG_BASE + 0x01BC )
#define SPM_CFG_CMSYS_TAGRAM_CONTROL_2                                                         (volatile uint32_t*)( SPM_CFG_BASE + 0x01C0 )
#define SPM_CFG_CMSYS_TCM2K_CONTROL_2                                                          (volatile uint32_t*)( SPM_CFG_BASE + 0x01C4 )
#define SPM_CFG_CMSYS_TCM4K_CONTROL_2                                                          (volatile uint32_t*)( SPM_CFG_BASE + 0x01C8 )
#define SPM_CFG_INFRA_IRTX_CONTROL_2                                                           (volatile uint32_t*)( SPM_CFG_BASE + 0x01CC )
#define SPM_CFG_PERISYS_USB_CONTROL_2                                                          (volatile uint32_t*)( SPM_CFG_BASE + 0x01D0 )
#define SPM_CFG_AUDIO_MEMIF_CONTROL_0                                                          (volatile uint32_t*)( SPM_CFG_BASE + 0x01D4 )
#define SPM_CFG_AUDIO_MEMIF_CONTROL_1                                                          (volatile uint32_t*)( SPM_CFG_BASE + 0x01D8 )
#define SPM_CFG_AUDIO_MEMIF_CONTROL_2                                                          (volatile uint32_t*)( SPM_CFG_BASE + 0x01DC )
#define SPM_CFG_CONN_MTCMOS_FLOW_FW                                                            (volatile uint32_t*)( SPM_CFG_BASE + 0x01E0 )
#define SPM_CFG_CONN_MTCMOS_FLOW_SW                                                            (volatile uint32_t*)( SPM_CFG_BASE + 0x01E4 )
#define SPM_CFG_MONITOR_WAKEUP_EVENT_EN                                                        (volatile uint32_t*)( SPM_CFG_BASE + 0x01E8 )
#define SPM_CFG_CMSYS_REQUEST_XO_CON                                                           (volatile uint32_t*)( SPM_CFG_BASE + 0x01EC )
#define SPM_CFG_SPM_EMI_GENA                                                                   (volatile uint32_t*)( SPM_CFG_BASE + 0x01F0 )
#define SPM_CFG_SPM_EMI_DSRAM                                                                  (volatile uint32_t*)( SPM_CFG_BASE + 0x01F4 )
#define SPM_CFG_SPM_EMI_ARB_A0_MAX_GNT_CNT                                                     (volatile uint32_t*)( SPM_CFG_BASE + 0x01F8 )
#define SPM_CFG_SPM_EMI_ARB_B0_MAX_GNT_CNT                                                     (volatile uint32_t*)( SPM_CFG_BASE + 0x01FC )
#define SPM_CFG_SPM_EMI_ARB_C0_MAX_GNT_CNT                                                     (volatile uint32_t*)( SPM_CFG_BASE + 0x0200 )
#define SPM_CFG_SFC_ID_0                                                                       (volatile uint32_t*)( SPM_CFG_BASE + 0x0204 )
#define SPM_CFG_SFC_ID_1                                                                       (volatile uint32_t*)( SPM_CFG_BASE + 0x0208 )
#define SPM_CFG_SFC_EMI_READY                                                                  (volatile uint32_t*)( SPM_CFG_BASE + 0x020C )
#define SPM_CFG_SKIP_SFC_EMI_TASK                                                              (volatile uint32_t*)( SPM_CFG_BASE + 0x0210 )
#define SPM_CFG_SFC_EMI_WAIT_TIME_IN_SLEEP                                                     (volatile uint32_t*)( SPM_CFG_BASE + 0x0214 )
#define SPM_CFG_SFC_EMI_WAIT_TIME_IN_WAKEUP                                                    (volatile uint32_t*)( SPM_CFG_BASE + 0x0218 )
#define SPM_CFG_SCENARIO_SELECT                                                                (volatile uint32_t*)( SPM_CFG_BASE + 0x021C )
#define SPM_CFG_SPM_AO_IDLE                                                                    (volatile uint32_t*)( SPM_CFG_BASE + 0x0220 )
#define SPM_CFG_SPM_PD_IDLE                                                                    (volatile uint32_t*)( SPM_CFG_BASE + 0x0224 )

#endif /* __SPMCFG_REG_DEFINITION_H__ */