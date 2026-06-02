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

#include <stdint.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/bluetooth/hci_types.h>
#include <zephyr/bluetooth/hci.h>

#include "app_state.h"
#include "app_button.h"
#include "app_motion_sensor.h"

#include "app_battery.h"
#include "app_power_manager.h"
#include "app_usb_port.h"
#include "app_links.h"
#include "app_scenario.h"
#include "app_wheel.h"
#include "app_links.h"
#include "app_led.h"
#include "app_rgb.h"
#include "app_argb.h"
// #include "app_argb_effect.h"
#include "app_race_cmd.h"
#include "app_slide_switch.h"
#include "app_user_profile.h"
#include "app_irpt.h"
#include "app_gpio.h"
#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#include "app_key_remap.h"
#endif
#include "app_fake_report.h"
#include "app_hogp.h"
#include "app_labtest.h"
#include "app_usb_report.h"
#include "app_pin_config_parser.h"
#include "app_fota_status.h"

#include <zephyr/settings/settings.h>
#include <zephyr/bluetooth/bluetooth.h>

#include "hid_scenario_service.h"
#include "hid_common.h"
#include "app_la_debug.h"
#include "nvkey.h"
#include "hal_wdt.h"
#include "app_sw_debounce.h"
#include "hal_clock_internal.h"

#define thisMODULE state_mgr_mouse
#define thisMOD    "state_mgr_mouse"
LOG_MODULE_REGISTER(thisMODULE);
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
static void app_state_mouse_init_modules();


/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/


/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
static bool app_state_mouse__evt_module_init(const struct af_evt_header *evt_header)
{
    APP_LOGI(thisMOD,"app_state_mouse__evt_module_init");
    #if 0
    APP_LOGI(thisMOD,"[SWLA]label_app_main STOP");
    HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_app_main, SWLA_DIRECTION_STOP);
    APP_LOGI(thisMOD,"[SWLA]label_app_state_init START");
    HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_app_state_init, SWLA_DIRECTION_START);
    #endif
    app_state_init();
    app_state_mouse_init_modules();

    return AF_TRAVERSE_NEXT;
}

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static void app_state_mouse_init_modules()
{
    APP_LOGI(thisMOD,"app_state_mouse_init_modules ");

    T_GPIO_PIN_USAGE_LIST_S pin_usage_list;
    app_pin_config_parser_init(&pin_usage_list);

    app_gpio_init(&pin_usage_list);

    #if defined (CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH)
    app_slide_switch_init(pin_usage_list.ctrl.slide_switch_ptr);
    #endif /* _CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH_ */

    app_links_init();

    bool power_ok = app_battery_init();
    APP_LOGI(thisMOD,"power_ok = %d", power_ok);

    app_power_mgr_init();

    uint32_t profile_idx = app_user_profile_init();
    app_scenario_init(profile_idx);

    #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
    app_usb_report_init();
    app_usb_port_init();
    #endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/

    app_button_init(profile_idx, pin_usage_list.ctrl.key_list_ptr);
    bool enter_labtest = 0;
    #if defined (CONFIG_AIR_TEST_GESTURE)
    enter_labtest = app_button_labtest_combo_key_pressed();
    #endif /* CONFIG_AIR_TEST_GESTURE */
    app_labtest_init(enter_labtest);
    if(enter_labtest){
        return;
    }
    #if defined(CONFIG_AIR_SW_KEY_DEBOUNCE)
    app_sw_deb_init(profile_idx);
    #endif
    app_motion_sensor_init(profile_idx);

    #if defined(CONFIG_AIR_TEST_GESTURE)
    app_fake_report_init();
    #endif

    app_irpt_init();

    app_wheel_init();

    //app_cis_init();
    app_race_cmd_init();
    app_hogp_init();

    #if defined (CONFIG_AIR_MIDDLE_LED) && !defined (CONFIG_AIR_HID_DEBUG_PIN)
    #if !defined(CONFIG_AIR_M21_SAMPLE)
    app_led_init(pin_usage_list.ctrl.single_led_ptr);
    #endif
    #endif

    app_rgb_init();
    app_argb_init();
    app_fota_status_init();
    #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    app_key_remap_init(profile_idx);
    #endif

    app_la_debug_init(&pin_usage_list);
    APP_LOGI(thisMOD,"app_state_mouse_init_modules end");
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
bool app_state_device_active()
{
    bool key_pressed = app_button_is_key_pressed();
    bool motion_active = app_motion_sensor_is_motion_pin_active();
    return (key_pressed || motion_active);
}

/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_module_init, app_state_mouse__evt_module_init);


/*=============================================================================*/