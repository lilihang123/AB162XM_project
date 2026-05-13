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
#include "rv_ccni.h"
#include "rv_hid_app.h"

/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
log_create_module(rv_ccni, PRINT_LEVEL_INFO);

/* Private variables ---------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

void rv_ccni__init()
{
    hal_ccni_unmask_event(APP_CCNI_EVENT_TO_RISCV);
}

void CCNI_DEF_HANDLER(3)(hal_ccni_event_t event, hal_ccni_message_t *msg)
{
    T_APP_CCNI_MSG_S * ccni_msg = (T_APP_CCNI_MSG_S *)msg;

    LOG_MSGID_I(rv_ccni, "rv_ccni_event_handler msg_id = 0x%02X, payload = 0x%08X"
        , 2
        , ccni_msg->msg_id
        , *(uint32_t*)&ccni_msg->payload[0]
        );

    switch(ccni_msg->msg_id)
    {
        case HID_CCNI_MSG_APP_STATE: // app_state
        {
            uint32_t cm33_app_state = ccni_msg->payload[0];
            rv_hid_app__cm33_state_update(cm33_app_state);
        }
        break;

        default:
        break;
    }
}

hal_ccni_status_t rv_ccni__send_to_CM33(uint8_t msg_id, uint8_t* payload, uint8_t len)
{
    hal_ccni_message_t msg;
    uint32_t data;

    if (len > 7) {
        return HAL_CCNI_STATUS_INVALID_PARAMETER; 
    }
    
    msg.data[0] = msg_id;
    memcpy( (uint8_t*)&msg.data[1] , payload , len);

    data = HAL_CCNI_EVENT_STATUS_BUSY;
    
    uint16_t retry_cnt = 0;
    #define MAX_CCNI_STATUS_RETRY_CNT 1000
    while((data == HAL_CCNI_EVENT_STATUS_BUSY) && (retry_cnt < MAX_CCNI_STATUS_RETRY_CNT)){
        retry_cnt++;
        hal_ccni_query_event_status(APP_CCNI_EVENT_TO_RISCV, &data);
    }
    assert( (retry_cnt < MAX_CCNI_STATUS_RETRY_CNT) && "Error : CM33 is busy");

    return hal_ccni_set_event(APP_CCNI_EVENT_TO_CM33, &msg);

}

// #endif /*  */

