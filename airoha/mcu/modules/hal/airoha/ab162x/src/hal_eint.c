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
#include <zephyr/sys/printk.h>
#ifdef HAL_EINT_MODULE_ENABLED
#include "hal_eint_internal.h"
#include "hal_nvic.h"
#include "hal_nvic_internal.h"
#include "hal_log.h"
#include "hal_gpt.h"
#include "memory_attribute.h"
#include "hal_cross_core_config.h"
#ifdef HAL_SLEEP_MANAGER_ENABLED
#include "hal_spm.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_internal.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAL_EINT_FEATURE_TIMESTAMP_COUNT
// volatile uint16_t  eint_count_value[EINT_COUNTER_NUMBER_MUX] = {0};
// volatile uint8_t   eint_count_number_table[HAL_EINT_NUMBER_MAX] = {0};
// volatile bool eint_count_enable_flag = false;
volatile uint8_t eint_count_table[EINT_COUNTER_NUMBER_MUX] = {0};
#endif

hal_eint_status_t hal_eint_init(hal_eint_number_t eint_number, const hal_eint_config_t *eint_config)
{
    hal_eint_status_t status;
    uint32_t mask;
    static bool is_initialized = false;
#ifdef HAL_SLEEP_MANAGER_ENABLED
    ao_backup_format_table_t eint;
    eint.module_base_addr = 0x42140000;
    eint.module_end_addr = 0x42140130;
    eint.module_backup_enable = 0x1;
#endif

    if (!is_initialized) {
        eint_ack_interrupt(eint_number);
        hal_nvic_register_isr_handler(EINT_IRQ_NUM, (hal_nvic_isr_t)hal_eint_isr);
        hal_nvic_enable_irq(EINT_IRQ_NUM);
#ifdef HAL_SLEEP_MANAGER_ENABLED
        sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_EINT, &eint);
#endif
        is_initialized = true;
    }

    if (eint_number >= HAL_EINT_NUMBER_MAX || eint_config == NULL) {
        return HAL_EINT_STATUS_INVALID_PARAMETER;
    }

    hal_nvic_save_and_set_interrupt_mask(&mask);
    eint_function_table[eint_number].eint_callback = NULL;
    eint_function_table[eint_number].user_data = NULL;
    hal_nvic_restore_interrupt_mask(mask);
    status  = hal_eint_set_trigger_mode(eint_number, eint_config->trigger_mode);
    status |= hal_eint_set_debounce_time(eint_number, eint_config->debounce_time);

    eint_ack_interrupt(eint_number);
    eint_ack_wakeup_event(eint_number);
    hal_eint_enable(eint_number);

    return status;
}

hal_eint_status_t hal_eint_deinit(hal_eint_number_t eint_number)
{
    uint32_t mask;

    if (eint_number >= HAL_EINT_NUMBER_MAX) {
        return HAL_EINT_STATUS_ERROR_EINT_NUMBER;
    }

    hal_nvic_save_and_set_interrupt_mask(&mask);
    eint_function_table[eint_number].eint_callback = NULL;
    eint_function_table[eint_number].user_data = NULL;

    eint_ack_interrupt(eint_number);
    hal_eint_mask(eint_number);
    hal_nvic_restore_interrupt_mask(mask);
    return HAL_EINT_STATUS_OK;
}

hal_eint_status_t hal_eint_register_callback(hal_eint_number_t eint_number,
                                             hal_eint_callback_t eint_callback,
                                             void *user_data)
{
    uint32_t mask;

    if (eint_number >= HAL_EINT_NUMBER_MAX || eint_callback == NULL) {
        return HAL_EINT_STATUS_INVALID_PARAMETER;
    }

    hal_nvic_save_and_set_interrupt_mask(&mask);
    eint_function_table[eint_number].eint_callback = eint_callback;
    eint_function_table[eint_number].user_data = user_data;
    hal_nvic_restore_interrupt_mask(mask);
    return HAL_EINT_STATUS_OK;
}


