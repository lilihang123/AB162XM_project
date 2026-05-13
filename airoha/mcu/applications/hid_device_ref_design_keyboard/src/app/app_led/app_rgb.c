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

#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>

#include "app_rgb.h"
#include "app_state.h"
#include "app_battery.h"
#include "app_nvkey.h"
#include "rgb_middle_control.h"
#include "rgb_control_style_cfg.h"

#if defined (CONFIG_AIR_MIDDLE_LED) && defined (CONFIG_AIR_MIDDLE_RGB)
#include "app_led.h"
#endif

#define thisMODULE app_rgb
#define thisMOD    "app_rgb"
LOG_MODULE_REGISTER(thisMODULE);

#define UNUSED(x)  ((void)(x))

#define RACE_RSP_SPEED_FAST    0x00 // original val: 0x80
#define RACE_RSP_SPEED_SLOW    0xFF
#define RACE_RSP_SPEED_NORMAL  0x00
#define RACE_RSP_RT_PAUSE      0x01
#define RACE_RSP_RT_RESUME     0x02

#if defined (CONFIG_AIR_MIDDLE_RGB)
#define RGB_STATUS_NONE       0
#define RGB_NORMAL_PLAY       1
#define RGB_REALTIME          2
#define RGB_FLASH_START       3
#define RGB_FLASH_PAUSE       4
#define RGB_ALL_TYPE          5

#define RGB_FLASH_ID_NONE     0
#define RGB_FLASH_ID_0        0x6200  //NVID_RGB_ID_0_DATA0
#define RGB_FLASH_ID_1        0x6208  //NVID_RGB_ID_1_DATA0
#define RGB_FLASH_ID_2        0x6210  //NVID_RGB_ID_2_DATA0
#define RGB_FLASH_ID_3        0x6218  //NVID_RGB_ID_3_DATA0
#define RGB_DEFAULT           0x6220  //NVID_RGB_DEFAULT_FLASH

#define FORCE_OPTION          0

#define STYLE_CONSTANT_ON     0
#define STYLE_BREATHING       1
#define STYLE_CONNECTED       2
#define STYLE_QUICK_FLASH     5

#define STYLE_PAIRING         3
#define STYLE_CHARGING        4
#define STYLE_RECONNECT       5

#define STYLE_RR_CHANGE       6
#define STYLE_MODE_CHANGE     7

#define STYLE_TEST_MODE       4
#define STYLE_BAT_WARNING     5
#define STYLE_NONE_500MS      8
#define STYLE_REMIND          9

#define RGB_COLOR_RED         0
#define RGB_COLOR_GREEN       1
#define RGB_COLOR_BLUE        2

typedef struct {
    uint8_t num;        //rgb id number
    uint16_t nvid;      //flash nvid
    uint8_t repeat;     //flash repeat
    uint8_t state;      //normal/flash/realtime
    uint8_t style;      //normal rgb
    uint8_t pattern;    //normal pattern
} T_APP_RGB_INFO_S;

#define RGB_LEVEL_MAX        15

/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
#if !defined (CONFIG_AIR_HID_DEBUG_PIN)
static void app_rgb__handle_realtime_rgb(uint8_t *data, uint8_t *color);
static void app_rgb__check_race_cmd_realtime_speed(uint8_t status);
static void app_rgb__race_cmd_rsp_announcement(T_RACE_CMD_E cmd, uint8_t status);
static int8_t app_rgb__disable_rgb(T_APP_RGB_INFO_S *rgb_id);
static void app_rgb__flash_finish_handle(void *user_data);
static void app_rgb__normal_play_finish_handle(void *user_data);
static bool app_rgb__enable_flash_rgb(T_APP_RGB_INFO_S *rgb_id);
static bool app_rgb__enable_normal_rgb(T_APP_RGB_INFO_S *rgb_id);
static void app_rgb__app_state_handler(uint8_t state);

#if defined (AIR_BATTERY_MANAGEMENT_ENABLE)
static bool app_rgb__check_and_play_charging_rgb();
#endif
static bool app_rgb__check_and_play_flash();
#endif /* _!DEF_CONFIG_AIR_HID_DEBUG_PIN_ */

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
bool led_flag = true;  //true means interrupt LED
bool flash_flag = false;
bool realtime_flag = false;
uint16_t saved_flash = RGB_DEFAULT;
T_APP_RGB_INFO_S rgb_id_0;

#if !defined (CONFIG_AIR_HID_DEBUG_PIN)
bool cmd_retry = false;
bool charging_flag = false;
uint8_t curr_speed = 0;
uint8_t state_stay = APP_STATE_NONE;

