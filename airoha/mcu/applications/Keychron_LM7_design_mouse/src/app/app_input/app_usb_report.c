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

#include "hal_sleep_manager.h"
#include "hal_sleep_manager_platform.h"
#include "hal_ccni.h"

#include "air_usb.h"
#include "air_usb_hid.h"
#include "air_usb_hid_desc.h"
#include "mouse_sensor.h"

#define thisMODULE usb_report
#define thisMOD    "usb_report"
LOG_MODULE_REGISTER(thisMODULE);

/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
bool app_usb_report_service_set(void);

/* timers defined ------------------------------------------------------------*/
static void app_usb_report__send_dummy_report_timer(struct k_timer *timer_id);
K_TIMER_DEFINE(send_dummy_report_timer, app_usb_report__send_dummy_report_timer, NULL);

/******************************************************************************/
/* variables                                                          */
/******************************************************************************/
/* defined */
#define PRINT_NO_SENSOR_LOG_TIME     5000  /* ms */
#define DUMMY_REPORT_TIME_INTERVAL    500  /* ms */
#define USB_TRY_DUMMY_REPORT_TIMES     10  /* times */

/* USB device handle */
const struct device *hdev0;
const struct device *hdev1;
const struct device *hdev2;
extern const struct device * dev_hdl_sensor;
app_usb_report_info_t ms_report = {0};
static uint8_t usb_ms_last_key;
bool usb_has_sensor = false;

uint8_t usb_send_dummy_counter = 0;

/* fast word write defined -----------------------------------------------------*/
#define FAST_WORD_WRITE(target, src_0,  src_1,  src_2,  src_3 )     \
    *((uint32_t *)&target ) = (src_0)                               \
                            | ((src_1) <<  8)                       \
                            | ((src_2) << 16)                       \
                            | ((src_3) << 24);
#define LSB   0xFF

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/
static void app_usb_report__send_dummy_report_timer(struct k_timer *timer_id)
{
    if(usb_send_dummy_counter >= USB_TRY_DUMMY_REPORT_TIMES) {
        APP_LOGI(thisMOD, "usb_send_dummy_counter >= USB_TRY_DUMMY_REPORT_TIMES !!!");
        hid_usb_ep_flush(ms_report.dev, true);
        usb_send_dummy_counter = 0;
    }
    #if defined (CONFIG_AIR_NVIDIA_REFLEX_ENABLE)
    air_usb_hid_gaming_ms_nv_report_t temp_report = {0};
    #else
    air_usb_hid_gaming_ms_report_t temp_report = {0};
    #endif
    temp_report.report_id = ms_report.report_id;
    usb_send_dummy_counter++;
    hid_scenario_usb_send_report(ms_report.dev, (uint8_t *)&temp_report);
}

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
    switch(report_id)
    {
        case REPORT_ID_MOUSE:
        {
            hid_scenario_usb_send_report(hdev0, data_ptr);
            usb_ms_last_key = data_ptr[1];
            break;
        }
        case REPORT_ID_KB_STD:
        case REPORT_ID_KB_CONSUMER:
        {
            hid_scenario_usb_send_report(hdev2, data_ptr);
            break;
        }

        case REPORT_ID_KB_STD_XY:
        {
            T_HID_REPORT_KB_STD2_XY_S *usb_kb_std_report = (T_HID_REPORT_KB_STD2_XY_S *)data_ptr;
            T_HID_REPORT_MS_K8_S16_Z8_S usb_ms_report = {0};
            usb_ms_report.report_id = REPORT_ID_MOUSE;
            usb_ms_report.k = usb_ms_last_key;
            FAST_WORD_WRITE(usb_ms_report.x
                        , (usb_kb_std_report->x & LSB)
                        , ((usb_kb_std_report->x >> 8) & LSB)
                        , (usb_kb_std_report->y & LSB)
                        , ((usb_kb_std_report->y >> 8) & LSB)
                        );
            usb_kb_std_report->report_id = REPORT_ID_KB_STD;
            FAST_WORD_WRITE(usb_kb_std_report->x, 0, 0, 0, 0);
            hid_scenario_usb_send_report(hdev2, (uint8_t *)usb_kb_std_report);
            hid_scenario_usb_send_report(hdev0, (uint8_t *)&usb_ms_report);
            break;
        }

        case REPORT_ID_KB_CONSUMER_XY:
        {
            T_HID_REPORT_KB_CONSUMER1_XY_S *usb_kb_consumer_report = (T_HID_REPORT_KB_CONSUMER1_XY_S *)data_ptr;
            T_HID_REPORT_MS_K8_S16_Z8_S usb_ms_report = {0};
            usb_ms_report.report_id = REPORT_ID_MOUSE;
            usb_ms_report.k = usb_ms_last_key;
            FAST_WORD_WRITE(usb_ms_report.x
                        , (usb_kb_consumer_report->x & LSB)
                        , ((usb_kb_consumer_report->x >> 8) & LSB)
                        , (usb_kb_consumer_report->y & LSB)
                        , ((usb_kb_consumer_report->y >> 8) & LSB)
                        );
            usb_kb_consumer_report->report_id = REPORT_ID_KB_CONSUMER;
            FAST_WORD_WRITE(usb_kb_consumer_report->x, 0, 0, 0, 0);
            hid_scenario_usb_send_report(hdev2, (uint8_t *)usb_kb_consumer_report);
            hid_scenario_usb_send_report(hdev0, (uint8_t *)&usb_ms_report);
            break;
        }
        default:{
            // APP_LOGI(thisMOD,"Not support id = 0x%X", report_id);
            break;
        }
    }
}

