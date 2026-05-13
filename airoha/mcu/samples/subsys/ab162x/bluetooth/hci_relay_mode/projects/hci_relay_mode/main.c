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
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
 * RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
 * TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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

#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/drivers/uart.h>
#define LOG_LEVEL LOG_LEVEL_DEBUG
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main);

#include "hal_platform.h"
#include "hal_gpt.h"

#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/drivers/sensor.h>

#include "memory_attribute.h"

//#include "autoconf.h"
#include "bt_debug.h"
#include "mouse_sensor.h"

#ifdef CONFIG_AIR_WDT
#include "wdt_airoha.h"
#endif
#include "hal_spm.h"
#define DIRECT_ACCESS_HAL
#define MCU_STRESS_WKUP_CONNSYS_TEST   (false)

K_HEAP_DEFINE(test_heap, 32*1024);
K_HEAP_DEFINE_NOCACHE(test_nc_heap, 7*1024);

#include <zephyr/storage/flash_map.h>




ATTR_RODATA_IN_TCM uint32_t tcm_ro_data = 0x12345678;
ATTR_RWDATA_IN_TCM uint32_t tcm_rw_data = 0x87654321;
ATTR_ZIDATA_IN_TCM uint32_t tcm_zi_data;

#if !defined(CONFIG_SOC_SERIES_AB162X)
ATTR_RWDATA_IN_NONCACHED_SYSRAM uint32_t nc_sram_rw_data = 0xA5A5A5A5;
ATTR_ZIDATA_IN_NONCACHED_SYSRAM uint32_t nc_sram_zi_data;
#endif

ATTR_SHARE_RWBT uint32_t sram_bt_rw_data = 0x11223344;
ATTR_SHARE_ZIBT_16BYTE_ALIGN uint32_t sram_bt_zi_data;

#if (MCU_STRESS_WKUP_CONNSYS_TEST != false)
#include "hal_rtc.h"
#define LC_SLEEP_WKUP_RETRY_CNT     (4)
uint32_t relay_rtc_handle = 0x00;
uint64_t relay_rtc_sleep_time_ms = 40;
void relay_set_sleep_time_rtc_int(void);
void relay_sleep_callback_rtc(void);
void relay_set_sleep_time_rtc(void);
extern void LC_SoftwareInt_Wakeup(void);

void relay_set_sleep_time_rtc_int(void)
{
    hal_rtc_enable_time();
    hal_rtc_alarm_get_handle(&relay_rtc_handle);
    relay_set_sleep_time_rtc();
}

void relay_sleep_callback_rtc(void)
{
    for (uint8_t retry_wkup_cnt = 0; retry_wkup_cnt < LC_SLEEP_WKUP_RETRY_CNT; retry_wkup_cnt++) {
        hal_gpt_delay_us(2000);
        LC_SoftwareInt_Wakeup();
    }
    relay_set_sleep_time_rtc();
}

void relay_set_sleep_time_rtc(void)
{
    hal_rtc_stop_alarm(relay_rtc_handle); /* hal_gpt_sw_start_timer_ms clk souce = 32M*/
    hal_rtc_set_alarm_ms(relay_rtc_handle, relay_rtc_sleep_time_ms, (hal_rtc_time_callback_t)relay_sleep_callback_rtc, NULL);
}
#endif /* #if (MCU_STRESS_WKUP_CONNSYS_TEST != FALSE) */


extern void relay_client_init();


void print_live(uint32_t interval)
{
   	uint32_t time_stamp_32 = k_uptime_get_32();
	uint32_t milliseconds_spent = 0;
	while (1)
	{
		milliseconds_spent = k_uptime_get_32() - time_stamp_32;

		if (milliseconds_spent>=interval)
		{
            BT_LOGI("Main", "Date : 0903...\n");
			time_stamp_32 = k_uptime_get_32();
		}
	}
}


const struct device *paw3395;
int main(void)
{
    // for dual device test uart setting changed by coretracer loading fixed addr
    //uint32_t gRelayUartPort = *(uint16_t*)(0xA0010480) & 0xff;
    uint8_t gRelayUartPort = 2;

#ifdef CONFIG_PIXART_PAW3395
    paw3395 = DEVICE_DT_GET(DT_NODELABEL(paw3395));
    sensor_attr_set(paw3395, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_INIT, NULL); //paw3395 init

    struct sensor_value val;
    val.val1=0;
    val.val2=0;
    sensor_attr_set(paw3395, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_SPI_NVIC_IRQ, &val); //close mcu spi irq

    struct sensor_value val_bt;
    val.val1=1;
    val.val2=0;
    sensor_attr_set(paw3395, SENSOR_CHAN_ALL, MOUSE_SENSOR_ATTR_BT_TRIGGER, &val_bt); //paw3395 bt trigger
#if 0
    if (paw3395 == NULL) {
        BT_LOGI("NOT found 3395\n");
    } else {
        sensor_sample_fetch(paw3395);
    }
#endif
#endif

    relay_client_init(gRelayUartPort);
#if (MCU_STRESS_WKUP_CONNSYS_TEST != FALSE)
    relay_set_sleep_time_rtc_int();
#endif
    BT_LOGI("Main", "=========== Relay Mode Init Completed ===========\n");

    //print_live(4000);
	return 0;
}


