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

 #if defined(AIR_ADC_KEYSCAN_ENABLE)
#include "hid_keycode_id.h"
#include "adc_keyscan.h"

#define KEY_MATRIX_ROWS    {HAL_GPIO_6, HAL_GPIO_7, HAL_GPIO_8}
#define KEY_MATRIX_COLS    {HAL_GPIO_26, HAL_GPIO_27, HAL_GPIO_28, HAL_GPIO_29,HAL_GPIO_30, HAL_GPIO_31, HAL_GPIO_32,HAL_GPIO_33, HAL_GPIO_34, HAL_GPIO_35,HAL_GPIO_36, HAL_GPIO_37, HAL_GPIO_40, HAL_GPIO_41,HAL_GPIO_42, HAL_GPIO_43}
#define KEY_MATRIX_ROWS_NUM 3
#define KEY_MATRIX_COLS_NUM 16
#define KEY_MATRIX_MUX_EN 5
/**/
#define KEY_MATRIX_MUX_YRIGGER_INDEX 3
#define KEY_MATRIX_MUX_MAX_INDEX 5
#define ADC_THRESHOLD 800
extern const uint16_t KEY_MATRIX[KEY_MATRIX_MUX_MAX_INDEX * 16];
extern const uint16_t FN_KEY_MATRIX[KEY_MATRIX_MUX_MAX_INDEX * 16];

#define KEY_MATRIX_FN_KEY_INDEX 16
#define KEYBOARD_FUNCTION_POINTER_NUMBER       20
extern const fn_key_callback_t keyboard_fun_ptr_list[KEYBOARD_FUNCTION_POINTER_NUMBER];
extern void fn_key_callback_fn_0(uint16_t keycode);
extern void fn_key_callback_fn_1(uint16_t keycode);
extern void fn_key_callback_fn_2(uint16_t keycode);
extern void fn_key_callback_fn_3(uint16_t keycode);

#endif /* AIR_ADC_KEYSCAN_ENABLE */