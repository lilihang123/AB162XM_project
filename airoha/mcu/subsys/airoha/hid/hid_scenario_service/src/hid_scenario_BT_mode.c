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
#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)

#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/addr.h>
#include <zephyr/sys/util.h>
#include <host/conn_internal.h>

#include "hid_scenario_service.h"
#include "hid_scenario_service_internal.h"
#include "hid_scenario_BT_mode.h"
#include "hid_scenario_adv.h"
#include "hid_scenario_nvkey.h"
#include "nvkey.h"
#include "hid_common.h"
#include "air_daemon_work_q.h"
#if defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER) && defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
#include "hid_scenario_le_gamepad.h"
#endif

#define thisMODULE  BT_mode
#define thisMOD    "BT_mode"

LOG_MODULE_REGISTER(thisMODULE);
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
static void BT_mode_connection_param_check();
static void BT_mode_dir_adv(struct k_work *work);
static void hid_scenario_bt_mode_conn_event_job(struct k_work *work);

static K_WORK_DEFINE(job_dir_adv, BT_mode_dir_adv);
static K_WORK_DEFINE(job_bt_mode_conn_event, hid_scenario_bt_mode_conn_event_job);
/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
#define IDEAL_SLAVE_LATENCY 66
#define MAX_UPDATE_ATTEMPTS 8

typedef enum
{
    BT_MODE_CONNECTED = 0,
    BT_MODE_DISCONNECTED,
    BT_MODE_SECURITY_CHANGED,
    BT_MODE_CONN_PARA_UPDATED,
    BT_MODE_STATE_CHANGE,
}T_BT_MODE_CONN_EVENT_E;

typedef struct{
    struct bt_conn *ble_conn_handle;
    bt_addr_le_t bond_addr;
    uint16_t ble_conn_interval;
    uint16_t ble_slave_latency;
    uint16_t ble_conn_timeout;
}T_BT_CONNECTION_INFO_S;

typedef struct{
    uint16_t rr;
    struct k_fifo fifo;
    T_HID_MODE_STATE_E state;
    uint8_t ble_retry_count;
    uint8_t repair;
    uint8_t repair_address_id;
    uint8_t address_id;
    uint8_t link_idx;
    bool disconnect_by_local;
}T_BT_SCENARIO_CONTROL_S;

typedef struct {
    void *fifo_reserved;
    struct bt_conn *bt_conn_ptr;
    uint8_t reason;
    T_BT_MODE_CONN_EVENT_E event;
    bt_security_t level;
	enum bt_security_err err;
    T_HID_MODE_STATE_E state;
} conn_event_fifo_t;

T_BT_CONNECTION_INFO_S conn_info;
T_BT_SCENARIO_CONTROL_S bt_mode =
{
    .state = MODE_CLOSED,
    .ble_retry_count = 0,
    .repair = 0,
    .repair_address_id = 0,
    .address_id = 0,
    .link_idx = 0,
    .disconnect_by_local = false,
};

static hid_bt_scenario_slave_latency_cb bt_slave_latency_callback = NULL;
/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/


/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/

static void copy_last_bonded_addr(const struct bt_bond_info *info, void *data)
{
	bt_addr_le_copy(&conn_info.bond_addr, &info->addr);
}

static bool BT_mode_check_bonded()
{
    bt_addr_le_copy(&conn_info.bond_addr, BT_ADDR_LE_NONE);
	bt_foreach_bond(bt_mode.address_id, copy_last_bonded_addr, NULL);

    return (bt_addr_le_cmp(&conn_info.bond_addr, BT_ADDR_LE_NONE) != 0);
}

static void BT_mode_update_conn_slave_latency()
{
    struct bt_le_conn_param conn_param = {
        .interval_min = conn_info.ble_conn_interval, 
        .interval_max = conn_info.ble_conn_interval,
        .latency      = IDEAL_SLAVE_LATENCY,
        .timeout      = 100
    };

    if(conn_info.ble_slave_latency == 0)
    {
        DBG_LOGI(thisMOD,"BT_mode_update_conn_slave_latency conn_interval = %d, slave_latency = %d", conn_info.ble_conn_interval, conn_info.ble_slave_latency);
        bt_conn_le_param_update(conn_info.ble_conn_handle, &conn_param);
        bt_mode.ble_retry_count++;
    }
    else if (bt_slave_latency_callback) 
    {
        bt_slave_latency_callback(true);
    }
}

static void BT_mode_connection_param_check()
{
    int err = 0;
    struct bt_le_conn_param conn_param = {
        .interval_min = CONFIG_BT_PERIPHERAL_PREF_MIN_INT,
        .interval_max = CONFIG_BT_PERIPHERAL_PREF_MIN_INT,
        .latency      = 0,
        .timeout      = 100
    };
    
    DBG_LOGI(thisMOD,"BT_mode_connection_param_check conn_interval = %d, slave_latency = %d", conn_info.ble_conn_interval, conn_info.ble_slave_latency);
    
    if(((conn_info.ble_conn_interval > CONFIG_BT_PERIPHERAL_PREF_MIN_INT+5) 
        || (conn_info.ble_slave_latency > 0) 
        || (conn_info.ble_conn_timeout != CONFIG_BT_PERIPHERAL_PREF_TIMEOUT))
        && (bt_mode.ble_retry_count < MAX_UPDATE_ATTEMPTS))
    {
        DBG_LOGI(thisMOD,"bt_conn_le_param_update, ideal conn_interval = %d, slave_latency = %d", CONFIG_BT_PERIPHERAL_PREF_MIN_INT, 0);
        err = bt_conn_le_param_update(conn_info.ble_conn_handle, &conn_param);
        if(err)
        {
            DBG_LOGI(thisMOD,"bt_conn_le_param_update err = %d", err);
        }
        bt_mode.ble_retry_count++;
    }
}

static void BT_mode_conn_le_param_updated_handler(struct bt_conn *conn)
{
    struct bt_conn_info info;
    int err = bt_conn_get_info(conn, &info);
    if (err) {
        DBG_LOGI(thisMOD,"bt_conn_get_info, err(%d)\n",  err);
        return;
    }
    bt_mode.rr = 800 / info.le.interval;
    DBG_LOGI(thisMOD,"BT_mode_conn_le_param_updated, interval = %d, latency = %d, timeout = %d"
        , info.le.interval
        , info.le.latency
        , info.le.timeout
        );
    
    conn_info.ble_conn_handle = conn;
    conn_info.ble_conn_interval = info.le.interval;
    conn_info.ble_slave_latency = info.le.latency;
    conn_info.ble_conn_timeout = info.le.timeout;
    
    if(bt_mode.state != MODE_STOPPED)
    {
        BT_mode_connection_param_check();
    }
    else
    {
        BT_mode_update_conn_slave_latency();
    }
}

static inline void BT_mode_disconnect_req()
{
    int err = 0;
    struct bt_conn_info info;
    bt_conn_get_info(conn_info.ble_conn_handle, &info);
    DBG_LOGI(thisMOD, "BT_mode_disconnect_req, state = %x", conn_info.ble_conn_handle->state);
    if(conn_info.ble_conn_handle->state != BT_CONN_DISCONNECTED)
    {
        err = bt_conn_disconnect(conn_info.ble_conn_handle, BT_HCI_ERR_REMOTE_USER_TERM_CONN);
        if(err)
        {
            DBG_LOGI(thisMOD, "Failed to disconnect, err = (%u), handle = %x", err, conn_info.ble_conn_handle);
        }
        else
        {
            bt_mode.disconnect_by_local = true;
            DBG_LOGI(thisMOD, "BT Disconnect request success, handle = %x", conn_info.ble_conn_handle);
        }
    }
}

static void hid_scenario_bt_mode_bond_address_save(const bt_addr_le_t* peer_addr)
{
	nvkey_status_t ret;
    ret = nvkey_write_data(NVID_BT_MODE_PEER_DEVICE_ADDR_0 + bt_mode.link_idx, (const uint8_t*)peer_addr , sizeof(bt_addr_le_t));
    DBG_LOGI(thisMOD,"nvkey write data id = 0x%08X , ret = %d, link = %d", NVID_BT_MODE_PEER_DEVICE_ADDR_0 + bt_mode.link_idx, ret, bt_mode.link_idx);
}

static bool hid_scenario_bt_mode_bond_address_is_rpa()
{
    bt_addr_le_t peer_addr = {0};
    uint8_t nvkey_size = HID_SCENARIO_NVKEY_READ_DATA(NVID_BT_MODE_PEER_DEVICE_ADDR_0 + bt_mode.link_idx, (void*)&peer_addr, sizeof(bt_addr_le_t));
    
    if(nvkey_size == 0)
    {
        DBG_LOGI(thisMOD,"Peer device address did't found");
    }
    else
    {
        if(BT_ADDR_IS_RPA(&peer_addr.a))
        {
            DBG_LOGI(thisMOD,"Peer device address is RPA, undir adv");
            return true;
        }
        else
        {
            DBG_LOGI(thisMOD,"Peer device address isn't RPA, dir adv");
            return false;
        }
    }

    return false;
}

static void hid_scenario_bt_mode_bt_id_reset()
{
    bt_addr_le_t static_random_addr = {0};
    bt_addr_le_create_static(&static_random_addr);
    int err = bt_id_reset(bt_mode.address_id, &static_random_addr, NULL);

    if (err < 0)
    {
        DBG_LOGI(thisMOD,"bt_id_reset failed with error code %d\n", err);
    }
    DBG_LOGI(thisMOD,"bt_id_reset successfully for id %d\n", err);
} 

static void BT_mode_dir_adv(struct k_work *work)
{
    hid_scenario_dir_adv_start(HID_SCENARIO_BT_MODE, &conn_info.bond_addr, bt_mode.address_id);
}

static void BT_mode_security_changed_handler(struct bt_conn *conn, bt_security_t level,
			     enum bt_security_err err)
{
    if (!err) {
        DBG_LOGI(thisMOD,"Security changed: level %d", level);
        hid_common_set_hid_exp_flag(FLAG_BIT_BT_ENCRYPTED);
        hid_scenario_send_state_update_notification(MODE_OPEN_CONNECTED_ENCRYPTED, 0);

        /* If repair success, then remove pair record */
        if(bt_mode.repair)
        {
            hid_scenario_bt_mode_bt_id_reset();
            bt_mode.repair = false;
            hid_scenario_adv_local_address_id_save(bt_mode.link_idx, bt_mode.repair_address_id);
        }
        else
        {
            /* Save link adv pair id */
            hid_scenario_adv_local_address_id_save(bt_mode.link_idx, bt_mode.address_id);
        }

    } else {
        DBG_LOGI(thisMOD,"Security failed: level %d err %d", level, err);
    }
}

static void hid_scenario_bt_mode_acl_event_handler(struct bt_conn *conn, uint8_t reason, T_BT_MODE_CONN_EVENT_E event)
{
    switch(event)
    {
        case BT_MODE_CONNECTED:
        {
            struct bt_conn_info info = {0};
            const bt_addr_le_t* dst_addr = bt_conn_get_dst(conn);
            int err = bt_conn_get_info(conn, &info);

            if (err) {
                DBG_LOGI(thisMOD,"bt_conn_get_info, err(%d)\n",  err);
            }

            if(bt_mode.state == MODE_OPEN_UNSPECIFIED)
            {
                hid_scenario_bt_mode_bond_address_save(info.le.remote);
            }

            DBG_LOGI(thisMOD,"BT_mode_connected with 0x%02X-%02X-%02X-%02X-%02X-%02X, type = %d"
                , dst_addr->a.val[0]
                , dst_addr->a.val[1]
                , dst_addr->a.val[2]
                , dst_addr->a.val[3]
                , dst_addr->a.val[4]
                , dst_addr->a.val[5]
                , dst_addr->type
                );
            
            bt_mode.ble_retry_count = 0;
            conn_info.ble_conn_handle = conn;
            conn_info.ble_conn_interval = info.le.interval;
            conn_info.ble_slave_latency = info.le.latency;
            conn_info.ble_conn_timeout = info.le.timeout;
            BT_mode_connection_param_check();

            bt_mode.state = MODE_OPEN_CONNECTED;
            hid_scenario_send_state_update_notification(bt_mode.state, 0);
        }
        break;

        case BT_MODE_DISCONNECTED:
        {
            const bt_addr_le_t* dst_addr =  bt_conn_get_dst(conn);

            DBG_LOGI(thisMOD,"BT_mode_disconnected from 0x%02X-%02X-%02X-%02X-%02X-%02X (reason 0x%02x), type = %d"
                , dst_addr->a.val[0]
                , dst_addr->a.val[1]
                , dst_addr->a.val[2]
                , dst_addr->a.val[3]
                , dst_addr->a.val[4]
                , dst_addr->a.val[5]
                , reason
                , dst_addr->type
                );

            hid_scenario_adv_stop();
            bt_mode.state = MODE_CLOSED;
            if(bt_mode.disconnect_by_local == true)
            {
                hid_scenario_send_state_update_notification(bt_mode.state, REASON_CONNECTION_TERMINATED_BY_LOCAL_HOST);
                bt_mode.disconnect_by_local = false;
            }
            else
            {
                hid_scenario_send_state_update_notification(bt_mode.state, reason);
            }
            
            hid_common_clear_hid_exp_flag(FLAG_BIT_BT_CONNECTED);
            hid_common_clear_hid_exp_flag(FLAG_BIT_BT_ENCRYPTED);
            hid_common_clear_hid_exp_flag(FLAG_BIT_ATT_NOTIFY_MOUSE_ENA);
            conn_info.ble_conn_handle = NULL;
        }
        break;

        default:
            break;
    }
}

static void hid_scenario_bt_mode_conn_event_job(struct k_work *work)
{
    conn_event_fifo_t* event_fifo = k_fifo_get(&bt_mode.fifo, K_NO_WAIT);

    while (event_fifo != NULL)
    {
        switch(event_fifo->event)
        {
            case BT_MODE_CONNECTED:
            case BT_MODE_DISCONNECTED:
            {
                hid_scenario_bt_mode_acl_event_handler(event_fifo->bt_conn_ptr, event_fifo->reason, event_fifo->event);
            }
            break;

            case BT_MODE_CONN_PARA_UPDATED:
            {
                BT_mode_conn_le_param_updated_handler(event_fifo->bt_conn_ptr);
            }
            break;

            case BT_MODE_SECURITY_CHANGED:
            {
                BT_mode_security_changed_handler(event_fifo->bt_conn_ptr, event_fifo->level, event_fifo->err);
            }
            break;

            case BT_MODE_STATE_CHANGE:
            {
                /* If connected, can't notify state; wait for close again */
                if (bt_mode.state == MODE_OPEN_UNSPECIFIED || bt_mode.state == MODE_OPEN_SPECIFIED)
                {
                    bt_mode.state = MODE_CLOSED;
                    hid_scenario_send_state_update_notification(bt_mode.state, 0);
                }
            }
            break;
        }
        
        k_free(event_fifo);
        event_fifo = k_fifo_get(&bt_mode.fifo, K_NO_WAIT);
    }
}

