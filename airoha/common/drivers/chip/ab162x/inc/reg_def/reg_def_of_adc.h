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

#ifndef __ADC_REG_DEFINITION_H__
#define __ADC_REG_DEFINITION_H__


#include <stdint.h>


/* structure type to access the ADC register
 */
typedef struct {
    uint32_t RESERVED0[1];
    __IO uint32_t AUXADC_CON1;
    union {
        struct {
            __I uint8_t ADC_STAT;
            __IO uint8_t SOFT_RST;
            __IO uint8_t AUXADC_CON3_RESERVED0;
            __IO uint8_t AUXADC_CON3_RESERVED1;
        } AUXADC_CON3_CELLS;
        __IO uint32_t AUXADC_CON3;
    } AUXADC_CON3_UNION;

    union {
        struct {
            __IO uint8_t AUTO_AVG_EN;
            __IO uint8_t AUTOSET;
            __IO uint8_t AUXADC_CON4_RESERVED0;
            __IO uint8_t AUXADC_CON4_RESERVED1;
        } AUXADC_CON4_CELLS;
        __IO uint32_t AUXADC_CON4;
    } AUXADC_CON4_UNION;

    __I  uint32_t AUXADC_DATA[32];

    __IO  uint32_t AUXADC_SLP_LIST;
    __IO  uint32_t AUXADC_SLP_STATE;
    __IO uint32_t AUXADC_CON5;

    union {
        struct {
            __IO uint8_t AUTO_AUXADC_EN;
            __IO uint8_t AUTO_SEL;
            __IO uint8_t AUXADC_CON6_RESERVED0;
            __IO uint8_t AUXADC_CON6_RESERVED1;
        } AUXADC_CON6_CELLS;
        __IO uint32_t AUXADC_CON6;
    } AUXADC_CON6_UNION;

    union {
        struct {
            __IO uint8_t ACD_MODE;
            __IO uint8_t ACD_AUX_PWDB;
            __IO uint8_t ACD_CON_SEL_RESERVED0;
            __IO uint8_t ACD_CON_SEL_RESERVED1;
        } ACD_CON_SEL_CELLS;
        __IO uint32_t ACD_CON_SEL;
    } ACD_CON_SEL_UNION;

    union {
        struct {
            __IO uint8_t EXT_AUX_SEL;
            __IO uint8_t EXT_AUX_EN;
            __IO uint8_t EXT_AUX_SEL_RESERVED0;
            __IO uint8_t EXT_AUX_SEL_RESERVED1;
        } EXT_AUX_SEL_CELLS;
        __IO uint32_t EXT_AUX_SEL;
    } EXT_AUX_SEL_UNION;

    __IO uint32_t AUXADC_DIV_CON;


    union {
        struct {
            __IO uint8_t RG_AUXADC_LDO_EN;
            __IO uint8_t RG_AUXADC_LDO_OUT_EN;
            __IO uint8_t MACRO_CON2_RESERVED0;
            __IO uint8_t MACRO_CON2_RESERVED1;
        } MACRO_CON2_CELLS;
        __IO uint32_t MACRO_CON2;
    } MACRO_CON2_UNION;


    union {
        struct {
            __IO uint8_t AUXADC_EN;
            __IO uint8_t RG_AUXADC_REF_SEL;
            __IO uint8_t ANA_EN_CON_RESERVED0;
            __IO uint8_t ANA_EN_CON_RESERVED1;
        } ANA_EN_CON_CELLS;
        __IO uint32_t ANA_EN_CON;
    } ANA_EN_CON_UNION;

    __IO  uint32_t AUXADC_AVG_NUM;

    __I   uint32_t AUXADC_AVG_READY;

    __I   uint32_t AUXADC_AVG_DATA;

    __IO uint32_t ACD_FUNC_MODE_CTL;

    __IO uint32_t RG_AUXADC_DEBUG_EN;

    __IO uint32_t AUXADC_SPL_CON;

    union {
        struct {
            __IO uint8_t AUXADC_MSB0_CON;
            __IO uint8_t AUXADC_MSB1_CON;
            __IO uint8_t AUXADC_MSB_CON_RESERVED0;
            __IO uint8_t AUXADC_MSB_CON_RESERVED1;
        } AUXADC_MSB_CON_CELLS;
        __IO uint32_t AUXADC_MSB_CON;
    } AUXADC_MSB_CON_UNION;

    __IO uint32_t RG_D2A_SAR_CLK_EN;

    union {
        struct {
            __IO uint8_t RG_ADC2SRAM_EN;
            __IO uint8_t AUXADC_MSB1_CON;
            __IO uint8_t ADC_SRAM_CON_RESERVED0;
            __IO uint8_t ADC_SRAM_CON_RESERVED1;
        } ADC_SRAM_CON_CELLS;
        __IO uint32_t ADC_SRAM_CON;
    } ADC_SRAM_CON_UNION;

    __IO uint32_t AUXADC_RESERVE;
    __IO uint32_t RESERVED1[9];
    __IO uint32_t AVG_DATA[32];

} ADC_REGISTER_T;

/* AUXADC_CON3 register definitions
 */
#define AUXADC_CON3_SOFT_RST_MASK                       (0x1UL)

#define AUXADC_CON3_ADC_STA_MASK                        (0x1UL)

/* AUXADC_CON4 register definitions
 */
#define AUXADC_CON4_AUTOSET_MASK                        (0x1UL)

/* MACRO_CON2 register definitions
 */
#define MACRO_CON2_RG_AUXADC_LDO_EN_MASK                (0x1UL)

/* ANA_EN_CON register definitions
 */
#define ANA_EN_CON_AUXADC_EN_MASK                       (0x1UL)


#define ADC                                     ((ADC_REGISTER_T *)SARADC_BASE)

#endif /* __ADC_REG_DEFINITION_H__ */