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


/* Includes ------------------------------------------------------------------*/
#include "riscv_hid_express.h"
#if defined (AIR_HID_BT_MODE) || defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
#include "riscv_hid_express_bt_mode.h"
#endif
#include "riscv_hid_express_2_4G_mode.h"
#include "riscv_hid_express_usb_mode.h"
#include "riscv_hid_express_xy_queue.h"
#if defined (AIR_PRODUCT_TYPE_KEYBOARD)
#include "riscv_hid_express_key_queue_keyboard.h"
#elif defined (AIR_PRODUCT_TYPE_MOUSE)
#include "riscv_hid_express_key_queue_mouse.h"
#if defined(AIR_KEY_REMAP_BACKEND_RISCV)
#include "key_remap_backend.h"
#endif
#endif
#if defined(AIR_KEY_REMAP_FRONTEND_RISCV)
#include "key_remap_frontend.h"
#endif

#include "mouse_sensor.h"
#include "pka.h"
#include "pka_share.h"
#if defined (AIR_FAKE_REPORT)
#include "rv_fake_report.h"
#endif
#include "hal_gpt_internal.h"
#include "hid_common.h"
#include "hal_eint_internal.h"
#include "swla.h"
#include <stdint.h>
#include "hal_gpio.h"
#include "rv_hid_exp_delay_printf.h"
#include "hal_spi_master.h"
#include "rv_latency.h"

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER) || defined(AIR_HW_KEYSCAN)
#include "hal_hw_keyscan.h"
#endif /* defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER) */

/* Private define ------------------------------------------------------------*/
#define MOTION_PIN_GPIO 18
#define BT_TX_PKT_NUM_MAX 10
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
#define JOYSTICK_0_LEVEL_VALUE 0x8000
#endif

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
log_create_module(rv_exp, PRINT_LEVEL_INFO);



/* Private variables ---------------------------------------------------------*/

T_KEY_QUEUE_CTRL_S kCtrl_k;

#if defined(AIR_REPORT_DATA_LOG)
T_HID_REPORT_LOG_S report_log;
#endif

/* Public variables ----------------------------------------------------------*/
uint32_t hid_flags;
uint32_t rv_fun_flags;
uint32_t last_tx_result;
uint32_t previous_tx_result;
uint32_t tx_buff_num;
uint32_t last_tx_buff_num;
uint32_t this_tx_idx;
uint32_t dongle_scenario;
uint32_t previous_key_status = 0;
uint32_t rr_idx_2_4g = HID_REPORT_RATE_TOTAL_NUM;

uint32_t hid_exp_feature_option = 0;

static riscv_ps_callback_t peripheral_sampling_cb_ptr = NULL;


uint32_t report_go = false;
uint32_t last_report_go = false;
uint32_t report_go_previous = false;

uint32_t curr_tx_count;
uint32_t report_repeat_cnt;
T_OUTGOING_VALUES_S outgoing_data;
uint32_t report_send_result;
uint8_t report_rate_pka;
T_hid_ctrl_S hid_ctrl; // HID control structure

void hid_express_dbg_check();

uint32_t timestamp_spi_cb_start;
uint32_t timestamp_spi_cb_start_previous;
uint32_t pka_active_state_always = 0;
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
uint32_t timestamp_spi_cb_end;
uint32_t timestamp_spi_cb_end_previous;
uint32_t lt_digital = 0;
uint32_t rt_digital = 0;
uint8_t *pka_tx_ptr = NULL;
uint8_t scenario_mode;/* BT/2.4G/USB */
#endif

extern uint8_t* reliable_tx_ptr;
extern uint8_t* reliable_tx_ptr_previous;

#if defined(AIR_REPORT_DATA_LOG)
void hid_express_report_log__attach_dbg_timestamp(uint32_t timestamp_of_submitted);
uint32_t report_log_counter = 0;
#endif

bool g_riscv_ccni_irq_occur = false;

KEY_QUEUE_STATUS key_queue_push_result = STATUS_UNKNOWN;

/* Private functions ---------------------------------------------------------*/
#if defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
void CCNI_DEF_HANDLER(3)(hal_ccni_event_t event, hal_ccni_message_t *msg)
{
    T_APP_CCNI_MSG_S* ccni_msg  =  (T_APP_CCNI_MSG_S*)msg;

    switch(ccni_msg->msg_id)
    {
        case HID_CCNI_MSG_ADC_SCAN_START:
        {
            // HID_DBG_LOG(rv_exp,"HID_CCNI_MSG_ADC_SCAN_START", 0);
            hid_express_entrance();
        }
        break;

        default:
        break;
    }
}
#endif

uint32_t hid_express_get_hid_flag()
{
    return hid_flags;
}

T_OUTGOING_VALUES_S *hid_express_get_outgoing_data()
{
    return &outgoing_data;
}

uint32_t hid_express_get_get_tx_result()
{
    return last_tx_result;
}

uint32_t hid_express_get_previous_tx_result()
{
    return previous_tx_result;
}

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
void hid_express_entrance()
{
    DBG_PING_H(DBG_SIGNAL_SPI_CB); //start : 0 us
    // take a timestamp at the begging
    timestamp_spi_cb_start_previous = timestamp_spi_cb_start;
    GPT_GET_FREE_RUN_COUNT_US(timestamp_spi_cb_start);
    RV_LATENCY__CHECK_POINT_FIRST(timestamp_spi_cb_start);

    pka_share_callback_type_t type;
    uint32_t tx_cnt = 0;
    hid_flags = hid_common->hid.flags;
    rr_idx_2_4g = hid_common->app.rr.rr_idx_2_4g;
    report_rate_pka = pka_share_get_current_report_rate();
    /* peripheral sampling first callback for pre-processing, for example IR ON... */
    if (peripheral_sampling_cb_ptr){
        peripheral_sampling_cb_ptr(HID_EXP_1ST_CB, NULL);
    }

    DBG_PING_L(DBG_SIGNAL_SPI_CB);

    /* pka pre-process: get last tx status */
    if(USB_DATA_GO(hid_flags) == 0){
        pka_spi_callback_pre_process( &type, &tx_cnt);
    }
    this_tx_idx = tx_cnt;
    last_tx_result = 0; /// Ack Ack
    DBG_PING_H(DBG_SIGNAL_SPI_CB);
    /* get last tx status and current tx ptr */
    if (USB_DATA_GO(hid_flags)){
        /* In USB Mode, last_tx_result means the last packet if is sent sucessfully, 0 - success, 1 - fail */
        last_tx_result = USB_TX_NACK(hid_flags)?  1 : 0;
        rv_hid_exp_key_queue_pre_process(&kCtrl_k , last_tx_result, MODE_USB);
    }
    #if defined (AIR_HID_BT_MODE)
    else if (BT_DATA_GO(hid_flags)){
        last_tx_result = hid_express_bt_get_tx_result();
        rv_hid_exp_key_queue_pre_process(&kCtrl_k , last_tx_result, MODE_BT);
    }
    #endif
    else if (GAMING_DATA_GO(hid_flags)){
        rv_hid_exp_key_queue_pre_process(&kCtrl_k , previous_tx_result, MODE_2_4G);
        /* In 2.4G Mode, last_tx_result means the current packet if is able to be sent, 0 - can be sent in this time, 1 - can not be sent in this time */
        last_tx_result = hid_express_gaming_get_tx_status();
        /* Ahead pka_share tx data lenth set for key latency*/
        pka_tx_ptr = (reliable_tx_ptr != NULL) ? (reliable_tx_ptr) : (reliable_tx_ptr_previous);
        if (report_rate_pka == HID_REPORT_RATE_8K_HZ) {
            *((uint16_t *)(pka_tx_ptr + pka_share_get_tx_datalen_offset())) = 9;
            *((uint16_t *)(pka_tx_ptr + pka_share_get_tx_pdulen_offset())) = 9;
        } else {
            *((uint16_t *)(pka_tx_ptr + pka_share_get_tx_datalen_offset())) = 17;
            *((uint16_t *)(pka_tx_ptr + pka_share_get_tx_pdulen_offset())) = 17;
        }

        /* Ahead  pka_active_state_always get for key latency*/
        pka_active_state_always = (pka_active_state_match(PKA_SHARE_ACTIVE_STATE_NORMAL) == false);  //STATE_ALWAYS

    }

    /* get lt/rt sw mode ahead */
    lt_digital = lt_is_digital();
    rt_digital = rt_is_digital();

    if (last_tx_result){
        dbg.nack_count++;
    }
    if(reliable_tx_ptr != NULL)
    {
        reliable_tx_ptr_previous = reliable_tx_ptr;
    }
    DBG_PING_L(DBG_SIGNAL_SPI_CB);

    if(USB_DATA_GO(hid_flags)){
        hid_express_usb_delay_for_latency();
        // hid_express_usb_wakeup_cm33_handler();
    }
    /* peripheral sampling second callback for non-key peripherals sampling, for example mouse sensor, game controller joysitck and trigger ... */
    dbg.sampling_cnt++;
    peripheral_sampling_cb_ptr(HID_EXP_2ND_CB, &outgoing_data);
    if(outgoing_data.x != JOYSTICK_0_LEVEL_VALUE || outgoing_data.y != JOYSTICK_0_LEVEL_VALUE ||
       outgoing_data.z != JOYSTICK_0_LEVEL_VALUE || outgoing_data.rz != JOYSTICK_0_LEVEL_VALUE) {
        dbg.sensor_ok++;
    }
    DBG_PING_H(DBG_SIGNAL_SPI_CB);
    
    RV_LATENCY__CHECK_POINT_SECOND();
    /* peripheral sampling third callback for key because of the best key latency */
    peripheral_sampling_cb_ptr(HID_EXP_3RD_CB_GET_KEY__TIMING_CRITICAL, &outgoing_data);
    if (previous_key_status ^ outgoing_data.k.word){
        previous_key_status = outgoing_data.k.word;
        dbg.valid_key_cnt++;
    }

    DBG_PING_H(DBG_SIGNAL_SPI_CB);

    /* send packet to controller */
    last_report_go = report_go;
    report_send_result = hid_express_send(&outgoing_data, timestamp_spi_cb_start);

    DBG_PING_L(DBG_SIGNAL_SPI_CB);

    /* pka post-process */
    if(USB_DATA_GO(hid_flags) == 0){
        #if defined(AIR_LATENCY_REPORT)
        uint32_t timestamp_report_submitted = pka_spi_callback_post_process();
        RV_LATENCY__CHECK_POINT_THIRD(timestamp_report_submitted, report_go);
        #else 
        pka_spi_callback_post_process();
        #endif
    }

    /* peripheral sampling fouth callback for post-process, for example record debug info */
    peripheral_sampling_cb_ptr(HID_EXP_4TH_CB_POST_PROCESS, &outgoing_data);
    hid_express_dbg_check();

    // DBG_PING_H(DBG_SIGNAL_SPI_CB);

    RV_LATENCY__UPDATE(report_go);
    report_go_previous = report_go;
    previous_tx_result = last_tx_result;

    // take a timestamp at the end
    timestamp_spi_cb_end_previous = timestamp_spi_cb_end;
    GPT_GET_FREE_RUN_COUNT_US(timestamp_spi_cb_end);
    #if 0
    uint32_t duration_count;
    hal_gpt_get_duration_count(timestamp_spi_cb_start, timestamp_spi_cb_end, &duration_count);
    if (duration_count >= 110)
    {
        HID_DBG_LOG(rv_exp,"hid_express_entrance run too long %u", 1, duration_count);
    }
    #endif

    DBG_PING_L(DBG_SIGNAL_SPI_CB);
    // DBG_PING_H(DBG_SIGNAL_SPI_CB);
    // DBG_PING_L(DBG_SIGNAL_SPI_CB);
}
#else
#if defined(AIR_PRODUCT_TYPE_MOUSE)
void hid_express_entrance(hal_spi_master_callback_event_t event, void *user_data)
#elif defined(AIR_PRODUCT_TYPE_KEYBOARD)

#include "assert.h"
#include "exception_handler.h"

void hid_express_entrance(uint32_t *keys, uint8_t one_packet_valid_num, uint8_t total_key_num, bool is_ghost_happen)
#endif
{
    DBG_PING_H(DBG_SIGNAL_SPI_CB); //start : 0 us
    // take a timestamp at the begging of spi callback
    timestamp_spi_cb_start_previous = timestamp_spi_cb_start;
    GPT_GET_FREE_RUN_COUNT_US(timestamp_spi_cb_start);
    RV_LATENCY__CHECK_POINT_FIRST(timestamp_spi_cb_start);

    hid_flags = hid_common->hid.flags;
    rr_idx_2_4g = hid_common->app.rr.rr_idx_2_4g;
    pka_active_state_always = 0;

    pka_share_callback_type_t type;
    uint32_t tx_cnt = 0;
    uint32_t timestamp_report_submitted = 0;

    #if defined(AIR_ACL_PACKET_VIA_HID_REPORT)
    // copy hid_common->hid.acl_pkt_queue to local memory first to save remote memory access time
    T_ACL_PACKET_QUEUE_S acl_pkt_queue;
    acl_pkt_queue.header = hid_common->hid.acl_pkt_queue.header;
    #endif

    if(USB_DATA_GO(hid_flags)){
        hid_express_usb_delay_for_latency();
    }

    if (peripheral_sampling_cb_ptr){
        peripheral_sampling_cb_ptr(HID_EXP_1ST_CB, NULL);
    }

    if(USB_DATA_GO(hid_flags) == 0){
        // DBG_PING_H(DBG_SIGNAL_DEBUG_1);
        pka_spi_callback_pre_process( &type, &tx_cnt);
        // DBG_PING_L(DBG_SIGNAL_DEBUG_1);
    }

    this_tx_idx = tx_cnt;
    last_tx_result = 0; /// Ack Ack

    // if (peripheral_sampling_cb_ptr)
    {
        if (USB_DATA_GO(hid_flags)){
            last_tx_result = USB_TX_NACK(hid_flags)?  1 : 0;
            rv_hid_exp_key_queue_pre_process(&kCtrl_k , last_tx_result, MODE_USB);
        }
        #if defined (AIR_HID_BT_MODE)
        else if (BT_DATA_GO(hid_flags)){
            last_tx_result = hid_express_bt_get_tx_result();
            rv_hid_exp_key_queue_pre_process(&kCtrl_k , last_tx_result, MODE_BT);
        }
        #endif
        else if (GAMING_DATA_GO(hid_flags)){
            #if defined(AIR_REPORT_DATA_LOG)
            hid_express_2_4g_copy_report_for_debug(previous_tx_result, report_go_previous);
            #endif
            rv_hid_exp_key_queue_pre_process(&kCtrl_k , previous_tx_result, MODE_2_4G);
            last_tx_result = hid_express_gaming_get_tx_status();

            /* Ahead  pka_active_state_always get for key latency*/
            pka_active_state_always = (pka_active_state_match(PKA_SHARE_ACTIVE_STATE_NORMAL) == false);
        }
        else {
            pka_spi_callback_post_process();

            if (peripheral_sampling_cb_ptr){
            peripheral_sampling_cb_ptr(HID_EXP_NO_REPORT_PROCESS, NULL);
            }

            hid_express_dbg_check();
            DBG_PING_L(DBG_SIGNAL_SPI_CB);
            g_riscv_ccni_irq_occur = false;
            return;
        }

        if (last_tx_result){
            dbg.nack_count++;
        }

        // show nack status
        if (last_tx_result)
        {
            DBG_PING_H(DBG_SIGNAL_TX_NACK);
            DBG_PING_L(DBG_SIGNAL_TX_NACK);
        }

        if (peripheral_sampling_cb_ptr){
            dbg.sampling_cnt++;
            peripheral_sampling_cb_ptr(HID_EXP_2ND_CB, &outgoing_data);
            #if defined(AIR_PRODUCT_TYPE_MOUSE)
            hid_express_prepare_X_Y(&outgoing_data);
            #endif
        }

        #if defined(AIR_ACL_PACKET_VIA_HID_REPORT)
        if (acl_pkt_queue.buf_head != acl_pkt_queue.buf_tail){
            // set up outgoing data, it will be pushed into key queue
            outgoing_data.acl_packet_data = hid_common->hid.acl_pkt_queue.response[acl_pkt_queue.buf_tail].data;
        }
        #endif

        if(USB_DATA_GO(hid_flags)){
            #if defined(AIR_PRODUCT_TYPE_MOUSE)
            hid_express_usb_wakeup_cm33_handler();
            #endif
        }

        if (peripheral_sampling_cb_ptr){
            RV_LATENCY__CHECK_POINT_SECOND();
            peripheral_sampling_cb_ptr(HID_EXP_3RD_CB_GET_KEY__TIMING_CRITICAL, &outgoing_data);

            // take timestamp_spi_cb_start as key press time is ok
            report_send_result = hid_express_send(&outgoing_data, timestamp_spi_cb_start);
        }
    }

    if(USB_DATA_GO(hid_flags) == 0){
        // complete the pka post process before too late
        // DBG_PING_H(DBG_SIGNAL_DEBUG_2);
        timestamp_report_submitted = pka_spi_callback_post_process();
        // DBG_PING_L(DBG_SIGNAL_DEBUG_2);
        RV_LATENCY__CHECK_POINT_THIRD(timestamp_report_submitted, report_go);
    }
    //DBG_LATENCY_H(DBG_SIGNAL_SPI_CB);

    #if defined(AIR_REPORT_DATA_LOG)
    if (report_go){
        hid_express_report_log__attach_dbg_timestamp(timestamp_report_submitted);
    }
    #endif

    #if defined (AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    key_remap_backend_process();
    #endif

    #if defined(AIR_ACL_PACKET_VIA_HID_REPORT)
    if (key_queue_push_result == STATUS_SUCCESS && outgoing_data.acl_packet_data ){
        // update notified packet number if key is pused successfully
        if ((acl_pkt_queue.buf_tail + 1) >= ACL_PKT_BUF_SIZE) {
            hid_common->hid.acl_pkt_queue.buf_tail = 0;
        }
        else {
            hid_common->hid.acl_pkt_queue.buf_tail =  acl_pkt_queue.buf_tail + 1;
        }
    }
    #endif


    // post process after pka_spi_callback_post_process
    if (peripheral_sampling_cb_ptr){
        peripheral_sampling_cb_ptr(HID_EXP_4TH_CB_POST_PROCESS, &outgoing_data);
        memset(&outgoing_data, 0, sizeof(outgoing_data));
    }

    hid_express_dbg_check();

    if (report_go){
        if (GAMING_DATA_GO(hid_flags)){
            hid_express_2_4g_post_process(last_tx_result);
        }
    }

    rv_hid_exp_key_queue_post_process(&kCtrl_k,  (timestamp_report_submitted - timestamp_spi_cb_start) );
    #if defined (AIR_FAKE_REPORT)
    rv_fake_report_post_process();
    #endif

    RV_LATENCY__UPDATE(report_go);

    report_go_previous = report_go;
    previous_tx_result = last_tx_result;
    last_tx_buff_num = tx_buff_num;
    g_riscv_ccni_irq_occur = false;
    DBG_PING_L(DBG_SIGNAL_SPI_CB);
    DBG_PING_H(DBG_SIGNAL_SPI_CB);
    DBG_PING_L(DBG_SIGNAL_SPI_CB);
 }
#endif

/* Public functions ---------------------------------------------------------*/
uint32_t hid_express_get_outgpoig_report_result()
{
    return report_send_result;
}

void hid_express_report_go_update(bool go)
{
    report_go = go;
}

#if defined(AIR_PRODUCT_TYPE_MOUSE)
int hid_express_prepare_X_Y(T_OUTGOING_VALUES_S * outgoing )
{
    hal_gpio_data_t motion_val;

    #if defined (AIR_FAKE_REPORT)
    rv_fake_report_fake_report(outgoing);
    #endif

    report_go = false;

    #if defined (AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    key_remap_frontend_process_xy(outgoing);
    #endif

    if( outgoing->z1){
        dbg.wheel_ok++;
    }

    if ( outgoing->x || outgoing->y )
    {
        dbg.sensor_ok++;
        report_go = true;
    }
    else
    {
        #if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
        if((last_tx_result && report_go_previous) || hid_express_x_y_buf_has_data())
        #else
        if(last_tx_result && report_go_previous)
        #endif
        {
            report_go = true;
        }
        else {
            report_go = false;
        }
    }

    hal_gpio_get_input(MOTION_PIN_GPIO, &motion_val);
    if(motion_val == 0)
    {
        dbg.motion_pin_cnt++;
    }

    /* Need to reset x, y queue when ack and report go previous */
    if (report_go || ((last_tx_result == 0) && report_go_previous))
    {
        if (GAMING_DATA_GO(hid_flags)){
            hid_express_2_4G_x_y_data_prepare(outgoing, last_tx_result, this_tx_idx, dongle_scenario);
        }
        #if defined (AIR_HID_BT_MODE) || defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        else if (BT_DATA_GO(hid_flags)){
            hid_express_bt_x_y_data_prepare(outgoing, last_tx_result, this_tx_idx, true);
        }
        #endif
        else if USB_DATA_GO(hid_flags){
            hid_express_usb_x_y_data_prepare(outgoing, last_tx_result, this_tx_idx);
        }

    }

    return 0;
}
#endif

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
int hid_express_send(T_OUTGOING_VALUES_S * outgoing, uint32_t timestamp_key_press)
{
    uint32_t result = 1;

    if (report_go || pka_active_state_always)
    {
        /* there is a new packet sent */
        if (GAMING_DATA_GO(hid_flags)){
            hid_express_gaming_data_send(outgoing, last_tx_result, this_tx_idx, dongle_scenario);
        }
        #if defined (AIR_HID_BT_MODE) || defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        else if (BT_DATA_GO(hid_flags)){
            hid_express_bt_data_send(outgoing, last_tx_result, this_tx_idx, true);
        }
        #endif
        else if USB_DATA_GO(hid_flags){
            hid_express_usb_data_send(outgoing, last_tx_result, this_tx_idx, report_go);
        } else {
            last_tx_result = 1;
        }
        if (report_go){
            result = 0; // success
            report_go = false;
        } else {
            // DBG_PING_H(40);
            // DBG_PING_L(40);
        }

    }
    else
    {
        if (GAMING_DATA_GO(hid_flags)){
            pka_share_push_hid_tx_ptr(reliable_tx_ptr);
        }
        #if defined (AIR_HID_BT_MODE) || defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        else if (BT_DATA_GO(hid_flags)){
            if(!is_bt_queue_empty()){
                hid_express_bt_data_send(outgoing, last_tx_result, this_tx_idx, false);
                result = 0;
            }
        }
        #endif
        #if defined(AIR_USB_CCNI_WAKEUP_CM33)
        else if (USB_DATA_GO(hid_flags)) {
            hid_express_usb_data_set_report_ready();
        }
        #endif /* _AIR_USB_CCNI_WAKEUP_CM33_*/
    }

    return result; // ignored
}
#else
int hid_express_send(T_OUTGOING_VALUES_S * outgoing, uint32_t timestamp_key_press )
{
    uint32_t result = 1;
    key_queue_push_result = STATUS_UNKNOWN;

    // DBG_PING_H(DBG_SIGNAL_DEBUG_1);
    #if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    #if defined(AIR_WHEEL_REMAP) && defined(AIR_PRODUCT_TYPE_MOUSE)
    key_remap_update_key_status(outgoing->k, outgoing->z1);
    #else
    key_remap_update_key_status(outgoing->k);
    #endif
    key_remap_frontend_process(outgoing);
    #endif

    // DBG_PING_L(DBG_SIGNAL_DEBUG_1);

    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    if (previous_key_status ^ outgoing->k){
        previous_key_status = outgoing->k;
        dbg.valid_key_cnt++;
    }

    KEY_QUEUE_STATUS status_z1 = STATUS_QUEUE_EMPTY;
    key_queue_push_result  = riscv_key_push(&kCtrl_k, outgoing, timestamp_key_press );
    // pop oldest key in queue
    KEY_QUEUE_STATUS status_k = riscv_key_pop_temperory(&kCtrl_k, outgoing, timestamp_key_press);
    // push current key status to queue
    #elif defined(AIR_PRODUCT_TYPE_KEYBOARD)
    DBG_PING_H(DBG_SIGNAL_TX_NACK);
    riscv_key_push(&kCtrl_k, outgoing, timestamp_key_press );
    // pop oldest key in queue
    KEY_QUEUE_STATUS status_k = riscv_key_pop_temperory(&kCtrl_k, outgoing, timestamp_key_press);
    // push current key status to queue
    DBG_PING_L(DBG_SIGNAL_TX_NACK);
    #endif

    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    if (status_k == STATUS_SUCCESS || status_z1 == STATUS_SUCCESS || outgoing->z1 || outgoing->z2)
    #else
    if (status_k == STATUS_SUCCESS)
    #endif
    {
        report_go = true;
        report_repeat_cnt = FORCE_REPORT_REPEAT_COUNTS; // workaround for packet missing
    }
    if (report_go || pka_active_state_always)
    {
        DBG_LATENCY_H(DBG_SIGNAL_LATCH_REPORT);

        if (GAMING_DATA_GO(hid_flags)){
            hid_express_gaming_data_send(outgoing, last_tx_result, this_tx_idx, dongle_scenario);
        }
        #if defined (AIR_HID_BT_MODE) || defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        else if (BT_DATA_GO(hid_flags)){
            hid_express_bt_data_send(outgoing, last_tx_result, this_tx_idx, true);
        }
        #endif
        else if (USB_DATA_GO(hid_flags)) {
            hid_express_usb_data_send(outgoing, last_tx_result, this_tx_idx, report_go);
        }
        DBG_LATENCY_L(DBG_SIGNAL_LATCH_REPORT);

        if (report_go) {
            result = 0; // success
        }
    }
    else {
        if (GAMING_DATA_GO(hid_flags)){
            pka_share_push_hid_tx_ptr(reliable_tx_ptr);
        }

        #if defined (AIR_NVIDIA_REFLEX)
        else if (USB_DATA_GO(hid_flags) && report_go_previous){
            hid_express_usb_data_send(outgoing, last_tx_result, this_tx_idx, report_go);
        }
        #endif
        #if defined(AIR_USB_CCNI_WAKEUP_CM33)
        else if (USB_DATA_GO(hid_flags)) {
            hid_express_usb_data_set_report_ready();

        }
        #endif /* _AIR_USB_CCNI_WAKEUP_CM33_*/

        #if defined (AIR_HID_BT_MODE) || defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        if(BT_DATA_GO(hid_flags) && !is_bt_queue_empty()){
            hid_express_bt_data_send(outgoing, last_tx_result, this_tx_idx, false);
            result = 0;
        }
        #endif
    }

    return result; // ignored
}
#endif

void hid_express_init_gpio_timestamp_latch()
{
    hal_eint_counter_enable();

    hal_eint_set_counter_number(5, EINT_COUNTER_NUMBER_0);
    hal_eint_set_counter_number(6, EINT_COUNTER_NUMBER_1);
    hal_eint_set_counter_number(17, EINT_COUNTER_NUMBER_2);
    hal_eint_set_counter_number(23, EINT_COUNTER_NUMBER_3);
    hal_eint_set_counter_number(24, EINT_COUNTER_NUMBER_4);
}

int hid_express_init(riscv_ps_callback_t ps_callback )
{
    //HID_DBG_LOG(rv_exp, "hid_express_init, callback = 0x%x ",1, callback);

    if (ps_callback) {
        peripheral_sampling_cb_ptr = ps_callback;
    }
    else {
        //HID_DBG_LOG(rv_exp, "Error ! Invalid callback function",0);
        return 1;
    }

    riscv_pka_init();
#if defined(AIR_PRODUCT_TYPE_MOUSE)
    hal_spi_master_register_callback(HAL_SPI_MASTER_0, hid_express_entrance, NULL);
    hid_express_init_gpio_timestamp_latch();
#elif defined(AIR_PRODUCT_TYPE_KEYBOARD)

    #if defined(AIR_HW_KEYSCAN)
        hal_hw_keyscan_register_callback((hal_hw_keyscan_callback_t)hid_express_entrance);
    #elif defined(AIR_SPIM)
        hal_spi_master_register_callback(HAL_SPI_MASTER_0, hid_express_entrance, NULL);
    #else
        #error "Unknown peripheral trigger configuration"
    #endif

    hid_express_init_gpio_timestamp_latch();
#elif defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)

    #if defined(AIR_HW_KEYSCAN)
        hal_hw_keyscan_register_callback((hal_hw_keyscan_callback_t)hid_express_entrance);
    #else
        hal_spi_master_register_callback(HAL_SPI_MASTER_0, hid_express_entrance, NULL);
    #endif /* AIR_HW_KEYSCAN */
#endif /* defined(AIR_PRODUCT_TYPE_***) */

    hid_express_usb_mode_init();
    hid_express_gaming_init();
    #if defined (AIR_HID_BT_MODE) || defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
    hid_express_bt_init();
    #endif
    init_key_ctrl(&kCtrl_k, 0);

    #if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    key_remap_frontend_init();
    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    key_remap_backend_init();
    #endif /* AIR_PRODUCT_TYPE_MOUSE */
    #endif /* AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */
    dongle_scenario = DONGLE_1627_1R2T_2K;
    hid_ctrl.rr_idx = DEFAULT_REPORT_RATE;

    #if defined(AIR_REPORT_DATA_LOG)
    report_log.buff_w_idx = REPORT_BUF_SIZE - REPORT_SIZE; // buff_w_idx will become 0 after +REPORT_SIZE
    #endif

    return 0;
}

void hid_express_dongle_scenario_update(uint32_t scenario)
{
    dongle_scenario = scenario;
}

void hid_express_set_features(uint32_t hid_exp_features)
{
    hid_exp_feature_option = hid_exp_features;
}

#if defined(AIR_REPORT_DATA_LOG)
void hid_express_copy_report_for_debug_print(uint8_t* ack, uint8_t* nack)
{
    // Update buff_w_idx first because nake report may be copied into ack report buffer for print
    // we do not want to change buff_w_idx and pool_idx when reports are filled
    report_log.buff_w_idx += REPORT_SIZE;

    if (report_log.buff_w_idx >= REPORT_BUF_SIZE) {
        report_log.buff_w_idx = 0;
        report_log.pool_idx = !report_log.pool_idx;
    }

    if (ack){
        FAST_WORD_COPY(&report_log.pool[report_log.pool_idx].ack[report_log.buff_w_idx], ack , 0);
        FAST_WORD_COPY(&report_log.pool[report_log.pool_idx].ack[report_log.buff_w_idx], ack , 1);
    }
}

void hid_express_report_log__attach_dbg_timestamp(uint32_t timestamp_of_submitted)
{
    if (report_go){
        uint32_t timestamp_delta_2;
        hal_gpt_get_duration_count(timestamp_spi_cb_start, timestamp_of_submitted, &timestamp_delta_2);
        *(uint16_t*)&report_log.pool[report_log.pool_idx].ack[report_log.buff_w_idx + DATA_SIZE] = (uint16_t)(timestamp_delta_2);

        // attach the detla time of each spi isr start time
        uint32_t timestamp_delta = timestamp_spi_cb_start - timestamp_spi_cb_start_previous;
        *(uint16_t*)&report_log.pool[report_log.pool_idx].ack[report_log.buff_w_idx + DATA_SIZE + 2] = (uint16_t)timestamp_delta;

        // Now, the time is ok for more debug check
        #if 0
        bool late_error = false;
        #define DELAY_TORANCE 3
        if (timestamp_delta > ((125 << (6-hid_ctrl.rr_idx)) + DELAY_TORANCE )){
            DBG_LATENCY_H(DBG_SIGNAL_DEBUG_3);
            DBG_LATENCY_L(DBG_SIGNAL_DEBUG_3);
            late_error = true;
        }

        //hid_common->app.riscv_trigger_time[hid_ctrl.rr_idx]
        if (timestamp_delta_2 >  0x48 ){
            late_error = true;
            DBG_LATENCY_H(DBG_SIGNAL_DEBUG_3);
            DBG_LATENCY_L(DBG_SIGNAL_DEBUG_3);
            DBG_LATENCY_H(DBG_SIGNAL_DEBUG_3);
            DBG_LATENCY_L(DBG_SIGNAL_DEBUG_3);
        }

        if (late_error){
            extern uint32_t sn_num ;
            uint32_t sn_num_dbg = sn_num & 0x03;

            while(sn_num_dbg--){
                DBG_LATENCY_H(DBG_SIGNAL_LATCH_REPORT);
                DBG_LATENCY_L(DBG_SIGNAL_LATCH_REPORT);
            }
            sn_num_dbg = (sn_num>>2) & 0x03;
            while(sn_num_dbg--){
                DBG_LATENCY_H(DBG_SIGNAL_DEBUG_3);
                DBG_LATENCY_L(DBG_SIGNAL_DEBUG_3);
            }
        }
        #endif
    }
}

void hid_express_report_log_print()
{
    if (report_log.pool_print_idx != report_log.pool_idx)
    {
        uint8_t*  log_buf =  (uint8_t*)&report_log.pool[report_log.pool_print_idx].ack;

        HID_DBG_LOG(rv_exp, "USB Report log[v6.00][%05u] [0~1]   =  %08X:%08X%08X, %08X:%08X%08X"
            , 7
            , report_log_counter
            , *(uint32_t*)&log_buf[	8 + (REPORT_SIZE * 0)]
            , *(uint32_t*)&log_buf[	4 + (REPORT_SIZE * 0)]
            , *(uint32_t*)&log_buf[	0 + (REPORT_SIZE * 0)]

            , *(uint32_t*)&log_buf[	8 + (REPORT_SIZE * 1)]
            , *(uint32_t*)&log_buf[	4 + (REPORT_SIZE * 1)]
            , *(uint32_t*)&log_buf[	0 + (REPORT_SIZE * 1)]
            );
        report_log_counter += 2;

        HID_DBG_LOG(rv_exp, "USB Report log[v6.00][%05u] [2~3]   =  %08X:%08X%08X, %08X:%08X%08X"
            , 7
            , report_log_counter
            , *(uint32_t*)&log_buf[	8 + (REPORT_SIZE * 2)]
            , *(uint32_t*)&log_buf[	4 + (REPORT_SIZE * 2)]
            , *(uint32_t*)&log_buf[	0 + (REPORT_SIZE * 2)]

            , *(uint32_t*)&log_buf[	8 + (REPORT_SIZE * 3)]
            , *(uint32_t*)&log_buf[	4 + (REPORT_SIZE * 3)]
            , *(uint32_t*)&log_buf[	0 + (REPORT_SIZE * 3)]
            );
        report_log_counter += 2;

        HID_DBG_LOG(rv_exp, "USB Report log[v6.00][%05u] [4~5]   =  %08X:%08X%08X, %08X:%08X%08X"
            , 7
            , report_log_counter
            , *(uint32_t*)&log_buf[	8 + (REPORT_SIZE * 4)]
            , *(uint32_t*)&log_buf[	4 + (REPORT_SIZE * 4)]
            , *(uint32_t*)&log_buf[	0 + (REPORT_SIZE * 4)]

            , *(uint32_t*)&log_buf[	8 + (REPORT_SIZE * 5)]
            , *(uint32_t*)&log_buf[	4 + (REPORT_SIZE * 5)]
            , *(uint32_t*)&log_buf[	0 + (REPORT_SIZE * 5)]
            );
        report_log_counter += 2;

        HID_DBG_LOG(rv_exp, "USB Report log[v6.00][%05u] [6~7]   =  %08X:%08X%08X, %08X:%08X%08X"
            , 7
            , report_log_counter
            , *(uint32_t*)&log_buf[	8 + (REPORT_SIZE * 6)]
            , *(uint32_t*)&log_buf[	4 + (REPORT_SIZE * 6)]
            , *(uint32_t*)&log_buf[	0 + (REPORT_SIZE * 6)]

            , *(uint32_t*)&log_buf[	8 + (REPORT_SIZE * 7)]
            , *(uint32_t*)&log_buf[	4 + (REPORT_SIZE * 7)]
            , *(uint32_t*)&log_buf[	0 + (REPORT_SIZE * 7)]
            );
        report_log_counter += 2;

        report_log.pool_print_idx = report_log.pool_idx;
    }
}

bool hid_express_report__get_log_data_ptr(T_HID_REPORT_LOG_S** log_data_ptr)
{
    *log_data_ptr = &report_log;
    return false;
}
#endif

void hid_express_debug_print()
{
    uint32_t riscv_trigger_time = hid_common->app.riscv_trigger_time[hid_ctrl.rr_idx];

    riscv_hid_express_key_queue_debug_print(&kCtrl_k, riscv_trigger_time);
    rv_hid_exp_delay_printf();

    RV_LATENCY__CHECK_AND_PRINT_REPORT();

    #if defined(AIR_REPORT_DATA_LOG)
    if USB_DATA_GO(hid_flags)
    {
        hid_express_report_log_print();
    }
    #endif
}

void hid_express_set_report_rate_idx(uint32_t rr)
{
    hid_ctrl.rr_idx = rr;
    report_rate_pka = rr;
    LOG_MSGID_I(rv_exp, "hid_express_set_report_rate_idx rr = %d ", 1, hid_ctrl.rr_idx);
}

void hid_express_clear_key_pushed()
{
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    riscv_game_controller_key_clear_key_pushed(&kCtrl_k);
#else
    riscv_key_clear_key_pushed(&kCtrl_k);
#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */
    return;
}

void hid_express__push_to_key_queue(uint32_t value_type, uint32_t value)
{
    #if !defined(AIR_PRODUCT_TYPE_KEYBOARD)
    uint32_t timestamp_key_press;
    GPT_GET_FREE_RUN_COUNT_US(timestamp_key_press);
    #endif
    T_OUTGOING_VALUES_S temp_outgoing;
    memset(&temp_outgoing, 0, sizeof(temp_outgoing));
    #if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
        /* TODO: implement it */
    #elif defined(AIR_PRODUCT_TYPE_MOUSE)
    if(is_queue_num_2(&kCtrl_k)) {
        riscv_key_pop_confirm(&kCtrl_k);
    }
    #endif /* !defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER) */

    #if defined (AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    switch(value_type)
    {
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
        case K_TYPE_K:
        {
            temp_outgoing.k.word = value;
        }
        break;
#else
        case K_TYPE_K:
        {
            temp_outgoing.k = value;
        }
        break;

        #if defined(AIR_PRODUCT_TYPE_MOUSE)
        case K_TYPE_Z1:
        {
            temp_outgoing.z1 = value;
        }
        break;
        #endif

#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */
        default:
        break;
    }

    #if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    riscv_game_controller_wakeup_key_push(&kCtrl_k, &temp_outgoing, timestamp_key_press);
    #else
    #if defined(AIR_WHEEL_REMAP)
    key_remap_update_key_status(temp_outgoing.k, temp_outgoing.z1);
    #else
    rv_key_remap_update_key_status(temp_outgoing.k);
    #endif /* AIR_WHEEL_REMAP */
    key_remap_backend_process();

    // HID_DBG_LOG(rv_exp, "temp_outgoing.k = 0x%X, temp_outgoing.z1 = %d" , 2 , temp_outgoing.k, temp_outgoing.z1 );    
    key_remap_frontend_process(&temp_outgoing);
    riscv_key_push(&kCtrl_k, &temp_outgoing, timestamp_key_press);
    #endif

    #else
    switch(value_type)
    {
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
        /* TODO: implement it */
#elif defined(AIR_PRODUCT_TYPE_MOUSE)
        case K_TYPE_K:
        {
            temp_outgoing.k = value;
            riscv_key_push(&kCtrl_k, &temp_outgoing, timestamp_key_press);
        }
        break;

        case K_TYPE_Z1:
        {
            temp_outgoing.z1 = value;
            riscv_key_push(&kCtrl_k, &temp_outgoing, timestamp_key_press);
        }
        break;
#endif /* !defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER) */

        default:
        break;
    }
    #endif
}

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
void hid_express_set_mode(uint8_t mode)
{
    scenario_mode = mode;
    HID_DBG_LOG(rv_exp,"hid_express_set_mode %d", 1, scenario_mode);
}

uint8_t hid_express_get_mode(void)
{
    return scenario_mode;
}
#endif

void hid_express_deinit()
{
    #if defined(AIR_PRODUCT_TYPE_MOUSE) && defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    key_remap_backend_deinit();
    #endif
}

uint32_t hid_express_get_report_go_previous()
{
    return report_go_previous;
}

uint32_t hid_express_get_last_report_go()
{
    return last_report_go;
}
// #endif /*  */
