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
#include "hal_gpt_internal.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if defined(AIR_LATENCY_REPORT)
typedef struct
{
    uint32_t max;       /** max duration */
    uint32_t sum;       /** sum of duration */
    uint32_t cnt;       /** data count */

}T_VARIATION_S;

/** Timeline
 * [risc-v callback]  ---->  [read key] ----->  [submit report to HWMAC]
 * |<------------   process_time   ------------>|
 *                           |<--packing_time-->|
 */
typedef struct
{
    uint32_t ref_timestamp;         /** timestamp of risc-v callback start */
    uint32_t read_key_timestamp;    /** timestamp of read key */
    uint32_t submit_timestamp;      /** timestamp of submit report to HWMAC */
    uint32_t report_ready;          /** flag for report print */
    T_VARIATION_S packing_time;     /** packing time info */
    T_VARIATION_S process_time;     /** process time info */
}T_LATENCY_REPORT_S;

T_LATENCY_REPORT_S  lat_rep;
#endif

/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#if defined(AIR_LATENCY_REPORT)
void rv_latency__accumulate(uint32_t tgt_time, T_VARIATION_S * var)
{
    uint32_t duration;
    
    if (tgt_time){
        hal_gpt_get_duration_count(lat_rep.ref_timestamp, tgt_time, &duration);

        if (var->max < duration ){
            var->max = duration;
        }
        var->sum += duration;
        var->cnt++;
    }
}

uint32_t rv_latency__caculate_avg(uint32_t dividend, uint32_t divisor )
{
    uint32_t tempD = divisor;
    uint32_t quotient = 0;
    uint32_t maxShift = 0;

    if (tempD <= 1){
        // do not wast time to caculate this
        return dividend;
    }

    // find max shift
    while((tempD << 1) <= dividend){
        DBG_PING_H(6);
        tempD <<= 1;
        maxShift++;        
        DBG_PING_L(6);
    }

    // start at the maxShift
    while(maxShift){
        DBG_PING_H(44);
        if (dividend >= (divisor << maxShift)){
            dividend -= (divisor << maxShift);
            quotient += (1<< maxShift);
            // LOG_MSGID_I(rv_exp, "quotient = %d, (1<< maxShift) = %d, maxShift = %d", 3, quotient, (1<< maxShift), maxShift);
        }
        maxShift--;
        DBG_PING_L(44);
    }

    return quotient;
}
#endif

/* Public functions ---------------------------------------------------------*/
#if defined(AIR_LATENCY_REPORT)
void rv_latency__set_ref_time(uint32_t ref_time)
{
    lat_rep.ref_timestamp = ref_time;
}

void rv_latency__read_key_timestamp()
{
    GPT_GET_FREE_RUN_COUNT_US(lat_rep.read_key_timestamp);
}

void rv_latency__submit_to_HWMAC_timestamp(uint32_t submit_time)
{
    lat_rep.submit_timestamp = submit_time;
}

void rv_latency__update(uint32_t report_go)
{
    if (lat_rep.report_ready){
        // report is ready. 
        // waiting for print process, do not update the data
    }
    else {
        if (report_go){
            rv_latency__accumulate(lat_rep.read_key_timestamp, &lat_rep.packing_time);
            rv_latency__accumulate(lat_rep.submit_timestamp  , &lat_rep.process_time);
        }
        else if (lat_rep.packing_time.cnt > 1000){
            // print the report if latency data base is large enough
            lat_rep.report_ready = true;
        }
    }
}

void rv_latency__check_and_print_report(uint32_t report_go)
{
    if (lat_rep.report_ready){
        // DBG_PING_H(45);
        uint32_t avg_packing_time = rv_latency__caculate_avg(lat_rep.packing_time.sum, lat_rep.packing_time.cnt);
        uint32_t avg_process_time = rv_latency__caculate_avg(lat_rep.process_time.sum, lat_rep.process_time.cnt);

        LOG_MSGID_I(rv_exp, "Latency Report: RR = %d, avg_packing_time(cnt, max, avg) = (%0d, %0d, %0d), avg_process_time(cnt, max, avg) = (%0d, %0d, %0d) "
            , 7
            , 125<<hid_common->app.rr.rr_idx_2_4g
            , lat_rep.packing_time.cnt
            , lat_rep.packing_time.max
            , avg_packing_time
            , lat_rep.process_time.cnt
            , lat_rep.process_time.max
            , avg_process_time
            );

        memset(&lat_rep, 0, sizeof(lat_rep));        
        // DBG_PING_H(45);
        lat_rep.report_ready = false;
    }
    
}


#endif