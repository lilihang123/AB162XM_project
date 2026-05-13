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

#include "hal_pwm_internal_v1.h"
#include "hal_nvic.h"
#include "hal_clock.h"
#ifdef HAL_PWM_MODULE_ENABLED
static volatile PWM_REGISTER_T     *pwm[HAL_PWM_INTERNAL_MAX]            = {(PWM_REGISTER_T *)PWM0_BASE, (PWM_REGISTER_T *)PWM1_BASE, (PWM_REGISTER_T *)PWM2_BASE};
static          uint8_t             pwm_clk_src[HAL_PWM_INTERNAL_MAX]    = {0};
static          uint8_t             pwm_clk_div[HAL_PWM_INTERNAL_MAX]    = {0};
uint32_t pwm_clk[4] = {32000000, 32000, 26000000, 52000000};
static uint8_t pwm_status[HAL_PWM_INTERNAL_MAX];
#define pwm_status_init (1<<0)
#define pwm_status_start (1<<1)
#define pwm_status_freq (1<<2)
#define pwm_status_duty (1<<3)

#if 0
#define log_irtx_info(fmt, cnt, ...)     log_hal_msgid_info("[hal][rtc] " fmt, cnt, ##__VA_ARGS__)
#define log_irtx_warning(fmt, cnt, ...)  log_hal_msgid_warning("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#define log_irtx_error(fmt, cnt, ...)    log_hal_msgid_error("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#else
#define log_pwm_info(fmt, cnt, ...)     printk(fmt, ##__VA_ARGS__)
#define log_pwm_warning(fmt, cnt, ...)  printk(fmt, ##__VA_ARGS__)
#define log_pwm_error(fmt, cnt, ...)    printk(fmt, ##__VA_ARGS__)
#endif

static const  hal_clock_cg_id pwm_clock[HAL_PWM_INTERNAL_MAX] = {HAL_CLOCK_CG_PWM_2, HAL_CLOCK_CG_PWM_3, HAL_CLOCK_CG_PWM_4};
void pwm_open_clock_source(hal_pwm_channel_t pwm_channel)
{
#ifndef FPGA_ENV
    if (hal_clock_is_enabled(pwm_clock[pwm_channel]) == false) {
        hal_clock_enable(pwm_clock[pwm_channel]);
    }
#endif
}

void pwm_close_clock_source(hal_pwm_channel_t pwm_channel)
{
#ifndef FPGA_ENV
    if (hal_clock_is_enabled(pwm_clock[pwm_channel]) == true) {
        hal_clock_disable(pwm_clock[pwm_channel]);
    }
#endif
}
// extern  hal_clock_status_t          clock_mux_sel(clock_mux_sel_id mux_id, uint32_t mux_sel);
hal_pwm_status_t    pwm_init(hal_pwm_channel_t pwm_channel, hal_pwm_source_clock_t source_clock)
{
    uint8_t pwm_channel_v1 = (uint8_t)(pwm_channel - 8);
    pwm[pwm_channel_v1]->PWM_CTRL   = 0;
    pwm[pwm_channel_v1]->PWM_COUNT  = 0;
    pwm[pwm_channel_v1]->PWM_THRESH = 0;
    pwm[pwm_channel_v1]->PWM_THRESH_DOWN = 0;
    pwm[pwm_channel_v1]->PWM_POL = 0;
    pwm[pwm_channel_v1]->PWM_CTRL  |= ((source_clock & 0x03) << PWM_CLK_SEL_OFFSET);
    pwm_clk_src[pwm_channel_v1] = source_clock;
    return HAL_PWM_STATUS_OK;

}


hal_pwm_status_t    pwm_deinit(hal_pwm_channel_t pwm_channel)
{
    pwm_channel = pwm_channel;
    return HAL_PWM_STATUS_OK;
}


