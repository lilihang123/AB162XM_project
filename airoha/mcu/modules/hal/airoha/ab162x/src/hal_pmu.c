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
#include "hal.h"

#ifdef HAL_PMU_MODULE_ENABLED
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hal_eint.h"
#include "hal_nvic.h"
#include "hal_nvic_internal.h"
#include "hal_gpt.h"
#include "hal_gpt_internal.h"
#include "hal_clock_internal.h"
#include "hal_pmu_platform.h"
#include "hal_pmu_cal.h"
#include "memory_attribute.h"
#include <soc.h>
#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>

#ifdef AIR_NVKEY_ENABLE
#include "nvkey.h"
#include "nvkey_id_def.h"
#include "hal_pmu_nvkey_struct.h"
#endif

#ifdef HAL_BAT_MODULE_ENABLED
#include "hal_bat.h"
#endif

#if defined(__EXT_BOOTLOADER__) || defined(__EXT_DA__)
#define log_pmu_info(msg, cnt, ...)
#define log_pmu_warn(msg, cnt, ...)
#define log_pmu_error(msg, cnt, ...)
#else
#define log_pmu_info(msg, cnt, ...)             printk("[HAL_PMU] "msg"\r\n", ##__VA_ARGS__)
#define log_pmu_warn(msg, cnt, ...)             printk("[HAL_PMU] "msg"\r\n", ##__VA_ARGS__)
#define log_pmu_error(msg, cnt, ...)            printk("[HAL_PMU] "msg"\r\n", ##__VA_ARGS__)
#endif

#define UNUSED(x)  ((void)(x))
//#define AIR_PMU_FULL_DUMP_ENABLE

#define PMU_BUCK_VRF_MIN_VOLT                   700
#define PMU_BUCK_VIO18_REF_VOLT                 1800
#define PMU_BUCK_VIO18_RET_REF_VOLT             1500
#if (CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_HQA)
uint16_t pmu_ldo_vcore_slp_volt               = 745;
uint16_t pmu_buck_vrf_slp_volt                = 890;
uint16_t pmu_buck_vrf_extslp1_volt            = 925;
uint16_t pmu_buck_vrf_extslp2_volt            = 720;
uint16_t pmu_ldo_vio18_nm_volt                = 1675;
uint16_t pmu_ldo_vio18_ret_volt               = 1650;
uint16_t pmu_ldo_vio18_ret_slp_volt           = 1650;
#else
uint16_t pmu_ldo_vcore_slp_volt               = 800;
#if (CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_GAMING) || (CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_OFFICE)
uint16_t pmu_buck_vrf_slp_volt                = 910;
#else
uint16_t pmu_buck_vrf_slp_volt                = 950;
#endif
uint16_t pmu_buck_vrf_extslp1_volt            = 925;
uint16_t pmu_buck_vrf_extslp2_volt            = 760;
#endif

extern int16_t vrf_offset;

#if (CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_HQA)
    uint8_t volt_type = PMU_VOLT_TYPE_HQA;
#elif (CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_DONGLE)
    uint8_t volt_type = PMU_VOLT_TYPE_DONGLE;
#elif (CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_GAMING)
    uint8_t volt_type = PMU_VOLT_TYPE_GAMING;
#elif (CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_OFFICE)
    uint8_t volt_type = PMU_VOLT_TYPE_OFFICE;
#else
    uint8_t volt_type = PMU_VOLT_TYPE_IOT;
#endif

pmu_volt_t pmu_volt_tab[PMU_VOLT_TYPE_NUM][PMU_VOLT_IDX_NUM] = {
#if (CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_HQA) //HQA
    { //rf_tx,rf_rx,rf_nm,vcore_nm
        { 895,  895,  895, 765}, //0~4dBm NV
        {1155,  895,  895, 765}, //6~8dBm NV
        {1365,  895,  895, 765}, // 10dBm NV
        {1035, 1035, 1035, 860}, //0~4dBm HV
        {1155, 1035, 1035, 860}, //6~8dBm HV
        {1365, 1035, 1035, 860}, // 10dBm HV
    },
#elif (CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_DONGLE) //DONGLE
    { //rf_tx,rf_rx,rf_nm,vcore_nm
        { 950,  950,  950, 800}, //0~4dBm NV
        {1225, 1225, 1225, 800}, //6~8dBm NV
        {1450, 1450, 1450, 800}, // 10dBm NV
        {1100, 1100, 1100, 910}, //0~4dBm HV
        {1225, 1225, 1225, 910}, //6~8dBm HV
        {1450, 1450, 1450, 910}, // 10dBm HV
    },
#elif (CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_GAMING) || (CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_OFFICE) //GAMING or OFFICE
    { //rf_tx,rf_rx,rf_nm,vcore_nm
        { 910,  910,  910, 800}, //0~4dBm NV
        {1225, 1225, 1225, 800}, //6~8dBm NV
        {1450, 1450, 1450, 800}, // 10dBm NV
        {1100, 1100, 1100, 910}, //0~4dBm HV
        {1225, 1225, 1225, 910}, //6~8dBm HV
        {1450, 1450, 1450, 910}, // 10dBm HV
    },
    { //rf_tx,rf_rx,rf_nm,vcore_nm
        { 910,  910,  910, 800}, //0~4dBm NV
        {1225,  910,  910, 800}, //6~8dBm NV
        {1450,  910,  910, 800}, // 10dBm NV
        {1100, 1100, 1100, 910}, //0~4dBm HV
        {1225, 1100, 1100, 910}, //6~8dBm HV
        {1450, 1100, 1100, 910}, // 10dBm HV
    },
#else //IOT or OTHERS
    { //rf_tx,rf_rx,rf_nm,vcore_nm
        { 950,  950,  950, 800}, //0~4dBm NV
        {1225,  950,  950, 800}, //6~8dBm NV
        {1450,  950,  950, 800}, // 10dBm NV
        {1100, 1100, 1100, 910}, //0~4dBm HV
        {1225, 1100, 1100, 910}, //6~8dBm HV
        {1450, 1100, 1100, 910}, // 10dBm HV
    },
#endif
};

pmu_func_t pmu_cb_func[PMU_CB_MAX][PMU_USER_MAX];
pmu_volt_t pmu_ref_volt = {0, 0, 0, 0};
uint8_t pmu_init_flag = 0;
uint8_t pmu_rftx_idx = PMU_RFTX_10;
uint16_t pmu_buck_vrf_ref_volt = 0;
uint8_t ext_buck_offset = 0;

/* PMU common */
void pmu_assert(void)
{
    log_pmu_error("pmu_assert, caller[0x%x]", 1, (uint32_t)__builtin_return_address(0));
    //assert(0);
}

int32_t pmu_round(int32_t val1, int32_t val2)
{
    int32_t ret = 0, tmp = 0;
    if (val2) {
        tmp = (val1 * 10) / val2;
        if (val1 > 0) {
            tmp += 5;
        } else {
            tmp -= 5;
        }

        ret = tmp / 10;
        // log_pmu_info("[PMU_CAL] round, val1[%d], val2[%d], tmp[%d], ret[%d]", 4, val1, val2, tmp, ret);
    } else {
        log_pmu_error("[PMU_CAL] pmu_round fail, denominator = 0", 0);
        pmu_assert();
    }
    return ret;
}

uint16_t pmu_lerp(uint16_t volt1, uint16_t adc1, uint16_t volt2, uint16_t adc2, uint16_t volt)
{
    int16_t adc = 0;
    int16_t volt_diff = 0;
    int16_t adc_diff = 0;

    if (volt1 > volt2) {
        volt_diff = volt1 - volt2;
        adc_diff = adc1 - adc2;
    } else {
        volt_diff = volt2 - volt1;
        adc_diff = adc2 - adc1;
    }

    if (volt > volt2) {
        adc = adc2 + pmu_round((adc_diff * (volt - volt2)), volt_diff);
    } else if (volt < volt2) {
        adc = adc2 - pmu_round((adc_diff * (volt2 - volt)), volt_diff);
    } else {
        adc = adc2;
    }
    //log_pmu_info("[PMU_CAL] lerp v1[%d], a1[%d], v2[%d], a2[%d], volt[%d], adc[%d]", 6, volt1, adc1, volt2, adc2, volt, adc);
    if (adc < 0) {
        adc = 1;
    }

    return adc;
}

void pmu_io_dbg_mux(void)
{
#if 0
    //IO DEBUG SETTING
    //6 [13:12]/5, [11:10],
    *IO_CFG_0_RTC_GPIO_MODE0 = 0x00001400;
    //21~17, [13:12] [11:10] [9:8] [7:6] [5:4] [3:2]
    *IO_CFG_0_RTC_GPIO_MODE1 = 0x00001554;
    //GPIOA17~22 = 0;
    *gpio_GPIO_MODE_C_CLR = 0x0FFFFFF0;
    //GPIOA17~22 DIR = 1;
    *gpio_GPIO_DIR_A_SET = 0x007E0000;
#endif
};

void pmu_strup_rg_unlock(void)
{
    pmu_set_strup_rg(0x38, 0xABCD);
}

void pmu_strup_rg_lock(void)
{
    pmu_set_strup_rg(0x38, 0x0000);
}

ATTR_TEXT_IN_TCM_RETENTION void pmu_set_strup_rg_value(uint8_t bank, uint16_t mask, uint16_t shift, uint16_t value)
{
    uint16_t rdata = 0, wdata = 0;
    uint16_t mask_buffer = (~(mask << shift));
    *PMU_DIG_STRUP_RG_CTRL = 0x00000000 | bank << 16;
    rdata = *PMU_DIG_STRUP_RDATA__F_STRUP_LATCH_RDATA;
    wdata = rdata & mask_buffer;
    wdata |= ((value & mask) << shift);
    *PMU_DIG_STRUP_RG_CTRL = 0x01000000 | wdata | bank << 16;
    rdata = *PMU_DIG_STRUP_RDATA__F_STRUP_LATCH_RDATA;
    if ((rdata != wdata) && ((bank < 0x21) || ((bank > 0x26) && (bank < 0x2F)) || ((bank > 0x2F) && (bank < 0x3A)))) {
        log_pmu_error("pmu_set_strup_rg_value fail, wdata[0x%X] != rdata[0x%X], bank[0x%X], mask[0x%X], shift[%d], value[0x%X]", 6,
                      wdata, rdata, bank, mask, shift, value);
    }
}

