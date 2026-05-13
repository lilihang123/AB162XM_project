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

#include "app_scenario.h"
#include "af_events_declaration.h"
#include "app_links.h"
#include "app_usb_port.h"
#include "hid_scenario_service.h"
#include "hid_scenario_report_rate.h"
#include "app_factory_reset.h"
#include "app_power_manager.h"
#include <stdint.h>
#include <zephyr/bluetooth/bluetooth.h>

#define thisMOD    "app_scenario"
#define thisMODULE  app_scenario
LOG_MODULE_REGISTER(thisMODULE);


typedef enum
{
    NEXT_PROCESS_NULL,
    NEXT_PROCESS_START,
    NEXT_PROCESS_STOP,
    NEXT_PROCESS_CLOSE,
}T_NEXT_PROCESS_E;

typedef enum {
    PROS_STATUS_IDLE,
    PROS_STATUS_WORKING,
}T_SCENARIO_PROCESS_STATUS_E;

/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/

//static void app_scenario_switch_to_next_link(struct k_work *work);
//static K_WORK_DEFINE(job_link_next, app_scenario_switch_to_next_link);

// static void app_scenario_next_process(struct k_work *work);
// static K_WORK_DEFINE(job_next_process, app_scenario_next_process);
static void app_scenario_next_process_announcement();
static void app_scenario_status_announcement(uint8_t scenario_status, uint8_t reason);
static void app_scenario_RR_status_announcement(uint8_t category, uint16_t rr);
static void app_scenario_config_delete_id_addr();
static void app_scenario_bt_mode_start(struct k_timer *timer_id);
#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
static bool app_scenario_config_adv_data(T_GAMING_ADV_SETTING_S *setting);
#endif
/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
uint8_t scenario_device_type = 0;
uint8_t scenario_mode = MODE_NONE;
uint8_t scenario_process_status = PROS_STATUS_IDLE;
uint8_t scenario_link_next = false;
uint8_t scenario_next_process = 0;
struct k_timer bt_mode_start_timer;
/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/

static void app_scenario_state_update(uint8_t scenario_state, uint8_t change_reason)
{
    scenario_process_status = PROS_STATUS_IDLE;
    scenario_mode = scenario_state;

    APP_LOGI(thisMOD,"app_scenario_state_update, scenario_state = 0x%02X, change_reason = %d ", scenario_state , change_reason);

    switch(scenario_state)
    {
        case MODE_CLOSED:
        {
            // if (scenario_link_next){
            //     scenario_link_next = false;
            //     APP_LOGI(thisMOD,"job_link_next");
            //     k_work_submit(&job_link_next);
            // }

            // Clear this flag otherwise the return value of app_scenario_get_scenario_type will be incorrect
            scenario_device_type = HID_SCENARIO_NONE;

            APP_LOGI(thisMOD,"MODE_CLOSED");
            k_timer_stop(&bt_mode_start_timer);
            app_scenario_status_announcement(scenario_state, change_reason);
        }
        break;

        case MODE_OPEN_SPECIFIED:
        case MODE_OPEN_UNSPECIFIED:
        #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
        case MODE_OPEN_SPECIFIED_RESUME:
        #endif
        {
            app_scenario_status_announcement(scenario_state, change_reason);
        }
        break;

        case MODE_OPEN_USB_CONNECTED:
        {
            APP_LOGI(thisMOD,"MODE_OPEN_USB_CONNECTED");
            app_scenario_status_announcement(scenario_state, change_reason);
            uint8_t plug_status = APP_USB_PLUG_OUT;
            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
            plug_status = app_usb_port__get_usb_plug_status();
            #endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/
            if(plug_status == APP_USB_PLUG_OUT)
            {
                scenario_next_process = NEXT_PROCESS_CLOSE;
                APP_LOGI(thisMOD,"MODE_OPEN_USB_CONNECTED job_next_process -> CLOSE");
                app_scenario_next_process_announcement();
            }
            else
            {
                scenario_next_process = NEXT_PROCESS_START;
                APP_LOGI(thisMOD,"MODE_OPEN_USB_CONNECTED job_next_process -> START");
                app_scenario_next_process_announcement();
            }
        }
        break;

        case MODE_OPEN_CONNECTED:
        {
            app_scenario_status_announcement(scenario_state, change_reason);
            APP_LOGI(thisMOD,"MODE_OPEN_CONNECTED");
        }
        break;

        #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        case MODE_OPEN_CONNECTED_CCCD_READY:
        {
            APP_LOGI(thisMOD,"MODE_OPEN_CONNECTED_CCCD_READY");
            app_scenario_status_announcement(scenario_state, change_reason);
            if(BT_ENCRYPTED_CCCD_READY(hid_common->hid.flags))
            {
                k_timer_stop(&bt_mode_start_timer);
                k_timer_start(&bt_mode_start_timer, K_MSEC(BT_MODE_HID_REPORT_START_TIMEOUT), K_NO_WAIT);
            }
        }
        break;

        case MODE_OPEN_CONNECTED_ENCRYPTED:
        {
            APP_LOGI(thisMOD,"MODE_OPEN_CONNECTED_ENCRYPTED");
            app_scenario_status_announcement(scenario_state, change_reason);
            if(BT_ENCRYPTED_CCCD_READY(hid_common->hid.flags))
            {
                k_timer_stop(&bt_mode_start_timer);
                k_timer_start(&bt_mode_start_timer, K_MSEC(BT_MODE_HID_REPORT_START_TIMEOUT), K_NO_WAIT);
            }
        }
        break;
        #endif

        case MODE_OPEN_CIS_SERVICE_READY:
        {
            app_scenario_status_announcement(scenario_state, change_reason);
            scenario_next_process = NEXT_PROCESS_START;
            APP_LOGI(thisMOD,"MODE_OPEN_CIS_SERVICE_READY, job_next_process");
            app_scenario_next_process_announcement();
        }
        break;

        case MODE_STOPPED:
        case MODE_USB_STOPPED:
        {
            APP_LOGI(thisMOD,"MODE_STOPPED");
            app_scenario_status_announcement(scenario_state, change_reason);
        }
        break;

        case MODE_USB_RESUME:
        {
            APP_LOGI(thisMOD,"MODE_USB_RESUME");
            app_scenario_status_announcement(scenario_state, change_reason);
        }
        break;

        case MODE_USB_STARTED:
        case MODE_STARTED:
        {
            APP_LOGI(thisMOD,"MODE_STARTED");
            app_scenario_status_announcement(scenario_state, change_reason);
        }
        break;

        default:
        break;
    }
}


static void app_scenario__hid_scenario_notification(uint32_t event, void *param, uint32_t param_len)
{
    switch(event)
    {
        case SS_EVT_STATE_UPDATE:
        {
            T_SCENARIO_SERVICE_STATE_UPDATE_S * scenario_update = (T_SCENARIO_SERVICE_STATE_UPDATE_S*)param;
            app_scenario_state_update(scenario_update->state , scenario_update->reason);
        }
        break;

        case SS_EVT_USB_REPORT_RATE_UPDATE:
        {
            app_scenario_RR_status_announcement(MODE_TYPE_USB, *(uint16_t *)param);

        }
        break;

        case SS_EVT_GAMING_REPORT_RATE_UPDATE:
        {
            app_scenario_RR_status_announcement(MODE_TYPE_GAMING, *(uint16_t *)param);
        }
        break;

        #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        case SS_EVT_BT_REPORT_RATE_UPDATE:
        {
            app_scenario_RR_status_announcement(MODE_TYPE_BT, *(uint16_t *)param);
        }
        break;
        #endif

        #if defined(CONFIG_AIR_HID_OUTPUT_REPORT_NOTIFY)
        case SS_EVT_HID_OUTPUT_REPORT:
        {
            struct evt_hid_output_report* event = create_evt_hid_output_report_ex(param_len);
            if (event){
                event->length = param_len;
                memcpy(event->output_report, param, param_len);
                AF_EVT_SUBMIT(event);

                APP_LOGI(thisMOD,"Submit evt_hid_output_report, param_len = %d, param = 0x%08X"
                    , param_len
                    , param
                );                
            }
        }
        break;
        #endif

        default:
        break;
    }
}

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static void app_scenario_next_process_announcement()
{
    struct evt_job_next_process* event = (struct evt_job_next_process*)create_evt_job_next_process();

    if (event){
        AF_EVT_SUBMIT(event);
    }
}

static void app_scenario_bt_mode_start(struct k_timer *timer_id)
{
    scenario_next_process = NEXT_PROCESS_START;
    APP_LOGI(thisMOD,"MODE_OPEN_CONNECTED_ENCRYPTED and MODE_OPEN_CONNECTED_CCCD_READY, job_next_process");
    app_scenario_next_process_announcement();
}

static void app_scenario_status_announcement(uint8_t scenario_status, uint8_t reason)
{
    APP_LOGI(thisMOD,"app_scenario_status_announcement = 0x%02X \n ", scenario_status);

    struct evt_scenario_status* status_event = (struct evt_scenario_status*)create_evt_scenario_status();

    if (status_event){
        status_event->status = scenario_status;
        status_event->reason = reason;
        AF_EVT_SUBMIT(status_event);
    }
}

static void app_scenario_RR_status_announcement(uint8_t category, uint16_t rr)
{
    APP_LOGI(thisMOD,"app_scenario_RR_status_announcement rr = %u \n ", rr);
    struct evt_rr_status *rr_event = (struct evt_rr_status*)create_evt_rr_status();

    if (rr_event){
        rr_event->category = category;
        rr_event->RR = rr;
        AF_EVT_SUBMIT(rr_event);
    }
}

static void app_scenario_race_cmd_rsp_announcement(T_RACE_CMD_E cmd, uint16_t result)
{
    APP_LOGI(thisMOD,"app_scenario_race_cmd_rsp_announcement result = %d", result);
    struct evt_race_cmd_rsp* event = create_evt_race_cmd_rsp();
    if (event){
        event->cmd = cmd;
        event->RR.result = result;
        event->OTHERS.status = (uint8_t) result;
        AF_EVT_SUBMIT(event);
    }
}

static bool app_scenario_evt_conn_req(const struct af_evt_header *evt_header)
{
    struct evt_conn_req* event = (struct evt_conn_req*)evt_header;

    uint8_t link_idx = app_links_get_link_idx();

    APP_LOGI(thisMOD,"evt_conn_req , cmd = %d, link_idx = %d , device_type = %d, mode = %d"
        , event->cmd
        , link_idx
        , scenario_device_type
        , scenario_mode
        );

    switch(event->cmd)
    {
        case CONN_REQ_CONN_NEW:
        {
            APP_LOGI(thisMOD,"CONN_REQ_CONN_NEW at %d ", __LINE__);
            if (app_links_read_link_type() == LINKT_TYPE_2_4G) {
                scenario_device_type = HID_SCENARIO_GAMING_MODE;
                app_power_mgr_system_low_clock_disable();
            }
            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
            else {
                scenario_device_type = HID_SCENARIO_BT_MODE;
            }
            #endif
            if(app_factory_reset_get_status())
            {
                app_scenario_config_delete_id_addr();
                app_factory_reset_clear_status();
            }
            hid_scenario_open(scenario_device_type, link_idx, 1, 0);
        }
        break;

        case CONN_REQ_CONN_LAST_LINK:
        {
            APP_LOGI(thisMOD,"CONN_REQ_CONN_LAST_LINK at %d ", __LINE__);
            if(app_factory_reset_get_status())
            {
                app_scenario_config_delete_id_addr();
                app_factory_reset_clear_status();
            }
            if (app_links_read_link_type() == LINKT_TYPE_2_4G) {
                scenario_device_type = HID_SCENARIO_GAMING_MODE;
                app_power_mgr_system_low_clock_disable();
                #if defined (CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE)
                T_GAMING_ADV_SETTING_S adv_setting;
                adv_setting.setting_type = ADV_SETTING_DEFAULT;
                app_scenario_config_adv_data(&adv_setting);
                #endif
                hid_scenario_open(scenario_device_type, link_idx, 0, event->reconnect_timeout_2_4G);
            }
            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
            else {
                scenario_device_type = HID_SCENARIO_BT_MODE;
                hid_scenario_open(scenario_device_type, link_idx, 0, 0);
            }
            #endif
        }
        break;

        case CONN_REQ_CONN_NEXT_LINK:
        {
            APP_LOGI(thisMOD,"CONN_REQ_CONN_NEXT_LINK at %d ", __LINE__);

            #if defined (CONFIG_AIR_M20_SAMPLE)
            // Reset workaround
            app_links_change_to_next_link_idx();
            hid_scenario_close(scenario_device_type, 0);
            #else
            hid_scenario_close(scenario_device_type, 0);
            // change link idx after closing the scenario;
            app_links_change_to_next_link_idx();
            #endif
            if(scenario_device_type == HID_SCENARIO_GAMING_MODE)
            {
                app_power_mgr_system_low_clock_disable();
            }
            #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
            else
            {
                k_timer_stop(&bt_mode_start_timer);
            }
            #endif
        }
        break;

        case CONN_REQ_CANCEL_CONN:
        case CONN_REQ_DISC:
        {
            APP_LOGI(thisMOD,"CONN_REQ_DISC at %d, scenario_device_type = %d", __LINE__, scenario_device_type);
            hid_scenario_close(scenario_device_type, 0);
            if(scenario_device_type == HID_SCENARIO_GAMING_MODE)
            {
                app_power_mgr_system_low_clock_disable();
            }
            #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
            else
            {
                k_timer_stop(&bt_mode_start_timer);
            }
            #endif
        }
        break;

        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
        case CONN_REQ_CONN_USB:
        {
            #if 0
            APP_LOGI(thisMOD,"[SWLA]label_usb_connect START");
            HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_usb_connect, SWLA_DIRECTION_START);
            #endif

            APP_LOGI(thisMOD,"CONN_REQ_CONN_USB at %d ", __LINE__);
            if(scenario_process_status == PROS_STATUS_IDLE)
            {
                scenario_process_status = PROS_STATUS_WORKING;
                scenario_device_type = HID_SCENARIO_USB_MODE;
                hid_scenario_open(scenario_device_type, 0, 0, 0);

                // app_usb_port__change_state_to_open_usb_mode();
            }
            else{
                APP_LOGI(thisMOD,"CONN_REQ_CONN_USB but scenario_process_status is working");
            }
        }
        break;
        #endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/

        case CONN_REQ_CONN_LAST_GAMING_LINK:
        {
            APP_LOGI(thisMOD,"CONN_REQ_CONN_LAST_GAMING_LINK at %d", __LINE__);
            scenario_device_type = HID_SCENARIO_GAMING_MODE;
            app_power_mgr_system_low_clock_disable();
            link_idx = app_links_get_link_idx();

            APP_LOGI(thisMOD,"CONN_REQ_CONN_LAST_GAMING_LINK, link_idx = %d", link_idx);
            #if defined (CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE)
            T_GAMING_ADV_SETTING_S adv_setting;
            adv_setting.setting_type = ADV_SETTING_DEFAULT;
            app_scenario_config_adv_data(&adv_setting);
            #endif
            hid_scenario_open(scenario_device_type, link_idx, 0, event->reconnect_timeout_2_4G);
        }
        break;

        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        case CONN_REQ_CONN_LAST_BT_LINK:
        {
            APP_LOGI(thisMOD,"CONN_REQ_CONN_LAST_BT_LINK at %d", __LINE__);
            scenario_device_type = HID_SCENARIO_BT_MODE;
            link_idx = app_links_get_link_idx();

            APP_LOGI(thisMOD,"CONN_REQ_CONN_LAST_BT_LINK, link_idx = %d", link_idx);
            hid_scenario_open(scenario_device_type, link_idx, 0, 0);
        }
        break;
        #endif

        case CONN_REQ_IDLE_1:
        {
            APP_LOGI(thisMOD,"CONN_REQ_IDLE_1");
            hid_scenario_stop(scenario_device_type, SCENARIO_IDLE1_STOP);
        }
        break;

        case CONN_REQ_IDLE_2:
        {
            APP_LOGI(thisMOD,"CONN_REQ_IDLE_2");
            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
            if(scenario_device_type == HID_SCENARIO_BT_MODE)
            {
                hid_scenario_stop(scenario_device_type, SCENARIO_IDLE2_STOP);
            }
            else
            #endif
            if (scenario_device_type == HID_SCENARIO_GAMING_MODE) {
                if(scenario_mode == MODE_STOPPED)
                {
                    app_scenario_status_announcement(scenario_mode, SCENARIO_STATE_CHANGE_REASON_NONE);
                }
                else
                {
                    hid_scenario_stop(scenario_device_type, SCENARIO_IDLE2_STOP);
                }
            }
        }
        break;

        case CONN_REQ_ACTIVE:
        {
            if(scenario_process_status == PROS_STATUS_IDLE)
            {
                scenario_process_status = PROS_STATUS_WORKING;
                APP_LOGI(thisMOD,"CONN_REQ_ACTIVE at %d", __LINE__);
                hid_scenario_start(scenario_device_type, link_idx, NULL);
            }
            else{
                APP_LOGI(thisMOD,"CONN_REQ_ACTIVE but scenario_process_status is working");
            }
        }
        break;
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
        case CONN_REQ_ACTIVE_USB:
        {
            if(scenario_process_status == PROS_STATUS_IDLE)
            {
                scenario_process_status = PROS_STATUS_WORKING;
                APP_LOGI(thisMOD,"CONN_REQ_ACTIVE_USB at %d", __LINE__);
                if(app_usb_port__get_usb_plug_status() == APP_USB_CONFIGURED){
                    hid_scenario_start(scenario_device_type, link_idx, NULL);
                }
                else
                {
                    APP_LOGI(thisMOD,"hid_scenario_close type = %d", scenario_device_type);
                    hid_scenario_close(scenario_device_type, 0);
                }

            }
            else{
                APP_LOGI(thisMOD,"CONN_REQ_ACTIVE_USB but scenario_process_status is working");
            }
        }
        break;

        case CONN_REQ_STOP_USB:
        {
            if(scenario_process_status == PROS_STATUS_IDLE)
            {
                    scenario_process_status = PROS_STATUS_WORKING;
                    APP_LOGI(thisMOD,"CONN_REQ_STOP_USB at %d", __LINE__);
                    hid_scenario_stop(scenario_device_type, SCENARIO_USB_STOP);
            }
            else{
                    APP_LOGI(thisMOD,"CONN_REQ_STOP_USB but scenario_process_status is working");
            }
        }
        break;
        #endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE */
        #if defined (CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE)
        case CONN_REQ_RESUME_WAIT:
        {
            APP_LOGI(thisMOD,"CONN_REQ_RESUME_WAIT, link_type: %d", app_links_read_link_type());
            if (app_links_read_link_type() == LINKT_TYPE_2_4G) {
                scenario_device_type = HID_SCENARIO_GAMING_MODE;
                app_power_mgr_system_low_clock_disable();
                T_GAMING_ADV_SETTING_S adv_setting;
                adv_setting.setting_type = ADV_SETTING_RESUME_WAIT;
                app_scenario_config_adv_data(&adv_setting);
                hid_scenario_open(scenario_device_type, link_idx, SCENARIO_SRV_OPEN_RESUME_WAIT, 0);
            }
            break;
        }
        #endif
        default:
            APP_LOGI(thisMOD,"Unexpected error at %d ", __LINE__);
            break;
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_scenario_evt_job_next_process(const struct af_evt_header *evt_header)
{
    uint8_t link_idx;
    link_idx = app_links_get_link_idx();

    APP_LOGI(thisMOD,"app_scenario_evt_job_next_process = %d,   link_idx = %d",scenario_next_process,link_idx);

    switch(scenario_next_process)
    {
        case NEXT_PROCESS_START:
        {
            if(scenario_process_status == PROS_STATUS_IDLE)
            {
                scenario_process_status = PROS_STATUS_WORKING;
                APP_LOGI(thisMOD,"hid_scenario_start type = %d", scenario_device_type);
                hid_scenario_start(scenario_device_type, link_idx, NULL);
            }
            else{
                APP_LOGI(thisMOD,"NEXT_PROCESS_START but scenario_process_status is working");
            }
            break;
        }
        case NEXT_PROCESS_CLOSE:
        {
            if(scenario_process_status == PROS_STATUS_IDLE)
            {
                scenario_process_status = PROS_STATUS_WORKING;
                APP_LOGI(thisMOD,"hid_scenario_close type = %d", scenario_device_type);
                hid_scenario_close(scenario_device_type, 0);
                if(scenario_device_type == HID_SCENARIO_GAMING_MODE)
                {
                    app_power_mgr_system_low_clock_disable();
                }
                #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
                else
                {
                    k_timer_stop(&bt_mode_start_timer);
                }
                #endif
            }
            else{
                APP_LOGI(thisMOD,"NEXT_PROCESS_CLOSE but scenario_process_status is working");
            }
            break;
        }
        case NEXT_PROCESS_STOP:
        {
            break;
        }
        default:{
            break;
        }
    }
    return AF_TRAVERSE_NEXT;
}

static bool app_scenario_evt_enter_test(const struct af_evt_header *evt_header)
{
    struct evt_enter_test* event = (struct evt_enter_test*)evt_header;
    APP_LOGI(thisMOD,"app_scenario_evt_enter_test, type = %d", event->type);

    switch(event->type)
    {
        case TEST_TYPE_RELAY_MODE:
        case TEST_TYPE_LAB_TEST:
        {
            if(scenario_device_type == HID_SCENARIO_USB_MODE)
            {
                APP_LOGI(thisMOD,"USB in test mode at %d", __LINE__);
                hid_scenario_stop(scenario_device_type, SCENARIO_USB_STOP);
            }
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_scenario_config_report_rate(uint8_t type, uint16_t para, uint8_t restore_or_chg_profile)
{
    APP_LOGI(thisMOD,"app_scenario_config_report_rate, type = %d, para = %d ", type, para);

    T_HID_SCENARIO_CONFIG_PARA_S config;
    T_REPORT_RATE_CHANGE_S* rr_change = (T_REPORT_RATE_CHANGE_S*)config.value;
    rr_change->type = type;
    rr_change->para = para;
    rr_change->restore_or_chg_profile = restore_or_chg_profile;
    config.len = sizeof(T_REPORT_RATE_CHANGE_S);
    config.cfg_type = SCENARIO_SRV_CONFIG_REPORT_RATE;
    assert( sizeof(config.value)>=sizeof(T_REPORT_RATE_CHANGE_S ));

    hid_scenario_config(scenario_device_type, &config);
    return 0;
}

#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
static bool app_scenario_config_adv_data(T_GAMING_ADV_SETTING_S *setting)
{
    APP_LOGI(thisMOD,"app_scenario_config_adv_data");

    T_HID_SCENARIO_CONFIG_PARA_S config;
    T_GAMING_ADV_SETTING_S* adv_setting = (T_GAMING_ADV_SETTING_S*)config.value;
    adv_setting->setting_type = setting->setting_type;
    config.len = sizeof(T_GAMING_ADV_SETTING_S);
    config.cfg_type = SECNARIO_SRV_CONFIG_GAMING_ADV;

    hid_scenario_config(HID_SCENARIO_GAMING_MODE, &config);
    return 0;
}
#endif

static bool app_scenario_config_set_uniaa(uint8_t* info)
{
    APP_LOGI(thisMOD,"app_scenario_config_set_uniaa");

    T_HID_SCENARIO_CONFIG_PARA_S config;

    config.pointerValue = info;
    config.len = sizeof(T_HID_SCENARIO_CONFIG_PARA_S);
    config.cfg_type = SECNARIO_SRV_CONFIG_SET_UNIAA;

    // hid_scenario_config(scenario_device_type, &config);
    hid_scenario_config(HID_SCENARIO_GAMING_MODE, &config);
    return 0;
}

static void app_scenario_config_get_uniaa(uint8_t type)
{
    APP_LOGI(thisMOD,"app_scenario_config_get_uniaa");

    T_HID_SCENARIO_CONFIG_PARA_S config;

    config.value[0] = type;
    config.len = sizeof(T_HID_SCENARIO_CONFIG_PARA_S);
    config.cfg_type = SECNARIO_SRV_CONFIG_GET_UNIAA;

    // hid_scenario_config(scenario_device_type, &config);
    hid_scenario_config(HID_SCENARIO_GAMING_MODE, &config);
    return;
}

static bool app_scenario_evt_rr_change_req_handler(const struct af_evt_header *evt_header)
{
    struct evt_rr_change_req* event = (struct evt_rr_change_req*)evt_header;
    APP_LOGI(thisMOD,"app_scenario_evt_rr_change_req_handler, change_type = %d,  RR = %d, RR_CHANGE_NEXT = %d \n ", event->change_type, event->RR, RR_CHANGE_NEXT);

    switch(event->change_type)
    {
        case RR_CHANGE_NEXT:
        {
            app_scenario_config_report_rate(CONFIG_RR_NEXT, 0, event->restore_or_chg_profile);
        }
        break;

        case RR_CHANGE_PREV:
        {
            app_scenario_config_report_rate(CONFIG_RR_PREV, 0, event->restore_or_chg_profile);
        }
        break;

        case RR_CHANGE_SPECIFIC:
        {
            app_scenario_config_report_rate(CONFIG_RR_SPECIFIC_VAL, event->RR, event->restore_or_chg_profile);
        }
        break;
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_scenario_evt_race_cmd_req(const struct af_evt_header *evt_header)
{
    struct evt_race_cmd_req* event = (struct evt_race_cmd_req*)evt_header;
    uint16_t res;
    uint16_t now_rr = app_scenario_get_report_rate();
    APP_LOGI(thisMOD,"evt_race_cmd_req , cmd = %x", event->cmd);

    switch(event->cmd)
    {
        case RACE_CMD_SET_REPORT_RATE:
        {
            APP_LOGI(thisMOD,"set report rate now_rr = %d to new_rr = %d", now_rr, event->RR.value);
            if(event->RR.value != now_rr)
            {
                struct evt_rr_change_req* rr_event = create_evt_rr_change_req();
                if (rr_event){
                    rr_event->change_type = RR_CHANGE_SPECIFIC;
                    rr_event->RR = event->RR.value;
                    rr_event->restore_or_chg_profile = false;
                    AF_EVT_SUBMIT(rr_event);
                }
            }

            app_scenario_race_cmd_rsp_announcement(RACE_CMD_SET_REPORT_RATE, 0);
        }
        break;

        case RACE_CMD_GET_REPORT_RATE:
        {
            res = app_scenario_get_report_rate();
            app_scenario_race_cmd_rsp_announcement(RACE_CMD_GET_REPORT_RATE, res);
        }
        break;

        case RACE_CMD_SET_PROFILE:
        {
            hid_scenario_report_rate_change_profile(event->PROFILE.id);
            hid_scenario_report_rate_change(MODE_TYPE_GAMING, RR_CHANGE_SPECIFIC, 0, true);
            uint16_t new_rr = app_scenario_get_new_report_rate();
            APP_LOGI(thisMOD,"set profile id = %d now_rr = %d to new_rr = %d", event->PROFILE.id, now_rr, new_rr);
            if(now_rr != new_rr)
            {
                struct evt_rr_change_req* rr_event = create_evt_rr_change_req();
                if (rr_event){
                    rr_event->change_type = RR_CHANGE_SPECIFIC;
                    rr_event->RR = 0;
                    rr_event->restore_or_chg_profile = true;
                    AF_EVT_SUBMIT(rr_event);
                }
            }
            app_scenario_race_cmd_rsp_announcement(RACE_CMD_SET_PROFILE, 0);
        }
        break;

        case RACE_CMD_SET_RESTORE:
        {
            hid_scenario_report_rate_restore();
            uint16_t new_rr = app_scenario_get_new_report_rate();
            APP_LOGI(thisMOD,"set restore, now_rr = %d to new_rr = %d", now_rr, new_rr);
            if(now_rr != new_rr)
            {
                struct evt_rr_change_req* rr_event = create_evt_rr_change_req();
                if (rr_event){
                    rr_event->change_type = RR_CHANGE_SPECIFIC;
                    rr_event->RR = REPORT_RATE_MAX;
                    rr_event->restore_or_chg_profile = true;
                    AF_EVT_SUBMIT(rr_event);
                }
            }

            app_scenario_race_cmd_rsp_announcement(RACE_CMD_SET_RESTORE, 0);
        }
        break;

        case RACE_CMD_SET_UNIAA:
        {
            res = app_scenario_config_set_uniaa((uint8_t*)&event->UNIAA.pair_device_type);
            app_scenario_race_cmd_rsp_announcement(RACE_CMD_SET_UNIAA, res);
            break;
        }
        case RACE_CMD_GET_UNIAA:
        {
            app_scenario_config_get_uniaa(event->UNIAA.pair_device_type);
            break;
        }

        default:{
            break;
        }

    }
    return AF_TRAVERSE_NEXT;
}

static void app_scenario_config_delete_id_addr()
{
    APP_LOGI(thisMOD,"app_scenario_config_delete_identity_addr");

    T_HID_SCENARIO_CONFIG_PARA_S config = {0};
    config.cfg_type = SECNARIO_SRV_CONFIG_ID_ADDR_DELETE;

    hid_scenario_config(HID_SCENARIO_BT_MODE, &config);
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
bool app_scenario_init(uint8_t profile_idx)
{
    APP_LOGI(thisMOD,"app_scenario_init");
    hid_scenario_init(app_scenario__hid_scenario_notification, profile_idx);
    k_timer_init(&bt_mode_start_timer , app_scenario_bt_mode_start, NULL);
    return 0;
}

uint8_t app_scenario_get_current_device_type()
{
    return scenario_device_type;
}

uint8_t app_scenario_get_current_mode()
{
    return scenario_device_type;
}

uint16_t app_scenario_get_report_rate()
{
    if(scenario_device_type == HID_SCENARIO_USB_MODE){
        return hid_scenario_read_now_report_rate(MODE_TYPE_USB);
    }
    else{
        return hid_scenario_read_now_report_rate(MODE_TYPE_GAMING);
    }
}

uint16_t app_scenario_get_new_report_rate()
{
    if(scenario_device_type == HID_SCENARIO_USB_MODE){
        return hid_scenario_read_new_report_rate(MODE_TYPE_USB);
    }
    else{
        return hid_scenario_read_new_report_rate(MODE_TYPE_GAMING);
    }
}

uint8_t app_scenario_get_scenario_type()
{
    uint8_t type = HID_SCENARIO_NONE;
    uint8_t  incoming_scenario_type = HID_SCENARIO_NONE;

    if (scenario_device_type != HID_SCENARIO_NONE){
        APP_LOGI(thisMOD,"app_scenario_get_scenario_type, scenario_device_type = %d", scenario_device_type);
        type =  scenario_device_type;
    }
    else {
        #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
        if (app_usb_port__get_usb_plug_status() == APP_USB_CONFIGURED){
            incoming_scenario_type = HID_SCENARIO_USB_MODE;
        }
        else
        #endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE */
        {
            if (app_links_read_link_type() == LINKT_TYPE_2_4G){
                incoming_scenario_type = HID_SCENARIO_GAMING_MODE;
            }
            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
            else {
                incoming_scenario_type = HID_SCENARIO_BT_MODE;
            }
            #endif
        }
        type = incoming_scenario_type;
    }

    APP_LOGI(thisMOD,"app_scenario_get_current_scenario_type, scenario_device_type = %d, incoming_scenario_type = %d", scenario_device_type, incoming_scenario_type);
    return type;
}

uint8_t app_scenario_config_bt_trigger_type(uint8_t trigger_type)
{
    APP_LOGI(thisMOD,"app_scenario_config_bt_trigger, trigger_type = %d ", trigger_type);

    T_HID_SCENARIO_CONFIG_PARA_S config;
    T_BT_TRIGGER_TYPE_S* bt_trigger_type = (T_BT_TRIGGER_TYPE_S*)config.value;

    bt_trigger_type->connection_handle = 0;
    bt_trigger_type->TriggerType = trigger_type;
    bt_trigger_type->ActionMode = ACTION_MODE_AUTO;

    config.len = sizeof(T_HID_SCENARIO_CONFIG_PARA_S);
    config.cfg_type = SECNARIO_SRV_CONFIG_BT_TRIGGER;

    return hid_scenario_config(HID_SCENARIO_NONE, &config);
}



/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_rr_change_req, app_scenario_evt_rr_change_req_handler);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_conn_req, app_scenario_evt_conn_req);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_race_cmd_req, app_scenario_evt_race_cmd_req);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_job_next_process, app_scenario_evt_job_next_process);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_enter_test, app_scenario_evt_enter_test);
/*=============================================================================*/
