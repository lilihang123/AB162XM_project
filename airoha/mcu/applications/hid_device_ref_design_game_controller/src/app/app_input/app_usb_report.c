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
#include "app_state.h"
#include "hid_scenario_USB_mode.h"
#include "hid_game_controller.h"

#include "hal_sleep_manager.h"
#include "hal_sleep_manager_platform.h"
#include "hal_ccni.h"
#include "hal_spi_master_internal.h"
#include "hal_hw_keyscan.h"

#include "air_usb.h"
#include "air_usb_hid.h"
#include "air_usb_hid_desc.h"
#if defined(CONFIG_AIR_USB_XINPUT_ENABLE)
#include "air_usb_xinput.h"
#endif /* CONFIG_AIR_USB_XINPUT_ENABLE */

#define thisMODULE usb_report
#define thisMOD    "usb_report"
LOG_MODULE_REGISTER(thisMODULE);

/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/

/* timers defined ------------------------------------------------------------*/
static void app_usb_report__send_dummy_report_timer(struct k_timer *timer_id);
K_TIMER_DEFINE(send_dummy_report_timer, app_usb_report__send_dummy_report_timer, NULL);

/******************************************************************************/
/* variables                                                          */
/******************************************************************************/
/* defined */
#define DUMMY_REPORT_TIME_INTERVAL    500  /* ms */
#define USB_TRY_DUMMY_REPORT_TIMES     10  /* times */

/* USB device handle */
const struct device *hdev0;
const struct device *hdev1;
const struct device *hdev2;
const struct device *hdev3;
#if defined(CONFIG_AIR_USB_XINPUT_ENABLE)
const struct device *xinput_dev;
const struct device *xinput_hdev0;
const struct device *xinput_hdev1;
const struct device *xinput_hdev2;
#endif
static app_usb_report_info_t gc_report = {0};

uint8_t usb_send_dummy_counter = 0;

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/
static void app_usb_report__send_dummy_report_timer(struct k_timer *timer_id)
{
    if(usb_send_dummy_counter >= USB_TRY_DUMMY_REPORT_TIMES) {
        APP_LOGI(thisMOD, "usb_send_dummy_counter >= USB_TRY_DUMMY_REPORT_TIMES !!!");
        hid_usb_ep_flush(gc_report.dev, true);
        usb_send_dummy_counter = 0;
    }
    air_usb_hid_gamepad_report_t temp_report = {0};
    temp_report.report_id = gc_report.report_id;
    usb_send_dummy_counter++;
    hid_scenario_usb_send_report(gc_report.dev, (uint8_t *)&temp_report);
}

/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
#if defined(CONFIG_AIR_USB_EARLY_WAKEUP_CM33)
ATTR_TEXT_IN_TCM void app_usb_report__usb_send_report_handler()
#else
ATTR_TEXT_IN_TCM void CCNI_DEF_HANDLER(0)(hal_ccni_event_t event, hal_ccni_message_t *msg)
#endif
{
    #if defined (AIR_SWLA_ENABLE)
    HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_usb_tx_send, SWLA_DIRECTION_START);
    #endif
    #if defined(CONFIG_AIR_USB_EARLY_WAKEUP_CM33)
    uint8_t send_report = hid_usb_mode__wait_for_ccni_send_ready();
    // DBG_PING_H(DBG_SIGNAL_DEBUG_3);
    if(send_report != USB_REPORT_COMPLETE){  //no packet need send
        #if defined (AIR_SWLA_ENABLE)
        HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_usb_tx_send, SWLA_DIRECTION_STOP);
        #endif
        return;
    }
    hid_common->hid.outgoing_report_ready = USB_REPORT_TX_READY;
    uint8_t *data_ptr = (uint8_t *)&(hid_common->outgoing_report[0]);
    #else
    uint8_t *data_ptr = (uint8_t *)&(msg->data[0]) + 1;
    #endif
    uint8_t report_id = data_ptr[0];
    air_usb_mode_t app_usb_mode = USB_MODE_HID;
    app_usb_mode = air_usb_mode_get();

    switch(report_id)
    {
        case REPORT_ID_MOUSE:
        {
            if(app_usb_mode == USB_MODE_HID){
                hid_scenario_usb_send_report(hdev0, data_ptr);
            }
            #if defined(CONFIG_AIR_USB_XINPUT_ENABLE)
            else{
                hid_scenario_usb_send_report(xinput_hdev0, data_ptr);
            }
            #endif
            break;
        }
        case REPORT_ID_KB_STD:
        case REPORT_ID_KB_CONSUMER:
        {
            if(app_usb_mode == USB_MODE_HID){
                hid_scenario_usb_send_report(hdev2, data_ptr);
            }
            #if defined(CONFIG_AIR_USB_XINPUT_ENABLE)
            else{
                hid_scenario_usb_send_report(xinput_hdev2, data_ptr);
            }
            #endif
            break;
        }
        case REPORT_ID_GAME_CONTROLLER:
        {
            hid_scenario_usb_send_report(gc_report.dev, data_ptr);
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
    game_controller_bt_hw_trigger_read();
}

static void app_usb_report__tx_done_interrupt_enable(bool enable)
{
    #if 0
    static uint8_t tx_done_enable = 0;
    if(enable && !tx_done_enable)
    {
        tx_done_enable = 1;
        air_usb_ep_interrupt_enable(gc_report.dev, true, tx_done_enable);
    }
    else if(!enable && tx_done_enable)
    {
        tx_done_enable = 0;
        air_usb_ep_interrupt_enable(gc_report.dev, true, tx_done_enable);
    }
    #endif
    return;
}

static void app_usb_report__hid_event_handler(uint8_t evt)
{
    switch(evt)
    {
        case HID_USB_RISCV_TRIGGER_CHANGE:
        {
            k_timer_stop(&send_dummy_report_timer);
            app_usb_report__tx_done_interrupt_enable(false);
            break;
        }
        case HID_USB_TX_DONE_ENABLE:
        {
            uint8_t state = app_state_current_state();
            if(state != APP_STATE_USB_ACTIVE) {
                app_usb_report__tx_done_interrupt_enable(true);
            }
            if(state == APP_STATE_USB_CONNECTED || state == APP_STATE_USB_ENTERING_ACTIVE)
            {
                usb_send_dummy_counter = 0;
                k_timer_stop(&send_dummy_report_timer);
                k_timer_start(&send_dummy_report_timer, K_NO_WAIT , K_MSEC(DUMMY_REPORT_TIME_INTERVAL));
            }
            break;
        }
        case HID_USB_SEND_DUMMY_REPORT:
        {
            if(k_timer_remaining_get(&send_dummy_report_timer)) {
                return;
            }
            usb_send_dummy_counter = 0;
            k_timer_start(&send_dummy_report_timer, K_NO_WAIT, K_MSEC(DUMMY_REPORT_TIME_INTERVAL));
            break;
        }
        case HID_USB_SEND_RESUME_REPORT:
        {
            APP_LOGI(thisMOD,"HID_USB_SEND_RESUME_REPORT");
            break;
        }
        case HID_USB_RESET_DUMMY_TIMER:
        {
            k_timer_stop(&send_dummy_report_timer);
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
    k_timer_init(&send_dummy_report_timer, app_usb_report__send_dummy_report_timer, NULL);
    return;
}

static void app_usb_report_service_set(void)
{
    int ret = 0;
    air_usb_mode_t app_usb_mode = air_usb_mode_get();
    if(app_usb_mode == USB_MODE_HID)
    {
        ret |= hid_usb_device_set_init(hdev0, HID_BOOT_IFACE_CODE_MOUSE, false);
        ret |= hid_usb_device_set_init(hdev1, HID_BOOT_IFACE_CODE_NONE, false);
        ret |= hid_usb_device_set_init(hdev2, HID_BOOT_IFACE_CODE_KEYBOARD, false);
        ret |= hid_usb_device_set_init(hdev3, HID_BOOT_IFACE_CODE_NONE, false);
    }
    #if defined(CONFIG_AIR_USB_XINPUT_ENABLE)
    else
    {
        ret |= hid_usb_device_set_init(xinput_hdev0, HID_BOOT_IFACE_CODE_MOUSE, false);
        ret |= hid_usb_device_set_init(xinput_hdev1, HID_BOOT_IFACE_CODE_NONE, false);
        ret |= hid_usb_device_set_init(xinput_hdev2, HID_BOOT_IFACE_CODE_KEYBOARD, false);
    }
    #endif /* CONFIG_AIR_USB_XINPUT_ENABLE */
    if(ret){
        APP_LOGE(thisMOD, "hid_usb_device_set_init fail");
        return;
    }
    if(app_usb_mode == USB_MODE_HID){
        gc_report.dev     = hdev3;
        gc_report.size    = sizeof(air_usb_hid_gamepad_report_t);
    }
    #if defined(CONFIG_AIR_USB_XINPUT_ENABLE)
    else{
        gc_report.dev     = xinput_dev;
        gc_report.size    = sizeof(T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S);
    }
    #endif
    gc_report.report_id   = AIR_USB_HID_GAMEPAD_REPORT_ID;
    gc_report.report_desc = AIR_USB_REPORT_DESC_GAMEPAD;

    #if defined(CONFIG_AIR_USB_XINPUT_ENABLE)
    if(app_usb_mode == USB_MODE_XINPUT){
        hid_register_usb_xinput_tx_done(gc_report.dev);
        hid_register_usb_xinput_data_received(gc_report.dev);
    }
    else
    #endif
    {
        hid_register_usb_tx_done(gc_report.report_desc, USB_HID_REPORT_TYPE_INPUT, gc_report.report_id, gc_report.size);
    }
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
uint8_t app_usb_report_service_init(void)
{
    int ret = 0;
    air_usb_mode_t app_usb_mode = USB_MODE_HID;
    #if defined(CONFIG_AIR_USB_XINPUT_ENABLE)
    uint32_t nvkey_size = sizeof(air_usb_mode_t);
    nvkey_status_t nvkey_ret = nvkey_read_data(NVID_APP_USB_MODE, (uint8_t *)&app_usb_mode, &nvkey_size);
    if ((nvkey_size != sizeof(air_usb_mode_t)) || (nvkey_ret != NVKEY_STATUS_OK)) {
        app_usb_mode = USB_MODE_HID;
    }
    hid_usb_mode__set_usb_mode(app_usb_mode);
    #endif /* CONFIG_AIR_USB_XINPUT_ENABLE */
    if(app_usb_mode == USB_MODE_HID)
    {
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
        air_usb_hid_report_desc_t descs3[2] = {AIR_USB_REPORT_DESC_GAMEPAD};
        ret |= hid_usb_device_register_init(hdev3, descs3, 1);
    }
    #if defined(CONFIG_AIR_USB_XINPUT_ENABLE)
    else if(app_usb_mode == USB_MODE_XINPUT)
    {
        APP_LOGI(thisMOD, "Xinput HID device_get_binding");
        xinput_hdev0 = device_get_binding("HID_SEC_0");
        if (xinput_hdev0 == NULL) {
            ret = -ENODEV;
            goto _fail_return;
        }
        xinput_hdev1 = device_get_binding("HID_SEC_1");
        if (xinput_hdev1 == NULL) {
            ret = -ENODEV;
            goto _fail_return;
        }
        xinput_hdev2 = device_get_binding("HID_SEC_2");
        if (xinput_hdev2 == NULL) {
            ret = -ENODEV;
            goto _fail_return;
        }
        xinput_dev = device_get_binding("XINPUT_DEV");
        if (xinput_dev == NULL) {
            ret = -ENODEV;
            goto _fail_return;
        }

        APP_LOGI(thisMOD, "Xinput HID Device: dev0 = %p, dev1 = %p, dev2 = %p", xinput_hdev0, xinput_hdev1, xinput_hdev2);
        // HID device
        air_usb_hid_report_desc_t xinput_descs0[2] = {AIR_USB_REPORT_DESC_GAMING_MS, AIR_USB_REPORT_DESC_CUSTOM};
        ret = hid_usb_device_register_init(xinput_hdev0, xinput_descs0, 2);
        air_usb_hid_report_desc_t xinput_descs1[2] = {AIR_USB_REPORT_DESC_MUX, AIR_USB_REPORT_DESC_EPIO};
        ret |= hid_usb_device_register_init(xinput_hdev1, xinput_descs1, 2);
        air_usb_hid_report_desc_t xinput_descs2[2] = {AIR_USB_REPORT_DESC_GAMING_KB, AIR_USB_REPORT_DESC_CONSUMER};
        ret |= hid_usb_device_register_init(xinput_hdev2, xinput_descs2, 2);
        // Xinput device
        ret = air_usb_xinput_device_register(xinput_dev);
        if (ret) {
            APP_LOGE(thisMOD, "Failed to register XInput device");
            goto _fail_return;
        }
    }
    #endif /* CONFIG_AIR_USB_XINPUT_ENABLE */

_fail_return:
    if(ret){
        APP_LOGE(thisMOD, "hid_usb_device_register_init fail, ret = %d", ret);
        return 1;
    }
    return 0;
}

uint8_t app_usb_report_init(void)
{
    int ret = 0;
    app_usb_report_service_init();
    app_usb_report_service_set();
    app_usb_report_timer_init();

    hid_scenario_usb_callbacks_t app_usb_report_cbs = {
        .sof_cb     = app_usb_report__hid_sof_handler,
        .usb_evt_cb = app_usb_report__hid_event_handler
    };
    ret = hid_scenario_usb_register_callbacks(&app_usb_report_cbs);
    if(ret){
        APP_LOGE(thisMOD, "hid_scenario_usb_register_callbacks fail");
    }
    #if defined(CONFIG_AIR_USB_EARLY_WAKEUP_CM33)
    ret = game_controller_usb_register(app_usb_report__usb_send_report_handler);
    if(ret){
        APP_LOGE(thisMOD, "hid_scenario_usb_register fail");
    }
    #endif

    return ret;
}

/*============================Application Framework============================*/

#endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/
