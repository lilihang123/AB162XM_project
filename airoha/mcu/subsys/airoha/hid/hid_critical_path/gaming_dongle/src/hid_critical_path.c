/* Copyright Statement:
*
* (C) 2025 Airoha Technology Corp. All rights reserved.
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
* the License Agreement ("Permitted User"). If you are not a Permitted User,
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
/* Airoha restricted information */

#include "hid_critical_path.h"
#include <stdint.h>
#include <stddef.h>
#include "pka_porting_layer.h"
#include "hal_dvfs.h"

static void hid_cp_sw_isr_callback(void);
static void hid_cp_bt_isr_callback(uint8_t* data, uint16_t len, usb_plc_cb_param *plc_param);
static hid_critical_path_status_t hid_cp_bt_isr_callback_process(uint8_t report_id);
static void hid_cp_bt_isr_callback(uint8_t* data, uint16_t len, usb_plc_cb_param *plc_param);

ATTR_TEXT_IN_TCM static hid_critical_path_status_t hid_cp_bt_isr_callback_process(uint8_t report_id)
{
    hid_critical_path_status_t status = HID_CP_STATUS_SUCCESS;
    hid_critical_path_t *hid_cp_ms_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
#if defined(CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE)
    hid_critical_path_t *hid_cp_key_remap_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_KEY_REMAP);
#endif
#if defined(CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE)
    hid_critical_path_t *hid_cp_nkey_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_NKEY);
#endif
#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE)
    hid_critical_path_t *hid_cp_game_controller_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_GAME_CONTROLLER);
#endif
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
    // hal_gpio_set_output(HID_CP_DEBUG_GPIO_2, HAL_GPIO_DATA_HIGH);
#endif
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
    hal_gpio_set_output(HID_CP_DEBUG_GPIO_6, HAL_GPIO_DATA_HIGH);
#endif

switch(report_id) {
#if defined(CONFIG_AIR_HID_CP_PROCESS_MOUSE_ENABLE)
    case REPORT_ID_MOUSE:
    case REPORT_ID_MOUSE_16BIT:
    {
        if(hid_critical_path_get_state(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE) == HID_CP_STATE_CONNECTED){
            hid_critical_path_set_state(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE, HID_CP_STATE_DATA_SEND);
        }
        if(hid_critical_path_get_state(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE) != HID_CP_STATE_DATA_SEND){
            return HID_CP_STATUS_STATE_ERR;
        }
        status = hid_cp_ms(&hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[0], \
                        hid_cp_ms_ctx->ms_ctx.bt_hid_data.data_len, \
                        &hid_cp_ms_ctx->ms_ctx.bt_hid_plc_param);
        break;
    }
#endif
#if defined(CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE)
    case REPORT_ID_KB_STD_XY:
    case REPORT_ID_KB_CONSUMER_XY:
    case REPORT_ID_KB_STD:
    case REPORT_ID_KB_CONSUMER:
    {
        if((hid_cp_key_remap_ctx->kb_ctx.bt_hid_data.data_len > 0)){
            status = hid_cp_kbd(
                &hid_cp_key_remap_ctx->kb_ctx.bt_hid_data.data[0], \
                hid_cp_key_remap_ctx->kb_ctx.bt_hid_data.data_len, \
                &hid_cp_key_remap_ctx->kb_ctx.bt_hid_plc_param
            );
        }
        break;
    }
#endif
#if defined (CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE)
    case REPORT_ID_KEYBOARD :
    case REPORT_ID_KEYBOARD_GROUP0 :
    case REPORT_ID_KEYBOARD_GROUP1 :
    {
        if(hid_critical_path_get_state(HID_CRITICAL_PATH_DEVICE_TYPE_NKEY) == HID_CP_STATE_CONNECTED){
            hid_critical_path_set_state(HID_CRITICAL_PATH_DEVICE_TYPE_NKEY, HID_CP_STATE_DATA_SEND);
        }
        if(hid_critical_path_get_state(HID_CRITICAL_PATH_DEVICE_TYPE_NKEY) != HID_CP_STATE_DATA_SEND){
            // LOG_ERR(BT_HID_CP_TAG"hid_cp_bt_isr_callback_process, state incorrect: %d", hid_critical_path_get_state(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE));
            return HID_CP_STATUS_STATE_ERR;
        }
        /*  NKEY Process*/
        status = hid_cp_nkey(
            &hid_cp_nkey_ctx->kb_ctx.bt_hid_data.data[0], \
            hid_cp_nkey_ctx->kb_ctx.bt_hid_data.data_len, \
            &hid_cp_nkey_ctx->kb_ctx.bt_hid_plc_param);
        break;
    }
#endif
#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE)
    if((hid_cp_game_controller_ctx->gp_ctx.bt_hid_data.data_len > 0)){
        case REPORT_ID_GAME_CONTROLLER:
        case REPORT_ID_GAME_CONTROLLER_GROUP0:
        case REPORT_ID_GAME_CONTROLLER_GROUP1:
        case REPORT_ID_GAME_CONTROLLER_GROUP2:
        case REPORT_ID_GAME_CONTROLLER_ALL_IN_ONE:
        {
            status = hid_cp_game_controller(
                &hid_cp_game_controller_ctx->gp_ctx.bt_hid_data.data[0], \
                hid_cp_game_controller_ctx->gp_ctx.bt_hid_data.data_len, \
                &hid_cp_game_controller_ctx->gp_ctx.bt_hid_plc_param
            );
        break;
        }
    }
#endif /* CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE */
    default:
    {
        LOG_ERR("hid_cp_bt_isr_callback_process, error reortid: %d", report_id);
        return HID_CP_STATUS_SEND_FAIL;
    }
}

