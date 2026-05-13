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
#if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE)
#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>

#include <zephyr/drivers/flash.h>
#include <zephyr/drivers/gpio.h>


#include <zephyr/drivers/sensor.h>
#include "mouse_sensor.h"

#include "hid_scenario_service.h"
#include "hid_scenario_service_internal.h"
#include "motion_sensor_mgr.h"
#include "hal_eint.h"
#include "hid_common.h"
#include "hid_scenario_nvkey.h"
#include "hal_eint_internal.h"
#include "hid_scenario_gaming_mode.h"
#include "hid_power_mgr.h"
#include "air_daemon_work_q.h"
/******************************************************************************/
/*  macro                                                                     */
/******************************************************************************/
#define STATE_CHANGE(x)    sensor_state = x;
#define STATE_CHECK(x)  (sensor_state == x)

#define MOTION_ISR_ENABLE() \
hal_eint_enable(MOUSE_MOTION_INT);\

#define MOTION_ISR_DISABLE() \
hal_eint_disable(MOUSE_MOTION_INT);\

#define SENSOR_DPI_MIN_VALUE     50
#define SENSOR_DPI_STEP_VALUE    50
#define SENSOR_DPI_MAX_VALUE     26000
#define MOUSE_SENSOR_PIN         18

#define ACCORDING_TO_PROFILE     0
#define DPI_DEFAULT_STAGE_CHANGE 0
#define DPI_DEFAULT_STAGE        2

#if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
#define SENSOR_CFG_CHECK_TIMEOUT 1
#endif

#define thisMOD    "msmgr"
#define thisMODULE msmgr
LOG_MODULE_REGISTER(thisMODULE);

/******************************************************************************/
/*  typedef                                                                   */
/******************************************************************************/
typedef enum{
    lod_0_7mm = 0,
    lod_1mm = 1,
    lod_2mm = 2
}T_RACE_CMD_LOD_VALUE_E;

typedef enum{
    RACE_ERRCODE_SUCCESS,
    RACE_ERRCODE_FAIL,
    RACE_ERRCODE_NOT_SUPPORT,
    RACE_ERRCODE_PARAMETER_ERROR,
}T_RACE_ERRCODE_E;

typedef enum{
    SENSOR_STATE_OFF,
    SENSOR_STATE_INIT,
    SENSOR_STATE_PARKING,
    SENSOR_STATE_DRIVING,
    SENSOR_STATE_REST,
}T_MOTION_SENSOR_STATE_E;

typedef struct {
    uint8_t lod;
    uint8_t motion_sync;
    uint8_t angle_snap;
    uint8_t ripple_control;
}T_SENSOR_ATTR_CONFIG_S;

typedef struct {
    uint8_t profile_idx;
    uint8_t bt_trigger;
    uint8_t restore;
    #if defined(AIR_DPI_SWITCH_RFOM_DEFAULT)
    uint8_t dpi_default_stage;
    #endif
    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    uint8_t cfg_status;
    #endif
}T_SENSOR_CTRL_S;
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
#if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
static void msmgr_config_start();
static void msmgr_config_end();
static void msmgr_config_end_job(struct k_work *work);
static K_WORK_DEFINE(job_msmgr_config_end, msmgr_config_end_job);
#endif
/******************************************************************************/
/* callback function                                                        */
/******************************************************************************/
#if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
static void msmgr_config_end_confirm(struct k_timer *timer_id);
#endif
/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
T_MOTION_SENSOR_STATE_E sensor_state = SENSOR_STATE_OFF;
const struct device * dev_hdl_sensor;

const static T_DPI_CONFIG_S *dpi_cfg_default = NULL;
static T_DPI_CONFIG_S dpi_cfg_profile[MAX_PROFILE_COUNT];
static T_DPI_CONFIG_S *curr_dpi_cfg;

static const T_SENSOR_ATTR_CONFIG_S sensor_attr_cfg_default = {1, true, false, false};
static T_SENSOR_ATTR_CONFIG_S sensor_attr_cfg[MAX_PROFILE_COUNT];
static T_SENSOR_ATTR_CONFIG_S *curr_sensor_attr_cfg;

#if defined(AIR_DPI_SWITCH_RFOM_DEFAULT)
static T_SENSOR_CTRL_S sensor_ctrl = {0, false, 0, DPI_DEFAULT_STAGE};
#elif defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
static T_SENSOR_CTRL_S sensor_ctrl = {0, false, 0, false};
#else
static T_SENSOR_CTRL_S sensor_ctrl = {0, false, 0};
#endif

struct gpio_callback motion_eint_cb;
const static struct device *gpio_dev;
#if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
struct k_timer sensor_cfg_timer;
#endif
/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/

/******************************************************************************/
/* functions                                                                  */
/******************************************************************************/
static void msmgr_nvkey_load(uint16_t nvkey_id, const uint8_t* p_default, uint8_t* p_dest, uint32_t length)
{
    nvkey_status_t nvkey_ret;
    uint32_t nvkey_size = length;

    nvkey_ret = nvkey_read_data(nvkey_id, p_dest, &nvkey_size);
    if ((nvkey_ret != NVKEY_STATUS_OK) || (sensor_ctrl.restore == true)) 
    {
        memcpy(p_dest, p_default, length);
        nvkey_ret = nvkey_write_data(nvkey_id, p_default, length);
        DBG_LOGI(thisMOD, "Save default data to nvkey of %x and return %d", nvkey_id, nvkey_ret);
    }
    else
    {
        DBG_LOGI(thisMOD, "Load sensor attr record data from nvkey of %x ok ", nvkey_id);
    }
}

#if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
static void msmgr_dpi_setting(uint8_t type, uint16_t x_dpi_value, uint16_t y_dpi_value)
{
    struct sensor_value val_x = {1600, 0};
    struct sensor_value val_y = {1600, 0};
    int err = 0;

    if(type == DPI_STAGE_LOCK && (x_dpi_value || y_dpi_value))
    {
        val_x.val1 = x_dpi_value;
        val_y.val1 = y_dpi_value;
    }
    else
    {
        val_x.val1 = curr_dpi_cfg->x_dpi_settings[curr_dpi_cfg->dpi_curr_idx];
        val_y.val1 = curr_dpi_cfg->y_dpi_settings[curr_dpi_cfg->dpi_curr_idx];
    }

    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_start();
    #endif
    err = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_CPI_X, &val_x);
 
    if(err)
    {
        DBG_LOGI(thisMOD, "msmgr_dpi_setting x value err = %d", err);
    }
    else
    {
        DBG_LOGI(thisMOD, "msmgr_dpi_setting dpi_x = %d", val_x.val1);
    }

    err = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_CPI_Y, &val_y);
    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_end();
    #endif

    if(err)
    {
        DBG_LOGI(thisMOD, "msmgr_dpi_setting y value err = %d", err);
    }
    else
    {
        DBG_LOGI(thisMOD, "msmgr_dpi_setting dpi_y = %d", val_y.val1);
    }

    #if !defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    if(sensor_ctrl.bt_trigger)
    {
        msmgr_bt_trigger_enable();
    }
    #endif
}
#else
static void msmgr_dpi_setting(uint8_t type, uint16_t dpi_value)
{
    struct sensor_value val = {1600, 0};
    int err = 0;

    if(type == DPI_STAGE_LOCK && dpi_value)
    {
        val.val1 = dpi_value;
    }
    else
    {
        val.val1 = curr_dpi_cfg->dpi_settings[curr_dpi_cfg->dpi_curr_idx];
    }

    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_start();
    #endif
    err = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_CPI, &val);
    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_end();
    #endif

    if(err)
    {
        DBG_LOGI(thisMOD, "msmgr_dpi_setting err = %d", err);
    }
    else
    {
        DBG_LOGI(thisMOD, "msmgr_dpi_setting dpi = %d", val.val1);
    }

    #if !defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    if(sensor_ctrl.bt_trigger)
    {
        msmgr_bt_trigger_enable();
    }
    #endif
}
#endif

static void msmgr_profile_config_setting(uint16_t report_rate, uint8_t link_mode)
{
    #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
    msmgr_dpi_setting(DPI_STAGE_LOOP, ACCORDING_TO_PROFILE, ACCORDING_TO_PROFILE);
    #else
    msmgr_dpi_setting(DPI_STAGE_LOOP, ACCORDING_TO_PROFILE);
    #endif
    msmgr_set_attr_config(SENSOR_LOD, curr_sensor_attr_cfg->lod, link_mode, report_rate);
    msmgr_set_attr_config(SENSOR_MOTION_SYNC, curr_sensor_attr_cfg->motion_sync, link_mode, report_rate);
    msmgr_set_attr_config(SENSOR_ANGLE_SNAP, curr_sensor_attr_cfg->angle_snap, link_mode, report_rate);
    msmgr_set_attr_config(SENSOR_RIPPLE_CONTROL, curr_sensor_attr_cfg->ripple_control, link_mode, report_rate);
}

static void msmgr_configure_motion_pin(msmgr_motion_isr_callback motion_pin_isr_cb)
{
    gpio_dev = device_get_binding(DEVICE_DT_NAME(DT_NODELABEL(gpio0)));
    if (!device_is_ready(gpio_dev)) {
        DBG_LOGI(thisMOD,"GPIO device is not ready");
        return;
    }

    gpio_pin_interrupt_configure(gpio_dev, (MOUSE_MOTION_INT), GPIO_INT_EDGE_FALLING);
    hal_eint_ext_sleep_set_debounce_time(MOUSE_MOTION_INT, 0);

    gpio_init_callback(&motion_eint_cb, motion_pin_isr_cb, BIT(MOUSE_MOTION_INT));
    int ret = gpio_add_callback(gpio_dev, &motion_eint_cb);
    if(ret){
        DBG_LOGI(thisMOD, "app_msen_configure_motion_pin error, ret = %d", ret);
    }
    else{
        DBG_LOGI(thisMOD, "app_msen_configure_motion_pin, cb = 0x%x ok!!!", &motion_eint_cb);
    }
}

#if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
static void msmgr_bt_trigger(uint8_t bt_trig)
{
    #define TURN_ON 1
    #define TURN_OFF 0

    if(hid_scenario_get() != HID_SCENARIO_USB_MODE)
    {
        struct sensor_value val = {TURN_OFF, 0}; 
        int ret_attr_1 = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_SPI_NVIC_IRQ  , &val); 

        val.val1 = bt_trig; 
        int ret_attr_2 = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_BT_TRIGGER    , &val); 

        DBG_LOGI(thisMOD,"msmgr_bt_trigger = %d, MOUSE_SENSOR_ATTR_SPI_NVIC_IRQ = %d, MOUSE_SENSOR_ATTR_BT_TRIGGER = %d"
                    , bt_trig
                    , ret_attr_1
                    , ret_attr_2
        );
    }
}

static void msmgr_config_start()
{
    if(sensor_ctrl.cfg_status == false)
    {
        sensor_ctrl.cfg_status = true;
        hid_power_mgr__lock_LC_sleep_control(true);
        hid_scenario__bt_trigger_peripheral_hw(false);
        msmgr_bt_trigger(false);
    }
}

static void msmgr_config_end()
{
    k_timer_stop(&sensor_cfg_timer);
    k_timer_start(&sensor_cfg_timer, K_MSEC(SENSOR_CFG_CHECK_TIMEOUT), K_NO_WAIT);
}

static void msmgr_config_end_job(struct k_work *work)
{
    if(sensor_ctrl.cfg_status)
    {
        msmgr_bt_trigger(true);
        hid_scenario__bt_trigger_peripheral_hw(true);
        hid_power_mgr__lock_LC_sleep_control(false);
        sensor_ctrl.cfg_status = false;
        DBG_LOGI(thisMOD, "msmgr_config_end done");
    }
}

static void msmgr_config_end_confirm(struct k_timer *timer_id)
{
    air_daemon_wq_work_submit(&job_msmgr_config_end);
}
#endif
/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
uint8_t msmgr_reload_sensor_attr(uint8_t profile_idx, bool restore, uint16_t report_rate, uint8_t link_mode)
{
    uint16_t nvkey_id;
    DBG_LOGI(thisMOD, "msmgr_reload_sensor_attr profile_idx = %d", profile_idx);

    sensor_ctrl.restore = restore;
    /* Reload DPI setting list */
    for(nvkey_id = NVID_DPI_SETTING_LIST_1; nvkey_id <= NVID_DPI_SETTING_LIST_4; nvkey_id++)
    {
        msmgr_nvkey_load(
            nvkey_id,
            (const uint8_t*)dpi_cfg_default,
            (uint8_t*)&dpi_cfg_profile[nvkey_id-NVID_DPI_SETTING_LIST_1],
            sizeof(T_DPI_CONFIG_S)
        );
        uint8_t idx;
        for(idx = 0; idx < MAX_DPI_COUNT; idx++){
            #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
            DBG_LOGI(thisMOD, "dpi value idx = %d, x_value = %d, y_value = %d", idx
                    , dpi_cfg_profile[nvkey_id-NVID_DPI_SETTING_LIST_1].x_dpi_settings[idx], dpi_cfg_profile[nvkey_id-NVID_DPI_SETTING_LIST_1].y_dpi_settings[idx]);
            #else
            DBG_LOGI(thisMOD, "dpi value idx = %d, value = %d", idx, dpi_cfg_profile[nvkey_id-NVID_DPI_SETTING_LIST_1].dpi_settings[idx]);
            #endif
        }
    }

    /* Reload other attributes setting (lod, motion sync, angle snap, ripple control)*/
    for(nvkey_id = NVID_SENSOR_ATTR_SETTING_1; nvkey_id <= NVID_SENSOR_ATTR_SETTING_4; nvkey_id++)
    {
        uint8_t idx = nvkey_id-NVID_SENSOR_ATTR_SETTING_1;
        msmgr_nvkey_load(
            nvkey_id,
            (const uint8_t*)&sensor_attr_cfg_default,
            (uint8_t*)&sensor_attr_cfg[idx],
            sizeof(sensor_attr_cfg_default)
        );

        DBG_LOGI(thisMOD, "profile idx = %d, lod = %d, motion sync = %d, angle_snap = %d, ripple_control = %d", idx,
            sensor_attr_cfg[idx].lod,
            sensor_attr_cfg[idx].motion_sync,
            sensor_attr_cfg[idx].angle_snap,
            sensor_attr_cfg[idx].ripple_control);
    }

    curr_dpi_cfg = &dpi_cfg_profile[profile_idx];
    curr_sensor_attr_cfg = &sensor_attr_cfg[profile_idx];
    sensor_ctrl.profile_idx = profile_idx;
    msmgr_profile_config_setting(report_rate, link_mode);
    return 0;
}

#if !defined (CONFIG_AIR_RUNTIME_BT_TRIGGER)
void msmgr_bt_trigger_enable()
{
    #define TURN_ON 1
    #define TURN_OFF 0

    struct sensor_value val = {TURN_OFF, 0};
    int ret_attr_1 = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_SPI_NVIC_IRQ  , &val);

    val.val1 = TURN_ON;
    int ret_attr_2 = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_BT_TRIGGER    , &val);

    DBG_LOGI(thisMOD,"msmgr_bt_trigger_enable, MOUSE_SENSOR_ATTR_SPI_NVIC_IRQ = %d, MOUSE_SENSOR_ATTR_BT_TRIGGER = %d"
                , ret_attr_1
                , ret_attr_2
                );
}
#endif

#if defined(AIR_DPI_SWITCH_RFOM_DEFAULT)
uint8_t msmgr_set_shortcut_dpi_default_stage(uint8_t stage)
{
    uint8_t result = RACE_ERRCODE_SUCCESS;
    sensor_ctrl.dpi_default_stage = stage;

    result = HID_SCENARIO_NVKEY_SAVE(NVID_KEY_REMAP_FN_KEY_1 + sensor_ctrl.profile_idx, (const uint8_t*)&stage, sizeof(stage));
    if (result != RACE_ERRCODE_SUCCESS) {
        DBG_LOGI(thisMOD, "Set dpi_default_stage fail and return %d", result);
        return result;
    }

    return result;
}

uint8_t msmgr_get_shortcut_dpi_default_stage()
{
    return sensor_ctrl.dpi_default_stage;
}
#endif

uint8_t msmgr_set_current_dpi(uint8_t idx)
{
    if(idx >= MAX_DPI_COUNT)
    {
        return RACE_ERRCODE_FAIL;
    }

    curr_dpi_cfg->dpi_curr_idx = idx;
    #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
    msmgr_dpi_setting(DPI_STAGE_LOOP, ACCORDING_TO_PROFILE, ACCORDING_TO_PROFILE);
    #else
    msmgr_dpi_setting(DPI_STAGE_LOOP, ACCORDING_TO_PROFILE);
    #endif

    int8_t err = HID_SCENARIO_NVKEY_SAVE(NVID_DPI_SETTING_LIST_1 + sensor_ctrl.profile_idx, (const uint8_t*)curr_dpi_cfg, sizeof(T_DPI_CONFIG_S));
    if(err){
        DBG_LOGI(thisMOD,"msmgr_set_current_dpi write nvkey error = %d", err);
    }
    return RACE_ERRCODE_SUCCESS;
}

#if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
uint8_t msmgr_set_dpi_value(uint8_t idx, uint16_t x_dpi_value, uint16_t y_dpi_value)
{
    if(idx >= MAX_DPI_COUNT)
    {
        return RACE_ERRCODE_FAIL;
    }
    /* Check that the dpi range and stepping are as expected by the driver. */
    if((x_dpi_value < SENSOR_DPI_MIN_VALUE) || (x_dpi_value > SENSOR_DPI_MAX_VALUE)
       ||(y_dpi_value < SENSOR_DPI_MIN_VALUE) || (y_dpi_value > SENSOR_DPI_MAX_VALUE))
    {
        return RACE_ERRCODE_NOT_SUPPORT;
    }

    if((x_dpi_value % SENSOR_DPI_STEP_VALUE) || (y_dpi_value % SENSOR_DPI_STEP_VALUE))
    {
        return RACE_ERRCODE_PARAMETER_ERROR;
    }

    curr_dpi_cfg->x_dpi_settings[idx] = x_dpi_value;
    curr_dpi_cfg->y_dpi_settings[idx] = y_dpi_value;

    /* Apply dpi value to sensor if current dpi index equals to the updated one */
    if(curr_dpi_cfg->dpi_curr_idx == idx)
    {
        msmgr_dpi_setting(DPI_STAGE_LOOP, ACCORDING_TO_PROFILE, ACCORDING_TO_PROFILE);
    }

    int8_t err = HID_SCENARIO_NVKEY_SAVE(NVID_DPI_SETTING_LIST_1 + sensor_ctrl.profile_idx, (const uint8_t*)curr_dpi_cfg, sizeof(T_DPI_CONFIG_S));
    if(err){
        DBG_LOGI(thisMOD,"msmgr_set_dpi_value write nvkey error = %d", err);
    }
    return RACE_ERRCODE_SUCCESS;
}
#else
uint8_t msmgr_set_dpi_value(uint8_t idx, uint16_t dpi_value)
{
    if(idx >= MAX_DPI_COUNT)
    {
        return RACE_ERRCODE_FAIL;
    }
    /* Check that the dpi range and stepping are as expected by the driver. */
    if((dpi_value < SENSOR_DPI_MIN_VALUE) || (dpi_value > SENSOR_DPI_MAX_VALUE))
    {
        return RACE_ERRCODE_NOT_SUPPORT;
    }

    if(dpi_value % SENSOR_DPI_STEP_VALUE)
    {
        return RACE_ERRCODE_PARAMETER_ERROR;
    }

    curr_dpi_cfg->dpi_settings[idx] = dpi_value;

    /* Apply dpi value to sensor if current dpi index equals to the updated one */
    if(curr_dpi_cfg->dpi_curr_idx == idx)
    {
        msmgr_dpi_setting(DPI_STAGE_LOOP, ACCORDING_TO_PROFILE);
    }

    int8_t err = HID_SCENARIO_NVKEY_SAVE(NVID_DPI_SETTING_LIST_1 + sensor_ctrl.profile_idx, (const uint8_t*)curr_dpi_cfg, sizeof(T_DPI_CONFIG_S));
    if(err){
        DBG_LOGI(thisMOD,"msmgr_set_dpi_value write nvkey error = %d", err);
    }
    return RACE_ERRCODE_SUCCESS;
}
#endif

#if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
uint8_t msmgr_get_dpi_value(uint8_t *loop_stage_range, uint8_t *curr_idx, uint16_t *x_dpi_value_array, uint16_t *y_dpi_value_array)
{
    *loop_stage_range = curr_dpi_cfg->dpi_loop_stage_range;
    *curr_idx = curr_dpi_cfg->dpi_curr_idx;
    memcpy((void*)x_dpi_value_array, (void*)(curr_dpi_cfg->x_dpi_settings), sizeof(curr_dpi_cfg->x_dpi_settings));
    memcpy((void*)y_dpi_value_array, (void*)(curr_dpi_cfg->y_dpi_settings), sizeof(curr_dpi_cfg->y_dpi_settings));

    for(uint32_t idx = 0; idx < MAX_DPI_COUNT; idx++){
        DBG_LOGI(thisMOD, "dpi value idx = %d, x_value = %d, y_value = %d", idx, x_dpi_value_array[idx], y_dpi_value_array[idx]);
    }
    return RACE_ERRCODE_SUCCESS;
}
#else
uint8_t msmgr_get_dpi_value(uint8_t *loop_stage_range, uint8_t *curr_idx, uint16_t *dpi_value_array)
{
    *loop_stage_range = curr_dpi_cfg->dpi_loop_stage_range;
    *curr_idx = curr_dpi_cfg->dpi_curr_idx;
    memcpy((void*)dpi_value_array, (void*)(curr_dpi_cfg->dpi_settings), sizeof(curr_dpi_cfg->dpi_settings));

    for(uint32_t idx = 0; idx < MAX_DPI_COUNT; idx++){
        DBG_LOGI(thisMOD, "dpi value idx = %d, value = %d", idx, dpi_value_array[idx]);
    }
    return RACE_ERRCODE_SUCCESS;
}
#endif

uint8_t msmgr_set_dpi_stage_range(uint8_t stage_range)
{
    if((stage_range < 1) || (stage_range > MAX_DPI_COUNT))
    {
        /* valid stage loop range is 1~MAX_DPI_COUNT */
        return RACE_ERRCODE_FAIL;
    }

    curr_dpi_cfg->dpi_loop_stage_range = stage_range;
    int8_t err = HID_SCENARIO_NVKEY_SAVE(NVID_DPI_SETTING_LIST_1 + sensor_ctrl.profile_idx, (const uint8_t*)curr_dpi_cfg, sizeof(T_DPI_CONFIG_S));
    if(err){
        DBG_LOGI(thisMOD,"msmgr_set_dpi_stage_range write nvkey error = %d", err);
    }
    return RACE_ERRCODE_SUCCESS;
}

#if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
void msmgr_dpi_change(uint8_t type, uint16_t x_value, uint16_t y_value)
#else
void msmgr_dpi_change(uint8_t type, uint16_t value)
#endif
{
    uint32_t hid_flags = hid_common->hid.flags;
    if(!BT_DATA_GO(hid_flags) && !USB_DATA_GO(hid_flags) && !GAMING_DATA_GO(hid_flags))
    {
        return;
    }

    switch(type)
    {
        case DPI_STAGE_LOOP:
        {
            curr_dpi_cfg->dpi_curr_idx = (curr_dpi_cfg->dpi_curr_idx + 1) % curr_dpi_cfg->dpi_loop_stage_range;
        }
        break;

        case DPI_STAGE_MINUS:
        {
            #if defined(AIR_DPI_SWITCH_RFOM_DEFAULT)
            #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
            if(x_value == DPI_DEFAULT_STAGE_CHANGE)
            #else
            if(value == DPI_DEFAULT_STAGE_CHANGE)
            #endif
            {
                curr_dpi_cfg->dpi_curr_idx = sensor_ctrl.dpi_default_stage;
            }
            #endif

            if(curr_dpi_cfg->dpi_curr_idx > 0)
            {
                curr_dpi_cfg->dpi_curr_idx--;
            }
        }
        break;

        case DPI_STAGE_PLUS:
        {
            #if defined(AIR_DPI_SWITCH_RFOM_DEFAULT)
            #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
            if(x_value == DPI_DEFAULT_STAGE_CHANGE)
            #else
            if(value == DPI_DEFAULT_STAGE_CHANGE)
            #endif
            {
                curr_dpi_cfg->dpi_curr_idx = sensor_ctrl.dpi_default_stage;
            }
            #endif

            if(curr_dpi_cfg->dpi_curr_idx < curr_dpi_cfg->dpi_loop_stage_range - 1)
            {
                curr_dpi_cfg->dpi_curr_idx++;
            }
        }
        break;

        case DPI_STAGE_LOCK:
        break;
    }

    #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
    msmgr_dpi_setting(type, x_value, y_value);
    #else
    msmgr_dpi_setting(type, value);
    #endif

    int8_t err = HID_SCENARIO_NVKEY_SAVE(NVID_DPI_SETTING_LIST_1 + sensor_ctrl.profile_idx, (const uint8_t*)curr_dpi_cfg, sizeof(T_DPI_CONFIG_S));
    if(err){
        DBG_LOGI(thisMOD,"msmgr_dpi_change write nvkey error = %d", err);
    }
}

void msmgr_get_current_dpi_status(T_DPI_STATUS_S* ret_cfg)
{
    uint8_t curr_idx = curr_dpi_cfg->dpi_curr_idx;
    ret_cfg->dpi_idx =  curr_idx;

    #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
    uint16_t curr_x_dpi = curr_dpi_cfg->x_dpi_settings[curr_dpi_cfg->dpi_curr_idx];
    uint16_t curr_y_dpi = curr_dpi_cfg->y_dpi_settings[curr_dpi_cfg->dpi_curr_idx];
    DBG_LOGI(thisMOD,"msmgr_get_current_dpi_status, dpi_idx = %d, x_val = %d, y_val = %d", curr_idx, curr_x_dpi, curr_y_dpi);
    ret_cfg->x_dpi_value = curr_x_dpi;
    ret_cfg->y_dpi_value = curr_y_dpi;
    #else
    uint16_t curr_dpi = curr_dpi_cfg->dpi_settings[curr_dpi_cfg->dpi_curr_idx];
    DBG_LOGI(thisMOD,"msmgr_get_current_dpi_status, dpi_idx = %d, val = %d", curr_idx, curr_dpi);
    ret_cfg->dpi_value = curr_dpi;
    #endif
}

uint8_t msmgr_set_attr_config(T_MOTION_ATTRIBUTE_E attr_type, uint8_t attr_value, uint8_t link_mode, uint16_t report_rate)
{
    int err = 0;
    struct sensor_value val = {attr_value, 0};
    DBG_LOGI(thisMOD,"msmgr_set_attr_config profile[%d] attr = %d, value = %d", sensor_ctrl.profile_idx, attr_type, attr_value);

    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_start();
    #endif

    switch(attr_type)
    {
        case SENSOR_LOD:
        {
            if(attr_value <= 2)
            {
                if(curr_sensor_attr_cfg->lod != attr_value)
                {
                    switch(attr_value)
                    {
                        #if defined(CONFIG_PIXART_PAW3950)
                        case lod_0_7mm:
                        {
                            val.val1 = lift_cut_off_0_7mm;
                        }
                        break;
                        #endif

                        case lod_1mm:
                        {
                            val.val1 = lift_cut_off_1mm;
                        }
                        break;

                        case lod_2mm:
                        {
                            val.val1 = lift_cut_off_2mm;
                        }
                        break;
                    }
                    curr_sensor_attr_cfg->lod = attr_value;

                    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_LOD  , &val);
                    err = HID_SCENARIO_NVKEY_SAVE(NVID_SENSOR_ATTR_SETTING_1 + sensor_ctrl.profile_idx, (const uint8_t*)curr_sensor_attr_cfg, sizeof(T_SENSOR_ATTR_CONFIG_S));
                }
            }
            else
            {
                return RACE_ERRCODE_PARAMETER_ERROR;
            }
        }
        break;

        case SENSOR_MOTION_SYNC:
        {
            if(attr_value <= 1)
            {
                #if defined(CONFIG_PIXART_PAW3395)
                #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
                if((link_mode != HID_SCENARIO_BT_MODE) && (report_rate == 8000))
                #else
                if(report_rate == 8000)
                #endif
                {
                    val.val1 = false;
                    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_MOTION_SYNC  , &val);
                    DBG_LOGI(thisMOD,"RR 8k Disable MOTION_SYNC");
                }
                else
                #endif /* CONFIG_PIXART_PAW3395 */
                {
                    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_MOTION_SYNC  , &val);
                }

                if(curr_sensor_attr_cfg->motion_sync != attr_value)
                {
                    curr_sensor_attr_cfg->motion_sync = attr_value;
                    err = HID_SCENARIO_NVKEY_SAVE(NVID_SENSOR_ATTR_SETTING_1 + sensor_ctrl.profile_idx, (const uint8_t*)curr_sensor_attr_cfg, sizeof(T_SENSOR_ATTR_CONFIG_S));
                }
            }
            else
            {
                return RACE_ERRCODE_PARAMETER_ERROR;
            }
        }
        break;

        case SENSOR_ANGLE_SNAP:
        {
            if(attr_value <= 1)
            {
                sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_ANGLE_SNAP  , &val);
                if(curr_sensor_attr_cfg->angle_snap != attr_value)
                {
                    curr_sensor_attr_cfg->angle_snap = attr_value;
                    err = HID_SCENARIO_NVKEY_SAVE(NVID_SENSOR_ATTR_SETTING_1 + sensor_ctrl.profile_idx, (const uint8_t*)curr_sensor_attr_cfg, sizeof(T_SENSOR_ATTR_CONFIG_S));
                }
            }
            else
            {
                return RACE_ERRCODE_PARAMETER_ERROR;
            }
        }
        break;

        case SENSOR_RIPPLE_CONTROL:
        {
            if(attr_value <= 1)
            {
                sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_RIPPLE_CONTROL  , &val);
                if(curr_sensor_attr_cfg->ripple_control != attr_value)
                {
                    curr_sensor_attr_cfg->ripple_control = attr_value;
                    err = HID_SCENARIO_NVKEY_SAVE(NVID_SENSOR_ATTR_SETTING_1 + sensor_ctrl.profile_idx, (const uint8_t*)curr_sensor_attr_cfg, sizeof(T_SENSOR_ATTR_CONFIG_S));
                }
            }
            else
            {
                return RACE_ERRCODE_PARAMETER_ERROR;
            }
        }
        break;
    }

    if(err){
        DBG_LOGI(thisMOD,"msmgr_set_attr_config write nvkey error = %d", err);
    }


    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_end();
    #else
    if(sensor_ctrl.bt_trigger)
    {
        msmgr_bt_trigger_enable();
    }
    #endif
    
    return RACE_ERRCODE_SUCCESS;
}

