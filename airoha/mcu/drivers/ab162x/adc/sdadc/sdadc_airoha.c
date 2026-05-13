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
#include <assert.h>
#include <string.h>
#include "memory_attribute.h"

#include <zephyr/drivers/adc.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>

#include "hal_adc.h"
#include "hal_saradc_internal.h"

#define DT_DRV_COMPAT airoha_air_saradc


struct sdadc_airoha_cfg
{
    uint8_t channel_num;
    uint16_t avg;
    uint8_t measure_mode;
    uint8_t data_rate;
    int gain;
    int reference;
};

struct sdadc_airoha_data
{

};


hal_adc_average_t acquisition_time_transition_to_airoha(uint16_t acquisition_time)
{
    hal_adc_average_t saradc_avg = HAL_ADC_AVERAGE_MAX;
    switch (acquisition_time)
    {
    case 1:
        saradc_avg = HAL_ADC_AVERAGE_1;
        break;
    case 2:
        saradc_avg = HAL_ADC_AVERAGE_2;
        break;
    case 4:
        saradc_avg = HAL_ADC_AVERAGE_4;
        break;
    case 8:
        saradc_avg = HAL_ADC_AVERAGE_8;
        break;
    case 64:
        saradc_avg = HAL_ADC_AVERAGE_64;
        break;
    case 168:
        saradc_avg = HAL_ADC_AVERAGE_128;
        break;
    case 256:
        saradc_avg = HAL_ADC_AVERAGE_256;
        break;
    case 512:
        saradc_avg = HAL_ADC_AVERAGE_512;
        break;
    default:
        saradc_avg = HAL_ADC_AVERAGE_512;
        break;
    }
    return saradc_avg;
}

static int sdadc_airoha_channel_setup(const struct device *dev,
				  const struct adc_channel_cfg *channel_cfg)
{
    const struct sdadc_airoha_cfg *config = (struct sdadc_airoha_cfg*)(dev->config);
    
    hal_saradc_measure_mode_t measure_mode = config->measure_mode;
    hal_saradc_data_rate_t data_rate = config->data_rate;
    hal_saradc_init(data_rate, measure_mode);

    return 0;
}

static int sdadc_airoha_read(const struct device *dev,
			 const struct adc_sequence *sequence)
{
    const struct sdadc_airoha_cfg *config = (struct sdadc_airoha_cfg*)(dev->config);
    hal_adc_channel_t channel = config->channel_num;
    uint32_t *data = sequence->buffer;
    uint32_t raw_data;
    hal_adc_average_t avg = acquisition_time_transition_to_airoha(config->avg);
    hal_adc_get_average_data(channel, avg ,&raw_data);
    hal_adc_get_calibration_voltage(raw_data, data);
    hal_saradc_deinit();
    return 0;
}

#ifdef CONFIG_ADC_ASYNC
static int sdadc_airoha_read_async(const struct device *dev,
			       const struct adc_sequence *sequence,
			       struct k_poll_signal *async)
{
    const struct sdadc_airoha_cfg *config = (struct sdadc_airoha_cfg*)(dev->config);
    hal_adc_channel_t channel = config->saradc_channel;
    uint32_t *data = sequence->buffer;
    uint32_t raw_data;
    hal_adc_average_t avg = config->saradc_avg;
    hal_adc_get_data_polling(channel, raw_data);
    hal_adc_get_calibration_voltage(raw_data, data);
    hal_saradc_deinit();
    return 0;
}
#endif

static int sdadc_airoha_init(const struct device *dev)
{
    // const struct sdadc_airoha_cfg *config = dev->config;
    hal_adc_init();
    return 0;
}

static const struct adc_driver_api sdadc_airoha_api = {
	.channel_setup = sdadc_airoha_channel_setup,
	.read = sdadc_airoha_read,
#ifdef CONFIG_ADC_ASYNC
	.read_async = sdadc_airoha_read_async,
#endif
	.ref_internal = 1800,
};

#define SAR_ADC_AIROHA_DEFINE(id)                                      \
	static struct sdadc_airoha_cfg sdadc_airoha_##id##_cfg = {       \
        .channel_num = (uint8_t)DT_INST_PROP(id, channel_id),          \
        .avg = (uint16_t)DT_INST_PROP(id, acquisition_time),           \
        .measure_mode = (uint32_t)DT_INST_PROP(id, resolution),        \
        .data_rate = (uint32_t)DT_INST_PROP(id, oversampling),         \
        .gain = (uint32_t)DT_INST_PROP(id, gain),                      \
        .reference = (uint32_t)DT_INST_PROP(id, reference),            \
    };                                                                 \
    static struct sdadc_airoha_data sdadc_airoha_##id##_data;        \
                                                                       \
	DEVICE_DT_INST_DEFINE(  id,                                        \
                            sdadc_airoha_init,                        \
                            NULL,                                      \
                            &sdadc_airoha_##id##_data,                \
			                &sdadc_airoha_##id##_cfg,                 \
                            CONFIG_AIOADC_INIT_LEVEL,                 \
                            CONFIG_AIOADC_INIT_PRIORITY,              \
			                &sdadc_airoha_api);                       \

DT_INST_FOREACH_STATUS_OKAY(AIOADC_AIROHA_DEFINE)