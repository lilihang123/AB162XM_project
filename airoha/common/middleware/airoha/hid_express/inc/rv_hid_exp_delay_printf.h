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


#ifndef __RISCV_HID_EXP_DELAY_PRINTF__
#define __RISCV_HID_EXP_DELAY_PRINTF__

#include "pka.h"

#define HID_EXP_DELAY_PRINTF
#if defined(HID_EXP_DELAY_PRINTF)
typedef struct
{
    uint32_t wheel_ok;
    uint32_t sensor_ok;
    uint32_t total_cnt;
    uint32_t sampling_cnt;
    uint32_t timestamp;
    uint32_t nack_count;
    uint32_t motion_pin_cnt;
    uint32_t valid_key_cnt;
    uint32_t pka_hid_drop_cnt;
    uint32_t pka_hid_cnt;
    uint32_t pka_acl_cnt;
    uint32_t all_buff_full_cnt;

    #if defined(HID_EXP_PROCESS_TIME_MONITOR)
    uint32_t data_for_write[STATUS_REP_ID_MAX];
    uint16_t data_for_print[STATUS_REP_ID_MAX];
    #endif

    uint16_t wheel_ok_4print;
    uint16_t waiting_4print;
    uint16_t sensor_ok_4print;
    uint16_t sampling_cnt_4print;
    uint16_t pka_hid_drop_cnt_4print;
    uint16_t pka_hid_cnt_4print;
    uint16_t pka_acl_cnt_4print;
    uint16_t total_cnt_4print;
    uint16_t nack_count_4print;
    uint16_t motion_pin_low_4print;
    uint16_t valid_key_cnt_4print;
}T_SENSOR_DATA_STATISTICS_S;

extern T_SENSOR_DATA_STATISTICS_S dbg;

void hid_express_dbg_check();
void rv_hid_exp_delay_printf();


#endif /** HID_EXP_DELAY_PRINTF*/

#endif /**__RISCV_HID_EXP_DELAY_PRINTF__ */
