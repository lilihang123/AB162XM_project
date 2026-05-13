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

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#ifdef HAL_HW_KEYSCAN_MODULE_ENABLED
#include "hw_keyscan.h"

hw_keyscan_status_t hw_keyscan_init(hw_keyscan_config_t *keyscan_config)
{
    hal_hw_keyscan_status_t ret;
    hal_hw_keyscan_config_t *hal_keyscan_config = (hal_hw_keyscan_config_t *)keyscan_config;
    ret = hal_hw_keyscan_init(hal_keyscan_config);
    return (hw_keyscan_status_t)ret;
}

hw_keyscan_status_t hw_keyscan_deinit(void)
{
    hal_hw_keyscan_status_t ret;
    ret = hal_hw_keyscan_deinit();
    return (hw_keyscan_status_t)ret;
}

hw_keyscan_status_t hw_keyscan_register_callback(hw_keyscan_callback_t callback)
{
    hal_hw_keyscan_status_t ret;
    hal_hw_keyscan_callback_t hal_callback = (hal_hw_keyscan_callback_t)callback;
    ret = hal_hw_keyscan_register_callback(hal_callback);
    return (hw_keyscan_status_t)ret;
}

hw_keyscan_status_t hw_keyscan_enable(void)
{
    hal_hw_keyscan_status_t ret;
    ret = hal_hw_keyscan_enable();
    return (hw_keyscan_status_t)ret;
}

hw_keyscan_status_t hw_keyscan_disable(void)
{
    hal_hw_keyscan_status_t ret;
    ret = hal_hw_keyscan_disable();
    return (hw_keyscan_status_t)ret;
}

void hw_keyscan_sw_trigger(void)
{
    hal_hw_keyscan_sw_trigger();
}

void hw_keyscan_align_bt_trigger_set_enable(bool bt_trigger_enable)
{
    hal_hw_keyscan_align_bt_trigger_set_enable(bt_trigger_enable);
}


#endif /*   HAL_HW_KEYSCAN_MODULE_ENABLED   */