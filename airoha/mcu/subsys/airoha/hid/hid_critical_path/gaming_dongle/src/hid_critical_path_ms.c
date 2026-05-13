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

#include "hid_critical_path_ms.h"
/* Struct Define Start*/

static bool hid_cp_ms_start_filter_duplicate_data(bt_ms_packet_t *ms_usb_data);
static void hid_cp_ms_reset_filter_duplicate(void);
static void hid_cp_ms_key_process(uint8_t key_in, uint8_t* key_out, hid_plc_reason_t reason);
static void hid_cp_ms_z_process(uint8_t z_data_in, uint8_t *z_data_out);
static void hid_cp_ms_hid_data_parse(uint8_t report_id, uint8_t* data_in, usb_plc_cb_param *plc_param, bt_ms_packet_t *data_out);
static void hid_cp_ms_prepare_boot_protocol(uint8_t *in, uint8_t *out);
static hid_critical_path_status_t hid_cp_ms_handle(uint8_t report_id, uint8_t* data, uint16_t len, usb_plc_cb_param *plc_param);

/* Function API Implementation */
ATTR_TEXT_IN_TCM static bool hid_cp_ms_start_filter_duplicate_data(bt_ms_packet_t *ms_usb_data)
{
    bool ret = false;
    hid_critical_path_t *hid_cp_ms_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
    /* x==y==z==0 && last_key is valid && current_key == last_key */
    if(!(hid_cp_ms_ctx->bit_mask & HID_CP_BIT_MASK_LAST_KEY_VAILD)){
        // LOG_ERR(BT_HID_CP_TAG"HID Critical Path: Last Key is not valid to start filter duplicate data!");
        ret = false;
        goto exit;
    }
    if (ms_usb_data->x == 0 && ms_usb_data->y == 0 && ms_usb_data->wheel == 0 && \
                ms_usb_data->key == hid_cp_ms_ctx->ms_ctx.last_key)
    {
        ret = true;
        // LOG_ERR(BT_HID_CP_TAG"USB DUPLICATE: x=%d, y=%d, wheel=%d, key=%d, last_key=%d",
        //     ms_usb_data->x, ms_usb_data->y, ms_usb_data->wheel,
        //     ms_usb_data->key, hid_cp_ms_ctx->ms_ctx.last_key);
    }
exit:
    if (ret) {
// #if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
//         hal_gpio_set_output(HID_CP_DEBUG_GPIO_4, HAL_GPIO_DATA_HIGH);
// #endif
        hid_cp_debug_paramter.duplicate_data_count ++;
#ifdef CONFIG_AIR_HID_CP_DEBUG_LOG
        uint32_t mask;
        hal_nvic_save_and_set_interrupt_mask(&mask);
        hid_cp_debug_paramter.usb_data[hid_cp_debug_paramter.usb_print_count].timestamp = GPT(HAL_GPT_US_PORT)->GPT_COUNT;
        memset(&hid_cp_debug_paramter.usb_data[hid_cp_debug_paramter.usb_print_count].data[0],
                0,
                7);
        hid_cp_debug_paramter.usb_data[hid_cp_debug_paramter.usb_print_count].data[6] = hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[6];
        hal_nvic_restore_interrupt_mask(mask);
#endif
// #if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
//         hal_gpio_set_output(HID_CP_DEBUG_GPIO_4, HAL_GPIO_DATA_LOW);
// #endif
    }
    return ret;
}

ATTR_TEXT_IN_TCM static void hid_cp_ms_reset_filter_duplicate(void)
{
    hid_critical_path_t *hid_cp_ms_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
    hid_cp_ms_ctx->bit_mask &= ~HID_CP_BIT_MASK_LAST_KEY_VAILD;
}

ATTR_TEXT_IN_TCM static void hid_cp_ms_clear_send_fail_data(void)
{
    hid_critical_path_t *hid_cp_ms_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
    memset(&hid_cp_ms_ctx->ms_ctx.resend_data, 0, sizeof(hid_critical_path_resend_t));
}

ATTR_TEXT_IN_TCM static int hid_cp_tx_done_cb(const struct device *dev, uint8_t type, uint8_t id,
				    uint16_t len, const uint8_t *buf)
{
    int ret = 0;
    uint32_t mask;
    hid_critical_path_t *hid_cp_ms_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
    hal_gpio_set_output(HID_CP_DEBUG_GPIO_5, HAL_GPIO_DATA_HIGH);
#endif
    hid_cp_debug_paramter.tx_done_cb_count++;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    if (hid_cp_ms_ctx->ms_ctx.resend_data.q_flag) {
        hid_cp_usb_tx_running_flag = true;
        bt_ms_packet_t ms_usb_data;
        memcpy(&ms_usb_data, &hid_cp_ms_ctx->ms_ctx.resend_data.data, sizeof(bt_ms_packet_t));
        ms_usb_data.report_id = REPORT_ID_MOUSE;
        hid_cp_ms_clear_send_fail_data();
        hal_nvic_restore_interrupt_mask(mask);
        ret = air_usb_hid_tx(hid_cp_ms_ctx->usb_user_id, \
                        hid_cp_ms_ctx->hid_dev, sizeof(bt_ms_packet_t), (uint8_t *)&ms_usb_data);
        hal_nvic_save_and_set_interrupt_mask(&mask);
        if (ret != 0) {
            hid_cp_debug_paramter.send_to_usb_fail_usb ++;
            hid_cp_ms_ctx->ms_ctx.resend_data.data.x += ms_usb_data.x;
            hid_cp_ms_ctx->ms_ctx.resend_data.data.y += ms_usb_data.y;
            hid_cp_ms_ctx->ms_ctx.resend_data.data.key = ms_usb_data.key;
            hid_cp_ms_ctx->ms_ctx.resend_data.data.wheel += ms_usb_data.wheel;
            hid_cp_ms_ctx->ms_ctx.resend_data.q_flag = true;
            hid_cp_ms_ctx->bit_mask |= HID_CP_BIT_MASK_RESEND_VAILD;
            hid_cp_ms_reset_filter_duplicate();
        } else {
            hid_cp_debug_paramter.send_to_usb_suc ++;
            hid_cp_ms_ctx->ms_ctx.last_key = ms_usb_data.key;
            hid_cp_ms_ctx->bit_mask |= HID_CP_BIT_MASK_LAST_KEY_VAILD;
            hid_cp_ms_ctx->bit_mask &= ~HID_CP_BIT_MASK_RESEND_VAILD;
#ifdef CONFIG_AIR_HID_CP_DEBUG_LOG
            if(len != sizeof(bt_ms_packet_t)) {
                LOG_ERR(BT_HID_CP_TAG"Invalid len in hid_cp_tx_done_cb");
                return -1;
            }
            uint32_t mask;
            hal_nvic_save_and_set_interrupt_mask(&mask);
            hid_cp_debug_paramter.usb_data[hid_cp_debug_paramter.usb_print_count].timestamp = GPT(HAL_GPT_US_PORT)->GPT_COUNT;
            memcpy(&hid_cp_debug_paramter.usb_data[hid_cp_debug_paramter.usb_print_count].data[0],
                    &ms_usb_data,
                    len);
            hid_cp_debug_paramter.usb_data[hid_cp_debug_paramter.usb_print_count].data[6] = hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[6];
            hal_nvic_restore_interrupt_mask(mask);
#endif
        }
        hid_cp_usb_tx_running_flag = false;
    }
    hal_nvic_restore_interrupt_mask(mask);
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
    hal_gpio_set_output(HID_CP_DEBUG_GPIO_5, HAL_GPIO_DATA_LOW);
#endif
    return 0;
}

/* packed mouse report send api */
ATTR_TEXT_IN_TCM int hid_cp_ms_data_send_to_usb(uint8_t* data, uint16_t len)
{
    int ret = 0;
    hid_critical_path_t *hid_cp_ms_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
    if (hid_cp_ms_ctx->hid_protocol == USB_PROTOCOL_REPORT_MODE) {
        ret = air_usb_hid_tx(hid_cp_ms_ctx->usb_user_id, \
                        hid_cp_ms_ctx->hid_dev, len, data);
    } else if (hid_cp_ms_ctx->hid_protocol == USB_PROTOCOL_BOOT_MODE) {
        /* Prepare for boot protocol  */
        uint8_t hid_boot_data[HID_BIOS_DATA_LEN] = {0};
        hid_cp_ms_prepare_boot_protocol(data, &hid_boot_data[0]);
        ret = air_usb_hid_tx(hid_cp_ms_ctx->usb_user_id, \
                        hid_cp_ms_ctx->hid_dev, HID_BIOS_DATA_LEN, &hid_boot_data[0]);
    } else {
        LOG_ERR(BT_HID_CP_TAG"Unknown usb hid protocol: %d", hid_cp_ms_ctx->hid_protocol);
    }
    return ret;
}

ATTR_TEXT_IN_TCM static void hid_cp_ms_key_process(uint8_t key_in, uint8_t *key_out, hid_plc_reason_t reason)
{
    /*
        1. last key send success: && no need plc --> last_key = key_in, last_key_valid = true
        2. last key send success && need plc --> last_key not change, last_key_valid = true
        3. last key send fail && no need plc --> last_key = key_in, last_key_valid = false
        4. last key send fail && need plc --> last_key not change, last_key_valid = false
    */
    hid_critical_path_t *hid_cp_ms_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
    if(key_in == 0x00 && reason){
        if(hid_cp_ms_ctx->bit_mask & HID_CP_BIT_MASK_RESEND_VAILD){
            /* 4. */
            hid_cp_ms_ctx->bit_mask &= ~HID_CP_BIT_MASK_LAST_KEY_VAILD;
        } else {
            /* 2. */
            hid_cp_ms_ctx->bit_mask |= HID_CP_BIT_MASK_LAST_KEY_VAILD;
        }
        *key_out = hid_cp_ms_ctx->ms_ctx.last_key;
    } else {
        if(hid_cp_ms_ctx->bit_mask & HID_CP_BIT_MASK_RESEND_VAILD){
            /* 3. */
            hid_cp_ms_ctx->bit_mask &= ~HID_CP_BIT_MASK_LAST_KEY_VAILD;
        } else {
            /* 1. */
            hid_cp_ms_ctx->bit_mask |= HID_CP_BIT_MASK_LAST_KEY_VAILD;
        }
        *key_out = key_in;
    }
    if (reason == HID_PLC_REASON_DUP_PKT) {
        *key_out = hid_cp_ms_ctx->ms_ctx.last_key;
    }
}

static int32_t plc_big_drift_x = 0;
static int32_t plc_big_drift_y = 0;
ATTR_TEXT_IN_TCM void hid_cp_ms_xy_process(uint8_t report_id, int32_t x_axis_in, int32_t y_axis_in, \
                                            usb_plc_cb_param *plc_param, \
                                            int32_t *x_axis_out, int32_t *y_axis_out)
{
    int32_t x_temp_out = 0;
    int32_t y_temp_out = 0;
    hid_critical_path_t *hid_cp_ms_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
    /* report_id process */
    switch (report_id) {
        case REPORT_ID_MOUSE:
        case REPORT_ID_MOUSE_16BIT:
            /* x_axis_in and y_axis_in process */
        #if defined(CONFIG_AIR_HID_PLC_CALCULATE) || defined(CONFIG_AIR_HID_PLC_BIG_DRIFT_PKT)
            /* Detect Big Drift & PLC */
            #ifdef CONFIG_AIR_HID_PLC_BIG_DRIFT_PKT
            bool window_flag = hid_plc_get_window_flag();
            hid_cp_ms_ctx->ms_ctx.big_drift_flag = false;
            if (plc_param->reason == HID_PLC_REASON_RX_SUCCEESS
                && hid_plc_common_detect_big_drift(&x_axis_in, &y_axis_in) != 0
                && !hid_cp_ms_ctx->ms_ctx.accumulate_flag
                && window_flag
                && hid_cp_ms_ctx->ms_ctx.dpi < CONFIG_AIR_HID_PLC_BIG_DRIFT_DPI) {
                #ifdef CONFIG_AIR_HID_PLC_CALCULATE
                hid_plc_common_get_character_data(&x_temp_out, &y_temp_out);
                /* restart detect big drift when cnt > 100 */
                if (hid_cp_ms_ctx->ms_ctx.big_drift_cnt > 100) {
                    hid_plc_common_clear();
                    hid_cp_ms_ctx->ms_ctx.big_drift_cnt = 0;
                }
                #else
                x_temp_out = 0;
                y_temp_out = 0;
                #endif
                hid_cp_ms_ctx->ms_ctx.big_drift_flag = true;
                hid_cp_ms_ctx->ms_ctx.big_drift_cnt ++;
                plc_big_drift_x = x_temp_out;
                plc_big_drift_y = y_temp_out;
                /* data_limiter : int32-->int16 */
                *x_axis_out = (x_temp_out > 32767) ? 32767 : ((x_temp_out < -32768) ? -32768 : x_temp_out);
                *y_axis_out = (y_temp_out > 32767) ? 32767 : ((y_temp_out < -32768) ? -32768 : y_temp_out);
                // assert(0);
                return;
            }
            #endif/* #CONFIG_AIR_HID_PLC_BIG_DRIFT_PKT */
        #else
            x_temp_out = x_axis_in;
            y_temp_out = y_axis_in;
        #endif/* #CONFIG_AIR_HID_PLC_CALCULATE || CONFIG_AIR_HID_PLC_BIG_DRIFT_PKT*/
            break;
        /* process x,y axis  but no algorithm process*/
        case REPORT_ID_KB_STD_XY:
        case REPORT_ID_KB_CONSUMER_XY:
        {
            x_temp_out = x_axis_in;
            y_temp_out = y_axis_in;
        }
        break;
        default:
            return;
    }

    #if defined(CONFIG_AIR_HID_PLC_CALCULATE)
    /* 125 && 250 & 500 & 1K, Do not PLC */
    bt_ull_le_hid_srv_report_rate_level_t report_rate = hid_cp_ms_ctx->report_rate;
    if (plc_param->reason &&
        ( report_rate == BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_2
        || report_rate == BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_3
        || report_rate == BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_4
        || report_rate == BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_5
    #if !defined(CONFIG_AIR_HID_PLC_WITH_RESEND)
        /* 2k need to resend & plc */
        || report_rate == BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_6
    #endif
    )) {
        return;
    }
    hid_plc_param_t plc_para;
    #if defined(CONFIG_AIR_HID_PLC_WITH_RESEND)
    plc_para.channel = plc_param->channel;
    #endif
    plc_para.correct = plc_param->correct;
    plc_para.reason = plc_param->reason;
    plc_para.accumulate = hid_cp_ms_ctx->ms_ctx.accumulate_flag;
    plc_para.x = x_axis_in;
    plc_para.y = y_axis_in;
    plc_para.report_rate = report_rate;
    /* Get PLC Data if not NULL PKT */
    if (plc_param->reason != HID_PLC_REASON_NULL_PKT
    #if defined(CONFIG_AIR_HID_PLC_WITH_RESEND)
    /* Only anchor channel do PLC */
        && plc_para.channel == 0
    #endif
    ) {
        hid_plc_common_status_t common_status = hid_plc_common_get_plc_data(&plc_para, &x_temp_out, &y_temp_out);
        if ((x_axis_in == 0 && y_axis_in == 0) &&
            (x_temp_out != 0 || y_temp_out != 0) &&
            (plc_param->reason == HID_PLC_REASON_RX_FAIL || plc_param->reason == HID_PLC_REASON_LEC_U_PKT || plc_param->reason == HID_PLC_REASON_DUP_PKT)) {
            hid_cp_debug_paramter.plc_correct_count++;
        }
        if (common_status == HID_PLC_COMMON_REVISED_ZERO) {
            hid_cp_debug_paramter.plc_revised_zero_count ++;
        }
    }
    #endif/* #CONFIG_AIR_HID_PLC_CALCULATE */
    /* data_limiter : int32-->int16 */
    *x_axis_out = (x_temp_out > 32767) ? 32767 : ((x_temp_out < -32768) ? -32768 : x_temp_out);
    *y_axis_out = (y_temp_out > 32767) ? 32767 : ((y_temp_out < -32768) ? -32768 : y_temp_out);
}

