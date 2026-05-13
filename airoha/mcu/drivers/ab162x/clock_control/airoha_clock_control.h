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
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
 * RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
 * TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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

#ifndef __AIROHA_CLOCK_CONTROL_H__
#define __AIROHA_CLOCK_CONTROL_H__

#include <zephyr/types.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/clock_control.h>

#include "autoconf.h"

#include "hal_clock_internal.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef ON
#define ON 1
#endif

#ifndef OFF
#define OFF 0
#endif

#ifndef ENABLE
#define ENABLE 1
#endif

#ifndef DISABLE
#define DISABLE 0
#endif

#define AIROHA_CLOCK_NODE_ID  DT_NODELABEL(clock_node_label)
#define AIROHA_CLOCK_DEVICE   DEVICE_DT_GET(AIROHA_CLOCK_NODE_ID)

// ============================================================================
typedef enum {
    AIR_CLK_GET_RATE__MCU_KHZ_FROM_MUX,
    AIR_CLK_GET_RATE__MUX_IDX,

    AIR_CLK_GET_RATE__FQMTR_HZ_REF_XO,         // Reference clock is DCXO and need to provide source clock frequency
    AIR_CLK_GET_RATE__FQMTR_HZ_REF_XO_WINSET,  // Reference clock is DCXO and need to provide winset
    AIR_CLK_GET_RATE__FQMTR_HZ,                // Need to provide reference clock id, frequency and source clock frequency
    AIR_CLK_GET_RATE__FQMTR_HZ_WINSET,         // Need to provide reference clock id, frequency and winset

#ifdef CONFIG_AIR_DVFS
    AIR_CLK_GET_RATE__DVFS_VCORE,
    AIR_CLK_GET_RATE__DVFS_FRQ
#endif
} air_clk_get_rate_op;

typedef union {
    struct {
        clock_mux_sel_id mux_id;
    } mux_idx;
    struct {
        hal_src_clock src_clk;
        uint32_t      src_clk_hz;
    } fqmtr_hz_ref_xo;
    struct {
        hal_src_clock src_clk;
        uint32_t      winset;
    } fqmtr_hz_ref_xo_windset;
    struct {
        hal_src_clock src_clk;
        ref_clock_t   ref_clk;
        uint32_t      src_clk_hz;
        uint32_t      ref_clk_hz;
    } fqmtr_hz;
    struct {
        hal_src_clock src_clk;
        ref_clock_t   ref_clk;
        uint32_t      ref_clk_hz;
        uint32_t      winset;
    } fqmtr_hz_winset;
} air_clk_get_rate_para_t;

typedef struct {
    air_clk_get_rate_op     operation;
    air_clk_get_rate_para_t t_para;
} air_clk_get_rate_t;

// ============================================================================
typedef enum {
    AIR_CLK_CFG__SET_MUX_IDX,

#ifdef CONFIG_MULTITHREADING
    AIR_CLK_CFG__SET_LPOSC_KHZ,
#endif

    AIR_CLK_CFG__DCM_CTRL,

#ifdef CONFIG_AIR_DCXO
    AIR_CLK_CFG__DCXO_32K_CTRL,
    AIR_CLK_CFG__DCXO_PM_CTRL  // Power Mode: LPM or FPM
#endif
} air_clk_cfg_op;

typedef union {
    struct {
        clock_mux_sel_id mux_id;
        clk_mux_sel_idx_t mux_sel;
    } set_mux_idx;
    struct {
        uint32_t    khz;
    } set_lposc_khz;
    struct {
        bool        val;  // ENABLE or DISABLE
    } dcm_ctrl;

#ifdef CONFIG_AIR_DCXO
    struct {
        bool        val;  // ENABLE or DISABLE
    } dcxo_32k_ctrl;
    struct {
        dcxo_mode_t mode;
    } dcxo_pm_ctrl;
#endif
} air_clk_cfg_para_t;

typedef struct {
    air_clk_cfg_op     operation;
    air_clk_cfg_para_t t_para;
} air_clk_cfg_t;

#endif /* __AIROHA_CLOCK_CONTROL_H__ */