uint8_t msmgr_get_attr_config(T_MOTION_ATTRIBUTE_E attr_type)
{
    switch(attr_type)
    {
        case SENSOR_LOD:
        {
            DBG_LOGI(thisMOD,"msmgr_get_attr_config profile[%d] SENSOR_LOD, value = %d", sensor_ctrl.profile_idx, curr_sensor_attr_cfg->lod);
            return curr_sensor_attr_cfg->lod;
        }

        case SENSOR_MOTION_SYNC:
        {
            DBG_LOGI(thisMOD,"msmgr_get_attr_config profile[%d] SENSOR_MOTION_SYNC, value = %d", sensor_ctrl.profile_idx, curr_sensor_attr_cfg->motion_sync);
            return curr_sensor_attr_cfg->motion_sync;
        }

        case SENSOR_ANGLE_SNAP:
        {
            DBG_LOGI(thisMOD,"msmgr_get_attr_config profile[%d] SENSOR_ANGLE_SNAP, value = %d", sensor_ctrl.profile_idx, curr_sensor_attr_cfg->angle_snap);
            return curr_sensor_attr_cfg->angle_snap;
        }

        case SENSOR_RIPPLE_CONTROL:
        {
            DBG_LOGI(thisMOD,"msmgr_get_attr_config profile[%d] SENSOR_RIPPLE_CONTROL, value = %d", sensor_ctrl.profile_idx, curr_sensor_attr_cfg->ripple_control);
            return curr_sensor_attr_cfg->ripple_control;
        }
    }
    return 0;
}

void msmgr_clear_sensor_data()
{
    struct sensor_value val = {3, 0};
    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_start();
    #endif
    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_CLEAR_DATA  , &val);
    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_end();
    #endif
}

void msmgr_keep_high_fps(bool enable)
{
    struct sensor_value val = {enable, 0};
    DBG_LOGI(thisMOD,"msmgr_keep_high_fps: %d", enable);
    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_start();
    #endif
    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_KEEP_HIGH_FPS, &val);
    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_end();
    #endif
}

/* According to mode and report rate, to set the sensor mode */
void msmgr_mode_setting(uint8_t link_mode, uint16_t report_rate)
{
    struct sensor_value val = {office_mode, 0}; 
    DBG_LOGI(thisMOD,"msmgr_mode_setting link_mode = %d, report_rate = %d", link_mode, report_rate);
    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_start();
    #endif
    switch(link_mode)
    {
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        case HID_SCENARIO_BT_MODE:
        {
            sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_MODE_SET, &val);
        }
        break;
        #endif
        case HID_SCENARIO_GAMING_MODE:
        {
            switch (report_rate)
            {
                case 8000:
                case 4000:
                case 2000:
                    val.val1 = corded_gaming_mode;
                    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_MODE_SET, &val);
                    break;

                case 1200:
                    val.val1 = high_performance_mode;
                    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_MODE_SET, &val);
                    break;

                case 1000:
                case 500:
                case 250:
                case 125:
                    val.val1 = low_power_mode;
                    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_MODE_SET, &val);
                    break;
            }
        }
        break;

        case HID_SCENARIO_USB_MODE:
        {
            val.val1 = corded_gaming_mode;
            sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_MODE_SET, &val);
        }
        break;
    }
    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_end();
    #endif
}

void msmgr_motion_sync_config(uint8_t link_mode, uint16_t report_rate)
{
    struct sensor_value val = {curr_sensor_attr_cfg->motion_sync, 0};

    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_start();
    #endif
    #if defined(CONFIG_PIXART_PAW3395)
    #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
    if((link_mode != HID_SCENARIO_BT_MODE) && (report_rate == 8000))
    #else
    if(report_rate == 8000)
    #endif
    {
        val.val1 = false;
        sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_MOTION_SYNC  , &val);
        DBG_LOGI(thisMOD,"RR 8k Disable MOTION_SYNC");
    }
    else
    #endif /* CONFIG_PIXART_PAW3395 */
    {
        sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_MOTION_SYNC  , &val);
    }

    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_end();
    #else
    if(link_mode != HID_SCENARIO_USB_MODE)
    {
        msmgr_bt_trigger_enable();
        sensor_ctrl.bt_trigger = true;
    }
    else
    {
        sensor_ctrl.bt_trigger = false;
    }
    #endif
    
    DBG_LOGI(thisMOD,"msmgr_motion_sync_config = %d complete !", val.val1);
    msmgr_print_sensor_ram_attr();
}

/* This function configures the rest mode with the given rest1 and rest2 downshift times when enter to idle. */
void msmgr_downshift_time_config(uint32_t rest1_downshift_time, uint32_t rest2_downshift_time)
{
    struct sensor_value val= {1000, 0};
    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_start();
    #endif
    
    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_RUN_DOWNSHIFT_TIME  , &val);
    val.val1 = rest1_downshift_time & 0xFFFF; // according to idle1
    val.val2 = rest1_downshift_time >> 16;
    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_REST1_DOWNSHIFT_TIME  , &val);
    val.val1 = rest2_downshift_time & 0xFFFF; // according to idle2
    val.val2 = rest2_downshift_time >> 16;
    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_REST2_DOWNSHIFT_TIME  , &val);
    DBG_LOGI(thisMOD,"msmgr_downshift_time_config complete !");

    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_end();
    #endif
}

