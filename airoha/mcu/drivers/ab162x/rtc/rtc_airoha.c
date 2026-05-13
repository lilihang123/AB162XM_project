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

#define DT_DRV_COMPAT airoha_air_rtc

#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <errno.h>
#include <zephyr/drivers/rtc.h>
#include "hal_rtc.h"
#include "air_chip.h"
#include <zephyr/logging/log.h>
static bool rtc_first_enable =false;
#define MAX_USER_ID 4
typedef struct{
	uint8_t user_id;
	struct device *user_dev;
	rtc_alarm_callback callback;
	void *user_data;
}rtc_callback_info_t;

struct rtc_airoha_data {
	uint32_t handle[MAX_USER_ID];
	rtc_callback_info_t rtc_callback_info[MAX_USER_ID];
};

void rtc_time_callback_handle(void * user_data){
	rtc_callback_info_t temp_rtc_callback = *(rtc_callback_info_t *)user_data;
	if(temp_rtc_callback.callback != NULL){
		temp_rtc_callback.callback(temp_rtc_callback.user_dev,temp_rtc_callback.user_id,temp_rtc_callback.user_data);
	}
}

static int rtc_airoha_set_time(const struct device *dev, const struct rtc_time *timeptr){
	if(rtc_first_enable == false){
		hal_rtc_enable_time();
		rtc_first_enable = true;
	}
	hal_rtc_time_t time;
	time.rtc_sec = (uint8_t)timeptr->tm_sec;
	time.rtc_min = (uint8_t)timeptr->tm_min;
	time.rtc_hour = (uint8_t)timeptr->tm_hour;
	time.rtc_day = (uint8_t)timeptr->tm_mday;
	time.rtc_mon = (uint8_t)timeptr->tm_mon;
	time.rtc_year = (uint16_t)timeptr->tm_year;
	time.rtc_week = (uint8_t)timeptr->tm_wday;
    time.rtc_milli_sec = (uint16_t)(timeptr->tm_nsec / 1000);
	hal_rtc_set_time(&time);
	return 0;
}

static int rtc_airoha_get_time(const struct device *dev, struct rtc_time *timeptr){
	hal_rtc_time_t time;
	hal_rtc_get_time(&time);
	timeptr->tm_sec = (int)time.rtc_sec;
	timeptr->tm_min = (int)time.rtc_min;
	timeptr->tm_hour = (int)time.rtc_hour;
	timeptr->tm_mday = (int)time.rtc_day;
	timeptr->tm_mon = (int)time.rtc_mon;
	timeptr->tm_year =(int) time.rtc_year;
	timeptr->tm_wday = (int)time.rtc_week;
	timeptr->tm_yday = -1;
	timeptr->tm_isdst = -1;
    timeptr->tm_nsec = (int)(time.rtc_milli_sec * 1000);
	return 0;
}

#if defined(CONFIG_RTC_ALARM) || defined(__DOXYGEN__)
static int rtc_airoha_alarm_set_time(const struct device *dev, uint16_t id, uint16_t mask,const struct rtc_time *timeptr){

	struct rtc_airoha_data *dev_data = dev->data;
	if(id>= MAX_USER_ID){
		return -EIO;
	}
	hal_rtc_status_t status;
	hal_rtc_alarm_get_handle(&(dev_data->handle[id]));
	hal_rtc_time_t time;
	time.rtc_sec = (uint8_t)timeptr->tm_sec;
	time.rtc_min = (uint8_t)timeptr->tm_min;
	time.rtc_hour = (uint8_t)timeptr->tm_hour;
	time.rtc_day = (uint8_t)timeptr->tm_mday;
	time.rtc_mon = (uint8_t)timeptr->tm_mon;
	time.rtc_year = (uint16_t)timeptr->tm_year;
	time.rtc_week = (uint8_t)timeptr->tm_wday;
    time.rtc_milli_sec =(uint16_t)( timeptr->tm_nsec / 1000);
	status  = hal_rtc_set_alarm((dev_data->handle[id]), &time, rtc_time_callback_handle, &(dev_data->rtc_callback_info[id]));
	return status;

}

static int rtc_airoha_alarm_get_time(const struct device *dev, uint16_t id, uint16_t *mask,struct rtc_time *timeptr){

	hal_rtc_time_t time;
	struct rtc_airoha_data *dev_data = dev->data;
	if(id>= MAX_USER_ID){
		return -EIO;
	}
	hal_rtc_get_alarm((dev_data->handle[id]),&time);
	timeptr->tm_sec = (int)time.rtc_sec;
	timeptr->tm_min = (int)time.rtc_min;
	timeptr->tm_hour = (int)time.rtc_hour;
	timeptr->tm_mday = (int)time.rtc_day;
	timeptr->tm_mon = (int)time.rtc_mon;
	timeptr->tm_year =(int) time.rtc_year;
	timeptr->tm_wday = (int)time.rtc_week;
	timeptr->tm_yday = -1;
	timeptr->tm_isdst = -1;
    timeptr->tm_nsec = (int)(time.rtc_milli_sec * 1000);
	return 0;
}

static int rtc_airoha_alarm_set_callback(const struct device *dev, uint16_t id,rtc_alarm_callback callback, void *user_data){
	struct rtc_airoha_data *dev_data = dev->data;
	if(id>= MAX_USER_ID){
		return -EIO;
	}
	dev_data->rtc_callback_info[id].user_id = (uint8_t)id;
	dev_data->rtc_callback_info[id].user_dev = (struct device *)dev;
	dev_data->rtc_callback_info[id].callback = callback;
	dev_data->rtc_callback_info[id].user_data = user_data;
	return 0;
}
#endif /* CONFIG_RTC_ALARM */
static int rtc_init(const struct device *dev)
{
	hal_rtc_init();
	return 0;
}

static const struct rtc_driver_api rtc_airoha_driver_api = {
	.set_time = rtc_airoha_set_time,
	.get_time = rtc_airoha_get_time,
#if defined(CONFIG_RTC_ALARM) || defined(__DOXYGEN__)
	.alarm_set_time = rtc_airoha_alarm_set_time,
	.alarm_get_time = rtc_airoha_alarm_get_time,
	.alarm_set_callback = rtc_airoha_alarm_set_callback,
#endif /* CONFIG_RTC_ALARM */
};

#define	RTC_AIROHA_DEVICE(id)						\
static struct rtc_airoha_data rtc_airoha_p##id##_data;		\
DEVICE_DT_INST_DEFINE(id,						\
	    rtc_init,						\
	    NULL,							\
	    &rtc_airoha_p##id##_data,					\
	    NULL, 					\
	    CONFIG_RTC_INIT_LEVEL, CONFIG_RTC_INIT_PRIORITY, &rtc_airoha_driver_api);

DT_INST_FOREACH_STATUS_OKAY(RTC_AIROHA_DEVICE)
