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

#if defined(AIR_PURE_GAMING_DONGLE_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include "app_debug.h"
#include "app_state.h"
#include "hid_scenario_dongle.h"
#include "app_bt_conn_manager.h"
#include "app_acl_conn.h"
#include "app_events.h"
#include "af_events_declaration.h"
#include "assert.h"
#include "app_bt_ull_conn.h"
#include "app_pure_gaming_dongle_scenario.h"
#include "hal_gpt.h"
#include "hid_scenario_dongle.h"
#include "app_usb.h"
#include "hid_critical_path.h"
#if defined (CONFIG_PM)
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_platform.h"
#endif /* CONFIG_PM */
#include "bt_ull_le_hid_service.h"
#include "bt_ull_le_hid_conn_service.h"
#include "nvkey.h"
#include "hal_nvic.h"
#include "hid_power_mgr.h"

#if defined(CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER)
#include"auto_switch_service.h"
#endif/*CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER*/

/* Private define ------------------------------------------------------------*/
#define thisMODULE app_pg_dongle
#define thisMOD    "app_pg_dongle"
LOG_MODULE_REGISTER(thisMODULE);

#define USB_SUSPEND_WAITING_PERIOD (500)
#define USB_SUSPEND_IDLE_PERIOD (800)
#define USB_SUSPEND_RECONNECT_PERIOD (100)
#define USB_SUSPEND_CONN_TIMEOUT (10)//10*10MS=100MS
#define WAKEUP_PC_IN_SUSPEND_TIMER_DURATION (50)
#define USB_SUSPEND_CHECK_TIMER_DURATION (1000)

#define RR_SUC_RATE_MAX     950   // 95.0%
#define RR_SUC_RATE_MIN     700   // 70.0%
#define WB_SCAN_DURATION_MAX    10000    // 10000 * 312.5us = 3.125 s
#define STABLE_RR_CHECK_LIMIT     10 /* Continuous check seconds */
#define AUTO_SWITCH_TIMER_DURATION 5000 // 5000 ms = 5 s

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if defined(CONFIG_AIR_PURE_GAMING_DONGLE_KB_ENABLE)
static const app_pg_dongle_rr_scenario_param_t app_pg_dongle_rr_scenario_param_table[] =
{
     // 125
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_82,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_2, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},

     // 250
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_82,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_3, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},

     // 500
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_82,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_4, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},

     // 1000
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_82,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_5, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},

     // 2000
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_82,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_6, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},

     // 4000
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_82,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_7, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},

     // 8000
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_82,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_8, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},
};
#elif defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
static const app_pg_dongle_rr_scenario_param_t app_pg_dongle_rr_scenario_param_table[] =
{
     // 125
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_83,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_2, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},

     // 250
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_83,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_3, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},

     // 500
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_83,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_4, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},

     // 1000
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_83,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_5, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},

     // 2000
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_83,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_6, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},

     // 4000
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_83,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_7, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},

     // 8000
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_83,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_8, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},
};
#elif defined(CONFIG_AIR_PURE_GAMING_DONGLE_MS_ENABLE)
static const app_pg_dongle_rr_scenario_param_t app_pg_dongle_rr_scenario_param_table[] =
{
     // 125
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_81,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_2, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},

     // 250
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_81,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_3, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},

     // 500
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_81,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_4, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},

     // 1000
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_81,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_5, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},

     // 2000
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_81,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_6, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},

     // 4000
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_81,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_7, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},

     // 8000
    {.sceanrio_param = BT_ULL_LE_HID_SRV_APP_SCENARIO_81,
    .report_rate_param = {.rr_level=BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_8, .phy=BT_ULL_LE_SRV_PHY_LE_4M}},
};
#else
    #error "Unknown product for dongle"
#endif/*CONFIG_AIR_PURE_GAMING_DONGLE_KB_ENABLE*/


/* Public variables ----------------------------------------------------------*/
app_pg_scenario_handle_t app_pg_dongle_ms_handle;
app_pg_scenario_handle_t app_pg_dongle_kb_handle;
app_pg_scenario_handle_t app_pg_dongle_hs_handle;
app_pg_scenario_handle_t app_pg_dongle_gp_handle;
#if defined(AIR_PURE_GAMING_DONGLE_MS_ENABLE)
app_pg_scenario_handle_t *app_pg_dongle_current_handle = &app_pg_dongle_ms_handle;
#elif defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
app_pg_scenario_handle_t *app_pg_dongle_current_handle = &app_pg_dongle_gp_handle;
#else
app_pg_scenario_handle_t *app_pg_dongle_current_handle = &app_pg_dongle_kb_handle;
#endif /* AIR_PURE_GAMING_DONGLE_MS_ENABLE */
bool app_pg_dongle_sleep_lock;
static uint32_t wakeup_pc_in_suspend_timer;
static uint32_t usb_suspend_check_timer;
static bool pure_gaming_dongle_scenario_start_flag = false;
bool g_usb_entry_suspend_flag=false;

#if defined(CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER)
static uint32_t auto_switch_timer;
static uint8_t stable_rr_check_high_cnt = 0;
static uint8_t stable_rr_check_low_cnt = 0;
static bt_ull_le_hid_srv_report_rate_level_t g_rr_level = BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_DEFAULT;
bool auto_switch_timer_on_flag = false  ;
#endif/*CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER*/
#if defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
#define TX_GC_4dBm 50
#define TX_GC_10dBm 62
#endif/*AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE*/

/* Private functions ---------------------------------------------------------*/
static int app_pure_gaming_dongle_scenario_handle_check(app_pg_scenario_handle_t *scenario_handle)
{
    int ret = -EPERM;

    if ((scenario_handle == &app_pg_dongle_ms_handle)
        || (scenario_handle == &app_pg_dongle_gp_handle)
        || (scenario_handle == &app_pg_dongle_kb_handle)
        || (scenario_handle == &app_pg_dongle_hs_handle))
    {
        ret = 0;
    }

    return ret;
}

static void app_pure_gaming_dongle_scenario_usb_suspend_timer_cb(void *user_data)
{
    app_pg_scenario_handle_t *scenario_handle = (app_pg_scenario_handle_t *)user_data;

    LOG_INF("[app_hid_dongle] pure gaming dongle scenario 0x%x entry timer 0x%x callback status %u.",
            scenario_handle,
            scenario_handle->usb_suspend_timer,
            scenario_handle->usb_suspend_timer_status);

    if (scenario_handle->usb_suspend_timer_status == APP_PG_TIMER_WAITTING_STAGE)
    {
        /* The waitting time in beginning is finished, trigger to reconnect */
        scenario_handle->usb_suspend_timer_status = APP_PG_TIMER_RECONNECT_STAGE;
        // #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
        // if(HAL_GPT_STATUS_OK != hal_gpt_sw_start_timer_ms(scenario_handle->usb_suspend_timer, USB_SUSPEND_RECONNECT_PERIOD, app_pure_gaming_dongle_scenario_usb_suspend_timer_cb, scenario_handle))
        // {
        //     assert(0);
        // }
        // #endif/*CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE*/
        app_events_send(EVT_CMD_RECONNECT_REQ, scenario_handle);
    }
    else if (scenario_handle->usb_suspend_timer_status == APP_PG_TIMER_IDLE_STAGE)
    {
        /* IDLE time is finished, trigger to reconnect */
        scenario_handle->usb_suspend_timer_status = APP_PG_TIMER_RECONNECT_STAGE;
        // #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
        // if(HAL_GPT_STATUS_OK != hal_gpt_sw_start_timer_ms(scenario_handle->usb_suspend_timer, USB_SUSPEND_RECONNECT_PERIOD, app_pure_gaming_dongle_scenario_usb_suspend_timer_cb, scenario_handle))
        // {
        //     assert(0);
        // }
        // #endif/*CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE*/
        app_events_send(EVT_CMD_RECONNECT_REQ, scenario_handle);
    }
    else if (scenario_handle->usb_suspend_timer_status == APP_PG_TIMER_RECONNECT_STAGE)
    {
        /* Reconnect time is finished, trigger to idle */
        // #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
        // scenario_handle->usb_suspend_timer_status = APP_PG_TIMER_IDLE_STAGE;
        // if(HAL_GPT_STATUS_OK != hal_gpt_sw_start_timer_ms(scenario_handle->usb_suspend_timer, USB_SUSPEND_IDLE_PERIOD, app_pure_gaming_dongle_scenario_usb_suspend_timer_cb, scenario_handle))
        // {
        //     assert(0);
        // }
        // app_events_send(EVT_CMD_RECONNECT_CANCEL_REQ, scenario_handle);
        // #endif/*CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE*/
    }
    else
    {
        assert(0);
    }
}

static app_pg_dongle_rr_scenario_param_t *app_pure_gaming_dongle_report_rate_convert_scenario_param(uint16_t report_rate)
{
#if 1
    uint8_t index;

    if (report_rate == 8000)
    {
        index = 6;
    }
    else if (report_rate >= 1000)
    {
        index = report_rate/2000+3;
    }
    else
    {
        index = report_rate/250;
    }

    return (app_pg_dongle_rr_scenario_param_t *)(&(app_pg_dongle_rr_scenario_param_table[index]));
#else
    switch (report_rate)
    {
        case 1000:
            return BT_ULL_LE_HID_SRV_APP_SCENARIO_6;

        case 8000:
            return BT_ULL_LE_HID_SRV_APP_SCENARIO_81;

        default:
            assert(0);
            return 0;
    }
#endif
}

static void app_pure_gaming_dongle_scenario_lock_sleep(void)
{
    if (app_pg_dongle_sleep_lock == false)
    {
        app_pg_dongle_sleep_lock = true;
#if defined (CONFIG_PM)
        hal_sleep_manager_lock_sleep(SLEEP_LOCK_APP);
#endif /* CONFIG_PM */
        LOG_INF("[app_hid_dongle] pure gaming dongle scenario lock sleep done.");
    }
    else
    {
        LOG_INF("[app_hid_dongle] pure gaming dongle scenario lock sleep has done.");
    }
}

static void app_pure_gaming_dongle_scenario_unlock_sleep(void)
{
    if (app_pg_dongle_sleep_lock == true)
    {
        app_pg_dongle_sleep_lock = false;
#if defined (CONFIG_PM)
        hal_sleep_manager_unlock_sleep(SLEEP_LOCK_APP);
#endif /* CONFIG_PM */
        LOG_INF("[app_hid_dongle] pure gaming dongle scenario unlock sleep done.");
    }
    else
    {
        LOG_INF("[app_hid_dongle] pure gaming dongle scenario unlock sleep has done.");
    }
}

/* Public functions ----------------------------------------------------------*/
void app_pure_gaming_dongle_scenario_init(void)
{
    LOG_INF("[app_hid_dongle] pure gaming dongle scenario init start.");

    memset(&app_pg_dongle_ms_handle, 0, sizeof(app_pg_scenario_handle_t));
    memset(&app_pg_dongle_kb_handle, 0, sizeof(app_pg_scenario_handle_t));
    memset(&app_pg_dongle_hs_handle, 0, sizeof(app_pg_scenario_handle_t));
    memset(&app_pg_dongle_gp_handle, 0, sizeof(app_pg_scenario_handle_t));

    /* HID service init */
#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE)
    /* according setting to choose usb mode */
    air_usb_mode_t usb_mode = USB_MODE_HID;
    uint32_t nvkey_size = sizeof(air_usb_mode_t);
    nvkey_status_t nvkey_ret = nvkey_read_data(NVID_APP_USB_MODE, (uint8_t *)&usb_mode, &nvkey_size);
    if ((nvkey_size != sizeof(air_usb_mode_t)) || (nvkey_ret != NVKEY_STATUS_OK))
    {
        usb_mode = USB_MODE_HID;
        nvkey_write_data(NVID_APP_USB_MODE, (uint8_t *)&usb_mode, sizeof(air_usb_mode_t));
        LOG_INF("[app_hid_dongle] pure gaming dongle scenario load usb mode fail, size = %d, ret = %d.", nvkey_size, nvkey_ret);
    }
    hid_scenario_dongle_usb_mode_set(usb_mode);
#endif /* defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE) */
    hid_scenario_dongle_init_param_t init_param;
    init_param.usb_evt_cb = app_usb_evt_cb;
    hid_scenario_dongle_mode_init(&init_param);

#if defined (CONFIG_PM)
    hal_sleep_manager_lock_extslp(SLEEP_LOCK_EXTEND_APP);
#endif /* CONFIG_PM */
    app_pure_gaming_dongle_scenario_lock_sleep();

    LOG_INF("[app_hid_dongle] pure gaming dongle scenario init done.");
}

