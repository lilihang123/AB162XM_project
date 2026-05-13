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
 
#ifndef __HID_DESCRIPTOR_KEYBOARD_STD_H__
#define __HID_DESCRIPTOR_KEYBOARD_STD_H__


0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)   
0x09, 0x06,                    // USAGE (Keyboard)   
0xa1, 0x01,                    // COLLECTION (Application)   
0x85, REPORT_ID_KB_STD,        //  REPORT_ID (?)                   
0x05, 0x07,                    //   USAGE_PAGE (Keyboard)   

0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)   
0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)   
0x15, 0x00,                    //   LOGICAL_MINIMUM (0)   
0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)   
0x75, 0x01,                    //   REPORT_SIZE (1)   
0x95, 0x08,                    //   REPORT_COUNT (8)   
0x81, 0x02,                    //   INPUT (Data,Var,Abs)            //b[1]

0x95, 0x05,                    //   REPORT_COUNT (5)   
0x75, 0x01,                    //   REPORT_SIZE (1)   
0x05, 0x08,                    //   USAGE_PAGE (LEDs)               
0x19, 0x01,                    //   USAGE_MINIMUM (Num Lock)   
0x29, 0x05,                    //   USAGE_MAXIMUM (Kana)   
0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)           //out b[0] led 

0x95, 0x01,                    //   REPORT_COUNT (1)   
0x75, 0x03,                    //   REPORT_SIZE (3)   
0x91, 0x03,                    //   OUTPUT (Cnst,Var,Abs)           //out b[0] dummy bits 

0x95, 0x06,                    //   REPORT_COUNT (6)                
0x75, 0x08,                    //   REPORT_SIZE (8)   
0x15, 0x00,                    //   LOGICAL_MINIMUM (0)   
0x25, 0xFF,                    //   LOGICAL_MAXIMUM (255)   
0x05, 0x07,                    //   USAGE_PAGE (Keyboard)   
0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))   
0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)   
0x81, 0x00,                    //   INPUT (Data,Ary,Abs)            //b[3~8] key code
0xc0,                           // END_COLLECTION   




#endif
