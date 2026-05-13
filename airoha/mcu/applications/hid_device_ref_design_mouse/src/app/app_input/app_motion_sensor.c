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

#include "app_motion_sensor.h"
#include "af_events_declaration.h"
#include "motion_sensor_mgr.h"
#include "app_state.h"
#include "app_scenario.h"
#include "app_battery.h"
#include "app_button.h"
#include <stdint.h>

#define thisMOD    "aMSEN"  // application motion sensor
#define thisMODULE aMSEN  // app motion sensor
LOG_MODULE_REGISTER(thisMODULE);
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
static void app_msen_return_acitve(uint32_t idle1_timeout, uint32_t idle2_timeout);
static void app_msen_BT_enter_idle1(uint32_t idle1_timeout, uint32_t idle2_timeout);
static void app_msen_2_4G_enter_idle1(uint32_t idle1_timeout, uint32_t idle2_timeout);
static void app_msen_enter_idle2(uint32_t idle2_timeout);
static void app_msen_enter_standby();
static void app_msen_race_cmd_rsp_announcement(T_RACE_CMD_E cmd, uint8_t value);
static void app_msen_send_dpi_status_event();
static void app_msen_race_cmd_req_for_set_dpi();
static void app_msen_enter_low_power();

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
const static T_DPI_CONFIG_S app_dpi_cfg = {
    .dpi_loop_stage_range = MAX_DPI_COUNT,     /* 1~5 */
    .dpi_curr_idx = 2,       /* 0, 1, 2, 3, 4 */
    #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
    .x_dpi_settings = {
        400, 800, 1600, 3200, 6400
    },
    .y_dpi_settings = {
        400, 800, 1600, 3200, 6400
    }
    #else
    .dpi_settings = {
        400, 800, 1600, 3200, 6400
    }
    #endif
};

bool app_msen_low_battery_check = false;

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/
void app_motion_sensor_pin_eint_callback(const struct device *dev, struct gpio_callback *cb, gpio_port_pins_t pins)
{
    #if defined (AIR_SWLA_ENABLE)
    HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_app_sensor_wakeup, SWLA_DIRECTION_START);
    #endif

    // APP_LOGI(thisMOD,"app_motion_sensor_pin_eint_callback");
    #if defined (CONFIG_AIR_APP_USB_DISABLE_IN_WIRELESS)
    uint8_t ss_type = SS_MODE_NONE;
    GET_SLIDE_SWITCH_MODE(&ss_type);
    if(ss_type == SS_MODE_OFF && app_usb_port__get_usb_plug_status() == APP_USB_PLUG_IN)
    {
        msmgr_motion_isr_disable();
        return;
    }
    #endif /* CONFIG_AIR_APP_USB_DISABLE_IN_WIRELESS */
    assert(!msmgr_motion_pin_mask());

    struct evt_active_status* event = create_evt_active_status();
    if (event){
        event->active = true;
        event->type = MOTION_SENSOR_WAKEUP;
        AF_EVT_SUBMIT(event);
        msmgr_motion_isr_disable();
    }

    #if defined (AIR_SWLA_ENABLE)
    HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_app_sensor_wakeup, SWLA_DIRECTION_STOP);
    #endif
}

/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
static bool app_motion_sensor_evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state* event = (struct evt_app_state*)evt_header;
    
    uint8_t scenario_type = app_scenario_get_scenario_type();
    uint16_t report_rate = app_scenario_get_report_rate();
    uint32_t idle1_timeout, idle2_timeout;

    APP_LOGI(thisMOD,"app_motion_sensor_evt_app_state , event->app_state = 0x%02X, scenario_type = %d, report_rate = %d \n ", event->app_state, scenario_type, report_rate );

    app_state_get_power_saving_timeout(&idle1_timeout, &idle2_timeout);

    switch (event->app_state)
    {
        case APP_STATE_CONNECT_PREPARING:
        {
            #if defined (STANDBY_SENSOR_OFF)
            msmgr_parking_mode(app_motion_sensor_pin_eint_callback);
            #endif
            msmgr_downshift_time_config(idle1_timeout, idle2_timeout);
            msmgr_driving_mode(scenario_type, report_rate);
            #if !defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
            msmgr_bt_trigger_enable();
            #endif

            msmgr_motion_sync_config(scenario_type, report_rate);
            hid_common_set_hid_exp_flag(FLAG_BIT_SENSOR_READY);            
        }
        break;

        case APP_STATE_BT_PAIRING:
        case APP_STATE_2_4G_PAIRING:
        case APP_STATE_BT_RECONNECT:
        case APP_STATE_2_4G_RECONNECT:
        case APP_STATE_2_4G_QUICK_CONNECT:
        case APP_STATE_USB_CONNECTED:
        {
            // #if defined (STANDBY_SENSOR_OFF)
            // msmgr_parking_mode(app_motion_sensor_pin_eint_callback);
            // #endif
            // msmgr_downshift_time_config(idle1_timeout, idle2_timeout);
            // msmgr_driving_mode(device_type, report_rate);
            // #if !defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
            // msmgr_bt_trigger_enable();
            // #endif
        }
        break;

        case APP_STATE_2_4G_CONNECTED_ACTIVE:
        {
            app_msen_race_cmd_req_for_set_dpi();
        }  //dont break
        case APP_STATE_USB_ACTIVE:
        case APP_STATE_BT_CONNECTED_ACTIVE:
        {
            // msmgr_motion_sync_config(device_type, report_rate);
            // hid_common_set_hid_exp_flag(FLAG_BIT_SENSOR_READY);
        }
        break;

        case APP_STATE_BT_CONNECTED_IDLE_1:
        {
            app_msen_BT_enter_idle1(idle1_timeout, idle2_timeout);
        }
        break;

        case APP_STATE_2_4G_CONNECTED_IDLE_1:
        {
            app_msen_2_4G_enter_idle1(idle1_timeout, idle2_timeout);
        }
        break;

        case APP_STATE_USB_SUSPEND:
        {
            app_msen_enter_standby();
        }
        break;

        case APP_STATE_STANDBY:
        {
            bool power_ok = app_battery__get_battery_power();
            app_msen_enter_standby();
            msmgr_enter_low_power_set_wakeup();
            if(!power_ok){  //action after set wakeup
                app_msen_enter_low_power();
            }
        }
        break;

        default:
        break;
    }
    return AF_TRAVERSE_NEXT;
}

static bool app_motion_sensor_evt_conn_req(const struct af_evt_header *evt_header)
{
    struct evt_conn_req* event = (struct evt_conn_req*)evt_header;
    APP_LOGI(thisMOD,"app_motion_sensor_evt_conn_req , cmd = %d", event->cmd);
    uint32_t idle1_timeout, idle2_timeout;
    app_state_get_power_saving_timeout(&idle1_timeout, &idle2_timeout);

    switch(event->cmd)
    {
        case CONN_REQ_ACTIVE:
        case CONN_REQ_ACTIVE_USB:
        {
            app_msen_return_acitve(idle1_timeout, idle2_timeout);
        }
        break;

        case CONN_REQ_IDLE_2:
        {
            app_msen_enter_idle2(idle2_timeout);
        }
        break;

        default:
        break;
    }
    return AF_TRAVERSE_NEXT;
}

static bool app_motion_sensor_evt_rr_status(const struct af_evt_header *evt_header)
{
    struct evt_rr_status* event = (struct evt_rr_status*)evt_header;
    APP_LOGI(thisMOD,"app_motion_sensor_evt_rr_status, category = %d,  RR = %d, RR_CHANGE_NEXT = %d", event->category, event->RR, RR_CHANGE_NEXT);

    if((app_state_check(TYPE_IN_USB_STATES) && event->category == 0) ||
        (app_state_check(TYPE_IN_GAMING_CONNECTED_STABLE) && event->category == 1))
    {
        uint8_t device_type = app_scenario_get_current_device_type();
        msmgr_mode_setting(device_type, event->RR);
        msmgr_motion_sync_config(device_type, event->RR);
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_motion_sensor_evt_dpi_change_req(const struct af_evt_header *evt_header)
{
    struct evt_dpi_change_req* event = (struct evt_dpi_change_req*)evt_header;
    APP_LOGI(thisMOD,"app_motion_sensor_evt_dpi_change_req , change_type = %d", event->change_type);

    #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
    msmgr_dpi_change(event->change_type, event->X_DPI, event->Y_DPI);
    #else
    msmgr_dpi_change(event->change_type, event->DPI);
    #endif

    app_msen_send_dpi_status_event();

    return AF_TRAVERSE_NEXT;
}

static bool app_motion_sensor_evt_race_cmd_req(const struct af_evt_header *evt_header)
{
    struct evt_race_cmd_req* event = (struct evt_race_cmd_req*)evt_header;
    APP_LOGI(thisMOD,"evt_race_cmd_req , cmd = %x", event->cmd);

    uint8_t result;
    uint8_t link_mode = app_scenario_get_current_device_type();
    uint16_t report_rate = app_scenario_get_report_rate();

    switch(event->cmd)
    {
        case RACE_CMD_SET_SENSOR_LOD:
        {
            result = msmgr_set_attr_config(SENSOR_LOD, event->SENSOR.value, link_mode, report_rate);
            app_msen_race_cmd_rsp_announcement(RACE_CMD_SET_SENSOR_LOD, result);
        }
        break;

        case RACE_CMD_GET_SENSOR_LOD:
        {
            result = msmgr_get_attr_config(SENSOR_LOD);
            app_msen_race_cmd_rsp_announcement(RACE_CMD_GET_SENSOR_LOD, result);
        }
        break;

        case RACE_CMD_SET_SENSOR_MOTION_SYNC:
        {
            result = msmgr_set_attr_config(SENSOR_MOTION_SYNC, event->SENSOR.value, link_mode, report_rate);
            app_msen_race_cmd_rsp_announcement(RACE_CMD_SET_SENSOR_MOTION_SYNC, result);
        }
        break;

        case RACE_CMD_GET_SENSOR_MOTION_SYNC:
        {
            result = msmgr_get_attr_config(SENSOR_MOTION_SYNC);
            app_msen_race_cmd_rsp_announcement(RACE_CMD_GET_SENSOR_MOTION_SYNC, result);
        }
        break;

        case RACE_CMD_SET_SENSOR_ANGLE_SNAP:
        {
            result = msmgr_set_attr_config(SENSOR_ANGLE_SNAP, event->SENSOR.value, link_mode, report_rate);
            app_msen_race_cmd_rsp_announcement(RACE_CMD_SET_SENSOR_ANGLE_SNAP, result);
        }
        break;

        case RACE_CMD_GET_SENSOR_ANGLE_SNAP:
        {
            result = msmgr_get_attr_config(SENSOR_ANGLE_SNAP);
            app_msen_race_cmd_rsp_announcement(RACE_CMD_GET_SENSOR_ANGLE_SNAP, result);
        }
        break;

        case RACE_CMD_SET_SENSOR_RIPPLE_CTRL:
        {
            result = msmgr_set_attr_config(SENSOR_RIPPLE_CONTROL, event->SENSOR.value, link_mode, report_rate);
            app_msen_race_cmd_rsp_announcement(RACE_CMD_SET_SENSOR_RIPPLE_CTRL, result);
        }
        break;

        case RACE_CMD_GET_SENSOR_RIPPLE_CTRL:
        {
            result = msmgr_get_attr_config(SENSOR_RIPPLE_CONTROL);
            app_msen_race_cmd_rsp_announcement(RACE_CMD_GET_SENSOR_RIPPLE_CTRL, result);
        }
        break;

        case RACE_CMD_SET_DPI:
        {
            T_DPI_STATUS_S dpi_cfg;
            bool set_dpi_req = false;
            msmgr_get_current_dpi_status(&dpi_cfg);
            APP_LOGI(thisMOD,"RACE_CMD_SET_DPI, curr idx = %d, set idx = %d", dpi_cfg.dpi_idx, event->DPI.dpi_idx);
            if(dpi_cfg.dpi_idx == event->DPI.dpi_idx)
            {
                #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
                APP_LOGI(thisMOD,"x dpi = %d-> %d, y dpi = %d-> %d", dpi_cfg.x_dpi_value, event->DPI.x_dpi_value, dpi_cfg.y_dpi_value, event->DPI.y_dpi_value);
                if(dpi_cfg.x_dpi_value != event->DPI.x_dpi_value || dpi_cfg.y_dpi_value != event->DPI.y_dpi_value)
                #else
                APP_LOGI(thisMOD,"dpi = %d-> %d", dpi_cfg.dpi_value, event->DPI.dpi_value);
                if(dpi_cfg.dpi_value != event->DPI.dpi_value)
                #endif
                {
                    set_dpi_req = true;
                }
            }
            #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
            result = msmgr_set_dpi_value(event->DPI.dpi_idx, event->DPI.x_dpi_value, event->DPI.y_dpi_value);
            #else
            result = msmgr_set_dpi_value(event->DPI.dpi_idx, event->DPI.dpi_value);
            #endif
            app_msen_race_cmd_rsp_announcement(RACE_CMD_SET_DPI, result);
            if(set_dpi_req){
                app_msen_race_cmd_req_for_set_dpi();
            }
        }
        break;

        case RACE_CMD_GET_DPI:
        {
            T_DPI_CONFIG_S dpi_cfg;
            #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
            msmgr_get_dpi_value(&dpi_cfg.dpi_loop_stage_range,
                                       &dpi_cfg.dpi_curr_idx,
                                       dpi_cfg.x_dpi_settings,
                                       dpi_cfg.y_dpi_settings);

            struct evt_race_cmd_rsp* event = create_evt_race_cmd_rsp();
            if (event){
                event->cmd = RACE_CMD_GET_DPI;
                event->DPI.dpi_loop_stage_range = dpi_cfg.dpi_loop_stage_range;
                event->DPI.dpi_curr_idx = dpi_cfg.dpi_curr_idx;
                memcpy(event->DPI.x_dpi_settings, &dpi_cfg.x_dpi_settings, sizeof(dpi_cfg.x_dpi_settings));
                memcpy(event->DPI.y_dpi_settings, &dpi_cfg.y_dpi_settings, sizeof(dpi_cfg.y_dpi_settings));
                AF_EVT_SUBMIT(event);
            }
            #else
            msmgr_get_dpi_value(&dpi_cfg.dpi_loop_stage_range,
                                        &dpi_cfg.dpi_curr_idx,
                                       dpi_cfg.dpi_settings);

            struct evt_race_cmd_rsp* event = create_evt_race_cmd_rsp();
            if (event){
                event->cmd = RACE_CMD_GET_DPI;
                event->DPI.dpi_loop_stage_range = dpi_cfg.dpi_loop_stage_range;
                event->DPI.dpi_curr_idx = dpi_cfg.dpi_curr_idx;
                memcpy(event->DPI.dpi_settings, &dpi_cfg.dpi_settings, sizeof(dpi_cfg.dpi_settings));
                AF_EVT_SUBMIT(event);
            }
            #endif
        }
        break;

        case RACE_CMD_SET_DPI_LOOP_RANGE:
        {
            result = msmgr_set_dpi_stage_range(event->SENSOR.value);
            app_msen_race_cmd_rsp_announcement(RACE_CMD_SET_DPI_LOOP_RANGE, result);
        }
        break;

        case RACE_CMD_SET_DPI_CURRENT:
        {
            result = msmgr_set_current_dpi(event->SENSOR.value);
            app_msen_race_cmd_rsp_announcement(RACE_CMD_SET_DPI_CURRENT, result);
            app_msen_send_dpi_status_event();
        }
        break;

        case RACE_CMD_SET_PROFILE:
        {
            result = msmgr_reload_sensor_attr(event->PROFILE.id, false, report_rate, link_mode);
            app_msen_race_cmd_rsp_announcement(RACE_CMD_SET_PROFILE, result);
        }
        break;

        case RACE_CMD_SET_RESTORE:
        {
            result = msmgr_reload_sensor_attr(0, true, report_rate, link_mode);
            app_msen_race_cmd_rsp_announcement(RACE_CMD_SET_RESTORE, result);
        }
        break;

        default:
        break;
    }
    return AF_TRAVERSE_NEXT;
}

static bool app_motion_sensor_evt_active_status(const struct af_evt_header *evt_header)
{
    struct evt_active_status* event = (struct evt_active_status*)evt_header;
    APP_LOGI(thisMOD,"app_motion_sensor_evt_active_status, active = %d, type = %d", event->active, event->type);

    if(event->active)
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
            {
                msmgr_exit_low_power();
                if(app_msen_low_battery_check){
                    app_msen_low_battery_check = false;
                    msmgr_parking_mode(app_motion_sensor_pin_eint_callback);
                }
                break;
            }
            #endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/
            default:{
                break;
            }
        }
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_motion_sensor_evt_workround(const struct af_evt_header *evt_header)
{
    msmgr_reinit();
    return AF_TRAVERSE_NEXT;
}
/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static void app_msen_return_acitve(uint32_t idle1_timeout, uint32_t idle2_timeout)
{
    /* Exit rest mode */
    uint16_t report_rate = app_scenario_get_report_rate();
    uint8_t device_type = app_scenario_get_current_device_type();
    msmgr_downshift_time_config(idle1_timeout, idle2_timeout);
    msmgr_driving_mode(device_type, report_rate);
    msmgr_motion_sync_config(device_type, report_rate);
}

static void app_msen_BT_enter_idle1(uint32_t idle1_timeout, uint32_t idle2_timeout)
{
    /* Enter rest1 mode*/
    msmgr_downshift_time_config(idle1_timeout, idle2_timeout);
    msmgr_rest_mode();
    msmgr_print_sensor_ram_attr();
    APP_LOGI(thisMOD,"BT sensor enter rest1 mode");
}

static void app_msen_2_4G_enter_idle1(uint32_t idle1_timeout, uint32_t idle2_timeout)
{
    /* Enter rest1 mode*/
    msmgr_downshift_time_config(idle1_timeout, idle2_timeout);
    msmgr_rest_mode();
    #if !defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_bt_trigger_enable();
    #endif
    msmgr_print_sensor_ram_attr();
    APP_LOGI(thisMOD,"2.4G sensor enter rest1 mode");
}

static void app_msen_enter_idle2(uint32_t idle2_timeout)
{
    /* Enter rest2 mode*/
    msmgr_downshift_time_config(2, idle2_timeout);
    msmgr_print_sensor_ram_attr();
    #if !defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_bt_trigger_enable();
    #endif
    APP_LOGI(thisMOD,"Sensor enter rest2 mode");
}

static void app_msen_enter_standby()
{
    #if defined (STANDBY_SENSOR_OFF)
    msmgr_off_mode();
    #else
    /* Enter rest3 mode*/
    msmgr_downshift_time_config(2, 40);
    APP_LOGI(thisMOD,"Sensor enter rest3 mode");
    msmgr_parking_mode(app_motion_sensor_pin_eint_callback);
    #endif
}

static void app_msen_race_cmd_rsp_announcement(T_RACE_CMD_E cmd, uint8_t result)
{
    APP_LOGI(thisMOD,"app_msen_race_cmd_rsp_announcement");
    struct evt_race_cmd_rsp* event = create_evt_race_cmd_rsp();
    if (event){
        event->cmd = cmd;
        event->SENSOR.result = result;
        event->OTHERS.status = result;
        AF_EVT_SUBMIT(event);
    }
}

static void app_msen_race_cmd_req_for_set_dpi()
{
    T_DPI_STATUS_S dpi_cfg;
    msmgr_get_current_dpi_status(&dpi_cfg);
    struct evt_race_cmd_rsp* event = create_evt_race_cmd_rsp();
    if (event){
        event->cmd = RACE_CMD_SET_DPI_VALUE;

        #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
        event->DPI.x_dpi_value = dpi_cfg.x_dpi_value;
        event->DPI.y_dpi_value = dpi_cfg.y_dpi_value;
        #else
        event->DPI.x_dpi_value = dpi_cfg.dpi_value;
        event->DPI.y_dpi_value = dpi_cfg.dpi_value;
        #endif
        AF_EVT_SUBMIT(event);
    }
}

static void app_msen_send_dpi_status_event()
{
    T_DPI_STATUS_S dpi_cfg;
    msmgr_get_current_dpi_status(&dpi_cfg);

    struct evt_dpi_status* evt = create_evt_dpi_status();
    if (evt) {
        evt->dpi_idx = dpi_cfg.dpi_idx;
        #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
        evt->x_dpi_value = dpi_cfg.x_dpi_value;
        evt->y_dpi_value = dpi_cfg.y_dpi_value;
        #else
        evt->dpi_value = dpi_cfg.dpi_value;
        #endif
        AF_EVT_SUBMIT(evt);
    }
    app_msen_race_cmd_req_for_set_dpi();
}

static void app_msen_enter_low_power()
{
    app_msen_low_battery_check = true;
    msmgr_off_mode();
    return;
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
void app_motion_sensor_init(uint8_t profile_idx)
{
    APP_LOGI(thisMOD,"app_motion_sensor_init");

    msmgr_init(app_motion_sensor_pin_eint_callback);
    msmgr_dpi_config_init(&app_dpi_cfg, profile_idx, app_scenario_get_report_rate(), app_scenario_get_current_device_type());
}

bool app_motion_sensor_is_motion_pin_active()
{
    hal_gpio_data_t gpio_data;
    hal_gpio_get_input(MOUSE_MOTION_INT, &gpio_data);

    return !gpio_data;
}

/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_dpi_change_req, app_motion_sensor_evt_dpi_change_req);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_active_status, app_motion_sensor_evt_active_status);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_app_state, app_motion_sensor_evt_app_state);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_conn_req, app_motion_sensor_evt_conn_req);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_race_cmd_req, app_motion_sensor_evt_race_cmd_req);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_rr_status, app_motion_sensor_evt_rr_status);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_mouse_sensor, app_motion_sensor_evt_workround);
/*=============================================================================*/
