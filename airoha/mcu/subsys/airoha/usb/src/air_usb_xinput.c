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
#ifdef AIR_USB_XINPUT_ENABLE

#include "air_usb_xinput.h"
#include "air_usb.h"
#include "air_usb_internal.h"
#include <zephyr/usb/usb_device.h>
#include <zephyr/sys/byteorder.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <usb_descriptor.h>

/* Logging Config */
#include <zephyr/logging/log.h>
#define LOG_LEVEL CONFIG_USB_DRIVER_LOG_LEVEL
LOG_MODULE_REGISTER(air_usb_xinput);

/* Global context for Xinput device - Definition of the global variable declared in header file */
xinput_device_ctx_t g_xinput_ctx = {
	.dev = NULL,
	.tx_busy = false,
	.tx_user_id = 0,
	.rx_cb = NULL,
	.tx_done_cb = NULL,
	.rx_cb_user_id = 0,
	.tx_done_cb_user_id = 0,
	.suspended = false,
	.configured = false,
};

/**
 * @brief Device descriptor structure for Xinput mode
 */
struct dev_xinput_mode_descriptor {
	struct usb_device_descriptor device_descriptor;
	struct usb_cfg_descriptor cfg_descr;
	struct usb_if_descriptor if0;
	/** Vendor-specific Xinput descriptor (17 bytes) for device identification */
	const uint8_t xinput_desc[17];
	struct usb_ep_descriptor if0_intr_in_ep;
	struct usb_ep_descriptor if0_intr_out_ep;
} __packed;

/**
 * Xinput descriptor defined in primary section.
 * Using USBD_DEVICE_DESCR_DEFINE(primary) to place descriptor in primary section.
 * This allows selecting between primary or secondary based on air_usb_mode_get()
 * when switching USB modes.
 */
USBD_DEVICE_SEC_DESCR_DEFINE(primary)  /* Define descriptor in primary section */
struct dev_xinput_mode_descriptor xinput_mode_desc = {
	/* Device descriptor */
	.device_descriptor = {
		.bLength            = sizeof(struct usb_device_descriptor),
		.bDescriptorType    = USB_DESC_DEVICE,
		.bcdUSB             = sys_cpu_to_le16(USB_SRN_2_0),
		.bDeviceClass       = 0,
		.bDeviceSubClass    = 0,
		.bDeviceProtocol    = 0,
		.bMaxPacketSize0    = USB_MAX_CTRL_MPS,
		.idVendor           = sys_cpu_to_le16((uint16_t)CONFIG_USB_XINPUT_VID),
		.idProduct          = sys_cpu_to_le16((uint16_t)CONFIG_USB_XINPUT_PID),
		.bcdDevice          = sys_cpu_to_le16((uint16_t)CONFIG_USB_XINPUT_DEVICE_BCD), // change may cause IOT issue
		.iManufacturer      = 1,
		.iProduct           = 2,
		.iSerialNumber      = 3,
		.bNumConfigurations = 1, 
	},
	/* Configuration descriptor */
	.cfg_descr = {
		.bLength = sizeof(struct usb_cfg_descriptor),
		.bDescriptorType = USB_DESC_CONFIGURATION,
		.wTotalLength = 0,  /* Will be calculated in air_usb_xinput_device_register() */
		.bNumInterfaces = 1,
		.bConfigurationValue = 1,
		.iConfiguration = 0,
		/* Configuration attributes with remote wakeup if enabled */
		.bmAttributes = USB_SCD_RESERVED |
				COND_CODE_1(CONFIG_USB_DEVICE_REMOTE_WAKEUP, (USB_SCD_REMOTE_WAKEUP), (0)),
		.bMaxPower = CONFIG_USB_MAX_POWER,
	},
	/* Interface descriptor - Xinput uses Vendor Specific Class */
	.if0 = {
		.bLength = sizeof(struct usb_if_descriptor),
		.bDescriptorType    = USB_DESC_INTERFACE,
		.bInterfaceNumber   = 0,
		.bAlternateSetting  = 0,
		.bNumEndpoints      = 2,
		.bInterfaceClass    = XINPUT_VENDOR_CLASS,     /* 0xFF (Vendor Specific) */
		.bInterfaceSubClass = XINPUT_VENDOR_SUBCLASS,  /* 0x5D (Xinput) */
		.bInterfaceProtocol = XINPUT_VENDOR_PROTOCOL,  /* 0x01 (Gamepad) */
		.iInterface = 0,
	},
	/* Xinput specific descriptor (17 bytes)*/
	.xinput_desc = {
		0x11, /* bLength [17] */
		0x21, /* bDescriptorType (0x21 - XUSB Interface Descriptor) */
		0x10, /* bcdXUSB (LSB) XUSB protocol version, currently 1.10 */
		0x01, /* bcdXUSB (MSB) */
		0x01, /* bDeviceSubtype XINPUT_DEVSUBTYPE_GAMEPAD */
		0x25, /* wReports: Expansion Port Endpoint Address (LSB) 
				- D07..04: Endpoint Type
				- D3:D0: Number of reports supported by this endpoint. */
		XINPUT_IN_EP_ADDR, /* wReports: Expansion Port Endpoint Address (MSB)
				- D15..08: Controller Input Endpoint Address*/
		0x14, /* bReportSize: 20 bytes for Report ID 0x00 */
		0x03, /* bReportSize: Report size for Report ID 0x01. 0x00 is also valid: report size is variable but smaller than max. */
		0x03, /* bReportSize: Report size for Report ID 0x02. */
		0x03, /* bReportSize: Report size for Report ID 0x03. */
		0x04, /* bReportSize: Report size for Report ID 0x03. */
		0x13, /* wReports (LSB) */
		XINPUT_OUT_EP_ADDR, /* wReports: Expansion Port Endpoint Address (MSB) */
		0x08, /* bReportSize: Report size for Report ID 0x00. */
		0x03, /* bReportSize: Report size for Report ID 0x01. */
		0x03, /* bReportSize: Report size for Report ID 0x02. */
	},
	/* Endpoint IN descriptor - Used to send Xinput data to Host */
	.if0_intr_in_ep = {
		.bLength          = sizeof(struct usb_ep_descriptor),
		.bDescriptorType  = USB_DESC_ENDPOINT,
		.bEndpointAddress = XINPUT_IN_EP_ADDR,
		.bmAttributes     = USB_DC_EP_INTERRUPT,
		.wMaxPacketSize	  = sys_cpu_to_le16(XINPUT_EP_MPS),
		.bInterval 		  = CONFIG_USB_XINPUT_INT_IN_EP_INTERVAL,
	},
	/* Endpoint OUT descriptor - Used to receive control commands from Host */
	.if0_intr_out_ep = {
		.bLength          = sizeof(struct usb_ep_descriptor),
		.bDescriptorType  = USB_DESC_ENDPOINT,
		.bEndpointAddress = XINPUT_OUT_EP_ADDR,
		.bmAttributes     = USB_DC_EP_INTERRUPT,
		.wMaxPacketSize   = sys_cpu_to_le16(XINPUT_EP_MPS),
		.bInterval        = CONFIG_USB_XINPUT_INT_OUT_EP_INTERVAL,
	},
};

/* Xinput string descriptors defined in primary section */
struct usb_xinput_string_desription {
	struct usb_string_descriptor lang_descr;
	struct usb_mfr_descriptor {
		uint8_t bLength;
		uint8_t bDescriptorType;
		uint8_t bString[USB_BSTRING_LENGTH(CONFIG_USB_DEVICE_MANUFACTURER)];
	} __packed utf16le_mfr;
	struct usb_product_descriptor {
		uint8_t bLength;
		uint8_t bDescriptorType;
		uint8_t bString[USB_BSTRING_LENGTH(CONFIG_USB_XINPUT_DEVICE_PRODUCT)];
	} __packed utf16le_product;
	struct usb_sn_descriptor {
		uint8_t bLength;
		uint8_t bDescriptorType;
		uint8_t bString[USB_BSTRING_LENGTH(CONFIG_USB_DEVICE_SN)];
	} __packed utf16le_sn;
	struct usb_iface_descriptor {
		uint8_t bLength;
		uint8_t bDescriptorType;
		uint8_t bString[USB_BSTRING_LENGTH("Xinput Interface")];
	} __packed utf16le_iface;
} __packed;

/* Define string descriptors in primary section */
USBD_STRING_SEC_DESCR_DEFINE(primary) struct usb_xinput_string_desription xinput_string_descr = {
	.lang_descr = {
		.bLength = sizeof(struct usb_string_descriptor),
		.bDescriptorType = USB_DESC_STRING,
		.bString = sys_cpu_to_le16(0x0409),
	},
	.utf16le_mfr = {
		.bLength = USB_STRING_DESCRIPTOR_LENGTH(CONFIG_USB_DEVICE_MANUFACTURER),
		.bDescriptorType = USB_DESC_STRING,
		.bString = CONFIG_USB_DEVICE_MANUFACTURER,
	},
	.utf16le_product = {
		.bLength = USB_STRING_DESCRIPTOR_LENGTH(CONFIG_USB_XINPUT_DEVICE_PRODUCT),
		.bDescriptorType = USB_DESC_STRING,
		.bString = CONFIG_USB_XINPUT_DEVICE_PRODUCT,
	},
	.utf16le_sn = {
		.bLength = USB_STRING_DESCRIPTOR_LENGTH(CONFIG_USB_DEVICE_SN),
		.bDescriptorType = USB_DESC_STRING,
		.bString = CONFIG_USB_DEVICE_SN,
	},
	.utf16le_iface = {
		.bLength = USB_STRING_DESCRIPTOR_LENGTH("Xinput Interface"),
		.bDescriptorType = USB_DESC_STRING,
		.bString = "Xinput Interface",
	},
};

/* Terminator for primary descriptor section */
USBD_TERM_SEC_DESCR_DEFINE(primary) struct usb_desc_header xinput_term_descr = {
	.bLength = 0,
	.bDescriptorType = 0,
};

/* Extended Compatible ID Descriptor for Xinput */
const uint8_t xinput_ext_com_ID_dscr[] = {
	0x28, 0x00, 0x00, 0x00,             /* dwLength   : Descriptor length in bytes */
	0x00, 0x01,                         /* bcdVersion : Version 1.0 */
	0x04, 0x00,                         /* wIndex     : Extended Configuration Descriptor */
	0x01,                               /* bCount     : Total number of Function Sections that follow the Header Section */
	0x00, 0x00, 0x00, 0x00,             /* RESERVED   : Reserved */
	0x00, 0x00, 0x00,
	0x00,                               /* bFirstInterfaceNumber : Starting Interface Number for this function. */
	0x02,                               /* bNumInterfaces  : 0x01:  game controller without audio; 0x02: game controller with audio */
	0x58, 0x55, 0x53, 0x42,             /* compatibleID    : 'XUSB10' designates Xbox One compatible device. Pad to 8 bytes with 0x00. */
	0x31, 0x30, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,             /* subCompatibleID : Secondary compatible ID (none) */
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,             /* RESERVED   : Reserved */
	0x00, 0x00
};

/* Controller Input Report Capabilities Data */
const uint8_t xinput_controller_input_report_capabilities_data[] = {
	0x00, /* 0 - bReportID */
	0x14, /* 1 - bSize */
	0xFF, /* 2 - bmButtons (LSB) */
	0xF7, /* 3 - bmButtons (MSB) */
	0xFF, /* 4 - bLeftTrigger */
	0xFF, /* 5 - bRightTrigger */
	0xFC, 0xFF,  /* 6 - wLeftStickX */
	0xFC, 0xFF,  /* 8 - wLeftStickY */
	0xFC, 0xFF,  /* 10 - wRightStickX */
	0xFC, 0xFF,  /* 12 - wRightStickY */
	0x00, 0x00, 0x00, 0x00,   /* 14 - Reserved (4-bytes) */
	0x00, /* 18 - bmControllerCapabilities (LSB) */
	0x00, /* 19 - bmControllerCapabilities (MSB) */
};

/* Rumble Motor Control Capabilities Data */
const uint8_t xinput_rumble_motor_control_capabilities_data[] = {
	0x00, 0x08, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00
};

/* Device ID */
const uint8_t xinput_device_id[] = {
	0x28, 0x00, 0x00, 0x00
};

/* Extended Compatible Descriptor */
const uint8_t xinput_ext_com_dscr[] = {
	0x0A, 0x00, 0x00, 0x00,         /* dwLength   : Descriptor length in bytes */
	0x00, 0x01,                     /* bcdVersion : Version 1.0 */
	0x04, 0x00,                     /* wIndex     : extended properties OS descriptor */
	0x00, 0x00                      /* wCount     : The number of custom property sections that follow the header section */
};

/* MS OS String Descriptor */
static const uint8_t USB_XINPUT_MS_OS_STRING[18] = {
	0x12,       /* bLength: 18 bytes */
	0x03,       /* bDescriptorType: String */
	'M', 0x00,  /* 'M' */
	'S', 0x00,  /* 'S' */
	'F', 0x00,  /* 'F' */
	'T', 0x00,  /* 'T' */
	'1', 0x00,  /* '1' */
	'0', 0x00,  /* '0' */
	'0', 0x00,  /* '0' */
	0x90, 0x00  /* Vendor Code (0x90), Padding */
};

/**************************************************************************************************
 * Helper Functions
 *************************************************************************************************/
// #define USB_HID_DBG_GPIO

#if defined (CONFIG_AIR_HID_CP_DEBUG_GPIO)
#ifndef USB_HID_DBG_GPIO
#define USB_HID_DBG_GPIO
#endif
#endif


#if defined(USB_HID_DBG_GPIO)
#include "hal_gpio.h"
#define GPIO_TX               HAL_GPIO_35
#define GPIO_TXDONE           HAL_GPIO_36
static void air_usb_hid_dbg_io_init(void)
{
	hal_gpio_init(GPIO_TX);
	hal_pinmux_set_function(GPIO_TX, 0);
	hal_gpio_set_direction(GPIO_TX, HAL_GPIO_DIRECTION_OUTPUT);
	hal_gpio_set_output(GPIO_TX, HAL_GPIO_DATA_LOW);

	hal_gpio_init(GPIO_TXDONE);
	hal_pinmux_set_function(GPIO_TXDONE, 0);
	hal_gpio_set_direction(GPIO_TXDONE, HAL_GPIO_DIRECTION_OUTPUT);
	hal_gpio_set_output(GPIO_TXDONE, HAL_GPIO_DATA_LOW);
}
#endif /* USB_HID_DBG_GPIO */

/**************************************************************************************************
 * USB Status Callback Implementation
 *************************************************************************************************/
static void air_usb_xinput_evt_cb(air_usb_evt_t evt, const uint8_t *para)
{
	switch (evt) {
	case AIR_USB_EVT_PLUG_OUT:
	case AIR_USB_EVT_RESET: {
		/* Reset TX Status */
		LOG_INF("usb reset xinput tx status");
		/* Mark TX as not busy */
		g_xinput_ctx.tx_busy = false;
		break;
	}
	case AIR_USB_EVT_SUSPEND:
	case AIR_USB_EVT_RESUME:
		break;
	case AIR_USB_EVT_CONFIGURED:
	default:
		break;
	}
}

/**************************************************************************************************
 * Zephyr USB xinput Callback Implementation
 *************************************************************************************************/

/* Forward declarations for endpoint callbacks */
static void xinput_in_ep_callback(uint8_t ep, enum usb_dc_ep_cb_status_code cb_status);
static void xinput_out_ep_callback(uint8_t ep, enum usb_dc_ep_cb_status_code cb_status);
static void xinput_do_status_cb(struct usb_cfg_data *cfg, enum usb_dc_status_code status, const uint8_t *param);

/* Xinput endpoint configuration */
static struct usb_ep_cfg_data xinput_endpoints[] = {
	{
		.ep_addr = XINPUT_IN_EP_ADDR,
		.ep_cb  = xinput_in_ep_callback,
	},
	{
		.ep_addr = XINPUT_OUT_EP_ADDR,
		.ep_cb  = xinput_out_ep_callback,
	}
};

/**
 * @brief Interface configuration callback for Xinput
 *
 * @param head Pointer to the USB descriptor header
 * @param bInterfaceNumber Interface number being configured
 */
static void xinput_interface_config(struct usb_desc_header *head, uint8_t bInterfaceNumber)
{
	LOG_INF("xinput_interface_config called, bInterfaceNumber=%d", bInterfaceNumber);
}

/**
 * @brief Handler for vendor-specific USB requests
 *
 * Processes vendor-specific USB control requests for Xinput device,
 * including Extended Compatible ID, Controller Input Report Capabilities,
 * Rumble Motor Control Capabilities, and Device ID requests.
 *
 * @param setup Pointer to the USB setup packet
 * @param len Pointer to the length of the data
 * @param data Pointer to the data buffer
 *
 * @return 0 if successful, negative error code otherwise
 */
static int xinput_vendor_handler_req(struct usb_setup_packet *setup, int32_t *len, uint8_t **data)
{
	LOG_INF("xinput_vendor_handler_req: bmRequestType=0x%02x, bRequest=0x%02x, wValue=0x%04x, wIndex=0x%04x",
	        setup->bmRequestType, setup->bRequest, setup->wValue, setup->wIndex);

	/* Handle Device ID request (bmRequestType=0xC0, bRequest=0x01) */
	if ((setup->bmRequestType == 0xC0) && (setup->bRequest == 0x01)) {
		LOG_INF("xinput_vendor_handler_req Get Device ID request");
		*data = (uint8_t *)xinput_device_id;
		*len = sizeof(xinput_device_id);
		return 0;
	}

	/* Handle Extended Compatible ID Descriptor request (bmRequestType=0xC0, bRequest=0x90, wIndex=0x04) */
	if ((setup->bmRequestType == 0xC0) && (setup->bRequest == 0x90) && (setup->wIndex == 0x04)) {
		LOG_INF("xinput_vendor_handler_req Get Extended Compatible ID Descriptor request");
		*data = (uint8_t *)xinput_ext_com_ID_dscr;
		*len = sizeof(xinput_ext_com_ID_dscr);
		return 0;
	}

	/* Handle Extended Compatible Descriptor request (bmRequestType=0xC0, bRequest=0x90, wIndex=0x05) */
	if ((setup->bmRequestType == 0xC0) && (setup->bRequest == 0x90) && (setup->wIndex == 0x05)) {
		LOG_INF("xinput_vendor_handler_req Get Extended Compatible Descriptor request (wIndex=0x%04x)", setup->wIndex);
		*data = (uint8_t *)xinput_ext_com_dscr;
		*len = sizeof(xinput_ext_com_dscr);
		return 0;
	}

	/* Handle Controller Input Report Capabilities request (bmRequestType=0xC1, bRequest=0x01, wValue=0x0100) */
	if ((setup->bmRequestType == 0xC1) && (setup->bRequest == 0x01) && (setup->wValue == 0x0100)) {
		LOG_INF("xinput_vendor_handler_req Get Controller Input Report Capabilities request");
		*data = (uint8_t *)xinput_controller_input_report_capabilities_data;
		*len = sizeof(xinput_controller_input_report_capabilities_data);
		return 0;
	}

	/* Handle Rumble Motor Control Capabilities request (bmRequestType=0xC1, bRequest=0x01, wValue=0x0000) */
	if ((setup->bmRequestType == 0xC1) && (setup->bRequest == 0x01) && (setup->wValue == 0x0000)) {
		LOG_INF("xinput_vendor_handler_req Get Rumble Motor Control Capabilities request");
		*data = (uint8_t *)xinput_rumble_motor_control_capabilities_data;
		*len = sizeof(xinput_rumble_motor_control_capabilities_data);
		return 0;
	}

	/* Handle Extended Compatible ID Descriptor request (bmRequestType=0xC1, bRequest=0x90, wIndex=0x05) */
	if ((setup->bmRequestType == 0xC1) && (setup->bRequest == 0x90) && (setup->wIndex == 0x05)) {
		LOG_INF("xinput_vendor_handler_req Get Extended Compatible ID Descriptor request (wIndex=0x05)");
		*data = (uint8_t *)xinput_ext_com_ID_dscr;
		*len = sizeof(xinput_ext_com_ID_dscr);
		return 0;
	}

	LOG_INF("xinput_vendor_handler_req no match command");

	return -ENOTSUP;
}

/**
 * @brief Handler for class-specific USB requests
 *
 * @param setup Pointer to the USB setup packet
 * @param len Pointer to the length of the data
 * @param data Pointer to the data buffer
 *
 * @return 0 if successful, negative error code otherwise
 */
static int xinput_class_handle_req(struct usb_setup_packet *setup, int32_t *len, uint8_t **data)
{
	LOG_INF("xinput_class_handle_req: bmRequestType=0x%02x, bRequest=0x%02x",
	        setup->bmRequestType, setup->bRequest);
	return -ENOTSUP;
}

/**
 * @brief Handler for custom USB requests
 *
 * Processes custom USB control requests, specifically handling
 * Get Descriptor requests for Xinput descriptor.
 *
 * @param setup Pointer to the USB setup packet
 * @param len Pointer to the length of the data
 * @param data Pointer to the data buffer
 *
 * @return 0 if successful, negative error code otherwise
 */
static int xinput_custom_handle_req(struct usb_setup_packet *setup, int32_t *len, uint8_t **data)
{
	LOG_INF("xinput_custom_handle_req: bmRequestType=0x%02x, bRequest=0x%02x, wValue=0x%04x",
	        setup->bmRequestType, setup->bRequest, setup->wValue);
	
	/* Handle Get Descriptor request for Xinput descriptor */
	if ((setup->bmRequestType == 0x81) &&
	    (setup->bRequest == USB_SREQ_GET_DESCRIPTOR) &&
	    ((setup->wValue >> 8) == USB_DESC_XINPUT)) {
		LOG_INF("xinput_custom_handle_req Get Xinput Descriptor request");
		*data = (uint8_t *)&xinput_mode_desc.xinput_desc;
		*len = sizeof(xinput_mode_desc.xinput_desc);
		return 0;
	}
	
	/* Handle MS OS String Descriptor request (bmRequestType=0x80, bRequest=0x06, wValue=0x03EE) */
	if ((setup->bmRequestType == 0x80) &&
	    (setup->bRequest == USB_SREQ_GET_DESCRIPTOR) &&
	    (setup->wValue == 0x03EE)) {
		LOG_INF("xinput_custom_handle_req Get MS OS String Descriptor request (wValue=0x03EE)");
		*data = (uint8_t *)USB_XINPUT_MS_OS_STRING;
		*len = sizeof(USB_XINPUT_MS_OS_STRING);
		return 0;
	}
	
	return -ENOTSUP;
}

/* Register the callback function for usb_cfg_data in xinput mode */
USBD_DEFINE_SEC_CFG_DATA(xinput_cfg_data) = {
	.usb_device_description = NULL,
	.interface_config = xinput_interface_config,
	.interface_descriptor = &xinput_mode_desc.if0,
	.cb_usb_status = xinput_do_status_cb,
	.interface = {
		.vendor_handler = xinput_vendor_handler_req,
		.class_handler  = xinput_class_handle_req,
		.custom_handler = xinput_custom_handle_req,
	},
	.endpoint = xinput_endpoints,
	.num_endpoints = ARRAY_SIZE(xinput_endpoints),
};

/**
 * @brief Endpoint IN callback function
 *
 * Called when data transmission is complete. Updates the transmission
 * status and invokes the registered TX done callback if available.
 *
 * @param ep Endpoint address
 * @param cb_status Callback status code
 */
static void xinput_in_ep_callback(uint8_t ep, enum usb_dc_ep_cb_status_code cb_status)
{
#if defined(USB_HID_DBG_GPIO)
	hal_gpio_set_output(GPIO_TXDONE, HAL_GPIO_DATA_HIGH);
#endif
	//LOG_INF("xinput_in_ep_callback: ep=0x%02x, status=%d", ep, cb_status);
	
	if (cb_status != USB_DC_EP_DATA_IN) {
		LOG_INF("xinput_in_ep_callback cb_status != USB_DC_EP_DATA_IN");
		return;
	}
	
	/* Mark TX as not busy */
	g_xinput_ctx.tx_busy = false;
	
	/* Call TX done callback if registered */
	if (g_xinput_ctx.tx_done_cb) {
		//LOG_INF("xinput_in_ep_callback Calling TX done callback for user_id=0x%08x", g_xinput_ctx.tx_done_cb_user_id);
		g_xinput_ctx.tx_done_cb(g_xinput_ctx.dev);
	}
#if defined(USB_HID_DBG_GPIO)
	hal_gpio_set_output(GPIO_TXDONE, HAL_GPIO_DATA_LOW);
#endif
}

/**
 * @brief Endpoint OUT callback function
 *
 * Called when data is received from the host. Reads the received data
 * and invokes the registered RX callback if available.
 *
 * @param ep Endpoint address
 * @param cb_status Callback status code
 */
static void xinput_out_ep_callback(uint8_t ep, enum usb_dc_ep_cb_status_code cb_status)
{
	uint8_t rx_buf[XINPUT_EP_MPS];
	uint32_t bytes_read = 0;
	int ret;
	
	if (cb_status != USB_DC_EP_DATA_OUT) {
		LOG_INF("cb_status != USB_DC_EP_DATA_OUT");
		return;
	}

	/* Read data from endpoint */
	ret = usb_read(ep, rx_buf, sizeof(rx_buf), &bytes_read);
	if (ret != 0) {
		LOG_INF("xinput_out_ep_callback Failed to read from endpoint 0x%02x, ret=%d", ep, ret);
		return;
	}

	LOG_DBG("xinput_out_ep_callback Received %d bytes from endpoint 0x%02x", bytes_read, ep);
	/* Debug: Print first 8 bytes of received data buffer content */
	/*
	if (bytes_read > 0) {
		uint8_t print_len = (bytes_read < 8) ? bytes_read : 8;
		LOG_INF("rx_buf first %d bytes: %02x %02x %02x %02x %02x %02x %02x %02x",
		        print_len,
		        (print_len > 0) ? rx_buf[0] : 0x00,
		        (print_len > 1) ? rx_buf[1] : 0x00,
		        (print_len > 2) ? rx_buf[2] : 0x00,
		        (print_len > 3) ? rx_buf[3] : 0x00,
		        (print_len > 4) ? rx_buf[4] : 0x00,
		        (print_len > 5) ? rx_buf[5] : 0x00,
		        (print_len > 6) ? rx_buf[6] : 0x00,
		        (print_len > 7) ? rx_buf[7] : 0x00);
	}
	*/

	/* Call data received callback if registered */
	if (g_xinput_ctx.rx_cb && bytes_read > 0) {
		//LOG_INF("xinput_out_ep_callback Calling RX callback for user_id=0x%08x", g_xinput_ctx.rx_cb_user_id);
		g_xinput_ctx.rx_cb(g_xinput_ctx.dev, bytes_read, rx_buf);
	}
}

/**
 * @brief Register Xinput device
 *
 * Initializes the Xinput device context and calculates the total length
 * of the configuration descriptor.
 *
 * @param dev Pointer to the USB device
 *
 * @return 0 if successful
 */
int air_usb_xinput_device_register(const struct device *dev)
{
	/**
	 * Calculate wTotalLength for configuration descriptor
	 * wTotalLength = cfg_descr + if_descr + xinput_desc + 2 * ep_descr
	 */
	uint16_t total_len = sizeof(struct usb_cfg_descriptor) +
	                     sizeof(struct usb_if_descriptor) +
	                     sizeof(xinput_mode_desc.xinput_desc) +
	                     sizeof(struct usb_ep_descriptor) * 2;
	
	LOG_INF("Xinput descriptor wTotalLength calculation:");
	LOG_INF("  cfg_descr size: %d", sizeof(struct usb_cfg_descriptor));
	LOG_INF("  if_descr size: %d", sizeof(struct usb_if_descriptor));
	LOG_INF("  xinput_desc size: %d", sizeof(xinput_mode_desc.xinput_desc));
	LOG_INF("  ep_descr size: %d x 2", sizeof(struct usb_ep_descriptor));
	LOG_INF("  Total wTotalLength = %d", total_len);
	
	xinput_mode_desc.cfg_descr.wTotalLength = sys_cpu_to_le16(total_len);
	
	/* Initialize device context */
	g_xinput_ctx.dev = dev;
	g_xinput_ctx.tx_busy = false;
	air_usb_register_evt_cb(AIR_USB_USBXINPUT_USER_ID, air_usb_xinput_evt_cb);
#if defined(USB_HID_DBG_GPIO)
	air_usb_hid_dbg_io_init();
#endif /* USB_HID_DBG_GPIO */

	return 0;
}

/**
 * @brief Transmit data over Xinput IN endpoint
 *
 * Sends data to the host through the Xinput IN endpoint.
 * Validates parameters and checks if transmission is already in progress.
 *
 * @param user_id User identifier for the transmission
 * @param dev Pointer to the USB device
 * @param len Length of the data to transmit
 * @param data Pointer to the data buffer
 *
 * @return 0 if successful, negative error code otherwise
 */
int air_usb_xinput_tx(uint32_t user_id, const struct device *dev, uint16_t len, uint8_t *data)
{
	uint32_t bytes_written = 0;
	int ret;

	//LOG_INF("air_usb_xinput_tx called, user_id=0x%08x, len=%d", user_id, len);
#if defined(USB_HID_DBG_GPIO)
	hal_gpio_set_output(GPIO_TX, HAL_GPIO_DATA_HIGH);
#endif

	/*
	 * Validate parameters
	 * Note: The 'dev' parameter is not used in this function, so validation is skipped.
	 *       For APP usage: API format is consistent with HID interface.
	 */
	if (!data || len == 0 || len > XINPUT_EP_MPS) {
		LOG_INF("air_usb_xinput_tx Invalid parameters: dev=%p, data=%p, len=%d", dev, data, len);
#if defined(USB_HID_DBG_GPIO)
	hal_gpio_set_output(GPIO_TX, HAL_GPIO_DATA_LOW);
#endif
		return -EINVAL;
	}

	/* Check if TX is busy */
	if (g_xinput_ctx.tx_busy) {
		//LOG_INF("air_usb_xinput_tx TX is busy, cannot send data");
#if defined(USB_HID_DBG_GPIO)
	hal_gpio_set_output(GPIO_TX, HAL_GPIO_DATA_LOW);
#endif
		return -EBUSY;
	}

	/* Mark TX as busy */
	g_xinput_ctx.tx_busy = true;
	g_xinput_ctx.tx_user_id = user_id;

	if (g_xinput_ctx.configured && !g_xinput_ctx.suspended) {
		/* Write data to endpoint */
		ret = usb_write(XINPUT_IN_EP_ADDR, data, len, &bytes_written);
		if (ret != 0) {
			LOG_INF("air_usb_xinput_tx Failed to write to endpoint, ret=%d", ret);
			g_xinput_ctx.tx_busy = false;
#if defined(USB_HID_DBG_GPIO)
		hal_gpio_set_output(GPIO_TX, HAL_GPIO_DATA_LOW);
#endif
			return ret;
		}
	} else {
		LOG_INF("Xinput device is not configured");
		g_xinput_ctx.tx_busy = false;
		return -EAGAIN;
	}

#if defined(USB_HID_DBG_GPIO)
	hal_gpio_set_output(GPIO_TX, HAL_GPIO_DATA_LOW);
#endif

	return 0;
}

