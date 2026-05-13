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

#ifdef AIR_USB_HID_ENABLE

#include <inttypes.h>
#include "air_usb_hid_desc.h"

#define AIR_USB_HID_MUX_ENABLE
#define AIR_USB_HID_GAMING_MS_ENABLE
#define AIR_USB_HID_GAMING_MS_NV_ENABLE
#define AIR_USB_HID_GAMING_KB_ENABLE
#define AIR_USB_HID_GAMING_KB_NKEY_ENABLE
#define AIR_USB_HID_OFFICE_MS_ENABLE
#define AIR_USB_HID_OFFICE_KB_ENABLE
#define AIR_USB_HID_CONSUMER_ENABLE
#define AIR_USB_HID_GAMEPAD_ENABLE

#define USB_HID_AIR_OUT_REPORT_ID 0x06
#define USB_HID_AIR_IN_REPORT_ID  0x07

#define AIR_USB_HID_CUSTOM_OUT_REPORT_ID AIR_USB_HID_CUSTOM_SET_REPORT_ID
#define AIR_USB_HID_CUSTOM_IN_REPORT_ID  AIR_USB_HID_CUSTOM_GET_REPORT_ID

#define AIR_USB_HID_CUSTOM_OUT_REPORT_LEN AIR_USB_HID_CUSTOM_SET_REPORT_LEN
#define AIR_USB_HID_CUSTOM_IN_REPORT_LEN  AIR_USB_HID_CUSTOM_GET_REPORT_LEN

/* clang-format off */
/**
 * Airoha In/Out report for Race, FOTA and HID logging via mux module
 *
 * Report ID 0x06(Out) as MUX_USB_HID_2 RX
 * Report ID 0x07(In)  as MUX_USB_HID_2 TX
 */
const uint8_t report_mux_desc[] = {
#ifdef AIR_USB_HID_MUX_ENABLE
    /* Airoha In/Out Report */
    0x06, 0x13, 0xFF,                           // Usage Page (Vendor-defined ,0xFF13)
    0x09, 0x01,                                 // Usage      (Vendor-defined ,0x0001)
    0xA1, 0x01,                                 // Collection (Application)
    0x15, 0x00,                                 // Logical minimum (0)
    0x26, 0xFF, 0x00,                           // Logical maximum (255)
    // Output Report
    0x85, USB_HID_AIR_OUT_REPORT_ID,            // Report Id (6)
    0x09, 0x00,                                 // Usage  (Vendor-defined ,0x0000)
    0x75, 0x08,                                 // Report Size  (8)
    0x95, 0x3D,                                 // Report Count (61)
    0x91, 0x02,                                 // Output (Data,Value,Absolute,Bit Field)
    // Input Report
    0x85, USB_HID_AIR_IN_REPORT_ID,             // Report Id (7)
    0x09, 0x00,                                 // Usage  (Vendor-defined ,0x0000)
    0x75, 0x08,                                 // Report Size  (8)
    0x95, 0x3D,                                 // Report Count (61)
    0x81, 0x02,                                 // Input    (Data,Value,Absolute,Bit Field)
	// Feature Report
    0x85, AIR_USB_HID_FEATURE_REPORT_ID,        // Report ID (0x14)
    0x09, 0x00,                                 // Usage  (Vendor-defined ,0x0000)
    0x75, 0x08,                                 // Report Size (8)
    0x95, (AIR_USB_HID_FEATURE_REPORT_LEN - 1), // Report Count (61)
    0xB2, 0x02, 0x01,                           // Feature (Data, Array, Absolute)
    0xC0,                                       // End Collection
#endif
};

/**
 * Airoha In/Out report for Bootloader DFU
 *
 * Report ID 0x06(Out) as MUX_USB_HID_2 RX
 * Report ID 0x07(In)  as MUX_USB_HID_2 TX
 */
const uint8_t report_mux2_desc[] = {
    /* Airoha In/Out Report */
    0x06, 0x13, 0xFF,                           // Usage Page (Vendor-defined ,0xFF13)
    0x09, 0x01,                                 // Usage      (Vendor-defined ,0x0001)
    0xA1, 0x01,                                 // Collection (Application)
    0x15, 0x00,                                 // Logical minimum (0)
    0x26, 0xFF, 0x00,                           // Logical maximum (255)
    // Output Report
    0x85, AIR_USB_HID_AIR2_OUT_REPORT_ID,       //   Report ID (8)
    0x09, 0x00,                                 //   Usage (0x00)
    0x75, 0x08,                                 //   Report Size (8)
    0x96, 0xFF, 0x03,                           //   Report Count (1023)
    0x91, 0x02,                                 //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    // Input Report
    0x85, AIR_USB_HID_AIR2_IN_REPORT_ID,        //   Report ID (9)
    0x09, 0x00,                                 //   Usage (0x00)
    0x75, 0x08,                                 //   Report Size (8)
    0x96, 0xFF, 0x03,                           //   Report Count (1023)
    0x81, 0x02,                                 //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	// Feature Report
    0x85, AIR_USB_HID_BL_DFU_FEATURE_REPORT_ID, // Report ID (0x30)
    0x09, 0x00,                                 // Usage  (Vendor-defined ,0x0000)
    0x75, 0x08,                                 // Report Size (8)
    0x96, 0xFF, 0x03,                           // Report Count (1023)
    0xB2, 0x02, 0x01,                           // Feature (Data, Array, Absolute)
    0xC0,                                       // End Collection
};

