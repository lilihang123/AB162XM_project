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

#ifndef __APP_DONGLE_CM_CONFIG_H__
#define __APP_DONGLE_CM_CONFIG_H__

#include "app_dongle_cm_type.h"

#ifdef __cplusplus
extern "C" {
#endif



/**================================================================================*/
/**                                Basic Feature Option                            */
/**================================================================================*/
#define APP_DONGLE_CM_LE_SCANNER_IGNORE_LONG_DISTANCE_DEVICE
#define APP_DONGLE_CM_LE_SCANNER_LONG_DISTANCE_RSSI                     (-60)

#define APP_DONGLE_CM_DEVICE_LIST_SUPPORT_NAME
#define APP_DONGLE_CM_DEVICE_LIST_NAME_MAX_LEN                          (31)

#define APP_DONGLE_CM_DEVICE_LIST_MAX_NUM                               8

// Inactive policy, when switch remove active device from A to B, Dongle CM need to inactive B via which policy (disconnect or only send inactive CMD)
typedef enum {
    APP_DONGLE_CM_INACTIVE_POLICY_DISCONNECT                            = 0,
    APP_DONGLE_CM_INACTIVE_POLICY_SEND_INACTIVE_CMD,
} app_dongle_cm_inactive_policy_t;

// Exclusive policy, when connected new remote device B, Dongle CM need to disconnect all other connected remote device or keep some remote device based on their link/device type
typedef enum {
    APP_DONGLE_CM_EXCLUSIVE_POLICY_DISCONNECT_ALL                       = 0,                // Disconnect all other remote device
    APP_DONGLE_CM_EXCLUSIVE_POLICY_OFFICE_DONGLE,                                           // Disconnect other link except LE_HOGP, Keep only one KB or MS
    APP_DONGLE_CM_EXCLUSIVE_POLICY_DISCONNECT_OTHER_LINK_TYPE,                              // Disconnect all device with different link type, such ass LEA multi-link
    APP_DONGLE_CM_EXCLUSIVE_POLICY_DISCONNECT_OTHER_DEVICE_TYPE,                            // Disconnect all device with different device type
} app_dongle_cm_exclusive_policy_t;



/**================================================================================*/
/**                                    Feature Mode                                */
/**================================================================================*/
#ifdef AIR_HOGP_DONGLE_ENABLE
// For office dongle (KB+MS, LE HOGP, max 3 KB + 3 MS)
#define   APP_DONGLE_CM_FEATURE_MODE_LE_OFFICE_DONGLE
#endif






/**================================================================================*/
/**                                  Feature Config                                */
/**================================================================================*/
#ifdef APP_DONGLE_CM_FEATURE_MODE_LE_OFFICE_DONGLE
#define   APP_DONGLE_CM_CONFIG_INACTIVE_POLICY                          APP_DONGLE_CM_INACTIVE_POLICY_DISCONNECT
#define   APP_DONGLE_CM_CONFIG_EXCLUSIVE_POLICY                         APP_DONGLE_CM_EXCLUSIVE_POLICY_OFFICE_DONGLE
#define   APP_DONGLE_CM_OFFICE_KB_MAX_NUM                               3
#define   APP_DONGLE_CM_OFFICE_MS_MAX_NUM                               3

#define   APP_DONGLE_CM_MAX_CONN_NUM                                    4 // (KB->KB, MS->MS)

#define   APP_DONGLE_CM_MAX_LINK_CONTEXT_NUM                            1 // Only LE HOGP

#define   APP_DONGLE_CM_LE_SCANNER_CHECK_REMOTE_DEVICE_NAME
#define   APP_DONGLE_CM_LE_SCANNER_REMOTE_DEVICE_NAME_PREFIX            ("Dell")
#endif



#ifdef __cplusplus
}
#endif

#endif /* __APP_DONGLE_CM_CONFIG_H__ */
