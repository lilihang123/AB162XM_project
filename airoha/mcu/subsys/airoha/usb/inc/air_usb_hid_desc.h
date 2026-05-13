/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
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

#ifndef __AIROHA_USB_HID_DESC_H__
#define __AIROHA_USB_HID_DESC_H__

#include <inttypes.h>

#define AIR_USB_HID_AIR_OUT_REPORT_ID 0x06
#define AIR_USB_HID_AIR_IN_REPORT_ID  0x07

#define AIR_USB_HID_AIR_OUT_REPORT_LEN 62
#define AIR_USB_HID_AIR_IN_REPORT_LEN  62

/*****************************************************************************/
/* AIROHA Report 2                                                           */
/*****************************************************************************/
#define AIR_USB_HID_AIR2_OUT_REPORT_ID 0x08
#define AIR_USB_HID_AIR2_IN_REPORT_ID  0x09

#define AIR_USB_HID_AIR2_OUT_REPORT_LEN 1024
#define AIR_USB_HID_AIR2_IN_REPORT_LEN  1024

#define AIR_USB_HID_FEATURE_REPORT_ID 0x14
#define AIR_USB_HID_FEATURE_REPORT_LEN 62

#define AIR_USB_HID_BL_DFU_FEATURE_REPORT_ID 0x30
#define AIR_USB_HID_BL_DFU_FEATURE_REPORT_LEN 1024

typedef struct {
	uint8_t report_id;
	uint8_t data[1023];
} air_usb_hid_air2_out_t;

typedef struct {
	uint8_t report_id;
	uint8_t data[1023];
} air_usb_hid_air2_in_t;

/*****************************************************************************/
/* Endpoint IN/OUT Report                                                    */
/*****************************************************************************/
#define AIR_USB_HID_EPIO_RX_REPORT_ID 0x2E
#define AIR_USB_HID_EPIO_TX_REPORT_ID 0x2F

#define AIR_USB_HID_EPIO_RX_REPORT_LEN 64
#define AIR_USB_HID_EPIO_TX_REPORT_LEN 64

typedef struct {
	uint8_t report_id;
	uint8_t data[63];
} air_usb_hid_epio_tx_t;

typedef struct {
	uint8_t report_id;
	uint8_t data[63];
} air_usb_hid_epio_rx_t;

/*****************************************************************************/
/* AIR_USB_REPORT_DESC_GAMING_MS                                             */
/*****************************************************************************/
#define AIR_USB_HID_GAMING_MS_REPORT_ID 0x02
typedef struct __attribute__((__packed__)) {
	uint8_t report_id;
	uint8_t button;
	int16_t x;
	int16_t y;
	int8_t wheel;
	int8_t acpen;
} air_usb_hid_gaming_ms_report_t;

/*****************************************************************************/
/* AIR_USB_REPORT_DESC_GAMING_MS_NV                                             */
/*****************************************************************************/
#define AIR_USB_HID_GAMING_MS_NV_REPORT_ID 0x03
typedef struct __attribute__((__packed__)) {
	uint8_t report_id;
	uint8_t button;
	uint8_t reserved;
	int16_t x;
	int16_t y;
	int8_t wheel;
	uint8_t nvidia_extension[5];
} air_usb_hid_gaming_ms_nv_report_t;

/*****************************************************************************/
/* AIR_USB_REPORT_DESC_GAMING_KB                                             */
/*****************************************************************************/
#define AIR_USB_HID_GAMING_KB_REPORT_ID     0x01
#define AIR_USB_HID_GAMING_KB_LED_REPORT_ID AIR_USB_HID_GAMING_KB_REPORT_ID

typedef struct __attribute__((__packed__)) {
	uint8_t report_id; /* AIR_USB_HID_GAMING_KB_REPORT_ID */
	uint8_t modifier;
	uint8_t key[5];
} air_usb_hid_gaming_kb_report_t;

typedef struct __attribute__((__packed__)) {
	uint8_t report_id; /* AIR_USB_HID_GAMING_KB_LED_REPORT_ID */
	uint8_t num_lock: 1;
	uint8_t cap_lock: 1;
	uint8_t scr_lock: 1;
	uint8_t compose: 1;
	uint8_t kana: 1;
	uint8_t reserved: 3;
} air_usb_hid_gaming_kb_led_report_t;

/*****************************************************************************/
/* AIR_USB_REPORT_DESC_GAMING_KB_NKEY                                             */
/*****************************************************************************/
#define AIR_USB_HID_GAMING_KB_NKEY_REPORT_ID     0x01
#define AIR_USB_HID_GAMING_KB_NKEY_LED_REPORT_ID AIR_USB_HID_GAMING_KB_NKEY_REPORT_ID

typedef struct __attribute__((__packed__)) {
	uint8_t report_id; /* AIR_USB_HID_GAMING_KB_NKEY_REPORT_ID */
	uint8_t modifier;
	uint8_t keymap[15];
} air_usb_hid_gaming_kb_nkey_report_t;

typedef struct __attribute__((__packed__)) {
	uint8_t report_id; /* AIR_USB_HID_GAMING_KB_NKEY_LED_REPORT_ID */
	uint8_t num_lock: 1;
	uint8_t cap_lock: 1;
	uint8_t scr_lock: 1;
	uint8_t compose: 1;
	uint8_t kana: 1;
	uint8_t reserved: 3;
} air_usb_hid_gaming_kb_nkey_led_report_t;

/*****************************************************************************/
/* AIR_USB_REPORT_DESC_OFFICE_MS                                             */
/*****************************************************************************/
#define AIR_USB_HID_OFFICE_MS_REPORT_ID 0x02

