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

#include "zephyr/sys/__assert.h"
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/init.h>
#if IS_ENABLED(CONFIG_AIR_DAEMON_WORKQUEUE_ENABLE)
#include "air_daemon_work_q.h"
#endif
#include <stdint.h>
#include <soc.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "air_chip.h"
#include "hal_log.h"
#include "hal_gpio.h"
#include "hal_gpt.h"
#include "hal_gpt_internal.h"
#include "memory_attribute.h"
#include "bm_core.h"
#include "bm_cust.h"

#ifdef AIR_NVKEY_ENABLE
#include "nvkey.h"
#include "nvkey_id_def.h"
#endif


#ifdef AIR_BATTERY_MANAGEMENT_ENABLE
#if defined(__EXT_BOOTLOADER__) || defined(__EXT_DA__)
#define log_bm_info(msg, cnt, ...)
#define log_bm_warn(msg, cnt, ...)
#define log_bm_error(msg, cnt, ...)
#else
#define log_bm_info(msg, cnt, ...)             printk("[BM_CORE] "msg"\r\n", ##__VA_ARGS__)
#define log_bm_warn(msg, cnt, ...)             printk("[BM_CORE] "msg"\r\n", ##__VA_ARGS__)
#define log_bm_error(msg, cnt, ...)            printk("[BM_CORE] "msg"\r\n", ##__VA_ARGS__)
#endif

#define UNUSED(x)  ((void)(x))

void bm_timer_cb(struct k_timer *timer);
K_TIMER_DEFINE(bm_timer, bm_timer_cb, NULL);

#if IS_ENABLED(CONFIG_AIR_DAEMON_WORKQUEUE_ENABLE)
K_WORK_DEFINE(bm_work, bm_work_handler);
#else
struct k_work bm_work;
#endif


void bm_assert(void)
{
    log_bm_error("bm_assert, caller[0x%x]", 1, (uint32_t)__builtin_return_address(0));
    //assert(0);
}

/* BM TIMER, WORK */
void bm_timer_cb(struct k_timer *timer)
{
    // log_bm_info("bm_timer_cb", 0);
#if IS_ENABLED(CONFIG_AIR_DAEMON_WORKQUEUE_ENABLE)
    air_daemon_wq_work_submit(&bm_work);
#else
    k_work_submit(&bm_work);
#endif
}

void bm_timer_start(uint32_t bm_timer_ms)
{
    k_timer_stop(&bm_timer);
    k_timer_start(&bm_timer, K_MSEC(bm_timer_ms), K_MSEC(bm_timer_ms));
    log_bm_info("bm_timer_start, bm_timer_ms[%dms]", 1, bm_timer_ms);
}

void bm_timer_stop(void)
{
    k_timer_stop(&bm_timer);
    log_bm_info("bm_timer_stop", 0);
}

/* BM CB */
bm_status_t bm_register_callback(bm_cb_t bm_cb, bm_callback_t callback, bm_user_t user)
{
    if ((bm_cb >= BM_CB_MAX) || (callback == NULL) || (user >= BM_USER_MAX)) {
        log_bm_error("bm_register_callback fail, bm_cb[%d], callback[0x%X], user[%d]", 3, bm_cb, callback, user);
        bm_assert();
        return BM_STATUS_INVALID_PARAMETER;
    }
    bm_cb_func[bm_cb][user].bm_callback = callback;
    log_bm_info("bm_register_callback ok, bm_cb[%d], user[%d]", 2, bm_cb, user);
    return BM_STATUS_OK;
}

bm_status_t bm_deregister_callback(bm_cb_t bm_cb, bm_user_t user)
{
    if ((bm_cb >= BM_CB_MAX) || (user >= BM_USER_MAX)) {
        log_bm_error("bm_deregister_callback fail, bm_cb[%d], user[%d]", 2, bm_cb, user);
        bm_assert();
        return BM_STATUS_INVALID_PARAMETER;
    }
    bm_cb_func[bm_cb][user].bm_callback = NULL;
    log_bm_info("bm_deregister_callback ok, bm_cb[%d], user[%d]", 2, bm_cb, user);
    return BM_STATUS_OK;
}

/* BM INIT  */
void bm_init(void)
{
    log_bm_info("bm_init", 0);
#if !defined(CONFIG_AIR_DAEMON_WORKQUEUE_ENABLE)
    k_work_init(&bm_work, bm_work_handler);
#endif
    bm_cust_init();
}

#endif /* AIR_BATTERY_MANAGEMENT_ENABLE */
