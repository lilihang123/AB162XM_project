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

#ifndef __HAL_SARADC_INTERNAL_H__
#define __HAL_SARADC_INTERNAL_H__

#ifdef HAL_ADC_MODULE_ENABLED

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "hal_platform.h"
#include "hal.h"
#include "hal_adc.h"

hal_adc_status_t hal_saradc_set_mode(hal_saradc_data_rate_t data_rate, hal_saradc_measure_mode_t measure_mode);
hal_adc_status_t hal_saradc_read_calibration(hal_saradc_measure_mode_t measure_mode);
hal_adc_status_t hal_saradc_enable();
hal_adc_status_t hal_saradc_disable();
hal_adc_status_t hal_saradc_set_gpio_mode(uint32_t channel_mask, hal_saradc_gpio_mode_t mode);
hal_adc_status_t hal_saradc_get_data_immediately(hal_saradc_data_t *saradc_data);
hal_adc_status_t hal_saradc_get_data_average(hal_saradc_data_t *saradc_data, hal_adc_average_t average_num);
hal_adc_status_t hal_saradc_get_calibration_voltage_mV(hal_saradc_measure_mode_t measure_mode, uint32_t raw_data, uint32_t *cal_voltage_mV);
hal_adc_status_t hal_saradc_init(hal_saradc_data_rate_t data_rate, hal_saradc_measure_mode_t measure_mode);
hal_adc_status_t hal_saradc_deinit();
hal_adc_status_t hal_adc_get_calibration_data(uint32_t raw_data, uint32_t  *cal_data);
hal_adc_status_t hal_adc_get_calibration_voltage(uint32_t raw_data, uint32_t *cal_voltage);
hal_adc_status_t hal_adc_get_raw_data_by_calibration_voltage(hal_saradc_measure_mode_t measure_mode, uint32_t cal_voltage_mV, uint32_t *raw_data);
#endif

#if defined(HAL_ADC_MODULE_ENABLED) || defined(HAL_AIOADC_MODULE_ENABLED)
void hal_saradc_sdadc_common_setting_internal(bool enable);
#endif

#endif