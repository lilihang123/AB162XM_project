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

#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/drivers/uart.h>
#define LOG_LEVEL LOG_LEVEL_DEBUG
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main);

#include "hal_platform.h"
#include "hal_gpt.h"

#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>

#include "memory_attribute.h"

//#include "autoconf.h"
#include "bt_debug.h"

#ifdef CONFIG_AIR_WDT
#include "wdt_airoha.h"
#endif

#define DIRECT_ACCESS_HAL

K_HEAP_DEFINE(test_heap, 32*1024);
K_HEAP_DEFINE_NOCACHE(test_nc_heap, 7*1024);

#include <zephyr/storage/flash_map.h>

#include "memory_attribute.h"

          //  __ASSERT(0xA5 == *dest_u8, "1 byte read test failed at address 0x%08X.", dest_u8);

//relay mode related headers
//#include "atci.h"
//#include "serial_port.h"
//#include "hal_uart.h"
#include "cosim_mdm.h"
#include "cosim_relay_cb.h"



ATTR_RODATA_IN_TCM uint32_t tcm_ro_data = 0x12345678;
ATTR_RWDATA_IN_TCM uint32_t tcm_rw_data = 0x87654321;
ATTR_ZIDATA_IN_TCM uint32_t tcm_zi_data;

#if !defined(CONFIG_SOC_SERIES_AB162X)
ATTR_RWDATA_IN_NONCACHED_SYSRAM uint32_t nc_sram_rw_data = 0xA5A5A5A5;
ATTR_ZIDATA_IN_NONCACHED_SYSRAM uint32_t nc_sram_zi_data;
#endif

ATTR_SHARE_RWBT uint32_t sram_bt_rw_data = 0x11223344;
ATTR_SHARE_ZIBT_16BYTE_ALIGN uint32_t sram_bt_zi_data;

void feed_watch_dog(void);
void relay_init();


//const struct device *uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);
const struct device *flash_device = DEVICE_DT_GET_OR_NULL(DT_CHOSEN(zephyr_flash_controller));
//const struct device *uart_dev = device_get_binding(DT_NODE_FULL_NAME(DT_NODELABEL(uart0)));
const struct device *uart_dev;

//struct k_mutex rx_mutex;
#define MAX_BUFFER_SIZE 512



#define UART_DMA_RX_BUF_SIZE  1024
#define UART_DMA_TX_BUF_SIZE  1024

#if defined(CONFIG_SOC_SERIES_AB162X)
ATTR_ALIGN(0x04000000) ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN uint8_t g_rx_vfifo_buffer[UART_DMA_RX_BUF_SIZE];
#else 
ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN uint8_t g_rx_vfifo_buffer[UART_DMA_RX_BUF_SIZE];
#endif

ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN uint8_t g_tx_vfifo_buffer[UART_DMA_TX_BUF_SIZE];

static uint8_t g_rx_buf[MAX_BUFFER_SIZE] = {0};
static uint16_t g_rx_buf_wIdx = 0; 
static uint16_t g_rx_buf_rIdx = 0; 

typedef struct {
    uint8_t cmd_type;
    uint16_t cmd_id;
    uint8_t payload_len;
    uint8_t payload[1];
}__attribute__((packed)) T_HCI_CMD_S;


typedef struct {
    uint8_t packet_type;
    uint8_t event_id;    
    uint8_t total_len;
    uint8_t num_hci_command_packets;
    uint16_t rsp_cmd_id;
    uint8_t status;
    uint8_t payload[1];
}__attribute__((packed)) T_HCI_EVENT_S;



#define MIN_LEN     (sizeof(T_HCI_CMD_S)-1)
#define HCI_CMD     0x01

#define UART_PORT_FOR_RELAY     0x02




/** Vol 4: Table 2.1: HCI packet indicators*/
typedef enum {
    HCI_COMMAND_PKT, 
    HCI_ACL_DATA_PKT, 
    HCI_SYNCHRONOUS_DATA_PKT, 
    HCI_EVENT_PKT,
    HCI_ISO_DATA_PKT
}HCI_PACKET_TYPE;


int app_hci_cmd_parser(bool is_debug);