uint16_t pmu_get_strup_rg_value(uint8_t bank, uint16_t mask, uint16_t shift)
{
    uint16_t rdata = 0, mask_buffer = 0;
    mask_buffer = (mask << shift);
    *PMU_DIG_STRUP_RG_CTRL = 0x00000000 | bank << 16;
    rdata = *PMU_DIG_STRUP_RDATA__F_STRUP_LATCH_RDATA;
    rdata &= mask_buffer;
    rdata = (rdata >> shift);
    return rdata;
}

void pmu_set_strup_rg(uint8_t bank, uint16_t data)
{
    uint16_t rdata = 0;
    *PMU_DIG_STRUP_RG_CTRL = 0x01000000 | data | bank << 16;
    rdata = *PMU_DIG_STRUP_RDATA__F_STRUP_LATCH_RDATA;
    if ((data != rdata) && ((bank < 0x21) || ((bank > 0x26) && (bank < 0x2F)) || ((bank > 0x2F) && (bank < 0x3A)))) {
        log_pmu_error("pmu_set_strup_rg fail, wdata[0x%X] != rdata[0x%X], bank[0x%X]", 3, data, rdata, bank);
    }
}

uint16_t pmu_get_strup_rg(uint8_t bank)
{
    uint16_t data = 0;
    *PMU_DIG_STRUP_RG_CTRL = 0x00000000 | bank << 16;
    data = *PMU_DIG_STRUP_RDATA__F_STRUP_LATCH_RDATA;
    return data;
}

void pmu_conn_rf_ctrl_sw_sel(pmu_rf_ctrl_t mode)
{
    if ((mode != PMU_HW_MODE) && (mode != PMU_SW_MODE)) {
        log_pmu_error("pmu_conn_rf_ctrl_sw_sel fail, mode[0x%X]", 1, mode);
        return;
    }
    uint8_t rg_sel = (*PMU_DIG_CTRL1__F_CONN_RF_CTRL & 0x3);
    rg_sel |= (mode << 2);
    *PMU_DIG_CTRL1__F_CONN_RF_CTRL = rg_sel;
    log_pmu_info("pmu_conn_rf_ctrl_sw_sel, mode(0:HW, 1:SW)[0x%X], rg_sel[0x%X], result[0x%X]", 3, mode, rg_sel, *PMU_DIG_CTRL1__F_CONN_RF_CTRL);
}

/* PWR TIMING */
ATTR_TEXT_IN_TCM void pmu_timing_ctrl_vcore(uint16_t vcore_nm)
{
    uint8_t vcore_h2l = 0, vcore_l2h = 0;
    if (vcore_nm <= pmu_volt_tab[volt_type][PMU_RFTX_0_4_NV].vcore_nm) {
        vcore_h2l = 0;
        vcore_l2h = 0;
    } else if (vcore_nm <= pmu_volt_tab[volt_type][PMU_RFTX_0_4_HV].vcore_nm) {
        vcore_h2l = 4;
        vcore_l2h = 2;
    }
    *PMU_DIG_CTRL3__F_VCORE_H2L_CYCLE_OPT = vcore_h2l;
    *PMU_DIG_CTRL6__F_VCORE_L2H_CYCLE_OPT = vcore_l2h;
}

ATTR_TEXT_IN_TCM void pmu_timing_ctrl_vrf_tx(uint16_t vrf_tx)
{
    uint8_t vrf_tx_h2l = 0;
    if (vrf_tx <= 950) {
        vrf_tx_h2l = 0;
    } else if (vrf_tx <= 985) {
        vrf_tx_h2l = 1;
    } else if (vrf_tx <= 1100) {
        vrf_tx_h2l = 6;
    } else if ((vrf_tx <= 1225) || (vrf_tx <= 1450)) {
        vrf_tx_h2l = 12;
    } else {
        vrf_tx_h2l = 13;
    }
    *PMU_DIG_CTRL3__F_VRF_H2L_EXTSLP_CYCLE_OPT = vrf_tx_h2l;
}

ATTR_TEXT_IN_TCM void pmu_timing_ctrl_vrf_nm(uint16_t vrf_nm)
{
    uint8_t vrf_nm_h2l = 0, vrf_nm_l2h = 0;
    if (vrf_nm <= pmu_volt_tab[volt_type][PMU_RFTX_0_4_NV].vrf_nm) {
        vrf_nm_l2h = 0;
    } else {
        vrf_nm_l2h = 1;
    }
    *PMU_DIG_CTRL3__F_VRF_H2L_SLP_CYCLE_OPT = vrf_nm_h2l;
    *PMU_DIG_CTRL6__F_VRF_L2H_SLP_CYCLE_OPT = vrf_nm_l2h;
}

/* SPM RG CTRL */
void pmu_spm_ctrl_eint_en(void)
{
    uint8_t eint_cm33 = 0, eint_ibex = 0;
    uint32_t spm_rg = 0;

    eint_cm33 = pmu_get_strup_rg_value(0x1F, 0xF, 0);
    eint_ibex = pmu_get_strup_rg_value(0x1F, 0xF, 8);
    spm_rg = *RTC_DIG_RSV0 & 0xFFFF00FF;
    spm_rg |= ((eint_cm33 << 8) + (eint_ibex << 12));
    *RTC_DIG_RSV0 = spm_rg;
    log_pmu_info("pmu_spm_ctrl_eint_en, eint_cm33[0x%X], eint_ibex[0x%X], RTC_DIG_RSV0[0x%X]", 3, eint_cm33, eint_ibex, *RTC_DIG_RSV0);
}

ATTR_TEXT_IN_TCM void pmu_spm_ctrl_vrf_nm(uint16_t vrf_nm)
{
    uint32_t spm_rg = 0;
    spm_rg = *RTC_DIG_RSV0 & 0xFFFFFFFB;
    if (vrf_nm > 1225) {
        spm_rg |= 0x4;
    }
    *RTC_DIG_RSV0 = spm_rg;
    //log_pmu_info("pmu_spm_ctrl_vrf_nm, vrf_nm[%d], RTC_DIG_RSV0[0x%X]", 2, vrf_nm, *RTC_DIG_RSV0);
}

void pmu_spm_ctrl_rf_tx(uint16_t rf_tx_10dbm)
{
    uint32_t spm_rg = 0;
    spm_rg = *RTC_DIG_RSV0 & 0xFFFFFFFD;
    if (rf_tx_10dbm) {
        spm_rg |= 0x2;
    }
    *RTC_DIG_RSV0 = spm_rg;
    log_pmu_info("pmu_spm_rg_ctrl_rftx, rf_tx_10dbm[%d], RTC_DIG_RSV0[0x%X]", 2, rf_tx_10dbm, *RTC_DIG_RSV0);
}

void pmu_spm_ctrl_ret_vio18(pmu_power_operate_t en)
{
    uint32_t spm_rg = 0;
    spm_rg = *RTC_DIG_RSV0 & 0xFFFFFFFE;
    if (en == PMU_ON) {
        spm_rg |= 0x1;
    }
    *RTC_DIG_RSV0 = spm_rg;
    log_pmu_info("pmu_spm_ctrl_ret_vio18, en[%d], RTC_DIG_RSV0[0x%X]", 2, en, *RTC_DIG_RSV0);
}

/* PMU PWR */
void pmu_set_slp_vrf_volt(uint16_t vrf_slp, uint16_t vrf_extslp1, uint16_t vrf_extslp2)
{
    uint16_t vrf_min = PMU_BUCK_VRF_MIN_VOLT;
    int16_t rg_vrf_slp     = (vrf_slp - vrf_min) / 5 + vrf_offset;
    int16_t rg_vrf_extslp1 = (vrf_extslp1 - vrf_min) / 5 + vrf_offset;
    int16_t rg_vrf_extslp2 = (vrf_extslp2 - vrf_min) / 5 + vrf_offset;
    if (rg_vrf_slp < 0) {
        rg_vrf_slp = 0;
    }
    if (rg_vrf_extslp1 < 0) {
        rg_vrf_extslp1 = 0;
    }
    if (rg_vrf_extslp2 < 0) {
        rg_vrf_extslp2 = 0;
    }
    *PMU_DIG_CTRL7__F_VRF_VSEL_SLP     = rg_vrf_slp;
    *PMU_DIG_CTRL7__F_VRF_VSEL_EXTSLP1 = rg_vrf_extslp1;
    pmu_buck_rf_ulp_trim(vrf_extslp2, rg_vrf_extslp2);
    log_pmu_info("pmu_set_slp_vrf_volt, vrf_slp[%d], vrf_extslp1[%d], vrf_extslp2[%d]", 3, vrf_slp, vrf_extslp1, vrf_extslp2);
    log_pmu_info("pmu_set_slp_vrf_volt, rg_vrf_slp[0x%X], rg_vrf_extslp1[0x%X], rg_vrf_extslp2[0x%X]", 3,
                 *PMU_DIG_CTRL7__F_VRF_VSEL_SLP, *PMU_DIG_CTRL7__F_VRF_VSEL_EXTSLP1, *PMU_DIG_CTRL7__F_VRF_VSEL_EXTSLP2);
}