typedef struct __attribute__((__packed__)) {
	uint8_t report_id; /* AIR_USB_HID_OFFICE_MS_REPORT_ID */
	uint8_t button[2];
	int16_t x;
	int16_t y;
	int8_t wheel;
	int8_t acpen;
} air_usb_hid_office_mouse_report_t;

/*****************************************************************************/
/* AIR_USB_REPORT_DESC_OFFICE_KB                                             */
/*****************************************************************************/
#define AIR_USB_HID_OFFICE_KB_REPORT_ID     0x01
#define AIR_USB_HID_OFFICE_KB_LED_REPORT_ID AIR_USB_HID_OFFICE_KB_REPORT_ID

typedef struct __attribute__((__packed__)) {
	uint8_t report_id; /* AIR_USB_HID_OFFICE_KB_REPORT_ID */
	uint8_t modifier;
	uint8_t key[6];
} air_usb_hid_office_kb_report_t;

typedef struct __attribute__((__packed__)) {
	uint8_t report_id; /* AIR_USB_HID_OFFICE_KB_LED_REPORT_ID */
	uint8_t num_lock: 1;
	uint8_t cap_lock: 1;
	uint8_t scr_lock: 1;
	uint8_t compose: 1;
	uint8_t kana: 1;
	uint8_t reserved: 3;
} air_usb_hid_office_kb_led_report_t;

/*****************************************************************************/
/* AIR_USB_REPORT_DESC_CONSUMER                                             */
/*****************************************************************************/
#define AIR_USB_HID_CONSUMER_REPORT_ID 0x0C

typedef struct __attribute__((__packed__)) {
	uint8_t report_id; /* AIR_USB_HID_CONSUMER_REPORT_ID */
	uint16_t consumer_usage[2];
	uint8_t numkey;
} air_usb_hid_consumer_report_t;

/*****************************************************************************/
/* AIR_USB_REPORT_DESC_CUSTOM                                                */
/*****************************************************************************/
#define AIR_USB_HID_CUSTOM_FEATURE_REPORT_ID 0x17
#define AIR_USB_HID_CUSTOM_SET_REPORT_ID 0x15
#define AIR_USB_HID_CUSTOM_GET_REPORT_ID 0x16
#define AIR_USB_HID_CUSTOM_FEATURE_REPORT_LEN 64
#define AIR_USB_HID_CUSTOM_SET_REPORT_LEN 64
#define AIR_USB_HID_CUSTOM_GET_REPORT_LEN 64

typedef struct __attribute__((__packed__)) {
	uint8_t report_id; /* AIR_USB_HID_CUSTOM_REPORT_ID */
	uint8_t data[63];
} air_usb_hid_custom_report_t;

/*****************************************************************************/
/* AIR_USB_REPORT_DESC_GAMEPAD                                               */
/*****************************************************************************/
#define AIR_USB_HID_GAMEPAD_REPORT_ID 0x13

typedef struct __attribute__((packed)) {
    uint8_t  report_id;      // 0x13
    // first (X, Y)
    uint16_t x;              // 16 bits
    uint16_t y;              // 16 bits
    // second (Z, Rz)
    uint16_t z;              // 16 bits
    uint16_t rz;             // 16 bits
    // Brake
    uint16_t brake : 10;     // 10 bits
    uint16_t reserved0 : 6;  // 6 bits (const, padding)
    // Accelerator
    uint16_t accelerator : 10; // 10 bits
    uint16_t reserved1 : 6;    // 6 bits (const, padding)
    // Hat switch
    uint8_t hat : 4;         // 4 bits
    uint8_t reserved2 : 4;   // 4 bits (const, padding)
    // Buttons
    uint16_t buttons : 15;   // 15 bits
    uint16_t reserved3 : 1;  // 1 bit (const, padding)
    // Consumer Record
    uint8_t record : 1;      // 1 bit
    uint8_t reserved4 : 7;   // 7 bits (const, padding)
} air_usb_hid_gamepad_report_t;

typedef enum {
	AIR_USB_REPORT_DESC_MUX,
	AIR_USB_REPORT_DESC_MUX2,
	AIR_USB_REPORT_DESC_EPIO,
	AIR_USB_REPORT_DESC_GAMING_MS,
	AIR_USB_REPORT_DESC_GAMING_MS_NV,
	AIR_USB_REPORT_DESC_GAMING_KB,
	AIR_USB_REPORT_DESC_GAMING_KB_NKEY,
	AIR_USB_REPORT_DESC_OFFICE_MS,
	AIR_USB_REPORT_DESC_OFFICE_KB,
	AIR_USB_REPORT_DESC_CONSUMER,
	AIR_USB_REPORT_DESC_CUSTOM,
	AIR_USB_REPORT_DESC_GAMEPAD,
	AIR_USB_REPORT_DESC_CUSTOM_NO_REPORT_ID,
	AIR_USB_REPORT_DESC_GAMING_MS_NO_REPORT_ID,
	AIR_USB_REPORT_DESC_NUM, /* The available num of hid report descs */
} air_usb_hid_report_desc_t;

typedef struct __attribute__((__packed__)) {
	air_usb_hid_report_desc_t type;
	const char *name;
	uint8_t *desc;
	uint16_t length;
} usb_hid_report_desc_hdlr_t;

extern usb_hid_report_desc_hdlr_t air_usb_hid_report_descs[AIR_USB_REPORT_DESC_NUM];

#endif /* __AIROHA_USB_HID_DESC_H__ */
