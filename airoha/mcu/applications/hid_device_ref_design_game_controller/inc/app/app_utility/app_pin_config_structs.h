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

#ifndef __APP_PIN_CONSIG_STRUCTS_H__
#define __APP_PIN_CONSIG_STRUCTS_H__



#include "application.h"

#define MAX_PIN_NUMBER 48

#define GPIO_UNDEFINE 0xFF



typedef struct
{
    T_OUTPUT_CTRL_PIN_INFO_S irpt_ena_pin;
    T_OUTPUT_CTRL_PIN_INFO_S scroll_ena_pin;
    T_OUTPUT_CTRL_PIN_INFO_S sensor_nreset_pin;
    T_OUTPUT_CTRL_PIN_INFO_S fuel_gauge_pin;
    T_OUTPUT_CTRL_PIN_INFO_S charge_ena_pin;
    T_OUTPUT_CTRL_PIN_INFO_S led_power_ctrl_pin;
    T_OUTPUT_CTRL_PIN_INFO_S irpt_ena_pin2;
}T_OUTPUT_CTRL_PIN_S;

/* shoubld be aligned with GAME_CONTROLLEER_KEY_INFO_T */
typedef struct
{
    uint8_t d_up_key;
    uint8_t d_down_key;
    uint8_t d_left_key;
    uint8_t d_right_key;
    uint8_t reserved_key0;
    uint8_t reserved_key1;
    uint8_t reserved_key2;
    uint8_t reserved_key3;
    uint8_t a_key;
    uint8_t b_key;
    uint8_t x_key;
    uint8_t y_key;
    uint8_t left_joystick_key;
    uint8_t right_joystick_key;
    uint8_t left_key;
    uint8_t right_key;
    uint8_t home_key;
    uint8_t menu_key;
    uint8_t start_key;
    uint8_t back_key;
    uint8_t external_key0;
    uint8_t external_key1;
    uint8_t external_key2;
    uint8_t external_key3;
    uint8_t external_key4;
    uint8_t external_key5;
    uint8_t external_key6;
    uint8_t external_key7;
    uint8_t external_key8;
    uint8_t external_key9;
    uint8_t external_key10;
    uint8_t external_key11;
}T_DEVICE_KEY_S;

typedef struct
{
    uint8_t led_0;
    uint8_t led_1;
    uint8_t led_2;
}T_SINGLE_LED_PIN_S;

typedef struct
{
    uint8_t ss_bt_mode;
    uint8_t ss_2_4G_mode;
}T_SLIDE_SWITCH_PIN_S;

typedef struct
{
    uint8_t spi_cb;
    uint8_t latch_report;
    uint8_t tx_nack;
    uint8_t dbg_1;
    uint8_t dbg_2;
    uint8_t dbg_3;
}T_DEVICE_DBG_PIN_S;

typedef struct
{
    uint8_t usb_tx;
    uint8_t usb_tx_done;
    uint8_t usb_sof;
}T_USB_DBG_PIN_S;

typedef struct
{
    uint8_t                     hw_dbg_pin[8];
    T_DEVICE_KEY_S              key_list;
    T_SINGLE_LED_PIN_S          single_led;
    T_SLIDE_SWITCH_PIN_S        slide_switch;
    T_DEVICE_DBG_PIN_S          device_dbg;
    T_USB_DBG_PIN_S             usb_dbg;

    T_OUTPUT_CTRL_PIN_S         output_ctrl;
}T_GPIO_PIN_USAGE_LIST_DATA_S;

typedef struct
{
    uint8_t hw_dbg_pin_num;
    T_DEVICE_KEY_S              *key_list_ptr;
    T_SINGLE_LED_PIN_S          *single_led_ptr;
    T_SLIDE_SWITCH_PIN_S        *slide_switch_ptr;
    T_DEVICE_DBG_PIN_S          *device_dbg_ptr;
    T_USB_DBG_PIN_S             *usb_dbg_ptr;
    uint8_t                     *hw_dbg_pin_ptr;
}T_GPIO_PIN_USAGE_LIST_CTRL_S;

typedef struct
{
    T_GPIO_PIN_USAGE_LIST_DATA_S data;
    T_GPIO_PIN_USAGE_LIST_CTRL_S ctrl;
}T_GPIO_PIN_USAGE_LIST_S;

#endif //__APP_PIN_CONSIG_STRUCTS_H__