/**
 * Endpoint In/Out Report
 *
 * This is a simple example report for Interrupt IN/OUT endpoint.
 *
 * IN  Report - ID:0x2E, LEN:64
 * OUT Report - ID:0x2F, LEN:64
 */
const uint8_t report_epio_desc[] = {
    0x06, 0x14, 0xFF,                           // Usage Page (Vendor Defined 0xFF14)
    0x09, 0x01,                                 // Usage (0x01)
    0xA1, 0x01,                                 // Collection (Application)
    0x15, 0x00,                                 //   Logical Minimum (0)
    0x26, 0xFF, 0x00,                           //   Logical Maximum (255)
    0x85, AIR_USB_HID_EPIO_RX_REPORT_ID,        //   Report ID (46)
    0x09, 0x00,                                 //   Usage (0x00)
    0x75, 0x08,                                 //   Report Size (8)
    0x95, 0x3F,                                 //   Report Count (63)
    0x91, 0x02,                                 //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, AIR_USB_HID_EPIO_TX_REPORT_ID,        //   Report ID (47)
    0x09, 0x00,                                 //   Usage (0x00)
    0x75, 0x08,                                 //   Report Size (8)
    0x95, 0x3F,                                 //   Report Count (63)
    0x81, 0x02,                                 //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,                                       // End Collection
};

static const uint8_t report_gaming_ms_desc[] = {
#ifdef AIR_USB_HID_GAMING_MS_ENABLE
	0x05, 0x01,                             // Usage Page (Generic Desktop Ctrls)
	0x09, 0x02,                             // Usage (Mouse)
	0xA1, 0x01,                             // Collection (Application)
	0x09, 0x01,                             //   Usage (Pointer)
	0xA1, 0x00,                             //   Collection (Physical)
	0x85, AIR_USB_HID_GAMING_MS_REPORT_ID,  //     Report ID (02)
	0x75, 0x01,                             //     Report Size (1)
	0x95, 0x08,                             //     Report Count (8)
	0x15, 0x00,                             //     Logical Minimum (0)
	0x25, 0x01,                             //     Logical Maximum (1)
	0x05, 0x09,                             //     Usage Page (Button)
	0x19, 0x01,                             //     Usage Minimum (0x01)
	0x29, 0x08,                             //     Usage Maximum (0x08)
	0x81, 0x02,                             //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x05, 0x01,                             //     Usage Page (Generic Desktop Ctrls)
	0x16, 0x01, 0x80,                       //     Logical Minimum (-32767)
	0x26, 0xFF, 0x7F,                       //     Logical Maximum (32767)
	0x75, 0x10,                             //     Report Size (16)
	0x95, 0x02,                             //     Report Count (2)
	0x09, 0x30,                             //     Usage (X)
	0x09, 0x31,                             //     Usage (Y)
	0x81, 0x06,                             //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
	0x15, 0x81,                             //     Logical Minimum (-127)
	0x25, 0x7F,                             //     Logical Maximum (127)
	0x75, 0x08,                             //     Report Size (8)
	0x95, 0x01,                             //     Report Count (1)
	0x09, 0x38,                             //     Usage (Wheel)
	0x81, 0x06,                             //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
	0x95, 0x01,                             //     Report Count (1)
	0x05, 0x0C,                             //     Usage Page (Consumer)
	0x0A, 0x38, 0x02,                       //     Usage (AC Pan)
	0x81, 0x06,                             //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
	0xC0,                                   //   End Collection
	0xC0,                                   // End Collection
#endif
};

static const uint8_t report_gaming_ms_nv_desc[] = {
#ifdef AIR_USB_HID_GAMING_MS_NV_ENABLE
	0x05, 0x01,                             // Usage Page (Generic Desktop Ctrls)
	0x09, 0x02,                             // Usage (Mouse)
	0xA1, 0x01,                             // Collection (Application)
	0x09, 0x01,                             //   Usage (Pointer)
	0xA1, 0x00,                             //   Collection (Physical)
	0x85, AIR_USB_HID_GAMING_MS_NV_REPORT_ID, //     Report ID (3)
	0x75, 0x01,                             //     Report Size (1)
	0x95, 0x08,                             //     Report Count (8)
	0x15, 0x00,                             //     Logical Minimum (0)
	0x25, 0x01,                             //     Logical Maximum (1)
	0x05, 0x09,                             //     Usage Page (Button)
	0x19, 0x01,                             //     Usage Minimum (0x01)
	0x29, 0x10,                             //     Usage Maximum (0x10)
	0x81, 0x02,                             //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x09, 0x00,                             //     Usage (Unassigned)
	0x75, 0x01,                             //     Report Size (1)
	0x95, 0x08,                             //     Report Count (8)
	0x81, 0x01,                             //     Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x05, 0x01,                             //     Usage Page (Generic Desktop Ctrls)
	0x16, 0x01, 0x80,                       //     Logical Minimum (-32767)
	0x26, 0xFF, 0x7F,                       //     Logical Maximum (32767)
	0x75, 0x10,                             //     Report Size (16)
	0x95, 0x02,                             //     Report Count (2)
	0x09, 0x30,                             //     Usage (X)
	0x09, 0x31,                             //     Usage (Y)
	0x81, 0x06,                             //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
	0x15, 0x81,                             //     Logical Minimum (-127)
	0x25, 0x7F,                             //     Logical Maximum (127)
	0x75, 0x08,                             //     Report Size (8)
	0x95, 0x01,                             //     Report Count (1)
	0x09, 0x38,                             //     Usage (Wheel)
	0x81, 0x06,                             //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
	0x95, 0x01,                             //     Report Count (1)
	0x06, 0x00, 0xFF,                       //     Usage Page (Vendor Defined 0xFF00)
	0x09, 0xF1,                             //     Usage (0xF1)
	0x75, 0x08,                             //     Report Size (8)
	0x95, 0x05,                             //     Report Count (5)
	0x15, 0x00,                             //     Logical Minimum (0)
	0x26, 0xFF, 0x00,                       //     Logical Maximum (255)
	0x81, 0x00,                             //     Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0xC0,                                   //   End Collection
	0xC0,                                   // End Collection
	// 84 bytes
#endif
};

static const uint8_t report_gaming_kb_desc[] = {
#ifdef AIR_USB_HID_GAMING_KB_ENABLE
	0x05, 0x01,                             // Usage Page (Generic Desktop Ctrls)
	0x09, 0x06,                             // Usage (Keyboard)
	0xA1, 0x01,                             // Collection (Application)
	0x85, AIR_USB_HID_GAMING_KB_REPORT_ID,  //   Report ID (1)
	0x05, 0x07,                             //   Usage Page (Kbrd/Keypad)
	0x19, 0xE0,                             //   Usage Minimum (0xE0)
	0x29, 0xE7,                             //   Usage Maximum (0xE7)
	0x15, 0x00,                             //   Logical Minimum (0)
	0x25, 0x01,                             //   Logical Maximum (1)
	0x75, 0x01,                             //   Report Size (1)
	0x95, 0x08,                             //   Report Count (8)
	0x81, 0x02,                             //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x95, 0x05,                             //   Report Count (5)
	0x05, 0x08,                             //   Usage Page (LEDs)
	0x19, 0x01,                             //   Usage Minimum (Num Lock)
	0x29, 0x05,                             //   Usage Maximum (Kana)
	0x91, 0x02,                             //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
	0x95, 0x01,                             //   Report Count (1)
	0x75, 0x03,                             //   Report Size (3)
	0x91, 0x01,                             //   Output (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
	0x95, 0x05,                             //   Report Count (5)
	0x75, 0x08,                             //   Report Size (8)
	0x15, 0x00,                             //   Logical Minimum (0)
	0x26, 0xA4, 0x00,                       //   Logical Maximum (164)
	0x05, 0x07,                             //   Usage Page (Kbrd/Keypad)
	0x19, 0x00,                             //   Usage Minimum (0x00)
	0x2A, 0xA4, 0x00,                       //   Usage Maximum (0xA4)
	0x81, 0x00,                             //   Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0xC0,                                   // End Collection
	// 59 bytes
#endif
};

