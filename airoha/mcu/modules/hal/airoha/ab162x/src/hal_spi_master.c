/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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
#include "hal.h"
#include "hal_platform.h"

#ifdef HAL_SPI_MASTER_MODULE_ENABLED
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hal_sw_irq.h"
#include "hal_queue.h"
#include "hal_nvic.h"
#include "hal_nvic_internal.h"
#include "hal_clock.h"
#include "hal_cache.h"
#include "hal_cache_internal.h"
#include "hal_log.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_internal.h"
#include "hal_spi_master.h"
#include "hal_spi_master_internal.h"
#include "hal_memview.h"

/***********************************************************************************************
 * Preprocessor Definitions
***********************************************************************************************/
#define SPIM_POLLING_TIMEOUT_US     5000

/***********************************************************************************************
 * Private Variabable Declare
***********************************************************************************************/
static const IRQn_Type              g_spi_master_irq_code[HAL_SPI_MASTER_MAX] = SPIM_IRQ_CODE_ARRAY;
static const uint16_t               g_spi_master_pri_code[HAL_SPI_MASTER_MAX] = SPIM_IRQ_PRIO_ARRAY;
#ifdef HAL_CLOCK_MODULE_ENABLED
static const hal_clock_cg_id        g_spi_master_cg_code[HAL_SPI_MASTER_MAX] = SPIM_CG_ARRAY;
static const hal_clock_cg_id        g_spi_master_bus_cg_code[HAL_SPI_MASTER_MAX] = SPIM_BUS_CG_ARRAY;
static const clock_mux_sel_id       g_spi_master_ck_mux_sel[HAL_SPI_MASTER_MAX] = SPIM_CLK_MUX_ARRAY;
#endif
static hal_spi_master_callback_t    g_spi_master_callback[HAL_SPI_MASTER_MAX] = {NULL};
static void                        *g_spi_master_user_data[HAL_SPI_MASTER_MAX] = {NULL};

#if defined(HAL_SPI_MASTER_FEATURE_NO_BUSY) && defined (HAL_SPI_MASTER_FEATURE_DMA_MODE)
static spi_master_transfer_queue_t  g_spi_master_buff;
#endif
static hal_spi_master_private_t     g_spi_master_private[HAL_SPI_MASTER_MAX] = {0};
static uint8_t                      g_spi_master_bt_enable[HAL_SPI_MASTER_MAX] = {0};

/***********************************************************************************************
 * Function Declare
***********************************************************************************************/
hal_clock_status_t clock_mux_sel(clock_mux_sel_id mux_id, uint32_t mux_sel);
void spi_master_none_block_irq_handle(hal_spi_master_callback_event_t event, void *user_data);
static hal_spi_master_status_t spi_master_config_dma(hal_spi_master_port_t master_port,
                                                     hal_spi_master_send_and_receive_config_t *transfer_config);
static void spi_master_isr(hal_nvic_irq_t irq_number);
static hal_spi_master_status_t spi_master_init(hal_spi_master_port_t master_port,
                                               hal_spi_master_config_t *spi_config);
int spi_master_deinit(hal_spi_master_port_t master_port);
int spi_master_wait_hw_idle(hal_spi_master_port_t master_port, uint32_t timeout_us);
#if defined(HAL_SPI_MASTER_FEATURE_NO_BUSY) && defined (HAL_SPI_MASTER_FEATURE_DMA_MODE)
hal_spi_master_status_t spi_master_start_none_blocking_tansfer(hal_spi_master_port_t master_port);
void spi_master_none_block_irq_handle(hal_spi_master_callback_event_t event, void *user_data);
void spi_master_sw_irq_handle(void *userdata);
#endif
#ifdef HAL_SLEEP_MANAGER_ENABLED
sleep_management_lock_request_t          g_spi_master_sleep_handle[HAL_SPI_MASTER_MAX] = SPIM_SLP_HANDLE_ARRAY;
sleep_management_backup_restore_module_t g_spi_master_sleep_backup_restore_handle[HAL_SPI_MASTER_MAX] = {0xFF, 0xFF, INFRA_PD_BACKUP_RESTORE_SPIMST_2};
#endif

