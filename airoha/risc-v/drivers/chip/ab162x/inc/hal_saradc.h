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

#ifndef __HAL_SARADC_H__
#define __HAL_SARADC_H__

#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"

#ifdef HAL_SARADC_MODULE_ENABLED
#include "hal_platform.h"

typedef enum {
    HAL_ADC_STATUS_INVALID_PARAMETER = -4,      /**< Invalid parameter */
    HAL_ADC_STATUS_ERROR_BUSY = -3,             /**< ADC is busy */
    HAL_ADC_STATUS_ERROR_CHANNEL = -2,          /**< ADC channel number error */
    HAL_ADC_STATUS_ERROR = -1,                  /**< ADC error */
    HAL_ADC_STATUS_OK = 0                       /**< ADC ok */
} hal_adc_status_t;

typedef enum {
    HAL_ADC_AVERAGE_1 =   0,                            /**< Average number 1 */
    HAL_ADC_AVERAGE_2 =   1,                            /**< Average number 4 */
    HAL_ADC_AVERAGE_4 =   2,                            /**< Average number 8 */
    HAL_ADC_AVERAGE_8 =   3,                            /**< Average number 16 */
    HAL_ADC_AVERAGE_64 =  4,                            /**< Average number 32 */
    HAL_ADC_AVERAGE_128 = 5,                            /**< Average number 64 */
    HAL_ADC_AVERAGE_256 = 6,                            /**< Average number 128 */
    HAL_ADC_AVERAGE_512 = 7,                            /**< Average number 256 */
    HAL_ADC_AVERAGE_MAX                                 /**< Define max average number(invalid) */
} hal_adc_average_t;

typedef enum {
    HAL_SARADC_DATA_RATE_HS_MODE = 0,
    HAL_SARADC_DATA_RATE_MS_MODE = 1,
    HAL_SARADC_DATA_RATE_LS_MODE = 2,
    HAL_SARADC_DATA_RATE_MAX     = 3
} hal_saradc_data_rate_t;

typedef enum {
    HAL_SARADC_MEASURE_SE_MODE   = 0,
    HAL_SARADC_MEASURE_DIV_MODE  = 1,
    HAL_SARADC_MEASURE_DIFF_MODE = 2,
    HAL_SARADC_MEASURE_MAX       = 3
} hal_saradc_measure_mode_t;

typedef enum {
    HAL_SARADC_GPIO_DIGITAL_MODE   = 0,
    HAL_SARADC_GPIO_ANALOG_MODE    = 1,
    HAL_SARADC_GPIO_MODE_MAX       = 2
} hal_saradc_gpio_mode_t;

typedef struct {
    uint32_t channel_mask;
    uint32_t channel_data[HAL_SARADC_CHANNEL_MAX];
} hal_saradc_data_t;

typedef struct {
    uint8_t gpio_pin[3];
    uint8_t mux_index;
} hal_saradc_special_gpio_cfg_t;

hal_adc_status_t hal_saradc_set_mode(hal_saradc_data_rate_t data_rate, hal_saradc_measure_mode_t measure_mode);
hal_adc_status_t hal_saradc_enable();
hal_adc_status_t hal_saradc_disable();
hal_adc_status_t hal_saradc_set_gpio_mode(uint32_t channel_mask, hal_saradc_gpio_mode_t mode);
hal_adc_status_t hal_saradc_get_data_immediately(hal_saradc_data_t *saradc_data);
hal_adc_status_t hal_saradc_dma_init();
hal_adc_status_t hal_saradc_get_data_immediately_for_special(volatile uint32_t *dest_address, uint32_t channel_mask, hal_saradc_special_gpio_cfg_t gpio_cfg, uint8_t mux_max_index);
hal_adc_status_t hal_saradc_get_calibration_voltage_mV(hal_saradc_measure_mode_t measure_mode, uint32_t raw_data, uint32_t *cal_voltage_mV);
hal_adc_status_t hal_saradc_init(hal_saradc_data_rate_t data_rate, hal_saradc_measure_mode_t measure_mode);
hal_adc_status_t hal_saradc_deinit();

#endif
#endif