/***************************************** *******************************
    sensitivity:
                            1         level  (default)
                            0         edge
    polarity:               0         negative polarity  (default)
                            1         positive polarity

 *************************************************************************/
hal_eint_status_t hal_eint_set_trigger_mode(hal_eint_number_t eint_number, hal_eint_trigger_mode_t trigger_mode)
{
    uint32_t reg_index;
    uint32_t reg_shift;

    if (eint_number >= EINT_NUMBER_MAX) {
        return HAL_EINT_STATUS_INVALID_PARAMETER;
    }

    reg_index = eint_number / EINT_GROUP_MAX_NUMBER;
    reg_shift = 1 << (eint_number % EINT_GROUP_MAX_NUMBER);

    switch (trigger_mode) {
        case HAL_EINT_LEVEL_LOW:
            EINT_REGISTER->EINT_SENS_SET[reg_index] = reg_shift;
            EINT_REGISTER->EINT_POL_CLR[reg_index] = reg_shift;
            break;
        case HAL_EINT_LEVEL_HIGH:
            EINT_REGISTER->EINT_SENS_SET[reg_index] = reg_shift;
            EINT_REGISTER->EINT_POL_SET[reg_index] = reg_shift;
            break;
        case HAL_EINT_EDGE_FALLING:
            EINT_REGISTER->EINT_SENS_CLR[reg_index] = reg_shift;
            EINT_REGISTER->EINT_POL_CLR[reg_index] = reg_shift;
            EINT_REGISTER->EINT_DUALEDGE_CLR[reg_index] = reg_shift;
            break;
        case HAL_EINT_EDGE_RISING:
            EINT_REGISTER->EINT_SENS_CLR[reg_index] = reg_shift;
            EINT_REGISTER->EINT_POL_SET[reg_index] = reg_shift;
            EINT_REGISTER->EINT_DUALEDGE_CLR[reg_index] = reg_shift;
            break;
        case HAL_EINT_EDGE_FALLING_AND_RISING:
            /* DUALEGE depends on SENS */
            EINT_REGISTER->EINT_SENS_CLR[reg_index] = reg_shift;
            EINT_REGISTER->EINT_DUALEDGE_SET[reg_index] = reg_shift;
            break;
        default:
            return HAL_EINT_STATUS_INVALID_PARAMETER;
    }

    hal_gpt_delay_us(100);
    return HAL_EINT_STATUS_OK;
}

/* every count = 1/32k*/
hal_eint_status_t hal_eint_set_debounce_count(hal_eint_number_t eint_number, uint32_t count)
{
    uint32_t  eint_con;

    if (eint_number > HAL_EINT_NUMBER_47) { //only gpio 0~47 need to set debounce
        return HAL_EINT_STATUS_INVALID_PARAMETER;
    }

    if ((count & (~EINT_CON_DBC_CNT_MASK))) {
        return HAL_EINT_STATUS_INVALID_PARAMETER;
    }

    eint_con = (count | EINT_CON_DBC_EN_MASK | (EINT_CON_PRESCALER_MASK & (EINT_CON_PRESCALER_32KHZ << EINT_CON_PRESCALER_OFFSET)));

    if (count == 0) {
        /*disenable debounce bit*/
        EINT_REGISTER->EINT_CON_REGISTER[eint_number].EINT_CON_CELLS.DBC_EN = EINT_CON_DBC_DISABLE;
        /* can't reset debounce as it will cause 1/32k delay by debounce */
    } else {
        EINT_REGISTER->EINT_CON_REGISTER[eint_number].EINT_CON = 0;
        EINT_REGISTER->EINT_CON_REGISTER[eint_number].EINT_CON_CELLS.DBC_EN = EINT_CON_DBC_ENABLE;
        EINT_REGISTER->EINT_CON_REGISTER[eint_number].EINT_CON_CELLS.RSTDBC = EINT_CON_RSTD_BC_MASK;
        hal_gpt_delay_us(125);
        EINT_REGISTER->EINT_CON_REGISTER[eint_number].EINT_CON = eint_con;
        EINT_REGISTER->EINT_CON_REGISTER[eint_number].EINT_CON_CELLS.RSTDBC = EINT_CON_RSTD_BC_MASK;
    }

    return HAL_EINT_STATUS_OK;
}

hal_eint_status_t hal_eint_set_debounce_time(hal_eint_number_t eint_number, uint32_t time_ms)
{
    uint32_t  count, eint_con;

    if (eint_number > HAL_EINT_NUMBER_47) { //only gpio 0~47 need to set debounce
        return HAL_EINT_STATUS_INVALID_PARAMETER;
    }

    count = eint_caculate_debounce_time(time_ms);
    eint_con = count;

    if (time_ms == 0) {
        /*disenable debounce bit*/
        EINT_REGISTER->EINT_CON_REGISTER[eint_number].EINT_CON_CELLS.DBC_EN = EINT_CON_DBC_DISABLE;
        /* can't reset debounce as it will cause 1/32k delay by debounce */
    } else {
        EINT_REGISTER->EINT_CON_REGISTER[eint_number].EINT_CON = 0;
        EINT_REGISTER->EINT_CON_REGISTER[eint_number].EINT_CON_CELLS.DBC_EN = EINT_CON_DBC_ENABLE;
        EINT_REGISTER->EINT_CON_REGISTER[eint_number].EINT_CON_CELLS.RSTDBC = EINT_CON_RSTD_BC_MASK;
        hal_gpt_delay_us(125);
        EINT_REGISTER->EINT_CON_REGISTER[eint_number].EINT_CON = eint_con;
        EINT_REGISTER->EINT_CON_REGISTER[eint_number].EINT_CON_CELLS.RSTDBC = EINT_CON_RSTD_BC_MASK;

    }

    return HAL_EINT_STATUS_OK;

}

hal_eint_status_t hal_eint_ext_sleep_set_debounce_time(hal_eint_number_t eint_number, uint32_t time_ms)
{
    uint32_t  count, eint_con;

    if (eint_number > HAL_EINT_NUMBER_47) { //only gpio 0~47 need to set debounce
        return HAL_EINT_STATUS_INVALID_PARAMETER;
    }

    count = eint_caculate_debounce_time(time_ms);
    eint_con = count;

    if (time_ms == 0) {
        EINT_REGISTER->EINT_CON_REGISTER[eint_number].EINT_CON = 0;
        EINT_REGISTER->EINT_CON_REGISTER[eint_number].EINT_CON_CELLS.DBC_EN = EINT_CON_DBC_ENABLE;
        EINT_REGISTER->EINT_CON_REGISTER[eint_number].EINT_CON_CELLS.RSTDBC = EINT_CON_RSTD_BC_MASK;
    } else {
        EINT_REGISTER->EINT_CON_REGISTER[eint_number].EINT_CON = 0;
        EINT_REGISTER->EINT_CON_REGISTER[eint_number].EINT_CON_CELLS.DBC_EN = EINT_CON_DBC_ENABLE;
        EINT_REGISTER->EINT_CON_REGISTER[eint_number].EINT_CON_CELLS.RSTDBC = EINT_CON_RSTD_BC_MASK;
        hal_gpt_delay_us(125);
        EINT_REGISTER->EINT_CON_REGISTER[eint_number].EINT_CON = eint_con;
        EINT_REGISTER->EINT_CON_REGISTER[eint_number].EINT_CON_CELLS.RSTDBC = EINT_CON_RSTD_BC_MASK;

    }

    return HAL_EINT_STATUS_OK;
}

