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


#include <zephyr/irq.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/types.h>
#include <stddef.h>
#include <sys/types.h>
#include <zephyr/device.h>

/* WDT interface required by the zephyr. */
#include <zephyr/drivers/watchdog.h>
#include <zephyr/sys/__assert.h>

#include "hal_pmu.h"
#include "hal_wdt.h"
#include "hal_wdt_internal.h"
#include "memory_attribute.h"

#include "wdt_airoha.h"

/* zephyr/lib/libc/minimal/include/errno.h */
#include <errno.h>

#define DT_DRV_COMPAT airoha_air_wdt


#define WDT_DATA(_device) \
        ((wdt_air_data_t*)((_device)->data))


#define WDT_0 device_get_binding(DEVICE_DT_NAME(DT_NODELABEL(wdt0)))
#define WDT_1 device_get_binding(DEVICE_DT_NAME(DT_NODELABEL(wdt1)))

#define DBG_HANG_WDT_RESET_MODE_AND_PMU_WARM_RESET 0

#if DBG_HANG_WDT_RESET_MODE_AND_PMU_WARM_RESET
    #define WDT_DEFAULT_MODE HAL_WDT_MODE_RESET
#else
    #define WDT_DEFAULT_MODE HAL_WDT_MODE_INTERRUPT
#endif

static int wdt_airoha_setup(const struct device *dev, uint8_t options)
{
    printk("wdt_airoha_setup was called\r\n");
    if (options & WDT_OPT_PAUSE_IN_SLEEP) {
        wdt_set_core_mask(true);
    }

    /* Deactivate running when debugger is attached. */
    if (options & WDT_OPT_PAUSE_HALTED_BY_DBG) {
        wdt_set_jtag_mask(true);
        printk("wdt_set_jtag_mask was called\r\n");
    }

    if(WDT_DATA(dev)->m_channel == 0){
        hal_wdt_enable(HAL_WDT_ENABLE_MAGIC);
        printk("hal_wdt_enable was called with ch 0\r\n");
    }
#ifdef CONFIG_AIR_WDT_2ND
    else if (WDT_DATA(dev)->m_channel == 1) {
        hal_wdt_enable_ext(HAL_WDT_ENABLE_MAGIC);
        printk("hal_wdt_enable was called with ch 1\r\n");
    }
#endif
    else {
        __ASSERT(false, "Error: wrong wdt device 0x%08X\r\n", (unsigned int)dev);
    }

#if DBG_HANG_WDT_RESET_MODE_AND_PMU_WARM_RESET
    pmu_strup_rg_unlock();
    pmu_set_strup_rg_value(45, 0x1, 8, 0x0);
    pmu_get_strup_rg(45);
    pmu_strup_rg_lock();
    printk("configure pmu as warm reset");
#endif

    printk("[mcu][pc][s]    0x%x\r\n", *((volatile unsigned int *)(CMSYS_CFG_BASE + 0x1000)));
    printk("[mcu][lr][s]    0x%x\r\n", *((volatile unsigned int *)(CMSYS_CFG_BASE + 0x1008)));
    printk("[mcu][pc][ns]   0x%x\r\n", *((volatile unsigned int *)(CMSYS_CFG_BASE + 0x1004)));
    printk("[mcu][lr][ns]   0x%x\r\n", *((volatile unsigned int *)(CMSYS_CFG_BASE + 0x100C)));

    return 0;
}

static int wdt_airoha_disable(const struct device *dev)
{
    printk("wdt_airoha_disable was called\r\n");
    if(WDT_DATA(dev)->m_channel == 0){
        hal_wdt_disable(HAL_WDT_DISABLE_MAGIC);
        hal_wdt_deinit();
    }
#ifdef CONFIG_AIR_WDT_2ND
    else if (WDT_DATA(dev)->m_channel == 1) {
        hal_wdt_disable_ext(HAL_WDT_DISABLE_MAGIC);
        hal_wdt_deinit_ext();
    }
#endif
    else {
        __ASSERT(false, "Error: wrong wdt device 0x%08X\r\n", (unsigned int)dev);
    }
    return 0;
}

ATTR_WEAK_SYMBOL void wdt_zephyr_callback(const struct device *dev, int channel_id)
{
    printk("wdt_zephyr_callback was called with dev: 0x%08X\r\n", (unsigned int)dev);
    printk("WDT Channel: %d\r\n", WDT_DATA(dev)->m_channel);
    if(WDT_DATA(dev)->m_channel == 0){
        __ASSERT(false, "WDT Channel 0 Timeout!!!\r\n");
    }
#ifdef CONFIG_AIR_WDT_2ND
    else if (WDT_DATA(dev)->m_channel == 1) {
        __ASSERT(false, "WDT Channel 1 Timeout!!!\r\n");
    }
#endif
    else {
        __ASSERT(false, "Error: wrong wdt device 0x%08X\r\n", (unsigned int)dev);
    }
}

static void wdt_callback_zephyr2air_wrapper_0(hal_wdt_reset_status_t status)
{
    wdt_zephyr_callback(WDT_0, 0);
}

#ifdef CONFIG_AIR_WDT_2ND
static void wdt_callback_zephyr2air_wrapper_1(hal_wdt_reset_status_t status)
{
    wdt_zephyr_callback(WDT_1, 0);
}
#endif

static int wdt_airoha_install_timeout(const struct device *dev,
                   const struct wdt_timeout_cfg *cfg)
{
    uint32_t ret_reset_status;
    hal_wdt_config_t wdt_config;
    hal_wdt_status_t op_ret;

    printk("wdt_airoha_install_timeout was called\r\n");
    if(IS_ENABLED(CONFIG_WDT_MULTISTAGE)){
        return -ENOTSUP;
    }
    if(cfg->window.min != 0){
        return -ENOTSUP;
    }

    if(WDT_DATA(dev)->m_channel == 0){
        ret_reset_status = hal_wdt_get_reset_status();
        printk("ret_reset_status is %d\r\n", ret_reset_status);
        wdt_config.mode = WDT_DATA(dev)->m_mode;
        wdt_config.seconds = cfg->window.max;
        printk("wdt_config.seconds is %d\r\n", wdt_config.seconds);

        if(cfg->callback){
            hal_wdt_register_callback(wdt_callback_zephyr2air_wrapper_0);
            printk("hal_wdt_register_callback ch 0\r\n");
        }

        op_ret = hal_wdt_init(&wdt_config);
        printk("hal_wdt_init return %d\r\n", op_ret);
        if(HAL_WDT_STATUS_OK != op_ret) {
            return (int)op_ret;
        }
    }
#ifdef CONFIG_AIR_WDT_2ND
    else if (WDT_DATA(dev)->m_channel == 1) {
        ret_reset_status = hal_wdt_get_reset_status();
        printk("ret_reset_status is %d\r\n", ret_reset_status);
        wdt_config.mode = WDT_DATA(dev)->m_mode;
        wdt_config.seconds = cfg->window.max;
        printk("wdt_config.seconds is %d\r\n", wdt_config.seconds);

        if(cfg->callback){
            hal_wdt_register_callback_ext(wdt_callback_zephyr2air_wrapper_1);
            printk("hal_wdt_register_callback ch 1\r\n");
        }

        op_ret = hal_wdt_init_ext(&wdt_config);
        printk("hal_wdt_init_ext return %d\r\n", op_ret);
        if(HAL_WDT_STATUS_OK != op_ret) {
            return (int)op_ret;
        }
    }
#endif
    else {
        __ASSERT(false, "Error: wrong wdt device 0x%08X with channel %d\r\n", (unsigned int)dev, WDT_DATA(dev)->m_channel);
    }

    return 0;
}


