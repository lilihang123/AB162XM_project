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
 

#include "app_sw_debounce.h"
#include "app_ccni.h"


#if defined(CONFIG_AIR_SW_KEY_DEBOUNCE)

#define thisMODULE app_sw_deb
#define thisMOD    "app_sw_deb"
LOG_MODULE_REGISTER(thisMODULE);

#define  SW_DB_UNIT_BT_MODE     1000
#define  SW_DB_UNIT_GAMING       125
#define  SW_DB_DEFAULT_STEPS_BT   3
#define  SW_DB_DEFAULT_STEPS      3

#define GET_1ST_SHORT_TIME(step, unit , period )        (((step * unit ) % period) == 0) ? unit : (  period - (((step ) * unit ) % period))

/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
static void app_sw_deb__updte_to_common_para(T_DEBOUNCE_PARA_S * config);
static uint32_t app_sw_deb_change_profile(uint8_t idx);
static uint8_t app_sw_deb_get_sw_debounce(T_DEBOUNCE_PARA_S **setting);
static uint8_t app_sw_deb_set_sw_debounce(T_DEBOUNCE_PARA_S deb);
static uint32_t app_sw_deb_sw_debounce_reload(uint8_t profile, bool restore);
/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
T_DEBOUNCE_PARA_S profile_sw_debounce_list[MAX_PROFILE_COUNT];
static uint8_t profile_idx = DEFAULT_PROFILE_IDX;
/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
static bool app_sw_deb__evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state* event = (struct evt_app_state*)evt_header;
    APP_LOGI(thisMOD,"app_sw_deb__evt_app_state , event->app_state = 0x%02X \n ", event->app_state);

    switch (event->app_state)
    {
        case APP_STATE_CONNECT_PREPARING:
        {
            app_sw_deb__updte_to_common_para(&profile_sw_debounce_list[profile_idx]);
        }
        break;

        default:
        break;
    }
    
    return AF_TRAVERSE_NEXT;
}


static void app_sw_deb_race_cmd_rsp_announcement(T_RACE_CMD_E cmd, uint8_t result, T_DEBOUNCE_PARA_S *setting)
{
    APP_LOGI(thisMOD,"app_sw_deb_race_cmd_rsp_announcement , result = %d", result);
    struct evt_race_cmd_rsp* event = create_evt_race_cmd_rsp();
    if (event){
        event->cmd = cmd;
        switch (cmd) {
            case RACE_CMD_GET_SW_DEBOUNCE:
                memcpy((uint8_t *)&event->SW_DEBOUNCE.settings, (uint8_t *)setting, sizeof(T_DEBOUNCE_PARA_S));
                break;

            case RACE_CMD_SET_SW_DEBOUNCE:
            case RACE_CMD_SET_PROFILE:
            case RACE_CMD_SET_RESTORE:
                event->OTHERS.status = result;
                break;

            default:
                break;
        }
        AF_EVT_SUBMIT(event);
    }
}

static bool app_sw_deb__evt_race_cmd_req(const struct af_evt_header *evt_header)
{
    struct evt_race_cmd_req* event = (struct evt_race_cmd_req*)evt_header;
    APP_LOGI(thisMOD,"evt_race_cmd_req , cmd = %x", event->cmd);
    uint8_t res;
    
    switch(event->cmd)
    {
        case RACE_CMD_SET_SW_DEBOUNCE:
        {
            res = app_sw_deb_set_sw_debounce(event->SW_DEBOUNCE.settings);
            app_sw_deb_race_cmd_rsp_announcement(RACE_CMD_SET_SW_DEBOUNCE, res, NULL);
        }
        break;

        case RACE_CMD_GET_SW_DEBOUNCE:
        {
            T_DEBOUNCE_PARA_S *deb_setting;
            res = app_sw_deb_get_sw_debounce(&deb_setting);
            app_sw_deb_race_cmd_rsp_announcement(RACE_CMD_GET_SW_DEBOUNCE, res, deb_setting);
        }
        break;

        case RACE_CMD_SET_PROFILE:
        {
            res = app_sw_deb_change_profile(event->PROFILE.id);
            app_sw_deb_race_cmd_rsp_announcement(RACE_CMD_SET_PROFILE, res, NULL);
        }
        break;

        case RACE_CMD_SET_RESTORE:
        {
            res = app_sw_deb_sw_debounce_reload(profile_idx, true);
            app_sw_deb_race_cmd_rsp_announcement(RACE_CMD_SET_RESTORE, res, NULL);
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
static uint32_t app_sw_deb_sw_debounce_reload(uint8_t profile, bool restore)
{
    bool result = false;
    APP_LOGI(thisMOD,"app_sw_deb_sw_debounce_reload");

    if(!restore)
    {
        result = app_nvkey_read_data((uint16_t) NVID_SW_DEBOUNCE_TIME_LIST, (uint8_t*)&profile_sw_debounce_list, sizeof(profile_sw_debounce_list));
    }
    
    if (!result)
    {
        for (int i = 0; i < MAX_PROFILE_COUNT; i++) 
        {
            profile_sw_debounce_list[i].step_wired = SW_DB_DEFAULT_STEPS;
            profile_sw_debounce_list[i].step_2_4g = SW_DB_DEFAULT_STEPS;
            profile_sw_debounce_list[i].step_bt = SW_DB_DEFAULT_STEPS_BT;
        }
 
        nvkey_status_t ret = nvkey_write_data(NVID_SW_DEBOUNCE_TIME_LIST , (const uint8_t*)&profile_sw_debounce_list , sizeof(profile_sw_debounce_list));
        if(ret)
        {
            APP_LOGI(thisMOD,"nvkey_write_data NVID_SW_DEBOUNCE_TIME_LIST err = %d", ret);
        }
    }
    
    profile_idx = profile;
    
    for (int i = 0; i < MAX_PROFILE_COUNT; i++) 
    {
        APP_LOGI(thisMOD, "SW deb Profile %d: wired = %d, 2.4G  = %d, BT = %d", i, profile_sw_debounce_list[i].step_wired, profile_sw_debounce_list[i].step_2_4g, profile_sw_debounce_list[i].step_bt);
    }
    return 0;
}

static uint8_t app_sw_deb_set_sw_debounce(T_DEBOUNCE_PARA_S settings)
{
    #define RACE_ERRCODE_SUCCESS 0 
    nvkey_status_t ret;
    
    profile_sw_debounce_list[profile_idx].step_wired = settings.step_wired;
    profile_sw_debounce_list[profile_idx].step_bt = settings.step_bt;
    profile_sw_debounce_list[profile_idx].step_2_4g = settings.step_2_4g;

    APP_LOGI(thisMOD,"app_sw_deb_set_sw_debounce wired = %d, 2.4G = %d, BT = %d", settings.step_wired, settings.step_2_4g, settings.step_bt);
    hid_common_set_app_para(PARA_TYPE_DEBOUNCE_CONFIG, (uint8_t*)&profile_sw_debounce_list[profile_idx], sizeof(T_DEBOUNCE_PARA_S));    

    ret = nvkey_write_data(NVID_SW_DEBOUNCE_TIME_LIST , (const uint8_t*)&profile_sw_debounce_list , sizeof(profile_sw_debounce_list));
    if(ret)
    {
        APP_LOGI(thisMOD,"nvkey_write_data NVID_SW_DEBOUNCE_TIME_LIST err = %d", ret);
    }
    
    struct evt_sw_deb_update* event = create_evt_sw_deb_update();
    if (event){
        AF_EVT_SUBMIT(event);
    }
    return RACE_ERRCODE_SUCCESS;
}

static uint8_t app_sw_deb_get_sw_debounce(T_DEBOUNCE_PARA_S **setting)
{  
    *setting = &profile_sw_debounce_list[profile_idx];

    APP_LOGI(thisMOD,"app_sw_deb_get_sw_debounce wired = %d, 2.4G = %d, deb_BT_step = %d", (*setting)->step_wired, (*setting)->step_2_4g, (*setting)->step_bt);

    return 0;
}

static uint32_t app_sw_deb_change_profile(uint8_t idx)
{
    APP_LOGI(thisMOD,"app_sw_deb_change_profile idx = %d", idx);
    /* There is no need to read each profile's data from the NVKEY,
    * since they are in RAM and may be newer than the NVKEY.*/
    profile_idx = idx;
    return 0;
}

static void app_sw_deb__updte_to_common_para(T_DEBOUNCE_PARA_S * config)
{
    APP_LOGI(thisMOD,"app_sw_deb__updte_to_common_para , step_bt =  %d, step_wired = %d, step_2_4g = %d"
        , config->step_bt
        , config->step_wired
        , config->step_2_4g
      );

    hid_common_set_app_para(PARA_TYPE_DEBOUNCE_CONFIG, (uint8_t*)config, sizeof(T_DEBOUNCE_PARA_S));
}

static bool app_sw_deb__evt_rr_status(const struct af_evt_header *evt_header)
{
    struct evt_rr_status* event = (struct evt_rr_status*)evt_header;
    APP_LOGI(thisMOD,"app_sw_deb__evt_rr_status , category = %d, RR = %d", event->category,  event->RR);

    APP_LOGI(thisMOD,"app_sw_deb__evt_rr_status , step_bt =  %d, step_wired = %d, step_2_4g = %d"
        , profile_sw_debounce_list[profile_idx].step_bt
        , profile_sw_debounce_list[profile_idx].step_wired
        , profile_sw_debounce_list[profile_idx].step_2_4g
      );

    hid_common_set_app_para(PARA_TYPE_DEBOUNCE_CONFIG, (uint8_t*)&profile_sw_debounce_list[profile_idx], sizeof(T_DEBOUNCE_PARA_S));

    return AF_TRAVERSE_NEXT;
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
void app_sw_deb_init(uint8_t profile_idx)
{
    app_sw_deb_sw_debounce_reload(profile_idx, false);
}

/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_app_state, app_sw_deb__evt_app_state);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_rr_status, app_sw_deb__evt_rr_status);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_race_cmd_req, app_sw_deb__evt_race_cmd_req);

/*=============================================================================*/


#endif  //CONFIG_AIR_SW_KEY_DEBOUNCE