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

#ifndef __APP_DONGLE_EVENTS_H__
#define __APP_DONGLE_EVENTS_H__

#include "app_type.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
    APP_DONGLE_EVENT_SYSTEM_INIT                                = 0,
} app_dongle_event_system_t;

typedef enum {
    APP_DONGLE_EVENT_USB_NONE                                   = 0,
    APP_DONGLE_EVENT_USB_CONNECTED,
    APP_DONGLE_EVENT_USB_DISCONNECTED,
    APP_DONGLE_EVENT_USB_READY,
    APP_DONGLE_EVENT_USB_SUSPEND,
    APP_DONGLE_EVENT_USB_RESUME,

    APP_DONGLE_EVENT_USB_TEST_EVENT,
} app_dongle_event_usb_t;

typedef enum {
    APP_DONGLE_EVENT_BT_NONE                                    = 0,
    APP_DONGLE_EVENT_BT_ON,
    APP_DONGLE_EVENT_BT_OFF,
    APP_DONGLE_EVENT_BT_LE_CONNECTED_IND,
    APP_DONGLE_EVENT_BT_LE_DISCONNECTED_IND,
    APP_DONGLE_EVENT_BT_LE_BOND_COMPLETE_IND,                   // 5
    APP_DONGLE_EVENT_BT_LE_SCAN_STARTED_IND,
    APP_DONGLE_EVENT_BT_LE_SCAN_STOPPED_IND,
    APP_DONGLE_EVENT_BT_LE_SCAN_TIMEOUT,
} app_dongle_event_bt_t;

typedef enum {
    APP_DONGLE_EVENT_HOGP_APP_NONE                              = 0,
    APP_DONGLE_EVENT_HOGP_APP_POWER_ON_RECONNECT_TIMEOUT,
} app_dongle_event_hogp_app_t;


#ifdef __cplusplus
}
#endif

#endif /* __APP_DONGLE_EVENTS_H__ */
