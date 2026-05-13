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

#if defined(AIR_PURE_GAMING_DONGLE_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <string.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include "app_bt_ull_conn.h"
#include "bt_ull_le_hid_service.h"
#include "app_bt_conn_manager.h"
#include <errno.h>
#include "assert.h"
#include "af_events_declaration.h"
#include "app_events.h"
#include "hal_gpt.h"
#include "hal_gpt_internal.h"
#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)
#include "custom_protocol.h"
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE */
#include "app_pure_gaming_dongle_scenario.h"

#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
#include "app_state.h"
#endif/*CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE*/

/* Private define ------------------------------------------------------------*/
#define thisMODULE app_bt_ull
#define thisMOD    "app_bt_ull"
LOG_MODULE_REGISTER(thisMODULE);

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static app_bt_conn_handle_t *remove_cig_link_handle = NULL;
static app_bt_conn_handle_t *change_report_rate_link_handle = NULL;
static uint32_t app_events_ull_service_timer = 0;
extern bool g_usb_entry_suspend_flag;

/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
int parse_data(void *param, uint32_t param_len)
{
    int i;
    uint8_t *data = (uint8_t *)param;

    for(i=0;i<(param_len);i++)
    {
        LOG_INF("[parse_data] data[%d]=%x",i,data[i]);
    }

    for(i=0;i<(param_len-3);i++)
    {
        if(data[i] == 0x19)
        {
            if(data[i+1] == 0x02 && data[i+2] == 0x32 && data[i+3] == 0x00)
            {
                LOG_INF("[app_hid_dongle] %x %x %x %x found",data[i],data[i+1],data[i+2],data[i+3]);
                return 0;
            }
        }

        if(data[i] == 0x19)
        {
            if(data[i+1] == 0x02 && data[i+2] == 0xfe && data[i+3] == 0xfe)
            {
                LOG_INF("[app_hid_dongle] %x %x %x %x found",data[i],data[i+1],data[i+2],data[i+3]);
                return -1;
            }
        }
    }
    return -1;
}
#endif/*CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE*/

static void app_bt_ull_event_callback(bt_ull_event_t event, void *param, uint32_t param_len)
{
    app_bt_conn_handle_t *link_handle = NULL;

    LOG_INF("[app_hid_dongle] ULL Connection Event 0x%x", event);

    switch (event)
    {
        case BT_ULL_EVENT_LE_HID_BONDING_COMPLETE_IND:
            bt_ull_le_hid_srv_bonding_complete_ind_t *bond_ind = (bt_ull_le_hid_srv_bonding_complete_ind_t *)param;
            /* find link */
            link_handle = app_bt_conn_manager_query_handle_by_conn(APP_BT_CONN_TYPE_ACL, bond_ind->conn);
            assert(link_handle != NULL);
            /* process event */
            if (bond_ind->status == 0)
            {
                /* update link info into link handle */
                app_bt_conn_manager_set_handle_addr(link_handle, APP_BT_CONN_TYPE_ULL, &(bond_ind->peer_addr));
                link_handle->ull_status = APP_BT_CONN_STATUS_BONDED;
                /* send event to do next step */
                app_events_send(EVT_CMD_ULL_BOND_SUCCESS, link_handle->scenario_handle);
                LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x bond success.", link_handle);
            }
            else
            {
                /* send event to do next step */
                app_events_send(EVT_CMD_ULL_BOND_FAIL, link_handle->scenario_handle);
                LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x bond failed, status = %d.", link_handle, bond_ind->status);
            }
            break;

        case BT_ULL_EVENT_LE_HID_CONNECTED_IND:
            bt_ull_le_hid_srv_connected_ind_t *connection_complete = (bt_ull_le_hid_srv_connected_ind_t *)param;
            /* process event */
            if (connection_complete->status == 0)
            {
                /* find link */
                link_handle = app_bt_conn_manager_query_handle_by_addr(APP_BT_CONN_TYPE_ULL, &(connection_complete->peer_addr));
                assert(link_handle != NULL);
                /* update link info into link handle */
                app_bt_conn_manager_set_handle_conn(link_handle, APP_BT_CONN_TYPE_ULL, connection_complete->conn);
                link_handle->ull_status = APP_BT_CONN_STATUS_CONNECTTED;
                /* connect service */
                app_bt_ull_connection_connect_service(link_handle);
                /* send event to do next step */
                app_pure_gaming_dongle_scenario_start(link_handle->scenario_handle);
                app_events_send(EVT_CMD_ULL_CONN_SUCCESS, link_handle->scenario_handle);
                LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x connect success.", link_handle);
            }else if(connection_complete->status == BT_HCI_ERR_ADV_TIMEOUT)
            {
                /* find link */
                link_handle = app_bt_conn_manager_query_handle_by_addr(APP_BT_CONN_TYPE_ULL, &(connection_complete->peer_addr));
                assert(link_handle != NULL);
                /* send event to do next step */
                app_events_send(EVT_CMD_RECONNECT_TIMEOUT, link_handle->scenario_handle);
                LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x connect timeout.", link_handle);
            }
            else if (connection_complete->status == BT_HCI_ERR_LOCALHOST_TERM_CONN)
            {
                /* find link */
#if defined(AIR_PURE_GAMING_DONGLE_MS_ENABLE)
                if (connection_complete->device_type == BT_ULL_LE_HID_SRV_DEVICE_MOUSE)
                {
                    link_handle = app_bt_conn_manager_query_handle_by_role(APP_BT_CONN_ROLE_MOUSE);
                }
#elif defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
                if (connection_complete->device_type == BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD)
                {
                    link_handle = app_bt_conn_manager_query_handle_by_role(APP_BT_CONN_ROLE_GAMEPAD);
                }
#else
                if (connection_complete->device_type == BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD)
                {
                    link_handle = app_bt_conn_manager_query_handle_by_role(APP_BT_CONN_ROLE_KEYBOARD);
                }
#endif /* AIR_PURE_GAMING_DONGLE_MS_ENABLE */
                assert(link_handle != NULL);
                link_handle->ull_status = APP_BT_CONN_STATUS_DISCONNECTED;
                /* send event to do next step */
                app_events_send(EVT_CMD_RECONNECT_CANCEL_SUCCESS, link_handle->scenario_handle);
                LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x cancel success.", link_handle);
            }
            else
            {
                /* find link */
#if defined(AIR_PURE_GAMING_DONGLE_MS_ENABLE)
                if (connection_complete->device_type == BT_ULL_LE_HID_SRV_DEVICE_MOUSE)
                {
                    link_handle = app_bt_conn_manager_query_handle_by_role(APP_BT_CONN_ROLE_MOUSE);
                }
#elif defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
                if (connection_complete->device_type == BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD)
                {
                    link_handle = app_bt_conn_manager_query_handle_by_role(APP_BT_CONN_ROLE_GAMEPAD);
                }
#else
                if (connection_complete->device_type == BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD)
                {
                    link_handle = app_bt_conn_manager_query_handle_by_role(APP_BT_CONN_ROLE_KEYBOARD);
                }
#endif /* AIR_PURE_GAMING_DONGLE_MS_ENABLE */
                assert(link_handle != NULL);
                link_handle->ull_status = APP_BT_CONN_STATUS_DISCONNECTED;
                /* send event to do next step */
                app_events_send(EVT_CMD_ULL_CONN_FAIL, link_handle->scenario_handle);
                LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x connect failed, status = %d.", link_handle, connection_complete->status);
            }
            break;

        case BT_ULL_EVENT_LE_HID_SERVICE_CONNECTED_IND:
            bt_ull_le_hid_srv_service_connected_ind_t *srv_connect_complete = (bt_ull_le_hid_srv_service_connected_ind_t *)param;
            /* find link */
            link_handle = app_bt_conn_manager_query_handle_by_conn(APP_BT_CONN_TYPE_ULL, srv_connect_complete->conn);
            assert(link_handle != NULL);

            if (app_events_ull_service_timer != 0)
            {
                hal_gpt_sw_stop_timer_ms(app_events_ull_service_timer);
            }

            /* process event */
            if (srv_connect_complete->status == 0)
            {
                if (link_handle->ull_status == APP_BT_CONN_STATUS_CONNECTTED)
                {
                    /* update link info into link handle */
                    link_handle->ull_status = APP_BT_CONN_STATUS_SERVICE_CONNECTTED;
                    /* send event to do next step */
                    /* TODO: Temp Solution, sometime connect service is not ready */
                    // app_events_send(EVT_CMD_ULL_SERVICE_CONN_SUCCESS, link_handle->scenario_handle);
                    LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x connect service success.", link_handle);
                }
                else
                {
                    LOG_ERR("[app_hid_dongle] ULL Connection handle 0x%x connect service error, status = %u.", link_handle, link_handle->ull_status);
                }
            }
            else
            {
                /* send event to do next step */
                /* TODO: Temp Solution, sometime connect service is not ready */
                // app_events_send(EVT_CMD_ULL_SERVICE_CONN_FAIL, link_handle->scenario_handle);
                LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x connect service failed, status = %d.", link_handle, srv_connect_complete->status);
            }
            break;

        case BT_ULL_EVENT_LE_HID_DISCONNECTED_IND:
            bt_ull_le_hid_srv_disconnected_ind_t *dis = (bt_ull_le_hid_srv_disconnected_ind_t *)param;

            if (app_events_ull_service_timer != 0)
            {
                hal_gpt_sw_stop_timer_ms(app_events_ull_service_timer);
            }

            /* find link */
            link_handle = app_bt_conn_manager_query_handle_by_conn(APP_BT_CONN_TYPE_ULL, dis->conn);
            // assert(link_handle != NULL);
            if (link_handle == NULL)
            {
                LOG_INF("[app_hid_dongle] ULL Service disconnect Error handle is NULL");
                break;
            }
            /* process event */
            if (dis->status == 0)
            {
                /* update link info into link handle */
                link_handle->ull_status = APP_BT_CONN_STATUS_DISCONNECTED;
                /* send event to do next step */
                if (dis->reason == BT_HCI_ERR_LOCALHOST_TERM_CONN)
                {
                    app_events_send(EVT_CMD_ULL_DISC_SUCCESS, link_handle->scenario_handle);
                    LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x disconnect success.", link_handle);
                }
                else
                {
                    app_events_send(EVT_CMD_DISCONNECT_BY_TARGET, link_handle->scenario_handle);
                    LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x disconnect happens, reason = 0x%x.", link_handle, dis->reason);
                }
            }
            else
            {
                /* send event to do next step */
                app_events_send(EVT_CMD_ULL_DISC_FAIL, link_handle->scenario_handle);
                LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x disconnect failed, status = %d.", link_handle, dis->status);
            }
            // app_pure_gaming_dongle_scenario_stop(link_handle->scenario_handle);
            app_pure_gaming_dongle_scenario_send_release_data();
            break;

#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)
        case BT_ULL_EVENT_USER_DATA_IND:
            bt_ull_user_data_t *user_data = (bt_ull_user_data_t *)param;
            if (user_data != NULL)
            {
                epio_bt_hid_recv_data(&user_data->remote_address, user_data->user_data_length, user_data->user_data);
            }
            break;
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE */

        case BT_ULL_EVENT_LE_HID_CIG_REMOVED:
            bt_ull_le_hid_srv_cig_removed_ind_t *remove_cig_ind = (bt_ull_le_hid_srv_cig_removed_ind_t *)param;
            if (remove_cig_ind->status == 0)
            {
                app_events_send(EVT_CMD_REMOVE_CIG_SUCCESS, remove_cig_link_handle->scenario_handle);
                LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x remove cig success.", remove_cig_link_handle);
            }
            else
            {
                app_events_send(EVT_CMD_REMOVE_CIG_FAIL, remove_cig_link_handle->scenario_handle);
                LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x remove cig fail, status = %d .", remove_cig_link_handle, remove_cig_ind->status);
            }
            break;

        case BT_ULL_EVENT_LE_HID_REPORT_RATE_CHANGE_IND:
            LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x report rate changed.", change_report_rate_link_handle);
            if (change_report_rate_link_handle != NULL)
            {
                app_events_send(EVT_CMD_REPORT_RATE_CHANGE_REQ, change_report_rate_link_handle->scenario_handle);
                change_report_rate_link_handle = NULL;
            }
            break;

        case BT_ULL_EVENT_LE_HID_CIS_ADV_REPORT_IND:
            #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
            LOG_INF("[app_hid_dongle] BT_ULL_EVENT_LE_HID_CIS_ADV_REPORT_IND");
            link_handle = app_bt_conn_manager_query_handle_by_role(APP_BT_CONN_ROLE_GAMEPAD);
            if(!g_usb_entry_suspend_flag)
            {
                app_state_change(APP_STATE_RECONNECT, REASON_AUTO);
                app_events_send(EVT_CMD_RECONNECT_REQ, link_handle->scenario_handle);
                LOG_INF("[app_hid_dongle] BT_ULL_EVENT_LE_HID_CIS_ADV_REPORT_IND-->pc resume ,reconnect");
            }else
            {
                /*parse data*/
                LOG_INF("[app_hid_dongle] BT_ULL_EVENT_LE_HID_CIS_ADV_REPORT_IND-->parse");
                int parse_ret = parse_data(param,param_len);
                if(parse_ret == 0)
                {
                    LOG_INF("[app_hid_dongle] BT_ULL_EVENT_LE_HID_CIS_ADV_REPORT_IND-->0x325");
                    app_events_send(EVT_CMD_CIS_SCAN_DEVICE_FOUND,link_handle->scenario_handle);
                }
            }
            #endif/*CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE*/
            break;

        default:
            break;
    }
}

/* Public functions ----------------------------------------------------------*/
int app_bt_ull_set_output_report(bt_ull_le_hid_srv_set_output_report_t *param)
{
    int err;

    // LOG_INF("app_bt_ull_set_output_report , len = %u, data = 0x%08x 0x%08x ...",param->size, *((uint32_t *)(&(param->data[0]))), *((uint32_t *)(&(param->data[0]))+1));

    err = bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_SET_OUTPUT_REPORT, (const void *)(param), sizeof(bt_ull_le_hid_srv_set_output_report_t));
    if (err)
    {
        LOG_INF("[app_hid_dongle] set output report failed, err = %d.", err);
    }
    else
    {
        LOG_INF("[app_hid_dongle] set output report.success.");
    }

    k_free(param->data);
    k_free(param);

    return err;
}

int app_bt_ull_connection_bond(app_bt_conn_handle_t *link_handle)
{
    int err;
    bt_ull_le_hid_srv_bond_t param;

    // LOG_INF("[app_hid_dongle] ULL Connection bond start.");

    param.conn = link_handle->acl_conn;
    err = bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_BOND, (const void *)(&param), sizeof(bt_ull_le_hid_srv_bond_t));
    if (err)
    {
        LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x bond start failed, err = %d.", link_handle, err);
    }
    else
    {
        LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x bond start.", link_handle);
    }

    return err;
}

int app_bt_ull_connection_connect_device(app_bt_conn_handle_t *link_handle)
{
    int err;
    bt_ull_le_hid_srv_connect_t param;
    memset(&param, 0, sizeof(bt_ull_le_hid_srv_connect_t));

    // LOG_INF("[app_hid_dongle] ULL Connection connect device start.");

#if defined(AIR_PURE_GAMING_DONGLE_MS_ENABLE)
    if (link_handle->role == APP_BT_CONN_ROLE_MOUSE)
    {
        param.mouse = (bt_ull_le_hid_srv_conn_params_t *)app_bt_conn_manager_malloc(sizeof(bt_ull_le_hid_srv_conn_params_t)+1*sizeof(bt_addr_le_t)-1);
        param.mouse->device_type = BT_ULL_LE_HID_SRV_DEVICE_MOUSE;
        param.mouse->list_num = 1;
        memcpy((void *)(param.mouse->peer_addr_list), (const void *)(&(link_handle->ull_addr)), sizeof(bt_addr_le_t));
    }
#elif defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
    if (link_handle->role == APP_BT_CONN_ROLE_GAMEPAD)
    {
        param.gamepad = (bt_ull_le_hid_srv_conn_params_t *)app_bt_conn_manager_malloc(sizeof(bt_ull_le_hid_srv_conn_params_t)+1*sizeof(bt_addr_le_t)-1);
        param.gamepad->device_type = BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD;
        param.gamepad->list_num = 1;
        memcpy((void *)(param.gamepad->peer_addr_list), (const void *)(&(link_handle->ull_addr)), sizeof(bt_addr_le_t));
    }
#else
    if (link_handle->role == APP_BT_CONN_ROLE_KEYBOARD)
    {
        param.keyboard= (bt_ull_le_hid_srv_conn_params_t *)app_bt_conn_manager_malloc(sizeof(bt_ull_le_hid_srv_conn_params_t)+1*sizeof(bt_addr_le_t)-1);
        param.keyboard->device_type = BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD;
        param.keyboard->list_num = 1;
        memcpy((void *)(param.keyboard->peer_addr_list), (const void *)(&(link_handle->ull_addr)), sizeof(bt_addr_le_t));
    }
#endif /* AIR_PURE_GAMING_DONGLE_MS_ENABLE */
    else
    {
        LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x device type is not supported (%d).", link_handle, link_handle->role);
        err = -EPERM;
        assert(0);
        return err;
    }

    app_bt_conn_status_t ull_service_backup;
    ull_service_backup = link_handle->ull_status;
    link_handle->ull_status = APP_BT_CONN_STATUS_CONNCETING;
    err = bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_CONNECT, (const void *)(&param), sizeof(bt_ull_le_hid_srv_connect_service_t));
    if (err >= 0)
    {
        LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x connect start.", link_handle);
    }
    else
    {
        link_handle->ull_status = ull_service_backup;
        LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x connect start failed, err = %d.", link_handle, err);
    }

#if defined(AIR_PURE_GAMING_DONGLE_MS_ENABLE)
    if (link_handle->role == APP_BT_CONN_ROLE_MOUSE)
    {
        app_bt_conn_manager_free(param.mouse);
    }
#elif defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
    if (link_handle->role == APP_BT_CONN_ROLE_GAMEPAD)
    {
        app_bt_conn_manager_free(param.gamepad);
    }
#else
    if (link_handle->role == APP_BT_CONN_ROLE_KEYBOARD)
    {
        app_bt_conn_manager_free(param.keyboard);
    }
#endif /* AIR_PURE_GAMING_DONGLE_MS_ENABLE */

    return err;
}

#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
int app_bt_ull_connection_connect_device_suspend(app_bt_conn_handle_t *link_handle)
{
    int err;
    bt_ull_le_hid_srv_enable_cis_scan_t param;
    memset(&param, 0, sizeof(bt_ull_le_hid_srv_enable_cis_scan_t));

    #if defined(AIR_PURE_GAMING_DONGLE_MS_ENABLE)
        if (link_handle->role == APP_BT_CONN_ROLE_MOUSE)
        {
            param.device_type = BT_ULL_LE_HID_SRV_DEVICE_MOUSE;
        }
    #elif defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
        if (link_handle->role == APP_BT_CONN_ROLE_GAMEPAD)
        {
            param.device_type = BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD;
        }
    #else
        if (link_handle->role == APP_BT_CONN_ROLE_KEYBOARD)
        {
            param.device_type = BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD;
        }
    #endif /* AIR_PURE_GAMING_DONGLE_MS_ENABLE */
        else
        {
            LOG_INF("[app_hid_dongle] ULL Connection_suspend handle 0x%x device type is not supported (%d).", link_handle, link_handle->role);
            err = -EPERM;
            assert(0);
            return err;
        }

    param.enable = 1;
    param.address = link_handle->ull_addr;
    param.scan_interval = 800;//for 800*0.625=500ms
    param.scan_window = 200;//200*0.625=125ms

    err = bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_ENABLE_CIS_SCAN, (const void *)(&param), sizeof(bt_ull_le_hid_srv_enable_cis_scan_t));
    if (err >= 0)
    {
        LOG_INF("[app_hid_dongle] ULL Connection_suspend handle 0x%x connect start.", link_handle);
    }
    else
    {
        LOG_INF("[app_hid_dongle] ULL Connection_suspend handle 0x%x connect start failed, err = %d.", link_handle, err);
    }

    return err;
}

