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

// #if defined()

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stdint.h"
#include "syslog.h"
#include "riscv_ccni.h"
#include "string.h"
#include "hid_common.h"
#include "riscv_peripheral_sampling.h"
#include "riscv_hid_express.h"
#include "riscv_hid_express_key_queue_game_controller.h"
#include "riscv_game_controller_key.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_platform.h"
#if defined (AIR_FAKE_REPORT)
#include "rv_fake_report.h"
#endif
#if defined(AIR_HID_BT_MODE)
#include "riscv_hid_express_bt_mode.h"
#endif
#if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#include "key_remap_frontend.h"
#endif
/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
#define thisMODULE iCCNI
#define thisMOD    "iCCNI"
log_create_module(riscv_ccni, PRINT_LEVEL_INFO);

/* Private variables ---------------------------------------------------------*/
uint32_t last_app_state = APP_STATE_NONE;
/* Public variables ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
void riscv_app_ccni_send_log_data_ptr();

/* Public functions ----------------------------------------------------------*/
uint8_t risv_app_sleep_lock_status = false;

void rv_sleep_lock_request(uint32_t lock)
{
    //DBG_PING_L(DBG_SIGNAL_DEBUG_1);

    if (lock  && (risv_app_sleep_lock_status == false)) {
        risv_app_sleep_lock_status = lock;
        hal_sleep_manager_status_t ret = hal_sleep_manager_lock_sleep(SLEEP_LOCK_APP);

        LOG_MSGID_I(riscv_ccni, "rv_sleep_lock_request hal_sleep_manager_lock_sleep = %d", 1, ret);
    }
    else if ((lock == false) && risv_app_sleep_lock_status){
        risv_app_sleep_lock_status = lock;
        hal_sleep_manager_status_t ret =  hal_sleep_manager_unlock_sleep(SLEEP_LOCK_APP);
        LOG_MSGID_I(riscv_ccni, "rv_sleep_lock_request hal_sleep_manager_unlock_sleep", 1, ret);
    }
    else {
        LOG_MSGID_I(riscv_ccni, "rv_sleep_lock_request  Ignored request, lock req = %d, risv_app_sleep_lock_status = %d"
            , 2
            , lock
            , risv_app_sleep_lock_status
        );
    }

    //DBG_PING_H(DBG_SIGNAL_DEBUG_1);
}

void CCNI_DEF_HANDLER(3)(hal_ccni_event_t event, hal_ccni_message_t *msg)
{
    uint8_t * raw_msg = (uint8_t *)msg;

    LOG_MSGID_I(riscv_ccni, "riscv_app_ccni_event_handler msg_id = 0x%02X"
        , 1
        , raw_msg[0]
        );

    switch(raw_msg[0])
    {
        case HID_CCNI_MSG_APP_STATE: // app_state
        {
            uint32_t app_state = (msg->data[0] >> 8) & 0x000000FF;
            LOG_MSGID_I(riscv_ccni, "======== app_state = 0x%x", 1, app_state);
            riscv_game_controller_key_change_state(app_state);
            switch(app_state)
            {
                case APP_STATE_STANDBY:
                {
                    rv_sleep_lock_request(false);
                }
                break;

                case APP_STATE_DISCONNECTED:
                {
                    hid_common_clear_hid_exp_flag(FLAG_BIT_FORCE_RELEASE_KEY);
                    #if defined(AIR_HID_BT_MODE)
                    hid_experss_bt_clear_queue();
                    #endif
                    rv_sleep_lock_request(true);
                }
                break;

                case APP_STATE_CONNECT_PREPARING:
                {
                    peripheral_sampling_init();
                    #if defined(AIR_REPORT_DATA_LOG)
                    riscv_app_ccni_send_log_data_ptr();
                    #endif
                }
                break;

                case APP_STATE_BT_PAIRING:
                case APP_STATE_2_4G_PAIRING:
                case APP_STATE_BT_RECONNECT:
                {
                    rv_sleep_lock_request(true);
                }
                break;

                case APP_STATE_2_4G_RECONNECT:
                {
                    rv_sleep_lock_request(true);
                    hid_express_dongle_scenario_update(hid_common_get_dongle_scenario());
                }
                break;

                case APP_STATE_2_4G_QUICK_CONNECT:
                {
                }
                break;

                case APP_STATE_USB_CONNECTED:
                {
                }
                break;

                case APP_STATE_USB_ACTIVE:
                {
                    rv_sleep_lock_request(true);
                    hid_express_clear_key_pushed();
                    peripheral_sampling_state_change_active();
                }
                break;

                case APP_STATE_USB_SUSPEND:
                {
                    rv_sleep_lock_request(true);
                }
                break;

                #if defined(AIR_HID_BT_MODE)
                case APP_STATE_BT_CONNECTED:
                {
                    rv_sleep_lock_request(true);
                }
                break;

                case APP_STATE_BT_CONNECTED_ACTIVE:
                {
                    rv_sleep_lock_request(true);
                    peripheral_sampling_state_change_active();
                }
                break;

                case APP_STATE_BT_CONNECTED_IDLE_1:
                {
                    rv_sleep_lock_request(true);
                }
                break;

                case APP_STATE_BT_CONNECTED_IDLE_2:
                {
                }
                break;
                case APP_STATE_BT_CONNECTED_IDLE_3:
                {
                }
                break;
                #endif

                case APP_STATE_2_4G_CONNECTED:
                {
                    rv_sleep_lock_request(true);
                }
                break;
                case APP_STATE_2_4G_CONNECTED_ACTIVE:
                {
                    rv_sleep_lock_request(true);
                    peripheral_sampling_state_change_active();
                }
                break;
                case APP_STATE_2_4G_CONNECTED_IDLE_1:
                {
                }
                break;

                case APP_STATE_2_4G_CONNECTED_IDLE_2:
                {
                    rv_sleep_lock_request(true);
                }
                break;

                case APP_STATE_2_4G_CONNECTED_IDLE_3:
                {
                }
                break;

                case APP_STATE_BT_CONNECTED_ENTERING_IDLE_1:
                case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1:
                {
                    // peripheral_sampling_idle_state_handler();
                }
                break;

                case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_2:
                case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_3:
                case APP_STATE_BT_CONNECTED_ENTERING_IDLE_2:
                case APP_STATE_BT_CONNECTED_ENTERING_IDLE_3:
                {
                }
                break;


                default:
                break;
            }
            peripheral_sampling_app_state_update(app_state);
            last_app_state = app_state;
        }
        break;

        #if defined (AIR_FAKE_REPORT)
        case HID_CCNI_MSG_FAKE_REPORT_ENABLE: // fake report param
        {
            LOG_MSGID_I(riscv_ccni, "======== fake report request  enable = %d, pattern = %d, rounds = %d \n"
                , 3
                , raw_msg[1]
                , raw_msg[2]
                , raw_msg[3]
                );
            rv_fake_report_config(raw_msg[1], raw_msg[2], raw_msg[3]);

        }
        break;
        #endif

        #if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
        case HID_CCNI_MSG_KEY_REMAP_CONFIG: // Set key remap
        {
            key_remap_frontend_setting_update();
        }
        break;
        #endif

        #if defined (AIR_FAKE_REPORT)
        case  HID_CCNI_MSG_FAKE_REPORT_CONFIG: // fake report data
        {
            uint32_t ptr_val;
            *((uint32_t *)&ptr_val) = *((uint32_t *)&raw_msg[1]) ;
            rv_fake_report_set((uint32_t *)ptr_val);
        }
        break;
        #endif

        #if defined(AIR_HID_BT_MODE)
        case HID_CCNI_MSG_HOGP_ATTR_HANDLE:
        {
            hid_experss_bt_set_attr_handle(raw_msg[1]);
        }
        break;
        #endif

        case HID_CCNI_MSG_COMMON_PARA_UPDATE:
        {
            peripheral_sampling_common_para_update();
        }
        break;

        case HID_CCNI_MSG_WAKEUP_KEY:
        {
            hid_express_set_mode(raw_msg[3]);
            if(raw_msg[2] == AK_RELEASE)
            {
                /* Key relase */
                hid_express__push_to_key_queue(K_TYPE_K, 0);
            }
            else
            {
                /* Key press */
                hid_express__push_to_key_queue(K_TYPE_K, riscv_game_controller_key_id_to_key_status(raw_msg[1]));
            }
        }
        break;

        case HID_CCNI_MSG_USB_PLUG_OUT:  //when in 2.4G or bt
        {
            peripheral_sampling_state_change_active();
        }
        break;

        default:
        break;
    }
}

void riscv_app_ccin_init()
{
    hal_ccni_unmask_event(APP_CCNI_EVENT_TO_RISCV);
}

hal_ccni_status_t riscv_app_ccin_send(uint8_t* payload, uint8_t len)
{
    hal_ccni_message_t msg;

    if ((len > 8) || (payload == NULL)) {
        return HAL_CCNI_STATUS_INVALID_PARAMETER;
    }

    memcpy( (uint8_t*)msg.data , payload , len);

    hal_ccni_status_t status = hal_ccni_set_event(APP_CCNI_EVENT_TO_CM33, &msg);
    return status;
}

void riscv_app_ccin_fake_data_disable()
{
    uint8_t msg[1];
    msg[0] = HID_CCNI_MSG_FAKE_REPORT_TERMINATE;

    riscv_app_ccin_send(msg, sizeof(msg));
}

#if defined(AIR_REPORT_DATA_LOG)
void riscv_app_ccni_send_log_data_ptr()
{
    T_HID_REPORT_LOG_S* log_data_ptr = NULL;
    hid_express_report__get_log_data_ptr(&log_data_ptr);

    T_LOG_REQ_S msg;
    msg.msg = HID_CCNI_MSG_PRINT_HID_REPORT_REQ;
    msg.log_ptr = log_data_ptr;

    //DBG_LATENCY_L(DBG_SIGNAL_DEBUG_1);
    riscv_app_ccin_send((uint8_t*)&msg, sizeof(T_LOG_REQ_S));
    //DBG_LATENCY_H(DBG_SIGNAL_DEBUG_1);
}
#endif

#if defined (AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
void riscv_app_ccni_key_remap_send(uint32_t status, uint32_t attribute)
{
    uint8_t msg[5];
    msg[0] = HID_CCNI_MSG_KEY_REMAP_TRIGGER;
    msg[1] = status;
    msg[2] = attribute & 0xFF; // type
    msg[3] = attribute >> 8 & 0XFF; //  value
    msg[4] = attribute >> 16; //  value

    riscv_app_ccin_send(msg, sizeof(msg));


    // HID_DBG_LOG(rv_key_remap, "riscv_app_ccni_key_remap_send status = %d, attribute = 0x%04X", status, attribute);
}
#endif

// #endif /*  */

