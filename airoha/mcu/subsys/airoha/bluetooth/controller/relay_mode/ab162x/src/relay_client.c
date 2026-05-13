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
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/logging/log.h>

#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>


#include "relay_client.h"
#include "hal_uart.h"
#include "memory_attribute.h"
#include "hal_sleep_manager_platform.h"
#include "avm_external.h"
#include "bt_linknode.h"
#include "avm_memory.h"
#include "bt_debug.h"
#include "bt_common_upper_layer.h"
#include "mux.h"
#include <zephyr/logging/log.h>
#define thisMODULE relay_cli
LOG_MODULE_REGISTER(thisMODULE);

/*=======================Macros=======================*/
#define DIRECT_ACCESS_HAL
#define BT_TX_BUF_SIZE 256*10
#define BT_RX_BUF_SIZE 2048*10

//struct k_mutex rx_mutex;
#define MAX_BUFFER_SIZE 512

#define UART_PORT_FOR_RELAY     0x02

#define UART_DMA_RX_BUF_SIZE  1024
#define UART_DMA_TX_BUF_SIZE  3072



#define UART_DEFAULT_BAUDRATE           HAL_UART_BAUDRATE_115200


/*=======================Structures=======================*/

typedef struct {
    uint32_t (*read_data)(uint8_t *buf, uint32_t buf_len, uint32_t offset);/**< Uart port read data function pointer. */
    uint32_t (*write_data)(uint8_t *buf, uint32_t buf_len);                /**< Uart port write data function pointer. */
    uint8_t (*init)(uint8_t port);                                         /**< Uart port init function pointer. */
    uint8_t (*deinit)();                                                   /**< Uart port deinit function pointer. */
} bt_relay_callbacks;


/*=======================Extern Functions=======================*/
extern bool bt_driver_enter_relay_mode(uint8_t port);
//extern void bt_driver_deinit_relay_mode(void);
extern void bt_driver_relay_register_callbacks(void *callback);
extern void bt_driver_handle_relay_port_data(void);

extern void  bt_memory_init_packet(bt_memory_packet_t type, char *buf, uint32_t size);
extern mux_status_t mux_change_port_setting(mux_port_t port, mux_port_setting_t *setting);
extern void log_global_turn_off(void);

/*=======================Functions=======================*/
//atci_status_t atci_cmd_hdlr_bt_relay(atci_parse_cmd_param_t *parse_cmd);

//uint32_t atci_bt_relay_port_service_read_data(uint8_t *buf, uint32_t buf_len, uint32_t offset);
//uint32_t atci_bt_relay_port_service_write_data(uint8_t *buf, uint32_t buf_len);
//uint8_t atci_bt_relay_port_service_init(uint8_t port);
//uint8_t atci_bt_relay_port_service_deinit();



/*=======================Variables=======================*/


//const struct device *uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);
//const struct device *flash_device = DEVICE_DT_GET_OR_NULL(DT_CHOSEN(zephyr_flash_controller));
//const struct device *uart_dev = device_get_binding(DT_NODE_FULL_NAME(DT_NODELABEL(uart0)));
//const struct device *uart_dev;


uint32_t gRelayUartPort = UART_PORT_FOR_RELAY;


#if defined(CONFIG_SOC_SERIES_AB162X)
ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN uint8_t g_rx_vfifo_buffer[UART_DMA_RX_BUF_SIZE];
#else
ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN uint8_t g_rx_vfifo_buffer[UART_DMA_RX_BUF_SIZE];
#endif

ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN uint8_t g_tx_vfifo_buffer[UART_DMA_TX_BUF_SIZE];

#define relay_notify_cb_num_max     (5)
static bt_relay_status_notify_callback_t relay_notify_cbs[relay_notify_cb_num_max] = {0};


//ATTR_ALIGN(4) static char bt_tx_buf[BT_TX_BUF_SIZE];
//ATTR_ALIGN(4) static char bt_rx_buf[BT_RX_BUF_SIZE];
#if 0

const atci_bt_relay_callbacks atci_bt_relay_cb = {
    .read_data = atci_bt_relay_port_service_read_data,
    .write_data = atci_bt_relay_port_service_write_data,
    .init = atci_bt_relay_port_service_init,
    .deinit = atci_bt_relay_port_service_deinit,
};





