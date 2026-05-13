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


#ifndef __APP_STATE_H__
#define __APP_STATE_H__


#include "application.h"



#define IS_WIRELESS_CONNECTED_STATE(state)      (state & (APP_STATE_BT_CONNECTED | APP_STATE_2_4G_CONNECTED))
#define IS_USB_CONNECTED_STATE(state)           (state & APP_STATE_USB_CONNECTED)

/* Template
    switch(event->app_state)
    {
        case APP_STATE_NONE:
        case APP_STATE_INITIALIZED:
        case APP_STATE_STANDBY:
        case APP_STATE_DISCONNECTED:
        case APP_STATE_TEST:
        case APP_STATE_CONNECT_PREPARING:
            break;

        case APP_STATE_BT_PAIRING:
        case APP_STATE_2_4G_PAIRING:
        case APP_STATE_BT_RECONNECT:
        case APP_STATE_2_4G_RECONNECT:
        case APP_STATE_2_4G_QUICK_CONNECT:
        case APP_STATE_CONNECT_CANCEL:
        case APP_STATE_CONNECT_CANCEL_CHECK:
            break;

        case APP_STATE_USB_CONNECTED:
        case APP_STATE_USB_ACTIVE:
        case APP_STATE_USB_SUSPEND:
        case APP_STATE_USB_ENTERING_ACTIVE:
        case APP_STATE_USB_DISCONNECTING:
            break;

        case APP_STATE_BT_CONNECTED:
        case APP_STATE_BT_CONNECTED_ACTIVE:
        case APP_STATE_BT_CONNECTED_IDLE_1:
        case APP_STATE_BT_CONNECTED_IDLE_2:
        case APP_STATE_BT_CONNECTED_IDLE_3:
        case APP_STATE_BT_CONNECTED_ENTERING_ACTIVE:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_1:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_2:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_3:
        case APP_STATE_BT_DISCONNECTING:
            break;

        case APP_STATE_2_4G_CONNECTED:
        case APP_STATE_2_4G_CONNECTED_ACTIVE:
        case APP_STATE_2_4G_CONNECTED_IDLE_1:
        case APP_STATE_2_4G_CONNECTED_IDLE_2:
        case APP_STATE_2_4G_CONNECTED_IDLE_3:
        case APP_STATE_2_4G_CONNECTED_ENTERING_ACTIVE:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_2:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_3:
        case APP_STATE_2_4G_DISCONNECTING:
            break;
    }
*/



typedef enum
{
    TYPE_CONNECTED_WO_ACTIVE,
    TYPE_IN_BT_PAIRING_RECONNECT,
    TYPE_IN_BT_CONNECTED_STATES,
    TYPE_IN_BT_STATES,
    TYPE_IN_USB_STATES,
    TYPE_IN_GAMING_PAIRING_RECONNECT,
    TYPE_IN_GAMING_CONNECTED_STATES,
    TYPE_IN_GAMING_CONNECTED_STABLE,
    TYPE_IN_GAMING_STATES,
    TYEP_IN_GAMING_RESUME,
}APP_STATE_CHECK_TYPE;













void app_state_get_power_saving_timeout(uint32_t *idle1_timeout, uint32_t *idle2_timeout);
uint32_t app_state_current_state();
uint32_t app_state_check(uint32_t condiction);
void app_state_init();

void app_state_standby_req();

#endif

