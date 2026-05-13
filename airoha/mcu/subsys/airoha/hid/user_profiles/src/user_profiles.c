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
 
#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include "user_profiles.h"
#include "hid_scenario_nvkey.h"
#include "hid_common.h"


#define thisMODULE  profile
#define thisMOD    "profile"

LOG_MODULE_REGISTER(thisMODULE);

/******************************************************************************/
/* macro                                                                      */
/******************************************************************************/

/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/


/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
static uint8_t user_profile_idx = DEFAULT_PROFILE_IDX;

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
uint8_t user_profile_reload(bool restore)
{
    bool res = HID_SCENARIO_NVKEY_READ_DATA(
                NVID_PROFILE_ID, 
                (uint8_t *)&user_profile_idx, 
                sizeof(uint8_t)
            );
    if (!res || restore)
    {
        user_profile_idx = DEFAULT_PROFILE_IDX;
        user_profile_idx_set(user_profile_idx);
    }
    DBG_LOGI(thisMOD, "user_profile_reload idx = %d", user_profile_idx);
    return 0;
}

uint8_t user_profile_idx_get()
{
    DBG_LOGI(thisMOD, "user_profile_idx_get idx = %d", user_profile_idx);
    return user_profile_idx;
}

uint8_t user_profile_idx_set(uint8_t idx)
{
    enum {
        RACE_ERRCODE_SUCCESS = 0,
        RACE_ERRCODE_NOT_SUPPORT = 2,
        RACE_ERRCODE_PARAMETER_ERROR = 3
    };

    if (idx > MAX_PROFILE_COUNT)
    {
        return RACE_ERRCODE_PARAMETER_ERROR;
    }

    int8_t ret = HID_SCENARIO_NVKEY_SAVE(NVID_PROFILE_ID, (const uint8_t *)&idx, sizeof(idx));

    if (ret == NVKEY_STATUS_OK)
    {
        user_profile_idx = idx;
        DBG_LOGI(thisMOD, "user_profile_idx_set idx = %d", user_profile_idx);
        return RACE_ERRCODE_SUCCESS;
    }
    return RACE_ERRCODE_NOT_SUPPORT;
}

uint8_t user_profile_init()
{
    user_profile_reload(false);
    return user_profile_idx;
}