int app_bt_ull_connection_disconnect_suspend(app_bt_conn_handle_t *link_handle)
{
    int err;
    bt_ull_le_hid_srv_enable_cis_scan_t param;
    memset(&param, 0, sizeof(bt_ull_le_hid_srv_enable_cis_scan_t));

    #if defined(AIR_PURE_GAMING_DONGLE_MS_ENABLE)
        if (link_handle->role == APP_BT_CONN_ROLE_MOUSE)
        {
            param.device_type = BT_ULL_LE_HID_SRV_DEVICE_MOUSE;
        }
    #elif defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
        if (link_handle->role == APP_BT_CONN_ROLE_GAMEPAD)
        {
            param.device_type = BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD;
        }
    #else
        if (link_handle->role == APP_BT_CONN_ROLE_KEYBOARD)
        {
            param.device_type = BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD;
        }
    #endif /* AIR_PURE_GAMING_DONGLE_MS_ENABLE */
        else
        {
            LOG_INF("[app_hid_dongle] ULL Connection_suspend handle 0x%x device type is not supported (%d).", link_handle, link_handle->role);
            err = -EPERM;
            assert(0);
            return err;
        }

    param.enable = 0;
    param.address = link_handle->ull_addr;
    param.scan_interval = 800;//for 800*0.625=500ms
    param.scan_window = 200;//200*0.625=125ms

    err = bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_ENABLE_CIS_SCAN, (const void *)(&param), sizeof(bt_ull_le_hid_srv_enable_cis_scan_t));
    if (err >= 0)
    {
        LOG_INF("[app_hid_dongle] ULL Connection_suspend handle 0x%x disconnect start.", link_handle);
    }
    else
    {
        LOG_INF("[app_hid_dongle] ULL Connection_suspend handle 0x%x disconnect start failed, err = %d.", link_handle, err);
    }

    return err;
}
#endif/*CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE*/

static void app_events_ull_service_timer_cb(void *user_data)
{
    LOG_INF("[app_hid_dongle] app_events_ull_service_timer_cb:5s not ready-> trigger assert");
    assert(0);
}

int app_bt_ull_connection_connect_service(app_bt_conn_handle_t *link_handle)
{
    int err;
    bt_ull_le_hid_srv_connect_service_t param;

    // LOG_INF("[app_hid_dongle] ULL Connection connect service start.");
    if (app_events_ull_service_timer == 0)
    {
        hal_gpt_sw_get_timer(&app_events_ull_service_timer);
    }
    hal_gpt_sw_stop_timer_ms(app_events_ull_service_timer);
    if(HAL_GPT_STATUS_OK != hal_gpt_sw_start_timer_ms(app_events_ull_service_timer, 5000, app_events_ull_service_timer_cb, NULL))
    {
        assert(0);
    }

    param.conn = link_handle->ull_conn;
    err = bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_CONNECT_SERVICE, (const void *)(&param), sizeof(bt_ull_le_hid_srv_connect_service_t));
    if (err)
    {
        if (app_events_ull_service_timer != 0)
        {
            hal_gpt_sw_stop_timer_ms(app_events_ull_service_timer);
        }
        LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x connect service start failed, err = %d.", link_handle, err);
    }
    else
    {
        LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x connect service start.", link_handle);
    }

    return err;
}

