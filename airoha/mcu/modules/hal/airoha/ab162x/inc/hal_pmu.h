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

#ifndef __HAL_PMU_H__
#define __HAL_PMU_H__

#include "hal_platform.h"
#include "hal_clock_internal.h"
#ifdef HAL_PMU_MODULE_ENABLED
//#define HAL_PMU_MODULE_EINT_ENABLED
#include "autoconf.h"

#define PMU_CONFIG_HQA        0
#define PMU_CONFIG_DONGLE     1
#define PMU_CONFIG_GAMING     2
#define PMU_CONFIG_OFFICE     3
#define PMU_CONFIG_IOT_OTHERS 4

typedef enum {
    PMU_STATUS_INVALID_PARAMETER  = -1,     /* pmu error invalid parameter */
    PMU_STATUS_ERROR              = 0,      /* pmu undefined error */
    PMU_STATUS_SUCCESS            = 1       /* pmu function ok */
}pmu_status_t;

typedef enum {
    PMU_OFF                 = 0,
    PMU_ON                  = 1,
} pmu_power_operate_t;

typedef enum {
    PMU_HW_MODE             = 0,
    PMU_SW_MODE             = 1,
} pmu_rf_ctrl_t;

typedef enum {
    OFF_REASON              = 0,
    DEEPSLP_BY_EINT         = 1,
    DEEPSLP_BY_COMP         = 2,
    DEEPSLP_BY_USB_PLUG     = 3,
} pmu_on_reason_t;

typedef enum {
    NORM_DEF                = 0,
    NORM_PAD_RSTB_L         = 1,
    NORM_VIO18_PG           = 2,
    NORM_VRF_PG             = 3,
    NORM_VCORE_PG           = 4,
    NORM_VRTC_PG            = 5,
    NORM_WDT                = 6,
    NORM_USB_1620D          = 7,
    NORM_OVP_VIO            = 8,
    NORM_OVP_NOC            = 9,
    NORM_SW_DEEPSLP         = 10,
    DEEPSLP_PAD_RSTB_L      = 11,
    DEEPSLP_VIO18_PG        = 12,
    DEEPSLP_OVP_VIO         = 13,
    SEQ_PAD_RSTB_L          = 14,
    SEQ_VIO18_PG            = 15,
    SEQ_VRF_PG              = 16,
    SEQ_VCORE_VRTC_PG       = 17,
    SEQ_VRTC_PG             = 18,
    SEQ_OVP_VIO             = 19,
    SEQ_OVP_NOC             = 20,
} pmu_off_reason_t;

typedef enum {
    PMU_PWROFF              = 0,
    PMU_NORMAL              = 1,
    PMU_SLEEP               = 2,
    PMU_EXTSLP              = 3,
    PMU_DEEPSLP             = 4,
} pmu_power_stage_t;

typedef enum {
    PMU_VCORE_NM_NV         = 800,
    PMU_VCORE_NM_HV         = 910,
} pmu_vcore_dvfs_t;

typedef enum {
    PMU_RFTX_0_4            = 0,
    PMU_RFTX_6_8            = 1,
    PMU_RFTX_10             = 2,
} pmu_rftx_idx_t;

typedef enum {
    PMU_POF_FALLING_EDGE    = 1,
    PMU_POF_RAISING_EDGE    = 2,
} pmu_pof_edge_t;

typedef enum {
    PMU_POF_DEBOUNCE_2T     = 0,
    PMU_POF_DEBOUNCE_4T     = 1,
} pmu_pof_debounce_t;

typedef enum {
    PMU_CP_R                = 0x1,
    PMU_CP_F                = 0x2,
    PMU_USB_PLUGIN          = 0x4,
    PMU_USB_PLUGOUT         = 0x8,
    PMU_EINT                = 0x10,
} pmu_irq_t;

typedef enum {
    PMU_CB_POF_R            = 0,
    PMU_CB_POF_F            = 1,
    PMU_CB_CP_R             = 2,
    PMU_CB_CP_F             = 3,
    PMU_CB_USB_PLUGIN       = 4,
    PMU_CB_USB_PLUGOUT      = 5,
    PMU_CB_EINT             = 6,
    PMU_CB_MAX              = 7,
} pmu_cb_t;

typedef enum{
    PMU_USER_BM             = 0,
    PMU_USER_POF            = 1,
    PMU_USER_USB            = 2,
    PMU_USER_COMP           = 3,
    PMU_USER_GPIO           = 4,
    PMU_USER_MAX            = 5,
} pmu_user_t;

typedef struct {
    void (*pmu_callback)(void *user_data);
} pmu_func_t;

typedef void (*pmu_callback_t)(void *user_data);

extern pmu_func_t pmu_cb_func[PMU_CB_MAX][PMU_USER_MAX];

typedef enum {
    PMU_EINT_CM33_DOMAIN    = 1,
    PMU_EINT_IBEX_DOMAIN    = 2,
} pmu_eint_domain_t;

typedef enum {
    PMU_RFTX_0_4_NV         = 0,
    PMU_RFTX_6_8_NV         = 1,
    PMU_RFTX_10_NV          = 2,
    PMU_RFTX_0_4_HV         = 3,
    PMU_RFTX_6_8_HV         = 4,
    PMU_RFTX_10_HV          = 5,
    PMU_VOLT_IDX_NUM        = 6,
} pmu_volt_idx_t;

typedef enum {
#if (CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_HQA)
    PMU_VOLT_TYPE_HQA,
#elif (CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_DONGLE)
    PMU_VOLT_TYPE_DONGLE,
#elif (CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_GAMING) || (CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_OFFICE)
    PMU_VOLT_TYPE_GAMING,
    PMU_VOLT_TYPE_OFFICE,
#else
    PMU_VOLT_TYPE_IOT,
#endif
    PMU_VOLT_TYPE_NUM,
} pmu_volt_type_t;

typedef struct {
    uint16_t vrf_tx;
    uint16_t vrf_rx;
    uint16_t vrf_nm;
    uint16_t vcore_nm;
} pmu_volt_t;


/* PMU COMMON */
void pmu_assert(void);
int32_t pmu_round(int32_t val1, int32_t val2);
uint16_t pmu_lerp(uint16_t volt1, uint16_t adc1, uint16_t volt2, uint16_t adc2, uint16_t volt);
void pmu_rg_dump(void);

/* PMU RG */
void pmu_strup_rg_unlock(void);
void pmu_strup_rg_lock(void);
void pmu_set_strup_rg_value(uint8_t bank, uint16_t mask, uint16_t shift, uint16_t value);
uint16_t pmu_get_strup_rg_value(uint8_t bank, uint16_t mask, uint16_t shift);
void pmu_set_strup_rg(uint8_t bank, uint16_t data);
uint16_t pmu_get_strup_rg(uint8_t bank);

/* PMU PWR */
void pmu_project_dump(void);
void pmu_volt_tab_dump(void);
void pmu_set_vio18_vout(uint16_t vio18_nm, uint16_t vio18_ret, uint16_t vio18_ret_slp);
void pmu_ret_vio18_ctrl(pmu_power_operate_t en);
void pmu_set_rftx_idx(pmu_rftx_idx_t rftx_idx);
void pmu_set_vrf_vcore(pmu_volt_idx_t volt_idx, uint16_t vrf_tx, uint16_t vrf_rx, uint16_t vrf_nm, uint16_t vcore_nm);
void pmu_volt_tab_(pmu_volt_idx_t volt_idx, uint16_t vrf_tx, uint16_t vrf_rx, uint16_t vrf_nm, uint16_t vcore_nm);
void pmu_set_volt_tab(hal_dvfs_vcore_t dvfs_sel, pmu_volt_type_t volt_sel);
void pmu_conn_rf_ctrl_sw_sel(pmu_rf_ctrl_t mode);
void pmu_volt_init(hal_dvfs_vcore_t dvfs_sel);
void pmu_volt_ctrl(hal_dvfs_vcore_t dvfs_sel);
void pmu_ext_buck_enable(pmu_power_operate_t en);
void pmu_ext_buck_volt_ctrl(void);

/* PMU IRQ */
pmu_status_t pmu_register_callback(pmu_cb_t pmu_cb, pmu_callback_t callback, pmu_user_t user);
pmu_status_t pmu_deregister_callback(pmu_cb_t pmu_cb, pmu_user_t user);

/* PMU NVKEY */
pmu_status_t pmu_get_nvkey(uint16_t id, uint8_t *ptr, uint32_t size);
pmu_status_t pmu_set_nvkey(uint16_t id, uint8_t *ptr, uint32_t size);

/* PMU INIT */
uint16_t pmu_get_power_on_reason(void) ;
uint16_t pmu_get_power_off_reason(void);
void pmu_power_off_sequence(pmu_power_stage_t stage);
void pmu_init(void);
void pmu_pinmux_init(void);

/* PMU INFO */
uint16_t pmu_get_usb_plugin_status(void);

#endif /*   HAL_PMU_MODULE_ENABLED   */
#endif /* __HAL_PMU_H__ */
