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
#include <math.h>
#include <assert.h>

#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#define LOG_LEVEL LOG_LEVEL_DEBUG
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main);

#include "air_chip.h"
#include "hal_platform.h"
#if defined(HAL_GPT_MODULE_ENABLED)
#include "hal_gpt.h"
#endif

#if defined(HAL_NVIC_MODULE_ENABLED)
#include "hal_nvic.h"
#endif

#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>

#include "memory_attribute.h"

#if CONFIG_BOOT_TIME_MEASUREMENT
#include "boot_time_measure.h"
#endif

#ifdef CONFIG_AIR_WDT
#include "wdt_airoha.h"
#endif

#include "app_init.h"
#include "app_debug.h"
#include "app_events.h"
#include "af_events_declaration.h"
#include "app_bt_conn_manager.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
int main()
{
    LOG_INF("[app_hid_dongle] main start!\n");

    app_init();

#if defined(AIR_PURE_GAMING_DONGLE_MS_ENABLE)
    app_events_send(EVT_CMD_STARTUP, (void *)APP_BT_CONN_ROLE_MOUSE);
#endif /* AIR_PURE_GAMING_DONGLE_MS_ENABLE */

#if defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
    app_events_send(EVT_CMD_STARTUP, (void *)APP_BT_CONN_ROLE_GAMEPAD);
#endif /* AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE */

#if defined(AIR_PURE_GAMING_DONGLE_KB_ENABLE)
    app_events_send(EVT_CMD_STARTUP, (void *)APP_BT_CONN_ROLE_KEYBOARD);
#endif /* AIR_PURE_GAMING_DONGLE_MS_ENABLE */

    /* all events are processed in application workqueue thread,
    so just return here */
    return 0;
}
