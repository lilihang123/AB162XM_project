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
#if defined(AIR_MUX_ENABLE)

#include "mux.h"
#include "mux_port.h"
#include "mux_port_device.h"
#include "hal_uart.h"
#include "hal_uart_internal.h"
#include "assert.h"


/**
 * This is UART none-block DMA MODE send data flow. (mask ENABLE_MUX_UART_POLLING_SEND)
    thread 1: user1 log -> log service -> mux_tx -> data copy to fifo -> phase2_send -> dma idle -> uart_dma -> return ...
    thread 2: user2 log -> log service -> mux_tx -> data copy to fifo -> phase2_send -> dma busy -> return ...
    thread 3: userx log -> log service -> mux_tx -> data copy to fifo -> phase2_send -> dma busy -> return ...
    ...
                                                                                                                ↓
                                                                                                        UART_DMA_TX_DONE IRQ -> fifo not empty -> restart dma -> return ...
                                                                                                                            ↓
                                                                                                                    UART_DMA_TX_DONE IRQ -> fifo empty -> return ...
    thread 4: user1 log -> log service -> mux_tx -> data copy to fifo -> phase2_send -> dma idle -> uart_dma -> return ...
    ...

 * This is UART block POLLING MODE send data flow. (enable ENABLE_MUX_UART_POLLING_SEND)
    thread 1: user1 log -> log service -> mux_tx -> phase2_send -> uart_dma -> loop tx done -> return ...
    thread 2: user2 log -> log service -> mux_tx -> phase2_send -> uart_dma -> loop tx done -> return ...
    thread x: userx log -> log service -> mux_tx -> phase2_send -> uart_dma -> loop tx done -> return ...
    ...
*/

#ifdef HAL_SLEEP_MANAGER_ENABLED
    // #define ENABLE_MUX_UART_POLLING_SEND
#endif

/******************************************************************************
 * MUX port macro redirect
 *****************************************************************************/
#define MUX_UART_NUM                                (HAL_UART_MAX)
#define UART_PORT_INDEX_TO_MUX_PORT(port_index)     (port_index + MUX_UART_0)

/******************************************************************************
 * MUX port Variables
 *****************************************************************************/
virtual_read_write_point_t g_mux_uart_r_w_point[MUX_UART_NUM];
static mux_irq_handler_t g_mux_irq_handler;

ATTR_TEXT_IN_TCM uint32_t port_mux_uart_get_hw_rptr(uint8_t port_index, bool is_rx)
{
    if (is_rx) {
        return uart_get_hw_rx_ptr(port_index, true);
    } else {
       return mux_common_device_get_hw_rptr((virtual_read_write_point_t *)&g_mux_uart_r_w_point[port_index], is_rx);
    }
}

ATTR_TEXT_IN_TCM uint32_t port_mux_uart_get_hw_wptr(uint8_t port_index, bool is_rx)
{
    if (is_rx) {
        return uart_get_hw_rx_ptr(port_index, false);
    } else {
        return mux_common_device_get_hw_wptr((virtual_read_write_point_t *)&g_mux_uart_r_w_point[port_index], is_rx);
    }
}

/**When Receive data, MUX will call this API to move Rx Ring buffer Read point.
    for MUX, firstly ,should copy data out. Then call this API to move Rx Ring buffer Read point. **/
void port_mux_uart_set_rx_hw_rptr(uint8_t port_index, uint32_t move_bytes)
{
    uart_set_rx_sw_move_byte(port_index, move_bytes, true);
}

/**When Send data, MUX will call this API to move Tx Ring buffer Write point.
    for MUX, firstly ,should copy data in. Then call this API to move Tx Ring buffer Write point. **/
/* TCM is mainly for Optimize log printing time */
ATTR_TEXT_IN_TCM void port_mux_uart_set_tx_hw_wptr(uint8_t port_index, uint32_t move_bytes)
{
    virtual_read_write_point_t *p = (virtual_read_write_point_t *)&g_mux_uart_r_w_point[port_index];

    mux_common_device_set_tx_hw_wptr(p, move_bytes);

    /* bypass current tx fifo data. */
    // mux_common_device_set_tx_hw_rptr_internal_use(p, move_bytes);
}

#ifdef CORE_MCU

void uart_send_buffer(uint8_t port_index, uint32_t addr, uint32_t len, volatile uint32_t *sending_point, bool block_send)
{
    if (block_send == true) {
        while (uart_send_dma_is_busy(port_index) == true);
    }

    *sending_point = addr + len;
    uart_send_dma_for_log(port_index, (uint8_t *)addr, len);

    if (block_send == true) {
        while (uart_send_dma_is_busy(port_index) == true);
    }
}

