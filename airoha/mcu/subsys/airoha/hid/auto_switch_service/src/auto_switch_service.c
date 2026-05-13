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

#if defined(CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER)

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include "bt_ull_le_hid_service.h"
#include "bt_ull_le_hid_conn_service.h"
#include "hid_critical_path.h"
#include "auto_switch_service.h"
#include "nvkey.h"

/* Private define ------------------------------------------------------------*/
#define thisMODULE  Auto_Switch_Service
#define thisMOD    "Auto_Switch_Service "
LOG_MODULE_REGISTER(thisMODULE);

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#define N_CHANNELS_TOP      8     // Best 8 channels
#define PER_SCALE           1000  // PER 1.0 = 1000
#define PER_BAD_THR         150   // 15.0%, BAD PER threshold
#define PER_SAFE_AVG        20    // 2.0%, SAFE AVG SNR threshold
#define PER_SAFE_AVG_BOOST  80    // 8.0%, SAFE AVG SNR threshold for boost distance
#define RR_SUC_RATE_MAX     950   // 95.0%
#define RR_SUC_RATE_MIN     700   // 70.0%
#define CHANNEL_NUMBER      40
#define WB_SCAN_DURATION_MAX    10000    // 10000 * 312.5us = 3.125 s


#if defined(CONFIG_AIR_HID_AUTO_SWITCH_PHY)
// Tx power & PHY Controller Number
#define TPC_PHY_MODE_NUM    7   
#else
#define TPC_PHY_MODE_NUM    6   
#endif

#define SNR_BOOST           15    // Boost Threshold
#define SNR_BOOST_DISTANCE  33    // Boost Distance Threshold
#define SNR_DROP            40    // Economy Drop Threshold
#define SNR_RECOVERY        40    // 2M -> 4M Recovery Threshold

#define MIN_SAFE_CH         4     // Boost trigger & Recovery requirement
#define MIN_DROP_CH         4     // Economy Drop requirement

#define STABLE_BOOST_LIMIT        2         // Continuous boost cnt
#define STABLE_DROP_LIMIT         4         // Continuous drop cnt when control tx power
#define STABLE_DROP_PHY_LIMIT     6         // Continuous drop phy cnt when switch phy
#define DEFAULT_PROFILE_IDX       3

static uint8_t current_idx = DEFAULT_PROFILE_IDX;
static uint8_t stable_boost_cnt = 0;
static uint8_t stable_drop_cnt = 0;
// static uint8_t stable_rr_check_high_cnt = 0;
// static uint8_t stable_rr_check_low_cnt = 0;

static bt_ull_le_hid_srv_device_t current_device;
static bt_ull_le_hid_srv_report_rate_level_t rr_level = BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_DEFAULT;
static auto_switch_control_param_t control_param;
static auto_switch_mode_t auto_switch_mode = AUTO_SWITCH_MODE_AUTO;

#define AUTO_SWITCH_SERVICE_STATE_NONE                  (0x00)
#define AUTO_SWITCH_SERVICE_STATE_DISCONNECTED          (0x01)
#define AUTO_SWITCH_SERVICE_STATE_CONNECTED             (0x02)
#define AUTO_SWITCH_SERVICE_STATE_REPORT_RATE_CHANGED   (0x03)
#define AUTO_SWITCH_SERVICE_STATE_MAX                   (0x04)
typedef uint8_t auto_switch_service_state_t;
auto_switch_service_state_t auto_switch_state = AUTO_SWITCH_SERVICE_STATE_NONE;

typedef struct {
    bool                        used;
    auto_switch_mode_t          mode;
} auto_switch_service_mode_nvkey_t;

typedef struct {
    bool                        used;
    uint8_t                     vpa;
    uint8_t                     tx_gc;
    uint8_t                     reserve[3];
} auto_switch_service_power_info_nvkey_t;

typedef struct
{
    bt_ull_le_srv_phy_t phy;
    uint8_t             vpa;    /* VPA voltage index: 0=0.96V, 1=1.2V, 2=1.45V */
    uint8_t             tx_gc;  /* TX Gain Control value */
} T_TPC_PHY_MODE_S;

/*
 * Transmit Power Control & PHY Mode Table
 * VPA encoding: 0 = 0.96V, 1 = 1.2V, 2 = 1.45V
 * TX_GC range: 0-61 (see TXGC-TXPower table)
 */