ATTR_TEXT_IN_TCM void pmu_set_vcore_volt(uint16_t vcore_nm)
{
    uint16_t vcore_min = 540;
    *PMU_DIG_CTRL12__F_VCORE_VSEL_NORM = (vcore_nm - vcore_min) / 5;
    pmu_timing_ctrl_vcore(vcore_nm);
    //log_pmu_info("pmu_set_vcore_volt, vcore_nm[%d]", 1, vcore_nm);
}

void pmu_set_slp_vcore_volt(uint16_t vcore_slp)
{
    uint16_t vcore_min = 540;
    *PMU_DIG_CTRL9__F_VCORE_VSEL_SLP = (vcore_slp - vcore_min) / 5;
    log_pmu_info("pmu_set_slp_vcore_volt, vcore_slp[%d]", 1, vcore_slp);
}

void pmu_set_vio18_vout(uint16_t vio18_nm, uint16_t vio18_ret, uint16_t vio18_ret_slp)
{
    uint16_t rg_vio18_nm = 0, rg_vio18_ret = 0, rg_vio18_ret_slp = 0;

    vio18_vout_t otp_vio18 = {0xFF, 0x40, 0x10};
    if (pmu_get_otp(OTP_VIO18_VOUT_ADDR, (uint8_t *)&otp_vio18, sizeof(otp_vio18)) != PMU_STATUS_SUCCESS) {
        return;
    }
    vio18_ret_vout_t otp_vio18_ret = {0xFF, 0x16, 0x1A};
    if (pmu_get_otp(OTP_VIO18_RET_VOUT_ADDR, (uint8_t *)&otp_vio18_ret, sizeof(otp_vio18_ret)) != PMU_STATUS_SUCCESS) {
        return;
    }
    rg_vio18_nm      = (otp_vio18.NM_VOTRIM_1p8 + ((vio18_nm - PMU_BUCK_VIO18_REF_VOLT) * 100 / 625));
    rg_vio18_ret     = (otp_vio18_ret.RET_VOTRIM_1p5 - ((vio18_ret - PMU_BUCK_VIO18_RET_REF_VOLT) / 25));
    rg_vio18_ret_slp = (otp_vio18_ret.RET_VOTRIM_1p8 - ((vio18_ret_slp - PMU_BUCK_VIO18_REF_VOLT) / 25));

    pmu_set_strup_rg_value(0x36, 0x7F, 0, rg_vio18_nm);
    pmu_set_strup_rg_value(0x34, 0x1F, 0, rg_vio18_ret);
    *PMU_DIG_CTRL10__F_VLDO18_RET_VSEL_NORM = rg_vio18_ret;
    pmu_set_strup_rg_value(0x34, 0x1F, 8, rg_vio18_ret_slp);
    *PMU_DIG_CTRL10__F_VLDO18_RET_VSEL_SLP = rg_vio18_ret_slp;
    log_pmu_info("pmu_set_vio18_vout, vio18_nm[%d], vio18_ret[%d], vio18_ret_slp[%d], rg_vio18_nm[0x%X], rg_vio18_ret0x%X], rg_vio18_ret_slp[0x%X]", 6,
                 vio18_nm, vio18_ret, vio18_ret_slp, rg_vio18_nm, rg_vio18_ret, rg_vio18_ret_slp);
}

ATTR_TEXT_IN_TCM uint8_t pmu_get_volt_tab_idx(uint8_t dvfs_sel)
{
    uint8_t volt_idx = 0;

    if (dvfs_sel == HAL_DVFS_VCORE_HIGH) {
        if (pmu_rftx_idx == PMU_RFTX_0_4) {
            volt_idx = PMU_RFTX_0_4_HV;
        } else if (pmu_rftx_idx == PMU_RFTX_6_8) {
            volt_idx = PMU_RFTX_6_8_HV;
        } else {
            volt_idx = PMU_RFTX_10_HV;
        }
    } else if (dvfs_sel == HAL_DVFS_VCORE_MID) {
        if (pmu_rftx_idx == PMU_RFTX_0_4) {
            volt_idx = PMU_RFTX_0_4_NV;
        } else if (pmu_rftx_idx == PMU_RFTX_6_8) {
            volt_idx = PMU_RFTX_6_8_NV;
        } else {
            volt_idx = PMU_RFTX_10_NV;
        }
    } else {
        log_pmu_error("pmu_get_volt_tab_idx fail, dvfs_sel[%d] >= HAL_DVFS_VCORE_MAX(2)", 1, dvfs_sel);
        pmu_assert();
    }
    //log_pmu_info("pmu_get_volt_table_idx, dvfs_sel[%d], volt_idx[%d]", 2, dvfs_sel, volt_idx);
    return volt_idx;
}

void pmu_project_dump(void)
{
#if CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_HQA
    log_pmu_info("pmu_project_dump, HQA_SLT_VOLT_CONFIG", 0);
#elif CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_DONGLE
    log_pmu_info("pmu_project_dump, DONGLE_VOLT_CONFIG", 0);
#elif CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_GAMING
    log_pmu_info("pmu_project_dump, GAMING_VOLT_CONFIG", 0);
#elif CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_OFFICE
    log_pmu_info("pmu_project_dump, OFFICE_VOLT_CONFIG", 0);
#else
    log_pmu_info("pmu_project_dump, IOT_OTHERS_VOLT_ONFIG", 0);
#endif
}

void pmu_volt_tab_dump(void)
{
    log_pmu_info("pmu_volt_tab_dump, PMU_RFTX_0_4_NV, vrf_tx[%4d], vrf_rx[%4d], vrf_nm[%4d], vcore_nm[%4d]", 4,
                 pmu_volt_tab[volt_type][0].vrf_tx, pmu_volt_tab[volt_type][0].vrf_rx, pmu_volt_tab[volt_type][0].vrf_nm, pmu_volt_tab[volt_type][0].vcore_nm);
    log_pmu_info("pmu_volt_tab_dump, PMU_RFTX_6_8_NV, vrf_tx[%4d], vrf_rx[%4d], vrf_nm[%4d], vcore_nm[%4d]", 4,
                 pmu_volt_tab[volt_type][1].vrf_tx, pmu_volt_tab[volt_type][1].vrf_rx, pmu_volt_tab[volt_type][1].vrf_nm, pmu_volt_tab[volt_type][1].vcore_nm);
    log_pmu_info("pmu_volt_tab_dump, PMU_RFTX_10_NV,  vrf_tx[%4d], vrf_rx[%4d], vrf_nm[%4d], vcore_nm[%4d]", 4,
                 pmu_volt_tab[volt_type][2].vrf_tx, pmu_volt_tab[volt_type][2].vrf_rx, pmu_volt_tab[volt_type][2].vrf_nm, pmu_volt_tab[volt_type][2].vcore_nm);
    log_pmu_info("pmu_volt_tab_dump, PMU_RFTX_0_4_HV, vrf_tx[%4d], vrf_rx[%4d], vrf_nm[%4d], vcore_nm[%4d]", 4,
                 pmu_volt_tab[volt_type][3].vrf_tx, pmu_volt_tab[volt_type][3].vrf_rx, pmu_volt_tab[volt_type][3].vrf_nm, pmu_volt_tab[volt_type][3].vcore_nm);
    log_pmu_info("pmu_volt_tab_dump, PMU_RFTX_6_8_HV, vrf_tx[%4d], vrf_rx[%4d], vrf_nm[%4d], vcore_nm[%4d]", 4,
                 pmu_volt_tab[volt_type][4].vrf_tx, pmu_volt_tab[volt_type][4].vrf_rx, pmu_volt_tab[volt_type][4].vrf_nm, pmu_volt_tab[volt_type][4].vcore_nm);
    log_pmu_info("pmu_volt_tab_dump, PMU_RFTX_10_HV,  vrf_tx[%4d], vrf_rx[%4d], vrf_nm[%4d], vcore_nm[%4d]", 4,
                 pmu_volt_tab[volt_type][5].vrf_tx, pmu_volt_tab[volt_type][5].vrf_rx, pmu_volt_tab[volt_type][5].vrf_nm, pmu_volt_tab[volt_type][5].vcore_nm);
}

void pmu_set_ref_volt(uint8_t volt_idx)
{
    uint8_t num = 0;
    num = (PMU_VOLT_IDX_NUM / 2);
    if (volt_idx >= num) {
        volt_idx -= num;
    }
    pmu_ref_volt.vrf_tx   = pmu_volt_tab[volt_type][volt_idx].vrf_tx;
    pmu_ref_volt.vrf_rx   = pmu_volt_tab[volt_type][volt_idx].vrf_rx;
    pmu_ref_volt.vrf_nm   = pmu_volt_tab[volt_type][volt_idx].vrf_nm;
    pmu_ref_volt.vcore_nm = pmu_volt_tab[volt_type][volt_idx].vcore_nm;
    pmu_buck_vrf_ref_volt = pmu_volt_tab[volt_type][PMU_RFTX_0_4_HV].vrf_nm;
    log_pmu_info("pmu_set_ref_volt, vrf_tx[%d], vrf_rx[%d], vrf_nm[%d], vcore_nm[%d], pmu_buck_vrf_ref_volt[%d]", 5,
                 pmu_ref_volt.vrf_tx, pmu_ref_volt.vrf_rx, pmu_ref_volt.vrf_nm, pmu_ref_volt.vcore_nm, pmu_buck_vrf_ref_volt);
}

