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
#ifndef  _LED_MIDDLE_CONTROL_H_
#define  _LED_MIDDLE_CONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "bsp_led.h"
#include "led_control_style_cfg.h"


/**
* @brief This struct for record users operate history
*/

typedef struct{
    bool                enable;     /**< Enable this pattern */
    led_pattern_type_t  pattern;    /**< Led pattern type */
    uint16_t            style_no;   /**< Led style number */
}led_pattern_record_t;


typedef void (*led_middle_callback_t)(void *user_data);

typedef struct {
    led_middle_callback_t call_back;
    void              *user_data;
} led_middle_info_t;

typedef enum{
    LED_MIDDLE_IDLE = 0,
    LED_MIDDLE_RUNNING = 1,
}led_middle_running_status_t;
/**
 * @brief This enum for define status
 */
typedef enum {
    LED_MIDDLE_STATUS_ERROR = -1,
    LED_MIDDLE_STATUS_OK = 0,
    LED_MIDDLE_STATUS_OK_LOW_PATTERN = 1,
    LED_MIDDLE_STATUS_OK_DONE= 2,
} led_middle_status_t;

led_middle_status_t    led_middle_control_enable(led_num_t led_num,  led_pattern_type_t pattern, uint8_t  style_no, bool force_option);
led_middle_status_t    led_middle_control_disable(led_num_t led_num, led_pattern_type_t pattern, bool force_option);
led_middle_status_t    led_middle_get_running_status(led_num_t led_num, led_middle_running_status_t *running_status);
led_middle_status_t    led_middle_register_callback(led_num_t led_num,led_middle_callback_t callback, void  *user_data);
#ifdef __cplusplus
}
#endif
#endif /*END _LED_MIDDLE_CONTROL_H_*/