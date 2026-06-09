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
 
 
#ifndef __GESTURE_HH__
#define __GESTURE_HH__
#include "hal_platform.h"

#if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) || defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD) || defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
#include "hid_common.h"
#else
// for the projects do not enable CONFIG_AIR_HID_COMMON_SERVICE
typedef struct {
    uint32_t combo_bit_00_31;
    uint32_t combo_bit_32_63;
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    uint32_t combo_bit_64_95;
#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */
}T_AIR_COMBO_KEY_S;
#endif

typedef enum {
    INPUT_PULL_NONE = 0,    /** Input pull none / floating */
    INPUT_PULL_UP,      /** Input pull up */
    INPUT_PULL_DOWN,    /** Input pull down */
} T_INPUT_PULL_OPT_E;

typedef enum {
    GESTURE_CFG_OPT_DISABLE_KEY_IRQ,      /** Disable the gpio interrupts specified in the key list*/
    GESTURE_CFG_OPT_ENABLE_KEY_IRQ,       /** Enable  the gpio interrupts specified in the key list*/
    GESTURE_CFG_OPT_DISABLE_EINT_COUNTER, /** Disable the gpio interrupts event counter*/
    GESTURE_CFG_OPT_ENABLE_EINT_COUNTER,  /** Enable  the gpio interrupts event counter*/
    GESTURE_CFG_OPT_DISABLE_PULL          /** Disable the internal pull-up/pull-down of the gpio pins in the regeristed key list */
} T_GESTURE_CONFIG_OPT_E;




typedef enum {
    AIRO_STATUS_FAIL                = -2,     /**< Failed to execute.*/
    AIRO_STATUS_INVALID_PARAM       = -1,     /**< Invalid input pin number. */
    AIRO_STATUS_SUCCESS              = 0      /**< Executed successfully. */
} airo_key_status_t;




/** @brief The click event type mask of the airokey framework. */
#define AK_CLICK_TYPE_MASK                    0x10

/** @brief The long press release event type mask of the airokey framework. */
#define AK_LONG_PRESS_RELEASE_TYPE_MASK       0x20

/** @brief The long press release event type mask of the airokey framework. */
#define AK_CLICK_AND_LONG_PRESS_RELEASE_TYPE_MASK       0x30


/** @brief The press event type mask of the airokey framework. */
#define AK_PRESS_MASK                           0x80

/** @brief The long press event type mask of the airokey framework. */
#define AK_LONG_PRESS_TYPE_MASK                 0x90

/** @brief The multi click and long press event type mask of the airokey framework. */
#define AK_CLICK_AND_LONG_PRESS_TYPE_MASK       0xA0

/** @brief The combo key event type mask of the airokey framework. */
#define AK_COMBO_HOLD_LV1_TYPE_MASK             0xB0
#define AK_COMBO_HOLD_LV2_TYPE_MASK             0xC0
#define AK_COMBO_HOLD_LV3_TYPE_MASK             0xD0





