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

#include "ot_performance_led.h"
#include <zephyr/kernel.h>

/* LED Driver init */
const struct device *led_device = DEVICE_DT_GET(DT_NODELABEL(led));

/* led on/off */
void ot_performance_led_turn_onoff(bool onoff, uint32_t led_number)
{
    if (onoff) {
        printk("led turn on, number: %d\r\n", led_number);
        led_on(led_device, led_number);
    } else {
        printk("led turn off, number: %d\r\n", led_number);
        led_off(led_device, led_number);
    }
}

/* green led [gpio35]*/
void ot_performance_led_green(bool onoff)
{
    ot_performance_led_turn_onoff(onoff, 0);
}

/* red led  [gpio36]*/
void ot_performance_led_red(bool onoff)
{
    ot_performance_led_turn_onoff(onoff, 1);
}

/* White led [gpio37]*/
void ot_performance_led_white(bool onoff)
{
    ot_performance_led_turn_onoff(onoff, 2);
}

/* blue led [gpio34]*/
void ot_performance_led_blue(bool onoff)
{
    ot_performance_led_turn_onoff(onoff, 4);
}

void ot_performance_led_rgbw(uint8_t red, uint8_t green, uint8_t blue, uint8_t white)
{
    if (red) {
        ot_performance_led_red(1);
    } else {
        ot_performance_led_red(0);
    }

    if (green) {
        ot_performance_led_green(1);
    } else {
        ot_performance_led_green(0);
    }

    if (blue) {
        ot_performance_led_blue(1);
    } else {
        ot_performance_led_blue(0);
    }
    
    if (white) {
        ot_performance_led_white(1);
    } else {
        ot_performance_led_white(0);
    }
}