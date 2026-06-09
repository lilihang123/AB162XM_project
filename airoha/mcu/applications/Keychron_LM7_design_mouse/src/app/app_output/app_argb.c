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

/**
 * @file    app_argb_test.c
 * @brief   ARGB LED 灯效系统 for Keychron LM7.
 *
 * LED 分配（3颗 WS2812 灯珠）:

 *
 * 灯效规格:

 */
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <errno.h>
#include <string.h>

#include "hal_gpio.h"
#include "hal_gpio_internal.h"
#include "hal_aioadc.h"
#include "bsp_argb.h"
#include "argb_control_style_cfg.h"

#include "af_framework.h"
#include "af_events_declaration.h"
#include "app_state.h"
#include "app_battery.h"
#include "app_usb_port.h"
#include "app_argb.h"

#define thisMODULE app_argb_test
#define thisMOD "app_argb"
LOG_MODULE_REGISTER(thisMODULE);
#if 1/*关闭只开启测试代码*/

/* ══════════════════════════════════════════════════════════════════════════ */
/*  硬件配置                                                                  */
/* ══════════════════════════════════════════════════════════════════════════ */

#define LED_COUNT 3
#define LED_POWER_EN_PIN 39
#define REFRESH_MS 20 /* 50Hz */

/*
 * NONALIGN 模式: DMA 以 4 字节 word 传输, 硬件每 word 提取 3 字节(24bit)
 * 给一颗 LED。每颗 LED 占 4 字节 slot。
 */
#define ARGB_SLOT_SIZE 3  /* 每颗LED 3字节紧凑排列 */
#define ARGB_BUF_SIZE (LED_COUNT * ARGB_SLOT_SIZE)

/* ══════════════════════════════════════════════════════════════════════════ */
/*  ARGB 字节布局 — 根据硬件行为选择                                          */
/* ══════════════════════════════════════════════════════════════════════════ */
/*
 * overlay: ed_big=1, bit_nonrev=1, nonalign=1
 * 推荐先试 Layout 0，同时改 overlay ed_big=0, bit_nonrev=0 (最简单映射)
 * 如果不行再试 Layout 1,2,3
 */
#define ARGB_BYTE_LAYOUT 0 /* Layout 2: R,G,B,0 (WS2812标准RGB顺序) */

/* ── 测试开关: 置 1 则只亮白光, 跳过灯效引擎 ───────────────────────────── */
#define ARGB_TEST_WHITE_ONLY  0  /* 1=测试白光, 0=正常灯效 */

typedef struct
{
    uint8_t r, g, b;
} argb_color_t;

static inline void argb_write_led(uint8_t *buf, uint8_t idx, argb_color_t c)
{
    uint8_t off = idx * ARGB_SLOT_SIZE;
#if ARGB_BYTE_LAYOUT == 0
    buf[off + 0] = c.b;
    buf[off + 1] = c.r;
    buf[off + 2] = c.g;
#elif ARGB_BYTE_LAYOUT == 1
    buf[off + 0] = 0;
    buf[off + 1] = c.g;
    buf[off + 2] = c.r;
#elif ARGB_BYTE_LAYOUT == 2
    buf[off + 0] = c.r;
    buf[off + 1] = c.g;
    buf[off + 2] = c.b;
#elif ARGB_BYTE_LAYOUT == 3
    buf[off + 0] = c.b;
    buf[off + 1] = c.r;
    buf[off + 2] = c.g;
#else
    buf[off + 0] = c.g;
    buf[off + 1] = c.r;
    buf[off + 2] = c.b;
#endif
}

/* ══════════════════════════════════════════════════════════════════════════ */
/*  预设颜色                                                                  */
/* ══════════════════════════════════════════════════════════════════════════ */
#if ARGB_TEST_WHITE_ONLY == 0 && defined(CONFIG_AIR_MIDDLE_ARGB)

