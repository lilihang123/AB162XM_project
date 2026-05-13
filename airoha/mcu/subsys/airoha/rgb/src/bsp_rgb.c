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
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWRGBGES AND AGREES
 * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWRGBGES
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
#include "bsp_rgb.h"
#include "zephyr/kernel.h"
#include <zephyr/devicetree.h>
#include <zephyr/device.h>

uint8_t *gpio_setting[3];
uint8_t *rgb_channel_select[CONFIG_AIR_RGB_NUM];
static uint8_t rgb_init[CONFIG_AIR_RGB_NUM];
// rgb_para_t rgb_para[CONFIG_AIR_RGB_NUM];

rgb_para_t rgb_para[CONFIG_AIR_RGB_NUM];
#define HANDLE_CHILD(node_id) \
    do {  \
        uint8_t rgb_num= DT_PROP(node_id, reg);  \
        rgb_para[rgb_num].pwm_port = DT_PROP(DT_PARENT(node_id), port);  \
        rgb_para[rgb_num].rgb_frequency = DT_PROP(DT_PARENT(node_id), led_rgb_frequency);  \
        rgb_para[rgb_num].gpio_channel = DT_PROP(DT_PARENT(node_id), rgb_gpio_channel);  \
        rgb_para[rgb_num].rgb_port = DT_PROP(node_id, port);  \
        rgb_para[rgb_num].gpio_control = DT_PROP(node_id, gpio_control);  \
        rgb_para[rgb_num].gpio_polarity = DT_PROP(node_id, gpio_polarity);  \
        rgb_para[rgb_num].channel0_polarity = DT_PROP_BY_IDX(DT_PARENT(node_id), channel_polarity,0);  \
        rgb_para[rgb_num].channel1_polarity = DT_PROP_BY_IDX(DT_PARENT(node_id), channel_polarity,1);  \
        rgb_para[rgb_num].channel2_polarity = DT_PROP_BY_IDX(DT_PARENT(node_id), channel_polarity,2);  \
        rgb_para[rgb_num].channel3_polarity = DT_PROP_BY_IDX(DT_PARENT(node_id), channel_polarity,3);  \
        rgb_para[rgb_num].r_channel = DT_PROP(node_id, r_channel);  \
        rgb_para[rgb_num].g_channel = DT_PROP(node_id, g_channel);  \
        rgb_para[rgb_num].b_channel = DT_PROP(node_id, b_channel);  \
    } while(0);  \

#define HANDLE_CHILD_1(node_id) \
    do {  \
        uint8_t rgb_num= DT_PROP(node_id, reg);  \
        rgb_para[rgb_num].pwm_port = DT_PROP(DT_PARENT(node_id), port);  \
        rgb_para[rgb_num].rgb_frequency = DT_PROP(DT_PARENT(node_id), led_rgb_frequency);  \
        rgb_para[rgb_num].gpio_channel = DT_PROP(DT_PARENT(node_id), rgb_gpio_channel);  \
        rgb_para[rgb_num].rgb_port = DT_PROP(node_id, port);  \
        rgb_para[rgb_num].gpio_control = DT_PROP(node_id, gpio_control);  \
        rgb_para[rgb_num].gpio_polarity = DT_PROP(node_id, gpio_polarity);     \
        rgb_para[rgb_num].channel0_polarity = DT_PROP(DT_NODELABEL(pwm0), channel_polarity);  \
        rgb_para[rgb_num].channel1_polarity = DT_PROP(DT_NODELABEL(pwm1), channel_polarity);  \
        rgb_para[rgb_num].channel2_polarity = DT_PROP(DT_NODELABEL(pwm2), channel_polarity);  \
        rgb_para[rgb_num].r_channel = DT_PROP(node_id, r_channel);  \
        rgb_para[rgb_num].g_channel = DT_PROP(node_id, g_channel);  \
        rgb_para[rgb_num].b_channel = DT_PROP(node_id, b_channel);  \
    } while(0);  \


static bsp_rgb_status_t init_pwm_port_settings(uint8_t rgb_num)
{
    DT_FOREACH_CHILD(DT_NODELABEL(pwm_dma0), HANDLE_CHILD);
    DT_FOREACH_CHILD(DT_NODELABEL(pwm_dma1), HANDLE_CHILD);
    DT_FOREACH_CHILD(DT_NODELABEL(pwm0), HANDLE_CHILD_1);
    uint8_t pwm_port = rgb_para[rgb_num].pwm_port;
    uint8_t gpio_channel = rgb_para[rgb_num].gpio_channel;

    if (gpio_setting[pwm_port] == NULL) {
        gpio_setting[pwm_port] = k_malloc(gpio_channel + 1);
        if (gpio_setting[pwm_port] == NULL) {
            return BSP_RGB_STATUS_ERROR; // Memory allocation failed
        }
        rgb_channel_select[rgb_num] = k_malloc(3);    //malloc rgb channel select channle
        if (rgb_channel_select[rgb_num] == NULL) {
            k_free(gpio_setting[pwm_port]);
            return BSP_RGB_STATUS_ERROR; // Memory allocation failed
        }
        *(rgb_channel_select[rgb_num] + 0)  = rgb_para[rgb_num].r_channel;
        *(rgb_channel_select[rgb_num] + 1)  = rgb_para[rgb_num].g_channel;
        *(rgb_channel_select[rgb_num] + 2)  = rgb_para[rgb_num].b_channel;
        uint8_t *setting = gpio_setting[pwm_port];
        setting[0] = gpio_channel;
        for (int i = 0; i < gpio_channel; i++) {
            uint8_t num = (rgb_para[0].pwm_port == 0) ? (pwm_port * rgb_para[0].gpio_channel + i) : i;
            setting[i + 1] = rgb_para[num].gpio_control | (rgb_para[num].gpio_polarity << 7);
        }
    }
    hal_pwm_set_polarity(pwm_port * 4 + 0, rgb_para[rgb_num].channel0_polarity);
    hal_pwm_set_polarity(pwm_port * 4 + 1, rgb_para[rgb_num].channel1_polarity);
    hal_pwm_set_polarity(pwm_port * 4 + 2, rgb_para[rgb_num].channel2_polarity);
    if (pwm_port <= 1) {
        hal_pwm_set_polarity(pwm_port * 4 + 3, rgb_para[rgb_num].channel3_polarity);
    }
    return BSP_RGB_STATUS_OK;
}

static void init_rgb_breath_config(hal_pwm_led_config_flex_ext_t *dest_cfg, const rgb_one_led_style_t *src_cfg)
{
    if (src_cfg != NULL) {
        dest_cfg->config_ext.timing.t0 = src_cfg->t0;                  /**< delay start time before rgb started */
        dest_cfg->config_ext.timing.t1.t_rising = src_cfg->t1_rising; /**< rgb on time in one twinkle cycle */
        dest_cfg->config_ext.timing.t1.t_lightest = src_cfg->t1_lightest; /**< rgb on time in one twinkle cycle */
        dest_cfg->config_ext.timing.t2.t_falling = src_cfg->t2_falling; /**< rgb off time in one twinkle cycle */
        dest_cfg->config_ext.timing.t2.t_darkest = src_cfg->t2_darkest; /**< rgb off time in one twinkle cycle */
        dest_cfg->config_ext.timing.t3 = src_cfg->t3;                 /**< rgb idle time after finish t1t2_repeat */
        dest_cfg->config_ext.brightness = src_cfg->brightness;       /**< brightness level */
        dest_cfg->config_ext.blink_nums = src_cfg->repeat_t1t2;      /**< blink repetition count */
        dest_cfg->other_config.start_brightness = src_cfg->start_brightness; /**< starting brightness */
        dest_cfg->other_config.end_brightness = src_cfg->end_brightness;     /**< ending brightness */
        dest_cfg->other_config.repeat_times = src_cfg->repeat_ext;   /**< extern loop repeat times */
    }
}

