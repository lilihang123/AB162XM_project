/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
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

#include "zephyr/sys/__assert.h"
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/init.h>
#if IS_ENABLED(CONFIG_AIR_DAEMON_WORKQUEUE_ENABLE)
#include "air_daemon_work_q.h"
#endif
#include <stdint.h>
#include <soc.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "air_chip.h"
#include "hal_log.h"
#include "hal_gpio.h"
#include "hal_gpio_internal.h"
#include "hal_gpt.h"
#include "hal_gpt_internal.h"
#include "memory_attribute.h"
#include "bm_core.h"
#include "bm_cust.h"

#ifdef AIR_NVKEY_ENABLE
#include "nvkey.h"
#include "nvkey_id_def.h"
#endif

#ifdef HAL_AIOADC_MODULE_ENABLED
#include "hal_aioadc.h"
#endif


#ifdef AIR_BATTERY_MANAGEMENT_ENABLE
#if defined(__EXT_BOOTLOADER__) || defined(__EXT_DA__)
#define log_bm_info(msg, cnt, ...)
#define log_bm_warn(msg, cnt, ...)
#define log_bm_error(msg, cnt, ...)
#else
#define log_bm_info(msg, cnt, ...)             printk("[BM_CUST] "msg"\r\n", ##__VA_ARGS__)
#define log_bm_warn(msg, cnt, ...)             printk("[BM_CUST] "msg"\r\n", ##__VA_ARGS__)
#define log_bm_error(msg, cnt, ...)            printk("[BM_CUST] "msg"\r\n", ##__VA_ARGS__)
#endif

#define UNUSED(x)  ((void)(x))

#if defined(AIR_BTD_IC_PREMIUM_G1)
#define BM_SOC_ADJUSTMENT_ENABLE
#elif defined(AIR_BTD_IC_MANDATORY_G1)
#else
    #error "Unkown Airoha Chip Series"
#endif

bm_info_t bm_info;
bm_info_t bm_info_old;
bm_func_t bm_cb_func[BM_CB_MAX][BM_USER_MAX];
uint32_t bm_timer_cnt = 0;
uint8_t bm_cust_init_done = PMU_OFF;


/* BM API */
void bm_get_vbat(void)
{
    uint16_t vbat = 4000;
#if defined(HAL_BAT_MODULE_ENABLED)
    vbat = bat_get_vbat();
#elif defined(AIR_BATTERY_MANAGEMENT_EXTERNAL_ENABLE)
    vbat = bm_get_vbat_ext();
#else
    log_bm_error("bm_get_vbat is not supported", 0);
    return;
#endif
    bm_info.vbat = vbat;
    log_bm_info("bm_get_vbat, vbat[%dmV]", 1, bm_info.vbat);

    if ((bm_info.vbat != bm_info_old.vbat) || (bm_cust_init_done == PMU_OFF)) {
        if (bm_cb_func[BM_CB_VBAT][BM_USER_APP].bm_callback) {
            bm_cb_func[BM_CB_VBAT][BM_USER_APP].bm_callback(&bm_info.vbat);
        }
    }
    bm_info_old.vbat = bm_info.vbat;
    return;
}

void bm_get_soc(void)
{
    uint8_t soc = 80;
#if defined(AIR_GM10P_ENABLE)
    soc = fg_get_sm_soc();
#elif defined(HAL_BAT_MODULE_ENABLED)
    soc = bat_get_soc(bm_info.vbat);
#elif defined(AIR_BATTERY_MANAGEMENT_EXTERNAL_ENABLE)
    soc = bm_get_soc_ext();
#else
    log_bm_error("bm_get_soc is not supported", 0);
    return;
#endif
    if (bm_cust_init_done == PMU_OFF) {
        bm_info.soc = soc;
    } else {
#if defined(BM_SOC_ADJUSTMENT_ENABLE)
        if (((bm_info.chg_en_sta == true) && (bm_info_old.soc > soc)) || ((bm_info.chg_en_sta == false) && (bm_info_old.soc < soc))) {
            log_bm_error("bm_get_soc unexpected, chg_en_sta[%d], soc[%d%], old_soc[%d%] keep", 3, bm_info.chg_en_sta, soc, bm_info_old.soc);
            soc = bm_info_old.soc;
        }
#endif
        bm_info.soc = (uint8_t)pmu_round((soc + bm_info_old.soc), 2);
    }
    log_bm_info("bm_get_soc, soc[%d%]", 1, bm_info.soc);

    if ((bm_info.soc != bm_info_old.soc) || (bm_cust_init_done == PMU_OFF)) {
        if (bm_cb_func[BM_CB_SOC][BM_USER_APP].bm_callback) {
            bm_cb_func[BM_CB_SOC][BM_USER_APP].bm_callback(&bm_info.soc);
        }
    }
    bm_info_old.soc = bm_info.soc;
    return;
}

