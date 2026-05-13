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
 
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>

#include "hid_labtest_service.h"

#define thisMODULE  labtest_serv
#define thisMOD    "labtest_serv"

LOG_MODULE_REGISTER(thisMODULE);

#if defined(CONFIG_LOG)
#define DBG_LOGI(module_name, format, ...)   \
        LOG_INF("["module_name"]" format, ## __VA_ARGS__)
#else
#define DBG_LOGI(module_name, format, ...)   \
        printk("["module_name"]"format, ## __VA_ARGS__)
#endif

/******************************************************************************/
/*  Private typedef                                                           */
/******************************************************************************/
#if defined(CONFIG_AIR_M21_SAMPLE) || defined(CONFIG_AIR_M21_3395)
#define MS_KEY_L     0
#define MS_KEY_R     1
#define MS_KEY_M    25 
#else
#define MS_KEY_L     5
#define MS_KEY_R     6
#define MS_KEY_M    17
#endif

/******************************************************************************/
/*  Private  macro                                                            */
/******************************************************************************/


/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
void hid_labtest_set_para();

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
const ble_gap_labtest_start_params_t labtest_default_param =
{
    LABTEST_MODE_DC_TONE,  //mode:TX
    0x0025,                //payload_len
    0x00,                  //tx_pattern
    LABTEST_RF_CH_0,       //start_channel
    0x04,                  //tx_gc1
    0x0F,                  //tx_gc2
    LABTEST_MODEM_PHY_1M
};

uint8_t hid_labtest_mode;
uint8_t hid_labtest_ch;
uint8_t hid_labtest_phy;

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
uint8_t hid_labtest__change_action_by_key_press(uint8_t key, uint8_t action)
{
    DBG_LOGI(thisMOD, "change_action_by_key_press: key = %d, action = %d", key, action);

    switch(key)
    {
        case MS_KEY_L:
        {
            break;
        }
        case MS_KEY_M:
        {
            break;
        }
        case MS_KEY_R:
        {
            break;
        }
        default:{
            break;
        }
    }

    hid_labtest_set_para();
    return 0;
}

void hid_labtest_set_para()
{
    ble_gap_labtest_start_params_t labtest_param;
    memcpy((void *)&labtest_param, (void *)&labtest_default_param, sizeof(ble_gap_labtest_start_params_t));
        
    labtest_param.phy = hid_labtest_phy;

    if(hid_labtest_ch == LABTEST_RF_FREQ_L)
    {
        if(hid_labtest_phy == LABTEST_MODEM_PHY_1M){
            labtest_param.rf_ch_idx = LABTEST_RF_CH_0;
        }
        else{
            labtest_param.rf_ch_idx = LABTEST_RF_CH_1; 
        }
    }
    else if(hid_labtest_ch == LABTEST_RF_FREQ_H)
    {
        if(hid_labtest_phy == LABTEST_MODEM_PHY_1M){
            labtest_param.rf_ch_idx = LABTEST_RF_CH_39;
        }
        else{
            labtest_param.rf_ch_idx = LABTEST_RF_CH_38;
        }
    }
    else{
        labtest_param.rf_ch_idx = LABTEST_RF_CH_19;               
    }

    if(hid_labtest_mode == LABTEST_MODE_DC_TONE)
    {
        labtest_param.mode = LABTEST_CTX_MODE;
        labtest_param.tx_pattern = 8;
    }
    else if(hid_labtest_mode == LABTEST_MODE_TX_MODE)
    {
        labtest_param.mode = LABTEST_CTX_MODE;
        labtest_param.tx_pattern = 0;
    }
    else// if(labtest_param_mode == LABTEST_MODE_RX_MODE)
    {
        labtest_param.mode = LABTEST_BRX_MODE;
        labtest_param.tx_pattern = 0;
    }
}