ATTR_TEXT_IN_TCM static void hid_cp_ms_z_process(uint8_t z_data_in, uint8_t *z_data_out)
{
    hid_critical_path_t *hid_cp_ms_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
    /* Merge Send fail data : wheel*/
    if(hid_cp_ms_ctx->bit_mask & HID_CP_BIT_MASK_RESEND_VAILD){
        // *z_data_out = z_data_in + hid_cp_ms_ctx->ms_ctx.resend_data.data.wheel;
    } else {
        *z_data_out = z_data_in;
    }
}
static int32_t last_valid_x_axis = 0;
static int32_t last_valid_y_axis = 0;
static int32_t last_valid_sn_axis = 0;
ATTR_TEXT_IN_TCM static void hid_cp_ms_hid_data_parse(uint8_t report_id, uint8_t* data_in, usb_plc_cb_param *plc_param, bt_ms_packet_t *data_out)
{
    // Parse the data from data_in to data_out
    uint8_t key = 0;
    int32_t x_axis = 0;
    int32_t y_axis = 0;
    int8_t wheel = 0;
    int8_t acpan = 0;
    int32_t x_axis_out = 0;
    int32_t y_axis_out = 0;
    hid_critical_path_t *hid_cp_ms_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
    if (report_id == REPORT_ID_MOUSE) {
        /* Parse Key */
        key = data_in[1];
        /* the valid bit for key is b0-b4, b5-b7 is reserved */
        if (key & 0xE0) {
            LOG_ERR(BT_HID_CP_TAG"hid_cp_ms_hid_data_parse: key error 0x%x, last_key: %d",
                    key, hid_cp_ms_ctx->ms_ctx.last_key);
            data_out->key = hid_cp_ms_ctx->ms_ctx.last_key;
            #ifdef CONFIG_AIR_HID_PLC_CALCULATE
            hid_plc_common_get_character_data(&x_axis_out, &y_axis_out);
            /* restart detect big drift when cnt > 100 */
            if (hid_cp_ms_ctx->ms_ctx.big_drift_cnt > 100) {
                hid_plc_common_clear();
                hid_cp_ms_ctx->ms_ctx.big_drift_cnt = 0;
            }
            #else
            x_axis_out = 0;
            y_axis_out = 0;
            #endif
            data_out->x = x_axis_out;
            data_out->y = y_axis_out;
            return;
        }
        /* Parse Z data */
        wheel = data_in[5];
        /* Parse X,Y coordinate  */
        x_axis = hid_cp_convert_data_extended((((data_in[3] & 0x0F) << 8) | data_in[2]));
        y_axis = hid_cp_convert_data_extended(((data_in[4] << 4)) | (data_in[3] >> 4));
        /* Parse AC/PAN */
        acpan = data_in[6];
    } else if (report_id == REPORT_ID_MOUSE_16BIT) {
        /* Parse Key and Wheel */
        key = data_in[1] & 0x1F; // Low 5 bits for key
        wheel = (data_in[1] & 0xE0) >> 5; // High 3 bits for wheel
        /* Sign extension for 3-bit wheel */
        if (wheel & 0x04) {
            wheel |= 0xF8;
        }
        /* Parse X,Y coordinate */
        x_axis = (int16_t)((data_in[3] << 8) | data_in[2]);
        y_axis = (int16_t)((data_in[5] << 8) | data_in[4]);
        /* Parse AC/PAN */
        acpan = data_in[6];
    }

    hid_cp_ms_key_process(key, &data_out->key, plc_param->reason);

    /* Parse Z data */
    hid_cp_ms_z_process(wheel, &data_out->wheel);
    if (plc_param->reason == HID_PLC_REASON_DUP_PKT) {
        data_out->wheel = 0;
    }

    if (data_in[6] != 0) {
        last_valid_sn_axis = data_in[6];
    }

    if (last_valid_x_axis == x_axis && last_valid_y_axis == y_axis && plc_param->reason != 5 && last_valid_sn_axis == data_in[6]) {
        // LOG_ERR(BT_HID_CP_TAG"Should be DUP, x:%d, y:%d, sn:%d, last_x:%d, last_y:%d,sn_last:%d,  reason:%d",
        //     x_axis, y_axis,  data_in[6], last_valid_x_axis, last_valid_y_axis, last_valid_sn_axis, plc_param->reason);
// #if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
//         hal_gpio_set_output(HID_CP_DEBUG_GPIO_3, HAL_GPIO_DATA_HIGH);
// #endif
// #if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
//         hal_gpio_set_output(HID_CP_DEBUG_GPIO_3, HAL_GPIO_DATA_LOW);
// #endif
        // assert(0);
    }
    if (x_axis != 0 || y_axis != 0) {
        last_valid_x_axis = x_axis;
        last_valid_y_axis = y_axis;
    }
    hid_cp_ms_xy_process(report_id, x_axis, y_axis, plc_param, &x_axis_out, &y_axis_out);
    data_out->x = x_axis_out;
    data_out->y = y_axis_out;

#if defined(CONFIG_AIR_HID_CP_DEBUG_LOG)
    if(acpan <= hid_cp_debug_paramter.last_acpan && acpan != 1){
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
        hal_gpio_set_output(HID_CP_DEBUG_GPIO_4, HAL_GPIO_DATA_HIGH);
#endif
        // LOG_ERR(BT_HID_CP_TAG"SN ERROR1, SN: %02X, last_SN: %02X", acpan, hid_cp_debug_paramter.last_acpan);
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
        hal_gpio_set_output(HID_CP_DEBUG_GPIO_4, HAL_GPIO_DATA_LOW);
#endif
    } else{
        if((acpan - hid_cp_debug_paramter.last_acpan > 1) && acpan != 0 && hid_cp_debug_paramter.last_acpan != 0){
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
        hal_gpio_set_output(HID_CP_DEBUG_GPIO_4, HAL_GPIO_DATA_HIGH);
#endif
    // LOG_ERR(BT_HID_CP_TAG"SN ERROR2, SN: %02X, last_SN: %02X", acpan, hid_cp_debug_paramter.last_acpan);
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
        hal_gpio_set_output(HID_CP_DEBUG_GPIO_4, HAL_GPIO_DATA_LOW);
#endif
        }
    }
    // data_out->acpan = acpan;
    hid_cp_debug_paramter.last_acpan = acpan;
#endif
    // hid_cp_ms_z_process(acpan, &data_out->acpan);
    /* Parse other data if needed */
}

