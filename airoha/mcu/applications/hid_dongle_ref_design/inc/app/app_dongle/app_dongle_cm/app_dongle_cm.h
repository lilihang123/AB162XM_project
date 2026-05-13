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

#ifndef __APP_DONGLE_CM_H__
#define __APP_DONGLE_CM_H__

#include "app_dongle_cm_config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    APP_DONGLE_CM_CONN_STATE_DISCONNECTED                        = 0,
    APP_DONGLE_CM_CONN_STATE_CONNECTING,
    APP_DONGLE_CM_CONN_STATE_CONNECTED,
    APP_DONGLE_CM_CONN_STATE_BONDED,
    APP_DONGLE_CM_CONN_STATE_DISCONNECTING,
} app_dongle_cm_conn_state_t;

typedef enum {
    APP_DONGLE_CM_CONN_EVENT_NONE                               = 0,
    APP_DONGLE_CM_CONN_EVENT_REQUEST_CONNECT,
    APP_DONGLE_CM_CONN_EVENT_REQUEST_DISCONNECT,
    APP_DONGLE_CM_CONN_EVENT_CONNECTED,
    APP_DONGLE_CM_CONN_EVENT_BONDED,
    APP_DONGLE_CM_CONN_EVENT_LINK_LOST,
    APP_DONGLE_CM_CONN_EVENT_DISCONNECTED,
} app_dongle_cm_conn_event_t;

typedef bool (*app_dongle_cm_interface_connect_all_t)(void);
typedef bool (*app_dongle_cm_interface_connect_t)(uint8_t addr_type, uint8_t *addr);
typedef bool (*app_dongle_cm_interface_disconnect_t)(uint8_t addr_type, uint8_t *addr);
typedef bool (*app_dongle_cm_interface_scan_t)(bool start_scan);
typedef void (*app_dongle_cm_interface_active_t)(uint8_t addr_type, uint8_t *addr);
typedef void (*app_dongle_cm_interface_inactive_t)(uint8_t addr_type, uint8_t *addr);

typedef struct {
    app_dongle_cm_interface_connect_all_t       connect_all_if;
    app_dongle_cm_interface_connect_t           connect_if;
    app_dongle_cm_interface_disconnect_t        disconnect_if;
    app_dongle_cm_interface_scan_t              scan_if;
    app_dongle_cm_interface_active_t            active_if;
    app_dongle_cm_interface_inactive_t          inactive_if;
} PACKED app_dongle_cm_interface_t;



void app_dongle_cm_init(void);

void app_dongle_cm_notify_conn_event(uint8_t link_type, app_dongle_cm_conn_event_t event, uint8_t addr_type, uint8_t *addr);

bool app_dongle_cm_add_found_addr(uint8_t link_type, uint8_t device_type, uint8_t addr_type, uint8_t *addr, bool connect);

void app_dongle_cm_register_link_interface(uint8_t link_type, app_dongle_cm_interface_t *interface);



#ifdef __cplusplus
}
#endif

#endif /* __APP_DONGLE_CM_H__ */
