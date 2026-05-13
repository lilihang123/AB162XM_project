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

#ifndef _RISCV_MOUSE_KEY_H_
#define _RISCV_MOUSE_KEY_H_

// #if defined( )

/* Includes ------------------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
#define AK_RELEASE 0x00
/* Public typedef ------------------------------------------------------------*/
/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
int riscv_mouse_key_init();
int riscv_mouse_key_get_key_status(uint32_t * outgoing_keys);
void riscv_mouse_key_change_state(uint32_t state);
void riscv_mouse_key_get_combo_key();
void riscv_mouse_key_pairing_key_check();
void riscv_mouse_key_early_handle();
void riscv_mouse_key_debug_print();
void riscv_mouse_key_post_process();

void riscv_mouse_key_set_output_ctrl_pin(uint8_t irpt_pin, uint8_t irpt_type );
void riscv_mouse_key_set_features(uint32_t hid_exp_features);
uint32_t riscv_mouse_key_polling_all_key_status();
uint32_t riscv_mouse_keys_is_new_key_pressed();
uint32_t riscv_mouse_key_id_to_key_status(uint32_t key_id);
void riscv_mouse_key__ccni_send_status(uint32_t new_keys_status);
/** read key status for debounce process only. HID report packaging is not triggered  */
uint32_t riscv_mouse_key_debounce_read();
void riscv_mouse_key__app_state_update(uint32_t new_state);
void riscv_mouse_key_common_para_update();

#if defined(AIR_KEY_SW_DEBOUNCE) || defined(AIR_IRPT_PIN_CTRL)
void riscv_mouse_key__notify_cm33_key_status(uint32_t new_keys_status);
#endif

// #endif /*  */

#endif /* _RISCV_MOUSE_KEY_H_ */
