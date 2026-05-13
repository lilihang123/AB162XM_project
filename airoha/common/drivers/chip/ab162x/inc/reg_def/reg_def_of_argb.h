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

#ifndef __ARGB_REG_DEFINITION_H__
#define __ARGB_REG_DEFINITION_H__


/* DMA global status */
typedef union {
    struct {
        __I  uint32_t RUN_TX                          :1;    /* bits:0-0, Channel TX running status */
        __I  uint32_t IT_TX                           :1;    /* bits:1-1, Channel TX interrupt status */
        __I  uint32_t RUN_RX                          :1;    /* bits:2-2, Channel RX running status */
        __I  uint32_t IT_RX                           :1;    /* bits:3-3, Channel RX interrupt status */
        __I  uint32_t __reserved_00                   :28;
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLBSTA_T;

#define ARGB_DMA_GLBSTA_RUN_TX_OFFSET                                         (0U)
#define ARGB_DMA_GLBSTA_RUN_TX_MASK                                           (0x1U << ARGB_DMA_GLBSTA_RUN_TX_OFFSET)
#define ARGB_DMA_GLBSTA_IT_TX_OFFSET                                          (1U)
#define ARGB_DMA_GLBSTA_IT_TX_MASK                                            (0x1U << ARGB_DMA_GLBSTA_IT_TX_OFFSET)
#define ARGB_DMA_GLBSTA_RUN_RX_OFFSET                                         (2U)
#define ARGB_DMA_GLBSTA_RUN_RX_MASK                                           (0x1U << ARGB_DMA_GLBSTA_RUN_RX_OFFSET)
#define ARGB_DMA_GLBSTA_IT_RX_OFFSET                                          (3U)
#define ARGB_DMA_GLBSTA_IT_RX_MASK                                            (0x1U << ARGB_DMA_GLBSTA_IT_RX_OFFSET)


/* DMA top hierarchy interrupt config */
typedef union {
    struct {
        __I  uint32_t CPU0_CFG_TX                     :1;    /* bits:0-0, Channel TX CPU0 interrupt enable configure */
        __I  uint32_t CPU0_CFG_RX                     :1;    /* bits:1-1, Channel RX CPU0 interrupt enable configure */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLB_CPU0_CFG_T;

#define ARGB_DMA_GLB_CPU0_CFG_CPU0_CFG_TX_OFFSET                              (0U)
#define ARGB_DMA_GLB_CPU0_CFG_CPU0_CFG_TX_MASK                                (0x1U << ARGB_DMA_GLB_CPU0_CFG_CPU0_CFG_TX_OFFSET)
#define ARGB_DMA_GLB_CPU0_CFG_CPU0_CFG_RX_OFFSET                              (1U)
#define ARGB_DMA_GLB_CPU0_CFG_CPU0_CFG_RX_MASK                                (0x1U << ARGB_DMA_GLB_CPU0_CFG_CPU0_CFG_RX_OFFSET)


/* DMA top hierarchy interrupt set */
typedef union {
    struct {
        __IO uint32_t CPU0_SET_TX                     :1;    /* bits:0-0, Channel TX CPU0 interrupt enable set */
        __IO uint32_t CPU0_SET_RX                     :1;    /* bits:1-1, Channel RX CPU0 interrupt enable set */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLB_CPU0_SET_T;

#define ARGB_DMA_GLB_CPU0_SET_CPU0_SET_TX_OFFSET                              (0U)
#define ARGB_DMA_GLB_CPU0_SET_CPU0_SET_TX_MASK                                (0x1U << ARGB_DMA_GLB_CPU0_SET_CPU0_SET_TX_OFFSET)
#define ARGB_DMA_GLB_CPU0_SET_CPU0_SET_RX_OFFSET                              (1U)
#define ARGB_DMA_GLB_CPU0_SET_CPU0_SET_RX_MASK                                (0x1U << ARGB_DMA_GLB_CPU0_SET_CPU0_SET_RX_OFFSET)


/* DMA top hierarchy interrupt clr */
typedef union {
    struct {
        __IO uint32_t CPU0_CLR_TX                     :1;    /* bits:0-0, Channel TX CPU0 interrupt enable clear */
        __IO uint32_t CPU0_CLR_RX                     :1;    /* bits:1-1, Channel RX CPU0 interrupt enable clear */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLB_CPU0_CLR_T;

#define ARGB_DMA_GLB_CPU0_CLR_CPU0_CLR_TX_OFFSET                              (0U)
#define ARGB_DMA_GLB_CPU0_CLR_CPU0_CLR_TX_MASK                                (0x1U << ARGB_DMA_GLB_CPU0_CLR_CPU0_CLR_TX_OFFSET)
#define ARGB_DMA_GLB_CPU0_CLR_CPU0_CLR_RX_OFFSET                              (1U)
#define ARGB_DMA_GLB_CPU0_CLR_CPU0_CLR_RX_MASK                                (0x1U << ARGB_DMA_GLB_CPU0_CLR_CPU0_CLR_RX_OFFSET)


/* DMA top hierarchy interrupt config */
typedef union {
    struct {
        __I  uint32_t CPU1_CFG_TX                     :1;    /* bits:0-0, Channel TX CPU1 interrupt enable configure */
        __I  uint32_t CPU1_CFG_RX                     :1;    /* bits:1-1, Channel RX CPU1 interrupt enable configure */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLB_CPU1_CFG_T;

#define ARGB_DMA_GLB_CPU1_CFG_CPU1_CFG_TX_OFFSET                              (0U)
#define ARGB_DMA_GLB_CPU1_CFG_CPU1_CFG_TX_MASK                                (0x1U << ARGB_DMA_GLB_CPU1_CFG_CPU1_CFG_TX_OFFSET)
#define ARGB_DMA_GLB_CPU1_CFG_CPU1_CFG_RX_OFFSET                              (1U)
#define ARGB_DMA_GLB_CPU1_CFG_CPU1_CFG_RX_MASK                                (0x1U << ARGB_DMA_GLB_CPU1_CFG_CPU1_CFG_RX_OFFSET)


/* DMA top hierarchy interrupt set */
typedef union {
    struct {
        __IO uint32_t CPU1_SET_TX                     :1;    /* bits:0-0, Channel TX CPU1 interrupt enable set */
        __IO uint32_t CPU1_SET_RX                     :1;    /* bits:1-1, Channel RX CPU1 interrupt enable set */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLB_CPU1_SET_T;

#define ARGB_DMA_GLB_CPU1_SET_CPU1_SET_TX_OFFSET                              (0U)
#define ARGB_DMA_GLB_CPU1_SET_CPU1_SET_TX_MASK                                (0x1U << ARGB_DMA_GLB_CPU1_SET_CPU1_SET_TX_OFFSET)
#define ARGB_DMA_GLB_CPU1_SET_CPU1_SET_RX_OFFSET                              (1U)
#define ARGB_DMA_GLB_CPU1_SET_CPU1_SET_RX_MASK                                (0x1U << ARGB_DMA_GLB_CPU1_SET_CPU1_SET_RX_OFFSET)


/* DMA top hierarchy interrupt clr */
typedef union {
    struct {
        __IO uint32_t CPU1_CLR_TX                     :1;    /* bits:0-0, Channel TX CPU1 interrupt enable clear */
        __IO uint32_t CPU1_CLR_RX                     :1;    /* bits:1-1, Channel RX CPU1 interrupt enable clear */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLB_CPU1_CLR_T;

#define ARGB_DMA_GLB_CPU1_CLR_CPU1_CLR_TX_OFFSET                              (0U)
#define ARGB_DMA_GLB_CPU1_CLR_CPU1_CLR_TX_MASK                                (0x1U << ARGB_DMA_GLB_CPU1_CLR_CPU1_CLR_TX_OFFSET)
#define ARGB_DMA_GLB_CPU1_CLR_CPU1_CLR_RX_OFFSET                              (1U)
#define ARGB_DMA_GLB_CPU1_CLR_CPU1_CLR_RX_MASK                                (0x1U << ARGB_DMA_GLB_CPU1_CLR_CPU1_CLR_RX_OFFSET)


/* DMA global software reset */
typedef union {
    struct {
        __I  uint32_t SW_RESET                        :1;    /* bits:0-0, Software reset write 1 reset */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLB_SWRST_T;

#define ARGB_DMA_GLB_SWRST_SW_RESET_OFFSET                                    (0U)
#define ARGB_DMA_GLB_SWRST_SW_RESET_MASK                                      (0x1U << ARGB_DMA_GLB_SWRST_SW_RESET_OFFSET)


/* DMA global bandwidth limiter register */
typedef union {
    struct {
        __IO uint32_t LIMITER                         :8;    /* bits:0-7, Utilization suppression This register suppresses the bus utilization of the DMA channel.  From 0 to 255. 0 means no limitation, 255 means totally banned. All other values indicate bus access permission for every (4 x n) AHB clock. */
        __I  uint32_t __reserved_00                   :24;
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLBLIMITER_T;

#define ARGB_DMA_GLBLIMITER_LIMITER_OFFSET                                    (0U)
#define ARGB_DMA_GLBLIMITER_LIMITER_MASK                                      (0xFFU << ARGB_DMA_GLBLIMITER_LIMITER_OFFSET)


/* DMA current chosen channel */
typedef union {
    struct {
        __I  uint32_t CC                              :32;    /* bits:0-31, Reserved for debug only. This signal indicates the channel that is currently be chosen. */
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLB_DBG_T;

#define ARGB_DMA_GLB_DBG_CC_OFFSET                                            (0U)
#define ARGB_DMA_GLB_DBG_CC_MASK                                              (0xFFFFFFFFU << ARGB_DMA_GLB_DBG_CC_OFFSET)


/* DMA global busy status */
typedef union {
    struct {
        __I  uint32_t RUN_TX                          :1;    /* bits:0-0, Channel TX running status IT will pull high after RUN pulling down in the same channel */
        __I  uint32_t RUN_RX                          :1;    /* bits:1-1, Channel RX running status IT will pull high after RUN pulling down in the same channel */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLB_BUSY_T;

#define ARGB_DMA_GLB_BUSY_RUN_TX_OFFSET                                       (0U)
#define ARGB_DMA_GLB_BUSY_RUN_TX_MASK                                         (0x1U << ARGB_DMA_GLB_BUSY_RUN_TX_OFFSET)
#define ARGB_DMA_GLB_BUSY_RUN_RX_OFFSET                                       (1U)
#define ARGB_DMA_GLB_BUSY_RUN_RX_MASK                                         (0x1U << ARGB_DMA_GLB_BUSY_RUN_RX_OFFSET)


/* DMA global interrupt status */
typedef union {
    struct {
        __I  uint32_t IT_TX                           :1;    /* bits:0-0, Channel TX interrupt status IT will pull high after RUN pulling down in the same channel */
        __I  uint32_t IT_RX                           :1;    /* bits:1-1, Channel RX interrupt status IT will pull high after RUN pulling down in the same channel */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLB_INTR_T;

#define ARGB_DMA_GLB_INTR_IT_TX_OFFSET                                        (0U)
#define ARGB_DMA_GLB_INTR_IT_TX_MASK                                          (0x1U << ARGB_DMA_GLB_INTR_IT_TX_OFFSET)
#define ARGB_DMA_GLB_INTR_IT_RX_OFFSET                                        (1U)
#define ARGB_DMA_GLB_INTR_IT_RX_MASK                                          (0x1U << ARGB_DMA_GLB_INTR_IT_RX_OFFSET)


/* DMA top hierarchy interrupt config */
typedef union {
    struct {
        __I  uint32_t CPU2_CFG1                       :1;    /* bits:0-0, Channel 1 CPU2 interrupt enable configure */
        __I  uint32_t CPU2_CFG2                       :1;    /* bits:1-1, Channel 2 CPU2 interrupt enable configure */
        __I  uint32_t CPU2_CFG3                       :1;    /* bits:2-2, Channel 3 CPU2 interrupt enable configure */
        __I  uint32_t CPU2_CFG4                       :1;    /* bits:3-3, Channel 4 CPU2 interrupt enable configure */
        __I  uint32_t CPU2_CFG5                       :1;    /* bits:4-4, Channel 5 CPU2 interrupt enable configure */
        __I  uint32_t CPU2_CFG6                       :1;    /* bits:5-5, Channel 6 CPU2 interrupt enable configure */
        __I  uint32_t CPU2_CFG7                       :1;    /* bits:6-6, Channel 7 CPU2 interrupt enable configure */
        __I  uint32_t __reserved_00                   :25;
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLB_CPU2_CFG_T;

#define ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG1_OFFSET                                (0U)
#define ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG1_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG1_OFFSET)
#define ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG2_OFFSET                                (1U)
#define ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG2_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG2_OFFSET)
#define ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG3_OFFSET                                (2U)
#define ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG3_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG3_OFFSET)
#define ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG4_OFFSET                                (3U)
#define ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG4_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG4_OFFSET)
#define ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG5_OFFSET                                (4U)
#define ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG5_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG5_OFFSET)
#define ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG6_OFFSET                                (5U)
#define ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG6_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG6_OFFSET)
#define ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG7_OFFSET                                (6U)
#define ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG7_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_CFG_CPU2_CFG7_OFFSET)


/* DMA top hierarchy interrupt set */
typedef union {
    struct {
        __IO uint32_t CPU2_SET1                       :1;    /* bits:0-0, Channel 1 CPU2 interrupt enable set */
        __IO uint32_t CPU2_SET2                       :1;    /* bits:1-1, Channel 2 CPU2 interrupt enable set */
        __IO uint32_t CPU2_SET3                       :1;    /* bits:2-2, Channel 3 CPU2 interrupt enable set */
        __IO uint32_t CPU2_SET4                       :1;    /* bits:3-3, Channel 4 CPU2 interrupt enable set */
        __IO uint32_t CPU2_SET5                       :1;    /* bits:4-4, Channel 5 CPU2 interrupt enable set */
        __IO uint32_t CPU2_SET6                       :1;    /* bits:5-5, Channel 6 CPU2 interrupt enable set */
        __IO uint32_t CPU2_SET7                       :1;    /* bits:6-6, Channel 7 CPU2 interrupt enable set */
        __I  uint32_t __reserved_00                   :25;
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLB_CPU2_SET_T;

#define ARGB_DMA_GLB_CPU2_SET_CPU2_SET1_OFFSET                                (0U)
#define ARGB_DMA_GLB_CPU2_SET_CPU2_SET1_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_SET_CPU2_SET1_OFFSET)
#define ARGB_DMA_GLB_CPU2_SET_CPU2_SET2_OFFSET                                (1U)
#define ARGB_DMA_GLB_CPU2_SET_CPU2_SET2_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_SET_CPU2_SET2_OFFSET)
#define ARGB_DMA_GLB_CPU2_SET_CPU2_SET3_OFFSET                                (2U)
#define ARGB_DMA_GLB_CPU2_SET_CPU2_SET3_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_SET_CPU2_SET3_OFFSET)
#define ARGB_DMA_GLB_CPU2_SET_CPU2_SET4_OFFSET                                (3U)
#define ARGB_DMA_GLB_CPU2_SET_CPU2_SET4_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_SET_CPU2_SET4_OFFSET)
#define ARGB_DMA_GLB_CPU2_SET_CPU2_SET5_OFFSET                                (4U)
#define ARGB_DMA_GLB_CPU2_SET_CPU2_SET5_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_SET_CPU2_SET5_OFFSET)
#define ARGB_DMA_GLB_CPU2_SET_CPU2_SET6_OFFSET                                (5U)
#define ARGB_DMA_GLB_CPU2_SET_CPU2_SET6_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_SET_CPU2_SET6_OFFSET)
#define ARGB_DMA_GLB_CPU2_SET_CPU2_SET7_OFFSET                                (6U)
#define ARGB_DMA_GLB_CPU2_SET_CPU2_SET7_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_SET_CPU2_SET7_OFFSET)


/* DMA top hierarchy interrupt clr */
typedef union {
    struct {
        __IO uint32_t CPU2_CLR1                       :1;    /* bits:0-0, Channel 1 CPU2 interrupt enable clear */
        __IO uint32_t CPU2_CLR2                       :1;    /* bits:1-1, Channel 2 CPU2 interrupt enable clear */
        __IO uint32_t CPU2_CLR3                       :1;    /* bits:2-2, Channel 3 CPU2 interrupt enable clear */
        __IO uint32_t CPU2_CLR4                       :1;    /* bits:3-3, Channel 4 CPU2 interrupt enable clear */
        __IO uint32_t CPU2_CLR5                       :1;    /* bits:4-4, Channel 5 CPU2 interrupt enable clear */
        __IO uint32_t CPU2_CLR6                       :1;    /* bits:5-5, Channel 6 CPU2 interrupt enable clear */
        __IO uint32_t CPU2_CLR7                       :1;    /* bits:6-6, Channel 7 CPU2 interrupt enable clear */
        __I  uint32_t __reserved_00                   :25;
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLB_CPU2_CLR_T;

#define ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR1_OFFSET                                (0U)
#define ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR1_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR1_OFFSET)
#define ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR2_OFFSET                                (1U)
#define ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR2_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR2_OFFSET)
#define ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR3_OFFSET                                (2U)
#define ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR3_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR3_OFFSET)
#define ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR4_OFFSET                                (3U)
#define ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR4_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR4_OFFSET)
#define ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR5_OFFSET                                (4U)
#define ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR5_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR5_OFFSET)
#define ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR6_OFFSET                                (5U)
#define ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR6_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR6_OFFSET)
#define ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR7_OFFSET                                (6U)
#define ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR7_MASK                                  (0x1U << ARGB_DMA_GLB_CPU2_CLR_CPU2_CLR7_OFFSET)


/* DMA top hierarchy interrupt config */
typedef union {
    struct {
        __I  uint32_t CPU3_CFG1                       :1;    /* bits:0-0, Channel 1 CPU3 interrupt enable configure */
        __I  uint32_t CPU3_CFG2                       :1;    /* bits:1-1, Channel 2 CPU3 interrupt enable configure */
        __I  uint32_t CPU3_CFG3                       :1;    /* bits:2-2, Channel 3 CPU3 interrupt enable configure */
        __I  uint32_t CPU3_CFG4                       :1;    /* bits:3-3, Channel 4 CPU3 interrupt enable configure */
        __I  uint32_t CPU3_CFG5                       :1;    /* bits:4-4, Channel 5 CPU3 interrupt enable configure */
        __I  uint32_t CPU3_CFG6                       :1;    /* bits:5-5, Channel 6 CPU3 interrupt enable configure */
        __I  uint32_t CPU3_CFG7                       :1;    /* bits:6-6, Channel 7 CPU3 interrupt enable configure */
        __I  uint32_t __reserved_00                   :25;
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLB_CPU3_CFG_T;

#define ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG1_OFFSET                                (0U)
#define ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG1_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG1_OFFSET)
#define ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG2_OFFSET                                (1U)
#define ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG2_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG2_OFFSET)
#define ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG3_OFFSET                                (2U)
#define ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG3_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG3_OFFSET)
#define ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG4_OFFSET                                (3U)
#define ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG4_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG4_OFFSET)
#define ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG5_OFFSET                                (4U)
#define ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG5_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG5_OFFSET)
#define ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG6_OFFSET                                (5U)
#define ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG6_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG6_OFFSET)
#define ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG7_OFFSET                                (6U)
#define ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG7_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_CFG_CPU3_CFG7_OFFSET)


/* DMA top hierarchy interrupt set */
typedef union {
    struct {
        __IO uint32_t CPU3_SET1                       :1;    /* bits:0-0, Channel 1 CPU3 interrupt enable set */
        __IO uint32_t CPU3_SET2                       :1;    /* bits:1-1, Channel 2 CPU3 interrupt enable set */
        __IO uint32_t CPU3_SET3                       :1;    /* bits:2-2, Channel 3 CPU3 interrupt enable set */
        __IO uint32_t CPU3_SET4                       :1;    /* bits:3-3, Channel 4 CPU3 interrupt enable set */
        __IO uint32_t CPU3_SET5                       :1;    /* bits:4-4, Channel 5 CPU3 interrupt enable set */
        __IO uint32_t CPU3_SET6                       :1;    /* bits:5-5, Channel 6 CPU3 interrupt enable set */
        __IO uint32_t CPU3_SET7                       :1;    /* bits:6-6, Channel 7 CPU3 interrupt enable set */
        __I  uint32_t __reserved_00                   :25;
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLB_CPU3_SET_T;

#define ARGB_DMA_GLB_CPU3_SET_CPU3_SET1_OFFSET                                (0U)
#define ARGB_DMA_GLB_CPU3_SET_CPU3_SET1_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_SET_CPU3_SET1_OFFSET)
#define ARGB_DMA_GLB_CPU3_SET_CPU3_SET2_OFFSET                                (1U)
#define ARGB_DMA_GLB_CPU3_SET_CPU3_SET2_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_SET_CPU3_SET2_OFFSET)
#define ARGB_DMA_GLB_CPU3_SET_CPU3_SET3_OFFSET                                (2U)
#define ARGB_DMA_GLB_CPU3_SET_CPU3_SET3_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_SET_CPU3_SET3_OFFSET)
#define ARGB_DMA_GLB_CPU3_SET_CPU3_SET4_OFFSET                                (3U)
#define ARGB_DMA_GLB_CPU3_SET_CPU3_SET4_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_SET_CPU3_SET4_OFFSET)
#define ARGB_DMA_GLB_CPU3_SET_CPU3_SET5_OFFSET                                (4U)
#define ARGB_DMA_GLB_CPU3_SET_CPU3_SET5_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_SET_CPU3_SET5_OFFSET)
#define ARGB_DMA_GLB_CPU3_SET_CPU3_SET6_OFFSET                                (5U)
#define ARGB_DMA_GLB_CPU3_SET_CPU3_SET6_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_SET_CPU3_SET6_OFFSET)
#define ARGB_DMA_GLB_CPU3_SET_CPU3_SET7_OFFSET                                (6U)
#define ARGB_DMA_GLB_CPU3_SET_CPU3_SET7_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_SET_CPU3_SET7_OFFSET)


/* DMA top hierarchy interrupt clr */
typedef union {
    struct {
        __IO uint32_t CPU3_CLR1                       :1;    /* bits:0-0, Channel 1 CPU3 interrupt enable clear */
        __IO uint32_t CPU3_CLR2                       :1;    /* bits:1-1, Channel 2 CPU3 interrupt enable clear */
        __IO uint32_t CPU3_CLR3                       :1;    /* bits:2-2, Channel 3 CPU3 interrupt enable clear */
        __IO uint32_t CPU3_CLR4                       :1;    /* bits:3-3, Channel 4 CPU3 interrupt enable clear */
        __IO uint32_t CPU3_CLR5                       :1;    /* bits:4-4, Channel 5 CPU3 interrupt enable clear */
        __IO uint32_t CPU3_CLR6                       :1;    /* bits:5-5, Channel 6 CPU3 interrupt enable clear */
        __IO uint32_t CPU3_CLR7                       :1;    /* bits:6-6, Channel 7 CPU3 interrupt enable clear */
        __I  uint32_t __reserved_00                   :25;
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLB_CPU3_CLR_T;

#define ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR1_OFFSET                                (0U)
#define ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR1_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR1_OFFSET)
#define ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR2_OFFSET                                (1U)
#define ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR2_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR2_OFFSET)
#define ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR3_OFFSET                                (2U)
#define ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR3_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR3_OFFSET)
#define ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR4_OFFSET                                (3U)
#define ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR4_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR4_OFFSET)
#define ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR5_OFFSET                                (4U)
#define ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR5_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR5_OFFSET)
#define ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR6_OFFSET                                (5U)
#define ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR6_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR6_OFFSET)
#define ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR7_OFFSET                                (6U)
#define ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR7_MASK                                  (0x1U << ARGB_DMA_GLB_CPU3_CLR_CPU3_CLR7_OFFSET)


/* DMA channel clock config */
typedef union {
    struct {
        __I  uint32_t CLK_CFG_TX                      :1;    /* bits:0-0, Channel TX clock enable configure */
        __I  uint32_t CLK_CFG_RX                      :1;    /* bits:1-1, Channel RX clock enable configure */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLB_CLK_CFG_T;

#define ARGB_DMA_GLB_CLK_CFG_CLK_CFG_TX_OFFSET                                (0U)
#define ARGB_DMA_GLB_CLK_CFG_CLK_CFG_TX_MASK                                  (0x1U << ARGB_DMA_GLB_CLK_CFG_CLK_CFG_TX_OFFSET)
#define ARGB_DMA_GLB_CLK_CFG_CLK_CFG_RX_OFFSET                                (1U)
#define ARGB_DMA_GLB_CLK_CFG_CLK_CFG_RX_MASK                                  (0x1U << ARGB_DMA_GLB_CLK_CFG_CLK_CFG_RX_OFFSET)


/* DMA channel clock set */
typedef union {
    struct {
        __IO uint32_t CLK_SET_TX                      :1;    /* bits:0-0, Channel TX clock enable set */
        __IO uint32_t CLK_SET_RX                      :1;    /* bits:1-1, Channel RX clock enable set */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLB_CLK_SET_T;

#define ARGB_DMA_GLB_CLK_SET_CLK_SET_TX_OFFSET                                (0U)
#define ARGB_DMA_GLB_CLK_SET_CLK_SET_TX_MASK                                  (0x1U << ARGB_DMA_GLB_CLK_SET_CLK_SET_TX_OFFSET)
#define ARGB_DMA_GLB_CLK_SET_CLK_SET_RX_OFFSET                                (1U)
#define ARGB_DMA_GLB_CLK_SET_CLK_SET_RX_MASK                                  (0x1U << ARGB_DMA_GLB_CLK_SET_CLK_SET_RX_OFFSET)


/* DMA channel clock clr */
typedef union {
    struct {
        __IO uint32_t CLK_CLR_TX                      :1;    /* bits:0-0, Channel TX clock enable clear */
        __IO uint32_t CLK_CLR_RX                      :1;    /* bits:1-1, Channel RX clock enable clear */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} ARGB_DMA_GLB_CLK_CLR_T;

#define ARGB_DMA_GLB_CLK_CLR_CLK_CLR_TX_OFFSET                                (0U)
#define ARGB_DMA_GLB_CLK_CLR_CLK_CLR_TX_MASK                                  (0x1U << ARGB_DMA_GLB_CLK_CLR_CLK_CLR_TX_OFFSET)
#define ARGB_DMA_GLB_CLK_CLR_CLK_CLR_RX_OFFSET                                (1U)
#define ARGB_DMA_GLB_CLK_CLR_CLK_CLR_RX_MASK                                  (0x1U << ARGB_DMA_GLB_CLK_CLR_CLK_CLR_RX_OFFSET)


/* DMA channel TX wrap point address */
typedef union {
    struct {
        __IO uint32_t WPPT                            :16;    /* bits:0-15, Transfer counts before jump The register specifies the transfer count that is necessary to perform before the jump point. This can be used to support the ring buffer or double buffer style memory access. To enable this function, two control bits in the DMA control register (WPEN and WPSD) must be programmed. If the transfer counter in the DMA engine is the same as this value, an address jump occurs, and the next address is the address specified in PDMAn_WPTO. To enable this function, set WPEN in PDMAn_CON. Note: the total size of data specified in the wrap point count in a DMA channel is determined by LEN and the SIZE in PDMAn_CON (i.e. WPPT x SIZE). */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} ARGB_PDMA_TX_WPPT_T;

#define ARGB_PDMA_TX_WPPT_WPPT_OFFSET                                         (0U)
#define ARGB_PDMA_TX_WPPT_WPPT_MASK                                           (0xFFFFU << ARGB_PDMA_TX_WPPT_WPPT_OFFSET)


/* DMA channel TX wrap to address */
typedef union {
    struct {
        __IO uint32_t WPTO                            :32;    /* bits:0-31, Jump address The register specifies the address of jump destination of a given DMA transfer to support the ring buffer or double buffer style memory access. To enable this function, set the two control bits in the DMA control register, WPEN and WPSD . To enable this function, WPEN in PDMAn_CON must be set. */
    } field;
    __IO uint32_t word;
} ARGB_PDMA_TX_WPTO_T;

#define ARGB_PDMA_TX_WPTO_WPTO_OFFSET                                         (0U)
#define ARGB_PDMA_TX_WPTO_WPTO_MASK                                           (0xFFFFFFFFU << ARGB_PDMA_TX_WPTO_WPTO_OFFSET)


/* DMA channel TX transfer count */
typedef union {
    struct {
        __IO uint32_t COUNT                           :16;    /* bits:0-15, The amount of total transfer counts This register specifies the amount of total transfer counts the DMA channel must perform. When complete, the DMA channel generates an interrupt request for the processor while ITEN in PDMAn_CON is set to 1. Note: the total size of data transferred by a DMA channel is determined by LEN and the SIZE in PDMAn_CON (i.e. LEN x SIZE). */
        __IO uint32_t PKTCNT                          :8;    /* bits:16-23, The amount of total transfer packet counts This register specifies the amount of total transfer packet counts the DMA channel must perform. After complete, the DMA channel set address back to PGMADDR when start. (For Auto Mode Only) */
        __I  uint32_t __reserved_00                   :8;
    } field;
    __IO uint32_t word;
} ARGB_PDMA_TX_COUNT_T;

#define ARGB_PDMA_TX_COUNT_COUNT_OFFSET                                       (0U)
#define ARGB_PDMA_TX_COUNT_COUNT_MASK                                         (0xFFFFU << ARGB_PDMA_TX_COUNT_COUNT_OFFSET)
#define ARGB_PDMA_TX_COUNT_PKTCNT_OFFSET                                      (16U)
#define ARGB_PDMA_TX_COUNT_PKTCNT_MASK                                        (0xFFU << ARGB_PDMA_TX_COUNT_PKTCNT_OFFSET)


/* DMA channel TX control */
typedef union {
    struct {
        __IO uint32_t DIRECTION                       :5;    /* bits:0-4, [0] Incremental source address. The source addresses increment every transfer. If the setting of SIZE is byte, the source addresses will increase by 1 every single transfer. If half-word, it will increase by 2; and if word, increase by 4. [1] Incremental destination address.  The destination addresses increases each transfer. If the setting of SIZE is in bytes, the destination addresses will increase by 1 for each  transfer. If half-word, it will increase by 2; and if word, increase by 4. [2] Wrap select: The side using address-wrapping function. Only one side of a DMA channel can activate the address-wrapping function at a time. [3] Wrap enable: Address-wrapping for ring buffer and double buffer. The next address of DMA jumps to WRAP TO address when the current address matches WRAP POINT count. [4] Directions of PDMA transfer The direction is from the perspective of the DMA masters. WRITE means reading from master and then writing to the address specified in PDMAn_PGMADDR, and vice versa. No effect on channel 1. */
        __I  uint32_t __reserved_00                   :3;
        __IO uint32_t SIZE                            :2;    /* bits:8-9, Data size of a bus cycle per transfer. These bits restrict the data transfer size between the source and destination to the specified value for one bus cycle. The size is measured in bytes, and the maximum value is 4 bytes. It is mainly decided by the data width of a DMA master. */
        __I  uint32_t __reserved_01                   :6;
        __IO uint32_t SETTING                         :4;    /* bits:16-19, [16] Throttle and handshake control for DMA transfer.  The DMA master can throttle down the transfer rate by the request-grant handshake. [17] Byte to word Word-to-byte or byte-to-word transfer for the application of transferring non-word-aligned-address data to word-aligned-address data. Note: BURST must be set to 4-beat burst and the SIZE is set to byte to enable this function. [19:18] Transfer type.  Burst-type transfers have better bus efficiency. We recommend using this type of transfer for mass data movement. Note: the burst-type transfer does not stop until all of the beats in a burst are complete, or the transfer length is reached. The available transfer types are limited by the SIZE. If SIZE is 00b (i.e. byte transfer), all four transfer types can be used. If SIZE is 01b (i.e. half-word transfer), 16-beat incremental burst cannot be used. If SIZE is 10b (i.e. word transfer), only single and 4-beat incremental burst can be used. */
        __I  uint32_t __reserved_02                   :4;
        __IO uint32_t ITEN                            :1;    /* bits:24-24, Enable DMA transfer completion interrupt */
        __I  uint32_t __reserved_03                   :7;
    } field;
    __IO uint32_t word;
} ARGB_PDMA_TX_CON_T;

#define ARGB_PDMA_TX_CON_DIRECTION_OFFSET                                     (0U)
#define ARGB_PDMA_TX_CON_DIRECTION_MASK                                       (0x1FU << ARGB_PDMA_TX_CON_DIRECTION_OFFSET)
#define ARGB_PDMA_TX_CON_SIZE_OFFSET                                          (8U)
#define ARGB_PDMA_TX_CON_SIZE_MASK                                            (0x3U << ARGB_PDMA_TX_CON_SIZE_OFFSET)
#define ARGB_PDMA_TX_CON_SETTING_OFFSET                                       (16U)
#define ARGB_PDMA_TX_CON_SETTING_MASK                                         (0xFU << ARGB_PDMA_TX_CON_SETTING_OFFSET)
#define ARGB_PDMA_TX_CON_ITEN_OFFSET                                          (24U)
#define ARGB_PDMA_TX_CON_ITEN_MASK                                            (0x1U << ARGB_PDMA_TX_CON_ITEN_OFFSET)


/* DMA channel TX start */
typedef union {
    struct {
        __I  uint32_t __reserved_00                   :15;
        __IO uint32_t STR                             :1;    /* bits:15-15, Start control for a DMA channel This register controls the activity of a DMA channel. Note that before setting STR to 1, all register settings must be configured. When STR is set to 1, the hardware will not clear it automatically, no matter whether the DMA channel accomplishes the DMA transfer or not. In other words, the value of STR stays at 1, regardless of the completion of the DMA transfer. Therefore, the software program must reset STR to 0 before starting another DMA transfer. If this bit is cleared to 0 when the DMA transfer is active, the software must poll RUNn in ARGB_DMA_GLBSTA when this bit is cleared to make sure that the current DMA transfer is terminated by the DMA engine. */
        __I  uint32_t __reserved_01                   :16;
    } field;
    __IO uint32_t word;
} ARGB_PDMA_TX_START_T;

#define ARGB_PDMA_TX_START_STR_OFFSET                                         (15U)
#define ARGB_PDMA_TX_START_STR_MASK                                           (0x1U << ARGB_PDMA_TX_START_STR_OFFSET)


/* DMA channel TX interrupt status */
typedef union {
    struct {
        __I  uint32_t __reserved_00                   :15;
        __I  uint32_t INT                             :1;    /* bits:15-15, Interrupt status for DMA channel */
        __I  uint32_t __reserved_01                   :16;
    } field;
    __IO uint32_t word;
} ARGB_PDMA_TX_INTSTA_T;

#define ARGB_PDMA_TX_INTSTA_INT_OFFSET                                        (15U)
#define ARGB_PDMA_TX_INTSTA_INT_MASK                                          (0x1U << ARGB_PDMA_TX_INTSTA_INT_OFFSET)


/* DMA channel TX interrupt acknowledge */
typedef union {
    struct {
        __I  uint32_t __reserved_00                   :15;
        __IO uint32_t ACK                             :1;    /* bits:15-15, Interrupt acknowledge for the DMA channel */
        __I  uint32_t __reserved_01                   :16;
    } field;
    __IO uint32_t word;
} ARGB_PDMA_TX_ACKINT_T;

#define ARGB_PDMA_TX_ACKINT_ACK_OFFSET                                        (15U)
#define ARGB_PDMA_TX_ACKINT_ACK_MASK                                          (0x1U << ARGB_PDMA_TX_ACKINT_ACK_OFFSET)


/* DMA channel TX remaining length of current transfer */
typedef union {
    struct {
        __I  uint32_t RLCT                            :16;    /* bits:0-15, This register shows the remaining count of the transfer.  Note: this value is transfer count, not the transfer data size. */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} ARGB_PDMA_TX_RLCT_T;

#define ARGB_PDMA_TX_RLCT_RLCT_OFFSET                                         (0U)
#define ARGB_PDMA_TX_RLCT_RLCT_MASK                                           (0xFFFFU << ARGB_PDMA_TX_RLCT_RLCT_OFFSET)


/* DMA channel TX bandwidth limiter */
typedef union {
    struct {
        __IO uint32_t LIMITER                         :8;    /* bits:0-7, Utilization suppression This register controls the suppression of the bus utilization of the DMA channel.  From 0 to 255. 0 means no limitation, 255 means totally banned. All other values show bus access permission for every (4 x n) AHB clock. */
        __I  uint32_t __reserved_00                   :24;
    } field;
    __IO uint32_t word;
} ARGB_PDMA_TX_LIMITER_T;

#define ARGB_PDMA_TX_LIMITER_LIMITER_OFFSET                                   (0U)
#define ARGB_PDMA_TX_LIMITER_LIMITER_MASK                                     (0xFFU << ARGB_PDMA_TX_LIMITER_LIMITER_OFFSET)


/* DMA channel TX programmable address */
typedef union {
    struct {
        __IO uint32_t PGMADDR                         :32;    /* bits:0-31, PDMA programmable address. These registers specify the address for a half-size DMA channel. This address represents the source address if DIR in ARGB_DMA_CON is set to 0 and represents the destination address if DIR in PDMAn_CON is set to 1. */
    } field;
    __IO uint32_t word;
} ARGB_PDMA_TX_PGMADDR_T;

#define ARGB_PDMA_TX_PGMADDR_PGMADDR_OFFSET                                   (0U)
#define ARGB_PDMA_TX_PGMADDR_PGMADDR_MASK                                     (0xFFFFFFFFU << ARGB_PDMA_TX_PGMADDR_PGMADDR_OFFSET)


/* ARGB Control 0 */
typedef union {
    struct {
        __IO uint32_t ONE_L_VAL                       :8;    /* bits:0-7, No. of clock  count value for ARGB Send One Low */
        __IO uint32_t ONE_H_VAL                       :8;    /* bits:8-15, No. of clock  count value for ARGB Send One High */
        __IO uint32_t ZERO_L_VAL                      :8;    /* bits:16-23, No. of clock  count value for ARGB Send Zero Low */
        __IO uint32_t ZERO_H_VAL                      :8;    /* bits:24-31, No. of clock  count value for ARGB Send Zero High */
    } field;
    __IO uint32_t word;
} ARGB_CTRL0_T;

#define ARGB_CTRL0_ONE_L_VAL_OFFSET                                      (0U)
#define ARGB_CTRL0_ONE_L_VAL_MASK                                        (0xFFU << ARGB_CTRL0_ONE_L_VAL_OFFSET)
#define ARGB_CTRL0_ONE_H_VAL_OFFSET                                      (8U)
#define ARGB_CTRL0_ONE_H_VAL_MASK                                        (0xFFU << ARGB_CTRL0_ONE_H_VAL_OFFSET)
#define ARGB_CTRL0_ZERO_L_VAL_OFFSET                                     (16U)
#define ARGB_CTRL0_ZERO_L_VAL_MASK                                       (0xFFU << ARGB_CTRL0_ZERO_L_VAL_OFFSET)
#define ARGB_CTRL0_ZERO_H_VAL_OFFSET                                     (24U)
#define ARGB_CTRL0_ZERO_H_VAL_MASK                                       (0xFFU << ARGB_CTRL0_ZERO_H_VAL_OFFSET)


/* ARGB Control 1 */
typedef union {
    struct {
        __IO uint32_t RST_VAL                         :16;    /* bits:0-15, No. of clock count value for ARGB Send Reset Pattern */
        __IO uint32_t PAT_CNT                         :8;    /* bits:16-23, Pattern Count (for each packet) This count means that how many ARGB LED we want to control */
        __I  uint32_t __reserved_00                   :1;
        __IO uint32_t ED_BIG                          :1;    /* bits:25-25, Data Endian for Nonalign mode */
        __IO uint32_t NONALIGN                        :1;    /* bits:26-26, Pattern nonalign mode Since the AMBA bus is 32bit, the ARGB data pattern is 24 bit. We support 32bit to 24bit data transfer mode and this mode name is 'nonalign'. Beside, if we set this RG to 0x0, it means that we will drop data bit 31 to 24 form AMBA bus. */
        __IO uint32_t BIT_NONREV                      :1;    /* bits:27-27, Bit non-reverse mode */
        __IO uint32_t CLK_DIV                         :2;    /* bits:28-29, Clock Divider for ARGB Controller */
        __I  uint32_t __reserved_01                   :1;
        __IO uint32_t EN_ARGB                         :1;    /* bits:31-31, Enable ARGB Controller */
    } field;
    __IO uint32_t word;
} ARGB_CTRL1_T;

#define ARGB_CTRL1_RST_VAL_OFFSET                                        (0U)
#define ARGB_CTRL1_RST_VAL_MASK                                          (0xFFFFU << ARGB_CTRL1_RST_VAL_OFFSET)
#define ARGB_CTRL1_PAT_CNT_OFFSET                                        (16U)
#define ARGB_CTRL1_PAT_CNT_MASK                                          (0xFFU << ARGB_CTRL1_PAT_CNT_OFFSET)
#define ARGB_CTRL1_ED_BIG_OFFSET                                         (25U)
#define ARGB_CTRL1_ED_BIG_MASK                                           (0x1U << ARGB_CTRL1_ED_BIG_OFFSET)
#define ARGB_CTRL1_NONALIGN_OFFSET                                       (26U)
#define ARGB_CTRL1_NONALIGN_MASK                                         (0x1U << ARGB_CTRL1_NONALIGN_OFFSET)
#define ARGB_CTRL1_BIT_NONREV_OFFSET                                     (27U)
#define ARGB_CTRL1_BIT_NONREV_MASK                                       (0x1U << ARGB_CTRL1_BIT_NONREV_OFFSET)
#define ARGB_CTRL1_CLK_DIV_OFFSET                                        (28U)
#define ARGB_CTRL1_CLK_DIV_MASK                                          (0x3U << ARGB_CTRL1_CLK_DIV_OFFSET)
#define ARGB_CTRL1_EN_ARGB_OFFSET                                        (31U)
#define ARGB_CTRL1_EN_ARGB_MASK                                          (0x1U << ARGB_CTRL1_EN_ARGB_OFFSET)


/* ARGB Interrupt Status */
typedef union {
    struct {
        __IO uint32_t ARGB_STOP_INT_STS               :1;    /* bits:0-0, ARGB Controller Stop Interrupt Status */
        __IO uint32_t RST_ST_INT_STS                  :1;    /* bits:1-1, ARGB Controller Reset Start Interrupt Status */
        __IO uint32_t AUTO_RE_ST_INT_STS              :1;    /* bits:2-2, ARGB Controller Auto Mode Re-Start Interrupt Status */
        __IO uint32_t PR_WK_INT_STS                   :1;    /* bits:3-3, ARGB Controller Auto Mode Pre-Wakeup Interrupt Status */
        __IO uint32_t ARGB_DMA_ST_INT_STS                  :1;    /* bits:4-4, ARGB Controller Auto Mode DMA Start Interrupt Status */
        __IO uint32_t AUTO_OFF_INT_STS                :1;    /* bits:5-5, ARGB Controller Auto Mode OFF Interrupt Status */
        __IO uint32_t ARGB_DMA_LVL_INT_STS                 :1;    /* bits:6-6, ARGB Controller DMA LVL Interrupt Status */
        __I  uint32_t __reserved_00                   :25;
    } field;
    __IO uint32_t word;
} ARGB_INTR_STS_T;

#define ARGB_INTR_STS_ARGB_STOP_INT_STS_OFFSET                           (0U)
#define ARGB_INTR_STS_ARGB_STOP_INT_STS_MASK                             (0x1U << ARGB_INTR_STS_ARGB_STOP_INT_STS_OFFSET)
#define ARGB_INTR_STS_RST_ST_INT_STS_OFFSET                              (1U)
#define ARGB_INTR_STS_RST_ST_INT_STS_MASK                                (0x1U << ARGB_INTR_STS_RST_ST_INT_STS_OFFSET)
#define ARGB_INTR_STS_AUTO_RE_ST_INT_STS_OFFSET                          (2U)
#define ARGB_INTR_STS_AUTO_RE_ST_INT_STS_MASK                            (0x1U << ARGB_INTR_STS_AUTO_RE_ST_INT_STS_OFFSET)
#define ARGB_INTR_STS_PR_WK_INT_STS_OFFSET                               (3U)
#define ARGB_INTR_STS_PR_WK_INT_STS_MASK                                 (0x1U << ARGB_INTR_STS_PR_WK_INT_STS_OFFSET)
#define ARGB_INTR_STS_ARGB_DMA_ST_INT_STS_OFFSET                              (4U)
#define ARGB_INTR_STS_ARGB_DMA_ST_INT_STS_MASK                                (0x1U << ARGB_INTR_STS_ARGB_DMA_ST_INT_STS_OFFSET)
#define ARGB_INTR_STS_AUTO_OFF_INT_STS_OFFSET                            (5U)
#define ARGB_INTR_STS_AUTO_OFF_INT_STS_MASK                              (0x1U << ARGB_INTR_STS_AUTO_OFF_INT_STS_OFFSET)
#define ARGB_INTR_STS_ARGB_DMA_LVL_INT_STS_OFFSET                             (6U)
#define ARGB_INTR_STS_ARGB_DMA_LVL_INT_STS_MASK                               (0x1U << ARGB_INTR_STS_ARGB_DMA_LVL_INT_STS_OFFSET)

/* ARGB Interrupt Mask */
typedef union {
    struct {
        __IO uint32_t ARGB_STOP_INT_MSK               :1;    /* bits:0-0, ARGB Controller Stop Interrupt Mask */
        __IO uint32_t RST_ST_INT_MSK                  :1;    /* bits:1-1, ARGB Controller Reset Start Interrupt Mask */
        __IO uint32_t AUTO_RE_ST_INT_MSK              :1;    /* bits:2-2, ARGB Controller Auto Mode Re-Start Interrupt Mask */
        __IO uint32_t PR_WK_INT_MSK                   :1;    /* bits:3-3, ARGB Controller Auto Mode Pre-Wakeup Interrupt Mask */
        __IO uint32_t ARGB_DMA_ST_INT_MSK                  :1;    /* bits:4-4, ARGB Controller Auto Mode DMA Start Interrupt Mask */
        __IO uint32_t AUTO_OFF_INT_MSK                :1;    /* bits:5-5, ARGB Controller Auto Mode OFF Interrupt Mask */
        __IO uint32_t ARGB_DMA_LVL_INT_MSK                 :1;    /* bits:5-5, ARGB Controller DMA  LVL Interrupt Mask */
        __I  uint32_t __reserved_00                   :25;
    } field;
    __IO uint32_t word;
} ARGB_INTR_MSK_T;

#define ARGB_INTR_MSK_ARGB_STOP_INT_MSK_OFFSET                           (0U)
#define ARGB_INTR_MSK_ARGB_STOP_INT_MSK_MASK                             (0x1U << ARGB_INTR_MSK_ARGB_STOP_INT_MSK_OFFSET)
#define ARGB_INTR_MSK_RST_ST_INT_MSK_OFFSET                              (1U)
#define ARGB_INTR_MSK_RST_ST_INT_MSK_MASK                                (0x1U << ARGB_INTR_MSK_RST_ST_INT_MSK_OFFSET)
#define ARGB_INTR_MSK_AUTO_RE_ST_INT_MSK_OFFSET                          (2U)
#define ARGB_INTR_MSK_AUTO_RE_ST_INT_MSK_MASK                            (0x1U << ARGB_INTR_MSK_AUTO_RE_ST_INT_MSK_OFFSET)
#define ARGB_INTR_MSK_PR_WK_INT_MSK_OFFSET                               (3U)
#define ARGB_INTR_MSK_PR_WK_INT_MSK_MASK                                 (0x1U << ARGB_INTR_MSK_PR_WK_INT_MSK_OFFSET)
#define ARGB_INTR_MSK_ARGB_DMA_ST_INT_MSK_OFFSET                              (4U)
#define ARGB_INTR_MSK_ARGB_DMA_ST_INT_MSK_MASK                                (0x1U << ARGB_INTR_MSK_ARGB_DMA_ST_INT_MSK_OFFSET)
#define ARGB_INTR_MSK_AUTO_OFF_INT_MSK_OFFSET                            (5U)
#define ARGB_INTR_MSK_AUTO_OFF_INT_MSK_MASK                              (0x1U << ARGB_INTR_MSK_AUTO_OFF_INT_MSK_OFFSET)
#define ARGB_INTR_MSK_ARGB_DMA_LVL_INT_MSK_OFFSET                             (6U)
#define ARGB_INTR_MSK_ARGB_DMA_LVL_INT_MSK_MASK                               (0x1U << ARGB_INTR_MSK_ARGB_DMA_LVL_INT_MSK_OFFSET)

/* ARGB FIFO Pattern_In */
typedef union {
    struct {
        __IO uint32_t FIFO_WR_PORT                    :24;    /* bits:0-23, FIFO Write Data Port */
        __I  uint32_t __reserved_00                   :8;
    } field;
    __IO uint32_t word;
} ARGB_PATT_T;

#define ARGB_PATT_FIFO_WR_PORT_OFFSET                                    (0U)
#define ARGB_PATT_FIFO_WR_PORT_MASK                                      (0xFFFFFFU << ARGB_PATT_FIFO_WR_PORT_OFFSET)


/* ARGB Auto Timer Mode Control */
typedef union {
    struct {
        __IO uint32_t AUTO_MODE                       :1;    /* bits:0-0, Start ARGB Auto Mode */
        __I  uint32_t __reserved_00                   :15;
        __IO uint32_t STOP_CNT                        :16;    /* bits:16-31, Self Stop Count No. of Count to Stop the ARGB Auto Mode */
    } field;
    __IO uint32_t word;
} ARGB_TCTRL_T;

#define ARGB_TCTRL_AUTO_MODE_OFFSET                                      (0U)
#define ARGB_TCTRL_AUTO_MODE_MASK                                        (0x1U << ARGB_TCTRL_AUTO_MODE_OFFSET)
#define ARGB_TCTRL_STOP_CNT_OFFSET                                       (16U)
#define ARGB_TCTRL_STOP_CNT_MASK                                         (0xFFFFU << ARGB_TCTRL_STOP_CNT_OFFSET)


/* ARGB Auto Timer Set */
typedef union {
    struct {
        __IO uint32_t AUTO_TIMER_VAL                  :24;    /* bits:0-23, Timer Setting Value for ARGB Auto Mode No. of clock  count value for ARGB Auto Mode Timer */
        __I  uint32_t __reserved_00                   :8;
    } field;
    __IO uint32_t word;
} ARGB_TIMER_T;

#define ARGB_TIMER_AUTO_TIMER_VAL_OFFSET                                 (0U)
#define ARGB_TIMER_AUTO_TIMER_VAL_MASK                                   (0xFFFFFFU << ARGB_TIMER_AUTO_TIMER_VAL_OFFSET)


/* ARGB PreWakeup Set */
typedef union {
    struct {
        __IO uint32_t PR_WAKE_VAL                     :24;    /* bits:0-23, PreWake Setting Value for ARGB Auto Mode No. of clock  count value for ARGB Auto Mode PreWake Interrupt */
        __I  uint32_t __reserved_00                   :8;
    } field;
    __IO uint32_t word;
} ARGB_PREWK_T;

#define ARGB_PREWK_PR_WAKE_VAL_OFFSET                                    (0U)
#define ARGB_PREWK_PR_WAKE_VAL_MASK                                      (0xFFFFFFU << ARGB_PREWK_PR_WAKE_VAL_OFFSET)


/* ARGB DMA Start Set */
typedef union {
    struct {
        __IO uint32_t ARGB_DMA_ST_VAL                      :24;    /* bits:0-23, DMA Start Setting Value for ARGB Auto Mode No. of clock  count value for ARGB Auto Mode to triggle DMA Auto Start */
        __I  uint32_t __reserved_00                   :8;
    } field;
    __IO uint32_t word;
} ARGB_DMAST_T;

#define ARGB_DMAST_ARGB_DMA_ST_VAL_OFFSET                                     (0U)
#define ARGB_DMAST_ARGB_DMA_ST_VAL_MASK                                       (0xFFFFFFU << ARGB_DMAST_ARGB_DMA_ST_VAL_OFFSET)


/* ARGB Auto Mode Packet Count */
typedef union {
    struct {
        __IO uint32_t ARGB_PKT_CNT                    :16;    /* bits:0-15, PKT Sending Counter for ARGB Auto Mode No. of PKT had been send by ARGB module */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} ARGB_PKTCNT_T;

#define ARGB_PKTCNT_ARGB_PKT_CNT_OFFSET                                  (0U)
#define ARGB_PKTCNT_ARGB_PKT_CNT_MASK                                    (0xFFFFU << ARGB_PKTCNT_ARGB_PKT_CNT_OFFSET)


/* ARGB Debug 0 */
typedef union {
    struct {
        __I  uint32_t FIFO_LEVEL                      :11;    /* bits:0-10, empty description */
        __I  uint32_t __reserved_00                   :3;
        __I  uint32_t FIFO_EMPTY                      :1;    /* bits:14-14, empty description */
        __I  uint32_t FIFO_FULL                       :1;    /* bits:15-15, empty description */
        __I  uint32_t __reserved_01                   :16;
    } field;
    __IO uint32_t word;
} ARGB_DBG0_T;

#define ARGB_DBG0_FIFO_LEVEL_OFFSET                                      (0U)
#define ARGB_DBG0_FIFO_LEVEL_MASK                                        (0x7FFU << ARGB_DBG0_FIFO_LEVEL_OFFSET)
#define ARGB_DBG0_FIFO_EMPTY_OFFSET                                      (14U)
#define ARGB_DBG0_FIFO_EMPTY_MASK                                        (0x1U << ARGB_DBG0_FIFO_EMPTY_OFFSET)
#define ARGB_DBG0_FIFO_FULL_OFFSET                                       (15U)
#define ARGB_DBG0_FIFO_FULL_MASK                                         (0x1U << ARGB_DBG0_FIFO_FULL_OFFSET)


/* ARGB Debug 1 */
typedef union {
    struct {
        __I  uint32_t TIMER_STATE                     :3;    /* bits:0-2, empty description */
        __I  uint32_t ARGB_AUTO_MODE_EN               :1;    /* bits:3-3, empty description */
        __I  uint32_t __reserved_00                   :28;
    } field;
    __IO uint32_t word;
} ARGB_DBG1_T;

#define ARGB_DBG1_TIMER_STATE_OFFSET                                     (0U)
#define ARGB_DBG1_TIMER_STATE_MASK                                       (0x7U << ARGB_DBG1_TIMER_STATE_OFFSET)
#define ARGB_DBG1_ARGB_AUTO_MODE_EN_OFFSET                               (3U)
#define ARGB_DBG1_ARGB_AUTO_MODE_EN_MASK                                 (0x1U << ARGB_DBG1_ARGB_AUTO_MODE_EN_OFFSET)


typedef struct {
    ARGB_DMA_GLBSTA_T                                           dma_glbsta; /* offset: 0x00000000, DMA global status */
    uint32_t                                         __reserved_00[1]; /* offset: 0x00000004, padding size: 0x00000004 */
    ARGB_DMA_GLB_CPU0_CFG_T                               dma_glb_cpu0_cfg; /* offset: 0x00000008, DMA top hierarchy interrupt config */
    ARGB_DMA_GLB_CPU0_SET_T                               dma_glb_cpu0_set; /* offset: 0x0000000C, DMA top hierarchy interrupt set */
    ARGB_DMA_GLB_CPU0_CLR_T                               dma_glb_cpu0_clr; /* offset: 0x00000010, DMA top hierarchy interrupt clr */
    ARGB_DMA_GLB_CPU1_CFG_T                               dma_glb_cpu1_cfg; /* offset: 0x00000014, DMA top hierarchy interrupt config */
    ARGB_DMA_GLB_CPU1_SET_T                               dma_glb_cpu1_set; /* offset: 0x00000018, DMA top hierarchy interrupt set */
    ARGB_DMA_GLB_CPU1_CLR_T                               dma_glb_cpu1_clr; /* offset: 0x0000001C, DMA top hierarchy interrupt clr */
    ARGB_DMA_GLB_SWRST_T                                     dma_glb_swrst; /* offset: 0x00000020, DMA global software reset */
    uint32_t                                         __reserved_01[1]; /* offset: 0x00000024, padding size: 0x00000004 */
    ARGB_DMA_GLBLIMITER_T                                   dma_glblimiter; /* offset: 0x00000028, DMA global bandwidth limiter register */
    uint32_t                                         __reserved_02[1]; /* offset: 0x0000002C, padding size: 0x00000004 */
    ARGB_DMA_GLB_DBG_T                                         dma_glb_dbg; /* offset: 0x00000030, DMA current chosen channel */
    uint32_t                                         __reserved_03[3]; /* offset: 0x00000034, padding size: 0x0000000C */
    ARGB_DMA_GLB_BUSY_T                                       dma_glb_busy; /* offset: 0x00000040, DMA global busy status */
    ARGB_DMA_GLB_INTR_T                                       dma_glb_intr; /* offset: 0x00000044, DMA global interrupt status */
    uint32_t                                         __reserved_04[2]; /* offset: 0x00000048, padding size: 0x00000008 */
    ARGB_DMA_GLB_CPU2_CFG_T                               dma_glb_cpu2_cfg; /* offset: 0x00000050, DMA top hierarchy interrupt config */
    ARGB_DMA_GLB_CPU2_SET_T                               dma_glb_cpu2_set; /* offset: 0x00000054, DMA top hierarchy interrupt set */
    ARGB_DMA_GLB_CPU2_CLR_T                               dma_glb_cpu2_clr; /* offset: 0x00000058, DMA top hierarchy interrupt clr */
    uint32_t                                         __reserved_05[1]; /* offset: 0x0000005C, padding size: 0x00000004 */
    ARGB_DMA_GLB_CPU3_CFG_T                               dma_glb_cpu3_cfg; /* offset: 0x00000060, DMA top hierarchy interrupt config */
    ARGB_DMA_GLB_CPU3_SET_T                               dma_glb_cpu3_set; /* offset: 0x00000064, DMA top hierarchy interrupt set */
    ARGB_DMA_GLB_CPU3_CLR_T                               dma_glb_cpu3_clr; /* offset: 0x00000068, DMA top hierarchy interrupt clr */
    uint32_t                                         __reserved_06[1]; /* offset: 0x0000006C, padding size: 0x00000004 */
    ARGB_DMA_GLB_CLK_CFG_T                                 dma_glb_clk_cfg; /* offset: 0x00000070, DMA channel clock config */
    ARGB_DMA_GLB_CLK_SET_T                                 dma_glb_clk_set; /* offset: 0x00000074, DMA channel clock set */
    ARGB_DMA_GLB_CLK_CLR_T                                 dma_glb_clk_clr; /* offset: 0x00000078, DMA channel clock clr */
    uint32_t                                        __reserved_07[35]; /* offset: 0x0000007C, padding size: 0x0000008C */
    ARGB_PDMA_TX_WPPT_T                                       pdma_tx_wppt; /* offset: 0x00000108, DMA channel TX wrap point address */
    ARGB_PDMA_TX_WPTO_T                                       pdma_tx_wpto; /* offset: 0x0000010C, DMA channel TX wrap to address */
    ARGB_PDMA_TX_COUNT_T                                     pdma_tx_count; /* offset: 0x00000110, DMA channel TX transfer count */
    ARGB_PDMA_TX_CON_T                                         pdma_tx_con; /* offset: 0x00000114, DMA channel TX control */
    ARGB_PDMA_TX_START_T                                     pdma_tx_start; /* offset: 0x00000118, DMA channel TX start */
    ARGB_PDMA_TX_INTSTA_T                                   pdma_tx_intsta; /* offset: 0x0000011C, DMA channel TX interrupt status */
    ARGB_PDMA_TX_ACKINT_T                                   pdma_tx_ackint; /* offset: 0x00000120, DMA channel TX interrupt acknowledge */
    ARGB_PDMA_TX_RLCT_T                                       pdma_tx_rlct; /* offset: 0x00000124, DMA channel TX remaining length of current transfer */
    ARGB_PDMA_TX_LIMITER_T                                 pdma_tx_limiter; /* offset: 0x00000128, DMA channel TX bandwidth limiter */
    ARGB_PDMA_TX_PGMADDR_T                                 pdma_tx_pgmaddr; /* offset: 0x0000012C, DMA channel TX programmable address */
    uint32_t                                        __reserved_08[54]; /* offset: 0x00000130, padding size: 0x000000D8 */
    ARGB_CTRL0_T                                                ctrl0; /* offset: 0x00000208, ARGB Control 0 */
    ARGB_CTRL1_T                                                ctrl1; /* offset: 0x0000020C, ARGB Control 1 */
    ARGB_INTR_STS_T                                          intr_sts; /* offset: 0x00000210, ARGB Interrupt Status */
    ARGB_INTR_MSK_T                                          intr_msk; /* offset: 0x00000214, ARGB Interrupt Mask */
    ARGB_PATT_T                                                  patt; /* offset: 0x00000218, ARGB FIFO Pattern_In */
    uint32_t                                         __reserved_09[1]; /* offset: 0x0000021C, padding size: 0x00000004 */
    ARGB_TCTRL_T                                                tctrl; /* offset: 0x00000220, ARGB Auto Timer Mode Control */
    ARGB_TIMER_T                                                timer; /* offset: 0x00000224, ARGB Auto Timer Set */
    ARGB_PREWK_T                                                prewk; /* offset: 0x00000228, ARGB PreWakeup Set */
    ARGB_DMAST_T                                                dmast; /* offset: 0x0000022C, ARGB DMA Start Set */
    ARGB_PKTCNT_T                                              pktcnt; /* offset: 0x00000230, ARGB Auto Mode Packet Count */
    uint32_t                                        __reserved_10[11]; /* offset: 0x00000234, padding size: 0x0000002C */
    ARGB_DBG0_T                                                  dbg0; /* offset: 0x00000260, ARGB Debug 0 */
    ARGB_DBG1_T                                                  dbg1; /* offset: 0x00000264, ARGB Debug 1 */
} ARGB_REGISTER_T;

#define ARGB_CLOCK_FREQUENCY     26000000 /* 32Mhz */
#endif /*__ARGB_REG_DEFINITION_H__*/
