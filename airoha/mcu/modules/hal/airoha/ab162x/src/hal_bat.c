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
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hal_eint.h"
#include "hal_nvic.h"
#include "hal_nvic_internal.h"
#include "hal_gpio.h"
#include "hal_gpio_internal.h"
#include "hal_gpt.h"
#include "hal_gpt_internal.h"
#include "hal_clock_internal.h"
#include "hal_pmu_platform.h"
#include "hal_pmu_cal.h"
#include "hal_bat.h"
#include "memory_attribute.h"
#include <soc.h>
#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>

#ifdef AIR_NVKEY_ENABLE
#include "nvkey.h"
#include "nvkey_id_def.h"
#endif

#ifdef HAL_AIOADC_MODULE_ENABLED
#include "hal_aioadc.h"
#endif

uint16_t pnzcv = 4000;

#ifdef HAL_BAT_MODULE_ENABLED
#if defined(__EXT_BOOTLOADER__) || defined(__EXT_DA__)
#define log_bat_info(msg, cnt, ...)
#define log_bat_warn(msg, cnt, ...)
#define log_bat_error(msg, cnt, ...)
#else
#define log_bat_info(msg, cnt, ...)             printk("[HAL_BAT] "msg"\r\n", ##__VA_ARGS__)
#define log_bat_warn(msg, cnt, ...)             printk("[HAL_BAT] "msg"\r\n", ##__VA_ARGS__)
#define log_bat_error(msg, cnt, ...)            printk("[HAL_BAT] "msg"\r\n", ##__VA_ARGS__)
#endif

#define UNUSED(x)  ((void)(x))

bat_func_t bat_cb_func[BAT_CB_MAX][BAT_USER_MAX];
uint8_t bat_init_flag = 0;
bat_adc_t bat_adc;
bat_volt_t bat_volt;

#define BAT_LINEAR_GAUGE_LV                     9

/* BAT API */
#ifdef HAL_AIOADC_MODULE_ENABLED
uint8_t bat_get_adc_ch(hal_gpio_pin_t gpio_pin)
{
    uint8_t adc_ch = (uint8_t)HAL_AIOADC_CH_0;
    if ((gpio_pin >= HAL_GPIO_25) && (gpio_pin <= HAL_GPIO_34)) {
        adc_ch = gpio_pin - HAL_GPIO_25;
    } else {
        log_bat_error("bat_get_adc_ch fail, gpio_pin[%d] isn't in GPIO_25 ~ GPIO_34", 1, gpio_pin);
    }
    //log_bat_info("bat_get_adc_ch, gpio_pin[%d], adc_ch[%d]", 2, gpio_pin, adc_ch);
    return adc_ch;
}

void bat_gpio_adc_enable(hal_gpio_pin_t gpio_pin)
{
    hal_pinmux_set_function(gpio_pin, GPIO_AUX_MODE0);
    hal_gpio_set_direction(gpio_pin, HAL_GPIO_DIRECTION_OUTPUT);
    hal_gpio_set_output(gpio_pin, HAL_GPIO_DATA_HIGH);
    // log_bat_info("bat_gpio_adc_enable, GPIO%d set HIGH", 1, gpio_pin);
}

void bat_gpio_adc_disable(hal_gpio_pin_t gpio_pin)
{
    hal_gpio_set_output(gpio_pin, HAL_GPIO_DATA_LOW);
    // log_bat_info("bat_gpio_adc_disable, GPIO%d set LOW", 1, gpio_pin);
}
#endif

uint16_t bat_get_vbat(void)
{
    uint16_t vbat = 4000;
#ifdef HAL_AIOADC_MODULE_ENABLED
    int16_t adc_val = 0;
    if (bat_adc.r6215 == 0) {
        bat_adc.r6215 = 12400;
    }
    if (bat_adc.r6217 == 0) {
        bat_adc.r6217 = 10000;
    }
    hal_aioadc_ch_en_t adc_ch = bat_get_adc_ch(bat_adc.adc_pin);      //default GPIO25
    hal_aioadc_mode_sel_t adc_mode = HAL_AIOADC_MODE_SE_0;
    if (bat_adc.sel == BAT_DET_INT_VBAT) {
        adc_mode = HAL_AIOADC_MODE_VBAT;
        hal_aioadc_init(adc_ch, adc_mode,NULL);
        vbat = (uint16_t)hal_aioadc_get_voltage(adc_ch, adc_mode);
        hal_aioadc_deinit();
    } else if (bat_adc.sel == BAT_DET_EXT_GPIO) {
        hal_pinmux_set_function(bat_adc.adc_pin, GPIO_AUX_MODE11);
        adc_mode = HAL_AIOADC_MODE_SE_0;
        bat_gpio_adc_enable(bat_adc.adc_ctrl);                        //default GPIO34
        hal_aioadc_init(adc_ch, adc_mode, NULL);
        hal_gpt_delay_ms(bat_adc.settle_time);
        adc_val = hal_aioadc_get_voltage(adc_ch, adc_mode);
        vbat = (uint16_t)pmu_round((adc_val * (bat_adc.r6215 + bat_adc.r6217)), bat_adc.r6217);
        hal_aioadc_deinit();
        bat_gpio_adc_disable(bat_adc.adc_ctrl);
    } else {
        log_bat_error("bat_get_vbat fail, bat_adc.sel[%d] not support", 1, bat_adc.sel);
    }
#else
    log_bat_error("bat_get_vbat fail, ADC not support", 0);
#endif
    return vbat;
}

uint8_t bat_get_soc(uint16_t vbat)
{
    uint8_t i = 0, soc = 0;
    uint32_t min = bat_volt.sd_bat.volt;
    uint32_t max = bat_volt.vbat[BAT_LINEAR_GAUGE_LV].volt;

    if (vbat <= min) {
        soc = 0;
    } else if (vbat >= max) {
        soc = 100;
    } else {
        for (i = 0; i < BAT_LINEAR_GAUGE_LV; i++) {
            if (vbat < bat_volt.vbat[i].volt) {
                break;
            }
        }
        if (i == 0) {
            max = bat_volt.vbat[0].volt;
        } else if (i == BAT_LINEAR_GAUGE_LV) {
            min = bat_volt.vbat[BAT_LINEAR_GAUGE_LV - 1].volt;
        } else {
            min = bat_volt.vbat[i - 1].volt;
            max = bat_volt.vbat[i].volt;
        }
        soc = (uint8_t)(pmu_round((10 * (vbat - min)), (max - min)) + (i * 10));
    }
    log_bat_info("bat_get_soc, soc[%d%]", 1, soc);
    return soc;
}

uint16_t bat_get_sd_bat(void)
{
    uint16_t sd_bat = 0;
    sd_bat = bat_volt.sd_bat.volt;
    return sd_bat;
}

uint16_t bat_get_full_bat(void)
{
    uint16_t full_bat = 0;
    full_bat = bat_volt.full_bat.volt;
    return full_bat;
}

void bat_get_pnzcv(void)
{
    bat_init();
    pnzcv = bat_get_vbat();
    log_bat_info("bat_get_pnzcv, pnzcv[%d]\n", 1, pnzcv);
}

/* BAT CB */
bat_status_t bat_register_callback(bat_cb_t bat_cb, bat_callback_t callback, bat_user_t user)
{
    if ((bat_cb >= BAT_CB_MAX) || (callback == NULL) || (user >= BAT_USER_MAX)) {
        log_bat_error("bat_register_callback fail, bat_cb[%d], callback[0x%X], user[%d]", 3, bat_cb, callback, user);
        pmu_assert();
        return BAT_STATUS_INVALID_PARAMETER;
    }
    bat_cb_func[bat_cb][user].bat_callback = callback;
    log_bat_info("bat_register_callback ok, bat_cb[%d], user[%d]", 2, bat_cb, user);
    return BAT_STATUS_SUCCESS;
}

