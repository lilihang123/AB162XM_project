/* Copyright Statement:
 *
 * (C) 2024  Airoha Technology Corp. All rights reserved.
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
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
 * RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
 * TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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
#if defined(CONFIG_IO_EXPANDER_AW95124)
 #ifndef _IO_EXPANDER_SENSOR_MGR_H_
 #define _IO_EXPANDER
#include "io_expander.h"


enum io_expander_button_id{
    BUTTON_M1 = 0 ,
    BUTTON_M2,
    BUTTON_M3,
    BUTTON_M4,
    BUTTON_M5,
    BUTTON_M6,
    BUTTON_G1 = 8,
    BUTTON_G2,
    BUTTON_G3,
    BUTTON_G4,
    BUTTON_G5,
    BUTTON_PAIRING,
    BUTTON_VIEW,
    BUTTON_VLED_EN,
    BUTTON_MENU,
    BUTTON_LT_MODE,
    BUTTON_RT_MODE,
 };

typedef void (*sw_debounce_io_epxander_callback_t)(uint32_t *keys);


/*
description:_get_all_interrupt_status
*/
uint32_t io_expander_mgr_get_all_interrupt_status(void);

/*
description: get the current input status of all pins
return: the current input status of all pins
*/
uint32_t io_expander_mgr_get_all_input_status(void);
/*
description: set the debounce parameters for the io expander
param sample_count: the number of samples to take for each key press, default 1
param debounce_time: the debounce time in ms, defaulat 25ms
*/
void io_expander_mgr_debounce_set(uint8_t pin_num, uint8_t debounce_time, uint8_t default_state);
/*
description: register a callback function to be called when a key is pressed or released
param sw_debounce_io_epxander_callback_t: the callback function to be called when a key is pressed
return: 0 if success, otherwise error code
*/
int io_expander_mgr_register_callback(sw_debounce_io_epxander_callback_t callback);
/*
description: pin configure
param pin_num: the pin number to be configured (0~23)
param config:
typedef struct io_expander_pin_config 
{
   uint32_t pin_dir:4;
   uint32_t pin_driver:4;
   uint32_t pin_pull:4;
   uint32_t pin_irq_en:4;
   uint32_t pin_irq_type:4;
   uint32_t reserved:12;
}io_expander_pin_config_t; in io_expander.h
return: 0 if success, otherwise error code
*/
int io_expander_mgr_pin_config_set(uint32_t pin_num, void* config);
/*
description: set the interrupt type for a specific pin
param pin_num: the pin number to be configured (0~23)
param irq_type: 
enum aw951xx_interrupt_trigger_type {
	AW951XX_INI_TRIGGER_RISING,
	AW951XX_INI_TRIGGER_FALLING,
	AW951XX_INI_TRIGGER_DUAL_EDGE,
	AW951XX_INI_TRIGGER_HIGH,
	AW951XX_INI_TRIGGER_LOW,
}; in io_expander_sensor.h
return: 0 if success, otherwise error code
*/
int io_expander_mgr_pin_irq_type_config_set(uint32_t pin_num, uint32_t irq_type);
/*
description: configure the pin irq enable or disable
param pin_num: the pin number to be configured (0~23)
param enable:  true to enable, false to disable
return: 0 if success, otherwise error code
*/
int io_expander_mgr_pin_irq_enabel_set(uint32_t pin_num, bool enable);
/*
description: configure the pin as input
param pin_num: the pin number to be configured (0~23)
return: 0 if success, otherwise error code
*/
int io_expander_mgr_pin_dir_input_set(uint32_t pin_num);
/*
description: configure the pin as output and set the initial value
param pin_num: the pin number to be configured (0~23)
param value: the initial value tob e set (0 or 1)
return: 0 if success, otherwise error code
*/
int io_expander_mgr_pin_dir_output_set(uint32_t pin_num, uint32_t value);
/*
description: Set the pull up or pull down setting for a specific pin.: 
param pin_num: the pin number to be configured (0~23)
param pull: the pull up or pull down setting (2: no pull, 1: pull up, 0: pull down)
return: 0 if success, otherwise error code
*/
int io_expander_mgr_pin_pull_set(uint32_t pin_num, uint32_t pull);
/*
description: Set the value of a specific pin.:
param pin_num: the pin number to be configured (0~23)
param value: the initial value to be set (0: low, 1: high)
return: 0 if success, otherwise error code
*/
int io_expander_mgr_pin_value_set(uint32_t pin_num, uint32_t value);

int io_expander_mgr_enter_low_power(void);

int io_expander_mgr_exit_low_power(void);

void io_expander_mgr_init(void);

void io_expander_mgr_deinit(void);
 #endif // _IO_EXPANDER_SENSOR_MGR_H_
 #endif //CONFIG_IO_EXPANDER_AW95124