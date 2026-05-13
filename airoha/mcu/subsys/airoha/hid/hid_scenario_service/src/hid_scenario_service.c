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

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <hid_scenario_service.h>
#include <hid_scenario_service_internal.h>
#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
#include <hid_scenario_BT_mode.h>
#endif
#include <hid_scenario_gaming_mode.h>
#include <hid_scenario_USB_mode.h>
#include <hid_scenario_report_rate.h>
#include "hid_scenario_adv.h"
#include "hid_scenario_clock.h"
#include "hid_common.h"

#define thisMODULE  scenario
#define thisMOD    "scenario"

LOG_MODULE_REGISTER(thisMODULE);


/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
hid_scenario_callback hid_scenario_cb = NULL;
uint8_t hid_scenario = HID_SCENARIO_NONE;
/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/


/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/


/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
bool hid_scenario_nvkey_read_data(uint16_t nvkey_id, uint8_t* p_dest, uint8_t length)
{
    nvkey_status_t nvkey_ret;
    uint32_t nvkey_size = length;

    nvkey_ret = nvkey_read_data(nvkey_id, p_dest, &nvkey_size);
    DBG_LOGI(thisMOD,"hid_scenario_nvkey_read_data, nvkey_ret = %d nvkey_id = %x , nvkey = 0x%X, length = %d ", nvkey_ret , nvkey_id, nvkey_size, length);

    if((nvkey_ret == NVKEY_STATUS_OK) && (nvkey_size == length)){
        DBG_LOGI(thisMOD,"app_nvkey_read_data nvkey_id = %x ok ", nvkey_id);
        return true;
    }

    return false;
}

 #if !defined(AIR_USING_DEFAULT_RISCV_TRIGGER_TIME)
static bool hid_scenario_features_init(uint16_t* riscv_trigger_time)
{
    DBG_LOGI(thisMOD,"hid_scenario_features_init");
    uint8_t ret = hid_scenario_nvkey_read_data(NVID_HID_EXPRESS_FEATURES, (uint8_t*)riscv_trigger_time, sizeof(uint16_t) * REPORT_RATE_NUM);

    if (ret){
        DBG_LOGI(thisMOD,"hid_scenario_features_init, risc-v trigger time[125~8K] = %03d-%03d-%03d  %03d-%03d-%03d-%03d  ret = %d "
            , riscv_trigger_time[0]
            , riscv_trigger_time[1]
            , riscv_trigger_time[2]
            , riscv_trigger_time[3]
            , riscv_trigger_time[4]
            , riscv_trigger_time[5]
            , riscv_trigger_time[6]
            , ret
        );

        return true;
    }

    return false;
}
#endif

uint8_t hid_scenario_init(hid_scenario_callback cb, uint8_t profile_idx)
{
    DBG_LOGI(thisMOD, "hid_scenario_init  cb = 0x%x ", cb);

    if (cb)
    {
        bool ret = true;
        hid_scenario_cb = cb;

        #if defined(AIR_USING_DEFAULT_RISCV_TRIGGER_TIME)
        uint16_t* riscv_trigger_time = NULL;
        #else
        uint16_t riscv_trigger_time[REPORT_RATE_NUM];             /** riscv trigger time for different report rate*/
        ret = hid_scenario_features_init(riscv_trigger_time);
        #endif

        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        hid_scenario_bt_mode_init();
        #endif

        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_GAMING_MODE)
        if (ret) {
            hid_scenario_gaming_mode_init(riscv_trigger_time);
        }
        else {
            hid_scenario_gaming_mode_init(NULL);
        }
        #endif

        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
        hid_scenario_usb_mode_init();
        #endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/

        hid_scenario_rr_init(profile_idx);
        return 0;
    }



    return 1;
}

uint8_t hid_scenario_open(uint8_t scenario, uint32_t link_idx, T_HID_SCENARIO_OPEN_TYPE_E type, uint16_t reconnect_time)
{
    DBG_LOGI(thisMOD, "hid_scenario_open scenario = %d, link_idx = %d, open_type: %d", scenario, link_idx, type);
    hid_scenario = scenario;
    hid_scenario_clk_switch(scenario);
    switch(scenario)
    {
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        case HID_SCENARIO_BT_MODE:
        {
            return hid_scenario_bt_mode_open(link_idx, type);
        }
        break;
        #endif
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_GAMING_MODE)
        case HID_SCENARIO_GAMING_MODE:
        {
            return hid_scenario_gaming_mode_open(link_idx, type, reconnect_time);
        }
        break;
        #endif
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
        case HID_SCENARIO_USB_MODE:
        {
            return hid_scenario_usb_mode_open(link_idx, type);
        }
        break;
        #endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/
    }

    return 0;
}

uint8_t hid_scenario_start(uint8_t scenario, uint32_t link_idx, void* parameter)
{
    DBG_LOGI(thisMOD, "hid_scenario_start link_idx = %d", link_idx);

    switch(scenario)
    {
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        case HID_SCENARIO_BT_MODE:
        {
            return hid_scenario_bt_mode_start(link_idx, parameter);
        }
        break;
        #endif
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_GAMING_MODE)
        case HID_SCENARIO_GAMING_MODE:
        {
            return hid_scenario_gaming_mode_start(link_idx, parameter);
        }
        break;
        #endif
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
        case HID_SCENARIO_USB_MODE:
        {
            return hid_scenario_usb_mode_start(link_idx, parameter);
        }
        break;
        #endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/
    }

    return 0;
}

