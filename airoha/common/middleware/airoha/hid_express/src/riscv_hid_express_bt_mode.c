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

#if defined(AIR_HID_BT_MODE) || defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "riscv_hid_express_bt_mode.h"
#include "rv_burst_tx_buf_ctrl.h"
#include "pka_share.h"
#include "pka.h"
#include "riscv_hid_express_xy_queue.h"
#if defined (CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
#include "riscv_hid_express_key_queue_keyboard.h"
#elif defined (AIR_PRODUCT_TYPE_MOUSE)
#include "riscv_hid_express_key_queue_mouse.h"
#endif

/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
T_BT_HID_REPORT_S default_BT_report = {0};
T_BT_DEBUG_S bt_debug = {0};
T_BT_QUEUE_CTRL_S bt_ctrl;
uint32_t bt_buffer_size;
uint32_t bt_buffer_size_mask;
T_ATT_ATTRIBUTE_HANDLE_S attr_handle;
uint32_t tx_result = 0;
uint32_t last_kb_report = 0;

/* Private functions ---------------------------------------------------------*/
void init_bt_queue() {
    bt_ctrl.front = 0;
    bt_ctrl.rear = 0;
    bt_buffer_size = BT_BUFFER_SIZE_DEFAULT;
    bt_buffer_size_mask = BT_BUFFER_SIZE_DEFAULT_MASK;
}

bool is_bt_queue_empty() {
    return bt_ctrl.front == bt_ctrl.rear;
}

bool is_bt_queue_full() {
    return (((bt_ctrl.rear + 1) & bt_buffer_size_mask) == bt_ctrl.front);
}

HID_EXPRESS_BT_QUEUE_STATUS bt_queue_push(T_BT_HID_REPORT_S report) {
    if (is_bt_queue_full()) {
        return BT_QUEUE_STATUS_QUEUE_FULL;
    }
    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    if(report.att.ATTRIBUTE_HANDLE != attr_handle.ms)
    {
        return BT_QUEUE_STATUS_NOT_MOUSE;
    }
    #endif /* AIR_PRODUCT_TYPE_MOUSE */

    bt_ctrl.bt_report[bt_ctrl.rear] = report;
    // HID_DBG_LOG(rv_exp, "push bt_ctrl.rear = %d, front = %d", 2, bt_ctrl.rear, bt_ctrl.front);
    // HID_DBG_LOG(rv_exp, "push x = %02d y = %02d", 2, bt_ctrl.bt_report[bt_ctrl.rear].ms_hid.x, bt_ctrl.bt_report[bt_ctrl.rear].ms_hid.y);
    bt_ctrl.rear = (bt_ctrl.rear + 1) & bt_buffer_size_mask;
    return BT_QUEUE_STATUS_SUCCESS;
}

HID_EXPRESS_BT_QUEUE_STATUS bt_queue_pop(T_BT_HID_REPORT_S *outgoing_report) {
    if (is_bt_queue_empty()) {
       return BT_QUEUE_STATUS_QUEUE_EMPTY;
    }

    memcpy(outgoing_report, &bt_ctrl.bt_report[bt_ctrl.front], sizeof(bt_ctrl.bt_report[bt_ctrl.front]));
    // HID_DBG_LOG(rv_exp, "pop bt_ctrl.rear = %d, front = %d", 2, bt_ctrl.rear, bt_ctrl.front);
    // HID_DBG_LOG(rv_exp, "pop x = %02d y = %02d", 2, outgoing_report->ms_hid.x, outgoing_report->ms_hid.y);
    bt_ctrl.front = (bt_ctrl.front + 1) & bt_buffer_size_mask;
    return BT_QUEUE_STATUS_SUCCESS;
}

