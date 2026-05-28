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
 *   LED[0] (STATUS): 充电/对码/回连 状态指示灯
 *   LED[1] (DPI):    DPI 档位指示灯（首次蓝灯，之后记忆上次颜色）
 *   LED[2] (RR):     回报率指示灯（首次蓝灯，之后记忆上次颜色）
 *
 * 灯效规格:
 *   有线模式: 充电中红灯常亮, 充满绿灯常亮
 *   2.4G对码: 绿灯慢闪(1s/次) 3min, 成功绿灯3s后灭, 超时休眠
 *   2.4G回连: 绿灯快闪(0.5s/次), 成功绿灯3s后灭
 *   强制对码: 长按左+中+右键3s (由app_button处理, 进入APP_STATE_2_4G_PAIRING)
 */
#if 1
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
#include "app_argb_test.h"

#define thisMODULE app_argb_test
#define thisMOD    "app_argb"
LOG_MODULE_REGISTER(thisMODULE);

/* ══════════════════════════════════════════════════════════════════════════ */
/*  硬件配置                                                                  */
/* ══════════════════════════════════════════════════════════════════════════ */

#define LED_COUNT           3
#define LED_POWER_EN_PIN    39
#define REFRESH_MS          20      /* 50Hz */

/*
 * NONALIGN 模式: DMA 以 4 字节 word 传输, 硬件每 word 提取 3 字节(24bit)
 * 给一颗 LED。每颗 LED 占 4 字节 slot。
 */
#define ARGB_SLOT_SIZE      4
#define ARGB_BUF_SIZE       (LED_COUNT * ARGB_SLOT_SIZE)

/* ══════════════════════════════════════════════════════════════════════════ */
/*  ARGB 字节布局 — 根据硬件行为选择                                          */
/* ══════════════════════════════════════════════════════════════════════════ */
/*
 * overlay: ed_big=1, bit_nonrev=1, nonalign=1
 * 推荐先试 Layout 0，同时改 overlay ed_big=0, bit_nonrev=0 (最简单映射)
 * 如果不行再试 Layout 1,2,3
 */
#define ARGB_BYTE_LAYOUT  0   /* 0:G,R,B,0  1:0,G,R,B  2:R,G,B,0  3:B,R,G,0 */

typedef struct { uint8_t r, g, b; } argb_color_t;

static inline void argb_write_led(uint8_t *buf, uint8_t idx, argb_color_t c)
{
    uint8_t off = idx * ARGB_SLOT_SIZE;
#if ARGB_BYTE_LAYOUT == 0
    buf[off+0]=c.g; buf[off+1]=c.r; buf[off+2]=c.b; buf[off+3]=0;
#elif ARGB_BYTE_LAYOUT == 1
    buf[off+0]=0;   buf[off+1]=c.g; buf[off+2]=c.r; buf[off+3]=c.b;
#elif ARGB_BYTE_LAYOUT == 2
    buf[off+0]=c.r; buf[off+1]=c.g; buf[off+2]=c.b; buf[off+3]=0;
#elif ARGB_BYTE_LAYOUT == 3
    buf[off+0]=c.b; buf[off+1]=c.r; buf[off+2]=c.g; buf[off+3]=0;
#else
    buf[off+0]=c.g; buf[off+1]=c.r; buf[off+2]=c.b; buf[off+3]=0;
#endif
}

/* ══════════════════════════════════════════════════════════════════════════ */
/*  预设颜色                                                                  */
/* ══════════════════════════════════════════════════════════════════════════ */

static const argb_color_t C_OFF   = {0,0,0};
static const argb_color_t C_RED   = {255,0,0};
static const argb_color_t C_GREEN = {0,255,0};
/* C_BLUE/C_WHITE/C_YELLOW/C_MAGENTA — 按需取消注释使用 */

static const argb_color_t g_dpi_colors[5] = {
    {0,0,255}, {0,255,0}, {255,255,0}, {255,0,0}, {255,0,255}
};
static const argb_color_t g_rr_colors[4] = {
    {255,0,0}, {0,255,0}, {0,0,255}, {255,255,255}
};
static uint8_t rr_idx(uint16_t hz) {
    return (hz<=125)?0:(hz<=250)?1:(hz<=500)?2:3;
}

/* ══════════════════════════════════════════════════════════════════════════ */
/*  灯效引擎                                                                  */
/* ══════════════════════════════════════════════════════════════════════════ */

typedef enum {
    EFF_OFF=0, EFF_CONSTANT, EFF_SLOW_BLINK, EFF_FAST_BLINK,
    EFF_TIMED_ON, EFF_BLINK_N
} eff_type_t;

typedef struct {
    eff_type_t  type;
    argb_color_t on, off;
    uint32_t    period_ms, on_ms, t0, dur_ms;
    uint8_t     n;
    bool        act;
} eff_t;

static eff_t g_eff[LED_COUNT];

static void e_off(eff_t *e)        { memset(e,0,sizeof(*e)); }
static void e_const(eff_t *e, argb_color_t c)
    { e->type=EFF_CONSTANT; e->on=c; e->act=1; }
static void e_slow(eff_t *e, argb_color_t c)
    { e->type=EFF_SLOW_BLINK; e->on=c; e->period_ms=1000; e->on_ms=500; e->t0=k_uptime_get_32(); e->act=1; }
static void e_fast(eff_t *e, argb_color_t c)
    { e->type=EFF_FAST_BLINK; e->on=c; e->period_ms=500; e->on_ms=250; e->t0=k_uptime_get_32(); e->act=1; }
static void e_timed(eff_t *e, argb_color_t c, uint32_t ms)
    { e->type=EFF_TIMED_ON; e->on=c; e->dur_ms=ms; e->t0=k_uptime_get_32(); e->act=1; }
static void e_blink_n(eff_t *e, argb_color_t c, uint8_t n, uint32_t p)
    { e->type=EFF_BLINK_N; e->on=c; e->period_ms=p; e->on_ms=p/2; e->n=n; e->t0=k_uptime_get_32(); e->act=1; }

static argb_color_t e_eval(eff_t *e)
{
    if (!e->act) return C_OFF;
    uint32_t dt = k_uptime_get_32() - e->t0;
    switch (e->type) {
    case EFF_CONSTANT:  return e->on;
    case EFF_SLOW_BLINK:
    case EFF_FAST_BLINK:return (dt%e->period_ms < e->on_ms)?e->on:C_OFF;
    case EFF_TIMED_ON:  if(dt>=e->dur_ms){e->act=0;return C_OFF;} return e->on;
    case EFF_BLINK_N:   if(dt/e->period_ms >= e->n){e->act=0;return C_OFF;}
                        return (dt%e->period_ms < e->on_ms)?e->on:C_OFF;
    default: return C_OFF;
    }
}

/* ══════════════════════════════════════════════════════════════════════════ */
/*  高层灯效 API                                                              */
/* ══════════════════════════════════════════════════════════════════════════ */

void app_argb_status_evt(argb_evt_status_t evt)
{
    eff_t *e = &g_eff[ARGB_LED_IDX_STATUS];
    switch (evt) {
    case ARGB_EVT_CHARGING:       LOG_INF("[LED] CHARGING RED");    e_const(e, C_RED); break;
    case ARGB_EVT_CHARGED:        LOG_INF("[LED] CHARGED GREEN");   e_const(e, C_GREEN); break;
    case ARGB_EVT_PAIRING_START:  LOG_INF("[LED] PAIRING SLOW");    e_slow(e, C_GREEN); break;
    case ARGB_EVT_PAIRING_OK:     LOG_INF("[LED] PAIRING OK 3s");   e_timed(e, C_GREEN, 3000); break;
    case ARGB_EVT_PAIRING_TIMEOUT:LOG_INF("[LED] TIMEOUT SLEEP");   for(int i=0;i<LED_COUNT;i++)e_off(&g_eff[i]); break;
    case ARGB_EVT_RECONNECT_START:LOG_INF("[LED] RECONN FAST");     e_fast(e, C_GREEN); break;
    case ARGB_EVT_RECONNECT_OK:   LOG_INF("[LED] RECONN OK 3s");    e_timed(e, C_GREEN, 3000); break;
    case ARGB_EVT_OFF:            LOG_INF("[LED] ALL OFF");         for(int i=0;i<LED_COUNT;i++)e_off(&g_eff[i]); break;
    }
}

void app_argb_dpi_evt(argb_evt_dpi_t evt, uint8_t dpi_idx)
{
    if (evt==ARGB_DPI_EVT_CHANGE && dpi_idx<5) {
        LOG_INF("[LED] DPI idx=%d blink %d", dpi_idx, dpi_idx+1);
        e_blink_n(&g_eff[ARGB_LED_IDX_DPI], g_dpi_colors[dpi_idx], dpi_idx+1, 400);
    }
}

void app_argb_rr_evt(argb_evt_rr_t evt, uint16_t hz)
{
    if (evt==ARGB_RR_EVT_CHANGE) {
        LOG_INF("[LED] RR %dHz blink 2", hz);
        e_blink_n(&g_eff[ARGB_LED_IDX_RR], g_rr_colors[rr_idx(hz)], 2, 400);
    }
}

void app_argb_wakeup(void) { LOG_INF("[LED] Wakeup"); }

/* ══════════════════════════════════════════════════════════════════════════ */
/*  DMA 硬件层                                                                */
/* ══════════════════════════════════════════════════════════════════════════ */

static uint8_t  argb_buf[ARGB_BUF_SIZE];
static bool     g_running;
static K_SEM_DEFINE(argb_frame_done, 0, 1);

static void argb_isr_cb(void *ud) { k_sem_give(&argb_frame_done); (void)ud; }

static int argb_send_frame(void)
{
    argb_style_config_t cfg = {
        .type=argb_occupy_normal, .argb_num=LED_COUNT,
        .pattern=0, .repeat=1, .argb_data=argb_buf
    };
    int r = bsp_argb_realtime_config(&cfg);
    if (r) return r;
    if (k_sem_take(&argb_frame_done, K_MSEC(10))) { LOG_WRN("timeout"); return -ETIMEDOUT; }
    return 0;
}

/* ══════════════════════════════════════════════════════════════════════════ */
/*  刷新线程                                                                  */
/* ══════════════════════════════════════════════════════════════════════════ */

#define STK 1024
#define PRI 7
static K_THREAD_STACK_DEFINE(rstk, STK);
static struct k_thread     rth;

static void refresh(void *a, void *b, void *c)
{
    LOG_INF("ARGB refresh (layout=%d)", ARGB_BYTE_LAYOUT);
    while (g_running) {
        for (int i=0;i<LED_COUNT;i++) argb_write_led(argb_buf, i, e_eval(&g_eff[i]));
        if (argb_send_frame()) LOG_ERR("send fail");
        k_sleep(K_MSEC(REFRESH_MS));
    }
}

/* ══════════════════════════════════════════════════════════════════════════ */
/*  Application Framework 事件处理                                            */
/* ══════════════════════════════════════════════════════════════════════════ */

static bool on_state(const struct af_evt_header *h)
{
    uint8_t s = ((struct evt_app_state*)h)->app_state;
    LOG_INF("[EVT] state=%d", s);
    switch (s) {
    case APP_STATE_USB_ACTIVE:
        if (app_battery__get_bat_charge_status())
            app_argb_status_evt(app_battery__get_battery_level()<100?ARGB_EVT_CHARGING:ARGB_EVT_CHARGED);
        break;
    case APP_STATE_2_4G_PAIRING:    app_argb_status_evt(ARGB_EVT_PAIRING_START); break;
    case APP_STATE_2_4G_RECONNECT:  app_argb_status_evt(ARGB_EVT_RECONNECT_START); break;
    case APP_STATE_2_4G_CONNECTED_ACTIVE: app_argb_status_evt(ARGB_EVT_RECONNECT_OK); break;
    case APP_STATE_BT_CONNECTED_ACTIVE:   app_argb_status_evt(ARGB_EVT_OFF); break;
    case APP_STATE_STANDBY:
    case APP_STATE_DISCONNECTED:    app_argb_status_evt(ARGB_EVT_OFF); break;
    }
    return AF_TRAVERSE_NEXT;
}

static bool on_bat(const struct af_evt_header *h)
{
    struct evt_app_battery *e = (struct evt_app_battery*)h;
    LOG_INF("[EVT] bat=%d", e->status);
    switch (e->status) {
    case BAT_EVT_CHG_ENABLE_STA_CHANGE:
        if (app_battery__get_bat_charge_status() && app_battery__get_battery_level()<100)
            app_argb_status_evt(ARGB_EVT_CHARGING);
        break;
    case BAT_EVT_END_OF_CHARGE: app_argb_status_evt(ARGB_EVT_CHARGED); break;
    case BAT_EVT_LOW_BAT_WARNING: LOG_WRN("Low battery!"); break;
    default: break;
    }
    return AF_TRAVERSE_NEXT;
}

static bool on_usb(const struct af_evt_header *h)
{
    struct evt_usb_status *e = (struct evt_usb_status*)h;
    if (e->status==1 && app_battery__get_bat_charge_status())
        app_argb_status_evt(app_battery__get_battery_level()<100?ARGB_EVT_CHARGING:ARGB_EVT_CHARGED);
    else if (e->status==0) app_argb_status_evt(ARGB_EVT_OFF);
    return AF_TRAVERSE_NEXT;
}

static bool on_dpi(const struct af_evt_header *h)
    { app_argb_dpi_evt(ARGB_DPI_EVT_CHANGE, ((struct evt_dpi_status*)h)->dpi_idx); return AF_TRAVERSE_NEXT; }

static bool on_rr(const struct af_evt_header *h)
    { app_argb_rr_evt(ARGB_RR_EVT_CHANGE, ((struct evt_rr_status*)h)->RR); return AF_TRAVERSE_NEXT; }

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
    hal_gpio_init(LED_POWER_EN_PIN);
    hal_gpio_set_output(LED_POWER_EN_PIN, HAL_GPIO_DATA_HIGH);
    LOG_INF("POWER_EN ON");

    for (int i=0;i<LED_COUNT;i++) e_off(&g_eff[i]);
    memset(argb_buf, 0, sizeof(argb_buf));

    bsp_argb_register_isr(argb_isr_cb, NULL);
    if (bsp_argb_enable()!=BSP_ARGB_STATUS_OK) { LOG_ERR("enable fail"); return -EIO; }

    g_running = true;
    k_thread_create(&rth, rstk, STK, refresh, NULL,NULL,NULL, PRI,0,K_NO_WAIT);
    LOG_INF("ARGB LED system ready");
    return 0;
}

int app_argb_demo_stop(void)
{
    g_running = false;
    k_sleep(K_MSEC(REFRESH_MS+50));
    for (int i=0;i<LED_COUNT;i++) e_off(&g_eff[i]);
    memset(argb_buf, 0, sizeof(argb_buf));
    argb_send_frame();
    hal_gpio_set_output(LED_POWER_EN_PIN, HAL_GPIO_DATA_LOW);
    bsp_argb_disable();
    LOG_INF("ARGB stopped");
    return 0;
}

#endif
