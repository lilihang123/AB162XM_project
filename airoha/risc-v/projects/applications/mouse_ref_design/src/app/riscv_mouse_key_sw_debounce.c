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
#include "riscv_mouse_key.h"
#include "riscv_mouse_key_sw_debounce.h"
#include "riscv_peripheral_sampling.h"
#include "hal_gpt.h"
#include "riscv_mouse_key_ir_ctrl.h"

#if defined(AIR_KEY_SW_DEBOUNCE)

/* Private define ------------------------------------------------------------*/
#define DEB_KEY_MASK    0x03   /** bit 0 : L-key; bit 1 : R-key; bit 2 : M-key; bit 3 : 4th-key; bit 4 : 5th-key; */
#define DEB_KEY_NUMBER  0x02

#define SW_DEBOUNCE_STEP_BT         1000
#define SW_DEBOUNCE_STEP_GAMING      125

#define SW_DEBOUNCE_PRE_PROCESS_TIME__TIMER_ISR      20
#define SW_DEBOUNCE_PRE_PROCESS_TIME__SPI_ISR      40

#if 1
#define SW_DEB_DBG_L(x)       DBG_LATENCY_L(x)
#define SW_DEB_DBG_H(x)       DBG_LATENCY_H(x)
#else 
#define SW_DEB_DBG_L(x)
#define SW_DEB_DBG_H(x)
#endif

#if 0
#define SW_DEB_DBG_LOG(module, message, arg_cnt, ...)        LOG_MSGID_I(module, message, arg_cnt, ##__VA_ARGS__ )
#else 
#define SW_DEB_DBG_LOG(module, message, arg_cnt, ...)  
#endif


/* Private typedef -----------------------------------------------------------*/
typedef enum 
{
    SW_DEBOUNCE_IDLE,
    SW_DEBOUNCE_TRIGGERED = 0x01,
    SW_DEBOUNCE_DEBOUNCING,
}T_SW_DEBOUNCE_STATE_E;


#define DEB_KEY_IS_PRESSED          1
#define DEB_KEY_IS_RELEASED         0

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
typedef struct 
{

    uint8_t state;    
    uint8_t count;
    uint8_t bit_idx;
    uint8_t debouncing_status;    
}T_SW_DEBOUNCE_SINGLE_KEY_S;

typedef enum
{
    DEB_POLLING_TYPE_OFF, 
    DEB_POLLING_TYPE_BT_ON,
    DEB_POLLING_TYPE_GAMING_ON,  
}T_DEB_POLLING_TYPE_E;

typedef struct 
{
    uint32_t timer_hdl;
    uint32_t output_status;
    uint32_t input_status;
    uint32_t interval_time;
    uint32_t interval_step;
    T_DEBOUNCE_PARA_S deb_para;
    T_SW_DEBOUNCE_SINGLE_KEY_S key[DEB_KEY_NUMBER];

    uint8_t app_state;
    uint8_t debounce_cnt;
    
}T_SW_DEBOUNCE_S;

T_SW_DEBOUNCE_S deb =
{
    .timer_hdl = 0,
};

void  riscv_sw_debounce__polling_reconfig(T_DEB_POLLING_TYPE_E type);
void riscv_sw_debounce_handler(uint32_t key_idx, uint32_t key_status, uint32_t key_changing );


/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/** timer timeout fro next debounce check process */
static void riscv_sw_debounce_timeout(void* user_data)
{
    SW_DEB_DBG_H(DBG_SIGNAL_DEBUG_3);
    // hal_gpt_get_free_run_count( HAL_GPT_CLOCK_SOURCE_1M , &deb.timer_isr_timestamp );
    riscv_mkey_ir_ctrl_on();
    hal_gpt_sw_stop_timer_us(deb.timer_hdl);
    hal_gpt_sw_start_timer_us(deb.timer_hdl,  deb.interval_time - 40  , riscv_sw_debounce_timeout, NULL);
    
    riscv_mkey_ir_ctrl_delay(40);
    
    deb.input_status = riscv_mouse_key_polling_all_key_status();
    
    deb.output_status &= ~0x0000001C;
    deb.output_status |= (deb.input_status & 0x0000001C);

    riscv_mkey_ir_ctrl_off();

    riscv_sw_debounce_post_process(true);

    // try to send notify to cm33 if need
    riscv_mouse_key__notify_cm33_key_status(deb.output_status);

    SW_DEB_DBG_L(DBG_SIGNAL_DEBUG_3);
}

static void riscv_sw_debounce_success(T_SW_DEBOUNCE_SINGLE_KEY_S *key, uint32_t key_bit)
{
    SW_DEB_DBG_H(DBG_SIGNAL_LATCH_REPORT);
    // debounce process complete if target count is reached
    key->state = SW_DEBOUNCE_IDLE;
    if (key->debouncing_status & key_bit ){
        // set it for key press
        deb.output_status |= key_bit;
    }
    else {
        // clear it for key release;
        deb.output_status &= ~key_bit;
    }
    SW_DEB_DBG_L(DBG_SIGNAL_LATCH_REPORT);
}

/** This is called at post process */
void riscv_sw_debounce_handler(uint32_t key_idx, uint32_t key_status, uint32_t key_changing )
{
    T_SW_DEBOUNCE_SINGLE_KEY_S *key = &deb.key[key_idx];

    switch(key->state)
    {
        case SW_DEBOUNCE_IDLE:
        {
            // DBG_LATENCY_H(DBG_SIGNAL_TX_NACK);
            if (key_changing){
                SW_DEB_DBG_H(DBG_SIGNAL_USB_TX_DONE);
                SW_DEB_DBG_H(DBG_SIGNAL_MAIN_LOOP);
                key->bit_idx = key_idx;
                key->debouncing_status = key_status;
                key->state = SW_DEBOUNCE_DEBOUNCING;
                key->count = 1;  // count to 1
                SW_DEB_DBG_L(DBG_SIGNAL_MAIN_LOOP);
                SW_DEB_DBG_L(DBG_SIGNAL_USB_TX_DONE);
            }
        }
        break;

        case SW_DEBOUNCE_DEBOUNCING:
         {
            SW_DEB_DBG_H(DBG_SIGNAL_USB_TX_DONE);
            if (key_changing){

                // if (deb.counting_in_critical_path == false) {
                    // debounce bit is holding. counter++
                    SW_DEB_DBG_H(24);
                    key->count++;
                    SW_DEB_DBG_L(24);
                // }

                if ((key->count >= (deb.interval_step)) // It is minused by 1 to ensure that the key will go out at next critical patch
                    || (deb.interval_step == 0)             // Incase deb.interval_step is 0. 
                    ) 
                {
                    riscv_sw_debounce_success(key, 0x01<< key->bit_idx );
                }
            }
            else {
                SW_DEB_DBG_H(DBG_SIGNAL_TX_NACK);
                key->state = SW_DEBOUNCE_IDLE;
                SW_DEB_DBG_L(DBG_SIGNAL_TX_NACK);
            }
            SW_DEB_DBG_L(DBG_SIGNAL_USB_TX_DONE);
        }
        break;
    };
}

/* Public functions ----------------------------------------------------------*/
/** This function is called in timing critical path */
uint32_t riscv_sw_debounce_process(uint32_t key_status)
{
    // keep the latest key status and handle it in post process
    deb.input_status = key_status;

    /** Update M key , FW key , and BW key status directly without sw debounce */
    deb.output_status &= ~0x0000001C;
    deb.output_status |= (key_status & 0x0000001C);

    /** update L R key status directly if debounce time is 0  */
    if (deb.interval_step == 0){
        SW_DEB_DBG_L(DBG_SIGNAL_DEBUG_3);
        uint32_t changed_bits = (deb.input_status & DEB_KEY_MASK) ^ deb.output_status ;

        for (uint32_t idx = 0; idx < DEB_KEY_NUMBER; idx ++ )
        {
            uint32_t key_bit = (0x1 << idx);
            if ((key_bit & changed_bits) ){
                if (key_status & key_bit ){
                    // set it for key press
                    deb.output_status |= key_bit;
                }
                else {
                    // clear it for key release;
                    deb.output_status &= ~key_bit;
                }
            } 
        }       
        SW_DEB_DBG_H(DBG_SIGNAL_DEBUG_3);
    }

    // always return latest debounce result no matter the debounce process is finished or not
    return deb.output_status;
}

uint32_t riscv_sw_debounce__get_debounce_output()
{
    return deb.output_status;
}

uint32_t riscv_sw_debounce_post_process(bool timer_isr)
{
    uint32_t idx;

    if (deb.interval_step ){
        // get changed bit : L-key, R-key, M-key, FW-key, BW-key
        uint32_t changed_bits = (deb.input_status & DEB_KEY_MASK) ^ deb.output_status ;

        for (idx = 0; idx < DEB_KEY_NUMBER; idx ++ )
        {
            SW_DEB_DBG_L(DBG_SIGNAL_DEBUG_3);
            uint32_t debouncing_key_status = (0x01 << idx) & deb.input_status;
            riscv_sw_debounce_handler(idx, debouncing_key_status, ((0x1 << idx) & changed_bits) );        
            SW_DEB_DBG_H(DBG_SIGNAL_DEBUG_3);
        } 
    }
    
    //SW_DEB_DBG_L(DBG_SIGNAL_DEBUG_3);
    // return the debounce check time for IR-PT module to turn on IR LED before debouncing 
    return 0;
}

uint32_t riscv_sw_debounce_config(uint32_t step, uint32_t time )
{
    return 0;
}

void riscv_sw_debounce_init()
{
    uint32_t idx;

    if (deb.timer_hdl == 0) {
        hal_gpt_sw_get_timer(&deb.timer_hdl);
    }

    SW_DEB_DBG_LOG(riscv_ps, "riscv_sw_debounce_init", 0);
    for (idx = 0 ; idx <DEB_KEY_NUMBER ; idx ++ ){
        deb.key[idx].state = SW_DEBOUNCE_IDLE;
    }
}

void riscv_sw_debounce_deinit()
{
    uint32_t idx;
    SW_DEB_DBG_LOG(riscv_ps, "riscv_sw_debounce_deinit ", 0);

    riscv_sw_debounce__polling_reconfig(DEB_POLLING_TYPE_OFF);

    if (deb.timer_hdl) {
        hal_gpt_sw_free_timer(deb.timer_hdl);
        deb.timer_hdl = 0;
    }

    for (idx = 0 ; idx <DEB_KEY_NUMBER ; idx ++ ){
        deb.key[idx].state = SW_DEBOUNCE_IDLE;
    }
}

void  riscv_sw_debounce__polling_reconfig(T_DEB_POLLING_TYPE_E type)
{
    SW_DEB_DBG_LOG(riscv_ps, "riscv_sw_debounce__polling_reconfig type = %d, deb.interval_time = %d  ", 2, type, deb.interval_time);
    switch(type)
    {
        case DEB_POLLING_TYPE_OFF:
        {
            hal_gpt_sw_stop_timer_us(deb.timer_hdl);
        }
        break;

        case DEB_POLLING_TYPE_BT_ON:
        {
            hal_gpt_sw_stop_timer_us(deb.timer_hdl);
            hal_gpt_sw_start_timer_us(deb.timer_hdl,  deb.interval_time , riscv_sw_debounce_timeout, NULL);
        }
        break;

        case DEB_POLLING_TYPE_GAMING_ON:
        {
            hal_gpt_sw_stop_timer_us(deb.timer_hdl);
            hal_gpt_sw_start_timer_us(deb.timer_hdl,  deb.interval_time, riscv_sw_debounce_timeout, NULL);
        }
        break;
    }
}

