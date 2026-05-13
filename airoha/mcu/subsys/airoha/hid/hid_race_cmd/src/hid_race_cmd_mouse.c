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
#if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE)
#include <stdint.h>
#include <sys/types.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include "hid_race_cmd_mouse.h"
#include "assert.h"
#include "motion_sensor_mgr.h"
#include "hid_race_cmd.h"
#include "hid_common.h"
#define thisMODULE  race_cmd_ms
#define thisMOD    "race_cmd_ms"

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
static void *hid_race_ms_set_sensor_LOD(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t sensor_LOD;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)&pCmd->sensor_LOD, pCmd->cmdhdr.length);
    RACE_DBG_LOGI(thisMOD,"hid_race_ms_set_sensor_LOD = %d ", pCmd->sensor_LOD);

    return NULL;
}

static void *hid_race_ms_get_sensor_LOD(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;
    hid_race_cmd_request(pCmd->cmdhdr.id, NULL, pCmd->cmdhdr.length);

    return NULL;
}


static void *hid_race_ms_set_sensor_motion_sync(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t sensor_motion_sync;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)&pCmd->sensor_motion_sync, pCmd->cmdhdr.length);
    RACE_DBG_LOGI(thisMOD,"hid_race_ms_set_sensor_motion_sync = %d ", pCmd->sensor_motion_sync);

    return NULL;
}

static void *hid_race_ms_get_sensor_motion_sync(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;
    hid_race_cmd_request(pCmd->cmdhdr.id, NULL, pCmd->cmdhdr.length);

    return NULL;
}

static void *hid_race_ms_set_sensor_angle_snap(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t sensor_angle_snap;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;
    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)&pCmd->sensor_angle_snap, pCmd->cmdhdr.length);
    RACE_DBG_LOGI(thisMOD,"hid_race_ms_set_sensor_angle_snap = %d ", pCmd->sensor_angle_snap);
    return NULL;
}

static void *hid_race_ms_get_sensor_angle_snap(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;
    hid_race_cmd_request(pCmd->cmdhdr.id, NULL, pCmd->cmdhdr.length);

    return NULL;
}

static void *hid_race_ms_set_sensor_ripple_control(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t sensor_ripple_control;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)&pCmd->sensor_ripple_control, pCmd->cmdhdr.length);
    RACE_DBG_LOGI(thisMOD,"hid_race_ms_set_sensor_ripple_control = %d ", pCmd->sensor_ripple_control);
    return NULL;
}

static void *hid_race_ms_get_sensor_ripple_control(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;
    hid_race_cmd_request(pCmd->cmdhdr.id, NULL, pCmd->cmdhdr.length);

    return NULL;
}

static void *hid_race_ms_set_dpi(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t dpi_stage_idx;
        #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
        uint16_t x_dpi_setting_value;
        uint16_t y_dpi_setting_value;
        #else
        uint16_t dpi_setting_value;
        #endif
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;
    #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
    RACE_DBG_LOGI(thisMOD,"hid_race_ms_set_dpi idx = %d, x_val = %d, y_val = %d", pCmd->dpi_stage_idx, pCmd->x_dpi_setting_value, pCmd->y_dpi_setting_value);
    #else
    RACE_DBG_LOGI(thisMOD,"hid_race_ms_set_dpi idx = %d, val = %d", pCmd->dpi_stage_idx, pCmd->dpi_setting_value);
    #endif
    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)&pCmd->dpi_stage_idx, pCmd->cmdhdr.length);
    
    return NULL;
}

static void *hid_race_ms_get_dpi(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    hid_race_cmd_request(pCmd->cmdhdr.id, NULL, pCmd->cmdhdr.length);
    RACE_DBG_LOGI(thisMOD,"hid_race_ms_get_dpi");

    return NULL;
}

static void *hid_race_ms_set_dpi_loop_stage_range(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t range;
    } PACKED HID_RACE_CMD_S;
    
    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)&pCmd->range, pCmd->cmdhdr.length);
    RACE_DBG_LOGI(thisMOD,"hid_race_ms_set_dpi_loop_stage_range = %d", pCmd->range);

    return NULL;
}

static void *hid_race_ms_set_dpi_current(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t dpi_idx;
    } PACKED HID_RACE_CMD_S;
    
    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    RACE_DBG_LOGI(thisMOD,"hid_race_ms_set_dpi_current = %d", pCmd->dpi_idx);
    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)&pCmd->dpi_idx, pCmd->cmdhdr.length);

    return NULL;
}

#if defined(CONFIG_AIR_SW_KEY_DEBOUNCE)
static void *hid_race_ms_set_sw_debounce(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        T_DEBOUNCE_PARA_S settings;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)&pCmd->settings, pCmd->cmdhdr.length);
    RACE_DBG_LOGI(thisMOD,"hid_race_ms_set_sw_debounce wired deb = %d 2.4 deb = %d, bt_step = %d", pCmd->settings.step_wired, pCmd->settings.step_2_4g, pCmd->settings.step_bt);

    return NULL;
}

static void *hid_race_ms_get_sw_debounce(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
    } PACKED HID_RACE_CMD_S;

    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;

    hid_race_cmd_request(pCmd->cmdhdr.id, NULL, pCmd->cmdhdr.length);
    RACE_DBG_LOGI(thisMOD,"hid_race_ms_get_sw_debounce");

    return NULL;
}
#endif

#if defined(CONFIG_AIR_REMAP_FN_KEY)
static void *hid_race_cmd_set_remap_fn_key(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t fn_key;
    } PACKED HID_RACE_CMD_S;
    
    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;
    
    RACE_DBG_LOGI(thisMOD,"hid_race_cmd_set_remap_fn_key fn_key = %x", pCmd->fn_key);
    hid_race_cmd_request(pCmd->cmdhdr.id, (uint8_t *)&pCmd->fn_key, pCmd->cmdhdr.length);

    return NULL;
}

static void *hid_race_cmd_get_remap_fn_key(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
    } PACKED HID_RACE_CMD_S;
    
    HID_RACE_CMD_S *pCmd = (HID_RACE_CMD_S *)pCmdMsg;
    hid_race_cmd_request(pCmd->cmdhdr.id, NULL, pCmd->cmdhdr.length);
    RACE_DBG_LOGI(thisMOD,"hid_race_cmd_get_remap_fn_key");
    
    return NULL;
}
#endif
/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/


void *hid_race_cmd_mouse_handler(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    void *pEvt = NULL;
    race_cmd_cid = channel_id;

    if (pCmdMsg->hdr.type == RACE_TYPE_COMMAND ||
        pCmdMsg->hdr.type == RACE_TYPE_COMMAND_WITHOUT_RSP ||
        pCmdMsg->hdr.type == RACE_TYPE_NOTIFICATION)
    {
        switch (pCmdMsg->hdr.id)
        {
            case RACE_VENDOR_SET_SENSOR_LOD:
                return hid_race_ms_set_sensor_LOD((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            
            case RACE_VENDOR_GET_SENSOR_LOD:
                return hid_race_ms_get_sensor_LOD((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            
            case RACE_VENDOR_SET_SENSOR_MOTION_SYNC:
                return hid_race_ms_set_sensor_motion_sync((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            
            case RACE_VENDOR_GET_SENSOR_MOTION_SYNC:
                return hid_race_ms_get_sensor_motion_sync((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            
            case RACE_VENDOR_SET_SENSOR_ANGLE_SNAP:
                return hid_race_ms_set_sensor_angle_snap((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            
            case RACE_VENDOR_GET_SENSOR_ANGLE_SNAP:
                return hid_race_ms_get_sensor_angle_snap((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            
            case RACE_VENDOR_SET_SENSOR_RIPPLE_CTRL:
                return hid_race_ms_set_sensor_ripple_control((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            
            case RACE_VENDOR_GET_SENSOR_RIPPLE_CTRL:
                return hid_race_ms_get_sensor_ripple_control((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);

            case RACE_VENDOR_SET_DPI:
                return hid_race_ms_set_dpi((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            
            case RACE_VENDOR_GET_DPI:
                return hid_race_ms_get_dpi((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            
            case RACE_VENDOR_SET_DPI_LOOP_RANGE:
                return hid_race_ms_set_dpi_loop_stage_range((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            
            case RACE_VENDOR_SET_DPI_CURRENT:
                return hid_race_ms_set_dpi_current((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);

            #if defined(CONFIG_AIR_SW_KEY_DEBOUNCE)
            case RACE_VENDOR_SET_SW_DEBOUNCE:
                return hid_race_ms_set_sw_debounce((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);

            case RACE_VENDOR_GET_SW_DEBOUNCE:
                return hid_race_ms_get_sw_debounce((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            #endif

            #if defined(CONFIG_AIR_REMAP_FN_KEY)
            case RACE_VENDOR_SET_REMAP_FN_KEY:
                return hid_race_cmd_set_remap_fn_key((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            
            case RACE_VENDOR_GET_REMAP_FN_KEY:
                return hid_race_cmd_get_remap_fn_key((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            #endif
            
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

 void hid_race_ms_set_sensor_LOD_rsp(uint8_t rsp_status)
{
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_SET_SENSOR_LOD,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_ms_set_sensor_LOD_rsp race_pack fail");
        return;
    }

    pRsp->status = rsp_status;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}

void hid_race_ms_get_sensor_LOD_rsp(uint8_t LOD)
{
    typedef struct {
        uint8_t status;
        uint8_t sensor_LOD;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_GET_SENSOR_LOD,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_ms_get_sensor_LOD_rsp race_pack fail");
        return;
    }

    pRsp->sensor_LOD = LOD;
    pRsp->status = RACE_ERRCODE_SUCCESS; 

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
    
    RACE_DBG_LOGI(thisMOD,"hid_race_ms_get_sensor_LOD_rsp = %d ", pRsp->sensor_LOD);
}

void hid_race_ms_set_sensor_motion_sync_rsp(uint8_t rsp_status)
{
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_SET_SENSOR_MOTION_SYNC,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_ms_set_sensor_motion_sync_rsp race_pack fail");
        return;
    }

    pRsp->status = rsp_status;
    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}

void hid_race_ms_get_sensor_motion_sync_rsp(uint8_t motion_sync)
{
    typedef struct {
        uint8_t status;
        uint8_t sensor_motion_sync;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_GET_SENSOR_MOTION_SYNC,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_ms_get_sensor_motion_sync_rsp race_pack fail");
        return;
    }

    pRsp->sensor_motion_sync = motion_sync;
    pRsp->status = RACE_ERRCODE_SUCCESS; 

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
    
    RACE_DBG_LOGI(thisMOD,"hid_race_ms_get_sensor_motion_sync_rsp = %d ", motion_sync);
}

void hid_race_ms_set_sensor_angle_snap_rsp(uint8_t rsp_status)
{
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_SET_SENSOR_ANGLE_SNAP,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_ms_set_sensor_angle_snap_rsp race_pack fail");
        return;
    }

    pRsp->status = rsp_status;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}

void hid_race_ms_get_sensor_angle_snap_rsp(uint8_t angle_snap)
{
    typedef struct {
        uint8_t status;
        uint8_t sensor_angle_snap;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_GET_SENSOR_ANGLE_SNAP,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_ms_get_sensor_angle_snap_rsp race_pack fail");
        return;
    }

    pRsp->sensor_angle_snap = angle_snap;
    pRsp->status = RACE_ERRCODE_SUCCESS; 

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
    
    RACE_DBG_LOGI(thisMOD,"hid_race_ms_get_sensor_angle_snap_rsp = %d ", pRsp->sensor_angle_snap);
}

void hid_race_ms_set_sensor_ripple_control_rsp(uint8_t rsp_status)
{
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_SET_SENSOR_RIPPLE_CTRL,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_ms_set_sensor_ripple_control_rsp race_pack fail");
        return;
    }

    pRsp->status = rsp_status;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}

void hid_race_ms_get_sensor_ripple_control_rsp(uint8_t ripple_control)
{
    typedef struct {
        uint8_t status;
        uint8_t sensor_ripple_control;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_GET_SENSOR_RIPPLE_CTRL,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_ms_get_sensor_ripple_control_rsp race_pack fail");
        return;
    }

    pRsp->sensor_ripple_control = ripple_control;
    pRsp->status = RACE_ERRCODE_SUCCESS; 

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
    
    RACE_DBG_LOGI(thisMOD,"hid_race_ms_get_sensor_ripple_control_rsp = %d ", pRsp->sensor_ripple_control);
}

void hid_race_ms_set_dpi_rsp(uint8_t rsp_status)
{
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_SET_DPI,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_ms_set_dpi race_pack fail");
        return;
    }

    pRsp->status = rsp_status;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}
#if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
void hid_race_ms_get_dpi_rsp(uint8_t dpi_loop_stage_range, uint8_t dpi_curr_idx, uint16_t* x_dpi_settings, uint16_t* y_dpi_settings)
#else
void hid_race_ms_get_dpi_rsp(uint8_t dpi_loop_stage_range, uint8_t dpi_curr_idx, uint16_t* dpi_settings)
#endif
{
    typedef struct {
        uint8_t status;
        uint8_t stage_loop_range;
        uint8_t curr_stage_idx;
        #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
        uint16_t x_dpi_setting_array[MAX_DPI_COUNT];
        uint16_t y_dpi_setting_array[MAX_DPI_COUNT];
        #else
        uint16_t dpi_setting_array[MAX_DPI_COUNT];
        #endif
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_NOTIFICATION,
                                            RACE_VENDOR_GET_DPI,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_ms_get_dpi_rsp race_pack fail");
        return;
    }

    /* Transfer data to the packed structure members */
    pRsp->stage_loop_range = dpi_loop_stage_range;
    pRsp->curr_stage_idx = dpi_curr_idx;
    
    #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
    memcpy(pRsp->x_dpi_setting_array, x_dpi_settings, sizeof(uint16_t) * MAX_DPI_COUNT);
    memcpy(pRsp->y_dpi_setting_array, y_dpi_settings, sizeof(uint16_t) * MAX_DPI_COUNT);
    #else
    memcpy(pRsp->dpi_setting_array, dpi_settings, sizeof(uint16_t) * MAX_DPI_COUNT);
    #endif

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
    
    RACE_DBG_LOGI(thisMOD,"hid_race_ms_get_dpi_rsp");
}

void hid_race_ms_set_dpi_loop_stage_range_rsp(uint8_t rsp_status)
{
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_SET_DPI_LOOP_RANGE,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_ms_set_dpi_loop_stage_range_rsp race_pack fail");
        return;
    }

    pRsp->status = rsp_status;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}

void hid_race_ms_set_dpi_current_rsp(uint8_t rsp_status)
{
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;

    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_SET_DPI_CURRENT,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_ms_set_dpi_current_rsp race_pack fail");
        return;
    }

    pRsp->status = rsp_status;

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}

#if defined(CONFIG_AIR_SW_KEY_DEBOUNCE)
void hid_race_ms_set_sw_debounce_rsp(uint8_t status)
{
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;
    
    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_SET_SW_DEBOUNCE,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_ms_set_sw_debounce_rsp race_pack fail");
        return;
    }

    pRsp->status = status; 

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}

void hid_race_ms_get_sw_debounce_rsp(uint8_t *deb_setting)
{
    typedef struct {
        uint8_t status;
        T_DEBOUNCE_PARA_S settings;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;
    
    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_GET_SW_DEBOUNCE,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_ms_get_sw_debounce_rsp race_pack fail");
        return;
    }
    
    pRsp->status = RACE_ERRCODE_SUCCESS; 
    memcpy((uint8_t *)&pRsp->settings, deb_setting, sizeof(T_DEBOUNCE_PARA_S));

    RACE_DBG_LOGI(thisMOD,"hid_race_ms_get_sw_debounce_rsp wired = %d 2.4G = %d, BT = %d", 
                    pRsp->settings.step_wired, pRsp->settings.step_2_4g, pRsp->settings.step_bt);

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}
#endif

#if defined(CONFIG_AIR_REMAP_FN_KEY)
void hid_race_ms_set_remap_fn_key_rsp(uint8_t status)
{
    typedef struct {
        uint8_t status;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;
    
    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_SET_REMAP_FN_KEY,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_ms_set_remap_fn_key_rsp race_pack fail");
        return;
    }

    pRsp->status = status; 

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}

void hid_race_ms_get_remap_fn_key_rsp(uint8_t fn_key)
{
    typedef struct {
        uint8_t status;
        uint8_t fn_key;
    } PACKED HID_RACE_RSP_S;

    int32_t race_ret = RACE_ERRCODE_FAIL;
    
    /* send response packet*/
    HID_RACE_RSP_S *pRsp = RACE_ClaimPacket(RACE_TYPE_RESPONSE,
                                            RACE_VENDOR_GET_REMAP_FN_KEY,
                                            sizeof(HID_RACE_RSP_S),
                                            race_cmd_cid);
    if (pRsp == NULL) {
        RACE_DBG_LOGI(thisMOD, "hid_race_ms_get_remap_fn_key_rsp race_pack fail");
        return;
    }

    pRsp->fn_key = fn_key;
    pRsp->status = RACE_ERRCODE_SUCCESS; 

    RACE_DBG_LOGI(thisMOD,"hid_race_ms_get_remap_fn_key_rsp fn_key = %x", fn_key);

    race_ret = race_flush_packet((uint8_t *)pRsp, race_cmd_cid);
    if (race_ret != RACE_ERRCODE_SUCCESS) {
        RACE_FreePacket((void *)pRsp);
    }
}
#endif
#endif
