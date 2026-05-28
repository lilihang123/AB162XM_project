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


#ifndef __APP_MODULE_H__
#define __APP_MODULE_H__

#include <af_framework.h>
#include <stdint.h>
#include "gesture.h"
#include "hid_common.h"

typedef enum{
    MSG_NONE,
    MSG_INIT,
    MSG_START,
    MSG_STOP,
    MSG_RESTART,
    MSG_CONNECT
}T_MODULE_MSG_E;


#define REPORT_RATE_MAX         8000
#define REPORT_RATE_DEFAULT     1000
#define MAX_DPI_NUM 5
typedef enum{
    RR_CHANGE_NEXT = 0,   /**request for next report rate in report rate list*/
    RR_CHANGE_PREV,       /**request for previous report rate in report rate list*/
    RR_CHANGE_SPECIFIC,   /**request specific report rate. A specific report rate should be specified by another parameter*/
}T_RR_CHANGE_TYPE_E;

#if 0
typedef enum{
    CONN_STATUS_DISCONNECTED,
    CONN_STATUS_CONNECTED,
    CONN_STATUS_CONNECTED_AND_SECURED,
}T_EVT_CONN_STATUS_E;
#endif

typedef enum{
    CONN_REQ_NONE,
    CONN_REQ_DISC,
    CONN_REQ_CONN_NEW,
    CONN_REQ_CONN_LAST_LINK,
    CONN_REQ_CONN_LAST_BT_LINK,
    CONN_REQ_CONN_LAST_GAMING_LINK,
    #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
    CONN_REQ_CONN_USB,  /* Send request to enable USB devices. */
    CONN_REQ_STOP_USB,
    #endif /* _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_ */
    CONN_REQ_CONN_NEXT_LINK,
    CONN_REQ_CONN_NEXT_BT_LINK,
    CONN_REQ_CONN_NEXT_GAMING_LINK,
    CONN_REQ_ACTIVE,
    CONN_REQ_ACTIVE_USB,
    CONN_REQ_IDLE_1,
    CONN_REQ_IDLE_2,
    CONN_REQ_IDLE_3,
    CONN_REQ_CANCEL_CONN,
}T_EVT_CONN_REQ_E;

typedef enum{
    USB_STATUS_PLUGGED_OUT,
    USB_STATUS_PLUGGED_IN,
    #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
    USB_STATUS_READY_TO_ENABLE,
    USB_STATUS_READY_TO_DISABLE,
    USB_STATUS_CONFIGURED,
    USB_STATUS_DISCONNECT,
    #endif
}T_EVT_USB_STATUS_E;

typedef enum{
    CHANGE_NEXT_LINK,
    #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
    CHANGE_NEXT_BT_LINK,
    #endif
    CHANGE_NEXT_GAMING_LINK,
}T_LINK_CHANGE_E;

typedef enum{
    PAIRING_REQ_RECOVERABLE,
    PAIRING_REQ_UNRECOVERABLE,
}T_PAIRING_REQUEST_E;

typedef enum{
    MOTION_SENSOR_WAKEUP,
    WHEEL_WAKEUP,
    KEY_WAKEUP,
    USB_PLUG_WAKEUP,
    #if defined(CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH)
    SLIDE_SWITCH_WAKEUP,
    #endif
    DISCONNECT_REQ_WAKEUP,
}T_WAKEUP_TYPE_E;

typedef enum{
    RACE_CMD_SET_REPORT_RATE = 0x3010,
    RACE_CMD_GET_REPORT_RATE,
    RACE_CMD_SET_UNIAA = 0x306A,
    RACE_CMD_GET_UNIAA = 0x306B,
    RACE_CMD_ENABLE_KEY_EVENT = 0x3070,
    RACE_CMD_SET_DPI_VALUE = 0x3080,
    RACE_CMD_SET_RGB = 0x30C0,
    #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    RACE_CMD_SET_KEY_REMAP = 0x30C2,
    RACE_CMD_GET_KEY_REMAP,
    #endif
    RACE_CMD_SET_DPI = 0x30C4,
    RACE_CMD_GET_DPI,
    RACE_CMD_SET_DPI_LOOP_RANGE,
    RACE_CMD_SET_DPI_CURRENT,
    RACE_CMD_SET_PROFILE,
    RACE_CMD_GET_PROFILE,
    RACE_CMD_SET_DEBOUNCE,
    RACE_CMD_GET_DEBOUNCE,
    RACE_CMD_SET_SENSOR_LOD,
    RACE_CMD_GET_SENSOR_LOD,
    RACE_CMD_SET_RESTORE,
    RACE_CMD_GET_BATTERY,
    #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    RACE_CMD_DELETE_MACRO = 0x30D1,
    #endif
    RACE_CMD_SET_SENSOR_MOTION_SYNC = 0x30D2,
    RACE_CMD_GET_SENSOR_MOTION_SYNC,
    RACE_CMD_SET_SENSOR_ANGLE_SNAP,
    RACE_CMD_GET_SENSOR_ANGLE_SNAP,
    RACE_CMD_SET_SENSOR_RIPPLE_CTRL,
    RACE_CMD_GET_SENSOR_RIPPLE_CTRL,
    RACE_CMD_SET_SW_DEBOUNCE = 0x30E8,
    RACE_CMD_GET_SW_DEBOUNCE,
    #if defined (CONFIG_AIR_REMAP_FN_KEY)
    RACE_CMD_SET_REMAP_FN_KEY,
    RACE_CMD_GET_REMAP_FN_KEY,
    #endif
}T_RACE_CMD_E;

typedef enum{
    FAKE_DATA_REPORT,
    FAKE_DATA_PARAM,
}T_FAKE_DATA_SEND_E;

typedef enum{
    TEST_TYPE_RELAY_MODE,
    TEST_TYPE_LAB_TEST,
}T_TEST_TYPE_E;

typedef enum {
    BAT_EVT_PERCENT_CHANGE = 0,
    BAT_EVT_CHG_EXIST_CHANGE,
    BAT_EVT_CHG_STATE_CHANGE,
    BAT_EVT_CHG_ENABLE_STA_CHANGE,
    BAT_EVT_END_OF_CHARGE,
    BAT_EVT_LOW_BAT_WARNING,
    BAT_EVT_POWER_OFF,
} T_BATTERY_EVENT_E;

#define RESTORE_MASK_BT_LINKS           0x01
#define RESTORE_MASK_DONGLE_LINKS       0x02
#define RESTORE_MASK_PC_TOOL_CONFIGURE  0x04

struct evt_module_init{
    struct af_evt_header header;
};

struct evt_active_status{
    struct af_evt_header header;
    uint8_t active;
    T_WAKEUP_TYPE_E type;
};

struct evt_app_state{
    struct af_evt_header header;
    uint8_t app_state;
};

struct evt_app_state_change_req{
    struct af_evt_header header;
    uint8_t app_state;
};

struct evt_app_battery{
    struct af_evt_header header;
    T_BATTERY_EVENT_E status;
    uint8_t val;
};

struct evt_app_bat_timer{
    struct af_evt_header header;
    uint8_t cmd;
};


struct evt_app_rgb_test{
    struct af_evt_header header;
    uint8_t cmd;
};

struct evt_bt_status{
    struct af_evt_header header;
    uint8_t status;
};

#if 0
struct evt_conn_status{
    struct af_evt_header header;
    T_EVT_CONN_STATUS_E status;
    uint8_t reason;
};
#endif

struct evt_conn_req{
    struct af_evt_header header;
    T_EVT_CONN_REQ_E cmd;
    uint16_t reconnect_timeout_2_4G;
    uint8_t repair_status;
};

struct evt_fake_report_execute{
    struct af_evt_header header;
    T_FAKE_DATA_SEND_E type;
    union{
        uint32_t* fake_data;
        struct {
            uint8_t enable;
            uint8_t pattern;
            uint32_t rounds;
        };
    };
};


struct evt_pairing_request{
    struct af_evt_header header;
    T_PAIRING_REQUEST_E type;  // 0: recoverable pairing request, 1: nonrecoverable pairing request
    uint8_t force_key_release_req; //0: key release success, 1: key release req
};

struct evt_restore{
    struct af_evt_header header;
    uint32_t restore_mask;
};


struct evt_riscv_key{
    struct af_evt_header header;
    uint32_t key_status;
};

#if defined (CONFIG_AIR_SUPPORT_IR_COMP)
struct evt_riscv_wheel_status{
    struct af_evt_header header;
    uint32_t wheel_status;
};
#endif

struct evt_mouse_sensor{
    struct af_evt_header header;
    uint8_t reserved;
};

struct evt_rr_change_req{
    struct af_evt_header header;
    T_RR_CHANGE_TYPE_E change_type;
    uint16_t RR;  //report rate
    uint8_t restore_or_chg_profile;
};

struct evt_rr_status{
    struct af_evt_header header;
    uint8_t category;       // report rate category such as usb and gaming
    uint16_t RR;            // report rate
};

struct evt_dpi_change_req{
    struct af_evt_header header;
    T_DPI_CHANGE_TYPE_E change_type;
    #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
    uint16_t X_DPI;
    uint16_t Y_DPI;
    #else
    uint16_t DPI;
    #endif
};

struct evt_dpi_status{
    struct af_evt_header header;
    uint8_t dpi_idx;
    #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
    uint16_t x_dpi_value;
    uint16_t y_dpi_value;
    #else
    uint16_t dpi_value;
    #endif
};

struct evt_scenario_status{
    struct af_evt_header header;
    uint8_t status;
    uint8_t reason;
};


struct evt_link_change{
    struct af_evt_header header;
    T_LINK_CHANGE_E type;
};

typedef enum{
    SLIDE_SWITCH_POS_OFF,
    SLIDE_SWITCH_POS_BT,
    SLIDE_SWITCH_POS_GAMING,
}T_SLIDE_SWITCH_STATUS_E;

struct evt_slide_switch_status{
    struct af_evt_header header;
    T_SLIDE_SWITCH_STATUS_E position;
};

struct evt_usb_status{
    struct af_evt_header header;
    T_EVT_USB_STATUS_E status;  // 0:plugged out, 1: plugged in, 2: suspend;
    uint8_t reason;
};

struct evt_race_cmd_req{
    struct af_evt_header header;
    T_RACE_CMD_E cmd;
    uint16_t len;
    union {
        struct {
            uint16_t value;
        } RR;

        struct {
            #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
            uint16_t x_dpi_value;
            uint16_t y_dpi_value;
            #else
            uint16_t dpi_value;
            #endif
            uint8_t dpi_idx;
        } DPI;

        struct {
            uint8_t value;
        } SENSOR;

        struct {
            uint8_t time;
        } DEBOUNCE;

        struct {
            T_DEBOUNCE_PARA_S settings;
        } SW_DEBOUNCE;

        struct {
            uint8_t id;
        } PROFILE;

        #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
        struct {
            uint8_t remap_key_id;
            uint8_t remap_key_type;
            uint8_t macro_name[16];
            uint8_t remap_setting[0];
        } KEY_REMAP;

        #if defined(CONFIG_AIR_REMAP_FN_KEY)
        struct {
            uint8_t key;
        } REMAP_FN_KEY;
        #endif
        #endif

        struct {
            uint8_t rgb_setting;
            uint8_t rgb_num;
            uint8_t rgb_interval;
            uint8_t rgb_count;
            uint8_t rgb_color[0];
        } RGB;

        struct {
            uint8_t pair_device_type;
            uint8_t addr_type;
            uint8_t pair_address[6];
            uint8_t uni_aa[4];
            uint8_t ltk[16];
            uint8_t skd[16];
            uint8_t iv[8];
        } UNIAA;

        struct {
            uint16_t event_id;
        } ENABLE_KEY_EVNET;
    };
} ;

struct evt_race_cmd_rsp{
    struct af_evt_header header;
    T_RACE_CMD_E cmd;
    union {
        struct {
            uint16_t result;
        } RR;

        struct {
            uint16_t x_dpi_value;
            uint16_t y_dpi_value;
            #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
            uint16_t x_dpi_settings[MAX_DPI_NUM];
            uint16_t y_dpi_settings[MAX_DPI_NUM];
            #else
            uint16_t dpi_settings[MAX_DPI_NUM];
            #endif
            uint8_t dpi_loop_stage_range;
            uint8_t dpi_curr_idx;
        } DPI;

        struct {
            uint8_t result;
        } SENSOR;

        struct {
            uint8_t result;
        } DEBOUNCE;

        struct {
            T_DEBOUNCE_PARA_S settings;
        } SW_DEBOUNCE;

        struct {
            uint8_t result;
        } PROFILE;

        struct {
            uint8_t charging;
            uint8_t battery;
        } BATTERY;

        #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
        struct {
            uint16_t remap_len;
            uint8_t remap_key_id;
            uint8_t remap_key_type;
            uint8_t remap_setting[0];
        } KEY_REMAP;

        #if defined(CONFIG_AIR_REMAP_FN_KEY)
        struct {
            uint8_t key;
        } REMAP_FN_KEY;
        #endif
        #endif

        struct {
            uint8_t status;
        } OTHERS;
    };
} ;

struct evt_race_cmd_rsp_for_rgb{
    struct af_evt_header header;
    T_RACE_CMD_E cmd;
    uint8_t status;
};

struct evt_enter_test{
    struct af_evt_header header;
    T_TEST_TYPE_E type;
};

struct evt_factory_reset{
    struct af_evt_header header;
    uint8_t status;
};

struct evt_key_event{
    struct af_evt_header header;
    uint8_t key_id;
    airoha_key_event_t key_evt;
};

struct evt_hogp_attr{
    struct af_evt_header header;
    uint8_t ms;
    uint8_t kb_std;
    uint8_t kb_consumer;
};

struct evt_sw_deb_update{
    struct af_evt_header header;
};

struct evt_job_next_process{
    struct af_evt_header header;
};

struct evt_force_key_release_success{
    struct af_evt_header header;
};
/*============================Application Framework============================*/
// General subscribable events
// Please SORT by alphabet
AF_EVT_EXTERN(evt_active_status);

AF_EVT_EXTERN(evt_app_state);
AF_EVT_EXTERN(evt_app_state_change_req);
AF_EVT_EXTERN(evt_app_battery);
AF_EVT_EXTERN(evt_app_bat_timer);
AF_EVT_EXTERN(evt_app_rgb_test);
AF_EVT_EXTERN(evt_enter_test);

AF_EVT_EXTERN(evt_bt_status);

AF_EVT_EXTERN(evt_conn_req);

AF_EVT_EXTERN(evt_fake_report_execute);

AF_EVT_EXTERN(evt_link_change);

AF_EVT_EXTERN(evt_pairing_request);

AF_EVT_EXTERN(evt_restore);

AF_EVT_EXTERN(evt_riscv_key);

#if defined (CONFIG_AIR_SUPPORT_IR_COMP)
AF_EVT_EXTERN(evt_riscv_wheel_status);
#endif

AF_EVT_EXTERN(evt_module_init);
AF_EVT_EXTERN(evt_mouse_sensor);

AF_EVT_EXTERN(evt_rr_change_req);
AF_EVT_EXTERN(evt_rr_status);
AF_EVT_EXTERN(evt_dpi_change_req);
AF_EVT_EXTERN(evt_dpi_status);

AF_EVT_EXTERN(evt_scenario_status);
AF_EVT_EXTERN(evt_slide_switch_status);

#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
AF_EVT_EXTERN(evt_usb_status);
#endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/

AF_EVT_EXTERN(evt_race_cmd_req);
AF_EVT_EXTERN(evt_race_cmd_rsp);
AF_EVT_EXTERN(evt_race_cmd_rsp_for_rgb);

AF_EVT_EXTERN(evt_factory_reset);
AF_EVT_EXTERN(evt_key_event);
AF_EVT_EXTERN(evt_hogp_attr);
AF_EVT_EXTERN(evt_sw_deb_update);
AF_EVT_EXTERN(evt_job_next_process);
AF_EVT_EXTERN(evt_force_key_release_success);
/*=============================================================================*/
#endif