void  riscv_sw_debounce__app_state_update(uint32_t new_state)
{
    SW_DEB_DBG_LOG(riscv_ps, "riscv_sw_debounce__app_state_update new_state = 0x%x  ", 1, new_state);
    switch(new_state)
    {
        case APP_STATE_STANDBY:
        break;

        case APP_STATE_DISCONNECTED:
        {
            riscv_sw_debounce_deinit();
        }
        break;

        case APP_STATE_CONNECT_PREPARING:
            riscv_sw_debounce_init();
        break;

        case APP_STATE_BT_PAIRING:
        case APP_STATE_BT_RECONNECT:
        {
            riscv_sw_debounce_common_para_update();
        }
        break;

        case APP_STATE_2_4G_PAIRING:
        case APP_STATE_2_4G_RECONNECT:
        {
            riscv_sw_debounce_common_para_update();
        }
        break;

        case APP_STATE_BT_CONNECTED:
        {
            riscv_sw_debounce_common_para_update();
        }
        break;

        case APP_STATE_USB_CONNECTED:
        case APP_STATE_2_4G_CONNECTED:
        {
            riscv_sw_debounce_common_para_update();
        }
        break;

        case APP_STATE_USB_ACTIVE:
        case APP_STATE_2_4G_CONNECTED_ACTIVE:
        {
            riscv_sw_debounce_common_para_update();
        }
        break;

        case APP_STATE_2_4G_CONNECTED_IDLE_1:
        {
            riscv_sw_debounce_common_para_update();
        }
        break;

        case APP_STATE_USB_ENTERING_ACTIVE:
        case APP_STATE_2_4G_CONNECTED_ENTERING_ACTIVE:
        {
            riscv_sw_debounce_common_para_update();
        }
        break;
    }

    deb.app_state = new_state;
 }

void riscv_sw_debounce_common_para_update()
{
    memcpy( (uint8_t*)&deb.deb_para ,  (uint8_t*)&hid_common->app.deb, sizeof(T_DEBOUNCE_PARA_S));

    if ((riscv_app.state & APP_STATE_BT_CONNECTED ) || (riscv_app.state == APP_STATE_BT_PAIRING)|| (riscv_app.state == APP_STATE_BT_RECONNECT)) {
        // BT connected
        deb.interval_step = deb.deb_para.step_bt;
        deb.interval_time = SW_DEBOUNCE_STEP_BT;
        riscv_sw_debounce__polling_reconfig(DEB_POLLING_TYPE_BT_ON);
    }
    else {
        if((riscv_app.state & APP_STATE_USB_CONNECTED))
        {
            deb.interval_step = deb.deb_para.step_wired;
        }
        else
        {
            deb.interval_step = deb.deb_para.step_2_4g;
        }
        
        deb.interval_time = SW_DEBOUNCE_STEP_GAMING;

        if (peripheral_sampling__check_condiction(APP_CHECK_8K_CONNECTED)){
            if (peripheral_sampling__check_condiction(APP_CHECK_CONNECTED_ACTIVE)){
                riscv_sw_debounce__polling_reconfig(DEB_POLLING_TYPE_OFF);
            }
            else {
                riscv_sw_debounce__polling_reconfig(DEB_POLLING_TYPE_GAMING_ON);
            }
        }
        else {
            riscv_sw_debounce__polling_reconfig(DEB_POLLING_TYPE_GAMING_ON);
        }        
    }

    SW_DEB_DBG_LOG(riscv_ps,"riscv_sw_debounce_common_para_update, riscv_app.state = 0x%x,  interval_step = %d, interval_time = %d "
        , 3
        , riscv_app.state    
        , deb.interval_step                
        , deb.interval_time
    );
}

void riscv_sw_debounce_debug_print()
{
    // if ((deb.input_status != deb.input_status_printed) || (deb.output_status != deb.output_status_printed) ) {
    //     SW_DEB_DBG_LOG(riscv_ps,"riscv_sw_debounce_debug_print, intput_status = 0x%x,  output_status = 0x%x"
    //         , 2
    //         , deb.input_status
    //         , deb.output_status                
    //     );

    //     deb.input_status_printed = deb.input_status;
    //     deb.output_status_printed = deb.output_status;
    // }
}

#endif /* AIR_IRPT_DEBOUNCE */
