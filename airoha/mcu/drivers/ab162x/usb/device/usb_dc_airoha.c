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

/**
 * @file usb_dc_airoha.c
 * @brief Airoha USB device controller shim driver for Airoha devices
 */

#include "usb_dc_airoha.h"

/* C Standard Includes */
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>
#include <zephyr/kernel.h>

/* Zephyr Includes */
#include <zephyr/device.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/drivers/usb/usb_dc.h>
#include <zephyr/init.h>
#include <zephyr/irq.h>
#include <zephyr/sys/printk.h>
#include <zephyr/dt-bindings/usb/usb.h>

/* HAL Includes */
#include "hal_dvfs.h"
#include "hal_dvfs_internal.h"
#include "hal_usb.h"
#include "hal_usb_internal.h"
#include "hal_gpt.h"
#include "hal_pmu.h"
#include "hal_nvic.h"
#include "hal_spm.h"

/* Logging Config */
#if defined(CONFIG_LOG)
#include <zephyr/logging/log.h>
// #define LOG_LEVEL LOG_LEVEL_ERR
#define LOG_LEVEL CONFIG_USB_DRIVER_LOG_LEVEL
LOG_MODULE_REGISTER(usb_dc_air);
#else
/* Temp logging method, backup for no log module environment. */
#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>
#define file_tag "usb_dc_airoha"
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

#define DT_DRV_COMPAT airoha_air_usbd
#define USB_MAXIMUM_SPEED DT_INST_ENUM_IDX_OR(0, maximum_speed, 1)

#define USB_TEST_MODE_J            0x01
#define USB_TEST_MODE_K            0x02
#define USB_TEST_MODE_SE0_NAK      0x03
#define USB_TEST_MODE_PACKET       0x04
#define USB_TEST_MODE_FORCE_ENABLE 0x05

#define USB_DC_AIROHA_SUPPORT_VBUS_DETECT
// #define USB_DBG_GPIO
/**************************************************************************************************
 * Airoha USB device controller driver
 *************************************************************************************************/

typedef enum {
	USB_EP0_IDLE = 0,
	USB_EP0_RX,
	USB_EP0_TX,
	USB_EP0_RX_STATUS
} USB_EP0_STATE;

/* usb standard command structure */
typedef struct __packed {
	uint8_t bmRequestType;
	uint8_t bRequest;
	uint16_t wValue;
	uint16_t wIndex;
	uint16_t wLength;
} usb_setup_cmd_t;

/**
 * @brief USB endpoint state structure.
 */
typedef struct {
	usb_dc_ep_callback cb;                /** Endpoint callback function */
	enum usb_dc_ep_transfer_type ep_type; /** Endpoint transfer type */
	uint8_t addr;                         /** Endpoint address */
	uint16_t mps;                         /** Endpoint max packet size */
} air_ep_ctx_t;

/**
 * @brief USB device controller driver structure.
 */
typedef struct {
	usb_dc_status_callback status_cb;
	USB_EP0_STATE ep0_state;
	uint32_t data_processed;
	bool setup_received;
	bool prev_attached;
	bool attached;
	bool vbus_ready;  /* This bit indicates whether the VBUS is ready or not. */
	bool enabled;     /* This bit indicates whether the USB IP is pull up D+ or not. */
	bool dvfs_locked; /* This bit indicates whether the USB Vcore is locked High or not. */
	usb_dc_plug_in_cb_t plug_in_cb;
	usb_dc_plug_out_cb_t plug_out_cb;
	air_ep_ctx_t epo_ctx[HAL_USB_MAX_NUMBER_ENDPOINT_RX + 1];
	air_ep_ctx_t epi_ctx[HAL_USB_MAX_NUMBER_ENDPOINT_TX + 1];
	usb_setup_cmd_t setup_cmd;
} air_usbd_ctx_t;

/**************************************************************************************************
 * Static Varaibles
 *************************************************************************************************/
static air_usbd_ctx_t usbd_ctx;

#if defined(USB_DC_AIROHA_SUPPORT_VBUS_DETECT)
static struct k_work vbus_detect_work;

#if CONFIG_USB_AIROHA_ATTACHED_EVENT_DELAY
static void vbus_detect_delay_hendler(struct k_timer *timer);
static K_TIMER_DEFINE(delay_timer, vbus_detect_delay_hendler, NULL);
#endif /* CONFIG_USB_AIROHA_ATTACHED_EVENT_DELAY */
#endif /* USB_DC_AIROHA_SUPPORT_VBUS_DETECT */

#if !defined(AIR_DOWNLOAD_AGENT) && !defined(CONFIG_MCUBOOT)
static int8_t usb_system_enable = -1;
static void usb_system_control(bool ctrl)
{
	uint32_t ret;

	if (ctrl == true)
	{
		if (usb_system_enable != 1)
		{
			hal_usb_lock_extslp();
			ret = spm_control_mtcmos(SPM_MTCMOS_PERISYS , SPM_MTCMOS_PWR_ENABLE);
			perisys_usb_sram_power_on();
			usb_system_enable = 1;
			LOG_INF("usb system power on, %u", ret);
		}
		else
		{
			LOG_INF("usb system has been power on");
		}
	}
	else
	{
		if (usb_system_enable != 0)
		{
			perisys_usb_sram_power_down();
			ret = spm_control_mtcmos(SPM_MTCMOS_PERISYS , SPM_MTCMOS_PWR_DISABLE);
			usb_system_enable = 0;
			hal_usb_unlock_extslp();
			LOG_INF("usb system power off, %u", ret);
		}
		else
		{
			LOG_INF("usb system has been power off");
		}
	}
}
#endif /* !defined(AIR_DOWNLOAD_AGENT) && !defined(CONFIG_MCUBOOT) */

/**************************************************************************************************
 * Helper Functions
 *************************************************************************************************/
#if defined(USB_DBG_GPIO)
#include "hal_gpio.h"
#define GPIO_USB_STATE_START HAL_GPIO_36
#define GPIO_USB_STATE HAL_GPIO_37
static void hal_usb_dbg_io_init(void)
{
    hal_gpio_init(GPIO_USB_STATE_START);
    hal_pinmux_set_function(GPIO_USB_STATE_START, 0);
    hal_gpio_set_direction(GPIO_USB_STATE_START, HAL_GPIO_DIRECTION_OUTPUT);
    hal_gpio_set_output(GPIO_USB_STATE_START, HAL_GPIO_DATA_LOW);
    hal_gpio_init(GPIO_USB_STATE);
    hal_pinmux_set_function(GPIO_USB_STATE, 0);
    hal_gpio_set_direction(GPIO_USB_STATE, HAL_GPIO_DIRECTION_OUTPUT);
    hal_gpio_set_output(GPIO_USB_STATE, HAL_GPIO_DATA_LOW);
}

static void hal_usb_state_gpio(hal_gpio_pin_t gpio_pin, uint8_t times)
{
	uint8_t i;

	for (i = 0; i < times; i++) {
		hal_gpio_set_output(gpio_pin, HAL_GPIO_DATA_HIGH);
		hal_gpio_set_output(gpio_pin, HAL_GPIO_DATA_LOW);
	}
}
#endif /* USB_DBG_GPIO */

static inline air_usbd_ctx_t *get_usbd_ctx(void)
{
	return &usbd_ctx;
}

static inline air_ep_ctx_t *get_ep_ctx(uint8_t ep_addr)
{
	air_ep_ctx_t *ctx = NULL;
	uint8_t idx = USB_EP_GET_IDX(ep_addr);
	uint8_t dir = USB_EP_GET_DIR(ep_addr);

	if (idx <= HAL_USB_MAX_NUMBER_ENDPOINT_TX && dir == USB_EP_DIR_IN) {
		ctx = &usbd_ctx.epi_ctx[idx];
	} else if (idx <= HAL_USB_MAX_NUMBER_ENDPOINT_RX && dir == USB_EP_DIR_OUT) {
		ctx = &usbd_ctx.epo_ctx[idx];
	}

	return ctx;
}

static void usb_dvfs_lock(bool lock)
{
	air_usbd_ctx_t *ctx = get_usbd_ctx();
	hal_dvfs_vcore_t target;

	LOG_INF("usb_dvfs_lock lock:%d->%d", ctx->dvfs_locked, lock);

	if (lock == true && ctx->dvfs_locked == true) {
		/* already locked, do-nothing */
	} else if (lock == true && ctx->dvfs_locked == false) {
		hal_dvfs_lock_control(HAL_DVS_VCORE_HIGH, HAL_DVFS_LOCK);
		ctx->dvfs_locked = true;
	} else if (lock == false && ctx->dvfs_locked == true) {
		hal_dvfs_lock_control(HAL_DVS_VCORE_HIGH, HAL_DVFS_UNLOCK);
		ctx->dvfs_locked = false;
	} else if (lock == false && ctx->dvfs_locked == false) {
		/* already unlocked, do-nothing */
	}

	if (lock) {
		target = HAL_DVFS_VCORE_HIGH;
	} else {
		target = HAL_DVFS_VCORE_MID;
	}

#if !defined(AIR_BL_USB_HID_DFU_ENABLE)
	/* Only wait when DVFS switch to high vcore */
	if (target == HAL_DVFS_VCORE_HIGH) {
		while (hal_dvfs_get_cur_vcore() != target) {
			/* TODO: timeout */
			;
		}
	}
#endif
}

/**************************************************************************************************
 * Zephyr USB device controller API implementation
 *************************************************************************************************/

int usb_dc_attach(void)
{
	air_usbd_ctx_t *ctx = get_usbd_ctx();
	if (ctx->vbus_ready == false) {
		LOG_ERR("airoha usb ip need vbus ready to work.");
		return -ENOTCONN;
	}

	if (ctx->enabled == true) {
		return 0;
	}

#if !defined(AIR_DOWNLOAD_AGENT) && !defined(CONFIG_MCUBOOT)
	/* normal pulgin case */
	usb_system_control(true);
#endif /* !defined(AIR_DOWNLOAD_AGENT) && !defined(CONFIG_MCUBOOT) */
	usb_dvfs_lock(true);

	hal_usb_reset_fifo();
	hal_usb_init();

#ifdef CONFIG_USB_DEVICE_SOF
	hal_usb_enable_driver_intr(HAL_USB_DRV_HDLR_SOF, 0, 1);
#endif
	// TODO: MUTEX Protect

	ctx->ep0_state = USB_EP0_IDLE;
	ctx->enabled = true;
	if (ctx->enabled && ctx->status_cb) {
		ctx->status_cb(USB_DC_CONNECTED, NULL);
	}

	hal_usb_pull_up_dp_line();
	return 0;
}

int usb_dc_detach(void)
{
	air_usbd_ctx_t *ctx = get_usbd_ctx();

	// TODO: MUTEX Protect
	hal_usb_deinit();
	ctx->enabled = false;
	usb_dvfs_lock(false);
#if !defined(AIR_DOWNLOAD_AGENT) && !defined(CONFIG_MCUBOOT)
	/* normal pulgout case */
	usb_system_control(false);
#endif /* !defined(AIR_DOWNLOAD_AGENT) && !defined(CONFIG_MCUBOOT) */
	return 0;
}

int usb_dc_reset(void)
{
	LOG_DBG("");
	hal_usb_deinit();
	hal_usb_reset_fifo();
	hal_usb_init();
	hal_usb_pull_up_dp_line();
	return 0;
}

int usb_dc_set_address(const uint8_t addr)
{
	/**
	 * Airoha USB Controller must set address in status stage in transfer.
	 * Ingore the function call.
	 */
	LOG_DBG("addr:%d", addr);
	return 0;
}

void usb_dc_set_status_callback(const usb_dc_status_callback cb)
{
	LOG_DBG("cb:%p", cb);
	air_usbd_ctx_t *ctx = get_usbd_ctx();

	if (ctx) {
		ctx->status_cb = cb;
	}
}

int usb_dc_ep_check_cap(const struct usb_dc_ep_cfg_data *const cfg)
{
	uint8_t ep = USB_EP_GET_IDX(cfg->ep_addr);
	uint8_t dir = USB_EP_GET_DIR(cfg->ep_addr);
	int ret = 0;

	LOG_DBG("ep %x, mps %d, type %d", cfg->ep_addr, cfg->ep_mps, cfg->ep_type);

	if ((cfg->ep_type == USB_DC_EP_CONTROL) && (ep != 0)) {
		ret = -EINVAL;
	} else if ((dir == USB_EP_DIR_IN) && (ep > HAL_USB_MAX_NUMBER_ENDPOINT_TX)) {
		ret = -EINVAL;
	} else if ((dir == USB_EP_DIR_OUT) && (ep > HAL_USB_MAX_NUMBER_ENDPOINT_RX)) {
		ret = -EINVAL;
	}

	return ret;
}

int usb_dc_ep_configure(const struct usb_dc_ep_cfg_data *const cfg)
{
	uint8_t idx = USB_EP_GET_IDX(cfg->ep_addr);
	uint8_t dir = USB_EP_GET_DIR(cfg->ep_addr);
	air_ep_ctx_t *ep_ctx = get_ep_ctx(cfg->ep_addr);

	LOG_DBG("ep_idx:%d, dir:%d, type:%d, mps:%d", idx, dir, cfg->ep_type, cfg->ep_mps);

	if (!ep_ctx) {
		LOG_ERR("cfg is illegal, addr:0x%02x, type:%d, mps:%d", cfg->ep_addr, cfg->ep_type,
			cfg->ep_mps);
		return -EINVAL;
	}

	ep_ctx->mps = cfg->ep_mps;
	ep_ctx->addr = cfg->ep_addr;
	ep_ctx->ep_type = cfg->ep_type;

	if (idx == 0x00) {
		/* Endpoint 0 */
	} else if (idx && dir == USB_EP_DIR_IN) {
		hal_usb_configure_tx_endpoint_type(idx, cfg->ep_type, false);
		hal_usb_init_tx_endpoint(idx, cfg->ep_mps, cfg->ep_type, false);
	} else if (idx && dir == USB_EP_DIR_OUT) {
		hal_usb_configure_rx_endpoint_type(idx, cfg->ep_type, false);
		hal_usb_init_rx_endpoint(idx, cfg->ep_mps, cfg->ep_type, false);
	}

	/* TODO: QMA handle */

	return 0;
}

int usb_dc_ep_set_stall(const uint8_t ep)
{
	LOG_DBG("ep:%d", ep);

	/* TODO: Check attached. */
	/* TODO: Check endpoint num. */

	uint8_t idx = USB_EP_GET_IDX(ep);
	uint8_t dir = USB_EP_DIR_IS_IN(ep) ? HAL_USB_EP_DIRECTION_TX : HAL_USB_EP_DIRECTION_RX;

	if (idx == 0) {
		hal_usb_update_endpoint_0_state(HAL_USB_EP0_DRV_STATE_NO_UPDATE, true, false);
	} else if (idx) {
		hal_usb_set_endpoint_stall(idx, dir, true);
	}
	return 0;
}

int usb_dc_ep_clear_stall(const uint8_t ep)
{
	LOG_DBG("ep:%d", ep);

	/* TODO: Check attached. */
	/* TODO: Check endpoint num. */

	uint8_t idx = USB_EP_GET_IDX(ep);
	uint8_t dir = USB_EP_DIR_IS_IN(ep) ? HAL_USB_EP_DIRECTION_TX : HAL_USB_EP_DIRECTION_RX;

	if (idx == 0) {
		/* EP0 would auto clear stall in ep0 intr (usb_ep0_routine) */
	} else if (idx) {
		hal_usb_set_endpoint_stall(idx, dir, false);
		/* TODO: Reset data toggle. */
	}

	return 0;
}

int usb_dc_ep_is_stalled(const uint8_t ep, uint8_t *const stalled)
{
	LOG_DBG("ep:%d, stalled:%d", ep, *stalled);

	/* TODO: Check attached. */
	/* TODO: Check endpoint num. */

	uint8_t idx = USB_EP_GET_IDX(ep);
	uint8_t dir = USB_EP_DIR_IS_IN(ep) ? HAL_USB_EP_DIRECTION_TX : HAL_USB_EP_DIRECTION_RX;

	if (idx == 0) {
		bool b_transaction_end;
		bool b_sent_stall;
		hal_usb_get_endpoint_0_status(&b_transaction_end, &b_sent_stall);
		*stalled = b_sent_stall;
	} else if (idx) {
		*stalled = hal_usb_get_endpoint_stall_status(idx, dir);
	}

	return 0;
}

int usb_dc_ep_halt(const uint8_t ep)
{
	return usb_dc_ep_set_stall(ep);
}

int usb_dc_ep_enable(const uint8_t ep)
{
	LOG_DBG("ep:%d", ep);

	/* TODO: Check attached. */
	/* TODO: Check endpoint num. */
	/* TODO: Check enable state. */

	uint8_t idx = USB_EP_GET_IDX(ep);
	uint8_t dir = USB_EP_DIR_IS_IN(ep) ? HAL_USB_EP_DIRECTION_TX : HAL_USB_EP_DIRECTION_RX;
	air_ep_ctx_t *ep_ctx = get_ep_ctx(ep);

	if (!ep_ctx) {
		return -EINVAL;
	}

	if (idx == 0) {
		hal_usb_enable_endpoint0();
	} else if (idx && dir == HAL_USB_EP_DIRECTION_TX) {
		hal_usb_enable_tx_endpoint(idx, ep_ctx->ep_type, HAL_USB_EP_USE_NO_DMA, true);
	} else if (idx && dir == HAL_USB_EP_DIRECTION_RX) {
		hal_usb_enable_rx_endpoint(idx, ep_ctx->ep_type, HAL_USB_EP_USE_NO_DMA, true);
	}

	return 0;
}

int usb_dc_ep_disable(const uint8_t ep)
{
	LOG_DBG("ep:%d", ep);

	/* TODO: Check attached. */
	/* TODO: Check endpoint num. */
	/* TODO: Check enable state. */

	uint8_t idx = USB_EP_GET_IDX(ep);
	uint8_t dir = USB_EP_DIR_IS_IN(ep) ? HAL_USB_EP_DIRECTION_TX : HAL_USB_EP_DIRECTION_RX;
	air_ep_ctx_t *ep_ctx = get_ep_ctx(ep);

	if (!ep_ctx) {
		return -EINVAL;
	}

	if (idx == 0) {
		hal_usb_disable_endpoint0();
	} else if (idx && dir == HAL_USB_EP_DIRECTION_TX) {
		hal_usb_disable_tx_endpoint(idx);
	} else if (idx && dir == HAL_USB_EP_DIRECTION_RX) {
		hal_usb_disable_rx_endpoint(idx);
	}

	return 0;
}

ATTR_TEXT_IN_TCM int usb_dc_ep_flush(const uint8_t ep)
{
	LOG_DBG("ep:%d", ep);

	/* TODO: Check attached. */
	/* TODO: Check endpoint num. */
	/* TODO: Check enable state. */

	uint8_t idx = USB_EP_GET_IDX(ep);
	uint8_t dir = USB_EP_DIR_IS_IN(ep) ? HAL_USB_EP_DIRECTION_TX : HAL_USB_EP_DIRECTION_RX;
	air_ep_ctx_t *ep_ctx = get_ep_ctx(ep);

	if (!ep_ctx) {
		return -EINVAL;
	}

	if (idx == 0) {
		hal_usb_clear_endpoint0_fifo();
	} else if (idx && dir == HAL_USB_EP_DIRECTION_TX) {
		hal_usb_clear_tx_endpoint_fifo(idx, ep_ctx->ep_type, true);
	} else if (idx && dir == HAL_USB_EP_DIRECTION_RX) {
		hal_usb_clear_rx_endpoint_fifo(idx, ep_ctx->ep_type, true);
	}

	return 0;
}

int usb_dc_ep_write(const uint8_t ep, const uint8_t *const data, const uint32_t data_len,
		    uint32_t *const ret_bytes)
{
	air_usbd_ctx_t *usbd_ctx = get_usbd_ctx();
	air_ep_ctx_t *ep_ctx = get_ep_ctx(ep);
	hal_usb_status_t ret = HAL_USB_STATUS_OK;
	bool end;

	if (!ep_ctx) {
		return -EINVAL;
	}

	/* Check Attached */
	/* Check Suspend */
	/* Check Configured */

	uint16_t txlen = data_len;
	if (txlen > ep_ctx->mps) {
		txlen = ep_ctx->mps;
	}
	end = (txlen == data_len);
	LOG_DBG("ep 0x%02x, data_len:%d, txlen:%d, end:%d", ep, data_len, txlen, end);

	if (ep == USB_CONTROL_EP_IN) {
		bool end = (txlen == data_len);
		if (txlen) {
			bool ep0_tx_packet_ready = hal_usb_check_ep0_tx_packet_ready();

			if (ep0_tx_packet_ready) {
				LOG_INF("error, usb ep0 tx packet ready is set, retry!");
				txlen = 0;
				goto tx_fail;
			}
			ret = hal_usb_write_endpoint_fifo(0, txlen, (void *)data);
			hal_usb_update_endpoint_0_state(HAL_USB_EP0_DRV_STATE_WRITE_RDY, false,
							end ? (txlen != ep_ctx->mps) : false);
			if (end && (txlen != ep_ctx->mps)) {
#if defined(USB_DBG_GPIO)
				hal_usb_state_gpio(GPIO_USB_STATE_START, 1);
				hal_usb_state_gpio(GPIO_USB_STATE, 1);
#endif
				usbd_ctx->ep0_state = USB_EP0_IDLE;
			} else {
tx_fail:
#if defined(USB_DBG_GPIO)
				hal_usb_state_gpio(GPIO_USB_STATE_START, 1);
				hal_usb_state_gpio(GPIO_USB_STATE, 2);
#endif
				usbd_ctx->ep0_state = USB_EP0_TX;
			}
		} else {
			if (usbd_ctx->ep0_state == USB_EP0_IDLE) {
				/* DataEnd is already sent, do nothing */
				if (!data) { // zephyr send status to host, but hardware must not enter write ready state at this point. Only ZLP enter write ready state.
					hal_usb_update_endpoint_0_state(HAL_USB_EP0_DRV_STATE_WRITE_RDY,
									false, end);
				}
			} else if (usbd_ctx->ep0_state == USB_EP0_RX_STATUS) {
				hal_usb_update_endpoint_0_state(HAL_USB_EP0_DRV_STATE_READ_END,
								false, end);
			} else {
				hal_usb_update_endpoint_0_state(HAL_USB_EP0_DRV_STATE_NO_UPDATE,
								false, end);
				if (end) {
#if defined(USB_DBG_GPIO)
				hal_usb_state_gpio(GPIO_USB_STATE_START, 1);
				hal_usb_state_gpio(GPIO_USB_STATE, 1);
#endif
					usbd_ctx->ep0_state = USB_EP0_IDLE;
				}
			}
		}
	} else {
		if (txlen) {
			ret = hal_usb_write_endpoint_fifo(USB_EP_GET_IDX(ep), txlen, (void *)data);
		}
		hal_usb_set_endpoint_tx_ready_toggle(USB_EP_GET_IDX(ep));
	}

	if (ret != HAL_USB_STATUS_OK) {
		LOG_DBG("ret != HAL_USB_STATUS_OK");
		return -EIO;
	}

	if (ret_bytes) {
		*ret_bytes = txlen;
	}

	return 0;
}

int usb_dc_ep_read(const uint8_t ep, uint8_t *const data, const uint32_t max_data_len,
		   uint32_t *const read_bytes)
{
	LOG_DBG("ep 0x%02x, maxlen %d", ep, max_data_len);
	int ret;

	ret = usb_dc_ep_read_wait(ep, data, max_data_len, read_bytes);
	if (ret) {
		return ret;
	}

	if (!data && !max_data_len) {
		return ret;
	}

	ret = usb_dc_ep_read_continue(ep);
	return ret;
}

int usb_dc_ep_set_callback(const uint8_t ep, const usb_dc_ep_callback cb)
{
	air_ep_ctx_t *ep_ctx = get_ep_ctx(ep);
	LOG_DBG("ep:%d, cb:%p", ep, cb);
	if (!ep_ctx) {
		return -EINVAL;
	}
	ep_ctx->cb = cb;
	return 0;
}

int usb_dc_ep_read_wait(uint8_t ep, uint8_t *data, uint32_t max_data_len, uint32_t *read_bytes)
{
	LOG_DBG("ep:%d, len:%d", ep, max_data_len);
	air_usbd_ctx_t *ctx = get_usbd_ctx();

	if (!USB_EP_DIR_IS_OUT(ep)) {
		return -EINVAL;
	}

	if (USB_EP_GET_IDX(ep) > HAL_USB_MAX_NUMBER_ENDPOINT_RX) {
		return -EINVAL;
	}

	if ((!data) || (!max_data_len)) {
		return -EINVAL;
	}

	/* Check Attached */
	/* Check Suspend */
	/* Check Configured */

	if (ep == USB_CONTROL_EP_OUT) {
		if (ctx->setup_received) {
			ctx->setup_received = false;
			memcpy(data, &ctx->setup_cmd, sizeof(usb_setup_cmd_t));
			if (read_bytes) {
				*read_bytes = sizeof(usb_setup_cmd_t);
			}

			// LOG_HEXDUMP_DBG(data, sizeof(usb_setup_cmd_t), "setup");
		} else {
			uint8_t nCount = hal_usb_ep0_pkt_len();
			uint8_t end;
			hal_usb_read_endpoint_fifo(0, nCount, data);

			if (read_bytes) {
				*read_bytes = nCount;
			}

			ctx->data_processed += nCount;
			if (ctx->data_processed == ctx->setup_cmd.wLength) {
#if defined(USB_DBG_GPIO)
				hal_usb_state_gpio(GPIO_USB_STATE_START, 1);
				hal_usb_state_gpio(GPIO_USB_STATE, 1);
#endif
				end = 1;
				ctx->ep0_state = USB_EP0_IDLE;
			} else {
#if defined(USB_DBG_GPIO)
				hal_usb_state_gpio(GPIO_USB_STATE_START, 1);
				hal_usb_state_gpio(GPIO_USB_STATE, 3);
#endif
				end = 0;
				ctx->ep0_state = USB_EP0_RX;
			}
			hal_usb_update_endpoint_0_state(HAL_USB_EP0_DRV_STATE_READ_END, false, end);

			// LOG_HEXDUMP_DBG(data, max_data_len, "ep0_rxdata");
		}

	} else {
		/* Read data from endpoint FIFO */
		uint8_t idx = USB_EP_GET_IDX(ep);
		uint32_t len = hal_usb_get_rx_packet_length(idx);
		uint32_t actual_read_bytes = MIN(len, max_data_len);
		if (read_bytes) {
			*read_bytes = actual_read_bytes;
		}
		hal_usb_read_endpoint_fifo(idx, actual_read_bytes, data);
		hal_usb_set_endpoint_rx_ready(idx);
	}

	return 0;
}

int usb_dc_ep_read_continue(uint8_t ep)
{
	LOG_DBG("ep:%d", ep);

	if (!USB_EP_DIR_IS_OUT(ep)) {
		return -EINVAL;
	}

	if (USB_EP_GET_IDX(ep) > HAL_USB_MAX_NUMBER_ENDPOINT_RX) {
		return -EINVAL;
	}

	return 0;
}

int usb_dc_ep_mps(uint8_t ep)
{
	air_ep_ctx_t *ep_ctx = get_ep_ctx(ep);

	if (!ep_ctx) {
		return -EINVAL;
	}

	return ep_ctx->mps;
}

int usb_dc_wakeup_request(void)
{
	hal_usb_rmwk_trigger();
	/* usb remote wakup, resume should pull 1 ~ 15 ms */
	k_sleep(K_USEC(CONFIG_USB_AIROHA_REMOTE_WAKEUP_DRV_TIME_US));
	hal_usb_rmwk_clear();
	return 0;
}

/******************************************************************************
 * Airoha Vbus Detect Function
 *****************************************************************************/
#if defined(USB_DC_AIROHA_SUPPORT_VBUS_DETECT)
static void usb_vbus_detect_handler(struct k_work *work);

#if CONFIG_USB_AIROHA_ATTACHED_EVENT_DELAY
static void vbus_detect_delay_hendler(struct k_timer *timer)
{
	LOG_DBG("vbus_detect_delay_hendler done");
#if !defined(CONFIG_MCUBOOT)
	k_work_submit(&vbus_detect_work);
#else
	usb_vbus_detect_handler(&vbus_detect_work);
#endif
}
#endif

/**
 * @brief USB plug in callback
 * This function execute in pmu isr context.
 */
void usb_plugin_cb(void)
{
	LOG_INF("usb_plugin_cb");
	air_usbd_ctx_t *usbd_ctx = get_usbd_ctx();
	uint32_t irq_mask = 0;
	hal_nvic_save_and_set_interrupt_mask(&irq_mask);
	usbd_ctx->attached = true;
	hal_nvic_restore_interrupt_mask(irq_mask);

#if !CONFIG_USB_AIROHA_ATTACHED_EVENT_DELAY
#if !defined(CONFIG_MCUBOOT)
	k_work_submit(&vbus_detect_work); /* Submit to system work queue */
#else
	usb_vbus_detect_handler(&vbus_detect_work);
#endif
#else
	uint32_t remaining = k_timer_remaining_get(&delay_timer);
	if (remaining > 0) {
		k_timer_stop(&delay_timer);
	}
	LOG_INF("usb_plugin_cb start a delay timer(%u ms), previous remaining time: %u ms",
		CONFIG_USB_AIROHA_ATTACHED_EVENT_DELAY, remaining);
	k_timer_start(&delay_timer, K_MSEC(CONFIG_USB_AIROHA_ATTACHED_EVENT_DELAY), K_NO_WAIT);
#endif
}

/**
 * @brief USB plug out callback
 * This function execute in pmu isr context.
 */
void usb_plugout_cb(void)
{
	LOG_INF("usb_plugout_cb");
	air_usbd_ctx_t *usbd_ctx = get_usbd_ctx();
	uint32_t irq_mask = 0;
	hal_nvic_save_and_set_interrupt_mask(&irq_mask);
	usbd_ctx->attached = false;
	hal_nvic_restore_interrupt_mask(irq_mask);
#if !defined(CONFIG_MCUBOOT)
	k_work_submit(&vbus_detect_work); /* Submit to system work queue */
#else
	usb_vbus_detect_handler(&vbus_detect_work);
#endif
}

static void usb_vbus_detect_handler(struct k_work *work)
{
	air_usbd_ctx_t *ctx = get_usbd_ctx();
	uint32_t irq_mask;
	bool prev;
	bool curr;
	bool plug_in_detected = false;
	bool plug_out_detected = false;

	hal_nvic_save_and_set_interrupt_mask(&irq_mask);
	prev = ctx->prev_attached;
	curr = ctx->attached;

	if (prev == false && curr == false) {
		/* Do-Nothing */
	}
	if (prev == false && curr == true) {
		/* Plug In */
		ctx->vbus_ready = true;
		plug_in_detected = true;
	}
	if (prev == true && curr == false) {
		/* Plug Out */
		ctx->vbus_ready = false;
		plug_out_detected = true;
	}
	if (prev == true && curr == true) {
		/* Do-Nothing */
	}
	ctx->prev_attached = curr;
	hal_nvic_restore_interrupt_mask(irq_mask);

	LOG_INF("usb_vbus_detect_handler vbus:%d->%d", prev, curr);
	if (plug_in_detected && ctx->plug_in_cb) {
		if (ctx->enabled && ctx->status_cb) {
			ctx->status_cb(USB_DC_CONNECTED, NULL);
		}
		ctx->plug_in_cb();
	}
	if (plug_out_detected && ctx->plug_out_cb) {
		if (ctx->enabled && ctx->status_cb) {
			ctx->status_cb(USB_DC_DISCONNECTED, NULL);
		}
		ctx->plug_out_cb();
	}
}

static int usb_dc_vbus_detect_init(void)
{
	LOG_INF("usb_vbus_detect_init");
	pmu_register_callback(PMU_CB_USB_PLUGIN, (pmu_callback_t)usb_plugin_cb, PMU_USER_USB);
	pmu_register_callback(PMU_CB_USB_PLUGOUT, (pmu_callback_t)usb_plugout_cb,
			      PMU_USER_USB);
	k_work_init(&vbus_detect_work, usb_vbus_detect_handler);

	uint16_t vbus_status = pmu_get_usb_plugin_status();

	LOG_INF("usb_dc_vbus_detect_init vbus:%d", vbus_status);
	if (vbus_status) {
		usb_plugin_cb();
	} else {
		usb_plugout_cb();
	}
	return 0;
}
#endif /* USB_DC_AIROHA_SUPPORT_VBUS_DETECT */

/******************************************************************************
 * Airoha Custom Expose functions
 *****************************************************************************/

int usb_dc_register_plug_in_cb(usb_dc_plug_in_cb_t cb)
{
	air_usbd_ctx_t *ctx = get_usbd_ctx();
	ctx->plug_in_cb = cb;
	return 0;
}

int usb_dc_register_plug_out_cb(usb_dc_plug_in_cb_t cb)
{
	air_usbd_ctx_t *ctx = get_usbd_ctx();
	ctx->plug_out_cb = cb;
	return 0;
}

bool usb_dc_is_vbus_ready(void)
{
	return get_usbd_ctx()->vbus_ready;
}

int usb_dc_set_speed(usb_dc_speed_t speed)
{
	switch (speed) {
	case USB_DC_SPPED_LOW_SPEED: {
		LOG_ERR("[USB_DC_AIR] USB not support low speed");
		return -ENOTSUP;
	}
	case DT_USB_MAXIMUM_SPEED_FULL_SPEED: {
		hal_usb_set_speed(0);
		return 0;
	}
	case DT_USB_MAXIMUM_SPEED_HIGH_SPEED: {
		hal_usb_set_speed(1);
		return 0;
	}
	case DT_USB_MAXIMUM_SPEED_SUPER_SPEED: {
		LOG_ERR("[USB_DC_AIR] USB not support super speed");
		return -ENOTSUP;
	}
	default: {
		LOG_ERR("[USB_DC_AIR] USB unsupport speed:%d", speed);
		return -EINVAL;
	}
	}
}

/******************************************************************************
 * Airoha Custom Rqquest function
 *****************************************************************************/

/**
 * @brief Handle request witch usb_dc not handle.
 *
 * @return int
 * @retval 1 request is handled by airoha driver.
 * @retval 0 request is not handled, should pass to usb_dc subsys.
 */
static int usb_handle_custom_request_in_idle(void)
{
	air_usbd_ctx_t *usbd_ctx = get_usbd_ctx();
	usb_setup_cmd_t *setup;

	setup = &(usbd_ctx->setup_cmd);

	/* Handle test mode request, due to usb_dc is not handle */
	if (setup->bRequest == USB_SREQ_SET_FEATURE && setup->wValue == USB_SFS_TEST_MODE) {
		LOG_INF("Receive TestMode Request");
		hal_usb_update_endpoint_0_state(HAL_USB_EP0_DRV_STATE_READ_END, false, true);
		return 1;
	}
	return 0;
}

/**
 * @brief Handle request witch usb_dc not handle.
 *
 * @return int
 * @retval 1 request is handled by airoha driver.
 * @retval 0 request is not handled, should pass to usb_dc subsys.
 */
static int usb_handle_custom_request_in_rx_status(void)
{
	air_usbd_ctx_t *usbd_ctx = get_usbd_ctx();
	usb_setup_cmd_t *setup;

	setup = &(usbd_ctx->setup_cmd);

	/* Handle test mode request, due to usb_dc is not handle */
	if (setup->bRequest == USB_SREQ_SET_FEATURE && setup->wValue == USB_SFS_TEST_MODE) {
		uint8_t mode = (setup->wIndex >> 8);
		LOG_INF("Enter test mode:%d", mode);
		if (mode == USB_TEST_MODE_J) {
			hal_usb_enter_test_mode(HAL_USB_TEST_MODE_TYPE_J);
		} else if (mode == USB_TEST_MODE_K) {
			hal_usb_enter_test_mode(HAL_USB_TEST_MODE_TYPE_K);
		} else if (mode == USB_TEST_MODE_SE0_NAK) {
			hal_usb_enter_test_mode(HAL_USB_TEST_MODE_TYPE_SE0_NAK);
		} else if (mode == USB_TEST_MODE_PACKET) {
			hal_usb_enter_test_mode(HAL_USB_TEST_MODE_TYPE_PACKET);
		}
		return 1;
	}
	return 0;
}

/******************************************************************************
 * SYS_INIT function
 *****************************************************************************/

static void usb_reset_routine(void)
{
	LOG_DBG("");
	air_usbd_ctx_t *ctx = get_usbd_ctx();
	if (ctx->status_cb) {
		ctx->status_cb(USB_DC_RESET, NULL);
	}
}

static void usb_suspend_routine(void)
{
	LOG_DBG("");
	air_usbd_ctx_t *ctx = get_usbd_ctx();
	if (ctx->status_cb) {
		ctx->status_cb(USB_DC_SUSPEND, NULL);
	}
}

static void usb_resume_routine(void)
{
	LOG_DBG("");
	air_usbd_ctx_t *ctx = get_usbd_ctx();
	if (ctx->status_cb) {
		ctx->status_cb(USB_DC_RESUME, NULL);
	}
}

static void usb_sof_routine(void)
{
	air_usbd_ctx_t *ctx = get_usbd_ctx();
	if (ctx->status_cb) {
		ctx->status_cb(USB_DC_SOF, NULL);
	}
}

/* Check the USB HW fifo data length for EP0*/
#if 0
bool USB_Check_EP0_DataLen(uint32_t ep_num, uint32_t expected_byte)
{
    uint32_t byte;
    uint32_t dma_timeout_start, dma_timeout_end, dma_timeout_duration;

    /* Get EP0 data length */
    byte = hal_usb_ep0_pkt_len();

    /* If EP0 data length is not enough, then wait 1ms */
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &dma_timeout_start);

    while (byte < expected_byte) {
        /* Get EP0 data length */
        byte = hal_usb_ep0_pkt_len();

        /* Timeout 1ms*/
        hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &dma_timeout_end);
        dma_timeout_duration = dma_timeout_end - dma_timeout_start;

        if (dma_timeout_duration > USB_GPT_TIMEOUT_1ms) {
            LOG_DBG("USB_Check_EP0_DataLen byte:%d < expect_byte:%d wait to timeout: %d us", 3,
                        byte, expected_byte, USB_GPT_TIMEOUT_1ms);
            return false;
        } else {
            //USB_DBG_I(USB_DBG_EP0_DATALEN_WAIT, ...
            LOG_DBG("USB_Check_EP0_DataLen wait %d us to get enough data", 1, dma_timeout_duration);
        }
    }

    return true;
}
#endif

static void usb_ep0_routine(void)
{
	bool b_transaction_end;
	bool b_sent_stall;
	bool notify_usbdc = false;
	uint32_t nCount;
	air_usbd_ctx_t *usbd_ctx = get_usbd_ctx();
	air_ep_ctx_t *ep0_ctx = get_ep_ctx(0);

	// LOG_DBG("ep0_state %d", usbd_ctx->ep0_state);

	hal_usb_get_endpoint_0_status(&b_transaction_end, &b_sent_stall);

	if ((usbd_ctx == NULL) || (ep0_ctx == NULL)) {
		LOG_INF("Get usbd_ctx or ep0_ctx failed");
		return;
	}
	/* Check for SentStall */
	/* SentStall && SetupEnd are impossible to occur together*/
	if (b_sent_stall == true) {
		hal_usb_update_endpoint_0_state(HAL_USB_EP0_DRV_STATE_CLEAR_SENT_STALL, false,
						false);
		usbd_ctx->ep0_state = USB_EP0_IDLE;
		LOG_INF("b_sent_stall");
	}

	/* Check for SetupEnd */
	if (b_transaction_end == true) {
		hal_usb_update_endpoint_0_state(HAL_USB_EP0_DRV_STATE_TRANSACTION_END, false,
						false);
		usbd_ctx->ep0_state = USB_EP0_IDLE;
		LOG_INF("b_transaction_end");
	}

	if (usbd_ctx->ep0_state == USB_EP0_RX_STATUS) {
#if defined(USB_DBG_GPIO)
		hal_usb_state_gpio(GPIO_USB_STATE_START, 1);
		hal_usb_state_gpio(GPIO_USB_STATE, 1);
#endif
		usbd_ctx->ep0_state = USB_EP0_IDLE;
		if (usbd_ctx->setup_cmd.bRequest == USB_SREQ_SET_ADDRESS) {
			hal_usb_set_address(usbd_ctx->setup_cmd.wValue, HAL_USB_SET_ADDR_STATUS);
		}
		usb_handle_custom_request_in_rx_status();
	}

	/* Call relevant routines for endpoint 0 state */
	if (usbd_ctx->ep0_state == USB_EP0_IDLE) {
		nCount = hal_usb_ep0_pkt_len();

		if (nCount) {
#if 0
            /* Check EP0 data is enough */
            USB_Check_EP0_DataLen(0, 8);
#endif
			hal_usb_clear_ep0_interrupt();
			hal_usb_clear_ep0_queue_event();
			/* Read ep0 data - setup command*/
			hal_usb_read_endpoint_fifo(0, 8, &usbd_ctx->setup_cmd);
			usbd_ctx->setup_received = true;
			if (((struct usb_setup_packet *)&usbd_ctx->setup_cmd)->RequestType.type == USB_REQTYPE_TYPE_STANDARD) {
				LOG_INF("bmRequestType:%02X, %02X, %04X, %04X, %04X",
					usbd_ctx->setup_cmd.bmRequestType, usbd_ctx->setup_cmd.bRequest,
					usbd_ctx->setup_cmd.wValue, usbd_ctx->setup_cmd.wIndex,
					usbd_ctx->setup_cmd.wLength);
			}

			if (usbd_ctx->setup_cmd.wLength > 0) {
				hal_usb_update_endpoint_0_state(HAL_USB_EP0_DRV_STATE_READ_END,
								false, false);
				usbd_ctx->data_processed = 0;
			}

			if (usb_reqtype_is_to_device(
				    (const struct usb_setup_packet *)&usbd_ctx->setup_cmd) &&
			    usbd_ctx->setup_cmd.wLength == 0) {
				/* LOG_DBG("idle case 1"); */
				/* Host -> Device, wLength == 0 */
#if defined(USB_DBG_GPIO)
				hal_usb_state_gpio(GPIO_USB_STATE_START, 1);
				hal_usb_state_gpio(GPIO_USB_STATE, 4);
#endif
				usbd_ctx->ep0_state = USB_EP0_RX_STATUS;
			} else if (usb_reqtype_is_to_device(
					   (const struct usb_setup_packet *)&usbd_ctx->setup_cmd) &&
				   usbd_ctx->setup_cmd.wLength) {
				/* LOG_DBG("idle case 2"); */
				/* Host -> Device, wLength > 0 */
#if defined(USB_DBG_GPIO)
				hal_usb_state_gpio(GPIO_USB_STATE_START, 1);
				hal_usb_state_gpio(GPIO_USB_STATE, 3);
#endif
				usbd_ctx->ep0_state = USB_EP0_RX;
			} else if (usb_reqtype_is_to_host(
					   (const struct usb_setup_packet *)&usbd_ctx->setup_cmd) &&
				   usbd_ctx->setup_cmd.wLength == 0) {
				/* illegal request */
			} else if (usb_reqtype_is_to_host(
					   (const struct usb_setup_packet *)&usbd_ctx->setup_cmd) &&
				   usbd_ctx->setup_cmd.wLength) {
				/* LOG_DBG("idle case 3"); */
				/* Host <- Device, wLength > 0 */
#if defined(USB_DBG_GPIO)
				hal_usb_state_gpio(GPIO_USB_STATE_START, 1);
				hal_usb_state_gpio(GPIO_USB_STATE, 2);
#endif
				usbd_ctx->ep0_state = USB_EP0_TX;
			} else {
				LOG_ERR("idle case error");
			}

			if (usb_handle_custom_request_in_idle() == 0) {
				notify_usbdc = true;
			}
			if (notify_usbdc) {
				ep0_ctx->cb(USB_CONTROL_EP_OUT, USB_DC_EP_SETUP);
			}
		}
	} else if (usbd_ctx->ep0_state == USB_EP0_RX) {
		nCount = hal_usb_ep0_pkt_len();
		if (nCount > 0) {
			/* LOG_DBG("RX case"); */
			ep0_ctx->cb(USB_CONTROL_EP_OUT, USB_DC_EP_DATA_OUT);
		} else {
			LOG_INF("RX case, no data");
		}
	} else if (usbd_ctx->ep0_state == USB_EP0_TX) {
		/* LOG_DBG("TX case"); */
		/* Tx state handler */
#if defined(USB_DBG_GPIO)
				hal_usb_state_gpio(GPIO_USB_STATE_START, 1);
				hal_usb_state_gpio(GPIO_USB_STATE, 1);
#endif
		usbd_ctx->ep0_state = USB_EP0_IDLE;
		ep0_ctx->cb(USB_CONTROL_EP_IN, USB_DC_EP_DATA_IN);
	}
}

static void epi_cb(uint8_t ep)
{
	air_ep_ctx_t *ep_ctx = get_ep_ctx(ep);
	if (ep_ctx && ep_ctx->cb) {
		ep_ctx->cb(ep, USB_DC_EP_DATA_IN);
	} else {
		LOG_INF("Get ep_ctx failed or cb is NULL for ep: %d", ep);
	}
}

static void epo_cb(uint8_t ep)
{
	air_ep_ctx_t *ep_ctx = get_ep_ctx(ep);
	if (ep_ctx && ep_ctx->cb) {
		ep_ctx->cb(ep, USB_DC_EP_DATA_OUT);
	} else {
		LOG_INF("Get ep_ctx failed or cb is NULL for ep: %d", ep);
	}
}

static void epi_81_cb(void)
{
	epi_cb(0x81);
}
static void epi_82_cb(void)
{
	epi_cb(0x82);
}
static void epi_83_cb(void)
{
	epi_cb(0x83);
}
static void epi_84_cb(void)
{
	epi_cb(0x84);
}
static void epi_85_cb(void)
{
	epi_cb(0x85);
}
static void epi_86_cb(void)
{
	epi_cb(0x86);
}
static void epi_87_cb(void)
{
	epi_cb(0x87);
}
static void epi_88_cb(void)
{
	epi_cb(0x88);
}

static void epo_01_cb(void)
{
	epo_cb(0x01);
}
static void epo_02_cb(void)
{
	epo_cb(0x02);
}
static void epo_03_cb(void)
{
	epo_cb(0x03);
}
static void epo_04_cb(void)
{
	epo_cb(0x04);
}
static void epo_05_cb(void)
{
	epo_cb(0x05);
}
static void epo_06_cb(void)
{
	epo_cb(0x06);
}
static void epo_07_cb(void)
{
	epo_cb(0x07);
}
static void epo_08_cb(void)
{
	epo_cb(0x08);
}

hal_usb_driver_interrupt_handler_t epi_cbs[] = {
	epi_81_cb, epi_82_cb, epi_83_cb, epi_84_cb, epi_85_cb, epi_86_cb, epi_87_cb, epi_88_cb,
};

hal_usb_driver_interrupt_handler_t epo_cbs[] = {
	epo_01_cb, epo_02_cb, epo_03_cb, epo_04_cb, epo_05_cb, epo_06_cb, epo_07_cb, epo_08_cb,
};

#if 1
/**
 * @brief Initialize USB driver
 * @param dev not used.
 * @return 0 on success.
 *
 * This function is called by the system to initialize the USB driver.
 *
 * 1. Register functions to the HAL USB driver.
 */
#if KERNELVERSION >= ZEPHYR_VERSION(3, 7, 0)
static int usb_dc_airoha_init(void)
{
#else
static int usb_dc_airoha_init(const struct device *dev)
{
	ARG_UNUSED(dev);
#endif

	LOG_INF("USB_MAXIMUM_SPEED: %d", USB_MAXIMUM_SPEED);
	if (USB_MAXIMUM_SPEED == DT_USB_MAXIMUM_SPEED_HIGH_SPEED) {
		hal_usb_set_speed(1);
	} else if (USB_MAXIMUM_SPEED == DT_USB_MAXIMUM_SPEED_FULL_SPEED) {
		hal_usb_set_speed(0);
	} else {
		/**
		 * These 2 speeds are not supported.
		 * DT_USB_MAXIMUM_SPEED_LOW_SPEED
		 * DT_USB_MAXIMUM_SPEED_SUPER_SPEED
		 */
		assert(0 && "The maximum_speed of zephyr_udc0 is not supported");
	}

	/* Register reset and ep0 interrupt handler to driver info */
	hal_usb_register_driver_callback(HAL_USB_DRV_HDLR_RESET, 0, usb_reset_routine);
	hal_usb_register_driver_callback(HAL_USB_DRV_HDLR_EP0, 0, usb_ep0_routine);
	hal_usb_register_driver_callback(HAL_USB_DRV_HDLR_SUSPEND, 0, usb_suspend_routine);
	hal_usb_register_driver_callback(HAL_USB_DRV_HDLR_RESUME, 0, usb_resume_routine);
	hal_usb_register_driver_callback(HAL_USB_DRV_HDLR_SOF, 0, usb_sof_routine);

#if defined(USB_DBG_GPIO)
	hal_usb_dbg_io_init();
#endif

	for (uint8_t i = 0; i < HAL_USB_MAX_NUMBER_ENDPOINT_TX; i++) {
		hal_usb_register_driver_callback(HAL_USB_DRV_HDLR_EP_TX, i + 1, epi_cbs[i]);
	}

	for (uint8_t i = 0; i < HAL_USB_MAX_NUMBER_ENDPOINT_RX; i++) {
		hal_usb_register_driver_callback(HAL_USB_DRV_HDLR_EP_RX, i + 1, epo_cbs[i]);
	}

#if !defined(USB_DC_AIROHA_SUPPORT_VBUS_DETECT)
	/* if no VBUS detect support, assume vbus ready always */
	get_usbd_ctx()->vbus_ready = true;
#endif /* USB_DC_AIROHA_SUPPORT_VBUS_DETECT */

	return 0;
}

SYS_INIT(usb_dc_airoha_init, CONFIG_USB_INIT_LEVEL, CONFIG_USB_INIT_PRIORITY);
#endif

#if defined(USB_DC_AIROHA_SUPPORT_VBUS_DETECT)
/**
 * @brief Construct a new sys init object
 *
 * usb_dc_vbus_detect_init must init in POST_KERNEL stage.
 * Because the vbus detect function need to do something in task.
 */
SYS_INIT(usb_dc_vbus_detect_init, CONFIG_USB_VBUS_DETECT_INIT_LEVEL,
	 CONFIG_USB_VBUS_DETECT_INIT_PRIORITY);
#endif /* USB_DC_AIROHA_SUPPORT_VBUS_DETECT */