#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
    hal_gpio_set_output(HID_CP_DEBUG_GPIO_6, HAL_GPIO_DATA_LOW);
#endif
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
    // hal_gpio_set_output(HID_CP_DEBUG_GPIO_2, HAL_GPIO_DATA_LOW);
#endif
    return status;
}

ATTR_TEXT_IN_TCM void hid_cp_sw_isr_callback(void)
{
    #if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE)
    hid_cp_gp_sw_isr_callback();
    #else
    hid_cp_ms_sw_isr_callback();
    #endif


    #if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE)
    /* process custom protocol data */
    hid_critical_path_common_custom_protocol_data_process();
    #endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE */
}

/* MS HID DATA IN AIR
case1: normal
Byte[0]: Report ID
Byte[1]: KEY
Byte[2-4]: X,Y
Byte[5]: Wheel
Byte[6]: ACPAN

case2: for crc error
Byte[0]: ACPAN
Byte[1]: KEY
Byte[2-4]: X,Y
Byte[5]: Wheel
Byte[6]: Report ID
*/
ATTR_TEXT_IN_TCM static void hid_cp_bt_isr_callback(uint8_t* data, uint16_t len, usb_plc_cb_param *plc_param)
{
    hid_critical_path_status_t status = HID_CP_STATUS_SUCCESS;
    uint8_t report_id = 0;

#if defined(CONFIG_AIR_HID_CP_PROCESS_MOUSE_ENABLE)
    hid_critical_path_t *hid_cp_ms_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
#endif
#if defined(CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE)
    hid_critical_path_t *hid_cp_key_remap_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_KEY_REMAP);
#endif
#if defined(CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE)
    hid_critical_path_t *hid_cp_nkey_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_NKEY);
#endif
#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE)
    hid_critical_path_t *hid_cp_game_controller_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_GAME_CONTROLLER);
#endif

#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
    hal_gpio_set_output(HID_CP_DEBUG_GPIO_1, HAL_GPIO_DATA_HIGH);
#endif
    hid_cp_debug_paramter.total_data_count++;
#ifdef CONFIG_AIR_HID_CP_DEBUG_LOG
    hid_cp_debug_paramter.hid_data[hid_cp_debug_paramter.log_print_count].timestamp = GPT(HAL_GPT_US_PORT)->GPT_COUNT;
#endif

#if defined(CONFIG_AIR_HID_CP_PROCESS_MOUSE_ENABLE)
    memset(&hid_cp_ms_ctx->ms_ctx.bt_hid_data, 0, sizeof(hid_cp_bt_hid_data));
#endif
#if CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE
    memset(&hid_cp_key_remap_ctx->kb_ctx.bt_hid_data, 0, sizeof(hid_cp_bt_hid_data));
#endif
#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
    memset(&hid_cp_nkey_ctx->kb_ctx.bt_hid_data, 0, sizeof(hid_cp_bt_hid_data));
#endif

#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE)
    memset(&hid_cp_game_controller_ctx->gp_ctx.bt_hid_data, 0, sizeof(hid_cp_bt_hid_data));
#endif /* CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE */

    if(data) {
        if (len == 7 || len == 9 || len == 17) {
            #if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_HIX_MIXING_ENABLE)
            report_id = data[len - 1] & 0x3F;
            #else
            report_id = data[len - 1] & 0x7F;
            #endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_HIX_MIXING_ENABLE */
        } else {
            LOG_ERR("hid_cp_bt_isr_callback: Invalid data length: %d", len);
            return;
        }
    }

/* plc data is null, need to set 0 then access */
    if (plc_param->reason && data == NULL) {
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
        hal_gpio_set_output(HID_CP_DEBUG_GPIO_4, HAL_GPIO_DATA_HIGH);
#endif
        hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[0] = REPORT_ID_MOUSE;
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
        hal_gpio_set_output(HID_CP_DEBUG_GPIO_4, HAL_GPIO_DATA_LOW);
#endif
    } else {
        switch(report_id){
#if CONFIG_AIR_HID_CP_PROCESS_MOUSE_ENABLE
            case REPORT_ID_MOUSE:
            case REPORT_ID_MOUSE_16BIT:
                hid_cp_ms_ctx->ms_ctx.accumulate_flag = false;
                if (data[len-1] & 0x80) {//get accumulate_flag, the bit7 of Report id
                    hid_cp_ms_ctx->ms_ctx.accumulate_flag = true;
                }
                #if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) || defined(AIR_DONGLE_OF_KEYBOARD_M607)
                /* HID_RAW_DATA_PROCESS_METHOD_CYCLLE_1B */
                memcpy(&hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[1], data, len-1);
                hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[0] = data[len - 1];
                hid_cp_ms_ctx->ms_ctx.bt_hid_data.data_len = len;
                #else
                /* HID_RAW_DATA_PROCESS_METHOD_EXCHANGE_1B */
                memcpy(&hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[0], data, len);
                hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[0] = data[len-1];
                hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[len - 1] = data[0];
                hid_cp_ms_ctx->ms_ctx.bt_hid_data.data_len = len;
                #endif

                #if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE)
                if (hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[0] & 0x40)
                {
                    /* this packet is hid data mixed with custome protocol data, so need do special opertaions */
                    hid_critical_path_common_custom_protocol_data_push(&hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[1], EPIO_CUSTOM_PROTOCOL_MIX_WITH_HID_PACKET_SIZE);
                    hid_cp_ms_custom_protocol_data_mix_with_hid_packet_process(&hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[0], len);
                }
                #endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE */
                break;
#endif
#if CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE
            case REPORT_ID_KB_STD_XY:
            case REPORT_ID_KB_CONSUMER_XY:
            case REPORT_ID_KB_STD:
            case REPORT_ID_KB_CONSUMER:
                #if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) || defined(AIR_DONGLE_OF_KEYBOARD_M607)
                /* HID_RAW_DATA_PROCESS_METHOD_CYCLLE_1B */
                memcpy(&hid_cp_key_remap_ctx->kb_ctx.bt_hid_data.data[1], data, len-1);
                hid_cp_key_remap_ctx->kb_ctx.bt_hid_data.data[0] = data[len - 1];
                hid_cp_key_remap_ctx->kb_ctx.bt_hid_data.data_len = len;
                #else
                /* HID_RAW_DATA_PROCESS_METHOD_EXCHANGE_1B */
                memcpy(&hid_cp_key_remap_ctx->kb_ctx.bt_hid_data.data[0], data, len);
                hid_cp_key_remap_ctx->kb_ctx.bt_hid_data.data[0] = data[len-1];
                hid_cp_key_remap_ctx->kb_ctx.bt_hid_data.data[len - 1] = data[0];
                hid_cp_key_remap_ctx->kb_ctx.bt_hid_data.data_len = len;
                #endif
                break;
#endif
#if defined (CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE)
            case REPORT_ID_KEYBOARD :
            case REPORT_ID_KEYBOARD_GROUP0 :
            case REPORT_ID_KEYBOARD_GROUP1 :
                /* HID_RAW_DATA_PROCESS_METHOD_CYCLLE_1B */
                memcpy(&hid_cp_nkey_ctx->kb_ctx.bt_hid_data.data[1], data, len-1);
                hid_cp_nkey_ctx->kb_ctx.bt_hid_data.data[0] = data[len - 1];
                hid_cp_nkey_ctx->kb_ctx.bt_hid_data.data_len = len;
                break;
#endif
#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE)
            case REPORT_ID_GAME_CONTROLLER:
            case REPORT_ID_GAME_CONTROLLER_GROUP0:
            case REPORT_ID_GAME_CONTROLLER_GROUP1:
            case REPORT_ID_GAME_CONTROLLER_GROUP2:
            case REPORT_ID_GAME_CONTROLLER_ALL_IN_ONE:
                /* HID_RAW_DATA_PROCESS_METHOD_CYCLLE_1B */
                memcpy(&hid_cp_game_controller_ctx->gp_ctx.bt_hid_data.data[1], data, len - 1);
                hid_cp_game_controller_ctx->gp_ctx.bt_hid_data.data[0] = data[len - 1];
                hid_cp_game_controller_ctx->gp_ctx.bt_hid_data.data_len = len;
                break;
#endif /* CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE */

            default:
                if(report_id != REPORT_ID_MOUSE)
                {
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
                    hal_gpio_set_output(HID_CP_DEBUG_GPIO_1, HAL_GPIO_DATA_LOW);
#endif
                    memcpy(&hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[0], data, len);
                    hid_cp_ms_ctx->ms_ctx.bt_hid_data.data_len = len;
                    hid_cp_debug_log(hid_cp_ms_ctx->report_rate);
                    #if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE)
                    hid_cp_debug_log(hid_cp_game_controller_ctx->report_rate);
                    #endif
                    hid_cp_debug_paramter.not_except_count ++;
#if defined(AIR_DONGLE_OF_KEYBOARD_M607)
                    LOG_ERR(BT_HID_CP_TAG"[Debug] report data(len %d): 0x%02X-0x%02X-0x%02X-0x%02X-0x%02X-0x%02X-0x%02X-0x%02X-0x%02X",
                        len,
                        data[0], data[1], data[2], data[3],
                        data[4], data[5], data[6], data[7],
                        data[8]
                    );
#endif
                    goto exit;
                }
                break;
        }
    }