ATTR_TEXT_IN_TCM static void app_usb_report__hid_sof_handler()
{
    if(usb_has_sensor){
        sensor_sample_fetch(dev_hdl_sensor);
    }
    #if 0
    else if(PRINT_NO_SENSOR_LOG_TIME)
    {
        static uint32_t last_time = 0;
        uint32_t curr_time = k_uptime_get_32();
        uint16_t delta_time = CALCULATE_DELTA_TIME(curr_time, last_time);
        if(delta_time >= PRINT_NO_SENSOR_LOG_TIME){
            APP_LOGI(thisMOD, "Notice: No sensor device found!");
            last_time = curr_time;
        }
    }
    #endif
}

static void app_usb_report__tx_done_interrupt_enable(bool enable)
{
    static uint8_t tx_done_enable = true;
    if(enable && !tx_done_enable)
    {
        tx_done_enable = 1;
        air_usb_interrupt_enable(ms_report.dev, AIR_USB_INTERRUPT_EP_TX, true, tx_done_enable);
    }
    else if(!enable && tx_done_enable)
    {
        tx_done_enable = 0;
        air_usb_interrupt_enable(ms_report.dev, AIR_USB_INTERRUPT_EP_TX, true, tx_done_enable);
    }
    return;
}

static void app_usb_report__hid_event_handler(uint8_t evt)
{
    switch(evt)
    {
        case HID_USB_RISCV_TRIGGER_CHANGE:
        {
            k_timer_stop(&send_dummy_report_timer);
            #define TURN_ON 1
            #define TURN_OFF 0

            struct sensor_value val = {TURN_OFF, 0};
            int ret_attr_1 = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_SPI_NVIC_IRQ  , &val);
            int ret_attr_2 = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_BT_TRIGGER    , &val);

            APP_LOGI(thisMOD,"HID_USB_SPI_TRIGGER_ENABLE, set SPI_NVIC_IRQ = %d, BT_TRIGGER = %d"
                        , ret_attr_1
                        , ret_attr_2
                        );
            if(ret_attr_1 < 0 || ret_attr_2 < 0){
                usb_has_sensor = false;
                APP_LOGI(thisMOD, "usb_spi_trigger_enable failed, pls check sensor!!!!!");
                break;
            }
            usb_has_sensor = true;
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
                k_timer_start(&send_dummy_report_timer, K_NO_WAIT, K_MSEC(DUMMY_REPORT_TIME_INTERVAL));
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
            #if defined (CONFIG_AIR_NVIDIA_REFLEX_ENABLE)
            air_usb_hid_gaming_ms_nv_report_t temp_report = {0};
            #else
            air_usb_hid_gaming_ms_report_t temp_report = {0};
            #endif
            temp_report.report_id = ms_report.report_id;
            temp_report.x = 0x001;
            temp_report.y = 0x001;
            hid_scenario_usb_send_report(ms_report.dev, (uint8_t *)&temp_report);
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

bool app_usb_report_service_set(void)
{
    int ret = 0;
    ret |= hid_usb_device_set_init(hdev0, HID_BOOT_IFACE_CODE_MOUSE, true);
    ret |= hid_usb_device_set_init(hdev1, HID_BOOT_IFACE_CODE_NONE, false);
    ret |= hid_usb_device_set_init(hdev2, HID_BOOT_IFACE_CODE_KEYBOARD, false);
    if(ret){
        APP_LOGE(thisMOD, "hid_usb_device_set_init fail");
        return 1;
    }

    ms_report.dev         = hdev0;
#if defined (CONFIG_AIR_NVIDIA_REFLEX_ENABLE)
    ms_report.report_id   = AIR_USB_HID_GAMING_MS_NV_REPORT_ID;
    ms_report.report_desc = AIR_USB_REPORT_DESC_GAMING_MS_NV;
    #if defined(CONFIG_AIR_USB_NO_REPORT_ID)
    ms_report.size        = sizeof(T_HID_REPORT_MS_NV_S_NO_ID);
    #else
    ms_report.size        = sizeof(air_usb_hid_gaming_ms_nv_report_t);
    #endif /* CONFIG_AIR_USB_NO_REPORT_ID */
#else
    ms_report.report_id   = AIR_USB_HID_GAMING_MS_REPORT_ID;
    #if defined(CONFIG_AIR_USB_NO_REPORT_ID)
    ms_report.report_desc = AIR_USB_REPORT_DESC_GAMING_MS_NO_REPORT_ID;
    ms_report.size        = sizeof(T_HID_MOUSE_REPORT_K8_S12_Z8_NO_ID);
    #else
    ms_report.report_desc = AIR_USB_REPORT_DESC_GAMING_MS;
    ms_report.size        = sizeof(air_usb_hid_gaming_ms_report_t);
    #endif /* CONFIG_AIR_USB_NO_REPORT_ID */
#endif

    #if defined(CONFIG_AIR_USB_NO_REPORT_ID)
    hid_register_usb_tx_done(ms_report.report_desc, USB_HID_REPORT_TYPE_INPUT_NO_REPORT_ID, 0, ms_report.size);
    #else
    hid_register_usb_tx_done(ms_report.report_desc, USB_HID_REPORT_TYPE_INPUT, ms_report.report_id, ms_report.size);
    #endif /* CONFIG_AIR_USB_NO_REPORT_ID */
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
    APP_LOGI(thisMOD, "HID Device: dev0 = %p, dev1 = %p, dev2 = %p", hdev0, hdev1, hdev2);

#if defined(CONFIG_AIR_USB_NO_REPORT_ID)
    air_usb_hid_report_desc_t descs0[1] = {AIR_USB_REPORT_DESC_GAMING_MS_NO_REPORT_ID};
    ret = hid_usb_device_register_init(hdev0, descs0, 1);
#else
    air_usb_hid_report_desc_t descs0[2] = {AIR_USB_REPORT_DESC_GAMING_MS, AIR_USB_REPORT_DESC_CUSTOM};
    ret = hid_usb_device_register_init(hdev0, descs0, 2);
#endif /* CONFIG_AIR_USB_NO_REPORT_ID */
    air_usb_hid_report_desc_t descs1[2] = {AIR_USB_REPORT_DESC_MUX, AIR_USB_REPORT_DESC_EPIO};
    ret |= hid_usb_device_register_init(hdev1, descs1, 2);
    air_usb_hid_report_desc_t descs2[2] = {AIR_USB_REPORT_DESC_GAMING_KB, AIR_USB_REPORT_DESC_CONSUMER};
    ret |= hid_usb_device_register_init(hdev2, descs2, 2);

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