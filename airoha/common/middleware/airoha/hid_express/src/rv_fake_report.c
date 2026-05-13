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


#if defined (AIR_FAKE_REPORT)
#include "stdio.h"
#include "stdint.h"

#include "riscv_hid_express.h"
#include "rv_fake_report.h"


uint32_t fake_report_idx=0;
uint32_t fake_report_rounds=0xFFFFFFFF;
uint32_t fake_report_rounds_counter=0xFFFFFFFF;
uint32_t fake_report_offset_cnt = 0;
uint32_t fake_report_pattern = 0;
uint32_t fake_report_size = 0;
const T_SENSOR_DATA_SMALL_S * fake_report_data;
T_SENSOR_DATA_SMALL_S curr_data;


int rv_fake_report_config(uint32_t enable, uint32_t pattern, uint32_t rounds)
{
    LOG_MSGID_I(rv_exp, "rv_fake_report_config  enable =%d, pattern = %d,   rounds = %d"
        , 3
        , enable
        , pattern
        , rounds
        );

    if (enable) // true
    {
        fake_report_pattern  = pattern;

        if (pattern == 0 ){
            fake_report_size = 1000;
        }
        else {
            fake_report_size = 100;
        }

        fake_report_rounds = rounds;

        fake_report_idx = 0;
        fake_report_rounds_counter = 0;
        fake_report_offset_cnt = 0;
    }
    else
    {
        fake_report_rounds = 0xFFFFFFFF;
        fake_report_rounds_counter = fake_report_rounds;
    }
    curr_data.sensor_x = 0;
    curr_data.sensor_y = 0;

    return 0;
}


void rv_fake_report_fake_report(T_OUTGOING_VALUES_S * outgoing )
{
    if (fake_report_rounds > fake_report_rounds_counter ||  fake_report_rounds == 0) {
        #if defined(IGNORE_SENSOR_DATA_IN_FAKE_REPORT)
        outgoing->x = curr_data.sensor_x;
        outgoing->y = curr_data.sensor_y;
        #else
        outgoing->x += curr_data.sensor_x;
        outgoing->y += curr_data.sensor_y;
        #endif

        fake_report_idx++;

        if (fake_report_idx >= fake_report_size ){
            // Single round is completed. clear the index and go next round if needed
            fake_report_idx=0;
            fake_report_rounds_counter++;
        }
    }
}

void rv_fake_report_post_process()
{
    if (fake_report_rounds > fake_report_rounds_counter ||  fake_report_rounds == 0) {
        curr_data.sensor_x = fake_report_data[fake_report_idx].sensor_x;
        curr_data.sensor_y = fake_report_data[fake_report_idx].sensor_y;
    }
}

void rv_fake_report_set(uint32_t *fake_data)
{
    fake_report_data = (T_SENSOR_DATA_SMALL_S *)fake_data;
}

bool rv_fake_report_get_report_status()
{
    if(fake_report_rounds == 0xFFFFFFFF){
        return false;
    }
    return true;
}

uint32_t rv_fake_report__get_state()
{
    if(fake_report_rounds == 0xFFFFFFFF){
        return FAKE_REPORT_DISABLED;
    }
    else if ((fake_report_rounds <= fake_report_rounds_counter) && fake_report_rounds){
        // specified rounds have been completed, disable fake report nvkey
        return FAKE_REPORT_COMPLETED;

    }
    return FAKE_REPORT_RUNNING;
}


#endif