void relay_client_init(uint32_t uartPort)
{
    BT_LOGI(GROUP_ATCI, "relay_client_init uartPort = %u \n", uartPort);
    gRelayUartPort = uartPort;

    bt_memory_init_packet(BT_MEMORY_TX_BUFFER, bt_tx_buf, BT_TX_BUF_SIZE);
    bt_memory_init_packet(BT_MEMORY_RX_BUFFER, bt_rx_buf, BT_RX_BUF_SIZE);
    atci_cmd_hdlr_bt_relay(NULL);
}



uint32_t atci_bt_relay_port_service_read_data(uint8_t *buf, uint32_t buf_len, uint32_t offset)
{

    //BT_LOGI(GROUP_ATCI, "atci_bt_relay_port_service_read_data buf_len = %d, offset = %d,  buf = 0x%x \n", buf_len, offset, (unsigned int)buf);

    uint32_t get_len = 0;

    #if defined (DIRECT_ACCESS_HAL)

    get_len = hal_uart_receive_dma(gRelayUartPort, buf + offset, buf_len);

    return get_len;

    #else

	if (!uart_irq_update(uart_dev)) {
		return get_len;
	}

	while (uart_irq_rx_ready(uart_dev)) {
		get_len = uart_fifo_read(uart_dev, buf + offset, buf_len);
        //BT_LOGI(GROUP_ATCI, "\n get_len len = %d \n", get_len);
	}
    #endif

    return get_len;

}

uint32_t atci_bt_relay_port_service_write_data(uint8_t *buf, uint32_t buf_len)
{
    BT_LOGI(GROUP_ATCI, "atci_bt_relay_port_service_write_data buf[%d] = %02x %02x %02x %02x \n", buf_len, buf[0],  buf[1],  buf[2],  buf[3] );

    #if defined (DIRECT_ACCESS_HAL)

    uint8_t send_Len = hal_uart_send_dma(gRelayUartPort, buf, buf_len);
    if ( send_Len != buf_len) {
        BT_LOGI(GROUP_ATCI, "send_Len = %d != %d", send_Len, buf_len);
    }
    #else
    uart_fifo_fill(uart_dev, buf, buf_len);
    #endif

    return 0;

}

#if defined (DIRECT_ACCESS_HAL)
void atci_bt_relay_port_service_data_callback(hal_uart_callback_event_t event, void *user_data)
#else
void atci_bt_relay_port_service_data_callback(const struct device *dev, void *user_data)
#endif
{
    //BT_LOGI(GROUP_ATCI, "...\n");
    //BT_LOGI(GROUP_ATCI, "atci_bt_relay_port_service_data_callback \n");
    bt_driver_handle_relay_port_data();
}


uint8_t atci_bt_relay_port_service_init(uint8_t port)
{
    BT_LOGI(GROUP_ATCI, "UART_DEFAULT_BAUDRATE = %d \n", UART_DEFAULT_BAUDRATE);
    BT_LOGI(GROUP_ATCI, "atci_bt_relay_port_service_init port = %d, g_rx_vfifo_buffer = 0x%x , g_tx_vfifo_buffer = 0x%x \n", port, (unsigned int)g_rx_vfifo_buffer, (unsigned int)g_tx_vfifo_buffer);


#ifndef DIRECT_ACCESS_HAL
    uart_dev = device_get_binding(DT_NODE_FULL_NAME(DT_NODELABEL(uart1)));

	if (!device_is_ready(uart_dev)) {
		BT_LOGI(GROUP_ATCI, "UART device not found!\n");
		return SERIAL_PORT_STATUS_UNINITIALIZED;
	}

	/* configure interrupt and callback to receive data */
	 int ret = uart_irq_callback_user_data_set(uart_dev, atci_bt_relay_port_service_data_callback, NULL);
     if (ret < 0) {
         if (ret == -ENOTSUP) {
             BT_LOGI(GROUP_ATCI, "Interrupt-driven UART API support not enabled\n");
         } else if (ret == -ENOSYS) {
             BT_LOGI(GROUP_ATCI, "UART device does not support interrupt-driven API\n");
         } else {
             BT_LOGI(GROUP_ATCI, "Error setting UART callback: %d\n", ret);
         }
         return SERIAL_PORT_STATUS_UNINITIALIZED;
     }

	uart_irq_rx_enable(uart_dev);
    uart_irq_tx_enable(uart_dev);

#else

    // deinit
    hal_uart_deinit(port);

    hal_uart_config_t uart_config;
    hal_uart_dma_config_t dma_config;


    BT_LOGI(GROUP_ATCI, " %d, %d, %d, %d", UART_DEFAULT_BAUDRATE, HAL_UART_PARITY_NONE, HAL_UART_STOP_BIT_1, HAL_UART_WORD_LENGTH_8);

    uart_config.baudrate    = UART_DEFAULT_BAUDRATE;
    uart_config.parity      = HAL_UART_PARITY_NONE;
    uart_config.stop_bit    = HAL_UART_STOP_BIT_1;
    uart_config.word_length = HAL_UART_WORD_LENGTH_8;
    hal_uart_status_t ret = hal_uart_init(port, &uart_config);

    BT_LOGI(GROUP_ATCI, "LINE=%d, ret = %d \n", __LINE__,  ret );

    if (ret != HAL_UART_STATUS_OK) {
        return SERIAL_PORT_STATUS_UNINITIALIZED;
    }

    dma_config.receive_vfifo_alert_size     = 50;
    dma_config.receive_vfifo_buffer         = g_rx_vfifo_buffer;
    dma_config.receive_vfifo_buffer_size    = UART_DMA_RX_BUF_SIZE;
    dma_config.receive_vfifo_threshold_size = 720;
    dma_config.send_vfifo_buffer            = g_tx_vfifo_buffer;
    dma_config.send_vfifo_buffer_size       = UART_DMA_TX_BUF_SIZE;
    dma_config.send_vfifo_threshold_size    = 32;


    BT_LOGI(GROUP_ATCI, "LINE=%d  \n", __LINE__ );

    #if 1
    ret = hal_uart_set_dma(port, &dma_config);

        BT_LOGI(GROUP_ATCI, "LINE=%d, ret = %d \n", __LINE__,  ret );

    if (ret != HAL_UART_STATUS_OK) {
        return SERIAL_PORT_STATUS_UNINITIALIZED;
    }
#endif

    BT_LOGI(GROUP_ATCI, "LINE=%d, ret = %d \n", __LINE__,  ret );


    ret = hal_uart_register_callback(port, atci_bt_relay_port_service_data_callback, NULL);
    if (ret != HAL_UART_STATUS_OK) {

        BT_LOGI(GROUP_ATCI, "LINE=%d, ret = %d \n", __LINE__,  ret );
        return SERIAL_PORT_STATUS_UNINITIALIZED;
    }

    #endif

    BT_LOGI(GROUP_ATCI, "LINE = %d \n", __LINE__ );
    return SERIAL_PORT_STATUS_OK;
}

uint8_t atci_bt_relay_port_service_deinit()
{
    BT_LOGI("Main", "atci_bt_relay_port_service_deinit n");
    return 0;
}



atci_status_t atci_cmd_hdlr_bt_relay(atci_parse_cmd_param_t *parse_cmd)
{
    BT_LOGI("Main", "atci_cmd_hdlr_bt_relay \n");
    bt_driver_relay_register_callbacks((void *)&atci_bt_relay_cb);
    bt_driver_enter_relay_mode(gRelayUartPort);
    BT_LOGI("Main", "en relay result, port is %d \n", gRelayUartPort);
    return ATCI_STATUS_OK;
}

#endif
static mux_handle_t bt_relay_mux_handle = 0;
static mux_port_t bt_relay_mux_port = 0;
#if defined(CONFIG_OPENTHREAD_COPROCESSOR_RCP)
static uint8_t bt_relay_port_buad = HAL_UART_BAUDRATE_921600;
#else
static uint8_t bt_relay_port_buad = HAL_UART_BAUDRATE_115200;
#endif

void bt_relay_set_buad_rate(uint8_t buad_rate)
{
    bt_relay_port_buad = buad_rate;

}

uint8_t bt_relay_mux_deinit()
{
    mux_status_t mux_status = MUX_STATUS_OK;
    if (bt_relay_mux_handle) {
        mux_status = mux_close(bt_relay_mux_handle);
        mux_status = mux_deinit(bt_relay_mux_port);
        bt_relay_mux_handle = 0;
    }
    return mux_status;
}
void bt_relay_mux_callback(mux_handle_t handle, mux_event_t event, uint32_t data_len, void *user_data)
{
    //printf("enter relay rx callback: %s, event: %d, data_len: %d", __FUNCTION__, event, data_len);
    switch (event) {
        case MUX_EVENT_READY_TO_READ: {
            bt_driver_handle_relay_port_data();
        }
        break;
        case MUX_EVENT_READY_TO_WRITE: {

        } break;

        default:
            break;
    }
}

uint32_t bt_relay_mux_send_data(uint8_t *buf, uint32_t buf_len)
{
    uint32_t data_len = 0;
    mux_buffer_t pdata;

    pdata.buf_size = buf_len;
    pdata.p_buf = buf;
    mux_status_t status = MUX_STATUS_OK;
    status = mux_tx(bt_relay_mux_handle, &pdata, 1, &data_len);
    LOG_ERR("bt relay send data status : %d, send_len:%d",status, data_len);
    return data_len;
}

uint32_t bt_relay_mux_read_data(uint8_t *buf, uint32_t buf_len, uint32_t offset)
{
    uint32_t data_len = 0;
    mux_buffer_t buffer;
    buffer.p_buf = buf + offset;
    buffer.buf_size = buf_len;
    mux_status_t status = MUX_STATUS_OK;
    status = mux_rx(bt_relay_mux_handle, &buffer, &data_len);
    LOG_ERR("bt relay read data status : %d, read_len:%d",status, data_len);
    return data_len;
}

static bool bt_is_port_user_opened(uint8_t port, const char *user)
{
    mux_handle_t mux_handle = 0;
    mux_status_t mux_status;
    mux_status = mux_query_user_handle(port, user, &mux_handle);
    if (MUX_STATUS_OK == mux_status && 0 != mux_handle) {
        return true;
    }
    return false;
}
void bt_relay_mux_tx_no_packed_callback(mux_handle_t handle, const mux_buffer_t payload[], uint32_t buffers_counter, mux_buffer_t *head, mux_buffer_t *tail, void *user_data)
{
    head->p_buf = NULL;
    tail->p_buf = NULL;
    head->buf_size = 0;
    tail->buf_size = 0;
}

void bt_relay_mux_rx_no_packed_callback(mux_handle_t  *handle, mux_buffer_t buffers[], uint32_t buffers_counter, uint32_t *consume_len, uint32_t *package_len, void *user_data)
{
    uint32_t total_size, i;
    mux_handle_t p_handle;
    *package_len = 0;
    *consume_len = 0;
    total_size = 0;
    for (i = 0; i < buffers_counter; i++) {
        total_size += buffers[i].buf_size;
    }
    *package_len = total_size;
    if (mux_query_user_handle(bt_relay_mux_port, "HCI_CMD", &p_handle) == MUX_STATUS_OK) {
        *handle = p_handle;
        *consume_len = 0;
    } else {
        //*handle = 0;
        *consume_len = total_size;
        return;
    }
}

static uint8_t bt_close_all_and_reinit(uint8_t port)
{
    mux_port_setting_t setting = {0};
    if (1 == port) {
        setting.tx_buffer_size = 500;
        setting.rx_buffer_size = 500;
    } else {
        setting.tx_buffer_size = 2400;
        setting.rx_buffer_size = 1200;
    }

    setting.dev_setting.uart.uart_config.baudrate = bt_relay_port_buad;
    setting.dev_setting.uart.uart_config.word_length = HAL_UART_WORD_LENGTH_8;
    setting.dev_setting.uart.uart_config.stop_bit = HAL_UART_STOP_BIT_1;
    setting.dev_setting.uart.uart_config.parity = HAL_UART_PARITY_NONE;
    setting.dev_setting.uart.flowcontrol_type = MUX_UART_NONE_FLOWCONTROL;

    mux_protocol_t bt_relay_mux_protocol = {
        .tx_protocol_callback = bt_relay_mux_tx_no_packed_callback,
        .rx_protocol_callback = bt_relay_mux_rx_no_packed_callback,
    };

    uint32_t port_user_count = 0;
    mux_query_port_user_number(port, &port_user_count);
    mux_port_assign_t *port_assign = NULL;
    mux_handle_t handle = 0;
    mux_status_t mux_status;

    if (0 < port_user_count) {
        uint32_t i;
        port_assign = (mux_port_assign_t *)k_malloc(port_user_count * sizeof(mux_port_assign_t));
        mux_query_port_user_name(port, port_assign);
        for (i = 0; i < port_user_count; i++) {
            handle = 0;
            mux_status = mux_query_user_handle(port, port_assign[i].name, &handle);
            if (MUX_STATUS_OK == mux_status) {
                mux_close(handle);
            }
        }
        k_free(port_assign);
        mux_deinit(port);
    }

    mux_status = mux_init(port, &setting, &bt_relay_mux_protocol);

    LOG_ERR("bt_close_all_and_reinit, status:0x%x, port_user_count:%d",mux_status, port_user_count);
    if (MUX_STATUS_OK == mux_status) {
        mux_status = mux_open(port, "HCI_CMD", &bt_relay_mux_handle, bt_relay_mux_callback, NULL);
    }
    return mux_status;
}




uint8_t bt_relay_mux_init(uint8_t port)
{
    mux_status_t mux_status = MUX_STATUS_ERROR;

    bool syslog_on = false;
    bool chg_on = false;
    bool race_on = false;
    uint32_t log = 0;

    mux_port_setting_t setting = {0};
    if (1 == port) {
        setting.tx_buffer_size = 500;
        setting.rx_buffer_size = 500;
    } else {
        setting.tx_buffer_size = 2400;
        setting.rx_buffer_size = 1200;
    }
    setting.dev_setting.uart.uart_config.baudrate = bt_relay_port_buad;
    setting.dev_setting.uart.uart_config.word_length = HAL_UART_WORD_LENGTH_8;
    setting.dev_setting.uart.uart_config.stop_bit = HAL_UART_STOP_BIT_1;
    setting.dev_setting.uart.uart_config.parity = HAL_UART_PARITY_NONE;
    setting.dev_setting.uart.flowcontrol_type = MUX_UART_NONE_FLOWCONTROL;

    syslog_on = bt_is_port_user_opened(port, "SYSLOG");
    chg_on = bt_is_port_user_opened(port, "SM_CHG");
    race_on = bt_is_port_user_opened(port, "RACE_CMD");

    if (syslog_on || chg_on || race_on) {
        log |= 1;
        if (syslog_on) {
            log |= 2;
            extern void syslog_global_turn_off(void);
            syslog_global_turn_off();
        }
        if (chg_on) {
            //bt_relay_is_port_1wire = 1;
        }
        mux_status = mux_change_port_setting(port, &setting);
        LOG_ERR("mux change port setting status is %x",mux_status);
        mux_status = mux_open(port, "HCI_CMD", &bt_relay_mux_handle, bt_relay_mux_callback, NULL);
        LOG_ERR( "mux change open status is %x",mux_status);
    } else {
        /* Note: after race refactor, race don't parse HCI protocol */
        log |= 4;
        mux_status = bt_close_all_and_reinit(port);
        LOG_ERR( "mux change close all and reinit status is %x",mux_status);
    }
    bt_relay_mux_port = port;
#ifndef UART_SLEEP_TRIGGER_ENABLED
    if (port == 1) {
        hal_sleep_manager_lock_sleep(SLEEP_LOCK_UART1);
    } else {
        hal_sleep_manager_lock_sleep(SLEEP_LOCK_UART2);
    }
#endif
    LOG_ERR("bt_relay_mux_init, log:0x%x, status:0x%x",log, mux_status);
    return mux_status;
}

void relay_status_notify_register(bt_relay_status_notify_callback_t cb)
{
    uint32_t index = 0;
    for (index = 0; index < relay_notify_cb_num_max; index ++) {
        if(relay_notify_cbs[index] == 0) {
           relay_notify_cbs[index] = cb;
        }
    }

}

void relay_status_register_notify(bt_relay_status_t status)
{
    uint32_t index = 0;
    for (index = 0; index < relay_notify_cb_num_max; index ++) {
        if (relay_notify_cbs[index] != 0) {
            relay_notify_cbs[index](status);
        }
    }
}


const bt_relay_callbacks bt_relay_cb = {
    .read_data = bt_relay_mux_read_data,
    .write_data = bt_relay_mux_send_data,
    .init = bt_relay_mux_init,
    .deinit = bt_relay_mux_deinit,
};


void relay_client_init(uint8_t uartPort)
{
    LOG_ERR("relay_client_init uartPort = %u \n", uartPort);
    gRelayUartPort = uartPort;

    bt_driver_relay_register_callbacks((void *)&bt_relay_cb);
    bt_driver_enter_relay_mode(uartPort);
    relay_status_register_notify(bt_relay_status_enable);
}