/***********************************************************************************************
* Public Function Declarations
*
***********************************************************************************************/
hal_spi_master_status_t hal_spi_master_init(hal_spi_master_port_t master_port,
                                            hal_spi_master_config_t *spi_config)
{
    hal_spi_master_private_t *pinfo = &g_spi_master_private[master_port];

    if (master_port >= HAL_SPI_MASTER_MAX) {
        return HAL_SPI_MASTER_STATUS_ERROR_PORT;
    }
    if (spi_config == NULL) {
        return HAL_SPI_MASTER_STATUS_INVALID_PARAMETER;
    }
    if (pinfo->op_state & SPI_MASTER_STATE_USER_MODE_NON_BLOCK) {
        return HAL_SPI_STATUS_BUSY_BY_NON_BLOCKING_FUNCTION;
    }
    pinfo->op_state = SPI_MASTER_STATE_USER_MODE_NORMAL;
#ifdef HAL_SLEEP_MANAGER_ENABLED
    if (master_port <= HAL_SPI_MASTER_1) {
        ao_backup_format_table_t spi_back_info;
        spi_master_ao_get_backup_info(master_port, &spi_back_info);
        sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_SPI_MST0 + master_port, &spi_back_info);
    } else {
        sleep_management_register_infra_pd_suspend_callback(g_spi_master_sleep_backup_restore_handle[master_port], (sleep_management_suspend_callback_t)spi_master_backup_register_callback, NULL);
        sleep_management_register_infra_pd_resume_callback(g_spi_master_sleep_backup_restore_handle[master_port], (sleep_management_resume_callback_t)spi_master_restore_register_callback, NULL);
    }
#endif
    return spi_master_init(master_port, spi_config);
}

hal_spi_master_status_t hal_spi_master_deinit(hal_spi_master_port_t master_port)
{
    hal_clock_status_t clk_status = 0;
    hal_spi_master_private_t *pinfo = &g_spi_master_private[master_port];

    if (master_port >= HAL_SPI_MASTER_MAX) {
        return HAL_SPI_MASTER_STATUS_ERROR_PORT;
    }
    /* disable clock */
    clk_status = spi_master_deinit(master_port);
    pinfo->op_state = 0;
    if (HAL_CLOCK_STATUS_OK != clk_status) {
        return HAL_SPI_MASTER_STATUS_ERROR;
    }
    return HAL_SPI_MASTER_STATUS_OK;
}

hal_spi_master_status_t hal_spi_master_send_and_receive_polling(hal_spi_master_port_t master_port,
                                                                hal_spi_master_send_and_receive_config_t *transfer_config)
{
    if (master_port >= HAL_SPI_MASTER_MAX) {
        return HAL_SPI_MASTER_STATUS_ERROR_PORT;
    }
    if (g_spi_master_bt_enable[master_port]) {
        return HAL_SPI_STATUS_BT_TRIGGER_BUSY;
    }
    if (transfer_config == NULL || transfer_config->receive_length > SPI_MASTER_FIFO_DEPTH || transfer_config->send_length > SPI_MASTER_FIFO_DEPTH ||
        (transfer_config->receive_length == 0 && transfer_config->send_length == 0)) {
        return HAL_SPI_MASTER_STATUS_INVALID_PARAMETER;
    }
    if (spi_master_wait_hw_idle(master_port, SPIM_POLLING_TIMEOUT_US) != HAL_SPI_MASTER_STATUS_OK) {
        return HAL_SPI_MASTER_STATUS_ERROR_BUSY;
    }
    spi_master_config_transfer(master_port, transfer_config, SPI_MASTER_MODE_FIFO);
    spi_master_ioctl(master_port, SPIM_SET_IE, false);
    spi_master_start_transfer(master_port, SPI_MASTER_MODE_FIFO, true);
    while (spi_master_ioctl(master_port, SPIM_GET_BUSY_STATUS, 0));
    spi_master_config_fifo(master_port, SPI_MASTER_RX, transfer_config->receive_buffer, transfer_config->receive_length);
    spi_master_ioctl(master_port, SPIM_GET_INT_STATUS, 0);
    return HAL_SPI_MASTER_STATUS_OK;
}


hal_spi_master_status_t hal_spi_master_send_polling(hal_spi_master_port_t master_port,
                                                    uint8_t *data,
                                                    uint32_t size)
{
    hal_spi_master_send_and_receive_config_t transfer_config;

    transfer_config.receive_length = 0;
    transfer_config.receive_buffer = NULL;
    transfer_config.send_data = data;
    transfer_config.send_length = size;
    return hal_spi_master_send_and_receive_polling(master_port, &transfer_config);
}