void msmgr_motion_isr_disable()
{
    MOTION_ISR_DISABLE();
}

uint32_t msmgr_motion_pin_mask()
{
    uint32_t eint_mask = *(volatile uint32_t*)0x42140114;
    uint32_t motion_pin_mask = (eint_mask >> 18) & 1;
    DBG_LOGI(thisMOD,"msmgr_motion_pin_mask = %08X, motion pin = %d", eint_mask, motion_pin_mask);
    return motion_pin_mask;
}

void msmgr_enter_low_power_set_wakeup()
{
    extern hal_gpio_status_t hal_gpio_wakeup_extend_sleep_config(hal_gpio_pin_t gpio_pin);
    hal_gpio_wakeup_extend_sleep_config(MOUSE_SENSOR_PIN);
}

void msmgr_exit_low_power()
{
    extern hal_gpio_status_t hal_gpio_wakeup_extend_sleep_clear(hal_gpio_pin_t gpio_pin);
    hal_gpio_wakeup_extend_sleep_clear(MOUSE_SENSOR_PIN);
}

void msmgr_parking_mode(msmgr_motion_isr_callback motion_pin_isr_cb)
{
    DBG_LOGI(thisMOD,"msmgr_parking_mode");
    struct sensor_value val = {true, 0};
    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_start();
    #endif
    if (STATE_CHECK(SENSOR_STATE_OFF))
    {
        int ret_attr = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_INIT, &val);
        DBG_LOGI(thisMOD,"SENSOR_STATE_OFF, ret_attr = %d", ret_attr);
        msmgr_configure_motion_pin(motion_pin_isr_cb);
    }

    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_REST_MODE  , &val);
    val.val1 = false;
    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_MOTION_SYNC  , &val);

    msmgr_clear_sensor_data();

    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_end();
    #endif
    
    MOTION_ISR_ENABLE();

    STATE_CHANGE(SENSOR_STATE_PARKING);
}

void msmgr_driving_mode(uint8_t mode, uint16_t report_rate) // Power Consumption : high
{
    MOTION_ISR_DISABLE();
  
    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_start();
    #endif
    msmgr_mode_setting(mode, report_rate); // According to mode and report rate
    struct sensor_value val = {false, 0}; 
    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_REST_MODE  , &val);

    #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
    val.val1 = curr_dpi_cfg->x_dpi_settings[curr_dpi_cfg->dpi_curr_idx]; // according to profile
    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_CPI_X  , &val);
    val.val1 = curr_dpi_cfg->y_dpi_settings[curr_dpi_cfg->dpi_curr_idx]; // according to profile
    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_CPI_Y  , &val);
    DBG_LOGI(thisMOD,"msmgr_driving_mode, REST_MODE = %d, X_CPI = %d, Y_CPI = %d", false, curr_dpi_cfg->x_dpi_settings[curr_dpi_cfg->dpi_curr_idx], curr_dpi_cfg->y_dpi_settings[curr_dpi_cfg->dpi_curr_idx]);
    #else
    val.val1 = curr_dpi_cfg->dpi_settings[curr_dpi_cfg->dpi_curr_idx]; // according to profile
    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_CPI  , &val);
    DBG_LOGI(thisMOD,"msmgr_driving_mode, REST_MODE = %d, CPI = %d", false, curr_dpi_cfg->dpi_settings[curr_dpi_cfg->dpi_curr_idx]);
    #endif
    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_end();
    #endif
    STATE_CHANGE(SENSOR_STATE_DRIVING);
}

void msmgr_rest_mode()     // Power Consumption : low. Rest mode
{
    DBG_LOGI(thisMOD,"msmgr_rest_mode, REST_MODE = %d, MOTION_SYNC = %d", true, false);

    MOTION_ISR_ENABLE();
    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_start();
    #endif
    struct sensor_value val = {true, 0};
    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_REST_MODE  , &val);
    val.val1 = false;
    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_MOTION_SYNC  , &val);
    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_end();
    #endif
    STATE_CHANGE(SENSOR_STATE_REST);
}

void msmgr_off_mode()      // Power Consumption : 0. power cut
{
    DBG_LOGI(thisMOD,"msmgr_off_mode");
    struct sensor_value val = {0, 0};

    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_DEINIT  , &val);

    STATE_CHANGE(SENSOR_STATE_OFF);
}

void msmgr_reinit()
{
    struct sensor_value val = {true, 0};
    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_start();
    #endif
    sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_REINIT, &val);
    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    msmgr_config_end();
    #endif
}

