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
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include "assert.h"
#include "race_cmd.h"
#include "app_race_cmd_event.h"
#include "app_race_cmd_pure_gaming_dongle.h"
#include "app_race_cmd_common.h"
#include "af_framework.h"
#include "app_race_cmd.h"

/* Private define ------------------------------------------------------------*/
#define thisMODULE app_race_cmd
#define thisMOD    "app_race_cmd"
LOG_MODULE_REGISTER(thisMODULE);

#define RACE_ID_APPLICATION_BEGIN 0x2C10
#define RACE_ID_APPLICATION_END 0x2CCF

#define RACE_ID_BTD_BEGIN 0x3000
#define RACE_ID_BTD_END   0x3100

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void *app_race_cmd_handler(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t cid)
{
    void *pEvt = NULL;

    LOG_INF("app_race_cmd_handler, type[0x%X], id[0x%X]", pCmdMsg->hdr.type, pCmdMsg->hdr.id);

    if (pCmdMsg->hdr.type == RACE_TYPE_COMMAND ||
        pCmdMsg->hdr.type == RACE_TYPE_RESPONSE ||
        pCmdMsg->hdr.type == RACE_TYPE_COMMAND_WITHOUT_RSP ||
        pCmdMsg->hdr.type == RACE_TYPE_NOTIFICATION)
    {
        switch (pCmdMsg->hdr.id)
        {
            case RACE_DONGLE_LE_SCAN:
            case RACE_DONGLE_LE_ADV_REPORT_NOTIFY:
            case RACE_DONGLE_LE_CONNECT:
            case RACE_DONGLE_LE_GET_DEVICE_STATUS:
            case RACE_DONGLE_LE_GET_DEVICE_LIST:
            case RACE_DONGLE_LE_SWITCH_ACTIVE_DEVICE:
            case RACE_DONGLE_LE_GET_PAIRED_LIST:
            case RACE_DONGLE_LE_REMOVE_PAIRED_RECORD:
            case RACE_DONGLE_LE_GET_DEVICE_NAME:
            case RACE_DONGLE_LE_GET_LINK_TYPE:
            case RACE_DONGLE_LE_SET_LINK_TYPE:
            case RACE_SET_REPORT_RATE:
            case RACE_GET_REPORT_RATE:
            case RACE_HID_RECONNECT:
            case RACE_SET_UNIAA:
            case RACE_GET_UNIAA:
            case RACE_GET_CUR_DPI:
            case RACE_GET_BATTERY:
            {
                return app_race_pg_dongle_le_race_cmd_handler(pCmdMsg, length, cid);
            }
            #if defined(CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER)
            case RACE_SET_AUTO_SWITCH_PARAM:
            case RACE_CONTROL_AUTO_SWITCH:
            case RACE_SET_VPA_TX_GC:
            case RACE_SET_POWER_CONTROL_MODE:
            case RACE_GET_POWER_CONTROL_MODE:
            case RACE_SET_POWER_INFO:
            #endif
            #if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE)
            case RACE_SET_USB_MODE:
            case RACE_GET_USB_MODE:
            #endif /* defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE) */
            case RACE_SET_APP_COMMON_CONFIG:
            case RACE_GET_APP_COMMON_CONFIG:
            {
                return app_race_common_race_cmd_handler(pCmdMsg, length, cid);
            }

            default:
                break;
        }
    }

    return pEvt;
}

static bool app_race_cmd_hdl(const struct af_evt_header *evt_header)
{
    struct af_evt_app_race_cmd *app_race_cmd = (struct af_evt_app_race_cmd *)evt_header;

    app_race_cmd_handler((ptr_race_pkt_t)(app_race_cmd->pCmdMsg),
                        app_race_cmd->length,
                        app_race_cmd->cid);
    k_free((void *)(app_race_cmd->pCmdMsg));

    return AF_TRAVERSE_NEXT;
}

static void *app_race_dispatch_handler(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t cid)
{
    void *pEvt = NULL;

    LOG_INF("app_race_dispatch_handler, type[0x%X], id[0x%X]", pCmdMsg->hdr.type, pCmdMsg->hdr.id);

    struct af_evt_app_race_cmd *app_race_cmd = create_af_evt_app_race_cmd();
    if (app_race_cmd){
        app_race_cmd->pCmdMsg = NULL;
        app_race_cmd->pCmdMsg = k_malloc(length+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint16_t));
        assert(app_race_cmd->pCmdMsg != NULL);
        memcpy(app_race_cmd->pCmdMsg, pCmdMsg, length+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint16_t));
        app_race_cmd->length = length;
        app_race_cmd->cid = cid;
        AF_EVT_SUBMIT(app_race_cmd);
    }
    else
    {
        assert(0);
    }

    return pEvt;
}

/* Public functions ----------------------------------------------------------*/
void app_race_cmd_event_init(void)
{
#if defined(AIR_RACE_CMD_ENABLE)
    RACE_HANDLER handler;
    race_status_t ret;

    handler.id_start = RACE_ID_APPLICATION_BEGIN;
    handler.id_end = RACE_ID_APPLICATION_END;
    handler.handler = app_race_dispatch_handler;
    ret = RACE_Register_Handler(&handler);
    if (RACE_STATUS_OK != ret) {
        LOG_INF(" app race register fail: ret=%d", ret);
        assert(0);
    }

    handler.id_start = RACE_ID_BTD_BEGIN;
    handler.id_end = RACE_ID_BTD_END;
    handler.handler = app_race_dispatch_handler;
    ret = RACE_Register_Handler(&handler);
    if (RACE_STATUS_OK != ret) {
        LOG_INF(" app race register fail: ret=%d", ret);
        assert(0);
    }

    LOG_INF(" app race cmd event init done");
#endif
}

AF_EVT_DECLARE(af_evt_app_race_cmd);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, af_evt_app_race_cmd, app_race_cmd_hdl);

#endif /* AIR_PURE_GAMING_DONGLE_ENABLE */
