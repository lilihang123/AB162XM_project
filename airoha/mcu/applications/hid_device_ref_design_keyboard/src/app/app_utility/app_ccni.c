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

#include "app_ccni.h"
#include "app_state.h"
#include <stdint.h>
#include "app_button.h"

#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#include "key_remap_queue.h"
#include "key_remap_backend.h"
#endif

#define MAX_CCNI_STATUS_RETRY_CNT 1000

#define thisMOD    "accni"
#define thisMODULE accni
LOG_MODULE_REGISTER(thisMODULE);
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
void app_ccni_send_event_to_RISC_V(uint8_t *ptr, uint8_t len );
static void app_ccni_send_key_event_to_RISC_V();
void app_ccni_send_key_remap_setting();
/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
typedef struct{
    uint8_t key_id;
    uint8_t key_evt;
    uint8_t ready_to_send;
}T_WAKEUP_KEY_EVENT_S;

T_WAKEUP_KEY_EVENT_S wakeup_key;

#if defined (CONFIG_AIR_PRINT_HID_REPORT_LOG)
uint32_t report_log_counter = 0;
T_HID_REPORT_LOG_S* report_log_ptr = NULL;

#define RISCV_REPORT_LOG_CHECK_INTERVAL  1  // ms
void app_ccni_HID_report_log_print();
void app_ccni__riscv_report_log_print_handler(struct k_timer *dummy);

K_TIMER_DEFINE(riscv_report_log_timer, app_ccni__riscv_report_log_print_handler, NULL);
#endif

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/
#if defined (CONFIG_AIR_PRINT_HID_REPORT_LOG)
void app_ccni__riscv_report_log_print_handler(struct k_timer *dummy)
{
    app_ccni_HID_report_log_print();
    k_timer_start(&riscv_report_log_timer, K_MSEC(RISCV_REPORT_LOG_CHECK_INTERVAL), K_NO_WAIT);
}
#endif

/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
static void app_ccni__evt_app_state_handler(const struct af_evt_header *evt_header)
{

    switch(((struct evt_app_state*)evt_header)->app_state)
    {
        case APP_STATE_BT_PAIRING:
        case APP_STATE_2_4G_PAIRING:
        case APP_STATE_2_4G_QUICK_CONNECT:
            break;

        case APP_STATE_BT_RECONNECT:
        case APP_STATE_2_4G_RECONNECT:
        {
            app_ccni_send_key_event_to_RISC_V();
        }
            break;

        case APP_STATE_BT_CONNECTED:
        case APP_STATE_2_4G_CONNECTED:
        {
            #if defined (CONFIG_AIR_PRINT_HID_REPORT_LOG)
            APP_LOGI(thisMOD,"report_log_ptr = 0x%x \n ",report_log_ptr);
            if (report_log_ptr){
                k_timer_stop(&riscv_report_log_timer);
                k_timer_start(&riscv_report_log_timer, K_MSEC(RISCV_REPORT_LOG_CHECK_INTERVAL), K_NO_WAIT);
            }
            #endif
        }
        break;

        case APP_STATE_DISCONNECTED:
        {
            #if defined (CONFIG_AIR_PRINT_HID_REPORT_LOG)
            k_timer_stop(&riscv_report_log_timer);
            #endif
        }
        break;

        default:
            break;
    }
}

#if CONFIG_AIR_GESTURE_SERVICE
static bool app_ccni__evt_key_event(const struct af_evt_header *evt_header)
{
    struct evt_key_event* event = (struct evt_key_event*)evt_header;
    uint32_t app_state = app_state_current_state();
    if(((event->key_evt == AK_PRESS) || (event->key_evt == AK_RELEASE))
        // && (event->key_id != M_KEY_DPI && event->key_id != M_KEY_RR))
    )
    {
        wakeup_key.key_id = event->key_id;
        wakeup_key.key_evt = event->key_evt;
        wakeup_key.ready_to_send = true;

        if(app_state == APP_STATE_BT_RECONNECT || app_state == APP_STATE_2_4G_RECONNECT
           || app_state_check(TYPE_IN_BT_CONNECTED_STATES) || app_state_check(TYPE_IN_GAMING_CONNECTED_STATES))
        {
            // app_ccni_send_key_event_to_RISC_V();
        }

    }

    return AF_TRAVERSE_NEXT;
}
#endif /* CONFIG_AIR_GESTURE_SERVICE */

static bool app_ccni__evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state* event = (struct evt_app_state*)evt_header;

    uint8_t msg[2];
    msg[0] = HID_CCNI_MSG_APP_STATE;
    msg[1] = event->app_state;

    app_ccni_send_event_to_RISC_V(msg, sizeof(msg));
    app_ccni__evt_app_state_handler(evt_header);

    return AF_TRAVERSE_NEXT;
}

#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
static bool app_ccni__evt_set_key_remap(const struct af_evt_header *evt_header)
{
    struct evt_race_cmd_rsp* event = (struct evt_race_cmd_rsp*)evt_header;

    if (event->cmd == RACE_CMD_SET_KEY_REMAP || event->cmd == RACE_CMD_DELETE_MACRO ||
        event->cmd == RACE_CMD_SET_RESTORE ||  event->cmd == RACE_CMD_SET_PROFILE
        #if defined(CONFIG_AIR_REMAP_FN_KEY)
            || event->cmd == RACE_CMD_SET_REMAP_FN_KEY
        #endif
        )
    {
        app_ccni_send_key_remap_setting();
    }

    return AF_TRAVERSE_NEXT;
}
#endif

#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
static bool app_ccni__evt_usb_status(const struct af_evt_header *evt_header)
{
    struct evt_usb_status* event = (struct evt_usb_status*)evt_header;
    APP_LOGI(thisMOD,"app_ccni__evt_usb_status, status = %d", event->status);
    switch(event->status)
    {
        case USB_STATUS_PLUGGED_OUT:  //0
        {
            uint8_t state = app_state_current_state();
            if(state == APP_STATE_BT_CONNECTED_ACTIVE || state == APP_STATE_2_4G_CONNECTED_ACTIVE)
            {
                APP_LOGI(thisMOD,"usb plugged out now, wait for enter idle1!");

                uint8_t msg[2];
                msg[0] = HID_CCNI_MSG_USB_PLUG_OUT;
                app_ccni_send_event_to_RISC_V(msg, sizeof(msg));
            }
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}
#endif

#if defined (CONFIG_AIR_PRINT_HID_REPORT_LOG)
void app_ccni_HID_report_log_print()
{
    if (report_log_ptr->pool_print_idx != report_log_ptr->pool_idx)
    {
        uint8_t*  log_buf =  (uint8_t*)report_log_ptr->pool[report_log_ptr->pool_print_idx].ack;

        APP_LOGI(thisMOD, "Report log[v6.00][%05u] [0~1]   =  %08X:%08X%08X, %08X:%08X%08X"
            , report_log_counter
            , *(uint32_t*)&log_buf[	8 + (REPORT_SIZE * 0)]
            , *(uint32_t*)&log_buf[	4 + (REPORT_SIZE * 0)]
            , *(uint32_t*)&log_buf[	0 + (REPORT_SIZE * 0)]

            , *(uint32_t*)&log_buf[	8 + (REPORT_SIZE * 1)]
            , *(uint32_t*)&log_buf[	4 + (REPORT_SIZE * 1)]
            , *(uint32_t*)&log_buf[	0 + (REPORT_SIZE * 1)]
            );
        report_log_counter += 2;

        APP_LOGI(thisMOD, "Report log[v6.00][%05u] [2~3]   =  %08X:%08X%08X, %08X:%08X%08X"
            , report_log_counter
            , *(uint32_t*)&log_buf[	8 + (REPORT_SIZE * 2)]
            , *(uint32_t*)&log_buf[	4 + (REPORT_SIZE * 2)]
            , *(uint32_t*)&log_buf[	0 + (REPORT_SIZE * 2)]

            , *(uint32_t*)&log_buf[	8 + (REPORT_SIZE * 3)]
            , *(uint32_t*)&log_buf[	4 + (REPORT_SIZE * 3)]
            , *(uint32_t*)&log_buf[	0 + (REPORT_SIZE * 3)]
            );
        report_log_counter += 2;

        APP_LOGI(thisMOD, "Report log[v6.00][%05u] [4~5]   =  %08X:%08X%08X, %08X:%08X%08X"
            , report_log_counter
            , *(uint32_t*)&log_buf[	8 + (REPORT_SIZE * 4)]
            , *(uint32_t*)&log_buf[	4 + (REPORT_SIZE * 4)]
            , *(uint32_t*)&log_buf[	0 + (REPORT_SIZE * 4)]

            , *(uint32_t*)&log_buf[	8 + (REPORT_SIZE * 5)]
            , *(uint32_t*)&log_buf[	4 + (REPORT_SIZE * 5)]
            , *(uint32_t*)&log_buf[	0 + (REPORT_SIZE * 5)]
            );
        report_log_counter += 2;

        APP_LOGI(thisMOD, "Report log[v6.00][%05u] [6~7]   =  %08X:%08X%08X, %08X:%08X%08X"
            , report_log_counter
            , *(uint32_t*)&log_buf[	8 + (REPORT_SIZE * 6)]
            , *(uint32_t*)&log_buf[	4 + (REPORT_SIZE * 6)]
            , *(uint32_t*)&log_buf[	0 + (REPORT_SIZE * 6)]

            , *(uint32_t*)&log_buf[	8 + (REPORT_SIZE * 7)]
            , *(uint32_t*)&log_buf[	4 + (REPORT_SIZE * 7)]
            , *(uint32_t*)&log_buf[	0 + (REPORT_SIZE * 7)]
            );
        report_log_counter += 2;

        report_log_ptr->pool_print_idx = report_log_ptr->pool_idx;
    }
}
#endif



static bool app_ccni__evt_rr_status(const struct af_evt_header *evt_header)
{
    uint8_t msg[1];
    msg[0] = HID_CCNI_MSG_COMMON_PARA_UPDATE;

    app_ccni_send_event_to_RISC_V(msg, sizeof(msg));
    return AF_TRAVERSE_NEXT;
}

static bool app_ccni__evt_sw_deb_update(const struct af_evt_header *evt_header)
{
    uint8_t msg[1];
    msg[0] = HID_CCNI_MSG_COMMON_PARA_UPDATE;

    app_ccni_send_event_to_RISC_V(msg, sizeof(msg));
    return AF_TRAVERSE_NEXT;
}

static bool app_ccni__evt_hogp_attr(const struct af_evt_header *evt_header)
{
    struct evt_hogp_attr* event = (struct evt_hogp_attr*)evt_header;

    uint8_t msg[5];
    msg[0] = HID_CCNI_MSG_HOGP_ATTR_HANDLE;
    msg[1] = event->ms;
    msg[2] = event->kb_std;
    msg[3] = event->kb_consumer;
    msg[4] = event->kb_nkey;

    app_ccni_send_event_to_RISC_V(msg, sizeof(msg));
    return AF_TRAVERSE_NEXT;
}

void CCNI_DEF_HANDLER(3)(hal_ccni_event_t event, hal_ccni_message_t *msg)
{
    T_APP_CCNI_MSG_S* app_ms  =  (T_APP_CCNI_MSG_S*)msg;

    APP_LOGI(thisMOD,"CCNI_DEF_HANDLER(3) event = 0x%X, app_ms->id = %d, value = 0x%02X-%02X-%02X "
        , event
        , app_ms->id
        , app_ms->value[0]
        , app_ms->value[1]
        , app_ms->value[2]
        );

    switch(app_ms->id)
    {
        case HID_CCNI_MSG_INACTIVITY_TIMEOUT:
        {
            struct evt_active_status* evt = create_evt_active_status();
            if (evt){
                evt->active = false;
                AF_EVT_SUBMIT(evt);
            }
        }
        break;

        case HID_CCNI_MSG_FORCE_ALL_KEY_RELEASED:
        {
            struct evt_force_key_release_success* evt = create_evt_force_key_release_success();
            if (evt){
                AF_EVT_SUBMIT(evt);
            }
        }
        break;

        case HID_CCNI_MSG_FAKE_REPORT_TERMINATE:
        {
            APP_LOGI(thisMOD,"HID_CCNI_MSG_FAKE_REPORT_TERMINATE");
#if CONFIG_AIR_GESTURE_SERVICE
            struct evt_key_event* evt = create_evt_key_event();
            if (evt)
            {
                evt->key_id = 0;
                evt->key_evt = AK_PRESS;
                AF_EVT_SUBMIT(evt);
            }
#endif /* CONFIG_AIR_GESTURE_SERVICE */
        }
        break;

        case HID_CCNI_MSG_PRINT_HID_REPORT_REQ:
        {
            #if defined (CONFIG_AIR_PRINT_HID_REPORT_LOG)
            T_LOG_REQ_S * ptr = (T_LOG_REQ_S *)msg;
            report_log_ptr = ptr->log_ptr;

            APP_LOGI(thisMOD,"HID_CCNI_MSG_PRINT_HID_REPORT_REQ report_log_ptr = 0x%x \n ",report_log_ptr);
            #endif
        }
        break;

        case HID_CCNI_MSG_POLLING_KEY_STATUS:
        {
            #if defined (CONFIG_AIR_SUPPORT_IRPT_LR_KEY)
            uint32_t mouse_5key =  *(uint32_t*)app_ms->value;
            struct evt_riscv_key* evt = create_evt_riscv_key();
            if (evt){
                evt->key_status = mouse_5key;
                AF_EVT_SUBMIT(evt);
            }
            #endif
        }
        break;

        case HID_CCNI_MSG_POLLING_WHEEL_STATUS:
        {
            #if defined (CONFIG_AIR_SUPPORT_IR_COMP)
            uint32_t wheel_status =  *(uint32_t*)app_ms->value;
            struct evt_riscv_wheel_status* evt = create_evt_riscv_wheel_status();
            if (evt){
                evt->wheel_status = wheel_status;
                AF_EVT_SUBMIT(evt);
            }
            #endif
        }
        break;

        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
        case HID_CCNI_MSG_KEY_REMAP_QUEUE:
        {
            T_REMAP_QUEUE_PTR_S * queue_ptr = (T_REMAP_QUEUE_PTR_S *)msg;
            key_remap_set_queue(queue_ptr->ptr);
        }
        break;
        #endif
    }
}

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static void app_ccni_send_key_event_to_RISC_V()
{
    if(wakeup_key.ready_to_send)
    {
        uint8_t msg[3];
        msg[0] = HID_CCNI_MSG_WAKEUP_KEY;
        msg[1] = wakeup_key.key_id;
        msg[2] = wakeup_key.key_evt;
        app_ccni_send_event_to_RISC_V(msg, sizeof(msg));
        wakeup_key.ready_to_send = false;
    }
}

void app_ccni_send_event_to_RISC_V(uint8_t *ptr, uint8_t len)
{
    T_APP_CCNI_MSG_S* app_msg  =  (T_APP_CCNI_MSG_S*)ptr;

    if (ptr==NULL || len > 8)
        return;

    hal_ccni_message_t ccni_msg;
    hal_ccni_status_t status;

    memcpy((uint8_t*)ccni_msg.data,  ptr, len );

    status = hal_ccni_set_event(APP_CCNI_EVENT_TO_RISCV, &ccni_msg);

    if(status == HAL_CCNI_STATUS_BUSY)
    {
        uint16_t retry_cnt = 0;
        uint32_t data = HAL_CCNI_EVENT_STATUS_BUSY;
        while((data == HAL_CCNI_EVENT_STATUS_BUSY) && (retry_cnt < MAX_CCNI_STATUS_RETRY_CNT)){
            retry_cnt++;
            hal_ccni_query_event_status(APP_CCNI_EVENT_TO_RISCV, &data);
        }
        assert( (retry_cnt < MAX_CCNI_STATUS_RETRY_CNT) && "Error : RISC-V busy for too long");
        APP_LOGI(thisMOD,"app_ccni_send_event_to_RISC_V busy retry count = %d", retry_cnt);

        status = hal_ccni_set_event(APP_CCNI_EVENT_TO_RISCV, &ccni_msg);
    }

    APP_LOGI(thisMOD,"app_ccni_send_event_to_RISC_V app_msg->id = %d, len = %d, value = 0x%02X-%02X, status = %d"
        , app_msg->id
        , len
        , app_msg->value[0]
        , app_msg->value[1]
        , status
        );
}
/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
void app_ccni_send_key_remap_setting()
{
    uint8_t msg[2];
    msg[0] = HID_CCNI_MSG_KEY_REMAP_CONFIG;

    app_ccni_send_event_to_RISC_V(msg, sizeof(msg));
}


/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_app_state, app_ccni__evt_app_state);
#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_race_cmd_rsp, app_ccni__evt_set_key_remap);
#endif
AF_EVT_SUBSCRIBE_FUN_LAST(thisMODULE, evt_rr_status, app_ccni__evt_rr_status);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_sw_deb_update, app_ccni__evt_sw_deb_update);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_hogp_attr, app_ccni__evt_hogp_attr);

#if CONFIG_AIR_GESTURE_SERVICE
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_key_event, app_ccni__evt_key_event);
#endif

#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_usb_status, app_ccni__evt_usb_status);
#endif /* _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_ */
/*=============================================================================*/

