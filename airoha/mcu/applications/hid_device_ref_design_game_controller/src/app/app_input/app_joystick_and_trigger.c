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

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)

/* Includes ------------------------------------------------------------------*/
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include "hal_platform.h"
#include "hal_saradc_internal.h"
#include "hal_eint.h"
#include "hal_eint_internal.h"
#include "hal_gpt.h"
#include "hal_gpio.h"
#include "hal_gpio_internal.h"
#include "hid_common.h"
#include "hid_common_button.h"
#include "app_debug.h"
#include "hid_game_controller.h"
#include "nvkey.h"
#include "app_joystick_and_trigger.h"
#include "af_events_declaration.h"
#include "hid_race_cmd_game_controller.h"
#include "app_state.h"
#include "app_button.h"
#include "app_slide_switch.h"

#if defined(CONFIG_IO_EXPANDER_AW95124)
#include "io_expander_sensor_mgr.h"
#endif /* CONFIG_IO_EXPANDER_AW95124 */

#if defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE)
#include "hal_rtc.h"
#endif /* CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE */

/* Private define ------------------------------------------------------------*/
#define thisMODULE joystick_and_trigger
#define thisMOD    "joystick_and_trigger"

/* Private typedef -----------------------------------------------------------*/
#define APP_JOYSTICK_AND_TRIGGER_RTC_TIMER_PERIOD_MS 100

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE)
uint32_t app_joystick_and_trigger_rtc_timer_handle;
bool app_joystick_and_trigger_wakeup_is_enable;
struct k_work joystick_and_trigger_rtc_timer_work;
#endif /* CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE */
static bool app_joystick_power_enable_flag = false;
static bool joystick_and_trigger_init_flag  = false;

/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void app_joystick_power_enable(bool power_enable)
{
    APP_LOGI(thisMOD,"app_joystick_power_enable tmr_en = %d ,app_joystick_power_enable_flag = %d", power_enable,app_joystick_power_enable_flag);
    #if defined(CONFIG_IO_EXPANDER_AW95124)
    if (power_enable) {
        if(!app_joystick_power_enable_flag)
        {
            io_expander_mgr_pin_value_set(20, 1);
            app_joystick_power_enable_flag = true;
        }
    }else
    {
        if(app_joystick_power_enable_flag)
        {
            io_expander_mgr_pin_value_set(20, 0);
            app_joystick_power_enable_flag = false;
        }
    }
    #endif/*CONFIG_IO_EXPANDER_AW95124*/
}

static bool app_joystick_and_trigger_evt_race_cmd_req(const struct af_evt_header *evt_header)
{
    struct evt_race_cmd_req* event = (struct evt_race_cmd_req*)evt_header;
    APP_LOGI(thisMOD,"evt_race_cmd_req , cmd = %x", event->cmd);

    switch(event->cmd)
    {
        case RACE_SET_JOYSTICK_PARAMETER:
        {
            app_joystick_save_paramter(event->JOYSTICK_PARAMETER.number, (joystick_nvkey_parameter_t *)&(event->JOYSTICK_PARAMETER.min_voltage));
            hid_race_cmd_set_joystick_parameter_rsp(0);
        }
        break;

        case RACE_SET_TRIGGER_PARAMETER:
        {
            app_trigger_save_paramter(event->TRIGGER_PARAMETER.number, (trigger_nvkey_parameter_t *)&(event->TRIGGER_PARAMETER.full_release_voltage));
            hid_race_cmd_set_trigger_parameter_rsp(0);
        }

        case RACE_GET_JOYSTICK_PARAMETER:
        {
            uint32_t x, y, z, rz;
            app_joystick_get_paramter(&x, &y, &z, &rz);
            hid_race_cmd_get_joystick_parameter_rsp(0, x, y, z, rz);
        }
        break;

        case RACE_GET_TRIGGER_PARAMETER:
        {
            uint32_t lt, rt;
            app_trigger_get_paramter(&lt, &rt);
            hid_race_cmd_get_trigger_parameter_rsp(0, lt, rt);
        }
        break;

        default:
        break;
    }

    return AF_TRAVERSE_NEXT;
}

#if defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE)
void app_joystick_and_trigger_rtc_timer_callback(void *user_data)
{
    APP_LOGI(thisMOD,"app_joystick_and_trigger_rtc_timer_callback ");
    /*dispatch to app task start*/
    k_work_submit(&joystick_and_trigger_rtc_timer_work);
}

void app_joystick_and_trigger_rtc_timer_dispatch_handler()
{
    uint32_t data;
    joystick_adc_parameter_t *joystick_adc_para;
    trigger_adc_parameter_t *trigger_adc_para;
    int need_wakeup = 0;
    uint8_t app_state = app_state_current_state();

    if((app_state == APP_STATE_STANDBY)
    #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
    || (app_state == APP_STATE_2_4G_RECONNECT_RESUME_WAIT)
    #endif
    || (app_state == APP_STATE_USB_SUSPEND)
    )
    {
        /* get joysitck and triggers' current data */
        app_joystick_power_enable(true);
        hid_common->hid.adc.saradc_data.channel_mask = 0x3f; //enable 6 channel
        hal_saradc_init(HAL_SARADC_DATA_RATE_HS_MODE,HAL_SARADC_MEASURE_DIV_MODE);
        hal_saradc_set_gpio_mode(hid_common->hid.adc.saradc_data.channel_mask, HAL_SARADC_GPIO_ANALOG_MODE);
        hal_saradc_get_data_immediately(&(hid_common->hid.adc.saradc_data));
        hal_saradc_deinit();
        app_joystick_power_enable(false);

        /* check Y axis value */
        data = hid_common->hid.adc.saradc_data.channel_data[0]<<4;
        joystick_adc_para = game_controller_joystick_get_calibration_value(GAME_CONTROLLER_JOYSTICK_Y);
        if ((data < joystick_adc_para->zero_deadzone_min_value) || (data > joystick_adc_para->zero_deadzone_max_value))
        {
            need_wakeup = 1;
            goto WAKE_UP_LABEL;
        }
        /* check X axis value */
        data = hid_common->hid.adc.saradc_data.channel_data[1]<<4;
        joystick_adc_para = game_controller_joystick_get_calibration_value(GAME_CONTROLLER_JOYSTICK_X);
        if ((data < joystick_adc_para->zero_deadzone_min_value) || (data > joystick_adc_para->zero_deadzone_max_value))
        {
            need_wakeup = 1;
            goto WAKE_UP_LABEL;
        }
        /* check RZ axis value */
        data = hid_common->hid.adc.saradc_data.channel_data[2]<<4;
        joystick_adc_para = game_controller_joystick_get_calibration_value(GAME_CONTROLLER_JOYSTICK_RZ);
        if ((data < joystick_adc_para->zero_deadzone_min_value) || (data > joystick_adc_para->zero_deadzone_max_value))
        {
            need_wakeup = 1;
            goto WAKE_UP_LABEL;
        }
        /* check Z axis value */
        data = hid_common->hid.adc.saradc_data.channel_data[3]<<4;
        joystick_adc_para = game_controller_joystick_get_calibration_value(GAME_CONTROLLER_JOYSTICK_Z);
        if ((data < joystick_adc_para->zero_deadzone_min_value) || (data > joystick_adc_para->zero_deadzone_max_value))
        {
            need_wakeup = 1;
            goto WAKE_UP_LABEL;
        }
        /* check LT value */
        if(!lt_is_digital())
        {
            data = hid_common->hid.adc.saradc_data.channel_data[4]<<4;
            trigger_adc_para = game_controller_trigger_get_calibration_value(GAME_CONTROLLER_TRIGGER_L);
            if (trigger_adc_para->direction == GAME_CONTROLLER_TRIGGER_DIRECTION_FORWARD)
            {
                if (data > trigger_adc_para->zero_deadzone_value)
                {
                    need_wakeup = 1;
                    goto WAKE_UP_LABEL;
                }
            }
            else
            {
                if (data < trigger_adc_para->zero_deadzone_value)
                {
                    need_wakeup = 1;
                    goto WAKE_UP_LABEL;
                }
            }
        }
        /* check RT value */
        if(!rt_is_digital())
        {
            data = hid_common->hid.adc.saradc_data.channel_data[5]<<4;
            trigger_adc_para = game_controller_trigger_get_calibration_value(GAME_CONTROLLER_TRIGGER_R);
            if (trigger_adc_para->direction == GAME_CONTROLLER_TRIGGER_DIRECTION_FORWARD)
            {
                if (data > trigger_adc_para->zero_deadzone_value)
                {
                    need_wakeup = 1;
                    goto WAKE_UP_LABEL;
                }
            }
            else
            {
                if (data < trigger_adc_para->zero_deadzone_value)
                {
                    need_wakeup = 1;
                    goto WAKE_UP_LABEL;
                }
            }
        }
    }
    else
    {
        need_wakeup = -1;
    }

WAKE_UP_LABEL:
    if (need_wakeup > 0)
    {
        /* found joystick or trigger wakeup event */
        app_joystick_and_trigger_wakeup_disable();
        APP_LOGI(thisMOD,"app_joystick_and_trigger_rtc_timer_callback wakeup, data = %u, adc data = %u, %u, %u, %u, %u, %u",
                data,
                hid_common->hid.adc.saradc_data.channel_data[0],
                hid_common->hid.adc.saradc_data.channel_data[1],
                hid_common->hid.adc.saradc_data.channel_data[2],
                hid_common->hid.adc.saradc_data.channel_data[3],
                hid_common->hid.adc.saradc_data.channel_data[4],
                hid_common->hid.adc.saradc_data.channel_data[5]);

        uint8_t ss_type = SS_MODE_NONE;
        GET_SLIDE_SWITCH_MODE(&ss_type);
        if((!app_button_get_power_off_status() && ss_type != SS_MODE_OFF)
        || (ss_type == SS_MODE_OFF && app_state == APP_STATE_USB_SUSPEND)
        )
        {
            struct evt_active_status* event = create_evt_active_status();
            if (event){
                event->active = true;
                event->type = MOTION_SENSOR_WAKEUP;
                AF_EVT_SUBMIT(event);
            }
        }
    }
    else if (need_wakeup < 0)
    {
        /* app state error */
        app_joystick_and_trigger_wakeup_disable();
        APP_LOGI(thisMOD,"app_joystick_and_trigger_rtc_timer_callback app state 0x%X error",
                app_state);
    }
    else
    {
        /* do check again */
        hal_rtc_status_t rtc_ret;
        hal_rtc_stop_alarm(app_joystick_and_trigger_rtc_timer_handle);
        rtc_ret = hal_rtc_set_alarm_ms(app_joystick_and_trigger_rtc_timer_handle, APP_JOYSTICK_AND_TRIGGER_RTC_TIMER_PERIOD_MS, app_joystick_and_trigger_rtc_timer_callback, NULL);
        assert(rtc_ret == HAL_RTC_STATUS_OK);
    }
    return;
}
#endif /* CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE */

static bool app_joystick_and_trigger_evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state* event = (struct evt_app_state*)evt_header;
    APP_LOGI(thisMOD,"app_joystick_and_trigger_evt_app_state event->app_state = 0x%x " , event->app_state);

    switch(event->app_state)
    {
        case APP_STATE_BT_CONNECTED_IDLE_1:
        case APP_STATE_2_4G_CONNECTED_IDLE_1:
        {
        }
        break;

        case APP_STATE_BT_CONNECTED_IDLE_2:
        case APP_STATE_2_4G_CONNECTED_IDLE_2:
        {
        }
        break;

        case APP_STATE_USB_ACTIVE:
        case APP_STATE_BT_CONNECTED_ACTIVE:
        case APP_STATE_2_4G_CONNECTED_ACTIVE:
        {
#if defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE)
            app_joystick_and_trigger_wakeup_disable();
#endif /* defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE) */
            app_joystick_and_trigger_init();
            app_joystick_power_enable(true);
        }
        break;

        case APP_STATE_USB_SUSPEND:
        case APP_STATE_2_4G_RECONNECT_RESUME_WAIT:
        case APP_STATE_STANDBY:
        {
            app_joystick_and_trigger_deinit();
#if defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE)
            app_joystick_and_trigger_wakeup_enable();
#endif /* defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE) */
            app_joystick_power_enable(false);
        }
        break;

        case APP_STATE_DISCONNECTED:
        {
        }
        break;

        case APP_STATE_TEST:
        {
        }
        break;

        case APP_STATE_CONNECT_PREPARING:
        {
        }
        break;

        default:
        break;
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_joystick_and_trigger_evt_active_status(const struct af_evt_header *evt_header)
{
    struct evt_active_status* event = (struct evt_active_status*)evt_header;
    APP_LOGI(thisMOD,"app_joystick_and_trigger_evt_active_status, active = %d, type = %d", event->active, event->type);
    uint32_t app_state = app_state_current_state();

    if(event->active && (app_state == APP_STATE_STANDBY || app_state == APP_STATE_2_4G_RECONNECT_RESUME_WAIT || app_state == APP_STATE_USB_SUSPEND))
    {
        switch(event->type)
        {
            case MOTION_SENSOR_WAKEUP:
            case WHEEL_WAKEUP:
            case KEY_WAKEUP:
            #if defined (CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH)
            case SLIDE_SWITCH_WAKEUP:
            #endif
            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
            case USB_PLUG_WAKEUP:
            #endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/
            {
#if defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE)
                app_joystick_and_trigger_wakeup_disable();
#endif /* defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE) */
                app_joystick_and_trigger_init();
                app_joystick_power_enable(true);
                break;
            }
            default:{
                break;
            }
        }
    }

    return AF_TRAVERSE_NEXT;
}

/* Public functions ----------------------------------------------------------*/
void app_joystick_and_trigger_init(void)
{
    if(joystick_and_trigger_init_flag)
    {
        APP_LOGI(thisMOD,"app_joystick_and_trigger_init already initialized");
        return;
    }
    joystick_and_trigger_init_flag = true;

    joystick_adc_parameter_t joystick_adc_para;
    joystick_nvkey_parameter_t joystick_nvkey_para;
    trigger_adc_parameter_t trigger_adc_para;
    trigger_nvkey_parameter_t trigger_nvkey_para;
    uint32_t nvkey_size;
    nvkey_status_t nvkey_ret;

    hid_common->hid.adc.saradc_data.channel_mask = 0x3f; //enable 6 channel
    hal_saradc_init(HAL_SARADC_DATA_RATE_HS_MODE,HAL_SARADC_MEASURE_DIV_MODE);
    hal_saradc_set_gpio_mode(hid_common->hid.adc.saradc_data.channel_mask, HAL_SARADC_GPIO_ANALOG_MODE);

    nvkey_size = sizeof(joystick_nvkey_parameter_t);
    nvkey_ret = nvkey_read_data(NVID_APP_GAME_CONTROLLER_JOYSTICK_X, (uint8_t *)&joystick_nvkey_para, &nvkey_size);
    assert(nvkey_size == sizeof(joystick_nvkey_parameter_t));
    APP_LOGI(thisMOD,"joystick x, min = %u, max = %u, zero = %u, zero_deadzone_min = %u, zero_deadzone_max = %u",
            joystick_nvkey_para.min_voltage,
            joystick_nvkey_para.max_voltage,
            joystick_nvkey_para.zero_voltage,
            joystick_nvkey_para.zero_deadzone_min_voltage,
            joystick_nvkey_para.zero_deadzone_max_voltage);
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, joystick_nvkey_para.min_voltage/1000, &joystick_adc_para.min);
    joystick_adc_para.min = (uint32_t)((double)joystick_adc_para.min/4096 * ADC_RANGE_VALUE_16BIT);
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, joystick_nvkey_para.max_voltage/1000, &joystick_adc_para.max);
    joystick_adc_para.max = (uint32_t)((double)joystick_adc_para.max/4096 * ADC_RANGE_VALUE_16BIT);
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, joystick_nvkey_para.zero_voltage/1000, &joystick_adc_para.zero_value);
    joystick_adc_para.zero_value = (uint32_t)((double)joystick_adc_para.zero_value/4096 * ADC_RANGE_VALUE_16BIT);
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, joystick_nvkey_para.zero_deadzone_min_voltage/1000, &joystick_adc_para.zero_deadzone_min_value);
    joystick_adc_para.zero_deadzone_min_value = (uint32_t)((double)joystick_adc_para.zero_deadzone_min_value/4096 * ADC_RANGE_VALUE_16BIT);
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, joystick_nvkey_para.zero_deadzone_max_voltage/1000, &joystick_adc_para.zero_deadzone_max_value);
    joystick_adc_para.zero_deadzone_max_value = (uint32_t)((double)joystick_adc_para.zero_deadzone_max_value/4096 * ADC_RANGE_VALUE_16BIT);
    game_controller_joystick_update_calibration_value(GAME_CONTROLLER_JOYSTICK_X, joystick_adc_para.min, joystick_adc_para.max, joystick_adc_para.zero_value,
                                                    joystick_adc_para.zero_deadzone_min_value, joystick_adc_para.zero_deadzone_max_value);

    nvkey_size = sizeof(joystick_nvkey_parameter_t);
    nvkey_ret = nvkey_read_data(NVID_APP_GAME_CONTROLLER_JOYSTICK_Y, (uint8_t *)&joystick_nvkey_para, &nvkey_size);
    assert(nvkey_size == sizeof(joystick_nvkey_parameter_t));
    APP_LOGI(thisMOD,"joystick y, min = %u, max = %u, zero = %u, zero_deadzone_min = %u, zero_deadzone_max = %u",
            joystick_nvkey_para.min_voltage,
            joystick_nvkey_para.max_voltage,
            joystick_nvkey_para.zero_voltage,
            joystick_nvkey_para.zero_deadzone_min_voltage,
            joystick_nvkey_para.zero_deadzone_max_voltage);
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, joystick_nvkey_para.min_voltage/1000, &joystick_adc_para.min);
    joystick_adc_para.min = (uint32_t)((double)joystick_adc_para.min/4096 * ADC_RANGE_VALUE_16BIT);
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, joystick_nvkey_para.max_voltage/1000, &joystick_adc_para.max);
    joystick_adc_para.max = (uint32_t)((double)joystick_adc_para.max/4096 * ADC_RANGE_VALUE_16BIT);
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, joystick_nvkey_para.zero_voltage/1000, &joystick_adc_para.zero_value);
    joystick_adc_para.zero_value = (uint32_t)((double)joystick_adc_para.zero_value/4096 * ADC_RANGE_VALUE_16BIT);
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, joystick_nvkey_para.zero_deadzone_min_voltage/1000, &joystick_adc_para.zero_deadzone_min_value);
    joystick_adc_para.zero_deadzone_min_value = (uint32_t)((double)joystick_adc_para.zero_deadzone_min_value/4096 * ADC_RANGE_VALUE_16BIT);
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, joystick_nvkey_para.zero_deadzone_max_voltage/1000, &joystick_adc_para.zero_deadzone_max_value);
    joystick_adc_para.zero_deadzone_max_value = (uint32_t)((double)joystick_adc_para.zero_deadzone_max_value/4096 * ADC_RANGE_VALUE_16BIT);
    game_controller_joystick_update_calibration_value(GAME_CONTROLLER_JOYSTICK_Y, joystick_adc_para.min, joystick_adc_para.max, joystick_adc_para.zero_value,
                                                    joystick_adc_para.zero_deadzone_min_value, joystick_adc_para.zero_deadzone_max_value);

    nvkey_size = sizeof(joystick_nvkey_parameter_t);
    nvkey_ret = nvkey_read_data(NVID_APP_GAME_CONTROLLER_JOYSTICK_Z, (uint8_t *)&joystick_nvkey_para, &nvkey_size);
    assert(nvkey_size == sizeof(joystick_nvkey_parameter_t));
    APP_LOGI(thisMOD,"joystick z, min = %u, max = %u, zero = %u, zero_deadzone_min = %u, zero_deadzone_max = %u",
            joystick_nvkey_para.min_voltage,
            joystick_nvkey_para.max_voltage,
            joystick_nvkey_para.zero_voltage,
            joystick_nvkey_para.zero_deadzone_min_voltage,
            joystick_nvkey_para.zero_deadzone_max_voltage);
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, joystick_nvkey_para.min_voltage/1000, &joystick_adc_para.min);
    joystick_adc_para.min = (uint32_t)((double)joystick_adc_para.min/4096 * ADC_RANGE_VALUE_16BIT);
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, joystick_nvkey_para.max_voltage/1000, &joystick_adc_para.max);
    joystick_adc_para.max = (uint32_t)((double)joystick_adc_para.max/4096 * ADC_RANGE_VALUE_16BIT);
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, joystick_nvkey_para.zero_voltage/1000, &joystick_adc_para.zero_value);
    joystick_adc_para.zero_value = (uint32_t)((double)joystick_adc_para.zero_value/4096 * ADC_RANGE_VALUE_16BIT);
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, joystick_nvkey_para.zero_deadzone_min_voltage/1000, &joystick_adc_para.zero_deadzone_min_value);
    joystick_adc_para.zero_deadzone_min_value = (uint32_t)((double)joystick_adc_para.zero_deadzone_min_value/4096 * ADC_RANGE_VALUE_16BIT);
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, joystick_nvkey_para.zero_deadzone_max_voltage/1000, &joystick_adc_para.zero_deadzone_max_value);
    joystick_adc_para.zero_deadzone_max_value = (uint32_t)((double)joystick_adc_para.zero_deadzone_max_value/4096 * ADC_RANGE_VALUE_16BIT);
    game_controller_joystick_update_calibration_value(GAME_CONTROLLER_JOYSTICK_Z, joystick_adc_para.min, joystick_adc_para.max, joystick_adc_para.zero_value,
                                                    joystick_adc_para.zero_deadzone_min_value, joystick_adc_para.zero_deadzone_max_value);

    nvkey_size = sizeof(joystick_nvkey_parameter_t);
    nvkey_ret = nvkey_read_data(NVID_APP_GAME_CONTROLLER_JOYSTICK_RZ, (uint8_t *)&joystick_nvkey_para, &nvkey_size);
    assert(nvkey_size == sizeof(joystick_nvkey_parameter_t));
    APP_LOGI(thisMOD,"joystick rz, min = %u, max = %u, zero = %u, zero_deadzone_min = %u, zero_deadzone_max = %u",
            joystick_nvkey_para.min_voltage,
            joystick_nvkey_para.max_voltage,
            joystick_nvkey_para.zero_voltage,
            joystick_nvkey_para.zero_deadzone_min_voltage,
            joystick_nvkey_para.zero_deadzone_max_voltage);
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, joystick_nvkey_para.min_voltage/1000, &joystick_adc_para.min);
    joystick_adc_para.min = (uint32_t)((double)joystick_adc_para.min/4096 * ADC_RANGE_VALUE_16BIT);
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, joystick_nvkey_para.max_voltage/1000, &joystick_adc_para.max);
    joystick_adc_para.max = (uint32_t)((double)joystick_adc_para.max/4096 * ADC_RANGE_VALUE_16BIT);
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, joystick_nvkey_para.zero_voltage/1000, &joystick_adc_para.zero_value);
    joystick_adc_para.zero_value = (uint32_t)((double)joystick_adc_para.zero_value/4096 * ADC_RANGE_VALUE_16BIT);
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, joystick_nvkey_para.zero_deadzone_min_voltage/1000, &joystick_adc_para.zero_deadzone_min_value);
    joystick_adc_para.zero_deadzone_min_value = (uint32_t)((double)joystick_adc_para.zero_deadzone_min_value/4096 * ADC_RANGE_VALUE_16BIT);
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, joystick_nvkey_para.zero_deadzone_max_voltage/1000, &joystick_adc_para.zero_deadzone_max_value);
    joystick_adc_para.zero_deadzone_max_value = (uint32_t)((double)joystick_adc_para.zero_deadzone_max_value/4096 * ADC_RANGE_VALUE_16BIT);
    game_controller_joystick_update_calibration_value(GAME_CONTROLLER_JOYSTICK_RZ, joystick_adc_para.min, joystick_adc_para.max, joystick_adc_para.zero_value,
                                                    joystick_adc_para.zero_deadzone_min_value, joystick_adc_para.zero_deadzone_max_value);

    nvkey_size = sizeof(trigger_nvkey_parameter_t);
    nvkey_ret = nvkey_read_data(NVID_APP_GAME_CONTROLLER_TRIGGER_L, (uint8_t *)&trigger_nvkey_para, &nvkey_size);
    assert(nvkey_size == sizeof(trigger_nvkey_parameter_t));
    APP_LOGI(thisMOD,"trigger l, release = %u, press = %u, zero = %u",
            trigger_nvkey_para.full_release_voltage,
            trigger_nvkey_para.full_press_voltage,
            trigger_nvkey_para.zero_deadzone_voltage);
    if (trigger_nvkey_para.full_release_voltage <= trigger_nvkey_para.full_press_voltage)
    {
        trigger_adc_para.direction =  GAME_CONTROLLER_TRIGGER_DIRECTION_FORWARD;
        hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, trigger_nvkey_para.full_release_voltage/1000, &trigger_adc_para.min);
        trigger_adc_para.min = (uint32_t)((double)trigger_adc_para.min/4096 * ADC_RANGE_VALUE_16BIT);
        hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, trigger_nvkey_para.full_press_voltage/1000, &trigger_adc_para.max);
        trigger_adc_para.max = trigger_adc_para.min/4096 * ADC_RANGE_VALUE_16BIT;
    }
    else
    {
        trigger_adc_para.direction =  GAME_CONTROLLER_TRIGGER_DIRECTION_REVERSE;
        hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, trigger_nvkey_para.full_release_voltage/1000, &trigger_adc_para.max);
        trigger_adc_para.max = (uint32_t)((double)trigger_adc_para.max/4096 * ADC_RANGE_VALUE_16BIT);
        hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, trigger_nvkey_para.full_press_voltage/1000, &trigger_adc_para.min);
        trigger_adc_para.min = (uint32_t)((double)trigger_adc_para.min/4096 * ADC_RANGE_VALUE_16BIT);
    }
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, trigger_nvkey_para.zero_deadzone_voltage/1000, &trigger_adc_para.zero_deadzone_value);
    trigger_adc_para.zero_deadzone_value = (uint32_t)((double)trigger_adc_para.zero_deadzone_value/4096 * ADC_RANGE_VALUE_16BIT);
    game_controller_trigger_update_calibration_value(GAME_CONTROLLER_TRIGGER_L, trigger_adc_para.direction, trigger_adc_para.min, trigger_adc_para.max, trigger_adc_para.zero_deadzone_value);

    nvkey_size = sizeof(trigger_nvkey_parameter_t);
    nvkey_ret = nvkey_read_data(NVID_APP_GAME_CONTROLLER_TRIGGER_R, (uint8_t *)&trigger_nvkey_para, &nvkey_size);
    assert(nvkey_size == sizeof(trigger_nvkey_parameter_t));
    APP_LOGI(thisMOD,"trigger r, release = %u, press = %u, zero = %u",
            trigger_nvkey_para.full_release_voltage,
            trigger_nvkey_para.full_press_voltage,
            trigger_nvkey_para.zero_deadzone_voltage);
    if (trigger_nvkey_para.full_release_voltage <= trigger_nvkey_para.full_press_voltage)
    {
        trigger_adc_para.direction =  GAME_CONTROLLER_TRIGGER_DIRECTION_FORWARD;
        hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, trigger_nvkey_para.full_release_voltage/1000, &trigger_adc_para.min);
        trigger_adc_para.min = (uint32_t)((double)trigger_adc_para.min/4096 * ADC_RANGE_VALUE_16BIT);
        hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, trigger_nvkey_para.full_press_voltage/1000, &trigger_adc_para.max);
        trigger_adc_para.max = (uint32_t)((double)trigger_adc_para.max/4096 * ADC_RANGE_VALUE_16BIT);
    }
    else
    {
        trigger_adc_para.direction =  GAME_CONTROLLER_TRIGGER_DIRECTION_REVERSE;
        hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, trigger_nvkey_para.full_release_voltage/1000, &trigger_adc_para.max);
        trigger_adc_para.max = (uint32_t)((double)trigger_adc_para.max/4096 * ADC_RANGE_VALUE_16BIT);
        hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, trigger_nvkey_para.full_press_voltage/1000, &trigger_adc_para.min);
        trigger_adc_para.min = (uint32_t)((double)trigger_adc_para.min/4096 * ADC_RANGE_VALUE_16BIT);
    }
    hal_adc_get_raw_data_by_calibration_voltage(HAL_SARADC_MEASURE_DIV_MODE, trigger_nvkey_para.zero_deadzone_voltage/1000, &trigger_adc_para.zero_deadzone_value);
    trigger_adc_para.zero_deadzone_value = (uint32_t)((double)trigger_adc_para.zero_deadzone_value/4096 * ADC_RANGE_VALUE_16BIT);
    game_controller_trigger_update_calibration_value(GAME_CONTROLLER_TRIGGER_R, trigger_adc_para.direction, trigger_adc_para.min, trigger_adc_para.max, trigger_adc_para.zero_deadzone_value);

    hid_common_set_hid_exp_flag(FLAG_BIT_SENSOR_READY);
#if defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE)
    k_work_init(&joystick_and_trigger_rtc_timer_work, app_joystick_and_trigger_rtc_timer_dispatch_handler);
#endif /* CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE */
    APP_LOGI(thisMOD,"app_joystick_and_trigger_init, channel mask = 0x%x", hid_common->hid.adc.saradc_data.channel_mask);
}

void app_joystick_and_trigger_deinit(void)
{
    if(!joystick_and_trigger_init_flag)
    {
        APP_LOGI(thisMOD,"app_joystick_and_trigger_deinit ,not initialized");
        return;
    }
    joystick_and_trigger_init_flag = false;
    hal_saradc_deinit();

    hid_common_clear_hid_exp_flag(FLAG_BIT_SENSOR_READY);

    APP_LOGI(thisMOD,"app_joystick_and_trigger_deinit");
}

void app_joystick_save_paramter(uint8_t number, joystick_nvkey_parameter_t *param)
{
    nvkey_status_t nvkey_ret = NVKEY_STATUS_ERROR;

    if ((number > 0) && (number <= GAME_CONTROLLER_JOYSTICK_NUM_MAX))
    {
        nvkey_ret = nvkey_write_data(NVID_APP_GAME_CONTROLLER_JOYSTICK_X+number-1, (uint8_t *)param, sizeof(joystick_nvkey_parameter_t));
    }

    APP_LOGI(thisMOD,"joystick %u write setting %d, min = %u, max = %u, zero = %u, zero_deadzone_min = %u, zero_deadzone_max = %u",
            number,
            nvkey_ret,
            param->min_voltage,
            param->max_voltage,
            param->zero_voltage,
            param->zero_deadzone_min_voltage,
            param->zero_deadzone_max_voltage);
}