void bm_get_temp(void)
{
    int16_t temp = 25;
#if defined(AIR_BATTERY_MANAGEMENT_EXTERNAL_ENABLE)
    temp = bm_get_temp_ext();
#else
    log_bm_error("bm_get_temp is not supported", 0);
    return;
#endif
    bm_info.temp = temp;
    log_bm_info("bm_get_temp, temp[%d]", 1, bm_info.temp);

    if ((bm_info.temp != bm_info_old.temp) || (bm_cust_init_done == PMU_OFF)) {
        if (bm_cb_func[BM_CB_TEMP][BM_USER_APP].bm_callback) {
            bm_cb_func[BM_CB_TEMP][BM_USER_APP].bm_callback(&bm_info.temp);
        }
    }
    bm_info_old.temp = bm_info.temp;
    return;
}

void bm_get_chg_exist(void)
{
    bool chg_exist = false;
#if defined(AIR_BATTERY_MANAGEMENT_EXTERNAL_ENABLE)
    chg_exist = (bool)bm_get_chg_exist_ext();
#else
    chg_exist = (bool)pmu_get_usb_plugin_status();
#endif
    bm_info.chg_exist = chg_exist;
    log_bm_info("bm_get_chg_exist, chg_exist[%d]", 1, bm_info.chg_exist);

    if ((bm_info.chg_exist != bm_info_old.chg_exist) || (bm_cust_init_done == PMU_OFF)) {
        if (bm_cb_func[BM_CB_CHG_EXIST][BM_USER_APP].bm_callback) {
            bm_cb_func[BM_CB_CHG_EXIST][BM_USER_APP].bm_callback(&bm_info.chg_exist);
        }
    }
    bm_info_old.chg_exist = bm_info.chg_exist;
    return;
}

void bm_get_chg_sta(void)
{
    uint8_t chg_sta = CHG_STA_IDLE;
#if defined(AIR_BATTERY_MANAGEMENT_EXTERNAL_ENABLE)
    chg_sta = bm_get_chg_sta_ext();
#else
    if (bm_info.chg_exist == false) {
        chg_sta = CHG_STA_IDLE;
    } else if (bm_info.vbat >= bm_info.full_bat - 300) {
        chg_sta = CHG_STA_CV;
        if (bm_info.vbat >= bm_info.full_bat) {
            chg_sta = CHG_STA_EOC;
        }
    } else {
        chg_sta = CHG_STA_CC;
    }
#endif
    bm_info.chg_sta = chg_sta;
    log_bm_info("bm_get_chg_sta, chg_sta[%d]", 1, bm_info.chg_sta);

    if ((bm_info.chg_sta != bm_info_old.chg_sta) || (bm_cust_init_done == PMU_OFF)) {
        if (bm_cb_func[BM_CB_CHG_STA][BM_USER_APP].bm_callback) {
            bm_cb_func[BM_CB_CHG_STA][BM_USER_APP].bm_callback(&bm_info.chg_sta);
        }
    }
    if ((bm_info_old.chg_sta != CHG_STA_EOC) && (bm_info.chg_sta == CHG_STA_EOC)) {
        bm_chg_eoc_cb();
    }
    bm_info_old.chg_sta = bm_info.chg_sta;
    return;
}

void bm_get_chg_en_sta(void)
{
    bool chg_en_sta = false;
#if defined(AIR_BATTERY_MANAGEMENT_EXTERNAL_ENABLE)
    chg_en_sta = bm_get_chg_en_sta_ext();
#else
    if ((bm_info.chg_sta == CHG_STA_CC) || (bm_info.chg_sta == CHG_STA_CV)) {
        chg_en_sta = true;
    } else {
        chg_en_sta = false;
    }
#endif
    bm_info.chg_en_sta = chg_en_sta;
    log_bm_info("bm_get_chg_en_sta, chg_en_sta[%d]", 1, bm_info.chg_en_sta);

    if ((bm_info.chg_en_sta != bm_info_old.chg_en_sta) || (bm_cust_init_done == PMU_OFF)) {
        if (bm_cb_func[BM_CB_CHG_EN_STA][BM_USER_APP].bm_callback) {
            bm_cb_func[BM_CB_CHG_EN_STA][BM_USER_APP].bm_callback(&bm_info.chg_en_sta);
        }
    }
    bm_info_old.chg_en_sta = bm_info.chg_en_sta;
    return;
}

void bm_get_chg_curr(void)
{
    uint16_t chg_curr = 0;
#if defined(AIR_BATTERY_MANAGEMENT_EXTERNAL_ENABLE)
    chg_curr = bm_get_chg_curr_ext();
#else
    log_bm_error("bm_get_chg_curr is not supported", 0);
    return;
#endif
    bm_info.chg_curr = chg_curr;
    log_bm_info("bm_get_chg_curr, chg_curr[%d]", 1, bm_info.chg_curr);

    if ((bm_info.chg_curr != bm_info_old.chg_curr) || (bm_cust_init_done == PMU_OFF)) {
        if (bm_cb_func[BM_CB_CHG_CURR][BM_USER_APP].bm_callback) {
            bm_cb_func[BM_CB_CHG_CURR][BM_USER_APP].bm_callback(&bm_info.chg_curr);
        }
    }
    bm_info_old.chg_curr = bm_info.chg_curr;
    return;
}

void bm_chg_enable(bool en)
{
#if defined(AIR_BATTERY_MANAGEMENT_EXTERNAL_ENABLE)
    bm_chg_enable_ext(en);
#else
    log_bm_error("bm_chg_enable is not supported", 0);
    return;
#endif
    log_bm_info("bm_chg_enable, en[%d]", 1, en);
}

void bm_update_info(void)
{
    bm_get_temp();
    bm_get_chg_exist();
    bm_get_chg_sta();
    bm_get_chg_en_sta();
    bm_get_chg_curr();
    bm_get_vbat();
    bm_get_soc();
}

/* BM CB */
void bm_chg_in_cb(void)
{
    log_bm_info("bm_chg_in_cb", 0);
    bm_info.chg_exist = true;
    if (bm_cb_func[BM_CB_CHG_IN][BM_USER_APP].bm_callback) {
        bm_cb_func[BM_CB_CHG_IN][BM_USER_APP].bm_callback(NULL);
    }
}

void bm_chg_out_cb(void)
{
    log_bm_info("bm_chg_out_cb", 0);
    bm_info.chg_exist = false;
    bm_info.chg_sta = CHG_STA_IDLE;
    bm_info.chg_en_sta = false;
    if (bm_cb_func[BM_CB_CHG_OUT][BM_USER_APP].bm_callback) {
        bm_cb_func[BM_CB_CHG_OUT][BM_USER_APP].bm_callback(NULL);
    }
}

void bm_chg_eoc_cb(void)
{
    bm_info.chg_exist = true;
    bm_info.chg_sta = CHG_STA_EOC;
    bm_info.chg_en_sta = false;
    log_bm_info("bm_chg_eoc_cb", 0);
    if (bm_cb_func[BM_CB_CHG_EOC][BM_USER_APP].bm_callback) {
        bm_cb_func[BM_CB_CHG_EOC][BM_USER_APP].bm_callback(NULL);
    }
}

void bm_timer_to_cb(void)
{
    log_bm_info("bm_timer_to_cb", 0);
    if (bm_cb_func[BM_CB_TIMER_TO][BM_USER_APP].bm_callback) {
        bm_cb_func[BM_CB_TIMER_TO][BM_USER_APP].bm_callback(NULL);
    }
}

void bm_cb_init(void)
{
    pmu_register_callback(PMU_CB_USB_PLUGIN,  (pmu_callback_t)bm_chg_in_cb,  PMU_USER_BM);
    pmu_register_callback(PMU_CB_USB_PLUGOUT, (pmu_callback_t)bm_chg_out_cb, PMU_USER_BM);
}

/* BM INFO */
int32_t bm_get_info(bm_info_idx_t info_idx)
{
    int32_t value = 0;
    switch (info_idx) {
        case BM_VBAT:
            value = (int32_t)bm_info.vbat;
            break;
        case BM_SOC:
            value = (int32_t)bm_info.soc;
            break;
        case BM_TEMP:
            value = (int32_t)bm_info.temp;
            break;
        case BM_CHG_EXIST:
            value = (int32_t)bm_info.chg_exist;
            break;
        case BM_CHG_STA:
            value = (int32_t)bm_info.chg_sta;
            break;
        case BM_CHG_EN_STA:
            value = (int32_t)bm_info.chg_en_sta;
            break;
        case BM_CHG_CURR:
            value = (int32_t)bm_info.chg_curr;
            break;
        case BM_SD_BAT:
            value = (int32_t)bm_info.sd_bat;
            break;
        case BM_FULL_BAT:
            value = (int32_t)bm_info.full_bat;
            break;
        case BM_PNZCV:
            value = (int32_t)bm_info.pnzcv;
            break;

        default:
            break;
    }
    return value;
}

void bm_dump_info(void)
{
    log_bm_info("bm_dump_info, vbat[%dmV], soc[%d%], temp[%d], chg_exist[%d], chg_sta[%d], chg_en_sta[%d], chg_curr[%dmA], sd_bat[%dmV], full_bat[%dmV], pnzcv[%dmV]", 10,
                bm_get_info(BM_VBAT), bm_get_info(BM_SOC), bm_get_info(BM_TEMP), bm_get_info(BM_CHG_EXIST), bm_get_info(BM_CHG_STA),
                bm_get_info(BM_CHG_EN_STA), bm_get_info(BM_CHG_CURR), bm_get_info(BM_SD_BAT), bm_get_info(BM_FULL_BAT), bm_get_info(BM_PNZCV));
}

void bm_work_handler(struct k_work *work)
{
    log_bm_info("bm_work_handler", 0);
    bm_timer_cnt++;
    bm_update_info();
    bm_timer_to_cb();
    if ((bm_timer_cnt % 2) == 0) {
        bm_dump_info();
        bm_timer_cnt = 0;
    }
}

void bm_cust_init(void)
{
    //log_bm_info("bm_cust_init", 0);
    bm_nvkey_init();
    bm_data_init();
    bm_cb_init();
    bm_chg_init();
    bm_gauge_init();
    bm_update_info();
    bm_dump_info();
    bm_cust_init_done = PMU_ON;
}

#endif /* AIR_BATTERY_MANAGEMENT_ENABLE */
