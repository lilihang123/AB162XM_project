/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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

#ifndef __HW_KEYSCAN_H__
#define __HW_KEYSCAN_H__

#include "hal_hw_keyscan.h"

/** @brief KB mode selection  */
typedef enum
{
  HW_KEYSCAN_OFFICE_KB = 0x0,          /**< office kb :start scan if any key pressed  */
  HW_KEYSCAN_GAMING_KB_ALIGN_BT = 0x1, /**< gaming kb :align BT timer trigger ,8k */
  HW_KEYSCAN_GAMING_KB = 0x2           /**< gaming kb :fixed period ,1k/2k/4k ,set by SFR_KEYSCAN_RATE_DLY_SEL  register*/
} hw_keyscan_mode_t;

/** @brief kb io delay selection  */
typedef enum
{
  HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_2T = 0x0,   /**< 2T  */
  HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_3T = 0x1,   /**< 3T */
  HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_4T = 0x2,   /**< 4T */
  HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_5T = 0x3,   /**< 5T */
  HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_6T = 0x4,   /**< 6T */
  HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_8T = 0x5,   /**< 8T */
  HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_10T = 0x6,  /**< 10T */
  HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_14T = 0x7   /**< 14T */
} hw_keyscan_io_switch_time_t;

/** @brief HW keyscan rate selection */
typedef enum
{
  HW_KEYSCAN_RATE_100RR = 0x00, /**< office:100RR    */
  HW_KEYSCAN_RATE_125RR = 0x01, /**< office/game_mech/game_opt:125RR    */
  HW_KEYSCAN_RATE_133RR = 0x02, /**< office/game_mech/game_opt:133RR    */
  HW_KEYSCAN_RATE_250RR = 0x03, /**< office/game_mech/game_opt:250RR    */
  HW_KEYSCAN_RATE_500RR = 0x04, /**< /game_mech/game_opt:500RR    */
  HW_KEYSCAN_RATE_1KRR = 0x05,  /**< /game_mech/game_opt:1KRR    */
  HW_KEYSCAN_RATE_2KRR = 0x06,  /**< /game_mech/game_opt:2KRR    */
  HW_KEYSCAN_RATE_4KRR = 0x07,  /**< /game_mech/game_opt:4KRR    */
  HW_KEYSCAN_RATE_8KRR = 0x08,  /**< /game_mech/game_opt:8KRR    */
  HW_KEYSCAN_RATE_16KRR = 0x09, /**< /game_mech/game_opt:16KRR    */
  HW_KEYSCAN_RATE_32KRR = 0x10  /**< /game_mech/game_opt:32KRR    */
} hw_keyscan_rate_t;

/** @brief HW keyscan runing status */
typedef enum
{
  KEYSCAN_HWSTATUS_UNINITIALIZED,
  KEYSCAN_HWSTATUS_INITIALIZED,
  KEYSCAN_HWSTATUS_RUNGING
} keyscan_hwstatus_t;

/** @brief HW keyscan type selection */
typedef enum
{
  HW_KEYSCAN_TYPE_OFFICE_KB = 0x00,
  HW_KEYSCAN_TYPE_GAMING_KB_MECH = 0x01,
  HW_KEYSCAN_TYPE_GAMING_KB_OPT = 0x02
} hw_keyscan_kb_type_t;

/** @brief HW keyscan col in active value selection */
typedef enum
{
  HW_KEYSCAN_IO_SETING_LOW_ACTIVE = 0x00,
  HW_KEYSCAN_IO_SETING_HIGH_ACTIVE = 0x01
} hw_keyscan_io_setting_t;

typedef enum
{
  HW_KEYSCAN_STATUS_ERROR = -2,      /**< A keypad function error. */
  HW_KEYSCAN_INVALID_PARAMETER = -1, /**< An invalid parameter. */
  HW_KEYSCAN_STATUS_OK = 0           /**< No error occurred during the function call. */
} hw_keyscan_status_t;

typedef struct
{
  hw_keyscan_mode_t mode;                 /**< Keyscan mode .*/
  hw_keyscan_io_switch_time_t swich_time; /**< Io switch time .*/
  hw_keyscan_rate_t rate;                 /**< Keyscan rate .*/
  bool debounce_en;
  uint8_t release_debounce;
  uint8_t press_debounce;
  uint8_t row_num;                        /**< Number of Row.    Max: 8 .*/
  uint8_t col_num;                        /**< Number of Column. Max: 18.*/
  uint8_t row[8];                         /**< Row IOs .*/
  uint8_t col[18];                        /**< Column IOs .*/
  hw_keyscan_kb_type_t keyboard_type; /**< Keyboard type. */
  uint8_t col_in_setting;                 /**< Column input valid level setting. */
} hw_keyscan_config_t;

typedef void (*hw_keyscan_callback_t)(uint32_t *keys, uint8_t one_packet_valid_num, uint8_t total_key_num, bool is_ghost_happen);

hw_keyscan_status_t hw_keyscan_init(hw_keyscan_config_t *keyscan_config);
hw_keyscan_status_t hw_keyscan_deinit(void);
hw_keyscan_status_t hw_keyscan_register_callback(hw_keyscan_callback_t callback);
hw_keyscan_status_t hw_keyscan_enable(void);
hw_keyscan_status_t hw_keyscan_disable(void);
void hw_keyscan_sw_trigger(void);
void hw_keyscan_align_bt_trigger_set_enable(bool bt_trigger_enable);

#endif /*__HW_KEYSCAN_H__*/