one_rgb_style_t   rgb_default_pattern_setting[] = {
    /* t0,  t1_rising   t1_lightest     t2_falling     t2_darkest  t3   repeat_t1t2  repeat_ext  brightness  start_brightness  end_brightness  onoff*/
    /* no.0  Constant on */
    {
        { 0,       0,       2000,              0,             0,       0,       1,       255,        255,          0,                 0,        RGB_ON },
        { 0,       0,       2000,              0,             0,       0,       1,       255,        255,          0,                 0,        RGB_ON },
        { 0,       0,       2000,              0,             0,       0,       1,       255,        255,          0,                 0,        RGB_ON },
    },
    /* no.1  Continuous breathing */
    {
        { 0,     200,        100,            200,             0,     500,       1,       255,        255,          0,                 0,        RGB_ON },
        { 0,     200,        100,            200,             0,     500,       1,       255,        255,          0,                 0,        RGB_ON },
        { 0,     200,        100,            200,             0,     500,       1,       255,        255,          0,                 0,        RGB_ON },
    },
    /* no.2  2-times flash */
    {
        { 0,     200,        100,            200,           500,       0,       2,         1,        255,          0,                 0,        RGB_ON },
        { 0,     200,        100,            200,           500,       0,       2,         1,        255,          0,                 0,        RGB_ON },
        { 0,     200,        100,            200,           500,       0,       2,         1,        255,          0,                 0,        RGB_ON },
    },
    /* no.3  Continuous 2-times flash */
    {
        { 0,     200,        100,            200,           500,    1000,       2,       255,        255,          0,                 0,        RGB_ON },
        { 0,     200,        100,            200,           500,    1000,       2,       255,        255,          0,                 0,        RGB_ON },
        { 0,     200,        100,            200,           500,    1000,       2,       255,        255,          0,                 0,        RGB_ON },
    },
    /* no.4  Continuous slow breathing light */
    {
        { 0,     500,        500,            500,             0,       0,      10,       255,        255,          0,                 0,        RGB_ON },
        { 0,     500,        500,            500,             0,       0,      10,       255,        255,          0,                 0,        RGB_ON },
        { 0,     500,        500,            500,             0,       0,      10,       255,        255,          0,                 0,        RGB_ON },
    },
    /* no.5  Continuous quick flash */
    {
        { 0,     200,        100,              0,           200,       0,       2,       255,        255,          0,                 0,        RGB_ON },
        { 0,     200,        100,              0,           200,       0,       2,       255,        255,          0,                 0,        RGB_ON },
        { 0,     200,        100,              0,           200,       0,       2,       255,        255,          0,                 0,        RGB_ON },
    },
    /* no.6  1-time quick flash */
    {
        { 0,     200,        100,              0,           200,       0,       1,         1,        255,          0,                 0,        RGB_ON },
        { 0,     200,        100,              0,           200,       0,       1,         1,        255,          0,                 0,        RGB_ON },
        { 0,     200,        100,              0,           200,       0,       1,         1,        255,          0,                 0,        RGB_ON },
    },
    /* no.7  2-times quick flash */
    {
        { 0,     200,        100,              0,           200,       0,       2,         1,        255,          0,                 0,        RGB_ON },
        { 0,     200,        100,              0,           200,       0,       2,         1,        255,          0,                 0,        RGB_ON },
        { 0,     200,        100,              0,           200,       0,       2,         1,        255,          0,                 0,        RGB_ON },
    },
    /* no.8  No light (0.5s) */
    {
        { 0,       0,          0,              0,             0,     500,       1,         1,          0,          0,                 0,        RGB_ON },
        { 0,       0,          0,              0,             0,     500,       1,         1,          0,          0,                 0,        RGB_ON },
        { 0,       0,          0,              0,             0,     500,       1,         1,          0,          0,                 0,        RGB_ON },
    },
    /* no.9  Blinks once at intervals*/
    {
        { 0,     200,        100,            200,           500,    4000,       1,         1,        150,          0,                 0,        RGB_ON },
        { 0,     200,        100,            200,           500,    4000,       1,         1,        150,          0,                 0,        RGB_ON },
        { 0,     200,        100,            200,           500,    4000,       1,         1,        150,          0,                 0,        RGB_ON },
    },
};

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/
static void app_rgb__flash_finish_handle(void *user_data)
{
    APP_LOGI(thisMOD,"Flash RGB finish");
    UNUSED(user_data);
    flash_flag = false;
}

static void app_rgb__normal_play_finish_handle(void *user_data)
{
    APP_LOGI(thisMOD,"Normal RGB finish");
    UNUSED(user_data);

    bool ret = false;
    static uint8_t state_flag = 0;
    #if defined (AIR_BATTERY_MANAGEMENT_ENABLE)
    if(app_battery__get_bat_charge_en_sta()){
        ret = app_rgb__check_and_play_charging_rgb();
        APP_LOGI(thisMOD,"charging_flag = %d, ret = %d", charging_flag, ret);
    }
    #endif
    if(!ret)
    {
        APP_LOGI(thisMOD,"state_flag = %d", state_flag);
        if(state_stay >= APP_STATE_BT_PAIRING &&
           state_stay <= APP_STATE_2_4G_RECONNECT){
            if(state_flag != state_stay){
                app_rgb__app_state_handler(state_stay);
                state_flag = state_stay;
            }
        }
        app_rgb__check_and_play_flash();
    }
}
#endif /* _!DEF_CONFIG_AIR_HID_DEBUG_PIN_ */
#endif /*END _CONFIG_AIR_MIDDLE_RGB_*/

/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
#if defined (CONFIG_AIR_MIDDLE_RGB)
#if !defined (CONFIG_AIR_HID_DEBUG_PIN)
static bool app_rgb__evt_race_cmd_req(const struct af_evt_header *evt_header)
{
    struct evt_race_cmd_req* event = (struct evt_race_cmd_req*)evt_header;
    APP_LOGI(thisMOD, "app_rgb__evt_race_cmd_req, cmd = %x", event->cmd);

    #if defined (CONFIG_AIR_MIDDLE_LED)
    APP_LOGI(thisMOD,"app_rgb__evt_race_cmd_req, led_flag = %d", led_flag);
    if(!led_flag){
        led_flag = true;
        app_led__disable_all_led();
    }
    #endif

    switch(event->cmd)
    {
        case RACE_CMD_SET_RGB:
        {
            if (event->RGB.rgb_count){
                app_rgb__handle_realtime_rgb((uint8_t*)&event->RGB.rgb_setting, event->RGB.rgb_color);
                k_free(event->RGB.rgb_color);
                event->RGB.rgb_color = NULL;
            }
            else{
                app_rgb__handle_realtime_rgb((uint8_t*)&event->RGB.rgb_setting, NULL);
            }
            break;
        }
        default:{
            break;
        }
    }
    return AF_TRAVERSE_NEXT;
}

static bool app_rgb__evt_app_rgb_test(const struct af_evt_header *evt_header)
{
    struct evt_app_rgb_test* event = (struct evt_app_rgb_test*)evt_header;
    APP_LOGI(thisMOD,"evt_app_rgb_test, cmd = %x", event->cmd);

    if(led_flag){
        switch(event->cmd)
        {
            case TEST_FLASH:
            {
                switch(saved_flash){
                    case RGB_DEFAULT:{
                        saved_flash = RGB_FLASH_ID_0;
                        break;
                    }
                    case RGB_FLASH_ID_0:{
                        saved_flash = RGB_FLASH_ID_1;
                        break;
                    }
                    case RGB_FLASH_ID_1:{
                        saved_flash = RGB_FLASH_ID_2;
                        break;
                    }
                    case RGB_FLASH_ID_2:{
                        saved_flash = RGB_FLASH_ID_3;
                        break;
                    }
                    case RGB_FLASH_ID_3:{
                        saved_flash = RGB_FLASH_ID_NONE;
                        break;
                    }
                    case RGB_FLASH_ID_NONE:{
                        saved_flash = RGB_FLASH_ID_0;
                        break;
                    }
                    default:{
                        break;
                    }
                }

                if(saved_flash == RGB_FLASH_ID_NONE && flash_flag)
                {
                    int8_t ret = app_rgb__disable_rgb(&rgb_id_0);
                    APP_LOGI(thisMOD,"Close flash RGB, ret = %d", ret);
                    if(ret >= 0)
                    {
                        nvkey_delete_data_item(NVID_RGB_DEFAULT_FLASH);
                        flash_flag = false;
                        rgb_middle_running_status_t status;
                        rgb_middle_get_running_status(rgb_id_0.num, &status);
                        if(!status && state_stay == APP_STATE_USB_ACTIVE){
                            app_rgb__app_state_handler(state_stay);
                        }
                    }
                }
                else
                {
                    rgb_id_0.nvid = saved_flash;
                    rgb_id_0.repeat = 255;
                    app_rgb__enable_flash_rgb(&rgb_id_0);
                }

                break;
            }
            default:{
                break;
            }
        }
    }
    return AF_TRAVERSE_NEXT;
}

static bool app_rgb_evt_rr_change_req(const struct af_evt_header *evt_header)
{
    struct evt_rr_change_req* event = (struct evt_rr_change_req*)evt_header;
    APP_LOGI(thisMOD, "app_rgb_evt_rr_change_req, change_type = %x", event->change_type);

    switch(event->change_type)
    {
        case RR_CHANGE_NEXT:
        case RR_CHANGE_PREV:
        case RR_CHANGE_SPECIFIC:
        {
            rgb_middle_running_status_t status;
            rgb_middle_get_running_status(rgb_id_0.num, &status);
            APP_LOGI(thisMOD,"Pause RGB realtime, status = %d", status);
            if(rgb_id_0.state == RGB_REALTIME && status){
                realtime_flag = true;
                app_rgb__race_cmd_rsp_announcement(RACE_CMD_SET_RGB, RACE_RSP_RT_PAUSE);
            }
            break;
        }
        default:{
            break;
        }
    }
    return AF_TRAVERSE_NEXT;
}

/******************************************************************************/
/* event handler functions with light effects                                 */
/******************************************************************************/
static bool app_rgb__evt_app_battery(const struct af_evt_header *evt_header)
{
    struct evt_app_battery* event = (struct evt_app_battery*)evt_header;
    APP_LOGI(thisMOD,"app_rgb__evt_app_battery, status = %x", event->status);

    switch(event->status)
    {
        case BAT_EVT_LOW_BAT_WARNING:
        {
            if(!charging_flag)
            {
                rgb_id_0.style = STYLE_BAT_WARNING;
                rgb_default_pattern_setting[rgb_id_0.style].rgb_r.onoff = RGB_OFF;
                rgb_default_pattern_setting[rgb_id_0.style].rgb_g.onoff = RGB_ON;
                rgb_default_pattern_setting[rgb_id_0.style].rgb_b.onoff = RGB_OFF;
                rgb_default_pattern_setting[rgb_id_0.style].rgb_r.repeat_ext = 10;
                rgb_default_pattern_setting[rgb_id_0.style].rgb_g.repeat_ext = 10;
                rgb_default_pattern_setting[rgb_id_0.style].rgb_b.repeat_ext = 10;

                if(led_flag){
                    rgb_id_0.pattern = RGB_PATTERN_FG;
                    app_rgb__enable_normal_rgb(&rgb_id_0);
                }
            }
            break;
        }
        case BAT_EVT_END_OF_CHARGE:  //4
        {
            APP_LOGI(thisMOD,"charging_flag = %d", charging_flag);
            if(charging_flag)
            {
                rgb_middle_status_t ret = rgb_middle_control_disable(rgb_id_0.num, rgb_occupy_rgb, RGB_PATTERN_FG, FORCE_OPTION);
                ret |= rgb_middle_control_disable(rgb_id_0.num, rgb_occupy_rgb, RGB_PATTERN_BG, FORCE_OPTION);
                charging_flag = false;
                if(ret >= 0){
                    app_rgb__check_and_play_flash();
                }
            }
            break;
        }
        case BAT_EVT_CHG_ENABLE_STA_CHANGE:
        {
            /* write light effect here */
            break;
        }
        default:{
            break;
        }
    }
    return AF_TRAVERSE_NEXT;
}

#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
static bool app_rgb__evt_usb_status(const struct af_evt_header *evt_header)
{
    struct evt_usb_status* event = (struct evt_usb_status*)evt_header;
    APP_LOGI(thisMOD,"app_rgb__evt_usb_status, target_mode = %d", event->status);

    switch(event->status)
    {
        case USB_STATUS_PLUGGED_OUT:
        {
            charging_flag = false;
        }  //dont break
        case USB_STATUS_PLUGGED_IN:
        {
            rgb_id_0.style = STYLE_MODE_CHANGE;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_r.onoff = RGB_OFF;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_g.onoff = RGB_ON;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_b.onoff = RGB_OFF;

            if(led_flag){
                rgb_id_0.pattern = RGB_PATTERN_FG;
                app_rgb__enable_normal_rgb(&rgb_id_0);
            }
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}
#endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE */

static bool app_rgb_evt_dpi_status(const struct af_evt_header *evt_header)
{
    struct evt_dpi_status* event = (struct evt_dpi_status*)evt_header;
    APP_LOGI(thisMOD,"app_rgb_evt_dpi_status, dpi_idx = %d", event->dpi_idx);

    #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
    APP_LOGI(thisMOD,"DPI idx = %d, x_dpi = %d, y_dpi = %d", event->dpi_idx, event->x_dpi_value, event->y_dpi_value);
    #else
    APP_LOGI(thisMOD,"DPI idx = %d, dpi = %d", event->dpi_idx, event->dpi_value);
    #endif

    switch(event->dpi_idx)
    {
        case 0:
        {
             /* write light effect here */
            break;
        }
        case 1:
        {
            /* write light effect here */
            break;
        }
        case 2:
        {
            /* write light effect here */
            break;
        }
        case 3:
        {
            /* write light effect here */
            break;
        }
        case 4:
        {
            /* write light effect here */
            break;
        }
        default:{
            break;
        }
    }
    return AF_TRAVERSE_NEXT;
}

static void app_rgb__app_state_handler(uint8_t state)
{
    APP_LOGI(thisMOD,"app_rgb__app_state_handler, state = %d", state);

    switch(state)
    {
        case APP_STATE_USB_ACTIVE:
        {
            rgb_id_0.style = STYLE_CONNECTED;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_r.onoff = RGB_ON;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_g.onoff = RGB_ON;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_b.onoff = RGB_ON;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_r.brightness = 150;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_g.brightness = 150;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_b.brightness = 150;

            if(led_flag){
                rgb_id_0.pattern = RGB_PATTERN_BG;
                app_rgb__enable_normal_rgb(&rgb_id_0);
            }
            break;
        }

        case APP_STATE_BT_PAIRING:
        {
            rgb_id_0.style = STYLE_PAIRING;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_r.onoff = RGB_OFF;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_g.onoff = RGB_OFF;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_b.onoff = RGB_ON;

            if(led_flag){
                rgb_id_0.pattern = RGB_PATTERN_BG;
                app_rgb__enable_normal_rgb(&rgb_id_0);
            }
            break;
        }

        case APP_STATE_2_4G_PAIRING:
        {
            rgb_id_0.style = STYLE_PAIRING;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_r.onoff = RGB_ON;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_g.onoff = RGB_OFF;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_b.onoff = RGB_OFF;

            if(led_flag){
                rgb_id_0.pattern = RGB_PATTERN_BG;
                app_rgb__enable_normal_rgb(&rgb_id_0);
            }
            break;
        }

        case APP_STATE_BT_RECONNECT:
        {
            rgb_id_0.style = STYLE_RECONNECT;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_r.onoff = RGB_OFF;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_g.onoff = RGB_OFF;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_b.onoff = RGB_ON;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_r.repeat_ext = 255;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_g.repeat_ext = 255;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_b.repeat_ext = 255;

            if(led_flag){
                rgb_id_0.pattern = RGB_PATTERN_BG;
                app_rgb__enable_normal_rgb(&rgb_id_0);
            }
            break;
        }

        case APP_STATE_2_4G_RECONNECT:
        {
            rgb_id_0.style = STYLE_RECONNECT;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_r.onoff = RGB_ON;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_g.onoff = RGB_OFF;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_b.onoff = RGB_OFF;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_r.repeat_ext = 255;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_g.repeat_ext = 255;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_b.repeat_ext = 255;

            if(led_flag){
                rgb_id_0.pattern = RGB_PATTERN_BG;
                app_rgb__enable_normal_rgb(&rgb_id_0);
            }
            break;
        }

        case APP_STATE_BT_CONNECTED_ACTIVE:
        case APP_STATE_2_4G_CONNECTED_ACTIVE:
        {
            rgb_id_0.style = STYLE_CONNECTED;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_r.onoff = RGB_ON;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_g.onoff = RGB_ON;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_b.onoff = RGB_ON;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_r.brightness = 150;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_g.brightness = 150;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_b.brightness = 150;

            if(led_flag){
                rgb_id_0.pattern = RGB_PATTERN_BG;
                app_rgb__enable_normal_rgb(&rgb_id_0);
            }
            break;
        }
        case APP_STATE_STANDBY:
        {
            #if defined (CONFIG_AIR_MIDDLE_LED)
            led_flag = false;
            #endif
            rgb_id_0.state = RGB_ALL_TYPE;
            int8_t ret = app_rgb__disable_rgb(&rgb_id_0);
            APP_LOGI(thisMOD,"Enter STANDBY, ret = %d", ret);
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
            if(rgb_id_0.state == RGB_FLASH_START){
                rgb_id_0.state = RGB_FLASH_PAUSE;
                int8_t ret = app_rgb__disable_rgb(&rgb_id_0);
                APP_LOGI(thisMOD,"Cancle flash RGB, ret = %d", ret);
            }
        }
        default:{
            break;
        }

    }
}

static bool app_rgb__evt_enter_test(const struct af_evt_header *evt_header)
{
    struct evt_enter_test* event = (struct evt_enter_test*)evt_header;
    APP_LOGI(thisMOD,"app_rgb__evt_enter_test, target_mode = %d", event->type);

    switch(event->type)
    {
        // case TEST_TYPE_LAB_TEST:
        case TEST_TYPE_RELAY_MODE:
        {
            rgb_id_0.style = STYLE_TEST_MODE;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_r.onoff = RGB_OFF;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_g.onoff = RGB_ON;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_g.brightness = 150;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_b.onoff = RGB_OFF;

            if(led_flag){
                rgb_id_0.pattern = RGB_PATTERN_BG;
                app_rgb__enable_normal_rgb(&rgb_id_0);
            }
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_rgb__evt_link_change(const struct af_evt_header *evt_header)
{
    struct evt_link_change* event = (struct evt_link_change*)evt_header;
    APP_LOGI(thisMOD,"app_rgb__evt_link_change, target_mode = %d", event->type);

    switch(event->type)
    {
        case CHANGE_NEXT_LINK:
        {
            rgb_id_0.style = STYLE_MODE_CHANGE;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_r.onoff = RGB_OFF;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_g.onoff = RGB_ON;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_g.brightness = 150;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_b.onoff = RGB_OFF;

            if(led_flag){
                rgb_id_0.pattern = RGB_PATTERN_FG;
                app_rgb__enable_normal_rgb(&rgb_id_0);
            }
            break;
        }
        default:{
            break;
        }
    }
    return AF_TRAVERSE_NEXT;
}

static bool app_rgb__evt_rr_status(const struct af_evt_header *evt_header)
{
    struct evt_rr_status* event = (struct evt_rr_status*)evt_header;
    APP_LOGI(thisMOD,"app_rgb__evt_rr_status, event->category = %d, app_state = %d", event->category, state_stay); // gaming = 1, usb rr = 0

    if(rgb_id_0.state == RGB_REALTIME && realtime_flag){
        realtime_flag = false;
        app_rgb__race_cmd_rsp_announcement(RACE_CMD_SET_RGB, RACE_RSP_RT_RESUME);
    }

    if((app_state_check(TYPE_IN_USB_STATES) && event->category == 0) ||
        (app_state_check(TYPE_IN_GAMING_STATES) && event->category == 1))
    {
        rgb_id_0.style = STYLE_RR_CHANGE;
        rgb_default_pattern_setting[rgb_id_0.style].rgb_r.onoff = RGB_OFF;
        rgb_default_pattern_setting[rgb_id_0.style].rgb_g.onoff = RGB_ON;
        rgb_default_pattern_setting[rgb_id_0.style].rgb_g.brightness = 150;
        rgb_default_pattern_setting[rgb_id_0.style].rgb_b.onoff = RGB_OFF;

        if(led_flag){
            rgb_id_0.pattern = RGB_PATTERN_FG;
            app_rgb__enable_normal_rgb(&rgb_id_0);
        }
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_rgb__evt_slide_switch_status(const struct af_evt_header *evt_header)
{
    struct evt_slide_switch_status* event = (struct evt_slide_switch_status*)evt_header;
    APP_LOGI(thisMOD,"app_rgb__evt_slide_switch_status, status = %d", event->position);

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
            rgb_id_0.style = STYLE_MODE_CHANGE;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_r.onoff = RGB_OFF;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_g.onoff = RGB_ON;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_g.brightness = 150;
            rgb_default_pattern_setting[rgb_id_0.style].rgb_b.onoff = RGB_OFF;

            if(led_flag){
                rgb_id_0.pattern = RGB_PATTERN_FG;
                app_rgb__enable_normal_rgb(&rgb_id_0);
            }
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_rgb__evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state* event = (struct evt_app_state*)evt_header;
    APP_LOGI(thisMOD,"app_rgb__evt_app_state, app_state = %d", event->app_state);
    state_stay = event->app_state;
    app_rgb__app_state_handler(event->app_state);

    return AF_TRAVERSE_NEXT;
}
#endif /* _!DEF_CONFIG_AIR_HID_DEBUG_PIN_ */
#endif /*END _CONFIG_AIR_MIDDLE_RGB_*/

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
#if defined (CONFIG_AIR_MIDDLE_RGB)
#if !defined (CONFIG_AIR_HID_DEBUG_PIN)
static void app_rgb__handle_realtime_rgb(uint8_t *data, uint8_t *color)
{
    T_SET_RGB_INFO_S *rgb_info = (T_SET_RGB_INFO_S *)data;
    APP_LOGI(thisMOD,"app_rgb__handle_realtime_rgb, setting = 0x%X, seq_num = 0x%X, interval = 0x%X, count = 0x%X, status = %d",
                                                rgb_info->setting,
                                                rgb_info->num,
                                                rgb_info->interval,
                                                rgb_info->count,
                                                rgb_id_0.state);
    int status = RGB_MIDDLE_STATUS_ERROR;
    switch(rgb_info->setting)
    {
        case APP_RGB_CONTINUE:
        {
            if(rgb_id_0.state != RGB_REALTIME){
                rgb_id_0.state = RGB_REALTIME;
            }
            uint8_t cnt = rgb_info->count;
            rgb_pattern_data_t rgb_data = {0};
            if(cnt > 0)
            {
                uint8_t itl = 0;
                for(int idx = 0; idx < cnt; idx++)
                {
                    APP_LOGI(thisMOD,"app_rgb__handle_realtime_rgb, color[%d] = 0x%X, color[%d] = 0x%X, color[%d] = 0x%X",
                                                itl, color[itl], itl+1, color[itl+1], itl+2, color[itl+2]);
                    rgb_data.cfg_r = &color[itl];
                    rgb_data.cfg_g = &color[itl+1];
                    rgb_data.cfg_b = &color[itl+2];
                    rgb_data.interval = rgb_info->interval;
                    rgb_id_0.state = RGB_REALTIME;
                    status = rgb_middle_control_enable_for_node(rgb_id_0.num, rgb_data, RGB_LEVEL_MAX, rgb_id_0.state);
                    itl += 3;
                    if(status < 0){
                        APP_LOGI(thisMOD,"rgb_middle_control_realtime_enable fail, enable status = %d", status);
                        break;
                    }
                }
            }

            app_rgb__check_race_cmd_realtime_speed(status);
            break;
        }
        case APP_RGB_START:
        {
            rgb_id_0.state = RGB_REALTIME;
            break;
        }
        case APP_RGB_STOP:
        {
            int8_t ret = app_rgb__disable_rgb(&rgb_id_0);
            APP_LOGI(thisMOD,"APP_RGB_STOP, ret = %d", ret);

            if(ret >= 0 && flash_flag)
            {
                rgb_id_0.nvid = saved_flash;
                rgb_id_0.repeat = 255;
                app_rgb__enable_flash_rgb(&rgb_id_0);
            }
            else{
                APP_LOGI(thisMOD,"rgb_middle_control_disable fail");
            }
            break;
        }
        default:{
            break;
        }
    }
}

static bool app_rgb__evt_race_cmd_rsp_for_rgb(const struct af_evt_header *evt_header)
{
    struct evt_race_cmd_rsp_for_rgb* event = (struct evt_race_cmd_rsp_for_rgb*)evt_header;
    APP_LOGI(thisMOD, "app_rgb__evt_race_cmd_rsp_for_rgb, status = %d", event->status);

    if(event->status){
        cmd_retry = true;
    }

    return AF_TRAVERSE_NEXT;
}

static void app_rgb__check_race_cmd_realtime_speed(uint8_t status)
{
    APP_LOGI(thisMOD,"app_rgb__check_race_cmd_realtime_speed, cmd_retry = %d", cmd_retry);
    static uint8_t prev_speed = 0x00;
    if(!cmd_retry){
        prev_speed = curr_speed;
    }
    APP_LOGI(thisMOD, "realtime, deep = %d, prev_speed = 0x%X", status, prev_speed);
    uint8_t diff = (APP_RGB_MAX_COUNT - APP_RGB_MINI_COUNT);
    if(status < APP_RGB_MINI_COUNT){  //3
        curr_speed = RACE_RSP_SPEED_FAST;
    }
    else if(status >= diff){   //7
        curr_speed = RACE_RSP_SPEED_SLOW;
    }
    else if(status >= (diff - APP_RGB_MINI_COUNT)){   //4
        curr_speed = RACE_RSP_SPEED_NORMAL;
    }

    if((prev_speed != curr_speed) || cmd_retry)
    {
        APP_LOGI(thisMOD, "realtime, response speed = 0x%X, retry = %d", curr_speed, cmd_retry);
        cmd_retry = false;
        app_rgb__race_cmd_rsp_announcement(RACE_CMD_SET_RGB, curr_speed);
    }
    return;
}

static void app_rgb__race_cmd_rsp_announcement(T_RACE_CMD_E cmd, uint8_t status)
{
    APP_LOGI(thisMOD, "app_rgb__race_cmd_rsp_announcement, status = 0x%X", status);
    struct evt_race_cmd_rsp* rsp_evt = create_evt_race_cmd_rsp();
    if (rsp_evt)
    {
        rsp_evt->cmd = cmd;
        rsp_evt->OTHERS.status = status;
        AF_EVT_SUBMIT(rsp_evt);
    }
    return;
}

static int8_t app_rgb__disable_rgb(T_APP_RGB_INFO_S *rgb_id)
{
    rgb_middle_status_t ret = RGB_MIDDLE_STATUS_OK;
    APP_LOGI(thisMOD,"CALL close RGB, state = %d, pattern = %d", rgb_id->state, rgb_id->pattern);

    if(rgb_id->state == RGB_FLASH_START || rgb_id->state == RGB_FLASH_PAUSE){
        ret = rgb_middle_control_disable(rgb_id->num, rgb_occupy_flash_rgb, RGB_PATTERN_BG, FORCE_OPTION);
        if(ret >= 0 && rgb_id->state == RGB_FLASH_START){
            flash_flag = false;
        }
    }
    else if(rgb_id->state == RGB_REALTIME){
        ret = rgb_middle_control_disable(rgb_id->num, rgb_occupy_realtime_rgb, RGB_PATTERN_FG, FORCE_OPTION);
        realtime_flag = false;
    }
    else if(rgb_id->state == RGB_NORMAL_PLAY)
    {
        ret = rgb_middle_control_disable(rgb_id->num, rgb_occupy_rgb, RGB_PATTERN_FG, FORCE_OPTION);
        ret |= rgb_middle_control_disable(rgb_id->num, rgb_occupy_rgb, RGB_PATTERN_BG, FORCE_OPTION);
    }
    else if(rgb_id->state == RGB_ALL_TYPE)
    {
        ret = rgb_middle_control_disable(rgb_id->num, rgb_occupy_flash_rgb, RGB_PATTERN_BG, FORCE_OPTION);
        ret |= rgb_middle_control_disable(rgb_id->num, rgb_occupy_realtime_rgb, RGB_PATTERN_FG, FORCE_OPTION);
        ret |= rgb_middle_control_disable(rgb_id->num, rgb_occupy_rgb, RGB_PATTERN_FG, FORCE_OPTION);
        ret |= rgb_middle_control_disable(rgb_id->num, rgb_occupy_rgb, RGB_PATTERN_BG, FORCE_OPTION);
    }
    return ret;
}

static bool app_rgb__enable_normal_rgb(T_APP_RGB_INFO_S *rgb_id)
{
    APP_LOGI(thisMOD,"CALL enable normal RGB, state = %d, style = %d, pattern = %d", rgb_id->state, rgb_id->style, rgb_id->pattern);
    if(led_flag)
    {
        rgb_pattern_data_t rgb_data = {0};
        rgb_data.index = rgb_id->style;
        int ret = rgb_middle_control_enable_for_node(rgb_id->num, rgb_data, rgb_id->pattern, RGB_NORMAL_PLAY);
        if(ret < 0){
            APP_LOGI(thisMOD,"normal RGB enable fail, ret = %d", ret);
            return false;
        }
        else
        {
            APP_LOGI(thisMOD,"rgb_middle_control_enable ok");
            rgb_id->state = RGB_NORMAL_PLAY;
            rgb_middle_status_t result;
            result = rgb_middle_register_callback(rgb_id_0.num, app_rgb__normal_play_finish_handle, NULL);
            if(ret < RGB_MIDDLE_STATUS_OK){
                APP_LOGI(thisMOD,"rgb_middle_register_callback fail, ret = %d", result);
                return false;
            }
            return true;
        }
    }
    return false;
}

static bool app_rgb__enable_flash_rgb(T_APP_RGB_INFO_S *rgb_id)
{
    APP_LOGI(thisMOD,"CALL enable flash RGB, state = %d, nvid = 0x%X, repeat = %d", rgb_id->state, rgb_id->nvid, rgb_id->repeat);

    if(led_flag && rgb_id->nvid && rgb_id->repeat)
    {
        rgb_pattern_data_t rgb_data = {0};
        rgb_data.index = rgb_id->nvid;
        rgb_data.interval = rgb_id->repeat;
        int ret = rgb_middle_control_enable_for_node(rgb_id->num, rgb_data, RGB_PATTERN_BG, RGB_FLASH_START);
        if(ret < 0){
            APP_LOGI(thisMOD,"RGB_NVID = 0x%X, enable fail, ret = %d", rgb_id->nvid, ret);
            nvkey_delete_data_item(NVID_RGB_DEFAULT_FLASH);
            return false;
        }
        else
        {
            APP_LOGI(thisMOD,"RGB_NVID = 0x%X, state = %d, ret = %d", rgb_id->nvid, rgb_id->state, ret);
            nvkey_status_t result = nvkey_write_data(NVID_RGB_DEFAULT_FLASH, (uint8_t*)&saved_flash, sizeof(saved_flash));
            if(result){
                APP_LOGI(thisMOD,"nvkey_write_data NVID_RGB_DEFAULT_FLASH, err = %d", result);
                return false;
            }
            rgb_middle_status_t ret = rgb_middle_register_callback(rgb_id->num, app_rgb__flash_finish_handle, NULL);
            if(ret < RGB_MIDDLE_STATUS_OK){
               APP_LOGI(thisMOD,"rgb_middle_register_callback fail, ret = %d", ret);
               return false;
            }
            rgb_id->state = RGB_FLASH_START;
            flash_flag = true;
            return true;
        }
    }
    flash_flag = false;
    return false;
}

static bool app_rgb__check_and_play_flash()
{
    rgb_middle_running_status_t status;
    rgb_middle_get_running_status(rgb_id_0.num, &status);
    APP_LOGI(thisMOD,"check_and_play_flash, flag = %d, status = %d", flash_flag, status);

    if(flash_flag && !status) //flag true & rgb idle
    {
        rgb_id_0.nvid = saved_flash;
        rgb_id_0.repeat = 255;
        bool ret = app_rgb__enable_flash_rgb(&rgb_id_0);
        if(ret){
            return true;
        }
    }
    return false;
}

#if defined (AIR_BATTERY_MANAGEMENT_ENABLE)
static bool app_rgb__check_and_play_charging_rgb()
{
    APP_LOGI(thisMOD,"app_rgb__check_and_play_charging_rgb, charging_flag = %d", charging_flag);
    if(!app_battery__get_bat_charge_en_sta() || !led_flag){
        return false;
    }
    uint8_t battery_level = app_battery__get_battery_level();
    if(battery_level < 0 && battery_level > 100){
        APP_LOGI(thisMOD,"error with battery_level");
        return false;
    }
    else if(battery_level == 100){
        return false;
    }

    rgb_id_0.style = STYLE_CHARGING;
    rgb_default_pattern_setting[rgb_id_0.style].rgb_r.onoff = RGB_OFF;
    rgb_default_pattern_setting[rgb_id_0.style].rgb_g.onoff = RGB_OFF;
    rgb_default_pattern_setting[rgb_id_0.style].rgb_b.onoff = RGB_ON;

    if(led_flag){
        rgb_id_0.pattern = RGB_PATTERN_FG;
        bool ret = app_rgb__enable_normal_rgb(&rgb_id_0);
        if(ret)
        {
            charging_flag = true;
            return true;
        }
    }
    return false;
}
#endif
#endif /* _!DEF_CONFIG_AIR_HID_DEBUG_PIN_ */

static void app_rgb_var_init()
{
    rgb_id_0.num = 0;
    rgb_id_0.nvid = 0x00;
    rgb_id_0.repeat = 255;
    rgb_id_0.state = RGB_STATUS_NONE;
    rgb_id_0.style = STYLE_NONE_500MS;
    rgb_id_0.pattern = RGB_PATTERN_NONE;
}
#endif /*END _CONFIG_AIR_MIDDLE_RGB_*/

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
void app_rgb_init()
{
    #if defined (CONFIG_AIR_MIDDLE_RGB)
    APP_LOGI(thisMOD, "app_rgb_init start");
    app_rgb_var_init();

    if(app_nvkey_read_data(NVID_RGB_DEFAULT_FLASH, (uint8_t*)&saved_flash, sizeof(saved_flash))){
        flash_flag = true;
    }
    APP_LOGI(thisMOD, "flash_flag = %d", flash_flag);

    #if defined (CONFIG_AIR_MIDDLE_LED)
    led_flag = false;
    #endif
    #endif /*END _CONFIG_AIR_MIDDLE_RGB_*/
    return;
}

/*============================Application Framework============================*/
#if defined (CONFIG_AIR_MIDDLE_RGB)
#if !defined (CONFIG_AIR_HID_DEBUG_PIN)
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_race_cmd_req, app_rgb__evt_race_cmd_req);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_race_cmd_rsp_for_rgb, app_rgb__evt_race_cmd_rsp_for_rgb);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_rr_change_req, app_rgb_evt_rr_change_req);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_app_rgb_test, app_rgb__evt_app_rgb_test);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_app_state, app_rgb__evt_app_state);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_app_battery, app_rgb__evt_app_battery);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_dpi_status, app_rgb_evt_dpi_status);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_enter_test, app_rgb__evt_enter_test);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_link_change, app_rgb__evt_link_change);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_rr_status, app_rgb__evt_rr_status);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_slide_switch_status, app_rgb__evt_slide_switch_status);
#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_usb_status, app_rgb__evt_usb_status);
#endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/
#endif /* _!DEF_CONFIG_AIR_HID_DEBUG_PIN_ */
#endif /*END _CONFIG_AIR_MIDDLE_RGB_*/

/*=============================================================================*/