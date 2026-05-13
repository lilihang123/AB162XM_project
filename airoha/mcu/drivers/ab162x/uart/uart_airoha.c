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

#include <assert.h>
#include <string.h>
#include "memory_attribute.h"

#include <zephyr/drivers/uart.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>

#include "hal_uart.h"
#include "hal_uart_internal.h"
#include "hal_gpt.h"
#include "hal_gpt_internal.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_internal.h"
#include "hal_gpio.h"
#include "hal_gpio_internal.h"
#include "hal_nvic.h"
#include "hal_nvic_internal.h"
#include "hal_pdma_internal.h"
#if defined(AIR_SHARE_BUFFER_ENABLE)
#include "share_buffer.h"
#endif /* AIR_SHARE_BUFFER_ENABLE */

#define DT_DRV_COMPAT airoha_air_uart

#define UART_FLOW_CTRL_DISABLE 0
#define UART_HW_FLOW_CTRL_ENABLE 1
#define UART_SW_FLOW_CTRL_ENBALE 2
// #define UART_DEBUG_LOG

typedef enum {
    UART_IRQ_EVENT_INTERRUPT_NONE= 0,
    UART_IRQ_EVENT_INTERRUPT_TRANSACTION_ERROR = 1,
    UART_IRQ_EVENT_INTERRUPT_RECEIVE_AVAILABLE = 2,
    UART_IRQ_EVENT_INTERRUPT_SEND_AVAILABLE = 3,
    UART_IRQ_EVENT_INTERRUPT_SEND_EMPTY = 4,
#ifdef HAL_UART_FEATURE_FLOWCONTROL_CALLBACK
    UART_IRQ_EVENT_INTERRUPT_SOFTWARE_FLOWCONTROL = 5,
    UART_IRQ_EVENT_INTERRUPT_HARDWARE_FLOWCONTROL = 6,
#endif
    UART_IRQ_EVENT_INTERRUPT_RECEIVE_DEAD = 7,
    UART_IRQ_EVENT_INTERRUPT_WAKEUP_SLEEP = 8,
} uart_callback_irq_event_t;

struct uart_pin_config
{
    uint32_t tx_pin;
    uint32_t rx_pin;
    uint32_t rts_pin;
    uint32_t cts_pin;
    bool rx_pull_up;
    bool cts_pull_up;
    uint8_t sw_flow_ctrl;
};

struct uart_airoha_cfg
{
    struct uart_config uart_config;
    uint8_t uart_port;
    struct uart_pin_config pin_cfg;
};


struct uart_airoha_data
{
    uart_irq_callback_user_data_t irq_cb;
    void *irq_cb_data;
};

typedef struct {
    uint32_t tx_buf_addr;
    uint32_t rx_buf_addr;
    uint32_t tx_buf_size;
    uint32_t rx_buf_size;
} uart_port_buf_config_t;

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
extern UART_REGISTER_T *const g_uart_regbase[];
static bool tx_avaliable_flag[HAL_UART_MAX]={false, false, false};
static bool tx_complete_flag[HAL_UART_MAX]={false, false, false};
static bool rx_receive_data_flag[HAL_UART_MAX]={false, false, false};
static uart_callback_irq_event_t g_current_callback_evet[HAL_UART_MAX] = {UART_IRQ_EVENT_INTERRUPT_NONE, UART_IRQ_EVENT_INTERRUPT_NONE, UART_IRQ_EVENT_INTERRUPT_NONE};
static uart_port_buf_config_t g_port_buf_cfg[HAL_UART_MAX];
#endif/*CONFIG_UART_INTERRUPT_DRIVEN*/

const char *const uart_lock_sleep_name= "UART";
uint32_t uart_lock_sleep_handle;
uint32_t gpt_handle;

hal_uart_baudrate_t baudrate_transition_to_airoha(uint32_t baudrate)
{
    hal_uart_baudrate_t baudrate_return = HAL_UART_BAUDRATE_MAX;
    switch (baudrate)
    {
    case 8666000:
        baudrate_return = HAL_UART_BAUDRATE_8666000;
        break;
    case 6000000:
        baudrate_return = HAL_UART_BAUDRATE_6000000;
        break;
    case 3200000:
        baudrate_return = HAL_UART_BAUDRATE_3200000;
        break;
    case 3000000:
        baudrate_return = HAL_UART_BAUDRATE_3000000;
        break;
    case 2000000:
        baudrate_return = HAL_UART_BAUDRATE_2000000;
        break;
    case 1000000:
        baudrate_return = HAL_UART_BAUDRATE_1000000;
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

hal_uart_parity_t parity_transition_to_airoha(uint8_t parity)
{
    const hal_uart_parity_t parity_map[] = {
        HAL_UART_PARITY_NONE,
        HAL_UART_PARITY_ODD,
        HAL_UART_PARITY_EVEN,
        /* Not support parity mark or space, default none*/
        HAL_UART_PARITY_NONE,
        HAL_UART_PARITY_NONE,
    };
    __ASSERT_NO_MSG(parity < (sizeof(parity_map)/sizeof(parity_map[0])));
    return parity_map[parity];
}

uint8_t stop_bits_transition_to_airoha(uint8_t stop_bits)
{
    const hal_uart_stop_bit_t stop_bit_map[] = {
        /* Not support stop bits of 0_5 & 1_5, default STOP_BIT_1 */
        HAL_UART_STOP_BIT_1,
        HAL_UART_STOP_BIT_1,
        HAL_UART_STOP_BIT_1,
        HAL_UART_STOP_BIT_2,
    };
    __ASSERT_NO_MSG(stop_bits < (sizeof(stop_bit_map)/sizeof(stop_bit_map[0])));
    return stop_bit_map[stop_bits];
}

uint8_t data_bits_transition_to_airoha(uint8_t data_bits)
{
    hal_uart_word_length_t data_bits_map[] = {
        HAL_UART_WORD_LENGTH_5,
        HAL_UART_WORD_LENGTH_6,
        HAL_UART_WORD_LENGTH_7,
        HAL_UART_WORD_LENGTH_8,
        /* Not support data bits of UART_CFG_DATA_BITS_9 */
        HAL_UART_WORD_LENGTH_8,
    };
    __ASSERT_NO_MSG(data_bits < (sizeof(data_bits_map)/sizeof(data_bits_map[0])));
    return data_bits_map[data_bits];
}


static int uart_airoha_poll_in(const struct device *dev, unsigned char *p_char)
{
    /* From zephyr, this function is a non-blocking call. */
    hal_uart_port_t uart_port = ((struct uart_airoha_cfg*)(dev->config))->uart_port;

    uint32_t value = 0x0;
    value = hal_uart_get_char_unblocking(uart_port);
    if (value == 0xffffffff) {
        return -1;
    } else {
        value &= 0xff;
    }

    *p_char = (unsigned char)value;
    return 0;
}

static void uart_airoha_poll_out(const struct device *dev, unsigned char out_char)
{
    /* From zephyr, this function is a blocking call. */
    hal_uart_put_char(((struct uart_airoha_cfg*)(dev->config))->uart_port, (char)out_char);
}

static int uart_airoha_err_check(const struct device *dev)
{
    // hal_uart_port_t uart_port = ((struct uart_airoha_cfg*)(dev->config))->uart_port;
    // UART_REGISTER_T *uart = g_uart_regbase[uart_port];

    // if (((uart->LSR) & UART_LSR_OE_MASK)) {
    //     return UART_ERROR_OVERRUN;
    // }
    // if (((uart->LSR) & UART_LSR_PE_MASK)) {
    //     return UART_ERROR_PARITY;
    // }
    // if (((uart->LSR) & UART_LSR_FE_MASK)) {
    //     return UART_ERROR_FRAMING;
    // }
    // if (((uart->LSR) & UART_LSR_BI_MASK)) {
    //     return UART_BREAK;
    // }
    /* return 0 if no error was detected */
    return 0;
}


#ifdef CONFIG_UART_USE_RUNTIME_CONFIGURE

static int uart_airoha_configure(const struct device *dev,
                                 const struct uart_config *cfg)
{
    hal_uart_port_t uart_port = ((struct uart_airoha_cfg*)(dev->config))->uart_port;
    hal_uart_config_t uart_cfg;
    uart_cfg.baudrate = baudrate_transition_to_airoha(cfg->baudrate);
    uart_cfg.parity = parity_transition_to_airoha(cfg->parity);
    uart_cfg.stop_bit = stop_bits_transition_to_airoha(cfg->stop_bits);
    uart_cfg.word_length = data_bits_transition_to_airoha(cfg->data_bits);
    hal_uart_set_format(uart_port, &uart_cfg);

    /* not support config uart_config_flow_config parameter, ignore the setting */
    void *dest = (void*)(&(((struct uart_airoha_cfg*)(dev->config))->uart_config));
    memcpy(dest, (void*)cfg, sizeof(struct uart_config));
    ((struct uart_config*)dest)->flow_ctrl = UART_CFG_FLOW_CTRL_NONE;

    return 0;
}

static int uart_airoha_config_get(const struct device *dev,
                                  struct uart_config *cfg)
{
    void *src = (void*)(&(((struct uart_airoha_cfg*)(dev->config))->uart_config));
    memcpy((void*)cfg, src, sizeof(struct uart_config));
    return 0;
}

#endif /*CONFIG_UART_USE_RUNTIME_CONFIGURE*/


#ifdef CONFIG_UART_INTERRUPT_DRIVEN
/* Fill FIFO with data */
static int uart_airoha_fifo_fill(const struct device *dev,
                                 const uint8_t *tx_data,
                                 int len)
{
    hal_uart_port_t uart_port = ((struct uart_airoha_cfg*)(dev->config))->uart_port;
    #ifdef UART_DEBUG_LOG
    printk("in uart_airoha_fifo_fill, uart port: %d,len=%d\r\n",uart_port, len);
    #endif
    int send_cnt = 0;
    send_cnt = (int)hal_uart_send_dma(uart_port, tx_data, len);
    tx_avaliable_flag[uart_port] = false;
    tx_complete_flag[uart_port] = false;
    return send_cnt;
}


/* Read data from FIFO */
static int uart_airoha_fifo_read(const struct device *dev,
                                 uint8_t *rx_data,
                                 const int size)
{

    hal_uart_port_t uart_port = ((struct uart_airoha_cfg*)(dev->config))->uart_port;
    if ((uart_port >= HAL_UART_MAX) || (uart_port < HAL_UART_0)) {
        return -1;
    }
    int recv_count = 0;
    recv_count = (int)hal_uart_receive_dma(uart_port, rx_data, size);
    rx_receive_data_flag[uart_port] = false;
    #ifdef UART_DEBUG_LOG
    printk("in uart_airoha_fifo_read,uart port: %d,recv_cnt=%d\r\n",uart_port, recv_count);
    #endif
    return recv_count;
}

/* Enable TX interrupt */
static void uart_airoha_irq_tx_enable(const struct device *dev)
{
    hal_uart_port_t uart_port = ((struct uart_airoha_cfg*)(dev->config))->uart_port;
    struct uart_airoha_data *data = (struct uart_airoha_data *)dev->data;

    #ifdef UART_DEBUG_LOG
    printk("in uart_airoha_irq_tx_enable & uart_port: %d\r\n", uart_port);
    #endif
    uart_enable_tx_interrupt(uart_port);
    // uart_enable_dma_interrupt(uart_port, false);
    uart_disable_dma_interrupt(uart_port, false);  //zephyr uart not use uart tx dma irq (openthread special request)
    g_current_callback_evet[uart_port] = UART_IRQ_EVENT_INTERRUPT_SEND_AVAILABLE;
    tx_avaliable_flag[uart_port] = true;
    
    if(data->irq_cb){
        data->irq_cb(dev, data->irq_cb_data);
    }
}

/* Disable TX interrupt */
static void uart_airoha_irq_tx_disable(const struct device *dev)
{
    hal_uart_port_t uart_port = ((struct uart_airoha_cfg*)(dev->config))->uart_port;
    #ifdef UART_DEBUG_LOG
    printk("in uart_airoha_irq_tx_disable & uart_port: %d\r\n", uart_port);
    #endif
    uart_disable_tx_interrupt(uart_port);
    // uart_disable_dma_interrupt(uart_port, false);
}


/* Check if UART TX buffer can accept a new char */
static int uart_airoha_irq_tx_ready(const struct device *dev)
{
    #ifdef UART_DEBUG_LOG
    printk("in uart_airoha_irq_tx_ready\r\n");
    #endif
    hal_uart_port_t uart_port = ((struct uart_airoha_cfg*)(dev->config))->uart_port;
    if(g_current_callback_evet[uart_port] == UART_IRQ_EVENT_INTERRUPT_SEND_AVAILABLE||
       g_current_callback_evet[uart_port] == UART_IRQ_EVENT_INTERRUPT_SEND_EMPTY ||
       tx_avaliable_flag[uart_port] == true || tx_complete_flag[uart_port] == true)
    {
        g_current_callback_evet[uart_port] = UART_IRQ_EVENT_INTERRUPT_NONE;
        return 1;
    }

    return 0;
}

/* Check if UART TX block finished transmission */
static int uart_airoha_irq_tx_complete(const struct device *dev)
{
    #ifdef UART_DEBUG_LOG
    printk("in uart_airoha_irq_tx_complete\r\n");
    #endif
    hal_uart_port_t uart_port = ((struct uart_airoha_cfg*)(dev->config))->uart_port;
    if(g_current_callback_evet[uart_port] == UART_IRQ_EVENT_INTERRUPT_SEND_EMPTY || tx_complete_flag[uart_port] == true)
    {
        g_current_callback_evet[uart_port] = UART_IRQ_EVENT_INTERRUPT_NONE;
        return 1;
    }

    return 0;
}

/* Enable RX interrupt */
static void uart_airoha_irq_rx_enable(const struct device *dev)
{
    hal_uart_port_t uart_port = ((struct uart_airoha_cfg*)(dev->config))->uart_port;
    #ifdef UART_DEBUG_LOG
    printk("in uart_airoha_irq_rx_enable & uart_port: %d\r\n", uart_port);
    #endif
    uart_enable_rx_interrupt(uart_port);
    // uart_enable_dma_interrupt(uart_port, true);
    uart_disable_dma_interrupt(uart_port, true); //zephyr uart not use uart rx dma irq (openthread special request)
}

/* Disable RX interrupt */
static void uart_airoha_irq_rx_disable(const struct device *dev)
{
    hal_uart_port_t uart_port = ((struct uart_airoha_cfg*)(dev->config))->uart_port;
    #ifdef UART_DEBUG_LOG
    printk("in uart_airoha_irq_rx_disable & uart_port: %d\r\n", uart_port);
    #endif
    uart_disable_rx_interrupt(uart_port);
    // uart_disable_dma_interrupt(uart_port, true);
}

/* Check if UART RX buffer has a received char */
static int uart_airoha_irq_rx_ready(const struct device *dev)
{
    #ifdef UART_DEBUG_LOG
    printk("in uart_airoha_irq_rx_ready\r\n");
    #endif
    hal_uart_port_t uart_port = ((struct uart_airoha_cfg*)(dev->config))->uart_port;
    if(g_current_callback_evet[uart_port] ==UART_IRQ_EVENT_INTERRUPT_RECEIVE_AVAILABLE || rx_receive_data_flag[uart_port] == true)
    {
        printk("uart_airoha_irq_rx_ready, uart2 rx dma irq:0x%x\r\n", *(volatile uint32_t*)0x42290214); 
        g_current_callback_evet[uart_port] = UART_IRQ_EVENT_INTERRUPT_NONE;
        return 1;
    }
    return 0;
}

/* Check if any IRQs is pending */
static int uart_airoha_irq_is_pending(const struct device *dev)
{
    #ifdef UART_DEBUG_LOG
    printk("in uart_airoha_irq_is_pending\r\n");
    #endif
    hal_uart_port_t uart_port = ((struct uart_airoha_cfg*)(dev->config))->uart_port;
    if(g_current_callback_evet[uart_port]!=UART_IRQ_EVENT_INTERRUPT_NONE)
    {
        return 1;
    }
    return 0;
}

/* Start processing interrupts in ISR */
static int uart_airoha_irq_update(const struct device *dev)
{ 
    #ifdef UART_DEBUG_LOG  
    printk("in uart_airoha_irq_update\r\n");
    #endif
    hal_uart_port_t uart_port = ((struct uart_airoha_cfg*)(dev->config))->uart_port;
    if(g_current_callback_evet[uart_port]==UART_IRQ_EVENT_INTERRUPT_RECEIVE_AVAILABLE||
    g_current_callback_evet[uart_port]==UART_IRQ_EVENT_INTERRUPT_SEND_AVAILABLE||
    g_current_callback_evet[uart_port]==UART_IRQ_EVENT_INTERRUPT_SEND_EMPTY)
    {
        return 1;
    }else
    {   
        g_current_callback_evet[uart_port]=UART_IRQ_EVENT_INTERRUPT_NONE;
        return 0;
    }

}

static uart_callback_irq_event_t uart_callback_event_transition_to_irq_event(hal_uart_callback_event_t event)
{
    uart_callback_irq_event_t irq_event = UART_IRQ_EVENT_INTERRUPT_NONE;
    switch(event)
    {
        case HAL_UART_EVENT_TRANSACTION_ERROR:
            irq_event = UART_IRQ_EVENT_INTERRUPT_TRANSACTION_ERROR;
            break;
        case HAL_UART_EVENT_READY_TO_READ:
            irq_event = UART_IRQ_EVENT_INTERRUPT_RECEIVE_AVAILABLE;
            break;
        case HAL_UART_EVENT_READY_TO_WRITE:
            irq_event = UART_IRQ_EVENT_INTERRUPT_SEND_AVAILABLE;
            break;
        case HAL_UART_EVENT_WAKEUP_SLEEP:
            irq_event = UART_IRQ_EVENT_INTERRUPT_WAKEUP_SLEEP;
            break;
#ifdef HAL_UART_FEATURE_FLOWCONTROL_CALLBACK
        case HAL_UART_EVENT_SW_FLOW_CTRL:
            irq_event = UART_IRQ_EVENT_INTERRUPT_SOFTWARE_FLOWCONTROL;
            break;
        case HAL_UART_EVENT_HW_FLOW_CTRL:
            irq_event = UART_IRQ_EVENT_INTERRUPT_HARDWARE_FLOWCONTROL;
            break;
#endif
        case HAL_UART_EVENT_TRANSMISSION_DONE:
            irq_event = UART_IRQ_EVENT_INTERRUPT_SEND_EMPTY;
            break;
        case HAL_UART_EVENT_RECEIVE_DEAD:
            irq_event = UART_IRQ_EVENT_INTERRUPT_RECEIVE_DEAD;
            break;
        case HAL_UART_EVENT_RECEIVE_BREAK_SIGNAL:
            irq_event = UART_IRQ_EVENT_INTERRUPT_TRANSACTION_ERROR;
            break;
        default:
            return UART_IRQ_EVENT_INTERRUPT_NONE;
    }
    return irq_event;
}

 void user_gpt_callback (void *user_data)
{   
    (void)user_data;
    if (hal_sleep_manager_is_sleep_handle_alive(uart_lock_sleep_handle) == true) {
        hal_sleep_manager_unlock_sleep(uart_lock_sleep_handle);
    }
    // user's handler
    hal_gpt_sw_stop_timer_ms(gpt_handle);
}

static void uart_user_callback(hal_uart_callback_event_t event, void *user_data)
{
    const struct device *dev = (const struct device *)user_data;
    struct uart_airoha_data *data = (struct uart_airoha_data *)dev->data;
    hal_uart_port_t uart_port = ((struct uart_airoha_cfg*)(dev->config))->uart_port;
    g_current_callback_evet[uart_port] = uart_callback_event_transition_to_irq_event(event);
    if(event == HAL_UART_EVENT_READY_TO_READ)
    {
      rx_receive_data_flag[uart_port] = true;
    }

    if(event == HAL_UART_EVENT_READY_TO_WRITE)
    {
      tx_avaliable_flag[uart_port] = true;
    }

    if(event == HAL_UART_EVENT_TRANSMISSION_DONE)
    {
        tx_complete_flag[uart_port] = true;
        tx_avaliable_flag[uart_port] = true;
    }

    if(event == HAL_UART_EVENT_WAKEUP_SLEEP){
        //Set the timeout to 10 ms, and register the callback at the same time
        if(HAL_GPT_STATUS_OK == hal_gpt_sw_start_timer_ms(gpt_handle, 1000, user_gpt_callback, &uart_port)) {
            //error handler
            hal_sleep_manager_lock_sleep(uart_lock_sleep_handle);
        }
    }

    if(data->irq_cb){
        data->irq_cb(dev, data->irq_cb_data);
    }
}

#define UART0_NODE_ID DT_NODELABEL(uart0)
#define UART_0_RX_BUF_SIZE DT_PROP(UART0_NODE_ID,rbuf_size)
#define UART_0_TX_BUF_SIZE DT_PROP(UART0_NODE_ID,tbuf_size)

#define UART1_NODE_ID DT_NODELABEL(uart1)
#define UART_1_RX_BUF_SIZE DT_PROP(UART1_NODE_ID,rbuf_size)
#define UART_1_TX_BUF_SIZE DT_PROP(UART1_NODE_ID,tbuf_size)

#define UART2_NODE_ID DT_NODELABEL(uart2)
#define UART_2_RX_BUF_SIZE DT_PROP(UART2_NODE_ID,rbuf_size)
#define UART_2_TX_BUF_SIZE DT_PROP(UART2_NODE_ID,tbuf_size)

/* Set the IRQ callback function pointer and its parameter */
static void uart_airoha_irq_callback_set(const struct device *dev,
                                         uart_irq_callback_user_data_t cb,
                                         void *cb_data)
{
    #ifdef UART_DEBUG_LOG
    printk("uart_airoha_irq_callback_set\r\n");
    #endif
    struct uart_airoha_data *data = (struct uart_airoha_data *)dev->data;
    hal_uart_port_t uart_port = ((struct uart_airoha_cfg*)(dev->config))->uart_port;
    struct uart_config *cfg = &(((struct uart_airoha_cfg*)(dev->config))->uart_config);
    data->irq_cb= cb;
    data->irq_cb_data= cb_data;

    /*malloc buffer*/
    // g_port_buf_cfg[uart_port].tx_buf_size = UART_0_TX_BUF_SIZE;
    g_port_buf_cfg[uart_port].tx_buf_size = 2048;   //openthread special request
    g_port_buf_cfg[uart_port].rx_buf_size = UART_0_RX_BUF_SIZE; //default 512 byte
    g_port_buf_cfg[uart_port].tx_buf_addr = (uint32_t)k_malloc(g_port_buf_cfg[uart_port].tx_buf_size);
    if(!g_port_buf_cfg[uart_port].tx_buf_addr)
    {
        assert(0 && "uart malloc txbuff fail");
    }
    g_port_buf_cfg[uart_port].rx_buf_addr = (uint32_t)k_malloc(g_port_buf_cfg[uart_port].tx_buf_size);
    if(!g_port_buf_cfg[uart_port].tx_buf_addr)
    {
        assert(0 && "uart malloc rxbuff fail");
    }

    /*set dma mode*/
    hal_uart_dma_config_t dma_config;
    dma_config.receive_vfifo_alert_size = 50;
    dma_config.receive_vfifo_buffer = (uint8_t *)(uint32_t *)g_port_buf_cfg[uart_port].rx_buf_addr;
    dma_config.receive_vfifo_buffer_size = g_port_buf_cfg[uart_port].rx_buf_size;
    dma_config.receive_vfifo_threshold_size = ((g_port_buf_cfg[uart_port].rx_buf_size)>>2);
    dma_config.send_vfifo_buffer = (uint8_t *)(uint32_t *)g_port_buf_cfg[uart_port].tx_buf_addr;
    dma_config.send_vfifo_buffer_size = (g_port_buf_cfg[uart_port].tx_buf_size);
    dma_config.send_vfifo_threshold_size = ((g_port_buf_cfg[uart_port].tx_buf_size)>>2);
    hal_uart_set_dma(uart_port, &dma_config);
    hal_uart_register_callback(uart_port, uart_user_callback, (void*)dev);

    /*set flow ctrl*/
    uint8_t flow_ctrl = (cfg->flow_ctrl);
    switch(flow_ctrl)
    {
        case UART_FLOW_CTRL_DISABLE:
            break;
        case UART_HW_FLOW_CTRL_ENABLE:
            break;
        case UART_SW_FLOW_CTRL_ENBALE:
            hal_uart_set_software_flowcontrol(uart_port,0x11,0x13,0x77);
            break;
        default:
            break;
    }
}
#endif /* CONFIG_UART_INTERRUPT_DRIVEN */


#ifdef CONFIG_UART_LINE_CTRL
static void uart_airoha_line_ctrl_set()
{

}

static void uart_airoha_line_ctrl_get()
{
    
}
#endif/*CONFIG_UART_LINE_CTRL*/

static int uart_airoha_init(const struct device *dev)
{
    hal_uart_port_t uart_port;
    uart_port = ((struct uart_airoha_cfg*)(dev->config))->uart_port;
    struct uart_config *cfg = &(((struct uart_airoha_cfg*)(dev->config))->uart_config);

    hal_uart_config_t uart_cfg;
    uart_cfg.baudrate = baudrate_transition_to_airoha(cfg->baudrate);
    uart_cfg.parity = parity_transition_to_airoha(cfg->parity);
    uart_cfg.stop_bit = stop_bits_transition_to_airoha(cfg->stop_bits);
    uart_cfg.word_length = data_bits_transition_to_airoha(cfg->data_bits);
    hal_uart_init(uart_port, &uart_cfg);

    uart_lock_sleep_handle = hal_sleep_manager_set_sleep_handle(uart_lock_sleep_name);
    if (HAL_GPT_STATUS_OK != hal_gpt_sw_get_timer(&gpt_handle) ) {
        //error handler
    }
    #ifdef UART_DEBUG_LOG
    printk("hal_uart_init,%d\r\n", uart_port);
    #endif
    return 0;
}

static const struct uart_driver_api uart_airoha_driver_api = {
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
    .irq_tx_ready = uart_airoha_irq_tx_ready,
    .irq_tx_complete = uart_airoha_irq_tx_complete,

    .irq_rx_enable = uart_airoha_irq_rx_enable,
    .irq_rx_disable = uart_airoha_irq_rx_disable,
    .irq_rx_ready = uart_airoha_irq_rx_ready,

    /* Not support error IRQ */
    .irq_err_enable = NULL,
    .irq_err_disable = NULL,

    .irq_is_pending = uart_airoha_irq_is_pending,
    .irq_update = uart_airoha_irq_update,
    .irq_callback_set = uart_airoha_irq_callback_set,
#endif /* CONFIG_UART_INTERRUPT_DRIVEN */

#ifdef CONFIG_UART_LINE_CTRL
	.line_ctrl_set = uart_airoha_line_ctrl_set,
	.line_ctrl_get = uart_airoha_line_ctrl_ger,
#endif
};


#define UART_AIROHA_DEVICE(id)                                     \
    static struct uart_airoha_cfg uart_airoha_##id##_cfg = {       \
        .uart_config = {                                           \
            .baudrate = (uint32_t)DT_INST_PROP(id, current_speed), \
            .data_bits = (uint8_t)DT_INST_PROP(id, data_bits),     \
            .stop_bits = (uint8_t)DT_INST_PROP(id, stop_bits),     \
            .parity = (uint8_t)DT_INST_PROP(id, parity),           \
            .flow_ctrl = (uint8_t)DT_INST_PROP(id, flow_ctrl),     \
        },                                                         \
        .uart_port = id,                                           \
    };                                                             \
                                                                   \
    static struct uart_airoha_data uart_airoha_##id##_data = {     \
        .irq_cb = NULL,                                            \
        .irq_cb_data = NULL,                                       \
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