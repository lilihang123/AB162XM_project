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

#ifndef _HID_GAME_CONTROLLER_H_
#define _HID_GAME_CONTROLLER_H_

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/* Public define -------------------------------------------------------------*/
#define JOYSTICK_MAX_VALUE 2047
#define JOYSTICK_MIN_VALUE -2048
#define JOYSTICK_0_LEVEL_VALUE 0x8000
#define JOYSTICK_HALF_RANGE_VALUE 0x7fff

#define TRIGGER_RANGE_VALUE 65535

#define ADC_RANGE_VALUE_12BIT 4096
#define ADC_RANGE_VALUE_16BIT 65536

#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#define JOYSTICK_DEFAULT_SENSITIVITY 100
#endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */
/* Public typedef ------------------------------------------------------------*/
typedef uint8_t game_controller_joystick_num_t;
enum {
    GAME_CONTROLLER_JOYSTICK_X = 0,
    GAME_CONTROLLER_JOYSTICK_Y,
    GAME_CONTROLLER_JOYSTICK_Z,
    GAME_CONTROLLER_JOYSTICK_RZ,
    GAME_CONTROLLER_JOYSTICK_NUM_MAX,
};

typedef struct {
    uint32_t max;
    uint32_t min;
    uint32_t zero_value;
    uint32_t zero_deadzone_min_value;
    uint32_t zero_deadzone_max_value;
} joystick_adc_parameter_t;

typedef uint8_t game_controller_trigger_num_t;
enum {
    GAME_CONTROLLER_TRIGGER_L = 0,
    GAME_CONTROLLER_TRIGGER_R,
    GAME_CONTROLLER_TRIGGER_NUM_MAX,
};

typedef uint8_t game_controller_trigger_direction_t;
enum {
    GAME_CONTROLLER_TRIGGER_DIRECTION_FORWARD = 0,
    GAME_CONTROLLER_TRIGGER_DIRECTION_REVERSE,
};

typedef uint8_t game_controller_sensitivity_direction_t;
enum {
    GAME_CONTROLLER_LEFT_SENSITIVITY = 0,
    GAME_CONTROLLER_RIGHT_SENSITIVITY,
};

typedef struct {
    game_controller_trigger_direction_t direction;
    uint32_t max;
    uint32_t min;
    uint32_t zero_deadzone_value;
} trigger_adc_parameter_t;

typedef void (*hid_game_controller_report_callback)();
/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
extern int game_controller_bt_hw_trigger_enable(void);
extern int game_controller_bt_hw_trigger_disable(void);
extern int game_controller_bt_hw_trigger_read(void);
extern joystick_adc_parameter_t *game_controller_joystick_get_calibration_value(game_controller_joystick_num_t joystick_num);
extern void game_controller_joystick_update_calibration_value(game_controller_joystick_num_t joystick_num,
                                                        uint32_t min, uint32_t max, uint32_t zero_value,
                                                        uint32_t zero_deadzone_min_value, uint32_t zero_deadzone_max_value);
extern trigger_adc_parameter_t *game_controller_trigger_get_calibration_value(game_controller_trigger_num_t trigger_num);
extern void game_controller_trigger_update_calibration_value(game_controller_trigger_num_t trigger_num, game_controller_trigger_direction_t direction,
                                                        uint32_t min, uint32_t max, uint32_t zero_deadzone_value);
bool game_controller_usb_register(hid_game_controller_report_callback cb);
extern void game_controller_fake_data_control(bool enable, uint8_t pattern, uint8_t rounds);
void game_controller_set_expand_button(uint32_t *key);
#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
void game_controller_set_sensitivity(uint8_t direction, uint8_t value);
#endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */
#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */

#endif /* _HID_GAME_CONTROLLER_H_ */
