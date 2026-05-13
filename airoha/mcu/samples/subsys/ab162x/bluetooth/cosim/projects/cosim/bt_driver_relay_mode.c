/* Copyright Statement:
 *
 * (C) 2005-2016  MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. ("MediaTek") and/or its licensors.
 * Without the prior written permission of MediaTek and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) MediaTek Software
 * if you have agreed to and been bound by the applicable license agreement with
 * MediaTek ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */
/* MediaTek restricted information */
#include "bt_debug.h"
#include "bt_hci_internal.h"
#include "bt_memory.h"
#include "bt_hci_log.h"
#include "bt_os_layer_api.h"
#include "bt_driver.h"
#include "bt_log.h"
#include "type_def.h"
#include "bt_driver_internal.h"
#include "avm_external.h"




#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include "zephyr/sys/__assert.h"
#include "cosim_script_parser.h"



#ifdef __BT_DRIVER_RELAY_MODE__
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

static uint32_t read_size = 0;
void bt_driver_handle_relay_port_data(void)
{
    BT_DRVLOG_MSGID_I("BTIF", BTIF_147, 0);
    //int i = 0;
    uint32_t cur_pos = 0;
    uint32_t current_read_size = 0;
    uint32_t total_payload_size = 0;
    uint32_t remaining_size = 0;
    bt_hci_le_packet_t *packet = NULL;
    bt_hci_le_packet_t *send_packet = NULL;
    bt_hb_queue_type_t queue_type = BT_QUEUE_TYPE_TX_CMD;
    uint8_t *queue_header = NULL;

    //bt_memset(bt_driver_relay_rx_buf, 0x00, RELAY_BUFFER_SIZE);
    do {
        current_read_size = bt_driver_relay_cb.read_data(bt_driver_relay_rx_buf, RELAY_BUFFER_SIZE, read_size);
        if (current_read_size > 0) {
            bt_driver_relay_rx_buf += 3;
            read_size += current_read_size;
        } else {
            return;
        }
#if 0
        if (current_read_size) {
            BT_LOGI("BT", "start--------");
            BT_DRVLOG_MSGID_W("BTIF", BTIF_241, 0);
            uint32_t i = 0;
            for (i = 0; i < current_read_size; i++) {                
                BT_LOGI("BT", "%x",bt_driver_relay_rx_buf[i]);
                BT_DRVLOG_MSGID_W("BTIF", BTIF_266, 1, bt_driver_relay_rx_buf[i]);
            }
            BT_LOGI("BT", "----end--------");
            BT_DRVLOG_MSGID_W("BTIF", BTIF_243, 0);
        }
        BT_LOGI("BT", "Current data len: %d", current_read_size);
#endif
#if 0//def __BT_SLT_TEST__
    {
        bool bt_driver_is_end_signal = true;
        uint8_t i;
        if (read_size == 2) {//FAIL, if 2 0xff is fail
            for (i = 0; i < read_size; i++) {
                BT_DRVLOG_MSGID_W("BTIF", BTIF_266, 1, bt_driver_relay_rx_buf[i]);
                BT_LOGI("BT", "%02x", bt_driver_relay_rx_buf[i]);
                if (bt_driver_relay_rx_buf[i] != 0xFF) {
                    bt_driver_is_end_signal = false;
                }
            }
            if (bt_driver_is_end_signal && (bt_driver_slt_test_cb != NULL)) {
                bt_driver_slt_test_cb(0x00);
                read_size = 0;
            }
            //read_size = 0;
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
            //read_size = 0;
        }
}
#endif /*__BT_SLT_TEST__*/
    if (read_size > 0) {
        remaining_size = read_size;
        packet = (bt_hci_le_packet_t *)(bt_driver_relay_rx_buf);
        send_packet = NULL;
        BT_LOGI("BT", "read_size %d, indicator %d", read_size, packet->indicator);
        if (packet->indicator == BT_UART_CMD) {
            if (remaining_size < BT_HCI_CMD_HEADER_LENGTH) {
                BT_LOGI("BT", "cmd remaining_size %d too small", remaining_size);
                return;
            }
            total_payload_size = BT_HCI_PACKET_CMD_SIZE(packet);
            queue_type = BT_QUEUE_TYPE_TX_CMD;
        } else if (packet->indicator == BT_UART_ACL) {
            if (remaining_size < BT_HCI_ACL_HEADER_LENGTH) {
                BT_LOGI("BT", "acl remaining_size %d too small", remaining_size);
                return;
            }
            total_payload_size = BT_HCI_PACKET_ACL_SIZE(packet);
            queue_type = BT_QUEUE_TYPE_TX_ACL;

            // return if it's rx acl
            if (*(bt_driver_relay_rx_buf - 3) == 2) {
                BT_LOGI("BT", "HCI RX %d size %d", packet->indicator, total_payload_size);
                bt_driver_relay_rx_buf += read_size;
                read_size = 0;
                return;
            }
#ifdef __BT_LE_AUDIO_ENABLE__
        } else if (packet->indicator == BT_UART_ISO) {               
               BT_LOGI("BT", "ISO data");
            if (remaining_size < BT_HCI_ISO_HEADER_LENGTH) {
                return;
            }
            total_payload_size = BT_HCI_PACKET_ISO_SIZE(packet);
            queue_type = BT_QUEUE_TYPE_TX_ISO;
#endif //__BT_LE_AUDIO_ENABLE__
        } else if (packet->indicator == BT_UART_EVT) {
            if (remaining_size < BT_HCI_EVT_HEADER_LENGTH) {
                BT_LOGI("BT", "evt remaining_size %d too small", remaining_size);
                return;
            }
            bt_driver_relay_rx_buf += read_size;
            read_size = 0;
            return;
        } else {
            bt_driver_relay_rx_buf += read_size;
            read_size = 0;
            return;
        }
        BT_LOGI("BT", "HCI TX %d size %d", packet->indicator, total_payload_size);

        cur_pos += total_payload_size;
        if (cur_pos == read_size) {
            bt_driver_relay_rx_buf += read_size;
            read_size = 0;
        }
        //BT_LOGI("BT", "read_size %d, cur_pos %d, total_payload_size:%d", read_size, cur_pos, total_payload_size);
        send_packet = BT_HCI_PKT_ALLOC(total_payload_size);
        if (!BT_IS_ALLOCATED_PACKET_VALID(send_packet)) {
            BT_DRVLOG_MSGID_I("BTIF", BTIF_156, 0);
            return;
        }
        bt_memcpy(send_packet, packet, total_payload_size);
        bt_hci_log(0, send_packet, total_payload_size);
        bt_driver_hw_semaphore_lock();
        /*In relay mode will not use hci layer, so push ACL into IF queue*/
        if (queue_type == BT_QUEUE_TYPE_TX_ACL || queue_type == BT_QUEUE_TYPE_TX_IF_PACKET) {
            BT_QUEUE_PUSH_BACK(BT_QUEUE_TX_IF_PACKET, BT_GET_NODE_FROM_PACKET(send_packet));
            queue_header = (uint8_t *)Bt_QUEUE_TX_IF_PACKET_NODE;
        } else if (queue_type == BT_QUEUE_TYPE_TX_CMD) {
            BT_QUEUE_PUSH_BACK(BT_QUEUE_TX_CMD, BT_GET_NODE_FROM_PACKET(send_packet));
            queue_header = (uint8_t *)BT_QUEUE_TX_CMD_NODE;
        }
#ifdef __BT_LE_AUDIO_ENABLE__
        else if (queue_type == BT_QUEUE_TYPE_TX_ISO) {
            BT_QUEUE_PUSH_BACK(BT_QUEUE_TX_ISO, BT_GET_NODE_FROM_PACKET(send_packet));
            queue_header = (uint8_t *)BT_QUEUE_TX_ISO_NODE;
        }
#endif //__BT_LE_AUDIO_ENABLE__
        bt_driver_hw_semaphore_unlock();

        //bt_driver_tx_notify_controller(queue_type, queue_header);
        //BT_LOGI("BT", "bt_tx_notify_pka");
        bt_tx_notify_pka(queue_type, queue_header);
    }
    } while (1);

    return;
}

bool bt_driver_enter_relay_mode(uint8_t port)
{

#if 0
    const uint8_t set_fixed_bt_addr_cmd[] = {0x01, 0x1a, 0xfc, 0x06, 0x01, 0x61, 0x67, 0x46, 0x00, 0x00}; /*fixed bt addr(reverse):00:00:46:67:61:01*/
    const uint8_t change_local_name_cmd[] = {0x01, 0x13, 0x0c, 0x0e, 'B', 'l', 'u', 'e', 't', 'o', 'o', 't', 'h', ' ', 'D', 'T', 'M', '\0'}; /*Bluetooth DTM*/
    const uint8_t write_extended_inquiry_response[0xF5] = {0x01, 0x52, 0x0c, 0xF1,
                                                           0x01, 0x11, 0x06, 0x1d, 0x23, 0xbb, 0x1b, 0x00, 0x00, 0x10, 0x00, 0x30, 0x00, 0x50, 0x80, 0x5f, 0x9b, 0x34, 0xfa,
                                                           0x0f, 0x09, 'B', 'l', 'u', 'e', 't', 'o', 'o', 't', 'h', ' ', 'D', 'T', 'M', '\0'
                                                          };
    const uint8_t read_bd_addr[] = {0x01, 0x09, 0x10, 0x00};                   /*read bd address*/
#endif

    if (bt_driver_relay_enabled && bt_driver_relay_enable_complete) {
        BT_LOGI("BT", "bt_driver_relay_enabled %x %x", bt_driver_relay_enabled, bt_driver_relay_enable_complete);
        return true;
    }

    bt_driver_init();

    bt_driver_relay_enabled = 1;
    bt_driver_relay_tx_buf = (uint8_t *)bt_mm_allocate_packet(BT_MEMORY_TX_BUFFER, RELAY_BUFFER_SIZE);
    bt_driver_relay_rx_buf = (uint8_t *)cosim_script_parser_get_rx_ptr();

    BT_LOGI("BT", "bt_driver_relay_tx_buf = 0x%x, bt_driver_relay_rx_buf = 0x%x \n", (unsigned int)bt_driver_relay_tx_buf, (unsigned int)bt_driver_relay_rx_buf);

    BT_ASSERT(bt_driver_relay_tx_buf && "tx relay oom, please keep 2K bytes.");
    bt_memset(bt_driver_relay_tx_buf, 0, RELAY_BUFFER_SIZE);

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

#if 0
    if (BT_STATUS_SUCCESS != bt_driver_send_reset_and_tx_pwr_config_cmd()) {
        bt_driver_deinit_relay_mode();
        BT_DRVLOG_MSGID_E("BTIF", BTIF_163, 0);
        return false;
    }

    if (BT_STATUS_SUCCESS != bt_driver_send_with_pending_response(set_fixed_bt_addr_cmd, sizeof(set_fixed_bt_addr_cmd))) {
        return BT_STATUS_FAIL;
    } else if (BT_STATUS_SUCCESS != bt_driver_send_with_pending_response(change_local_name_cmd, sizeof(change_local_name_cmd))) {
        return BT_STATUS_FAIL;
    } else if (BT_STATUS_SUCCESS != bt_driver_send_with_pending_response(write_extended_inquiry_response, sizeof(write_extended_inquiry_response))) {
        return BT_STATUS_FAIL;
    } else if (BT_STATUS_SUCCESS != bt_driver_send_with_pending_response(read_bd_addr, sizeof(read_bd_addr))) {
        return BT_STATUS_FAIL;
    }
#endif

    if (0 != bt_driver_relay_cb.init(port)) {
        BT_LOGI("BT", "bt_driver_relay_cb.init fail");
        bt_driver_deinit_relay_mode();
        return false;
    }

    bt_driver_relay_enable_complete = 1;

    //bt_device_mode_t last_mode = BT_NORMAL_MODE;
    //bt_app_event_callback(BT_TEST_MODE_RELAY_ENABLE_IND, BT_STATUS_SUCCESS, NULL);

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
    bt_driver_relay_cb.deinit();

    //bt_device_mode_t last_mode = BT_RELAY_MODE;
    bt_app_event_callback(BT_TEST_MODE_NONE_IND, BT_STATUS_SUCCESS, NULL);
}

#endif
