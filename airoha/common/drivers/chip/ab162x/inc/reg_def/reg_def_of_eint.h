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

#ifndef __EINT_REG_DEFINITION_H__
#define __EINT_REG_DEFINITION_H__

#include <stdint.h>
/*************************** EINT definition start line  *******************************/
#define EINT_NUMBER_MAX 48   /*!< The eint max number--support gpio 0-47*/
#define EINT_BASE 0x42140000 /*External Interrupts*/

typedef union
{
    struct
    {
        uint8_t DBC_CON[2]; /*!< bit 0-14: DBC_CON - debounce duration in terms of the number of 32768Hz clock cycles,
                                                      cycle length is determinded by PRESCALER*/
        uint8_t DBC_EN;     /*!< bit 16: DBC_EN - enable debounce */
        uint8_t RSTDBC;     /*!< bit 24: RSTDBC - reset the de-bounce counter */
    } EINT_CON_CELLS;
    uint32_t EINT_CON;
} EINT_CON_UNION;

typedef struct
{
    __IO uint32_t EINT_SENS[2];                             /*!< 0x0000 EINT sensitivitity register */
    __IO uint32_t EINT_DUALEDGE[2];                         /*!< 0x0008 EINT dual edge sensitivity register*/
    __IO uint32_t EINT_POL[2];                              /*!< 0x0010 EINT polarity register*/
    __IO EINT_CON_UNION EINT_CON_REGISTER[EINT_NUMBER_MAX]; /*!< 0x0018~0x00D4 EINT config register */
    __IO uint32_t EINT_TIMER_SEL[10];                       /*!< 0x00D8~0x00FC Timer will record which EINTx selectr*/
    __IO uint32_t EINT_COUNTER_CTRL;                        /*!< 0x0100 EINT internal counter control */
    __IO uint32_t EINT_D0EN[2];                             /*!< 0x0104 EINT CM33 domain enable register */
    __IO uint32_t EINT_D1EN[2];                             /*!< 0x010C EINT RISCV domain enable register */
    __IO uint32_t EINT_MASK[2];                             /*!< 0x0114 EINT interrupt mask register */
    __IO uint32_t EINT_WAKEUP_MASK[2];                      /*!< 0x011C EINT wakeup event mask register */
    __IO uint32_t EINT_ENABLE[2];                           /*!< 0x0124 EINT trigger result enable register */
    __IO uint32_t EINT_TOGGLE[2];                           /*!< 0x012C EINT TOGGLE register */
    __I uint32_t RESERVED0[51];                             /*!< 0x012c~0x01FC Reserved */
    __IO uint32_t EINT_INTACK[2];  /*!< 0x0200 EINT interrupt acknowledge register */
    __IO uint32_t EINT_EEVTACK[2]; /*!< 0x0208 EINT wakeup event acknowledge register */
    __IO uint32_t EINT_SOFT[2];    /*!< 0x0210 EINT software interrupt register */
    __I uint32_t RESERVED1[58];    /*!< 0x0218~0x02FC Reserved */

    __IO uint32_t EINT_STA[2];     /*!< 0x0300 EINT interrupt status register */
    __IO uint32_t EINT_EEVT[2];    /*!< 0x0308 EINT EINT wakeup event status register */
    __IO uint32_t EINT_DBC_OUT[2]; /*!< 0x0310 EINT pass through the debounce circuit out */
    __I uint32_t RESERVED2[58];    /*!< 0x0318~0x03FC Reserved */

    __IO uint32_t EINT_SENS_SET[2];        /*!< 0x0400 EINT sensitivity set register */
    __IO uint32_t EINT_SENS_CLR[2];        /*!< 0x0408 EINT sensitivity clear register */
    __IO uint32_t EINT_DUALEDGE_SET[2];    /*!< 0x0410 EINT dual edge sensitivity set register */
    __IO uint32_t EINT_DUALEDGE_CLR[2];    /*!< 0x0418 EINT dual edge sensitivity clear register*/
    __IO uint32_t EINT_POL_SET[2];         /*!< 0x0420 EINT polarity set register */
    __IO uint32_t EINT_POL_CLR[2];         /*!< 0x0428 EINT polarity clear register */
    __IO uint32_t EINT_D0EN_SET[2];        /*!< 0x0430 EINT CM33 domain enable set register */
    __IO uint32_t EINT_D0EN_CLR[2];        /*!< 0x0438 EINT CM33 domain enable clear register */
    __IO uint32_t EINT_D1EN_SET[2];        /*!< 0x0440 EINT RISCV domain enable set register */
    __IO uint32_t EINT_D1EN_CLR[2];        /*!< 0x0448 EINT RISCV domain enable clear register */
    __IO uint32_t EINT_MASK_SET[2];        /*!< 0x0450 EINT interrupt mask set register */
    __IO uint32_t EINT_MASK_CLR[2];        /*!< 0x0458 EINT interrupt mask clear register */
    __IO uint32_t EINT_WAKEUP_MASK_SET[2]; /*!< 0x0460 EINT wakeup event mask set register */
    __IO uint32_t EINT_WAKEUP_MASK_CLR[2]; /*!< 0x0468 EINT wakeup event mask clear register */
    __IO uint32_t EINT_SOFT_SET[2];        /*!< 0x0470 EINT software interrupt set register */
    __IO uint32_t EINT_SOFT_CLR[2];        /*!< 0x0478 EINT software interrupt clear register */
    __IO uint32_t EINT_ENABLE_SET[2];        /*!< 0x0480 EINT trigger result enable set register */
    __IO uint32_t EINT_ENABLE_CLR[2];        /*!< 0x0488 EINT trigger result enable clear register */
    __IO uint32_t EINT_TOGGLE_DIS[2];        /*!< 0x0490 EINT TOOGLE DIS */
    __I uint32_t RESERVED3[27];            /*!< 0x0490~0x0500 Reserved */

    __IO uint32_t EINT_COUNTER_OUT; /*!< 0x0504 EINT internal counter value out */
    __I uint32_t RESERVED4[18];     /*!< 0x0508~0x054C Reserved */

    __IO uint32_t EINT_TIMER_OUT[10];   /*!< 0x0550~0x0574 Timer0 timestamp value out*/
    __I uint32_t RESERVED5[35];         /*!< 0x0578~0x05FC Reserved */
    __IO uint32_t EINT_TRIGGER_STA[14]; /*!< 0x0600~0x0634 EINT trigger status register */
    __I uint32_t RESERVED6[51];         /*!< 0x0638~0x06FC Reserved */
    __IO uint32_t EINT_DEBUG_SEL;       /*!< 0x0700 EINT debug select register */
} EINT_REGISTER_T;

#define EINT_CON_DBC_CNT_OFFSET (0)
#define EINT_CON_DBC_CNT_MASK (0x7FFUL << EINT_CON_DBC_CNT_OFFSET)

#define EINT_CON_DBC_EN_OFFSET (16)
#define EINT_CON_DBC_EN_MASK (0x1UL << EINT_CON_DBC_EN_OFFSET)

#define EINT_CON_RSTD_OFFSET (24)
#define EINT_CON_RSTD_MASK (0x1UL << EINT_CON_RSTD_OFFSET)

#define EINT_CON_PRESCALER_OFFSET (12)
#define EINT_CON_PRESCALER_MASK (0x7UL << EINT_CON_PRESCALER_OFFSET)

/*************************** EINT definition end line  ********************************/

#endif /* __EINT_REG_DEFINITION_H__ */