#if !defined(CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE)
    memcpy(&hid_cp_ms_ctx->ms_ctx.bt_hid_plc_param, plc_param, sizeof(usb_plc_cb_param));
#endif
#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE)
    memcpy(&hid_cp_game_controller_ctx->gp_ctx.bt_hid_plc_param, plc_param, sizeof(usb_plc_cb_param));
#endif
    if(report_id != 0) {
        status = hid_cp_bt_isr_callback_process(report_id);
    }
    if(plc_param && plc_param->reason) {
        if (plc_param->reason == HID_PLC_REASON_RX_FAIL || plc_param->reason == HID_PLC_REASON_LEC_U_PKT) {
            hid_cp_debug_paramter.plc_err_count++;
        } else if (plc_param->reason == HID_PLC_REASON_NULL_PKT) {
            hid_cp_debug_paramter.plc_null_count++;
        } else if (plc_param->reason == HID_PLC_REASON_DUP_PKT) {
            hid_cp_debug_paramter.plc_dup_count++;
        } else {
            hid_cp_debug_paramter.plc_dup_count++;
        }
    } else {
        hid_cp_debug_paramter.normal_data_count++;
    }
exit:

#ifdef CONFIG_AIR_HID_CP_DEBUG_LOG
    if (hid_cp_ms_ctx->ms_ctx.bt_hid_data.data_len != 0)
    {
        memcpy(&hid_cp_debug_paramter.hid_data[hid_cp_debug_paramter.log_print_count].data[0],
                &hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[0],
                hid_cp_ms_ctx->ms_ctx.bt_hid_data.data_len);
    }
