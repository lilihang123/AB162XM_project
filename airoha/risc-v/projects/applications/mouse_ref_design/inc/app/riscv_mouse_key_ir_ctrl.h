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

#ifndef _RISCV_MOUSE_KEY_IR_CTRL_H_
#define _RISCV_MOUSE_KEY_IR_CTRL_H_
#if defined(AIR_IRPT_PIN_CTRL)

/* Includes ------------------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
#define IRPT_ON_TIME                        20      // 18us

#define IRPT_INTERVAL_AT_IDLE_STATE         5000    // 5000us



/* Public typedef ------------------------------------------------------------*/
/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
extern bool IR_LED_status_on;
extern uint32_t protect_cnt;


/* Public functions ----------------------------------------------------------*/


uint32_t riscv_mkey_ir_ctrl_delay(uint32_t duration);
void riscv_mkey_ir_ctrl_on();
void riscv_mkey_ir_ctrl_off();
void riscv_mkey_ir_ctrl_init();

/** request to turn on IR according to next_read_key_time  in time */
void riscv_mkey_ir_ctrl_post_process(uint32_t next_read_key_time);
void riscv_mkey_ir_ctrl_idle_state_handler();
void riscv_mkey_ir_ctrl_disconnected_state_handler();
void  riscv_mkey_ir_ctrl__app_state_update(uint32_t new_state);
void riscv_mkey_ir_ctrl_debug_print();
uint32_t riscv_mkey_ir_ctrl__ir_key_check(uint32_t ir_status, uint32_t key_status, uint32_t old_key_status );


#endif /* AIR_IRPT_PIN_CTRL */
#endif /* _RISCV_MOUSE_KEY_IR_CTRL_H_ */
