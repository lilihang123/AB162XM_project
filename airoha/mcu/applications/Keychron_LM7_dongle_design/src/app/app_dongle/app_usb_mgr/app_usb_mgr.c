
/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
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

#include "app_usb_mgr.h"

#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/class/usb_hid.h>

#include "air_usb.h"
#include "air_usb_hid.h"

#include "hal_dvfs.h"
#include "hal_gpio.h"
#include "hal_gpt.h"
#include "hal_usb.h"
#include "hal_usb_internal.h"
#include "hal_eint.h"
#include "hal_eint_internal.h"

#include "app_debug.h"
#include "app_dongle_event.h"



/**================================================================================*/
/**                              Definition & Structure                            */
/**================================================================================*/
#define LOG_TAG             "[APP_DONGLE][USB_MGR]"

//#define APP_USB_MGR_MS_TEST_ENABLE
//#define APP_USB_MGR_KB_TEST_ENABLE

#define APP_USB_MGR_EVENT_WINDOW_TIMER_DELAY_MS             20

#define APP_USB_MGR_EVENT_MS_REPORT_LEN                     (sizeof(air_usb_hid_office_mouse_report_t))
#define APP_USB_MGR_EVENT_KB_REPORT_LEN                     (sizeof(air_usb_hid_office_kb_report_t))

static const struct device                                 *app_usb_mgr_hid_dev0 = NULL;
static const struct device                                 *app_usb_mgr_hid_dev1 = NULL;
static const struct device                                 *app_usb_mgr_hid_dev2 = NULL;

static uint32_t         app_usb_mgr_user_id                 = 0;

static bool             app_usb_mgr_ready                   = FALSE;

static air_usb_evt_t    app_usb_mgr_cur_event               = AIR_USB_EVT_PLUG_OUT;
static air_usb_evt_t    app_usb_mgr_last_event              = AIR_USB_EVT_PLUG_OUT;
static uint32_t         app_usb_mgr_window_timer            = 0;



/**================================================================================*/
/**                                   Internal API                                 */
/**================================================================================*/
static bool app_usb_mgr_send_ms_report(air_usb_hid_office_mouse_report_t *ms_report);
static bool app_usb_mgr_send_kb_report(air_usb_hid_office_kb_report_t *kb_report);

#if defined(APP_USB_MGR_MS_TEST_ENABLE) || defined(APP_USB_MGR_KB_TEST_ENABLE)
static uint32_t app_usb_mgr_test_count = 0;

static void app_usb_mgr_test_handler(void)
{
    app_usb_mgr_test_count++;
    APPS_LOG_MSGID_I(LOG_TAG" test_handler, count=%d", 1, app_usb_mgr_test_count);

#ifdef APP_USB_MGR_MS_TEST_ENABLE
    air_usb_hid_office_mouse_report_t ms_report = {0};
    ms_report.report_id = AIR_USB_HID_OFFICE_MS_REPORT_ID;
    if ((app_usb_mgr_test_count % 6) == 0) {
        ms_report.x = 100;
        ms_report.y = 100;
    } else if ((app_usb_mgr_test_count % 6) == 1) {
        ms_report.x = 200;
        ms_report.y = 200;
    } else if ((app_usb_mgr_test_count % 6) == 2) {
        ms_report.x = 300;
        ms_report.y = 300;
    } else if ((app_usb_mgr_test_count % 6) == 3) {
        ms_report.x = 300;
        ms_report.y = 150;
    } else if ((app_usb_mgr_test_count % 6) == 4) {
        ms_report.x = 300;
        ms_report.y = 0;
    } else if ((app_usb_mgr_test_count % 6) == 5) {
        ms_report.x = 300;
        ms_report.y = -100;
    }
    app_usb_mgr_send_ms_report(&ms_report);
#endif
#ifdef APP_USB_MGR_KB_TEST_ENABLE
    air_usb_hid_office_kb_report_t kb_report = {0};
    kb_report.report_id = AIR_USB_HID_OFFICE_KB_REPORT_ID;
    memset(kb_report.key, 0x30 + (app_usb_mgr_test_count % 10), 6);
    app_usb_mgr_send_kb_report(&kb_report);
#endif
}

static void app_usb_mgr_test_start(void)
{
    APPS_LOG_MSGID_W(LOG_TAG" test_start", 0);
    app_usb_mgr_send_ms_report(NULL);
    app_usb_mgr_send_kb_report(NULL);

    app_usb_mgr_test_count = 0;
    app_dongle_event_send_delay_event(APP_DONGLE_EVENT_GROUP_USB, APP_DONGLE_EVENT_USB_TEST_EVENT,
                                      NULL, 0, 1000);
}
#endif

bool app_usb_mgr_event_handler(uint8_t event_group, uint16_t event_id, void *data, uint32_t data_len)
{
    if (event_group == APP_DONGLE_EVENT_GROUP_USB) {
#ifdef APP_USB_MGR_MS_TEST_ENABLE
        if (event_id == APP_DONGLE_EVENT_USB_TEST_EVENT) {
            app_usb_mgr_test_handler();
            app_dongle_event_send_delay_event(APP_DONGLE_EVENT_GROUP_USB, APP_DONGLE_EVENT_USB_TEST_EVENT,
                                              NULL, 0, 100);
        }
#endif
    }
    return FALSE;
}

static bool app_usb_mgr_send_ms_report(air_usb_hid_office_mouse_report_t *ms_report)
{
    if (ms_report == NULL || !app_usb_mgr_ready) {
        APPS_LOG_MSGID_E(LOG_TAG" send_ms_report, error ms_report=0x%08X ready=%d", 2, ms_report, app_usb_mgr_ready);
        return FALSE;
    }

    int ret = air_usb_hid_tx(app_usb_mgr_user_id, app_usb_mgr_hid_dev0,
                             APP_USB_MGR_EVENT_MS_REPORT_LEN, (uint8_t *)ms_report);
    if (ret != 0) {
        APPS_LOG_MSGID_E(LOG_TAG" send_ms_report, error ret=%d", 1, ret);
    }
    return (ret == 0);
}

static bool app_usb_mgr_send_kb_report(air_usb_hid_office_kb_report_t *kb_report)
{
    if (kb_report == NULL || !app_usb_mgr_ready) {
        APPS_LOG_MSGID_E(LOG_TAG" send_kb_report, error kb_report=0x%08X ready=%d", 2, kb_report, app_usb_mgr_ready);
        return FALSE;
    }

    int ret = air_usb_hid_tx(app_usb_mgr_user_id, app_usb_mgr_hid_dev1,
                             APP_USB_MGR_EVENT_KB_REPORT_LEN, (uint8_t *)kb_report);
    if (ret != 0) {
        APPS_LOG_MSGID_E(LOG_TAG" send_kb_report, ret=%d", 1, ret);
    }
    return (ret == 0);
}