ATTR_TEXT_IN_TCM static void hid_cp_ms_prepare_boot_protocol(uint8_t *in, uint8_t *out)
{
    bt_ms_packet_t *pkt = (bt_ms_packet_t *)in;
    out[0] = pkt->key;

    int16_t x_int16 = pkt->x;
    int16_t y_int16 = pkt->y;

    /* Merge Send fail data : x, y*/
    // if(hid_cp_ms_ctx->bit_mask & HID_CP_BIT_MASK_RESEND_VAILD){
    //     x_int16 +=  hid_cp_ms_ctx->ms_ctx.resend_data.data.x;
    //     y_int16 +=  hid_cp_ms_ctx->ms_ctx.resend_data.data.y;
    // }

    if (x_int16 < -128) {
        x_int16 = -128;
    } else if (x_int16 > 127) {
        x_int16 = 127;
    }

    if (y_int16 < -128) {
        y_int16 = -128;
    } else if (y_int16 > 127) {
        y_int16 = 127;
    }

    out[1] = (uint8_t)(x_int16 & 0xFF);
    out[2] = (uint8_t)(y_int16 & 0xFF);
    /* Byte 3~7 are reserved */
    out[3] = 0;
    out[4] = 0;
    out[5] = 0;
    out[6] = 0;
    out[7] = 0;
}

// #ifdef CONFIG_AIR_HID_CP_DEBUG_LOG
static uint32_t err_cnt = 0;
static uint8_t not_excepted_data[8] = {0};
// #endif
ATTR_TEXT_IN_TCM static hid_critical_path_status_t hid_cp_ms_handle(uint8_t report_id, uint8_t* data, uint16_t len, usb_plc_cb_param *plc_param)
{
    hid_critical_path_status_t status = HID_CP_STATUS_SUCCESS;
    hid_critical_path_t *hid_cp_ms_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
    bool is_duplicated = false;
    int ret = 0;
    bt_ms_packet_t ms_usb_data;
    memset(&ms_usb_data, 0, sizeof(bt_ms_packet_t));
    ms_usb_data.report_id = AIR_USB_HID_GAMING_MS_REPORT_ID;
    /* Process ms hid data */
    hid_cp_ms_hid_data_parse(report_id, data, plc_param, &ms_usb_data);
    /* Filter duplication packets mechanism */
    is_duplicated = hid_cp_ms_start_filter_duplicate_data(&ms_usb_data);
    if(is_duplicated){
        return HID_CP_STATUS_DUMPLICATED;
    }
    /* Send to USB */
    if(hid_cp_usb_tx_running_flag == false) {
        /* merge new data & record data , key not changed*/
        if (hid_cp_ms_ctx->ms_ctx.resend_data.q_flag) {
            ms_usb_data.x += hid_cp_ms_ctx->ms_ctx.resend_data.data.x;
            ms_usb_data.y += hid_cp_ms_ctx->ms_ctx.resend_data.data.y;
            ms_usb_data.wheel += hid_cp_ms_ctx->ms_ctx.resend_data.data.wheel;
        }
// #ifdef CONFIG_AIR_HID_CP_DEBUG_LOG
        hid_cp_ms_ctx->ms_ctx.not_excepted_data_flag = false;
        if (ms_usb_data.x > 169 || ms_usb_data.x < -169 || ms_usb_data.y > 169 || ms_usb_data.y < -169) {
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
            hal_gpio_set_output(HID_CP_DEBUG_GPIO_4, HAL_GPIO_DATA_HIGH);
#endif
            err_cnt ++;
            memcpy(&not_excepted_data, &ms_usb_data, sizeof(bt_ms_packet_t));
            hid_cp_ms_ctx->ms_ctx.not_excepted_data_flag = true;
            // LOG_ERR(BT_HID_CP_TAG"Not Excepted Data, report_id: %d, key: %d, x:%d, y:%d, wheel:%d, acpan: %d, err_cnt: %d",
            //             report_id, ms_usb_data.key, ms_usb_data.x, ms_usb_data.y, ms_usb_data.wheel, ms_usb_data.acpan, err_cnt);
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
            hal_gpio_set_output(HID_CP_DEBUG_GPIO_4, HAL_GPIO_DATA_LOW);
#endif
        }
// #endif
        if ((ret = hid_cp_ms_data_send_to_usb((uint8_t *)&ms_usb_data, sizeof(bt_ms_packet_t))) == 0) {
            /* Send to USB Successfully  */
            hid_cp_debug_paramter.send_to_usb_suc ++;
            hid_cp_ms_ctx->ms_ctx.last_key = ms_usb_data.key;
            hid_cp_ms_ctx->bit_mask |= HID_CP_BIT_MASK_LAST_KEY_VAILD;
            hid_cp_ms_ctx->bit_mask &= ~HID_CP_BIT_MASK_RESEND_VAILD;
            /* clear record data */
            hid_cp_ms_clear_send_fail_data();
#ifdef CONFIG_AIR_HID_CP_DEBUG_LOG
            if(len != sizeof(bt_ms_packet_t)) {
                LOG_ERR(BT_HID_CP_TAG"Invalid len in hid_cp_ms_handle");
                return -1;
            }
            uint32_t mask;
            hal_nvic_save_and_set_interrupt_mask(&mask);
            hid_cp_debug_paramter.usb_data[hid_cp_debug_paramter.usb_print_count].timestamp = GPT(HAL_GPT_US_PORT)->GPT_COUNT;
            memcpy(&hid_cp_debug_paramter.usb_data[hid_cp_debug_paramter.usb_print_count].data[0],
                    data,
                    len);
            hid_cp_debug_paramter.usb_data[hid_cp_debug_paramter.usb_print_count].data[6] = hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[6];
            hal_nvic_restore_interrupt_mask(mask);
#endif
        } else {
            /* Send to USB Failed */
            status = HID_CP_STATUS_SEND_FAIL;
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
            hal_gpio_set_output(HID_CP_DEBUG_GPIO_3, HAL_GPIO_DATA_HIGH);
#endif
            hid_cp_debug_paramter.send_to_usb_fail_bt ++;
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
            hal_gpio_set_output(HID_CP_DEBUG_GPIO_3, HAL_GPIO_DATA_LOW);
#endif
            hid_cp_ms_ctx->bit_mask |= HID_CP_BIT_MASK_RESEND_VAILD;
            hid_cp_ms_reset_filter_duplicate();
            /*  Q send fail data*/
            hid_cp_ms_ctx->ms_ctx.resend_data.q_flag = true;
            memcpy(&hid_cp_ms_ctx->ms_ctx.resend_data.data, &ms_usb_data, sizeof(bt_ms_packet_t));
        }
    } else {
        /*usb tx done cb is running */
        status = HID_CP_STATUS_STATE_BUSY;
        hid_cp_debug_paramter.tx_done_send_busy_count++;
        hid_cp_ms_ctx->ms_ctx.resend_data.q_flag = true;
        hid_cp_ms_ctx->ms_ctx.resend_data.data.x += ms_usb_data.x;
        hid_cp_ms_ctx->ms_ctx.resend_data.data.y += ms_usb_data.y;
        hid_cp_ms_ctx->ms_ctx.resend_data.data.key = ms_usb_data.key;
        hid_cp_ms_ctx->ms_ctx.resend_data.data.wheel += ms_usb_data.wheel;
    }

    return status;
}

