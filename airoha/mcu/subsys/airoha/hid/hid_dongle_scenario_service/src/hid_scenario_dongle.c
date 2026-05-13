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
 * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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

#if defined(AIR_PURE_GAMING_DONGLE_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/drivers/sensor.h>
#include "air_usb.h"
#include "air_usb_hid.h"
// #include "hal_gpt.h"
// #include "hal_gpt_internal.h"
#include "hal_ccni.h"
#include "hal_ccni_config.h"
#include "hal_usb.h"
#include "hal_usb_internal.h"
#include "hal_gpio.h"
#include "hid_scenario_dongle.h"
#include "hid_critical_path.h"
#include "hal_dvfs.h"
#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)
#include "custom_protocol.h"
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE) */
#ifdef AIR_USB_XINPUT_ENABLE
#include "air_usb_xinput.h"
#include "app_bt_conn_manager.h"
#include "app_events.h"
#include "af_events_declaration.h"
#endif /* AIR_USB_XINPUT_ENABLE */
#if defined(CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER)
#include "auto_switch_service.h"
#endif

/* Private define ------------------------------------------------------------*/
#define thisMODULE  Dongle_mode
#define thisMOD    "Dongle_mode"
LOG_MODULE_REGISTER(thisMODULE);

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static const struct device *hdev0;
static const struct device *hdev1;
static const struct device *hdev2;
#if CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE
static const struct device *hdev3;
#endif /* CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE */
#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
static const struct device *hdev4;
#endif /* CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE */
#ifdef AIR_USB_XINPUT_ENABLE
air_usb_mode_t usb_mode = USB_MODE_HID;
const struct device *xinput_dev;
const struct device *xinput_hdev0;
const struct device *xinput_hdev1;
const struct device *xinput_hdev2;
const struct device *xinput_hdev3;
#endif /* AIR_USB_XINPUT_ENABLE */

/* Public variables ----------------------------------------------------------*/
uint32_t usb_user_id;

static const struct device * get_hid_device(void) {
    static uint8_t hid_dev_count = 0;
    const struct device *hid_dev = NULL;
    if (hid_dev_count >= CONFIG_USB_HID_DEVICE_COUNT) {
        LOG_ERR("HID device count exceeded maximum limit");
        return NULL;
    }
    char dev_name[10];
    snprintf(dev_name, sizeof(dev_name), "HID_%d", hid_dev_count);
    hid_dev = device_get_binding(dev_name);
    if (hid_dev == NULL) {
        LOG_ERR("Failed to get HID device %d binding", hid_dev_count);
        return NULL;
    }
    hid_dev_count++;
    return hid_dev;
}