/**
 * @brief Register data received callback
 *
 * Registers a callback function to be invoked when data is received
 * from the host through the Xinput OUT endpoint.
 *
 * @param user_id User identifier for the callback
 * @param dev Pointer to the USB device
 * @param cb Callback function pointer
 *
 * @return 0 if successful, negative error code otherwise
 */
int air_usb_xinput_register_data_received_cb(uint32_t user_id, const struct device *dev,
                                               air_xinput_data_received_cb_t cb)
{
	LOG_INF("air_usb_xinput_register_data_received_cb called, user_id=0x%08x, cb=%p",
	        user_id, cb);
	
	/* Validate parameters */
	if (!dev) {
		LOG_ERR("air_usb_xinput_register_data_received_cb Invalid device pointer");
		return -EINVAL;
	}
	
	/* Register callback */
	g_xinput_ctx.rx_cb = cb;
	g_xinput_ctx.rx_cb_user_id = user_id;

	return 0;
}

/**
 * @brief Register transmission complete callback
 *
 * Registers a callback function to be invoked when data transmission
 * to the host through the Xinput IN endpoint is complete.
 *
 * @param user_id User identifier for the callback
 * @param dev Pointer to the USB device
 * @param cb Callback function pointer
 *
 * @return 0 if successful, negative error code otherwise
 */
int air_usb_xinput_register_tx_done_cb(uint32_t user_id, const struct device *dev,
                                         air_xinput_tx_done_cb_t cb)
{
	LOG_INF("air_usb_xinput_register_tx_done_cb called, user_id=0x%08x, cb=%p",
	        user_id, cb);
	
	/* Validate parameters */
	if (!dev) {
		LOG_INF("air_usb_xinput_register_tx_done_cb Invalid device pointer");
		return -EINVAL;
	}
	
	/* Register callback */
	g_xinput_ctx.tx_done_cb = cb;
	g_xinput_ctx.tx_done_cb_user_id = user_id;

	return 0;
}

static void xinput_do_status_cb(struct usb_cfg_data *cfg,
			  enum usb_dc_status_code status,
			  const uint8_t *param)
{
	switch (status) {
	case USB_DC_ERROR:
		LOG_INF("XINPUT Device error");
		break;
	case USB_DC_RESET: {
		LOG_INF("XINPUT Device reset detected");
		g_xinput_ctx.configured = false;
		g_xinput_ctx.suspended = false;
		usb_dc_ep_flush(XINPUT_IN_EP_ADDR);
	}
		break;
	case USB_DC_CONNECTED:
		LOG_INF("XINPUT Device connected");
		break;
	case USB_DC_CONFIGURED:
		LOG_INF("XINPUT Device configured");
		g_xinput_ctx.configured = true;
		break;
	case USB_DC_DISCONNECTED:
		LOG_INF("XINPUT Device disconnected");
		g_xinput_ctx.configured = false;
		g_xinput_ctx.suspended = false;
		break;
	case USB_DC_SUSPEND:
		LOG_INF("XINPUT Device suspended");
		g_xinput_ctx.suspended = true;
		break;
	case USB_DC_RESUME:
		LOG_INF("XINPUT Device resumed");
		if (g_xinput_ctx.suspended) {
			LOG_INF("XINPUT from suspend");
			g_xinput_ctx.suspended = false;
		} else {
			LOG_DBG("XINPUT Spurious resume event");
		}
		break;
	case USB_DC_SOF:
		break;
	case USB_DC_UNKNOWN:
	default:
		LOG_INF("XINPUT Unknown event");
		break;
	}

}

/* Define XINPUT device */
DEVICE_DEFINE(xinput,
             "XINPUT_DEV",
             &air_usb_xinput_device_register,
             NULL,
             &g_xinput_ctx,               /* device data */
             &xinput_cfg_data,            /* configuration data */
             POST_KERNEL,
             CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
             NULL);


#endif