static const uint8_t report_gaming_kb_nkey_desc[] = {
#ifdef AIR_USB_HID_GAMING_KB_NKEY_ENABLE
	0x05, 0x01,                             // Usage Page (Generic Desktop Ctrls)
	0x09, 0x06,                             // Usage (Keyboard)
	0xA1, 0x01,                             // Collection (Application)
	0x85, AIR_USB_HID_GAMING_KB_NKEY_REPORT_ID, //   Report ID (1)
	0x05, 0x07,                             //   Usage Page (Kbrd/Keypad)
	0x19, 0xE0,                             //   Usage Minimum (0xE0)
	0x29, 0xE7,                             //   Usage Maximum (0xE7)
	0x15, 0x00,                             //   Logical Minimum (0)
	0x25, 0x01,                             //   Logical Maximum (1)
	0x75, 0x01,                             //   Report Size (1)
	0x95, 0x08,                             //   Report Count (8)
	0x81, 0x02,                             //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x95, 0x05,                             //   Report Count (5)
	0x05, 0x08,                             //   Usage Page (LEDs)
	0x19, 0x01,                             //   Usage Minimum (Num Lock)
	0x29, 0x05,                             //   Usage Maximum (Kana)
	0x91, 0x02,                             //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
	0x95, 0x01,                             //   Report Count (1)
	0x75, 0x03,                             //   Report Size (3)
	0x91, 0x01,                             //   Output (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
	0x05, 0x07,                             //   Usage Page (Kbrd/Keypad)
	0x15, 0x00,                             //   Logical Minimum (0)
	0x25, 0x01,                             //   Logical Maximum (1)
	0x19, 0x00,                             //   Usage Minimum (0x00)
	0x29, 0x77,                             //   Usage Maximum (0x77)
	0x75, 0x01,                             //   Report Size (1)
	0x95, 0x78,                             //   Report Count (120)
	0x81, 0x02,                             //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0xC0,                                   // End Collection
	// 57 bytes
#endif
};

static const uint8_t report_office_ms_desc[] = {
#ifdef AIR_USB_HID_OFFICE_MS_ENABLE
	0x05, 0x01,                             // Usage Page (Generic Desktop Ctrls)
	0x09, 0x02,                             // Usage (Mouse)
	0xA1, 0x01,                             // Collection (Application)
	0x85, AIR_USB_HID_OFFICE_MS_REPORT_ID,  //   Report ID (2)
	0x09, 0x01,                             //   Usage (Pointer)
	0xA1, 0x00,                             //   Collection (Physical)
	0x05, 0x09,                             //     Usage Page (Button)
	0x19, 0x01,                             //     Usage Minimum (0x01)
	0x29, 0x10,                             //     Usage Maximum (0x10)
	0x15, 0x00,                             //     Logical Minimum (0)
	0x25, 0x01,                             //     Logical Maximum (1)
	0x95, 0x10,                             //     Report Count (16)
	0x75, 0x01,                             //     Report Size (1)
	0x81, 0x02,                             //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x05, 0x01,                             //     Usage Page (Generic Desktop Ctrls)
	0x16, 0x01, 0x80,                       //     Logical Minimum (-32767)
	0x26, 0xFF, 0x7F,                       //     Logical Maximum (32767)
	0x75, 0x10,                             //     Report Size (16)
	0x95, 0x02,                             //     Report Count (2)
	0x09, 0x30,                             //     Usage (X)
	0x09, 0x31,                             //     Usage (Y)
	0x81, 0x06,                             //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
	0x15, 0x81,                             //     Logical Minimum (-127)
	0x25, 0x7F,                             //     Logical Maximum (127)
	0x75, 0x08,                             //     Report Size (8)
	0x95, 0x01,                             //     Report Count (1)
	0x09, 0x38,                             //     Usage (Wheel)
	0x81, 0x06,                             //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
	0x05, 0x0C,                             //     Usage Page (Consumer)
	0x0A, 0x38, 0x02,                       //     Usage (AC Pan)
	0x95, 0x01,                             //     Report Count (1)
	0x81, 0x06,                             //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
	0xC0,                                   //   End Collection
	0xC0,                                   // End Collection
	// 69 bytes
	#endif
};

static const uint8_t report_office_kb_desc[] = {
#ifdef AIR_USB_HID_OFFICE_KB_ENABLE
	0x05, 0x01,                             // Usage Page (Generic Desktop Ctrls)
	0x09, 0x06,                             // Usage (Keyboard)
	0xA1, 0x01,                             // Collection (Application)
	0x85, AIR_USB_HID_OFFICE_KB_REPORT_ID,  //   Report ID (1)
	0x05, 0x07,                             //   Usage Page (Kbrd/Keypad)
	0x19, 0xE0,                             //   Usage Minimum (0xE0)
	0x29, 0xE7,                             //   Usage Maximum (0xE7)
	0x15, 0x00,                             //   Logical Minimum (0)
	0x25, 0x01,                             //   Logical Maximum (1)
	0x75, 0x01,                             //   Report Size (1)
	0x95, 0x08,                             //   Report Count (8)
	0x81, 0x02,                             //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x95, 0x05,                             //   Report Count (5)
	0x05, 0x08,                             //   Usage Page (LEDs)
	0x19, 0x01,                             //   Usage Minimum (Num Lock)
	0x29, 0x05,                             //   Usage Maximum (Kana)
	0x91, 0x02,                             //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
	0x95, 0x01,                             //   Report Count (1)
	0x75, 0x03,                             //   Report Size (3)
	0x91, 0x01,                             //   Output (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
	0x95, 0x06,                             //   Report Count (6)
	0x75, 0x08,                             //   Report Size (8)
	0x15, 0x00,                             //   Logical Minimum (0)
	0x26, 0xA4, 0x00,                       //   Logical Maximum (164)
	0x05, 0x07,                             //   Usage Page (Kbrd/Keypad)
	0x19, 0x00,                             //   Usage Minimum (0x00)
	0x2A, 0xA4, 0x00,                       //   Usage Maximum (0xA4)
	0x81, 0x00,                             //   Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0xC0,                                   // End Collection
	// 59 bytes
#endif
};

