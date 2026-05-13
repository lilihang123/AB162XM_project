/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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



#include "race_cmd_feature.h"
#ifdef RACE_FOTA_CMD_ENABLE
#include "fota_multi_info_util.h"
#include "fota_flash.h"
#include "fota_multi_info.h"
#include "fota_signature.h"
#include "race_xport.h"
#include "race_util.h"
#include "race_bt.h"
#include "race_timer.h"
#include "race_cmd_fota.h"
#include "race_fota_util.h"
#include "race_fota.h"
#include "race_storage_access.h"
#include "race_storage_util.h"
#include "race_noti.h"
#ifdef __FOTA_FOR_BISTO__
#include "fota_flash_for_gsound.h"
#endif
#ifdef RACE_CFU_ENABLE
#include "cfu.h"
#endif
#ifdef RACE_FOTA_ACTIVE_MODE_KEEP_HFP
#ifdef AIR_LE_AUDIO_ENABLE
#include "bt_sink_srv_le_cap_audio_manager.h"
#include "bt_sink_srv_le_cap.h"
#endif
#endif
#ifdef AIR_RACE_CO_SYS_ENABLE
#include "race_cmd_relay_cmd_cosys.h"
#endif

#ifdef RACE_RELAY_CMD_ENABLE
#include "race_cmd_relay_cmd.h"
#endif
#ifdef AIR_BLE_ULTRA_LOW_LATENCY_WITH_HID_ENABLE
#include "bt_ull_le_hid_service.h"
#include "ble_air_interface.h"
#endif
#if defined(AIR_DONGLE_FOTA_BY_SP_ENABLE) || defined(AIR_FOTA_DONGLE_HEADSET_BY_SP_ENABLE)
#include "nvkey.h"
#include "nvdm.h"
#include "nvkey_id_list.h"
#include "nvdm_id_list.h"
#include "fota.h"
#endif
#include "hal_dvfs.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_platform.h"

#include <zephyr/bluetooth/addr.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/sys/util.h>
#include <zephyr/settings/settings.h>
#ifdef AIR_BT_AIR_SERVICE_ENABLE
#include "ble_air_internal.h"
#endif
#ifdef CONFIG_BT_PKA_LIB_MULTI_PROTOCOL
#include "ieee802154_controller.h"
#endif
bool g_race_fota_dvfs_locked = false;

typedef struct {
    race_recipient_type_enum recipient_type;
    race_fota_stop_originator_enum originator;
    race_fota_stop_reason_enum reason;
} race_fota_stop_msg_data_struct;


race_fota_cntx_struct g_race_fota_cntx;
race_fota_cntx_struct *g_race_fota_cntx_ptr;
uint16_t g_race_fota_spp_transmit_interval;
uint16_t g_race_fota_ble_transmit_interval;

#ifdef MTK_RACE_EVENT_ID_ENABLE
/* register_id is not included in g_race_fota_cntx because g_race_fota_cntx is reset frequently. */
int32_t g_race_fota_event_register_id;

static RACE_ERRCODE race_fota_race_event_cb(int32_t register_id, race_event_type_enum event_type, void *param, void *user_data);
#else
static RACE_ERRCODE race_fota_race_event_cb(race_event_type_enum event_type, void *param, void *user_data);
#endif

#if 0//def  AIR_BLE_ULTRA_LOW_LATENCY_WITH_HID_ENABLE
void race_fota_le_ull_set_advertising_enable(bool enable, bool general_adv, bool pairing);
#endif

#ifdef AIR_PURE_GAMING_DONGLE_ENABLE
void race_fota_dongle_reconnect_ms_kb();

void race_fota_dongle_disconnect_ms_kb();

void race_fota_dongle_disconnect_ms_kb_default()
{
    return;
}
void race_fota_dongle_reconnect_ms_kb_default()
{
    return;
}

#pragma weak race_fota_dongle_reconnect_ms_kb=race_fota_dongle_reconnect_ms_kb_default

#pragma weak race_fota_dongle_disconnect_ms_kb=race_fota_dongle_disconnect_ms_kb_default
#endif

RACE_ERRCODE race_fota_reset(void)
{
    if (g_race_fota_cntx_ptr) {
        memset(g_race_fota_cntx_ptr, 0, sizeof(race_fota_cntx_struct));
        g_race_fota_cntx_ptr->app_id_timer_id = RACE_TIMER_INVALID_TIMER_ID;
        g_race_fota_cntx_ptr->commit_timer_id = RACE_TIMER_INVALID_TIMER_ID;
        g_race_fota_cntx_ptr->fota_mode = RACE_FOTA_MODE_MAX;
        g_race_fota_cntx_ptr->dl_method = RACE_FOTA_DUAL_DEVICE_DL_METHOD_MAX;
        memset(&g_race_fota_cntx_ptr->remote_address, 0, sizeof(bt_addr_t));
#if 0//def AIR_BLE_ULTRA_LOW_LATENCY_WITH_HID_ENABLE
        g_race_fota_cntx_ptr->switch_link_timer_id = RACE_TIMER_INVALID_TIMER_ID;
#endif
        return RACE_ERRCODE_SUCCESS;
    }

    return RACE_ERRCODE_FAIL;
}


RACE_ERRCODE race_fota_init(void)
{
    if (!g_race_fota_cntx_ptr) {
        g_race_fota_cntx_ptr = &g_race_fota_cntx;
    }

#ifdef MTK_RACE_EVENT_ID_ENABLE
    race_event_register(&g_race_fota_event_register_id, race_fota_race_event_cb, NULL);
#else
    race_event_register(race_fota_race_event_cb, NULL);
#endif

    g_race_fota_spp_transmit_interval = RACE_FOTA_DEFAULT_SPP_TRANSMIT_INTERVAL_IN_MS;
    g_race_fota_ble_transmit_interval = RACE_FOTA_DEFAULT_BLE_TRANSMIT_INTERVAL_IN_MS;

    return race_fota_reset();
}


race_fota_cntx_struct *race_fota_cntx_get(void)
{
    return g_race_fota_cntx_ptr;
}

#if 0//def AIR_BLE_ULTRA_LOW_LATENCY_WITH_HID_ENABLE
void race_fota_le_ull_set_advertising_enable_default(bool enable, bool general_adv, bool pairing)
{
    UNUSED(enable);
    UNUSED(general_adv);
    UNUSED(pairing);
}
#pragma weak race_fota_le_ull_set_advertising_enable=race_fota_le_ull_set_advertising_enable_default

uint8_t race_fota_switch_link_timer_id_get(void)
{
    if (g_race_fota_cntx_ptr) {
        if (race_timer_smart_is_enabled(g_race_fota_cntx_ptr->switch_link_timer_id)) {
            return g_race_fota_cntx_ptr->switch_link_timer_id;
        }

        g_race_fota_cntx_ptr->switch_link_timer_id = RACE_TIMER_INVALID_TIMER_ID;
    }

    return RACE_TIMER_INVALID_TIMER_ID;
}


RACE_ERRCODE race_fota_switch_link_timer_id_set(uint8_t timer_id)
{
    if (g_race_fota_cntx_ptr) {
        g_race_fota_cntx_ptr->switch_link_timer_id = timer_id;

        return RACE_ERRCODE_SUCCESS;
    }

    return RACE_ERRCODE_FAIL;
}

void race_fota_switch_le_link_timer_expiration_hdl(uint8_t id, void *user_data)
{
    uint8_t channel_id = 0;

    if (!g_race_fota_cntx_ptr || id != g_race_fota_cntx_ptr->switch_link_timer_id) {
        race_timer_smart_stop(id, NULL);
        return;
    }

    race_timer_smart_stop(id, NULL);
    race_fota_switch_link_timer_id_set(RACE_TIMER_INVALID_TIMER_ID);
    if (RACE_ERRCODE_SUCCESS == race_fota_channel_id_get(&channel_id)) {
        bt_addr_t *addr = (bt_addr_t *)race_get_bt_connection_addr(channel_id);
        ble_air_switch_link(BT_ULL_LE_HID_SRV_LINK_MODE_FOTA, addr);
    }
    /*trigger ADV*/
    race_fota_le_ull_set_advertising_enable(true,true,false);
}

void race_fota_switch_cis_link_timer_expiration_hdl(uint8_t id, void *user_data)
{
    uint8_t channel_id = 0;

    if (!g_race_fota_cntx_ptr || id != g_race_fota_cntx_ptr->switch_link_timer_id) {
        race_timer_smart_stop(id, NULL);
        return;
    }

    race_timer_smart_stop(id, NULL);
    race_fota_switch_link_timer_id_set(RACE_TIMER_INVALID_TIMER_ID);
    if (RACE_ERRCODE_SUCCESS == race_fota_channel_id_get(&channel_id)) {
        bt_addr_t *addr = (bt_addr_t *)race_get_bt_connection_addr(channel_id);
        ble_air_switch_link(BT_ULL_LE_HID_SRV_LINK_MODE_NORMAL, addr);
    }
}
#endif

uint8_t race_fota_app_id_timer_id_get(void)
{
    if (g_race_fota_cntx_ptr) {
        if (race_timer_smart_is_enabled(g_race_fota_cntx_ptr->app_id_timer_id)) {
            return g_race_fota_cntx_ptr->app_id_timer_id;
        }

        g_race_fota_cntx_ptr->app_id_timer_id = RACE_TIMER_INVALID_TIMER_ID;
    }

    return RACE_TIMER_INVALID_TIMER_ID;
}


RACE_ERRCODE race_fota_app_id_timer_id_set(uint8_t timer_id)
{
    if (g_race_fota_cntx_ptr) {
        g_race_fota_cntx_ptr->app_id_timer_id = timer_id;

        return RACE_ERRCODE_SUCCESS;
    }

    return RACE_ERRCODE_FAIL;
}


void race_fota_app_id_timer_expiration_hdl(uint8_t id, void *user_data)
{
    printk("id:%d app_id_timer_id:%d",
                     id,
                     g_race_fota_cntx_ptr ? g_race_fota_cntx_ptr->app_id_timer_id : RACE_TIMER_INVALID_TIMER_ID);

    if (!g_race_fota_cntx_ptr || id != g_race_fota_cntx_ptr->app_id_timer_id) {
        /*RACE_LOG_MSGID_W("Timer id not match. id:%d app_id_timer_id:%d", 2,
                         id,
                         g_race_fota_cntx_ptr ? g_race_fota_cntx_ptr->app_id_timer_id : RACE_TIMER_INVALID_TIMER_ID);*/
        /* Must not reset timer id for it may be the previous timer which is not stopped properly. */
        race_timer_smart_stop(id, NULL);
        return;
    }

    /* SP lost */
    g_race_fota_cntx_ptr->sp_online = FALSE;

    race_timer_smart_stop(id, NULL);
    race_fota_app_id_timer_id_set(RACE_TIMER_INVALID_TIMER_ID);
    race_fota_stop(RACE_FOTA_STOP_ORIGINATOR_AGENT, RACE_FOTA_STOP_REASON_SP_LOST);
}


uint8_t race_fota_commit_timer_id_get(void)
{
    if (g_race_fota_cntx_ptr) {
        if (race_timer_smart_is_enabled(g_race_fota_cntx_ptr->commit_timer_id)) {
            return g_race_fota_cntx_ptr->commit_timer_id;
        }

        g_race_fota_cntx_ptr->commit_timer_id = RACE_TIMER_INVALID_TIMER_ID;
    }

    return RACE_TIMER_INVALID_TIMER_ID;
}


RACE_ERRCODE race_fota_commit_timer_id_set(uint8_t timer_id)
{
    if (g_race_fota_cntx_ptr) {
        g_race_fota_cntx_ptr->commit_timer_id = timer_id;

        return RACE_ERRCODE_SUCCESS;
    }

    return RACE_ERRCODE_FAIL;
}


void race_fota_commit_timer_expiration_hdl(uint8_t id, void *user_data)
{
    race_fota_commit_timer_msg_struct *commit_timer_msg = (race_fota_commit_timer_msg_struct *)user_data;
#if 0//def AIR_BLE_ULTRA_LOW_LATENCY_WITH_HID_ENABLE
    uint8_t channel_id = 0;
#endif
    printk("id:%d commit_timer_id:%d",
                     id,
                     g_race_fota_cntx_ptr ? g_race_fota_cntx_ptr->commit_timer_id : RACE_TIMER_INVALID_TIMER_ID);

    if (!g_race_fota_cntx_ptr || id != g_race_fota_cntx_ptr->commit_timer_id) {
        /*RACE_LOG_MSGID_W("Timer id not match. id:%d commit_timer_id:%d", 2,
                         id,
                         g_race_fota_cntx_ptr ? g_race_fota_cntx_ptr->commit_timer_id : RACE_TIMER_INVALID_TIMER_ID);*/
        /* Must not reset timer id for it may be the previous timer which is not stopped properly. */
        race_timer_smart_stop(id, NULL);
        return;
    }
#if 0//def AIR_BLE_ULTRA_LOW_LATENCY_WITH_HID_ENABLE
    if (RACE_ERRCODE_SUCCESS == race_fota_channel_id_get(&channel_id)) {
        bt_addr_t *addr = (bt_addr_t *)race_get_bt_connection_addr(channel_id);
        ble_air_switch_link(BT_ULL_LE_HID_SRV_LINK_MODE_NORMAL, addr);
    }
#endif
    if (RACE_FOTA_DOWNLOAD_STATE_COMMITING == race_fota_dl_state_get()) {
        if (commit_timer_msg &&
            RACE_EVENT_REMOTE_DEVICE_ADDRESS_LENGTH >= commit_timer_msg->address_length) {
            race_event_send_fota_need_reboot_event(commit_timer_msg->address, commit_timer_msg->address_length);
        } else {
            race_event_send_fota_need_reboot_event(NULL, 0);
        }
    }

    race_timer_smart_stop(id, NULL);
    if (user_data) {
        race_mem_free(user_data);
    }
    race_fota_commit_timer_id_set(RACE_TIMER_INVALID_TIMER_ID);
}


uint8_t race_fota_stop_timer_id_get(void)
{
    if (g_race_fota_cntx_ptr) {
        if (race_timer_smart_is_enabled(g_race_fota_cntx_ptr->stop_timer_id)) {
            return g_race_fota_cntx_ptr->stop_timer_id;
        }

        g_race_fota_cntx_ptr->stop_timer_id = RACE_TIMER_INVALID_TIMER_ID;
    }

    return RACE_TIMER_INVALID_TIMER_ID;
}


RACE_ERRCODE race_fota_stop_timer_id_set(uint8_t timer_id)
{
    if (g_race_fota_cntx_ptr) {
        g_race_fota_cntx_ptr->stop_timer_id = timer_id;

        return RACE_ERRCODE_SUCCESS;
    }

    return RACE_ERRCODE_FAIL;
}


void race_fota_stop_timer_expiration_hdl(uint8_t id, void *user_data)
{
    race_fota_download_state_enum fota_dl_state = race_fota_dl_state_get();
    race_fota_cntx_struct *fota_cntx = race_fota_cntx_get();

    printk("id:%d stop_timer_id:%d",
            id,
            fota_cntx ? fota_cntx->stop_timer_id : 0xFF);

    if (!fota_cntx || id != fota_cntx->stop_timer_id) {
        /*RACE_LOG_MSGID_W("Timer id not match. id:%d stop_timer_id:%d", 2,
                         id,
                         fota_cntx ? fota_cntx->stop_timer_id : RACE_TIMER_INVALID_TIMER_ID);*/
        /* Must not reset timer id for it may be the previous timer which is not stopped properly. */
        race_timer_smart_stop(id, NULL);
        return;
    }

    if (RACE_FOTA_DOWNLOAD_STATE_STOPPING == fota_dl_state) {
        race_fota_stop_agent_sp_stop_noti_struct sp_stop_noti = {0};

        sp_stop_noti.status = RACE_ERRCODE_SUCCESS;
        sp_stop_noti.recipient_type = fota_cntx->is_dual_fota ? RACE_RECIPIENT_TYPE_AGENT_PARTNER : RACE_RECIPIENT_TYPE_AGENT_ONLY;

        fota_cntx->stop_status = RACE_FOTA_STOP_STATUS_WAIT_FOR_5D;
        race_fota_stop_agent_sp_stop_noti_process(&sp_stop_noti);
    }

    race_timer_smart_stop(id, NULL);
    race_fota_stop_timer_id_set(RACE_TIMER_INVALID_TIMER_ID);
}


void race_fota_set_fota_mode(race_fota_mode_enum fota_mode)
{
    if (g_race_fota_cntx_ptr) {
        g_race_fota_cntx_ptr->fota_mode = fota_mode;
    }
}


bool race_fota_is_active_mode(void)
{
    if (g_race_fota_cntx_ptr) {
        return RACE_FOTA_MODE_ACTIVE == g_race_fota_cntx_ptr->fota_mode;
    }

    return FALSE;
}


#ifdef RACE_FOTA_ADAPTIVE_MODE_ENABLE
bool race_fota_is_adaptive_mode(void)
{
    if (g_race_fota_cntx_ptr) {
        return RACE_FOTA_MODE_ADAPTIVE == g_race_fota_cntx_ptr->fota_mode;
    }

    return FALSE;
}
#endif

#if 0
bool race_fota_is_dual_fota(void)
{
    if (g_race_fota_cntx_ptr) {
        return g_race_fota_cntx_ptr->is_dual_fota;
    }

    return FALSE;
}
#endif

race_fota_download_state_enum race_fota_dl_state_get(void)
{
    if (g_race_fota_cntx_ptr) {
//        RACE_LOG_MSGID_I("dl_state:%d old_dl_state:%d", 2,
//                         g_race_fota_cntx_ptr->dl_state,
//                         g_race_fota_cntx_ptr->old_dl_state);

        return g_race_fota_cntx_ptr->dl_state;
    }

    return RACE_FOTA_DOWNLOAD_STATE_MAX;
}


void race_fota_dl_state_set(race_fota_download_state_enum state)
{
    if (g_race_fota_cntx_ptr) {
        if (state == g_race_fota_cntx_ptr->dl_state) {
            return;
        }

        if (RACE_FOTA_DOWNLOAD_STATE_NONE == state ||
            RACE_FOTA_DOWNLOAD_STATE_MAX == state) {
            g_race_fota_cntx_ptr->old_dl_state = state;
            g_race_fota_cntx_ptr->dl_state = state;
        } else {
            g_race_fota_cntx_ptr->old_dl_state = g_race_fota_cntx_ptr->dl_state;
            g_race_fota_cntx_ptr->dl_state = state;
        }
    }
}


void race_fota_dl_state_rollback(void)
{
    if (g_race_fota_cntx_ptr) {
        /*RACE_LOG_MSGID_I("dl_state:%d old_dl_state:%d", 2,
                         g_race_fota_cntx_ptr->dl_state,
                         g_race_fota_cntx_ptr->old_dl_state);*/
        g_race_fota_cntx_ptr->dl_state = g_race_fota_cntx_ptr->old_dl_state;
    }
}


void race_fota_sp_trans_method_set(race_fota_sp_trans_method_enum sp_trans_method)
{
    if (g_race_fota_cntx_ptr) {
        g_race_fota_cntx_ptr->sp_trans_method = sp_trans_method;
    }
}


race_fota_sp_trans_method_enum race_fota_sp_trans_method_get(void)
{
    if (g_race_fota_cntx_ptr) {
        if (!race_fota_is_race_fota_running()) {
            g_race_fota_cntx_ptr->sp_trans_method = RACE_FOTA_SP_TRANS_METHOD_NONE;
        }

        return g_race_fota_cntx_ptr->sp_trans_method;
    }

    return RACE_FOTA_SP_TRANS_METHOD_MAX;
}


RACE_ERRCODE race_fota_set_sp_trans_method_by_channel_id(uint8_t channel_id)
{
    race_serial_port_type_enum port_type = race_get_port_type_by_channel_id(channel_id);

    if (RACE_SERIAL_PORT_TYPE_BLE == port_type) {
        race_fota_sp_trans_method_set(RACE_FOTA_SP_TRANS_METHOD_BLE);
    } else if (RACE_SERIAL_PORT_TYPE_SPP == port_type) {
        race_fota_sp_trans_method_set(RACE_FOTA_SP_TRANS_METHOD_SPP);
    }
#ifdef MTK_AIRUPDATE_ENABLE
    else if (RACE_SERIAL_PORT_TYPE_AIRUPDATE == port_type) {
        race_fota_sp_trans_method_set(RACE_FOTA_SP_TRANS_METHOD_AIRUPDATE);
    }
#endif
#ifdef MTK_IAP2_PROFILE_ENABLE
    else if (RACE_SERIAL_PORT_TYPE_IAP2 == port_type) {
        race_fota_sp_trans_method_set(RACE_FOTA_SP_TRANS_METHOD_IAP2);
    }
#endif
#ifdef MTK_GATT_OVER_BREDR_ENABLE
    else if (RACE_SERIAL_PORT_TYPE_GATT_OVER_BREDR == port_type) {
        race_fota_sp_trans_method_set(RACE_FOTA_SP_TRANS_METHOD_GATT_OVER_BREDR);
    }
#endif
#if defined(AIR_USB_ENABLE)
    else if (MUX_USB_COM_1 == port_type) {
        race_fota_sp_trans_method_set(RACE_FOTA_SP_TRANS_METHOD_USB1);
    } else if (MUX_USB_COM_2 == port_type) {
        race_fota_sp_trans_method_set(RACE_FOTA_SP_TRANS_METHOD_USB2);
    }
#endif
    else if (RACE_SERIAL_PORT_TYPE_BLE_1 == port_type) {
        race_fota_sp_trans_method_set(RACE_FOTA_SP_TRANS_METHOD_BLE_1);
    } else if (RACE_SERIAL_PORT_TYPE_BLE_2 == port_type) {
        race_fota_sp_trans_method_set(RACE_FOTA_SP_TRANS_METHOD_BLE_2);
    } else if (RACE_SERIAL_PORT_TYPE_UART == port_type) {
        race_fota_sp_trans_method_set(RACE_FOTA_SP_TRANS_METHOD_UART);
    }
#ifdef AIR_MUX_BT_HID_ENABLE
     else if (RACE_SERIAL_PORT_TYPE_HID == port_type) {
        race_fota_sp_trans_method_set(RACE_FOTA_SP_TRANS_METHOD_HID);
     }
#endif
#if defined(AIR_DONGLE_FOTA_BY_SP_ENABLE) || defined(AIR_FOTA_DONGLE_HEADSET_BY_SP_ENABLE)
    else if (RACE_SERIAL_PORT_TYPE_BLE_SP_DONGLE == port_type) {
        race_fota_sp_trans_method_set(RACE_FOTA_SP_TRANS_METHOD_SP_DONGLE);
    }
#endif
#if defined(AIR_FOTA_DONGLE_HEADSET_BY_SP_ENABLE)
    else if (MUX_BT_BLE_SP_DONGLE_THROUGHOUT == port_type) {
        race_fota_sp_trans_method_set(RACE_FOTA_SP_TRANS_METHOD_SP_DONGLE_THROUGHOUT);
    }
#endif
    else {
        return RACE_ERRCODE_NOT_SUPPORT;
    }

    return RACE_ERRCODE_SUCCESS;
}


