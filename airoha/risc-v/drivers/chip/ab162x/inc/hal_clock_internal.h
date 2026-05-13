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

#ifndef __HAL_CLOCK_INTERNAL_H__
#define __HAL_CLOCK_INTERNAL_H__

#include "hal_clock.h"

#ifdef HAL_CLOCK_MODULE_ENABLED
#include "hal_clock_platform.h"

/*****************************************************************************
 * General definition
 *****************************************************************************/
#if defined(CONFIG_AIR_FPGA_ENV_ENABLE) && !defined(FPGA_ENV)
#define FPGA_ENV
#endif

/*****************************************************************************
 * enum or struct
 *****************************************************************************/
/* Index definitions of Every MUX (clock_mux_sel_id) */
/* Used when Select a Target index in a MUX          */
typedef enum {
    /* MUX: CLK_IBEX_SEL */
    MUX_IBEX_IDX_XO                  = 0,
    MUX_IBEX_IDX_XO_DBL              = 1,
    MUX_IBEX_IDX_OSC_26M             = 2,
    MUX_IBEX_IDX_OSC_LS              = 3,
} clk_mux_sel_idx_t;

/*****************************************************************************
 * CG
 *****************************************************************************/
/* ------ Range ------ */
#define HAL_CLOCK_CG_XO_PDN_PD_BEGIN       HAL_CLOCK_CG_AUXADC
#define HAL_CLOCK_CG_XO_PDN_PD_END         HAL_CLOCK_CG_AUXADC

#define HAL_CLOCK_CG_XO_PDN_AO0_BEGIN      HAL_CLOCK_CG_PWM_DMA_0
#define HAL_CLOCK_CG_XO_PDN_AO0_END        HAL_CLOCK_CG_PMU_1M

#define HAL_CLOCK_CG_XO_PDN_AO1_BEGIN      HAL_CLOCK_CG_FAST_DMA_1
#define HAL_CLOCK_CG_XO_PDN_AO1_END        HAL_CLOCK_CG_SEC_MON_AO

#define HAL_CLOCK_CG_XO_PDN_TOP0_BEGIN     HAL_CLOCK_CG_SPIMST0
#define HAL_CLOCK_CG_XO_PDN_TOP0_END       HAL_CLOCK_CG_BT_MAC

#define HAL_CLOCK_CG_XO_PDN_TOP1_BEGIN     HAL_CLOCK_CG_CMSYS_BUS
#define HAL_CLOCK_CG_XO_PDN_TOP1_END       HAL_CLOCK_CG_OSC_HS_D4

#define HAL_CLOCK_CG_PDN_PD_BEGIN          HAL_CLOCK_CG_AUXADC_SRAM
#define HAL_CLOCK_CG_PDN_PD_END            HAL_CLOCK_CG_USB_DMA

#define HAL_CLOCK_CG_PDN_TOP_BEGIN         HAL_CLOCK_CG_CMSYS_ROM
#define HAL_CLOCK_CG_PDN_TOP_END           HAL_CLOCK_CG_CMSYS_ROM

/* ------ Alias ------ */
#define HAL_CLOCK_CG_PWM_DMA0              HAL_CLOCK_CG_PWM_DMA_0
#define HAL_CLOCK_CG_PWM_DMA1              HAL_CLOCK_CG_PWM_DMA_1
#define HAL_CLOCK_CG_PWM_0                 HAL_CLOCK_CG_PWM_DMA_0
#define HAL_CLOCK_CG_PWM_1                 HAL_CLOCK_CG_PWM_DMA_1
#define HAL_CLOCK_CG_PWM0                  HAL_CLOCK_CG_PWM_DMA_0
#define HAL_CLOCK_CG_PWM1                  HAL_CLOCK_CG_PWM_DMA_1
#define HAL_CLOCK_CG_PWM2                  HAL_CLOCK_CG_PWM_2
#define HAL_CLOCK_CG_PWM3                  HAL_CLOCK_CG_PWM_3
#define HAL_CLOCK_CG_PWM4                  HAL_CLOCK_CG_PWM_4
#define HAL_CLOCK_CG_UART_0                HAL_CLOCK_CG_UART0
#define HAL_CLOCK_CG_UART_1                HAL_CLOCK_CG_UART1
#define HAL_CLOCK_CG_UART_2                HAL_CLOCK_CG_UART2
#define HAL_CLOCK_CG_UART_DMA_0            HAL_CLOCK_CG_UART_DMA0
#define HAL_CLOCK_CG_UART_DMA_1            HAL_CLOCK_CG_UART_DMA1
#define HAL_CLOCK_CG_UART_DMA_2            HAL_CLOCK_CG_UART_DMA2
#define HAL_CLOCK_CG_I3C_0                 HAL_CLOCK_CG_I3C0
#define HAL_CLOCK_CG_I3C_1                 HAL_CLOCK_CG_I3C1
#define HAL_CLOCK_CG_I3C_DMA_0             HAL_CLOCK_CG_I3C_DMA0
#define HAL_CLOCK_CG_I3C_DMA_1             HAL_CLOCK_CG_I3C_DMA1
#define HAL_CLOCK_CG_SPIMST_0              HAL_CLOCK_CG_SPIMST0
#define HAL_CLOCK_CG_SPIMST_1              HAL_CLOCK_CG_SPIMST1
#define HAL_CLOCK_CG_SPIMST_2              HAL_CLOCK_CG_SPIMST2
#define HAL_CLOCK_CG_FAST_DMA0             HAL_CLOCK_CG_FAST_DMA_0
#define HAL_CLOCK_CG_FAST_DMA1             HAL_CLOCK_CG_FAST_DMA_1
#define HAL_CLOCK_CG_AUD_ENGINE_BUS        HAL_CLOCK_CG_AUD_ENGINE
    
/******************************************************************************
 * Common use
 ******************************************************************************/
#define UNUSED_PARAMETER(x) ((void)(x))

#define _U8_B0_              0x01
#define _U8_B1_              0x02
#define _U8_B2_              0x04
#define _U8_B3_              0x08
#define _U8_B4_              0x10
#define _U8_B5_              0x20
#define _U8_B6_              0x40
#define _U8_B7_              0x80

#define _U16_B0_             0x0001
#define _U16_B1_             0x0002
#define _U16_B2_             0x0004
#define _U16_B3_             0x0008
#define _U16_B4_             0x0010
#define _U16_B5_             0x0020
#define _U16_B6_             0x0040
#define _U16_B7_             0x0080
#define _U16_B8_             0x0100
#define _U16_B9_             0x0200
#define _U16_B10_            0x0400
#define _U16_B11_            0x0800
#define _U16_B12_            0x1000
#define _U16_B13_            0x2000
#define _U16_B14_            0x4000
#define _U16_B15_            0x8000

#define _U32_B0_             0x00000001
#define _U32_B1_             0x00000002
#define _U32_B2_             0x00000004
#define _U32_B3_             0x00000008
#define _U32_B4_             0x00000010
#define _U32_B5_             0x00000020
#define _U32_B6_             0x00000040
#define _U32_B7_             0x00000080
#define _U32_B8_             0x00000100
#define _U32_B9_             0x00000200
#define _U32_B10_            0x00000400
#define _U32_B11_            0x00000800
#define _U32_B12_            0x00001000
#define _U32_B13_            0x00002000
#define _U32_B14_            0x00004000
#define _U32_B15_            0x00008000
#define _U32_B16_            0x00010000
#define _U32_B17_            0x00020000
#define _U32_B18_            0x00040000
#define _U32_B19_            0x00080000
#define _U32_B20_            0x00100000
#define _U32_B21_            0x00200000
#define _U32_B22_            0x00400000
#define _U32_B23_            0x00800000
#define _U32_B24_            0x01000000
#define _U32_B25_            0x02000000
#define _U32_B26_            0x04000000
#define _U32_B27_            0x08000000
#define _U32_B28_            0x10000000
#define _U32_B29_            0x20000000
#define _U32_B30_            0x40000000
#define _U32_B31_            0x80000000

/*****************************************************************************
 * Function prototype
 *****************************************************************************/
uint8_t hal_clock_mux_cur_sel(clock_mux_sel_id mux_id);
hal_clock_status_t hal_clock_mux_sel(clock_mux_sel_id mux_id, clk_mux_sel_idx_t mux_sel);

#endif /* HAL_CLOCK_MODULE_ENABLED */
#endif /* __HAL_CLOCK_INTERNAL_H__ */