static int app_usb_mgr_usb_device_init(void)
{
    app_usb_mgr_hid_dev0 = device_get_binding("HID_0");
    app_usb_mgr_hid_dev1 = device_get_binding("HID_1");
    app_usb_mgr_hid_dev2 = device_get_binding("HID_2");
    if (app_usb_mgr_hid_dev0 == NULL || app_usb_mgr_hid_dev1 == NULL || app_usb_mgr_hid_dev2 == NULL) {
        APPS_LOG_MSGID_E(LOG_TAG" usb_device_init, create HID device fail 0x%08X 0x%08X 0x%08X",
                         3, app_usb_mgr_hid_dev0, app_usb_mgr_hid_dev1, app_usb_mgr_hid_dev2);
        return -1;
    }

    /* Register the HID device to airoha usb hid subsys */
    int ret = 0;
    ret |= air_usb_hid_device_register(app_usb_mgr_hid_dev0);
    ret |= air_usb_hid_device_register(app_usb_mgr_hid_dev1);
    ret |= air_usb_hid_device_register(app_usb_mgr_hid_dev2);
    if (ret != 0) {
        APPS_LOG_MSGID_E(LOG_TAG" usb_device_init, register HID device ret=%d", 1, ret);
        return -2;
    }

    ret = 0;
    ret |= air_usb_hid_gen_rdesc(app_usb_mgr_hid_dev0, (air_usb_hid_report_desc_t[1]) {
        AIR_USB_REPORT_DESC_OFFICE_MS
    }, 1);
    ret |= air_usb_hid_gen_rdesc(app_usb_mgr_hid_dev1, (air_usb_hid_report_desc_t[1]) {
        AIR_USB_REPORT_DESC_OFFICE_KB
    }, 1);
    ret |= air_usb_hid_gen_rdesc(app_usb_mgr_hid_dev2, (air_usb_hid_report_desc_t[1]) {
        AIR_USB_REPORT_DESC_MUX
    }, 1);
    if (ret != 0) {
        APPS_LOG_MSGID_E(LOG_TAG" usb_device_init, gen_rdesc ret=%d", 1, ret);
        return -3;
    }

    /* Register to Zephyr USB HID stack */
    usb_hid_register_device(app_usb_mgr_hid_dev0, air_usb_hid_get_rdesc(app_usb_mgr_hid_dev0),
                            air_usb_hid_get_rdesc_len(app_usb_mgr_hid_dev0),
                            &airoha_usb_hid_ops);
    usb_hid_register_device(app_usb_mgr_hid_dev1, air_usb_hid_get_rdesc(app_usb_mgr_hid_dev1),
                            air_usb_hid_get_rdesc_len(app_usb_mgr_hid_dev1),
                            &airoha_usb_hid_ops);
    usb_hid_register_device(app_usb_mgr_hid_dev2, air_usb_hid_get_rdesc(app_usb_mgr_hid_dev2),
                            air_usb_hid_get_rdesc_len(app_usb_mgr_hid_dev2),
                            &airoha_usb_hid_ops);

    ret = 0;
    ret |= usb_hid_set_proto_code(app_usb_mgr_hid_dev0, HID_BOOT_IFACE_CODE_MOUSE);
    ret |= usb_hid_set_proto_code(app_usb_mgr_hid_dev1, HID_BOOT_IFACE_CODE_KEYBOARD);
    ret |= usb_hid_set_proto_code(app_usb_mgr_hid_dev2, HID_BOOT_IFACE_CODE_NONE);
    if (ret != 0) {
        APPS_LOG_MSGID_E(LOG_TAG" usb_device_init, set_proto_code fail ret=%d", 3, ret);
        return -4;
    }

    ret = 0;
    ret |= usb_hid_init(app_usb_mgr_hid_dev0);
    ret |= usb_hid_init(app_usb_mgr_hid_dev1);
    ret |= usb_hid_init(app_usb_mgr_hid_dev2);
    if (ret != 0) {
        APPS_LOG_MSGID_E(LOG_TAG" usb_device_init, usb_hid_init ret=%d", 1, ret);
        return -5;
    }

    APPS_LOG_MSGID_I(LOG_TAG" usb_device_init, init done", 0);
    return 0;
}

static void app_usb_mgr_register_usb_hid_cb(void)
{
#if 0
    const struct device *hiddev_kb = air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_GAMING_KB);

    air_usb_hid_register_output_cb(app_usb_mgr_user_id, hiddev_kb,
                                   USB_HID_REPORT_TYPE_OUTPUT, 0X01, 0x02,
                                   app_usb_mgr_kb_led_update);

    const struct device *hiddev_ms = air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_GAMING_MS);
    air_usb_hid_register_tx_done_cb(app_usb_mgr_user_id, hiddev_ms,
                                    USB_HID_REPORT_TYPE_INPUT, 0X02, 0x07,
                                    app_usb_mgr_ms_tx_done);
    air_usb_hid_register_tx_free_cb(app_usb_mgr_user_id, hiddev_ms, app_usb_mgr_ms_tx_free);
#endif
}

