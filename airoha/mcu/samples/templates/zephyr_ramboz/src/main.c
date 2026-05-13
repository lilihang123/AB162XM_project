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

#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <zephyr/drivers/sensor.h>
#include <zephyr/pm/device.h>
#include <zephyr/drivers/pinctrl.h>
#include <soc.h>

#include <hal_ramboz.h>

#include <zephyr/logging/log.h>
#include <zephyr/irq.h>

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

#define RAMBOZ_NODE_ID	 DT_NODELABEL(ramboz)
const struct device *dev = DEVICE_DT_GET(RAMBOZ_NODE_ID);

void feed_watch_dog(void);

struct sensor_value value = {255, 100};

/*When you need to trigger an IRQ for motion, you need to register a callback function of type SENSOR_TRIG_MOTION.
After registration, there is no need to call sensor_sample_fetch. When motion is detected,
a SENSOR_TRIG_MOTION IRQ will be generated (note that after this IRQ is generated, the IRQ will be disabled,
 so if you want the motion to trigger an IRQ again next time, you need to register it again).*/

void ramboz_test_callback(const struct device *dev, const struct sensor_trigger *trigger)
{
    int ret = 0;
    if (trigger->type == SENSOR_TRIG_DATA_READY) {
        ret = sensor_channel_get(dev, trigger->chan, &value);
        if (ret != 0) {
            printk("Failed to get sensor data: %d\n", ret);
        } else {
            printk("Sensor data ready: %d\n", value.val1);
        }
    } else if (trigger->type == SENSOR_TRIG_MOTION) {
        printk("Motion detected\n");
    }
}

void ramboz_test(void)
{
    printk("--------------ramboz test-----------------");
    int ret;

    struct sensor_trigger trig = {
        .type = SENSOR_TRIG_DATA_READY,
        .chan = SENSOR_CHAN_POS_DZ
        };

    ret = sensor_trigger_set(dev, &trig, ramboz_test_callback);
    if (ret != 0) {
        printk("SENSOR_TRIG_DATA_READY trigger set failed: %d\n", ret);
    } else {
        printk("SENSOR_TRIG_DATA_READY trigger set successfully\n");
    }

    hal_gpt_delay_ms(1000);

    struct sensor_trigger trig2 = {
        .type = SENSOR_TRIG_MOTION,
        .chan = SENSOR_CHAN_POS_DZ
    };

    ret = sensor_trigger_set(dev, &trig2, ramboz_test_callback);
    if (ret != 0) {
        printk("SENSOR_TRIG_MOTION trigger set failed: %d\n", ret);
    } else {
        printk("SENSOR_TRIG_MOTION trigger set successfully\n");
    }

    hal_gpt_delay_ms(1000);
}

int main(void)
{
    int ret;
    ramboz_test();
    for(;;){
        ret = sensor_sample_fetch(dev);
        if (ret != 0 ) {
            printk("sensor_sample_fetch failed\n");
        }
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