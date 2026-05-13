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

#ifndef __HID_RACE_CMD_EVENT__
#define __HID_RACE_CMD_EVENT__

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include "race_cmd.h"
#include "race_xport.h"

#if defined(CONFIG_LOG)
#define RACE_DBG_LOGI(module_name, format, ...)   \
        LOG_INF("[srv-i]["module_name"]" format, ## __VA_ARGS__)
#else
#define RACE_DBG_LOGI(module_name, format, ...)   \
        printk("[srv-i]["module_name"]"format, ## __VA_ARGS__)
#endif

////////////////////////////////////////////////////////////////////////////////
// CONSTANT DEFINITIONS ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define RACE_ID_BTD_BEGIN                   0x3000
#define RACE_ID_BTD_END                     0x30FF

// #define RACE_GET_EXCEPTION_INFO             0x300F
#define RACE_SET_REPORT_RATE                0x3010
#define RACE_GET_REPORT_RATE                0x3011
// #define RACE_SET_POWER_SAVING_TIME          0x3012
// #define RACE_GET_POWER_SAVING_TIME          0x3013
// #define RACE_HID_OUTPUT_REPORT              0x3014
// #define RACE_HID_INPUT_REPORT               0x3015
// #define RACE_USB_STATUS_UPDATE              0x3016
// #define RACE_GET_BATTERY_LEVEL              0x3017
// #define RACE_REPORT_BATTERY_LEVEL           0x3018
// #define RACE_DEVICE_SYNC_STATUS             0x3019
// #define RACE_SET_USB_MCU_GPIO               0x3020
// #define RACE_GET_USB_MCU_GPIO               0x3021
// #define RACE_UPDATE_USB_MCU_GPIO            0x3022
// #define RACE_GET_USB_MCU_BATTERY_VALUE      0x3023
// #define RACE_USB_MCU_ALLOW_ENTER_DEEPSLEEP  0x3024
// #define RACE_USB_MCU_ALLOW_EXIT_DEEPSLEEP   0x3025
// #define RACE_USB_MCU_HID_DATA_RX            0x3026
// #define RACE_USB_MCU_HID_DATA_TX            0x3027
// #define RACE_USB_MCU_WAKEUP                 0x3028

// #define RACE_SET_LINK_STATUS                0x301E
// #define RACE_GET_LINK_STATUS                0x301F

// #define RACE_CRYSTAL_TRIM_GET_DEFAULT_CAP   0x3031
// #define RACE_CRYSTAL_TRIM_SET_CAP           0x3033
// #define RACE_CRYSTAL_TRIM_WRITE_CAP         0x3034
// #define RACE_SET_KEYMAPPING_PATTERN         0x3040
#define RACE_WBSCAN_CONTROL                 0x3050

#define RACE_SET_UNIAA                      0x306A
#define RACE_GET_UNIAA                      0x306B
// #define RACE_SWITCH_WIRED_PAIRING_MODE      0x306C
// #define RACE_GET_WIRED_PAIRING_MODE         0x306D
// #define RACE_SWITCH_QC_STATE                0x306E
// #define RACE_GET_QC_STATE                   0x306F
#define RACE_ENABLE_KEY_EVENT               0x3070 /*param 0x0019 to reboot*/
// #define RACE_GET_LOCAL_BDADDR               0x3071
#define RACE_SET_DPI_VALUE                  0x3080

/* RGB */
// #define RACE_RGB_GET_STATUS_INFO            0x30B0
// #define RACE_RGB_WRITE_BIN_DATA             0x30B1
// #define RACE_RGB_WRITE_BIN_CRC              0x30B2
#define RACE_VENDOR_SET_RGB                 0x30C0
// #define RACE_VENDOR_GET_RGB                 0x30C1

#define RACE_VENDOR_SET_DPI                 0x30C4
#define RACE_VENDOR_GET_DPI                 0x30C5
#define RACE_VENDOR_SET_DPI_LOOP_RANGE      0x30C6
#define RACE_VENDOR_SET_DPI_CURRENT         0x30C7
#define RACE_VENDOR_SET_PROFILE             0x30C8
#define RACE_VENDOR_GET_PROFILE             0x30C9
#define RACE_VENDOR_SET_DEBOUNCE            0x30CA
#define RACE_VENDOR_GET_DEBOUNCE            0x30CB
#define RACE_VENDOR_SET_SENSOR_LOD          0x30CC
#define RACE_VENDOR_GET_SENSOR_LOD          0x30CD
#define RACE_VENDOR_SET_RESTORE             0x30CE

/*battery*/
#define RACE_GET_BATTERY                    0x30CF

#define RACE_VENDOR_SET_SENSOR_MOTION_SYNC  0x30D2
#define RACE_VENDOR_GET_SENSOR_MOTION_SYNC  0x30D3
#define RACE_VENDOR_SET_SENSOR_ANGLE_SNAP   0x30D4
#define RACE_VENDOR_GET_SENSOR_ANGLE_SNAP   0x30D5
#define RACE_VENDOR_SET_SENSOR_RIPPLE_CTRL  0x30D6
#define RACE_VENDOR_GET_SENSOR_RIPPLE_CTRL  0x30D7
// #define RACE_VENDOR_FAKE_REPORT             0x30D8

#define RACE_VENDOR_ENTER_LABTEST           0x30DB

#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
/* key remap related race cmd ID */
#define RACE_VENDOR_SET_KEY_REMAP           0x30C2
#define RACE_VENDOR_GET_KEY_REMAP           0x30C3
#define RACE_VENDOR_DELETE_MACRO            0x30D1
// //keyboard key remap
// #define RACE_VENDOR_SET_GAMING_MODE			0x30E0
// #define RACE_VENDOR_GET_GAMING_MODE			0x30E1
// #define RACE_VENDOR_SET_KB_REMAP			0x30E2
// #define RACE_VENDOR_GET_KB_REMAP			0x30E3
// #define RACE_VENDOR_GET_KB_REMAP_ID			0x30E4

#if defined(CONFIG_AIR_REMAP_FN_KEY)
#define RACE_VENDOR_SET_REMAP_FN_KEY        0x30EA
#define RACE_VENDOR_GET_REMAP_FN_KEY        0x30EB
#endif

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
#define RACE_VENDOR_SET_LT_RT_THRESHOLD     0x30F3
#define RACE_VENDOR_GET_LT_RT_THRESHOLD     0x30F4
#endif
#endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */

#if defined(CONFIG_AIR_SW_KEY_DEBOUNCE)
#define RACE_VENDOR_SET_SW_DEBOUNCE	    0x30E8
#define RACE_VENDOR_GET_SW_DEBOUNCE	    0x30E9
#endif

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
#define RACE_SET_JOYSTICK_PARAMETER	    0x30EC
#define RACE_SET_TRIGGER_PARAMETER	    0x30ED
#define RACE_GET_JOYSTICK_PARAMETER         0x30F1
#define RACE_GET_TRIGGER_PARAMETER          0x30F2
#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
#define RACE_SET_USB_MODE        0x30EE
#define RACE_GET_USB_MODE        0x30EF
#endif /* defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER) */

#if defined(CONFIG_AIR_KEYBOARD_M607)
#define    APP_RACE_CMD_ID_MODE_SWITCH       0x0001
#define    APP_RACE_CMD_ID_POWER_OFF_REQUEST 0x0002
#define    APP_RACE_CMD_ID_QUERY_READY       0x0003
#define    APP_RACE_CMD_ID_LOW_POWER_REQUEST 0x0004
#endif
#endif /* __HID_RACE_CMD_EVENT__ */
