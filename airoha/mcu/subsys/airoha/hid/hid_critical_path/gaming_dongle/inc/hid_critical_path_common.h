/* Copyright Statement:
*
* (C) 2025 Airoha Technology Corp. All rights reserved.
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
* the License Agreement ("Permitted User"). If you are not a Permitted User,
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
/* Airoha restricted information */

#ifndef __BT_HID_CRITICAL_PATH_COMMON_H__
#define __BT_HID_CRITICAL_PATH_COMMON_H__

#include <zephyr/kernel.h>
#include "bt_ull_le_hid_service.h"
#include "bt_ull_le_hid_conn_service.h"
#include "zephyr/logging/log.h"
#include "la_debug.h"
#include "air_usb.h"
#include "air_usb_hid.h"
#if defined(CONFIG_AIR_HID_PLC_CALCULATE)
#include "hid_plc_common.h"
#endif
#include "hal_gpio.h"
#include "hal_platform.h"
#include "hal_gpt.h"
#include "hal_gpt_internal.h"
#include "hal_nvic.h"
#include "hid_common_report_structure.h"
#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE)
#include "custom_protocol.h"
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE */
#if CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE
#ifdef AIR_USB_XINPUT_ENABLE
#include "hid_scenario_dongle.h"
#include "air_usb_xinput.h"
#endif /* AIR_USB_XINPUT_ENABLE */
#endif /* CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE */

#define BT_HID_CP_TAG     "[HID][CP] "

#if !defined (CONFIG_AIR_HID_DUMMY_REPORT_RATE)
#define HID_GAMEPAD_DATA_LEN (17)
#elif defined(CONFIG_AIR_GAME_CONTROLLER_9B_DATA)
#define HID_GAMEPAD_DATA_LEN (9)
#else
#define HID_GAMEPAD_DATA_LEN (7)
#endif
#define HID_NORMAL_DATA_LEN (7)
#define HID_BIOS_DATA_LEN (8)
#define HID_CONSUMER_DATA_LEN (6)
#define HID_NKEY_DATA_LEN (15)
#define HID_NKEY_PKT_DATA_LEN (2 + HID_NKEY_DATA_LEN)
#if defined(AIR_NVIDIA_REFLEX_ENABLE)
#define HID_NVIDIA_DATA_LEN (13)
#endif
#define HID_MAX_DATA_LEN (17)

#define HID_LOG_PRINT_COUNT 4

#ifdef CONFIG_AIR_HID_CP_DEBUG_GPIO
#if defined(AIR_DONGLE_OF_KEYBOARD_M607)
#define HID_CP_DEBUG_GPIO_2     HAL_GPIO_34     // crc error
#define HID_CP_DEBUG_GPIO_6     HAL_GPIO_33     // sw isr
#define HID_CP_DEBUG_GPIO_5     HAL_GPIO_32     // usb tx done cb
#else
#define HID_CP_DEBUG_GPIO_2     HAL_GPIO_46     // crc error
#define HID_CP_DEBUG_GPIO_6     HAL_GPIO_45     // sw isr
#define HID_CP_DEBUG_GPIO_5     HAL_GPIO_39     // usb tx done cb
#endif

#define HID_CP_DEBUG_GPIO_1     HAL_GPIO_44     // hid bt cb
#define HID_CP_DEBUG_GPIO_3     HAL_GPIO_47     // bt send fail
#define HID_CP_DEBUG_GPIO_4     HAL_GPIO_28     // usb duplicated
#endif

#define HID_CP_CUSTOM_PROTOCOL_PACKET_CNT 16

/******************************************************************************
 * BT HID Report ID Definition
 *****************************************************************************/
typedef uint8_t hid_critical_path_device_type_t;
#define HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE             0x00
#define HID_CRITICAL_PATH_DEVICE_TYPE_KEY_REMAP         0x01
#define HID_CRITICAL_PATH_DEVICE_TYPE_NKEY              0x02
#define HID_CRITICAL_PATH_DEVICE_TYPE_GAME_CONTROLLER   0x03
#define HID_CRITICAL_PATH_DEVICE_TYPE_MAX_NUM           0x04

typedef uint8_t hid_critical_path_info_type_t;
#define HID_CRITICAL_PATH_INFO_TYPE_REPORT_RATE         0x01        /* Set the Report rate, for parameter please refer to structure #uin16_t. */
#define HID_CRITICAL_PATH_INFO_TYPE_DPI                 0x02        /* Set the DPI value, for parameter please refer to structure #uin16_t. */