int app_bt_ull_connection_disconnect(app_bt_conn_handle_t *link_handle, uint8_t reason)
{
    int err;
    bt_ull_le_hid_srv_disconnect_t param;

    // LOG_INF("[app_hid_dongle] ULL Connection disconnect start.");
    if (app_events_ull_service_timer != 0)
    {
        hal_gpt_sw_stop_timer_ms(app_events_ull_service_timer);
    }
    param.conn = link_handle->ull_conn;
    param.reason = reason;
    err = bt_ull_le_hid_srv_action( BT_ULL_ACTION_LE_HID_DISCONNECT , (const void *)(&param), sizeof(bt_ull_le_hid_srv_disconnect_t));
    if (err)
    {
        LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x disconnect start failed, err = %d.", link_handle, err);
    }
    else
    {
        LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x disconnect start.", link_handle);
    }

    return err;
}

int app_bt_ull_connection_cancel(app_bt_conn_handle_t *link_handle)
{
    int err;
    bt_ull_le_hid_srv_cancel_connect_t param;

    // LOG_INF("[app_hid_dongle] ULL Connection cancel start.");
    if (app_events_ull_service_timer != 0)
    {
        hal_gpt_sw_stop_timer_ms(app_events_ull_service_timer);
    }
#if defined(AIR_PURE_GAMING_DONGLE_MS_ENABLE)
    if (link_handle->role == APP_BT_CONN_ROLE_MOUSE)
    {
        param.device_type = BT_ULL_LE_HID_SRV_DEVICE_MOUSE;
    }
#elif defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
    if (link_handle->role == APP_BT_CONN_ROLE_GAMEPAD)
    {
        param.device_type = BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD;
    }
#else
    if (link_handle->role == APP_BT_CONN_ROLE_KEYBOARD)
    {
        param.device_type = BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD;
    }
#endif /* AIR_PURE_GAMING_DONGLE_MS_ENABLE */
    else
    {
        LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x cancel device type is not supported (%d).", link_handle, link_handle->role);
        err = -EPERM;
        assert(0);
        return err;
    }
    err = bt_ull_le_hid_srv_action( BT_ULL_ACTION_LE_HID_CANCEL_CONNECT, (const void *)(&param), sizeof(bt_ull_le_hid_srv_cancel_connect_t));
    if (err)
    {
        LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x cancel start failed, err = %d.", link_handle, err);
    }
    else
    {
        LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x cancel start.", link_handle);
    }

    return err;
}

int app_bt_ull_connection_set_scenario(app_bt_conn_handle_t *link_handle, bt_ull_le_hid_srv_app_scenario_t scenario)
{
    int err;
    bt_ull_le_hid_srv_app_scenario_t param;

    // LOG_INF("[app_hid_dongle] ULL Connection set scenario start.");

    param = scenario;
    err = bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_SET_SCENARIO, (const void *)(&param), sizeof(bt_ull_le_hid_srv_app_scenario_t));
    if (err < 0)
    {
        LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x set scenario 0x%x start failed, err = %d.", link_handle, scenario, err);
    }
    else
    {
        LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x set scenario 0x%x start success, err = %d..", link_handle, scenario, err);
        err = 0;
    }

    return err;
}

int app_bt_ull_connection_set_report_rate(app_bt_conn_handle_t *link_handle, bt_ull_le_hid_srv_report_rate_t *report_rate)
{
    int err;

    change_report_rate_link_handle = link_handle;
    err = bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_SET_REPORT_RATE, (const void *)(report_rate), sizeof(bt_ull_le_hid_srv_report_rate_t));
    if (err < 0)
    {
        LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x set report rate 0x%x (phy:0x%x) start failed, err = %d.", link_handle, report_rate->rr_level, report_rate->phy, err);
    }
    else
    {
        LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x set report rate 0x%x (phy:0x%x) start success, err = %d.", link_handle, report_rate->rr_level, report_rate->phy, err);
        err = 0;
    }

    return err;
}

