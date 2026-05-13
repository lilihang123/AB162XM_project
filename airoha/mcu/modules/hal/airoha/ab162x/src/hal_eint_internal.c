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

/*************************************************************************
 * Included header files
 *************************************************************************/

#include "hal_eint.h"

#ifdef HAL_EINT_MODULE_ENABLED
#include "hal_eint_internal.h"
#include "hal_nvic_internal.h"
#include "hal_log.h"
#include "hal_gpt.h"
#include "memory_attribute.h"

#ifdef HAL_TIME_CHECK_ENABLED
#include "hal_time_check.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct  {
    uint8_t  max_ms;
    uint8_t  prescaler;
    uint16_t clock;
} eint_config_debounce_t;

static const eint_config_debounce_t eint_deb_table[] = {
    { 0,  EINT_CON_PRESCALER_32KHZ, 0 },
    { 2,  EINT_CON_PRESCALER_32KHZ, 32768 },
    { 4,  EINT_CON_PRESCALER_16KHZ, 16384 },
    { 8,  EINT_CON_PRESCALER_8KHZ, 8192 },
    { 16, EINT_CON_PRESCALER_4KHZ, 4096 },
    { 32, EINT_CON_PRESCALER_2KHZ, 2048 },
    { 64, EINT_CON_PRESCALER_1KHZ, 1024 }
};

ATTR_RWDATA_IN_TCM EINT_REGISTER_T *EINT_REGISTER = (EINT_REGISTER_T *)EINT_BASE;

eint_function_t eint_function_table[HAL_EINT_NUMBER_MAX];

// #ifdef HAL_EINT_FEATURE_TIMESTAMP_COUNT
// extern volatile uint16_t  eint_count_value[EINT_COUNTER_NUMBER_MUX];
// extern volatile uint8_t  eint_count_number_table[HAL_EINT_NUMBER_MAX];
// extern volatile bool eint_count_enable_flag;
// #endif

ATTR_TEXT_IN_TCM uint32_t eint_get_status(uint32_t index)
{
    if (index > (HAL_EINT_NUMBER_MAX >> 5)) {
        return 0xFFFFFFFF;
    }
    return (EINT_REGISTER->EINT_STA[index]);
}

ATTR_TEXT_IN_TCM uint32_t eint_get_event(uint32_t index)
{
    if (index > (HAL_EINT_NUMBER_MAX >> 5)) {
        return 0xFFFFFFFF;
    }
    return (EINT_REGISTER->EINT_EEVT[index]);
}

ATTR_TEXT_IN_TCM void eint_ack_interrupt(uint32_t eint_number)
{
    uint32_t reg_index;
    uint32_t reg_shift;

    reg_index = eint_number / EINT_GROUP_MAX_NUMBER;
    reg_shift = 1 << (eint_number % EINT_GROUP_MAX_NUMBER);

    EINT_REGISTER->EINT_INTACK[reg_index] = reg_shift;
}

ATTR_TEXT_IN_TCM void eint_ack_wakeup_event(uint32_t eint_number)
{
    uint32_t reg_index;
    uint32_t reg_shift;

    reg_index = eint_number / EINT_GROUP_MAX_NUMBER;
    reg_shift = 1 << (eint_number % EINT_GROUP_MAX_NUMBER);

    EINT_REGISTER->EINT_EEVTACK[reg_index] = reg_shift;
}

uint32_t eint_caculate_debounce_time(uint32_t ms)
{
    uint32_t prescaler = EINT_CON_PRESCALER_32KHZ;
    uint32_t count = 0;
    uint8_t i;

    for (i = 0; i < 6; i++) {
        if (ms <= eint_deb_table[i].max_ms) {
            prescaler = eint_deb_table[i].prescaler;
            count = EINT_TIME_MS_TO_COUNT(ms, eint_deb_table[i].clock);
            break;
        }
    }

    count = (count | EINT_CON_DBC_EN_MASK |
             (EINT_CON_PRESCALER_MASK & (prescaler << EINT_CON_PRESCALER_OFFSET)));
    return count;
}

ATTR_TEXT_IN_TCM void hal_eint_isr(hal_nvic_irq_t index)
{
    uint32_t i;
    uint32_t reg_index;
    uint32_t eint_index;
    uint32_t status;

    for (reg_index = 0; reg_index < 2; reg_index++) {
        status = EINT_REGISTER->EINT_STA[reg_index];
        for (i = 0; status; i++) {
            if (status & (1 << i)) {
                eint_index = (reg_index << 5)  + i;
                if (eint_function_table[eint_index].eint_callback) {
// #ifdef HAL_EINT_FEATURE_TIMESTAMP_COUNT
//                     if(eint_count_enable_flag) {
//                         eint_count_value[eint_count_number_table[eint_index]] = EINT_REGISTER->EINT_TIMER_OUT[eint_count_number_table[eint_index]];
//                     }
// #endif
                    // hal_eint_mask((hal_eint_number_t)eint_index);
                    eint_function_table[eint_index].eint_callback(eint_function_table[eint_index].user_data);
                    hal_eint_clear_software_trigger(eint_index);
                    eint_ack_interrupt(eint_index);
                    eint_ack_wakeup_event(eint_index);
                } else {
                    //log_hal_msgid_error("ERROR: no EINT interrupt handler!\n", 0);
                }
                status &= ~(1 << i);
            }
        }
    }
}

void hal_eint_enable(uint32_t eint_number)
{   
    uint32_t reg_index;
    uint32_t reg_shift;

    reg_index = eint_number / EINT_GROUP_MAX_NUMBER;
    reg_shift = 1 << (eint_number % EINT_GROUP_MAX_NUMBER);
    EINT_REGISTER->EINT_ENABLE_SET[reg_index] |= reg_shift;
    // EINT_REGISTER->EINT_ENABLE[reg_index] |= reg_shift;
}

void hal_eint_disable(uint32_t eint_number)
{
    uint32_t reg_index;
    uint32_t reg_shift;

    reg_index = eint_number / EINT_GROUP_MAX_NUMBER;
    reg_shift = 1 << (eint_number % EINT_GROUP_MAX_NUMBER);
    EINT_REGISTER->EINT_ENABLE_CLR[reg_index] |= reg_shift;
    // EINT_REGISTER->EINT_ENABLE[reg_index] &= (~reg_shift);
}

uint8_t g_debounce[HAL_EINT_NUMBER_MAX];
void hal_eint_debonnce_config(uint32_t eint_number,uint8_t debounce)
{
    g_debounce[eint_number] = debounce;
}

void hal_eint_get_debounce_out_value_by_mask(uint32_t *value1,uint32_t *value2)
{
    *value1 = EINT_REGISTER->EINT_DBC_OUT[0];
    *value2 = EINT_REGISTER->EINT_DBC_OUT[1];
}

#ifdef __cplusplus
}
#endif

#endif /* HAL_EINT_MODULE_ENABLED */