void pmu_volt_init(hal_dvfs_vcore_t dvfs_sel)
{
    uint16_t volt_idx = 0, vrf_tx = 0, vrf_rx = 0, vrf_nm = 0, vcore_nm = 0, rf_tx_10dbm = 0, vrf_min = PMU_BUCK_VRF_MIN_VOLT;

    volt_idx = pmu_get_volt_tab_idx(dvfs_sel);
    vrf_tx   = pmu_volt_tab[volt_type][volt_idx].vrf_tx;
    vrf_rx   = pmu_volt_tab[volt_type][volt_idx].vrf_rx;
    vrf_nm   = pmu_volt_tab[volt_type][volt_idx].vrf_nm;
    vcore_nm = pmu_volt_tab[volt_type][volt_idx].vcore_nm;

    pmu_volt_tab_dump();

    pmu_set_ref_volt(volt_idx);

    *PMU_DIG_CTRL8__F_VRF_VSEL_NORM = (vrf_nm - vrf_min) / 5 + vrf_offset;
    *PMU_DIG_CTRL7__F_VRF_VSEL_RX   = (vrf_rx - vrf_min) / 5 + vrf_offset;
    *PMU_DIG_CTRL8__F_VRF_VSEL_TX   = (vrf_tx - vrf_min) / 5 + vrf_offset;
    pmu_timing_ctrl_vrf_tx(vrf_tx);
    pmu_timing_ctrl_vrf_nm(vrf_nm);

    pmu_set_vcore_volt(vcore_nm);
    pmu_set_slp_vrf_volt(pmu_buck_vrf_slp_volt, pmu_buck_vrf_extslp1_volt, pmu_buck_vrf_extslp2_volt);
    pmu_set_slp_vcore_volt(pmu_ldo_vcore_slp_volt);

    *PMU_DIG_CTRL5__F_VCORE_ON_CYCLE_OPT = 2;

    if (pmu_rftx_idx == PMU_RFTX_10) {
        rf_tx_10dbm = 1;
    }
    pmu_spm_ctrl_rf_tx(rf_tx_10dbm);//default RF TX 10dBm
    pmu_spm_ctrl_vrf_nm(vrf_nm);    //default vrf_nm = 1.45V

#if (CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_HQA)
    pmu_set_vio18_vout(pmu_ldo_vio18_nm_volt, pmu_ldo_vio18_ret_volt, pmu_ldo_vio18_ret_slp_volt);
#endif
    log_pmu_info("pmu_volt_init, vrf_tx[%d], vrf_rx[%d], vrf_nm[%d], vcore_nm[%d], vrf_offset[%d]", 5, vrf_tx, vrf_rx, vrf_nm, vcore_nm, vrf_offset);
    log_pmu_info("pmu_volt_init, vrf_tx_rg[0x%X], vrf_rx_rg[0x%X], vrf_nm_rg[0x%X], vcore_nm_rg[0x%X], dvfs_sel[%d]", 5,
                 *PMU_DIG_CTRL8__F_VRF_VSEL_TX, *PMU_DIG_CTRL7__F_VRF_VSEL_RX, *PMU_DIG_CTRL8__F_VRF_VSEL_NORM, *PMU_DIG_CTRL12__F_VCORE_VSEL_NORM, dvfs_sel);
}

ATTR_TEXT_IN_TCM void pmu_volt_ctrl(hal_dvfs_vcore_t dvfs_sel)
{
    uint16_t volt_idx = 0, vrf_tx = 0, vrf_rx = 0, vrf_nm = 0, vcore_nm = 0, vrf_min = PMU_BUCK_VRF_MIN_VOLT;

    volt_idx = pmu_get_volt_tab_idx(dvfs_sel);

    if (dvfs_sel == HAL_DVFS_VCORE_HIGH) {
        if (pmu_ref_volt.vrf_tx < pmu_buck_vrf_ref_volt) {
            vrf_nm = pmu_buck_vrf_ref_volt;
            vrf_tx = pmu_buck_vrf_ref_volt;
        } else {
            vrf_nm = pmu_ref_volt.vrf_tx;
            vrf_tx = pmu_ref_volt.vrf_tx;
        }
        if (pmu_ref_volt.vrf_rx < pmu_buck_vrf_ref_volt) {
            vrf_rx = pmu_buck_vrf_ref_volt;
        } else {
            vrf_rx = pmu_ref_volt.vrf_rx;
        }
    } else if (dvfs_sel == HAL_DVFS_VCORE_MID) {
        if (pmu_ref_volt.vrf_tx < pmu_buck_vrf_ref_volt) {
            vrf_nm = pmu_buck_vrf_ref_volt;
        } else {
            vrf_nm = pmu_ref_volt.vrf_tx;
        }
        vrf_rx = pmu_ref_volt.vrf_rx;
        vrf_tx = pmu_ref_volt.vrf_tx;
    } else {
        log_pmu_error("pmu_volt_ctrl fail, dvfs_sel[%d] >= HAL_DVFS_VCORE_MAX(2)", 1, dvfs_sel);
        pmu_assert();
        return;
    }
    vcore_nm = pmu_volt_tab[volt_type][volt_idx].vcore_nm;
    //log_pmu_info("pmu_volt_ctrl step, vrf_tx[%d], vrf_rx[%d], vrf_nm[%d], vcore_nm[%d]", 4, vrf_tx, vrf_rx, vrf_nm, vcore_nm);

    *PMU_DIG_CTRL8__F_VRF_VSEL_NORM = (vrf_nm - vrf_min) / 5 + vrf_offset - ext_buck_offset;
    *PMU_DIG_CTRL8__F_SW_VRF_VSEL   = 0x1;
    *PMU_DIG_CTRL7__F_VRF_VSEL_RX   = (vrf_rx - vrf_min) / 5 + vrf_offset - ext_buck_offset;
    *PMU_DIG_CTRL8__F_VRF_VSEL_TX   = (vrf_tx - vrf_min) / 5 + vrf_offset - ext_buck_offset;
    pmu_timing_ctrl_vrf_tx(vrf_tx);
    pmu_timing_ctrl_vrf_nm(vrf_nm);
    if (dvfs_sel == HAL_DVFS_VCORE_HIGH) {
        hal_gpt_delay_us(100);
    }
    pmu_set_vcore_volt(vcore_nm);
    if (dvfs_sel == HAL_DVFS_VCORE_HIGH) {
        *PMU_DIG_CTRL8__F_SW_BUCK_EXTSLP_VCORE_DMY_LOAD_EN = 0x3;
    }
    hal_gpt_delay_us(300);
    if (dvfs_sel == HAL_DVFS_VCORE_HIGH) {
        *PMU_DIG_CTRL8__F_SW_BUCK_EXTSLP_VCORE_DMY_LOAD_EN = 0x0;
    }
    *PMU_DIG_CTRL8__F_SW_VRF_VSEL = 0x0;
    if (dvfs_sel == HAL_DVFS_VCORE_HIGH) {
        if (pmu_ref_volt.vrf_nm < pmu_buck_vrf_ref_volt) {
            vrf_nm = pmu_buck_vrf_ref_volt;
        } else {
            vrf_nm = pmu_ref_volt.vrf_tx;
        }
    } else {
        vrf_nm = pmu_ref_volt.vrf_nm;
    }
    *PMU_DIG_CTRL8__F_VRF_VSEL_NORM = (vrf_nm - vrf_min) / 5 + vrf_offset - ext_buck_offset;
    pmu_timing_ctrl_vrf_nm(vrf_nm);
    pmu_spm_ctrl_vrf_nm(vrf_nm);
    //log_pmu_info("pmu_volt_ctrl, vrf_tx[%d], vrf_rx[%d], vrf_nm[%d], vcore_nm[%d], vrf_offset[%d]", 5, vrf_tx, vrf_rx, vrf_nm, vcore_nm, vrf_offset);
    //log_pmu_info("pmu_volt_ctrl, vrf_tx_rg[0x%X], vrf_rx_rg[0x%X], vrf_nm_rg[0x%X], vcore_nm_rg[0x%X]", 4,
                 //*PMU_DIG_CTRL8__F_VRF_VSEL_TX, *PMU_DIG_CTRL7__F_VRF_VSEL_RX, *PMU_DIG_CTRL8__F_VRF_VSEL_NORM, *PMU_DIG_CTRL12__F_VCORE_VSEL_NORM);
}

void pmu_ext_buck_enable(pmu_power_operate_t en)
{
    if (en == PMU_OFF) {
        ext_buck_offset = 0;
    } else {
        ext_buck_offset = 40;
    }
    log_pmu_info("pmu_ext_buck_enable, en[%d], ext_buck_offset[%d]", 2, en, ext_buck_offset);
}

ATTR_TEXT_IN_TCM void pmu_ext_buck_volt_ctrl(void)
{
    hal_dvfs_vcore_t dvfs_sel = hal_dvfs_get_cur_vcore();
    pmu_volt_ctrl(dvfs_sel);
}

void pmu_ret_vio18_ctrl(pmu_power_operate_t en)
{
    if (en == PMU_ON) {
        *PMU_DIG_CTRL10__F_EXTSLP_VIO18_OFF             = 0;    //extslp ret_vio18 on
        *PMU_DIG_CTRL4__F_VLDO18_EXTSLP_ON_CYCLE_OPT    = 5;    //0~3:17~20T//4~7:34~37T, def:5, ret500us(1), on:1000ms(5)
        pmu_set_strup_rg_value(0x2D, 0x1, 9, 0);                //VIO18_DEEPSLP_OFF on
        log_pmu_info("pmu_ret_vio18_ctrl, enable", 0);
    } else {
        *PMU_DIG_CTRL10__F_EXTSLP_VIO18_OFF             = 1;    //extslp ret_vio18 off
        *PMU_DIG_CTRL4__F_VLDO18_EXTSLP_ON_CYCLE_OPT    = 1;    //0~3:17~20T//4~7:34~37T, def:5, ret500us(1), on:1000ms(5)
        pmu_set_strup_rg_value(0x2D, 0x1, 9, 1);                //VIO18_DEEPSLP_OFF off
        log_pmu_info("pmu_ret_vio18_ctrl, disable", 0);
    }
    pmu_spm_ctrl_ret_vio18(en);
}

void pmu_ret_vio18_init(void)
{
#if defined (CONFIG_AIR_PMU_RET_VIO18_ENABLE)
    pmu_ret_vio18_ctrl(PMU_ON);
#else
    pmu_ret_vio18_ctrl(PMU_OFF);
#endif
}

void pmu_vrf_lpm_en(void)
{
    uint8_t vrf_rg = 0;
    vrf_rg = *PMU_ANA_CON0__F_VRF_RSV0 | 0x2;
    *PMU_ANA_CON0__F_VRF_RSV0 = vrf_rg;
}

void pmu_set_rftx_idx(pmu_rftx_idx_t rftx_idx)
{
    pmu_rftx_idx = rftx_idx;
    log_pmu_info("pmu_set_rftx_idx, pmu_rftx_idx[%d]", 1, pmu_rftx_idx);
}

void pmu_set_vrf_vcore(pmu_volt_idx_t volt_idx, uint16_t vrf_tx, uint16_t vrf_rx, uint16_t vrf_nm, uint16_t vcore_nm)
{
    if (volt_idx >= PMU_VOLT_IDX_NUM) {
        log_pmu_error("pmu_set_vrf_vcore fail, volt_idx[%d] >= PMU_VOLT_IDX_NUM[%d]", 2, volt_idx, PMU_VOLT_IDX_NUM);
        return;
    }
    pmu_volt_tab[volt_type][volt_idx].vrf_tx   = vrf_tx;
    pmu_volt_tab[volt_type][volt_idx].vrf_rx   = vrf_rx;
    pmu_volt_tab[volt_type][volt_idx].vrf_nm   = vrf_nm;
    pmu_volt_tab[volt_type][volt_idx].vcore_nm = vcore_nm;
    log_pmu_info("pmu_set_vrf_vcore, volt_idx[%d], vrf_tx[%d], vrf_rx[%d], vrf_nm[%d], vcore_nm[%d]", 5, volt_idx, vrf_tx, vrf_rx, vrf_nm, vcore_nm);
}

#if (CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_GAMING) || (CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_OFFICE)
void pmu_set_volt_tab(hal_dvfs_vcore_t dvfs_sel, pmu_volt_type_t volt_sel)
{
    if (volt_sel == volt_type) {
        log_pmu_warn("pmu_set_volt_tab, volt_sel[%d] = volt_type[%d]", 2, volt_sel, volt_type);
        return;
    }
    if (volt_sel == PMU_VOLT_TYPE_GAMING) {
        log_pmu_info("pmu_project_dump, GAMING_VOLT_CONFIG", 0);
    } else if (volt_sel == PMU_VOLT_TYPE_OFFICE) {
        log_pmu_info("pmu_project_dump, OFFICE_VOLT_CONFIG", 0);
    } else {
        log_pmu_error("pmu_set_volt_tab fail, volt_sel[%d], PMU_VOLT_TYPE_GAMING[%d], PMU_VOLT_TYPE_OFFICE[%d]", 3,
                      volt_sel, PMU_VOLT_TYPE_GAMING, PMU_VOLT_TYPE_OFFICE);
        return;
    }
    volt_type = volt_sel;
    pmu_volt_init(dvfs_sel);
}
#endif

void pmu_set_slt_volt(hal_dvfs_vcore_t dvfs_sel)
{
    pmu_ldo_vcore_slp_volt           = 745;
    pmu_buck_vrf_slp_volt            = 890;
    pmu_buck_vrf_extslp2_volt        = 795;
#if (CONFIG_AIR_PMU_VOLT_TYPE == PMU_CONFIG_HQA)
    pmu_ldo_vio18_nm_volt            = 1675;
    pmu_ldo_vio18_ret_volt           = 1650;
    pmu_ldo_vio18_ret_slp_volt       = 1650;
#endif
    pmu_set_vrf_vcore(PMU_RFTX_0_4_NV,  895,  895,  895, 750);//DVFS NV : vrf_tx, vrf_rx, vrf_nm, vcore_nm
    pmu_set_vrf_vcore(PMU_RFTX_6_8_NV, 1155,  895,  895, 750);
    pmu_set_vrf_vcore(PMU_RFTX_10_NV,  1365,  895,  895, 750);
    pmu_set_vrf_vcore(PMU_RFTX_0_4_HV, 1035, 1035, 1035, 855);//DVFS HV : vrf_tx, vrf_rx, vrf_nm, vcore_nm
    pmu_set_vrf_vcore(PMU_RFTX_6_8_HV, 1155, 1035, 1035, 855);
    pmu_set_vrf_vcore(PMU_RFTX_10_HV,  1365, 1035, 1035, 855);
    pmu_set_rftx_idx(PMU_RFTX_0_4);
    pmu_volt_tab_dump();
    pmu_volt_init(dvfs_sel);
}

/* PMU OVP */
void pmu_hw_ovp_init(void)
{
    pmu_set_strup_rg_value(0xF, 0xFF, 0, 0x99);
    hal_gpt_delay_ms(1);
    pmu_set_strup_rg_value(0xF, 0xFF, 0, 0x77);
}

void pmu_hw_ovp_enable(pmu_power_operate_t en)
{
    uint16_t val = 0;
    if (en == PMU_ON) {
        val = 0x0;
    } else {
        val = 0x3;
    }
    pmu_set_strup_rg_value(0x2C, 0x3, 4, val);//OVP_NOCLDO_FORCE_OFF, OVP_VIO_FORCE_OFF
}

/* PMU PG */
void pmu_pg_ctrl(pmu_power_operate_t en)
{
    uint16_t val = 0;
    uint16_t vio18_force_on = pmu_get_strup_rg_value(0x2D, 0x1, 6);
    if (vio18_force_on == PMU_ON) {
        log_pmu_error("pmu_pg_init_ctrl fail, vio18_force_on = 1", 0);
        return;
    }
    if (en == PMU_ON) {
        val = 0x7;
    }
    pmu_set_strup_rg_value(0x2C, 0x7, 0, val);
}

/* PMU IRQ */
pmu_status_t pmu_register_callback(pmu_cb_t pmu_cb, pmu_callback_t callback, pmu_user_t user)
{
    if ((pmu_cb >= PMU_CB_MAX) || (callback == NULL) || (user >= PMU_USER_MAX)) {
        log_pmu_error("pmu_register_callback fail, pmu_cb[%d], callback[0x%X], user[%d]", 3, pmu_cb, callback, user);
        pmu_assert();
        return PMU_STATUS_INVALID_PARAMETER;
    }
    pmu_cb_func[pmu_cb][user].pmu_callback = callback;
    log_pmu_info("pmu_register_callback ok, pmu_cb[%d], user[%d]", 2, pmu_cb, user);
    return PMU_STATUS_SUCCESS;
}

pmu_status_t pmu_deregister_callback(pmu_cb_t pmu_cb, pmu_user_t user)
{
    if ((pmu_cb >= PMU_CB_MAX) || (user >= PMU_USER_MAX)) {
        log_pmu_error("pmu_deregister_callback fail, pmu_cb[%d], user[%d]", 2, pmu_cb, user);
        pmu_assert();
        return PMU_STATUS_INVALID_PARAMETER;
    }
    pmu_cb_func[pmu_cb][user].pmu_callback = NULL;
    log_pmu_info("pmu_deregister_callback ok, pmu_cb[%d], user[%d]", 2, pmu_cb, user);
    return PMU_STATUS_SUCCESS;
}

void pmu_gpio_get_eint_status(void)
{
    log_pmu_info("pmu_gpio_get_eint_status, EINT_GPIO_RAW_STA0[0x%X], EINT_GPIO_RAW_STA1[0x%X], EINT_GPIO_RAW_STA2[0x%X]", 3,
                 pmu_get_strup_rg(0x23), pmu_get_strup_rg(0x24), pmu_get_strup_rg(0x25));
}

void pmu_gpio_eint_ctrl(void)
{
    // *IO_CFG_0_RTC_IN_EN    = *SPM_CFG_DUMMY_REG_C;
    // *IO_CFG_1_RTC_IN_EN    = *SPM_CFG_DUMMY_REG_D;
    *PMU_DIG_STRUP_RG_CTRL = 0x01230008;                          //Clear All[3]
    *PMU_DIG_STRUP_RG_CTRL = 0x01220010;                          //MASK CLR[4]
}

void pmu_irq_pof_debounce_ctrl(pmu_power_operate_t en, pmu_pof_debounce_t sel)
{
    uint8_t val = (sel << 1) + en;
    *PMU_DIG_INT_CTRL0__F_INT_DEB_VBAT_POF          = val;        //[1]:sel(0:2T, 1:4T), [0]:en(debounce enable/disable)
    log_pmu_info("pmu_irq_pof_debounce_ctrl, en[%d], sel[%d](0:2T, 1:4T)", 2, en, sel);
}

void pmu_irq_pof_enable(uint16_t domain, uint16_t irq_sel)
{
    *PMU_DIG_INT_CTRL0__F_INT_DOMAIN_EN_VBAT        = domain;     //[1]:IBEX, [0]:CM33, only choose one
    pmu_irq_pof_debounce_ctrl(PMU_OFF, PMU_POF_DEBOUNCE_2T);      //debounce disable, debounce time = 2T
    *PMU_ANA_CON6__F_VBAT_POF_VSENS_SEL             = 0x0;        //VBAT < 1.7V trigger POF falling IRQ
    *PMU_DIG_INT_CTRL1__F_INT_EN_VBAT_POF           = irq_sel;    //[1]:raising edge enable, [0]:falling edge enable
    hal_gpt_delay_us(200);
    *PMU_ANA_CON6__F_VBAT_POF_CTRL                  = 0x1;        //[0]:POF COMP EN = 1, [1]:HYS SEL = 0(0:50mV, 1:100mV)
    hal_gpt_delay_ms(1);
    *PMU_DIG_INT_CTRL1__F_INT_MASK_VBAT_POF         = 0x0;        //[1]:raising edge mask enable, [0]:falling edge mask enable
    log_pmu_info("pmu_irq_pof_enable, domain[%d](1:cm33, 2:ibex), irq_sel[0x%X], rg_044[0x%X], rg_048[0x%X], rg_078[0x%X]", 5,
                 domain, irq_sel, *PMU_DIG_INT_CTRL0, *PMU_DIG_INT_CTRL1, *PMU_ANA_CON6);
}

