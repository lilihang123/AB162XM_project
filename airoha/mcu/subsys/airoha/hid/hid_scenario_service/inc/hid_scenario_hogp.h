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

#ifndef __APP_HOG_H__
#define __APP_HOG_H__

#ifdef __cplusplus
extern "C" {
#endif


// #define BT_MODE_NKEY_SPLIT_GROUP


// attribute id
#define ATTRIBUTE_ID_KEYBOARD_CONSUMER   6
#define ATTRIBUTE_ID_KEYBOARD            10
#define ATTRIBUTE_ID_MOUSE               14
#if defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
#if defined(BT_MODE_NKEY_SPLIT_GROUP)
#define ATTRIBUTE_ID_KB_BIT_REP_1        18
#define ATTRIBUTE_ID_KB_BIT_REP_2        22
#define ATTRIBUTE_ID_KB_BIT_REP_3        26
#else
#define ATTRIBUTE_ID_KB_NKEY             18
#endif
#endif
#define ATTRIBUTE_ID_GAME_CONTROLLER     6

#if defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
typedef void (* hid_scenario_hogp_attr_cb)(uint8_t ms_attr, uint8_t kb_std_attr, uint8_t kb_consumer_attr, uint8_t kb_nkey_attr);
#elif defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER) && defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
typedef void (* hid_scenario_hogp_attr_cb)(uint8_t game_controller);
#else
typedef void (* hid_scenario_hogp_attr_cb)(uint8_t ms_attr, uint8_t kb_std_attr, uint8_t kb_consumer_attr);
#endif

typedef struct {
    uint8_t     keys;
    int16_t     x;
    int16_t     y;
    int8_t      wheel;
    int8_t      ac_pan;
}__packed T_MOUSE_REPORT_S;

typedef struct {
    uint8_t    keys;
    int8_t     x;
    int8_t     y;
}__packed T_MOUSE_SAMPLE_REPORT_S;




typedef struct {
    uint8_t combo;
    uint8_t keycode[5];
}__packed T_KEYBOARD_REPORT_STD_S;


typedef struct {
    uint8_t bitmap[5];
}__packed T_KEYBOARD_REPORT_NKEY_S;


typedef struct {
    uint8_t combo;
    uint8_t bitmap[5];
}__packed T_KEYBOARD_REPORT_NKEY_G1_S;

typedef struct {
    uint16_t keycode[2];
    uint8_t num;
}__packed T_KEYBOARD_REPORT_CONSUMER_S;







void hid_scenario_hog_init(hid_scenario_hogp_attr_cb cb);
int hog_notify(uint8_t attr_idx, uint8_t * payload_data, uint8_t payload_data_len);
#else




















#ifdef __cplusplus
}
#endif


#endif
