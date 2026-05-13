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
#include <zephyr/drivers/rtc.h>

#include <stdio.h>
#include <string.h>

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

#define CONFIG_TEST_RTC_ALARM_TIME_MASK (0x1FF)

#define RTC_TEST_ALARM_TEST_NOT_PENDING_DELAY (3)
#define RTC_TEST_ALARM_TEST_PENDING_DELAY     (10)

static const struct device *rtc = DEVICE_DT_GET(DT_NODELABEL(rtc));
//static const uint16_t alarms_count = 4;
static const uint16_t test_alarm_time_mask_set = CONFIG_TEST_RTC_ALARM_TIME_MASK;

// static const uint16_t test_alarm_time_masks[] = {
// 	RTC_ALARM_TIME_MASK_SECOND,  RTC_ALARM_TIME_MASK_MINUTE,
// 	RTC_ALARM_TIME_MASK_HOUR,    RTC_ALARM_TIME_MASK_MONTHDAY,
// 	RTC_ALARM_TIME_MASK_MONTH,   RTC_ALARM_TIME_MASK_YEAR,
// 	RTC_ALARM_TIME_MASK_WEEKDAY, RTC_ALARM_TIME_MASK_YEARDAY,
// 	RTC_ALARM_TIME_MASK_NSEC
// };

uint16_t alarm_id = 0;

/* Fri Jan 01 2021 13:29:50 GMT+0000 */
static const struct rtc_time test_rtc_time_set = {
	.tm_sec = 50,
	.tm_min = 29,
	.tm_hour = 13,
	.tm_mday = 1,
	.tm_mon = 0,
	.tm_year = 121,
	.tm_wday = 5,
	.tm_yday = 1,
	.tm_isdst = -1,
	.tm_nsec = 0,
};

/* Fri Jan 01 2021 13:30:00 GMT+0000 */
static const struct rtc_time test_alarm_time_set = {
	.tm_sec = 0,
	.tm_min = 30,
	.tm_hour = 13,
	.tm_mday = 1,
	.tm_mon = 0,
	.tm_year = 121,
	.tm_wday = 5,
	.tm_yday = 1,
	.tm_isdst = -1,
	.tm_nsec = 0,
};


void alarm_callback(const struct device *rtc_dev, uint16_t id, void *user_data)
{
    printk("Alarm callback called\n");
    printk("------------------------------------");
}

void print_rtc_handle(const struct rtc_time *time_handle)
{
    if (time_handle == NULL) {
        printk("invalid rtc_time handle\n");
        return;
    }

    printk("tm_sec:%d tm_min:%d tm_hour:%d \
        tm_mday:%d tm_mon:%d tm_year:%d \
        tm_wday:%d tm_yday:%d tm_isdst:%d tm_nsec:%d\n", \
        time_handle->tm_sec, time_handle->tm_min, time_handle->tm_hour, \
        time_handle->tm_mday, time_handle->tm_mon, time_handle->tm_year, \
        time_handle->tm_wday, time_handle->tm_yday, time_handle->tm_isdst, \
        time_handle->tm_nsec);
}

void zephyr_rtc_test(void)
{
    printk("-------------------zephyr rtc test----------------\n");
    int ret;
    uint16_t alarm_time_mask_get = 0;
    struct rtc_time alarm_time_get;
    memset(&alarm_time_get, 0, sizeof(struct rtc_time));
    ret = rtc_set_time(rtc, &test_rtc_time_set);
    if (ret != 0) {
        printk("Failed to set RTC time, ret = %d", ret);
    } else {
        printk("RTC time set successfully");
        print_rtc_handle(&test_rtc_time_set);
    }
    struct rtc_time current_time = {0};
    ret = rtc_get_time(rtc, &current_time);
    if (ret != 0) {
        printk("Failed to get RTC time, ret = %d", ret);
    } else {
        printk("get Current RTC time successed");
        print_rtc_handle(&current_time);
    }
    ret = rtc_alarm_set_time(rtc, alarm_id, 0, &test_alarm_time_set);
    if (ret != 0) {
        printk("Failed to set alarm: %d\n", ret);
    } else {
        printk("Alarm init successfully\n");
    }
    ret = rtc_alarm_set_callback(rtc, alarm_id, alarm_callback, NULL);
    if (ret != 0) {
        printk("set alarm callback failed:%d\n", ret);
    } else {
        printk("set alarm callback success\n");
    }
    ret = rtc_alarm_set_time(rtc, alarm_id, test_alarm_time_mask_set, &test_alarm_time_set);
    if (ret != 0) {
        printk("Failed to set alarm time: %d\n", ret);
    } else {
        printk("Alarm time set successfully,mask: %x", test_alarm_time_mask_set);
        print_rtc_handle(&test_alarm_time_set);
    }
    /*This api is used to obtain how much times is left for the alarm to trigger*/
    printk("before get alarm time");
    print_rtc_handle(&alarm_time_get);
    ret = rtc_alarm_get_time(rtc, alarm_id, &alarm_time_mask_get, &alarm_time_get);
    if (ret != 0) {
        printk("Failed to get alarm time: %d\n", ret);
    } else {
        printk("Get alarm time successfully,mask: %x", alarm_time_mask_get);
        print_rtc_handle(&alarm_time_get);
    }
}

void feed_watch_dog(void);

int main(void)
{
    zephyr_rtc_test();

    for(;;){
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