#if CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE
    else if (hid_cp_key_remap_ctx->kb_ctx.bt_hid_data.data_len != 0){
        LOG_ERR(BT_HID_CP_TAG"record keyboard debug data, len: %d, %02X %02X %02X %02X %02X %02X %02X %02X",
            (int)hid_cp_key_remap_ctx->kb_ctx.bt_hid_data.data_len,
            (unsigned int)hid_cp_debug_paramter.hid_data[hid_cp_debug_paramter.log_print_count].data[0],
            (unsigned int)hid_cp_debug_paramter.hid_data[hid_cp_debug_paramter.log_print_count].data[1],
            (unsigned int)hid_cp_debug_paramter.hid_data[hid_cp_debug_paramter.log_print_count].data[2],
            (unsigned int)hid_cp_debug_paramter.hid_data[hid_cp_debug_paramter.log_print_count].data[3],
            (unsigned int)hid_cp_debug_paramter.hid_data[hid_cp_debug_paramter.log_print_count].data[4],
            (unsigned int)hid_cp_debug_paramter.hid_data[hid_cp_debug_paramter.log_print_count].data[5],
            (unsigned int)hid_cp_debug_paramter.hid_data[hid_cp_debug_paramter.log_print_count].data[6],
            (unsigned int)hid_cp_debug_paramter.hid_data[hid_cp_debug_paramter.log_print_count].data[7]
        );
        memcpy(&hid_cp_debug_paramter.hid_data[hid_cp_debug_paramter.log_print_count].data[0],
                &hid_cp_key_remap_ctx->kb_ctx.bt_hid_data.data[0],
                hid_cp_key_remap_ctx->kb_ctx.bt_hid_data.data_len);
    }
#endif
#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE)
    if (hid_cp_game_controller_ctx->gp_ctx.bt_hid_data.data_len != 0)
    {
        memcpy(&hid_cp_debug_paramter.hid_data[hid_cp_debug_paramter.log_print_count].data[0],
                &hid_cp_game_controller_ctx->gp_ctx.bt_hid_data.data[0],
                hid_cp_game_controller_ctx->gp_ctx.bt_hid_data.data_len);
    }
#endif /* CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE */
    else
    {
        memset(&hid_cp_debug_paramter.hid_data[hid_cp_debug_paramter.log_print_count].data[0],
                0,
                HID_NORMAL_DATA_LEN);
    }
    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    hid_cp_debug_paramter.hid_data[hid_cp_debug_paramter.log_print_count].data[7] = plc_param->reason;
    hid_cp_debug_paramter.log_print_count++;
    if (hid_cp_debug_paramter.log_print_count >= HID_LOG_PRINT_COUNT*2)
    {
        hid_cp_debug_paramter.log_print_count = 0;
    }
    hid_cp_debug_paramter.usb_data[hid_cp_debug_paramter.usb_print_count].data[7] = status;
    hid_cp_debug_paramter.usb_print_count++;
    if (hid_cp_debug_paramter.usb_print_count >= HID_LOG_PRINT_COUNT*2)
    {
        hid_cp_debug_paramter.usb_print_count = 0;
    }
    hal_nvic_restore_interrupt_mask(mask);
#endif

    hal_nvic_set_pending_irq(WDT_IRQn);
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
    hal_gpio_set_output(HID_CP_DEBUG_GPIO_1, HAL_GPIO_DATA_LOW);
#endif
}

int hid_critical_path_send_dummy_data(hid_critical_path_device_type_t type)
{
    int ret = 0;
    LOG_INF(BT_HID_CP_TAG"hid_critical_path_send_dummy_data, type: %d", type);
    if (type >= HID_CRITICAL_PATH_DEVICE_TYPE_MAX_NUM) {
        return -1;
    }
    bt_ms_packet_t ms_usb_data;
    memset(&ms_usb_data, 0, sizeof(bt_ms_packet_t));
    ms_usb_data.report_id = AIR_USB_HID_GAMING_MS_REPORT_ID;
    ms_usb_data.x = 1;
    ms_usb_data.y = 1;
    hid_cp_ms_data_send_to_usb((uint8_t*)(&ms_usb_data), sizeof(ms_usb_data));
    return ret;
}

