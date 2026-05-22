
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

#include "app_bt_service_common.h"

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/logging/log.h>
#include <zephyr/settings/settings.h>

#include "app_bt_service_le_connection.h"
#include "app_bt_service_le_scanner.h"
#include "app_debug.h"
#include "app_dongle_event.h"


/**================================================================================*/
/**                              Definition & Structure                            */
/**================================================================================*/
#define LOG_TAG             "[APP_DONGLE][BT_SRV][COMMON]"




/**================================================================================*/
/**                                   Internal API                                 */
/**================================================================================*/
static void app_bt_service_common_bt_ready_callback(int err)
{
    APPS_LOG_MSGID_I(LOG_TAG" bt_ready_callback, error=%d", 1, err);
    if (err == 0) {
        app_dongle_event_send_event(APP_DONGLE_EVENT_GROUP_BT, APP_DONGLE_EVENT_BT_ON);
    }
}



/**================================================================================*/
/**                                     Public API                                 */
/**================================================================================*/
void app_bt_service_common_init(void)
{
    if (bt_is_ready()) {
        APPS_LOG_MSGID_I(LOG_TAG" init, BT already ON", 0);
    } else {
        int err = bt_enable(app_bt_service_common_bt_ready_callback);
        if (err != 0) {
            APPS_LOG_MSGID_E(LOG_TAG" init, bt_enable error %d", 1, err);
            return;
        }

        err = settings_load();
        APPS_LOG_MSGID_I(LOG_TAG" init, settings_load err=%d", 1, err);
    }
    app_bt_service_le_connection_init();
    app_bt_service_le_scanner_init();
}

bool app_bt_service_power_off_bt(void)
{
    int err = bt_disable();
    if (err == 0) {
        app_dongle_event_send_event(APP_DONGLE_EVENT_GROUP_BT, APP_DONGLE_EVENT_BT_OFF);
    } else {
        APPS_LOG_MSGID_E(LOG_TAG" power_off_bt, error %d", 1, err);
    }
    return (err == 0);
}