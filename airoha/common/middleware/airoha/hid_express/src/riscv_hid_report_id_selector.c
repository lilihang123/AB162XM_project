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


/* Includes ------------------------------------------------------------------*/
#include "riscv_hid_report_id_selector.h"
#include "riscv_hid_express.h"
/* Private define ------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/



/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/







uint32_t riscv_hid_report_id_select(T_OUTGOING_VALUES_S* outgoing)
{
    #if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP) && defined(AIR_PRODUCT_TYPE_MOUSE)
    if (outgoing->type == REPORT_ID_KB_STD)
    {
        /*
            Byte 0 : Combo type
            Byte 1 : Keycode 0 (first key)
            Byte 2 : Keycode 1 (second key)
            Byte 3 : Keycode 2 (third key)

            If Byte 3 is non-zero, 3 keys are pressed.
            Send standard keyboard report only, without xy data.
        */
        if((outgoing->kb_std[0] >> 24) & LSB)
        {
            return REPORT_ID_KB_STD;
        }
        else
        {
            return REPORT_ID_KB_STD_XY;
        }
    }
    else if (outgoing->type == REPORT_ID_KB_CONSUMER)
    {
        /*
            Byte 0, 1 : Consumer 0
            Byte 2, 3 : Conumser 1

            If Byte 2, 3 is non-zero, 2 keys are pressed.
            Send Consumer keyboard report only, without xy data.
        */
        if(outgoing->kb_consumer >> 16)
        {
            return REPORT_ID_KB_CONSUMER;
        }
        else
        {
            return REPORT_ID_KB_CONSUMER_XY;
        }
    }
    #endif

    return outgoing->type;
}
