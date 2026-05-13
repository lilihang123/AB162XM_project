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
#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#include "app_key_remap.h"
#include "af_events_declaration.h"
#include "hid_key_remap.h"
#include "hid_key_remap_game_controller.h"
#include "assert.h"
#include "key_remap_backend.h"
#include "hal_ccni.h"

#define thisMODULE key_remap
#define thisMOD    "key_remap"
LOG_MODULE_REGISTER(thisMODULE);
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
static void app_key_remap_race_cmd_rsp_announcement(T_RACE_CMD_E cmd, uint8_t result);

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
#define REMAP_DATA_ERROR    -1

T_KEY_REMAP_S key_remap_cfg;
/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
static bool app_key_remap_evt_race_cmd_req(const struct af_evt_header *evt_header)
{
    struct evt_race_cmd_req* req_event = (struct evt_race_cmd_req*)evt_header;
    APP_LOGI(thisMOD,"evt_race_cmd_req , cmd = %x", req_event->cmd);

    switch(req_event->cmd)
    {
        case RACE_CMD_SET_KEY_REMAP:
        {
            struct evt_race_cmd_rsp* rsp_event = create_evt_race_cmd_rsp();
            if (rsp_event){
                if (req_event->len >= 4) {
                    rsp_event->OTHERS.status = hid_key_remap_game_controller_set(req_event->KEY_REMAP.remap_key_id, req_event->KEY_REMAP.remap_key_type, req_event->KEY_REMAP.remap_setting, req_event->len-4);
                }
                rsp_event->cmd = RACE_CMD_SET_KEY_REMAP;
                AF_EVT_SUBMIT(rsp_event);
            }
        }
        break;

        case RACE_CMD_GET_KEY_REMAP:
        {
            uint16_t remap_len;
            key_remap_cfg.setting = (uint8_t *)k_malloc(KEY_REMAP_MACRO_MAX_LEN);
            if(key_remap_cfg.setting)
            {
                remap_len = hid_key_remap_game_controller_get(req_event->KEY_REMAP.remap_key_id, &key_remap_cfg.key_type, key_remap_cfg.setting);
                struct evt_race_cmd_rsp* rsp_event = create_evt_race_cmd_rsp_ex(remap_len);
                if (rsp_event){
                    rsp_event->KEY_REMAP.remap_key_id = req_event->KEY_REMAP.remap_key_id;
                    rsp_event->KEY_REMAP.remap_key_type = key_remap_cfg.key_type;
                    memcpy(&rsp_event->KEY_REMAP.remap_setting, key_remap_cfg.setting, remap_len);
                    rsp_event->KEY_REMAP.remap_len = remap_len;
                    rsp_event->cmd = RACE_CMD_GET_KEY_REMAP;
                    AF_EVT_SUBMIT(rsp_event);
                }
                k_free(key_remap_cfg.setting);
                key_remap_cfg.setting = NULL;
            }
            else
            {
                APP_LOGI(thisMOD, "key_remap_cfg.setting is NULL");
            }
        }
        break;

        case RACE_CMD_DELETE_MACRO:
        {
            uint8_t status = hid_kr_game_controller_delete_macro(req_event->KEY_REMAP.macro_name, req_event->len);
            app_key_remap_race_cmd_rsp_announcement(RACE_CMD_DELETE_MACRO, status);
        }
        break;

        case RACE_CMD_SET_PROFILE:
        {
            hid_key_remap_game_controller_reload(req_event->PROFILE.id, false);
            app_key_remap_race_cmd_rsp_announcement(RACE_CMD_SET_PROFILE, 0);
        }
        break;

        case RACE_CMD_SET_RESTORE:
        {
            hid_key_remap_game_controller_reload(0, true);
            app_key_remap_race_cmd_rsp_announcement(RACE_CMD_SET_RESTORE, 0);
        }
        break;

        case RACE_CMD_SET_LT_RT_THRESHOLD:
        {
            uint8_t ret = hid_kr_gc_remap_linear_threshold_set(req_event->LT_RT_REMAP.threshold);
            app_key_remap_race_cmd_rsp_announcement(RACE_CMD_SET_LT_RT_THRESHOLD, ret);
        }
        break;

        case RACE_CMD_GET_LT_RT_THRESHOLD:
        {
            struct evt_race_cmd_rsp* rsp_event = create_evt_race_cmd_rsp();
            if (rsp_event){
                rsp_event->cmd = RACE_CMD_GET_LT_RT_THRESHOLD;
                rsp_event->LT_RT_REMAP.threshold = hid_kr_gc_remap_linear_threshold_get();
                AF_EVT_SUBMIT(rsp_event);
            }
        }
        break;

        default:
        break;
    }

    if((req_event->cmd != RACE_CMD_GET_KEY_REMAP) && (req_event->cmd != RACE_CMD_GET_LT_RT_THRESHOLD))
    {
        key_remap_backend_setting();
    }
    return AF_TRAVERSE_NEXT;
}

static bool app_key_remap_evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state* event = (struct evt_app_state*)evt_header;
    APP_LOGI(thisMOD,"app_key_remap__evt_app_state event->app_state = 0x%x " , event->app_state );

    switch(event->app_state)
    {
        case APP_STATE_DISCONNECTED:
        {
            key_remap_backend_deinit();
        }
        break;

        case APP_STATE_CONNECT_PREPARING:
        {
            key_remap_backend_init();
        }
        break;

        default:
        break;
    }

    return AF_TRAVERSE_NEXT;
}
/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static void app_key_remap_race_cmd_rsp_announcement(T_RACE_CMD_E cmd, uint8_t result)
{
    APP_LOGI(thisMOD,"app_key_remap_race_cmd_rsp_announcement , result = %d", result);
    struct evt_race_cmd_rsp* event = create_evt_race_cmd_rsp();
    if (event){
        event->cmd = cmd;
        event->OTHERS.status = result;
        AF_EVT_SUBMIT(event);
    }
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
uint8_t app_key_remap_init(uint8_t profile_idx)
{
    hid_key_remap_init(profile_idx);
    return true; 
}

/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_race_cmd_req, app_key_remap_evt_race_cmd_req);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_app_state, app_key_remap_evt_app_state);
/*=============================================================================*/
#endif

