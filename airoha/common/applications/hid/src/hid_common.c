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

#if defined(AIR_HID_COMMON_MEMORY)

/* Includes ------------------------------------------------------------------*/
#include "hid_common.h"
#include "hal_cross_core_config.h"
#include "assert.h"
#include "hal_nvic.h"

/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/

hid_common_info *hid_common = (hid_common_info*)CROSS_CORE_MEM_VARIABLE(hid_common_para);

/* Private functions ---------------------------------------------------------*/
/* Public functions ---------------------------------------------------------*/
void hid_common_set_app_feature(uint8_t feature_id)
{
    hid_common->app.features |= (0x01 << feature_id);
}

void hid_common_clear_app_feature(uint8_t feature_id)
{
    hid_common->app.features &= (~(0x01 << feature_id));
}


void hid_common_set_app_para(uint8_t para_type, uint8_t* data, uint8_t length)
{
    switch(para_type)
    {
        case PARA_TYPE_RR_IDX:
        {
            if (length == sizeof(T_HID_REPORT_RATE_VAL_S)) {
                memcpy(&hid_common->app.rr, &data[0], length);
            }
        }
        break;

        case PARA_TYPE_RISCV_TRIGGER_TIME:
        {
            size_t max_len = sizeof(hid_common->app.riscv_trigger_time);
            if (length > max_len) length = max_len;
            memcpy(hid_common->app.riscv_trigger_time, data, length);
        }
        break;

    #if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
        case RAPA_TYPE_KEY_REMAP_ENABLE:
        {
            size_t max_len = sizeof(hid_common->app.key_remap_enable);
            if (length > max_len) length = max_len;
            memcpy(&hid_common->app.key_remap_enable, &data[0], length);
        }
        break;

        #if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
        case RAPA_TYPE_KEY_NOT_REMAP_DISABLE:
        {
            size_t max_len = sizeof(hid_common->app.key_not_remap_disable);
            if (length > max_len) length = max_len;
            memcpy(&hid_common->app.key_not_remap_disable, &data[0], length);
        }
        break;
        #elif defined(AIR_PRODUCT_TYPE_MOUSE)
        case RAPA_TYPE_REMAP_FN_KEY:
        {
            hid_common->app.key_remap_fn_key = data[0];
        }
        break;
        #endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */
    #endif /* AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */

    #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_PRODUCT_TYPE_MOUSE)
        case PARA_TYPE_DEBOUNCE_CONFIG:
        {
            size_t max_len = sizeof(hid_common->app.deb);
            if (length > max_len) length = max_len;
            memcpy(&hid_common->app.deb, data, length);
        }
        break;



        case PARA_TYPE_IRPT_CTRL:
        {
            hid_common->app.irpt_ctrl.id = data[0];
            hid_common->app.irpt_ctrl.para = data[1];
        }
        break;

        case PARA_TYPE_SCROLL_CTRL:
        {
            hid_common->app.scroll_ctrl.id = data[0];
            hid_common->app.scroll_ctrl.para = data[1];
        }
        break;
    #endif

        default:
        break;
    }
}

uint32_t hid_common_set_hid_para(uint8_t para_type, uint8_t* data, uint8_t length)
{
    uint32_t ret = 0;
    switch(para_type)
    {
        case RAPA_TYPE_ACL_RESPONSE_VIA_HID_REPORT:
        {
            #if defined(CONFIG_AIR_ACL_PACKET_VIA_HID_REPORT) || defined(AIR_ACL_PACKET_VIA_HID_REPORT)
            if (data && (length == sizeof(T_ACL_PKT_BUFFER_S))){
                return acl_pkt_add_item((T_ACL_PKT_BUFFER_S *) data);
            }
            #endif
        }
        break;

        default:
        break;
    }

    return ret;
}

void hid_common_set_hid_exp_flag(uint8_t flag_id)
{
    hid_common->hid.flags |= (0x01 << flag_id);
}

void hid_common_clear_hid_exp_flag(uint8_t flag_id)
{
    hid_common->hid.flags &= (~(0x01 << flag_id));
}

void hid_common_set_dongle_scenario(uint32_t dongle_scenario)
{
    hid_common->hid.dongle_scenario = dongle_scenario;
}

void hid_common_set_hid_exp_features(uint32_t hid_exp_features)
{
    hid_common->hid.features = hid_exp_features;
}

void hid_common_get_hid_exp_features(uint32_t *hid_exp_features)
{
    if (hid_exp_features){
        *hid_exp_features = hid_common->hid.features;
    }
}


uint32_t hid_common_get_dongle_scenario()
{
    return hid_common->hid.dongle_scenario;
}

void hid_common_sync_debug(T_COMMON_LA_DBG_S *debug)
{
    memcpy((uint8_t*)debug, (uint8_t*)&hid_common->dbg, sizeof(T_COMMON_LA_DBG_S));
}

#if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_PRODUCT_TYPE_MOUSE)
void hid_common_set_combo_key(const T_AIR_COMBO_KEY_S *combo_key_list, uint32_t combo_key_list_size, uint32_t hold_timeout)
{
    hid_common->app.combo_key_list = combo_key_list;
    hid_common->app.combo_key_list_size = combo_key_list_size;
    hid_common->app.hold_timeout = hold_timeout;
}

void hid_common_get_combo_key_list(T_AIR_COMBO_KEY_S **combo_key_list, uint32_t *combo_key_list_size, uint32_t *hold_timeout)
{
    *combo_key_list = (T_AIR_COMBO_KEY_S*)hid_common->app.combo_key_list;
    *combo_key_list_size = hid_common->app.combo_key_list_size;
    *hold_timeout = hid_common->app.hold_timeout;
}
#endif

#if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
void hid_common_set_key_remap_data(T_HID_KEY_REMAP_S *mapped_data, uint8_t key_id)
{
    memcpy(&hid_common->mapped_data[key_id], &mapped_data[0], sizeof(T_HID_KEY_REMAP_S));
}

void hid_common_get_backend_key_remap_data(T_HID_KEY_REMAP_BACKEND_S *mapped_data, uint8_t key_id)
{
    mapped_data->status = hid_common->mapped_data[key_id].status;
    mapped_data->play_mode = hid_common->mapped_data[key_id].play_mode;
    mapped_data->repeat_times = hid_common->mapped_data[key_id].repeat_times;
    mapped_data->macro = hid_common->mapped_data[key_id].macro[0];
    mapped_data->keycode = hid_common->mapped_data[key_id].keycode[0];
}

void hid_common_get_frontend_key_remap_data(T_HID_KEY_REMAP_FRONTEND_S *mapped_data, uint8_t key_id)
{
    mapped_data->status = hid_common->mapped_data[key_id].status;
    mapped_data->item = hid_common->mapped_data[key_id].item;
}

void hid_common_clear_key_remap_data(uint8_t key_id)
{
    memset(&hid_common->mapped_data[key_id], 0, sizeof(T_HID_KEY_REMAP_S));
}

void hid_common_clear_all_key_remap_data()
{
    memset(hid_common->mapped_data, 0, sizeof(T_HID_KEY_REMAP_S) * 5);
}
#endif /* AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */
#endif /* AIR_HID_COMMON_MEMORY */