ATTR_TEXT_IN_TCM hid_critical_path_status_t hid_cp_ms(uint8_t* data, uint16_t len, usb_plc_cb_param *plc_param)
{
    hid_critical_path_status_t status = HID_CP_STATUS_SUCCESS;
    if (data == NULL || plc_param == NULL) {
        LOG_ERR(BT_HID_CP_TAG"Invalid parameters in hid_cp_ms");
        status = HID_CP_STATUS_FAIL;
        return status;
    }

    /* extract report ID */
    #if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_HIX_MIXING_ENABLE)
    uint8_t report_id = data[0] & 0x3F;
    #else
    uint8_t report_id = data[0] & 0x7F;
    #endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_HIX_MIXING_ENABLE */
    if (report_id == REPORT_ID_MOUSE || report_id == REPORT_ID_MOUSE_16BIT)
    {
        status = hid_cp_ms_handle(report_id, data, len, plc_param);
    } else {
        /* KB TBD */
        // status = app_usb_utils_kb_callback_handle(report_id, data, len);
        status = HID_CP_STATUS_FAIL;
    }
    return status;
}

ATTR_TEXT_IN_TCM void hid_cp_ms_sw_isr_callback(void)
{
    hid_critical_path_t *hid_cp_ms_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
// #if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
//     hal_gpio_set_output(HID_CP_DEBUG_GPIO_6, HAL_GPIO_DATA_HIGH);
// #endif

#if defined(CONFIG_AIR_HID_PLC_CALCULATE)
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
    // hal_gpio_set_output(HID_CP_DEBUG_GPIO_2, HAL_GPIO_DATA_HIGH);
#endif
    hid_cp_debug_log(hid_cp_ms_ctx->report_rate);
    usb_plc_cb_param plc_param = hid_cp_ms_ctx->ms_ctx.bt_hid_plc_param;
    hid_plc_param_t plc_para;
#if defined(CONFIG_AIR_HID_PLC_WITH_RESEND)
    plc_para.channel = plc_param.channel;
#endif
    plc_para.correct = plc_param.correct;
    plc_para.reason = plc_param.reason;
    plc_para.accumulate = hid_cp_ms_ctx->ms_ctx.accumulate_flag;
    if ((hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[0] & 0x1F) == REPORT_ID_MOUSE_16BIT) {
        plc_para.x = (int16_t)((hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[3] << 8) | \
                        hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[2]);
        plc_para.y = (int16_t)((hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[5] << 8) | \
                            hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[4]);
    } else if ((hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[0] & 0x1F) == REPORT_ID_MOUSE) {
        plc_para.x = hid_cp_convert_data_extended((((hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[3] & 0x0F) << 8) | \
                        hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[2]));
        plc_para.y = hid_cp_convert_data_extended(((hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[4] << 4)) | \
                            (hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[3] >> 4));
    }

    /* 125 && 250 , Do not PLC*/
    plc_para.report_rate = hid_cp_ms_ctx->report_rate;
    if (plc_param.reason != HID_PLC_REASON_NULL_PKT) {
        if (plc_param.reason != HID_PLC_REASON_RX_FAIL) {
            hid_cp_ms_ctx->ms_ctx.null_cnt = 0;
        }

    /* resend channel only for normal data to plc buffer to calculate */
#if defined(CONFIG_AIR_HID_PLC_WITH_RESEND)
        if ( plc_para.channel == 0 ) {
            hid_plc_common_handler(&plc_para);
        } else {
            if (plc_param.reason == HID_PLC_REASON_RX_SUCCEESS) {
                hid_plc_common_handler(&plc_para);
            }
        }
#else
        hid_plc_common_handler(&plc_para);
#endif
    } else {
        hid_cp_ms_ctx->ms_ctx.null_cnt ++;
        if (hid_cp_ms_ctx->ms_ctx.null_cnt > 10) {
#ifdef CONFIG_AIR_HID_PLC_CALCULATE
            hid_plc_common_clear();
#endif
        }
    }
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
    // hal_gpio_set_output(HID_CP_DEBUG_GPIO_2, HAL_GPIO_DATA_LOW);
#endif
#endif /* CONFIG_AIR_HID_PLC_DUPLICATE_PKT */
    if (hid_cp_ms_ctx->ms_ctx.big_drift_flag) {
        LOG_ERR(BT_HID_CP_TAG"BIG Drift Detect! cnt: %d, plc_out(%d, %d)",
            hid_cp_ms_ctx->ms_ctx.big_drift_cnt, plc_big_drift_x, plc_big_drift_y);
    }
    if (hid_cp_ms_ctx->ms_ctx.not_excepted_data_flag
        && hid_cp_ms_ctx->report_rate >= BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_5) {
        LOG_ERR(BT_HID_CP_TAG"Not excepted data! cnt: %d, data(%02X, %02X, %02X, %02X, %02X, %02X, %02X)", err_cnt,
                                                                            not_excepted_data[0],
                                                                            not_excepted_data[1],
                                                                            not_excepted_data[2],
                                                                            not_excepted_data[3],
                                                                            not_excepted_data[4],
                                                                            not_excepted_data[5],
                                                                            not_excepted_data[6]);
    }
#ifdef CONFIG_AIR_HID_CP_DEBUG_LOG
    // extern void app_hid_plc_debug_info(void);
    // app_hid_plc_debug_info();
    uint32_t buf_index;
    bool is_dump;
    uint32_t mask;
    uint8_t cnt;

    /* dump bt input data */
    is_dump = false;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    cnt = hid_cp_debug_paramter.log_print_count;
    if ((cnt >= 0 && cnt < HID_LOG_PRINT_COUNT) && (HID_LOG_PRINT_COUNT == hid_cp_debug_paramter.log_print_count_last))
    {
        buf_index = HID_LOG_PRINT_COUNT;
        is_dump = true;
        hid_cp_debug_paramter.log_print_count_last = 0;
    }
    else if ((cnt >= HID_LOG_PRINT_COUNT) && (0 == hid_cp_debug_paramter.log_print_count_last))
    {
        buf_index = 0;
        is_dump = true;
        hid_cp_debug_paramter.log_print_count_last = HID_LOG_PRINT_COUNT;
    }
    hal_nvic_restore_interrupt_mask(mask);
    if (is_dump)
    {
        LOG_INF(BT_HID_CP_TAG"hid_cp_sw_isr_callback: bt  data[0-3]: %08X%08X%08X--%08X%08X%08X--%08X%08X%08X--%08X%08X%08X",
                                    hid_cp_debug_paramter.hid_data[0+buf_index].timestamp,
                                    *(uint32_t *)&hid_cp_debug_paramter.hid_data[0+buf_index].data[4],
                                    *(uint32_t *)&hid_cp_debug_paramter.hid_data[0+buf_index].data[0],
                                    hid_cp_debug_paramter.hid_data[1+buf_index].timestamp,
                                    *(uint32_t *)&hid_cp_debug_paramter.hid_data[1+buf_index].data[4],
                                    *(uint32_t *)&hid_cp_debug_paramter.hid_data[1+buf_index].data[0],
                                    hid_cp_debug_paramter.hid_data[2+buf_index].timestamp,
                                    *(uint32_t *)&hid_cp_debug_paramter.hid_data[2+buf_index].data[4],
                                    *(uint32_t *)&hid_cp_debug_paramter.hid_data[2+buf_index].data[0],
                                    hid_cp_debug_paramter.hid_data[3+buf_index].timestamp,
                                    *(uint32_t *)&hid_cp_debug_paramter.hid_data[3+buf_index].data[4],
                                    *(uint32_t *)&hid_cp_debug_paramter.hid_data[3+buf_index].data[0]);
    }

    /* dump usb output data */
    is_dump = false;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    cnt = hid_cp_debug_paramter.usb_print_count;
    if ((cnt >= 0 && cnt < HID_LOG_PRINT_COUNT) && (HID_LOG_PRINT_COUNT == hid_cp_debug_paramter.usb_print_count_last))
    {
        buf_index = HID_LOG_PRINT_COUNT;
        is_dump = true;
        hid_cp_debug_paramter.usb_print_count_last = 0;
    }
    else if ((cnt >= HID_LOG_PRINT_COUNT) && (0 == hid_cp_debug_paramter.usb_print_count_last))
    {
        buf_index = 0;
        is_dump = true;
        hid_cp_debug_paramter.usb_print_count_last = HID_LOG_PRINT_COUNT;
    }
    hal_nvic_restore_interrupt_mask(mask);
    if (is_dump)
    {
        LOG_INF(BT_HID_CP_TAG"hid_cp_sw_isr_callback: usb data[0-3]: %08X%08X%08X--%08X%08X%08X--%08X%08X%08X--%08X%08X%08X",
                                    hid_cp_debug_paramter.usb_data[0+buf_index].timestamp,
                                    *(uint32_t *)&hid_cp_debug_paramter.usb_data[0+buf_index].data[4],
                                    *(uint32_t *)&hid_cp_debug_paramter.usb_data[0+buf_index].data[0],
                                    hid_cp_debug_paramter.usb_data[1+buf_index].timestamp,
                                    *(uint32_t *)&hid_cp_debug_paramter.usb_data[1+buf_index].data[4],
                                    *(uint32_t *)&hid_cp_debug_paramter.usb_data[1+buf_index].data[0],
                                    hid_cp_debug_paramter.usb_data[2+buf_index].timestamp,
                                    *(uint32_t *)&hid_cp_debug_paramter.usb_data[2+buf_index].data[4],
                                    *(uint32_t *)&hid_cp_debug_paramter.usb_data[2+buf_index].data[0],
                                    hid_cp_debug_paramter.usb_data[3+buf_index].timestamp,
                                    *(uint32_t *)&hid_cp_debug_paramter.usb_data[3+buf_index].data[4],
                                    *(uint32_t *)&hid_cp_debug_paramter.usb_data[3+buf_index].data[0]);
    }
#endif
}

