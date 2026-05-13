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

#include "app_factory_reset_mouse.h"
#include "app_factory_reset.h"

/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
const uint16_t nvkey_id_list[] =
{
    NVID_LINK_IDX, 
    NVID_DEBOUNCE_TIME_LIST,
    NVID_SW_DEBOUNCE_TIME_LIST,
    NVID_LOCAL_DEVICES_ADDR_ID_0, 
    NVID_LOCAL_DEVICES_ADDR_ID_1,
    NVID_LOCAL_DEVICES_ADDR_ID_2, 
    NVID_LOCAL_DEVICES_ADDR_ID_3,
    NVID_LOCAL_DEVICES_ADDR_ID_4, 
    NVID_LOCAL_DEVICES_ADDR_ID_5,
    NVID_LOCAL_DEVICES_ADDR_ID_6, 
    NVID_LOCAL_DEVICES_ADDR_ID_7,
    // NVID_GAMING_MODE_PEER_DEVICE_INFO_0, 
    // NVID_GAMING_MODE_PEER_DEVICE_INFO_1,
    // NVID_GAMING_MODE_PEER_DEVICE_INFO_2, 
    // NVID_GAMING_MODE_PEER_DEVICE_INFO_3,
    NVID_BT_MODE_PEER_DEVICE_ADDR_0,
    NVID_BT_MODE_PEER_DEVICE_ADDR_1,
    NVID_BT_MODE_PEER_DEVICE_ADDR_2,
    NVID_BT_MODE_PEER_DEVICE_ADDR_3,
    NVID_REPORT_RATE_LIST_0, 
    NVID_REPORT_RATE_LIST_1,
    NVID_DPI_SETTING_LIST_1, 
    NVID_DPI_SETTING_LIST_2,
    NVID_DPI_SETTING_LIST_3, 
    NVID_DPI_SETTING_LIST_4,
    NVID_SENSOR_ATTR_SETTING_1, 
    NVID_SENSOR_ATTR_SETTING_2,
    NVID_SENSOR_ATTR_SETTING_3, 
    NVID_SENSOR_ATTR_SETTING_4,
    NVID_KEY_REMAP_MACRO_1_1, 
    NVID_KEY_REMAP_MACRO_1_2,
    NVID_KEY_REMAP_MACRO_1_3, 
    NVID_KEY_REMAP_MACRO_1_4,
    NVID_KEY_REMAP_MACRO_1_5, 
    NVID_KEY_REMAP_MACRO_1_6, 
    NVID_KEY_REMAP_MACRO_1_7, 
    NVID_KEY_REMAP_MACRO_1_8, 
    NVID_KEY_REMAP_MACRO_1_9, 
    NVID_KEY_REMAP_MACRO_1_10, 
    NVID_KEY_REMAP_MACRO_2_1,
    NVID_KEY_REMAP_MACRO_2_2, 
    NVID_KEY_REMAP_MACRO_2_3,
    NVID_KEY_REMAP_MACRO_2_4, 
    NVID_KEY_REMAP_MACRO_2_5,
    NVID_KEY_REMAP_MACRO_2_6, 
    NVID_KEY_REMAP_MACRO_2_7, 
    NVID_KEY_REMAP_MACRO_2_8, 
    NVID_KEY_REMAP_MACRO_2_9, 
    NVID_KEY_REMAP_MACRO_2_10,
    NVID_KEY_REMAP_MACRO_3_1, 
    NVID_KEY_REMAP_MACRO_3_2,
    NVID_KEY_REMAP_MACRO_3_3, 
    NVID_KEY_REMAP_MACRO_3_4,
    NVID_KEY_REMAP_MACRO_3_5, 
    NVID_KEY_REMAP_MACRO_3_6, 
    NVID_KEY_REMAP_MACRO_3_7, 
    NVID_KEY_REMAP_MACRO_3_8, 
    NVID_KEY_REMAP_MACRO_3_9, 
    NVID_KEY_REMAP_MACRO_3_10,
    NVID_KEY_REMAP_MACRO_4_1,
    NVID_KEY_REMAP_MACRO_4_2, 
    NVID_KEY_REMAP_MACRO_4_3,
    NVID_KEY_REMAP_MACRO_4_4, 
    NVID_KEY_REMAP_MACRO_4_5,
    NVID_KEY_REMAP_MACRO_4_6, 
    NVID_KEY_REMAP_MACRO_4_7, 
    NVID_KEY_REMAP_MACRO_4_8, 
    NVID_KEY_REMAP_MACRO_4_9, 
    NVID_KEY_REMAP_MACRO_4_10,
    NVID_KEY_REMAP_PROFILE_1, 
    NVID_KEY_REMAP_PROFILE_2,
    NVID_KEY_REMAP_PROFILE_3, 
    NVID_KEY_REMAP_PROFILE_4,
    #if defined (CONFIG_AIR_REMAP_FN_KEY)
    NVID_KEY_REMAP_FN_KEY_1,
    NVID_KEY_REMAP_FN_KEY_2,
    NVID_KEY_REMAP_FN_KEY_3,
    NVID_KEY_REMAP_FN_KEY_4,
    #endif
    NVID_PROFILE_ID,
};

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/


/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/



/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
bool app_factory_reset_mouse_init()
{
    return app_factory_reset_hdl(nvkey_id_list, sizeof(nvkey_id_list)/sizeof(uint16_t)); 
}

/*============================Application Framework============================*/
/*=============================================================================*/