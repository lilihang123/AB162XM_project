/* Copyright Statement:
*
* (C) 2024 Airoha Technology Corp. All rights reserved.
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
* the License Agreement ("Permitted User"). If you are not a Permitted User,
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
/* Airoha restricted information */

#include "bt_hci_vendor_event_dispatch.h"
#include "zephyr/logging/log.h"

LOG_MODULE_REGISTER(HCI_EVT_DISPATCH);

#define BT_HCI_VENDOR_EVT_LOG     "[HCI_VENDOR_EVNT][DISPATCH] "

typedef struct {
    bt_hci_vendor_event_module_t         module;
    bt_hci_vendor_event_cb               callback;
} bt_hci_vendor_evnet_callback_t;

static bt_hci_vendor_evnet_callback_t g_bt_hci_vendor_event_cb[BT_HCI_VENDOR_EVENT_MODULE_MAX] = {0};

struct hci_evt_prop {
	uint8_t  subevent;
} __packed;

static bool prop_cb(struct net_buf_simple *buf)
{
	struct hci_evt_prop *pe;

	pe = net_buf_simple_pull_mem(buf, sizeof(*pe));
    uint8_t event_code = pe->subevent;
    switch (event_code) {
    case BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_ESTABLISHED:
    case BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_DISCONNECT_COMPLETE: 
    case BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_RR_CHANGE: 
    case BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_CONN_INFO:
    case BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_ADV_REPORT:{
            if(g_bt_hci_vendor_event_cb[BT_HCI_VENDOR_EVENT_MODULE_ULL_HID_SRV].callback){
                g_bt_hci_vendor_event_cb[BT_HCI_VENDOR_EVENT_MODULE_ULL_HID_SRV].callback(0, event_code, buf->data);
            } else {
                LOG_ERR(BT_HCI_VENDOR_EVT_LOG"prop_cb ull hid service is not register!!");
            }
            break;
        }
    case BT_HCI_SUBEVT_LE_VENDOR_AIR_PADV_TAIL_DATA_RECEIVED: {
            if(g_bt_hci_vendor_event_cb[BT_HCI_VENDOR_EVENT_MODULE_APP].callback){
                g_bt_hci_vendor_event_cb[BT_HCI_VENDOR_EVENT_MODULE_APP].callback(0, event_code, buf->data);
            }
        }
    break;
    default: {
            LOG_ERR(BT_HCI_VENDOR_EVT_LOG"prop_cb event_code: 0x%x is not support!!", event_code);
            break;
        }
    }

	return false;
}

void bt_hci_vendor_event_dispatch_init(void)
{
    LOG_INF(BT_HCI_VENDOR_EVT_LOG"bt_hci_vendor_event_dispatch_init");
    memset(&g_bt_hci_vendor_event_cb, 0, sizeof(bt_hci_vendor_evnet_callback_t) * BT_HCI_VENDOR_EVENT_MODULE_MAX);
    /* Register the prop callback */
	bt_hci_register_vnd_evt_cb(prop_cb);
    return;
}

int bt_hci_vendor_event_dispatch_register(bt_hci_vendor_event_module_t module, bt_hci_vendor_event_cb callback)
{
    LOG_INF(BT_HCI_VENDOR_EVT_LOG"bt_hci_vendor_event_dispatch_register, module: 0x%x, 0x%x", module, callback);
    if (g_bt_hci_vendor_event_cb[module].callback == NULL && module < BT_HCI_VENDOR_EVENT_MODULE_MAX) {
        g_bt_hci_vendor_event_cb[module].callback = callback;
        g_bt_hci_vendor_event_cb[module].module = module;
        return 0;
    }
    LOG_ERR(BT_HCI_VENDOR_EVT_LOG"bt_hci_vendor_event_dispatch_register fail!!");
    return -EPERM;
}

void bt_hci_vendor_event_dispatch_deinit(void)
{
    memset(&g_bt_hci_vendor_event_cb, 0, sizeof(bt_hci_vendor_evnet_callback_t) * BT_HCI_VENDOR_EVENT_MODULE_MAX);
    return;
}
