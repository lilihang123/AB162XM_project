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
#include "bt_common_upper_layer.h"
#include "bt_linknode.h"
#include "bt_memory.h"
#include "bt_sm_math.h"
#ifdef __BT_HB_DUO__
#include "bt_gap_internal.h"
#include "bt_sdp_internal.h"
#include "bt_hfp_internal.h"
#endif

extern bt_status_t bt_hci_tx_send(void);

bt_hummingbird_t bt_hummingbird;

#ifdef __BT_HB_DUO__
void bt_a2dp_init(void);
#endif

void bt_hfp_init_ext()
{
    return;
}

bt_status_t default_bt_driver_set_tx_pwr_gain_table(const bt_config_tx_power_gain_t *bdr_tx_pwr_gain_table, const bt_config_tx_power_gain_t *edr_tx_pwr_gain_table);

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_hfp_init=_bt_hfp_init_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_hfp_init = bt_hfp_init_ext
#else
#error "Unsupported Platform"
#endif


#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_app_event_callback=_default_bt_app_event_callback")
#pragma comment(linker, "/alternatename:_bt_a2dp_init=_bt_a2dp_init_default")
#pragma comment(linker, "/alternatename:_bt_driver_set_tx_pwr_gain_table=_default_bt_driver_set_tx_pwr_gain_table")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__ARMCC_VERSION) || defined(__CC_ARM)
#pragma weak bt_app_event_callback = default_bt_app_event_callback
#pragma weak bt_a2dp_init = bt_a2dp_init_default
#pragma weak bt_driver_set_tx_pwr_gain_table = default_bt_driver_set_tx_pwr_gain_table
#else
#error "Unsupported Platform"
#endif
bt_status_t bt_driver_set_tx_pwr_gain_table(const bt_config_tx_power_gain_t *bdr_tx_pwr_gain_table, const bt_config_tx_power_gain_t *edr_tx_pwr_gain_table);
extern void *bt_mm_get_sync_pointer_info(void);
bool bt_driver_get_bt_clock_directly(void);
bt_status_t bt_driver_get_bt_clock_with_gpt(uint16_t hci_handle, bt_clock_t *bt_clk, uint32_t *gpt_count);
bt_status_t bt_avm_get_bt_clock_with_gpt_count(uint16_t handle);
extern uint32_t hal_gpt_delay_us(uint32_t us);
bool bt_driver_get_bt_clock_directly(void);
bt_status_t bt_driver_get_bt_clock(uint16_t hci_handle, bt_clock_t *bt_clk);

bt_status_t default_bt_app_event_callback(bt_msg_type_t msg, bt_status_t status, void *buff)
{
    return BT_STATUS_SUCCESS;
}

void bt_a2dp_init_default(void)
{
//    BT_LOG_MSGID_W("COMMON", BTCOMMON_001, 0);
}

bt_status_t default_bt_driver_set_tx_pwr_gain_table(const bt_config_tx_power_gain_t *bdr_tx_pwr_gain_table, const bt_config_tx_power_gain_t *edr_tx_pwr_gain_table)
{
    return BT_STATUS_SUCCESS;
}

bt_status_t bt_config_tx_power_gain_table(const bt_config_tx_power_gain_t *bdr_table, const bt_config_tx_power_gain_t *edr_table)
{
    return bt_driver_set_tx_pwr_gain_table(bdr_table, edr_table);
}

bt_connection_t *bt_find_conn_by_handle(uint32_t handle, bool remove)
{
    #if 0 //hci_relay temp
    bt_linknode_t *p = &bt_hummingbird.le_connection, *pp;
    do {
        pp = p;
        p = p->front;
    } while (p && BT_GET_CONN_FROM_NODE(p)->handle != handle);

    if (p && remove) {
        bt_linknode_remove_node(pp, BT_NODE_FRONT);
    }

    return p ? BT_GET_CONN_FROM_NODE(p) : NULL;
    #endif
    return NULL;
}

#ifdef BT_LE_AUDIO_ENABLE
bt_cis_connection_t *bt_find_cis_conn_by_handle(uint32_t handle, bool remove)
{
    bt_linknode_t *p = &bt_hummingbird.cis_connection, *pp;
    do {
        pp = p;
        p = p->front;
    } while (p && BT_GET_CONN_FROM_CIS_NODE(p)->cis_handle != handle);

    if (p && remove) {
        bt_linknode_remove_node(pp, BT_NODE_FRONT);
    }

    return p ? BT_GET_CONN_FROM_CIS_NODE(p) : NULL;
}
#endif

#ifdef __BT_HB_DUO__
void bt_profiles_init(void)
{
    bt_hfp_init();
    bt_a2dp_init();
}
#endif

bt_tx_queue_t *bt_find_tx_queue_by_handle(uint32_t handle)
{
    bt_tx_queue_t *q = NULL;
    bt_connection_t *le_conn;
    le_conn = bt_find_conn_by_handle(handle, false);
    if (le_conn) {
        q = &(le_conn->tx_con_queue);
    }
#ifdef __BT_HB_DUO__
    else {
        bt_gap_connection_t *bt_conn;
        bt_conn = bt_gap_find_connection_by_handle(handle);
        if (bt_conn) {
            q = &(bt_conn->tx_con_queue);
        }
    }
#endif /* __BT_HB_DUO__ */
    return q;
}

void bt_remove_link_node(bt_linknode_t *head, bt_linknode_t *node)
{
    bt_linknode_t *pp;
    pp = bt_linknode_travel_node(head, bt_linknode_cmp_backward, (void *)node);
    if (pp) {
        bt_linknode_remove_node(pp, BT_NODE_FRONT);
    }
}

bool bt_is_connection_existing(const bt_addr_t *peer_address)
{
    bt_linknode_t *p = &bt_hummingbird.le_connection;
    do {
        p = p->front;
    } while (p && bt_memcmp(&BT_GET_CONN_FROM_NODE(p)->peer_addr, peer_address, sizeof(bt_addr_t)));

    return p ? true : false;
}

bool bt_is_hci_cmd_connection_oriented(uint32_t cmd_code)
{
    switch (cmd_code) {
        case BT_HCI_CMD_DISCONNECT:
        case BT_HCI_CMD_LE_CONNECTION_UPDATE:
        case BT_HCI_CMD_LE_START_ENCRYPTION:
        case BT_HCI_CMD_LE_LONG_TERM_KEY_REQUEST_REPLY:
        case BT_HCI_CMD_LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY:
        case BT_HCI_CMD_LE_REMOTE_CONNECTION_PARAMETER_REQUEST_REPLY:
        case BT_HCI_CMD_LE_REMOTE_CONNECTION_PARAMETER_REQUEST_NEGATIVE_REPLY:
        case BT_HCI_CMD_LE_SET_DATA_LENGTH:
            return true;
    }
    return false;
}

bt_status_t bt_get_status_from_hci_event_cc(const void *packet)
{
    bt_hci_status_t hci_status = ((bt_hci_le_packet_t *)packet)->evt.evt_code == BT_HCI_EVT_COMMAND_COMPLETE ?
                                 BT_HCI_LE_PACKET_TO_EVENT_CC(bt_hci_evt_cc_general_t, packet)->status :
                                 BT_HCI_LE_PACKET_TO_EVENT(bt_hci_evt_command_status_t, packet)->status;

    bt_status_t status = hci_status == BT_HCI_STATUS_SUCCESS ?
                         BT_STATUS_SUCCESS : (BT_HCI_STATUS_MASK & hci_status);
    return status;
}

void bt_reverse_key(uint8_t *dst, const uint8_t *src, uint32_t length)
{
    uint32_t i;
    for (i = 0; i < length; i++) {
        dst[i] = src[length - i - 1];
    }
}

uint8_t *bt_copy_and_increase(uint8_t *dst, const uint8_t *src, uint32_t length)
{
    bt_memcpy(dst, src, length);
    return dst + length;
}

void bt_xor_16_byte(bt_key_t output, const bt_key_t input)
{
    uint8_t i;
    for (i = 0; i < 16; ++i) {
        output[i] ^= input[i];
    }
}

bt_hci_le_packet_t *bt_alloc_rx_packet_with_node(uint32_t size)
{
    bt_hci_packet_linknode_t *packet;

    packet = (bt_hci_packet_linknode_t *)(bt_mm_allocate_packet(BT_MEMORY_RX_BUFFER, size + sizeof(bt_hci_packet_linknode_t)));
    if (packet) {
#ifdef __BT_HB_DUO__
        packet->packet_length = size + sizeof(bt_hci_packet_linknode_t);
        packet->ref_count = 1;
        packet->offset = 0;
        packet->is_rx = 1;
#endif
        return (bt_hci_le_packet_t *)(packet + 1);
    } else {
        return NULL;
    }
}

uint8_t *bt_allocate_packet_with_node(bt_memory_packet_t type, uint32_t size)
{
    uint8_t *p;

    printk("     bt_allocate_packet_with_node type = %d, size = %d, sizeof(bt_hci_packet_linknode_t) = %d \n", type, size, sizeof(bt_hci_packet_linknode_t) );

    p = (uint8_t *)bt_mm_allocate_packet((type), (size) + sizeof(bt_hci_packet_linknode_t));
    printk("    p = %p \n", p);

    if ((p == NULL) && (type == BT_MEMORY_TX_BUFFER) && bt_is_bt_task_running()) {

        printk("     bt_hci_tx_send missed \n"); 
        //bt_hci_tx_send();
        p = (uint8_t *)bt_mm_allocate_packet(BT_MEMORY_TX_BUFFER, (size) + sizeof(bt_hci_packet_linknode_t));
    }
    if (p) {
        return p + sizeof(bt_hci_packet_linknode_t);
    } else {

        return NULL;
    }
}

void bt_store_little_endian_from_16(uint8_t *buff, uint16_t le_value)
{
    buff[1] = (uint8_t)(le_value >> 8);
    buff[0] = (uint8_t) le_value;
}

void bt_store_little_endian_from_32(uint8_t *buff, uint32_t le_value)
{
    buff[3] = (uint8_t)(le_value >> 24);
    buff[2] = (uint8_t)(le_value >> 16);
    buff[1] = (uint8_t)(le_value >> 8);
    buff[0] = (uint8_t) le_value;
}

uint16_t bt_retrieve_little_endian_to_16(const uint8_t *ptr)
{
    return (uint16_t)(((uint16_t) * (ptr + 1) << 8) | ((uint16_t) * ptr));
}

uint32_t bt_retrieve_little_endian_to_32(const uint8_t *ptr)
{
    return (uint32_t)(((uint32_t) * (ptr + 3) << 24) |
                      ((uint32_t) * (ptr + 2) << 16) |
                      ((uint32_t) * (ptr + 1) << 8) |
                      ((uint32_t) * (ptr)));
}

bool bt_endian_order_swap(uint8_t *dest, const uint8_t *src, uint8_t len)
{
    uint8_t temp[16]; /*Add temp variable to support dest and src are same point*/
    if (len == 2 || len == 4 || len == 8 || len == 16) {
        uint8_t i;
        for (i = 0; i < len; i++) {
            *(temp + i) = *(src + (len - 1) - i);
        }
        bt_memcpy(dest, temp, len);
        return true;
    } else {
        return false;
    }
}

void bt_free_packet_with_node(bt_memory_packet_t type, uint8_t *ptr)
{
    bt_mm_free_packet(type, (char *)ptr - sizeof(bt_hci_packet_linknode_t));
}

void *bt_get_packet_from_node(uint8_t *ptr)
{
    return (void *)(ptr + sizeof(bt_hci_packet_linknode_t));
}

extern void bt_module_handle_notify(void);
void bt_module_handle_process(void)
{
    bt_module_free_handle_list_t *ptr = (bt_module_free_handle_list_t *)(bt_hummingbird.module_free_handle_list.front);

    while (ptr) {
        bt_status_t ret;
        bt_linknode_t *f_node = bt_linknode_travel_node(&bt_hummingbird.module_free_handle_list,
                                                        bt_linknode_cmp_backward, (void *)ptr);
        if (f_node) {
            ret = ptr->callback((void *)ptr);
            if (ret != BT_STATUS_SUCCESS) {
                bt_module_handle_notify();
                return;
            }
            bt_linknode_remove_node(f_node, BT_NODE_FRONT);
        }
        ptr = (bt_module_free_handle_list_t *) ptr->free_handle_list.front;
    }
}

void bt_module_add_to_free_list(bt_linknode_t *node)
{
    bt_linknode_t *head = &(bt_hummingbird.module_free_handle_list);
    bt_linknode_t *tmp = NULL;
    tmp = bt_linknode_travel_node(head, bt_linknode_cmp_backward, node);
    if(tmp == NULL){
        bt_linknode_insert_node(&bt_hummingbird.module_free_handle_list, node, BT_NODE_BACK);
    }

    bt_module_handle_notify();
}

void bt_module_delete_from_free_list(bt_linknode_t *node)
{
    BT_ASSERT(node && "NULL oom node");
    bt_linknode_t *head = &(bt_hummingbird.module_free_handle_list);
    bt_linknode_t *src_node = (bt_linknode_t *)node;
    bt_linknode_t *dest_node = NULL;
    dest_node = bt_linknode_travel_node(head, bt_linknode_cmp_backward, src_node);
    BT_ASSERT(dest_node && "NULL dest node");
    bt_linknode_remove_node(dest_node, BT_NODE_FRONT);
}

void *bt_alloc_rx_buffer_from_external(uint32_t buffer_size)
{
#ifndef __BT_HB_DUO__
    bt_hci_packet_linknode_t *rx_ptr = NULL;
#else
    bt_hci_packet_t *rx_ptr = NULL;
    uint32_t total_size = buffer_size + sizeof(bt_hci_packet_t);
    BT_ASSERT(buffer_size < 896 && "buffer_size is larger than 896 B");
    BT_MUTEX_LOCK();
    rx_ptr = (bt_hci_packet_t *)bt_mm_allocate_packet(BT_MEMORY_RX_BUFFER, total_size);
    if (rx_ptr == NULL) {
        BT_LOG_MSGID_W("COMMON", BTCOMMON_002, 0);
    } else {
        bt_memset(rx_ptr, 0, total_size);
        rx_ptr->packet_length = total_size;
        rx_ptr->offset = sizeof(bt_hci_packet_t);
        rx_ptr->ref_count = 1;
    }
    BT_MUTEX_UNLOCK();
#endif
    return rx_ptr;
}

#ifdef __BT_HB_DUO__
#define BT_TIMCON_NCLK_REG  (0x00000038)
#define BT_TIMCON_INTRA_REG (0x00000040)
#define BT_NCLK_PRECISE_SLOT (625)
#define BT_NCLK_PRECISE_FRAME (1250)
#define BT_NCLK_BIT_MASK (0x0FFFFFFC)
bt_avm_clk_offset_cmd_t g_clk_offset_info = {0};

extern bt_status_t bt_avm_set_N9_sleep_lock(bool lock);
#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_drvier_get_timconn_base=_default_bt_drvier_get_timconn_base")
#pragma comment(linker, "/alternatename:_bt_avm_set_N9_sleep_lock=_default_bt_avm_set_N9_sleep_lock")
#pragma comment(linker, "/alternatename:_bt_driver_get_bt_clock_directly=_default_bt_driver_get_bt_clock_directly")
#pragma comment(linker, "/alternatename:_bt_driver_get_bt_clock=_default_bt_driver_get_bt_clock")
#pragma comment(linker, "/alternatename:_bt_driver_get_bt_clock_with_gpt=_default_bt_driver_get_bt_clock_with_gpt")
#pragma comment(linker, "/alternatename:_bt_avm_get_bt_clock_with_gpt_count=_default_bt_avm_get_bt_clock_with_gpt_count")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_drvier_get_timconn_base = default_bt_drvier_get_timconn_base
#pragma weak bt_avm_set_N9_sleep_lock = default_bt_avm_set_N9_sleep_lock
#pragma weak bt_driver_get_bt_clock_directly = default_bt_driver_get_bt_clock_directly
#pragma weak bt_driver_get_bt_clock = default_bt_driver_get_bt_clock
#pragma weak bt_driver_get_bt_clock_with_gpt = default_bt_driver_get_bt_clock_with_gpt
#pragma weak bt_avm_get_bt_clock_with_gpt_count = default_bt_avm_get_bt_clock_with_gpt_count
#else
#error "Unsupported Platform"
#endif

uint32_t default_bt_drvier_get_timconn_base()
{
    return 0XA3350000;
}

bt_status_t default_bt_avm_set_N9_sleep_lock(bool lock)
{
    return BT_STATUS_SUCCESS;
}

bool default_bt_driver_get_bt_clock_directly(void)
{
    return false;
}

bt_status_t default_bt_driver_get_bt_clock(uint16_t hci_handle, bt_clock_t *bt_clk)
{
    return BT_STATUS_FAIL;
}

bt_status_t default_bt_driver_get_bt_clock_with_gpt(uint16_t hci_handle, bt_clock_t *bt_clk, uint32_t *gpt_count)
{
    return BT_STATUS_FAIL;
}

bt_status_t default_bt_avm_get_bt_clock_with_gpt_count(uint16_t handle)
{
    return BT_STATUS_FAIL;
}

void bt_get_native_clock(bt_clock_t *bt_clock)
{
    uint32_t timconn_base = bt_drvier_get_timconn_base();
    uint32_t nclk, intra;
    do {
        nclk = *((uint32_t volatile *)(timconn_base + BT_TIMCON_NCLK_REG));
        intra = *((uint32_t volatile *)(timconn_base + BT_TIMCON_INTRA_REG));

        if (((nclk & 0x03) != 0x03) || ((intra << 1) > BT_NCLK_PRECISE_SLOT)) {
            // to avoid nclk_intra has carried when nclk has been read.
            break;
        }
    } while (1);

    bt_clock->nclk = ((nclk & BT_NCLK_BIT_MASK) + ((intra << 1) / BT_NCLK_PRECISE_SLOT))
                     & BT_NCLK_BIT_MASK;
    bt_clock->nclk_intra = ((intra << 1) % BT_NCLK_PRECISE_SLOT) >> 1;
}

void bt_get_bt_clock_offset(uint32_t gap_handle, bt_clock_t *offset)
{
    bt_handle_t handle = 0;
    bt_clock_offset_info_t *p_base = g_clk_offset_info.base_addr;
    bt_gap_connection_t *conn = (bt_gap_connection_t *)gap_handle;
    uint32_t link_num = g_clk_offset_info.link_num;
    uint32_t link_idx = 0;

    if (conn == NULL || offset == NULL) {
        return ;
    }

    handle = conn->handle;
    while (link_idx < link_num) {
        uint8_t *temp_ptr = NULL;
        if (p_base->handle == handle) {
            offset->nclk = p_base->offset_nclk;
            offset->nclk_intra = p_base->offset_intra;
            break;
        }
        ++link_idx;
        temp_ptr = ((uint8_t *)p_base + sizeof(bt_clock_offset_info_t));
        p_base = (bt_clock_offset_info_t *)temp_ptr;
    }
}

bool bt_clock_check_carry(bt_clock_t *bt_clk, bt_clock_t *offset)
{
    bool carry_zone = false;
    if (bt_clk->nclk_intra < BT_NCLK_PRECISE_SLOT &&
        bt_clk->nclk_intra >= offset->nclk_intra) {
        carry_zone = true;
    } else if (offset->nclk_intra > BT_NCLK_PRECISE_SLOT &&
               (bt_clk->nclk_intra > offset->nclk_intra ||
                bt_clk->nclk_intra < BT_NCLK_PRECISE_SLOT)) {
        carry_zone = true;
    }

    return carry_zone;
}

bt_status_t bt_get_bt_clock_with_gpt(uint32_t gap_handle, bt_clock_t *bt_clock, uint32_t *gpt_count)
{
    bt_gap_connection_t *conn = (bt_gap_connection_t *)gap_handle;
    bt_status_t status = BT_STATUS_FAIL;
    BT_MUTEX_LOCK();
    if (conn == NULL || bt_clock == NULL) {
        BT_MUTEX_UNLOCK();
        return BT_STATUS_FAIL;
    }

    bt_mm_pool_control_blk_t *bt_ctx = (bt_mm_pool_control_blk_t *)bt_mm_get_sync_pointer_info();
    const bt_clock_offset_info_t *p_base = g_clk_offset_info.base_addr;
    const uint32_t link_num = g_clk_offset_info.link_num;
    bt_handle_t handle = conn->handle;

    if (bt_driver_get_bt_clock_directly()) {
        bt_status_t status = bt_driver_get_bt_clock_with_gpt(handle, bt_clock, gpt_count);
        BT_LOG_MSGID_W("COMMON", BTCOMMON_003, 5,
                       handle, bt_clock->nclk, bt_clock->nclk_intra, status, 0);
    } else {
        status = bt_avm_get_bt_clock_with_gpt_count(handle);
        do {
            hal_gpt_delay_us(1);
        } while (!(bt_ctx->reserved & (1 << 5)));
        //hal_gpio_set_output(2, 0);
        uint32_t *temp_ptr = (uint32_t *)((uint8_t *)p_base + link_num * sizeof(bt_clock_offset_info_t));

        bt_clock->nclk = temp_ptr[0];
        bt_clock->nclk_intra = (temp_ptr[1] & 0xffff);
        *gpt_count = temp_ptr[2];

        if (bt_clock->nclk_intra >= BT_NCLK_PRECISE_FRAME) {
            bt_clock->nclk_intra -= BT_NCLK_PRECISE_FRAME;
        }
    }

    BT_MUTEX_UNLOCK();

    return status;
}

bt_status_t bt_get_bt_clock(uint32_t gap_handle, bt_clock_t *bt_clock)
{
    bt_gap_connection_t *conn = (bt_gap_connection_t *)gap_handle;
    bt_handle_t handle = 0;
    bt_clock_t native_clk = {0};
    bt_clock_t offset = {0};
    bool carry = false;
    BT_MUTEX_LOCK();
    if (conn == NULL || bt_clock == NULL) {
        BT_MUTEX_UNLOCK();
        return BT_STATUS_FAIL;
    }

    handle = conn->handle;
    if (bt_driver_get_bt_clock_directly()) {
        bt_status_t status = bt_driver_get_bt_clock(handle, bt_clock);
        BT_LOG_MSGID_W("COMMON", BTCOMMON_003, 5,
                       handle, bt_clock->nclk, bt_clock->nclk_intra, status, 0);

        BT_MUTEX_UNLOCK();

        return status;
    }

    bt_avm_set_N9_sleep_lock(true);
    bt_get_native_clock(&native_clk);
    bt_avm_set_N9_sleep_lock(false);

    bt_get_bt_clock_offset(gap_handle, &offset);
    BT_LOG_MSGID_W("COMMON", BTCOMMON_003, 5,
                   handle, native_clk.nclk, native_clk.nclk_intra, offset.nclk, offset.nclk_intra);

    native_clk.nclk += offset.nclk;
    native_clk.nclk_intra += offset.nclk_intra;
    if (native_clk.nclk_intra >= BT_NCLK_PRECISE_FRAME) {
        native_clk.nclk_intra -= BT_NCLK_PRECISE_FRAME;
        //native_clk.nclk += 4;
        native_clk.nclk &= 0x0FFFFFFC;
    }

    bt_clock->nclk = native_clk.nclk;
    bt_clock->nclk_intra = native_clk.nclk_intra;

    carry = bt_clock_check_carry(bt_clock, &offset);
    if (carry) {
        native_clk.nclk -= 4;
    }
    //BT_LOGW("COMMON", "[get_clk] carry info, carry:%d", carry);
    BT_MUTEX_UNLOCK();

    return BT_STATUS_SUCCESS;
}
#endif
