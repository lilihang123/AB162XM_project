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

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <errno.h>
#include <zephyr/drivers/led.h>
#include <zephyr/sys/util.h>
#include <zephyr/kernel.h>
#include "hal_gpt.h"

#include <zephyr/device.h>

#include "air_chip.h"
#include "hal_platform.h"

#if defined(HAL_GPT_MODULE_ENABLED)
#include "hal_gpt.h"
#endif

#include "memory_attribute.h"
#include "autoconf.h"

#ifdef CONFIG_AIR_WDT
#include "wdt_airoha.h"
#endif

#define LED_PWM_NODE_ID	 DT_NODELABEL(led)

const int num_leds = 3;

#define MAX_BRIGHTNESS	100

#define FADE_DELAY_MS	10
#define FADE_DELAY	K_MSEC(FADE_DELAY_MS)

/**
 * @brief Run tests on a single LED using the LED API syscalls.
 *
 * @param led_pwm LED PWM device.
 * @param led Number of the LED to test.
 */
static void run_led_test(const struct device *led_pwm, uint8_t led)
{
	int err;
	uint16_t level = MAX_BRIGHTNESS;

	printk("led test----------------------");

	/* Turn LED on. */
	err = led_on(led_pwm, led);
	if (err < 0) {
		printk("led on failed - err: %d");
		return;
	}
	printk("led on");
	hal_gpt_delay_ms(1000);

	/* Turn LED off. */
	err = led_off(led_pwm, led);
	if (err < 0) {
		printk("led off failed - err: %d");
		return;
	}
	printk("led off");
	hal_gpt_delay_ms(1000);

	/* Increase LED brightness gradually up to the maximum level. */
	printk("  Increasing brightness gradually");
	for (level = 2; level <= MAX_BRIGHTNESS; level++) {
		err = led_set_brightness(led_pwm, led, level);
		if (err < 0) {
			printk("err=%d brightness=%d\n", err, level);
			return;
		}
		hal_gpt_delay_ms(100);
	}
	hal_gpt_delay_ms(1000);

	/* Set LED blinking (on: 0.1 sec, off: 0.1 sec) */
	err = led_blink(led_pwm, led, 100, 100);
	if (err < 0) {
		printk("err=%d", err);
		return;
	}
	printk("  Blinking on: 0.1 sec, off: 0.1 sec");
	hal_gpt_delay_ms(5000);

	/* Enable LED blinking (on: 1 sec, off: 1 sec) */
	err = led_blink(led_pwm, led, 1000, 1000);
	if (err < 0) {
		printk("err=%d", err);
		printk("  Cycle period not supported - on: 1 sec, off: 1 sec");
	} else {
		printk("  Blinking on: 1 sec, off: 1 sec");
	}
	hal_gpt_delay_ms(5000);

	/* Turn LED off. */
	err = led_off(led_pwm, led);
	if (err < 0) {
		printk("err=%d", err);
		return;
	}
	printk("  Turned off, loop end");
}

void feed_watch_dog(void);

int main(void)
{
	const struct device *led_pwm;
	uint8_t led = 0;

	led_pwm = DEVICE_DT_GET(LED_PWM_NODE_ID);
	if (!device_is_ready(led_pwm)) {
		printk("Device %s is not ready", led_pwm->name);
		return 0;
	}

	for(led = 0; led < num_leds; led++) {
            feed_watch_dog();
            run_led_test(led_pwm, led);
        }

    for(;;){
        // for(led = 0; led < num_leds; led++) {
        //     feed_watch_dog();
        //     run_led_test(led_pwm, led);
        // }
#if defined(HAL_GPT_MODULE_ENABLED)
        hal_gpt_delay_ms(3000);
#else
        uint32_t count = 0x5A5A5A5A;
        while(count--){
            __asm__("mov r0, r0");
        }
#endif
        feed_watch_dog();
    }
    return 0;
}

void feed_watch_dog(void)
{
#ifdef CONFIG_AIR_WDT
    const struct device *wdt_dev = \
        device_get_binding(DT_NODE_FULL_NAME(DT_NODELABEL(wdt0)));
    if(wdt_dev != NULL){
        int wdt_ch = ((wdt_air_data_t*)(wdt_dev->data))->m_channel;
        printk("[wdt] wdt_feed was called with dev: 0x%08X and channel %d\r\n", (unsigned int)wdt_dev, wdt_ch);
        wdt_feed(wdt_dev, wdt_ch);
    }
#endif
}
