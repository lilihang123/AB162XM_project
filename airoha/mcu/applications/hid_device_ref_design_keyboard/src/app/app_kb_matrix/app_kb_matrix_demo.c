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
 #include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include "app_kb_matrix_demo.h"

#if IS_ENABLED(CONFIG_AIR_KB_DEFAULT_MATRIX_ENABLE)

const uint16_t KEY_MATRIX[KEY_MATRIX_MUX_MAX_INDEX * 16] =
{
    KC_LEFT,    KC_DOWN,   KC_RIGHT,    KC_NO,           KC_NO,       KC_NO,      KC_NO,         KC_NO,         KC_NO,       KC_NO,        KC_NO,        KC_NO,        KC_NO,         KC_NO,       KC_NO,         KC_NO,
    FN_KEY,   KC_4,      KC_8,        KC_EQUAL,        KC_Q,        KC_T,       KC_O,          KC_BSLASH,     KC_S,        KC_H,         KC_SCOLON,    KC_LSHIFT,    KC_V,          KC_COMMA,    KC_UP,         KC_LALT,
    KC_2,       KC_6,      KC_0,        KC_DELETE,       KC_E,        KC_U,       KC_LBRACKET,   KC_CAPSLOCK,   KC_F,        KC_K,         KC_ENTER,     KC_X,         KC_N,          KC_SLASH,    KC_LCTRL,      KC_RALT,
    KC_1,       KC_5,      KC_9,        KC_BSPACE,       KC_W,        KC_Y,       KC_P,          KC_HOME,       KC_D,        KC_J,         KC_QUOTE,     KC_Z,         KC_B,          KC_DOT,      KC_PGDOWN,     KC_SPACE,
    KC_3,       KC_7,      KC_MINUS,    KC_TAB,          KC_R,        KC_I,       KC_RBRACKET,   KC_A,          KC_G,        KC_L,         KC_PGUP,      KC_C,         KC_M,          KC_RSHIFT,   KC_LGUI,       FN_KEY
};

const uint16_t FN_KEY_MATRIX[KEY_MATRIX_MUX_MAX_INDEX * 16] =
{
    KC_Q,        KC_W,      KC_E,        KC_NO,           KC_NO,       KC_NO,      KC_NO,         KC_NO,         KC_NO,       KC_NO,        KC_NO,        KC_NO,        KC_NO,         KC_NO,       KC_NO,         KC_NO,
    FN_KEY,      KC2_VOLUME_DECREMENT_RTC,      KC_8,        KC_EQUAL,        KC_Q,        KC_T,       KC_O,          KC_BSLASH,     KC_S,        KC_H,         KC_SCOLON,    KC_LSHIFT,    KC_V,          KC_COMMA,    KC_UP,         KC_LALT,
    FN_02,       KC_6,      FN_00,       KC_DELETE,       KC_E,        KC_U,       KC_LBRACKET,   KC_CAPSLOCK,   KC_F,        KC_K,         KC_ENTER,     KC_X,         KC_N,          KC_SLASH,    KC_LCTRL,      KC_RALT,
    FN_01,       KC2_MUTE_OOC,      KC_9,        KC_BSPACE,       KC_W,        KC_Y,       KC_P,          KC_HOME,       KC_D,        KC_J,         KC_QUOTE,     KC_Z,         KC_B,          KC_DOT,      KC_PGDOWN,     KC_SPACE,
    KC2_VOLUME_INCREMENT_RTC,       KC_7,      KC_MINUS,    KC_TAB,          KC_R,        KC_I,       KC_RBRACKET,   KC_A,          KC_G,        KC_L,         KC_PGUP,      KC_C,         KC_M,          KC_RSHIFT,   KC_LGUI,       FN_KEY
};

// const uint16_t KEY_MATRIX[5 * 16] =
// {
//     KC_0,      KC_1,       KC_2,      KC_3,        KC_4,        KC_5,       KC_6,        KC_7,          KC_8,       KC_9,     KC_A,  KC_B,        KC_C,          KC_D,       KC_E,     KC_F,
// };

const fn_key_callback_t keyboard_fun_ptr_list[KEYBOARD_FUNCTION_POINTER_NUMBER] =
{
    fn_key_callback_fn_0, //FN_00
    fn_key_callback_fn_1, //FN_01
    fn_key_callback_fn_2, //FN_02
    fn_key_callback_fn_3, //FN_03
};

/*fn key api*/
void fn_key_callback_fn_0(uint16_t keycode)
{
    printk("fn_key_callback_FN_NUM_0");
}
void fn_key_callback_fn_1(uint16_t keycode)
{
    printk("fn_key_callback_FN_NUM_1");
}
void fn_key_callback_fn_2(uint16_t keycode){
    printk("fn_key_callback_FN_NUM_2");
}
void fn_key_callback_fn_3(uint16_t keycode){
    printk("fn_key_callback_FN_NUM_3");
}

#endif /* IS_ENABLED(CONFIG_AIR_KB_DEFAULT_MATRIX_ENABLE) */