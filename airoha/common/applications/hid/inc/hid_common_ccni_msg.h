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

#ifndef _HID_COMMON_CCNI_MSG_H_
#define _HID_COMMON_CCNI_MSG_H_


/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "hal_gpio.h"

/* Public define -------------------------------------------------------------*/

/* Public typedef ------------------------------------------------------------*/

typedef enum
{
    // message from cm33 to risc-v
    HID_CCNI_MSG_APP_STATE = 0x10,
    HID_CCNI_MSG_FAKE_REPORT_ENABLE,
    HID_CCNI_MSG_FAKE_REPORT_CONFIG,
    HID_CCNI_MSG_KEY_REMAP_CONFIG,
    HID_CCNI_MSG_FEATURE_CONFIG,
    HID_CCNI_MSG_HOGP_ATTR_HANDLE, //0x15
    HID_CCNI_MSG_SET_DBG_PIN,
    HID_CCNI_MSG_SET_OUTPUT_CTRL_PIN, //0x17
    HID_CCNI_MSG_SET_FEATURE,
    HID_CCNI_MSG_COMMON_PARA_UPDATE,
    HID_CCNI_MSG_WAKEUP_KEY,
    HID_CCNI_MSG_USB_PLUG_OUT,
    HID_CCNI_MSG_KEY,

    // message from risv-v to cm33
    HID_CCNI_MSG_INACTIVITY_TIMEOUT = 0x81,
    HID_CCNI_MSG_FORCE_ALL_KEY_RELEASED,
    HID_CCNI_MSG_KEY_REMAP_TRIGGER,
    HID_CCNI_MSG_FAKE_REPORT_TERMINATE,
    HID_CCNI_MSG_PRINT_HID_REPORT_REQ,
    HID_CCNI_MSG_POLLING_KEY_STATUS,
    HID_CCNI_MSG_POLLING_WHEEL_STATUS,
    #if defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD) || defined(AIR_PRODUCT_TYPE_KEYBOARD)
    HID_CCNI_MSG_ADC_SCAN_START,
    #endif
    #if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER) || defined (CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    HID_CCNI_MSG_KEY_REMAP_QUEUE,
    #endif
}T_HID_CCNI_MSG_E;


/* Public macro --------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
/* Inline functions ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/


#endif /* _HID_COMMON_CCNI_MSG_H_ */
