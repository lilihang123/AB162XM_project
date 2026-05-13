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

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hal.h"
#include "bsp_led.h"

int channel_polarity_test[LED_NUM_MAX];
static  uint8_t    led_init[LED_NUM_MAX];
void init_polarity(void){
    #ifdef DT_PATH_led_channel0
    #define CHANNEL0_NODE DT_PATH(led,channel0);
    channel_polarity_test[0] =  DT_PROP_OR(CHANNEL0_NODE, polarity,0);
    #endif
    #ifdef DT_PATH_led_channel1
    #define CHANNEL1_NODE DT_PATH(led,channel1);
    channel_polarity_test[1] =  DT_PROP_OR(CHANNEL1_NODE, polarity,0);
    #endif

    #ifdef DT_PATH_led_channel2
    #define CHANNEL2_NODE DT_PATH(led,channel2);
    channel_polarity_test[2] =  DT_PROP_OR(CHANNEL2_NODE, polarity,0);
    #endif

    #if DT_NODE_HAS_PROP(DT_NODELABEL(pwm_dma0),channel_polarity)
        channel_polarity_test[3] =  DT_PROP_BY_IDX(DT_NODELABEL(pwm_dma0), channel_polarity,0);
        channel_polarity_test[4] =  DT_PROP_BY_IDX(DT_NODELABEL(pwm_dma0), channel_polarity,1);
        channel_polarity_test[5] =  DT_PROP_BY_IDX(DT_NODELABEL(pwm_dma0), channel_polarity,2);
        channel_polarity_test[6] =  DT_PROP_BY_IDX(DT_NODELABEL(pwm_dma0), channel_polarity,3);
    #endif

    #if DT_NODE_HAS_PROP(DT_NODELABEL(pwm_dma1),channel_polarity)
        channel_polarity_test[7] =  DT_PROP_BY_IDX(DT_NODELABEL(pwm_dma1), channel_polarity,0);
        channel_polarity_test[8] =  DT_PROP_BY_IDX(DT_NODELABEL(pwm_dma1), channel_polarity,1);
        channel_polarity_test[9] =  DT_PROP_BY_IDX(DT_NODELABEL(pwm_dma1), channel_polarity,2);
        channel_polarity_test[10] = DT_PROP_BY_IDX(DT_NODELABEL(pwm_dma1), channel_polarity,3);
    #endif

    #if DT_NODE_HAS_PROP(DT_NODELABEL(pwm0),channel_polarity)
        channel_polarity_test[11] = DT_PROP(DT_NODELABEL(pwm0), channel_polarity);
    #endif
    #if DT_NODE_HAS_PROP(DT_NODELABEL(pwm1),channel_polarity)
        channel_polarity_test[12] = DT_PROP(DT_NODELABEL(pwm1), channel_polarity);

    #endif
    #if DT_NODE_HAS_PROP(DT_NODELABEL(pwm2),channel_polarity)
        channel_polarity_test[13] = DT_PROP(DT_NODELABEL(pwm2), channel_polarity);
    #endif
}

bsp_led_status_t bsp_led_enable(uint8_t led_num,one_led_style_t *cfg){
    int status = 0;
    uint32_t irq_status;
    hal_led_config_flex_ext_t led_cfg;
    led_cfg.config_ext.timing.t0 = cfg->t0;        /**< delay start time before led started */
    led_cfg.config_ext.timing.t1.t_rising = cfg->t1_rising;        /**< led on time in one twinkle cycle */
    led_cfg.config_ext.timing.t1.t_lightest = cfg->t1_lightest;        /**< led on time in one twinkle cycle */
    led_cfg.config_ext.timing.t2.t_falling = cfg->t2_falling;        /**< led off time in one twinkle cycle */
    led_cfg.config_ext.timing.t2.t_darkest = cfg->t2_darkest;        /**< led off time in one twinkle cycle */
    led_cfg.config_ext.timing.t3 = cfg->t3;        /**< led idle time after finish t1t2_repeat */
    led_cfg.config_ext.brightness = cfg->brightness;        /**< led idle time after finish t1t2_repeat */
    led_cfg.config_ext.blink_nums = cfg->repeat_t1t2;        /**< led idle time after finish t1t2_repeat */
    led_cfg.other_config.start_brightness = cfg->start_brightness;        /**< led on off(1:on,0:off) */
    led_cfg.other_config.end_brightness = cfg->end_brightness;        /**< led on off(1:on,0:off) */
    led_cfg.other_config.repeat_times = cfg->repeat_ext;   /**< extern loop repeat times */
    init_polarity();
    if(led_init[led_num]){
        return BSP_LED_STATUS_OK;
    }
    if(led_num < 3){
        status = hal_led_init(led_num);

        status |= hal_led_set_invert(led_num,!(channel_polarity_test[led_num]));

        status |= hal_led_configure_flex_ext(led_num,(hal_led_config_flex_ext_t *)&led_cfg);

        status |= hal_led_start(led_num);

        status |= hal_led_unmask(led_num);
    }
    else{
        uint8_t pwm_led_num = led_num -3;
        status = hal_pwm_led_init(pwm_led_num);

        status |= hal_pwm_led_set_polarity(pwm_led_num,channel_polarity_test[led_num]);

        status |= hal_pwm_led_config_ext(pwm_led_num,(hal_pwm_led_config_flex_ext_t *)&led_cfg);

        status |= hal_pwm_led_start(pwm_led_num);

        status |= hal_pwm_led_unmask(pwm_led_num);
    }
    if(status != 0){
        return BSP_LED_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    led_init[led_num] = true;
    hal_nvic_restore_interrupt_mask(irq_status);
    return BSP_LED_STATUS_OK;
}


bsp_led_status_t bsp_led_disable(uint8_t led_num){
    int status = 0;
    uint8_t data = 0;
    uint32_t irq_status;
    if(led_init[led_num] == false){
        return BSP_LED_STATUS_OK;
    }
    if(led_num < 3){
        status = hal_led_mask(led_num);
        if(status != 0){
            data = 1;
        }
        status |= hal_led_stop(led_num);
        if(status != 0){
            data |= 1<<1;
        }
        status |= hal_led_deinit(led_num);
        if(status != 0){
            data |= 1<<2;
        }
    }
    else{
        uint8_t pwm_led_num = led_num -3;
        status = hal_pwm_led_mask(pwm_led_num);
        status |= hal_pwm_led_stop(pwm_led_num);
        status |= hal_pwm_led_deinit(pwm_led_num);
    }
    if(status != 0){
        return BSP_LED_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    led_init[led_num] = false;
    hal_nvic_restore_interrupt_mask(irq_status);
    return BSP_LED_STATUS_OK;
}


bsp_led_status_t bsp_led_register_isr(uint8_t led_num,bsp_led_callback_t callback,void *user_data){
    int status = 0;
    if(led_num < 3){
        status = hal_led_register_callback(led_num, callback, user_data);
    }
    else{
        led_num = led_num -3;
        status =  hal_pwm_led_register_callback(led_num, callback, user_data);
    }
    if(status != 0)return BSP_LED_STATUS_ERROR;
    return BSP_LED_STATUS_OK;
}