hal_eint_status_t hal_eint_set_software_trigger(hal_eint_number_t eint_number)
{
    //  uint32_t mask;
    uint32_t reg_index;
    uint32_t reg_shift;

    if (eint_number >= HAL_EINT_NUMBER_MAX) {
        return HAL_EINT_STATUS_INVALID_PARAMETER;
    }

    reg_index = eint_number / EINT_GROUP_MAX_NUMBER;
    reg_shift = 1 << (eint_number % EINT_GROUP_MAX_NUMBER);

    EINT_REGISTER->EINT_SOFT_SET[reg_index] = reg_shift;

    return HAL_EINT_STATUS_OK;
}

hal_eint_status_t hal_eint_clear_software_trigger(hal_eint_number_t eint_number)
{
    uint32_t reg_index;
    uint32_t reg_shift;

    if (eint_number >= HAL_EINT_NUMBER_MAX) {
        return HAL_EINT_STATUS_ERROR;
    }

    reg_index = eint_number / EINT_GROUP_MAX_NUMBER;
    reg_shift = 1 << (eint_number % EINT_GROUP_MAX_NUMBER);

    EINT_REGISTER->EINT_SOFT_CLR[reg_index] = reg_shift;
    return HAL_EINT_STATUS_OK;
}

ATTR_TEXT_IN_TCM hal_eint_status_t eint_mask_wakeup_source(hal_eint_number_t eint_number)
{
    uint32_t reg_index;
    uint32_t reg_shift;

    if (eint_number >= HAL_EINT_NUMBER_MAX) {
        return HAL_EINT_STATUS_INVALID_PARAMETER;
    }

    reg_index = eint_number / EINT_GROUP_MAX_NUMBER;
    reg_shift = 1 << (eint_number % EINT_GROUP_MAX_NUMBER);

    EINT_REGISTER->EINT_WAKEUP_MASK_SET[reg_index] = reg_shift;

    return HAL_EINT_STATUS_OK;
}

ATTR_TEXT_IN_TCM hal_eint_status_t eint_unmask_wakeup_source(hal_eint_number_t eint_number)
{
    uint32_t reg_index;
    uint32_t reg_shift;

    if (eint_number >= HAL_EINT_NUMBER_MAX) {
        return HAL_EINT_STATUS_INVALID_PARAMETER;
    }

    reg_index = eint_number / EINT_GROUP_MAX_NUMBER;
    reg_shift = 1 << (eint_number % EINT_GROUP_MAX_NUMBER);

    EINT_REGISTER->EINT_WAKEUP_MASK_CLR[reg_index] = reg_shift;

    return HAL_EINT_STATUS_OK;
}

#ifdef HAL_EINT_FEATURE_MASK
ATTR_TEXT_IN_TCM hal_eint_status_t hal_eint_mask(hal_eint_number_t eint_number)
{
    uint32_t reg_index;
    uint32_t reg_shift;

    if (eint_number >= HAL_EINT_NUMBER_MAX) {
        return HAL_EINT_STATUS_INVALID_PARAMETER;
    }

    reg_index = eint_number / EINT_GROUP_MAX_NUMBER;
    reg_shift = 1 << (eint_number % EINT_GROUP_MAX_NUMBER);

    EINT_REGISTER->EINT_D0EN_CLR[reg_index] = reg_shift;
    EINT_REGISTER->EINT_MASK_SET[reg_index] = reg_shift;
    eint_mask_wakeup_source(eint_number);

    return HAL_EINT_STATUS_OK;
}

ATTR_TEXT_IN_TCM hal_eint_status_t hal_eint_unmask(hal_eint_number_t eint_number)
{
    //  uint32_t mask;
    uint32_t reg_index;
    uint32_t reg_shift;

    if (eint_number >= HAL_EINT_NUMBER_MAX) {
        return HAL_EINT_STATUS_INVALID_PARAMETER;
    }

    reg_index = eint_number / EINT_GROUP_MAX_NUMBER;
    reg_shift = 1 << (eint_number % EINT_GROUP_MAX_NUMBER);

    /*eint and firq only one work*/
    EINT_REGISTER->EINT_D0EN_SET[reg_index] = reg_shift;
    EINT_REGISTER->EINT_MASK_CLR[reg_index] = reg_shift;
    hal_nvic_enable_irq(EINT_IRQ_NUM);
    eint_unmask_wakeup_source(eint_number);
    return HAL_EINT_STATUS_OK;
}
#endif

