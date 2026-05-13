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

#ifndef __LED_CTRL_REG_DEFINITION_H__
#define __LED_CTRL_REG_DEFINITION_H__


#include <stdint.h>


/********************************************************* LED enable control **********************************************************/

typedef union {
    struct {
        __IO uint32_t LED0_EN                         :1;    /* bits:0-0, Enable LED0.   0: Disable 1: Enable */
        __IO uint32_t LED1_EN                         :1;    /* bits:1-1, Enable LED1.  0: Disable 1: Enable */
        __IO uint32_t LED2_EN                         :1;    /* bits:2-2, Enable LED2.   0: Disable 1: Enable */
        __IO uint32_t LED3_EN                         :1;    /* bits:3-3, Enable LED3.   0: Disable 1: Enable */
        __I  uint32_t __reserved_00                   :4;
        __IO uint32_t LED0_DIS_WHEN_IDLE              :1;    /* bits:8-8, Force to disable LED0 when LED Controller FSM is in IDLE state */
        __IO uint32_t LED1_DIS_WHEN_IDLE              :1;    /* bits:9-9, Force to disable LED1 when LED Controller FSM is in IDLE state */
        __IO uint32_t LED2_DIS_WHEN_IDLE              :1;    /* bits:10-10, Force to disable LED2 when LED Controller FSM is in IDLE state */
        __I  uint32_t __reserved_01                   :13;
        __I  uint32_t LED0_EN_SYS_SW                  :1;    /* bits:24-24, Indicate LED0 is running */
        __I  uint32_t LED1_EN_SYS_SW                  :1;    /* bits:25-25, Indicate LED1 is running */
        __I  uint32_t LED2_EN_SYS_SW                  :1;    /* bits:26-26, Indicate LED2 is running */
        __I  uint32_t LED3_EN_SYS_SW                  :1;    /* bits:27-27, Indicate LED3 is running */
        __I  uint32_t __reserved_02                   :4;
    } field;
    __IO uint32_t word;
} LED_EN_CTRL_T;

#define LED_EN_CTRL_LED0_EN_OFFSET                                       (0U)
#define LED_EN_CTRL_LED0_EN_MASK                                         (0x1U << LED_EN_CTRL_LED0_EN_OFFSET)
#define LED_EN_CTRL_LED1_EN_OFFSET                                       (1U)
#define LED_EN_CTRL_LED1_EN_MASK                                         (0x1U << LED_EN_CTRL_LED1_EN_OFFSET)
#define LED_EN_CTRL_LED2_EN_OFFSET                                       (2U)
#define LED_EN_CTRL_LED2_EN_MASK                                         (0x1U << LED_EN_CTRL_LED2_EN_OFFSET)
#define LED_EN_CTRL_LED3_EN_OFFSET                                       (3U)
#define LED_EN_CTRL_LED3_EN_MASK                                         (0x1U << LED_EN_CTRL_LED3_EN_OFFSET)
#define LED_EN_CTRL_LED0_DIS_WHEN_IDLE_OFFSET                            (8U)
#define LED_EN_CTRL_LED0_DIS_WHEN_IDLE_MASK                              (0x1U << LED_EN_CTRL_LED0_DIS_WHEN_IDLE_OFFSET)
#define LED_EN_CTRL_LED1_DIS_WHEN_IDLE_OFFSET                            (9U)
#define LED_EN_CTRL_LED1_DIS_WHEN_IDLE_MASK                              (0x1U << LED_EN_CTRL_LED1_DIS_WHEN_IDLE_OFFSET)
#define LED_EN_CTRL_LED2_DIS_WHEN_IDLE_OFFSET                            (10U)
#define LED_EN_CTRL_LED2_DIS_WHEN_IDLE_MASK                              (0x1U << LED_EN_CTRL_LED2_DIS_WHEN_IDLE_OFFSET)
#define LED_EN_CTRL_LED0_EN_SYS_SW_OFFSET                                (24U)
#define LED_EN_CTRL_LED0_EN_SYS_SW_MASK                                  (0x1U << LED_EN_CTRL_LED0_EN_SYS_SW_OFFSET)
#define LED_EN_CTRL_LED1_EN_SYS_SW_OFFSET                                (25U)
#define LED_EN_CTRL_LED1_EN_SYS_SW_MASK                                  (0x1U << LED_EN_CTRL_LED1_EN_SYS_SW_OFFSET)
#define LED_EN_CTRL_LED2_EN_SYS_SW_OFFSET                                (26U)
#define LED_EN_CTRL_LED2_EN_SYS_SW_MASK                                  (0x1U << LED_EN_CTRL_LED2_EN_SYS_SW_OFFSET)
#define LED_EN_CTRL_LED3_EN_SYS_SW_OFFSET                                (27U)
#define LED_EN_CTRL_LED3_EN_SYS_SW_MASK                                  (0x1U << LED_EN_CTRL_LED3_EN_SYS_SW_OFFSET)


