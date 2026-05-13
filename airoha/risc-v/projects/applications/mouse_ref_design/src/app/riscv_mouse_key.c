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
#include "riscv_ccni.h"
#include "riscv_mouse_key.h"
#include "riscv_peripheral_sampling.h"
#include "pka_share.h"
#include "pka.h"
#include "hal_gpio_internal.h"
#include "hal_eint_internal.h"
#include "hal_gpt.h"
#include "hid_common.h"
#include "riscv_mouse_key_sw_debounce.h"
#include "riscv_mouse_key_ir_ctrl.h"
#include "riscv_hid_express_key_queue_mouse.h"

#define COMBO_KEY_NONE                          0xFF
#define PAIRING_COMBO_HOLD                         0

#define GPIO_FIRST_SECTION_MAX                  32
#define GPIO_SECOND_SECTION_MAX                 48

#define COMBO_BIT_PART_1_MAX    32
#define COMBO_KEY_BIT(key_id)        ((key_id <  COMBO_BIT_PART_1_MAX) ? (0x01<<key_id)   : (0x01<<(key_id-COMBO_BIT_PART_1_MAX)))

typedef struct {
    T_AIR_COMBO_KEY_S *combo_key_list;
    uint32_t combo_key_list_size;
    uint32_t hold_timeout;
    uint32_t app_state;
}T_COMBO_KEY_CFG_S;

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/



/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
static uint32_t start_gpt_free_count = 0;
static T_COMBO_KEY_CFG_S combo_cfg;

static uint32_t rv_key_num;
uint32_t rv_key_ids[RISCV_MAX_KEY_NUM] = {0};

static uint32_t mouse_5key = 0;
static uint32_t  mouse_5key_printed = 0;
static uint32_t combo_key_result = COMBO_KEY_NONE;

#if defined(AIR_IRPT_PIN_CTRL) || defined(AIR_FAKE_REPORT)
uint32_t new_keys_status_record = 0;
#endif

/* Public variables ----------------------------------------------------------*/


/* Private functions ---------------------------------------------------------*/
uint32_t riscv_mouse_key_polling_all_key_status()
{
    uint32_t idx;

    mouse_5key = 0; // all mouse key released 
    gpio_data_in_mask_t gpio_data_in_mask_temp;

    DBG_LATENCY_L(DBG_SIGNAL_SPI_CB);
    hal_eint_get_debounce_out_value_by_mask(&gpio_data_in_mask_temp.register0, &gpio_data_in_mask_temp.register1);

    #if defined(AIR_IRPT_PIN_CTRL)
    uint32_t ir_status = IR_LED_status_on;

    #if defined(AIR_KEY_SW_DEBOUNCE)
    if (peripheral_sampling__check_condiction(APP_CHECK_8K_CONNECTED))
    #endif
    {
        riscv_mkey_ir_ctrl_off();
    }
    #endif


    // gpio   : 0  is pressed , 1 is released 
    // ms key : 1  is pressed , 0 is released  
    uint32_t all_gpio_status_1 = ~gpio_data_in_mask_temp.register0;
    uint32_t all_gpio_status_2 = ~gpio_data_in_mask_temp.register1;    

    for (idx = 0 ; idx < rv_key_num ; idx++ )
    {
        if (rv_key_ids[idx] < GPIO_FIRST_SECTION_MAX ){
            if ( all_gpio_status_1 & (1 << (rv_key_ids[idx]))){
                // mouse key is pressed
                mouse_5key |= (1 << (idx));
            }
        }
        else if (rv_key_ids[idx] < GPIO_SECOND_SECTION_MAX  ){
            if ( all_gpio_status_2 & (1 << (rv_key_ids[idx]-32))){
                // mouse key is pressed
                mouse_5key |= (1 << (idx));
            }
        }
    }

    #if defined(AIR_IRPT_PIN_CTRL)
    mouse_5key = riscv_mkey_ir_ctrl__ir_key_check(ir_status, mouse_5key, new_keys_status_record);
    #endif

    return mouse_5key;
}

void update_key_status(uint32_t *all_gpio_status_1, uint32_t *all_gpio_status_2, uint32_t key_id_index, bool is_pressed) 
{
    uint32_t shift_value = COMBO_KEY_BIT(rv_key_ids[key_id_index]);

    if (rv_key_ids[key_id_index] < GPIO_FIRST_SECTION_MAX) {
        if (is_pressed) {
            *all_gpio_status_1 |= shift_value;
        } else {
            *all_gpio_status_1 &= ~shift_value;
        }
    } else {
        if (is_pressed) {
            *all_gpio_status_2 |= shift_value;
        } else {
            *all_gpio_status_2 &= ~shift_value;
        }
    }
}

uint32_t riscv_mouse_key_combo_key_check()
{
    uint32_t ret = COMBO_KEY_NONE;
    uint32_t combo_key_1, combo_key_2; 
    uint32_t combo_idx;
    gpio_data_in_mask_t gpio_data_in_mask_temp;


    hal_eint_get_debounce_out_value_by_mask(&gpio_data_in_mask_temp.register0, &gpio_data_in_mask_temp.register1);

    // gpio   : 0  is pressed , 1 is released 
    // ms key : 1  is pressed , 0 is released  
    uint32_t all_gpio_status_1 = ~gpio_data_in_mask_temp.register0;
    uint32_t all_gpio_status_2 = ~gpio_data_in_mask_temp.register1;    

    #if defined(AIR_IRPT_PIN_CTRL)
    // update IR-L key status
    update_key_status(&all_gpio_status_1, &all_gpio_status_2, 0, mouse_5key & 0x00000001);

    // update IR-r key status
    update_key_status(&all_gpio_status_1, &all_gpio_status_2, 1, mouse_5key & 0x00000002);
    #endif


    for (combo_idx = 0; combo_idx < combo_cfg.combo_key_list_size; combo_idx++)
    {
        combo_key_1 = combo_cfg.combo_key_list[combo_idx].combo_bit_00_31;
        combo_key_2 = combo_cfg.combo_key_list[combo_idx].combo_bit_32_63;
        
        if(((combo_key_1 & all_gpio_status_1) == combo_key_1) && ((combo_key_2 & all_gpio_status_2) == combo_key_2))
        {
            ret = combo_idx;
            break;
        }
    }
    return ret;
}

/* Public functions ----------------------------------------------------------*/
int riscv_mouse_key_init()
{
    uint32_t idx;

    rv_key_num = hid_common->app.mouse_key_num;
    for (idx = 0; idx < rv_key_num; idx++ )
    {
        rv_key_ids[idx] = hid_common->app.mouse_key_list[idx];
    }

    riscv_mouse_key_get_combo_key();
   
    LOG_MSGID_I(riscv_ps, "riscv_mouse_key_init, key_num = %d, rv_key_ids = %d, %d, %d, %d, %d, %d, %d, %d"
        , 10
        , rv_key_num
        , rv_key_ids[0]
        , rv_key_ids[1]
        , rv_key_ids[2]
        , rv_key_ids[3]
        , rv_key_ids[4]
        , rv_key_ids[5]
        , rv_key_ids[6]
        , rv_key_ids[7]
        );

    return 0;
}

void riscv_mouse_key_deinit()
{

}

void riscv_mouse_key_early_handle()
{
    hal_gpt_get_free_run_count( HAL_GPT_CLOCK_SOURCE_1M , &riscv_app.read_key_timestamp );    
    #if defined(AIR_IRPT_PIN_CTRL)
        #if defined(AIR_KEY_SW_DEBOUNCE)
        if (peripheral_sampling__check_condiction(APP_CHECK_8K_CONNECTED))
        #endif
        {
            riscv_mkey_ir_ctrl_on();
        }
    #endif
}

int riscv_mouse_key_get_key_status(uint32_t * outgoing_keys)
{
    uint32_t new_keys_status = 0;

    #if defined(AIR_IRPT_PIN_CTRL)
    riscv_app.read_key_timestamp = riscv_mkey_ir_ctrl_delay(IRPT_ON_TIME);
    #else
    hal_gpt_get_free_run_count( HAL_GPT_CLOCK_SOURCE_1M , &riscv_app.read_key_timestamp );
    #endif    

    #if defined(AIR_KEY_SW_DEBOUNCE)
        if (peripheral_sampling__check_condiction(APP_CHECK_8K_CONNECTED)){
            new_keys_status = riscv_mouse_key_polling_all_key_status();
            *outgoing_keys = riscv_sw_debounce_process(new_keys_status); 
        }
        else {
            *outgoing_keys = riscv_sw_debounce__get_debounce_output();
        }
    #else
        new_keys_status = riscv_mouse_key_polling_all_key_status();
        *outgoing_keys = new_keys_status;
    #endif

    // #if defined(AIR_IRPT_PIN_CTRL)
    //     #if defined(AIR_KEY_SW_DEBOUNCE)
    //     if (peripheral_sampling__check_condiction(APP_CHECK_8K_CONNECTED))
    //     #endif
    //     {
    //         DBG_LATENCY_L(DBG_SIGNAL_SPI_CB);
    //         riscv_mkey_ir_ctrl_off();
    //     }
    // #endif
    
    return SUCCESS;
}

void riscv_mouse_key_post_process()
{
    #if defined(AIR_IRPT_PIN_CTRL) || defined(AIR_KEY_SW_DEBOUNCE)
        uint32_t next_ir_on_time = 0; 
    #endif

    #if defined(AIR_KEY_SW_DEBOUNCE)
        if (peripheral_sampling__check_condiction(APP_CHECK_8K_CONNECTED)){
            next_ir_on_time = riscv_sw_debounce_post_process(false);
        }
    #endif

    #if defined(AIR_IRPT_PIN_CTRL)
    riscv_mkey_ir_ctrl_post_process(next_ir_on_time);
    #endif

    #if defined(AIR_IRPT_PIN_CTRL) || defined(AIR_FAKE_REPORT)
    new_keys_status_record = mouse_5key;
    #endif 
}

void riscv_mouse_key_get_combo_key()
{
    hid_common_get_combo_key_list(&combo_cfg.combo_key_list, &combo_cfg.combo_key_list_size, &combo_cfg.hold_timeout);
}

void riscv_mouse_key_change_state(uint32_t state)
{
    combo_cfg.app_state = state;
}

#if defined(AIR_FAKE_REPORT)
uint32_t riscv_mouse_keys_is_new_key_pressed()
{
    return mouse_5key && (new_keys_status_record != mouse_5key);
}
#endif

void riscv_mouse_key_pairing_key_check()
{
    if((combo_cfg.app_state & APP_STATE_CONNECTED) && (combo_cfg.app_state & 0x01))
    {
        uint32_t end_gpt_free_count = 0;
        uint32_t duration_count = 0;
        combo_key_result = riscv_mouse_key_combo_key_check();
        if((start_gpt_free_count != 0) && (combo_key_result == PAIRING_COMBO_HOLD))
        {
            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &end_gpt_free_count);
            hal_gpt_get_duration_count(start_gpt_free_count, end_gpt_free_count, &duration_count);
            if(duration_count >= (combo_cfg.hold_timeout << 15))
            {
                hid_common_set_hid_exp_flag(FLAG_BIT_FORCE_RELEASE_KEY);
                start_gpt_free_count = 0;
            }
        }
        else if(combo_key_result == PAIRING_COMBO_HOLD)
        {
            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &start_gpt_free_count);
        }
        else
        {
            start_gpt_free_count = 0;
        }
    }
}

void riscv_mouse_key__app_state_update(uint32_t new_state)
{
    DBG_LATENCY_H(DBG_SIGNAL_LATCH_REPORT);
    // LOG_MSGID_I(riscv_ps, "riscv_mouse_key__app_state_update  new_state = 0x%x " , 1, new_state);
    #if defined(AIR_KEY_SW_DEBOUNCE)
    riscv_sw_debounce__app_state_update(new_state);
    #endif 

    #if defined(AIR_IRPT_PIN_CTRL)
    riscv_mkey_ir_ctrl__app_state_update(new_state);
    #endif

    switch(new_state)
    {
        case APP_STATE_STANDBY:
        case APP_STATE_2_4G_CONNECTED_ENTERING_ACTIVE:
        case APP_STATE_BT_CONNECTED_ENTERING_ACTIVE:
        case APP_STATE_USB_ENTERING_ACTIVE:
        case APP_STATE_BT_CONNECTED:
        case APP_STATE_2_4G_CONNECTED:
        case APP_STATE_USB_CONNECTED:
        {

        }
        break;

        case APP_STATE_BT_RECONNECT:
        case APP_STATE_2_4G_RECONNECT:
        case APP_STATE_USB_SUSPEND:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_1:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1:
        {

        }
        break;

        case APP_STATE_DISCONNECTED:
        {
            riscv_mouse_key_deinit();
        }
        break;

        default:
        break;
    }

    DBG_LATENCY_L(DBG_SIGNAL_LATCH_REPORT);
}

void riscv_mouse_key_common_para_update()
{
    #if defined(AIR_KEY_SW_DEBOUNCE)
    riscv_sw_debounce_common_para_update();
    #endif
}

void riscv_mouse_key_debug_print()
{
    #if defined(AIR_IRPT_PIN_CTRL)
    riscv_mkey_ir_ctrl_debug_print();
    #endif

    #if defined(AIR_KEY_SW_DEBOUNCE)
    riscv_sw_debounce_debug_print();
    #endif

    if (mouse_5key_printed != mouse_5key){
        LOG_MSGID_I(riscv_ps, "mouse_5key = 0x%x --> 0x%x,  combo_key_list = 0x%08X-%08X, combo_key_list_size = 0x%x, combo_key_result = 0x%x, flags = 0x%x"
            , 7
            , mouse_5key_printed
            , mouse_5key
            , combo_cfg.combo_key_list[0].combo_bit_00_31
            , combo_cfg.combo_key_list[0].combo_bit_32_63
            , combo_cfg.combo_key_list_size
            , combo_key_result
            , hid_common->hid.flags
            );

        mouse_5key_printed = mouse_5key;
    }
}

void riscv_mouse_key__ccni_send_status(uint32_t new_keys_status)
{
    uint8_t msg[5];
    msg[0] = HID_CCNI_MSG_POLLING_KEY_STATUS;
    *(uint32_t*)&msg[1] = new_keys_status;

    riscv_app_ccin_send(msg, sizeof(msg));
}

#if defined(AIR_KEY_SW_DEBOUNCE) || defined(AIR_IRPT_PIN_CTRL)
void riscv_mouse_key__notify_cm33_key_status(uint32_t new_keys_status)
{
    if (peripheral_sampling__check_condiction(APP_CHECK_CONNECTED_ACTIVE) == false)
    {
        //DBG_LATENCY_H(DBG_SIGNAL_LATCH_REPORT);
        if (new_keys_status != new_keys_status_record){
            riscv_mouse_key__ccni_send_status(new_keys_status);
            hid_express__push_to_key_queue(K_TYPE_K, new_keys_status);
        }
        //DBG_LATENCY_L(DBG_SIGNAL_LATCH_REPORT);
    }
    new_keys_status_record = new_keys_status;
}
#endif

uint32_t riscv_mouse_key_id_to_key_status(uint32_t key_id)
{
    int found_idx = -1;
    for (int idx = 0; idx < rv_key_num; idx++) {
        if (rv_key_ids[idx] == key_id) {
            found_idx = idx;
            break;
        }
    }

    if (found_idx >= 0) {
        return (1 << found_idx);
    } else {
        return 0;
    }
}
// #endif /*  */