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

#ifndef _HID_COMMON__REPORT_STRUCTURE_H_
#define _HID_COMMON__REPORT_STRUCTURE_H_

#if defined(AIR_HID_COMMON_SERVICE)

/* Public define -------------------------------------------------------------*/
// report id
#define REPORT_ID_KB_STD_XY           1
#define REPORT_ID_MOUSE               2
#define REPORT_ID_NVIDIA_REFLEX       3
#define REPORT_ID_KEYBOARD_NKEY       4
#define REPORT_ID_KB_CONSUMER_XY      5
// #define REPORT_ID_KEYBOARD_BIT_REP_1  6
// #define REPORT_ID_KEYBOARD_BIT_REP_2  7
// #define REPORT_ID_KEYBOARD_BIT_REP_3  8
#define REPORT_ID_KEYBOARD            6
#define REPORT_ID_KEYBOARD_GROUP0     7
#define REPORT_ID_KEYBOARD_GROUP1     8
#define REPORT_ID_KB_STD              9
#define REPORT_ID_KB_CONSUMER         10

#define REPORT_ID_MOUSE_16BIT         11

#define REPORT_ID_USB_KB_CONSUMBER              12

#define REPORT_ID_BT_GAME_CONTROLLER          0x1
#define REPORT_ID_BT_GAME_CONTROLLER_GROUP0   0x2
#define REPORT_ID_BT_GAME_CONTROLLER_GROUP1   0x3
#define REPORT_ID_BT_GAME_CONTROLLER_GROUP2   0x4

#define REPORT_ID_GAME_CONTROLLER          0x13
#define REPORT_ID_GAME_CONTROLLER_GROUP0   0x14
#define REPORT_ID_GAME_CONTROLLER_GROUP1   0x15
#define REPORT_ID_GAME_CONTROLLER_GROUP2   0x16
#define REPORT_ID_GAME_CONTROLLER_ALL_IN_ONE   0x17

#define HID_REPORT_WITH_CUSTOMER_DATA_BIT                  0x40
#if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_PRODUCT_TYPE_MOUSE)
#define REPORT_ID_MS_ACL_PACKET_CUST_PROTOCOL           (HID_REPORT_WITH_CUSTOMER_DATA_BIT | REPORT_ID_MOUSE )     // 0x42
#elif defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_PRODUCT_TYPE_MOUSE)
#define REPORT_ID_MS_ACL_PACKET_CUST_PROTOCOL           (HID_REPORT_WITH_CUSTOMER_DATA_BIT | REPORT_ID_GAME_CONTROLLER )     // 0x53
#endif


/* Public typedef ------------------------------------------------------------*/
typedef struct {
    uint8_t report_id;
    uint8_t k;
    int16_t x;
    int16_t y;
    int8_t z1;
    int8_t z2;
} __attribute__((__packed__)) T_HID_REPORT_MS_K8_S16_Z8_S;

typedef struct {
    uint8_t report_id;
    uint8_t k;
    int8_t xy[3];
    int8_t z1;
    int8_t z2;
} T_HID_REPORT_MS_K8_S12_Z16_S;

typedef struct {
    uint8_t report_id;
    uint8_t ms_key;
    int8_t xy_val[3];
    int8_t wheel;
    int8_t ac_pan;
    int8_t dummy;
} __attribute__((__packed__)) T_HID_MOUSE_REPORT_K8_S12_Z8; // Key 8bits, Sensor 12 bits; Z data(wheel/pan) 8 bits

#if defined(AIR_GAME_CONTROLLER_9B_DATA) || defined(AIR_PRODUCT_TYPE_KEYBOARD)
typedef struct {
    uint8_t wheel_key; /* 3 bits wheel + 5 bits key */
    int16_t x;
    int16_t y;
    int8_t ac_pan;
    int8_t dummy[2];
    uint8_t report_id;
} __attribute__((__packed__)) T_HID_MOUSE_2_4G_REPORT_K8_S16_Z8; // Key 8bits, Sensor 16 bits; Z data(wheel/pan) 8 bits
#elif defined(AIR_MOUSE_9B_DATA)
typedef struct {
    int8_t dummy_2;    /* Byte 8 */
    uint8_t wheel_key; /* 3 bits wheel + 5 bits key */
    int16_t x;
    int16_t y;
    int8_t ac_pan;
    int8_t dummy_1;    /* Byte 7 */
    uint8_t report_id;
} __attribute__((__packed__)) T_HID_MOUSE_2_4G_REPORT_K8_S16_Z8; // Key 8bits, Sensor 16 bits; Z data(wheel/pan) 8 bits
#else
typedef struct {
    int8_t ac_pan;
    uint8_t wheel_key; /* 3 bits wheel + 5 bits key */
    int16_t x;
    int16_t y;
    uint8_t report_id;
    int8_t dummy;
} __attribute__((__packed__)) T_HID_MOUSE_2_4G_REPORT_K8_S16_Z8; // Key 8bits, Sensor 16 bits; Z data(wheel/pan) 8 bits
#endif

