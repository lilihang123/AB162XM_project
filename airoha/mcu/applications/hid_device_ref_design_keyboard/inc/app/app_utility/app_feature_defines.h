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

#ifndef __APP_FEATURE_DEFINE_H__
#define __APP_FEATURE_DEFINE_H__



#define AIROHA_HOGS

#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_GAMING_MODE)
#define AIROHA_DEFAULT_LINK_IS_PROPRIERTARY_2_4G
#endif

#define AIROHA_HID_MOUSE_FAKE_REPORT


#define AIROHA_BASIC_LA_DEBUG


#define LINK_MASK  0x01   // 0:BT; 1:Gaming. totally 8 bits for 8 links

#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
#define LINK_NUM   0x02   // link 0:gaming, 1:bt
#else
#define LINK_NUM   0x01   // link 0:gaming, 1:bt
#endif

#define POWER_SAVING_ACTIVE_TIMEOUT     10   // unit second
#define POWER_SAVING_IDLE_1_TIMEOUT     10000   // unit ms
#define POWER_SAVING_IDLE_2_TIMEOUT     10000   // unit ms
#define POWER_SAVING_PAIRING_TIMEOUT    30000   // unit ms
#define POWER_SAVING_RECONNECT_TIMEOUT  10000   // unit ms

#define BT_MODE_HID_REPORT_START_TIMEOUT 500

#define APP_NVKEY_ID 0x6000

#define USB_CHECKING_PLUGGED_TIMEOUT    250   //ms
#define USB_CHECKING_CONFIGURED_TIMEOUT 2000  //ms

#define BATTERY_MANAGERMENT_INTERVAL    30000 //ms
#define BATTERY_LOW_BATTERY_PERSENTAGE  5     //%

#define DEFAULT_DEBOUNCE_TIME 10


//#define FAKE_REPORT_TRIGGER_BY_MIDDLE_KEY


#endif

