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
#include <zephyr/sys/util.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/gpio/gpio_utils.h>

#ifdef CONFIG_AIR_WDT
#include "wdt_airoha.h"
#endif
#include "hal_dvfs.h"
#include "hal_gpio.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_platform.h"
#include "ot_performance_plat.h"
#if CONFIG_OPENTHREAD_CLI_EXTENSION
#include "ot_cli_extension.h"
#endif


static uint8_t s_factory_reset_count = 0;

#define OT_DEVICE_TYPE_FACTORY_RESET_PIN   HAL_GPIO_21
#define OT_DEVICE_TYPE_GPIO_PIN            HAL_GPIO_23
#define OT_WDT_TIMER_EXPIRE_TIME          (10)  /* 10s */
#define OT_WDT_TIMER_FACTORY_RESET_TIME    (2)  /* 2s */

typedef void (*CB)();
void feed_watch_dog(void);
void openthread_wdt_timer_callback(struct k_timer *timer_id);
static void factory_reset_timer_callback(struct k_timer *timer);
void FactoryReset(struct k_work *work);
static K_WORK_DEFINE(factoryreset, FactoryReset);

static struct gpio_callback s_factory_button_gpio_cb;
struct k_timer openthread_wdt_timer_handle;
struct k_timer factory_reset_timer_handle;
K_TIMER_DEFINE(openthread_wdt_timer_handle, openthread_wdt_timer_callback, NULL);
K_TIMER_DEFINE(factory_reset_timer_handle, factory_reset_timer_callback, NULL);
void openthread_wdt_timer_callback(struct k_timer *timer_id)
{
    // printk("OT WDT feed watch log!  10s\r\n");
    k_timer_start(&openthread_wdt_timer_handle, K_SECONDS(OT_WDT_TIMER_EXPIRE_TIME), K_MSEC(OT_WDT_TIMER_EXPIRE_TIME));
    feed_watch_dog();
}

void feed_watch_dog(void)
{
#ifdef CONFIG_AIR_WDT
    const struct device *wdt_dev = \
        device_get_binding(DEVICE_DT_NAME(DT_NODELABEL(wdt0)));
    __ASSERT_NO_MSG(wdt_dev != NULL);
    int wdt_ch = ((wdt_air_data_t*)(wdt_dev->data))->m_channel;
    // printk("wdt_feed was called with dev: 0x%08X and channel %d\r\n", (unsigned int)wdt_dev, wdt_ch);
    wdt_feed(wdt_dev, wdt_ch);
#endif

#ifdef CONFIG_AIR_WDT_2ND
    const struct device *wdt_dev_1 = \
        device_get_binding(DEVICE_DT_NAME(DT_NODELABEL(wdt1)));
    __ASSERT_NO_MSG(wdt_dev_1 != NULL);
    int wdt_ch_1 = ((wdt_air_data_t*)(wdt_dev_1->data))->m_channel;
    printk("wdt_feed was called with dev: 0x%08X and channel %d\r\n", (unsigned int)wdt_dev_1, wdt_ch_1);
    wdt_feed(wdt_dev_1, wdt_ch_1);
#endif
}

void FactoryReset(struct k_work *work)
{
    ot_performance_factory_reset();
}

static void factory_reset_timer_callback(struct k_timer *timer)
{
	if (!timer) {
		return;
	}

	if (timer == &factory_reset_timer_handle) {
		s_factory_reset_count = 0;
	}
}

void ButtonInit(uint8_t button_pin, struct gpio_callback *gpio_cb, CB app_cb)
{
	gpio_init_callback(gpio_cb, (gpio_callback_handler_t)app_cb, BIT(button_pin));

	const struct device *gpio_dev = device_get_binding(DT_NODE_FULL_NAME(DT_NODELABEL(gpio0)));
	gpio_pin_configure(gpio_dev, button_pin, GPIO_INPUT);
	gpio_pin_interrupt_configure(gpio_dev, button_pin, GPIO_INT_MODE_EDGE | GPIO_INT_LOW_0);
	gpio_add_callback(gpio_dev, gpio_cb);
}

void FactoryResetButtonHandler()
{
	if (s_factory_reset_count < 2) {
		s_factory_reset_count++;
	}
	if (s_factory_reset_count == 2) {
		s_factory_reset_count = 0;
        k_work_submit(&factoryreset);
		k_timer_stop(&factory_reset_timer_handle);
	} else if (s_factory_reset_count == 1) {
		k_timer_start(&factory_reset_timer_handle, K_SECONDS(OT_WDT_TIMER_FACTORY_RESET_TIME), K_NO_WAIT);
	}
}

void set_ot_device_mode(void)
{
    otLinkModeConfig OT_LinkMode = { 0 };
    hal_gpio_data_t gpio_data;
    hal_gpio_get_input(OT_DEVICE_TYPE_GPIO_PIN, &gpio_data);
    if (gpio_data == HAL_GPIO_DATA_HIGH) {
/* FTD */
        printk("[OT_PERF] set_ot_device_mode FTD \r\n");
        OT_LinkMode.mRxOnWhenIdle = 1;
        OT_LinkMode.mDeviceType   = 1;
    } else {
/* MTD */
        printk("[OT_PERF] set_ot_device_mode MTD \r\n");
        OT_LinkMode.mRxOnWhenIdle = 0;
        OT_LinkMode.mDeviceType   = 0;
    }
    OT_LinkMode.mNetworkData  = 1U;
    ot_performace_set_device_mode(&OT_LinkMode);
}

extern void IEEE802154_Controller_DisableBle(void);
int main(void)
{
    printk("[OT_PERF] OT Performance Test Main \r\n");
    hal_dvfs_lock_control(HAL_DVFS_OPP_HIGH, HAL_DVFS_LOCK);
    //hal_sleep_manager_lock_extslp(SLEEP_LOCK_EXTEND_APP);
    hal_sleep_manager_lock_sleep(SLEEP_LOCK_BT_CONTROLLER);

    k_timer_start(&openthread_wdt_timer_handle, K_SECONDS(OT_WDT_TIMER_EXPIRE_TIME), K_MSEC(OT_WDT_TIMER_EXPIRE_TIME));
    IEEE802154_Controller_DisableBle();
    /* Init Custom Cli CMD[Iperf] */
#if CONFIG_OPENTHREAD_CLI_EXTENSION
    air_cli_custom_command_init();
#endif
    /* Init Button */
    ButtonInit(OT_DEVICE_TYPE_FACTORY_RESET_PIN, &s_factory_button_gpio_cb, FactoryResetButtonHandler);
    /* Init led */

    /* Register OT state changed Callback */
    ot_performace_state_event_init();

    /* Set Device Type */
    set_ot_device_mode();

    /* set router selection jitter */
    ot_performance_set_router_selection_jitter(5);

    /* Get Dataset */
    otOperationalDatasetTlvs dataset;
    otError error = ot_performace_get_active_tlvs(&dataset);

    /* Start OpenThread */
    ot_performace_start_openthread((error == OT_ERROR_NONE) ? &dataset : NULL);


    return 0;
}