HID_EXPRESS_BT_QUEUE_STATUS hid_express_bt_merge_xy(int16_t x, int16_t y) {
    if (is_bt_queue_empty()) {
        return BT_QUEUE_STATUS_QUEUE_EMPTY;
    }
    uint8_t rearIndex = (bt_ctrl.rear - 1 + bt_buffer_size) & bt_buffer_size_mask;
    bt_ctrl.bt_report[rearIndex].ms_hid.x += x;
    bt_ctrl.bt_report[rearIndex].ms_hid.y += y;
    //HID_DBG_LOG(rv_exp, "merge rearIndex = %02d, x = %02d y = %02d", 3, rearIndex, bt_ctrl.bt_report[rearIndex].ms_hid.x, bt_ctrl.bt_report[rearIndex].ms_hid.y);
    return BT_QUEUE_STATUS_SUCCESS;
}

#if 0
void print_queue() {
    uint8_t index = bt_ctrl.front;
    while (index != bt_ctrl.rear) {
        T_BT_HID_REPORT_S* report = &bt_ctrl.bt_report[index];
        HID_DBG_LOG(rv_exp, "Report at index %d: X=%d, Y=%d, Z2=%d", 4,
            index,
            report->ms_hid.x,
            report->ms_hid.y,
            report->ms_hid.z2);

        index = (index + 1) & bt_buffer_size_mask;
    }
}
#endif

#if defined(AIR_PRODUCT_TYPE_MOUSE)
static void hid_express_bt_assemble_ms_report(T_BT_HID_REPORT_S* assemble_report, T_OUTGOING_VALUES_S* outgoing)
{
    memcpy(assemble_report, &default_BT_report, sizeof(T_BT_HID_REPORT_S));

    assemble_report->ms_hid.k = outgoing->k;
    assemble_report->ms_hid.x = outgoing->x;
    assemble_report->ms_hid.y = outgoing->y;
    assemble_report->ms_hid.z1 = outgoing->z1;
    assemble_report->ms_hid.z2 = outgoing->z2;
    assemble_report->att.ATTRIBUTE_HANDLE = attr_handle.ms;
    #if 0
    HID_DBG_LOG(rv_exp, "report at 0x%04X,  k= 0x%02X, x= 0x%04X, y= 0x%04X, z1= 0x%02X"
                , 5
                , &assemble_report->ms_hid.k
                , assemble_report->ms_hid.k
                , assemble_report->ms_hid.x
                , assemble_report->ms_hid.y
                , assemble_report->ms_hid.z1
                );
    #endif
}
#endif /* AIR_PRODUCT_TYPE_MOUSE */

#if defined (AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP) && !defined(AIR_PRODUCT_TYPE_KEYBOARD) && !defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
static void hid_express_bt_assemble_kb_std_report(T_BT_HID_REPORT_S* assemble_report, T_OUTGOING_VALUES_S* outgoing)
{
    memcpy(assemble_report, &default_BT_report, sizeof(T_BT_HID_REPORT_S));
    assemble_report->att.ATTRIBUTE_HANDLE = attr_handle.kb_std;
    assemble_report->kb_std5.combo = outgoing->kb_std[0] & LSB;
    assemble_report->kb_std5.keycode[0] =(outgoing->kb_std[0] >> 8) & LSB;
    assemble_report->kb_std5.keycode[1] = (outgoing->kb_std[0] >> 16) & LSB;
    assemble_report->kb_std5.keycode[2] = (outgoing->kb_std[0] >> 24) & LSB;
    assemble_report->kb_std5.keycode[3] = outgoing->kb_std[1] & LSB;
    assemble_report->kb_std5.keycode[4] = (outgoing->kb_std[1] >> 8) & LSB;

    #if 0
    HID_DBG_LOG(rv_exp, "hid_express_bt_assemble_kb_std_report %02X %02X %02X %02X %02X %02X"
                , 6
                , assemble_report->kb_std5.combo
                , assemble_report->kb_std5.keycode[0]
                , assemble_report->kb_std5.keycode[1]
                , assemble_report->kb_std5.keycode[2]
                , assemble_report->kb_std5.keycode[3]
                , assemble_report->kb_std5.keycode[4]
                );
    #endif
}

static void hid_express_bt_assemble_kb_consumer_report(T_BT_HID_REPORT_S* assemble_report, T_OUTGOING_VALUES_S* outgoing)
{
    memcpy(assemble_report, &default_BT_report, sizeof(T_BT_HID_REPORT_S));
    assemble_report->att.ATTRIBUTE_HANDLE = attr_handle.kb_csm;
    assemble_report->kb_consumer2.consumer[0] = outgoing->kb_consumer & 0xFFFF;
    assemble_report->kb_consumer2.consumer[1] = (outgoing->kb_consumer >> 16) & 0xFFFF;

    #if 0
    HID_DBG_LOG(rv_exp, "hid_express_bt_assemble_kb_consumer_report, %04X %04X %02X"
                , 3
                , assemble_report->kb_consumer2.consumer[0]
                , assemble_report->kb_consumer2.consumer[1]
                , assemble_report->kb_consumer2.numeric_key_pad
                );
    #endif
}
#endif /* just for defined(AIR_PRODUCT_TYPE_MOUSE) */

#if defined (AIR_PRODUCT_TYPE_KEYBOARD) && defined(AIR_HID_BT_MODE)
static void hid_express_bt_assemble_kb_nkey_report(T_BT_HID_REPORT_S* assemble_report, T_OUTGOING_VALUES_S* outgoing)
{
    memcpy(assemble_report, &default_BT_report, sizeof(T_BT_HID_REPORT_S));
    assemble_report->att.ATTRIBUTE_HANDLE = attr_handle.kb_nkey;
    memcpy(&assemble_report->kb_nkey, &outgoing->kb_nkey_map[0], 16);
    assemble_report->l2cap.LEN = sizeof(T_ATT_HEADER_S) + sizeof(T_HID_REPORT_KB_NKEY_BT_PAYLOAD_S);
    
    #if 0
    HID_DBG_LOG(rv_exp, "hid_express_bt_assemble_kb_nkey_report %08X %08X %08X %08X"
                , 4
                , outgoing->kb_nkey_map[0]
                , outgoing->kb_nkey_map[1]
                , outgoing->kb_nkey_map[2]
                , outgoing->kb_nkey_map[3]
                );
    #endif
}

static void hid_express_bt_assemble_ms_report(T_BT_HID_REPORT_S* assemble_report, T_OUTGOING_VALUES_S* outgoing)
{
    memcpy(assemble_report, &default_BT_report, sizeof(T_BT_HID_REPORT_S));

    assemble_report->ms_hid.x = 0;
    assemble_report->ms_hid.y = 0;
    assemble_report->ms_hid.z1 = (outgoing->kb_ms) & LSB;
    assemble_report->ms_hid.z2 = 0;
    assemble_report->ms_hid.k = (outgoing->kb_ms >> 8) & LSB;
    assemble_report->l2cap.LEN = sizeof(T_ATT_HEADER_S) + sizeof(T_MOUSE_REPORT_PAYLOAD_S);
    assemble_report->att.ATTRIBUTE_HANDLE = attr_handle.ms;
    #if defined(AIR_DEBUG_POLLING_LOG)
    HID_DBG_LOG(rv_exp, "hid_express_bt_assemble_ms_report at 0x%04X,  k= 0x%02X, x= 0x%04X, y= 0x%04X, z1= 0x%02X"
                , 5
                , &assemble_report->ms_hid.k
                , assemble_report->ms_hid.k
                , assemble_report->ms_hid.x
                , assemble_report->ms_hid.y
                , assemble_report->ms_hid.z1
                );

    HID_DBG_LOG(rv_exp, "hid_express_bt_assemble_report", 0);
    #endif
}

static void hid_express_bt_assemble_kb_consumer_report(T_BT_HID_REPORT_S* assemble_report, T_OUTGOING_VALUES_S* outgoing)
{
    memcpy(assemble_report, &default_BT_report, sizeof(T_BT_HID_REPORT_S));
    assemble_report->att.ATTRIBUTE_HANDLE = attr_handle.kb_csm;
    assemble_report->kb_consumer2.consumer[0] = outgoing->kb_consumer & 0xFFFF;
    assemble_report->kb_consumer2.consumer[1] = (outgoing->kb_consumer >> 16) & 0xFFFF;
    assemble_report->l2cap.LEN = sizeof(T_ATT_HEADER_S) + sizeof(T_MOUSE_REPORT_PAYLOAD_S);
    #if defined(AIR_DEBUG_POLLING_LOG)
    HID_DBG_LOG(rv_exp, "hid_express_bt_assemble_kb_consumer_report, %04X %04X %02X"
                , 3
                , assemble_report->kb_consumer2.consumer[0]
                , assemble_report->kb_consumer2.consumer[1]
                , assemble_report->kb_consumer2.numeric_key_pad
                );
    #endif
}

#endif

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
static uint16_t hid_express_bt_assemble_button_convert(uint16_t input)
{
    typedef struct {
        // Buttons (1 bit each)
        uint8_t button_a : 1;       // Button A
        uint8_t button_b : 1;       // Button B
        uint8_t reserved1 : 1;      // Reserved  bit
        uint8_t button_x : 1;       // Button X
        uint8_t button_y : 1;       // Button Y
        uint8_t reserved2 : 1;      // Reserved  bit
        uint8_t button_lb : 1;      // Left Bumper
        uint8_t button_rb : 1;      // Right Bumper

        uint8_t reserved3 : 2;      // Reserved  bit
        uint8_t button_back : 1;    // menu  button
        uint8_t button_start : 1;   // Start button
        uint8_t button_logo : 1;    // Logo button
        uint8_t button_ls : 1;      // Left Stick Click
        uint8_t button_rs : 1;      // Right Stick Click
        uint8_t reserved4 : 1;       // Reserved  bit
    } __attribute__((packed)) gamepad_output_bits;

    typedef struct {
        // Buttons (1 bit each)
        uint8_t button_a : 1;       // Button A
        uint8_t button_b : 1;       // Button B
        uint8_t button_x : 1;       // Button X
        uint8_t button_y : 1;       // Button Y
        uint8_t button_ls : 1;      // Left Stick Click
        uint8_t button_rs : 1;      // Right Stick Click
        uint8_t button_lb : 1;      // Left Bumper
        uint8_t button_rb : 1;      // Right Bumper

        uint8_t button_logo : 1;    // Logo button
        uint8_t button_start : 1;   // Start button
        uint8_t button_back : 1;    // menu  button
        uint8_t reserved : 5;      // Reserved  bit
    } __attribute__((packed)) gamepad_in_bits;

    typedef union {
        gamepad_output_bits bits;
        uint16_t output_byte;
    } gamepad_out_button;

    typedef union {
        gamepad_in_bits bits;
        uint16_t input_byte;
    } gamepad_in_button;

    gamepad_in_button in_button = {0};
    gamepad_out_button out_button = {0};
    in_button.input_byte = input;

    out_button.bits.button_a = in_button.bits.button_a;
    out_button.bits.button_b = in_button.bits.button_b;
    out_button.bits.button_x = in_button.bits.button_x;
    out_button.bits.button_y = in_button.bits.button_y;
    out_button.bits.button_lb = in_button.bits.button_lb;
    out_button.bits.button_rb = in_button.bits.button_rb;
    out_button.bits.button_back = in_button.bits.button_back;
    out_button.bits.button_start = in_button.bits.button_start;
    out_button.bits.button_logo = in_button.bits.button_logo;
    out_button.bits.button_ls = in_button.bits.button_ls;
    out_button.bits.button_rs = in_button.bits.button_rs;
    return out_button.output_byte;
}

