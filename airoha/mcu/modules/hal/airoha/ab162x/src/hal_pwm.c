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
#include "hal_platform.h"

#include "hal_gpio.h"
#include "hal_pwm.h"
#include "hal_nvic.h"
#include "hal_pwm_internal.h"
#include "hal_pwm_internal_v1.h"
#include "hal_pwm_internal_v2.h"
#define HAL_PWM_PORT_MAX_CHANNEL  (3)

#ifdef HAL_PWM_MODULE_ENABLED

#define pwm_status_init    (1<<0)
#define pwm_status_start   (1<<1)
#define pwm_status_freq    (1<<2)
#define pwm_status_duty    (1<<3)
#define pwm_status_config  (1<<4)
#define pwm_status_bufa    (1<<4)
#define pwm_status_bufb    (1<<4)
#define pwm_status_unmask  (1<<5)


#define pwm_used_none   (0)
#define pwm_used_pwm    (1)
#define pwm_used_dma   (2)
#define pwm_used_led   (3)
#define pwm_used_rgb    (4)

static uint8_t    pwm_used_status[HAL_PWM_PORT_MAX_CHANNEL];
static uint8_t    pwm_status[HAL_PWM_PORT_MAX_CHANNEL];
static uint8_t    pwm_by_channel_status[HAL_PWM_PORT_MAX_CHANNEL][4];


#if 0
#define log_irtx_info(fmt, cnt, ...)     log_hal_msgid_info("[hal][rtc] " fmt, cnt, ##__VA_ARGS__)
#define log_irtx_warning(fmt, cnt, ...)  log_hal_msgid_warning("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#define log_irtx_error(fmt, cnt, ...)    log_hal_msgid_error("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#else
#define log_pwm_info(fmt, cnt, ...)     printk(fmt, ##__VA_ARGS__)
#define log_pwm_warning(fmt, cnt, ...)  printk(fmt, ##__VA_ARGS__)
#define log_pwm_error(fmt, cnt, ...)    printk(fmt, ##__VA_ARGS__)
#endif

void pwm_get_index(uint8_t channel, uint8_t *index, uint8_t *num)
{
    if (channel <= 3) {
        *index = 0;
        *num = channel;
    } else if (channel <= 7) {
        *index = 1;
        *num = channel - 4;
    } else if (channel <= 10) {
        *index = 2;
        *num = channel - 8;
    }
}
hal_pwm_status_t    hal_pwm_set_advanced_config(hal_pwm_channel_t pwm_channel, hal_pwm_advanced_config_t advanced_config)
{
    hal_pwm_status_t status = HAL_PWM_STATUS_OK;
    if ((HAL_PWM_MAX_CHANNEL <= pwm_channel) && (HAL_PWM_5 > pwm_channel)) {
        log_pwm_error("[PWM_PWM]pwm set advanced failed, ch:%d not support set \r\n", 1, pwm_channel);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    status = pwm_set_advanced_config(pwm_channel, advanced_config);
    return status;
}

hal_pwm_status_t    hal_pwm_set_polarity(hal_pwm_channel_t pwm_channel, bool polarity)
{
    uint8_t pwm_port, num;
    pwm_get_index(pwm_channel, &pwm_port, &num);
    uint32_t save_mask;
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    if (pwm_channel <= HAL_PWM_7) {
        pwm_set_polarity_v2(pwm_channel, polarity);
    } else {
        pwm_set_polarity_v1(pwm_channel, !polarity);
    }
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

#ifdef HAL_SLEEP_MANAGER_ENABLED
#include "hal_spm.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_internal.h"
#endif/*HAL_SLEEP_MANAGER_ENABLED*/

bool ao_backup_register_state = false;
hal_pwm_status_t    hal_pwm_init(hal_pwm_channel_t pwm_channel, hal_pwm_source_clock_t source_clock)
{
    hal_pwm_status_t status = HAL_PWM_STATUS_OK;
    uint8_t pwm_port, num;
    uint8_t tick_num = 2;
    pwm_get_index(pwm_channel, &pwm_port, &num);
    uint32_t save_mask;
    if ((pwm_used_status[pwm_port] != pwm_used_none) && (pwm_used_status[pwm_port] != pwm_used_pwm)) {
        log_pwm_error("[PWM_PWM]pwm init, pwm:%d already used status %x \r\n", 2, pwm_channel, pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if ((pwm_by_channel_status[pwm_port][num] & pwm_status_init) == pwm_status_init) {
        log_pwm_error("[PWM_PWM]pwm ch%d already init \r\n", 1, pwm_channel);
        return HAL_PWM_STATUS_ERROR;
    }
    if (((pwm_status[pwm_port] & pwm_status_init) == pwm_status_init) && (pwm_channel <= HAL_PWM_7)) {
        // log_pwm_error("[PWM_PWM]pwm hw port:%d already init \r\n", 1, pwm_port);
        pwm_by_channel_status[pwm_port][num] |= pwm_status_init;
        return HAL_PWM_STATUS_OK;
    }
#if defined(HAL_SLEEP_MANAGER_ENABLED)
    if(!ao_backup_register_state){
    ao_backup_format_table_t pwm2, pwm3, pwm4;
    pwm2.module_base_addr = 0x421B0000;
    pwm2.module_end_addr = 0x421B0010;
    pwm2.module_backup_enable = 0x1;

    pwm3.module_base_addr = 0x421C0000;
    pwm3.module_end_addr = 0x421C0010;
    pwm3.module_backup_enable = 0x1;

    pwm4.module_base_addr = 0x421D0000;
    pwm4.module_end_addr = 0x421D0010;
    pwm4.module_backup_enable = 0x1;
    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_PWM_0, &pwm2);
    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_PWM_1, &pwm3);
    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_PWM_2, &pwm4);
    ao_backup_register_state = true;
    }
#endif

    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    if (pwm_channel <= HAL_PWM_7) {
        pwm_dma_port_init(pwm_port, tick_num);
    } else {
        status = pwm_init(pwm_channel, source_clock);
    }
    if (status == HAL_PWM_STATUS_OK) {
        pwm_by_channel_status[pwm_port][num] |= pwm_status_init;
        pwm_used_status[pwm_port] = pwm_used_pwm;
        pwm_status[pwm_port] |= pwm_status_init;
    }
    hal_nvic_restore_interrupt_mask(save_mask);
    return status;
}

hal_pwm_status_t    hal_pwm_deinit(hal_pwm_channel_t pwm_channel)
{
    uint8_t pwm_port, num;
    pwm_get_index(pwm_channel, &pwm_port, &num);
    uint32_t save_mask;
    if (((pwm_status[pwm_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_port] != pwm_used_pwm)) {
        log_pwm_error("[PWM_PWM]pwm deinit failed, ch:%d not init or not used pwm ,status:0x%x,used_status:0x%x\r\n", 3, pwm_channel, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if (((pwm_by_channel_status[pwm_port][num] & pwm_status_init) != pwm_status_init) || ((pwm_by_channel_status[pwm_port][num] & pwm_status_start) == pwm_status_start)) {
        log_pwm_error("[PWM_PWM]pwm deinit ch%d not init or is running,status %x \r\n", 2, pwm_channel, pwm_by_channel_status[pwm_port][num]);
        return HAL_PWM_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    pwm_by_channel_status[pwm_port][num] = 0;
    if (pwm_channel <= HAL_PWM_7) {
        if ((pwm_status[pwm_port] & pwm_status_start) == pwm_status_start) {
            hal_nvic_restore_interrupt_mask(save_mask);
            // log_pwm_error("[PWM_PWM] pwm deinit failed, port:%d is running, pwm_status:%x \r\n", 2, pwm_port, pwm_status[pwm_port]);
            return HAL_PWM_STATUS_OK;
        }
        pwm_dma_port_deinit(pwm_port);
    } else {
        pwm_deinit(pwm_channel);
        if ((pwm_status[pwm_port] & pwm_status_start) == pwm_status_start) {
            hal_nvic_restore_interrupt_mask(save_mask);
            log_pwm_error("[PWM_PWM] pwm deinit failed, pwm_port:%d is running \r\n", 1, pwm_port);
            return HAL_PWM_STATUS_OK;
        }
    }
    pwm_used_status[pwm_port] = 0;
    pwm_status[pwm_port] = 0;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    hal_pwm_set_frequency(hal_pwm_channel_t pwm_channel, uint32_t frequency, uint32_t *total_count)
{

    hal_pwm_status_t status = HAL_PWM_STATUS_OK;
    uint8_t pwm_port, num;
    pwm_get_index(pwm_channel, &pwm_port, &num);
    uint32_t save_mask;
    if (((pwm_status[pwm_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_port] != pwm_used_pwm)) {
        log_pwm_error("[PWM_PWM]pwm set frequency failed, ch:%d not init or not used pwm ,status:0x%x,used_status:0x%x\r\n", 3, pwm_channel, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if ((pwm_by_channel_status[pwm_port][num] & pwm_status_init) != pwm_status_init) {
        log_pwm_error("[PWM_PWM]pwm set frequency ch%d not init status %x \r\n", 2, pwm_channel, pwm_by_channel_status[pwm_port][num]);
        return HAL_PWM_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    if (pwm_channel <= HAL_PWM_7) {
        status = pwm_dma_by_channel_frequency(pwm_channel, frequency, total_count);
    } else {
        status = pwm_set_frequency(pwm_channel, frequency, total_count);
    }
    if (status == HAL_PWM_STATUS_OK) {
        pwm_by_channel_status[pwm_port][num] |= pwm_status_freq;
    }
    hal_nvic_restore_interrupt_mask(save_mask);
    return status;
}

hal_pwm_status_t  hal_pwm_set_duty_cycle(hal_pwm_channel_t pwm_channel, uint32_t duty_cycle)
{
    hal_pwm_status_t status = HAL_PWM_STATUS_OK;
    uint8_t pwm_port, num;
    pwm_get_index(pwm_channel, &pwm_port, &num);
    uint32_t save_mask;
    if (((pwm_status[pwm_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_port] != pwm_used_pwm)) {
        log_pwm_error("[PWM_PWM]pwm set duty cycle failed, ch:%d not init or not used pwm ,status:0x%x,used_status:0x%x\r\n", 3, pwm_channel, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if ((pwm_by_channel_status[pwm_port][num] & pwm_status_init) != pwm_status_init) {
        log_pwm_error("[PWM_PWM]pwm set duty cycle ch%d not init status %x \r\n", 2, pwm_channel, pwm_by_channel_status[pwm_port][num]);
        return HAL_PWM_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    if (pwm_channel <= HAL_PWM_7) {
        status = pwm_dma_by_channel_duty_cycle(pwm_channel, duty_cycle);
    } else {
        status = pwm_set_duty_cycle(pwm_channel, duty_cycle);
    }
    if (status == HAL_PWM_STATUS_OK) {
        pwm_by_channel_status[pwm_port][num] |= pwm_status_duty;
    }
    hal_nvic_restore_interrupt_mask(save_mask);
    return status;
}


hal_pwm_status_t    hal_pwm_start(hal_pwm_channel_t pwm_channel)
{
    hal_pwm_status_t status = HAL_PWM_STATUS_OK;
    uint8_t pwm_port, num;
    pwm_get_index(pwm_channel, &pwm_port, &num);
    uint32_t save_mask;
    if (((pwm_status[pwm_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_port] != pwm_used_pwm)) {
        log_pwm_error("[PWM_PWM]pwm start failed, ch:%d not init or not used pwm ,status:0x%x,used_status:0x%x\r\n", 3, pwm_channel, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if (((pwm_by_channel_status[pwm_port][num] & pwm_status_init) != pwm_status_init) || ((pwm_by_channel_status[pwm_port][num] & pwm_status_start) == pwm_status_start)) {
        log_pwm_error("[PWM_PWM]pwm start ch%d not init or is running,status %x \r\n", 2, pwm_channel, pwm_by_channel_status[pwm_port][num]);
        return HAL_PWM_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    pwm_by_channel_status[pwm_port][num] |= pwm_status_start;
    if (((pwm_status[pwm_port] & pwm_status_start) == pwm_status_start) && (pwm_channel <= HAL_PWM_7)) {
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_PWM_STATUS_OK;
    }
    if (pwm_channel <= HAL_PWM_7) {
        pwm_dma_port_start(pwm_port);
    } else {
        pwm_start(pwm_channel);
    }
    pwm_status[pwm_port] |= pwm_status_start;
    hal_nvic_restore_interrupt_mask(save_mask);
    return status;
}

hal_pwm_status_t    hal_pwm_stop(hal_pwm_channel_t pwm_channel)
{
    uint8_t pwm_port, num;
    pwm_get_index(pwm_channel, &pwm_port, &num);
    uint32_t save_mask;
    if (((pwm_status[pwm_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_port] != pwm_used_pwm)) {
        log_pwm_error("[PWM_PWM]pwm stop failed, ch:%d not init or not used pwm ,status:0x%x,used_status:0x%x\r\n", 3, pwm_channel, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if (((pwm_by_channel_status[pwm_port][num] & pwm_status_init) != pwm_status_init) || ((pwm_by_channel_status[pwm_port][num] & pwm_status_start) != pwm_status_start)) {
        log_pwm_error("[PWM_PWM]pwm stop ch%d not init or is not start ,status %x \r\n", 2, pwm_channel, pwm_by_channel_status[pwm_port][num]);
        return HAL_PWM_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    pwm_by_channel_status[pwm_port][num] &= ~pwm_status_start;
    // log_pwm_info("[PWM_PWM] pwm dma stop pwm_channel:%d  \r\n", 1, pwm_channel);
    if (pwm_channel <= HAL_PWM_7) {
        pwm_dma_by_channel_stop(pwm_channel);
    } else {
        pwm_stop(pwm_channel);
    }
    for (int i = 0; i < 4; i++) { //check all channel is stop
        if (((pwm_by_channel_status[pwm_port][i] & pwm_status_start) == pwm_status_start) && (pwm_channel <= HAL_PWM_7)) {
            hal_nvic_restore_interrupt_mask(save_mask);
            log_pwm_info("[PWM_PWM] pwm dma stop failed, pwm_channel%d is running \r\n", 1, (i + pwm_port * 4));
            return HAL_PWM_STATUS_OK;
        }
    }
    if (pwm_port <= 1) {
        pwm_dma_port_stop(pwm_port);
        pwm_status[pwm_port] &= ~pwm_status_start;
    }
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}


hal_pwm_status_t    hal_pwm_get_frequency(hal_pwm_channel_t pwm_channel, uint32_t *frequency)
{
    uint8_t pwm_port, num;
    pwm_get_index(pwm_channel, &pwm_port, &num);
    if (((pwm_status[pwm_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_port] != pwm_used_pwm)) {
        log_pwm_error("[PWM_PWM]pwm get frequency failed, ch:%d not init or not used pwm ,status:0x%x,used_status:0x%x\r\n", 3, pwm_channel, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if ((pwm_by_channel_status[pwm_port][num] & pwm_status_freq) != pwm_status_freq) {
        log_pwm_error("[PWM_PWM]pwm get frequency failed, ch%d not set frequency ,status %x \r\n", 2, pwm_channel, pwm_by_channel_status[pwm_port][num]);
        return HAL_PWM_STATUS_ERROR;
    }
    if (pwm_channel <= HAL_PWM_7) {
        pwm_dma_by_channel_get_frequency(pwm_channel, frequency);
    } else {
        pwm_get_frequency(pwm_channel, frequency);
    }
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    hal_pwm_get_duty_cycle(hal_pwm_channel_t pwm_channel, uint32_t *duty_cycle)
{
    uint8_t pwm_port, num;
    pwm_get_index(pwm_channel, &pwm_port, &num);
    if (((pwm_status[pwm_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_port] != pwm_used_pwm)) {
        log_pwm_error("[PWM_PWM]pwm get duty failed, ch:%d not init or not used pwm ,status:0x%x,used_status:0x%x\r\n", 3, pwm_channel, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if ((pwm_by_channel_status[pwm_port][num] & pwm_status_duty) != pwm_status_duty) {
        log_pwm_error("[PWM_PWM]pwm get duty failed, ch%d not set duty ,status %x \r\n", 2, pwm_channel, pwm_by_channel_status[pwm_port][num]);
        return HAL_PWM_STATUS_ERROR;
    }
    if (pwm_channel <= HAL_PWM_7) {
        pwm_dma_by_channel_get_duty_cycle(pwm_channel, duty_cycle);
    } else {
        pwm_get_duty_cycle(pwm_channel, duty_cycle);
    }
    return HAL_PWM_STATUS_OK;
}



hal_pwm_status_t  hal_pwm_set_frequency_and_duty(hal_pwm_channel_t pwm_channel, hal_pwm_source_clock_t clk, uint32_t frequency, float duty_ratio)
{
    hal_pwm_status_t status = HAL_PWM_STATUS_OK;
    uint32_t duty_cycle, total_count = 0;
    uint8_t pwm_port, num;
    pwm_get_index(pwm_channel, &pwm_port, &num);
    if (((pwm_status[pwm_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_port] != pwm_used_pwm)) {
        log_pwm_error("[PWM_PWM]pwm get duty failed, ch:%d not init or not used pwm ,status:0x%x,used_status:0x%x\r\n", 3, pwm_channel, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if ((pwm_by_channel_status[pwm_port][num] & pwm_status_init) != pwm_status_init) {
        log_pwm_error("[PWM_PWM]pwm get duty failed, ch%d not init ,status %x \r\n", 2, pwm_channel, pwm_by_channel_status[pwm_port][num]);
        return HAL_PWM_STATUS_ERROR;
    }
    status = hal_pwm_set_frequency(pwm_channel, frequency, &total_count);
    if (status != HAL_PWM_STATUS_OK) {
        return HAL_PWM_STATUS_ERROR;
    }
    duty_cycle = (uint32_t)(duty_ratio * total_count);
    status = hal_pwm_set_duty_cycle(pwm_channel, duty_cycle);
    if (status != HAL_PWM_STATUS_OK) {

        return HAL_PWM_STATUS_ERROR;
    }
    return status;
}


hal_pwm_status_t    hal_pwm_dma_init(hal_pwm_dma_port_t pwm_dma_port)
{
    uint32_t save_mask;
    uint8_t tick_num = 2;
    if ((pwm_used_status[pwm_dma_port] != pwm_used_none) && (pwm_used_status[pwm_dma_port] != pwm_used_dma)) {
        log_pwm_error("[PWM_DMA]pwm dma init, port:%d already used status %x \r\n", 2, pwm_dma_port, pwm_used_status[pwm_dma_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if ((pwm_status[pwm_dma_port] & pwm_status_init) == pwm_status_init) {
        log_pwm_error("[PWM_DMA]pwm port%d already init \r\n", 1, pwm_dma_port);
        return HAL_PWM_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    pwm_dma_port_init(pwm_dma_port, tick_num);
    pwm_status[pwm_dma_port] |= pwm_status_init;
    pwm_used_status[pwm_dma_port] = pwm_used_dma;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    hal_pwm_dma_deinit(hal_pwm_dma_port_t pwm_dma_port)
{
    uint32_t save_mask;
    if (((pwm_status[pwm_dma_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_dma_port] != pwm_used_dma)) {
        log_pwm_error("[PWM_DMA]pwm dma deinit failed, port:%d not init or not used pwm dma ,status:0x%x,used_status:0x%x\r\n", 3, pwm_dma_port, pwm_status[pwm_dma_port], pwm_used_status[pwm_dma_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if ((pwm_status[pwm_dma_port] & pwm_status_start) == pwm_status_start) {
        log_pwm_error("[PWM_DMA]pwm dma deinit failed, port:%d is running ,status:0x%x\r\n", 2, pwm_dma_port, pwm_status[pwm_dma_port]);
        return HAL_PWM_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    pwm_dma_port_deinit(pwm_dma_port);
    pwm_used_status[pwm_dma_port] = 0;
    pwm_status[pwm_dma_port] = 0;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    hal_pwm_dma_set_frequency(hal_pwm_dma_port_t pwm_dma_port, uint32_t frequency, uint32_t *total_count)
{
    uint32_t save_mask;
    hal_pwm_status_t status = HAL_PWM_STATUS_OK;
    if (((pwm_status[pwm_dma_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_dma_port] != pwm_used_dma)) {
        log_pwm_error("[PWM_DMA]pwm dma set frequency failed, port:%d not init or not used pwm dma ,status:0x%x,used_status:0x%x\r\n", 3, pwm_dma_port, pwm_status[pwm_dma_port], pwm_used_status[pwm_dma_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    status = pwm_dma_set_frequency(pwm_dma_port, frequency, total_count);
    pwm_status[pwm_dma_port] |= pwm_status_freq;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    hal_pwm_dma_set_config(hal_pwm_dma_port_t pwm_dma_port, hal_pwm_dma_config *config)
{
    uint32_t save_mask;
    hal_pwm_status_t status = HAL_PWM_STATUS_OK;
    if (((pwm_status[pwm_dma_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_dma_port] != pwm_used_dma)) {
        log_pwm_error("[PWM_DMA]pwm dma set config failed, port:%d not init or not used pwm dma ,status:0x%x,used_status:0x%x\r\n", 3, pwm_dma_port, pwm_status[pwm_dma_port], pwm_used_status[pwm_dma_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if ((pwm_status[pwm_dma_port] & pwm_status_freq) != pwm_status_freq) {
        log_pwm_error("[PWM_DMA]pwm dma set config failed, port:%d not set freq,status:0x%x\r\n", 2, pwm_dma_port, pwm_status[pwm_dma_port]);
        return HAL_PWM_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    status = pwm_dma_set_config(pwm_dma_port, config);
    pwm_status[pwm_dma_port] |= pwm_status_config;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    hal_pwm_dma_register_callback(hal_pwm_dma_port_t pwm_dma_port, hal_pwm_irq_enable *irq_enable, hal_pwm_callback_t pwm_callback, void *user_data)
{
    uint32_t save_mask;
    if (((pwm_status[pwm_dma_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_dma_port] != pwm_used_dma)) {
        log_pwm_error("[PWM_DMA]pwm dma register callback failed, port:%d not init or not used pwm dma ,status:0x%x,used_status:0x%x\r\n", 3, pwm_dma_port, pwm_status[pwm_dma_port], pwm_used_status[pwm_dma_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    pwm_dma_register_callback(pwm_dma_port, irq_enable, pwm_callback, user_data);
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    hal_pwm_dma_enqueue_BufA(hal_pwm_dma_port_t pwm_dma_port, uint32_t *bufaddr, uint16_t sample_cnt)
{
    uint32_t save_mask;
    hal_pwm_status_t status = HAL_PWM_STATUS_OK;
    if (((pwm_status[pwm_dma_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_dma_port] != pwm_used_dma)) {
        log_pwm_error("[PWM_DMA]pwm dma set BUFA error, port:%d not init or not used pwm dma ,status:0x%x,used_status:0x%x\r\n", 3, pwm_dma_port, pwm_status[pwm_dma_port], pwm_used_status[pwm_dma_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if ((pwm_status[pwm_dma_port] & pwm_status_config) != pwm_status_config) {
        log_pwm_error("[PWM_DMA] pwm dma set BUFA error, port:%d not config,status:0x%x\r\n", 1, pwm_dma_port, pwm_status[pwm_dma_port]);
        return HAL_PWM_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    status = pwm_dma_enqueue_BufA(pwm_dma_port, bufaddr, sample_cnt);
    if (status == HAL_PWM_STATUS_OK) {
        pwm_status[pwm_dma_port] |= pwm_status_bufa;
    }
    hal_nvic_restore_interrupt_mask(save_mask);
    return status;
}

hal_pwm_status_t    hal_pwm_dma_enqueue_BufB(hal_pwm_dma_port_t pwm_dma_port, uint32_t *bufaddr, uint16_t sample_cnt)
{
    uint32_t save_mask;
    hal_pwm_status_t status = HAL_PWM_STATUS_OK;
    if (((pwm_status[pwm_dma_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_dma_port] != pwm_used_dma)) {
        log_pwm_error("[PWM_DMA]pwm dma set BUFB error, port:%d not init or not used pwm dma ,status:0x%x,used_status:0x%x\r\n", 3, pwm_dma_port, pwm_status[pwm_dma_port], pwm_used_status[pwm_dma_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if ((pwm_status[pwm_dma_port] & pwm_status_config) != pwm_status_config) {
        log_pwm_error("[PWM_DMA] pwm dma set BUFB error, port:%d not config,status:0x%x\r\n", 1, pwm_dma_port, pwm_status[pwm_dma_port]);
        return HAL_PWM_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    status = pwm_dma_enqueue_BufB(pwm_dma_port, bufaddr, sample_cnt);
    if (status == HAL_PWM_STATUS_OK) {
        pwm_status[pwm_dma_port] |= pwm_status_bufb;
    }
    hal_nvic_restore_interrupt_mask(save_mask);
    return status;
}

hal_pwm_status_t hal_pwm_dma_start(hal_pwm_dma_port_t pwm_dma_port)
{
    uint32_t save_mask;
    if (((pwm_status[pwm_dma_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_dma_port] != pwm_used_dma)) {
        log_pwm_error("[PWM_DMA]pwm dma start error, port:%d not init or not used pwm dma ,status:0x%x,used_status:0x%x\r\n", 3, pwm_dma_port, pwm_status[pwm_dma_port], pwm_used_status[pwm_dma_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if (((pwm_status[pwm_dma_port] & pwm_status_start) == pwm_status_start) || ((pwm_status[pwm_dma_port] & pwm_status_bufa) != pwm_status_bufa) || ((pwm_status[pwm_dma_port] & pwm_status_bufb) != pwm_status_bufb)) {
        log_pwm_error("[PWM_DMA]pwm dma start error, port:%d already start or not set bufa or bufb,status:0x%x \r\n", 1, pwm_dma_port, pwm_status[pwm_dma_port]);
        return HAL_PWM_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    pwm_dma_start(pwm_dma_port);
    pwm_status[pwm_dma_port] |= pwm_status_start;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t hal_pwm_dma_stop(hal_pwm_dma_port_t pwm_dma_port)
{
    hal_pwm_status_t status = HAL_PWM_STATUS_OK;
    uint32_t save_mask;
    if (((pwm_status[pwm_dma_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_dma_port] != pwm_used_dma)) {
        log_pwm_error("[PWM_DMA]pwm dma stop error, port:%d not init or not used pwm dma ,status:0x%x,used_status:0x%x\r\n", 3, pwm_dma_port, pwm_status[pwm_dma_port], pwm_used_status[pwm_dma_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if ((pwm_status[pwm_dma_port] & pwm_status_start) != pwm_status_start) {
        log_pwm_error("[PWM_DMA]pwm dma stop error, port:%d not start ,status:0x%x\r\n", 2, pwm_dma_port, pwm_status[pwm_dma_port]);
        return HAL_PWM_STATUS_ERROR;
    }
    status = pwm_dma_stop(pwm_dma_port);
    if (status == HAL_PWM_STATUS_OK) {
        hal_nvic_save_and_set_interrupt_mask(&save_mask);
        pwm_status[pwm_dma_port] &= ~pwm_status_start;
        hal_nvic_restore_interrupt_mask(save_mask);
    }
    return status;
}


#if defined(HAL_PWM_LED_SUPPORTED) || defined(HAL_PWM_RGB_SUPPORTED)

#include "hal_gpt.h"
pwm_led_config_bk_t *led_channel_bk[HAL_PWM_LED_MAX_CHANNEL];
static void led_duty_covert_count(uint8_t channel, uint8_t duty, uint16_t total_cnt)
{
    if (channel <= HAL_PWM_7) {
        pwm_dma_led_rgb_set_duty_cycle(channel, duty, total_cnt);
    } else {
        pwm_led_set_duty_cycle(channel, duty);
    }
}
static uint16_t led_get_duty(hal_pwm_led_config_t *led_config, pwm_led_config_bk_t *led_channel_bk, uint8_t *get_duty, uint16_t period_ms)
{

    if (led_config->t0_ms >= period_ms) {
        led_config->t0_ms = led_config->t0_ms - period_ms;
        *get_duty = 0;
        return 0;
    }
repeat_start:
    if (led_config->repeat_count != 0) {
        if (led_channel_bk->init_status == 0) {
            led_channel_bk->t1_rising_ms   = led_config->t1_rising_ms;                       //backup
            led_channel_bk->t1_on_ms       = led_config->t1_on_ms;                           //backup
            led_channel_bk->t2_falling_ms  = led_config->t2_falling_ms;                      //backup
            led_channel_bk->t2_off_ms      = led_config->t2_off_ms;                          //backup
            led_channel_bk->t3_ms          = led_config->t3_ms;                              //backup
            led_channel_bk->on_step_rem    = led_config->on_step_rem;
            led_channel_bk->off_step_rem   = led_config->off_step_rem;
            led_channel_bk->on_step_inc    = led_config->on_step_inc;
            led_channel_bk->off_step_inc   = led_config->off_step_inc;
            led_channel_bk->t1t2_repeat_count = led_config->t1t2_repeat_count;
            led_channel_bk->init_status = 1;
        }
        if (led_config->t1t2_repeat_count != 0) {
            if (led_config->t1_rising_ms >= period_ms) {
                if (((led_config->start_duty + led_config->on_step_inc) >= led_config->high_duty) ||
                    ((led_config->start_duty + led_config->on_step_inc) < led_config->start_duty)) { //avoid overflow
                    *get_duty = led_config->high_duty;
                } else {
                    *get_duty = led_config->start_duty + led_config->on_step_inc;
                }
                led_config->on_step_inc += led_channel_bk->on_step_inc;
                led_config->on_step_rem += led_channel_bk->on_step_rem;
                if (led_config->on_step_rem >= led_config->t1_rising_ms / period_ms) {
                    led_config->on_step_inc += 1;
                    led_config->on_step_rem -= led_config->t1_rising_ms / period_ms;
                }
                led_config->t1_rising_ms =  led_config->t1_rising_ms - period_ms;
                return 0;
            }
            if (led_config->t1_on_ms >= period_ms) {
                led_config->t1_on_ms =  led_config->t1_on_ms - period_ms;
                *get_duty = led_config->high_duty;
                return 0;
            }
            if (led_config->t2_falling_ms >= period_ms) {
                if (((led_config->high_duty - led_config->off_step_inc) <= led_config->end_duty) ||
                    ((led_config->high_duty - led_config->off_step_inc) > led_config->high_duty)) { //avoid over flow
                    *get_duty = led_config->end_duty;
                } else {
                    *get_duty = led_config->high_duty - led_config->off_step_inc;
                }
                led_config->off_step_inc += led_channel_bk->off_step_inc;
                led_config->off_step_rem += led_channel_bk->off_step_rem;
                if (led_config->off_step_rem >= led_config->t2_falling_ms / period_ms) {
                    led_config->off_step_inc += 1;
                    led_config->off_step_rem -= led_config->t2_falling_ms / period_ms;
                }
                led_config->t2_falling_ms =  led_config->t2_falling_ms - period_ms;
                return 0;
            }
            if (led_config->t2_off_ms >= period_ms) {
                led_config->t2_off_ms =  led_config->t2_off_ms - period_ms;
                *get_duty = led_config->end_duty;
                return 0;
            }
            led_config->t1t2_repeat_count = led_config->t1t2_repeat_count - 1;
            led_config->t1_rising_ms = led_channel_bk->t1_rising_ms;
            led_config->t1_on_ms     = led_channel_bk->t1_on_ms;
            led_config->t2_falling_ms = led_channel_bk->t2_falling_ms;
            led_config->t2_off_ms    = led_channel_bk->t2_off_ms;
            led_config->on_step_rem  = led_channel_bk->on_step_rem;
            led_config->off_step_rem = led_channel_bk->off_step_rem;
            led_config->on_step_inc  = led_channel_bk->on_step_inc;
            led_config->off_step_inc = led_channel_bk->off_step_inc;
            goto repeat_start;
        }
        if (led_config->t3_ms >= period_ms) {
            led_config->t3_ms =  led_config->t3_ms - period_ms;
            *get_duty = led_config->end_duty;
            return 0;
        }
        if (led_config->repeat_count != 0xFF) {
            led_config->repeat_count--;
        }
        led_config->t1_rising_ms = led_channel_bk->t1_rising_ms;
        led_config->t1_on_ms     = led_channel_bk->t1_on_ms;
        led_config->t2_falling_ms = led_channel_bk->t2_falling_ms;
        led_config->t2_off_ms    = led_channel_bk->t2_off_ms;
        led_config->t3_ms        = led_channel_bk->t3_ms;
        led_config->on_step_rem  = led_channel_bk->on_step_rem;
        led_config->off_step_rem = led_channel_bk->off_step_rem;
        led_config->on_step_inc  = led_channel_bk->on_step_inc;
        led_config->off_step_inc = led_channel_bk->off_step_inc;
        led_config->t1t2_repeat_count = led_channel_bk->t1t2_repeat_count;
        goto repeat_start;
    } else {
        led_channel_bk->init_status = 0;
        *get_duty = 0;
        return 1;
    }
    return 1;
}
static void led_config_convert(hal_pwm_led_config_t *led_config, hal_pwm_led_config_flex_ext_t *flex_ext, uint16_t period_ms)
{
    uint16_t count_rising = flex_ext->config_ext.timing.t1.t_rising / period_ms;
    uint16_t count_falling = flex_ext->config_ext.timing.t2.t_falling / period_ms;
    led_config->t0_ms = flex_ext->config_ext.timing.t0;
    led_config->t1_rising_ms = flex_ext->config_ext.timing.t1.t_rising;
    led_config->t1_on_ms = flex_ext->config_ext.timing.t1.t_lightest;
    led_config->t2_falling_ms = flex_ext->config_ext.timing.t2.t_falling;
    led_config->t2_off_ms = flex_ext->config_ext.timing.t2.t_darkest;
    led_config->t3_ms = flex_ext->config_ext.timing.t3;
    led_config->start_duty = flex_ext->other_config.start_brightness;
    led_config->end_duty = flex_ext->other_config.end_brightness;
    led_config->high_duty = flex_ext->config_ext.brightness;
    if (count_rising != 0) {
        led_config->on_step_inc = (flex_ext->config_ext.brightness - flex_ext->other_config.start_brightness) / count_rising;
        led_config->on_step_rem = (flex_ext->config_ext.brightness - flex_ext->other_config.start_brightness) % count_rising;
    } else {
        led_config->on_step_inc = 0;
        led_config->on_step_rem = 0;
    }
    if (count_falling != 0) {
        led_config->off_step_inc = (flex_ext->config_ext.brightness - flex_ext->other_config.end_brightness) / count_falling;
        led_config->off_step_rem = (flex_ext->config_ext.brightness - flex_ext->other_config.end_brightness) % count_falling;
    } else {
        led_config->off_step_inc = 0;
        led_config->off_step_rem = 0;
    }
    led_config->t1t2_repeat_count = flex_ext->config_ext.blink_nums;
    led_config->repeat_count = flex_ext->other_config.repeat_times;
}
#endif

/**********************************************************************************************************************************************************
**************************************************************** pwm_led ******************************************************************************
**********************************************************************************************************************************************************/
#ifdef HAL_PWM_LED_SUPPORTED
#define led_frequency   (60)    //defalult 60hz
pwm_led_para_t led_para[HAL_PWM_MAX_CHANNEL];
uint32_t pwm_led_handle[3];
static void pwm_led_isr(void *pwm_led)
{
    uint8_t led = *(uint8_t *)pwm_led;
    uint8_t pwm_port, num;
    pwm_get_index(led, &pwm_port, &num);
    if (led >= 8) {
        hal_gpt_sw_start_timer_ms(pwm_led_handle[led - 8], led_para[led].led_one_period_ms, pwm_led_isr, &(led_para[led].led_channel));
    }
    int channels = pwm_port <= 1 ? 4 : 1;
    for (int i = 0; i < channels; i++) {
        int idx = pwm_port <= 1 ? pwm_port * 4 + i : led;
        if (!(pwm_by_channel_status[pwm_port][i] & pwm_status_start)) {
            if (pwm_by_channel_status[pwm_port][i] & pwm_status_init) {
                led_duty_covert_count(idx, 0, led_para[led].led_one_period_count);
            }
            continue;
        }
        uint8_t duty;
        int ret = led_get_duty(led_para[idx].led_config, led_channel_bk[idx], &duty, led_para[idx].led_one_period_ms);
        uint8_t led_idx = (pwm_port <= 1) ? (idx + pwm_port * 4) : led;
        led_duty_covert_count(led_idx, duty, led_para[idx].led_one_period_count);
        if (ret && ((pwm_by_channel_status[pwm_port][i] & pwm_status_unmask) == pwm_status_unmask) && (led_para[idx].pwm_led_info.call_back != NULL)) {
            led_para[idx].pwm_led_info.call_back(led_para[idx].pwm_led_info.user_data);
        }
    }
}

hal_pwm_status_t    hal_pwm_led_set_polarity(hal_pwm_led_channel_t pwm_led, bool polarity)
{
    hal_pwm_set_polarity((hal_pwm_channel_t)pwm_led, polarity);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    hal_pwm_led_init(hal_pwm_led_channel_t pwm_led)
{
    uint8_t pwm_port, num;
    uint8_t tick_num = 2;
    pwm_get_index(pwm_led, &pwm_port, &num);
    uint32_t save_mask;
    if ((pwm_used_status[pwm_port] != pwm_used_none) && (pwm_used_status[pwm_port] != pwm_used_led)) {
        log_pwm_error("[PWM_LED]pwm led init, port%d already used status %d \r\n", 2, pwm_port, pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if ((pwm_by_channel_status[pwm_port][num] & pwm_status_init) == pwm_status_init) {
        log_pwm_error("[PWM_LED]pwm ch%d already init \r\n", 1, pwm_led);
        return HAL_PWM_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    led_para[pwm_led].led_config = k_malloc(sizeof(hal_pwm_led_config_t));
    if (led_para[pwm_led].led_config == NULL) {
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_PWM_STATUS_ERROR;
    }
    led_channel_bk[pwm_led] = k_malloc(sizeof(pwm_led_config_bk_t));
    if (led_channel_bk[pwm_led] == NULL) {
        k_free(led_channel_bk[pwm_led]);
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_PWM_STATUS_ERROR;
    }
    pwm_by_channel_status[pwm_port][num] |= pwm_status_init;
    led_para[pwm_led].led_one_period_ms = (uint16_t)(1000 / led_frequency);
    if (pwm_port <= 1) {       // pwm isr
        led_para[pwm_led].led_one_period_count  = (uint16_t)(1000000 / led_frequency/ tick_num);  //calc one period count
        if ((pwm_status[pwm_port] & pwm_status_init) == pwm_status_init) {
            hal_nvic_restore_interrupt_mask(save_mask);
            return HAL_PWM_STATUS_OK;
        }

        pwm_dma_port_init(pwm_port, tick_num);
        led_para[pwm_led].led_channel = pwm_led;
        pwm_dma_port_register_callback(pwm_port, pwm_led_isr, &(led_para[pwm_led].led_channel));
    } else {
        led_para[pwm_led].led_one_period_count  = 255;    //calc one period count
        pwm_led_rgb_init(pwm_led);
    }
    pwm_status[pwm_port] |= pwm_status_init;
    pwm_used_status[pwm_port] = pwm_used_led;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}


hal_pwm_status_t    hal_pwm_led_deinit(hal_pwm_led_channel_t pwm_led)
{
    uint8_t pwm_port, num;
    pwm_get_index(pwm_led, &pwm_port, &num);
    uint32_t save_mask;
    if (((pwm_status[pwm_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_port] != pwm_used_led)) {
        log_pwm_error("[PWM_LED]pwm led deinit failed, led:%d not init or not used led ,status:0x%x,used_status:0x%x\r\n", 3, pwm_led, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if (((pwm_by_channel_status[pwm_port][num]& pwm_status_start) == pwm_status_start) || ((pwm_by_channel_status[pwm_port][num]& pwm_status_init) != pwm_status_init)) {
        log_pwm_error("[PWM_LED] pwm led deinit failed, led:%d is running or is not init,status:0x%x\r\n", 2, pwm_led, pwm_by_channel_status[pwm_port][num]);
        return HAL_PWM_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    pwm_by_channel_status[pwm_port][num] = 0;

    k_free(led_para[pwm_led].led_config);
    k_free(led_channel_bk[pwm_led]);
    memset(&(led_para[pwm_led]), 0x0, sizeof(pwm_led_para_t));

    if (pwm_port > 1) {
        pwm_led_rgb_deinit(pwm_led);
        hal_gpt_sw_free_timer(pwm_led_handle[pwm_led]);
    }
    if ((pwm_status[pwm_port] & pwm_status_start) == pwm_status_start) {
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_PWM_STATUS_OK;
    }
    pwm_used_status[pwm_port] = 0;
    pwm_status[pwm_port] = 0;
    if (pwm_port <= 1) {
        pwm_dma_port_deinit(pwm_port);
    }
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    hal_pwm_led_config_ext(hal_pwm_led_channel_t pwm_led, hal_pwm_led_config_flex_ext_t *flex_ext)
{
    uint8_t pwm_port, num;
    pwm_get_index(pwm_led, &pwm_port, &num);
    uint32_t save_mask;
    if (((pwm_status[pwm_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_port] != pwm_used_led)) {
        log_pwm_error("[PWM_LED]pwm led config failed, led:%d not init or not used led ,status:0x%x,used_status:0x%x\r\n", 3, pwm_led, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if (((pwm_by_channel_status[pwm_port][num] & pwm_status_init) != pwm_status_init) || ((pwm_by_channel_status[pwm_port][num] & pwm_status_start) == pwm_status_start)) {
        log_pwm_error("[PWM_LED]pwm led config failed, led:%d is running or is not init,status:0x%x\r\n", 2, pwm_led, pwm_by_channel_status[pwm_port][num]);
        return HAL_PWM_STATUS_ERROR;
    }
    memset(led_para[pwm_led].led_config, 0, sizeof(hal_pwm_led_config_t));
    memset(led_channel_bk[pwm_led], 0, sizeof(pwm_led_config_bk_t));
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    led_config_convert(led_para[pwm_led].led_config, flex_ext, led_para[pwm_led].led_one_period_ms);
    pwm_by_channel_status[pwm_port][num] |= pwm_status_config;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    hal_pwm_led_start(hal_pwm_led_channel_t pwm_led)
{
    uint8_t pwm_port, num;
    pwm_get_index(pwm_led, &pwm_port, &num);
    uint32_t save_mask;
    if (((pwm_status[pwm_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_port] != pwm_used_led)) {
        log_pwm_error("[PWM_LED]pwm led start failed, led:%d not init or not used led ,status:0x%x,used_status:0x%x\r\n", 3, pwm_led, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if (((pwm_by_channel_status[pwm_port][num] & pwm_status_init) != pwm_status_init) || ((pwm_by_channel_status[pwm_port][num] & pwm_status_start) == pwm_status_start)) {
        log_pwm_error("[PWM_LED]pwm led start failed, led:%d is running or is not init,status:0x%x\r\n", 2, pwm_led, pwm_by_channel_status[pwm_port][num]);
        return HAL_PWM_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    pwm_by_channel_status[pwm_port][num] |= pwm_status_start;
    led_duty_covert_count(pwm_led, 0, led_para[pwm_led].led_one_period_count);
    if (pwm_port <= 1) {
        if ((pwm_status[pwm_port] & pwm_status_start) != pwm_status_start) {
            pwm_dma_led_rgb_port_start(pwm_port, led_para[pwm_led].led_one_period_count - 1, 3);
            pwm_status[pwm_port] |= pwm_status_start;
        }
    } else {
        led_para[pwm_led].led_channel = pwm_led;
        hal_gpt_sw_get_timer(&pwm_led_handle[pwm_led - 8]);
        hal_gpt_sw_start_timer_ms(pwm_led_handle[pwm_led - 8], led_para[pwm_led].led_one_period_ms, pwm_led_isr, &(led_para[pwm_led].led_channel));
        pwm_led_rgb_start(pwm_led);
        pwm_status[pwm_port] |= pwm_status_start;
    }
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    hal_pwm_led_stop(hal_pwm_led_channel_t pwm_led)
{
    uint8_t pwm_port, num;
    pwm_get_index(pwm_led, &pwm_port, &num);
    uint32_t save_mask;
    if (((pwm_status[pwm_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_port] != pwm_used_led)) {
        log_pwm_error("[PWM_LED]pwm led stop failed, led:%d not init or not used led ,status:0x%x,used_status:0x%x\r\n", 3, pwm_led, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    if ((pwm_by_channel_status[pwm_port][num] & pwm_status_start) != pwm_status_start) {
        return HAL_PWM_STATUS_OK;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    pwm_by_channel_status[pwm_port][num] &= ~pwm_status_start;
    if (pwm_port > 1) {
        pwm_led_rgb_stop(pwm_led);
    }
    int idx = pwm_port <= 1 ? 4 : 3;
    for (int i = 0; i < idx; i++) { //check all channel is stop
        if ((pwm_by_channel_status[pwm_port][i] & pwm_status_start) == pwm_status_start) {
            hal_nvic_restore_interrupt_mask(save_mask);
            return HAL_PWM_STATUS_OK;
        }
    }
    if (pwm_port <= 1) {
        hal_gpt_sw_stop_timer_ms(pwm_led_handle[pwm_led]);
        pwm_dma_led_rgb_port_stop(pwm_port, (led_para[pwm_led].led_one_period_count - 1), 3);
    }
    pwm_status[pwm_port] &= ~pwm_status_start;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t hal_pwm_led_register_callback(hal_pwm_led_channel_t pwm_led, hal_pwm_led_callback_t pwm_led_callback, void *user_data)
{
    uint32_t save_mask;
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    led_para[pwm_led].pwm_led_info.call_back = pwm_led_callback;
    led_para[pwm_led].pwm_led_info.user_data = user_data;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}
hal_pwm_status_t hal_pwm_led_unmask(hal_pwm_led_channel_t pwm_led)
{
    uint8_t pwm_port, num;
    pwm_get_index(pwm_led, &pwm_port, &num);
    uint32_t save_mask;
    if (((pwm_status[pwm_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_port] != pwm_used_led)) {
        log_pwm_error("[PWM_LED]pwm led unmask failed, led:%d not init or not used led ,status:0x%x,used_status:0x%x\r\n", 3, pwm_led, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    pwm_by_channel_status[pwm_port][num] |= pwm_status_unmask;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t hal_pwm_led_mask(hal_pwm_led_channel_t pwm_led)
{
    uint8_t pwm_port, num;
    pwm_get_index(pwm_led, &pwm_port, &num);
    uint32_t save_mask;
    if (((pwm_status[pwm_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_port] != pwm_used_led)) {
        log_pwm_error("[PWM_LED]pwm led mask failed, led:%d not init or not used led ,status:0x%x,used_status:0x%x\r\n", 3, pwm_led, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    pwm_by_channel_status[pwm_port][num] &= ~pwm_status_unmask;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}
#endif // HAL_PWM_LED_SUPPORTED


/**********************************************************************************************************************************************************
**************************************************************** pwm_rgb ******************************************************************************
**********************************************************************************************************************************************************/

#ifdef HAL_PWM_RGB_SUPPORTED

void rgb_duty_covert_count(hal_pwm_port_t pwm_port, uint8_t channel, uint8_t duty, uint16_t total_count)
{
    led_duty_covert_count((pwm_port * 4 + channel), duty, total_count);
}


/** @brief The PWM DMA port */
pwm_rgb_para_t pwm_rgb_para[HAL_PWM_PORT_MAX_CHANNEL];
uint32_t pwm_rgb_handle;
#define INCREMENT_CYCLIC(var, max_val, min_val) do { var = (var + 1 > max_val) ? min_val : var + 1; } while(0)

static void zero_duty(hal_pwm_port_t pwm_port, pwm_rgb_config_t *led_rgb)
{
    rgb_duty_covert_count(pwm_port, *(led_rgb->rgb_channel_setting + 0), 0, pwm_rgb_para[pwm_port].rgb_one_period_count);   //convert duty to R
    rgb_duty_covert_count(pwm_port, *(led_rgb->rgb_channel_setting + 1), 0, pwm_rgb_para[pwm_port].rgb_one_period_count);   //convert duty to G
    rgb_duty_covert_count(pwm_port, *(led_rgb->rgb_channel_setting + 2), 0, pwm_rgb_para[pwm_port].rgb_one_period_count);   //convert duty to B
}


static void pwm_rgb_handle_config(hal_pwm_port_t pwm_port, pwm_rgb_config_t *led_rgb)
{
    if (!(led_rgb->status & pwm_status_start)) {
        return;
    }
    switch (led_rgb->mode) {
        case rgb_breath: {
            uint8_t breath_ret = 1;
            for (int i = 0; i < 3; i++) {
                pwm_rgb_led_config_t *rgb_config = (pwm_rgb_led_config_t *)(led_rgb->user_data + sizeof(pwm_rgb_led_config_t) * i);
                pwm_led_config_bk_t *bk_rgb_config = (pwm_led_config_bk_t *)(led_rgb->bk_user_data + sizeof(pwm_led_config_bk_t) * i);

                uint8_t duty = 0;
                if (rgb_config->status == pwm_status_config) {
                    breath_ret &= led_get_duty(&(rgb_config->led_config), bk_rgb_config, &duty,
                                               pwm_rgb_para[pwm_port].rgb_one_period_ms);
                }
                rgb_duty_covert_count(pwm_port, *(led_rgb->rgb_channel_setting + i), duty, pwm_rgb_para[pwm_port].rgb_one_period_count);
            }
            if (breath_ret) {
                zero_duty(pwm_port, led_rgb);
                if ((led_rgb->status & pwm_status_unmask) == pwm_status_unmask && led_rgb->rgb_info.call_back != NULL) {
                    led_rgb->rgb_info.call_back(led_rgb->rgb_info.user_data);
                }
            }
            return;
        }
        case rgb_real_time: {
#ifdef RGB_REAL_TIME_FIFO
            rgb_real_time_config_t *entry = k_queue_get((struct k_queue *) & (led_rgb->real_time), K_NO_WAIT);
            if (entry == NULL) {
                zero_duty(pwm_port, led_rgb);
                if ((led_rgb->status & pwm_status_unmask) == pwm_status_unmask &&
                    led_rgb->rgb_info.call_back != NULL) {
                    led_rgb->rgb_info.call_back(led_rgb->rgb_info.user_data);
                }
            } else {
                // log_pwm_error("[PWM_RGB]pwm_rgb_handle_config, port:%d rgb_r %x, rgb_g %x, rgb_b %x \r\n", 4, pwm_port, entry->rgb_r, entry->rgb_g, entry->rgb_b);
                rgb_duty_covert_count(pwm_port, *(led_rgb->rgb_channel_setting + 0), entry->rgb_r, pwm_rgb_para[pwm_port].rgb_one_period_count);
                rgb_duty_covert_count(pwm_port, *(led_rgb->rgb_channel_setting + 1), entry->rgb_g, pwm_rgb_para[pwm_port].rgb_one_period_count);
                rgb_duty_covert_count(pwm_port, *(led_rgb->rgb_channel_setting + 2), entry->rgb_b, pwm_rgb_para[pwm_port].rgb_one_period_count);
                (*(led_rgb->bk_user_data))--;
                k_free(entry);
            }
#endif

#ifdef RGB_REAL_TIME_ACK
            // log_pwm_error("[PWM_RGB]pwm_rgb_handle_config, port:%d status %x \r\n", 2, pwm_port, led_rgb->status);
            zero_duty(pwm_port, led_rgb);
            if ((led_rgb->status & pwm_status_unmask) == pwm_status_unmask &&
                led_rgb->rgb_info.call_back != NULL) {
                led_rgb->rgb_info.call_back(led_rgb->rgb_info.user_data);
            }
#endif
            return;
        }
        case rgb_flash: {
            rgb_flash_config_t *led_config = (rgb_flash_config_t *)led_rgb->user_data;
            uint16_t *user_count = (uint16_t *) led_rgb->bk_user_data;
repeat_start:
            if ((led_config->repeat_count == 0) && (led_config->irq_left_size == 0)) {
                zero_duty(pwm_port, led_rgb);
                if ((led_rgb->status & pwm_status_unmask) == pwm_status_unmask && led_rgb->rgb_info.call_back != NULL) {
                    led_rgb->rgb_info.call_back(led_rgb->rgb_info.user_data);
                }
            } else {
                (*user_count) ++;
                if ((*(led_rgb->bk_user_data)) <= led_config->size) {
                    size_t flash_idx = (*user_count) - 1;
                    rgb_duty_covert_count(pwm_port, *(led_rgb->rgb_channel_setting + 0), *(led_config->rgb_r + flash_idx), pwm_rgb_para[pwm_port].rgb_one_period_count);
                    rgb_duty_covert_count(pwm_port, *(led_rgb->rgb_channel_setting + 1), *(led_config->rgb_g + flash_idx), pwm_rgb_para[pwm_port].rgb_one_period_count);
                    rgb_duty_covert_count(pwm_port, *(led_rgb->rgb_channel_setting + 2), *(led_config->rgb_b + flash_idx), pwm_rgb_para[pwm_port].rgb_one_period_count);
                    if ((led_config->irq_left_size != 0) && (led_config->repeat_count == 1) && ((led_config->size - flash_idx) <= led_config->irq_left_size)) {
                        if ((led_rgb->status & pwm_status_unmask) == pwm_status_unmask && led_rgb->rgb_info.call_back != NULL) {
                            led_rgb->rgb_info.call_back(led_rgb->rgb_info.user_data);
                        }
                    }
                } else {
                    if (led_config->repeat_count != 0xFF) {
                        led_config->repeat_count--;
                    }
                    (*(user_count)) = 0;
                    goto repeat_start;
                }
            }
            return;
        }
        case rgb_flash_v2: {
            rgb_flash_config_v2_t *led_config = (rgb_flash_config_v2_t *)led_rgb->user_data;
            uint16_t *user_count = (uint16_t *) led_rgb->bk_user_data;
repeat_start_v2:
            if ((led_config->repeat_count == 0) && (led_config->irq_left_size == 0)) {
                zero_duty(pwm_port, led_rgb);
                if ((led_rgb->status & pwm_status_unmask) == pwm_status_unmask && led_rgb->rgb_info.call_back != NULL) {
                    led_rgb->rgb_info.call_back(led_rgb->rgb_info.user_data);
                }
            } else {
                (*user_count) += 3;
                if ((*(user_count)) <= led_config->size) {
                    uint16_t flash_idx = (*(user_count)) - 3;
                    rgb_duty_covert_count(pwm_port, *(led_rgb->rgb_channel_setting + 0), *(led_config->rgb + flash_idx + 0), pwm_rgb_para[pwm_port].rgb_one_period_count);
                    rgb_duty_covert_count(pwm_port, *(led_rgb->rgb_channel_setting + 1), *(led_config->rgb + flash_idx + 1), pwm_rgb_para[pwm_port].rgb_one_period_count);
                    rgb_duty_covert_count(pwm_port, *(led_rgb->rgb_channel_setting + 2), *(led_config->rgb + flash_idx + 2), pwm_rgb_para[pwm_port].rgb_one_period_count);
                    if ((led_config->irq_left_size != 0) && (led_config->repeat_count == 1) && ((led_config->size - flash_idx) <= led_config->irq_left_size)) {
                        if ((led_rgb->status & pwm_status_unmask) == pwm_status_unmask && led_rgb->rgb_info.call_back != NULL) {
                            led_rgb->rgb_info.call_back(led_rgb->rgb_info.user_data);
                        }
                    }
                } else {
                    if (led_config->repeat_count != 0xFF) {
                        led_config->repeat_count--;
                    }
                    (*(user_count)) = 0;
                    goto repeat_start_v2;
                }
            }
            return;
        }
        default:
            return;
    }
}

static void  pwm_rgb_isr(void *port)
{
    uint8_t pwm_port = *(uint8_t *)port;
    if (pwm_status[pwm_port] & pwm_status_start) {
        if (pwm_port == 2) {
            pwm_rgb_para[pwm_port].rgb_port = pwm_port;
            hal_gpt_sw_start_timer_ms(pwm_rgb_handle, 16, pwm_rgb_isr, &(pwm_rgb_para[pwm_port].rgb_port));
        }
        uint8_t led_num = pwm_rgb_para[pwm_port].rgb_gpio_setting[0];
        pwm_rgb_config_t *led_rgb;
        if (led_num != 0) {
            uint8_t led_count = pwm_rgb_para[pwm_port].rgb_total_num_count % led_num;
            hal_gpio_set_output((pwm_rgb_para[pwm_port].rgb_gpio_setting[pwm_rgb_para[pwm_port].close_port] & 0x7F), !((pwm_rgb_para[pwm_port].rgb_gpio_setting[pwm_rgb_para[pwm_port].close_port] >> 7) & 0x1));
            led_rgb = (pwm_rgb_config_t *)(pwm_rgb_para[pwm_port].pwm_rgb_entry + led_count * sizeof(pwm_rgb_config_t));
            hal_gpio_set_output((pwm_rgb_para[pwm_port].rgb_gpio_setting[pwm_rgb_para[pwm_port].open_port] & 0x7F), ((pwm_rgb_para[pwm_port].rgb_gpio_setting[pwm_rgb_para[pwm_port].open_port] >> 7) & 0x1));
            INCREMENT_CYCLIC(pwm_rgb_para[pwm_port].close_port, led_num, 1);   //add self
            INCREMENT_CYCLIC(pwm_rgb_para[pwm_port].open_port, led_num, 1);
            INCREMENT_CYCLIC(pwm_rgb_para[pwm_port].rgb_total_num_count, (led_num - 1), 0);
        } else {
            led_rgb = (pwm_rgb_config_t *)pwm_rgb_para[pwm_port].pwm_rgb_entry;
        }
        // log_pwm_error("[PWM_RGB]pwm_rgb_isr, port:%d led:%d\r\n", 2, pwm_port, led_num);
        pwm_rgb_handle_config(pwm_port, led_rgb);
    }
}

hal_pwm_status_t    hal_pwm_rgb_init(hal_pwm_port_t pwm_port, uint8_t led, uint8_t rgb_frequency, uint8_t *gpio_setting, uint8_t *rgb_channel_setting)
{
    uint32_t save_mask;
    uint8_t tick_num = 2;
    if ((pwm_used_status[pwm_port] != pwm_used_none) && (pwm_used_status[pwm_port] != pwm_used_rgb)) {
        log_pwm_error("[PWM_RGB]pwm rgb init, port:%d led:%d already used status %x \r\n", 3, pwm_port, led, pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    if ((pwm_status[pwm_port] & pwm_status_init) != pwm_status_init) {
        uint8_t led_num = gpio_setting[0];
        if ((led != 0 && led_num == 0) || (led >= led_num && led_num != 0)) {
            log_pwm_error("[PWM_RGB]pwm rgb init, led parameter is failed,port:%d led:%d is over total led:%d\r\n", 3, pwm_port, led, led_num);
            hal_nvic_restore_interrupt_mask(save_mask);
            return HAL_PWM_STATUS_INVALID_PARAMETER;
        }
        pwm_rgb_para[pwm_port].close_port = led_num;
        pwm_rgb_para[pwm_port].open_port = 1;
        pwm_rgb_para[pwm_port].rgb_gpio_setting = gpio_setting;
        uint16_t num = (led_num == 0) ? 1 : led_num;
        pwm_rgb_para[pwm_port].pwm_rgb_entry = k_malloc(sizeof(pwm_rgb_config_t) * num);
        if (pwm_rgb_para[pwm_port].pwm_rgb_entry == NULL) {
            hal_nvic_restore_interrupt_mask(save_mask);
            log_pwm_error("[PWM_RGB]pwm rgb init,malloc is failed,port:%d led:%d is over total led:%d\r\n", 3, pwm_port, led, led_num);
            return HAL_PWM_STATUS_ERROR;
        }
        memset(pwm_rgb_para[pwm_port].pwm_rgb_entry, 0x0, sizeof(pwm_rgb_config_t)*num);
        pwm_rgb_para[pwm_port].rgb_one_period_ms = (uint16_t)(1000 / rgb_frequency);
        pwm_used_status[pwm_port] = pwm_used_rgb;
        pwm_status[pwm_port] |= pwm_status_init;
        if (pwm_port <= 1) {       // pwm dma isr
            pwm_rgb_para[pwm_port].rgb_one_period_count = (uint16_t)(1000000 / rgb_frequency / num / tick_num); //calc one period count
            pwm_rgb_para[pwm_port].rgb_port = pwm_port;
            pwm_dma_port_init(pwm_port, tick_num);
            pwm_dma_port_register_callback(pwm_port, pwm_rgb_isr, &(pwm_rgb_para[pwm_port].rgb_port));
        } else {
            pwm_led_rgb_init(8);
            pwm_led_rgb_init(9);
            pwm_led_rgb_init(10);
            pwm_rgb_para[pwm_port].rgb_one_period_count = 255;
        }
        if (led_num != 0) {
            for (int i = 0; i < led_num; i++) {
                hal_gpio_set_output((pwm_rgb_para[pwm_port].rgb_gpio_setting[i + 1] & 0x7F), !((pwm_rgb_para[pwm_port].rgb_gpio_setting[i + 1] >> 7) & 0x1));    //set gpio control close
            }
        }
    }
    // log_pwm_error("[PWM_RGB]pwm port:%d rgb init,rgb_one_period_ms:%d rgb_one_period_count:%d freq:%d\r\n", 4,pwm_port, pwm_rgb_para[pwm_port].rgb_one_period_ms, pwm_rgb_para[pwm_port].rgb_one_period_count, rgb_frequency);
    pwm_rgb_config_t *led_rgb = (pwm_rgb_config_t *)(pwm_rgb_para[pwm_port].pwm_rgb_entry + led * sizeof(pwm_rgb_config_t));
    if ((led_rgb->status & pwm_status_init) == pwm_status_init) {
        hal_nvic_restore_interrupt_mask(save_mask);
        log_pwm_error("[PWM_RGB]pwm rgb init, port:%d led:%d already init,status %x\r\n", 3, pwm_port, led, led_rgb->status);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    led_rgb->status = pwm_status_init;
    led_rgb->rgb_channel_setting = rgb_channel_setting;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    hal_pwm_rgb_deinit(hal_pwm_port_t pwm_port, uint8_t led)
{

    uint32_t save_mask;
    if (((pwm_status[pwm_port] & pwm_status_init) != pwm_status_init) || (pwm_used_status[pwm_port] != pwm_used_rgb)) {
        log_pwm_error("[PWM_RGB]pwm rgb deinit failed, port:%d led:%d is not init or is not used rgb, status:%x, used_status:%x \r\n", 4, pwm_port, led, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_NOT_INIT;
    }
    pwm_rgb_config_t *led_rgb = (pwm_rgb_config_t *)(pwm_rgb_para[pwm_port].pwm_rgb_entry + led * sizeof(pwm_rgb_config_t));
    if (((led_rgb->status & pwm_status_start) == pwm_status_start) || ((led_rgb->status & pwm_status_init) != pwm_status_init)) {
        log_pwm_error("[PWM_RGB]pwm rgb deinit failed, port:%d led:%d is not init or is running, status:%x\r\n", 3, pwm_port, led, led_rgb->status);
        return HAL_PWM_STATUS_NOT_INIT;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    led_rgb->status  = 0;
    if ((led_rgb->mode == rgb_breath) || (led_rgb->mode == rgb_flash) || (led_rgb->mode == rgb_flash_v2)) {
        k_free(led_rgb->user_data);
        k_free(led_rgb->bk_user_data);
        led_rgb->user_data = 0x0;
        led_rgb->bk_user_data = 0x0;
    } else if (led_rgb->mode == rgb_real_time) {
#ifdef RGB_REAL_TIME_FIFO
        while (!k_queue_is_empty((struct k_queue *) & (led_rgb->real_time))) {
            rgb_real_time_config_t *entry = k_queue_get((struct k_queue *) & (led_rgb->real_time), K_NO_WAIT);
            k_free(entry);
        }
        k_free(led_rgb->bk_user_data);
        led_rgb->user_data = 0x0;
        led_rgb->bk_user_data = 0x0;
#endif
    }

    if ((pwm_status[pwm_port] & pwm_status_start) == pwm_status_start) {
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_PWM_STATUS_OTHER_IS_RUN;
    }
    k_free(pwm_rgb_para[pwm_port].pwm_rgb_entry);
    memset(&(pwm_rgb_para[pwm_port]), 0x0, sizeof(pwm_rgb_para_t));
    pwm_used_status[pwm_port] = pwm_used_none;
    pwm_status[pwm_port] = 0;
    hal_nvic_restore_interrupt_mask(save_mask);
    if (pwm_port <= 1) {
        pwm_dma_port_deinit(pwm_port);
    } else {
        pwm_led_rgb_deinit(8);
        pwm_led_rgb_deinit(9);
        pwm_led_rgb_deinit(10);
        hal_gpt_sw_free_timer(pwm_rgb_handle);
    }
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t hal_pwm_rgb_breath_config(hal_pwm_port_t pwm_port, uint8_t led, hal_pwm_led_config_flex_ext_t *rgb_r, hal_pwm_led_config_flex_ext_t *rgb_g, hal_pwm_led_config_flex_ext_t *rgb_b)
{
    uint32_t mask;
    if ((pwm_used_status[pwm_port] != pwm_used_rgb) && (pwm_status[pwm_port] != pwm_status_init)) {
        log_pwm_error("[PWM_RGB]pwm rgb breath config failed, port:%d led:%d is not init or is not used rgb, status:%x, used_status:%x \r\n", 4, pwm_port, led, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    pwm_rgb_config_t *led_rgb = (pwm_rgb_config_t *)(pwm_rgb_para[pwm_port].pwm_rgb_entry + led * sizeof(pwm_rgb_config_t));
    if (((led_rgb->status & pwm_status_init) != pwm_status_init) || (led_rgb->mode != 0 && led_rgb->mode != rgb_real_time)) {
        log_pwm_error("[PWM_RGB]pwm rgb breath status failed, port:%d led:%d status:%x, used_status:%x \r\n", 4, pwm_port, led, led_rgb->status, led_rgb->mode);
        return HAL_PWM_STATUS_ERROR;
    }
    if ((led_rgb->status & pwm_status_config) != pwm_status_config) {
        led_rgb->user_data = k_malloc(sizeof(pwm_rgb_led_config_t) * 3);
        if (led_rgb->user_data == 0x0) {
            // hal_nvic_restore_interrupt_mask(mask);
            return HAL_PWM_STATUS_ERROR;
        }
        led_rgb->bk_user_data = k_malloc(sizeof(pwm_led_config_bk_t) * 3);
        if (led_rgb->bk_user_data == 0x0) {
            k_free(led_rgb->user_data);
            // hal_nvic_restore_interrupt_mask(mask);
            return HAL_PWM_STATUS_ERROR;
        }
        hal_nvic_save_and_set_interrupt_mask(&mask);
        led_rgb->status |= pwm_status_config;
        led_rgb->mode = rgb_breath;
        hal_nvic_restore_interrupt_mask(mask);
    }
    memset(led_rgb->user_data, 0xFF, sizeof(pwm_rgb_led_config_t) * 3);
    memset(led_rgb->bk_user_data, 0, sizeof(pwm_led_config_bk_t) * 3);
    pwm_rgb_led_config_t *rgb_r_config = (pwm_rgb_led_config_t *)led_rgb->user_data;
    pwm_rgb_led_config_t *rgb_g_config = (pwm_rgb_led_config_t *)(led_rgb->user_data + sizeof(pwm_rgb_led_config_t));
    pwm_rgb_led_config_t *rgb_b_config = (pwm_rgb_led_config_t *)(led_rgb->user_data + sizeof(pwm_rgb_led_config_t) * 2);
    if (rgb_r != NULL) {
        led_config_convert(&(rgb_r_config->led_config), rgb_r, pwm_rgb_para[pwm_port].rgb_one_period_ms);
        rgb_r_config->status = pwm_status_config;
    }
    if (rgb_g != NULL) {
        led_config_convert(&(rgb_g_config->led_config), rgb_g, pwm_rgb_para[pwm_port].rgb_one_period_ms);
        rgb_g_config->status = pwm_status_config;
    }
    if (rgb_b != NULL) {
        led_config_convert(&(rgb_b_config->led_config), rgb_b, pwm_rgb_para[pwm_port].rgb_one_period_ms);
        rgb_b_config->status = pwm_status_config;
    }
    hal_nvic_save_and_set_interrupt_mask(&mask);
    pwm_status[pwm_port] |= pwm_status_config;
    hal_nvic_restore_interrupt_mask(mask);
    return HAL_PWM_STATUS_OK;
}

#ifdef RGB_REAL_TIME_FIFO
int hal_pwm_rgb_real_time_config(hal_pwm_port_t pwm_port, uint8_t led, uint8_t *rgb_r, uint8_t *rgb_g, uint8_t *rgb_b)
{
    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    if ((pwm_used_status[pwm_port] != pwm_used_rgb) && (pwm_status[pwm_port] != pwm_status_init)) {
        hal_nvic_restore_interrupt_mask(mask);
        log_pwm_error("[PWM_RGB]pwm rgb realtime config failed, port:%d led:%d is not init or is not used rgb, status:%x, used_status:%x \r\n", 4, pwm_port, led, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    pwm_rgb_config_t *led_rgb = (pwm_rgb_config_t *)(pwm_rgb_para[pwm_port].pwm_rgb_entry + led * sizeof(pwm_rgb_config_t));
    if (((led_rgb->status & pwm_status_init) != pwm_status_init) || (led_rgb->mode != 0 && led_rgb->mode != rgb_real_time)) {
        hal_nvic_restore_interrupt_mask(mask);
        log_pwm_error("[PWM_RGB]pwm rgb realtime status failed, port:%d led:%d status:%x, used_status:%x \r\n", 4, pwm_port, led, led_rgb->status, led_rgb->mode);
        return HAL_PWM_STATUS_ERROR;
    }
    if ((led_rgb->status & pwm_status_config) != pwm_status_config) {
        led_rgb->bk_user_data = k_malloc(1);
        if (led_rgb->bk_user_data == 0x0) {
            hal_nvic_restore_interrupt_mask(mask);
            log_pwm_error("[PWM_RGB]pwm rgb realtime malloc failed_1, port:%d led:%d status:%x, used_status:%x \r\n", 4, pwm_port, led, led_rgb->status, led_rgb->mode);
            return HAL_PWM_STATUS_ERROR;
        }
        k_queue_init((struct k_queue *) & (led_rgb->real_time));
        led_rgb->status |= pwm_status_config;
        led_rgb->mode = rgb_real_time;
        memset(led_rgb->bk_user_data, 0, 1);   // bk_user_data for count
    }
    // log_pwm_error("[PWM_RGB]pwm rgb realtime debug, port:%d led:%d status:%x, mode:%x, bk_user_data:%d\r\n", 5, pwm_port, led, led_rgb->status, led_rgb->mode,*(led_rgb->bk_user_data) );
    // log_pwm_error("[PWM_RGB]hal_pwm_rgb_real_time_config, port:%d led:%d rgb_r:%x, rgb_g:%x, rgb_b:%d\r\n", 5, pwm_port, led, *rgb_r, *rgb_g,*rgb_b );
    rgb_real_time_config_t *entry = k_malloc(sizeof(rgb_real_time_config_t));
    if (entry == NULL) {
        hal_nvic_restore_interrupt_mask(mask);
        log_pwm_error("[PWM_RGB]pwm rgb realtime malloc failed_2, port:%d led:%d status:%x, used_status:%x \r\n", 4, pwm_port, led, led_rgb->status, led_rgb->mode);
        return HAL_PWM_STATUS_ERROR;
    }
    entry->rgb_r = *rgb_r;
    entry->rgb_g = *rgb_g;
    entry->rgb_b = *rgb_b;
    k_queue_append((struct k_queue *) & (led_rgb->real_time), entry);
    pwm_status[pwm_port] |= pwm_status_config;
    (*(led_rgb->bk_user_data))++;
    hal_nvic_restore_interrupt_mask(mask);
    return (*(led_rgb->bk_user_data));
}
#endif

#ifdef RGB_REAL_TIME_ACK
hal_pwm_status_t hal_pwm_rgb_real_time_config(hal_pwm_port_t pwm_port, uint8_t led, uint8_t *rgb_r, uint8_t *rgb_g, uint8_t *rgb_b)
{
    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    if ((pwm_used_status[pwm_port] != pwm_used_rgb) && (pwm_status[pwm_port] != pwm_status_init)) {
        hal_nvic_restore_interrupt_mask(mask);
        log_pwm_error("[PWM_RGB]pwm rgb realtime config failed, port:%d led:%d is not init or is not used rgb, status:%x, used_status:%x \r\n", 4, pwm_port, led, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    pwm_rgb_config_t *led_rgb = (pwm_rgb_config_t *)(pwm_rgb_para[pwm_port].pwm_rgb_entry + led * sizeof(pwm_rgb_config_t));
    if (((led_rgb->status & pwm_status_init) != pwm_status_init) || (led_rgb->mode != 0 && led_rgb->mode != rgb_real_time)) {
        hal_nvic_restore_interrupt_mask(mask);
        log_pwm_error("[PWM_RGB]pwm rgb realtime status failed, port:%d led:%d status:%x, used_status:%x \r\n", 4, pwm_port, led, led_rgb->status, led_rgb->mode);
        return HAL_PWM_STATUS_ERROR;
    }
    if ((led_rgb->status & pwm_status_config) != pwm_status_config) {
        led_rgb->status |= pwm_status_config;
        led_rgb->mode = rgb_real_time;
    }

    led_rgb->real_time.rgb_r = *rgb_r;
    led_rgb->real_time.rgb_g = *rgb_g;
    led_rgb->real_time.rgb_b = *rgb_b;
    pwm_status[pwm_port] |= pwm_status_config;
    hal_nvic_restore_interrupt_mask(mask);
    // log_pwm_error("[PWM_RGB]hal_pwm_rgb_real_time_config RGB_REAL_TIME_ACK, port:%d led:%d, status:%x, used_status:%x \r\n", 2, pwm_port, led, pwm_status[pwm_port], pwm_used_status[pwm_port]);
    return HAL_PWM_STATUS_OK;
}
#endif

hal_pwm_status_t hal_pwm_rgb_flash_config(hal_pwm_port_t pwm_port, uint8_t led, uint8_t *rgb_r, uint8_t *rgb_g, uint8_t *rgb_b, uint16_t size, uint8_t repeat)
{
    uint32_t mask;
    if ((pwm_used_status[pwm_port] != pwm_used_rgb) && (pwm_status[pwm_port] != pwm_status_init)) {
        log_pwm_error("[PWM_RGB]pwm rgb flash config failed, port:%d led:%d is not init or is not used rgb, status:%x, used_status:%x \r\n", 4, pwm_port, led, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    pwm_rgb_config_t *led_rgb = (pwm_rgb_config_t *)(pwm_rgb_para[pwm_port].pwm_rgb_entry + led * sizeof(pwm_rgb_config_t));
    if (((led_rgb->status & pwm_status_init) != pwm_status_init) || (led_rgb->mode != 0 && led_rgb->mode != rgb_flash)) {
        log_pwm_error("[PWM_RGB]pwm rgb flash status failed, port:%d led:%d status:%x, used_status:%x \r\n", 4, pwm_port, led, led_rgb->status, led_rgb->mode);
        return HAL_PWM_STATUS_ERROR;
    }
    if ((led_rgb->status & pwm_status_config) != pwm_status_config) {
        led_rgb->user_data = (uint8_t *)k_malloc(sizeof(rgb_flash_config_t));
        if (led_rgb->user_data == 0x0) {
            // hal_nvic_restore_interrupt_mask(mask);
            log_pwm_error("[PWM_RGB]pwm rgb flash malloc failed_1, port:%d led:%d status:%x, used_status:%x \r\n", 4, pwm_port, led, led_rgb->status, led_rgb->mode);
            return HAL_PWM_STATUS_ERROR;
        }
        led_rgb->bk_user_data = k_malloc(2);
        if (led_rgb->bk_user_data == 0x0) {
            k_free(led_rgb->user_data);
            // hal_nvic_restore_interrupt_mask(mask);
            log_pwm_error("[PWM_RGB]pwm rgb flash malloc failed_2, port:%d led:%d status:%x, used_status:%x \r\n", 4, pwm_port, led, led_rgb->status, led_rgb->mode);
            return HAL_PWM_STATUS_ERROR;
        }
        memset(led_rgb->bk_user_data, 0, 2);   // bk_user_data for count
        hal_nvic_save_and_set_interrupt_mask(&mask);
        led_rgb->status |= pwm_status_config;
        led_rgb->mode = rgb_flash;
        hal_nvic_restore_interrupt_mask(mask);
    }
    rgb_flash_config_t *rgb_config;
    rgb_config = (rgb_flash_config_t *)led_rgb->user_data;
    rgb_config->rgb_r = rgb_r;
    rgb_config->rgb_g = rgb_g;
    rgb_config->rgb_b = rgb_b;
    rgb_config->size = size;
    rgb_config->repeat_count = repeat;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    pwm_status[pwm_port] |= pwm_status_config;
    hal_nvic_restore_interrupt_mask(mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t hal_pwm_rgb_flash_config_v2(hal_pwm_port_t pwm_port, uint8_t led, uint8_t *rgb, uint16_t size, uint8_t repeat)
{
    uint32_t mask;
    if ((pwm_used_status[pwm_port] != pwm_used_rgb) && (pwm_status[pwm_port] != pwm_status_init)) {
        log_pwm_error("[PWM_RGB]pwm rgb flash_v2 config failed, port:%d led:%d is not init or is not used rgb, status:%x, used_status:%x \r\n", 4, pwm_port, led, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    pwm_rgb_config_t *led_rgb = (pwm_rgb_config_t *)(pwm_rgb_para[pwm_port].pwm_rgb_entry + led * sizeof(pwm_rgb_config_t));
    if (((led_rgb->status & pwm_status_init) != pwm_status_init) || (led_rgb->mode != 0 && led_rgb->mode != rgb_flash)) {
        log_pwm_error("[PWM_RGB]pwm rgb flash_v2 status failed, port:%d led:%d status:%x, used_status:%x \r\n", 4, pwm_port, led, led_rgb->status, led_rgb->mode);
        return HAL_PWM_STATUS_ERROR;
    }
    if ((led_rgb->status & pwm_status_config) != pwm_status_config) {
        led_rgb->user_data = (uint8_t *)k_malloc(sizeof(rgb_flash_config_v2_t));
        if (led_rgb->user_data == 0x0) {
            // hal_nvic_restore_interrupt_mask(mask);
            log_pwm_error("[PWM_RGB]pwm rgb flash_v2 malloc failed_1, port:%d led:%d status:%x, used_status:%x \r\n", 4, pwm_port, led, led_rgb->status, led_rgb->mode);
            return HAL_PWM_STATUS_ERROR;
        }
        led_rgb->bk_user_data = k_malloc(2);
        if (led_rgb->bk_user_data == 0x0) {
            k_free(led_rgb->user_data);
            // hal_nvic_restore_interrupt_mask(mask);
            log_pwm_error("[PWM_RGB]pwm rgb flash_v2 malloc failed_2, port:%d led:%d status:%x, used_status:%x \r\n", 4, pwm_port, led, led_rgb->status, led_rgb->mode);
            return HAL_PWM_STATUS_ERROR;
        }
        memset(led_rgb->bk_user_data, 0, 2);   // bk_user_data for count
        hal_nvic_save_and_set_interrupt_mask(&mask);
        led_rgb->status |= pwm_status_config;
        led_rgb->mode = rgb_flash_v2;
        hal_nvic_restore_interrupt_mask(mask);
    }
    rgb_flash_config_v2_t *rgb_config;
    rgb_config = (rgb_flash_config_v2_t *)led_rgb->user_data;
    rgb_config->rgb = rgb;
    rgb_config->size = size;
    rgb_config->repeat_count = repeat;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    pwm_status[pwm_port] |= pwm_status_config;
    hal_nvic_restore_interrupt_mask(mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t hal_pwm_rgb_flash_advance_config(hal_pwm_port_t pwm_port, uint8_t led, rgb_flash_type_t type, uint8_t irq_left_size, uint8_t *rgb, uint16_t size)
{
    uint32_t mask;
    if ((pwm_used_status[pwm_port] != pwm_used_rgb) && (pwm_status[pwm_port] != pwm_status_init)) {
        log_pwm_error("[PWM_RGB]pwm rgb flash advance config failed, port:%d led:%d is not init or is not used rgb, status:%x, used_status:%x \r\n", 4, pwm_port, led, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    pwm_rgb_config_t *led_rgb = (pwm_rgb_config_t *)(pwm_rgb_para[pwm_port].pwm_rgb_entry + led * sizeof(pwm_rgb_config_t));
    if (((led_rgb->status & pwm_status_config) != pwm_status_config) || (led_rgb->mode != 0 && led_rgb->mode != rgb_flash_v2)) {
        log_pwm_error("[PWM_RGB]pwm rgb flash advance status failed, port:%d led:%d status:%x, used_status:%x \r\n", 4, pwm_port, led, led_rgb->status, led_rgb->mode);
        return HAL_PWM_STATUS_ERROR;
    }
    rgb_flash_config_v2_t *rgb_config;
    rgb_config = (rgb_flash_config_v2_t *)led_rgb->user_data;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    if (type == rgb_flash_left_size) {
        rgb_config->irq_left_size = irq_left_size;
    } else {
        rgb_config->rgb = rgb;
        rgb_config->size = size;
        memset(led_rgb->bk_user_data, 0, 2);   // bk_user_data for count
    }
    hal_nvic_restore_interrupt_mask(mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    hal_pwm_rgb_start(hal_pwm_port_t pwm_port, uint8_t led)
{
    // log_pwm_error("[PWM_RGB]pwm rgb start, port:%d led:%d  used status:0x%x current status:0x%x\r\n", 4, pwm_port, led, pwm_used_status[pwm_port], pwm_status[pwm_port]);
    uint32_t save_mask;
    if ((pwm_used_status[pwm_port] != pwm_used_rgb) || ((pwm_status[pwm_port] & pwm_status_config) != pwm_status_config)) {
        log_pwm_error("[PWM_RGB]pwm rgb start failed, port:%d led:%d  used status:0x%x current status:0x%x\r\n", 4, pwm_port, led, pwm_used_status[pwm_port], pwm_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    pwm_rgb_config_t *led_rgb;
    led_rgb = (pwm_rgb_config_t *)(pwm_rgb_para[pwm_port].pwm_rgb_entry + led * sizeof(pwm_rgb_config_t));
    if (((led_rgb->status  & pwm_status_config) != pwm_status_config) || ((led_rgb->status & pwm_status_start) == pwm_status_start)) {
        log_pwm_error("[PWM_RGB]pwm rgb start failed, port:%d led:%d status:0x%x \r\n", 3, pwm_port, led, led_rgb->status);
        return HAL_PWM_STATUS_ERROR;
    }
    if ((pwm_status[pwm_port] & pwm_status_start) == pwm_status_start) {
        led_rgb->status |= pwm_status_start;
        return HAL_PWM_STATUS_OTHER_IS_RUN;
    }
#ifdef RGB_REAL_TIME_ACK
    log_pwm_error("[PWM_RGB]pwm rgb start begin, port:%d, rgb_r:%x , rgb_g:%x ,rgb_b:%x ,rgb_one_period_count:%x",5,pwm_port, led_rgb->real_time.rgb_r, led_rgb->real_time.rgb_g, led_rgb->real_time.rgb_b, pwm_rgb_para[pwm_port].rgb_one_period_count);
    rgb_duty_covert_count(pwm_port, *(led_rgb->rgb_channel_setting + 0), led_rgb->real_time.rgb_r, pwm_rgb_para[pwm_port].rgb_one_period_count);
    rgb_duty_covert_count(pwm_port, *(led_rgb->rgb_channel_setting + 1), led_rgb->real_time.rgb_g, pwm_rgb_para[pwm_port].rgb_one_period_count);
    rgb_duty_covert_count(pwm_port, *(led_rgb->rgb_channel_setting + 2), led_rgb->real_time.rgb_b, pwm_rgb_para[pwm_port].rgb_one_period_count);
#endif
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    led_rgb->status |= pwm_status_start;
    pwm_status[pwm_port] |= pwm_status_start;
    if (pwm_port <= 1) {       // pwm dma isr
        uint8_t calc_num = 6 - (*(led_rgb->rgb_channel_setting + 0) + * (led_rgb->rgb_channel_setting + 1) + * (led_rgb->rgb_channel_setting + 2));
        pwm_dma_led_rgb_port_start(pwm_port, pwm_rgb_para[pwm_port].rgb_one_period_count - 1, calc_num);
    }
    if (pwm_port == 2) {      // pwm isr
        pwm_rgb_para[pwm_port].rgb_port = pwm_port;
        hal_gpt_sw_get_timer(&pwm_rgb_handle);
        hal_gpt_sw_start_timer_ms(pwm_rgb_handle, pwm_rgb_para[pwm_port].rgb_one_period_ms, pwm_rgb_isr, &(pwm_rgb_para[pwm_port].rgb_port));
        pwm_led_rgb_start(8);
        pwm_led_rgb_start(9);
        pwm_led_rgb_start(10);
    }
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    hal_pwm_rgb_start_for_ack(hal_pwm_port_t pwm_port, uint8_t led)
{
    uint32_t save_mask;
    if ((pwm_used_status[pwm_port] != pwm_used_rgb) || ((pwm_status[pwm_port] & pwm_status_config) != pwm_status_config)) {
        log_pwm_error("[PWM_RGB]pwm rgb start failed, port:%d led:%d  used status:0x%x current status:0x%x\r\n", 4, pwm_port, led, pwm_used_status[pwm_port], pwm_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    pwm_rgb_config_t *led_rgb;
    led_rgb = (pwm_rgb_config_t *)(pwm_rgb_para[pwm_port].pwm_rgb_entry + led * sizeof(pwm_rgb_config_t));
    if (((led_rgb->status  & pwm_status_config) != pwm_status_config) || ((led_rgb->status & pwm_status_start) == pwm_status_start)) {
        log_pwm_error("[PWM_RGB]pwm rgb start failed, port:%d led:%d status:0x%x \r\n", 3, pwm_port, led, led_rgb->status);
        return HAL_PWM_STATUS_ERROR;
    }
    if ((pwm_status[pwm_port] & pwm_status_start) == pwm_status_start) {
        led_rgb->status |= pwm_status_start;
        return HAL_PWM_STATUS_OTHER_IS_RUN;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    led_rgb->status |= pwm_status_start;
    pwm_status[pwm_port] |= pwm_status_start;
    if (pwm_port <= 1) {       // pwm dma isr
        uint8_t calc_num = 6 - (*(led_rgb->rgb_channel_setting + 0) + * (led_rgb->rgb_channel_setting + 1) + * (led_rgb->rgb_channel_setting + 2));
        pwm_dma_led_rgb_port_start(pwm_port, pwm_rgb_para[pwm_port].rgb_one_period_count - 1, calc_num);
    }
    if (pwm_port == 2) {      // pwm isr
        pwm_rgb_para[pwm_port].rgb_port = pwm_port;
        hal_gpt_sw_get_timer(&pwm_rgb_handle);
        hal_gpt_sw_start_timer_ms(pwm_rgb_handle, pwm_rgb_para[pwm_port].rgb_one_period_ms, pwm_rgb_isr, &(pwm_rgb_para[pwm_port].rgb_port));
        pwm_led_rgb_start(8);
        pwm_led_rgb_start(9);
        pwm_led_rgb_start(10);
    }
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    hal_pwm_rgb_stop(hal_pwm_port_t pwm_port, uint8_t led)
{
    uint32_t save_mask;
    if ((pwm_used_status[pwm_port] != pwm_used_rgb) || ((pwm_status[pwm_port] & pwm_status_start) != pwm_status_start)) {
        log_pwm_error("[PWM_RGB]pwm rgb stop failed, port:%d led:%d  used status:0x%x current status:0x%x\r\n", 4, pwm_port, led, pwm_used_status[pwm_port], pwm_status[pwm_port]);
        return HAL_PWM_STATUS_OK;
    }
    pwm_rgb_config_t *led_rgb = (pwm_rgb_config_t *)(pwm_rgb_para[pwm_port].pwm_rgb_entry + led * sizeof(pwm_rgb_config_t));
    if ((led_rgb->status & pwm_status_start) != pwm_status_start) {
        return HAL_PWM_STATUS_OK;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    led_rgb->status &= ~pwm_status_start;
    uint8_t led_num = pwm_rgb_para[pwm_port].rgb_gpio_setting[0];
    for (int i = 0; i < led_num; i++) { //check all rgb is stop
        if ((led_rgb->status & pwm_status_start) == pwm_status_start) {
            hal_nvic_restore_interrupt_mask(save_mask);
            return HAL_PWM_STATUS_OK;
        }
    }
    if (pwm_port <= 1) {
        uint8_t calc_num = 6 - (*(led_rgb->rgb_channel_setting + 0) + * (led_rgb->rgb_channel_setting + 1) + * (led_rgb->rgb_channel_setting + 2));
        pwm_dma_led_rgb_port_stop(pwm_port, pwm_rgb_para[pwm_port].rgb_one_period_count, calc_num);
    } else {
        hal_gpt_sw_stop_timer_ms(pwm_rgb_handle);
        pwm_led_rgb_stop(8);
        pwm_led_rgb_stop(9);
        pwm_led_rgb_stop(10);
    }
    pwm_status[pwm_port] &= ~pwm_status_start;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t hal_pwm_rgb_register_callback(hal_pwm_port_t pwm_port, uint8_t led, hal_pwm_rgb_callback_t callback, void *user_data)
{
    uint32_t save_mask;
    if ((pwm_used_status[pwm_port] != pwm_used_rgb) && (pwm_status[pwm_port] != pwm_status_init)) {
        log_pwm_error("[PWM_RGB]pwm rgb register callback failed, port:%d led:%d is not init or is not used rgb, status:%x, used_status:%x \r\n", 4, pwm_port, led, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    pwm_rgb_config_t *led_rgb = (pwm_rgb_config_t *)(pwm_rgb_para[pwm_port].pwm_rgb_entry + led * sizeof(pwm_rgb_config_t));
    if ((led_rgb->status & pwm_status_init) != pwm_status_init) {
        return HAL_PWM_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    led_rgb->rgb_info.call_back = callback;
    led_rgb->rgb_info.user_data = user_data;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    hal_pwm_rgb_mask(hal_pwm_port_t pwm_port, uint8_t led)
{
    uint32_t save_mask;
    if ((pwm_used_status[pwm_port] != pwm_used_rgb) && (pwm_status[pwm_port] != pwm_status_init)) {
        log_pwm_error("[PWM_RGB]pwm rgb mask failed, port:%d led:%d is not init or is not used rgb, status:%x, used_status:%x \r\n", 4, pwm_port, led, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    pwm_rgb_config_t *led_rgb = (pwm_rgb_config_t *)(pwm_rgb_para[pwm_port].pwm_rgb_entry + led * sizeof(pwm_rgb_config_t));
    if ((led_rgb->status & pwm_status_init) != pwm_status_init) {
        return HAL_PWM_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    led_rgb->status &= ~pwm_status_unmask;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

hal_pwm_status_t    hal_pwm_rgb_unmask(hal_pwm_port_t pwm_port, uint8_t led)
{
    uint32_t save_mask;
    if ((pwm_used_status[pwm_port] != pwm_used_rgb) && (pwm_status[pwm_port] != pwm_status_init)) {
        log_pwm_error("[PWM_RGB]pwm rgb unmask failed, port:%d led:%d is not init or is not used rgb, status:%x, used_status:%x \r\n", 4, pwm_port, led, pwm_status[pwm_port], pwm_used_status[pwm_port]);
        return HAL_PWM_STATUS_ERROR_CHANNEL;
    }
    pwm_rgb_config_t *led_rgb = (pwm_rgb_config_t *)(pwm_rgb_para[pwm_port].pwm_rgb_entry + led * sizeof(pwm_rgb_config_t));
    if ((led_rgb->status & pwm_status_init) != pwm_status_init) {
        return HAL_PWM_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    led_rgb->status |= pwm_status_unmask;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_PWM_STATUS_OK;
}

#endif // HAL_PWM_RGB_SUPPORTED


#endif //HAL_PWM_MODULE_ENABLED