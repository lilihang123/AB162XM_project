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

#ifndef __HAL_PWM_INTERNAL_V2_H__
#define __HAL_PWM_INTERNAL_V2_H__

#include "hal_pwm.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifdef HAL_PWM_DMA_MODULE_ENABLED

typedef struct {
    hal_pwm_callback_t call_back;
    void              *user_data;
} pwm_info_t;

hal_pwm_status_t    pwm_dma_port_init(hal_pwm_dma_port_t pwm_dma_port, uint8_t tick_num);
hal_pwm_status_t    pwm_dma_port_deinit(hal_pwm_dma_port_t pwm_dma_port);
hal_pwm_status_t    pwm_set_polarity_v2(hal_pwm_channel_t pwm_channel, bool polarity);

hal_pwm_status_t    pwm_dma_port_start(hal_pwm_dma_port_t pwm_dma_port);
hal_pwm_status_t    pwm_dma_port_stop(hal_pwm_dma_port_t pwm_dma_port);
hal_pwm_status_t    pwm_dma_by_channel_frequency(hal_pwm_channel_t pwm_channel, uint32_t frequency, uint32_t *total_count);
hal_pwm_status_t    pwm_dma_by_channel_duty_cycle(hal_pwm_channel_t pwm_channel, uint32_t duty_cycle);
hal_pwm_status_t    pwm_dma_by_channel_stop(hal_pwm_channel_t pwm_channel);
hal_pwm_status_t    pwm_dma_by_channel_get_frequency(hal_pwm_channel_t pwm_channel, uint32_t *frequency);
hal_pwm_status_t    pwm_dma_by_channel_get_duty_cycle(hal_pwm_channel_t pwm_channel, uint32_t *duty_cycle);
hal_pwm_status_t    pwm_dma_init(hal_pwm_dma_port_t pwm_dma_port, hal_pwm_source_clock_t source_clock);
hal_pwm_status_t    pwm_dma_deinit(hal_pwm_dma_port_t pwm_dma_port);
hal_pwm_status_t    pwm_dma_set_frequency(hal_pwm_dma_port_t pwm_dma_port, uint32_t frequency, uint32_t *total_count);
hal_pwm_status_t    pwm_dma_set_config(hal_pwm_dma_port_t pwm_dma_port, hal_pwm_dma_config *config);
hal_pwm_status_t    pwm_dma_register_callback(hal_pwm_dma_port_t pwm_dma_port, hal_pwm_irq_enable *irq_enable,hal_pwm_callback_t pwm_callback, void *user_data);
hal_pwm_status_t    pwm_dma_enqueue_BufA(hal_pwm_dma_port_t pwm_dma_port,uint32_t *bufaddr, uint16_t sample_cnt);
hal_pwm_status_t    pwm_dma_enqueue_BufB(hal_pwm_dma_port_t pwm_dma_port,uint32_t *bufaddr, uint16_t sample_cnt);
hal_pwm_status_t    pwm_dma_start(hal_pwm_dma_port_t pwm_dma_port);
hal_pwm_status_t    pwm_dma_stop(hal_pwm_dma_port_t pwm_dma_port);


#if defined(HAL_PWM_LED_SUPPORTED) || defined(HAL_PWM_RGB_SUPPORTED)
typedef void (*hal_pwm_dma_port_callback_t)(void *user_data);
typedef struct {
    hal_pwm_dma_port_callback_t call_back;
    void              *user_data;
} pwm_dma_port_info_t;

hal_pwm_status_t    pwm_dma_reset_default_reg(hal_pwm_dma_port_t pwm_dma_port);
void pwm_dma_led_rgb_set_duty_cycle(uint8_t channel,uint8_t duty,uint16_t total_count);
void pwm_dma_led_rgb_port_start(hal_pwm_dma_port_t pwm_dma_port, uint16_t total_count,uint8_t calc_num);
void pwm_dma_led_rgb_port_stop(hal_pwm_dma_port_t pwm_dma_port,uint16_t total_count,uint8_t calc_num);
void pwm_dma_port_register_callback(hal_pwm_dma_port_t pwm_dma_port,hal_pwm_dma_port_callback_t pwm_callback, void *user_data);
#endif
#endif
#ifdef __cplusplus
}
#endif

#endif