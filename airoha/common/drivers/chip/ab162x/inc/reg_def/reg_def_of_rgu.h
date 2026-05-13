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

#ifndef __RGU_REG_DEFINITION_H__
#define __RGU_REG_DEFINITION_H__


/* Watchdog Timer Enable Register */
typedef union {
    struct {
        __IO uint32_t KEY0                            :8;    /* bits:0-7, Configure WDT enable register if KEY= 8'h10 */
        __IO uint32_t WDT_EN                          :1;    /* bits:8-8, Enable the watchdog timer 0: Disable watchdog timer 1: Enable watchdog timer */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t KEY1                            :8;    /* bits:16-23, Configure WDT enable register if KEY= 8'h11 */
        __IO uint32_t WDT_EN_TEST                     :1;    /* bits:24-24, Enable the watchdog timer in testmode 0: Disable watchdog timer 1: Enable watchdog timer */
        __I  uint32_t __reserved_01                   :7;
    } field;
    __IO uint32_t word;
} WDT_EN_T;

#define WDT_EN_KEY0_OFFSET                                               (0U)
#define WDT_EN_KEY0_MASK                                                 (0xFFU << WDT_EN_KEY0_OFFSET)
#define WDT_EN_WDT_EN_OFFSET                                             (8U)
#define WDT_EN_WDT_EN_MASK                                               (0x1U << WDT_EN_WDT_EN_OFFSET)
#define WDT_EN_KEY1_OFFSET                                               (16U)
#define WDT_EN_KEY1_MASK                                                 (0xFFU << WDT_EN_KEY1_OFFSET)
#define WDT_EN_WDT_EN_TEST_OFFSET                                        (24U)
#define WDT_EN_WDT_EN_TEST_MASK                                          (0x1U << WDT_EN_WDT_EN_TEST_OFFSET)


/* Watchdog Length Register */
typedef union {
    struct {
        __IO uint32_t KEY                             :8;    /* bits:0-7, Configure WDT length if KEY= 8'h12 */
        __I  uint32_t __reserved_00                   :8;
        __IO uint32_t WDT_LENGTH                      :16;    /* bits:16-31, Watchdog timer length The length counter unit is 15.625ms. */
    } field;
    __IO uint32_t word;
} WDT_LENGTH_T;

#define WDT_LENGTH_KEY_OFFSET                                            (0U)
#define WDT_LENGTH_KEY_MASK                                              (0xFFU << WDT_LENGTH_KEY_OFFSET)
#define WDT_LENGTH_WDT_LENGTH_OFFSET                                     (16U)
#define WDT_LENGTH_WDT_LENGTH_MASK                                       (0xFFFFU << WDT_LENGTH_WDT_LENGTH_OFFSET)


/* Watchdog Interval Register */
typedef union {
    struct {
        __IO uint32_t KEY                             :8;    /* bits:0-7, Configure WDT interval if KEY= 8'h13 */
        __I  uint32_t __reserved_00                   :8;
        __IO uint32_t WDT_INTERVAL                    :16;    /* bits:16-31, Watchdog timer interval Shows the reset duration when a watchdog timer timeout occurs. The register is not valid when WDT_IE = 1. The interval counter unit is 30.52us. */
    } field;
    __IO uint32_t word;
} WDT_INTERVAL_T;

#define WDT_INTERVAL_KEY_OFFSET                                          (0U)
#define WDT_INTERVAL_KEY_MASK                                            (0xFFU << WDT_INTERVAL_KEY_OFFSET)
#define WDT_INTERVAL_WDT_INTERVAL_OFFSET                                 (16U)
#define WDT_INTERVAL_WDT_INTERVAL_MASK                                   (0xFFFFU << WDT_INTERVAL_WDT_INTERVAL_OFFSET)


/* Watchdog Timer Software Restart Register */
typedef union {
    struct {
        __IO uint32_t KEY                             :32;    /* bits:0-31, Software restart the watchdog timer Restart the watchdog timer if KEY= 32'h1456789a  Only bit 0 is readable 0: watchdog timer is not updating value 1: watchdog time is updating value (please wait this flag de-assert and then write restart register) */
    } field;
    __IO uint32_t word;
} WDT_SW_RESTART_T;

#define WDT_SW_RESTART_KEY_OFFSET                                        (0U)
#define WDT_SW_RESTART_KEY_MASK                                          (0xFFFFFFFFU << WDT_SW_RESTART_KEY_OFFSET)


/* Watchdog Timer Software Reset Register */
typedef union {
    struct {
        __IO uint32_t KEY                             :32;    /* bits:0-31, Software reset the watchdog timer Reset the watchdog timer if KEY= 32'h156789ab */
    } field;
    __IO uint32_t word;
} WDT_SW_RST_T;

#define WDT_SW_RST_KEY_OFFSET                                            (0U)
#define WDT_SW_RST_KEY_MASK                                              (0xFFFFFFFFU << WDT_SW_RST_KEY_OFFSET)


/* Watchdog Timer Auto Restart Register */
typedef union {
    struct {
        __IO uint32_t KEY                             :8;    /* bits:0-7, Configure WDT automatic restart enable register if KEY= 8'h16 */
        __IO uint32_t WDT_AUTO_RESTART_EN             :1;    /* bits:8-8, Enable the watchdog timer to automatic restart. The hardware automatically restarts when the watchdog timer resets. 0: Disable 1: Enable */
        __I  uint32_t __reserved_00                   :23;
    } field;
    __IO uint32_t word;
} WDT_AUTO_RESTART_EN_T;

#define WDT_AUTO_RESTART_EN_KEY_OFFSET                                   (0U)
#define WDT_AUTO_RESTART_EN_KEY_MASK                                     (0xFFU << WDT_AUTO_RESTART_EN_KEY_OFFSET)
#define WDT_AUTO_RESTART_EN_WDT_AUTO_RESTART_EN_OFFSET                   (8U)
#define WDT_AUTO_RESTART_EN_WDT_AUTO_RESTART_EN_MASK                     (0x1U << WDT_AUTO_RESTART_EN_WDT_AUTO_RESTART_EN_OFFSET)


/* Watchdog Timer Status Register */
typedef union {
    struct {
        __I  uint32_t WDT_STA                         :2;    /* bits:0-1, Watchdog timer status [1]: HW_WDT, Shows the cause of watchdog reset 0: Reset not caused by the watchdog timer. 1: Reset caused by expiry of the watchdog timer timeout period. [0]: SW_WDT, Shows if the watchdog timer reset is triggered by software. 0: Reset not caused by watchdog timer triggered software 1: Reset caused by watchdog timer triggered software */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} WDT_STA_T;

#define WDT_STA_WDT_STA_OFFSET                                           (0U)
#define WDT_STA_WDT_STA_MASK                                             (0x3U << WDT_STA_WDT_STA_OFFSET)
#define WDT_STA_WDT_SW_STA_OFFSET                                        (0U)
#define WDT_STA_WDT_SW_STA_MASK                                          (0x1U << WDT_STA_WDT_SW_STA_OFFSET)
#define WDT_STA_WDT_HW_STA_OFFSET                                        (1U)
#define WDT_STA_WDT_HW_STA_MASK                                          (0x1U << WDT_STA_WDT_HW_STA_OFFSET)


/* Watchdog Timer Interrupt Enable Register */
typedef union {
    struct {
        __IO uint32_t KEY_NMI                         :8;    /* bits:0-7, Configure WDT interrupt enable if KEY= 8'h17 */
        __IO uint32_t WDT_NMI_IE                      :1;    /* bits:8-8, Enable the interrupt of the watchdog timer Sends an interrupt signal for the watchdog timer instead of a reset signal */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t KEY_IRQ                         :8;    /* bits:16-23, Configure WDT interrupt enable if KEY= 8'h18 */
        __IO uint32_t WDT_IRQ_IE                      :1;    /* bits:24-24, Enable the interrupt of the watchdog timer Sends an interrupt signal for the watchdog timer instead of a reset signal */
        __I  uint32_t __reserved_01                   :7;
    } field;
    __IO uint32_t word;
} WDT_IE_T;

#define WDT_IE_KEY_NMI_OFFSET                                            (0U)
#define WDT_IE_KEY_NMI_MASK                                              (0xFFU << WDT_IE_KEY_NMI_OFFSET)
#define WDT_IE_WDT_NMI_IE_OFFSET                                         (8U)
#define WDT_IE_WDT_NMI_IE_MASK                                           (0x1U << WDT_IE_WDT_NMI_IE_OFFSET)
#define WDT_IE_KEY_IRQ_OFFSET                                            (16U)
#define WDT_IE_KEY_IRQ_MASK                                              (0xFFU << WDT_IE_KEY_IRQ_OFFSET)
#define WDT_IE_WDT_IRQ_IE_OFFSET                                         (24U)
#define WDT_IE_WDT_IRQ_IE_MASK                                           (0x1U << WDT_IE_WDT_IRQ_IE_OFFSET)


/* Watchdog Timer Interrupt Register */
typedef union {
    struct {
        __I  uint32_t WDT_INT                         :1;    /* bits:0-0, Watchdog timer interrupt WDT interrupt read clear register */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} WDT_INT_T;

#define WDT_INT_WDT_INT_OFFSET                                           (0U)
#define WDT_INT_WDT_INT_MASK                                             (0x1U << WDT_INT_WDT_INT_OFFSET)


/* Watchdog Timer Wakeup Event Enable Register */
typedef union {
    struct {
        __IO uint32_t KEY_WAKEUP_EN                   :8;    /* bits:0-7, Configure WDT interrupt enable if KEY= 8'h19 */
        __IO uint32_t WDT_WAKEUP_EN                   :1;    /* bits:8-8, Enable the wakeup event of the watchdog timer Sends an wakeup event signal for the watchdog timer instead of a reset signal */
        __I  uint32_t __reserved_00                   :23;
    } field;
    __IO uint32_t word;
} WDT_WAKEUP_EN_T;

#define WDT_WAKEUP_EN_KEY_WAKEUP_EN_OFFSET                               (0U)
#define WDT_WAKEUP_EN_KEY_WAKEUP_EN_MASK                                 (0xFFU << WDT_WAKEUP_EN_KEY_WAKEUP_EN_OFFSET)
#define WDT_WAKEUP_EN_WDT_WAKEUP_EN_OFFSET                               (8U)
#define WDT_WAKEUP_EN_WDT_WAKEUP_EN_MASK                                 (0x1U << WDT_WAKEUP_EN_WDT_WAKEUP_EN_OFFSET)


/* Watchdog Timer Wakeup Event Register */
typedef union {
    struct {
        __I  uint32_t WDT_WAKEUP                      :1;    /* bits:0-0, Watchdog timer wakeup event WDT wakeup event read clear register */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} WDT_WAKEUP_T;

#define WDT_WAKEUP_WDT_WAKEUP_OFFSET                                     (0U)
#define WDT_WAKEUP_WDT_WAKEUP_MASK                                       (0x1U << WDT_WAKEUP_WDT_WAKEUP_OFFSET)


/* Watchdog Timer counter current value */
typedef union {
    struct {
        __I  uint32_t WDT_COUNTER_STA                 :25;    /* bits:0-24, Watchdog timer counter current value */
        __I  uint32_t __reserved_00                   :7;
    } field;
    __IO uint32_t word;
} WDT_COUNTER_STA_T;

#define WDT_COUNTER_STA_WDT_COUNTER_STA_OFFSET                           (0U)
#define WDT_COUNTER_STA_WDT_COUNTER_STA_MASK                             (0x1FFFFFFU << WDT_COUNTER_STA_WDT_COUNTER_STA_OFFSET)


/* Watchdog Timer 1 Enable Register */
typedef union {
    struct {
        __IO uint32_t KEY0                            :8;    /* bits:0-7, Configure WDT enable register if KEY= 8'h40 */
        __IO uint32_t WDT1_EN                         :1;    /* bits:8-8, Enable the watchdog timer 0: Disable watchdog timer 1: Enable watchdog timer */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t KEY1                            :8;    /* bits:16-23, Configure WDT enable register if KEY= 8'h41 */
        __IO uint32_t WDT1_EN_TEST                    :1;    /* bits:24-24, Enable the watchdog timer in testmode 0: Disable watchdog timer 1: Enable watchdog timer */
        __I  uint32_t __reserved_01                   :7;
    } field;
    __IO uint32_t word;
} WDT1_EN_T;

#define WDT1_EN_KEY0_OFFSET                                              (0U)
#define WDT1_EN_KEY0_MASK                                                (0xFFU << WDT1_EN_KEY0_OFFSET)
#define WDT1_EN_WDT1_EN_OFFSET                                           (8U)
#define WDT1_EN_WDT1_EN_MASK                                             (0x1U << WDT1_EN_WDT1_EN_OFFSET)
#define WDT1_EN_KEY1_OFFSET                                              (16U)
#define WDT1_EN_KEY1_MASK                                                (0xFFU << WDT1_EN_KEY1_OFFSET)
#define WDT1_EN_WDT1_EN_TEST_OFFSET                                      (24U)
#define WDT1_EN_WDT1_EN_TEST_MASK                                        (0x1U << WDT1_EN_WDT1_EN_TEST_OFFSET)


/* Watchdog Timer 1 Length Register */
typedef union {
    struct {
        __IO uint32_t KEY                             :8;    /* bits:0-7, Configure WDT length if KEY= 8'h42 */
        __I  uint32_t __reserved_00                   :8;
        __IO uint32_t WDT1_LENGTH                     :16;    /* bits:16-31, Watchdog timer length The length counter unit is 15.625ms. */
    } field;
    __IO uint32_t word;
} WDT1_LENGTH_T;

#define WDT1_LENGTH_KEY_OFFSET                                           (0U)
#define WDT1_LENGTH_KEY_MASK                                             (0xFFU << WDT1_LENGTH_KEY_OFFSET)
#define WDT1_LENGTH_WDT1_LENGTH_OFFSET                                   (16U)
#define WDT1_LENGTH_WDT1_LENGTH_MASK                                     (0xFFFFU << WDT1_LENGTH_WDT1_LENGTH_OFFSET)


/* Watchdog Timer 1 Interval Register */
typedef union {
    struct {
        __IO uint32_t KEY                             :8;    /* bits:0-7, Configure WDT interval if KEY= 8'h43 */
        __I  uint32_t __reserved_00                   :8;
        __IO uint32_t WDT1_INTERVAL                   :16;    /* bits:16-31, Watchdog timer interval Shows the reset duration when a watchdog timer timeout occurs. The register is not valid when WDT_IE = 1. The interval counter unit is 30.52us. */
    } field;
    __IO uint32_t word;
} WDT1_INTERVAL_T;

#define WDT1_INTERVAL_KEY_OFFSET                                         (0U)
#define WDT1_INTERVAL_KEY_MASK                                           (0xFFU << WDT1_INTERVAL_KEY_OFFSET)
#define WDT1_INTERVAL_WDT1_INTERVAL_OFFSET                               (16U)
#define WDT1_INTERVAL_WDT1_INTERVAL_MASK                                 (0xFFFFU << WDT1_INTERVAL_WDT1_INTERVAL_OFFSET)


/* Watchdog Timer 1 Software Restart Register */
typedef union {
    struct {
        __IO uint32_t KEY                             :32;    /* bits:0-31, Software restart the watchdog timer Restart the watchdog timer if KEY= 32'h4456789a  Only bit 0 is readable 0: watchdog timer is not updating value 1: watchdog time is updating value (please wait this flag de-assert and then write restart register) */
    } field;
    __IO uint32_t word;
} WDT1_SW_RESTART_T;

#define WDT1_SW_RESTART_KEY_OFFSET                                       (0U)
#define WDT1_SW_RESTART_KEY_MASK                                         (0xFFFFFFFFU << WDT1_SW_RESTART_KEY_OFFSET)


/* Watchdog Timer 1 Software Reset Register */
typedef union {
    struct {
        __IO uint32_t KEY                             :32;    /* bits:0-31, Software reset the watchdog timer Reset the watchdog timer if KEY= 32'h456789ab */
    } field;
    __IO uint32_t word;
} WDT1_SW_RST_T;

#define WDT1_SW_RST_KEY_OFFSET                                           (0U)
#define WDT1_SW_RST_KEY_MASK                                             (0xFFFFFFFFU << WDT1_SW_RST_KEY_OFFSET)


/* Watchdog Timer 1 Auto Restart Register */
typedef union {
    struct {
        __IO uint32_t KEY                             :8;    /* bits:0-7, Configure WDT automatic restart enable register if KEY= 8'h46 */
        __IO uint32_t WDT1_AUTO_RESTART_EN            :1;    /* bits:8-8, Enable the watchdog timer to automatic restart. The hardware automatically restarts when the watchdog timer resets. 0: Disable 1: Enable */
        __I  uint32_t __reserved_00                   :23;
    } field;
    __IO uint32_t word;
} WDT1_AUTO_RESTART_EN_T;

#define WDT1_AUTO_RESTART_EN_KEY_OFFSET                                  (0U)
#define WDT1_AUTO_RESTART_EN_KEY_MASK                                    (0xFFU << WDT1_AUTO_RESTART_EN_KEY_OFFSET)
#define WDT1_AUTO_RESTART_EN_WDT1_AUTO_RESTART_EN_OFFSET                 (8U)
#define WDT1_AUTO_RESTART_EN_WDT1_AUTO_RESTART_EN_MASK                   (0x1U << WDT1_AUTO_RESTART_EN_WDT1_AUTO_RESTART_EN_OFFSET)


/* Watchdog Timer 1 Status Register */
typedef union {
    struct {
        __I  uint32_t WDT1_STA                        :2;    /* bits:0-1, Watchdog timer status [1]: HW_WDT, Shows the cause of watchdog reset 0: Reset not caused by the watchdog timer. 1: Reset caused by expiry of the watchdog timer timeout period. [0]: SW_WDT, Shows if the watchdog timer reset is triggered by software. 0: Reset not caused by watchdog timer triggered software 1: Reset caused by watchdog timer triggered software */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} WDT1_STA_T;

#define WDT1_STA_WDT1_STA_OFFSET                                         (0U)
#define WDT1_STA_WDT1_STA_MASK                                           (0x3U << WDT1_STA_WDT1_STA_OFFSET)


/* Watchdog Timer 1 Interrupt Enable Register */
typedef union {
    struct {
        __IO uint32_t KEY_NMI                         :8;    /* bits:0-7, Configure WDT interrupt enable if KEY= 8'h47 */
        __IO uint32_t WDT1_NMI_IE                     :1;    /* bits:8-8, Enable the interrupt of the watchdog timer Sends an interrupt signal for the watchdog timer instead of a reset signal */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t KEY_IRQ                         :8;    /* bits:16-23, Configure WDT interrupt enable if KEY= 8'h48 */
        __IO uint32_t WDT1_IRQ_IE                     :1;    /* bits:24-24, Enable the interrupt of the watchdog timer Sends an interrupt signal for the watchdog timer instead of a reset signal */
        __I  uint32_t __reserved_01                   :7;
    } field;
    __IO uint32_t word;
} WDT1_IE_T;

#define WDT1_IE_KEY_NMI_OFFSET                                           (0U)
#define WDT1_IE_KEY_NMI_MASK                                             (0xFFU << WDT1_IE_KEY_NMI_OFFSET)
#define WDT1_IE_WDT1_NMI_IE_OFFSET                                       (8U)
#define WDT1_IE_WDT1_NMI_IE_MASK                                         (0x1U << WDT1_IE_WDT1_NMI_IE_OFFSET)
#define WDT1_IE_KEY_IRQ_OFFSET                                           (16U)
#define WDT1_IE_KEY_IRQ_MASK                                             (0xFFU << WDT1_IE_KEY_IRQ_OFFSET)
#define WDT1_IE_WDT1_IRQ_IE_OFFSET                                       (24U)
#define WDT1_IE_WDT1_IRQ_IE_MASK                                         (0x1U << WDT1_IE_WDT1_IRQ_IE_OFFSET)


/* Watchdog Timer 1 Interrupt Register */
typedef union {
    struct {
        __I  uint32_t WDT1_INT                        :1;    /* bits:0-0, Watchdog timer interrupt WDT interrupt read clear register */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} WDT1_INT_T;

#define WDT1_INT_WDT1_INT_OFFSET                                         (0U)
#define WDT1_INT_WDT1_INT_MASK                                           (0x1U << WDT1_INT_WDT1_INT_OFFSET)


/* Watchdog Timer 1 Wakeup Event Enable Register */
typedef union {
    struct {
        __IO uint32_t KEY_WAKEUP_EN                   :8;    /* bits:0-7, Configure WDT interrupt enable if KEY= 8'h49 */
        __IO uint32_t WDT1_WAKEUP_EN                  :1;    /* bits:8-8, Enable the wakeup event of the watchdog timer Sends an wakeup event signal for the watchdog timer instead of a reset signal */
        __I  uint32_t __reserved_00                   :23;
    } field;
    __IO uint32_t word;
} WDT1_WAKEUP_EN_T;

#define WDT1_WAKEUP_EN_KEY_WAKEUP_EN_OFFSET                              (0U)
#define WDT1_WAKEUP_EN_KEY_WAKEUP_EN_MASK                                (0xFFU << WDT1_WAKEUP_EN_KEY_WAKEUP_EN_OFFSET)
#define WDT1_WAKEUP_EN_WDT1_WAKEUP_EN_OFFSET                             (8U)
#define WDT1_WAKEUP_EN_WDT1_WAKEUP_EN_MASK                               (0x1U << WDT1_WAKEUP_EN_WDT1_WAKEUP_EN_OFFSET)


/* Watchdog Timer 1 Wakeup Event Register */
typedef union {
    struct {
        __I  uint32_t WDT1_WAKEUP                     :1;    /* bits:0-0, Watchdog timer wakeup event WDT wakeup event read clear register */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} WDT1_WAKEUP_T;

#define WDT1_WAKEUP_WDT1_WAKEUP_OFFSET                                   (0U)
#define WDT1_WAKEUP_WDT1_WAKEUP_MASK                                     (0x1U << WDT1_WAKEUP_WDT1_WAKEUP_OFFSET)


/* Watchdog Timer 1 counter current value */
typedef union {
    struct {
        __I  uint32_t WDT1_COUNTER_STA                :25;    /* bits:0-24, Watchdog timer counter current value */
        __I  uint32_t __reserved_00                   :7;
    } field;
    __IO uint32_t word;
} WDT1_COUNTER_STA_T;

#define WDT1_COUNTER_STA_WDT1_COUNTER_STA_OFFSET                         (0U)
#define WDT1_COUNTER_STA_WDT1_COUNTER_STA_MASK                           (0x1FFFFFFU << WDT1_COUNTER_STA_WDT1_COUNTER_STA_OFFSET)


/* Software Reset System Register */
typedef union {
    struct {
        __IO uint32_t KEY0                            :8;    /* bits:0-7, Configure SYSTEM software reset if KEY= 8'h1a */
        __IO uint32_t SYSTEM_SW_RST                   :1;    /* bits:8-8, SYSTEM_SW_RST 0: Disable reset 1: Enable reset */
        __I  uint32_t __reserved_00                   :23;
    } field;
    __IO uint32_t word;
} SW_RSTSYS_T;

#define SW_RSTSYS_KEY0_OFFSET                                            (0U)
#define SW_RSTSYS_KEY0_MASK                                              (0xFFU << SW_RSTSYS_KEY0_OFFSET)
#define SW_RSTSYS_SYSTEM_SW_RST_OFFSET                                   (8U)
#define SW_RSTSYS_SYSTEM_SW_RST_MASK                                     (0x1U << SW_RSTSYS_SYSTEM_SW_RST_OFFSET)


/* Software Reset 0 Register */
typedef union {
    struct {
#if 0
        __IO uint32_t KEY0                            :8;    /* bits:0-7, Configure RISCV software reset if KEY= 8'h1b */
        __IO uint32_t MODULE0_SW_RST                  :1;    /* bits:8-8, RISCV_SW_RST 0: Disable reset 1: Enable reset */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t KEY1                            :8;    /* bits:16-23, Configure    software reset if KEY= 8'h1c */
        __IO uint32_t MODULE1_SW_RST                  :1;    /* bits:24-24, SW_RST 0: Disable reset 1: Enable reset */
        __I  uint32_t __reserved_01                   :7;
#endif
        __IO uint16_t RISCV_SW_RST;
        __I uint16_t RESERVED;
    } field;
    __IO uint32_t word;
} SW_RST0_T;

#define SW_RST0_KEY0_OFFSET                                              (0U)
#define SW_RST0_KEY0_MASK                                                (0xFFU << SW_RST0_KEY0_OFFSET)
#define SW_RST0_MODULE0_SW_RST_OFFSET                                    (8U)
#define SW_RST0_MODULE0_SW_RST_MASK                                      (0x1U << SW_RST0_MODULE0_SW_RST_OFFSET)
#define SW_RST0_KEY1_OFFSET                                              (16U)
#define SW_RST0_KEY1_MASK                                                (0xFFU << SW_RST0_KEY1_OFFSET)
#define SW_RST0_MODULE1_SW_RST_OFFSET                                    (24U)
#define SW_RST0_MODULE1_SW_RST_MASK                                      (0x1U << SW_RST0_MODULE1_SW_RST_OFFSET)


/* Software Reset 1 Register */
typedef union {
    struct {
#if 0
        __IO uint32_t KEY0                            :8;    /* bits:0-7, Configure CONNSYS software reset if KEY= 8'h1d */
        __IO uint32_t MODULE2_SW_RST                  :1;    /* bits:8-8, SW_RST 0: Disable reset 1: Enable reset */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t KEY1                            :8;    /* bits:16-23, Configure      software reset if KEY= 8'h1e */
        __IO uint32_t MODULE3_SW_RST                  :1;    /* bits:24-24, SW_RST 0: Disable reset 1: Enable reset */
        __I  uint32_t __reserved_01                   :7;
#endif
        __IO uint16_t CONNSYS_SW_RST;
        __I uint16_t RESERVED;
    } field;
    __IO uint32_t word;
} SW_RST1_T;

#define SW_RST1_KEY0_OFFSET                                              (0U)
#define SW_RST1_KEY0_MASK                                                (0xFFU << SW_RST1_KEY0_OFFSET)
#define SW_RST1_MODULE2_SW_RST_OFFSET                                    (8U)
#define SW_RST1_MODULE2_SW_RST_MASK                                      (0x1U << SW_RST1_MODULE2_SW_RST_OFFSET)
#define SW_RST1_KEY1_OFFSET                                              (16U)
#define SW_RST1_KEY1_MASK                                                (0xFFU << SW_RST1_KEY1_OFFSET)
#define SW_RST1_MODULE3_SW_RST_OFFSET                                    (24U)
#define SW_RST1_MODULE3_SW_RST_MASK                                      (0x1U << SW_RST1_MODULE3_SW_RST_OFFSET)


/* Software Reset 2 Register */
typedef union {
    struct {
#if 0
        __IO uint32_t KEY0                            :8;    /* bits:0-7, Configure AUDIOSYS software reset if KEY= 8'h1f */
        __IO uint32_t MODULE4_SW_RST                  :1;    /* bits:8-8, SW_RST 0: Disable reset 1: Enable reset */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t KEY1                            :8;    /* bits:16-23, Configure      software reset if KEY= 8'h20 */
        __IO uint32_t MODULE5_SW_RST                  :1;    /* bits:24-24, SW_RST 0: Disable reset 1: Enable reset */
        __I  uint32_t __reserved_01                   :7;
#endif
        __IO uint16_t AUDIOSYS_SW_RST;
        __I uint16_t RESERVED;
    } field;
    __IO uint32_t word;
} SW_RST2_T;

#define SW_RST2_KEY0_OFFSET                                              (0U)
#define SW_RST2_KEY0_MASK                                                (0xFFU << SW_RST2_KEY0_OFFSET)
#define SW_RST2_MODULE4_SW_RST_OFFSET                                    (8U)
#define SW_RST2_MODULE4_SW_RST_MASK                                      (0x1U << SW_RST2_MODULE4_SW_RST_OFFSET)
#define SW_RST2_KEY1_OFFSET                                              (16U)
#define SW_RST2_KEY1_MASK                                                (0xFFU << SW_RST2_KEY1_OFFSET)
#define SW_RST2_MODULE5_SW_RST_OFFSET                                    (24U)
#define SW_RST2_MODULE5_SW_RST_MASK                                      (0x1U << SW_RST2_MODULE5_SW_RST_OFFSET)


/* Software Reset 3 Register */
typedef union {
    struct {
#if 0
        __IO uint32_t KEY0                            :8;    /* bits:0-7, Configure USB software reset if KEY= 8'h21 */
        __IO uint32_t MODULE6_SW_RST                  :1;    /* bits:8-8, USB_SW_RST 0: Disable reset 1: Eenable reset */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t KEY1                            :8;    /* bits:16-23, Configure USBSIF software reset if KEY= 8'h22 */
        __IO uint32_t MODULE7_SW_RST                  :1;    /* bits:24-24, USBSIF_SW_RST 0: Disable reset 1: Eenable reset */
        __I  uint32_t __reserved_01                   :7;
#endif
        __IO uint16_t USB_SW_RST;
        __IO uint16_t USBSIF_SW_RST;
    } field;
    __IO uint32_t word;
} SW_RST3_T;

#define SW_RST3_KEY0_OFFSET                                              (0U)
#define SW_RST3_KEY0_MASK                                                (0xFFU << SW_RST3_KEY0_OFFSET)
#define SW_RST3_MODULE6_SW_RST_OFFSET                                    (8U)
#define SW_RST3_MODULE6_SW_RST_MASK                                      (0x1U << SW_RST3_MODULE6_SW_RST_OFFSET)
#define SW_RST3_KEY1_OFFSET                                              (16U)
#define SW_RST3_KEY1_MASK                                                (0xFFU << SW_RST3_KEY1_OFFSET)
#define SW_RST3_MODULE7_SW_RST_OFFSET                                    (24U)
#define SW_RST3_MODULE7_SW_RST_MASK                                      (0x1U << SW_RST3_MODULE7_SW_RST_OFFSET)


/* Reset Mask 0 Register */
typedef union {
    struct {
#if 0
        __IO uint32_t KEY0                            :8;    /* bits:0-7, Configure JTAG reset mask if KEY= 8'h23 */
        __IO uint32_t MODULE0_RST_MASK                :1;    /* bits:8-8, JTAG reset mask Mask reset source from JTAG, Enable by default. 0: Disable mask 1: Enable mask */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t KEY1                            :8;    /* bits:16-23, Configure AIRCR reset mask if KEY= 8'h24 */
        __IO uint32_t MODULE1_RST_MASK                :1;    /* bits:24-24, AIRCR reset require mask Mask reset source from AIRCR, Enable by default. 0: Disable mask 1: Enable mask */
        __I  uint32_t __reserved_01                   :7;
#endif
        __IO uint16_t JTAG_RESET;
        __IO uint16_t AIRCR_RESET;
    } field;
    __IO uint32_t word;
} RST_MASK0_T;

#define RST_MASK0_KEY0_OFFSET                                            (0U)
#define RST_MASK0_KEY0_MASK                                              (0xFFU << RST_MASK0_KEY0_OFFSET)
#define RST_MASK0_MODULE0_RST_MASK_OFFSET                                (8U)
#define RST_MASK0_MODULE0_RST_MASK_MASK                                  (0x1U << RST_MASK0_MODULE0_RST_MASK_OFFSET)
#define RST_MASK0_KEY1_OFFSET                                            (16U)
#define RST_MASK0_KEY1_MASK                                              (0xFFU << RST_MASK0_KEY1_OFFSET)
#define RST_MASK0_MODULE1_RST_MASK_OFFSET                                (24U)
#define RST_MASK0_MODULE1_RST_MASK_MASK                                  (0x1U << RST_MASK0_MODULE1_RST_MASK_OFFSET)


/* Reset Mask 1 Register */
typedef union {
    struct {
#if 0
        __IO uint32_t KEY0                            :8;    /* bits:0-7, Configure PCM reset mask if KEY= 8'h25 */
        __IO uint32_t MODULE2_RST_MASK                :1;    /* bits:8-8, PCM reset require mask Mask reset source from PCM, Enable by default. 0: Disable mask 1: Enable mask */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t KEY1                            :8;    /* bits:16-23, Configure PMU reset mask if KEY= 8'h26 */
        __IO uint32_t MODULE3_RST_MASK                :1;    /* bits:24-24, PMU reset mask Mask reset to PMU, Enable by default. 0: Disable mask 1: Enable mask */
        __I  uint32_t __reserved_01                   :7;
#endif
        __IO uint16_t PCM_RESET;
        __IO uint16_t PMU_RESET;
    } field;
    __IO uint32_t word;
} RST_MASK1_T;

#define RST_MASK1_KEY0_OFFSET                                            (0U)
#define RST_MASK1_KEY0_MASK                                              (0xFFU << RST_MASK1_KEY0_OFFSET)
#define RST_MASK1_MODULE2_RST_MASK_OFFSET                                (8U)
#define RST_MASK1_MODULE2_RST_MASK_MASK                                  (0x1U << RST_MASK1_MODULE2_RST_MASK_OFFSET)
#define RST_MASK1_KEY1_OFFSET                                            (16U)
#define RST_MASK1_KEY1_MASK                                              (0xFFU << RST_MASK1_KEY1_OFFSET)
#define RST_MASK1_MODULE3_RST_MASK_OFFSET                                (24U)
#define RST_MASK1_MODULE3_RST_MASK_MASK                                  (0x1U << RST_MASK1_MODULE3_RST_MASK_OFFSET)


/* Reset Fucntion Control Register */
typedef union {
    struct {
        __IO uint32_t KEY0                            :8;    /* bits:0-7, KEY= 8'h27 */
        __IO uint32_t CM4_RST_INTERVAL                :8;    /* bits:8-15, CM4 (AIRCR) reset interval Shows the reset duration when CM4 AIRCR is enabled. The interval counter unit is 3.05 us. */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} RST_FUNC_CONT0_T;

#define RST_FUNC_CONT0_KEY0_OFFSET                                       (0U)
#define RST_FUNC_CONT0_KEY0_MASK                                         (0xFFU << RST_FUNC_CONT0_KEY0_OFFSET)
#define RST_FUNC_CONT0_CM4_RST_INTERVAL_OFFSET                           (8U)
#define RST_FUNC_CONT0_CM4_RST_INTERVAL_MASK                             (0xFFU << RST_FUNC_CONT0_CM4_RST_INTERVAL_OFFSET)


/* Reset Fucntion Control Register */
typedef union {
    struct {
#if 0
        __IO uint32_t KEY0                            :8;    /* bits:0-7, Configure Retention flag 0 reset mask if KEY= 8'h28 */
        __IO uint32_t PMU_RST_INV_EN                  :1;    /* bits:8-8, Polarity of reset to the PMU 0: PMU reset active low 1: PMU reset active high */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t KEY1                            :8;    /* bits:16-23, Configure Retention flag 0 reset mask if KEY= 8'h29 */
        __IO uint32_t PMIC_IO_RST_INV_EN              :1;    /* bits:24-24, Polarity of reset to the PMIC (IO output) 0: PMIC reset active low 1: PMIC reset active high */
        __I  uint32_t __reserved_01                   :7;
#endif
        __IO uint16_t PMU_RST_INV_EN;
        __IO uint16_t PMIC_IO_RST_INV_EN;
    } field;
    __IO uint32_t word;
} RST_FUNC_CONT1_T;

#define RST_FUNC_CONT1_KEY0_OFFSET                                       (0U)
#define RST_FUNC_CONT1_KEY0_MASK                                         (0xFFU << RST_FUNC_CONT1_KEY0_OFFSET)
#define RST_FUNC_CONT1_PMU_RST_INV_EN_OFFSET                             (8U)
#define RST_FUNC_CONT1_PMU_RST_INV_EN_MASK                               (0x1U << RST_FUNC_CONT1_PMU_RST_INV_EN_OFFSET)
#define RST_FUNC_CONT1_KEY1_OFFSET                                       (16U)
#define RST_FUNC_CONT1_KEY1_MASK                                         (0xFFU << RST_FUNC_CONT1_KEY1_OFFSET)
#define RST_FUNC_CONT1_PMIC_IO_RST_INV_EN_OFFSET                         (24U)
#define RST_FUNC_CONT1_PMIC_IO_RST_INV_EN_MASK                           (0x1U << RST_FUNC_CONT1_PMIC_IO_RST_INV_EN_OFFSET)


/* Retention Flag 0 Register */
typedef union {
    struct {
        __IO uint32_t KEY                             :8;    /* bits:0-7, Configure Retention flag 0 reset mask if KEY= 8'h2a */
        __I  uint32_t __reserved_00                   :8;
        __IO uint32_t RETN_FLAG0                      :16;    /* bits:16-31, Retention flag 0 This register can only be reset by the hardware. */
    } field;
    __IO uint32_t word;
} RETN_FLAG0_T;

#define RETN_FLAG0_KEY_OFFSET                                            (0U)
#define RETN_FLAG0_KEY_MASK                                              (0xFFU << RETN_FLAG0_KEY_OFFSET)
#define RETN_FLAG0_RETN_FLAG0_OFFSET                                     (16U)
#define RETN_FLAG0_RETN_FLAG0_MASK                                       (0xFFFFU << RETN_FLAG0_RETN_FLAG0_OFFSET)


/* Retention Flag 1 Register */
typedef union {
    struct {
        __IO uint32_t KEY                             :8;    /* bits:0-7, Configure Retention flag 1 reset mask if KEY= 8'h2b */
        __I  uint32_t __reserved_00                   :8;
        __IO uint32_t RETN_FLAG1                      :16;    /* bits:16-31, Retention flag 1 This register can only be reset by the hardware. */
    } field;
    __IO uint32_t word;
} RETN_FLAG1_T;

#define RETN_FLAG1_KEY_OFFSET                                            (0U)
#define RETN_FLAG1_KEY_MASK                                              (0xFFU << RETN_FLAG1_KEY_OFFSET)
#define RETN_FLAG1_RETN_FLAG1_OFFSET                                     (16U)
#define RETN_FLAG1_RETN_FLAG1_MASK                                       (0xFFFFU << RETN_FLAG1_RETN_FLAG1_OFFSET)


/* Retention Flag 2 Register */
typedef union {
    struct {
        __IO uint32_t KEY                             :8;    /* bits:0-7, Configure Retention flag 2 reset mask if KEY= 8'h2c */
        __I  uint32_t __reserved_00                   :8;
        __IO uint32_t RETN_FLAG2                      :16;    /* bits:16-31, Retention flag 2 This register can only be reset by the hardware. */
    } field;
    __IO uint32_t word;
} RETN_FLAG2_T;

#define RETN_FLAG2_KEY_OFFSET                                            (0U)
#define RETN_FLAG2_KEY_MASK                                              (0xFFU << RETN_FLAG2_KEY_OFFSET)
#define RETN_FLAG2_RETN_FLAG2_OFFSET                                     (16U)
#define RETN_FLAG2_RETN_FLAG2_MASK                                       (0xFFFFU << RETN_FLAG2_RETN_FLAG2_OFFSET)


/* Retention Flag 3 Register */
typedef union {
    struct {
        __IO uint32_t KEY                             :8;    /* bits:0-7, Configure Retention flag 3 reset mask if KEY= 8'h2d */
        __I  uint32_t __reserved_00                   :8;
        __IO uint32_t RETN_FLAG3                      :16;    /* bits:16-31, Retention flag 3 This register can only be reset by the hardware. */
    } field;
    __IO uint32_t word;
} RETN_FLAG3_T;

#define RETN_FLAG3_KEY_OFFSET                                            (0U)
#define RETN_FLAG3_KEY_MASK                                              (0xFFU << RETN_FLAG3_KEY_OFFSET)
#define RETN_FLAG3_RETN_FLAG3_OFFSET                                     (16U)
#define RETN_FLAG3_RETN_FLAG3_MASK                                       (0xFFFFU << RETN_FLAG3_RETN_FLAG3_OFFSET)


/* Retention Flag 4 Register */
typedef union {
    struct {
        __IO uint32_t KEY                             :8;    /* bits:0-7, Configure Retention flag 4 reset mask if KEY= 8'h2e */
        __I  uint32_t __reserved_00                   :8;
        __IO uint32_t RETN_FLAG4                      :16;    /* bits:16-31, Retention flag 4 This register can only be reset by the hardware. */
    } field;
    __IO uint32_t word;
} RETN_FLAG4_T;

#define RETN_FLAG4_KEY_OFFSET                                            (0U)
#define RETN_FLAG4_KEY_MASK                                              (0xFFU << RETN_FLAG4_KEY_OFFSET)
#define RETN_FLAG4_RETN_FLAG4_OFFSET                                     (16U)
#define RETN_FLAG4_RETN_FLAG4_MASK                                       (0xFFFFU << RETN_FLAG4_RETN_FLAG4_OFFSET)


/* Retention Flag 5 Register */
typedef union {
    struct {
        __IO uint32_t KEY                             :8;    /* bits:0-7, Configure Retention flag 5 reset mask if KEY= 8'h2f */
        __I  uint32_t __reserved_00                   :8;
        __IO uint32_t RETN_FLAG5                      :16;    /* bits:16-31, Retention flag 5 This register can only be reset by the hardware. */
    } field;
    __IO uint32_t word;
} RETN_FLAG5_T;

#define RETN_FLAG5_KEY_OFFSET                                            (0U)
#define RETN_FLAG5_KEY_MASK                                              (0xFFU << RETN_FLAG5_KEY_OFFSET)
#define RETN_FLAG5_RETN_FLAG5_OFFSET                                     (16U)
#define RETN_FLAG5_RETN_FLAG5_MASK                                       (0xFFFFU << RETN_FLAG5_RETN_FLAG5_OFFSET)


/* Retention Data 0 Register */
typedef union {
    struct {
        __IO uint32_t RETN_DAT0                       :32;    /* bits:0-31, Retention data 0 This register can only be reset by the hardware. */
    } field;
    __IO uint32_t word;
} RETN_DAT0_T;

#define RETN_DAT0_RETN_DAT0_OFFSET                                       (0U)
#define RETN_DAT0_RETN_DAT0_MASK                                         (0xFFFFFFFFU << RETN_DAT0_RETN_DAT0_OFFSET)


/* Retention Data 1 Register */
typedef union {
    struct {
        __IO uint32_t RETN_DAT1                       :32;    /* bits:0-31, Retention data 1 This register can only be reset by the hardware. */
    } field;
    __IO uint32_t word;
} RETN_DAT1_T;

#define RETN_DAT1_RETN_DAT1_OFFSET                                       (0U)
#define RETN_DAT1_RETN_DAT1_MASK                                         (0xFFFFFFFFU << RETN_DAT1_RETN_DAT1_OFFSET)


/* Retention Data 2 Register */
typedef union {
    struct {
        __IO uint32_t RETN_DAT2                       :32;    /* bits:0-31, Retention data 2 This register can only be reset by the hardware. */
    } field;
    __IO uint32_t word;
} RETN_DAT2_T;

#define RETN_DAT2_RETN_DAT2_OFFSET                                       (0U)
#define RETN_DAT2_RETN_DAT2_MASK                                         (0xFFFFFFFFU << RETN_DAT2_RETN_DAT2_OFFSET)


/* Retention Data 3 Register */
typedef union {
    struct {
        __IO uint32_t RETN_DAT3                       :32;    /* bits:0-31, Retention data 3 This register can only be reset by the hardware. */
    } field;
    __IO uint32_t word;
} RETN_DAT3_T;

#define RETN_DAT3_RETN_DAT3_OFFSET                                       (0U)
#define RETN_DAT3_RETN_DAT3_MASK                                         (0xFFFFFFFFU << RETN_DAT3_RETN_DAT3_OFFSET)


/* Retention Data 4 Register */
typedef union {
    struct {
        __IO uint32_t RETN_DAT4                       :32;    /* bits:0-31, Retention data 4 This register can only be reset by the hardware. */
    } field;
    __IO uint32_t word;
} RETN_DAT4_T;

#define RETN_DAT4_RETN_DAT4_OFFSET                                       (0U)
#define RETN_DAT4_RETN_DAT4_MASK                                         (0xFFFFFFFFU << RETN_DAT4_RETN_DAT4_OFFSET)


/* Retention Data 5 Register */
typedef union {
    struct {
        __IO uint32_t RETN_DAT5                       :32;    /* bits:0-31, Retention data 5 This register can only be reset by the hardware. */
    } field;
    __IO uint32_t word;
} RETN_DAT5_T;

#define RETN_DAT5_RETN_DAT5_OFFSET                                       (0U)
#define RETN_DAT5_RETN_DAT5_MASK                                         (0xFFFFFFFFU << RETN_DAT5_RETN_DAT5_OFFSET)


/* pmu testmode sw reset */
typedef union {
    struct {
        __IO uint32_t KEY                             :8;    /* bits:0-7, Configure Retention flag 0 reset mask if KEY= 8'h30 */
        __IO uint32_t PMU_TEST_SW_RST                 :1;    /* bits:8-8, PMU_TEST_SW_RST 0: Disable reset 1: Eenable reset */
        __I  uint32_t __reserved_00                   :23;
    } field;
    __IO uint32_t word;
} PMU_TEST_SW_RST_T;

#define PMU_TEST_SW_RST_KEY_OFFSET                                       (0U)
#define PMU_TEST_SW_RST_KEY_MASK                                         (0xFFU << PMU_TEST_SW_RST_KEY_OFFSET)
#define PMU_TEST_SW_RST_PMU_TEST_SW_RST_OFFSET                           (8U)
#define PMU_TEST_SW_RST_PMU_TEST_SW_RST_MASK                             (0x1U << PMU_TEST_SW_RST_PMU_TEST_SW_RST_OFFSET)


/* Software Reset for rf Register */
typedef union {
    struct {
        __IO uint32_t KEY0                            :8;    /* bits:0-7, Configure RF software reset if KEY= 8'h31 */
        __IO uint32_t RF_SW_RST                       :1;    /* bits:8-8, RF_SW_RST 0: Disable reset 1: Eenable reset */
        __I  uint32_t __reserved_00                   :23;
    } field;
    __IO uint32_t word;
} SW_RF_RST_T;

#define SW_RF_RST_KEY0_OFFSET                                            (0U)
#define SW_RF_RST_KEY0_MASK                                              (0xFFU << SW_RF_RST_KEY0_OFFSET)
#define SW_RF_RST_RF_SW_RST_OFFSET                                       (8U)
#define SW_RF_RST_RF_SW_RST_MASK                                         (0x1U << SW_RF_RST_RF_SW_RST_OFFSET)


/* debug select */
typedef union {
    struct {
        __IO uint32_t DEBUG_SEL                       :32;    /* bits:0-31, debug select single */
    } field;
    __IO uint32_t word;
} RGU_DEBUG_SEL_T;

#define RGU_DEBUG_SEL_DEBUG_SEL_OFFSET                                   (0U)
#define RGU_DEBUG_SEL_DEBUG_SEL_MASK                                     (0xFFFFFFFFU << RGU_DEBUG_SEL_DEBUG_SEL_OFFSET)


typedef struct {
    WDT_EN_T                                                   wdt_en; /* offset: 0x00000000, Watchdog Timer Enable Register */
    WDT_LENGTH_T                                           wdt_length; /* offset: 0x00000004, Watchdog Length Register */
    WDT_INTERVAL_T                                       wdt_interval; /* offset: 0x00000008, Watchdog Interval Register */
    WDT_SW_RESTART_T                                   wdt_sw_restart; /* offset: 0x0000000C, Watchdog Timer Software Restart Register */
    WDT_SW_RST_T                                           wdt_sw_rst; /* offset: 0x00000010, Watchdog Timer Software Reset Register */
    WDT_AUTO_RESTART_EN_T                         wdt_auto_restart_en; /* offset: 0x00000014, Watchdog Timer Auto Restart Register */
    WDT_STA_T                                                 wdt_sta; /* offset: 0x00000018, Watchdog Timer Status Register */
    WDT_IE_T                                                   wdt_ie; /* offset: 0x0000001C, Watchdog Timer Interrupt Enable Register */
    WDT_INT_T                                                 wdt_int; /* offset: 0x00000020, Watchdog Timer Interrupt Register */
    WDT_WAKEUP_EN_T                                     wdt_wakeup_en; /* offset: 0x00000024, Watchdog Timer Wakeup Event Enable Register */
    WDT_WAKEUP_T                                           wdt_wakeup; /* offset: 0x00000028, Watchdog Timer Wakeup Event Register */
    WDT_COUNTER_STA_T                                 wdt_counter_sta; /* offset: 0x0000002C, Watchdog Timer counter current value */
} RGU_REGISTER_T;


typedef struct {
    SW_RSTSYS_T                                             sw_rstsys; /* offset: 0x00000060, Software Reset System Register */
    SW_RST0_T                                                 sw_rst0; /* offset: 0x00000064, Software Reset 0 Register */
    SW_RST1_T                                                 sw_rst1; /* offset: 0x00000068, Software Reset 1 Register */
    SW_RST2_T                                                 sw_rst2; /* offset: 0x0000006C, Software Reset 2 Register */
    SW_RST3_T                                                 sw_rst3; /* offset: 0x00000070, Software Reset 3 Register */
    uint32_t                                         __reserved_00[3]; /* offset: 0x00000074, padding size: 0x0000000C */
    RST_MASK0_T                                             rst_mask0; /* offset: 0x00000080, Reset Mask 0 Register */
    RST_MASK1_T                                             rst_mask1; /* offset: 0x00000084, Reset Mask 1 Register */
    uint32_t                                         __reserved_01[2]; /* offset: 0x00000088, padding size: 0x00000008 */
    RST_FUNC_CONT0_T                                   rst_func_cont0; /* offset: 0x00000090, Reset Fucntion Control Register */
    RST_FUNC_CONT1_T                                   rst_func_cont1; /* offset: 0x00000094, Reset Fucntion Control Register */
    uint32_t                                         __reserved_02[2]; /* offset: 0x00000098, padding size: 0x00000008 */
    RETN_FLAG0_T                                           retn_flag0; /* offset: 0x000000A0, Retention Flag 0 Register */
    RETN_FLAG1_T                                           retn_flag1; /* offset: 0x000000A4, Retention Flag 1 Register */
    RETN_FLAG2_T                                           retn_flag2; /* offset: 0x000000A8, Retention Flag 2 Register */
    RETN_FLAG3_T                                           retn_flag3; /* offset: 0x000000AC, Retention Flag 3 Register */
    RETN_FLAG4_T                                           retn_flag4; /* offset: 0x000000B0, Retention Flag 4 Register */
    RETN_FLAG5_T                                           retn_flag5; /* offset: 0x000000B4, Retention Flag 5 Register */
    uint32_t                                         __reserved_03[2]; /* offset: 0x000000B8, padding size: 0x00000008 */
    RETN_DAT0_T                                             retn_dat0; /* offset: 0x000000C0, Retention Data 0 Register */
    RETN_DAT1_T                                             retn_dat1; /* offset: 0x000000C4, Retention Data 1 Register */
    RETN_DAT2_T                                             retn_dat2; /* offset: 0x000000C8, Retention Data 2 Register */
    RETN_DAT3_T                                             retn_dat3; /* offset: 0x000000CC, Retention Data 3 Register */
    RETN_DAT4_T                                             retn_dat4; /* offset: 0x000000D0, Retention Data 4 Register */
    RETN_DAT5_T                                             retn_dat5; /* offset: 0x000000D4, Retention Data 5 Register */
    uint32_t                                         __reserved_04[2]; /* offset: 0x000000D8, padding size: 0x00000008 */
    PMU_TEST_SW_RST_T                                 pmu_test_sw_rst; /* offset: 0x000000E0, pmu testmode sw reset */
    uint32_t                                         __reserved_05[3]; /* offset: 0x000000E4, padding size: 0x0000000C */
    SW_RF_RST_T                                             sw_rf_rst; /* offset: 0x000000F0, Software Reset for rf Register */
    uint32_t                                         __reserved_06[3]; /* offset: 0x000000F4, padding size: 0x0000000C */
    RGU_DEBUG_SEL_T                                         debug_sel; /* offset: 0x00000100, debug select */
} RGU_MISC_REGISTER_T;
#define RGU_0       ((volatile RGU_REGISTER_T*)(RGU_BASE))
#define RGU         (RGU_0)

#ifdef CORE_MCU
    #if IS_ENABLED(CONFIG_AIR_WDT_2ND)
        #define RGU_1       ((volatile RGU_REGISTER_T*)(RGU_BASE + 0x30))
    #endif /* IS_ENABLED(CONFIG_AIR_WDT_2ND) */
#else
    #define RGU_1       ((volatile RGU_REGISTER_T*)(RGU_BASE + 0x30))
#endif /* CORE_MCU */

#define RGU_MISC    ((volatile RGU_MISC_REGISTER_T*)(RGU_BASE + 0x60))

#define WDT_EN_KEY                          (0x10)
#define WDT1_EN_KEY                         (0x40)

#define WDT_LENGTH_KEY                      (0x12)
#define WDT1_LENGTH_KEY                     (0x42)

#define WDT_INTERVAL_KEY                    (0x13)
#define WDT1_INTERVAL_KEY                   (0x43)

/* Bit definition for WDT_SW_RESTART Register */
#define WDT_SW_RESTART_KEY                  (0x1456789a)
#define WDT1_SW_RESTART_KEY                 (0x4456789a)

/* Bit definition for WDT_SW_RST Register */
#define WDT_SW_RST_KEY                      (0x156789ab)
#define WDT1_SW_RST_KEY                     (0x456789ab)

#define WDT_AUTO_RESTART_EN_KEY             (0x16)
#define WDT1_AUTO_RESTART_EN_KEY            (0x46)

#define WDT_IRQ_IE_KEY                      (0x18)
#define WDT1_IRQ_IE_KEY                     (0x48)

#define WDT_NMI_IE_KEY                      (0x17)
#define WDT1_NMI_IE_KEY                     (0x47)

#define WDT_WAKEUP_EN_KEY                   (0x19)
#define WDT1_WAKEUP_EN_KEY                  (0x49)

#define WDT_SW_RSTSYS_KEY                   (0x1A)
#define WDT_SW_RESET_RISCV_KEY               (0x1B)
#define WDT_CONNSYS_SW_RST_KEY              (0x1D)
#define WDT_AUDIOSYS_SW_RST_KEY             (0x1F)
#define WDT_USB_SW_RST_KEY                  (0x21)
#define WDT_USBIF_SW_RST_KEY                (0x22)
#define WDT_JTAG_MASK_SW_RST_KEY            (0x23)
#define WDT_AIRCR_MASK_SW_RST_KEY           (0x24)

#define WDT_EN_TEST_MODE_KEY                (0x11)
#define WDT_PMU_SW_RST_POLARITY_KEY         (0x28)
#define WDT_AIRCR_SW_RST_INTERVAL_KEY       (0x27)
#define WDT_PMU_MASK_SW_RST_KEY             (0x26)
#define WDT_PCM_MASK_SW_RST_KEY             (0x25)

#endif /*__RGU_REG_DEFINITION_H__*/
