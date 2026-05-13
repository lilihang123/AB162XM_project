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

#ifdef HAL_RAMBOZ_MODULE_ENABLED
#include "hal_ramboz.h"
#include "hal_nvic.h"
#include "hal_nvic_internal.h"
#include "air_chip.h"
#include "hal_gpt.h"
#include "hal_spm.h"
#include <zephyr/sys/printk.h>

// #define RAMBOZ_DEBUG_LOG

static volatile HW_RAMBZ_REGISTER_T *const ramboz_register = (HW_RAMBZ_REGISTER_T *)(RAMBOZ_BASE);
// void (*ramboz_callback)(uint8_t direction, int16_t number) = NULL;
void (*ramboz_callback)(uint8_t irq_type) = NULL;
static hal_ramboz_hw_status_t ramboz_status = RAMBOZ_STATUS_UNINITIALIZED;

static void hw_ramboz_Isr_zephyr(void)
{
    volatile uint32_t irq_status = ramboz_register->RAMBOZ_IRQ_STATE;
    if ((irq_status & RAMBOZ_IRQ_STATUS_Z_CNT_MASK))
    {
        if (ramboz_callback!=NULL)
        {
            ramboz_callback(HAL_RAMBOZ_IRQ_Z_CNT);
        }
        /*clear irq_notify */
        ramboz_register->RAMBOZ_IRQ_CLR_UNION.RAMBOZ_IRQ_CLR_CELLS.IRQ_NOTIFY_CLR = 0x2;
        ramboz_register->RAMBOZ_IRQ_CLR_UNION.RAMBOZ_IRQ_CLR = 0x200;
        ramboz_register->RAMBOZ_WKUP_CLR_UNION.RAMBOZ_WKUP_CLR_CELLS.WKUP_NOTIFY_CLR = 0x2;
        ramboz_register->RAMBOZ_WKUP_CLR_UNION.RAMBOZ_WKUP_CLR = 0x200;
    }
    else if(irq_status & RAMBOZ_IRQ_STATUS_RAMBO_CNT_MASK)
    {
        if (ramboz_callback!=NULL)
        {
            ramboz_callback(HAL_RAMBOZ_IRQ_RAMBO_CNT);
        }
        /*clear irq_notify */
        ramboz_register->RAMBOZ_IRQ_CLR_UNION.RAMBOZ_IRQ_CLR_CELLS.IRQ_NOTIFY_CLR = 0x1;
        ramboz_register->RAMBOZ_IRQ_CLR_UNION.RAMBOZ_IRQ_CLR = 0x100;
        ramboz_register->RAMBOZ_WKUP_CLR_UNION.RAMBOZ_WKUP_CLR_CELLS.WKUP_NOTIFY_CLR = 0x1;
        ramboz_register->RAMBOZ_WKUP_CLR_UNION.RAMBOZ_WKUP_CLR = 0x100;
    }else if(irq_status & RAMBOZ_IRQ_STATUS_DATA_READY_MASK)
    {
        if (ramboz_callback!=NULL)
        {
            ramboz_callback(HAL_RAMBOZ_IRQ_DATA_READY);
        }
        /*clear data readyirq_event and irq_notify */
        ramboz_register->RAMBOZ_IRQ_CLR_UNION.RAMBOZ_IRQ_CLR_CELLS.IRQ_NOTIFY_CLR = 0x4;
        ramboz_register->RAMBOZ_IRQ_CLR_UNION.RAMBOZ_IRQ_CLR = 0x400;
    }
    printk("*(volatile uint32_t *)(0x42102048)==%x\r\n",*(volatile uint32_t *)(0x42102048));
    printk("*(volatile uint32_t *)(0x4210204c)==%x\r\n",*(volatile uint32_t *)(0x4210204c));
}

static hal_ramboz_status_t hal_ramboz_init_para_check(hal_ramboz_config_t *ramboz_cfg)
{
    hal_ramboz_direction_t direction = ramboz_cfg->direction;
    if ((direction != HAL_RAMBOZ_DIRECTION_0) && (direction != HAL_RAMBOZ_DIRECTION_1))
    {
        return HAL_RAMBOZ_INVALID_PARAMETER;
    }
    hal_ramboz_mode_t mode = ramboz_cfg->mode;
    if ((mode != HAL_RAMBOZ_MODE_8CNT) && (mode != HAL_RAMBOZ_MODE_5CNT))
    {
        return HAL_RAMBOZ_INVALID_PARAMETER;
    }
    uint8_t filter_period = ramboz_cfg->filter_period;
    uint16_t fast_sample_period = ramboz_cfg->fast_sample_period;
    uint16_t low_sample_period = ramboz_cfg->slow_sample_period;
    uint16_t fast_roll_period = ramboz_cfg->fast_roll_period;

    if ((filter_period > FILTER_PERIOD_MAX) || (fast_sample_period > FAST_SAMPLE_PERIOD_MAX) || (low_sample_period > SLOW_SAMPLE_PERIOD_MAX) ||
        (fast_roll_period > FAST_ROLL_PERIOD_MAX))
    {
        return HAL_RAMBOZ_INVALID_PARAMETER;
    }
    return HAL_RAMBOZ_STATUS_OK;
}

static void ramboz_reg_adr_check()
{
#if 0
    printk("RAMBOZ_BASE==%p\r\n", (HW_RAMBZ_REGISTER_T *)(ramboz_register));
    printk("RAMBOZ_CFG_UNION==%p\r\n", &(ramboz_register->RAMBOZ_CFG_UNION));

    printk("FILTER_PERIOD==%p\r\n", &(ramboz_register->FILTER_PERIOD));
    printk("FAST_SAMPLE_PERIOD==%p\r\n", &(ramboz_register->FAST_SAMPLE_PERIOD));
    printk("SLOW_SAMPLE_PERIOD==%p\r\n", &(ramboz_register->SLOW_SAMPLE_PERIOD));
    printk("FAST_ROLL_PERIOD==%p\r\n", &(ramboz_register->FAST_ROLL_PERIOD));
    printk("SAMPLE_RATE_CONTROL_UNION==%p\r\n", &(ramboz_register->SAMPLE_RATE_CONTROL_UNION));
    printk("RAMBOZ_IRQ_MASK==%p\r\n", &(ramboz_register->RAMBOZ_IRQ_MASK));
    printk("RAMBOZ_IRQ_CLR_UNION==%p\r\n", &(ramboz_register->RAMBOZ_IRQ_CLR_UNION));
    printk("RAMBOZ_WKUP_MASK==%p\r\n", &(ramboz_register->RAMBOZ_WKUP_MASK));
    printk("RAMBOZ_WKUP_CLR_UNION==%p\r\n", &(ramboz_register->RAMBOZ_WKUP_CLR_UNION));
    printk("RAMBOZ_ENABLE==%p\r\n", &(ramboz_register->RAMBOZ_ENABLE));
    printk("RAMBOZ_CNT==%p\r\n", &(ramboz_register->RAMBOZ_CNT));

    printk("RAMBOZ_Z_CNT_UNION==%p\r\n", &(ramboz_register->RAMBOZ_Z_CNT_UNION));
    printk("RAMBOZ_IRQ_STATE==%p\r\n", &(ramboz_register->RAMBOZ_IRQ_STATE));
    printk("RAMBOZ_WKUP_STATE==%p\r\n", &(ramboz_register->RAMBOZ_WKUP_STATE));
    printk("RAMBOZ_DEBUG_MON_UNION==%p\r\n", &(ramboz_register->RAMBOZ_DEBUG_MON_UNION));

    printk("RAMBOZ_DEBUG_INFO_0_UNION==%p\r\n", &(ramboz_register->RAMBOZ_DEBUG_INFO_0_UNION));
    printk("RAMBOZ_DEBUG_INFO_1_UNION==%p\r\n", &(ramboz_register->RAMBOZ_DEBUG_INFO_1_UNION));

#endif
}

hal_ramboz_status_t hal_ramboz_init(hal_ramboz_config_t *ramboz_cfg)
{

    ramboz_reg_adr_check();  
    hal_nvic_status_t nvic_status;
    /*rambz status  check*/
    if (ramboz_status != RAMBOZ_STATUS_UNINITIALIZED)
    {
        return HAL_RAMBOZ_STATUS_ERROR;
    }
    /*para check*/
    if (hal_ramboz_init_para_check(ramboz_cfg) != HAL_RAMBOZ_STATUS_OK)
    {
        return HAL_RAMBOZ_INVALID_PARAMETER;
    }
#ifdef HAL_SLEEP_MANAGER_ENABLED
    spm_control_mtcmos(SPM_MTCMOS_RTCSYS,SPM_MTCMOS_PWR_ENABLE); 
#endif 
    /*config register*/
    ramboz_register->RAMBOZ_CFG_UNION.RAMBOZ_CFG_CELLS.RAMBOZ_DIRECTION = ramboz_cfg->direction;
    ramboz_register->RAMBOZ_CFG_UNION.RAMBOZ_CFG_CELLS.RAMBOZ_5CNT_MODE = ramboz_cfg->mode;
    ramboz_register->FILTER_PERIOD = ramboz_cfg->filter_period;
    ramboz_register->FAST_SAMPLE_PERIOD = ramboz_cfg->fast_sample_period;
    ramboz_register->SLOW_SAMPLE_PERIOD = ramboz_cfg->slow_sample_period;
    ramboz_register->FAST_ROLL_PERIOD = ramboz_cfg->fast_roll_period;
    /*fast sample mode running*/
    ramboz_register->SAMPLE_RATE_CONTROL_UNION.SAMPLE_RATE_CONTROL_CELLS.SAMPLE_RATE_CHANGE = 0x01;
    ramboz_register->SAMPLE_RATE_CONTROL_UNION.SAMPLE_RATE_CONTROL_CELLS.SW_FORCE_FAST_SAMPLE = 0x01;

    hal_ramboz_disable_irq(HAL_RAMBOZ_IRQ_Z_CNT);
    hal_ramboz_disable_irq(HAL_RAMBOZ_IRQ_RAMBO_CNT);
    hal_ramboz_disable_irq(HAL_RAMBOZ_IRQ_DATA_READY);

    // /*register calllback ISR*/
    nvic_status = hal_nvic_register_isr_handler(RAMBOZ_IRQn, (void *)hw_ramboz_Isr_zephyr);
    if (nvic_status != HAL_NVIC_STATUS_OK)
    {
        return HAL_RAMBOZ_STATUS_ERROR;
    }
    hal_nvic_enable_irq(RAMBOZ_IRQn);
    ramboz_status = RAMBOZ_STATUS_INITIALIZED;
    return HAL_RAMBOZ_STATUS_OK;
}

hal_ramboz_status_t hal_ramboz_enable_irq(hal_ramboz_irq_type_t irq_type)
{
    if (irq_type == HAL_RAMBOZ_IRQ_DATA_READY)
    {
        ramboz_register->RAMBOZ_CFG_UNION.RAMBOZ_CFG_CELLS.IRQ_ENABLE |= 0x4;
        ramboz_register->RAMBOZ_IRQ_MASK |= 0x04;
    }
    else if (irq_type == HAL_RAMBOZ_IRQ_Z_CNT)
    {
        ramboz_register->RAMBOZ_CFG_UNION.RAMBOZ_CFG_CELLS.IRQ_ENABLE |= 0x2;
        ramboz_register->RAMBOZ_IRQ_MASK |= 0x02;
    }
    else if (irq_type == HAL_RAMBOZ_IRQ_RAMBO_CNT)
    {
        ramboz_register->RAMBOZ_CFG_UNION.RAMBOZ_CFG_CELLS.IRQ_ENABLE |= 0x1;
        ramboz_register->RAMBOZ_IRQ_MASK |= 0x01;
    }
    else
    {
        return HAL_RAMBOZ_INVALID_PARAMETER;
    }
    return HAL_RAMBOZ_STATUS_OK;
}

hal_ramboz_status_t hal_ramboz_disable_irq(hal_ramboz_irq_type_t irq_type)
{
    if (irq_type == HAL_RAMBOZ_IRQ_DATA_READY)
    {
        ramboz_register->RAMBOZ_CFG_UNION.RAMBOZ_CFG_CELLS.IRQ_ENABLE &= (~0x4);
        ramboz_register->RAMBOZ_IRQ_MASK &= (~0x04);
    }
    else if (irq_type == HAL_RAMBOZ_IRQ_Z_CNT)
    {
        ramboz_register->RAMBOZ_CFG_UNION.RAMBOZ_CFG_CELLS.IRQ_ENABLE &= (~0x2);
        ramboz_register->RAMBOZ_IRQ_MASK &= (~0x02);
    }
    else if (irq_type == HAL_RAMBOZ_IRQ_RAMBO_CNT)
    {
        ramboz_register->RAMBOZ_CFG_UNION.RAMBOZ_CFG_CELLS.IRQ_ENABLE &= (~0x1);
        ramboz_register->RAMBOZ_IRQ_MASK &= (~0x01);
    }
    else
    {
        return HAL_RAMBOZ_INVALID_PARAMETER;
    }
    return HAL_RAMBOZ_STATUS_OK;
}

hal_ramboz_status_t hal_ramboz_enable(void)
{
    if (ramboz_status != RAMBOZ_STATUS_INITIALIZED)
    {
        return HAL_RAMBOZ_STATUS_ERROR;
    }
    ramboz_register->RAMBOZ_ENABLE = 0x01;
    ramboz_status = RAMBOZ_STATUS_RUNNING;
    return HAL_RAMBOZ_STATUS_OK;
}

hal_ramboz_status_t hal_ramboz_disable(void)
{
    if (ramboz_status != RAMBOZ_STATUS_RUNNING)
    {
        return HAL_RAMBOZ_STATUS_ERROR;
    }
    ramboz_register->RAMBOZ_ENABLE = 0x0;
    ramboz_register->RAMBOZ_Z_CNT_UNION.RAMBOZ_Z_CNT_CELLS.Z_CNT_LATCH_N_CLR = 0x01;
    ramboz_status = RAMBOZ_STATUS_INITIALIZED;
    return HAL_RAMBOZ_STATUS_OK;
}

hal_ramboz_status_t hal_ramboz_deinit(void)
{
    hal_ramboz_disable();
    ramboz_status = RAMBOZ_STATUS_UNINITIALIZED;
#ifdef HAL_SLEEP_MANAGER_ENABLED    
    spm_control_mtcmos(SPM_MTCMOS_RTCSYS, SPM_MTCMOS_PWR_DISABLE);
#endif    
    return HAL_RAMBOZ_STATUS_OK;
}

hal_ramboz_status_t hal_ramboz_register_callback(hal_ramboz_callback_t callback)
{
    if (callback == NULL)
    {
        /**/
        return HAL_RAMBOZ_INVALID_PARAMETER;
    }
    ramboz_callback = callback;
#ifdef RAMBOZ_DEBUG_LOG
    printk("hal_ramboz_register_callback\r\n");
#endif /*RAMBOZ_DEBUG_LOG*/
    return HAL_RAMBOZ_STATUS_OK;
}

static bool ramboz_available_data = false;
hal_ramboz_status_t hal_ramboz_set_latch_clear()
{
    // if(ramboz_available_data == false)
    // {
        ramboz_register->RAMBOZ_Z_CNT_UNION.RAMBOZ_Z_CNT_CELLS.Z_CNT_LATCH_N_CLR = 0x01;
        ramboz_available_data = true;
        return HAL_RAMBOZ_STATUS_OK;
    // }
    // return HAL_RAMBOZ_STATUS_ERROR;
}

hal_ramboz_status_t hal_ramboz_get_data(int16_t *data)
{
    // if(ramboz_available_data == false)
    // {
    //     return HAL_RAMBOZ_STATUS_ERROR;
    // }

    volatile int8_t fifo_data = ramboz_register->RAMBOZ_Z_CNT_UNION.RAMBOZ_Z_CNT_CELLS.Z_CNT;
    ramboz_available_data = false;
#ifdef RAMBOZ_DEBUG_LOG
    printk("fifo_data=%x\r\n", fifo_data);
#endif /*RAMBOZ_DEBUG_LOG*/

    *data = fifo_data;
    return HAL_RAMBOZ_STATUS_OK;
}

hal_ramboz_status_t hw_ramboz_data_getting_type_set(hal_ramboz_data_getting_type_t ramboz_data_getting_type)
{
    if (ramboz_data_getting_type == HAL_RAMBOZ_READ_DATA_BY_IRQ)
    {
        hal_ramboz_enable_irq(HAL_RAMBOZ_IRQ_DATA_READY);
    }
    else if (ramboz_data_getting_type == HAL_RAMBOZ_READ_DATA_BY_NEXT_CYCLE)
    {
        hal_ramboz_disable_irq(HAL_RAMBOZ_IRQ_DATA_READY);
    }
    else
    {
        return HAL_RAMBOZ_INVALID_PARAMETER;
    }
    return HAL_RAMBOZ_STATUS_OK;
}

hal_ramboz_status_t hw_ramboz_data_sample_mode_set(hal_ramboz_sample_mode_t ramboz_sample_mode)
{
    if (ramboz_sample_mode == HAL_RAMBOZ_FAST_SAMPLE)
    {
        ramboz_register->SAMPLE_RATE_CONTROL_UNION.SAMPLE_RATE_CONTROL_CELLS.SW_FORCE_FAST_SAMPLE = 0x01;
    }
    else if (ramboz_sample_mode == HAL_RAMBOZ_SLOW_SAMPLE)
    {
        ramboz_register->SAMPLE_RATE_CONTROL_UNION.SAMPLE_RATE_CONTROL_CELLS.SW_FORCE_SLOW_SAMPLE = 0x01;
    }
    else
    {
        return HAL_RAMBOZ_INVALID_PARAMETER;
    }
    return HAL_RAMBOZ_STATUS_OK;
}

hal_ramboz_status_t hal_ramboz_enable_wakeup_event(hal_ramboz_wakeup_event_type_t wakeup_event_type)
{
    if (wakeup_event_type == HAL_RAMBOZ_WAKEUP_EVENT_Z_CNT)
    {
        ramboz_register->RAMBOZ_CFG_UNION.RAMBOZ_CFG_CELLS.WKUP_ENABLE |= 0x2;
        ramboz_register->RAMBOZ_WKUP_MASK |= 0x02;
    }
    else if (wakeup_event_type == HAL_RAMBOZ_WAKEUP_EVENT_RAMBO_CNT)
    {
        ramboz_register->RAMBOZ_CFG_UNION.RAMBOZ_CFG_CELLS.WKUP_ENABLE |= 0x1;
        ramboz_register->RAMBOZ_WKUP_MASK |= 0x01;
    }
    else
    {
        return HAL_RAMBOZ_INVALID_PARAMETER;
    }
    return HAL_RAMBOZ_STATUS_OK;
}

hal_ramboz_status_t hal_ramboz_disable_wakeup_event(hal_ramboz_wakeup_event_type_t wakeup_event_type)
{
    if (wakeup_event_type == HAL_RAMBOZ_WAKEUP_EVENT_Z_CNT)
    {
        ramboz_register->RAMBOZ_CFG_UNION.RAMBOZ_CFG_CELLS.WKUP_ENABLE &= (~0x2);
        ramboz_register->RAMBOZ_WKUP_MASK &= (~0x02);
    }
    else if (wakeup_event_type == HAL_RAMBOZ_WAKEUP_EVENT_RAMBO_CNT)
    {
        ramboz_register->RAMBOZ_CFG_UNION.RAMBOZ_CFG_CELLS.WKUP_ENABLE &= (~0x1);
        ramboz_register->RAMBOZ_WKUP_MASK &= (~0x01);
    }
    else
    {
        return HAL_RAMBOZ_INVALID_PARAMETER;
    }
    return HAL_RAMBOZ_STATUS_OK;
}

#endif /* HAL_RAMBOZ_MODULE_ENABLED */