void app_pure_gaming_dongle_scenario_deinit(void)
{
    LOG_INF("[app_hid_dongle] pure gaming dongle scenario deinit start.");

    /* HID service init */
    hid_scenario_dongle_mode_deinit();

#if defined (CONFIG_PM)
    hal_sleep_manager_unlock_extslp(SLEEP_LOCK_EXTEND_APP);
#endif /* CONFIG_PM */
    app_pure_gaming_dongle_scenario_unlock_sleep();

    LOG_INF("[app_hid_dongle] pure gaming dongle scenario deinit done.");
}

int app_pure_gaming_dongle_scenario_open(app_pg_scenario_handle_t *scenario_handle)
{
    int ret;
    uint8_t dev_cnt;
    app_bt_conn_role_t role;

    ret = app_pure_gaming_dongle_scenario_handle_check(scenario_handle);
    assert(ret == 0);

    ret = hid_scenario_dongle_mode_open();
    assert(ret == 0);

    role = app_pure_gaming_dongle_scenario_get_role_by_handle(scenario_handle);
    scenario_handle->link_handle = app_bt_conn_manager_get_handle(role);
    assert(scenario_handle->link_handle != NULL);
    app_bt_conn_manager_set_scenario_handle(scenario_handle->link_handle, scenario_handle);

    /* load bonded device info */
    app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_GET_BONDED_DEVICE_NUM, &dev_cnt);
    assert(dev_cnt < 2);
    if (dev_cnt != 0)
    {
        app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_BT_GET_BONDED_DEVICE_ADDR, NULL);
        LOG_INF("[app_hid_dongle] pure gaming dongle scenario 0x%x handle 0x%x reconnect address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x",
                scenario_handle,
                scenario_handle->link_handle,
                scenario_handle->link_handle->ull_addr.a.val[5],
                scenario_handle->link_handle->ull_addr.a.val[4],
                scenario_handle->link_handle->ull_addr.a.val[3],
                scenario_handle->link_handle->ull_addr.a.val[2],
                scenario_handle->link_handle->ull_addr.a.val[1],
                scenario_handle->link_handle->ull_addr.a.val[0]);
    }

    LOG_INF("[app_hid_dongle] pure gaming dongle scenario handle 0x%x open done, %d.", scenario_handle, ret);

    return ret;
}

int app_pure_gaming_dongle_scenario_start(app_pg_scenario_handle_t *scenario_handle)
{
    int ret = 0;
    uint32_t mask;

    ret = app_pure_gaming_dongle_scenario_handle_check(scenario_handle);
    assert(ret == 0);

    hal_nvic_save_and_set_interrupt_mask(&mask);
    if(pure_gaming_dongle_scenario_start_flag)
    {
        hal_nvic_restore_interrupt_mask(mask);
        LOG_INF("[app_hid_dongle] pure gaming dongle scenario handle 0x%x start error.", scenario_handle);
        return ret;
    }
    pure_gaming_dongle_scenario_start_flag = true;
    hal_nvic_restore_interrupt_mask(mask);

    ret = hid_scenario_dongle_mode_start();
    assert(ret == 0);

    LOG_INF("[app_hid_dongle] pure gaming dongle scenario handle 0x%x start done, %d.", scenario_handle, ret);

    return ret;
}

int app_pure_gaming_dongle_scenario_stop(app_pg_scenario_handle_t *scenario_handle)
{
    int ret = 0;
    uint32_t mask;

    ret = app_pure_gaming_dongle_scenario_handle_check(scenario_handle);
    assert(ret == 0);

    hal_nvic_save_and_set_interrupt_mask(&mask);
    if(!pure_gaming_dongle_scenario_start_flag)
    {
        hal_nvic_restore_interrupt_mask(mask);
        LOG_INF("[app_hid_dongle] pure gaming dongle scenario handle 0x%x stop error.", scenario_handle);
        return ret;
    }
    pure_gaming_dongle_scenario_start_flag = false;
    hal_nvic_restore_interrupt_mask(mask);

    ret = hid_scenario_dongle_mode_stop();
    assert(ret == 0);

    LOG_INF("[app_hid_dongle] pure gaming dongle scenario handle 0x%x stop done, %d.", scenario_handle, ret);

    return ret;
}

int app_pure_gaming_dongle_scenario_close(app_pg_scenario_handle_t *scenario_handle)
{
    int ret;

    ret = app_pure_gaming_dongle_scenario_handle_check(scenario_handle);
    assert(ret == 0);

    ret = hid_scenario_dongle_mode_close();
    assert(ret == 0);

    app_bt_conn_manager_release_handle(scenario_handle->link_handle);

    LOG_INF("[app_hid_dongle] pure gaming dongle scenario handle 0x%x close done, %d.", scenario_handle, ret);

    return ret;
}

int app_pure_gaming_dongle_scenario_set_config(app_pg_scenario_handle_t *scenario_handle, app_pg_scenario_config_cmd_t cmd, void *param)
{
    int ret;
    app_pg_dongle_rr_scenario_param_t *scenario_rr_param;
    nvkey_status_t nvs_ret;

    LOG_INF("[app_hid_dongle] pure gaming dongle scenario set config handle 0x%x cmd %u param 0x%x", scenario_handle, cmd, param);

    ret = app_pure_gaming_dongle_scenario_handle_check(scenario_handle);
    assert(ret == 0);

    switch (cmd)
    {
        case APP_PG_CFG_CMD_BT_STATUS:
            scenario_handle->bt_connected = *((bool *)param);
            ret = 0;
            break;

        case APP_PG_CFG_CMD_USB_STATUS:
            scenario_handle->usb_status = *((app_pg_scenario_usb_status_t *)param);
            ret = 0;
            break;

        case APP_PG_CFG_CMD_BT_HANDLE_UPDATE:
            assert(scenario_handle->bt_connected == false);
            if (scenario_handle->link_handle != NULL)
            {
                app_bt_conn_manager_release_handle(scenario_handle->link_handle);
                scenario_handle->link_handle = NULL;
            }
            scenario_handle->link_handle = (app_bt_conn_handle_t *)param;
            ret = 0;
            break;

        case APP_PG_CFG_CMD_TEMP_BT_HANDLE_UPDATE:
            scenario_handle->temp_link_handle = (app_bt_conn_handle_t *)param;
            ret = 0;
            break;

        case APP_PG_CFG_CMD_BT_REMOVE_ULL_LINK_RECORD:
            app_bt_ull_connection_remove_bonded_addr_list(scenario_handle->link_handle, app_pure_gaming_dongle_scenario_get_role_by_handle(scenario_handle));
            ret = 0;
            break;

        case APP_PG_CFG_CMD_SET_SCENARIO:
            scenario_rr_param = app_pure_gaming_dongle_report_rate_convert_scenario_param(*(uint16_t *)param);
            ret = app_bt_ull_connection_set_scenario(scenario_handle->link_handle, scenario_rr_param->sceanrio_param);
            assert(ret == 0);
            LOG_INF("[app_hid_dongle] pure gaming dongle scenario 0x%x set scenario to %u, ret = %d", scenario_handle, scenario_rr_param->sceanrio_param, ret);
            break;

        case APP_PG_CFG_CMD_SET_REPORT_RATE:
            scenario_handle->report_rate = *(uint16_t *)param;
            app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_SET_REPORT_RATE_NVS_SETTING, (void *)(&(scenario_handle->report_rate)));
            scenario_rr_param = app_pure_gaming_dongle_report_rate_convert_scenario_param(scenario_handle->report_rate);
            #if defined(AIR_HID_DUMMY_REPORT_RATE)
            ret = 0 ;//FOR GAMEPAD DUMMY RATE , DO NOT REALLY CHANGE AIR RAET
            #else
            ret = app_bt_ull_connection_set_report_rate(scenario_handle->link_handle, &scenario_rr_param->report_rate_param);
            #endif/**/
            assert(ret == 0);
            LOG_INF("[app_hid_dongle] pure gaming dongle scenario 0x%x set report rate to %u, ret = %d", scenario_handle, scenario_handle->report_rate, ret);
            app_pure_gaming_dongle_scenario_update_critical_device_infe(HID_CRITICAL_PATH_INFO_TYPE_REPORT_RATE);
            break;

        case APP_PG_CFG_CMD_SET_REPORT_RATE_NVS_SETTING:
            nvs_ret = nvkey_write_data(NVID_APP_DONGLE_ULL2_HID_SCENARIO, (uint8_t *)param, sizeof(uint16_t));
            LOG_INF("[app_hid_dongle] pure gaming dongle scenario 0x%x set report rate nvs setting = 0x%x, ret = %d", scenario_handle, *(uint16_t *)param, nvs_ret);
            break;

        case APP_PG_CFG_CMD_SET_REPORT_RATE_CHANGE_REQUEST:
            scenario_handle->rr_changed_request = *(bool *)param;
            LOG_INF("[app_hid_dongle] pure gaming dongle scenario 0x%x set report rate reuqest = %u", scenario_handle, scenario_handle->rr_changed_request);
            break;

        case APP_PG_CFG_CMD_SET_SCAN_REQUEST:
            scenario_handle->scan_request = ((app_pg_scenario_scan_request_param_t *)param)->request;
            scenario_handle->scan_timeout_ms = ((app_pg_scenario_scan_request_param_t *)param)->timeout_ms;
            ret = 0;
            break;

        case APP_PG_CFG_CMD_SET_DPI_PARA:
            scenario_handle->cur_dpi = *(app_pg_dpi_para_t *)param;
            ret = 0;
            break;

        case APP_PG_CFG_CMD_SET_CHARGERING_STATUS:
            scenario_handle->chargering_status = *(uint8_t *)param;
            ret = 0;
            break;

        case APP_PG_CFG_CMD_SET_BATTERY_STATUS:
            scenario_handle->battery_status_percent = *(uint8_t *)param;
            ret = 0;
            break;

        default:
            assert(0);
            break;
    }

    return ret;
}

