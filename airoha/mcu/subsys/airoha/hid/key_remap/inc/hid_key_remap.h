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
 
#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#ifndef __HID_KEY_REMAP_H__
#define __HID_KEY_REMAP_H__

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include "hid_common.h"
#include "hid_scenario_nvkey.h"
#include "race_cmd.h"
#include "race_xport.h"

#if defined(CONFIG_LOG)
#define DBG_LOGI(module_name, format, ...)   \
        LOG_INF("[srv-i]["module_name"]" format, ## __VA_ARGS__)
#else
#define DBG_LOGI(module_name, format, ...)   \
        printk("[srv-i]["module_name"]"format, ## __VA_ARGS__)
#endif
/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
// #define MS_KEY_REMAP_TEST
// #define AIR_EXPAND_MACRO

/* MACRO DEFINITIONS */
#define KEY_REMAP_VER2_MACRO_KEY_EVENT_IN_BYTES      10
#define KEY_REMAP_VER1_MACRO_KEY_EVENT_IN_BYTES      7
#define KEY_REMAP_MACRO_NAME_LEN                16 /* include ending '\0' */
#define KEY_REMAP_MACRO_PLAY_MODE_LEN           2
#define KEY_REMAP_MACRO_DESCRIP_LEN             (KEY_REMAP_MACRO_NAME_LEN + \
                KEY_REMAP_MACRO_PLAY_MODE_LEN)

#define KEY_REMAP_MACRO_MAX_LEN                 (KEY_REMAP_MACRO_NAME_LEN + \
                KEY_REMAP_MACRO_PLAY_MODE_LEN + \
                KEY_REMAP_VER2_MACRO_KEY_EVENT_IN_BYTES*KEY_REMAP_MACRO_SUPPORT_ITEM_NUM)

#if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE)
/* Each remapping function can be described using up to 5 bytes. */
#define KEY_REMAP_MAX_FUNC_DESC_LEN             5
#else
/* Each remapping function can be described using up to 7 bytes. Fire key expand */
#define KEY_REMAP_MAX_FUNC_DESC_LEN             7
#endif

#define KEY_REMAP_PROFILE_LEN                   (KEY_NUMBER * KEY_REMAP_MAX_FUNC_DESC_LEN)
#define KEY_REMAP_PROFILE_COUNT                 4
#define KEY_REMAP_MAX_PROFILE_IDX               (KEY_REMAP_PROFILE_COUNT-1)
// Version
#define MACRO_VERSION2                          0xE8  /* Add Consumer key */

#define FIRE_PRESS_RELEASE_RATIO                50     /* Each keys press/release time ratio %*/
#define FIRE_KEY_INTERVAL                       30     /* Each keys interval */
#define MACRO_INTERVAL                          10     /* Each macros interval */

// macro[]: [31:24] type, [23:0] relative_time
#define MACRO_PACK(type, rel_time)      ( ((uint32_t)(type) << 24) | ((rel_time) & 0xFFFFFF) )

// x_y[]: [11:0] x, [23:12] y
#define MACRO_XY_PACK(x, y)             ( ((uint32_t)(x) & 0xFFF) | (((uint32_t)(y) & 0xFFF) << 12) )

// 3-byte array to uint32_t
#define ARR3_TO_U24(arr)   ((uint32_t)(arr)[2] | ((uint32_t)(arr)[1] << 8) | ((uint32_t)(arr)[0] << 16))

#if defined (MS_KEY_REMAP_TEST)
#define XY_TO_U24(x, y)   ( ((uint32_t)((x) & 0xFFF)) | (((uint32_t)((y) & 0xFFF)) << 12) )
#define XY_TO_ARR(x, y)   U24_TO_ARR(XY_TO_U24(x, y))
/** Convert 24-bit value to 3-byte array (little endian) */
#define U24_TO_ARR(val) { \
    (uint8_t)(((val) >> 16) & 0xFF), \
    (uint8_t)(((val) >> 8) & 0xFF),  \
    (uint8_t)((val) & 0xFF)          \
}

#if defined (AIR_EXPAND_MACRO)
#define MACRO_MS_KEY(type, offset, duration, key) {type, U24_TO_ARR(offset), .relative_time_in_ms = U24_TO_ARR(duration), .ms_key = key}
#define MACRO_STD_KEY(type, offset, duration, key) {type, U24_TO_ARR(offset), .relative_time_in_ms = U24_TO_ARR(duration), .std_key = key}
#define MACRO_CSM_KEY(type, offset, duration, key) {type, U24_TO_ARR(offset), .relative_time_in_ms = U24_TO_ARR(duration), .consumer_key = key}
#define MACRO_GC_KEY(type, offset, duration, key) {type, U24_TO_ARR(offset), .relative_time_in_ms = U24_TO_ARR(duration), .game_controller_key = key}
/** Pack x and y (each 12 bits, signed) into 24 bits, then to 3-byte array */
#define MACRO_XY(offset, x, y) \
    {MACRO_X_Y_KEYCODE, U24_TO_ARR(offset), U24_TO_ARR(0x000000), .x_y = XY_TO_ARR(x, y) }
#else
#define MACRO_KEY(key, offset, duration) { key, U24_TO_ARR(offset), .relative_time_in_ms = U24_TO_ARR(duration) }
/** Pack x and y (each 12 bits, signed) into 24 bits, then to 3-byte array */
#define MACRO_XY(offset, x, y) \
    { MACRO_X_Y_KEYCODE, U24_TO_ARR(offset), .x_y = XY_TO_ARR(x, y) }
#endif
#endif

#define MACRO_NVKEY_IDX   8  /* Macro nvkey id, key idx bigger than 8 is use another region */
#define MACRO_NVKEY_IDX_2 13 /* Macro nvkey id, key idx bigger than 13 is use another region */

