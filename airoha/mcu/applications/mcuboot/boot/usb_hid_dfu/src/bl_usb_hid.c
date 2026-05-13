/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
 *
 * This software/firmware and related documentation ("Airoha Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or
 * its licensors. Without the prior written permission of Airoha and/or its
 * licensors, any reproduction, modification, use or disclosure of Airoha
 * Software, and information contained herein, in whole or in part, shall be
 * strictly prohibited. You may only use, reproduce, modify, or distribute (as
 * applicable) Airoha Software if you have agreed to and been bound by the
 * applicable license agreement with Airoha ("License Agreement") and been
 * granted explicit permission to do so within the License Agreement ("Permitted
 * User").  If you are not a Permitted User, please cease any access or use of
 * Airoha Software immediately. BY OPENING THIS FILE, RECEIVER HEREBY
 * UNEQUIVOCALLY ACKNOWLEDGES AND AGREES THAT AIROHA SOFTWARE RECEIVED FROM
 * AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON AN "AS-IS"
 * BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY
 * ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY
 * THIRD PARTY ALL PROPER LICENSES CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL
 * ALSO NOT BE RESPONSIBLE FOR ANY AIROHA SOFTWARE RELEASES MADE TO RECEIVER'S
 * SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 * RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND CUMULATIVE
 * LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE, AT
 * AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE, OR REFUND ANY
 * SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO AIROHA FOR SUCH
 * AIROHA SOFTWARE AT ISSUE.
 */

#ifdef CONFIG_AIR_BL_USB_HID_DFU_ENABLE

#include "bl_usb_hid.h"

#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/atomic.h>

#include "hal_usb.h"
#include "air_usb.h"
#include "air_usb_hid.h"
#include "hal_pmu.h"

#define USB_WAIT_TX_READY_TIME 500 /* ms */
#define DATAREADY_BIT 1

static volatile bool configured;
static const struct device *hdev0;
static uint32_t bl_usb_id;

#define BL_USB_HID_PAYLOAD_MAX_LEN 4112

static uint8_t rxbuf[BL_USB_HID_PAYLOAD_MAX_LEN];

typedef struct {
	uint32_t txlen;
	uint8_t *txbuf;
	uint32_t txbuf_len;
	uint32_t rxlen;
	uint8_t *rxbuf;
	uint32_t rxbuf_len;
	ATOMIC_DEFINE(txready, 1);
} bl_usb_hid_t;

static bl_usb_hid_t ctx1;
static bl_usb_hid_t *ctx = &ctx1;


typedef struct __attribute__((__packed__)) {
	uint8_t report_id;
	uint16_t payload_len;
	uint8_t reserved;
	uint8_t data[BL_USB_HID_PAYLOAD_MAX_LEN];
} bl_usb_report_t;

static inline bool bl_usb_is_tx_ready(void)
{
	return atomic_test_bit(ctx->txready, DATAREADY_BIT);
}

static inline int bl_usb_set_tx_ready(void)
{
	return atomic_test_and_set_bit(ctx->txready, DATAREADY_BIT);
}

static inline int bl_usb_clear_tx_ready(void)
{
	return atomic_test_and_clear_bit(ctx->txready, DATAREADY_BIT);
}

void bl_usb_evt_cb(air_usb_evt_t evt, const uint8_t *para)
{
	int ret;
	switch (evt) {
	case AIR_USB_EVT_PLUG_IN:
		printk("AIR_USB_EVT_PLUG_IN\r\n");
		ret = air_usb_enable();
		if (ret != 0) {
			printk("Failed to enable USB: %d\r\n", ret);
			return;
		}
		break;
	case AIR_USB_EVT_PLUG_OUT:
		printk("AIR_USB_EVT_PLUG_OUT\r\n");
		ret = air_usb_disable();
		if (ret != 0) {
			printk("Failed to disable USB: %d\r\n", ret);
			return;
		}
		configured = false;
		break;
	case AIR_USB_EVT_CONFIGURED:
		printk("AIR_USB_EVT_CONFIGURED\r\n");
		configured = true;
		break;
	case AIR_USB_EVT_RESET:
		printk("AIR_USB_EVT_RESET\r\n");
		configured = false;
		break;
	case AIR_USB_EVT_SUSPEND:
		printk("AIR_USB_EVT_SUSPEND\r\n");
		break;
	case AIR_USB_EVT_RESUME:
		printk("AIR_USB_EVT_RESUME\r\n");
		break;
	default:
		break;
	}
}

void bl_usb_cfg_init()
{
	int rlen;

	hal_usb_set_speed(0);

	hdev0 = device_get_binding("HID_0");
	if (hdev0 == NULL) {
		printk("Cannot get USB HID Device 0");
	}

	/* Register the HID device to airoha usb hid subsys */
	air_usb_hid_device_register(hdev0);

	air_usb_hid_gen_rdesc(hdev0,
			      (air_usb_hid_report_desc_t[1]){
				      AIR_USB_REPORT_DESC_MUX2,
			      },
			      1);
	rlen = air_usb_hid_get_rdesc_len(hdev0);

	if (rlen < 0) {
		printk("rlen[%d] error", rlen);
		return;
	}
	/* Register to Zephyr USB HID stack */
	usb_hid_register_device(hdev0, air_usb_hid_get_rdesc(hdev0),
				rlen,
				&airoha_usb_hid_ops);

	usb_hid_init(hdev0);
}

static int bl_usb_hid_tx_callback(const struct device *dev, uint8_t type,
				  uint8_t id, uint16_t len, uint8_t *buf)
{
	uint32_t txlen = 0;
	uint8_t *txptr = NULL;
	bl_usb_report_t *report; /* cast data to report_t */

	/* Get the data from tx buf */
	if (bl_usb_is_tx_ready()) {
		if ((ctx->txbuf_len - ctx->txlen) >
		    AIR_USB_HID_AIR2_IN_REPORT_LEN) {
			txlen = AIR_USB_HID_AIR2_IN_REPORT_LEN;
			txptr = ctx->txbuf + ctx->txlen;
		} else {
			txlen = ctx->txbuf_len - ctx->txlen;
			txptr = ctx->txbuf + ctx->txlen;
		}
		ctx->txlen = ctx->txlen + txlen;
	}

	/* Generate Report */
	report = (bl_usb_report_t *)buf;
	report->report_id = AIR_USB_HID_AIR2_IN_REPORT_ID;
	report->payload_len = txlen;
	report->reserved = 0;
	memcpy(report->data, txptr, txlen);
	memset(report->data + txlen, 0, AIR_USB_HID_AIR2_IN_REPORT_LEN - txlen);

	if (txlen > 0) {
		printk("bl_usb_hid_tx_callback tx_len:%d, completeted:%d\r\n", txlen, ctx->txlen == ctx->txbuf_len);
	}

	if (ctx->txlen == ctx->txbuf_len) {
		bl_usb_clear_tx_ready();
	}

	return 0;
}

static int bl_usb_hid_tx_feature_callback(const struct device *dev, uint8_t type,
				  uint8_t id, uint16_t len, uint8_t *buf)
{
	uint32_t txlen = 0;
	uint8_t *txptr = NULL;
	bl_usb_report_t *report; /* cast data to report_t */

	/* Get the data from tx buf */
	if (bl_usb_is_tx_ready()) {
		if ((ctx->txbuf_len - ctx->txlen) >
		    AIR_USB_HID_BL_DFU_FEATURE_REPORT_LEN) {
			txlen = AIR_USB_HID_BL_DFU_FEATURE_REPORT_LEN;
			txptr = ctx->txbuf + ctx->txlen;
		} else {
			txlen = ctx->txbuf_len - ctx->txlen;
			txptr = ctx->txbuf + ctx->txlen;
		}
		ctx->txlen = ctx->txlen + txlen;
	}

	/* Generate Report */
	report = (bl_usb_report_t *)buf;
	report->report_id = AIR_USB_HID_AIR2_IN_REPORT_ID;
	report->payload_len = txlen;
	report->reserved = 0;
	memcpy(report->data, txptr, txlen);
	memset(report->data + txlen, 0, AIR_USB_HID_BL_DFU_FEATURE_REPORT_LEN - txlen);

	if (txlen > 0) {
		printk("bl_usb_hid_tx_feature_callback tx_len:%d, completeted:%d\r\n", txlen, ctx->txlen == ctx->txbuf_len);
	}

	if (ctx->txlen == ctx->txbuf_len) {
		bl_usb_clear_tx_ready();
	}

	return 0;
}

static int bl_usb_hid_rx_callback(const struct device *dev, uint8_t type,
				  uint8_t id, uint16_t len, const uint8_t *buf)
{
	bl_usb_report_t *report; /* cast data to report_t */
	uint32_t plen;           /* the payload length */

	report = (bl_usb_report_t *)buf;
	plen = report->payload_len;


#ifdef USB_DEBUG_LOG_ENABLE
	for (uint32_t i = 0; i < 8; i++) {
		printk("%02X ", report->data[i]);
	}
	printk("...");

	for (uint32_t i = plen - 3; i < plen; i++) {
		printk("%02X ", report->data[i]);
	}
	printk("\r\n");
#endif

	if (plen) {
		if ((ctx->rxbuf_len + plen) > BL_USB_HID_PAYLOAD_MAX_LEN) {
			ctx->rxbuf_len = 0;
		}
		memcpy(ctx->rxbuf + ctx->rxbuf_len, report->data, plen);
		ctx->rxbuf_len += plen;
		printk("usb_hid_rx_callback plen:%d, rxbuf_len:%d\r\n", plen, ctx->rxbuf_len);
	}
	return 0;
}

static void bl_usb_reg_cb(void)
{
	air_usb_register_evt_cb(bl_usb_id, bl_usb_evt_cb);

	const struct device *hiddev = air_usb_hid_find_first_device_by_report(
		AIR_USB_REPORT_DESC_MUX2);

	air_usb_hid_register_set_report_cb(
		bl_usb_id, hiddev, USB_HID_REPORT_TYPE_OUTPUT,
		AIR_USB_HID_AIR2_OUT_REPORT_ID, AIR_USB_HID_AIR2_OUT_REPORT_LEN,
		bl_usb_hid_rx_callback);
	air_usb_hid_register_get_report_cb(
		bl_usb_id, hiddev, USB_HID_REPORT_TYPE_INPUT,
		AIR_USB_HID_AIR2_IN_REPORT_ID, AIR_USB_HID_AIR2_IN_REPORT_LEN,
		bl_usb_hid_tx_callback);
	air_usb_hid_register_set_report_cb(
            bl_usb_id, hiddev, USB_HID_REPORT_TYPE_FEATURE, AIR_USB_HID_BL_DFU_FEATURE_REPORT_ID,
            AIR_USB_HID_BL_DFU_FEATURE_REPORT_LEN, bl_usb_hid_rx_callback);
	air_usb_hid_register_get_report_cb(
		bl_usb_id, hiddev, USB_HID_REPORT_TYPE_FEATURE, AIR_USB_HID_BL_DFU_FEATURE_REPORT_ID,
		AIR_USB_HID_BL_DFU_FEATURE_REPORT_LEN, bl_usb_hid_tx_feature_callback);
}

void bl_usb_sw_init(void)
{
	ctx->rxbuf = rxbuf;
	ctx->rxlen = 0;
	ctx->rxbuf_len = 0;
	bl_usb_clear_tx_ready();
}

int bl_usb_hid_init(void)
{
	printk("bl_usb_hid_init");
	air_usb_create_user("HIDDFU", &bl_usb_id);

	bl_usb_sw_init();
	bl_usb_cfg_init();
	bl_usb_reg_cb();

	air_usb_init();
	hal_usb_set_speed(0);
	air_usb_enable();
	return 0;
}

int bl_usb_hid_deinit(void)
{
	air_usb_disable();
	air_usb_deinit();
	return 0;
}

int bl_usb_hid_get(uint8_t *data, uint32_t length, uint32_t *rxlen)
{
	uint8_t* rxptr = NULL;
	int res = 0;

	if (data == NULL || length == 0) {
		*rxlen = 0;
		return BL_USB_HID_STATUS_GET_LENGTH_ZERO;
	}

	hal_nvic_disable_irq(USB_IRQn);
	if (ctx->rxbuf_len == 0) {
		*rxlen = 0;
		res = BL_USB_HID_STATUS_GET_LENGTH_ZERO;
		goto unlock;
	}

	if (ctx->rxbuf_len - ctx->rxlen > length) {
		*rxlen = length;
	} else {
		*rxlen = ctx->rxbuf_len - ctx->rxlen;
	}
	rxptr = ctx->rxbuf + ctx->rxlen;
	hal_nvic_enable_irq(USB_IRQn);
	memcpy(data, rxptr, *rxlen);
	ctx->rxlen = ctx->rxlen + *rxlen;

	if (*rxlen) {
		printk("usb_hid_get rx_len:%d, rxlen==rxbuf_len:%d\r\n", *rxlen, ctx->rxlen == ctx->rxbuf_len);
	}

	hal_nvic_disable_irq(USB_IRQn);
	if (ctx->rxlen == ctx->rxbuf_len) {
		ctx->rxlen = 0;
		ctx->rxbuf_len = 0;
	}

unlock:
	hal_nvic_enable_irq(USB_IRQn);

	return res;
}

int bl_usb_hid_put(uint8_t *data, uint32_t length, uint32_t *txlen)
{
	uint32_t timeout = (USB_WAIT_TX_READY_TIME / 2);
	// printk("bl_usb_hid_put data:%08X, length:%d\r\n", (uint32_t)data, length);
	if (bl_usb_is_tx_ready()) {
		return -EBUSY;
	}

	if (data == NULL) {
		*txlen = 0;
		return 0;
	}

	ctx->txbuf = data;
	ctx->txbuf_len = length;

	bl_usb_set_tx_ready();
	while (pmu_get_usb_plugin_status() && bl_usb_is_tx_ready() && timeout) {
		hal_gpt_delay_ms(2);
		timeout--;
	}

	if (!timeout) {
        printk("wait tx ready timeout\r\n");
    }

	/* Should be the same as length */
	*txlen = ctx->txlen;
	ctx->txlen = 0;

	return 0;
}

bool bl_usb_hid_is_configured(void)
{
	return configured;
}

#endif /* CONFIG_AIR_BL_USB_HID_DFU_ENABLE */
