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

#ifndef __HAL_SLEEPMANAGER_INTERNAL_H__
#define __HAL_SLEEPMANAGER_INTERNAL_H__
#include "hal_platform.h"
#include "hal_sleep_manager_platform.h"
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"

#ifdef HAL_SLEEP_MANAGER_ENABLED

typedef enum {
    UNLOCK_SLEEP    = 0,
    LOCK_SLEEP      = 1
} sleep_management_lock_sleep_t;

typedef enum {
    UNLOCK_EXTSLP    = 0,
    LOCK_EXTSLP      = 1
} sleep_management_lock_extslp_t;

typedef enum {
    SLEEP_MANAGEMENT_UNINITIALIZED  = 0,
    SLEEP_MANAGEMENT_INITIALIZED    = 1
} sleep_management_init_status_t;

/* Lock Sleep Handle ID : 0~49 */
#define  SLEEP_LOCK_HANDLE_MAX                50
#define  SLEEP_LOCK_HANDLE_USER_MAX           (SLEEP_LOCK_HANDLE_MAX-SLEEP_LOCK_USER_START_ID)
#define  SLEEP_HANDLE_NAME_LEN                11

typedef struct {
    uint64_t    lock_sleep_request;
    uint32_t    user_handle_resoure;
    uint8_t     user_handle_count;
    uint8_t     lock_sleep_request_count[SLEEP_LOCK_HANDLE_MAX];
    uint8_t     user_handle_name[SLEEP_LOCK_HANDLE_USER_MAX][SLEEP_HANDLE_NAME_LEN];
} sleep_management_handle_t;

typedef void(* sleep_management_suspend_callback_t)(void *data);
typedef void(* sleep_management_resume_callback_t)(void *data);

typedef struct {
    sleep_management_suspend_callback_t func;
    void *data;
    bool init_status;
} sleep_management_suspend_callback_func_t;

typedef struct {
    sleep_management_resume_callback_t func;
    void *data;
    bool init_status;
} sleep_management_resume_callback_func_t;

void sleep_management_register_suspend_callback(sleep_management_backup_restore_module_t module, sleep_management_suspend_callback_t callback, void *data);
void sleep_management_register_resume_callback(sleep_management_backup_restore_module_t module, sleep_management_resume_callback_t callback, void *data);
void sleep_management_suspend_callback(void);
void sleep_management_resume_callback(void);

void sleep_management_enter_sleep(void);
void sleep_management_enter_deep_sleep(void);

uint8_t sleep_management_get_lock_handle(const char *handle_name);
void sleep_management_release_lock_handle(uint8_t handle_index);
void sleep_management_lock_sleep(sleep_management_lock_sleep_t lock, uint8_t handle_index);
bool sleep_management_check_sleep_locks(void);
bool sleep_management_check_handle_status(uint8_t handle_index);
uint64_t sleep_management_get_lock_sleep_handle_list(void);
uint64_t sleep_management_get_lock_sleep_request_info(void);
uint8_t sleep_management_get_lock_extslp_handle(const char *handle_name);
void sleep_management_release_lock_extslp_handle(uint8_t handle_index);
void sleep_management_lock_extslp(sleep_management_lock_extslp_t lock, uint8_t handle_index);
bool sleep_management_check_extslp_locks(void);
bool sleep_management_check_request_extslp_status();

#ifdef __cplusplus
}
#endif

/**
* @}
* @}
*/

#endif /*HAL_SLEEP_MANAGER_ENABLED*/
#endif /*__HAL_SPM_SLEEMANGER_INTERNAL_H__*/

