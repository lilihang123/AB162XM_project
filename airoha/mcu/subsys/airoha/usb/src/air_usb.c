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

#ifdef AIR_USB_ENABLE

#include <zephyr/drivers/usb/usb_dc.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <string.h>
#include <zephyr/sys/byteorder.h>

#include "air_usb.h"
#include "air_usb_internal.h"
#include "air_usb_hid.h"
#include "hal_usb_internal.h"

#include "memory_attribute.h"

#if defined(AIR_BTD_IC_PREMIUM_G1)
#include "errno.h"
#endif
/* Logging Config */
#if defined(CONFIG_LOG)
#include <zephyr/logging/log.h>
// #define LOG_LEVEL LOG_LEVEL_ERR
#define LOG_LEVEL CONFIG_USB_DRIVER_LOG_LEVEL
LOG_MODULE_REGISTER(air_usb);
#else
/* Temp logging method, backup for no log module environment. */
#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>
#define file_tag "air_usb_hid"
#ifdef CONFIG_USB_DRIVER_LOG_LEVEL
#define LOG_LEVEL CONFIG_USB_DRIVER_LOG_LEVEL
#else
#define LOG_LEVEL LOG_LEVEL_NONE
// #define LOG_LEVEL LOG_LEVEL_ERR
// #define LOG_LEVEL LOG_LEVEL_WRN
// #define LOG_LEVEL LOG_LEVEL_INF
// #define LOG_LEVEL LOG_LEVEL_DBG
#endif
#undef LOG_ERR
#undef LOG_WRN
#undef LOG_INF
#undef LOG_DBG
#define LOG_ERR(...)                                                                               \
	do {                                                                                       \
		if (LOG_LEVEL <= LOG_LEVEL_ERR) {                                                  \
			printk("<err> " file_tag ": %s: ", __func__);                              \
			printk(__VA_ARGS__);                                                       \
			printk("\r\n");                                                            \
		}                                                                                  \
	} while (0)
#define LOG_WRN(...)                                                                               \
	do {                                                                                       \
		if (LOG_LEVEL <= LOG_LEVEL_WRN) {                                                  \
			printk("<wrn> " file_tag ": %s: ", __func__);                              \
			printk(__VA_ARGS__);                                                       \
			printk("\r\n");                                                            \
		}                                                                                  \
	} while (0)
#define LOG_INF(...)                                                                               \
	do {                                                                                       \
		if (LOG_LEVEL <= LOG_LEVEL_INF) {                                                  \
			printk("<inf> " file_tag ": %s: ", __func__);                              \
			printk(__VA_ARGS__);                                                       \
			printk("\r\n");                                                            \
		}                                                                                  \
	} while (0)
#define LOG_DBG(...)                                                                               \
	do {                                                                                       \
		if (LOG_LEVEL <= LOG_LEVEL_DBG) {                                                  \
			printk("<dbg> " file_tag ": %s: ", __func__);                              \
			printk(__VA_ARGS__);                                                       \
			printk("\r\n");                                                            \
		}                                                                                  \
	} while (0)
#endif

/**************************************************************************************************
 * Macros
 *************************************************************************************************/
#define AIR_USB_USER_MAX       (CONFIG_AIR_USB_USER_NUM)
#define AIR_USB_DYN_USER_START (AIR_USB_FIX_USER_START + 0x543)
#define AIR_USB_FIX_USER_NUM   (AIR_USB_FIX_USER_END - AIR_USB_FIX_USER_START)
#define AIR_USB_DYN_USER_NUM   (AIR_USB_USER_MAX - AIR_USB_FIX_USER_NUM)

#define AIR_USB_EVT_HDLR_NUM    10
#define AIR_USB_STATUS_HDLR_NUM 10

#ifdef CONFIG_USB_DEVICE_STACK
#define UID_CODE_LENGTH 16
#endif

#if defined(AIR_BTD_IC_PREMIUM_G1)
/* Copy macros from zephyr/subsys/usb/device/class/hid/core.c */
#define HID_INT_IN_EP_IDX  0
#define HID_INT_OUT_EP_IDX 1
#endif
/**************************************************************************************************
 * Structures
 *************************************************************************************************/
typedef struct air_usb_user {
	uint32_t id;
	const char *name;
} air_usb_user_t;

typedef struct air_usb_evt_hdlr {
	uint32_t id;
	air_usb_evt_cb_t cb;
} air_usb_evt_hdlr_t;

