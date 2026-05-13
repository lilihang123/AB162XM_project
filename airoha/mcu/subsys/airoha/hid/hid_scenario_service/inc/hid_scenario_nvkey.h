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
 

#ifndef __HID_SCENARIO_NVKEY_H__
#define __HID_SCENARIO_NVKEY_H__

#include "nvkey_id_def.h"
#include "nvkey.h"

// #define HID_SCENARIO_NVKEY_ID           0x6100
// #define OFFSET_GAMING_TARGET            0x10
// #define OFFSET_RR_USER_DATAS            0x18
// #define OFFSET_DPI_USER_DATAS           0x20
// #define OFFSET_SENSOR_ATTR_USER_DATAS   0x28
// #define OFFSET_MACRO_USER1_DATAS        0x30
// #define OFFSET_MACRO_USER2_DATAS        0x38
// #define OFFSET_MACRO_USER3_DATAS        0x40
// #define OFFSET_MACRO_USER4_DATAS        0x48
// #define OFFSET_KEY_REMAP_DATAS          0x60
// #define OFFSET_PROFILE                  0x68

// typedef enum{
//     NVID_LOCAL_DEVICES_ADDR_ID_0 = HID_SCENARIO_NVKEY_ID,
//     NVID_LOCAL_DEVICES_ADDR_ID_1,
//     NVID_LOCAL_DEVICES_ADDR_ID_2,
//     NVID_LOCAL_DEVICES_ADDR_ID_3,
//     NVID_LOCAL_DEVICES_ADDR_ID_4,
//     NVID_LOCAL_DEVICES_ADDR_ID_5,
//     NVID_LOCAL_DEVICES_ADDR_ID_6,
//     NVID_LOCAL_DEVICES_ADDR_ID_7,

//     NVID_GAMING_MODE_PEER_DEVICE_INFO_0 = HID_SCENARIO_NVKEY_ID + OFFSET_GAMING_TARGET,
//     NVID_GAMING_MODE_PEER_DEVICE_INFO_1,
//     NVID_GAMING_MODE_PEER_DEVICE_INFO_2,
//     NVID_GAMING_MODE_PEER_DEVICE_INFO_3,

//     NVID_REPORT_RATE_LIST_0 = HID_SCENARIO_NVKEY_ID + OFFSET_RR_USER_DATAS,
//     NVID_REPORT_RATE_LIST_1,

//     NVID_DPI_SETTING_LIST_1 = HID_SCENARIO_NVKEY_ID + OFFSET_DPI_USER_DATAS,
//     NVID_DPI_SETTING_LIST_2,
//     NVID_DPI_SETTING_LIST_3,
//     NVID_DPI_SETTING_LIST_4,
    
//     NVID_SENSOR_ATTR_SETTING_1 = HID_SCENARIO_NVKEY_ID + OFFSET_SENSOR_ATTR_USER_DATAS,
//     NVID_SENSOR_ATTR_SETTING_2,
//     NVID_SENSOR_ATTR_SETTING_3,
//     NVID_SENSOR_ATTR_SETTING_4,

//     NVID_KEY_REMAP_MACRO_1_1 = HID_SCENARIO_NVKEY_ID + OFFSET_MACRO_USER1_DATAS,
//     NVID_KEY_REMAP_MACRO_1_2,
//     NVID_KEY_REMAP_MACRO_1_3,
//     NVID_KEY_REMAP_MACRO_1_4,
//     NVID_KEY_REMAP_MACRO_1_5,

//     NVID_KEY_REMAP_MACRO_2_1 = HID_SCENARIO_NVKEY_ID + OFFSET_MACRO_USER2_DATAS,
//     NVID_KEY_REMAP_MACRO_2_2,
//     NVID_KEY_REMAP_MACRO_2_3,
//     NVID_KEY_REMAP_MACRO_2_4,
//     NVID_KEY_REMAP_MACRO_2_5,

//     NVID_KEY_REMAP_MACRO_3_1 = HID_SCENARIO_NVKEY_ID + OFFSET_MACRO_USER3_DATAS,
//     NVID_KEY_REMAP_MACRO_3_2,
//     NVID_KEY_REMAP_MACRO_3_3,
//     NVID_KEY_REMAP_MACRO_3_4,
//     NVID_KEY_REMAP_MACRO_3_5,

//     NVID_KEY_REMAP_MACRO_4_1 = HID_SCENARIO_NVKEY_ID + OFFSET_MACRO_USER4_DATAS,
//     NVID_KEY_REMAP_MACRO_4_2,
//     NVID_KEY_REMAP_MACRO_4_3,
//     NVID_KEY_REMAP_MACRO_4_4,
//     NVID_KEY_REMAP_MACRO_4_5,

//     NVID_KEY_REMAP_PROFILE_1 = HID_SCENARIO_NVKEY_ID + OFFSET_KEY_REMAP_DATAS,
//     NVID_KEY_REMAP_PROFILE_2,
//     NVID_KEY_REMAP_PROFILE_3,
//     NVID_KEY_REMAP_PROFILE_4,

//     NVID_PROFILE_ID = HID_SCENARIO_NVKEY_ID + OFFSET_PROFILE,
// }HID_NVKEY_ID_ENUM;


#define HID_SCENARIO_NVKEY_READ_DATA(nvkey_id, p_dest, length) ({ \
    nvkey_status_t nvkey_ret; \
    uint32_t nvkey_size = length; \
    nvkey_ret = nvkey_read_data((uint16_t)nvkey_id, p_dest, &nvkey_size); \
    if ((nvkey_ret == NVKEY_STATUS_OK) && (nvkey_size == length)) { \
        DBG_LOGI(thisMOD, "hid_scenario_nvkey_read_data nvkey_id = %x ok ", nvkey_id); \
    } \
    nvkey_size; \
})

#define HID_SCENARIO_NVKEY_SAVE(nvkey_id, data, length) ({ \
    nvkey_status_t ret = nvkey_write_data((uint16_t)nvkey_id, data, length); \
    DBG_LOGI(thisMOD, "nvkey write data id = 0x%04X, ret = %d", nvkey_id, ret); \
    ret; \
})

#endif //__HID_SCENARIO_NVKEY_H__