static const uint8_t report_consumer_desc[] = {
#ifdef AIR_USB_HID_CONSUMER_ENABLE
	0x05, 0x0C,                             // Usage Page (Consumer)
	0x09, 0x01,                             // Usage (Consumer Control)
	0xA1, 0x01,                             // Collection (Application)
	0x85, AIR_USB_HID_CONSUMER_REPORT_ID,   //   Report ID (12)
	0x19, 0x00,                             //   Usage Minimum (Unassigned)
	0x2A, 0xFF, 0x0F,                       //   Usage Maximum (0x0FFF)
	0x15, 0x00,                             //   Logical Minimum (0)
	0x26, 0xFF, 0x0F,                       //   Logical Maximum (4095)
	0x95, 0x02,                             //   Report Count (2)
	0x75, 0x10,                             //   Report Size (16)
	0x81, 0x00,                             //   Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x09, 0x02,                             //   Usage (Numeric Key Pad)
	0xA1, 0x02,                             //   Collection (Logical)
	0x05, 0x09,                             //     Usage Page (Button)
	0x19, 0x01,                             //     Usage Minimum (0x01)
	0x29, 0x0A,                             //     Usage Maximum (0x0A)
	0x15, 0x01,                             //     Logical Minimum (1)
	0x25, 0x0A,                             //     Logical Maximum (10)
	0x95, 0x01,                             //     Report Count (1)
	0x75, 0x08,                             //     Report Size (8)
	0x81, 0x40,                             //     Input (Data,Array,Abs,No Wrap,Linear,Preferred State,Null State)
	0xC0,                                   //   End Collection
	0xC0,                                   // End Collection
	// 46 bytes
#endif
};

static const uint8_t report_custom_desc[] = {
#if 1
	0x06, 0x15, 0xFF,                               // Usage Page (Vendor Defined 0xFF15)
	0x09, 0x01,                                     // Usage (0x01)
	0xA1, 0x01,                                     // Collection (Application)
	0x15, 0x00,                                     // Logical Minimum (0)
	0x26, 0xFF, 0x00,                               // Logical maximum (255)
	0x85, AIR_USB_HID_CUSTOM_FEATURE_REPORT_ID,     // Report ID (0x17)
	0x09, 0x00,                                     // Usage  (Vendor-defined ,0x0000)
	0x75, 0x08,                                     // Report Size (8)
	0x95, (AIR_USB_HID_CUSTOM_FEATURE_REPORT_LEN - 1), // Report Count (63)
	0xB2, 0x02, 0x01,                               // Feature (Data, Array, Absolute)
	// Output Report
	0x85, AIR_USB_HID_CUSTOM_OUT_REPORT_ID,         // Report Id (0x15)
	0x09, 0x00,                                     // Usage  (Vendor-defined ,0x0000)
	0x75, 0x08,                                     // Report Size  (8)
	0x95, (AIR_USB_HID_CUSTOM_OUT_REPORT_LEN - 1),  // Report Count (63)
	0x91, 0x02,                                     // Output (Data,Value,Absolute,Bit Field)
	// Input Report
	0x85, AIR_USB_HID_CUSTOM_IN_REPORT_ID,          // Report Id (0x16)
	0x09, 0x00,                                     // Usage  (Vendor-defined ,0x0000)
	0x75, 0x08,                                     // Report Size  (8)
	0x95, (AIR_USB_HID_CUSTOM_IN_REPORT_LEN - 1),   // Report Count (63)
	0x81, 0x02,                                     // Input    (Data,Value,Absolute,Bit Field)
	0xC0,                                           // End Collection
	// 44 bytes
#endif
};

const uint8_t report_gamepad_desc[] = {
#if 0
#ifdef AIR_USB_HID_GAMEPAD_ENABLE
    0x05, 0x01,                             // Usage Page (Generic Desktop Ctrls)
    0x09, 0x05,                             // Usage (Game Pad)
    0xA1, 0x01,                             // Collection (Application)
    0xA1, 0x02,                             //   Collection (Logical)
    0x85, USB_HID_GAMEPAD_REPORT_ID,        //     Report ID (13)
    0x15, 0x00,                             //     Logical Minimum (0)
    0x25, 0x01,                             //     Logical Maximum (1)
    0x35, 0x00,                             //     Physical Minimum (0)
    0x45, 0x01,                             //     Physical Maximum (1)
    0x75, 0x01,                             //     Report Size (1)
    0x95, 0x0F,                             //     Report Count (15)
    0x05, 0x09,                             //     Usage Page (Button)
    0x19, 0x01,                             //     Usage Minimum (0x01)
    0x29, 0x0F,                             //     Usage Maximum (0x0F)
    0x81, 0x02,                             //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x01,                             //     Report Count (1)
    0x81, 0x01,                             //     Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01,                             //     Usage Page (Generic Desktop Ctrls)
    0x25, 0x07,                             //     Logical Maximum (7)
    0x46, 0x3B, 0x01,                       //     Physical Maximum (315)
    0x75, 0x04,                             //     Report Size (4)
    0x95, 0x01,                             //     Report Count (1)
    0x65, 0x14,                             //     Unit (System: English Rotation, Length: Centimeter)
    0x09, 0x39,                             //     Usage (Hat switch)
    0x81, 0x42,                             //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,Null State)
    0x65, 0x00,                             //     Unit (None)
    0x95, 0x01,                             //     Report Count (1)
    0x81, 0x01,                             //     Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x26, 0xFF, 0xFF,                       //     Logical Maximum (-1)
    0x46, 0xFF, 0xFF,                       //     Physical Maximum (-1)
    0x09, 0x30,                             //     Usage (X)
    0x09, 0x31,                             //     Usage (Y)
    0x09, 0x32,                             //     Usage (Z)
    0x09, 0x35,                             //     Usage (Rz)
    0x75, 0x10,                             //     Report Size (16)
    0x95, 0x04,                             //     Report Count (4)
    0x81, 0x02,                             //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x02,                             //     Usage Page (Sim Ctrls)
    0x09, 0xC5,                             //     Usage (Brake)
    0x15, 0x00,                             //     Logical Minimum (0)
    0x26, 0xFF, 0x03,                       //     Logical Maximum (1023)
    0x95, 0x01,                             //     Report Count (1)
    0x75, 0x0A,                             //     Report Size (10)
    0x81, 0x02,                             //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x15, 0x00,                             //     Logical Minimum (0)
    0x25, 0x00,                             //     Logical Maximum (0)
    0x75, 0x06,                             //     Report Size (6)
    0x95, 0x01,                             //     Report Count (1)
    0x81, 0x03,                             //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,                                   //   End Collection
    0xC0,                                   // End Collection
    // 104 bytes
#endif
#endif

#if 1
#ifdef AIR_USB_HID_GAMEPAD_ENABLE
    0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
    0x09, 0x05,        // Usage (Game Pad)
    0xA1, 0x01,        // Collection (Application)
    0x85, AIR_USB_HID_GAMEPAD_REPORT_ID,        //   Report ID (0x13)
    0x09, 0x01,        //   Usage (Pointer)
    0xA1, 0x00,        //   Collection (Physical)
    0x09, 0x30,        //     Usage (X)
    0x09, 0x31,        //     Usage (Y)
    0x15, 0x00,        //     Logical Minimum (0)
    0x27, 0xFF, 0xFF, 0x00, 0x00,  //     Logical Maximum (65534)
    0x95, 0x02,        //     Report Count (2)
    0x75, 0x10,        //     Report Size (16)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              //   End Collection
    0x09, 0x01,        //   Usage (Pointer)
    0xA1, 0x00,        //   Collection (Physical)
    0x09, 0x32,        //     Usage (Z)
    0x09, 0x35,        //     Usage (Rz)
    0x15, 0x00,        //     Logical Minimum (0)
    0x27, 0xFF, 0xFF, 0x00, 0x00,  //     Logical Maximum (65534)
    0x95, 0x02,        //     Report Count (2)
    0x75, 0x10,        //     Report Size (16)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              //   End Collection
    0x05, 0x02,        //   Usage Page (Sim Ctrls)
    0x09, 0xC5,        //   Usage (Brake)
    0x15, 0x00,        //   Logical Minimum (0)
    0x26, 0xFF, 0x03,  //   Logical Maximum (1023)
    0x95, 0x01,        //   Report Count (1)
    0x75, 0x0A,        //   Report Size (10)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x15, 0x00,        //   Logical Minimum (0)
    0x25, 0x00,        //   Logical Maximum (0)
    0x75, 0x06,        //   Report Size (6)
    0x81, 0x03,        //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x09, 0xC4,        //   Usage (Accelerator)
    0x15, 0x00,        //   Logical Minimum (0)
    0x26, 0xFF, 0x03,  //   Logical Maximum (1023)
    0x95, 0x01,        //   Report Count (1)
    0x75, 0x0A,        //   Report Size (10)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x15, 0x00,        //   Logical Minimum (0)
    0x25, 0x00,        //   Logical Maximum (0)
    0x75, 0x06,        //   Report Size (6)
    0x81, 0x03,        //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01,        //   Usage Page (Generic Desktop Ctrls)
    0x09, 0x39,        //   Usage (Hat switch)
    0x15, 0x01,        //   Logical Minimum (1)
    0x25, 0x08,        //   Logical Maximum (8)
    0x35, 0x00,        //   Physical Minimum (0)
    0x46, 0x3B, 0x01,  //   Physical Maximum (315)
    0x66, 0x14, 0x00,  //   Unit (System: English Rotation, Length: Centimeter)
    0x75, 0x04,        //   Report Size (4)
    0x95, 0x01,        //   Report Count (1)
    0x81, 0x42,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,Null State)
    0x75, 0x04,        //   Report Size (4)
    0x95, 0x01,        //   Report Count (1)
    0x81, 0x03,        //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x09,        //   Usage Page (Button)
    0x19, 0x01,        //   Usage Minimum (0x01)
    0x29, 0x0F,        //   Usage Maximum (0x0F)
    0x15, 0x00,        //   Logical Minimum (0)
    0x25, 0x01,        //   Logical Maximum (1)
    0x75, 0x01,        //   Report Size (1)
    0x95, 0x0F,        //   Report Count (15)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x75, 0x01,        //   Report Size (1)
    0x95, 0x01,        //   Report Count (1)
    0x81, 0x03,        //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x0C,        //   Usage Page (Consumer)
    0x0A, 0xB2, 0x00,  //   Usage (Record)
    0x15, 0x00,        //   Logical Minimum (0)
    0x25, 0x01,        //   Logical Maximum (1)
    0x75, 0x01,        //   Report Size (1)
    0x95, 0x01,        //   Report Count (1)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x75, 0x07,        //   Report Size (7)
    0x95, 0x01,        //   Report Count (1)
    0x81, 0x03,        //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x0F,        //   Usage Page (PID Page)
    0x09, 0x21,        //   Usage (0x21)
    0x85, 0x03,        //   Report ID (3)
    0xA1, 0x02,        //   Collection (Logical)
    0x09, 0x97,        //     Usage (0x97)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x01,        //     Logical Maximum (1)
    0x75, 0x04,        //     Report Size (4)
    0x95, 0x01,        //     Report Count (1)
    0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x00,        //     Logical Maximum (0)
    0x75, 0x04,        //     Report Size (4)
    0x95, 0x01,        //     Report Count (1)
    0x91, 0x03,        //     Output (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x09, 0x70,        //     Usage (0x70)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x64,        //     Logical Maximum (100)
    0x75, 0x08,        //     Report Size (8)
    0x95, 0x04,        //     Report Count (4)
    0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x09, 0x50,        //     Usage (0x50)
    0x66, 0x01, 0x10,  //     Unit (System: SI Linear, Time: Seconds)
    0x55, 0x0E,        //     Unit Exponent (-2)
    0x15, 0x00,        //     Logical Minimum (0)
    0x26, 0xFF, 0x00,  //     Logical Maximum (255)
    0x75, 0x08,        //     Report Size (8)
    0x95, 0x01,        //     Report Count (1)
    0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x09, 0xA7,        //     Usage (0xA7)
    0x15, 0x00,        //     Logical Minimum (0)
    0x26, 0xFF, 0x00,  //     Logical Maximum (255)
    0x75, 0x08,        //     Report Size (8)
    0x95, 0x01,        //     Report Count (1)
    0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x65, 0x00,        //     Unit (None)
    0x55, 0x00,        //     Unit Exponent (0)
    0x09, 0x7C,        //     Usage (0x7C)
    0x15, 0x00,        //     Logical Minimum (0)
    0x26, 0xFF, 0x00,  //     Logical Maximum (255)
    0x75, 0x08,        //     Report Size (8)
    0x95, 0x01,        //     Report Count (1)
    0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0,              //   End Collection
    0xC0,              // End Collection
    // 259 bytes
