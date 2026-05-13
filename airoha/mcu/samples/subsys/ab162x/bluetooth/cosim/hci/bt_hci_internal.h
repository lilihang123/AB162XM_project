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

#ifndef __BT_HCI_INTERNAL_H__
#define __BT_HCI_INTERNAL_H__

#include "bt_common_upper_layer.h"
#include "bt_linknode.h"
#include "bt_timer.h"
#include "bt_type_def.h"
//#include "bt_hci_ext.h"
//#include "bt_common_ext.h"

BT_EXTERN_C_BEGIN

typedef bt_timeout_callback_t bt_hci_event_callback_t;

#define BT_HCI_RHO_ALLOWED               0x00
#define BT_HCI_RHO_RX_QUEUE_NOT_EMPTY    0x01
#define BT_HCI_RHO_DATA_LENGTH_TOO_LARGE 0x02

#define BT_HCI_CONTINUOUS_TX_OOM_MAX_NUMBER     50

#define BT_HCI_FLAG_RHO_DISALLOWED_LE_PACKET    0x01

#define BT_HCI_RX_PACKET_PENDING_BY_RHO  (BT_MODULE_HCI|0x03)

typedef struct {
    bt_handle_t old;
    bt_handle_t new;
} bt_hci_le_handle_map_t;

BT_PACKED(
typedef struct {
    uint8_t le_link_num;
    bt_hci_le_handle_map_t handle_map[1];
}) bt_hci_rho_le_new_link_info_t;

typedef struct {
    uint16_t index;
    bt_hci_event_callback_t callback;
} bt_hci_event_table_t;

typedef enum {
    BT_HCI_UNKNOWN_CONNECTION,
    BT_HCI_LE_CONNECIION,
    BT_HCI_EDR_CONNECIION,
#ifdef BT_LE_AUDIO_ENABLE
    BT_HCI_CIS_CONNECIION,
#endif
} bt_hci_connection_type;

#define BT_TIMER_HCI_TX_OOM_MASK  0x00030000
#define BT_HCI_TX_OOM_NOTIFY_TIMER  (BT_MODULE_HCI | BT_TIMER_HCI_TX_OOM_MASK | 0x0001)

#ifdef __BT_HB_ENABLE_SLEEP_MODE__
/*sleep mode */
#define BT_HCI_SLEEP_DISABLE        0x00
#define BT_HCI_SLEEP_6_PIN          0x01
#define BT_HCI_SLEEP_4_PIN          0x02
#define BT_HCI_SLEEP_3_PIN          0x03 /*for 2523/7697*/
#define BT_HCI_SLEEP_3_PIN_HOST     0x04
#define BT_HCI_SLEEP_USB_MODE_1     0x05
#define BT_HCI_SLEEP_USB_MODE_2     0x06

#define BT_TIMER_HCI_SLEEP_MODE_MASK  0x00020000
#define BT_HCI_SLEEP_MODE_TIMER    \
        (BT_MODULE_HCI | BT_TIMER_HCI_SLEEP_MODE_MASK | 0x0000)

#define BT_HCI_WAKE_CONTROLLER_TIMER    \
        (BT_MODULE_HCI | BT_TIMER_HCI_SLEEP_MODE_MASK | 0x0001)

/*
 * default timer for host which thought
 * controller has sleeped after no data exchange
 */
#define BT_HCI_SLEEP_MODE_DEFAULT_TIMEOUT      4000

BT_PACKED(
typedef struct {
    uint8_t     mode;
    uint16_t    duration;
    uint16_t    host_duration;
    uint8_t     wakeup_pin;
    uint8_t     time_comp;
}) bt_hci_sleep_mode_param_t;
extern const bt_hci_sleep_mode_param_t bt_hci_enable_sleep_mode;
//extern const bt_hci_sleep_mode_param_t bt_hci_disable_sleep_mode;
#endif //__BT_HB_ENABLE_SLEEP_MODE__

BT_PACKED(
typedef struct {
    bt_hci_cmd_op_t   cmd_code;
    uint8_t           length;
    const void        *param; /* This is a pointer */
}) bt_hci_cmd_t;

//the same CMD wait for send
BT_PACKED(
typedef struct {
    bt_linknode_t           node;
    uint32_t                data;
    bt_hci_event_callback_t callback;
    bt_hci_cmd_t            cmd;
})bt_hci_cmd_w4_send_node_t;

#define bt_hci_rx_cb(packet) (BT_QUEUE_PUSH_BACK(BT_QUEUE_RX, BT_GET_NODE_FROM_PACKET(packet)), BT_STATUS_SUCCESS)

void bt_hci_connection_construct(bt_connection_t *conn);
#ifdef BT_LE_AUDIO_ENABLE
void bt_hci_cis_connection_construct(bt_cis_connection_t *conn);
#endif
void bt_hci_connection_destroy(bt_tx_queue_t *tx_queue, bt_hci_connection_type connection_type);

/* #bt_hci_cmd_t is not part of #bt_hci_packet_t, but #bt_hci_packet_cmd_t is */
bt_status_t bt_hci_cmd_send(const bt_hci_cmd_t *cmd, uint32_t data,
                            const bt_hci_event_callback_t callback);
bt_status_t bt_hci_cmd_send_debug(const bt_hci_cmd_t *cmd, uint32_t data,
                                  const bt_hci_event_callback_t callback);

bt_status_t bt_hci_acl_le_send(bt_connection_t *const conn,
                               const bt_l2cap_packet_t *l2cap_packet, uint16_t length);
bt_status_t bt_hci_cmd_send_w_pkg(uint32_t cmd_code, bt_hci_le_packet_t *packet, uint32_t data,
                                  const bt_hci_event_callback_t callback);
extern void bt_hci_lock_sleep(bt_handle_t handle);
extern void bt_hci_unlock_sleep(bt_handle_t handle);
#ifdef __BT_HB_DUO__
bt_status_t bt_hci_acl_send(bt_gap_connection_t *const conn,
                            const bt_l2cap_packet_t *l2cap_packet, uint16_t length);
bt_status_t bt_hci_acl_send_with_auto_flush(bt_gap_connection_t *const conn,
                                            const bt_l2cap_packet_t *l2cap_packet, uint16_t length);
#endif

#ifdef __MTK_AWS_MCE_ENABLE__
bool bt_hci_rho_get_rx_event_handle_flag(void);
uint32_t bt_hci_rho_get_rho_busy_flag(void);
void bt_hci_rho_get_new_le_link_info(void *data);
bool bt_hci_is_cmd_in_rho_white_list(bt_hci_cmd_op_t cmd_code, bt_hci_le_packet_t *packet);
bool bt_hci_is_evt_in_rho_white_list(bt_hci_evt_op_t evt_code, bt_hci_le_packet_t *packet);
#endif

/**
 * @brief   To send hci data, or process data in the received queue.
 * @return  Bt_status of this operation.
 */
bt_status_t bt_hci_process_packet(void);

BT_EXTERN_C_END

#endif /* __BT_HCI_INTERNAL_H__ */