int app_pure_gaming_dongle_scenario_get_config(app_pg_scenario_handle_t *scenario_handle, app_pg_scenario_config_cmd_t cmd, void *param)
{
    int ret;
    uint16_t report_rate;
    uint32_t nvkey_size;
    nvkey_status_t nvkey_ret;
    app_pg_dongle_rr_scenario_param_t *scenario_rr_param;

    LOG_INF("[app_hid_dongle] pure gaming dongle scenario get config handle 0x%x cmd %u param 0x%x", scenario_handle, cmd, param);

    ret = app_pure_gaming_dongle_scenario_handle_check(scenario_handle);
    assert(ret == 0);

    switch (cmd)
    {
        case APP_PG_CFG_CMD_BT_STATUS:
            *((bool *)param) = scenario_handle->bt_connected;
            ret = 0;
            break;

        case APP_PG_CFG_CMD_USB_STATUS:
            *((app_pg_scenario_usb_status_t *)param) = scenario_handle->usb_status;
            ret = 0;
            break;

        case APP_PG_CFG_CMD_BT_HANDLE_QEURY:
            *((app_bt_conn_handle_t **)param) = scenario_handle->link_handle;
            ret = 0;
            break;

        case APP_PG_CFG_CMD_TEMP_BT_HANDLE_QEURY:
            *((app_bt_conn_handle_t **)param) = scenario_handle->temp_link_handle;
            ret = 0;
            break;

        case APP_PG_CFG_CMD_BT_GET_BONDED_DEVICE_NUM:
            *((uint8_t *)param) = app_bt_ull_connection_get_bonded_device_num(app_pure_gaming_dongle_scenario_get_role_by_handle(scenario_handle));
            ret = 0;
            break;

        case APP_PG_CFG_CMD_BT_GET_BONDED_DEVICE_ADDR:
            app_bt_ull_connection_get_bonded_device_addr(scenario_handle->link_handle, app_pure_gaming_dongle_scenario_get_role_by_handle(scenario_handle));
            ret = 0;
            break;

        case APP_PG_CFG_CMD_BT_GET_PAIRED_DEVICE_LIST:
            if (scenario_handle->link_handle != NULL)
            {
                app_bt_ull_connection_get_bonded_addr_list(scenario_handle->link_handle->role, ((app_pg_scenario_paired_list_param_t *)param)->dev_cnt, ((app_pg_scenario_paired_list_param_t *)param)->list);
            }
            else
            {
                ((app_pg_scenario_paired_list_param_t *)param)->dev_cnt = 0;
                ((app_pg_scenario_paired_list_param_t *)param)->list = NULL;
            }
            ret = 0;
            break;

        case APP_PG_CFG_CMD_BT_GET_ULL_LINK_STATUS:
            *((app_bt_conn_status_t *)param) = scenario_handle->link_handle->ull_status;
            ret = 0;
            break;

        case APP_PG_CFG_CMD_BT_GET_ULL_LINK_ADDR:
            memcpy(param, &(scenario_handle->link_handle->ull_addr), sizeof(bt_addr_le_t));
            ret = 0;
            break;

        case APP_PG_CFG_CMD_GET_SCENARIO:
            scenario_rr_param = app_pure_gaming_dongle_report_rate_convert_scenario_param(scenario_handle->report_rate);
            *((bt_ull_le_hid_srv_app_scenario_t *)param) = scenario_rr_param->sceanrio_param;
            LOG_INF("[app_hid_dongle] pure gaming dongle scenario 0x%x get scenario to %u, ret = %d", scenario_handle, scenario_rr_param->sceanrio_param, ret);
            ret = 0;
            break;

        case APP_PG_CFG_CMD_GET_REPORT_RATE:
            app_pure_gaming_dongle_scenario_get_config(scenario_handle, APP_PG_CFG_CMD_GET_REPORT_RATE_NVS_SETTING, param);
            LOG_INF("[app_hid_dongle] pure gaming dongle scenario 0x%x get report rate to %u, ret = %d", scenario_handle, *((uint16_t *)param), ret);
            ret = 0;
            break;

        case APP_PG_CFG_CMD_GET_REPORT_RATE_CHANGE_REQUEST:
            *(bool *)param = scenario_handle->rr_changed_request;
            break;

        case APP_PG_CFG_CMD_GET_REPORT_RATE_NVS_SETTING:
            nvkey_size = sizeof(uint16_t);
            nvkey_ret = nvkey_read_data(NVID_APP_DONGLE_ULL2_HID_SCENARIO, (uint8_t *)&report_rate, &nvkey_size);
            if ((nvkey_ret == NVKEY_STATUS_OK) && (nvkey_size == sizeof(uint16_t)))
            {
                *((uint16_t *)param) = report_rate;
                LOG_INF("[app_hid_dongle] pure gaming dongle scenario 0x%x get report rate nvs setting = 0x%x", scenario_handle, report_rate);
            }
            else
            {
                // assert(0);
                report_rate = CONFIG_AIR_PURE_GAMING_DEFAULT_REPORT_RATE;
                *((uint16_t *)param) = report_rate;
                LOG_INF("[app_hid_dongle] pure gaming dongle scenario 0x%x get report rate default rr = 0x%d", scenario_handle, report_rate);
            }
            ret = 0;
            break;

        case APP_PG_CFG_CMD_GET_SCAN_REQUEST:
            ((app_pg_scenario_scan_request_param_t *)param)->request = scenario_handle->scan_request;
            ((app_pg_scenario_scan_request_param_t *)param)->timeout_ms = scenario_handle->scan_timeout_ms;
            ret = 0;
            break;

        case APP_PG_CFG_CMD_GET_DPI_PARA:
            LOG_INF("[debug] APP_PG_CFG_CMD_GET_DPI_PARA 0x%x get cur_dpi = 0x%d", scenario_handle, scenario_handle->cur_dpi);
            *(app_pg_dpi_para_t *)param = scenario_handle->cur_dpi;
            ret = 0;
            break;

        case APP_PG_CFG_CMD_GET_CHARGERING_STATUS:
            LOG_INF("[debug] APP_PG_CFG_CMD_GET_CHARGERING_STATUS 0x%x get chargering_status = %d", scenario_handle, scenario_handle->chargering_status);
            *(uint8_t *)param = scenario_handle->chargering_status;
            ret = 0;
            break;
        case APP_PG_CFG_CMD_GET_BATTERY_STATUS:
            LOG_INF("[debug] APP_PG_CFG_CMD_GET_BATTERY_STATUS 0x%x get battery_status_percent = %d", scenario_handle, scenario_handle->battery_status_percent);
            *(uint8_t *)param = scenario_handle->battery_status_percent;
            ret = 0;
            break;

        default:
            assert(0);
            break;
    }

    return ret;
}

app_pg_scenario_handle_t *app_pure_gaming_dongle_scenario_get_handle_by_link(app_bt_conn_handle_t *link_handle)
{
    app_pg_scenario_handle_t *scenario_handle = NULL;

    assert(link_handle != NULL);

    if (app_pg_dongle_ms_handle.link_handle == link_handle)
    {
        scenario_handle = &app_pg_dongle_ms_handle;
    }
    else if (app_pg_dongle_kb_handle.link_handle == link_handle)
    {
        scenario_handle = &app_pg_dongle_kb_handle;
    }
    else if (app_pg_dongle_hs_handle.link_handle == link_handle)
    {
        scenario_handle = &app_pg_dongle_hs_handle;
    }
    else if (app_pg_dongle_gp_handle.link_handle == link_handle)
    {
        scenario_handle = &app_pg_dongle_gp_handle;
    }

    LOG_INF("[app_hid_dongle] pure gaming dongle scenario get link 0x%x handle 0x%x", link_handle, scenario_handle);

    return scenario_handle;
}

app_pg_scenario_handle_t *app_pure_gaming_dongle_scenario_get_handle_by_role(app_bt_conn_role_t role)
{
    app_pg_scenario_handle_t *scenario_handle = NULL;

    assert(role != APP_BT_CONN_ROLE_UNKNOWN);

    if (role == APP_BT_CONN_ROLE_MOUSE)
    {
        scenario_handle = &app_pg_dongle_ms_handle;
    }
    else if (role == APP_BT_CONN_ROLE_KEYBOARD)
    {
        scenario_handle = &app_pg_dongle_kb_handle;
    }
    else if (role == APP_BT_CONN_ROLE_HEADSET)
    {
        scenario_handle = &app_pg_dongle_hs_handle;
    }
    else if (role == APP_BT_CONN_ROLE_GAMEPAD)
    {
        scenario_handle = &app_pg_dongle_gp_handle;
    }

    LOG_INF("[app_hid_dongle] pure gaming dongle scenario get role %u handle 0x%x", role, scenario_handle);

    return scenario_handle;
}

app_bt_conn_role_t app_pure_gaming_dongle_scenario_get_role_by_handle(app_pg_scenario_handle_t *scenario_handle)
{
    if (scenario_handle == &app_pg_dongle_ms_handle)
    {
        return APP_BT_CONN_ROLE_MOUSE;
    }
    else if (scenario_handle == &app_pg_dongle_kb_handle)
    {
        return APP_BT_CONN_ROLE_KEYBOARD;
    }
    else if (scenario_handle == &app_pg_dongle_hs_handle)
    {
        return APP_BT_CONN_ROLE_HEADSET;
    }
    else if (scenario_handle == &app_pg_dongle_gp_handle)
    {
        return APP_BT_CONN_ROLE_GAMEPAD;
    }
    else
    {
        assert(0);
    }

    return APP_BT_CONN_ROLE_UNKNOWN;
}

#ifdef AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE
static int app_pure_gaming_dongle_scenario_set_local_tx_power(uint8_t local_tx_power_gc)
{
    int err;
    bt_ull_le_hid_srv_set_tx_power_t param;

    param.tx_power_type = 0;
    param.device_type = BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD;
    param.local_tx_gc = local_tx_power_gc;

    err = bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_SET_TXPOWER, (const void *)(&param), sizeof(bt_ull_le_hid_srv_set_tx_power_t));
    if (err >= 0)
    {
        LOG_INF("[app_hid_dongle] app_pure_gaming_dongle_scenario_set_local_tx_power success,tx_power_type = %d,local_tx_gc=%d",param.tx_power_type,param.device_type);
    }
    else
    {
        LOG_INF("[app_hid_dongle] app_pure_gaming_dongle_scenario_set_local_tx_power failed, err = %d");
    }

    return err;
}
#endif

int app_pure_gaming_dongle_scenario_entry_usb_suspend_case(app_pg_scenario_handle_t *scenario_handle)
{
    int ret = 0;

    assert(!(scenario_handle->usb_suspend_timer_status != APP_PG_TIMER_NOT_START));

    hal_gpt_sw_get_timer(&scenario_handle->usb_suspend_timer);
    if(HAL_GPT_STATUS_OK != hal_gpt_sw_start_timer_ms(scenario_handle->usb_suspend_timer, USB_SUSPEND_WAITING_PERIOD, app_pure_gaming_dongle_scenario_usb_suspend_timer_cb, scenario_handle))
    {
        assert(0);
    }
    scenario_handle->usb_suspend_timer_status = APP_PG_TIMER_WAITTING_STAGE;

#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
    app_pure_gaming_dongle_scenario_unlock_sleep();
#else
    bt_ull_le_hid_conn_srv_set_create_cis_timeout(USB_SUSPEND_CONN_TIMEOUT);
    app_pure_gaming_dongle_scenario_unlock_sleep();
#endif

#if defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
    app_pure_gaming_dongle_scenario_set_local_tx_power(TX_GC_4dBm);
#endif/*AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE*/

    /*enable BT sleep event*/
    hid_power_mgr__set_LC_sleep_pollicy(LC_SLP_POLICY_CTR_CHANGE, LC_SLP_POLICY_LIGHT_SLEEP);

    g_usb_entry_suspend_flag = true;

    app_pure_gaming_dongle_scenario_stop(scenario_handle);
    LOG_INF("[app_hid_dongle] pure gaming dongle scenario 0x%x entry usb suspend timer 0x%x status %u done %d.",
            scenario_handle,
            scenario_handle->usb_suspend_timer,
            scenario_handle->usb_suspend_timer_status,
            ret);

    return ret;
}

int app_pure_gaming_dongle_scenario_usb_suspend_case_switch_to_idle(app_pg_scenario_handle_t *scenario_handle)
{
    int ret = 0;

    assert(!(scenario_handle->usb_suspend_timer_status != APP_PG_TIMER_RECONNECT_STAGE));

    if (scenario_handle->usb_suspend_timer == 0)
    {
        hal_gpt_sw_get_timer(&scenario_handle->usb_suspend_timer);
    }

    if(HAL_GPT_STATUS_OK != hal_gpt_sw_start_timer_ms(scenario_handle->usb_suspend_timer, USB_SUSPEND_IDLE_PERIOD, app_pure_gaming_dongle_scenario_usb_suspend_timer_cb, scenario_handle))
    {
        assert(0);
    }
    scenario_handle->usb_suspend_timer_status = APP_PG_TIMER_IDLE_STAGE;

    app_pure_gaming_dongle_scenario_unlock_sleep();

    LOG_INF("[app_hid_dongle] pure gaming dongle scenario 0x%x usb_suspend_case switch_to_idle 0x%x status %u done %d.",
            scenario_handle,
            scenario_handle->usb_suspend_timer,
            scenario_handle->usb_suspend_timer_status,
            ret);

    return ret;
}