static int wdt_airoha_feed(const struct device *dev, int channel_id)
{
    uint32_t lr = (uint32_t)__builtin_return_address(0);
    // printk("[WDT] wdt_airoha_feed was called by 0x%08X\r\n", (unsigned int)lr);
    if(WDT_DATA(dev)->m_channel == 0){
        hal_wdt_feed(HAL_WDT_FEED_MAGIC);
        WDT_DATA(dev)->m_feed_caller = lr;
        WDT_DATA(dev)->m_feed_tick = k_uptime_get_32();
    }
#ifdef CONFIG_AIR_WDT_2ND
    else if (WDT_DATA(dev)->m_channel == 1) {
        hal_wdt_feed_ext(HAL_WDT_FEED_MAGIC);
        WDT_DATA(dev)->m_feed_caller = lr;
        WDT_DATA(dev)->m_feed_tick = k_uptime_get_32();
    }
#endif
    else {
        __ASSERT(false, "Error: wrong wdt device 0x%08X\r\n", (unsigned int)dev);
    }
    // printk("[WDT] wdt_airoha_feed ended with status %d\r\n", (int)status);
    return 0;
}


static const struct wdt_driver_api wdt_airoha_driver_api = {
    .setup = wdt_airoha_setup,
    .disable = wdt_airoha_disable,
    .install_timeout = wdt_airoha_install_timeout,
    .feed = wdt_airoha_feed,
};


#define AIR_WDT_DTS_LABEL(idx) DT_NODELABEL(wdt##idx)


#define WDT_AIROHA_DEVICE(idx)                                              \
    static wdt_air_data_t wdt_##idx##_data = {                              \
        .m_mode = WDT_DEFAULT_MODE,                                         \
        .m_options = WDT_OPT_PAUSE_IN_SLEEP | WDT_OPT_PAUSE_HALTED_BY_DBG,  \
        .m_channel = idx                                                    \
    };                                                                      \
    static const struct wdt_timeout_cfg wdt_##idx##_config = {              \
        .window = { 0, (uint32_t)DT_INST_PROP(idx, timeout_sec) },          \
        .callback = wdt_zephyr_callback,                                    \
        .flags = WDT_FLAG_RESET_SOC                                         \
    };                                                                      \
    _Static_assert(                                                         \
        (uint32_t)DT_INST_PROP(idx, timeout_sec) >=                         \
        CONFIG_AIR_WDT_TIMEOUT_SEC_MIN,                                     \
        "WDT timeout too small");                                           \
    _Static_assert(                                                         \
        (uint32_t)DT_INST_PROP(idx, timeout_sec) <=                         \
        CONFIG_AIR_WDT_TIMEOUT_SEC_MAX,                                     \
        "WDT timeout too big");                                             \
    static int wdt_##idx##_init(const struct device *dev)                   \
    {                                                                       \
        int op_ret = 0;                                                     \
        printk("wdt_%d_init was called \r\n", idx);                         \
        op_ret = wdt_install_timeout(dev, &wdt_##idx##_config);             \
        __ASSERT_NO_MSG(op_ret == 0);                                       \
        op_ret = wdt_setup(dev, wdt_##idx##_data.m_options);                \
        printk("wdt_%d_init and return %d \r\n", idx, op_ret);              \
        return 0;                                                           \
    }                                                                       \
    DEVICE_DT_DEFINE(AIR_WDT_DTS_LABEL(idx),                                \
                wdt_##idx##_init,                                           \
                NULL,                                                       \
                &wdt_##idx##_data,                                          \
                &wdt_##idx##_config,                                        \
                CONFIG_WDT_INIT_LEVEL, CONFIG_WDT_INIT_PRIORITY,            \
                &wdt_airoha_driver_api)


#ifdef CONFIG_AIR_WDT
WDT_AIROHA_DEVICE(0);
#endif

#ifdef CONFIG_AIR_WDT_2ND
WDT_AIROHA_DEVICE(1);
#endif

