/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWRGBGES AND AGREES
 * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWRGBGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.
 */

#ifndef __BSP_ARGB_H__
#define __BSP_ARGB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hal.h"
#include "hal_argb.h"
#include "argb_control_style_cfg.h"

/** @defgroup bsp_rgb_typedef Typedef
  * @{
  */
/** @brief Callback functioon definition to handle the RGB completed event. */
typedef void(* bsp_argb_callback_t)(void *user_data);
/**
* @}
*/
typedef enum {
    BSP_ARGB_STATUS_ERROR_BUSY          = -5,
    BSP_ARGB_STATUS_ERROR_NO_DEVICE     = -4,
    BSP_ARGB_STATUS_ERROR_CHANNEL       = -3,       /**< The ISINK error channel. */
    BSP_ARGB_STATUS_ERROR_INVALID_PARAMETER   = -2, /**< An error occurred, invalid parameter was given. */
    BSP_ARGB_STATUS_ERROR               = -1,        /**< The ISINK function error occurred. */
    BSP_ARGB_STATUS_OK   = 0                         /**< The ISINK operation completed successfully.*/
} bsp_argb_status_t;


typedef struct {
    uint32_t gpio_channel;
    uint32_t one_h_value;
    uint32_t one_l_value;
    uint32_t zero_h_value;
    uint32_t zero_l_value;
    uint32_t reset_value;
    uint8_t pat_cnt;
    uint8_t bit_nonrev;
    uint8_t ed_big;
    uint8_t nonalign;
    uint32_t auto_timer_val;
    uint32_t pre_wake_val;
    uint32_t dma_start_val;
    bsp_argb_callback_t callback;
    void *user_data;
} argb_para_t;


bsp_argb_status_t bsp_argb_enable(void);

bsp_argb_status_t bsp_argb_disable(void);

bsp_argb_status_t bsp_argb_register_isr(bsp_argb_callback_t callback, void *user_data);

bsp_argb_status_t bsp_argb_realtime_enable(argb_style_config_t *cfg, uint8_t interval);

bsp_argb_status_t bsp_argb_realtime_config(argb_style_config_t *cfg);

bsp_argb_status_t bsp_argb_realtime_start(void);

#ifdef __cplusplus
}
#endif

#endif