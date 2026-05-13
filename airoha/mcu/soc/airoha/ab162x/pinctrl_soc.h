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
/*
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __AIR_PINCTRL_SOC_H__
#define __AIR_PINCTRL_SOC_H__
#include <pinctrl_airoha.h>

struct airoha_pinctrl_soc_pin {
	/** Pin number 0..57 */
	uint32_t pin_num : 6;
	/** control the pin function (UART, SPI, etc.) */
	uint32_t function : 5;
	/** Enable the pin high impedance resistor */
	uint32_t high_impedance : 1;
	/** Enable the pin pull down resistor */
	uint32_t pulldown : 1;
	/** Enable the pin pull up resistor */
	uint32_t pullup : 1;
	/** control the pin as an input or output */
	uint32_t direction : 1;
    /** control the pin as output,set output level */
	uint32_t output : 1;
	/** Enable the internal schmitt trigger */
	uint32_t schmitt: 1;
    /** control the pin drive strength , in mA */
	uint32_t drive_strength : 4;
	/** Slew rate, may be either false (slow) or true (fast) */
	uint32_t slew_rate: 1;
	uint32_t debounce: 6;
};

typedef struct airoha_pinctrl_soc_pin pinctrl_soc_pin_t;


#define Z_PINCTRL_STATE_PIN_INIT(node_id, prop, idx)				\
	{									\
		AIROHA_GET_PIN_NUM(DT_PROP_BY_IDX(node_id, prop, idx)),		\
		AIROHA_GET_PIN_ALT_FUNC(DT_PROP_BY_IDX(node_id, prop, idx)),	\
		DT_PROP(node_id, bias_high_impedance),				\
		DT_PROP(node_id, bias_pull_down),					\
		DT_PROP(node_id, bias_pull_up),				    \
		DT_PROP(node_id, output_enable),					\
        DT_PROP(node_id, output_high),					\
		DT_PROP(node_id, input_schmitt_enable),				\
        DT_ENUM_IDX(node_id, drive_strength),				\
        DT_PROP(node_id, slew_rate),				\
		DT_PROP(node_id ,debounce),            \
	},

#define Z_PINCTRL_STATE_PINS_INIT(node_id, prop)				\
	{DT_FOREACH_CHILD_VARGS(DT_PHANDLE(node_id, prop),			\
				DT_FOREACH_PROP_ELEM, pinmux,			\
				Z_PINCTRL_STATE_PIN_INIT)}


#define AIROHA_GET_PIN_NUM(pinctrl) \
	(((pinctrl) >> AIROHA_PIN_NUM_POS) & AIROHA_PIN_NUM_MASK)
#define AIROHA_GET_PIN_ALT_FUNC(pinctrl) \
	(((pinctrl) >> AIROHA_ALT_FUNC_POS) & AIROHA_ALT_FUNC_MASK)

#endif /* __AIR_PINCTRL_SOC_H__ */