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

#ifndef __AIOADC_REG_DEFINITION_H__
#define __AIOADC_REG_DEFINITION_H__


#include <stdint.h>

/* structure type to access the ADC register
 */
typedef struct {
    __IO uint32_t AIO_ADC_DATA[10];
    __IO uint32_t AIO_ADC_RESERVED0[22];

    union {
        struct {
            __IO uint8_t aio_adc_en_pluse;
            __IO uint8_t aio_adc_busy;
            __IO uint8_t AIO_ADC_EN_RESERVED0;
            __IO uint8_t AIO_ADC_EN_RESERVED1;
        } AIO_ADC_EN_CELLS;
        __IO uint32_t AIO_ADC_EN;
    } AIO_ADC_EN_UNION;

    union {
        struct {
            __IO uint8_t aio_adc_avg_sel;
            __IO uint8_t aio_adc_avg_shift_sel;
            __IO uint8_t aio_adc_rst_dly;
            __IO uint8_t aio_adc_sw_ch_dly;
        } AIO_ADC_CON0_CELLS;
        __IO uint32_t AIO_ADC_CON0;
    } AIO_ADC_CON0_UNION;

    __IO uint32_t AIO_ADC_CON1;
    __IO uint32_t AIO_ADC_CON2;
    __IO uint32_t AIO_ADC_CON3;

    union {
        struct {
            __IO uint8_t aio_clk_dig_en;
            __IO uint8_t aio_clk_ana_en;
            __IO uint8_t AIO_ADC_CON4_RESERVED0;
            __IO uint8_t AIO_ADC_CON4_RESERVED1;
        } AIO_ADC_CON4_CELLS;
        __IO uint32_t AIO_ADC_CON4;
    } AIO_ADC_CON4_UNION;

    __IO uint32_t AIO_ADC_CON5;

    union {
        struct {
            __IO uint8_t aio_debug_en;
            __IO uint8_t aio_debug_sel;
            __IO uint8_t AIO_ADC_DEBUG_RESERVED0;
            __IO uint8_t AIO_ADC_DEBUG_RESERVED1;
        } AIO_ADC_DEBUG_CELLS;
        __IO uint32_t AIO_ADC_DEBUG;
    } AIO_ADC_DEBUG_UNION;

    union {
        struct {
            __IO uint8_t aio_adc_force_on;
            __IO uint8_t aio_adc_clk_inv_en;
            __IO uint8_t AIO_ADC_CON6_RESERVED0;
            __IO uint8_t AIO_ADC_CON6_RESERVED1;
        } AIO_ADC_CON6_CELLS;
        __IO uint32_t AIO_ADC_CON6;
    } AIO_ADC_CON6_UNION;

    union {
        struct {
            __IO uint8_t da_sel_mode_aio_man;
            __IO uint8_t da_rstn_aio_man;
            __IO uint8_t da_en_aio_man;
            __IO uint8_t AIO_ADC_MAN0_RESERVED0;
        } AIO_ADC_MAN0_CELLS;
        __IO uint32_t AIO_ADC_MAN0;
    } AIO_ADC_MAN0_UNION;

    __IO  uint32_t AIO_ADC_MAN1;

    union {
        struct {
            __IO uint8_t da_sel_mode_aio_man_sel;
            __IO uint8_t da_rstn_aio_man_sel;
            __IO uint8_t da_en_aio_man_sel;
            __IO uint8_t da_sel_ch_aio_man_sel;
        } AIO_ADC_MAN_SEL_CELLS;
        __IO uint32_t AIO_ADC_MAN_SEL;
    } AIO_ADC_MAN_SEL_UNION;
} AIOADC_REGISTER_T;

#define AIOADC                                     ((AIOADC_REGISTER_T *)AIOADC_BASE)
#endif /* __AIOADC_REG_DEFINITION_H__ */