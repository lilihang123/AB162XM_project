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

#include <zephyr/bluetooth/services/bas.h>
#include <zephyr/bluetooth/gatt.h>
#include "app_battery.h"
#include "app_state.h"
#include "app_button.h"
#include "app_usb_port.h"

#if defined (AIR_BATTERY_MANAGEMENT_ENABLE)
#include "bm_core.h"
#include "bm_cust.h"
#endif /* _AIR_BATTERY_MANAGEMENT_ENABLE_ */

#define thisMODULE bat
#define thisMOD    "bat"
LOG_MODULE_REGISTER(thisMODULE);

#define UNUSED(x)  ((void)(x))

/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
#if defined (AIR_BATTERY_MANAGEMENT_ENABLE)
static int app_battery__bt_bas_set_battery_level(uint8_t level);
static void app_battery_bas_cccd_cb(const struct bt_gatt_attr *attr, uint16_t value);
static ssize_t app_battery_read_battery_level(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset);
static void app_battery__race_cmd_rsp_and_notify();

static bool app_battery__check_vbat_change(uint32_t bm_vbat);
static bool app_battery__check_soc_change(uint8_t bm_soc);
static bool app_battery__check_chg_state_change(uint8_t bm_chg_state);
static bool app_battery__check_chg_en_sta_change(bool bm_chg_en_sta);
static bool app_battery__check_chg_exist_change(bool bm_chg_exist);
static bool app_battery__check_low_battery();

static void app_battery_update_var();
static void app_battery_check_info();
static void app_battery_bat_event_announcement(uint8_t status, uint8_t val);
static void app_battery_bat_timer_evt_announcement(uint8_t cmd);

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
static uint8_t app_bat_low_battery_warn = false;
#endif /* _AIR_BATTERY_MANAGEMENT_ENABLE_ */
static T_APP_BATTERY_INFO_S app_bat; //store APP battery var

#if defined (AIR_BATTERY_MANAGEMENT_ENABLE)
/********************************* uuid ******************************************/
static const struct bt_gatt_cpf level_cpf = {
    .format = 0x04,        /* uint8 */
    .exponent = 0x0,
    .unit = 0x27AD,        /* Percentage */
    .name_space = 0x01,    /* Bluetooth SIG */
    .description = 0x0106, /* "main" */
};

