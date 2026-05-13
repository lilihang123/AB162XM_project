/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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
#include "assert.h"
#include "hal_pmu.h"
#include "hal_pmu_cal.h"
#include "hal_pmu_platform.h"
#include "hal_flash_disk_internal.h"
#include "hal_flash.h"

#ifdef AIR_NVDM_ENABLE
#include "nvkey_id_list.h"
#include "nvkey.h"
#endif

#if defined(__EXT_BOOTLOADER__) || defined(__EXT_DA__)
#define log_pmu_info(msg, cnt, ...)
#define log_pmu_warn(msg, cnt, ...)
#define log_pmu_error(msg, cnt, ...)
#else
#define log_pmu_info(msg, cnt, ...)             printk("[PMU_CAL] "msg"\r\n", ##__VA_ARGS__)
#define log_pmu_warn(msg, cnt, ...)             printk("[PMU_CAL] "msg"\r\n", ##__VA_ARGS__)
#define log_pmu_error(msg, cnt, ...)            printk("[PMU_CAL] "msg"\r\n", ##__VA_ARGS__)
#endif


#define UNUSED(x)  ((void)(x))
#define AIR_PMU_DUMP_ENABLE

uint8_t otp_ft_id = 0;
uint8_t otp_ddie_ver = 0;
int16_t vrf_offset = 0;
uint8_t otp_vrf_votrim_ulpm = 0;


/* PMU TRIM */
pmu_status_t pmu_get_otp(uint16_t addr, uint8_t *ptr, uint32_t size)
{
#ifdef HAL_FLASH_MODULE_ENABLED
    hal_flash_status_t status = hal_flash_otp_read(addr, ptr, size);
    if (addr < OTP_BASE_ADDR) {
        if (status != HAL_FLASH_STATUS_OK) {
            log_pmu_error("pmu_get_otp bank0 fail, otp_addr[%d], status[%d], size[%d]", 3, addr, status, size);
            return PMU_STATUS_ERROR;
        }
        return PMU_STATUS_SUCCESS;
    }
    if (status != HAL_FLASH_STATUS_OK) {
        log_pmu_error("pmu_get_otp fail, otp_addr[%d], status[%d], size[%d]", 3, (addr - OTP_BASE_ADDR), status, size);
        return PMU_STATUS_ERROR;
    }
    if  (ptr[0] == OTP_OK) {
        return PMU_STATUS_SUCCESS;
    } else {
        log_pmu_error("pmu_get_otp fail, otp_addr[%d], kflag[%x]", 2, (addr - OTP_BASE_ADDR), ptr[0]);
        return PMU_STATUS_ERROR;
    }
#else
    log_pmu_error("pmu_get_otp fail, HAL_FLASH_STATUS_ERROR_NO_INIT", 0);
    return PMU_STATUS_ERROR;
#endif
}

void pmu_get_otp_ft_id()
{
    if (pmu_get_otp(OTP_FT_ID_ADDR, (uint8_t *)&otp_ft_id, sizeof(otp_ft_id)) != PMU_STATUS_SUCCESS) {
        return;
    }
    log_pmu_info("pmu_get_otp_ft_id, otp_ft_id[%d]", 1, otp_ft_id);
}

void pmu_get_ddie_ver()
{
    if (pmu_get_otp(OTP_DDIE_VER_ADDR, (uint8_t *)&otp_ddie_ver, sizeof(otp_ddie_ver)) != PMU_STATUS_SUCCESS) {
        return;
    }
    log_pmu_info("pmu_get_ddie_ver, otp_ddie_ver[%d]", 1, otp_ddie_ver);
}

void pmu_buck_rf_bias(void)
{
    buck_rf_bias_t otp = {0xFF, 0x8};
    if (pmu_get_otp(OTP_BUCK_RF_BIAS_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        return;
    }
    pmu_set_strup_rg_value(0xC, 0xF, 8, otp.VRF_IBIAS_TRIM);
}

void pmu_buck_rf_vout(void)
{
    buck_rf_vout_t otp = {0xFF, 0x20, 0x20, 0x20, 0x0};
    *PMU_DIG_RSV0__F_DIG_TOP_RSV0 = 0x2020;
    if (pmu_get_otp(OTP_BUCK_RF_VOUT_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        return;
    }
    pmu_set_strup_rg_value(0xC, 0x3F, 0, otp.VRF_VOTRIM_NM);
    *PMU_ANA_CON5__F_VRF_VOCAL_LP_TRIM = otp.VRF_VOTRIM_LPM;
    *PMU_DIG_RSV0__F_DIG_TOP_RSV0 = ((otp.VRF_VOTRIM_ULPM << 8) + otp.VRF_VOTRIM_LPM);
    pmu_set_strup_rg_value(0xB, 0x7, 4, otp.VRF_IODUM_TRIM);
    otp_vrf_votrim_ulpm = otp.VRF_VOTRIM_ULPM;
}

void pmu_buck_rf_timer(void)
{
    buck_rf_timer_t otp = {0xFF, 0x8, 0x4, 0x4, 0x8};
    if (pmu_get_otp(OTP_BUCK_RF_TIMER_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        return;
    }
    pmu_set_strup_rg_value(0xB, 0x1, 0, ((otp.VRF_COT_TRIM >> 4) & 0x1));
    pmu_set_strup_rg_value(0xB, 0xF, 8, (otp.VRF_COT_TRIM & 0xF));
    pmu_set_strup_rg_value(0xB, 0x7, 12, otp.VRF_PREON);
    *PMU_ANA_CON5__F_VRF_IQDN_ITH = otp.VRF_IQDN;
    pmu_set_strup_rg_value(0x11, 0xF, 12, otp.VRF_HIZ_TRIM);
}

void pmu_buck_rf_oc(void)
{
    buck_rf_oc_t otp = {0xFF, 0x9};
    if (pmu_get_otp(OTP_BUCK_RF_OC_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        return;
    }
    *PMU_ANA_CON5__F_VRF_OCOS_TRIM = otp.VRF_OCOS_TRIM;
}

void pmu_buck_rf_zc(void)
{
    buck_rf_zc_t otp = {0xFF, 0x8, 0x4};
    if (pmu_get_otp(OTP_BUCK_RF_ZC_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        return;
    }
    *PMU_ANA_CON5__F_VRF_ZXOS_TRIM = otp.VRF_ZCOS_TRIM;
    *PMU_ANA_CON3__F_VRF_OCN_SEL = otp.VRF_CCM_ZCOS_TRIM;
}

void pmu_lpo32_freqk(void)
{
    lpo32_freqk_t otp = {0xFF, 0x21, 0x3};
    if (pmu_get_otp(OTP_LPO32_FREQK_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        return;
    }
    pmu_set_strup_rg(0x7, ((otp.Ftune << 8) + otp.Ctune));
}

void pmu_capless_ldo_vout(void)
{
    capless_ldo_vout_t otp = {0xFF, 0x16};
    if (pmu_get_otp(OTP_CAPLESS_LDO_VOUT_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        return;
    }
    pmu_set_strup_rg_value(0x8, 0x3F, 0, otp.VOTRIM);
}

void pmu_capless_ldo_vout_rsv(void)
{
    capless_ldo_vout_rsv_t otp = {0xFF, 0x0};
    if (pmu_get_otp(OTP_CAPLESS_LDO_VOUT_RSV_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        return;
    }
    if ((otp.NOCLDO_RSV >= 10) && (otp.NOCLDO_RSV <= 90)) {
        vrf_offset = otp.NOCLDO_RSV - 50;
    } else {
        vrf_offset = 0;
    }
    log_pmu_info("pmu_capless_ldo_vout_rsv, NOCLDO_RSV[%d], vrf_offset[%d]", 2, otp.NOCLDO_RSV, vrf_offset);
}

void pmu_ovp_vio(void)
{
    ovp_vio_t otp = {0xFF, 0xF, 0x7, 0xE};
    if (pmu_get_otp(OTP_OVP_VIO_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        return;
    }
    if (otp_ddie_ver > FT_DDIE_VER_E1) {
        pmu_set_strup_rg_value(0xD,  0x1, 7, ((otp.OVP_VIO_VTH >> 5) & 0x1));
        pmu_set_strup_rg_value(0x10, 0x1, 4, ((otp.OVP_VIO_VTH_LP >> 5) & 0x1));
    }
    pmu_set_strup_rg_value(0xE, 0x1F, 0, (otp.OVP_VIO_VTH & 0x1F));
    pmu_set_strup_rg_value(0xD, 0xF,  0, (otp.OVP_VIO_IBIAS & 0xF));
    pmu_set_strup_rg_value(0xE, 0x1F, 8, (otp.OVP_VIO_VTH_LP & 0x1F));
}

void pmu_ovp_nocldo(void)
{
    ovp_nocldo_t otp = {0xFF, 0xC, 0x8};
    if (pmu_get_otp(OTP_OVP_NOCLDO_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        return;
    }
    pmu_set_strup_rg_value(0xF, 0x1F, 8, (otp.OVP_NOCLDO_VTH & 0x1F));
    pmu_set_strup_rg_value(0xD, 0xF, 8, (otp.OVP_NOCLDO_IBIAS & 0xF));
}

void pmu_vcore_ldo(void)
{
    vcore_ldo_t otp = {0xFF, 0x10};
    if (pmu_get_otp(OTP_VCORE_LDO_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        return;
    }
    pmu_set_strup_rg_value(0xA, 0xFF, 0, otp.VCORE_VOTRIM);
}

void pmu_vcore_ldo_dummy_load(void)
{
    vcore_ldo_dummy_load_t otp = {0xFF, 0x0000};
    if (pmu_get_otp(OTP_VCORE_LDO_DUMMY_LOAD_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        return;
    }
    //otp.VCORE_DL;
}

void pmu_lpbg_tctrim(void)
{
    lpbg_tctrim_t otp = {0xFF, 0x8};
    if (pmu_get_otp(OTP_LPBG_TCTRIM_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        return;
    }
    pmu_set_strup_rg_value(0x4, 0xF, 8, otp.LPBG_TCTRIM);
}

void pmu_lpbg_ibtrim(void)
{
    lpbg_ibtrim_t otp = {0xFF, 0x10};
    if (pmu_get_otp(OTP_LPBG_IBTRIM_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        return;
    }
    pmu_set_strup_rg_value(0x4, 0x1F, 0, otp.LPBG_IBTRIM);
}

void pmu_lpbg_vref(void)
{
    lpbg_vref_t otp = {0xFF, 0x10, 0x10, 0x10, 0x7};
    if (pmu_get_otp(OTP_LPBG_VREF_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        return;
    }
    pmu_set_strup_rg(0x5, ((otp.LPBG_VREF1P0TRIM << 8) + otp.LPBG_VREF0P5TRIM));
    pmu_set_strup_rg(0x6, otp.LPBG_VREF0P5_UVLO_TRIM1);
    //otp.LPBG_VREF0P5_UVLO_TRIM2
}

void pmu_hpbg_tctrim(void)
{
    hpbg_tctrim_t otp = {0xFF, 0x8};
    if (pmu_get_otp(OTP_HPBG_TCTRIM_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        return;
    }
    pmu_set_strup_rg_value(0x3, 0xF, 8, otp.HPBG_TCTRIM);
}

void pmu_hpbg_vref(void)
{
    hpbg_vref_t otp = {0xFF, 0x8};
    if (pmu_get_otp(OTP_HPBG_VREF_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        return;
    }
    pmu_set_strup_rg_value(0x3, 0x1F, 0, otp.HPBG_VREF0P5TRIM);
}

void pmu_vio18_vout(void)
{
    vio18_vout_t otp = {0xFF, 0x40, 0x10};
    if (pmu_get_otp(OTP_VIO18_VOUT_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        return;
    }
    pmu_set_strup_rg_value(0x36, 0x7F, 0, otp.NM_VOTRIM_1p8);
    //otp.NM_VOTRIM_1p5;
}

void pmu_vio18_ret_vout(void)
{
    vio18_ret_vout_t otp = {0xFF, 0x16, 0x1A};
    if (pmu_get_otp(OTP_VIO18_RET_VOUT_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        return;
    }
    //pmu_set_strup_rg_value(0x34, 0x1F, 8, otp.RET_VOTRIM_1p8);
    //pmu_set_strup_rg_value(0x34, 0x1F, 0, otp.RET_VOTRIM_1p5);
    pmu_set_strup_rg(0x34, ((otp.RET_VOTRIM_1p8 << 8) + otp.RET_VOTRIM_1p5));
    *PMU_DIG_CTRL10__F_VLDO18_RET_VSEL_SLP = otp.RET_VOTRIM_1p8;
    *PMU_DIG_CTRL10__F_VLDO18_RET_VSEL_NORM = otp.RET_VOTRIM_1p5;
}

void pmu_vio18_oc(void)
{
    vio18_oc_t otp = {0xFF, 0x4};
    if (pmu_get_otp(OTP_VIO18_OC_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        return;
    }
    pmu_set_strup_rg_value(0x0, 0x7, 8, otp.OCTRIM);
}

void pmu_buck_rf_ulp_trim(uint16_t vrf_extslp2, int16_t rg_vrf_extslp2)
{
    int16_t trim_os = 0, trim_fin = 0, vrf_comp_mis = 0;
    uint16_t vrf_min_volt = 700;
    uint32_t rg_dig_top_rsv0 = 0;
    buck_rf_ulp_trim_t otp = {0xFF, 0x44, 0x64, 0x00, 0x20, 0x32};

    if (pmu_get_otp(OTP_BUCK_RF_ULP_TRIM_ADDR, (uint8_t *)&otp, sizeof(otp)) != PMU_STATUS_SUCCESS) {
        *PMU_DIG_CTRL7__F_VRF_VSEL_EXTSLP2 = rg_vrf_extslp2;
        return;
    }
    rg_vrf_extslp2 = pmu_round(((vrf_extslp2 - vrf_min_volt) * 10), otp.BUCK_VRF_LP_TRIM_STEP) + vrf_offset;
    if (rg_vrf_extslp2 >= 0) {
        *PMU_DIG_CTRL7__F_VRF_VSEL_EXTSLP2 = rg_vrf_extslp2;
    } else {
        vrf_comp_mis = otp.BUCK_VRF_COMP_MIS & 0x7F;
        if ((otp.BUCK_VRF_COMP_MIS >> 7) & 0x1) {
            vrf_comp_mis = vrf_comp_mis * -1;
        }
        *PMU_DIG_CTRL7__F_VRF_VSEL_EXTSLP2 = 0;
        *PMU_DIG_RSV0__F_DIG_TOP_RSV0 &= 0xFFFF7FFF;
        if (otp_ddie_ver > FT_DDIE_VER_E1) {
            trim_os = pmu_round(((otp.BUCK_VRF_R2 * vrf_extslp2) - (otp.BUCK_VRF_R1 + otp.BUCK_VRF_R2) * (500 + vrf_comp_mis)), vrf_extslp2);
            trim_fin = otp_vrf_votrim_ulpm + trim_os;
            if (trim_fin < 0) {
                trim_fin = 0;
            } else if (trim_fin > 63) {
                trim_fin = 63;
            }
            rg_dig_top_rsv0 = *PMU_DIG_RSV0__F_DIG_TOP_RSV0;
            rg_dig_top_rsv0 &= 0xFFC0FFFF;
            rg_dig_top_rsv0 |= ((trim_fin & 0x3F) << 16);
            rg_dig_top_rsv0 |= (1 << 15);
            *PMU_DIG_RSV0__F_DIG_TOP_RSV0 = rg_dig_top_rsv0;
        }
    }
    log_pmu_info("pmu_buck_rf_ulp_trim, vrf_extslp2[%d], rg_vrf_extslp2[%d], trim_os[%d], trim_fin[%d], VRF_VSEL_EXTSLP2[0x%X], DIG_TOP_RSV0[0x%X]", 6,
                 vrf_extslp2, rg_vrf_extslp2, trim_os, trim_fin, *PMU_DIG_CTRL7__F_VRF_VSEL_EXTSLP2, *PMU_DIG_RSV0__F_DIG_TOP_RSV0);
}

void pmu_otp_dump(void)
{
#if defined(AIR_PMU_DUMP_ENABLE)
    buck_rf_bias_t otp_0 = {0, 0};
    if (pmu_get_otp(OTP_BUCK_RF_BIAS_ADDR, (uint8_t *)&otp_0, sizeof(otp_0)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_0%d, kflag[0x%X], VRF_IBIAS_TRIM[0x%X]", 3,
                     (OTP_BUCK_RF_BIAS_ADDR - OTP_BASE_ADDR), otp_0.kflag, otp_0.VRF_IBIAS_TRIM);
    }
    buck_rf_vout_t otp_2 = {0, 0, 0, 0, 0};
    if (pmu_get_otp(OTP_BUCK_RF_VOUT_ADDR, (uint8_t *)&otp_2, sizeof(otp_2)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_0%d, kflag[0x%X], VRF_VOTRIM_NM[0x%X], VRF_VOTRIM_LPM[0x%X], VRF_VOTRIM_ULPM[0x%X], VRF_IODUM_TRIM[0x%X]", 6,
                     (OTP_BUCK_RF_VOUT_ADDR - OTP_BASE_ADDR), otp_2.kflag, otp_2.VRF_VOTRIM_NM, otp_2.VRF_VOTRIM_LPM, otp_2.VRF_VOTRIM_ULPM, otp_2.VRF_IODUM_TRIM);
    }
    buck_rf_timer_t otp_7 = {0, 0, 0, 0, 0};
    if (pmu_get_otp(OTP_BUCK_RF_TIMER_ADDR, (uint8_t *)&otp_7, sizeof(otp_7)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_0%d, kflag[0x%X], VRF_COT_TRIM[0x%X], VRF_PREON[0x%X], VRF_IQDN[0x%X], VRF_HIZ_TRIM[0x%X]", 6,
                     (OTP_BUCK_RF_TIMER_ADDR - OTP_BASE_ADDR), otp_7.kflag, otp_7.VRF_COT_TRIM, otp_7.VRF_PREON, otp_7.VRF_IQDN, otp_7.VRF_HIZ_TRIM);
    }
    buck_rf_oc_t otp_12 = {0, 0};
    if (pmu_get_otp(OTP_BUCK_RF_OC_ADDR, (uint8_t *)&otp_12, sizeof(otp_12)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_%d, kflag[0x%X], VRF_OCOS_TRIM[0x%X]", 3,
                     (OTP_BUCK_RF_OC_ADDR - OTP_BASE_ADDR), otp_12.kflag, otp_12.VRF_OCOS_TRIM);
    }
    buck_rf_zc_t otp_14 = {0, 0, 0};
    if (pmu_get_otp(OTP_BUCK_RF_ZC_ADDR, (uint8_t *)&otp_14, sizeof(otp_14)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_%d, kflag[0x%X], VRF_ZCOS_TRIM[0x%X], VRF_CCM_ZCOS_TRIM[0x%X]", 4,
                     (OTP_BUCK_RF_ZC_ADDR - OTP_BASE_ADDR), otp_14.kflag, otp_14.VRF_ZCOS_TRIM, otp_14.VRF_CCM_ZCOS_TRIM);
    }
    lpo32_freqk_t otp_17 = {0, 0, 0};
    if (pmu_get_otp(OTP_LPO32_FREQK_ADDR, (uint8_t *)&otp_17, sizeof(otp_17)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_%d, kflag[0x%X], Ftune[0x%X], Ctune[0x%X]", 4,
                     (OTP_LPO32_FREQK_ADDR - OTP_BASE_ADDR), otp_17.kflag, otp_17.Ftune, otp_17.Ctune);
    }
    capless_ldo_vout_t otp_20 = {0, 0};
    if (pmu_get_otp(OTP_CAPLESS_LDO_VOUT_ADDR, (uint8_t *)&otp_20, sizeof(otp_20)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_%d, kflag[0x%X], VOTRIM[0x%X]", 3,
                     (OTP_CAPLESS_LDO_VOUT_ADDR - OTP_BASE_ADDR), otp_20.kflag, otp_20.VOTRIM);
    }
    capless_ldo_vout_rsv_t otp_22 = {0, 0};
    if (pmu_get_otp(OTP_CAPLESS_LDO_VOUT_RSV_ADDR, (uint8_t *)&otp_22, sizeof(otp_22)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_%d, kflag[0x%X], NOCLDO_RSV[%d]", 3,
                     (OTP_CAPLESS_LDO_VOUT_RSV_ADDR - OTP_BASE_ADDR), otp_22.kflag, otp_22.NOCLDO_RSV);
    }
    ovp_vio_t otp_24 = {0, 0, 0, 0};
    if (pmu_get_otp(OTP_OVP_VIO_ADDR, (uint8_t *)&otp_24, sizeof(otp_24)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_%d, kflag[0x%X], OVP_VIO_VTH[0x%X], OVP_VIO_IBIAS[0x%X], OVP_VIO_VTH_LP[0x%X]", 5,
                     (OTP_OVP_VIO_ADDR - OTP_BASE_ADDR), otp_24.kflag, otp_24.OVP_VIO_VTH, otp_24.OVP_VIO_IBIAS, otp_24.OVP_VIO_VTH_LP);
    }
    ovp_nocldo_t otp_28 = {0, 0, 0};
    if (pmu_get_otp(OTP_OVP_NOCLDO_ADDR, (uint8_t *)&otp_28, sizeof(otp_28)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_%d, kflag[0x%X], OVP_NOCLDO_VTH[0x%X], OVP_NOCLDO_IBIAS[0x%X]", 4,
                     (OTP_OVP_NOCLDO_ADDR - OTP_BASE_ADDR), otp_28.kflag, otp_28.OVP_NOCLDO_VTH, otp_28.OVP_NOCLDO_IBIAS);
    }
    vcore_ldo_t otp_31 = {0, 0};
    if (pmu_get_otp(OTP_VCORE_LDO_ADDR, (uint8_t *)&otp_31, sizeof(otp_31)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_%d, kflag[0x%X], VCORE_VOTRIM[0x%X]", 3,
                     (OTP_VCORE_LDO_ADDR - OTP_BASE_ADDR), otp_31.kflag, otp_31.VCORE_VOTRIM);
    }
    vcore_ldo_dummy_load_t otp_33 = {0, 0};
    if (pmu_get_otp(OTP_VCORE_LDO_DUMMY_LOAD_ADDR, (uint8_t *)&otp_33, sizeof(otp_33)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_%d, kflag[0x%X], VCORE_DL[0x%X]", 3,
                     (OTP_VCORE_LDO_DUMMY_LOAD_ADDR - OTP_BASE_ADDR), otp_33.kflag, otp_33.VCORE_DL);
    }
    lpbg_tctrim_t otp_36 = {0, 0};
    if (pmu_get_otp(OTP_LPBG_TCTRIM_ADDR, (uint8_t *)&otp_36, sizeof(otp_36)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_%d, kflag[0x%X], LPBG_TCTRIM[0x%X]", 3,
                     (OTP_LPBG_TCTRIM_ADDR - OTP_BASE_ADDR), otp_36.kflag, otp_36.LPBG_TCTRIM);
    }
    lpbg_ibtrim_t otp_38 = {0, 0};
    if (pmu_get_otp(OTP_LPBG_IBTRIM_ADDR, (uint8_t *)&otp_38, sizeof(otp_38)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_%d, kflag[0x%X], LPBG_IBTRIM[0x%X]", 3,
                     (OTP_LPBG_IBTRIM_ADDR - OTP_BASE_ADDR), otp_38.kflag, otp_38.LPBG_IBTRIM);
    }
    lpbg_vref_t otp_40 = {0, 0, 0, 0, 0};
    if (pmu_get_otp(OTP_LPBG_VREF_ADDR, (uint8_t *)&otp_40, sizeof(otp_40)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_%d, kflag[0x%X], LPBG_VREF1P0TRIM[0x%X], LPBG_VREF0P5TRIM[0x%X], LPBG_VREF0P5_UVLO_TRIM1[0x%X], LPBG_VREF0P5_UVLO_TRIM2[0x%X]", 6,
                     (OTP_LPBG_VREF_ADDR - OTP_BASE_ADDR), otp_40.kflag, otp_40.LPBG_VREF1P0TRIM, otp_40.LPBG_VREF0P5TRIM, otp_40.LPBG_VREF0P5_UVLO_TRIM1, otp_40.LPBG_VREF0P5_UVLO_TRIM2);
    }
    hpbg_tctrim_t otp_45 = {0, 0};
    if (pmu_get_otp(OTP_HPBG_TCTRIM_ADDR, (uint8_t *)&otp_45, sizeof(otp_45)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_%d, kflag[0x%X], HPBG_TCTRIM[0x%X]", 3,
                     (OTP_HPBG_TCTRIM_ADDR - OTP_BASE_ADDR), otp_45.kflag, otp_45.HPBG_TCTRIM);
    }
    hpbg_vref_t otp_47 = {0, 0};
    if (pmu_get_otp(OTP_HPBG_VREF_ADDR, (uint8_t *)&otp_47, sizeof(otp_47)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_%d, kflag[0x%X], HPBG_VREF0P5TRIM[0x%X]", 3,
                     (OTP_HPBG_VREF_ADDR - OTP_BASE_ADDR), otp_47.kflag, otp_47.HPBG_VREF0P5TRIM);
    }
    vio18_vout_t otp_49 = {0, 0, 0};
    if (pmu_get_otp(OTP_VIO18_VOUT_ADDR, (uint8_t *)&otp_49, sizeof(otp_49)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_%d, kflag[0x%X], NM_VOTRIM_1p8[0x%X], NM_VOTRIM_1p5[0x%X]", 4,
                     (OTP_VIO18_VOUT_ADDR - OTP_BASE_ADDR), otp_49.kflag, otp_49.NM_VOTRIM_1p8, otp_49.NM_VOTRIM_1p5);
    }
    vio18_ret_vout_t otp_52 = {0, 0, 0};
    if (pmu_get_otp(OTP_VIO18_RET_VOUT_ADDR, (uint8_t *)&otp_52, sizeof(otp_52)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_%d, kflag[0x%X], RET_VOTRIM_1p8[0x%X], RET_VOTRIM_1p5[0x%X]", 4,
                     (OTP_VIO18_RET_VOUT_ADDR - OTP_BASE_ADDR), otp_52.kflag, otp_52.RET_VOTRIM_1p8, otp_52.RET_VOTRIM_1p5);
    }
    vio18_oc_t otp_55 = {0, 0};
    if (pmu_get_otp(OTP_VIO18_OC_ADDR, (uint8_t *)&otp_55, sizeof(otp_55)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_%d, kflag[0x%X], OCTRIM[0x%X]", 3,
                     (OTP_VIO18_OC_ADDR - OTP_BASE_ADDR), otp_55.kflag, otp_55.OCTRIM);
    }
    buck_rf_ulp_trim_t otp_57 = {0, 0, 0, 0, 0, 0};
    if (pmu_get_otp(OTP_BUCK_RF_ULP_TRIM_ADDR, (uint8_t *)&otp_57, sizeof(otp_57)) == PMU_STATUS_SUCCESS) {
        log_pmu_info("pmu_otp_dump, otp_%d, kflag[0x%X], BUCK_VRF_R1[0x%X], BUCK_VRF_R2[0x%X], BUCK_VRF_COMP_MIS[0x%X], BUCK_VRF_VOCAL_LP_IQDN_TRIM[0x%X], BUCK_VRF_LP_TRIM_STEP[0x%X]", 7,
                     (OTP_BUCK_RF_ULP_TRIM_ADDR - OTP_BASE_ADDR), otp_57.kflag, otp_57.BUCK_VRF_R1, otp_57.BUCK_VRF_R2,
                      otp_57.BUCK_VRF_COMP_MIS, otp_57.BUCK_VRF_VOCAL_LP_IQDN_TRIM, otp_57.BUCK_VRF_LP_TRIM_STEP);
    }
#endif
}

void pmu_cal_init(void)
{
    pmu_otp_dump();
    pmu_get_otp_ft_id();
    pmu_get_ddie_ver();
    pmu_strup_rg_unlock();
    pmu_lpbg_tctrim();
    pmu_lpbg_ibtrim();
    pmu_lpbg_vref();
    pmu_hpbg_tctrim();
    pmu_hpbg_vref();
    pmu_lpo32_freqk();
    pmu_buck_rf_bias();
    pmu_buck_rf_vout();
    pmu_buck_rf_timer();
    pmu_buck_rf_oc();
    pmu_buck_rf_zc();
    pmu_vcore_ldo();
    pmu_vcore_ldo_dummy_load();
    pmu_vio18_vout();
    pmu_vio18_ret_vout();
    pmu_vio18_oc();
    pmu_capless_ldo_vout();
    pmu_capless_ldo_vout_rsv();
    pmu_ovp_vio();
    pmu_ovp_nocldo();
    pmu_strup_rg_lock();

    log_pmu_info("pmu_cal_init", 0);
}

#endif  /* HAL_PMU_MODULE_ENABLED */
