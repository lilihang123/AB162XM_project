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
/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <zephyr/drivers/pinctrl.h>
#include "hal_gpio.h"
#include "hal_eint_internal.h"

static void pinctrl_configure_pin(pinctrl_soc_pin_t pin)
{
    hal_gpio_init(pin.pin_num);
    hal_pinmux_set_function(pin.pin_num,pin.function);
    if((pin.high_impedance == 1)&&(pin.function == 0)){
        hal_gpio_set_high_impedance(pin.pin_num);
    }else if((pin.high_impedance == 0)&&(pin.function == 0)){
        hal_gpio_clear_high_impedance(pin.pin_num);
    }
    hal_gpio_set_direction(pin.pin_num,pin.direction);
    hal_gpio_set_output(pin.pin_num,pin.output);
    if(pin.pullup != 0){
        hal_gpio_pull_up(pin.pin_num);
    }else if(pin.pulldown != 0){
        hal_gpio_pull_down(pin.pin_num);
    }
    else{
        hal_gpio_disable_pull(pin.pin_num);
    }
    if(pin.schmitt){
        hal_gpio_set_schmitt(pin.pin_num);
    }else{
        hal_gpio_clear_schmitt(pin.pin_num);
    }
    if(pin.slew_rate){
        hal_gpio_set_slew_rate(pin.pin_num);
    }else{
        hal_gpio_clear_slew_rate(pin.pin_num);
    }
    if(pin.debounce != 0)
    {
        hal_eint_debonnce_config(pin.pin_num, pin.debounce);
    }
    hal_gpio_set_driving_current(pin.pin_num,pin.drive_strength);
}

int pinctrl_configure_pins(const pinctrl_soc_pin_t *pins, uint8_t pin_cnt,
			   uintptr_t reg)
{
	ARG_UNUSED(reg);
	for (uint8_t i = 0U; i < pin_cnt; i++) {
		pinctrl_configure_pin(*pins++);
	}

	return 0;
}