void pmu_irq_pof_disable(uint16_t irq_sel)
{
    *PMU_DIG_INT_CTRL1__F_INT_MASK_VBAT_POF         = irq_sel;    //[1]:raising edge mask enable, [0]:falling edge mask enable
    *PMU_ANA_CON6__F_VBAT_POF_CTRL                  = 0x0;        //POF COMP EN = 0, HYS SEL = 0
    log_pmu_info("pmu_irq_pof_disable", 0);
}

void pmu_irq_pof_clear(void)
{
    uint8_t pof_irq_f = *PMU_DIG_INT_STATUS__F_INT_RAW_STATUS_VBAT_POF_R;
    uint8_t pof_irq_r = *PMU_DIG_INT_STATUS__F_INT_RAW_STATUS_VBAT_POF_F;
    if ((pof_irq_f == 0) && (pof_irq_r == 0)) {
        return;
    }
    log_pmu_info("pmu_irq_pof_clear, rg_04C[0x%X]", 1, *PMU_DIG_INT_STATUS);
    if (pof_irq_f != 0) {
        *PMU_DIG_INT_STATUS__F_INT_RAW_STATUS_VBAT_POF_R = 0x1;
    }
    if (pof_irq_r != 0) {
        *PMU_DIG_INT_STATUS__F_INT_RAW_STATUS_VBAT_POF_F = 0x1;
    }
    for (uint8_t i = 0; i < 64; i++) {
        if ((*PMU_DIG_INT_STATUS__F_INT_RAW_STATUS_VBAT_POF_R == 0) && (*PMU_DIG_INT_STATUS__F_INT_RAW_STATUS_VBAT_POF_F == 0)) {
            break;
        } else if (i >= 63) {
            log_pmu_error("pmu_irq_pof_clear fail, pof_irq_f[%d], pof_irq_r[%d]", 2,
                          *PMU_DIG_INT_STATUS__F_INT_RAW_STATUS_VBAT_POF_R, *PMU_DIG_INT_STATUS__F_INT_RAW_STATUS_VBAT_POF_F);
            pmu_assert();
        }
    }
    if (pof_irq_f != 0) {
        log_pmu_info("pmu_irq_pof_clear, pof_falling", 0);
        if (pmu_cb_func[PMU_CB_POF_F][PMU_USER_POF].pmu_callback) {
            pmu_cb_func[PMU_CB_POF_F][PMU_USER_POF].pmu_callback(NULL);
        }
    }
    if (pof_irq_r != 0) {
        log_pmu_info("pmu_irq_pof_clear, pof_raising", 0);
        if (pmu_cb_func[PMU_CB_POF_R][PMU_USER_POF].pmu_callback) {
            pmu_cb_func[PMU_CB_POF_R][PMU_USER_POF].pmu_callback(NULL);
        }
    }
}

void pmu_irq_usb_comp_enable(uint16_t domain, uint16_t irq_sel)
{
    uint16_t bank_1F = pmu_get_strup_rg(0x1F);
    if (domain == PMU_EINT_CM33_DOMAIN) {
        bank_1F |= irq_sel;
    } else {
        bank_1F |= (irq_sel << 8);
    }
    pmu_set_strup_rg(0x1F, bank_1F);//domain enable
    pmu_set_strup_rg(0x26, irq_sel);//clear usb comp irq
    pmu_set_strup_rg(0x22, irq_sel);//clear usb comp irq mask and read bank_20 to check status
    log_pmu_info("pmu_irq_usb_comp_enable, domain[%d](1:cm33, 2:ibex), irq_sel[0x%X], bank_1F[0x%X], bank_20[0x%X], bank_22[0x%X], bank_26[0x%X]", 6,
                 domain, irq_sel, pmu_get_strup_rg(0x1F), pmu_get_strup_rg(0x20), pmu_get_strup_rg(0x22), pmu_get_strup_rg(0x26));
    pmu_spm_ctrl_eint_en();
}

void pmu_irq_usb_comp_disable(uint16_t irq_sel)
{
    pmu_set_strup_rg(0x21, irq_sel);//set usb irq mask
    pmu_set_strup_rg(0x26, irq_sel);//clear usb irq
    log_pmu_info("pmu_irq_usb_comp_disable", 0);
}

void pmu_irq_usb_comp_clear(uint16_t irq_sel)
{
    uint16_t bank_26 = pmu_get_strup_rg(0x26);
    uint16_t irq_mask = bank_26 & irq_sel;
    if (irq_mask == 0) {
        return;
    }
    log_pmu_info("pmu_irq_usb_comp_clear, irq_mask[0x%X], bank_26[0x%X]", 2, irq_mask, pmu_get_strup_rg(0x26));
    pmu_set_strup_rg(0x26, irq_sel);
    for (uint8_t i = 0; i < 64; i++) {
        if ((pmu_get_strup_rg(0x26) & irq_sel) == 0) {
            break;
        } else if (i >= 63) {
            log_pmu_error("pmu_irq_usb_comp_clear fail", 0);
            pmu_assert();
        }
    }
    if (irq_mask & PMU_CP_R) {
        log_pmu_info("pmu_irq_usb_comp_clear, PMU_CP_R ", 0);
        if (pmu_cb_func[PMU_CB_CP_R][PMU_USER_COMP].pmu_callback) {
            pmu_cb_func[PMU_CB_CP_R][PMU_USER_COMP].pmu_callback(NULL);
        }
    }
    if (irq_mask & PMU_CP_F) {
        log_pmu_info("pmu_irq_usb_comp_clear, PMU_CP_F ", 0);
        if (pmu_cb_func[PMU_CB_CP_F][PMU_USER_COMP].pmu_callback) {
            pmu_cb_func[PMU_CB_CP_F][PMU_USER_COMP].pmu_callback(NULL);
        }
    }
    if (irq_mask & PMU_USB_PLUGIN) {
        log_pmu_info("pmu_irq_usb_comp_clear, PMU_USB_PLUGIN ", 0);
        if (pmu_cb_func[PMU_CB_USB_PLUGIN][PMU_USER_BM].pmu_callback) {
            pmu_cb_func[PMU_CB_USB_PLUGIN][PMU_USER_BM].pmu_callback(NULL);
        }
        if (pmu_cb_func[PMU_CB_USB_PLUGIN][PMU_USER_USB].pmu_callback) {
            pmu_cb_func[PMU_CB_USB_PLUGIN][PMU_USER_USB].pmu_callback(NULL);
        }
    }
    if (irq_mask & PMU_USB_PLUGOUT) {
        log_pmu_info("pmu_irq_usb_comp_clear, PMU_USB_PLUGOUT ", 0);
        if (pmu_cb_func[PMU_CB_USB_PLUGOUT][PMU_USER_BM].pmu_callback) {
            pmu_cb_func[PMU_CB_USB_PLUGOUT][PMU_USER_BM].pmu_callback(NULL);
        }
        if (pmu_cb_func[PMU_CB_USB_PLUGOUT][PMU_USER_USB].pmu_callback) {
            pmu_cb_func[PMU_CB_USB_PLUGOUT][PMU_USER_USB].pmu_callback(NULL);
        }
    }
}

void pmu_irq_gpio_enable(uint16_t domain, uint32_t gpio_0_22, uint32_t gpio_23_48)
{
    uint16_t bank_1F = pmu_get_strup_rg(0x1F);
    if (domain == PMU_EINT_CM33_DOMAIN) {
        bank_1F |= PMU_EINT;
    } else {
        bank_1F |= (PMU_EINT << 8);
    }
    *IO_CFG_0_RTC_IN_EN = gpio_0_22;                //GPIO EINT pinmux (0x10)
    *IO_CFG_1_RTC_IN_EN = gpio_23_48;               //GPIO EINT pinmux (0x0)
    pmu_set_strup_rg(0x1F, bank_1F);                //domain enable
    //pmu_set_strup_rg(0x23, 0xFFFF);                 //GPIO EINT
    //pmu_set_strup_rg(0x24, 0xFFFF);                 //GPIO EINT
    //pmu_set_strup_rg(0x25, 0xFFFF);                 //GPIO EINT
    pmu_set_strup_rg(0x26, 0x000F);                 //??
    pmu_set_strup_rg(0x22, PMU_EINT);               //clear gpio irq mask and read bank_20 to check status
    log_pmu_info("pmu_irq_gpio_enable, domain[%d](1:cm33, 2:ibex), IO_CFG_0[0x%X], IO_CFG_1[0x%X], bank_1F[0x%X], bank_20[0x%X], bank_22[0x%X], bank_26[0x%X]", 7,
                 domain, *IO_CFG_0_RTC_IN_EN, *IO_CFG_1_RTC_IN_EN, pmu_get_strup_rg(0x1F), pmu_get_strup_rg(0x20), pmu_get_strup_rg(0x22), pmu_get_strup_rg(0x26));
}

void pmu_irq_gpio_disable(void)
{
    pmu_set_strup_rg(0x21, PMU_EINT);
    pmu_set_strup_rg(0x26, PMU_EINT);
    log_pmu_info("pmu_irq_gpio_disable", 0);
}

