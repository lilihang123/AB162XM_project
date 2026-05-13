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

#if defined(AIR_PRODUCT_TYPE_MOUSE)

/* Includes ------------------------------------------------------------------*/
#include "riscv_hid_express_xy_queue.h"
#include "pka.h"

/* Private define ------------------------------------------------------------*/



/* Private typedef -----------------------------------------------------------*/


#define NAK    1  // Not Acked packet
#define ACK    0  // Acked packet


/* Private macro -------------------------------------------------------------*/
T_ASSEMBLE_VAL_CTRL_S vCtrl_x;
T_ASSEMBLE_VAL_CTRL_S vCtrl_y;

/* Private variables ---------------------------------------------------------*/



/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ---------------------------------------------------------*/


/**  For USB mode, tx_result can be received immediately
 * 1R1T : value_n : value_0 
 *        value_predict_case_n : value_predict_case_0, (Nack) 
 *                               value_predict_case_1  (Ack)
*/
void hid_express_generate_value_candidate(T_ASSEMBLE_VAL_CTRL_S  * vctrl, uint32_t tx_result, int32_t value_new )
{
    vctrl->predict_n[ACK] = value_new;
    vctrl->predict_n[NAK] = value_new + vctrl->tx_n[0];

    // update the value of last tx_0 according to tx_result
    vctrl->tx_n[0] = vctrl->predict_n[tx_result];
}

/**
 * 1R1T : value_n : value_0 
 *        value_predict_case_n : value_predict_case_0, (Nack) 
 *                               value_predict_case_1  (Ack)
*/
void hid_express_generate_value_candidate_1R1T_concurrent(T_ASSEMBLE_VAL_CTRL_S  * vctrl, uint32_t tx_result, int32_t value_new )
{
    // update the value of last tx_0 according to tx_result
    vctrl->tx_n[0] = vctrl->predict_n[tx_result];

    if (tx_result){
        vctrl->predict_n[ACK] = value_new + vctrl->predict_n[0];
    }
    else {
        vctrl->predict_n[ACK] = value_new;
    }

    vctrl->predict_n[NAK] = vctrl->tx_n[0];
}

/* Check if buffer has the value to be transmitted */
uint32_t hid_express_x_y_buf_has_data()
{
    if(vCtrl_x.predict_n[0] || vCtrl_x.predict_n[1]
      || vCtrl_y.predict_n[0] || vCtrl_y.predict_n[1])
    {
        return true;
    }
    return false;
}

void hid_express_x_y_buf_init(T_ASSEMBLE_VAL_CTRL_S **vctrl_x, T_ASSEMBLE_VAL_CTRL_S **vctrl_y)
{
    *vctrl_x = &vCtrl_x;
    *vctrl_y = &vCtrl_y;
    memset(&vCtrl_x, 0, sizeof(vCtrl_x));
    memset(&vCtrl_y, 0, sizeof(vCtrl_y));
}
#endif /* AIR_PRODUCT_TYPE_MOUSE */
