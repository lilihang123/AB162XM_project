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

#include "hid_critical_path_common.h"
#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE)
#include "hal_nvic.h"
#include <assert.h>
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE */

LOG_MODULE_REGISTER(HID_CRITICAL_PATH);

bool hid_cp_usb_tx_running_flag = false;
hid_cp_debug_paramter_t hid_cp_debug_paramter;
hid_critical_path_t hid_critical_path_ctx[HID_CRITICAL_PATH_DEVICE_TYPE_MAX_NUM];
static hid_cp_debug_callback_t hid_cp_debug_info_cb = NULL;
#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE)
static hid_critical_path_custom_protocol_data_t hid_cp_custom_protocol_data;
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE */

#ifdef CONFIG_AIR_HID_CP_DEBUG_GPIO
T_LA_DEBUG_CFG_S la_dbg_pin[] =
{
    #if 1
    {HID_CP_DEBUG_GPIO_1, PINMUX_FUN_GPIO },
    {HID_CP_DEBUG_GPIO_2, PINMUX_FUN_GPIO },
    {HID_CP_DEBUG_GPIO_3, PINMUX_FUN_GPIO },
    {HID_CP_DEBUG_GPIO_4, PINMUX_FUN_GPIO },
    {HID_CP_DEBUG_GPIO_5, PINMUX_FUN_GPIO },
    {HID_CP_DEBUG_GPIO_6, PINMUX_FUN_GPIO },
    #endif

    #if defined(AIR_DONGLE_OF_KEYBOARD_M607)
    {14, PINMUX_FUN_HW_CTRL_DEBUG }, // BT dbg TX
    {45, PINMUX_FUN_HW_CTRL_DEBUG }, // BT dbg RX
    #else
    {24, PINMUX_FUN_HW_CTRL_DEBUG }, // BT dbg
    {23, PINMUX_FUN_HW_CTRL_DEBUG }, // BT dbg
    #endif

    #if 0
    {25, PINMUX_FUN_HW_CTRL_DEBUG }, // BT dbg

    {22, PINMUX_FUN_HW_CTRL_DEBUG }, // BT dbg
    {21, PINMUX_FUN_HW_CTRL_DEBUG }, // BT dbg
    {20, PINMUX_FUN_HW_CTRL_DEBUG }, // BT dbg
    {19, PINMUX_FUN_HW_CTRL_DEBUG }, // BT dbg
    {18, PINMUX_FUN_HW_CTRL_DEBUG }, // BT dbg
    {17, PINMUX_FUN_HW_CTRL_DEBUG }, // BT dbg

    {6, PINMUX_FUN_HW_CTRL_DEBUG }, // BT dbg
    {5, PINMUX_FUN_HW_CTRL_DEBUG }, // BT dbg
    {4, PINMUX_FUN_HW_CTRL_DEBUG }, // BT dbg

    {35, PINMUX_FUN_HW_CTRL_DEBUG }, // BT dbg
    {34, PINMUX_FUN_HW_CTRL_DEBUG }, // BT dbg

    {1, PINMUX_FUN_HW_CTRL_DEBUG }, // BT dbg
    {0, PINMUX_FUN_HW_CTRL_DEBUG }, // BT dbg
    #endif
};
#endif

ATTR_TEXT_IN_TCM void hid_critical_path_common_init(void)
{
#ifdef CONFIG_AIR_HID_CP_DEBUG_GPIO
    la_debug_init(la_dbg_pin, sizeof(la_dbg_pin)/sizeof(T_LA_DEBUG_CFG_S), 62,  false);
#endif
    memset(&hid_critical_path_ctx, 0, sizeof(hid_critical_path_t)*HID_CRITICAL_PATH_DEVICE_TYPE_MAX_NUM);
}

hid_critical_path_t *hid_critical_path_common_get_ctx(hid_critical_path_device_type_t type)
{
    return &hid_critical_path_ctx[type];
}

ATTR_TEXT_IN_TCM int32_t hid_cp_convert_data_extended(int16_t data)
{
    /* int12 -> int32 */
    if(data & 0x0800) {
        return (int32_t)(data | 0xFFFFF000);
    } else {
        return (int32_t)(data & 0x0FFF);
    }
}

ATTR_TEXT_IN_TCM int16_t hid_cp_convert_data_limiter(int32_t data)
{
    /* int32 -> int12 */
    if(data > 2047) {
        return 2047;
    } else if(data < -2048) {
        return -2048;
    } else {
        return (int16_t)(data & 0xFFF);
    }
}

ATTR_TEXT_IN_TCM void hid_critical_path_set_state(hid_critical_path_device_type_t type, hid_cp_state_t state)
{
    LOG_INF(BT_HID_CP_TAG"HID Critical Path State SET[type=%d]:%d -> %d", type, hid_critical_path_ctx[type].state, state);
    hid_critical_path_ctx[type].state = state;
}

