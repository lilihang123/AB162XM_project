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

#ifndef _APP_CIS_CONN_H_
#define _APP_CIS_CONN_H_

#if defined(AIR_PURE_GAMING_DONGLE_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include "app_bt_conn_manager.h"
#include "bt_ull_le_hid_service.h"

/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
extern int app_bt_ull_set_output_report(bt_ull_le_hid_srv_set_output_report_t *param);
extern int app_bt_ull_connection_bond(app_bt_conn_handle_t *link_handle);
extern int app_bt_ull_connection_connect_device(app_bt_conn_handle_t *link_handle);
extern int app_bt_ull_connection_connect_service(app_bt_conn_handle_t *link_handle);
extern int app_bt_ull_connection_disconnect(app_bt_conn_handle_t *link_handle, uint8_t reason);
extern int app_bt_ull_connection_cancel(app_bt_conn_handle_t *link_handle);
extern int app_bt_ull_connection_set_scenario(app_bt_conn_handle_t *link_handle, bt_ull_le_hid_srv_app_scenario_t scenario);
extern int app_bt_ull_connection_set_report_rate(app_bt_conn_handle_t *link_handle, bt_ull_le_hid_srv_report_rate_t *report_rate);
extern int app_bt_ull_connection_remove_cig(app_bt_conn_handle_t *link_handle);
extern bt_ull_le_hid_srv_device_t app_bt_conn_manager_role_to_bt_type(app_bt_conn_role_t role);
extern uint8_t app_bt_ull_connection_get_bonded_device_num(app_bt_conn_role_t role);
extern void app_bt_ull_connection_get_bonded_device_addr(app_bt_conn_handle_t *link_handle, app_bt_conn_role_t role);
extern void app_bt_ull_connection_get_bonded_addr_list(app_bt_conn_role_t role, uint8_t count, bt_addr_le_t *list);
extern void app_bt_ull_connection_remove_bonded_addr_list(app_bt_conn_handle_t *link_handle, app_bt_conn_role_t role);
extern int app_bt_ull_connection_init(void);
#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
extern int app_bt_ull_connection_connect_device_suspend(app_bt_conn_handle_t *link_handle);
extern int app_bt_ull_connection_disconnect_suspend(app_bt_conn_handle_t *link_handle);
#endif /*CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE*/
#endif /* AIR_PURE_GAMING_DONGLE_ENABLE */

#endif /* _APP_CIS_CONN_H_ */
