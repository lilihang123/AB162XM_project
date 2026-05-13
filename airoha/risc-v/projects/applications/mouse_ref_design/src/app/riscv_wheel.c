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
#include "stdio.h"
#include "stdint.h"
#include "syslog.h"
#include "hal_spi_master.h"
#include "riscv_wheel.h"
#include "hal_qdec.h"
#include "hid_common.h"
#include "riscv_wheel_ir_comparator.h"
#include "rv_application.h"
#include "riscv_peripheral_sampling.h"
#include "riscv_ccni.h"
#include "riscv_hid_express_key_queue_mouse.h"

#include "riscv_wheel_queue.h"
#include "hid_common.h"
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

uint8_t scroll_ctrl_pin_id;
uint8_t scroll_active_level;

/* Public variables ----------------------------------------------------------*/
uint32_t qdec_reverse_enable = false;
static uint32_t app_state = APP_STATE_NONE;
/* Private functions ---------------------------------------------------------*/
static void riscv_wheel_get_num(int16_t *number)
{
    int16_t queue_num;

    if (*number) {
        riscv_wheel_queue_pop_temp(&queue_num);

        if ((*number > 0 && queue_num > 0) || (*number < 0 && queue_num < 0)) {
            riscv_wheel_queue_update(*number);
        } 
        else {
            riscv_wheel_queue_push(*number);
        }
    }
    
    riscv_wheel_queue_pop_temp(&queue_num);

    if (queue_num > 0) {
        queue_num--;
        riscv_wheel_queue_update(-1);
        if (queue_num == 0) {
            riscv_wheel_queue_pop_confirm();
        }
        *number = 1;
    } 
    else if (queue_num < 0) {
        queue_num++;
        riscv_wheel_queue_update(1);
        if (queue_num == 0) {
            riscv_wheel_queue_pop_confirm();
        }
        *number = -1;
    }
}

/* Public functions ----------------------------------------------------------*/


int riscv_wheel_trigger_read_process()
{
    #if defined(AIR_WHEEL_IR_COMPARATOR)

    #else
    hal_qdec_set_latch_clear();
    #endif
    
    //LOG_MSGID_I(riscv_ps, "riscv_wheel_trigger_read_process", 0);

    return 0;
}

int riscv_wheel_get_data(int32_t * outgoing_z)
{
    int16_t number = 0;

    *outgoing_z = 0;
    
    #if defined(AIR_WHEEL_IR_COMPARATOR)
        riscv_wheel_ir_comp_get_data(&number);
    #else 
        bool hw_latch_busy;
        hal_qdec_status_t ret;   
        ret = hal_qdec_latch_status_is_busy(&hw_latch_busy);

        //LOG_MSGID_I(riscv_ps, "hal_qdec_latch_status_is_busy =%d", 1, ret);
        if (ret != HAL_QDEC_STATUS_OK)
        {
            return -1;
        }
        // get wheel data from QDEC
        hal_qdec_get_data(&number);
    #endif

    riscv_wheel_get_num(&number);

    if(qdec_reverse_enable)
    {
        *outgoing_z = -(int32_t)number;
    }
    else
    {
        *outgoing_z = (int32_t)number;
    }
    return 0;
}



void riscv_wheel_post_process()
{
    #if defined(AIR_WHEEL_IR_COMPARATOR)
    riscv_wheel_ir_comp_process();
    #endif
}

int riscv_wheel_init()
{
    if(QDEC_DIRECTION_REVERSE_ENABLE(hid_common->app.features))
    {
        qdec_reverse_enable = true;
    }

    scroll_ctrl_pin_id = hid_common->app.scroll_ctrl.id;
    scroll_active_level = hid_common->app.scroll_ctrl.para & 0x01;
    HID_DBG_LOG(riscv_ps, "riscv_wheel_init, qdec_reverse_enable = %d, scroll_ctrl_pin_id = %d, scroll_active_level = %d", 3 , qdec_reverse_enable, scroll_ctrl_pin_id, scroll_active_level);

    #if defined(AIR_WHEEL_IR_COMPARATOR)
        riscv_wheel_ir_comp_init();
    #endif 
    riscv_wheel_queue_init_q_ctrl();
    return 0;
}

void riscv_wheel_deinit()
{
    HID_DBG_LOG(riscv_ps, "riscv_wheel_deinit", 0);

    #if defined(AIR_WHEEL_IR_COMPARATOR)
    // disable qdec

    #endif

}

void riscv_wheel__app_state_update(uint32_t new_state)
{
    #if defined(AIR_WHEEL_IR_COMPARATOR)
    riscv_wheel_ir_comp__app_state_update(new_state);
    #endif

    switch(new_state)
    {
        case APP_STATE_DISCONNECTED:
        {
            riscv_wheel_deinit();
        }
        break;

        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_1:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1:
        {
        }
        break;

        default:
        break;
    }

    app_state = new_state;
}

#if defined(AIR_WHEEL_IR_COMPARATOR)
void riscv_wheel__notify_cm33_wheel_status(uint32_t new_wheel_status)
{
    if (peripheral_sampling__check_condiction(APP_CHECK_CONNECTED_ACTIVE) == false)
    {
        HID_DBG_LOG(riscv_ps, "riscv_wheel__notify_cm33_wheel_status", 0);

        uint8_t msg[5];
        msg[0] = HID_CCNI_MSG_POLLING_WHEEL_STATUS;
        *(uint32_t*)&msg[1] = new_wheel_status;

        riscv_app_ccin_send(msg, sizeof(msg));
        hid_express__push_to_key_queue(K_TYPE_Z1 ,new_wheel_status);
    }
}
#endif

void riscv_wheel_debug_print()
{
    #if defined(AIR_WHEEL_IR_COMPARATOR)
    riscv_wheel_ir_comp__debug_print();
    #endif
}

// #endif /*  */
