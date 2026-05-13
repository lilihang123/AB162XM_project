
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
#include "riscv_peripheral_sampling.h"
#include "hal_gpio_internal.h"
#include "hal_gpt_internal.h"
#include "hal_gpt.h"
#include "rv_application.h"
#include "riscv_mouse_key_ir_ctrl.h"
#include "riscv_mouse_key.h"
#include "mouse_sensor.h"

#define IRPT_DETEC_INTERVAL         125
#define KEY_MASK_L_R                0x03


#if defined(AIR_IRPT_PIN_CTRL)
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/

#if 0
#define IRPT_DBG_L(x)       DBG_LATENCY_L(x)
#define IRPT_DBG_H(x)       DBG_LATENCY_H(x)
#else 
#define IRPT_DBG_L(x)
#define IRPT_DBG_H(x)
#endif


bool IR_LED_status_on = false;  /** Protection for invalid key status reading */


#if defined(AIR_IRPT_PIN_CTRL_2ND)
#define IR_TURN_ON()                        hal_gpio_set_output(irpt.pin_id, !irpt.idle_level); hal_gpio_set_output(46, !irpt.idle_level); IR_LED_status_on=true;
#define IR_TURN_OFF()                       hal_gpio_set_output(irpt.pin_id, irpt.idle_level);  hal_gpio_set_output(46, irpt.idle_level);  IR_LED_status_on=false;
#else 
#define IR_TURN_ON()                        hal_gpio_set_output(irpt.pin_id, !irpt.idle_level); IR_LED_status_on=true;
#define IR_TURN_OFF()                       hal_gpio_set_output(irpt.pin_id, irpt.idle_level); IR_LED_status_on=false;
#endif


/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
typedef struct 
{
    uint32_t ir_turn_on_timestamp;
    uint32_t pin_id;
    uint32_t idle_level;
    uint32_t turn_on_timer_hdl;
    int32_t protect_cnt;
}T_IRPT_CTRL_S;

T_IRPT_CTRL_S irpt = 
{
    .turn_on_timer_hdl = 0,
    .protect_cnt = 0,
};

const uint8_t protect_cnt_non_bt_mode_tbl[]=
{
    2, //   RR = 125, unit = 8ms :  lifted debounct cnt = 2, ignore time = 16ms
    4, //   RR = 250, unit = 4ms :  lifted debounct cnt = 4, ignore time = 16ms
    8,//    RR = 500, unit = 2ms :  lifted debounct cnt = 8, ignore time = 16ms
    16,//   RR = 1000, unit = 1ms :  lifted debounct cnt = 16, ignore time = 16ms
    32,//   RR = 2000, unit = 0.5ms :  lifted debounct cnt = 32, ignore time = 16ms
    64,//   RR = 4000, unit = 0.25ms :  lifted debounct cnt = 64, ignore time = 16ms
    128,//  RR = 8000, unit = 0.125ms :  lifted debounct cnt = 128, ignore time = 16ms
};

#define PROTECT_COUNT_BT_MODE               3                                 //unit : 7.5ms
#define PROTECT_COUNT_NON_BT_MODE       (protect_cnt_non_bt_mode_tbl[riscv_app.rr_idx])


/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
uint32_t riscv_mkey_ir_ctrl_delay(uint32_t duration)
{
    uint32_t duration_count;
    uint32_t ir_check_timestamp;    

    do {
        //DBG_PING_L(46);
        GPT_GET_FREE_RUN_COUNT_US(ir_check_timestamp);
        hal_gpt_get_duration_count(irpt.ir_turn_on_timestamp, ir_check_timestamp, &duration_count);
        //DBG_PING_H(46);
    }while((duration_count < duration));

    return ir_check_timestamp;
}

void riscv_mkey_ir_ctrl_on()
{
    IR_TURN_ON();

    GPT_GET_FREE_RUN_COUNT_US(irpt.ir_turn_on_timestamp );
}

void riscv_mkey_ir_ctrl_off()
{
    IR_TURN_OFF();
}

void riscv_mkey_ir_ctrl_init()
{
    #if !defined(AIR_KEY_SW_DEBOUNCE)
    if (irpt.turn_on_timer_hdl ==0){
        hal_gpt_sw_get_timer(&irpt.turn_on_timer_hdl);
    }
    #endif

    HID_DBG_LOG(riscv_ps, "riscv_mkey_ir_ctrl_init , get timer (irpt.turn_on_timer_hdl) id = %d", 1, irpt.pin_id );
    irpt.pin_id = hid_common->app.irpt_ctrl.id;
    irpt.idle_level = hid_common->app.irpt_ctrl.para & 0x01;
}

void riscv_mkey_ir_ctrl_deinit()
{
    HID_DBG_LOG(riscv_ps, "riscv_mkey_ir_ctrl_deinit , stop and free timer(irpt.turn_on_timer_hdl)", 0);
    riscv_mkey_ir_ctrl_off();

    #if !defined(AIR_KEY_SW_DEBOUNCE)
    if (irpt.turn_on_timer_hdl) {
        hal_gpt_sw_stop_timer_us(irpt.turn_on_timer_hdl);
        hal_gpt_sw_free_timer(irpt.turn_on_timer_hdl);
        irpt.turn_on_timer_hdl = 0;
    }
    #endif
}

#if !defined(AIR_KEY_SW_DEBOUNCE)
static void riscv_mkey_ir_ctrl_idle_state_scan(void* user_data)
{
    uint32_t ir_timer_start, delta_time;
    IRPT_DBG_H(DBG_SIGNAL_USB_SOF);  
    riscv_mkey_ir_ctrl_on();
    hal_gpt_sw_stop_timer_us(irpt.turn_on_timer_hdl);
    hal_gpt_sw_start_timer_us(irpt.turn_on_timer_hdl, RR_IDX_TO_TIME_IN_MICRO_SEC(riscv_app.rr_idx) , riscv_mkey_ir_ctrl_idle_state_scan, NULL);
    GPT_GET_FREE_RUN_COUNT_US(ir_timer_start);
    hal_gpt_get_duration_count(irpt.ir_turn_on_timestamp, ir_timer_start, &delta_time);
    if(delta_time < IRPT_ON_TIME)
    {
        hal_gpt_delay_us(IRPT_ON_TIME - delta_time);
    }

    uint32_t key_status = riscv_mouse_key_polling_all_key_status();    

    // try to send notify to cm33 if need
    riscv_mouse_key__notify_cm33_key_status(key_status);
    riscv_mkey_ir_ctrl_off();
    IRPT_DBG_L(DBG_SIGNAL_USB_SOF);
}

static void riscv_mkey_ir_ctrl_idle_state_scan_stop()
{
    hal_gpt_sw_stop_timer_us(irpt.turn_on_timer_hdl);
}
#endif

void riscv_mkey_ir_ctrl__reset_cnt()
{
    if (riscv_app.state == APP_STATE_BT_RECONNECT){
        irpt.protect_cnt = PROTECT_COUNT_BT_MODE;
    }
    else {
        irpt.protect_cnt = PROTECT_COUNT_NON_BT_MODE;
    }
}

uint32_t riscv_mkey_ir_ctrl__ir_key_check(uint32_t ir_status, uint32_t key_status, uint32_t old_key_status )
{
    if (ir_status == false){
        // Error handling
        // Elliminate L/R key status if IR LED is off during polling process
        key_status &= (~KEY_MASK_L_R);
        key_status |= (old_key_status & KEY_MASK_L_R);
    }

    if (mouse_sensor_is_lifted()){
        if (irpt.protect_cnt == 0){
            riscv_mkey_ir_ctrl__reset_cnt();
        }

        // do debounce if mouse is lift
        if ((key_status & KEY_MASK_L_R)^(old_key_status & KEY_MASK_L_R)){
            irpt.protect_cnt--;

            if (irpt.protect_cnt > 0 ){
                return old_key_status;
            }
            else {
                riscv_mkey_ir_ctrl__reset_cnt();
                return key_status;
            }
            
        }
        else {
            riscv_mkey_ir_ctrl__reset_cnt();
            return key_status;
        }
    }
    else {
        if (irpt.protect_cnt > 0){
            // ignore new key status for a while
            irpt.protect_cnt--;
            return old_key_status;
        }
        else {
            return key_status;
        }
    }
}

void riscv_mkey_ir_ctrl_post_process(uint32_t next_read_key_time)
{
}

 void  riscv_mkey_ir_ctrl__app_state_update(uint32_t new_state)
 {
    switch(new_state)
    {
        case APP_STATE_CONNECT_PREPARING:
        {
            #if defined(AIR_IRPT_PIN_CTRL)
            riscv_mkey_ir_ctrl_init();
            #endif 
        }
        break;

        case APP_STATE_DISCONNECTED:
        {
            riscv_mkey_ir_ctrl_deinit();
        }
        break;

        case APP_STATE_BT_PAIRING:
        case APP_STATE_BT_RECONNECT:
        case APP_STATE_2_4G_PAIRING:
        case APP_STATE_2_4G_RECONNECT:
        {
            #if !defined(AIR_KEY_SW_DEBOUNCE)
            riscv_mkey_ir_ctrl_idle_state_scan(NULL);
            #endif
        }
        break;

        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_1:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1:
        {
            #if !defined(AIR_KEY_SW_DEBOUNCE)
            riscv_mkey_ir_ctrl_idle_state_scan(NULL);
            #endif
        }
        break;

        case APP_STATE_USB_ACTIVE:
        case APP_STATE_2_4G_CONNECTED_ACTIVE:
        case APP_STATE_BT_CONNECTED_ACTIVE:        
        case APP_STATE_BT_CONNECTED:
        case APP_STATE_USB_CONNECTED:
        case APP_STATE_2_4G_CONNECTED:
        {
            #if !defined(AIR_KEY_SW_DEBOUNCE)
            riscv_mkey_ir_ctrl_idle_state_scan_stop();
            #endif
        }
        break;

        default:
        break;
    }
 }

void riscv_mkey_ir_ctrl_debug_print()
{

}

#endif /*  */
