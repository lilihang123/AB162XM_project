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
#if defined(CONFIG_AIR_TEST_GESTURE)
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>

#include "app_fake_report.h"
#include "app_nvkey.h"
#include "app_state.h"
#include "app_button.h"

#define thisMODULE fake_rep
#define thisMOD    "fake_rep"

LOG_MODULE_REGISTER(thisMODULE);
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
static void app_fake_req_trigger_announcement(uint8_t type, uint8_t OnOff, uint8_t pattern, uint8_t rounds);
static void app_fake_rep__handle_fake_report(bool enable, uint32_t pattern, uint32_t rounds);

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
typedef struct
{
    uint8_t enable;
    uint8_t pattern;
    uint8_t rounds;
}T_FAKE_REPORT_PARAM_S;

extern const T_SENSOR_DATA_SMALL_S fake_data_sensor_circle_1000[1000];
extern const T_SENSOR_DATA_SMALL_S fake_data_sensor_square_100[100];

static uint8_t app_fake_report_enable = false;

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/
#if 0
void app_fake_rep_generate_next_report(struct k_work *work);
static void app_fake_rep_start(uint16_t period_in_ms);
static void app_fake_rep_stop();

static K_WORK_DEFINE(genFake, app_fake_rep_generate_next_report);

struct k_timer fake_report_timers;
static uint16_t fake_data_idx = 0;
static uint16_t fake_data_rounds = 5;

void app_fake_rep_generate_next_report(struct k_work *work)
{
    APP_LOGI(thisMOD,"app_fake_rep_generate_next_report Round[%d] idx = %d ", fake_data_rounds, fake_data_idx );

    struct evt_hid_ms_motion* event = create_evt_hid_ms_motion();

    if (event){
        event->motion_X = fake_data_sensor_circle_100[fake_data_idx].sensor_x;
        event->motion_Y = fake_data_sensor_circle_100[fake_data_idx].sensor_y;
        fake_data_idx++;
        AF_EVT_SUBMIT(event);
    }

    if (fake_data_idx >= (sizeof(fake_data_sensor_circle_100) / sizeof(T_SENSOR_DATA_SMALL_S)))
    {
        fake_data_idx = 0;
        APP_LOGI(thisMOD,"fake report completed, stop timer !! \n ");

        if (fake_data_rounds){
            fake_data_rounds--;

            if (fake_data_rounds == 0){
                k_timer_stop(&fake_report_timers);
            }
        }
    }
}
#endif

/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
#if 0
static bool app_fake_rep_evt_hdl_gatt_ch_status(const struct af_evt_header *evt_header)
{
    struct evt_gatt_ch_status* event = (struct evt_gatt_ch_status*)evt_header;
    APP_LOGI(thisMOD,"===>> app_fake_rep_evt_hdl_gatt_ch_status , cccd_ch[%d] = %d \n ", event->cccd_ch_id, event->cccd_ch_status);

    if (event->cccd_ch_id == 1){
        if (event->cccd_ch_status){
            app_fake_rep_start(5000);
        }
        else  {
            app_fake_rep_stop();
        }
    }
    return AF_TRAVERSE_NEXT;
}
#endif

static bool app_fake_evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state* event = (struct evt_app_state*)evt_header;
    APP_LOGI(thisMOD,"app_fake_evt_app_state , event->app_state = %x \n ", event->app_state);

    switch (event->app_state)
    {
        case APP_STATE_USB_ACTIVE:
        case APP_STATE_BT_CONNECTED_ACTIVE:
        case APP_STATE_2_4G_CONNECTED_ACTIVE:
        {
            T_FAKE_REPORT_PARAM_S fake_param;
            if (app_nvkey_read_data(NVID_FAKE_REPORT_STATUS, (uint8_t *)&fake_param, sizeof(fake_param)))
            {
                APP_LOGI(thisMOD, "app_fake_rep_check start fake report");
                // app_fake_req_trigger_announcement(FAKE_DATA_REPORT, fake_param.enable, fake_param.pattern, fake_param.rounds);
                app_fake_req_trigger_announcement(FAKE_DATA_PARAM, fake_param.enable, fake_param.pattern, fake_param.rounds);
            }
        }
        break;

        default:
        break;
    }
    return AF_TRAVERSE_NEXT;
}

static bool app_fake__evt_key_event(const struct af_evt_header *evt_header)
{
    struct evt_key_event* event = (struct evt_key_event*)evt_header;
    APP_LOGI(thisMOD," app_fake__evt_key_event , key_id = %d, event = %x", event->key_id, event->key_evt);

    switch (event->key_evt)
    {
        case AK_PRESS:
        {
            break;
        }

        case AK_TLONG:
        {
            break;
        }

        case AK_4LONG:
        {
            break;
        }

        case AK_5LONG:
        {
            break;
        }

        case AK_4_CLICK:
        {
            break;
        }

        case AK_5_CLICK:
        {
            break;
        }

        case AK_COMBO_HOLD_LV1_1:
        {
            app_fake_rep__handle_fake_report(!app_fake_report_enable, 0, 0);
            break;
        }

        default: {
            break;
        }
    }
    return AF_TRAVERSE_NEXT;
}

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
#if 0
static void app_fake_rep_timeout(struct k_timer *timer)
{
    k_work_submit(&genFake);
}


static void app_fake_rep_start(uint16_t period_in_ms)
{
    #if 1
    APP_LOGI(thisMOD,"app_fake_rep_start , period_in_ms = %u \n ", period_in_ms);

    fake_data_idx = 0;

    k_timer_init(&fake_report_timers , app_fake_rep_timeout, NULL);
    k_timer_start(&fake_report_timers, K_MSEC(period_in_ms) , K_MSEC(period_in_ms));
    #endif
}

static void app_fake_rep_stop()
{
    APP_LOGI(thisMOD,"app_fake_rep_stop");

    k_timer_stop(&fake_report_timers);
}
#endif

static void app_fake_rep__handle_fake_report(bool enable, uint32_t pattern, uint32_t rounds)
{
    nvkey_status_t ret;
    APP_LOGI(thisMOD, "app_fake_rep__handle_fake_report, enable = %d, pattern = %d, rounds = %d, app_fake_report_enable = %d", enable, pattern, rounds, app_fake_report_enable);

    app_fake_report_enable = enable;
    if(enable)
    {
        // app_fake_req_trigger_announcement(FAKE_DATA_REPORT, app_fake_report_enable, pattern, rounds);

        T_FAKE_REPORT_PARAM_S param = {
            .enable = app_fake_report_enable,
            .pattern = pattern,
            .rounds = rounds
        };
        ret = nvkey_write_data(NVID_FAKE_REPORT_STATUS, (const uint8_t *)&param, sizeof(param));
        if (ret) {
            APP_LOGI(thisMOD, "Write NVID_FAKE_REPORT_STATUS nvkey err, ret = %d", ret);
        }

        app_fake_req_trigger_announcement(FAKE_DATA_PARAM, app_fake_report_enable, pattern, rounds);
    }
    else
    {
        ret = nvkey_delete_data_item(NVID_FAKE_REPORT_STATUS);
        if (ret) {
            APP_LOGI(thisMOD, "Delete NVID_FAKE_REPORT_STATUS nvkey err, ret = %d", ret);
        }

        app_fake_req_trigger_announcement(FAKE_DATA_PARAM, app_fake_report_enable, pattern, rounds);
    }
}

static void app_fake_req_trigger_announcement(uint8_t type, uint8_t OnOff, uint8_t pattern, uint8_t rounds)
{
    struct evt_fake_report_execute* event = create_evt_fake_report_execute();
    if (!event) return;

    APP_LOGI(thisMOD, "app_fake_req_trigger_announcement type = %d, enable = %d, pattern = %d, rounds = %d", type, OnOff, pattern, rounds);

    event->type = type;

    if (type == FAKE_DATA_REPORT)
    {
        event->fake_data = NULL;
    }
    else if (type == FAKE_DATA_PARAM)
    {
        event->enable = OnOff;
        event->pattern = pattern;
        event->rounds = rounds;
    }

    AF_EVT_SUBMIT(event);
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
bool app_fake_report_init()
{
    T_FAKE_REPORT_PARAM_S fake_param;
    bool ret = app_nvkey_read_data(NVID_FAKE_REPORT_STATUS, (uint8_t *)&fake_param, sizeof(fake_param));
    if (ret)
    {
        app_fake_report_enable = fake_param.enable;
    }
    else
    {
        app_fake_report_enable = false;
    }

    APP_LOGI(thisMOD, "app_fake_report_init, enable = %d, pattern = %d, rounds = %d", fake_param.enable, fake_param.pattern, fake_param.rounds);
    return ret;
}

/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_app_state, app_fake_evt_app_state);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_key_event, app_fake__evt_key_event);
#endif
/*=============================================================================*/