typedef enum {
    /* Key events are not reported. */
    REMAP_TO_DISABLE = 0,

    REMAP_TO_LEFT_KEY,
    REMAP_TO_RIGHT_KEY,
    REMAP_TO_MIDDLE_KEY,
    REMAP_TO_FOURTH_KEY,
    REMAP_TO_FIFTH_KEY,

    /* Remaps the keys on the mouse to certain keys
     * on the keyboard for the convenience of the user.
     */
    REMAP_TO_KBD_KEY,

    /* wired mode: app_mouse_report_rate_change
     * wireless mode: send RACE_SET_REPORT_RATE to dongle
     */
    REMAP_TO_REPORT_RATE_SWITCH,

    /* Remap mouse buttons as macro functions for
     * quick implementation of certain keyboard combinations.
     */
    REMAP_TO_MACRO,

    REMAP_TO_FIRE_KEY,

    REMAP_RESERVED_FUNCTION,         /* reserved function */

    REMAP_TO_DPI_CONTROL,
    
    REMAP_TO_WHEEL_UP,
    REMAP_TO_WHEEL_DOWN,

    REMAP_TO_PAIRING_KEY,

    REMAP_TO_GAME_CONTOLLER_KEY,
    REMAP_TO_LIFT_SENSITIVITY,
    REMAP_TO_RIGHT_SENSITIVITY,
    REMAP_TO_COMBINE_KEY,
    REMAP_TO_CURSOR_MODE,
    REMAP_TO_CHANGE_PROFILE,
    REMAP_TO_GYROSCOPE,
    REMAP_TO_COMPETITIVE_MODE,
} KEY_REMAP_TYPE_E;

extern const uint8_t key_type_len_mapping_table[];

typedef struct {
    uint8_t type;                      /* keycode 0xF0 = MS left, 0xF1 = MS right, 0xF2 = MS middle, 0xF3 = MS Forward, 0xF4 = MS Backward, 0xF5 = Standard, 0xF6 = Consumer, 0xF7 = Game controller, 0xFF = X,Y*/
    uint8_t offset_time_in_ms[3];      /* relative start time */
    uint8_t relative_time_in_ms[3];   /* Key press duration time */
    union {
        uint8_t x_y[3];
        uint8_t ms_key;
        uint8_t std_key;
        uint8_t consumer_key[2];
        uint8_t game_controller_key;
    };
} __attribute__((packed)) T_KEY_REMAP_MACRO_RECORD_VER2_S;

#if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE)
typedef struct {
    uint8_t key_code;                /* only standard keycode 0xF0 = MS left, 0xF1 = MS right, 0xF2 = MS middle, 0xF3 = MS Forward, 0xF4 = MS Backward*/
    uint8_t offset_time_in_ms[3];    /* relative start time */
    union {
        uint8_t x_y[3];
        uint8_t relative_time_in_ms[3];
    };
} __attribute__((packed)) T_KEY_REMAP_MACRO_RECORD_VER1_S;
#endif  /* CONFIG_AIR_PRODUCT_TYPE_MOUSE */

typedef struct {
    uint8_t type;                      /* keycode 0xF0 = MS left, 0xF1 = MS right, 0xF2 = MS middle, 0xF3 = MS Forward, 0xF4 = MS Backward, 0xF5 = Standard, 0xF6 = Consumer, 0xF7 = Game controller */
    union {
        uint8_t x_y[3];
        uint8_t ms_key;
        uint8_t std_key;
        uint8_t consumer_key[2];
        uint8_t game_controller_key;
    };
} __attribute__((packed)) T_KEY_REMAP_FIRE_RECORD_S;

typedef struct {
    uint32_t abs_time;
    uint8_t type;
    union {
        uint32_t key_code;
        uint32_t x_y;
    };
}__attribute__((packed)) T_MACRO_EVENT_S;

typedef struct {
    char name[16];          /* The macro name represented by the ascii code including the terminator. */
    uint8_t play_mode;
    uint8_t repeat_times;
    uint8_t version;
    T_KEY_REMAP_MACRO_RECORD_VER2_S rcds[4];
} __attribute__((packed)) T_KEY_REMAP_MACRO_PARAM_S;
/******************************************************************************/
/* functions                                                                  */
/******************************************************************************/
uint32_t hid_key_remap_init(uint8_t profile_idx);
uint8_t hid_key_remap_delete_macro(const uint8_t macro_name[], uint8_t name_len, uint8_t profile_idx, uint8_t *s_key_remap_profile);
uint8_t hid_key_remap_set(uint8_t key_id, KEY_REMAP_TYPE_E key_type, uint8_t *setting, uint16_t len, uint8_t *s_key_remap_profile, uint8_t profile_idx);
uint32_t hid_key_remap_get(uint8_t key_id, KEY_REMAP_TYPE_E *key_type, uint8_t *setting, uint8_t *s_key_remap_profile, uint8_t profile_idx);
void hid_kr_fill_kb_data(uint8_t *p_key_func_descrip, T_HID_KEY_REMAP_S *remapped_data);
uint32_t hid_kr_get_macro_nvkey_id(uint8_t key_idx, uint8_t profile_idx);
uint32_t hid_key_remap_enable(uint8_t *s_key_remap_default_profile, uint8_t *s_key_remap_profile, uint8_t *key_bit);
void hid_kr_fill_macro_data(T_HID_KEY_REMAP_S *remapped_data, uint8_t key_idx, uint8_t profile_idx);
void hid_kr_fill_fire_data(uint8_t *s_key_remap_profile, T_HID_KEY_REMAP_S *remapped_data, uint8_t key_idx);
#endif //__HID_KEY_REMAP_H__
#endif
