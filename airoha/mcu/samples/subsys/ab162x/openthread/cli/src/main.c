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
#ifdef CONFIG_AIR_WDT
#include "wdt_airoha.h"
#endif
#include "hal_dvfs.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_platform.h"
#if CONFIG_OPENTHREAD_CLI_EXTENSION
#include "ot_cli_extension.h"
#endif
#include "avm_external.h"
#include "hal_spm.h"

#define OT_WDT_TIMER_EXPIRE_TIME          (10)  /* 10s */
#define RELAY_CLIENT_PORT 2
void feed_watch_dog(void);
void relay_client_init(uint32_t uart_port);
void openthread_wdt_timer_callback(struct k_timer *timer_id);

struct k_timer openthread_wdt_timer_handle;
K_TIMER_DEFINE(openthread_wdt_timer_handle, openthread_wdt_timer_callback, NULL);
extern void IEEE802154_Controller_DisableBle(void);
#define OT_PERFORMANCE_TEST

int main(void)
{
    printk("OT CLI INIT! %s\r\n", CONFIG_BOARD);
    relay_client_init(RELAY_CLIENT_PORT);
#if CONFIG_OPENTHREAD_CLI_EXTENSION
    air_cli_custom_command_init();
#endif
#ifdef OT_PERFORMANCE_TEST
    hal_dvfs_lock_control(HAL_DVFS_OPP_HIGH, HAL_DVFS_LOCK);
    //hal_sleep_manager_lock_extslp(SLEEP_LOCK_EXTEND_APP);
    hal_sleep_manager_lock_sleep(SLEEP_LOCK_BT_CONTROLLER);
    k_timer_start(&openthread_wdt_timer_handle, K_SECONDS(OT_WDT_TIMER_EXPIRE_TIME), K_MSEC(OT_WDT_TIMER_EXPIRE_TIME));
    IEEE802154_Controller_DisableBle();
#else
    bt_sleep_policy_t policy;
    policy.slp_policyctl = BT_AVM_CHANGE_SLP_POLICY;
    policy.slp_policy = BT_AVM_ENABLE_DEEP_SLEEP;
    bt_set_controller_sleep_policy_direct(&policy);
    spm_control_mtcmos(SPM_MTCMOS_RTCSYS, SPM_MTCMOS_PWR_DISABLE);
    hal_dvfs_lock_control(HAL_DVFS_OPP_MID, HAL_DVFS_LOCK);
    IEEE802154_Controller_DisableBle();
#endif
    return 0;
}

void openthread_wdt_timer_callback(struct k_timer *timer_id)
{
    printk("OT WDT feed watch log!  10s\r\n");
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