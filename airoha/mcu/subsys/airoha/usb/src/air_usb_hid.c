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

#ifdef AIR_USB_HID_ENABLE

#include "air_usb.h"
#include "air_usb_hid_desc.h"
#include "air_usb_hid.h"
#include "air_usb_internal.h"
#include "hal_usb_internal.h"
#include "memory_attribute.h"

#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/class/usb_hid.h>
#include <string.h>
#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <usb_descriptor.h>

/* Logging Config */
#if defined(CONFIG_LOG)
#include <zephyr/logging/log.h>
// #define LOG_LEVEL LOG_LEVEL_ERR
#define LOG_LEVEL CONFIG_USB_DRIVER_LOG_LEVEL
LOG_MODULE_REGISTER(air_usb_hid);
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

/* Copy macros from zephyr/subsys/usb/device/class/hid/core.c */
#define HID_INT_IN_EP_IDX  0
#define HID_INT_OUT_EP_IDX 1

#if defined(CONFIG_USBD_HID_INSTANCE_COUNT)
#define AIR_USB_HID_NUM CONFIG_USBD_HID_INSTANCE_COUNT
#elif defined(CONFIG_USB_HID_DEVICE_COUNT)
#define AIR_USB_HID_NUM CONFIG_USB_HID_DEVICE_COUNT
#else
#error "no hid device count assigned"
#endif

#define CONFIG_AIR_USB_HID_GET_REPORT_CB_NUM CONFIG_AIR_USB_HID_CB_NUM
#define CONFIG_AIR_USB_HID_SET_REPORT_CB_NUM CONFIG_AIR_USB_HID_CB_NUM
#define CONFIG_AIR_USB_HID_OUTPUT_CB_NUM     CONFIG_AIR_USB_HID_CB_NUM
#define CONFIG_AIR_USB_TX_DONE_CB_NUM        CONFIG_AIR_USB_HID_CB_NUM
#define CONFIG_AIR_USB_TX_FREE_CB_NUM        CONFIG_AIR_USB_HID_CB_NUM
#define CONFIG_AIR_USB_HID_PROTOCOL_CB_NUM   CONFIG_AIR_USB_HID_CB_NUM

#define GET_REPORT_CB_NUM CONFIG_AIR_USB_HID_GET_REPORT_CB_NUM
#define SET_REPORT_CB_NUM CONFIG_AIR_USB_HID_SET_REPORT_CB_NUM
#define OUTPUT_CB_NUM     CONFIG_AIR_USB_HID_OUTPUT_CB_NUM
#define TX_DONE_CB_NUM    CONFIG_AIR_USB_TX_DONE_CB_NUM
#define TX_FREE_CB_NUM    CONFIG_AIR_USB_TX_FREE_CB_NUM
#define PROTOCOL_CB_NUM   CONFIG_AIR_USB_HID_PROTOCOL_CB_NUM

#define AIR_USB_HID_REPOTR_MAX_LEN 1024
#define REPORT_WORK_QUEUE_SIZE 37
/**************************************************************************************************
 * Internal Struct
 *************************************************************************************************/
typedef struct air_usb_tranfer_chk {
	bool done;
	uint8_t user_id;
	uint8_t rid;
	uint8_t rlen;
} air_usb_tranfer_chk_t;

typedef struct air_usb_hid_str {
	struct device *dev;
	air_usb_hid_report_desc_t *descs;
	uint8_t descn;
	uint8_t *report_desc;
	uint16_t report_desc_len;
	uint8_t pktdone_enable;
	uint8_t pktdone_dir;
	uint8_t pktdone_set;
	air_usb_tranfer_chk_t tx_trans;
	bool in_no_report_id;
	bool out_no_report_id;
	bool feature_in_no_report_id;
	bool feature_out_no_report_id;
} air_usb_hid_str_t;

typedef struct {
	uint32_t user_id;
	const struct device *dev;
	uint8_t type;
	uint8_t id;
	uint16_t len;
	bool registered;
	void *cb;
} cb_hdlr_t;

#if defined(AIR_BTD_IC_MANDATORY_G1)
#define ATTR_ZIDATA_IN_TCM_NONE_RETENTION
#endif

#if IS_ENABLED(CONFIG_AIR_USB_HID_PKTDONE_EINT)
#define USB_HID_PKTDONE_SET_NUM 2

typedef struct {
	struct device *dev;
	uint8_t ep_idx;
	uint8_t ep_dir; /* 1:IN, 0:OUT */
	uint8_t enable; /* 1:enable, 0:disable */
} air_usb_hid_pktdone_ctx_t;

static air_usb_hid_pktdone_ctx_t air_usb_hid_pktdone_ctx[USB_HID_PKTDONE_SET_NUM];
#endif

/**
 * @brief This Struct is copy from zephyr/subsys/usb/device/class/hid/core.c
 * This struct is used to cast dev->data and get detail of hid device.
 */
struct hid_device_info {
	const uint8_t *report_desc;
	size_t report_size;
	const struct hid_ops *ops;
#ifdef CONFIG_USB_DEVICE_SOF
	uint32_t sof_cnt[CONFIG_USB_HID_REPORTS];
	bool idle_on;
	uint8_t idle_rate[CONFIG_USB_HID_REPORTS];
#endif
#ifdef CONFIG_USB_HID_BOOT_PROTOCOL
	uint8_t protocol;
#endif
	bool configured;
	bool suspended;
	struct usb_dev_data common;
};

/**************************************************************************************************
 * Variables
 *************************************************************************************************/
static air_usb_hid_str_t air_usb_hids[AIR_USB_HID_NUM];
static uint8_t air_usb_hid_cnt = 0;

static cb_hdlr_t get_report_hdlrs[GET_REPORT_CB_NUM];
static cb_hdlr_t set_report_hdlrs[SET_REPORT_CB_NUM];
static cb_hdlr_t output_hdlrs[OUTPUT_CB_NUM];
static cb_hdlr_t tx_done_hdlrs[TX_DONE_CB_NUM];
static cb_hdlr_t tx_free_hdlrs[TX_FREE_CB_NUM];
static cb_hdlr_t protocol_hdlrs[PROTOCOL_CB_NUM];
#if !defined(CONFIG_MCUBOOT)
static uint8_t g_usb_report_write_index = 0;
static uint8_t g_usb_report_read_index = 0;
ATTR_ZIDATA_IN_TCM_NONE_RETENTION struct set_report_work_data g_usb_report_work_queue[REPORT_WORK_QUEUE_SIZE];
struct k_work g_usb_set_report_work;
#endif

/**
 * NOTE:
 * Get/Set Report buffer is not need to keep in mcu sleep stage.
 * Put it to ATTR_ZIDATA_IN_TCM_NONE_RETENTION section to resuce sram cost.
 */
ATTR_ZIDATA_IN_TCM_NONE_RETENTION static uint8_t air_usb_get_report_buf[AIR_USB_HID_REPOTR_MAX_LEN];
ATTR_ZIDATA_IN_TCM_NONE_RETENTION static uint8_t air_usb_out_report_buf[AIR_USB_HID_REPOTR_MAX_LEN];

/**************************************************************************************************
 * Function Declarations
 *************************************************************************************************/
static void air_usb_hid_evt_cb(air_usb_evt_t evt, const uint8_t *para);

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

#if !defined(CONFIG_MCUBOOT)
static uint32_t get_queue_remain_data(uint32_t write, uint32_t read)
{
    return (write >= read) ? (write - read) : (write + (REPORT_WORK_QUEUE_SIZE - read));
}
#endif
/**************************************************************************************************
 * Public Functions
 *************************************************************************************************/
#if !defined(CONFIG_MCUBOOT)
void set_report_work_handler(struct k_work *work_item)
{
	const struct device *dev;
	air_hid_set_report_cb_t cb;
	uint8_t type;
	uint8_t id;
	uint16_t len;
	uint8_t *data;
	uint8_t l_usb_report_read_index;
	uint8_t l_usb_report_write_index;
	uint8_t queue_remain_data;

	hal_usb_disable_endpoint0();
	l_usb_report_write_index = g_usb_report_write_index;
	l_usb_report_read_index = g_usb_report_read_index;
	hal_usb_enable_endpoint0();

	queue_remain_data = get_queue_remain_data(l_usb_report_write_index, l_usb_report_read_index);

	if (queue_remain_data > 1) {
		LOG_INF("q_data[%d], w[%d], r[%d]", queue_remain_data, g_usb_report_write_index, g_usb_report_read_index);
	}

	while (l_usb_report_read_index != l_usb_report_write_index) {
		dev = g_usb_report_work_queue[l_usb_report_read_index].dev;
		cb = g_usb_report_work_queue[l_usb_report_read_index].cb;
		type = g_usb_report_work_queue[l_usb_report_read_index].type;
		id = g_usb_report_work_queue[l_usb_report_read_index].id;
		len = g_usb_report_work_queue[l_usb_report_read_index].len;
		data = g_usb_report_work_queue[l_usb_report_read_index].data;
		hal_usb_disable_endpoint0();
		g_usb_report_read_index = ((g_usb_report_read_index + 1) % REPORT_WORK_QUEUE_SIZE);
		l_usb_report_write_index = g_usb_report_write_index;
		l_usb_report_read_index = g_usb_report_read_index;
		hal_usb_enable_endpoint0();

		if (cb == NULL) {
			LOG_INF("set_report cb is NULL");
			break;
		}
		cb(dev, type, id, len, data);
	}
}
#endif

int air_usb_hid_device_register(const struct device *dev)
{
	if (air_usb_hid_cnt >= AIR_USB_HID_NUM) {
		return -EINVAL;
	}
	air_usb_hids[air_usb_hid_cnt].dev = (struct device *)dev;
	air_usb_hids[air_usb_hid_cnt].tx_trans.done = true;
	air_usb_hids[air_usb_hid_cnt].in_no_report_id = false;
	air_usb_hids[air_usb_hid_cnt].out_no_report_id = false;
	air_usb_hids[air_usb_hid_cnt].feature_in_no_report_id = false;
	air_usb_hids[air_usb_hid_cnt].feature_out_no_report_id = false;
	air_usb_hid_cnt++;
	air_usb_register_evt_cb(AIR_USB_USBHID_USER_ID, air_usb_hid_evt_cb);
#if defined(USB_HID_DBG_GPIO)
	air_usb_hid_dbg_io_init();
#endif /* USB_HID_DBG_GPIO */
	return 0;
}

static air_usb_hid_str_t *air_usb_hid_find_device(const struct device *dev)
{
	int idx = 0;
	air_usb_hid_str_t *str = NULL;
	for (idx = 0; idx < AIR_USB_HID_NUM; idx++) {
		if (air_usb_hids[idx].dev == dev) {
			str = &air_usb_hids[idx];
		}
	}

	return str;
}

int air_usb_hid_gen_rdesc(const struct device *dev, air_usb_hid_report_desc_t *descs, uint8_t descn)
{
	air_usb_hid_str_t *str = NULL;
	uint32_t len = 0;

	str = air_usb_hid_find_device(dev);

	if (!str) {
		return -EINVAL;
	}

	if (str->descs) {
		k_free(str->descs);
	}
	str->descs = k_malloc(sizeof(air_usb_hid_report_desc_t) * descn);
	str->descn = descn;

	if (str->descs == NULL) {
		LOG_INF("usb Failed to allocate memory descs");
		return -ENOMEM;
	} else if (descs == NULL) {
		LOG_INF("usb invalid input");
		return -EINVAL;
	}
	memcpy(str->descs, descs, sizeof(air_usb_hid_report_desc_t) * descn);

	/* Calculate the length of the report descriptor */
	for (uint16_t i = 0; i < descn; i++) {
		usb_hid_report_desc_hdlr_t *rhdlr = &air_usb_hid_report_descs[descs[i]];
		len += rhdlr->length;
		// LOG_DBG("i:%d, desc:%d, %s", i, descs[i], rhdlr->name);
	}

	/* Allocate memory for report descriptor */
	if (len > 0) {
		str->report_desc = k_malloc(len);
		str->report_desc_len = len;
	}
	if (str->report_desc == NULL) {
		LOG_INF("usb Failed to allocate memory report_desc");
		return -ENOMEM;
	}

	/* Copy report descriptors to allocated memory */
	uint8_t *ptr = str->report_desc;
	for (uint16_t i = 0; i < descn; i++) {
		usb_hid_report_desc_hdlr_t *rhdlr = &air_usb_hid_report_descs[descs[i]];
		if ((rhdlr == NULL) || (rhdlr->desc == NULL)) {
			LOG_INF("usb Invalid report descriptor[%d]", i);
			return -ENOMEM;
		}
		memcpy(ptr, rhdlr->desc, rhdlr->length);
		ptr += rhdlr->length;
	}

	// LOG_DBG("len:%d", len);

	if (len) {
		return 0;
	} else {
		return -EINVAL;
	}
}

int air_usb_hid_get_rdesc_len(const struct device *dev)
{
	air_usb_hid_str_t *str = NULL;
	str = air_usb_hid_find_device(dev);
	if (str == NULL) {
		LOG_INF("hid_str not found");
		return -EINVAL;
	}
	return str->report_desc_len;
}

const uint8_t *air_usb_hid_get_rdesc(const struct device *dev)
{
	air_usb_hid_str_t *str = NULL;
	str = air_usb_hid_find_device(dev);
	if (str == NULL) {
		LOG_INF("hid_str not found");
		return NULL;
	}
	return str->report_desc;
}

struct device *air_usb_hid_find_first_device_by_report(air_usb_hid_report_desc_t report)
{
	struct device *dev = NULL;
	air_usb_hid_str_t *hidstr;

	for (uint16_t i = 0; i < AIR_USB_HID_NUM; i++) {
		hidstr = &air_usb_hids[i];
#if 0
		LOG_DBG("i:%d, hidstr:%p, hidstr->descn:%d", i, hidstr,
			hidstr->descn);
#endif
		for (uint16_t j = 0; j < hidstr->descn; j++) {
#if 0
			LOG_DBG("  j:%d, desc:%d", i, hidstr->descs[j]);
#endif
			if (hidstr->descs[j] == report) {
				dev = hidstr->dev;
				break;
			}
		}

		if (dev) {
			break;
		}
	}

	return dev;
}

int air_usb_hid_tx(uint32_t user_id, const struct device *dev, uint16_t len, uint8_t *data)
{
	air_usb_hid_str_t *hidstr = NULL;
	uint8_t r_id;
	uint32_t wlen = 0;
	int ret = 0;

	//printk("air_usb_hid_tx user_id:%d, dev:%d, len:%d", user_id, dev, len);

#if defined(USB_HID_DBG_GPIO)
	hal_gpio_set_output(GPIO_TX, HAL_GPIO_DATA_HIGH);
#endif

	hidstr = air_usb_hid_find_device(dev);
	if (hidstr == NULL) {
		ret = -ENODEV;
		goto _leave_air_usb_hid_tx;
	}

	if (data == NULL || len == 0) {
		ret = -EFAULT;
		goto _leave_air_usb_hid_tx;
	}

	const struct usb_cfg_data *cfg;
	uint8_t ep_addr_in;

	if (!dev) {
		ret = -ENOMEM;
		LOG_INF("dev is NULL");
		goto _leave_air_usb_hid_tx;
	}
	cfg = dev->config;
	ep_addr_in = cfg->endpoint[HID_INT_IN_EP_IDX].ep_addr;

#if defined(AIR_BTD_IC_PREMIUM_G1)
	uint8_t ep_num = USB_EP_GET_IDX(ep_addr_in);
	bool ep_dir = USB_EP_GET_DIR(ep_addr_in);
	bool interrupt_enable = hal_usb_get_tx_interrupt_enable_status(ep_num);
	/* TODO: mutex protect */
	if (interrupt_enable) {
#endif
		if (hidstr->tx_trans.done == false && hidstr->tx_trans.rlen) {
			ret = -EBUSY;
			goto _leave_air_usb_hid_tx;
		}
#if defined(AIR_BTD_IC_PREMIUM_G1)
	} else {
		if (!hal_usb_ep_empty(ep_num, ep_dir)) {
			ret = -EBUSY;
			goto _leave_air_usb_hid_tx;
		}
	}
#endif
#if 0
	if (hidstr->in_no_report_id) {
		r_id = 0;
	}
	else
#endif
	{
		r_id = ((hidstr->in_no_report_id) ? 0 : data[0]);
	}

	/* TODO: report id & len check system? */
#if defined(AIR_BTD_IC_PREMIUM_G1)
	if (interrupt_enable) {
#endif
		hidstr->tx_trans.done = false;
		hidstr->tx_trans.rid = r_id;
		hidstr->tx_trans.rlen = len;
		hidstr->tx_trans.user_id = user_id;
#if defined(AIR_BTD_IC_PREMIUM_G1)
	}
#endif
	ret = hid_int_ep_write(dev, data, len, &wlen);
	if (ret) {
#if defined(AIR_BTD_IC_PREMIUM_G1)
		if (interrupt_enable) {
#endif
			hidstr->tx_trans.done = true;
#if defined(AIR_BTD_IC_PREMIUM_G1)
		}
#endif
	}
#if defined(AIR_BTD_IC_MANDATORY_G1)
	else {
		uint32_t fifonum;

		fifonum = hal_usb_ep_get_fifo_number(ep_addr_in);
		hal_usb_fifo_enable_int(fifonum, true, true);
	}
#endif

_leave_air_usb_hid_tx:
	if (ret) {
		/* Debug log */
	}
	// LOG_INF("air_usb_hid_tx len:%d, ret:%d", len, ret);

#if defined(USB_HID_DBG_GPIO)
	hal_gpio_set_output(GPIO_TX, HAL_GPIO_DATA_LOW);
#endif
	return ret;
}

#if IS_ENABLED(CONFIG_AIR_USB_HID_PKTDONE_EINT)
/**************************************************************************************************
 * USB HID PKTDONE Functions
 *************************************************************************************************/
int air_usb_hid_config_pktdone_eint(const struct device *dev, uint8_t dir, bool enable, uint8_t set)
{
	air_usb_hid_str_t *hidstr = NULL;
	const struct usb_cfg_data *cfg = dev->config;
	uint8_t ep_idx = 0;

	hidstr = air_usb_hid_find_device(dev);
	if (hidstr == NULL) {
		return -ENODEV;
	}

	if (set >= USB_HID_PKTDONE_SET_NUM) {
		return -EINVAL;
	}

	cfg = dev->config;

	if (dir == 0) {
		ep_idx = USB_EP_GET_IDX(cfg->endpoint[HID_INT_IN_EP_IDX].ep_addr);
	} else if (dir == 1) {
		ep_idx = USB_EP_GET_IDX(cfg->endpoint[HID_INT_OUT_EP_IDX].ep_addr);
	} else {
		return -EINVAL;
	}

	printk("air_usb_hid_config_pktdone_eint ep_idx:%d, dir:%d, enable:%d, set:%d\n", ep_idx,
	       dir, enable, set);

	air_usb_hid_pktdone_ctx[set].dev = (struct device *)dev;
	air_usb_hid_pktdone_ctx[set].ep_idx = ep_idx;
	air_usb_hid_pktdone_ctx[set].ep_dir = dir;
	air_usb_hid_pktdone_ctx[set].enable = enable;

	return 0;
}

int air_usb_hid_clear_pktdone_eint(const struct device *dev)
{
	air_usb_hid_str_t *hidstr = NULL;

	hidstr = air_usb_hid_find_device(dev);
	if (hidstr == NULL) {
		return -ENODEV;
	}

	int i;
	air_usb_hid_pktdone_ctx_t *pktdone = NULL;
	for (i = 0; i < USB_HID_PKTDONE_SET_NUM; i++) {
		pktdone = &air_usb_hid_pktdone_ctx[i];
		if (pktdone->enable && pktdone->dev == dev) {
			hal_usb_pktdone_clear(i);
		}
	}

	if (i == USB_HID_PKTDONE_SET_NUM) {
		return -EINVAL;
	}

	return 0;
}

bool air_usb_hid_get_pktdone_eint_status(const struct device *dev)
{
	air_usb_hid_str_t *hidstr = NULL;

	hidstr = air_usb_hid_find_device(dev);
	if (hidstr == NULL) {
		return false;
	}

	if (hidstr->pktdone_enable == 0) {
		return false;
	}

	if (hal_usb_pktdone_get_status(hidstr->pktdone_set)) {
		return true;
	} else {
		return false;
	}
}

static void air_usb_hid_pktdone_reset(void)
{
	air_usb_hid_pktdone_ctx_t *pktdone = NULL;
	for (int i = 0; i < USB_HID_PKTDONE_SET_NUM; i++) {
		pktdone = &air_usb_hid_pktdone_ctx[i];
		hal_usb_pktdone_cfg(i, 0, 0, 0);
	}
}

static void air_usb_hid_pktdone_setup(void)
{
	uint8_t ep_idx = 0;
	air_usb_hid_pktdone_ctx_t *pktdone = NULL;
	const struct usb_cfg_data *cfg = NULL;

	for (int i = 0; i < USB_HID_PKTDONE_SET_NUM; i++) {
		pktdone = &air_usb_hid_pktdone_ctx[i];
		if (pktdone->enable && pktdone->dev) {
			cfg = pktdone->dev->config;
			ep_idx = USB_EP_GET_IDX(cfg->endpoint[HID_INT_IN_EP_IDX].ep_addr);
			hal_usb_pktdone_cfg(i, pktdone->enable, ep_idx, pktdone->ep_dir ? 0 : 1);
		} else {
			hal_usb_pktdone_cfg(i, 0, 0, 0);
		}
	}
}
#endif

/**************************************************************************************************
 * Airoha USB HID Callback Register Functions
 *************************************************************************************************/

static cb_hdlr_t *find_cb_hdlr(cb_hdlr_t *hdlrs, uint16_t hdlrs_len, const struct device *dev,
			       uint8_t type, uint8_t id, uint16_t len)
{
	cb_hdlr_t *hdlr = NULL;
	air_usb_hid_str_t *str = NULL;
	uint8_t input_output_type = (type & (USB_HID_REPORT_TYPE_NO_REPORT_ID_BIT - 1));

	str = air_usb_hid_find_device(dev);

	if (!str) {
		return hdlr;
	}

	if (((input_output_type == USB_HID_REPORT_TYPE_INPUT) && str->in_no_report_id) ||
		((input_output_type == USB_HID_REPORT_TYPE_OUTPUT) && str->out_no_report_id) ||
		((input_output_type == USB_HID_REPORT_TYPE_FEATURE) && str->feature_in_no_report_id) ||
		((input_output_type == USB_HID_REPORT_TYPE_FEATURE) && str->feature_out_no_report_id)) {
		for (uint32_t i = 0; i < hdlrs_len; i++) {
			if (hdlrs[i].dev == dev && hdlrs[i].type == (USB_HID_REPORT_TYPE_NO_REPORT_ID_BIT | type) &&
				hdlrs[i].len == len && hdlrs[i].registered == true) {
				hdlr = &hdlrs[i];
				break;
			}
		}
	} else {
		for (uint32_t i = 0; i < hdlrs_len; i++) {
			if (hdlrs[i].dev == dev && hdlrs[i].type == type && hdlrs[i].id == id &&
				hdlrs[i].len == len && hdlrs[i].registered == true) {
				hdlr = &hdlrs[i];
				break;
			}
		}
	}

	return hdlr;
}

static cb_hdlr_t *find_first_empty_hdlr(cb_hdlr_t *hdlrs, uint16_t hdlrs_len)
{
	cb_hdlr_t *hdlr = NULL;
	for (uint32_t i = 0; i < hdlrs_len; i++) {
		if (hdlrs[i].registered == false) {
			hdlr = &hdlrs[i];
		}
	}

	return hdlr;
}

static int register_cb(cb_hdlr_t *hdlrs, uint16_t hdlrs_len, uint32_t user_id,
		       const struct device *dev, uint8_t type, uint8_t id, uint16_t len, void *cb)
{
	cb_hdlr_t *hdlr = NULL;
	air_usb_hid_str_t *str = NULL;

	str = air_usb_hid_find_device(dev);

	if (!str) {
		return -EINVAL;
	}
	if (((type == USB_HID_REPORT_TYPE_INPUT_NO_REPORT_ID) && str->in_no_report_id) ||
	((type == USB_HID_REPORT_TYPE_OUTPUT_NO_REPORT_ID) && str->out_no_report_id) ||
	((type == USB_HID_REPORT_TYPE_FEATURE_NO_REPORT_ID) && (hdlrs == get_report_hdlrs) && str->feature_in_no_report_id) ||
	((type == USB_HID_REPORT_TYPE_FEATURE_NO_REPORT_ID) && (hdlrs == set_report_hdlrs) && str->feature_out_no_report_id)) {
		return -EPERM;
	}

	hdlr = find_cb_hdlr(hdlrs, hdlrs_len, dev, type, id, len);

	if (hdlr != NULL) {
		if (hdlr->user_id != user_id) {
			/* If different user register the same report, return
			 * error. */
			return -EACCES;
		} else {
			/* If the same user register the same report again,
			 * update cb. */
			hdlr->cb = cb;
			return 0;
		}
	}

	hdlr = find_first_empty_hdlr(hdlrs, hdlrs_len);

	if (hdlr) {
		hdlr->user_id = user_id;
		hdlr->dev = dev;
		hdlr->type = type;
		hdlr->id = id;
		hdlr->len = len;
		hdlr->cb = cb;
		hdlr->registered = true;

		if (type == USB_HID_REPORT_TYPE_INPUT_NO_REPORT_ID) {
			str->in_no_report_id = true;
		} else if (type == USB_HID_REPORT_TYPE_OUTPUT_NO_REPORT_ID) {
			str->out_no_report_id = true;
		} else if (type == USB_HID_REPORT_TYPE_FEATURE_NO_REPORT_ID) {
			if (hdlrs == get_report_hdlrs) {
				str->feature_in_no_report_id = true;
			} else if (hdlrs == set_report_hdlrs){
				str->feature_out_no_report_id = true;
			}
		}
		return 0;
	} else {
		/* LOG : The cb handler is full, please increase
		 * CONFIG_AIR_USB_HID_GET_REPORT_CB_NUM. */
		return -EINVAL;
	}
}

int air_usb_hid_register_get_report_cb(uint32_t user_id, const struct device *dev, uint8_t type,
				       uint8_t id, uint16_t len, air_hid_get_report_cb_t cb)
{
	if (air_usb_check_user_id(user_id) != 0) {
		return -EINVAL;
	}

	if ((type == USB_HID_REPORT_TYPE_OUTPUT) || (type == USB_HID_REPORT_TYPE_OUTPUT_NO_REPORT_ID)) {
		return -EINVAL;
	}

	int status = 0;

	status = register_cb(get_report_hdlrs, GET_REPORT_CB_NUM, user_id, dev, type, id, len, cb);
	LOG_INF("air_usb_hid_register_get_report_cb user_id:%d cb:%p, status:%d, dev:%p, type:%d, id:%d, len:%d",
			user_id, cb, status, dev, type, id, len);

	return status;
}

int air_usb_hid_register_set_report_cb(uint32_t user_id, const struct device *dev, uint8_t type,
				       uint8_t id, uint16_t len, air_hid_set_report_cb_t cb)
{
	if (air_usb_check_user_id(user_id) != 0) {
		return -EINVAL;
	}

	if ((type == USB_HID_REPORT_TYPE_INPUT) || (type == USB_HID_REPORT_TYPE_INPUT_NO_REPORT_ID)) {
		return -EINVAL;
	}

	int status = 0;

	status = register_cb(set_report_hdlrs, SET_REPORT_CB_NUM, user_id, dev, type, id, len, cb);
	LOG_INF("air_usb_hid_register_set_report_cb user_id:%d cb:%p, status:%d, dev:%p, type:%d, id:%d, len:%d",
			user_id, cb, status, dev, type, id, len);
	return status;
}

int air_usb_hid_register_output_cb(uint32_t user_id, const struct device *dev, uint8_t type,
				   uint8_t id, uint16_t len, air_hid_output_cb_t cb)
{
	if (air_usb_check_user_id(user_id) != 0) {
		return -EINVAL;
	}

	if ((type == USB_HID_REPORT_TYPE_INPUT) || (type == USB_HID_REPORT_TYPE_INPUT_NO_REPORT_ID)) {
		return -EINVAL;
	}

	int status = 0;

	status = register_cb(output_hdlrs, OUTPUT_CB_NUM, user_id, dev, type, id, len, cb);
	LOG_DBG("user:%s(0x%08X), cb:%p, status:%d, dev:%p, type:%d, id:%d, "
		"len:%d",
		air_usb_get_user_name(user_id), user_id, cb, status, dev, type, id, len);

	return status;
}

int air_usb_hid_register_tx_done_cb(uint32_t user_id, const struct device *dev, uint8_t type,
				    uint8_t id, uint16_t len, air_hid_tx_done_cb_t cb)
{
	if (air_usb_check_user_id(user_id) != 0) {
		return -EINVAL;
	}

	if ((type == USB_HID_REPORT_TYPE_OUTPUT) || (type == USB_HID_REPORT_TYPE_OUTPUT_NO_REPORT_ID)) {
		return -EINVAL;
	}

	int status = 0;

	status = register_cb(tx_done_hdlrs, TX_DONE_CB_NUM, user_id, dev, type, id, len, cb);
	LOG_DBG("user:%s(0x%08X), cb:%p, status:%d, dev:%p, type:%d, id:%d, "
		"len:%d",
		air_usb_get_user_name(user_id), user_id, cb, status, dev, type, id, len);

	return status;
}

int air_usb_hid_register_tx_free_cb(uint32_t user_id, const struct device *dev,
				    air_hid_tx_free_cb_t cb)
{
	if (air_usb_check_user_id(user_id) != 0) {
		return -EINVAL;
	}

	int status = 0;

	status = register_cb(tx_free_hdlrs, TX_FREE_CB_NUM, user_id, dev, 0, 0, 0, cb);
	LOG_DBG("user:%s(0x%08X), cb:%p, status:%d, dev:%p", air_usb_get_user_name(user_id),
		user_id, cb, status, dev);

	return status;
}

int air_usb_hid_register_protocol_change_cb(uint32_t user_id, const struct device *dev,
					    air_hid_protocol_change_cb_t cb)
{
	if (air_usb_check_user_id(user_id) != 0) {
		return -EINVAL;
	}

	int status = 0;

	status = register_cb(protocol_hdlrs, PROTOCOL_CB_NUM, user_id, dev, 0, 0, 0, cb);
	LOG_DBG("user:%s(0x%08X), cb:%p, status:%d, dev:%p", air_usb_get_user_name(user_id),
		user_id, cb, status, dev);

	return 0;
}

/**************************************************************************************************
 * USB Status Callback Implementation
 *************************************************************************************************/
static void air_usb_hid_evt_cb(air_usb_evt_t evt, const uint8_t *para)
{
	air_usb_hid_str_t *str = NULL;
	switch (evt) {
	case AIR_USB_EVT_PLUG_OUT:
	case AIR_USB_EVT_RESET: {
		/* Reset TX Status */
		LOG_INF("reset hid tx status");
		for (uint8_t i = 0; i < AIR_USB_HID_NUM; i++) {
			str = &air_usb_hids[i];
			str->tx_trans.done = true;
		}
#if IS_ENABLED(CONFIG_AIR_USB_HID_PKTDONE_EINT)
		air_usb_hid_pktdone_reset();
#endif
		break;
	}
	case AIR_USB_EVT_SUSPEND:
	case AIR_USB_EVT_RESUME:
		break;
	case AIR_USB_EVT_CONFIGURED:
#if IS_ENABLED(CONFIG_AIR_USB_HID_PKTDONE_EINT)
		air_usb_hid_pktdone_setup();
#endif
	default:
		break;
	}
}

/**************************************************************************************************
 * Zephyr USB HID Callback Implementation
 *************************************************************************************************/

/**
 * @brief Airoha USB HID Get Report Callback
 *
 * @param dev[in]
 * @param setup[in]
 * @param len[in]
 * @param data[in]
 * @return int
 *
 * This function is registered to zephyr usb_dc hid stack.
 * And dispatch GetReport request to user-defined callback function.
 */
static int air_usb_hid_get_report_callback(const struct device *dev, struct usb_setup_packet *setup,
					   int32_t *len, uint8_t **data)
{
	uint8_t r_type = setup->wValue >> 8;
	uint8_t r_id = setup->wValue & 0xFF;
	uint8_t r_if __unused = setup->wIndex;
	uint16_t r_len = setup->wLength;

	cb_hdlr_t *hdlr = NULL;
	air_hid_get_report_cb_t cb = NULL;

#if 0
	LOG_INF("air_usb_hid_get_report_callback, r_if:%d, r_type=%d, r_id=%dr_len=%d\r\n",
		r_if, r_type, r_id, r_len);
#endif
	if (r_len > AIR_USB_HID_REPOTR_MAX_LEN) {
		return -ENOMEM;
	}

	hdlr = find_cb_hdlr(get_report_hdlrs, GET_REPORT_CB_NUM, dev, r_type, r_id, r_len);
	if (hdlr) {
		cb = hdlr->cb;
	}

	memset(air_usb_get_report_buf, 0, r_len);
	if (cb) {
#if 0
		LOG_DBG("user:%s(0x%08X), cb:%p",
			air_usb_get_user_name(hdlr->user_id), hdlr->user_id, cb);
#endif
		cb(dev, r_type, r_id, r_len, air_usb_get_report_buf);
	} else {
		/* If no callback registered, return all zero data */
		air_usb_get_report_buf[0] = r_id;
	}

	if (r_id != 0 && air_usb_get_report_buf[0] != r_id) {
		// TODO: WARNING
	}

	*data = air_usb_get_report_buf;
	*len = r_len;

	return 0;
}

/**
 * @brief Airoha USB HID Set Report Callback
 *
 * @param dev[in]
 * @param setup[in]
 * @param len[in]
 * @param data[in]
 * @return int
 *
 * This function is registered to zephyr usb_dc hid stack.
 * And dispatch SetReport request to user-defined callback function.
 */
ATTR_TEXT_IN_TCM static int air_usb_hid_set_report_callback(const struct device *dev, struct usb_setup_packet *setup,
					   int32_t *len, uint8_t **data)
{
	uint8_t r_type = setup->wValue >> 8;
	uint8_t r_id = setup->wValue & 0xFF;
	uint8_t r_if __unused = setup->wIndex;
	uint16_t r_len = setup->wLength;
	const uint8_t *buf __unused = *data;

	cb_hdlr_t *hdlr = NULL;
	air_hid_set_report_cb_t cb = NULL;

	//LOG_INF("air_usb_hid_set_report_callback dev:%p, r_if:%d, r_type=%d, r_id=%d, r_len=%d", dev, r_if, r_type, r_id, r_len);
#if defined(CONFIG_MCUBOOT)
	if (r_len > AIR_USB_HID_REPOTR_MAX_LEN) {
		LOG_INF("set_report exceed max buffer[%d], curr[%d]", AIR_USB_HID_REPOTR_MAX_LEN, r_len);
		return -ENOMEM;
	}
#else
	if (r_len > AIR_USB_HID_SET_REPOTR_BUFFER_LEN) {
		LOG_INF("set_report exceed max buffer[%d], curr[%d]", AIR_USB_HID_SET_REPOTR_BUFFER_LEN, r_len);
		return -ENOMEM;
	}
#endif

	hdlr = find_cb_hdlr(set_report_hdlrs, SET_REPORT_CB_NUM, dev, r_type, r_id, r_len);
	if (hdlr) {
		cb = hdlr->cb;
	}

	if (cb) {
#if 1
		LOG_DBG("user:%s(0x%08X), cb:%p", air_usb_get_user_name(hdlr->user_id),
			hdlr->user_id, cb);
#endif
#if defined(CONFIG_MCUBOOT)
		cb(dev, r_type, r_id, r_len, *data);
#else
		if (((g_usb_report_write_index + 1) % REPORT_WORK_QUEUE_SIZE) != g_usb_report_read_index) {
			g_usb_report_work_queue[g_usb_report_write_index].cb = cb;
			g_usb_report_work_queue[g_usb_report_write_index].dev = dev;
			g_usb_report_work_queue[g_usb_report_write_index].type = r_type;
			g_usb_report_work_queue[g_usb_report_write_index].id = r_id;
			g_usb_report_work_queue[g_usb_report_write_index].len = r_len;
			memcpy(g_usb_report_work_queue[g_usb_report_write_index].data, (*data), r_len);
			g_usb_report_write_index = ((g_usb_report_write_index + 1) % REPORT_WORK_QUEUE_SIZE);
			k_work_submit(&g_usb_set_report_work);
		} else {
			LOG_INF("g_usb_report_work_queue full, put fail!");
		}
#endif
	}

	return 0;
}

/**
 * @brief Airoha USB HID Protocol Change Callback
 *
 * @param dev[in]
 * @param protocol[in]
 *
 * This function is registered to zephyr usb_dc hid stack.
 * And dispatch Protocol Change request to user-defined callback function.
 */
static void air_usb_hid_protocol_change_callback(const struct device *dev, uint8_t protocol)
{
	cb_hdlr_t *hdlr = NULL;
	air_hid_protocol_change_cb_t cb = NULL;

#if 1
	LOG_INF("air_usb_hid_protocol_change_callback, dev:0x%08X, protocol:%d", (uint32_t)dev,
		protocol);
#endif

	/* Multi user callback */
	for (int i = 0; i < PROTOCOL_CB_NUM; i++) {
		hdlr = &protocol_hdlrs[i];
		if (hdlr->dev == dev && hdlr->cb) {
			cb = hdlr->cb;
			cb(dev, protocol);
#if 0
			LOG_DBG("user:%s(0x%08X), protocol_change cb:%p",
				air_usb_get_user_name(hdlr->user_id), hdlr->user_id, hdlr->cb);
#endif
		}
	}
}

/**
 * @brief Airoha USB HID On Idle Callback
 *
 * @param dev[in]
 * @param report_id[in]
 *
 * This function is registered to zephyr usb_dc hid stack.
 */
static void air_usb_hid_on_idle_callback(const struct device *dev, uint16_t report_id)
{
}

/**
 * @brief Airoha USB HID Input Ready Callback
 *
 * @param dev[in]
 *
 * This function is registered to zephyr usb_dc hid stack.
 */
