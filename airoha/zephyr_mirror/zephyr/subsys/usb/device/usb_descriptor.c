/* usb_descriptor.c - USB common device descriptor definition */

/*
 * Copyright (c) 2017 PHYTEC Messtechnik GmbH
 * Copyright (c) 2017, 2018 Intel Corporation
 * Copyright (c) 2026 Airoha Technology Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Modifications:
2026-03-03 by Airoha - Add device qualifier descriptor and support Xinpit mode with HID device
*/

#include <string.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/usb/usb_device.h>
#include "usb_descriptor.h"
#include <zephyr/drivers/hwinfo.h>
#include <zephyr/sys/iterable_sections.h>
#include <zephyr/logging/log.h>
#include "air_usb_xinput.h"
LOG_MODULE_REGISTER(usb_descriptor, CONFIG_USB_DEVICE_LOG_LEVEL);

/*
 * The last index of the initializer_string without null character is:
 *   ascii_idx_max = bLength / 2 - 2
 * Use this macro to determine the last index of ASCII7 string.
 */
#define USB_BSTRING_ASCII_IDX_MAX(n)	(n / 2 - 2)

/*
 * The last index of the bString is:
 *   utf16le_idx_max = sizeof(initializer_string) * 2 - 2 - 1
 *   utf16le_idx_max = bLength - 2 - 1
 * Use this macro to determine the last index of UTF16LE string.
 */
#define USB_BSTRING_UTF16LE_IDX_MAX(n)	(n - 3)

/* Linker-defined symbols bound the USB descriptor structs
   Keep original start/end for HID, add secondary to support Xinput switching */
extern struct usb_desc_header __usb_descriptor_start[];
extern struct usb_desc_header __usb_descriptor_end[];
extern struct usb_desc_header __usb_sec_descriptor_start[];
extern struct usb_desc_header __usb_sec_descriptor_end[];

/* USB mode selection: 0=HID (primary), 1=Xinput (secondary)
   This variable is defined in air_usb.c, included via air_usb.h */
#include "air_usb.h"
#include "air_usb_xinput.h"

/* Structure representing the global USB description */
struct common_descriptor {
	struct usb_device_descriptor device_descriptor;
	struct usb_cfg_descriptor cfg_descr;
} __packed;

#define USB_DESC_MANUFACTURER_IDX			1
#define USB_DESC_PRODUCT_IDX				2
#define USB_DESC_SERIAL_NUMBER_IDX			3

/*
 * Device and configuration descriptor placed in the device section,
 * no additional descriptor may be placed there.
 */
USBD_DEVICE_DESCR_DEFINE(primary) struct common_descriptor common_desc = {
	/* Device descriptor */
	.device_descriptor = {
		.bLength = sizeof(struct usb_device_descriptor),
		.bDescriptorType = USB_DESC_DEVICE,
#ifdef CONFIG_USB_DEVICE_BOS
		.bcdUSB = sys_cpu_to_le16(USB_SRN_2_0_1),
#else
		.bcdUSB = sys_cpu_to_le16(USB_SRN_2_0),
#endif
#ifdef CONFIG_USB_COMPOSITE_DEVICE
		.bDeviceClass = USB_BCC_MISCELLANEOUS,
		.bDeviceSubClass = 0x02,
		.bDeviceProtocol = 0x01,
#else
		.bDeviceClass = 0,
		.bDeviceSubClass = 0,
		.bDeviceProtocol = 0,
#endif
		.bMaxPacketSize0 = USB_MAX_CTRL_MPS,
		.idVendor = sys_cpu_to_le16((uint16_t)CONFIG_USB_DEVICE_VID),
		.idProduct = sys_cpu_to_le16((uint16_t)CONFIG_USB_DEVICE_PID),
		.bcdDevice = sys_cpu_to_le16(USB_BCD_DRN),
		.iManufacturer = USB_DESC_MANUFACTURER_IDX,
		.iProduct = USB_DESC_PRODUCT_IDX,
		.iSerialNumber = USB_DESC_SERIAL_NUMBER_IDX,
		.bNumConfigurations = 1,
	},
	/* Configuration descriptor */
	.cfg_descr = {
		.bLength = sizeof(struct usb_cfg_descriptor),
		.bDescriptorType = USB_DESC_CONFIGURATION,
		/*wTotalLength will be fixed in usb_fix_descriptor() */
		.wTotalLength = 0,
		.bNumInterfaces = 0,
		.bConfigurationValue = 1,
		.iConfiguration = 0,
		.bmAttributes = USB_SCD_RESERVED |
				COND_CODE_1(CONFIG_USB_SELF_POWERED,
					    (USB_SCD_SELF_POWERED), (0)) |
				COND_CODE_1(CONFIG_USB_DEVICE_REMOTE_WAKEUP,
					    (USB_SCD_REMOTE_WAKEUP), (0)),
		.bMaxPower = CONFIG_USB_MAX_POWER,
	},
};

struct usb_string_desription {
	struct usb_string_descriptor lang_descr;
	struct usb_mfr_descriptor {
		uint8_t bLength;
		uint8_t bDescriptorType;
		uint8_t bString[USB_BSTRING_LENGTH(
				CONFIG_USB_DEVICE_MANUFACTURER)];
	} __packed utf16le_mfr;

	struct usb_product_descriptor {
		uint8_t bLength;
		uint8_t bDescriptorType;
		uint8_t bString[USB_BSTRING_LENGTH(CONFIG_USB_DEVICE_PRODUCT)];
	} __packed utf16le_product;

	struct usb_sn_descriptor {
		uint8_t bLength;
		uint8_t bDescriptorType;
		uint8_t bString[USB_BSTRING_LENGTH(CONFIG_USB_DEVICE_SN)];
	} __packed utf16le_sn;
} __packed;

/*
 * Language, Manufacturer, Product and Serial string descriptors,
 * placed in the string section.
 * FIXME: These should be sorted additionally.
 */
USBD_STRING_DESCR_DEFINE(primary) struct usb_string_desription string_descr = {
	.lang_descr = {
		.bLength = sizeof(struct usb_string_descriptor),
		.bDescriptorType = USB_DESC_STRING,
		.bString = sys_cpu_to_le16(0x0409),
	},
	/* Manufacturer String Descriptor */
	.utf16le_mfr = {
		.bLength = USB_STRING_DESCRIPTOR_LENGTH(
				CONFIG_USB_DEVICE_MANUFACTURER),
		.bDescriptorType = USB_DESC_STRING,
		.bString = CONFIG_USB_DEVICE_MANUFACTURER,
	},
	/* Product String Descriptor */
	.utf16le_product = {
		.bLength = USB_STRING_DESCRIPTOR_LENGTH(
				CONFIG_USB_DEVICE_PRODUCT),
		.bDescriptorType = USB_DESC_STRING,
		.bString = CONFIG_USB_DEVICE_PRODUCT,
	},
	/* Serial Number String Descriptor */
	.utf16le_sn = {
		.bLength = USB_STRING_DESCRIPTOR_LENGTH(CONFIG_USB_DEVICE_SN),
		.bDescriptorType = USB_DESC_STRING,
		.bString = CONFIG_USB_DEVICE_SN,
	},
};
USBD_DEVICE_QUAL_DESCR_DEFINE(primary) struct usb_device_qualifier_descriptor usb_device_qual_descr ={
		.bLength = sizeof(struct usb_device_qualifier_descriptor),
		.bDescriptorType = USB_DESC_DEVICE_QUALIFIER,
#ifdef CONFIG_USB_DEVICE_BOS
		.bcdUSB = sys_cpu_to_le16(USB_SRN_2_0_1),
#else
		.bcdUSB = sys_cpu_to_le16(USB_SRN_2_0),
#endif
#ifdef CONFIG_USB_COMPOSITE_DEVICE
		.bDeviceClass = USB_BCC_MISCELLANEOUS,
		.bDeviceSubClass = 0x02,
		.bDeviceProtocol = 0x01,
#else
		.bDeviceClass = 0,
		.bDeviceSubClass = 0,
		.bDeviceProtocol = 0,
#endif
		.bMaxPacketSize0 = USB_MAX_CTRL_MPS,
		.bNumConfigurations = 1,
		.bReserved = 0,
};