hal_pwm_status_t    pwm_set_frequency(hal_pwm_channel_t pwm_channel, uint32_t frequency, uint32_t *total_count)
{
    uint32_t    clock_div = 0, clk_div = 0;
    uint32_t    clock_pwm = 0;
    // uint32_t    control   = 0;
    uint32_t    min_frequency = 0;
    uint32_t    temp      = 0;
    uint8_t pwm_channel_v1 = (uint8_t)(pwm_channel - 8);
    for (clk_div = 0; clk_div < 4; clk_div++) {
        clock_div = 1 << clk_div;
        clock_pwm     = pwm_clk[pwm_clk_src[pwm_channel_v1]] / clock_div;
        min_frequency = clock_pwm / PWM_MAX_COUNT;
        if ((clk_div == 3) && (frequency < min_frequency)) {
            //log_pwm_error("[pwm] ch%d freq(%dHz) smaller than hw support(hw min freq %dHz)!\r\n", 3, pwm_channel_v1, frequency, min_frequency);
            return HAL_PWM_STATUS_INVALID_FREQUENCY;
        } else if (frequency > min_frequency) {
            temp = (clock_pwm / frequency);
            break;
        }
    }
    if (temp > 0) {
        pwm_clk_div[pwm_channel_v1] = clk_div;
        pwm[pwm_channel_v1]->PWM_COUNT = temp - 1;
        *total_count = temp;
        pwm_status[pwm_channel_v1] |= pwm_status_freq;
        return HAL_PWM_STATUS_OK;
    } else {
        log_pwm_error("[pwm] ch%d freq(%dHz) bigger than hw support(hw min freq %dHz)!\r\n", 3, pwm_channel_v1, frequency, clock_pwm);
        return HAL_PWM_STATUS_INVALID_FREQUENCY;
    }
    return HAL_PWM_STATUS_OK;
}


