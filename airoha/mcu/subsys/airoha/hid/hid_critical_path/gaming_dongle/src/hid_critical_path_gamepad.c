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

#include "hid_critical_path_gamepad.h"

#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE)
#define JOYSTICK_0_LEVEL_VALUE 0x8000
static uint8_t usb_tx_send_failed_flush_count = 0;
#define USB_TX_SEND_FAILED_FLUSH_COUNT_MAX 10
#define APP_HID_INT_IN_EP_IDX  0
#define APP_HID_INT_OUT_EP_IDX 1
#endif /* CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE */

#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE)
ATTR_ZIDATA_IN_TCM T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S gc_usb_payload_record;
ATTR_ZIDATA_IN_TCM static bool hid_cp_usb_tx_running_flag_game_controller = false;
ATTR_ZIDATA_IN_TCM static bool hid_cp_game_controller_filter_duplicate_flag = false;
ATTR_ZIDATA_IN_TCM static T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S hid_cp_game_controller_filter_duplicate_record;
#if defined(AIR_HID_DUMMY_REPORT_RATE)
uint32_t game_controller_dummy_data_count = 0;
ATTR_ZIDATA_IN_TCM static bool hid_cp_game_controller_button_filter_duplicate_flag = false;
ATTR_ZIDATA_IN_TCM static T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S hid_cp_game_controller_button_filter_duplicate_record;
#endif/*AIR_HID_DUMMY_REPORT_RATE*/
#endif /* CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE */

#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE)
ATTR_TEXT_IN_TCM void hid_cp_game_controller_reset_filter_duplicate(void)
{
    hid_cp_game_controller_filter_duplicate_flag = false;
}

#if defined(AIR_HID_DUMMY_REPORT_RATE)
ATTR_TEXT_IN_TCM void hid_cp_game_controller_reset_button_filter_duplicate(void)
{
    hid_cp_game_controller_button_filter_duplicate_flag = false;
}
#endif/*AIR_HID_DUMMY_REPORT_RATE*/

ATTR_TEXT_IN_TCM bool hid_cp_game_controller_check_filter_duplicate(uint8_t* data, uint16_t len)
{
    bool ret = false;
    T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S *p_gc_usb_payload = (T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S *)data;

    if (hid_cp_game_controller_filter_duplicate_flag)
    {
        if ((p_gc_usb_payload->report_id == REPORT_ID_GAME_CONTROLLER)
            && (p_gc_usb_payload->hat_switch == hid_cp_game_controller_filter_duplicate_record.hat_switch)
            && (p_gc_usb_payload->button == hid_cp_game_controller_filter_duplicate_record.button)
            && (p_gc_usb_payload->breake == 0) && (hid_cp_game_controller_filter_duplicate_record.breake == 0)
            && (p_gc_usb_payload->accelerator == 0) && (hid_cp_game_controller_filter_duplicate_record.accelerator == 0)
            && (p_gc_usb_payload->x == JOYSTICK_0_LEVEL_VALUE) && (hid_cp_game_controller_filter_duplicate_record.x == JOYSTICK_0_LEVEL_VALUE)
            && (p_gc_usb_payload->y == JOYSTICK_0_LEVEL_VALUE) && (hid_cp_game_controller_filter_duplicate_record.y == JOYSTICK_0_LEVEL_VALUE)
            && (p_gc_usb_payload->z == JOYSTICK_0_LEVEL_VALUE) && (hid_cp_game_controller_filter_duplicate_record.z == JOYSTICK_0_LEVEL_VALUE)
            && (p_gc_usb_payload->rz == JOYSTICK_0_LEVEL_VALUE) && (hid_cp_game_controller_filter_duplicate_record.rz == JOYSTICK_0_LEVEL_VALUE)
            )
        {
            /* if the buttons are not changed
            and the triggers are not presssed
            and the joysitcks are not used,
            the data is duplicated */
            ret = true;
        }
    }

    return ret;
}

#if defined(AIR_HID_DUMMY_REPORT_RATE)
ATTR_TEXT_IN_TCM bool hid_cp_game_controller_check_button_filter_duplicate(uint8_t* data, uint16_t len)
{
    bool ret = false;
    T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S *p_gc_usb_payload = (T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S *)data;

    if (hid_cp_game_controller_button_filter_duplicate_flag)
    {
        if ((p_gc_usb_payload->report_id == REPORT_ID_GAME_CONTROLLER)
            && (p_gc_usb_payload->hat_switch == hid_cp_game_controller_button_filter_duplicate_record.hat_switch)
            && (p_gc_usb_payload->button == hid_cp_game_controller_button_filter_duplicate_record.button)
            )
        {
            /* if the buttons are not changed
            and the triggers are not presssed
            and the joysitcks are not used,
            the data is duplicated */
            ret = true;
        }
    }

    return ret;
}
#endif/*AIR_HID_DUMMY_REPORT_RATE*/

