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

#ifndef AIR_USB_HID_H
#define AIR_USB_HID_H

#include <zephyr/drivers/usb/usb_dc.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/class/usb_hid.h>
#include <zephyr/kernel.h>
#include <inttypes.h>

#include "air_usb_hid_desc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define USB_HID_REPORT_TYPE_NO_REPORT_ID_BIT BIT(7)

#define USB_HID_REPORT_TYPE_INPUT   1
#define USB_HID_REPORT_TYPE_OUTPUT  2
#define USB_HID_REPORT_TYPE_FEATURE 3
#define USB_HID_REPORT_TYPE_INPUT_NO_REPORT_ID   (USB_HID_REPORT_TYPE_NO_REPORT_ID_BIT | USB_HID_REPORT_TYPE_INPUT)
#define USB_HID_REPORT_TYPE_OUTPUT_NO_REPORT_ID  (USB_HID_REPORT_TYPE_NO_REPORT_ID_BIT | USB_HID_REPORT_TYPE_OUTPUT)
#define USB_HID_REPORT_TYPE_FEATURE_NO_REPORT_ID (USB_HID_REPORT_TYPE_NO_REPORT_ID_BIT | USB_HID_REPORT_TYPE_FEATURE)
#define AIR_USB_HID_SET_REPOTR_BUFFER_LEN 64

struct set_report_work_data {
	void *cb;
	const struct device *dev;
	uint8_t type;
	uint8_t id;
	uint16_t len;
	uint8_t data[AIR_USB_HID_SET_REPOTR_BUFFER_LEN];
};

typedef int (*air_hid_get_report_cb_t)(const struct device *dev, uint8_t type, uint8_t id,
				       uint16_t len, uint8_t *buf);

typedef int (*air_hid_set_report_cb_t)(const struct device *dev, uint8_t type, uint8_t id,
				       uint16_t len, const uint8_t *buf);

typedef int (*air_hid_output_cb_t)(const struct device *dev, uint8_t type, uint8_t id, uint16_t len,
				   const uint8_t *buf);

typedef int (*air_hid_tx_done_cb_t)(const struct device *dev, uint8_t type, uint8_t id,
				    uint16_t len, const uint8_t *buf);

typedef int (*air_hid_tx_free_cb_t)(const struct device *dev);

int air_usb_hid_register_get_report_cb(uint32_t user_id, const struct device *dev, uint8_t type,
				       uint8_t id, uint16_t len, air_hid_get_report_cb_t cb);

int air_usb_hid_register_set_report_cb(uint32_t user_id, const struct device *dev, uint8_t type,
				       uint8_t id, uint16_t len, air_hid_set_report_cb_t cb);

int air_usb_hid_register_output_cb(uint32_t user_id, const struct device *dev, uint8_t type,
				   uint8_t id, uint16_t len, air_hid_output_cb_t cb);

int air_usb_hid_register_tx_done_cb(uint32_t user_id, const struct device *dev, uint8_t type,
				    uint8_t id, uint16_t len, air_hid_tx_done_cb_t cb);

int air_usb_hid_register_tx_free_cb(uint32_t user_id, const struct device *dev,
				    air_hid_tx_free_cb_t cb);

int air_usb_hid_tx(uint32_t user_id, const struct device *dev, uint16_t len, uint8_t *data);

extern const struct hid_ops airoha_usb_hid_ops;

/**
 * @brief
 *
 * @param buf
 * @param buf_size
 * @param report_types
 * @param report_nums
 * @return int
 *
 * ```
 * #include <zephyr/usb/usb_dc.h>
 * #include <zephyr/usb/class/usb_hid.h>
 *
 * #include "airoha/mcu/subsys/airoha/usb/inc/air_usb.h"
 *
 * int main(void) {
 * 	uint8_t report_desc[2048];
 * 	uint16_t report_desc_len = 0;
 * 	uint8_t report_types[2] = {
 * 		AIR_USB_HID_REPORT_GAMING_KB,
 * 		AIR_USB_HID_REPORT_CONSUMER,
 *      }
 *
 * 	air_usb_hid_generate_report_desc(report_desc, 2048,
 * 					 report_types, 2,
 * 				         &report_desc_len);
 *
 * 	usb_hid_register_device(dev, report_desc, report_desc_len, hidops);
 * }
 * ```
 */
int air_usb_hid_generate_report_desc(uint8_t *buf, uint16_t buf_size, uint8_t *report_types,
				     uint8_t *report_nums, uint16_t *desc_len);

int air_usb_hid_device_register(const struct device *dev);

int air_usb_hid_gen_rdesc(const struct device *dev, air_usb_hid_report_desc_t *descs,
			  uint8_t descn);

int air_usb_hid_get_rdesc_len(const struct device *dev);
const uint8_t *air_usb_hid_get_rdesc(const struct device *dev);
struct device *air_usb_hid_find_first_device_by_report(air_usb_hid_report_desc_t report);

/**
 * dev: whitch hid device protocol changed
 * protocol:
 *   0: boot mode (bios mode)
 *   1: reprot mode (normal mode)
 */
#define USB_PROTOCOL_BOOT_MODE   0
#define USB_PROTOCOL_REPORT_MODE 1
typedef int (*air_hid_protocol_change_cb_t)(const struct device *dev, uint8_t protocol);

int air_usb_hid_register_protocol_change_cb(uint32_t user_id, const struct device *dev,
					    air_hid_protocol_change_cb_t cb);

/**
 * @brief
 *
 * @param dev
 * @return int
 * @retval 1 (USB_PROTOCOL_REPORT_MODE)
 * @retval 0 (USB_PROTOCOL_BOOT_MODE)
 */
int air_usb_hid_get_protocol_mode(const struct device *dev);

/**
 * @brief Setup PKTDONE EINT of HID device.
 *
 * @param dev[in] The hid device
 * @param dir[in] Direction of the endpoint (1:TX(IN) or 0:RX(OUT))
 * @param enable[in] Enable pktdone hw or not
 * @param set[in] Set the eint number (0:HAL_EINT_USB0, 1:HAL_EINT_USB1)
 *
 * @return int
 * @retval -ENODEV  No hid device found
 * @retval -EINVAL  The dir or set is invalid
 * @retval -ENOTSUP HW is not support pktdone eint
 *
 * After HID data is sent or received, the corresponding EINT will be triggered,
 * and the EINT state will change from 1 to 0.
 * The user must call air_usb_hid_pktdone_clear to clear the EINT and restore its state to 1.
 *
 * HAL_EINT_USB0 and HAL_EINT_USB1 are active high by default.
 *
 * The user must configure the corresponding EINT hardware to receive EINT signals.
 */
int air_usb_hid_config_pktdone_eint(const struct device *dev, uint8_t dir, bool enable, uint8_t set);

/**
 * @brief Clear PKTDONE EINT of HID device.
 *
 * @param dev[in] The hid device
 *
 * @return int
 * @retval -ENODEV     No hid device found
 * @retval -ENOTSUP    HW is not support pktdone eint
 * @retval -EINVAL     The pktdone hw of hid device is disabled
 */
int air_usb_hid_clear_pktdone_eint(const struct device *dev);

/**
 * @brief Get the status of PKTDONE EINT.
 *
 * @param dev[in] The hid device
 *
 * @return bool
 * @retval true  The pktdone eint is triggered
 * @retval false The pktdone eint is not triggered or device is not found
 */
bool air_usb_hid_get_pktdone_eint_status(const struct device *dev);

/**
 * @brief Move the get report handling from the ISR to the task level.
 *
 */
void get_report_work_handler(struct k_work *work_item);

#if !defined(CONFIG_MCUBOOT)
/**
 * @brief Move the set report handling from the ISR to the task level.
 *
 */
void set_report_work_handler(struct k_work *work_item);
#endif

#ifdef __cplusplus
}
#endif

#endif /* AIR_USB_HID_H */
