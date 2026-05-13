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

#ifndef __BT_HCI_VENDOR_EVENT_DISPTACH_H__
#define __BT_HCI_VENDOR_EVENT_DISPTACH_H__

#include <zephyr/device.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/buf.h>
#include <zephyr/bluetooth/bluetooth.h>

/**
 * @brief Define moudle type.
 */
typedef uint8_t bt_hci_vendor_event_module_t;
#define BT_HCI_VENDOR_EVENT_MODULE_APP                              0x00   /**< Application module type. */
#define BT_HCI_VENDOR_EVENT_MODULE_ULL_HID_SRV                      0x01   /**< ULL HID service module type. */
#define BT_HCI_VENDOR_EVENT_MODULE_MAX                              0x02   /**< Invalid module type. */

typedef int (* bt_hci_vendor_event_cb)(int err, uint8_t event_code, void *event_data);

/*for ull hid service*/
#define BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_ESTABLISHED                 0xFA
#define BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_DISCONNECT_COMPLETE         0xFB
#define BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_RR_CHANGE                   0xFC
#define BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_TX_POWER                    0xFD
#define BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_CONN_INFO                   0xFE
#define BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_ADV_REPORT                  0xFF

/*for vendor periodic adv*/
#define BT_HCI_SUBEVT_LE_VENDOR_AIR_PADV_TAIL_DATA_RECEIVED  0xD0
#define BT_HCI_SUBEVT_LE_VENDOR_AIR_PADV_SYNCINFO_RECEIVED   0xD3

/*******************************************************************************************************************************************************************************
* 
* Define AIR HID CIS APIS
*
*******************************************************************************************************************************************************************************/

/**
 * @brief    This function init bt hci vendor event dispatch .
 */
void bt_hci_vendor_event_dispatch_init(void);

/**
 * @brief     This function set AIR HID CIG.
 * @param[in] module             is the module to register in hci vendor event module #bt_ull_le_set_air_hid_cig_t.
 * @param[in] callback           is the callback to listern hci vendor event #bt_hci_vendor_event_cb.
 * @return                       #0, the operation completed successfully.
 *                               #otherwise, the operation has failed.
 */
int bt_hci_vendor_event_dispatch_register(bt_hci_vendor_event_module_t module, bt_hci_vendor_event_cb callback);

/**
 * @brief    This function init bt hci vendor event dispatch .
 */
void bt_hci_vendor_event_dispatch_deinit(void);

#endif