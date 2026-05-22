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

/*
 * Dual-mode slide switch driver (USB + 2.4G only, no BT).
 *
 * Hardware: 1 GPIO pin, active level configurable via Kconfig.
 *            Active   -> 2.4G mode  (SS_MODE_2_4G)
 *            Inactive -> OFF mode   (SS_MODE_OFF, USB can take over)
 */

#if defined (CONFIG_AIR_DUAL_MODE_SLIDE_SWITCH)
#include <stdint.h>
#include <zephyr/kernel.h>

#include "app_slide_switch_dual.h"
#include "app_state.h"
#include "app_usb_port.h"
#include "app_battery.h"
#include "app_button.h"
#include "hal_gpio.h"
#include "hal_eint_internal.h"

#define thisMOD    "ss_dual"
#define thisMODULE   ss_dual
LOG_MODULE_REGISTER(thisMODULE);

static void gpio_test_monitor_handler(struct k_work *work);
static uint8_t gpio_test_prev = 0xFF;
static uint32_t gpio_test_loop_cnt = 0;

static K_WORK_DELAYABLE_DEFINE(gpio_test_work, gpio_test_monitor_handler);
static void gpio_test_monitor_handler(struct k_work *work)
{
    hal_gpio_data_t za_val;

    gpio_test_loop_cnt++;
    if (gpio_test_loop_cnt % 1000 == 0) {
        APP_LOGI(thisMOD, "[GPIO_TEST] heartbeat: alive (cnt=%u, prev=%d)",
                 gpio_test_loop_cnt, gpio_test_prev);
    }

    hal_gpio_get_input(35, &za_val);

    if (za_val != gpio_test_prev) {
        APP_LOGI(thisMOD, "[GPIO_TEST] (2_4g GPIO%d)=%d",
                 35, (int)za_val);
        gpio_test_prev = za_val;
    }

    k_work_schedule(&gpio_test_work, K_MSEC(2));
}

/*============================================================================*/
/*  defines                                                                   */
/*============================================================================*/
#define SS_DEBOUNCE_WITH_USB      10  /* ms, when USB plugged */
#define SS_DEBOUNCE_WITHOUT_USB    1  /* ms, normal */
#define SS_DEBOUNCE_EXTEND_SLEEP   0  /* ms, deep sleep */

/* SS mode values (from hid_common.h) */
#define SS_MODE_NONE  0x00
#define SS_MODE_OFF   0x01
#define SS_MODE_2_4G  0x03

/*============================================================================*/
/*  function prototypes                                                       */
/*============================================================================*/
static void app_ss_dual__check_mode_timer_cb(struct k_timer *timer_id);
static void app_ss_dual__get_init_ss_type(void);
static void app_ss_dual__change_slide_switch_position(uint8_t mode);
static void app_ss_dual_enter_low_power_set_wakeup(void);
static void app_ss_dual_exit_low_power(void);
static void app_ss_dual__announce_ss_wakeup_event(void);
static bool app_ss_dual_check_ss_mode(hal_gpio_data_t gpio_level);
static void app_ss_dual_set_hid_flag(void);
static void app_ss_dual_configure_gpio(void);
static void app_ss_dual__announce_usb_status_event(uint8_t status);

/*============================================================================*/
/*  timers                                                                    */
/*============================================================================*/
K_TIMER_DEFINE(check_mode_timer_dual, app_ss_dual__check_mode_timer_cb, NULL);

/*============================================================================*/
/*  variables                                                                 */
/*============================================================================*/
static uint8_t app_ss_dual_mode = SS_MODE_NONE;
static uint8_t app_ss_dual_low_power_state = 0;  /* 0:normal, 1:low power */
static uint8_t ss_dual_debounce = SS_DEBOUNCE_WITHOUT_USB;
static uint8_t ss_dual_2_4G_pin = CONFIG_AIR_SLIDE_SWITCH_DUAL_2_4G_MODE_PIN;  /* default: GPIO35 */
static uint8_t ss_dual_active_high = 0;

#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
static bool app_ss_dual_suspend_resume = false;
#endif

/*============================================================================*/
/*  callback functions                                                        */
/*============================================================================*/
static void app_ss_dual__check_mode_timer_cb(struct k_timer *timer_id)
{
    hal_gpio_data_t gpio_level;
    hal_gpio_get_input(ss_dual_2_4G_pin, &gpio_level);

    printk("[ss_dual] check_mode_timer_cb, pin=%d, level=%d\r\n", ss_dual_2_4G_pin, gpio_level);
    APP_LOGI(thisMOD, "check_mode_timer_cb, pin=%d, level=%d", ss_dual_2_4G_pin, gpio_level);

    bool ret = app_ss_dual_check_ss_mode(gpio_level);
    if (ret) {
        APP_LOGI(thisMOD, "check_mode_timer_cb, mode unchanged or invalid, skip");
        return;
    }

    app_ss_dual_set_hid_flag();

    switch (app_ss_dual_mode) {
        case SS_MODE_2_4G:
            printk("[ss_dual] Change to SS_MODE_2_4G (GAMING)\r\n");
            APP_LOGI(thisMOD, "Change to SS_MODE_2_4G (GAMING)");
            app_ss_dual__change_slide_switch_position(SLIDE_SWITCH_POS_GAMING);
            break;
        case SS_MODE_OFF:
            printk("[ss_dual] Change to SS_MODE_OFF\r\n");
            APP_LOGI(thisMOD, "Change to SS_MODE_OFF");
            app_ss_dual__change_slide_switch_position(SLIDE_SWITCH_POS_OFF);
            break;
        default:
            break;
    }
}

static void slide_switch_dual_eint_callback(void *id)
{
    uint8_t pin = *(uint8_t *)id;
    printk("[ss_dual] eint_callback, pin=0x%X, debounce=%d\r\n", pin, ss_dual_debounce);
    APP_LOGI(thisMOD, "eint_callback, pin=0x%X, debounce=%d", pin, ss_dual_debounce);

    uint32_t state = app_state_current_state();
    if (state == APP_STATE_STANDBY
#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
        || (state == APP_STATE_2_4G_RECONNECT_RESUME_WAIT)
#endif
    ) {
        app_ss_dual__check_mode_timer_cb(&check_mode_timer_dual);
    } else {
        k_timer_stop(&check_mode_timer_dual);
        k_timer_start(&check_mode_timer_dual, K_MSEC(500), K_NO_WAIT);
    }
}

/*============================================================================*/
/*  event handlers                                                            */
/*============================================================================*/
static bool app_ss_dual_evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state *event = (struct evt_app_state *)evt_header;
    APP_LOGI(thisMOD, "evt_app_state, app_state=%d", event->app_state);

    switch (event->app_state) {
#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
        case APP_STATE_2_4G_CONNECTED_ACTIVE:
            if (app_ss_dual_suspend_resume) {
                app_ss_dual_exit_low_power();
                app_ss_dual_suspend_resume = false;
            }
            break;
        case APP_STATE_2_4G_RECONNECT_RESUME_WAIT:
            app_ss_dual_suspend_resume = true;
            break;
#endif
        case APP_STATE_STANDBY:
            if (app_battery__get_battery_power()) {
                app_ss_dual_enter_low_power_set_wakeup();
            }
            break;
        default:
            break;
    }
    return AF_TRAVERSE_NEXT;
}

static bool app_ss_dual_evt_active_status(const struct af_evt_header *evt_header)
{
    struct evt_active_status *event = (struct evt_active_status *)evt_header;
    APP_LOGI(thisMOD, "evt_active_status, active=%d, type=%d", event->active, event->type);

    uint32_t app_state = app_state_current_state();
    if (event->active &&
        (app_state == APP_STATE_STANDBY
#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
         || (app_state == APP_STATE_2_4G_RECONNECT_RESUME_WAIT)
#endif
        )) {
        switch (event->type) {
            case MOTION_SENSOR_WAKEUP:
            case WHEEL_WAKEUP:
            case KEY_WAKEUP:
            case SLIDE_SWITCH_WAKEUP:
#ifdef CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE
            case USB_PLUG_WAKEUP:
#endif
                app_ss_dual_exit_low_power();
#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
                app_ss_dual_suspend_resume = false;
#endif
                break;
            default:
                break;
        }
    }
    return AF_TRAVERSE_NEXT;
}

static bool app_ss_dual_evt_usb_status(const struct af_evt_header *evt_header)
{
    struct evt_usb_status *event = (struct evt_usb_status *)evt_header;
    APP_LOGI(thisMOD, "evt_usb_status, status=%d, debounce=%d", event->status, ss_dual_debounce);

    switch (event->status) {
        case USB_STATUS_PLUGGED_OUT:
            if (ss_dual_debounce != SS_DEBOUNCE_WITHOUT_USB) {
                ss_dual_debounce = SS_DEBOUNCE_WITHOUT_USB;
                hal_eint_set_debounce_time(ss_dual_2_4G_pin, ss_dual_debounce);
            }
            break;
        case USB_STATUS_PLUGGED_IN:
            if (ss_dual_debounce != SS_DEBOUNCE_WITH_USB) {
                ss_dual_debounce = SS_DEBOUNCE_WITH_USB;
                hal_eint_set_debounce_time(ss_dual_2_4G_pin, ss_dual_debounce);
            }
            break;
        default:
            break;
    }
    return AF_TRAVERSE_NEXT;
}

/*============================================================================*/
/*  private functions                                                         */
/*============================================================================*/
static void app_ss_dual_configure_gpio(void)
{
    /* Step 1: init & set to GPIO mode (follow HAL GPIO usage pattern) */
    hal_gpio_init(ss_dual_2_4G_pin);
    hal_pinmux_set_function(ss_dual_2_4G_pin, HAL_GPIO_35_GPIO35);
    hal_gpio_set_direction(ss_dual_2_4G_pin, HAL_GPIO_DIRECTION_INPUT);

    /* Step 2: configure EINT */
    hal_eint_status_t ret_log[3];
    hal_eint_config_t eint_config;
    eint_config.trigger_mode = HAL_EINT_EDGE_FALLING_AND_RISING;
    eint_config.debounce_time = SS_DEBOUNCE_WITHOUT_USB;

    ret_log[0] = hal_eint_init(ss_dual_2_4G_pin, &eint_config);

    /* Step 3: enable internal pull-up (after eint_init, which may reset pinmux) */
    hal_gpio_pull_up(ss_dual_2_4G_pin);

    ret_log[1] = hal_eint_register_callback(ss_dual_2_4G_pin,
                    slide_switch_dual_eint_callback, (void *)&ss_dual_2_4G_pin);

    hal_eint_enable(ss_dual_2_4G_pin);
    ret_log[2] = hal_eint_unmask(ss_dual_2_4G_pin);

    APP_LOGI(thisMOD, "configure_gpio: init=%d, register=%d, unmask=%d, pin=%d",
             ret_log[0], ret_log[1], ret_log[2], ss_dual_2_4G_pin);
}

static void app_ss_dual__get_init_ss_type(void)
{
    hal_gpio_data_t gpio_level;
    hal_gpio_get_input(ss_dual_2_4G_pin, &gpio_level);

    APP_LOGI(thisMOD, "get_init_ss_type, pin=%d, level=%d, active_high=%d",
             ss_dual_2_4G_pin, gpio_level, ss_dual_active_high);

    bool is_active = ss_dual_active_high ? (gpio_level != 0) : (gpio_level == 0);

    if (is_active) {
        app_ss_dual_mode = SS_MODE_2_4G;
    } else {
        app_ss_dual_mode = SS_MODE_OFF;
    }

    APP_LOGI(thisMOD, "get_init_ss_type, ss_type=%d", app_ss_dual_mode);
}

static bool app_ss_dual_check_ss_mode(hal_gpio_data_t gpio_level)
{
    static uint8_t prev_mode = SS_MODE_NONE;

    bool is_active = ss_dual_active_high ? (gpio_level != 0) : (gpio_level == 0);

    if (is_active) {
        app_ss_dual_mode = SS_MODE_2_4G;
    } else {
        /* If already in USB state, don't switch to OFF */
        if (app_state_check(TYPE_IN_USB_STATES)) {
            APP_LOGI(thisMOD, "Already in USB state, skip OFF mode");
            return true;
        }
        app_ss_dual_mode = SS_MODE_OFF;
    }

    if (app_ss_dual_mode == prev_mode) {
        return true;  /* mode unchanged */
    }
    prev_mode = app_ss_dual_mode;
    return false;
}

static void app_ss_dual_set_hid_flag(void)
{
    switch (app_ss_dual_mode) {
        case SS_MODE_2_4G:
            hid_common_set_hid_exp_flag(FLAG_BIT_SLIDE_SWITCH_POS);
            hid_common_set_hid_exp_flag(FLAG_BIT2_SLIDE_SWITCH_POS);
            break;
        case SS_MODE_OFF:
            hid_common_set_hid_exp_flag(FLAG_BIT_SLIDE_SWITCH_POS);
            hid_common_clear_hid_exp_flag(FLAG_BIT2_SLIDE_SWITCH_POS);
            break;
        default:
            break;
    }
    APP_LOGI(thisMOD, "set_hid_flag, mode=%d", app_ss_dual_mode);
}

static void app_ss_dual__announce_usb_status_event(uint8_t status)
{
    struct evt_usb_status *event = create_evt_usb_status();
    if (event) {
        event->status = status;
        AF_EVT_SUBMIT(event);
    }
}

static void app_ss_dual__change_slide_switch_position(uint8_t mode)
{
    APP_LOGI(thisMOD, "change_slide_switch_position, mode=%d", mode);

#ifdef CONFIG_AIR_USB_PLUG_AND_PLAY
    if (app_state_check(TYPE_IN_USB_STATES)) {
        APP_LOGI(thisMOD, "USB plugged, cannot change mode (PLUG_AND_PLAY=y)");
        return;
    }
#endif

    if (mode == SLIDE_SWITCH_POS_OFF) {
        goto _switch_pos;
    }

    /* Notify USB to disconnect when switching to 2.4G */
    if (app_usb_port__get_usb_plug_status()) {
        app_ss_dual__announce_usb_status_event(USB_STATUS_READY_TO_DISABLE);
    }

    uint8_t app_state = app_state_current_state();
    if (app_state == APP_STATE_STANDBY
#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
        || (app_state == APP_STATE_2_4G_RECONNECT_RESUME_WAIT)
#endif
    ) {
        app_ss_dual__announce_ss_wakeup_event();
    }

_switch_pos:
    {
        struct evt_slide_switch_status *event = create_evt_slide_switch_status();
        if (event) {
            event->position = mode;
            AF_EVT_SUBMIT(event);
        }
    }
}

static void app_ss_dual__announce_ss_wakeup_event(void)
{
    struct evt_active_status *event = create_evt_active_status();
    if (event) {
        event->active = true;
        event->type = SLIDE_SWITCH_WAKEUP;
        AF_EVT_SUBMIT(event);
    }
}

static void app_ss_dual_enter_low_power_set_wakeup(void)
{
    APP_LOGI(thisMOD, "enter_low_power, state=%d", app_ss_dual_low_power_state);
    if (!app_ss_dual_low_power_state) {
        extern hal_gpio_status_t hal_gpio_wakeup_extend_sleep_config(hal_gpio_pin_t gpio_pin);
        hal_gpio_wakeup_extend_sleep_config(ss_dual_2_4G_pin);
        ss_dual_debounce = SS_DEBOUNCE_EXTEND_SLEEP;
        hal_eint_set_debounce_time(ss_dual_2_4G_pin, ss_dual_debounce);
        APP_LOGI(thisMOD, "enter_low_power, debounce=%d", ss_dual_debounce);
        app_ss_dual_low_power_state = 1;
    }
    APP_LOGI(thisMOD, "[EINT_STA]=0x%08X, [EINT_STA1]=0x%08X",
             (unsigned int)(*(volatile uint32_t *)0x42140300),
             (unsigned int)(*(volatile uint32_t *)0x42140304));
    APP_LOGI(thisMOD, "[EINT_MASK]=0x%08X, [EINT_MASK1]=0x%08X",
             (unsigned int)(*(volatile uint32_t *)0x42140114),
             (unsigned int)(*(volatile uint32_t *)0x42140118));
}

static void app_ss_dual_exit_low_power(void)
{
    APP_LOGI(thisMOD, "exit_low_power, state=%d", app_ss_dual_low_power_state);
    if (app_ss_dual_low_power_state) {
        extern hal_gpio_status_t hal_gpio_wakeup_extend_sleep_clear(hal_gpio_pin_t gpio_pin);
        hal_gpio_wakeup_extend_sleep_clear(ss_dual_2_4G_pin);

        if (app_usb_port__get_usb_plug_status()) {
            ss_dual_debounce = SS_DEBOUNCE_WITH_USB;
        } else {
#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
            uint32_t state = app_state_current_state();
            if (state == APP_STATE_2_4G_RECONNECT_RESUME_WAIT) {
                ss_dual_debounce = SS_DEBOUNCE_EXTEND_SLEEP;
            } else
#endif
            {
                ss_dual_debounce = SS_DEBOUNCE_WITHOUT_USB;
            }
        }
        hal_eint_set_debounce_time(ss_dual_2_4G_pin, ss_dual_debounce);
        APP_LOGI(thisMOD, "exit_low_power, debounce=%d", ss_dual_debounce);
        app_ss_dual_low_power_state = 0;
    }
}

/*============================================================================*/
/*  public functions                                                          */
/*============================================================================*/
void app_slide_switch_dual__get_ss_type(uint8_t *ss_type)
{
    *ss_type = app_ss_dual_mode;
    APP_LOGI(thisMOD, "get_ss_type=%d", *ss_type);
}

uint8_t app_slide_switch_dual_init(uint8_t ss_2_4G_pin)
{
    static uint8_t init_flag = 1;
    if (init_flag) {
        ss_dual_2_4G_pin = ss_2_4G_pin;

#ifdef CONFIG_AIR_SLIDE_SWITCH_DUAL_2_4G_PIN_HIGH_ACTIVE
        ss_dual_active_high = 1;
#else
        ss_dual_active_high = 0;
#endif

        k_timer_init(&check_mode_timer_dual, app_ss_dual__check_mode_timer_cb, NULL);

        app_ss_dual_configure_gpio();
        app_ss_dual__get_init_ss_type();

        /* start GPIO polling test */
        k_work_schedule(&gpio_test_work, K_MSEC(100));

        printk("[ss_dual] init ok, pin=%d, active_high=%d, mode=%d\r\n",
                 ss_dual_2_4G_pin, ss_dual_active_high, app_ss_dual_mode);
        APP_LOGI(thisMOD, "init ok, pin=%d, active_high=%d, mode=%d",
                 ss_dual_2_4G_pin, ss_dual_active_high, app_ss_dual_mode);
        init_flag = 0;
    }
    return app_ss_dual_mode;
}

/*============================ Application Framework =========================*/
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_active_status, app_ss_dual_evt_active_status);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_app_state, app_ss_dual_evt_app_state);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_usb_status, app_ss_dual_evt_usb_status);

/*============================================================================*/

#endif /* CONFIG_AIR_DUAL_MODE_SLIDE_SWITCH */
