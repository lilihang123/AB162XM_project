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

#ifndef _ADC_KEYSCAN_H_
#define _ADC_KEYSCAN_H_

#if defined(AIR_ADC_KEYSCAN_ENABLE)

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

typedef union {
    uint16_t keyid_bit[7];                    /*report keyid bit*/
} sw_keyscan_keybit_data_t;
typedef void (*adc_keyscan_callback_t)(sw_keyscan_keybit_data_t *output_data);

typedef struct {
    uint32_t adc_data[16];
} sw_keyscan_row_data_t;

typedef struct {
    uint8_t row_gpio_num;                     /**< Number of Row.*/
    uint8_t row_gpio_map[3];                   /**< Row IOs .*/
    uint8_t mux_en_gpio;
    uint8_t mux_max_index;
    uint8_t mux_trigger_index;
    uint16_t v_threshold;
} sw_keyscan_cfg_t;

typedef struct {
    uint8_t row_gpio_num;                     /**< Number of Row.*/
    uint8_t row_gpio_map[3];                   /**< Row IOs .*/
    uint8_t mux_en_gpio;
    uint8_t mux_max_index;
    uint8_t mux_trigger_index;
    uint16_t v_threshold;
    adc_keyscan_callback_t callback;
    bool init_flag;
} sw_keyscan_info_t;

typedef struct {
    uint8_t write_data_index;
    uint8_t read_data_index;
    sw_keyscan_row_data_t mux_row_data[7];
}sw_keyscan_data_buf_info_t;

typedef enum
{
  ADC_KEYSCAN_STATUS_ERROR = -2,      /**< A keypad function error. */
  ADC_KEYSCAN_INVALID_PARAMETER = -1, /**< An invalid parameter. */
  ADC_KEYSCAN_STATUS_OK = 0           /**< No error occurred during the function call. */
} adc_keyscan_status_t;

typedef void (*fn_key_callback_t)(uint16_t);

#if defined(CORE_MCU)
adc_keyscan_status_t sw_keyscan_mcu_init(sw_keyscan_cfg_t *cfg_info);
adc_keyscan_status_t sw_keyscan_mcu_register_callback(adc_keyscan_callback_t callback);
void sw_keyscan_mcu_deinit(void);
void sw_keyscan_mcu_trigger_dummy_irq(void);
void sw_keyscan_mcu_process(sw_keyscan_keybit_data_t *output_data);
#endif/*CORE_MCU*/

#if defined(CORE_RISCV)
void sw_keyscan_riscv_init(void);
void sw_keyscan_riscv_deinit(void);
void sw_keyscan_riscv_scan_once(void);
#endif/*CORE_RISCV*/






#endif /* AIR_ADC_KEYSCAN_ENABLE */

#endif /* _ADC_KEYSCAN_H_ */
