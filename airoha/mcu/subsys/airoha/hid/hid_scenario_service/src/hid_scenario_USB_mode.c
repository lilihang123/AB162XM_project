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

#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/drivers/sensor.h>
#include "bt_ull_le_hid_device_manager.h"

#include "hid_scenario_service.h"
#include "hid_scenario_service_internal.h"
#include "hid_scenario_USB_mode.h"
#include "hid_scenario_report_rate.h"
#include "hid_scenario_hogp.h"
#include "hid_common.h"
#include "hid_common_usb.h"

#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
#include "air_usb.h"
#include "air_usb_hid.h"
#include "air_usb_hid_desc.h"
#if defined(CONFIG_AIR_USB_XINPUT_ENABLE)
#include "air_usb_xinput.h"
#endif /* CONFIG_AIR_USB_XINPUT_ENABLE */
#endif /* defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE) */

#include "hal_gpt.h"
#include "hal_gpt_internal.h"
#include "hal_ccni.h"
#include "hal_ccni_config.h"
#include "hal_usb.h"
#include "hal_usb_internal.h"
#include "hal_gpio.h"
#include "hal_dvfs.h"
#include "hal_nvic.h"
#include "hal_nvic_internal.h"
#include "hal_eint_internal.h"
#include "hal_platform.h"
#include "hal_spi_master.h"


#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)
#include "custom_protocol.h"
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE) */

#define thisMODULE  U_mode
#define thisMOD    "U_mode"

LOG_MODULE_REGISTER(thisMODULE);

#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
static int usb_tx_done(const struct device *dev, uint8_t type, uint8_t id, uint16_t len, const uint8_t *buf);
#if defined(CONFIG_AIR_USB_XINPUT_ENABLE)
static int usb_xinput_tx_done(const struct device *dev);
static int usb_xinput_data_receivced(const struct device *dev, uint16_t len, const uint8_t *buf);
#endif /* CONFIG_AIR_USB_XINPUT_ENABLE */
static uint16_t hid_usb_timing_for_sof(void);

#if defined(CONFIG_HID_USB_CHECK_FS_HS)
static uint16_t hid_usb_check_hs_fs(uint16_t cur_interval);
#endif /*_CONFIG_HID_USB_CHECK_FS_HS_*/
static int  hid_usb_protocol_change_cb(const struct device *dev, uint8_t protocol);
static void hid_usb_ms_prepare_boot_protocol(uint8_t *in, uint8_t *out);

#if defined (CONFIG_AIR_NVIDIA_REFLEX_ENABLE)
static void hid_usb_ms_prepare_nv_report(uint8_t *in_buffer, uint8_t *out_buffer);
static bool hid_usb_scenario__is_empty_report(uint8_t *data);
#endif /* CONFIG_AIR_NVIDIA_REFLEX_ENABLE */
static void hid_usb_mode_var_reset(void);
static void hid_usb_set_func_exe_time_adjustment(uint8_t us_time);
/* timers defined ------------------------------------------------------------*/
static void hid_usb_mode__check_suspend_timeout(struct k_timer *timer_id);
K_TIMER_DEFINE(check_suspend_timer, hid_usb_mode__check_suspend_timeout, NULL);
static void hid_usb_mode__resume_dummy_packet_cb(struct k_timer *timer_id);
K_TIMER_DEFINE(resume_dummy_packet_timer, hid_usb_mode__resume_dummy_packet_cb, NULL);

#ifdef CONFIG_DBG_HID_USB_SOF
void hid_usb_tx_count(struct k_timer *timer_id);
K_TIMER_DEFINE(hid_usb_tx_count_timer, hid_usb_tx_count, NULL);
#endif /*_CONFIG_DBG_HID_USB_SOF_*/
/* k_work defined ------------------------------------------------------------*/
static void hid_usb_mode__tx_done_next(struct k_work *work);
static K_WORK_DEFINE(tx_done_next, hid_usb_mode__tx_done_next);
static void hid_usb_mode__tx_nack_next(struct k_work *work);
static K_WORK_DEFINE(tx_nack_next, hid_usb_mode__tx_nack_next);

/* fast word write defined -----------------------------------------------------*/
#define FAST_WORD_WRITE(target, src_0,  src_1,  src_2,  src_3 )     \
    *((uint32_t *)&target ) = (src_0)                               \
                            | ((src_1) <<  8)                       \
                            | ((src_2) << 16)                       \
                            | ((src_3) << 24);

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
/* defined */
#define HID_USB_BIOS_DATA_LEN           8
#define HID_USB_NV_DATA_LEN            14

#define USB_MAX_HS_REPORT_RATE       8000  /* 8000Hz is the limination of High-speed USB*/
#define USB_MAX_FS_REPORT_RATE       1000  /* 1000Hz is the limination of Full-speed USB*/
#define USB_HS_RR_1K_COUNT              8
#define USB_FS_RR_1K_COUNT              1
#define USB_TX_COUNT_WAIT_TIME          1  /* second */
#define USB_CHECK_SUSPEND_TIME       2000  /* ms */
#define SEND_RESUME_DUMMY_TIME         50  /* ms */
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
#define JOYSTICK_0_LEVEL_VALUE       0x8000
#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */
#if defined (CONFIG_AIR_HID_DEBUG_PIN)
#define USB_MS_KEY_NUM               1
#else
#define USB_MS_KEY_NUM               5
#endif /* CONFIG_AIR_HID_DEBUG_PIN */

#if defined(CONFIG_AIR_USB_EARLY_WAKEUP_CM33)
#define USB_CM33_WAIT_FOR_CCNI_TIME    40   /* us */
static uint8_t ccni_wating_counter = 0;
#endif /* CONFIG_AIR_USB_EARLY_WAKEUP_CM33 */

/* private */
static hid_scenario_usb_callbacks_t usb_mode_callback = {0};
static T_HID_MODE_STATE_E usb_mode_state = MODE_NONE;

/* flag */
bool usb_suspend = false;  // check if usb is suspended
bool usb_open_dvfs = false;  // dvfs open or not
bool hid_usb_protocol = false;  //boot or report mode

/* report rate */
uint32_t hid_sof_count = 0;
uint32_t t0_point = 0;
uint32_t t0_delta_time = 0;
uint32_t sof_cb_counter = 0;
uint16_t usb_report_rate;
uint16_t cur_report_rate;
uint8_t usb_report_count = 0;
uint8_t usb_reduce_time = 0;

extern uint32_t flash_p_e_start_time;

/* sof status */
bool usb_sof_status = false;
bool usb_sof_first = false;
uint16_t tx_waiting_count = 0;
#if defined(CONFIG_DBG_WAIT_SOF_COUNT)
uint32_t usb_sof_wait_count = 0;
#endif

#if defined (CONFIG_DBG_HID_USB_SOF)
hid_usb_sof_dbg_t usb_sof_dbg = {
    .sof_count = 0,
    .tx_ok_count = 0,
    .tx_fail_count = 0,
    .max_time = 0,
    .min_time = UINT16_MAX,
    .sum_time = 0,
};
#endif /*_CONFIG_DBG_HID_USB_SOF_*/

/* USB device handle */
uint32_t usb_user_id;
uint32_t usb_ep_flush_flag = false;

/* nv related */
#if defined (CONFIG_AIR_NVIDIA_REFLEX_ENABLE)
typedef struct {
    uint8_t curr_val;
    uint8_t last_val;
    int32_t latency;
} hid_usb_ms_key_t;

hid_usb_ms_key_t usb_ms_key = {0, 0, 0};
uint8_t hid_nv_data[HID_USB_NV_DATA_LEN] = {0};
#else
uint8_t usb_last_ms_key;
#endif /*_CONFIG_AIR_NVIDIA_REFLEX_ENABLE_*/

/* report log */
uint8_t continue_tx_nack_cnt = 0;
#if defined (CONFIG_DBG_REPORT_LOG)
uint8_t cont_kb_ms_tx_nack_cnt = 0;
#endif

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/
static void hid_usb_mode__tx_done_next(struct k_work *work)
{
    if(usb_sof_status)  //if get first time tx done, then update state
    {
        if(usb_mode_callback.usb_evt_cb){
            usb_mode_callback.usb_evt_cb(HID_USB_RISCV_TRIGGER_CHANGE);
        }
        hid_common_clear_hid_exp_flag(FLAG_BIT_USB_TX_NACK);
        usb_mode_state = MODE_USB_STARTED;
        hid_scenario_send_state_update_notification(usb_mode_state, 0);
        #if defined(CONFIG_DBG_WAIT_SOF_COUNT)
        DBG_LOGI(thisMOD, "When sof start to tx success, sof count = %d, try tx times = %d", usb_sof_wait_count, tx_waiting_count);
        #endif /* CONFIG_DBG_WAIT_SOF_COUNT */
        #if defined (CONFIG_DBG_HID_USB_SOF)
        usb_sof_dbg.tx_fail_count = 0;
        usb_sof_dbg.tx_ok_count = 0;
        #endif /*_CONFIG_DBG_HID_USB_SOF_*/

        tx_waiting_count = 0;
        usb_sof_first = false;
        hid_common_set_hid_exp_flag(FLAG_BIT_USB_CONNECTED);
        return;
    }
}

