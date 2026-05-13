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

#if defined(AIR_PURE_GAMING_DONGLE_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/drivers/sensor.h>
#include "air_usb.h"
#include "air_usb_hid.h"
#include "hal_gpt.h"
#include "hal_gpt_internal.h"
#include "hal_ccni.h"
#include "hal_ccni_config.h"
#include "hal_usb.h"
#include "hal_usb_internal.h"
#include "hal_gpio.h"
#include "app_pure_gaming_dongle_scenario.h"
#include "app_events.h"
#include "af_events_declaration.h"
#include "assert.h"

/* Private define ------------------------------------------------------------*/
#define thisMODULE  app_usb
#define thisMOD    "app_usb"
LOG_MODULE_REGISTER(thisMODULE);

#define APP_USB_EVT_WINDOW_TIMER_DELAY_MS 20

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
air_usb_evt_t app_usb_evt_status        = AIR_USB_EVT_PLUG_OUT;
air_usb_evt_t app_usb_evt_last_status   = AIR_USB_EVT_PLUG_OUT;
bool app_usb_sof_status = false;
uint32_t app_usb_window_timer;

/* Private functions ---------------------------------------------------------*/
static void app_usb_window_timer_cb(void *user_data)
{
    air_usb_evt_t evt;
    app_pg_scenario_handle_t *scenario_handle = app_pure_gaming_dongle_scenario_get_current_context();

    evt = app_usb_evt_status;
    if (evt == app_usb_evt_last_status)
    {
        LOG_INF("app usb window timer callback dritectly return, usb status = %d.", evt);
        return;
    }
    app_usb_evt_last_status = evt;
    switch(evt)
    {
        case AIR_USB_EVT_CONNECTED:
        {
            app_events_send(EVT_CMD_USB_PLUGIN, scenario_handle);
            break;
        }
        case AIR_USB_EVT_CONFIGURED:
        {
            app_events_send(EVT_CMD_USB_READY, scenario_handle);
#if defined(CONFIG_AIR_HID_DISABLE_SOF_INTR)
            app_pure_gaming_dongle_scenario_disable_sof_intr();
#endif
            break;
        }
        case AIR_USB_EVT_DISCONNECTED:
        {
            app_events_send(EVT_CMD_USB_PLUGOUT, scenario_handle);
            break;
        }
        case AIR_USB_EVT_SUSPEND:
        {
            app_events_send(EVT_CMD_USB_SUSPEND, scenario_handle);
            break;
        }
        case AIR_USB_EVT_RESUME:
        {
            app_events_send(EVT_CMD_USB_RESUME, scenario_handle);
            break;
        }
        default:
        {
            break;
        }
    }
    LOG_INF("app usb window timer callback normal return, usb status = %d.", evt);
}

static void app_usb_window_timer_start(void)
{
    if (app_usb_window_timer == 0)
    {
        hal_gpt_sw_get_timer(&app_usb_window_timer);
    }
    hal_gpt_sw_stop_timer_ms(app_usb_window_timer);
    if(HAL_GPT_STATUS_OK != hal_gpt_sw_start_timer_ms(app_usb_window_timer, APP_USB_EVT_WINDOW_TIMER_DELAY_MS, app_usb_window_timer_cb, NULL))
    {
        assert(0);
    }
    LOG_INF("app usb window timer start, usb status = %d.", app_usb_evt_status);
}

/* Public functions ----------------------------------------------------------*/
void app_usb_evt_cb(air_usb_evt_t evt, const uint8_t *param)
{
    switch(evt)
    {
        case AIR_USB_EVT_RESET:
        {
            LOG_INF("AIR_USB_EVT_RESET");
            break;
        }
        case AIR_USB_EVT_CONNECTED:
        {
            LOG_INF("AIR_USB_EVT_CONNECTED");
            /* start window timer for trigger update usb status */
            app_usb_evt_status = evt;
            app_usb_window_timer_start();
            break;
        }
        case AIR_USB_EVT_CONFIGURED:
        {
            LOG_INF("AIR_USB_EVT_CONFIGURED");
            /* start window timer for trigger update usb status */
            app_usb_evt_status = evt;
            app_usb_window_timer_start();
            break;
        }
        case AIR_USB_EVT_DISCONNECTED:
        {
            LOG_INF("AIR_USB_EVT_DISCONNECTED");
            /* start window timer for trigger update usb status */
            app_usb_evt_status = evt;
            app_usb_window_timer_start();
            break;
        }
        case AIR_USB_EVT_SUSPEND:
        {
            LOG_INF("AIR_USB_EVT_SUSPEND");
            /* start window timer for trigger update usb status */
            app_usb_evt_status = evt;
            app_usb_window_timer_start();
            break;
        }
        case AIR_USB_EVT_RESUME:
        {
            LOG_INF("AIR_USB_EVT_RESUME");
            /* start window timer for trigger update usb status */
            /* Note: some case only has usb resume evnet, not have usb configured event, so we treat thess events as the same */
            app_usb_evt_status = AIR_USB_EVT_CONFIGURED;
            app_usb_window_timer_start();
            break;
        }
        case AIR_USB_EVT_SOF:
        {
            break;
        }
        default:
        {
            LOG_INF("AIR_USB_EVT unknow evt: %u");
            break;
        }
    }
}

#endif /* AIR_PURE_GAMING_DONGLE_ENABLE */
