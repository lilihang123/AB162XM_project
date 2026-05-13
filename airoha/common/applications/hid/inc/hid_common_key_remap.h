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
#if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#ifndef _HID_COMMON_KEY_REMAP_H_
#define _HID_COMMON_KEY_REMAP_H_

#include "hid_common_report_rate.h"
/* Public define -------------------------------------------------------------*/
#if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_PRODUCT_TYPE_MOUSE)
    #if defined (AIR_WHEEL_REMAP) || defined (CONFIG_AIR_WHEEL_REMAP)
    #define KEY_NUMBER 10
    #else
    #define KEY_NUMBER 8
    #endif
#elif defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    #define KEY_NUMBER 36
#else
    #define KEY_NUMBER 8
#endif

#define KEY_REMAP_MACRO_SUPPORT_ITEM_NUM  35
#define KEY_REMAP_MACRO_EVENT_NUM         KEY_REMAP_MACRO_SUPPORT_ITEM_NUM * 2 + 1

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
typedef enum {
    LT_LIGHT_PRESS_IDX = 0,
    LT_DEEP_PRESS_IDX,
    RT_LIGHT_PRESS_IDX,
    RT_DEEP_PRESS_IDX,
}T_GAMEPAD_KEY_IDX_E;
#define LT_KEY_BIT                    (0x01 << 4)
#define RT_KEY_BIT                    (0x01 << 5)
#define MAX_DEBOUNCE_COUNT(rr_idx)    RR_IDX_TO_REPORT_RATE(rr_idx) >> 4
#define FIRST_DEBOUNCE                50 /* first level debounce, us */
#define SECOND_DEBOUNCE               30 /* second level debounce, us */
#define LT_MODE_BIT                   0x40
#define RT_MODE_BIT                   0x80
#endif

#define KEY_BIT_DISABLE              0x00
#define M_KEY_BIT_L                  0x01
#define M_KEY_BIT_R                  0x02
#define M_KEY_BIT_M                  0x04
#define M_KEY_BIT_PK                 0x08
#define M_KEY_BIT_NK                 0x10

#if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_PRODUCT_TYPE_MOUSE)

#if defined (AIR_BASIC_LA_DEBUG)
#define M_KEY_BIT_DPI                0x04
#define M_KEY_BIT_RR                 0x08
#else
#define M_KEY_BIT_DPI                0x20
#define M_KEY_BIT_RR                 0x40
#endif
#define M_KEY_BIT_PAIRING            0x80

#if defined (AIR_WHEEL_REMAP) || defined (CONFIG_AIR_WHEEL_REMAP)
#define WHEEL_UP_BIT           0x40000000
#define WHEEL_DOWN_BIT         0x80000000
#endif
#define MOUSE_XY_MACRO_BIT     0x80000000
#endif

#define KC_LCTRL               0xE0
#define KC_LSHIFT              0xE1
#define KC_LALT                0xE2
#define KC_LGUI                0xE3
#define KC_RCTRL               0xE4
#define KC_RSHIFT              0xE5
#define KC_RALT                0xE6
#define KC_RGUI                0xE7

#define LCTRL_VALUE_IN_COMBO    0x01
#define LSHIFT_VALUE_IN_COMBO   0x02
#define LALT_VALUE_IN_COMBO     0x04
#define LWIN_VALUE_IN_COMBO     0x08
#define RCTRL_VALUE_IN_COMBO    0x10
#define RSHIFT_VALUE_IN_COMBO   0x20
#define RALT_VALUE_IN_COMBO     0x40
#define RWIN_VALUE_IN_COMBO     0x80

#define L_KEY_KEYCODE             0xF0
#define MACRO_STD_KEYCODE         0xF5
#define MACRO_CONSUMER_KEYCODE    0xF6
#define MACRO_GAME_CONTROLLER_KEY 0xF7
#define MACRO_X_Y_KEYCODE         0xFF

#define MACRO_TYPE(val)                 ( ((val) >> 24) & 0xFF )
#define MACRO_REL_TIME(val)             ( (val) & 0xFFFFFF )

/** Extract signed x (12 bits, two's complement) from x_y[] and assign to int */
#define MACRO_X_SIGNED(val)  ( ((int32_t)((val) & 0xFFF) << 20) >> 20 )
/** Extract signed y (12 bits, two's complement) from x_y[] and assign to int */
#define MACRO_Y_SIGNED(val)  ( ((int32_t)(((val) >> 12) & 0xFFF) << 20) >> 20 )

/* Public typedef ------------------------------------------------------------*/
typedef enum{
    NO_REMAP,
    REMAP_MS_KEY,
    REMAP_KB_STD,
    REMAP_KB_CONSUMER,
    MACRO_REMAP,
    MACRO_CONTINUE,
    #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_PRODUCT_TYPE_MOUSE)
    REMAP_TO_RR,
    REMAP_TO_DPI,
    #if defined (AIR_WHEEL_REMAP) || defined (CONFIG_AIR_WHEEL_REMAP)
    REMAP_TO_SCROLL_UP,
    REMAP_TO_SCROLL_DOWN,
    #endif
    REMAP_TO_PAIRING,
    #elif defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    REMAP_GAME_CONTROLLER_KEY,
    REMAP_GAME_CONTROLLER_LT,
    REMAP_GAME_CONTROLLER_RT,
    REMAP_LIFT_SENSITIVITY,
    REMAP_RIGHT_SENSITIVITY,
    REMAP_CURSOR_MODE,
    REMAP_CHANGE_PROFILE,
    REMAP_GYROSCOPE,
    REMAP_COMPETITIVE_MODE,
    #endif
}T_HID_KEY_REMAP_STATUS_E;

