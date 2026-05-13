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
#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/class/usb_hid.h>

#include "app_usb_report.h"
#include "hid_scenario_USB_mode.h"

#include "hal_sleep_manager.h"
#include "hal_sleep_manager_platform.h"
#include "hal_ccni.h"
#include "adc_keyscan.h"

#include "air_usb.h"
#include "air_usb_hid.h"
#include "air_usb_hid_desc.h"

#define thisMODULE usb_report
#define thisMOD    "usb_report"
LOG_MODULE_REGISTER(thisMODULE);

/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
bool app_usb_report_service_set(void);

/* timers defined ------------------------------------------------------------*/

/******************************************************************************/
/* variables                                                          */
/******************************************************************************/
/* defined */
#define PRINT_NO_SENSOR_LOG_TIME     0  /* ms */

/* USB device handle */
const struct device *hdev0;
const struct device *hdev1;
const struct device *hdev2;
const struct device *hdev3;

app_usb_report_info_t kb_report = {0};

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/

/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
ATTR_TEXT_IN_TCM void CCNI_DEF_HANDLER(0)(hal_ccni_event_t event, hal_ccni_message_t *msg)
{
    #if defined (AIR_SWLA_ENABLE)
    HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_usb_tx_send, SWLA_DIRECTION_START);
    #endif
    #if defined(CONFIG_AIR_USB_EARLY_WAKEUP_CM33)
    uint8_t send_report = hid_usb_mode__wait_for_ccni_send_ready();
    // DBG_PING_H(DBG_SIGNAL_DEBUG_3);
    hid_common->hid.outgoing_report_ready = 0;
    if(!(send_report & 0x02)){  //no packet need send
        #if defined (AIR_SWLA_ENABLE)
        HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_usb_tx_send, SWLA_DIRECTION_STOP);
        #endif
        return;
    }
    uint8_t *data_ptr = (uint8_t *)&(hid_common->outgoing_report[0]);
    #else
    uint8_t *data_ptr = (uint8_t *)&(msg->data[0]) + 1;
    #endif
    uint8_t report_id = data_ptr[0];
    switch(report_id)
    {
        case REPORT_ID_MOUSE:
        {
            hid_scenario_usb_send_report(hdev0, data_ptr);
            break;
        }
        case REPORT_ID_KB_STD:
        case REPORT_ID_USB_KB_CONSUMBER:
        {
            hid_scenario_usb_send_report(hdev2, data_ptr);
            break;
        }
        case REPORT_ID_KEYBOARD_NKEY:
        {
            hid_scenario_usb_send_report(hdev3, data_ptr);
            break;
        }
        default:{
            APP_LOGI(thisMOD,"Not support id = 0x%X", report_id);
            break;
        }
    }
}

ATTR_TEXT_IN_TCM static void app_usb_report__hid_sof_handler()
{
    sw_keyscan_mcu_trigger_dummy_irq();
}

static void app_usb_report__hid_event_handler(uint8_t evt)
{
    switch(evt)
    {
        case HID_USB_RISCV_TRIGGER_CHANGE:
        {
            extern void sw_keyscan_bt_trigger_control(bool is_enable);
            sw_keyscan_bt_trigger_control(false);
            break;
        }
        case HID_USB_SEND_DUMMY_REPORT:
        {
            // APP_LOGI(thisMOD,"HID_USB_SEND_DUMMY_REPORT");
            air_usb_hid_gaming_kb_nkey_report_t temp_report = {0};
            temp_report.report_id = kb_report.report_id;
            hid_scenario_usb_send_report(kb_report.dev, (uint8_t *)&temp_report);
            break;
        }
        case HID_USB_SEND_RESUME_REPORT:
        {
            APP_LOGI(thisMOD,"HID_USB_SEND_RESUME_REPORT");
            break;
        }
        default:{
            break;
        }
    }
}
/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static void app_usb_report_timer_init()
{
    return;
}
bool app_usb_report_service_set(void)
{
    int ret = 0;
    ret |= hid_usb_device_set_init(hdev0, HID_BOOT_IFACE_CODE_MOUSE, false);
    ret |= hid_usb_device_set_init(hdev1, HID_BOOT_IFACE_CODE_NONE, false);
    ret |= hid_usb_device_set_init(hdev2, HID_BOOT_IFACE_CODE_KEYBOARD, false);
    ret |= hid_usb_device_set_init(hdev3, HID_BOOT_IFACE_CODE_KEYBOARD, false);
    if(ret){
        APP_LOGE(thisMOD, "hid_usb_device_set_init fail");
        return 1;
    }

    kb_report.dev         = hdev3;
    kb_report.report_id   = REPORT_ID_KEYBOARD_NKEY;
    kb_report.report_desc = AIR_USB_REPORT_DESC_GAMING_KB_NKEY;
    kb_report.size        = sizeof(air_usb_hid_gaming_kb_nkey_report_t);
    hid_register_usb_tx_done(kb_report.report_desc, USB_HID_REPORT_TYPE_INPUT, kb_report.report_id, kb_report.size);
    return 0;
}
/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
uint8_t app_usb_report_service_init(void)
{
    APP_LOGI(thisMOD, "app_usb_report_service_init start");
    int ret = 0;
    hdev0 = device_get_binding("HID_0");
    if (hdev0 == NULL) {
        ret = -ENODEV;
        goto _fail_return;
    }
    hdev1 = device_get_binding("HID_1");
    if (hdev1 == NULL) {
        ret = -ENODEV;
        goto _fail_return;
    }
    hdev2 = device_get_binding("HID_2");
    if (hdev2 == NULL) {
        ret = -ENODEV;
        goto _fail_return;
    }
    hdev3 = device_get_binding("HID_3");
    if (hdev3 == NULL) {
        ret = -ENODEV;
        goto _fail_return;
    }
    APP_LOGI(thisMOD, "HID Device: dev0 = %p, dev1 = %p, dev2 = %p, dev3 = %p", hdev0, hdev1, hdev2, hdev3);

    air_usb_hid_report_desc_t descs0[2] = {AIR_USB_REPORT_DESC_GAMING_MS, AIR_USB_REPORT_DESC_CUSTOM};
    ret = hid_usb_device_register_init(hdev0, descs0, 2);
    air_usb_hid_report_desc_t descs1[2] = {AIR_USB_REPORT_DESC_MUX, AIR_USB_REPORT_DESC_EPIO};
    ret |= hid_usb_device_register_init(hdev1, descs1, 2);
    air_usb_hid_report_desc_t descs2[2] = {AIR_USB_REPORT_DESC_GAMING_KB, AIR_USB_REPORT_DESC_CONSUMER};
    ret |= hid_usb_device_register_init(hdev2, descs2, 2);
    air_usb_hid_report_desc_t descs3[2] = {AIR_USB_REPORT_DESC_GAMING_KB_NKEY, AIR_USB_REPORT_DESC_CONSUMER};
    ret |= hid_usb_device_register_init(hdev3, descs3, 2);

_fail_return:
    if(ret){
        APP_LOGE(thisMOD, "hid_usb_device_register_init fail, ret = %d", ret);
        return 1;
    }
    return 0;
}
uint8_t app_usb_report_init(void)
{
    APP_LOGI(thisMOD, "app_usb_report_init start");
    int ret = app_usb_report_service_init();
    if(ret){
        APP_LOGE(thisMOD, "app_usb_report_service_init fail");
    }
    ret = app_usb_report_service_set();
    if(ret){
        APP_LOGE(thisMOD, "app_usb_report_service_set fail");
    }
    app_usb_report_timer_init();

    hid_scenario_usb_callbacks_t app_usb_report_cbs = {
        .sof_cb     = app_usb_report__hid_sof_handler,
        .usb_evt_cb = app_usb_report__hid_event_handler
    };
    ret = hid_scenario_usb_register_callbacks(&app_usb_report_cbs);
    if(ret){
        APP_LOGE(thisMOD, "hid_scenario_usb_register_callbacks fail");
    }

    return ret;
}
/*============================Application Framework============================*/
#endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/
