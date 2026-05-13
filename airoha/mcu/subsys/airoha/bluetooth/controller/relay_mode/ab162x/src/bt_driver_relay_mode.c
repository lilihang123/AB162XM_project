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

#include "avm_external.h"
#include "bt_linknode.h"
#include "avm_memory.h"
#include "bt_debug.h"
#include "bt_common_upper_layer.h"
#include "avm_external.h"
#include "memory_attribute.h"
#include "bt_hci_log.h"


#include <zephyr/logging/log.h>
#define thisMODULE btd_relay
LOG_MODULE_REGISTER(thisMODULE);

#define HCI_FROM_HOST         0
#define HCI_FROM_CONTROLLER   1


typedef struct _bt_connection_t {
    bt_linknode_t next_node;
    bt_handle_t handle;
    bt_tx_queue_t tx_con_queue;
    bt_role_t   role;
    void *conn_ind_buffer;
    uint8_t support_features[8];
    bool is_connected;
} bt_connection_t;


typedef struct {
    uint32_t (*read_data)(uint8_t *buf, uint32_t buf_len, uint32_t offset);/**< Uart port read data function pointer. */
    uint32_t (*write_data)(uint8_t *buf, uint32_t buf_len);                /**< Uart port write data function pointer. */
    uint8_t (*init)(uint8_t port);                                         /**< Uart port init function pointer. */
    uint8_t (*deinit)(void);                                               /**< Uart port deinit function pointer. */
} bt_driver_relay_callbacks;

bt_connection_t acl_conn;


extern void *bt_memcpy(void *dest, const void *src, uint32_t size);
extern void bt_driver_deinit_relay_mode(void);
extern bt_status_t bt_driver_send_reset_and_tx_pwr_config_cmd(void);
extern bt_status_t bt_driver_send_with_pending_response(const void *packet, uint32_t length);
extern bt_status_t bt_driver_power_on(void);


static uint8_t bt_driver_relay_enabled = 0;
static uint8_t bt_driver_relay_enable_complete = 0;
static uint8_t *bt_driver_relay_rx_buf = NULL;
static uint8_t *bt_driver_relay_tx_buf = NULL;
bool bt_driver_enter_relay_mode(uint8_t port);
extern bt_status_t bt_driver_power_off(void);
#ifdef __BT_LE_AUDIO_ENABLE__
static bt_tx_queue_t bt_mm_iso_queue_temp;
bt_tx_queue_t *bt_mm_iso_queue_p = NULL;
#endif  //__BT_LE_AUDIO_ENABLE__

#ifdef __BT_SLT_TEST__
typedef void (*bt_slt_test_cb)(uint8_t result);
static bt_slt_test_cb bt_driver_slt_test_cb = NULL;

bool bt_driver_slt_test_enable(uint8_t port, void *result_callback)
{
    /*check callback received slt test result*/
    if (result_callback == NULL) {
       // BT_DRVLOG_MSGID_E("BTIF", BTIF_226, 0);
        return false;
    }
    bt_driver_slt_test_cb = (bt_slt_test_cb)result_callback;
    /*enable relay mode*/
    if (!bt_driver_enter_relay_mode(port)) {
       // BT_DRVLOG_MSGID_E("BTIF", BTIF_227, 0);
        return false;
    }
    return true;
}
#endif

bool bt_driver_is_relay_mode_enabled(void)
{
    return (bt_driver_relay_enabled == 1);
}

bool bt_driver_is_relay_mode_enable_complete(void)
{
    return (bt_driver_relay_enable_complete == 1);
}

uint8_t *bt_driver_get_relay_tx_buffer(void)
{
    return bt_driver_relay_tx_buf;
}

uint8_t *bt_driver_get_relay_rx_buffer(void)
{
    return bt_driver_relay_rx_buf;
}

bt_driver_relay_callbacks bt_driver_relay_cb;

void bt_driver_relay_register_callbacks(void *callback)
{
    bt_memcpy(&bt_driver_relay_cb, (bt_driver_relay_callbacks *)callback, sizeof(bt_driver_relay_callbacks));
}

#define BT_HCI_PACKET_ACL_SIZE_2(p)   (*(uint16_t *)((uint8_t *)(p)+2)+BT_HCI_ACL_HEADER_LENGTH)
#define BT_HCI_PACKET_CMD_SIZE_2(p)   (*(uint8_t *)((uint8_t *)(p)+2)+BT_HCI_CMD_HEADER_LENGTH)

void bt_driver_avm_send(uint16_t payload_size, uint8_t * packet, uint8_t HCI_pcket_type, bt_hb_queue_type_t qType)
{
    bt_hci_le_packet_t *send_packet = NULL;

    bt_hb_queue_type_t queue_type = qType;
    uint8_t *queue_header = NULL;

    uint16_t total_payload_size = 0;

    if (HCI_pcket_type == BT_UART_CMD) {
        total_payload_size = BT_HCI_PACKET_CMD_SIZE_2(packet);
    } else if (HCI_pcket_type == BT_UART_ACL) {
        total_payload_size = BT_HCI_PACKET_ACL_SIZE_2(packet);
    }

    BT_LOGD("AVM","total_payload_size = %u,  payload_size  = %u,HCI_pcket_type = %d,  queue_type = %d \n"
        , total_payload_size
        , payload_size
        , HCI_pcket_type
        , queue_type);

    send_packet = BT_HCI_PKT_ALLOC(total_payload_size +1);


    BT_LOGD("AVM","bt_driver_avm_send,  send_packet @ 0x%02X, qType = %d \n", (unsigned int)send_packet, queue_type);
    BT_LOGD("AVM","??? BT_QUEUE_TX_ALL->front = %p,  BT_QUEUE_TX_ALL = %p \n", BT_QUEUE_TX_ALL->front , BT_QUEUE_TX_ALL);


    if (!BT_IS_ALLOCATED_PACKET_VALID(send_packet)) {
        //BT_DRVLOG_MSGID_I("BTIF", BTIF_156, 0);
        return;
    }

    *((uint8_t *)send_packet) = HCI_pcket_type;

    bt_memcpy( ((uint8_t *)send_packet)+1, packet, total_payload_size);

    bt_hci_log(HCI_FROM_HOST, send_packet, total_payload_size);


    if (HCI_pcket_type == BT_UART_CMD) {
        BT_LOGI("AVM"," send_packet = 0x%02X-%02X-%02X-%02X   %02X-%02X   %02X-%02X\n"
            , *(((uint8_t *)send_packet)+0)
            , *(((uint8_t *)send_packet)+1)
            , *(((uint8_t *)send_packet)+2)
            , *(((uint8_t *)send_packet)+3)
            , *(((uint8_t *)send_packet)+4)
            , *(((uint8_t *)send_packet)+5)
            , *(((uint8_t *)send_packet)+6)
            , *(((uint8_t *)send_packet)+7)
            );
    }
    else if (HCI_pcket_type == BT_UART_ACL) {
        BT_LOGI("AVM"," send_packet = HCI ACL(%X), ConnHdl = 0x%04X , len = %d,  L2CAP len= 0x%04X , L2CAP ch = 0x%04X, ATT opcode = 0x%X, 0x%02X-0x%02X \n"
            , *(((uint8_t *)send_packet)+0)
            , *(((uint16_t *)send_packet)+1)
            , *(((uint16_t *)send_packet)+3)
            , *(((uint16_t *)send_packet)+5)
            , *(((uint16_t *)send_packet)+7)
            , *(((uint8_t *)send_packet)+9)
            , *(((uint8_t *)send_packet)+10)
            , *(((uint8_t *)send_packet)+7)
            );
    }

    //bt_hci_log(0, send_packet, total_payload_size);

    #ifdef NO_TEMP_REMOVE_BY_RELAY_MODE
    bt_driver_hw_semaphore_lock();
    #endif

    /*In relay mode will not use hci layer, so push ACL into IF queue*/
    if (queue_type == BT_QUEUE_TYPE_TX_ACL || queue_type == BT_QUEUE_TYPE_TX_IF_PACKET) {
        BT_QUEUE_PUSH_BACK(BT_QUEUE_TX_IF_PACKET, BT_GET_NODE_FROM_PACKET(send_packet));
        queue_header = (uint8_t *)Bt_QUEUE_TX_IF_PACKET_NODE;
    } else if (queue_type == BT_QUEUE_TYPE_TX_CMD) {
        BT_QUEUE_PUSH_BACK(BT_QUEUE_TX_CMD, BT_GET_NODE_FROM_PACKET(send_packet));
        queue_header = (uint8_t *)BT_QUEUE_TX_CMD_NODE;
    }

#ifdef NO_TEMP_REMOVE_BY_RELAY_MODE
    bt_driver_hw_semaphore_unlock();
#endif

    //bt_driver_tx_notify_controller(queue_type, queue_header);
    BT_LOGD("AVM","prepare to send data ========");
    bt_tx_notify_pka(queue_type, queue_header);
    BT_LOGD("AVM","send data End ========");
}



