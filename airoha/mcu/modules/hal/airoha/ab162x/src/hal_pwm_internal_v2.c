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
#include "hal_pwm_internal_v2.h"
#include "hal_nvic.h"
#include "hal_gpt.h"
#include "hal_gpio.h"
#include "hal_clock.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_platform.h"

#ifdef HAL_PWM_DMA_MODULE_ENABLED


#define PWM_DMA_CLOCK (26000000)
static uint32_t pwm_dma_resolution[HAL_PWM_DMA_MAX_CHANNEL] = {1000, 1000};
static uint32_t pwm_dma_total_count[HAL_PWM_DMA_MAX_CHANNEL];
static uint32_t pwm_dma_duty_cycle[HAL_PWM_DMA_MAX_CHANNEL][4];
static uint8_t  pwm_dma_level_edge[HAL_PWM_DMA_MAX_CHANNEL][4];
static pwm_info_t pwm_info[HAL_PWM_DMA_MAX_CHANNEL];
const uint8_t s_pwm_nvic_irq_num[HAL_PWM_DMA_MAX_CHANNEL] = {PWM_DMA0_IRQn, PWM_DMA1_IRQn};
#define pwm_dma_status_init    (1<<0)
#define pwm_dma_status_start   (1<<1)
#define pwm_dma_status_freq    (1<<2)
#define pwm_dma_status_duty    (1<<3)
#define pwm_dma_status_config  (1<<4)
#define pwm_dma_status_bufa  (1<<4)
#define pwm_dma_status_bufb  (1<<4)
#define pwm_dma_status_unmask  (1<<5)
static volatile  PWM_DMA_REGISTER_T *const  pwm_dma_reg[2] = { (PWM_DMA_REGISTER_T *)(PWM_DMA0_BASE), (PWM_DMA_REGISTER_T *)(PWM_DMA1_BASE)};
static const  hal_clock_cg_id pwm_dma_clock[HAL_PWM_DMA_MAX_CHANNEL] = {HAL_CLOCK_CG_PWM_DMA_0, HAL_CLOCK_CG_PWM_DMA_1};
// static const sleep_management_lock_request_t g_pwm_dma_sleep_handle[HAL_PWM_DMA_MAX_CHANNEL]={SLEEP_LOCK_PWM_DMA0,SLEEP_LOCK_PWM_DMA1};


#if 0
#define log_irtx_info(fmt, cnt, ...)     log_hal_msgid_info("[hal][rtc] " fmt, cnt, ##__VA_ARGS__)
#define log_irtx_warning(fmt, cnt, ...)  log_hal_msgid_warning("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#define log_irtx_error(fmt, cnt, ...)    log_hal_msgid_error("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#else
#define log_pwm_v2_info(fmt, cnt, ...)     printk(fmt, ##__VA_ARGS__)
#define log_pwm_v2_warning(fmt, cnt, ...)  printk(fmt, ##__VA_ARGS__)
#define log_pwm_v2_error(fmt, cnt, ...)    printk(fmt, ##__VA_ARGS__)
#endif


void pwm_dma_open_clock_source(hal_pwm_dma_port_t pwm_dma_port)
{
#ifndef FPGA_ENV
    if (hal_clock_is_enabled(pwm_dma_clock[pwm_dma_port]) == false) {
        hal_clock_enable(pwm_dma_clock[pwm_dma_port]);
    }
#endif
}

void pwm_dma_close_clock_source(hal_pwm_dma_port_t pwm_dma_port)
{
#ifndef FPGA_ENV
    if (hal_clock_is_enabled(pwm_dma_clock[pwm_dma_port]) == true) {
        hal_clock_disable(pwm_dma_clock[pwm_dma_port]);
    }
#endif
}
uint8_t pwm_dma_get_channel_num(hal_pwm_dma_port_t pwm_dma_port, hal_pwm_channel_t pwm_channel)
{
    if (pwm_dma_port == 0) {
        return pwm_channel;
    } else if (pwm_dma_port == 1) {
        return (pwm_channel - 4);
    }
    return 255;
}

