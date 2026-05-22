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

#ifndef __APP_DONGLE_CM_LE_SCANNER_H__
#define __APP_DONGLE_CM_LE_SCANNER_H__

#include "app_dongle_cm_config.h"

#ifdef __cplusplus
extern "C" {
#endif


#define APP_DONGLE_CM_LE_SCAN_DEFAULT_INTERVAL                  0x0640                    /* uint:0.625ms, 1000 ms */
#define APP_DONGLE_CM_LE_SCAN_DEFAULT_SCAN_WINDOW               0x0500                    /* uint:0.625ms, 800 ms */
//#define APP_DONGLE_CM_LE_SCAN_DEFAULT_SCAN_WINDOW               0x0600                    /* uint:0.625ms, 960 ms */



typedef enum {
    APP_DONGLE_CM_LE_SCANNER_USER_NONE                          = 0,
    APP_DONGLE_CM_LE_SCANNER_USER_CM,
    APP_DONGLE_CM_LE_SCANNER_USER_LE_HOGP,
    APP_DONGLE_CM_LE_SCANNER_USER_ULL_HID,
    APP_DONGLE_CM_LE_SCANNER_USER_MAX
} app_dongle_cm_le_scanner_user_id_t;

typedef enum {
    APP_DONGLE_CM_LE_SCANNER_SCAN_FULL                          = 0,
    APP_DONGLE_CM_LE_SCANNER_USER_WHITELIST,
} app_dongle_cm_le_scanner_scan_policy_t;

typedef enum {
    APP_DONGLE_CM_LE_SCANNER_WHITELIST_STATE_IDLE               = 0,
    APP_DONGLE_CM_LE_SCANNER_WHITELIST_STATE_ADD_ONGOING,
    APP_DONGLE_CM_LE_SCANNER_WHITELIST_STATE_REMOVE_ONGOING,
    APP_DONGLE_CM_LE_SCANNER_WHITELIST_STATE_CLEAR_ONGOING,
    APP_DONGLE_CM_LE_SCANNER_WHITELIST_STATE_COMPLETE,
} app_dongle_cm_le_scanner_whitelist_state_t;

typedef enum {
    APP_DONGLE_CM_LE_SCANNER_WHITELIST_ACTION_ADD               = 0,
    APP_DONGLE_CM_LE_SCANNER_WHITELIST_ACTION_REMOVE,
    APP_DONGLE_CM_LE_SCANNER_WHITELIST_ACTION_CLEAR
} app_dongle_cm_le_scanner_whitelist_action_t;

typedef enum {
    APP_DONGLE_CM_LE_SCANNER_STATE_IDLE               = 0,
    APP_DONGLE_CM_LE_SCANNER_STATE_WHITELIST_ONGOING,
    APP_DONGLE_CM_LE_SCANNER_STATE_STARTING,
    APP_DONGLE_CM_LE_SCANNER_STATE_STOPPING,
    APP_DONGLE_CM_LE_SCANNER_STATE_STARTED,
} app_dongle_cm_le_scanner_state_t;

typedef void (*app_dongle_cm_le_scanner_state_change_cb_t)(uint8_t old_state, uint8_t new_state);
typedef void (*app_dongle_cm_le_scanner_adv_report_cb_t)(uint8_t addr_type, uint8_t *addr, int8_t rssi,
                                                         uint8_t *adv_data, uint8_t adv_len,
                                                         uint8_t link_type, uint8_t device_type,
                                                         uint8_t *user_param);

typedef struct {
    app_dongle_cm_le_scanner_state_change_cb_t      state_change_cb;
    app_dongle_cm_le_scanner_adv_report_cb_t        adv_report_cb;
} PACKED app_dongle_cm_le_scanner_callback_t;

typedef struct {
    app_dongle_cm_le_scanner_scan_policy_t          scan_policy;
    uint8_t                                         scan_link_type_bit_mask;
    uint8_t                                         scan_device_type_bit_mask;

    uint16_t                                        scan_interval;
    uint16_t                                        scan_window;
    bool                                            duplicate_filter;
    uint32_t                                        timeout_ms;
} PACKED app_dongle_cm_le_scanner_scan_parameter_t;



void        app_dongle_cm_le_scanner_init(void);

bool        app_dongle_cm_le_scanner_register(uint8_t user_id, app_dongle_cm_le_scanner_callback_t callback, void *user_param);
bool        app_dongle_cm_le_scanner_unregister(uint8_t user_id);

bool        app_dongle_cm_le_scanner_whitelist_add_addr(uint8_t addr_type, uint8_t *addr);
bool        app_dongle_cm_le_scanner_whitelist_remove_addr(uint8_t addr_type, uint8_t *addr);
bool        app_dongle_cm_le_scanner_whitelist_clear_addr(void);
bool        app_dongle_cm_le_scanner_whitelist_operate(app_dongle_cm_le_scanner_whitelist_action_t action);

bool        app_dongle_cm_le_scanner_start_scan(uint8_t user_id, app_dongle_cm_le_scanner_scan_parameter_t scan_param);
bool        app_dongle_cm_le_scanner_stop_scan(uint8_t user_id);
uint8_t     app_dongle_cm_le_scanner_get_state(void);



#ifdef __cplusplus
}
#endif

#endif /* __APP_DONGLE_CM_LE_SCANNER_H__ */