/** @brief All the supported events of the airokey framework. */
typedef enum {
    // Events triggered when a key is released.
AK_RELEASE              = 0x00,                                       /**< A key is hardware released.*/

    AK_SHORT_CLICK          = AK_CLICK_TYPE_MASK  | 1,              /**< A key is short-clicked. */
    AK_DOUBLE_CLICK         = AK_CLICK_TYPE_MASK  | 2,              /**< A key is double-clicked */
    AK_TRIPLE_CLICK         = AK_CLICK_TYPE_MASK  | 3,              /**< A key is triple-clicked. */
    AK_4_CLICK              = AK_CLICK_TYPE_MASK  | 4,              /**< A key is 4-clicked. */
    AK_5_CLICK              = AK_CLICK_TYPE_MASK  | 5,              /**< A key is 5-clicked. */
    AK_6_CLICK              = AK_CLICK_TYPE_MASK  | 6,              /**< A key is 6-clicked. */
    AK_7_CLICK              = AK_CLICK_TYPE_MASK  | 7,              /**< A key is 7-clicked. */
    AK_8_CLICK              = AK_CLICK_TYPE_MASK  | 8,              /**< A key is 8-clicked. */
    AK_9_CLICK              = AK_CLICK_TYPE_MASK  | 9,              /**< A key is 9-clicked. */

    AK_LONG_PRESS_RELEASE_1 = AK_LONG_PRESS_RELEASE_TYPE_MASK | 1,  /**< A special event, a key is released after AK_LONG_PRESS_1.*/
    AK_LONG_PRESS_RELEASE_2 = AK_LONG_PRESS_RELEASE_TYPE_MASK | 2,  /**< A special event, a key is released after AK_LONG_PRESS_2.*/
    AK_LONG_PRESS_RELEASE_3 = AK_LONG_PRESS_RELEASE_TYPE_MASK | 3,  /**< A special event, a key is released after AK_LONG_PRESS_3.*/

    AK_SLONG_RELEASE        = AK_CLICK_AND_LONG_PRESS_RELEASE_TYPE_MASK | 1,                                       /**< A special event, a key is released after AK_SLONG.*/
    AK_DLONG_RELEASE        = AK_CLICK_AND_LONG_PRESS_RELEASE_TYPE_MASK | 2,                                       /**< A special event, a key is released after AK_DLONG.*/
    AK_TLONG_RELEASE        = AK_CLICK_AND_LONG_PRESS_RELEASE_TYPE_MASK | 3,                                       /**< A special event, a key is released after AK_TLONG.*/
    AK_4LONG_RELEASE        = AK_CLICK_AND_LONG_PRESS_RELEASE_TYPE_MASK | 4,                                       /**< A special event, a key is released after AK_4LONG.*/
    AK_5LONG_RELEASE        = AK_CLICK_AND_LONG_PRESS_RELEASE_TYPE_MASK | 5,                                       /**< A special event, a key is released after AK_5LONG.*/
    AK_6LONG_RELEASE        = AK_CLICK_AND_LONG_PRESS_RELEASE_TYPE_MASK | 6,                                       /**< A special event, a key is released after AK_6LONG.*/
    AK_7LONG_RELEASE        = AK_CLICK_AND_LONG_PRESS_RELEASE_TYPE_MASK | 7,                                       /**< A special event, a key is released after AK_7LONG.*/
    AK_8LONG_RELEASE        = AK_CLICK_AND_LONG_PRESS_RELEASE_TYPE_MASK | 8,                                       /**< A special event, a key is released after AK_8LONG.*/
    AK_9LONG_RELEASE        = AK_CLICK_AND_LONG_PRESS_RELEASE_TYPE_MASK | 9,                                       /**< A special event, a key is released after AK_9LONG.*/

    // Events triggered when a key is pressed.
    AK_PRESS                = AK_PRESS_MASK | 0,                                       /**0x80 128 < A key is hardware pressed.*/
    //AK_REPEAT               = 0x81,                                       /**< A key remains pressed after the last long press event is issued. */

    AK_LONG_PRESS_LV_1         = AK_LONG_PRESS_TYPE_MASK | 1,          /**< A key is long pressed. */
    AK_LONG_PRESS_LV_2         = AK_LONG_PRESS_TYPE_MASK | 2,          /**< A key is long pressed. */
    AK_LONG_PRESS_LV_3         = AK_LONG_PRESS_TYPE_MASK | 3,          /**< A key is long pressed. */

    AK_SLONG                = AK_CLICK_AND_LONG_PRESS_TYPE_MASK | 1,                                       /**< A key is single-clicked and then long pressed. */
    AK_DLONG                = AK_CLICK_AND_LONG_PRESS_TYPE_MASK | 2,                                       /**< A key is double-clicked and then long pressed. */
    AK_TLONG                = AK_CLICK_AND_LONG_PRESS_TYPE_MASK | 3,                                       /**< A key is tripple-clicked and then long pressed. */
    AK_4LONG                = AK_CLICK_AND_LONG_PRESS_TYPE_MASK | 4,                                       /**< A key is 4-clicked and then long pressed. */
    AK_5LONG                = AK_CLICK_AND_LONG_PRESS_TYPE_MASK | 5,                                       /**< A key is 5-clicked and then long pressed. */
    AK_6LONG                = AK_CLICK_AND_LONG_PRESS_TYPE_MASK | 6,                                       /**< A key is 6-clicked and then long pressed. */
    AK_7LONG                = AK_CLICK_AND_LONG_PRESS_TYPE_MASK | 7,                                       /**< A key is 7-clicked and then long pressed. */
    AK_8LONG                = AK_CLICK_AND_LONG_PRESS_TYPE_MASK | 8,                                       /**< A key is 8-clicked and then long pressed. */
    AK_9LONG                = AK_CLICK_AND_LONG_PRESS_TYPE_MASK | 9,                                       /**< A key is 9-clicked and then long pressed. */
    /*1级100MS触发*/
    AK_COMBO_HOLD_LV1_0         = AK_COMBO_HOLD_LV1_TYPE_MASK  | 0,      /**< A combo key event corresponse to the 1st combo in combo_key_list */
    AK_COMBO_HOLD_LV1_1         = AK_COMBO_HOLD_LV1_TYPE_MASK  | 1,      /**< A combo key event corresponse to the 2nd combo in combo_key_list */
    AK_COMBO_HOLD_LV1_2         = AK_COMBO_HOLD_LV1_TYPE_MASK  | 2,      /**< A combo key event corresponse to the 3rd combo in combo_key_list */
    AK_COMBO_HOLD_LV1_3         = AK_COMBO_HOLD_LV1_TYPE_MASK  | 3,      /**< A combo key event corresponse to the 4th combo in combo_key_list */
    AK_COMBO_HOLD_LV1_4         = AK_COMBO_HOLD_LV1_TYPE_MASK  | 4,      /**< A combo key event corresponse to the 5th combo in combo_key_list */
    AK_COMBO_HOLD_LV1_5         = AK_COMBO_HOLD_LV1_TYPE_MASK  | 5,      /**< A combo key event corresponse to the 6th combo in combo_key_list */
    AK_COMBO_HOLD_LV1_6         = AK_COMBO_HOLD_LV1_TYPE_MASK  | 6,      /**< A combo key event corresponse to the 7th combo in combo_key_list */
    AK_COMBO_HOLD_LV1_7         = AK_COMBO_HOLD_LV1_TYPE_MASK  | 7,      /**< A combo key event corresponse to the 8th combo in combo_key_list */
    AK_COMBO_HOLD_LV1_8         = AK_COMBO_HOLD_LV1_TYPE_MASK  | 8,      /**< A combo key event corresponse to the 9th combo in combo_key_list */
    AK_COMBO_HOLD_LV1_9         = AK_COMBO_HOLD_LV1_TYPE_MASK  | 9,      /**< A combo key event corresponse to the 10th combo in combo_key_list */
    /*2级3S触发*/
    AK_COMBO_HOLD_LV2_0         = AK_COMBO_HOLD_LV2_TYPE_MASK  | 0,      /**< A combo key event corresponse to the 1st combo in combo_key_list */
    AK_COMBO_HOLD_LV2_1         = AK_COMBO_HOLD_LV2_TYPE_MASK  | 1,      /**< A combo key event corresponse to the 2nd combo in combo_key_list */
    AK_COMBO_HOLD_LV2_2         = AK_COMBO_HOLD_LV2_TYPE_MASK  | 2,      /**< A combo key event corresponse to the 3rd combo in combo_key_list */
    AK_COMBO_HOLD_LV2_3         = AK_COMBO_HOLD_LV2_TYPE_MASK  | 3,      /**< A combo key event corresponse to the 4th combo in combo_key_list */
    AK_COMBO_HOLD_LV2_4         = AK_COMBO_HOLD_LV2_TYPE_MASK  | 4,      /**< A combo key event corresponse to the 5th combo in combo_key_list */
    AK_COMBO_HOLD_LV2_5         = AK_COMBO_HOLD_LV2_TYPE_MASK  | 5,      /**< A combo key event corresponse to the 6th combo in combo_key_list */
    AK_COMBO_HOLD_LV2_6         = AK_COMBO_HOLD_LV2_TYPE_MASK  | 6,      /**< A combo key event corresponse to the 7th combo in combo_key_list */
    AK_COMBO_HOLD_LV2_7         = AK_COMBO_HOLD_LV2_TYPE_MASK  | 7,      /**< A combo key event corresponse to the 8th combo in combo_key_list */
    AK_COMBO_HOLD_LV2_8         = AK_COMBO_HOLD_LV2_TYPE_MASK  | 8,      /**< A combo key event corresponse to the 9th combo in combo_key_list */
    AK_COMBO_HOLD_LV2_9         = AK_COMBO_HOLD_LV2_TYPE_MASK  | 9,      /**< A combo key event corresponse to the 10th combo in combo_key_list */

    /*3级30S触发*/
    AK_COMBO_HOLD_LV3_0         = AK_COMBO_HOLD_LV3_TYPE_MASK  | 0,      /**< A combo key event corresponse to the 1st combo in combo_key_list */
    AK_COMBO_HOLD_LV3_1         = AK_COMBO_HOLD_LV3_TYPE_MASK  | 1,      /**< A combo key event corresponse to the 2nd combo in combo_key_list */
    AK_COMBO_HOLD_LV3_2         = AK_COMBO_HOLD_LV3_TYPE_MASK  | 2,      /**< A combo key event corresponse to the 3rd combo in combo_key_list */
    AK_COMBO_HOLD_LV3_3         = AK_COMBO_HOLD_LV3_TYPE_MASK  | 3,      /**< A combo key event corresponse to the 4th combo in combo_key_list */
    AK_COMBO_HOLD_LV3_4         = AK_COMBO_HOLD_LV3_TYPE_MASK  | 4,      /**< A combo key event corresponse to the 5th combo in combo_key_list */
    AK_COMBO_HOLD_LV3_5         = AK_COMBO_HOLD_LV3_TYPE_MASK  | 5,      /**< A combo key event corresponse to the 6th combo in combo_key_list */
    AK_COMBO_HOLD_LV3_6         = AK_COMBO_HOLD_LV3_TYPE_MASK  | 6,      /**< A combo key event corresponse to the 7th combo in combo_key_list */
    AK_COMBO_HOLD_LV3_7         = AK_COMBO_HOLD_LV3_TYPE_MASK  | 7,      /**< A combo key event corresponse to the 8th combo in combo_key_list */
    AK_COMBO_HOLD_LV3_8         = AK_COMBO_HOLD_LV3_TYPE_MASK  | 8,      /**< A combo key event corresponse to the 9th combo in combo_key_list */
    AK_COMBO_HOLD_LV3_9         = AK_COMBO_HOLD_LV3_TYPE_MASK  | 9,      /**< A combo key event corresponse to the 10th combo in combo_key_list */

    AK_INVALID              = 0xFF,                                       /**< A key is pressed but it does not match any event.*/
} airoha_key_event_t;