typedef struct {
    uint8_t report_id;
    uint8_t combo;
    uint8_t keycode[2];
    int16_t x;
    int16_t y;
} __attribute__((__packed__))T_HID_REPORT_KB_STD2_XY_S;

typedef struct {
    uint8_t report_id;
    uint16_t consumer;
    uint8_t numeric_key_pad;
    int16_t x;
    int16_t y;
} __attribute__((__packed__)) T_HID_REPORT_KB_CONSUMER1_XY_S;

typedef struct {
    uint8_t report_id;
    uint8_t k;
    uint8_t reserved;
    int16_t x;
    int16_t y;
    int8_t z1;
    uint8_t nv_ext[5];  //nvidia_extension
} __attribute__((__packed__)) T_HID_REPORT_MS_NV_S;

typedef struct {
    uint8_t report_id;
    uint8_t combo;
    uint8_t keycode[5];
    uint8_t dummy;
} __attribute__((__packed__))T_HID_REPORT_KB_STD5_S;

typedef struct {
    uint8_t report_id;
    uint8_t consumer[4];
    uint8_t numeric_key_pad;
    uint8_t dummy[2];
} __attribute__((__packed__)) T_HID_REPORT_KB_CONSUMER2_S;

#if defined(AIR_GAME_CONTROLLER_9B_DATA) || defined(AIR_PRODUCT_TYPE_KEYBOARD)
typedef struct {
    uint8_t combo;
    uint8_t keycode[5];
    uint8_t dummy[2];
    uint8_t report_id;
} __attribute__((__packed__))T_HID_2_4G_REPORT_KB_STD5_S;

typedef struct {
    uint8_t consumer[4];
    uint8_t numeric_key_pad;
    uint8_t dummy[3];
    uint8_t report_id;
} __attribute__((__packed__)) T_HID_2_4G_REPORT_KB_CONSUMER2_S;
#elif defined(AIR_MOUSE_9B_DATA)
typedef struct {
    uint8_t dummy_2;
    uint8_t combo;
    uint8_t keycode[5];
    uint8_t dummy_1;
    uint8_t report_id;
} __attribute__((__packed__))T_HID_2_4G_REPORT_KB_STD5_S;

typedef struct {
    uint8_t dummy_2;
    uint8_t consumer[4];
    uint8_t numeric_key_pad;
    uint8_t dummy_1;
    uint8_t report_id;
} __attribute__((__packed__)) T_HID_2_4G_REPORT_KB_CONSUMER2_S;
#else
typedef struct {
    uint8_t last_keycode;
    uint8_t combo;
    uint8_t keycode[4];
    uint8_t report_id;
    uint8_t dummy;
} __attribute__((__packed__))T_HID_2_4G_REPORT_KB_STD5_S;

typedef struct {
    uint8_t numeric_key_pad;
    uint8_t consumer[4];
    uint8_t report_id;
    uint8_t dummy[2];
} __attribute__((__packed__)) T_HID_2_4G_REPORT_KB_CONSUMER2_S;
#endif

#if !defined (AIR_HID_DUMMY_REPORT_RATE)
typedef struct {
    uint8_t wheel_key; /* 3 bits wheel + 5 bits key */
    int16_t x;
    int16_t y;
    int8_t ac_pan;
    int8_t dummy[10];
    uint8_t report_id;
} __attribute__((__packed__)) T_HID_MOUSE_2_4G_REPORT_K8_S16_Z8_17B; // Key 8bits, Sensor 12 bits; Z data(wheel/pan) 8 bits

typedef struct {
    uint8_t combo;
    uint8_t keycode[5];
    uint8_t dummy[10];
    uint8_t report_id;
} __attribute__((__packed__))T_HID_2_4G_REPORT_KB_STD5_17B_S;

typedef struct {
    uint8_t consumer[4];
    uint8_t numeric_key_pad;
    uint8_t dummy[11];
    uint8_t report_id;
} __attribute__((__packed__)) T_HID_2_4G_REPORT_KB_CONSUMER2_17B_S;
#endif

typedef struct {
    uint8_t combo;
    uint8_t keycode[5];
} __attribute__((__packed__))T_REPORT_KB_STD5_PAYLOAD_S;

typedef struct {
    uint8_t keycode[5];
    uint8_t reserve;//avoid memory overflow
} __attribute__((__packed__))T_REPORT_KB_KEY_BIT_PAYLOAD_S;

typedef struct {
    uint16_t consumer[2];
    uint8_t numeric_key_pad;
} __attribute__((__packed__)) T_REPORT_KB_CONSUMER2_PAYLOAD_S;

typedef struct {
    uint8_t  combo;
    uint8_t  nkey[7];
    uint8_t  report_id;
} __attribute__((__packed__)) T_HID_REPORT_KB_COMBO_N7_S;

typedef struct {
    uint8_t  nkey[8];
    uint8_t  report_id;
} __attribute__((__packed__)) T_HID_REPORT_KB_N8_S;

typedef struct {
    uint8_t combo;
    uint8_t nkey[15];
    uint8_t report_id;
} __attribute__((__packed__)) T_HID_REPORT_KB_NKEY_16_S;

#if defined(CONFIG_AIR_USB_NO_REPORT_ID)
typedef struct {
    uint8_t ms_key;
    int8_t xy_val[3];
    int8_t wheel;
    int8_t ac_pan;
} __attribute__((__packed__)) T_HID_MOUSE_REPORT_K8_S12_Z8_NO_ID;

typedef struct {
    uint8_t ms_key;
    int16_t x;
    int16_t y;
    int8_t wheel;
    int8_t ac_pan;
} __attribute__((__packed__)) T_HID_MOUSE_REPORT_K8_S16_Z8_NO_ID;

typedef struct {
    uint8_t combo;
    uint8_t keycode[2];
    int16_t x;
    int16_t y;
} __attribute__((__packed__))T_HID_REPORT_KB_STD2_XY_S_NO_ID;

typedef struct {
    uint16_t consumer;
    uint8_t numeric_key_pad;
    int16_t x;
    int16_t y;
} __attribute__((__packed__)) T_HID_REPORT_KB_CONSUMER1_XY_S_NO_ID;

typedef struct {
    uint8_t k;
    uint8_t reserved;
    int16_t x;
    int16_t y;
    int8_t z1;
    uint8_t nv_ext[5];  //nvidia_extension
} __attribute__((__packed__)) T_HID_REPORT_MS_NV_S_NO_ID;

typedef struct {
    uint8_t modifier;
    uint8_t keymap[15];
} __attribute__((__packed__)) T_HID_REPORT_GAMING_KB_NK_S_NO_ID;

typedef struct {
    uint8_t consumer[4];
    uint8_t numeric_key_pad;
} __attribute__((__packed__)) T_HID_REPORT_KB_CONSUMER2_S_NO_ID;

typedef struct {
    uint8_t combo;
    uint8_t keycode[5];
} __attribute__((__packed__))T_HID_REPORT_KB_STD5_S_NO_ID;

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t z;
    uint16_t rz;
    uint16_t breake;
    uint16_t accelerator;
    uint8_t hat_switch;
    uint16_t button;
    uint8_t record;
} __attribute__((__packed__)) T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S_NO_ID;
#endif /* _CONFIG_AIR_USB_NO_REPORT_ID_ */

typedef struct {
#if defined(CONFIG_AIR_GAME_CONTROLLER_12BIT_ADC) || defined(AIR_GAME_CONTROLLER_12BIT_ADC)
    uint8_t x_y_z_rz[6];
    #if defined(CONFIG_AIR_GAME_CONTROLLER_9B_DATA) || defined(AIR_GAME_CONTROLLER_9B_DATA)
    uint8_t button1;
    uint8_t button2;
    #endif
#else
    uint16_t x;
    uint16_t y;
    uint16_t z;
    uint16_t rz;
#endif
    uint8_t report_id;
} __attribute__((__packed__)) T_HID_REPORT_GAME_CONTROLLER_PAYLOAD_0_S;

typedef struct {
    uint8_t button;
    uint8_t hat_switch_and_trigger[3];
#if defined(CONFIG_AIR_GAME_CONTROLLER_9B_DATA) || defined(AIR_GAME_CONTROLLER_9B_DATA)
    uint8_t diff_x;
    uint8_t diff_y;
    uint8_t diff_z;
    uint8_t diff_rz;
#else
    uint8_t diff_x_y_z_rz[2];
#endif
    uint8_t report_id;
} __attribute__((__packed__)) T_HID_REPORT_GAME_CONTROLLER_PAYLOAD_1_S;

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t z;
    uint16_t rz;
    uint16_t breake;
    uint16_t accelerator;
    uint8_t hat_switch;
    uint16_t button;
    uint8_t record;
    uint8_t report_id;
} __attribute__((__packed__)) T_HID_REPORT_GAME_CONTROLLER_PAYLOAD_ALL_IN_ONE_S;

typedef struct {
    uint8_t report_id;
    uint16_t x;
    uint16_t y;
    uint16_t z;
    uint16_t rz;
    uint16_t breake;
    uint16_t accelerator;
    uint8_t hat_switch;
    uint16_t button;
    uint8_t record;
} __attribute__((__packed__)) T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S;

typedef struct {
    uint8_t report_id;
    uint8_t report_size;
    uint16_t button;
    uint8_t left_trigger;
    uint8_t right_trigger;
    int16_t left_x;
    int16_t left_y;
    int16_t right_x;
    int16_t right_y;
    uint8_t reserved[6];
} __attribute__((__packed__)) T_HID_REPORT_GAME_CONTROLLER_XINPUT_PAYLOAD_S;

#endif /* AIR_HID_COMMON_SERVICE */
#endif /* _HID_COMMON_H_ */
