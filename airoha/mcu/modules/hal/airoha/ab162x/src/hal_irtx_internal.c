/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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
#include "hal.h"
#include "hal_platform.h"
#include "hal_irtx_internal.h"
#include "hal_nvic.h"
// #include "hal_sleep_manager_platform.h"
#include "hal_clock.h"
#ifdef HAL_IRTX_MODULE_ENABLED
extern uint8_t ir_tx_status;
static hal_irtx_callback_t s_irtx_callback = NULL;
static void               *s_user_data = NULL;

#if 0
#define log_irtx_info(fmt, cnt, ...)     log_hal_msgid_info("[hal][rtc] " fmt, cnt, ##__VA_ARGS__)
#define log_irtx_warning(fmt, cnt, ...)  log_hal_msgid_warning("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#define log_irtx_error(fmt, cnt, ...)    log_hal_msgid_error("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#else
#define log_irtx_info(fmt, cnt, ...)     printk(fmt, ##__VA_ARGS__)
#define log_irtx_warning(fmt, cnt, ...)  printk(fmt, ##__VA_ARGS__)
#define log_irtx_error(fmt, cnt, ...)    printk(fmt, ##__VA_ARGS__)
#endif

void irtx_power_set(bool is_power_on){
#ifndef FPGA_ENV
    if(is_power_on == true){
        if (hal_clock_is_enabled(HAL_CLOCK_CG_IRTX) == false) {
            hal_clock_enable(HAL_CLOCK_CG_IRTX);
        }
    }else{
        if (hal_clock_is_enabled(HAL_CLOCK_CG_IRTX) == true) {
            hal_clock_disable(HAL_CLOCK_CG_IRTX);
        }
    }
#endif
}


void irtx_clock_div_set(uint32_t frequency)
{
    IRTX_REGISTER_T *irtx_register_base = (IRTX_REGISTER_T *)IRTX_BASE;
    uint8_t clock_div;
    if(frequency > IRTX_CLOCK_FREQUENCY){
        log_irtx_error("[hal][irtx][poll]:irtx set frequency %d error\r\n",1, frequency);
        return;
    }
    clock_div = IRTX_CLOCK_FREQUENCY / frequency;
    irtx_register_base->reg_0080_ir_tx_0.field.reg_ir_tx_ckdiv_num_0080 = clock_div -1;
}

int irtx_set_unit_value(uint8_t unit,uint16_t level1_us,uint16_t level2_us,bool level1_value,bool level2_value){

    IRTX_REGISTER_T *irtx_register_base = (IRTX_REGISTER_T *)IRTX_BASE;
    if(unit > IRTX_UNIT_MAX){
        log_irtx_error("[hal][irtx][poll]:irtx set unit value error, unit %d out of range\r\n",1,unit);
        return -1;
    }
    irtx_register_base->reg_level_cnt[unit].level1_cnt_t.field.level1_cnt = level1_us*(IRTX_CLOCK_SOURCE/1000000);
    irtx_register_base->reg_level_cnt[unit].level2_cnt_t.field.level2_cnt = level2_us*(IRTX_CLOCK_SOURCE/1000000);
    if(unit < 8){
        irtx_register_base->reg_level_value_0.word &= ~((0x3)<<(2*unit));
        irtx_register_base->reg_level_value_0.word |= (level2_value|(level1_value << 1))<<(2*unit);
    }else{
        irtx_register_base->reg_level_value_1.word &= ~((0x3)<<(2*(unit-8)));
        irtx_register_base->reg_level_value_1.word |= (level2_value|(level1_value << 1))<<(2*(unit-8));
    }
    return 0;
}

int irtx_set_total_cycle(uint32_t total_us){

    IRTX_REGISTER_T *irtx_register_base = (IRTX_REGISTER_T *)IRTX_BASE;
    uint32_t total_cycle = total_us*(IRTX_CLOCK_SOURCE/1000000);
    irtx_register_base->reg_total_cnt_1.field.reg_ir_tx_total_cycle_cnt_1 = (uint16_t)((total_cycle & 0xFFFF0000)>>16);
    irtx_register_base->reg_total_cnt_0.field.reg_ir_tx_total_cycle_cnt_0 = (uint16_t)(total_cycle & 0x0000FFFF);
    return 0;
}

// int    irtx_wait_idle_with_timeout(uint32_t timeout_us)
// {
// #define     IRTX_WAIT_IDLE_TIME_UNIT     100 //0.1ms

