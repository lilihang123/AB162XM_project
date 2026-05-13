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

#ifndef _RISCV_HID_EXPRESS_XY_QUEUE_H_
#define _RISCV_HID_EXPRESS_XY_QUEUE_H_

#if defined(AIR_PRODUCT_TYPE_MOUSE)

#include "riscv_hid_express.h"

#define REASSEMBLE_MEMORY_NOT_INITIALIZED   0
#define REASSEMBLE_MEMORY_INITIALIZED   1

#define TX_TYPE_1R1T 0
#define TX_TYPE_1R2T 1

#define TX_NUM_1R1T  (TX_TYPE_1R1T + 1) // 1
#define TX_NUM_1R2T  (TX_TYPE_1R2T + 1) // 2

#define CANDIDATE_NUM_1R1T  (1 << TX_NUM_1R1T)  // 2
#define CANDIDATE_NUM_1R2T  (1 << TX_NUM_1R2T)  // 4


typedef struct {
    int32_t tx_n[1];                /** value of transmitted tx_0*/
    int32_t predict_n[2];           /** value of predict_0 (Ack), predict_1 (Nack)*/
    int32_t untransmitted_value;    /** value of untransmitted*/

}T_ASSEMBLE_VAL_CTRL_S; 

void hid_express_x_y_buf_init(T_ASSEMBLE_VAL_CTRL_S **vctrl_x, T_ASSEMBLE_VAL_CTRL_S **vctrl_y);
uint32_t hid_express_x_y_buf_has_data();
void hid_express_generate_value_candidate(T_ASSEMBLE_VAL_CTRL_S  * vctrl, uint32_t tx_result, int32_t value_new );
void hid_express_generate_value_candidate_1R1T_concurrent(T_ASSEMBLE_VAL_CTRL_S  * vctrl, uint32_t tx_result, int32_t value_new );
void hid_express_generate_value_candidate_1R1T_one_by_one(T_ASSEMBLE_VAL_CTRL_S  * vctrl, uint32_t tx_result, int32_t value_new );
#endif /* AIR_PRODUCT_TYPE_MOUSE */

#endif /* _RISCV_HID_EXPRESS_XY_QUEUE_H_ */