/* Private functions ---------------------------------------------------------*/
static int usb_device_init(void)
{
    LOG_INF("usb_device_init ");
    hdev0 = get_hid_device();
    if (hdev0 == NULL) {
        LOG_ERR("Cannot get USB HID Device to hdev0");
        return -ENODEV;
    }
    else{
        LOG_INF("get_hid_device to hdev0");
    }

    hdev1 = get_hid_device();
    if (hdev1 == NULL) {
        LOG_ERR("Cannot get USB HID Device to hdev1");
        return -ENODEV;
    }
    else{
        LOG_INF("get_hid_device to hdev1");
    }

    hdev2 = get_hid_device();
    if (hdev2 == NULL) {
        LOG_ERR("Cannot get USB HID Device to hdev2");
        return -ENODEV;
    }
    else{
        LOG_INF("get_hid_device to hdev2");
    // LOG_INF("HID Device: dev0 %p, dev1 %p, dev2 %p", hdev0, hdev1, hdev2);
    }

    #if CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE
    hdev3 = get_hid_device();
    if (hdev3 == NULL) {
        LOG_ERR("Cannot get USB HID Device to hdev3");
        return -ENODEV;
    }
    else{
        LOG_INF("get_hid_device to hdev3");
    }
    #endif /* CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE */

#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
    hdev4 = get_hid_device();
    if (hdev4 == NULL) {
        LOG_ERR("Cannot get USB HID Device to hdev4");
        return -ENODEV;
    }
    else{
        LOG_INF("get_hid_device to hdev4");
    }
#endif /* CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE */

    /* Register the HID device to airoha usb hid subsys */
    int ret = 0;
    ret |= air_usb_hid_device_register(hdev0);
    ret |= air_usb_hid_device_register(hdev1);
    ret |= air_usb_hid_device_register(hdev2);
    #if CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE
    ret |= air_usb_hid_device_register(hdev3);
    #endif /* CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE */
#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
    ret |= air_usb_hid_device_register(hdev4);
#endif /* CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE */
    if(ret != 0){
        LOG_ERR("air_usb_hid_device_register something fail");
    }
    else{
        LOG_INF("air_usb_hid_device_register all ok");
    }
    ret = 0;
    ret |= air_usb_hid_gen_rdesc(hdev0,
                  (air_usb_hid_report_desc_t[2]){
                      AIR_USB_REPORT_DESC_GAMING_MS,
                      AIR_USB_REPORT_DESC_CUSTOM,
                  }, 2);

    ret |= air_usb_hid_gen_rdesc(hdev1,
                  (air_usb_hid_report_desc_t[2]){
                      AIR_USB_REPORT_DESC_MUX,
                      AIR_USB_REPORT_DESC_EPIO,
                  }, 2);

    ret |= air_usb_hid_gen_rdesc(hdev2,
                  (air_usb_hid_report_desc_t[2]){
                      AIR_USB_REPORT_DESC_GAMING_KB,
                      AIR_USB_REPORT_DESC_CONSUMER,
                  }, 2);
#if CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE
    ret |= air_usb_hid_gen_rdesc(hdev3,
                  (air_usb_hid_report_desc_t[1]){
                      AIR_USB_REPORT_DESC_GAMEPAD,
                  }, 1);
#endif /* CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE */
#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
    ret |= air_usb_hid_gen_rdesc(hdev4,
                  (air_usb_hid_report_desc_t[1]){
                      AIR_USB_REPORT_DESC_GAMING_KB_NKEY,
                  }, 1);
#endif /* CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE */
    if(ret != 0){
        LOG_ERR("air_usb_hid_gen_rdesc something fail");
    }
    else{
        LOG_INF("air_usb_hid_gen_rdesc all ok");
    }

    /* Register to Zephyr USB HID stack */
    usb_hid_register_device(hdev0, air_usb_hid_get_rdesc(hdev0),
                air_usb_hid_get_rdesc_len(hdev0),
                &airoha_usb_hid_ops);
    usb_hid_register_device(hdev1, air_usb_hid_get_rdesc(hdev1),
                air_usb_hid_get_rdesc_len(hdev1),
                &airoha_usb_hid_ops);
    usb_hid_register_device(hdev2, air_usb_hid_get_rdesc(hdev2),
                air_usb_hid_get_rdesc_len(hdev2),
                &airoha_usb_hid_ops);
#if CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE
    usb_hid_register_device(hdev3, air_usb_hid_get_rdesc(hdev3),
                air_usb_hid_get_rdesc_len(hdev3),
                &airoha_usb_hid_ops);
#endif /* CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE */
#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
    usb_hid_register_device(hdev4, air_usb_hid_get_rdesc(hdev4),
                air_usb_hid_get_rdesc_len(hdev4),
                &airoha_usb_hid_ops);
#endif /* CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE */

    if (usb_hid_set_proto_code(hdev0, HID_BOOT_IFACE_CODE_MOUSE)) {
        LOG_WRN("Failed to set Pry83otocol Code on USB HID Device 0");
    }
    if (usb_hid_set_proto_code(hdev1, HID_BOOT_IFACE_CODE_KEYBOARD)) {
        LOG_WRN("Failed to set Protocol Code on USB HID Device 1");
    }
    if (usb_hid_set_proto_code(hdev2, HID_BOOT_IFACE_CODE_NONE)) {
        LOG_WRN("Failed to set Protocol Code on USB HID Device 2");
    }
#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
    if (usb_hid_set_proto_code(hdev4, HID_BOOT_IFACE_CODE_KEYBOARD)) {
        LOG_WRN("Failed to set Protocol Code on USB HID Device 4");
    }
#endif /* CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE */

#if defined (CONFIG_AIR_M21_SAMPLE)
    air_usb_set_descriptor_value(USB_DESC_DEVICE, AIR_USB_DESC_BCDDEVICE, 0x0101);
    air_usb_set_descriptor_value(USB_DESC_DEVICE, AIR_USB_DESC_ISERIALNUMBER, 0x0);
    air_usb_hid_set_iinterface(hdev0, 2);
    air_usb_hid_set_bcd_version(hdev0, 0x0100);
    air_usb_hid_set_mps(hdev1, USB_EP_DIR_IN, 0x10);
    air_usb_hid_set_mps(hdev2, USB_EP_DIR_IN, 8);
    air_usb_hid_set_binterval(hdev1, USB_EP_DIR_IN, 4);
    air_usb_hid_set_binterval(hdev2, USB_EP_DIR_IN, 4);
#endif /* CONFIG_AIR_M21_SAMPLE */

    ret = 0;
    ret |= usb_hid_init(hdev0);
    ret |= usb_hid_init(hdev1);
    ret |= usb_hid_init(hdev2);
#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE)
    ret |= usb_hid_init(hdev3);
#endif /* defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) */
#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
    ret |= usb_hid_init(hdev4);
#endif /* CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE */

    if(ret != 0){
        LOG_ERR("usb_hid_init something fail");
    }
    else{
        LOG_INF("usb_hid_init all ok");
    }

    return 0;
}

#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE)
static int usb_xinput_device_init(void)
{
    int ret = 0, ret0 = 0, ret1 = 0, ret2 = 0, ret3 = 0;
    LOG_INF("usb_xinput_device_init ");
    xinput_hdev0 = device_get_binding("HID_SEC_0");
    if (xinput_hdev0 == NULL) {
        ret0 = -ENODEV;
    }
    xinput_hdev1 = device_get_binding("HID_SEC_1");
    if (xinput_hdev1 == NULL) {
        ret1 = -ENODEV;
    }
    xinput_hdev2 = device_get_binding("HID_SEC_2");
    if (xinput_hdev2 == NULL) {
        ret2 = -ENODEV;
    }
    xinput_hdev3 = device_get_binding("HID_SEC_3");
    if (xinput_hdev3 == NULL) {
        ret3 = -ENODEV;
    }
    xinput_dev = device_get_binding("XINPUT_DEV");
    if (xinput_dev == NULL) {
        ret = -ENODEV;
    }

    LOG_INF("device_get_binding, ret: %d, ret0: %d, ret1: %d, ret2: %d, ret3: %d",
            ret, ret0, ret1, ret2, ret3);

    /* Register the HID device to airoha usb hid subsys */
    ret0 = air_usb_hid_device_register(xinput_hdev0);
    ret1 = air_usb_hid_device_register(xinput_hdev1);
    ret2 = air_usb_hid_device_register(xinput_hdev2);
    ret3 = air_usb_hid_device_register(xinput_hdev3);
    LOG_INF("air_usb_hid_device_register, ret0: %d, ret1: %d, ret2: %d, ret3: %d",
            ret0, ret1, ret2, ret3);

    ret0 = air_usb_hid_gen_rdesc(xinput_hdev0,
                  (air_usb_hid_report_desc_t[2]){
                      AIR_USB_REPORT_DESC_GAMING_MS,
                      AIR_USB_REPORT_DESC_CUSTOM,
                  }, 2);

    ret1 = air_usb_hid_gen_rdesc(xinput_hdev1,
                  (air_usb_hid_report_desc_t[2]){
                      AIR_USB_REPORT_DESC_MUX,
                      AIR_USB_REPORT_DESC_EPIO,
                  }, 2);

    ret2 = air_usb_hid_gen_rdesc(xinput_hdev2,
                  (air_usb_hid_report_desc_t[2]){
                      AIR_USB_REPORT_DESC_GAMING_KB,
                      AIR_USB_REPORT_DESC_CONSUMER,
                  }, 2);

    ret3 = air_usb_hid_gen_rdesc(xinput_hdev3,
                  (air_usb_hid_report_desc_t[1]){
                      AIR_USB_REPORT_DESC_CUSTOM,
                  }, 1);

    LOG_INF("air_usb_hid_gen_rdesc, ret0: %d, ret1: %d, ret2: %d, ret3: %d",
            ret0, ret1, ret2, ret3);
    /* Register to Zephyr USB HID stack */
    usb_hid_register_device(xinput_hdev0, air_usb_hid_get_rdesc(xinput_hdev0),
                air_usb_hid_get_rdesc_len(xinput_hdev0),
                &airoha_usb_hid_ops);
    usb_hid_register_device(xinput_hdev1, air_usb_hid_get_rdesc(xinput_hdev1),
                air_usb_hid_get_rdesc_len(xinput_hdev1),
                &airoha_usb_hid_ops);
    usb_hid_register_device(xinput_hdev2, air_usb_hid_get_rdesc(xinput_hdev2),
                air_usb_hid_get_rdesc_len(xinput_hdev2),
                &airoha_usb_hid_ops);
    usb_hid_register_device(xinput_hdev3, air_usb_hid_get_rdesc(xinput_hdev3),
                air_usb_hid_get_rdesc_len(xinput_hdev3),
                &airoha_usb_hid_ops);
    /* xinput register device */
    air_usb_xinput_device_register(xinput_dev);

    if (usb_hid_set_proto_code(xinput_hdev0, HID_BOOT_IFACE_CODE_MOUSE)) {
        LOG_WRN("Failed to set Pry83otocol Code on USB HID Device 0");
    }
    if (usb_hid_set_proto_code(xinput_hdev1, HID_BOOT_IFACE_CODE_KEYBOARD)) {
        LOG_WRN("Failed to set Protocol Code on USB HID Device 1");
    }
    if (usb_hid_set_proto_code(xinput_hdev2, HID_BOOT_IFACE_CODE_NONE)) {
        LOG_WRN("Failed to set Protocol Code on USB HID Device 2");
    }

    if (usb_hid_set_proto_code(xinput_hdev3, HID_BOOT_IFACE_CODE_NONE)) {
        LOG_WRN("Failed to set Protocol Code on USB HID Device 4");
    }

    ret = 0;
    ret |= usb_hid_init(xinput_hdev0);
    ret |= usb_hid_init(xinput_hdev1);
    ret |= usb_hid_init(xinput_hdev2);
    ret |= usb_hid_init(xinput_hdev3);

    if(ret != 0){
        LOG_ERR("usb_hid_init something fail");
    }
    else{
        LOG_INF("usb_hid_init all ok");
    }

    return 0;
}
#endif /* defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE) */