static void hid_usb_mode__tx_nack_next(struct k_work *work)
{
    if(!usb_sof_status && continue_tx_nack_cnt)
    {
        if(usb_mode_callback.usb_evt_cb){
            usb_mode_callback.usb_evt_cb(HID_USB_SEND_DUMMY_REPORT);
        }
        return;
    }
}

static void hid_usb_mode__check_suspend_timeout(struct k_timer *timer_id)
{
    if(usb_suspend)
    {
        DBG_LOGI(thisMOD, "check_suspend_timeout for %d ms, need wait for configured! state = %d", USB_CHECK_SUSPEND_TIME, usb_mode_state);
        hid_usb_mode_var_reset();
        #ifdef CONFIG_DBG_HID_USB_SOF
        k_timer_stop(&hid_usb_tx_count_timer);
        #endif /*_CONFIG_DBG_HID_USB_SOF_*/
        hid_scenario_send_state_update_notification(usb_mode_state, 0);
    }
    else{
        DBG_LOGI(thisMOD, "check_suspend_timeout, touch suspend but get reset! state = %d", usb_mode_state);
    }
}

static void hid_usb_mode__resume_dummy_packet_cb(struct k_timer *timer_id)
{
    DBG_LOGI(thisMOD, "hid_usb_mode__resume_dummy_packet_cb! state = %d", usb_mode_state);
    if(usb_mode_callback.usb_evt_cb){
        usb_mode_callback.usb_evt_cb(HID_USB_SEND_RESUME_REPORT);
    }
}

#if defined (CONFIG_DBG_HID_USB_SOF)
void hid_usb_tx_count(struct k_timer *timer_id)
{
    if(usb_sof_dbg.tx_ok_count | usb_sof_dbg.tx_fail_count){
        DBG_LOGI(thisMOD, "In %ds, fail = %4d, ok = %4d, sof_total = %4d; max = %d, min = %d, avg = %d",
                USB_TX_COUNT_WAIT_TIME,
                usb_sof_dbg.tx_fail_count,
                usb_sof_dbg.tx_ok_count,
                usb_sof_dbg.sof_count,
                usb_sof_dbg.max_time,
                usb_sof_dbg.min_time,
                usb_sof_dbg.sof_count ? usb_sof_dbg.sum_time/usb_sof_dbg.sof_count : 0);
    }
    memset(&usb_sof_dbg, 0, sizeof(usb_sof_dbg));
    usb_sof_dbg.min_time = UINT16_MAX;
}
#endif /*_CONFIG_DBG_HID_USB_SOF_*/

ATTR_TEXT_IN_TCM void hid_usb_sof_trigger_calculate()
{
    uint8_t adj_time = flash_p_e_start_time ? USB_KEY_DELAY_TIME : 0;
    hid_usb_set_func_exe_time_adjustment(adj_time);

    uint16_t sof_interval = hid_usb_timing_for_sof();
    #if defined(CONFIG_HID_USB_CHECK_FS_HS)
    hid_usb_check_hs_fs(sof_interval);
    #endif /*_CONFIG_HID_USB_CHECK_FS_HS_*/
    uint32_t sof_times = t0_delta_time / 125;
    #if defined(CONFIG_AIR_USB_EARLY_WAKEUP_CM33)
    if (sof_cb_counter && (hid_common->hid.outgoing_report_ready == USB_REPORT_TX_NACK ||
        (hid_common->hid.outgoing_report_ready == USB_REPORT_NONE && ccni_wating_counter >= USB_CM33_WAIT_FOR_CCNI_TIME) ||
        (hid_common->hid.outgoing_report_ready == USB_REPORT_COMPLETE &&
        (!ccni_wating_counter || ccni_wating_counter >= USB_CM33_WAIT_FOR_CCNI_TIME))))
    {
        sof_cb_counter--;
        DBG_PING_H(DBG_SIGNAL_DEBUG_2);
        DBG_PING_L(DBG_SIGNAL_DEBUG_2);
        // DBG_LOGI(thisMOD, "report_ready = %d, ccni_wating_counter = %d, sof_cb_counter = %d",
        //     hid_common->hid.outgoing_report_ready,
        //     ccni_wating_counter, sof_cb_counter);
    }
    hid_common->hid.outgoing_report_ready = USB_REPORT_SKIP;
    #endif
    int pending_count = (sof_times / usb_report_count) - sof_cb_counter;
    hid_sof_count = (pending_count > 0) ? pending_count : 0;
    // DBG_LOGI(thisMOD, "sof_cb_counter=%d, sof_times=%d, t0_delta_time=%d, pending_count=%d, hid_sof_count=%d, usb_report_count=%d",
    //      sof_cb_counter, sof_times, t0_delta_time, pending_count, hid_sof_count, usb_report_count);
    if(hid_sof_count && sof_interval < 165)
    {
        if(usb_mode_callback.sof_cb)
        {
            DBG_PING_H(DBG_SIGNAL_DEBUG_3);
            usb_mode_callback.sof_cb();
            sof_cb_counter++;
            DBG_PING_L(DBG_SIGNAL_DEBUG_3);
        }
    }
    #if defined(CONFIG_AIR_USB_EARLY_WAKEUP_CM33)
    else{
        hid_common->hid.outgoing_report_ready = USB_REPORT_TRIGGER_SKIP;
    }
    ccni_wating_counter = 0;
    #endif
    return;
}

void hid_usb_evt_cb_without_sof(air_usb_evt_t evt, const uint8_t *param)
{
    switch(evt)
    {
        case AIR_USB_EVT_PLUG_IN:   // 0
        case AIR_USB_EVT_PLUG_OUT:  // 1
        {
            if(evt == AIR_USB_EVT_PLUG_IN){
                DBG_LOGI(thisMOD, "Receive AIR_USB_EVT_PLUG_IN");
            }
            else{
                DBG_LOGI(thisMOD, "Receive AIR_USB_EVT_PLUG_OUT");
            }
            if(usb_mode_callback.usb_cb){
                usb_mode_callback.usb_cb(evt);
            }
            break;
        }
        case AIR_USB_EVT_DISCONNECTED:
        {
            DBG_LOGI(thisMOD, "Receive AIR_USB_EVT_DISCONNECTED");
            if(k_timer_remaining_get(&check_suspend_timer)){
                DBG_LOGI(thisMOD, "Stop usb suspend timer");
                k_timer_stop(&check_suspend_timer);
            }
            break;
        }
        case AIR_USB_EVT_RESET:  //5
        {
            DBG_LOGI(thisMOD, "Receive AIR_USB_EVT_RESET, usb_mode_state = 0x%X", usb_mode_state);
            usb_sof_status = false;
            tx_waiting_count = 0;
            usb_mode_state = MODE_NONE;
            hid_scenario_send_state_update_notification(usb_mode_state, 0);

            if(k_timer_remaining_get(&check_suspend_timer))
            {
                DBG_LOGI(thisMOD, "Reset usb suspend timer");
                k_timer_stop(&check_suspend_timer);
                k_timer_start(&check_suspend_timer, K_MSEC(USB_CHECK_SUSPEND_TIME) , K_NO_WAIT);
            }
            if(usb_mode_callback.usb_cb){
                usb_mode_callback.usb_cb(AIR_USB_EVT_RESET);
            }
            if(usb_mode_callback.usb_evt_cb){
                usb_mode_callback.usb_evt_cb(HID_USB_RESET_DUMMY_TIMER);
            }
            break;
        }
        case AIR_USB_EVT_CONFIGURED:  //2, After PC enum on, will enter this evt
        {
            DBG_LOGI(thisMOD, "Receive AIR_USB_EVT_CONFIGURED, usb_mode_state = 0x%X", usb_mode_state);
            usb_mode_state = MODE_OPEN_CONNECTED;

            if(k_timer_remaining_get(&check_suspend_timer))
            {
                DBG_LOGI(thisMOD, "Stop usb suspend timer");
                k_timer_stop(&check_suspend_timer);
            }
            if(usb_mode_callback.usb_cb){
                usb_mode_callback.usb_cb(AIR_USB_EVT_CONFIGURED);
            }
            if(usb_mode_callback.usb_evt_cb){
                usb_mode_callback.usb_evt_cb(HID_USB_TX_DONE_ENABLE);
            }
            break;
        }
        case AIR_USB_EVT_SUSPEND:  //6, sleep
        {
            DBG_LOGI(thisMOD, "Receive AIR_USB_EVT_SUSPEND, usb_mode_state = 0x%X", usb_mode_state);
            #if defined(CONFIG_AIR_USB_EARLY_WAKEUP_CM33)
            DBG_PING_H(DBG_SIGNAL_DEBUG_2);
            DBG_PING_L(DBG_SIGNAL_DEBUG_2);
            hid_common->hid.outgoing_report_ready = USB_REPORT_SKIP;
            #endif
            usb_suspend = true;
            tx_waiting_count = 0;
            usb_mode_state = MODE_USB_STOPPED;

            k_timer_stop(&check_suspend_timer);
            k_timer_start(&check_suspend_timer, K_MSEC(USB_CHECK_SUSPEND_TIME) , K_NO_WAIT);
            if(usb_mode_callback.usb_evt_cb){
                usb_mode_callback.usb_evt_cb(HID_USB_RESET_DUMMY_TIMER);
            }
            break;
        }
        case AIR_USB_EVT_RESUME:  //7, wakeup
        {
            DBG_LOGI(thisMOD, "Receive AIR_USB_EVT_RESUME, usb_mode_state = 0x%X", usb_mode_state);
            if(usb_mode_state == MODE_USB_STOPPED || usb_mode_state == MODE_STOPPED)
            {
                if(usb_mode_callback.usb_evt_cb){
                    usb_mode_callback.usb_evt_cb(HID_USB_TX_DONE_ENABLE);
                }
                usb_mode_state = MODE_USB_RESUME;
                hid_scenario_send_state_update_notification(usb_mode_state, 0);
            }
            break;
        }
        default:{
            break;
        }
    }
}

ATTR_TEXT_IN_TCM void hid_usb_evt_cb(air_usb_evt_t evt, const uint8_t *param)
{
    usb_suspend = false;
    switch(evt)
    {
        case AIR_USB_EVT_SOF:  //11
        {
            DBG_PING_H(DBG_SIGNAL_USB_SOF);
            if(!usb_sof_first){
                // DBG_LOGI(thisMOD, "Receive first AIR_USB_EVT_SOF, usb_mode_state = 0x%X", usb_mode_state);
                usb_sof_first = true;
            #if defined(CONFIG_DBG_WAIT_SOF_COUNT)
                usb_sof_wait_count = 1;
                break;
            }
            else if(usb_sof_first && !usb_sof_status){  //record wait
                usb_sof_wait_count++;
            #endif
            }

            if(usb_sof_status)
            {
                hid_usb_sof_trigger_calculate();
            }
            DBG_PING_L(DBG_SIGNAL_USB_SOF);
            break;
        }
        default:
        {
            hid_usb_evt_cb_without_sof(evt, param);
            break;
        }
    }
}

int hid_usb_protocol_change_cb(const struct device *dev, uint8_t protocol)
{
    DBG_LOGI(thisMOD, "hid_usb_protocol_change_cb dev: %p, protocol: %d", dev, protocol);
    hid_usb_protocol = (protocol == USB_PROTOCOL_BOOT_MODE) ? 0 : 1;
    return 0;
}

/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/


/******************************************************************************/
/* USB tx related functions                                                   */
/******************************************************************************/
#if defined (CONFIG_AIR_NVIDIA_REFLEX_ENABLE)
static void hid_ms_get_key_timestamp(uint32_t hid_ms_tx_done_time)
{
    if(usb_ms_key.curr_val != usb_ms_key.last_val)
    {
        uint8_t diff = usb_ms_key.curr_val;
        diff ^= usb_ms_key.last_val;

        for(uint8_t idx = 0; idx < USB_MS_KEY_NUM; idx++)
        {
            if(diff & 0b01)
            {
                uint32_t key_pressed_time = hal_eint_get_counter_value(idx);
                usb_ms_key.latency = (int32_t)hid_ms_tx_done_time - (int32_t)key_pressed_time;
                if(usb_ms_key.latency < 0) {
                    usb_ms_key.latency += UINT16_MAX;
                }
                DBG_LOGI(thisMOD, "[Key %d -> %d] key_press_time = %d, tx_done_time = %d, latency = %d",
                            usb_ms_key.last_val,
                            usb_ms_key.curr_val,
                            key_pressed_time,
                            hid_ms_tx_done_time,
                            usb_ms_key.latency);
                break;
            }
            diff >>= 1;
        }
        usb_ms_key.last_val = usb_ms_key.curr_val;
    }
}
#endif /*_CONFIG_AIR_NVIDIA_REFLEX_ENABLE_*/

ATTR_TEXT_IN_TCM static uint32_t hid_mode_state_check_tx()
{
    if(usb_mode_state == MODE_NONE || usb_mode_state == MODE_STOPPED || usb_mode_state == MODE_CLOSED) {
        return false;
    }
    return true;
}

#if defined(CONFIG_AIR_USB_XINPUT_ENABLE)
ATTR_TEXT_IN_TCM static int usb_xinput_tx_done(const struct device *dev)
{
    DBG_PING_H(DBG_SIGNAL_USB_TX_DONE);
    if(usb_ep_flush_flag) {
        usb_ep_flush_flag = false;
        k_work_submit(&tx_nack_next);
    }
    else if(!usb_sof_status && hid_mode_state_check_tx())
    {
        usb_sof_status = true;
        t0_point = 0;
        sof_cb_counter = 0;
        DBG_LOGI(thisMOD, "[Report log]first xinput tx done!!!!, usb_mode_state = %d", usb_mode_state);
        k_work_submit(&tx_done_next);
    }
    DBG_PING_L(DBG_SIGNAL_USB_TX_DONE);
    return 0;
}

ATTR_TEXT_IN_TCM static int usb_xinput_data_receivced(const struct device *dev, uint16_t len, const uint8_t *buf)
{
    #if defined(CONFIG_AIR_HID_OUTPUT_REPORT_NOTIFY)
    DBG_LOGI(thisMOD, "[Report log]xinput data received, dev = %p, len = %u, data = 0x%08x 0x%08x ...", dev, len, *((uint32_t *)buf), *((uint32_t *)buf+1));
    hid_scenario_send_notification(SS_EVT_HID_OUTPUT_REPORT, (uint8_t *)buf, len);
    #else
    DBG_LOGI(thisMOD, "CONFIG_AIR_HID_OUTPUT_REPORT_NOTIFY=n, plz enable it in config!");
    #endif
    return 0;
}
#endif /* CONFIG_AIR_USB_XINPUT_ENABLE */

ATTR_TEXT_IN_TCM static int usb_tx_done(const struct device *dev, uint8_t type, uint8_t id, uint16_t len, const uint8_t *buf)
{
    DBG_PING_H(DBG_SIGNAL_USB_TX_DONE);
    if(usb_ep_flush_flag) {
        usb_ep_flush_flag = false;
        k_work_submit(&tx_nack_next);
    }
    else if(!usb_sof_status && hid_mode_state_check_tx())
    {
        usb_sof_status = true;
        t0_point = 0;
        sof_cb_counter = 0;
        DBG_LOGI(thisMOD, "[Report log]first tx done!!!!, usb_mode_state = %d", usb_mode_state);
        k_work_submit(&tx_done_next);
    }
    DBG_PING_L(DBG_SIGNAL_USB_TX_DONE);
    return 0;
}

#if 0
ATTR_TEXT_IN_TCM static int usb_tx_free(const struct device *dev)
{
    DBG_LOGI(thisMOD, "[Report log]usb_tx_free");
    return 0;
}
#endif

#if defined (CONFIG_AIR_NVIDIA_REFLEX_ENABLE)
ATTR_TEXT_IN_TCM static void hid_usb_ms_prepare_nv_report(uint8_t *in_buffer, uint8_t *out_buffer)
{
    int16_t x_in = in_buffer[2] | ((in_buffer[3] & 0x0F) << 8);
    int16_t y_in = (in_buffer[3] >> 4) | (in_buffer[4] << 4);
    /* int12 -> int16 */
    if(x_in & 0x800){
        x_in |= 0xF000;
    }
    if(y_in & 0x800){
        y_in |= 0xF000;
    }

    out_buffer[0] = REPORT_ID_NVIDIA_REFLEX;
    out_buffer[1] = in_buffer[1];
    out_buffer[2] = 0;
    out_buffer[3] = x_in & 0x00FF;
    out_buffer[4] = (x_in >> 8) & 0x00FF;
    out_buffer[5] = y_in & 0x00FF;
    out_buffer[6] = (y_in >> 8) & 0x00FF;
    out_buffer[7] = in_buffer[5];
    out_buffer[8] = AIR_USB_HID_GAMING_MS_NV_REPORT_ID;
    out_buffer[9] = usb_ms_key.latency & 0x00FF;
    out_buffer[10] = (usb_ms_key.latency >> 8) & 0x00FF;
    out_buffer[11] = 0;
    #if defined (CONFIG_DBG_REPORT_LOG)
    DBG_LOGI(thisMOD, "nv_payload = %x-%x-%x-%x-%x-%x-%x-%x",
            out_buffer[1],
            out_buffer[3], out_buffer[4], out_buffer[5],
            out_buffer[6], out_buffer[7],
            out_buffer[9], out_buffer[10]);
    #endif
}
#endif

ATTR_TEXT_IN_TCM static void hid_usb_ms_prepare_boot_protocol(uint8_t *in_buffer, uint8_t *out_buffer)
{
    out_buffer[0] = in_buffer[1];

    int16_t x_in = (in_buffer[2]) | ((in_buffer[3] & 0x0F) << 8);
    int16_t y_in = (in_buffer[4] << 4) | ((in_buffer[3] & 0xF0) >> 4);

    if (x_in & 0x800){  // negative number
        x_in |= 0xF000;
    }
    if (x_in < -128){
        x_in = -128;
    }
    else if (x_in > 127){
        x_in = 127;
    }
    if (y_in & 0x800){  // negative number
        y_in |= 0xF000;
    }
    if (y_in < -128){
        y_in = -128;
    }
    else if (y_in > 127){
        y_in = 127;
    }

    out_buffer[1] = (uint8_t)(x_in & 0xFF);
    out_buffer[2] = (uint8_t)(y_in & 0xFF);
    /* Byte 3~7 are reserved */
    out_buffer[3] = 0;
    out_buffer[4] = 0;
    out_buffer[5] = 0;
    out_buffer[6] = 0;
    out_buffer[7] = 0;
}

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
int hid_usb_device_register_init(const struct device *dev, air_usb_hid_report_desc_t *descs, size_t desc_count)
{
    int ret = 0;
    /* Register the HID device to airoha usb hid subsys */
    ret = air_usb_hid_device_register(dev);
    if(ret){
        DBG_LOGI(thisMOD, "air_usb_hid_device_register fail, dev = %p", dev);
        goto _failed_return;
    }

    /* Generate Report Descriptor for each device */
    ret = air_usb_hid_gen_rdesc(dev, descs, desc_count);
    if(ret){
        DBG_LOGI(thisMOD, "air_usb_hid_gen_rdesc fail, dev = %p", dev);
        goto _failed_return;
    }

    /* Register to Zephyr USB HID stack */
    int len = air_usb_hid_get_rdesc_len(dev);
    const uint8_t *rdesc = air_usb_hid_get_rdesc(dev);
    if (len > 0 && rdesc != NULL) {
        usb_hid_register_device(dev, rdesc, len, &airoha_usb_hid_ops);
    }
    else{
        DBG_LOGI(thisMOD, "air_usb_hid_get_rdesc or len fail, len = %d", len);
        ret = len;
        goto _failed_return;
    }

    ret = usb_hid_init(dev);
    if(ret){
        DBG_LOGI(thisMOD, "usb_hid_init fail, dev = %p", dev);
        goto _failed_return;
    }

_failed_return:
    if(ret){
        DBG_LOGI(thisMOD, "hid_usb_device_register_init fail, dev = %p, ret = %d", dev, ret);
        return 1;
    }
    DBG_LOGI(thisMOD, "hid_usb_device_register_init ok, dev = %p", dev);
    return 0;
}

bool hid_usb_device_set_init(const struct device *dev, uint8_t iface, bool set_nv)
{
    /* Set Protocol Code for each device */
    if (usb_hid_set_proto_code(dev, iface)) {
        DBG_LOGI(thisMOD, "Failed to set Protocol Code on USB HID Device, dev = %p", dev);
        return 1;
    }

    #if defined (CONFIG_AIR_NVIDIA_REFLEX_ENABLE)
    /* USB PKTDONE EINT Setup */
    if(set_nv){
        air_usb_hid_config_pktdone_eint(dev, 1, true, 0);
    }
    #endif

    int ret = air_usb_hid_register_protocol_change_cb(usb_user_id, dev, hid_usb_protocol_change_cb);
    if(ret){
        DBG_LOGI(thisMOD, "air_usb_hid_register_protocol_change_cb fail, dev = %p, ret = %d", dev, ret);
        return 1;
    }
    DBG_LOGI(thisMOD, "hid_usb_device_set_init ok, dev = %p", dev);
    return 0;
}

#if defined(CONFIG_AIR_USB_XINPUT_ENABLE)
void hid_register_usb_xinput_tx_done(const struct device *dev)
{
    int ret = air_usb_xinput_register_tx_done_cb(usb_user_id, dev, usb_xinput_tx_done);
    if(ret){
        DBG_LOGI(thisMOD, "hid_register_usb_xinput_tx_done fail, dev = %p", dev);
        return;
    }
    DBG_LOGI(thisMOD, "hid_register_usb_xinput_tx_done ok, dev = %p", dev);
}

void hid_register_usb_xinput_data_received(const struct device *dev)
{
    int ret = air_usb_xinput_register_data_received_cb(usb_user_id, dev, usb_xinput_data_receivced);
    if(ret){
        DBG_LOGI(thisMOD, "hid_register_usb_xinput_data_received fail, dev = %p", dev);
        return;
    }
    DBG_LOGI(thisMOD, "hid_register_usb_xinput_data_received ok, dev = %p", dev);
}
#endif /* CONFIG_AIR_USB_XINPUT_ENABLE */

void hid_register_usb_tx_done(uint8_t report_desc, uint8_t type, uint8_t report_id, uint8_t len)
{
    const struct device *hiddev = air_usb_hid_find_first_device_by_report(report_desc);
    int ret = air_usb_hid_register_tx_done_cb(usb_user_id, hiddev, type,
                                report_id, len, usb_tx_done);
    if(ret){
        DBG_LOGI(thisMOD, "hid_register_usb_tx_done fail, report_id = %d", report_id);
        return;
    }
    DBG_LOGI(thisMOD, "hid_register_usb_tx_done ok, report_id = %d", report_id);
}

ATTR_TEXT_IN_TCM static void hid_usb_set_func_exe_time_adjustment(uint8_t us_time)
{
    if(us_time != usb_reduce_time){
        // DBG_LOGI(thisMOD,"Total delay time = %d, additional reduce = %d->%d", USB_KEY_DELAY_TIME, usb_reduce_time, us_time);
        usb_reduce_time = us_time;
    }
    return;
}

ATTR_TEXT_IN_TCM static uint16_t hid_usb_timing_for_sof(void)
{
    static uint32_t start_point = 0;
    uint32_t delta_time = 0;
    uint32_t end_point = 0;

    if(!t0_point)
    {
        GPT_GET_FREE_RUN_COUNT_US(t0_point);
        if(!start_point){
            start_point = t0_point;
        }
        sof_cb_counter = 0;
        t0_delta_time = 0;
    }
    else
    {
        GPT_GET_FREE_RUN_COUNT_US(end_point);
        hal_gpt_get_duration_count(start_point, end_point, &delta_time);
        hal_gpt_get_duration_count(t0_point, end_point, &t0_delta_time);
        start_point = end_point;
        uint8_t temp_delay = (delta_time >= 125) ?
                             ((delta_time < (125 + USB_KEY_DELAY_TIME)) ? ((delta_time - 124)) : USB_KEY_DELAY_TIME) :
                             0;
        hid_common->hid.delay_for_key_polling_ms = temp_delay + usb_reduce_time;
    #ifdef CONFIG_DBG_HID_USB_SOF
        usb_sof_dbg.sum_time += delta_time;
        usb_sof_dbg.max_time = (delta_time > usb_sof_dbg.max_time) ? delta_time : usb_sof_dbg.max_time;
        usb_sof_dbg.min_time = (delta_time < usb_sof_dbg.min_time) ? delta_time : usb_sof_dbg.min_time;
    }
    usb_sof_dbg.sof_count++;
    #else
    }
    #endif /*_CONFIG_DBG_HID_USB_SOF_*/
    if(t0_delta_time >= 60000000) //1s
    {
        t0_point = end_point;
        sof_cb_counter = 0;
    }
    return delta_time;
}

static void hid_usb_mode_var_reset(void)
{
    usb_sof_status = false;
    usb_sof_first = false;
    t0_point = 0;
    sof_cb_counter = 0;
    t0_delta_time = 0;
}

