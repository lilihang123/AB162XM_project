/*
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

#ifdef HAL_HW_KEYSCAN_MODULE_ENABLED
#include "hal_hw_keyscan.h"
#include "hal_nvic.h"
#include "hal_nvic_internal.h"
#include "air_chip.h"
#include "hal_gpt.h"
#include "hal_platform.h"
#include "hal_clock.h"
#include "hal_gpt.h"

#ifdef HAL_SLEEP_MANAGER_ENABLED
#include "hal_spm.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_internal.h"
#endif/*HAL_SLEEP_MANAGER_ENABLED*/

#include <zephyr/sys/printk.h>

/***************************************************/
/*Variables*/
/***************************************************/
// #define KEYSCAN_DEBUG_LOG
#define RELEASE_DEBOUNCE_MAX 0x3f
#define PRESS_DEBOUNCE_MAX 0x3f
#define ROW_NUM_MAX 8
#define COL_NUM_MAX 18
#define SFR_ROW_MAP_DEFAULT_VALUE 0X3f
#define SFR_COL_MAP_DEFAULT_VALUE 0X3f

#define SFR_RLS_DEB_TIME_DEFAULT_VALUE 0X03
#define SFR_PRS_DEB_TIME_DEFAULT_VALUE 0X01

static uint8_t total_key_num;
static uint8_t one_packet_valid_num;
static hal_keyscan_hwstatus_t hw_keyscan_status = HAL_KEYSCAN_HWSTATUS_UNINITIALIZED;
static const hal_clock_cg_id keycan_cg_blck = HAL_CLOCK_CG_KEY_SCAN_BCLK;
static const hal_clock_cg_id keycan_cg_2m = HAL_CLOCK_CG_KEY_SCAN_F2M;


bool is_ghost = false;

static volatile HW_KEYSCAN_REGISTER_T *const keyscan_register = (HW_KEYSCAN_REGISTER_T *)(HW_KEYSCAN_BASE);
void (*key_transaction)(uint32_t *keys, uint8_t one_packet_valid_num, uint8_t total_key_num, bool is_ghost_happen) = NULL;

static void hw_keyscan_Isr(void)
{
#ifdef KEYSCAN_DEBUG_LOG
    printk("hw_keyscan_Isr-in\r\n");
#endif
    while (!(keyscan_register->AFIFO_STATUS_UNION.AFIFO_STATUS_CELLS.AFIFO_EMPTY))
    {
        volatile uint8_t available_data_num = keyscan_register->AFIFO_STATUS_UNION.AFIFO_STATUS_CELLS.AFIFO_DNUM;
#ifdef KEYSCAN_DEBUG_LOG
        printk("available_data_num=%d\r\n", available_data_num);
        printk("one_packet_valid_num=%d\r\n", one_packet_valid_num);
#endif
        if (available_data_num >= one_packet_valid_num)
        {
            uint32_t key_data[5];
            int i;
            if (keyscan_register->GHOST_KEY == 0x01)
            {
                is_ghost = true;
            }
            else
            {
                is_ghost = false;
            }

            for (i = 0; i < one_packet_valid_num; i++)
            {
                key_data[i] = keyscan_register->AFIFO_DOUT;
            }

            if (key_transaction)
            {
                key_transaction(key_data, one_packet_valid_num, total_key_num, is_ghost);
            }
        }
        else
        {
            /*check if the fifo is full,full means keyscan stop to wait reading the data,last data is invalid*/
            volatile uint8_t scan_stop_flag = keyscan_register->AFIFO_STATUS_UNION.AFIFO_STATUS_CELLS.FIFO_STOP_FLAG;
            if (scan_stop_flag)
            {
                /*clear the invalid data in the fifo*/
                uint32_t key_fifo_invalid_data;
                int i;
                for (i = 0; i < available_data_num; i++)
                {
                    key_fifo_invalid_data = keyscan_register->AFIFO_DOUT;
                }
                break;
            }
            else
            {
                /*if afifo is not full, means the data is valid, but not finish updated*/
                break;
            }
        }
    }
#ifdef KEYSCAN_DEBUG_LOG
    printk("hw_keyscan_Isr-out\r\n");
    printk("\r\n");
#endif
    keyscan_register->SFR_IRQ_CLEAR = 0x01;
}
static hal_hw_keyscan_status_t hw_keyscan_debounce_is_valid(uint8_t press_debounce, uint8_t release_debounce)
{
    if (release_debounce > RELEASE_DEBOUNCE_MAX || press_debounce > PRESS_DEBOUNCE_MAX)
    {
        return HAL_HW_KEYSCAN_INVALID_PARAMETER;
    }
    else
    {
        return HAL_HW_KEYSCAN_STATUS_OK;
    }
}

static hal_hw_keyscan_status_t hw_keyscan_row_col_num_is_valid(uint8_t row_num, uint8_t col_num)
{
    if ((row_num > ROW_NUM_MAX) || (col_num > COL_NUM_MAX) || (row_num == 0) || (col_num == 0))
    {
        return HAL_HW_KEYSCAN_INVALID_PARAMETER;
    }
    else
    {
        return HAL_HW_KEYSCAN_STATUS_OK;
    }
}

static hal_hw_keyscan_status_t hw_keyscan_scan_rate_is_valid(hal_hw_keyscan_kb_type_t keyboard_type, hal_hw_keyscan_rate_t rate)
{
    if (((keyboard_type == HAL_HW_KEYSCAN_TYPE_OFFICE_KB) && (rate > HAL_HW_KEYSCAN_RATE_250RR)) || ((keyboard_type == HAL_HW_KEYSCAN_TYPE_GAMING_KB_MECH) && (rate == HAL_HW_KEYSCAN_RATE_100RR)) || ((keyboard_type == HAL_HW_KEYSCAN_TYPE_GAMING_KB_OPT) && (rate == HAL_HW_KEYSCAN_RATE_100RR)))
    {
        return HAL_HW_KEYSCAN_INVALID_PARAMETER;
    }
    else
    {
        return HAL_HW_KEYSCAN_STATUS_OK;
    }
}

static hal_hw_keyscan_status_t hw_keyscan_io_delay_is_valid(hal_hw_keyscan_kb_type_t keyboard_type, hal_hw_keyscan_rate_t rate, hal_hw_keyscan_io_switch_time_t swich_time)
{
    if (keyboard_type == HAL_HW_KEYSCAN_TYPE_OFFICE_KB)
    {
        if (((rate == HAL_HW_KEYSCAN_RATE_100RR) && (swich_time > HAL_HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_3T)) || ((rate == HAL_HW_KEYSCAN_RATE_125RR) && (swich_time > HAL_HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_6T)) || ((rate == HAL_HW_KEYSCAN_RATE_133RR) && (swich_time > HAL_HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_5T)) || ((rate == HAL_HW_KEYSCAN_RATE_250RR) && (swich_time > HAL_HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_6T)))
        {
            return HAL_HW_KEYSCAN_INVALID_PARAMETER;
        }
        else
        {
            return HAL_HW_KEYSCAN_STATUS_OK;
        }
    }
    else if (keyboard_type == HAL_HW_KEYSCAN_TYPE_GAMING_KB_MECH)
    {
        if (((rate == HAL_HW_KEYSCAN_RATE_133RR) && (swich_time > HAL_HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_4T)) || ((rate != HAL_HW_KEYSCAN_RATE_133RR) && (swich_time > HAL_HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_5T)))
        {
            return HAL_HW_KEYSCAN_INVALID_PARAMETER;
        }
        else
        {
            return HAL_HW_KEYSCAN_STATUS_OK;
        }
    }
    else if (keyboard_type == HAL_HW_KEYSCAN_TYPE_GAMING_KB_OPT)
    {
        if ((rate == HAL_HW_KEYSCAN_RATE_133RR) && (swich_time > HAL_HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_5T))
        {
            return HAL_HW_KEYSCAN_INVALID_PARAMETER;
        }else if ((rate == HAL_HW_KEYSCAN_RATE_8KRR) && (swich_time > HAL_HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_14T))
        {
            return HAL_HW_KEYSCAN_INVALID_PARAMETER;
        }else if(((rate != HAL_HW_KEYSCAN_RATE_133RR)&&(rate != HAL_HW_KEYSCAN_RATE_8KRR)) && (swich_time > HAL_HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_6T))
        {
            return HAL_HW_KEYSCAN_INVALID_PARAMETER;
        }
        else
        {
            return HAL_HW_KEYSCAN_STATUS_OK;
        }
    }
    else
    {
        return HAL_HW_KEYSCAN_INVALID_PARAMETER;
    }
}

static hal_hw_keyscan_status_t hal_hw_keyscan_clock_enable()
{
    if (hal_clock_is_enabled(keycan_cg_blck) != true) {
        if (HAL_CLOCK_STATUS_OK != hal_clock_enable(keycan_cg_blck)) {
            printk("keycan_cg_blck enable failed!\r\n");
            return HAL_HW_KEYSCAN_STATUS_ERROR;
        }
    }
    if (hal_clock_is_enabled(keycan_cg_2m) != true) {
        if (HAL_CLOCK_STATUS_OK != hal_clock_enable(keycan_cg_2m)) {
            printk("keycan_cg_2m enable failed!\r\n");
            return HAL_HW_KEYSCAN_STATUS_ERROR;
        }
    }

    return HAL_HW_KEYSCAN_STATUS_OK;
}

static hal_hw_keyscan_status_t hal_hw_keyscan_clock_disable()
{
    if (hal_clock_is_enabled(keycan_cg_blck) == true) {
        if (HAL_CLOCK_STATUS_OK != hal_clock_disable(keycan_cg_blck)) {
            printk("keycan_cg_blck disable failed!\r\n");
            return HAL_HW_KEYSCAN_STATUS_ERROR;
        }
    }
    if (hal_clock_is_enabled(keycan_cg_2m) == true) {
        if (HAL_CLOCK_STATUS_OK != hal_clock_enable(keycan_cg_2m)) {
            printk("keycan_cg_2m disable failed!\r\n");
            return HAL_HW_KEYSCAN_STATUS_ERROR;
        }
    }

    return HAL_HW_KEYSCAN_STATUS_OK;
}


hal_hw_keyscan_status_t hal_hw_keyscan_init(hal_hw_keyscan_config_t *keyscan_config)
{
    if (hw_keyscan_status != HAL_KEYSCAN_HWSTATUS_UNINITIALIZED)
    {
        return HAL_HW_KEYSCAN_STATUS_ERROR;
    }

    hal_nvic_status_t nvic_status;
    uint8_t row_num = keyscan_config->row_num;
    uint8_t col_num = keyscan_config->col_num;


    hal_hw_keyscan_mode_t mode = keyscan_config->mode;
    if(keyscan_config->mode == HAL_HW_KEYSCAN_SW_TRIGGER)
    {
        mode = HAL_HW_KEYSCAN_GAMING_KB_ALIGN_BT;
    }
    hal_hw_keyscan_io_switch_time_t swich_time = keyscan_config->swich_time;
    hal_hw_keyscan_rate_t rate = keyscan_config->rate;
    uint8_t release_debounce = keyscan_config->release_debounce;
    uint8_t press_debounce = keyscan_config->press_debounce;
    bool debounce_en = keyscan_config->debounce_en;
    hal_hw_keyscan_kb_type_t keyboard_type = keyscan_config->keyboard_type;
    hal_hw_keyscan_io_setting_t col_in_setting = keyscan_config->col_in_setting;

    if ((hw_keyscan_debounce_is_valid(press_debounce, release_debounce) != HAL_HW_KEYSCAN_STATUS_OK) || (hw_keyscan_row_col_num_is_valid(row_num, col_num) != HAL_HW_KEYSCAN_STATUS_OK) || (hw_keyscan_scan_rate_is_valid(keyboard_type, rate) != HAL_HW_KEYSCAN_STATUS_OK) || (hw_keyscan_io_delay_is_valid(keyboard_type, rate, swich_time) != HAL_HW_KEYSCAN_STATUS_OK))
    {
        return HAL_HW_KEYSCAN_INVALID_PARAMETER;
    }

    if (HAL_HW_KEYSCAN_STATUS_OK != hal_hw_keyscan_clock_enable()) {
        return HAL_HW_KEYSCAN_STATUS_ERROR;
    }

    keyscan_register->MATRIX_SIZE_UNION.MATRIX_SIZE_CELLS.SFR_ROW_NUM = (row_num - 1);
    keyscan_register->MATRIX_SIZE_UNION.MATRIX_SIZE_CELLS.SFR_COL_NUM = (col_num - 1);
    keyscan_register->SFR_SCAN_MODE = mode;
    keyscan_register->SFR_IO_SW_TIME_SEL = swich_time;
    keyscan_register->SFR_KEYSCAN_RATE_DLY_SEL = rate;
    keyscan_register->SFR_RLS_DEB_TIME = release_debounce;
    keyscan_register->SFR_PRS_DEB_TIME = press_debounce;
    keyscan_register->SFR_DEB_EN = debounce_en;
    keyscan_register->SFR_KB_TYPE = keyboard_type;
    keyscan_register->SFR_COL_IN_SETTING = col_in_setting;

    if(keyscan_config->mode == HAL_HW_KEYSCAN_SW_TRIGGER)
    {
        /*sw trigger mode*/
        *(volatile uint32_t *)(0x42020038) = (0x1);//keyscan en sw trigger mode
    }

    total_key_num = (row_num * col_num);
    if((total_key_num % 32) == 0)
    {
        one_packet_valid_num = (total_key_num / 32);
    }else
    {
        one_packet_valid_num = (total_key_num / 32) + 1;
    }
    /* unused field must be 0x3f, otherwise there would be extra current*/
    int i;
    for (i = row_num; i < 8; i++)
    {
        keyscan_register->SFR_ROW_MAP[i] = SFR_ROW_MAP_DEFAULT_VALUE;
    }

    for (i = col_num; i < 18; i++)
    {
        keyscan_register->SFR_COL_MAP[i] = SFR_COL_MAP_DEFAULT_VALUE;
    }
    // Set Row IO
    for (i = 0; i < row_num; i++)
    {
        keyscan_register->SFR_ROW_MAP[i] = keyscan_config->row[i];
    }
    // Set Column IO
    for (i = 0; i < col_num; i++)
    {
        keyscan_register->SFR_COL_MAP[i] = keyscan_config->col[i];
    }

    /*register calllback ISR*/
    nvic_status = hal_nvic_register_isr_handler(KEYSCAN_IRQn, (void *)hw_keyscan_Isr);
    if (nvic_status != HAL_NVIC_STATUS_OK)
    {
#ifdef KEYSCAN_DEBUG_LOG
        printk("register hw keyscan isr failed\r\n");
#endif
        return HAL_HW_KEYSCAN_STATUS_ERROR;
    }
    hal_nvic_enable_irq(KEYSCAN_IRQn);
    keyscan_register->SFR_KEYSCAN_IO_EN = SFR_KEYSCAN_IO_ENBLE;
    hw_keyscan_status = HAL_KEYSCAN_HWSTATUS_INITIALIZED;

#ifdef HAL_SLEEP_MANAGER_ENABLED
    ao_backup_format_table_t keyscan_backup_reg;
    keyscan_backup_reg.module_base_addr = 0x421e0000;
    keyscan_backup_reg.module_end_addr = 0x421e008c;
    keyscan_backup_reg.module_backup_enable = 0x1;
    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_KEY_SCAN, &keyscan_backup_reg); 
#endif /*HAL_SLEEP_MANAGER_ENABLED*/

#ifdef KEYSCAN_DEBUG_LOG
    printk("hw keyscan init success\r\n");
#endif
    return HAL_HW_KEYSCAN_STATUS_OK;
}

hal_hw_keyscan_status_t hal_hw_keyscan_deinit(void)
{
    if (hw_keyscan_status != HAL_KEYSCAN_HWSTATUS_INITIALIZED)
    {
        return HAL_HW_KEYSCAN_STATUS_ERROR;
    }
    // Set Row IO

    if (HAL_HW_KEYSCAN_STATUS_OK != hal_hw_keyscan_clock_disable()) {
        return HAL_HW_KEYSCAN_STATUS_ERROR;
    }

    int i;
    keyscan_register->SFR_KEYSCAN_EN = SFR_KEYSCAN_DISENABLE;
    keyscan_register->SFR_KEYSCAN_IO_EN = SFR_KEYSCAN_IO_DISENABLE;
    for (i = 0; i < 8; i++)
    {
        keyscan_register->SFR_ROW_MAP[i] = SFR_ROW_MAP_DEFAULT_VALUE;
    }
    // Set Column IO
    for (i = 0; i < 18; i++)
    {
        keyscan_register->SFR_COL_MAP[i] = SFR_COL_MAP_DEFAULT_VALUE;
    }
    keyscan_register->SFR_RLS_DEB_TIME = SFR_RLS_DEB_TIME_DEFAULT_VALUE;
    keyscan_register->SFR_PRS_DEB_TIME = SFR_PRS_DEB_TIME_DEFAULT_VALUE;
    total_key_num = 0;
    one_packet_valid_num = 0;
    hw_keyscan_status = HAL_KEYSCAN_HWSTATUS_UNINITIALIZED;
    return HAL_HW_KEYSCAN_STATUS_OK;
}

hal_hw_keyscan_status_t hal_hw_keyscan_enable(void)
{
    if (hw_keyscan_status != HAL_KEYSCAN_HWSTATUS_INITIALIZED)
    {
        return HAL_HW_KEYSCAN_STATUS_ERROR;
    }
    keyscan_register->SFR_KEYSCAN_EN = SFR_KEYSCAN_ENBLE;
    hw_keyscan_status = HAL_KEYSCAN_HWSTATUS_RUNGING;
#ifdef KEYSCAN_DEBUG_LOG
    printk("hal_hw_keyscan_enable success\r\n");
#endif
    hal_gpt_delay_us(5);//for sw trigger hw limitation
    return HAL_HW_KEYSCAN_STATUS_OK;
}

hal_hw_keyscan_status_t hal_hw_keyscan_disable(void)
{
    if (hw_keyscan_status != HAL_KEYSCAN_HWSTATUS_RUNGING)
    {
        return HAL_HW_KEYSCAN_STATUS_ERROR;
    }
    keyscan_register->SFR_KEYSCAN_EN = SFR_KEYSCAN_DISENABLE;
    hw_keyscan_status = HAL_KEYSCAN_HWSTATUS_INITIALIZED;
#ifdef KEYSCAN_DEBUG_LOG
    printk("hal_hw_keyscan_disable success\r\n");
#endif
    return HAL_HW_KEYSCAN_STATUS_OK;
}

hal_hw_keyscan_status_t hal_hw_keyscan_register_callback(hal_hw_keyscan_callback_t callback)
{
    if (callback == NULL)
    {
        return HAL_HW_KEYSCAN_INVALID_PARAMETER;
    }

    key_transaction = callback;
#ifdef KEYSCAN_DEBUG_LOG
    printk("hal_hw_keyscan_register_callback success\r\n");
#endif
    return HAL_HW_KEYSCAN_STATUS_OK;
}

void hal_hw_keyscan_sw_trigger(void)
{
    *(volatile uint32_t *)(0x4202003c) = (0x1);//sw trigger scan once
}

void hal_hw_keyscan_align_bt_trigger_set_enable(bool bt_trigger_enable)
{
    if(bt_trigger_enable)
    {
        /*bt trigger mode enable*/
        *(volatile uint32_t *)(0x42020038) = (0x0);
    }
    else{
        /*bt trigger mode disable*/
        *(volatile uint32_t *)(0x42020038) = (0x1);//change to sw trigger mode
    }
}
#endif /* HAL_HW_KEYSCAN_MODULE_ENABLED */