void uart_ready_to_write_user_callback(uint8_t port_index, void *user_data)
{
    virtual_read_write_point_t *p = (virtual_read_write_point_t *)&g_mux_uart_r_w_point[port_index];;
    uint32_t next_available_block_len, irq_mask;

    port_mux_cross_local_enter_critical(&irq_mask);
    if (p->tx_send_is_running != MUX_DEVICE_HW_RUNNING) {
        port_mux_cross_local_exit_critical(irq_mask);
        return;
    }

    //transfer done , then update tx_buff_read_point
    uint32_t move_size = p->tx_sending_read_point - p->tx_buff_read_point;
    mux_common_device_set_tx_hw_rptr_internal_use(p, move_size);

    next_available_block_len = mux_common_device_get_buf_next_available_block_len(p->tx_buff_start, p->tx_buff_read_point, p->tx_buff_write_point, p->tx_buff_end, p->tx_buff_available_len);
    if (next_available_block_len == 0) {
        p->tx_send_is_running = MUX_DEVICE_HW_IDLE; //change to idle
        port_mux_cross_local_exit_critical(irq_mask);
        return;
    } else {
        p->tx_send_is_running = MUX_DEVICE_HW_RUNNING; //keep running
        port_mux_cross_local_exit_critical(irq_mask);
        /* irq mode, none-block send */
        uart_send_buffer(port_index, p->tx_buff_read_point, next_available_block_len, &p->tx_sending_read_point, false);
        return;
    }
}

static void mux_uart_callback(hal_uart_callback_event_t event, void *user_data)
{
    uint32_t port_index = (uint32_t)user_data;

    if ((event == HAL_UART_EVENT_READY_TO_WRITE) || (event == HAL_UART_EVENT_TRANSMISSION_DONE)) {
        uart_ready_to_write_user_callback(UART_PORT_INDEX_TO_MUX_PORT(port_index), user_data);
    } else if (event == HAL_UART_EVENT_READY_TO_READ) {
        g_mux_irq_handler(UART_PORT_INDEX_TO_MUX_PORT(port_index), MUX_EVENT_READY_TO_READ, user_data);
    } else {
        /* not support */
    }
}

mux_status_t port_mux_uart_normal_init(uint8_t port_index, mux_port_config_t *p_setting, mux_irq_handler_t irq_handler)
{
    hal_uart_config_t uart_config;
    hal_uart_dma_config_t dma_config;

    g_mux_irq_handler = irq_handler;

    uart_config.baudrate     = p_setting->p_user_setting->dev_setting.uart.uart_config.baudrate;    //CONFIG_SYSLOG_BAUDRATE;
    uart_config.parity       = p_setting->p_user_setting->dev_setting.uart.uart_config.parity;      //HAL_UART_PARITY_NONE;
    uart_config.stop_bit     = p_setting->p_user_setting->dev_setting.uart.uart_config.stop_bit;    //HAL_UART_STOP_BIT_1;
    uart_config.word_length  = p_setting->p_user_setting->dev_setting.uart.uart_config.word_length; //HAL_UART_WORD_LENGTH_8;
    dma_config.receive_vfifo_buffer             = (uint8_t *)(uint32_t *)p_setting->rx_buf_addr;
    dma_config.receive_vfifo_buffer_size        = p_setting->rx_buf_size;
    dma_config.receive_vfifo_threshold_size     = dma_config.receive_vfifo_buffer_size / 2;
    dma_config.receive_vfifo_alert_size         = 12;

    hal_uart_deinit(port_index);
    mux_common_device_r_w_point_init((virtual_read_write_point_t *)&g_mux_uart_r_w_point[port_index], p_setting);

    if (HAL_UART_STATUS_OK != hal_uart_init(port_index, &uart_config)) {
        return MUX_STATUS_ERROR_INIT_FAIL;
    }

    if (HAL_UART_STATUS_OK != hal_uart_set_dma(port_index, &dma_config)) {
        return MUX_STATUS_ERROR_INIT_FAIL;
    }

    if (p_setting->p_user_setting->dev_setting.uart.flowcontrol_type == MUX_UART_NONE_FLOWCONTROL) {
        hal_uart_disable_flowcontrol(port_index);
    } else if (p_setting->p_user_setting->dev_setting.uart.flowcontrol_type == MUX_UART_SW_FLOWCONTROL) {
        hal_uart_set_software_flowcontrol(port_index, 0x11, 0x13, 0x77);
    } else if (p_setting->p_user_setting->dev_setting.uart.flowcontrol_type == MUX_UART_HW_FLOWCONTROL) {
        hal_uart_set_hardware_flowcontrol(port_index);
    } else {
        assert(0);
    }

    if (HAL_UART_STATUS_OK != hal_uart_register_callback(port_index, mux_uart_callback, (void *)(intptr_t)port_index)) {
        return MUX_STATUS_ERROR_INIT_FAIL;
    }

    /* port 0 must enable irq!!!
        only syslog use for debug, dma mode like pdma, so must rely on interrupt continue send data. */
#ifdef ENABLE_MUX_UART_POLLING_SEND
    uart_disable_tx_interrupt(port_index);
#else
    uart_enable_tx_interrupt(port_index);
#endif

    uart_enable_rx_interrupt(port_index);

    return MUX_STATUS_OK;
}

mux_status_t port_mux_uart_deinit(uint8_t port_index)
{
    if (HAL_UART_STATUS_OK != hal_uart_deinit(port_index)) {
        return MUX_STATUS_ERROR_DEINIT_FAIL;
    } else {
        return MUX_STATUS_OK;
    }
}

void port_mux_uart_exception_init(uint8_t port_index)
{
    hal_uart_config_t uart_config;

    hal_uart_deinit(port_index);
    extern uint32_t g_uart_baudrate;
    uart_config.baudrate = g_uart_baudrate;
    uart_config.parity = HAL_UART_PARITY_NONE;
    uart_config.stop_bit = HAL_UART_STOP_BIT_1;
    uart_config.word_length = HAL_UART_WORD_LENGTH_8;
    hal_uart_init(port_index, &uart_config);

#ifndef MTK_DEBUG_PLAIN_LOG_ENABLE
    hal_uart_set_software_flowcontrol(port_index, 0x11, 0x13, 0x77);
#endif
}

void port_mux_uart_exception_send(uint8_t port_index, uint8_t *buffer, uint32_t size)
{
    uart_exception_send_polling(port_index, buffer, size);
}

/* TCM is mainly for Optimize log printing time */
bool port_mux_uart_buf_is_full(uint8_t port_index, bool is_rx)
{
    virtual_read_write_point_t *p = (virtual_read_write_point_t *)&g_mux_uart_r_w_point[port_index];

    return mux_common_device_buf_is_full(p, is_rx);
}

#endif /* CORE_MCU */


/* TCM is mainly for Optimize log printing time */
mux_status_t port_mux_uart_phase1_send(uint8_t port_index)
{
    (void) port_index;
    return MUX_STATUS_OK;
}

/* TCM is mainly for Optimize log printing time, follow mux_usb */
ATTR_TEXT_IN_TCM mux_status_t port_mux_uart_phase2_send(uint8_t port_index)
{
    virtual_read_write_point_t *p = (virtual_read_write_point_t *)&g_mux_uart_r_w_point[port_index];
    uint32_t send_addr, send_len;
    uint32_t irq_mask;

    port_mux_cross_local_enter_critical(&irq_mask);
    send_len  = mux_common_device_get_buf_next_available_block_len(p->tx_buff_start, p->tx_buff_read_point, p->tx_buff_write_point, p->tx_buff_end, p->tx_buff_available_len);
    send_addr = p->tx_buff_read_point;
    if ((p->tx_send_is_running == MUX_DEVICE_HW_RUNNING) || (send_len == 0)) {
        port_mux_cross_local_exit_critical(irq_mask);
        return MUX_STATUS_ERROR_BUSY;
    } else {
        p->tx_send_is_running = MUX_DEVICE_HW_RUNNING;
    }
#ifndef ENABLE_MUX_UART_POLLING_SEND
    /* interrupt mode, statue clean by irq callback handle */
    port_mux_cross_local_exit_critical(irq_mask);
    uart_send_buffer(port_index, send_addr, send_len, &p->tx_sending_read_point, false);
#else
    /* polling mode, block send clean by current thread */
    uart_send_buffer(port_index, send_addr, send_len, &p->tx_sending_read_point, true);
    mux_common_device_set_tx_hw_rptr_internal_use(p, (p->tx_sending_read_point - p->tx_buff_read_point));
    p->tx_send_is_running = MUX_DEVICE_HW_IDLE; //change to idle
    port_mux_cross_local_exit_critical(irq_mask);
#endif

    return MUX_STATUS_OK;
}

void port_mux_uart_clear_rx_buf(uint8_t port_index)
{
    virtual_read_write_point_t *p = (virtual_read_write_point_t *)&g_mux_uart_r_w_point[port_index];

    p->rx_buff_read_point =  p->rx_buff_start;
    p->rx_buff_available_len = 0;
    return;
}

void port_mux_uart_clear_tx_buf(uint8_t port_index)
{
    uint32_t per_cpu_irq_mask;
    virtual_read_write_point_t *p = (virtual_read_write_point_t *)&g_mux_uart_r_w_point[port_index];

    port_mux_cross_local_enter_critical(&per_cpu_irq_mask);
    p->tx_buff_read_point = p->tx_buff_start;
    p->tx_buff_write_point = p->tx_buff_start;
    p->tx_buff_available_len = 0;
    p->tx_send_is_running = MUX_DEVICE_HW_IDLE;
    port_mux_cross_local_exit_critical(per_cpu_irq_mask);
    return;
}

/* [interrupt mode] before sleep, clear tx buffer */
void port_mux_uart_push_tx_buffer(uint8_t port_index)
{
    virtual_read_write_point_t *p = (virtual_read_write_point_t *)&g_mux_uart_r_w_point[port_index];
    uint32_t send_addr, send_len;

    /* monitor uart ready to write behavior
        before sleep, check if last IRQ not complete, wait busy flag and update virtual hw_rptr */
    if (p->tx_send_is_running == MUX_DEVICE_HW_RUNNING) {
        while (uart_send_dma_is_busy(port_index) == true);
        mux_common_device_set_tx_hw_rptr_internal_use(p, (p->tx_sending_read_point - p->tx_buff_read_point));
    }

    /* before back to sleep, check if there is data need to send */
    if (p->tx_buff_available_len != 0) {
        for (int i = 0; i < 2; i++) {
            send_len  = mux_common_device_get_buf_next_available_block_len(p->tx_buff_start, p->tx_buff_read_point, p->tx_buff_write_point, p->tx_buff_end, p->tx_buff_available_len);
            send_addr = p->tx_buff_read_point;
            if (send_len != 0) {
                uart_send_buffer(port_index, send_addr, send_len, &p->tx_sending_read_point, true);
                mux_common_device_set_tx_hw_rptr_internal_use(p, send_len);
            }
        }
    }
}

mux_status_t port_mux_uart_control(uint8_t port_index, mux_ctrl_cmd_t command, mux_ctrl_para_t *para)
{
    PORT_MUX_UNUSED(para);

    switch (command) {
        case MUX_CMD_CLEAN: {
            /* reset mux uart virtual fifo parameter */
            port_mux_uart_clear_tx_buf(port_index);
            port_mux_uart_clear_rx_buf(port_index);
#ifndef ENABLE_MUX_UART_POLLING_SEND
            /* [interrupt mode] enable uart tx interrupt for log continue send */
            uart_enable_tx_interrupt(port_index);
#endif
            return MUX_STATUS_OK;
        } break;

        case MUX_CMD_CLEAN_TX_VIRUTUAL: {
            port_mux_uart_clear_tx_buf(port_index);
            return MUX_STATUS_OK;
        } break;

        case MUX_CMD_CLEAN_RX_VIRUTUAL: {
            port_mux_uart_clear_rx_buf(port_index);
            return MUX_STATUS_OK;
        } break;

        case MUX_CMD_TX_BUFFER_SEND: {
#ifndef ENABLE_MUX_UART_POLLING_SEND
            /* irq mode disable uart interrupt and clear pending status */
            uart_disable_tx_interrupt(port_index);
            uart_clear_tx_pending_irq(port_index);

            /* [interrupt mode] empty the tx fifo left data */
            port_mux_uart_push_tx_buffer(port_index);
#endif
            return MUX_STATUS_OK;
        } break;

        default: {
        } break;
    }

    return MUX_STATUS_ERROR;
}

port_mux_device_ops_t g_port_mux_uart_ops = {
#ifdef CORE_MCU
    port_mux_uart_normal_init,
    port_mux_uart_deinit,
    port_mux_uart_exception_init,
    port_mux_uart_exception_send,
    port_mux_uart_buf_is_full,
#endif
    port_mux_uart_get_hw_rptr,
    port_mux_uart_set_rx_hw_rptr,
    port_mux_uart_get_hw_wptr,
    port_mux_uart_set_tx_hw_wptr,
    port_mux_uart_phase1_send,
    port_mux_uart_phase2_send,
    port_mux_uart_control,
    NULL,
    NULL,
};


#endif /* AIR_MUX_ENABLE */
