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

#ifndef AIR_USB_XINPUT_H
#define AIR_USB_XINPUT_H

#include <zephyr/drivers/usb/usb_dc.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/kernel.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef AIR_USB_XINPUT_ENABLE
/* XInput Configuration
 * XInput uses Vendor Class (0xFF) with SubClass 0x5D and Protocol 0x01
 */
#define XINPUT_VENDOR_CLASS    0xFF
#define XINPUT_VENDOR_SUBCLASS 0x5D
#define XINPUT_VENDOR_PROTOCOL 0x01

#define XINPUT_IN_EP_ADDR      0x81
#define XINPUT_OUT_EP_ADDR     0x02
#define XINPUT_EP_MPS          64

/* Xinput specific descriptor type (0x21 is HID class descriptor type, reused for Xinput) */
#define USB_DESC_XINPUT 0x21

typedef int (*air_xinput_data_received_cb_t)(const struct device *dev, uint16_t len, const uint8_t *buf);
typedef int (*air_xinput_tx_done_cb_t)(const struct device *dev);

/* Xinput device context structure */
typedef struct {
	const struct device *dev;
	bool tx_busy;
	uint32_t tx_user_id;
	air_xinput_data_received_cb_t rx_cb;
	air_xinput_tx_done_cb_t tx_done_cb;
	uint32_t rx_cb_user_id;
	uint32_t tx_done_cb_user_id;
	bool suspended;
	bool configured;
} xinput_device_ctx_t;

int air_usb_xinput_device_register(const struct device *dev);
int air_usb_xinput_tx(uint32_t user_id, const struct device *dev, uint16_t len, uint8_t *data);
int air_usb_xinput_register_data_received_cb(uint32_t user_id, const struct device *dev, 
                                              air_xinput_data_received_cb_t cb);
int air_usb_xinput_register_tx_done_cb(uint32_t user_id, const struct device *dev,
                                        air_xinput_tx_done_cb_t cb);

#endif

#ifdef __cplusplus
}
#endif

#endif /* AIR_USB_XINPUT_H */