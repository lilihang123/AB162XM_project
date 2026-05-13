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
 

#ifndef __HID_DESCRIPTOR_KEYBOARD_CONSUMER_H__
#define __HID_DESCRIPTOR_KEYBOARD_CONSUMER_H__


0x05, 0x0c,        /* USAGE_PAGE (Consumer Devices) */
0x09, 0x01,        /* USAGE (Consumer Control) */
0xa1, 0x01,        /* COLLECTION (Application) */
0x85, REPORT_ID_KB_CONSUMER,        /*  REPORT_ID (?) */                  //b[0]

0x19, 0x00,        /*  USAGE_MINIMUM (0) */
0x2A, 0xFF, 0x0F,  /*  USAGE_MAXIMUM (FFF) */

0x15, 0x00,        /*  LOGICAL_MINIMUM (0) */
0x26, 0xFF, 0x0F,  /*  LOGICAL_MAXIMUM (FFF) */

0x95, 0x02,        /*  REPORT_COUNT (2) */
0x75, 0x10,        /*  REPORT_SIZE (16) */          //b[1~2]     b[3~4]
0x81, 0x00,        /*  INPUT (Data,Ary,Abs) */

/*  numeric key pad */
0x09, 0x02,        /* USAGE (Numeric Key Pad) */
0xA1, 0x02,        /* COLLECTION (Logical)    */
0x05, 0x09,        /* USAGE_PAGE (Button) */

0x19, 0x01,        /*  USAGE Minimum */
0x29, 0x0A,        /*  USAGE Maximum */
0x15, 0x01,        /*  Logical Minimum */
0x25, 0x0A,        /*  Logical Maximum */
0x95, 0x01,        /*   REPORT_COUNT (1) */
0x75, 0x08,        /*   REPORT_SIZE ( 8) */                   // b[5]  number 1,2, ... 9, 0
0x81, 0x40,        /*   INPUT (Data,Ary,Abs,null state) */
0xC0,              /* END_COLLECTION (Logical) */   
/*  numeric key pad */
0xC0,              /* END_COLLECTION (Application) */

#endif
