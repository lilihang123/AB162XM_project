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
 
#ifndef __APP_BUTTON_H__
#define __APP_BUTTON_H__

#include "application.h"
#include "app_button_combo.h"

#define VIRTUAL_KEY_ID_BASE 0x80

#if defined(CONFIG_AIR_M21_SAMPLE) || defined(CONFIG_AIR_M21_3395)
#define M_KEY_L     0
#define M_KEY_R     1
#define M_KEY_M    25 
#define M_KEY_NK    5
#define M_KEY_PK    4
#define M_KEY_DPI   6
#define M_KEY_RR   45
#define M_MOTION_PIN   18
#define SCROLL_UP_PIN     28
#define SCROLL_DOWN_PIN   29
#define M_KEY_PAIRING  (VIRTUAL_KEY_ID_BASE + 0)
#else
/* LM7: left button=GPIO6, right button=GPIO5 */
#define M_KEY_L     6
#define M_KEY_R     5
#define M_KEY_M    38 //中键
#define M_KEY_NK   24
#define M_KEY_PK   23
// #define M_KEY_DPI  29
#define M_KEY_RR   45//Report rate
#define M_KEY_PAIRING  (VIRTUAL_KEY_ID_BASE + 0)
#define M_MOTION_PIN   18
#endif

#define M_KEY_NOT_PRESSED    0
#define M_KEY_L_PRESSED      1
#define M_KEY_R_PRESSED      2
#define M_KEY_M_PRESSED      4
#define M_KEY_FW_PRESSED     8
#define M_KEY_BW_PRESSED    16
#define M_KEY_LRM_PRESSED    7


#define M_5_KEY_BIT_L      0x01
#define M_5_KEY_BIT_R      0x02
#define M_5_KEY_BIT_M      0x04
#define M_5_KEY_BIT_NK     0x05
#define M_5_KEY_BIT_PK     0x10


#define PRESS_AND_HOLE_LV_0_TO_1     2000  // 2 sec
#define PRESS_AND_HOLE_LV_1_TO_2     1000  // 1 sec
#define PRESS_AND_HOLE_LV_2_TO_3     2000  // 2 sec
#define MULTI_CLICK_GUARD_TIME        400  // 400 ms  这个是检测单个按键，单击 双击，不是给组合键用的

#define PAIRING_KEY_PRESS_AND_HOLD_TIME      (PRESS_AND_HOLE_LV_0_TO_1 + PRESS_AND_HOLE_LV_1_TO_2 )  // 3 sec

uint8_t gpio_init();


uint8_t app_button_ms_key_polling(uint8_t * ms_key);
void app_button_init(uint8_t profile_idx, T_MOUSE_KEY_S *config_key_list);

bool app_button_is_key_pressed();
bool app_button_labtest_combo_key_pressed();

#endif

