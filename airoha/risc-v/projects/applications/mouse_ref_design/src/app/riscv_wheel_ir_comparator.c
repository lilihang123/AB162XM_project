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
#include "riscv_wheel.h"
#include "riscv_wheel_ir_comparator.h"
#include "comp_wheel.h"
#include "riscv_wheel_queue.h"

#if defined(AIR_WHEEL_IR_COMPARATOR)

// #define IR_COMP_DBG

#define COMP_WHEEL_IR_ON_TIME_US                                            80
#define COMP_WHEEL_SAMPLE_RATE_US                                         4000

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef struct
{
    uint32_t    wheel_pin_timeout_hdl;
    uint32_t    ir_comp_cnt;
    #if defined(IR_COMP_DBG)
    uint32_t    wheel_valid_cnt;
    uint32_t    wheel_pop_cnt;
    uint32_t    dbg_time_stamp;
    #endif
}T_WHEEL_PIN_CTRL_S;

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
T_WHEEL_PIN_CTRL_S wheel_ena_ctrl =
{
    .wheel_pin_timeout_hdl = 0,
};

/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void riscv_wheel_ir_comp_data_cb(int16_t  wheel_data)
{
    riscv_wheel_queue_push(wheel_data);
    if (wheel_data){
        #if defined(IR_COMP_DBG)
        wheel_ena_ctrl.wheel_valid_cnt++;
        #endif

        riscv_wheel__notify_cm33_wheel_status(wheel_data);
    }
}

void riscv_wheel_ir_comp_timeout(void* user_data)
{
    #if defined(IR_COMP_DBG)
    wheel_ena_ctrl.ir_comp_cnt++;
    #endif

    comp_wheel_scan_once(COMP_WHEEL_IR_ON_TIME_US);
    hal_gpt_sw_start_timer_us(wheel_ena_ctrl.wheel_pin_timeout_hdl, COMP_WHEEL_SAMPLE_RATE_US, riscv_wheel_ir_comp_timeout, NULL);
}

/* Public functions ----------------------------------------------------------*/
void riscv_wheel_ir_comp_process()
{
}

bool riscv_wheel_ir_comp_get_data(int16_t* number)
{
    riscv_wheel_queue_pop(number);
    return true;
}

void riscv_wheel_ir_comp_init()
{
    if (wheel_ena_ctrl.wheel_pin_timeout_hdl == 0) {
        hal_gpt_sw_get_timer(&wheel_ena_ctrl.wheel_pin_timeout_hdl);
    }

    HID_DBG_LOG(riscv_ps, "A riscv_wheel_ir_comp_init, wheel_ena_ctrl.wheel_pin_timeout_hdl = 0x%x", 1, wheel_ena_ctrl.wheel_pin_timeout_hdl);

    riscv_comp_wheel_config_t wheel_cfg = {
        .pin_led = 24,
        .up_pin = HAL_GPIO_SEL_GPIO28,
        .down_pin = HAL_GPIO_SEL_GPIO29,
    };

    comp_wheel_init(&wheel_cfg , riscv_wheel_ir_comp_data_cb);
    riscv_wheel_queue_init_q_ctrl();
}

void riscv_wheel_ir_comp_deinit()
{
    if (wheel_ena_ctrl.wheel_pin_timeout_hdl){
        hal_gpt_sw_stop_timer_us(wheel_ena_ctrl.wheel_pin_timeout_hdl);
        hal_gpt_sw_free_timer(wheel_ena_ctrl.wheel_pin_timeout_hdl);
        wheel_ena_ctrl.wheel_pin_timeout_hdl = 0;
    }

    HID_DBG_LOG(riscv_ps, "riscv_wheel_ir_comp_deinit , stop wheel polling timer (wheel_pin_timeout_hdl) = 0x%x", 1, wheel_ena_ctrl.wheel_pin_timeout_hdl);
    comp_wheel_deinit();
}

void riscv_wheel_ir_comp__app_state_update(uint32_t new_state)
{
    HID_DBG_LOG(riscv_ps, "riscv_wheel_ir_comp__app_state_update new_state = 0x%x", 1, new_state);

    switch(new_state)
    {
        case APP_STATE_DISCONNECTED:
        {
            riscv_wheel_ir_comp_deinit();
        }
        break;

        case APP_STATE_BT_CONNECTED:
        case APP_STATE_USB_CONNECTED:
        case APP_STATE_2_4G_CONNECTED:
        {
            hal_gpt_sw_stop_timer_us(wheel_ena_ctrl.wheel_pin_timeout_hdl);
            hal_gpt_sw_start_timer_us(wheel_ena_ctrl.wheel_pin_timeout_hdl, COMP_WHEEL_SAMPLE_RATE_US, riscv_wheel_ir_comp_timeout, NULL);
        }
        break;

        default:
        break;
    }
}

void riscv_wheel_ir_comp__debug_print()
{
    #if defined(IR_COMP_DBG)
    uint32_t current_gpt_free_count;
    uint32_t time_delta;
    GPT_GET_FREE_RUN_COUNT_US(current_gpt_free_count);
    hal_gpt_get_duration_count(wheel_ena_ctrl.dbg_time_stamp, current_gpt_free_count, &time_delta);

    if( time_delta > (1000000-(125/2)) ){
        HID_DBG_LOG(riscv_ps, "riscv_wheel_ir_comp__debug_print  ir_comp_cnt = %d,  wheel_valid_cnt = %d,  wheel_pop_cnt = %d ", 1, wheel_ena_ctrl.ir_comp_cnt, wheel_ena_ctrl.wheel_valid_cnt, wheel_ena_ctrl.wheel_pop_cnt);
        wheel_ena_ctrl.ir_comp_cnt = 0;
        wheel_ena_ctrl.wheel_valid_cnt = 0;
        wheel_ena_ctrl.wheel_pop_cnt = 0;
        GPT_GET_FREE_RUN_COUNT_US(wheel_ena_ctrl.dbg_time_stamp);
    }
    #endif
}


#endif /* AIR_WHEEL_IR_COMPARATOR */