void app_trigger_save_paramter(uint8_t number, trigger_nvkey_parameter_t *param)
{
    nvkey_status_t nvkey_ret = NVKEY_STATUS_ERROR;

    if ((number > 0) && (number <= GAME_CONTROLLER_TRIGGER_NUM_MAX))
    {
        nvkey_ret = nvkey_write_data(NVID_APP_GAME_CONTROLLER_TRIGGER_L+number-1, (uint8_t *)param, sizeof(trigger_nvkey_parameter_t));
    }

    APP_LOGI(thisMOD,"trigger %u write setting %d, release = %u, press = %u, zero = %u",
            number,
            nvkey_ret,
            param->full_release_voltage,
            param->full_press_voltage,
            param->zero_deadzone_voltage);
}

void app_joystick_get_paramter(uint32_t *x, uint32_t *y, uint32_t *z, uint32_t *rz)
{
    uint32_t x_vol, y_vol, z_vol, rz_vol;
    *y  = hid_common->hid.adc.saradc_data.channel_data[0];
    *x  = hid_common->hid.adc.saradc_data.channel_data[1];
    *rz  = hid_common->hid.adc.saradc_data.channel_data[2];
    *z = hid_common->hid.adc.saradc_data.channel_data[3];
    hal_saradc_get_calibration_voltage_mV(HAL_SARADC_MEASURE_DIV_MODE, *x, &x_vol);
    hal_saradc_get_calibration_voltage_mV(HAL_SARADC_MEASURE_DIV_MODE, *y, &y_vol);
    hal_saradc_get_calibration_voltage_mV(HAL_SARADC_MEASURE_DIV_MODE, *z, &z_vol);
    hal_saradc_get_calibration_voltage_mV(HAL_SARADC_MEASURE_DIV_MODE, *rz, &rz_vol);
    *x = x_vol * 1000;
    *y = y_vol * 1000;
    *z = z_vol * 1000;
    *rz = rz_vol * 1000;
    APP_LOGI(thisMOD,"app_joystick_get_paramter,  x = %u, y = %u, z = %u, rz = %u", *x, *y, *z, *rz);
}

