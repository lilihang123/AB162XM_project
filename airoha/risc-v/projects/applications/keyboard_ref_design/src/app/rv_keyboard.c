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
 * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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

// #if defined()

/* Includes ------------------------------------------------------------------*/
#include "rv_application.h"
#include "rv_keyboard.h"

#include "riscv_peripheral_sampling.h"

#ifdef AIR_ADC_KEYSCAN_ENABLE
#include "adc_keyscan.h"
#endif

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
log_create_module(rv_kb, PRINT_LEVEL_INFO);


/* Public variables ----------------------------------------------------------*/
T_RV_KB_S rv_kb;


/* Private functions ---------------------------------------------------------*/
void rv_kb__preprocess()
{
    
}

void rv_kb__process()
{
    
}

void rv_kb__post_process()
{
    
}

/* Public functions ----------------------------------------------------------*/
void rv_kb__cm33_state_update(uint32_t new_state)
{
    LOG_MSGID_I(rv_kb, "rv_kb__cm33_state_update, new_state = 0x%02X ", 1, new_state);

    switch(new_state)
    {
        case APP_STATE_NONE:
        case APP_STATE_INITIALIZED:
        case APP_STATE_STANDBY:
        case APP_STATE_DISCONNECTED:
        case APP_STATE_TEST:
        case APP_STATE_CONNECT_PREPARING:
            break;

        case APP_STATE_BT_PAIRING:
        case APP_STATE_2_4G_PAIRING:
        case APP_STATE_BT_RECONNECT:
        case APP_STATE_2_4G_RECONNECT:
        case APP_STATE_2_4G_QUICK_CONNECT:
        case APP_STATE_CONNECT_CANCEL:
        case APP_STATE_CONNECT_CANCEL_CHECK:
            break;

        case APP_STATE_USB_CONNECTED:
        case APP_STATE_USB_ACTIVE:
        case APP_STATE_USB_SUSPEND:
        case APP_STATE_USB_ENTERING_ACTIVE:
        case APP_STATE_USB_DISCONNECTING:
            break;

        case APP_STATE_BT_CONNECTED: 
        case APP_STATE_BT_CONNECTED_ACTIVE:     
        case APP_STATE_BT_CONNECTED_IDLE_1:
        case APP_STATE_BT_CONNECTED_IDLE_2:
        case APP_STATE_BT_CONNECTED_IDLE_3:
        case APP_STATE_BT_CONNECTED_ENTERING_ACTIVE:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_1:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_2:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_3:
        case APP_STATE_BT_DISCONNECTING:
            break;

        case APP_STATE_2_4G_CONNECTED:
        case APP_STATE_2_4G_CONNECTED_ACTIVE:
        case APP_STATE_2_4G_CONNECTED_IDLE_1:
        case APP_STATE_2_4G_CONNECTED_IDLE_2:
        case APP_STATE_2_4G_CONNECTED_IDLE_3:
        case APP_STATE_2_4G_CONNECTED_ENTERING_ACTIVE:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_2:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_3:
        case APP_STATE_2_4G_DISCONNECTING:
            break;
    }
}

void rv_kb__init()
{
#ifdef AIR_ADC_KEYSCAN_ENABLE
    sw_keyscan_riscv_init();
#endif

    peripheral_sampling_init();
}

void rv_kb__deinit()
{
#ifdef AIR_ADC_KEYSCAN_ENABLE
    sw_keyscan_riscv_deinit();
#endif
}


// #endif /*  */