#if defined(CONFIG_AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
const T_TPC_PHY_MODE_S TPC_PHY_MODE[TPC_PHY_MODE_NUM] = {
    {BT_ULL_LE_SRV_PHY_LE_4M, AUTO_SWITCH_VPA_1_2V, 30},  // Idx 0 (4M, -8dBm):  Ultra-low power (VPA=1.2V)
    {BT_ULL_LE_SRV_PHY_LE_4M, AUTO_SWITCH_VPA_1_2V, 38},  // Idx 1 (4M, -4dBm):  Low power (VPA=1.2V)
    {BT_ULL_LE_SRV_PHY_LE_4M, AUTO_SWITCH_VPA_1_2V, 46},  // Idx 2 (4M,  0dBm):  Balanced (VPA=1.2V)
    {BT_ULL_LE_SRV_PHY_LE_4M, AUTO_SWITCH_VPA_1_2V, 54},  // Idx 3 (4M,  4dBm):  Default (VPA=1.2V) ← DEFAULT_PROFILE_IDX
    {BT_ULL_LE_SRV_PHY_LE_4M, AUTO_SWITCH_VPA_1_2V, 61},  // Idx 4 (4M,  8dBm):  Enhanced mode (VPA=1.2V)
    {BT_ULL_LE_SRV_PHY_LE_4M, AUTO_SWITCH_VPA_1_2V, 61},  // Idx 5 (4M, 10dBm):  4M highest power (VPA=1.2V)
    #if defined(CONFIG_AIR_HID_AUTO_SWITCH_PHY)
    {BT_ULL_LE_SRV_PHY_LE_2M, AUTO_SWITCH_VPA_1_2V, 61}   // Idx 6 (2M, 10dBm):  Survival mode (VPA=1.2V)
    #endif
};
#else
const T_TPC_PHY_MODE_S TPC_PHY_MODE[TPC_PHY_MODE_NUM] = {
    {BT_ULL_LE_SRV_PHY_LE_4M, AUTO_SWITCH_VPA_0_96V, 37},  // Idx 0 (4M, -8dBm):  Ultra-low power (VPA=0.96V)
    {BT_ULL_LE_SRV_PHY_LE_4M, AUTO_SWITCH_VPA_0_96V, 45},  // Idx 1 (4M, -4dBm):  Low power (VPA=0.96V)
    {BT_ULL_LE_SRV_PHY_LE_4M, AUTO_SWITCH_VPA_0_96V, 53},  // Idx 2 (4M,  0dBm):  Balanced (VPA=0.96V)
    {BT_ULL_LE_SRV_PHY_LE_4M, AUTO_SWITCH_VPA_0_96V, 61},  // Idx 3 (4M,  4dBm):  Default (VPA=0.96V) ← DEFAULT_PROFILE_IDX
    {BT_ULL_LE_SRV_PHY_LE_4M, AUTO_SWITCH_VPA_1_2V, 61},   // Idx 4 (4M,  8dBm):  Enhanced mode (VPA=1.2V)
    {BT_ULL_LE_SRV_PHY_LE_4M, AUTO_SWITCH_VPA_1_45V, 61},  // Idx 5 (4M, 10dBm):  4M highest power (VPA=1.45V)
    #if defined(CONFIG_AIR_HID_AUTO_SWITCH_PHY)
    {BT_ULL_LE_SRV_PHY_LE_2M, AUTO_SWITCH_VPA_1_45V, 61}   // Idx 6 (2M, 10dBm):  Survival mode (VPA=1.45V)
    #endif
};
#endif

static auto_switch_service_mode_nvkey_t       mode_nvkey;
static auto_switch_service_power_info_nvkey_t power_info_nvkey;
/* Public variables ----------------------------------------------------------*/
static auto_switch_callback auto_switch_cb;

/* Private functions ---------------------------------------------------------*/
static void auto_switch_conn_info_update(int8_t rx_rssi, int8_t* wb_rssi_arr, uint16_t* per_arr, uint8_t* ch_map);
static void auto_switch_ull_hid_le_callback(bt_ull_event_t event, void *param, uint32_t param_len);
// static void auto_switch_hid_critical_path_callback(uint32_t total_data_count, uint32_t normal_data_count, uint32_t report_rate);
static int8_t calculate_average_snr(int8_t rx_rssi, int8_t* wb_rssi_arr, uint8_t channel_num);
static void calculate_link_health(uint8_t* ch_map, uint16_t* per_arr, uint8_t* active_ch_num, uint8_t* good_ch_num, uint8_t* bad_ch_num, uint16_t* per_avr);
static int auto_switch_get_conn_info(uint8_t period);
static int auto_switch_set_tx_power(uint8_t current_idx, uint8_t next_idx);
#if defined(CONFIG_AIR_HID_AUTO_SWITCH_PHY)
static int auto_switch_set_phy(bt_ull_le_srv_phy_t phy);
#endif

static void calculate_link_health(uint8_t* ch_map, uint16_t* per_arr, uint8_t* active_ch_num, uint8_t* good_ch_num, uint8_t* bad_ch_num, uint16_t* per_avr)
{
    uint32_t per_sum = 0;
    uint8_t index = 0;
    for(uint8_t i = 0; i < CHANNEL_NUMBER/8; i++) {
        for(uint8_t j = 0; j < 8; j++) {
            if (ch_map[i] & (1 << j)) {
                (*active_ch_num)++;
                per_sum += per_arr[index];
                if (per_arr[index] > PER_BAD_THR) {
                    (*bad_ch_num)++;
                } else{
                    (*good_ch_num)++;
                }
                // LOG_ERR("calculate_link_health: per_sum:%d, active_ch_num:%d, good_ch_num:%d, bad_ch_num:%d, i:%d, j: %d, per_arr[%d]= %d", 
                // per_sum, *active_ch_num, *good_ch_num, *bad_ch_num, i, j, index, per_arr[index]);
            }
            index++;
        }
    }
    // LOG_INF("calculate_link_health: PER[0-7]:%02X %02X %02X %02X %02X %02X %02X %02X", per_arr[0], per_arr[1], per_arr[2], per_arr[3], per_arr[4], per_arr[5], per_arr[6], per_arr[7]);
    // LOG_INF("calculate_link_health: PER[8-15]:%02X %02X %02X %02X %02X %02X %02X %02X", per_arr[8], per_arr[9], per_arr[10], per_arr[11], per_arr[12], per_arr[13], per_arr[14], per_arr[15]);
    // LOG_INF("calculate_link_health: PER[16-23]:%02X %02X %02X %02X %02X %02X %02X %02X", per_arr[16], per_arr[17], per_arr[18], per_arr[19], per_arr[20], per_arr[21], per_arr[22], per_arr[23]);
    // LOG_INF("calculate_link_health: PER[24-31]:%02X %02X %02X %02X %02X %02X %02X %02X", per_arr[24], per_arr[25], per_arr[26], per_arr[27], per_arr[28], per_arr[29], per_arr[30], per_arr[31]);
    // LOG_INF("calculate_link_health: PER[32-39]:%02X %02X %02X %02X %02X %02X %02X %02X", per_arr[32], per_arr[33], per_arr[34], per_arr[35], per_arr[36], per_arr[37], per_arr[38], per_arr[39]);

    /* Calculate average PER, ensure per_avr is always initialized */
    if(*active_ch_num > 0){
        *per_avr = per_sum / *active_ch_num;
    } else {
        *per_avr = 0;  /* No active channels, set PER to 0 */
    }

}

static int8_t calculate_average_snr(int8_t rx_rssi, int8_t* wb_rssi_arr, uint8_t channel_num)
{
    if(channel_num > CHANNEL_NUMBER){
        LOG_ERR("Invalid channel number: %d", channel_num);
        return 0;
    }
    int8_t snr[CHANNEL_NUMBER] = {0};
    int8_t snr_temp = 0;
    int32_t snr_sum = 0;
    uint8_t i, j = 0;
    for(i = 0; i < CHANNEL_NUMBER; i++) {
        snr[i] = rx_rssi - wb_rssi_arr[i];
    }
    /* Sort the SNR array */
    for(i = 0; i < CHANNEL_NUMBER - 1; i++) {
        for(j = i + 1; j < CHANNEL_NUMBER; j++) {
            if (snr[i] < snr[j]){
                snr_temp = snr[i];
                snr[i] = snr[j];
                snr[j] = snr_temp;
            }
        }
    }
    for(i = 0; i < channel_num; i++){
        snr_sum+=snr[i];
    }
    return (int8_t)(snr_sum / channel_num); 
}

static int auto_switch_get_conn_info(uint8_t period)
{
    LOG_INF("auto_switch_get_conn_info period: %d, dt: %d", period, current_device);
    bt_ull_le_hid_srv_get_conn_quality_info_t action_param;
    action_param.device_type = current_device;
    action_param.update_period = period;
    return bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_GET_CONNECION_QUALITY_INFO, &action_param, sizeof(action_param));
}

static int auto_switch_set_tx_power(uint8_t current_idx, uint8_t next_idx)
{
    /* Boundary check to prevent array out-of-bounds access */
    if (next_idx >= TPC_PHY_MODE_NUM) {
        LOG_ERR(thisMOD"Invalid next_idx: %d (max: %d)", next_idx, TPC_PHY_MODE_NUM - 1);
        return -EINVAL;
    }

    if (current_idx >= TPC_PHY_MODE_NUM) {
        LOG_WRN(thisMOD"Invalid current_idx: %d (max: %d)", current_idx, TPC_PHY_MODE_NUM - 1);
    }

    LOG_INF(thisMOD"auto_switch_set_tx_power, current_idx: %d, next_idx: %d, vpa: %d (%.2fV), tx_gc: %d",
            current_idx, next_idx, TPC_PHY_MODE[next_idx].vpa,
            TPC_PHY_MODE[next_idx].vpa == 0 ? 0.96 : (TPC_PHY_MODE[next_idx].vpa == 1 ? 1.2 : 1.45),
            TPC_PHY_MODE[next_idx].tx_gc);

    auto_switch_set_vap_tx_gc(TPC_PHY_MODE[next_idx].vpa, TPC_PHY_MODE[next_idx].tx_gc);
    return 0;
}

#if defined(CONFIG_AIR_HID_AUTO_SWITCH_PHY)
static int auto_switch_set_phy(bt_ull_le_srv_phy_t phy)
{
    LOG_INF("auto_switch_set_phy: %d, report_rate: %d", phy, rr_level);
    if((rr_level == BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_8) && (phy != BT_ULL_LE_SRV_PHY_LE_4M)){
        LOG_INF("auto_switch_set_phy error, not support!");
        return -1;
    }
    bt_ull_le_hid_srv_report_rate_t action_param;
    action_param.phy = phy;
    action_param.rr_level = rr_level;
    return bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_SET_REPORT_RATE, &action_param, sizeof(action_param));
}
#endif

