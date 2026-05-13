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

#ifndef _APP_JOYSTICK_AND_TRIGGER_H_
#define _APP_JOYSTICK_AND_TRIGGER_H_

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
typedef struct {
    uint32_t min_voltage; /* uint: uV */
    uint32_t max_voltage; /* uint: uV */
    uint32_t zero_voltage; /* uint: uV */
    uint32_t zero_deadzone_min_voltage; /* uint: uV */
    uint32_t zero_deadzone_max_voltage; /* uint: uV */
} joystick_nvkey_parameter_t;

typedef struct {
    uint32_t full_release_voltage; /* uint: uV */
    uint32_t full_press_voltage; /* uint: uV */
    uint32_t zero_deadzone_voltage; /* uint: uV */
} trigger_nvkey_parameter_t;

/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
extern void app_joystick_and_trigger_init(void);
extern void app_joystick_and_trigger_deinit(void);
extern void app_joystick_save_paramter(uint8_t number, joystick_nvkey_parameter_t *param);
extern void app_trigger_save_paramter(uint8_t number, trigger_nvkey_parameter_t *param);
extern void app_joystick_get_paramter(uint32_t *x, uint32_t *y, uint32_t *z, uint32_t *rz);
extern void app_trigger_get_paramter(uint32_t *lt, uint32_t *rt);
#if defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE)
extern void app_joystick_and_trigger_wakeup_enable(void);
extern void app_joystick_and_trigger_wakeup_disable(void);
#endif /* CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE */

#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */

#endif /* _APP_JOYSTICK_AND_TRIGGER_H_ */
