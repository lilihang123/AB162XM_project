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

#ifndef  _RGB_CONTROL_STYLE_CFG_H_
#define  _RGB_CONTROL_STYLE_CFG_H_

#ifdef __cplusplus
extern "C" {
#endif
/**
 * File: rgb_control_style_cfg.h
 * Description: This file is to read rgb configure infomation from NVDM.
 * Note: None
 */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hal_platform.h"
#include "hal.h"

#define     RGB_SYSTEM_MODE_NORMAL          0 /* Define normal mode,that rgb will not turn off when system enter sleep */
#define     RGB_SYSTEM_MODE_LP_TEST         1 /* Define lowpower test mode for user measure system lowpower */

#define     RGB_ON      1
#define     RGB_OFF     0

/**
 * @brief This enum for define rgb pattern
 */
typedef enum {
    RGB_PATTERN_BG = 0, /**< The backgroud pattern */
    RGB_PATTERN_FG,     /**< The foregroud pattern */
    RGB_PATTERN_FILTER, /**< The filter pattern */
    RGB_PATTERN_NONE,   /**< The error pattern */
} rgb_pattern_type_t;

#pragma  pack(1)
typedef struct {
    uint16_t     t0;        /**< delay start time before rgb started */
    uint16_t     t1_rising;        /**< rgb on time in one twinkle cycle */
    uint16_t     t1_lightest;        /**< rgb on time in one twinkle cycle */
    uint16_t     t2_falling;        /**< rgb off time in one twinkle cycle */
    uint16_t     t2_darkest;        /**< rgb off time in one twinkle cycle */
    uint16_t     t3;        /**< rgb idle time after finish t1t2_repeat */
    uint8_t      repeat_t1t2;  /**< t1t2 repeat times */
    uint8_t      repeat_ext;   /**< extern loop repeat times */
    uint8_t      brightness;   /**< rgb brightness*/
    uint8_t      start_brightness;        /**< rgb start brightness */
    uint8_t      end_brightness;        /**< rgb end brightness */
    uint8_t      onoff;                   /**< rgb on off(1:on,0:off) */
} rgb_one_led_style_t;
#pragma  pack()

typedef struct {
    rgb_one_led_style_t rgb_r;
    rgb_one_led_style_t rgb_g;
    rgb_one_led_style_t rgb_b;
} one_rgb_style_t;

typedef enum {
    rgb_occupy_none = 0,      /**< The rgb is not running */
    rgb_occupy_rgb,           /**< The rgb is breath*/
    rgb_occupy_realtime_rgb, /**<  The rgb is realtime */
    rgb_occupy_flash_rgb,    /**<  The rgb is flash */
} rgb_run_type_t;

/**
 * @brief This struct for rgb style config setting which stored in NVDM.
 */
typedef struct {
    uint8_t                  rgb_num;    /**< rgb num that user configured by config tool*/
    rgb_run_type_t           type;
    one_rgb_style_t         *rgb_setting;/**< rgb style setting that user configured by config tool*/
    uint8_t       pattern;    /**< Led pattern type */
} rgb_style_config_t;



/**
 * @brief This function get rgb style configure infomation.
 * @param[in] type is the type that RGB want to read.
 * @param[in] pattern is the pattern type that RGB want to read.
 * @param[in] style_no is the style number that rgb want to read.
 * @return #Not NULL  means success.
 *         #NULL  means fail.
 */
rgb_style_config_t    *rgb_style_config_read(uint8_t rgb_num, rgb_run_type_t type, uint8_t    pattern, uint8_t  style_no);


/**
 * @brief This function get system mode
 * @return #RGB_SYSTEM_MODE_NORMAL
 *             #RGB_SYSTEM_MODE_LP_TEST
 */
uint8_t               rgb_style_config_sys_mode(void);

#ifdef __cplusplus
}
#endif
#endif /*END _RGB_CONTROL_STYLE_CFG_H_*/