static bt_ull_le_hid_srv_report_rate_level_t hid_critical_path_covert_report_rate(uint16_t report_rate)
{
    bt_ull_le_hid_srv_report_rate_level_t rr_level;
    switch (report_rate) {
        case 125:
            rr_level = BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_2;
            break;
        case 250:
            rr_level = BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_3;
            break;
        case 500:
            rr_level = BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_4;
            break;
        case 1000:
            rr_level = BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_5;
            break;
        case 2000:
            rr_level = BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_6;
            break;
        case 4000:
            rr_level = BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_7;
            break;
        case 8000:
            rr_level = BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_8;
            break;
        default:
            rr_level = BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_1;
            break;
    }
    return rr_level;
}

void hid_critical_path_set_device_info(hid_critical_path_device_type_t dev_type, hid_critical_path_info_type_t info_type, const void *info)
{
    hid_critical_path_t *hid_cp_ctx = hid_critical_path_common_get_ctx(dev_type);
    LOG_INF(BT_HID_CP_TAG"hid_critical_path_set_device_info, dev_type: %d, info_type: %d", dev_type, info_type);
    if (!info) {
        return;
    }
    switch (info_type) {
        case HID_CRITICAL_PATH_INFO_TYPE_REPORT_RATE: {
            uint16_t report_rate = *(uint16_t *)info;
            LOG_INF(BT_HID_CP_TAG"Report rate changed from %d to %d", hid_cp_ctx->report_rate, hid_critical_path_covert_report_rate(report_rate));
            hid_cp_ctx->report_rate = hid_critical_path_covert_report_rate(report_rate);
            break;
        }
        case HID_CRITICAL_PATH_INFO_TYPE_DPI: {
            uint16_t dpi = *(uint16_t *)info;
            LOG_INF(BT_HID_CP_TAG"DPI changed from %d to %d", hid_cp_ctx->ms_ctx.dpi, dpi);
            hid_cp_ctx->ms_ctx.dpi = dpi;
            break;
        }
        default: {
            LOG_ERR(BT_HID_CP_TAG"Unknown info type");
            break;
        }
    }
}

void hid_critical_path_start(hid_critical_path_device_type_t type)
{
    hid_critical_path_t *hid_cp_ctx = hid_critical_path_common_get_ctx(type);
    hid_critical_path_set_state(type, HID_CP_STATE_CONNECTED);
    hid_cp_ctx->bit_mask &= ~HID_CP_BIT_MASK_LAST_KEY_VAILD;
    #if defined(AIR_HID_DUMMY_REPORT_RATE)
    // hid_cp_ctx->report_rate = bt_ull_le_hid_srv_get_report_rate();
    #else
    hid_cp_ctx->report_rate = bt_ull_le_hid_srv_get_report_rate();
    #endif/*AIR_HID_DUMMY_REPORT_RATE*/
    #if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE)
    if (hid_scenario_dongle_usb_mode_check() == USB_MODE_HID) {
        hid_cp_ctx->hid_protocol = air_usb_hid_get_protocol_mode(hid_cp_ctx->hid_dev);
    }
    #else
        hid_cp_ctx->hid_protocol = air_usb_hid_get_protocol_mode(hid_cp_ctx->hid_dev);
    #endif
    LOG_INF(BT_HID_CP_TAG"hid_critical_path_start, type: %d, report_rate: %x, mode: %d", type, hid_cp_ctx->report_rate, hid_cp_ctx->hid_protocol);
    switch(type){
        case HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE:
            hid_critical_path_ms_start();
            break;
#if CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE
        case HID_CRITICAL_PATH_DEVICE_TYPE_KEY_REMAP:
            hid_critical_path_kb_start();
            break;
#endif
#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
        case HID_CRITICAL_PATH_DEVICE_TYPE_NKEY:
            hid_critical_path_kb_start();
            break;
#endif
#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE)
        case HID_CRITICAL_PATH_DEVICE_TYPE_GAME_CONTROLLER:
            hid_critical_path_gamepad_start();
            break;
#endif /* CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE */
        default:
            assert(0);
            break;
    }
    /* lock 156M when start, unlock when stop*/
    hal_dvfs_lock_control(HAL_DVFS_OPP_HIGH, HAL_DVFS_LOCK);
}

void hid_critical_path_stop(hid_critical_path_device_type_t type)
{
    hid_critical_path_t *hid_cp_ctx = hid_critical_path_common_get_ctx(type);
    LOG_INF(BT_HID_CP_TAG"hid_critical_path_stop, type: %d, mode:%d", type, hid_cp_ctx->hid_protocol);
    switch(type){
        case HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE:
            hid_critical_path_ms_stop();
            break;
#if CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE
        case HID_CRITICAL_PATH_DEVICE_TYPE_KEY_REMAP:
            hid_critical_path_kb_stop();
            break;
#endif
#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
        case HID_CRITICAL_PATH_DEVICE_TYPE_NKEY:
            hid_critical_path_kb_stop();
            break;
#endif
#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE)
        case HID_CRITICAL_PATH_DEVICE_TYPE_GAME_CONTROLLER:
            hid_critical_path_gamepad_stop();
            break;
#endif /* CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE */
        default:
            assert(0);
            break;
    }

    hid_critical_path_set_state(type, HID_CP_STATE_DISCONNECTED);
    hid_critical_path_set_state(type, HID_CP_STATE_IDLE);
    hid_cp_ctx->bit_mask &= ~HID_CP_BIT_MASK_LAST_KEY_VAILD;
    /* lock 156M when start, unlock when stop*/
    hal_dvfs_lock_control(HAL_DVFS_OPP_HIGH, HAL_DVFS_UNLOCK);
    /* Clear PLC TBD */
}

int hid_critical_path_init(void)
{
    int ret = 0;
    LOG_INF(BT_HID_CP_TAG"HID Critical Path Init");
    hid_critical_path_common_init();
    hid_critical_path_ms_init();
#if CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE
    hid_critical_path_kb_init();
#endif
#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
    hid_critical_path_kb_init();
#endif
#if CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE
    hid_critical_path_gamepad_init();
#endif

    pka_hid_data_forward_callback_register((void *)hid_cp_bt_isr_callback);
    /* SW ISR Register  */
    hal_nvic_disable_irq(WDT_IRQn);
#if defined(AIR_NVIDIA_REFLEX_ENABLE)
    /* Enable nvidia reflex: USB ISR > BT ISR > WDT ISR > BT timer ISR */
    hal_nvic_set_priority(WDT_IRQn, (DEFAULT_IRQ_PRIORITY + 2));
#else
    /* Disable nvidia reflex: BT ISR > WDT ISR > BT timer ISR > USB ISR */
    hal_nvic_set_priority(WDT_IRQn, (DEFAULT_IRQ_PRIORITY + 2));
#endif
    hal_nvic_register_isr_handler(WDT_IRQn, (hal_nvic_isr_t)hid_cp_sw_isr_callback);
    hal_nvic_enable_irq(WDT_IRQn);
    /* Set Usb Reserved tx anchor: Pre */
    /* Air-Rx-Done to modem process + BT-Rx-done to HID-CB + HID-CB-Process*/
    /* 8us[8K] + 2.5us + 16.5us, worst case is 35us in LA, 5us is reserved buffer */
    bt_ull_le_hid_conn_srv_set_usb_tx_anchor(CONFIG_AIR_HID_CP_TRIGGER_USB_ANCHOR);
    return ret;
}

void hid_critical_path_deinit(void)
{
    LOG_INF(BT_HID_CP_TAG"HID Critical Path DeInit");
    hid_critical_path_ms_deinit();
    hid_critical_path_kb_deinit();
    hid_critical_path_gamepad_deinit();
}

void hid_critical_path_register_debug_callback(hid_cp_debug_callback_t cb)
{
    hid_critical_path_common_register_callback(cb);
}

/* End of file */