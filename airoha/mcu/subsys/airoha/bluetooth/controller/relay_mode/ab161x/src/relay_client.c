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
#include "hal_uart_internal.h"

//#include "avm_external.h"
//#include "bt_linknode.h"
//#include "avm_memory.h"
//#include "bt_debug.h"
//#include "bt_common_upper_layer.h"

#include <zephyr/logging/log.h>
#define thisMODULE relay_cli
LOG_MODULE_REGISTER(thisMODULE);

/*=======================Macros=======================*/
#define DIRECT_ACCESS_HAL


//struct k_mutex rx_mutex;

#define UART_PORT_FOR_RELAY     0x02

#define UART_DMA_RX_BUF_SIZE  512
//#define UART_DMA_TX_BUF_SIZE  3072



#define UART_DEFAULT_BAUDRATE           HAL_UART_BAUDRATE_115200


/*=======================Structures=======================*/

typedef struct {
    uint32_t (*read_data)(uint8_t *buf, uint32_t buf_len, uint32_t offset);/**< Uart port read data function pointer. */
    uint32_t (*write_data)(uint8_t *buf, uint32_t buf_len);                /**< Uart port write data function pointer. */
    uint8_t (*init)(uint8_t port);                                         /**< Uart port init function pointer. */
    uint8_t (*deinit)();                                                   /**< Uart port deinit function pointer. */
} atci_bt_relay_callbacks;


/*=======================Extern Functions=======================*/
extern bool bt_driver_enter_relay_mode(uint8_t port);
extern void bt_driver_deinit_relay_mode(void);
extern void bt_driver_relay_register_callbacks(void *callback);
extern void bt_driver_handle_relay_port_data(void);

//extern void  bt_memory_init_packet(bt_memory_packet_t type, char *buf, uint32_t size);

/*=======================Functions=======================*/
atci_status_t atci_cmd_hdlr_bt_relay(atci_parse_cmd_param_t *parse_cmd);

uint32_t atci_bt_relay_port_service_read_data(uint8_t *buf, uint32_t buf_len, uint32_t offset);
uint32_t atci_bt_relay_port_service_write_data(uint8_t *buf, uint32_t buf_len);
uint8_t atci_bt_relay_port_service_init(uint8_t port);
uint8_t atci_bt_relay_port_service_deinit();



/*=======================Variables=======================*/


//const struct device *uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);
const struct device *flash_device = DEVICE_DT_GET_OR_NULL(DT_CHOSEN(zephyr_flash_controller));
//const struct device *uart_dev = device_get_binding(DT_NODE_FULL_NAME(DT_NODELABEL(uart0)));
const struct device *uart_dev;


uint32_t gRelayUartPort = UART_PORT_FOR_RELAY;


#if 0
#if defined(CONFIG_SOC_SERIES_AB162X)
ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN uint8_t g_rx_vfifo_buffer[UART_DMA_RX_BUF_SIZE];
#else 
ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN uint8_t g_rx_vfifo_buffer[UART_DMA_RX_BUF_SIZE];
#endif
#endif

ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN uint8_t *g_rx_vfifo_buffer = NULL;

//ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN uint8_t g_tx_vfifo_buffer[UART_DMA_TX_BUF_SIZE];



const atci_bt_relay_callbacks atci_bt_relay_cb = {
    .read_data = atci_bt_relay_port_service_read_data,
    .write_data = atci_bt_relay_port_service_write_data,
    .init = atci_bt_relay_port_service_init,
    .deinit = atci_bt_relay_port_service_deinit,
};

static uint8_t bt_relay_port_buad = HAL_UART_BAUDRATE_115200;

void bt_relay_set_buad_rate(uint8_t buad_rate)
{
    bt_relay_port_buad = buad_rate;

}

void relay_client_init(uint32_t uartPort)
{   
    //BT_LOGI(GROUP_ATCI, "relay_client_init uartPort = %u \n", uartPort);
    gRelayUartPort = uartPort;
    
    atci_cmd_hdlr_bt_relay(NULL);
}

uint32_t atci_bt_relay_port_service_read_data(uint8_t *buf, uint32_t buf_len, uint32_t offset)
{

    //BT_LOGI(GROUP_ATCI, "atci_bt_relay_port_service_read_data buf_len = %d, offset = %d,  buf = 0x%x \n", buf_len, offset, (unsigned int)buf);
    //printk("atci recice dma data \r\n");
    uint32_t get_len = 0;


    get_len = hal_uart_receive_dma(gRelayUartPort, buf + offset, buf_len);

    return get_len;

   
}

uint32_t atci_bt_relay_port_service_write_data(uint8_t *buf, uint32_t buf_len)
{
    //BT_LOGI(GROUP_ATCI, "atci_bt_relay_port_service_write_data buf[%d] = %02x %02x %02x %02x \n", buf_len, buf[0],  buf[1],  buf[2],  buf[3] );

#if 1
    uint8_t send_Len = hal_uart_send_dma(gRelayUartPort, buf, buf_len);
    if ( send_Len != buf_len) {
        //BT_LOGI(GROUP_ATCI, "send_Len = %d != %d", send_Len, buf_len);
    }
#else
    
    //printk("atci send uart data \r\n");
    hal_uart_send_polling(gRelayUartPort, buf, buf_len);
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

    hal_uart_deinit(port);
    //*(volatile uint32_t *)(0x40003704) = 0x6000000;//uart1 pinmux function gpio 7
    //*(volatile uint32_t *)(0x40003708) = 0x0000006;//uart1 pinmux function gpio 8
    //*(volatile uint32_t *)(0x40003708) = 0x6000000;//uart1 pinmux function gpio 11
    //*(volatile uint32_t *)(0x4000370C) = 0x0060606;//uart1 pinmux function gpio 12
    hal_uart_config_t uart_config;
    hal_uart_dma_config_t dma_config;
    uart_config.baudrate    = bt_relay_port_buad;
    uart_config.parity      = HAL_UART_PARITY_NONE;
    uart_config.stop_bit    = HAL_UART_STOP_BIT_1;
    uart_config.word_length = HAL_UART_WORD_LENGTH_8;
    hal_uart_status_t ret = hal_uart_init(port, &uart_config);

    if (ret != HAL_UART_STATUS_OK) {
        return SERIAL_PORT_STATUS_UNINITIALIZED;
    }
    g_rx_vfifo_buffer = (uint8_t *)k_malloc(UART_DMA_RX_BUF_SIZE);

    dma_config.receive_vfifo_alert_size     = 50;
    dma_config.receive_vfifo_buffer         = g_rx_vfifo_buffer;
    dma_config.receive_vfifo_buffer_size    = UART_DMA_RX_BUF_SIZE;
    dma_config.receive_vfifo_threshold_size = 720;


    ret = hal_uart_set_dma(port, &dma_config);


    if (ret != HAL_UART_STATUS_OK) {
        k_free(g_rx_vfifo_buffer);
        g_rx_vfifo_buffer = NULL;
        return SERIAL_PORT_STATUS_UNINITIALIZED;
    }

    ret = hal_uart_register_callback(port, atci_bt_relay_port_service_data_callback, NULL);
    if (ret != HAL_UART_STATUS_OK) {
        k_free(g_rx_vfifo_buffer);
        g_rx_vfifo_buffer = NULL;
        return SERIAL_PORT_STATUS_UNINITIALIZED;
    }
    
    hal_uart_set_rx_idle_timeout(port,0x0f);

    return SERIAL_PORT_STATUS_OK;
}

uint8_t atci_bt_relay_port_service_deinit()
{
    //BT_LOGI("Main", "atci_bt_relay_port_service_deinit n");
    return 0;
}



atci_status_t atci_cmd_hdlr_bt_relay(atci_parse_cmd_param_t *parse_cmd)
{
    //BT_LOGI("Main", "atci_cmd_hdlr_bt_relay \n");
    printk("atci enter relay \r\n");
    bt_driver_relay_register_callbacks((void *)&atci_bt_relay_cb);
    bt_driver_enter_relay_mode(gRelayUartPort);
    //BT_LOGI("Main", "en relay result, port is %d \n", gRelayUartPort);
    return ATCI_STATUS_OK;
}




