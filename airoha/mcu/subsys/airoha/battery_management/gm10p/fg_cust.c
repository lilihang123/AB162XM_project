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

#include "zephyr/sys/__assert.h"
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/init.h>

#include <math.h>
#include "fg_sim.h"
#include "fg_nafg.h"
#include "fg_zcv.h"
#include "fg_cust.h"
#ifdef FG_SIM
#include <fstream>
#include "fg_sim_data.h"
using namespace std;
#else
#include "bm_core.h"
#ifdef AIR_NVKEY_ENABLE
#include "nvkey.h"
#include "nvkey_id_def.h"
#endif
#ifdef HAL_RTC_MODULE_ENABLED
#include "hal_rtc.h"
#endif
#endif

#ifdef AIR_SDK_ZCV_TABLE_ENABLE
#include "fg_zcv_tab_sdk.h"
#else
#include "fg_zcv_tab_cust.h"
#endif


#ifndef FG_SIM
#if defined(__EXT_BOOTLOADER__) || defined(__EXT_DA__)
#define log_fg_info(msg, cnt, ...)
#define log_fg_warn(msg, cnt, ...)
#define log_fg_error(msg, cnt, ...)
#else
#define log_fg_info(msg, cnt, ...)             printk(""msg"\r\n", ##__VA_ARGS__)
#define log_fg_warn(msg, cnt, ...)             printk(""msg"\r\n", ##__VA_ARGS__)
#define log_fg_error(msg, cnt, ...)            printk(""msg"\r\n", ##__VA_ARGS__)
#define printf(msg, ...)                       printk(""msg"\r\n", ##__VA_ARGS__)
#endif
#endif

#define FG_NV_SAVE_SOC_GAP                     1 // abs(pre_soc - curr_soc) >= FG_NV_SAVE_SOC_GAP, save data to nvkey

ATTR_ZIDATA_IN_TCM static uint32_t fg_tick_cnt = 0;
zcv_bat_stru zcv_bat;

int32_t fg_log_conv(double val, uint8_t digit)
{
    int32_t result = 0, offset = 0;
    if (val >= 0) {
        offset = 5;
    } else {
        offset = -5;
    }
    result = (int32_t)(val * pow(10, (digit + 1)) + offset) / 10;
    // log_fg_info("[BM_FG] fg_log_conv, result[%d], digit[%d]", 2, result, digit);

    return result;
}

void fg_get_time_dur(void)
{
#ifdef HAL_RTC_MODULE_ENABLED
    uint32_t time_dur_32k = 0;
    uint32_t fg_tick_cnt_old = fg_tick_cnt;
    fg_tick_cnt = hal_rtc_get_current(2);
    if (fg_tick_cnt >= fg_tick_cnt_old) {
        time_dur_32k = fg_tick_cnt - fg_tick_cnt_old;
    } else {
        time_dur_32k = fg_tick_cnt + (0xFFFFFFFF - fg_tick_cnt_old);
    }
    nafg.time_dur = pmu_round(time_dur_32k, 32768);
    log_fg_info("[BM_FG] fg_get_time_dur, fg_tick_cnt_old[%d], fg_tick_cnt[%d], nafg.time_dur[%d]", 3, fg_tick_cnt_old, fg_tick_cnt, nafg.time_dur);
#else
    log_fg_error("[BM_FG] fg_get_time_dur doesn't support", 0);
#endif
}

void fg_update_temp(void)
{
#ifdef FG_SIM
    nafg.temp = SIM_TEMP;
#else
    #ifdef AIR_BATTERY_MANAGEMENT_ENABLE
    nafg.temp = bm_get_info(BM_TEMP);
    #endif
#endif
}

bool fg_update_zcv(void)
{
    bool ret = false;
    int16_t dlt_temp = 0;

    if (nafg.temp > nafg.temp_old) {
        dlt_temp = nafg.temp - nafg.temp_old;
    } else {
        dlt_temp = nafg.temp_old - nafg.temp;
    }
#ifdef AIR_SDK_ZCV_TABLE_ENABLE
    if ((dlt_temp >= fg_cfg.dlt_temp_thrd) || ((nafg.temp_old <= 10) && (nafg.temp >= 11)) || ((nafg.temp <= 10) && (nafg.temp_old >= 11))) {
#else
    if ((dlt_temp >= fg_cfg.dlt_temp_thrd) || ((nafg.temp_old <= 14) && (nafg.temp >= 15)) || ((nafg.temp <= 14) && (nafg.temp_old >= 15))) {
#endif
        ret = true;
    }
    return ret;
}

bool fg_get_chg_exist(void)
{
    bool ret = false;
    int32_t chg_exist = 0;
#ifdef FG_SIM
    #ifdef IN_CHARGER
    chg_exist = 1;
    #endif
#else
    #ifdef AIR_BATTERY_MANAGEMENT_ENABLE
    chg_exist = bm_get_info(BM_CHG_EXIST);
    #endif
#endif
    if (chg_exist) {
        ret = true;
    }
    return ret;
}

void fg_get_charging_sta(void)
{
#ifdef FG_SIM
    #ifdef IN_CHARGER
    nafg.is_charging = 1;
    #else
    nafg.is_charging = 0;
    #endif
#else
    #ifdef AIR_BATTERY_MANAGEMENT_ENABLE
    nafg.chg_sta = bm_get_info(BM_CHG_STA);
    #endif
    if ((nafg.chg_sta == CHG_STA_CC) || (nafg.chg_sta == CHG_STA_CV)) {
        nafg.is_charging = 1;
    } else {
        nafg.is_charging = 0;
    }
    // log_fg_info("[BM_FG] fg_get_charging_sta, chg_sta[%d], is_charging[%d]", 2, nafg.chg_sta, nafg.is_charging);
#endif
}

void fg_get_i_max_thrd(void)
{
    double i_max_tmp = 0;
#ifdef FG_SIM
    i_max_tmp = I_MAX_THRD;
#else
    i_max_tmp = (double)(bm_get_info(BM_CHG_CURR) * (-1));
#endif
    if ((nafg.i_max_thrd) && (nafg.cv_flag) && (i_max_tmp < nafg.i_max_thrd)) {
        // re-calculate v_tune, todo(nice to have)
        nafg.cv_flag = 0;
        nafg.v_tune_flag = 0;
#if defined (FG_FIXED_POINT_CONVERT)
        log_fg_info("[BM_FG] fg_get_i_max_thrd, unexpected, i_max_tmp[%d], i_max_thrd[%d]\n", 2, (int32_t)i_max_tmp, (int32_t)nafg.i_max_thrd);
#else
        printf("[BM_FG] fg_get_i_max_thrd, unexpected, i_max_tmp[%5.2f], i_max_thrd[%5.2f]\n", i_max_tmp, nafg.i_max_thrd);
#endif
    }
    nafg.i_max_thrd = i_max_tmp;
}

void fg_get_sd_bat(void)
{
    nafg.sd_bat = (uint16_t)bm_get_info(BM_SD_BAT) * 10;
}

double fg_get_cm_i(void)
{
    double cm_i = 0;
#ifdef FG_SIM
    cm_i = (double)curr_data[nafg.idx / 10];
#else
    // cm_i = (double)(pmu_get_chg_curr() * (-1));    // todo c mode
#endif
    return cm_i;
}

void fg_sd_bat_init(void)
{
#ifdef FG_SIM
    nafg.sd_bat = SD_VBAT;
#else
    nafg.sd_bat = bm_get_info(BM_SD_BAT) * 10;
#endif
    log_fg_info("[BM_FG] fg_sd_bat_init, sd_bat[%d]", 1, nafg.sd_bat);
}

void fg_pnzcv_init(void)
{
#ifdef FG_SIM
    nafg.pnzcv = vbat_data[0];
#else
    nafg.pnzcv = bm_get_info(BM_PNZCV) * 10;
#endif
    nafg.vbat = nafg.pnzcv;
    log_fg_info("[BM_FG] fg_pnzcv_init, pnzcv[%d]", 1, nafg.pnzcv);
}

void fg_get_cv_thrd(void)
{
    uint16_t full_bat = 0;
#ifdef FG_SIM
    full_bat = FULL_VBAT;
#else
    full_bat = (uint16_t)bm_get_info(BM_FULL_BAT) * 10;
#endif
    nafg.cv_thrd = full_bat - fg_cfg.cv_offset;
    nafg.cv_rsv_thrd = nafg.cv_thrd - fg_cfg.cv_rev_offset;
#ifdef FG_DBG_LOG_ENABLE
    log_fg_info("[BM_FG] fg_get_cv_thrd, full_bat[%d], cv_thrd[%d], cv_rsv_thrd[%d]", 3, full_bat, nafg.cv_thrd, nafg.cv_rsv_thrd);
#endif
}

void fg_ocv_soc_sel(double soc)
{
    if ((((double)fg_nv.pre_soc - soc) > (double)fg_cfg.soc_gap_thrd) ||
       (((soc - (double)fg_nv.pre_soc) > (double)fg_cfg.soc_gap_thrd) && (fg_get_chg_exist() == false))) {
        nafg.ocv = nafg.pnzcv;
        nafg.soc = soc;
    } else {
        nafg.ocv = (double)fg_nv.pre_ocv;
        nafg.soc = (double)fg_nv.pre_soc;
    }
}

void fg_save_ocv_soc(void)
{
    uint8_t soc = 0, dlt_soc = 0;
    soc = (uint8_t) ((nafg.soc * 10 + 5) / 10);
    if (soc > fg_nv.pre_soc) {
        dlt_soc = soc - fg_nv.pre_soc;
    } else {
        dlt_soc = fg_nv.pre_soc - soc;
    }
    if (dlt_soc >= FG_NV_SAVE_SOC_GAP) {
        fg_nv.pre_ocv = (uint32_t) ((nafg.ocv * 10 + 5) / 10);
        fg_nv.pre_soc = soc;
#ifndef FG_SIM
        log_fg_info("[BM_FG] fg_save_ocv_soc, pre_ocv[%d], pre_soc[%d]", 2, fg_nv.pre_ocv, fg_nv.pre_soc);
#endif
        fg_set_nvkey();
    }
}

bool fg_eoc_check(void)
{
    bool ret = false;

#ifdef FG_SIM
    #ifndef IN_CHARGER
    return ret;
    #endif
    if (nafg.idx == FG_EOC_TRIGGER_IDX) {
#else
    if ((nafg.chg_sta_old == CHG_STA_CV) && (nafg.chg_sta == CHG_STA_EOC)) {
#endif
        ret = true;
    }
    nafg.chg_sta_old = nafg.chg_sta;
    return ret;
}

uint32_t fg_sm_soc_comp(void)
{
    double soc = 0;
    uint32_t comp_soc = 0;

    if ((fg_sm.sm_soc == 0) || (fg_sm.sm_soc == 100)) {
        soc = fg_sm.sm_soc;
    } else {
        if (fg_sm.sm_soc >= fg_cfg.soc_100_comp_start) {
            soc = fg_cfg.soc_100_comp_start + (fg_sm.sm_soc - fg_cfg.soc_100_comp_start) * (100 - fg_cfg.soc_100_comp_start) / (fg_cfg.soc_100_comp_end - fg_cfg.soc_100_comp_start);
        } else if (fg_sm.sm_soc <= fg_cfg.soc_0_comp_start) {
            soc = fg_cfg.soc_0_comp_start - (fg_cfg.soc_0_comp_start - fg_sm.sm_soc) * (fg_cfg.soc_0_comp_start - 0) / (fg_cfg.soc_0_comp_start - fg_cfg.soc_0_comp_end);
        } else {
            soc = fg_sm.sm_soc;
        }
        if (soc > 100) {
            soc = 100;
        } else if (soc < 0) {
            soc = 0;
        }
    }
    comp_soc = ((uint32_t)(soc * 10) + 5) / 10;
    return comp_soc;
}

uint32_t fg_get_sm_soc(void)
{
    uint32_t sm_soc = 0;
    if (fg_cfg.soc_comp_en) {
        sm_soc = fg_sm_soc_comp();
    } else {
        sm_soc = ((uint32_t)(fg_sm.sm_soc * 10) + 5) / 10;
    }
    return sm_soc;
}

void fg_sm_init(void)
{
    fg_sm.sm_arr_idx = 0;
    fg_sm.sm_arr_num = 0;
    fg_sm.sm_soc = -1;
    fg_sm.sm_soc_old = -1;
    if (fg_cfg.sm_act_arr_size > FG_SM_MAX_ARR_SIZE) {
        fg_cfg.sm_act_arr_size = FG_SM_MAX_ARR_SIZE;
    }
    for (int i = 0; i < FG_SM_MAX_ARR_SIZE; i++) {
        fg_sm.sm_soc_arr[i] = 0;
    }
    log_fg_info("[BM_FG] fg_sm_init, sm_act_arr_size[%d], FG_SM_MAX_ARR_SIZE[%d]", 2, fg_cfg.sm_act_arr_size, FG_SM_MAX_ARR_SIZE);
}

void fg_data_init(void)
{
    nafg.idx = 0;
    nafg.chg_sta = -1;
    nafg.chg_sta_old = -1;
    nafg.is_charging = 0;
    nafg.charging_sta = -1;
    nafg.qmax = 0;
    nafg.init_qmax = 0;
    nafg.vm_total_car = 0;
    nafg.cm_total_car = 0;
    nafg.vbat_arr_idx = 0;
    nafg.vbat_arr_num = 0;
    nafg.cv_cnt = 0;
    nafg.cv_thrd = 0;
    nafg.cv_rsv_thrd = 0;
    nafg.cv_flag = 0;
    nafg.pt_i_comp_flag = 0;
    nafg.v_tune_flag = 0;
    nafg.i_tune_flag = 0;
    nafg.i_max_thrd = 0;
    nafg.pt_dlt_vbat = 0;
    nafg.pt_r = 0;
    nafg.pt_ocv = 0;
    nafg.pt_vbat = 0;
    nafg.v_tune = 0;
    nafg.i_tune = 0;
    nafg.soc = 0;
    nafg.temp_old = -99;
    nafg.i_coef_conv = (double)fg_cfg.i_coef_conv / FG_I_COEF_CONV;
    nafg.aging_vector = (double)fg_nv.aging_coef_conv / FG_FIX_POINT_CONV;

#if defined (FG_FIXED_POINT_CONVERT)
    log_fg_info("[BM_FG] fg_data_init, i_coef_conv[%d(2)], aging_vector[%d(2)]", 2,
                (uint32_t)(nafg.i_coef_conv * 100), (uint32_t)(nafg.aging_vector * 100));
#else
    printf("[BM_FG] fg_data_init, i_coef_conv[%3.2f], aging_vector[%3.2f]\n", nafg.i_coef_conv, nafg.aging_vector);
#endif
}

void fg_zcv_init(void)
{
    uint8_t bat_id = 0;
#ifndef FG_SIM
    // bat_id = bm_cust.battery_category - 1;
#endif
    log_fg_info("[BM_FG] fg_zcv_init, bat_id[%d], temp_num[%d]", 2, bat_id, ZCV_TEMP_NUM);

    uint32_t zcv_size = sizeof(zcv_stru) * ZCV_DATA_SIZE;
    memcpy(zcv_bat.zcv_temp[0].zcv, fg_zcv_t0[bat_id], zcv_size);
    memcpy(zcv_bat.zcv_temp[1].zcv, fg_zcv_t1[bat_id], zcv_size);
    memcpy(zcv_bat.zcv_temp[2].zcv, fg_zcv_t2[bat_id], zcv_size);
    memcpy(zcv_bat.zcv_temp[3].zcv, fg_zcv_t3[bat_id], zcv_size);
    memcpy(zcv_bat.zcv_temp[4].zcv, fg_zcv_t4[bat_id], zcv_size);

    for (int i = 0; i < ZCV_TEMP_NUM; i++) {
        zcv_bat.zcv_temp[i].temp = fg_zcv_temp[i];
        log_fg_info("[BM_FG] fg_zcv_init, temp%d[%d]", 2, (i + 1), zcv_bat.zcv_temp[i].temp);
    }
}

void fg_noti(void)
{
#ifdef FG_SIM
    printf("[BM_FG] fg_noti, TEMP: %d, is_charging %d, VBAT: %d, fg_soc: %d, sm_soc: %d, comp_soc: %d",
           nafg.temp, nafg.is_charging, nafg.vbat, fg_get_soc(), fg_get_sm_soc(), fg_sm_soc_comp());
#else
    #if defined (FG_FIXED_POINT_CONVERT)
    log_fg_info("[BM_FG] fg_noti, TEMP: %d, is_charging %d, VBAT: %d, fg_soc: %d, sm_soc: %d, comp_soc: %d", 6,
                nafg.temp, nafg.is_charging, fg_log_conv(nafg.vbat, 0), fg_get_soc(), fg_get_sm_soc(), fg_sm_soc_comp());
    #else
    log_fg_info("[BM_FG] fg_noti, TEMP: %d, is_charging %d, VBAT: %d, fg_soc: %d, sm_soc: %d, comp_soc: %d", 6,
                nafg.temp, nafg.is_charging, nafg.vbat, fg_get_soc(), fg_get_sm_soc(), fg_sm_soc_comp());
    #endif
#endif
}
