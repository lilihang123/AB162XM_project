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

#include <zephyr/sys/printk.h>
#include "hal_qdec.h"
#include "hal_gpt.h"

#include <zephyr/drivers/uart.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include "qdec_airoha.h"


void positive_direction(uint8_t number, uint32_t delay_us)
{
    int i;
    for (i = 0; i < number; i++)
    {
        *(volatile uint32_t *)0x42020030 = 0x0000;
        hal_gpt_delay_us(delay_us);
        *(volatile uint32_t *)0x42020030 = 0x8000;
        hal_gpt_delay_us(delay_us);
        *(volatile uint32_t *)0x42020030 = 0xC000;
        hal_gpt_delay_us(delay_us);
        *(volatile uint32_t *)0x42020030 = 0x4000;
        hal_gpt_delay_us(delay_us);
        *(volatile uint32_t *)0x42020030 = 0x0000;
    }
}


void qdec_zephry_test_callback()
{	
	int rc;	
	struct sensor_value val;
	const struct device *dev= device_get_binding(DT_NODE_FULL_NAME(DT_NODELABEL(qdec)));
	rc = sensor_channel_get(dev, SENSOR_CHAN_ROTATION, &val);
	if (rc != 0) {
			printk("Failed to get data (%d)\n", rc);
            // LOG_INF("Failed to get data (%d)\n", rc);
	}
	printk("callback Position = %d degrees = %d\n", val.val1, val.val2);
	printk("\r\n");
}



void qdec_porting_test(void)
{
    /*fpga setting*/
    *(volatile uint32_t *)0x42020040 = 0x8000;//jixie
    // LOG_INF("multi thread :qdec test\r\n");
    printk("main :qdec test\r\n");


	int rc;
    const struct device *dev= device_get_binding(DT_NODE_FULL_NAME(DT_NODELABEL(qdec)));
	if (!device_is_ready(dev)) {
		printk("Qdec device is not ready\n");
        // LOG_INF("Qdec device is not ready\r\n");
	}
	
	struct sensor_trigger trig = {
		.type = SENSOR_TRIG_DATA_READY,
		.chan = SENSOR_CHAN_POS_DZ,
	};
	rc = sensor_trigger_set(dev ,&trig, qdec_zephry_test_callback);
	if (rc != 0) {
			printk("Failed to sensor_trigger_set (%d)\n", rc);
            // LOG_INF("Failed to fetch sample (%d)\n", rc);
	}

	struct sensor_trigger trig2 = {
		.type = SENSOR_TRIG_MOTION,
		.chan = SENSOR_CHAN_POS_DZ,
	};
	rc = sensor_trigger_set(dev ,&trig2, qdec_zephry_test_callback);
	if (rc != 0) {
			printk("Failed to sensor_trigger_set2 (%d)\n", rc);
            // LOG_INF("Failed to fetch sample (%d)\n", rc);
	}

	/*zephyr set api test*/
	printk("zephyr set api test\r\n");
	struct sensor_value attr_val_set;
	int ret;
	// attr_val_set.val1=1;
	// attr_val_set.val2=0;
	// ret = sensor_attr_set(dev,SENSOR_CHAN_POS_DZ,QDEC_MODE_STATUS, &attr_val_set);
	// if(ret != 0)
	// {
	// 	printk("zephyr get failed\r\n");
	// }
	// printk("attr_val_set,hw mode 1:active/0:idle = %d\r\n",attr_val_set.val1);
	// hal_gpt_delay_ms(1000);

	// attr_val_set.val1=0x0;
	// attr_val_set.val2=0x2;
	// ret = sensor_attr_set(dev,SENSOR_CHAN_POS_DZ,QDEC_A_GROUP_CFG, &attr_val_set);
	// if(ret != 0)
	// {
	// 	printk("zephyr get failed\r\n");
	// }
	// printk("attr_val_set,a reg 0:sample/1= %d,led+debounce ,%d\r\n",attr_val_set.val1,attr_val_set.val2);
	// hal_gpt_delay_ms(1000);

	// attr_val_set.val1=0xC;
	// attr_val_set.val2=0xC0C;
	// ret = sensor_attr_set(dev,SENSOR_CHAN_POS_DZ,QDEC_B_GROUP_CFG, &attr_val_set);
	// if(ret != 0)
	// {
	// 	printk("zephyr get failed\r\n");
	// }
	// printk("attr_val_set,b reg 0:sample/1= %d,led+debounce = %d\r\n",attr_val_set.val1,attr_val_set.val2);
	// hal_gpt_delay_ms(1000);

	// attr_val_set.val1=0;
	// attr_val_set.val2=0;
	// ret = sensor_attr_set(dev,SENSOR_CHAN_POS_DZ,QDEC_DATA_READY_IRQ, &attr_val_set);
	// if(ret != 0)
	// {
	// 	printk("zephyr get failed\r\n");
	// }
	// printk("attr_val_set,data ready 1:enable/0:disable = %d\r\n",attr_val_set.val1);
	// hal_gpt_delay_ms(1000);

	attr_val_set.val1=1;
	attr_val_set.val2=0xA;
	ret = sensor_attr_set(dev,SENSOR_CHAN_POS_DZ,QDEC_Z_SUM_IRQ_CFG, &attr_val_set);
	if(ret != 0)
	{
		printk("zephyr get failed\r\n");
	}
	printk("attr_val_set,z sum 1:enable/0:disable = %d,value = %d,\r\n",attr_val_set.val1,attr_val_set.val2);
	hal_gpt_delay_ms(1000);

	// attr_val_set.val1=1;
	// attr_val_set.val2=1;
	// ret = sensor_attr_set(dev,SENSOR_CHAN_POS_DZ,QDEC_HW_SEL_CFG, &attr_val_set);
	// if(ret != 0)
	// {
	// 	printk("zephyr get failed\r\n");
	// }
	// printk("attr_val_set,hw sel 1:enable/0:disable = %d,value = %d,\r\n",attr_val_set.val1,attr_val_set.val2);
	// hal_gpt_delay_ms(1000);

	// attr_val_set.val1=0;
	// attr_val_set.val2=0;
	// ret = sensor_attr_set(dev,SENSOR_CHAN_POS_DZ,QDEC_HW_LATCH_STATUS,&attr_val_set);
	// if(ret != 0)
	// {
	// 	printk("zephyr set failed-QDEC_HW_LATCH_STATUS\r\n");
	// }
	// printk("attr_val_set,latch status 0:on going/1:finish = %d\r\n",attr_val_set.val1);
	// hal_gpt_delay_ms(1000);
	// printk("\r\n");



	/*zephyr get api test*/
	printk("zephyr get api test\r\n");
	struct sensor_value attr_val_get;
	// // int ret;
	// attr_val_get.val1=0;
	// attr_val_get.val2=0;
	// hal_gpt_delay_ms(1000);
	// ret = sensor_attr_get(dev,SENSOR_CHAN_POS_DZ,QDEC_MODE_STATUS, &attr_val_get);
	// if(ret != 0)
	// {
	// 	printk("zephyr get failed\r\n");
	// }
	// printk("attr_val_get,hw mode 1:active/0:idle = %d\r\n",attr_val_get.val1);
	// hal_gpt_delay_ms(1000);

	// attr_val_get.val1=0;
	// attr_val_get.val2=0;
	// hal_gpt_delay_ms(1000);
	// ret = sensor_attr_get(dev,SENSOR_CHAN_POS_DZ,QDEC_A_GROUP_CFG, &attr_val_get);
	// if(ret != 0)
	// {
	// 	printk("zephyr get failed\r\n");
	// }
	// printk("attr_val_get,a reg 0:sample/1= %d,led+debounce ,%d\r\n",attr_val_get.val1,attr_val_get.val2);
	// hal_gpt_delay_ms(1000);

	// attr_val_get.val1=0;
	// attr_val_get.val2=0;
	// hal_gpt_delay_ms(1000);
	// ret = sensor_attr_get(dev,SENSOR_CHAN_POS_DZ,QDEC_B_GROUP_CFG, &attr_val_get);
	// if(ret != 0)
	// {
	// 	printk("zephyr get failed\r\n");
	// }
	// printk("attr_val_get,b reg 0:sample/1= %d,led+debounce = %d\r\n",attr_val_get.val1,attr_val_get.val2);
	// hal_gpt_delay_ms(1000);

	// attr_val_get.val1=0;
	// attr_val_get.val2=0;
	// hal_gpt_delay_ms(1000);
	// ret = sensor_attr_get(dev,SENSOR_CHAN_POS_DZ,QDEC_DATA_READY_IRQ, &attr_val_get);
	// if(ret != 0)
	// {
	// 	printk("zephyr get failed\r\n");
	// }
	// printk("attr_val_get,data ready 1:enable/0:disable = %d\r\n",attr_val_get.val1);
	// hal_gpt_delay_ms(1000);

	attr_val_get.val1=0;
	attr_val_get.val2=0;
	hal_gpt_delay_ms(1000);
	ret = sensor_attr_get(dev,SENSOR_CHAN_POS_DZ,QDEC_Z_SUM_IRQ_CFG, &attr_val_get);
	if(ret != 0)
	{
		printk("zephyr get failed\r\n");
	}
	printk("attr_val_get,z sum 1:enable/0:disable = %d,value = %d,\r\n",attr_val_get.val1,attr_val_get.val2);
	hal_gpt_delay_ms(1000);

	// attr_val_get.val1=0;
	// attr_val_get.val2=0;
	// hal_gpt_delay_ms(1000);
	// ret = sensor_attr_get(dev,SENSOR_CHAN_POS_DZ,QDEC_HW_SEL_CFG, &attr_val_get);
	// if(ret != 0)
	// {
	// 	printk("zephyr get failed\r\n");
	// }
	// printk("attr_val_get,hw sel 1:enable/0:disable = %d,value = %d,\r\n",attr_val_get.val1,attr_val_get.val2);
	// hal_gpt_delay_ms(1000);

	attr_val_get.val1=0;
	attr_val_get.val2=0;
	hal_gpt_delay_ms(1000);
	ret = sensor_attr_get(dev,SENSOR_CHAN_POS_DZ,QDEC_HW_LATCH_STATUS,&attr_val_get);
	if(ret != 0)
	{
		printk("zephyr get failed\r\n");
	}
	printk("attr_val_get,latch status 0:on going/1:finish = %d\r\n",attr_val_get.val1);
	ret = sensor_attr_get(dev,SENSOR_CHAN_POS_DZ,QDEC_HW_LATCH_STATUS,&attr_val_get);
	if(ret != 0)
	{
		printk("zephyr get failed\r\n");
	}
	printk("attr_val_get,latch status 0:on going/1:finish = %d\r\n",attr_val_get.val1);
	hal_gpt_delay_ms(1000);





	printk("z sum irq test\r\n");
	positive_direction(6,500);
	hal_gpt_delay_ms(5000);
	printk("\r\n");

	printk("sensor_sample_fetch\r\n");
	rc = sensor_sample_fetch(dev);
	if (rc != 0) {
			printk("Failed to fetch sample (%d)\n", rc);
            // LOG_INF("Failed to fetch sample (%d)\n", rc);
	}


	while (true) {
		printk("while\r\n");
		// rc = sensor_sample_fetch(dev);
		// if (rc != 0) {
		// 	printk("Failed to fetch sample (%d)\n", rc);
        //     // LOG_INF("Failed to fetch sample (%d)\n", rc);
		// }
		hal_gpt_delay_ms(1000);
        // LOG_INF("FPosition = %d degrees\n", val.val1);
		// positive_direction(8,500);
		
	attr_val_get.val1=0;
	attr_val_get.val2=0;
	hal_gpt_delay_ms(1000);
	ret = sensor_attr_get(dev,SENSOR_CHAN_POS_DZ,QDEC_HW_LATCH_STATUS,&attr_val_get);
	if(ret != 0)
	{
		printk("zephyr get failed\r\n");
	}
	printk("attr_val_get,latch status 0:on going/1:finish = %d\r\n",attr_val_get.val1);
	ret = sensor_attr_get(dev,SENSOR_CHAN_POS_DZ,QDEC_HW_LATCH_STATUS,&attr_val_get);
	if(ret != 0)
	{
		printk("zephyr get failed\r\n");
	}
	printk("attr_val_get,latch status 0:on going/1:finish = %d\r\n",attr_val_get.val1);
	hal_gpt_delay_ms(1000);

		hal_gpt_delay_ms(1000);
	}

while(1);
}




















