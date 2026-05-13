
/* Copyright Statement:
 *
 * (C) 2024  Airoha Technology Corp. All rights reserved.
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

#ifndef __HID_SCENARIO_USB_MODE_H__
#define __HID_SCENARIO_USB_MODE_H__
#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)

#include "hid_scenario_service.h"
#include "air_usb_hid_desc.h"
#include "air_usb.h"

// #define CONFIG_DBG_HID_USB_SOF       //USB Debug Log for SOF
// #define CONFIG_DBG_REPORT_LOG
#define CONFIG_DBG_WAIT_SOF_COUNT
// #define CONFIG_HID_USB_CHECK_FS_HS

/* Public typedef ------------------------------------------------------------*/
typedef enum {
    HID_SCENARIO_APP_CHANGE_OPEN_STATUS = 0,
    HID_SCENARIO_APP_USB_ENABLE,
    HID_SCENARIO_APP_USB_DISABLE,
    HID_SCENARIO_APP_USB_SOF_ON,
} hid_scenario_app_usb_evt_t;

typedef enum {
    HID_USB_RISCV_TRIGGER_CHANGE,
    HID_USB_SEND_DUMMY_REPORT,
    HID_USB_SEND_RESUME_REPORT,
    HID_USB_TX_DONE_ENABLE,
    HID_USB_RESET_DUMMY_TIMER,
} hid_scenario_usb_event_t;

typedef void (*hid_scenario_usb_callback)(uint8_t event);
typedef void (*hid_scenario_sof_callback)();
typedef void (*hid_scenario_usb_event_callback)(uint8_t evt);
typedef struct {
    hid_scenario_usb_callback        usb_cb;
    hid_scenario_sof_callback        sof_cb;
    hid_scenario_usb_event_callback  usb_evt_cb;
} hid_scenario_usb_callbacks_t;

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
typedef struct {
    uint16_t sof_count;
    uint16_t tx_ok_count;
    uint16_t tx_fail_count;
    uint16_t max_time;
    uint16_t min_time;
    uint32_t sum_time;
} hid_usb_sof_dbg_t;

/******************************************************************************/
/* functions                                                                  */
/******************************************************************************/
int hid_usb_device_register_init(const struct device *dev, air_usb_hid_report_desc_t *descs, size_t desc_count);
bool hid_usb_device_set_init(const struct device *dev, uint8_t iface, bool set_nv);
#if defined(CONFIG_AIR_USB_XINPUT_ENABLE)
void hid_register_usb_xinput_tx_done(const struct device *dev);
void hid_register_usb_xinput_data_received(const struct device *dev);
#endif /* CONFIG_AIR_USB_XINPUT_ENABLE */
void hid_register_usb_tx_done(uint8_t report_desc, uint8_t type, uint8_t report_id, uint8_t len);
void hid_register_usb_hid_cb(void);
bool hid_scenario_usb_register_callbacks(const hid_scenario_usb_callbacks_t *cbs);

uint8_t hid_scenario_usb_mode_init();
uint8_t hid_scenario_usb_mode_open(uint32_t link_idx, T_HID_SCENARIO_OPEN_TYPE_E parameter);
uint8_t hid_scenario_usb_mode_start(uint32_t link_idx, void* parameter);
uint8_t hid_scenario_usb_mode_stop(uint8_t parameter);
uint8_t hid_scenario_usb_mode_close(uint8_t parameter);
uint8_t hid_scenario_usb_mode_config(T_HID_SCENARIO_CONFIG_PARA_S* config);

uint8_t hid_scenario_usb_for_applaciton(uint8_t event);
void hid_scenario_usb_send_report(const struct device *dev, uint8_t *report);
uint8_t hid_usb_mode__wait_for_ccni_send_ready(void);
uint8_t hid_scenario_usb_mode__get_state();
#if defined(CONFIG_AIR_USB_XINPUT_ENABLE)
void hid_usb_mode__set_usb_mode(air_usb_mode_t mode);
#endif /* CONFIG_AIR_USB_XINPUT_ENABLE */

bool hid_scenario_usb_get_vbus();
void hid_usb_ep_flush(const struct device *dev, bool dir_in);
#endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/

#endif /*END _HID_SCENARIO_USB_MODE_H_*/
