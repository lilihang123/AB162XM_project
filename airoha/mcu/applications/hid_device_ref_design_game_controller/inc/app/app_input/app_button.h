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


#define GC_KEY_D_UP        21
#define GC_KEY_D_DOWN      22
#define GC_KEY_D_LEFT      24
#define GC_KEY_D_RIGHT     33
#define GC_RESERVED_KEY0   0xFF
#define GC_RESERVED_KEY1   0xFF
#define GC_RESERVED_KEY2   0xFF
#define GC_RESERVED_KEY3   0xFF
#define GC_KEY_A           13
#define GC_KEY_B           15
#define GC_KEY_X           12
#define GC_KEY_Y           14
#define GC_KEY_JOYS_L      10
#define GC_KEY_JOYS_R      11
#define GC_KEY_LB          16  /* Left Joystick button */
#define GC_KEY_RB          20  /* Right Joystick button */
#define GC_KEY_HOME1       19
#define GC_KEY_START       0xFF
#define GC_KEY_BACK        0xFF
#define GC_KEY_M1          0x80 /*M1 button*/
#define GC_KEY_M2          0x81 /*M2 button*/
#define GC_KEY_M3          0x82 /*M3 button*/
#define GC_KEY_M4          0x83 /*M4 button*/
#define GC_KEY_M5          0x84 /*M5 button*/
#define GC_KEY_M6          0x85 /*M6 button*/
#define GC_KEY_G1          0x88 /*G1 button */
#define GC_KEY_G2          0x89 /*G2 button */
#define GC_KEY_G5          0x8A /*G5 button */
#define GC_KEY_G3          0x8B /*G3 button */
#define GC_KEY_G4          0x8C /*G4 button */
#define GC_KEY_PAIR        0x8D /* Pairing button */
#define GC_KEY_VIEW        0x8E /* View button */
#define GC_KEY_MENU        0x90 /* Mwnu button */
#define GC_KEY_LT_MODE     0x91 /* LT button */
#define GC_KEY_RT_MODE     0x92 /* RT button */

#define GC_KEY_LT_SW       17  //?
#define GC_KEY_RT_SW       23  //?

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


#define PRESS_AND_HOLE_LV_0_TO_1     1000  // 1 sec
#define PRESS_AND_HOLE_LV_1_TO_2     2000  // 2 sec
#define PRESS_AND_HOLE_LV_2_TO_3     2000  // 2 sec
#define PRESS_AND_HOLE_LV_0_TO_2     (PRESS_AND_HOLE_LV_0_TO_1 + PRESS_AND_HOLE_LV_1_TO_2)
#define PRESS_AND_HOLE_LV_0_TO_3     (PRESS_AND_HOLE_LV_0_TO_2 + PRESS_AND_HOLE_LV_2_TO_3)
#define MULTI_CLICK_GUARD_TIME        400  // 400 ms

#define PAIRING_KEY_PRESS_AND_HOLD_TIME      (PRESS_AND_HOLE_LV_0_TO_1 + PRESS_AND_HOLE_LV_1_TO_2 )  // 3 sec

typedef enum {
    APP_BUTTON_STATE_NORMAL,
    APP_BUTTON_STATE_SUSPEND_RESUME,
}T_APP_BUTTON_STATE_E;

uint8_t gpio_init();


void app_button_init(uint8_t profile_idx, T_DEVICE_KEY_S *config_key_list);

bool app_button_is_key_pressed();
bool app_button_labtest_combo_key_pressed();
uint8_t app_button_get_power_off_status();

#endif