ATTR_TEXT_IN_TCM void hid_cp_game_controller_update_filter_duplicate(uint8_t* data, uint16_t len)
{
    // T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S *p_gc_usb_payload = (T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S *)data;

    // hid_cp_game_controller_filter_duplicate_record.hat_switch = p_gc_usb_payload->hat_switch;
    // hid_cp_game_controller_filter_duplicate_record.button = p_gc_usb_payload->button;
    memcpy((void *)&hid_cp_game_controller_filter_duplicate_record, (void *)data, len);
    hid_cp_game_controller_filter_duplicate_flag = true;
}

#if defined(AIR_HID_DUMMY_REPORT_RATE)
ATTR_TEXT_IN_TCM void hid_cp_game_controller_update_button_filter_duplicate(uint8_t* data, uint16_t len)
{
    T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S *p_gc_usb_payload = (T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S *)data;

    hid_cp_game_controller_button_filter_duplicate_record.hat_switch = p_gc_usb_payload->hat_switch;
    hid_cp_game_controller_button_filter_duplicate_record.button = p_gc_usb_payload->button;
    hid_cp_game_controller_button_filter_duplicate_flag  = true;
}
#endif/*AIR_HID_DUMMY_REPORT_RATE*/

void hid_cp_gp_sw_isr_callback(void)
{
    hid_critical_path_t *hid_cp_game_controller_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_GAME_CONTROLLER);
    hid_cp_debug_log(hid_cp_game_controller_ctx->report_rate);
#ifdef CONFIG_AIR_HID_CP_DEBUG_LOG
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

#if defined(AIR_USB_XINPUT_ENABLE)
ATTR_TEXT_IN_TCM void hid_cp_game_controller_covert_xinput_format(T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S *in_data, uint16_t in_len, T_HID_REPORT_GAME_CONTROLLER_XINPUT_PAYLOAD_S *out_data, uint16_t out_len)
{
    int32_t temp32 = 0;
    uint8_t hat_switch;

    memset(out_data, 0, out_len);
    out_data->report_id = 0x0;
    out_data->report_size = 0x14;

    /* button process */
    /* Bit Field Description
        0 Dpad Up Dpad Up switch
        1 Dpad Down Dpad Down switch
        2 Dpad Left Dpad Left switch
        3 Dpad Right Dpad Right switch
        4 Start Start button
        5 Back Back button
        6 Left Thumbswitch Left Joystick switch
        7 Right Thumbswitch Right Joystick switch
        8 LeftShoulder Left Shoulder switch
        9 RightShoulder Right Shoulder switch
        10 Xe Xe Switch
        11 Binding Binding Switch
        12 A A button
        13 B B button
        14 X X button
        15 Y Y button
    */
    hat_switch = (in_data->hat_switch & 0x0f);
    switch (hat_switch)
    {
        case 0x1:
            hat_switch = 0x1; /* UP */
            break;

        case 0x2:
            hat_switch = 0x9; /* UP + RIGHT */
            break;

        case 0x3:
            hat_switch = 0x8; /* LEFT */
            break;

        case 0x4:
            hat_switch = 0xA; /* RIGHT + DOWN */
            break;

        case 0x5:
            hat_switch = 0x2; /* DOWN */
            break;

        case 0x6:
            hat_switch = 0x6; /* DOWN + LEFT */
            break;

        case 0x7:
            hat_switch = 0x4; /* LEFT */
            break;

        case 0x8:
            hat_switch = 0x5; /* LEFT + UP */
            break;

        default:
            break;
    }
    out_data->button = hat_switch
                        | (((in_data->button & 0x0600) >> 9) << 4)
                        | (((in_data->button & 0x00f0) >> 4) << 6)
                        | (((in_data->button & 0x0100) >> 8) << 10)
                        | ((in_data->button & 0x000f) << 12);

    /* trigger process */
    out_data->left_trigger = (in_data->breake >> 2) & 0xff;
    out_data->right_trigger = (in_data->accelerator >> 2) & 0xff;

    /* joystick data process */
    temp32 = in_data->x - JOYSTICK_0_LEVEL_VALUE;
    if (temp32 > 32767)
    {
        temp32 = 32767;
    }
    else if (temp32 < -32768)
    {
        temp32 = -32768;
    }
    out_data->left_x = temp32;
    temp32 = JOYSTICK_0_LEVEL_VALUE - in_data->y;
    if (temp32 > 32767)
    {
        temp32 = 32767;
    }
    else if (temp32 < -32768)
    {
        temp32 = -32768;
    }
    out_data->left_y = temp32;
    temp32 = in_data->z - JOYSTICK_0_LEVEL_VALUE;
    if (temp32 > 32767)
    {
        temp32 = 32767;
    }
    else if (temp32 < -32768)
    {
        temp32 = -32768;
    }
    out_data->right_x = temp32;
    temp32 = JOYSTICK_0_LEVEL_VALUE - in_data->rz;
    if (temp32 > 32767)
    {
        temp32 = 32767;
    }
    else if (temp32 < -32768)
    {
        temp32 = -32768;
    }
    out_data->right_y = temp32;
}
#endif /* AIR_USB_XINPUT_ENABLE */

#if defined(AIR_HID_DUMMY_REPORT_RATE)
static uint8_t hid_cp_game_controller_dummy_data_rr_cover_to_index(bt_ull_le_hid_srv_report_rate_level_t rr_level)
{
    uint8_t rr_index= 1;
    switch (rr_level) {
        case BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_2:
            rr_index = 64;
            break;
        case BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_3:
            rr_index = 32;
            break;
        case BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_4:
            rr_index = 16;
            break;
        case BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_5:
            rr_index = 8;
            break;
        case BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_6:
            rr_index = 4;
            break;
        case BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_7:
            rr_index = 2;
            break;
        case BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_8:
            rr_index = 1;
            break;
        default:
            rr_index = 1;
            break;
    }
    return rr_index;
}

ATTR_TEXT_IN_TCM static bool hid_cp_game_controller_dummy_data_process(uint8_t* data, uint16_t len)
{
    uint8_t index;
    hid_critical_path_t *hid_cp_game_controller_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_GAME_CONTROLLER);
    index = hid_cp_game_controller_dummy_data_rr_cover_to_index(hid_cp_game_controller_ctx->report_rate);

    /*check if send to usb */
    if(((game_controller_dummy_data_count++)%index) == 0)
    {
        return true;
    }
    else{
        return false;
    }
}
#endif/*(AIR_HID_DUMMY_REPORT_RATE)*/

ATTR_TEXT_IN_TCM static int hid_cp_game_controller_data_send_to_usb(uint8_t* data, uint16_t len)
{
    int send_result = 0;
    hid_critical_path_t *hid_cp_game_controller_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_GAME_CONTROLLER);

#if defined(AIR_HID_DUMMY_REPORT_RATE)
    if(hid_cp_game_controller_dummy_data_process(data,len) == true)
    {
        /* check if it is duplicate */
            if (hid_cp_game_controller_check_filter_duplicate(data, len) == false)
            {
        #if defined(AIR_USB_XINPUT_ENABLE)
                if (hid_scenario_dongle_usb_mode_check() == USB_MODE_HID)
                {
                    send_result = air_usb_hid_tx(hid_cp_game_controller_ctx->usb_user_id, \
                                hid_cp_game_controller_ctx->hid_dev, len, data);
                }
                else
                {
                    T_HID_REPORT_GAME_CONTROLLER_XINPUT_PAYLOAD_S xusb_data;
                    hid_cp_game_controller_covert_xinput_format((T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S *)data, len, &xusb_data, sizeof(T_HID_REPORT_GAME_CONTROLLER_XINPUT_PAYLOAD_S));
                    send_result = air_usb_xinput_tx(hid_cp_game_controller_ctx->usb_user_id, \
                                hid_cp_game_controller_ctx->hid_dev, sizeof(T_HID_REPORT_GAME_CONTROLLER_XINPUT_PAYLOAD_S), (uint8_t *)&xusb_data);
                }
        #else
                send_result = air_usb_hid_tx(hid_cp_game_controller_ctx->usb_user_id, \
                            hid_cp_game_controller_ctx->hid_dev, len, data);
        #endif /* AIR_USB_XINPUT_ENABLE */
                if (send_result == 0)
                {
                    hid_cp_game_controller_update_button_filter_duplicate(data, len);
                }
            }
    }else
    {
        if (hid_cp_game_controller_check_button_filter_duplicate(data, len) == false)
        {
        #if defined(AIR_USB_XINPUT_ENABLE)
                if (hid_scenario_dongle_usb_mode_check() == USB_MODE_HID)
                {
                    send_result = air_usb_hid_tx(hid_cp_game_controller_ctx->usb_user_id, \
                                hid_cp_game_controller_ctx->hid_dev, len, data);
                }
                else
                {
                    T_HID_REPORT_GAME_CONTROLLER_XINPUT_PAYLOAD_S xusb_data;
                    hid_cp_game_controller_covert_xinput_format((T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S *)data, len, &xusb_data, sizeof(T_HID_REPORT_GAME_CONTROLLER_XINPUT_PAYLOAD_S));
                    send_result = air_usb_xinput_tx(hid_cp_game_controller_ctx->usb_user_id, \
                                hid_cp_game_controller_ctx->hid_dev, sizeof(T_HID_REPORT_GAME_CONTROLLER_XINPUT_PAYLOAD_S), (uint8_t *)&xusb_data);
                }
        #else
            send_result = air_usb_hid_tx(hid_cp_game_controller_ctx->usb_user_id, \
                        hid_cp_game_controller_ctx->hid_dev, len, data);
        #endif /* AIR_USB_XINPUT_ENABLE */
            if (send_result == 0)
            {
                hid_cp_game_controller_update_button_filter_duplicate(data, len);
                game_controller_dummy_data_count = 0;
            }
        }
    }

    return send_result;
#endif/*AIR_HID_DUMMY_REPORT_RATE*/

    /* check if it is duplicate */
    if (hid_cp_game_controller_check_filter_duplicate(data, len) == false)
    {
#if defined(AIR_USB_XINPUT_ENABLE)
        if (hid_scenario_dongle_usb_mode_check() == USB_MODE_HID)
        {
            send_result = air_usb_hid_tx(hid_cp_game_controller_ctx->usb_user_id, \
                        hid_cp_game_controller_ctx->hid_dev, len, data);
        }
        else
        {
            T_HID_REPORT_GAME_CONTROLLER_XINPUT_PAYLOAD_S xusb_data;
            hid_cp_game_controller_covert_xinput_format((T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S *)data, len, &xusb_data, sizeof(T_HID_REPORT_GAME_CONTROLLER_XINPUT_PAYLOAD_S));
            send_result = air_usb_xinput_tx(hid_cp_game_controller_ctx->usb_user_id, \
                        hid_cp_game_controller_ctx->hid_dev, sizeof(T_HID_REPORT_GAME_CONTROLLER_XINPUT_PAYLOAD_S), (uint8_t *)&xusb_data);
        }
#else
        send_result = air_usb_hid_tx(hid_cp_game_controller_ctx->usb_user_id, \
                    hid_cp_game_controller_ctx->hid_dev, len, data);
#endif /* AIR_USB_XINPUT_ENABLE */
        if (send_result == 0)
        {
            hid_cp_game_controller_update_filter_duplicate(data, len);
            usb_tx_send_failed_flush_count = 0;
        }else
        {
            // LOG_INF(BT_HID_CP_TAG"send_result-%d",send_result);
            usb_tx_send_failed_flush_count ++;
            if(usb_tx_send_failed_flush_count > USB_TX_SEND_FAILED_FLUSH_COUNT_MAX)
            {
                air_usb_ep_flush(hid_cp_game_controller_ctx->usb_user_id,hid_cp_game_controller_ctx->hid_dev,APP_HID_INT_IN_EP_IDX);
                usb_tx_send_failed_flush_count = 0;
            }
        }
    }

    return send_result;
}

