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


#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>

#include "app_state.h"
#include "app_scenario.h"

#include "race_event.h"
#include "race_fota.h"

#define thisMODULE fota_status
#define thisMOD    "fota_status"
LOG_MODULE_REGISTER(thisMODULE);

/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
static void app_fota_status_evt_rr_change_req_announcement(T_RR_CHANGE_TYPE_E type, uint16_t rr, uint8_t optional);
static uint8_t app_fota_status_restore_report_rate();
bool app_fota_status__get_fota_state(void);

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
#ifdef MTK_RACE_EVENT_ID_ENABLE
static int32_t APP_RACE_ID;
#endif

#define APP_FOTA_SET_RR     125

uint32_t fota_restore_rr_flag = 0;

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/
#ifdef MTK_RACE_EVENT_ID_ENABLE
static RACE_ERRCODE app_fota_status__race_event_cb(int32_t register_id, race_event_type_enum event_type, void *param, void *user_data)
#else
static RACE_ERRCODE app_fota_status__race_event_cb(race_event_type_enum event_type, void *param, void *user_data)
#endif
{
    #ifdef MTK_RACE_EVENT_ID_ENABLE
    APP_LOGI(thisMOD,"race_event_cb, register_id[%d] event_type[%d] param[0x%X] user_data[0x%X]", register_id, event_type, param, user_data);

    if (APP_RACE_ID != register_id) {
        APP_LOGI(thisMOD,"race_event_cb, register_id does not match! register_id is %d", register_id);
        return RACE_ERRCODE_PARAMETER_ERROR;
    }
    #else
    APP_LOGI(thisMOD,"race_event_cb, event_type[%d] param[0x%X] user_data[0x%X]", event_type, param, user_data);
    #endif

    switch (event_type)
    {
        case RACE_EVENT_TYPE_FOTA_START:
        {
            uint16_t now_rr = app_scenario_get_report_rate();
            nvkey_status_t result = nvkey_write_data(NVID_APP_FOTA_RECOED_RR, (uint8_t*)&now_rr, sizeof(now_rr));
            if(result){
                APP_LOGI(thisMOD,"nvkey_write_data NVID_APP_FOTA_RECOED_RR, err = %d", result);
            }
            if(now_rr != APP_FOTA_SET_RR){
                app_fota_status_evt_rr_change_req_announcement(RR_CHANGE_SPECIFIC, APP_FOTA_SET_RR, false);
            }
            app_fota_status__get_fota_state();
            break;
        }
        case RACE_EVENT_TYPE_FOTA_CANCEL:
        {
            app_fota_status_restore_report_rate();
            break;
        }
        default:{
            break;
        }
    }

    return RACE_ERRCODE_SUCCESS;
}

/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
static bool app_fota_status__evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state* event = (struct evt_app_state*)evt_header;
    APP_LOGI(thisMOD,"app_fota_status__evt_app_state, state = 0x%x" , event->app_state);

    switch(event->app_state)
    {
        case APP_STATE_USB_CONNECTED:
        case APP_STATE_2_4G_CONNECTED_ACTIVE:
        case APP_STATE_BT_CONNECTED_ACTIVE:
        {
            bool status = race_fota_is_running(true);
            if(!status)
            {
                app_fota_status_restore_report_rate();
            }
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_fota_status__evt_rr_status(const struct af_evt_header *evt_header)
{
    struct evt_rr_status* event = (struct evt_rr_status*)evt_header;
    APP_LOGI(thisMOD,"app_fota_status__evt_rr_status, rr = %d, flag = %d", event->RR, fota_restore_rr_flag);

    if(fota_restore_rr_flag)
    {
        uint16_t record_rr = 0;
        uint16_t now_rr = event->RR;
        app_nvkey_read_data(NVID_APP_FOTA_RECOED_RR, (uint8_t*)&record_rr, sizeof(record_rr));
        if(record_rr == now_rr) {
            nvkey_delete_data_item(NVID_APP_FOTA_RECOED_RR);
            fota_restore_rr_flag = 0;
        }
        else if(record_rr){
            app_fota_status_restore_report_rate();
        }
    }

    return AF_TRAVERSE_NEXT;
}

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static void app_fota_status_evt_rr_change_req_announcement(T_RR_CHANGE_TYPE_E type, uint16_t rr, uint8_t optional)
{
    APP_LOGI(thisMOD,"app_fota_status_evt_rr_change_req_announcement, type = %d, rr = %d, optional = %d", type, rr, optional);
    struct evt_rr_change_req* event = create_evt_rr_change_req();
    if (event) {
        event->change_type = type;
        event->RR = rr;
        event->restore_or_chg_profile = optional;
        AF_EVT_SUBMIT(event);
    }
}

static uint8_t app_fota_status_restore_report_rate()
{
    uint16_t record_rr = 0;
    bool fota_state = app_fota_status__get_fota_state();
    app_nvkey_read_data(NVID_APP_FOTA_RECOED_RR, (uint8_t*)&record_rr, sizeof(record_rr));
    if(!fota_state && record_rr)
    {
        uint16_t now_rr = app_scenario_get_report_rate();
        APP_LOGI(thisMOD,"app_fota_status_restore_report_rate, rr = (%d:%d), fota_state = %d", record_rr, now_rr, fota_state);
        if((record_rr == now_rr) || app_state_check(TYPE_IN_BT_STATES)) {
            nvkey_delete_data_item(NVID_APP_FOTA_RECOED_RR);
        }
        else
        {
            fota_restore_rr_flag = 1;
            app_fota_status_evt_rr_change_req_announcement(RR_CHANGE_SPECIFIC, record_rr, false);
        }
        return 0;
    }
    return 1;
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
uint8_t app_fota_status_init(void)
{
    #ifdef MTK_RACE_EVENT_ID_ENABLE
    race_event_register(&APP_RACE_ID, app_fota_status__race_event_cb, NULL);
    #else
    race_event_register(app_fota_status__race_event_cb, NULL);
    #endif
    return 0;
}

bool app_fota_status__get_fota_state(void)
{
    bool status = race_fota_is_running(true);
    APP_LOGI(thisMOD, "app_fota_status__get_fota_state, status = %d", status);
    if(status)
    {
        struct evt_active_status* event = create_evt_active_status();
        if(event) {
            event->active = true;
            AF_EVT_SUBMIT(event);
        }
    }
    return status;
}

/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_app_state, app_fota_status__evt_app_state);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_rr_status, app_fota_status__evt_rr_status);
/*=============================================================================*/


