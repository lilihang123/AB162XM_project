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
#ifndef  _RGB_MIDDLE_CONTROL_H_
#define  _RGB_MIDDLE_CONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "bsp_rgb.h"
#include "rgb_control_style_cfg.h"


/**
* @brief This struct for record users operate history
*/

typedef struct {
    bool                enable;     /**< Enable this pattern */
    rgb_pattern_type_t  pattern;    /**< Led pattern type */
    uint16_t            style_no;   /**< Led style number */
} rgb_pattern_record_t;

typedef struct {
    bool                enable;     /**< Enable this pattern */
    rgb_pattern_type_t  pattern;    /**< Led pattern type */
    uint16_t            index;   /**< Led style number */
    uint8_t             repeat;     /**< Flash mode repeat time */
} rgb_pattern_flash_record_t;

typedef struct {
    uint8_t     *cfg_r;
    uint8_t     *cfg_g;
    uint8_t     *cfg_b;
    uint8_t     interval;   /**< Led style number for flash / real time*/
    uint16_t    index;       /**< Led style number for flash / normal*/
} rgb_pattern_data_t;

/**
* @brief This struct for record users enum and rgb data
*/

/**
 * @brief This enum for define rgb effect type
 */
typedef enum {
    TYPE_RGB_NORMAL = 1,
    TYPE_RGB_FLASH = 2,
    TYPE_RGB_REAL_TIME = 3,
} rgb_effect_type_t;

typedef struct {
    uint8_t     *cfg_r;
    uint8_t     *cfg_g;
    uint8_t     *cfg_b;
    uint8_t     interval;   /* Led style for real time */
} rgb_real_time_effect_t;

typedef struct {
    uint8_t     index;
    uint8_t     interval;   /* Led style for flash */
} rgb_flash_effect_t;

typedef struct {
    uint8_t     index;   /* Led style for normal */
} rgb_normal_effect_t;

typedef struct {
    rgb_effect_type_t     type;
    union {
        rgb_normal_effect_t normal;
        rgb_flash_effect_t  flash;
        rgb_real_time_effect_t realtime;
    } effect_data;
} rgb_effect_t;

typedef void (*rgb_middle_callback_t)(void *user_data);

typedef struct {
    rgb_middle_callback_t call_back;
    void              *user_data;
} rgb_middle_info_t;

typedef struct {
    uint8_t  rgb_count;
    uint8_t  rgb_size;
    uint8_t  rgb_size2;
    uint8_t  rgb_interval;
    uint8_t  *rgb_data;
} rgb_nvkey_t;

typedef enum {
    RGB_MIDDLE_IDLE = 0,
    RGB_MIDDLE_RUNNING = 1,
} rgb_middle_running_status_t;
/**
 * @brief This enum for define status
 */
typedef enum {
    RGB_MIDDLE_STATUS_ERROR = -1,
    RGB_MIDDLE_STATUS_OK = 0,
    RGB_MIDDLE_STATUS_OK_LOW_PATTERN = 1,
    RGB_MIDDLE_STATUS_OK_DONE = 2,
    RGB_MIDDLE_FLASH_DONE = 3,
} rgb_middle_status_t;

rgb_middle_status_t    rgb_middle_control_enable(uint8_t rgb_num,  rgb_pattern_type_t pattern, uint8_t  style_no, bool force_option);
rgb_middle_status_t    rgb_middle_control_disable(uint8_t rgb_num, rgb_run_type_t type, rgb_pattern_type_t  pattern, bool force_option);
rgb_middle_status_t    rgb_middle_get_running_status(uint8_t rgb_num, rgb_middle_running_status_t *running_status);
rgb_middle_status_t    rgb_middle_register_callback(uint8_t rgb_num, rgb_middle_callback_t callback, void  *user_data);
int                    rgb_middle_control_realtime_enable(uint8_t rgb_num, uint8_t interval, uint8_t *cfg_r, uint8_t *cfg_g, uint8_t *cfg_b);
rgb_middle_status_t    rgb_middle_control_flash_enable(uint8_t rgb_num, uint16_t id, uint8_t repeat);
rgb_middle_status_t    rgb_middle_control_enable_for_node(uint8_t rgb_num, rgb_pattern_data_t data_config, uint8_t pattern, rgb_run_type_t run_type);
uint8_t                rgb_middle_get_rgb_info_list_for_current_priority(uint8_t rgb_num);
uint8_t                rgb_middle_get_rgb_info_list_for_current_type(uint8_t rgb_num);
rgb_middle_status_t    rgb_middle_control_disable_all(uint8_t rgb_num);

#ifdef __cplusplus
}
#endif
#endif /*END _RGB_MIDDLE_CONTROL_H_*/