#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE)
ATTR_TEXT_IN_TCM void hid_cp_ms_custom_protocol_data_mix_with_hid_packet_process(uint8_t *data_buf, uint16_t len)
{
    hid_critical_path_t *hid_cp_ms_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);

    /* clear custom protocol flag bit */
    data_buf[0] &= 0xBF;

    /* covert mix packet to normal packet */
    if (len == 7)
    {
        int8_t x = (int8_t)data_buf[5];
        int8_t y = (int8_t)data_buf[6];
        /* debug data */
        data_buf[1] = 0;
        /* key data */
        data_buf[2] = hid_cp_ms_ctx->ms_ctx.last_key;
        /* X/Y data */
        data_buf[3] = (uint8_t)x;
        if (x >= 0)
        {
            data_buf[4] = ((y&0xF)<<4);

        }
        else
        {
            data_buf[4] = ((y&0xF)<<4) | 0xF;
        }
        if (y >= 0)
        {
            data_buf[5] = ((y&0xF0)>>4);
        }
        else
        {
            data_buf[5] = 0xF0 | ((y&0xF0)>>4);
        }
        /* wheel data */
        data_buf[6] = 0;
    }
}
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE */

int hid_critical_path_ms_init(void)
{
    int ret = 0;
    hid_critical_path_t *hid_cp_ms_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
    LOG_INF(BT_HID_CP_TAG"HID Critical Path MS Init");
    if (hid_critical_path_get_state(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE) == HID_CP_STATE_IDLE) {
        LOG_ERR(BT_HID_CP_TAG"HID Critical Path Already Init!");
        return -EBUSY;
    }
#if defined(CONFIG_AIR_HID_PLC_CALCULATE)
    hid_plc_common_init();
#endif
    hid_critical_path_set_state(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE, HID_CP_STATE_IDLE);

    /* Obtain gaming mouse */
    hid_cp_ms_ctx->hid_dev = \
        air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_GAMING_MS);

    /* Creat USB ID  */
    ret = air_usb_create_user("HID_CRITICAL_PATH", &hid_cp_ms_ctx->usb_user_id);
    if(ret != 0)
    {
        LOG_ERR(BT_HID_CP_TAG"air_usb_create_user fail");
        return ret;
    }
    else{
        LOG_INF(BT_HID_CP_TAG"air_usb_create_user ok");
    }

    air_usb_register_evt_cb(hid_cp_ms_ctx->usb_user_id, hid_cp_usb_evt_cb);

    air_usb_hid_register_protocol_change_cb(hid_cp_ms_ctx->usb_user_id, \
                            hid_cp_ms_ctx->hid_dev, hid_cp_protocol_change_cb);

    air_usb_hid_register_tx_done_cb(hid_cp_ms_ctx->usb_user_id,
                                    hid_cp_ms_ctx->hid_dev,
                                    USB_HID_REPORT_TYPE_INPUT,
                                    REPORT_ID_MOUSE,
                                    7,
                                    hid_cp_tx_done_cb);
    return ret;
}

