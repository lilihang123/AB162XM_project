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

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "air_chip.h"
#include "hal_platform.h"

#include "led_middle_control.h"
#include "led_control_style_cfg.h"

#if defined(HAL_GPT_MODULE_ENABLED)
#include "hal_gpt.h"
#endif

#include "memory_attribute.h"
#include "autoconf.h"

#ifdef CONFIG_AIR_WDT
#include "wdt_airoha.h"
#endif

void feed_watch_dog(void);

#define FADE_DELAY_MS	5000
#define FADE_DELAY	K_MSEC(FADE_DELAY_MS)


one_led_style_t   led_default_pattern_setting[] = {
    /* t0,  t1_rising   t1_lightest     t2_falling     t2_darkest  t3   repeat_t1t2  repeat_ext  brightness  start_brightness  end_brightness     onoff*/
    /* no.0  Constant on */
    { 0,       0,          0,              0,             0,       0,       1,            3,        125,          0,                 0,           LED_ON },
    /* no.1  1-time flash */
    { 0,       0,          0,              0,             0,       0,       0,            0,        0,            0,                 0,           LED_OFF},
    /* no.2  2-times flash  */
    { 0,     200,        100,            200,           500,       0,       2,            1,        150,          0,                 0,           LED_ON },
    /* no.3  Continuous 2-times flash */
    { 0,     200,        100,            200,           500,    1000,       2,          255,        150,          0,                 0,           LED_ON },
    /* no.4  Continuous slow breathing light */
    { 0,     500,        500,            500,             0,       0,      10,          255,        150,          0,                 0,           LED_ON },
    /* no.5  Continuous quick flash */
    { 0,     200,        100,              0,           200,       0,      10,          255,        150,          0,                 0,           LED_ON },
    /* no.6  1-time quick flash */
    { 0,     200,        100,              0,           200,       0,       1,            1,        150,          0,                 0,           LED_ON },
    /* no.7  2-times quick flash */
    { 0,     200,        100,              0,           200,       0,       2,            1,        150,          0,                 0,           LED_ON },
    /* no.8  No light (0.5s)*/
    { 0,       0,          0,              0,             0,     500,       1,            1,          0,          0,                 0,           LED_ON },
    /* no.9  No light (1s)*/
    { 0,       0,          0,              0,             0,    1000,       1,            1,          0,          0,                 0,           LED_ON },
};

void led_middle_test(void)
{
    printk("--------------------led_middle_test start------------------\n");
    led_middle_status_t ret;

    /*para1:led_num para3:the index of led_default_pattern_setting */
    ret = led_middle_control_enable(0, LED_PATTERN_BG, 0, false);
    if (ret != LED_MIDDLE_STATUS_OK) {
        printk("led4 control enable fail\n");
        return;
    }
    printk("led4 control enable success\n");

    ret = led_middle_control_enable(1, LED_PATTERN_BG, 4, false);
    if (ret != LED_MIDDLE_STATUS_OK) {
        printk("led5 control enable fail\n");
        return;
    }
    printk("led5 control enable success\n");

    ret = led_middle_control_enable(2, LED_PATTERN_BG, 5, false);
    if (ret != LED_MIDDLE_STATUS_OK) {
        printk("led6 control enable fail\n");
        return;
    }
    printk("led6 control enable success\n");

    k_sleep(FADE_DELAY);

    feed_watch_dog();
    // ret = led_middle_control_enable(0, LED_PATTERN_BG, 1, false);
    ret = led_middle_control_disable(0, LED_PATTERN_BG, false);
    if (ret != LED_MIDDLE_STATUS_OK_DONE) {
        printk("led4 disable fail, ret: %d\n", ret);
    } else {
        printk("led4 disable success\n");
    }

    ret = led_middle_control_disable(1, LED_PATTERN_BG, false);
    if (ret != LED_MIDDLE_STATUS_OK_DONE) {
        printk("led5 disable fail\n");
    } else {
        printk("led5 disable success\n");
    }

    ret = led_middle_control_disable(2, LED_PATTERN_BG, false);
    if (ret != LED_MIDDLE_STATUS_OK_DONE) {
        printk("led6 disable fail\n");

    } else {
        printk("led6 disable success\n");
    }
}

int main(void)
{
    led_middle_test();
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