void app_trigger_get_paramter(uint32_t *lt, uint32_t *rt)
{
    /* read finial trigger value form share memory */
    uint32_t lt_vol, rt_vol;
    *lt = hid_common->hid.adc.saradc_data.channel_data[4];
    *rt = hid_common->hid.adc.saradc_data.channel_data[5];
    hal_saradc_get_calibration_voltage_mV(HAL_SARADC_MEASURE_DIV_MODE, *lt, &lt_vol);
    hal_saradc_get_calibration_voltage_mV(HAL_SARADC_MEASURE_DIV_MODE, *rt, &rt_vol);
    *lt = lt_vol * 1000;
    *rt = rt_vol * 1000;
    APP_LOGI(thisMOD,"app_trigger_get_paramter, lt:%u, rt:%u, lt_vol:%u, rt_vol:%u", *lt, *rt, lt_vol, rt_vol);
}

#if defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE)
void app_joystick_and_trigger_wakeup_enable(void)
{
    uint32_t mask;
    bool do_operation = false;
    hal_rtc_status_t rtc_ret;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    if (app_joystick_and_trigger_wakeup_is_enable)
    {
        hal_nvic_restore_interrupt_mask(mask);
        return;
    }
    app_joystick_and_trigger_wakeup_is_enable = true;
    do_operation = true;
    hal_nvic_restore_interrupt_mask(mask);

    if (do_operation)
    {
        rtc_ret = hal_rtc_enable_time();
        assert(rtc_ret == HAL_RTC_STATUS_OK);
        if (app_joystick_and_trigger_rtc_timer_handle == 0)
        {
            rtc_ret = hal_rtc_alarm_get_handle(&app_joystick_and_trigger_rtc_timer_handle);
            assert(rtc_ret == HAL_RTC_STATUS_OK);
        }
        hal_rtc_stop_alarm(app_joystick_and_trigger_rtc_timer_handle);
        rtc_ret = hal_rtc_set_alarm_ms(app_joystick_and_trigger_rtc_timer_handle, APP_JOYSTICK_AND_TRIGGER_RTC_TIMER_PERIOD_MS, app_joystick_and_trigger_rtc_timer_callback, NULL);
        assert(rtc_ret == HAL_RTC_STATUS_OK);
        APP_LOGI(thisMOD,"app_joystick_and_trigger_wakeup_enable, handle = 0x%x", app_joystick_and_trigger_rtc_timer_handle);
    }
}

void app_joystick_and_trigger_wakeup_disable(void)
{
    uint32_t mask;
    bool do_operation = false;
    hal_rtc_status_t rtc_ret;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    if (!app_joystick_and_trigger_wakeup_is_enable)
    {
        hal_nvic_restore_interrupt_mask(mask);
        return;
    }
    app_joystick_and_trigger_wakeup_is_enable = false;
    do_operation = true;
    hal_nvic_restore_interrupt_mask(mask);

    if (do_operation)
    {
        hal_rtc_stop_alarm(app_joystick_and_trigger_rtc_timer_handle);
        rtc_ret = hal_rtc_alarm_free_handle(app_joystick_and_trigger_rtc_timer_handle);
        assert(rtc_ret == HAL_RTC_STATUS_OK);
        // rtc_ret = hal_rtc_disable_time();
        // assert(rtc_ret == HAL_RTC_STATUS_OK);
        APP_LOGI(thisMOD,"app_joystick_and_trigger_wakeup_disable, handle = 0x%x", app_joystick_and_trigger_rtc_timer_handle);
        app_joystick_and_trigger_rtc_timer_handle = 0;
    }
}
#endif /* CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE */

/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_app_state, app_joystick_and_trigger_evt_app_state);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_active_status, app_joystick_and_trigger_evt_active_status);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_race_cmd_req, app_joystick_and_trigger_evt_race_cmd_req);

#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */
