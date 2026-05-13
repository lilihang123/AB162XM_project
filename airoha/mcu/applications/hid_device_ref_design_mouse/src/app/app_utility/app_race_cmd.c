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


#include <stdint.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>

#include "app_race_cmd.h"
#include "hid_race_cmd.h"
#include "hid_race_cmd_mouse.h"
#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#include "app_key_remap.h"
#endif
#include "app_rgb.h"

#define thisMODULE app_race_cmd
#define thisMOD    "app_race_cmd"
LOG_MODULE_REGISTER(thisMODULE);
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/

#define RACE_CMD_SET_SUCCESS 0
#define SETTING_COUNT_MAX 5
uint8_t setting_cnt = 0;

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/
static void app_race_cmd_req_handler(uint16_t race_cmd_id, uint8_t *para, uint16_t length)
{
    APP_LOGI(thisMOD, "app_race_cmd_req_handler race_cmd_id = %x", race_cmd_id);

    #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    if(race_cmd_id == RACE_CMD_SET_KEY_REMAP)
    {
        if(length < 4)
        {
            APP_LOGI(thisMOD, "Invalid length for RACE_CMD_SET_KEY_REMAP");
            return;
        }
        uint16_t setting_len = length - 4;
        struct evt_race_cmd_req* event = create_evt_race_cmd_req_ex(setting_len);
        if (event){
            event->cmd = race_cmd_id;
            event->len = length;
            event->KEY_REMAP.remap_key_id = para[0];
            event->KEY_REMAP.remap_key_type = para[1];
            if(setting_len)
            {
                memcpy(event->KEY_REMAP.remap_setting, para + 2, setting_len);
            }
            AF_EVT_SUBMIT(event);
        }
    }
    else
    #endif
    #if defined(CONFIG_AIR_MIDDLE_RGB)
    if(race_cmd_id == RACE_CMD_SET_RGB)
    {
        uint8_t basic_len = 6;
        uint16_t max_length = (CONFIG_AIR_RGB_NUM*3 + basic_len);
        if((length < basic_len) && (length > max_length)){
            return;
        }
        int16_t race_color_len = length - basic_len;
        uint8_t rgb_count = para[3];
        uint16_t rgb_color_len = rgb_count * 3;
        if(race_color_len == 0)
        {
            struct evt_race_cmd_req* event = create_evt_race_cmd_req();
            event->cmd = race_cmd_id;
            event->len = length;
            event->RGB.rgb_setting = para[0];
            event->RGB.rgb_num = para[1];
            event->RGB.rgb_interval = para[2];
            event->RGB.rgb_count = rgb_count;
            AF_EVT_SUBMIT(event);
            // APP_LOGI(thisMOD,"app_race_cmd_evt, RACE_CMD_SET_RGB, setting = 0x%X, num = 0x%X, count = 0x%X, interval = 0x%X",
            //                                     event->RGB.rgb_setting,
            //                                     event->RGB.rgb_num,
            //                                     event->RGB.rgb_count,
            //                                     event->RGB.rgb_interval);
        }
        else if(race_color_len == rgb_color_len)
        {
            struct evt_race_cmd_req* event = create_evt_race_cmd_req_ex(race_color_len);
            event->cmd = race_cmd_id;
            event->len = length;
            event->RGB.rgb_setting = para[0];
            event->RGB.rgb_num = para[1];
            event->RGB.rgb_interval = para[2];
            event->RGB.rgb_count = rgb_count;
            memcpy(event->RGB.rgb_color, para + 4, rgb_color_len);
            AF_EVT_SUBMIT(event);
            // APP_LOGI(thisMOD,"app_race_cmd_evt, RACE_CMD_SET_RGB, setting = 0x%X, num = 0x%X, count = 0x%X, interval = 0x%X",
            //                                         event->RGB.rgb_setting,
            //                                         event->RGB.rgb_num,
            //                                         event->RGB.rgb_count,
            //                                         event->RGB.rgb_interval);
        }
        else
        {
            APP_LOGI(thisMOD,"app_race_cmd_evt, RACE_CMD_SET_RGB, rgb_color_len = %d, race_color_len = %d", rgb_color_len, race_color_len);
            return;
        }
    }
    else
    #endif /* CONFIG_AIR_MIDDLE_RGB */
    {
        struct evt_race_cmd_req* event = create_evt_race_cmd_req();
        // APP_LOGI(thisMOD, "[ALLOC]request, 0, event = %x, size = %d", event, sizeof(struct evt_race_cmd_req));

        if (event){
            event->cmd = race_cmd_id;
            event->len = length;

            switch(race_cmd_id)
            {
                case RACE_CMD_SET_DEBOUNCE:
                {
                    event->DEBOUNCE.time = *para;
                }
                break;

                #if defined(CONFIG_AIR_SW_KEY_DEBOUNCE)
                case RACE_CMD_SET_SW_DEBOUNCE:
                {
                    memcpy(&event->SW_DEBOUNCE.settings, para, sizeof(T_DEBOUNCE_PARA_S));
                }
                break;
                #endif

                case RACE_CMD_SET_REPORT_RATE:
                {
                    event->RR.value = *(uint16_t*)para;
                }
                break;

                case RACE_CMD_SET_SENSOR_LOD:
                case RACE_CMD_SET_SENSOR_MOTION_SYNC:
                case RACE_CMD_SET_SENSOR_ANGLE_SNAP:
                case RACE_CMD_SET_SENSOR_RIPPLE_CTRL:
                case RACE_CMD_SET_DPI_LOOP_RANGE:
                case RACE_CMD_SET_DPI_CURRENT:
                {
                    event->SENSOR.value = *para;
                }
                break;

                case RACE_CMD_SET_DPI:
                {
                    event->DPI.dpi_idx = *para;
                    #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
                    event->DPI.x_dpi_value = *(uint16_t *)(para + 1);
                    event->DPI.y_dpi_value = *(uint16_t *)(para + 3);
                    #else
                    event->DPI.dpi_value = *(uint16_t *)(para + 1);
                    #endif
                }
                break;

                case RACE_CMD_SET_PROFILE:
                {
                    event->PROFILE.id = *para;
                }
                break;

                #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
                case RACE_CMD_GET_KEY_REMAP:
                {
                    event->KEY_REMAP.remap_key_id = *para;
                }
                break;

                case RACE_CMD_DELETE_MACRO:
                {
                    if(event->len <= sizeof(event->KEY_REMAP.macro_name))
                    {
                        memcpy(&event->KEY_REMAP.macro_name, para, event->len);
                    }
                }
                break;
                #endif

                case RACE_CMD_SET_UNIAA:
                {
                    event->UNIAA.pair_device_type = para[0];
                    event->UNIAA.addr_type = para[1];
                    memcpy(event->UNIAA.pair_address, para + ADDR_OFFSET+1, 6);  //+2
                    memcpy(event->UNIAA.uni_aa, para + UNI_AA_OFFSET, 4);  //+8
                    memcpy(event->UNIAA.ltk, para + LTK_OFFSET, 16);  //+12
                    memcpy(event->UNIAA.skd, para + SKD_OFFSET, 16);  //+28
                    memcpy(event->UNIAA.iv, para + IV_OFFSET, 8);  //+44

                    APP_LOGI(thisMOD, "app_race_cmd_evt, RACE_CMD_SET_UNIAA, device_type:0x%X, addr_type:0x%X, addr:0x%02X-%02X-%02X-%02X-%02X-%02X, uniaa:0x%02X-%02X-%02X-%02X",
                                event->UNIAA.pair_device_type, event->UNIAA.addr_type, event->UNIAA.pair_address[0], event->UNIAA.pair_address[1],
                                event->UNIAA.pair_address[2], event->UNIAA.pair_address[3], event->UNIAA.pair_address[4], event->UNIAA.pair_address[5],
                                event->UNIAA.uni_aa[0], event->UNIAA.uni_aa[1], event->UNIAA.uni_aa[2], event->UNIAA.uni_aa[3]
                            );
                    break;
                }

                case RACE_CMD_GET_UNIAA:
                {
                    event->UNIAA.pair_device_type = *para;
                    APP_LOGI(thisMOD,"app_race_cmd_evt, RACE_CMD_GET_UNIAA, device_type = 0x%X", event->UNIAA.pair_device_type);
                    break;
                }

                #if defined (CONFIG_AIR_REMAP_FN_KEY)
                case RACE_CMD_SET_REMAP_FN_KEY:
                {
                    event->REMAP_FN_KEY.key = *para;
                }
                break;
                #endif

                case RACE_CMD_ENABLE_KEY_EVENT:
                {
                    event->ENABLE_KEY_EVNET.event_id = *para;
                }
                break;

                default:{
                    break;
                }
            }
            AF_EVT_SUBMIT(event);
        }
    }
}

