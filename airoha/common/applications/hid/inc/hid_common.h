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

#ifndef _HID_COMMON_H_
#define _HID_COMMON_H_

#if defined(AIR_HID_COMMON_SERVICE)

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "hid_common_debug.h"
#include "hid_common_ccni_msg.h"
#include "hid_common_report_rate.h"
#include "hid_common_hid_app_states.h"
#include "hid_common_key_remap.h"
#include "hid_common_usb.h"
#include "hid_common_report_structure.h"
#include "hid_common_button.h"

#if defined(CONFIG_AIR_ACL_PACKET_VIA_HID_REPORT) || defined(AIR_ACL_PACKET_VIA_HID_REPORT)
#include "hid_common_acl_rsp_via_hid.h"
#endif

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
#if defined(CORE_MCU)
#include "hal_platform.h"
#else
#include "hal_saradc.h"
#endif
#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */

/* Public define -------------------------------------------------------------*/

#define MAX_PROFILE_COUNT 4
#define DEFAULT_PROFILE_IDX   0
#define RISCV_MAX_KEY_NUM 10

/* Public typedef ------------------------------------------------------------*/
typedef struct
{
    uint8_t id;
    uint8_t para;
}T_OUTPUT_CTRL_PIN_INFO_S;

typedef struct {
    #if !defined(AIR_USB_CCNI_WAKEUP_CM33) && !defined(CONFIG_AIR_USB_EARLY_WAKEUP_CM33)
    uint8_t ccni_msg_id;
    #endif
    union{
        T_HID_REPORT_MS_K8_S16_Z8_S    ms_s16_z8;  // Key 8bits, Sensor 16 bits; Z data(wheel/pan) 8 bits
        #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_PRODUCT_TYPE_MOUSE)
        T_HID_REPORT_KB_STD2_XY_S       kb_std2;
        T_HID_REPORT_KB_CONSUMER1_XY_S  kb_consumer1;
        #endif
        T_HID_REPORT_KB_STD5_S          kb_std5;
        T_HID_REPORT_KB_CONSUMER2_S     kb_consumer2;
        #if defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER) || defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
        T_HID_REPORT_GAME_CONTROLLER_USB_PAYLOAD_S gc_usb_payload;
        #endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */
    };
}__packed T_HID_CCNI_USB_REPORT_S;

typedef struct {
    uint32_t combo_bit_00_31;
    uint32_t combo_bit_32_63;
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    uint32_t combo_bit_64_95;
#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */
}T_AIR_COMBO_KEY_S;

typedef struct {
    uint8_t     step_wired;      /** interval_time    = 125 * interval */
    uint8_t     step_2_4g;       /** interval_time    = 125 * interval */
    uint8_t     step_bt;         /** interval_time_bt = 1000 * interval_bt */
} T_DEBOUNCE_PARA_S;

typedef struct {
    uint8_t     step_bt;    /** interval_time_bt = 1000 * interval_bt */
    uint8_t     step;       /** interval_time    = 125 * interval */
} T_RACE_CMD_DEBOUNCE_PARA_S;

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
typedef struct {
    uint32_t status;
} T_GAME_CONTROLLER_EXPAND_IO_PARA_S;

typedef struct {
    hal_saradc_data_t saradc_data;
} T_GAME_CONTROLLER_ADC_PARA_S;
#endif

typedef struct {
    uint32_t hid_scenario_type;
    uint32_t dongle_scenario;
    uint32_t flags;
    uint32_t features;
    volatile uint32_t outgoing_report_ready;
    uint8_t delay_for_key_polling_ms;                   /** delay time in ms for key polling. this is used to get best key latency */
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    T_GAME_CONTROLLER_EXPAND_IO_PARA_S expand_io;
    T_GAME_CONTROLLER_ADC_PARA_S adc;
    uint32_t x;
    uint32_t y;
    uint32_t z;
    uint32_t rz;
    uint32_t lt;
    uint32_t rt;
#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */

    #if defined(CONFIG_AIR_ACL_PACKET_VIA_HID_REPORT) || defined(AIR_ACL_PACKET_VIA_HID_REPORT)
    T_ACL_PACKET_QUEUE_S acl_pkt_queue;
    #endif

} hid_shared_parameters;

typedef struct {
    uint32_t features;
    uint32_t inActivity_timeout;

    #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_PRODUCT_TYPE_MOUSE)
    const T_AIR_COMBO_KEY_S *combo_key_list;
    uint32_t combo_key_list_size;
    uint32_t hold_timeout;

    T_OUTPUT_CTRL_PIN_INFO_S irpt_ctrl;
    T_OUTPUT_CTRL_PIN_INFO_S scroll_ctrl;
    #endif

    #if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_PRODUCT_TYPE_MOUSE)
    uint32_t key_remap_enable;
    uint32_t key_remap_fn_key;
    #elif defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER) || defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    uint32_t key_remap_enable[2];
    uint16_t linear_threshold[4];
    uint32_t key_not_remap_disable[2];
    #endif
    #endif /* AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */

    uint16_t  riscv_trigger_time[HID_REPORT_RATE_TOTAL_NUM];

    #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_PRODUCT_TYPE_MOUSE)
    uint8_t  mouse_key_list[RISCV_MAX_KEY_NUM];         /** gpio list of mouse key */
    uint8_t  mouse_key_num;             /** gpio number in  mouse_key_list */
    #elif defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    uint8_t  device_key_list[32];
    uint8_t  device_key_num;
    #elif defined(AIR_PRODUCT_TYPE_KEYBOARD)
    uint8_t  device_key_list[32];
    uint8_t  device_key_num;
    #endif

    T_HID_REPORT_RATE_VAL_S rr;
    #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_PRODUCT_TYPE_MOUSE)
    T_DEBOUNCE_PARA_S   deb;
    #endif
} app_shared_parameters;

typedef struct {
    //contraband of application
    app_shared_parameters   app;
    hid_shared_parameters   hid;
    T_COMMON_LA_DBG_S       dbg;
    #if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    T_HID_KEY_REMAP_S       mapped_data[KEY_NUMBER]; /* key remap setting data of key */
    #endif /* AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */
    #if defined(AIR_USB_CCNI_WAKEUP_CM33) || defined(CONFIG_AIR_USB_EARLY_WAKEUP_CM33)
    T_HID_CCNI_USB_REPORT_S outgoing_report[1];
    #endif
} hid_common_info;

/* Public macro --------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

extern hid_common_info *hid_common;

/* Inline functions ----------------------------------------------------------*/


/* Public functions ----------------------------------------------------------*/
inline void hid_common_app_para_get(app_shared_parameters* app_para)
{
    memcpy((uint8_t*)app_para, (uint8_t*)&hid_common->app, sizeof(app_shared_parameters));
}

inline void hid_common_hid_exp_para_get(hid_shared_parameters* hid_para)
{
    memcpy((uint8_t*)hid_para, (uint8_t*)&hid_common->hid, sizeof(hid_shared_parameters));
}




void hid_common_set_app_feature(uint8_t feature_id);
void hid_common_clear_app_feature(uint8_t feature_id);
void hid_common_set_hid_exp_flag(uint8_t flag_id);
void hid_common_clear_hid_exp_flag(uint8_t flag_id);

void hid_common_set_dongle_scenario(uint32_t dongle_scenario);
uint32_t hid_common_get_dongle_scenario();
void hid_common_sync_debug(T_COMMON_LA_DBG_S *debug);
#if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_PRODUCT_TYPE_MOUSE)
void hid_common_set_combo_key(const T_AIR_COMBO_KEY_S *combo_key_list, uint32_t combo_key_list_size, uint32_t hold_timeout);
void hid_common_get_combo_key_list(T_AIR_COMBO_KEY_S **combo_key_list, uint32_t *combo_key_list_size, uint32_t *hold_timeout);
#endif
#if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
void hid_common_set_key_remap_data(T_HID_KEY_REMAP_S *mapped_data, uint8_t key_id);
void hid_common_get_backend_key_remap_data(T_HID_KEY_REMAP_BACKEND_S* mapped_data, uint8_t key_id);
void hid_common_get_frontend_key_remap_data(T_HID_KEY_REMAP_FRONTEND_S* mapped_data, uint8_t key_id);
void hid_common_clear_key_remap_data(uint8_t key_id);
void hid_common_clear_all_key_remap_data();
#endif /* AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */
#define FLAG_BIT_BT_ENCRYPTED           2
#define FLAG_BIT_ATT_NOTIFY_MOUSE_ENA   3
#define FLAG_BIT_SENSOR_READY           4

#define FLAG_BIT_USB_CONNECTED          5
#define FLAG_BIT_BT_CONNECTED           6
#define FLAG_BIT_GAMING_CONNECTED       7

#define FLAG_BIT_USB_TX_NACK            8
#define FLAG_BIT_FORCE_RELEASE_KEY      9

#define FLAG_BIT_USB_PLUG_STATUS       10
#define FLAG_BIT_SLIDE_SWITCH_POS      11
#define FLAG_BIT2_SLIDE_SWITCH_POS     12
#define FLAG_BIT_SCENARIO_MODE_TYPE    13
#define FLAG_BIT2_SCENARIO_MODE_TYPE   14

/** app features*/
#define APP_FEATURE_QDEC_DIRECTION_REVERSE              1
#define APP_FEATURE_IR_KEY_LR                           2

#define BIT_MASK_ENCRYPTED_CCCD_READY           ((0x01 << FLAG_BIT_BT_ENCRYPTED)|(0x01 << FLAG_BIT_ATT_NOTIFY_MOUSE_ENA))
#define BIT_MASK_BT_CH_READY                    ((0x01 << FLAG_BIT_BT_CONNECTED)|(0x01 << FLAG_BIT_BT_ENCRYPTED)|(0x01 << FLAG_BIT_ATT_NOTIFY_MOUSE_ENA)|(0x01 << FLAG_BIT_SENSOR_READY))
#define BIT_MASK_GAMING_CH_READY                ((0x01 << FLAG_BIT_GAMING_CONNECTED)|(0x01 << FLAG_BIT_SENSOR_READY))

#define USB_DATA_GO(flags)                      (flags & (0x01 << FLAG_BIT_USB_CONNECTED) )
#define BT_DATA_GO(flags)                       ((flags & BIT_MASK_BT_CH_READY ) == BIT_MASK_BT_CH_READY)
#define GAMING_DATA_GO(flags)                   ((flags & BIT_MASK_GAMING_CH_READY) == BIT_MASK_GAMING_CH_READY)
#define BT_ENCRYPTED_CCCD_READY(flags)          ((flags & BIT_MASK_ENCRYPTED_CCCD_READY) == BIT_MASK_ENCRYPTED_CCCD_READY)

#define USB_TX_NACK(flags)                      (flags & (0x01 << FLAG_BIT_USB_TX_NACK))
#define FORCE_RELEASE_KEY_ENABLE(flags)         (flags & (0x01 << FLAG_BIT_FORCE_RELEASE_KEY))



#define QDEC_DIRECTION_REVERSE_ENABLE(flags)    (flags & (0x01 << APP_FEATURE_QDEC_DIRECTION_REVERSE))
#define IR_KEY_LR(flags)                        (flags & (0x01 << APP_FEATURE_IR_KEY_LR))

#define USB_PLUG_STATUS_CHECK(flags)            (flags & (0x01 << FLAG_BIT_USB_PLUG_STATUS))
#define SLIDE_SWITCH_POSITION(flags)            (((flags >> FLAG_BIT_SLIDE_SWITCH_POS) & 0x01) | (((flags >> FLAG_BIT2_SLIDE_SWITCH_POS) & 0x01) << 4))
#define APP_SCENARIO_MODE_TYPE(flags)           (((flags >> FLAG_BIT_SCENARIO_MODE_TYPE) & 0x01) | (((flags >> FLAG_BIT2_SCENARIO_MODE_TYPE) & 0x01) << 4))


#define HID_EXP_FEATURE_IRPT_CTRL_PIN_ENABLE            0x0001
#define HID_EXP_FEATURE_REPORT_LOG_ENABLE               0x0100


void hid_common_set_hid_exp_features(uint32_t hid_exp_features);
void hid_common_get_hid_exp_features(uint32_t *hid_exp_features);

typedef enum{
    DPI_STAGE_PLUS,       /**request for next DPI in DPI list*/
    DPI_STAGE_MINUS,      /**request for previous DPI in DPI list*/
    DPI_STAGE_LOCK,       /**request specific DPI. A specific DPI should be specified by another parameter*/
    DPI_STAGE_LOOP,       /**request to loop through DPI list*/
}T_DPI_CHANGE_TYPE_E;

typedef enum {
    PARA_TYPE_IRPT_CTRL,
    PARA_TYPE_SCROLL_CTRL,
    PARA_TYPE_DEBUG_PIN,
    PARA_TYPE_RR_IDX,
    PARA_TYPE_RISCV_TRIGGER_TIME,
    PARA_TYPE_DEBOUNCE_CONFIG,
    #if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    RAPA_TYPE_KEY_REMAP_ENABLE,
    RAPA_TYPE_REMAP_FN_KEY,
    RAPA_TYPE_KEY_NOT_REMAP_DISABLE,
    #endif
}T_APP_PARA_TYPE_E;

typedef enum {
    RAPA_TYPE_ACL_RESPONSE_VIA_HID_REPORT,
}T_HID_PARA_TYPE_E;

typedef enum {
    HID_SCENARIO_NONE = 0x00,
    HID_SCENARIO_BT_MODE = 0x01,
    HID_SCENARIO_GAMING_MODE = 0x02,
    HID_SCENARIO_USB_MODE = 0x03,
}T_HID_SCENARIO_DEVICE_TYPE_E;

typedef enum {
    USB_PLUG_OUT = 0,
    USB_PLUG_IN,
} T_USB_PLUG_STATUS_E;

typedef enum {
    SS_MODE_NONE = 0x00,
    SS_MODE_OFF = 0x01,
    SS_MODE_BT = 0x02,
    SS_MODE_2_4G = 0x03,
} T_SLIDE_SWITCH_MODE_E;

void hid_common_set_app_para(uint8_t para_type, uint8_t* data, uint8_t length);
uint32_t hid_common_set_hid_para(uint8_t para_type, uint8_t* data, uint8_t length);

#endif /* AIR_HID_COMMON_SERVICE */
#endif /* _HID_COMMON_H_ */
