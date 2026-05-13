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
 
 
#ifndef __HID_SCENARIO_SERVICE_H__
#define __HID_SCENARIO_SERVICE_H__

#include "hid_vendor_cmd.h"
#include <zephyr/bluetooth/bluetooth.h>
#include "hid_common.h"


/** HID scenario service events*/
typedef enum {
    SS_EVT_STATE_UPDATE,                /** for scenario state update notification*/
    SS_EVT_USB_REPORT_RATE_UPDATE,      /** for usb report rate update notification*/
    SS_EVT_GAMING_REPORT_RATE_UPDATE,   /** for gaming report rate update notification*/
    SS_EVT_BT_REPORT_RATE_UPDATE,       /** for bt report rate update notification*/

    #if defined(CONFIG_AIR_HID_OUTPUT_REPORT_NOTIFY)
    SS_EVT_HID_OUTPUT_REPORT,           /** for HID output report notification*/
    #endif
}T_SCENARIO_SERVICE_EVENT_E;

typedef enum {
    MODE_NONE = 0x00,
    MODE_CLOSED,

    MODE_OPEN_SPECIFIED = 0x10,
    MODE_OPEN_UNSPECIFIED,
#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
    MODE_OPEN_SPECIFIED_RESUME,
#endif

    MODE_OPEN_USB_CONNECTED  = 0x20,
    MODE_USB_RESUME,
    MODE_USB_STARTED,
    MODE_USB_STOPPED,

    MODE_OPEN_CONNECTED = 0x40,
    MODE_OPEN_CONNECTED_CCCD_READY,
    MODE_OPEN_CONNECTED_ENCRYPTED,
    MODE_OPEN_CIS_SERVICE_READY,
    MODE_STARTED,
    MODE_STOPPED,
}T_HID_MODE_STATE_E;


typedef enum {
    SCENARIO_SRV_CONFIG_REPORT_RATE,    
    SECNARIO_SRV_CONFIG_ID_ADDR_DELETE,
    SECNARIO_SRV_CONFIG_SET_UNIAA,
    SECNARIO_SRV_CONFIG_GET_UNIAA,
    SECNARIO_SRV_CONFIG_BT_TRIGGER,
    SECNARIO_SRV_CONFIG_GAMING_ADV,
}T_HID_SCENARIO_CONFIG_TYPE_E;

typedef enum {
    SCENARIO_SRV_OPEN_RECONNECT,    
    SCENARIO_SRV_OPEN_REPARING,
    SCENARIO_SRV_OPEN_RESUME_WAIT,
}T_HID_SCENARIO_OPEN_TYPE_E;

typedef struct {
    T_HID_SCENARIO_CONFIG_TYPE_E cfg_type;
    uint8_t len;
    union {
        struct {
            uint8_t value[8];
        };
        struct {
            uint8_t *pointerValue;
        };
    };
}T_HID_SCENARIO_CONFIG_PARA_S;


typedef struct {
    uint16_t para;
    uint8_t type;
    uint8_t restore_or_chg_profile;
}T_REPORT_RATE_CHANGE_S;

typedef struct {
    uint8_t state;      /** new scenario state */
    uint8_t reason;     /** the reason of changing state*/
}T_SCENARIO_SERVICE_STATE_UPDATE_S;

typedef enum {
    CONFIG_RR_NEXT,
    CONFIG_RR_PREV,
    CONFIG_RR_SPECIFIC_IDX,
    CONFIG_RR_SPECIFIC_VAL
}T_RR_CONFIG_TYPE_E;

typedef enum {
    ADV_SETTING_DEFAULT,
    ADV_SETTING_RESUME_WAIT,
}T_ADV_SETTING_TYPE_E;

typedef struct {
    T_ADV_SETTING_TYPE_E setting_type;
}T_GAMING_ADV_SETTING_S;

typedef enum {
    SCENARIO_STATE_CHANGE_REASON_NONE,
    SCENARIO_STATE_CHANGE_REASON_OPENED, 
    SCENARIO_STATE_CHANGE_REASON_CLOSED,
    SCENARIO_STATE_CHANGE_REASON_STARTED,
    SCENARIO_STATE_CHANGE_REASON_STOPPED,

    REASON_CONNECTION_TERMINATED_BY_LOCAL_HOST =  0x16, 
    REASON_RECONNECTION_CREATE_FAIL,
#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
    REASON_RECONNECTION_RESUME,
#endif
}T_SCENARIO_STATE_CHANGE_REASON_E;


typedef enum {
    SCENARIO_IDLE1_STOP,
    SCENARIO_IDLE2_STOP, 
    SCENARIO_USB_STOP,
}T_MODE_STOPPED_STATE_E;

#define USER_PROFILE_NUMBER 4



typedef void (* hid_scenario_callback)(uint32_t event, void *param, uint32_t param_len);

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/



/******************************************************************************/
/* functions                                                                  */
/******************************************************************************/
uint8_t hid_scenario_init(hid_scenario_callback cb, uint8_t profile_idx);
uint8_t hid_scenario_open(uint8_t scenario, uint32_t link_idx, T_HID_SCENARIO_OPEN_TYPE_E type, uint16_t reconnect_time);
uint8_t hid_scenario_start(uint8_t scenario, uint32_t link_idx, void* parameter);
uint8_t hid_scenario_stop(uint8_t scenario, uint8_t parameter);
uint8_t hid_scenario_close(uint8_t scenario, uint8_t parameter);
uint8_t hid_scenario_config(uint8_t scenario, T_HID_SCENARIO_CONFIG_PARA_S* parameter);
uint8_t hid_scenario_get();
uint8_t hid_scenario_get_state();
bool hid_scenario__bt_trigger_peripheral_hw(uint32_t enable);
#endif