/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static bool app_race_cmd_evt_rsp(const struct af_evt_header *evt_header)
{
    struct evt_race_cmd_rsp* event = (struct evt_race_cmd_rsp*)evt_header;
    APP_LOGI(thisMOD,"app_race_cmd_evt_rsp , cmd = %x", event->cmd);

    switch(event->cmd)
    {
        case RACE_CMD_SET_DEBOUNCE:
        {
            hid_race_set_debounce_rsp(event->DEBOUNCE.result);
        }
        break;

        case RACE_CMD_GET_DEBOUNCE:
        {
            hid_race_get_debounce_rsp(event->DEBOUNCE.result);
        }
        break;

        #if defined(CONFIG_AIR_SW_KEY_DEBOUNCE)
        case RACE_CMD_SET_SW_DEBOUNCE:
        {
            hid_race_ms_set_sw_debounce_rsp(event->OTHERS.status);
        }
        break;

        case RACE_CMD_GET_SW_DEBOUNCE:
        {
            hid_race_ms_get_sw_debounce_rsp((uint8_t *)&event->SW_DEBOUNCE.settings);
        }
        break;
        #endif

        case RACE_CMD_SET_REPORT_RATE:
        {
            hid_race_set_report_rate_rsp(event->RR.result);
        }
        break;

        case RACE_CMD_GET_REPORT_RATE:
        {
            hid_race_get_report_rate_rsp(event->RR.result);
        }
        break;

        case RACE_CMD_SET_SENSOR_LOD:
        {
            hid_race_ms_set_sensor_LOD_rsp(event->SENSOR.result);
        }
        break;

        case RACE_CMD_GET_SENSOR_LOD:
        {
            hid_race_ms_get_sensor_LOD_rsp(event->SENSOR.result);
        }
        break;

        case RACE_CMD_SET_SENSOR_MOTION_SYNC:
        {
            hid_race_ms_set_sensor_motion_sync_rsp(event->SENSOR.result);
        }
        break;

        case RACE_CMD_GET_SENSOR_MOTION_SYNC:
        {
            hid_race_ms_get_sensor_motion_sync_rsp(event->SENSOR.result);
        }
        break;

        case RACE_CMD_SET_SENSOR_ANGLE_SNAP:
        {
            hid_race_ms_set_sensor_angle_snap_rsp(event->SENSOR.result);
        }
        break;

        case RACE_CMD_GET_SENSOR_ANGLE_SNAP:
        {
            hid_race_ms_get_sensor_angle_snap_rsp(event->SENSOR.result);
        }
        break;

        case RACE_CMD_SET_SENSOR_RIPPLE_CTRL:
        {
            hid_race_ms_set_sensor_ripple_control_rsp(event->SENSOR.result);
        }
        break;

        case RACE_CMD_GET_SENSOR_RIPPLE_CTRL:
        {
            hid_race_ms_get_sensor_ripple_control_rsp(event->SENSOR.result);
        }
        break;

        case RACE_CMD_SET_DPI:
        {
            hid_race_ms_set_dpi_rsp(event->SENSOR.result);
        }
        break;

        case RACE_CMD_GET_DPI:
        {
            #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
            hid_race_ms_get_dpi_rsp(event->DPI.dpi_loop_stage_range, event->DPI.dpi_curr_idx, event->DPI.x_dpi_settings, event->DPI.y_dpi_settings);
            #else
            hid_race_ms_get_dpi_rsp(event->DPI.dpi_loop_stage_range, event->DPI.dpi_curr_idx, event->DPI.dpi_settings);
            #endif
        }
        break;

        case RACE_CMD_SET_DPI_LOOP_RANGE:
        {
            hid_race_ms_set_dpi_loop_stage_range_rsp(event->SENSOR.result);
        }
        break;

        case RACE_CMD_SET_DPI_CURRENT:
        {
            hid_race_ms_set_dpi_current_rsp(event->SENSOR.result);
        }
        break;

        case RACE_CMD_SET_PROFILE:
        {
            if(event->OTHERS.status == RACE_CMD_SET_SUCCESS)
            {
                setting_cnt++;
            }

            if(setting_cnt == SETTING_COUNT_MAX)
            {
                hid_race_set_profile_rsp(event->PROFILE.result);
                setting_cnt = 0;
            }
        }
        break;

        case RACE_CMD_GET_PROFILE:
        {
            hid_race_get_profile_rsp(event->PROFILE.result);
        }
        break;

        case RACE_CMD_SET_RESTORE:
        {
            if(event->OTHERS.status == RACE_CMD_SET_SUCCESS)
            {
                setting_cnt++;
            }

            if(setting_cnt == SETTING_COUNT_MAX)
            {
                hid_race_set_restore_rsp(event->PROFILE.result);
                setting_cnt = 0;
            }
        }
        break;

        case RACE_CMD_GET_BATTERY:
        {
            // rsp tool
            hid_race_get_battery_rsp(event->BATTERY.charging, event->BATTERY.battery);
            // req dongle
            hid_race_set_battery_req(event->BATTERY.charging, event->BATTERY.battery);
        }
        break;

        #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
        case RACE_CMD_SET_KEY_REMAP:
        {
            hid_race_set_key_remap_rsp(event->OTHERS.status);
        }
        break;

        case RACE_CMD_GET_KEY_REMAP:
        {
            hid_race_get_key_remap_rsp(event->KEY_REMAP.remap_key_id, event->KEY_REMAP.remap_key_type, event->KEY_REMAP.remap_setting, event->KEY_REMAP.remap_len);
        }
        break;

        case RACE_CMD_DELETE_MACRO:
        {
            hid_race_delete_macro_rsp(event->OTHERS.status);
        }
        break;
        #endif

        case RACE_CMD_SET_RGB:
        {
            race_errcode_enum result  = hid_race_set_rgb_rsp(event->OTHERS.status);
            if(result)
            {
                APP_LOGI(thisMOD,"[error]hid_race_set_rgb_rsp, result = %x", result);
                struct evt_race_cmd_rsp_for_rgb* rsp_evt = create_evt_race_cmd_rsp_for_rgb();

                if (rsp_evt) {
                    rsp_evt->cmd = RACE_CMD_SET_RGB;
                    rsp_evt->status = result;
                    AF_EVT_SUBMIT(rsp_evt);
                }
            }
            break;
        }
        case RACE_CMD_SET_UNIAA:
        {
            hid_race_set_uniaa_rsp(event->OTHERS.status);
            break;
        }

        #if defined (CONFIG_AIR_REMAP_FN_KEY)
        case RACE_CMD_SET_REMAP_FN_KEY:
        {
            hid_race_ms_set_remap_fn_key_rsp(event->OTHERS.status);
        }
        break;

        case RACE_CMD_GET_REMAP_FN_KEY:
        {
            hid_race_ms_get_remap_fn_key_rsp(event->REMAP_FN_KEY.key);
        }
        break;
        #endif

        case RACE_CMD_ENABLE_KEY_EVENT:
        {
            hid_race_enable_key_event_rsp(event->OTHERS.status);
        }
        break;

        case RACE_CMD_SET_DPI_VALUE:
        {
            race_errcode_enum ret = hid_race_set_dpi_value_req(event->DPI.x_dpi_value, event->DPI.y_dpi_value);
            if(ret){
                APP_LOGI(thisMOD,"[error]RACE_CMD_SET_DPI_VALUE, result = %x", ret);
            }
            break;
        }

        default:{
            break;
        }
    }
    return AF_TRAVERSE_NEXT;
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
void app_race_cmd_init(void)
{
    uint8_t ret = hid_race_cmd_init(app_race_cmd_req_handler);
    if(ret){
        APP_LOGE(thisMOD, "hid_race_cmd_init fail");
    }
}

/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_race_cmd_rsp, app_race_cmd_evt_rsp);

/*=============================================================================*/