/* Copyright Statement:
*
* (C) 2025 Airoha Technology Corp. All rights reserved.
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
* the License Agreement ("Permitted User"). If you are not a Permitted User,
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
/* Airoha restricted information */
#include "hid_critical_path_common.h"
#ifndef __BT_HID_CRITICAL_PATH_KB_H__
#define __BT_HID_CRITICAL_PATH_KB_H__

#if CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE
hid_critical_path_status_t hid_cp_kbd(uint8_t* data, uint16_t len, usb_plc_cb_param *plc_param);
#endif
#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
hid_critical_path_status_t hid_cp_nkey(uint8_t* data, uint16_t len, usb_plc_cb_param *plc_param);
#endif
/**
 * @brief   This function is used for application to initialize HID Critical Path KB.
 * @param[in]             #none.
 * @return                #0, the operation completed successfully.
 *                        #others, the operation has failed.
 */
int hid_critical_path_kb_init(void);

/**
 * @brief   This function is used for application to start HID Critical Path KB when CIS Connected.
 * @param[in]             #type, HID Critical Path Device Type.
 * @return                #none
 */
void hid_critical_path_kb_start(void);

/**
 * @brief   This function is used for application to stop HID Critical Path KB when CIS Disconnected.
 * @param[in]             #type, HID Critical Path Device Type.
 * @return                #none
 */
void hid_critical_path_kb_stop(void);

/**
 * @brief   This function is used for application to initialize HID Critical Path KB.
 * @param[in]             #none.
 * @return                #none
 */
void hid_critical_path_kb_deinit(void);

#endif