static const argb_color_t C_OFF = {0, 0, 0};
static const argb_color_t C_RED = {255, 0, 0};
static const argb_color_t C_GREEN = {0, 255, 0};
static const argb_color_t C_BLUE = {0, 0, 255};
static const argb_color_t C_WHITE = {255, 255, 255};
static const argb_color_t C_YELLOW = {255, 255, 0};
static const argb_color_t C_PURPLE = {255, 0, 255};

/* DPI 颜色: 1=400白  2=800绿  3=1600蓝  4=3200黄  5=5000红 */
static const argb_color_t g_dpi_colors[5] = {
    C_WHITE, C_GREEN, C_BLUE, C_YELLOW, C_RED};
/* 回报率颜色: 1=125白  2=500绿  3=1000蓝  4=2000黄  5=4000红  6=8000紫 */
static const argb_color_t g_rr_colors[6] = {
    C_WHITE, C_GREEN, C_BLUE, C_YELLOW, C_RED, C_PURPLE};
static uint8_t rr_idx(uint16_t hz)
{
    if (hz <= 125)
        return 0;
    if (hz <= 500)
        return 1;
    if (hz <= 1000)
        return 2;
    if (hz <= 2000)
        return 3;
    if (hz <= 4000)
        return 4;
    return 5; /* 8000 */
}

#endif /* ARGB_TEST_WHITE_ONLY == 0 */

/* ══════════════════════════════════════════════════════════════════════════ */
/*  灯效引擎                                                                  */
/* ══════════════════════════════════════════════════════════════════════════ */
#if ARGB_TEST_WHITE_ONLY == 0 && defined(CONFIG_AIR_MIDDLE_ARGB)

typedef enum
{
    EFF_OFF = 0,
    EFF_CONSTANT,
    EFF_SLOW_BLINK,
    EFF_FAST_BLINK,
    EFF_TIMED_ON,
    EFF_BLINK_N
} eff_type_t;

typedef struct
{
    eff_type_t type;
    argb_color_t on, off;
    uint32_t period_ms, on_ms, t0, dur_ms;
    uint8_t n;
    bool act;
} eff_t;

static eff_t g_eff[LED_COUNT];

static void e_off(eff_t *e) { memset(e, 0, sizeof(*e)); }
static void e_const(eff_t *e, argb_color_t c)
{
    e->type = EFF_CONSTANT;
    e->on = c;
    e->act = 1;
}
static void e_slow(eff_t *e, argb_color_t c)
{
    e->type = EFF_SLOW_BLINK;
    e->on = c;
    e->period_ms = 1000;
    e->on_ms = 500;
    e->t0 = k_uptime_get_32();
    e->act = 1;
}
static void e_fast(eff_t *e, argb_color_t c)
{
    e->type = EFF_FAST_BLINK;
    e->on = c;
    e->period_ms = 500;
    e->on_ms = 250;
    e->t0 = k_uptime_get_32();
    e->act = 1;
}
static void e_timed(eff_t *e, argb_color_t c, uint32_t ms)
{
    e->type = EFF_TIMED_ON;
    e->on = c;
    e->dur_ms = ms;
    e->t0 = k_uptime_get_32();
    e->act = 1;
}
static void e_blink_n(eff_t *e, argb_color_t c, uint8_t n, uint32_t p)
{
    e->type = EFF_BLINK_N;
    e->on = c;
    e->period_ms = p;
    e->on_ms = p / 2;
    e->n = n;
    e->t0 = k_uptime_get_32();
    e->act = 1;
}

static argb_color_t e_eval(eff_t *e)
{
    if (!e->act)
        return C_OFF;
    uint32_t dt = k_uptime_get_32() - e->t0;
    switch (e->type)
    {
    case EFF_CONSTANT:
        return e->on;
    case EFF_SLOW_BLINK:
    case EFF_FAST_BLINK:
        return (dt % e->period_ms < e->on_ms) ? e->on : C_OFF;
    case EFF_TIMED_ON:
        if (dt >= e->dur_ms)
        {
            e->act = 0;
            return C_OFF;
        }
        return e->on;
    case EFF_BLINK_N:
        if (dt / e->period_ms >= e->n)
        {
            e->act = 0;
            return C_OFF;
        }
        return (dt % e->period_ms < e->on_ms) ? e->on : C_OFF;
    default:
        return C_OFF;
    }
}

/* ══════════════════════════════════════════════════════════════════════════ */
/*  充电状态记忆（对码/回连结束后恢复充电灯效）                               */
/* ══════════════════════════════════════════════════════════════════════════ */
static bool g_charging_active = false;
static bool g_was_charging_before_pairing = false;

/* DPI/RR 切换时 3s 颜色覆盖（3灯同色，不修改 g_eff 基础状态） */
#define OVERRIDE_DUR_MS  3000
static bool g_override_active = false;
static argb_color_t g_override_color;
static uint32_t g_override_t0;

static void argb_restore_charging_if_needed(void)
{
    if (g_was_charging_before_pairing && g_charging_active)
    {
        eff_t *e = &g_eff[ARGB_LED_IDX_STATUS];
        if (!e->act || e->type == EFF_TIMED_ON)
        {
            /* 对码/回连灯效已结束，恢复充电灯 */
            if (app_battery__get_battery_level() < 100)
            {
                LOG_INF("[LED] restore CHARGING RED");
                e_const(e, C_RED);
            }
            else
            {
                LOG_INF("[LED] restore CHARGED GREEN");
                e_const(e, C_GREEN);
            }
            g_was_charging_before_pairing = false;
        }
    }
}

/* ══════════════════════════════════════════════════════════════════════════ */
/*  LED 电源管理（省电：灯全灭时关闭 POWER_EN）                                */
/* ══════════════════════════════════════════════════════════════════════════ */

static bool g_power_on = false;  /* LED_POWER_EN_PIN 当前状态 */

static inline void argb_power_on(void)
{
    if (!g_power_on) {
        g_power_on = true;
        hal_gpio_set_output(LED_POWER_EN_PIN, HAL_GPIO_DATA_HIGH);
    }
}

static inline void argb_power_off(void)
{
    if (g_power_on) {
        g_power_on = false;
        hal_gpio_set_output(LED_POWER_EN_PIN, HAL_GPIO_DATA_LOW);
    }
}

/* ══════════════════════════════════════════════════════════════════════════ */
/*  高层灯效 API                                                              */
/* ══════════════════════════════════════════════════════════════════════════ */

void app_argb_status_evt(argb_evt_status_t evt)
{
    eff_t *e = &g_eff[ARGB_LED_IDX_STATUS];
    switch (evt)
    {
    case ARGB_EVT_CHARGING:
        LOG_INF("[LED] CHARGING RED");
        argb_power_on();
        g_charging_active = true;
        g_was_charging_before_pairing = false;
        /* 对码优先：如果正在对码/回连，不覆盖 */
        if (e->act && (e->type == EFF_SLOW_BLINK || e->type == EFF_FAST_BLINK))
            break;
        e_const(e, C_RED);
        break;
    case ARGB_EVT_CHARGED:
        LOG_INF("[LED] CHARGED GREEN");
        argb_power_on();
        g_charging_active = true;
        g_was_charging_before_pairing = false;
        if (e->act && (e->type == EFF_SLOW_BLINK || e->type == EFF_FAST_BLINK))
            break;
        e_const(e, C_GREEN);
        break;
    case ARGB_EVT_PAIRING_START:
        LOG_INF("[LED] PAIRING SLOW");
        argb_power_on();
        /* 记下充电状态，对码优先 */
        if (g_charging_active && e->act)
            g_was_charging_before_pairing = true;
        e_slow(e, C_GREEN);
        break;
    case ARGB_EVT_PAIRING_OK:
        LOG_INF("[LED] PAIRING OK 3s");
        argb_power_on();
        e_timed(e, C_GREEN, 3000);
        break;
    case ARGB_EVT_PAIRING_TIMEOUT:
        LOG_INF("[LED] TIMEOUT SLEEP");
        for (int i = 0; i < LED_COUNT; i++)
            e_off(&g_eff[i]);
        g_was_charging_before_pairing = false;
        argb_power_off();
        break;
    case ARGB_EVT_RECONNECT_START:
        LOG_INF("[LED] RECONN FAST");
        argb_power_on();
        if (g_charging_active && e->act)
            g_was_charging_before_pairing = true;
        e_fast(e, C_GREEN);
        break;
    case ARGB_EVT_RECONNECT_OK:
        LOG_INF("[LED] RECONN OK 3s");
        argb_power_on();
        e_timed(e, C_GREEN, 3000);
        break;
    case ARGB_EVT_FORCE_PAIRING:
        LOG_INF("[LED] FORCE PAIRING SLOW");
        argb_power_on();
        if (g_charging_active && e->act)
            g_was_charging_before_pairing = true;
        e_slow(e, C_GREEN);
        break;
    case ARGB_EVT_FACTORY_RESET:
        LOG_INF("[LED] FACTORY RESET flash 3");
        argb_power_on();
        for (int i = 0; i < LED_COUNT; i++)
            e_blink_n(&g_eff[i], C_WHITE, 3, 400);
        g_charging_active = false;
        g_was_charging_before_pairing = false;
        break;
    case ARGB_EVT_OFF:
        LOG_INF("[LED] ALL OFF");
        for (int i = 0; i < LED_COUNT; i++)
            e_off(&g_eff[i]);
        g_was_charging_before_pairing = false;
        argb_power_off();
        break;
    }
}

void app_argb_dpi_evt(argb_evt_dpi_t evt, uint8_t dpi_idx)
{
    if ((evt == ARGB_DPI_EVT_CHANGE || evt == ARGB_DPI_EVT_FIRST_CONNECT) && dpi_idx < 5)
    {
        LOG_INF("[LED] DPI idx=%d on 3s", dpi_idx);
        argb_power_on();
        /* 3灯同色覆盖 3s，不破坏底层状态灯效 */
        g_override_active = true;
        g_override_color = g_dpi_colors[dpi_idx];
        g_override_t0 = k_uptime_get_32();
    }
}

void app_argb_rr_evt(argb_evt_rr_t evt, uint16_t hz)
{
    if (evt == ARGB_RR_EVT_CHANGE || evt == ARGB_RR_EVT_FIRST_CONNECT)
    {
        uint8_t idx = rr_idx(hz);
        LOG_INF("[LED] RR %dHz (idx=%d) on 3s", hz, idx);
        argb_power_on();
        /* 3灯同色覆盖 3s，不破坏底层状态灯效 */
        g_override_active = true;
        g_override_color = g_rr_colors[idx];
        g_override_t0 = k_uptime_get_32();
    }
}

void app_argb_wakeup(void)
{
    LOG_INF("[LED] Wakeup - restart pairing");
    /* 对码超时休眠后，按任意键/移动鼠标 → 重新进入对码 */
    app_argb_status_evt(ARGB_EVT_PAIRING_START);
}

#else  /* ARGB_TEST_WHITE_ONLY == 1: 空桩 */
void app_argb_status_evt(argb_evt_status_t evt) { (void)evt; }
void app_argb_dpi_evt(argb_evt_dpi_t evt, uint8_t dpi_idx)
{
    (void)evt;
    (void)dpi_idx;
}
void app_argb_rr_evt(argb_evt_rr_t evt, uint16_t hz)
{
    (void)evt;
    (void)hz;
}
void app_argb_wakeup(void) {}
#endif /* ARGB_TEST_WHITE_ONLY */

/* ══════════════════════════════════════════════════════════════════════════ */
/*  DMA 硬件层                                                                */
/* ══════════════════════════════════════════════════════════════════════════ */
#if defined(CONFIG_AIR_MIDDLE_ARGB)

static uint8_t argb_buf[ARGB_BUF_SIZE] __aligned(4); /* DMA需要4字节对齐 */
static bool g_running;
static K_SEM_DEFINE(argb_frame_done, 0, 1);

static void argb_isr_cb(void *ud)
{
    k_sem_give(&argb_frame_done);
    (void)ud;
}

static int argb_send_frame(void)
{
    argb_style_config_t cfg = {
        .type = argb_occupy_normal, .argb_num = LED_COUNT, .pattern = 0, .repeat = 1, .argb_data = argb_buf};
    int r = bsp_argb_realtime_config(&cfg);
    if (r)
        return r;
    if (k_sem_take(&argb_frame_done, K_MSEC(10)))
    {
        LOG_WRN("timeout");
        return -ETIMEDOUT;
    }
    return 0;
}

/* ══════════════════════════════════════════════════════════════════════════ */
/*  Refresh thread 刷新线程                                                                  */
/* ══════════════════════════════════════════════════════════════════════════ */

#define STK 1024
#define PRI 7
static K_THREAD_STACK_DEFINE(rstk, STK);
static struct k_thread rth;

static void refresh(void *a, void *b, void *c)
{
#if ARGB_TEST_WHITE_ONLY  /*持续发送相同的颜色*/
    static const argb_color_t red   = {0xFF, 0x00, 0};
    static const argb_color_t green = {0, 0xFF, 0};
    static const argb_color_t blue  = {0, 0, 0xFF};
    LOG_INF("ARGB test mode: R,G,B per LED (layout=%d)", ARGB_BYTE_LAYOUT);
    while (g_running)
    {
        argb_write_led(argb_buf, 0, red);
        argb_write_led(argb_buf, 1, green);
        argb_write_led(argb_buf, 2, blue);
        if (argb_send_frame())  //实际发送141112   231
            LOG_ERR("send fail");
        // k_sleep(K_MSEC(REFRESH_MS)); //20ms
        k_sleep(K_MSEC(1000)); /* 测试模式颜色不变, 1s刷1帧即可 */
    }

#else
    // LOG_INF("ARGB refresh (layout=%d)", ARGB_BYTE_LAYOUT);
    while (g_running)
    {
        /* 3灯同色：只用 g_eff[0]（状态灯）驱动，DPI/RR 切换时临时覆盖 */
        static argb_color_t prev = {0xFF, 0xFF, 0xFF}; /* 首帧强制发送 */
        argb_color_t c;
        if (g_override_active) {
            if (k_uptime_get_32() - g_override_t0 >= OVERRIDE_DUR_MS) {
                g_override_active = false;
                c = e_eval(&g_eff[0]);
            } else {
                c = g_override_color;
            }
        } else {
            c = e_eval(&g_eff[0]);
        }
        /* 灯全黑时关电省电（不改变点灯逻辑，仅电源管理） */
        if (c.r == 0 && c.g == 0 && c.b == 0 && g_power_on) {
            argb_power_off();
        }

        if (c.r != prev.r || c.g != prev.g || c.b != prev.b) {
            prev = c;
            for (int i = 0; i < LED_COUNT; i++)
                argb_write_led(argb_buf, i, c);
            if (argb_send_frame())
                LOG_ERR("send fail");
        }
        k_sleep(K_MSEC(REFRESH_MS));
    }
#endif
}

#endif /* defined(CONFIG_AIR_MIDDLE_ARGB) */

/* ══════════════════════════════════════════════════════════════════════════ */
/*  Application Framework 事件处理                                            */
/* ══════════════════════════════════════════════════════════════════════════ */

static uint8_t g_prev_state = 0xFF;

static bool on_state(const struct af_evt_header *h)
{
    uint8_t s = ((struct evt_app_state *)h)->app_state;
    LOG_INF("[EVT] state=%d prev=%d", s, g_prev_state);
    switch (s)
    {
    case APP_STATE_USB_ACTIVE:
        /* 有线模式: 不休眠; 充电指示 */
        if (app_battery__get_bat_charge_status())
            app_argb_status_evt(app_battery__get_battery_level() < 100 ? ARGB_EVT_CHARGING : ARGB_EVT_CHARGED);
        break;
    case APP_STATE_2_4G_PAIRING:
        app_argb_status_evt(ARGB_EVT_PAIRING_START);
        break;
    case APP_STATE_2_4G_RECONNECT:
        app_argb_status_evt(ARGB_EVT_RECONNECT_START);
        break;
    case APP_STATE_2_4G_CONNECTED:
    case APP_STATE_2_4G_CONNECTED_ACTIVE:
        /* 区分对码成功 vs 回连成功 */
        if (g_prev_state == APP_STATE_2_4G_PAIRING)
            app_argb_status_evt(ARGB_EVT_PAIRING_OK);
        else if (g_prev_state == APP_STATE_2_4G_RECONNECT)
            app_argb_status_evt(ARGB_EVT_RECONNECT_OK);
        /* 连接后恢复充电灯（如果之前在充电） */
        #if ARGB_TEST_WHITE_ONLY == 0 && defined(CONFIG_AIR_MIDDLE_ARGB)
        argb_restore_charging_if_needed();
        #endif
        break;
    case APP_STATE_BT_CONNECTED_ACTIVE:
        app_argb_status_evt(ARGB_EVT_OFF);
        break;
    case APP_STATE_STANDBY:
        /* 有线模式下不休眠，不关灯 */
        if (g_prev_state != APP_STATE_USB_ACTIVE && g_prev_state != APP_STATE_USB_CONNECTED)
            app_argb_status_evt(ARGB_EVT_OFF);
        break;
    case APP_STATE_DISCONNECTED:
        app_argb_status_evt(ARGB_EVT_OFF);
        break;
    }
    g_prev_state = s;
    return AF_TRAVERSE_NEXT;
}

static bool on_bat(const struct af_evt_header *h)
{
    struct evt_app_battery *e = (struct evt_app_battery *)h;
    LOG_INF("[EVT] bat=%d", e->status);
    switch (e->status)
    {
    case BAT_EVT_CHG_ENABLE_STA_CHANGE:
        if (app_battery__get_bat_charge_status() && app_battery__get_battery_level() < 100)
            app_argb_status_evt(ARGB_EVT_CHARGING);
        break;
    case BAT_EVT_END_OF_CHARGE:
        app_argb_status_evt(ARGB_EVT_CHARGED);
        break;
    case BAT_EVT_LOW_BAT_WARNING:
        LOG_WRN("Low battery!");
        break;
    default:
        break;
    }
    return AF_TRAVERSE_NEXT;
}

static bool on_usb(const struct af_evt_header *h)
{
    struct evt_usb_status *e = (struct evt_usb_status *)h;
    if (e->status == 1 && app_battery__get_bat_charge_status())
        app_argb_status_evt(app_battery__get_battery_level() < 100 ? ARGB_EVT_CHARGING : ARGB_EVT_CHARGED);
    else if (e->status == 0)
        app_argb_status_evt(ARGB_EVT_OFF);
    return AF_TRAVERSE_NEXT;
}

static bool on_dpi(const struct af_evt_header *h)
{
    app_argb_dpi_evt(ARGB_DPI_EVT_CHANGE, ((struct evt_dpi_status *)h)->dpi_idx);
    return AF_TRAVERSE_NEXT;
}

static bool on_rr(const struct af_evt_header *h)
{
    app_argb_rr_evt(ARGB_RR_EVT_CHANGE, ((struct evt_rr_status *)h)->RR);
    return AF_TRAVERSE_NEXT;
}

AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_app_state, on_state);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_app_battery, on_bat);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_usb_status, on_usb);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_dpi_status, on_dpi);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_rr_status, on_rr);

/* ══════════════════════════════════════════════════════════════════════════ */
/*  Public API                                                                */
/* ══════════════════════════════════════════════════════════════════════════ */

int app_argb_init(void)
{
#if defined(CONFIG_AIR_MIDDLE_ARGB)
    hal_gpio_init(LED_POWER_EN_PIN);
    hal_gpio_set_output(LED_POWER_EN_PIN, HAL_GPIO_DATA_HIGH);
    g_power_on = true;
    LOG_INF("POWER_EN ON");
    
#if ARGB_TEST_WHITE_ONLY == 0
    for (int i = 0; i < LED_COUNT; i++)
        e_off(&g_eff[i]);
#endif
    memset(argb_buf, 0, sizeof(argb_buf));

    bsp_argb_register_isr(argb_isr_cb, NULL);
    if (bsp_argb_enable() != BSP_ARGB_STATUS_OK)
    {
        LOG_ERR("enable fail");
        return -EIO;
    }

    g_running = true;
    k_thread_create(&rth, rstk, STK, refresh, NULL, NULL, NULL, PRI, 0, K_NO_WAIT);
    LOG_INF("ARGB LED system ready");
#endif
    return 0;
}

int app_argb_stop(void)
{
#if defined(CONFIG_AIR_MIDDLE_ARGB)
    g_running = false;
    k_sleep(K_MSEC(REFRESH_MS + 50));
#if ARGB_TEST_WHITE_ONLY == 0
    for (int i = 0; i < LED_COUNT; i++)
        e_off(&g_eff[i]);
#endif
    memset(argb_buf, 0, sizeof(argb_buf));
    argb_send_frame();
    g_power_on = false;
    hal_gpio_set_output(LED_POWER_EN_PIN, HAL_GPIO_DATA_LOW);
    bsp_argb_disable();
    LOG_INF("ARGB stopped");
#endif /* defined(CONFIG_AIR_MIDDLE_ARGB) */
    return 0;
}
#else /*测试 */
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include "app_argb.h"
#include "hal_gpio.h"
#include "hal_pinmux_define.h"
#include "argb_middle_control.h"

// LOG_MODULE_REGISTER(app_argb);

/* 最大支持的 LED 数量 */
#define ARGB_MAX_LED_COUNT     5

/* 每颗 LED 的字节数（GRB 格式，nonalign 模式为 3 字节） */
#define ARGB_BYTES_PER_LED     3

/* 颜色数据缓冲区：用于缓存待发送的颜色数据，需4字节对齐给DMA */
static uint8_t app_argb_color_buf[ARGB_MAX_LED_COUNT * ARGB_BYTES_PER_LED] __aligned(4);
static bool    app_argb_initialized = false;

/*
 * 1 秒白光线程
 * 每 1 秒将 3 颗 LED 都设置为白色（GRB = 0xFF,0xFF,0xFF）
 * 在 app_argb_init() 末尾自动启动，调用 init 即可看到效果。
 */
#define ARGB_WHITE_THREAD_INTERVAL_MS   1000
#define ARGB_WHITE_LED_COUNT            3
#define ARGB_WHITE_THREAD_STACK_SIZE    1024  /* DMA/信号量需要较大栈 */
#define ARGB_WHITE_THREAD_PRIORITY      5

/* 3 颗 LED 全白的 GRB 数据 */
static const uint8_t app_argb_white_data[ARGB_MAX_LED_COUNT * ARGB_BYTES_PER_LED] = {
    0x12, 0x13, 0x14,   /* LED0: */
    0x24, 0x25, 0x26,   /* LED1: */
    0x34, 0x35, 0x31,   /* LED2: */
    0x42, 0x4F, 0x40,   /* LED4: */
    0x52, 0x54, 0x56,   /* LED5: */
};

static struct k_thread app_argb_white_thread_data;
static K_THREAD_STACK_DEFINE(app_argb_white_thread_stack, ARGB_WHITE_THREAD_STACK_SIZE);

/**
 * @brief ARGB 播放完成回调函数
 *
 * 当 ARGB 控制器完成一轮数据发送后调用。
 * 用户可在此处添加播放完成后的处理逻辑（如链式播放）。
 */
static void app_argb_callback(void *user_data)
{
    (void)user_data;
}

int app_argb_set_colors(uint8_t *colors, uint8_t count)
{
    argb_style_config_t config;

    if (!app_argb_initialized) {
        LOG_ERR("ARGB not initialized");
        return -1;
    }
    if (colors == NULL || count == 0) {
        LOG_ERR("ARGB invalid parameters");
        return -1;
    }
    if (count > ARGB_MAX_LED_COUNT) {
        LOG_WRN("ARGB LED count %d exceeds max %d, truncating", count, ARGB_MAX_LED_COUNT);
        count = ARGB_MAX_LED_COUNT;
    }

    /* 缓存颜色数据（确保 DMA 传输期间数据稳定） */
    memcpy(app_argb_color_buf, colors, ARGB_MAX_LED_COUNT * ARGB_BYTES_PER_LED);

    /*
     * 硬件字节补偿: ed_big=0 (小端) 时，nonalign 模式每3字节组左移1字节
     *   buffer [b0, b1, b2] → 实际输出 [b1, b2, b0]
     * 所以预旋转：按 [b2, b0, b1] 重排
     */
    // for (int i = 0; i < count; i++) {
    //     uint8_t *g = &app_argb_color_buf[i * 3];
    //     uint8_t tmp = g[0];
    //     g[0] = g[2];
    //     g[2] = g[1];
    //     g[1] = tmp;
    // }

    /* 构造 ARGB 配置 */
    config.type      = 0;       /* 数据类型 */
    config.argb_num  = ARGB_WHITE_LED_COUNT;   /* LED 数量 */
    config.pattern   = 0;       /* 模式索引 */
    config.repeat    = 1;       /* 播放次数（1 = 单次） */
    config.argb_data = app_argb_color_buf;

    /* 配置数据并启动播放 */
    if (bsp_argb_realtime_config(&config) != BSP_ARGB_STATUS_OK) {
        LOG_ERR("ARGB set colors failed");
        return -1;
    }

    return 0;
}

/**
 * @brief 白光线程入口
 *        每 1 秒发送一包白光数据到 3 颗 LED。
 */
static void app_argb_white_thread_entry(void *arg1, void *arg2, void *arg3)
{
    (void)arg1;
    (void)arg2;
    (void)arg3;

    while (1) {
        app_argb_set_colors((uint8_t *)app_argb_white_data, ARGB_WHITE_LED_COUNT);
        k_msleep(ARGB_WHITE_THREAD_INTERVAL_MS);
    }
}

int app_argb_init(void)
{
    #if defined (CONFIG_AIR_MIDDLE_ARGB)
    if (app_argb_initialized) {
        LOG_WRN("ARGB already initialized");
        return -1;
    }

    /* 注册 ARGB 回调 */
    if (bsp_argb_register_isr(app_argb_callback, NULL) != BSP_ARGB_STATUS_OK) {
        LOG_ERR("ARGB register callback failed");
        return -1;
    }

    /* 使能 ARGB 硬件 */
    if (bsp_argb_enable() != BSP_ARGB_STATUS_OK) {
        LOG_ERR("ARGB enable failed");
        return -1;
    }

    app_argb_initialized = true;
    LOG_INF("ARGB initialized, GPIO34, max %d LEDs", ARGB_MAX_LED_COUNT);

    /* 自动启动白光线程，每 1 秒刷新一次 */
    k_thread_create(&app_argb_white_thread_data,
                    app_argb_white_thread_stack,
                    K_THREAD_STACK_SIZEOF(app_argb_white_thread_stack),
                    app_argb_white_thread_entry,
                    NULL, NULL, NULL,
                    ARGB_WHITE_THREAD_PRIORITY,
                    0,
                    K_NO_WAIT);
    k_thread_name_set(&app_argb_white_thread_data, "app_argb_white");
    LOG_INF("ARGB white thread started, interval %dms", ARGB_WHITE_THREAD_INTERVAL_MS);
    #endif /*END _CONFIG_AIR_MIDDLE_RGB_*/
    return 0;
}


#endif


