






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

#if defined(AIR_LOGGING_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <zephyr/logging/log_backend.h>
#include <zephyr/logging/log_core.h>
#include <zephyr/logging/log_output.h>
#include <zephyr/logging/log_output_dict.h>
#include <zephyr/logging/log_backend_std.h>
#include <zephyr/logging/log.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/sys/util_macro.h>
#include <zephyr/sys/__assert.h>
#include "assert.h"
#include "syslog_portable.h"
#include <stdint.h>
#include "memory_attribute.h"
#if IS_ENABLED(CONFIG_AIR_DAEMON_WORKQUEUE_ENABLE)
#include "air_daemon_work_q.h"
#endif


#ifdef CONFIG_SOC_SERIES_AB162X
struct uart_pin_config
{
    uint32_t tx_pin;
    uint32_t rx_pin;
    uint32_t rts_pin;
    uint32_t cts_pin;
    bool rx_pull_up;
    bool cts_pull_up;
};

struct uart_airoha_cfg
{
    struct uart_config uart_config;
    uint8_t uart_port;
    struct uart_pin_config pin_cfg;
};


static const struct device *const g_syslog_uart_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_logging_port));




syslog_port_dts_config_t syslog_uart_setting;/**< Data bits, use @ref uart_config_data_bits */


void syslog_port_update_the_syslog_parameter(void)
{
    syslog_uart_setting.uart_port = ((struct uart_airoha_cfg*)(g_syslog_uart_dev->config))->uart_port;/**< port number */
    syslog_uart_setting.baudrate = ((struct uart_airoha_cfg*)(g_syslog_uart_dev->config))->uart_config.baudrate;/**< Baudrate setting in bps */
    syslog_uart_setting.parity = ((struct uart_airoha_cfg*)(g_syslog_uart_dev->config))->uart_config.parity;  /**< Parity bit, use @ref uart_config_parity */
    syslog_uart_setting.stop_bits = ((struct uart_airoha_cfg*)(g_syslog_uart_dev->config))->uart_config.stop_bits; /**< Stop bits, use @ref uart_config_stop_bits */
    syslog_uart_setting.data_bits = ((struct uart_airoha_cfg*)(g_syslog_uart_dev->config))->uart_config.data_bits;/**< Data bits, use @ref uart_config_data_bits */
}

uint8_t syslog_port_get_uart_log(void)
{
   return ((struct uart_airoha_cfg*)(g_syslog_uart_dev->config))->uart_port; 
}

#if defined CONFIG_TRACING_USER
extern uint32_t sys_trace_query_thread_id(struct k_thread *thread);
#endif

uint32_t syslog_query_thread_id(struct k_thread *thread)
{
#if defined CONFIG_TRACING_USER
    return sys_trace_query_thread_id(thread);
#else
    return 0;
#endif
}

#define SYSLOG_INIT_NONE   0x00
extern syslog_share_variable_t *g_syslog_share_variable;
void syslog_global_turn_off(void)
{
    g_syslog_share_variable->init_phase = SYSLOG_INIT_NONE;
}

ATTR_TEXT_IN_TCM uint8_t query_syslog_init_phase_states(void)
{
    return g_syslog_share_variable->init_phase;
}

#ifdef AIR_SYSLOG_BUFFER_EXPAND_ENABLE
    #define AIR_SYSLOG_TX_BUFFER_SIZE       (16 * 1024)
#elif defined(AIR_SYSLOG_BUFFER_SLIM_ENABLE)
    #define AIR_SYSLOG_TX_BUFFER_SIZE       (4 * 1024)
#else
    #define AIR_SYSLOG_TX_BUFFER_SIZE       (8 * 1024)
#endif

#define AIR_SYSLOG_RX_BUFFER_SIZE           (1024)

#ifdef AIR_OFFLINE_DUMP_ENABLE
ATTR_ALIGN(4) volatile uint8_t SYSLOG_TX_BUFFER[AIR_SYSLOG_TX_BUFFER_SIZE];
ATTR_ALIGN(4) volatile uint8_t SYSLOG_RX_BUFFER[AIR_SYSLOG_RX_BUFFER_SIZE];
#else
ATTR_ZIDATA_IN_TCM_NONE_RETENTION ATTR_ALIGN(4) volatile uint8_t SYSLOG_TX_BUFFER[AIR_SYSLOG_TX_BUFFER_SIZE];
ATTR_ZIDATA_IN_TCM_NONE_RETENTION ATTR_ALIGN(4) volatile uint8_t SYSLOG_RX_BUFFER[AIR_SYSLOG_RX_BUFFER_SIZE];
#endif


uint32_t syslog_port_query_tx_buffer_size(void)
{
    return AIR_SYSLOG_TX_BUFFER_SIZE;
}

uint32_t syslog_port_query_rx_buffer_size(void)
{
    return AIR_SYSLOG_RX_BUFFER_SIZE;
}

#endif /*CONFIG_SOC_SERIES_AB162X*/

#ifndef CONFIG_MULTITHREADING
ATTR_WEAK_SYMBOL k_tid_t z_impl_k_sched_current_thread_query(void)
{
    k_tid_t ret = _current_cpu->current;
	return ret;
}
#endif

#if IS_ENABLED(CONFIG_AIR_DAEMON_WORKQUEUE_ENABLE)
extern void log_save_filter(struct k_work *work);
K_WORK_DEFINE(syslog_save_nvkey_work, log_save_filter);
#endif

void syslog_port_air_daemon_wq_work_submit(void)
{
#if IS_ENABLED(CONFIG_AIR_DAEMON_WORKQUEUE_ENABLE)
        /*send queue to daemon task to save*/
        air_daemon_wq_work_submit(&syslog_save_nvkey_work);
#endif
}

#endif /* AIR_LOGGING_ENABLE */
