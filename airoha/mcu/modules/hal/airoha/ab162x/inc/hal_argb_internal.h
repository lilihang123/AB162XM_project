/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
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

#ifndef __HAL_ARGB_INTERNAL_H__
#define __HAL_ARGB_INTERNAL_H__

#include "hal_argb.h"
#include <zephyr/kernel.h>
#ifdef __cplusplus
extern "C" {
#endif

#if defined(HAL_MIDDLE_ARGB_SUPPORTED)

/** @brief ARGB data mode */
typedef enum
{
    BREATH_MODE = 1,    /* breath mode */
    REPEAT_MODE = 2,    /* repeat mode */
    INFINITE_MODE = 3,  /* infinite mode */
} hal_middle_argb_mode_t;

typedef void (*middle_argb_callback_t)(void *user_data);

typedef struct {
    middle_argb_callback_t call_back;      
    void              *user_data;       
} middle_argb_info_t;

hal_argb_status_t hal_argb_init_for_middle(hal_argb_setting *setting, hal_argb_dma_timing_setting *dma_setting);
hal_argb_status_t hal_argb_config_data_mdoe_for_middle(uint8_t index, uint32_t data_size, uint8_t *count_data, hal_middle_argb_mode_t mode);
hal_argb_status_t hal_middle_argb_deinit(void);
hal_argb_status_t hal_middle_argb_stop(void);
hal_argb_status_t hal_middle_argb_start(void);
hal_argb_status_t hal_middle_argb_register_callback(middle_argb_callback_t argb_callback, void *user_data);

#endif

#ifdef __cplusplus
}
#endif

#endif