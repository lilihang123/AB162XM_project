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

#ifndef _HID_COMMON_HID_APP_STATES_H_
#define _HID_COMMON_HID_APP_STATES_H_


/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"

/* Public define -------------------------------------------------------------*/

/* Public typedef ------------------------------------------------------------*/

typedef enum
{
    APP_STATE_NONE,
    APP_STATE_INITIALIZED,
    APP_STATE_STANDBY,
    APP_STATE_DISCONNECTED,
    APP_STATE_TEST,

    APP_STATE_CONNECT_PREPARING = 0x0A,

    APP_STATE_BT_PAIRING = 0x10,
    APP_STATE_2_4G_PAIRING,
    APP_STATE_BT_RECONNECT,
    APP_STATE_2_4G_RECONNECT,
    APP_STATE_2_4G_QUICK_CONNECT,
    APP_STATE_2_4G_RECONNECT_RESUME_WAIT,

    APP_STATE_CONNECT_CANCEL = 0x1E,
    APP_STATE_CONNECT_CANCEL_CHECK,

    APP_STATE_USB_CONNECTED = 0x20,
    APP_STATE_USB_ACTIVE,
    APP_STATE_USB_SUSPEND,
    APP_STATE_USB_STOP,
    APP_STATE_USB_ENTERING_ACTIVE = 0x2A,
    APP_STATE_USB_DISCONNECTING = 0x2E,

    APP_STATE_BT_CONNECTED = 0x40,
    APP_STATE_BT_CONNECTED_ACTIVE,
    APP_STATE_BT_CONNECTED_IDLE_1,
    APP_STATE_BT_CONNECTED_IDLE_2,
    APP_STATE_BT_CONNECTED_IDLE_3,
    APP_STATE_BT_CONNECTED_ENTERING_ACTIVE = 0x4A,
    APP_STATE_BT_CONNECTED_ENTERING_IDLE_1,
    APP_STATE_BT_CONNECTED_ENTERING_IDLE_2,
    APP_STATE_BT_CONNECTED_ENTERING_IDLE_3,
    APP_STATE_BT_DISCONNECTING,

    APP_STATE_2_4G_CONNECTED = 0x80,
    APP_STATE_2_4G_CONNECTED_ACTIVE,
    APP_STATE_2_4G_CONNECTED_IDLE_1,
    APP_STATE_2_4G_CONNECTED_IDLE_2,
    APP_STATE_2_4G_CONNECTED_IDLE_3,
    APP_STATE_2_4G_CONNECTED_ENTERING_ACTIVE = 0x8A,
    APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1,
    APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_2,
    APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_3,
    APP_STATE_2_4G_DISCONNECTING,
} APP_STATES;

typedef enum
{
    /**
    0x00 ~ 0x47 are reserved for HCI error code
     */

    REASON_NONE  = 0x50,
    REASON_INIT_BT_COMPLETE,
    REASON_INIT_COMPLETE,
    REASON_LINK_NEXT,
    REASON_LOW_BATTERY,
    REASON_WAIT_FOR_TRIGGER,
    REASON_SLIDE_SWITCH_IN_OFF,

    REASON_BT_RECONNECT = 0x60,
    REASON_PAIR,
    REASON_2_4G_RECONNECT,
    REASON_2_4G_QUICK_CONNECT,
    REASON_ACTIVE,
    REASON_CONNECT_START,
    REASON_2_4G_RECONNECT_RESUME_WAIT,
    REASON_2_4G_RECONNECT_RESUME_ACTIVE,

    REASON_USB_IN = 0x70,
    REASON_USB_CHANNEL_READY,
    REASON_USB_SUSPEND,
    REASON_USB_OUT,
    REASON_USB_OFF,
    REASON_USB_EXIT,

    REASON_CONNECTED = 0x80,
    REASON_IDLE,
    REASON_IDLE_2,
    REASON_IDLE_3,

    REASON_DISCONNECT = 0xE0,
    REASON_LINK_LOSE,
    REASON_TIMEOUT,
    REASON_PAIRING_TIMEOUT,
    REASON_RECONNECT_TIMEOUT,
    REASON_ADV_TIMEOUT,
    REASON_CIS_TIMEOUT,
    REASON_STANDBY_TIMEOUT,
    REASON_RECONNECT_FAIL,

    REASON_ENTER_LABTEST = 0xF0,

} APP_STATE_CHANGE_REASON;

/* Public macro --------------------------------------------------------------*/
#define APP_STATE_CONNECTED             (APP_STATE_USB_CONNECTED | APP_STATE_BT_CONNECTED | APP_STATE_2_4G_CONNECTED)
#define APP_STATE_ACTIVE_BIT            0x01  // active state are 0x21, 0x41, and 0x81
#define APP_STATE_SUB_STATE_BIT_MASK    0x0F  // lower 4 bits
#define IS_APP_STATE_IN_ACTIVE(s)       ((s & APP_STATE_SUB_STATE_BIT_MASK ) == APP_STATE_ACTIVE_BIT)


/* Public variables ----------------------------------------------------------*/
/* Inline functions ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/


#endif /* _HID_COMMON_HID_APP_STATES_H_ */
