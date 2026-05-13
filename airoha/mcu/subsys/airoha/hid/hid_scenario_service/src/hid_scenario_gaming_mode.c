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

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include "host/conn_internal.h"

#include "hid_scenario_service.h"
#include "hid_scenario_service_internal.h"
#include "hid_scenario_gaming_mode.h"
#include "hid_scenario_report_rate.h"

#include "bt_ull_le_hid_conn_service.h"
#include "bt_ull_le_hid_service.h"
#include "bt_ull_le_hid_device_manager.h"
#include "hid_scenario_adv.h"
#include "hid_scenario_report_rate.h"
#include "hid_common.h"
#include "hid_race_cmd.h"
#include "hid_race_cmd_mouse.h"
#include "nvkey.h"
#include "air_daemon_work_q.h"
#include "assert.h"

#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)
#include "custom_protocol.h"
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE */

#if defined (AIR_ADC_KEYSCAN_ENABLE)
#include "adc_keyscan.h"
#endif /*END AIR_ADC_KEYSCAN_ENABLE*/

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
#include "hid_game_controller.h"
#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */

#if defined(HAL_SPI_MASTER_MODULE_ENABLED)
#include "hal_spi_master.h"
#endif


#define thisMODULE  G_mode
#define thisMOD    "G_mode"

#define ULL_SERIVE_READY // 0x80 workaround

LOG_MODULE_REGISTER(thisMODULE);
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
static void hid_scenario_gaming_mode_ull_cmd_init();
static void hid_scenario_gaming_mode_ull_cmd_deinit();
static void hid_scenario_gaming_mode_state_change(uint8_t new_state, uint8_t reason);
static void hid_scenario_gaming_mode_ull_srv_event_job(struct k_work *work);
static void hid_scenario_gaming_mode_acl_event_job(struct k_work *work);
static uint8_t hid_scenario_gaming_mode_get_device_type();
#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
static void hid_scenario_gaming_mode_config_adv(T_GAMING_ADV_SETTING_S *adv_setting);
#endif
#if defined(ULL_SERIVE_READY)
static void hid_scenario_gaming_mode_ull_service_not_ready(struct k_timer *timer_id);
struct k_timer ull_service_ready_check_timer;
#define ULL_SERVICE_READY_TIMEOUT 5
#endif

static K_WORK_DEFINE(job_g_mode_ull_srv_event, hid_scenario_gaming_mode_ull_srv_event_job);
static K_WORK_DEFINE(job_g_mode_acl_event, hid_scenario_gaming_mode_acl_event_job);
/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
typedef enum
{
    FLAG_BONDED = 0,
    FLAG_PAIRING,
}T_GAMING_MODE_FLAG_E;

typedef enum
{
    G_MODE_CONNECTED = 0,
    G_MODE_DISCONNECTED,
}T_G_MODE_CONN_EVENT_E;

typedef struct
{
    bt_ull_le_hid_srv_app_scenario_t scenario;
    bt_addr_le_t peer_addr;
}T_BOND_RECORD_S;

typedef struct
{
    //32//////////
    uint32_t  flags;
    struct bt_conn *bt_conn_ptr;

    // struct/////
    T_BOND_RECORD_S peer_record;

    //16//////////

    //8///////////
    T_HID_MODE_STATE_E state;
    uint8_t link_idx;
    uint8_t ull_init;
    uint16_t riscv_trigger_time[REPORT_RATE_NUM];
    struct k_fifo fifo;
    struct k_fifo acl_fifo;
}T_GAMING_SCENARIO_S;

typedef struct {
    void *fifo_reserved;
    bt_ull_event_t event;
    uint8_t *param;
    uint32_t param_len;
} ull_srv_event_fifo_t;

typedef struct {
    void *fifo_reserved;
    struct bt_conn_info info;
    uint8_t reason;
    T_G_MODE_CONN_EVENT_E event;
} acl_event_fifo_t;


T_GAMING_SCENARIO_S g_mode =
{
    .state = MODE_CLOSED,
    .flags = 0,
    .bt_conn_ptr= NULL,
    .ull_init = false,
    .riscv_trigger_time = 
    {
        CONFIG_AIR_DEFAULT_RISCV_TRIGGER_TIME_RR_125HZ,
        CONFIG_AIR_DEFAULT_RISCV_TRIGGER_TIME_RR_250HZ,
        CONFIG_AIR_DEFAULT_RISCV_TRIGGER_TIME_RR_500HZ,
        CONFIG_AIR_DEFAULT_RISCV_TRIGGER_TIME_RR_1000HZ,
        CONFIG_AIR_DEFAULT_RISCV_TRIGGER_TIME_RR_2000HZ,
        CONFIG_AIR_DEFAULT_RISCV_TRIGGER_TIME_RR_4000HZ,
        CONFIG_AIR_DEFAULT_RISCV_TRIGGER_TIME_RR_8000HZ,
    },
};

#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
uint16_t adv_interval_resume = 640; /* 640 * 1.25 = 800ms*/
uint16_t ad_appearance_2_4G = CONFIG_AIR_2_4G_DEVICE_APPEARANCE;
uint16_t ad_appearance_2_4G_resume = 0xFEFE;

static struct bt_data ad_proprietary_2_4G[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_NO_BREDR)),
    BT_DATA(BT_DATA_GAP_APPEARANCE, &ad_appearance_2_4G, sizeof(ad_appearance_2_4G) ),
};

static struct bt_data ad_proprietary_2_4G_resume[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_NO_BREDR)),
    BT_DATA(BT_DATA_GAP_APPEARANCE, &ad_appearance_2_4G_resume, sizeof(ad_appearance_2_4G_resume) ),
};
#endif

// Macro to set a flag
#define SET_G_MODE_FLAG(flag_id)     ((g_mode.flags) |= (0x01 << flag_id))

// Macro to clear a flag
#define CLEAR_G_MODE_FLAG(flag_id)   ((g_mode.flags) &= ~(0x01 << flag_id))

// Macro to check if a flag is set
#define CHECK_G_MODE_FLAG(flag_id)   (((g_mode.flags) & (0x01 << flag_id)) ? 1 : 0)

#define CONVERT_RACE_DEVICE_TYPE(type)                        \
    ((type) == 0x00 ? BT_ULL_LE_HID_SRV_DEVICE_NONE :         \
    (type) == 0x04 ? BT_ULL_LE_HID_SRV_DEVICE_HEADSET :       \
    (type) == 0x05 ? BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD :      \
    (type) == 0x06 ? BT_ULL_LE_HID_SRV_DEVICE_MOUSE :         \
    (type) == 0x07 ? BT_ULL_LE_HID_SRV_DEVICE_EARBUDS :       \
    (type) == 0x0A ? BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD :       \
    BT_ULL_LE_HID_SRV_DEVICE_NONE)

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/


/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
#if defined (ULL_SERIVE_READY)
static void hid_scenario_gaming_mode_ull_service_not_ready(struct k_timer *timer_id)
{
    DBG_LOGI(thisMOD,"hid_scenario_gaming_mode_ull_service_not_ready");
    assert("ULL service not ready over 5s" && 0);
}
#endif

static void hid_scenario_gaming_mode_state_change(uint8_t new_state, uint8_t reason)
{
    DBG_LOGI(thisMOD," hid_scenario_gaming_mode_state_change 0x%02X to 0x%02X , reason = 0x%02X",g_mode.state,  new_state, reason);

    switch(g_mode.state)
    {
        case MODE_OPEN_SPECIFIED:
        case MODE_OPEN_UNSPECIFIED:
        #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
        case MODE_OPEN_SPECIFIED_RESUME:
        #endif
        {
            if((new_state == MODE_OPEN_CONNECTED) || (new_state == MODE_CLOSED))
            {
                hid_scenario_send_state_update_notification(new_state, reason);
                g_mode.state = new_state;
            }
        }
        break;

        case MODE_OPEN_CONNECTED:
        {
            if((new_state == MODE_OPEN_CIS_SERVICE_READY) || (new_state == MODE_CLOSED))
            {
                hid_scenario_send_state_update_notification(new_state, reason);
                g_mode.state = new_state;
            }
        }
        break;

        case MODE_OPEN_CIS_SERVICE_READY:
        {
            if((new_state == MODE_STARTED) || (new_state == MODE_CLOSED))
            {
                hid_scenario_send_state_update_notification(new_state, reason);
                g_mode.state = new_state;
            }
        }
        break;

        case MODE_STARTED:
        {
            if((new_state == MODE_STOPPED) || (new_state == MODE_CLOSED))
            {
                hid_scenario_send_state_update_notification(new_state, reason);
                g_mode.state = new_state;
            }
        }
        break;

        case MODE_STOPPED:
        {
            if((new_state == MODE_STARTED) || (new_state == MODE_CLOSED))
            {
                hid_scenario_send_state_update_notification(new_state, reason);
                g_mode.state = new_state;
            }
        }
        break;

        case MODE_CLOSED:
        {
            if((new_state == MODE_OPEN_UNSPECIFIED) 
                || (new_state == MODE_OPEN_SPECIFIED)
                #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
                || (new_state == MODE_OPEN_SPECIFIED_RESUME)
                #endif
            ){
                hid_scenario_send_state_update_notification(new_state, reason);
                g_mode.state = new_state;
            }
        }
        break;

        default:
            DBG_LOGI(thisMOD," hid_scenario_gaming_mode_state_change Error!!  Unexpected state change from  0x%d to 0x%d ",g_mode.state , new_state);
        break;
    }
}

void hid_scenario_gaming_mode_ull_srv_event_handler(bt_ull_event_t event, void *param, uint32_t param_len)
{
    switch(event)
    {
        case BT_ULL_EVENT_USER_DATA_IND:
        {
#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)
            // bt_ull_user_data_t *user_data = (bt_ull_user_data_t *)param;
            // if (user_data != NULL)
            // {
            //     epio_bt_hid_recv_data(&user_data->remote_address, user_data->user_data_length, user_data->user_data);
            // }
#else
            DBG_LOGI(thisMOD," Gaming Mode User Data !! ");
#endif
        }
        break;

        case BT_ULL_EVENT_LE_HID_BONDING_COMPLETE_IND:  //0x20
        {
            bt_ull_le_hid_srv_bonding_complete_ind_t*  bond_info = (bt_ull_le_hid_srv_bonding_complete_ind_t *)param;
            uint8_t device_type = hid_scenario_gaming_mode_get_device_type();
            bt_ull_le_hid_dm_device_info_t* device_info = bt_ull_le_hid_dm_read_device_info(device_type , &bond_info->peer_addr);
            if (device_info){
                g_mode.peer_record.scenario = device_info->scenario;
                DBG_LOGI(thisMOD," device_info->scenario = %x"
                    , g_mode.peer_record.scenario
                    );
            }
            else {
                DBG_LOGI(thisMOD," device_info  = NULL");
                g_mode.peer_record.scenario = 0xFF;
            }

            memcpy( &g_mode.peer_record.peer_addr , &bond_info->peer_addr , sizeof(bt_addr_le_t)  );
            nvkey_status_t ret = nvkey_write_data( NVID_GAMING_MODE_PEER_DEVICE_INFO_0  + g_mode.link_idx , (const uint8_t*)&g_mode.peer_record , sizeof(T_BOND_RECORD_S));

            DBG_LOGI(thisMOD," gaming connection bonding complete !! addr_type = 0x%X, peer_addr = 0x%02X-%02X-%02X-%02X-%02X-%02X, rr_level = %d, rr = %d, nvkey_write_data = %d"
                , g_mode.peer_record.peer_addr.type
                , g_mode.peer_record.peer_addr.a.val[0]
                , g_mode.peer_record.peer_addr.a.val[1]
                , g_mode.peer_record.peer_addr.a.val[2]
                , g_mode.peer_record.peer_addr.a.val[3]
                , g_mode.peer_record.peer_addr.a.val[4]
                , g_mode.peer_record.peer_addr.a.val[5]
                , bond_info->report_rate.rr_level
                , ULL_REPORT_RATE_IDX_TO_VALUE(bond_info->report_rate.rr_level)
                , ret
                 );

            // New bonded device, check the report rate
            hid_scenario_report_rate__new_connection(MODE_TYPE_GAMING, ULL_REPORT_RATE_IDX_TO_VALUE(bond_info->report_rate.rr_level));
        }
        break;

        case BT_ULL_EVENT_LE_HID_CONNECTED_IND: // 0x21
        {
            if ( g_mode.state == MODE_CLOSED){
                DBG_LOGI(thisMOD," clear FLAG_BIT_GAMING_CONNECTED flag");
                hid_common_clear_hid_exp_flag(FLAG_BIT_GAMING_CONNECTED);
            }
            else {
                DBG_IDX(3, DBG_SIGNAL_MAIN_LOOP)
                bt_ull_le_hid_srv_connected_ind_t*  connected_ind = (bt_ull_le_hid_srv_connected_ind_t *)param;

                g_mode.bt_conn_ptr = connected_ind->conn;
                if(connected_ind->status == BT_HCI_ERR_SUCCESS)
                {
                    DBG_LOGI(thisMOD," Gaming Mode ULL Connected  !! device_type = %d, peer_addr = 0x%02X-%02X-%02X - %02X-%02X-%02X"
                        , connected_ind->device_type
                        , connected_ind->peer_addr.a.val[0]
                        , connected_ind->peer_addr.a.val[1]
                        , connected_ind->peer_addr.a.val[2]
                        , connected_ind->peer_addr.a.val[3]
                        , connected_ind->peer_addr.a.val[4]
                        , connected_ind->peer_addr.a.val[5]
                    );

                    //g_mode.state = MODE_OPEN_CONNECTED;
                    #if defined(ULL_SERIVE_READY)
                    k_timer_stop(&ull_service_ready_check_timer);
                    k_timer_start(&ull_service_ready_check_timer, K_SECONDS(ULL_SERVICE_READY_TIMEOUT), K_NO_WAIT);
                    #endif
                    hid_scenario_gaming_mode_state_change(MODE_OPEN_CONNECTED, 0);
                }
                else if(connected_ind->status == BT_HCI_ERR_ADV_TIMEOUT)
                {
                    DBG_LOGI(thisMOD," Gaming Mode Create sync cancel success !!");
                    hid_scenario_gaming_mode_state_change(MODE_CLOSED, REASON_CONNECTION_TERMINATED_BY_LOCAL_HOST);
                    hid_scenario_gaming_mode_ull_cmd_deinit();
                }
            }
        }
        break;

        case BT_ULL_EVENT_LE_HID_SERVICE_CONNECTED_IND: // 0x22
        {
            if ( g_mode.state == MODE_CLOSED){
                DBG_LOGI(thisMOD," clear FLAG_BIT_GAMING_CONNECTED flag");
                hid_common_clear_hid_exp_flag(FLAG_BIT_GAMING_CONNECTED);
            }
            else {
                DBG_IDX(4, DBG_SIGNAL_MAIN_LOOP)
                DBG_LOGI(thisMOD," Gaming Mode ULL Service Ready !! ");
                #if defined (ULL_SERIVE_READY)
                k_timer_stop(&ull_service_ready_check_timer);
                #endif
                hid_scenario_report_rate_validation_check(MODE_TYPE_GAMING, hid_scenario_read_now_report_rate(MODE_TYPE_GAMING));
                hid_scenario_gaming_mode_state_change(MODE_OPEN_CIS_SERVICE_READY, 0);
            }
        }
        break;

        case BT_ULL_EVENT_LE_HID_DISCONNECTED_IND: // 0x23
        {
            bt_ull_le_hid_srv_disconnected_ind_t*  disconnected_ind = (bt_ull_le_hid_srv_disconnected_ind_t *)param;
            #if defined (ULL_SERIVE_READY)
            k_timer_stop(&ull_service_ready_check_timer);
            #endif
            g_mode.bt_conn_ptr = NULL;
            DBG_LOGI(thisMOD," Gaming Mode ULL Disconnected !! reason = 0x%02X", disconnected_ind->reason );
            hid_common_clear_hid_exp_flag(FLAG_BIT_GAMING_CONNECTED);
            hid_scenario_gaming_mode_ull_cmd_deinit();

            hid_scenario_gaming_mode_state_change(MODE_CLOSED, disconnected_ind->reason);
        }
        break;


        case BT_ULL_EVENT_LE_HID_REPORT_RATE_CHANGE_IND: //0x27
        {
            bt_ull_le_hid_srv_report_rate_change_ind_t*  rr_ind = (bt_ull_le_hid_srv_report_rate_change_ind_t *)param;
            uint32_t rr = ULL_REPORT_RATE_IDX_TO_VALUE(rr_ind->report_rate.rr_level);
            DBG_LOGI(thisMOD," ULL Report Rate Updated !! status = %d, rr = %d Hz", rr_ind->status, rr );
            hid_scenario_report_rate_validation_check(MODE_TYPE_GAMING, rr);
        }
        break;

        #if defined(CONFIG_AIR_HID_OUTPUT_REPORT_NOTIFY)
        case BT_ULL_EVENT_LE_HID_OUTPUT_REPORT_IND: //0x29
        {
            bt_ull_le_hid_srv_output_report_ind_t*  output_report = (bt_ull_le_hid_srv_output_report_ind_t *)param;
            hid_scenario_send_notification(SS_EVT_HID_OUTPUT_REPORT,  output_report->data, output_report->data_length );
        }
        break;
        #endif

        default:
        {
            DBG_LOGI(thisMOD," hid_scenario_gaming_mode_ull_srv_event_handler, un-handled event = 0x%02x, len = %d \n ", event, param_len );
        }
        break;

    }
    DBG_LOGI(thisMOD," hid_scenario_gaming_mode_ull_srv_event_handler, g_mode.state = %02x ", g_mode.state );
}

static void hid_scenario_gaming_mode_ull_srv_event_job(struct k_work *work)
{
    ull_srv_event_fifo_t* ull_srv_event_fifo = k_fifo_get(&g_mode.fifo, K_NO_WAIT);

    DBG_LOGI(thisMOD," hid_scenario_gaming_mode_ull_srv_event_job");

    while (ull_srv_event_fifo != NULL)
    {
        hid_scenario_gaming_mode_ull_srv_event_handler(ull_srv_event_fifo->event, ull_srv_event_fifo->param, ull_srv_event_fifo->param_len);
        k_free(ull_srv_event_fifo->param);
        k_free(ull_srv_event_fifo);
        ull_srv_event_fifo = k_fifo_get(&g_mode.fifo, K_NO_WAIT);
    }
}

static void hid_scenario_gaming_mode_ull_srv_event_cb(bt_ull_event_t event, void *param, uint32_t param_len)
{
    DBG_PING_H(DBG_SIGNAL_DEBUG_2);

    if(event == BT_ULL_EVENT_USER_DATA_IND){
        #if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)
        bt_ull_user_data_t *user_data = (bt_ull_user_data_t *)param;
        if (user_data != NULL)
        {
            epio_bt_hid_recv_data(&user_data->remote_address, user_data->user_data_length, user_data->user_data);
        }
        #else
        DBG_LOGI(thisMOD," Gaming Mode User Data !! ");
        #endif
    }
    else{
        #if defined(CONFIG_AIR_HID_REPORT_QUICK_START)
        if (event == BT_ULL_EVENT_LE_HID_CONNECTED_IND){
            bt_ull_le_hid_srv_connected_ind_t*  connected_ind = (bt_ull_le_hid_srv_connected_ind_t *)param;

            if(connected_ind->status == BT_HCI_ERR_SUCCESS){
                hid_common_set_hid_exp_flag(FLAG_BIT_GAMING_CONNECTED);
                DBG_PING_L(DBG_SIGNAL_DEBUG_2);
                DBG_PING_H(DBG_SIGNAL_DEBUG_2);
                DBG_PING_L(DBG_SIGNAL_DEBUG_2);
                DBG_PING_H(DBG_SIGNAL_DEBUG_2);
            }

            #if defined (AIR_SWLA_ENABLE)
            HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_app_bt_connecting, SWLA_DIRECTION_STOP);
            #endif
        }
        #endif

        ull_srv_event_fifo_t * ull_srv_event_fifo = (ull_srv_event_fifo_t * )k_malloc(sizeof(ull_srv_event_fifo_t));
        assert(ull_srv_event_fifo != NULL && "ull_srv_event_fifo malloc failed");
        if (ull_srv_event_fifo) {
            ull_srv_event_fifo->event = event;
            ull_srv_event_fifo->param_len = param_len;
            ull_srv_event_fifo->param = (uint8_t *)k_malloc(param_len);
            if (ull_srv_event_fifo->param != NULL) {
                memcpy(ull_srv_event_fifo->param, (uint8_t *)param, param_len);
                k_fifo_put(&g_mode.fifo, ull_srv_event_fifo);
                air_daemon_wq_work_submit(&job_g_mode_ull_srv_event);
            }
            else {
                k_free(ull_srv_event_fifo);
                assert(0 && "submit ull_srv_event param malloc failed");
            }
        }
        DBG_LOGI(thisMOD," submit ull_srv_event = 0x%x, param_len = %d", event, param_len);
    }
    DBG_PING_L(DBG_SIGNAL_DEBUG_2);
}

int hid_scenario_gaming_mode_ull_cmd__create_sync(bt_addr_le_t *peer_addr)
{
    int err = 0;

    bt_ull_le_hid_srv_create_sync_t param;
    param.device_type = hid_scenario_gaming_mode_get_device_type();
    memcpy(&param.peer_addr, peer_addr, sizeof(bt_addr_le_t));

    err = bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_CREATE_SYNC, &param, sizeof(param));

    DBG_LOGI(thisMOD,"hid_scenario_gaming_mode_ull_cmd__create_sync[0x%X]=%d, peer_addr =  0x%02X-%02X-%02X-%02X-%02X-%02X"
        , BT_ULL_ACTION_LE_HID_CREATE_SYNC
        , err
        , peer_addr->a.val[0]
        , peer_addr->a.val[1]
        , peer_addr->a.val[2]
        , peer_addr->a.val[3]
        , peer_addr->a.val[4]
        , peer_addr->a.val[5]
        );
    return err;
}

int hid_scenario_gaming_mode_ull_cmd__set_report_rate(uint8_t rr_level, uint8_t phy)
{
    int err = 0;
    bt_ull_le_hid_srv_report_rate_t param;
    param.rr_level = rr_level;
    param.phy = phy;

    DBG_LOGI(thisMOD,"hid_scenario_gaming_mode_ull_cmd__set_report_rate[0x%X]=%d, rr_level = %d, phy = 0x%02X"
        , BT_ULL_ACTION_LE_HID_SET_REPORT_RATE
        , err
        , param.rr_level
        , param.phy
        );
    err = bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_SET_REPORT_RATE, &param, sizeof(param));
    assert(  (rr_level<=8) && (rr_level > 0) &&   "Error : invalid rr_level");
    return err;
}

int hid_scenario_gaming_mode_ull_cmd__cancel_create_sync()
{
    int err = 0;
    bt_ull_le_hid_srv_cancel_create_sync_t param;
    param.device_type = hid_scenario_gaming_mode_get_device_type();
    err = bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_CANCEL_CREATE_SYNC, &param, sizeof(param));
    DBG_LOGI(thisMOD, "hid_scenario_gaming_mode_ull_cmd_send ull_action[%d] = %d ",BT_ULL_ACTION_LE_HID_CANCEL_CREATE_SYNC, err);
    return err;
}


int hid_scenario_gaming_mode_ull_cmd__disconnect()
{
    int err = 0;
    bt_ull_le_hid_srv_disconnect_t param;
    param.conn = g_mode.bt_conn_ptr;
    param.reason = BT_HCI_ERR_REMOTE_USER_TERM_CONN;

    err = bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_DISCONNECT, &param, sizeof(param));
    DBG_LOGI(thisMOD, "hid_scenario_gaming_mode_ull_cmd__disconnect ull_action[%d] = %d ",BT_ULL_ACTION_LE_HID_DISCONNECT, err);

    return err;
}

static void hid_scenario_gaming_mode_ull_cmd_init()
{
    if(g_mode.ull_init == false)
    {
        int ret = bt_ull_le_hid_srv_init(BT_ULL_ROLE_CLIENT, hid_scenario_gaming_mode_ull_srv_event_cb);
        uint8_t device_type = hid_scenario_gaming_mode_get_device_type();
        int ret2 = bt_ull_le_hid_srv_init_device_type(device_type);
        g_mode.ull_init = true;
        DBG_LOGI(thisMOD, "hid_scenario_gaming_mode_ull_cmd_init, bt_ull_le_hid_srv_init = %d, %d, g_mode.state = %d", ret, ret2, g_mode.state);
    }
    else
    {
        DBG_LOGI(thisMOD,"Already bt_ull_le_hid_srv_init !!!");
    }
}

static void hid_scenario_gaming_mode_ull_cmd_deinit()
{
    if(g_mode.ull_init)
    {
        int ret = bt_ull_le_hid_srv_deinit(BT_ULL_ROLE_CLIENT, hid_scenario_gaming_mode_ull_srv_event_cb);
        DBG_LOGI(thisMOD, "hid_scenario_gaming_mode_ull_cmd_deinit, bt_ull_le_hid_srv_deinit = %d, g_mode.state = %d", ret, g_mode.state);
        g_mode.ull_init = false;
    }
    else
    {
        DBG_LOGI(thisMOD,"Already bt_ull_le_hid_srv_deinit !!!");
    }
}


static void hid_scenario_gaming_mode_acl_handler(struct bt_conn_info info, uint8_t reason, T_G_MODE_CONN_EVENT_E event)
{
    switch(event)
    {
        case G_MODE_CONNECTED:
        {
            bt_addr_le_t invalid_peer_addr = {0};
            const bt_addr_le_t* dst_addr = info.le.dst;
            DBG_LOGI(thisMOD,"hid_scenario_gaming_mode_acl_connected with 0x%02X-%02X-%02X-%02X-%02X-%02X, type = %d, g_mode.state = 0x%02X"
                , dst_addr->a.val[0]
                , dst_addr->a.val[1]
                , dst_addr->a.val[2]
                , dst_addr->a.val[3]
                , dst_addr->a.val[4]
                , dst_addr->a.val[5]
                , dst_addr->type
                , g_mode.state
                );
            // hid_scenario_gaming_mode_acl_connected might occurs even if the connection is not established yet
            // this is happened when canceling the process of re-connect with dongle 
            if (memcmp(&invalid_peer_addr.a, &dst_addr->a, 6) == 0){
                DBG_LOGI(thisMOD,"Cancel completed !!");
                hid_scenario_gaming_mode_state_change(MODE_CLOSED, 0);
            }
            else if (g_mode.state == MODE_OPEN_UNSPECIFIED )
            {
                hid_scenario_gaming_mode_state_change(MODE_OPEN_CONNECTED, 0);
            }
        }
        break;

        case G_MODE_DISCONNECTED:
        {
            #if defined (ULL_SERIVE_READY)
            k_timer_stop(&ull_service_ready_check_timer);
            #endif
            const bt_addr_le_t* dst_addr = info.le.dst;
            DBG_LOGI(thisMOD,"hid_scenario_gaming_mode_acl_disconnected from 0x%02X-%02X-%02X-%02X-%02X-%02X (reason 0x%02x), type = %d"
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
            hid_common_clear_hid_exp_flag(FLAG_BIT_GAMING_CONNECTED);
            g_mode.bt_conn_ptr = NULL;
            DBG_LOGI(thisMOD," Gaming Mode Disconnected !! reason = 0x%02X", reason);

            hid_scenario_gaming_mode_state_change(MODE_CLOSED, reason);

            //bt_addr_le_t static_random_addr;
            //bt_addr_le_create_static(&static_random_addr);
            //bt_id_reset(g_mode.link_idx + 1, &static_random_addr, NULL);
        }
        break;

        default:
            break;
    }
}

static void hid_scenario_gaming_mode_acl_event_job(struct k_work *work)
{
    acl_event_fifo_t* acl_event_fifo = k_fifo_get(&g_mode.acl_fifo, K_NO_WAIT);
    DBG_LOGI(thisMOD," hid_scenario_gaming_mode_ull_srv_event_job");

    while (acl_event_fifo != NULL)
    {
        hid_scenario_gaming_mode_acl_handler(acl_event_fifo->info, acl_event_fifo->reason, acl_event_fifo->event);
        k_free(acl_event_fifo);
        acl_event_fifo = k_fifo_get(&g_mode.acl_fifo, K_NO_WAIT);
    }
}

static uint8_t hid_scenario_gaming_mode_get_device_type()
{
    uint8_t device_type = BT_ULL_LE_HID_SRV_DEVICE_NONE;
#if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE)
    device_type = BT_ULL_LE_HID_SRV_DEVICE_MOUSE;
#elif defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
    device_type = BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD;
#elif defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    device_type = BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD;
#endif /* CONFIG_AIR_PRODUCT_TYPE */
    return device_type;
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
uint8_t hid_scenario_gaming_mode_init(uint8_t* riscv_trigger_time)
{
    if (riscv_trigger_time){
        memcpy(g_mode.riscv_trigger_time, riscv_trigger_time, sizeof(g_mode.riscv_trigger_time) );
    }
    else {

    }

    DBG_LOGI(thisMOD, "hid_scenario_gaming_mode_init, riscv_trigger_time = 0x%x, value = %03d-%03d-%03d  %03d-%03d-%03d-%03d (125Hz ~ 8Khz)"
        , riscv_trigger_time
        , g_mode.riscv_trigger_time[0]
        , g_mode.riscv_trigger_time[1]
        , g_mode.riscv_trigger_time[2]
        , g_mode.riscv_trigger_time[3]
        , g_mode.riscv_trigger_time[4]
        , g_mode.riscv_trigger_time[5]
        , g_mode.riscv_trigger_time[6]
         );

    hid_common_set_app_para(PARA_TYPE_RISCV_TRIGGER_TIME, (uint8_t*)g_mode.riscv_trigger_time, sizeof(g_mode.riscv_trigger_time));

    k_fifo_init(&g_mode.fifo);
    k_fifo_init(&g_mode.acl_fifo);

    #if defined (ULL_SERIVE_READY)
    k_timer_init(&ull_service_ready_check_timer , hid_scenario_gaming_mode_ull_service_not_ready, NULL);
    #endif
    return 0;
}


uint8_t hid_scenario_gaming_mode_open(uint32_t link_idx, T_HID_SCENARIO_OPEN_TYPE_E re_pairing, uint16_t reconnect_time)
{
    uint8_t err = 0;
    bool bonded = 0;

    if (re_pairing == SCENARIO_SRV_OPEN_REPARING){
        SET_G_MODE_FLAG(FLAG_PAIRING);
    }
    else {
        CLEAR_G_MODE_FLAG(FLAG_PAIRING);
    }

    assert(link_idx<=2 && "Error : Max Gaming links is 2");
    hid_scenario_gaming_mode_ull_cmd_init();
    g_mode.link_idx = link_idx;

    T_BOND_RECORD_S bond_record;
    uint32_t len = sizeof(T_BOND_RECORD_S);
    nvkey_status_t ret = nvkey_read_data(NVID_GAMING_MODE_PEER_DEVICE_INFO_0 + g_mode.link_idx , (uint8_t*)&bond_record , &len);

    if (NVKEY_STATUS_OK == ret){
        hid_common_set_dongle_scenario(bond_record.scenario);

        uint8_t device_type = hid_scenario_gaming_mode_get_device_type();
        bonded = bt_ull_le_hid_srv_is_bonded_device(device_type , &bond_record.peer_addr );

        DBG_LOGI(thisMOD,"target scenario = 0x%X, peer_addr =  0x%02X-%02X-%02X-%02X-%02X-%02X"
            , bond_record.scenario
            , bond_record.peer_addr.a.val[0]
            , bond_record.peer_addr.a.val[1]
            , bond_record.peer_addr.a.val[2]
            , bond_record.peer_addr.a.val[3]
            , bond_record.peer_addr.a.val[4]
            , bond_record.peer_addr.a.val[5]
            );

        DBG_LOGI(thisMOD,"ret = %d, len = %d, re-pairing = %d, g_mode.flags = 0x%X"
            , ret
            , len
            , re_pairing
            , g_mode.flags
            );
    }

    uint8_t  rr_idx = hid_scenario_read_report_rate_idx(MODE_TYPE_GAMING);

    DBG_LOGI(thisMOD, "hid_scenario_gaming_mode_open link_idx = %d, bonded = %d, rr_idx = %d, riscv_trigger_time = %03d ret = %d"
        , link_idx
        , bonded
        , rr_idx
        , g_mode.riscv_trigger_time[rr_idx]
        , ret
        );

    hid_scenario_adv_print_local_address(0);
    if (bonded && (CHECK_G_MODE_FLAG(FLAG_PAIRING) == false)){

        hid_scenario_update_comm_report_rate_para(MODE_TYPE_GAMING);
        bt_ull_le_hid_conn_srv_set_hid_tx_anchor( g_mode.riscv_trigger_time, REPORT_RATE_NUM);
        bt_ull_le_hid_conn_srv_set_sync_cis_timeout(reconnect_time * 100);

        DBG_PING_H(DBG_SIGNAL_LATCH_REPORT);
        DBG_PING_L(DBG_SIGNAL_LATCH_REPORT);
        DBG_PING_H(DBG_SIGNAL_LATCH_REPORT);
        if (hid_scenario_gaming_mode_ull_cmd__create_sync(&bond_record.peer_addr) == 0){
            #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
            if (re_pairing == SCENARIO_SRV_OPEN_RESUME_WAIT){
                hid_scenario_gaming_mode_state_change(MODE_OPEN_SPECIFIED_RESUME, REASON_RECONNECTION_RESUME);
            } else 
            #endif
            {
                hid_scenario_gaming_mode_state_change(MODE_OPEN_SPECIFIED, 0);
            }
        }
        else {
            assert(0 && "ull_cmd__create_sync failed");
            hid_scenario_gaming_mode_state_change(MODE_CLOSED, REASON_RECONNECTION_CREATE_FAIL);
        }
        DBG_PING_L(DBG_SIGNAL_LATCH_REPORT);
    }
    else {
        err = hid_scenario_undir_adv_start(HID_SCENARIO_GAMING_MODE,  0);
        DBG_LOGI(thisMOD, "hid_scenario_undir_adv_start ret = %d, re-pairing = %d ",err, re_pairing);
        hid_scenario_gaming_mode_state_change(MODE_OPEN_UNSPECIFIED, 0);
    }

    #if defined(CONFIG_AIR_KB_SAMPLE)
    extern void sw_keyscan_bt_trigger_control(bool is_enable);
    sw_keyscan_bt_trigger_control(true);
    #endif /* CONFIG_AIR_KB_SAMPLE */

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    // game_controller_bt_hw_trigger_enable();
#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */

    return err;
}

uint8_t hid_scenario_gaming_mode_start(uint32_t link_idx, void* parameter)
{
    DBG_LOGI(thisMOD, "hid_scenario_gaming_mode_start link_idx = %d, g_mode.state = %d" ,link_idx, g_mode.state);

    hid_common_set_hid_exp_flag(FLAG_BIT_GAMING_CONNECTED);
    // TODO: ENABLE spi trigger by BT

    hid_scenario_gaming_mode_state_change(MODE_STARTED, 0);
    return 0;
}

uint8_t hid_scenario_gaming_mode_stop(uint8_t parameter)
{
    DBG_LOGI(thisMOD, "hid_scenario_gaming_mode_stop g_mode.state = %d", g_mode.state);

    hid_scenario_gaming_mode_state_change(MODE_STOPPED, 0);
    hid_common_clear_hid_exp_flag(FLAG_BIT_GAMING_CONNECTED);
    return 0;
}

uint8_t hid_scenario_gaming_mode_close(uint8_t parameter)
{
    DBG_LOGI(thisMOD, "hid_scenario_gaming_mode_close, g_mode.state = %d", g_mode.state);
    #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
    T_GAMING_ADV_SETTING_S adv_setting;
    adv_setting.setting_type = ADV_SETTING_DEFAULT;
    hid_scenario_gaming_mode_config_adv(&adv_setting);
    #endif
    #if defined(CONFIG_AIR_KB_SAMPLE)
    extern void sw_keyscan_bt_trigger_control(bool is_enable);
    sw_keyscan_bt_trigger_control(false);
    #endif /* CONFIG_AIR_KB_SAMPLE */

    hid_common_clear_hid_exp_flag(FLAG_BIT_GAMING_CONNECTED);
    #if defined (ULL_SERIVE_READY)
    k_timer_stop(&ull_service_ready_check_timer);
    #endif
    switch(g_mode.state)
    {
        case MODE_OPEN_UNSPECIFIED:
        {
            hid_scenario_adv_stop();

            hid_scenario_gaming_mode_state_change(MODE_CLOSED, REASON_CONNECTION_TERMINATED_BY_LOCAL_HOST);
            hid_scenario_gaming_mode_ull_cmd_deinit();
        }
        break;

        case MODE_OPEN_SPECIFIED:
        #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
        case MODE_OPEN_SPECIFIED_RESUME:
        #endif
        {
            if (hid_scenario_gaming_mode_ull_cmd__cancel_create_sync() == 0){

                hid_scenario_gaming_mode_state_change(MODE_CLOSED, REASON_CONNECTION_TERMINATED_BY_LOCAL_HOST);
                hid_scenario_gaming_mode_ull_cmd_deinit();
            }
        }
        break;

        case MODE_OPEN_CONNECTED:
        case MODE_STARTED:
        case MODE_STOPPED:
        {
            hid_scenario_gaming_mode_ull_cmd__disconnect();
        }
        break;

        case MODE_CLOSED:
        {


        }
        break;

        default:
            break;
    }

// #if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
//     game_controller_bt_hw_trigger_disable();
// #endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */

    return 0;
}

void hid_scenario_gaming_mode_config_rr(T_REPORT_RATE_CHANGE_S* change)
{
    if ((g_mode.state == MODE_STARTED) || (g_mode.state == MODE_STOPPED)){

        uint8_t new_rr_idx = hid_scenario_report_rate_change(MODE_TYPE_GAMING, change->type, change->para, change->restore_or_chg_profile);
        hid_scenario_report_rate_2_4G_change_start();
        DBG_LOGI(thisMOD, "hid_scenario_gaming_mode_config_rr, type = %d, para = %d, new_rr_idx = %d"
            , change->type
            , change->para
            , new_rr_idx
            );
    }
    else {
        DBG_LOGI(thisMOD, " RR change at wrong state, ignore change ");
    }
}

#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
void hid_scenario_gaming_mode_config_adv(T_GAMING_ADV_SETTING_S *adv_setting)
{
    if ((g_mode.state == MODE_STARTED) || (g_mode.state == MODE_STOPPED) || (g_mode.state == MODE_CLOSED)
    #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
    || (g_mode.state == MODE_OPEN_SPECIFIED_RESUME)
    #endif
    ){
        switch(adv_setting->setting_type)
        {
            case ADV_SETTING_DEFAULT:
                bt_ull_le_hid_conn_srv_set_adv_interval(0);
                bt_ull_le_hid_conn_srv_set_adv_data(ad_proprietary_2_4G, ARRAY_SIZE(ad_proprietary_2_4G));
                break;
            case ADV_SETTING_RESUME_WAIT:
                bt_ull_le_hid_conn_srv_set_adv_interval(adv_interval_resume);
                bt_ull_le_hid_conn_srv_set_adv_data(ad_proprietary_2_4G_resume, ARRAY_SIZE(ad_proprietary_2_4G_resume));
                break;
            default:
                break;
        }

        DBG_LOGI(thisMOD, "hid_scenario_gaming_mode_config_adv, setting = %d", adv_setting->setting_type);
    }
    else {
        DBG_LOGI(thisMOD, " Adv set at wrong state, ignore set, state: %d", g_mode.state);
    }
}
#endif

uint8_t hid_scenario_gaming_mode_config(T_HID_SCENARIO_CONFIG_PARA_S* config)
{
    DBG_LOGI(thisMOD, "hid_scenario_gaming_mode_config");

    switch(config->cfg_type)
    {
        case SCENARIO_SRV_CONFIG_REPORT_RATE:
        {
            hid_scenario_gaming_mode_config_rr((T_REPORT_RATE_CHANGE_S*)config->value);
        }
        break;

        case SECNARIO_SRV_CONFIG_ID_ADDR_DELETE:
        {
            hid_scenario_adv_delete_id();
        }
        break;

        case SECNARIO_SRV_CONFIG_SET_UNIAA:
        {
            bt_ull_le_hid_dm_device_info_t* device_info = (bt_ull_le_hid_dm_device_info_t *)k_malloc(sizeof(bt_ull_le_hid_dm_device_info_t));

            if (device_info == NULL){
                DBG_LOGI(thisMOD, "SECNARIO_SRV_CONFIG_SET_UNIAA fail");
                break;
            }

            uint8_t *value = (uint8_t *)config->pointerValue;
            uint8_t type = CONVERT_RACE_DEVICE_TYPE(*value);
            *value = type;
            device_info->device_type = type;
            memcpy(&device_info->addr, value + ADDR_OFFSET, sizeof(bt_addr_le_t));
            memcpy(&device_info->uni_aa, value + UNI_AA_OFFSET, BT_ULL_LE_HID_DM_UNI_AA_LEN);
            memcpy(&device_info->ltk, value + LTK_OFFSET, BT_ULL_LE_HID_DM_LTK_LEN);
            memcpy(&device_info->skd, value + SKD_OFFSET, BT_ULL_LE_HID_DM_SKD_LEN);
            memcpy(&device_info->iv, value + IV_OFFSET, BT_ULL_LE_HID_DM_IV_LEN);
#if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE)
            device_info->scenario = BT_ULL_LE_HID_SRV_APP_SCENARIO_81;
#elif defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
            device_info->scenario = BT_ULL_LE_HID_SRV_APP_SCENARIO_82;
#elif defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
            device_info->scenario = BT_ULL_LE_HID_SRV_APP_SCENARIO_83;
#else
            #error "Unknown product"
#endif

            DBG_LOGI(thisMOD, "SET_UNIAA, ull_write_device_info, device_type = 0x%X, addr_type = 0x%X, addr = 0x%02X-%02X-%02X-%02X-%02X-%02X, uniaa = 0x%02X-%02X-%02X-%02X",
                            device_info->device_type, device_info->addr.type, device_info->addr.a.val[0], device_info->addr.a.val[1],
                            device_info->addr.a.val[2], device_info->addr.a.val[3], device_info->addr.a.val[4], device_info->addr.a.val[5],
                            device_info->uni_aa[0], device_info->uni_aa[1], device_info->uni_aa[2], device_info->uni_aa[3]
                        );

            int result = bt_ull_le_hid_dm_write_device_info(device_info);
            if(result == NVKEY_STATUS_OK)
            {
                if (device_info)
                {
                    g_mode.peer_record.scenario = device_info->scenario;
                    DBG_LOGI(thisMOD, "device_info->scenario = 0x%X", g_mode.peer_record.scenario);
                }
                else
                {
                    DBG_LOGI(thisMOD, "device_info = NULL");
                    g_mode.peer_record.scenario = 0xFF;
                }

                memcpy(&g_mode.peer_record.peer_addr, &device_info->addr, sizeof(bt_addr_le_t));
                k_free(device_info);
                nvkey_status_t ret = nvkey_write_data(NVID_GAMING_MODE_PEER_DEVICE_INFO_0  + g_mode.link_idx, (const uint8_t*)&g_mode.peer_record, sizeof(T_BOND_RECORD_S));

                DBG_LOGI(thisMOD,"SET_UNIAA, nvkey_write_data complete !! peer_addr.type = 0x%X, peer_addr.val = 0x%02X-%02X-%02X-%02X-%02X-%02X, nvkey_write_data = %d"
                    , g_mode.peer_record.peer_addr.type
                    , g_mode.peer_record.peer_addr.a.val[0]
                    , g_mode.peer_record.peer_addr.a.val[1]
                    , g_mode.peer_record.peer_addr.a.val[2]
                    , g_mode.peer_record.peer_addr.a.val[3]
                    , g_mode.peer_record.peer_addr.a.val[4]
                    , g_mode.peer_record.peer_addr.a.val[5]
                    , ret
                    );

                if(g_mode.peer_record.peer_addr.type != device_info->addr.type){
                    DBG_LOGI(thisMOD, "Notice! addr.type is not match, peer_record = 0x%X, device_info = 0x%X", g_mode.peer_record.peer_addr.type, device_info->addr.type);
                }
            }
            else{
                DBG_LOGI(thisMOD, "bt_ull_le_hid_dm_write_device_info, ret = %d", result);
            }
            break;
        }
        case SECNARIO_SRV_CONFIG_GET_UNIAA:
        {
            bt_addr_le_t address = {0};
            uint8_t device_type = CONVERT_RACE_DEVICE_TYPE(*(uint8_t *)config->value);
            DBG_LOGI(thisMOD, "SECNARIO_SRV_CONFIG_GET_UNIAA, device_type = 0x%X", device_type);

            bt_ull_le_hid_dm_get_bonded_device_list(device_type, 1, &address);
            bt_ull_le_hid_dm_device_info_t *temp_info = bt_ull_le_hid_dm_read_device_info(device_type, &address);

            race_errcode_enum ret = RACE_ERRCODE_SUCCESS;
            if(!temp_info){
                race_errcode_enum ret = hid_race_get_uniaa_rsp(NULL);
                DBG_LOGI(thisMOD, "GET_UNIAA fail, ret = 0x%X", ret);
                break;
            }

            typedef struct {
                uint8_t status;
                uint8_t remote_address[7];
                uint8_t uni_aa[4];
                uint8_t ltk[16];
                uint8_t skd[16];
                uint8_t iv[8];
            } hid_race_rsp_t;

            hid_race_rsp_t *device_info = (hid_race_rsp_t *)k_malloc(sizeof(hid_race_rsp_t));
            if (device_info != NULL && temp_info != NULL)
            {
                device_info->status = 0;
                memcpy(device_info->remote_address, &(temp_info->addr), sizeof(bt_addr_le_t));
                memcpy(device_info->uni_aa, temp_info->uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN);
                memcpy(device_info->ltk, temp_info->ltk, BT_ULL_LE_HID_DM_LTK_LEN);
                memcpy(device_info->skd, temp_info->skd, BT_ULL_LE_HID_DM_SKD_LEN);
                memcpy(device_info->iv, temp_info->iv, BT_ULL_LE_HID_DM_IV_LEN);
            }

            ret = hid_race_get_uniaa_rsp((uint8_t*)device_info);
            DBG_LOGI(thisMOD, "GET_UNIAA, hid_race_get_uniaa_rsp, ret = 0x%X", ret);
            k_free(device_info);
            break;
        }
        #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
        case SECNARIO_SRV_CONFIG_GAMING_ADV:
        {
            hid_scenario_gaming_mode_config_adv((T_GAMING_ADV_SETTING_S*)config->value);
            break;
        }
        #endif
        default:{
            return 1;
            break;
        }
    }

    return 0;
}

bool hid_scenario_gaming_mode__bt_trigger_peripheral_hw(uint32_t enable)
{
    if (g_mode.bt_conn_ptr){
        T_BT_TRIGGER_TYPE_S params;
        params.connection_handle = g_mode.bt_conn_ptr->handle;
        params.TriggerType = TRIGGER_TYPE_SPI;

        if (enable){
            params.ActionMode = ACTION_MODE_RESUME;
        }
        else{
            params.ActionMode = ACTION_MODE_PAUSE;
        }

        DBG_LOGI(thisMOD, "hid_scenario_gaming_mode__bt_trigger_peripheral_hw , enable = %d, connection_handle = 0x%X, ActionMode = %d"
            , enable
            , g_mode.bt_conn_ptr->handle
            , params.ActionMode
        );

        hid_vendor_set_peripheral_trigger(&params);
        return 0;
    }
    else{
        return -1;
    }
}

uint8_t hid_scenario_gaming_mode__get_state()
{
    return g_mode.state;
}

static void hid_scenario_gaming_mode_acl_event_submit(struct bt_conn *conn, uint8_t reason, T_G_MODE_CONN_EVENT_E event)
{
    struct bt_conn_info info;
    int err = bt_conn_get_info(conn, &info);

    if (err) {
        DBG_LOGI(thisMOD,"bt_conn_get_info, err(%d)\n",  err);
        return;
    }

    acl_event_fifo_t * acl_event_fifo = (acl_event_fifo_t * )k_malloc(sizeof(acl_event_fifo_t));
    assert(acl_event_fifo != NULL && "acl_event_fifo malloc failed");

    if (acl_event_fifo) {
        memcpy(&acl_event_fifo->info, &info, sizeof(struct bt_conn_info));
        acl_event_fifo->reason = reason;
        acl_event_fifo->event = event;
        k_fifo_put(&g_mode.acl_fifo, acl_event_fifo);
        air_daemon_wq_work_submit(&job_g_mode_acl_event);
    }
    DBG_LOGI(thisMOD,"hid_scenario_gaming_mode_acl_event_submit = %d", info.state);
}

static void hid_scenario_gaming_mode_acl_connected(struct bt_conn *conn, uint8_t err)
{
    if(hid_scenario_get() == HID_SCENARIO_GAMING_MODE)
    {
        if (err) {
            DBG_LOGI(thisMOD,"Failed to connect, err(%u)\n",  err);
            return;
        }
        struct bt_conn_info info;
        bt_conn_get_info(conn, &info);
        if(info.role == 0x80 || info.role == 0x81)
        {
            DBG_LOGI(thisMOD,"Gaming Mode pseduo Connected");
            return;
        }
        hid_scenario_gaming_mode_acl_event_submit(conn, 0, G_MODE_CONNECTED);
    }
}

static void hid_scenario_gaming_mode_acl_disconnected(struct bt_conn *conn, uint8_t reason)
{
    if((hid_scenario_get() == HID_SCENARIO_GAMING_MODE) && (g_mode.state != MODE_CLOSED))
    {

        struct bt_conn_info info;
        bt_conn_get_info(conn, &info);
        if(info.role == 0x80 || info.role == 0x81)
        {
            DBG_LOGI(thisMOD,"Gaming Mode pseduo Disconnected, reason = 0x%x", reason);
            return;
        }
        hid_scenario_gaming_mode_acl_event_submit(conn, reason, G_MODE_DISCONNECTED);

    }
   
}


BT_CONN_CB_DEFINE(conn_cbs_gaming_conn) = {
    .connected = hid_scenario_gaming_mode_acl_connected,
    .disconnected = hid_scenario_gaming_mode_acl_disconnected,
    // .security_changed = app_conn_security_changed,
};