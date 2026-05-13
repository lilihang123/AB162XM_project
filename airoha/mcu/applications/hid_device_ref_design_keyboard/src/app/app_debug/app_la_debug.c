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

#include "app_la_debug.h"
#include "la_debug.h"
#include "hal_pinmux_define.h"

#define thisMODULE la_dbg
#define thisMOD    "la_dbg"
LOG_MODULE_REGISTER(thisMODULE);

/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/


/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
const T_LA_DEBUG_CFG_S la_dbg_pin[] =
{
    {47, PINMUX_FUN_GPIO }, //Nack
    {46, PINMUX_FUN_GPIO },

    {45, PINMUX_FUN_GPIO }, // Mouse RR key
    {44, PINMUX_FUN_GPIO },

    {39, PINMUX_FUN_GPIO },
    {38, PINMUX_FUN_GPIO },

    {43, PINMUX_FUN_GPIO },
    {42, PINMUX_FUN_GPIO },

    {28, PINMUX_FUN_GPIO },//latch

    {5, PINMUX_FUN_HW_CTRL_DEBUG }, // BT dbg
    {4, PINMUX_FUN_HW_CTRL_DEBUG }, // BT dbg
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
static bool app_la_debug__evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state* event = (struct evt_app_state*)evt_header;
    APP_LOGI(thisMOD, "app_la_debug__evt_app_state, event->state", event->app_state );

    switch(event->app_state)
    {
        case APP_STATE_CONNECT_PREPARING:
        {
            app_la_debug_init(NULL);
        }
        break;

        case APP_STATE_USB_CONNECTED:
        {
        }
        break;

        default:
            break;
    }

    return AF_TRAVERSE_NEXT;
}


/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
bool app_la_debug_init(T_GPIO_PIN_USAGE_LIST_S * pin_usage_list)
{
    APP_LOGI(thisMOD, "app_la_debug_init");
#if defined (CONFIG_AIR_HID_DEBUG_PIN)
    la_debug_init(la_dbg_pin, sizeof(la_dbg_pin)/sizeof(T_LA_DEBUG_CFG_S), 75,  true);
#endif

    APP_LOGI(thisMOD, "REG_GPIO_MODE [23_16]= 0x%08X, [15_08]= 0x%08X, [07_00]= 0x%08X", (unsigned int)(*(volatile uint32_t*)0x420b0038) , (unsigned int)(*(volatile uint32_t*)0x420b0034), (unsigned int)(*(volatile uint32_t*)0x420b0030));
    APP_LOGI(thisMOD, "REG_GPIO_MODE [47_40]= 0x%08X, [39_32]= 0x%08X, [31_24]= 0x%08X", (unsigned int)(*(volatile uint32_t*)0x420b0044), (unsigned int)(*(volatile uint32_t*)0x420b0040), (unsigned int)(*(volatile uint32_t*)0x420b003C));

    APP_LOGI(thisMOD, "REG_INPUT_PD [47_23]= 0x%07X, [22_00]= 0x%06X",  (unsigned int)(*(volatile uint32_t*)0x420d0050), (unsigned int)(*(volatile uint32_t*)0x420c0050));
    APP_LOGI(thisMOD, "REG_INPUT_PU [47_23]= 0x%07X, [22_00]= 0x%06X",  (unsigned int)(*(volatile uint32_t*)0x420d0070), (unsigned int)(*(volatile uint32_t*)0x420c0070));

    APP_LOGI(thisMOD, "REG_GPIO_DIR [47_32]= 0x%04X, [31_00]= 0x%08X",  (unsigned int)(*(volatile uint32_t*)0x420B0004), (unsigned int)(*(volatile uint32_t*)0x420B0000));

    return true;
}




/*============================Application Framework============================*/
/*=============================================================================*/
#if defined (CONFIG_AIR_HID_DEBUG_PIN)
AF_EVT_SUBSCRIBE_FUN_LOW(thisMODULE, evt_app_state, app_la_debug__evt_app_state);
#endif