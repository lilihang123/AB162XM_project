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

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "app_debug.h"
#include "app_state.h"
#if defined(AIR_PURE_GAMING_DONGLE_ENABLE)
#include "app_pure_gaming_dongle_scenario.h"
#include "app_bt_conn_manager.h"
#endif
#include "app_events.h"
#include "af_events_declaration.h"
#include "app_race_cmd.h"

#ifdef AIR_HOGP_DONGLE_ENABLE
#include "app_dongle_cm.h"
#include "app_dongle_event.h"
#include "app_hogp_client.h"
#include "app_usb_mgr.h"
#include "app_debug.h"
#endif

#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)
#include "app_custom_protocol.h"
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE */

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
void app_dongle_init(void)
{
#ifdef AIR_HOGP_DONGLE_ENABLE
    app_usb_mgr_init();
    app_dongle_cm_init();

    app_hogp_client_init();
#endif
}

void app_init(void)
{
#ifdef AIR_PURE_GAMING_DONGLE_ENABLE
    /* app state init */
    app_state_init();

    /* app events init */
    app_events_init();
    /* only allow start up now */
    app_events_suspend_all_events();
    app_events_allow_special_event(EVT_CMD_STARTUP);

    /* app race cmd init */
    app_race_cmd_event_init();

    /* BT service init */
    app_bt_conn_init();

    /* scenario init */
    app_pure_gaming_dongle_scenario_init();

#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)
    /* custom protocol init */
    app_epio_custom_protocol_init();
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE */
#endif

#ifdef AIR_HOGP_DONGLE_ENABLE
    app_dongle_event_init();
#endif

#if defined(CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER)
    // app_pure_gaming_dongle_scenario_register_auto_switch_callback();
#endif/*CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER*/

}
