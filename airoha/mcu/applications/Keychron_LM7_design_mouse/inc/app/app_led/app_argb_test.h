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
 */

#ifndef __APP_ARGB_TEST_H__
#define __APP_ARGB_TEST_H__

#ifdef __cplusplus
extern "C" {
#endif
#if 1

#include <stdint.h>

/* ── LED Index definitions ──────────────────────────────────────────────── */
#define ARGB_LED_IDX_STATUS     0   /**< 充电/对码/回连 状态灯 */
#define ARGB_LED_IDX_DPI        1   /**< DPI 指示灯 */
#define ARGB_LED_IDX_RR         2   /**< 回报率指示灯 */

/* ── LED Effect commands for Status LED ─────────────────────────────────── */
typedef enum {
    ARGB_EVT_CHARGING,              /**< 充电中 → 红灯常亮 */
    ARGB_EVT_CHARGED,               /**< 充满电 → 绿灯常亮 */
    ARGB_EVT_PAIRING_START,         /**< 2.4G 对码开始 → 绿灯慢闪 */
    ARGB_EVT_PAIRING_OK,            /**< 2.4G 对码成功 → 绿灯常亮3s */
    ARGB_EVT_PAIRING_TIMEOUT,       /**< 2.4G 对码超时 → 全灭(休眠) */
    ARGB_EVT_RECONNECT_START,       /**< 2.4G 回连开始 → 绿灯快闪 */
    ARGB_EVT_RECONNECT_OK,          /**< 2.4G 回连成功 → 绿灯常亮3s */
    ARGB_EVT_OFF,                   /**< 关闭所有灯 */
} argb_evt_status_t;

/* ── LED Effect commands for DPI LED ────────────────────────────────────── */
typedef enum {
    ARGB_DPI_EVT_NONE = 0,          /**< DPI 不变 */
    ARGB_DPI_EVT_CHANGE,            /**< DPI 切换 → 蓝灯闪烁指示档位 */
} argb_evt_dpi_t;

/* ── LED Effect commands for Report Rate LED ────────────────────────────── */
typedef enum {
    ARGB_RR_EVT_NONE = 0,           /**< RR 不变 */
    ARGB_RR_EVT_CHANGE,             /**< RR 切换 → 蓝灯闪烁指示档位 */
} argb_evt_rr_t;

/* ── Public API ──────────────────────────────────────────────────────────── */

/**
 * @brief Initialize ARGB LED effect system.
 * @return 0 on success, negative error code on failure.
 */
int app_argb_init(void);

/**
 * @brief Stop ARGB LED effects and turn off all LEDs.
 * @return 0 on success, negative error code on failure.
 */
int app_argb_demo_stop(void);

/**
 * @brief Trigger a status LED effect (charging/pairing/reconnection).
 * @param evt  The status event to trigger.
 */
void app_argb_status_evt(argb_evt_status_t evt);

/**
 * @brief Trigger a DPI LED indication.
 * @param evt     The DPI event.
 * @param dpi_idx DPI level index (0-4).
 */
void app_argb_dpi_evt(argb_evt_dpi_t evt, uint8_t dpi_idx);

/**
 * @brief Trigger a Report Rate LED indication.
 * @param evt    The RR event.
 * @param rr_hz  Report rate in Hz (e.g., 125, 250, 500, 1000).
 */
void app_argb_rr_evt(argb_evt_rr_t evt, uint16_t rr_hz);

/**
 * @brief Wake up from sleep (used after pairing timeout).
 */
void app_argb_wakeup(void);

#endif

#ifdef __cplusplus
}
#endif

#endif /* __APP_ARGB_TEST_H__ */