hal_pwm_status_t    pwm_set_duty_cycle(hal_pwm_channel_t pwm_channel, uint32_t duty_cycle)
{
    uint32_t    temp  = 0;
    uint8_t pwm_channel_v1 = (uint8_t)(pwm_channel - 8);
    temp = pwm[pwm_channel_v1]->PWM_COUNT;
    pwm[pwm_channel_v1]->PWM_THRESH_DOWN = 0;
    if (0 == duty_cycle) {
        pwm[pwm_channel_v1]->PWM_THRESH_DOWN = 1;
        pwm[pwm_channel_v1]->PWM_THRESH      = 0;
    } else if (duty_cycle > temp) {
        pwm[pwm_channel_v1]->PWM_THRESH = temp;
    } else {
        pwm[pwm_channel_v1]->PWM_THRESH = duty_cycle - 1;
    }
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    pwm_start(hal_pwm_channel_t pwm_channel)
{
    uint8_t pwm_channel_v1 = (uint8_t)(pwm_channel - 8);
    pwm_open_clock_source(pwm_channel_v1);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    pwm_stop(hal_pwm_channel_t pwm_channel)
{
    uint8_t pwm_channel_v1 = (uint8_t)(pwm_channel - 8);
    pwm_close_clock_source(pwm_channel_v1);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    pwm_get_frequency(hal_pwm_channel_t pwm_channel, uint32_t *frequency)
{
    uint8_t    clock_div = 0;
    uint32_t   clock_pwm = 0;
    uint32_t   temp      = 0;
    uint8_t pwm_channel_v1 = (uint8_t)(pwm_channel - 8);
    clock_div = 1 << pwm_clk_div[pwm_channel_v1];
    clock_pwm = pwm_clk[pwm_clk_src[pwm_channel_v1]] / clock_div;
    temp      = pwm[pwm_channel_v1]->PWM_COUNT + 1;
    *frequency = clock_pwm / temp;
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    pwm_get_duty_cycle(hal_pwm_channel_t pwm_channel, uint32_t *duty_cycle)
{
    uint8_t pwm_channel_v1 = (uint8_t)(pwm_channel - 8);
    *duty_cycle = pwm[pwm_channel_v1]->PWM_THRESH;

    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    pwm_set_advanced_config(hal_pwm_channel_t pwm_channel, hal_pwm_advanced_config_t advanced_config)
{
    uint32_t save_mask;
    uint8_t pwm_channel_v1 = (uint8_t)(pwm_channel - 8);
    if ((pwm_status[pwm_channel_v1] & pwm_status_start) != pwm_status_start) {
        //log_hal_pwm_error("[hal][pwm%d] set advanced config: dev is running", 1, pwm_channel);
        return HAL_PWM_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    pwm[pwm_channel_v1]->PWM_CTRL &= ~(PWM_CLK_DIV_MASK);
    pwm[pwm_channel_v1]->PWM_CTRL |= advanced_config;
    pwm_clk_src[pwm_channel_v1] = advanced_config;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    pwm_set_polarity_v1(hal_pwm_channel_t pwm_channel, bool polarity)
{
    uint32_t save_mask;
    uint8_t pwm_channel_v1 = (uint8_t)(pwm_channel - 8);
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    if (polarity == false) {
        pwm[pwm_channel_v1]->PWM_POL = 0; //initial polarity of the PWM output is low
    } else {
        pwm[pwm_channel_v1]->PWM_POL = 1; //initial polarity of the PWM output is high
    }
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

#if defined(HAL_PWM_LED_SUPPORTED) || defined(HAL_PWM_RGB_SUPPORTED)
void    pwm_reset_default_reg(hal_pwm_channel_t pwm_channel)
{
    pwm[pwm_channel]->PWM_CTRL   = 0;
    pwm[pwm_channel]->PWM_COUNT  = 0;
    pwm[pwm_channel]->PWM_THRESH = 0;
    pwm[pwm_channel]->PWM_THRESH_DOWN = 0;
    pwm[pwm_channel]->PWM_POL = 0;
}

void    pwm_led_rgb_init(hal_pwm_channel_t pwm_channel)
{
    uint8_t pwm_channel_v1 = (uint8_t)(pwm_channel - 8);
    pwm[pwm_channel_v1]->PWM_CTRL  |= 3;  //32m clock ,div =8
    pwm[pwm_channel_v1]->PWM_COUNT = 255;
    pwm[pwm_channel_v1]->PWM_THRESH_DOWN = 1;    //duty is 0
    pwm[pwm_channel_v1]->PWM_THRESH      = 0;
}

void   pwm_led_rgb_deinit(hal_pwm_channel_t pwm_channel)
{
    uint8_t pwm_channel_v1 = (uint8_t)(pwm_channel - 8);
    pwm_reset_default_reg(pwm_channel_v1);
}

void    pwm_led_rgb_start(hal_pwm_channel_t pwm_channel)
{
    uint8_t pwm_channel_v1 = (uint8_t)(pwm_channel - 8);
    pwm_open_clock_source(pwm_channel_v1);

}

void    pwm_led_rgb_stop(hal_pwm_channel_t pwm_channel)
{
    uint8_t pwm_channel_v1 = (uint8_t)(pwm_channel - 8);
    pwm_close_clock_source(pwm_channel_v1);
}

void    pwm_led_set_duty_cycle(hal_pwm_channel_t pwm_channel, uint8_t duty_cycle)
{
    uint32_t save_mask;
    uint8_t pwm_channel_v1 = (uint8_t)(pwm_channel - 8);
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    pwm[pwm_channel_v1]->PWM_THRESH_DOWN = 0;
    if (0 == duty_cycle) {
        pwm[pwm_channel_v1]->PWM_THRESH_DOWN = 1;
        pwm[pwm_channel_v1]->PWM_THRESH      = 0;
    } else {
        pwm[pwm_channel_v1]->PWM_THRESH = duty_cycle;
    }
    hal_nvic_restore_interrupt_mask(save_mask);
}
#endif  //defined(HAL_PWM_LED_SUPPORTED) || defined(HAL_PWM_RGB_SUPPORTED)

#endif  //HAL_PWM_MODULE_ENABLED