typedef enum {
    KEY_EVENT_NONE,
    KEY_EVENT_STD_PRESS,
    KEY_EVENT_STD_RELEASE,
    KEY_EVENT_CSM_PRESS,
    KEY_EVENT_CSM_RELEASE,
    KEY_EVENT_MS_PRESS,
    KEY_EVENT_MS_RELEASE,
    #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_PRODUCT_TYPE_MOUSE)
    KEY_EVENT_MOUSE_XY,
    #endif
    #if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    KEY_EVENT_GC_KEY_PRESS,
    KEY_EVENT_GC_KEY_RELEASE,
    KEY_EVENT_GC_LT_PRESS,
    KEY_EVENT_GC_LT_RELEASE,
    KEY_EVENT_GC_RT_PRESS,
    KEY_EVENT_GC_RT_RELEASE,
    #endif
} T_KEY_EVENT_E;

typedef enum {
    REPEAT_SPECIFIED_TIMES,
    REPEAT_UNTIL_THE_KEY_RELEASE,
    REPEAT_UNTIL_ANY_KEY_PRESS,
} T_MACRO_PLAY_MODE_E;

typedef enum {
    M_KEY_L_IDX,
    M_KEY_R_IDX,

    #if !defined (AIR_BASIC_LA_DEBUG)
    M_KEY_M_IDX,
    M_KEY_NK_IDX,
    M_KEY_PK_IDX,
    #endif

    #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_PRODUCT_TYPE_MOUSE)
    M_KEY_DPI_IDX,
    M_KEY_RR_IDX,
    M_KEY_PAIRING_IDX,
    #if defined (AIR_WHEEL_REMAP) || defined (CONFIG_AIR_WHEEL_REMAP)
    M_WHEEL_UP_IDX,
    M_WHEEL_DOWN_IDX,
    #endif
    #endif
} T_KEY_BIT_IDX_E;

#if defined(AIR_PRODUCT_TYPE_MOUSE)
#if defined(AIR_MOUSE_9B_DATA)
typedef struct {
    uint8_t dummy_2;
    uint8_t combo;
    uint8_t keycode[2];
    int8_t x_y[3];
    uint8_t dummy_1;
    uint8_t report_id;
} __attribute__((__packed__))T_HID_2_4G_REPORT_KB_STD2_XY_S;

typedef struct {
    uint8_t dummy_2;
    uint16_t consumer;
    uint8_t numeric_key_pad;
    int8_t x_y[3];
    uint8_t dummy_1;
    uint8_t report_id;
} __attribute__((__packed__)) T_HID_2_4G_REPORT_KB_CONSUMER1_XY_S;
#else
typedef struct {
    int8_t last_x_y;
    uint8_t combo;
    uint8_t keycode[2];
    int8_t x_y[2];
    uint8_t report_id;
    uint8_t dummy;
} __attribute__((__packed__))T_HID_2_4G_REPORT_KB_STD2_XY_S;

typedef struct {
    int8_t last_x_y;
    uint16_t consumer;
    uint8_t numeric_key_pad;
    int8_t x_y[2];
    uint8_t report_id;
    uint8_t dummy;
} __attribute__((__packed__)) T_HID_2_4G_REPORT_KB_CONSUMER1_XY_S;
#endif /* AIR_MOUSE_9B_DATA */
#endif /* AIR_PRODUCT_TYPE_MOUSE */

typedef struct{
    uint32_t    ms_k;
    int32_t     ms_z1;
    uint32_t    kb_std[2];
    uint32_t    kb_consumer;
    #if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    uint32_t    gc_k;
    uint32_t    gc_lt;
    uint32_t    gc_rt;
    #endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */
}T_REMAP_VALUES_S;

typedef struct{
    uint32_t status;   
    union {
        uint32_t item;              /* (1byte) MS key / (2bytes) std+combo key / (2bytes)consumer key / (3btyes) DPI type and value */
        struct {
            uint16_t play_mode;
            uint16_t repeat_times;
            uint32_t macro[KEY_REMAP_MACRO_EVENT_NUM];     /* Macro record : relative_time (24 bits), type (uint8_t) */
            union {                 /* x_y value (24 bits)/ keycode (uint8_t) */
                uint32_t keycode[KEY_REMAP_MACRO_EVENT_NUM];
                #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_PRODUCT_TYPE_MOUSE)
                uint32_t x_y[KEY_REMAP_MACRO_EVENT_NUM];
                #endif
            };
        };
    };
}__attribute__((__packed__)) T_HID_KEY_REMAP_S;

typedef struct{
    uint32_t status;   
    union {
        uint32_t item;              /* (1byte) MS key / (2bytes) std+combo key / (2bytes)consumer key / (3btyes) DPI type and value */
        struct {
            uint16_t play_mode;
            uint16_t repeat_times;
            uint32_t macro;     /* Macro record : relative_time (24 bits), type (uint8_t) */
            union {                 /* x_y value (24 bits)/ keycode (uint8_t) */
                uint32_t keycode;
                #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_PRODUCT_TYPE_MOUSE)
                uint32_t x_y;
                #endif
            };
        };
    };
}__attribute__((__packed__)) T_HID_KEY_REMAP_BACKEND_S;

typedef struct{
    uint32_t status;   
    uint32_t item;              /* MS key / Game controller key */
}__attribute__((__packed__)) T_HID_KEY_REMAP_FRONTEND_S;
#endif /* _HID_COMMON_KEY_REMAP_H_ */
#endif /* AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */