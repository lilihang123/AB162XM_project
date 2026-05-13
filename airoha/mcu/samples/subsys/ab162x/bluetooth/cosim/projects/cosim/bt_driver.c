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

#include "bt_hci_internal.h"
#include "bt_memory.h"
#include "bt_hci_log.h"
#include "bt_os_layer_api.h"
#include "bt_driver.h"
#include "bt_log.h"
#include "bt_driver_internal.h"
#include "bt_hci_spec.h"
#include "avm_external.h"
#include "bt_timer.h"

//#define BT_LMP_BUFFER_SIZE   (15 * 1024)
//ATTR_SHARE_ZIBT_4BYTE_ALIGN char pka_lmp_buf[BT_LMP_BUFFER_SIZE] __attribute__((aligned(4)));

//static uint32_t nvic_mask = 0;
static uint8_t bt_driver_powered_on = 0;
static uint8_t bt_driver_tx_power_config[10] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
uint32_t gHostTaskHandle = 0;
static bt_firmware_type_t bt_n9_bin_type_index = BT_FIRMWARE_TYPE_INVALID;

uint8_t *bt_driver_get_tx_power_config_table(void)
{
    return &bt_driver_tx_power_config[0];
}

bool bt_driver_is_driver_powered_on(void)
{
    return (bt_driver_powered_on == 1);
}

bt_status_t bt_driver_set_tx_power(uint8_t *tx_power)
{
    BT_ASSERT(tx_power);
    bt_driver_tx_power_config[0] = tx_power[0];
    bt_driver_tx_power_config[1] = 0;
    bt_driver_tx_power_config[2] = tx_power[2];
    bt_driver_tx_power_config[3] = tx_power[3];
    bt_driver_tx_power_config[4] = tx_power[4];
    bt_driver_tx_power_config[5] = tx_power[5];
    bt_driver_tx_power_config[6] = tx_power[1];
    bt_driver_tx_power_config[7] = 0;
    bt_driver_tx_power_config[8] = tx_power[1];
    bt_driver_tx_power_config[9] = 0;

    BT_DRVLOG_MSGID_I("BTIF", BTIF_139, 10,
        bt_driver_tx_power_config[0],
        bt_driver_tx_power_config[1],
        bt_driver_tx_power_config[2],
        bt_driver_tx_power_config[3],
        bt_driver_tx_power_config[4],
        bt_driver_tx_power_config[5],
        bt_driver_tx_power_config[6],
        bt_driver_tx_power_config[7],
        bt_driver_tx_power_config[8],
        bt_driver_tx_power_config[9]);

    return BT_STATUS_SUCCESS;
}

bt_status_t bt_driver_advance_set_tx_power(uint8_t *tx_power)
{
    BT_ASSERT(tx_power);
    bt_memcpy(bt_driver_tx_power_config, tx_power, sizeof(bt_driver_tx_power_config));
    BT_DRVLOG_MSGID_I("BTIF", BTIF_139, 10,
        bt_driver_tx_power_config[0],
        bt_driver_tx_power_config[1],
        bt_driver_tx_power_config[2],
        bt_driver_tx_power_config[3],
        bt_driver_tx_power_config[4],
        bt_driver_tx_power_config[5],
        bt_driver_tx_power_config[6],
        bt_driver_tx_power_config[7],
        bt_driver_tx_power_config[8],
        bt_driver_tx_power_config[9]);

    return BT_STATUS_SUCCESS;
}

static struct k_mutex bt_driver_mutex;
void bt_driver_hw_semaphore_lock(void)
{
    //BT_LOGI(GROUP_BT_DRIVER, "bt_driver_hw_semaphore_lock\n");
    //BT_ASSERT(bt_driver_mutex);
    //k_mutex_lock(&bt_driver_mutex, K_FOREVER);
}

void bt_driver_hw_semaphore_unlock(void)
{
    //BT_LOGI(GROUP_BT_DRIVER, "bt_driver_hw_semaphore_unlock\n");
    //BT_ASSERT(bt_driver_mutex);
    //k_mutex_unlock(&bt_driver_mutex);
}

void bt_driver_init(void)
{
    k_mutex_init(&bt_driver_mutex);
}

void bt_driver_deinit(void)
{
    //bt_os_layer_delete_mutex(bt_driver_mutex);
    //bt_driver_mutex = 0;
}
extern void BT_Controller_Init(void);
extern void BT_Controller_Deinit(void);
bt_status_t bt_driver_power_on(void)
{
    BT_LOGI(GROUP_BT_DRIVER, "bt_driver_power_on \n");


    avm_pka_callbacks_t pka_avm_callbacks;
    BT_DRVLOG_MSGID_I("BTIF", BTIF_140, 0);
    const uint8_t setup_evt[] = {0x04, 0x0E, 0x19, 0x01, 0x00, 0x00, 'b', 't', 0x20, 'c', 'o', 'n', 't', 'r', 'o', 'l', 'l', 'e', 'r', 0x20, 'p', 'o', 'w', 'e', 'r', 0x20, 'o', 'n'};

    if (0 == bt_driver_powered_on) {
        bt_driver_init();
        bt_hci_log(1, setup_evt, sizeof(setup_evt));
        pka_avm_callbacks.bt_hb_mm_allocate = (unsigned char *(*)(uint8_t type, unsigned int size))bt_hb_mm_allocate;
        pka_avm_callbacks.bt_hb_mm_free = bt_hb_mm_free;
        pka_avm_callbacks.bt_hb_rx_enqueue = bt_hb_rx_enqueue;
        pka_avm_callbacks.bt_hb_tx_dequeue = bt_hb_tx_dequeue;
        pka_avm_callbacks.bt_get_hb_header_size = bt_get_hb_header_size;
        pka_avm_callbacks.bt_rx_notify_hb = bt_rx_notify_hb;
        bt_avm_pka_register_callbacks(pka_avm_callbacks);
        BT_LOGI(GROUP_BT_DRIVER, "before BT_Controller_Init \n" ); 
        BT_Controller_Init();
        BT_LOGI(GROUP_BT_DRIVER, "bt_driver_power_on:: BT_Controller_Init() skipped  \n" ); 
        

        bt_driver_powered_on = 1;
        BT_DRVLOG_MSGID_I("BTIF", BTIF_142, 0);
    }
    return BT_STATUS_SUCCESS;
}

bt_status_t bt_driver_power_off(void)
{
    extern void bt_mm_reinit_buffer_internal(bt_memory_packet_t type);

    bt_status_t bRet = BT_STATUS_SUCCESS;
    BT_DRVLOG_MSGID_I("BTIF", BTIF_143, 0);
    const uint8_t controller_power_off_evt[] = {0x04, 0xF6, 0x17, 'b', 't', 0x20, 'c', 'o', 'n', 't', 'r', 'o', 'l', 'l', 'e', 'r', 0x20, 'p', 'o', 'w', 'e', 'r', 0x20, 'o', 'f', 'f'};

    /*delete pikachu tasks*/
    BT_Controller_Deinit();
    bt_driver_powered_on = 0;
    /*reset init table index*/
    //bt_init_reset_table();
    
    bt_driver_clear_queue(BT_QUEUE_TYPE_RX);
    bt_driver_clear_queue(BT_QUEUE_TYPE_TX_ACL);
    bt_driver_clear_queue(BT_QUEUE_TYPE_TX_CMD);
    bt_driver_clear_queue(BT_QUEUE_TYPE_TX_IF_PACKET);
    bt_mm_reinit_buffer(BT_MEMORY_RX_BUFFER);
    bt_mm_reinit_buffer(BT_MEMORY_TX_BUFFER);
    
    bt_driver_deinit();
    bt_hci_log(1, controller_power_off_evt, sizeof(controller_power_off_evt));
    //bt_driver_deinit_dut_mode();
    return bRet;
}

void bt_driver_tx_notify_controller(bt_hb_queue_type_t type, uint8_t *q_header)
{
    #if 0
    if ((bt_driver_is_dut_mode_enabled() && bt_driver_is_dut_mode_enable_complete()) || 
        (bt_driver_is_relay_mode_enabled() && bt_driver_is_relay_mode_enable_complete())) {
        bt_timer_stop_all_timer();
        bt_driver_clear_queue(BT_QUEUE_TYPE_TX_ACL);
        bt_driver_clear_queue(BT_QUEUE_TYPE_TX_CMD);
        bt_driver_clear_queue(BT_QUEUE_TYPE_TX_IF_PACKET);
        return;
    }
    #endif
    bt_tx_notify_pka(type, q_header);
}

uint8_t bt_driver_firmware_type_set(bt_firmware_type_t type)
{
    if (type >= BT_FIRMWARE_TYPE_MAX) {
        return 1;
    }
    bt_n9_bin_type_index = type;
    return 0;
}

bt_firmware_type_t bt_driver_firmware_type_get(void)
{
    return bt_n9_bin_type_index;
}