#if defined(CONFIG_HID_USB_CHECK_FS_HS)
ATTR_TEXT_IN_TCM static uint16_t hid_usb_check_hs_fs(uint16_t cur_interval)
{
    /** Full-speed: 1000(us)/sof
     * rr  | count |  max_rr |  cur_rr
     * 8000:   1   =   1000  /   1000
     * 4000:   1   =   1000  /   1000
     * 2000:   1   =   1000  /   1000
     * 1000:   1   =   1000  /   1000
     *  500:   2   =   1000  /    500
     *  250:   4   =   1000  /    250
     *  125:   8   =   1000  /    125
    */
    static uint16_t last_speed = USB_MAX_HS_REPORT_RATE;

    if(!cur_interval || (cur_interval > 1100)){
        DBG_LOGI(thisMOD, "cur_interval = %d", cur_interval);
        return last_speed;
    }
    if(cur_interval > 900 && last_speed != USB_MAX_FS_REPORT_RATE)
    {
        last_speed = USB_MAX_FS_REPORT_RATE;
        if(hid_sof_count > 8){
            hid_sof_count = 1;
        }
    }
    else if(cur_interval < 200  && last_speed != USB_MAX_HS_REPORT_RATE) {
        last_speed = USB_MAX_HS_REPORT_RATE;
    }
    usb_report_count = last_speed / usb_report_rate;
    return last_speed;
}
#endif /*_CONFIG_HID_USB_CHECK_FS_HS_*/

static void hid_scenario_usb_timer_init()
{
    #ifdef CONFIG_DBG_HID_USB_SOF
    k_timer_init(&hid_usb_tx_count_timer, hid_usb_tx_count, NULL);
    #endif /*_CONFIG_DBG_HID_USB_SOF_*/
    k_timer_init(&check_suspend_timer, hid_usb_mode__check_suspend_timeout, NULL);
    k_timer_init(&resume_dummy_packet_timer, hid_usb_mode__resume_dummy_packet_cb, NULL);
}

static bool hid_scenario_usb_enable()
{
    int ret = air_usb_enable();
    if(ret)
    {
        DBG_LOGI(thisMOD, "air_usb_enable fail, ret = %d", ret);
        switch (ret)
        {
            case -ENOTCONN:
            {
                DBG_LOGI(thisMOD, "air_usb_enable fail, vbus not ready!");
                break;
            }
            default:
            {
                DBG_LOGI(thisMOD, "air_usb_enable fail, ret = %d", ret);
                assert(0 && "air_usb_enable fail!");
                break;
            }
        }
        return 1;
    }
    else{
        DBG_LOGI(thisMOD, "air_usb_enable ok");
    }
    return 0;
}

static bool hid_scenario_usb_disable()
{
    int ret = air_usb_disable();
    if(ret)
    {
        DBG_LOGI(thisMOD, "air_usb_disable fail, ret = %d", ret);
        assert(0 && "air_usb_disable fail!");
        return 1;
    }
    DBG_LOGI(thisMOD, "air_usb_disable ok");

    return 0;
}

#if defined (CONFIG_AIR_NVIDIA_REFLEX_ENABLE)
static void hid_usb_eint_cb()
{
    uint32_t hid_ms_tx_done_time = hal_eint_get_counter_value(EINT_COUNTER_NUMBER_5);
    if(hid_ms_tx_done_time)
    {
        hid_ms_get_key_timestamp(hid_ms_tx_done_time);
        const struct device *hiddev_ms_nv = air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_GAMING_MS_NV);
        hal_eint_unmask(HAL_EINT_USB0);
        air_usb_hid_clear_pktdone_eint(hiddev_ms_nv);
    }
}

static void hid_scenario_usb_eint_register(void)
{
    DBG_LOGI(thisMOD, "hid_scenario_usb_eint_register called");
    hal_eint_status_t ret_log[3];
    hal_eint_config_t eint_config;
    eint_config.trigger_mode = HAL_EINT_EDGE_FALLING;
    eint_config.debounce_time = 0;

    ret_log[0] = hal_eint_init(HAL_EINT_USB0, &eint_config);
    ret_log[1] = hal_eint_register_callback(HAL_EINT_USB0, (void *)hid_usb_eint_cb, NULL);
    hal_eint_enable(HAL_EINT_USB0);
    ret_log[2] = hal_eint_unmask(HAL_EINT_USB0);

    DBG_LOGI(thisMOD, "HAL_EINT_USB0, hal_eint_init = %d, hal_eint_register_callback = %d, hal_eint_unmask = %d"
        , ret_log[0]
        , ret_log[1]
        , ret_log[2]);

    hal_eint_counter_enable();
    hal_eint_set_counter_number(HAL_EINT_USB0, EINT_COUNTER_NUMBER_5);
}

ATTR_TEXT_IN_TCM static bool hid_usb_scenario__is_empty_report(uint8_t *data)
{
    return (data[1] == 0) && (data[2] == 0) &&
           (data[3] == 0) && (data[4] == 0) &&
           (data[5] == 0) && (data[6] == 0) && (data[7] == 0);
}
#endif /* CONFIG_AIR_NVIDIA_REFLEX_ENABLE */

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
bool hid_scenario_usb_register_callbacks(const hid_scenario_usb_callbacks_t *cbs)
{
    if(!cbs){
        return 1;
    }
    if(cbs->usb_cb){
        usb_mode_callback.usb_cb = cbs->usb_cb;
    }
    if(cbs->sof_cb){
        usb_mode_callback.sof_cb = cbs->sof_cb;
    }
    if(cbs->usb_evt_cb){
        usb_mode_callback.usb_evt_cb = cbs->usb_evt_cb;
    }
    return 0;
}

uint8_t hid_scenario_usb_mode_init()
{
    #if defined (CONFIG_AIR_NVIDIA_REFLEX_ENABLE)
    hid_scenario_usb_eint_register();
    #endif

    int ret = air_usb_create_user("HID_DEMO", &usb_user_id);
    if(ret){
        DBG_LOGI(thisMOD, "air_usb_create_user fail");
        return 1;
    }

    ret = air_usb_register_evt_cb(usb_user_id, hid_usb_evt_cb);
    if(ret){
        DBG_LOGI(thisMOD, "air_usb_register_evt_cb fail");
        return 1;
    }

    ret = air_usb_init();
    if(ret){
        DBG_LOGI(thisMOD, "air_usb_init fail, ret = %d", ret);
        return 1;
    }

    hid_scenario_usb_timer_init();
    DBG_LOGI(thisMOD, "hid_scenario_usb_mode_init end");
    return 0;
}

uint8_t hid_scenario_usb_mode_open(uint32_t link_idx, T_HID_SCENARIO_OPEN_TYPE_E parameter)
{
    DBG_LOGI(thisMOD, "hid_scenario_usb_mode_open link_idx = %d, usb_mode_state = 0x%X" ,link_idx, usb_mode_state);
    if(usb_mode_state == MODE_OPEN_USB_CONNECTED || usb_mode_state == MODE_OPEN_SPECIFIED){
        return 1;
    }
    usb_mode_state = MODE_OPEN_SPECIFIED;
    hal_nvic_set_priority(BT_IRQn, (DEFAULT_IRQ_PRIORITY + 3));
    hal_nvic_set_priority(OS_GPT_IRQn, (DEFAULT_IRQ_PRIORITY + 3));
    bt_ull_le_hid_dm_init();
    hid_usb_mode_var_reset();
    // Update report rate parameters after opened
    usb_report_rate = hid_scenario_read_now_report_rate(MODE_TYPE_USB);
    usb_report_count = USB_MAX_HS_REPORT_RATE / usb_report_rate;
    t0_point = 0;
    sof_cb_counter = 0;
    if(!usb_open_dvfs){
        usb_open_dvfs = true;
        hal_dvfs_lock_control(HAL_DVFS_OPP_HIGH, HAL_DVFS_LOCK);
    }

    usb_mode_state = MODE_OPEN_USB_CONNECTED;
    hid_scenario_send_state_update_notification(usb_mode_state, 0);

#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)
    epio_custom_protocol_enable(EPIO_CUSTOM_PROTOCOL_USB);
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE */

    return 0;
}

uint8_t hid_scenario_usb_mode_start(uint32_t link_idx, void* parameter)
{
    DBG_LOGI(thisMOD, "hid_scenario_usb_mode_start link_idx = %d, usb_mode_state = 0x%X" ,link_idx, usb_mode_state);

    switch(usb_mode_state)
    {
        case MODE_USB_STARTED:{
            goto _leave_func;
        }
        case MODE_USB_STOPPED:
        {
            int ret = air_usb_wakeup_request();
            if(ret)
            {
                if(ret == -EACCES)  //permission denied
                {
                    DBG_LOGI(thisMOD, "air_usb_wakeup_request fail, Device not allow to remote wakeup!");
                    usb_mode_state = MODE_STOPPED;
                    hid_scenario_send_state_update_notification(usb_mode_state, 0);
                    goto _leave_func;
                }
                else if(ret == -ENOTSUP)  //unsupppoeted value
                {
                    DBG_LOGI(thisMOD, "air_usb_wakeup_request fail, CONFIG_USB_DEVICE_REMOTE_WAKEUP=n");
                    goto _leave_func;
                }
            }
            else
            {
                DBG_LOGI(thisMOD, "air_usb_wakeup_request ok");
                k_timer_start(&resume_dummy_packet_timer, K_MSEC(SEND_RESUME_DUMMY_TIME) , K_NO_WAIT);
                goto _leave_func;
            }
            break;
        }
        default:{
            break;
        }
    }

    usb_mode_state = MODE_USB_STARTED;
    DBG_LOGI(thisMOD, "hid_scenario_usb_mode_start end, usb_mode_state = 0x%X", usb_mode_state);

    if(usb_mode_callback.usb_evt_cb){
        usb_mode_callback.usb_evt_cb(HID_USB_SEND_DUMMY_REPORT);
    }

    #ifdef CONFIG_DBG_HID_USB_SOF
        k_timer_stop(&hid_usb_tx_count_timer);
        k_timer_start(&hid_usb_tx_count_timer, K_SECONDS(USB_TX_COUNT_WAIT_TIME) , K_SECONDS(USB_TX_COUNT_WAIT_TIME));
    #endif /*_CONFIG_DBG_HID_USB_SOF_*/
    return 0;

_leave_func:
    return 1;
}

uint8_t hid_scenario_usb_mode_stop(uint8_t parameter)
{
    DBG_LOGI(thisMOD, "hid_scenario_usb_mode_stop, usb_mode_state = 0x%X", usb_mode_state);
    if(usb_mode_state == MODE_STOPPED || usb_mode_state == MODE_USB_STOPPED){
        return 1;
    }

    hid_common_clear_hid_exp_flag(FLAG_BIT_USB_CONNECTED);

    #ifdef CONFIG_DBG_HID_USB_SOF
    k_timer_stop(&hid_usb_tx_count_timer);
    #endif /*_CONFIG_DBG_HID_USB_SOF_*/

    usb_mode_state = MODE_STOPPED;
    hid_usb_mode_var_reset();
    hid_scenario_send_state_update_notification(usb_mode_state, 0);
    return 0;
}

uint8_t hid_scenario_usb_mode_close(uint8_t parameter)
{
    DBG_LOGI(thisMOD, "hid_scenario_usb_mode_close, usb_mode_state = 0x%X", usb_mode_state);
    if(usb_mode_state == MODE_CLOSED){
        return 1;
    }

    hal_nvic_set_priority(BT_IRQn, BT_IRQ_PRIORITY);
    hal_nvic_set_priority(OS_GPT_IRQn, OS_GPT_IRQ_PRIORITY);
    hid_common_clear_hid_exp_flag(FLAG_BIT_USB_CONNECTED);

    #ifdef CONFIG_DBG_HID_USB_SOF
    k_timer_stop(&hid_usb_tx_count_timer);
     #endif /*_CONFIG_DBG_HID_USB_SOF_*/

    if(usb_open_dvfs){
        usb_open_dvfs = false;
        hal_dvfs_lock_control(HAL_DVFS_OPP_HIGH, HAL_DVFS_UNLOCK);
    }

    usb_mode_state = MODE_CLOSED;
    hid_usb_mode_var_reset();

    hid_scenario_send_state_update_notification(usb_mode_state, REASON_CONNECTION_TERMINATED_BY_LOCAL_HOST);

#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)
    epio_custom_protocol_disable(EPIO_CUSTOM_PROTOCOL_USB);
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE */

    return 0;
}

void hid_scenario_usb_mode_config_rr(T_REPORT_RATE_CHANGE_S* change)
{
    uint8_t new_rr_idx = hid_scenario_report_rate_change(MODE_TYPE_USB, change->type, change->para, change->restore_or_chg_profile);
    usb_report_rate = hid_scenario_read_new_report_rate(MODE_TYPE_USB);

    /** High-speed: 125(us)/sof
     * rr  | count |  max_rr |  cur_rr
     * 8000:   1   =   8000  /   8000
     * 4000:   2   =   8000  /   4000
     * 2000:   4   =   8000  /   2000
     * 1000:   8   =   8000  /   1000
     *  500:  16   =   8000  /    500
     *  250:  32   =   8000  /    250
     *  125:  64   =   8000  /    125
    */
    usb_report_count = USB_MAX_HS_REPORT_RATE / usb_report_rate;
    cur_report_rate = hid_scenario_read_now_report_rate(MODE_TYPE_USB);
    //msmgr_mode_setting(2, new_report_rate);
    t0_point = 0;
    sof_cb_counter = 0;
    DBG_LOGI(thisMOD, "hid_scenario_usb_mode_config_rr, type = %d, para = %d, new_rr_idx = %d, new_report_rate = %d "
        , change->type
        , change->para
        , new_rr_idx
        , usb_report_rate
        );
}

uint8_t hid_scenario_usb_mode_config(T_HID_SCENARIO_CONFIG_PARA_S* config)
{
    switch(config->cfg_type)
    {
        case SCENARIO_SRV_CONFIG_REPORT_RATE:
        {
            hid_scenario_usb_mode_config_rr((T_REPORT_RATE_CHANGE_S*)config->value);
            break;
        }
        default:{
            return 1;
            break;
        }
    }
    return 0;
}

#if defined(CONFIG_AIR_USB_XINPUT_ENABLE)
ATTR_TEXT_IN_TCM void hid_usb_game_controller_covert_xinput_format(T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S *in_data, uint16_t in_len, T_HID_REPORT_GAME_CONTROLLER_XINPUT_PAYLOAD_S *out_data, uint16_t out_len)
{
    int32_t temp32 = 0;
    uint8_t hat_switch;

    memset(out_data, 0, out_len);
    out_data->report_id = 0x0;
    #if defined(CONFIG_AIR_USB_NO_REPORT_ID)
    out_data->report_size = 0x13;
    #else
    out_data->report_size = 0x14;
    #endif

    /* button process */
    /* Bit Field Description
        0 Dpad Up Dpad Up switch
        1 Dpad Down Dpad Down switch
        2 Dpad Left Dpad Left switch
        3 Dpad Right Dpad Right switch
        4 Start Start button
        5 Back Back button
        6 Left Thumbswitch Left Joystick switch
        7 Right Thumbswitch Right Joystick switch
        8 LeftShoulder Left Shoulder switch
        9 RightShoulder Right Shoulder switch
        10 Xe Xe Switch
        11 Binding Binding Switch
        12 A A button
        13 B B button
        14 X X button
        15 Y Y button
    */
    hat_switch = (in_data->hat_switch & 0x0f);
    switch (hat_switch)
    {
        case 0x1:
            hat_switch = 0x1; /* UP */
            break;

        case 0x2:
            hat_switch = 0x9; /* UP + RIGHT */
            break;

        case 0x3:
            hat_switch = 0x8; /* LEFT */
            break;

        case 0x4:
            hat_switch = 0xA; /* RIGHT + DOWN */
            break;

        case 0x5:
            hat_switch = 0x2; /* DOWN */
            break;

        case 0x6:
            hat_switch = 0x6; /* DOWN + LEFT */
            break;

        case 0x7:
            hat_switch = 0x4; /* LEFT */
            break;

        case 0x8:
            hat_switch = 0x5; /* LEFT + UP */
            break;

        default:
            break;
    }
    out_data->button = hat_switch
                        | (((in_data->button & 0x0600) >> 9) << 4)
                        | (((in_data->button & 0x00f0) >> 4) << 6)
                        | (((in_data->button & 0x0100) >> 8) << 10)
                        | ((in_data->button & 0x000f) << 12);

    /* trigger process */
    out_data->left_trigger = (in_data->breake >> 2) & 0xff;
    out_data->right_trigger = (in_data->accelerator >> 2) & 0xff;

    /* joystick data process */
    temp32 = in_data->x - JOYSTICK_0_LEVEL_VALUE;
    if (temp32 > 32767)
    {
        temp32 = 32767;
    }
    else if (temp32 < -32768)
    {
        temp32 = -32768;
    }
    out_data->left_x = temp32;
    temp32 = JOYSTICK_0_LEVEL_VALUE - in_data->y;
    if (temp32 > 32767)
    {
        temp32 = 32767;
    }
    else if (temp32 < -32768)
    {
        temp32 = -32768;
    }
    out_data->left_y = temp32;
    temp32 = in_data->z - JOYSTICK_0_LEVEL_VALUE;
    if (temp32 > 32767)
    {
        temp32 = 32767;
    }
    else if (temp32 < -32768)
    {
        temp32 = -32768;
    }
    out_data->right_x = temp32;
    temp32 = JOYSTICK_0_LEVEL_VALUE - in_data->rz;
    if (temp32 > 32767)
    {
        temp32 = 32767;
    }
    else if (temp32 < -32768)
    {
        temp32 = -32768;
    }
    out_data->right_y = temp32;
}
#endif /* CONFIG_AIR_USB_XINPUT_ENABLE */

ATTR_TEXT_IN_TCM void hid_scenario_usb_send_report(const struct device *dev, uint8_t *report)
{
    int ret = 0;
    if (report == NULL || hid_mode_state_check_tx() == false) {
        return;
    }
    bool tx_flag = true;
    uint8_t report_id = *report;
    // DBG_LOGI(thisMOD,"hid_scenario_usb_send_report, id = 0x%X", report_id);
    DBG_PING_H(DBG_SIGNAL_USB_TX);
    switch(report_id)
    {

        case REPORT_ID_MOUSE:
        {
            if(hid_usb_protocol == USB_PROTOCOL_REPORT_MODE)
            {
            #if defined(CONFIG_AIR_NVIDIA_REFLEX_ENABLE)
                bool need_merge = hid_usb_scenario__is_empty_report(report);
                if(need_merge && usb_ms_key.latency != 0)
                {
                    hid_nv_data[9] = (uint8_t)(usb_ms_key.latency & 0x00FF);
                    hid_nv_data[10] = (uint8_t)((usb_ms_key.latency >> 8) & 0x00FF);
                    DBG_LOGI(thisMOD, "[nv]merge_key_latency = %d", usb_ms_key.latency);
                    usb_ms_key.latency = 0;
                    usb_ms_key.curr_val = 0;
                #if defined(CONFIG_AIR_USB_NO_REPORT_ID)
                    T_HID_REPORT_MS_NV_S_NO_ID *usb_nv_report = (T_HID_REPORT_MS_NV_S_NO_ID *)((uint8_t *)hid_nv_data+1);
                    ret = air_usb_hid_tx(usb_user_id, dev, sizeof(T_HID_REPORT_MS_NV_S_NO_ID), (uint8_t *)usb_nv_report);
                #else
                    air_usb_hid_gaming_ms_nv_report_t *usb_nv_report = (air_usb_hid_gaming_ms_nv_report_t *)hid_nv_data;
                    ret = air_usb_hid_tx(usb_user_id, dev, sizeof(air_usb_hid_gaming_ms_nv_report_t), (uint8_t *)usb_nv_report);
                #endif /* CONFIG_AIR_USB_NO_REPORT_ID */
                }
                else
                {
                    hid_usb_ms_prepare_nv_report(report, &hid_nv_data[0]);
                    if(usb_ms_key.latency){
                        DBG_LOGI(thisMOD, "[nv]key_latency = %d", usb_ms_key.latency);
                        usb_ms_key.latency = 0;
                    }
                #if defined(CONFIG_AIR_USB_NO_REPORT_ID)
                    T_HID_REPORT_MS_NV_S_NO_ID *usb_nv_report = (T_HID_REPORT_MS_NV_S_NO_ID *)((uint8_t *)hid_nv_data+1);
                    usb_ms_key.curr_val = usb_nv_report->k;
                    ret = air_usb_hid_tx(usb_user_id, dev, sizeof(T_HID_REPORT_MS_NV_S_NO_ID), (uint8_t *)usb_nv_report);
                #else
                    air_usb_hid_gaming_ms_nv_report_t *usb_nv_report = (air_usb_hid_gaming_ms_nv_report_t *)hid_nv_data;
                    usb_ms_key.curr_val = usb_nv_report->button;
                    ret = air_usb_hid_tx(usb_user_id, dev, sizeof(air_usb_hid_gaming_ms_nv_report_t), (uint8_t *)usb_nv_report);
                #endif /* CONFIG_AIR_USB_NO_REPORT_ID */
                }
            #else
                {
                #if defined(CONFIG_AIR_USB_NO_REPORT_ID)
                    T_HID_MOUSE_REPORT_K8_S12_Z8_NO_ID *usb_ms_report = (T_HID_MOUSE_REPORT_K8_S12_Z8_NO_ID *)((uint8_t *)report+1);
                    usb_last_ms_key = usb_ms_report->ms_key;
                    ret = air_usb_hid_tx(usb_user_id, dev, sizeof(T_HID_MOUSE_REPORT_K8_S12_Z8_NO_ID), (uint8_t *)usb_ms_report);
                    #if defined (CONFIG_DBG_REPORT_LOG)
                    int16_t x_data = 0x00;
                    int16_t y_data = 0x00;
                    THREE_BYTES_TO_XY12(usb_ms_report->xy_val, x_data, y_data);
                    DBG_LOGI(thisMOD, "[Report log]ms_payload = %x-%x-%x-%x, ret = %d",
                            usb_ms_report->ms_key, x_data, y_data, usb_ms_report->wheel, ret);
                    #endif /* CONFIG_DBG_REPORT_LOG */
                #else
                    air_usb_hid_gaming_ms_report_t *usb_ms_report = (air_usb_hid_gaming_ms_report_t *)report;
                    usb_last_ms_key = usb_ms_report->button;
                    ret = air_usb_hid_tx(usb_user_id, dev, sizeof(air_usb_hid_gaming_ms_report_t), (uint8_t *)usb_ms_report);
                    #if defined (CONFIG_DBG_REPORT_LOG)
                    DBG_LOGI(thisMOD, "[Report log]ms_payload = %x-%x-%x-%x-%x",
                            usb_ms_report->report_id, usb_ms_report->button,
                            usb_ms_report->x, usb_ms_report->y, usb_ms_report->wheel);
                    #endif /* CONFIG_DBG_REPORT_LOG */
                #endif /* CONFIG_AIR_USB_NO_REPORT_ID */
                }
            #endif
            }
            else
            {
                uint8_t hid_boot_data[HID_USB_BIOS_DATA_LEN] = {0};
                hid_usb_ms_prepare_boot_protocol(report, &hid_boot_data[0]);
                ret = air_usb_hid_tx(usb_user_id, dev, HID_USB_BIOS_DATA_LEN, (uint8_t *)hid_boot_data);
            }

            break;
        }
        #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
        case REPORT_ID_KB_STD:
        {
            #if defined(CONFIG_AIR_USB_NO_REPORT_ID)
            T_HID_REPORT_KB_STD5_S_NO_ID *usb_kb_std_report = (T_HID_REPORT_KB_STD5_S_NO_ID *)((uint8_t *)report+1);
            ret = air_usb_hid_tx(usb_user_id, dev, sizeof(T_HID_REPORT_KB_STD5_S_NO_ID), (uint8_t *)usb_kb_std_report);
            #else
            T_HID_REPORT_KB_STD5_S *usb_kb_std_report = (T_HID_REPORT_KB_STD5_S *)report;
            usb_kb_std_report->report_id = AIR_USB_HID_GAMING_KB_REPORT_ID;
            ret = air_usb_hid_tx(usb_user_id, dev, sizeof(T_HID_REPORT_KB_STD5_S) - 1, (uint8_t *)usb_kb_std_report); /* Except dummy*/
            #endif /* CONFIG_AIR_USB_NO_REPORT_ID */
            break;
        }
        #endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */

        case REPORT_ID_KB_CONSUMER:
        {
            #if defined(CONFIG_AIR_USB_NO_REPORT_ID)
            T_HID_REPORT_KB_CONSUMER2_S_NO_ID *usb_kb_consumer_report = (T_HID_REPORT_KB_CONSUMER2_S_NO_ID *)((uint8_t *)report+1);
            ret = air_usb_hid_tx(usb_user_id, dev, sizeof(T_HID_REPORT_KB_CONSUMER2_S_NO_ID), (uint8_t *)usb_kb_consumer_report);
            #else
            T_HID_REPORT_KB_CONSUMER2_S *usb_kb_consumer_report = (T_HID_REPORT_KB_CONSUMER2_S *)report;
            usb_kb_consumer_report->report_id = AIR_USB_HID_CONSUMER_REPORT_ID;
            ret = air_usb_hid_tx(usb_user_id, dev, sizeof(T_HID_REPORT_KB_CONSUMER2_S) - 2, (uint8_t *)usb_kb_consumer_report); /* Except dummy*/
            #endif /* CONFIG_AIR_USB_NO_REPORT_ID */
            break;
        }
#if defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
        case REPORT_ID_KEYBOARD_NKEY:
        {
            #if defined(CONFIG_AIR_USB_NO_REPORT_ID)
            T_HID_REPORT_GAMING_KB_NK_S_NO_ID *kb_nkey_report = (T_HID_REPORT_GAMING_KB_NK_S_NO_ID *)((uint8_t *)report+1);
            ret = air_usb_hid_tx(usb_user_id, dev, sizeof(T_HID_REPORT_GAMING_KB_NK_S_NO_ID), (uint8_t *)kb_nkey_report);
            #else
            air_usb_hid_gaming_kb_nkey_report_t *kb_nkey_report = (air_usb_hid_gaming_kb_nkey_report_t *)report;
            kb_nkey_report->report_id = AIR_USB_REPORT_DESC_GAMING_KB_NKEY;
            ret = air_usb_hid_tx(usb_user_id, dev, sizeof(air_usb_hid_gaming_kb_nkey_report_t), (uint8_t *)kb_nkey_report);
            #endif /* CONFIG_AIR_USB_NO_REPORT_ID */
            break;
        }
#endif
#if defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
        case REPORT_ID_GAME_CONTROLLER:
        {
    #if defined(CONFIG_AIR_USB_NO_REPORT_ID)
        #if defined(CONFIG_AIR_USB_XINPUT_ENABLE)
            if (air_usb_mode_get() == USB_MODE_XINPUT)
            {
                T_HID_REPORT_GAME_CONTROLLER_XINPUT_PAYLOAD_S xusb_data;
                hid_usb_game_controller_covert_xinput_format((T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S *)usb_gp_report, sizeof(air_usb_hid_gamepad_report_t), &xusb_data, sizeof(T_HID_REPORT_GAME_CONTROLLER_XINPUT_PAYLOAD_S));
                T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S_NO_ID *usb_gp_report = (T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S_NO_ID *)((uint8_t *)xusb_data+1);
                ret = air_usb_xinput_tx(usb_user_id, dev, sizeof(T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S_NO_ID), (uint8_t *)&usb_gp_report);
            }
            else
        #endif /* CONFIG_AIR_USB_XINPUT_ENABLE */
            {
                T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S_NO_ID *usb_gp_report = (T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S_NO_ID *)((uint8_t *)report+1);
                ret = air_usb_hid_tx(usb_user_id, dev, sizeof(T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S_NO_ID), (uint8_t *)usb_gp_report);
            }
    #else
            air_usb_hid_gamepad_report_t *usb_gp_report = (air_usb_hid_gamepad_report_t *)report;
            usb_gp_report->report_id = AIR_USB_HID_GAMEPAD_REPORT_ID;
    #if defined(CONFIG_AIR_USB_XINPUT_ENABLE)
            if (air_usb_mode_get() == USB_MODE_XINPUT)
            {
                T_HID_REPORT_GAME_CONTROLLER_XINPUT_PAYLOAD_S xusb_data;
                hid_usb_game_controller_covert_xinput_format((T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S *)usb_gp_report, sizeof(air_usb_hid_gamepad_report_t), &xusb_data, sizeof(T_HID_REPORT_GAME_CONTROLLER_XINPUT_PAYLOAD_S));
                ret = air_usb_xinput_tx(usb_user_id, dev, sizeof(T_HID_REPORT_GAME_CONTROLLER_XINPUT_PAYLOAD_S), (uint8_t *)&xusb_data);
            }
            else
    #endif /* CONFIG_AIR_USB_XINPUT_ENABLE */
            {
                ret = air_usb_hid_tx(usb_user_id, dev, sizeof(air_usb_hid_gamepad_report_t), (uint8_t *)usb_gp_report);
            }
    #endif /* CONFIG_AIR_USB_NO_REPORT_ID */
            break;
        }
#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */

        default:{
            // DBG_LOGI(thisMOD, "Unknown report ID!!! = 0x%X", report_id);
            tx_flag = false;
            break;
        }
    }
    DBG_PING_L(DBG_SIGNAL_USB_TX);
    if(ret)
    {
        DBG_PING_H(DBG_SIGNAL_TX_NACK);
        DBG_PING_L(DBG_SIGNAL_TX_NACK);
        hid_common_set_hid_exp_flag(FLAG_BIT_USB_TX_NACK);
        #if defined(CONFIG_AIR_USB_EARLY_WAKEUP_CM33)
        hid_common->hid.outgoing_report_ready = USB_REPORT_TX_NACK;
        #endif
        #if defined (CONFIG_DBG_REPORT_LOG)
        DBG_LOGI(thisMOD, "[Report log]USB_TX_NACK, ret = %d", ret);
        #endif
        continue_tx_nack_cnt++;
    }
    else
    {
        hid_common_clear_hid_exp_flag(FLAG_BIT_USB_TX_NACK);
        #if defined(CONFIG_AIR_USB_EARLY_WAKEUP_CM33)
        hid_common->hid.outgoing_report_ready = USB_REPORT_TX_ACK;
        #endif
        #if defined (CONFIG_DBG_REPORT_LOG)
        if(continue_tx_nack_cnt)
        {
            DBG_LOGI(thisMOD, "[Report log] continue_tx_nack_cnt = %d", continue_tx_nack_cnt);
        }
        #endif
        continue_tx_nack_cnt = 0;
    }

    if(!usb_sof_status){
        DBG_LOGI(thisMOD, "[Report log] air_usb_hid_tx/air_usb_xinput_tx, ret = %d", ret);
        k_work_submit(&tx_nack_next);
    }

    #if defined (CONFIG_DBG_HID_USB_SOF)
    if(ret){
        usb_sof_dbg.tx_fail_count++;
    }
    else{
        usb_sof_dbg.tx_ok_count++;
    }
    #endif /*_CONFIG_DBG_HID_USB_SOF_*/

    if(tx_flag){
        tx_waiting_count++;
    };
    #if defined (AIR_SWLA_ENABLE)
    HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_usb_tx_send, SWLA_DIRECTION_STOP);
    #endif
}

uint8_t hid_scenario_usb_for_applaciton(uint8_t event)
{
    DBG_LOGI(thisMOD, "hid_scenario_usb_for_applaciton, event = %d", event);

    switch(event)
    {
        case HID_SCENARIO_APP_CHANGE_OPEN_STATUS:  //0
        {
            usb_mode_state = MODE_OPEN_USB_CONNECTED;
            hid_scenario_send_state_update_notification(usb_mode_state, 0);
            break;
        }
        case HID_SCENARIO_APP_USB_ENABLE:
        {
            hid_scenario_usb_enable();
            break;
        }
        case HID_SCENARIO_APP_USB_DISABLE:
        {
            hid_scenario_usb_disable();
            break;
        }
        case HID_SCENARIO_APP_USB_SOF_ON:
        {
            usb_sof_status = true;
            break;
        }
        default:{
            break;
        }
    }
    return 0;
}

#if defined(CONFIG_AIR_USB_EARLY_WAKEUP_CM33)
ATTR_TEXT_IN_TCM uint8_t hid_usb_mode__wait_for_ccni_send_ready(void)
{
    DBG_PING_H(DBG_SIGNAL_DEBUG_1);
    uint32_t start_time = 0;
    uint32_t end_time = 0;
    uint32_t delta_time = 0;
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &start_time);
    while((delta_time < USB_CM33_WAIT_FOR_CCNI_TIME) && (!hid_common->hid.outgoing_report_ready))
    {
        DBG_PING_L(DBG_SIGNAL_DEBUG_1);
        DBG_PING_H(DBG_SIGNAL_DEBUG_1);
        hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &end_time);
        hal_gpt_get_duration_count(start_time, end_time, &delta_time);
    }
    DBG_PING_L(DBG_SIGNAL_DEBUG_1);
    uint32_t report_ready = hid_common->hid.outgoing_report_ready;
    return report_ready;
}
#endif

uint8_t hid_scenario_usb_mode__get_state()
{
    return usb_mode_state;
}

#if defined(CONFIG_AIR_USB_XINPUT_ENABLE)
void hid_usb_mode__set_usb_mode(air_usb_mode_t mode)
{
    air_usb_mode_t hid_usb_mode = air_usb_mode_get();
    DBG_LOGI(thisMOD, "hid_usb_mode__set_usb_mode, usb_mode = %d", hid_usb_mode);
    air_usb_mode_set(mode);
    return;
}
#endif /* CONFIG_AIR_USB_XINPUT_ENABLE */

bool hid_scenario_usb_get_vbus()
{
    bool vbus = air_usb_is_vbus_ready();
    DBG_LOGI(thisMOD, "air_usb_is_vbus_ready, vbus = %d", vbus);

    return vbus;
}

void hid_usb_ep_flush(const struct device *dev, bool dir_in)
{
    if(!usb_ep_flush_flag)
    {
        usb_ep_flush_flag = true;
        air_usb_ep_flush(usb_user_id, dev, dir_in);
    }
}

#endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE */