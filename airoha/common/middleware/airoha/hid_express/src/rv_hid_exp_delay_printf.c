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



#include "stdio.h"
#include "stdint.h"


#include "riscv_hid_express.h"
#include "rv_hid_exp_delay_printf.h"
#include "hal_gpt_internal.h"
#include "riscv_hid_express_2_4G_mode.h"
#include "riscv_hid_express_bt_mode.h"
#include "assert.h"



T_SENSOR_DATA_STATISTICS_S dbg;



void hid_express_dbg_inc_pka_hid_cnt()
{
    dbg.pka_hid_cnt++;
}

void hid_express_dbg_inc_pka_acl_cnt()
{
    dbg.pka_acl_cnt++;
}

void hid_express_dbg_inc_pka_hid_drop_cnt()
{
    dbg.pka_hid_drop_cnt++;
}

void hid_express_dbg_check()
{
    dbg.total_cnt++;

    uint32_t current_gpt_free_count;
    uint32_t time_delta;
    GPT_GET_FREE_RUN_COUNT_US(current_gpt_free_count);
    hal_gpt_get_duration_count(dbg.timestamp, current_gpt_free_count, &time_delta);

    if( time_delta > (1000000-(125/2)) ){
        dbg.waiting_4print = true;
        dbg.wheel_ok_4print = dbg.wheel_ok;
        dbg.total_cnt_4print = dbg.total_cnt;
        dbg.sensor_ok_4print = dbg.sensor_ok;
        dbg.sampling_cnt_4print = dbg.sampling_cnt;
        dbg.nack_count_4print = dbg.nack_count;
        dbg.motion_pin_low_4print = dbg.motion_pin_cnt;
        dbg.valid_key_cnt_4print = dbg.valid_key_cnt;
        dbg.pka_hid_drop_cnt_4print = dbg.pka_hid_drop_cnt;
        dbg.pka_hid_cnt_4print = dbg.pka_hid_cnt;
        dbg.pka_acl_cnt_4print = dbg.pka_acl_cnt;

        dbg.wheel_ok = 0;
        dbg.total_cnt = 0;
        dbg.sensor_ok = 0;
        dbg.sampling_cnt = 0;
        dbg.nack_count = 0;
        dbg.motion_pin_cnt = 0;
        dbg.valid_key_cnt = 0;
        dbg.pka_hid_drop_cnt = 0;
        dbg.pka_hid_cnt = 0;
        dbg.pka_acl_cnt = 0;
        dbg.timestamp = current_gpt_free_count;
        #if defined (AIR_HID_BT_MODE)
        if(BT_DATA_GO(hid_flags)){
            hid_express_bt_debug_check();
        }
        #endif
    }
}

void rv_hid_exp_delay_printf()
{
    #define SPI_BUS_AND_IRQ_TIME (23)
    #define COMPASATION_TIME (13 + SPI_BUS_AND_IRQ_TIME)

    if(dbg.waiting_4print){
        //DBG_LATENCY_L(DBG_SIGNAL_USB_TX_DONE);
        LOG_MSGID_I(rv_exp, "Common HID Exp Status Report: Key = %d,  Wheel = %d, Nack = %d, Motion Count = %d, Motion Pin Low = %d, Sampling Count = %d, SPI CB in 1s = %d, RR_idx = %d (0=125, 3=1K, 6=8k)"
            , 8
            , dbg.valid_key_cnt_4print
            , dbg.wheel_ok_4print
            , dbg.nack_count_4print
            , dbg.sensor_ok_4print
            , dbg.motion_pin_low_4print
            , dbg.sampling_cnt_4print
            , dbg.total_cnt_4print
            , hid_ctrl.rr_idx
            );

       LOG_MSGID_I(rv_exp, "Common HID PKA Status Report: PkaHidDrop = %d, PkaHid = %d, PkaAcl = %d"
            , 3
            , dbg.pka_hid_drop_cnt_4print
            , dbg.pka_hid_cnt_4print
            , dbg.pka_acl_cnt_4print
            );

        if(GAMING_DATA_GO(hid_flags)){
            if(dbg.nack_count_4print == dbg.total_cnt_4print){
                dbg.all_buff_full_cnt++;
                if(dbg.all_buff_full_cnt == 2)
                {
                    assert(0 && "Always buffer full within 2 seconds");
                }
            }
            else{
                dbg.all_buff_full_cnt = 0;
            }
        }
        
        #if defined (AIR_HID_BT_MODE)
        if(BT_DATA_GO(hid_flags)){
            hid_express_bt_debug_print();
        }
        #endif
        //DBG_LATENCY_H(DBG_SIGNAL_USB_TX_DONE);
        dbg.waiting_4print = false;

    }
}