#endif
#endif
};

static const uint8_t report_gaming_ms_no_report_id_desc[] = {
#ifdef AIR_USB_HID_GAMING_MS_ENABLE
	0x05, 0x01,                             // Usage Page (Generic Desktop Ctrls)
	0x09, 0x02,                             // Usage (Mouse)
	0xA1, 0x01,                             // Collection (Application)
	0x09, 0x01,                             //   Usage (Pointer)
	0xA1, 0x00,                             //   Collection (Physical)
	0x75, 0x01,                             //     Report Size (1)
	0x95, 0x08,                             //     Report Count (8)
	0x15, 0x00,                             //     Logical Minimum (0)
	0x25, 0x01,                             //     Logical Maximum (1)
	0x05, 0x09,                             //     Usage Page (Button)
	0x19, 0x01,                             //     Usage Minimum (0x01)
	0x29, 0x08,                             //     Usage Maximum (0x08)
	0x81, 0x02,                             //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x05, 0x01,                             //     Usage Page (Generic Desktop Ctrls)
	0x16, 0x01, 0xF8,                       //     Logical Minimum (-2047)
	0x26, 0xFF, 0x07,                       //     Logical Maximum (2047)
	0x75, 0x0C,                             //     Report Size (12)
	0x95, 0x02,                             //     Report Count (2)
	0x09, 0x30,                             //     Usage (X)
	0x09, 0x31,                             //     Usage (Y)
	0x81, 0x06,                             //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
	0x15, 0x81,                             //     Logical Minimum (-127)
	0x25, 0x7F,                             //     Logical Maximum (127)
	0x75, 0x08,                             //     Report Size (8)
	0x95, 0x01,                             //     Report Count (1)
	0x09, 0x38,                             //     Usage (Wheel)
	0x81, 0x06,                             //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
	0x95, 0x01,                             //     Report Count (1)
	0x05, 0x0C,                             //     Usage Page (Consumer)
	0x0A, 0x38, 0x02,                       //     Usage (AC Pan)
	0x81, 0x06,                             //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
	0xC0,                                   //   End Collection
	0xC0,                                   // End Collection
#endif
};

