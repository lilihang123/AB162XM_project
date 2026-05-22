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

// #if defined()

/* Includes ------------------------------------------------------------------*/
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include "app_state.h"
#include "app_debug.h"
#include <app_evt_dispatcher.h>
#include "af_events_declaration.h"

/* Private define ------------------------------------------------------------*/
#define thisMODULE state_mgr
#define thisMOD    "state_mgr"
LOG_MODULE_REGISTER(thisMODULE);

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
APP_STATES app_state;
APP_STATES app_state_last;

/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
void app_state_init(void)
{
    app_state_change(APP_STATE_INIT , REASON_NONE);

    LOG_INF("app_state_init end");
}

void app_state_change(APP_STATES new_state, APP_STATE_CHANGE_REASON reason)
{
    // app_state_announce_new_state(new_state);

    LOG_INF("=====================================================================");
    LOG_INF(" App State changed from %02X to %02X, reason = %X"
        , app_state
        , new_state
        , reason
        );
    LOG_INF("=====================================================================");

    app_state_last = app_state;
    app_state = new_state;

#if defined(CONFIG_AIR_MIDDLE_RGB) || defined(CONFIG_AIR_MIDDLE_LED)
    struct state_cmd* cmd = create_state_cmd();
    if (cmd){
        cmd->state = new_state;
        cmd->last_state = app_state_last;
        cmd->reason = reason;
        AF_EVT_SUBMIT(cmd);
    }
#endif /* CONFIG_AIR_MIDDLE_RGB || CONFIG_AIR_MIDDLE_LED */
}

APP_STATES app_state_get_current(void)
{
    return app_state;
}

APP_STATES app_state_get_last(void)
{
    return app_state_last;
}

// #endif /*  */