hal_pwm_status_t pwm_dma_set_resolution(hal_pwm_dma_port_t pwm_dma_port, uint32_t unit_us)
{
    if (unit_us != 0) {
        uint32_t prescale = (PWM_DMA_CLOCK / 1000000ul) * unit_us - 1;
        if (prescale & 0xffff0000) {
            return HAL_PWM_STATUS_INVALID_PARAMETER;
        }
        pwm_dma_reg[pwm_dma_port]->pscale_reg.field.PR = (prescale & 0xffff);
    } else {
        pwm_dma_reg[pwm_dma_port]->pscale_reg.field.PR = 0;
    }
    pwm_dma_resolution[pwm_dma_port] = unit_us;
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    pwm_dma_reset_default_reg(hal_pwm_dma_port_t pwm_dma_port)
{
    uint32_t save_mask;
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    pwm_dma_reg[pwm_dma_port]->match_reg[0].field.MR = 0;
    pwm_dma_reg[pwm_dma_port]->match_reg[1].field.MR = 0;
    pwm_dma_reg[pwm_dma_port]->match_reg[2].field.MR = 0;
    pwm_dma_reg[pwm_dma_port]->match_reg[3].field.MR = 0;
    pwm_dma_reg[pwm_dma_port]->match_reg_2[0].field.MR_2 = 0;
    pwm_dma_reg[pwm_dma_port]->match_reg_2[1].field.MR_2 = 0;
    pwm_dma_reg[pwm_dma_port]->match_reg_2[2].field.MR_2 = 0;
    pwm_dma_reg[pwm_dma_port]->match_reg_2[3].field.MR_2 = 0;
    // pwm_dma_reg[pwm_dma_port]->ext_match_ctrl_reg.word &= 0xFF000000;
    pwm_dma_reg[pwm_dma_port]->ext_match_ctrl_reg.word = 0x0;
    pwm_dma_reg[pwm_dma_port]->time_ctrl_reg.field.CEN = 0;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    pwm_set_polarity_v2(hal_pwm_channel_t pwm_channel, bool polarity)
{
    uint8_t index = (pwm_channel > 3) ? 1 : 0;
    uint8_t num = pwm_dma_get_channel_num(index, pwm_channel);
    uint32_t save_mask;
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    // pwm_dma_reg[index]->ext_match_ctrl_reg.word  &= ~(1 << (EXT_MATCH_CTRL_REG_EM0_INV_OFFSET+num));      //clear polarity
    // pwm_dma_reg[index]->ext_match_ctrl_reg.word |= (polarity << (EXT_MATCH_CTRL_REG_EM0_INV_OFFSET+num));  //set polarity
    pwm_dma_level_edge[index][num] = polarity;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

static uint8_t get_pwm_status(hal_pwm_dma_port_t pwm_dma_port)
{
    uint8_t status = 0;
    uint32_t irq_status = pwm_dma_reg[pwm_dma_port]->intr_sts.word;
    uint32_t irq_enable = pwm_dma_reg[pwm_dma_port]->intr_en.word;
    pwm_dma_reg[pwm_dma_port]->intr_sts.word = irq_status;
    status = (uint8_t)((irq_status >> INTR_STS_DMA_DONE_OFFSET) & irq_enable);
    return status;
}

int     pwm_get_port_by_nvic_id(hal_nvic_irq_t irq_num)
{
    int i = 0;
    for (i = 0; i < HAL_PWM_DMA_MAX_CHANNEL; i++) {
        if (irq_num == s_pwm_nvic_irq_num[i]) {
            return i;
        }
    }
    return -1;
}

hal_pwm_status_t   pwm_dma_port_init(hal_pwm_dma_port_t pwm_dma_port, uint8_t tick_num)
{
    pwm_dma_set_resolution(pwm_dma_port, tick_num);
    pwm_dma_open_clock_source(pwm_dma_port);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    pwm_dma_port_deinit(hal_pwm_dma_port_t pwm_dma_port)
{
    pwm_dma_close_clock_source(pwm_dma_port);
    pwm_dma_reset_default_reg(pwm_dma_port);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    pwm_dma_port_start(hal_pwm_dma_port_t pwm_dma_port)
{

    pwm_dma_reg[pwm_dma_port]->match_ctrl_reg.field.MR3R_2 = 1;  // keep frequency
    pwm_dma_reg[pwm_dma_port]->time_ctrl_reg.field.CEN = 1;
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t   pwm_dma_port_stop(hal_pwm_dma_port_t pwm_dma_port)
{
    pwm_dma_reg[pwm_dma_port]->match_ctrl_reg.field.MR3R_2 = 0;  // keep frequency
    pwm_dma_reg[pwm_dma_port]->time_ctrl_reg.field.CEN = 0;
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    pwm_dma_by_channel_frequency(hal_pwm_channel_t pwm_channel, uint32_t frequency, uint32_t *total_count)
{
    uint8_t index = (pwm_channel > 3) ? 1 : 0;
    uint8_t num = pwm_dma_get_channel_num(index, pwm_channel);
    if (frequency > (PWM_DMA_CLOCK / 2)) {
        log_pwm_v2_error("[pwm_v2] pwm set freqency failed, ch%d is over %d \r\n", 2, pwm_channel, (PWM_DMA_CLOCK / 2));
        return HAL_PWM_STATUS_INVALID_FREQUENCY;
    }
    if (frequency >= 1000000) {
        pwm_dma_set_resolution(index, 0);
        *total_count = PWM_DMA_CLOCK / frequency;
    } else {
        pwm_dma_set_resolution(index, 1);
        *total_count = 1000000 / frequency;
    }
    pwm_dma_total_count[index] = *total_count;
    pwm_dma_reg[index]->time_ctrl_reg.field.CRST = 1;   //reset count
    if (num != 3) {
        pwm_dma_reg[index]->match_reg_2[3].field.MR_2 = pwm_dma_total_count[index] - 1;    //set reset TC,match reg(MR3_2 match TC,TC is reset)
    }
    pwm_dma_reg[index]->match_reg_2[num].field.MR_2 = pwm_dma_total_count[index] - 1;        //set match register
    pwm_dma_reg[index]->time_ctrl_reg.field.CRST = 0;   //reset count
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t pwm_dma_by_channel_duty_cycle(hal_pwm_channel_t pwm_channel, uint32_t duty_cycle)
{
    uint8_t index = (pwm_channel > 3) ? 1 : 0;
    uint8_t num = pwm_dma_get_channel_num(index, pwm_channel);
    if (duty_cycle > (pwm_dma_total_count[index] - 1)) {       //set duty sycle
        pwm_dma_reg[index]->match_reg[num].field.MR = pwm_dma_total_count[index] - 1;
    } else if (duty_cycle == 0) {
        pwm_dma_reg[index]->match_reg[num].field.MR = pwm_dma_total_count[index];
    } else {
        pwm_dma_reg[index]->match_reg[num].field.MR = pwm_dma_total_count[index] - duty_cycle - 1;
    }
    pwm_dma_duty_cycle[index][num] = duty_cycle;

    pwm_dma_reg[index]->ext_match_ctrl_reg.word &= ~(0x3 << (EXT_MATCH_CTRL_REG_EMC0_OFFSET + 2 * num)); //clear EMC,EMC_2
    pwm_dma_reg[index]->ext_match_ctrl_reg.word &= ~(0x3 << (EXT_MATCH_CTRL_REG_EMC0_2_OFFSET + 2 * num));
    if (duty_cycle == 0) {            //set output level
        if (pwm_dma_level_edge[index][num] == 0) {
            pwm_dma_reg[index]->ext_match_ctrl_reg.word |= (1 << (EXT_MATCH_CTRL_REG_EMC0_OFFSET + 2 * num)); //set EMC,if default is high level light led,this is set to low
            pwm_dma_reg[index]->ext_match_ctrl_reg.word |= (1 << (EXT_MATCH_CTRL_REG_EMC0_2_OFFSET + 2 * num)); //set EMC_2,if default is high level light led,this is set to low
        } else {
            pwm_dma_reg[index]->ext_match_ctrl_reg.word |= (2 << (EXT_MATCH_CTRL_REG_EMC0_OFFSET + 2 * num)); //set EMC,if default is low level light led,this is set to high
            pwm_dma_reg[index]->ext_match_ctrl_reg.word |= (2 << (EXT_MATCH_CTRL_REG_EMC0_2_OFFSET + 2 * num)); //set EMC_2,if default is low level light led,this is set to high
        }
    } else if (duty_cycle == pwm_dma_total_count[index]) {          //set output level
        if (pwm_dma_level_edge[index][num] == 0) {
            pwm_dma_reg[index]->ext_match_ctrl_reg.word |= (2 << (EXT_MATCH_CTRL_REG_EMC0_OFFSET + 2 * num)); //set EMC,if default is low level light led,this is set to high
            pwm_dma_reg[index]->ext_match_ctrl_reg.word |= (2 << (EXT_MATCH_CTRL_REG_EMC0_2_OFFSET + 2 * num)); //set EMC_2,if default is low level light led,this is set to high
        } else {
            pwm_dma_reg[index]->ext_match_ctrl_reg.word |= (1 << (EXT_MATCH_CTRL_REG_EMC0_OFFSET + 2 * num)); //set EMC,if default is high level light led,this is set to low
            pwm_dma_reg[index]->ext_match_ctrl_reg.word |= (1 << (EXT_MATCH_CTRL_REG_EMC0_2_OFFSET + 2 * num)); //set EMC_2,if default is high level light led,this is set to low
        }
    } else {
        if (pwm_dma_level_edge[index][num] == 0) {
            pwm_dma_reg[index]->ext_match_ctrl_reg.word |= (2 << (EXT_MATCH_CTRL_REG_EMC0_OFFSET + 2 * num)); //set EMC,if default is low level light led,this is set to high
            pwm_dma_reg[index]->ext_match_ctrl_reg.word |= (1 << (EXT_MATCH_CTRL_REG_EMC0_2_OFFSET + 2 * num)); //set EMC_2,if default is low level light led,this is set to low
        } else {
            pwm_dma_reg[index]->ext_match_ctrl_reg.word |= (1 << (EXT_MATCH_CTRL_REG_EMC0_OFFSET + 2 * num)); //set EMC,if default is high level light led,this is set to low
            pwm_dma_reg[index]->ext_match_ctrl_reg.word |= (2 << (EXT_MATCH_CTRL_REG_EMC0_2_OFFSET + 2 * num)); //set EMC_2,if default is high level light led,this is set to high
        }
    }
    return HAL_PWM_STATUS_OK;
}



hal_pwm_status_t    pwm_dma_by_channel_stop(hal_pwm_channel_t pwm_channel)
{
    uint8_t index = (pwm_channel > 3) ? 1 : 0;
    uint8_t num = pwm_dma_get_channel_num(index, pwm_channel);
    pwm_dma_reg[index]->ext_match_ctrl_reg.word &= ~(0x3 << (EXT_MATCH_CTRL_REG_EMC0_OFFSET + 2 * num)); //clear EMC,EMC_2
    pwm_dma_reg[index]->ext_match_ctrl_reg.word &= ~(0x3 << (EXT_MATCH_CTRL_REG_EMC0_2_OFFSET + 2 * num));
    if (pwm_dma_level_edge[index][num] == 0) {
        pwm_dma_reg[index]->ext_match_ctrl_reg.word |= (1 << (EXT_MATCH_CTRL_REG_EMC0_OFFSET + 2 * num)); //set EMC,if default is low level light led,this is set to high
        pwm_dma_reg[index]->ext_match_ctrl_reg.word |= (1 << (EXT_MATCH_CTRL_REG_EMC0_2_OFFSET + 2 * num)); //set EMC_2,if default is low level light led,this is set to high
    } else {
        pwm_dma_reg[index]->ext_match_ctrl_reg.word |= (2 << (EXT_MATCH_CTRL_REG_EMC0_OFFSET + 2 * num)); //set EMC,if default is high level light led,this is set to low
        pwm_dma_reg[index]->ext_match_ctrl_reg.word |= (2 << (EXT_MATCH_CTRL_REG_EMC0_2_OFFSET + 2 * num)); //set EMC_2,if default is high level light led,this is set to low
    }
    return HAL_PWM_STATUS_OK;
}


hal_pwm_status_t    pwm_dma_by_channel_get_frequency(hal_pwm_channel_t pwm_channel, uint32_t *frequency)
{
    uint8_t index = (pwm_channel > 3) ? 1 : 0;
    *frequency = 1000000 / pwm_dma_total_count[index];
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    pwm_dma_by_channel_get_duty_cycle(hal_pwm_channel_t pwm_channel, uint32_t *duty_cycle)
{
    uint8_t index = (pwm_channel > 3) ? 1 : 0;
    uint8_t num = pwm_dma_get_channel_num(index, pwm_channel);
    *duty_cycle = pwm_dma_duty_cycle[index][num];
    return HAL_PWM_STATUS_OK;
}

/**********************************************************************************************************************************************************
**************************************************************** pwm_dma ******************************************************************************
**********************************************************************************************************************************************************/


hal_pwm_status_t    pwm_dma_set_frequency(hal_pwm_dma_port_t pwm_dma_port, uint32_t frequency, uint32_t *total_count)
{
    if (frequency > 1000000) {
        pwm_dma_set_resolution(pwm_dma_port, 0);   //change resolution to 1/32us
        *total_count = PWM_DMA_CLOCK / frequency;
    } else {
        pwm_dma_set_resolution(pwm_dma_port, 1);   //change resolution to 1us
        *total_count = 1000000 / frequency;
    }
    pwm_dma_total_count[pwm_dma_port] = *total_count;
    pwm_dma_reg[pwm_dma_port]->match_reg[3].field.MR = pwm_dma_total_count[pwm_dma_port] - 1; //set reset TC,match reg(MR3_2 match TC,TC is reset
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t pwm_dma_set_config(hal_pwm_dma_port_t pwm_dma_port, hal_pwm_dma_config *config)
{
    uint32_t word = ((config->dma_sign << DMA_SET_DMA_DATA_SIGN_OFFSET) | (1 << DMA_SET_DMA_MODE_OFFSET) | (config->dma_repeat_en << DMA_SET_DMA_BUF_REPEAT_EN_OFFSET) | (config->dma_8bit << DMA_SET_DMA_BUF_8B_OFFSET) | \
                     (config->dma_nonaligin << DMA_SET_DMA_BUF_NONALIGN_OFFSET) | ((config->dma_channel_number - 1) << DMA_SET_DMA_CH_NO_OFFSET) | (config->dma_data_repeat << DMA_SET_DMA_DATA_REPEAT_OFFSET) | \
                     (config->dma_gain << DMA_SET_DMA_DATA_GAIN_OFFSET) | (config->dma_scale << DMA_SET_DMA_DATA_SCALE_OFFSET));
    pwm_dma_reg[pwm_dma_port]->dma_set.word = word;
    pwm_dma_reg[pwm_dma_port]->ext_match_ctrl_reg.word &= ~(0xFF << (EXT_MATCH_CTRL_REG_EMC0_OFFSET)); //clear EMC
    pwm_dma_reg[pwm_dma_port]->ext_match_ctrl_reg.word &= ~(0xFF << (EXT_MATCH_CTRL_REG_EMC0_2_OFFSET)); //clear EMC_2
    for (int num = 0; num < (config->dma_channel_number); num++) {
        if (pwm_dma_level_edge[pwm_dma_port][num] == 0) {
            pwm_dma_reg[pwm_dma_port]->ext_match_ctrl_reg.word |= (2 << (EXT_MATCH_CTRL_REG_EMC0_OFFSET + 2 * num)); //set EMC,if default is low level light led,this is set to high
            pwm_dma_reg[pwm_dma_port]->ext_match_ctrl_reg.word |= (1 << (EXT_MATCH_CTRL_REG_EMC0_2_OFFSET + 2 * num)); //set EMC_2,if default is low level light led,this is set to low
        } else {
            pwm_dma_reg[pwm_dma_port]->ext_match_ctrl_reg.word |= (1 << (EXT_MATCH_CTRL_REG_EMC0_OFFSET + 2 * num)); //set EMC,if default is high level light led,this is set to low
            pwm_dma_reg[pwm_dma_port]->ext_match_ctrl_reg.word |= (2 << (EXT_MATCH_CTRL_REG_EMC0_2_OFFSET + 2 * num)); //set EMC_2,if default is high level light led,this is set to high
        }
    }
    return HAL_PWM_STATUS_OK;
}



static int    pwm_wait_idle_with_timeout(hal_pwm_dma_port_t pwm_dma_port, uint32_t timeout_us)
{
#define     PWM_WAIT_IDLE_TIME_UNIT     100 //0.1ms

    uint32_t  tick_pre = 0, tick_cur = 0, tick_dur = 0, count = 0, max_ms = 0;
    uint32_t  save_mask;
    int       result = 0;
    volatile uint32_t *ptemp = NULL;

    max_ms = timeout_us / PWM_WAIT_IDLE_TIME_UNIT;
    ptemp = &(pwm_dma_reg[pwm_dma_port]->dma_sts.word);

    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &tick_pre);
    while (1) {
        hal_nvic_save_and_set_interrupt_mask(&save_mask);
        if (((*ptemp) & 0x1) == 0) {
            result = 0;
            break;
        }
        hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &tick_cur);
        hal_gpt_get_duration_count(tick_pre, tick_cur, &tick_dur);
        if (tick_dur > PWM_WAIT_IDLE_TIME_UNIT) {
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

static void  pwm_dma_isr(hal_nvic_irq_t irq_number)
{

    hal_pwm_dma_port_t pwm_port = pwm_get_port_by_nvic_id(irq_number);
    if (pwm_port >= HAL_PWM_DMA_MAX_CHANNEL) {
        //log_hal_pwm_error("[pwm_v2][pwm%d] irq handle err: port invalid", 1, pwm_port);
        return;
    }
    uint8_t status = get_pwm_status(pwm_port);
    if (pwm_info[pwm_port].call_back) {
        pwm_info[pwm_port].call_back(status, pwm_info[pwm_port].user_data);
    }
}

hal_pwm_status_t pwm_dma_register_callback(hal_pwm_dma_port_t pwm_dma_port, hal_pwm_irq_enable *irq_enable, hal_pwm_callback_t pwm_callback, void *user_data)
{
    pwm_dma_reg[pwm_dma_port]->intr_en.field.DMA_DONE_INT_EN = irq_enable->done_irq;
    pwm_dma_reg[pwm_dma_port]->intr_en.field.DMA_BUFA_DONE_INT_EN = irq_enable->bufa_done_irq;
    pwm_dma_reg[pwm_dma_port]->intr_en.field.DMA_BUFB_DONE_INT_EN = irq_enable->bufb_done_irq;
    pwm_dma_reg[pwm_dma_port]->intr_en.field.DMA_BUFA_OV_INT_EN = 1;
    pwm_dma_reg[pwm_dma_port]->intr_en.field.DMA_BUFB_OV_INT_EN = 1;
    pwm_info[pwm_dma_port].call_back = pwm_callback;
    pwm_info[pwm_dma_port].user_data = user_data;
    hal_nvic_register_isr_handler(s_pwm_nvic_irq_num[pwm_dma_port], pwm_dma_isr);
    hal_nvic_enable_irq(s_pwm_nvic_irq_num[pwm_dma_port]);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t pwm_dma_enqueue_BufA(hal_pwm_dma_port_t pwm_dma_port, uint32_t *bufaddr, uint16_t sample_cnt)
{

    if ((uint32_t)bufaddr & 0x0003) { // the address must be 4-byte aligned
        // log_pwm_v2_error("[pwm_v2] pwm dma set BUFA error, index%d buffer not 4-byte align \r\n", 1, pwm_dma_port);
        return HAL_PWM_STATUS_ERROR;
    }
    pwm_dma_reg[pwm_dma_port]->dma_base_addr_a.field.DMA_BADDR_A = (uint32_t)bufaddr;
    pwm_dma_reg[pwm_dma_port]->dma_length_a.field.DMA_LEN_A = sample_cnt;
    pwm_dma_reg[pwm_dma_port]->dma_ctrl.field.DMA_START_P = 1;
    return HAL_PWM_STATUS_OK;

}

hal_pwm_status_t pwm_dma_enqueue_BufB(hal_pwm_dma_port_t pwm_dma_port, uint32_t *bufaddr, uint16_t sample_cnt)
{
    if ((uint32_t)bufaddr & 0x0003) { // the address must be 4-byte aligned
        // log_pwm_v2_error("[pwm_v2] pwm dma set BUFB error, index%d buffer not 4-byte align \r\n", 1, pwm_dma_port);
        return HAL_PWM_STATUS_ERROR;
    }
    pwm_dma_reg[pwm_dma_port]->dma_base_addr_b.field.DMA_BADDR_B = (uint32_t)bufaddr;
    pwm_dma_reg[pwm_dma_port]->dma_length_b.field.DMA_LEN_B = sample_cnt;
    pwm_dma_reg[pwm_dma_port]->dma_ctrl.field.DMA_START_P = 1;
    return HAL_PWM_STATUS_OK;

}
hal_pwm_status_t pwm_dma_start(hal_pwm_dma_port_t pwm_dma_port)
{
    pwm_dma_reg[pwm_dma_port]->match_ctrl_reg.field.MR3R = 1;  // keep frequency
    pwm_dma_reg[pwm_dma_port]->dma_ctrl.field.DMA_START_P = 1;
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t pwm_dma_stop(hal_pwm_dma_port_t pwm_dma_port)
{
    uint32_t save_mask;
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    pwm_dma_reg[pwm_dma_port]->dma_ctrl.field.DMA_ABORT_P = 1;
    hal_nvic_restore_interrupt_mask(save_mask);
    if (pwm_wait_idle_with_timeout(pwm_dma_port, 1000) == 0) {
        hal_nvic_save_and_set_interrupt_mask(&save_mask);
        pwm_dma_reg[pwm_dma_port]->match_ctrl_reg.field.MR3R = 0;  // keep frequency
        // pwm_dma_reg[pwm_dma_port]->time_ctrl_reg.field.CEN = 0;
        pwm_dma_reg[pwm_dma_port]->dma_ctrl.field.DMA_START_P = 0;
        hal_nvic_restore_interrupt_mask(save_mask);
    } else {
        return HAL_PWM_STATUS_ERROR;
    }
    return HAL_PWM_STATUS_OK;
}


#if defined(HAL_PWM_LED_SUPPORTED) || defined(HAL_PWM_RGB_SUPPORTED)
static pwm_dma_port_info_t pwm_dma_port_info[HAL_PWM_DMA_MAX_CHANNEL] = {0};
static uint16_t duty_covert_count(uint8_t channel, uint8_t duty, uint16_t total_count, uint8_t *val_emc, uint8_t *val_emc2)
{
    uint16_t ret_count;
    uint8_t index = (channel > 3) ? 1 : 0;
    uint8_t num = pwm_dma_get_channel_num(index, channel);
    if (duty == 0) {
        *val_emc = pwm_dma_level_edge[index][num] == 0 ? 2 : 1;
        *val_emc2 = *val_emc;
        return 1;
    } else if (duty == 255) {
        *val_emc = pwm_dma_level_edge[index][num] == 0 ? 1 : 2;
        *val_emc2 = *val_emc;
        return 1;
    } else {
        ret_count = duty * (total_count / 255);
        *val_emc = (pwm_dma_level_edge[index][num] == 0) ? 1 : 2;
        *val_emc2 = *val_emc == 1 ? 2 : 1;
        return total_count - ret_count;
    }
}
void pwm_dma_led_rgb_set_duty_cycle(uint8_t channel, uint8_t duty, uint16_t total_count) // calculation zero duty cycle duty count in breathing mode
{
    uint8_t index = (channel > 3) ? 1 : 0;
    uint8_t num = pwm_dma_get_channel_num(index, channel);
    uint8_t set_val_emc = 0;
    uint8_t set_val_emc2 = 0;
    uint16_t mr_count =  duty_covert_count(channel, duty, total_count, &set_val_emc, &set_val_emc2);
    pwm_dma_reg[index]->match_reg[num].field.MR = mr_count;
    pwm_dma_reg[index]->ext_match_ctrl_reg.word &= ~((0x3 << (EXT_MATCH_CTRL_REG_EMC0_OFFSET + 2 * num)) | (0x3 << (EXT_MATCH_CTRL_REG_EMC0_2_OFFSET + 2 * num)));
    pwm_dma_reg[index]->ext_match_ctrl_reg.word |= ((set_val_emc << (EXT_MATCH_CTRL_REG_EMC0_OFFSET + 2 * num)) | (set_val_emc2 << (EXT_MATCH_CTRL_REG_EMC0_2_OFFSET + 2 * num)));
}

static void pwm_led_rgb_set_frequency_num(hal_pwm_dma_port_t pwm_dma_port, uint8_t calc_num, bool irq)
{

    if (calc_num == 0) {
        pwm_dma_reg[pwm_dma_port]->match_ctrl_reg.field.MR0I_2 = irq;
        pwm_dma_reg[pwm_dma_port]->wake_up_mask.field.MR0_2_WAKEUP = irq;
    } else if (calc_num == 1) {
        pwm_dma_reg[pwm_dma_port]->match_ctrl_reg.field.MR1I_2 = irq;
        pwm_dma_reg[pwm_dma_port]->wake_up_mask.field.MR1_2_WAKEUP = irq;
    } else if (calc_num == 2) {
        pwm_dma_reg[pwm_dma_port]->match_ctrl_reg.field.MR2I_2 = irq;
        pwm_dma_reg[pwm_dma_port]->wake_up_mask.field.MR2_2_WAKEUP = irq;
    } else if (calc_num == 3) {
        pwm_dma_reg[pwm_dma_port]->match_ctrl_reg.field.MR3I_2 = irq;
        pwm_dma_reg[pwm_dma_port]->wake_up_mask.field.MR3_2_WAKEUP = irq;
    }

}

void pwm_dma_led_rgb_port_start(hal_pwm_dma_port_t pwm_dma_port, uint16_t total_count, uint8_t calc_num)
{
    pwm_dma_reg[pwm_dma_port]->match_reg_2[calc_num].field.MR_2 = total_count;
    pwm_led_rgb_set_frequency_num(pwm_dma_port, calc_num, 1);
    // hal_sleep_manager_lock_sleep(g_pwm_dma_sleep_handle[pwm_dma_port]);
    pwm_dma_reg[pwm_dma_port]->time_ctrl_reg.field.CEN = 1;
}

void pwm_dma_led_rgb_port_stop(hal_pwm_dma_port_t pwm_dma_port, uint16_t total_count, uint8_t calc_num)
{
    // hal_sleep_manager_unlock_sleep(g_pwm_dma_sleep_handle[pwm_dma_port]);
    pwm_dma_reg[pwm_dma_port]->time_ctrl_reg.field.CRST = 1;
    pwm_dma_led_rgb_set_duty_cycle(pwm_dma_port * 4 + 0, 0, total_count);  //convert duty to R
    pwm_dma_led_rgb_set_duty_cycle(pwm_dma_port * 4 + 1, 0, total_count);  //convert duty to G
    pwm_dma_led_rgb_set_duty_cycle(pwm_dma_port * 4 + 2, 0, total_count);  //convert duty to B
    pwm_dma_led_rgb_set_duty_cycle(pwm_dma_port * 4 + 3, 0, total_count);  //convert duty to B
    pwm_dma_reg[pwm_dma_port]->time_ctrl_reg.field.CRST = 0;
    pwm_led_rgb_set_frequency_num(pwm_dma_port, calc_num, 0);
}

static void  pwm_port_isr(hal_nvic_irq_t irq_number)
{

    hal_pwm_dma_port_t pwm_port = pwm_get_port_by_nvic_id(irq_number);
    if (pwm_port >= HAL_PWM_DMA_MAX_CHANNEL) {
        return;
    }
    get_pwm_status(pwm_port);
    pwm_dma_reg[pwm_port]->time_ctrl_reg.field.CRST = 1;
    if (pwm_dma_port_info[pwm_port].call_back) {
        pwm_dma_port_info[pwm_port].call_back(pwm_dma_port_info[pwm_port].user_data);
    }
    pwm_dma_reg[pwm_port]->time_ctrl_reg.field.CRST = 0;
}

void pwm_dma_port_register_callback(hal_pwm_dma_port_t pwm_dma_port, hal_pwm_dma_port_callback_t pwm_callback, void *user_data)
{
    pwm_dma_port_info[pwm_dma_port].call_back = pwm_callback;
    pwm_dma_port_info[pwm_dma_port].user_data = user_data;
    hal_nvic_register_isr_handler(s_pwm_nvic_irq_num[pwm_dma_port], pwm_port_isr);
    hal_nvic_enable_irq(s_pwm_nvic_irq_num[pwm_dma_port]);
}

#endif  //defined(HAL_PWM_LED_SUPPORTED) || defined(HAL_PWM_RGB_SUPPORTED)

#endif //HAL_PWM_DMA_MODULE_ENABLED