void pmu_irq_gpio_clear(void)
{
    uint16_t bank_26 = pmu_get_strup_rg(0x26);
    uint16_t irq_mask = bank_26 & PMU_EINT;
    if (irq_mask == 0) {
        return;
    }
    log_pmu_info("pmu_irq_gpio_clear, irq_mask[0x%X], bank_26[0x%X]", 2, irq_mask, pmu_get_strup_rg(0x26));
    pmu_set_strup_rg(0x26, irq_mask);

    pmu_set_strup_rg(0x23, 0xFFFF);   // GPIO EINT
    pmu_set_strup_rg(0x24, 0xFFFF);   // GPIO EINT
    pmu_set_strup_rg(0x25, 0xFFFF);   // GPIO EINT

    uint16_t ret35,ret36,ret37,ret38;
    ret35 =pmu_get_strup_rg(0x23);
    log_pmu_info("pmu_get_strup_rg(0x23)=%x",1, ret35);
    ret36 =pmu_get_strup_rg(0x24);
    log_pmu_info("pmu_get_strup_rg(0x24)=%x",1, ret36);
    ret37 =pmu_get_strup_rg(0x25);
    log_pmu_info("pmu_get_strup_rg(0x25)=%x",1, ret37);
    ret38 =pmu_get_strup_rg(0x26);
    log_pmu_info("pmu_get_strup_rg(0x26)=%x",1, ret38);
    while(ret35||ret36||ret37)
    {   
        hal_gpt_delay_ms(10);
        pmu_set_strup_rg(0x23, 0xFFFF);   // GPIO EINT
        pmu_set_strup_rg(0x24, 0xFFFF);   // GPIO EINT
        pmu_set_strup_rg(0x25, 0xFFFF);   // GPIO EINT
        
        ret35 =pmu_get_strup_rg(0x23);
        log_pmu_info("pmu_get_strup_rg(0x23)=%x",1, ret35);
        ret36 =pmu_get_strup_rg(0x24);
        log_pmu_info("pmu_get_strup_rg(0x24)=%x",1, ret36);
        ret37 =pmu_get_strup_rg(0x25);
        log_pmu_info("pmu_get_strup_rg(0x25)=%x",1, ret37);
    }

    hal_gpt_delay_ms(100);

    if (irq_mask & PMU_EINT) {
        log_pmu_info("pmu_irq_gpio_clear, PMU_EINT", 0);
        if (pmu_cb_func[PMU_CB_EINT][PMU_USER_GPIO].pmu_callback) {
            pmu_cb_func[PMU_CB_EINT][PMU_USER_GPIO].pmu_callback(NULL);
        }
    }
}

/* PMU ISR */
void pmu_isr(hal_nvic_irq_t irq_number)
{
    UNUSED(irq_number);

    pmu_irq_pof_clear();
    pmu_irq_usb_comp_clear(PMU_CP_R | PMU_CP_F | PMU_USB_PLUGIN | PMU_USB_PLUGOUT);
    pmu_irq_gpio_clear();

#if 0
    uint32_t irq_status = 0, pmu_vbat_irq = 0;
    uint32_t eint_0_15_status = 0, eint_16_31_status = 0, eint_32_47_status = 0;
    irq_status = IRQ_STA(); //Add this line in Everest    ??PMU IRQ42 from NVIC status
    if(irq_status == CM33_IRQ_PMU) {
        pmu_vbat_irq = ((pmu_get_strup_rg(0x26)) & 0x1f);
        if( (pmu_vbat_irq & 0x10) == 0x10) {
            /*TINFO="eint edge irq"*/
            eint_0_15_status  = pmu_get_strup_rg(0x23);
            eint_16_31_status = pmu_get_strup_rg(0x24);
            eint_32_47_status = pmu_get_strup_rg(0x25);
            /*TINFO="eint_0_15_status  =%x", eint_0_15_status  */
            /*TINFO="eint_16_31_status =%x", eint_16_31_status  */
            /*TINFO="eint_32_47_status =%x", eint_32_47_status  */
            pmu_set_strup_rg (0x23, eint_0_15_status);
            pmu_set_strup_rg (0x24, eint_16_31_status);
            pmu_set_strup_rg (0x25, eint_32_47_status);
        }
    }
#endif
}

void pmu_nvic_init(void)
{
    static bool is_init = false;
    if (is_init == false) {
        hal_nvic_disable_irq(PMU_IRQn);
        hal_nvic_register_isr_handler(PMU_IRQn, (hal_nvic_isr_t)pmu_isr);
        hal_nvic_enable_irq(PMU_IRQn);
        is_init = true;
    }
}

void pmu_isr_init(void)
{
    //pmu_irq_pof_enable(PMU_EINT_CM33_DOMAIN, PMU_POF_FALLING_EDGE);
    pmu_irq_usb_comp_enable(PMU_EINT_CM33_DOMAIN, (PMU_CP_R | PMU_CP_F | PMU_USB_PLUGIN | PMU_USB_PLUGOUT));

    //*RTC_LPOSC_CON1__F_LPOSC_EXTEND_SLEEP_MODE      = 0x1;        //??
    //*PMU_DIG_SRAM_CTRL__F_SRAM_PG_EN_CTRL           = 0x1         //force SRAM_PG_EN = 0 ???
    hal_gpt_delay_us(400);
    //pmu_set_strup_rg(0x2C, 0x7);                                    //?? rg_vio18_pg_en_vrtc_on, rg_rtc_pg_en_vrtc_on, rg_vrf_pg_en

    pmu_nvic_init();
    log_pmu_info("pmu_isr_init", 0);
}

/* PMU NVKEY */
#ifdef AIR_NVKEY_ENABLE
pmu_status_t pmu_get_nvkey(uint16_t id, uint8_t *ptr, uint32_t size)
{
    if ((ptr == NULL) || (size == 0)) {
        log_pmu_error("pmu_get_nvkey fail, id[0x%X], ptr[0x%X], size[%d]", 3, id, ptr, size);
        pmu_assert();
        return PMU_STATUS_ERROR;
    }
    nvkey_status_t status = nvkey_read_data(id, ptr, &size);
    if (status != NVKEY_STATUS_OK) {
        log_pmu_error("pmu_get_nvkey fail, id[0x%X], status[%d]", 2, id, status);
        pmu_assert();
        return PMU_STATUS_ERROR;
    }
    return PMU_STATUS_SUCCESS;
}

pmu_status_t pmu_set_nvkey(uint16_t id, uint8_t *ptr, uint32_t size)
{
    if ((ptr == NULL) || (size == 0)) {
        log_pmu_error("pmu_set_nvkey fail, id[0x%X], ptr[0x%X], size[%d]", 3, id, ptr, size);
        pmu_assert();
        return PMU_STATUS_ERROR;
    }
    nvkey_status_t status = nvkey_write_data(id, ptr, size);
    if (status != NVKEY_STATUS_OK) {
        log_pmu_error("pmu_set_nvkey fail, id[0x%X], status[%d]", 2, id, status);
        pmu_assert();
        return PMU_STATUS_ERROR;
    }
    return PMU_STATUS_SUCCESS;
}
#endif

void pmu_nvkey_init(void)
{
#ifdef AIR_NVKEY_ENABLE
    pmu_get_nvkey(NVID_VPA_VOLTAGE, &pmu_rftx_idx, sizeof(pmu_rftx_idx));
#endif
    log_pmu_info("pmu_nvkey_init, pmu_rftx_idx[%d](RF TX power 0:0~4dBm, 1:6~8dBm, 2:10dBm)", 1, pmu_rftx_idx);
}

/* PMU INIT */
uint16_t pmu_get_power_on_reason(void)
{
    uint16_t reason = 0;
    reason = pmu_get_strup_rg(0x3F) & 0x3;
    switch (reason) {
        case OFF_REASON:
            log_pmu_info("pmu_get_power_on_reason, OFF_REASON", 0);
            break;
        case DEEPSLP_BY_EINT:
            log_pmu_info("pmu_get_power_on_reason, DEEPSLP_BY_EINT", 0);
            break;
        case DEEPSLP_BY_COMP:
            log_pmu_info("pmu_get_power_on_reason, DEEPSLP_BY_COMP", 0);
            break;
        case DEEPSLP_BY_USB_PLUG:
            log_pmu_info("pmu_get_power_on_reason, DEEPSLP_BY_USB_PLUG", 0);
            break;
        default:
            log_pmu_error("pmu_get_power_on_reason unexpected, reason[%d]", 1, reason);
            pmu_assert();
            break;
    }
    return reason;
}

uint16_t pmu_get_power_off_reason(void)
{
    uint16_t reason = 0;
    reason = (pmu_get_strup_rg(0x3F) >> 8) & 0x1F;

    switch (reason) {
        case NORM_DEF:
            log_pmu_info("pmu_get_power_off_reason, NORM_DEF", 0);
            break;
        case NORM_PAD_RSTB_L:
            log_pmu_info("pmu_get_power_off_reason, NORM_PAD_RSTB_L", 0);
            break;
        case NORM_VIO18_PG:
            log_pmu_info("pmu_get_power_off_reason, NORM_VIO18_PG", 0);
            break;
        case NORM_VRF_PG:
            log_pmu_info("pmu_get_power_off_reason, NORM_VRF_PG", 0);
            break;
        case NORM_VCORE_PG:
            log_pmu_info("pmu_get_power_off_reason, NORM_VCORE_PG", 0);
            break;
        case NORM_VRTC_PG:
            log_pmu_info("pmu_get_power_off_reason, NORM_VRTC_PG", 0);
            break;
        case NORM_WDT:
            log_pmu_info("pmu_get_power_off_reason, NORM_WDT", 0);
            break;
        case NORM_USB_1620D:
            log_pmu_info("pmu_get_power_off_reason, NORM_USB_1620D", 0);
            break;
        case NORM_OVP_VIO:
            log_pmu_info("pmu_get_power_off_reason, NORM_OVP_VIO", 0);
            break;
        case NORM_OVP_NOC:
            log_pmu_info("pmu_get_power_off_reason, NORM_OVP_NOC", 0);
            break;
        case NORM_SW_DEEPSLP:
            log_pmu_info("pmu_get_power_off_reason, NORM_SW_DEEPSLP", 0);
            break;
        case DEEPSLP_PAD_RSTB_L:
            log_pmu_info("pmu_get_power_off_reason, DEEPSLP_PAD_RSTB_L", 0);
            break;
        case DEEPSLP_VIO18_PG:
            log_pmu_info("pmu_get_power_off_reason, DEEPSLP_VIO18_PG", 0);
            break;
        case DEEPSLP_OVP_VIO:
            log_pmu_info("pmu_get_power_off_reason, DEEPSLP_OVP_VIO", 0);
            break;
        case SEQ_PAD_RSTB_L:
            log_pmu_info("pmu_get_power_off_reason, SEQ_PAD_RSTB_L", 0);
            break;
        case SEQ_VIO18_PG:
            log_pmu_info("pmu_get_power_off_reason, SEQ_VIO18_PG", 0);
            break;
        case SEQ_VRF_PG:
            log_pmu_info("pmu_get_power_off_reason, SEQ_VRF_PG", 0);
            break;
        case SEQ_VCORE_VRTC_PG:
            log_pmu_info("pmu_get_power_off_reason, SEQ_VCORE_VRTC_PG", 0);
            break;
        case SEQ_VRTC_PG:
            log_pmu_info("pmu_get_power_off_reason, SEQ_VRTC_PG", 0);
            break;
        case SEQ_OVP_VIO:
            log_pmu_info("pmu_get_power_off_reason, SEQ_OVP_VIO", 0);
            break;
        case SEQ_OVP_NOC:
            log_pmu_info("pmu_get_power_off_reason, SEQ_OVP_NOC", 0);
            break;
        default:
            log_pmu_error("pmu_get_power_off_reason unexpected, reason[%d]", 1, reason);
            break;
    }
    return reason;
}

