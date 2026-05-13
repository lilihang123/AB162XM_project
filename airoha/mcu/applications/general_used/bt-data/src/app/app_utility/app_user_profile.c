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

#include "app_user_profile.h"
#include "user_profiles.h"


#define thisMODULE user_profile
#define thisMOD    "user_profile"
LOG_MODULE_REGISTER(thisMODULE);
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
static void app_user_profile_race_cmd_rsp_announcement(T_RACE_CMD_E cmd, uint8_t result);

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/


/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
static bool app_user_profile_evt_race_cmd_req(const struct af_evt_header *evt_header)
{
    struct evt_race_cmd_req* event = (struct evt_race_cmd_req*)evt_header;
    APP_LOGI(thisMOD,"evt_race_cmd_req , cmd = %x", event->cmd);

    uint8_t result;

    switch(event->cmd)
    {
        case RACE_CMD_SET_PROFILE:
        {
            result = user_profile_idx_set(event->PROFILE.id);
            app_user_profile_race_cmd_rsp_announcement(RACE_CMD_SET_PROFILE, result);
        }
        break;

        case RACE_CMD_GET_PROFILE:
        {
            result = user_profile_idx_get();
            app_user_profile_race_cmd_rsp_announcement(RACE_CMD_GET_PROFILE, result);
        }
        break;

        case RACE_CMD_SET_RESTORE:
        {
            result = user_profile_reload(true);
            app_user_profile_race_cmd_rsp_announcement(RACE_CMD_SET_RESTORE, result);
        }
        break;

        default:
        break;
    }
    return AF_TRAVERSE_NEXT;
}






/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static void app_user_profile_race_cmd_rsp_announcement(T_RACE_CMD_E cmd, uint8_t result)
{
    APP_LOGI(thisMOD,"app_user_profile_race_cmd_rsp_announcement");
    struct evt_race_cmd_rsp* event = create_evt_race_cmd_rsp();
    if (event){
        event->cmd = cmd;
        event->PROFILE.result = result;
        event->OTHERS.status = result;
        AF_EVT_SUBMIT(event);
    }
}



/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
uint8_t app_user_profile_init(void)
{
    return user_profile_init();
}




/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_race_cmd_req, app_user_profile_evt_race_cmd_req);
/*=============================================================================*/