/* LED Golbal control register */
typedef union {
    struct {
        __IO uint32_t LED_LP_EN                       :1;    /* bits:0-0, Enable LED Self Clock Gating for Low Power 0: Disable 1: Enable */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} LED_GBL_CTRL_T;

#define LED_GBL_CTRL_LED_LP_EN_OFFSET                                    (0U)
#define LED_GBL_CTRL_LED_LP_EN_MASK                                      (0x1U << LED_GBL_CTRL_LED_LP_EN_OFFSET)


/* LED control register 0 */
typedef union {
    struct {
        __IO uint32_t LED_T1T2_REPEAT                :4;    /* bits:0-3, Repeat (LED_T1T2_REPEAT+1) times of T1 & T2 during one complete period. For example, if this value is 1, then one complete period is T0->T1->T2->T1->T2->T3. */
        __IO uint32_t LED_REPEAT                     :1;    /* bits:4-4, LED repeat the configured complete period waveform forever   1'b0 : no repeat   1'b1 : repeat (T1->T2->T3->T1->T2->T3…) */
        __IO uint32_t LED_INVERT                     :1;    /* bits:5-5, Invert LED output waveform 0: not invert 1: invert */
        __I  uint32_t __reserved_00                   :10;
        __IO uint32_t LED_FW_EN                      :1;    /* bits:16-16, Enable LED Follow Mode 0: Disable 1: Enable */
        __IO uint32_t LED_FW_SEL                     :2;    /* bits:17-18, LED Follow Source Selection 01: Follow LED1 FSM 10: Follow LED2 FSM Others: Useless */
        __IO uint32_t LED_FW_RETRIG                  :1;    /* bits:19-19, LED Follow Retrigger Mode 0: Re-trigger only when FSM is done 1: Always re-trigger */
        __IO uint32_t LED_FW_T1T2                    :1;    /* bits:20-20, LED Output Trigger Signal 0: End of LED FSM T1 1 End of LED FSM T2 */
        __I  uint32_t __reserved_01                   :11;
    } field;
    __IO uint32_t word;
} LED_CON0_T;

#define LED_CON0_LED_T1T2_REPEAT_OFFSET                                (0U)
#define LED_CON0_LED_T1T2_REPEAT_MASK                                  (0xFU << LED_CON0_LED_T1T2_REPEAT_OFFSET)
#define LED_CON0_LED_REPEAT_OFFSET                                     (4U)
#define LED_CON0_LED_REPEAT_MASK                                       (0x1U << LED_CON0_LED_REPEAT_OFFSET)
#define LED_CON0_LED_INVERT_OFFSET                                     (5U)
#define LED_CON0_LED_INVERT_MASK                                       (0x1U << LED_CON0_LED_INVERT_OFFSET)
#define LED_CON0_LED_FW_EN_OFFSET                                      (16U)
#define LED_CON0_LED_FW_EN_MASK                                        (0x1U << LED_CON0_LED_FW_EN_OFFSET)
#define LED_CON0_LED_FW_SEL_OFFSET                                     (17U)
#define LED_CON0_LED_FW_SEL_MASK                                       (0x3U << LED_CON0_LED_FW_SEL_OFFSET)
#define LED_CON0_LED_FW_RETRIG_OFFSET                                  (19U)
#define LED_CON0_LED_FW_RETRIG_MASK                                    (0x1U << LED_CON0_LED_FW_RETRIG_OFFSET)
#define LED_CON0_LED_FW_T1T2_OFFSET                                    (20U)
#define LED_CON0_LED_FW_T1T2_MASK                                      (0x1U << LED_CON0_LED_FW_T1T2_OFFSET)


/* LED unit */
typedef union {
    struct {
        __IO uint32_t LED_UNIT                       :8;    /* bits:0-7, The time unit of LED_T0, LED_T1, LED_T2 and LED_T3. The corresponding real time is (2^LED_XN * LED_UNIT / fclk ) second. The fclk is the frequency of clk, which is 32KHz. */
        __IO uint32_t LED_XN                         :2;    /* bits:8-9, LED multiplier, to amplify the LED_UNIT additionally.   2'd0 : 1x   2'd1 : 2x   2'd2 : 4x   2'd3 : 8x */
        __I  uint32_t __reserved_00                   :22;
    } field;
    __IO uint32_t word;
} LED_UNIT_T;

#define LED_UNIT_LED_UNIT_OFFSET                                       (0U)
#define LED_UNIT_LED_UNIT_MASK                                         (0xFFU << LED_UNIT_LED_UNIT_OFFSET)
#define LED_UNIT_LED_XN_OFFSET                                         (8U)
#define LED_UNIT_LED_XN_MASK                                           (0x3U << LED_UNIT_LED_XN_OFFSET)


/* LED period control register 0 */
typedef union {
    struct {
        __IO uint32_t LED_T0                         :8;    /* bits:0-7, period of T0 (initial wait period) of LED */
        __IO uint32_t LED_T1                         :8;    /* bits:8-15, period of T1 (led on period) of LED */
        __IO uint32_t LED_T2                         :8;    /* bits:16-23, period of T2 (led off period) of LED */
        __IO uint32_t LED_T3                         :8;    /* bits:24-31, period of T3 (final wait period) of LED */
    } field;
    __IO uint32_t word;
} LED_PERIOD0_T;

#define LED_PERIOD0_LED_T0_OFFSET                                      (0U)
#define LED_PERIOD0_LED_T0_MASK                                        (0xFFU << LED_PERIOD0_LED_T0_OFFSET)
#define LED_PERIOD0_LED_T1_OFFSET                                      (8U)
#define LED_PERIOD0_LED_T1_MASK                                        (0xFFU << LED_PERIOD0_LED_T1_OFFSET)
#define LED_PERIOD0_LED_T2_OFFSET                                      (16U)
#define LED_PERIOD0_LED_T2_MASK                                        (0xFFU << LED_PERIOD0_LED_T2_OFFSET)
#define LED_PERIOD0_LED_T3_OFFSET                                      (24U)
#define LED_PERIOD0_LED_T3_MASK                                        (0xFFU << LED_PERIOD0_LED_T3_OFFSET)


/* LED PWM control register 0 */
typedef union {
    struct {
        __IO uint32_t LED_PWM_LOAD_EN                :1;    /* bits:0-0, Enable to update LED_PWM_DURATION when LED is running. When LED_PWM_DURATION is updated, HW clear this value to 0. */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} LED_PWM0_T;

#define LED_PWM0_LED_PWM_LOAD_EN_OFFSET                                (0U)
#define LED_PWM0_LED_PWM_LOAD_EN_MASK                                  (0x1U << LED_PWM0_LED_PWM_LOAD_EN_OFFSET)


/* LED PWM control register 1 */
typedef union {
    struct {
        __IO uint32_t LED_PWM_PERIOD                 :8;    /* bits:0-7, The period of pwm. Every (LED_PWM_PERIOD+1) clks, the pwm duty is updated according to LED_PWM_DURATION / LED_PWM_OFFSTEP / LED_PWM_ONSTEP. */
        __IO uint32_t LED_PWM_DURATION               :8;    /* bits:8-15, Final duty of LED waveform during every (LED_PWM_PERIOD+1) clks.  This value should not be greater than LED_PWM_PERIOD. If LED_PWM_ONSTEP is not zero, the duty increases smoothly; otherwise, duty goes from 0 to this value directly. If LED_PWM_OFFSTEP is not zero, the duty decreases smoothly; otherwise, duty goes from this value to 0 directly.    LED_PWM_PERIOD    : 100%     LED_PWM_PERIOD-1 : (LED_PWM_PERIOD-1)/(LED_PWM_PERIOD+1)     ...     8'h02 : 2/(LED_PWM_PERIOD+1)     8'h01 : 1/(LED_PWM_PERIOD+1)     8'h00 : invalid (LED never on) The value can be changed even when LED_EN is 1'b1. If the state is in T1, the waveform will ramping to the new value. */
        __IO uint32_t LED_PWM_DURATION2              :8;    /* bits:16-23, OFF State duty of LED waveform during every (LED_PWM_PERIOD+1) clks.  This value should not be greater than LED_PWM_PERIOD.    LED_PWM_PERIOD    : 100%     LED_PWM_PERIOD-1 : (LED_PWM_PERIOD-1)/(LED_PWM_PERIOD+1)     ...     8'h02 : 2/(LED_PWM_PERIOD+1)     8'h01 : 1/(LED_PWM_PERIOD+1)     8'h00 : 0 (LED is OFF when OFF state) */
        __I  uint32_t __reserved_00                   :8;
    } field;
    __IO uint32_t word;
} LED_PWM1_T;

#define LED_PWM1_LED_PWM_PERIOD_OFFSET                                 (0U)
#define LED_PWM1_LED_PWM_PERIOD_MASK                                   (0xFFU << LED_PWM1_LED_PWM_PERIOD_OFFSET)
#define LED_PWM1_LED_PWM_DURATION_OFFSET                               (8U)
#define LED_PWM1_LED_PWM_DURATION_MASK                                 (0xFFU << LED_PWM1_LED_PWM_DURATION_OFFSET)
#define LED_PWM1_LED_PWM_DURATION2_OFFSET                              (16U)
#define LED_PWM1_LED_PWM_DURATION2_MASK                                (0xFFU << LED_PWM1_LED_PWM_DURATION2_OFFSET)


/* LED PWM control register 2 */
typedef union {
    struct {
        __IO uint32_t LED_PWM_ONSTEP                 :8;    /* bits:0-7, Duty increate step. Determine how fast duty reaches led1_pwm_duration_set.    8'd0  : disable breathe (0->final duty directly)   others : every ((LED_PWM_PERIOD+1)*LED_PWM_ONSTEP/fclk) seconds to increase 1/(LED_PWM_PERIOD+1) duty */
        __IO uint32_t LED_PWM_OFFSTEP                :8;    /* bits:8-15, Duty decrease step. Determine how fast duty decrease to 0.   8'd0  : disable breathe (final duty->0 directly)   others : every ((LED_PWM_PERIOD+1)*LED_PWM_OFFSTEP/fclk) seconds to decrease 1/(LED_PWM_PERIOD+1) duty */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} LED_PWM2_T;

#define LED_PWM2_LED_PWM_ONSTEP_OFFSET                                 (0U)
#define LED_PWM2_LED_PWM_ONSTEP_MASK                                   (0xFFU << LED_PWM2_LED_PWM_ONSTEP_OFFSET)
#define LED_PWM2_LED_PWM_OFFSTEP_OFFSET                                (8U)
#define LED_PWM2_LED_PWM_OFFSTEP_MASK                                  (0xFFU << LED_PWM2_LED_PWM_OFFSTEP_OFFSET)

/* LED3 control register 0 */
typedef union {
    struct {
        __I  uint32_t __reserved_00                   :5;
        __IO uint32_t LED3_INVERT                     :1;    /* bits:5-5, Invert LED3 output waveform 0: not invert 1: invert */
        __I  uint32_t __reserved_01                   :26;
    } field;
    __IO uint32_t word;
} LED3_CON0_T;

#define LED3_CON0_LED3_INVERT_OFFSET                                     (5U)
#define LED3_CON0_LED3_INVERT_MASK                                       (0x1U << LED3_CON0_LED3_INVERT_OFFSET)


/* LED3 PWM control register 1 */
typedef union {
    struct {
        __IO uint32_t LED3_PWM_PERIOD                 :8;    /* bits:0-7, The period of pwm. Every (LED3_PWM_PERIOD+1) clks, the pwm duty is updated according to LED3_PWM_DURATION. */
        __IO uint32_t LED3_PWM_DURATION               :8;    /* bits:8-15, Final duty of LED3 waveform during every (LED3_PWM_PERIOD+1) clks.  This value should not be greater than LED3_PWM_PERIOD.    LED3_PWM_PERIOD    : 100%     LED3_PWM_PERIOD-1 : (LED3_PWM_PERIOD-1)/(LED3_PWM_PERIOD+1)     ...     8'h02 : 2/(LED3_PWM_PERIOD+1)     8'h01 : 1/(LED3_PWM_PERIOD+1)     8'h00 : invalid (LED3 never on) */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} LED3_PWM1_T;

#define LED3_PWM1_LED3_PWM_PERIOD_OFFSET                                 (0U)
#define LED3_PWM1_LED3_PWM_PERIOD_MASK                                   (0xFFU << LED3_PWM1_LED3_PWM_PERIOD_OFFSET)
#define LED3_PWM1_LED3_PWM_DURATION_OFFSET                               (8U)
#define LED3_PWM1_LED3_PWM_DURATION_MASK                                 (0xFFU << LED3_PWM1_LED3_PWM_DURATION_OFFSET)


/* Driver debug register */
typedef union {
    struct {
        __IO uint32_t RG_LED0_EN_SW_MODE              :1;    /* bits:0-0, LED0_EN 0: HW mode 1: SW mode from RG_LED0_SW */
        __IO uint32_t RG_LED0_EN_SW                   :1;    /* bits:1-1, LED0_EN SW value */
        __I  uint32_t __reserved_00                   :6;
        __IO uint32_t RG_LED1_EN_SW_MODE              :1;    /* bits:8-8, LED1_EN 0: HW mode 1: SW mode from RG_LED1_SW */
        __IO uint32_t RG_LED1_EN_SW                   :1;    /* bits:9-9, LED1_EN SW value */
        __I  uint32_t __reserved_01                   :6;
        __IO uint32_t RG_LED2_EN_SW_MODE              :1;    /* bits:16-16, LED2_EN 0: HW mode 1: SW mode from RG_LED2_SW */
        __IO uint32_t RG_LED2_EN_SW                   :1;    /* bits:17-17, LED2_EN SW value */
        __I  uint32_t __reserved_02                   :6;
        __IO uint32_t RG_LED3_EN_SW_MODE              :1;    /* bits:24-24, LED3_EN 0: HW mode 1: SW mode from RG_LED3_SW */
        __IO uint32_t RG_LED3_EN_SW                   :1;    /* bits:25-25, LED3_EN SW value */
        __I  uint32_t __reserved_03                   :6;
    } field;
    __IO uint32_t word;
} LED_DBG_CTRL_T;

#define LED_DBG_CTRL_RG_LED0_EN_SW_MODE_OFFSET                           (0U)
#define LED_DBG_CTRL_RG_LED0_EN_SW_MODE_MASK                             (0x1U << LED_DBG_CTRL_RG_LED0_EN_SW_MODE_OFFSET)
#define LED_DBG_CTRL_RG_LED0_EN_SW_OFFSET                                (1U)
#define LED_DBG_CTRL_RG_LED0_EN_SW_MASK                                  (0x1U << LED_DBG_CTRL_RG_LED0_EN_SW_OFFSET)
#define LED_DBG_CTRL_RG_LED1_EN_SW_MODE_OFFSET                           (8U)
#define LED_DBG_CTRL_RG_LED1_EN_SW_MODE_MASK                             (0x1U << LED_DBG_CTRL_RG_LED1_EN_SW_MODE_OFFSET)
#define LED_DBG_CTRL_RG_LED1_EN_SW_OFFSET                                (9U)
#define LED_DBG_CTRL_RG_LED1_EN_SW_MASK                                  (0x1U << LED_DBG_CTRL_RG_LED1_EN_SW_OFFSET)
#define LED_DBG_CTRL_RG_LED2_EN_SW_MODE_OFFSET                           (16U)
#define LED_DBG_CTRL_RG_LED2_EN_SW_MODE_MASK                             (0x1U << LED_DBG_CTRL_RG_LED2_EN_SW_MODE_OFFSET)
#define LED_DBG_CTRL_RG_LED2_EN_SW_OFFSET                                (17U)
#define LED_DBG_CTRL_RG_LED2_EN_SW_MASK                                  (0x1U << LED_DBG_CTRL_RG_LED2_EN_SW_OFFSET)
#define LED_DBG_CTRL_RG_LED3_EN_SW_MODE_OFFSET                           (24U)
#define LED_DBG_CTRL_RG_LED3_EN_SW_MODE_MASK                             (0x1U << LED_DBG_CTRL_RG_LED3_EN_SW_MODE_OFFSET)
#define LED_DBG_CTRL_RG_LED3_EN_SW_OFFSET                                (25U)
#define LED_DBG_CTRL_RG_LED3_EN_SW_MASK                                  (0x1U << LED_DBG_CTRL_RG_LED3_EN_SW_OFFSET)


/* LED Interrupt Status register */
typedef union {
    struct {
        __I  uint32_t LED0_DONE_INTR                  :1;    /* bits:0-0, Interrupt for LED0 Done Status */
        __I  uint32_t LED1_DONE_INTR                  :1;    /* bits:1-1, Interrupt for LED1 Done Status */
        __I  uint32_t LED2_DONE_INTR                  :1;    /* bits:2-2, Interrupt for LED2 Done Status */
        __I  uint32_t __reserved_00                   :29;
    } field;
    __IO uint32_t word;
} LED_INTR_STS_T;

#define LED_INTR_STS_LED0_DONE_INTR_OFFSET                               (0U)
#define LED_INTR_STS_LED0_DONE_INTR_MASK                                 (0x1U << LED_INTR_STS_LED0_DONE_INTR_OFFSET)
#define LED_INTR_STS_LED1_DONE_INTR_OFFSET                               (1U)
#define LED_INTR_STS_LED1_DONE_INTR_MASK                                 (0x1U << LED_INTR_STS_LED1_DONE_INTR_OFFSET)
#define LED_INTR_STS_LED2_DONE_INTR_OFFSET                               (2U)
#define LED_INTR_STS_LED2_DONE_INTR_MASK                                 (0x1U << LED_INTR_STS_LED2_DONE_INTR_OFFSET)


/* LED Interrupt Status Clear register */
typedef union {
    struct {
        __IO uint32_t LED0_DONE_INTR_CLR              :1;    /* bits:0-0, Clear LED0 Done Interrupt */
        __IO uint32_t LED1_DONE_INTR_CLR              :1;    /* bits:1-1, Clear LED1 Done Interrupt */
        __IO uint32_t LED2_DONE_INTR_CLR              :1;    /* bits:2-2, Clear LED2 Done Interrupt */
        __I  uint32_t __reserved_00                   :29;
    } field;
    __IO uint32_t word;
} LED_INTR_CLR_T;

#define LED_INTR_CLR_LED0_DONE_INTR_CLR_OFFSET                           (0U)
#define LED_INTR_CLR_LED0_DONE_INTR_CLR_MASK                             (0x1U << LED_INTR_CLR_LED0_DONE_INTR_CLR_OFFSET)
#define LED_INTR_CLR_LED1_DONE_INTR_CLR_OFFSET                           (1U)
#define LED_INTR_CLR_LED1_DONE_INTR_CLR_MASK                             (0x1U << LED_INTR_CLR_LED1_DONE_INTR_CLR_OFFSET)
#define LED_INTR_CLR_LED2_DONE_INTR_CLR_OFFSET                           (2U)
#define LED_INTR_CLR_LED2_DONE_INTR_CLR_MASK                             (0x1U << LED_INTR_CLR_LED2_DONE_INTR_CLR_OFFSET)


/* LED Interrupt Status Enable register */
typedef union {
    struct {
        __IO uint32_t LED0_DONE_INTR_EN               :1;    /* bits:0-0, Enable LED0 Done Interrupt Status */
        __IO uint32_t LED1_DONE_INTR_EN               :1;    /* bits:1-1, Enable LED1 Done Interrupt Status */
        __IO uint32_t LED2_DONE_INTR_EN               :1;    /* bits:2-2, Enable LED2 Done Interrupt Status */
        __I  uint32_t __reserved_00                   :29;
    } field;
    __IO uint32_t word;
} LED_INTR_EN_T;

#define LED_INTR_EN_LED0_DONE_INTR_EN_OFFSET                             (0U)
#define LED_INTR_EN_LED0_DONE_INTR_EN_MASK                               (0x1U << LED_INTR_EN_LED0_DONE_INTR_EN_OFFSET)
#define LED_INTR_EN_LED1_DONE_INTR_EN_OFFSET                             (1U)
#define LED_INTR_EN_LED1_DONE_INTR_EN_MASK                               (0x1U << LED_INTR_EN_LED1_DONE_INTR_EN_OFFSET)
#define LED_INTR_EN_LED2_DONE_INTR_EN_OFFSET                             (2U)
#define LED_INTR_EN_LED2_DONE_INTR_EN_MASK                               (0x1U << LED_INTR_EN_LED2_DONE_INTR_EN_OFFSET)


/* LED Interrupt Mask register */
typedef union {
    struct {
        __IO uint32_t LED0_DONE_INTR_MSK              :1;    /* bits:0-0, Enable LED0 Done Interrupt Mask */
        __IO uint32_t LED1_DONE_INTR_MSK              :1;    /* bits:1-1, Enable LED1 Done Interrupt Mask */
        __IO uint32_t LED2_DONE_INTR_MSK              :1;    /* bits:2-2, Enable LED2 Done Interrupt Mask */
        __I  uint32_t __reserved_00                   :29;
    } field;
    __IO uint32_t word;
} LED_INTR_MSK_T;

#define LED_INTR_MSK_LED0_DONE_INTR_MSK_OFFSET                           (0U)
#define LED_INTR_MSK_LED0_DONE_INTR_MSK_MASK                             (0x1U << LED_INTR_MSK_LED0_DONE_INTR_MSK_OFFSET)
#define LED_INTR_MSK_LED1_DONE_INTR_MSK_OFFSET                           (1U)
#define LED_INTR_MSK_LED1_DONE_INTR_MSK_MASK                             (0x1U << LED_INTR_MSK_LED1_DONE_INTR_MSK_OFFSET)
#define LED_INTR_MSK_LED2_DONE_INTR_MSK_OFFSET                           (2U)
#define LED_INTR_MSK_LED2_DONE_INTR_MSK_MASK                             (0x1U << LED_INTR_MSK_LED2_DONE_INTR_MSK_OFFSET)


typedef struct {
    LED_CON0_T                                             led_con0; /* offset: 0x00000100, LED control register 0 */
    LED_UNIT_T                                             led_unit; /* offset: 0x00000104, LED unit */
    LED_PERIOD0_T                                       led_period0; /* offset: 0x00000108, LED period control register 0 */
    uint32_t                                         __reserved_02[1]; /* offset: 0x0000010C, padding size: 0x00000004 */
    LED_PWM0_T                                             led_pwm0; /* offset: 0x00000110, LED PWM control register 0 */
    LED_PWM1_T                                             led_pwm1; /* offset: 0x00000114, LED PWM control register 1 */
    LED_PWM2_T                                             led_pwm2; /* offset: 0x00000118, LED PWM control register 2 */
    uint32_t                                         __reserved_03[9]; /* offset: 0x0000011C, padding size: 0x00000024 */
}LED_STRUCT_T;


typedef struct {
    LED_EN_CTRL_T                                         led_en_ctrl; /* offset: 0x00000000, LED enable control */
    uint32_t                                        __reserved_00[15]; /* offset: 0x00000004, padding size: 0x0000003C */
    LED_GBL_CTRL_T                                       led_gbl_ctrl; /* offset: 0x00000040, LED Golbal control register */
    uint32_t                                        __reserved_01[47]; /* offset: 0x00000044, padding size: 0x000000BC */
    LED_STRUCT_T                                         led_struct[3];
    LED3_CON0_T                                             led3_con0; /* offset: 0x000001C0, LED3 control register 0 */
    uint32_t                                         __reserved_08[4]; /* offset: 0x000001C4, padding size: 0x00000010 */
    LED3_PWM1_T                                             led3_pwm1; /* offset: 0x000001D4, LED3 PWM control register 1 */
    uint32_t                                       __reserved_09[138]; /* offset: 0x000001D8, padding size: 0x00000228 */
    LED_DBG_CTRL_T                                       led_dbg_ctrl; /* offset: 0x00000400, Driver debug register */
    uint32_t                                        __reserved_10[63]; /* offset: 0x00000404, padding size: 0x000000FC */
    LED_INTR_STS_T                                       led_intr_sts; /* offset: 0x00000500, LED Interrupt Status register */
    LED_INTR_CLR_T                                       led_intr_clr; /* offset: 0x00000504, LED Interrupt Status Clear register */
    LED_INTR_EN_T                                         led_intr_en; /* offset: 0x00000508, LED Interrupt Status Enable register */
    LED_INTR_MSK_T                                       led_intr_msk; /* offset: 0x0000050C, LED Interrupt Mask register */
} LED_CONTROL_REGISTER_T;

#endif /* __LED_CTRL_REG_DEFINITION_H__ */