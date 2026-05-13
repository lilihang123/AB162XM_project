/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
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

#ifndef __APP_HID_PLC_UTIL_H__
#define __APP_HID_PLC_UTIL_H__

#include "bt_ull_le_hid_service.h"

#define APP_HID_DATA_NUM 11

typedef uint8_t hid_plc_status;
#define APP_HID_PLC_SUCCESS          0
#define APP_HID_PLC_ONE_POINT        1
#define APP_HID_PLC_TWO_POINT        2
#define APP_HID_PLC_CORRECT          3
#define APP_HID_PLC_CORRECT_ZERO     4
#define APP_HID_PLC_FAIL             5

typedef uint8_t hid_plc_reason_t;
#define HID_PLC_REASON_RX_SUCCEESS              0x00
#define HID_PLC_REASON_RX_FAIL                  0x01
#define HID_PLC_REASON_LEC_U_PKT                0x02 /* useless packets in LEC format that are not expected to appear in HID scenarios */
#define HID_PLC_REASON_NULL_PKT                 0x03 /* empty packet */
#define HID_PLC_REASON_STOP_PLC                 0x04 /* two consecutive empty packets( the accumulated amount of PLCs will be cleared ) */
#define HID_PLC_REASON_DUP_PKT                  0x05 /* Duplicated data */
#define HID_PLC_REASON_WBPLC_2RX                0x06 /* WB scan PLC needed in 1st and 2nd RX */
#define HID_PLC_REASON_RXOK_WB_PLC              0x07 /* WB scan PLC needed in 2nd RX */

typedef uint8_t hid_plc_line_type;
#define APP_HID_PLC_DEFAULT_LINE_TYPE          1<<0
#define APP_HID_PLC_STAIGHT_LINE_TYPE          1<<1
#define APP_HID_PLC_CONSTANT_RATE_TYPE         1<<2
#define APP_HID_PLC_VARIABLE_RATE_TYPE         1<<3

typedef uint8_t plc_revise_state_t;
#define PLC_REVISE_STATE_NONE      0
#define PLC_REVISE_STATE_FINISH    1
#define PLC_REVISE_STATE_NEED_TODO 2
#define PLC_REVISE_STATE_NOT_PLC   3

typedef struct{
    uint8_t  last_useful_data_num;
    uint8_t  trend_num_x;
    uint8_t  trend_num_y;
    hid_plc_line_type  line_type;
    uint8_t  lose_point_num;
    uint8_t  zero_num;
    int32_t  remainder_x;
    int32_t  remainder_y;
    int32_t average_value_x;
    int32_t average_value_y;
    uint32_t deviation_x;
    uint32_t deviation_y;
} point_charcter;

typedef struct{
    bool fake; /* 1:fake data; 0: real data */
    bool correct;
    bool accumulate;
    bool useful_flag_x;
    bool useful_flag_y;
    int32_t x;
    int32_t y;
    int32_t char_out_x;
    int32_t char_out_y;
    point_charcter hid_data_char;
} point;

typedef struct{
    plc_revise_state_t revise_state;
    int8_t read_index; //ring buffer
    int8_t write_index; //ring buffer
    bool duplicate_flag; // duplicate flag, 0: no duplicate, 1: duplicate
    bool predict_nack_flag;  // predict nack flag, 0: predict nack packet clear, 1: predict nack packet set
    bool predict_revise_flag; // predict revise flag, 0: predict revise clear, 1: predict revise set
    int32_t predict_x; // predict_point x
    int32_t predict_y; // predict point y
    point hid_data[APP_HID_DATA_NUM];
} hid_plc_t;

typedef struct{
    bool channel;
    bool correct;
    bool accumulate;
    hid_plc_reason_t reason;
    bt_ull_le_hid_srv_report_rate_level_t report_rate;
    int32_t x;
    int32_t y;
} hid_plc_param_t;

#endif
