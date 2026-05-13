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
 
#if defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
#ifndef __HID_DESCRIPTOR_KEYBOARD_NKEY_H__
#define __HID_DESCRIPTOR_KEYBOARD_NKEY_H__


    0x05, 0x01,                    // Usage Page (Generic Desktop Ctrls)
    0x09, 0x06,                    // Usage (Keyboard)
    0xA1, 0x01,                    // Collection (Application)
    0x85, REPORT_ID_KEYBOARD_NKEY, //   Report ID (4)

    0x75, 0x01,                    //   Report Size (1)
    0x95, 0x08,                    //   Report Count (8)
    0x15, 0x00,                    //   Logical Minimum (0)
    0x25, 0x01,                    //   Logical Maximum (1)
    0x05, 0x07,                    //   Usage Page (Kbrd/Keypad)
    0x19, 0xE0,                    //   Usage Minimum (0xE0)
    0x29, 0xE7,                    //   Usage Maximum (0xE7)
    0x81, 0x02,                    //   Input (Data,Var,Abs)

    0x75, 0x01,                    //   Report Size (1)
    0x95, 0x78,                    //   Report Count (120)
    0x15, 0x00,                    //   Logical Minimum (0)
    0x25, 0x01,                    //   Logical Maximum (1)
    0x05, 0x07,                    //   Usage Page (Kbrd/Keypad)
    0x19, 0x00,                    //   Usage Minimum (0x00)
    0x29, 0x78,                    //   Usage Maximum (0x78)
    0x81, 0x02,                    //   Input (Data,Var,Abs)

    0xC0                           // End Collection

    // 0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
    // 0x09, 0x06,        // Usage (Keyboard)
    // 0xA1, 0x01,        // Collection (Application)
    // 0x85, REPORT_ID_KEYBOARD_NKEY,        //   Report ID (6)
    // 0x75, 0x01, 	   //	Report Size (1)
    // 0x95, 0x08, 	   //	Report Count (8)
    // 0x15, 0x00, 	   //	Logical Minimum (0)
    // 0x25, 0x01, 	   //	Logical Maximum (1)
    // 0x05, 0x07, 	   //	Usage Page (Kbrd/Keypad)
    // 0x19, 0xE0, 	   //	Usage Minimum (0xE0)
    // 0x29, 0xE7, 	   //	Usage Maximum (0xE7)
    // 0x81, 0x02, 	   //	Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    // 0x75, 0x01,        //   Report Size (1)
    // 0x95, 0x28,        //   Report Count (40)
    // 0x15, 0x00,        //   Logical Minimum (0)
    // 0x25, 0x01,        //   Logical Maximum (1)
    // 0x05, 0x07,        //   Usage Page (Kbrd/Keypad)
    // 0x19, 0x00,        //   Usage Minimum (0x00)
    // 0x29, 0x27,        //   Usage Maximum (0x28)
    // 0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    // 0xC0,              // End Collection

    // 0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
    // 0x09, 0x06,        // Usage (Keyboard)
    // 0xA1, 0x01,        // Collection (Application)
    // 0x85, REPORT_ID_KEYBOARD_BIT_REP_1,        //   Report ID (6)
    // 0x75, 0x01, 	   //	Report Size (1)
    // 0x95, 0x08, 	   //	Report Count (8)
    // 0x15, 0x00, 	   //	Logical Minimum (0)
    // 0x25, 0x01, 	   //	Logical Maximum (1)
    // 0x05, 0x07, 	   //	Usage Page (Kbrd/Keypad)
    // 0x19, 0xE0, 	   //	Usage Minimum (0xE0)
    // 0x29, 0xE7, 	   //	Usage Maximum (0xE7)
    // 0x81, 0x02, 	   //	Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    // 0x75, 0x01,        //   Report Size (1)
    // 0x95, 0x28,        //   Report Count (40)
    // 0x15, 0x00,        //   Logical Minimum (0)
    // 0x25, 0x01,        //   Logical Maximum (1)
    // 0x05, 0x07,        //   Usage Page (Kbrd/Keypad)
    // 0x19, 0x00,        //   Usage Minimum (0x00)
    // 0x29, 0x27,        //   Usage Maximum (0x28)
    // 0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    // 0xC0,              // End Collection

    // 0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
    // 0x09, 0x06,        // Usage (Keyboard)
    // 0xA1, 0x01,        // Collection (Application)
    // 0x85, REPORT_ID_KEYBOARD_BIT_REP_2,        //   Report ID (7)
    // 0x75, 0x01,        //   Report Size (1)
    // 0x95, 0x28,        //   Report Count (40)
    // 0x15, 0x00,        //   Logical Minimum (0)
    // 0x25, 0x01,        //   Logical Maximum (1)
    // 0x05, 0x07,        //   Usage Page (Kbrd/Keypad)
    // 0x19, 0x28,        //   Usage Minimum (0x28)
    // 0x29, 0x4F,        //   Usage Maximum (0x50)
    // 0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    // 0xC0,              // End Collection

    // 0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
    // 0x09, 0x06,        // Usage (Keyboard)
    // 0xA1, 0x01,        // Collection (Application)
    // 0x85, REPORT_ID_KEYBOARD_BIT_REP_3,        //   Report ID (8)
    // 0x75, 0x01,        //   Report Size (1)
    // 0x95, 0x28,        //   Report Count (40)
    // 0x15, 0x00,        //   Logical Minimum (0)
    // 0x25, 0x01,        //   Logical Maximum (1)
    // 0x05, 0x07,        //   Usage Page (Kbrd/Keypad)
    // 0x19, 0x50,        //   Usage Minimum (0x50)
    // 0x29, 0x77,        //   Usage Maximum (0x78)
    // 0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    // 0xC0,              // End Collection

#endif
#endif