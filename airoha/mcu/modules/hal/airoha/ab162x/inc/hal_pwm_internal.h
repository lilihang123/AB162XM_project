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

#ifndef __HAL_PWM_INTERNAL_H__
#define __HAL_PWM_INTERNAL_H__

#include "hal_pwm.h"
#include <zephyr/kernel.h>
#ifdef __cplusplus
extern "C" {
#endif

#if defined(HAL_PWM_LED_SUPPORTED) || defined(HAL_PWM_RGB_SUPPORTED)

/** @brief led timing config */
typedef struct {
    uint16_t  t0;                   /**<The led delay start time(unit ms)*/
    struct {
        uint16_t  t_rising;         /**<The led breath mode timing adjustment setting corresponding to the brightness level from darker to lighter(unit ms). */
        uint16_t  t_lightest;       /**<The duration time of the brightest level(unit ms). */
    }t1;
    struct {
        uint16_t  t_falling;        /**<The led breath mode timing adjustment setting corresponding to the brightness level from lighter to darker(unit ms). */
        uint16_t  t_darkest;        /**<The duration time of the darkest time(unit ms). */
    }t2;
    uint16_t  t3;                   /**<The led idle time for next ext-loop(unit ms). */
}hal_pwm_led_timing_config_t;

/** @brief led extend config */
typedef struct{
    hal_pwm_led_timing_config_t         timing;        /**< The timing of led. */
    uint8_t                                 brightness;    /**< The brightness of led. */
    uint8_t                                 blink_nums;    /**< The blink number of led(the period is t1 + t2). */
}hal_pwm_led_config_ext_t;

/** @brief led other config */
typedef struct {
    uint8_t start_brightness;                     /**< The start brightness of led. */
    uint8_t end_brightness;                       /**< The end brightness of led. */
    uint8_t repeat_times;                         /**< The total of led repeat time. */
}hal_pwm_led_other_config_t;


/** @brief led extend config */
typedef struct{
    hal_pwm_led_config_ext_t        config_ext;        /**< The timing of led. */
    hal_pwm_led_other_config_t      other_config;    /**< The brightness of led. */
}hal_pwm_led_config_flex_ext_t;


typedef struct
{
    uint16_t  t1_rising_ms;
    uint16_t  t1_on_ms;
    uint16_t  t2_falling_ms;
    uint16_t  t2_off_ms;
    uint16_t  t3_ms;
    uint16_t  on_step_rem;
    uint16_t  off_step_rem;
    uint16_t   on_step_inc;
    uint16_t   off_step_inc;
    uint8_t   t1t2_repeat_count;
    uint8_t   init_status;
}pwm_led_config_bk_t;

typedef struct
{
    uint16_t  t0_ms;
    uint16_t  t1_rising_ms;
    uint16_t  t1_on_ms;
    uint16_t  t2_falling_ms;
    uint16_t  t2_off_ms;
    uint16_t  t3_ms;
    uint16_t  on_step_rem;
    uint16_t  off_step_rem;
    uint16_t  on_step_inc;
    uint16_t  off_step_inc;
    uint8_t   start_duty;
    uint8_t   high_duty;
    uint8_t   end_duty;
    uint8_t   t1t2_repeat_count;
    uint8_t   repeat_count;
}hal_pwm_led_config_t;
#endif  /* defined(HAL_PWM_LED_SUPPORTED) || defined(HAL_PWM_RGB_SUPPORTED) */


#ifdef HAL_PWM_LED_SUPPORTED
typedef void (*hal_pwm_led_callback_t)(void *user_data);

typedef struct {
    hal_pwm_led_callback_t call_back;
    void              *user_data;
} pwm_led_info_t;


typedef struct {
    uint16_t         led_one_period_count;
    uint16_t         led_one_period_ms;
    hal_pwm_led_config_t *led_config;
    pwm_led_info_t    pwm_led_info;
    uint8_t           led_channel;
}pwm_led_para_t;

#endif //HAL_PWM_LED_SUPPORTED

#ifdef HAL_PWM_RGB_SUPPORTED

typedef void (*hal_pwm_rgb_callback_t)(void *user_data);

typedef struct {
    hal_pwm_rgb_callback_t call_back;
    void              *user_data;
} pwm_rgb_info_t;

typedef struct {
    uint16_t rgb_one_period_count;
    uint8_t rgb_one_period_ms;
    uint8_t  close_port;
    uint8_t  open_port;
    uint8_t  rgb_total_num_count;
    uint8_t  rgb_port;
    uint8_t  *pwm_rgb_entry;
    uint8_t  *rgb_gpio_setting;
}pwm_rgb_para_t;

#ifdef RGB_REAL_TIME_FIFO
typedef struct {
    void    *fifo_reserved;
    uint8_t  rgb_r;
    uint8_t  rgb_g;
    uint8_t  rgb_b;
}rgb_real_time_config_t;

typedef struct {
    uint8_t mode;
    uint8_t status;
    pwm_rgb_info_t rgb_info;
    uint8_t *user_data;
    uint8_t *bk_user_data;
    uint8_t *rgb_channel_setting;
    struct k_queue real_time;
}pwm_rgb_config_t;
#endif

#ifdef RGB_REAL_TIME_ACK
typedef struct {
    uint8_t  rgb_r;
    uint8_t  rgb_g;
    uint8_t  rgb_b;
}rgb_real_time_config_t;

typedef struct {
    uint8_t mode;
    uint8_t status;
    pwm_rgb_info_t rgb_info;
    uint8_t *user_data;
    uint8_t *bk_user_data;
    uint8_t *rgb_channel_setting;
    rgb_real_time_config_t real_time;
}pwm_rgb_config_t;
#endif

typedef struct {
    uint8_t *rgb_r;
    uint8_t *rgb_g;
    uint8_t *rgb_b;
    uint16_t size;
    uint8_t irq_left_size;
    uint8_t  repeat_count;
}rgb_flash_config_t;

typedef struct {
    uint8_t *rgb;
    uint16_t size;
    uint8_t irq_left_size;
    uint8_t  repeat_count;
}rgb_flash_config_v2_t;

typedef enum {
    rgb_flash_left_size = 0,
    rgb_flash_refresh = 1,
} rgb_flash_type_t;

typedef enum {
    rgb_breath = 1,
    rgb_real_time =2,
    rgb_flash =3,
    rgb_flash_v2 =4,
} rgb_mode_t;

typedef struct {
    hal_pwm_led_config_t led_config;
    uint8_t status;
}pwm_rgb_led_config_t;

#endif  //HAL_PWM_RGB_SUPPORTED

#ifdef __cplusplus
}
#endif

#endif