#if 0
void msmgr_get_sensor_attr()
{
    struct sensor_value val = {0, 0};
    sensor_attr_get(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_MODE_SET, &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_MODE_SET = %d",  val.val1);
    sensor_attr_get(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_REST_MODE  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_REST_MODE = %d",  val.val1);
    sensor_attr_get(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_CPI  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_CPI = %d",  val.val1);
    sensor_attr_get(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_MOTION_SYNC  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_MOTION_SYNC = %d",  val.val1);
    sensor_attr_get(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_REST2_PERIOD_TIME  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_REST2_PERIOD_TIME = %d",  val.val1);
    sensor_attr_get(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_REST3_PERIOD_TIME  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_REST3_PERIOD_TIME = %d",  val.val1);
    sensor_attr_get(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_RUN_DOWNSHIFT_TIME  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_RUN_DOWNSHIFT_TIME = %d",  val.val1);
    sensor_attr_get(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_REST1_DOWNSHIFT_TIME  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_REST1_DOWNSHIFT_TIME = %d",  ((uint16_t)val.val2<<16|(uint16_t)val.val1));
    sensor_attr_get(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_REST2_DOWNSHIFT_TIME  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_REST2_DOWNSHIFT_TIME = %d",  ((uint16_t)val.val2<<16|(uint16_t)val.val1));
    sensor_attr_get(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_ANGLE_SNAP  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_ANGLE_SNAP = %d",  val.val1);
    sensor_attr_get(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_RIPPLE_CONTROL  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_RIPPLE_CONTROL = %d",  val.val1);
    sensor_attr_get(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_LOD  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_LOD = %d",  val.val1);

    //msmgr_bt_trigger_enable();
}
#endif

void msmgr_print_sensor_ram_attr()
{
    struct sensor_value val = {0, 0};
    sensor_attr_get(dev_hdl_sensor, MOUSE_SENSOR_CHAN_RAM_DATA, MOUSE_SENSOR_ATTR_SPI_STATUS, &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_SPI_STATUS = %d",  val.val1);
    sensor_attr_get(dev_hdl_sensor, MOUSE_SENSOR_CHAN_RAM_DATA, MOUSE_SENSOR_ATTR_MODE_SET, &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_MODE_SET = %d",  val.val1);
    sensor_attr_get(dev_hdl_sensor, MOUSE_SENSOR_CHAN_RAM_DATA, MOUSE_SENSOR_ATTR_REST_MODE  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_REST_MODE = %d",  val.val1);
    sensor_attr_get(dev_hdl_sensor, MOUSE_SENSOR_CHAN_RAM_DATA, MOUSE_SENSOR_ATTR_CPI  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_CPI = %d",  val.val1);
    sensor_attr_get(dev_hdl_sensor, MOUSE_SENSOR_CHAN_RAM_DATA, MOUSE_SENSOR_ATTR_MOTION_SYNC  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_MOTION_SYNC = %d",  val.val1);
    sensor_attr_get(dev_hdl_sensor, MOUSE_SENSOR_CHAN_RAM_DATA, MOUSE_SENSOR_ATTR_REST1_PERIOD_TIME  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_REST1_PERIOD_TIME = %d",  val.val1);
    sensor_attr_get(dev_hdl_sensor, MOUSE_SENSOR_CHAN_RAM_DATA, MOUSE_SENSOR_ATTR_REST2_PERIOD_TIME  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_REST2_PERIOD_TIME = %d",  val.val1);
    sensor_attr_get(dev_hdl_sensor, MOUSE_SENSOR_CHAN_RAM_DATA, MOUSE_SENSOR_ATTR_REST3_PERIOD_TIME  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_REST3_PERIOD_TIME = %d",  val.val1);
    sensor_attr_get(dev_hdl_sensor, MOUSE_SENSOR_CHAN_RAM_DATA, MOUSE_SENSOR_ATTR_RUN_DOWNSHIFT_TIME  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_RUN_DOWNSHIFT_TIME = %d",  val.val1);
    sensor_attr_get(dev_hdl_sensor, MOUSE_SENSOR_CHAN_RAM_DATA, MOUSE_SENSOR_ATTR_REST1_DOWNSHIFT_TIME  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_REST1_DOWNSHIFT_TIME = %d",  ((uint16_t)val.val2<<16|(uint16_t)val.val1));
    sensor_attr_get(dev_hdl_sensor, MOUSE_SENSOR_CHAN_RAM_DATA, MOUSE_SENSOR_ATTR_REST2_DOWNSHIFT_TIME  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_REST2_DOWNSHIFT_TIME = %d",  ((uint16_t)val.val2<<16|(uint16_t)val.val1));
    sensor_attr_get(dev_hdl_sensor, MOUSE_SENSOR_CHAN_RAM_DATA, MOUSE_SENSOR_ATTR_ANGLE_SNAP  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_ANGLE_SNAP = %d",  val.val1);
    sensor_attr_get(dev_hdl_sensor, MOUSE_SENSOR_CHAN_RAM_DATA, MOUSE_SENSOR_ATTR_RIPPLE_CONTROL  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_RIPPLE_CONTROL = %d",  val.val1);
    sensor_attr_get(dev_hdl_sensor, MOUSE_SENSOR_CHAN_RAM_DATA, MOUSE_SENSOR_ATTR_LOD  , &val);
    DBG_LOGI(thisMOD,"MOUSE_SENSOR_ATTR_LOD = %d",  val.val1);

    //msmgr_bt_trigger_enable();
}

void msmgr_dpi_config_init(const T_DPI_CONFIG_S *dpi_cfg, uint8_t profile_idx, uint16_t report_rate, uint8_t link_mode)
{
    if(dpi_cfg_default == NULL){
        dpi_cfg_default = dpi_cfg;
    }
    msmgr_reload_sensor_attr(profile_idx, false, report_rate, link_mode);
    return;
}

void msmgr_init(msmgr_motion_isr_callback motion_pin_isr_cb)
{
    #if defined(CONFIG_PIXART_PAW3950)
    dev_hdl_sensor = DEVICE_DT_GET(DT_NODELABEL(paw3950));
    DBG_LOGI(thisMOD,"msmgr_init paw3950 , dev_hdl_sensor = 0x%x", *(uint32_t*)dev_hdl_sensor);
    #else
    dev_hdl_sensor = DEVICE_DT_GET(DT_NODELABEL(paw3395));
    DBG_LOGI(thisMOD,"msmgr_init paw3395, dev_hdl_sensor = 0x%x", *(uint32_t*)dev_hdl_sensor);
    #endif

    if (STATE_CHECK(SENSOR_STATE_OFF))
    {
        struct sensor_value val = {true, 0};
        int ret_attr1 = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_INIT, &val);
        val.val1 = false;
        int res_attr2 = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_MOTION_SYNC , &val);
        STATE_CHANGE(SENSOR_STATE_INIT);
        DBG_LOGI(thisMOD,"SENSOR_STATE_INIT, ret_attr1 = %d, ret_attr2 = %d", ret_attr1, res_attr2);
    }

    #if defined(CONFIG_AIR_RUNTIME_BT_TRIGGER)
    k_timer_init(&sensor_cfg_timer , msmgr_config_end_confirm, NULL);
    #endif
    msmgr_clear_sensor_data();
    msmgr_configure_motion_pin(motion_pin_isr_cb);
}
#endif