RACE_ERRCODE race_fota_channel_id_get(uint8_t *channel_id)
{
    race_fota_sp_trans_method_enum sp_trans_method = race_fota_sp_trans_method_get();

    if (!channel_id) {
        return RACE_ERRCODE_PARAMETER_ERROR;
    }

    *channel_id = 0xFF;

    if (RACE_FOTA_SP_TRANS_METHOD_SPP == sp_trans_method) {
        *channel_id = race_get_channel_id_by_port_type(RACE_SERIAL_PORT_TYPE_SPP);
        return RACE_ERRCODE_SUCCESS;
    } else if (RACE_FOTA_SP_TRANS_METHOD_BLE == sp_trans_method) {
        *channel_id = race_get_channel_id_by_port_type(RACE_SERIAL_PORT_TYPE_BLE);
        return RACE_ERRCODE_SUCCESS;
    }
#ifdef MTK_AIRUPDATE_ENABLE
    else if (RACE_FOTA_SP_TRANS_METHOD_AIRUPDATE == sp_trans_method) {
        *channel_id = race_get_channel_id_by_port_type(RACE_SERIAL_PORT_TYPE_AIRUPDATE);
        return RACE_ERRCODE_SUCCESS;
    }
#endif
#ifdef MTK_IAP2_PROFILE_ENABLE
    else if (RACE_FOTA_SP_TRANS_METHOD_IAP2 == sp_trans_method) {
        *channel_id = race_get_channel_id_by_port_type(RACE_SERIAL_PORT_TYPE_IAP2);
        return RACE_ERRCODE_SUCCESS;
    }
#endif
#ifdef MTK_GATT_OVER_BREDR_ENABLE
    else if (RACE_FOTA_SP_TRANS_METHOD_GATT_OVER_BREDR == sp_trans_method) {
        *channel_id = race_get_channel_id_by_port_type(RACE_SERIAL_PORT_TYPE_GATT_OVER_BREDR);
        return RACE_ERRCODE_SUCCESS;
    }
#endif
#if defined(AIR_USB_ENABLE)
    else if (RACE_FOTA_SP_TRANS_METHOD_USB1 == sp_trans_method) {
        *channel_id = race_get_channel_id_by_port_type(MUX_USB_COM_1);
        return RACE_ERRCODE_SUCCESS;
    } else if (RACE_FOTA_SP_TRANS_METHOD_USB2 == sp_trans_method) {
        *channel_id = race_get_channel_id_by_port_type(MUX_USB_COM_2);
        return RACE_ERRCODE_SUCCESS;
    }
#endif
    else if (RACE_FOTA_SP_TRANS_METHOD_BLE_1 == sp_trans_method) {
        *channel_id = race_get_channel_id_by_port_type(RACE_SERIAL_PORT_TYPE_BLE_1);
        return RACE_ERRCODE_SUCCESS;
    } else if (RACE_FOTA_SP_TRANS_METHOD_BLE_2 == sp_trans_method) {
        *channel_id = race_get_channel_id_by_port_type(RACE_SERIAL_PORT_TYPE_BLE_2);
        return RACE_ERRCODE_SUCCESS;
    } else if (RACE_FOTA_SP_TRANS_METHOD_UART == sp_trans_method) {
        *channel_id = race_get_channel_id_by_port_type(RACE_SERIAL_PORT_TYPE_UART);
        return RACE_ERRCODE_SUCCESS;
    }
#ifdef AIR_MUX_BT_HID_ENABLE
     else if (RACE_FOTA_SP_TRANS_METHOD_HID == sp_trans_method) {
        *channel_id = race_get_channel_id_by_port_type(RACE_SERIAL_PORT_TYPE_HID);
        return RACE_ERRCODE_SUCCESS;
    }
#endif
#if defined(AIR_DONGLE_FOTA_BY_SP_ENABLE) || defined(AIR_FOTA_DONGLE_HEADSET_BY_SP_ENABLE)
    else if (RACE_FOTA_SP_TRANS_METHOD_SP_DONGLE == sp_trans_method) {
        *channel_id = race_get_channel_id_by_port_type(RACE_SERIAL_PORT_TYPE_BLE_SP_DONGLE);
        return RACE_ERRCODE_SUCCESS;
    }
#endif
#if defined(AIR_FOTA_DONGLE_HEADSET_BY_SP_ENABLE)
    else if (RACE_FOTA_SP_TRANS_METHOD_SP_DONGLE_THROUGHOUT == sp_trans_method) {
        *channel_id = race_get_channel_id_by_port_type(MUX_BT_BLE_SP_DONGLE_THROUGHOUT);
        return RACE_ERRCODE_SUCCESS;
    }
#endif
    printk("Cannot get FOTA channel id.");
    return RACE_ERRCODE_FAIL;
}


bool race_fota_is_race_fota_running(void)
{
    if (RACE_FOTA_DOWNLOAD_STATE_NONE != race_fota_dl_state_get() &&
        RACE_FOTA_DOWNLOAD_STATE_MAX != race_fota_dl_state_get()
#ifdef RACE_FOTA_DELAY_COMMIT_ENABLE
        && RACE_FOTA_DOWNLOAD_STATE_WAIT_FOR_COMMIT != race_fota_dl_state_get()
#endif
       ) {
        return TRUE;
    }

    return FALSE;
}


bool race_fota_is_running(bool is_race_fota)
{
    if (is_race_fota) {
        return race_fota_is_race_fota_running();
    } else {
#ifdef __FOTA_FOR_BISTO__
        return fota_is_bisto_fota_running();
#else
        return FALSE;
#endif
    }
}

bool race_fota_is_busy(void)
{
    FotaStorageType type = fota_flash_get_storage_type();
    if (race_fota_is_race_fota_running() || FOTA_ERRCODE_SUCCESS != fota_check_fota_partition_is_erased(type)) {
        return TRUE;
    }
    return FALSE;
}

bool race_fota_is_cmd_allowed(race_fota_stop_reason_enum *reason, uint16_t cmd_id, uint8_t channel_id, bt_addr_t *peer_address)
{
    race_serial_port_type_enum port_type = race_get_port_type_by_channel_id(channel_id);
    race_fota_sp_trans_method_enum sp_trans_method = race_fota_sp_trans_method_get();
    race_fota_download_state_enum fota_dl_state = race_fota_dl_state_get();
    bool same_trans_method = FALSE;
    race_fota_cntx_struct *fota_cntx = race_fota_cntx_get();

    if (reason) {
        *reason = RACE_FOTA_STOP_REASON_MAX;
    }

    if ((RACE_FOTA_SP_TRANS_METHOD_UART == sp_trans_method &&
            RACE_SERIAL_PORT_TYPE_UART == port_type)
#ifdef MTK_AIRUPDATE_ENABLE
        || (RACE_FOTA_SP_TRANS_METHOD_AIRUPDATE == sp_trans_method &&
            RACE_SERIAL_PORT_TYPE_AIRUPDATE == port_type)
#endif
#ifdef MTK_IAP2_PROFILE_ENABLE
        || (RACE_FOTA_SP_TRANS_METHOD_IAP2 == sp_trans_method &&
            RACE_SERIAL_PORT_TYPE_IAP2 == port_type)
#endif
#ifdef AIR_MUX_BT_HID_ENABLE
        || (RACE_FOTA_SP_TRANS_METHOD_HID == sp_trans_method &&
            RACE_SERIAL_PORT_TYPE_HID == port_type)
#endif
        || (RACE_FOTA_SP_TRANS_METHOD_SPP == sp_trans_method &&
            RACE_SERIAL_PORT_TYPE_SPP == port_type)
        || (RACE_FOTA_SP_TRANS_METHOD_BLE == sp_trans_method &&
            RACE_SERIAL_PORT_TYPE_BLE == port_type)
        || (RACE_FOTA_SP_TRANS_METHOD_BLE_1 == sp_trans_method &&
            RACE_SERIAL_PORT_TYPE_BLE_1 == port_type)
        || (RACE_FOTA_SP_TRANS_METHOD_BLE_2 == sp_trans_method &&
            RACE_SERIAL_PORT_TYPE_BLE_2 == port_type)
#ifdef MTK_GATT_OVER_BREDR_ENABLE
        || (RACE_FOTA_SP_TRANS_METHOD_GATT_OVER_BREDR == sp_trans_method &&
            RACE_SERIAL_PORT_TYPE_GATT_OVER_BREDR == port_type)
#endif
#if defined(AIR_DONGLE_FOTA_BY_SP_ENABLE) || defined(AIR_FOTA_DONGLE_HEADSET_BY_SP_ENABLE)
        || (RACE_FOTA_SP_TRANS_METHOD_SP_DONGLE == sp_trans_method &&
            RACE_SERIAL_PORT_TYPE_BLE_SP_DONGLE == port_type)
#endif
#if defined(AIR_FOTA_DONGLE_HEADSET_BY_SP_ENABLE)
        || (RACE_FOTA_SP_TRANS_METHOD_SP_DONGLE_THROUGHOUT == sp_trans_method &&
            MUX_BT_BLE_SP_DONGLE_THROUGHOUT == port_type)
#endif
#if defined(AIR_USB_ENABLE)
        || (RACE_FOTA_SP_TRANS_METHOD_USB1 == sp_trans_method &&
            MUX_USB_COM_1 == port_type)
        || (RACE_FOTA_SP_TRANS_METHOD_USB2 == sp_trans_method &&
            MUX_USB_COM_2 == port_type)
#endif
        ) {
        same_trans_method = TRUE;
    }

    bt_addr_t *addr = (bt_addr_t *)race_get_bt_connection_addr(port_type);

    if (NULL != addr && fota_cntx) {
        if (memcmp((uint8_t *)addr, &fota_cntx->remote_address, sizeof(bt_addr_t)) == 0) {
            same_trans_method = TRUE;
        }
    }
    /*after RHO, new partner need check the address, because tool will send FOTA start(0x1c08) again*/
    if (NULL != peer_address && fota_cntx) {
        if (memcmp((uint8_t *)peer_address, &fota_cntx->remote_address, sizeof(bt_addr_t)) == 0) {
            same_trans_method = TRUE;
        }
    }

#ifdef __FOTA_FOR_BISTO__
    if (fota_is_bisto_fota_running()) {
        goto end;
    }
#endif

#ifdef RACE_CFU_ENABLE
    if (cfu_is_running()) {
        goto end;
    }
#endif
    /* Enhance: If it's the single FOTA(fota_cntx->is_dual_fota==FALSE), do not allow dual cmds. */

    /* COMMIT is to reboot the devicer for FOTA upgrade. If allowed, there's a chance that only
      * one device is rebooted.
      */

    switch (fota_dl_state) {
        case RACE_FOTA_DOWNLOAD_STATE_NONE:
        case RACE_FOTA_DOWNLOAD_STATE_MAX: {
            if (RACE_FOTA_START == cmd_id ||
                RACE_FOTA_STOP == cmd_id ||
                RACE_FOTA_COMMIT == cmd_id) {
                return TRUE;
            }
            break;
        }

        case RACE_FOTA_DOWNLOAD_STATE_STARTING: {
            if ((RACE_FOTA_START == cmd_id ||
                 RACE_FOTA_STOP == cmd_id) &&
                same_trans_method) {
                return TRUE;
            }
            break;
        }

        case RACE_FOTA_DOWNLOAD_STATE_START: {
            if (same_trans_method) {
                return TRUE;
            }

            break;
        }
#ifdef RACE_FOTA_STOP_DURING_RHO_SUPPORT
        case RACE_FOTA_DOWNLOAD_STATE_RHOING: {
            if (
#ifdef RACE_FOTA_STOP_DURING_RHO_SUPPORT
                RACE_FOTA_STOP == cmd_id  &&
#endif
                same_trans_method) {
                    return TRUE;
            }

            break;
        }
#endif
#ifdef RACE_FOTA_DELAY_COMMIT_ENABLE
        case RACE_FOTA_DOWNLOAD_STATE_WAIT_FOR_COMMIT: {
            if (RACE_FOTA_START == cmd_id ||
                RACE_FOTA_STOP == cmd_id ||
                RACE_FOTA_COMMIT == cmd_id) {
                return TRUE;
            }

            if ((RACE_FOTA_QUERY_STATE == cmd_id ||
                 RACE_FOTA_DUAL_DEVICES_QUERY_STATE == cmd_id) &&
                same_trans_method) {
                return TRUE;
            }

            if (RACE_BLUETOOTH_GET_LE_LINK_STATUS == cmd_id &&
                same_trans_method) {
                /* New start */
                if (g_race_fota_cntx_ptr) {
                    g_race_fota_cntx_ptr->old_dl_state = RACE_FOTA_DOWNLOAD_STATE_STARTING;
                    g_race_fota_cntx_ptr->dl_state = RACE_FOTA_DOWNLOAD_STATE_START;
                }
                return TRUE;
            }

            break;
        }
#endif

        case RACE_FOTA_DOWNLOAD_STATE_STOPPING: {
            race_fota_cntx_struct *fota_cntx = race_fota_cntx_get();

            if (RACE_FOTA_STOP == cmd_id && same_trans_method) {
                return TRUE;
            }

            if (fota_cntx && reason) {
                *reason = fota_cntx->reason;
                printk("stop reason:%x", fota_cntx->reason);
            }

            goto end;
        }

        case RACE_FOTA_DOWNLOAD_STATE_COMMITING: {
            if ((RACE_FOTA_COMMIT == cmd_id) &&
                same_trans_method) {
                return TRUE;
            }

            break;
        }

        default:
            break;
    }

end:
    if (reason && (*reason == RACE_FOTA_STOP_REASON_MAX)) {
        *reason = RACE_FOTA_STOP_REASON_NOT_ALLOWED;
    }
    return FALSE;
}


static RACE_ERRCODE race_fota_stop_send_req_to_sp(race_fota_stop_reason_enum reason,
                                                  uint8_t channel_id)
{
    typedef struct {
        uint8_t sender;
        uint8_t recipient;
        uint8_t reason;
    } PACKED CMD;

    CMD *pCmd = NULL;
    int32_t ret = RACE_ERRCODE_FAIL;

    printk("reason:%d channel_id:%d", reason, channel_id);

    pCmd = RACE_ClaimPacketAppID(RACE_APP_ID_FOTA,
                                 RACE_TYPE_COMMAND,
                                 RACE_FOTA_STOP,
                                 sizeof(CMD),
                                 channel_id);
    if (pCmd) {
        pCmd->sender = 0;
        pCmd->recipient = 0x80; /* SP */
        pCmd->reason = reason;

        ret = race_flush_packet((uint8_t *)pCmd, channel_id);
        if (ret != RACE_STATUS_OK) {
            RACE_FreePacket(pCmd);
        }
        ret = RACE_STATUS_OK == ret ? RACE_ERRCODE_SUCCESS : RACE_ERRCODE_FAIL;
    }

    return ret;
}


/* Pre-process the cmd with RACE_APP_ID_FOTA
  * 1. For the below cases, do not process the cmd received. If the cmd received
  *     is not 5B or 5D, send RACE_FOTA_STOP back also (or send 5B with status of failure).
  * 1). race_fota is not allowed
  * 2). race_fota is allowed and race_fota is not running and the cmd received is not FOTA_START cmd
  *     such as RACE_FOTA_START, RACE_FOTA_COMMIT
  * 2. Reset app_id timer for the cases below
  * 1). race_fota is running
  *
  * Start app_id timer within the FOTA_START cmd hdl.
  */
RACE_ERRCODE race_fota_cmd_preprocess(uint16_t cmd_id,
                                      uint8_t cmd_type,
                                      uint8_t channel_id)
{
    uint8_t app_id_timer_id = race_fota_app_id_timer_id_get();
    race_fota_stop_reason_enum reason;

    if (!race_fota_is_cmd_allowed(&reason, cmd_id, channel_id, NULL)) {
        if (RACE_TYPE_COMMAND == cmd_type ||
            RACE_TYPE_COMMAND_WITHOUT_RSP == cmd_type) {
                /* Send FOTA_STOP or send 5B with status of failure. */
                race_fota_stop_send_req_to_sp(reason, channel_id);
        }

        return RACE_ERRCODE_NOT_ALLOWED;
    }

    if (RACE_TIMER_INVALID_TIMER_ID != app_id_timer_id) {
        race_timer_smart_reset(app_id_timer_id);
    }

    return RACE_ERRCODE_SUCCESS;
}

bool race_fota_is_stop_allowed(bool *execute_stop)
{
    if (execute_stop) {
        *execute_stop = FALSE;
    }

    if (
#ifdef __FOTA_FOR_BISTO__
        fota_is_bisto_fota_running() ||
#endif
        RACE_FOTA_DOWNLOAD_STATE_COMMITING == race_fota_dl_state_get()
#ifndef RACE_FOTA_STOP_DURING_RHO_SUPPORT
        || RACE_FOTA_DOWNLOAD_STATE_RHOING == race_fota_dl_state_get()
#endif
    ) {
        return FALSE;
    }

    if (!(RACE_FOTA_DOWNLOAD_STATE_NONE == race_fota_dl_state_get() ||
          RACE_FOTA_DOWNLOAD_STATE_MAX == race_fota_dl_state_get() ||
          RACE_FOTA_DOWNLOAD_STATE_STOPPING == race_fota_dl_state_get())) {
        if (execute_stop) {
            *execute_stop = TRUE;
        }
    }

    return TRUE;
}


void race_fota_stop_agent_reset(void)
{
    void *user_data = NULL;

    race_storage_disable_fota_partition_accessibility();

    /* Reset fota status */
    fota_multi_info_sector_reset();
    /* Stop app_id timer */
    race_timer_smart_stop(race_fota_app_id_timer_id_get(), NULL);
    race_timer_smart_stop(race_fota_commit_timer_id_get(), &user_data);
    if (user_data) {
        race_mem_free(user_data);
        user_data = NULL;
    }

    /* Reset fota cntx. */
    race_fota_reset();
}


static RACE_ERRCODE race_fota_stop_agent_revert(void)
{
    race_fota_download_state_enum fota_dl_state = race_fota_dl_state_get();
    race_fota_cntx_struct *fota_cntx = race_fota_cntx_get();

    if (!fota_cntx ||
        RACE_FOTA_DOWNLOAD_STATE_STOPPING != fota_dl_state) {
        return RACE_ERRCODE_WRONG_STATE;
    }

    race_fota_dl_state_rollback();
    fota_cntx->originator = RACE_FOTA_STOP_ORIGINATOR_NONE;
    fota_cntx->reason = RACE_FOTA_STOP_REASON_MAX;
    race_timer_smart_stop(race_fota_stop_timer_id_get(), NULL);

    return RACE_ERRCODE_SUCCESS;
}


RACE_ERRCODE race_fota_stop_send_noti_to_sp(uint8_t status,
                                            uint8_t recipient,
                                            uint8_t channel_id,
                                            bool noti_delay)
{
    race_fota_stop_noti_struct *noti = NULL;
    RACE_ERRCODE ret = RACE_ERRCODE_FAIL;

    noti = (void *)RACE_ClaimPacketAppID(RACE_APP_ID_FOTA,
                                         RACE_TYPE_NOTIFICATION,
                                         RACE_FOTA_STOP,
                                         sizeof(race_fota_stop_noti_struct),
                                         channel_id);
    if (noti) {
        /* A3. Set the noti parameters with the cmd results.  */
        noti->status = status;
        noti->sender = 7;
        noti->recipient = recipient;

        /* A4. Send the noti. */
        ret = race_noti_send(noti, channel_id, noti_delay);
        if (RACE_ERRCODE_SUCCESS != ret) {
            /* A5. Free the noti if needed. */
            RACE_FreePacket(noti);
            noti = NULL;
        }
    } else {
        ret = RACE_ERRCODE_NOT_ENOUGH_MEMORY;
    }

    return ret;
}

RACE_ERRCODE race_fota_state_check(race_fota_stop_agent_sp_stop_req_struct *sp_stop_req)
{
    race_fota_cntx_struct *fota_cntx = race_fota_cntx_get();
    race_fota_download_state_enum fota_dl_state = race_fota_dl_state_get();
    if (!fota_cntx || !sp_stop_req) {
        return RACE_ERRCODE_WRONG_STATE;
    }

    if (!race_fota_is_stop_allowed(NULL)) {
        return RACE_ERRCODE_NOT_ALLOWED;
    }
    if (RACE_FOTA_DOWNLOAD_STATE_STARTING == fota_dl_state) {
        //RACE_LOG_MSGID_I("Cache FOTA_STOP during STARTING and execute it after START is done.", 0);
        /* Execute FOTA_STOP after FOTA_START is done. */
        fota_cntx->fota_stop_required = TRUE;
        return RACE_ERRCODE_SUCCESS;
    }
#ifdef RACE_FOTA_STOP_DURING_RHO_SUPPORT
    else if (RACE_FOTA_DOWNLOAD_STATE_RHOING == fota_dl_state) {
        fota_cntx->fota_stop_required = TRUE;
        return RACE_ERRCODE_SUCCESS;
    }
#endif

    if (RACE_FOTA_DOWNLOAD_STATE_STOPPING == fota_dl_state) {
        /* If multiple RACE_FOTA_STOP 5A is sent, only respond one 5D.
                 * If the originator is not SP, do not respond 5D.
                 * AGENT_ONLY will not reach here actually. Keep to extend for delaying CANCELLED event.
                 */
        return RACE_ERRCODE_SUCCESS;
    }
    return RACE_ERRCODE_FAIL;
}


RACE_ERRCODE race_fota_stop_agent_sp_stop_req_process(race_fota_stop_agent_sp_stop_req_struct *sp_stop_req)
{
    RACE_ERRCODE ret = RACE_ERRCODE_FAIL;
    race_fota_cntx_struct *fota_cntx = race_fota_cntx_get();
#ifdef RACE_FOTA_DELAY_COMMIT_ENABLE
    race_fota_download_state_enum fota_dl_state = race_fota_dl_state_get();
#endif
    if (!fota_cntx || !sp_stop_req) {
        return RACE_ERRCODE_WRONG_STATE;
    }

    if (!race_fota_is_race_fota_running()) {
#ifdef RACE_FOTA_DELAY_COMMIT_ENABLE
        if (RACE_FOTA_DOWNLOAD_STATE_WAIT_FOR_COMMIT == fota_dl_state) {
            race_fota_dl_state_set(RACE_FOTA_DOWNLOAD_STATE_NONE);
        }
#endif
        return race_fota_stop_send_noti_to_sp(RACE_ERRCODE_SUCCESS,
                                              sp_stop_req->recipient_type,
                                              sp_stop_req->channel_id,
                                              TRUE);
    }

    ret = race_fota_state_check(sp_stop_req);

    if ((RACE_ERRCODE_WRONG_STATE == ret) || (RACE_ERRCODE_NOT_ALLOWED == ret) ||
        (RACE_ERRCODE_SUCCESS == ret)) {
        return ret;
    }

    if (!((fota_cntx->is_dual_fota && RACE_RECIPIENT_TYPE_AGENT_PARTNER == sp_stop_req->recipient_type) ||
          (!fota_cntx->is_dual_fota && RACE_RECIPIENT_TYPE_AGENT_ONLY == sp_stop_req->recipient_type))) {
        return RACE_ERRCODE_NOT_SUPPORT;
    }
    if (RACE_RECIPIENT_TYPE_AGENT_ONLY == sp_stop_req->recipient_type) {
        /* Agent only */
        fota_cntx->originator = RACE_FOTA_STOP_ORIGINATOR_SP;
        fota_cntx->reason = sp_stop_req->reason;
        race_fota_dl_state_set(RACE_FOTA_DOWNLOAD_STATE_STOPPING);
        race_event_send_fota_cancelling_event(fota_cntx->originator,
                                              fota_cntx->reason);
        race_fota_stop_send_noti_to_sp(RACE_ERRCODE_SUCCESS,
                                       sp_stop_req->recipient_type,
                                       sp_stop_req->channel_id,
                                       TRUE);
        /* Even if 5D is not sent successfully, still stop FOTA. */
        race_event_send_fota_cancel_event(TRUE,
                                          fota_cntx->originator,
                                          fota_cntx->reason);
        race_fota_stop_agent_reset();
        ret = RACE_ERRCODE_SUCCESS;
    }else {
        /* Never reach here actually. Keep to extend for PARTNER_ONLY maybe. */
        ret = RACE_ERRCODE_NOT_SUPPORT;
    }

    return ret;
}


static RACE_ERRCODE race_fota_stop_agent_active_stop_process(race_fota_stop_agent_active_stop_struct *active_stop)
{
    RACE_ERRCODE ret = RACE_ERRCODE_SUCCESS;
    race_fota_cntx_struct *fota_cntx = race_fota_cntx_get();
    race_fota_download_state_enum fota_dl_state = race_fota_dl_state_get();
    race_fota_stop_agent_sp_stop_noti_struct sp_stop_noti = {0};

    if (!fota_cntx || !active_stop) {
        return RACE_ERRCODE_WRONG_STATE;
    }

    sp_stop_noti.recipient_type = active_stop->recipient_type;

    if (!race_fota_is_race_fota_running()) {
#ifdef RACE_FOTA_DELAY_COMMIT_ENABLE
        if (RACE_FOTA_DOWNLOAD_STATE_WAIT_FOR_COMMIT == fota_dl_state) {
            race_fota_dl_state_set(RACE_FOTA_DOWNLOAD_STATE_NONE);
        }
#endif
        return RACE_ERRCODE_SUCCESS;
    }

    if (!race_fota_is_stop_allowed(NULL)) {
        return RACE_ERRCODE_NOT_ALLOWED;
    }

    if (RACE_FOTA_STOP_REASON_UNEXPECTED_RHO_DONE == active_stop->reason ||
        RACE_FOTA_STOP_REASON_UNEXPECTED_RHO_ONGOING == active_stop->reason) {
        /* FOTA stop may be interrupted by RHO triggered by non-FOTA modules. In such case,
         * FOTA procedure is interrupted and it's hard or impossible to recover the previous FOTA
         * stop procedure. Therefore, reset FOTA directly no matter if it's STOPPING or not. Also,
         * it's simple and reliable to reset FOTA directly when it's other state, such as STARTING.
         * SP retry mechanism will discover the failure.
         */
        if (RACE_FOTA_DOWNLOAD_STATE_STOPPING != fota_dl_state) {
            fota_cntx->originator = active_stop->originator;
            fota_cntx->reason = active_stop->reason;
            race_fota_dl_state_set(RACE_FOTA_DOWNLOAD_STATE_STOPPING);
            race_event_send_fota_cancelling_event(fota_cntx->originator, fota_cntx->reason);
        }
        race_event_send_fota_cancel_event(TRUE,
                                          fota_cntx->originator,
                                          fota_cntx->reason);
        race_fota_stop_agent_reset();
        return RACE_ERRCODE_SUCCESS;
    }

    if (RACE_FOTA_STOP_REASON_SP_LOST == active_stop->reason ||
        RACE_FOTA_STOP_REASON_BT_OFF == active_stop->reason) {
        /* SPP/BLE DISC event may be received after RHO_RESULT event. In such case,
         * fota_cntx->sp_online has not been set FALSE by DISC event.
         */
        /*RACE_LOG_MSGID_W("Set sp_online:%d to FALSE actively for reason:%d", 2,
                         fota_cntx->sp_online, active_stop->reason);*/
        fota_cntx->sp_online = FALSE;
    }

    if (RACE_FOTA_DOWNLOAD_STATE_STARTING == fota_dl_state) {
        //RACE_LOG_MSGID_I("Cache FOTA_STOP during STARTING and execute it after START is done.", 0);
        /* Execute FOTA_STOP after FOTA_START is done. */
        fota_cntx->fota_stop_required = TRUE;
        return RACE_ERRCODE_SUCCESS;
    }
#ifdef RACE_FOTA_STOP_DURING_RHO_SUPPORT
    else if (RACE_FOTA_DOWNLOAD_STATE_RHOING == fota_dl_state) {
        fota_cntx->fota_stop_required = TRUE;
        return RACE_ERRCODE_SUCCESS;
    }
#endif

    if (RACE_FOTA_DOWNLOAD_STATE_STOPPING == fota_dl_state) {
        if ((RACE_FOTA_STOP_REASON_SP_LOST == active_stop->reason ||
             RACE_FOTA_STOP_REASON_BT_OFF == active_stop->reason) &&
            (RACE_FOTA_STOP_STATUS_WAIT_FOR_5B == fota_cntx->stop_status ||
             RACE_FOTA_STOP_STATUS_WAIT_FOR_5D == fota_cntx->stop_status)) {
            sp_stop_noti.status = RACE_ERRCODE_SUCCESS;
            return race_fota_stop_agent_sp_stop_noti_process(&sp_stop_noti);
        }

        return RACE_ERRCODE_SUCCESS;
    }

    if (RACE_RECIPIENT_TYPE_AGENT_ONLY == active_stop->recipient_type) {
        uint8_t timer_id = race_fota_stop_timer_id_get();

        fota_cntx->originator = active_stop->originator;
        fota_cntx->reason = active_stop->reason;
        race_fota_dl_state_set(RACE_FOTA_DOWNLOAD_STATE_STOPPING);
        race_event_send_fota_cancelling_event(fota_cntx->originator,
                                              fota_cntx->reason);

        /* Send RACE_FOTA_STOP REQ(5A) to SP */
        if (fota_cntx->sp_online) {
            ret = race_fota_stop_send_req_to_sp(fota_cntx->reason,
                                                active_stop->channel_id);
        }

        if (!fota_cntx->sp_online ||
            RACE_ERRCODE_SUCCESS != ret) {
            /* Failed to send 5A. Stop FOTA immediately. */
            sp_stop_noti.status = RACE_ERRCODE_SUCCESS;
            fota_cntx->stop_status = RACE_FOTA_STOP_STATUS_WAIT_FOR_5D;
            return race_fota_stop_agent_sp_stop_noti_process(&sp_stop_noti);
        } else {
            /* Start timer and wait for 5B/5D from SP. */
            if (RACE_TIMER_INVALID_TIMER_ID == timer_id) {
                ret = race_timer_smart_start(&timer_id,
                                             RACE_FOTA_AGENT_STOP_TIMEOUT_IN_MS,
                                             race_fota_stop_timer_expiration_hdl,
                                             NULL);
                if (RACE_ERRCODE_SUCCESS == ret) {
                    race_fota_stop_timer_id_set(timer_id);
                }
            } else {
                /* There must be something wrong. Stop FOTA immediately. */
                ret = RACE_ERRCODE_FAIL;
            }

            if (RACE_ERRCODE_SUCCESS == ret) {
                fota_cntx->stop_status = RACE_FOTA_STOP_STATUS_WAIT_FOR_5B;
            } else {
                /* Failed to start the stop timer or something wrong happened.
                               * Stop FOTA immediately for 5D may not be received. */
                sp_stop_noti.status = RACE_ERRCODE_SUCCESS;
                fota_cntx->stop_status = RACE_FOTA_STOP_STATUS_WAIT_FOR_5D;
                return race_fota_stop_agent_sp_stop_noti_process(&sp_stop_noti);
            }
        }
    }else {
        ret = RACE_ERRCODE_NOT_SUPPORT;
    }

    return ret;
}


RACE_ERRCODE race_fota_stop_agent_sp_stop_noti_process(race_fota_stop_agent_sp_stop_noti_struct *sp_stop_noti)
{
    RACE_ERRCODE ret = RACE_ERRCODE_SUCCESS;
    race_fota_cntx_struct *fota_cntx = race_fota_cntx_get();
    race_fota_download_state_enum fota_dl_state = race_fota_dl_state_get();

    if (!fota_cntx || !sp_stop_noti ||
        RACE_FOTA_DOWNLOAD_STATE_STOPPING != fota_dl_state ||
        (RACE_FOTA_STOP_STATUS_WAIT_FOR_5B != fota_cntx->stop_status &&
         RACE_FOTA_STOP_STATUS_WAIT_FOR_5D != fota_cntx->stop_status)) {
        /*RACE_LOG_MSGID_W("fota_cntx:%x is_dual_fota:%d fota_dl_state:%d stop_status:%d", 4,
                         fota_cntx,
                         fota_cntx ? fota_cntx->is_dual_fota : FALSE,
                         fota_dl_state,
                         fota_cntx ? fota_cntx->stop_status : RACE_FOTA_STOP_STATUS_MAX);*/
        return RACE_ERRCODE_WRONG_STATE;
    }

    if (RACE_FOTA_STOP_ORIGINATOR_AGENT == fota_cntx->originator
#ifdef RACE_FOTA_CANCEL_FROM_PARTNER_ENABLE
        || RACE_FOTA_STOP_ORIGINATOR_PARTNER == fota_cntx->originator
#endif
       ) {
        if (RACE_RECIPIENT_TYPE_AGENT_ONLY == sp_stop_noti->recipient_type) {
            if (RACE_ERRCODE_SUCCESS == sp_stop_noti->status) {
                race_event_send_fota_cancel_event(TRUE,
                                                  RACE_FOTA_STOP_ORIGINATOR_AGENT,
                                                  RACE_FOTA_STOP_REASON_CANCEL);
                race_fota_stop_agent_reset();
            } else {
                race_event_send_fota_cancel_event(FALSE,
                                                  fota_cntx->originator,
                                                  fota_cntx->reason);
                race_fota_stop_agent_revert();
            }
        }else {
            ret = RACE_ERRCODE_NOT_SUPPORT;
        }
    } else {
        ret = RACE_ERRCODE_WRONG_STATE;
    }

    return ret;
}


RACE_ERRCODE race_fota_stop_agent_sp_stop_rsp_process(race_fota_stop_agent_sp_stop_rsp_struct *sp_stop_rsp)
{
    RACE_ERRCODE ret = RACE_ERRCODE_SUCCESS;
    race_fota_cntx_struct *fota_cntx = race_fota_cntx_get();
    race_fota_download_state_enum fota_dl_state = race_fota_dl_state_get();

    if (!fota_cntx || !sp_stop_rsp ||
        RACE_FOTA_DOWNLOAD_STATE_STOPPING != fota_dl_state ||
        RACE_FOTA_STOP_STATUS_WAIT_FOR_5B != fota_cntx->stop_status) {
        /*RACE_LOG_MSGID_W("fota_cntx:%x sp_stop_rsp:%x fota_dl_state:%d stop_status:%d", 4,
                         fota_cntx,
                         sp_stop_rsp,
                         fota_dl_state,
                         fota_cntx ? fota_cntx->stop_status : RACE_FOTA_STOP_STATUS_MAX);*/
        return RACE_ERRCODE_WRONG_STATE;
    }

    if (RACE_FOTA_STOP_ORIGINATOR_AGENT == fota_cntx->originator) {
        if (RACE_RECIPIENT_TYPE_AGENT_ONLY == sp_stop_rsp->recipient_type) {
            if (RACE_ERRCODE_SUCCESS == sp_stop_rsp->status) {
                fota_cntx->stop_status = RACE_FOTA_STOP_STATUS_WAIT_FOR_5D;
            } else {
                race_fota_stop_agent_sp_stop_noti_struct sp_stop_noti = {0};

                sp_stop_noti.recipient_type = sp_stop_rsp->recipient_type;
                sp_stop_noti.status = sp_stop_rsp->status;

                fota_cntx->stop_status = RACE_FOTA_STOP_STATUS_WAIT_FOR_5D;
                return race_fota_stop_agent_sp_stop_noti_process(&sp_stop_noti);
            }
        } else {
            ret = RACE_ERRCODE_NOT_SUPPORT;
        }
    } else {
        ret = RACE_ERRCODE_WRONG_STATE;
    }

    return ret;
}


/* Send FOTA_STOP MSG to race task. */
RACE_ERRCODE race_fota_stop(race_fota_stop_originator_enum originator,
                            race_fota_stop_reason_enum reason)
{
#ifdef RACE_FOTA_DELAY_COMMIT_ENABLE
    race_fota_download_state_enum fota_dl_state = race_fota_dl_state_get();
#endif
    race_general_msg_t msg_queue_item = {0};
    race_fota_stop_msg_data_struct *msg_data = NULL;
    RACE_ERRCODE ret = RACE_ERRCODE_FAIL;


    printk("race_fota_stop originator:%d reason:%d", originator, reason);

    if (!g_race_fota_cntx_ptr) {
        return RACE_ERRCODE_SUCCESS;
    }

#ifndef RACE_FOTA_CANCEL_FROM_PARTNER_ENABLE
    if (RACE_FOTA_STOP_ORIGINATOR_PARTNER == originator) {
        return RACE_ERRCODE_NOT_SUPPORT;
    }
#endif

    if (!race_fota_is_race_fota_running()) {
#ifdef RACE_FOTA_DELAY_COMMIT_ENABLE
        if (RACE_FOTA_DOWNLOAD_STATE_WAIT_FOR_COMMIT == fota_dl_state) {
            // TODO: Need mutex for it's running in multiple tasks.
            race_fota_dl_state_set(RACE_FOTA_DOWNLOAD_STATE_NONE);
        }
#endif

        return RACE_ERRCODE_SUCCESS;
    }

    if (!race_fota_is_stop_allowed(NULL)) {
        return RACE_ERRCODE_NOT_ALLOWED;
    }

    /* Send FOTA_STOP MSG to race cmd task. */
    msg_data = race_mem_alloc(sizeof(race_fota_stop_msg_data_struct));
    if (!msg_data) {
        return RACE_ERRCODE_NOT_ENOUGH_MEMORY;
    }

    msg_data->originator = originator;
    msg_data->reason = reason;
    msg_data->recipient_type = g_race_fota_cntx_ptr->is_dual_fota ? RACE_RECIPIENT_TYPE_AGENT_PARTNER : RACE_RECIPIENT_TYPE_AGENT_ONLY;
#ifdef RACE_FOTA_CANCEL_FROM_PARTNER_ENABLE
    if (RACE_FOTA_STOP_ORIGINATOR_PARTNER == originator) {
        msg_data->recipient_type = RACE_RECIPIENT_TYPE_AGENT_PARTNER;
    }
#endif

    msg_queue_item.msg_id = MSG_ID_RACE_LOCAL_FOTA_STOP_IND;
    msg_queue_item.msg_data = (uint8_t *)msg_data;
    ret = race_send_msg(&msg_queue_item);
    if (RACE_ERRCODE_SUCCESS != ret) {
        //RACE_LOG_MSGID_W("Failed to send msg:%d. ret:%d", 2, MSG_ID_RACE_LOCAL_FOTA_STOP_IND, ret);
        race_mem_free((void *)msg_data);
    }
#ifndef AIR_BTA_IC_PREMIUM_G2
#if defined (AIR_BLE_ULTRA_LOW_LATENCY_WITH_HID_ENABLE) && defined (AIR_HEADSET_ENABLE)
    extern void DisableForcingAirCisScheduling(void);
    DisableForcingAirCisScheduling();
#endif
#endif
    return ret;
}


RACE_ERRCODE race_fota_stop_msg_process(race_general_msg_t *msg)
{
    RACE_ERRCODE ret = RACE_ERRCODE_SUCCESS;
    race_fota_stop_msg_data_struct *msg_data = NULL;
    uint8_t channel_id = 0;

    if (!msg || !msg->msg_data || !g_race_fota_cntx_ptr) {
        return RACE_ERRCODE_PARAMETER_ERROR;
    }

    msg_data = (race_fota_stop_msg_data_struct *)msg->msg_data;

    /*RACE_LOG_MSGID_I("stop_status:%d curr_originator:%d curr_reason:%x", 3,
                     g_race_fota_cntx_ptr->stop_status,
                     g_race_fota_cntx_ptr->originator,
                     g_race_fota_cntx_ptr->reason);*/

    ret = race_fota_channel_id_get(&channel_id);
    if (RACE_ERRCODE_SUCCESS != ret) {
        return ret;
    }

    /* Do not care if msg_data->originator is Agent or not. FOTA stop is only marked
            * during RHO and will be executed after RHO. If FOTA is stopped during RHO with
            * the originator of Partner by then. After RHO is done succesfully, the role is changed
            * to Agent. originator and role will not match. So ignore originator here.
            */
    race_fota_stop_agent_active_stop_struct agent_active_stop = {0};

    agent_active_stop.channel_id = channel_id;
    agent_active_stop.originator = msg_data->originator;
    agent_active_stop.reason = msg_data->reason;
    agent_active_stop.recipient_type = msg_data->recipient_type;

    return race_fota_stop_agent_active_stop_process(&agent_active_stop);
}


RACE_ERRCODE race_fota_cancel(void)
{
    return race_fota_stop(RACE_FOTA_STOP_ORIGINATOR_AGENT, RACE_FOTA_STOP_REASON_CANCEL);
}


RACE_ERRCODE race_fota_integrity_check(uint32_t signature_start_address,
                                       uint8_t storage_type,
                                       uint8_t *signature_generated,
                                       uint8_t signature_generated_size)
{
    unsigned char signature_in_fota_partition[RACE_STORAGE_SIGNATURE_MAX_SIZE] = {0};
    int32_t ret = RACE_ERRCODE_FAIL;

    if (!signature_generated || !signature_generated_size ||
        RACE_STORAGE_SIGNATURE_MAX_SIZE < signature_generated_size) {
        printk("signature_generated:%x signature_generated_size:%d", signature_generated, signature_generated_size);
        return RACE_ERRCODE_PARAMETER_ERROR;
    }

    ret = fota_flash_read(signature_start_address,
                          signature_in_fota_partition,
                          signature_generated_size);
    if (true == ret) {
        if (strncmp((const char *)signature_in_fota_partition, (const char *)signature_generated, signature_generated_size) != 0) {
            ret = FOTA_ERRCODE_CHECK_INTEGRITY_FAIL;
        } else {
            ret = fota_dl_integrity_res_write(FOTA_DL_INTEGRITY_RES_VAL_PASS);
        }
    }

    ret = FOTA_ERRCODE_SUCCESS == ret ? RACE_ERRCODE_SUCCESS : RACE_ERRCODE_CHECK_INTEGRITY_FAIL;
    return ret;
}


#ifdef MTK_RACE_EVENT_ID_ENABLE
static RACE_ERRCODE race_fota_race_event_cb(int32_t register_id, race_event_type_enum event_type, void *param, void *user_data)
#else
static RACE_ERRCODE race_fota_race_event_cb(race_event_type_enum event_type, void *param, void *user_data)
#endif
{
    race_fota_cntx_struct *fota_cntx = race_fota_cntx_get();
    race_fota_sp_trans_method_enum sp_trans_method = race_fota_sp_trans_method_get();

#ifdef MTK_RACE_EVENT_ID_ENABLE
    printk("register_id:%d event_type:%d", register_id, event_type);

    if (!fota_cntx || register_id != g_race_fota_event_register_id) {
        /*RACE_LOG_MSGID_E("register_id does not match! register_id:%d, g_register_id:%d", 2,
                         register_id,
                         g_race_fota_event_register_id);*/
        return RACE_ERRCODE_PARAMETER_ERROR;
    }
#else
    printk("event_type:%d param:%x user_data:%x", event_type, param, user_data);

    if (!fota_cntx) {
        return RACE_ERRCODE_PARAMETER_ERROR;
    }
#endif

    switch (event_type) {
        case RACE_EVENT_TYPE_CONN_BLE_DISCONNECT:
        case RACE_EVENT_TYPE_CONN_SPP_DISCONNECT:
        case RACE_EVENT_TYPE_CONN_BLE_1_DISCONNECT:
        case RACE_EVENT_TYPE_CONN_BLE_2_DISCONNECT:
#if defined(AIR_DONGLE_FOTA_BY_SP_ENABLE) || defined(AIR_FOTA_DONGLE_HEADSET_BY_SP_ENABLE)
        case RACE_EVENT_TYPE_CONN_BLE_SP_DONGLE_DISCONNECT:
#endif
#if defined(AIR_FOTA_DONGLE_HEADSET_BY_SP_ENABLE)
        case RACE_EVENT_TYPE_CONN_SP_DONGLE_THROUGHOUT_DISCONNECT:
#endif
#ifdef AIR_MUX_BT_HID_ENABLE
        case RACE_EVENT_TYPE_CONN_HID_DISCONNECT:
#endif
#ifdef MTK_AIRUPDATE_ENABLE
        case RACE_EVENT_TYPE_CONN_AIRUPDATE_DISCONNECT:
#endif
#ifdef MTK_IAP2_PROFILE_ENABLE
        case RACE_EVENT_TYPE_CONN_IAP2_DISCONNECT:
#endif
#ifdef MTK_GATT_OVER_BREDR_ENABLE
        case RACE_EVENT_TYPE_CONN_GATT_OVER_BREDR_DISCONNECT:
#endif
        case RACE_EVENT_TYPE_CONN_USB_DISCONNECT: {
            /* DISC event caused by RHO may be received when RHO has already been done for BT task's
             * priority is higher than race task's. If RHO fails, Agent receives it and do nothing and let FOTA
             * err be handled within RHO_RESULT event behind it. If RHO succeeds, Partner receives it and
             * nothing need be done.
             */
#ifdef AIR_FOTA_DONGLE_HEADSET_BY_SP_ENABLE
            /* when dongle is disconnect to sp, need notify headset to stop fota.*/
            if (event_type == RACE_EVENT_TYPE_CONN_SP_DONGLE_THROUGHOUT_DISCONNECT) {
                if (race_bt_is_connected(MUX_BT_BLE)) {
                    typedef struct {
                        uint8_t sender;
                        uint8_t recipient;
                        uint8_t reason;
                    } PACKED CMD;

                    CMD *pCmd = NULL;
                    int32_t ret = RACE_ERRCODE_FAIL;
                    uint8_t channel_id = MUX_BT_BLE;
                    pCmd = RACE_ClaimPacketAppID(RACE_APP_ID_FOTA,
                                                 RACE_TYPE_COMMAND_WITHOUT_RSP,
                                                 RACE_FOTA_STOP,
                                                 sizeof(CMD),
                                                 channel_id);
                    if (pCmd) {
                        pCmd->sender = 0x07;
                        pCmd->recipient = 0x03; /*agent&partner*/
                        pCmd->reason = RACE_FOTA_STOP_REASON_SP_LOST;
                        ret = race_flush_packet((uint8_t *)pCmd, channel_id);
                        printk("SP disc to dongle,ret = %x", ret);
                        if (ret != RACE_STATUS_OK) {
                            RACE_FreePacket(pCmd);
                        }
                    }
                } else {
                        printk("MUX_BT_BLE is disconnected ");
                }
            }
#endif
            race_fota_download_state_enum fota_dl_state = race_fota_dl_state_get();

            /*RACE_LOG_MSGID_I("fota_cntx:%x dl_state:%d trans_method:%d", 3,
                                fota_cntx,
                                fota_dl_state,
                                sp_trans_method);*/
            if (fota_cntx && race_fota_is_race_fota_running()) {
                if ((RACE_FOTA_SP_TRANS_METHOD_SPP == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_SPP_DISCONNECT == event_type) ||
                    (RACE_FOTA_SP_TRANS_METHOD_BLE == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_BLE_DISCONNECT == event_type)
#ifdef MTK_AIRUPDATE_ENABLE
                    || (RACE_FOTA_SP_TRANS_METHOD_AIRUPDATE == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_AIRUPDATE_DISCONNECT == event_type)
#endif
#ifdef MTK_IAP2_PROFILE_ENABLE
                    || (RACE_FOTA_SP_TRANS_METHOD_IAP2 == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_IAP2_DISCONNECT == event_type)
#endif
#ifdef MTK_GATT_OVER_BREDR_ENABLE
                    || (RACE_FOTA_SP_TRANS_METHOD_GATT_OVER_BREDR == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_GATT_OVER_BREDR_DISCONNECT == event_type)
#endif
                    || (RACE_FOTA_SP_TRANS_METHOD_USB1 == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_USB_DISCONNECT == event_type)
                    || (RACE_FOTA_SP_TRANS_METHOD_USB2 == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_USB_DISCONNECT == event_type)
                    || (RACE_FOTA_SP_TRANS_METHOD_BLE_1 == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_BLE_1_DISCONNECT == event_type)
                    || (RACE_FOTA_SP_TRANS_METHOD_BLE_2 == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_BLE_2_DISCONNECT == event_type)
#ifdef AIR_MUX_BT_HID_ENABLE
                    || (RACE_FOTA_SP_TRANS_METHOD_HID == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_HID_DISCONNECT == event_type)
#endif
#if defined(AIR_DONGLE_FOTA_BY_SP_ENABLE) || defined(AIR_FOTA_DONGLE_HEADSET_BY_SP_ENABLE)
                    || (RACE_FOTA_SP_TRANS_METHOD_SP_DONGLE == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_BLE_SP_DONGLE_DISCONNECT == event_type)
#endif
#if defined(AIR_FOTA_DONGLE_HEADSET_BY_SP_ENABLE)
                    || (RACE_FOTA_SP_TRANS_METHOD_SP_DONGLE_THROUGHOUT == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_SP_DONGLE_THROUGHOUT_DISCONNECT == event_type)
#endif
                    ) {
#ifdef CONFIG_BT_PKA_LIB_MULTI_PROTOCOL
                    if (RACE_FOTA_SP_TRANS_METHOD_BLE == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_BLE_DISCONNECT == event_type) {
                        IEEE802154_Controller_DisableBle();
                    }
#endif
                    fota_cntx->sp_online = FALSE;
                    if (RACE_FOTA_DOWNLOAD_STATE_COMMITING == fota_dl_state) {
                        /* Do nothing for it's caused by reboot procedure triggered by FOTA COMMIT. Even if
                                                        * the disconnection occurs before COMMIT CMD procedure finishes, it's OK to do
                                                        * nothing for it's not AWS detach and Agent will decide FOTA fail or reboot on
                                                        * receiving rsp from the partner.  */
                        // TODO: Handle SP disconnects SPP / BLE immediately on receiving 5B of COMMIT cmd
                        /* If SP disconnects SPP / BLE immediately on receiving 5B of COMMIT cmd, AWS may detach
                                                        * before Agent receives the commit RSP from the Partner. (5D of COMMIT may need in such case)
                                                        * Currently SP does not disconnect SPP / BLE on receiving 5B of COMMIT cmd.
                                                        */
                        printk("SPP/BLE Disc. It's FOTA COMMITING");
                    } else {
                        /* Link loss */
                        printk("SPP/BLE Disc. Stop FOTA for Link lost");
                        race_fota_stop(RACE_FOTA_STOP_ORIGINATOR_AGENT, RACE_FOTA_STOP_REASON_SP_LOST);
                    }
                }
                /* else FOTA should not care the DISC event of the trans method which it is not using.
                                    * Even if RHO may be able to executed when BLE is connected, RHO service needs
                                    * to notify FOTA to disconnect BLE before RHO if FOTA uses BLE connection.
                                    */
            }
            break;
        }

        case RACE_EVENT_TYPE_CONN_BLE_CONNECT:
        case RACE_EVENT_TYPE_CONN_SPP_CONNECT:
        case RACE_EVENT_TYPE_CONN_BLE_1_CONNECT:
        case RACE_EVENT_TYPE_CONN_BLE_2_CONNECT:
#if defined(AIR_DONGLE_FOTA_BY_SP_ENABLE) || defined(AIR_FOTA_DONGLE_HEADSET_BY_SP_ENABLE)
        case RACE_EVENT_TYPE_CONN_BLE_SP_DONGLE_CONNECT:
#endif
#if defined(AIR_FOTA_DONGLE_HEADSET_BY_SP_ENABLE)
        case RACE_EVENT_TYPE_CONN_SP_DONGLE_THROUGHOUT_CONNECT:
#endif
#ifdef AIR_MUX_BT_HID_ENABLE
        case RACE_EVENT_TYPE_CONN_HID_CONNECT:
#endif
#ifdef MTK_AIRUPDATE_ENABLE
        case RACE_EVENT_TYPE_CONN_AIRUPDATE_CONNECT:
#endif
#ifdef MTK_IAP2_PROFILE_ENABLE
        case RACE_EVENT_TYPE_CONN_IAP2_CONNECT:
#endif
#ifdef MTK_GATT_OVER_BREDR_ENABLE
        case RACE_EVENT_TYPE_CONN_GATT_OVER_BREDR_CONNECT:
#endif
        case RACE_EVENT_TYPE_CONN_USB_CONNECT: {
            if (fota_cntx && race_fota_is_race_fota_running()) {
                if ((RACE_FOTA_SP_TRANS_METHOD_SPP == sp_trans_method &&
                     RACE_EVENT_TYPE_CONN_SPP_CONNECT == event_type) ||
                    (RACE_FOTA_SP_TRANS_METHOD_BLE == sp_trans_method &&
                     RACE_EVENT_TYPE_CONN_BLE_CONNECT == event_type)
#ifdef MTK_AIRUPDATE_ENABLE
                    || (RACE_FOTA_SP_TRANS_METHOD_AIRUPDATE == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_AIRUPDATE_CONNECT == event_type)
#endif
#ifdef MTK_IAP2_PROFILE_ENABLE
                    || (RACE_FOTA_SP_TRANS_METHOD_IAP2 == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_IAP2_CONNECT == event_type)
#endif
#ifdef MTK_GATT_OVER_BREDR_ENABLE
                    || (RACE_FOTA_SP_TRANS_METHOD_GATT_OVER_BREDR == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_GATT_OVER_BREDR_CONNECT == event_type)
#endif
                    || (RACE_FOTA_SP_TRANS_METHOD_USB1 == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_USB_CONNECT == event_type)
                    || (RACE_FOTA_SP_TRANS_METHOD_USB2 == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_USB_CONNECT == event_type)
                    || (RACE_FOTA_SP_TRANS_METHOD_BLE_1 == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_BLE_1_CONNECT == event_type)
                    || (RACE_FOTA_SP_TRANS_METHOD_BLE_2 == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_BLE_2_CONNECT == event_type)
#ifdef AIR_MUX_BT_HID_ENABLE
                    || (RACE_FOTA_SP_TRANS_METHOD_HID == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_HID_CONNECT == event_type)
#endif
#if defined(AIR_DONGLE_FOTA_BY_SP_ENABLE) || defined(AIR_FOTA_DONGLE_HEADSET_BY_SP_ENABLE)
                    || (RACE_FOTA_SP_TRANS_METHOD_SP_DONGLE == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_BLE_SP_DONGLE_CONNECT == event_type)
#endif
#if defined(AIR_FOTA_DONGLE_HEADSET_BY_SP_ENABLE)
                    || (RACE_FOTA_SP_TRANS_METHOD_SP_DONGLE_THROUGHOUT == sp_trans_method &&
                        RACE_EVENT_TYPE_CONN_SP_DONGLE_THROUGHOUT_CONNECT == event_type)
#endif
                    ) {
                    /* Works only after RHO because only after SPP/BLE is connected, will fota be running
                                       * if it's starting FOTA. Set TRUE here to allow to continue FOTA without RACE_FOTA_START cmd.
                                       */
                    fota_cntx->sp_online = TRUE;
                }
            }
            break;
        }

        case RACE_EVENT_TYPE_FOTA_NEED_REBOOT: {
            /* Process the need reboot event sent by FOTA. */
            /* Do the things before reboot - start */

            hal_wdt_software_reset();

            hal_sleep_manager_unlock_sleep(SLEEP_LOCK_RACE_CMD);
            /* Do the things before reboot - end */
            /* UI shell will handle all reboot requests. Do not reboot here. */
            break;
        }

        case RACE_EVENT_TYPE_FOTA_START: {
            /* Process the FOTA start event. */
            race_event_start_param_struct *start_param = (race_event_start_param_struct *)param;
            if (start_param) {
                printk("FOTA Start. is_dual_fota:%d is_active_fota:%d",
                                    start_param ? start_param->is_dual_fota : 0xff,
                                    start_param ? start_param->is_active_fota : 0xff);
            }
#ifdef AIR_BT_AIR_SERVICE_ENABLE
            ble_air_link_performace_optimization();
#endif
#ifdef AIR_PURE_GAMING_DONGLE_ENABLE
            race_fota_dongle_disconnect_ms_kb();
#endif
#ifdef RACE_FOTA_ACTIVE_MODE_ENABLE
            /* If FOTA is not running, race_fota_is_active_mode() will return FALSE and it will revert also. */
            if (race_fota_is_active_mode()) {
                race_app_fota_active_mode_process();
            } else {
                race_app_fota_active_mode_process_revert();
            }
#endif
#ifdef RACE_FOTA_CMD_ENABLE
            // if (RACE_FOTA_MODE_BACKGROUND != race_fota_get_fota_mode()) {
#ifdef HAL_DVFS_MODULE_ENABLED
                hal_dvfs_lock_control(HAL_DVFS_OPP_HIGH, HAL_DVFS_LOCK);
#endif
                g_race_fota_dvfs_locked = true;
            // }
#endif
            break;
        }

        case RACE_EVENT_TYPE_FOTA_CANCEL: {
            /* Process the FOTA cancel event. */
            race_event_cancel_param_struct *cancel_param = (race_event_cancel_param_struct *)param;

            if (cancel_param) {
                printk("FOTA STOP result:%d origiantor:%d reason:%d.",
                                          cancel_param->result,
                                          cancel_param->originator,
                                          cancel_param->reason);
            }
#ifdef AIR_BT_AIR_SERVICE_ENABLE
            ble_air_link_performace_optimization_revert();
#endif
#ifdef AIR_PURE_GAMING_DONGLE_ENABLE
            race_fota_dongle_reconnect_ms_kb();
#endif

#ifdef RACE_FOTA_ACTIVE_MODE_ENABLE
            /* No matter if it is in the active mode or not, just revert. If it's backgroud FOTA, nothing will happen. */
            race_app_fota_active_mode_process_revert();
#endif
#ifdef RACE_FOTA_CMD_ENABLE
            if (g_race_fota_dvfs_locked) {
#ifdef HAL_DVFS_MODULE_ENABLED
                hal_dvfs_lock_control(HAL_DVFS_OPP_HIGH, HAL_DVFS_UNLOCK);
#endif
                g_race_fota_dvfs_locked = false;
            }
#endif
            break;
        }

        default:
            break;
    }

    return RACE_ERRCODE_SUCCESS;
}


RACE_ERRCODE race_fota_get_transmit_interval(uint16_t *spp_transmit_interval, uint16_t *ble_transmit_interval)
{
    if (!spp_transmit_interval && !ble_transmit_interval) {
        return RACE_ERRCODE_PARAMETER_ERROR;
    }

    if (spp_transmit_interval) {
        *spp_transmit_interval = g_race_fota_spp_transmit_interval;
    }

    if (ble_transmit_interval) {
        *ble_transmit_interval = g_race_fota_ble_transmit_interval;
    }

    return RACE_ERRCODE_SUCCESS;
}


RACE_ERRCODE race_fota_set_transmit_interval(uint16_t spp_transmit_interval, uint16_t ble_transmit_interval)
{
    g_race_fota_spp_transmit_interval = spp_transmit_interval;
    g_race_fota_ble_transmit_interval = ble_transmit_interval;

    return RACE_ERRCODE_SUCCESS;
}


#ifdef RACE_FOTA_ACTIVE_MODE_KEEP_HFP
bool race_fota_is_hfp_active(void)
{
    bt_sink_srv_state_t srv_state = bt_sink_srv_get_state();
#ifdef AIR_LE_AUDIO_ENABLE
    bt_sink_srv_cap_am_mode mode = bt_sink_srv_cap_am_get_current_mode(); // LEA CALL
    printk("race_fota_is_hfp_active->mode:%x", mode);
#endif
    if (BT_SINK_SRV_STATE_INCOMING == srv_state ||
        BT_SINK_SRV_STATE_OUTGOING == srv_state ||
        BT_SINK_SRV_STATE_ACTIVE == srv_state ||
        BT_SINK_SRV_STATE_TWC_INCOMING == srv_state ||
        BT_SINK_SRV_STATE_TWC_OUTGOING == srv_state ||
        BT_SINK_SRV_STATE_HELD_ACTIVE == srv_state ||
        BT_SINK_SRV_STATE_HELD_REMAINING == srv_state ||
        BT_SINK_SRV_STATE_MULTIPARTY == srv_state
#ifdef AIR_LE_AUDIO_ENABLE
        || mode <= CAP_AM_UNICAST_CALL_MODE_END
#endif
        ) {
        return TRUE;
    }

    return FALSE;
}
#endif


RACE_ERRCODE race_fota_is_fota_mode_allowed(race_fota_mode_enum fota_mode)
{
    if (RACE_FOTA_MODE_MAX <= fota_mode
#ifndef RACE_FOTA_ACTIVE_MODE_ENABLE
        || RACE_FOTA_MODE_ACTIVE == fota_mode
#endif
#ifndef RACE_FOTA_ADAPTIVE_MODE_ENABLE
        || RACE_FOTA_MODE_ADAPTIVE == fota_mode
#endif
       ) {
        return RACE_ERRCODE_NOT_SUPPORT;
    }

#ifdef RACE_FOTA_ACTIVE_MODE_KEEP_HFP
    if (RACE_FOTA_MODE_ACTIVE == fota_mode &&
        race_fota_is_hfp_active()) {
        return RACE_ERRCODE_REJECT_FOR_CALL_ONGOING;
    }
#endif

    if (g_race_fota_cntx_ptr &&
        (RACE_FOTA_MODE_MAX != g_race_fota_cntx_ptr->fota_mode &&
         fota_mode != g_race_fota_cntx_ptr->fota_mode)) {
        return RACE_ERRCODE_CONFLICT;
    }

    return RACE_ERRCODE_SUCCESS;
}


RACE_ERRCODE race_fota_is_dl_method_allowed(race_fota_dual_device_dl_method_enum dl_method)
{
    if (RACE_FOTA_DUAL_DEVICE_DL_METHOD_MAX <= dl_method
#ifndef RACE_FOTA_DUAL_DEVICE_CONCURRENT_DOWNLOAD_ENABLE
        || RACE_FOTA_DUAL_DEVICE_DL_METHOD_CONCURRENT == dl_method
#endif
       ) {
        return RACE_ERRCODE_NOT_SUPPORT;
    }

    if (g_race_fota_cntx_ptr &&
        (RACE_FOTA_DUAL_DEVICE_DL_METHOD_MAX != g_race_fota_cntx_ptr->dl_method &&
         dl_method != g_race_fota_cntx_ptr->dl_method)) {
        return RACE_ERRCODE_CONFLICT;
    }

    return RACE_ERRCODE_SUCCESS;
}


RACE_ERRCODE race_fota_start_check_params(race_recipient_type_enum recipient_type,
                                          race_fota_mode_enum fota_mode,
                                          race_fota_dual_device_dl_method_enum dl_method)
{
    RACE_ERRCODE ret = RACE_ERRCODE_SUCCESS;

    if (RACE_RECIPIENT_TYPE_NONE == recipient_type ||
        RACE_RECIPIENT_TYPE_MAX <= recipient_type ||
        RACE_RECIPIENT_TYPE_PARTNER_ONLY == recipient_type) {
        ret = RACE_ERRCODE_NOT_SUPPORT;
    }

    if (RACE_ERRCODE_SUCCESS == ret) {
        ret = race_fota_is_fota_mode_allowed(fota_mode);
    }

    if (RACE_ERRCODE_SUCCESS == ret &&
        RACE_RECIPIENT_TYPE_AGENT_PARTNER == recipient_type) {
        ret = race_fota_is_dl_method_allowed(dl_method);
    }

    return ret;
}


race_fota_mode_enum race_fota_get_fota_mode(void)
{
    if (g_race_fota_cntx_ptr &&
        race_fota_is_race_fota_running()) {
        return g_race_fota_cntx_ptr->fota_mode;
    }

   return RACE_FOTA_MODE_MAX;
}


#ifdef RACE_FOTA_ADAPTIVE_MODE_ENABLE
void race_get_device_busy_status_default(bool *is_busy)
{
    if (is_busy) {
        *is_busy = FALSE;
    }
}

#pragma weak race_get_device_busy_status=race_get_device_busy_status_default

void race_cmd_post_process(race_pkt_t *race_cmd_ptr)
{
    if (race_cmd_ptr && RACE_APP_ID_FOTA == race_cmd_ptr->hdr.pktId.field.app_id &&
        race_fota_is_adaptive_mode() &&
        (RACE_TYPE_RESPONSE == race_cmd_ptr->hdr.type ||
         RACE_TYPE_NOTIFICATION == race_cmd_ptr->hdr.type)) {
        uint8_t *status_ptr = (uint8_t *)race_cmd_ptr + 6;
        bool is_busy = FALSE;
#if defined(RACE_RELAY_CMD_ENABLE) || defined(AIR_RACE_CO_SYS_ENABLE)
        if (RACE_TYPE_NOTIFICATION == race_cmd_ptr->hdr.type &&
            RACE_CMDRELAY_PASS_TO_DST == race_cmd_ptr->hdr.id) {
            /* Length includes ID and payload. Add 2 bytes for ID and another 2 bytes for RACE_CMDRELAY_PASS_TO_DST NOTI structure. */
            if (race_cmd_ptr->hdr.length > sizeof(race_pkt_t) + 4) {
                race_pkt_t relayed_race_cmd;

                memcpy(&relayed_race_cmd, race_cmd_ptr->payload + 2, sizeof(race_pkt_t));
                if (RACE_APP_ID_FOTA == relayed_race_cmd.hdr.pktId.field.app_id &&
                    (RACE_TYPE_RESPONSE == relayed_race_cmd.hdr.type ||
                     RACE_TYPE_NOTIFICATION == relayed_race_cmd.hdr.type)) {
                    status_ptr = race_cmd_ptr->payload + 8;
                } else {
                    return;
                }
            } else {
                return;
            }
        }
#endif
        race_get_device_busy_status(&is_busy);

        if (is_busy) {
            (*status_ptr) = (*status_ptr) | 0x80;
        }
    }
}
#endif

#if defined(AIR_DONGLE_FOTA_BY_SP_ENABLE) || defined(AIR_FOTA_DONGLE_HEADSET_BY_SP_ENABLE)
bool race_fota_is_race_fota_upgrade_completed(void)
{
    bool result = false;
    uint8_t flag = 0;
    uint32_t f_length = sizeof(uint8_t);
    fota_get_upgrade_result(&result);
    bool n_status = race_fota_read_nvkey_upgrade_complete_flag(&flag, &f_length);
    //RACE_LOG_MSGID_I("fota_upgrade_completed:%x, %x, %x", 3, result, flag, n_status);
    if (true == n_status) {
        if (1 == flag && result == true) {
            return true;
        }
    }

    return false;
}

bool race_fota_read_nvkey_upgrade_complete_flag(uint8_t *buffer, uint32_t *size)
{
    nvkey_status_t status;
    status = nvkey_read_data(NVID_FOTA_UPDATE_COMPLETE_FLAG, buffer, size);
    if (NVKEY_STATUS_OK == status) {
        return true;
    }
    return false;
}

bool race_fota_write_nvkey_upgrade_complete_flag(uint8_t *buffer, uint32_t size)
{
    nvkey_status_t status;
    status = nvkey_write_data(NVID_FOTA_UPDATE_COMPLETE_FLAG, buffer, size);
    if (NVKEY_STATUS_OK == status) {
        return true;
    }
    return false;
}

bool race_fota_clear_nvkey_upgrade_complete_flag(void)
{
    nvkey_status_t status;
    uint8_t flag = 0;
    uint32_t f_length = sizeof(uint8_t);
    status = nvkey_write_data(NVID_FOTA_UPDATE_COMPLETE_FLAG, &flag, f_length);
    if (NVKEY_STATUS_OK == status) {
        return true;
    }
    return false;
}
#endif

RACE_ERRCODE race_fota_hash_nb_send_message(void *context)
{
    race_general_msg_t msg = {0};

    /* Send the message to continue to calculate has. */
    msg.msg_id = MSG_ID_RACE_LOCAL_HASH_NB_GENERATE_CONTINUE_IND;
    msg.msg_data = (uint8_t *)context;

    return race_send_msg(&msg);
}


void race_fota_hash_nb_generate_continue_msg_process(race_general_msg_t *msg)
{
    fota_hash_nb_context_struct *nb_hash_context = NULL;
    int ret = RACE_ERRCODE_PARAMETER_ERROR;

    if (msg && msg->msg_data) {
        /* callback will free nb_hash_context */
        nb_hash_context = (fota_hash_nb_context_struct *)msg->msg_data;
        ret = fota_hash_nb_generate_continue(nb_hash_context);
        if (FOTA_ERRCODE_WOULDBLOCK == ret) {
            ret = race_fota_hash_nb_send_message(nb_hash_context);
            if (RACE_ERRCODE_SUCCESS != ret) {
                fota_hash_nb_generate_cancel(nb_hash_context);
                /* callback has been invoked by fota_hash_nb_generate_cancel(). */
            } /* else callback will be invoked by fota_hash_nb_generate_continue(). */
        } /* else callback has been invoked by fota_hash_nb_generate_continue(). */
    }
}
uint16_t race_fota_ad_appearance = CONFIG_BT_DEVICE_APPEARANCE;
#define RACE_FOTA_BT_ADV_START_INTERVAL_MAX  0x0040
#define RACE_FOTA_BT_ADV_START_INTERVAL_MIN  0x0020

static const struct bt_data race_fota_ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA_BYTES(BT_DATA_UUID16_ALL,
                BT_UUID_16_ENCODE(BT_UUID_HIDS_VAL),
                BT_UUID_16_ENCODE(BT_UUID_BAS_VAL)),

    BT_DATA(BT_DATA_GAP_APPEARANCE, &race_fota_ad_appearance, sizeof(race_fota_ad_appearance) ),

};

static const struct bt_data race_fota_sd[] = {
    BT_DATA(BT_DATA_NAME_COMPLETE, CONFIG_BT_DEVICE_NAME, (sizeof(CONFIG_BT_DEVICE_NAME) - 1)),
};

#if 0
static const uint8_t temp_address[6] = {0};
static uint8_t race_fota_adv_set_static_random_address(uint8_t id)
{
    int err;
    bt_addr_le_t static_random_addr;
    struct bt_le_oob oob;

    err = bt_le_oob_get_local(id, &oob);
    if (err) {
        LOG_INF("race fota Failed to get OOB data (err %d) id = %d\n", err, id);
        return 0;
    }

    if(memcmp(temp_address, &oob.addr.a.val[0], 6) == 0) {
        err = bt_addr_le_create_static(&static_random_addr);
        if (err) {
            LOG_INF("race fota bt_addr_le_create_static failed (err %d)\n", err);
            return 0;
        }
        static_random_addr.type = BT_ADDR_LE_RANDOM;
        err = bt_id_create(&static_random_addr, NULL);
        if (err < 0) {
            LOG_INF("race fota bt_id_create failed with error code %d\n", err);
            return 0;
        }

        LOG_INF("race fota Random static address set successfully for id %d\n", err);
        return err;
    } else {
        LOG_INF("race fota adv address is not match \n");
    }

    return 0;
}

#endif
static uint8_t race_fota_enable_adv(uint8_t address_id)
{
    int err = 0;
    struct bt_le_adv_param adv_param;
    adv_param = *BT_LE_ADV_CONN_ONE_TIME;
    adv_param.interval_max = RACE_FOTA_BT_ADV_START_INTERVAL_MAX;
    adv_param.interval_min = RACE_FOTA_BT_ADV_START_INTERVAL_MIN;
    adv_param.id = address_id;
    LOG_INF("race_fota_adv_start, ad len = %d, sd len %d,adv_param:%x\n", ARRAY_SIZE(race_fota_ad), ARRAY_SIZE(race_fota_sd), adv_param);
    err = bt_le_adv_start(&adv_param, race_fota_ad, ARRAY_SIZE(race_fota_ad), race_fota_sd, ARRAY_SIZE(race_fota_sd) );

    if (err) {
        LOG_INF("race_fota_adv_start undir adv failed (err %d)\n", err);
    } else {
        LOG_INF("race_fota_adv_start successed\n");
    }

    return err;
}

void race_fota_start_adv()
{
#ifdef CONFIG_BT_PKA_LIB_MULTI_PROTOCOL
    IEEE802154_Controller_EnableBle();
#else
    bt_enable(NULL);
#endif
    race_fota_enable_adv(0);
}
#endif /* RACE_FOTA_CMD_ENABLE */

