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
#if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP) || defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#if defined(CONFIG_AIR_KEY_REMAP_BACKEND_CM33) || defined(AIR_KEY_REMAP_BACKEND_RISCV)
#ifndef _KEY_REMAP_BACKEND_H_
#define _KEY_REMAP_BACKEND_H_

#include "key_remap_queue.h"

#define STD_KB_NUM   5
#define CSM_KB_NUM   2

typedef enum {
    NONE,
    MACRO_START,
    MACRO_STOP,
    MACRO_STOP_TO_RESTART,
    MACRO_RESTART,
} T_MACRO_STATUS_E;

typedef enum {
    STATUS_NONE,
    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    SWITCH_RR,
    SWITCH_DPI,
    SWITCH_DPI_STOP,
    FN_KEY_DPI_SWITCH,
    PRESS_PAIRING_KEY,
    UPDATE_PAIRING_KEY,
    WHEEL_PAIRING_KEY,
    #elif defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    PRESSED_LEFT_SENITIVITY = 0x01,
    PRESSED_RIGHT_SENITIVITY = 0x02,
    MACRO_PROCESS = 0x04,
    #endif
} T_POST_PROCESS_STATUS_E;

void key_remap_backend_setting();
void key_remap_backend_process();
uint32_t key_remap_get_process_status();
uint32_t key_remap_get_dpi_attr();
void key_remap_state_reset();
void key_remap_backend_init();
void key_remap_backend_postprocess();
#if defined(AIR_WHEEL_REMAP)
void key_remap_update_key_status(uint32_t new_key, int new_z1);
#else
void key_remap_update_key_status(uint32_t new_key);
#endif
void key_remap_backend_deinit();
uint32_t key_remap_get_key_status(uint32_t *key_status);
void key_remap_set_queue(T_REMAP_QUEUE_CTRL_S *q_Ctrl);
#endif /* _KEY_REMAP_BACKEND_H_ */
#endif /* CONFIG_AIR_KEY_REMAP_BACKEND_CM33, AIR_KEY_REMAP_BACKEND_RISCV */
#endif /* AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP, CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */