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

#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/pinctrl.h>
#include <soc.h>

#include <hal_qdec.h>
#include <qdec_airoha.h>
#include <zephyr/logging/log.h>
#include <zephyr/irq.h>

#include "air_chip.h"
#include "hal_platform.h"

#include "qdec_airoha.h"

#if defined(HAL_GPT_MODULE_ENABLED)
#include "hal_gpt.h"
#endif

#include "memory_attribute.h"
#include "autoconf.h"

#ifdef CONFIG_AIR_WDT
#include "wdt_airoha.h"
#endif

void feed_watch_dog(void);

#define QDEC_NODE_ID	 DT_NODELABEL(qdec)
const struct device *dev = DEVICE_DT_GET(QDEC_NODE_ID);

struct sensor_value attr_val_set = {.val1 = 1, .val2 = 0};

/*When you need to trigger an IRQ for motion, you need to register a callback function of type SENSOR_TRIG_MOTION.
After registration, there is no need to call sensor_sample_fetch. When motion is detected,
a SENSOR_TRIG_MOTION IRQ will be generated (note that after this IRQ is generated, the IRQ will be disabled,
 so if you want the motion to trigger an IRQ again next time, you need to register it again).*/

void qdec_zephyr_test_callback(const struct device *dev,
					 const struct sensor_trigger *trigger)
{
    int rc;
    struct sensor_value val;
    if (trigger->type == SENSOR_TRIG_DATA_READY) {
    rc = sensor_channel_get(dev, SENSOR_CHAN_POS_DZ, &val);
    if (rc != 0) {
        printk("Failed to get data (%d)\n", rc);
    }
        printk("callback Position = %d degrees = %d\n", val.val1, val.val2);
        printk("\r\n");
    } else if (trigger->type == SENSOR_TRIG_MOTION) {
        printk("Motion detected\n");
    }
}

void qdec_test(void)
{
    printk("-----------------------qdec driver test--------------------------\n");

    if (!device_is_ready(dev)) {
        printk("Qdec device is not ready\n");
        return;
    }

    int rc;

    struct sensor_trigger trig = {
      .type = SENSOR_TRIG_DATA_READY,
      .chan = SENSOR_CHAN_POS_DZ,
    };

    rc = sensor_trigger_set(dev ,&trig, qdec_zephyr_test_callback);
    if (rc != 0) {
      printk("set SENSOR_TRIG_DATA_READY trigger failed (%d)\n", rc);
    } else {
        printk("set SENSOR_TRIG_DATA_READY trigger success\n");
    }

    struct sensor_trigger trig2 = {
      .type = SENSOR_TRIG_MOTION,
      .chan = SENSOR_CHAN_POS_DZ,
    };
    rc = sensor_trigger_set(dev ,&trig2, qdec_zephyr_test_callback);
    if (rc != 0) {
      printk("set SENSOR_TRIG_MOTION trigger failed (%d)\n", rc);
    } else {
        printk("set SENSOR_TRIG_MOTION trigger success\n");
    }

    int ret;

    attr_val_set.val1=0;
    attr_val_set.val2=0;
    ret = sensor_attr_set(dev, SENSOR_CHAN_POS_DZ, QDEC_MODE_STATUS, &attr_val_set);
    if(ret != 0)
    {
      printk("QDEC_MODE_STATUS set failed\r\n");
    } else {
      printk("QDEC_MODE_STATUS set success\r\n");
    }
    printk("attr_val_set,hw mode 1:active/0:idle = %d\r\n",attr_val_set.val1);
    hal_gpt_delay_ms(1000);

    attr_val_set.val1=0XC;
    attr_val_set.val2=0xC0C;
    ret = sensor_attr_set(dev, SENSOR_CHAN_POS_DZ, QDEC_A_GROUP_CFG, &attr_val_set);
    if(ret != 0)
    {
      printk("QDEC_A_GROUP_CFG set failed\r\n");
    } else {
      printk("QDEC_A_GROUP_CFG set success\r\n");
    }
    printk("attr_val_set,z sum 1:enable/0:disable value1 = %d,value2 = %d,\r\n",attr_val_set.val1,attr_val_set.val2);
    hal_gpt_delay_ms(1000);

    attr_val_set.val1=0XC;
    attr_val_set.val2=0xC0C;
    ret = sensor_attr_set(dev, SENSOR_CHAN_POS_DZ, QDEC_B_GROUP_CFG, &attr_val_set);
    if(ret != 0) {
      printk("QDEC_B_GROUP_CFG set failed\r\n");
    } else {
      printk("QDEC_B_GROUP_CFG set success\r\n");
    }
    printk("attr_val_set,z sum 1:enable/0:disable value1 = %d,value2 = %d,\r\n",attr_val_set.val1,attr_val_set.val2);
    hal_gpt_delay_ms(1000);

    attr_val_set.val1=1;
    attr_val_set.val2=0;
    ret = sensor_attr_set(dev, SENSOR_CHAN_POS_DZ, QDEC_DATA_READY_IRQ, &attr_val_set);
    if(ret != 0) {
      printk("QDEC_DATA_READY_IRQ set failed\r\n");
    } else {
      printk("QDEC_DATA_READY_IRQ set success\r\n");
    }
    printk("attr_val_set,data ready 1:enable/0:disable = %d\r\n",attr_val_set.val1);
    hal_gpt_delay_ms(1000);

    attr_val_set.val1=1;
    attr_val_set.val2=0x0;
    ret = sensor_attr_set(dev, SENSOR_CHAN_POS_DZ, QDEC_Z_SUM_IRQ_CFG, &attr_val_set);
    if(ret != 0) {
      printk("QDEC_Z_SUM_IRQ_CFG set failed\r\n");
    } else {
      printk("QDEC_Z_SUM_IRQ_CFG set success\r\n");
    }
    printk("attr_val_set,z sum 1:enable/0:disable = %d,value = %d,\r\n",attr_val_set.val1,attr_val_set.val2);
    hal_gpt_delay_ms(1000);

    // attr_val_set.val1=1;
	// attr_val_set.val2=0x0;
	// ret = sensor_attr_set(dev, SENSOR_CHAN_POS_DZ, QDEC_HW_SEL_CFG, &attr_val_set);
	// if(ret != 0)
	// {
	// 	printk("QDEC_HW_SEL_CFG set failed\r\n");
	// } else {
    //     printk("QDEC_HW_SEL_CFG set success\r\n");
    // }
	// printk("attr_val_set,z sum 1:enable/0:disable = %d,value = %d,\r\n",attr_val_set.val1,attr_val_set.val2);
	// hal_gpt_delay_ms(1000);

    feed_watch_dog();

    struct sensor_value attr_val_get;

    attr_val_get.val1=0;
    attr_val_get.val2=0;
    hal_gpt_delay_ms(1000);
    ret = sensor_attr_get(dev, SENSOR_CHAN_POS_DZ, QDEC_A_GROUP_CFG, &attr_val_get);
    if(ret != 0) {
      printk("sensor get failed\r\n");
    } else {
      printk("sensor get success\r\n");
    }
    printk("attr_val_get,z sum 1:enable/0:disable value1 = %d,value2 = %d,\r\n",attr_val_get.val1,attr_val_get.val2);
    hal_gpt_delay_ms(1000);

    feed_watch_dog();

    /*Qdec hw latch status: This can only be gotten; setting it is invalid.
    You can use it to check whether the data transfer is complete after the latch is released.
    Once the transfer is complete, the status will return 1.
    (Note, when the data ready IRQ is enabled, this value will not be valid,
    which means the user should choose either to get the hw latch status via the data ready IRQ or by polling.)*/
}

int main(void)
{
    int ret;
    qdec_test();
    for(;;){
      printk("sensor_sample_fetch\r\n");
      ret = sensor_sample_fetch(dev);
      if (ret != 0) {
        printk("Failed to fetch sample (%d)\n", ret);
      } else {
        printk("sensor_sample_fetch success\r\n");
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