/* Copyright Statement:
 *
 * (C) 2019  Airoha Technology Corp. All rights reserved.
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
 * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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


//<<<=====================================================================>>>//
//<<                            INCLUDE HEADER FILES                       >>//
//<<<=====================================================================>>>//
#include "avm_external.h"
#include "pka_porting_layer.h"
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/hci.h>
#include "bt_linknode.h"
#include "bt_common_upper_layer.h"
//<<<=====================================================================>>>//
//<<                            Constant                                  >>//
//<<<=====================================================================>>>//

//<<<=====================================================================>>>//
//<<                            Global Variables                          >>//
//<<<=====================================================================>>>//
avm_pka_callbacks_t avm_callbacks;
uint8_t gDchsRole = DCHS_ROLE_NONE;

//<<<=====================================================================>>>//
//<<                             Function                                  >>//
//<<<=====================================================================>>>/ uint16_t length);
void bt_avm_pka_register_callbacks(avm_pka_callbacks_t callbacks)
{
    avm_callbacks = callbacks;
}

#define BTCON_IPC_MSG_TYPE_HCI_CMD 0
#define BTCON_IPC_MSG_TYPE_ACL_U_TX 1
#define BTCON_IPC_MSG_TYPE_ISO_U_TX 5
#define OS_ADDITIONAL_BYTES_FOR_MEMORY_ARRAY 24
void bt_tx_notify_pka(uint8_t type, unsigned char *q_header)
{
    //bt_debug_port(8,1);
    uint32_t Caller = (uint32_t) __builtin_return_address(0);
    uint8_t *ptr = avm_callbacks.bt_hb_tx_dequeue(type, q_header);
    ptr = ptr - bt_get_pka_header_size(BT_MEMORY_TYPE_TX_BUFFER);

    // init osmem blk without eob, so no need to fill in length
    void *pMsg = pka_init_osmem_blk(ptr, 0, BT_MEMORY_TYPE_TX_BUFFER, Caller);

    *((uint16_t *)pMsg) = bt_get_pka_header_size(BT_MEMORY_TYPE_TX_BUFFER) - OS_ADDITIONAL_BYTES_FOR_MEMORY_ARRAY + avm_callbacks.bt_get_hb_header_size() + 1;

    switch (type) {
        case BT_QUEUE_TX_ACL_TYPE: {
            type = BTCON_IPC_MSG_TYPE_ACL_U_TX;
            break;
        }
        case BT_QUEUE_TX_CMD_TYPE:
            type = BTCON_IPC_MSG_TYPE_HCI_CMD;
            break;
#if (LE_BT52_ISOAL_SUPPORTED == TRUE)
        case BT_QUEUE_TX_ISO_TYPE:
            type = BTCON_IPC_MSG_TYPE_ISO_U_TX;
            break;
#endif
        default:
            return;
    }

    bt_hci_notify_pka(pMsg, type);
}

uint16_t bt_get_pka_header_size(uint8_t type)
{
    if ((type == BT_MEMORY_TYPE_TX_BUFFER) || (type == BT_MEMORY_TYPE_RX_BUFFER)) {
        return OS_ADDITIONAL_BYTES_FOR_MEMORY_ARRAY + 20;
    } else {
        return 0;
    }
}

int bt_set_controller_sleep_policy(bt_sleep_policy_t *policy)
{
    struct net_buf *buf = NULL;

    bt_sleep_policy_t *policy_config = NULL;
    buf = bt_hci_cmd_create(BT_HCI_CMD_VENDOR_SET_LC_SLP_POLICY,
                sizeof(bt_sleep_policy_t));
    if (!buf) {
        return -1;
    }

    policy_config = net_buf_add(buf, sizeof(bt_sleep_policy_t));
    policy_config->slp_policyctl = policy->slp_policyctl;
    policy_config->slp_policy = policy->slp_policy;
    return bt_hci_cmd_send(BT_HCI_CMD_VENDOR_SET_LC_SLP_POLICY, buf);

}

extern bt_status_t bt_driver_send_hci_cmd(const bt_hci_cmd_t *cmd, uint32_t data, bt_timeout_callback_t callback);
bt_status_t bt_set_controller_sleep_policy_direct(bt_sleep_policy_t *policy)
{
    bt_hci_cmd_t cmd = {0};
    cmd.cmd_code = BT_HCI_CMD_VENDOR_SET_LC_SLP_POLICY;
    cmd.length = sizeof(bt_sleep_policy_t);
    cmd.param = policy;
    bt_driver_send_hci_cmd(&cmd, 0, NULL);
    return BT_STATUS_SUCCESS;
}