bsp_rgb_status_t bsp_rgb_enable(uint8_t rgb_num, rgb_one_led_style_t *cfg_r, rgb_one_led_style_t *cfg_g, rgb_one_led_style_t *cfg_b)
{
    int status = 0;
    uint32_t irq_status;
    if (rgb_init[rgb_num] == true) {
        return BSP_RGB_STATUS_OK;
    }
    hal_pwm_led_config_flex_ext_t rgb_cfg_r;
    hal_pwm_led_config_flex_ext_t *rgb_cfg_r_ptr = NULL;
    if (cfg_r != NULL) {
        init_rgb_breath_config(&rgb_cfg_r, cfg_r);
        rgb_cfg_r_ptr = &rgb_cfg_r;
    }
    // Green configuration
    hal_pwm_led_config_flex_ext_t rgb_cfg_g;
    hal_pwm_led_config_flex_ext_t *rgb_cfg_g_ptr = NULL;
    if (cfg_g != NULL) {
        init_rgb_breath_config(&rgb_cfg_g, cfg_g);
        rgb_cfg_g_ptr = &rgb_cfg_g;
    }

    // Blue configuration
    hal_pwm_led_config_flex_ext_t rgb_cfg_b;
    hal_pwm_led_config_flex_ext_t *rgb_cfg_b_ptr = NULL;
    if (cfg_b != NULL) {
        init_rgb_breath_config(&rgb_cfg_b, cfg_b);
        rgb_cfg_b_ptr = &rgb_cfg_b;
    }

    status = init_pwm_port_settings(rgb_num);
    if (status != BSP_RGB_STATUS_OK) {
        return BSP_RGB_STATUS_ERROR;
    }
    uint8_t pwm_port =  rgb_para[rgb_num].pwm_port;
    uint8_t rgb_port =  rgb_para[rgb_num].rgb_port;
    uint8_t rgb_frequency = rgb_para[rgb_num].rgb_frequency;
    status = hal_pwm_rgb_init(pwm_port, rgb_port, rgb_frequency, gpio_setting[pwm_port], rgb_channel_select[rgb_num]);
    if (rgb_para[rgb_num].callback != NULL) {
        status |= hal_pwm_rgb_register_callback(pwm_port, rgb_port, rgb_para[rgb_num].callback, rgb_para[rgb_num].user_data);
    }
    status |= hal_pwm_rgb_breath_config(pwm_port, rgb_port, (hal_pwm_led_config_flex_ext_t *)rgb_cfg_r_ptr, (hal_pwm_led_config_flex_ext_t *)rgb_cfg_g_ptr, (hal_pwm_led_config_flex_ext_t *)rgb_cfg_b_ptr);

    status |= hal_pwm_rgb_start(pwm_port, rgb_port);
    status |= hal_pwm_rgb_unmask(pwm_port, rgb_port);
    if (status != 0) {
        return BSP_RGB_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    rgb_init[rgb_num] = true;
    hal_nvic_restore_interrupt_mask(irq_status);
    return BSP_RGB_STATUS_OK;
}


bsp_rgb_status_t bsp_rgb_realtime_enable(uint8_t rgb_num, uint8_t interval)
{

    int status = 0;
    uint32_t irq_status;
    uint8_t rgb_frequency = 0;
    if (rgb_init[rgb_num] == true) {
        return BSP_RGB_STATUS_OK;
    }
    status = init_pwm_port_settings(rgb_num);
    if (status != BSP_RGB_STATUS_OK) {
        return BSP_RGB_STATUS_ERROR;
    }
    uint8_t pwm_port =  rgb_para[rgb_num].pwm_port;
    uint8_t rgb_port =  rgb_para[rgb_num].rgb_port;
    if (interval == 0) {
        rgb_frequency = rgb_para[rgb_num].rgb_frequency;
    } else {
        rgb_frequency = (uint8_t)(1000 / interval);
    }
    status = hal_pwm_rgb_init(pwm_port, rgb_port, rgb_frequency, gpio_setting[pwm_port], rgb_channel_select[rgb_num]);
    if (rgb_para[rgb_num].callback != NULL) {
        status |= hal_pwm_rgb_register_callback(pwm_port, rgb_port, rgb_para[rgb_num].callback, rgb_para[rgb_num].user_data);
    }
    status |= hal_pwm_rgb_unmask(pwm_port, rgb_port);
    if (status < 0) {
        return BSP_RGB_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    rgb_init[rgb_num] = true;
    hal_nvic_restore_interrupt_mask(irq_status);
    return BSP_RGB_STATUS_OK;
}


#ifdef RGB_REAL_TIME_FIFO
int bsp_rgb_realtime_config(uint8_t rgb_num, uint8_t *cfg_r, uint8_t *cfg_g, uint8_t *cfg_b)
{
    uint8_t pwm_port =  rgb_para[rgb_num].pwm_port;
    uint8_t rgb_port =  rgb_para[rgb_num].rgb_port;
    int ret = hal_pwm_rgb_real_time_config(pwm_port, rgb_port, cfg_r, cfg_g, cfg_b);
    if (ret < 0) {
        return BSP_RGB_STATUS_ERROR;
    }
    return ret;
}
#endif

#ifdef RGB_REAL_TIME_ACK
bsp_rgb_status_t bsp_rgb_realtime_config(uint8_t rgb_num, uint8_t *cfg_r, uint8_t *cfg_g, uint8_t *cfg_b)
{
    uint8_t pwm_port =  rgb_para[rgb_num].pwm_port;
    uint8_t rgb_port =  rgb_para[rgb_num].rgb_port;
    int ret = hal_pwm_rgb_real_time_config(pwm_port, rgb_port, cfg_r, cfg_g, cfg_b);
    return ret;
}
#endif

bsp_rgb_status_t bsp_rgb_realtime_start(uint8_t rgb_num)
{
    int status = 0;
    uint8_t pwm_port =  rgb_para[rgb_num].pwm_port;
    uint8_t rgb_port =  rgb_para[rgb_num].rgb_port;
    status = hal_pwm_rgb_start(pwm_port, rgb_port);
    if (status != 0) {
        return BSP_RGB_STATUS_ERROR;
    }
    return BSP_RGB_STATUS_OK;
}


bsp_rgb_status_t bsp_rgb_flash_enable(uint8_t rgb_num, uint8_t *rgb, uint16_t interval, uint16_t size, uint8_t repeat)
{

    int status = 0;
    uint32_t irq_status;
    uint8_t rgb_frequency = 0;
    if (rgb_init[rgb_num] == true) {
        return BSP_RGB_STATUS_OK;
    }
    status = init_pwm_port_settings(rgb_num);
    if (status != BSP_RGB_STATUS_OK) {
        return BSP_RGB_STATUS_ERROR;
    }
    uint8_t pwm_port =  rgb_para[rgb_num].pwm_port;
    uint8_t rgb_port =  rgb_para[rgb_num].rgb_port;
    if (interval == 0) {
        rgb_frequency = rgb_para[rgb_num].rgb_frequency;
    } else {
        rgb_frequency = (uint8_t)(1000 / interval);
    }
    status = hal_pwm_rgb_init(pwm_port, rgb_port, rgb_frequency, gpio_setting[pwm_port], rgb_channel_select[rgb_num]);
    if (rgb_para[rgb_num].callback != NULL) {
        status |= hal_pwm_rgb_register_callback(pwm_port, rgb_port, rgb_para[rgb_num].callback, rgb_para[rgb_num].user_data);
    }
    status |= hal_pwm_rgb_flash_config_v2(pwm_port, rgb_port, rgb, size, repeat);
    status |= hal_pwm_rgb_start(pwm_port, rgb_port);
    status |= hal_pwm_rgb_unmask(pwm_port, rgb_port);
    if (status < 0) {
        return BSP_RGB_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    rgb_init[rgb_num] = true;
    hal_nvic_restore_interrupt_mask(irq_status);
    return BSP_RGB_STATUS_OK;
}

bsp_rgb_status_t bsp_rgb_flash_config_left_size(uint8_t rgb_num)
{
    uint8_t pwm_port =  rgb_para[rgb_num].pwm_port;
    uint8_t rgb_port =  rgb_para[rgb_num].rgb_port;
    return hal_pwm_rgb_flash_advance_config(pwm_port, rgb_port, rgb_flash_left_size, 3, NULL, 0);
}

bsp_rgb_status_t bsp_rgb_flash_continued_enable(uint8_t rgb_num, uint8_t *rgb, uint16_t size)
{
    uint8_t pwm_port =  rgb_para[rgb_num].pwm_port;
    uint8_t rgb_port =  rgb_para[rgb_num].rgb_port;
    return hal_pwm_rgb_flash_advance_config(pwm_port, rgb_port, rgb_flash_refresh, 0, rgb, size);
}

bsp_rgb_status_t bsp_rgb_disable(uint8_t rgb_num)
{
    int status = 0;
    uint32_t irq_status;
    if (rgb_init[rgb_num] == false) {
        return BSP_RGB_STATUS_OK;
    }
    uint8_t pwm_port =  rgb_para[rgb_num].pwm_port;
    uint8_t rgb_port =  rgb_para[rgb_num].rgb_port;
    status = hal_pwm_rgb_mask(pwm_port, rgb_port);
    status |= hal_pwm_rgb_stop(pwm_port, rgb_port);
    if (status != 0) {
        return BSP_RGB_STATUS_ERROR;
    }
    status = hal_pwm_rgb_deinit(pwm_port, rgb_port);
    if (status == HAL_PWM_STATUS_OK) {
        uint32_t save_mask;
        hal_nvic_save_and_set_interrupt_mask(&save_mask);
        k_free(gpio_setting[pwm_port]);
        gpio_setting[pwm_port] = NULL;
        k_free(rgb_channel_select[rgb_num]);
        rgb_channel_select[rgb_num] = NULL;
        hal_nvic_restore_interrupt_mask(save_mask);
    } else if (status == HAL_PWM_STATUS_OTHER_IS_RUN) {
        return BSP_RGB_STATUS_OK;
    } else {
        return BSP_RGB_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    rgb_init[rgb_num] = false;
    hal_nvic_restore_interrupt_mask(irq_status);
    return BSP_RGB_STATUS_OK;
}


bsp_rgb_status_t bsp_rgb_register_isr(uint8_t rgb_num, bsp_rgb_callback_t callback, void *user_data)
{
    uint32_t save_mask;
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    rgb_para[rgb_num].callback = callback;
    rgb_para[rgb_num].user_data = user_data;
    hal_nvic_restore_interrupt_mask(save_mask);
    return BSP_RGB_STATUS_OK;
}