static void hid_express_bt_assemble_game_controller_report(T_BT_HID_REPORT_S* assemble_report, T_OUTGOING_VALUES_S* outgoing)
{


    static uint16_t s_last_tx_button_byte = 0;
    s_last_tx_button_byte = outgoing->key_air_byte;
    if (lt_is_digital()){
        outgoing->lt = (outgoing->lt_rt_digital & 0x1) ? 1023 : 0;
    }
    if (rt_is_digital()){
        outgoing->rt = (outgoing->lt_rt_digital & 0x2) ? 1023 : 0;
    }
    memcpy(assemble_report, &default_BT_report, sizeof(T_BT_HID_REPORT_S));
    assemble_report->att.ATTRIBUTE_HANDLE = attr_handle.game_controller;
    assemble_report->gamepad.x  = outgoing->x;
    assemble_report->gamepad.y  = outgoing->y;
    assemble_report->gamepad.z  = outgoing->z;
    assemble_report->gamepad.rz = outgoing->rz;
    assemble_report->gamepad.brake = outgoing->lt;
    assemble_report->gamepad.accelerator = outgoing->rt;
    assemble_report->gamepad.hat_switch = outgoing->hat_switch_byte;
    assemble_report->gamepad.button = hid_express_bt_assemble_button_convert(s_last_tx_button_byte);
    //assemble_report->gamepad.record = ((outgoing->k.word >> 24) & 0xffff);
    outgoing->last_x = outgoing->x;
    outgoing->last_y = outgoing->y;
    outgoing->last_z = outgoing->z;
    outgoing->last_rz = outgoing->rz;
    outgoing->last_lt = outgoing->lt;
    outgoing->last_rt = outgoing->rt;
    outgoing->last_key_air_byte = outgoing->key_air_byte;
}
#endif

static void hid_express_bt_submit_report_to_pka_16bits(T_BT_HID_REPORT_S* assemble_report)
{
    uint8_t* bt_tx_buffer = pka_share_tx_buf_get_from_q();
    if (bt_tx_buffer == NULL) {
        // HID_DBG_LOG(rv_exp, "bt_tx_buffer is NULL", 0);
        return;
    }

    T_BT_HID_REPORT_S* outgoing_report = (T_BT_HID_REPORT_S*)pka_share_tx_buf_get_payload(bt_tx_buffer);

    memcpy(outgoing_report, assemble_report, sizeof(T_BT_HID_REPORT_S));

    #if 0
    HID_DBG_LOG(rv_exp, "hid_express_bt_submit_report_to_pka_12bits, bt_tx_buffer = 0x%X, outgoing_payload = 0x%X, sizeof(T_BT_HID_REPORT_S) = %d"
                , 3
                , bt_tx_buffer
                , outgoing_report
                , sizeof(T_BT_HID_REPORT_S)
                );

    HID_DBG_LOG(rv_exp, "outgoing_payload at 0x%04X, LEN =  0x%04X, CH_ID = 0x%04X, OPCODE = 0x%02X, ATTRIBUTE_HANDLE = 0x%04X  "
                , 5
                , &outgoing_report->l2cap.LEN
                , outgoing_report->l2cap.LEN
                , outgoing_report->l2cap.CH_ID
                , outgoing_report->att.OPCODE
                , outgoing_report->att.ATTRIBUTE_HANDLE
                );

    HID_DBG_LOG(rv_exp, "report at 0x%04X,  k= 0x%02X, x= %d, y= %d, z1= 0x%02X"
                , 6
                , &outgoing_report->ms_hid.k
                , outgoing_report->ms_hid.k
                , outgoing_report->ms_hid.x
                , outgoing_report->ms_hid.y
                , outgoing_report->ms_hid.z1
                );
    #endif
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER) && defined(AIR_HID_BT_MODE)
    pka_share_tx_buf_set_pkt_len((uint16_t *)bt_tx_buffer, 23);
#elif defined(AIR_PRODUCT_TYPE_KEYBOARD) && defined(AIR_HID_BT_MODE)
    pka_share_tx_buf_set_pkt_len((uint16_t *)bt_tx_buffer, assemble_report->att.ATTRIBUTE_HANDLE == attr_handle.kb_nkey ? 23 :15);
#else
    pka_share_tx_buf_set_pkt_len((uint16_t *)bt_tx_buffer, 15);
#endif
    pka_share_tx_buf_send(bt_tx_buffer);

    #if defined(AIR_REPORT_DATA_LOG)
    DBG_PING_H(DBG_SIGNAL_DEBUG_3);
    hid_express_copy_report_for_debug_print((uint8_t*)&outgoing_report->ms_hid, NULL);
    DBG_PING_L(DBG_SIGNAL_DEBUG_3);
    #endif
}

static void hid_express_bt_send_report(T_BT_HID_REPORT_S *assemble_report, uint32_t assemble)
{
    DBG_PING_H(DBG_SIGNAL_DEBUG_3);
    uint32_t buf_avail_num = pka_share_tx_buf_avail_num();
    uint32_t controller_buffer_avail = rv_bt_burst_tx_num_ctrl(assemble_report, buf_avail_num);
    tx_result = 0;
    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    last_kb_report = 0;
    #endif

    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    if(((assemble_report->att.ATTRIBUTE_HANDLE == attr_handle.kb_std) ||
        (assemble_report->att.ATTRIBUTE_HANDLE == attr_handle.kb_csm)) && buf_avail_num)
    {
        DBG_PING_L(DBG_SIGNAL_DEBUG_3);
        hid_express_bt_submit_report_to_pka_16bits(assemble_report);
        last_kb_report = 1;
        DBG_PING_H(DBG_SIGNAL_DEBUG_3);
    }
    else
    #endif
    if(controller_buffer_avail)
    {
        //DBG_PING_L(DBG_PIN_BT_KEY);
        if(!is_bt_queue_empty())
        {
            while(!is_bt_queue_empty() && controller_buffer_avail)
            {
                /* App BT Queue is not empty, pop the report from the queue and push new report to queue*/
                T_BT_HID_REPORT_S popped_report;
                bt_queue_pop(&popped_report);

                DBG_PING_L(DBG_SIGNAL_DEBUG_3);
                hid_express_bt_submit_report_to_pka_16bits(&popped_report);
                DBG_PING_H(DBG_SIGNAL_DEBUG_3);
                controller_buffer_avail--;
                // HID_DBG_LOG(rv_exp, "App BT Queue is not empty, pop the report from the queue and push new report to queue = %d", 1, controller_buffer_avail);
            }

            if(assemble)
            {
                if(controller_buffer_avail)
                {
                    DBG_PING_L(DBG_SIGNAL_DEBUG_3);
                    hid_express_bt_submit_report_to_pka_16bits(assemble_report);
                    DBG_PING_H(DBG_SIGNAL_DEBUG_3);
                }
                else if(!is_bt_queue_full())
                {
                    bt_queue_push(*assemble_report);
                    bt_debug.controller_full++;
                }
                else
                {
                    #if defined (AIR_BT_DATA_MERGE_XY)
                    if(assemble_report->att.ATTRIBUTE_HANDLE == attr_handle.ms)
                    {
                        hid_express_bt_merge_xy(assemble_report->ms_hid.x, assemble_report->ms_hid.y);
                    }
                    bt_debug.drop_data++;
                    bt_debug.controller_full++;
                    #endif
                    tx_result = 1;
                }
            }
        }
        else{
            /* App BT Queue is empty, submit a report to controller buffer */
            DBG_PING_L(DBG_SIGNAL_DEBUG_3);
            hid_express_bt_submit_report_to_pka_16bits(assemble_report);
            DBG_PING_H(DBG_SIGNAL_DEBUG_3);

            //HID_DBG_LOG(rv_exp, "App BT Queue is empty, submit a report to controller buffer", 0);
        }
        //DBG_PING_H(DBG_PIN_BT_KEY);
    }
    else if(!is_bt_queue_full())
    {
        /* App BT Queue is not full, push the report to the queue */
        bt_queue_push(*assemble_report);
        // HID_DBG_LOG(rv_exp, "App BT Queue is not full, push the report to the queue", 0);
        bt_debug.controller_full++;
    }
    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    else{
        /* App BT Queue is full, merge or drop x, y data */
        #if defined (AIR_BT_DATA_MERGE_XY)
        if(assemble_report->att.ATTRIBUTE_HANDLE == attr_handle.ms)
        {
            hid_express_bt_merge_xy(assemble_report->ms_hid.x, assemble_report->ms_hid.y);
            if((assemble_report->ms_hid.k != 0) || (assemble_report->ms_hid.z1 != 0) || (assemble_report->ms_hid.z2 != 0))
            {
                controller_buffer_avail = 0;
            }
            else
            {
                controller_buffer_avail = 1;
            }
        }
        // HID_DBG_LOG(rv_exp, "App BT Queue is full, merge x, y data", 0);
        #else
        if((assemble_report->ms_hid.k != 0) || (assemble_report->ms_hid.z1 != 0) || (assemble_report->ms_hid.z2 != 0))
        {
            T_BT_HID_REPORT_S popped_report;
            bt_queue_pop(&popped_report);
            bt_queue_push(*assemble_report);
        }
        //HID_DBG_LOG(rv_exp, "App BT Queue is full, drop x, y data", 0);
        #endif
        bt_debug.drop_data++;
        bt_debug.controller_full++;
        tx_result = 1;
    }

    if(buf_avail_num == 0)
    {
        bt_debug.tx_buffer_full++;
    }
    #endif

    DBG_PING_L(DBG_SIGNAL_DEBUG_3);
}

/* Public variables ----------------------------------------------------------*/
int hid_express_bt_get_tx_result()
{
    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    if((tx_result == 0) || last_kb_report)
    #else
    if((tx_result == 0))
    #endif
    {
        return 0;
    }
    return 1;
}

#if defined(AIR_PRODUCT_TYPE_MOUSE)
int hid_express_bt_x_y_data_prepare(T_OUTGOING_VALUES_S* outgoing, uint32_t tx_result, uint32_t  tx_idx, uint32_t assemble)
{
    return 0;
}
#endif

int hid_express_bt_data_send(T_OUTGOING_VALUES_S* outgoing, uint32_t tx_result, uint32_t  tx_idx, uint32_t assemble)
{
    T_BT_HID_REPORT_S assemble_report = {0};
    /* Assemble the BT report */
    if(assemble)
    {
        #if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP) && !defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
        if(outgoing->type == REPORT_ID_KB_STD)
        {
            hid_express_bt_assemble_kb_std_report(&assemble_report, outgoing);
            hid_express_bt_send_report(&assemble_report, assemble);
        }
        else if(outgoing->type == REPORT_ID_KB_CONSUMER)
        {
            hid_express_bt_assemble_kb_consumer_report(&assemble_report, outgoing);
            hid_express_bt_send_report(&assemble_report, assemble);
        }
        #endif /* AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP && !AIR_PRODUCT_TYPE_GAME_CONTROLLER */
        #if defined(AIR_PRODUCT_TYPE_MOUSE) || (defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP) && !defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER))
        #if defined(AIR_PRODUCT_TYPE_MOUSE)
        if(outgoing->type == REPORT_ID_MOUSE || outgoing->x != 0 || outgoing->y != 0)
        #elif defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
        else if(outgoing->type == REPORT_ID_MOUSE)
        #endif
        {
            hid_express_bt_assemble_ms_report(&assemble_report, outgoing);
            hid_express_bt_send_report(&assemble_report, assemble);
        }
        #endif
        #if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
        if (outgoing->type >= REPORT_ID_GAME_CONTROLLER && outgoing->type <= REPORT_ID_GAME_CONTROLLER_GROUP2) {
            hid_express_bt_assemble_game_controller_report(&assemble_report, outgoing);
            hid_express_bt_send_report(&assemble_report, assemble);
        }
        #endif
        #if defined(AIR_PRODUCT_TYPE_KEYBOARD) && defined(AIR_HID_BT_MODE)
        if (outgoing->type >= REPORT_ID_KEYBOARD && outgoing->type <= REPORT_ID_KEYBOARD_GROUP1) {
            hid_express_bt_assemble_kb_nkey_report(&assemble_report, outgoing);
            hid_express_bt_send_report(&assemble_report, assemble);
        } 
        else if(outgoing->type == REPORT_ID_MOUSE)
        {
            hid_express_bt_assemble_ms_report(&assemble_report, outgoing);
            hid_express_bt_send_report(&assemble_report, assemble);
        }
        else if(outgoing->type == REPORT_ID_KB_CONSUMER)
        {
            hid_express_bt_assemble_kb_consumer_report(&assemble_report, outgoing);
            hid_express_bt_send_report(&assemble_report, assemble);
        }
        #endif
    }
    else
    {
        hid_express_bt_send_report(&assemble_report, assemble);
    }

    return 0;
}

void hid_express_bt_init()
{
    init_bt_queue();
    #if defined(AIR_REPORT_DATA_LOG)
    memset((uint8_t*)&report_log, 0, sizeof(report_log));
    #endif
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER) && defined(AIR_HID_BT_MODE)
    default_BT_report.l2cap.LEN = sizeof(T_ATT_HEADER_S) + sizeof(T_HID_REPORT_GAME_CONTROLLER_BT_PAYLOAD_S);
#elif defined(AIR_PRODUCT_TYPE_KEYBOARD) && defined(AIR_HID_BT_MODE)
    default_BT_report.l2cap.LEN = sizeof(T_ATT_HEADER_S) + sizeof(T_HID_REPORT_KB_NKEY_BT_PAYLOAD_S);
#else
    default_BT_report.l2cap.LEN = sizeof(T_ATT_HEADER_S) + sizeof(T_MOUSE_REPORT_PAYLOAD_S);
#endif
    default_BT_report.l2cap.CH_ID = L2CAP_ATTRIBUTE_PROTOCOL;
    default_BT_report.att.OPCODE = ATT_HANDLE_VALUE_NOTIFICATION;
}

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER) && defined(AIR_HID_BT_MODE)
void hid_experss_bt_set_attr_handle(uint32_t game_controller)
{
    attr_handle.game_controller = game_controller;
    HID_DBG_LOG(rv_exp, "hid_experss_bt_set_attr_handle game_controller= %d", 1, game_controller);
}
#elif defined(AIR_PRODUCT_TYPE_KEYBOARD) && defined(AIR_HID_BT_MODE)
void hid_experss_bt_set_attr_handle(uint32_t ms, uint32_t kb_std, uint32_t kb_consumer, uint32_t kb_nkey)
{
    attr_handle.ms = ms;
    attr_handle.kb_std = kb_std;
    attr_handle.kb_csm = kb_consumer;
    attr_handle.kb_nkey = kb_nkey;
    HID_DBG_LOG(rv_exp, "hid_experss_bt_set_attr_handle kb_nkey= %d", 1, kb_nkey);
}
#else
void hid_experss_bt_set_attr_handle(uint32_t ms, uint32_t kb_std, uint32_t kb_consumer)
{
    attr_handle.ms = ms;
    attr_handle.kb_std = kb_std;
    attr_handle.kb_csm = kb_consumer;
}
#endif

void hid_experss_bt_clear_queue()
{
    bt_ctrl.front = 0;
    bt_ctrl.rear = 0;
}

void hid_express_bt_debug_check()
{
    bt_debug.drop_data_print = bt_debug.drop_data;
    bt_debug.controller_full_print = bt_debug.controller_full;
    bt_debug.tx_buffer_full_print = bt_debug.tx_buffer_full;
    bt_debug.LC_burst_tx_number_10_print = bt_debug.LC_burst_tx_number_10;
    bt_debug.drop_data = 0;
    bt_debug.controller_full = 0;
    bt_debug.tx_buffer_full = 0;
    bt_debug.LC_burst_tx_number_10 = 0;
}

void hid_express_bt_debug_print()
{
    #if defined (AIR_BT_DATA_MERGE_XY)
    HID_DBG_LOG(rv_exp, "BT mode status merge data = %d, controller full = %d, tx buffer full = %d, LC_burst_tx_number is 10 = %d", 4, bt_debug.drop_data_print, bt_debug.controller_full_print, bt_debug.tx_buffer_full_print, bt_debug.LC_burst_tx_number_10_print);
    #else
    HID_DBG_LOG(rv_exp, "BT mode status drop data = %d, controller full = %d, tx buffer full = %d, LC_burst_tx_number is 10 = %d", 4, bt_debug.drop_data_print, bt_debug.controller_full_print, bt_debug.tx_buffer_full_print, bt_debug.LC_burst_tx_number_10_print);
    #endif
}
// #endif /*  */
#endif /*  */