static uint32_t read_size = 0;
void bt_driver_handle_relay_port_data(void)
{
//    BT_DRVLOG_MSGID_I("BTIF", BTIF_147, 0);
    //int i = 0;
    uint32_t cur_pos = 0;
    uint32_t current_read_size = 0;
    uint32_t total_payload_size = 0;
    uint32_t remaining_size = 0;
    bt_hci_le_packet_t *packet = NULL;
    bt_hci_le_packet_t *send_packet = NULL;
    bt_hb_queue_type_t queue_type = BT_QUEUE_TYPE_TX_CMD;
    uint8_t *queue_header = NULL;



    //BT_LOGI("BT","bt_driver_handle_relay_port_data \n");

    bt_memset(bt_driver_relay_rx_buf, 0x00, RELAY_BUFFER_SIZE);
    do {
        current_read_size = bt_driver_relay_cb.read_data(bt_driver_relay_rx_buf, RELAY_BUFFER_SIZE, read_size);
        read_size += current_read_size;
        if (current_read_size) {
            LOG_ERR("start--------");
            uint32_t i = 0;
            for (i = 0; i < current_read_size; i++) {
                LOG_ERR("%x",bt_driver_relay_rx_buf[i]);
            }
            LOG_ERR("----end--------");
        }
        //BT_LOGI("BT","Current data len: %d", current_read_size);
    } while (0);


#ifdef __BT_SLT_TEST__
    {
        bool bt_driver_is_end_signal = true;
        uint8_t i;
        LOG_ERR("tool result>");
        if (read_size == 2) {//FAIL, if 2 0xff is fail
            for (i = 0; i < read_size; i++) {
                LOG_ERR("%02x", bt_driver_relay_rx_buf[i]);
                if (bt_driver_relay_rx_buf[i] != 0xFF) {
                    bt_driver_is_end_signal = false;
                }
            }
            if (bt_driver_is_end_signal && (bt_driver_slt_test_cb != NULL)) {
                bt_driver_slt_test_cb(0x00);
                read_size = 0;
            }
        } else if (read_size == 3) {// PASS, if 3 0xff is success
            for (i = 0; i < read_size; i++) {
                if (bt_driver_relay_rx_buf[i] != 0xFF) {
                    bt_driver_is_end_signal = false;
                }
            }
            if (bt_driver_is_end_signal && (bt_driver_slt_test_cb != NULL)) {
                bt_driver_slt_test_cb(0x01);
                read_size = 0;
            }
        }
    }
#endif /*__BT_SLT_TEST__*/

    LOG_ERR("read_size = %d, cur_pos = %d \n", read_size, cur_pos);

    while (read_size > cur_pos) {
        remaining_size = read_size - cur_pos;
        packet = (bt_hci_le_packet_t *)(bt_driver_relay_rx_buf + cur_pos);
        send_packet = NULL;
        LOG_ERR("read_size > cur_pos");
        if (packet->indicator == BT_UART_CMD) {
            LOG_ERR("CMD data");
            if (remaining_size < BT_HCI_CMD_HEADER_LENGTH) {
                LOG_ERR("remaining_size < cmd Header length");
                break;
            }
            LOG_ERR("remaining_size = %d \n", remaining_size);
            total_payload_size = BT_HCI_PACKET_CMD_SIZE(packet);
            LOG_ERR("total_payload_size = %d \n", total_payload_size);

            queue_type = BT_QUEUE_TYPE_TX_CMD;
            LOG_ERR("queue_type = %d \n", queue_type);

        } else if (packet->indicator == BT_UART_ACL) {
            LOG_ERR("ACL data");
            if (remaining_size < BT_HCI_ACL_HEADER_LENGTH) {
                LOG_ERR("remaining_size < acl Header length");
                break;
            }
            total_payload_size = BT_HCI_PACKET_ACL_SIZE(packet);
            queue_type = BT_QUEUE_TYPE_TX_ACL;


        } else {
            LOG_ERR("Indicator is %d", packet->indicator);
            return;
        }
        LOG_ERR("Total payload size is %d", total_payload_size);

        #if 1
        /*disassemblely packet*/
        if (cur_pos + total_payload_size > read_size) {
            bt_memcpy(bt_driver_relay_rx_buf, bt_driver_relay_rx_buf +
                      cur_pos, remaining_size);
            LOG_ERR("cur_pos + total_payload_size > read_size");
            read_size -= cur_pos;
            break;
        }
        #endif


        cur_pos += total_payload_size;
        if (cur_pos == read_size) {
            read_size = 0;
        }


        //BT_DRVLOG_MSGID_I("BTIF", BTIF_155, 1, read_size);
        send_packet = BT_HCI_PKT_ALLOC(total_payload_size);

        LOG_ERR("send_packet = 0x%x \n", (unsigned int)send_packet);


        if (!BT_IS_ALLOCATED_PACKET_VALID(send_packet)) {
            //BT_DRVLOG_MSGID_I("BTIF", BTIF_156, 0);
            return;
        }

        bt_memcpy(send_packet, packet, total_payload_size);
        bt_hci_log(0, send_packet, total_payload_size);

        #ifdef NO_TEMP_REMOVE_BY_RELAY_MODE
        bt_driver_hw_semaphore_lock();
        #endif



        /*In relay mode will not use hci layer, so push ACL into IF queue*/
        if (queue_type == BT_QUEUE_TYPE_TX_ACL || queue_type == BT_QUEUE_TYPE_TX_IF_PACKET) {
            BT_QUEUE_PUSH_BACK(BT_QUEUE_TX_IF_PACKET, BT_GET_NODE_FROM_PACKET(send_packet));
            queue_header = (uint8_t *)Bt_QUEUE_TX_IF_PACKET_NODE;
        } else if (queue_type == BT_QUEUE_TYPE_TX_CMD) {
            BT_QUEUE_PUSH_BACK(BT_QUEUE_TX_CMD, BT_GET_NODE_FROM_PACKET(send_packet));
            queue_header = (uint8_t *)BT_QUEUE_TX_CMD_NODE;
        }



        #ifdef NO_TEMP_REMOVE_BY_RELAY_MODE
        bt_driver_hw_semaphore_unlock();
        #endif

        //bt_driver_tx_notify_controller(queue_type, queue_header);
        LOG_ERR("prepare to send data ========");
        bt_tx_notify_pka(queue_type, queue_header);
        LOG_ERR("send data End ========");
    }

    return;
}