BT_GATT_SERVICE_DEFINE(bas_svc,
    BT_GATT_PRIMARY_SERVICE(BT_UUID_BAS),
    BT_GATT_CHARACTERISTIC(BT_UUID_BAS_BATTERY_LEVEL, BT_GATT_CHRC_NOTIFY | BT_GATT_CHRC_READ,
    BT_GATT_PERM_READ, app_battery_read_battery_level, NULL, &app_bat.soc),
    BT_GATT_CCC(app_battery_bas_cccd_cb, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
    BT_GATT_CPF(&level_cpf),
);

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/
static void app_battery_bas_cccd_cb(const struct bt_gatt_attr *attr, uint16_t value)
{
    int ret = app_battery__bt_bas_set_battery_level(app_bat.soc);
    if(ret){
        APP_LOGI(thisMOD,"[CHECK_GATT]app_battery_bas_cccd_cb, error with set battery level, ret = %d", ret);
        return;
    }
    APP_LOGI(thisMOD,"[CHECK_GATT]app_battery_bas_cccd_cb, battery power is ok, soc = %d", app_bat.soc);
}

void app_battery_handle_vbat(void *data)
{
    APP_LOGI(thisMOD, "app_battery_handle_vbat");
    UNUSED(data);
    app_battery_bat_timer_evt_announcement(APP_BAT_VBAT);
}

void app_battery_handle_soc(void *data)
{
    APP_LOGI(thisMOD, "app_battery_handle_soc");
    UNUSED(data);
    app_battery_bat_timer_evt_announcement(APP_BAT_SOC);
}

void app_battery_handle_chg_exist(void *data)
{
    APP_LOGI(thisMOD, "app_battery_handle_chg_exist");
    UNUSED(data);
    app_battery_bat_timer_evt_announcement(APP_BAT_CHG_EXIST);
}

void app_battery_handle_chg_sta(void *data)
{
    APP_LOGI(thisMOD, "app_battery_handle_chg_sta");
    UNUSED(data);
    app_battery_bat_timer_evt_announcement(APP_BAT_CHG_STA);
}

void app_battery_handle_chg_en_sta(void *data)
{
    APP_LOGI(thisMOD, "app_battery_handle_chg_en_sta");
    UNUSED(data);
    app_battery_bat_timer_evt_announcement(APP_BAT_CHG_EN_STA);
}

void app_battery_handle_chg_eoc(void *data)
{
    APP_LOGI(thisMOD, "app_battery_handle_chg_eoc");
    UNUSED(data);
    app_battery_bat_timer_evt_announcement(APP_BAT_CHG_EOC);
}

#if 0
void app_battery_handle_chg_curr(void *data)
{
    APP_LOGI(thisMOD, "app_battery_handle_chg_curr");
    UNUSED(data);
    app_battery_bat_timer_evt_announcement(APP_BAT_CHG_CURR);
}

void app_battery_handle_temp(void *data)
{
    APP_LOGI(thisMOD, "app_battery_handle_temp");
    UNUSED(data);
    app_battery_bat_timer_evt_announcement(APP_BAT_TEMP);
}


void app_battery_handle_bm_timer_cb(void *data)
{
    APP_LOGI(thisMOD, "app_battery_handle_bm_timer_cb");
    UNUSED(data);
    app_battery_bat_timer_evt_announcement(APP_BAT_TIMER_TO);
}

void app_battery_handle_chg_in(void *data)
{
    APP_LOGI(thisMOD, "app_battery_handle_chg_in");
    UNUSED(data);
    app_battery_bat_timer_evt_announcement(APP_BAT_CHG_IN);
}

void app_battery_handle_chg_out(void *data)
{
    APP_LOGI(thisMOD, "app_battery_handle_chg_out");
    UNUSED(data);
    app_battery_bat_timer_evt_announcement(APP_BAT_CHG_OUT);
}
#endif
#endif /* _AIR_BATTERY_MANAGEMENT_ENABLE_ */

/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
#if defined (AIR_BATTERY_MANAGEMENT_ENABLE)
static bool app_battery__evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state* event = (struct evt_app_state*)evt_header;
    switch(event->app_state)
    {
        case APP_STATE_STANDBY:
        case APP_STATE_USB_SUSPEND:
        {
            app_bat_low_battery_warn = false;
        }  //dont break
        case APP_STATE_TEST:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_1:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_2:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_3:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_2:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_3:
        {
            APP_LOGI(thisMOD,"bm_timer_stop, app_state = %02X", event->app_state);
            bm_timer_stop();
            break;
        }
        case APP_STATE_CONNECT_PREPARING:
        case APP_STATE_USB_ACTIVE:
        case APP_STATE_BT_CONNECTED_ACTIVE:
        {
            APP_LOGI(thisMOD,"bm_timer_start, app_state = %02X", event->app_state);
            bm_timer_start(BATTERY_MANAGERMENT_INTERVAL);
            app_battery_update_var();
            break;
        }
        case APP_STATE_2_4G_CONNECTED_ACTIVE:
        {
            APP_LOGI(thisMOD,"bm_timer_start, app_state = %02X", event->app_state);
            bm_timer_start(BATTERY_MANAGERMENT_INTERVAL);
            app_battery_update_var();
            app_battery__race_cmd_rsp_and_notify();
            break;
        }
        default:{
            // APP_LOGI(thisMOD,"Enter app_battery__evt_app_state default case, app_state = %d", event->app_state);
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_battery__evt_race_cmd_req(const struct af_evt_header *evt_header)
{
    struct evt_race_cmd_req* event = (struct evt_race_cmd_req*)evt_header;
    APP_LOGI(thisMOD,"evt_race_cmd_req , cmd = %x", event->cmd);

    switch(event->cmd)
    {
        case RACE_CMD_GET_BATTERY:
        {
            app_battery__race_cmd_rsp_and_notify();
            break;
        }
        default: {
            break;
        }
    }
    return AF_TRAVERSE_NEXT;
}

static bool app_battery__evt_key_event(const struct af_evt_header *evt_header)
{
    struct evt_key_event* event = (struct evt_key_event*)evt_header;
    APP_LOGI(thisMOD," app_battery__evt_key_event , key_id = %d, event = %x", event->key_id, event->key_evt);

    switch (event->key_evt)
    {
        case AK_5_CLICK:
        {
            #ifdef M_KEY_DPI
            if(event->key_id == M_KEY_DPI)
            {
                // app_battery_test_soc();
                break;
            }
            #endif
        }
        default: {
            break;
        }
    }
    return AF_TRAVERSE_NEXT;
}

static bool app_battery__evt_app_bat_timer(const struct af_evt_header *evt_header)
{
    struct evt_app_bat_timer* event = (struct evt_app_bat_timer*)evt_header;
    APP_LOGI(thisMOD,"app_battery__evt_app_bat_timer, cmd = %d", event->cmd);
    bool ret = 0;

    switch(event->cmd)
    {
        case APP_BAT_VBAT:  //0
        {
            app_battery__check_vbat_change(bm_get_info(BM_VBAT));
            break;
        }
        case APP_BAT_SOC:  //1
        {
            ret = app_battery__check_soc_change(bm_get_info(BM_SOC));
            if(ret){
                app_battery__race_cmd_rsp_and_notify();
            }
            app_battery__check_low_battery();
            break;
        }
        case APP_BAT_CHG_EXIST:  //2
        {
            app_battery__check_chg_exist_change(bm_get_info(BM_CHG_EXIST));
            break;
        }
        case APP_BAT_CHG_STA:  //3
        {
            app_battery__check_chg_state_change(bm_get_info(BM_CHG_STA));
            break;
        }
        case APP_BAT_CHG_EN_STA:  //4
        {
            ret = app_battery__check_chg_en_sta_change(bm_get_info(BM_CHG_EN_STA));
            if(ret){
                app_battery__race_cmd_rsp_and_notify();
            }
            break;
        }
        case APP_BAT_CHG_IN:  //5
        {
            APP_LOGI(thisMOD,"APP_BAT_CHG_IN, power_status = %d, chg_state = %d", app_bat.power_status, app_bat.chg_state);
            app_battery_update_var();
            break;
        }
        case APP_BAT_CHG_OUT:  //6
        {
            APP_LOGI(thisMOD,"APP_BAT_CHG_OUT, power_status = %d, chg_state = %d", app_bat.power_status, app_bat.chg_state);
            app_battery_update_var();
            break;
        }
        case APP_BAT_CHG_EOC:  //7
        {
            // app_battery_update_var();
            app_battery_bat_event_announcement(BAT_EVT_END_OF_CHARGE, app_bat.soc);
            break;
        }
        case APP_BAT_CHECK_LOW_BAT:
        {
            app_battery__check_low_battery();
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}

#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
static bool app_battery__evt_usb_status(const struct af_evt_header *evt_header)
{
    struct evt_usb_status* event = (struct evt_usb_status*)evt_header;
    APP_LOGI(thisMOD,"app_battery__evt_usb_status, status = %d", event->status);

    switch(event->status)
    {
        case USB_STATUS_PLUGGED_IN:  //1
        {
            if(!app_bat.power_status){
                app_bat.power_status = true;
            }
            app_battery_bat_timer_evt_announcement(APP_BAT_CHG_IN);
            break;
        }
        case USB_STATUS_PLUGGED_OUT:  //0
        {
            app_battery_bat_timer_evt_announcement(APP_BAT_CHG_OUT);
            app_bat_low_battery_warn = false;
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}
#endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE */
#endif /* _AIR_BATTERY_MANAGEMENT_ENABLE_ */

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
#if defined (AIR_BATTERY_MANAGEMENT_ENABLE)
static void app_battery_register_cb()
{
    bm_register_callback(BM_CB_VBAT,       (bm_callback_t)app_battery_handle_vbat,        BM_USER_APP);
    bm_register_callback(BM_CB_SOC,        (bm_callback_t)app_battery_handle_soc,         BM_USER_APP);
    // bm_register_callback(BM_CB_TEMP,     (bm_callback_t)app_battery_handle_temp,        BM_USER_APP);
    bm_register_callback(BM_CB_CHG_EXIST,  (bm_callback_t)app_battery_handle_chg_exist,   BM_USER_APP);
    bm_register_callback(BM_CB_CHG_STA,    (bm_callback_t)app_battery_handle_chg_sta,     BM_USER_APP);
    bm_register_callback(BM_CB_CHG_EN_STA, (bm_callback_t)app_battery_handle_chg_en_sta,  BM_USER_APP);
    //bm_register_callback(BM_CB_CHG_CURR,   (bm_callback_t)app_battery_handle_chg_curr,    BM_USER_APP);
    // bm_register_callback(BM_CB_CHG_IN,     (bm_callback_t)app_battery_handle_chg_in,      BM_USER_APP);
    // bm_register_callback(BM_CB_CHG_OUT,    (bm_callback_t)app_battery_handle_chg_out,     BM_USER_APP);
    bm_register_callback(BM_CB_CHG_EOC,    (bm_callback_t)app_battery_handle_chg_eoc,     BM_USER_APP);
    // bm_register_callback(BM_CB_TIMER_TO,   (bm_callback_t)app_battery_handle_bm_timer_cb, BM_USER_APP);
}

static void app_battery__race_cmd_rsp_and_notify()
{
    struct evt_race_cmd_rsp* event = create_evt_race_cmd_rsp();
    if (event){
        event->cmd = RACE_CMD_GET_BATTERY;
        event->BATTERY.charging = app_bat.chg_en_sta;
        event->BATTERY.battery = app_bat.soc;
        AF_EVT_SUBMIT(event);
        APP_LOGI(thisMOD,"RACE_CMD_GET_BATTERY, charging = %d, battery = %d", event->BATTERY.charging, event->BATTERY.battery);
    }
}

static int app_battery__bt_bas_set_battery_level(uint8_t level)
{
    if (app_state_check(TYPE_IN_BT_STATES))
    {
        if (level > 100U) {
            return -EINVAL;
        }
        int ret = bt_gatt_notify(NULL, &bas_svc.attrs[1], &level, sizeof(level));
        return ret == -ENOTCONN ? 0 : ret;
    }
    else{
        return -EPERM;
    }
}

static void app_battery_update_var()
{
    //bm_update_info();  //can not call this in ISR domain
    bm_get_chg_exist();
    bm_get_chg_sta();
    bm_get_chg_en_sta();
    //bm_get_chg_curr();
    bm_get_vbat();
    bm_get_soc();

    if(app_bat.init_flag){
        app_battery_check_info();
    }
    else{
        app_battery_bat_timer_evt_announcement(APP_BAT_CHECK_LOW_BAT);
    }
}

static bool app_battery__check_vbat_change(uint32_t bm_vbat)
{
    if((app_bat.vbat != bm_vbat) || app_bat.init_flag)
    {
        if(app_bat.chg_en_sta)
        {
            APP_LOGI(thisMOD,"In charging, vbat: %d -> %d", app_bat.vbat, bm_vbat);
            app_bat.vbat = bm_vbat;
            return true;
        }
        else if(!app_bat.chg_en_sta)
        {
            APP_LOGI(thisMOD,"No charging, vbat: %d -> %d", app_bat.vbat, bm_vbat);
            app_bat.vbat = bm_vbat;
            return true;
        }
    }
    APP_LOGI(thisMOD,"Just check vbat: %d & %d, chg_en_sta = %d, chg_exist = %d", app_bat.vbat, bm_vbat, app_bat.chg_en_sta, app_bat.chg_exist);
    return false;
}

static bool app_battery__check_soc_change(uint8_t bm_soc)
{
    if((app_bat.soc != bm_soc) || app_bat.init_flag)
    {
        if(app_bat.chg_en_sta)
        {
            APP_LOGI(thisMOD,"In charging, soc: %d -> %d", app_bat.soc, bm_soc);
            app_bat.soc = bm_soc;
            if(!app_bat.init_flag){
                app_battery__bt_bas_set_battery_level(app_bat.soc);
                app_battery_bat_event_announcement(BAT_EVT_PERCENT_CHANGE, app_bat.soc);
                if(app_bat.soc == 100){
                    app_battery_bat_timer_evt_announcement(APP_BAT_CHG_EOC);
                }
            }
            return true;
        }
        else if(!app_bat.chg_en_sta)
        {
            APP_LOGI(thisMOD,"No charging, soc: %d -> %d", app_bat.soc, bm_soc);
            app_bat.soc = bm_soc;
            if(!app_bat.init_flag){
                app_battery__bt_bas_set_battery_level(app_bat.soc);
                app_battery_bat_event_announcement(BAT_EVT_PERCENT_CHANGE, app_bat.soc);
            }
            return true;
        }
    }
    APP_LOGI(thisMOD,"Just check soc: %d & %d, chg_en_sta = %d, chg_exist = %d", app_bat.soc, bm_soc, app_bat.chg_en_sta, app_bat.chg_exist);
    return false;
}

static bool app_battery__check_chg_state_change(uint8_t bm_chg_state)
{
    if(app_bat.chg_state != bm_chg_state)
    {
        if(bm_chg_state){
            APP_LOGI(thisMOD,"Start charging, chg_state: %d -> %d", app_bat.chg_state, bm_chg_state);
        }
        else{
            APP_LOGI(thisMOD,"Stop charging, chg_state: %d -> %d", app_bat.chg_state, bm_chg_state);
        }
        app_bat.chg_state = bm_chg_state;
        if(!app_bat.init_flag){
            app_battery_bat_event_announcement(BAT_EVT_CHG_STATE_CHANGE, app_bat.chg_state);
        }
        return true;
    }
    APP_LOGI(thisMOD,"Just check chg_state: %d", app_bat.chg_state);
    return false;
}

static bool app_battery__check_chg_en_sta_change(bool bm_chg_en_sta)
{
    if(app_bat.chg_en_sta != bm_chg_en_sta)
    {
        if(bm_chg_en_sta){
            APP_LOGI(thisMOD,"In charging, chg_en_sta: %d -> %d", app_bat.chg_en_sta, bm_chg_en_sta);
        }
        else{
            APP_LOGI(thisMOD,"No charging, chg_en_sta: %d -> %d", app_bat.chg_en_sta, bm_chg_en_sta);
        }
        app_bat.chg_en_sta = bm_chg_en_sta;
        if(!app_bat.init_flag){
            app_battery_bat_event_announcement(BAT_EVT_CHG_ENABLE_STA_CHANGE, app_bat.chg_en_sta);
        }
        return true;
    }
    APP_LOGI(thisMOD,"Just check chg_en_sta: %d", app_bat.chg_en_sta);
    return false;
}

static void app_battery_check_info()
{
    T_APP_BATTERY_INFO_S bm_bat;
    bm_bat.vbat = bm_get_info(BM_VBAT);
    bm_bat.soc = bm_get_info(BM_SOC);
    bm_bat.chg_exist =  bm_get_info(BM_CHG_EXIST);
    bm_bat.chg_state = bm_get_info(BM_CHG_STA);
    bm_bat.chg_en_sta = bm_get_info(BM_CHG_EN_STA);
    APP_LOGI(thisMOD,"In bm_bat, vbat = %d, soc = %d, chg_state = %d, chg_exist = %d, chg_en = %d",
                    bm_bat.vbat, bm_bat.soc, bm_bat.chg_state, bm_bat.chg_exist, bm_bat.chg_en_sta);

    app_battery__check_chg_state_change(bm_bat.chg_state);
    app_battery__check_chg_exist_change(bm_bat.chg_exist);
    app_battery__check_chg_en_sta_change(bm_bat.chg_en_sta);
    app_battery__check_vbat_change(bm_bat.vbat);
    app_battery__check_soc_change(bm_bat.soc);
}

static bool app_battery__check_chg_exist_change(bool bm_chg_exist)
{
    if(app_bat.chg_exist != bm_chg_exist)
    {
        if(bm_chg_exist){
            APP_LOGI(thisMOD,"Plugged in, chg_exist: %d -> %d", app_bat.chg_exist, bm_chg_exist);
        }
        else{
            APP_LOGI(thisMOD,"Plugged out, chg_exist: %d -> %d", app_bat.chg_exist, bm_chg_exist);
        }
        app_bat.chg_exist = bm_chg_exist;
        if(!app_bat.init_flag){
            app_battery_bat_event_announcement(BAT_EVT_CHG_EXIST_CHANGE, app_bat.chg_exist);
        }
        return true;
    }
    APP_LOGI(thisMOD,"Just check chg_exist: %d", app_bat.chg_exist);
    return false;
}

static ssize_t app_battery_read_battery_level(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                                            void *buf, uint16_t len, uint16_t offset)
{
    APP_LOGI(thisMOD,"[CHECK_GATT]app_battery_read_battery_level, soc = %d", app_bat.soc);
    return bt_gatt_attr_read(conn, attr, buf, len, offset, &app_bat.soc, sizeof(app_bat.soc));
}

static void app_battery_bat_event_announcement(uint8_t status, uint8_t val)
{
    struct evt_app_battery* event = create_evt_app_battery();
    if (event)
    {
        APP_LOGI(thisMOD,"app_battery_bat_event_announcement, bat_evt = %d, bat_val = %d", status, val);
        event->val = val;
        event->status = status;
        AF_EVT_SUBMIT(event);
    }
}

static void app_battery_bat_timer_evt_announcement(uint8_t cmd)
{
    struct evt_app_bat_timer* event = create_evt_app_bat_timer();
    if (event)
    {
        APP_LOGI(thisMOD,"app_battery_bat_timer_evt_announcement, bat_cmd = %d", cmd);
        event->cmd = cmd;
        AF_EVT_SUBMIT(event);
    }
}

static bool app_battery__check_low_battery()
{
    if(!app_bat.chg_en_sta)
    {
        if(app_bat.soc <= BATTERY_LOW_BATTERY_PERSENTAGE)
        {
            if(!app_bat_low_battery_warn)
            {
                app_bat_low_battery_warn = true;
                APP_LOGI(thisMOD,"app_battery__check_low_battery, warning low battery!!!");
                app_battery_bat_event_announcement(BAT_EVT_LOW_BAT_WARNING, app_bat.soc);
            }
            else{
                APP_LOGI(thisMOD,"app_battery__check_low_battery, already warning once");
            }
        }
        if(app_bat.soc <= 1 && app_bat.power_status)
        {
            APP_LOGI(thisMOD,"app_battery__check_low_battery, enter STANDBY!!!");
            app_bat.power_status = false;
            app_battery_bat_event_announcement(BAT_EVT_POWER_OFF, app_bat.soc);
            return true;
        }
    }
    else {
       APP_LOGI(thisMOD,"app_battery__check_low_battery, you plugged in the charger/USB cable");
    }

    if(app_bat.soc > BATTERY_LOW_BATTERY_PERSENTAGE){
        app_bat_low_battery_warn = false;
    }

    return false;
}

#endif /* _AIR_BATTERY_MANAGEMENT_ENABLE_ */

void app_battery_init_var()
{
    app_bat.init_flag = true;
    app_bat.vbat = 2345;
    app_bat.soc = 6;
    app_bat.chg_state = 0;
    app_bat.chg_exist = 0;
    app_bat.chg_en_sta = false;
    app_bat.power_status = true;
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
bool app_battery_init()
{
    app_battery_init_var();

    #if defined (AIR_BATTERY_MANAGEMENT_ENABLE)
    bm_init();
    bm_timer_start(BATTERY_MANAGERMENT_INTERVAL); //30S间隔

    app_battery_update_var();
    app_battery__check_low_battery();
    app_bat.init_flag = false;
    app_battery_register_cb();
    #endif /* _AIR_BATTERY_MANAGEMENT_ENABLE_ */
    // APP_LOGI(thisMOD,"app_battery_init finished");

    return app_bat.power_status;
}

#if defined (AIR_BATTERY_MANAGEMENT_ENABLE)
bool app_battery__get_bat_charge_exist()
{
    APP_LOGI(thisMOD,"app_bat.chg_exist = %d", app_bat.chg_exist);
    return app_bat.chg_exist;
}

#if 0
void app_battery_test_soc()
{
    static int soc = 150;
    bm_timer_stop();

    if (soc > 0)
    {
        APP_LOGI(thisMOD,"app_battery_test_soc, would be set to %d to %d!!!", soc, soc-50);
        soc -= 50;
        app_bat.soc = soc;
        app_battery__check_low_battery();
        app_battery_bat_event_announcement(BAT_EVT_PERCENT_CHANGE, app_bat.soc);
    }
    else
    {
        soc = 100;
        app_bat.soc = soc;
        app_battery__check_low_battery();
        app_battery_bat_event_announcement(BAT_EVT_PERCENT_CHANGE, app_bat.soc);
        APP_LOGI(thisMOD, "Battery SOC has reached 0 => %d%", app_bat.soc);
    }
    if(app_bat.soc == 100){
        app_battery_bat_timer_evt_announcement(APP_BAT_CHG_EOC);
    }
}
#endif
#endif /* _AIR_BATTERY_MANAGEMENT_ENABLE_ */

bool app_battery__get_battery_power()
{
    APP_LOGI(thisMOD,"app_battery__get_battery_power, power_status = %d", app_bat.power_status);
    return app_bat.power_status;
}

uint8_t app_battery__get_battery_level()
{
    #if defined (AIR_BATTERY_MANAGEMENT_ENABLE)
    bm_get_vbat();
    bm_get_soc();
    uint8_t bm_soc = bm_get_info(BM_SOC);
    APP_LOGI(thisMOD,"bm_soc = %d", bm_soc);
    return bm_soc;
    #else
    APP_LOGI(thisMOD,"app_battery__get_battery_level, soc = %d", app_bat.soc);
    return app_bat.soc;
    #endif
}

uint8_t app_battery__get_bat_charge_status()
{
    #if defined (AIR_BATTERY_MANAGEMENT_ENABLE)
    bm_get_chg_exist();
    bm_get_chg_sta();
    bm_get_chg_en_sta();
    uint8_t bm_chg_sta = bm_get_info(BM_CHG_STA);
    uint8_t bm_chg_en_sta = bm_get_info(BM_CHG_EN_STA);
    APP_LOGI(thisMOD,"bm_chg_sta = %d, bm_chg_en_sta = %d", bm_chg_sta, bm_chg_en_sta);
    return bm_chg_sta;
    #else
    bool plug_in = app_usb_port__get_vbus_ready();
    APP_LOGI(thisMOD,"Battery config=n, just detect vbus status = %d", plug_in);
    return plug_in;
    #endif
}

bool app_battery__check_bat_charge_and_power_on()
{
    uint8_t charge = app_battery__get_bat_charge_status();
    if(charge && app_bat.power_status){
        return true;
    }
    return false;
}

/*============================Application Framework============================*/
#if defined (AIR_BATTERY_MANAGEMENT_ENABLE)
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_app_state, app_battery__evt_app_state);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_app_bat_timer, app_battery__evt_app_bat_timer);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_key_event, app_battery__evt_key_event);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_race_cmd_req, app_battery__evt_race_cmd_req);
#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_usb_status, app_battery__evt_usb_status);
#endif
#endif /* _AIR_BATTERY_MANAGEMENT_ENABLE_ */

/*=============================================================================*/