#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE)
const struct device *hid_scenario_dongle_get_xinput_dev(void)
{
    return xinput_dev;
}

int hid_scenario_dongle_xinput_data_received_cb(const struct device *dev, uint16_t len, const uint8_t *buf)
{
    LOG_INF("hid_scenario_dongle_xinput_data_received_cb usb in process dev = 0x%x, len = %u, data = 0x%08x 0x%08x ...", dev, len, *((uint32_t *)buf), *((uint32_t *)buf+1));

    bt_ull_le_hid_srv_set_output_report_t *g_output_report = (bt_ull_le_hid_srv_set_output_report_t *)k_malloc(sizeof(bt_ull_le_hid_srv_set_output_report_t));
    if (g_output_report == NULL)
    {
        LOG_INF("Failed to malloc xinput_data buffer->g_output_report");
        return 0;
    }
    g_output_report->data= (uint8_t *)k_malloc(len);

    if (g_output_report->data == NULL)
    {
        LOG_INF("Failed to malloc xinput_data buffer -> data");
        k_free(g_output_report);
        return 0;
    }

    g_output_report->device_type = BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD;
    g_output_report->size = len;
    memcpy(g_output_report->data, buf, len);

    // LOG_INF("hid_scenario_dongle_xinput_data_received_cb usb in process dev = 0x%x, output_report.len = %u, output_report-> data = 0x%08x 0x%08x ...", dev, g_output_report->size, *((uint32_t *)g_output_report->data), *((uint32_t *)(g_output_report->data)+1));
    app_events_send(EVT_CMD_OUTPUT_REPORT_CHANGE_REQ, g_output_report);
    return 0;
}
#endif /* defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE) */

static void register_usb_hid_cb(void)
{
#if 0
    const struct device *hiddev_kb =
        air_usb_hid_find_first_device_by_report(
            AIR_USB_REPORT_DESC_GAMING_KB);

    air_usb_hid_register_output_cb(usb_user_id, hiddev_kb,
                       USB_HID_REPORT_TYPE_OUTPUT, 0X01, 0x02,
                       kb_led_update);

    const struct device *hiddev_ms =
        air_usb_hid_find_first_device_by_report(
            AIR_USB_REPORT_DESC_GAMING_MS);

    air_usb_hid_register_tx_done_cb(usb_user_id, hiddev_ms,
                    USB_HID_REPORT_TYPE_INPUT, 0X02, 0x07,
                    ms_tx_done);
    air_usb_hid_register_tx_free_cb(usb_user_id, hiddev_ms, ms_tx_free);
#endif

#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE)
    air_usb_xinput_register_data_received_cb(usb_user_id, xinput_dev, hid_scenario_dongle_xinput_data_received_cb);
#endif /* defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE) */
}

/* Public functions ----------------------------------------------------------*/
int hid_scenario_dongle_mode_init(hid_scenario_dongle_init_param_t *init_param)
{
    LOG_INF("hid_scenario_dongle_mode_init");

    /* lock highest speed */
    hal_dvfs_lock_control(HAL_DVFS_OPP_HIGH, HAL_DVFS_LOCK);

    /* enable USB device */
    #if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE)
    if (hid_scenario_dongle_usb_mode_check() == USB_MODE_HID) {
        air_usb_mode_set(USB_MODE_HID);
        usb_device_init();
    } else if (hid_scenario_dongle_usb_mode_check() == USB_MODE_XINPUT) {
        air_usb_mode_set(USB_MODE_XINPUT);
        usb_xinput_device_init();
    }
    #else
        usb_device_init();
    #endif /* #if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE) */

    int ret = air_usb_create_user("HID_Dongle", &usb_user_id);
    if(ret != 0)
    {
        LOG_ERR("air_usb_create_user fail");
        return 0;
    }
    else{
        LOG_INF("air_usb_create_user ok, %u", usb_user_id);
    }

    ret = air_usb_register_evt_cb(usb_user_id, init_param->usb_evt_cb);
    if(ret != 0)
    {
        LOG_ERR("air_usb_register_status_cb fail");
        return 0;
    }
    else
        LOG_INF("air_usb_register_status_cb ok");

    ret = air_usb_init_work_item();
    if(ret)
    {
        LOG_INF("air_usb_init fail ret = %d",ret);
    }

    register_usb_hid_cb();

    hid_critical_path_init();
    #if defined(CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER)
    auto_switch_init();
    #endif
    ret = air_usb_enable();
    if(ret != 0)
    {
        LOG_ERR("air_usb_enable fail");
        return 0;
    }
    else
    {
        LOG_ERR("air_usb_enable ok");
    }

    LOG_INF("hid_scenario_dongle_mode_init end");

    return 0;
}

int hid_scenario_dongle_mode_deinit(void)
{
    LOG_INF("hid_scenario_dongle_mode_deinit");

    hid_critical_path_deinit();

    /* unlock highest speed */
    hal_dvfs_lock_control(HAL_DVFS_OPP_HIGH, HAL_DVFS_UNLOCK);

    LOG_INF("hid_scenario_dongle_mode_deinit end");

    return 0;
}

int hid_scenario_dongle_mode_open(void)
{
    LOG_INF("hid_scenario_dongle_mode_open");

#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)
    epio_custom_protocol_enable(EPIO_CUSTOM_PROTOCOL_USB);
    epio_custom_protocol_enable(EPIO_CUSTOM_PROTOCOL_BT);
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE */

    LOG_INF("hid_scenario_dongle_mode_open end");

    return 0;
}

int hid_scenario_dongle_mode_start(void)
{
    LOG_INF("hid_scenario_dongle_mode_start");

    hid_critical_path_start(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
#if CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE
    hid_critical_path_start(HID_CRITICAL_PATH_DEVICE_TYPE_KEY_REMAP);
#endif
#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
    hid_critical_path_start(HID_CRITICAL_PATH_DEVICE_TYPE_NKEY);
#endif
#if CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE
    hid_critical_path_start(HID_CRITICAL_PATH_DEVICE_TYPE_GAME_CONTROLLER);
#endif /* CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE */

    LOG_INF("hid_scenario_dongle_mode_start end");

    return 0;
}

int hid_scenario_dongle_mode_stop(void)
{
    LOG_INF("hid_scenario_dongle_mode_stop");

    hid_critical_path_stop(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
#if CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE
    hid_critical_path_stop(HID_CRITICAL_PATH_DEVICE_TYPE_KEY_REMAP);
#endif
#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
    hid_critical_path_stop(HID_CRITICAL_PATH_DEVICE_TYPE_NKEY);
#endif
#if CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE
    hid_critical_path_stop(HID_CRITICAL_PATH_DEVICE_TYPE_GAME_CONTROLLER);
#endif /* CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE */

    LOG_INF("hid_scenario_dongle_mode_stop end");

    return 0;
}

int hid_scenario_dongle_mode_close(void)
{
    LOG_INF("hid_scenario_dongle_mode_close");

#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)
    epio_custom_protocol_disable(EPIO_CUSTOM_PROTOCOL_USB);
    epio_custom_protocol_disable(EPIO_CUSTOM_PROTOCOL_BT);
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE */

    LOG_INF("hid_scenario_dongle_mode_close end");

    return 0;
}

int hid_scenario_dongle_mode_config(void)
{
    LOG_INF("hid_scenario_dongle_mode_config");

    LOG_INF("hid_scenario_dongle_mode_config end");

    return 0;
}

#if defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE)
ATTR_TEXT_IN_TCM air_usb_mode_t hid_scenario_dongle_usb_mode_check(void)
{
    return usb_mode;
}

int hid_scenario_dongle_usb_mode_set(air_usb_mode_t mode)
{
    usb_mode = mode;

    LOG_INF("hid_scenario_dongle_usb_mode_set, mode = %d", mode);
    return 0;
}
#endif /* defined(CONFIG_AIR_HID_CP_PROCESS_GAME_CONTROLLER_DATA_ENABLE) && defined(AIR_USB_XINPUT_ENABLE) */

#endif /* AIR_PURE_GAMING_DONGLE_ENABLE */