#define BT_TX_BUF_SIZE 256*10
#define BT_RX_BUF_SIZE 256*10

ATTR_ZIDATA_IN_TCM_NONE_RETENTION ATTR_ALIGN(4) static char tx_buf[BT_TX_BUF_SIZE];

ATTR_ZIDATA_IN_TCM_NONE_RETENTION ATTR_ALIGN(4) static char rx_buf[BT_RX_BUF_SIZE];

extern void  bt_memory_init_packet(bt_memory_packet_t type, char *buf, uint32_t size);

bool bt_hci_cmp_by_tx_queue(const bt_linknode_t *node, const void *tx_queue_node)
{
    return (node == (bt_linknode_t *)tx_queue_node);
}

void bt_driver_memory_init(void)
{
    bt_memory_init_packet(BT_MEMORY_TX_BUFFER, tx_buf, BT_TX_BUF_SIZE);
    bt_memory_init_packet(BT_MEMORY_RX_BUFFER, rx_buf, BT_RX_BUF_SIZE);
}

bool bt_driver_avm_init()
{
    BT_LOGI("AVM","bt_driver_enter_relay_mode, RELAY_BUFFER_SIZE = %d \n", RELAY_BUFFER_SIZE );

    bt_driver_memory_init();

    BT_LOGI("AVM","tx_buf @[%p ~ %p] \n",tx_buf, tx_buf +  RELAY_BUFFER_SIZE );
    BT_LOGI("AVM","rx_buf @[%p ~ %p] \n",rx_buf, rx_buf +  RELAY_BUFFER_SIZE );

    BT_LOGD("AVM"," BT_QUEUE_TX_CMD = 0x%x\n", (unsigned int)BT_QUEUE_TX_CMD);
    BT_LOGD("AVM"," BT_QUEUE_TX_ALL = 0x%x\n", (unsigned int)BT_QUEUE_TX_ALL);
    BT_LOGD("AVM"," BT_QUEUE_TX_CMD_NODE = 0x%x\n", (unsigned int)BT_QUEUE_TX_CMD_NODE);
    BT_LOGD("AVM"," BT_QUEUE_TX_IF_PACKET = 0x%x\n", (unsigned int)BT_QUEUE_TX_IF_PACKET);
    BT_LOGD("AVM"," Bt_QUEUE_TX_IF_PACKET_NODE = 0x%x\n", (unsigned int)Bt_QUEUE_TX_IF_PACKET_NODE);

    bt_linknode_t *queue_header = NULL;
    bt_linknode_t * tx_queue_to_find = NULL;

    // init TX_ALL_QUEUE
    bt_driver_hw_semaphore_lock();
    BT_QUEUE_TX_CMD->front = NULL;
    BT_QUEUE_TX_ALL->front = BT_QUEUE_TX_ALL;
    BT_QUEUE_TX_CMD_NODE->front = NULL;

    queue_header = (bt_linknode_t *)BT_QUEUE_TX_ALL;
    tx_queue_to_find = bt_linknode_travel_node(queue_header, bt_hci_cmp_by_tx_queue, BT_QUEUE_TX_CON_NODE(&acl_conn));
    BT_ASSERT(tx_queue_to_find == NULL && "Repeat to create the same queue");
    BT_QUEUE_PUSH_FRONT(queue_header, BT_QUEUE_TX_CON_NODE(&acl_conn));

    bt_driver_hw_semaphore_unlock();

    BT_LOGI("AVM","bt_driver_power_on start..................................... \n");
    bt_driver_power_on();
    BT_LOGI("AVM","bt_driver_enter_relay_mode End \n\n");

    return true;
}

