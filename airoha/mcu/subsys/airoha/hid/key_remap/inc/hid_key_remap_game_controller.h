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
 
#if defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER) && defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#ifndef __HID_KEY_REMAP_GAME_CONTROLLER_H__
#define __HID_KEY_REMAP_GAME_CONTROLLER_H__

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>


#if defined(CONFIG_LOG)
#define DBG_LOGI(module_name, format, ...)   \
        LOG_INF("[srv-i]["module_name"]" format, ## __VA_ARGS__)
#else
#define DBG_LOGI(module_name, format, ...)   \
        printk("[srv-i]["module_name"]"format, ## __VA_ARGS__)
#endif
/******************************************************************************/
/* macro                                                                  */
/******************************************************************************/
#define THRESHOLD_MIN_PERCENT               10 /* lt, rt light press threshold min percent*/
#define THRESHOLD_MAX_PERCENT               95 /* lt, rt deep press threshold max percent*/
#define DEFAULT_LINEAR_REMAP_THRESHOLD      0x320A320A /* default linear remap threshold, 10, 50, 10, 50 */
/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
/* Protocal game controller key setting*/
typedef enum {
    A_KEY,
    B_KEY,
    X_KEY,
    Y_KEY,
    JOYS_L_KEY,
    JOYS_R_KEY,
    LB_KEY,
    RB_KEY,
    VIEW_KEY,
    MENU_KEY,
    LT_SW_KEY,
    RT_SW_KEY,
    D_UP_KEY,
    D_DOWN_KEY,
    D_LEFT_KEY,
    D_RIGHT_KEY,
}T_GC_KEY_SETTING_ID_E;
/******************************************************************************/
/* functions                                                                  */
/******************************************************************************/
uint8_t hid_key_remap_game_controller_reload(uint8_t profile_idx, bool restore);
uint8_t hid_key_remap_game_controller_set(uint8_t key_id, KEY_REMAP_TYPE_E key_type, uint8_t *setting, uint16_t len);
uint32_t hid_key_remap_game_controller_get(uint8_t key_id, KEY_REMAP_TYPE_E *key_type, uint8_t *setting);
uint32_t hid_key_remap_game_controller_init(uint8_t profile_idx);
uint8_t hid_kr_game_controller_delete_macro(const uint8_t macro_name[], uint8_t name_len);
void hid_kr_game_controller_remap_enable_clear(uint8_t key_idx);
void hid_kr_game_controller_macro_parsing(uint8_t key_idx, uint32_t *pressType, uint32_t *releaseType, uint32_t *item);
uint8_t hid_kr_gc_remap_linear_threshold_set(uint32_t threshold);
uint32_t hid_kr_gc_remap_linear_threshold_get();
#endif
#endif /* CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER */
