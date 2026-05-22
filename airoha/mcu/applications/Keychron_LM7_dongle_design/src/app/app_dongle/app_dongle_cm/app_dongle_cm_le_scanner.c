
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

#include "app_dongle_cm_le_scanner.h"

#include "app_bt_service_le_scanner.h"

#include "app_debug.h"
#include "app_dongle_event.h"
#include "app_porting.h"



/**================================================================================*/
/**                              Definition & Structure                            */
/**================================================================================*/
#define LOG_TAG             "[APP_DONGLE][CM][LE_SCANNER]"

typedef struct {
    app_dongle_cm_le_scanner_callback_t                     callback;
    void                                                   *user_param;
} PACKED app_dongle_cm_le_scanner_user_info_t;

typedef struct {
    uint8_t                                                 user_id;
    bool                                                    start_scan;
    app_dongle_cm_le_scanner_scan_parameter_t               scan_param;
} PACKED app_dongle_cm_le_scanner_next_action_t;

typedef struct {
    app_dongle_cm_le_scanner_user_info_t                    user_list[APP_DONGLE_CM_LE_SCANNER_USER_MAX];
    app_dongle_cm_le_scanner_scan_parameter_t               scan_param;
    uint8_t                                                 scan_state;
    uint8_t                                                 scanning_user_id;

    bool                                                    stop_for_restart;
    app_dongle_cm_le_scanner_next_action_t                  next_action;
} PACKED app_dongle_cm_le_scanner_context_t;

static app_dongle_cm_le_scanner_context_t                   app_dongle_cm_le_scanner_ctx = {0};

#define BT_SIG_AD_TYPE_16BIT_UUID_COMPLETE                  0x03
#define BT_SIG_AD_TYPE_APPEARANCE                           0x19
#define BT_GAP_LE_AD_TYPE_NAME_SHORT                        0x08
#define BT_GAP_LE_AD_TYPE_NAME_COMPLETE                     0x09

#define APP_DONGLE_CM_LINK_SERVICE_UUID_LE_HOGP             (0x1812)
#define APP_DONGLE_CM_LINK_SERVICE_UUID_ULL_HID             (0x1111)        // ToDo
#define APP_DONGLE_CM_LINK_SERVICE_UUID_ULL2                (0x1111)        // ToDo
#define APP_DONGLE_CM_LINK_SERVICE_UUID_LEA                 (0x184E)

#define BT_SIG_AD_TYPE_APPEARANCE_KB                        (0x03C1)
#define BT_SIG_AD_TYPE_APPEARANCE_MS                        (0x03C2)
#define BT_SIG_AD_TYPE_APPEARANCE_GAMEPAD                   (0x03C4)
#define BT_SIG_AD_TYPE_APPEARANCE_SPEAKER                   (0x0845)
#define BT_SIG_AD_TYPE_APPEARANCE_EARBUDS                   (0x0941)
#define BT_SIG_AD_TYPE_APPEARANCE_HEADSET                   (0x0942)
#define BT_SIG_AD_TYPE_APPEARANCE_HEARING_AID               (0x0A40)




/**================================================================================*/
/**                                 LE Scan Whitelist                              */
/**================================================================================*/
typedef struct {
    uint8_t                                                 addr_type;
    uint8_t                                                *addr;
    uint8_t                                                 whitelist_state;
} PACKED app_dongle_cm_le_scanner_whitelist_item_t;

typedef struct {
    app_dongle_cm_le_scanner_whitelist_item_t               whitelist[APP_DONGLE_CM_DEVICE_LIST_MAX_NUM];
    uint8_t                                                 whitelist_state;
    uint8_t                                                 whitelist_action;
} PACKED app_dongle_cm_le_scanner_whitelist_context_t;

static app_dongle_cm_le_scanner_whitelist_context_t         app_dongle_cm_le_scanner_whitelist_ctx = {0};



static void app_dongle_cm_le_scanner_whitelist_printf()
{

}

static void app_dongle_cm_le_scanner_whitelist_init()
{
    memset(&app_dongle_cm_le_scanner_whitelist_ctx, 0, sizeof(app_dongle_cm_le_scanner_whitelist_context_t));
}

bool app_dongle_cm_le_scanner_whitelist_add_addr(uint8_t addr_type, uint8_t *addr)
{
    return TRUE;
}

bool app_dongle_cm_le_scanner_whitelist_remove_addr(uint8_t addr_type, uint8_t *addr)
{
    return TRUE;
}

bool app_dongle_cm_le_scanner_whitelist_clear_addr(void)
{
    return TRUE;
}

bool app_dongle_cm_le_scanner_whitelist_operate(app_dongle_cm_le_scanner_whitelist_action_t action)
{
    return TRUE;
}



/**================================================================================*/
/**                                   Internal API                                 */
/**================================================================================*/
static void app_dongle_cm_le_scanner_found_link_device_type(uint8_t *adv_data, uint8_t adv_len,
                                                            uint8_t *link_type, uint8_t *device_type, bool *check_name_pass)
{
    // APPS_LOG_MSGID_E(LOG_TAG" found_link_device_type, %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X",
    //                  12, adv_data[0], adv_data[1], adv_data[2], adv_data[3], adv_data[4], adv_data[5], adv_data[6], adv_data[7],
    //                 adv_data[8], adv_data[9], adv_data[10], adv_data[11]);

    int index = 0;
    while (index < adv_len) {
        const uint8_t data_len = adv_data[index];
        index++;
        if (data_len < 1) {
            break;
        }

        const uint8_t ad_type = adv_data[index];
        index++;
        const uint8_t buf_len = data_len - 1;

        if (ad_type == BT_SIG_AD_TYPE_APPEARANCE) {
            uint16_t appearance = (adv_data[index] | (adv_data[index + 1] << 8));
            index += buf_len;
            if (appearance == BT_SIG_AD_TYPE_APPEARANCE_KB) {
                *device_type = APP_DONGLE_CM_DEVICE_TYPE_KB;
                // Workaround for old keyboard
                //*link_type = APP_DONGLE_CM_LINK_TYPE_LE_HOGP;
            } else if (appearance == BT_SIG_AD_TYPE_APPEARANCE_MS) {
                *device_type = APP_DONGLE_CM_DEVICE_TYPE_MS;
            } else if (appearance == BT_SIG_AD_TYPE_APPEARANCE_GAMEPAD) {
                *device_type = APP_DONGLE_CM_DEVICE_TYPE_GAMEPAD;
            } else if (appearance == BT_SIG_AD_TYPE_APPEARANCE_HEADSET
                       || appearance == BT_SIG_AD_TYPE_APPEARANCE_EARBUDS
                       || appearance == BT_SIG_AD_TYPE_APPEARANCE_SPEAKER
                       || appearance == BT_SIG_AD_TYPE_APPEARANCE_HEARING_AID) {
                *device_type = APP_DONGLE_CM_DEVICE_TYPE_HEADSET;
            }
        } else if (ad_type == BT_SIG_AD_TYPE_16BIT_UUID_COMPLETE) {
            uint16_t uuid = (adv_data[index] | (adv_data[index + 1] << 8));
            index += buf_len;
            if (uuid == APP_DONGLE_CM_LINK_SERVICE_UUID_LE_HOGP) {
                *link_type = APP_DONGLE_CM_LINK_TYPE_LE_HOGP;
            } else if (uuid == APP_DONGLE_CM_LINK_SERVICE_UUID_ULL_HID) {
                *link_type = APP_DONGLE_CM_LINK_TYPE_ULL_HID;
            } else if (uuid == APP_DONGLE_CM_LINK_SERVICE_UUID_ULL2) {
                *link_type = APP_DONGLE_CM_LINK_TYPE_ULL2;
            } else if (uuid == APP_DONGLE_CM_LINK_SERVICE_UUID_LEA) {
                *link_type = APP_DONGLE_CM_LINK_TYPE_LEA;
            }
        }
#ifdef APP_DONGLE_CM_LE_SCANNER_CHECK_REMOTE_DEVICE_NAME
        else if (ad_type == BT_GAP_LE_AD_TYPE_NAME_SHORT || ad_type == BT_GAP_LE_AD_TYPE_NAME_COMPLETE) {
            uint8_t *name = &adv_data[index];
            index += buf_len;
            if (memcmp(name, APP_DONGLE_CM_LE_SCANNER_REMOTE_DEVICE_NAME_PREFIX, strlen(APP_DONGLE_CM_LE_SCANNER_REMOTE_DEVICE_NAME_PREFIX)) == 0) {
                *check_name_pass = TRUE;
            }
        }
#endif
        else {
            index += buf_len;
        }
    }
}

static void app_dongle_cm_le_scanner_found_callback(uint8_t addr_type, uint8_t *addr, int8_t rssi, uint8_t *adv_data, uint8_t adv_len)
{
    // Callback from BT Task
    app_dongle_cm_le_scanner_scan_parameter_t scan_param = app_dongle_cm_le_scanner_ctx.scan_param;
    uint8_t link_type = APP_DONGLE_CM_LINK_TYPE_NONE;
    uint8_t device_type = APP_DONGLE_CM_DEVICE_TYPE_NONE;
    bool check_name_pass = FALSE;
    app_dongle_cm_le_scanner_found_link_device_type(adv_data, adv_len, &link_type, &device_type, &check_name_pass);
    APPS_LOG_MSGID_I(LOG_TAG" found_callback, addr=%d %08X%04X rssi=%d adv_len=%d - link_type=%d 0x%04X device_type=%d 0x%04X check_name_pass=%d",
                     10, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), rssi, adv_len,
                     link_type, scan_param.scan_link_type_bit_mask, device_type, scan_param.scan_device_type_bit_mask, check_name_pass);

#ifdef APP_DONGLE_CM_LE_SCANNER_CHECK_REMOTE_DEVICE_NAME
    if (!check_name_pass) {
        return;
    }
#endif

    bool match_link_type = FALSE;
    bool match_device_type = FALSE;
    if (scan_param.scan_link_type_bit_mask > 0) {
        bool need_check_le_hogp = ((scan_param.scan_link_type_bit_mask & (1 << APP_DONGLE_CM_LINK_TYPE_LE_HOGP)) > 0);
        bool need_check_ull_hid = ((scan_param.scan_link_type_bit_mask & (1 << APP_DONGLE_CM_LINK_TYPE_ULL_HID)) > 0);
        bool need_check_ull2 = ((scan_param.scan_link_type_bit_mask & (1 << APP_DONGLE_CM_LINK_TYPE_ULL2)) > 0);
        bool need_check_lea = ((scan_param.scan_link_type_bit_mask & (1 << APP_DONGLE_CM_LINK_TYPE_LEA)) > 0);

        if (need_check_le_hogp && link_type == APP_DONGLE_CM_LINK_TYPE_LE_HOGP) {
            match_link_type = TRUE;
        }
        if (need_check_ull_hid && link_type == APP_DONGLE_CM_LINK_TYPE_ULL_HID) {
            match_link_type = TRUE;
        }
        if (need_check_ull2 && link_type == APP_DONGLE_CM_LINK_TYPE_ULL2) {
            match_link_type = TRUE;
        }
        if (need_check_lea && link_type == APP_DONGLE_CM_LINK_TYPE_LEA) {
            match_link_type = TRUE;
        }
    } else {
        match_link_type = TRUE;
    }

    if (scan_param.scan_device_type_bit_mask > 0) {
        bool need_check_kb = ((scan_param.scan_device_type_bit_mask & (1 << APP_DONGLE_CM_DEVICE_TYPE_KB)) > 0);
        bool need_check_ms = ((scan_param.scan_device_type_bit_mask & (1 << APP_DONGLE_CM_DEVICE_TYPE_MS)) > 0);
        bool need_check_gamepad = ((scan_param.scan_device_type_bit_mask & (1 << APP_DONGLE_CM_DEVICE_TYPE_GAMEPAD)) > 0);
        bool need_check_headset = ((scan_param.scan_device_type_bit_mask & (1 << APP_DONGLE_CM_DEVICE_TYPE_HEADSET)) > 0);

        if (need_check_kb && device_type == APP_DONGLE_CM_DEVICE_TYPE_KB) {
            match_device_type = TRUE;
        }
        if (need_check_ms && device_type == APP_DONGLE_CM_DEVICE_TYPE_MS) {
            match_device_type = TRUE;
        }
        if (need_check_gamepad && device_type == APP_DONGLE_CM_DEVICE_TYPE_GAMEPAD) {
            match_device_type = TRUE;
        }
        if (need_check_headset && device_type == APP_DONGLE_CM_DEVICE_TYPE_HEADSET) {
            match_device_type = TRUE;
        }
    } else {
        match_device_type = TRUE;
    }

    if (!match_link_type || !match_device_type) {
        uint8_t user_id = app_dongle_cm_le_scanner_ctx.scanning_user_id;
        APPS_LOG_MSGID_E(LOG_TAG" found_callback, not match - user_id=%d match_link_type=%d match_device_type=%d",
                         3, user_id, match_link_type, match_device_type);
        return;
    }

    for (uint8_t user_id = 0; user_id < APP_DONGLE_CM_LE_SCANNER_USER_MAX; user_id++) {
        if (user_id != APP_DONGLE_CM_LE_SCANNER_USER_NONE && user_id == app_dongle_cm_le_scanner_ctx.scanning_user_id) {
            app_dongle_cm_le_scanner_callback_t callback = app_dongle_cm_le_scanner_ctx.user_list[user_id].callback;
            uint8_t *user_param = app_dongle_cm_le_scanner_ctx.user_list[user_id].user_param;

            if (callback.adv_report_cb != NULL) {
                callback.adv_report_cb(addr_type, addr, rssi, adv_data, adv_len, link_type, device_type, user_param);
            }
            break;
        }
    }
}

static void app_dongle_cm_le_scanner_change_state(uint8_t scan_state)
{
    uint8_t old_state = app_dongle_cm_le_scanner_ctx.scan_state;
    if (old_state != scan_state) {
        app_dongle_cm_le_scanner_ctx.scan_state = scan_state;
        APPS_LOG_MSGID_I(LOG_TAG" change_state, scan_state=%d->%d", 2, old_state, scan_state);
        for (uint8_t user_id = 0; user_id < APP_DONGLE_CM_LE_SCANNER_USER_MAX; user_id++) {
            app_dongle_cm_le_scanner_callback_t callback = app_dongle_cm_le_scanner_ctx.user_list[user_id].callback;
            if (callback.state_change_cb != NULL) {
                callback.state_change_cb(old_state, scan_state);
            }
        }
    }
}

bool app_dongle_cm_le_scanner_event_handler(uint8_t event_group, uint16_t event_id, void *data, uint32_t data_len)
{
    if (event_group == APP_DONGLE_EVENT_GROUP_BT) {
        if (event_id == APP_DONGLE_EVENT_BT_LE_SCAN_STARTED_IND) {
            APPS_LOG_MSGID_I(LOG_TAG" event_handler, LE_SCAN_STARTED_IND", 0);
            app_dongle_cm_le_scanner_change_state(APP_DONGLE_CM_LE_SCANNER_STATE_STARTED);
        } else if (event_id == APP_DONGLE_EVENT_BT_LE_SCAN_STOPPED_IND) {
            APPS_LOG_MSGID_I(LOG_TAG" event_handler, LE_SCAN_STOPPED_IND", 0);
            app_dongle_cm_le_scanner_change_state(APP_DONGLE_CM_LE_SCANNER_STATE_IDLE);
            app_dongle_cm_le_scanner_ctx.scanning_user_id = APP_DONGLE_CM_LE_SCANNER_USER_NONE;
        } else if (event_id == APP_DONGLE_EVENT_BT_LE_SCAN_TIMEOUT) {
            APPS_LOG_MSGID_I(LOG_TAG" event_handler, LE_SCAN_TIMEOUT", 0);
            app_dongle_cm_le_scanner_stop_scan(app_dongle_cm_le_scanner_ctx.scanning_user_id);
        }
    }
    return FALSE;
}