#ifdef HAL_EINT_FEATURE_TIMESTAMP_COUNT

hal_eint_status_t hal_eint_counter_enable(void)
{
    EINT_REGISTER->EINT_COUNTER_CTRL = 0x1;
    // eint_count_enable_flag = true;

    return HAL_EINT_STATUS_OK;
}

hal_eint_status_t hal_eint_counter_disable(void)
{
    // uint8_t i = 0;

    // eint_count_enable_flag = false;
    EINT_REGISTER->EINT_COUNTER_CTRL = 0x0;

    // for(i = 0; i < HAL_EINT_NUMBER_MAX; i++) {
    //     if(eint_count_number_table[i] != 0 ) {
    //         eint_count_value[eint_count_number_table[i]] = 0;
    //         eint_count_number_table[i] = 0;
    //     }
    // }

    return HAL_EINT_STATUS_OK;
}

hal_eint_status_t hal_eint_set_counter_number(hal_eint_number_t eint_number, eint_counter_number_t counter_number)
{
    if ((eint_number >= HAL_EINT_NUMBER_MAX) || (counter_number > EINT_COUNTER_NUMBER_9))
    {
        return HAL_EINT_STATUS_INVALID_PARAMETER;
    }

    EINT_REGISTER->EINT_TIMER_SEL[counter_number] = eint_number;
    // eint_count_number_table[eint_number] = counter_number;
    eint_count_table[counter_number] = eint_number;

    return HAL_EINT_STATUS_OK;
}

#if !IS_ENABLED(CONFIG_MCUBOOT) && !defined(AIR_DOWNLOAD_AGENT)
uint32_t hal_eint_get_counter_value(eint_counter_number_t counter_number)
{
    uint32_t counter_value;
    uint32_t real_value;

    volatile uint32_t *eint_count_value = (volatile uint32_t *)CROSS_CORE_MEM_VARIABLE(eint_count);

    // counter_value = eint_count_value[counter_number];
    counter_value = EINT_REGISTER->EINT_TIMER_OUT[counter_number];
    if(counter_value != 0) {
        real_value = counter_value;
        eint_count_value[counter_number] = counter_value;
    } else {
        real_value = eint_count_value[counter_number];
    }

    eint_ack_interrupt(eint_count_table[counter_number]);  //clear timestamp

    return real_value;
}
#endif

uint32_t hal_eint_get_free_counter_value(void)
{
    return EINT_REGISTER->EINT_COUNTER_OUT;
}

hal_eint_status_t hal_eint_toggle_set(hal_eint_number_t eint_number,bool toggle)
{
    uint32_t reg_index;
    uint32_t reg_shift;

    if (eint_number >= HAL_EINT_NUMBER_MAX) {
        return HAL_EINT_STATUS_INVALID_PARAMETER;
    }

    reg_index = eint_number / EINT_GROUP_MAX_NUMBER;
    reg_shift = 1 << (eint_number % EINT_GROUP_MAX_NUMBER);

    EINT_REGISTER->EINT_TOGGLE_DIS[reg_index] |= reg_shift;
    if(toggle)
    {
        EINT_REGISTER->EINT_TOGGLE[reg_index] |= reg_shift;
    }else
    {
        EINT_REGISTER->EINT_TOGGLE[reg_index] &= (~reg_shift);
    }
    return HAL_EINT_STATUS_OK;
}
#endif


#ifdef __cplusplus
}
#endif

#endif /* HAL_EINT_MODULE_ENABLED */

