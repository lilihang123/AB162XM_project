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
#include <zephyr/logging/log.h>

#include "hid_scenario_service.h"
#include "hid_scenario_service_internal.h"
#include "hal_clock_internal.h"

#define thisMODULE clk
#define thisMOD    "clk"
LOG_MODULE_REGISTER(thisMODULE);
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/

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
void hid_scenario_clk_switch(uint8_t scenario)
{
    switch(scenario)
    {
        #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
        case HID_SCENARIO_BT_MODE:
        {
            //clock_mux_sel(CLK_IBEX_SEL, MUX_IBEX_IDX_XO);
            //clock_mux_sel(CLK_SYS_SEL, MUX_SYS_IDX_OSC_LS);
        }
        break;
        #endif

        case HID_SCENARIO_GAMING_MODE:
        case HID_SCENARIO_USB_MODE:
        {

        }
        break;
    }
    DBG_LOGI(thisMOD, "hid_scenario_clk_switch scenario = %d, CLK_IBEX_SEL = %d, CLK_SYS_SEL = %d" , 
                    scenario, clock_mux_cur_sel(CLK_IBEX_SEL),  clock_mux_cur_sel(CLK_SYS_SEL));
}