int app_bt_ull_connection_remove_cig(app_bt_conn_handle_t *link_handle)
{
    int err;

    remove_cig_link_handle = link_handle;
    err = bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_REMOVE_CIG, NULL, 0);
    if (err < 0)
    {
        LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x remove cig start failed, err = %d.", link_handle, err);
    }
    else
    {
        LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x remove cig start success, err = %d.", link_handle, err);
    }

    return err;
}

bt_ull_le_hid_srv_device_t app_bt_conn_manager_role_to_bt_type(app_bt_conn_role_t role)
{
    bt_ull_le_hid_srv_device_t device_type;

    switch (role)
    {
        case APP_BT_CONN_ROLE_MOUSE:
            device_type = BT_ULL_LE_HID_SRV_DEVICE_MOUSE;
            break;

        case APP_BT_CONN_ROLE_KEYBOARD:
            device_type = BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD;
            break;

        case APP_BT_CONN_ROLE_HEADSET:
            device_type = BT_ULL_LE_HID_SRV_DEVICE_HEADSET;
            break;

        case APP_BT_CONN_ROLE_GAMEPAD:
            device_type = BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD;
            break;

        default:
            device_type = BT_ULL_LE_HID_SRV_DEVICE_NONE;
            break;
    }

    return device_type;
}

uint8_t app_bt_ull_connection_get_bonded_device_num(app_bt_conn_role_t role)
{
    uint8_t count = 0;
    bt_ull_le_hid_srv_device_t device_type = app_bt_conn_manager_role_to_bt_type(role);

    count = bt_ull_le_hid_srv_get_bonded_device_num(device_type);
    return count;
}

void app_bt_ull_connection_get_bonded_device_addr(app_bt_conn_handle_t *link_handle, app_bt_conn_role_t role)
{
    bt_ull_le_hid_srv_device_t device_type = app_bt_conn_manager_role_to_bt_type(role);

    // LOG_INF("[app_hid_dongle] ULL Connection get bonded device addr start.");
    bt_ull_le_hid_srv_get_bonded_device_list(device_type, 1, &(link_handle->ull_addr));
    link_handle->ull_status = APP_BT_CONN_STATUS_BONDED;
    LOG_INF("[app_hid_dongle] ULL Connection handle 0x%x role %u get bonded device addr success.", link_handle, role);
}

void app_bt_ull_connection_get_bonded_addr_list(app_bt_conn_role_t role, uint8_t count, bt_addr_le_t *list)
{
    bt_ull_le_hid_srv_device_t device_type = app_bt_conn_manager_role_to_bt_type(role);

    // LOG_INF("[app_hid_dongle] ULL Connection get bonded addr list start.");
    bt_ull_le_hid_srv_get_bonded_device_list(device_type, count, list);
    LOG_INF("[app_hid_dongle] ULL Connection get bonded addr list done, role %u, count %u.", role, count);
}

void app_bt_ull_connection_remove_bonded_addr_list(app_bt_conn_handle_t *link_handle, app_bt_conn_role_t role)
{
    int ret;
    bt_ull_le_hid_srv_device_t device_type = app_bt_conn_manager_role_to_bt_type(role);

    // LOG_INF("[app_hid_dongle] ULL Connection remove bonded addr list start.");
    ret = bt_ull_le_hid_srv_clear_bonded_list(device_type);
    // link_handle->ull_status = APP_BT_CONN_STATUS_UNKNOWN;
    LOG_INF("[app_hid_dongle] ULL Connection remove bonded addr list done, role %u, ret %d.", role, ret);
}

int app_bt_ull_connection_init(void)
{
    int err;

    LOG_INF("[app_hid_dongle] ULL Connection init start.");

    err = bt_ull_le_hid_srv_init(BT_ULL_ROLE_SERVER, app_bt_ull_event_callback);
    if (err) {
        LOG_INF("[app_hid_dongle] ULL LE HID init, err = %d", err);
        return err;
    }

    LOG_INF("[app_hid_dongle] ULL Connection init done.");

    return err;
}

#endif /* AIR_PURE_GAMING_DONGLE_ENABLE */