int app_pure_gaming_dongle_scenario_exit_usb_suspend_case(app_pg_scenario_handle_t *scenario_handle)
{
    int ret = 0;

    hal_gpt_sw_stop_timer_ms(scenario_handle->usb_suspend_timer);
    hal_gpt_sw_free_timer(scenario_handle->usb_suspend_timer);
    scenario_handle->usb_suspend_timer = 0;
    scenario_handle->usb_suspend_timer_status = APP_PG_TIMER_NOT_START;

#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
    app_pure_gaming_dongle_scenario_lock_sleep();
#else
    bt_ull_le_hid_conn_srv_set_create_cis_timeout(0);//always connect
    app_pure_gaming_dongle_scenario_lock_sleep();
#endif

#if defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
    app_pure_gaming_dongle_scenario_set_local_tx_power(TX_GC_10dBm);
#endif/*AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE*/
    /*disable BT sleep event*/
    hid_power_mgr__set_LC_sleep_pollicy(LC_SLP_POLICY_CTR_CHANGE, LC_SLP_POLICY_DISABLE);

    g_usb_entry_suspend_flag = false;

    LOG_INF("[app_hid_dongle] pure gaming dongle scenario 0x%x exit usb suspend timer 0x%x status %u done %d.",
            scenario_handle,
            scenario_handle->usb_suspend_timer,
            scenario_handle->usb_suspend_timer_status,
            ret);

    return ret;
}

int app_pure_gaming_dongle_scenario_usb_status_update_by_evt(app_pg_scenario_handle_t *scenario_handle, T_EVT_CMD_E cmd)
{
    int ret = 0;
    app_pg_scenario_usb_status_t usb_status;

    if ((cmd < EVT_CMD_USB_PLUGIN) || (cmd > EVT_CMD_USB_RESUME))
    {
        assert(0);
    }

    usb_status = APP_PG_USB_PLUGOUT + (cmd - EVT_CMD_USB_PLUGIN);
    app_pure_gaming_dongle_scenario_set_config(scenario_handle, APP_PG_CFG_CMD_USB_STATUS, &usb_status);

    return ret;
}

app_pg_scenario_handle_t *app_pure_gaming_dongle_scenario_set_current_context(app_bt_conn_role_t role)
{
    if (role == APP_BT_CONN_ROLE_MOUSE)
    {
        app_pg_dongle_current_handle = &app_pg_dongle_ms_handle;
    }
    else if (role == APP_BT_CONN_ROLE_KEYBOARD)
    {
        app_pg_dongle_current_handle = &app_pg_dongle_kb_handle;
    }
    else if (role == APP_BT_CONN_ROLE_HEADSET)
    {
        app_pg_dongle_current_handle = &app_pg_dongle_hs_handle;
    }
    else if (role == APP_BT_CONN_ROLE_GAMEPAD)
    {
        app_pg_dongle_current_handle = &app_pg_dongle_gp_handle;
    }
    else
    {
        assert(0);
    }

    LOG_INF("[app_hid_dongle] pure gaming dongle scenario set current context handle 0x%x, %d.", app_pg_dongle_current_handle, role);

    return app_pg_dongle_current_handle;
}

app_pg_scenario_handle_t *app_pure_gaming_dongle_scenario_get_current_context(void)
{
    return app_pg_dongle_current_handle;
}

static void app_pure_gaming_dongle_scenario_wakeup_pc_in_suspend_timer_cb(void *user_data)
{
    /*send 1*1 data for wakeup*/
    LOG_INF("[app_hid_dongle] pure gaming dongle scenario wakeup_pc_in_suspend_timer_cb");
    hid_critical_path_send_dummy_data(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
    if (wakeup_pc_in_suspend_timer != 0)
    {
        hal_gpt_sw_stop_timer_ms(wakeup_pc_in_suspend_timer);
    }
}

int app_pure_gaming_dongle_scenario_wakeup_pc(void)
{
    int ret = 0;

    if (wakeup_pc_in_suspend_timer == 0)
    {
        hal_gpt_sw_get_timer(&wakeup_pc_in_suspend_timer);
    }

    hal_gpt_sw_stop_timer_ms(wakeup_pc_in_suspend_timer);
    if(HAL_GPT_STATUS_OK != hal_gpt_sw_start_timer_ms(wakeup_pc_in_suspend_timer, WAKEUP_PC_IN_SUSPEND_TIMER_DURATION, app_pure_gaming_dongle_scenario_wakeup_pc_in_suspend_timer_cb, NULL))
    {
        assert(0);
    }
    LOG_INF("[app_hid_dongle] pure gaming dongle scenario wakeup_pc start timer");
    return ret;
}

static void app_pure_gaming_dongle_scenario_us_suspend_check_timer_cb(void *user_data)
{
    LOG_INF("[app_hid_dongle] app_pure_gaming_dongle_scenario_us_suspend_check_timer_cb");
    /*for start up ,pc suspend,dongle reconnect ms*/
    app_state_change(APP_STATE_RECONNECT, REASON_RECONNECT);
}

int app_pure_gaming_dongle_scenario_suspend_timer_start(void)
{
    int ret = 0;

    if (usb_suspend_check_timer == 0)
    {
        hal_gpt_sw_get_timer(&usb_suspend_check_timer);
    }

    if(HAL_GPT_STATUS_OK != hal_gpt_sw_start_timer_ms(usb_suspend_check_timer, USB_SUSPEND_CHECK_TIMER_DURATION, app_pure_gaming_dongle_scenario_us_suspend_check_timer_cb, NULL))
    {
        assert(0);
    }
    LOG_INF("[app_hid_dongle] app_pure_gaming_dongle_scenario_suspend_timer_start");
    return ret;
}

int app_pure_gaming_dongle_scenario_suspend_timer_stop(void)
{
    int ret = 0;

    if (usb_suspend_check_timer != 0)
    {
        hal_gpt_sw_stop_timer_ms(usb_suspend_check_timer);
        LOG_INF("[app_hid_dongle] app_pure_gaming_dongle_scenario_suspend_timer_stop");
    }else
    {
        LOG_INF("[app_hid_dongle] app_pure_gaming_dongle_scenario_suspend_timer_stop failed, timer is not running");
    }
    return ret;
}

void app_pure_gaming_dongle_scenario_update_critical_device_infe(hid_critical_path_info_type_t device_info)
{
    app_pg_scenario_handle_t *scenario_handle;
    scenario_handle = app_pure_gaming_dongle_scenario_get_current_context();
    int ret;

    if(device_info == HID_CRITICAL_PATH_INFO_TYPE_REPORT_RATE)
    {
         uint16_t report_rate;
        ret = app_pure_gaming_dongle_scenario_get_config(scenario_handle,APP_PG_CFG_CMD_GET_REPORT_RATE,&report_rate);
        if(ret!=0)
        {
            LOG_INF("[app_hid_dongle] app_pure_gaming_dongle_scenario_update_critical_device_infe APP_PG_CFG_CMD_GET_REPORT_RATE error");
        }
        LOG_INF("[app_hid_dongle] app_pure_gaming_dongle_scenario_update_critical_device_infe report_rate=%d",report_rate);

        #if defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
        hid_critical_path_set_device_info(HID_CRITICAL_PATH_DEVICE_TYPE_GAME_CONTROLLER,device_info,&report_rate);
        #endif/*AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE*/

        #if defined(AIR_PURE_GAMING_DONGLE_MS_ENABLE)
        hid_critical_path_set_device_info(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE,device_info,&report_rate);
        #endif/*AIR_PURE_GAMING_DONGLE_MS_ENABLE*/

    }else if(device_info == HID_CRITICAL_PATH_INFO_TYPE_DPI)
    {
        app_pg_dpi_para_t dpi;
        ret = app_pure_gaming_dongle_scenario_get_config(scenario_handle,APP_PG_CFG_CMD_GET_DPI_PARA,&dpi);
        uint16_t dpi_max = (dpi.cur_dpi_x > dpi.cur_dpi_y?dpi.cur_dpi_x:dpi.cur_dpi_y);

        if(ret!=0)
        {
            LOG_INF("[app_hid_dongle] app_pure_gaming_dongle_scenario_update_critical_device_infe APP_PG_CFG_CMD_GET_DPI_PARA error");
        }
        LOG_INF("[app_hid_dongle] app_pure_gaming_dongle_scenario_update_critical_device_infe dpi_max=%d",dpi_max);
        hid_critical_path_set_device_info(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE,device_info,&dpi_max);
    }
    else{
            LOG_INF("[app_hid_dongle] app_pure_gaming_dongle_scenario_update_critical_device_infe wrong device info");
    }
}

void app_pure_gaming_dongle_scenario_send_release_data(void)
{
    #if CONFIG_AIR_PURE_GAMING_DONGLE_MS_ENABLE
    hid_critical_path_ms_stop();
    #endif/*CONFIG_AIR_PURE_GAMING_DONGLE_MS_ENABLE*/

    #if CONFIG_AIR_PURE_GAMING_DONGLE_KB_ENABLE
    hid_critical_path_kb_stop();
    #endif/*CONFIG_AIR_PURE_GAMING_DONGLE_KB_ENABLE*/

    #if CONFIG_AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE
    hid_critical_path_gamepad_stop();
    #endif /* CONFIG_AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE */

    LOG_INF("app_pure_gaming_dongle_scenario_send_release_data");
}

#if defined(CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER)
void app_auto_switch_stop(void)
{
    auto_switch_stop();
    auto_switch_timer_on_flag = false;
    LOG_INF("[app_hid_dongle] app_auto_switch_stop");
}

void app_auto_switch_timer_cb()
{
    app_events_send(EVT_CMD_AUTO_SWITCH_CANCEL_REQ, NULL);
    LOG_INF("[app_hid_dongle] app_auto_switch_timer_cb->auto_switch_stop");
}

void app_auto_switch_start(void)
{
    auto_switch_start();
    if (auto_switch_timer == 0)
    {
        hal_gpt_sw_get_timer(&auto_switch_timer);
    }

    if(HAL_GPT_STATUS_OK != hal_gpt_sw_start_timer_ms(auto_switch_timer, AUTO_SWITCH_TIMER_DURATION, app_auto_switch_timer_cb, NULL))
    {
        assert(0);
    }
    auto_switch_timer_on_flag = true;
    LOG_INF("[app_hid_dongle] pure gaming dongle scenario auto_switch_timer"); 
}

/* 1s periodic WDT IRQ */
void app_auto_switch_hid_critical_path_callback(uint32_t total_data_count, uint32_t normal_data_count, uint32_t report_rate)
{
    g_rr_level = report_rate;
    uint32_t total_cnt = total_data_count;
    uint32_t rx_success_cnt = normal_data_count;
    uint32_t rx_success_rate = (rx_success_cnt * 1000)/total_cnt; /* 1.0 = 1000 */
    LOG_INF("app_auto_switch_hid_critical_path_callback, rr: %d, rx_success_rate: %d", report_rate, rx_success_rate);

    if(!auto_switch_timer_on_flag)
    {
        if (rx_success_rate > RR_SUC_RATE_MAX) {
            stable_rr_check_low_cnt = 0;
            stable_rr_check_high_cnt++;
        } else if (rx_success_rate < RR_SUC_RATE_MIN && rx_success_rate > 0){
            stable_rr_check_high_cnt = 0;
            stable_rr_check_low_cnt++;
        } else {
            stable_rr_check_low_cnt = 0;
            stable_rr_check_high_cnt = 0;
        }
        if (stable_rr_check_high_cnt >= STABLE_RR_CHECK_LIMIT){
            stable_rr_check_high_cnt = 0;
            app_events_send(EVT_CMD_AUTO_SWITCH_REQ, NULL);
        }
        if (stable_rr_check_low_cnt >= STABLE_RR_CHECK_LIMIT){
            stable_rr_check_low_cnt = 0;
            app_events_send(EVT_CMD_AUTO_SWITCH_REQ, NULL);
        }
    }
}

void app_pure_gaming_dongle_scenario_register_auto_switch_callback(void)
{
    /* Register HID critical path callback */
    hid_critical_path_register_debug_callback(app_auto_switch_hid_critical_path_callback);
    LOG_INF("[app_hid_dongle] app_pure_gaming_dongle_scenario_register_tx_auto_switch_callback");
}

#endif/*CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER*/

#if defined(CONFIG_AIR_HID_DISABLE_SOF_INTR)
void app_pure_gaming_dongle_scenario_disable_sof_intr(void)
{
    const struct device *hiddev = air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_MUX);
    air_usb_interrupt_enable(hiddev, AIR_USB_INTERRUPT_SOF, true, false);
}
#endif

#endif /* AIR_PURE_GAMING_DONGLE_ENABLE */
