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
#include "riscv_hid_express.h"
#include "pka.h"
#include "rv_burst_tx_buf_ctrl.h"
/* Private define ------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/



/* Private variables ---------------------------------------------------------*/
static uint32_t LC_ReTx_times = 0;
static uint32_t LC_traffic_statistic_counter = 0;
#if defined(AIR_PRODUCT_TYPE_MOUSE)
static uint8_t last_ms_key = 0;
#endif
/* Public variables ----------------------------------------------------------*/
uint32_t LC_burst_tx_number = LC_BURST_TX_PKT_NUM_MIN;
uint32_t outgoing_buffer_avail = LC_BURST_TX_PKT_NUM_MIN;
extern T_BT_DEBUG_S bt_debug;
extern T_ATT_ATTRIBUTE_HANDLE_S attr_handle;
/* Private functions ---------------------------------------------------------*/







/* Public functions ---------------------------------------------------------*/
uint32_t rv_bt_burst_tx_num_ctrl(T_BT_HID_REPORT_S *report, uint32_t buf_avail_num)
{
    uint32_t LC_queued_tx_pkt_num = PKA_TX_BUF_HID_NUM_LE - buf_avail_num;
    outgoing_buffer_avail = LC_burst_tx_number;

    if(LC_queued_tx_pkt_num && LC_queued_tx_pkt_num != PKA_TX_BUF_HID_NUM_LE)
    {
        LC_queued_tx_pkt_num--;
    }
    else if(LC_queued_tx_pkt_num == PKA_TX_BUF_HID_NUM_LE)
    {
        // HID_DBG_LOG(rv_exp, "bt_tx_buffer is NULL" , 0);
        return 0;
    }

    // HID_DBG_LOG(rv_exp, "LC_queued_tx_pkt_num = %d" , 1, LC_queued_tx_pkt_num);
    
    #if defined(AIR_BASIC_LA_DEBUG)
    uint32_t temp = LC_queued_tx_pkt_num;
    while(temp--)
    {
        DBG_PING_L(DBG_SIGNAL_DEBUG_1);
        DBG_PING_H(DBG_SIGNAL_DEBUG_1);
    }
    #endif

    if(LC_queued_tx_pkt_num >= LC_BURST_TX_PKT_NUM_MIN)
    {
        LC_ReTx_times++;
    }

    if (LC_queued_tx_pkt_num >= LC_burst_tx_number)
    {
        /* only X/Y has new data, so can drop it */
        #if defined(AIR_PRODUCT_TYPE_MOUSE)
        if ((last_ms_key == report->ms_hid.k) && (report->ms_hid.z1 == 0) && (report->att.ATTRIBUTE_HANDLE == attr_handle.ms))
        {
            outgoing_buffer_avail = 0;
        }
        else
        #endif
        {
            outgoing_buffer_avail = buf_avail_num;
        }
    }

    /* Check LC trafic status */
    LC_traffic_statistic_counter++;
    if(LC_traffic_statistic_counter >= LC_TRAFFIC_STATISTIC_PERIOD)
    {
        if (LC_ReTx_times >= LC_TRAFFIC_POOR_THRESHOLD)
        {
            /* Extend LC MD limination */
            LC_burst_tx_number = LC_BURST_TX_PKT_NUM_MAX;
            bt_debug.LC_burst_tx_number_10++;
        }
        else
        {
            LC_burst_tx_number = LC_BURST_TX_PKT_NUM_MIN;
        }

        // HID_DBG_LOG(rv_exp, "LC_ReTx_times = %d, LC_burst_tx_number = %d" , 2, LC_ReTx_times, LC_burst_tx_number);
        LC_traffic_statistic_counter = 0;
        LC_ReTx_times = 0;
    }

    if(LC_burst_tx_number > LC_queued_tx_pkt_num && (outgoing_buffer_avail != 0))
    {
        if((LC_burst_tx_number == LC_BURST_TX_PKT_NUM_MAX) && (LC_queued_tx_pkt_num == (PKA_TX_BUF_HID_NUM_LE - 2)))
        {
            /* When buffer num is 10, and pkt num is 8 now, need to add 1, buffer avail num is 1 */
            LC_queued_tx_pkt_num++;
        }
        outgoing_buffer_avail = LC_burst_tx_number - LC_queued_tx_pkt_num;
    } 

    // HID_DBG_LOG(rv_exp, "LC_queued_tx_pkt_num = %d,  outgoing_buffer_avail = %d" , 2, LC_queued_tx_pkt_num,  outgoing_buffer_avail);
    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    last_ms_key = report->ms_hid.k;
    #endif

    return outgoing_buffer_avail;
}
#endif /*  */