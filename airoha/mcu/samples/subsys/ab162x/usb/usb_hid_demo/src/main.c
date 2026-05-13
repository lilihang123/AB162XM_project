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

#include <zephyr/kernel.h>
#include <zephyr/init.h>

#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/class/usb_hid.h>

#include "air_usb.h"
#include "air_usb_hid.h"

#include "hal_dvfs.h"
#include "hal_gpio.h"
#include "hal_gpt.h"
#include "hal_usb.h"
#include "hal_eint.h"
#include "hal_eint_internal.h"

#define USB_SOF_GPIO           HAL_GPIO_6
#define USB_SOF_GPIO_MODE_GPIO HAL_GPIO_6_GPIO6

#define USB_TX_GPIO           HAL_GPIO_19
#define USB_TX_GPIO_MODE_GPIO HAL_GPIO_19_GPIO19

#define USB_XXX_GPIO           HAL_GPIO_20
#define USB_XXX_GPIO_MODE_GPIO HAL_GPIO_20_GPIO20

#define USB_YYY_GPIO           HAL_GPIO_21
#define USB_YYY_GPIO_MODE_GPIO HAL_GPIO_21_GPIO21

/* Logging Config */
#if defined(CONFIG_LOG)
#include <zephyr/logging/log.h>
// #define LOG_LEVEL LOG_LEVEL_ERR
#define LOG_LEVEL CONFIG_USB_DRIVER_LOG_LEVEL
LOG_MODULE_REGISTER(usb_hid_demo);
#else
/* Temp logging method, backup for no log module environment. */
#include <zephyr/sys/printk.h>
#define file_tag "usb_hid_demo"
#undef LOG_ERR
#undef LOG_WRN
#undef LOG_INF
#undef LOG_DBG
#define LOG_ERR(...)                                                                               \
	do {                                                                                       \
		printk("<err> " file_tag ": %s: ", __func__);                                      \
		printk(__VA_ARGS__);                                                               \
		printk("\r\n");                                                                    \
	} while (0)
#define LOG_WRN(...)                                                                               \
	do {                                                                                       \
		printk("<wrn> " file_tag ": %s: ", __func__);                                      \
		printk(__VA_ARGS__);                                                               \
		printk("\r\n");                                                                    \
	} while (0)
#define LOG_INF(...)                                                                               \
	do {                                                                                       \
		printk("<inf> " file_tag ": %s: ", __func__);                                      \
		printk(__VA_ARGS__);                                                               \
		printk("\r\n");                                                                    \
	} while (0)
#define LOG_DBG(...)                                                                               \
	do {                                                                                       \
		printk("<dbg> " file_tag ": %s: ", __func__);                                      \
		printk(__VA_ARGS__);                                                               \
		printk("\r\n");                                                                    \
	} while (0)
#endif

static bool configured __unused;
static const struct device *hdev0;
static const struct device *hdev1;
static const struct device *hdev2;

static void usb_start_tx(void);
static void usb_start_kb_tx(void);

static void usb_evt_cb(air_usb_evt_t evt, const uint8_t *para)
{
	int ret;
	switch (evt) {
	case AIR_USB_EVT_PLUG_IN:
		LOG_INF("AIR_USB_EVT_PLUG_IN");
		ret = air_usb_enable();
		if (ret != 0) {
			LOG_ERR("Failed to enable USB: %d", ret);
			return;
		}
		break;
	case AIR_USB_EVT_PLUG_OUT:
		LOG_INF("AIR_USB_EVT_PLUG_OUT");
		ret = air_usb_disable();
		if (ret != 0) {
			LOG_ERR("Failed to disable USB: %d", ret);
			return;
		}
		break;
	case AIR_USB_EVT_CONNECTED:
		LOG_INF("AIR_USB_EVT_CONNECTED");
		break;
	case AIR_USB_EVT_CONFIGURED:
		LOG_INF("AIR_USB_EVT_CONFIGURED, fcpu:%d khz", hal_dvfs_get_cpu_frequency());
		usb_start_tx();
		usb_start_kb_tx();
		break;
	case AIR_USB_EVT_DISCONNECTED:
		LOG_INF("AIR_USB_EVT_DISCONNECTED");
		break;
	case AIR_USB_EVT_RESET:
		LOG_INF("AIR_USB_EVT_RESET");
		break;
	case AIR_USB_EVT_SUSPEND:
		LOG_INF("AIR_USB_EVT_SUSPEND");
		break;
	case AIR_USB_EVT_RESUME:
		LOG_INF("AIR_USB_EVT_RESUME");
		break;
	case AIR_USB_EVT_INTERFACE:
		LOG_INF("AIR_USB_EVT_INTERFACE");
		break;
	case AIR_USB_EVT_SET_HALT:
		LOG_INF("AIR_USB_EVT_SET_HALT");
		break;
	case AIR_USB_EVT_CLEAR_HALT:
		LOG_INF("AIR_USB_EVT_CLEAR_HALT");
		break;
	case AIR_USB_EVT_SOF:
		// LOG_INF("AIR_USB_EVT_SOF");
		hal_gpio_set_output(USB_SOF_GPIO, HAL_GPIO_DATA_HIGH);
		hal_gpt_delay_us(1);
		hal_gpio_set_output(USB_SOF_GPIO, HAL_GPIO_DATA_LOW);
		break;
	default:
		LOG_DBG("%u unhandled", evt);
		break;
	}
}

#if KERNEL_VERSION_NUMBER >= ZEPHYR_VERSION(3, 7, 0)
static int usb_device_init(void)
#else
static int usb_device_init(const struct device *dev)
#endif
{
	hdev0 = device_get_binding("HID_0");
	if (hdev0 == NULL) {
		LOG_ERR("Cannot get USB HID Device 0");
		return -ENODEV;
	}

	hdev1 = device_get_binding("HID_1");
	if (hdev1 == NULL) {
		LOG_ERR("Cannot get USB HID Device 1");
		return -ENODEV;
	}

	hdev2 = device_get_binding("HID_2");
	if (hdev2 == NULL) {
		LOG_ERR("Cannot get USB HID Device 2");
		return -ENODEV;
	}

	LOG_INF("HID Device: dev0 %p, dev1 %p, dev2 %p", hdev0, hdev1, hdev2);

	/* Register the HID device to airoha usb hid subsys */
	air_usb_hid_device_register(hdev0);
	air_usb_hid_device_register(hdev1);
	air_usb_hid_device_register(hdev2);

	air_usb_hid_gen_rdesc(hdev0,
			      (air_usb_hid_report_desc_t[1]){
				      AIR_USB_REPORT_DESC_GAMING_MS,
			      },
			      1);

	air_usb_hid_gen_rdesc(hdev1,
			      (air_usb_hid_report_desc_t[2]){
				      AIR_USB_REPORT_DESC_GAMING_KB,
				      AIR_USB_REPORT_DESC_CONSUMER,
			      },
			      2);

	air_usb_hid_gen_rdesc(hdev2,
			      (air_usb_hid_report_desc_t[1]){
				      AIR_USB_REPORT_DESC_MUX,
			      },
			      1);

	/* Register to Zephyr USB HID stack */
	usb_hid_register_device(hdev0, air_usb_hid_get_rdesc(hdev0),
				air_usb_hid_get_rdesc_len(hdev0), &airoha_usb_hid_ops);
	usb_hid_register_device(hdev1, air_usb_hid_get_rdesc(hdev1),
				air_usb_hid_get_rdesc_len(hdev1), &airoha_usb_hid_ops);
	usb_hid_register_device(hdev2, air_usb_hid_get_rdesc(hdev2),
				air_usb_hid_get_rdesc_len(hdev2), &airoha_usb_hid_ops);

	if (usb_hid_set_proto_code(hdev0, HID_BOOT_IFACE_CODE_MOUSE)) {
		LOG_WRN("Failed to set Protocol Code");
	}
	if (usb_hid_set_proto_code(hdev1, HID_BOOT_IFACE_CODE_KEYBOARD)) {
		LOG_WRN("Failed to set Protocol Code");
	}
	if (usb_hid_set_proto_code(hdev2, HID_BOOT_IFACE_CODE_NONE)) {
		LOG_WRN("Failed to set Protocol Code");
	}

	usb_hid_init(hdev0);
	usb_hid_init(hdev1);
	usb_hid_init(hdev2);

	/* USB PKTDONE EINT Setup */
	air_usb_hid_config_pktdone_eint(hdev0, 1, true, 0);

	return 0;
}

void usb0_eint_cb(void *p)
{
	const struct device *hiddev_ms =
		air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_GAMING_MS);

	uint32_t t = hal_eint_get_counter_value(EINT_COUNTER_NUMBER_0);
	// uint32_t t = 0;
	LOG_INF("usb0_eint_cb t=%d", t);
	hal_eint_unmask(HAL_EINT_USB0);
	air_usb_hid_clear_pktdone_eint(hiddev_ms);
}

void usb_eint_init(void)
{
	LOG_INF("usb_eint_init");
	hal_eint_status_t status;
	hal_eint_config_t config_eint;
	config_eint.trigger_mode = HAL_EINT_EDGE_FALLING;
	config_eint.debounce_time = 0;

	status = hal_eint_init(HAL_EINT_USB0, &config_eint);
	if (status != HAL_EINT_STATUS_OK) {
		printk("Failed to initialize EINT1 %d\r\n", HAL_EINT_USB0);
	}
	status = hal_eint_register_callback(HAL_EINT_USB0, (void *)usb0_eint_cb,
					    NULL);
	if (status != HAL_EINT_STATUS_OK) {
		printk("Failed to config register callback for EINT1 %d\r\n",
		       HAL_EINT_USB0);
	}
	hal_eint_enable(HAL_EINT_USB0);
	hal_eint_unmask(HAL_EINT_USB0);

	hal_eint_counter_enable();
	hal_eint_set_counter_number(HAL_EINT_USB0, EINT_COUNTER_NUMBER_0);
}

SYS_INIT(usb_device_init, APPLICATION, CONFIG_KERNEL_INIT_PRIORITY_DEVICE);

static uint32_t usb_user_id;

typedef struct __attribute__((__packed__)) {
	uint8_t id;
	uint8_t key;
	uint16_t x: 12;
	uint16_t y: 12;
	uint8_t wheel;
	uint8_t acpan;
} gaming_ms_report_t;

static gaming_ms_report_t ms_report = {
	.id = 0x02, .key = 0x00, .x = 0x00, .y = 0x00, .wheel = 0x00, .acpan = 0x00};

air_usb_hid_gaming_kb_report_t kb_report_key_a = {
	.report_id = AIR_USB_HID_GAMING_KB_REPORT_ID, .modifier = 0x00, .key = {0x04, 0, 0, 0, 0}};

air_usb_hid_gaming_kb_report_t kb_report_empty = {
	.report_id = AIR_USB_HID_GAMING_KB_REPORT_ID, .modifier = 0x00, .key = {0, 0, 0, 0, 0}};

static volatile bool pressed = false;

static int kb_led_update(const struct device *dev, uint8_t type, uint8_t id, uint16_t len,
			 const uint8_t *buf)
{
	LOG_INF("kb_led_update, r_id:%d, r_len:%d, data[0]:%d, data[1]:%d", id, len, buf[0],
		buf[1]);
	return 0;
}

static int ms_tx_done(const struct device *dev, uint8_t type, uint8_t id, uint16_t len,
		      const uint8_t *buf)
{
	LOG_INF("ms_tx_done, r_id:%d, r_len:%d, x:%d", id, len, ms_report.x);

	if (ms_report.x >= 10) {
		return 0;
	}
	ms_report.x += 1;
	hal_gpio_set_output(USB_TX_GPIO, HAL_GPIO_DATA_HIGH);
	int ret = air_usb_hid_tx(usb_user_id, dev, sizeof(ms_report), (void *)&ms_report);
	hal_gpio_set_output(USB_TX_GPIO, HAL_GPIO_DATA_LOW);
	LOG_INF("air_usb_hid_tx ret:%d", ret);
	return 0;
}

static int kb_tx_done(const struct device *dev, uint8_t type, uint8_t id, uint16_t len,
		      const uint8_t *buf)
{
	LOG_INF("kb_tx_done, r_id:%d, r_len:%d", id, len);
	if (pressed) {
		hal_gpio_set_output(USB_TX_GPIO, HAL_GPIO_DATA_HIGH);
		air_usb_hid_tx(usb_user_id, dev, sizeof(kb_report_empty), (void *)&kb_report_empty);
		hal_gpio_set_output(USB_TX_GPIO, HAL_GPIO_DATA_LOW);
		pressed = false;
	}

	return 0;
}

static int ms_tx_free(const struct device *dev)
{
	LOG_INF("ms_tx_free");
	return 0;
}

static void usb_start_tx(void)
{
	const struct device *hiddev_ms =
		air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_GAMING_MS);

	hal_gpio_set_output(USB_TX_GPIO, HAL_GPIO_DATA_HIGH);
	int ret = air_usb_hid_tx(usb_user_id, hiddev_ms, sizeof(ms_report), (void *)&ms_report);
	hal_gpio_set_output(USB_TX_GPIO, HAL_GPIO_DATA_LOW);
	LOG_INF("air_usb_hid_tx ret:%d", ret);
}

static void usb_start_kb_tx(void)
{
	const struct device *hiddev_kb =
		air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_GAMING_KB);
	int ret;

	pressed = true;
	hal_gpt_delay_ms(20);
	hal_gpio_set_output(USB_TX_GPIO, HAL_GPIO_DATA_HIGH);
	ret = air_usb_hid_tx(usb_user_id, hiddev_kb, sizeof(kb_report_key_a),
			     (void *)&kb_report_key_a);
	hal_gpio_set_output(USB_TX_GPIO, HAL_GPIO_DATA_LOW);
	LOG_INF("usb_kb_tx ret:%d", ret);
}

static void register_usb_hid_cb(void) __unused;
static void register_usb_hid_cb(void)
{
	const struct device *hiddev =
		air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_MUX);

	air_usb_hid_register_set_report_cb(usb_user_id, hiddev, USB_HID_REPORT_TYPE_FEATURE, 0x06,
					   0x3B, NULL);
	air_usb_hid_register_set_report_cb(usb_user_id, hiddev, USB_HID_REPORT_TYPE_FEATURE, 0x07,
					   0x3B, NULL);

	const struct device *hiddev_kb =
		air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_GAMING_KB);

	air_usb_hid_register_output_cb(usb_user_id, hiddev_kb, USB_HID_REPORT_TYPE_OUTPUT, 0X01,
				       0x02, kb_led_update);
	air_usb_hid_register_tx_done_cb(usb_user_id, hiddev_kb, USB_HID_REPORT_TYPE_INPUT,
					AIR_USB_HID_GAMING_KB_REPORT_ID,
					sizeof(air_usb_hid_gaming_kb_report_t), kb_tx_done);

	const struct device *hiddev_ms =
		air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_GAMING_MS);

	air_usb_hid_register_tx_done_cb(usb_user_id, hiddev_ms, USB_HID_REPORT_TYPE_INPUT, 0X02,
					0x07, ms_tx_done);
	air_usb_hid_register_tx_free_cb(usb_user_id, hiddev_ms, ms_tx_free);
}

int misc_init(void)
{
	hal_gpio_init(USB_SOF_GPIO);
	hal_pinmux_set_function(USB_SOF_GPIO, USB_SOF_GPIO_MODE_GPIO);
	hal_gpio_set_direction(USB_SOF_GPIO, HAL_GPIO_DIRECTION_OUTPUT);
	hal_gpio_set_output(USB_SOF_GPIO, HAL_GPIO_DATA_LOW);

	hal_gpio_init(USB_TX_GPIO);
	hal_pinmux_set_function(USB_TX_GPIO, USB_TX_GPIO_MODE_GPIO);
	hal_gpio_set_direction(USB_TX_GPIO, HAL_GPIO_DIRECTION_OUTPUT);
	hal_gpio_set_output(USB_TX_GPIO, HAL_GPIO_DATA_LOW);

	return 0;
}

int main(void)
{
	int ret;
	printk("main!!\r\n");

	LOG_INF("Starting application");

	misc_init();
	usb_eint_init();

	hal_dvfs_lock_control(HAL_DVFS_OPP_HIGH, HAL_DVFS_LOCK);

	air_usb_create_user("HID_DEMO", &usb_user_id);

	hal_usb_set_speed(1);
	register_usb_hid_cb();

	air_usb_register_evt_cb(usb_user_id, usb_evt_cb);

	ret = air_usb_init();
	if (ret != 0) {
		LOG_ERR("Failed to init USB");
		return 0;
	}

	return 0;
}