typedef struct {
	const uint32_t fix_user_cnt;
	uint32_t dyn_user_cnt;
	uint32_t evt_hdlr_cnt;
	const air_usb_user_t fix_user[AIR_USB_FIX_USER_NUM];
	air_usb_user_t dyn_user[AIR_USB_DYN_USER_NUM];
	air_usb_evt_hdlr_t evt_hdlrs[AIR_USB_EVT_HDLR_NUM];
} air_usb_ctx_t;

/**************************************************************************************************
 * Extern Variables
 *************************************************************************************************/
#if !defined(CONFIG_MCUBOOT)
extern struct k_work g_usb_set_report_work;
#endif

/**************************************************************************************************
 * Varaiables
 *************************************************************************************************/
/**
 * @brief Global USB mode variable
 *
 * This variable tracks the current USB mode.
 * Default is set to Xinput mode.
 * This variable is used by usb_descriptor.c and other USB-related modules.
 */
air_usb_mode_t g_usb_mode = USB_MODE_HID;

 /* Linker-defined symbols bound the USB descriptor structs */
extern struct usb_desc_header __usb_descriptor_start[];
extern struct usb_desc_header __usb_descriptor_end[];

static air_usb_ctx_t air_usb_ctx = {.fix_user_cnt = AIR_USB_FIX_USER_NUM,
				    .dyn_user_cnt = 0,
				    .evt_hdlr_cnt = 0,
				    .fix_user = {{.id = AIR_USB_USBDBG_USER_ID, .name = "USBDBG"},
						 {.id = AIR_USB_USBHID_USER_ID, .name = "USBHID"},
						 {.id = AIR_USB_USBXINPUT_USER_ID, .name = "USBXINPUT"},
						 {.id = AIR_USB_USBAUD_USER_ID, .name = "USBAUD"},
						 {.id = AIR_USB_USBCDC_USER_ID, .name = "USBCDC"}}};

#if 0
_Static_assert((sizeof(air_usb_ctx.fix_user) / sizeof(air_usb_user_t)) ==
		       AIR_USB_FIX_USER_NUM,
	       "Fix users number mismatch 1");

_Static_assert(air_usb_ctx.fix_user_cnt == AIR_USB_FIX_USER_NUM,
	       "Fix users number mismatch 2");
#endif

/**************************************************************************************************
 * Helper Functions
 *************************************************************************************************/
 #ifdef CONFIG_USB_DEVICE_STACK
extern void uid_code_get(uint8_t *p_data);
#endif
static air_usb_ctx_t *air_usb_get_ctx(void)
{
	return &air_usb_ctx;
}

#if defined(AIR_BTD_IC_PREMIUM_G1)

ATTR_TEXT_IN_TCM int air_usb_ep_flush(uint32_t id, const struct device *dev, bool dir_in)
{
	uint8_t addr_idx = (dir_in ? HID_INT_IN_EP_IDX : HID_INT_OUT_EP_IDX);
	const struct usb_cfg_data *cfg;
	uint8_t ep_addr;
	int ret;

	if (air_usb_check_user_id(id) != 0) {
		return -EINVAL;
	}

	if (!dev) {
		LOG_INF("dev is NULL");
		return -ENOMEM;
	}
	cfg = dev->config;
	ep_addr = cfg->endpoint[addr_idx].ep_addr;

	ret = usb_dc_ep_flush(ep_addr);
	LOG_INF("ep[0x%x], flush:%d", ep_addr, ret);

	return ret;
}

int air_usb_interrupt_enable(const struct device *dev, air_usb_interrupt_evt_t event, bool dir_in, bool enable)
{
	hal_usb_status_t ret;

	if (event == AIR_USB_INTERRUPT_EP_TX) {
		uint8_t addr_idx = (dir_in ? HID_INT_IN_EP_IDX : HID_INT_OUT_EP_IDX);
		const struct usb_cfg_data *cfg;
		uint8_t ep_addr;
		uint8_t ep_num;

		if (!dev) {
			LOG_INF("dev is NULL");
			return -ENOMEM;
		}
		cfg = dev->config;
		ep_addr = cfg->endpoint[addr_idx].ep_addr;
		ep_num = USB_EP_GET_IDX(ep_addr);
		ret = hal_usb_enable_driver_intr(HAL_USB_DRV_HDLR_EP_TX, ep_num, enable);
		LOG_INF("ep[0x%x][%d], intr en[%d], ret[%d]", ep_addr, ep_num, enable, ret);
	} else if (event < AIR_USB_INTERRUPT_EVENT_MAX) {

		ret = hal_usb_enable_driver_intr(event, 0, enable);
		LOG_INF("intr en[%d], ret[%d]", enable, ret);
	} else {
		ret = -EINVAL;
		LOG_INF("usb not support interrupt event[%d]", event);
	}

	return ret;
}

uint32_t air_usb_get_sof_frame_number(void) {
	return hal_usb_get_sof_frame_number();
}

#endif

static inline const air_usb_user_t *air_usb_get_user(uint32_t id)
{
	air_usb_ctx_t *c = air_usb_get_ctx();
	const air_usb_user_t *user = NULL;
	if (AIR_USB_FIX_USER_START <= id && id < AIR_USB_FIX_USER_START + AIR_USB_FIX_USER_NUM) {
		user = &(c->fix_user[id - AIR_USB_FIX_USER_START]);
	} else if (AIR_USB_DYN_USER_START <= id && id < AIR_USB_DYN_USER_START + c->dyn_user_cnt) {
		user = &(c->dyn_user[id - AIR_USB_DYN_USER_START]);
	}
	return user;
}

static void air_usb_execute_cb(air_usb_evt_t evt, const uint8_t *para)
{
	air_usb_evt_hdlr_t *hdlr = NULL;
	air_usb_ctx_t *c = air_usb_get_ctx();

	for (uint32_t i = 0; i < AIR_USB_EVT_HDLR_NUM; i++) {
		hdlr = &(c->evt_hdlrs[i]);
		if (hdlr->id && hdlr->cb) {
#if 0
			/* TODO: some evt should not print log, e.g. SOF */
			LOG_DBG("user:%s(0x%08X), cb:%p",
				air_usb_get_user_name(hdlr->id), hdlr->id,
				hdlr->cb);
#endif
			hdlr->cb(evt, para);
		}
	}
}

#ifdef CONFIG_USB_DEVICE_STACK

int air_usb_hwinfo_get_device_id(uint8_t *buffer, size_t length)
{
	if (length < UID_CODE_LENGTH) {
		return -ENOMEM;
	}

	uid_code_get(buffer);

	return UID_CODE_LENGTH;
}

uint8_t *usb_update_sn_string_descriptor(void)
{
	/*
	 * The biggest device ID supported by the HWINFO driver is currently
	 * 128 bits, which is 16 bytes. Assume this is the maximum for now,
	 * unless the user requested a longer serial number.
	 */
	const int usblen = sizeof(CONFIG_USB_DEVICE_SN) / 2;
	uint8_t hwid[MAX(UID_CODE_LENGTH, sizeof(CONFIG_USB_DEVICE_SN) / 2)];
	static uint8_t sn[sizeof(CONFIG_USB_DEVICE_SN) + 1];
	const char hex[] = "0123456789ABCDEF";
	int hwlen, skip;

	memset(hwid, 0, sizeof(hwid));
	memset(sn, 0, sizeof(sn));

	hwlen = air_usb_hwinfo_get_device_id(hwid, sizeof(hwid));
	if (hwlen > 0) {
		skip = MAX(0, hwlen - usblen);

		for (int i = 0; i < usblen; i++) {
			sn[i * 2] = hex[hwid[i + skip] >> 4];
			sn[i * 2 + 1] = hex[hwid[i + skip] & 0xF];
		}
	}

	return sn;
}

#endif

int air_usb_hid_set_bcd_version(const struct device *dev, uint16_t usb_version)
{
	const struct usb_cfg_data *cfg;
	struct usb_hid_config *desc;

	if (!dev) {
		return -ENOMEM;
	}

	cfg = (struct usb_cfg_data*)(dev->config);
	desc = cfg->interface_descriptor;

	desc->if0_hid.bcdHID = sys_cpu_to_le16(usb_version);

	return 0;
}

int air_usb_hid_set_binterval(const struct device *dev, uint8_t ep_dir, uint8_t usb_endpoint_interval)
{
	const struct usb_cfg_data *cfg;
	struct usb_hid_config *desc;
	int res = 0;

	if (!dev) {
		return -ENOMEM;
	}

	cfg = (struct usb_cfg_data*)(dev->config);
	desc = cfg->interface_descriptor;

	switch (ep_dir) {
	case USB_EP_DIR_IN:
		desc->if0_int_in_ep.bInterval = usb_endpoint_interval;
		break;
#ifdef CONFIG_ENABLE_HID_INT_OUT_EP
	case USB_EP_DIR_OUT:
		desc->if0_int_out_ep.bInterval = usb_endpoint_interval;
		break;
#endif
	default:
		res = -ENOTSUP;
	}

	return res;
}

int air_usb_hid_set_mps(const struct device *dev, uint8_t ep_dir, uint16_t usb_endpoint_mps)
{
	const struct usb_cfg_data *cfg;
	struct usb_hid_config *desc;
	int res = 0;

	if (!dev) {
		return -ENOMEM;
	}

	cfg = (struct usb_cfg_data*)(dev->config);
	desc = cfg->interface_descriptor;

	switch (ep_dir) {
	case USB_EP_DIR_IN:
		desc->if0_int_in_ep.wMaxPacketSize = sys_cpu_to_le16(usb_endpoint_mps);
		break;
#ifdef CONFIG_ENABLE_HID_INT_OUT_EP
	case USB_EP_DIR_OUT:
		desc->if0_int_out_ep.wMaxPacketSize = sys_cpu_to_le16(usb_endpoint_mps);
		break;
#endif
	default:
		res = -ENOTSUP;
	}

	return res;
}

int air_usb_hid_set_iinterface(const struct device *dev, uint8_t usb_iinterface)
{
	const struct usb_cfg_data *cfg;
	struct usb_hid_config *desc;

	if (!dev) {
		return -ENOMEM;
	}

	cfg = (struct usb_cfg_data*)(dev->config);
	desc = cfg->interface_descriptor;
	desc->if0.iInterface = usb_iinterface;

	return 0;
}

/*
 * Switch descriptor start/end address according to air_usb_mode_get()
 * USB_MODE_HID   : primary
 * USB_MODE_XINPUT: secondary
 */
extern struct usb_desc_header __usb_sec_descriptor_start[];
extern struct usb_desc_header __usb_sec_descriptor_end[];

int find_usb_descriptor_head(struct usb_desc_header *head, uint8_t type, struct usb_desc_header **find_head)
{
	struct usb_desc_header *desc_end;
	if (!find_head) {
		return -ENOMEM;
	}

	if (air_usb_mode_get() == USB_MODE_HID) {
		desc_end = __usb_descriptor_end;
	} else {
		desc_end = __usb_sec_descriptor_end;
	}

next_desc:
	while ((head->bLength != 0U) && (head < desc_end)) {
		if (head->bDescriptorType == type) {
			*find_head = head;
			return 0;
		}

		/* Move to next descriptor */
		head = (struct usb_desc_header *)((uint8_t *)head + head->bLength);
	}

	if ((head + 1) != desc_end) {
		head = head + 1;
		LOG_INF("usb try to fix next descriptor at %p", head);
		goto next_desc;
	}

	return -ENODEV;
}

/*
 * Switch descriptor start address according to air_usb_mode_get()
 * USB_MODE_HID   : primary
 * USB_MODE_XINPUT: secondary
 */
int air_usb_set_descriptor_value(uint8_t type, uint16_t offset, uint32_t value)
{
	struct usb_desc_header *desc;
	struct usb_desc_header *desc_start;

	if (air_usb_mode_get() == USB_MODE_HID) {
		desc_start = __usb_descriptor_start;
	} else {
		desc_start = __usb_sec_descriptor_start;
	}

	if ((type != USB_DESC_DEVICE) && (type != USB_DESC_CONFIGURATION)) {
		return -ENOTSUP;
	}

	int res = find_usb_descriptor_head(desc_start, type, &desc);

	if ((res < 0) || (desc == NULL)) {
		LOG_INF("usb no header or res[%d]", res);
		return res;
	}

	switch (type) {
	case USB_DESC_DEVICE:
		switch (offset) {
		case AIR_USB_DESC_BCDUSB:
			((struct usb_device_descriptor *)desc)->bcdUSB = sys_cpu_to_le16((uint16_t)value);
			break;
		case AIR_USB_DESC_BDEVICECLASS:
			((struct usb_device_descriptor *)desc)->bDeviceClass = (uint8_t)value;
			break;
		case AIR_USB_DESC_BDEVICESUBCLASS:
			((struct usb_device_descriptor *)desc)->bDeviceSubClass = (uint8_t)value;
			break;
		case AIR_USB_DESC_BDEVICEPROTOCOL:
			((struct usb_device_descriptor *)desc)->bDeviceProtocol = (uint8_t)value;
			break;
		case AIR_USB_DESC_BMAXPACKETSIZE0:
			((struct usb_device_descriptor *)desc)->bMaxPacketSize0 = (uint8_t)value;
			break;
		case AIR_USB_DESC_IDVENDOR:
			((struct usb_device_descriptor *)desc)->idVendor = sys_cpu_to_le16((uint16_t)value);
			break;
		case AIR_USB_DESC_IDPRODUCT:
			((struct usb_device_descriptor *)desc)->idProduct = sys_cpu_to_le16((uint16_t)value);
			break;
		case AIR_USB_DESC_BCDDEVICE:
			((struct usb_device_descriptor *)desc)->bcdDevice = sys_cpu_to_le16((uint16_t)value);
			break;
		case AIR_USB_DESC_IMANUFACTURER:
			((struct usb_device_descriptor *)desc)->iManufacturer = (uint8_t)value;
			break;
		case AIR_USB_DESC_IPRODUCT:
			((struct usb_device_descriptor *)desc)->iProduct = (uint8_t)value;
			break;
		case AIR_USB_DESC_ISERIALNUMBER:
			((struct usb_device_descriptor *)desc)->iSerialNumber = (uint8_t)value;
			break;
		case AIR_USB_DESC_BNUMCONFIGURATIONS:
			((struct usb_device_descriptor *)desc)->bNumConfigurations = (uint8_t)value;
			break;
		default:
			LOG_INF("device descriptor error attribute[%d]", offset);
		}
		break;
	case USB_DESC_CONFIGURATION:
		switch (offset) {
		case AIR_USB_DESC_BNUMINTERFACES:
			((struct usb_cfg_descriptor *)desc)->bNumInterfaces = (uint8_t)value;
			break;
		case AIR_USB_DESC_BCONFIGURATIONVALUE:
			((struct usb_cfg_descriptor *)desc)->bConfigurationValue = (uint8_t)value;
			break;
		case AIR_USB_DESC_ICONFIGURATION:
			((struct usb_cfg_descriptor *)desc)->iConfiguration = (uint8_t)value;
			break;
		case AIR_USB_DESC_BMATTRIBUTES:
			((struct usb_cfg_descriptor *)desc)->bmAttributes = (uint8_t)value;
			break;
		case AIR_USB_DESC_BMAXPOWER:
			((struct usb_cfg_descriptor *)desc)->bMaxPower = (uint8_t)value;
			break;
		default:
			LOG_INF("configuration descriptor error attribute[%d]", offset);
		}
		break;
	default:
		LOG_INF("descriptor type error[%d]", type);
	}

	return res;
}

int air_usb_set_string_descriptor(uint8_t type, uint8_t *buffer, uint8_t size)
{
	struct usb_desc_header *desc;
	int res = find_usb_descriptor_head(__usb_descriptor_start, USB_DESC_STRING, &desc);
	uint8_t string_size;
	uint8_t *target_string;

	if ((res < 0) || (desc == NULL)) {
		LOG_INF("error usb no header or res[%d]", res);
		return res;
	}

	switch (type) {
	case AIR_USB_DESC_MANUFACTURER_IDX:
		string_size = (sizeof(CONFIG_USB_DEVICE_MANUFACTURER) - 1);
		desc = (struct usb_desc_header *)((uint8_t *)desc + desc->bLength);
		break;
	case AIR_USB_DESC_PRODUCT_IDX:
		string_size = (sizeof(CONFIG_USB_DEVICE_PRODUCT) - 1);
		desc = (struct usb_desc_header *)((uint8_t *)desc + desc->bLength);
		desc = (struct usb_desc_header *)((uint8_t *)desc + desc->bLength);
		break;
	default:
		LOG_INF("error usb string descriptor type error[%d]", type);
		return -EINVAL;
	}

	if (size > string_size) {
		res = -ENOMEM;
		LOG_INF("error usb string type[%d], string size[%d] over size[%d]", type, string_size, size);
	} else {
		target_string = ((uint8_t *)desc + sizeof(*desc));
		memcpy(target_string, buffer, size);
		LOG_INF("usb string type[%d]:0x%x", type, target_string[0]);
	}

	return res;
}


// #define USB_DBG_GPIO

#if defined (CONFIG_AIR_HID_CP_DEBUG_GPIO)
#ifndef USB_DBG_GPIO
#define USB_DBG_GPIO
#endif
#endif


#if defined(USB_DBG_GPIO)
#include "hal_gpio.h"
#define GPIO_SOF           HAL_GPIO_37
static void air_usb_dbg_io_init(void)
{
	hal_gpio_init(GPIO_SOF);
	hal_pinmux_set_function(GPIO_SOF, 0);
	hal_gpio_set_direction(GPIO_SOF, HAL_GPIO_DIRECTION_OUTPUT);
	hal_gpio_set_output(GPIO_SOF, HAL_GPIO_DATA_LOW);
}
#endif /* USB_DBG_GPIO */

/**************************************************************************************************
 * User System Internal Functions
 *************************************************************************************************/
int air_usb_check_user_id(uint32_t id)
{
	air_usb_ctx_t *c = air_usb_get_ctx();
	if (AIR_USB_FIX_USER_START <= id && id < AIR_USB_FIX_USER_START + AIR_USB_FIX_USER_NUM) {
		return 0;
	} else if (AIR_USB_DYN_USER_START <= id && id < AIR_USB_DYN_USER_START + c->dyn_user_cnt) {
		return 0;
	}
	return -ENOENT;
}

const char *air_usb_get_user_name(uint32_t id)
{
	const air_usb_user_t *user = air_usb_get_user(id);

	if (user) {
		return user->name;
	} else {
		return NULL;
	}
}

/**************************************************************************************************
 * USB_DC Callback Functions
 *************************************************************************************************/
void air_usb_dc_status_cb(enum usb_dc_status_code cb_status, const uint8_t *param)
{
	switch (cb_status) {
	case USB_DC_RESET:
		air_usb_execute_cb(AIR_USB_EVT_RESET, param);
		break;
	case USB_DC_CONNECTED:
		air_usb_execute_cb(AIR_USB_EVT_CONNECTED, param);
		break;
	case USB_DC_CONFIGURED:
		air_usb_execute_cb(AIR_USB_EVT_CONFIGURED, param);
		break;
	case USB_DC_DISCONNECTED:
		air_usb_execute_cb(AIR_USB_EVT_DISCONNECTED, param);
		break;
	case USB_DC_SUSPEND:
		air_usb_execute_cb(AIR_USB_EVT_SUSPEND, param);
		break;
	case USB_DC_RESUME:
		air_usb_execute_cb(AIR_USB_EVT_RESUME, param);
		break;
	case USB_DC_INTERFACE:
		air_usb_execute_cb(AIR_USB_EVT_INTERFACE, param);
		break;
	case USB_DC_SET_HALT:
		air_usb_execute_cb(AIR_USB_EVT_SET_HALT, param);
		break;
	case USB_DC_CLEAR_HALT:
		air_usb_execute_cb(AIR_USB_EVT_CLEAR_HALT, param);
		break;
	case USB_DC_SOF:
#if defined(USB_DBG_GPIO)
		hal_gpio_set_output(GPIO_SOF, HAL_GPIO_DATA_HIGH);
#endif
		air_usb_execute_cb(AIR_USB_EVT_SOF, param);
#if defined(USB_DBG_GPIO)
		hal_gpio_set_output(GPIO_SOF, HAL_GPIO_DATA_LOW);
#endif
		break;
	case USB_DC_ERROR:
		break;
	case USB_DC_UNKNOWN:
		break;
	default:
		break;
	}
}

static void air_usb_dc_pulg_in_cb(void)
{
	LOG_INF("air_usb_dc_pulg_in_cb");
	air_usb_execute_cb(AIR_USB_EVT_PLUG_IN, NULL);
}

static void air_usb_dc_pulg_out_cb(void)
{
	LOG_INF("air_usb_dc_pulg_out_cb");
	air_usb_execute_cb(AIR_USB_EVT_PLUG_OUT, NULL);
}

void air_usb_plugin_cb(void) {
	usb_plugin_cb();
}

void air_usb_plugout_cb(void) {
	usb_plugout_cb();
}

/**************************************************************************************************
 * Aioha USB Subsys Public Functions
 *************************************************************************************************/
int air_usb_create_user(const char *name, uint32_t *id)
{
	if (!name) {
		return -ENOMEM;
	}

	air_usb_ctx_t *c = air_usb_get_ctx();
	air_usb_user_t *user = NULL;

	if (c->dyn_user_cnt < AIR_USB_DYN_USER_NUM) {
		user = &(c->dyn_user[c->dyn_user_cnt]);
		user->id = AIR_USB_DYN_USER_START + c->dyn_user_cnt;
		user->name = name;
		c->dyn_user_cnt += 1;
		LOG_INF("USB Registered user name[0x%p] with id 0x%x", user->name, user->id);
		*id = user->id;
		return 0;
	} else {
		LOG_ERR("USB Failed to register user name[0x%p]", name);
		return -EINVAL;
	}
}

int air_usb_register_evt_cb(uint32_t id, air_usb_evt_cb_t cb)
{
	uint32_t idx = 0;
	air_usb_ctx_t *c = air_usb_get_ctx();

	if (cb == NULL) {
		return -EINVAL;
	}

	if (air_usb_check_user_id(id) != 0) {
		return -EINVAL;
	}

	for (idx = 0; idx < AIR_USB_EVT_HDLR_NUM; idx++) {
		if (c->evt_hdlrs[idx].id == id) {
			c->evt_hdlrs[idx].cb = cb;
			break;
		} else if (c->evt_hdlrs[idx].id == 0) {
			c->evt_hdlrs[idx].id = id;
			c->evt_hdlrs[idx].cb = cb;
			c->evt_hdlr_cnt++;
			break;
		}
	}

	if (idx == AIR_USB_EVT_HDLR_NUM) {
		return -ENOTSUP;
	}
	LOG_INF("air_usb_register_evt_cb, id=0x%08X, cb=%p, cb_idx=%d, cnt=%d",
		id, cb, idx, c->evt_hdlr_cnt);

	return 0;
}

bool air_usb_is_vbus_ready(void)
{
	return usb_dc_is_vbus_ready();
}

int air_usb_init_work_item(void)
{
#if !defined(CONFIG_MCUBOOT)
	k_work_init(&g_usb_set_report_work, set_report_work_handler);
#endif

	return 0;
}

int air_usb_init(void)
{
	usb_dc_register_plug_in_cb(air_usb_dc_pulg_in_cb);
	usb_dc_register_plug_out_cb(air_usb_dc_pulg_out_cb);
#if defined(USB_DBG_GPIO)
	air_usb_dbg_io_init();
#endif /* USB_DBG_GPIO */
	air_usb_init_work_item();
	return 0;
}

int air_usb_deinit(void)
{
	usb_dc_register_plug_in_cb(NULL);
	usb_dc_register_plug_out_cb(NULL);
	return 0;
}

int air_usb_enable(void)
{
	int ret = usb_enable(air_usb_dc_status_cb);
	if (ret) {
		LOG_ERR("air_usb_enable failed(%d)", ret);
	}
#if defined(USB_DBG_GPIO)
	air_usb_dbg_io_init();
#endif /* USB_DBG_GPIO */
	return ret;
}

int air_usb_disable(void)
{
	int ret = usb_disable();
	if (ret) {
		LOG_ERR("air_usb_enable failed(%d)", ret);
	}
	return ret;
}

int air_usb_wakeup_request(void)
{
	extern bool usb_get_remote_wakeup_status(void);

	bool config_en = IS_ENABLED(CONFIG_USB_DEVICE_REMOTE_WAKEUP);
	bool feature_en = usb_get_remote_wakeup_status();

	LOG_INF("air_usb_wakeup_request config:%d, feature:%d", config_en, feature_en);

	int ret = usb_wakeup_request();
	if (ret) {
		LOG_ERR("air_usb_wakeup_request failed(%d)", ret);
	}
	return ret;
}

/**************************************************************************************************
 * USB Mode Switch Functions
 *************************************************************************************************/
ATTR_TEXT_IN_TCM air_usb_mode_t air_usb_mode_get(void)
{
	return g_usb_mode;
}

int air_usb_mode_set(air_usb_mode_t mode)
{
	if (mode >= USB_MODE_MAX) {
		LOG_ERR("Invalid USB mode: %d", mode);
		return -EINVAL;
	}

	air_usb_mode_t old_mode = g_usb_mode;
	g_usb_mode = mode;

	LOG_INF("USB mode set: %d -> %d", old_mode, mode);

	return 0;
}


#endif /* AIR_USB_ENABLE */