static void app_usb_mgr_window_timer_cb(void *user_data)
{
    air_usb_evt_t event = app_usb_mgr_cur_event;
    if (app_usb_mgr_cur_event == app_usb_mgr_last_event) {
        APPS_LOG_MSGID_E(LOG_TAG" window_timer_cb, same usb event=%d", 1, event);
        return;
    }
    app_usb_mgr_last_event = event;

    switch (event) {
        case AIR_USB_EVT_CONNECTED: {
            app_dongle_event_send_event(APP_DONGLE_EVENT_GROUP_USB, APP_DONGLE_EVENT_USB_CONNECTED);
            break;
        }
        case AIR_USB_EVT_CONFIGURED: {
            app_dongle_event_send_event(APP_DONGLE_EVENT_GROUP_USB, APP_DONGLE_EVENT_USB_DISCONNECTED);
            break;
        }
        case AIR_USB_EVT_DISCONNECTED: {
            app_dongle_event_send_event(APP_DONGLE_EVENT_GROUP_USB, APP_DONGLE_EVENT_USB_READY);
            break;
        }
        case AIR_USB_EVT_SUSPEND: {
            app_dongle_event_send_event(APP_DONGLE_EVENT_GROUP_USB, APP_DONGLE_EVENT_USB_SUSPEND);
            break;
        }
        case AIR_USB_EVT_RESUME: {
            app_dongle_event_send_event(APP_DONGLE_EVENT_GROUP_USB, APP_DONGLE_EVENT_USB_RESUME);
            break;
        }
        default: {
            break;
        }
    }
}

static void app_usb_mgr_timer_start(void)
{
    if (app_usb_mgr_window_timer == 0) {
        hal_gpt_sw_get_timer(&app_usb_mgr_window_timer);
    }
    hal_gpt_sw_stop_timer_ms(app_usb_mgr_window_timer);
    hal_gpt_status_t status = hal_gpt_sw_start_timer_ms(app_usb_mgr_window_timer,
                                                        APP_USB_MGR_EVENT_WINDOW_TIMER_DELAY_MS,
                                                        app_usb_mgr_window_timer_cb, NULL);
    APPS_LOG_MSGID_W(LOG_TAG" timer_start, usb event=%d status=%d", 2, app_usb_mgr_cur_event, status);
}

static void app_usb_mgr_update_event(air_usb_evt_t evt)
{
    app_usb_mgr_cur_event = evt;
    app_usb_mgr_timer_start();
}



/**================================================================================*/
/**                                  Event Handler                                 */
/**================================================================================*/
static void app_usb_mgr_usb_evt_cb(air_usb_evt_t event, const uint8_t *para)
{
    switch (event) {
        case AIR_USB_EVT_PLUG_IN: {
            APPS_LOG_MSGID_W(LOG_TAG" AIR_USB_EVT_PLUG_IN", 0);
            break;
        }
        case AIR_USB_EVT_PLUG_OUT: {
            APPS_LOG_MSGID_W(LOG_TAG" AIR_USB_EVT_PLUG_OUT", 0);
            break;
        }
        case AIR_USB_EVT_RESET: {
            APPS_LOG_MSGID_W(LOG_TAG" AIR_USB_EVT_RESET", 0);
            break;
        }

        case AIR_USB_EVT_CONNECTED: {
            APPS_LOG_MSGID_W(LOG_TAG" AIR_USB_EVT_CONNECTED", 0);
            app_usb_mgr_update_event(event);
            break;
        }
        case AIR_USB_EVT_CONFIGURED: {
            APPS_LOG_MSGID_W(LOG_TAG" AIR_USB_EVT_CONFIGURED", 0);
            app_usb_mgr_ready = TRUE;
            app_usb_mgr_update_event(event);

#if defined(APP_USB_MGR_MS_TEST_ENABLE) || defined(APP_USB_MGR_KB_TEST_ENABLE)
            app_usb_mgr_test_start();
#endif
            break;
        }
        case AIR_USB_EVT_DISCONNECTED: {
            APPS_LOG_MSGID_W(LOG_TAG" AIR_USB_EVT_DISCONNECTED", 0);
            app_usb_mgr_update_event(event);
            break;
        }
        case AIR_USB_EVT_SUSPEND: {
            APPS_LOG_MSGID_W(LOG_TAG" AIR_USB_EVT_SUSPEND", 0);
            app_usb_mgr_ready = FALSE;
            app_usb_mgr_update_event(event);
            break;
        }
        case AIR_USB_EVT_RESUME: {
            APPS_LOG_MSGID_W(LOG_TAG" AIR_USB_EVT_RESUME", 0);
            app_usb_mgr_ready = TRUE;
            app_usb_mgr_cur_event = AIR_USB_EVT_CONFIGURED;
            /* Note: some case only has usb resume event, not have usb configured event, so we treat thess events as the same */
            app_usb_mgr_update_event(event);
            break;
        }

        default:
            break;
    }
}



/**================================================================================*/
/**                                     Public API                                 */
/**================================================================================*/
void app_usb_mgr_init(void)
{
#ifdef HAL_DVFS_MODULE_ENABLED
    hal_dvfs_lock_control(HAL_DVFS_OPP_HIGH, HAL_DVFS_LOCK);
#endif

    int ret = app_usb_mgr_usb_device_init();
    if (ret != 0) {
        APPS_LOG_MSGID_E(LOG_TAG" init, usb_device_init fail", 0);
        return;
    }

    ret = air_usb_create_user("HID_Dongle", &app_usb_mgr_user_id);
    if (ret != 0) {
        APPS_LOG_MSGID_E(LOG_TAG" init, create error user_id=%d ret=%d", 2, app_usb_mgr_user_id, ret);
        return;
    }

    ret = air_usb_register_evt_cb(app_usb_mgr_user_id, app_usb_mgr_usb_evt_cb);
    if (ret != 0) {
        APPS_LOG_MSGID_E(LOG_TAG" init, register_evt_cb error ret=%d", 1, ret);
        return;
    }

    app_usb_mgr_register_usb_hid_cb();

    ret = air_usb_enable();
    APPS_LOG_MSGID_W(LOG_TAG" init, enable user_id=0x%08X ret=%d", 2, app_usb_mgr_user_id, ret);
}

bool app_usb_mgr_send_input_report(bool kb_or_ms, uint8_t *data, uint16_t length)
{
    bool success = FALSE;
    if (data == NULL || length == 0 || !app_usb_mgr_ready) {
        APPS_LOG_MSGID_E(LOG_TAG" send_input_report, error data=0x%08X length=%d ready=%d", 3, data, length, app_usb_mgr_ready);
        return FALSE;
    }

    if (kb_or_ms) {
        air_usb_hid_office_kb_report_t kb_report = {0};
        kb_report.report_id = AIR_USB_HID_OFFICE_KB_REPORT_ID;
        kb_report.modifier = data[0];
        // ignore data[1]=padding
        memcpy(&kb_report.key[0], &data[2], 6);
        success = app_usb_mgr_send_kb_report(&kb_report);
    } else {
        air_usb_hid_office_mouse_report_t ms_report = {0};
        ms_report.report_id = AIR_USB_HID_OFFICE_MS_REPORT_ID;
        ms_report.button[0] = data[0] & 0x1F;
        memcpy((uint8_t *)(&ms_report.button[1]) + 1, &data[1], 5);
        success = app_usb_mgr_send_ms_report(&ms_report);

        // APPS_LOG_MSGID_I(LOG_TAG" send_input_report, dump HOGP=%02X:%02X:%02X:%02X:%02X:%02X USB:button[1]=%02X button[0]=%02X X=%03X Y=%03X",
        //                   10, data[0], data[1], data[2], data[3], data[4], data[5],
        //                   ms_report.button[1], ms_report.button[0], ms_report.x, ms_report.y);
    }

    APPS_LOG_MSGID_I(LOG_TAG" send_input_report, kb_or_ms=%d data=0x%08X length=%d success=%d",
                     4, kb_or_ms, data, length, success);
    return success;
}

