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
#include "hal_platform.h"
#if defined(HAL_LED_MODULE_ENABLED)

#ifdef HAL_SLEEP_MANAGER_ENABLED
#include "hal_spm.h"
#endif

hal_led_callback_context_t led_context[HAL_LED_MAX_CHANNEL];
static LED_CONTROL_REGISTER_T *led_base = (LED_CONTROL_REGISTER_T *)(LED_BASE);
#define LED_IRQ_NUM 48
int    led_wait_idle_with_timeout(hal_led_channel_t channel, hal_led_busy_status_t status,uint32_t timeout_us);
static int led_set_timeunit(uint8_t led, int tm_unit_ms)
{
    uint32_t  save_mask;
    int xn = 0, unit = 0, i = 0;
    int temp;

    for (xn = 1; xn < 9; xn = xn * 2) {
        unit = (tm_unit_ms * 32) / xn;
        if (unit <= 255) {
            break;
        }
        i++;
    }
    if (xn <= 8) {
        temp = (i << 8) | unit;
        hal_nvic_save_and_set_interrupt_mask(&save_mask);
        led_base->led_struct[led].led_unit.word = temp;
        hal_nvic_restore_interrupt_mask(save_mask);
        temp = ((xn * unit) / 32);
        return temp;
    } else {
        return 0;
    }
}

static bool    led_set_timing(uint8_t led, uint32_t t0, uint32_t t1, uint32_t t2, uint32_t t3, uint32_t time_unit)
{
    uint8_t     tmp0, tmp1;
    uint32_t  save_mask;
    tmp0 = t0 / time_unit;
    tmp1 = t1 / time_unit;

    if (t0 != 0) {
        tmp0 = (tmp0 == 0) ? 1 : tmp0;
    }
    if (t1 != 0) {
        tmp1 = (tmp1 == 0) ? 1 : tmp1;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    led_base->led_struct[led].led_period0.field.LED_T0 = tmp0;
    led_base->led_struct[led].led_period0.field.LED_T1 = tmp1;
    tmp0 = t2 / time_unit;
    tmp1 = t3 / time_unit;
    led_base->led_struct[led].led_period0.field.LED_T2 = tmp0;
    led_base->led_struct[led].led_period0.field.LED_T3 = tmp1;
    hal_nvic_restore_interrupt_mask(save_mask);
    return true;
}

static void led_set_t1t2_repeat(uint8_t led, uint32_t blink_num)
{
    blink_num = (blink_num > 16) ? 0 : blink_num;
    uint32_t  save_mask;
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    led_base->led_struct[led].led_con0.field.LED_T1T2_REPEAT = (blink_num & 0xF);
    hal_nvic_restore_interrupt_mask(save_mask);
}
static void led_set_repeat(uint8_t led, uint8_t repeat){
    uint32_t  save_mask;
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    if(repeat > 0){
        led_base->led_struct[led].led_con0.field.LED_REPEAT = 1;
    }else{
        led_base->led_struct[led].led_con0.field.LED_REPEAT = 0;
    }
    hal_nvic_restore_interrupt_mask(save_mask);
}

hal_led_status_t  hal_led_init(hal_led_channel_t  channel)
{   
#ifdef HAL_SLEEP_MANAGER_ENABLED
    spm_control_mtcmos(SPM_MTCMOS_RTCSYS, SPM_MTCMOS_PWR_ENABLE);
#endif
    return HAL_LED_STATUS_OK;
}

hal_led_status_t  hal_led_deinit(hal_led_channel_t channel)
{
#ifdef HAL_SLEEP_MANAGER_ENABLED
    spm_control_mtcmos(SPM_MTCMOS_RTCSYS, SPM_MTCMOS_PWR_DISABLE);
#endif
    return HAL_LED_STATUS_OK;
}

hal_led_status_t  hal_led_set_invert(hal_led_channel_t channel,bool invert)
{
    uint32_t     save_mask;
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    led_base->led_struct[channel].led_con0.field.LED_INVERT = invert;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_LED_STATUS_OK;
}

static hal_led_status_t  led_find_period_step(uint8_t tr,uint8_t tf,uint8_t *period,uint8_t *onstep,uint8_t *offstep){
    uint8_t current_onstep,current_offstep,current_period;
    uint16_t temp_period;
    uint32_t temp,temp_tr,temp_tf;
    temp_tr = 32*tr;
    temp_tf = 32*tf;
    uint16_t diff_min=0xffff;
    for(temp_period =16;temp_period<=255;temp_period++){
        temp = (temp_period+1)*(temp_period);
        int temp_onstep = -1,temp_offstep = -1;
        uint16_t diff_onstep,diff_offstep,current_diff;
        if(temp_tr == 0){
            temp_onstep = 0;
        }else if(temp_tr/temp <= 255){
            temp_onstep = temp_tr/temp;
        }
        if(temp_tf == 0 ){
            temp_offstep = 0;
        }else if(temp_tf/temp <= 255){
            temp_offstep = temp_tf/temp;
        }
        if(temp_onstep >=0 && temp_offstep >= 0){
            diff_onstep = (temp_onstep * temp > temp_tr)?(temp_onstep * temp -temp_tr) : (temp_tr - temp_onstep * temp);
            diff_offstep = (temp_offstep * temp > temp_tf)?(temp_offstep * temp -temp_tf) : (temp_tf - temp_offstep * temp);
            current_diff = diff_onstep+diff_offstep;
        }
        if(current_diff < diff_min){
            diff_min = current_diff;
            current_onstep = (uint8_t)temp_onstep;
            current_offstep = (uint8_t)temp_offstep;
            current_period = (uint8_t)temp_period;
        }
    }
    if(diff_min != 0xffff){
        *onstep = current_onstep;
        *offstep = current_offstep;
        *period= current_period;
        return HAL_LED_STATUS_OK;
    }else{
        return HAL_LED_STATUS_ERROR_INVALID_PARAMETER;
    }
}

static  void    led_set_style(uint8_t led, hal_led_config_ext_t *config)
{
    // uint32_t     pwm_cyc_tm;
    uint32_t     save_mask;
    uint8_t     pwm_period = 0;
    uint32_t     pwm_duration;
    uint8_t     pwm_step_on = 0, pwm_step_off = 0;
    uint32_t     tr = 0, tf = 0;

    tr = config->timing.t1.t_rising;
    tf = config->timing.t2.t_falling;

    led_find_period_step(tr,tf,&pwm_period,&pwm_step_on,&pwm_step_off);
    pwm_duration = ((pwm_period) * (config->brightness)) / 255;
    if(config->brightness != 0 && pwm_duration == 0){
        pwm_duration = 1;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    led_base->led_struct[led].led_pwm1.word =  ((pwm_duration << 8) | pwm_period);
    led_base->led_struct[led].led_pwm2.word =  ((pwm_step_off << 8) | pwm_step_on);
    led_base->led_struct[led].led_pwm0.word = 1;
    hal_nvic_restore_interrupt_mask(save_mask);
}

hal_led_status_t  hal_led_configure_flex_ext(hal_led_channel_t channel,hal_led_config_flex_ext_t *cfg){

    uint32_t t_hi, t_lo, t_max, t_unit;
    if (channel >= HAL_LED_MAX_CHANNEL || cfg == NULL) {
        log_hal_msgid_info("[hal][led] config fail, invalid param", 0);
        return HAL_LED_STATUS_ERROR_INVALID_PARAMETER;
    }
    t_hi = cfg->config_ext.timing.t1.t_rising  + cfg->config_ext.timing.t1.t_lightest;
    t_lo = cfg->config_ext.timing.t2.t_falling + cfg->config_ext.timing.t2.t_darkest;
    t_max = (t_hi > t_lo) ? t_hi : t_lo;
    if (t_hi == 0) {
        t_max = t_lo;
    } else if (t_lo == 0) {
        t_max = t_hi;
    }
    if (t_max < 255) {
        t_unit = 1;//1ms
    } else {
        t_unit = 50;//50ms
    }
    if (led_wait_idle_with_timeout(channel,HAL_LED_NORMAL_BUSY,150) != 0) {
        log_hal_msgid_info("[hal][led] led busy, waiting for idle", 0);
        return HAL_LED_STATUS_ERROR_BUSY;
    }
    if (led_wait_idle_with_timeout(channel,HAL_LED_IRQ_BUSY,150) != 0) {
        log_hal_msgid_info("[hal][led] led busy, waiting for idle", 0);
        return HAL_LED_STATUS_ERROR_CHANNEL;
    }
    led_set_timeunit(channel, t_unit);
    led_set_t1t2_repeat(channel, cfg->config_ext.blink_nums);
    led_set_timing(channel, cfg->config_ext.timing.t0, t_hi, t_lo, cfg->config_ext.timing.t3, t_unit);
    led_set_style(channel, &cfg->config_ext);
    led_set_repeat(channel,cfg->other_config.repeat_times);
    return HAL_LED_STATUS_OK;
}

hal_led_status_t  hal_led_configure_for_irpt(hal_led_channel_t channel, uint32_t light_time_us, uint32_t dark_time_us){
    uint32_t  save_mask;
    uint8_t t1 = (uint8_t)(light_time_us/ 30);
    if(t1 > 255 || t1 == 0){
        return HAL_LED_STATUS_ERROR_INVALID_PARAMETER;
    }
    uint8_t t2,t3;
    uint32_t t_hi = (dark_time_us / light_time_us);
    if(t_hi > 510){
        return HAL_LED_STATUS_ERROR_INVALID_PARAMETER;
    }else if(t_hi < 255){
        t2 = t_hi;
        t3 = 0;
    }else{
        t2 = 255;
        t3 = t_hi - 255;
    }       
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    led_base->led_struct[channel].led_unit.word = 1;
    led_base->led_struct[channel].led_period0.field.LED_T0 = 0;
    led_base->led_struct[channel].led_period0.field.LED_T1 = t1;
    led_base->led_struct[channel].led_period0.field.LED_T2 = t2;
    led_base->led_struct[channel].led_period0.field.LED_T3 = t3;
    led_base->led_struct[channel].led_con0.field.LED_REPEAT = 1;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_LED_STATUS_OK;
}

hal_led_status_t  hal_led_configure_ext(hal_led_channel_t channel, hal_led_config_ext_t *cfg)
{
    hal_led_config_flex_ext_t flex_cfg;
    memcpy(&(flex_cfg.config_ext),cfg,sizeof(hal_led_config_ext_t));
    flex_cfg.other_config.end_brightness = 0;
    flex_cfg.other_config.start_brightness = 0;
    flex_cfg.other_config.repeat_times = 1;
    return hal_led_configure_flex_ext(channel,&flex_cfg);
}



hal_led_status_t hal_led_follow_setting(hal_follow_setting_t *set)
{
    uint32_t  save_mask;
    uint8_t follow_led = (set->type & 0x3);
    uint8_t output_time = ((set->type >> 2) & 0x1);
    uint8_t output_led = ((set->type >> 3) & 0x3);
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    if(set->enable == 0){
        led_base->led_struct[follow_led].led_con0.field.LED_FW_EN  = 0;
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_LED_STATUS_OK;
    }else{
        led_base->led_struct[follow_led].led_con0.field.LED_FW_EN  = 1;
        led_base->led_struct[follow_led].led_con0.field.LED_FW_SEL  = output_led;
        led_base->led_struct[output_led].led_con0.field.LED_FW_T1T2 =  output_time;
        led_base->led_struct[follow_led].led_con0.field.LED_FW_RETRIG =  set->hard_force_follow;
    }
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_LED_STATUS_OK;
}

hal_led_status_t hal_led_start(hal_led_channel_t channel)
{
    uint32_t  save_mask;
    uint32_t    control_data = 0;
    uint8_t busy_bit = 0;
    if (channel >= HAL_LED_MAX_CHANNEL) {
        log_hal_msgid_info("[hal][led] start fail, invalid param", 0);
        return HAL_LED_STATUS_ERROR_INVALID_PARAMETER;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    control_data = led_base->led_en_ctrl.word;
    busy_bit = ((control_data >> 24) & 0xf) & (1 << channel);
    if(busy_bit){
        hal_nvic_restore_interrupt_mask(save_mask);
        log_hal_msgid_info("[hal][led] start fail, led busy", 0);
        return HAL_LED_STATUS_ERROR_BUSY;
    }
    led_base->led_en_ctrl.word |= (1 << channel);
    hal_gpt_delay_us(50);
    // led_base->led_gbl_ctrl.field.LED_LP_EN = 1;    //control auto clock
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_LED_STATUS_OK;
}

hal_led_status_t hal_led_stop(hal_led_channel_t channel)
{
    uint32_t  save_mask;
    uint32_t  control_data = 0;
    uint8_t busy_bit = 0;
    if (channel >= HAL_LED_MAX_CHANNEL) {
        log_hal_msgid_info("[hal][led] stop fail, invalid param", 0);
        return HAL_LED_STATUS_ERROR_INVALID_PARAMETER;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    control_data = led_base->led_en_ctrl.word;
    busy_bit = (control_data >> 24 & 0xf) & (1 << channel);
    if(!busy_bit){
        hal_nvic_restore_interrupt_mask(save_mask);
        log_hal_msgid_info("[hal][led] stop fail, led not start", 0);
        return HAL_LED_STATUS_ERROR;
    }
    led_base->led_en_ctrl.word &= ~(1 << channel);
    led_base->led_intr_clr.word = (1<<channel);
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_LED_STATUS_OK;
}

int    led_wait_idle_with_timeout(hal_led_channel_t channel, hal_led_busy_status_t status,uint32_t timeout_us)
{
#define     LED_WAIT_IDLE_TIME_UNIT     10 //0.1ms

    uint32_t  tick_pre = 0, tick_cur = 0, tick_dur = 0, count = 0, max_ms = 0;
    uint32_t  save_mask;
    int       result = 0;
    volatile uint32_t *ptemp = NULL;
    uint32_t  temp_check = 0;
    max_ms = timeout_us / LED_WAIT_IDLE_TIME_UNIT;
    if(status == HAL_LED_IRQ_BUSY){
        ptemp = &(led_base->led_intr_clr.word);
        temp_check = (0x1 << channel);
    }else{
        ptemp = &(led_base->led_en_ctrl.word);
        temp_check = (0x1 << (channel+LED_EN_CTRL_LED0_EN_SYS_SW_OFFSET));
    }
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &tick_pre);
    while (1) {
        hal_nvic_save_and_set_interrupt_mask(&save_mask);
        if (((*ptemp) & (temp_check) ) == 0) {
            result = 0;
            break;
        }
        hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &tick_cur);
        hal_gpt_get_duration_count(tick_pre, tick_cur, &tick_dur);
        if (tick_dur > LED_WAIT_IDLE_TIME_UNIT) {
            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &tick_pre);
            count++;
        }
        if (count > max_ms) {
            result = -1;
            break;
        }
        hal_nvic_restore_interrupt_mask(save_mask);
    }
    hal_nvic_restore_interrupt_mask(save_mask);
    return result;
}

void led_interrupt_handler(hal_nvic_irq_t irq_number){
    uint8_t i =0;
    for (i = 0; i < HAL_LED_MAX_CHANNEL; i++) {
        if(led_base->led_intr_sts.word & (1<<i)){
            led_base->led_intr_clr.word = (1<<i);
            if(led_wait_idle_with_timeout(i,HAL_LED_IRQ_BUSY,150) != 0){
                log_hal_msgid_info("[hal][led] wait idle error", 0);
            }
            if (led_context[i].callback!= NULL){
                led_context[i].callback(led_context[i].user_data);
            }
        }
    }
}

hal_led_status_t hal_led_register_callback(hal_led_channel_t channel, hal_led_callback_t callback, void *user_data)
{
    uint32_t  save_mask;
    static bool led_irq_init = false;
    if (led_irq_init == false) {
        hal_nvic_disable_irq(LED_IRQ_NUM);
        hal_nvic_register_isr_handler(LED_IRQ_NUM, led_interrupt_handler);
        hal_nvic_enable_irq(LED_IRQ_NUM);
        led_irq_init = true;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    led_context[channel].callback  = callback;
    led_context[channel].user_data = user_data;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_LED_STATUS_OK;
}


hal_led_status_t hal_led_mask(hal_led_channel_t channel){
    uint32_t  save_mask;
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    led_base->led_intr_msk.word &= ~(1 << channel);     //mask irq
    led_base->led_intr_en.word &= ~(1 << channel);     //enable irq
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_LED_STATUS_OK;
}

hal_led_status_t hal_led_unmask(hal_led_channel_t channel){
    uint32_t  save_mask;
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    led_base->led_intr_en.word |= (1 << channel);     //enable irq
    led_base->led_intr_msk.word |= (1 << channel);     //mask irq
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_LED_STATUS_OK;
}

// static bool    led_set_mode(uint8_t led, uint32_t t1, uint32_t t2, bool is_blink)
// {
//     uint32_t    min;
//     uint32_t    pwm_cyc_tm;
//     uint32_t    pwm_period;
//     uint32_t    pwm_duration;
//     uint32_t    pwm_step;

//     min = (t1 > t2) ? t2 : t1;
//     if (min <= 500) {
//         pwm_cyc_tm   = 1;//1ms
//         pwm_period   = 31;
//     } else if (min <= 2000) {
//         pwm_cyc_tm   = 5;//5ms
//         pwm_period   = 159;
//     } else {
//         pwm_cyc_tm   = 8;//8ms
//         pwm_period   = 255;
//     }

//     min = (min >> 1);
//     if (min != 0) {
//         pwm_step = (pwm_period + 1) / (min / pwm_cyc_tm);
//         pwm_step = (pwm_step == 0) ? 1 : pwm_step;
//     } else {
//         pwm_step = 0;
//     }
//     if (is_blink) {
//         pwm_period   = 31;
//         pwm_step     = 0;
//     }
//     pwm_duration = (pwm_period + 1) / 2;

//     led_base->led_struct[led].led_pwm1.field.LED_PWM_PERIOD =pwm_period;
//     led_base->led_struct[led].led_pwm1.field.LED_PWM_DURATION =pwm_duration;
//     led_base->led_struct[led].led_pwm2.field.LED_PWM_ONSTEP =pwm_step;
//     led_base->led_struct[led].led_pwm2.field.LED_PWM_OFFSTEP =pwm_step;
//     if(pwm_step != 0){
//         led_base->led_struct[led].led_pwm0.field.LED_PWM_LOAD_EN = 1;
//     }
//     return true;
// }

// hal_led_status_t hal_led_configure(hal_led_channel_t channel, hal_led_config_t *cfg)
// {
//     uint32_t t_hi, t_lo, t_min, t_unit;

//     if (channel >= HAL_LED_MAX_CHANNEL || cfg == NULL) {
//         log_hal_msgid_info("[hal][led] config fail, invalid param", 0);
//         return HAL_LED_STATUS_ERROR_INVALID_PARAMETER;
//     }
//     t_hi = cfg->config.pwm_mode.hi_level_time;
//     t_lo = cfg->config.pwm_mode.lo_level_time;
//     t_min = (t_hi > t_lo) ? t_lo : t_hi;
//     if (t_min < 50) {
//         t_unit = 1;//1ms
//     } else {
//         t_unit = 50;//50ms
//     }
//     led_set_timeunit(channel, t_unit);
//     switch (cfg->mode) {
//         case HAL_LED_MODE_BREATH: {
//             log_hal_msgid_info("[hal][led] config for breath mode, t1(%d),t2(%d),blink_num(%d)", 3,
//                                cfg->config.pwm_mode.hi_level_time,
//                                cfg->config.pwm_mode.lo_level_time,
//                                cfg->config.pwm_mode.blink_nums
//                               );
//             led_set_t1t2_repeat(channel, cfg->config.pwm_mode.blink_nums);
//             led_set_timing(channel, 0, cfg->config.pwm_mode.hi_level_time, cfg->config.pwm_mode.lo_level_time, 0, t_unit);
//             led_set_mode(channel, cfg->config.pwm_mode.hi_level_time, cfg->config.pwm_mode.lo_level_time, false);
//         }
//         break;
//         case HAL_LED_MODE_PWM: {
//             log_hal_msgid_info("[hal][led] config for blink mode, t1(%d),t2(%d),blink_num(%d)", 3,
//                                cfg->config.pwm_mode.hi_level_time,
//                                cfg->config.pwm_mode.lo_level_time,
//                                cfg->config.pwm_mode.blink_nums
//                               );
//             led_set_t1t2_repeat(channel, cfg->config.pwm_mode.blink_nums);
//             led_set_timing(channel, 0, cfg->config.pwm_mode.hi_level_time, cfg->config.pwm_mode.lo_level_time, 0, t_unit);
//             led_set_mode(channel, cfg->config.pwm_mode.hi_level_time, cfg->config.pwm_mode.lo_level_time, true);
//         }
//         break;
//         default: {
//             return HAL_LED_STATUS_ERROR_INVALID_PARAMETER;
//         }
//     }
//     return HAL_LED_STATUS_OK;
// }
#endif