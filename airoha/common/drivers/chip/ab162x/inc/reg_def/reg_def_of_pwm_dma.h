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

#ifndef __PWM_DMA_REG_DEFINITION_H__
#define __PWM_DMA_REG_DEFINITION_H__


/* PWM DMA Interrupt Status */
typedef union {
    struct {
        __IO uint32_t MR0                             :1;    /* bits:0-0, Interrupt flag for match channel 0 */
        __IO uint32_t MR1                             :1;    /* bits:1-1, Interrupt flag for match channel 1 */
        __IO uint32_t MR2                             :1;    /* bits:2-2, Interrupt flag for match channel 2 */
        __IO uint32_t MR3                             :1;    /* bits:3-3, Interrupt flag for match channel 3 */
        __IO uint32_t MR0_2                           :1;    /* bits:4-4, Interrupt flag for 2nd match channel 0 */
        __IO uint32_t MR1_2                           :1;    /* bits:5-5, Interrupt flag for 2nd match channel 1 */
        __IO uint32_t MR2_2                           :1;    /* bits:6-6, Interrupt flag for 2nd match channel 2 */
        __IO uint32_t MR3_2                           :1;    /* bits:7-7, Interrupt flag for 2nd match channel 3 */
        __IO uint32_t DMA_DONE                        :1;    /* bits:8-8, Interrupt flag of DMA done event. Each time the DMA is done without any buffer is queue, this bit is set. */
        __IO uint32_t DMA_BUFA_DONE                   :1;    /* bits:9-9, Interrupt flag of DMA bufferA done event. Each time the DMA bufferA is done, this bit is set. */
        __IO uint32_t DMA_BUFB_DONE                   :1;    /* bits:10-10, Interrupt flag of DMA bufferB done event. Each time the DMA bufferB is done, this bit is set. */
        __IO uint32_t DMA_BUFA_OV                     :1;    /* bits:11-11, Interrupt flag of DMA bufferA overflow event. Each time     (1)the dma_bufa_queue is 1 and      (2)dma_next_buf is 0 and      (3)SW set the dma_start_p,      this bit is set. */
        __IO uint32_t DMA_BUFB_OV                     :1;    /* bits:12-12, Interrupt flag of DMA bufferB overflow event. Each time     (1)the dma_bufa_queue is 1 and      (2)dma_next_buf is 0 and      (3)SW set the dma_start_p,      this bit is set. */
        __I  uint32_t __reserved_00                   :19;
    } field;
    __IO uint32_t word;
} INTR_STS_T;

#define INTR_STS_MR0_OFFSET                                              (0U)
#define INTR_STS_MR0_MASK                                                (0x1U << INTR_STS_MR0_OFFSET)
#define INTR_STS_MR1_OFFSET                                              (1U)
#define INTR_STS_MR1_MASK                                                (0x1U << INTR_STS_MR1_OFFSET)
#define INTR_STS_MR2_OFFSET                                              (2U)
#define INTR_STS_MR2_MASK                                                (0x1U << INTR_STS_MR2_OFFSET)
#define INTR_STS_MR3_OFFSET                                              (3U)
#define INTR_STS_MR3_MASK                                                (0x1U << INTR_STS_MR3_OFFSET)
#define INTR_STS_MR0_2_OFFSET                                            (4U)
#define INTR_STS_MR0_2_MASK                                              (0x1U << INTR_STS_MR0_2_OFFSET)
#define INTR_STS_MR1_2_OFFSET                                            (5U)
#define INTR_STS_MR1_2_MASK                                              (0x1U << INTR_STS_MR1_2_OFFSET)
#define INTR_STS_MR2_2_OFFSET                                            (6U)
#define INTR_STS_MR2_2_MASK                                              (0x1U << INTR_STS_MR2_2_OFFSET)
#define INTR_STS_MR3_2_OFFSET                                            (7U)
#define INTR_STS_MR3_2_MASK                                              (0x1U << INTR_STS_MR3_2_OFFSET)
#define INTR_STS_DMA_DONE_OFFSET                                         (8U)
#define INTR_STS_DMA_DONE_MASK                                           (0x1U << INTR_STS_DMA_DONE_OFFSET)
#define INTR_STS_DMA_BUFA_DONE_OFFSET                                    (9U)
#define INTR_STS_DMA_BUFA_DONE_MASK                                      (0x1U << INTR_STS_DMA_BUFA_DONE_OFFSET)
#define INTR_STS_DMA_BUFB_DONE_OFFSET                                    (10U)
#define INTR_STS_DMA_BUFB_DONE_MASK                                      (0x1U << INTR_STS_DMA_BUFB_DONE_OFFSET)
#define INTR_STS_DMA_BUFA_OV_OFFSET                                      (11U)
#define INTR_STS_DMA_BUFA_OV_MASK                                        (0x1U << INTR_STS_DMA_BUFA_OV_OFFSET)
#define INTR_STS_DMA_BUFB_OV_OFFSET                                      (12U)
#define INTR_STS_DMA_BUFB_OV_MASK                                        (0x1U << INTR_STS_DMA_BUFB_OV_OFFSET)


/* Timer Control Register (TCR) */
typedef union {
    struct {
        __IO uint32_t CEN                             :1;    /* bits:0-0, Enable Timer Counter and Prescale Counter (This RG will be clear when MR Stop occurs) 0: Disable 1: Enable */
        __IO uint32_t CRST                            :1;    /* bits:1-1, Reset  Timer Counter and Prescale Counter 0: Release 1: Reset */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} TIME_CTRL_REG_T;

#define TIME_CTRL_REG_CEN_OFFSET                                         (0U)
#define TIME_CTRL_REG_CEN_MASK                                           (0x1U << TIME_CTRL_REG_CEN_OFFSET)
#define TIME_CTRL_REG_CRST_OFFSET                                        (1U)
#define TIME_CTRL_REG_CRST_MASK                                          (0x1U << TIME_CTRL_REG_CRST_OFFSET)


/* Timer Counter (TC) */
typedef union {
    struct {
        __I  uint32_t TC                              :16;    /* bits:0-15, Timer Counter. The 16-bit TC is incremented every PR+1 cycles of PCLK. The TC is controlled through the TCR. */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} TIME_CNT_T;

#define TIME_CNT_TC_OFFSET                                               (0U)
#define TIME_CNT_TC_MASK                                                 (0xFFFFU << TIME_CNT_TC_OFFSET)


/* PreScale Set Register (PCR) */
typedef union {
    struct {
        __IO uint32_t PR                              :16;    /* bits:0-15, Prescale Set Register. When the Prescale Counter (below) is equal to this value, the next clock increments the TC and clears the PC. */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} PSCALE_REG_T;

#define PSCALE_REG_PR_OFFSET                                             (0U)
#define PSCALE_REG_PR_MASK                                               (0xFFFFU << PSCALE_REG_PR_OFFSET)


/* PreScale Counter (PC) */
typedef union {
    struct {
        __I  uint32_t PC                              :16;    /* bits:0-15, Prescale Counter. The 16-bit PC is a counter which is incremented to the value stored in PR. When the value in PR is reached, the TC is incremented and the PC is cleared. */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} PSCALE_CNT_T;

#define PSCALE_CNT_PC_OFFSET                                             (0U)
#define PSCALE_CNT_PC_MASK                                               (0xFFFFU << PSCALE_CNT_PC_OFFSET)


/* Match Control Register (MCR) */
typedef union {
    struct {
        __IO uint32_t MR0I                            :1;    /* bits:0-0, Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC. */
        __IO uint32_t MR0R                            :1;    /* bits:1-1, Reset on MR0: the TC will be reset if MR0 matches it. */
        __IO uint32_t MR0S                            :1;    /* bits:2-2, Stop on MR0: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC. */
        __IO uint32_t MR1I                            :1;    /* bits:3-3, Interrupt on MR1: an interrupt is generated when MR1 matches the value in the TC. */
        __IO uint32_t MR1R                            :1;    /* bits:4-4, Reset on MR1: the TC will be reset if MR1 matches it. */
        __IO uint32_t MR1S                            :1;    /* bits:5-5, Stop on MR1: the TC and PC will be stopped and TCR[0] will be set to 0 if MR1 matches the TC. */
        __IO uint32_t MR2I                            :1;    /* bits:6-6, Interrupt on MR2: an interrupt is generated when MR2 matches the value in the TC. */
        __IO uint32_t MR2R                            :1;    /* bits:7-7, Reset on MR2: the TC will be reset if MR2 matches it. */
        __IO uint32_t MR2S                            :1;    /* bits:8-8, Stop on MR2: the TC and PC will be stopped and TCR[0] will be set to 0 if MR2 matches the TC. */
        __IO uint32_t MR3I                            :1;    /* bits:9-9, Interrupt on MR3: an interrupt is generated when MR3 matches the value in the TC. */
        __IO uint32_t MR3R                            :1;    /* bits:10-10, Reset on MR3: the TC will be reset if MR3 matches it. */
        __IO uint32_t MR3S                            :1;    /* bits:11-11, Stop on MR3: the TC and PC will be stopped and TCR[0] will be set to 0 if MR3 matches the TC. */
        __I  uint32_t __reserved_00                   :4;
        __IO uint32_t MR0I_2                          :1;    /* bits:16-16, Interrupt on MR0_2: an interrupt is generated when MR0_2 matches the value in the TC. */
        __IO uint32_t MR0R_2                          :1;    /* bits:17-17, Reset on MR0_2: the TC will be reset if MR0_2 matches it. */
        __IO uint32_t MR0S_2                          :1;    /* bits:18-18, Stop on MR0_2: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0_2 matches the TC. */
        __IO uint32_t MR1I_2                          :1;    /* bits:19-19, Interrupt on MR1_2: an interrupt is generated when MR1_2 matches the value in the TC. */
        __IO uint32_t MR1R_2                          :1;    /* bits:20-20, Reset on MR1_2: the TC will be reset if MR1_2 matches it. */
        __IO uint32_t MR1S_2                          :1;    /* bits:21-21, Stop on MR1_2: the TC and PC will be stopped and TCR[0] will be set to 0 if MR1_2 matches the TC. */
        __IO uint32_t MR2I_2                          :1;    /* bits:22-22, Interrupt on MR2_2: an interrupt is generated when MR2_2 matches the value in the TC. */
        __IO uint32_t MR2R_2                          :1;    /* bits:23-23, Reset on MR2_2: the TC will be reset if MR2_2 matches it. */
        __IO uint32_t MR2S_2                          :1;    /* bits:24-24, Stop on MR2_2: the TC and PC will be stopped and TCR[0] will be set to 0 if MR2_2 matches the TC. */
        __IO uint32_t MR3I_2                          :1;    /* bits:25-25, Interrupt on MR3_2: an interrupt is generated when MR3_2 matches the value in the TC. */
        __IO uint32_t MR3R_2                          :1;    /* bits:26-26, Reset on MR3_2: the TC will be reset if MR3_2 matches it. */
        __IO uint32_t MR3S_2                          :1;    /* bits:27-27, Stop on MR3_2: the TC and PC will be stopped and TCR[0] will be set to 0 if MR3_2 matches the TC. */
        __I  uint32_t __reserved_01                   :4;
    } field;
    __IO uint32_t word;
} MATCH_CTRL_REG_T;

#define MATCH_CTRL_REG_MR0I_OFFSET                                       (0U)
#define MATCH_CTRL_REG_MR0I_MASK                                         (0x1U << MATCH_CTRL_REG_MR0I_OFFSET)
#define MATCH_CTRL_REG_MR0R_OFFSET                                       (1U)
#define MATCH_CTRL_REG_MR0R_MASK                                         (0x1U << MATCH_CTRL_REG_MR0R_OFFSET)
#define MATCH_CTRL_REG_MR0S_OFFSET                                       (2U)
#define MATCH_CTRL_REG_MR0S_MASK                                         (0x1U << MATCH_CTRL_REG_MR0S_OFFSET)
#define MATCH_CTRL_REG_MR1I_OFFSET                                       (3U)
#define MATCH_CTRL_REG_MR1I_MASK                                         (0x1U << MATCH_CTRL_REG_MR1I_OFFSET)
#define MATCH_CTRL_REG_MR1R_OFFSET                                       (4U)
#define MATCH_CTRL_REG_MR1R_MASK                                         (0x1U << MATCH_CTRL_REG_MR1R_OFFSET)
#define MATCH_CTRL_REG_MR1S_OFFSET                                       (5U)
#define MATCH_CTRL_REG_MR1S_MASK                                         (0x1U << MATCH_CTRL_REG_MR1S_OFFSET)
#define MATCH_CTRL_REG_MR2I_OFFSET                                       (6U)
#define MATCH_CTRL_REG_MR2I_MASK                                         (0x1U << MATCH_CTRL_REG_MR2I_OFFSET)
#define MATCH_CTRL_REG_MR2R_OFFSET                                       (7U)
#define MATCH_CTRL_REG_MR2R_MASK                                         (0x1U << MATCH_CTRL_REG_MR2R_OFFSET)
#define MATCH_CTRL_REG_MR2S_OFFSET                                       (8U)
#define MATCH_CTRL_REG_MR2S_MASK                                         (0x1U << MATCH_CTRL_REG_MR2S_OFFSET)
#define MATCH_CTRL_REG_MR3I_OFFSET                                       (9U)
#define MATCH_CTRL_REG_MR3I_MASK                                         (0x1U << MATCH_CTRL_REG_MR3I_OFFSET)
#define MATCH_CTRL_REG_MR3R_OFFSET                                       (10U)
#define MATCH_CTRL_REG_MR3R_MASK                                         (0x1U << MATCH_CTRL_REG_MR3R_OFFSET)
#define MATCH_CTRL_REG_MR3S_OFFSET                                       (11U)
#define MATCH_CTRL_REG_MR3S_MASK                                         (0x1U << MATCH_CTRL_REG_MR3S_OFFSET)
#define MATCH_CTRL_REG_MR0I_2_OFFSET                                     (16U)
#define MATCH_CTRL_REG_MR0I_2_MASK                                       (0x1U << MATCH_CTRL_REG_MR0I_2_OFFSET)
#define MATCH_CTRL_REG_MR0R_2_OFFSET                                     (17U)
#define MATCH_CTRL_REG_MR0R_2_MASK                                       (0x1U << MATCH_CTRL_REG_MR0R_2_OFFSET)
#define MATCH_CTRL_REG_MR0S_2_OFFSET                                     (18U)
#define MATCH_CTRL_REG_MR0S_2_MASK                                       (0x1U << MATCH_CTRL_REG_MR0S_2_OFFSET)
#define MATCH_CTRL_REG_MR1I_2_OFFSET                                     (19U)
#define MATCH_CTRL_REG_MR1I_2_MASK                                       (0x1U << MATCH_CTRL_REG_MR1I_2_OFFSET)
#define MATCH_CTRL_REG_MR1R_2_OFFSET                                     (20U)
#define MATCH_CTRL_REG_MR1R_2_MASK                                       (0x1U << MATCH_CTRL_REG_MR1R_2_OFFSET)
#define MATCH_CTRL_REG_MR1S_2_OFFSET                                     (21U)
#define MATCH_CTRL_REG_MR1S_2_MASK                                       (0x1U << MATCH_CTRL_REG_MR1S_2_OFFSET)
#define MATCH_CTRL_REG_MR2I_2_OFFSET                                     (22U)
#define MATCH_CTRL_REG_MR2I_2_MASK                                       (0x1U << MATCH_CTRL_REG_MR2I_2_OFFSET)
#define MATCH_CTRL_REG_MR2R_2_OFFSET                                     (23U)
#define MATCH_CTRL_REG_MR2R_2_MASK                                       (0x1U << MATCH_CTRL_REG_MR2R_2_OFFSET)
#define MATCH_CTRL_REG_MR2S_2_OFFSET                                     (24U)
#define MATCH_CTRL_REG_MR2S_2_MASK                                       (0x1U << MATCH_CTRL_REG_MR2S_2_OFFSET)
#define MATCH_CTRL_REG_MR3I_2_OFFSET                                     (25U)
#define MATCH_CTRL_REG_MR3I_2_MASK                                       (0x1U << MATCH_CTRL_REG_MR3I_2_OFFSET)
#define MATCH_CTRL_REG_MR3R_2_OFFSET                                     (26U)
#define MATCH_CTRL_REG_MR3R_2_MASK                                       (0x1U << MATCH_CTRL_REG_MR3R_2_OFFSET)
#define MATCH_CTRL_REG_MR3S_2_OFFSET                                     (27U)
#define MATCH_CTRL_REG_MR3S_2_MASK                                       (0x1U << MATCH_CTRL_REG_MR3S_2_OFFSET)


/* Match Register (MR0,MR1,MR2.MR3) */
typedef union {
    struct {
        __IO uint32_t MR                              :16;    /* bits:0-15, Match Register  MR0/MR1/MR2/MR3 can be enabled through the MCR to reset the TC, stop both the TC and PC, and/or generate an interrupt every time MR0 matches the TC. */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} MATCH_REG_T;

#define MATCH_REG_OFFSET                                            (0U)
#define MATCH_REG_MASK                                              (0xFFFFU << MATCH_REG_OFFSET)


/* WAKEUP MASK Register*/
typedef union {
    struct {
        __IO  uint32_t MR0_WAKEUP                     :1;
        __IO  uint32_t MR1_WAKEUP                     :1;
        __IO  uint32_t MR2_WAKEUP                     :1;
        __IO  uint32_t MR3_WAKEUP                     :1;
        __IO  uint32_t MR0_2_WAKEUP                   :1;
        __IO  uint32_t MR1_2_WAKEUP                   :1;
        __IO  uint32_t MR2_2_WAKEUP                   :1;
        __IO  uint32_t MR3_2_WAKEUP                   :1;
        __IO  uint32_t DMA_DONE_WAKEUP                :1;
        __IO  uint32_t DMA_BUFA_DONE_WAKEUP           :1;
        __IO  uint32_t DMA_BUFB_DONE_WAKEUP           :1;
        __IO  uint32_t DMA_BUFA_OV_WAKEUP             :1;
        __IO  uint32_t DMA_BUFB_OV_WAKEUP             :1;
        __I  uint32_t __reserved_00                   :19;
    } field;
    __IO uint32_t word;
} WAKEUP_MASK_T;

/* External Match Control Register (EMR) */
typedef union {
    struct {
        __I  uint32_t EM0                             :1;    /* bits:0-0, External Match 0. This bit reflects the state of output pwm4, whether or not this output is connected to its pin. When a match occurs between the TC and MR0, this bit acts according to EMC0; when a match occurs between the TC and MR0_2, this bit acts according to EMC0_2. */
        __I  uint32_t EM1                             :1;    /* bits:1-1, External Match 1. This bit reflects the state of output pwm4, whether or not this output is connected to its pin. When a match occurs between the TC and MR1, this bit acts according to EMC1; when a match occurs between the TC and MR1_2, this bit acts according to EMC1_2. */
        __I  uint32_t EM2                             :1;    /* bits:2-2, External Match 2. This bit reflects the state of output pwm4, whether or not this output is connected to its pin. When a match occurs between the TC and MR2, this bit acts according to EMC2; when a match occurs between the TC and MR2_2, this bit acts according to EMC2_2. */
        __I  uint32_t EM3                             :1;    /* bits:3-3, External Match 3. This bit reflects the state of output pwm4, whether or not this output is connected to its pin. When a match occurs between the TC and MR3, this bit acts according to EMC3; when a match occurs between the TC and MR3_2, this bit acts according to EMC3_2. */
        __IO uint32_t EMC0                            :2;    /* bits:4-5, External Match Control 0 0: Do Nothing 1: Set to 0 2: Set to 1 3: Toggle */
        __IO uint32_t EMC1                            :2;    /* bits:6-7, External Match Control 1 0: Do Nothing 1: Set to 0 2: Set to 1 3: Toggle */
        __IO uint32_t EMC2                            :2;    /* bits:8-9, External Match Control 2 0: Do Nothing 1: Set to 0 2: Set to 1 3: Toggle */
        __IO uint32_t EMC3                            :2;    /* bits:10-11, External Match Control 3 0: Do Nothing 1: Set to 0 2: Set to 1 3: Toggle */
        __I  uint32_t __reserved_00                   :4;
        __IO uint32_t EMC0_2                          :2;    /* bits:16-17, 2nd External Match Control 0 0: Do Nothing 1: Set to 0 2: Set to 1 3: Toggle */
        __IO uint32_t EMC1_2                          :2;    /* bits:18-19, 2nd External Match Control 1 0: Do Nothing 1: Set to 0 2: Set to 1 3: Toggle */
        __IO uint32_t EMC2_2                          :2;    /* bits:20-21, 2nd External Match Control 2 0: Do Nothing 1: Set to 0 2: Set to 1 3: Toggle */
        __IO uint32_t EMC3_2                          :2;    /* bits:22-23, 2nd External Match Control 3 0: Do Nothing 1: Set to 0 2: Set to 1 3: Toggle */
        __IO uint32_t EM0_INV                         :1;    /* bits:24-24, External Match Invert Set0 1: invert the output pin corresponding to EM3 (the sfr value is not inverted) 0: no invert */
        __IO uint32_t EM1_INV                         :1;    /* bits:25-25, External Match Invert Set1 1: invert the output pin corresponding to EM3 (the sfr value is not inverted) 0: no invert */
        __IO uint32_t EM2_INV                         :1;    /* bits:26-26, External Match Invert Set2 1: invert the output pin corresponding to EM3 (the sfr value is not inverted) 0: no invert */
        __IO uint32_t EM3_INV                         :1;    /* bits:27-27, External Match Invert Set3 1: invert the output pin corresponding to EM3 (the sfr value is not inverted) 0: no invert */
        __I  uint32_t __reserved_01                   :4;
    } field;
    __IO uint32_t word;
} EXT_MATCH_CTRL_REG_T;

#define EXT_MATCH_CTRL_REG_EM0_OFFSET                                    (0U)
#define EXT_MATCH_CTRL_REG_EM0_MASK                                      (0x1U << EXT_MATCH_CTRL_REG_EM0_OFFSET)
#define EXT_MATCH_CTRL_REG_EM1_OFFSET                                    (1U)
#define EXT_MATCH_CTRL_REG_EM1_MASK                                      (0x1U << EXT_MATCH_CTRL_REG_EM1_OFFSET)
#define EXT_MATCH_CTRL_REG_EM2_OFFSET                                    (2U)
#define EXT_MATCH_CTRL_REG_EM2_MASK                                      (0x1U << EXT_MATCH_CTRL_REG_EM2_OFFSET)
#define EXT_MATCH_CTRL_REG_EM3_OFFSET                                    (3U)
#define EXT_MATCH_CTRL_REG_EM3_MASK                                      (0x1U << EXT_MATCH_CTRL_REG_EM3_OFFSET)
#define EXT_MATCH_CTRL_REG_EMC0_OFFSET                                   (4U)
#define EXT_MATCH_CTRL_REG_EMC0_MASK                                     (0x3U << EXT_MATCH_CTRL_REG_EMC0_OFFSET)
#define EXT_MATCH_CTRL_REG_EMC1_OFFSET                                   (6U)
#define EXT_MATCH_CTRL_REG_EMC1_MASK                                     (0x3U << EXT_MATCH_CTRL_REG_EMC1_OFFSET)
#define EXT_MATCH_CTRL_REG_EMC2_OFFSET                                   (8U)
#define EXT_MATCH_CTRL_REG_EMC2_MASK                                     (0x3U << EXT_MATCH_CTRL_REG_EMC2_OFFSET)
#define EXT_MATCH_CTRL_REG_EMC3_OFFSET                                   (10U)
#define EXT_MATCH_CTRL_REG_EMC3_MASK                                     (0x3U << EXT_MATCH_CTRL_REG_EMC3_OFFSET)
#define EXT_MATCH_CTRL_REG_EMC0_2_OFFSET                                 (16U)
#define EXT_MATCH_CTRL_REG_EMC0_2_MASK                                   (0x3U << EXT_MATCH_CTRL_REG_EMC0_2_OFFSET)
#define EXT_MATCH_CTRL_REG_EMC1_2_OFFSET                                 (18U)
#define EXT_MATCH_CTRL_REG_EMC1_2_MASK                                   (0x3U << EXT_MATCH_CTRL_REG_EMC1_2_OFFSET)
#define EXT_MATCH_CTRL_REG_EMC2_2_OFFSET                                 (20U)
#define EXT_MATCH_CTRL_REG_EMC2_2_MASK                                   (0x3U << EXT_MATCH_CTRL_REG_EMC2_2_OFFSET)
#define EXT_MATCH_CTRL_REG_EMC3_2_OFFSET                                 (22U)
#define EXT_MATCH_CTRL_REG_EMC3_2_MASK                                   (0x3U << EXT_MATCH_CTRL_REG_EMC3_2_OFFSET)
#define EXT_MATCH_CTRL_REG_EM0_INV_OFFSET                                (24U)
#define EXT_MATCH_CTRL_REG_EM0_INV_MASK                                  (0x1U << EXT_MATCH_CTRL_REG_EM0_INV_OFFSET)
#define EXT_MATCH_CTRL_REG_EM1_INV_OFFSET                                (25U)
#define EXT_MATCH_CTRL_REG_EM1_INV_MASK                                  (0x1U << EXT_MATCH_CTRL_REG_EM1_INV_OFFSET)
#define EXT_MATCH_CTRL_REG_EM2_INV_OFFSET                                (26U)
#define EXT_MATCH_CTRL_REG_EM2_INV_MASK                                  (0x1U << EXT_MATCH_CTRL_REG_EM2_INV_OFFSET)
#define EXT_MATCH_CTRL_REG_EM3_INV_OFFSET                                (27U)
#define EXT_MATCH_CTRL_REG_EM3_INV_MASK                                  (0x1U << EXT_MATCH_CTRL_REG_EM3_INV_OFFSET)


/* 2nd Match Register 0 (MR0) */
typedef union {
    struct {
        __IO uint32_t MR_2                           :16;    /* bits:0-15, 2nd Match Register 0 MR0 MR1 MR2 MR3 can be enabled through the MCR to reset the TC, stop both the TC and PC, and/or generate an interrupt every time MR0 matches the TC. Furthermore, when in DMA mode, the value is updated every TC counts. */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} MATCH_REG_2_T;

#define MATCH_REG_2_OFFSET                                        (0U)
#define MATCH_REG_2_MASK                                          (0xFFFFU << MATCH_REG_2_OFFSET)


/* DMA SET Register */
typedef union {
    struct {
        __IO uint32_t DMA_DATA_SCALE                  :4;    /* bits:0-3, Scale of DMA data. The fetched data from DMA is scale down by (2^dma_data_scale) after sign to unsign offset */
        __IO uint32_t DMA_DATA_GAIN                   :4;    /* bits:4-7, Gain of DMA data. The fetched data from DMA is scale up by (2^dma_data_gain) before sign to unsign offset */
        __IO uint32_t DMA_DATA_REPEAT                 :4;    /* bits:8-11, Number of repeat times of each sample. Each sample is used by (1+dma_data_repeats) times. */
        __I  uint32_t __reserved_00                   :4;
        __IO uint32_t DMA_CH_NO                       :2;    /* bits:16-17, Number of Channel for DMA mode 3: DMA move 4 Channel PWM data 2: DMA move 3 Channel PWM data 1: DMA move 2 Channel PWM data 0: DMA move 1 Channel PWM data */
        __IO uint32_t DMA_BUF_NONALIGN                :1;    /* bits:18-18, DMA mode for non-align Data Source 1: Non-align Data Souce (DMA cotrol will wrap the data automatically) 0: Align Data Source (The data must be aligned in data source) */
        __IO uint32_t DMA_BUF_8B                      :1;    /* bits:19-19, 8bit Data for DMA mode 1: 8 bit Data 0: 16 bit Data */
        __IO uint32_t DMA_BUF_REPEAT_EN               :1;    /* bits:20-20, Enable of buffer repeat. the proceeding buffer is repeated until dma_buf_repeat_en is 0 or dma_abort_p is set. SW can change the value at any time. Note that according to the state of PWM, it may run one more time of the buffer after SW set dma_buf_repeat_en to 0. 1: Enable buffer repeat  0: Disable buffer repeat */
        __I  uint32_t __reserved_01                   :3;
        __IO uint32_t DMA_MODE                        :1;    /* bits:24-24, DMA mode. The overall enable of DMA mode. 1 : DMA mode 0 : legacy mode */
        __I  uint32_t __reserved_02                   :3;
        __IO uint32_t DMA_DATA_SIGN                   :1;    /* bits:28-28, Data Sign Extension Control Enable 1: Enable Data Sign Extension with Gain and Scale control 0: No pre-processing for Data */
        __I  uint32_t __reserved_03                   :3;
    } field;
    __IO uint32_t word;
} DMA_SET_T;

#define DMA_SET_DMA_DATA_SCALE_OFFSET                                    (0U)
#define DMA_SET_DMA_DATA_SCALE_MASK                                      (0xFU << DMA_SET_DMA_DATA_SCALE_OFFSET)
#define DMA_SET_DMA_DATA_GAIN_OFFSET                                     (4U)
#define DMA_SET_DMA_DATA_GAIN_MASK                                       (0xFU << DMA_SET_DMA_DATA_GAIN_OFFSET)
#define DMA_SET_DMA_DATA_REPEAT_OFFSET                                   (8U)
#define DMA_SET_DMA_DATA_REPEAT_MASK                                     (0xFU << DMA_SET_DMA_DATA_REPEAT_OFFSET)
#define DMA_SET_DMA_CH_NO_OFFSET                                         (16U)
#define DMA_SET_DMA_CH_NO_MASK                                           (0x3U << DMA_SET_DMA_CH_NO_OFFSET)
#define DMA_SET_DMA_BUF_NONALIGN_OFFSET                                  (18U)
#define DMA_SET_DMA_BUF_NONALIGN_MASK                                    (0x1U << DMA_SET_DMA_BUF_NONALIGN_OFFSET)
#define DMA_SET_DMA_BUF_8B_OFFSET                                        (19U)
#define DMA_SET_DMA_BUF_8B_MASK                                          (0x1U << DMA_SET_DMA_BUF_8B_OFFSET)
#define DMA_SET_DMA_BUF_REPEAT_EN_OFFSET                                 (20U)
#define DMA_SET_DMA_BUF_REPEAT_EN_MASK                                   (0x1U << DMA_SET_DMA_BUF_REPEAT_EN_OFFSET)
#define DMA_SET_DMA_MODE_OFFSET                                          (24U)
#define DMA_SET_DMA_MODE_MASK                                            (0x1U << DMA_SET_DMA_MODE_OFFSET)
#define DMA_SET_DMA_DATA_SIGN_OFFSET                                     (28U)
#define DMA_SET_DMA_DATA_SIGN_MASK                                       (0x1U << DMA_SET_DMA_DATA_SIGN_OFFSET)


/* PWM DMA Interrupt Enable */
typedef union {
    struct {
        __IO uint32_t DMA_DONE_INT_EN                 :1;    /* bits:0-0, Interrupt enable of DMA done event. If enabled, the DMA_DONE (INTR_STS[8]) would asserts interrupt to mcu when 1'b1. 1: Enable 0: Disable */
        __IO uint32_t DMA_BUFA_DONE_INT_EN            :1;    /* bits:1-1, Interrupt enable of DMA bufferA done event. If enabled, the DMA_BUFA_DONE (INTR_STS[9]) would asserts interrupt to mcu when 1'b1. 1: Enable 0: Disable */
        __IO uint32_t DMA_BUFB_DONE_INT_EN            :1;    /* bits:2-2, Interrupt enable of DMA bufferB done event. If enabled, the DMA_BUFB_DONE (INTR_STS[10]) would asserts interrupt to mcu when 1'b1. 1: Enable 0: Disable */
        __IO uint32_t DMA_BUFA_OV_INT_EN              :1;    /* bits:3-3, Interrupt enable of DMA bufferA overflow event. If enabled, the DMA_BUFB_OV (INTR_STS[11]) would asserts interrupt to mcu when 1'b1. 1: Enable 0: Disable */
        __IO uint32_t DMA_BUFB_OV_INT_EN              :1;    /* bits:4-4, Interrupt enable of DMA bufferB overflow event. If enabled, the DMA_BUFB_OV (INTR_STS[12]) would asserts interrupt to mcu when 1'b1. 1: Enable 0: Disable */
        __I  uint32_t __reserved_00                   :27;
    } field;
    __IO uint32_t word;
} INTR_EN_T;

#define INTR_EN_DMA_DONE_INT_EN_OFFSET                                   (0U)
#define INTR_EN_DMA_DONE_INT_EN_MASK                                     (0x1U << INTR_EN_DMA_DONE_INT_EN_OFFSET)
#define INTR_EN_DMA_BUFA_DONE_INT_EN_OFFSET                              (1U)
#define INTR_EN_DMA_BUFA_DONE_INT_EN_MASK                                (0x1U << INTR_EN_DMA_BUFA_DONE_INT_EN_OFFSET)
#define INTR_EN_DMA_BUFB_DONE_INT_EN_OFFSET                              (2U)
#define INTR_EN_DMA_BUFB_DONE_INT_EN_MASK                                (0x1U << INTR_EN_DMA_BUFB_DONE_INT_EN_OFFSET)
#define INTR_EN_DMA_BUFA_OV_INT_EN_OFFSET                                (3U)
#define INTR_EN_DMA_BUFA_OV_INT_EN_MASK                                  (0x1U << INTR_EN_DMA_BUFA_OV_INT_EN_OFFSET)
#define INTR_EN_DMA_BUFB_OV_INT_EN_OFFSET                                (4U)
#define INTR_EN_DMA_BUFB_OV_INT_EN_MASK                                  (0x1U << INTR_EN_DMA_BUFB_OV_INT_EN_OFFSET)


/* PWM DMA Base Address for Buffer A */
typedef union {
    struct {
        __IO uint32_t DMA_BADDR_A                     :32;    /* bits:0-31, The base address of DMA data buffer A. Should be 4-byte align. If DMA_NEXT_BUF is 0, set DMA_BADDR_A before DMA_START_P. When  DMA_BUFA_QUEUE is 1, don't change the value. */
    } field;
    __IO uint32_t word;
} DMA_BASE_ADDR_A_T;

#define DMA_BASE_ADDR_A_DMA_BADDR_A_OFFSET                               (0U)
#define DMA_BASE_ADDR_A_DMA_BADDR_A_MASK                                 (0xFFFFFFFFU << DMA_BASE_ADDR_A_DMA_BADDR_A_OFFSET)


/* PWM DMA  Buffer Length for Buffer A */
typedef union {
    struct {
        __IO uint32_t DMA_LEN_A                       :14;    /* bits:0-13, The length of DMA data buffer A. The unit is samples.  The value should not be 0. If DMA_NEXT_BUF is 0, set DMA_LEN_A before DMA_START_P. When DMA_BUFA_QUEUE is 1, don't change the value. */
        __I  uint32_t __reserved_00                   :18;
    } field;
    __IO uint32_t word;
} DMA_LENGTH_A_T;

#define DMA_LENGTH_A_DMA_LEN_A_OFFSET                                    (0U)
#define DMA_LENGTH_A_DMA_LEN_A_MASK                                      (0x3FFFU << DMA_LENGTH_A_DMA_LEN_A_OFFSET)


/* PWM DMA Base Address for Buffer B */
typedef union {
    struct {
        __IO uint32_t DMA_BADDR_B                     :32;    /* bits:0-31, The base address of DMA data buffer B. Should be 4-byte align. If DMA_NEXT_BUF is 0, set DMA_BADDR_B before DMA_START_P. When  DMA_BUFB_QUEUE is 1, don't change the value. */
    } field;
    __IO uint32_t word;
} DMA_BASE_ADDR_B_T;

#define DMA_BASE_ADDR_B_DMA_BADDR_B_OFFSET                               (0U)
#define DMA_BASE_ADDR_B_DMA_BADDR_B_MASK                                 (0xFFFFFFFFU << DMA_BASE_ADDR_B_DMA_BADDR_B_OFFSET)


/* PWM DMA  Buffer Length for Buffer B */
typedef union {
    struct {
        __IO uint32_t DMA_LEN_B                       :14;    /* bits:0-13, The length of DMA data buffer B. The unit is samples.  The value should not be 0. If DMA_NEXT_BUF is 0, set DMA_LEN_B before DMA_START_P. When DMA_BUFB_QUEUE is 1, don't change the value. */
        __I  uint32_t __reserved_00                   :18;
    } field;
    __IO uint32_t word;
} DMA_LENGTH_B_T;

#define DMA_LENGTH_B_DMA_LEN_B_OFFSET                                    (0U)
#define DMA_LENGTH_B_DMA_LEN_B_MASK                                      (0x3FFFU << DMA_LENGTH_B_DMA_LEN_B_OFFSET)


/* PWM DMA Control Register */
typedef union {
    struct {
        __IO uint32_t DMA_START_P                     :1;    /* bits:0-0, Start of DMA process. After all settings are ready, set this bit to start DMA process. */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t DMA_ABORT_P                     :1;    /* bits:8-8, Force stop of DMA process. Used to abort the DMA process when DMA is busy. */
        __I  uint32_t __reserved_01                   :23;
    } field;
    __IO uint32_t word;
} DMA_CTRL_T;

#define DMA_CTRL_DMA_START_P_OFFSET                                      (0U)
#define DMA_CTRL_DMA_START_P_MASK                                        (0x1U << DMA_CTRL_DMA_START_P_OFFSET)
#define DMA_CTRL_DMA_ABORT_P_OFFSET                                      (8U)
#define DMA_CTRL_DMA_ABORT_P_MASK                                        (0x1U << DMA_CTRL_DMA_ABORT_P_OFFSET)


/* PWM DMA Clock Control Register */
typedef union {
    struct {
        __IO uint32_t PWM_CLK_FREE_EN                 :1;    /* bits:0-0, clk free-run of PWM 0 : the clk of PWM is auto 1 : the clk of PWM is free-run */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} CLK_CTRL_T;

#define CLK_CTRL_PWM_CLK_FREE_EN_OFFSET                                  (0U)
#define CLK_CTRL_PWM_CLK_FREE_EN_MASK                                    (0x1U << CLK_CTRL_PWM_CLK_FREE_EN_OFFSET)


/* PWM DMA Status */
typedef union {
    struct {
        __I  uint32_t DMA_BUSY                        :1;    /* bits:0-0, The busy indicator of DMA process. After DMA_START_P is set, DMA_BUSY is 1. After the DMA process is done (return to idle), DMA_BUSY is 0. If DMA_BUSY is 1 and DMA_ABORT_P is set, SW need wait dma_busy to 0. */
        __I  uint32_t DMA_BUFA_QUEUE                  :1;    /* bits:1-1, The busy indicator of bufferA. 0: bufferA is idle. SW can set dma_start_p if dma_next_buf is 0 to trigger bufferA. 1: bufferA is queue. SW cannot set dma_start_p if dma_next_buf is 0. */
        __I  uint32_t DMA_BUFB_QUEUE                  :1;    /* bits:2-2, The busy indicator of bufferB. 0: bufferB is idle. SW can set dma_start_p if dma_next_buf is 1 to trigger bufferB. 1: bufferB is queue. SW cannot set dma_start_p if dma_next_buf is 1. */
        __I  uint32_t DMA_NEXT_BUF                    :1;    /* bits:3-3, The pointer indicator of bufferA and bufferB. 0: The next dma_start_p will trigger bufferA. 1: The next dma_start_p will trigger bufferB. */
        __I  uint32_t __reserved_00                   :28;
    } field;
    __IO uint32_t word;
} DMA_STS_T;

#define DMA_STS_DMA_BUSY_OFFSET                                          (0U)
#define DMA_STS_DMA_BUSY_MASK                                            (0x1U << DMA_STS_DMA_BUSY_OFFSET)
#define DMA_STS_DMA_BUFA_QUEUE_OFFSET                                    (1U)
#define DMA_STS_DMA_BUFA_QUEUE_MASK                                      (0x1U << DMA_STS_DMA_BUFA_QUEUE_OFFSET)
#define DMA_STS_DMA_BUFB_QUEUE_OFFSET                                    (2U)
#define DMA_STS_DMA_BUFB_QUEUE_MASK                                      (0x1U << DMA_STS_DMA_BUFB_QUEUE_OFFSET)
#define DMA_STS_DMA_NEXT_BUF_OFFSET                                      (3U)
#define DMA_STS_DMA_NEXT_BUF_MASK                                        (0x1U << DMA_STS_DMA_NEXT_BUF_OFFSET)

/* PWM DMA Status */
typedef union {
    struct {
        __I  uint32_t DMA_BUF_CNT_PRELOAD             :14;
        __I  uint32_t __reserved_00                   :1;   
        __I  uint32_t DMA_BUF_PRELOAD                 :1;   
        __I  uint32_t DMA_BUF_CNT_CURRENT             :14;
        __I  uint32_t __reserved_01                   :1;    
        __I  uint32_t DMA_BUF_CURRENT                 :1;    
    } field;
    __IO uint32_t word;
} DMA_CNT_STS_T;

typedef struct {
    INTR_STS_T                                               intr_sts; /* offset: 0x00000000, PWM DMA Interrupt Status */
    TIME_CTRL_REG_T                                     time_ctrl_reg; /* offset: 0x00000004, Timer Control Register (TCR) */
    TIME_CNT_T                                               time_cnt; /* offset: 0x00000008, Timer Counter (TC) */
    PSCALE_REG_T                                           pscale_reg; /* offset: 0x0000000C, PreScale Set Register (PCR) */
    PSCALE_CNT_T                                           pscale_cnt; /* offset: 0x00000010, PreScale Counter (PC) */
    MATCH_CTRL_REG_T                                   match_ctrl_reg; /* offset: 0x00000014, Match Control Register (MCR) */
    MATCH_REG_T                                           match_reg[4]; /* offset: 0x00000018, Match Register 0,1,2,3 (MR0,MR1,MR2,MR3) */
    uint32_t                                         __reserved_00[2]; /* offset: 0x00000028, padding size: 0x00000014 */
    WAKEUP_MASK_T                                      wake_up_mask;  /* offset: 0x00000030, padding size: 0x00000014 */
    uint32_t                                         __reserved_01[2]; /* offset: 0x00000034, padding size: 0x00000014 */
    EXT_MATCH_CTRL_REG_T                           ext_match_ctrl_reg; /* offset: 0x0000003C, External Match Control Register (EMR) */
    MATCH_REG_2_T                                       match_reg_2[4]; /* offset: 0x00000040, 2nd Match Register 0,1,2,3 (MR0_2,MR1_2,MR2_2,MR3_2) */
    DMA_SET_T                                                 dma_set; /* offset: 0x00000050, DMA SET Register */
    INTR_EN_T                                                 intr_en; /* offset: 0x00000054, PWM DMA Interrupt Enable */
    DMA_BASE_ADDR_A_T                                 dma_base_addr_a; /* offset: 0x00000058, PWM DMA Base Address for Buffer A */
    DMA_LENGTH_A_T                                       dma_length_a; /* offset: 0x0000005C, PWM DMA  Buffer Length for Buffer A */
    DMA_BASE_ADDR_B_T                                 dma_base_addr_b; /* offset: 0x00000060, PWM DMA Base Address for Buffer B */
    DMA_LENGTH_B_T                                       dma_length_b; /* offset: 0x00000064, PWM DMA  Buffer Length for Buffer B */
    DMA_CTRL_T                                               dma_ctrl; /* offset: 0x00000068, PWM DMA Control Register */
    CLK_CTRL_T                                               clk_ctrl; /* offset: 0x0000006C, PWM DMA Clock Control Register */
    DMA_STS_T                                                 dma_sts; /* offset: 0x00000070, PWM DMA Status */
    DMA_CNT_STS_T                                             dma_cnt_sts; /* offset: 0x00000074, PWM DMA buffer Status */
} PWM_DMA_REGISTER_T;


#endif /*__PWM_DMA_0_REG_DEFINITION_H__*/