ATTR_TEXT_IN_TCM hid_cp_state_t hid_critical_path_get_state(hid_critical_path_device_type_t type)
{
    hid_cp_state_t state = hid_critical_path_ctx[type].state;
    return state;
}

ATTR_TEXT_IN_TCM void hid_cp_usb_evt_cb(air_usb_evt_t evt, const uint8_t *para)
{
    switch (evt) {
        case AIR_USB_EVT_SUSPEND:
            /* handle suspend event */
            break;
        case AIR_USB_EVT_RESUME:
            /* handle resume event */
            break;
        default:
            break;
    }
}

static bt_ull_le_hid_srv_report_rate_level_t last_report_rate = BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_1;
ATTR_TEXT_IN_TCM void hid_cp_debug_log(bt_ull_le_hid_srv_report_rate_level_t report_rate)
{
    uint32_t data_cnt = 0;
    if (last_report_rate != report_rate) {
        hid_cp_debug_paramter.total_data_count = 0;
        last_report_rate = report_rate;
#ifdef CONFIG_AIR_HID_PLC_CALCULATE
        hid_plc_clear();
#endif
        return;
    }
    last_report_rate = report_rate;
    if (report_rate == BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_8) {
        data_cnt = 8000;
    } else {
        data_cnt = 4000;
    }

    if(hid_cp_debug_paramter.total_data_count >= data_cnt){
        switch (report_rate) {
            case BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_1:
                break;
            case BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_2:
                if ((hid_cp_debug_paramter.total_data_count % 125) == 0 && hid_cp_debug_info_cb){
                    hid_cp_debug_info_cb(125, hid_cp_debug_paramter.normal_data_count, report_rate);
                }
                break;
            case BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_3:
                if ((hid_cp_debug_paramter.total_data_count % 250) == 0 && hid_cp_debug_info_cb){
                    hid_cp_debug_info_cb(250, hid_cp_debug_paramter.normal_data_count, report_rate);
                }
                break;
            case BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_4:
                if ((hid_cp_debug_paramter.total_data_count % 500) == 0 && hid_cp_debug_info_cb){
                    hid_cp_debug_info_cb(500, hid_cp_debug_paramter.normal_data_count, report_rate);
                }
                break;
            case BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_5:
                if ((hid_cp_debug_paramter.total_data_count % 1000) == 0 && hid_cp_debug_info_cb){
                hid_cp_debug_info_cb(1000, hid_cp_debug_paramter.normal_data_count, report_rate);
                }
                break;
            case BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_6:
                if ((hid_cp_debug_paramter.total_data_count % 2000) == 0 && hid_cp_debug_info_cb){
                    hid_cp_debug_info_cb(2000, hid_cp_debug_paramter.normal_data_count, report_rate);
                }
                break;
            case BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_7:
                if ((hid_cp_debug_paramter.total_data_count % 4000) == 0 && hid_cp_debug_info_cb){
                    hid_cp_debug_info_cb(4000, hid_cp_debug_paramter.normal_data_count, report_rate);
                }
                break;
            case BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_8:
                if ((hid_cp_debug_paramter.total_data_count % 8000) == 0 && hid_cp_debug_info_cb){
                    hid_cp_debug_info_cb(8000, hid_cp_debug_paramter.normal_data_count, report_rate);
                }
                break;
            default:
                break;
        }
        LOG_INF(BT_HID_CP_TAG"DBG_LOG: TOTAL:%04d, SUC:%04d, CRC_ERR:%04d, NULL:%04d, DUP: %03d, NOT_EXPECT:%04d, PLC:%03d, ZERO: %03d, USB_SUC:%04d, USB_FAIL:%04d, TX_DONE:%04d, FAIL_BT:%04d",
                            hid_cp_debug_paramter.total_data_count,
                            hid_cp_debug_paramter.normal_data_count,
                            hid_cp_debug_paramter.plc_err_count,
                            hid_cp_debug_paramter.plc_null_count,
                            hid_cp_debug_paramter.plc_dup_count,
                            hid_cp_debug_paramter.not_except_count,
                            hid_cp_debug_paramter.plc_correct_count,
                            hid_cp_debug_paramter.plc_revised_zero_count,
                            hid_cp_debug_paramter.send_to_usb_suc,
                            // hid_cp_debug_paramter.duplicate_data_count,
                            hid_cp_debug_paramter.send_to_usb_fail_usb,
                            // hid_cp_debug_paramter.tx_done_send_busy_count,
                            hid_cp_debug_paramter.tx_done_cb_count,
                            hid_cp_debug_paramter.send_to_usb_fail_bt);
        hid_cp_debug_paramter.total_data_count = 0;
        hid_cp_debug_paramter.normal_data_count = 0;
        hid_cp_debug_paramter.plc_correct_count = 0;
        hid_cp_debug_paramter.plc_revised_zero_count = 0;
        hid_cp_debug_paramter.plc_err_count = 0;
        hid_cp_debug_paramter.plc_null_count = 0;
        hid_cp_debug_paramter.plc_dup_count = 0;
        hid_cp_debug_paramter.not_except_count = 0;
        hid_cp_debug_paramter.duplicate_data_count = 0;
        hid_cp_debug_paramter.send_to_usb_count = 0;
        hid_cp_debug_paramter.send_to_usb_suc = 0;
        hid_cp_debug_paramter.send_to_usb_fail_bt = 0;
        hid_cp_debug_paramter.send_to_usb_fail_usb = 0;
        hid_cp_debug_paramter.tx_done_send_busy_count = 0;
        hid_cp_debug_paramter.tx_done_cb_count = 0;
    }
}

ATTR_TEXT_IN_TCM int hid_cp_protocol_change_cb(const struct device *dev, uint8_t protocol)
{
    LOG_INF(BT_HID_CP_TAG"HID Critical Path Protocol Change Callback dev: %p, protocol: %d", dev, protocol);
    if(hid_critical_path_ctx[HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE].hid_dev == dev){
        hid_critical_path_ctx[HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE].hid_protocol = protocol;
#if CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE
    } else if(hid_critical_path_ctx[HID_CRITICAL_PATH_DEVICE_TYPE_KEY_REMAP].hid_dev == dev) {
        hid_critical_path_ctx[HID_CRITICAL_PATH_DEVICE_TYPE_KEY_REMAP].hid_protocol = protocol;
#endif
#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
    } else if(hid_critical_path_ctx[HID_CRITICAL_PATH_DEVICE_TYPE_NKEY].hid_dev == dev) {
        hid_critical_path_ctx[HID_CRITICAL_PATH_DEVICE_TYPE_NKEY].hid_protocol = protocol;
#endif
    } else {
        LOG_ERR(BT_HID_CP_TAG"HID Critical Path Protocol Change Callback Failed!");
        return -1;
    }
    return 0;
}

ATTR_TEXT_IN_TCM void hid_critical_path_common_register_callback(hid_cp_debug_callback_t cb)
{
    hid_cp_debug_info_cb = cb;
}

#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE)
ATTR_TEXT_IN_TCM void hid_critical_path_common_custom_protocol_data_push(uint8_t *in_buf, uint16_t len)
{
    uint32_t mask;
    uint8_t *dest_addr;

    assert(!hid_cp_custom_protocol_data.is_full);
    hal_nvic_save_and_set_interrupt_mask(&mask);
    dest_addr = &hid_cp_custom_protocol_data.buff[hid_cp_custom_protocol_data.write_ptr];
    hid_cp_custom_protocol_data.write_ptr += len;
    hid_cp_custom_protocol_data.write_ptr = hid_cp_custom_protocol_data.write_ptr % (EPIO_CUSTOM_PROTOCOL_MIX_WITH_HID_PACKET_SIZE * HID_CP_CUSTOM_PROTOCOL_PACKET_CNT);
    if (hid_cp_custom_protocol_data.write_ptr == hid_cp_custom_protocol_data.read_ptr)
    {
        hid_cp_custom_protocol_data.is_full = true;
    }
    hal_nvic_restore_interrupt_mask(mask);

    memcpy(dest_addr, in_buf, len);
}

ATTR_TEXT_IN_TCM void hid_critical_path_common_custom_protocol_data_query(uint8_t **current_read_ptr, uint16_t len)
{
    *current_read_ptr = &hid_cp_custom_protocol_data.buff[hid_cp_custom_protocol_data.read_ptr];
}

ATTR_TEXT_IN_TCM void hid_critical_path_common_custom_protocol_data_pop(uint8_t *out_buf, uint16_t len)
{
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    hid_cp_custom_protocol_data.read_ptr += len;
    hid_cp_custom_protocol_data.read_ptr = hid_cp_custom_protocol_data.read_ptr % (EPIO_CUSTOM_PROTOCOL_MIX_WITH_HID_PACKET_SIZE * HID_CP_CUSTOM_PROTOCOL_PACKET_CNT);
    hid_cp_custom_protocol_data.is_full = false;
    hal_nvic_restore_interrupt_mask(mask);
}

ATTR_TEXT_IN_TCM void hid_critical_path_common_custom_protocol_data_process(void)
{
    uint8_t *data_buf;

    if ((hid_cp_custom_protocol_data.write_ptr != hid_cp_custom_protocol_data.read_ptr) || (hid_cp_custom_protocol_data.is_full))
    {
        hid_critical_path_common_custom_protocol_data_query(&data_buf, EPIO_CUSTOM_PROTOCOL_MIX_WITH_HID_PACKET_SIZE);
        epio_bt_hid_recv_data_mix_with_hid_packet(NULL, EPIO_CUSTOM_PROTOCOL_MIX_WITH_HID_PACKET_SIZE, data_buf);
        hid_critical_path_common_custom_protocol_data_pop(NULL, EPIO_CUSTOM_PROTOCOL_MIX_WITH_HID_PACKET_SIZE);
    }
}
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE */

/* End of file */
