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

/**
 * @addtogroup HAL
 * @{
 * @addtogroup LED
 * @{
 */

#ifndef __HAL_LED_H__
#define __HAL_LED_H__

#include "hal_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup hal_led_enum Enum
  * @{
  */

/** @brief LED channel. */
typedef enum {
    HAL_LED_CHANNEL_0 = 0,                          /**< The LED channel 0. */
    HAL_LED_CHANNEL_1 = 1,                          /**< The LED channel 1. */
    HAL_LED_CHANNEL_2 = 2,                          /**< The LED channel 2. */
    HAL_LED_CHANNEL_3 = 3,                          /**< The LED channel 3. */
    HAL_LED_MAX_CHANNEL                             /**< The LED maximum channel (invalid).*/
} hal_led_channel_t;


/** @brief LED operating mode seletion. */
typedef enum {
    HAL_LED_MODE_PWM = 0,                              /**<The PWM mode.  */
    HAL_LED_MODE_BREATH = 1,                           /**<The Breath mode.  */
} hal_led_mode_t ;

/** @brief LED status. */
typedef enum {

    HAL_LED_STATUS_ERROR               = -4,       /**< The LED function error occurred. */
    HAL_LED_STATUS_ERROR_BUSY           = -3,       /**< The LED BUSY channel. */
    HAL_LED_STATUS_ERROR_CHANNEL       = -2,       /**< The LED error channel. */
    HAL_LED_STATUS_ERROR_INVALID_PARAMETER   = -1, /**< An error occurred, invalid parameter was given. */
    HAL_LED_STATUS_OK   = 0                       /**< The LED operation completed successfully.*/
} hal_led_status_t;


/** @brief  This enum defines the LED running status. */
typedef enum {
    HAL_LED_IRQ_BUSY = 0,                         /**< The LED is IRQ BUSY. */
    HAL_LED_NORMAL_BUSY = 1                          /**< The LED is NORMAL busy. */
}hal_led_busy_status_t;


/** @brief  This enum defines the LED running status. */
typedef enum {
    HAL_LED_IDLE = 0,                         /**< The LED is idle. */
    HAL_LED_BUSY = 1                          /**< The LED is busy. */
} hal_led_running_status_t;

typedef void (*hal_led_callback_t)(void *user_data);

typedef struct {
    hal_led_callback_t callback;
    void              *user_data;
} hal_led_callback_context_t;

/** @brief LED breath mode based ont the time adjustment and brightness levels. */
// typedef enum {
//     HAL_LED_TIME_0_123_SECOND = 0,                       /**<The LED breath adjustment time, 0.123s.  */
//     HAL_LED_TIME_0_338_SECOND = 1,                       /**<The LED breath adjustment time, 0.338s.  */
//     HAL_LED_TIME_0_523_SECOND = 2,                       /**<The LED breath adjustment time, 0.523s. */
//     HAL_LED_TIME_0_707_SECOND = 3,                       /**<The LED breath adjustment time, 0.707s. */
//     HAL_LED_TIME_0_926_SECOND = 4,                       /**<The LED breath adjustment time, 0.926s. */
//     HAL_LED_TIME_1_107_SECOND = 5,                       /**<The LED breath adjustment time, 1.107s. */
//     HAL_LED_TIME_1_291_SECOND = 6,                       /**<The LED breath adjustment time, 1.291s.  */
//     HAL_LED_TIME_1_507_SECOND = 7,                       /**<The LED breath adjustment time, 1.507s.  */
//     HAL_LED_TIME_1_691_SECOND = 8,                       /**<The LED breath adjustment time, 1.691s. */
//     HAL_LED_TIME_1_876_SECOND = 9,                       /**<The LED breath adjustment time, 1.876s. */
//     HAL_LED_TIME_2_091_SECOND = 10,                      /**<The LED breath adjustment time, 2.091s.*/
//     HAL_LED_TIME_2_276_SECOND = 11,                      /**<The LED breath adjustment time, 2.276s. */
//     HAL_LED_TIME_2_460_SECOND = 12,                      /**<The LED breath adjustment time, 2.460s. */
//     HAL_LED_TIME_2_676_SECOND = 13,                      /**<The LED breath adjustment time, 2.676s. */
//     HAL_LED_TIME_2_860_SECOND = 14,                      /**<The LED breath adjustment time, 2.860s. */
//     HAL_LED_TIME_3_075_SECOND = 15                       /**<The LED breath adjustment time, 3.075s. */
// } hal_led_breath_adjust_on_t ;

/** @brief LED breath mode off based on each time adjustment. */

// typedef enum {
//     HAL_LED_TIME_0_246_SECOND = 0,                       /**<The LED breath adjustment time, 0.246s.  */
//     HAL_LED_TIME_0_677_SECOND = 1,                       /**<The LED breath adjustment time, 0.677s.  */
//     HAL_LED_TIME_1_046_SECOND = 2,                       /**<The LED breath adjustment time, 1.046s. */
//     HAL_LED_TIME_1_417_SECOND = 3,                       /**<The LED breath adjustment time, 1.417s. */
//     HAL_LED_TIME_1_845_SECOND = 4,                       /**<The LED breath adjustment time, 1.845s. */
//     HAL_LED_TIME_2_214_SECOND = 5,                       /**<The LED breath adjustment time, 2.214s.  */
//     HAL_LED_TIME_2_583_SECOND = 6,                       /**<The LED breath adjustment time, 2.583s.  */
//     HAL_LED_TIME_3_014_SECOND = 7,                       /**<The LED breath adjustment time, 3.014s.  */
//     HAL_LED_TIME_3_383_SECOND = 8,                       /**<The LED breath adjustment time, 3.383s. */
//     HAL_LED_TIME_3_752_SECOND = 9,                       /**<The LED breath adjustment time, 3.752s. */
//     HAL_LED_TIME_4_183_SECOND = 10,                      /**<The LED breath adjustment time, 4.183s. */
//     HAL_LED_TIME_4_552_SECOND = 11,                      /**<The LED breath adjustment time, 4.552s. */
//     HAL_LED_TIME_4_921_SECOND = 12,                      /**<The LED breath adjustment time, 4.921s. */
//     HAL_LED_TIME_5_351_SECOND = 13,                      /**<The LED breath adjustment time, 5.351s. */
//     HAL_LED_TIME_5_720_SECOND = 14,                      /**<The LED breath adjustment time, 5.720s. */
//     HAL_LED_TIME_6_151_SECOND = 15                       /**<The LED breath adjustment time, 6.151s. */
// } hal_led_breath_adjust_off_t ;


/** @defgroup hal_led_struct Struct
  * @{
  */

// /** @brief led breath mode config */
// typedef struct {
//     hal_led_breath_adjust_on_t  darker_to_lighter_time1;         /**<The LED breath mode timing adjustment setting 1 corresponding to the brightness level from darker to lighter. */
//     hal_led_breath_adjust_on_t  darker_to_lighter_time2;         /**<The LED breath mode timing adjustment setting 2 corresponding to the brightness level from darker to lighter. */
//     hal_led_breath_adjust_on_t  lightest_time;                   /**< Duration of the brightest level.  */
//     hal_led_breath_adjust_on_t  lighter_to_darker_time1;         /**<The LED breath mode timing adjustment setting 1 corresponding to the brightness level from lighter  to darker. */
//     hal_led_breath_adjust_on_t  lighter_to_darker_time2;         /**<The LED breath mode timing adjustment setting 2 corresponding to the brightness level from lighter   to darker.*/
//     hal_led_breath_adjust_off_t darkest_time;                    /**< Duration of the darkest time.  */
// } hal_led_breath_mode_t;


// /** @brief led pwm mode config */
// typedef struct {
//     uint16_t     hi_level_time;         /**< The time of PWM output high level in one cycle(unit ms). */
//     uint16_t     lo_level_time;         /**< The time of PWM output low level in one cycle(unit ms). */
//     uint16_t     blink_nums;            /**< Pulse number of PWM output signal. */
//     uint16_t     idle_time;             /**< Idle times after completion of blink numbers. The time must be an integer that is a multiple of the pwm cycle time.*/
// }hal_led_pwm_mode_t;


// typedef struct{
//     hal_led_mode_t                mode;          /**< The mode of LED. */
//     union{
//         hal_led_breath_mode_t     breath_mode;   /**< The config of breath mode when the mode is breath mode. */
//         hal_led_pwm_mode_t        pwm_mode;      /**< The config of pwm mode when the mode is pwm mode. */
//     }config;                                       /**< The LED configure setting. */
// }hal_led_config_t;


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
}hal_led_timing_config_t;