hal_spi_master_status_t hal_spi_master_register_callback(hal_spi_master_port_t master_port,
                                                         hal_spi_master_callback_t callback,
                                                         void *user_data)
{
    hal_spi_master_private_t *pinfo = &g_spi_master_private[master_port];

    if (master_port >= HAL_SPI_MASTER_MAX) {
        return HAL_SPI_MASTER_STATUS_ERROR_PORT;
    }
    if (NULL == callback) {
        return HAL_SPI_MASTER_STATUS_INVALID_PARAMETER;
    }

    g_spi_master_callback[master_port] = callback;
    /* user_data can be as NULL */
    g_spi_master_user_data[master_port] = user_data;
    /* register NVIC */
    hal_nvic_register_isr_handler(g_spi_master_irq_code[master_port], spi_master_isr);
    hal_nvic_set_priority(g_spi_master_irq_code[master_port], g_spi_master_pri_code[master_port]);
    hal_nvic_enable_irq(g_spi_master_irq_code[master_port]);
    pinfo->op_state |= SPI_MASTER_STATE_IRQ_MODE_MASK;
    return HAL_SPI_MASTER_STATUS_OK;
}

hal_spi_master_status_t hal_spi_master_send_and_receive_dma(hal_spi_master_port_t master_port,
                                                            hal_spi_master_send_and_receive_config_t *transfer_config)
{
    hal_spi_master_status_t     status;

    if (g_spi_master_bt_enable[master_port]) {
        return HAL_SPI_STATUS_BT_TRIGGER_BUSY;
    }
    /* reduce the api latency by checking the transfer config */
    status = spi_master_check_tranfer_config(master_port, transfer_config);
    if (status != HAL_SPI_MASTER_STATUS_OK) {
        status = spi_master_config_dma(master_port, transfer_config);
        if (status != HAL_SPI_MASTER_STATUS_OK) {
            return status;
        }
        spi_master_ioctl(master_port, SPIM_SET_IE, true);
    }
    spi_master_start_transfer(master_port, SPI_MASTER_MODE_DMA, true);
#ifdef HAL_SLEEP_MANAGER_ENABLED
    if( g_spi_master_callback[master_port] != NULL) {
        hal_sleep_manager_lock_sleep(g_spi_master_sleep_handle[master_port]);
    }
#endif
    return HAL_SPI_MASTER_STATUS_OK;
}


hal_spi_master_status_t hal_spi_master_send_dma(hal_spi_master_port_t master_port,
                                                uint8_t *data,
                                                uint32_t size)
{
    hal_spi_master_send_and_receive_config_t transfer_config;

    transfer_config.receive_length = 0;
    transfer_config.receive_buffer = NULL;
    transfer_config.send_data = data;
    transfer_config.send_length = size;
    return hal_spi_master_send_and_receive_dma(master_port, &transfer_config);
}

hal_spi_master_status_t hal_spi_master_send_and_receive_dma_blocking(hal_spi_master_port_t master_port,
                                                                     hal_spi_master_send_and_receive_config_t *transfer_config)
{
    hal_spi_master_status_t status;

    status = spi_master_config_dma(master_port, transfer_config);
    if (status != HAL_SPI_MASTER_STATUS_OK) {
        return status;
    }
    spi_master_ioctl(master_port, SPIM_SET_IE, false);
    spi_master_start_transfer(master_port, SPI_MASTER_MODE_DMA, true);
    while (spi_master_ioctl(master_port, SPIM_GET_BUSY_STATUS, 0));
    spi_master_ioctl(master_port, SPIM_GET_INT_STATUS, 0);
    return HAL_SPI_MASTER_STATUS_OK;
}

hal_spi_master_status_t hal_spi_master_send_dma_blocking(hal_spi_master_port_t master_port,
                                                         uint8_t *data,
                                                         uint32_t size)
{
    hal_spi_master_send_and_receive_config_t transfer_config;

    transfer_config.receive_length = 0;
    transfer_config.receive_buffer = NULL;
    transfer_config.send_data = data;
    transfer_config.send_length = size;
    return hal_spi_master_send_and_receive_dma_blocking(master_port, &transfer_config);
}


