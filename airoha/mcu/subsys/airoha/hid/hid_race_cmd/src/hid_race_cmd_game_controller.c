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

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <sys/types.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include "hid_race_cmd_game_controller.h"
#include "assert.h"
#include "hid_race_cmd.h"
#include "hid_common.h"
#if defined(AIR_USB_XINPUT_ENABLE)
#include "nvkey.h"
#include "hal_wdt.h"
#include "hal_gpt.h"
#include "hal_nvic.h"
#endif /* AIR_USB_XINPUT_ENABLE */

/* Private define ------------------------------------------------------------*/
#define thisMODULE  race_cmd_game_controller
#define thisMOD    "race_cmd_game_controller"

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t race_cmd_cid;

/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void *hid_race_cmd_set_joystick_parameter(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t settings[0];
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)(&(pCmd->settings[0])), pCmd->cmdhdr.length);

    return NULL;
}

static void *hid_race_cmd_set_trigger_parameter(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t settings[0];
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)(&(pCmd->settings[0])), pCmd->cmdhdr.length);

    return NULL;
}

static void *hid_race_cmd_get_joystick_parameter(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t settings[0];
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)(&(pCmd->settings[0])), pCmd->cmdhdr.length);

    return NULL;
}

static void *hid_race_cmd_get_trigger_parameter(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t settings[0];
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)(&(pCmd->settings[0])), pCmd->cmdhdr.length);

    return NULL;
}

#if defined(AIR_USB_XINPUT_ENABLE)
static void *hid_race_cmd_set_usb_mode(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t mode;
    } PACKED HID_RACE_CMD_S;

    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;
    HID_RACE_RSP_S *pRsp = NULL;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

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
                                sizeof(HID_RACE_RSP_S),
                                race_cmd_cid);
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

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    return NULL;
}

static void *hid_race_cmd_get_usb_mode(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
    } PACKED HID_RACE_CMD_S;

    typedef struct {
        uint8_t status;
        uint8_t mode;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;
    HID_RACE_RSP_S *pRsp = NULL;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

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
                                sizeof(HID_RACE_RSP_S),
                                race_cmd_cid);
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

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    return NULL;
}
#endif /* AIR_USB_XINPUT_ENABLE */

#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
static void *hid_race_cmd_set_lt_rt_threshold(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint32_t threshold;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;
    RACE_DBG_LOGI(thisMOD, "hid_race_cmd_set_lt_rt_threshold = %x", pCmd->threshold);
    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)(&(pCmd->threshold)), pCmd->cmdhdr.length);
    return NULL;
}

static void *hid_race_cmd_get_lt_rt_threshold(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    hid_race_cmd_request(pCmd->cmdhdr.id, NULL, pCmd->cmdhdr.length);
    return NULL;
}
#endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */

/* Public functions ----------------------------------------------------------*/
void hid_race_cmd_set_joystick_parameter_rsp(uint8_t status)
{
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_SET_JOYSTICK_PARAMETER,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_cmd_set_joystick_parameter_rsp race_pack fail");
        return;
    }

    pRsp->status = status;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}

void hid_race_cmd_set_trigger_parameter_rsp(uint8_t status)
{
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_SET_TRIGGER_PARAMETER,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_cmd_set_trigger_parameter_rsp race_pack fail");
        return;
    }

    pRsp->status = status;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}

void hid_race_cmd_get_joystick_parameter_rsp(uint8_t status, uint32_t x, uint32_t y, uint32_t z, uint32_t rz)
{
    typedef struct {
        uint8_t status;
        uint32_t x;
        uint32_t y;
        uint32_t z;
        uint32_t rz;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_GET_JOYSTICK_PARAMETER,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_cmd_get_joystick_parameter_rsp race_pack fail");
        return;
    }

    pRsp->status = status;
    pRsp->x = x;
    pRsp->y = y;
    pRsp->z = z;
    pRsp->rz = rz;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}

void hid_race_cmd_get_trigger_parameter_rsp(uint8_t status, uint32_t lt, uint32_t rt)
{
    typedef struct {
        uint8_t status;
        uint32_t lt;
        uint32_t rt;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_GET_TRIGGER_PARAMETER,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_cmd_get_trigger_parameter_rsp race_pack fail");
        return;
    }

    pRsp->status = status;
    pRsp->lt = lt;
    pRsp->rt = rt;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}

#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
void hid_race_cmd_set_lt_rt_threshold_rsp(uint8_t status)
{
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_SET_LT_RT_THRESHOLD,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_cmd_set_lt_rt_threshold_rsp race_pack fail");
        return;
    }

    pRsp->status = status;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}

void hid_race_cmd_get_lt_rt_threshold_rsp(uint32_t threshold)
{
    typedef struct {
        uint8_t status;
        uint32_t threshold;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_GET_LT_RT_THRESHOLD,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_cmd_get_lt_rt_threshold_rsp race_pack fail");
        return;
    }

    pRsp->threshold = threshold;
    pRsp->status = RACE_ERRCODE_SUCCESS;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}
#endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */

void *hid_race_cmd_game_controller_handler(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    void *pEvt = NULL;
    race_cmd_cid = channel_id;

    if (pCmdMsg->hdr.type == RACE_TYPE_COMMAND ||
        pCmdMsg->hdr.type == RACE_TYPE_COMMAND_WITHOUT_RSP ||
        pCmdMsg->hdr.type == RACE_TYPE_NOTIFICATION)
    {
        switch (pCmdMsg->hdr.id)
        {
            case RACE_SET_JOYSTICK_PARAMETER:
                return hid_race_cmd_set_joystick_parameter((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);

            case RACE_SET_TRIGGER_PARAMETER:
                return hid_race_cmd_set_trigger_parameter((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);

            case RACE_GET_JOYSTICK_PARAMETER:
                return hid_race_cmd_get_joystick_parameter((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);

            case RACE_GET_TRIGGER_PARAMETER:
                return hid_race_cmd_get_trigger_parameter((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);

            #if defined(AIR_USB_XINPUT_ENABLE)
            case RACE_SET_USB_MODE:
                return hid_race_cmd_set_usb_mode((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);

            case RACE_GET_USB_MODE:
                return hid_race_cmd_get_usb_mode((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            #endif /* AIR_USB_XINPUT_ENABLE */

            #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
            case RACE_VENDOR_SET_LT_RT_THRESHOLD:
                return hid_race_cmd_set_lt_rt_threshold((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);

            case RACE_VENDOR_GET_LT_RT_THRESHOLD:
                return hid_race_cmd_get_lt_rt_threshold((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            #endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */

            default:
                RACE_DBG_LOGI(thisMOD, "not support cmd 0x%x", pCmdMsg->hdr.id);
                assert(0);
                break;
        }
    }
    else if(pCmdMsg->hdr.type == RACE_TYPE_RESPONSE)
    {

    }

    return pEvt;
}

#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */
