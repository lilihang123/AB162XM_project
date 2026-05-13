/* Copyright Statement:
 *
 * (C) 2005-2017 MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. ("MediaTek") and/or its licensors.
 * Without the prior written permission of MediaTek and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) MediaTek Software
 * if you have agreed to and been bound by the applicable license agreement with
 * MediaTek ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User"). If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */

#ifndef __HAL_SLEEPMANAGER_H__
#define __HAL_SLEEPMANAGER_H__
#include "hal_platform.h"
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"

#ifdef HAL_SLEEP_MANAGER_ENABLED

typedef enum {
    HAL_SLEEP_MANAGER_ERROR                           = -1,    /**< An undefined error occurred. */
    HAL_SLEEP_MANAGER_OK                              = 0,     /**< The operation completed successfully. */
} hal_sleep_manager_status_t;

uint32_t hal_sleep_manager_set_sleep_time_rtc(uint32_t sleep_time_ms);
void hal_sleep_manager_sw_gpt_callback_rtc(void);
uint8_t hal_sleep_manager_set_sleep_handle(const char *handle_name);
hal_sleep_manager_status_t hal_sleep_manager_lock_sleep(uint8_t handle_index); /* TODOs: check code in RAM? */
hal_sleep_manager_status_t hal_sleep_manager_unlock_sleep(uint8_t handle_index);
hal_sleep_manager_status_t hal_sleep_manager_release_sleep_handle(uint8_t handle_index);
bool hal_sleep_manager_is_sleep_handle_alive(uint8_t handle_index);
uint32_t hal_sleep_manager_get_lock_status(void);
bool hal_sleep_manager_is_sleep_locked(void);
void hal_sleep_manager_riscv_sleep_routine(void);
hal_sleep_manager_status_t hal_sleep_manager_init(void);

#ifdef __cplusplus
}
#endif

/**
* @}
* @}
*/

#endif /*HAL_SLEEP_MANAGER_ENABLED*/
#endif /*__HAL_SPM_SLEEMANGER_INTERNAL_H__*/