/* This element marks the end of the entire descriptor. */
USBD_TERM_DESCR_DEFINE(primary) struct usb_desc_header term_descr = {
	.bLength = 0,
	.bDescriptorType = 0,
};

/*
 * This function fixes bString by transforming the ASCII-7 string
 * into a UTF16-LE during runtime.
 */
static void ascii7_to_utf16le(void *descriptor)
{
	struct usb_string_descriptor *str_descr = descriptor;
	int idx_max = USB_BSTRING_UTF16LE_IDX_MAX(str_descr->bLength);
	int ascii_idx_max = USB_BSTRING_ASCII_IDX_MAX(str_descr->bLength);
	uint8_t *buf = (uint8_t *)&str_descr->bString;

	LOG_DBG("idx_max %d, ascii_idx_max %d, buf %p",
		idx_max, ascii_idx_max, (void *)buf);

	for (int i = idx_max; i >= 0; i -= 2) {
		LOG_DBG("char %c : %x, idx %d -> %d",
			buf[ascii_idx_max],
			buf[ascii_idx_max],
			ascii_idx_max, i);
		__ASSERT(buf[ascii_idx_max] > 0x1F && buf[ascii_idx_max] < 0x7F,
			 "Only printable ascii-7 characters are allowed in USB "
			 "string descriptors");
		buf[i] = 0U;
		buf[i - 1] = buf[ascii_idx_max--];
	}
}

/*
 * Look for the bString that has the address equal to the ptr and
 * return its index. Use it to determine the index of the bString and
 * assign it to the interfaces iInterface variable.
 */
/*
 * Switch descriptor start/end address according to air_usb_mode_get()
 * USB_MODE_HID   : primary
 * USB_MODE_XINPUT: secondary
 */
int usb_get_str_descriptor_idx(void *ptr)
{
	struct usb_desc_header *head;
	struct usb_desc_header *desc_end;
	struct usb_string_descriptor *str = ptr;
	int str_descr_idx = 0;

	if (air_usb_mode_get() == USB_MODE_HID) {
		head = __usb_descriptor_start;
		desc_end = __usb_descriptor_end;
	} else {
		head = __usb_sec_descriptor_start;
		desc_end = __usb_sec_descriptor_end;
	}

	while (head < desc_end && head->bLength != 0U) {
		switch (head->bDescriptorType) {
		case USB_DESC_STRING:
			if (head == (struct usb_desc_header *)str) {
				return str_descr_idx;
			}
			str_descr_idx += 1;
			break;
		default:
			break;
		}

		/* move to next descriptor */
		head = (struct usb_desc_header *)((uint8_t *)head + head->bLength);
	}

	return 0;
}

/*
 * Validate endpoint address and Update the endpoint descriptors at runtime,
 * the result depends on the capabilities of the driver and the number and
 * type of endpoints.
 * The default endpoint address is stored in endpoint descriptor and
 * usb_ep_cfg_data, so both variables bEndpointAddress and ep_addr need
 * to be updated.
 */
static int usb_validate_ep_cfg_data(struct usb_ep_descriptor * const ep_descr,
				    struct usb_cfg_data * const cfg_data,
				    uint32_t *requested_ep)
{
	for (unsigned int i = 0; i < cfg_data->num_endpoints; i++) {
		struct usb_ep_cfg_data *ep_data = cfg_data->endpoint;

		/*
		 * Trying to find the right entry in the usb_ep_cfg_data.
		 */
		if (ep_descr->bEndpointAddress != ep_data[i].ep_addr) {
			LOG_INF("ep_descr->bEndpointAddress != ep_data[i].ep_addr");
			continue;
		}

		/* Step 1: Try to use user-configured endpoint address first */
		struct usb_dc_ep_cfg_data ep_cfg;
		uint8_t user_ep_idx = USB_EP_GET_IDX(ep_descr->bEndpointAddress);
		bool is_in = (ep_descr->bEndpointAddress & USB_EP_DIR_IN) ? true : false;

		ep_cfg.ep_type = (ep_descr->bmAttributes & USB_EP_TRANSFER_TYPE_MASK);
		ep_cfg.ep_mps = ep_descr->wMaxPacketSize;
		ep_cfg.ep_addr = ep_descr->bEndpointAddress;

		LOG_INF("Validating EP: user_cfg=0x%02x, idx=%d, dir=%s",
			ep_descr->bEndpointAddress, user_ep_idx, is_in ? "IN" : "OUT");

		/* Check if user-configured endpoint is available */
		if (user_ep_idx > 0 && user_ep_idx < 16U) {
			bool ep_already_used = is_in ?
				(*requested_ep & (1U << (user_ep_idx + 16U))) :
				(*requested_ep & (1U << user_ep_idx));
			
			if (!ep_already_used && !usb_dc_ep_check_cap(&ep_cfg)) {
				LOG_INF("Using user-configured EP 0x%02x", ep_cfg.ep_addr);
				ep_data[i].ep_addr = ep_cfg.ep_addr;
				if (is_in) {
					*requested_ep |= (1U << (user_ep_idx + 16U));
				} else {
					*requested_ep |= (1U << user_ep_idx);
				}
				return 0;
			} else {
				LOG_INF("User-configured EP 0x%02x not available (used=%d), scanning for alternative",
					ep_cfg.ep_addr, ep_already_used);
			}
		}

		/* Step 2: Scan for available endpoint from 1 to 16 */
		/* For Xinput mode with HID composite: reserve EP 1-2 for Xinput */
		uint8_t start_idx = 1;
		#ifdef AIR_USB_XINPUT_ENABLE
		if (air_usb_mode_get() == USB_MODE_XINPUT) {
			start_idx = 3;  /* HID starts from EP 3 in Xinput mode */
			LOG_INF("Xinput mode: scanning HID endpoints from EP %d", start_idx);
		}
		#endif

		for (uint8_t idx = start_idx; idx < 16U; idx++) {
			ep_cfg.ep_addr = is_in ? (USB_EP_DIR_IN | idx) : idx;
			
			bool ep_used = is_in ?
				(*requested_ep & (1U << (idx + 16U))) :
				(*requested_ep & (1U << idx));
			
			if (ep_used) {
				LOG_INF("EP%d %s already used, skipping", idx, is_in ? "IN" : "OUT");
				continue;
			}

			if (!usb_dc_ep_check_cap(&ep_cfg)) {
				LOG_INF("Assigned alternative EP: 0x%02x -> 0x%02x",
					ep_descr->bEndpointAddress, ep_cfg.ep_addr);
				ep_descr->bEndpointAddress = ep_cfg.ep_addr;
				ep_data[i].ep_addr = ep_cfg.ep_addr;
				if (is_in) {
					*requested_ep |= (1U << (idx + 16U));
				} else {
					*requested_ep |= (1U << idx);
				}
				return 0;
			}
		}

		LOG_ERR("Failed to find available endpoint for 0x%02x", ep_descr->bEndpointAddress);
	}
	return -1;
}

/*
 * The interface descriptor of a USB function must be assigned to the
 * usb_cfg_data so that usb_ep_cfg_data and matching endpoint descriptor
 * can be found.
 */
static struct usb_cfg_data *usb_get_cfg_data(struct usb_if_descriptor *iface)
{
	//LOG_INF("usb_get_cfg_data g_usb_mode:%d", air_usb_mode_get());
	if (air_usb_mode_get() == USB_MODE_HID) {
		STRUCT_SECTION_FOREACH(usb_cfg_data, cfg_data) {
			if (cfg_data->interface_descriptor == iface) {
				return cfg_data;
			}
		}
	} else {
		STRUCT_SECTION_FOREACH(usb_sec_cfg_data, cfg_data) {
			if (cfg_data->interface_descriptor == iface) {
				return cfg_data;
			}
		}
	}