/**================================================================================*/
/**                                     Public API                                 */
/**================================================================================*/
void app_dongle_cm_le_scanner_init(void)
{
    app_dongle_cm_le_scanner_whitelist_init();
    app_dongle_cm_le_scanner_whitelist_printf();

    memset(&app_dongle_cm_le_scanner_ctx, 0, sizeof(app_dongle_cm_le_scanner_context_t));
}

bool app_dongle_cm_le_scanner_register(uint8_t user_id, app_dongle_cm_le_scanner_callback_t callback, void *user_param)
{
    if (user_id >= APP_DONGLE_CM_LE_SCANNER_USER_MAX) {
        return FALSE;
    }
    app_dongle_cm_le_scanner_ctx.user_list[user_id].callback = callback;
    app_dongle_cm_le_scanner_ctx.user_list[user_id].user_param = user_param;
    return TRUE;
}

bool app_dongle_cm_le_scanner_unregister(uint8_t user_id)
{
    if (user_id >= APP_DONGLE_CM_LE_SCANNER_USER_MAX) {
        return FALSE;
    }
    app_dongle_cm_le_scanner_ctx.user_list[user_id].callback.state_change_cb = NULL;
    app_dongle_cm_le_scanner_ctx.user_list[user_id].callback.adv_report_cb = NULL;
    app_dongle_cm_le_scanner_ctx.user_list[user_id].user_param = NULL;
    return TRUE;
}

bool app_dongle_cm_le_scanner_start_scan(uint8_t user_id, app_dongle_cm_le_scanner_scan_parameter_t scan_param)
{
    uint8_t scan_state = app_dongle_cm_le_scanner_ctx.scan_state;
    APPS_LOG_MSGID_W(LOG_TAG" start_scan, user_id=%d scan_state=%d", 2, user_id, scan_state);
    if (scan_state != APP_DONGLE_CM_LE_SCANNER_STATE_IDLE) {
        return FALSE;
    }
    // ToDo, enhance other state

    bool success = app_bt_service_le_scanner_start((scan_param.scan_policy == APP_DONGLE_CM_LE_SCANNER_USER_WHITELIST), scan_param.duplicate_filter,
                                                   scan_param.scan_interval, scan_param.scan_window,
                                                   scan_param.timeout_ms, app_dongle_cm_le_scanner_found_callback);
    if (success) {
        app_dongle_cm_le_scanner_ctx.scan_param = scan_param;
        app_dongle_cm_le_scanner_change_state(APP_DONGLE_CM_LE_SCANNER_STATE_STARTING);
        app_dongle_cm_le_scanner_ctx.scanning_user_id = user_id;
    }
    return success;
}

bool app_dongle_cm_le_scanner_stop_scan(uint8_t user_id)
{
    uint8_t scan_state = app_dongle_cm_le_scanner_ctx.scan_state;
    APPS_LOG_MSGID_W(LOG_TAG" stop_scan, user_id=%d scan_state=%d", 2, user_id, scan_state);
    if (scan_state != APP_DONGLE_CM_LE_SCANNER_STATE_STARTED) {
        return FALSE;
    }
    // ToDo, enhance other state

    bool success = app_bt_service_le_scanner_stop();
    if (success) {
        app_dongle_cm_le_scanner_change_state(APP_DONGLE_CM_LE_SCANNER_STATE_STOPPING);
        app_dongle_cm_le_scanner_ctx.scanning_user_id = user_id;
    }
    return success;
}

uint8_t app_dongle_cm_le_scanner_get_state(void)
{
    return app_dongle_cm_le_scanner_ctx.scan_state;
}