uint8_t hid_scenario_stop(uint8_t scenario, uint8_t parameter)
{
    DBG_LOGI(thisMOD, "hid_scenario_stop");

    switch(scenario)
    {
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        case HID_SCENARIO_BT_MODE:
        {
            return hid_scenario_bt_mode_stop(parameter);
        }
        break;
        #endif
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_GAMING_MODE)
        case HID_SCENARIO_GAMING_MODE:
        {
            return hid_scenario_gaming_mode_stop(parameter);
        }
        break;
        #endif
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
        case HID_SCENARIO_USB_MODE:
        {
            return hid_scenario_usb_mode_stop(parameter);
        }
        break;
        #endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/
    }

    return 0;
}

uint8_t hid_scenario_close(uint8_t scenario, uint8_t parameter)
{
    DBG_LOGI(thisMOD, "hid_scenario_close");

    switch(scenario)
    {
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        case HID_SCENARIO_BT_MODE:
        {
            return hid_scenario_bt_mode_close(parameter);
        }
        break;
        #endif
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_GAMING_MODE)
        case HID_SCENARIO_GAMING_MODE:
        {
            return hid_scenario_gaming_mode_close(parameter);
        }
        break;
        #endif
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
        case HID_SCENARIO_USB_MODE:
        {
            return hid_scenario_usb_mode_close(parameter);
        }
        break;
        #endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/
    }

    return 0;
}

uint8_t hid_scenario_general_config(T_HID_SCENARIO_CONFIG_PARA_S* config)
{
    DBG_LOGI(thisMOD, "hid_scenario_general_config");

    switch(config->cfg_type)
    {
        case SECNARIO_SRV_CONFIG_BT_TRIGGER:
        {
            T_BT_TRIGGER_TYPE_S *cfg = (T_BT_TRIGGER_TYPE_S*)config->value;
            DBG_LOGI(thisMOD, "hid_scenario_set_peripheral_trigger hdl = 0x%x, TriggerType = %d, ActionMode = %d",  cfg->connection_handle, cfg->TriggerType,  cfg->ActionMode );
            hid_vendor_set_peripheral_trigger(cfg);
        }
        break;

        default:{
            return 1;
            break;
        }
    }

    return 0;
}


uint8_t hid_scenario_config(uint8_t scenario, T_HID_SCENARIO_CONFIG_PARA_S* config)
{
    DBG_LOGI(thisMOD, "hid_scenario_config");

    switch(scenario)
    {
        case HID_SCENARIO_NONE:
        {
            hid_scenario_general_config(config);
        }
        break;

        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        case HID_SCENARIO_BT_MODE:
        {
            return hid_scenario_bt_mode_config(config);
        }
        break;
        #endif
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_GAMING_MODE)
        case HID_SCENARIO_GAMING_MODE:
        {
            return hid_scenario_gaming_mode_config(config);
        }
        break;
        #endif
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
        case HID_SCENARIO_USB_MODE:
        {
            return hid_scenario_usb_mode_config(config);
        }
        break;
        #endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/
    }

    return 0;
}

void hid_scenario_send_state_update_notification(uint8_t new_state, uint8_t reason)
{
    T_SCENARIO_SERVICE_STATE_UPDATE_S para;

    para.state = new_state;
    para.reason = reason;
    hid_scenario_send_notification(SS_EVT_STATE_UPDATE, (uint8_t*)&para, sizeof(para));
}

void hid_scenario_send_notification(uint8_t event, uint8_t* param, uint8_t param_len)
{
    if (hid_scenario_cb){
        hid_scenario_cb(event, param, param_len);
    }
}

uint8_t hid_scenario_get()
{
    return hid_scenario;
}

uint8_t hid_scenario_get_state()
{
    switch(hid_scenario)
    {
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        case HID_SCENARIO_BT_MODE:
            return hid_scenario_bt_mode__get_state();
        #endif
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_GAMING_MODE)
        case HID_SCENARIO_GAMING_MODE:
            return hid_scenario_gaming_mode__get_state();
        #endif
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
        case HID_SCENARIO_USB_MODE:
            return hid_scenario_usb_mode__get_state();
        #endif
        default:
            return MODE_NONE;
    }
}

bool hid_scenario__bt_trigger_peripheral_hw(uint32_t enable)
{
    switch(hid_scenario)
    {
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        case HID_SCENARIO_BT_MODE:
            return hid_scenario_bt_mode__bt_trigger_peripheral_hw(enable);
        #endif
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_GAMING_MODE)
        case HID_SCENARIO_GAMING_MODE:
            return hid_scenario_gaming_mode__bt_trigger_peripheral_hw(enable);
        #endif
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
        case HID_SCENARIO_USB_MODE:
        #endif
        default:
            return -1;
    }
}