static const uint8_t report_custom_no_report_id_desc[] = {
#if 1
	0x06, 0x15, 0xFF,                               // Usage Page (Vendor Defined 0xFF15)
	0x09, 0x01,                                     // Usage (0x01)
	0xA1, 0x01,                                     // Collection (Application)
	0x15, 0x00,                                     // Logical Minimum (0)
	0x26, 0xFF, 0x00,                               // Logical maximum (255)
	0x09, 0x00,                                     // Usage  (Vendor-defined ,0x0000)
	0x75, 0x08,                                     // Report Size (8)
	0x95, AIR_USB_HID_CUSTOM_FEATURE_REPORT_LEN,    // Report Count (64)
	0xB2, 0x02, 0x01,                               // Feature (Data, Array, Absolute)
	// Output Report
	0x09, 0x00,                                     // Usage  (Vendor-defined ,0x0000)
	0x75, 0x08,                                     // Report Size  (8)
	0x95, AIR_USB_HID_CUSTOM_OUT_REPORT_LEN,        // Report Count (64)
	0x91, 0x02,                                     // Output (Data,Value,Absolute,Bit Field)
	// Input Report
	0x09, 0x00,                                     // Usage  (Vendor-defined ,0x0000)
	0x75, 0x08,                                     // Report Size  (8)
	0x95, AIR_USB_HID_CUSTOM_IN_REPORT_LEN,         // Report Count (64)
	0x81, 0x02,                                     // Input    (Data,Value,Absolute,Bit Field)
	0xC0,                                           // End Collection
	// 44 bytes
#endif
};
/* clang-format on */

#define REPORT_DESC_STRUCT(NAME, DESC)                                                             \
	[AIR_USB_REPORT_DESC_##NAME] = {                                                           \
		.type = AIR_USB_REPORT_DESC_##NAME,                                                \
		.name = #NAME,                                                                     \
		.desc = (void *)DESC,                                                              \
		.length = sizeof(DESC),                                                            \
	}

/* clang-format off */
usb_hid_report_desc_hdlr_t air_usb_hid_report_descs[] = {
    REPORT_DESC_STRUCT(MUX,            report_mux_desc),
    REPORT_DESC_STRUCT(MUX2,           report_mux2_desc),
    REPORT_DESC_STRUCT(EPIO,           report_epio_desc),
    REPORT_DESC_STRUCT(GAMING_MS,      report_gaming_ms_desc),
    REPORT_DESC_STRUCT(GAMING_MS_NV,   report_gaming_ms_nv_desc),
    REPORT_DESC_STRUCT(GAMING_KB,      report_gaming_kb_desc),
    REPORT_DESC_STRUCT(GAMING_KB_NKEY, report_gaming_kb_nkey_desc),
    REPORT_DESC_STRUCT(OFFICE_MS,      report_office_ms_desc),
    REPORT_DESC_STRUCT(OFFICE_KB,      report_office_kb_desc),
    REPORT_DESC_STRUCT(CONSUMER,       report_consumer_desc),
    REPORT_DESC_STRUCT(CUSTOM,         report_custom_desc),
    REPORT_DESC_STRUCT(GAMEPAD,        report_gamepad_desc),
    REPORT_DESC_STRUCT(CUSTOM_NO_REPORT_ID,         report_custom_no_report_id_desc),
    REPORT_DESC_STRUCT(GAMING_MS_NO_REPORT_ID,      report_gaming_ms_no_report_id_desc),
};
/* clang-format on */

_Static_assert(((sizeof(air_usb_hid_report_descs) / sizeof(usb_hid_report_desc_hdlr_t)) ==
		AIR_USB_REPORT_DESC_NUM),
	       "Report Descriptor number mismatch");

#endif /* AIR_USB_HID_ENABLE */
