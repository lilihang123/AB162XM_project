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

#include "hid_scenario_service.h"
#include "hid_scenario_service_internal.h"
#include "hid_scenario_report_rate.h"

#include "hid_power_mgr.h"
#include "nvkey.h"
#include "hid_race_cmd.h"
#include "hid_race_cmd_mouse.h"

#define thisMODULE rr
#define thisMOD    "rr"
LOG_MODULE_REGISTER(thisMODULE);
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
static void hid_scenario_rr__timeout_to_change_rr(struct k_timer *timer_id);

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
#define DEFAULT_RR_PROFILE_IDX  0
#define DELAY_TIME_TO_ASK_DONGLE_CHANGE_RR     50

/** report rate control structure */
typedef struct {
    struct k_timer      rr_change_timer;
    uint16_t            rr_usb;                             /** usb mode report rate */
    uint16_t            rr_2_4G_ideal;                      /** ideal gaming mode report rate */
    uint16_t            rr_2_4G_actual;                     /** actual gaming mode report rate */
    uint8_t     		rr_idx_2_4G;                        /** index of report rate table for gaming mode  */
    uint8_t     		rr_idx_usb;                         /** index of report rate table for usb mode */
    uint16_t            rr_list_0[USER_PROFILE_NUMBER];     /** report rate list for profile 0 */
    uint16_t            rr_list_1[USER_PROFILE_NUMBER];     /** report rate list for profile 1 */
    
    uint8_t     user_profile_idx;                   /** index of user profile */
}T_RR_CTROL_S; 


T_RR_CTROL_S rr_ctrl;


#define SUPPORTED_MASK_RR_TABLE_USB     0x3F   /** 125 ON, 500 ON, 1K ON, 2K ON, 4K ON, 8K ON */ 
#define SUPPORTED_MASK_RR_TABLE_2_4G    0x3F   /** 125 ON, 500 ON, 1K ON, 2K ON, 4K ON, 8K ON */ 

const uint16_t RR_TABLE_USB[]=
{
    125,
    500,
    1000,
    2000,
    4000,
    8000
};

const uint16_t RR_TABLE_2_4G[]=
{
    125,
    500,
    1000,
    2000,
    4000,
    8000
};

#define RR_TABLE_USB_SIZE       (sizeof(RR_TABLE_USB)/sizeof(uint16_t))
#define RR_TABLE_2_4G_SIZE      (sizeof(RR_TABLE_2_4G)/sizeof(uint16_t))


/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/

/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static uint8_t hid_scenario_rr_value_2_idx(uint16_t value, uint16_t * tbl, uint8_t tbl_size)
{
    uint8_t idx = 0 ;
    uint8_t i;

    for (i=0; i<tbl_size; i++)
    {
        if (value >= tbl[i]){
            // update the idx if the value is greater than the current table entry
            idx = i;
        }
        else {
            // idx was the closest index that is greater than or equal to the value
            break;
        }
    }

    return idx;
}

void hid_scenario_rr_write_nvkeys(uint16_t* list, uint32_t profile_id, uint16_t nvkey_id, uint16_t new_rr)
{
    if(list[profile_id] != new_rr)
    {
        list[profile_id] = new_rr;

        DBG_LOGI(thisMOD, "hid_scenario_rr_write_nvkeys, list at 0x%X, profile_id = %d, nvkey_id = %d, new_rr = %d"
            , list
            , profile_id
            , nvkey_id
            , new_rr
                );

        nvkey_status_t ret = nvkey_write_data(nvkey_id , (uint8_t*)list , sizeof(uint16_t)*USER_PROFILE_NUMBER);

        if (NVKEY_STATUS_OK != ret){    
            assert(0 && "hid_scenario_rr_write_nvkeys fail !");
        }
    }
}


uint16_t hid_scenario_rr_read_nvkeys(uint16_t* list, uint16_t nvkey_id, uint16_t default_val, uint8_t restore)
{
    uint32_t len = sizeof(uint16_t)*USER_PROFILE_NUMBER;

    DBG_LOGI(thisMOD, "hid_scenario_rr_read_nvkeys, list at 0x%X, profile_id = %d, nvkey_id = %d, default_val = %d"
        , list
        , rr_ctrl.user_profile_idx
        , nvkey_id
        , default_val
            );

    nvkey_status_t ret = nvkey_read_data(nvkey_id , (uint8_t*)list , &len);

    if (NVKEY_STATUS_OK != ret || restore){
        uint8_t idx;
        uint8_t val_diff = false;

        for(idx = 0; idx<USER_PROFILE_NUMBER; idx++)
        {
            if(list[idx] != default_val)
            {
                val_diff = true;
            }
            list[idx] = default_val;
        }

        DBG_LOGI(thisMOD, "hid_scenario_rr_read_nvkeys  list reset complete, profile_id = %d, list[0] = %d, list[1] = %d,  list[2] = %d,  list[3] = %d, val_diff = %d"
            , rr_ctrl.user_profile_idx
            , list[0]
            , list[1]
            , list[2]
            , list[3]
            , val_diff
             );
             
        
        if(val_diff)
        {
            nvkey_status_t w_ret = NVKEY_STATUS_ERROR;
            w_ret = nvkey_write_data(nvkey_id , (uint8_t*)list , sizeof(uint16_t)*USER_PROFILE_NUMBER);

            if (NVKEY_STATUS_OK != w_ret){    
            assert(0 && "write_nvkeys fail !");
            }
            else {
                DBG_LOGI(thisMOD, "write rr list complete, size = %d bytes"
                    , sizeof(uint16_t)*USER_PROFILE_NUMBER
                    );
            }
        }
    }

    if (rr_ctrl.user_profile_idx > USER_PROFILE_NUMBER){
        rr_ctrl.user_profile_idx = 0;
    }

    DBG_LOGI(thisMOD, "hid_scenario_rr_read_nvkeys completed, profile_id = %d, list[0] = %d, list[1] = %d"
        , rr_ctrl.user_profile_idx
        , list[0]
        , list[1]
        );

    return list[rr_ctrl.user_profile_idx];
}



/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
void hid_scenario_rr_init(uint8_t profile_idx)
{
    memset(&rr_ctrl, 0, sizeof(rr_ctrl));

    rr_ctrl.user_profile_idx = profile_idx;
    rr_ctrl.rr_usb    = hid_scenario_rr_read_nvkeys(rr_ctrl.rr_list_0,  NVID_REPORT_RATE_LIST_0, CONFIG_AIR_HID_DEVICE_USB_DEFAULT_REPORT_RATE, false);
    rr_ctrl.rr_2_4G_ideal = hid_scenario_rr_read_nvkeys(rr_ctrl.rr_list_1,   NVID_REPORT_RATE_LIST_1, CONFIG_AIR_HID_DEVICE_2_4G_DEFAULT_REPORT_RATE, false);
    rr_ctrl.rr_2_4G_actual = rr_ctrl.rr_2_4G_ideal;
    rr_ctrl.rr_idx_2_4G = hid_scenario_rr_value_2_idx(rr_ctrl.rr_2_4G_ideal, (uint16_t*)RR_TABLE_2_4G, RR_TABLE_2_4G_SIZE);
    rr_ctrl.rr_idx_usb = hid_scenario_rr_value_2_idx(rr_ctrl.rr_usb, (uint16_t*)RR_TABLE_USB, RR_TABLE_USB_SIZE);

    hid_scenario_update_comm_report_rate_para(MODE_TYPE_USB);

    DBG_LOGI(thisMOD, "hid_scenario_rr_init, size = %d-%d, rr_usb = %d, rr_2_4G_ideal = %d, rr_idx_2_4G = %d, rr_idx_usb = %d, user_profile_idx = %d " 
        , RR_TABLE_USB_SIZE
        , RR_TABLE_2_4G_SIZE
        , rr_ctrl.rr_usb
        , rr_ctrl.rr_2_4G_ideal
        , rr_ctrl.rr_idx_2_4G
        , rr_ctrl.rr_idx_usb
        , rr_ctrl.user_profile_idx
        );

    hid_scenario_send_notification(SS_EVT_USB_REPORT_RATE_UPDATE, (uint8_t*)&rr_ctrl.rr_usb, sizeof(rr_ctrl.rr_usb));
    hid_scenario_send_notification(SS_EVT_GAMING_REPORT_RATE_UPDATE, (uint8_t*)&rr_ctrl.rr_2_4G_ideal, sizeof(rr_ctrl.rr_2_4G_ideal));
    
    k_timer_init(&rr_ctrl.rr_change_timer , hid_scenario_rr__timeout_to_change_rr, NULL);
}

static void hid_scenario_rr__timeout_to_change_rr(struct k_timer *timer_id)
{
    if (rr_ctrl.rr_2_4G_actual != rr_ctrl.rr_2_4G_ideal){
        race_errcode_enum ret = hid_race_set_report_rate_req(rr_ctrl.rr_2_4G_ideal);

        DBG_LOGI(thisMOD, "hid_scenario_rr__timeout_to_change_rr  rr_2_4G_ideal (%d ) , ask dongle to change RR, ret = %d "
            , rr_ctrl.rr_2_4G_ideal
            , ret
        );
        #if CONFIG_AIR_HID_DUMMY_REPORT_RATE
        rr_ctrl.rr_2_4G_actual = rr_ctrl.rr_2_4G_ideal;
        #endif
    }
}

static void hid_scenario_idx_update_next(uint8_t* idx, uint8_t tbl_size, uint8_t mask)
{
    uint8_t temp_idx = *idx; 
    uint8_t cnt = 0;

    while( (cnt < REPORT_RATE_NUM))
    {
        cnt++;
        temp_idx = ((temp_idx + 1) >= tbl_size) ? 0 : temp_idx + 1 ;

        if ( (0x01<<temp_idx) & mask){
            *idx = temp_idx;
            return;
        }
    }
}

static void hid_scenario_idx_update_previous(uint8_t* idx, uint8_t tbl_size, uint8_t mask)
{
    uint8_t temp_idx = *idx; 
    uint8_t cnt = 0;

    while( (cnt < REPORT_RATE_NUM))
    {
        cnt++;
        temp_idx = (temp_idx == 0) ? (tbl_size - 1 ) : temp_idx - 1;

        if ( (0x01<<temp_idx) & mask){
            *idx = temp_idx;
            return;
        }
    }
}

static void hid_scenario_rr_change(uint8_t* idx, uint8_t type, uint16_t para, uint16_t* tbl, uint8_t tbl_size, uint8_t mask)
{
    DBG_LOGI(thisMOD, "hid_scenario_rr_change, type = %d, idx = %d, para = %d, mask = 0x%02X"
        , type
        , *idx
        , para
        , mask
        );

    switch(type)
    {
        case CONFIG_RR_NEXT:
        {
            hid_scenario_idx_update_next(idx, tbl_size, mask);
        }
        break;

        case CONFIG_RR_PREV:
        {
            hid_scenario_idx_update_previous(idx, tbl_size, mask);
        }
        break;

        case CONFIG_RR_SPECIFIC_IDX:
        {
            if (para < tbl_size){
                *idx = para;
            }
        }
        break;

        case CONFIG_RR_SPECIFIC_VAL:
        {
            *idx = hid_scenario_rr_value_2_idx(para, tbl, tbl_size);
        }
        break;

        default:
            //assert(0 && "Error : Invalid Report Rate Change Type !!");
            break;
    }
}

void hid_scenario_update_comm_report_rate_para(uint8_t category_id)
{
    T_HID_REPORT_RATE_VAL_S rr_val; 

    rr_val.rr_idx_usb = rr_ctrl.rr_idx_usb;
    rr_val.rr_idx_2_4g = rr_ctrl.rr_idx_2_4G;

    DBG_LOGI(thisMOD, "hid_scenario_update_comm_report_rate_para , rr_idx_usb = %d, rr_idx_2_4G = %d", rr_val.rr_idx_usb, rr_val.rr_idx_2_4g);

    hid_common_set_app_para(PARA_TYPE_RR_IDX, (uint8_t*)&rr_val,  sizeof(T_HID_REPORT_RATE_VAL_S));
}


void hid_scenario_report_rate_2_4G_record_update()
{
    rr_ctrl.rr_2_4G_ideal = RR_TABLE_2_4G[rr_ctrl.rr_idx_2_4G];
    hid_scenario_rr_write_nvkeys(rr_ctrl.rr_list_1 , rr_ctrl.user_profile_idx , NVID_REPORT_RATE_LIST_1,  hid_scenario_read_new_report_rate(MODE_TYPE_GAMING));
    // hid_scenario_send_notification(SS_EVT_GAMING_REPORT_RATE_UPDATE, (uint8_t*)&rr_ctrl.rr_2_4G_ideal, sizeof(rr_ctrl.rr_2_4G_ideal));
}

void hid_scenario_report_rate_USB_record_update()
{
    rr_ctrl.rr_usb = RR_TABLE_USB[rr_ctrl.rr_idx_usb];
    hid_scenario_rr_write_nvkeys(rr_ctrl.rr_list_0 , rr_ctrl.user_profile_idx , NVID_REPORT_RATE_LIST_0,  hid_scenario_read_new_report_rate(MODE_TYPE_USB));
    hid_scenario_send_notification(SS_EVT_USB_REPORT_RATE_UPDATE, (uint8_t*)&rr_ctrl.rr_usb, sizeof(rr_ctrl.rr_usb));     
}

void hid_scenario_report_rate_sync_wired_and_wireless(uint8_t category_id)
{
    #if defined(CONFIG_AIR_SYNC_REPORT_RATE_BETWEEN_USB_AND_2_4G)
    DBG_LOGI(thisMOD, "hid_scenario_report_rate_sync_wired_and_wireless");

    if (category_id == MODE_TYPE_USB){
        rr_ctrl.rr_idx_2_4G = rr_ctrl.rr_idx_usb;
        hid_scenario_report_rate_2_4G_record_update();
    }
    else {
        rr_ctrl.rr_idx_usb = rr_ctrl.rr_idx_2_4G;
        hid_scenario_report_rate_USB_record_update();
    }
    #endif
}

uint8_t hid_scenario_report_rate_change(uint8_t category_id,  uint8_t type, uint16_t para, uint8_t restore_or_chg_profile)
{
    uint8_t  rr_idx;
    if (category_id == MODE_TYPE_USB){
        if(restore_or_chg_profile)
        {
            hid_scenario_rr_change(&rr_ctrl.rr_idx_usb, CONFIG_RR_SPECIFIC_VAL, rr_ctrl.rr_list_0[rr_ctrl.user_profile_idx], (uint16_t*)RR_TABLE_USB,  RR_TABLE_USB_SIZE, SUPPORTED_MASK_RR_TABLE_USB);
        }
        else
        {
            hid_scenario_rr_change(&rr_ctrl.rr_idx_usb, type, para, (uint16_t*)RR_TABLE_USB,  RR_TABLE_USB_SIZE, SUPPORTED_MASK_RR_TABLE_USB);  
        }

        hid_scenario_report_rate_USB_record_update();
        hid_scenario_update_comm_report_rate_para(MODE_TYPE_USB);    
        rr_idx =  rr_ctrl.rr_idx_usb;
    }
    else {
        
        if(restore_or_chg_profile)
        {
            hid_scenario_rr_change(&rr_ctrl.rr_idx_2_4G, CONFIG_RR_SPECIFIC_VAL, rr_ctrl.rr_list_1[rr_ctrl.user_profile_idx], (uint16_t*)RR_TABLE_2_4G,  RR_TABLE_2_4G_SIZE, SUPPORTED_MASK_RR_TABLE_2_4G); 
        }
        else
        {
            hid_scenario_rr_change(&rr_ctrl.rr_idx_2_4G, type, para, (uint16_t*)RR_TABLE_2_4G,  RR_TABLE_2_4G_SIZE, SUPPORTED_MASK_RR_TABLE_2_4G);
        }

        hid_scenario_report_rate_2_4G_record_update();
        hid_scenario_update_comm_report_rate_para(MODE_TYPE_GAMING);
        rr_idx =  rr_ctrl.rr_idx_2_4G;
    }
   
    hid_scenario_report_rate_sync_wired_and_wireless(category_id);

    DBG_LOGI(thisMOD, "Change complete, usb_idx[%d] = %d, gaming_idx[%d] = %d "
    , rr_ctrl.rr_idx_usb
    , rr_ctrl.rr_usb
    , rr_ctrl.rr_idx_2_4G
    , rr_ctrl.rr_2_4G_ideal
    );

    return rr_idx;
}

void hid_scenario_report_rate__new_connection(uint8_t category_id,  uint16_t report_rate )
{
    uint16_t default_rr;
    if (category_id == MODE_TYPE_GAMING){
        default_rr = CONFIG_AIR_HID_DEVICE_2_4G_DEFAULT_REPORT_RATE;
    }
    else {
        default_rr = CONFIG_AIR_HID_DEVICE_USB_DEFAULT_REPORT_RATE;
    }

    DBG_LOGI(thisMOD, "hid_scenario_report_rate__new_connection  received dongle rr = (%d ), mouse default rr = (%d) ", report_rate , default_rr );

    hid_scenario_report_rate_change(category_id, CONFIG_RR_SPECIFIC_VAL, default_rr , false);   
}

void hid_scenario_report_rate_2_4G_change_start()
{
    k_timer_stop(&rr_ctrl.rr_change_timer);            
    k_timer_start(&rr_ctrl.rr_change_timer, K_MSEC(DELAY_TIME_TO_ASK_DONGLE_CHANGE_RR), K_NO_WAIT);
}

void hid_scenario_report_rate_validation_check(uint8_t category_id,  uint16_t para )
{
    if (category_id == MODE_TYPE_GAMING){
        if (para != rr_ctrl.rr_2_4G_ideal){
            DBG_LOGI(thisMOD, "hid_scenario_report_rate_validation_check  curr rr (%d ) != original rr (%d ), set a %d ms timer to ask dongle change rr "
                , para
                , rr_ctrl.rr_2_4G_ideal
                , DELAY_TIME_TO_ASK_DONGLE_CHANGE_RR
            );
            hid_scenario_report_rate_2_4G_change_start();
            hid_power_mgr__lock_LC_sleep_control(true);
        }
        else {
            DBG_LOGI(thisMOD, "hid_scenario_report_rate_validation_check  curr rr (%d ) is confirmed "
                , para
            );
            hid_scenario_send_notification(SS_EVT_GAMING_REPORT_RATE_UPDATE, (uint8_t*)&rr_ctrl.rr_2_4G_ideal, sizeof(rr_ctrl.rr_2_4G_ideal));
        }
        rr_ctrl.rr_2_4G_actual = para;
    }
}

uint16_t hid_scenario_read_now_report_rate(uint8_t category_id)
{
    if (category_id == MODE_TYPE_USB){
        return RR_TABLE_USB[rr_ctrl.rr_idx_usb];
    }
    else {
        return rr_ctrl.rr_2_4G_actual;
    }
}

uint16_t hid_scenario_read_new_report_rate(uint8_t category_id)
{
    if (category_id == MODE_TYPE_USB){
        return RR_TABLE_USB[rr_ctrl.rr_idx_usb];
    }
    else {
        return rr_ctrl.rr_2_4G_ideal;
    }
}

uint8_t hid_scenario_read_report_rate_idx(uint8_t category_id)
{
    if (category_id == MODE_TYPE_USB){
        return rr_ctrl.rr_idx_usb;
    }
    else {
        return rr_ctrl.rr_idx_2_4G;
    }
}

void hid_scenario_report_rate_change_profile(uint8_t profile_idx)
{
    rr_ctrl.user_profile_idx = profile_idx;
}

void hid_scenario_report_rate_restore()
{
    rr_ctrl.user_profile_idx = DEFAULT_RR_PROFILE_IDX;
    rr_ctrl.rr_usb    = hid_scenario_rr_read_nvkeys(rr_ctrl.rr_list_0,  NVID_REPORT_RATE_LIST_0, CONFIG_AIR_HID_DEVICE_USB_DEFAULT_REPORT_RATE, true);
    rr_ctrl.rr_2_4G_ideal = hid_scenario_rr_read_nvkeys(rr_ctrl.rr_list_1,   NVID_REPORT_RATE_LIST_1, CONFIG_AIR_HID_DEVICE_2_4G_DEFAULT_REPORT_RATE, true);
    rr_ctrl.rr_idx_2_4G = hid_scenario_rr_value_2_idx(rr_ctrl.rr_2_4G_ideal, (uint16_t*)RR_TABLE_2_4G, RR_TABLE_2_4G_SIZE);
    rr_ctrl.rr_idx_usb = hid_scenario_rr_value_2_idx(rr_ctrl.rr_usb, (uint16_t*)RR_TABLE_USB, RR_TABLE_USB_SIZE);
}


