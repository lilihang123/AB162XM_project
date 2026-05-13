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
#define DT_DRV_COMPAT airoha_air_pwmdma

#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <errno.h>
#include <zephyr/drivers/pwm.h>
#include "hal_pwm.h"
#include "air_chip.h"
#include <zephyr/logging/log.h>

struct pwmdma_airoha_data {
	uint32_t channel_total_cycles;
	uint8_t start_flag[4];
};

struct pwmdma_airoha_config {
	uint8_t port;
};

static int pwmdma_airoha_set_cycles(const struct device *dev, uint32_t channel,
			       uint32_t period_cycles, uint32_t pulse_cycles,
			       pwm_flags_t flags){
	const struct pwmdma_airoha_config *dev_config = dev->config;
    struct pwmdma_airoha_data *dev_data = dev->data;
	uint32_t freq_cycles;
	hal_pwm_status_t status;
	if(dev_config->port == 0){
		if(channel >= 4){
			return -EINVAL;
		}
	}else{
		if((channel >= 8)||(channel <= 3)){
			return -EINVAL;
		}
	}
	if(dev_data->channel_total_cycles == 0){
		return -EIO;
	}
	if(dev_data->start_flag[channel] != 0){
		status = hal_pwm_stop(channel);
		if(status != HAL_PWM_STATUS_OK){
			return status;
		}
		dev_data->start_flag[channel] = 0;
	}
	if((period_cycles != 0) && (pulse_cycles != 0)){
		status = hal_pwm_set_frequency(channel,dev_data->channel_total_cycles/period_cycles,&freq_cycles);
		status |= hal_pwm_set_duty_cycle(channel,freq_cycles*pulse_cycles/period_cycles);
		if(flags & PWM_POLARITY_INVERTED){
			status |= hal_pwm_set_polarity(channel,0);
		}else{
			status |= hal_pwm_set_polarity(channel,1);
		}
		status |= hal_pwm_start(channel);
		if(status != HAL_PWM_STATUS_OK){
			return status;
		}
		dev_data->start_flag[channel] = 1;
	}
	return 0;
}

static int pwmdma_airoha_get_cycles_per_sec(const struct device *dev, uint32_t channel,
				       uint64_t *cycles)
{
	const struct pwmdma_airoha_config *dev_config = dev->config;
    struct pwmdma_airoha_data *dev_data = dev->data;
	hal_pwm_status_t status;
	if(dev_config->port == 0){
		if(channel >= 4){
			return -EINVAL;
		}
	}else{
		if((channel >= 8)||(channel <= 3)){
			return -EINVAL;
		}
	}
	status = hal_pwm_init(channel,0);
	status |= hal_pwm_set_frequency(channel,1,&(dev_data->channel_total_cycles));
	if(status != HAL_PWM_STATUS_OK){
		return status;
	}
	*cycles = dev_data->channel_total_cycles;
	return 0;
}

static int pwmdma_init(const struct device *dev)
{
	return 0;
}

static const struct pwm_driver_api pwmdma_airoha_driver_api = {
	.set_cycles = pwmdma_airoha_set_cycles,
	.get_cycles_per_sec = pwmdma_airoha_get_cycles_per_sec,
};



#define	PWMDMA_AIROHA_DEVICE(id)						\
									\
static struct pwmdma_airoha_data pwmdma_airoha_p##id##_data;		\
									\
static const struct pwmdma_airoha_config pwmdma_airoha_p##id##_config = {		\
	.port = DT_INST_PROP(id, port),		\
};									\
									\
DEVICE_DT_INST_DEFINE(id,						\
	    pwmdma_init,						\
	    NULL,							\
	    &pwmdma_airoha_p##id##_data,					\
	    &pwmdma_airoha_p##id##_config, 					\
	    CONFIG_PWM_DMA_INIT_LEVEL, CONFIG_PWM_DMA_INIT_PRIORITY, &pwmdma_airoha_driver_api);

DT_INST_FOREACH_STATUS_OKAY(PWMDMA_AIROHA_DEVICE)
