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

#ifdef HAL_CLOCK_MODULE_ENABLED
#include <stdbool.h>
#include <stdio.h>
#include "hal_clock_internal.h"

/*****************************************************************************
 * General definition
 *****************************************************************************/
#define PSEUDO_CG_TTL                           (HAL_CLOCK_CG_PSEUDO_END - HAL_CLOCK_CG_PSEUDO_BEGIN + 1)

#define PWM_CG_MULTI_CTRL_REQUEST_BIT_MASK       0x0000001F  /* 5 PWM Channels, bit[4:0] */

typedef enum {
    CG_REQUEST_STATUS,
    CG_REQUEST_CLEAR,
    CG_REQUEST_SET,

    CLK_REQ_ENABLE = CG_REQUEST_CLEAR,
    CLK_REQ_DISABLE = CG_REQUEST_SET
} cg_request_t;

typedef enum {
    CG_CLR__CLK_ON,
    CG_SET__CLK_OFF
} cg_state_t;

cg_state_t pseudo_cg_tbl[PSEUDO_CG_TTL];

const hal_clock_cg_id clk_always_on_cg_tbl[] = {
    HAL_CLOCK_CG_CMSYS_BUS,
    //HAL_CLOCK_CG_MEM_BUS,
    //HAL_CLOCK_CG_CONN_BUS,
    HAL_CLOCK_CG_IBEX,
    HAL_CLOCK_CG_OSTIMER,
    HAL_CLOCK_CG_SFC,
    HAL_CLOCK_CG_SPM_BCLK_CM33, HAL_CLOCK_CG_SPM_DIV,

    HAL_CLOCK_CG_DUMMY_END
};

/* request type
 * CG_REQUEST_STATUS: return CG_CLR__CLK_ON, CG_SET__CLK_OFF, HAL_CLOCK_STATUS_INVALID_PARAMETER
 * CG_REQUEST_CLEAR : return HAL_CLOCK_STATUS_OK, HAL_CLOCK_STATUS_INVALID_PARAMETER
 * CG_REQUEST_SET   : return HAL_CLOCK_STATUS_OK, HAL_CLOCK_STATUS_ERROR, HAL_CLOCK_STATUS_INVALID_PARAMETER
 * others           : return HAL_CLOCK_STATUS_INVALID_PARAMETER
 */
int32_t clock_physical_cg_ctrl(hal_clock_cg_id clock_id, cg_request_t request)
{
    volatile uint32_t *con_addr = NULL, *set_addr = NULL, *clr_addr = NULL;
    uint32_t bit_idx = clock_id & 0x1F;

    /* Set pointer to CG reg ptr */
    if((clock_id >= HAL_CLOCK_CG_XO_PDN_PD_BEGIN) && (clock_id <= HAL_CLOCK_CG_XO_PDN_PD_END)) {
        con_addr = XO_PDN_PD_COND0__XO_PDN_PD_COND0;
        set_addr = XO_PDN_PD_SETD0__XO_PDN_PD_SETD0;
        clr_addr = XO_PDN_PD_CLRD0__XO_PDN_PD_CLRD0;
    }
    else if((clock_id >= HAL_CLOCK_CG_XO_PDN_AO0_BEGIN) && (clock_id <= HAL_CLOCK_CG_XO_PDN_AO0_END)) {
        con_addr = XO_PDN_AO_COND0__XO_PDN_AO_COND0;
        set_addr = XO_PDN_AO_SETD0__XO_PDN_AO_SETD0;
        clr_addr = XO_PDN_AO_CLRD0__XO_PDN_AO_CLRD0;
    }
    else if((clock_id >= HAL_CLOCK_CG_XO_PDN_AO1_BEGIN) && (clock_id <= HAL_CLOCK_CG_XO_PDN_AO1_END)) {
        con_addr = XO_PDN_AO_COND1__XO_PDN_AO_COND1;
        set_addr = XO_PDN_AO_SETD1__XO_PDN_AO_SETD1;
        clr_addr = XO_PDN_AO_CLRD1__XO_PDN_AO_CLRD1;
    }
    else if((clock_id >= HAL_CLOCK_CG_XO_PDN_TOP0_BEGIN) && (clock_id <= HAL_CLOCK_CG_XO_PDN_TOP0_END)) {
        con_addr = XO_PDN_TOP_COND0__XO_PDN_TOP_COND0;
        set_addr = XO_PDN_TOP_SETD0__XO_PDN_TOP_SETD0;
        clr_addr = XO_PDN_TOP_CLRD0__XO_PDN_TOP_CLRD0;
    }
    else if((clock_id >= HAL_CLOCK_CG_XO_PDN_TOP1_BEGIN) && (clock_id <= HAL_CLOCK_CG_XO_PDN_TOP1_END)) {
        con_addr = XO_PDN_TOP_COND1__XO_PDN_TOP_COND1;
        set_addr = XO_PDN_TOP_SETD1__XO_PDN_TOP_SETD1;
        clr_addr = XO_PDN_TOP_CLRD1__XO_PDN_TOP_CLRD1;
    }
    else if((clock_id >= HAL_CLOCK_CG_PDN_PD_BEGIN) && (clock_id <= HAL_CLOCK_CG_PDN_PD_END)) {
        con_addr = PDN_PD_COND0__PDN_PD_COND0;
        set_addr = PDN_PD_SETD0__PDN_PD_SETD0;
        clr_addr = PDN_PD_CLRD0__PDN_PD_CLRD0;
    }
    else if((clock_id >= HAL_CLOCK_CG_PDN_TOP_BEGIN) && (clock_id <= HAL_CLOCK_CG_PDN_TOP_END)) {
        con_addr = PDN_TOP_COND0__PDN_TOP_COND0;
        set_addr = PDN_TOP_SETD0__PDN_TOP_SETD0;
        clr_addr = PDN_TOP_CLRD0__PDN_TOP_CLRD0;
    }
    else {
        return HAL_CLOCK_STATUS_INVALID_PARAMETER;
    }

    if(request == CG_REQUEST_STATUS) {
        return ((*con_addr >> bit_idx) & 0x01); /* status (return cg bit directly) */
    }
    else if(request == CG_REQUEST_CLEAR) {
        *clr_addr = (1 << bit_idx); /* cg clear (clock on) */
    }
    else if(request == CG_REQUEST_SET) {
        uint8_t idx = 0;

        do {
            if(clock_id == clk_always_on_cg_tbl[idx]) { /* do not allow disabling of the CG in the table */
                return HAL_CLOCK_STATUS_ERROR;
            }
        }
        while(clk_always_on_cg_tbl[++idx] != HAL_CLOCK_CG_DUMMY_END);

        *set_addr = (1 << bit_idx); /* cg set (clock off) */
    }
    else {
        return HAL_CLOCK_STATUS_INVALID_PARAMETER;
    }
    return HAL_CLOCK_STATUS_OK;
}

hal_clock_status_t hal_clock_enable(hal_clock_cg_id clock_id)
{
#ifdef FPGA_ENV
    return HAL_CLOCK_STATUS_OK;
#else
    if((clock_id >= HAL_CLOCK_CG_PSEUDO_BEGIN) && (clock_id <= HAL_CLOCK_CG_PSEUDO_END)) {
        pseudo_cg_tbl[clock_id-HAL_CLOCK_CG_PSEUDO_BEGIN] = CG_CLR__CLK_ON;
    }
    else if(clock_id & HAL_CLOCK_CG_PWM_MULTI_CTRL) {
        *XO_PDN_AO_CLRD0__XO_PDN_AO_CLRD0 = clock_id & PWM_CG_MULTI_CTRL_REQUEST_BIT_MASK;
    }
    else {
        hal_clock_status_t status = clock_physical_cg_ctrl(clock_id, CG_REQUEST_CLEAR);
        if(status != HAL_CLOCK_STATUS_OK) {
            return status;
        }
    }
    return HAL_CLOCK_STATUS_OK;
#endif /* !FPGA_ENV */
}

hal_clock_status_t hal_clock_disable(hal_clock_cg_id clock_id)
{
#ifdef FPGA_ENV
    return HAL_CLOCK_STATUS_OK;
#else
    if((clock_id >= HAL_CLOCK_CG_PSEUDO_BEGIN) && (clock_id <= HAL_CLOCK_CG_PSEUDO_END)) {
        pseudo_cg_tbl[clock_id-HAL_CLOCK_CG_PSEUDO_BEGIN] = CG_SET__CLK_OFF;
    }
    else if(clock_id & HAL_CLOCK_CG_PWM_MULTI_CTRL) {
        *XO_PDN_AO_SETD0__XO_PDN_AO_SETD0 = clock_id & PWM_CG_MULTI_CTRL_REQUEST_BIT_MASK;
    }
    else {
        hal_clock_status_t status = clock_physical_cg_ctrl(clock_id, CG_REQUEST_SET);
        if(status != HAL_CLOCK_STATUS_OK) {
            return status;
        }
    }
    return HAL_CLOCK_STATUS_OK;
#endif /* !FPGA_ENV */
}

bool hal_clock_is_enabled(hal_clock_cg_id clock_id)
{
#ifdef FPGA_ENV
    return true;
#else
    if((clock_id >= HAL_CLOCK_CG_PSEUDO_BEGIN) && (clock_id <= HAL_CLOCK_CG_PSEUDO_END)) {
        return pseudo_cg_tbl[clock_id-HAL_CLOCK_CG_PSEUDO_BEGIN];
    }
    else {
        if(clock_physical_cg_ctrl(clock_id, CG_REQUEST_STATUS) == CG_CLR__CLK_ON) {
            return true;
        }
    }
    return false;
#endif
}

uint8_t hal_clock_mux_cur_sel(clock_mux_sel_id mux_id)
{
    uint8_t mux_sel = 0;

#ifndef FPGA_ENV
    switch(mux_id) {
        case CLK_SYS_SEL:
            mux_sel = *RTC_LPOSC_CON4__CLK_SYS_SEL;
            break;
        case CLK_IBEX_SEL:
            mux_sel = *CKSYS_CLK_CFG_0__CLK_IBEX_SEL;
        default:
            break;
    }
#endif
    return mux_sel;
}

hal_clock_status_t hal_clock_mux_sel(clock_mux_sel_id mux_id, clk_mux_sel_idx_t mux_sel)
{
#ifndef FPGA_ENV
    switch(mux_id) {
        case CLK_IBEX_SEL:
            *CKSYS_CLK_FORCE_ON_0__CLK_IBEX_FORCE_ON = 1;
            *CKSYS_CLK_CFG_0__CLK_IBEX_SEL = mux_sel;
            *CKSYS_CLK_UPDATE_0__CHG_IBEX = 1;
            while(*CKSYS_CLK_UPDATE_0__CHG_IBEX);
            while(*CKSYS_CLK_UPDATE_STATUS_0__CHG_IBEX_OK);
            *CKSYS_CLK_FORCE_ON_0__CLK_IBEX_FORCE_ON = 0;
            return HAL_CLOCK_STATUS_OK;
        default:
            return HAL_CLOCK_STATUS_INVALID_PARAMETER;
    }
#endif
    return HAL_CLOCK_STATUS_OK;
}

#endif /* HAL_CLOCK_MODULE_ENABLED */