ATTR_TEXT_IN_TCM hid_critical_path_status_t hid_cp_game_controller(uint8_t* data, uint16_t len, usb_plc_cb_param *plc_param)
{
    if (plc_param->reason == HID_PLC_REASON_DUP_PKT){
        return HID_CP_STATUS_FAIL;
    }
    hid_critical_path_status_t status = HID_CP_STATUS_SUCCESS;
    hid_critical_path_t *hid_cp_game_controller_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_GAME_CONTROLLER);
    T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S gc_usb_payload;
    int send_result = 0;
    int32_t x,y,z,rz;

    if ((data == NULL) || (len == 0)) {
        LOG_ERR(BT_HID_CP_TAG"Invalid data for hid_cp_game_controller");
        status = HID_CP_STATUS_FAIL;
        return status;
    }

    ARG_UNUSED(plc_param);

    /* handle report first */
    #if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_HIX_MIXING_ENABLE)
    uint8_t report_id = data[0] & 0x3F;
    #else
    uint8_t report_id = data[0] & 0x7F;
    #endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_HIX_MIXING_ENABLE */
    switch(report_id){
        case REPORT_ID_GAME_CONTROLLER:
            gc_usb_payload.report_id = REPORT_ID_GAME_CONTROLLER;
            /* process joysitck data */
            #if defined(CONFIG_AIR_GAME_CONTROLLER_12BIT_ADC)
            x = (data[1] | ((data[2] & 0x0f) << 8))<<4;
            if ((x & 0x8000) != 0)
            {
                x = 0xFFFF0000 | x;
            }
            y = (((data[2] & 0xf0)>>4) | (data[3]<< 4))<<4;
            if ((y & 0x8000) != 0)
            {
                y = 0xFFFF0000 | y;
            }
            z = (data[4] | ((data[5] & 0x0f) << 8))<<4;
            if ((z & 0x8000) != 0)
            {
                z = 0xFFFF0000 | z;
            }
            rz = (((data[5] & 0xf0)>>4) | (data[6]<< 4))<<4;
            if ((rz & 0x8000) != 0)
            {
                rz = 0xFFFF0000 | rz;
            }
            #if defined(CONFIG_AIR_GAME_CONTROLLER_9B_DATA)
            gc_usb_payload.button = data[7] | (data[8] << 8);
            #else
            gc_usb_payload.button = gc_usb_payload_record.button;
            #endif
            #else
            x = data[1] | (data[2] << 8);
            y = data[3] | (data[4] << 8);
            z = data[5] | (data[6] << 8);
            rz = data[7] | (data[8] << 8);
            gc_usb_payload.button = gc_usb_payload_record.button;
            #endif
            gc_usb_payload.x  = (uint16_t)(JOYSTICK_0_LEVEL_VALUE + x);
            gc_usb_payload.y  = (uint16_t)(JOYSTICK_0_LEVEL_VALUE + y);
            gc_usb_payload.z  = (uint16_t)(JOYSTICK_0_LEVEL_VALUE + z);
            gc_usb_payload.rz = (uint16_t)(JOYSTICK_0_LEVEL_VALUE + rz);
            gc_usb_payload_record.x  = gc_usb_payload.x;
            gc_usb_payload_record.y  = gc_usb_payload.y;
            gc_usb_payload_record.z  = gc_usb_payload.z;
            gc_usb_payload_record.rz = gc_usb_payload.rz;
            /* process trigger data */
            gc_usb_payload.breake = gc_usb_payload_record.breake;
            gc_usb_payload.accelerator = gc_usb_payload_record.accelerator;
            /* process button data */
            gc_usb_payload.hat_switch = gc_usb_payload_record.hat_switch;
            gc_usb_payload.record = 0;
            break;

        case REPORT_ID_GAME_CONTROLLER_GROUP0:
        case REPORT_ID_GAME_CONTROLLER_GROUP1:
        case REPORT_ID_GAME_CONTROLLER_GROUP2:
            gc_usb_payload.report_id = REPORT_ID_GAME_CONTROLLER;
            /* process button data */
            gc_usb_payload.record = 0;
            if (report_id == REPORT_ID_GAME_CONTROLLER_GROUP0 ) {
                gc_usb_payload.button = (gc_usb_payload_record.button & 0xFF00) | data[1];
            } else if (report_id == REPORT_ID_GAME_CONTROLLER_GROUP1) {
                gc_usb_payload.button = (gc_usb_payload_record.button & 0x00FF) | (data[1] << 8);
            } else if (report_id == REPORT_ID_GAME_CONTROLLER_GROUP2) {
                /* reserved for future use */
                gc_usb_payload.button = gc_usb_payload_record.button;
            }
            gc_usb_payload_record.button = gc_usb_payload.button;
            gc_usb_payload.hat_switch = data[2] & 0x0f;
            gc_usb_payload_record.hat_switch = gc_usb_payload.hat_switch;
            /* process trigger data */
            gc_usb_payload.breake = ((data[2] & 0xf0)>>4) | ((data[3] & 0x3f)<<4);
            gc_usb_payload_record.breake = gc_usb_payload.breake;
            gc_usb_payload.accelerator = ((data[3] & 0xC0)>>6) | (data[4]<<2);
            gc_usb_payload_record.accelerator = gc_usb_payload.accelerator;
            /* process joystick */
            #if defined(CONFIG_AIR_GAME_CONTROLLER_9B_DATA)
            x   = (int32_t)((int8_t)data[5]);
            y   = (int32_t)((int8_t)data[6]);
            z   = (int32_t)((int8_t)data[7]);
            rz  = (int32_t)((int8_t)data[8]);
            #else
            gc_usb_payload.x = data[5] & 0x0f;
            gc_usb_payload.y = (data[5] & 0xf0)>>4;
            gc_usb_payload.z = (data[6] & 0x0f);
            gc_usb_payload.rz = (data[6] & 0xf0)>>4;
            #endif
            gc_usb_payload.x = (uint16_t)(x + gc_usb_payload_record.x);
            gc_usb_payload_record.x  = gc_usb_payload.x;
            gc_usb_payload.y = (uint16_t)(y + gc_usb_payload_record.y);
            gc_usb_payload_record.y  = gc_usb_payload.y;
            gc_usb_payload.z = (uint16_t)(z + gc_usb_payload_record.z);
            gc_usb_payload_record.z  = gc_usb_payload.z;
            gc_usb_payload.rz = (uint16_t)(rz + gc_usb_payload_record.rz);
            gc_usb_payload_record.rz = gc_usb_payload.rz;
            break;

        case REPORT_ID_GAME_CONTROLLER_ALL_IN_ONE:
            gc_usb_payload.report_id = REPORT_ID_GAME_CONTROLLER;
            /* process joysitck data */
            x = data[1] | (data[2] << 8);
            y = data[3] | (data[4] << 8);
            z = data[5] | (data[6] << 8);
            rz = data[7] | (data[8] << 8);
            gc_usb_payload.x  = (uint16_t)(x);
            gc_usb_payload.y  = (uint16_t)(y);
            gc_usb_payload.z  = (uint16_t)(z);
            gc_usb_payload.rz = (uint16_t)(rz);
            gc_usb_payload_record.x  = gc_usb_payload.x;
            gc_usb_payload_record.y  = gc_usb_payload.y;
            gc_usb_payload_record.z  = gc_usb_payload.z;
            gc_usb_payload_record.rz = gc_usb_payload.rz;
            /* process trigger data */
            gc_usb_payload.breake = data[9] | (data[10] << 8);
            gc_usb_payload_record.breake = gc_usb_payload.breake;
            gc_usb_payload.accelerator = data[11] | (data[12] << 8);
            gc_usb_payload_record.accelerator = gc_usb_payload.accelerator;
            /* process button data */
            gc_usb_payload.hat_switch = data[13] & 0x0f;
            gc_usb_payload_record.hat_switch = gc_usb_payload.hat_switch;
            gc_usb_payload.button = data[14] | (data[15] << 8);
            gc_usb_payload_record.button = gc_usb_payload.button;
            gc_usb_payload.record = 0;
            break;

        default:
            status = HID_CP_STATUS_FAIL;
            __ASSERT_NO_MSG(0);
            break;
    }

    if (hid_cp_usb_tx_running_flag_game_controller)
    {
        /* the last packet is senting in USB TX Done callback, so try to resend this packet in the next TX Done callback */
        send_result = -1;
    }
    else
    {
        /* try to send this packet */
        send_result = hid_cp_game_controller_data_send_to_usb((uint8_t*)(&gc_usb_payload), sizeof(gc_usb_payload));
    }
    if (send_result != 0)
    {
        /* USB Send fail, try to re-send in USB TX Done callback */
        hid_cp_game_controller_ctx->gp_ctx.resend_data.q_flag = true;
        memcpy(&hid_cp_game_controller_ctx->gp_ctx.resend_data.data_game_controller, &gc_usb_payload, sizeof(gc_usb_payload));
        status = HID_CP_STATUS_FAIL;
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
        hal_gpio_set_output(HID_CP_DEBUG_GPIO_3, HAL_GPIO_DATA_HIGH);
#endif
        hid_cp_debug_paramter.send_to_usb_fail_bt ++;
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
        hal_gpio_set_output(HID_CP_DEBUG_GPIO_3, HAL_GPIO_DATA_LOW);
#endif
    }
    else
    {
        /* USB Send sucesss */
        hid_cp_debug_paramter.send_to_usb_suc ++;
        hid_cp_game_controller_ctx->gp_ctx.resend_data.q_flag = false;
    }
    return status;
}

ATTR_TEXT_IN_TCM static int hid_cp_game_controller_tx_done_cb(const struct device *dev, uint8_t type, uint8_t id,
				    uint16_t len, const uint8_t *buf)
{
    uint32_t mask;
    hid_critical_path_t *hid_cp_game_controller_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_GAME_CONTROLLER);
    T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S gc_usb_payload;
    int send_result;
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
    hal_gpio_set_output(HID_CP_DEBUG_GPIO_5, HAL_GPIO_DATA_HIGH);
#endif
    hid_cp_debug_paramter.tx_done_cb_count++;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    if (hid_cp_game_controller_ctx->gp_ctx.resend_data.q_flag)
    {
        hid_cp_game_controller_ctx->gp_ctx.resend_data.q_flag = false;
        memcpy(&gc_usb_payload, &hid_cp_game_controller_ctx->gp_ctx.resend_data.data_game_controller, sizeof(gc_usb_payload));
        hid_cp_usb_tx_running_flag_game_controller = true;
    }
    hal_nvic_restore_interrupt_mask(mask);

    if (hid_cp_usb_tx_running_flag_game_controller)
    {
        hid_cp_game_controller_reset_filter_duplicate();
        #if defined(AIR_HID_DUMMY_REPORT_RATE)
        hid_cp_game_controller_reset_button_filter_duplicate();
        #endif/*AIR_HID_DUMMY_REPORT_RATE*/
        send_result = hid_cp_game_controller_data_send_to_usb((uint8_t*)(&gc_usb_payload), sizeof(gc_usb_payload));
        if (send_result != 0) {
            hid_cp_debug_paramter.send_to_usb_fail_usb ++;
        } else {
            hid_cp_debug_paramter.send_to_usb_suc ++;
        }
        hid_cp_usb_tx_running_flag_game_controller = false;
    }
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
    hal_gpio_set_output(HID_CP_DEBUG_GPIO_5, HAL_GPIO_DATA_LOW);
#endif
    return 0;
}

#ifdef AIR_USB_XINPUT_ENABLE
ATTR_TEXT_IN_TCM static int hid_cp_game_controller_xinput_tx_done_cb(const struct device *dev)
{
    uint32_t mask;
    hid_critical_path_t *hid_cp_game_controller_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_GAME_CONTROLLER);
    T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S gc_usb_payload;
    int send_result;
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
    hal_gpio_set_output(HID_CP_DEBUG_GPIO_5, HAL_GPIO_DATA_HIGH);
#endif
    hid_cp_debug_paramter.tx_done_cb_count++;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    if (hid_cp_game_controller_ctx->gp_ctx.resend_data.q_flag)
    {
        hid_cp_game_controller_ctx->gp_ctx.resend_data.q_flag = false;
        memcpy(&gc_usb_payload, &hid_cp_game_controller_ctx->gp_ctx.resend_data.data_game_controller, sizeof(gc_usb_payload));
        hid_cp_usb_tx_running_flag_game_controller = true;
    }
    hal_nvic_restore_interrupt_mask(mask);

    if (hid_cp_usb_tx_running_flag_game_controller)
    {
        hid_cp_game_controller_reset_filter_duplicate();
        #if defined(AIR_HID_DUMMY_REPORT_RATE)
        hid_cp_game_controller_reset_button_filter_duplicate();
        #endif/*AIR_HID_DUMMY_REPORT_RATE*/
        send_result = hid_cp_game_controller_data_send_to_usb((uint8_t*)(&gc_usb_payload), sizeof(gc_usb_payload));
        if (send_result != 0) {
            hid_cp_debug_paramter.send_to_usb_fail_usb ++;
        } else {
            hid_cp_debug_paramter.send_to_usb_suc ++;
        }
        hid_cp_usb_tx_running_flag_game_controller = false;
    }
#if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
    hal_gpio_set_output(HID_CP_DEBUG_GPIO_5, HAL_GPIO_DATA_LOW);
#endif
    return 0;
}
#endif /* AIR_USB_XINPUT_ENABLE */
#endif /* CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE */

int hid_critical_path_gamepad_init(void)
{
    int ret = 0;
    LOG_INF(BT_HID_CP_TAG"HID Critical Path GP Init");
#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE)
    hid_critical_path_t *hid_cp_game_controller_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_GAME_CONTROLLER);

    if (hid_critical_path_get_state(HID_CRITICAL_PATH_DEVICE_TYPE_GAME_CONTROLLER) == HID_CP_STATE_IDLE) {
        LOG_ERR(BT_HID_CP_TAG"HID Critical Path Already Init!");
        return -EBUSY;
    }

    memset(hid_cp_game_controller_ctx, 0, sizeof(hid_critical_path_t));
    hid_critical_path_set_state(HID_CRITICAL_PATH_DEVICE_TYPE_GAME_CONTROLLER, HID_CP_STATE_IDLE);
    hid_cp_game_controller_ctx->hid_dev = \
        air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_GAMEPAD);

    /* Creat USB ID  */
    ret = air_usb_create_user("HID_CRITICAL_PATH", &hid_cp_game_controller_ctx->usb_user_id);
    if(ret != 0)
    {
        LOG_ERR(BT_HID_CP_TAG"air_usb_create_user for game controller fail");
        return ret;
    }
    else{
        LOG_INF(BT_HID_CP_TAG"air_usb_create_user for game controller ok");
    }

    air_usb_hid_register_protocol_change_cb(hid_cp_game_controller_ctx->usb_user_id, \
                            hid_cp_game_controller_ctx->hid_dev, hid_cp_protocol_change_cb);
    air_usb_hid_register_tx_done_cb(hid_cp_game_controller_ctx->usb_user_id,
                                    hid_cp_game_controller_ctx->hid_dev,
                                    USB_HID_REPORT_TYPE_INPUT,
                                    REPORT_ID_GAME_CONTROLLER,
                                    sizeof(T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S),
                                    hid_cp_game_controller_tx_done_cb);
#ifdef AIR_USB_XINPUT_ENABLE
    if (hid_scenario_dongle_usb_mode_check() == USB_MODE_XINPUT) {
        hid_cp_game_controller_ctx->hid_dev = hid_scenario_dongle_get_xinput_dev();
    air_usb_xinput_register_tx_done_cb(hid_cp_game_controller_ctx->usb_user_id,
                                    hid_cp_game_controller_ctx->hid_dev,
                                    hid_cp_game_controller_xinput_tx_done_cb);
    }
#endif /* AIR_USB_XINPUT_ENABLE */
#endif /* CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE */

    return ret;
}

void hid_critical_path_gamepad_start(void)
{
#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE)
    hid_cp_game_controller_reset_filter_duplicate();
    #if defined(AIR_HID_DUMMY_REPORT_RATE)
    hid_cp_game_controller_reset_button_filter_duplicate();
    #endif/*AIR_HID_DUMMY_REPORT_RATE*/
    memset((void *)(&gc_usb_payload_record), 0, sizeof(gc_usb_payload_record));
    gc_usb_payload_record.report_id = REPORT_ID_GAME_CONTROLLER;
    gc_usb_payload_record.x  = JOYSTICK_0_LEVEL_VALUE;
    gc_usb_payload_record.y  = JOYSTICK_0_LEVEL_VALUE;
    gc_usb_payload_record.z  = JOYSTICK_0_LEVEL_VALUE;
    gc_usb_payload_record.rz = JOYSTICK_0_LEVEL_VALUE;
#endif
}

void hid_critical_path_gamepad_stop(void)
{
#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE)
    hid_cp_game_controller_reset_filter_duplicate();
    #if defined(AIR_HID_DUMMY_REPORT_RATE)
    hid_cp_game_controller_reset_button_filter_duplicate();
    #endif/*AIR_HID_DUMMY_REPORT_RATE*/
    memset((void *)(&gc_usb_payload_record), 0, sizeof(gc_usb_payload_record));
    gc_usb_payload_record.report_id = REPORT_ID_GAME_CONTROLLER;
    gc_usb_payload_record.x  = JOYSTICK_0_LEVEL_VALUE;
    gc_usb_payload_record.y  = JOYSTICK_0_LEVEL_VALUE;
    gc_usb_payload_record.z  = JOYSTICK_0_LEVEL_VALUE;
    gc_usb_payload_record.rz = JOYSTICK_0_LEVEL_VALUE;
    hid_cp_game_controller_data_send_to_usb((uint8_t *)&gc_usb_payload_record, sizeof(gc_usb_payload_record));
    hid_cp_game_controller_reset_filter_duplicate();
    #if defined(AIR_HID_DUMMY_REPORT_RATE)
    hid_cp_game_controller_reset_button_filter_duplicate();
    #endif/*AIR_HID_DUMMY_REPORT_RATE*/
#endif /* CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE */
}

void hid_critical_path_gamepad_deinit(void)
{
    LOG_INF(BT_HID_CP_TAG"HID Critical Path GP DeInit");
#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE)
    hid_critical_path_t *hid_cp_game_controller_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_GAME_CONTROLLER);
    memset(hid_cp_game_controller_ctx, 0, sizeof(hid_critical_path_t));
    hid_cp_game_controller_ctx->bit_mask &= ~HID_CP_BIT_MASK_LAST_KEY_VAILD;
#endif
}


/* End of file */