	return NULL;
}

/*
 * Default USB Serial Number string descriptor will be derived from
 * Hardware Information Driver (HWINFO). User can implement own variant
 * of this function. Please note that the length of the new Serial Number
 * descriptor may not exceed the length of the CONFIG_USB_DEVICE_SN. In
 * case the device ID returned by the HWINFO driver is bigger, the lower
 * part is used for the USB Serial Number, as that part is usually having
 * more entropy.
 */
__weak uint8_t *usb_update_sn_string_descriptor(void)
{
	/*
	 * The biggest device ID supported by the HWINFO driver is currently
	 * 128 bits, which is 16 bytes. Assume this is the maximum for now,
	 * unless the user requested a longer serial number.
	 */
	const int usblen = sizeof(CONFIG_USB_DEVICE_SN) / 2;
	uint8_t hwid[MAX(16, sizeof(CONFIG_USB_DEVICE_SN) / 2)];
	static uint8_t sn[sizeof(CONFIG_USB_DEVICE_SN) + 1];
	const char hex[] = "0123456789ABCDEF";
	int hwlen, skip;

	memset(hwid, 0, sizeof(hwid));
	memset(sn, 0, sizeof(sn));

	hwlen = hwinfo_get_device_id(hwid, sizeof(hwid));
	if (hwlen > 0) {
		skip = MAX(0, hwlen - usblen);
		LOG_HEXDUMP_DBG(&hwid[skip], usblen, "Serial Number");
		for (int i = 0; i < usblen; i++) {
			sn[i * 2] = hex[hwid[i + skip] >> 4];
			sn[i * 2 + 1] = hex[hwid[i + skip] & 0xF];
		}
	}

	return sn;
}

static void usb_fix_ascii_sn_string_descriptor(struct usb_sn_descriptor *sn)
{
	uint8_t *runtime_sn =  usb_update_sn_string_descriptor();
	int runtime_sn_len, default_sn_len;

	if (!runtime_sn) {
		return;
	}

	runtime_sn_len = strlen(runtime_sn);
	if (!runtime_sn_len) {
		return;
	}

	default_sn_len = strlen(CONFIG_USB_DEVICE_SN);

	if (runtime_sn_len != default_sn_len) {
		LOG_WRN("the new SN descriptor doesn't have the same "
			"length as CONFIG_USB_DEVICE_SN");
	}

	memcpy(sn->bString, runtime_sn, MIN(runtime_sn_len, default_sn_len));
}

static void usb_desc_update_mps0(struct usb_device_descriptor *const desc)
{
	struct usb_dc_ep_cfg_data ep_cfg = {
		.ep_addr = 0,
		.ep_mps = USB_MAX_CTRL_MPS,
		.ep_type = USB_DC_EP_CONTROL,
	};
	int ret;

	ret = usb_dc_ep_check_cap(&ep_cfg);
	if (ret) {
		/* Try the minimum bMaxPacketSize0 that must be supported. */
		ep_cfg.ep_mps = 8;
		ret = usb_dc_ep_check_cap(&ep_cfg);
		if (ret) {
			ep_cfg.ep_mps = 0;
		}

		__ASSERT(ret == 0, "Failed to find valid bMaxPacketSize0");
	}

	desc->bMaxPacketSize0 = ep_cfg.ep_mps;
	LOG_DBG("Set bMaxPacketSize0 %u", desc->bMaxPacketSize0);
}

/*
 * The entire descriptor, placed in the .usb.descriptor section,
 * needs to be fixed before use. Currently, only the length of the
 * entire device configuration (with all interfaces and endpoints)
 * and the string descriptors will be corrected.
 *
 * Restrictions:
 * - just one device configuration (there is only one)
 * - string descriptor must be present
 */
/*  Modify usb_fix_descriptor to support different descriptor end
    Determine whether to use primary or secondary end address based on air_usb_mode_get() */
static int usb_fix_descriptor(struct usb_desc_header *head)
{
	struct usb_cfg_descriptor *cfg_descr = NULL;
	struct usb_if_descriptor *if_descr = NULL;
	struct usb_cfg_data *cfg_data = NULL;
	struct usb_ep_descriptor *ep_descr = NULL;
	uint8_t numof_ifaces = 0U;
	uint8_t str_descr_idx = 0U;
	uint32_t requested_ep = BIT(16) | BIT(0);
	struct usb_desc_header *desc_end;

	// Select corresponding descriptor end based on air_usb_mode_get()
	if (air_usb_mode_get() == USB_MODE_HID) {
		desc_end = __usb_descriptor_end;
		LOG_INF("usb_fix_descriptor __usb_descriptor_end:0x%X", __usb_descriptor_end);
	} else {
		desc_end = __usb_sec_descriptor_end;
		LOG_INF("usb_fix_descriptor __usb_sec_descriptor_end:0x%X", __usb_sec_descriptor_end);
	}

	while (head->bLength != 0U) {
		switch (head->bDescriptorType) {
		case USB_DESC_DEVICE:
		case USB_DESC_DEVICE_QUALIFIER:
			LOG_INF("Device descriptor bLength=%u, bDescriptorType=%u", head->bLength, head->bDescriptorType);
			usb_desc_update_mps0((void *)head);
			break;
		case USB_DESC_CONFIGURATION:
			cfg_descr = (struct usb_cfg_descriptor *)head;
			LOG_INF("Configuration descriptor bLength=%u, bDescriptorType=%u", head->bLength, head->bDescriptorType);
			break;
		case USB_DESC_INTERFACE_ASSOC:
			LOG_INF("Association descriptor bLength=%u, bDescriptorType=%u", head->bLength, head->bDescriptorType);
			break;
		case USB_DESC_INTERFACE:
			if_descr = (struct usb_if_descriptor *)head;
			LOG_INF("Interface descriptor bLength=%u, bDescriptorType=%u", head->bLength, head->bDescriptorType);
			if (if_descr->bAlternateSetting) {
				LOG_INF("Skip alternate interface");
				break;
			}

			if (if_descr->bInterfaceNumber == 0U) {
				cfg_data = usb_get_cfg_data(if_descr);
				if (!cfg_data) {
					LOG_ERR("There is no usb_cfg_data "
						"for %p", head);
					return -1;
				}

				if (cfg_data->interface_config) {
					cfg_data->interface_config(head,
							numof_ifaces);
				}
			}

			numof_ifaces++;
			break;
		case USB_DESC_ENDPOINT:
			if (!cfg_data) {
				LOG_ERR("Uninitialized usb_cfg_data pointer, "
					"corrupted device descriptor?");
				return -1;
			}

			LOG_INF("Endpoint descriptor bLength=%u, bDescriptorType=%u", head->bLength, head->bDescriptorType);
			ep_descr = (struct usb_ep_descriptor *)head;
			if (usb_validate_ep_cfg_data(ep_descr,
						     cfg_data,
						     &requested_ep)) {
				LOG_ERR("Failed to validate endpoints");
				return -1;
			}

			break;
		case 0:
		case USB_DESC_STRING:
			/*
			 * Copy runtime SN string descriptor first, if has
			 */
			if (str_descr_idx == USB_DESC_SERIAL_NUMBER_IDX) {
				struct usb_sn_descriptor *sn =
					(struct usb_sn_descriptor *)head;
				usb_fix_ascii_sn_string_descriptor(sn);
			}
			/*
			 * Skip language descriptor but correct
			 * wTotalLength and bNumInterfaces once.
			 */
			if (str_descr_idx) {
				ascii7_to_utf16le(head);
			} else {
				if (!cfg_descr) {
					LOG_ERR("Incomplete device descriptor");
					return -1;
				}

				LOG_INF("Now the wTotalLength is %d",
					(uint8_t *)head - (uint8_t *)cfg_descr);
				sys_put_le16((uint8_t *)head - (uint8_t *)cfg_descr,
					     (uint8_t *)&cfg_descr->wTotalLength);
				cfg_descr->bNumInterfaces = numof_ifaces;
			}

			str_descr_idx += 1U;

			break;
		default:
			break;
		}

		/* Move to next descriptor */
		head = (struct usb_desc_header *)((uint8_t *)head + head->bLength);
	}

	if ((head + 1) != desc_end) {
		LOG_INF("try to fix next descriptor at %p, desc_end %p", head + 1, desc_end);
		return usb_fix_descriptor(head + 1);
	}

	return 0;
}

/* Return corresponding descriptor (HID or Xinput) based on air_usb_mode_get() */ 
uint8_t *usb_get_device_descriptor(void)
{
	static bool initialized_primary = false;
	static bool initialized_secondary = false;
	struct usb_desc_header *desc_start;
	struct usb_desc_header *desc_end;

	LOG_INF("__usb_descriptor_start 0x%X", __usb_descriptor_start);
	LOG_INF("__usb_descriptor_end 0x%X", __usb_descriptor_end);
	LOG_INF("__usb_sec_descriptor_start 0x%X", __usb_sec_descriptor_start);
	LOG_INF("__usb_sec_descriptor_end 0x%X", __usb_sec_descriptor_end);

	if (air_usb_mode_get() == USB_MODE_HID) {
		// HID mode (default)
		desc_start = __usb_descriptor_start;
		desc_end = __usb_descriptor_end;
		LOG_INF("Using HID descriptor (default mode)");
		if (!initialized_primary) {
			if (usb_fix_descriptor(desc_start)) {
				LOG_ERR("Failed to fixup USB descriptor (HID)");
				return NULL;
			}
			initialized_primary = true;
		}
	} else {
		// Xinput mode (secondary)
		desc_start = __usb_sec_descriptor_start;
		desc_end = __usb_sec_descriptor_end;
		LOG_INF("Using Xinput descriptor (secondary mode)");

		if (!initialized_secondary) {
			if (usb_fix_descriptor(desc_start)) {
				LOG_ERR("Failed to fixup USB descriptor (secondary)");
				return NULL;
			}
			initialized_secondary = true;
		}
	}

	return (uint8_t *) desc_start;
}

struct usb_dev_data *usb_get_dev_data_by_cfg(sys_slist_t *list,
					     struct usb_cfg_data *cfg)
{
	struct usb_dev_data *dev_data;

	SYS_SLIST_FOR_EACH_CONTAINER(list, dev_data, node) {
		const struct device *dev = dev_data->dev;
		const struct usb_cfg_data *cfg_cur = dev->config;

		if (cfg_cur == cfg) {
			return dev_data;
		}
	}

	LOG_INF("Device data not found for cfg %p", cfg);

	return NULL;
}

struct usb_dev_data *usb_get_dev_data_by_iface(sys_slist_t *list,
					       uint8_t iface_num)
{
	struct usb_dev_data *dev_data;

	SYS_SLIST_FOR_EACH_CONTAINER(list, dev_data, node) {
		const struct device *dev = dev_data->dev;
		const struct usb_cfg_data *cfg = dev->config;
		const struct usb_if_descriptor *if_desc =
						cfg->interface_descriptor;

		if (if_desc->bInterfaceNumber == iface_num) {
			return dev_data;
		}
	}

	LOG_INF("Device data not found for iface number %u", iface_num);

	return NULL;
}

struct usb_dev_data *usb_get_dev_data_by_ep(sys_slist_t *list, uint8_t ep)
{
	struct usb_dev_data *dev_data;

	SYS_SLIST_FOR_EACH_CONTAINER(list, dev_data, node) {
		const struct device *dev = dev_data->dev;
		const struct usb_cfg_data *cfg = dev->config;
		const struct usb_ep_cfg_data *ep_data = cfg->endpoint;

		for (uint8_t i = 0; i < cfg->num_endpoints; i++) {
			if (ep_data[i].ep_addr == ep) {
				return dev_data;
			}
		}
	}

	LOG_INF("Device data not found for ep %u", ep);

	return NULL;
}