static void air_usb_hid_int_in_ready_callback(const struct device *dev)
{
	air_usb_hid_str_t *hidstr = NULL;
	cb_hdlr_t *hdlr = NULL;
	uint8_t r_type = USB_HID_REPORT_TYPE_INPUT;
	uint8_t r_id = 0;
	uint32_t r_len = 0;

	air_hid_tx_done_cb_t tx_done_cb = NULL;

	hidstr = air_usb_hid_find_device(dev);
	if (hidstr == NULL) {
		return;
	}
#if defined(USB_HID_DBG_GPIO)
	hal_gpio_set_output(GPIO_TXDONE, HAL_GPIO_DATA_HIGH);
#endif

	r_id = hidstr->tx_trans.rid;
	r_len = hidstr->tx_trans.rlen;

	/* TODO: mutex protect */
	hidstr->tx_trans.done = true;

	LOG_DBG("dev:%p, r_type:%d, r_id:%d, r_len:%d", dev, r_type, r_id, r_len);
	/* Execute TX Done Callback */
	hdlr = find_cb_hdlr(tx_done_hdlrs, TX_DONE_CB_NUM, dev, r_type, r_id, r_len);
	if (hdlr) {
		tx_done_cb = hdlr->cb;
	}
	if (tx_done_cb) {
#if 1
		LOG_DBG("user:%s(0x%08X), tx_done cb:%p", air_usb_get_user_name(hdlr->user_id),
			hdlr->user_id, tx_done_cb);
#endif
		tx_done_cb(dev, r_type, r_id, r_len, NULL);
	}

	/* Execute TX Free Callback */
	if (hidstr->tx_trans.done == false) {
		/* user send data in the tx_done callback function  */
#if defined(USB_HID_DBG_GPIO)
	hal_gpio_set_output(GPIO_TXDONE, HAL_GPIO_DATA_LOW);
#endif
		return;
	}

	/* if no data is available */
	for (int i = 0; i < TX_FREE_CB_NUM; i++) {
		hdlr = &tx_free_hdlrs[i];
		if (hdlr->dev == dev && hdlr->cb) {
			((air_hid_tx_free_cb_t)hdlr->cb)(dev);
#if 1
			LOG_DBG("user:%s(0x%08X), tx_free cb:%p",
				air_usb_get_user_name(hdlr->user_id), hdlr->user_id, hdlr->cb);
#endif
		}
	}
#if defined(USB_HID_DBG_GPIO)
	hal_gpio_set_output(GPIO_TXDONE, HAL_GPIO_DATA_LOW);
#endif
}

/**
 * @brief Airoha USB HID Output Ready Callback
 *
 * @param dev[in]
 *
 * This function is registered to zephyr usb_dc hid stack.
 */
static void air_usb_hid_int_out_ready_callback(const struct device *dev) __unused;
static void air_usb_hid_int_out_ready_callback(const struct device *dev)
{
	air_usb_hid_str_t *hidstr = NULL;
	cb_hdlr_t *hdlr = NULL;
	air_hid_set_report_cb_t cb = NULL;
	const struct usb_cfg_data *cfg = dev->config;

	uint8_t r_type = USB_HID_REPORT_TYPE_OUTPUT;
	uint8_t r_id = 0;
	uint32_t r_len = 0;

	hidstr = air_usb_hid_find_device(dev);

	/* TODO: Replace sizeof(air_usb_out_report_buf) as hid mps. */
	hid_int_ep_read(dev, air_usb_out_report_buf, sizeof(air_usb_out_report_buf), &r_len);

	if (r_len == 0) {
		LOG_ERR("Zero Length Report");
		return;
	}

	r_id = air_usb_out_report_buf[0];

#if 0
	if (hidstr->out_no_report_id) {
		r_id = 0;
	}
	else {
		r_id = air_usb_out_report_buf[0];
	}
#endif

	hdlr = find_cb_hdlr(output_hdlrs, OUTPUT_CB_NUM, dev, r_type, r_id, r_len);
	if (hdlr) {
		cb = hdlr->cb;
	}

	if (cb) {
#if 1
		LOG_DBG("user:%s(0x%08X), cb:%p", air_usb_get_user_name(hdlr->user_id),
			hdlr->user_id, cb);
#endif
		cb(dev, r_type, r_id, r_len, air_usb_out_report_buf);
	} else {
		LOG_WRN("No callback registered for output report dev:%p, "
			"ep:%d, id:%d, len:%d",
			dev, cfg->endpoint[HID_INT_OUT_EP_IDX].ep_addr, r_id, r_len);
	}
}

int air_usb_hid_get_protocol_mode(const struct device *dev)
{
#ifdef CONFIG_USB_HID_BOOT_PROTOCOL
	struct hid_device_info *dev_data = dev->data;
	printk("air_usb_hid_get_protocol_mode dev:%08X, protocol:%d", (uint32_t)dev, dev_data->protocol);
	return dev_data->protocol;
#else
	return USB_PROTOCOL_REPORT_MODE;
#endif
}

const struct hid_ops airoha_usb_hid_ops = {
	.get_report = air_usb_hid_get_report_callback,
	.set_report = air_usb_hid_set_report_callback,
	.protocol_change = air_usb_hid_protocol_change_callback,
	.on_idle = air_usb_hid_on_idle_callback,
	.int_in_ready = air_usb_hid_int_in_ready_callback,
#ifdef CONFIG_ENABLE_HID_INT_OUT_EP
	.int_out_ready = air_usb_hid_int_out_ready_callback,
#endif
};

#endif /* AIR_USB_HID_ENABLE */
