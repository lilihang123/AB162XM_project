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
#include "air_chip.h"

#include <zephyr/kernel.h>
#include <zephyr/drivers/entropy.h>
#include <zephyr/drivers/bluetooth/hci_driver.h>
#include <zephyr/bluetooth/controller.h>
#include <zephyr/bluetooth/hci_vs.h>
#include <zephyr/bluetooth/buf.h>
#include <zephyr/init.h>
#include <zephyr/irq.h>
#include <zephyr/kernel.h>
#include <soc.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/sys/util.h>
#include <stdbool.h>
#include <zephyr/sys/__assert.h>
#include "bt_type.h"
#if KERNELVERSION >= 0x3070000
#include <zephyr/drivers/bluetooth.h>
#endif
/* header for using macro of BT_ASSERT_MSG */
#include "common/assert.h"
#include "hal_gpio.h"
#include "avm_external.h"
//#include "bt_linknode.h"
//#include "bt_memory.h"
#include "bt_debug.h"
//#include "bt_common_upper_layer.h"
#include "bt_hci_log.h"
#include "air_version.h"
#include <zephyr/bluetooth/hci.h>
#include "nvkey.h"
#if KERNELVERSION >= 0x3070000
#define DT_DRV_COMPAT airoha_air_bt_hci
#endif
#include "relay_client.h"
void pka_init_test(void);
void bt_tx_notify_pka_test(uint8_t type, unsigned char *q_header);

extern void *bt_hb_tx_dequeue(uint8_t type, uint8_t *q_header);
extern void bt_hb_rx_enqueue(uint8_t *hb_header);
extern uint16_t bt_get_hb_header_size(void);
extern uint8_t *bt_hb_mm_allocate(uint8_t type, uint32_t size);
extern void bt_hb_mm_free(uint8_t type, uint8_t *ptr);

#if 1 
typedef enum {
    BT_QUEUE_TYPE_RX = 0,
    BT_QUEUE_TYPE_TX_ACL,
    BT_QUEUE_TYPE_TX_CMD,
} bt_hb_queue_type_t;
#endif 

#define HCI_FROM_HOST         0
#define HCI_FROM_CONTROLLER   1

/**
 * @brief HCI packet indicator. Refer to the Bluetooth core specifications version 4.2 [Vol 4, Part A] UART Transport Layer, CH2 PROTOCOL.
 */
#define BT_UART_CMD     0x01
#define BT_UART_ACL     0x02
#define BT_UART_EVT     0x04
#define BT_UART_ISO     0x05
typedef uint8_t bt_uart_t;


#define BT_DBG_ENABLED IS_ENABLED(CONFIG_BT_DEBUG_HCI_DRIVER)
#define LOG_MODULE_NAME air_hci_driver

#include <zephyr/logging/log.h>
#define thisMODULE hcid_airo
LOG_MODULE_REGISTER(thisMODULE);

#if KERNELVERSION >= 0x3070000
struct hci_driver_data {
	bt_hci_recv_t recv;
};

struct hci_driver_data recv_data = {
    .recv = NULL
};
#endif

typedef struct {
    bool relay_enable;
    uint8_t port_number;
} bt_power_on_relay_config_t;

bt_bd_addr_t local_public_addr = {0};

#if 0
static void hex_display(const uint8_t *buf, uint16_t len)
{
    const uint8_t *p = buf;
    int i;
    for (i = 0; i < len; i++) {
        printk("%x",p[i]);
    }
    printk("\n");
}

static void char_display(const uint8_t *buf, uint16_t len)
{
    const uint8_t *p = buf;
    int i;
    for (i = 0; i < len; i++) {
        printk("%c",p[i]);
    }
    printk("\n");
}
#endif

static void cmd_handle(struct net_buf *cmd)
{
    //struct bt_hci_cmd_hdr *hdr;
    //uint16_t opcode;
    //uint8_t  len;

    BT_LOGD(GROUP_BT_DRIVER, "cmd_handle, cmd->size %d, cmd->len %d, user_data[0] = %d", cmd->size, cmd->len, cmd->user_data[0]);
    //bt_tx_notify_pka_test(BT_QUEUE_TYPE_TX_CMD, (unsigned char *)cmd);

    #if defined (CONFIG_AIR_AVM)
    //BT_LOGI(GROUP_BT_DRIVER, "cmd->data = 0x%02x-%02x-%02x-%02x ", cmd->data[0], cmd->data[1], cmd->data[2], cmd->data[3]);
    extern void bt_driver_avm_send(uint16_t total_payload_size, uint8_t * packet, uint8_t HCI_pcket_type, bt_hb_queue_type_t qType);
    bt_driver_avm_send(cmd->len, cmd->data, BT_UART_CMD, BT_QUEUE_TYPE_TX_CMD );
    #endif
}

#if defined(CONFIG_BT_CONN)
static void acl_handle(struct net_buf *acl)
{
    BT_LOGD(GROUP_BT_DRIVER, "acl_handle");

    #if 0 
    struct bt_hci_acl_hdr *hdr;
    uint16_t handle;
    uint16_t len;

    bt_tx_notify_pka_test(BT_QUEUE_TYPE_TX_ACL, acl);

    hdr = net_buf_pull_mem(acl, sizeof(*hdr));
    len = sys_le16_to_cpu(hdr->len);
    handle = sys_le16_to_cpu(hdr->handle);

    BT_LOGI(GROUP_BT_DRIVER, "%c%c%c%c%c%c%c%c%c",'\xab','\xcd', BT_UART_ACL, ((len + 4) >> 8), (len+ 4) & 0xFF, handle & 0xFF, handle >> 8, len & 0xFF, len >> 8);
    #else
    #if defined (CONFIG_AIR_AVM)
    //BT_LOGI(GROUP_BT_DRIVER, "cmd->data = 0x%02x-%02x-%02x-%02x ", cmd->data[0], cmd->data[1], cmd->data[2], cmd->data[3]);
    extern void bt_driver_avm_send(uint16_t total_payload_size, uint8_t * packet, uint8_t HCI_pcket_type, bt_hb_queue_type_t qType);
    bt_driver_avm_send(acl->len, acl->data, BT_UART_ACL, BT_QUEUE_TYPE_TX_ACL);
    #endif    

    #endif
}
#endif

#ifdef CONFIG_AIR_BT_RELAY_HOST_ENABLE
static uint8_t host_relay_tx_buf[1024] = {0};
#endif

#if KERNELVERSION == 0x3030000
static int hci_driver_send(struct net_buf *buf)
#else
static int hci_driver_send(const struct device *dev, struct net_buf *buf)
#endif
{
    uint8_t type;


    if (!buf->len) {
        BT_LOGD(GROUP_BT_DRIVER, "Empty HCI packet");
        return -EINVAL;
    }

    type = bt_buf_get_type(buf);

#ifdef CONFIG_AIR_BT_RELAY_HOST_ENABLE
    LOG_ERR("type is %x", type);
    extern void bt_driver_relay_cb_write_data(uint8_t *buf, uint32_t buf_len);
    uint32_t packet_len = buf->len + 1;
    uint8_t *relay_tx_buff = host_relay_tx_buf;
	if (type == BT_BUF_ACL_OUT) {
        relay_tx_buff[0] = BT_UART_ACL;
    } else if (type == BT_BUF_CMD) {
        relay_tx_buff[0] = BT_UART_CMD;
    } else {
		LOG_ERR("type is %x", type);
        /*Unexcept data*/
    }
    memcpy(relay_tx_buff + 1, buf->data, buf->len);
    bt_driver_relay_cb_write_data(relay_tx_buff, packet_len);
    memset(relay_tx_buff, 0x00, packet_len);
    net_buf_unref(buf);
    return 0;
#endif

    BT_LOGI(GROUP_BT_DRIVER,"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    BT_LOGI(GROUP_BT_DRIVER, "hci_driver_send, buf->ref = %d", buf->ref);

    if (type == BT_BUF_CMD){
        BT_LOGI(GROUP_BT_DRIVER, "HCI CMD = %02x-%02x - %02x-%02x - %02x-%02x ", buf->data[0], buf->data[1], buf->data[2], buf->data[3], buf->data[4], buf->data[5]);    
    }
    else {
        //BT_LOGI(GROUP_BT_DRIVER, "HCI ACL = %02x-%02x - %02x-%02x - %02x-%02x ", buf->data[0], buf->data[1], buf->data[2], buf->data[3], buf->data[4], buf->data[5]);    
        BT_LOGI(GROUP_BT_DRIVER," HCI ACL: ConnHdl = 0x%04X , len = 0x%X,  L2CAP len= 0x%04X , L2CAP ch = 0x%04X, ATT opcode = 0x%X, 0x%02X-0x%02X \n"
            , ((buf->data[1]<<8) | buf->data[0])
            , ((buf->data[3]<<8) | buf->data[2])
            , ((buf->data[5]<<8) | buf->data[4])
            , ((buf->data[7]<<8) | buf->data[6])            
            , buf->data[8]
            , buf->data[9]
            , buf->data[10]            
            );
    }

    BT_LOGI(GROUP_BT_DRIVER,"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");

    
    switch (type) {
#if defined(CONFIG_BT_CONN)
    case BT_BUF_ACL_OUT:
        acl_handle(buf);
        break;
#endif          /* CONFIG_BT_CONN */
    case BT_BUF_CMD:
        cmd_handle(buf);
        break;
    default:
        BT_LOGI(GROUP_BT_DRIVER, "Unknown HCI type %u", type);
        return -EINVAL;
    }

    // unref one time here
    net_buf_unref(buf);

    //controller will free the buf
    return 0;
}

static void data_packet_process(uint8_t *payload)
{
    uint8_t *hci_buf = payload+1; 
    struct net_buf *data_buf = bt_buf_get_rx(BT_BUF_ACL_IN, K_FOREVER);
    struct bt_hci_acl_hdr *hdr = (struct bt_hci_acl_hdr *)(hci_buf);
    uint16_t hf, len;

    BT_LOGD(GROUP_BT_DRIVER, "data_packet_process data_buf = %p", data_buf);


    if (!data_buf) {
        BT_LOGI(GROUP_BT_DRIVER, "No data buffer available");
        return;
    }




    len = sys_le16_to_cpu(hdr->len);
    hf = sys_le16_to_cpu(hdr->handle);


    bt_hci_log(HCI_FROM_CONTROLLER, payload, len + sizeof(*hdr) + 1);

    BT_LOGD(GROUP_BT_DRIVER, "len = %u,  hf = %u, sizeof(*hdr) = %d", len, hf, sizeof(*hdr));


    
   // BT_LOGI(GROUP_BT_DRIVER, "%c%c%c%c%c%c%c%c%c",'\xab','\xcd', BT_UART_ACL, ((len + 4) >> 8), (len+ 4) & 0xFF, hf & 0xFF, hf >> 8, len & 0xFF, len >> 8);
    //char_display(&hci_buf[4], len);

    BT_LOGI(GROUP_BT_DRIVER, "hci_buf = %02X-%02X-%02X-%02X, len = %u ",  hci_buf[0], hci_buf[1], hci_buf[2], hci_buf[3], len + sizeof(*hdr) );

    net_buf_add_mem(data_buf, &hci_buf[0], len + sizeof(*hdr));
    
#if KERNELVERSION == 0x3030000
    bt_recv(data_buf);
#else
    recv_data.recv(NULL,data_buf);
#endif

}

bool event_packet_is_discardable(const uint8_t *hci_buf)
{
    struct bt_hci_evt_hdr *hdr = (void *)hci_buf;

    BT_LOGD(GROUP_BT_DRIVER, "event_packet_is_discardable hci_buf = %p ", hci_buf);

    switch (hdr->evt) {
    case BT_HCI_EVT_LE_META_EVENT: {
        struct bt_hci_evt_le_meta_event *me = (void *)&hci_buf[2];

        switch (me->subevent) {
        case BT_HCI_EVT_LE_ADVERTISING_REPORT:
            return true;
        default:
            return false;
        }
    }
    default:
        return false;
    }
}

static void event_packet_process(uint8_t *payload)
{
    uint8_t *hci_buf = payload+1; 
    bool discardable = event_packet_is_discardable(hci_buf);
    struct bt_hci_evt_hdr *hdr = (struct bt_hci_evt_hdr *)hci_buf;
    struct net_buf *evt_buf;

    //printk("%c%c%c%c%c",'\xab','\xcd', BT_HCI_LOG_EVENT, ((hdr->len + sizeof(*hdr)) >> 8), (hdr->len+ sizeof(*hdr)) & 0xFF);
    //char_display(hci_buf, hdr->len + sizeof(*hdr));

    evt_buf = bt_buf_get_evt(hdr->evt, discardable,
                discardable ? K_NO_WAIT : K_FOREVER);

    if (!evt_buf) {
        if (discardable) {
            BT_LOGD(GROUP_BT_DRIVER, "Discarding event");
            return;
        }

        BT_LOGD(GROUP_BT_DRIVER,"No event buffer available");
        return;
    }


    bt_hci_log(HCI_FROM_CONTROLLER, payload, hdr->len + sizeof(*hdr) + 1);
    net_buf_add_mem(evt_buf, &hci_buf[0], hdr->len + sizeof(*hdr));
    //BT_LOGHEX(GROUP_BT_DRIVER,"evt_buf->data =",evt_buf->data, hdr->len + sizeof(*hdr) + 1 );
#if KERNELVERSION == 0x3030000
        bt_recv(evt_buf);
#else
        recv_data.recv(NULL,evt_buf);
#endif
}

#if 0 
uint8_t *bt_hb_mm_allocate(uint8_t type, uint32_t size)
{
    //normal alloc
    uint8_t* mem = (uint8_t *)k_malloc(size);
    printk("bt_hb_mm_allocate allocated at %p\n", mem); 
    return mem;
}

void bt_hb_mm_free(uint8_t type, uint8_t *ptr)
{
    printk("bt_hb_mm_free allocated at %p\n", ptr);
    //normal free
    k_free((void *)ptr);
}
#endif





uint8_t *g_hb_header = NULL;

#if 0
uint16_t bt_get_hb_header_size(void)
{
    return sizeof(bt_hci_packet_linknode_t);
}

void bt_hb_rx_enqueue(uint8_t *hb_header)
{
    BT_LOGI(GROUP_BT_DRIVER, "bt_hb_rx_enqueue");
    g_hb_header = hb_header;

}

void *bt_hb_tx_dequeue(uint8_t type, uint8_t *q_header)
{
    BT_LOGI(GROUP_BT_DRIVER, "bt_hb_tx_dequeue");
    BT_ASSERT_MSG((type == BT_QUEUE_TYPE_TX_ACL || type == BT_QUEUE_TYPE_TX_CMD), "err type %d", type);
    return q_header;
}
#endif 

void bt_rx_notify_hb(void)
{
    extern void *bt_get_packet_from_node(uint8_t *ptr);
    uint8_t *payload = bt_get_packet_from_node(g_hb_header);
    bt_uart_t hciH4Type = payload[0];

    BT_LOGI(GROUP_BT_DRIVER," ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
    BT_LOGI(GROUP_BT_DRIVER," bt_rx_notify_hb");

    if (hciH4Type == BT_UART_EVT){
        BT_LOGI(GROUP_BT_DRIVER," HCI Event(%X), Evt = 0x%02X , len = %d,  Nocp= %d , opcode = %02X, status = %d, payload = %p \n"
            , payload[0]
            , payload[1]
            , payload[2]
            , payload[3]        
            , ((payload[5]<<8) | payload[4])
            , payload[6]
            , payload
            );
    }
    else {
        BT_LOGI(GROUP_BT_DRIVER," HCI ACL(%X), ConnHdl = 0x%04X , len = %d,  L2CAP len= 0x%04X , L2CAP ch = 0x%04X, ATT opcode = 0x%X, 0x%02X-0x%02X \n"
            , payload[0]
            , ((payload[2]<<8) | payload[1])
            , ((payload[4]<<8) | payload[3])
            , ((payload[6]<<8) | payload[5])
            , ((payload[8]<<8) | payload[7])            
            , payload[9]
            , payload[10]
            , payload[11]            
            );
    }
    BT_LOGI(GROUP_BT_DRIVER," ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");

    BT_LOGD(GROUP_BT_DRIVER, "bt_rx_notify_hb hciH4Type = %d", hciH4Type);
    BT_LOGD(GROUP_BT_DRIVER, "g_hb_header = %p,  bt_get_hb_header_size = %d \n", g_hb_header, bt_get_hb_header_size() );

    extern uint8_t bt_driver_relay_event_handle();
    if (bt_driver_relay_event_handle()){
        return;
    }

    switch (hciH4Type) {
        case BT_UART_ACL:
            data_packet_process(payload);
            break;
        case BT_UART_EVT:
            event_packet_process(payload);
            break;
        default:
            break;
    }

    #if defined (CONFIG_AIR_AVM)
    extern void bt_driver_hci_event_handle();
    bt_driver_hci_event_handle();
    #endif

    BT_LOGI(GROUP_BT_DRIVER," ..");
    BT_LOGI(GROUP_BT_DRIVER," ......");
    //bt_hb_mm_free(BT_QUEUE_TYPE_RX, g_hb_header);
}

void pka_init(void);

#if KERNELVERSION == 0x3030000
static int hci_driver_open(void)
#else
static int hci_driver_open(const struct device *dev, bt_hci_recv_t recv)
#endif
{
    BT_LOGD(GROUP_BT_DRIVER, "hci_driver_open ");
#if KERNELVERSION >= 0x3070000
    struct hci_driver_data *data = dev->data;
    data->recv = recv;
    recv_data.recv = recv;
#endif
#ifdef CONFIG_AIR_BT_RELAY_HOST_ENABLE
    relay_client_init(2);
    return 0;
#endif

    #if defined (CONFIG_AIR_AVM)
    extern bool bt_driver_avm_init(void);
    bt_driver_avm_init();
    #endif

    //BT_LOGHEX(GROUP_BT_DRIVER,"Airoha Controller version: ",bt_pikachu_lib_verno(), strlen(bt_pikachu_lib_verno()));
    //BT_LOGHEX(GROUP_BT_DRIVER,"Airoha Controller commit: ", bt_pikachu_lib_lastest_commit(), strlen(bt_pikachu_lib_lastest_commit()));

    avm_pka_callbacks_t pka_avm_callbacks;
    pka_avm_callbacks.bt_hb_mm_allocate = (unsigned char *(*)(uint8_t type, unsigned int size))bt_hb_mm_allocate;
    pka_avm_callbacks.bt_hb_mm_free = bt_hb_mm_free;
    pka_avm_callbacks.bt_hb_rx_enqueue = bt_hb_rx_enqueue;
    pka_avm_callbacks.bt_hb_tx_dequeue = bt_hb_tx_dequeue;
    pka_avm_callbacks.bt_get_hb_header_size = bt_get_hb_header_size;
    pka_avm_callbacks.bt_rx_notify_hb = bt_rx_notify_hb;
    bt_avm_pka_register_callbacks(pka_avm_callbacks);
    pka_init_test();
    
    bt_power_on_relay_config_t relay_config = {
        .relay_enable = false,
        .port_number = 0,
    };
    uint32_t relay_size = sizeof(bt_power_on_relay_config_t);
    nvkey_status_t status =nvkey_read_data(NVID_BT_HOST_RELAY_ENABLE, (uint8_t *)(&relay_config), &relay_size);
    if (status != NVKEY_STATUS_OK) {
        LOG_ERR("Read relay nvkey error");
    }
    if (relay_config.relay_enable) {
        LOG_ERR("Enter relay uart is %d", relay_config.port_number);
        relay_client_init(relay_config.port_number);
        return -1;
    }
    return 0;
}
#if KERNELVERSION == 0x3030000
static const struct bt_hci_driver drv = {
    .name = "Airoha Controller",
    .bus = BT_HCI_DRIVER_BUS_VIRTUAL,
    .open = hci_driver_open,
    .send = hci_driver_send,
};
#endif

#if !defined(CONFIG_BT_HCI_VS_EXT)
uint8_t bt_read_static_addr(struct bt_hci_vs_static_addr addrs[], uint8_t size)
{
    return 0;
}
#endif /* !defined(CONFIG_BT_HCI_VS_EXT) */

void bt_ctlr_set_public_addr(const uint8_t *addr)
{
//#define BT_HCI_CMD_SET_BD_ADDR                               0xFC1A
}

//controller simulation
#include <zephyr/bluetooth/hci.h>


#if KERNELVERSION == 0x3030000
static int hci_driver_init(const struct device *unused)
{
    ARG_UNUSED(unused);
    int err = 0;

    err = bt_hci_driver_register(&drv);

    return err;
}
#endif




static int bt_set_addr(uint8_t* bd_addr)
{
    #define BD_ADDR_SIZE  6
    #define BT_HCI_OP_VS_SET_DEVICE_ADDR		BT_OP(BT_OGF_VS, 0x001A)
    
    struct net_buf *buf;
    int err;

    buf = bt_hci_cmd_create(BT_HCI_OP_VS_SET_DEVICE_ADDR, BD_ADDR_SIZE);
    if (!buf) {
        return -ENOBUFS;
    }

    net_buf_add_mem(buf, bd_addr, BD_ADDR_SIZE );

    err = bt_hci_cmd_send(BT_HCI_OP_VS_SET_DEVICE_ADDR, buf);
    if (err) {
         return err;
    }
    return 0;
}
void bt_retrieve_device_addr()
{
    uint8_t bd_addr[6] = {0};
    uint32_t addr_size = sizeof(bt_bd_addr_t);
    if (NVKEY_STATUS_OK != nvkey_read_data(NVID_BT_HOST_LOCAL_ADDR, bd_addr, &addr_size)) {
#if IS_ENABLED(CONFIG_AIR_ENTROPY_ENABLE)
        LOG_INF("[BT_Dri] Get random value for loacl addr");
        memset(&bd_addr[0], 0, sizeof(bd_addr));
        const struct device *const entropy = DEVICE_DT_GET_OR_NULL(DT_CHOSEN(zephyr_entropy));
        if (0 != entropy_get_entropy(entropy, (uint8_t*)&bd_addr[0], sizeof(bd_addr))) {
            LOG_ERR("[BT_Dri] Get entropy error");
            bd_addr[5] = 0;
            bd_addr[4] = ((build_date_time_str[5]-0x30)<<4)| ((build_date_time_str[6]-0x30));
            bd_addr[3] = ((build_date_time_str[8]-0x30)<<4)| ((build_date_time_str[9]-0x30));
            bd_addr[2] = ((build_date_time_str[11]-0x30)<<4)| ((build_date_time_str[12]-0x30));
            bd_addr[1] = ((build_date_time_str[14]-0x30)<<4)| ((build_date_time_str[15]-0x30));
            bd_addr[0] = ((build_date_time_str[17]-0x30)<<4)| ((build_date_time_str[18]-0x30));
        }
#else
            bd_addr[5] = 0;
            bd_addr[4] = ((build_date_time_str[5]-0x30)<<4)| ((build_date_time_str[6]-0x30));
            bd_addr[3] = ((build_date_time_str[8]-0x30)<<4)| ((build_date_time_str[9]-0x30));
            bd_addr[2] = ((build_date_time_str[11]-0x30)<<4)| ((build_date_time_str[12]-0x30));
            bd_addr[1] = ((build_date_time_str[14]-0x30)<<4)| ((build_date_time_str[15]-0x30));
            bd_addr[0] = ((build_date_time_str[17]-0x30)<<4)| ((build_date_time_str[18]-0x30));
#endif

        LOG_ERR("[BT_Dri] read nvdm addr fail");
        addr_size = sizeof(bt_bd_addr_t);
        if (NVKEY_STATUS_OK != nvkey_write_data(NVID_BT_HOST_LOCAL_ADDR, bd_addr, addr_size)) {
           LOG_ERR("[BT_Dri] write nvdm addr fail");
        }
    }
    LOG_INF("[I][" GROUP_BT_DRIVER"]""BD_ADDR = 0x%02X-%02X-%02X-%02X-%02X-%02X",bd_addr[5], bd_addr[4], bd_addr[3], bd_addr[2], bd_addr[1], bd_addr[0]);
    memcpy(&local_public_addr, bd_addr, sizeof(bt_bd_addr_t));
    bt_set_addr(bd_addr);
}

void bt_driver_airoha_get_loacl_addr(bt_bd_addr_t *addr)
{
    bt_bd_addr_t invalid_addr = {0};
    uint32_t addr_size = sizeof(bt_bd_addr_t);
    if (memcmp(&invalid_addr, &local_public_addr, sizeof(bt_bd_addr_t))) {
        memcpy(addr, &local_public_addr, sizeof(bt_bd_addr_t));
    } else {
        if (NVKEY_STATUS_OK == nvkey_read_data(NVID_BT_HOST_LOCAL_ADDR, (uint8_t *)&local_public_addr, &addr_size)) {
            memcpy(addr, &local_public_addr, sizeof(bt_bd_addr_t));
        } else {
            addr_size = sizeof(bt_bd_addr_t);
#if IS_ENABLED(CONFIG_AIR_ENTROPY_ENABLE)
            LOG_INF("[BT_Dri] Get random value for loacl addr");
            uint8_t new_bd_addr[6] = {0};
        
            const struct device *const entropy = DEVICE_DT_GET_OR_NULL(DT_CHOSEN(zephyr_entropy));
            if (0 != entropy_get_entropy(entropy, (uint8_t*)&new_bd_addr[0], addr_size)) {
                LOG_ERR("[BT_Dri] Get entropy error");
                new_bd_addr[5] = 0;
                new_bd_addr[4] = ((build_date_time_str[5]-0x30)<<4)| ((build_date_time_str[6]-0x30));
                new_bd_addr[3] = ((build_date_time_str[8]-0x30)<<4)| ((build_date_time_str[9]-0x30));
                new_bd_addr[2] = ((build_date_time_str[11]-0x30)<<4)| ((build_date_time_str[12]-0x30));
                new_bd_addr[1] = ((build_date_time_str[14]-0x30)<<4)| ((build_date_time_str[15]-0x30));
                new_bd_addr[0] = ((build_date_time_str[17]-0x30)<<4)| ((build_date_time_str[18]-0x30));
            }
#else
                uint8_t new_bd_addr[6] = {0};
                new_bd_addr[5] = 0;
                new_bd_addr[4] = ((build_date_time_str[5]-0x30)<<4)| ((build_date_time_str[6]-0x30));
                new_bd_addr[3] = ((build_date_time_str[8]-0x30)<<4)| ((build_date_time_str[9]-0x30));
                new_bd_addr[2] = ((build_date_time_str[11]-0x30)<<4)| ((build_date_time_str[12]-0x30));
                new_bd_addr[1] = ((build_date_time_str[14]-0x30)<<4)| ((build_date_time_str[15]-0x30));
                new_bd_addr[0] = ((build_date_time_str[17]-0x30)<<4)| ((build_date_time_str[18]-0x30));
#endif
            
        nvkey_write_data(NVID_BT_HOST_LOCAL_ADDR, new_bd_addr, addr_size);
        memcpy(addr, new_bd_addr, sizeof(bt_bd_addr_t));
        }
    }
}

void pka_init_test(void)
{
    BT_LOGD(GROUP_BT_DRIVER, "pka_init");
    bt_retrieve_device_addr();    
    return;
}

#define CMD_COMLETE_EVENT_SIZE (BT_HCI_EVT_HDR_SIZE + sizeof(struct bt_hci_evt_cmd_complete))
#define CMD_STATUS_EVENT_SIZE (BT_HCI_EVT_HDR_SIZE + sizeof(struct bt_hci_evt_cmd_status))

//generate evt
//hciH4Type(1byte) + payload(evt header + evt param)

#if 0
uint8_t * generate_cmd_complete_evt(uint16_t opcode, uint8_t *return_param, uint8_t len)
{
    uint8_t *pkt = bt_hb_mm_allocate(BT_QUEUE_TYPE_RX, 1 + CMD_COMLETE_EVENT_SIZE + len);
    if (NULL == pkt) {
        return NULL;
    }
    pkt[0] = BT_UART_EVT;
    struct bt_hci_evt_hdr *evt = (struct bt_hci_evt_hdr *)(pkt + 1);
    evt->evt = BT_HCI_EVT_CMD_COMPLETE;
    evt->len = sizeof(struct bt_hci_evt_cmd_complete) + len;
    BT_LOGI(GROUP_BT_DRIVER, "generate_cmd_complete_evt opcode 0x%x, len %d", opcode, evt->len);
    struct bt_hci_evt_cmd_complete *param = (struct bt_hci_evt_cmd_complete *)(pkt + 1 + BT_HCI_EVT_HDR_SIZE);
    param->ncmd = 1;
    param->opcode = opcode;
    memcpy((uint8_t *)param + 3, return_param, len);
    BT_LOGHEX(GROUP_BT_DRIVER,"pkt ", pkt, 1 + CMD_COMLETE_EVENT_SIZE + len);
    return pkt;
}

uint8_t * generate_cmd_status_evt(uint16_t opcode)
{
    uint8_t *pkt = bt_hb_mm_allocate(BT_QUEUE_TYPE_RX, 1 + CMD_STATUS_EVENT_SIZE);
    if (NULL == pkt) {
        return NULL;
    }
    pkt[0] = BT_UART_EVT;
    struct bt_hci_evt_hdr *evt = (struct bt_hci_evt_hdr *)(pkt + 1);
    evt->evt = BT_HCI_EVT_CMD_STATUS;
    evt->len = sizeof(struct bt_hci_evt_cmd_status);
    BT_LOGI(GROUP_BT_DRIVER, "generate_cmd_status_evt opcode 0x%x, len %d", opcode, evt->len);
    struct bt_hci_evt_cmd_status *param = (struct bt_hci_evt_cmd_status *)(pkt + 1 + BT_HCI_EVT_HDR_SIZE);
    param->status = 0;
    param->ncmd = 1;
    param->opcode = opcode;

    BT_LOGHEX(GROUP_BT_DRIVER, "pkt", pkt, 1 + CMD_COMLETE_EVENT_SIZE);
    return pkt;
}
void bt_tx_notify_pka_test(uint8_t type, unsigned char *q_header)
{
    struct net_buf *buf = bt_hb_tx_dequeue(type, q_header); 
    BT_LOGI(GROUP_BT_DRIVER, "bt_tx_notify_pka type %d, buf size %d, buf len %d", type, buf->size, buf->len);
    if (type == BT_QUEUE_TYPE_TX_CMD)
    {
        struct bt_hci_cmd_hdr *hdr;
        //uint8_t *reserve;
        uint16_t opcode;
        uint8_t  len;
        //uint8_t *pkt = NULL;
        //reserve = (uint8_t *)net_buf_push_mem(buf, 24);
        hdr = net_buf_pull_mem(buf, sizeof(*hdr));
        len = hdr->param_len;
        opcode = sys_le16_to_cpu(hdr->opcode);
        //printk("%c%c%c%c%c%c%c%c",'\xab','\xcd', BT_HCI_LOG_CMD, ((len + 3) >> 8), (len+ 3) & 0xFF, opcode & 0xFF, (opcode >> 8), len & 0xFF);
        //char_display( (const uint8_t *) (hdr+3), len);

        switch (opcode) {
            case BT_HCI_OP_READ_LOCAL_FEATURES:
                {
                    struct bt_hci_rp_read_local_features evt;
                    evt.status = 0;
                    memset(evt.features, 0xff, 8);
                    len = sizeof(struct bt_hci_rp_read_local_features);
                    //pkt = generate_cmd_complete_evt(opcode, (uint8_t *)&evt, len);
                }
                break;
            case BT_HCI_OP_RESET:
            case BT_HCI_OP_HOST_BUFFER_SIZE:
            case BT_HCI_OP_SET_CTL_TO_HOST_FLOW:
                {
                    //uint8_t status = 0;
                    //pkt = generate_cmd_complete_evt(opcode, &status, 1);
                }
                break;
            case BT_HCI_OP_READ_LOCAL_VERSION_INFO:
                {
                    struct bt_hci_rp_read_local_version_info evt;
                    evt.hci_version = 1;
                    evt.hci_revision = 2;
                    evt.lmp_version = 5;
                    evt.lmp_subversion = 3;
                    evt.manufacturer = 0xff;
                    len = sizeof(struct bt_hci_rp_read_local_version_info);
                    //pkt = generate_cmd_complete_evt(opcode, (uint8_t *)&evt, len);
                }
                break;
            case BT_HCI_OP_READ_SUPPORTED_COMMANDS:
                {
                    struct bt_hci_rp_read_supported_commands evt;
                    evt.status = 0;
                    memset(evt.commands, 0xff, 64);
                    len = sizeof(struct bt_hci_rp_read_supported_commands);
                    //pkt = generate_cmd_complete_evt(opcode, (uint8_t *)&evt, len);
                }
                break;
            case BT_HCI_OP_LE_RAND:
                {
                    struct bt_hci_rp_le_rand evt;
                    evt.status = 0;
                    memset(evt.rand, 0xff, 8);
                    len = sizeof(struct bt_hci_rp_le_rand);
                    //pkt = generate_cmd_complete_evt(opcode, (uint8_t *)&evt, len);
                }
                break;
            case BT_HCI_OP_LE_READ_LOCAL_FEATURES:
                {
                    struct bt_hci_rp_le_read_local_features evt;
                    evt.status = 0;
                    memset(evt.features, 0xff, 8);
                    len = sizeof(struct bt_hci_rp_le_read_local_features);
                    //pkt = generate_cmd_complete_evt(opcode, (uint8_t *)&evt, len);
                }
                break;
            case BT_HCI_OP_LE_READ_BUFFER_SIZE:
                {
                    struct bt_hci_rp_le_read_buffer_size evt;
                    evt.status = 0;
                    evt.le_max_len = 255;
                    evt.le_max_num = 10;
                    len = sizeof(struct bt_hci_rp_le_read_buffer_size);
                    //pkt = generate_cmd_complete_evt(opcode, (uint8_t *)&evt, len);
                }
                break;
            default:
                BT_LOGI(GROUP_BT_DRIVER, "not supported by temp controller now");
                break;
        }
        //bt_hb_rx_enqueue(pkt);
        bt_rx_notify_hb();
    }
    net_buf_unref(buf);
    return;
}
#endif

#if KERNELVERSION >= 0x3070000
static int hci_driver_close(const struct device *dev)
{
    struct hci_driver_data *data = dev->data;
    data->recv = NULL;

    return 0;
}
#endif

#if KERNELVERSION == 0x3030000
SYS_INIT(hci_driver_init, POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEVICE);
#elif KERNELVERSION >= 0x3070000
static const struct bt_hci_driver_api hci_airoha_driver_api = {
    .open = hci_driver_open,
    .close = hci_driver_close,
    .send = hci_driver_send,
};

#define BT_HCI_CONTROLLER_INIT(inst) \
    static struct hci_driver_data data_##inst; \
    DEVICE_DT_INST_DEFINE(inst, NULL, NULL, &data_##inst, NULL, POST_KERNEL, \
                          CONFIG_KERNEL_INIT_PRIORITY_DEVICE, &hci_airoha_driver_api)

/* Only a single instance is supported */
BT_HCI_CONTROLLER_INIT(0)

#else
#error "Unkown support kernal version"
#endif

