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

#ifndef __BSP_RGB_H__
#define __BSP_RGB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hal.h"
#include "hal_pwm.h"
#include "rgb_control_style_cfg.h"

/** @defgroup bsp_rgb_typedef Typedef
  * @{
  */
/** @brief Callback functioon definition to handle the RGB completed event. */
typedef void(* bsp_rgb_callback_t)(void *user_data);
/**
* @}
*/
typedef enum {
    BSP_RGB_STATUS_ERROR_BUSY          = -5,
    BSP_RGB_STATUS_ERROR_NO_DEVICE     = -4,
    BSP_RGB_STATUS_ERROR_CHANNEL       = -3,       /**< The ISINK error channel. */
    BSP_RGB_STATUS_ERROR_INVALID_PARAMETER   = -2, /**< An error occurred, invalid parameter was given. */
    BSP_RGB_STATUS_ERROR               = -1,        /**< The ISINK function error occurred. */
    BSP_RGB_STATUS_OK   = 0                         /**< The ISINK operation completed successfully.*/
} bsp_rgb_status_t;


typedef struct {
    uint8_t pwm_port;
    uint8_t rgb_frequency;
    uint8_t gpio_channel;
    uint8_t rgb_port;
    uint8_t gpio_control;
    uint8_t gpio_polarity;
    uint8_t channel0_polarity;
    uint8_t channel1_polarity;
    uint8_t channel2_polarity;
    uint8_t channel3_polarity;
    uint8_t r_channel;
    uint8_t g_channel;
    uint8_t b_channel;
    bsp_rgb_callback_t callback;
    void *user_data;
} rgb_para_t;


bsp_rgb_status_t bsp_rgb_enable(uint8_t rgb_num, rgb_one_led_style_t *cfg_r, rgb_one_led_style_t *cfg_g, rgb_one_led_style_t *cfg_b);

bsp_rgb_status_t bsp_rgb_disable(uint8_t rgb_num);

bsp_rgb_status_t bsp_rgb_register_isr(uint8_t rgb_num, bsp_rgb_callback_t callback, void *user_data);

bsp_rgb_status_t bsp_rgb_realtime_enable(uint8_t rgb_num, uint8_t interval);

#ifdef RGB_REAL_TIME_FIFO 
int              bsp_rgb_realtime_config(uint8_t rgb_num, uint8_t *cfg_r, uint8_t *cfg_g, uint8_t *cfg_b);
#endif

#ifdef RGB_REAL_TIME_ACK
bsp_rgb_status_t bsp_rgb_realtime_config(uint8_t rgb_num, uint8_t *cfg_r, uint8_t *cfg_g, uint8_t *cfg_b);
#endif
bsp_rgb_status_t bsp_rgb_realtime_start(uint8_t rgb_num);

bsp_rgb_status_t bsp_rgb_flash_enable(uint8_t rgb_num, uint8_t *rgb, uint16_t interval, uint16_t size, uint8_t repeat);

bsp_rgb_status_t bsp_rgb_flash_config_left_size(uint8_t rgb_num);

bsp_rgb_status_t bsp_rgb_flash_continued_enable(uint8_t rgb_num, uint8_t *rgb, uint16_t size);
#ifdef __cplusplus
}
#endif

#endif