bool bt_driver_enter_relay_mode(uint8_t port)
{
    LOG_ERR("bt_driver_enter_relay_mode, RELAY_BUFFER_SIZE = %d \n", RELAY_BUFFER_SIZE );

    static const uint8_t set_fixed_bt_addr_cmd[] = {0x01, 0x1a, 0xfc, 0x06, 0x01, 0x61, 0x67, 0x46, 0x00, 0x00}; /*fixed bt addr(reverse):00:00:46:67:61:01*/
    static const uint8_t change_local_name_cmd[] = {0x01, 0x13, 0x0c, 0x0e, 'B', 'l', 'u', 'e', 't', 'o', 'o', 't', 'h', ' ', 'D', 'T', 'M', '\0'}; /*Bluetooth DTM*/
    //static const uint8_t write_extended_inquiry_response[0xF5] = {0x01, 0x52, 0x0c, 0xF1,
    //                                                       0x01, 0x11, 0x06, 0x1d, 0x23, 0xbb, 0x1b, 0x00, 0x00, 0x10, 0x00, 0x30, 0x00, 0x50, 0x80, 0x5f, 0x9b, 0x34, 0xfa,
    //                                                       0x0f, 0x09, 'B', 'l', 'u', 'e', 't', 'o', 'o', 't', 'h', ' ', 'D', 'T', 'M', '\0'
    //                                                      };
    const uint8_t read_bd_addr[] = {0x01, 0x09, 0x10, 0x00};                   /*read bd address*/

    if (bt_driver_relay_enabled && bt_driver_relay_enable_complete) {
        return true;
    }
    bt_memory_init_packet(BT_MEMORY_TX_BUFFER, tx_buf, BT_TX_BUF_SIZE);
    bt_memory_init_packet(BT_MEMORY_RX_BUFFER, rx_buf, BT_RX_BUF_SIZE);

    bt_driver_relay_enabled = 1;
    bt_driver_relay_tx_buf = (uint8_t *)bt_mm_allocate_packet(BT_MEMORY_TX_BUFFER, RELAY_BUFFER_SIZE);
    bt_driver_relay_rx_buf = (uint8_t *)bt_mm_allocate_packet(BT_MEMORY_RX_BUFFER, RELAY_BUFFER_SIZE);

    BT_LOGI("BT","bt_driver_relay_tx_buf = 0x%x, bt_driver_relay_rx_buf = 0x%x \n", (unsigned int)bt_driver_relay_tx_buf, (unsigned int)bt_driver_relay_rx_buf);

    BT_ASSERT(bt_driver_relay_tx_buf && "tx relay oom, please keep 2K bytes.");
    BT_ASSERT(bt_driver_relay_rx_buf && "rx relay oom, please keep 2K bytes.");
    bt_memset(bt_driver_relay_tx_buf, 0, RELAY_BUFFER_SIZE);
    bt_memset(bt_driver_relay_rx_buf, 0, RELAY_BUFFER_SIZE);

    BT_LOGI("BT"," BT_QUEUE_TX_CMD = 0x%x\n", (unsigned int)BT_QUEUE_TX_CMD);
    BT_LOGI("BT"," BT_QUEUE_TX_ALL = 0x%x\n", (unsigned int)BT_QUEUE_TX_ALL);
    BT_LOGI("BT"," BT_QUEUE_TX_CMD_NODE = 0x%x\n", (unsigned int)BT_QUEUE_TX_CMD_NODE);
    BT_LOGI("BT"," BT_QUEUE_TX_IF_PACKET = 0x%x\n", (unsigned int)BT_QUEUE_TX_IF_PACKET);
    BT_LOGI("BT"," Bt_QUEUE_TX_IF_PACKET_NODE = 0x%x\n", (unsigned int)Bt_QUEUE_TX_IF_PACKET_NODE);
    // init TX_ALL_QUEUE
    bt_driver_hw_semaphore_lock();


    BT_QUEUE_TX_CMD->front = NULL;
    BT_QUEUE_TX_ALL->front = BT_QUEUE_TX_ALL;
    BT_QUEUE_TX_CMD_NODE->front = NULL;
 //   BT_QUEUE_TX_IF_PACKET->front = NULL;
 //   Bt_QUEUE_TX_IF_PACKET_NODE->front = NULL;



#ifdef __BT_LE_AUDIO_ENABLE__
    bt_mm_iso_queue_p = &bt_mm_iso_queue_temp;
    BT_QUEUE_TX_ISO->front = NULL;
    BT_QUEUE_TX_ISO_NODE->front = NULL;
#endif //__BT_LE_AUDIO_ENABLE__
    bt_driver_hw_semaphore_unlock();

    bt_driver_power_on();


    if (BT_STATUS_SUCCESS != bt_driver_send_reset_and_tx_pwr_config_cmd()) {
        bt_driver_deinit_relay_mode();

        //BT_DRVLOG_MSGID_E("BTIF", BTIF_163, 0);
        return false;
    }

    if (BT_STATUS_SUCCESS != bt_driver_send_with_pending_response(set_fixed_bt_addr_cmd, sizeof(set_fixed_bt_addr_cmd))) {
        return BT_STATUS_FAIL;
    } else if (BT_STATUS_SUCCESS != bt_driver_send_with_pending_response(change_local_name_cmd, sizeof(change_local_name_cmd))) {
        return BT_STATUS_FAIL;
    }

    //else if (BT_STATUS_SUCCESS != bt_driver_send_with_pending_response(write_extended_inquiry_response, sizeof(write_extended_inquiry_response))) {
    //    return BT_STATUS_FAIL;
    //}
    else if (BT_STATUS_SUCCESS != bt_driver_send_with_pending_response(read_bd_addr, sizeof(read_bd_addr))) {
        return BT_STATUS_FAIL;
    }

    if (0 != bt_driver_relay_cb.init(port)) {
        bt_driver_deinit_relay_mode();
        return false;
    }

    bt_driver_relay_enable_complete = 1;

    //bt_device_mode_t last_mode = BT_NORMAL_MODE;
    //bt_app_event_callback(BT_TEST_MODE_RELAY_ENABLE_IND, BT_STATUS_SUCCESS, NULL);
    LOG_ERR("bt_driver_enter_relay_mode End \n\n");

    return true;
}

void bt_driver_deinit_relay_mode(void)
{
    bt_driver_relay_enabled = 0;
    bt_driver_relay_enable_complete = 0;
    bt_driver_power_off();
    if (bt_driver_relay_tx_buf) {
        bt_mm_free_packet(BT_MEMORY_TX_BUFFER, (char *)bt_driver_relay_tx_buf);
        bt_driver_relay_tx_buf = NULL;
    }
    if (bt_driver_relay_rx_buf) {
        bt_mm_free_packet(BT_MEMORY_RX_BUFFER, (char *)bt_driver_relay_rx_buf);
        bt_driver_relay_rx_buf = NULL;
    }
    bt_driver_relay_cb.deinit();

    //bt_device_mode_t last_mode = BT_RELAY_MODE;
}



void bt_driver_relay_cb_write_data(uint8_t *buf, uint32_t buf_len)
{
    bt_driver_relay_cb.write_data(buf, buf_len);
}