void hid_critical_path_ms_start(void)
{
    hid_critical_path_t *hid_cp_ms_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
#ifdef CONFIG_AIR_HID_PLC_CALCULATE
        hid_plc_common_clear();
#endif
    LOG_INF(BT_HID_CP_TAG"hid_critical_path_start mouse ,report_rate: %x", hid_cp_ms_ctx->report_rate);
    hid_cp_ms_reset_filter_duplicate();
}

void hid_critical_path_ms_stop(void)
{
    hid_critical_path_t *hid_cp_ms_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
    LOG_INF(BT_HID_CP_TAG"hid_critical_path_stop mouse, mode:%d",  hid_cp_ms_ctx->hid_protocol);
#ifdef CONFIG_AIR_HID_PLC_CALCULATE
    hid_plc_common_clear();
#endif
    if(hid_cp_ms_ctx->hid_protocol == USB_PROTOCOL_BOOT_MODE) {
        /* Prepare for boot protocol  */
        uint8_t hid_boot_data[HID_BIOS_DATA_LEN] = {0};
        hid_boot_data[0] = AIR_USB_HID_GAMING_MS_REPORT_ID;
        hid_cp_ms_data_send_to_usb(&hid_boot_data[0], HID_BIOS_DATA_LEN);
    } else if(hid_cp_ms_ctx->hid_protocol == USB_PROTOCOL_REPORT_MODE){
        uint8_t hid_report_data[sizeof(bt_ms_packet_t)] = {0};
        hid_report_data[0] = AIR_USB_HID_GAMING_MS_REPORT_ID;
        hid_cp_ms_data_send_to_usb(&hid_report_data[0], sizeof(bt_ms_packet_t));
    }
}

void hid_critical_path_ms_deinit(void)
{
    hid_critical_path_t *hid_cp_ms_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
    LOG_INF(BT_HID_CP_TAG"HID Critical Path MS DeInit");
    memset(hid_cp_ms_ctx, 0, sizeof(hid_critical_path_t));
    hid_cp_ms_ctx->bit_mask &= ~HID_CP_BIT_MASK_LAST_KEY_VAILD;
    /* Clear PLC context TBD*/
#if defined(CONFIG_AIR_HID_PLC_CALCULATE)
    hid_plc_common_clear();
#endif
}

/* End of file */
