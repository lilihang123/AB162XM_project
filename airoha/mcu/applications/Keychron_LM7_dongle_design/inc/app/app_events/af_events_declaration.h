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

#ifndef _AF_EVENTS_DECLARATION_H_
#define _AF_EVENTS_DECLARATION_H_


/* Includes ------------------------------------------------------------------*/
#include <app_evt_dispatcher.h>
#include <stdint.h>

/* Public define -------------------------------------------------------------*/
typedef uint8_t T_EVT_CMD_E;
enum {
    EVT_CMD_STARTUP = 0, /* param: role */
    EVT_CMD_RUNNING,
    /* Reconnect event area */
    EVT_CMD_RECONNECT_REQ = 10,
    EVT_CMD_RECONNECT_SUCCESS,
    EVT_CMD_RECONNECT_FAIL,
    EVT_CMD_RECONNECT_TIMEOUT,
    EVT_CMD_RECONNECT_CANCEL_REQ,
    EVT_CMD_RECONNECT_CANCEL_SUCCESS,
    EVT_CMD_RECONNECT_CANCEL_FAIL,
    /* Disconnect event area */
    EVT_CMD_DISCONNECT_BY_TARGET = 20,
    EVT_CMD_DISCONNECT_REQ,
    EVT_CMD_DISCONNECT_SUCCESS,
    EVT_CMD_DISCONNECT_FAIL,
    /* Remove CIG event area */
    EVT_CMD_REMOVE_CIG_SUCCESS,
    EVT_CMD_REMOVE_CIG_FAIL,
    /* Scan and Pair event area */
    EVT_CMD_ACL_SCAN_START_REQ = 30, /* param: timeout millsecond */
    EVT_CMD_ACL_SCAN_STOP_REQ, /* param: NULL */
    EVT_CMD_ACL_DEVICE_FOUND, /* param: NULL */
    EVT_CMD_ACL_PAIR_REQ, /* param: device found */
    EVT_CMD_ACL_PAIR_SUCCESS,
    EVT_CMD_ACL_PAIR_FAIL,
    EVT_CMD_ACL_PAIR_TIMEOUT,
    EVT_CMD_ACL_CONN_REQ,
    EVT_CMD_ACL_CONN_SUCCESS,
    EVT_CMD_ACL_CONN_FAIL,
    EVT_CMD_ACL_SEC_UPDATE_REQ = 40,
    EVT_CMD_ACL_SEC_UPDATE_SUCCESS,
    EVT_CMD_ACL_SEC_UPDATE_FAIL,
    EVT_CMD_ACL_DISC_REQ,
    EVT_CMD_ACL_DISC_SUCCESS,
    EVT_CMD_ACL_DISC_FAIL,
    EVT_CMD_ACL_DISC_ERR,
    EVT_CMD_ULL_BOND_REQ,
    EVT_CMD_ULL_BOND_SUCCESS,
    EVT_CMD_ULL_BOND_FAIL,
    /* Connect event area */
    EVT_CMD_ULL_CONN_REQ = 60,
    EVT_CMD_ULL_CONN_SUCCESS,
    EVT_CMD_ULL_CONN_FAIL,
    EVT_CMD_ULL_SERVICE_CONN_REQ,
    EVT_CMD_ULL_SERVICE_CONN_SUCCESS,
    EVT_CMD_ULL_SERVICE_CONN_FAIL,
    EVT_CMD_ULL_DISC_REQ,
    EVT_CMD_ULL_DISC_SUCCESS,
    EVT_CMD_ULL_DISC_FAIL,
    /* USB event area */
    EVT_CMD_USB_PLUGIN = 80,
    EVT_CMD_USB_PLUGOUT,
    EVT_CMD_USB_READY,
    EVT_CMD_USB_SUSPEND,
    EVT_CMD_USB_RESUME,
    /* report rate event area */
    EVT_CMD_REPORT_RATE_CHANGE_REQ = 90,
    /* output reportevent area */
    EVT_CMD_OUTPUT_REPORT_CHANGE_REQ = 91,
    /* auto switch event area  */
    EVT_CMD_AUTO_SWITCH_REQ = 92,
    EVT_CMD_AUTO_SWITCH_CANCEL_REQ = 93,
    /* cis scan event area  */
    EVT_CMD_CIS_SCAN_DEVICE_FOUND = 94,
    /* end */
    EVT_CMD_END,
};

/* Public typedef ------------------------------------------------------------*/
struct evt_cmd{
    struct af_evt_header header;
    T_EVT_CMD_E cmd;
    void *param;
};

struct state_cmd{
    struct af_evt_header header;
    uint32_t state;
    uint32_t last_state;
    uint32_t reason;
};

/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
AF_EVT_EXTERN(evt_cmd);
AF_EVT_EXTERN(state_cmd);

/* Public functions ----------------------------------------------------------*/


#endif /* _AF_EVENTS_DECLARATION_H_ */
