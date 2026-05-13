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
 
#if defined(AIR_HID_BT_MODE) || defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
#ifndef _RISCV_HID_EXPRESS_BT_MODE_H_
#define _RISCV_HID_EXPRESS_BT_MODE_H_
#include "riscv_hid_express.h"

typedef enum {
    BT_QUEUE_STATUS_SUCCESS = 0,
    BT_QUEUE_STATUS_QUEUE_EMPTY,    
    BT_QUEUE_STATUS_QUEUE_FULL,
    BT_QUEUE_STATUS_NOT_MOUSE,
    BT_QUEUE_STATUS_UNKNOWN,
    // Additional error codes can be added here
} HID_EXPRESS_BT_QUEUE_STATUS;

/* Private define ------------------------------------------------------------*/
#define BT_BUFFER_SIZE_DEFAULT                 2                              /** The size of the buffer used to store the bt report, it should be a power of 2 */
#define BT_BUFFER_SIZE_DEFAULT_MASK            (BT_BUFFER_SIZE_DEFAULT - 1)   /** The mask of the buffer size  */
/* Private typedef -----------------------------------------------------------*/
#define L2CAP_ATTRIBUTE_PROTOCOL                (4)
#define ATT_HANDLE_VALUE_NOTIFICATION       (0x1b)
#define ATT_ATTRIBUTE_HANDLE                (0x2F)

typedef struct {
    uint32_t ms;
    uint32_t kb_std;
    uint32_t kb_csm;
    uint32_t game_controller;
    uint32_t kb_nkey;
}T_ATT_ATTRIBUTE_HANDLE_S;

typedef struct {
    uint16_t LEN;               //size of (T_ATT_HEADER_S + T_MOUSE_REPORT_PAYLOAD_S)
    uint16_t CH_ID;             //Fixed : 4
}T_L2CAP_HEADER_S;

typedef struct {
    uint8_t OPCODE;                 //Handle Value Notification
    uint16_t ATTRIBUTE_HANDLE;      //Condictional Fixed : 42  (depends on descriptor)
}__packed T_ATT_HEADER_S;

typedef struct {
    uint16_t k;
    int16_t x;
    int16_t y;
    int8_t z1;
    int8_t z2;
}__packed T_MOUSE_REPORT_PAYLOAD_S;

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t z;
    uint16_t rz;
    uint16_t brake;
    uint16_t accelerator;
    uint8_t hat_switch;
    uint16_t button;
    uint8_t record;
}__packed T_HID_REPORT_GAME_CONTROLLER_BT_PAYLOAD_S;

typedef struct {
    uint8_t combo;
    uint8_t nkey[15];
}__packed T_HID_REPORT_KB_NKEY_BT_PAYLOAD_S;

typedef struct {
    T_L2CAP_HEADER_S    l2cap;
    T_ATT_HEADER_S      att;
    union {
        T_MOUSE_REPORT_PAYLOAD_S         ms_hid;
        T_REPORT_KB_STD5_PAYLOAD_S       kb_std5;
        T_REPORT_KB_CONSUMER2_PAYLOAD_S  kb_consumer2;
        #if defined(AIR_PRODUCT_TYPE_KEYBOARD)
        T_HID_REPORT_KB_NKEY_BT_PAYLOAD_S    kb_nkey;
        #endif
        #if defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
        T_REPORT_KB_KEY_BIT_PAYLOAD_S    kb_bit;
        #endif
        #if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER) && defined(AIR_HID_BT_MODE)
        T_HID_REPORT_GAME_CONTROLLER_BT_PAYLOAD_S gamepad;
        #endif
    };
}__packed T_BT_HID_REPORT_S;

typedef struct {
    uint8_t front;
    uint8_t rear;
    T_BT_HID_REPORT_S bt_report[BT_BUFFER_SIZE_DEFAULT];
} T_BT_QUEUE_CTRL_S;

typedef struct {
    uint8_t tx_buffer_full;
    uint8_t controller_full;
    uint8_t drop_data;
    uint8_t LC_burst_tx_number_10;
    uint8_t tx_buffer_full_print;
    uint8_t controller_full_print;
    uint8_t drop_data_print;
    uint8_t LC_burst_tx_number_10_print;
} T_BT_DEBUG_S;

extern T_BT_DEBUG_S bt_debug;

int hid_express_bt_data_send(T_OUTGOING_VALUES_S* outgoing, uint32_t tx_result, uint32_t  tx_idx, uint32_t assemble);
int hid_express_bt_x_y_data_prepare(T_OUTGOING_VALUES_S* outgoing, uint32_t tx_result, uint32_t  tx_idx, uint32_t assemble);
int hid_express_bt_get_tx_result();
void hid_express_bt_init();
void hid_express_bt_debug_print();
bool is_bt_queue_empty();
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER) && defined(AIR_HID_BT_MODE)
void hid_experss_bt_set_attr_handle(uint32_t game_controller);
#elif defined(AIR_PRODUCT_TYPE_KEYBOARD) && defined(AIR_HID_BT_MODE)
void hid_experss_bt_set_attr_handle(uint32_t ms, uint32_t kb_std, uint32_t kb_consumer, uint32_t kb_nkey);
#else
void hid_experss_bt_set_attr_handle(uint32_t ms, uint32_t kb_std, uint32_t kb_consumer);
#endif
void hid_experss_bt_clear_queue();
void hid_express_bt_debug_check();
void hid_express_bt_debug_print();
#endif /* _RISCV_HID_EXPRESS_BT_MODE_H_ */
#endif