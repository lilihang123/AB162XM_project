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
/*
 * SPDX-License-Identifier: Apache-2.0
 */
#include <string.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>

#include "hal_uart.h"
#include "hal_uart_internal.h"

#include "hal_gpio.h"
#include "hal_gpio_internal.h"

#include "hal_nvic.h"
#include "hal_nvic_internal.h"

#include "memory_attribute.h"
#include "hal_pdma_internal.h"

// #ifndef assert(expr)
// #define assert(expr)
// #endif

#define DT_DRV_COMPAT airoha_air_uart

#define DT_N_NODELABEL_uart_P_0 HAL_UART_0
#define DT_N_NODELABEL_uart_P_1 HAL_UART_1
#define DT_N_NODELABEL_uart_P_2 HAL_UART_2

extern UART_REGISTER_T *const g_uart_regbase[];

#ifdef CONFIG_UART_ASYNC_API
extern vdma_channel_t uart_port_to_dma_map[2][3];
#define uart_port_to_dma_channel(uart_port, is_rx) (uart_port_to_dma_map[is_rx][uart_port])
static hal_uart_dma_config_t g_dma_config[HAL_UART_MAX];
#endif/*CONFIG_UART_ASYNC_API*/
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
    UART_REGISTER_T *adress_base;
    uint8_t uart_port;
    struct uart_pin_config pin_cfg;
};

#ifdef CONFIG_UART_ASYNC_API
struct uart_async_dma_config
{
    uint8_t *tx_buf;
    uint32_t tx_len;

    uint8_t *rx_buf;
    uint32_t offset;
    uint32_t len;
    uint8_t *next_rx_buf;
    uint32_t next_offset;
    uint32_t next_len;
};
#endif/*CONFIG_UART_ASYNC_API*/
struct uart_airoha_data
{
    // #ifdef CONFIG_UART_ASYNC_API
    uart_callback_t async_cb;
    void *async_cb_data;
    // #endif/*CONFIG_UART_ASYNC_API*/

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
    uart_irq_callback_user_data_t irq_cb;
    void *irq_cb_data;
#endif /*CONFIG_UART_INTERRUPT_DRIVEN*/
};

/*********************************other api -start line*****************************/
uint32_t baudrate_transition_to_airoha(uint32_t baudrate)
{
    hal_uart_baudrate_t baudrate_return = -1;
    switch (baudrate)
    {
    case 2000000:
        baudrate_return = HAL_UART_BAUDRATE_2000000;
        break;
    case 921600:
        baudrate_return = HAL_UART_BAUDRATE_921600;
        break;
    case 460800:
        baudrate_return = HAL_UART_BAUDRATE_460800;
        break;
    case 230400:
        baudrate_return = HAL_UART_BAUDRATE_230400;
        break;
    case 115200:
        baudrate_return = HAL_UART_BAUDRATE_115200;
        break;
    case 57600:
        baudrate_return = HAL_UART_BAUDRATE_57600;
        break;
    case 38400:
        baudrate_return = HAL_UART_BAUDRATE_38400;
        break;
    case 19200:
        baudrate_return = HAL_UART_BAUDRATE_19200;
        break;
    case 9600:
        baudrate_return = HAL_UART_BAUDRATE_9600;
        break;
    case 4800:
        baudrate_return = HAL_UART_BAUDRATE_4800;
        break;
    case 2400:
        baudrate_return = HAL_UART_BAUDRATE_2400;
        break;
    case 1200:
        baudrate_return = HAL_UART_BAUDRATE_1200;
        break;
    case 300:
        baudrate_return = HAL_UART_BAUDRATE_300;
        break;
    case 110:
        baudrate_return = HAL_UART_BAUDRATE_110;
        break;
    default:
        break;
    }
    return baudrate_return;
}

uint8_t parity_transition_to_airoha(uint8_t parity)
{
    hal_uart_parity_t parity_return = -1;
    switch (parity)
    {
    case UART_CFG_PARITY_NONE:
        parity_return = HAL_UART_PARITY_NONE;
        break;
    case UART_CFG_PARITY_ODD:
        parity_return = HAL_UART_PARITY_ODD;
        break;
    case UART_CFG_PARITY_EVEN:
        parity_return = HAL_UART_PARITY_EVEN;
        break;
    default:
        break;
    }
    return parity_return;
}

uint8_t stop_bits_transition_to_airoha(uint8_t stop_bits)
{
    hal_uart_stop_bit_t stop_bits_return = -1;
    if (stop_bits == UART_CFG_STOP_BITS_1)
    {
        stop_bits_return = HAL_UART_STOP_BIT_1;
    }
    if (stop_bits == UART_CFG_STOP_BITS_2)
    {
        stop_bits_return = HAL_UART_STOP_BIT_2;
    }
    return stop_bits_return;
}

uint8_t data_bits_transition_to_airoha(uint8_t data_bits)
{
    hal_uart_word_length_t data_bits_return = -1;
    switch (data_bits)
    {
    case UART_CFG_DATA_BITS_5:
        data_bits_return = HAL_UART_WORD_LENGTH_5;
        break;
    case UART_CFG_DATA_BITS_6:
        data_bits_return = HAL_UART_WORD_LENGTH_6;
        break;
    case UART_CFG_DATA_BITS_7:
        data_bits_return = HAL_UART_WORD_LENGTH_7;
        break;
    case UART_CFG_DATA_BITS_8:
        data_bits_return = HAL_UART_WORD_LENGTH_8;
        break;
    default:
        break;
    }
    return data_bits_return;
}
static inline const struct uart_airoha_cfg *get_port_cfg(const struct device *dev)
{
    return dev->config;
}

static inline const struct uart_airoha_data *get_port_data(const struct device *dev)
{
    return dev->data;
}
/*********************************other api -end line*****************************/

/*********************************************public API-start line*********************************/
static int uart_airoha_poll_in(const struct device *dev, unsigned char *c)
{
    static hal_uart_port_t uart_port;
    uart_port = get_port_cfg(dev)->uart_port;

    uint32_t value = 0x0;
    value = hal_uart_get_char_unblocking(uart_port);
    if (value == 0xffffffff)
    {
        return -1;
    }
    else
    {
        value &= 0xff;
    }

    *c = (unsigned char)value;
    return 0;
}

static void uart_airoha_poll_out(const struct device *dev, unsigned char c)
{
    static hal_uart_port_t uart_port;
    uart_port = get_port_cfg(dev)->uart_port;
    hal_uart_put_char(uart_port, c);
}

static int uart_airoha_err_check(const struct device *dev)
{
    static hal_uart_port_t uart_port;
    uart_port = get_port_cfg(dev)->uart_port;

    UART_REGISTER_T *uartx;
    uartx = g_uart_regbase[uart_port];
    enum uart_rx_stop_reason err = 0;

    if (((uartx->LSR) & UART_LSR_OE_MASK))
    {
        err = UART_ERROR_OVERRUN;
        return err;
    }
    if (((uartx->LSR) & UART_LSR_PE_MASK))
    {
        err = UART_ERROR_PARITY;
        return err;
    }
    if (((uartx->LSR) & UART_LSR_FE_MASK))
    {
        err = UART_ERROR_FRAMING;
        return err;
    }
    if (((uartx->LSR) & UART_LSR_BI_MASK))
    {
        err = UART_BREAK;
        return err;
    }
    return err;
}
/*********************************************public API-send line*********************************/

/********************************************************CONFIG_UART_USE_RUNTIME_CONFIGURE-start line*********************************/
#ifdef CONFIG_UART_USE_RUNTIME_CONFIGURE

static int uart_airoha_configure(const struct device *dev,
                                 const struct uart_config *cfg)
{
    static hal_uart_port_t uart_port;
    uart_port = get_port_cfg(dev)->uart_port;
    hal_uart_config_t uart_cfg;
    uart_cfg.baudrate = baudrate_transition_to_airoha(cfg->baudrate);
    uart_cfg.parity = parity_transition_to_airoha(cfg->parity);
    uart_cfg.stop_bit = stop_bits_transition_to_airoha(cfg->stop_bits);
    uart_cfg.word_length = data_bits_transition_to_airoha(cfg->data_bits);
    hal_uart_set_format(uart_port, &uart_cfg);
    return 0;
}

static int uart_airoha_config_get(const struct device *dev,
                                  struct uart_config *cfg)
{
    *cfg = get_port_cfg(dev)->uart_config;
    return 0;
}

#endif /*CONFIG_UART_USE_RUNTIME_CONFIGURE*/
/********************************************************CONFIG_UART_USE_RUNTIME_CONFIGURE-end line*********************************/

/**********************************************************CONFIG_UART_ASYNC_API-start-line*******************************************************************************/

#ifdef CONFIG_UART_ASYNC_API
static struct uart_event airoha_event_to_zephyr_evt(struct device *dev, hal_uart_callback_event_t event)
{
    printk("airoha_event_to_zephyr_evt-start\r\n");
    static hal_uart_port_t uart_port;
    uart_port = get_port_cfg(dev)->uart_port;

    if (event == HAL_UART_EVENT_READY_TO_READ)
    {
        struct uart_event evt = {
            .type = UART_RX_RDY,
            .data.rx.buf = NULL,
            .data.rx.len = 0,
            .data.rx.offset = 0};
        return evt;
    }

    if (event == HAL_UART_EVENT_READY_TO_WRITE)
    {
        struct uart_event evt = {
            .type = UART_TX_DONE,
            .data.tx.buf = NULL,
            .data.tx.len = 0};
        return evt;
    }

    if (event == HAL_UART_EVENT_TRANSACTION_ERROR)
    {
        enum uart_rx_stop_reason err_code = uart_airoha_err_check(dev);
        struct uart_event evt = {
            .type = UART_RX_STOPPED,
            .data.rx_stop.reason = err_code,
            .data.rx_stop.data.len = 0,
            .data.rx_stop.data.offset = 0,
            .data.rx_stop.data.buf = NULL};
        return evt;
    }

    if (event == HAL_UART_EVENT_TRANSMISSION_DONE)
    {
        struct uart_event evt = {
            .type = UART_TX_DONE,
            .data.tx.buf = NULL,
            .data.tx.len = 0,
        };
        return evt;
    }

    // if (event == HAL_UART_EVENT_RECEIVE_DEAD)
    // {
    //     struct uart_event evt = {
    //         .type = UART_RX_RDY,
    //         .data.rx.buf = &(g_dma_config[uart_port].receive_vfifo_buffer),
    //         .data.rx.len = 0,
    //         .data.rx.offset = 0};
    //     return evt;
    // }
    /*********flow  control********/
    // if (event == HAL_UART_EVENT_SW_FLOW_CTRL || event == HAL_UART_EVENT_HW_FLOW_CTRL)
    // {
    //     struct uart_event evt = {
    //         .type = UART_TX_ABORTED,
    //         .data.tx.buf = &(g_dma_config[uart_port].send_vfifo_buffer),
    //         .data.tx.len = 0};
    //     return evt;
    // }
    /***********wake up************/
    // if (event == HAL_UART_EVENT_WAKEUP_SLEEP)
    // {
    // }


    
    else{
        struct uart_event evt = {
            .type = UART_TX_DONE,
            .data.tx.buf = NULL,
            .data.tx.len = 0,
        };
        return evt;
    }
    printk("airoha_event_to_zephyr_evt-end\r\n");
}

static void uart_airoha_ASYNC_callback(hal_uart_callback_event_t event, void *user_data)
{
    printk("uart_airoha_ASYNC_callback-start\r\n");
    struct device *dev = user_data;
    struct uart_airoha_data *data = (struct uart_airoha_data *)dev->data;
    uart_callback_t callback;
    static void *user_data_cb;
    /* covert airoha event to  zephyr event */
    struct uart_event evt;
    evt = airoha_event_to_zephyr_evt(dev, event);
    /* get user callback and user data */
    callback = data->async_cb;
    user_data_cb = data->async_cb_data;
    /* run user callback */
    if (callback)
    {
        callback(dev, &evt, user_data_cb);
    }
    printk("uart_airoha_ASYNC_callback-end\r\n");
}

static int uart_airoha_callback_set(const struct device *dev,
                                    uart_callback_t callback,
                                    void *user_data)
{
    printk("uart_airoha_callback_set1\r\n");
    static hal_uart_port_t uart_port;
    struct uart_airoha_data *data = (struct uart_airoha_data *)dev->data;
    uart_port = get_port_cfg(dev)->uart_port;
    printk("uart_airoha_callback_set2\r\n");
    data->async_cb = callback;
    data->async_cb_data = user_data;
    printk("uart_airoha_callback_set3\r\n");
    hal_uart_register_callback(uart_port, uart_airoha_ASYNC_callback, (void *)dev);
    return 0;
}

