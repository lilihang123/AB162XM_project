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
 * @brief   ARGB LED framework for Keychron LM7.
 *
 * Architecture:
 *   ┌─ argb_refresh_thread() ──────────────────────────┐
 *   │  固定间隔 (REFRESH_MS) 调用各灯效函数获取颜色      │
 *   │  组装 GRB 帧 → argb_send_frame() → k_sleep()     │
 *   └──────────────────────────────────────────────────┘
 *          ↑                  ↑                  ↑
 *   led_effect_0()     led_effect_1()     led_effect_2()
 *
 * 改灯效只需改对应的 led_effect_N()，不想呼吸就返回固定颜色。
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

#define thisMODULE app_argb_test
#define thisMOD    "app_argb"
LOG_MODULE_REGISTER(thisMODULE);

/* ── Hardware config ─────────────────────────────────────────────────────── */

#define LED_COUNT           3
#define LED_POWER_EN_PIN    39
#define REFRESH_MS          20      /* Frame refresh interval */

/* Each LED occupies 4 bytes in the DMA buffer: {G, R, B, 0x00} */
#define ARGB_SLOT_SIZE      4
#define ARGB_PAD_BYTES      4       /* guard bytes before first LED data */
#define ARGB_BUF_SIZE       (ARGB_PAD_BYTES + LED_COUNT * ARGB_SLOT_SIZE)

/* ── Color type ──────────────────────────────────────────────────────────── */

typedef struct { uint8_t r, g, b; } argb_color_t;

/** Write one LED's GRB data into buffer, 4-byte aligned per LED.
 *  LED data starts at offset ARGB_PAD_BYTES to absorb any DMA startup skew. */
static inline void argb_write_grb(uint8_t *buf, uint8_t idx, argb_color_t c)
{
    uint8_t off = ARGB_PAD_BYTES + idx * ARGB_SLOT_SIZE;
    buf[off + 0] = c.g;
    buf[off + 1] = c.r;
    buf[off + 2] = c.b;
    buf[off + 3] = 0;
}

/* ══════════════════════════════════════════════════════════════════════════ */
/*  LED effect functions — 改灯效只改这里！                                   */
/*  每个函数接收 tick（帧计数，每 REFRESH_MS 加 1），返回该灯当前颜色         */
/* ══════════════════════════════════════════════════════════════════════════ */

static uint32_t g_tick;

/** LED 0: Red breathing (~2s period) */
static argb_color_t led_effect_0(uint32_t tick)
{
    // uint32_t phase = tick % 100;                    /* 100 ticks = 2s */
    // uint8_t  b;

    // if (phase < 50) {
    //     b = (uint8_t)(phase * 255 / 50);            /*  0 → 255 */
    // } else {
    //     b = (uint8_t)((100 - phase) * 255 / 50);    /* 255 → 0  */
    // }
    // return (argb_color_t){ .r = b, .g = b, .b = b };
    return (argb_color_t){ .r = 255, .g = 255, .b = 255 };
    
}

/** LED 1: Green constant on */
static argb_color_t led_effect_1(uint32_t tick)
{
    (void)tick;
    return (argb_color_t){ .r = 255, .g = 255, .b = 255 };
}

/** LED 2: Blue constant on */
static argb_color_t led_effect_2(uint32_t tick)
{
    (void)tick;
    return (argb_color_t){ .r = 255, .g = 255, .b = 255 };
}

/* ══════════════════════════════════════════════════════════════════════════ */
/*  Hardware layer — 不需要修改                                               */
/* ══════════════════════════════════════════════════════════════════════════ */

static uint8_t       argb_buf[ARGB_BUF_SIZE];   /* {G,R,B,0} per LED */
static bool          g_running;
static K_SEM_DEFINE(argb_frame_done, 0, 1);

static void argb_isr_cb(void *user_data)
{
    k_sem_give(&argb_frame_done);
}

static int argb_send_frame(void)
{
    argb_style_config_t cfg = {
        .type = argb_occupy_normal, .argb_num = LED_COUNT,
        .pattern = 0, .repeat = 1,
        /* Skip the 4-byte guard padding before first LED */
        .argb_data = argb_buf + ARGB_PAD_BYTES,
    };
    int ret = bsp_argb_realtime_config(&cfg);
    if (ret) return ret;
    if (k_sem_take(&argb_frame_done, K_MSEC(10))) {
        LOG_WRN("frame timeout");
        return -ETIMEDOUT;
    }
    return 0;
}

/* ══════════════════════════════════════════════════════════════════════════ */
/*  Refresh thread — 统一调度，不需要修改                                     */
/* ══════════════════════════════════════════════════════════════════════════ */

#define STACK_SIZE  1024
#define PRIORITY    7

static K_THREAD_STACK_DEFINE(refresh_stack, STACK_SIZE);
static struct k_thread     refresh_thread;

static void argb_refresh_thread(void *p1, void *p2, void *p3)
{
    LOG_INF("ARGB refresh started");

    while (g_running) {
        argb_write_grb(argb_buf, 0, led_effect_0(g_tick));
        argb_write_grb(argb_buf, 1, led_effect_1(g_tick));
        argb_write_grb(argb_buf, 2, led_effect_2(g_tick));

        if (argb_send_frame()) {
            LOG_ERR("send failed");
        }
        g_tick++;
        k_sleep(K_MSEC(REFRESH_MS));
    }
    LOG_INF("ARGB refresh stopped");
}

/* ── ADC test thread ─────────────────────────────────────────────────────── */
#define ADC_TEST_EN         0       /* Set to 1 to enable ADC test */

#if ADC_TEST_EN

static void ADC_EN_GPIO_init(void)
{
    hal_pinmux_set_function(HAL_GPIO_44, GPIO_AUX_MODE0);
    hal_gpio_init(HAL_GPIO_44);
    hal_gpio_set_direction(HAL_GPIO_44, HAL_GPIO_DIRECTION_OUTPUT);
    hal_gpio_set_output(HAL_GPIO_44, HAL_GPIO_DATA_HIGH);
    LOG_INF("GPIO44 (ADC_CTRL) initialized HIGH");
}


#define ADC_TEST_PIN      HAL_GPIO_25
#define ADC_TEST_CH       HAL_AIOADC_CH_0
#define ADC_TEST_MODE     HAL_AIOADC_MODE_SE_0
#define ADC_POLL_MS       500

static K_THREAD_STACK_DEFINE(adc_test_stack, 1024);
static struct k_thread     adc_test_thread_data;
static bool                g_adc_test_running;

static void adc_test_thread(void *p1, void *p2, void *p3)
{
    LOG_INF("ADC test started on GPIO%d, ch=%d", ADC_TEST_PIN, ADC_TEST_CH);

    /* Set GPIO25 to analog ADC mode (AUXADC0) */
    hal_pinmux_set_function(ADC_TEST_PIN, GPIO_AUX_MODE11);

    while (g_adc_test_running) {
        hal_aioadc_status_t ret;
        int16_t adc_mv;

        ret = hal_aioadc_init(ADC_TEST_CH, ADC_TEST_MODE, NULL);
        if (ret != HAL_AIOADC_STATUS_OK) {
            LOG_ERR("ADC init failed: %d", ret);
            k_sleep(K_MSEC(ADC_POLL_MS));
            continue;
        }

        /* Let the ADC settle before reading */
        k_sleep(K_MSEC(1));

        adc_mv = hal_aioadc_get_voltage(ADC_TEST_CH, ADC_TEST_MODE);

        hal_aioadc_deinit();

        printk("[ADC_TEST] GPIO25 = %d mV\n", adc_mv);
        LOG_INF("ADC GPIO25: %d mV", adc_mv);

        k_sleep(K_MSEC(ADC_POLL_MS));
    }

    LOG_INF("ADC test stopped");
}
#endif
/* ── Public API ──────────────────────────────────────────────────────────── */

int app_argb_demo_start(void)
{

    hal_gpio_init(LED_POWER_EN_PIN);
    hal_gpio_set_output(LED_POWER_EN_PIN, HAL_GPIO_DATA_HIGH);
    LOG_INF("LED_POWER_EN ON");

    bsp_argb_register_isr(argb_isr_cb, NULL);
    if (bsp_argb_enable() != BSP_ARGB_STATUS_OK) {
        LOG_ERR("bsp_argb_enable failed");
        return -EIO;
    }

    g_running = true;
    g_tick = 0;
    k_thread_create(&refresh_thread, refresh_stack, STACK_SIZE,
                    argb_refresh_thread, NULL, NULL, NULL,
                    PRIORITY, 0, K_NO_WAIT);

    LOG_INF("ARGB running: LED0=red breath, LED1=green, LED2=blue");

    /* Start ADC test thread */
#if ADC_TEST_EN
    if(1) ADC_EN_GPIO_init();

    g_adc_test_running = true;
    k_thread_create(&adc_test_thread_data, adc_test_stack, 1024,
                    adc_test_thread, NULL, NULL, NULL,
                    PRIORITY, 0, K_NO_WAIT);
#endif
    return 0;
}

int app_argb_demo_stop(void)
{
    g_running = false;
    k_sleep(K_MSEC(REFRESH_MS + 50));

    memset(argb_buf, 0, sizeof(argb_buf));
    argb_send_frame();
    hal_gpio_set_output(LED_POWER_EN_PIN, HAL_GPIO_DATA_LOW);
    bsp_argb_disable();

    LOG_INF("ARGB stopped");
    return 0;
}