/** @brief led extend config */
typedef struct{
    hal_led_timing_config_t         timing;        /**< The timing of led. */
    uint8_t                         brightness;    /**< The brightness of led. */
    uint8_t                         blink_nums;    /**< The blink number of led(the period is t1 + t2). */
}hal_led_config_ext_t;

/** @brief led other config */
typedef struct {
    uint8_t start_brightness;                     /**< The start brightness of led. */
    uint8_t end_brightness;                       /**< The end brightness of led. */
    uint8_t repeat_times;                         /**< The total of led repeat time. */
}hal_led_other_config_t;


/** @brief led extend config */
typedef struct{
    hal_led_config_ext_t        config_ext;        /**< The timing of led. */
    hal_led_other_config_t      other_config;      /**< The brightness of led. */
}hal_led_config_flex_ext_t;


#define LED0   0
#define LED1   1
#define LED2   2
#define T0     0
#define T1     1
/* 00 0 01 ********* 00 is led0,0 is T0,01 is led 1*/
typedef enum {
    HAL_LED0_T0_LED1 = (LED0<<3)|(T0<<2)|(LED1),                       /**<The LED LED1 follow LED0 T0.  */
    HAL_LED0_T0_LED2 = (LED0<<3)|(T0<<2)|(LED2),                       /**<The LED LED2 follow LED0 T0.  */
    HAL_LED0_T1_LED1 = (LED0<<3)|(T1<<2)|(LED1),                       /**<The LED LED1 follow LED0 T1.  */
    HAL_LED0_T1_LED2 = (LED0<<3)|(T1<<2)|(LED2),                       /**<The LED LED2 follow LED0 T1.  */
    HAL_LED1_T0_LED0 = (LED1<<3)|(T0<<2)|(LED0),                       /**<The LED LED0 follow LED1 T0.  */
    HAL_LED1_T0_LED2 = (LED1<<3)|(T0<<2)|(LED2),                       /**<The LED LED2 follow LED1 T0.  */
    HAL_LED1_T1_LED0 = (LED1<<3)|(T1<<2)|(LED0),                       /**<The LED LED0 follow LED1 T1.  */
    HAL_LED1_T1_LED2 = (LED1<<3)|(T1<<2)|(LED2),                       /**<The LED LED2 follow LED1 T1.  */
    HAL_LED2_T0_LED0 = (LED2<<3)|(T0<<2)|(LED0),                       /**<The LED LED0 follow LED2 T0.  */
    HAL_LED2_T0_LED1 = (LED2<<3)|(T0<<2)|(LED1),                       /**<The LED LED1 follow LED2 T0.  */
    HAL_LED2_T1_LED0 = (LED2<<3)|(T1<<2)|(LED0),                       /**<The LED LED0 follow LED2 T1.  */
    HAL_LED2_T1_LED1 = (LED2<<3)|(T1<<2)|(LED1),                       /**<The LED LED1 follow LED2 T1.  */
} hal_led_follow_type_t ;



typedef struct{
    uint8_t enable;                             /**<The LED enable follow.  */
    uint8_t hard_force_follow;                  /**<The LED hard force follow.  */
    hal_led_follow_type_t type;                 /**<The LED follow  type.  */
}hal_follow_setting_t;


/**
  * @}
  */

/**
 * @brief    This function initializes the LED hardware.
 * @param[in]  channel is the LED channel number. For more details about the parameter, please refer to #hal_led_channel_t.
 * @return   Indicates whether this function call is successful or not.
 *            If the return value is #HAL_LED_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_LED_STATUS_ERROR_INVALID_PARAMETER, a wrong parameter is given. The parameter needs to be verified.
 * @sa  hal_led_deinit()
 */

hal_led_status_t  hal_led_init(hal_led_channel_t  channel);


/**
 * @brief    This function deinitializes the LED hardware.
 * @param[in]  channel is the LED channel number. For more details about the parameter, please refer to #hal_led_channel_t.
 * @return     Indicates whether this function call is successful or not.
 *            If the return value is #HAL_LED_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_LED_STATUS_ERROR_INVALID_PARAMETER, a wrong parameter is given. The parameter needs to be verified.
 * @sa  hal_led_init()
 */

hal_led_status_t  hal_led_deinit(hal_led_channel_t channel);

// /**
//  * @brief  This function is to configure LED HW.
//  * @param[in]  channel is the LED channel number. For more details about the parameter, please refer to #hal_led_channel_t.
//  * @param[in]  config is the LED mode and mode setting.For more details about the parameter, please refer to #hal_led_config_t.
//  * @return     Indicates whether this function call is successful or not.
//  *            If the return value is #HAL_LED_STATUS_OK, the operation completed successfully.
//  *            If the return value is #HAL_LED_STATUS_ERROR_INVALID_PARAMETER, a wrong parameter is given. The parameter needs to be verified.
//  */

// hal_led_status_t hal_led_configure(hal_led_channel_t channel, hal_led_config_t *cfg);

/**
 * @brief    This function invert the LED hardware output waveform.
 * @param[in]  channel is the LED channel number. For more details about the parameter, please refer to #hal_led_channel_t.
 * @param[in]  invert enable or disable the LED hardware output waveform invert function.
 * @return     Indicates whether this function call is successful or not.
 *            If the return value is #HAL_LED_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_LED_STATUS_ERROR_INVALID_PARAMETER, a wrong parameter is given. The parameter needs to be verified.
 */

hal_led_status_t  hal_led_set_invert(hal_led_channel_t channel,bool invert);
/**
 * @brief  This function is to configure LED with new hardware feature.
 * @param[in]  channel is the LED channel number. For more details about the parameter, please refer to #hal_led_channel_t.
 * @param[in]  config is the LED timing, brightness and blink numbers. For more details about the parameter, please refer to #hal_led_config_ext_t.
 * @return     Indicates whether this function call is successful or not.
 *            If the return value is #HAL_LED_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_LED_STATUS_ERROR_INVALID_PARAMETER, a wrong parameter is given. The parameter needs to be verified.
 */