typedef void(*airo_key_callback_t)(airoha_key_event_t event, uint8_t key_id);

typedef struct {
    airo_key_callback_t key_handle_cb;
    uint32_t hold_timeout_ms;               // Press and Hold time
    uint32_t hold_timeout_LP2_ms;           // The hold time between AK_LONG_PRESS_1 and  AK_LONG_PRESS_2 
    uint32_t hold_timeout_LP3_ms;           // The hold time between AK_LONG_PRESS_2 and  AK_LONG_PRESS_3 
    uint32_t click_timeout_ms;              // time to recognize single, double, tripple click
    const uint8_t* key_list;                // Key list
    uint8_t key_list_size;                  // Key list size
    const T_AIR_COMBO_KEY_S* combo_key_list;         // Combo key list
    uint8_t combo_key_list_size;            // Combo key list size
    uint8_t *debounce_time_list;     // Debounce time
}T_AIROHA_KEY_CONFIGURATION_S;


airo_key_status_t airo_key_init(T_AIROHA_KEY_CONFIGURATION_S * cfg);
uint8_t airo_key_get_gpio_id_by_index(uint8_t idx);
uint8_t airo_key_get_key_index(uint8_t gpio_id);
uint32_t airo_key_read_all_key_status(uint32_t *all_key_status_0, uint32_t *all_key_status_1);
airo_key_status_t gesture_key_reconfiguration(uint8_t* key_list, uint8_t key_list_size, uint8_t config_option);
void airo_key_gpio_debounce_config(uint8_t idx, uint8_t debounce_time);
void airo_key_gpio_extslp_debounce_config(uint8_t idx, uint8_t debounce_time);
void gesture_key_changed_handler(uint8_t gpio_pin, uint8_t gpio_level, uint8_t key_idx);
void gesture_key_all_click_reset(uint8_t* key_list, uint8_t key_list_size, bool multi_click_counts_reset);
void gesture_key_click_reset(uint8_t key_idx, bool multi_click_counts_reset);
bool gesture_key_click_timer_running(uint8_t key_idx);
#endif //__GESTURE_HH__