static int uart_airoha_tx(const struct device *dev, const uint8_t *buf,
                          size_t len,
                          int32_t timeout)
{
    hal_uart_port_t uart_port;
    uart_port = get_port_cfg(dev)->uart_port;
    UART_REGISTER_T *uartx;
    uartx = g_uart_regbase[uart_port];
    size_t num;
    num = hal_uart_send_dma(uart_port, buf, len);
    return 0;
}

static int uart_airoha_tx_abort(const struct device *dev)
{
    hal_uart_port_t uart_port;
    uart_port = get_port_cfg(dev)->uart_port;
    vdma_channel_t tx_dma_channel;
    UART_REGISTER_T *uartx;
    uartx = g_uart_regbase[uart_port];
    tx_dma_channel = uart_port_to_dma_channel(uart_port, 0);
    // UART_ASSERT();
    return 0;
}

static int uart_airoha_rx_enable(const struct device *dev, uint8_t *buf,
                                 size_t len,
                                 int32_t timeout)
{
    hal_uart_port_t uart_port;
    uart_port = get_port_cfg(dev)->uart_port;
    UART_REGISTER_T *uartx;
    uartx = g_uart_regbase[uart_port];
    int num;
    num = hal_uart_receive_dma(uart_port, buf, len);
    return 0;
}

static int uart_airoha_rx_buf_rsp(const struct device *dev, uint8_t *buf,
                                  size_t len)
{
    return 0;
}

static int uart_airoha_rx_disable(const struct device *dev)
{
    hal_uart_port_t uart_port;
    uart_port = get_port_cfg(dev)->uart_port;
    UART_REGISTER_T *uartx;
    uartx = g_uart_regbase[uart_port];
    // UART_ASSERT();
    return 0;
}
#endif /*CONFIG_UART_ASYNC_API*/
/***************************************************************CONFIG_UART_ASYNC_API-start-line************************************************************/

/* *******************************************************Interrupt driven API-start line**********************************************************************/
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
/** Interrupt driven FIFO fill function */
static int uart_airoha_fifo_fill(const struct device *dev,
                                 const uint8_t *tx_data,
                                 int len)
{
    printk("in uart_airoha_fifo_fill\r\n");
    static hal_uart_port_t uart_port;
    uart_port = get_port_cfg(dev)->uart_port;
    // hal_uart_send_polling(uart_port, tx_data, len);
    int i;
    for (i = 0; i < len; i++)
    {
        hal_uart_put_char(uart_port, *tx_data);
        tx_data++;
    }
    return len;
}

/** Interrupt driven FIFO read function */
static int uart_airoha_fifo_read(const struct device *dev,
                                 uint8_t *rx_data,
                                 const int size)
{
    printk("\r\n in uart_airoha_fifo_read\r\n");
    static hal_uart_port_t uart_port;
    uart_port = get_port_cfg(dev)->uart_port;
    hal_uart_receive_polling(uart_port, rx_data, size);
    return size;
}

/** Interrupt driven transfer enabling function */
static void uart_airoha_irq_tx_enable(const struct device *dev)
{
    printk("in uart_airoha_irq_tx_enable\r\n"); // need to delete
    static hal_uart_port_t uart_port;
    uart_port = get_port_cfg(dev)->uart_port;
    // if (uart_port == HAL_UART_0)
    // {
    //     *(volatile uint8_t *)0xA003000C |= 0X1;
    // }
    // if (uart_port == HAL_UART_1)
    // {
    //     *(volatile uint8_t *)0xA007000C |= 0X1;
    // }
    // if (uart_port == HAL_UART_2)
    // {
    //     *(volatile uint8_t *)0xA008000C |= 0X1;
    // }
    uart_enable_tx_interrupt(uart_port);
}

/** Interrupt driven transfer disabling function */
static void uart_airoha_irq_tx_disable(const struct device *dev)
{
    static hal_uart_port_t uart_port;
    uart_port = get_port_cfg(dev)->uart_port;
    // if (uart_port == HAL_UART_0)
    // {
    //     *(volatile uint8_t *)0xA003000C &= 0Xfe;
    // }
    // if (uart_port == HAL_UART_1)
    // {
    //     *(volatile uint8_t *)0xA007000C &= 0Xfe;
    // }
    // if (uart_port == HAL_UART_2)
    // {
    //     *(volatile uint8_t *)0xA008000C &= 0Xfe;
    // }
    uart_disable_tx_interrupt(uart_port);
}

/** Interrupt driven receiver enabling function */
static void uart_airoha_irq_rx_enable(const struct device *dev)
{
    static hal_uart_port_t uart_port;
    uart_port = get_port_cfg(dev)->uart_port;
    printk("in uart_airoha_irq_rx_enable & uart_port: %d\r\n", uart_port); // need to delete
    // if (uart_port == HAL_UART_0)
    // {
    //     *(volatile uint16_t *)0xA003000C |= 0X100;
    // }
    // if (uart_port == HAL_UART_1)
    // {
    //     *(volatile uint16_t *)0xA007000C |= 0X100;
    // }
    // if (uart_port == HAL_UART_2)
    // {
    //     *(volatile uint16_t *)0xA008000C |= 0X100;
    // }
    uart_enable_rx_interrupt(uart_port);
}

/** Interrupt driven receiver disabling function */
static void uart_airoha_irq_rx_disable(const struct device *dev)
{
    static hal_uart_port_t uart_port;
    uart_port = get_port_cfg(dev)->uart_port;
    // if (uart_port == HAL_UART_0)
    // {
    //     *(volatile uint16_t *)0xA003000C &= 0Xfeff;
    // }
    // if (uart_port == HAL_UART_1)
    // {
    //     *(volatile uint16_t *)0xA007000C &= 0Xfeff;
    // }
    // if (uart_port == HAL_UART_2)
    // {
    //     *(volatile uint16_t *)0xA008000C &= 0Xfeff;
    // }
    uart_disable_rx_interrupt(uart_port);
}

/** Interrupt driven transfer empty function */
static int uart_airoha_irq_tx_ready_complete(const struct device *dev)
{
    printk("in uart_airoha_irq_tx_ready_complete\r\n"); // need to delete
    static hal_uart_port_t uart_port;
    uart_port = get_port_cfg(dev)->uart_port;
    if (uart_query_tx_empty(uart_port))
    {
        return 1;
    }
    return 0;
}

/** Interrupt driven receiver ready function */
static int uart_airoha_irq_rx_ready(const struct device *dev)
{
    printk("in uart_airoha_irq_rx_ready\r\n"); // need to delete
    static hal_uart_port_t uart_port;
    uart_port = get_port_cfg(dev)->uart_port;
    if (uart_query_rx_empty(uart_port))
    {
        return 1;
    }
    return 0;
}

/** Interrupt driven error enabling function */
static void uart_airoha_irq_err_enable(const struct device *dev)
{
    printk("in uart_airoha_irq_err_enable\r\n"); // need to delete
    static hal_uart_port_t uart_port;
    uart_port = get_port_cfg(dev)->uart_port;
    static UART_REGISTER_T *UART;
    if (uart_port == HAL_UART_0)
    {
        UART = UART0;
    }
    if (uart_port == HAL_UART_1)
    {
        UART = UART1;
    }
    if (uart_port == HAL_UART_2)
    {
        UART = UART2;
    }
    uart_unmask_send_interrupt(UART);
    uart_unmask_receive_interrupt(UART);
}

/** Interrupt driven error disabling function */
static void uart_airoha_irq_err_disable(const struct device *dev)
{
    static hal_uart_port_t uart_port;
    uart_port = get_port_cfg(dev)->uart_port;
    static UART_REGISTER_T *UART;
    if (uart_port == HAL_UART_0)
    {
        UART = UART0;
    }
    if (uart_port == HAL_UART_1)
    {
        UART = UART1;
    }
    if (uart_port == HAL_UART_2)
    {
        UART = UART2;
    }
    uart_mask_send_interrupt(UART);
    uart_mask_receive_interrupt(UART);
}

/** Interrupt driven pending status function */
static int uart_airoha_irq_is_pending(const struct device *dev)
{
    return 1;
}

/** Interrupt driven interrupt update function */
static int uart_airoha_irq_update(const struct device *dev)
{
    return 1;
}

/** Set the callback function */
// void uart_airoha_irq_isr(hal_nvic_irq_t irq_number)
// {
//     printk("uart_airoha_irq_isr\r\n");
// }

// static void uart_airoha_irq_callback(hal_uart_callback_event_t event, void *user_data)
// {
//     printk("uart_airoha_irq_callback-start\r\n");
//     struct device *dev = user_data;
//     struct uart_airoha_data *data = (struct uart_airoha_data *)dev->data;
//     uart_callback_t callback;
//     static void *user_data_cb;
//     /* covert airoha event to  zephyr event */
//     struct uart_event evt;
//     // evt = airoha_event_to_zephyr_evt(dev, event);
//     /* get user callback and user data */
//     callback = data->irq_cb;
//     user_data_cb = data->irq_cb_data;
//     /* run user callback */
//     if (callback)
//     {
//         callback(dev, &evt, user_data_cb);
//     }
//     printk("uart_airoha_irq_callback-end\r\n");
// }

extern void uart_interrupt_handler(hal_nvic_irq_t irq_number);
static void uart_airoha_irq_callback_set(const struct device *dev,
                                         uart_irq_callback_user_data_t cb,
                                         void *cb_data)
{
    printk("uart_airoha_callback_set1\r\n");
    static hal_uart_port_t uart_port;
    struct uart_airoha_data *data = (struct uart_airoha_data *)dev->data;
    uart_port = get_port_cfg(dev)->uart_port;
    printk("uart_airoha_callback_set2\r\n");
    data->irq_cb = cb;
    data->irq_cb_data = cb_data;
    printk("uart_airoha_callback_set3\r\n");
    // hal_uart_register_callback(uart_port, uart_airoha_ASYNC_callback, (void *)dev);

    // hal_zephyr_uart_register_callback(uart_port, uart_airoha_ASYNC_callback, (void *)dev);
}

#endif /* CONFIG_UART_INTERRUPT_DRIVEN */
/* *******************************************************Interrupt driven API-end line**********************************************************************/

static int uart_airoha_init(const struct device *dev)
{
    static hal_uart_port_t uart_port;
    uart_port = get_port_cfg(dev)->uart_port;
    /*    uart_cfg   set  */
    struct uart_config cfg;
    cfg = get_port_cfg(dev)->uart_config;
    // printk("uart_airoha_init-start\r\n");
    /*******************************--gpio-init-start********************/
    // if (uart_port == HAL_UART_0)
    // {
    //     /*uart0_TX gpio init and Take by pin*/
    //     hal_gpio_init(HAL_GPIO_0);
    //     hal_pinmux_set_function(HAL_GPIO_0, 1);
    //     /*uart0_RX gpio init and Take by pin*/
    //     hal_gpio_init(HAL_GPIO_1);
    //     hal_pinmux_set_function(HAL_GPIO_1, 1);
    // }

    // if (uart_port == HAL_UART_1)
    // {
    //     /*uart1_TX gpio init and Take by pin*/
    //     hal_gpio_init(HAL_GPIO_4);
    //     hal_pinmux_set_function(HAL_GPIO_4, 2);
    //     /*uart1_RX gpio init and Take by pin*/
    //     hal_gpio_init(HAL_GPIO_5);
    //     hal_pinmux_set_function(HAL_GPIO_5, 2);
    // }
    // if (uart_port == HAL_UART_2)
    // {
    //     // /*uart1_TX gpio init and Take by pin*/
    //     hal_gpio_init(HAL_GPIO_18);
    //     hal_pinmux_set_function(HAL_GPIO_18, 8);
    //     /*uart1_RX gpio init and Take by pin*/
    //     hal_gpio_init(HAL_GPIO_19);
    //     hal_pinmux_set_function(HAL_GPIO_19, 8);
    // }
    /*******************************--gpio-init-end*************************/

    /***************************uart config-start line *********************/
    hal_uart_config_t uart_cfg;
    uart_cfg.baudrate = baudrate_transition_to_airoha(cfg.baudrate);
    uart_cfg.parity = parity_transition_to_airoha(cfg.parity);
    uart_cfg.stop_bit = stop_bits_transition_to_airoha(cfg.stop_bits);
    uart_cfg.word_length = data_bits_transition_to_airoha(cfg.data_bits);
    hal_uart_init(uart_port, &uart_cfg);

    printk("hal_uart_init,%d\r\n", uart_port);

    // hal_nvic_status_t nvic_status;
    // nvic_status = hal_nvic_register_isr_handler(16, uart_airoha_irq_isr);
    // if (nvic_status != HAL_NVIC_STATUS_OK)
    // {
    //     UART_ASSERT();
    //     return HAL_UART_STATUS_ERROR;
    // }

    /***************************uart config-end line***********************/

    /***************************set dma-start line*************************/
    #ifdef CONFIG_UART_ASYNC_API
    static char ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN rx_vfifo_buffer[512];
    static char ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN tx_vfifo_buffer[512];
    hal_uart_dma_config_t dma_config;
    dma_config.receive_vfifo_alert_size = 50;
    dma_config.receive_vfifo_buffer = rx_vfifo_buffer;
    dma_config.receive_vfifo_buffer_size = 512;
    dma_config.receive_vfifo_threshold_size = 128;
    dma_config.send_vfifo_buffer = tx_vfifo_buffer;
    dma_config.send_vfifo_buffer_size = 512;
    dma_config.send_vfifo_threshold_size = 51;

    g_dma_config[uart_port] = dma_config;
    hal_uart_set_dma(uart_port, &dma_config);
    #endif /* CONFIG_UART_ASYNC_API */
    // /***************************setdma-end line****************************/
    return 0;
}

static const struct uart_driver_api uart_airoha_driver_api = {
#ifdef CONFIG_UART_ASYNC_API
    .callback_set = uart_airoha_callback_set,
    .tx = uart_airoha_tx,
    .tx_abort = uart_airoha_tx_abort,
    .rx_enable = uart_airoha_rx_enable,
    .rx_buf_rsp = uart_airoha_rx_buf_rsp,
    .rx_disable = uart_airoha_rx_disable,
#endif /* CONFIG_UART_ASYNC_API */
    .poll_in = uart_airoha_poll_in,
    .poll_out = uart_airoha_poll_out,
    .err_check = uart_airoha_err_check,
#ifdef CONFIG_UART_USE_RUNTIME_CONFIGURE
    .configure = uart_airoha_configure,
    .config_get = uart_airoha_config_get,
#endif /*CONFIG_UART_USE_RUNTIME_CONFIGURE*/
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
    .fifo_fill = uart_airoha_fifo_fill,
    .fifo_read = uart_airoha_fifo_read,
    .irq_tx_enable = uart_airoha_irq_tx_enable,
    .irq_tx_disable = uart_airoha_irq_tx_disable,
    .irq_tx_ready = uart_airoha_irq_tx_ready_complete,
    .irq_rx_enable = uart_airoha_irq_rx_enable,
    .irq_rx_disable = uart_airoha_irq_rx_disable,
    .irq_tx_complete = uart_airoha_irq_tx_ready_complete,
    .irq_rx_ready = uart_airoha_irq_rx_ready,
    .irq_err_enable = uart_airoha_irq_err_enable,
    .irq_err_disable = uart_airoha_irq_err_disable,
    .irq_is_pending = uart_airoha_irq_is_pending,
    .irq_update = uart_airoha_irq_update,
    .irq_callback_set = uart_airoha_irq_callback_set,
#endif /* CONFIG_UART_INTERRUPT_DRIVEN */
};

uint8_t async_tx_buf[256];
uint8_t async_rx_buf[256];

#define UART_AIROHA_DEVICE(id)                                     \
    static const struct uart_airoha_cfg uart_airoha_##id##_cfg = { \
        .uart_config = {                                           \
            .baudrate = 921600,                                    \
            .data_bits = UART_CFG_DATA_BITS_8,                     \
            .stop_bits = UART_CFG_STOP_BITS_1,                     \
            .parity = UART_CFG_PARITY_NONE,                        \
        },                                                         \
        .adress_base = NULL,                                       \
        .uart_port = DT_PROP(DT_NODELABEL(uart), id)};             \
                                                                   \
    static struct uart_airoha_data uart_airoha_##id##_data = {     \
        .async_cb = NULL,                                          \
        .async_cb_data = NULL,                                     \
    };                                                             \
                                                                   \
    DEVICE_DT_INST_DEFINE(id, uart_airoha_init,                    \
                          NULL,                                    \
                          &uart_airoha_##id##_data,                \
                          &uart_airoha_##id##_cfg,                 \
                          CONFIG_SERIAL_INIT_LEVEL,                \
                          CONFIG_SERIAL_INIT_PRIORITY,             \
                          &uart_airoha_driver_api);
DT_INST_FOREACH_STATUS_OKAY(UART_AIROHA_DEVICE);

// static struct uart_async_dma_config uart_airoha_##id##_data = {
    //     .tx_buf=NULL,                                               
    //     .tx_len=0,                                                  
    //     .rx_buf=NULL,                                               
    //     .offset=0,                                                  
    //     .len=0,                                                     
    //     .next_rx_buf=NULL,                                          
    //     .next_offset=0,                                             
    //     .next_len=0,                                                
    // };