void hw_qdec_dvt_test_case()
{
    /*fpga setting*/
    *(volatile uint32_t *)0x42020040 = 0x8000;//jixie
    // *(volatile uint32_t *)0x42020040 = 0x0;//guangzhou


    hal_qdec_config_t qdec_test_config = {
        .led_force_off = HAL_QDEC_LED_NO_EFFECT,
        .led_active_output = HAL_QDEC_LED_LOW_ACTIVE,
        .z_sum_thr = 2,
		.group_a_cfg = {
			.smp_period = 3,
			.led_period = 0,
			.dbc_count = 0,
		},
		.group_b_cfg = {
        .smp_period = 10,
        .led_period = 10,
        .dbc_count = 10,
		},
    };

/*reset  dvt test*/
#if 0
    printk("hal_qdec_reset\r\n");
    extern hal_qdec_status_t hal_qdec_deinit();
    extern hal_qdec_status_t hal_qdec_init(hal_qdec_config_t * qdec);
    hal_qdec_init(&qdec_test_config);
    extern hal_qdec_status_t hal_qdec_register_callback(hal_qdec_callback_t callback);
    hal_qdec_register_callback(test_qdeec_callback);
    extern hal_qdec_status_t hal_qdec_enable(void);
    hal_qdec_enable();
    printk("hal_qdec_init. passs\r\n");
    hal_gpt_delay_ms(10000);
#endif

    printk("hal_qdec_reset\r\n");
    extern hal_qdec_status_t hal_qdec_deinit();
    hal_qdec_deinit();
    // hal_gpt_delay_ms(10000);

    printk("hal_qdec_init2. start\r\n");
    extern hal_qdec_status_t hal_qdec_init(hal_qdec_config_t * qdec);
    hal_qdec_init(&qdec_test_config);

/*zcnt test*/
#ifdef ZCNT_MODE
    extern hal_qdec_status_t hal_qdec_zcnt_mode_set(hal_qdec_z_div_setting_t z_div, uint16_t z_cnt_thr);
    hal_qdec_zcnt_mode_set(HAL_QDEC_DIV_OF_Z_COUNT_1_2, 1);
#endif

/*get data type test*/
#ifdef IRQ_TYPE
    extern hal_qdec_status_t hw_qdec_data_getting_type_set(hal_qdec_data_getting_type_t qdec_data_getting_type);
    hw_qdec_data_getting_type_set(HAL_QDEC_READ_DATA_BY_IRQ);
    extern hal_qdec_status_t hal_qdec_register_callback(hal_qdec_callback_t callback);
    hal_qdec_register_callback(test_qdeec_callback);
#else
    int16_t number = 0;
    uint8_t direction = 0;
    extern hal_qdec_status_t hal_qdec_get_data(uint8_t * direction_para, int16_t * number_para);
#endif

    extern hal_qdec_status_t hal_qdec_enable(void);
    hal_qdec_enable();
    printk("hal_qdec_init_2. passs\r\n");

/*group change*/
#if 0
    extern hal_qdec_status_t hal_qdec_select_to_idle_status();
    hal_qdec_select_to_idle_status();
#endif

    positive_direction(4, 10000);
    hal_gpt_delay_ms(10);
    while (1)
    {
        extern hal_qdec_status_t hal_qdec_set_latch_clear();
        hal_qdec_set_latch_clear();
        // // hal_gpt_delay_us(2000);
        hal_gpt_delay_ms(500);

#ifdef IRQ_TYPE

#else
        hal_qdec_get_data(&direction, &number);
        printk("direction=%d,number=%d\r\n", direction, number);
#endif

        printk("main\r\n");
        hal_gpt_delay_ms(100);
        // positive_direction(4,10000);
        positive_direction(8,500);
        // debounce_dvt_test_data();
        // debounce_dvt_test_data2();
        hal_gpt_delay_ms(500);
        printk("\r\n");
    }
}