/*
 * Read characters from UART until line end is detected. Afterwards push the
 * data to the message queue.
 */
void app_uart_irq_cb(const struct device *dev, void *user_data)
{
	if (!uart_irq_update(uart_dev)) {
		return;
	}
	
    //printk( "app_uart_irq_cb.2");
	while (uart_irq_rx_ready(uart_dev)) {

        if (g_rx_buf_rIdx > (MAX_BUFFER_SIZE >>1) ){            
            BT_LOGI("Main", "move  %d bytes from  %d to head \n", g_rx_buf_wIdx - g_rx_buf_rIdx, g_rx_buf_wIdx );
            // move data to head
            if (g_rx_buf_wIdx - g_rx_buf_rIdx)
                memcpy(&g_rx_buf[0], &g_rx_buf[g_rx_buf_rIdx],  g_rx_buf_wIdx - g_rx_buf_rIdx);

            g_rx_buf_wIdx -= g_rx_buf_wIdx;
            g_rx_buf_rIdx = 0;
             BT_LOGI("Main", "g_rx_buf_wIdx = %d, g_rx_buf_rIdx = %d\n", g_rx_buf_wIdx , g_rx_buf_rIdx );
        }
        
		uint32_t get_len = uart_fifo_read(uart_dev, &g_rx_buf[g_rx_buf_wIdx], MAX_BUFFER_SIZE);
        BT_LOGI("Main", "\n uart_fifo_read len = %d \n", get_len);
		if (get_len>0)
		{
            get_len =  app_hci_cmd_parser(true);
            g_rx_buf_wIdx += get_len;

            if (g_rx_buf_wIdx < g_rx_buf_rIdx) {

            }
		}		
	}
}

uint32_t uart_get_buffer(uint8_t *buf, uint32_t length)
{	
	//return hal_uart_receive_dma(DA_UART_PORT, buf, length);
	return 0;//not use
}

void uart_put_buffer(uint8_t *buf, uint32_t length)
{
    #if 0 
    BT_LOGI("Main", "uart_poll_out.1 %d\n", length);
    for(int i=0;i<length;++i)
    {
        uart_poll_out(uart_dev, buf[i]);
    }
    #else 
    BT_LOGI("Main", "uart_poll_out.2 %d\n", length);
    uart_fifo_fill(uart_dev, buf, length);
    #endif
}


void app_send_hci_cmd_complete_rsp(uint16_t cmd_id, uint8_t status, uint8_t* payload, uint8_t payload_len)
{
    T_HCI_EVENT_S* event =  k_malloc(sizeof(T_HCI_EVENT_S) - 1 + payload_len);; 

    event->packet_type = HCI_EVENT_PKT;
    event->event_id=0x0e; //hci command  complete 
    event->total_len = sizeof(T_HCI_EVENT_S) - 1 + payload_len;
    event->num_hci_command_packets =1;
    event->rsp_cmd_id = cmd_id;
    event->status = status;

    if (payload && payload_len){
        memcpy( event->payload, payload, payload_len);
    }

    uart_put_buffer((uint8_t*)event, sizeof(T_HCI_EVENT_S) - 1 + payload_len );
}


void app_hci_cmd_handler(T_HCI_CMD_S* hci_cmd)
{
    switch( hci_cmd->cmd_id )
    {
        case 0x0C03:
        BT_LOGI("Main", "HCI reset \n");      
        app_send_hci_cmd_complete_rsp(hci_cmd->cmd_id, 0, NULL, 0); 
        break; 

        case 0x1009: 
        BT_LOGI("Main", "GET BD ADDR \n");
        uint8_t addr[] = {0,1,2,3,4,5};
        app_send_hci_cmd_complete_rsp(hci_cmd->cmd_id, 0, addr, sizeof(addr));
        break; 

        default:
            BT_LOGI("Main", "Unknow HCI cmd \n");
    }
}


int app_hci_cmd_parser(bool is_debug)
{
    uint16_t len = ( g_rx_buf_wIdx >  g_rx_buf_rIdx )? g_rx_buf_wIdx -  g_rx_buf_rIdx : MAX_BUFFER_SIZE - g_rx_buf_rIdx + g_rx_buf_wIdx ; ;
    T_HCI_CMD_S* hci_cmd = NULL;

    if (len < MIN_LEN)
        return 0;

    BT_LOGI("Main", "app_hci_cmd_parser g_rx_buf_rIdx = %d, g_rx_buf_wIdx = %d \n", g_rx_buf_rIdx, g_rx_buf_wIdx );

    // find head
    bool bFindHead = false;
    do
    {
        len = ( g_rx_buf_wIdx >  g_rx_buf_rIdx )? g_rx_buf_wIdx -  g_rx_buf_rIdx : MAX_BUFFER_SIZE - g_rx_buf_rIdx + g_rx_buf_wIdx ;                
        BT_LOGI("Main", "Do len=%d, data = 0x%02x-%02x-%02x-%02x \n", len , g_rx_buf[g_rx_buf_rIdx+0], g_rx_buf[g_rx_buf_rIdx+1], g_rx_buf[g_rx_buf_rIdx+2], g_rx_buf[g_rx_buf_rIdx+3] );

        if (g_rx_buf[g_rx_buf_rIdx] != HCI_CMD) // not find HCI_CMD
        {
            g_rx_buf_rIdx++;

        }
        else    //find HCI_CMD
        {
            hci_cmd = (T_HCI_CMD_S*)&g_rx_buf[g_rx_buf_rIdx];
            BT_LOGI("Main", "cmd_id = 0x%X,  Payload_len = %d \n", hci_cmd->cmd_id, hci_cmd->payload_len);
            
            if (len >= hci_cmd->payload_len + MIN_LEN){
                g_rx_buf_rIdx += (hci_cmd->payload_len + MIN_LEN );
                bFindHead = true;
                break;                 
            }
            else {
                g_rx_buf_rIdx++;
            }
        }
    }while (len >= MIN_LEN);
    
   BT_LOGI("Main", "bFindHead = %d \n", bFindHead);

    // check len
    if (bFindHead && hci_cmd)
    {
        BT_LOGI("Main", "cmd id = 0x%x, payload len = %d, payload = 0x%02x-%02x-%02x-%02x \r\n", hci_cmd->cmd_id, hci_cmd->payload_len, hci_cmd->payload[0], hci_cmd->payload[1], hci_cmd->payload[2], hci_cmd->payload[3] ); 

        app_hci_cmd_handler(hci_cmd);

        return hci_cmd->payload_len + MIN_LEN;
    }
    
    return 0;
}


int read_uart()
{
    int err;
    while(1)
    {
        err = uart_poll_in(uart_dev, &g_rx_buf[g_rx_buf_wIdx]);

        if (err == 0){
            BT_LOGI("Main", "g_rx_buf[%d] = 0x%x",g_rx_buf_wIdx,  g_rx_buf[g_rx_buf_wIdx]);
            g_rx_buf_wIdx++;
        }
        else if (err == -1){
            //no data
            return 0;
        }
        else{
            return err;
        }
    }

    //pool full
    return 1;
}


void uart_init()
{

}

#define BT_TX_BUF_SIZE 256*10
#define BT_RX_BUF_SIZE 2048*10

ATTR_ALIGN(4) static char tx_buf[BT_TX_BUF_SIZE];
ATTR_ALIGN(4) static char rx_buf[BT_RX_BUF_SIZE];
#include "bt_system.h"

void upper_layer_init()
{   
    bt_memory_init_packet(BT_MEMORY_TX_BUFFER, tx_buf, BT_TX_BUF_SIZE);
    bt_memory_init_packet(BT_MEMORY_RX_BUFFER, rx_buf, BT_RX_BUF_SIZE);
}


void print_live(uint32_t interval)
{
   	uint32_t time_stamp_32 = k_uptime_get_32();
	uint32_t milliseconds_spent = 0;
	while (1)
	{
		milliseconds_spent = k_uptime_get_32() - time_stamp_32;
		
		if (milliseconds_spent>=interval)
		{
            BT_LOGI("Main", "Date : 0430_1011...\n");
			time_stamp_32 = k_uptime_get_32();
		}
	}
}


int main(void)
{
    // DONT MOVE!! cosim error ignore messages
    MDM_TM_PRINTF("SIM_LOG_IGNORE: ErrorCode");
    MDM_TM_PRINTF("SIM_LOG_IGNORE: ErrCode");

    BT_LOGI("Main", "Multi thread environment with board %s\r\n", CONFIG_BOARD);

    upper_layer_init();
    BT_LOGI("Main", "upper_layer_init Completed \n");

    relay_init();
    BT_LOGI("Main", "=========== Relay Mode Init Completed ===========\n");



    extern void bt_driver_handle_relay_port_data(void);
    while(1){
        //MDM_TM_PRINTF("bt_driver_handle_relay_port_data");
        bt_driver_handle_relay_port_data();
    };

    //print_live(8000);
    return 0;
}


void feed_watch_dog(void)
{
#ifdef CONFIG_AIR_WDT
    const struct device *wdt_dev = \
        device_get_binding(DT_LABEL(DT_NODELABEL(wdt0)));
    if(wdt_dev != NULL){
        int wdt_ch = ((wdt_air_config_t*)(wdt_dev->config))->wdt_channel;
        BT_LOGI("Main", "wdt_feed was called with dev: 0x%08X and channel %d\r\n", (unsigned int)wdt_dev, wdt_ch);
        wdt_feed(wdt_dev, wdt_ch);
    }
#endif
}













typedef struct {
    uint32_t (*read_data)(uint8_t *buf, uint32_t buf_len, uint32_t offset);/**< Uart port read data function pointer. */
    uint32_t (*write_data)(uint8_t *buf, uint32_t buf_len);                /**< Uart port write data function pointer. */
    uint8_t (*init)(uint8_t port);                                         /**< Uart port init function pointer. */
    uint8_t (*deinit)();                                                   /**< Uart port deinit function pointer. */
} atci_bt_relay_callbacks;

//static uint32_t atci_bt_port_service_relay_port_handle = 0;
//static uint8_t atci_bt_port_service_usb_init_success = 0;

extern bool bt_driver_enter_relay_mode(uint8_t port);
extern void bt_driver_deinit_relay_mode(void);
extern void bt_driver_handle_relay_port_data(void);
extern void bt_driver_relay_register_callbacks(void *callback);


uint32_t atci_bt_relay_port_service_read_data(uint8_t *buf, uint32_t buf_len, uint32_t offset);
uint32_t atci_bt_relay_port_service_write_data(uint8_t *buf, uint32_t buf_len);
uint8_t atci_bt_relay_port_service_init(uint8_t port);
uint8_t atci_bt_relay_port_service_deinit();

const atci_bt_relay_callbacks atci_bt_relay_cb = {
    .read_data = cosim_relay_mux_read_data,
    .write_data = cosim_relay_mux_send_data,
    .init = cosim_relay_mux_init,
    .deinit = cosim_relay_mux_deinit,
};

void relay_init()
{   
    //extern atci_status_t atci_cmd_hdlr_bt_relay(atci_parse_cmd_param_t *parse_cmd);
    //#include "atci.h"
    //atci_cmd_hdlr_bt_relay(NULL);
    bt_driver_relay_register_callbacks((void *)&atci_bt_relay_cb);
    bool result = bt_driver_enter_relay_mode(UART_PORT_FOR_RELAY);
    if (result == true) {
        /* BT enter relay mode successed. */
        BT_LOGI("Main", "[BT]enable relay mode success!!!");
    } else {
        /* BT enter relay mode failed. */
        BT_LOGI("Main", "[BT]enable relay mode fail!!!");
    }

}


uint32_t atci_bt_relay_port_service_read_data(uint8_t *buf, uint32_t buf_len, uint32_t offset)
{
#if 0
    #if 0
    assert(buf && buf_len && atci_bt_port_service_relay_port_handle);
    serial_port_read_data_t read_data;
    read_data.buffer = (uint8_t *)(buf + offset);
    read_data.size = buf_len - offset;
    bt_os_layer_serial_port_control((uint32_t)atci_bt_port_service_relay_port_handle, (uint8_t)SERIAL_PORT_CMD_READ_DATA, (void *)&read_data);
    return read_data.ret_size;
    #endif

    BT_LOGI(GROUP_ATCI, "atci_bt_relay_port_service_read_data buf_len = %d, offset = %d,  buf = 0x%x \n", buf_len, offset, (unsigned int)buf);

    uint32_t get_len = 0;

    #if defined (DIRECT_ACCESS_HAL) 

    get_len = hal_uart_receive_dma(UART_PORT_FOR_RELAY, buf + offset, buf_len);

    return get_len;

    #else 

	if (!uart_irq_update(uart_dev)) {
		return get_len;
	}
	
	while (uart_irq_rx_ready(uart_dev)) {
		get_len = uart_fifo_read(uart_dev, buf + offset, buf_len);
        BT_LOGI(GROUP_ATCI, "\n get_len len = %d \n", get_len);
	}
    #endif

    return get_len;
#else
    return 0;
#endif
    
}

uint32_t atci_bt_relay_port_service_write_data(uint8_t *buf, uint32_t buf_len)
{
#if 0
    #if 0
    assert(buf && buf_len && atci_bt_port_service_relay_port_handle);
    serial_port_write_data_t write_data;
    write_data.data = buf;
    write_data.size = buf_len;
    bt_os_layer_serial_port_control((uint32_t)atci_bt_port_service_relay_port_handle, (uint8_t)SERIAL_PORT_CMD_WRITE_DATA_BLOCKING, &write_data);
    return write_data.ret_size;
    #endif

    BT_LOGI(GROUP_ATCI, "atci_bt_relay_port_service_write_data buf[%d] = %02x %02x %02x %02x \n", buf_len, buf[0],  buf[1],  buf[2],  buf[3] );

    #if defined (DIRECT_ACCESS_HAL) 

    uint8_t send_Len = hal_uart_send_dma(UART_PORT_FOR_RELAY, buf, buf_len);
    if ( send_Len != buf_len) {
        BT_LOGI(GROUP_ATCI, "send_Len = %d != %d", send_Len, buf_len);
    }
    #else 
    uart_fifo_fill(uart_dev, buf, buf_len);
    #endif
#endif

    return 0;

}

#if 0
#if defined (DIRECT_ACCESS_HAL)
void atci_bt_relay_port_service_data_callback(hal_uart_callback_event_t event, void *user_data)
#else
void atci_bt_relay_port_service_data_callback(const struct device *dev, void *user_data)
#endif
{
    #if 0
    //uint32_t current_read_size = 0;
    //serial_port_read_data_t read_data;
    //serial_port_status_t status = SERIAL_PORT_STATUS_FAIL;
    switch (event) {
        case SERIAL_PORT_EVENT_READY_TO_READ: {
            bt_driver_handle_relay_port_data();
            break;
        }
        case SERIAL_PORT_EVENT_BT_CONNECTION: {
            atci_bt_port_service_usb_init_success = 1;
            break;
        }
        case SERIAL_PORT_EVENT_READY_TO_WRITE: {
            break;
        }
        default:
            break;
    }
    #else 

    BT_LOGI(GROUP_ATCI, "...\n");
    BT_LOGI(GROUP_ATCI, "atci_bt_relay_port_service_data_callback \n");
    bt_driver_handle_relay_port_data();
    #endif
}
#endif


uint8_t atci_bt_relay_port_service_init(uint8_t port)
{
    #if 0
    serial_port_status_t status;
    serial_port_open_para_t serial_port_open_para;
    serial_port_setting_uart_t uart_setting;
    serial_port_setting_uart_t default_uart_setting;
    uint8_t pollPeriod = 1;
    uint32_t timer = 0;

    if ((serial_port_dev_t)port >= SERIAL_PORT_DEV_MAX) {
        return SERIAL_PORT_STATUS_FAIL;
    }
    if (g_atci_uart_port == (hal_uart_port_t)port) {
        LOG_MSGID_I(atci_bt, "relay mode use atci port", 0);
        atci_deinit(g_atci_uart_port);
    }

    if (atci_bt_port_service_relay_port_handle) {
        serial_port_status_t status = bt_os_layer_serial_port_close((uint32_t)atci_bt_port_service_relay_port_handle);
        if (status != SERIAL_PORT_STATUS_OK) {
            return SERIAL_PORT_STATUS_OK;
        }
    }
    uart_setting.baudrate = atci_bt_relay_port_buad;
    serial_port_status_t read_ret = serial_port_config_read_dev_setting(port, (serial_port_dev_setting_t *)&default_uart_setting);
    serial_port_config_write_dev_setting(port, (serial_port_dev_setting_t *)&uart_setting);
    // register the serial user event callback
    serial_port_open_para.callback = atci_bt_relay_port_service_data_callback;
    serial_port_open_para.tx_buffer_size = 1024;
    serial_port_open_para.rx_buffer_size = 1024;
    // for serial port configuration
    status = bt_os_layer_serial_port_open((uint16_t)port, (void *)&serial_port_open_para, (uint32_t *)&atci_bt_port_service_relay_port_handle);
    if (status == SERIAL_PORT_STATUS_UNINITIALIZED) {
        status = SERIAL_PORT_STATUS_OK;
        while (!atci_bt_port_service_usb_init_success) {
            bt_os_layer_sleep_task(pollPeriod);
            timer += pollPeriod;
            if (timer >= 1000) {
                status = SERIAL_PORT_STATUS_FAIL;
                break;
            }
        }
    } else if (status == SERIAL_PORT_STATUS_OK) {
        status = SERIAL_PORT_STATUS_OK;
    } else {
        status = SERIAL_PORT_STATUS_FAIL;
    }
    if (read_ret == SERIAL_PORT_STATUS_OK) {
        serial_port_config_write_dev_setting(port, (serial_port_dev_setting_t *)&default_uart_setting);
    }

    return status;
    #endif 

    BT_LOGI(GROUP_ATCI, "...\n");
    BT_LOGI(GROUP_ATCI, "atci_bt_relay_port_service_init port = %d, g_rx_vfifo_buffer = 0x%x , g_tx_vfifo_buffer = 0x%x \n", port, (unsigned int)g_rx_vfifo_buffer, (unsigned int)g_tx_vfifo_buffer);


#if 0 
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


    BT_LOGI(GROUP_ATCI, " %d, %d, %d, %d", HAL_UART_BAUDRATE_921600, HAL_UART_PARITY_NONE, HAL_UART_STOP_BIT_1, HAL_UART_WORD_LENGTH_8);

    uart_config.baudrate    = HAL_UART_BAUDRATE_921600;
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
#else
    return 0;
#endif
}

uint8_t atci_bt_relay_port_service_deinit()
{
    #if 0
    serial_port_status_t status = SERIAL_PORT_STATUS_OK;
    if (atci_bt_port_service_relay_port_handle) {
        status = serial_port_close(atci_bt_port_service_relay_port_handle);
        atci_bt_port_service_relay_port_handle = 0;
    }
    return (uint8_t)status;
    #else 
    BT_LOGI("Main", "atci_bt_relay_port_service_deinit n");
    return 0;
    #endif
}

#if 0
atci_status_t atci_cmd_hdlr_bt_relay(atci_parse_cmd_param_t *parse_cmd)
{
    #if 0
    uint8_t port = *((uint8_t *)parse_cmd->string_ptr + 9) - '0';

    bt_driver_relay_register_callbacks((void *)&atci_bt_relay_cb);
    result = bt_driver_enter_relay_mode(port);
    LOG_MSGID_I(atci_bt, "en relay result, result: %d port is %d", 2, result,port);
    bt_power_on_set_config_type(BT_POWER_ON_RELAY);
    vPortFree(output);
    return ATCI_STATUS_OK;
    #else 
    BT_LOGI("Main", "atci_cmd_hdlr_bt_relay \n");
    bt_driver_relay_register_callbacks((void *)&atci_bt_relay_cb);
    bool result = bt_driver_enter_relay_mode(UART_PORT_FOR_RELAY);
    BT_LOGI("Main", "en relay result, result: %d port is %d \n", result,UART_PORT_FOR_RELAY);
    return ATCI_STATUS_OK;
    #endif
}
#endif








