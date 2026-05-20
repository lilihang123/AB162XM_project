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
#include "hid_key_remap_mouse.h"
#include "app_scenario.h"
#include "assert.h"
#include "app_button.h"

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
                    rsp_event->OTHERS.status = hid_key_remap_mouse_set(req_event->KEY_REMAP.remap_key_id, req_event->KEY_REMAP.remap_key_type, req_event->KEY_REMAP.remap_setting, req_event->len-4);
                }
                rsp_event->cmd = RACE_CMD_SET_KEY_REMAP;
                AF_EVT_SUBMIT(rsp_event);
            }
        }
        break;

        case RACE_CMD_GET_KEY_REMAP:
        {
            uint16_t remap_len, report_rate = app_scenario_get_report_rate();
            key_remap_cfg.setting = (uint8_t *)k_malloc(KEY_REMAP_MACRO_MAX_LEN);
            if(key_remap_cfg.setting)
            {
                remap_len = hid_key_remap_mouse_get(req_event->KEY_REMAP.remap_key_id, &key_remap_cfg.key_type, key_remap_cfg.setting, report_rate);
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

        case RACE_CMD_SET_PROFILE:
        {
            hid_key_remap_mouse_reload(req_event->PROFILE.id, false);
            app_key_remap_race_cmd_rsp_announcement(RACE_CMD_SET_PROFILE, 0);
        }
        break;

        case RACE_CMD_SET_RESTORE:
        {
            hid_key_remap_mouse_reload(0, true);
            app_key_remap_race_cmd_rsp_announcement(RACE_CMD_SET_RESTORE, 0);
        }
        break;

        case RACE_CMD_DELETE_MACRO:
        {
            uint8_t status = hid_key_remap_mouse_delete_macro(req_event->KEY_REMAP.macro_name, req_event->len);
            app_key_remap_race_cmd_rsp_announcement(RACE_CMD_DELETE_MACRO, status);
        }
        break;

        #if defined (CONFIG_AIR_REMAP_FN_KEY)
        case RACE_CMD_SET_REMAP_FN_KEY:
        {
            uint8_t status = hid_key_remap_mouse_set_fn_key(req_event->REMAP_FN_KEY.key);
            app_key_remap_race_cmd_rsp_announcement(RACE_CMD_SET_REMAP_FN_KEY, status);
        }
        break;

        case RACE_CMD_GET_REMAP_FN_KEY:
        {
            uint8_t key = hid_key_remap_mouse_get_fn_key();
            struct evt_race_cmd_rsp* event = create_evt_race_cmd_rsp();
            if (event){
                event->cmd = RACE_CMD_GET_REMAP_FN_KEY;
                event->REMAP_FN_KEY.key = key;
                AF_EVT_SUBMIT(event);
            }
        }
        break; 
        #endif
        
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

uint8_t app_key_remap_check(uint8_t key_idx)
{
    uint8_t type = hid_key_remap_mouse_get_type(key_idx);

    switch(type)
    {
        case REMAP_TO_LEFT_KEY:           return M_KEY_L;
        case REMAP_TO_RIGHT_KEY:          return M_KEY_R;
        case REMAP_TO_MIDDLE_KEY:         return M_KEY_M;
        case REMAP_TO_FOURTH_KEY:         return M_KEY_NK;
        case REMAP_TO_FIFTH_KEY:          return M_KEY_PK;
        case REMAP_TO_REPORT_RATE_SWITCH: return M_KEY_RR;
        #ifdef M_KEY_DPI
        case REMAP_TO_DPI_CONTROL:        return M_KEY_DPI;
        #endif
        case REMAP_TO_PAIRING_KEY:        return M_KEY_PAIRING;
        default:                          return 0;
    }
}

/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_race_cmd_req, app_key_remap_evt_race_cmd_req);
/*=============================================================================*/
#endif

