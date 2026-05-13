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
 



#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>


#include "app_scenario.h"
#include "app_riscv_trigger.h"
#include "hid_game_controller.h"


#define thisMODULE riscv_trig
#define thisMOD    "riscv_trig"

LOG_MODULE_REGISTER(thisMODULE);


/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
static void app_riscv_trigger___trigger_selector(bool triggered_by_bt);


/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/



/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/





/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
static bool app_riscv_trigger___evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state* event = (struct evt_app_state*)evt_header;
    

    switch(event->app_state)
    {
        case APP_STATE_DISCONNECTED:
        {
            app_riscv_trigger___trigger_selector(false);
        }
        break;

        case APP_STATE_CONNECT_PREPARING:
        {
            uint8_t curr_mode = app_scenario_get_scenario_type();
            if (HID_SCENARIO_USB_MODE == curr_mode){
                app_riscv_trigger___trigger_selector(false);
            }
            else
            {
                app_riscv_trigger___trigger_selector(true);
                #if defined(CONFIG_AIR_HW_KEYSCAN)
                app_scenario_config_bt_trigger_type(TRIGGER_TYPE_KEY_SCAN);
                #else
                app_scenario_config_bt_trigger_type(TRIGGER_TYPE_SPI);
                #endif /* CONFIG_AIR_HW_KEYSCAN */
            }

            APP_LOGI(thisMOD,"app_riscv_trigger___evt_app_state  event->app_state = 0x%x, curr_mode = %d " , event->app_state, curr_mode );
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
void app_riscv_trigger___trigger_selector(bool triggered_by_bt)
{
    APP_LOGI(thisMOD,"app_riscv_trigger___trigger_selector  triggered_by_bt = 0x%x  " , triggered_by_bt);

    if (triggered_by_bt){
        game_controller_bt_hw_trigger_enable();
    }
    else {
        game_controller_bt_hw_trigger_disable();
    }


}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/




/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_app_state, app_riscv_trigger___evt_app_state);

/*=============================================================================*/

