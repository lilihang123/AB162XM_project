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

#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include "app_state.h"
#include "app_pure_gaming_dongle_scenario.h"
#include "app_bt_conn_manager.h"
#include "app_events.h"
#include "custom_protocol.h"
#include "bt_ull_le_hid_service.h"

/* Private define ------------------------------------------------------------*/
#define thisMODULE app_custom_protocol
#define thisMOD    "app_custom_protocol"
LOG_MODULE_REGISTER(thisMODULE);

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
void app_epio_custom_protocol_usb_in_process(const struct device *dev, uint16_t len, uint8_t *buf)
{
    /* Demo: let USB in data do directly BT out */
    LOG_INF("[app_epio_custom_protocol] usb in process dev = 0x%x, len = %u, data = 0x%08x 0x%08x ...", dev, len, *((uint32_t *)buf), *((uint32_t *)buf+1));
    // uint32_t i;
    // for (i = 0; i < (len+3)/4; i++)
    // {
    //     LOG_INF("[app_epio_custom_protocol] data = 0x%08x ...", *((uint32_t *)buf+i));
    // }
    app_pg_scenario_handle_t *scenario_handle;
    bt_addr_le_t remote_address;

#if defined(AIR_PURE_GAMING_DONGLE_MS_ENABLE)
    scenario_handle = app_pure_gaming_dongle_scenario_get_handle_by_role(APP_BT_CONN_ROLE_MOUSE);
#endif /* AIR_PURE_GAMING_DONGLE_MS_ENABLE */
#if defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
    scenario_handle = app_pure_gaming_dongle_scenario_get_handle_by_role(APP_BT_CONN_ROLE_GAMEPAD);
#endif /* AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE */
#if defined(CONFIG_AIR_PURE_GAMING_DONGLE_KB_ENABLE)
    scenario_handle = app_pure_gaming_dongle_scenario_get_handle_by_role(APP_BT_CONN_ROLE_KEYBOARD);
#endif /* AIR_PURE_GAMING_DONGLE_MS_ENABLE */

    app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_GET_ULL_LINK_ADDR, &remote_address);
#if defined (CONFIG_AIR_M21_SAMPLE)
    if ((buf[5] == 0x4) && (buf[7] == 0x87))
    {
        epio_bt_hid_send_data(&(remote_address.a), len, buf);
    }
    else if ((buf[5] == 0x4) && (buf[7] == 0x93))
    {
        epio_bt_hid_send_data(&(remote_address.a), len, buf);
    }
#else
    epio_bt_hid_send_data(&(remote_address.a), len, buf);
#endif
}

void app_epio_custom_protocol_bt_in_process(bt_addr_t *remote_address, uint16_t len, uint8_t *buf)
{
    /* Demo: let BT in data do directly USB out */
    LOG_INF("[app_epio_custom_protocol] bt in process len = %u, data = 0x%08x 0x%08x ...", len, *((uint32_t *)buf), *((uint32_t *)buf+1));
    // uint32_t i;
    // for (i = 0; i < (len+3)/4; i++)
    // {
    //     LOG_INF("[app_epio_custom_protocol] data = 0x%08x ...", *((uint32_t *)buf+i));
    // }
#if defined (CONFIG_AIR_M21_SAMPLE)
    epio_usb_hid_send_data(epio_custom_protocol_get_control_transfer_usb_device(), len, buf);
#else
    epio_usb_hid_send_data(epio_custom_protocol_get_interrupt_transfer_usb_device(), len, buf);
#endif
}

void app_epio_custom_protocol_init(void)
{
    epio_process_callback_t cb;

    cb.usb_recv_data_callback    = app_epio_custom_protocol_usb_in_process;
    cb.bt_recv_data_callback     = app_epio_custom_protocol_bt_in_process;

    epio_custom_protocol_init();
    epio_custom_protocol_register_callback(&cb);
}

void app_epio_custom_protocol_deinit(void)
{
    epio_custom_protocol_deinit();
}
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE */
