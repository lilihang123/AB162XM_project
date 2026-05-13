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

#ifndef _APP_PURE_GAMING_DONGLE_SCENARIO_H_
#define _APP_PURE_GAMING_DONGLE_SCENARIO_H_

#if defined(AIR_PURE_GAMING_DONGLE_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "app_bt_conn_manager.h"
#include "af_events_declaration.h"
#include "bt_ull_le_hid_service.h"
#include "hid_critical_path.h"
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
typedef uint8_t app_pg_scenario_usb_status_t;
enum {
    APP_PG_USB_PLUGOUT,
    APP_PG_USB_PLUGIN,
    APP_PG_USB_READY,
    APP_PG_USB_SUSPEND,
    APP_PG_USB_RESUME,
};

typedef uint8_t app_pg_scenario_timer_status_t;
enum {
    APP_PG_TIMER_NOT_START,
    APP_PG_TIMER_WAITTING_STAGE,
    APP_PG_TIMER_IDLE_STAGE,
    APP_PG_TIMER_RECONNECT_STAGE,
};

typedef struct {
    uint16_t cur_dpi_x;
    uint16_t cur_dpi_y;
} app_pg_dpi_para_t;

typedef struct {
    bool bt_connected;
    bool scan_request;
    bool rr_changed_request;
    app_pg_scenario_usb_status_t usb_status;
    app_pg_scenario_timer_status_t usb_suspend_timer_status;
    uint16_t report_rate;
    uint32_t scan_timeout_ms;
    uint32_t usb_suspend_timer;
    app_bt_conn_handle_t *link_handle;
    app_bt_conn_handle_t *temp_link_handle;
    app_pg_dpi_para_t cur_dpi;
    uint8_t chargering_status;
    uint8_t battery_status_percent;
} app_pg_scenario_handle_t;

typedef uint8_t app_pg_scenario_config_cmd_t;
enum {
    APP_PG_CFG_CMD_USB_STATUS,
    APP_PG_CFG_CMD_BT_STATUS,
    APP_PG_CFG_CMD_BT_HANDLE_UPDATE,
    APP_PG_CFG_CMD_BT_HANDLE_QEURY,
    APP_PG_CFG_CMD_TEMP_BT_HANDLE_UPDATE,
    APP_PG_CFG_CMD_TEMP_BT_HANDLE_QEURY,
    APP_PG_CFG_CMD_BT_GET_BONDED_DEVICE_NUM,
    APP_PG_CFG_CMD_BT_GET_BONDED_DEVICE_ADDR,
    APP_PG_CFG_CMD_BT_GET_PAIRED_DEVICE_LIST,
    APP_PG_CFG_CMD_BT_GET_ULL_LINK_STATUS,
    APP_PG_CFG_CMD_BT_GET_ULL_LINK_ADDR,
    APP_PG_CFG_CMD_BT_REMOVE_ULL_LINK_RECORD,
    APP_PG_CFG_CMD_SET_SCENARIO,
    APP_PG_CFG_CMD_SET_REPORT_RATE,
    APP_PG_CFG_CMD_SET_REPORT_RATE_NVS_SETTING,
    APP_PG_CFG_CMD_SET_REPORT_RATE_CHANGE_REQUEST,
    APP_PG_CFG_CMD_GET_SCENARIO,
    APP_PG_CFG_CMD_GET_REPORT_RATE,
    APP_PG_CFG_CMD_GET_REPORT_RATE_NVS_SETTING,
    APP_PG_CFG_CMD_GET_REPORT_RATE_CHANGE_REQUEST,
    APP_PG_CFG_CMD_SET_SCAN_REQUEST,
    APP_PG_CFG_CMD_GET_SCAN_REQUEST,
    APP_PG_CFG_CMD_SET_DPI_PARA,
    APP_PG_CFG_CMD_GET_DPI_PARA,
    APP_PG_CFG_CMD_SET_CHARGERING_STATUS,
    APP_PG_CFG_CMD_GET_CHARGERING_STATUS,
    APP_PG_CFG_CMD_SET_BATTERY_STATUS,
    APP_PG_CFG_CMD_GET_BATTERY_STATUS,
};

typedef struct {
    uint8_t dev_cnt;
    bt_addr_le_t *list;
} app_pg_scenario_paired_list_param_t;

typedef struct {
    bool request;
    uint32_t timeout_ms;
} app_pg_scenario_scan_request_param_t;

typedef struct {
    bt_ull_le_hid_srv_app_scenario_t sceanrio_param;
    bt_ull_le_hid_srv_report_rate_t report_rate_param;
} app_pg_dongle_rr_scenario_param_t;

/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
extern void app_pure_gaming_dongle_scenario_init(void);
extern void app_pure_gaming_dongle_scenario_deinit(void);
extern int app_pure_gaming_dongle_scenario_open(app_pg_scenario_handle_t *scenario_handle);
extern int app_pure_gaming_dongle_scenario_start(app_pg_scenario_handle_t *scenario_handle);
extern int app_pure_gaming_dongle_scenario_stop(app_pg_scenario_handle_t *scenario_handle);
extern void app_pure_gaming_dongle_scenario_send_release_data(void);
extern int app_pure_gaming_dongle_scenario_close(app_pg_scenario_handle_t *scenario_handle);
extern int app_pure_gaming_dongle_scenario_set_config(app_pg_scenario_handle_t *scenario_handle, app_pg_scenario_config_cmd_t cmd, void *param);
extern int app_pure_gaming_dongle_scenario_get_config(app_pg_scenario_handle_t *scenario_handle, app_pg_scenario_config_cmd_t cmd, void *param);
extern app_pg_scenario_handle_t *app_pure_gaming_dongle_scenario_get_handle_by_link(app_bt_conn_handle_t *link_handle);
extern app_pg_scenario_handle_t *app_pure_gaming_dongle_scenario_get_handle_by_role(app_bt_conn_role_t role);
extern app_bt_conn_role_t app_pure_gaming_dongle_scenario_get_role_by_handle(app_pg_scenario_handle_t *scenario_handle);
extern int app_pure_gaming_dongle_scenario_entry_usb_suspend_case(app_pg_scenario_handle_t *scenario_handle);
extern int app_pure_gaming_dongle_scenario_usb_suspend_case_switch_to_idle(app_pg_scenario_handle_t *scenario_handle);
extern int app_pure_gaming_dongle_scenario_exit_usb_suspend_case(app_pg_scenario_handle_t *scenario_handle);
extern int app_pure_gaming_dongle_scenario_usb_status_update_by_evt(app_pg_scenario_handle_t *scenario_handle, T_EVT_CMD_E cmd);
extern app_pg_scenario_handle_t *app_pure_gaming_dongle_scenario_set_current_context(app_bt_conn_role_t role);
extern app_pg_scenario_handle_t *app_pure_gaming_dongle_scenario_get_current_context(void);
extern int app_pure_gaming_dongle_scenario_wakeup_pc(void);
int app_pure_gaming_dongle_scenario_suspend_timer_start(void);
int app_pure_gaming_dongle_scenario_suspend_timer_stop(void);
void app_pure_gaming_dongle_scenario_update_critical_device_infe(hid_critical_path_info_type_t device_info);

#if defined(CONFIG_AIR_HID_DISABLE_SOF_INTR)
void app_pure_gaming_dongle_scenario_disable_sof_intr(void);
#endif

#if defined(CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER)
void app_pure_gaming_dongle_scenario_register_auto_switch_callback(void);
void app_auto_switch_start(void);
void app_auto_switch_stop(void);
#endif/*CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER*/
#endif /* AIR_PURE_GAMING_DONGLE_ENABLE */

#endif /* _APP_PURE_GAMING_DONGLE_SCENARIO_H_ */
