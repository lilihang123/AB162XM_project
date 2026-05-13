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

#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>

#include "app_race_cmd.h"
#include "app_state.h"


#define thisMODULE app_mode_switch
#define thisMOD    "app_mode_switch"
LOG_MODULE_REGISTER(thisMODULE);

#define UNUSED(x)  ((void)(x))

#define RACE_RSP_MODE_2_4G      0x80 // original val: 0x80
#define RACE_RSP_MODE_BT        0x40
#define RACE_RSP_MODE_WIRED     0x20
#define RACE_RSP_SUCCESS        0x00
#define RACE_RSP_FAIL           0x01



/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/


/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
#if defined (CONFIG_AIR_KEYBOARD_M607)
bool app_mode_switch__evt_race_cmd_req(const struct af_evt_header *evt_header)
{
    struct evt_race_mode_switch* event = (struct evt_race_mode_switch*)evt_header;
    APP_LOGI(thisMOD, "app_mode_switch__evt_race_cmd_req, cmd = %x, mode = %x", event->cmd, event->kb_mode);
    uint8_t mode = 0;
    
    switch(event->kb_mode)
    {
        case RACE_RSP_MODE_2_4G:
        {
            mode = SLIDE_SWITCH_POS_GAMING;
            break;
        }
        
        case RACE_RSP_MODE_BT:
        {
            mode = SLIDE_SWITCH_POS_BT;
            break;
        }
        
        case RACE_RSP_MODE_WIRED:
        {
            mode = SLIDE_SWITCH_POS_OFF;
            break;
        }
        
        default:{
            break;
        }
    }
    // struct evt_slide_switch_status* mode_switch_event = create_evt_slide_switch_status();

    // if (mode_switch_event)
    // {
    //     mode_switch_event->position = mode;
    //     AF_EVT_SUBMIT(mode_switch_event);
    // }
    struct evt_mode_switch_status* mode_switch_event = create_evt_mode_switch_status();

    if (mode_switch_event)
    {
        mode_switch_event->position = mode;
        AF_EVT_SUBMIT(mode_switch_event);
    }

    return AF_TRAVERSE_NEXT;
}


#endif /*END CONFIG_AIR_KEYBOARD_M607*/

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
#if defined (CONFIG_AIR_KEYBOARD_M607)

void app_mode_switch__race_cmd_rsp_announcement(T_RACE_CMD_E cmd, uint8_t status)
{
    APP_LOGI(thisMOD, "app_mode_switch__race_cmd_rsp_announcement, status = 0x%X", status);
    struct evt_race_cmd_rsp* rsp_evt = create_evt_race_cmd_rsp();
    if (rsp_evt)
    {
        rsp_evt->cmd = cmd;
        rsp_evt->MODE_SWITCH.status = status;
        AF_EVT_SUBMIT(rsp_evt);
    }
    return;
}

#endif /*END CONFIG_AIR_KEYBOARD_M607*/

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/


/*============================Application Framework============================*/

#if defined (CONFIG_AIR_KEYBOARD_M607)
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_race_mode_switch, app_mode_switch__evt_race_cmd_req);
#endif /*END CONFIG_AIR_KEYBOARD_M607*/

/*=============================================================================*/