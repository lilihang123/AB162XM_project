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
#include "avm_external.h"
#include "bt_linknode.h"
#include "avm_memory.h"
#include "bt_debug.h"
#include "bt_common_upper_layer.h"

#include <zephyr/logging/log.h>
#include "bt_hci_log.h"

#define thisMODULE bt_misc
LOG_MODULE_REGISTER(thisMODULE);



#if 0
const bt_hci_sleep_mode_param_t bt_hci_enable_sleep_mode = {
    .mode = BT_HCI_SLEEP_3_PIN,
    .duration = 0x1F40,
    .host_duration = 0x1F40,
    .wakeup_pin = 0x00,
    .time_comp = 0x02,
};
#endif 


#pragma weak bt_driver_is_relay_mode_enabled = default_bt_driver_is_relay_mode_enabled
#pragma weak bt_driver_is_relay_mode_enable_complete = default_bt_driver_is_relay_mode_enable_complete

extern bool bt_driver_is_relay_mode_enabled(void);
extern bool bt_driver_is_relay_mode_enable_complete(void);
extern void bt_driver_tx_notify_controller(bt_hb_queue_type_t type, uint8_t *q_header);

extern void bt_driver_relay_cb_write_data(uint8_t *buf, uint32_t buf_len);


uint8_t *bt_driver_get_relay_tx_buffer(void);


bool default_bt_driver_is_relay_mode_enabled(void)
{
    return 0;
}

bool default_bt_driver_is_relay_mode_enable_complete(void)
{
    return 0;
}

void *bt_memcpy(void *dest, const void *src, uint32_t size)
{
    return memcpy(dest, src, size);
}

int bt_memcmp(const void *buf1, const void *buf2, uint32_t size)
{
    return memcmp(buf1, buf2, size);
}

void *bt_memset(void *buf, uint8_t ch, uint32_t size)
{
    return memset(buf, ch, size);
}



void bt_driver_set_no_retransmission_mode(uint16_t seq_num, uint16_t length)
{
    bt_pka_set_no_retransmission_mode(seq_num, length);
}

bool bt_driver_is_queue_empty(uint8_t *queue_header)
{
    BT_ASSERT(queue_header != NULL);
    BT_LOGD(GROUP_BT_DRIVER, "bt_driver_is_queue_empty queue header addr \n" );

    bt_driver_hw_semaphore_lock();
    if (BT_QUEUE_EMPTY((bt_linknode_t *)queue_header)) {
        BT_LOGD(GROUP_BT_DRIVER,"queue empty\n");
        bt_driver_hw_semaphore_unlock();
        return true;
    }
    bt_driver_hw_semaphore_unlock();
    return false;
}

void *bt_driver_rx_dequeue(void)
{
    BT_LOGD(GROUP_BT_DRIVER,"bt_driver_rx_dequeue\n");
    bt_hci_le_packet_t *packet = NULL;

    bt_driver_hw_semaphore_lock();
    BT_ASSERT(BT_QUEUE_RX->front);
    packet = (bt_hci_le_packet_t *)BT_GET_PACKET_FROM_NODE(BT_QUEUE_POP_FRONT(BT_QUEUE_RX));
    bt_driver_hw_semaphore_unlock();
    return (void *)packet;
}

void bt_driver_clear_queue(bt_hb_queue_type_t type)
{
    bt_hci_le_packet_t *packet = NULL;
    bt_linknode_t *queue = NULL;
    if (type == BT_QUEUE_TYPE_TX_ACL) {
        if (BT_QUEUE_TX_ALL->front != BT_QUEUE_TX_ALL) {
            bt_tx_queue_t *tx_queue = (bt_tx_queue_t *)(BT_QUEUE_TX_ALL->front);
            if (NULL == tx_queue) {
                return;
            }
            do {
                while (!BT_QUEUE_EMPTY(&tx_queue->queue)) {
                    packet = (bt_hci_le_packet_t *)BT_GET_PACKET_FROM_NODE(BT_QUEUE_POP_FRONT(&tx_queue->queue));
                    BT_ASSERT(packet && BT_IS_ALLOCATED_PACKET_VALID(packet));
                    BT_FREE_PACKET_WITH_NODE(BT_MEMORY_TX_BUFFER, packet);
                }
                tx_queue = (bt_tx_queue_t *)tx_queue->next_node.front;
            } while ((bt_linknode_t *)tx_queue != (bt_linknode_t *)BT_QUEUE_TX_ALL);
        }
    } else {
        if (type == BT_QUEUE_TYPE_TX_CMD) {
            queue = BT_QUEUE_TX_CMD;
        } else if (type == BT_QUEUE_TYPE_TX_IF_PACKET) {
            queue = BT_QUEUE_TX_IF_PACKET;
        } else if (type == BT_QUEUE_TYPE_RX) {
            queue = BT_QUEUE_RX;
        }
        while (!BT_QUEUE_EMPTY(queue)) {
            packet = (bt_hci_le_packet_t *)BT_GET_PACKET_FROM_NODE(BT_QUEUE_POP_FRONT(queue));
            BT_ASSERT(packet && BT_IS_ALLOCATED_PACKET_VALID(packet));
            if (type == BT_QUEUE_TYPE_RX) {
                BT_FREE_PACKET_WITH_NODE(BT_MEMORY_RX_BUFFER, packet);
            } else {
                BT_FREE_PACKET_WITH_NODE(BT_MEMORY_TX_BUFFER, packet);
            }
        }
    }
}

static uint8_t bt_driver_cmd_complete_flag = 0;

bt_status_t bt_driver_send_with_pending_response(const void *packet, uint32_t length)
{
//    uint8_t pollPeriod = 1;
//    uint32_t timer = 0;
    uint32_t total_payload_size = 0;
    bt_hci_le_packet_t *send_packet = NULL;

    BT_LOGD(GROUP_BT_DRIVER, "bt_driver_send_with_pending_response packet length = %d", length);

    if (NULL == packet) {
        return BT_STATUS_FAIL;;
    }
    

    //BT_DRVLOG_MSGID_I("BTIF", BTIF_120, 0);
    //bt_hci_log(0, packet, length);
    total_payload_size = BT_HCI_PACKET_CMD_SIZE(packet);
    send_packet = BT_HCI_CMD_ALLOC(total_payload_size);

    BT_LOGHEX(GROUP_BT_DRIVER,"HCI CMD ", (uint8_t*)packet,  length);

    BT_LOGD(GROUP_BT_DRIVER, "HCI CMD = %02x, %02x, %02x, %02x, total_payload_size = %d,   \n", *((uint8_t*)packet+0),*((uint8_t*)packet+1),*((uint8_t*)packet+2),*((uint8_t*)packet+3) , total_payload_size);
    BT_LOGD(GROUP_BT_DRIVER, "send_packet = %p,  NODE_FROM_PACKET = %p , sizeof(bt_hci_packet_linknode_t) = %d\n", send_packet, BT_GET_NODE_FROM_PACKET(send_packet), sizeof(bt_hci_packet_linknode_t) );

    if (!BT_IS_ALLOCATED_PACKET_VALID(send_packet)) {
        BT_LOGD(GROUP_BT_DRIVER, " line = %d \n", __LINE__ );
        //BT_DRVLOG_MSGID_E("BTIF", BTIF_121, 0);        
        return BT_STATUS_FAIL;
    }

    bt_memcpy(send_packet, packet, total_payload_size);
    bt_driver_hw_semaphore_lock();
    BT_QUEUE_PUSH_BACK(BT_QUEUE_TX_CMD, BT_GET_NODE_FROM_PACKET(send_packet));


//#define BT_GET_NODE_FROM_PACKET(ptr)                ((bt_linknode_t*) ((char *)(ptr) - sizeof(bt_hci_packet_linknode_t)) )
//#define BT_QUEUE_POP_FRONT(q)       (bt_linknode_remove_node(q, BT_NODE_FRONT))
//#define BT_QUEUE_POP_BACK(q)        (bt_linknode_remove_node(q, BT_NODE_BACK))
//#define BT_QUEUE_PUSH_FRONT(q,item) (bt_linknode_insert_node(q, (item), BT_NODE_FRONT))
//#define BT_QUEUE_PUSH_BACK(q, item) (bt_linknode_insert_node(q, (item), BT_NODE_BACK))


    bt_driver_hw_semaphore_unlock();
    bt_driver_cmd_complete_flag = 0;

    BT_LOGD( GROUP_BT_DRIVER ," Start =================\n..\n");
    bt_driver_tx_notify_controller(BT_QUEUE_TYPE_TX_CMD, (uint8_t *)BT_QUEUE_TX_CMD_NODE);
    BT_LOGD(GROUP_BT_DRIVER , " End =================\n..\n");

#if 0
    // wait for response,
    while (!bt_driver_cmd_complete_flag) {
////        bt_os_layer_sleep_task(pollPeriod);
        //timer += pollPeriod;
        if (timer >= BT_DRIVER_MAX_PENDING_TIME) {
            BT_DRVLOG_MSGID_I("BTIF", BTIF_122, 0);
            return BT_STATUS_FAIL;
        }
    }
#endif    

    BT_LOGD(GROUP_BT_DRIVER, "bt_driver_send_with_pending_response END **********\n");

    // check response
    //    while (!bt_driver_is_queue_empty((uint8_t *)BT_QUEUE_RX)) {
    //        bt_hci_le_packet_t *recv_packet = (bt_hci_le_packet_t *)bt_driver_rx_dequeue();
    //        BT_ASSERT(recv_packet && BT_IS_ALLOCATED_PACKET_VALID(recv_packet));
    //        BT_ASSERT(recv_packet->indicator == BT_UART_ACL || recv_packet->indicator == BT_UART_EVT);
    //        BT_FREE_PACKET_WITH_NODE(BT_MEMORY_RX_BUFFER, recv_packet);
    //    }
    return BT_STATUS_SUCCESS;
}

void bt_driver_handle_test_mode_rsp(void)
{
    /*notify the cmd is complete*/
    bt_driver_cmd_complete_flag = 1;

    BT_LOGD(GROUP_BT_DRIVER, "bt_driver_handle_test_mode_rsp \n");
    
    while (!bt_driver_is_queue_empty((uint8_t *)BT_QUEUE_RX)) {

        bt_hci_le_packet_t *packet = (bt_hci_le_packet_t *)bt_driver_rx_dequeue();
        BT_ASSERT(packet && BT_IS_ALLOCATED_PACKET_VALID(packet));
        BT_ASSERT(/*BT_UART_ACL == packet->indicator || */ BT_UART_EVT == packet->indicator);
        //bt_hci_log(1, packet, BT_HCI_PACKET_EVT_SIZE(packet));
        //if (BT_UART_EVT == packet->indicator) {
        if (BT_HCI_EVT_COMMAND_COMPLETE == packet->evt.evt_code &&
                BT_HCI_CMD_RESET == BT_HCI_LE_PACKET_TO_EVENT(bt_hci_evt_command_complete_t, packet)->cmd_code) {
            //BT_DRVLOG_MSGID_I("BTIF", BTIF_219, 0);
        }
#if 0        
        if (BT_HCI_EVT_COMMAND_COMPLETE == packet->evt.evt_code &&
            BT_HCI_CMD_ENABLE_DUT == BT_HCI_LE_PACKET_TO_EVENT(bt_hci_evt_command_complete_t, packet)->cmd_code) {
            bt_app_event_callback(BT_TEST_MODE_DUT_ONLY_ENABLE_IND, BT_STATUS_SUCCESS, NULL);
        } 
#endif
        BT_FREE_PACKET_WITH_NODE(BT_MEMORY_RX_BUFFER, packet);
    }

    BT_LOGI(GROUP_BT_DRIVER, "bt_driver_handle_test_mode_rsp End \n");
    //BT_DRVLOG_MSGID_I("BTIF", BTIF_107, 0);

}

bt_status_t bt_driver_send_reset_and_tx_pwr_config_cmd(void)
{
    bt_status_t bRet = BT_STATUS_SUCCESS;
    const uint8_t reset_cmd[] = {0x01, 0x03, 0x0c, 0x00}; /*reset_cmd*/

    BT_LOGD(GROUP_BT_DRIVER, "..\n..\n..\n bt_driver_send_reset_and_tx_pwr_config_cmd line \n"  );

    bRet = bt_driver_send_with_pending_response(reset_cmd, sizeof(reset_cmd));
    if (BT_STATUS_SUCCESS != bRet) {
        return BT_STATUS_FAIL;
    }
    const uint8_t empty_tx_power_config[10] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    uint8_t *tx_power_config_table = bt_driver_get_tx_power_config_table();
    /*TX power was configed before*/
    BT_ASSERT(tx_power_config_table);
    if (bt_memcmp(tx_power_config_table, empty_tx_power_config, sizeof(empty_tx_power_config))) {
        /*set_tx_power_cmd*/
        uint8_t set_tx_power_cmd[] = {0x01, 0xbb, 0xfd, 0x0a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
        bt_memcpy(set_tx_power_cmd + 4, tx_power_config_table, sizeof(empty_tx_power_config));

        bRet = bt_driver_send_with_pending_response(set_tx_power_cmd, sizeof(set_tx_power_cmd));
        if (BT_STATUS_SUCCESS != bRet) {            
            return BT_STATUS_FAIL;
        }
        //BT_DRVLOG_MSGID_I("BTIF", BTIF_223, 0);
    }
    return BT_STATUS_SUCCESS;
}

bt_status_t bt_driver_send_hci_cmd(const bt_hci_cmd_t *cmd, uint32_t data, bt_timeout_callback_t callback)
{
    BT_ASSERT(cmd && cmd->cmd_code);
    uint32_t total_packet_len = cmd->length + BT_HCI_CMD_HEADER_LENGTH;

    bt_hci_le_packet_t *packet = BT_HCI_CMD_ALLOC(total_packet_len);
    if (!BT_IS_ALLOCATED_PACKET_VALID(packet)) {
        return BT_STATUS_OUT_OF_MEMORY;
    }

    packet->indicator = BT_UART_CMD;
    packet->cmd.cmd_code = cmd->cmd_code;
    packet->cmd.length = cmd->length;
    if (cmd->length) {
        bt_memcpy((void *)packet->cmd.param, cmd->param, cmd->length);
    }
    bt_hci_log(0, packet, BT_HCI_PACKET_CMD_SIZE(packet));
    bt_driver_hw_semaphore_lock();
    BT_QUEUE_PUSH_BACK(BT_QUEUE_TX_CMD, BT_GET_NODE_FROM_PACKET(packet));
    bt_driver_hw_semaphore_unlock();
    bt_tx_notify_pka(BT_QUEUE_TYPE_TX_CMD, (uint8_t *)BT_QUEUE_TX_CMD_NODE);

    return BT_STATUS_SUCCESS;
}


/*For bt_memory.c, get controller extra packet size*/
uint32_t bt_driver_get_mm_reserve_size(bt_memory_packet_t type)
{
    uint32_t len = bt_get_pka_header_size(type); 
    BT_LOGD(GROUP_BT_DRIVER, "     bt_driver_get_mm_reserve_size = %d, type = %d \n", len, type);
    return len;
}

static bt_tx_queue_t bt_mm_if_pkt_queue_temp;
bt_tx_queue_t *bt_driver_get_mm_tx_if_packet_queue(void)
{
    return &bt_mm_if_pkt_queue_temp;
}

bool bt_driver_support_host_controller_share_buffer(void)
{
    return true;
}

bool bt_driver_support_multiple_standalone_tx_queue(void)
{
    return true;
}

bool bt_driver_reset_controller_during_power_off()
{
    return true;
}

#if 0
bool bt_driver_validate_public_key(const uint8_t *key, bt_public_key_t key_type)
{
    bool is_P256 = (key_type == BT_PUBLIC_KEY_256) ? true : false;
    bool result = bt_os_layer_validate_public_key(key, is_P256);
    BT_DRVLOG_MSGID_I("BTIF", BTIF_172, 1, result);
    return result;
}
#endif 

void bt_driver_lock_dvfs(void)
{
    //bt_os_layer_lock_dvfs(BT_OS_LAYER_DVFS_208M_SPEED);
}

void bt_driver_unlock_dvfs(void)
{
    //bt_os_layer_unlock_dvfs(BT_OS_LAYER_DVFS_208M_SPEED);
}

void bt_driver_vcore_lock_1P1(void)
{

}

void bt_driver_vcore_unlock_1P1(void)
{

}

#if 0
bt_controller_spec_ver_t bt_driver_get_controller_spec_version(void)
{
    return BT_CONTROLLER_SPEC_VER_5_0;
}

bt_controller_endian_order_t bt_driver_get_controller_endian_order(void)
{
    return BT_CONTROLLER_ENDIAN_ORDER_LITTLE;
}
#endif 

bool bt_gap_get_host_security_connect_support_feature(void)
{
    return true;
}

#ifdef __BT_HB_ENABLE_SLEEP_MODE__
void bt_driver_set_wakeup_cmd_sent_flag(uint8_t flag)
{
    return;
}

uint8_t bt_driver_get_wakeup_cmd_sent_flag(void)
{
    return 1;
}

void bt_driver_set_controller_sleep_flag(uint8_t flag)
{
    return;
}

uint8_t bt_driver_get_controller_sleep_flag(void)
{
    return 1;
}

uint8_t bt_driver_wakeup_host_status(void)
{
    return 1;
}

void bt_driver_wakeup_device(bool trigger)
{
    return;
}

void bt_driver_wakeup_pattern_send(void)
{
    return;
}

#if 1
bt_status_t bt_driver_wakeup_controller_timeout(uint32_t is_timeout,
        uint32_t timer_id,
        uint32_t data,
        const void *arg)
{
    return BT_STATUS_SUCCESS;
}

void bt_driver_start_wakeup_controller_timer(void)
{
    return;
}
#endif

bt_status_t bt_driver_wakeup_controller(void)
{
    return BT_STATUS_SUCCESS;
}

void bt_driver_wakeup_controller_complete(void)
{
    return;
}

void bt_driver_wakeup_host_complete(void)
{
    return;
}
void bt_driver_lock_sleep(void)
{
    return;

}

void bt_driver_unlock_sleep(void)
{
    return;
}

bt_status_t bt_driver_tx(bt_hci_le_packet_t *packet, uint32_t length)
{
    return BT_STATUS_SUCCESS;
}

void bt_driver_recv(void)
{

}

#endif // __BT_HB_ENABLE_SLEEP_MODE__


uint8_t bt_driver_relay_event_handle()
{
    bool relay_enabled = bt_driver_is_relay_mode_enabled();
    bool relay_enable_completed = bt_driver_is_relay_mode_enable_complete();

    BT_LOGD(GROUP_BT_DRIVER, "bt_driver_relay_event_handle,  relay_enabled = %d relay_enable_completed = %d\n", relay_enabled, relay_enable_completed);


    if (relay_enabled && !relay_enable_completed) {
        bt_driver_handle_test_mode_rsp();
        BT_LOGD(GROUP_BT_DRIVER, "bt_driver_handle_test_mode_rsp End \n");
        
        return true;
    } 
    else if (relay_enabled && relay_enable_completed) {
        while (!bt_driver_is_queue_empty((uint8_t *)BT_QUEUE_RX)) {


            BT_LOGD(GROUP_BT_DRIVER, "bt_driver_is_queue_empty \n");

            bt_hci_le_packet_t *relay_packet = (bt_hci_le_packet_t *)bt_driver_rx_dequeue();
            BT_ASSERT(relay_packet && BT_IS_ALLOCATED_PACKET_VALID(relay_packet));
            BT_ASSERT(BT_UART_ACL == relay_packet->indicator || BT_UART_EVT == relay_packet->indicator);

            uint32_t packet_len = 0;
            if (BT_UART_EVT == relay_packet->indicator) {
                packet_len = BT_HCI_PACKET_EVT_SIZE(relay_packet);

                if (BT_HCI_EVT_COMMAND_COMPLETE == relay_packet->evt.evt_code &&
                        BT_HCI_CMD_RESET == BT_HCI_LE_PACKET_TO_EVENT(bt_hci_evt_command_complete_t, relay_packet)->cmd_code) {
                    //BT_DRVLOG_MSGID_I("BTIF", BTIF_219, 0);
                }
            } else if (BT_UART_ACL == relay_packet->indicator) {
                packet_len = BT_HCI_PACKET_ACL_SIZE(relay_packet);
            }
            bt_hci_log(1, relay_packet, packet_len);
            uint8_t *relay_tx_buff = bt_driver_get_relay_tx_buffer();
            BT_ASSERT(relay_tx_buff);
            if (packet_len >= RELAY_BUFFER_SIZE) {
                return false;
            }
            bt_memcpy(relay_tx_buff, relay_packet, packet_len);
            BT_FREE_PACKET_WITH_NODE(BT_MEMORY_RX_BUFFER, relay_packet);

            bt_driver_relay_cb_write_data(relay_tx_buff, packet_len);
            //bt_driver_relay_cb.write_data(relay_tx_buff, packet_len);
            
            bt_memset(relay_tx_buff, 0x00, packet_len);
        }
        return true;
    }
    return false;
}


void bt_driver_hci_event_handle()
{
    bt_hci_le_packet_t *hci_evt_packet = (bt_hci_le_packet_t *)bt_driver_rx_dequeue();
    BT_ASSERT(hci_evt_packet && BT_IS_ALLOCATED_PACKET_VALID(hci_evt_packet));
    BT_ASSERT(BT_UART_ACL == hci_evt_packet->indicator || BT_UART_EVT == hci_evt_packet->indicator);

    BT_LOGD(GROUP_BT_DRIVER, "bt_driver_hci_event_handle, packet type = %d,  len = %d\n"
        , hci_evt_packet->indicator
        , BT_HCI_PACKET_EVT_SIZE(hci_evt_packet)
        );

    BT_FREE_PACKET_WITH_NODE(BT_MEMORY_RX_BUFFER, hci_evt_packet);
}

void bt_hb_rx_enqueue(uint8_t *hb_header)
{
    BT_LOGI(GROUP_BT_DRIVER, "bt_hb_rx_enqueue, hb_header %p", hb_header);
    extern uint8_t *g_hb_header;

    g_hb_header = hb_header;


    /*hb_header : bt_hci_packet_linknode_t* type*/
    BT_ASSERT(NULL != hb_header);

    bt_driver_hw_semaphore_lock();
    BT_QUEUE_PUSH_BACK(BT_QUEUE_RX, (bt_linknode_t *)hb_header);
    /* check packet validation */
    bt_mm_check_packet_integrity(BT_MEMORY_RX_BUFFER, ((char *)(hb_header)));
    bt_driver_hw_semaphore_unlock();
}

void *bt_hb_tx_dequeue(uint8_t type, uint8_t *q_header)
{
    BT_LOGD(GROUP_BT_DRIVER, "bt_hb_tx_dequeue at %p, type = %d", q_header, type);

    #if 0 
    BT_ASSERT_MSG((type == BT_QUEUE_TYPE_TX_ACL || type == BT_QUEUE_TYPE_TX_CMD), "err type %d", type);
    return q_header;

    #else 
    BT_ASSERT(NULL != q_header);
    BT_ASSERT(type == BT_QUEUE_TYPE_TX_ACL || type == BT_QUEUE_TYPE_TX_CMD || type == BT_QUEUE_TYPE_TX_IF_PACKET);
    bt_tx_queue_t *q_header_to_pop = (bt_tx_queue_t *)q_header;
    bt_hci_packet_linknode_t *pop_packet = NULL;

    

    bt_driver_hw_semaphore_lock();
    if (BT_QUEUE_TYPE_TX_ACL == type) {
        if (bt_driver_is_relay_mode_enabled() && bt_driver_is_relay_mode_enable_complete()) {
            if (Bt_QUEUE_TX_IF_PACKET_NODE != (bt_linknode_t *)q_header_to_pop) {
                BT_ASSERT("Can not find specific IF packet queue header in relay mode" && 0);
            }
        } else {
            BT_LOGD("AVM","skip ack dequeue......");
            BT_LOGD("AVM","BT_QUEUE_TX_ALL->front = %p, BT_QUEUE_TX_ALL = %p", BT_QUEUE_TX_ALL->front, BT_QUEUE_TX_ALL);

            #if 0 
            /*start_tx_queue is the first node pointer of tx_all_queue*/
            BT_ASSERT((BT_QUEUE_TX_ALL->front != BT_QUEUE_TX_ALL) && "TX ALL Q is empty");
            bt_tx_queue_t *tx_queue = (bt_tx_queue_t *)(BT_QUEUE_TX_ALL->front);
            while (tx_queue != q_header_to_pop) {

                BT_LOGI("AVM","tx_queue = %p, q_header_to_pop = %p ", tx_queue, q_header_to_pop);
                
                tx_queue = (bt_tx_queue_t *)(tx_queue->next_node.front);
                /*Traverse the circular queue, but not find the target*/
                if ((bt_linknode_t *)tx_queue == (bt_linknode_t *)BT_QUEUE_TX_ALL) {
                    BT_ASSERT("Can not find spccific ACL connection queue header" && 0);
                }
            }
            #endif
        }
    } else if (BT_QUEUE_TYPE_TX_CMD == type) {
        if (BT_QUEUE_TX_CMD_NODE != (bt_linknode_t *)q_header_to_pop) {
            BT_ASSERT("Can not find spccific cmd queue header" && 0);
        }
    } else if (BT_QUEUE_TYPE_TX_IF_PACKET == type) {
        if (Bt_QUEUE_TX_IF_PACKET_NODE != (bt_linknode_t *)q_header_to_pop) {
            BT_ASSERT("Can not find spccific IF packet queue header" && 0);
        }
    }
#ifdef __BT_LE_AUDIO_ENABLE__
    else if (BT_QUEUE_TYPE_TX_ISO == type) {
        if (BT_QUEUE_TX_ISO_NODE != (bt_linknode_t *)q_header_to_pop) {
            BT_ASSERT("Can not find spccific iso queue header" && 0);
        }
    }
#endif
    if (BT_QUEUE_EMPTY(&(q_header_to_pop->queue))) {
        bt_driver_hw_semaphore_unlock();
        //BT_DRVLOG_MSGID_E("BTIF", BTIF_228, 1, type);
        return NULL;
    }
    pop_packet = (bt_hci_packet_linknode_t *)BT_QUEUE_POP_FRONT(&(q_header_to_pop->queue));

    BT_LOGD(GROUP_BT_DRIVER, "pop_packet addr:%p \n", pop_packet);

    bt_driver_hw_semaphore_unlock();
    return (void *)pop_packet;
#endif 


}


uint16_t bt_get_hb_header_size(void)
{
    return sizeof(bt_hci_packet_linknode_t);
}

uint8_t *bt_hb_mm_allocate(bt_memory_packet_t type, uint32_t size)
{
    BT_LOGD(GROUP_BT_DRIVER, "bt_hb_mm_allocate called with type %d and size %d\n", type, size); 

    #if 1 
    bt_hci_packet_linknode_t *packet = NULL;
    uint16_t hb_header_size = 0;
    BT_ASSERT(type == BT_MEMORY_RX_BUFFER || type == BT_MEMORY_TX_BUFFER);

    hb_header_size = sizeof(bt_hci_packet_linknode_t);
    packet = (bt_hci_packet_linknode_t *)bt_mm_allocate_packet((type), (size) + hb_header_size);
    if (!packet) {
        //BT_DRVLOG_MSGID_E("BTIF", BTIF_121, 0);
        return NULL;
    }

    return (uint8_t *)(packet);
    #else 
    uint8_t* mem = (uint8_t *)k_malloc(size);
    BT_LOGI(GROUP_BT_DRIVER, "bt_hb_mm_allocate allocated at %p\n", mem); 
    return mem;
    #endif
}

void bt_hb_mm_free(bt_memory_packet_t type, uint8_t *ptr)
{
    BT_LOGD(GROUP_BT_DRIVER, "bt_hb_mm_free allocated at %p\n", ptr );

    #if 1
    bt_mm_free_packet(type, (char *)ptr);
    #else 
    k_free((void *)ptr);
    #endif 
}