bat_status_t bat_deregister_callback(bat_cb_t bat_cb, bat_user_t user)
{
    if ((bat_cb >= BAT_CB_MAX) || (user >= BAT_USER_MAX)) {
        log_bat_error("bat_deregister_callback fail, bat_cb[%d], user[%d]", 2, bat_cb, user);
        pmu_assert();
        return BAT_STATUS_INVALID_PARAMETER;
    }
    bat_cb_func[bat_cb][user].bat_callback = NULL;
    log_bat_info("bat_deregister_callback ok, bat_cb[%d], user[%d]", 2, bat_cb, user);
    return BAT_STATUS_SUCCESS;
}

/* BAT INIT */
void bat_nvkey_init(void)
{
#ifdef AIR_NVKEY_ENABLE
    pmu_get_nvkey(NVID_CAL_VBAT_ADC_CAL_TABLE, (uint8_t *)&bat_adc, sizeof(bat_adc_t));
    pmu_get_nvkey(NVID_CAL_VBAT_VOLT_CFG, (uint8_t *)&bat_volt, sizeof(bat_volt_t));

    /* Allow Kconfig to override NVKEY values for custom hardware */
#ifdef CONFIG_AIR_BAT_ADC_CTRL_PIN
    bat_adc.adc_ctrl = CONFIG_AIR_BAT_ADC_CTRL_PIN;
#endif
#ifdef CONFIG_AIR_BAT_ADC_PIN
    bat_adc.adc_pin = CONFIG_AIR_BAT_ADC_PIN;
#endif
#ifdef CONFIG_AIR_BAT_ADC_SETTLE_TIME
    bat_adc.settle_time = CONFIG_AIR_BAT_ADC_SETTLE_TIME;
#endif
#ifdef CONFIG_AIR_BAT_ADC_R6215
    bat_adc.r6215 = CONFIG_AIR_BAT_ADC_R6215;
#endif
#ifdef CONFIG_AIR_BAT_ADC_R6217
    bat_adc.r6217 = CONFIG_AIR_BAT_ADC_R6217;
#endif
    bat_adc.sel= BAT_DET_EXT_GPIO;
    log_bat_info("bat_nvkey_init, 0x2020, kflag[%d], sel[%d](0:disable, 1:VBAT, 2:GPIO), adc_ctrl[GPIO%d], adc_pin[GPIO%d], settle_time[%dms], r6215[%d], r6217[%d]", 7,
                bat_adc.kflag, bat_adc.sel, bat_adc.adc_ctrl, bat_adc.adc_pin, bat_adc.settle_time, bat_adc.r6215, bat_adc.r6217);
    log_bat_info("bat_nvkey_init, 0x2021, kflag[%d], full_bat[%d], sd_bat(0%)[%d], 10%[%d], 20%[%d], 30%[%d], 40%[%d]", 7,
                bat_volt.kflag, bat_volt.full_bat.volt, bat_volt.sd_bat.volt, bat_volt.vbat[0].volt, bat_volt.vbat[1].volt, bat_volt.vbat[2].volt, bat_volt.vbat[3].volt);
    log_bat_info("bat_nvkey_init, 0x2021, 50%[%d], 60%[%d], 70%[%d], 80%[%d], 90%[%d], 100%[%d]", 6,
                bat_volt.vbat[4].volt, bat_volt.vbat[5].volt, bat_volt.vbat[6].volt, bat_volt.vbat[7].volt, bat_volt.vbat[8].volt, bat_volt.vbat[9].volt);
#else
    log_bat_info("bat_nvkey_init, nvkey not support)", 0);
#endif
}

void bat_init_internal(void)
{
    bat_init_flag = 1;
}

void bat_init(void)
{
    log_bat_info("bat_init", 0);
    bat_nvkey_init();
    bat_init_internal();
}
#endif /*   HAL_BAT_MODULE_ENABLED   */
