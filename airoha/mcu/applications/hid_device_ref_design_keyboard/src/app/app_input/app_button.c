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

#if CONFIG_AIR_GESTURE_SERVICE

#include <stdint.h>
#include <zephyr/drivers/gpio.h>

#include <hal_gpio.h>
#include <hal_wdt.h>
#include "af_events_declaration.h"
#include "hal_eint.h"



#include "gesture.h"
#include "app_pin_config_parser.h"
#include "app_button.h"
#include "app_state.h"
#include "hid_common.h"
#include "app_nvkey.h"
#include "app_labtest.h"
#include "app_rgb.h"

#define thisMODULE buttons
#define thisMOD    "buttons"

LOG_MODULE_REGISTER(thisMODULE);

//#define AF_DELAYABLE_EVT_TEST
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
static uint32_t app_button_change_profile(uint8_t idx);
// static void app_btn_announce_rr_req(uint8_t type, uint16_t rr);

static void app_btn_key_event_announcement(uint8_t key_id, airoha_key_event_t key_event);

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
static uint8_t key_ids[] =
{
    M_KEY_DPI,
    M_KEY_RR,
};

uint8_t key_num = sizeof(key_ids);



/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/



/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
static bool app_button__evt_app_state(const struct af_evt_header *evt_header)
{
    switch(((struct evt_app_state*)evt_header)->app_state)
    {
        case APP_STATE_BT_CONNECTED_IDLE_1:
        case APP_STATE_2_4G_CONNECTED_IDLE_1:
        {

        }
        break;

        case APP_STATE_BT_CONNECTED_IDLE_2:
        case APP_STATE_2_4G_CONNECTED_IDLE_2:
        {

        }
        break;

        case APP_STATE_USB_ACTIVE:
        case APP_STATE_BT_CONNECTED_ACTIVE:
        case APP_STATE_2_4G_CONNECTED_ACTIVE:

        break;

        case APP_STATE_STANDBY:

        break;

        case APP_STATE_USB_SUSPEND:
        case APP_STATE_DISCONNECTED:

        break;

        case APP_STATE_TEST:
        break;

        case APP_STATE_CONNECT_PREPARING:
        break;

        default:
        break;
    }

    return AF_TRAVERSE_NEXT;
}

void app_button_key_event_hdl(airoha_key_event_t event, uint8_t key_id)
{
    APP_LOGI(thisMOD,"app_key_event key_%d event = 0x%x " , key_id, event);

    app_btn_key_event_announcement(key_id, event);

    switch (event)
    {
        case AK_RELEASE:
        {

        }
        break;

        case AK_PRESS:
        {
            if(app_state_check(TYPE_CONNECTED_WO_ACTIVE) || (app_state_current_state() == APP_STATE_STANDBY))
            {
                struct evt_active_status* evt = create_evt_active_status();
                if (evt){
                    evt->active = true;
                    evt->type = KEY_WAKEUP;
                    AF_EVT_SUBMIT(evt);
                }
            }
        }
        break;

        case AK_COMBO_HOLD_LV1_0:
        {
            struct evt_pairing_request* evt = create_evt_pairing_request();
            if (evt){
                evt->type = PAIRING_REQ_RECOVERABLE;
                evt->force_key_release_req = true;
                AF_EVT_SUBMIT(evt);
            }
        }
        break;

        case AK_COMBO_HOLD_LV1_1:
        {

        }
        break;

        case AK_COMBO_HOLD_LV1_2:
        {
        }
        break;

        case AK_COMBO_HOLD_LV1_3:
        {

        }
        break;

        case AK_DLONG:
        {

        }
        break;

        case AK_TLONG:
        {
            APP_LOGI(thisMOD,"Key[%d] %d clicks and Long press", key_id, event - AK_CLICK_AND_LONG_PRESS_TYPE_MASK);
        }
        break;

        case AK_4LONG:
        {
            APP_LOGI(thisMOD,"Key[%d] %d clicks and Long press", key_id, event - AK_CLICK_AND_LONG_PRESS_TYPE_MASK);
        }
        break;

        case AK_5LONG:
        {
            APP_LOGI(thisMOD,"Key[%d] %d clicks and Long press", key_id, event - AK_CLICK_AND_LONG_PRESS_TYPE_MASK);
        }
        break;

        case AK_6LONG:
        case AK_7LONG:
        case AK_8LONG:
        {
            APP_LOGI(thisMOD,"Key[%d] %d clicks and Long press", key_id, event - AK_CLICK_AND_LONG_PRESS_TYPE_MASK);
        }
        break;

        case AK_9LONG:
        {
            APP_LOGI(thisMOD,"Key[%d] %d clicks and Long press", key_id, event - AK_CLICK_AND_LONG_PRESS_TYPE_MASK);
            struct evt_factory_reset* evt = create_evt_factory_reset();
            if (evt){
                APP_LOGI(thisMOD,"Back door fun: FACTORY_RESET");
                evt->status = true;
                AF_EVT_SUBMIT(evt);
            }
        }
        break;

        case AK_SHORT_CLICK:
        {
            APP_LOGI(thisMOD,"Key[%d] short clicks", key_id);
        }
        break;

        case AK_DOUBLE_CLICK:
        {
            APP_LOGI(thisMOD,"Key[%d] Double clicks", key_id);
        }
        break;

        case AK_TRIPLE_CLICK:
        {
            APP_LOGI(thisMOD,"Key[%d] Tripple clicks", key_id);
        }
        break;

        case AK_4_CLICK:
        {
            APP_LOGI(thisMOD,"Key[%d] %d clicks", key_id, AK_4_CLICK - AK_CLICK_TYPE_MASK);
        }
        break;

        case AK_5_CLICK:
        case AK_6_CLICK:
        case AK_7_CLICK:
        case AK_8_CLICK:
        case AK_9_CLICK:
        {
            APP_LOGI(thisMOD,"Key[%d] %d clicks", key_id, event - AK_CLICK_TYPE_MASK);
        }
        break;

        case AK_LONG_PRESS_LV_1:
        {
            APP_LOGI(thisMOD,"Key[%d] Press and hold level 1 (2s)", key_id);
            switch(key_id)
            {
                case M_KEY_RR:
                {
                    struct evt_app_rgb_test* evt = (struct evt_app_rgb_test*)create_evt_app_rgb_test();
                    if (evt){
                        evt->cmd = TEST_FLASH;
                        AF_EVT_SUBMIT(evt);
                    }
                    break;
                }
                default:{
                    break;
                }
            }
        }
        break;

        case AK_LONG_PRESS_LV_2:
        {
            APP_LOGI(thisMOD,"Key[%d] Press and hold level 2 (2+1s)", key_id);
            switch(key_id)
            {
                case M_KEY_DPI:
                {
                    struct evt_link_change* evt = (struct evt_link_change*)create_evt_link_change();

                    if (evt){
                        evt->type = CHANGE_NEXT_LINK;
                        AF_EVT_SUBMIT(evt);
                    }
                }
            }
        }
        break;
        case AK_LONG_PRESS_LV_3:
        {
            APP_LOGI(thisMOD,"Key[%d] Press and hold level 3 (2+1+2s)", key_id);
        }
        break;

        default:
            break;
    }
}

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static uint8_t app_button_set_debounce(uint8_t debounce)
{
    return 0;
}

static uint8_t app_button_get_debounce()
{
    APP_LOGI(thisMOD,"app_button_get_debounce");
    return 0;
}

static uint32_t app_button_change_profile(uint8_t idx)
{
    APP_LOGI(thisMOD,"app_button_change_profile idx = %d", idx);
    return 0;
}

static uint32_t app_button_debounce_time_reload(uint8_t profile, bool restore)
{
    APP_LOGI(thisMOD,"app_button_debounce_time_reload");
    return 0;
}

static void app_btn_key_event_announcement(uint8_t key_id, airoha_key_event_t key_event)
{
    struct evt_key_event* event = create_evt_key_event();
    if (event){
        APP_LOGI(thisMOD,"app_btn_key_event_announcement");
        event->key_id = key_id;
        event->key_evt = key_event;
        AF_EVT_SUBMIT(event);
    }
}

static void app_btn_race_cmd_rsp_announcement(T_RACE_CMD_E cmd, uint8_t result)
{
    APP_LOGI(thisMOD,"app_btn_race_cmd_rsp_announcement , result = %d", result);
    struct evt_race_cmd_rsp* event = create_evt_race_cmd_rsp();
    if (event){
        event->cmd = cmd;
        event->DEBOUNCE.result = result;
        event->OTHERS.status = result;
        AF_EVT_SUBMIT(event);
    }
}

static bool app_button_evt_race_cmd_req(const struct af_evt_header *evt_header)
{
    struct evt_race_cmd_req* event = (struct evt_race_cmd_req*)evt_header;
    APP_LOGI(thisMOD,"evt_race_cmd_req , cmd = %x", event->cmd);
    uint8_t res;

    switch(event->cmd)
    {
        case RACE_CMD_SET_DEBOUNCE:
        {
            res = app_button_set_debounce(event->DEBOUNCE.time);
            app_btn_race_cmd_rsp_announcement(RACE_CMD_SET_DEBOUNCE, res);
        }
        break;

        case RACE_CMD_GET_DEBOUNCE:
        {
            res = app_button_get_debounce();
            app_btn_race_cmd_rsp_announcement(RACE_CMD_GET_DEBOUNCE, res);
        }
        break;

        case RACE_CMD_SET_PROFILE:
        {
            res = app_button_change_profile(event->PROFILE.id);
            app_btn_race_cmd_rsp_announcement(RACE_CMD_SET_PROFILE, res);
        }
        break;

        case RACE_CMD_SET_RESTORE:
        {
            res = app_button_debounce_time_reload(0, true);
            app_btn_race_cmd_rsp_announcement(RACE_CMD_SET_RESTORE, res);
        }
        break;

        default:
        break;
    }
    return AF_TRAVERSE_NEXT;
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
uint8_t app_button_ms_key_polling(uint8_t * ms_key)
{
    return 0; //success
}

void app_button_init(uint8_t profile_idx, T_MOUSE_KEY_S *config_key_list)
{
    T_AIROHA_KEY_CONFIGURATION_S airo_key_cfg;


    APP_LOGI(thisMOD,"app_button_init: config_key_list = 0x%X, key_num =%d  "
        , config_key_list
        , key_num
        );

    airo_key_cfg.key_handle_cb = app_button_key_event_hdl;
    airo_key_cfg.key_list = key_ids;
    airo_key_cfg.key_list_size = key_num;
    airo_key_cfg.hold_timeout_ms = 2000;
    airo_key_cfg.hold_timeout_LP2_ms = 1000;  //The hold time between LP1 and LP2
    airo_key_cfg.hold_timeout_LP3_ms = 2000;  //The hold time between LP2 and LP3
    airo_key_cfg.click_timeout_ms = 400;
    airo_key_cfg.combo_key_list = NULL;
    airo_key_cfg.combo_key_list_size = 0;
    airo_key_cfg.debounce_time_list = NULL;

    airo_key_status_t ret = airo_key_init(&airo_key_cfg);
    if(ret){
        assert(0 && "airo_key_init fail !");
    }

    APP_LOGI(thisMOD,"app_button_init: ret = %d ", ret );
}

uint32_t app_button_is_key_pressed()
{
    uint32_t key_status = 1;
    // airo_key_read_all_key_status();
    APP_LOGI(thisMOD,"app_button_is_key_pressed, key_status = 0x%08X", key_status);
    return ~key_status;
}

/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_app_state, app_button__evt_app_state);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_race_cmd_req, app_button_evt_race_cmd_req);

/*=============================================================================*/


#endif /* CONFIG_AIR_GESTURE_SERVICE */