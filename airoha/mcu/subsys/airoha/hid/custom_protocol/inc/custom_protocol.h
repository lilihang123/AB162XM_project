/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
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

#ifndef _CUSTOM_PROTOCOL_H_
#define _CUSTOM_PROTOCOL_H_

#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include "bt_ull_le_hid_service.h"

/* Public define -------------------------------------------------------------*/
#define AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_REPORT_MODE
#define AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_INTERRUPT_MODE

#define EPIO_CUSTOM_PROTOCOL_MIX_WITH_HID_PACKET_SIZE 4

/* Public typedef ------------------------------------------------------------*/
typedef void (*epio_custom_protocol_usb_recv_data_callback_t)(const struct device *dev, uint16_t len, uint8_t *buf);
typedef void (*epio_custom_protocol_bt_recv_data_callback_t)(bt_addr_t *remote_address, uint16_t len, uint8_t *buf);

typedef struct {
    epio_custom_protocol_usb_recv_data_callback_t   usb_recv_data_callback;
    epio_custom_protocol_bt_recv_data_callback_t    bt_recv_data_callback;
} epio_process_callback_t;

typedef uint8_t epio_custom_protocol_path;
enum {
    EPIO_CUSTOM_PROTOCOL_USB,
    EPIO_CUSTOM_PROTOCOL_BT,
};

/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
extern int epio_usb_hid_send_data(const struct device *dev, uint16_t len, uint8_t *buf);
extern int epio_bt_hid_send_data(bt_addr_t *remote_address, uint16_t len, uint8_t *buf);
extern int epio_bt_hid_recv_data(bt_addr_t *remote_address, uint16_t len, uint8_t *buf);
#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE)
extern int epio_bt_hid_send_data_mix_with_hid_packet(bt_addr_t *remote_address, uint16_t len, uint8_t *buf);
extern int epio_bt_hid_recv_data_mix_with_hid_packet(bt_addr_t *remote_address, uint16_t len, uint8_t *buf);
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE */
extern const struct device *epio_custom_protocol_get_interrupt_transfer_usb_device(void);
extern const struct device *epio_custom_protocol_get_control_transfer_usb_device(void);
void epio_custom_protocol_register_callback(epio_process_callback_t *callback);
void epio_custom_protocol_enable(epio_custom_protocol_path path);
void epio_custom_protocol_disable(epio_custom_protocol_path path);
extern void epio_custom_protocol_init(void);
extern void epio_custom_protocol_deinit(void);

#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE */

#endif /* _CUSTOM_PROTOCOL_H_ */
