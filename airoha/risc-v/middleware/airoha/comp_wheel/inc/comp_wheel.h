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

#ifndef __COMP_WHEEL_H__
#define __COMP_WHEEL_H__

#include "hal_platform.h"
#include "hal_comparator.h"
#include "hal_gpt.h"
#include "hal_gpt_internal.h"
#include "hal_gpio.h"
#include "hal_gpio_internal.h"

typedef enum
{
    COMP_WHEEL_STATUS_ERROR_INVALID_PARAMETER = -2, /**< The COMP_WHEEL encoder parameter error. */
    COMP_WHEEL_STATUS_ERROR = -1,                   /**< The COMP_WHEEL encoder status error. */
    COMP_WHEEL_STATUS_OK = 0                        /**< The COMP_WHEEL encoder status OK. */
} riscv_comp_wheel_status_t;

typedef void (*riscv_comp_wheel_callback_t)(int16_t wheel_data);

typedef struct
{
    uint32_t scan_cycle_us;
    hal_gpio_pin_t pin_led;
    hal_gpio_pin_t pina;
    hal_gpio_pin_t pinb;
    hal_gpio_data_t pina_state;
    hal_gpio_data_t pinb_state;
    int32_t relative_position;
    uint8_t pc_state;  /**< Including previous and current status of the pinA and pinB. */
    uint8_t dpc_state; /**< Including double previous and current status of the pinA and pinB. */
    riscv_comp_wheel_callback_t callback;
} risvc_comp_wheel_info_t;

typedef struct
{
    hal_gpio_pin_t pin_led;
    hal_comp_gpio_cfg_t up_pin;
    hal_comp_gpio_cfg_t down_pin;
}riscv_comp_wheel_config_t;

riscv_comp_wheel_status_t comp_wheel_init(riscv_comp_wheel_config_t *config , riscv_comp_wheel_callback_t callback);
void comp_wheel_deinit(void);
void comp_wheel_scan_once(uint16_t delay_us);

#endif/*__COMP_WHEEL_H__*/