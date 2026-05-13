/* Copyright Statement:
 *
 * (C) 2005-2019  MediaTek Inc. All rights reserved.
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
#ifndef __BT_DRIVER_INTERNAL_H__
#define __BT_DRIVER_INTERNAL_H__
#include "bt_debug.h"
#include "type_def.h"
#include "bt_system.h"
/*for send/event hci command/event by ATCI command, e.x: manual test or ATE tool test*/
#define __BT_DRIVER_ATCI_MODE__
#define BT_DRIVER_SYSTEM_LOG_ENABLE
#define __BT_SLT_TEST__
#define __BT_DRIVER_DUT_MODE__
#define __BT_DRIVER_RELAY_MODE__
#if defined (__BT_SLT_TEST__) && !defined(__BT_DRIVER_RELAY_MODE__)
#define __BT_DRIVER_RELAY_MODE__
#endif

#ifdef BT_DRIVER_SYSTEM_LOG_ENABLE
#define BT_DRIVER_LOGI    BT_LOGI
#define BT_DRIVER_LOGD    BT_LOGD
#define BT_DRIVER_LOGW    BT_LOGW
#define BT_DRIVER_LOGE    BT_LOGE
#define BT_DRVLOG_MSGID_I    BT_LOG_MSGID_I
#define BT_DRVLOG_MSGID_D    BT_LOG_MSGID_D
#define BT_DRVLOG_MSGID_W    BT_LOG_MSGID_W
#define BT_DRVLOG_MSGID_E    BT_LOG_MSGID_E
#else
#define BT_DRIVER_LOGI(...)
#define BT_DRIVER_LOGD(...)
#define BT_DRIVER_LOGW(...)
#define BT_DRIVER_LOGE(...)
#define BT_DRVLOG_MSGID_I(...)
#define BT_DRVLOG_MSGID_D(...)
#define BT_DRVLOG_MSGID_W(...)
#define BT_DRVLOG_MSGID_E(...)
#endif

#define BT_DRIVER_MAX_PENDING_TIME  (1000)  /*MS*/
#define BT_DRIVER_HCI_CMD_TIMEOUT   (8000)  //8s to avoid unnessary cmd timeout.

void bt_driver_init(void);

#ifdef __BT_DRIVER_DUT_MODE__
#define BT_DRIVER_DUT_MODE_DELAY_TIME (3000) /*ms*/
bool bt_driver_is_dut_mode_enabled(void);
bool bt_driver_is_dut_mode_enable_complete(void);
void bt_driver_dut_test_end();
void bt_driver_dut_mode_mixed_with_normal_mode(bool is_mixed);
bool bt_driver_is_dut_mode_mixed_with_normal_mode(void);
bool bt_driver_is_dut_mixed_enabled(void);
bool bt_driver_is_dut_only_enabled(void);
void bt_driver_deinit_dut_mode(void);
#endif

#ifdef __BT_DRIVER_RELAY_MODE__

#ifdef __BT_LE_AUDIO_ENABLE__
#define BT_QUEUE_TYPE_TX_ISO (0x04)
#define BT_UART_ISO          (0x05)

#define BT_HCI_ISO_HEADER_LENGTH       5  //sizeof(bt_uart_t) + sizeof(bt_hci_Packet_iso_t) - 1
#define BT_HCI_PACKET_ISO_SIZE(p)   (*(uint16_t *)((uint8_t *)(p)+3)+BT_HCI_ISO_HEADER_LENGTH)

extern bt_tx_queue_t *bt_mm_iso_queue_p;
#define bt_mm_iso_queue             (*bt_mm_iso_queue_p)
#define BT_QUEUE_TX_ISO             (&(bt_mm_iso_queue.queue))
#define BT_QUEUE_TX_ISO_NODE        ((bt_linknode_t *)&bt_mm_iso_queue)
#endif


//#include "memory_attribute.h"
#define RELAY_BUFFER_SIZE 2048

typedef struct {
    uint32_t (*read_data)(uint8_t *buf, uint32_t buf_len, uint32_t offset);/**< Uart port read data function pointer. */
    uint32_t (*write_data)(uint8_t *buf, uint32_t buf_len);                /**< Uart port write data function pointer. */
    uint8_t (*init)(uint8_t port);                                         /**< Uart port init function pointer. */
    uint8_t (*deinit)(void);                                               /**< Uart port deinit function pointer. */
} bt_driver_relay_callbacks;

extern bt_driver_relay_callbacks bt_driver_relay_cb;
uint8_t *bt_driver_get_relay_rx_buffer(void);
uint8_t *bt_driver_get_relay_tx_buffer(void);
bool bt_driver_is_relay_mode_enabled(void);
bool bt_driver_is_relay_mode_enable_complete(void);
void bt_driver_deinit_relay_mode(void);
#endif

#ifdef __BT_DRIVER_ATCI_MODE__
typedef void (*bt_atci_cb)(uint8_t *data, uint32_t dataLen);
bool bt_driver_is_enter_atci_mode(void);
void bt_driver_deinit_atci_mode(void);
void bt_driver_at_handle_rx_pkt(void);
#endif

bool bt_driver_is_driver_powered_on(void);
uint8_t *bt_driver_get_tx_power_config_table(void);
uint8_t *bt_hb_mm_allocate(bt_memory_packet_t type, uint32_t size);
void bt_hb_mm_free(bt_memory_packet_t type, uint8_t *ptr);
void bt_hb_rx_enqueue(uint8_t *hb_header);
void *bt_hb_tx_dequeue(bt_hb_queue_type_t type, uint8_t *q_header);
uint16_t bt_get_hb_header_size(void);
void bt_rx_notify_hb(void);
void bt_init_reset_table(void);
void bt_driver_hw_semaphore_lock(void);
void bt_driver_hw_semaphore_unlock(void);
void bt_driver_tx_notify_controller(bt_hb_queue_type_t type, uint8_t *q_header);
bt_status_t bt_driver_power_on(void);
bool bt_driver_is_queue_empty(uint8_t *queue_header);
void *bt_driver_rx_dequeue(void);
bt_status_t bt_driver_send_reset_and_tx_pwr_config_cmd(void);
bt_status_t bt_driver_send_with_pending_response(const void *packet, uint32_t length);
void bt_driver_handle_test_mode_rsp(void);
void bt_driver_clear_queue(bt_hb_queue_type_t type);
#endif
