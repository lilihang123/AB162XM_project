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
#define DT_DRV_COMPAT airoha_air_led

#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <errno.h>
#include <zephyr/drivers/led.h>
#include "hal_led.h"
#include "hal_gpt.h"
#include "hal_gpio.h"
#include "air_chip.h"
#include <zephyr/logging/log.h>

#ifdef AIR_LED_PWM
#include "hal_pwm.h"
#define PWM_CHANNEL_BASE 4
#endif

struct led_airoha_data {
	uint8_t start_flag[3];
	uint8_t brightness[3];
	uint8_t polarity[3];
};

// struct k_mutex led_mutex;
static int led_airoha_api_set_brightness(const struct device *dev, uint32_t led,
				      uint8_t value){
	printk("led_airoha_api_set_brightness, led: %d, value: %d\n", led, value);
	if(led > 4){
		return -EIO;
	}

	// k_mutex_lock(&led_mutex, K_FOREVER);
	// struct led_airoha_data *dev_data = dev->data;
	if(led <= 3){
		hal_led_init(led);
		// if(dev_data->start_flag[led]){
		hal_led_stop(led);
		// dev_data->start_flag[led] = 0;
		hal_led_config_ext_t config_led;
		config_led.timing.t0= 0;
		config_led.timing.t1.t_rising = 0;
		config_led.timing.t1.t_lightest= 1000;
		config_led.timing.t2.t_falling = 0;
		config_led.timing.t2.t_darkest = 0;
		config_led.timing.t3 = 0;
		config_led.brightness = value;
		config_led.blink_nums = 0;
		hal_led_configure_ext(led,&config_led);
		hal_led_start(led);
		// }
		// dev_data->start_flag[led] = 1;
	}else if (led > 3) {
#ifdef AIR_LED_PWM
		// Handle the case where the LED is > 3
		uint32_t frequency = 200; //PWM output frequency
		uint32_t pwm_value = 255; //PWM output value
		hal_pwm_source_clock_t source_clock = HAL_PWM_CLOCK_32KHZ;
		hal_pwm_init(led - PWM_CHANNEL_BASE, source_clock);
		hal_pwm_set_polarity(led - PWM_CHANNEL_BASE, pwm_value);
		hal_pwm_set_frequency_and_duty(led - PWM_CHANNEL_BASE, source_clock, frequency, pwm_value);
		hal_pwm_start(led - PWM_CHANNEL_BASE);
#endif
	}
	// dev_data->start_flag[led] = 1;
	// k_mutex_unlock(&led_mutex);
	return 0;
}

static int led_airoha_api_on(const struct device *dev, uint32_t led){

	struct led_airoha_data *dev_data = dev->data;
	return led_airoha_api_set_brightness(dev,  led, dev_data->brightness[led]);
}

static int led_airoha_api_off(const struct device *dev, uint32_t led){
	if(led > 4){
		return -EIO;
	}
	struct led_airoha_data *dev_data = dev->data;
	// k_mutex_lock(&led_mutex, K_FOREVER);
	if( led <= 3){
		// if(dev_data->start_flag[led]){
			hal_led_stop(led);
		// 	dev_data->start_flag[led] = 0;
		// }
		hal_led_config_ext_t config_led;
		config_led.timing.t0= 0;
		config_led.timing.t1.t_rising = 0;
		config_led.timing.t1.t_lightest= 0;
		config_led.timing.t2.t_falling = 0;
		config_led.timing.t2.t_darkest = 1000;
		config_led.timing.t3 = 0;
		config_led.brightness = dev_data->brightness[led];
		config_led.blink_nums = 0;
		hal_led_configure_ext(led,&config_led);
		hal_led_start(led);
	}else if (led > 3) {
		// Handle the case where the LED is > 3
#ifdef AIR_LED_PWM
		hal_pwm_stop(led - PWM_CHANNEL_BASE);
		hal_pwm_deinit(led - PWM_CHANNEL_BASE);
#endif
	}
	// k_mutex_unlock(&led_mutex);
	// dev_data->start_flag[led] = 1;
	return 0;
}

static int led_airoha_api_blink(const struct device *dev, uint32_t led,
			     uint32_t delay_on, uint32_t delay_off){
	if(led > 4){
		return -EIO;
	}
	struct led_airoha_data *dev_data = dev->data;
	if(dev_data->start_flag[led]){
		hal_led_stop(led);
		dev_data->start_flag[led] = 0;
	}
	hal_led_config_ext_t config_led;
	config_led.timing.t0= 0;
	config_led.timing.t1.t_rising = 0;
	config_led.timing.t1.t_lightest= delay_on;
	config_led.timing.t2.t_falling = 0;
	config_led.timing.t2.t_darkest = delay_off;
	config_led.timing.t3 = 0;
	config_led.brightness = dev_data->brightness[led];
	config_led.blink_nums = 0;
	hal_led_configure_ext(led,&config_led);
	hal_led_start(led);
	dev_data->start_flag[led] = 1;
	return 0;
}

static int led_init(const struct device *dev)
{
	// k_mutex_init(&led_mutex);
	return 0;
}

static const struct led_driver_api led_airoha_driver_api = {
	.on = led_airoha_api_on,
	.off = led_airoha_api_off,
	.blink = led_airoha_api_blink,
	.set_brightness = led_airoha_api_set_brightness,
};

#if 0
#define LED_CHANNEL_CFG(node) \
{ \
	.brightness = DT_PROP(node, brightness), \
	.polarity = DT_PROP(node, polarity), \
},


#define	LED_AIROHA_DEVICE(id)						\
									\
static struct led_airoha_data led_airoha_p##id##_data;		\
									\
static const struct led_airoha_config led_airoha_p##id##_config[] = {		\
	DT_INST_FOREACH_CHILD(id, LED_CHANNEL_CFG) \
};									\
									\
DEVICE_DT_INST_DEFINE(id,						\
	    led_init,						\
	    NULL,							\
	    &led_airoha_p##id##_data,					\
	    &led_airoha_p##id##_config, 					\
	    CONFIG_LED_INIT_LEVEL, CONFIG_LED_INIT_PRIORITY, &led_airoha_driver_api);

#else
#define	LED_AIROHA_DEVICE(id)						\
									\
static struct led_airoha_data led_airoha_p##id##_data = { \
	.brightness[0] = DT_PROP(DT_CHILD(DT_DRV_INST(id),channel0),brightness), \
	.brightness[1] = DT_PROP(DT_CHILD(DT_DRV_INST(id),channel1),brightness), \
	.brightness[2] = DT_PROP(DT_CHILD(DT_DRV_INST(id),channel2),brightness), \
	.polarity[0] = DT_PROP(DT_CHILD(DT_DRV_INST(id),channel0),polarity), \
	.polarity[1] = DT_PROP(DT_CHILD(DT_DRV_INST(id),channel1),polarity), \
	.polarity[2] = DT_PROP(DT_CHILD(DT_DRV_INST(id),channel2),polarity), \
};\
									\
DEVICE_DT_INST_DEFINE(id,						\
	    led_init,						\
	    NULL,							\
	    &led_airoha_p##id##_data,					\
	    NULL, 					\
	    CONFIG_LED_INIT_LEVEL, CONFIG_LED_INIT_PRIORITY, &led_airoha_driver_api);
#endif

DT_INST_FOREACH_STATUS_OKAY(LED_AIROHA_DEVICE)
