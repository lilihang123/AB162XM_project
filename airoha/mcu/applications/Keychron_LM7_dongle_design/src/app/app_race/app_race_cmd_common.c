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
#include <stdint.h>
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
#include "race_xport.h"
#include "app_race_cmd_event.h"
#include "app_race_cmd_pure_gaming_dongle.h"
#include "app_events.h"
#include "af_events_declaration.h"
#include "app_pure_gaming_dongle_scenario.h"
#include "app_bt_conn_manager.h"
#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE)
#include "nvkey.h"
#include "hal_wdt.h"
#include "hal_gpt.h"
#include "hal_nvic.h"
#endif /* defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE) */

#if defined(CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER)
#include "auto_switch_service.h"
#endif

/* Private define ------------------------------------------------------------*/
#define thisMODULE app_race_cmd
#define thisMOD    "app_race_cmd"
LOG_MODULE_DECLARE(thisMODULE);

/* Private typedef -----------------------------------------------------------*/
typedef struct {
    uint8_t status;
    uint16_t config_type;
    uint8_t mode;
} PACKED get_usb_mode_response_t;

#define APP_DONGLE_CM_SOURCE_ULL_V1    0x00    /**< ULL v1 source types . */
#define APP_DONGLE_CM_SOURCE_ULL_V2    0x01    /**< ULL v2 source types . */
#define APP_DONGLE_CM_SOURCE_LEA       0x02    /**< LEA source types . */
#define APP_DONGLE_CM_SOURCE_BTA       0x03    /**< BTA source types . */
#define APP_DONGLE_CM_SOURCE_HID       0x04    /**< BTA source types . */
#define APP_DONGLE_CM_SOURCE_MAX       0x05    /**< Max source types . */
#define APP_DONGLE_CM_SOURCE_INVALID   APP_DONGLE_CM_SOURCE_MAX + 1    /**< Invalid source types . */
typedef uint8_t app_dongle_cm_source_t;  /**< Dongle source types . */

#define APP_DONGLE_CM_LINK_MODE_ULL_V1          (1 << APP_DONGLE_CM_SOURCE_ULL_V1)
#define APP_DONGLE_CM_LINK_MODE_ULL_V2          (1 << APP_DONGLE_CM_SOURCE_ULL_V2)
#define APP_DONGLE_CM_LINK_MODE_LEA             (1 << APP_DONGLE_CM_SOURCE_LEA)
#define APP_DONGLE_CM_LINK_MODE_BTA             (1 << APP_DONGLE_CM_SOURCE_BTA)
typedef uint8_t app_dongle_cm_link_mode_t;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void *app_race_common_get_config(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint16_t config_type;
        uint8_t config_data[0];
    } PACKED CMD;

    int32_t race_ret = RACE_ERRCODE_FAIL;
    void *pRsp = NULL;

    CMD *pCmd = (CMD *)pCmdMsg;

    LOG_INF("race get app common config: handler_id=0x%04X, config_type=0x%04X",
                        2, pCmd->cmdhdr.id, pCmd->config_type);

    switch (pCmd->config_type) {
        case APPS_RACE_CMD_CONFIG_TYPE_USB_MODE:
            /* send response */
            pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                        pCmd->cmdhdr.id,
                                        sizeof(get_usb_mode_response_t),
                                        cid);
            if (pRsp == NULL) {
                LOG_ERR("app_race_pg_dongle_scan RACE_ClaimPacketAppID fail");
                return NULL;
            }
            ((get_usb_mode_response_t *)pRsp)->status = RACE_ERRCODE_SUCCESS;
            ((get_usb_mode_response_t *)pRsp)->config_type = APPS_RACE_CMD_CONFIG_TYPE_USB_MODE;
            ((get_usb_mode_response_t *)pRsp)->mode = APP_DONGLE_CM_LINK_MODE_ULL_V2;
            race_ret = race_flush_packet((uint8_t *)pRsp, cid);
            if (race_ret != RACE_ERRCODE_SUCCESS) {
                RACE_FreePacket((void *)pRsp);
            }
            break;

        default:
            break;
    }

    return NULL;
}

#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE)
static void *app_race_common_set_usb_mode(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t mode;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    int32_t race_ret = RACE_ERRCODE_FAIL;
    RSP *pRsp = NULL;

    CMD *pCmd = (CMD *)pCmdMsg;

    LOG_INF("race set usb mode: handler_id=0x%04X, mode = %u", pCmd->cmdhdr.id, pCmd->mode);

    uint8_t usb_mode = pCmd->mode;
    nvkey_status_t nvkey_ret = nvkey_write_data(NVID_APP_USB_MODE, (uint8_t *)&usb_mode, sizeof(uint8_t));
    if (nvkey_ret == NVKEY_STATUS_OK)
    {
        uint32_t mask;
        hal_nvic_save_and_set_interrupt_mask(&mask);
        hal_gpt_delay_ms(10);
        hal_wdt_software_reset();
        hal_nvic_restore_interrupt_mask(mask);
    }

    /* send response */
    pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                pCmd->cmdhdr.id,
                                sizeof(RSP),
                                cid);
    if (pRsp == NULL) {
        LOG_ERR("race set usb mode RACE_ClaimPacketAppID fail");
        return NULL;
    }
    if (nvkey_ret == NVKEY_STATUS_OK)
    {
        pRsp->status = 0;
    }
    else
    {
        pRsp->status = 1;
    }

    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    return NULL;
}

static void *app_race_common_get_usb_mode(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
        uint8_t mode;
    } PACKED RSP;

    int32_t race_ret = RACE_ERRCODE_FAIL;
    RSP *pRsp = NULL;

    CMD *pCmd = (CMD *)pCmdMsg;

    uint8_t usb_mode;
    uint32_t nvkey_size = sizeof(uint8_t);
    nvkey_status_t nvkey_ret = nvkey_read_data(NVID_APP_USB_MODE, (uint8_t *)&usb_mode, &nvkey_size);
    if ((nvkey_size != sizeof(uint8_t)) || (nvkey_ret != NVKEY_STATUS_OK))
    {
        LOG_ERR("race get usb mode fail, size = %d, ret = %d.", nvkey_size, nvkey_ret);
    }
    else
    {
        LOG_INF("race get usb mode: handler_id=0x%04X, config_type=0x%04X",
                            2, pCmd->cmdhdr.id, usb_mode);
    }

    /* send response */
    pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                pCmd->cmdhdr.id,
                                sizeof(RSP),
                                cid);
    if (pRsp == NULL) {
        LOG_ERR("race get usb mode RACE_ClaimPacketAppID fail");
        return NULL;
    }
    if (nvkey_ret == NVKEY_STATUS_OK)
    {
        pRsp->status = 0;
        pRsp->mode = usb_mode;
    }
    else
    {
        pRsp->status = 1;
        pRsp->mode = 0xff;
    }

    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    return NULL;
}
#endif /* defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE) */

#if defined(CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER)
static void *app_race_common_set_auto_switch_param(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        auto_switch_control_param_t param;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    int32_t race_ret = RACE_ERRCODE_FAIL;
    RSP *pRsp = NULL;

    CMD *pCmd = (CMD *)pCmdMsg;

    LOG_INF("race set auto switch param, handler_id=0x%04X", pCmd->cmdhdr.id);

    auto_switch_set_parameter(&pCmd->param);

    /* send response */
    pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                pCmd->cmdhdr.id,
                                sizeof(RSP),
                                cid);
    if (pRsp == NULL) {
        LOG_ERR("race set usb mode RACE_ClaimPacketAppID fail");
        return NULL;
    }
    pRsp->status = 0;

    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    return NULL;
}

static void *app_race_common_control_auto_switch(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t  control;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    int32_t race_ret = RACE_ERRCODE_FAIL;
    RSP *pRsp = NULL;

    CMD *pCmd = (CMD *)pCmdMsg;

    LOG_INF("race set auto switch param, handler_id=0x%04X, control: %d", pCmd->cmdhdr.id, pCmd->control);

    auto_switch_control(pCmd->control);

    /* send response */
    pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                pCmd->cmdhdr.id,
                                sizeof(RSP),
                                cid);
    if (pRsp == NULL) {
        LOG_ERR("race set usb mode RACE_ClaimPacketAppID fail");
        return NULL;
    }
    pRsp->status = 0;


    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    return NULL;
}

static void *app_race_common_set_vpa_tx_gc(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t  vpa;
        uint8_t   tx_gc;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    int32_t race_ret = RACE_ERRCODE_FAIL;
    RSP *pRsp = NULL;

    CMD *pCmd = (CMD *)pCmdMsg;

    LOG_INF("race set auto switch param, handler_id=0x%04X, vpa: %d, tx_gc: %d", pCmd->cmdhdr.id, pCmd->vpa, pCmd->tx_gc);

    auto_switch_set_vap_tx_gc(pCmd->vpa, pCmd->tx_gc);

    /* send response */
    pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                pCmd->cmdhdr.id,
                                sizeof(RSP),
                                cid);
    if (pRsp == NULL) {
        LOG_ERR("race set usb mode RACE_ClaimPacketAppID fail");
        return NULL;
    }
    pRsp->status = 0;


    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    return NULL;
}

static void *app_race_common_set_power_control_mode(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t mode;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    int32_t race_ret = RACE_ERRCODE_FAIL;
    RSP *pRsp = NULL;

    CMD *pCmd = (CMD *)pCmdMsg;

    LOG_INF("race set power control mode, handler_id=0x%04X, mode: %d", pCmd->cmdhdr.id, pCmd->mode);

    auto_switch_set_mode(pCmd->mode);

    /* send response */
    pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                pCmd->cmdhdr.id,
                                sizeof(RSP),
                                cid);
    if (pRsp == NULL) {
        LOG_ERR("race set power control mode RACE_ClaimPacketAppID fail");
        return NULL;
    }
    pRsp->status = 0;

    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    return NULL;
}

static void *app_race_common_get_power_control_mode(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
        uint8_t mode;
    } PACKED RSP;

    int32_t race_ret = RACE_ERRCODE_FAIL;
    RSP *pRsp = NULL;

    CMD *pCmd = (CMD *)pCmdMsg;

    LOG_INF("race get power control mode, handler_id=0x%04X", pCmd->cmdhdr.id);

    /* send response */
    pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                pCmd->cmdhdr.id,
                                sizeof(RSP),
                                cid);
    if (pRsp == NULL) {
        LOG_ERR("race get power control mode RACE_ClaimPacketAppID fail");
        return NULL;
    }
    pRsp->status = 0;
    pRsp->mode = auto_switch_get_mode();

    LOG_INF("race get power control mode, mode: %d", pRsp->mode);

    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    return NULL;
}

static void *app_race_common_set_power_info(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t cid)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t vpa;
        uint8_t tx_gc;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    int32_t race_ret = RACE_ERRCODE_FAIL;
    RSP *pRsp = NULL;

    CMD *pCmd = (CMD *)pCmdMsg;

    LOG_INF("race set power info, handler_id=0x%04X, vpa: %d, tx_gc: %d", pCmd->cmdhdr.id, pCmd->vpa, pCmd->tx_gc);

    auto_switch_set_power_info(pCmd->vpa, pCmd->tx_gc);

    /* send response */
    pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                pCmd->cmdhdr.id,
                                sizeof(RSP),
                                cid);
    if (pRsp == NULL) {
        LOG_ERR("race set power info RACE_ClaimPacketAppID fail");
        return NULL;
    }
    pRsp->status = 0;

    race_ret = race_flush_packet((uint8_t *)pRsp, cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    return NULL;
}

#endif

/* Public functions ----------------------------------------------------------*/
void *app_race_common_race_cmd_handler(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t cid)
{
    void *pEvt = NULL;

    if (pCmdMsg->hdr.type == RACE_TYPE_COMMAND ||
        pCmdMsg->hdr.type == RACE_TYPE_RESPONSE ||
        pCmdMsg->hdr.type == RACE_TYPE_COMMAND_WITHOUT_RSP ||
        pCmdMsg->hdr.type == RACE_TYPE_NOTIFICATION)
    {
        switch (pCmdMsg->hdr.id)
        {
            case RACE_GET_APP_COMMON_CONFIG:
                return app_race_common_get_config((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);

            #if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE)
            case RACE_SET_USB_MODE:
                return app_race_common_set_usb_mode((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);

            case RACE_GET_USB_MODE:
                return app_race_common_get_usb_mode((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);
            #endif /* defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE) */
            #if defined(CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER)
            case RACE_SET_AUTO_SWITCH_PARAM:
                return app_race_common_set_auto_switch_param((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);
            case RACE_CONTROL_AUTO_SWITCH:
                return app_race_common_control_auto_switch((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);
            case RACE_SET_VPA_TX_GC:
                return app_race_common_set_vpa_tx_gc((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);
            case RACE_SET_POWER_CONTROL_MODE:
                return app_race_common_set_power_control_mode((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);
            case RACE_GET_POWER_CONTROL_MODE:
                return app_race_common_get_power_control_mode((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);
            case RACE_SET_POWER_INFO:
                return app_race_common_set_power_info((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, cid);
            #endif
            default:
                LOG_ERR("not support cmd 0x%x", pCmdMsg->hdr.id);
                break;
        }
    }

    return pEvt;
}

// #endif /*  */
