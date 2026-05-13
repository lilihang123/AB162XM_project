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

#ifndef __AIROHA_USB_INTERNAL_H__
#define __AIROHA_USB_INTERNAL_H__

#include <inttypes.h>
#include <zephyr/drivers/usb/usb_dc.h>

struct usb_hid_class_subdescriptor {
	uint8_t bDescriptorType;
	uint16_t wDescriptorLength;
} __packed;

struct usb_hid_descriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t bcdHID;
	uint8_t bCountryCode;
	uint8_t bNumDescriptors;

	/*
	 * Specification says at least one Class Descriptor needs to
	 * be present (Report Descriptor).
	 */
	struct usb_hid_class_subdescriptor subdesc[1];
} __packed;

struct usb_hid_config {
	struct usb_if_descriptor if0;
	struct usb_hid_descriptor if0_hid;
	struct usb_ep_descriptor if0_int_in_ep;
#ifdef CONFIG_ENABLE_HID_INT_OUT_EP
	struct usb_ep_descriptor if0_int_out_ep;
#endif
} __packed;

/**
 * @brief Get the user name from the given ID.
 *
 * This function retrieves the name of the user associated with the given ID.
 *
 * @param id[in] User ID
 * @return Pointer to store the user's name.
 */
const char *air_usb_get_user_name(uint32_t id);

/**
 * @brief Check if the given user ID is valid.
 *
 * @param id[in] User ID
 *
 * @return 0 on success, -EINVAL if user not found.
 */
int air_usb_check_user_id(uint32_t id);

/******************************************************************************
 * Airoha USB DC Custom funcion
 *****************************************************************************/
/**
 * This section should align file
 * airoha/mcu/drivers/ab162x/usb/device/usb_dc_airoha.h
 */
typedef void (*usb_dc_plug_in_cb_t)(void);
typedef void (*usb_dc_plug_out_cb_t)(void);

int usb_dc_register_plug_in_cb(usb_dc_plug_in_cb_t cb);

int usb_dc_register_plug_out_cb(usb_dc_plug_in_cb_t cb);

bool usb_dc_is_vbus_ready(void);

void usb_plugin_cb(void);
void usb_plugout_cb(void);

#endif /* __AIROHA_USB_INTERNAL_H__ */