typedef uint8_t hid_critical_path_status_t;
#define HID_CP_STATUS_SUCCESS                         0x00
#define HID_CP_STATUS_SEND_FAIL                       0x01
#define HID_CP_STATUS_DUMPLICATED                     0x02
#define HID_CP_STATUS_STATE_ERR                       0x03
#define HID_CP_STATUS_FAIL                            0x04
#define HID_CP_STATUS_RESEND_CB                       0x05
#define HID_CP_STATUS_RESEND_OK                       0x06
#define HID_CP_STATUS_RESEND_FAIL                     0x07
#define HID_CP_STATUS_STATE_BUSY                      0x08

typedef uint8_t hid_critical_path_usb_status_t;
#define HID_CP_USB_STATUS_SUCCESS                     0x00
#define HID_CP_USB_STATUS_BUSY                        0x01
#define HID_CP_USB_STATUS_RECORD                      0x02
#define HID_CP_USB_STATUS_TX_DONE_SEND                0x03

typedef uint8_t hid_cp_bit_mask_t;
#define HID_CP_BIT_MASK_LAST_KEY_VAILD                              (1 << 0)
#define HID_CP_BIT_MASK_RESEND_VAILD                                (1 << 1)

typedef uint8_t hid_cp_state_t;
#define HID_CP_STATE_IDLE                       (1)
#define HID_CP_STATE_CONNECTED                  (2)
#define HID_CP_STATE_DATA_SEND                  (3)
#define HID_CP_STATE_DISCONNECTED               (4)
#define HID_CP_STATE_USB_SUSPENDED              (5)
#define HID_CP_STATE_INVAILD_STATE              (6)

typedef uint8_t hid_critical_path_raw_data_process_method_t;
#define HID_RAW_DATA_PROCESS_METHOD_NONE             (0)    /* do nothing */
#define HID_RAW_DATA_PROCESS_METHOD_EXCHANGE_1B      (1)    /* excahange the first byte and the last byte */
#define HID_RAW_DATA_PROCESS_METHOD_CYCLLE_1B        (2)    /* cycle move 1 byte */

typedef struct {
    uint8_t report_id;
    uint8_t combo;
    uint8_t keycode[2];
    int8_t x_y[3];
    uint8_t dummy;
} __attribute__((__packed__))hid_24g_report_kb_std2_xy_s;

typedef struct {
    uint8_t report_id;
    uint16_t consumer;
    uint8_t numeric_key_pad;
    int8_t x_y[3];
    uint8_t dummy;
} __attribute__((__packed__)) hid_24g_report_kb_consumer1_xy_s;

typedef struct{
#if defined(CONFIG_AIR_HID_PLC_WITH_RESEND)
    bool channel;  /* 0: anchor channel; 1: resend channel */
#else
    bool need_plc; /* 0: no PLC needed; 1: PLC needed */
#endif
    bool correct;   /* 0: not correct; 1: correct[accumalation] */
    hid_plc_reason_t reason;  /* 0: no PLC needed; 1: PLC needed */
} usb_plc_cb_param;

typedef struct __attribute__((__packed__))
{
    uint8_t report_id;
    uint8_t key;
    int16_t x;
    int16_t y;
    int8_t wheel;
    int8_t acpan;
} bt_ms_packet_t;

typedef struct {
    bool q_flag;
    union {
        bt_ms_packet_t data;
#if CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE
        T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S data_game_controller;
#endif /* CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE */
    };
} hid_critical_path_resend_t;

typedef struct{
    uint32_t timestamp;
    uint16_t data_len;
    uint8_t data[HID_MAX_DATA_LEN + 1];
} hid_cp_bt_hid_data;

typedef struct{
    uint32_t timestamp;
    #ifdef CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE
    uint8_t data[HID_GAMEPAD_DATA_LEN + 1];
    #else
    uint8_t data[HID_NORMAL_DATA_LEN + 1]; /* Use the last byte to indicate the return value of bt isr process */
    #endif
} hid_cp_usb_hid_data;

typedef struct {
    bool accumulate_flag;
    bool empty_flag; 
    bool big_drift_flag;
    bool not_excepted_data_flag;
    uint32_t null_cnt;
    uint32_t big_drift_cnt;
    uint8_t last_key;
    usb_plc_cb_param bt_hid_plc_param;
    hid_cp_bt_hid_data bt_hid_data;
    hid_critical_path_resend_t resend_data;
    uint16_t dpi;
} hid_critical_path_ms_t;

typedef struct {
    uint8_t last_key;
    usb_plc_cb_param bt_hid_plc_param;
    hid_cp_bt_hid_data bt_hid_data;
} hid_critical_path_kb_t;

typedef struct {
    uint8_t last_key;
    usb_plc_cb_param bt_hid_plc_param;
    hid_cp_bt_hid_data bt_hid_data;
    hid_critical_path_resend_t resend_data;
} hid_critical_path_gamepad_t;

typedef struct {
    bool hid_protocol;
    hid_cp_bit_mask_t bit_mask;
    bt_ull_le_hid_srv_report_rate_level_t report_rate;
    hid_cp_state_t state;
    uint32_t usb_user_id;
    const struct device *hid_dev;
    union {
        hid_critical_path_ms_t ms_ctx;
        hid_critical_path_kb_t kb_ctx;
        hid_critical_path_gamepad_t gp_ctx;
    };
} hid_critical_path_t;

typedef struct {
    bool flag; /* flag = true --> total_data_count == 8000 */
    int8_t last_acpan;
    uint8_t log_print_count;/* when log_print_count = HID_LOG_PRINT_COUNT*/
    uint8_t log_print_count_last;/* when log_print_count = HID_LOG_PRINT_COUNT*/
    hid_cp_bt_hid_data hid_data[HID_LOG_PRINT_COUNT*2];
    uint8_t usb_print_count_last;/* when log_print_count = HID_LOG_PRINT_COUNT*/
    uint8_t usb_print_count;/* when log_print_count = HID_LOG_PRINT_COUNT*/
    hid_cp_usb_hid_data usb_data[HID_LOG_PRINT_COUNT*2];
    uint8_t send_usb_dum;
    uint8_t send_usb_ret;
    hid_cp_bt_hid_data usb_hid_data;
    uint32_t normal_data_count;
    uint32_t plc_correct_count;
    uint32_t plc_revised_zero_count;
    uint32_t plc_err_count;
    uint32_t plc_null_count;
    uint32_t plc_dup_count;
    uint32_t not_except_count;
    uint32_t total_data_count;
    uint32_t tx_done_cb_count;
    uint32_t tx_done_send_busy_count;
    uint32_t duplicate_data_count;
    uint32_t send_to_usb_count;
    uint32_t send_to_usb_suc;
    uint32_t send_to_usb_fail_bt;
    uint32_t send_to_usb_fail_usb;
} hid_cp_debug_paramter_t;

#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE)
typedef struct {
    bool is_full;
    uint16_t write_ptr;
    uint16_t read_ptr;
    uint8_t buff[EPIO_CUSTOM_PROTOCOL_MIX_WITH_HID_PACKET_SIZE * HID_CP_CUSTOM_PROTOCOL_PACKET_CNT];
} hid_critical_path_custom_protocol_data_t;
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE */

extern hid_cp_debug_paramter_t hid_cp_debug_paramter;
extern bool hid_cp_usb_tx_running_flag;

typedef void (*hid_cp_debug_callback_t)(uint32_t total_data_count, uint32_t normal_data_count, uint32_t report_rate);

extern int hid_cp_protocol_change_cb(const struct device *dev, uint8_t protocol);
extern void hid_critical_path_set_state(hid_critical_path_device_type_t type, hid_cp_state_t state);
extern hid_cp_state_t hid_critical_path_get_state(hid_critical_path_device_type_t type);
extern void hid_cp_usb_evt_cb(air_usb_evt_t evt, const uint8_t *para);
extern int32_t hid_cp_convert_data_extended(int16_t data);
extern int16_t hid_cp_convert_data_limiter(int32_t data);
extern void hid_cp_debug_log(bt_ull_le_hid_srv_report_rate_level_t report_rate);
extern void hid_critical_path_common_register_callback(hid_cp_debug_callback_t cb);
#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE)
extern void hid_critical_path_common_custom_protocol_data_push(uint8_t *in_buf, uint16_t len);
extern void hid_critical_path_common_custom_protocol_data_query(uint8_t **current_read_ptr, uint16_t len);
extern void hid_critical_path_common_custom_protocol_data_pop(uint8_t *out_buf, uint16_t len);
extern void hid_critical_path_common_custom_protocol_data_process(void);
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE */

/**
 * @brief   This function is used for application to initialize HID Critical Path COMMON.
 * @param[in]             #none.
 * @return                #NULL.
 */
void hid_critical_path_common_init(void);

/**
 * @brief   This function is used for application to get HID Critical Path Context By device type.
 * @param[in]             #type.
 * @return                #hid_critical_path_t *.
 */
hid_critical_path_t *hid_critical_path_common_get_ctx(hid_critical_path_device_type_t type);

#endif