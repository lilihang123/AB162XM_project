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
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include "zephyr/sys/__assert.h"
#include <zephyr/bluetooth/buf.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/hci_raw.h>
#include <zephyr/net/buf.h>
//#include <zephyr/subsys/bluetooth/host/hci_core.h>
//#include <zephyr/include/zephyr/drivers/bluetooth.h>
//#include "zephyr/include/zephyr/bluetooth/buf.h"
#include <zephyr/drivers/bluetooth.h>
#include <zephyr/sys/byteorder.h>

//#include <zephyr/subsys/bluetooth/host/hci_core.h>

//#include "avm_external.h"
//#include "bt_linknode.h"
//#include "avm_memory.h"
//#include "bt_debug.h"
//#include "bt_common_upper_layer.h"
//#include "avm_external.h"
#include "memory_attribute.h"
//#include "bt_hci_log.h"

#include <zephyr/logging/log.h>
#include <zephyr/drivers/entropy.h>
#include "nvkey.h"
#include "nvkey_id_def.h"
#include "air_version.h"

#define thisMODULE btd_relay
LOG_MODULE_REGISTER(thisMODULE);

#define HCI_FROM_HOST         0
#define HCI_FROM_CONTROLLER   1

#define BT_HCI_DEV  DT_CHOSEN(zephyr_bt_hci)

struct bt_dev {
	const struct device *hci;
};

struct bt_dev bt_relay_dev = {
#if DT_HAS_CHOSEN(zephyr_bt_hci)
        .hci = DEVICE_DT_GET(BT_HCI_DEV),
#endif
};


NET_BUF_POOL_DEFINE(relay_pool, 2,256, 0, NULL);

extern int bt_send(struct net_buf *buf);
typedef struct {
    uint32_t (*read_data)(uint8_t *buf, uint32_t buf_len, uint32_t offset);/**< Uart port read data function pointer. */
    uint32_t (*write_data)(uint8_t *buf, uint32_t buf_len);                /**< Uart port write data function pointer. */
    uint8_t (*init)(uint8_t port);                                         /**< Uart port init function pointer. */
    uint8_t (*deinit)(void);                                               /**< Uart port deinit function pointer. */
} bt_driver_relay_callbacks;

typedef uint16_t bt_hci_cmd_op_t;
typedef uint8_t bt_data_t[1];
typedef uint8_t bt_uart_t;
typedef uint8_t bt_hci_evt_op_t;

#define BT_UART_CMD     0x01
#define BT_UART_ACL     0x02
#define BT_UART_EVT     0x04
typedef uint8_t bt_uart_t;


#define BT_HCI_ACL_HEADER_LENGTH       5  //sizeof(bt_uart_t) + sizeof(bt_hci_packet_acl_t) - 1
#define BT_HCI_CMD_HEADER_LENGTH       4  //sizeof(bt_uart_t) + sizeof(bt_hci_Packet_cmd_t) - 1
//#define BT_HCI_EVT_HEADER_LENGTH       3  //sizeof(bt_uart_t) + sizeof(bt_hci_Packet_evt_t) - 1
//#define BT_HCI_L2CAP_HEADER_LENGTH     4  //sizeof(bt_l2cap_cmd_t) -1

//#define BT_HCI_PACKET_ACL_SIZE(p)   ((*(uint16_t *)((uint8_t *)(p)+3))+BT_HCI_ACL_HEADER_LENGTH)
#define BT_HCI_PACKET_CMD_SIZE(p)   ((*(uint8_t *)((uint8_t *)(p)+3))+BT_HCI_CMD_HEADER_LENGTH)
//#define BT_HCI_PACKET_EVT_SIZE(p)   ((*(uint8_t *)((uint8_t *)(p)+2))+BT_HCI_EVT_HEADER_LENGTH)

/**
 *  @brief      HCI command packet. Please refer to core spec 5.4.1 HCI Command Packet.
 */

typedef struct {
    bt_hci_cmd_op_t     cmd_code; /**< Command code */
    uint8_t             length;   /**< Length of all of the parameters contained in this packet */
    bt_data_t           param;     /**< Parameters */
}__packed bt_hci_packet_cmd_t;

/**
 *  @brief      HCI event packet. Please refer to core spec 5.4.4 HCI Event Packet.
 */

typedef struct {
    bt_hci_evt_op_t     evt_code; /**< Event code */
    uint8_t             length;   /**< Length of all of the parameters contained in this packet */
    bt_data_t           param;    /**< Parameters */
}__packed bt_hci_packet_evt_t;

/**
 *  @brief      HCI ACL packet. Please refer to core spec, Please refer to core spec 5.4.2 HCI ACL Data Packets.
 */

typedef struct {
    uint16_t    handle: 12; /**< Handle */
    uint16_t    pb_flag: 2; /**< Packet boundary flag */
    uint16_t    bc_flag: 2; /**< Broadcast flag */
    uint16_t    length;     /**< Data total length */
    bt_data_t   data;       /**< Data */
}__packed bt_hci_packet_acl_t;

typedef struct {
    bt_uart_t   indicator;                  /**< Indicate packet is CMD, ACL or EVT */
    union {
        bt_hci_packet_acl_t acl; /**< ACL packet */
        bt_hci_packet_cmd_t cmd; /**< Command packet */
        bt_hci_packet_evt_t evt; /**< Event packet */
    };
}__packed bt_hci_le_packet_t;


extern void bt_driver_deinit_relay_mode(void);

static uint8_t bt_driver_relay_enabled = 0;
static uint8_t bt_driver_relay_enable_complete = 0;
#define RELAY_BUFFER_SIZE 512
//static uint8_t bt_driver_relay_rx_buf[RELAY_BUFFER_SIZE] = {0};

//static uint8_t bt_driver_relay_tx_buf[256] = {0};


static uint8_t *bt_driver_relay_tx_buf = NULL;
static uint8_t *bt_driver_relay_rx_buf = NULL;

uint8_t bt_driver_relay_event_handle(struct net_buf *buf);

uint8_t *bt_driver_get_relay_tx_buffer(void)
{

    return bt_driver_relay_tx_buf;
}


bool bt_driver_enter_relay_mode(uint8_t port);

static K_THREAD_STACK_DEFINE(trx_thread_stack, 768);
static struct k_thread trx_thread_data;
static K_FIFO_DEFINE(trx_queue);

#if 0
bool bt_driver_is_relay_mode_enabled(void)
{
    return (bt_driver_relay_enabled == 1);
}

bool bt_driver_is_relay_mode_enable_complete(void)
{
    return (bt_driver_relay_enable_complete == 1);
}
#endif
bt_driver_relay_callbacks bt_driver_relay_cb;

void bt_driver_relay_register_callbacks(void *callback)
{
    
    //BT_LOGI("BT","bt_driver_relay_register_callbacks \n");
    memcpy(&bt_driver_relay_cb, (bt_driver_relay_callbacks *)callback, sizeof(bt_driver_relay_callbacks));
  
    //BT_LOGI("BT","init @ 0x%x, read_data @ 0x%x, write_data @ 0x%x,  \n", (unsigned int)bt_driver_relay_cb.init, (unsigned int)bt_driver_relay_cb.read_data, (unsigned int)bt_driver_relay_cb.write_data);
}

//#define BT_HCI_PACKET_ACL_SIZE_2(p)   (*(uint16_t *)((uint8_t *)(p)+2)+BT_HCI_ACL_HEADER_LENGTH)
//#define BT_HCI_PACKET_CMD_SIZE_2(p)   (*(uint8_t *)((uint8_t *)(p)+2)+BT_HCI_CMD_HEADER_LENGTH)


static uint32_t g_exist_data_len = 0;
void bt_driver_handle_relay_port_data(void)
{
    uint32_t current_data_len = g_exist_data_len + 
        bt_driver_relay_cb.read_data(bt_driver_relay_rx_buf, (RELAY_BUFFER_SIZE - g_exist_data_len), g_exist_data_len);
    uint32_t send_out_len = 0;

    while (current_data_len > 0) {
        uint32_t bt_buf_type = 0;
        uint32_t payload_size = 0;
        bt_hci_le_packet_t *packet = (bt_hci_le_packet_t *)(bt_driver_relay_rx_buf + send_out_len);
        if (packet->indicator == BT_UART_CMD) {
            if (current_data_len < BT_HCI_CMD_HEADER_LENGTH) {
                /* cmd header incomplete */
                break;
            }
            payload_size = BT_HCI_PACKET_CMD_SIZE(packet);
            bt_buf_type = BT_BUF_CMD;
        } else if (packet->indicator == BT_UART_ACL) {
            if (current_data_len < BT_HCI_ACL_HEADER_LENGTH) {
                /* Acl header incomplete */
                break;
            }
            payload_size = packet->acl.length + BT_HCI_ACL_HEADER_LENGTH;
            bt_buf_type = BT_BUF_ACL_OUT;
        } else {
            printk("Unknown packet type!!! \r\n");
            break;
        }
        if (current_data_len < payload_size) {
            /* HCI packet incomplete */
            break;
        }
        struct net_buf *buf = net_buf_alloc(&relay_pool, K_FOREVER);
        if (NULL == buf) {
            printk("Failed to get CMD TX buffer \r\n");
            break;
        }
        net_buf_reserve(buf, BT_BUF_RESERVE);
        bt_buf_set_type(buf, bt_buf_type);
        net_buf_add_mem(buf, &(packet->cmd), payload_size - 1);
        net_buf_put(&trx_queue, buf);
        current_data_len -= payload_size;
        send_out_len += payload_size;
    }
    if (current_data_len != 0 && send_out_len != 0) {
        /* Move the remain data to the buffer head. */
        memcpy(bt_driver_relay_rx_buf, bt_driver_relay_rx_buf + send_out_len, current_data_len);
    }
    if (current_data_len != 0) {
        printk("There are remain data %d at %d\r\n", current_data_len, send_out_len);
    }
    g_exist_data_len = current_data_len;
}

int bt_hci_relay_recv(const struct device *dev, struct net_buf *buf)
{
	//printk("buf %p len %u \r\n", buf, buf->len);
    //printk("recv data \r\n");

    //bt_driver_relay_event_handle(buf);
    net_buf_put(&trx_queue, buf);
	return 0;
}

static void trx_thread(void *p1, void *p2, void *p3)
{
	while (1) {
		struct net_buf *buf = NULL;
        enum bt_buf_type buf_type = 0;

		/* Wait until a buffer is available */
		buf = net_buf_get(&trx_queue, K_FOREVER);
        buf_type = bt_buf_get_type(buf);
        if (BT_BUF_EVT == buf_type || BT_BUF_ACL_IN == buf_type) {
            /* Relay HCI event and ACL in data to the upper tester. */
            bt_driver_relay_event_handle(buf);
        } else {
            /* Pass buffer to the stack */
            int err = bt_send(buf);
            if (err) {
                printk("Unable to send (err %d)", err);
                net_buf_unref(buf);
            }
        }
		/* Give other threads a chance to run if trx_queue keeps getting
		 * new data all the time.
		 */
		k_yield();
	}
}

bool bt_driver_enter_relay_mode(uint8_t port)
{
    //BT_LOGI("BT","bt_driver_enter_relay_mode, RELAY_BUFFER_SIZE = %d \n", RELAY_BUFFER_SIZE );

    if (bt_driver_relay_enabled && bt_driver_relay_enable_complete) {
        //BT_DRVLOG_MSGID_W("BTIF", BTIF_229, 0);
        return true;
    }

    //bt_driver_init();

    bt_driver_relay_enabled = 1;

    //bt_driver_power_on();


    //bt_enable(NULL);
    //t_enable_raw(&trx_queue);
    bt_hci_open(bt_relay_dev.hci, bt_hci_relay_recv);
    const uint8_t reset_cmd[] = {0x03, 0x0c,0x00}; /*reset_cmd*/
    
    struct net_buf *buf;
    buf = net_buf_alloc(&relay_pool, K_FOREVER);
    if(!buf) {
        printk("Failed to get ACL TX buffer \r\n");
    }
	net_buf_reserve(buf, BT_BUF_RESERVE);

	bt_buf_set_type(buf, BT_BUF_CMD);

    net_buf_add_mem(buf, reset_cmd, sizeof(reset_cmd));
    if (bt_send(buf)) {
        printk("Failed to send reset data \r\n");
        net_buf_unref(buf);
    }


    printk("relay mode send reset \r\n");
    /*reset controller*/    

    if (0 != bt_driver_relay_cb.init(port)) {
        bt_driver_deinit_relay_mode();
        return false;
    }

    bt_driver_relay_tx_buf = (uint8_t *)k_malloc(RELAY_BUFFER_SIZE);
    bt_driver_relay_rx_buf = (uint8_t *)k_malloc(RELAY_BUFFER_SIZE);

    bt_driver_relay_enable_complete = 1;


    k_thread_create(&trx_thread_data, trx_thread_stack,
	K_THREAD_STACK_SIZEOF(trx_thread_stack), trx_thread,
		NULL, NULL, NULL, K_PRIO_COOP(7), 0, K_NO_WAIT);
	k_thread_name_set(&trx_thread_data, "HCI uart TRX");

    return true;
}

void bt_driver_deinit_relay_mode(void)
{
    bt_driver_relay_enabled = 0;
    bt_driver_relay_enable_complete = 0;
    
    bt_driver_relay_cb.deinit();

}

uint8_t bt_driver_relay_event_handle(struct net_buf *buf)
{

        uint8_t *relay_tx_buff = bt_driver_get_relay_tx_buffer();

        switch (bt_buf_get_type(buf)) {
            case BT_BUF_ACL_IN:
            {
                //printk("ACL IN DATA \r\n");
                relay_tx_buff[0] = 2;
                memcpy(relay_tx_buff + 1, buf->data, buf->len);
                break;
            }
            case BT_BUF_EVT:
            {                
                //printk("EVT:len:%d, buf0:%x, buf1:%x, buf2:%d\r\n",buf->len, buf->data[0], buf->data[1], buf->data[2]);
                relay_tx_buff[0] = 4; 
                memcpy(relay_tx_buff + 1, buf->data, buf->len);                
                //printk("relay_tx_buff[0] is %d, relay_tx_buff[1] is %d,relay_tx_buff[2] is %d \r\n",relay_tx_buff[0],relay_tx_buff[1],relay_tx_buff[2]);
            }            
            break;
            default:
            printk("Invalid buf type %u \r\n", bt_buf_get_type(buf));
            net_buf_unref(buf);
            break;
        }
        //BT_ASSERT(relay_tx_buff);
        //BT_FREE_PACKET_WITH_NODE(BT_MEMORY_RX_BUFFER, relay_packet);
        bt_driver_relay_cb.write_data(relay_tx_buff, (buf->len + 1));        
        //printk("relay_tx_buff[0] is %d, relay_tx_buff[1] is %d,relay_tx_buff[2] is %d \r\n",relay_tx_buff[0],relay_tx_buff[1],relay_tx_buff[2]);
        //memset(relay_tx_buff, 0x00, buf->len);
        net_buf_unref(buf);
        return true;
}


void bt_driver_relay_cb_write_data(uint8_t *buf, uint32_t buf_len)
{
    bt_driver_relay_cb.write_data(buf, buf_len);
}