hal_led_status_t  hal_led_configure_ext(hal_led_channel_t channel, hal_led_config_ext_t *cfg);

/**
 * @brief  This function is to configure LED flex with new hardware feature.
 * @param[in]  channel is the LED channel number. For more details about the parameter, please refer to #hal_led_channel_t.
 * @param[in]  config is the LED timing, brightness and blink numbers. For more details about the parameter, please refer to #hal_led_config_flex_ext_t.
 * @return     Indicates whether this function call is successful or not.
 *            If the return value is #HAL_LED_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_LED_STATUS_ERROR_INVALID_PARAMETER, a wrong parameter is given. The parameter needs to be verified.
 */
hal_led_status_t  hal_led_configure_flex_ext(hal_led_channel_t channel,hal_led_config_flex_ext_t *cfg);

/**
 * @brief  This function is to configure LED special for irpt new feature.
 * @param[in]  channel is the LED channel number. For more details about the parameter, please refer to #hal_led_channel_t.
 * @param[in]  light_time_us is the LED light timing. 
 * @param[in]  dark_time_us is the LED light timing. 
 * @return     Indicates whether this function call is successful or not.
 *            If the return value is #HAL_LED_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_LED_STATUS_ERROR_INVALID_PARAMETER, a wrong parameter is given. The parameter needs to be verified.
 */
hal_led_status_t  hal_led_configure_for_irpt(hal_led_channel_t channel, uint32_t light_time_us, uint32_t dark_time_us);

/**
 * @brief  This function is to configure following setting for LED.
 * @param[in]  set is the LED follow setting.For more details about the parameter, please refer to #hal_follow_setting_t.
 * @return     Indicates whether this function call is successful or not.
 *            If the return value is #HAL_LED_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_LED_STATUS_ERROR_INVALID_PARAMETER, a wrong parameter is given. The parameter needs to be verified.
 */
hal_led_status_t hal_led_follow_setting(hal_follow_setting_t *set);

/**
 * @brief  This function start LED hardware.
 * @param[in]  channel is the LED channel number. For more details about the parameter, please refer to #hal_led_channel_t.
 * @return     Indicates whether this function call is successful or not.
 *            If the return value is #HAL_LED_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_LED_STATUS_ERROR_INVALID_PARAMETER, a wrong parameter is given. The parameter needs to be verified.
 */

hal_led_status_t hal_led_start(hal_led_channel_t channel);

/**
 * @brief  This function stop LED hardware.
 * @param[in]  channel is the LED channel number. For more details about the parameter, please refer to #hal_led_channel_t.
 * @return     Indicates whether this function call is successful or not.
 *            If the return value is #HAL_LED_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_LED_STATUS_ERROR_INVALID_PARAMETER, a wrong parameter is given. The parameter needs to be verified.
 */

hal_led_status_t hal_led_stop(hal_led_channel_t channel);

/**
 * @brief  This function register callback for led stop event.
 * @param[in]  channel is the LED channel number. For more details about the parameter, please refer to #hal_led_channel_t.
 * @param[in]  callback is the LED channel number. For more details about the parameter, please refer to #hal_led_callback_t.
 * @param[in]  user_data is the LED channel number.
 * @return     Indicates whether this function call is successful or not.
 *            If the return value is #HAL_LED_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_LED_STATUS_ERROR_INVALID_PARAMETER, a wrong parameter is given. The parameter needs to be verified.
 */
hal_led_status_t hal_led_register_callback(hal_led_channel_t channel, hal_led_callback_t callback, void *user_data);

/**
 * @brief  This function unmask led IRQ.
 * @param[in]  channel is the LED channel number. For more details about the parameter, please refer to #hal_led_channel_t.
 * @return     Indicates whether this function call is successful or not.
 *            If the return value is #HAL_LED_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_LED_STATUS_ERROR_INVALID_PARAMETER, a wrong parameter is given. The parameter needs to be verified.
 */
hal_led_status_t hal_led_unmask(hal_led_channel_t channel);

/**
 * @brief  This function mask led IRQ.
 * @param[in]  channel is the LED channel number. For more details about the parameter, please refer to #hal_led_channel_t.
 * @return     Indicates whether this function call is successful or not.
 *            If the return value is #HAL_LED_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_LED_STATUS_ERROR_INVALID_PARAMETER, a wrong parameter is given. The parameter needs to be verified.
 */
hal_led_status_t hal_led_mask(hal_led_channel_t channel);

#ifdef __cplusplus
}
#endif

#endif /* HAL_LED_H */


