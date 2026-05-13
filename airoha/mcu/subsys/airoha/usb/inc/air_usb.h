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

#ifndef __AIROHA_USB_H__
#define __AIROHA_USB_H__

#include <inttypes.h>
#include <stdbool.h>
#include <zephyr/usb/usb_device.h>
#include "hal_usb.h"

enum {
	AIR_USB_FIX_USER_START = CONFIG_AIR_USB_USER_MAGIC_NUMBER,
	AIR_USB_USBDBG_USER_ID = AIR_USB_FIX_USER_START,
	AIR_USB_USBHID_USER_ID,
	AIR_USB_USBXINPUT_USER_ID,
	AIR_USB_USBAUD_USER_ID,
	AIR_USB_USBCDC_USER_ID,
	AIR_USB_FIX_USER_END,
};

#if defined(AIR_BTD_IC_PREMIUM_G1)
/** USB interrupt event */
typedef enum {
	AIR_USB_INTERRUPT_RESET = HAL_USB_DRV_HDLR_RESET,       /**< USB bus reset */
	AIR_USB_INTERRUPT_SUSPEND = HAL_USB_DRV_HDLR_SUSPEND,   /**< USB bus suspended */
	AIR_USB_INTERRUPT_RESUME = HAL_USB_DRV_HDLR_RESUME,     /**< USB bus resume */
	AIR_USB_INTERRUPT_SOF = HAL_USB_DRV_HDLR_SOF,           /**< USB bus sof */
	AIR_USB_INTERRUPT_EP0 = HAL_USB_DRV_HDLR_EP0,           /**< USB endpoint 0 */
	AIR_USB_INTERRUPT_EP_TX = HAL_USB_DRV_HDLR_EP_TX,       /**< USB endpoint n TX */
	AIR_USB_INTERRUPT_EP_RX = HAL_USB_DRV_HDLR_EP_RX,       /**< USB endpoint n RX */
	AIR_USB_INTERRUPT_EVENT_MAX,
} air_usb_interrupt_evt_t;

#endif
/** USB Standard Device Descriptor defined in spec. Table 9-8 */
enum {
	AIR_USB_DESC_BCDUSB,
	AIR_USB_DESC_BDEVICECLASS,
	AIR_USB_DESC_BDEVICESUBCLASS,
	AIR_USB_DESC_BDEVICEPROTOCOL,
	AIR_USB_DESC_BMAXPACKETSIZE0,
	AIR_USB_DESC_IDVENDOR,
	AIR_USB_DESC_IDPRODUCT,
	AIR_USB_DESC_BCDDEVICE,
	AIR_USB_DESC_IMANUFACTURER,
	AIR_USB_DESC_IPRODUCT,
	AIR_USB_DESC_ISERIALNUMBER,
	AIR_USB_DESC_BNUMCONFIGURATIONS,
};

/** USB Standard Configuration Descriptor defined in spec. Table 9-10 */
enum {
	AIR_USB_DESC_BNUMINTERFACES,
	AIR_USB_DESC_BCONFIGURATIONVALUE,
	AIR_USB_DESC_ICONFIGURATION,
	AIR_USB_DESC_BMATTRIBUTES,
	AIR_USB_DESC_BMAXPOWER,
};

/* USB String Descriptor defined in spec. Table 9-12 */
enum {
	AIR_USB_DESC_MANUFACTURER_IDX = 1,
	AIR_USB_DESC_PRODUCT_IDX,
};

/**
 * @brief Register a new user to use the USB stack
 *
 * @param[in] name The name of the user.
 * @param[out] id The ID of the user if success, 0 on fail.
 *
 * @return 0 on success, negative errno code on fail.
 */
int air_usb_create_user(const char *name, uint32_t *id);

typedef enum {
	AIR_USB_EVT_PLUG_IN,
	AIR_USB_EVT_PLUG_OUT,
	AIR_USB_EVT_CONFIGURED,
	AIR_USB_EVT_CONNECTED,    /* deprecated  */
	AIR_USB_EVT_DISCONNECTED, /* deprecated  */
	AIR_USB_EVT_RESET,
	AIR_USB_EVT_SUSPEND,
	AIR_USB_EVT_RESUME,
	AIR_USB_EVT_INTERFACE,
	AIR_USB_EVT_SET_HALT,
	AIR_USB_EVT_CLEAR_HALT,
	AIR_USB_EVT_SOF,
} air_usb_evt_t;

typedef void (*air_usb_evt_cb_t)(air_usb_evt_t evt, const uint8_t *para);

/**
 * @brief Register a callback function to handle the status change of the USB
 * stack.
 *
 * @param[in] id The ID of the user who want to register the callback function.
 * @param[in] cb The callback function.
 *
 * @return 0 on success, negative errno code on fail.
 *
 * Example:
 * ```
 * #include "airoha/mcu/subsys/airoha/usb/inc/air_usb.h"
 *
 * int main(void) {
 * 	uint32_t user_id = 0;
 * 	int status;
 *
 * 	status = air_usb_create_user("APP", &user_id);
 * 	if (status != 0) {
 * 		printf("Failed to create user APP\n");
 * 	}
 *
 * 	status = air_usb_register_evt_cb(user_id, my_evt_cb);
 * 	if (status != 0) {
 * 		printf("Failed to register callback\n");
 * 	}
 *
 * 	status = air_usb_init();
 * 	if (status != 0) {
 * 		printf("Failed to init usb\n");
 * 	}
 *
 * 	status = air_usb_enable();
 * 	if (status != 0) {
 * 		printf("Failed to enable usb\n");
 * 	}
 * }
 *
 * void my_evt_cb(air_usb_evt_t evt, const uint8_t *para) {
 * 	switch (evt) {
 * 	case AIR_USB_EVT_PLUG_IN:
 * 		printf("Device attached\n");
 * 		break;
 * 	case AIR_USB_EVT_PLUG_OUT:
 * 		printf("Device detached\n");
 * 		break;
 *      ...
 * }
 * ```
 */
int air_usb_register_evt_cb(uint32_t id, air_usb_evt_cb_t cb);

/**
 * @brief Gets the user name for the given user ID from the airoha USB subsys.
 *
 * This function retrieves the user name associated with the provided user ID
 * from the airoha USB subsys.
 *
 * @param[in] id The ID of the user for whom the name needs to be retrieved.
 *
 * @return A pointer to a constant character string containing the user name, or
 * NULL if the user ID is not found.
 */
const char *air_usb_get_user_name(uint32_t id);

/**
 * @brief Get the status of VBUS.
 *
 * @return bool the USB cable is plug in or not.
 * @retval true USB cable is plug in and the VBUS is ready.
 * @retval false USB cable is not plug in.
 */
bool air_usb_is_vbus_ready(void);

/**
 * @brief Initialize the USB work item.
 *
 * This function initializes the USB work item.
 * After initialization, the events set_report will be handled by system wq.
 *
 * @return int
 * @retval 0 on success
 * @retval other negative value on failure
 */
int air_usb_init_work_item(void);

/**
 * @brief Initialize the USB subsystem & vbus detection.
 *
 * This function initializes the USB subsystem and sets up VBUS detection.
 * After initialization, the events AIR_USB_EVT_PLUG_IN and AIR_USB_EVT_PLUG_OUT
 * will be generated when the USB cable is plugged in or out.
 *
 * @return int
 * @retval 0 on success
 * @retval other negative value on failure
 */
int air_usb_init(void);

/**
 * @brief De-initialize the USB subsystem and vbus detection.
 *
 * @return int
 * @retval 0 on success
 * @retval other negative value on failure
 */
int air_usb_deinit(void);

/**
 * @brief Enable USB device and pull up D+.
 *
 * @return int
 * @retval 0 on success
 * @retval -ENOTCONN if VBUS is not ready
 * @retval other negative value on failure
 */
int air_usb_enable(void);

/**
 * @brief Disable USB device and release D+.
 *
 * @return int
 * @retval 0 on success
 * @retval negative value on failure
 */
int air_usb_disable(void);

/**
 * @brief Start the USB remote wakeup procedure
 *
 * The USB device will send a remote wakeup signal to the host for a duration specified by
 * CONFIG_USB_AIROHA_REMOTE_WAKEUP_DRV_TIME_US microseconds.
 * During this time, the API will block until the remote wakeup signal is completed.
 *
 * @return int 0 on success, negative errno code on fail.
 * @retval 0 success
 * @retval -ENOTSUP The CONFIG_USB_DEVICE_REMOTE_WAKEUP is not enabled.
 * @retval -EACCES The USB device is not receive SetFeature(RemoteWakeup).
 */
int air_usb_wakeup_request(void);

/**
 * @brief Set USB Device/Configuration Descriptor attribute value
 *
 * @details Should be called before usb_hid_init().
 *
 * @param[in]  type         Descriptor type (e.g. USB_DESC_DEVICE, USB_DESC_CONFIGURATION)
 * @param[in]  offset       Offset of the descriptor attribute to be set (e.g. AIR_USB_DESC_BCDUSB, AIR_USB_DESC_BNUMINTERFACES, ...)
 * @param[in]  value        Value to be set for the descriptor attribute
 *
 * @return 0 on success, negative errno code on fail.
 */
int air_usb_set_descriptor_value(uint8_t type, uint16_t offset, uint32_t value);

/**
 * @brief Set USB MANUFACTURER/PRODUCT String
 *
 * @details Should be called before usb_hid_init().
 *
 * @param[in]  type         String descriptor type (e.g. AIR_USB_DESC_MANUFACTURER_IDX, AIR_USB_DESC_PRODUCT_IDX)
 * @param[in]  buffer       Pointer to the input string buffer provided by the caller.
 * @param[in]  size         Length of the string descriptor to set (in bytes).
 *
 * @return 0 on success, negative errno code on fail.
 */
int air_usb_set_string_descriptor(uint8_t type, uint8_t *buffer, uint8_t size);

