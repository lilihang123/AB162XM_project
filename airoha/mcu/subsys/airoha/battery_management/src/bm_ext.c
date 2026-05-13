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


#ifdef AIR_BATTERY_MANAGEMENT_ENABLE
#if defined(__EXT_BOOTLOADER__) || defined(__EXT_DA__)
#define log_bm_info(msg, cnt, ...)
#define log_bm_warn(msg, cnt, ...)
#define log_bm_error(msg, cnt, ...)
#else
#define log_bm_info(msg, cnt, ...)             printk("[BM_EXT] "msg"\r\n", ##__VA_ARGS__)
#define log_bm_warn(msg, cnt, ...)             printk("[BM_EXT] "msg"\r\n", ##__VA_ARGS__)
#define log_bm_error(msg, cnt, ...)            printk("[BM_EXT] "msg"\r\n", ##__VA_ARGS__)
#endif

#define UNUSED(x)  ((void)(x))

extern uint16_t pnzcv;
extern bm_info_t bm_info;
extern bm_info_t bm_info_old;

#if !defined (HAL_BAT_MODULE_ENABLED)
#ifdef AIR_NVKEY_ENABLE
#include "nvkey.h"
#include "nvkey_id_def.h"
#endif
bat_adc_t bm_adc;
bat_volt_t bm_volt;
#endif

/* BM EXT */
uint16_t bm_get_vbat_ext(void)
{
    uint16_t vbat = 4000;

    // implement for customized design

    return vbat;
}

uint8_t bm_get_soc_ext(void)
{
    uint8_t soc = 80;

    // implement for customized design

    return soc;
}

int16_t bm_get_temp_ext(void)
{
    int16_t temp = 25;

    // implement for customized design

    return temp;
}

bool bm_get_chg_exist_ext(void)
{
    bool chg_exist = false;

    // implement for customized design

    return chg_exist;
}

uint8_t bm_get_chg_sta_ext(void)
{
    uint8_t chg_sta = CHG_STA_IDLE;

    // implement for customized design

    return chg_sta;
}

bool bm_get_chg_en_sta_ext(void)
{
    bool chg_en_sta = false;

    if ((bm_info.chg_sta == CHG_STA_CC) || (bm_info.chg_sta == CHG_STA_CV)) {
        chg_en_sta = true;
    } else {
        chg_en_sta = false;
    }

    // implement for customized design

    return chg_en_sta;
}

uint16_t bm_get_chg_curr_ext(void)
{
    uint16_t chg_curr = 0;

    // implement for customized design

    return chg_curr;
}

void bm_chg_enable_ext(bool en)
{
    if ((en == true) && (bm_info.chg_exist == true)) {
        bm_info.chg_en_sta = PMU_ON;
    } else {
        bm_info.chg_en_sta = PMU_OFF;
    }

    // implement for customized design

}

void bm_chg_init(void)
{
    // implement for customized design

}

void bm_gauge_init(void)
{
#if defined(AIR_GM10P_ENABLE)
    fg_zcv_init();
    fg_init();
#else
    // implement for customized design

#endif
}

void bm_nvkey_init(void)
{
    // implement for customized design
#if !defined (HAL_BAT_MODULE_ENABLED)
#ifdef AIR_NVKEY_ENABLE
    pmu_get_nvkey(NVID_CAL_VBAT_ADC_CAL_TABLE, (uint8_t *)&bm_adc, sizeof(bat_adc_t));
    pmu_get_nvkey(NVID_CAL_VBAT_VOLT_CFG, (uint8_t *)&bm_volt, sizeof(bat_volt_t));
    log_bm_info("bm_nvkey_init, 0x2020, kflag[%d], sel[%d](0:disable, 1:VBAT, 2:GPIO), adc_ctrl[GPIO%d], adc_pin[GPIO%d], settle_time[%dms], r6215[%d], r6217[%d]", 7,
                bm_adc.kflag, bm_adc.sel, bm_adc.adc_ctrl, bm_adc.adc_pin, bm_adc.settle_time, bm_adc.r6215, bm_adc.r6217);
    log_bm_info("bm_nvkey_init, 0x2021, kflag[%d], full_bat[%d], sd_bat(0%)[%d], 10%[%d], 20%[%d], 30%[%d], 40%[%d]", 7,
                bm_volt.kflag, bm_volt.full_bat.volt, bm_volt.sd_bat.volt, bm_volt.vbat[0].volt, bm_volt.vbat[1].volt, bm_volt.vbat[2].volt, bm_volt.vbat[3].volt);
    log_bm_info("bm_nvkey_init, 0x2021, 50%[%d], 60%[%d], 70%[%d], 80%[%d], 90%[%d], 100%[%d]", 6,
                bm_volt.vbat[4].volt, bm_volt.vbat[5].volt, bm_volt.vbat[6].volt, bm_volt.vbat[7].volt, bm_volt.vbat[8].volt, bm_volt.vbat[9].volt);
#else
    log_bm_error("bm_nvkey_init, nvkey not support)", 0);
#endif
#endif /* HAL_BAT_MODULE_ENABLED */
}

void bm_data_init(void)
{
    bm_info.vbat          = 4000;
    bm_info.soc           = 80;
    bm_info.temp          = 25;
    bm_info.chg_exist     = false;
    bm_info.chg_sta       = CHG_STA_IDLE;
    bm_info.chg_en_sta    = false;
    bm_info.chg_curr      = 0;
    bm_info_old.soc       = 80;
#if defined(HAL_BAT_MODULE_ENABLED)
    bm_info.sd_bat        = bat_get_sd_bat();
    bm_info.full_bat      = bat_get_full_bat();
    bm_info.pnzcv         = pnzcv;
#else
    bm_info.sd_bat        = bm_volt.sd_bat.volt;
    bm_info.full_bat      = bm_volt.full_bat.volt;
    bm_info.pnzcv         = bm_get_vbat_ext();
#endif
}

#endif /* AIR_BATTERY_MANAGEMENT_ENABLE */
