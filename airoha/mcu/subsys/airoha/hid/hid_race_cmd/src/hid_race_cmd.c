/* Copyright Statement:
 *
 * (C) 2024  Airoha Technology Corp. All rights reserved.
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
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
 * RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
 * TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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

#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include "hid_race_cmd.h"
#include "hid_race_cmd_mouse.h"
#include "hid_race_cmd_keyboard.h"
#include "hid_race_cmd_game_controller.h"
#include "race_port_bt.h"
#include "hal_wdt.h"

#define thisMODULE  hid_race_cmd
#define thisMOD    "hid_race_cmd"

LOG_MODULE_REGISTER(thisMODULE);

/******************************************************************************/
/*  Private typedef                                                           */
/******************************************************************************/


/******************************************************************************/
/*  Private  macro                                                            */
/******************************************************************************/


/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/


/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
hid_race_cmd_callback hid_race_cmd_req_cb = NULL;
static uint8_t race_cmd_cid;

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/


/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static void *hid_race_set_report_rate(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint16_t report_rate;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)&pCmd->report_rate, pCmd->cmdhdr.length);

    RACE_DBG_LOGI(thisMOD,"hid_race_set_report_rate = %d ", pCmd->report_rate);

    return NULL;
}

static void *hid_race_get_report_rate(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    hid_race_cmd_request(pCmd->cmdhdr.id, NULL, pCmd->cmdhdr.length);


    return NULL;
}

static void *hid_race_enter_labtest(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t rsvd;
    } PACKED HID_RACE_CMD_S;

    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;
    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            pCmd->cmdhdr.id,
                                            sizeof(HID_RACE_RSP_S),
                                            channel_id);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_enter_labtest race_pack fail");
        return NULL;
    }

    // To do : enter labtest mode
    pRsp->status = RACE_STATUS_OK;

    race_ret = race_flush_packet((uint8_t *)pRsp, channel_id);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    RACE_DBG_LOGI(thisMOD,"hid_race_enter_labtest");

    return NULL;
}

#if defined (CONFIG_AIR_MIDDLE_RGB)
static void *hid_race_set_rgb(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t rgb_setting;
        uint8_t rgb_num;
        uint8_t rgb_interval;
        uint8_t rgb_count;
        uint8_t rgb_color[0];
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;
    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)&pCmd->rgb_setting, pCmd->cmdhdr.length);

    return NULL;
}
#endif /* END _CONFIG_AIR_MIDDLE_RGB_ */

static void *hid_race_cmd_set_uniaa(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t pair_device_type;
        uint8_t addr_type;
        uint8_t pair_address[6];
        uint8_t uni_aa[4];
        uint8_t ltk[16];
        uint8_t skd[16];
        uint8_t iv[8];
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;
    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)&pCmd->pair_device_type, pCmd->cmdhdr.length);

    return NULL;
}


static void *hid_race_cmd_get_uniaa(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t device_type;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;
    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)&pCmd->device_type, pCmd->cmdhdr.length);

    return NULL;
}

static void *hid_race_cmd_enable_key_event(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint16_t event_id;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    if(pCmd->event_id == 0x0019) {  /* reboot */
        hal_wdt_software_reset();
    }
    else if(pCmd->event_id == 0x0095) { /* Factory reset */
        hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)&pCmd->event_id, pCmd->cmdhdr.length);
    }

    return NULL;
}

#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
static void *hid_race_set_key_remap(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t key_id;
        uint8_t key_type;
        /* Note that flexible arrays take up no space.
         * Here, it can only provide a pointer to the data immediately following the key_type.
         */
        uint8_t setting[];
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;
    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)&pCmd->key_id, pCmd->cmdhdr.length);

    RACE_DBG_LOGI(thisMOD,"hid_race_set_key_remap key_id = %d, key_type = %d, length = %d", pCmd->key_id, pCmd->key_type, length);

    return NULL;
}

static void *hid_race_get_key_remap(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t key_id;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;
    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)&pCmd->key_id, pCmd->cmdhdr.length);

    return NULL;
}

static void *hid_race_delete_macro(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t macro_name[16];            /* not fixed length */
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)&pCmd->macro_name, pCmd->cmdhdr.length - 2);

    RACE_DBG_LOGI(thisMOD,"hid_race_delete_macro");

    return NULL;
}
#endif

static void *hid_race_set_profile(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t target_profile_idx;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    RACE_DBG_LOGI(thisMOD,"hid_race_set_profile = %d", pCmd->target_profile_idx);
    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)&pCmd->target_profile_idx, pCmd->cmdhdr.length);

    return NULL;
}

static void *hid_race_get_profile(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;
    hid_race_cmd_request(pCmd->cmdhdr.id, NULL, pCmd->cmdhdr.length);

    return NULL;
}

static void *hid_race_set_debounce(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t debounce;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)&pCmd->debounce, pCmd->cmdhdr.length);
    RACE_DBG_LOGI(thisMOD,"hid_race_set_debounce = %d ", pCmd->debounce);

    return NULL;
}

static void *hid_race_get_debounce(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t debounce_state;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)&pCmd->debounce_state, pCmd->cmdhdr.length);
    RACE_DBG_LOGI(thisMOD,"hid_race_get_debounce debounce_state = %d", pCmd->debounce_state);

    return NULL;
}

static void *hid_race_set_restore(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    hid_race_cmd_request(pCmd->cmdhdr.id, NULL, pCmd->cmdhdr.length);
    RACE_DBG_LOGI(thisMOD,"hid_race_set_restore");

    return NULL;
}

static void *hid_race_get_battery(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    hid_race_cmd_request(pCmd->cmdhdr.id, NULL, pCmd->cmdhdr.length);
    RACE_DBG_LOGI(thisMOD,"hid_race_get_battery");

    return NULL;
}

static void *hid_race_btd_handler(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    void *pEvt = NULL;
    race_cmd_cid = channel_id;
    RACE_DBG_LOGI(thisMOD,"hid_race_btd_handler, type[0x%X], id[0x%X]", pCmdMsg->hdr.type, pCmdMsg->hdr.id);

    if (pCmdMsg->hdr.type == RACE_TYPE_COMMAND ||
        pCmdMsg->hdr.type == RACE_TYPE_COMMAND_WITHOUT_RSP ||
        pCmdMsg->hdr.type == RACE_TYPE_NOTIFICATION)
    {
        switch (pCmdMsg->hdr.id) {
            case RACE_SET_REPORT_RATE:
                return hid_race_set_report_rate((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);

            case RACE_GET_REPORT_RATE:
                return hid_race_get_report_rate((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);

            case RACE_VENDOR_ENTER_LABTEST:
                return hid_race_enter_labtest((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);

            #if defined (CONFIG_AIR_MIDDLE_RGB)
            case RACE_VENDOR_SET_RGB:
                return hid_race_set_rgb((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            #endif

            case RACE_SET_UNIAA:
                return hid_race_cmd_set_uniaa((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            case RACE_GET_UNIAA:
                return hid_race_cmd_get_uniaa((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            case RACE_ENABLE_KEY_EVENT:
                return hid_race_cmd_enable_key_event((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);

            #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
            case RACE_VENDOR_SET_KEY_REMAP:
                return hid_race_set_key_remap((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            case RACE_VENDOR_GET_KEY_REMAP:
                return hid_race_get_key_remap((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            case RACE_VENDOR_DELETE_MACRO:
                return hid_race_delete_macro((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            #endif

            case RACE_VENDOR_SET_PROFILE:
                return hid_race_set_profile((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            case RACE_VENDOR_GET_PROFILE:
                return hid_race_get_profile((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);

            case RACE_VENDOR_SET_DEBOUNCE:
                return hid_race_set_debounce((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            case RACE_VENDOR_GET_DEBOUNCE:
                return hid_race_get_debounce((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);

            case RACE_VENDOR_SET_RESTORE:
                return hid_race_set_restore((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);

            case RACE_GET_BATTERY:
                return hid_race_get_battery((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);

            #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE)

            case RACE_VENDOR_SET_SENSOR_LOD:
            case RACE_VENDOR_GET_SENSOR_LOD:
            case RACE_VENDOR_SET_SENSOR_MOTION_SYNC:
            case RACE_VENDOR_GET_SENSOR_MOTION_SYNC:
            case RACE_VENDOR_SET_SENSOR_ANGLE_SNAP:
            case RACE_VENDOR_GET_SENSOR_ANGLE_SNAP:
            case RACE_VENDOR_SET_SENSOR_RIPPLE_CTRL:
            case RACE_VENDOR_GET_SENSOR_RIPPLE_CTRL:
            case RACE_VENDOR_SET_DPI:
            case RACE_VENDOR_GET_DPI:
            case RACE_VENDOR_SET_DPI_LOOP_RANGE:
            case RACE_VENDOR_SET_DPI_CURRENT:
            #if defined(CONFIG_AIR_SW_KEY_DEBOUNCE)
            case RACE_VENDOR_SET_SW_DEBOUNCE:
            case RACE_VENDOR_GET_SW_DEBOUNCE:
            #endif
            #if defined(CONFIG_AIR_REMAP_FN_KEY)
            case RACE_VENDOR_SET_REMAP_FN_KEY:
            case RACE_VENDOR_GET_REMAP_FN_KEY:
            #endif
                return hid_race_cmd_mouse_handler(pCmdMsg, length, channel_id);
            #endif /* CONFIG_AIR_PRODUCT_TYPE_MOUSE */

            #if defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
            case RACE_SET_JOYSTICK_PARAMETER:
            case RACE_SET_TRIGGER_PARAMETER:
            case RACE_GET_JOYSTICK_PARAMETER:
            case RACE_GET_TRIGGER_PARAMETER:
            case RACE_SET_USB_MODE:
            case RACE_GET_USB_MODE:
            #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
            case RACE_VENDOR_SET_LT_RT_THRESHOLD:
            case RACE_VENDOR_GET_LT_RT_THRESHOLD:
            #endif
                return hid_race_cmd_game_controller_handler(pCmdMsg, length, channel_id);
            #endif /* CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER */

            case RACE_WBSCAN_CONTROL:
                break;

            default:
                RACE_DBG_LOGI(thisMOD, "not support cmd 0x%x", pCmdMsg->hdr.id);
                break;
        }
    }
    else if(pCmdMsg->hdr.type == RACE_TYPE_RESPONSE)
    {
        switch (pCmdMsg->hdr.id) {
            case RACE_SET_REPORT_RATE:
                RACE_DBG_LOGI(thisMOD, "RACE_SET_REPORT_RATE");
                break;

            default:
                RACE_DBG_LOGI(thisMOD, "not support response 0x%x", pCmdMsg->hdr.id);
                break;
        }
    }

    return pEvt;
}


/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
uint8_t hid_race_cmd_init(hid_race_cmd_callback cb)
{
    RACE_HANDLER handler;
    race_status_t ret;

    RACE_DBG_LOGI(thisMOD,"hid race cmd init, cb = 0x%x", cb);

    if (cb){
        hid_race_cmd_req_cb = cb;
        handler.id_start = RACE_ID_BTD_BEGIN;
        handler.id_end = RACE_ID_BTD_END;
        handler.handler = hid_race_btd_handler;
        ret = RACE_Register_Handler(&handler);
        if (RACE_STATUS_OK != ret)
        {
            RACE_DBG_LOGI(thisMOD, "hid race register fail: ret = %d", ret);
            return 1;
        }
        return 0;
    }

    return 1;
}

void hid_race_cmd_request(uint16_t race_cmd_id, uint8_t *para, uint16_t len)
{
    if (hid_race_cmd_req_cb){
        hid_race_cmd_req_cb(race_cmd_id, para, len);
    }
}

void hid_race_set_report_rate_rsp(uint8_t rsp_status)
{
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_NOTIFICATION,
                                            RACE_SET_REPORT_RATE,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_set_report_rate race_pack fail");
        return;
    }

    pRsp->status = rsp_status;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}

void hid_race_get_report_rate_rsp(uint16_t report_rate)
{
    typedef struct {
        uint8_t status;
        uint16_t report_rate;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_GET_REPORT_RATE,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_get_report_rate race_pack fail");
        return;
    }

    pRsp->report_rate = report_rate;
    pRsp->status = RACE_STATUS_OK;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    RACE_DBG_LOGI(thisMOD,"hid_race_get_report_rate = %d ", pRsp->report_rate);
}

race_errcode_enum hid_race_set_report_rate_req(uint16_t report_rate)
{
    if (race_bt_is_connected(MUX_BT_BLE))
    {

        typedef struct {
            uint16_t report_rate;
        } PACKED HID_RACE_CMD_S;

        /* send request packet*/
        HID_RACE_CMD_S *pReq = RACE_ClaimPacket(RACE_TYPE_COMMAND,
                                                RACE_SET_REPORT_RATE,
                                                sizeof(HID_RACE_CMD_S),
                                                MUX_BT_BLE);
        if (pReq == NULL) {
            RACE_DBG_LOGI(thisMOD, "hid_race_set_report_rate pReq fail");
            return RACE_ERRCODE_NOT_ENOUGH_MEMORY;
        }

        pReq->report_rate = report_rate;

        race_errcode_enum race_ret = race_flush_packet((uint8_t *)pReq, MUX_BT_BLE);

        if (race_ret != RACE_ERRCODE_SUCCESS) {
            RACE_FreePacket((void *)pReq);
            return RACE_ERRCODE_NOT_ENOUGH_MEMORY;
        }

        RACE_DBG_LOGI(thisMOD, "hid_race_set_report_rate_req = %d  RACE_STATUS_OK", report_rate);

        return RACE_ERRCODE_SUCCESS;
    }

    return RACE_ERRCODE_CONNECTION_BROKEN;

}

race_errcode_enum hid_race_set_rgb_rsp(uint8_t rsp_status)
{
    RACE_DBG_LOGI(thisMOD, "hid_race_set_rgb_rs, rsp_status = 0x%X", rsp_status);
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_SET_RGB,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_set_rgb race_pack fail");
        return RACE_ERRCODE_FAIL;
    }

    pRsp->status = rsp_status;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
        return RACE_ERRCODE_FAIL;
    }

    RACE_DBG_LOGI(thisMOD,"hid_race_set_rgb");
    return RACE_ERRCODE_SUCCESS;
}

void hid_race_set_uniaa_rsp(uint8_t rsp_status)
{
    RACE_DBG_LOGI(thisMOD, "hid_race_set_uniaa_rsp, rsp_status = 0x%X", rsp_status);
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_SET_UNIAA,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_set_uniaa_rsp race_pack fail");
        return;
    }

    pRsp->status = rsp_status;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    RACE_DBG_LOGI(thisMOD,"hid_race_set_uniaa_rsp");
    return;
}

race_errcode_enum hid_race_get_uniaa_rsp(uint8_t *info)
{
    RACE_DBG_LOGI(thisMOD, "hid_race_get_uniaa_rsp");

    typedef struct {
        uint8_t status;
        uint8_t remote_address[7];
        uint8_t uni_aa[4];
        uint8_t ltk[16];
        uint8_t skd[16];
        uint8_t iv[8];
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;
    uint8_t rsp_size = sizeof(HID_RACE_RSP_S);

    if (!info) {
        RACE_DBG_LOGI(thisMOD, "hid_race_get_uniaa_rsp race_pack fail");
        rsp_size = 1;
    }

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_GET_UNIAA,
                                            rsp_size,
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_get_uniaa_rsp race_pack fail");
        return race_ret;
    }

    if(!info){
        pRsp->status = RACE_STATUS_ERROR;
    }
    else
    {
        pRsp->status = RACE_STATUS_OK;
        uint8_t *value = (uint8_t *)info;
        memcpy(pRsp->remote_address, value + ADDR_OFFSET, 7);
        memcpy(pRsp->uni_aa, value + UNI_AA_OFFSET, 4);
        memcpy(pRsp->ltk, value + LTK_OFFSET, 16);
        memcpy(pRsp->skd, value + SKD_OFFSET, 16);
        memcpy(pRsp->iv, value + IV_OFFSET, 8);
        RACE_DBG_LOGI(thisMOD, "hid_race_get_uniaa_rsp, addr_type = 0x%X, addr = 0x%02X-%02X-%02X-%02X-%02X-%02X, uniaa = 0x%02X-%02X-%02X-%02X",
                        pRsp->remote_address[0], pRsp->remote_address[1], pRsp->remote_address[2], pRsp->remote_address[3],
                        pRsp->remote_address[4], pRsp->remote_address[5], pRsp->remote_address[6],
                        pRsp->uni_aa[0], pRsp->uni_aa[1], pRsp->uni_aa[2], pRsp->uni_aa[3]
                    );
    }

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    return race_ret;
}

void hid_race_enable_key_event_rsp(uint8_t rsp_status)
{
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_NOTIFICATION,
                                            RACE_ENABLE_KEY_EVENT,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_enable_key_event_rsp race_pack fail");
        return;
    }

    pRsp->status = rsp_status;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}

race_errcode_enum hid_race_set_dpi_value_req(uint16_t x_dpi, uint16_t y_dpi)
{
    if (race_bt_is_connected(MUX_BT_BLE))
    {
        typedef struct {
            uint16_t x_dpi;
            uint16_t y_dpi;
        } PACKED HID_RACE_CMD_S;

        /* send request packet*/
        HID_RACE_CMD_S *pReq = RACE_ClaimPacket(RACE_TYPE_COMMAND,
                                                RACE_SET_DPI_VALUE,
                                                sizeof(HID_RACE_CMD_S),
                                                MUX_BT_BLE);
        if (pReq == NULL) {
            RACE_DBG_LOGI(thisMOD, "hid_race_set_dpi_value_req pRsp fail");
            return RACE_ERRCODE_NOT_ENOUGH_MEMORY;
        }

        pReq->x_dpi = x_dpi;
        pReq->y_dpi = y_dpi;

        race_errcode_enum race_ret = race_flush_packet((uint8_t *)pReq, MUX_BT_BLE);
        if (race_ret != RACE_ERRCODE_SUCCESS) {
            RACE_FreePacket((void *)pReq);
            return RACE_ERRCODE_NOT_ENOUGH_MEMORY;
        }

        RACE_DBG_LOGI(thisMOD, "hid_race_set_dpi_value_req, RACE_STATUS_OK, x_dpi = %d, y_dpi = %d", pReq->x_dpi, pReq->y_dpi);

        return RACE_ERRCODE_SUCCESS;
    }
    else{
        RACE_DBG_LOGI(thisMOD, "race_bt_is_connected get false");
    }
    return RACE_ERRCODE_CONNECTION_BROKEN;
}

race_errcode_enum hid_race_set_battery_req(uint8_t charging, uint8_t battery)
{
    if (race_bt_is_connected(MUX_BT_BLE))
    {
        typedef struct {
            uint8_t status;
            uint8_t charging;
            uint8_t current_battery;
        } PACKED HID_RACE_RSP_S;

        /* send response packet*/
       HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_COMMAND,
                                        RACE_GET_BATTERY,
                                        sizeof(HID_RACE_RSP_S),
                                        MUX_BT_BLE);
        if (pRsp == NULL) {
            RACE_DBG_LOGI(thisMOD, "hid_race_set_battery_req pReq fail");
            return RACE_ERRCODE_NOT_ENOUGH_MEMORY;
        }

        pRsp->charging = charging;
        pRsp->current_battery = battery;
        pRsp->status = RACE_ERRCODE_SUCCESS;

        race_errcode_enum race_ret = race_flush_packet((uint8_t *)pRsp, MUX_BT_BLE);
        if (race_ret != RACE_ERRCODE_SUCCESS) {
            RACE_FreePacket((void *)pRsp);
            return RACE_ERRCODE_NOT_ENOUGH_MEMORY;
        }

        RACE_DBG_LOGI(thisMOD, "hid_race_set_battery_req, charging = %d, battery = %d, RACE_STATUS_OK", charging, battery);
        return RACE_ERRCODE_SUCCESS;
    }
    else{
        RACE_DBG_LOGI(thisMOD, "hid_race_set_battery_req, race_bt_is_connected get false");
    }
    return RACE_ERRCODE_CONNECTION_BROKEN;
}

#if defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
void hid_race_get_usb_mode_rsp(uint8_t mode)
{
    typedef struct {
        uint8_t status;
        uint8_t mode;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_GET_USB_MODE,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_get_usb_mode_rsp fail");
        return;
    }

    pRsp->status = RACE_STATUS_OK;
    pRsp->mode = mode;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    RACE_DBG_LOGI(thisMOD,"hid_race_get_usb_mode_rsp = %d ", pRsp->mode);
}

race_errcode_enum hid_race_set_usb_mode_req(uint8_t mode)
{
    if (race_bt_is_connected(MUX_BT_BLE))
    {
        typedef struct {
            uint8_t mode;
        } PACKED HID_RACE_CMD_S;

        /* send request packet*/
        HID_RACE_CMD_S *pReq = RACE_ClaimPacket(RACE_TYPE_COMMAND,
                                                RACE_SET_USB_MODE,
                                                sizeof(HID_RACE_CMD_S),
                                                MUX_BT_BLE);
        if (pReq == NULL) {
            RACE_DBG_LOGI(thisMOD, "hid_race_set_usb_mode_req pReq fail");
            return RACE_ERRCODE_NOT_ENOUGH_MEMORY;
        }

        pReq->mode = mode;

        race_errcode_enum race_ret = race_flush_packet((uint8_t *)pReq, MUX_BT_BLE);

        if (race_ret != RACE_ERRCODE_SUCCESS) {
            RACE_FreePacket((void *)pReq);
            return RACE_ERRCODE_NOT_ENOUGH_MEMORY;
        }

        RACE_DBG_LOGI(thisMOD, "hid_race_set_usb_mode_req mode = %d  RACE_STATUS_OK", mode);

        return RACE_ERRCODE_SUCCESS;
    }

    return RACE_ERRCODE_CONNECTION_BROKEN;
}
#endif /* defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER) */

#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
void hid_race_set_key_remap_rsp(uint8_t rsp_status)
{
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_SET_KEY_REMAP,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);

    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_set_key_remap_rsp race_pack fail");
        return;
    }
    RACE_DBG_LOGI(thisMOD, " hid_race_set_key_remap_rsp = %d", rsp_status);
    pRsp->status = rsp_status;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}

void hid_race_get_key_remap_rsp(uint8_t key_id, uint8_t key_type, uint8_t *setting, uint16_t len)
{
    typedef struct {
        uint8_t status;
        uint8_t key_id;
        uint8_t func_type;
        uint8_t setting[];
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_GET_KEY_REMAP,
                                            sizeof(HID_RACE_RSP_S) + len,
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_get_key_remap_rsp race_pack fail");
        return;
    }

    pRsp->key_id = key_id;
    pRsp->func_type = key_type;
    if((setting != NULL) && (len > 0))
    {
        memcpy(pRsp->setting, setting, len);
    }

    pRsp->status = RACE_ERRCODE_SUCCESS;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    RACE_DBG_LOGI(thisMOD,"hid_race_get_key_remap_rsp key_type = %d, len = %d", key_type, len);
}


void hid_race_delete_macro_rsp(uint8_t status)
{
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_DELETE_MACRO,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_delete_macro_rsp race_pack fail");
        return;
    }

    pRsp->status = status;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}
#endif

void hid_race_set_profile_rsp(uint8_t rsp_status)
{
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_SET_PROFILE,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_set_profile_rsp race_pack fail");
        return;
    }

    pRsp->status = rsp_status;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}

void hid_race_get_profile_rsp(uint8_t profile_idx)
{
    typedef struct {
        uint8_t status;
        uint8_t current_profile_idx;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_GET_PROFILE,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_get_profile_rsp race_pack fail");
        return;
    }

    pRsp->current_profile_idx = profile_idx;
    pRsp->status = RACE_ERRCODE_SUCCESS;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    RACE_DBG_LOGI(thisMOD,"hid_race_get_profile = %d", pRsp->current_profile_idx);
}

void hid_race_set_debounce_rsp(uint8_t rsp_status)
{
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_SET_DEBOUNCE,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_set_debounce_rsp race_pack fail");
        return;
    }

    pRsp->status = rsp_status;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}

void hid_race_get_debounce_rsp(uint8_t debounce_time)
{
    typedef struct {
        uint8_t status;
        uint8_t debounce;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_GET_DEBOUNCE,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_get_debounce_rsp race_pack fail");
        return;
    }

    pRsp->debounce = debounce_time;
    pRsp->status = RACE_ERRCODE_SUCCESS;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    RACE_DBG_LOGI(thisMOD,"hid_race_get_debounce_rsp debounce time = %d", pRsp->debounce);
}

void hid_race_set_restore_rsp(uint8_t rsp_status)
{
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_SET_RESTORE,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_set_restore_rsp race_pack fail");
        return ;
    }

    pRsp->status = rsp_status;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}

void hid_race_get_battery_rsp(uint8_t charging, uint8_t battery)
{
    typedef struct {
        uint8_t status;
        uint8_t charging;
        uint8_t current_battery;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_GET_BATTERY,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_get_battery_rsp race_pack fail");
        return;
    }

    pRsp->charging = charging;
    pRsp->current_battery = battery;
    pRsp->status = RACE_ERRCODE_SUCCESS;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }

    RACE_DBG_LOGI(thisMOD,"hid_race_get_battery");
}
