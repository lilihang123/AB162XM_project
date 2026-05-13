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

#ifndef __RTC_TIMER_REG_DEFINITION_H__
#define __RTC_TIMER_REG_DEFINITION_H__


/* RTC control */
typedef union {
    struct {
        __IO uint32_t EN0                             :1;    /* bits:0-0, Enable RTC */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t MODE0                           :2;    /* bits:8-9, Operation mode of RTC */
        __I  uint32_t __reserved_01                   :6;
        __IO uint32_t SW_CG0                          :1;    /* bits:16-16, Enable the clock for RTC */
        __I  uint32_t __reserved_02                   :15;
    } field;
    __IO uint32_t word;
} RTC_CON_T;

#define RTC_CON_EN0_OFFSET                                            (0U)
#define RTC_CON_EN0_MASK                                              (0x1U << RTC_CON_EN0_OFFSET)
#define RTC_CON_MODE0_OFFSET                                          (8U)
#define RTC_CON_MODE0_MASK                                            (0x3U << RTC_CON_MODE0_OFFSET)
#define RTC_CON_SW_CG0_OFFSET                                         (16U)
#define RTC_CON_SW_CG0_MASK                                           (0x1U << RTC_CON_SW_CG0_OFFSET)


/* Clear RTC */
typedef union {
    struct {
        __IO uint32_t CLR0                            :1;    /* bits:0-0, Clear RTC */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} RTC_CLR_T;

#define RTC_CLR_CLR0_OFFSET                                           (0U)
#define RTC_CLR_CLR0_MASK                                             (0x1U << RTC_CLR_CLR0_OFFSET)


/* RTC clock setting */
typedef union {
    struct {
        __IO uint32_t CLK0                            :5;    /* bits:0-4, The clock source and the clock divider for RTC */
        __I  uint32_t __reserved_00                   :27;
    } field;
    __IO uint32_t word;
} RTC_CLK_T;

#define RTC_CLK_CLK0_OFFSET                                           (0U)
#define RTC_CLK_CLK0_MASK                                             (0x1FU << RTC_CLK_CLK0_OFFSET)


/* RTC IRQ enable */
typedef union {
    struct {
        __IO uint32_t IRQEN0                          :1;    /* bits:0-0, Enable the interrupt of RTC */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} RTC_IRQ_EN_T;

#define RTC_IRQ_EN_IRQEN0_OFFSET                                      (0U)
#define RTC_IRQ_EN_IRQEN0_MASK                                        (0x1U << RTC_IRQ_EN_IRQEN0_OFFSET)


/* RTC IRQ status */
typedef union {
    struct {
        __I  uint32_t IRQSTA0                         :1;    /* bits:0-0, Interrupt status of RTC */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} RTC_IRQ_STA_T;

#define RTC_IRQ_STA_IRQSTA0_OFFSET                                    (0U)
#define RTC_IRQ_STA_IRQSTA0_MASK                                      (0x1U << RTC_IRQ_STA_IRQSTA0_OFFSET)


/* RTC IRQ acknowledgement */
typedef union {
    struct {
        __IO uint32_t IRQACK0                         :1;    /* bits:0-0, Interrupt acknowledgement for RTC */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} RTC_IRQ_ACK_T;

#define RTC_IRQ_ACK_IRQACK0_OFFSET                                    (0U)
#define RTC_IRQ_ACK_IRQACK0_MASK                                      (0x1U << RTC_IRQ_ACK_IRQACK0_OFFSET)


/* RTC counter value */
typedef union {
    struct {
        __I  uint32_t COUNTER0                        :32;    /* bits:0-31, Counter value of RTC */
    } field;
    __IO uint32_t word;
} RTC_COUNT_T;

#define RTC_COUNT_COUNTER0_OFFSET                                     (0U)
#define RTC_COUNT_COUNTER0_MASK                                       (0xFFFFFFFFU << RTC_COUNT_COUNTER0_OFFSET)


/* RTC comparison value */
typedef union {
    struct {
        __IO uint32_t COMPARE0                        :32;    /* bits:0-31, Comparison value of RTC */
    } field;
    __IO uint32_t word;
} RTC_COMPARE_T;

#define RTC_COMPARE_COMPARE0_OFFSET                                   (0U)
#define RTC_COMPARE_COMPARE0_MASK                                     (0xFFFFFFFFU << RTC_COMPARE_COMPARE0_OFFSET)

typedef struct {
    RTC_CON_T                                           rtc_con; /* offset: 0x00000000, RTC control */
    RTC_CLR_T                                           rtc_clr; /* offset: 0x00000004, Clear RTC */
    RTC_CLK_T                                           rtc_clk; /* offset: 0x00000008, RTC clock setting */
    RTC_IRQ_EN_T                                     rtc_irq_en; /* offset: 0x0000000C, RTC IRQ enable */
    RTC_IRQ_STA_T                                   rtc_irq_sta; /* offset: 0x00000010, RTC IRQ status */
    RTC_IRQ_ACK_T                                   rtc_irq_ack; /* offset: 0x00000014, RTC IRQ acknowledgement */
    RTC_COUNT_T                                       rtc_count; /* offset: 0x00000018, RTC counter value */
    RTC_COMPARE_T                                   rtc_compare; /* offset: 0x0000001C, RTC comparison value */
    uint32_t                                        __reserved_00[56]; /* offset: 0x00000020, padding size: 0x000000E0 */
}RTC_CONFIG_T; 

/* RTC_T IRQ status */
typedef union {
    struct {
        __I  uint32_t IRQSTA                          :3;    /* bits:0-2, Interrupt status of each RTC_T */
        __I  uint32_t __reserved_00                   :29;
    } field;
    __IO uint32_t word;
} RTC_T_IRQSTA_T;

#define RTC_T_IRQSTA_IRQSTA_OFFSET                                       (0U)
#define RTC_T_IRQSTA_IRQSTA_MASK                                         (0x7U << RTC_T_IRQSTA_IRQSTA_OFFSET)


/* RTC_T IRQ mask for CM33 */
typedef union {
    struct {
        __IO uint32_t IRQMASK0                        :3;    /* bits:0-2, CM33 IRQ mask of each RTC_T */
        __I  uint32_t __reserved_00                   :29;
    } field;
    __IO uint32_t word;
} RTC_T_IRQMASK0_T;

#define RTC_T_IRQMASK0_IRQMASK0_OFFSET                                   (0U)
#define RTC_T_IRQMASK0_IRQMASK0_MASK                                     (0x7U << RTC_T_IRQMASK0_IRQMASK0_OFFSET)


/* RTC_T IRQ mask for RISCV */
typedef union {
    struct {
        __IO uint32_t IRQMASK1                        :3;    /* bits:0-2, RISCV IRQ mask of each RTC_T */
        __I  uint32_t __reserved_00                   :29;
    } field;
    __IO uint32_t word;
} RTC_T_IRQMASK1_T;

#define RTC_T_IRQMASK1_IRQMASK1_OFFSET                                   (0U)
#define RTC_T_IRQMASK1_IRQMASK1_MASK                                     (0x7U << RTC_T_IRQMASK1_IRQMASK1_OFFSET)


/* RTC_T wake up mask for CM33 */
typedef union {
    struct {
        __IO uint32_t EVENTMASK0                      :3;    /* bits:0-2, CM33 wake up mask of each RTC_T */
        __I  uint32_t __reserved_00                   :29;
    } field;
    __IO uint32_t word;
} RTC_T_WAKEUPMASK0_T;

#define RTC_T_WAKEUPMASK0_EVENTMASK0_OFFSET                              (0U)
#define RTC_T_WAKEUPMASK0_EVENTMASK0_MASK                                (0x7U << RTC_T_WAKEUPMASK0_EVENTMASK0_OFFSET)


/* RTC_T wake up mask for RISCV */
typedef union {
    struct {
        __IO uint32_t EVENTMASK1                      :3;    /* bits:0-2, RISCV wake up mask of each RTC_T */
        __I  uint32_t __reserved_00                   :29;
    } field;
    __IO uint32_t word;
} RTC_T_WAKEUPMASK1_T;

#define RTC_T_WAKEUPMASK1_EVENTMASK1_OFFSET                              (0U)
#define RTC_T_WAKEUPMASK1_EVENTMASK1_MASK                                (0x7U << RTC_T_WAKEUPMASK1_EVENTMASK1_OFFSET)


/* RTC_T clear status */
typedef union {
    struct {
        __I  uint32_t CLRSTA                          :3;    /* bits:0-2, Clear each RTC_T status */
        __I  uint32_t __reserved_00                   :29;
    } field;
    __IO uint32_t word;
} RTC_T_CLRSTA_T;

#define RTC_T_CLRSTA_CLRSTA_OFFSET                                       (0U)
#define RTC_T_CLRSTA_CLRSTA_MASK                                         (0x7U << RTC_T_CLRSTA_CLRSTA_OFFSET)


/* RTC_T write comparison value status */
typedef union {
    struct {
        __I  uint32_t WCOMPSTA                        :3;    /* bits:0-2, Write the comparison value status of each RTC_T */
        __I  uint32_t __reserved_00                   :29;
    } field;
    __IO uint32_t word;
} RTC_T_WCOMPSTA_T;

#define RTC_T_WCOMPSTA_WCOMPSTA_OFFSET                                   (0U)
#define RTC_T_WCOMPSTA_WCOMPSTA_MASK                                     (0x7U << RTC_T_WCOMPSTA_WCOMPSTA_OFFSET)


typedef struct {
    RTC_CONFIG_T                                        rtc_config[2]; /* offset: 0x00000000, RTC configuration register */
    uint32_t                                       __reserved_02[320]; /* offset: 0x00000220, padding size: 0x000005E0 */
    RTC_T_IRQSTA_T                                       rtc_t_irqsta; /* offset: 0x00000700, RTC_T IRQ status */
    RTC_T_IRQMASK0_T                                   rtc_t_irqmask0; /* offset: 0x00000704, RTC_T IRQ mask for CM33 */
    RTC_T_IRQMASK1_T                                   rtc_t_irqmask1; /* offset: 0x00000708, RTC_T IRQ mask for RISCV */
    RTC_T_WAKEUPMASK0_T                             rtc_t_wakeupmask0; /* offset: 0x0000070C, RTC_T wake up mask for CM33 */
    RTC_T_WAKEUPMASK1_T                             rtc_t_wakeupmask1; /* offset: 0x00000710, RTC_T wake up mask for RISCV */
    RTC_T_CLRSTA_T                                       rtc_t_clrsta; /* offset: 0x00000714, RTC_T clear status */
    RTC_T_WCOMPSTA_T                                   rtc_t_wcompsta; /* offset: 0x00000718, RTC_T write comparison value status */
    uint32_t                                        __reserved_03[57]; /* offset: 0x00000800, padding size: 0x000000E4 */
    RTC_CONFIG_T                                        rtc_ao_config; /* offset: 0x00000800, RTC AO configuration register */
    uint32_t                                       __reserved_04[384];/* offset: 0x00000F00, padding size: 0x000000600 */
    RTC_T_IRQSTA_T                                    rtc_ao_t_irqsta; /* offset: 0x00000F00, RTC_AO_T IRQ status */
    RTC_T_IRQMASK0_T                                 rtc_ao_t_irqmask0; /* offset: 0x00000F04, RTC_AO_T IRQ mask for CM33 */
    RTC_T_IRQMASK1_T                                 rtc_ao_t_irqmask1; /* offset: 0x00000F08, RTC_AO_T IRQ mask for RISCV */
    RTC_T_WAKEUPMASK0_T                           rtc_ao_t_wakeupmask0; /* offset: 0x00000F0C, RTC_AO_T wake up mask for CM33 */
    RTC_T_WAKEUPMASK1_T                           rtc_ao_t_wakeupmask1; /* offset: 0x00000F10, RTC_AO_T wake up mask for RISCV */
    RTC_T_CLRSTA_T                                     rtc_ao_t_clrsta; /* offset: 0x00000F14, RTC_AO_T clear status */
    RTC_T_WCOMPSTA_T                                 rtc_ao_t_wcompsta; /* offset: 0x00000F18, RTC_AO_T write comparison value status */
} RTC_TIMER_REGISTER_T;


#endif /*__RTC_TIMER_REG_DEFINITION_H__*/