/**
* @brief Smart TPC Update Function (Call every n * 500ms)
* @param rx_rssi      Receiver RSSI (dBm)
* @param wb_rssi_arr  Background Noise Array [CHANNEL_NUMBER] (dBm)
* @param per_arr      Packet Error Rate Array [CHANNEL_NUMBER] (0-1000)
* @param ch_map       Active Channel Bitmask[CHANNEL_NUMBER/8] (bit0-bit39)
*/
static void auto_switch_conn_info_update(int8_t rx_rssi, int8_t* wb_rssi_arr, uint16_t* per_arr, uint8_t* ch_map)
{
    // 1. Calculate Predicted SNR (Top-N Avg)
    // ... (Sorting logic to find top N_CHANNELS_TOP SNRs) ...
    int8_t snr_pred = calculate_average_snr(rx_rssi, wb_rssi_arr, control_param.good_ch_cnt);

    // 2. Analyze Link Health
    uint8_t num_active = 0;
    uint8_t bad_ch_cnt = 0;
    uint8_t good_ch_cnt = 0;
    uint16_t per_avr;
    calculate_link_health(ch_map, per_arr, &num_active, &good_ch_cnt, &bad_ch_cnt, &per_avr);
    if (num_active == 0) {
        LOG_INF(thisMOD"auto_switch_conn_info_update: return : %d", num_active);
        return; // Error protection
    }
    if(auto_switch_cb){
        auto_service_link_quality_t link_quality;
        link_quality.rx_rssi = rx_rssi;
        link_quality.aver_per = per_avr;
        link_quality.snr_perd = snr_pred;
        auto_switch_cb(AUTO_SWITCH_EVENT_LINK_QUALITY_IND, &link_quality, sizeof(auto_service_link_quality_t));
    }
    if(auto_switch_mode == AUTO_SWITCH_MODE_MANUAL){
        LOG_INF(thisMOD"auto_switch_conn_info_update: return mode : %d", auto_switch_mode);
        auto_switch_stop();
        return; // Error protection
    }
    // 3. Decision Matrix
    uint8_t next_idx = current_idx;

    // --- Logic A: Boost ---
    // Only boost if cornered [low channels] AND [weak signal]
    if (((good_ch_cnt < MIN_SAFE_CH) && (snr_pred < control_param.snr_boost))
        || (snr_pred < control_param.snr_boost_distance)
        || (PER_SAFE_AVG_BOOST < per_avr)) {
        stable_boost_cnt++;
        if (stable_boost_cnt >= control_param.stable_boost_limit) {
            if (current_idx < TPC_PHY_MODE_NUM - 1) {
                next_idx++;
            }
            stable_boost_cnt = 0;
        }
        stable_drop_cnt = 0;
    }
    
    // --- Logic B: Drop ---
    else {
        bool safe_to_drop = false;
        stable_boost_cnt = 0;
        // Scenario 1: Recovery (2M -> 4M)
        #if defined(CONFIG_AIR_HID_AUTO_SWITCH_PHY)
        if (current_idx == (TPC_PHY_MODE_NUM - 1)) {
            if ((snr_pred > control_param.snr_recovery_phy) &&
                (per_avr < PER_SAFE_AVG) &&
                (good_ch_cnt >= MIN_SAFE_CH)) {
                safe_to_drop = true;
            }
        }
        // Scenario 2: Economy (4M Power Drop)
        else 
        #endif
        {
            if ((snr_pred > control_param.snr_drop) &&
                (per_avr < PER_SAFE_AVG) &&
                (good_ch_cnt >= MIN_DROP_CH)) {
                safe_to_drop = true;
            }
        }

        if (safe_to_drop) {
            stable_drop_cnt++;
            uint8_t limit = control_param.stable_drop_limit ;
            if (TPC_PHY_MODE[current_idx].phy == BT_ULL_LE_SRV_PHY_LE_2M) {
                limit = control_param.stable_drop_phy_limit;
            }
            if (stable_drop_cnt >= limit) {
                if (current_idx > 0) {
                    next_idx--;
                }
                stable_drop_cnt = 0;
            }
        } else {
            stable_drop_cnt = 0;
        }
    }
    LOG_INF(thisMOD"auto_switch_conn_info_update: Rx_RSSI:%d, SNR_Pred: %d, AVR_PER: %d, total_ch_cnt: %d, good_ch_cnt:%d, Cur_idx:%d, stable_drop_cnt: %d, stable_boost_cnt: %d", 
            rx_rssi, snr_pred, per_avr, good_ch_cnt+bad_ch_cnt,good_ch_cnt, current_idx, stable_drop_cnt, stable_boost_cnt);
    // 4. Apply Changes
    if (next_idx != current_idx) {
        stable_boost_cnt = 0;
        stable_drop_cnt = 0;
        if (next_idx >= TPC_PHY_MODE_NUM) {
            next_idx = TPC_PHY_MODE_NUM - 1;
            current_idx = next_idx;
        }
        if (((next_idx < DEFAULT_PROFILE_IDX) && (rr_level > BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_5)) || 
            (auto_switch_state < AUTO_SWITCH_SERVICE_STATE_CONNECTED)){
            return;
        }
        LOG_INF(thisMOD"Switching to index: from %d to %d", current_idx, next_idx);
        auto_switch_set_tx_power(current_idx, next_idx);
        #if defined(CONFIG_AIR_HID_AUTO_SWITCH_PHY)
        if (TPC_PHY_MODE[current_idx].phy != TPC_PHY_MODE[next_idx].phy){
            auto_switch_set_phy(TPC_PHY_MODE[next_idx].phy);
        }
        #endif
        current_idx = next_idx;
    }
}

static void auto_switch_recover_setting(void)
{
    auto_switch_mode_t mode = auto_switch_get_mode();
    LOG_INF(thisMOD"auto_switch_recover_setting, mode: %d", mode);
    if(mode == AUTO_SWITCH_MODE_MANUAL) {
        /* read vpa & tx_gc from nvkey */
        if(power_info_nvkey.used)
        {
            auto_switch_set_vap_tx_gc(power_info_nvkey.vpa, power_info_nvkey.tx_gc);
        }
    } else {
        current_idx = DEFAULT_PROFILE_IDX;
        auto_switch_set_tx_power(current_idx, DEFAULT_PROFILE_IDX);
    }
}

void auto_switch_ull_hid_le_callback(bt_ull_event_t event, void *param, uint32_t param_len)
{
    LOG_INF(thisMOD"auto_switch_ull_hid_le_callback, event: %d", event);
    switch (event) {
        case BT_ULL_EVENT_LE_HID_CONN_QUALITY_INFO_IND: 
        {
            bt_ull_le_hid_conn_srv_msg_conn_info_t *conn_info = (bt_ull_le_hid_conn_srv_msg_conn_info_t *)param;
            // uint32_t duration = (conn_info->wb_duration * 312.5) / 1000000;
            LOG_INF(thisMOD"auto_switch_ull_hid_le_callback, status: %x, phy: %x, tx_power: %x, duration: %d (uint:312.5us), channel_map: %02X%02X%02X%02X%02X", \
                conn_info->status, conn_info->phy, conn_info->tx_power, conn_info->wb_duration,
                conn_info->channel_map[0], conn_info->channel_map[1],
                conn_info->channel_map[2], conn_info->channel_map[3], conn_info->channel_map[4]);

            if ((current_idx != (TPC_PHY_MODE_NUM - 1)) && (conn_info->phy == BT_ULL_LE_SRV_PHY_LE_2M)){
                LOG_ERR(thisMOD"idx && phy error! current_idx=%d, phy=%d", current_idx, conn_info->phy);
            }
            auto_switch_conn_info_update(conn_info->rx_rssi,
                                        (int8_t *)&conn_info->wb_rssi,  /* RSSI is signed */
                                        (uint16_t *)&conn_info->PER,
                                        (uint8_t *)&conn_info->channel_map);
        }
        break;
        case BT_ULL_EVENT_LE_HID_CONNECTED_IND:
        {
            LOG_INF(thisMOD"CONNECTED EVENT");
            auto_switch_state = AUTO_SWITCH_SERVICE_STATE_CONNECTED;
            auto_switch_recover_setting();
        }
        break;
        case BT_ULL_EVENT_LE_HID_DISCONNECTED_IND: 
        {
            LOG_INF(thisMOD"DISCONNECTED EVENT");
            auto_switch_state = AUTO_SWITCH_SERVICE_STATE_DISCONNECTED;
            current_idx = DEFAULT_PROFILE_IDX;
        }
        break;
        case BT_ULL_EVENT_LE_HID_REPORT_RATE_CHANGE_IND:
        {
            bt_ull_le_hid_srv_report_rate_change_ind_t*  rr_ind = (bt_ull_le_hid_srv_report_rate_change_ind_t *)param;
            if (rr_level != rr_ind->report_rate.rr_level) {
                auto_switch_recover_setting();
            }
            rr_level = rr_ind->report_rate.rr_level;
            LOG_INF(thisMOD"REPORT RATE CHANGE EVENT, rr_level: %d, phy: %d", rr_level, rr_ind->report_rate.phy);
        }
        break;
        default:
            break;
        
    }
}

int auto_switch_start(void)
{
    return auto_switch_get_conn_info(1);
}

int auto_switch_stop(void)
{
    return auto_switch_get_conn_info(0);
}

int auto_switch_set_parameter(auto_switch_control_param_t *param)
{
    control_param.snr_boost = param->snr_boost;
    control_param.snr_boost_distance = param->snr_boost_distance;
    control_param.snr_drop = param->snr_drop;
    control_param.snr_recovery_phy = param->snr_recovery_phy;
    control_param.stable_boost_limit = param->stable_boost_limit;
    control_param.stable_drop_limit = param->stable_drop_limit;
    control_param.stable_drop_phy_limit = param->stable_drop_phy_limit;
    control_param.good_ch_cnt = param->good_ch_cnt;
    LOG_INF(thisMOD"auto_switch_set_parametersnr_boost: %d, snr_boost_distance: %d, snr_drop: %d, snr_recovery_phy: %d, stable_boost_limit: %d, stable_drop_limit: %d, stable_drop_phy_limit: %d, good_cnt: %d", 
            control_param.snr_boost, control_param.snr_boost_distance, 
            control_param.snr_drop, control_param.snr_recovery_phy, control_param.stable_boost_limit, 
            control_param.stable_drop_limit, control_param.stable_drop_phy_limit, control_param.good_ch_cnt);
    return 0;
}

int auto_switch_control(uint8_t control)
{
    LOG_INF(thisMOD"auto_switch_control, control: %d", control);
    if (control) {
        auto_switch_start();
    } else{
        auto_switch_stop();
    }
    return 0;
}

void auto_switch_set_power_info(uint8_t vpa, uint8_t tx_gc)
{
    /* Store power info to NVKey */
    nvkey_status_t status = NVKEY_STATUS_ERROR;
    uint32_t info_size = sizeof(auto_switch_service_power_info_nvkey_t);
    power_info_nvkey.used = 1;
    power_info_nvkey.vpa = vpa;
    power_info_nvkey.tx_gc = tx_gc;
    status = nvkey_write_data(NVID_APP_DYNAMIC_POWER_CONTROL_INFO, (uint8_t *)&power_info_nvkey, info_size);
    LOG_INF(thisMOD"auto_switch_set_power_info, vpa: %d, tx_gc: %d, nv_status: %d", vpa, tx_gc, status);

    /* Apply immediately if in manual mode and connected */
    if (auto_switch_mode == AUTO_SWITCH_MODE_MANUAL &&
        auto_switch_state >= AUTO_SWITCH_SERVICE_STATE_CONNECTED) {
        auto_switch_set_vap_tx_gc(vpa, tx_gc);
        LOG_INF(thisMOD"auto_switch_set_power_info: applied immediately in manual mode");
    }
}

void auto_switch_set_mode(auto_switch_mode_t mode)
{
    auto_switch_mode = mode;
    /* store the mode in nvkey */
    nvkey_status_t status = NVKEY_STATUS_ERROR;
    uint32_t mode_size = sizeof(auto_switch_service_mode_nvkey_t);
    mode_nvkey.used = 1;
    mode_nvkey.mode = mode;
    status = nvkey_write_data(NVID_APP_POWER_CONTROL_MODE, (uint8_t *)&mode_nvkey, mode_size);
    if(auto_switch_mode == AUTO_SWITCH_MODE_AUTO){
        auto_switch_start();
        current_idx = DEFAULT_PROFILE_IDX;
        /* Apply default power setting immediately if connected */
        if (auto_switch_state >= AUTO_SWITCH_SERVICE_STATE_CONNECTED) {
            auto_switch_set_tx_power(current_idx, DEFAULT_PROFILE_IDX);
            LOG_INF(thisMOD"auto_switch_set_mode: applied default power in auto mode");
        }
    } else {
        auto_switch_stop();
        /* Apply saved power info immediately if connected and power_info is valid */
        if (auto_switch_state >= AUTO_SWITCH_SERVICE_STATE_CONNECTED && power_info_nvkey.used) {
            auto_switch_set_vap_tx_gc(power_info_nvkey.vpa, power_info_nvkey.tx_gc);
            LOG_INF(thisMOD"auto_switch_set_mode: applied saved power info in manual mode (vpa=%d, tx_gc=%d)",
                    power_info_nvkey.vpa, power_info_nvkey.tx_gc);
        }
    }
    LOG_INF(thisMOD"auto_switch_set_mode, mode: %d,nv_status: %d", mode, status);
}

auto_switch_mode_t auto_switch_get_mode(void)
{
    LOG_INF(thisMOD"auto_switch_get_mode, mode: %d", auto_switch_mode);
    return auto_switch_mode;
}

int auto_switch_set_vap_tx_gc(uint8_t vpa, uint8_t tx_gc)
{
    /* Set VPA and TX_GC */
    LOG_INF(thisMOD"auto_switch_set_vap_tx_gc, dt: %d, vpa: %d, tx_gc: %d", current_device, vpa, tx_gc);
    bt_ull_le_hid_srv_set_vpa_tx_gc_t vpa_tx_gc;
    vpa_tx_gc.device_type = current_device;
    vpa_tx_gc.tx_gc = tx_gc;
    vpa_tx_gc.pa_vol = vpa;
    bt_ull_le_hid_srv_action(BT_ULL_ACTION_LE_HID_SET_VPA_TX_GC, &vpa_tx_gc, sizeof(bt_ull_le_hid_srv_set_vpa_tx_gc_t));
    return 0;
}

int auto_switch_init(void)
{
    /* Register ull_hid_le_callback */
    #ifdef CONFIG_AIR_PURE_GAMING_DONGLE_KB_ENABLE
    current_device = BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD;
    #elif CONFIG_AIR_PURE_GAMING_DONGLE_MS_ENABLE
    current_device = BT_ULL_LE_HID_SRV_DEVICE_MOUSE;
    #elif CONFIG_AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE
    current_device = BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD;
    #endif

    control_param.snr_boost = SNR_BOOST;
    control_param.snr_boost_distance = SNR_BOOST_DISTANCE;
    control_param.snr_drop = SNR_DROP;
    control_param.snr_recovery_phy = SNR_RECOVERY;
    control_param.stable_boost_limit = STABLE_BOOST_LIMIT;
    control_param.stable_drop_limit = STABLE_DROP_LIMIT;
    control_param.stable_drop_phy_limit = STABLE_DROP_PHY_LIMIT;
    control_param.good_ch_cnt = N_CHANNELS_TOP;
    auto_switch_state = AUTO_SWITCH_SERVICE_STATE_NONE;
    int ret = bt_ull_le_hid_srv_register_callback(BT_ULL_LE_HID_SRV_MODULE_AUTO_SWTICHER, auto_switch_ull_hid_le_callback);
    LOG_INF(thisMOD"auto_switch_init, ret: %d, dt: %d, snr_boost: %d, snr_boost_distance: %d, snr_drop: %d, snr_recovery_phy: %d, stable_boost_limit: %d, stable_drop_limit: %d, stable_drop_phy_limit: %d", 
            ret, current_device, control_param.snr_boost, control_param.snr_boost_distance, 
            control_param.snr_drop, control_param.snr_recovery_phy, control_param.stable_boost_limit, 
            control_param.stable_drop_limit, control_param.stable_drop_phy_limit);
    
    /* Read auto_switch_mode and power_info from NVKey */
    nvkey_status_t status = NVKEY_STATUS_ERROR;
    uint32_t mode_size = sizeof(auto_switch_service_mode_nvkey_t);
    uint32_t info_size = sizeof(auto_switch_service_power_info_nvkey_t);
    memset(&mode_nvkey, 0, mode_size);
    memset(&power_info_nvkey, 0, info_size);

    /* Read mode from NVKey */
    status = nvkey_read_data(NVID_APP_POWER_CONTROL_MODE, (uint8_t *)&mode_nvkey, &mode_size);
    if (NVKEY_STATUS_OK != status && NVKEY_STATUS_ITEM_NOT_FOUND != status) {
        LOG_ERR(thisMOD"auto_switch_init, mode read error status:%d, size: %d", status, mode_size);
        return -EPERM;
    } else {
        LOG_INF(thisMOD"auto_switch_init, mode used:%d, mode: %d", mode_nvkey.used, mode_nvkey.mode);

        /* Restore mode from NVKey if valid */
        if (mode_nvkey.used && (status == NVKEY_STATUS_OK)) {
            auto_switch_mode = mode_nvkey.mode;
            LOG_INF(thisMOD"auto_switch_init: restored mode from NVKey: %d", auto_switch_mode);
        } else {
            /* Use default mode if NVKey not found or not used */
            LOG_INF(thisMOD"auto_switch_init: using default mode: %d", auto_switch_mode);
        }
    }

    /* Read power info from NVKey */
    status = nvkey_read_data(NVID_APP_DYNAMIC_POWER_CONTROL_INFO, (uint8_t *)&power_info_nvkey, &info_size);
    if (NVKEY_STATUS_OK != status && NVKEY_STATUS_ITEM_NOT_FOUND != status) {
        LOG_ERR(thisMOD"auto_switch_init, power_info read error status:%d, size: %d", status, info_size);
        return -EPERM;
    } else {
        LOG_INF(thisMOD"auto_switch_init, power_info used:%d, vpa: %d, tx_gc: %d",
                power_info_nvkey.used, power_info_nvkey.vpa, power_info_nvkey.tx_gc);
    }

    return ret;
}

void auto_switch_deinit(void)
{
    current_device = BT_ULL_LE_HID_SRV_DEVICE_NONE;
    auto_switch_state = AUTO_SWITCH_SERVICE_STATE_NONE;
    auto_switch_mode = AUTO_SWITCH_MODE_AUTO;
    /* Unregister hid_critical_path_callback */
    /* RegUnregisterister ull_hid_le_callback */
}

int auto_switch_srv_register_callback(auto_switch_callback cb)
{
    LOG_INF("auto_switch_srv_register_callback: 0x%x", cb);
    auto_switch_cb = cb;
    return 0;
}

#endif/* CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER */
