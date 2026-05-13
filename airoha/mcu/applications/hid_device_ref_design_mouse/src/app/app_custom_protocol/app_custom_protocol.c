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
#include "custom_protocol.h"
#include "bt_ull_le_hid_service.h"
#include "air_usb.h"
#include "air_usb_hid.h"

#if defined(CONFIG_AIR_ACL_PACKET_VIA_HID_REPORT)
#include "hid_common.h"
#include "application.h"
#include "app_state.h"
#endif

/* Private define ------------------------------------------------------------*/
#define thisMODULE app_custom_protocol
#define thisMOD    "app_custom_protocol"
LOG_MODULE_REGISTER(thisMODULE);

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if defined (CONFIG_AIR_M21_SAMPLE)
static const uint8_t app_epio_custom_cmd0[] =
{
0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x87,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x83, 0x00,
};

static const uint8_t app_epio_custom_cmd1[] =
{
0x02, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x93,
0x01, 0x0d, 0x01, 0x00, 0x01, 0x0d, 0x01, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x9b, 0x00,
};
#endif /* CONFIG_AIR_M21_SAMPLE */

/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
void app_epio_custom_protocol_usb_in_process(const struct device *dev, uint16_t len, uint8_t *buf)
{
    /* Demo: let USB in data do directly usb out */
    LOG_INF("[app_epio_custom_protocol] usb in process dev = 0x%x, len = %u, data = 0x%08x 0x%08x ...", dev, len, *((uint32_t *)buf), *((uint32_t *)buf+1));
    // uint32_t i;
    // for (i = 0; i < (len+3)/4; i++)
    // {
    //     LOG_INF("[app_epio_custom_protocol] data = 0x%08x ...", *((uint32_t *)buf+i));
    // }
#if defined (CONFIG_AIR_M21_SAMPLE)
    /* Use set/get report case */
    epio_usb_hid_send_data(dev, len, buf);
#else
    /* Use in/out report case */
    buf[0] = AIR_USB_HID_EPIO_TX_REPORT_ID;
    epio_usb_hid_send_data(dev, len, buf);
#endif
}

void app_epio_custom_protocol_bt_in_process(bt_addr_t *remote_address, uint16_t len, uint8_t *buf)
{
    /* Demo: let BT in data do directly BT out */
    LOG_INF("[app_epio_custom_protocol] bt in process len = %u, data = 0x%08x 0x%08x ...", len, *((uint32_t *)buf), *((uint32_t *)buf+1));
    // uint32_t i;
    // for (i = 0; i < (len+3)/4; i++)
    // {
    //     LOG_INF("[app_epio_custom_protocol] data = 0x%08x ...", *((uint32_t *)buf+i));
    // }
#if defined (CONFIG_AIR_M21_SAMPLE)
    if ((len > 8) && (buf[5] == 0x4) && (buf[7] == 0x87))
    {
        if(len > sizeof(app_epio_custom_cmd0)){
            return;
        }
        epio_bt_hid_send_data(remote_address, len, (uint8_t *)app_epio_custom_cmd0);
    }
    else if ((len > 8) && (buf[5] == 0x4) && (buf[7] == 0x93))
    {
        if(len > sizeof(app_epio_custom_cmd1)){
            return;
        }
        epio_bt_hid_send_data(remote_address, len, (uint8_t *)app_epio_custom_cmd1);
    }
    else
    {
        epio_bt_hid_send_data(remote_address, len, buf);
    }
#else

    #if defined(CONFIG_AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE)
    uint16_t pkt_len = *(uint16_t*)&buf[1];
    if (pkt_len <= 2)
    {
        // Go to active state to avoid auto disconnect process
        if (app_state_check(TYPE_CONNECTED_WO_ACTIVE)){
            struct evt_active_status* event = create_evt_active_status();
            if (event){
                event->active = true;
                event->type = KEY_WAKEUP;
                AF_EVT_SUBMIT(event);
            }
        }

        uint32_t acl_pkt_payload =  *((uint32_t *)buf) | AIR_USB_HID_EPIO_TX_REPORT_ID;
        epio_bt_hid_send_data_mix_with_hid_packet(NULL, sizeof(acl_pkt_payload), (uint8_t*)&acl_pkt_payload);
    }
    else
    #endif
    {
        buf[0] = AIR_USB_HID_EPIO_TX_REPORT_ID;
        epio_bt_hid_send_data(remote_address, len, buf);
    }
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