#if defined(HAL_SPI_MASTER_FEATURE_NO_BUSY) && defined (HAL_SPI_MASTER_FEATURE_DMA_MODE)
hal_spi_master_status_t hal_spi_master_send_and_receive_dma_no_busy(hal_spi_master_port_t master_port,
                                                                    hal_spi_send_and_receive_config_ex_no_busy_t *transfer_config)
{
    static bool initlized = false;
    hal_spi_master_private_t    *priv_data = &g_spi_master_private[master_port];
    uint32_t save_mask;
    spi_master_transfer_queue_t *p_spim_buff = &g_spi_master_buff;

    if (master_port >= HAL_SPI_MASTER_MAX) {
        return HAL_SPI_MASTER_STATUS_ERROR_PORT;
    }
    if (g_spi_master_bt_enable[master_port]) {
        return HAL_SPI_STATUS_BT_TRIGGER_BUSY;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    if (initlized == false) {
        memset(g_spi_master_private, 0, sizeof(g_spi_master_private));
        memset(&g_spi_master_buff, 0, sizeof(g_spi_master_buff));
        initlized = true;
    }

    if (priv_data->op_state & SPI_MASTER_STATE_USER_MODE_NORMAL) {
        hal_nvic_restore_interrupt_mask(save_mask); /* enable irq */
        return HAL_SPI_STATUS_ERROR_USED_BY_NORMAL_USER;
    }
    priv_data->op_state |= SPI_MASTER_STATE_USER_MODE_NON_BLOCK;
    if (p_spim_buff->index >= MAX_SPI_MASTER_QUEUE_LEN) {
        p_spim_buff->index = 0;
    }

    if (p_spim_buff->used_flag[p_spim_buff->index]) {
        hal_nvic_restore_interrupt_mask(save_mask); /* enable irq */
        return HAL_SPI_STATUS_FULL_BY_NON_BLOCKING_FUNCTION;
    }
    p_spim_buff->tranfer_cfg[p_spim_buff->index] = *transfer_config;
    p_spim_buff->used_flag[p_spim_buff->index] = true;
    hal_queue_push(&priv_data->queue, p_spim_buff->index);
    p_spim_buff->index++;

    if ((priv_data->op_state & SPI_MASTER_STATE_IS_WORKING) == 0) {
        /* For solve the disable irq too long issue, then use the sw GPT to do spi hardware config */
        priv_data->op_state |= SPI_MASTER_STATE_IS_WORKING;
    }
    hal_nvic_restore_interrupt_mask(save_mask);
    hal_sw_irq_trigger(HAL_SW_IRQ_0, spi_master_sw_irq_handle, (void *)master_port);

    return HAL_SPI_MASTER_STATUS_OK;
}
#endif


#ifdef HAL_SPI_MASTER_FEATURE_ADVANCED_CONFIG
hal_spi_master_status_t hal_spi_master_set_advanced_config(hal_spi_master_port_t master_port,
                                                           hal_spi_master_advanced_config_t *advanced_config)
{
    if (advanced_config == NULL) {
        return HAL_SPI_MASTER_STATUS_INVALID_PARAMETER;
    }
    spi_master_set_advanced_config(master_port, advanced_config);
    return HAL_SPI_MASTER_STATUS_OK;
}
#endif

hal_spi_master_status_t hal_spi_master_get_running_status(hal_spi_master_port_t master_port,
                                                          hal_spi_master_running_status_t *running_status)
{
    uint32_t ret = 0;

    if (master_port >= HAL_SPI_MASTER_MAX) {
        return HAL_SPI_MASTER_STATUS_ERROR_PORT;
    }
    if (running_status == NULL) {
        return HAL_SPI_MASTER_STATUS_INVALID_PARAMETER;
    }
    ret = spi_master_ioctl(master_port, SPIM_GET_BUSY_STATUS, 0);
    *running_status = (ret ? HAL_SPI_MASTER_BUSY : HAL_SPI_MASTER_IDLE);
    return HAL_SPI_MASTER_STATUS_OK;
}

hal_spi_master_status_t hal_spi_master_set_chip_select(hal_spi_master_port_t master_port, hal_spi_master_slave_port_t slv_port)
{
    if (master_port >= HAL_SPI_MASTER_MAX) {
        return HAL_SPI_MASTER_STATUS_ERROR_PORT;
    }
    if (slv_port > HAL_SPI_MASTER_SLAVE_MAX) {
        return HAL_SPI_MASTER_STATUS_INVALID_PARAMETER;
    }
    spi_master_ioctl(master_port, SPIM_SET_CHIP_SEL, slv_port);
    return HAL_SPI_MASTER_STATUS_OK;
}

hal_spi_master_status_t hal_spi_master_set_chip_select_timing(hal_spi_master_port_t master_port,
                                                              hal_spi_master_chip_select_timing_t chip_select_timing)
{
    if (master_port >= HAL_SPI_MASTER_MAX) {
        return HAL_SPI_MASTER_STATUS_ERROR_PORT;
    }
    spi_master_set_cs_timing(master_port, &chip_select_timing);
    return HAL_SPI_MASTER_STATUS_ERROR;
}

hal_spi_master_status_t hal_spi_master_set_deassert(hal_spi_master_port_t master_port,
                                                    hal_spi_master_deassert_t deassert)
{
    if (master_port >= HAL_SPI_MASTER_MAX) {
        return HAL_SPI_MASTER_STATUS_ERROR_PORT;
    }
    spi_master_ioctl(master_port, SPIM_SET_DEASSERT, (deassert == HAL_SPI_MASTER_DEASSERT_ENABLE) ? 1 : 0);
    return HAL_SPI_MASTER_STATUS_OK;
}

hal_spi_master_status_t hal_spi_master_set_mode(hal_spi_master_port_t master_port,
                                                hal_spi_master_mode_t mode)
{
    if (master_port >= HAL_SPI_MASTER_MAX) {
        return HAL_SPI_MASTER_STATUS_ERROR_PORT;
    }
    spi_master_ioctl(master_port, SPIM_SET_TRANS_MODE, mode);
    return HAL_SPI_MASTER_STATUS_OK;
}

hal_spi_master_status_t hal_spi_master_set_dummy_bits(hal_spi_master_port_t master_port,
                                                      uint8_t dummy_bits)
{
    if (master_port >= HAL_SPI_MASTER_MAX) {
        return HAL_SPI_MASTER_STATUS_ERROR_PORT;
    }
    spi_master_ioctl(master_port, SPIM_SET_DUMMY_CNT, dummy_bits);
    return HAL_SPI_MASTER_STATUS_OK;
}

hal_spi_master_status_t hal_spi_master_set_command_bytes(hal_spi_master_port_t master_port,
                                                         uint8_t command_bytes)
{
    if (master_port >= HAL_SPI_MASTER_MAX) {
        return HAL_SPI_MASTER_STATUS_ERROR_PORT;
    }
    spi_master_ioctl(master_port, SPIM_SET_CMD_CNT, command_bytes);
    return HAL_SPI_MASTER_STATUS_OK;
}

hal_spi_master_status_t hal_spi_master_set_clear_data(hal_spi_master_port_t master_port, uint8_t cmd_cnt, bool is_high, bool enable)
{
    hal_spi_master_status_t ret;

    if (master_port >= HAL_SPI_MASTER_MAX) {
        return HAL_SPI_MASTER_STATUS_ERROR_PORT;
    }
    ret = spi_master_set_clear_data(master_port, cmd_cnt, is_high, enable);
    return ret;
}

hal_spi_master_status_t hal_spi_master_set_delay_cnt(hal_spi_master_port_t master_port, uint16_t delay_cnt, uint8_t one_location_cnt, bool is_multy)
{
    if (master_port >= HAL_SPI_MASTER_MAX) {
        return HAL_SPI_MASTER_STATUS_ERROR_PORT;
    }
    spi_master_set_delay_cnt(master_port, delay_cnt, one_location_cnt, is_multy);
    return HAL_SPI_MASTER_STATUS_OK;
}

hal_spi_master_status_t hal_spi_master_set_bt_enable(hal_spi_master_port_t master_port, bool bt_enable)
{
    uint32_t saved_mask;

    if (master_port >= HAL_SPI_MASTER_MAX) {
        return HAL_SPI_MASTER_STATUS_ERROR_PORT;
    }
    hal_nvic_save_and_set_interrupt_mask(&saved_mask);

    spi_master_ioctl(master_port, SPIM_SET_BT_EN, bt_enable);
    g_spi_master_bt_enable[master_port] = (uint8_t)bt_enable;

    hal_nvic_restore_interrupt_mask(saved_mask);
    return HAL_SPI_MASTER_STATUS_OK;
}

hal_spi_master_status_t hal_spi_master_trigger_start(hal_spi_master_port_t master_port, bool start)
{
    if (master_port >= HAL_SPI_MASTER_MAX) {
        return HAL_SPI_MASTER_STATUS_ERROR_PORT;
    }
    spi_master_start_transfer(master_port, SPI_MASTER_MODE_DMA, start);
    return HAL_SPI_MASTER_STATUS_OK;
}

hal_spi_master_status_t hal_spi_enable_nvic_irq(hal_spi_master_port_t master_port, bool enable)
{
    if (enable) {
        hal_nvic_enable_irq(g_spi_master_irq_code[master_port]);
    } else {
        hal_nvic_disable_irq(g_spi_master_irq_code[master_port]);
    }
    return HAL_SPI_MASTER_STATUS_OK;
}


hal_spi_master_status_t hal_spi_master_restore_address_advanced(hal_spi_master_port_t master_port, uint8_t *tx_address, uint8_t *rx_address)
{
    spi_master_set_rwaddr(master_port, SPI_MASTER_TX, tx_address);
    spi_master_set_rwaddr(master_port, SPI_MASTER_RX, rx_address);
    return HAL_SPI_MASTER_STATUS_OK;
}

hal_spi_master_status_t hal_spi_master_send_and_receive_dma_advanced(hal_spi_master_port_t master_port,
                                                                     hal_spi_master_send_and_receive_config_t *transfer_config, bool start)
{
    hal_spi_master_status_t     status;

    status = spi_master_config_dma(master_port, transfer_config);
    if (status != HAL_SPI_MASTER_STATUS_OK) {
        return status;
    }
    spi_master_ioctl(master_port, SPIM_SET_IE, true);
    spi_master_start_transfer(master_port, SPI_MASTER_MODE_DMA, start);
#ifdef HAL_SLEEP_MANAGER_ENABLED
    if( g_spi_master_callback[master_port] != NULL && start) {
        hal_sleep_manager_lock_sleep(g_spi_master_sleep_handle[master_port]);
    }
#endif
    return HAL_SPI_MASTER_STATUS_OK;
}

hal_spi_master_status_t hal_spi_master_send_and_receive_fifo_advanced(hal_spi_master_port_t master_port,
                                                                     hal_spi_master_send_and_receive_config_t *transfer_config, bool start)
{
    if (master_port >= HAL_SPI_MASTER_MAX) {
        return HAL_SPI_MASTER_STATUS_ERROR_PORT;
    }
    if (g_spi_master_bt_enable[master_port]) {
        return HAL_SPI_STATUS_BT_TRIGGER_BUSY;
    }
    if (transfer_config == NULL || transfer_config->receive_length > SPI_MASTER_FIFO_DEPTH || transfer_config->send_length > SPI_MASTER_FIFO_DEPTH ||
        (transfer_config->receive_length == 0 && transfer_config->send_length == 0)) {
        return HAL_SPI_MASTER_STATUS_INVALID_PARAMETER;
    }
    if (spi_master_wait_hw_idle(master_port, SPIM_POLLING_TIMEOUT_US) != HAL_SPI_MASTER_STATUS_OK) {
        return HAL_SPI_MASTER_STATUS_ERROR_BUSY;
    }
    spi_master_config_transfer(master_port, transfer_config, SPI_MASTER_MODE_FIFO);
    spi_master_ioctl(master_port, SPIM_SET_IE, true);
    spi_master_start_transfer(master_port, SPI_MASTER_MODE_FIFO, start);
#ifdef HAL_SLEEP_MANAGER_ENABLED
    if( g_spi_master_callback[master_port] != NULL && start) {
        hal_sleep_manager_lock_sleep(g_spi_master_sleep_handle[master_port]);
    }
#endif
    return HAL_SPI_MASTER_STATUS_OK;
}

hal_spi_master_status_t hal_spi_master_fifo_access(hal_spi_master_port_t master_port, bool write, uint8_t *data, uint32_t size)
{
    spi_master_direction_t direction = write ? SPI_MASTER_TX : SPI_MASTER_RX;
    if (master_port >= HAL_SPI_MASTER_MAX) {
        return HAL_SPI_MASTER_STATUS_ERROR_PORT;
    }
    if (data == NULL || size == 0 || size > SPI_MASTER_FIFO_DEPTH) {
        return HAL_SPI_MASTER_STATUS_INVALID_PARAMETER;
    }
    spi_master_config_fifo(master_port, direction, data, size);
    return HAL_SPI_MASTER_STATUS_OK;
}


hal_spi_master_status_t hal_spi_master_select_slave_port(hal_spi_master_port_t master_port, hal_spi_master_slave_port_t slave_port)
{
    if (master_port >= HAL_SPI_MASTER_MAX) {
        return HAL_SPI_MASTER_STATUS_ERROR_PORT;
    }
    if (slave_port >= HAL_SPI_MASTER_SLAVE_MAX) {
        return HAL_SPI_MASTER_STATUS_INVALID_PARAMETER;
    }
    spi_master_ioctl(master_port, SPIM_SET_CHIP_SEL, slave_port);
    return HAL_SPI_MASTER_STATUS_OK;
}


/***********************************************************************************************
 * Private Function Declarations
***********************************************************************************************/
static hal_spi_master_status_t spi_master_config_dma(hal_spi_master_port_t master_port,
                                                     hal_spi_master_send_and_receive_config_t *transfer_config)
{
    hal_spi_master_status_t status;

    if (master_port >= HAL_SPI_MASTER_MAX) {
        return HAL_SPI_MASTER_STATUS_ERROR_PORT;
    }
    if (g_spi_master_bt_enable[master_port]) {
        return HAL_SPI_STATUS_BT_TRIGGER_BUSY;
    }
    if (transfer_config == NULL) {
        return HAL_SPI_MASTER_STATUS_INVALID_PARAMETER;
    }
    if (spi_master_ioctl(master_port, SPIM_GET_BUSY_STATUS, 0)) {
        return HAL_SPI_MASTER_STATUS_ERROR_BUSY;
    }
    status = spi_master_config_transfer(master_port, transfer_config, SPI_MASTER_MODE_DMA);
    if (status != HAL_SPI_MASTER_STATUS_OK) {
        return status;
    }
    return HAL_SPI_MASTER_STATUS_OK;
}

static void spi_master_isr(hal_nvic_irq_t irq_number)
{
    uint32_t i;
    hal_spi_master_port_t spi_port = HAL_SPI_MASTER_0;

    for (i = 0; i < HAL_SPI_MASTER_MAX; i++) {
        if (g_spi_master_irq_code[i] == irq_number) {
            spi_port = (hal_spi_master_port_t)i;
            break;
        }
    }
    spi_master_isr_handler(spi_port, g_spi_master_callback[spi_port], g_spi_master_user_data[spi_port]);
#ifdef HAL_SLEEP_MANAGER_ENABLED
    hal_sleep_manager_unlock_sleep(g_spi_master_sleep_handle[spi_port]);
#endif
}

static hal_spi_master_status_t spi_master_init(hal_spi_master_port_t master_port,
                                               hal_spi_master_config_t *spi_config)
{
    hal_clock_status_t clk_status = 0;

#ifdef HAL_CLOCK_MODULE_ENABLED
    /* enable clock */
    uint8_t clk_sel = SPI_MASTER_CLOCK_SOURCE_32MHZ;
    if (master_port == HAL_SPI_MASTER_2) {
        clk_sel = SPI_MASTER_CLOCK_SOURCE_78MHZ;/* 78M clock source only for master2*/
    }
    clk_status |= hal_clock_enable(g_spi_master_cg_code[master_port]);
    clk_status |= hal_clock_enable(g_spi_master_bus_cg_code[master_port]);
    clk_status |= clock_mux_sel(g_spi_master_ck_mux_sel[master_port], clk_sel);
    if (HAL_CLOCK_STATUS_OK != clk_status) {
        return HAL_SPI_MASTER_STATUS_ERROR;
    }
#endif
    /* init spi mater hardware */
    spi_master_hw_reset(master_port);
    spi_master_init_config(master_port, spi_config, clk_sel);
    spi_master_ioctl(master_port, SPIM_SET_CHIP_SEL, spi_config->slave_port);
    return HAL_SPI_MASTER_STATUS_OK;
}


int spi_master_deinit(hal_spi_master_port_t master_port)
{
    hal_clock_status_t clk_status = 0;
#ifdef HAL_CLOCK_MODULE_ENABLED
    /* disable clock */
    clk_status = hal_clock_disable(g_spi_master_cg_code[master_port]);
    clk_status = hal_clock_disable(g_spi_master_bus_cg_code[master_port]);
#endif
    return clk_status;
}

int spi_master_wait_hw_idle(hal_spi_master_port_t master_port, uint32_t timeout_us)
{
    uint32_t  tick_sta, tick_cur, tick_dur;

    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &tick_sta);
    while (1) {
        if (HAL_SPI_MASTER_IDLE == spi_master_ioctl(master_port, SPIM_GET_BUSY_STATUS, 0)) {
            break;
        }
        hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &tick_cur);
        hal_gpt_get_duration_count(tick_sta, tick_cur, &tick_dur);
        if (tick_dur > timeout_us) {
            return HAL_SPI_MASTER_STATUS_ERROR_BUSY;
        }
    }
    return HAL_SPI_MASTER_STATUS_OK;
}

#if defined(HAL_SPI_MASTER_FEATURE_NO_BUSY) && defined (HAL_SPI_MASTER_FEATURE_DMA_MODE)
hal_spi_master_status_t spi_master_start_none_blocking_tansfer(hal_spi_master_port_t master_port)
{
    int rslt = 0, index = 0;
    hal_spi_send_and_receive_config_ex_no_busy_t *pconfig;
    hal_spi_master_private_t *priv_data =  &g_spi_master_private[master_port];
    hal_spi_master_status_t status;
    spi_master_transfer_queue_t *p_spim_buff = &g_spi_master_buff;

    rslt = hal_queue_top(&priv_data->queue, &index);
    if (rslt < 0) {
        return HAL_SPI_MASTER_STATUS_ERROR;
    }
    pconfig = &p_spim_buff->tranfer_cfg[index];
    spi_master_init(master_port, &pconfig->spi_config);
    hal_spi_master_set_chip_select_timing(master_port, pconfig->chip_select_timing);
    hal_spi_master_register_callback(master_port, spi_master_none_block_irq_handle, (void *) master_port);
    status = hal_spi_master_send_and_receive_dma(master_port, &pconfig->spi_send_and_receive_config_ex);
    if (status != HAL_SPI_MASTER_STATUS_OK) {
        /* if send/recv fail, should release the Queue */
        hal_queue_pop(&priv_data->queue, &index);
        p_spim_buff->used_flag[index] = false;

    }
    return status;
}

void spi_master_none_block_irq_handle(hal_spi_master_callback_event_t event, void *user_data)
{
    hal_spi_master_port_t master_port = (hal_spi_master_port_t) user_data;;
    hal_spi_master_private_t *priv_data = &g_spi_master_private[master_port];
    hal_spi_send_and_receive_config_ex_no_busy_t *pconfig;
    int rslt = 0, index = 0;
    spi_master_transfer_queue_t *p_spim_buff = &g_spi_master_buff;

    /* process current transfer: pop current index, and release it*/
    rslt = hal_queue_pop(&priv_data->queue, &index);
    if (rslt < 0) {
        spi_master_deinit(master_port);
#ifdef HAL_SLEEP_MANAGER_ENABLED
        hal_sleep_manager_unlock_sleep(g_spi_master_sleep_handle[master_port]);
#endif
        return;
    }
    pconfig = &p_spim_buff->tranfer_cfg[index];
    if (pconfig->spi_callback != NULL) {
        pconfig->spi_callback(event, pconfig->user_data);
    }
    p_spim_buff->used_flag[index] = false;

    /* process next transfer: if rslt < 0, means queue is empty and not user in wait list, so release the state */
    rslt = spi_master_start_none_blocking_tansfer(master_port);
    if (rslt < 0) {
        priv_data->op_state &= ~SPI_MASTER_STATE_IS_WORKING;
        priv_data->op_state &= ~SPI_MASTER_STATE_USER_MODE_NON_BLOCK;
        spi_master_deinit(master_port);
#ifdef HAL_SLEEP_MANAGER_ENABLED
        hal_sleep_manager_unlock_sleep(g_spi_master_sleep_handle[master_port]);
#endif
    }
}

void spi_master_sw_irq_handle(void *userdata)
{
    hal_spi_master_port_t master_port = (hal_spi_master_port_t)userdata;
    hal_spi_master_status_t status;
    hal_spi_master_private_t *priv_data = &g_spi_master_private[master_port];

    status = spi_master_start_none_blocking_tansfer(master_port);
    if (status != HAL_SPI_MASTER_STATUS_OK) {
        priv_data->op_state &= ~SPI_MASTER_STATE_IS_WORKING;
    }
}
#endif

#endif /* HAL_SPI_MASTER_MODULE_ENABLED */