void pmu_rg_dump(void)
{
#if defined(AIR_PMU_FULL_DUMP_ENABLE)
    uint8_t i = 0;
    for (i = 0; i < 10; i++) {
        log_pmu_info("pmu_rg_dump, rg_%02X[0x%08X], rg_%02X[0x%08X], rg_%02X[0x%08X], rg_%02X[0x%08X]", 8,
                     ((i * 16) + 0), (*(volatile uint32_t *)(PMU_DIG_VRTC_BASE + (i * 16) + 0)), ((i * 16) + 4),  (*(volatile uint32_t *)(PMU_DIG_VRTC_BASE + (i * 16) + 4)),
                     ((i * 16) + 8), (*(volatile uint32_t *)(PMU_DIG_VRTC_BASE + (i * 16) + 8)), ((i * 16) + 12), (*(volatile uint32_t *)(PMU_DIG_VRTC_BASE + (i * 16) + 12)));
    }
    for (i = 0; i < 16; i++) {
        log_pmu_info("pmu_rg_dump, bank_%02X[0x%04X], bank_%02X[0x%04X], bank_%02X[0x%04X], bank_%02X[0x%04X]", 8,
                     ((i * 4) + 0), pmu_get_strup_rg(((i * 4) + 0)), ((i * 4) + 1), pmu_get_strup_rg(((i * 4) + 1)),
                     ((i * 4) + 2), pmu_get_strup_rg(((i * 4) + 2)), ((i * 4) + 3), pmu_get_strup_rg(((i * 4) + 3)));
    }
#else
    log_pmu_info("pmu_rg_dump, bank_2D[0x%X], bank_2E[0x%X], bank_2F[0x%X], bank_38[0x%X], bank_39[0x%X], bank_3A[0x%X], bank_3F[0x%X]", 7,
                 pmu_get_strup_rg(0x2D), pmu_get_strup_rg(0x2E), pmu_get_strup_rg(0x2F), pmu_get_strup_rg(0x38), pmu_get_strup_rg(0x39), pmu_get_strup_rg(0x3A), pmu_get_strup_rg(0x3F));
    log_pmu_info("pmu_rg_dump, rg_010[0x%X], rg_014[0x%X], rg_01C[0x%X], rg_020[0x%X], rg_038[0x%X], rg_040[0x%X], rg_060[0x%X]", 7,
                 *PMU_DIG_CTRL0, *PMU_DIG_CTRL1, *PMU_DIG_CTRL3, *PMU_DIG_CTRL4, *PMU_DIG_CTRL10, *PMU_DIG_CTRL12, *PMU_ANA_CON0);
#endif
    log_pmu_info("pmu_rg_dump, GPIO_MODE_A[0x%08X], GPIO_MODE_B[0x%08X], GPIO_MODE_C[0x%08X], GPIO_MODE_D[0x%08X], GPIO_MODE_E[0x%08X], GPIO_MODE_F[0x%08X]", 6,
                 *PMU_GPIO_MODE_A, *PMU_GPIO_MODE_B, *PMU_GPIO_MODE_C, *PMU_GPIO_MODE_D, *PMU_GPIO_MODE_E, *PMU_GPIO_MODE_F);
    log_pmu_info("pmu_rg_dump, PD_CFG0[0x%08X], PU4P7K_CFG0[0x%08X], PU_CFG0[0x%08X], RTC_GPIO_MODE0[0x%08X], RTC_GPIO_MODE1[0x%08X]", 5,
                 *PMU_PD_CFG0, *PMU_PU4P7K_CFG0, *PMU_PU_CFG0, *PMU_RTC_GPIO_MODE0, *PMU_RTC_GPIO_MODE1);
}

void pmu_init_internal(void)
{
    pmu_project_dump();
    pmu_get_power_on_reason();
    pmu_get_power_off_reason();

    pmu_strup_rg_unlock();                                   //unlock vbat rg
    pmu_set_strup_rg_value(0x2E, 0x3, 14, 0x1);              //set OSC32K_CYC_OPT = 3T, wait 80us then set OSC32K_EN_SW = 0
    pmu_set_strup_rg(0x2F, 0xAC00);                          //disable test_scan_en
    *PMU_DIG_CTRL0 = 0x02000000;                             //PMU_DIG_CTRL0 change to HW mode(GO_SLP, GO_EXTSLP, LDO_VCORE, WDT)
    *PMU_GPIO_BACKUP = 0x1;                                  //PMU_GPIO_BACKUP clear AD_ST_EXTSLP status
    *PMU_DIG_CTRL1 = 0x00000000;                             //PMU_DIG_CTRL1 change to HW mode(ST_EXTSLP, VBAT_POF)
    pmu_vrf_lpm_en();                                        //Reduced BUCK_VRF quiescent current

    pmu_volt_init(HAL_DVFS_VCORE_HIGH);
    pmu_ret_vio18_init();
    pmu_set_strup_rg_value(0x2D, 0x1, 6, 0x0);               //not force VIO18, VRTC, VRF PG on when VRTC is on
    pmu_set_strup_rg_value(0x2D, 0x1, 8, 0x1);               //WDT cold reset enable
    pmu_set_strup_rg_value(0x3A, 0x1, 0, 0x0);               //disable “skip bootrom” function
    pmu_set_strup_rg(0x39, 0x0002);                          //wait SPM setting ready

    pmu_gpio_get_eint_status();                              //get gpio eint status
    *PMU_DIG_STRUP_RG_CTRL = 0x01210010;                     //MASK SET[4]
    *PMU_ANA_CON4__F_VRF_TM_EN = 0x1;                        //enable test mode to improve load transient
    *PMU_ANA_CON0__F_VRF_RSV1 = 0x3;                         //improve load transient
    pmu_set_strup_rg(0x1, 0x0008);                           //improve load transient
    *RTC_DIG_RSV1 = pmu_get_strup_rg(0xA);                   //disable VCORE PG in extslp
    *SRAM_UHDE_DELSEL_LV = 0x50704;                          //ULL SRAM 0.8V setting update
    pmu_set_strup_rg_value(0x2D, 0x1, 15, 0x1);              //OVP_VIO_LP_VAL, add OVP init setting
    //pmu_io_dbg_mux();
    //*PMU_DIG_DEBUG_MON = 0x2;//state

#ifndef AIR_SLT_TEST
    if ((otp_ft_id != FT_ID_AB1620D) && (otp_ft_id != FT_ID_AB1620DM)) {
        pmu_set_strup_rg_value(0x2D, 0x1, 11, 0x0);          //OSC32K on/off by HW event for low power saving
    }
#endif

    pmu_strup_rg_lock();                                     //lock vbat rg
    pmu_init_flag = 1;
    pmu_isr_init();
    pmu_rg_dump();

#ifdef HAL_BAT_MODULE_ENABLED
    bat_get_pnzcv();
#endif
}

void pmu_power_off_sequence(pmu_power_stage_t stage)
{
    switch(stage) {
        case PMU_PWROFF:
            break;
        case PMU_DEEPSLP:
            log_pmu_info("pmu_power_off_sequence [PMU_DEEPSLP]", 0);
            pmu_strup_rg_unlock();
            pmu_rg_dump();
            pmu_gpio_eint_ctrl();
            *XO_PDN_AO_SETD0 = 0x40000000;
            pmu_set_strup_rg_value(0x3A, 0x1, 0, 0x1);
            pmu_set_strup_rg(0x39, 3);
            pmu_strup_rg_lock();
            hal_gpt_delay_ms(20);
            *PMU_DIG_CTRL2__F_GO_DEEPSLP = 0x1;
            break;
        case PMU_NORMAL:
            break;
        case PMU_SLEEP:
            break;
        default:
            break;
    }
}

void pmu_init(void)
{
#if !defined(AIR_DOWNLOAD_AGENT) && !defined(CONFIG_MCUBOOT)
    pmu_cal_init();
    pmu_nvkey_init();
    pmu_init_internal();
#endif
}

void pmu_pinmux_init(void)
{
    pmu_set_strup_rg_value(0x2F, 0x1, 4, 0x1);                 //call the API after pinmux ready
}

uint16_t pmu_get_usb_plugin_status(void)
{
    uint16_t status = 0;
    status = pmu_get_strup_rg_value(0x3A, 0x1, 7);
    return status;
}
#endif /*   HAL_PMU_MODULE_ENABLED   */