static void hid_scenario_bt_mode_conn_event_submit(struct bt_conn *conn, uint8_t reason, T_BT_MODE_CONN_EVENT_E event, T_HID_MODE_STATE_E state)
{
    conn_event_fifo_t * event_fifo = (conn_event_fifo_t * )k_malloc(sizeof(conn_event_fifo_t));
    assert(event_fifo != NULL && "event_fifo_t malloc failed");

    if (event_fifo) {
        event_fifo->bt_conn_ptr = conn;
        event_fifo->reason = reason;
        event_fifo->event = event;
        event_fifo->state = state;
        k_fifo_put(&bt_mode.fifo, event_fifo);
        air_daemon_wq_work_submit(&job_bt_mode_conn_event);
    }
    DBG_LOGI(thisMOD,"hid_scenario_bt_mode_conn_event_submit = %d", event);
}
/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
uint8_t hid_scenario_bt_mode_init()
{
    conn_info.ble_conn_handle = NULL;
    k_fifo_init(&bt_mode.fifo);
    return 0;
}

uint8_t hid_scenario_bt_mode_open( uint32_t link_idx, T_HID_SCENARIO_OPEN_TYPE_E parameter)
{
    if((bt_mode.state == MODE_OPEN_UNSPECIFIED) || (bt_mode.state == MODE_OPEN_SPECIFIED))
    {
        DBG_LOGI(thisMOD, "Repeat hid_scenario_bt_mode_open !");
        return 1;
    }

    uint8_t ret;
    bt_mode.repair = parameter;
    bt_mode.link_idx = link_idx;
    bt_mode.address_id = hid_scenario_adv_local_address_id_read(link_idx);
    DBG_LOGI(thisMOD, "hid_scenario_bt_mode_open link_idx = %d, repair = %d, address_id = %d" ,link_idx, bt_mode.repair, bt_mode.address_id);
    
    if(bt_mode.repair)
    {
        bt_mode.repair_address_id = hid_scenario_adv_get_unused_address_id();
        hid_scenario_adv_print_local_address(bt_mode.repair_address_id);
        DBG_LOGI(thisMOD, "repair address_id = %d" ,bt_mode.repair_address_id);
        ret = hid_scenario_undir_adv_start(HID_SCENARIO_BT_MODE, bt_mode.repair_address_id);
        if (ret == 0){
            bt_mode.state = MODE_OPEN_UNSPECIFIED;
            hid_scenario_send_state_update_notification(bt_mode.state, 0);
        }
    }
    else if(BT_mode_check_bonded())
    {
        hid_scenario_adv_print_local_address(bt_mode.address_id);
        DBG_LOGI(thisMOD,"check_bt_bonded with 0x%02X-%02X-%02X-%02X-%02X-%02X, type = %d"
            , conn_info.bond_addr.a.val[0]
            , conn_info.bond_addr.a.val[1]
            , conn_info.bond_addr.a.val[2]
            , conn_info.bond_addr.a.val[3]
            , conn_info.bond_addr.a.val[4]
            , conn_info.bond_addr.a.val[5]
            , conn_info.bond_addr.type
        );

        if(hid_scenario_bt_mode_bond_address_is_rpa())
        {
            ret = hid_scenario_filter_undir_adv_start(HID_SCENARIO_BT_MODE, &conn_info.bond_addr, bt_mode.address_id);
        }
        else
        {
            ret = hid_scenario_dir_adv_start(HID_SCENARIO_BT_MODE, &conn_info.bond_addr, bt_mode.address_id);
        }

        
        if (ret == 0){
            bt_mode.state = MODE_OPEN_SPECIFIED;
            hid_scenario_send_state_update_notification(bt_mode.state, 0);
        }
    }
    else
    {
        hid_scenario_adv_print_local_address(bt_mode.address_id);
        ret = hid_scenario_undir_adv_start(HID_SCENARIO_BT_MODE, bt_mode.address_id);
        if (ret == 0){
            bt_mode.state = MODE_OPEN_UNSPECIFIED;
            hid_scenario_send_state_update_notification(bt_mode.state, 0);
        }
    }

    #if defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER) && defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
    // game_controller_bt_mode_hw_trigger_enable();
    #endif
    return 0;
}

uint8_t hid_scenario_bt_mode_start(uint32_t link_idx, void* parameter)
{
    DBG_LOGI(thisMOD, "hid_scenario_bt_mode_start link_idx = %d" ,link_idx);

    if(bt_mode.state == MODE_STARTED)
    {
        return 1;
    }

    hid_common_set_hid_exp_flag(FLAG_BIT_BT_CONNECTED);
    
    if (bt_slave_latency_callback) {
        bt_slave_latency_callback(false);
    }

    if(bt_mode.state == MODE_STOPPED)
    {
        bt_mode.ble_retry_count = 0;
        BT_mode_connection_param_check();
    }
    
    hid_scenario_send_notification(SS_EVT_BT_REPORT_RATE_UPDATE, (uint8_t*)&bt_mode.rr, sizeof(bt_mode.rr));
    bt_mode.state = MODE_STARTED;
    hid_scenario_send_state_update_notification(bt_mode.state, 0);
    
    return 0;
}

uint8_t hid_scenario_bt_mode_stop(uint8_t parameter)
{
    DBG_LOGI(thisMOD, "hid_scenario_bt_mode_stop");

    hid_common_clear_hid_exp_flag(FLAG_BIT_BT_CONNECTED);

    if(parameter == SCENARIO_IDLE2_STOP)
    {
        bt_mode.ble_retry_count = 0;
        BT_mode_update_conn_slave_latency();
    }

    bt_mode.state = MODE_STOPPED;
    hid_scenario_send_state_update_notification(bt_mode.state, 0);
    return 0;
}

uint8_t hid_scenario_bt_mode_close(uint8_t parameter)
{
    DBG_LOGI(thisMOD, "hid_scenario_bt_mode_close");
    bt_mode.disconnect_by_local = false;
    
    if(bt_mode.state == MODE_CLOSED)
    {
        return 1;
    }

    hid_common_clear_hid_exp_flag(FLAG_BIT_BT_CONNECTED);
    hid_common_clear_hid_exp_flag(FLAG_BIT_BT_ENCRYPTED);
    hid_common_clear_hid_exp_flag(FLAG_BIT_ATT_NOTIFY_MOUSE_ENA);

    switch(bt_mode.state)
    {
        case MODE_OPEN_UNSPECIFIED:
        {
            #if defined(CONFIG_AIR_MUTIPLE_ADV_SUPPORT)
            hid_scenario_adv_stop_advertising_timer();
            #endif
        }
        case MODE_OPEN_SPECIFIED:
        {
            int err = hid_scenario_adv_stop();

            if(err)
            {
                DBG_LOGI(thisMOD, "hid_scenario_adv_stop err = %d", err);
            }
            else
            {
                /* When closing, if BT is connected, submit to daemon task.
                After connected, also send closed state to daemon to check if app state change notification is needed. */
                hid_scenario_bt_mode_conn_event_submit(conn_info.ble_conn_handle, 0, BT_MODE_STATE_CHANGE, MODE_CLOSED);
            }
        }
        break;
        
        case MODE_OPEN_CONNECTED:
        case MODE_STARTED:
        case MODE_STOPPED:
        {   
            BT_mode_disconnect_req();
        }
        break;         

        case MODE_CLOSED:
        {
        }
        break;

        default:
            break;

    }
    
    
    
    return 0;
}

uint8_t hid_scenario_bt_mode_config(T_HID_SCENARIO_CONFIG_PARA_S* config)
{
    DBG_LOGI(thisMOD, "hid_scenario_bt_mode_config bt_mode.state = %d", bt_mode.state);

    switch(config->cfg_type)
    {
        case SECNARIO_SRV_CONFIG_ID_ADDR_DELETE:
        {
            hid_scenario_adv_delete_id();
        }
        break;
        
        default:
        return 1;
        break;
    }
    return 0;
}

bool hid_scenario_bt_mode__bt_trigger_peripheral_hw(uint32_t enable)
{
    if (conn_info.ble_conn_handle){
        T_BT_TRIGGER_TYPE_S params;
        params.connection_handle = conn_info.ble_conn_handle->handle;
        params.TriggerType = TRIGGER_TYPE_SPI;

        if (enable){
            params.ActionMode = ACTION_MODE_RESUME;
        }
        else{
            params.ActionMode = ACTION_MODE_PAUSE;
        }

        DBG_LOGI(thisMOD, "hid_scenario_bt_mode__bt_trigger_peripheral_hw , enable = %d, connection_handle = 0x%X, ActionMode = %d"
            , enable
            , conn_info.ble_conn_handle
            , params.ActionMode
        );

        hid_vendor_set_peripheral_trigger(&params);
        return 0;
    }
    else{
        return -1;
    }
}

uint8_t hid_scenario_bt_mode__get_state()
{
    return bt_mode.state;
}

static void BT_mode_connected_cb(struct bt_conn *conn, uint8_t err)
{
    if(hid_scenario_get() == HID_SCENARIO_BT_MODE)
    {
        #if defined(CONFIG_AIR_MUTIPLE_ADV_SUPPORT)
        hid_scenario_adv_stop_advertising_timer();
        #endif
        if(err == BT_HCI_ERR_ADV_TIMEOUT)
        {
            k_work_submit(&job_dir_adv);
            DBG_LOGI(thisMOD,"Failed to dir adv connect, err(%u)\n",  err);
            return;
        }
        else if (err)
        {
            DBG_LOGI(thisMOD,"Failed to connect, err(%u)\n",  err);
            return;
        }

        if (bt_mode.state == MODE_OPEN_UNSPECIFIED || bt_mode.state == MODE_OPEN_SPECIFIED)
        {
            hid_scenario_bt_mode_conn_event_submit(conn, 0, BT_MODE_CONNECTED, bt_mode.state);
        }

        #if 0
        if (bt_conn_set_security(conn, BT_SECURITY_L2)) {
            printk("Failed to set security\n");
        }
        #endif
    }

    #if defined (AIR_SWLA_ENABLE)
    HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_app_bt_connecting, SWLA_DIRECTION_STOP);
    #endif    
}



static void BT_mode_disconnected_cb(struct bt_conn *conn, uint8_t reason)
{
    /* USB open workaround, remove check scenario */
    if (hid_scenario_get() == HID_SCENARIO_BT_MODE && bt_mode.state != MODE_CLOSED)
    {
        hid_scenario_bt_mode_conn_event_submit(conn, reason, BT_MODE_DISCONNECTED, bt_mode.state);
    }
}

static void BT_mode_conn_le_param_updated_cb(struct bt_conn *conn, uint16_t interval, uint16_t latency,
			     uint16_t timeout)
{
    hid_scenario_bt_mode_conn_event_submit(conn, 0, BT_MODE_CONN_PARA_UPDATED, bt_mode.state);
}

static void BT_mode_security_changed_cb(struct bt_conn *conn, bt_security_t level,
			     enum bt_security_err err)
{
    if (hid_scenario_get() == HID_SCENARIO_BT_MODE)
    {
        conn_event_fifo_t * event_fifo = (conn_event_fifo_t * )k_malloc(sizeof(conn_event_fifo_t));
        assert(event_fifo != NULL && "conn_event_fifo_t malloc failed");
        
        if (event_fifo) {
            event_fifo->bt_conn_ptr = conn;
            event_fifo->level = level;
            event_fifo->err = err;
            event_fifo->event = BT_MODE_SECURITY_CHANGED;
            k_fifo_put(&bt_mode.fifo, event_fifo);
            air_daemon_wq_work_submit(&job_bt_mode_conn_event);
        }
        DBG_LOGI(thisMOD,"BT_MODE_SECURITY_CHANGED submit !");
    }
}

void hid_scenario_bt_register_slave_latency_cb(hid_bt_scenario_slave_latency_cb callback) 
{
    bt_slave_latency_callback = callback;
}


BT_CONN_CB_DEFINE(conn_cbs_bt_conn) = {
	.connected = BT_mode_connected_cb,
	.disconnected = BT_mode_disconnected_cb,
    .le_param_updated = BT_mode_conn_le_param_updated_cb,
    .security_changed = BT_mode_security_changed_cb,
};

#endif