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

#if defined (CONFIG_AIR_MIDDLE_LED) && !defined (CONFIG_AIR_HID_DEBUG_PIN)
#include "app_led.h"
#include "app_state.h"
#include "app_battery.h"

#include "led_middle_control.h"

#define thisMOD    "led"
#define thisMODULE led
LOG_MODULE_REGISTER(thisMODULE);

#define FORCE_OPTION          0
#define STYLE_STANDBY_STAY    4
#define STYLE_CONNECTED       2
#define STYLE_PAIRING         3
#define STYLE_CHARGING        4
#define STYLE_RECONNECT       5

#define STYLE_RR_CHANGE       6
#define STYLE_MODE_CHANGE     7

#define STYLE_TEST_MODE       4
#define STYLE_BAT_WARNING     5
#define STYLE_NONE_500MS      8
#define STYLE_NONE_1S         9

#define LED_COLOR_RED         0
#define LED_COLOR_GREEN       1
#define LED_COLOR_BLUE        2

/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
static void app_led__app_state_handler(uint8_t state);
static void app_led__enable_all_led(led_pattern_type_t led_pattern, uint8_t *style);
static void app_led_close_led(led_num_t led_num, led_pattern_type_t led_pattern);
static bool app_led__check_and_play_charging();
void app_led__setting_all_style(uint8_t *store_rgb, uint8_t style);

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
const one_led_style_t   led_default_pattern_setting[] = {
    /* t0,  t1_rising   t1_lightest     t2_falling     t2_darkest  t3   repeat_t1t2  repeat_ext  brightness  start_brightness  end_brightness    onoff*/
    /* no.0  Constant on */
    { 0,       0,      10000,              0,             0,       0,       1,          100,        125,          0,                 0,          LED_ON },
    /* no.1  1-time flash */
    { 0,     200,        100,            200,             0,    2500,       1,          255,        150,          0,                 0,          LED_ON },
    /* no.2  2-times flash  */
    { 0,     200,        100,            200,           500,       0,       2,            1,        150,          0,                 0,          LED_ON },
    /* no.3  Continuous 2-times flash */
    { 0,     200,        100,            200,           500,    1000,       2,          255,        150,          0,                 0,          LED_ON },
    /* no.4  Continuous slow breathing light */
    { 0,     500,        500,            500,             0,       0,      10,          255,        150,          0,                 0,          LED_ON },
    /* no.5  Continuous quick flash */
    { 0,     200,        100,              0,           200,       0,      10,          255,        150,          0,                 0,          LED_ON },
    /* no.6  1-time quick flash */
    { 0,     200,        100,              0,           200,       0,       1,            1,        150,          0,                 0,          LED_ON },
    /* no.7  2-times quick flash */
    { 0,     200,        100,              0,           200,       0,       2,            1,        150,          0,                 0,          LED_ON },
    /* no.8  No light (0.5s)*/
    { 0,       0,          0,              0,             0,     500,       1,            1,          0,          0,                 0,          LED_ON },
    /* no.9  No light (1s)*/
    { 0,       0,          0,              0,             0,    1000,       1,            1,          0,          0,                 0,          LED_ON },
};

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
static void app_led__app_state_handler(uint8_t state)
{
    uint8_t style_rgb[3] = {0};
    APP_LOGI(thisMOD,"app_led__app_state_handler, state = %d", state);

    switch(state)
    {
        case APP_STATE_USB_ACTIVE:
        {
            app_led__setting_all_style(style_rgb, STYLE_CONNECTED);
            app_led__enable_all_led(LED_PATTERN_BG, style_rgb);
            break;
        }
        case APP_STATE_BT_CONNECTED_ACTIVE:
        case APP_STATE_2_4G_CONNECTED_ACTIVE:
        {
            app_led__setting_all_style(style_rgb, STYLE_CONNECTED);
            app_led__enable_all_led(LED_PATTERN_BG, style_rgb);
            break;
        }
        case APP_STATE_2_4G_PAIRING:
        {
            app_led__setting_all_style(style_rgb, STYLE_NONE_1S);
            style_rgb[LED_COLOR_RED] = STYLE_PAIRING;
            app_led__enable_all_led(LED_PATTERN_BG, style_rgb);
            break;
        }
        case APP_STATE_BT_PAIRING:
        {
            app_led__setting_all_style(style_rgb, STYLE_NONE_1S);
            style_rgb[LED_COLOR_BLUE] = STYLE_PAIRING;
            app_led__enable_all_led(LED_PATTERN_BG, style_rgb);
            break;
        }
        case APP_STATE_2_4G_RECONNECT:
        {
            app_led__setting_all_style(style_rgb, STYLE_NONE_1S);
            style_rgb[LED_COLOR_RED] = STYLE_RECONNECT;
            app_led__enable_all_led(LED_PATTERN_BG, style_rgb);
            break;
        }
        case APP_STATE_BT_RECONNECT:
        {
            app_led__setting_all_style(style_rgb, STYLE_NONE_1S);
            style_rgb[LED_COLOR_BLUE] = STYLE_RECONNECT;
            app_led__enable_all_led(LED_PATTERN_BG, style_rgb);
            break;
        }
        case APP_STATE_STANDBY:
        {
            #if defined (AIR_APP_STANDBY_WITH_ADAPTOR_RGB)
            if(app_usb_port__get_usb_plug_status() != APP_USB_PLUG_OUT)
            {
                APP_LOGI(thisMOD,"standby state with adaptor in, Show Your LED here...");
                app_led__setting_all_style(style_rgb, STYLE_STANDBY_STAY);
                app_led__enable_all_led(LED_PATTERN_BG, style_rgb);
            }
            else
            #endif
            {
                app_led__disable_all_led();
            }
            break;
        }
        case APP_STATE_CONNECT_PREPARING:
        case APP_STATE_USB_SUSPEND:
        case APP_STATE_TEST:
        case APP_STATE_CONNECT_CANCEL:
        case APP_STATE_BT_DISCONNECTING:
        case APP_STATE_2_4G_DISCONNECTING:
        case APP_STATE_USB_DISCONNECTING:
        {
            break;
        }
        case APP_STATE_DISCONNECTED:
        {
            app_led__disable_all_led();
            break;
        }
        default:{
            break;
        }
    }
}

static bool app_led__evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state* event = (struct evt_app_state*)evt_header;
    APP_LOGI(thisMOD,"app_led__evt_app_state, app_state = %d", event->app_state);
    app_led__app_state_handler(event->app_state);

    return AF_TRAVERSE_NEXT;
}

static bool app_led__evt_slide_switch_status(const struct af_evt_header *evt_header)
{
    struct evt_slide_switch_status* event = (struct evt_slide_switch_status*)evt_header;
    APP_LOGI(thisMOD,"app_led__evt_slide_switch_status, status = %d", event->position);

    switch(event->position)
    {
        #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        case SLIDE_SWITCH_POS_BT:
        #endif
        #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_GAMING_MODE)
        case SLIDE_SWITCH_POS_GAMING:
        #endif
        #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
        case SLIDE_SWITCH_POS_OFF:
        #endif
        {
            uint8_t style_rgb[3] = {0};
            app_led__setting_all_style(style_rgb, STYLE_NONE_1S);
            style_rgb[LED_COLOR_GREEN] = STYLE_MODE_CHANGE;
            app_led__enable_all_led(LED_PATTERN_FG, style_rgb);
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_led__evt_enter_test(const struct af_evt_header *evt_header)
{
    struct evt_enter_test* event = (struct evt_enter_test*)evt_header;
    APP_LOGI(thisMOD,"app_led__evt_enter_test, target_mode = %d", event->type);

    switch(event->type)
    {
        // case TEST_TYPE_LAB_TEST:
        case TEST_TYPE_RELAY_MODE:
        {
            uint8_t style_rgb[3] = {0};
            app_led__setting_all_style(style_rgb, STYLE_NONE_1S);
            style_rgb[LED_COLOR_GREEN] = STYLE_TEST_MODE;
            app_led__enable_all_led(LED_PATTERN_FG, style_rgb);
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_led__evt_link_change(const struct af_evt_header *evt_header)
{
    struct evt_link_change* event = (struct evt_link_change*)evt_header;
    APP_LOGI(thisMOD,"app_led__evt_link_change, target_mode = %d", event->type);

    switch(event->type)
    {
        case CHANGE_NEXT_LINK:
        {
            uint8_t style_rgb[3] = {0};
            app_led__setting_all_style(style_rgb, STYLE_NONE_1S);
            style_rgb[LED_COLOR_GREEN] = STYLE_MODE_CHANGE;
            app_led__enable_all_led(LED_PATTERN_FG, style_rgb);
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_led__evt_rr_status(const struct af_evt_header *evt_header)
{
    struct evt_rr_status* event = (struct evt_rr_status*)evt_header;
    APP_LOGI(thisMOD,"app_led__evt_rr_status, event->category = %d", event->category); // gaming = 1, usb rr = 0

    if((app_state_check(TYPE_IN_USB_STATES) && event->category == 0) ||
        (app_state_check(TYPE_IN_GAMING_STATES) && event->category == 1))
    {
        uint8_t style_rgb[3] = {0};
        app_led__setting_all_style(style_rgb, STYLE_NONE_500MS);
        style_rgb[LED_COLOR_GREEN] = STYLE_RR_CHANGE;
        app_led__enable_all_led(LED_PATTERN_FG, style_rgb);
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_led__evt_app_battery(const struct af_evt_header *evt_header)
{
    struct evt_app_battery* event = (struct evt_app_battery*)evt_header;
    APP_LOGI(thisMOD,"app_led__evt_app_battery, val = %d, cmd = %d", event->val, event->status);

    switch(event->status)
    {
        case BAT_EVT_LOW_BAT_WARNING:
        {
            if(!app_battery__get_bat_charge_status())
            {
                uint8_t style_rgb[3] = {0};
                app_led__setting_all_style(style_rgb, STYLE_NONE_1S);
                style_rgb[LED_COLOR_RED] = STYLE_BAT_WARNING;
                style_rgb[LED_COLOR_GREEN] = STYLE_BAT_WARNING;
                app_led__enable_all_led(LED_PATTERN_FG, style_rgb);
            }
            break;
        }
        case BAT_EVT_END_OF_CHARGE:  //4
        {
            app_led__disable_all_led();
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}

#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
static bool app_led__evt_usb_status(const struct af_evt_header *evt_header)
{
    struct evt_usb_status* event = (struct evt_usb_status*)evt_header;
    APP_LOGI(thisMOD,"app_led__evt_usb_status, target_mode = %d", event->status);

    switch(event->status)
    {
        case USB_STATUS_PLUGGED_IN:
        case USB_STATUS_PLUGGED_OUT:
        {
            uint8_t style_rgb[3] = {0};
            app_led__setting_all_style(style_rgb, STYLE_NONE_1S);
            style_rgb[LED_COLOR_GREEN] = STYLE_MODE_CHANGE;
            app_led__enable_all_led(LED_PATTERN_FG, style_rgb);

            bool ret = app_led__check_and_play_charging();
            APP_LOGI(thisMOD,"play_charging_led, ret = %d", ret);
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}
#endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static void app_led__enable_all_led(led_pattern_type_t led_pattern, uint8_t *style)
{
    APP_LOGI(thisMOD,"CALL enable all led, led_pattern = %d, (R:G:B) = (%d:%d:%d)", led_pattern, style[0], style[1], style[2]);
    led_middle_control_enable(LED_RED, led_pattern, style[0], FORCE_OPTION);
    led_middle_control_enable(LED_GREEN, led_pattern, style[1], FORCE_OPTION);
    led_middle_control_enable(LED_BLUE, led_pattern, style[2], FORCE_OPTION);
}

static void app_led_close_led(led_num_t led_num, led_pattern_type_t led_pattern)
{
    int ret = led_middle_control_disable(led_num, led_pattern, FORCE_OPTION);
    if(ret == LED_MIDDLE_STATUS_OK || ret == LED_MIDDLE_STATUS_OK_DONE)
    {
        switch(led_num)
        {
            case LED_BLUE:
            {
                APP_LOGI(thisMOD,"led_middle_control_disable(BLUE)");
                break;
            }
            case LED_GREEN:
            {
                APP_LOGI(thisMOD,"led_middle_control_disable(GREEN)");
                break;
            }
            case LED_RED:
            {
                APP_LOGI(thisMOD,"led_middle_control_disable(RED)");
                break;
            }
            default:
                break;
        }
    }
}

void app_led__setting_all_style(uint8_t *store_rgb, uint8_t style){
    for (int i = 0; i < 3; ++i){
        store_rgb[i] = style;
    }
}

static bool app_led__check_and_play_charging()
{
    #if defined (AIR_BATTERY_MANAGEMENT_ENABLE)
    APP_LOGI(thisMOD,"app_led__check_and_play_charging");

    if(!app_battery__get_bat_charge_status()){
        goto _false_return;
    }
    uint8_t battery_level = app_battery__get_battery_level();
    if(battery_level < 0 && battery_level > 100){
        APP_LOGI(thisMOD,"error with battery_level");
        goto _false_return;
    }
    else if(battery_level == 100){
        APP_LOGI(thisMOD,"full battery_level");
        goto _false_return;
    }

    uint8_t style_rgb[3] = {0};
    app_led__setting_all_style(style_rgb, STYLE_NONE_1S);
    style_rgb[LED_COLOR_BLUE] = STYLE_CHARGING;
    app_led__enable_all_led(LED_PATTERN_BG, style_rgb);

    return true;

_false_return:
    app_led__disable_all_led();
    #endif /* AIR_BATTERY_MANAGEMENT_ENABLE */

    return false;
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
void app_led_init(T_SINGLE_LED_PIN_S *single_led_ptr)
{
    if (single_led_ptr){
        APP_LOGI(thisMOD, "app_led_init pin = %d, %d, %d ", single_led_ptr->led_0, single_led_ptr->led_1, single_led_ptr->led_2);
    }

    APP_LOGI(thisMOD, "app_led_init start");
}

void app_led__disable_all_led(void)
{
    APP_LOGI(thisMOD,"CALL close all led");
    app_led_close_led(LED_RED, LED_PATTERN_BG);
    app_led_close_led(LED_GREEN, LED_PATTERN_BG);
    app_led_close_led(LED_BLUE, LED_PATTERN_BG);
}

/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_app_state, app_led__evt_app_state);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_app_battery, app_led__evt_app_battery);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_enter_test, app_led__evt_enter_test);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_link_change, app_led__evt_link_change);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_rr_status, app_led__evt_rr_status);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_slide_switch_status, app_led__evt_slide_switch_status);
#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_usb_status, app_led__evt_usb_status);
#endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/
#endif /*END _CONFIG_AIR_MIDDLE_LED_*/

/*=============================================================================*/
