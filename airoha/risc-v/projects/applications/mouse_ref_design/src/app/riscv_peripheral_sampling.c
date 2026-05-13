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
#include "rv_application.h"

#include "riscv_peripheral_sampling.h"

#include "riscv_motion_sensor.h"
#include "riscv_mouse_key.h"
#include "riscv_wheel.h"
#include "pka.h"
#include "hal_gpt.h"
#include "riscv_hid_express_key_queue_mouse.h"
#include "hid_common.h"
#include "swla.h"
#if defined (AIR_FAKE_REPORT)
#include "rv_fake_report.h"
#endif
#if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#include "key_remap_backend.h"
#endif /* AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP  */
#include "riscv_wheel_ir_comparator.h"
#include "riscv_mouse_key_sw_debounce.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
#define SAMPLEING_STATE_ACTIVE      0
#define SAMPLEING_STATE_SWITCHING   1
#define SAMPLEING_STATE_IDLE        2

#define SINGLE_TX 0
#define DOUBLE_TX 1

#define TX_RESULT_NACK_NACK    0
#define TX_RESULT_ACK_NACK     1
#define TX_RESULT_NACK_ACK     2
#define TX_RESULT_ACK_ACK      3

#define TX0_ACKED      0x01
#define TX1_ACKED      0x02

#define GPT_TIME_10_SEC    10000
#define GPT_TIME_1_SEC      1000
#define GPT_TIME_100_MS      100
#define GPT_TIME_500_MS      500
#define GPT_TIME_15_MS        15


#define MY_GPT_TIMER    GPT_TIME_10_SEC

#define MIN_IDLE_CHECK_COUNT 80

/* Private macro -------------------------------------------------------------*/
log_create_module(riscv_ps, PRINT_LEVEL_INFO);

/* Private variables ---------------------------------------------------------*/
static uint32_t inActivity_gpt_hdl = 0;
uint32_t inactivity_counter;
static uint32_t sampling_state = SAMPLEING_STATE_ACTIVE;
uint32_t pairing_state = PAIRING_STATE_SEND_REPORT;
uint32_t inActivity_time = MY_GPT_TIMER;
T_RISCV_APP_S riscv_app;


void peripheral_sampling_last_handler();

/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#if defined (AIR_FAKE_REPORT)
void riscv_fake_report_check()
{
    uint32_t fake_report_state = rv_fake_report__get_state();
    uint32_t btn_pressed = riscv_mouse_keys_is_new_key_pressed();

    if (btn_pressed){
        if (FAKE_REPORT_DISABLED != fake_report_state){
            rv_fake_report_config(false, 0, 0);
            riscv_app_ccin_fake_data_disable();
        }
    }
    else if (FAKE_REPORT_COMPLETED == fake_report_state){
        rv_fake_report_config(false, 0, 0);
        riscv_app_ccin_fake_data_disable();
    }
}
#endif
/* Public functions ----------------------------------------------------------*/
void peripheral_sampling_state_change_active()
{
    sampling_state = SAMPLEING_STATE_ACTIVE;
}

void peripheral_sampling_set_inActivity_timeout()
{
    inActivity_time = hid_common->app.inActivity_timeout;
}

void peripheral_sampling_inactivity_timeout(void* user_data)
{
    uint8_t msg[2] ;
    msg[0] = HID_CCNI_MSG_INACTIVITY_TIMEOUT;
    // LOG_MSGID_I(riscv_ps, "peripheral_sampling_inactivity_timeout", 0 );

    riscv_app_ccin_send((uint8_t*)msg, 2);
    sampling_state = SAMPLEING_STATE_IDLE;
}

void peripheral_sampling_pairing_state_change()
{
    pairing_state = PAIRING_STATE_SEND_REPORT;
}

void peripheral_sampling_all_key_release_ccni_send()
{
    uint8_t msg[2] ;
    msg[0] = HID_CCNI_MSG_FORCE_ALL_KEY_RELEASED;

    riscv_app_ccin_send((uint8_t*)msg, 2);
    pairing_state = PAIRING_STATE_CCNI_SEND;

    // HID_DBG_LOG(riscv_ps, "peripheral_sampling_all_key_release_send_ccni pairing_state = %d", 1, pairing_state);
}

void peripheral_sampling_pairing_check()
{
    //uint32_t last_pairing_state = pairing_state;
    uint32_t flag = hid_express_get_hid_flag();

    switch(pairing_state)
    {
        case PAIRING_STATE_SEND_REPORT:
        {
            pairing_state = PAIRING_STATE_CHECK_BUFFER;
        }
        break;

        case PAIRING_STATE_CHECK_BUFFER:
        {
            if (BT_DATA_GO(flag)) {
                if((pka_share_tx_buf_avail_num() == PKA_TX_BUF_HID_NUM_LE))
                {
                    peripheral_sampling_all_key_release_ccni_send();
                    pairing_state = PAIRING_STATE_CCNI_SEND;
                }
            }
            else if (GAMING_DATA_GO(flag)) {
                if( hid_express_get_get_tx_result() == 0){
                    peripheral_sampling_all_key_release_ccni_send();
                    pairing_state = PAIRING_STATE_CCNI_SEND;
                }
            }
        }
        break;

        case PAIRING_STATE_CCNI_SEND:
        {
            //HID_DBG_LOG(riscv_ps, "Waiting for disconnect event", 0);
        }
        break;
    }

    // if(pairing_state != last_pairing_state){
    //     HID_DBG_LOG(riscv_ps, "peripheral_sampling_pairing_check pairing_state  %d -> %d", 2, last_pairing_state, pairing_state);
    // }
}

void peripheral_sampling_idle_check(uint32_t send_result)
{
    if ( send_result == 0 ){
        if(sampling_state ==  SAMPLEING_STATE_SWITCHING)
        {
            hal_gpt_sw_stop_timer_ms(inActivity_gpt_hdl);
        }
        inactivity_counter = 0;
        sampling_state = SAMPLEING_STATE_ACTIVE;
    }
    else {
        if (inactivity_counter < MIN_IDLE_CHECK_COUNT ){
            inactivity_counter++;
        }
        else if (sampling_state == SAMPLEING_STATE_ACTIVE && inActivity_time){
            #if 1
            sampling_state = SAMPLEING_STATE_SWITCHING;

            //HID_DBG_LOG(riscv_ps, " Start timer and waiting peripheral_sampling_inactivity_timeout MY_GPT_TIMER = %d ", 1, inActivity_time );
            hal_gpt_sw_stop_timer_ms(inActivity_gpt_hdl);
            hal_gpt_sw_start_timer_ms(inActivity_gpt_hdl, inActivity_time, peripheral_sampling_inactivity_timeout, NULL );
            #endif
        }
        else {
        }
    }
}

bool peripheral_sampling__need_early_key_handle_in_wireless_mode()
{
    if (   (riscv_app.state == APP_STATE_CONNECT_PREPARING )                //0x0A
        || (riscv_app.state & APP_STATE_BT_PAIRING )                        //0x1x
        || (riscv_app.state == APP_STATE_2_4G_CONNECTED )                   //0x80
        || (riscv_app.state == APP_STATE_2_4G_CONNECTED_ACTIVE )            //0x81
        || (riscv_app.state == APP_STATE_2_4G_CONNECTED_ENTERING_ACTIVE )   //0x8A
        || (riscv_app.state == APP_STATE_BT_CONNECTED )                     //0x40
        || (riscv_app.state == APP_STATE_BT_CONNECTED_ACTIVE )              //0x41
        || (riscv_app.state == APP_STATE_BT_CONNECTED_ENTERING_ACTIVE )     //0x4A
        )
    {
        return true;
    }

    return false;
}

void peripheral_sampling_handler(T_PS_CB_TYPE_E ps_cb_type, T_OUTGOING_VALUES_S* outgoing_data)
{
    switch(ps_cb_type)
    {
        case HID_EXP_1ST_CB:
        {
            if ((peripheral_sampling__need_early_key_handle_in_wireless_mode() && (riscv_app.rr_idx == HID_REPORT_RATE_8K_HZ))
            || (riscv_app.state == APP_STATE_USB_ACTIVE))
            {
                riscv_mouse_key_early_handle();
            }
        }
        break;

        case HID_EXP_2ND_CB:
        {
            // assert( outgoing_data &&   "Error : outgoing_data is NULL at HID_EXP_2ND_CB");
            if(FORCE_RELEASE_KEY_ENABLE(hid_flags))
            {
                peripheral_sampling_pairing_check();
            }
            else
            {
                riscv_motion_sensor_data_get(&outgoing_data->x, &outgoing_data->y);

                if(peripheral_sampling__need_early_key_handle_in_wireless_mode() && (riscv_app.rr_idx != HID_REPORT_RATE_8K_HZ))
                {
                    riscv_mouse_key_early_handle();
                }

                //DBG_PING_H(DBG_SIGNAL_SPI_CB);
                riscv_wheel_get_data(&outgoing_data->z1);

                riscv_wheel_trigger_read_process();
            }
            //hid_express_prepare_X_Y(&outgoing_data);
        }
        break;

        case HID_EXP_3RD_CB_GET_KEY__TIMING_CRITICAL:
        {
            // assert( outgoing_data &&   "Error : outgoing_data is NULL at HID_EXP_3RD_CB_GET_KEY__TIMING_CRITICAL");
            outgoing_data->type = 1; // mouse report

            if(FORCE_RELEASE_KEY_ENABLE(hid_flags))
            {

            }
            else
            {
                riscv_mouse_key_get_key_status(&outgoing_data->k);
            }
        }
        break;

        case HID_EXP_4TH_CB_POST_PROCESS:
        {
            // assert( outgoing_data &&   "Error : outgoing_data is NULL at HID_EXP_4TH_CB_POST_PROCESS");
            peripheral_sampling_last_handler();
        }
        break;

        case HID_EXP_NO_REPORT_PROCESS:
        {
           // Traffic is stopped.
           // Do pheripheral control if needed
        }
        break;
    }
}

void peripheral_sampling_last_handler()
{
    riscv_wheel_post_process();

    peripheral_sampling_idle_check(hid_express_get_outgpoig_report_result());
    #if defined (AIR_FAKE_REPORT)
    riscv_fake_report_check();
    #endif
    #if defined (AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    uint32_t status = key_remap_get_process_status();
    uint32_t key_status;
    switch (status)
    {
        case SWITCH_RR:
            riscv_app_ccni_key_remap_send(REMAP_TO_RR, 0);
            key_remap_state_reset();
            break;

        case SWITCH_DPI:
            riscv_app_ccni_key_remap_send(REMAP_TO_DPI, key_remap_get_dpi_attr());
            key_remap_state_reset();
            break;

        case SWITCH_DPI_STOP:
            riscv_app_ccni_key_remap_send(REMAP_TO_DPI, DPI_STAGE_LOCK);
            key_remap_state_reset();
            break;

        case WHEEL_PAIRING_KEY:
            riscv_app_ccni_key_remap_send(REMAP_TO_PAIRING, 0);
            key_remap_state_reset();
            break;
    }

    if(key_remap_get_key_status(&key_status))
    {
        riscv_mouse_key__ccni_send_status(key_status);
    }
    #endif

    riscv_mouse_key_post_process();
}

int peripheral_sampling_init()
{
    hid_common_get_hid_exp_features(&riscv_app.hid_exp_features);

    riscv_wheel_init();
    riscv_motion_sensor_init();
    riscv_mouse_key_init();

    peripheral_sampling_common_para_update();

    hid_express_set_features(riscv_app.hid_exp_features);

    peripheral_sampling_set_inActivity_timeout();
    hal_gpt_sw_get_timer(&inActivity_gpt_hdl);

    hid_express_init(peripheral_sampling_handler);

    return 0;
}

void peripheral_sampling_deinit()
{
    // HID_DBG_LOG(riscv_ps, "peripheral_sampling_deinit, stop idle detect time  (inActivity_gpt_hdl)", 0);
    hal_gpt_sw_stop_timer_ms(inActivity_gpt_hdl);
    hal_gpt_sw_free_timer(inActivity_gpt_hdl);
    hid_express_deinit();
}

void peripheral_sampling_app_state_update(uint32_t new_state)
{
    DBG_LATENCY_H(DBG_SIGNAL_LATCH_REPORT);
    HID_DBG_LOG(riscv_ps, "peripheral_sampling_app_state_update, riscv_app.state = 0x%x", 1, riscv_app.state);
    riscv_app.state = new_state;

    switch(riscv_app.state)
    {
        case APP_STATE_CONNECT_PREPARING:
            peripheral_sampling_common_para_update();
        break;

        case APP_STATE_DISCONNECTED:
        {
            peripheral_sampling_pairing_state_change();
            peripheral_sampling_deinit();
        }
        break;

        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_1:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1:
        {

        }
        break;

        case APP_STATE_USB_CONNECTED:
        case APP_STATE_BT_CONNECTED:
        {
            peripheral_sampling_common_para_update();
        }
        break;

        case APP_STATE_2_4G_CONNECTED:
        {
            peripheral_sampling_common_para_update();

        }
        break;

        default:
        break;
    }

    riscv_mouse_key__app_state_update(new_state);
    riscv_wheel__app_state_update(new_state);

    DBG_LATENCY_L(DBG_SIGNAL_LATCH_REPORT);
}

void peripheral_sampling_debug_print()
{
    riscv_mouse_key_debug_print();
    riscv_wheel_debug_print();
}

void peripheral_sampling_common_para_update()
{
    // DBG_LATENCY_H(DBG_SIGNAL_TX_NACK);
    riscv_app.rr_idx_usb = hid_common->app.rr.rr_idx_usb;
    riscv_app.rr_idx_2_4g = hid_common->app.rr.rr_idx_2_4g;
    riscv_app.rr_idx = hid_common->app.rr.rr_idx_2_4g;

    if ( riscv_app.state & 0x20){
        riscv_app.rr_idx = riscv_app.rr_idx_usb;
    }
    else if( riscv_app.state & 0x80){
        riscv_app.rr_idx = riscv_app.rr_idx_2_4g;
    }
    else if( riscv_app.state & 0x40){
        riscv_app.rr_idx = 0;
    }

    HID_DBG_LOG(riscv_ps, "peripheral_sampling_common_para_update, rr_idx = %d, rr_idx_usb = %d, rr_idx_2_4g = %d "
        , 3
        , riscv_app.rr_idx
        , riscv_app.rr_idx_usb
        , riscv_app.rr_idx_2_4g
         );

    hid_express_set_report_rate_idx(riscv_app.rr_idx);
    riscv_mouse_key_common_para_update();
    // DBG_LATENCY_L(DBG_SIGNAL_TX_NACK);
}

bool peripheral_sampling__check_condiction(uint32_t check_type)
{
    switch(check_type)
    {
        case APP_CHECK_8K_CONNECTED:
        {
            if ((riscv_app.rr_idx == HID_REPORT_RATE_8K_HZ) &&  (riscv_app.state  & APP_STATE_CONNECTED) && !(riscv_app.state  & APP_STATE_BT_CONNECTED)){
                return true;
            }
        }
        break;

        case APP_CHECK_CONNECTED_IDLE:
        {
            if ((riscv_app.state  & APP_STATE_CONNECTED)){
                if (IS_APP_STATE_IN_ACTIVE(riscv_app.state) == false){
                    return true;
                }
            }
        }
        break;

        case APP_CHECK_CONNECTED_ACTIVE:
        {
            if ((riscv_app.state  & APP_STATE_CONNECTED)){
                if (IS_APP_STATE_IN_ACTIVE(riscv_app.state)){
                    return true;
                }
            }
        }
        break;

        case APP_CHECK_USB_MODE:
        {
            if ((riscv_app.state  & APP_STATE_USB_CONNECTED)){
                return true;
            }
        }
        break;

        default:
        break;
    }

    return false;
}




// #endif /*  */