//     uint32_t  tick_pre = 0, tick_cur = 0, tick_dur = 0, count = 0, max_ms = 0;
//     uint32_t  save_mask;
//     int       result = 0;
//     volatile uint32_t *ptemp = NULL;
//     IRTX_REGISTER_T *irtx_register_base = (IRTX_REGISTER_T *)IRTX_BASE;
//     max_ms = timeout_us / IRTX_WAIT_IDLE_TIME_UNIT;
//     ptemp = &(irtx_register_base->reg_0090_ir_tx_0.word);

//     hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &tick_pre);
//     while (1) {
//         hal_nvic_save_and_set_interrupt_mask(&save_mask);
//         if (((*ptemp) & 0x1) == 1) {
//             result = 0;
//             break;
//         }
//         hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &tick_cur);
//         hal_gpt_get_duration_count(tick_pre, tick_cur, &tick_dur);
//         if (tick_dur > IRTX_WAIT_IDLE_TIME_UNIT) {
//             hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &tick_pre);
//             count++;
//         }
//         if (count > max_ms) {
//             result = -1;
//             break;
//         }
//         hal_nvic_restore_interrupt_mask(save_mask);
//     }
//     hal_nvic_restore_interrupt_mask(save_mask);
//     return result;
// }


void irtx_nvic_set(bool enable)
{
    hal_nvic_irq_t  irq_number;
    IRTX_REGISTER_T *irtx_register_base = (IRTX_REGISTER_T *)IRTX_BASE;

    irq_number = IRTX_IRQn;
    uint32_t  save_mask;
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    if (enable) {
        irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_int_en_0088 = 0x1;
        irtx_register_base->reg_0094_ir_tx_0.field.reg_ir_tx_clr_done_flag_0094 = 1;  /*clear irtx status*/
        hal_nvic_enable_irq(irq_number);
    } else {
        irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_int_en_0088  = 0x0;
        irtx_register_base->reg_0094_ir_tx_0.field.reg_ir_tx_clr_done_flag_0094 = 1;  /*clear irtx status*/
        hal_nvic_disable_irq(irq_number);
    }
    hal_nvic_restore_interrupt_mask(save_mask);
}

void irtx_isr(hal_nvic_irq_t irq_number)
{
    IRTX_REGISTER_T *irtx_register_base = (IRTX_REGISTER_T *)IRTX_BASE;
    if (IRTX_IRQn == irq_number) {
        uint8_t flag = irtx_register_base->reg_0090_ir_tx_0.field.reg_ir_tx_done_flag_0090;
        irtx_register_base->reg_0094_ir_tx_0.field.reg_ir_tx_clr_done_flag_0094 = 1;  /*clear irtx status*/
        irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_rstz_0088 = 0;
        ir_tx_status &= ~(1<<1);   //clear start status
        if(s_irtx_callback != NULL){
            if(flag){
                s_irtx_callback(HAL_IRTX_EVENT_TRANSACTION_SUCCESS, NULL);
            }else{
                s_irtx_callback(HAL_IRTX_EVENT_TRANSACTION_ERROR, NULL);
            }
        }
    }
}

void irtx_register_callback(hal_irtx_callback_t callback, void *user_data)
{
    s_irtx_callback = callback;
    s_user_data     = user_data;
    if (HAL_NVIC_STATUS_OK != hal_nvic_register_isr_handler(IRTX_IRQn, irtx_isr)) {
        return;
    }
}

uint32_t irtx_msb_transfer_lsb(uint32_t pdata, uint8_t bit_num){

    uint32_t data = 0;
    for(int i = 0;i<bit_num;i++){
        data = (data << 1) |(pdata & 1);
        pdata >>=1;
     }
    return data; 
}

void irtx_byte_bit_inverse(uint8_t *pdata, uint8_t inverse_byte_number)
{
    uint8_t data = 0;
    uint8_t tmp = 0;
    uint8_t i;

    for (i = 0; i < inverse_byte_number; i++) {
        data = *(pdata + i);
        tmp = ~data;
        *(pdata + i) = tmp;
    }
}

uint8_t irtx_byte_bit_shift(uint8_t data)
{
    data = (data << 4) | (data >> 4);
    data = ((data << 2) & 0xcc) | ((data >> 2) & 0x33);
    data = ((data << 1) & 0xaa) | ((data >> 1) & 0x55);

    return data;
}


uint16_t irtx_bit_transfer_shift(uint16_t data,uint8_t bitChunkSize,uint8_t totalBits)
{
    uint16_t return_data =0;
    uint8_t numChunks=totalBits/bitChunkSize;
    for(int i =0;i<numChunks;++i){
        uint8_t chunk = (data >> (i*bitChunkSize)) &((1<<bitChunkSize) -1);
        return_data |= chunk << (4*i);
    }
    return return_data;
}
#endif