/**
 * @brief Set USB HID class BCD HID Code
 *
 * @details Should be called before usb_hid_init().
 *
 * @param[in]  dev               Pointer to USB HID device
 * @param[in]  usb_version       To be used for bcdHID
 *
 * @return 0 on success, negative errno code on fail.
 */
int air_usb_hid_set_bcd_version(const struct device *dev, uint16_t usb_version);

/**
 * @brief Set USB HID class interval Code
 *
 * @details Should be called before usb_hid_init().
 *
 * @param[in]  dev                         Pointer to USB HID device
 * @param[in]  usb_endpoint_interval       To be used for bInterval
 *
 * @return 0 on success, negative errno code on fail.
 */
int air_usb_hid_set_binterval(const struct device *dev, uint8_t ep_dir, uint8_t usb_endpoint_interval);

/**
 * @brief Set USB HID class iInterface Code
 *
 * @details Should be called before usb_hid_init().
 *
 * @param[in]  dev              Pointer to USB HID device
 * @param[in]  usb_iinterface   To be used for iInterface
 *
 * @return 0 on success, negative errno code on fail.
 */
int air_usb_hid_set_iinterface(const struct device *dev, uint8_t usb_iinterface);

/**
 * @brief Set USB HID class Max Packet Size Code
 *
 * @details Should be called before usb_hid_init().
 *
 * @param[in]  dev                Pointer to USB HID device
 * @param[in]  ep_dir             Endpoint direction(e.g. USB_EP_DIR_IN, USB_EP_DIR_OUT)
 * @param[in]  usb_endpoint_mps   To be used for wMaxPacketSize
 *
 * @return 0 on success, negative errno code on fail.
 */
int air_usb_hid_set_mps(const struct device *dev, uint8_t ep_dir, uint16_t usb_endpoint_mps);

/**
 * @brief update plugin flag
 *
 * @return void
 */
void air_usb_plugin_cb(void);

/**
 * @brief update plugout flag
 *
 * @return void
 */
void air_usb_plugout_cb(void);

/**
 * @brief Get USB SOF frame number.
 *
 * @return uint32_t frame number.
 */
uint32_t air_usb_get_sof_frame_number(void);

/**
 * @brief USB mode enumeration for HID and Xinput mode switching
 *
 * The USB mode allows the device to operate in different USB classes.
 * This enum is designed to be extensible for future USB modes.
 */
typedef enum {
	USB_MODE_HID = 0,    /**< HID mode (Standard USB HID Class) */
	USB_MODE_XINPUT = 1, /**< Xinput mode (Vendor Specific Class 0xFF5D) */
	USB_MODE_MAX         /**< Maximum USB mode value (for validation) */
} air_usb_mode_t;

/**
 * @brief Global USB mode variable
 *
 * This variable tracks the current USB mode.
 *
 * @note This variable is defined in air_usb.c and used by usb_descriptor.c and other USB modules
 */
extern air_usb_mode_t g_usb_mode;

/**
 * @brief Get current USB mode
 *
 * @return Current USB mode (air_usb_mode_t)
 *
 * Example usage:
 * @code
 * air_usb_mode_t mode = air_usb_mode_get();
 * if (mode == USB_MODE_HID) {
 *     printk("Current mode: HID\n");
 * } else if (mode == USB_MODE_XINPUT) {
 *     printk("Current mode: Xinput\n");
 * }
 * @endcode
 */
air_usb_mode_t air_usb_mode_get(void);

/**
 * @brief Set USB mode
 *
 * This function sets the USB mode without performing the switch.
 * The actual switch will occur on the next USB enable.
 *
 * @param mode USB mode to set (air_usb_mode_t)
 * @return 0 on success, -EINVAL if mode is invalid
 *
 * @note This function only sets the mode variable, it does not trigger USB re-enumeration
 *
 * Example usage:
 * @code
 * // Set mode to Xinput before USB initialization
 * int ret = air_usb_mode_set(USB_MODE_XINPUT);
 * if (ret == 0) {
 *     usb_enable(NULL);
 * }
 * @endcode
 */
int air_usb_mode_set(air_usb_mode_t mode);

#if defined(AIR_BTD_IC_PREMIUM_G1)
/**
 * @brief USB EP interrupt enable
 *
 * @param[in]  dev       Pointer to USB device
 * @param[in]  event     interrupt event
 * @param[in]  dir_in    true for IN, false for OUT
 * @param[in]  enable    enable releated interrupt or not
 *
 * @return 0 on success, -ENOMEM if mode is invalid
 */
int air_usb_interrupt_enable(const struct device *dev, air_usb_interrupt_evt_t event, bool dir_in, bool enable);

/**
 * @brief USB EP FIFO flush
 *
 * @param[in]  id        The ID of the user
 * @param[in]  dev       Pointer to USB device
 * @param[in]  dir_in    true for IN, false for OUT
 *
 * @return 0 on success, -ENOMEM if dev is invalid, -EINVAL if mode is invalid
 */
int air_usb_ep_flush(uint32_t id, const struct device *dev, bool dir_in);
#endif

#endif /* __AIROHA_USB_H__ */
