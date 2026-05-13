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

#ifndef __GPIO_REG_DEFINITION_H__
#define __GPIO_REG_DEFINITION_H__

#include <stdint.h>

/*************************** GPIO register definition start line  *******************************
 */

typedef struct
{
    __IO uint32_t GPIO_DIR[2];   /*0X420B0000:< GPIO direction register */
    __IO uint32_t RESERVED0[2];  /*reserved  */
    __IO uint32_t GPIO_DOUT[2];  /*0X420B0010:< GPIO direction register */
    __IO uint32_t RESERVED1[2];  /*reserved  */
    __IO uint32_t GPIO_DIN[2];   /*0X420B0020:< GPIO direction register */
    __IO uint32_t RESERVED2[2];  /*reserved  */
    __IO uint32_t GPIO_MODE[6];  /*0X420B0030:< GPIO direction register */
    __IO uint32_t RESERVED3[2];  /*reserved  */
    __IO uint32_t GPIO_BACKUP;   /*0X420B0050:< GPIO direction register */
    __IO uint32_t RESERVED4[47]; /*reserved  */

    __IO uint32_t GPIO_DIR_SET[2];  /*0X420B0110:< GPIO direction register */
    __IO uint32_t RESERVED5[2];     /*reserved  */
    __IO uint32_t GPIO_DIR_CLR[2];  /*0X420B0120< GPIO direction register */
    __IO uint32_t RESERVED6[6];     /*reserved  */
    __IO uint32_t GPIO_DOUT_SET[2]; /*0X420B0140< GPIO direction register */
    __IO uint32_t RESERVED7[2];     /*reserved  */
    __IO uint32_t GPIO_DOUT_CLR[2]; /*0X420B0150< GPIO direction register */
    __IO uint32_t RESERVED8[42];    /*reserved  */

    __IO uint32_t GPIO_MODE_SET[6]; /*0X420B0200< GPIO direction register */
    __IO uint32_t RESERVED9[58];    /*reserved  */

    __IO uint32_t GPIO_MODE_CLR[6]; /*0X420B0300< GPIO direction register */
} GPIO_BASE_REGISTER_T;

typedef struct
{
    __IO uint32_t RW;   /*!< GPIO RW register */
    __IO uint32_t SET;  /*!< GPIO set register */
    __IO uint32_t CLR;  /*!< GPIO clear register */
    uint32_t RESERVED1; /*!< reserved */
} GPIO_CFG_REGISTER_T;

typedef struct
{
    GPIO_CFG_REGISTER_T GPIO_DRV[2];           /*0X420C0000!< GPIO DRV register */
    GPIO_CFG_REGISTER_T GPIO_EH;               /*0X420C0020!< GPIO DRV register */
    GPIO_CFG_REGISTER_T GPIO_G;                /*0X420C0030!< GPIO analog control register */
    GPIO_CFG_REGISTER_T GPIO_IES;              /*0X420C0040!< GPIO input buffer control register */
    GPIO_CFG_REGISTER_T GPIO_PD;               /*0X420C0050!< GPIO pull down register */
    GPIO_CFG_REGISTER_T GPIO_PU4P7K;           /*0X420C0060!< GPIO pull up register */
    GPIO_CFG_REGISTER_T GPIO_PU;               /*0X420C0070!< GPIO pull up register */
    GPIO_CFG_REGISTER_T GPIO_RSEL;             /*0X420C0080!< GPIO RDSEL register */
    GPIO_CFG_REGISTER_T GPIO_SMT;              /*0X420C0090!< GPIO schimtt trigger register */
    GPIO_CFG_REGISTER_T GPIO_SR;               /*0X420C00A0!< GPIO slew rate register */
    GPIO_CFG_REGISTER_T GPIO_TDSEL;            /*0X420C00B0!< GPIO TDSEL register */
    GPIO_CFG_REGISTER_T GPIO_DUMMY;            /*0X420C00C0!< GPIO dummy register */
    __IO uint32_t RESERVED[4];                /*0X420C00D0:reserved  */
    GPIO_CFG_REGISTER_T GPIO_RTC_IN_EN;        /*0X420C00E0!< GPIO dummy register */
    GPIO_CFG_REGISTER_T GPIO_RTC_GPIO_MODE[2]; /*0X420C00F0!< GPIO dummy register */
} GPIO_CFG0_REGISTER_T;

typedef struct
{
    GPIO_CFG_REGISTER_T GPIO_DRV[2];           /*0X420C0000!< GPIO DRV register */
    GPIO_CFG_REGISTER_T GPIO_EH;               /*0X420C0020!< GPIO DRV register */
    GPIO_CFG_REGISTER_T GPIO_G;                /*0X420C0030!< GPIO analog control register */
    GPIO_CFG_REGISTER_T GPIO_IES;              /*0X420C0040!< GPIO input buffer control register */
    GPIO_CFG_REGISTER_T GPIO_PD;               /*0X420C0050!< GPIO pull down register */
    GPIO_CFG_REGISTER_T GPIO_PU4P7K;           /*0X420C0060!< GPIO pull up register */
    GPIO_CFG_REGISTER_T GPIO_PU;               /*0X420C0070!< GPIO pull up register */
    GPIO_CFG_REGISTER_T GPIO_RSEL;             /*0X420C0080!< GPIO RDSEL register */
    GPIO_CFG_REGISTER_T GPIO_SMT;              /*0X420C0090!< GPIO schimtt trigger register */
    GPIO_CFG_REGISTER_T GPIO_SR;               /*0X420C00A0!< GPIO slew rate register */
    GPIO_CFG_REGISTER_T GPIO_TDSEL;            /*0X420C00B0!< GPIO TDSEL register */
    GPIO_CFG_REGISTER_T GPIO_DUMMY;            /*0X420C00C0!< GPIO dummy register */
    __IO uint32_t RESERVED[8];                /*0X420C00D0:reserved  */
    GPIO_CFG_REGISTER_T GPIO_RTC_IN_EN;        /*0X420C00F0!< GPIO dummy register */
    GPIO_CFG_REGISTER_T GPIO_RTC_GPIO_MODE[2]; /*0X420C0100!< GPIO dummy register */
} GPIO_CFG1_REGISTER_T;

#define GPIO_BASE_REGISTER ((GPIO_BASE_REGISTER_T *)GPIO_BASE)
#define GPIO_CFG0_REGISTER ((GPIO_CFG0_REGISTER_T *)IO_CFG_0_BASE)
#define GPIO_CFG1_REGISTER ((GPIO_CFG1_REGISTER_T *)IO_CFG_1_BASE)

/*************************** GPIO register definition end line  *******************************
 */

#endif /* __GPIO_REG_DEFINITION_H__ */