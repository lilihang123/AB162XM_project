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

#ifdef HAL_QDEC_MODULE_ENABLED
#include "hal_qdec.h"
#include "hal_nvic.h"
// #include "hal_nvic_internal.h"
#include "air_chip.h"
#include "hal_gpt.h"
#include "hal_gpio.h"
#include <string.h>
// #include <zephyr/sys/printk.h>

#define QDEC_RISCV_IRQ_NUM 11
static volatile HW_QDEC_REGISTER_T *const qdec_register = (HW_QDEC_REGISTER_T *)(QDEC_BASE);
static volatile hal_qdec_hw_status_t qdec_status = QDEC_STATUS_UNINITIALIZED;
static volatile hal_qdec_mode_t qdec_mode = HAL_QDEC_ZSUM_MODE;
static hal_qdec_config_t g_qdec_cfg;
// static volatile int g_first_offset;
static bool g_first_data_flag = false;
static volatile bool qdec_available_data = false;
hal_qdec_mode_status_t g_qdec_mode_status;

void (*qdec_callback)(uint8_t irq_type) = NULL;

static hal_qdec_irq_type_t hw_qdec_irq_type_query(void)
{
  volatile uint32_t irq_status = qdec_register->QDEC_IRQ_STATUS_UNION.QDEC_IRQ_STATUS;
  if (irq_status & QDEC_IRQ_Z_SUM_MASK)
  {
    return QDEC_IRQ_Z_SUM;
  }
  else if (irq_status & QDEC_IRQ_Z_CNT_MASK)
  {
    return QDEC_IRQ_Z_CNT;
  }
  else
  {
    return QDEC_IRQ_DATA_READY;
  }
}

static void hw_qdec_Isr_zephyr(void)
{
  hal_qdec_irq_type_t irq_type = hw_qdec_irq_type_query();
  if (irq_type & QDEC_IRQ_Z_CNT)
  {
    if (qdec_callback != NULL)
    {
      qdec_callback(QDEC_IRQ_Z_CNT);
    }
    /*clear irq_notify */
    qdec_register->QDEC_IRQ_LCR_UNION.QDEC_IRQ_LCR_CELLS.IRQ_CLR_Z_THR_NOTIFY = 0x2;
    qdec_register->QDEC_IRQ_LCR_UNION.QDEC_IRQ_LCR_CELLS.IRQ_CLR_Z_THR_EVENT = 0x4;
    qdec_register->QDEC_SEL_GROUP_UNION.QDEC_SEL_GROUP_CELLS.SEL_GROUP = HAL_QDEC_SELECT_GROUP_A;
    g_qdec_mode_status = HAL_QDEC_LED_ACTIVE_MDOE;
  }
  else if ((irq_type & QDEC_IRQ_Z_SUM))
  {
    if (qdec_callback != NULL)
    {
      qdec_callback(QDEC_IRQ_Z_SUM);
    }
    /*clear irq_notify */
    qdec_register->QDEC_IRQ_LCR_UNION.QDEC_IRQ_LCR_CELLS.IRQ_CLR_Z_THR_NOTIFY = 0x1;
    qdec_register->QDEC_IRQ_LCR_UNION.QDEC_IRQ_LCR_CELLS.IRQ_CLR_Z_THR_EVENT = 0x1;
    qdec_register->QDEC_SEL_GROUP_UNION.QDEC_SEL_GROUP_CELLS.SEL_GROUP = HAL_QDEC_SELECT_GROUP_A;
    g_qdec_mode_status = HAL_QDEC_LED_ACTIVE_MDOE;
  }
  else if (irq_type & QDEC_IRQ_DATA_READY)
  {
    if (qdec_callback != NULL)
    {
      qdec_callback(QDEC_IRQ_DATA_READY);
    }
    /*clear data readyirq_event and irq_notify */
    qdec_register->QDEC_IRQ_LCR_UNION.QDEC_IRQ_LCR_CELLS.IRQ_CLR_DATA_RDY = 0x01;
  }
}

static hal_qdec_status_t qdec_group_config_para_check(hal_qdec_group_config_t qdec_group_cfg)
{
  uint16_t smp_period = qdec_group_cfg.smp_period;
  uint8_t led_period = qdec_group_cfg.led_period;
  uint8_t dbc_count = qdec_group_cfg.dbc_count;
  if ((smp_period > SAMPLE_PERIOD_MAX) || (led_period > LED_PERIOD_MAX) || (led_period > smp_period) ||
      (dbc_count > DBC_COUNT_MAX) || (dbc_count == 1))
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }
  return HAL_QDEC_STATUS_OK;
}

static hal_qdec_status_t hw_qdec_init_config_para_check(hal_qdec_config_t *qdec_cfg)
{
  /*check z sum throughhold*/
  uint16_t z_sum_thr = qdec_cfg->z_sum_thr;
  if (z_sum_thr > Z_SUM_THR_MAX)
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }

  /*check A/B group reg setting*/
  hal_qdec_status_t ret;
  hal_qdec_group_config_t group_a_cfg = qdec_cfg->group_a_cfg;
  ret = qdec_group_config_para_check(group_a_cfg);
  if (ret != HAL_QDEC_STATUS_OK)
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }

  hal_qdec_group_config_t group_b_cfg = qdec_cfg->group_b_cfg;
  ret = qdec_group_config_para_check(group_b_cfg);
  if (ret != HAL_QDEC_STATUS_OK)
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }

  /*check qdec pin setting*/
  uint8_t pina_pin = qdec_cfg->pina_pin;
  uint8_t pinb_pin = qdec_cfg->pinb_pin;
  uint8_t led_pin = qdec_cfg->led_pin;
  if ((pina_pin > HAL_GPIO_MAX) || (pinb_pin > HAL_GPIO_MAX) || (led_pin > HAL_GPIO_MAX))
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }

  /*check led ctrl setting*/
  if ((qdec_cfg->led_force_off > HAL_QDEC_LED_FORCE_OFF) || (qdec_cfg->led_active_output > HAL_QDEC_LED_HIGH_ACTIVE))
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }

  /*record para cfg*/
  g_qdec_cfg.pina_pin = pina_pin;
  g_qdec_cfg.pinb_pin = pinb_pin;
  g_qdec_cfg.led_pin = led_pin;
  g_qdec_cfg.led_force_off = qdec_cfg->led_force_off;
  g_qdec_cfg.led_active_output = qdec_cfg->led_active_output;
  g_qdec_cfg.z_sum_thr = z_sum_thr;
  g_qdec_cfg.group_a_cfg = group_a_cfg;
  g_qdec_cfg.group_b_cfg = group_b_cfg;
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_init(hal_qdec_config_t *qdec_cfg)
{

  // if (qdec_status != QDEC_STATUS_UNINITIALIZED)
  // {
  //   return HAL_QDEC_STATUS_ERROR;
  // }

  if (hw_qdec_init_config_para_check(qdec_cfg) != HAL_QDEC_STATUS_OK)
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }
  /*reset qdec register*/
  qdec_register->QDEC_CON_UNION.QDEC_CON_CELLS.SW_RSTB = 0x00;
  /*config register*/
  qdec_register->QDEC_LED_CON_UNION.QDEC_LED_CON_CELLS.LED_FORCE_OFF = g_qdec_cfg.led_force_off;
  qdec_register->QDEC_LED_CON_UNION.QDEC_LED_CON_CELLS.LED_POL = g_qdec_cfg.led_active_output;
  qdec_register->QDEC_SAMPLE_THR_UNION.QDEC_SAMPLE_THR_CELLS.Z_SUM_THR = g_qdec_cfg.z_sum_thr;
  qdec_register->QDEC_SAMPLE_CON_A_UNION.QDEC_SAMPLE_CON_A_CELLS.SMP_PERIOD_A = g_qdec_cfg.group_a_cfg.smp_period;
  qdec_register->QDEC_SAMPLE_CON_A_UNION.QDEC_SAMPLE_CON_A_CELLS.LED_PERIOD_A = g_qdec_cfg.group_a_cfg.led_period;
  qdec_register->QDEC_SAMPLE_CON_A_UNION.QDEC_SAMPLE_CON_A_CELLS.DBC_COUNT_A = g_qdec_cfg.group_a_cfg.dbc_count;
  qdec_register->QDEC_SAMPLE_CON_B_UNION.QDEC_SAMPLE_CON_B_CELLS.SMP_PERIOD_B = g_qdec_cfg.group_b_cfg.smp_period;
  qdec_register->QDEC_SAMPLE_CON_B_UNION.QDEC_SAMPLE_CON_B_CELLS.LED_PERIOD_B = g_qdec_cfg.group_b_cfg.led_period;
  qdec_register->QDEC_SAMPLE_CON_B_UNION.QDEC_SAMPLE_CON_B_CELLS.DBC_COUNT_B = g_qdec_cfg.group_b_cfg.dbc_count;

  /*enable HW_SEL_EN, detec z ,hw auto change to setting group*/
  qdec_register->QDEC_SEL_GROUP_UNION.QDEC_SEL_GROUP_CELLS.HW_SEL_GROUP = HAL_QDEC_SELECT_GROUP_A;
  /*select group*/
  qdec_register->QDEC_SEL_GROUP_UNION.QDEC_SEL_GROUP_CELLS.SEL_GROUP = HAL_QDEC_SELECT_GROUP_A;
  /*push qdec cfg to qdec hw internal reg*/
  qdec_register->QDEC_CON_UNION.QDEC_CON_CELLS.SW_RELOAD = 0x01;

  /*register calllback ISR*/
  hal_nvic_register_isr_handler(QDEC_RISCV_IRQ_NUM, (void *)hw_qdec_Isr_zephyr);
  // if (nvic_status != HAL_NVIC_STATUS_OK)
  // {
  //   return HAL_QDEC_STATUS_ERROR;
  // }
  hal_nvic_enable_irq(QDEC_RISCV_IRQ_NUM);
  qdec_status = QDEC_STATUS_INITIALIZED;
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_deinit(void)
{
  // if (qdec_status != QDEC_STATUS_INITIALIZED)
  // {
  //   return HAL_QDEC_STATUS_ERROR;
  // }
  memset(&g_qdec_cfg, 0, sizeof(g_qdec_cfg));
  // g_first_offset = 0;
  g_first_data_flag = false;
  qdec_register->QDEC_CON_UNION.QDEC_CON_CELLS.SW_RSTB = 0x00;
  qdec_status = QDEC_STATUS_UNINITIALIZED;
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_enable(void)
{
  // if (qdec_status != QDEC_STATUS_INITIALIZED)
  // {
  //   return HAL_QDEC_STATUS_ERROR;
  // }

  /*hw deault pina/pinb is low, detect pina/pinb input value, aviod first wrong data*/
  // hal_gpio_data_t qdec_pina_status;
  // hal_gpio_data_t qdec_pinb_status;
  // hal_gpio_status_t ret;
  // ret = hal_gpio_get_input(g_qdec_cfg.pina_pin, &qdec_pina_status);
  // if (ret != HAL_GPIO_STATUS_OK)
  // {
  //   return HAL_QDEC_STATUS_ERROR;
  // }
  // ret = hal_gpio_get_input(g_qdec_cfg.pina_pin, &qdec_pinb_status);
  // if (ret != HAL_GPIO_STATUS_OK)
  // {
  //   return HAL_QDEC_STATUS_ERROR;
  // }

  // if ((qdec_pina_status = HAL_GPIO_DATA_LOW) && (qdec_pinb_status = HAL_GPIO_DATA_HIGH))
  // {
  //   g_first_offset = -1;
  // }
  // if ((qdec_pina_status = HAL_GPIO_DATA_HIGH) && (qdec_pinb_status = HAL_GPIO_DATA_LOW))
  // {
  //   g_first_offset = 1;
  // }
  g_first_data_flag = true;
  qdec_register->QDEC_CON_UNION.QDEC_CON_CELLS.QDEC_ENABLE = 0x01;
  qdec_status = QDEC_STATUS_RUNNING;
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_disable(void)
{
  // if (qdec_status != QDEC_STATUS_RUNNING)
  // {
  //   return HAL_QDEC_STATUS_ERROR;
  // }

  qdec_register->QDEC_CON_UNION.QDEC_CON_CELLS.QDEC_ENABLE = 0x0;
  // g_first_offset = 0;
  g_first_data_flag = false;
  qdec_status = QDEC_STATUS_INITIALIZED;
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_register_callback(hal_qdec_callback_t callback)
{
  if (callback == NULL)
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }

  qdec_callback = callback;
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_zcnt_mode_set(hal_qdec_z_div_setting_t z_div, uint16_t z_cnt_thr)
{
  // if (qdec_status != QDEC_STATUS_INITIALIZED)
  // {
  //   return HAL_QDEC_STATUS_ERROR;
  // }

  if (z_cnt_thr > Z_CNT_THR_MAX)
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }
  qdec_register->QDEC_SAMPLE_THR_UNION.QDEC_SAMPLE_THR_CELLS.Z_COUNT_THR = z_cnt_thr;
  qdec_register->QDEC_SAMPLE_THR_UNION.QDEC_SAMPLE_THR_CELLS.Z_DIV = z_div;
  qdec_mode = HAL_QDEC_ZCNT_MODE;
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_set_latch_clear(void)
{
  // if (qdec_status == QDEC_STATUS_RUNNING)
  // {
    if (qdec_available_data == false)
    {
      qdec_register->QDEC_LATCH_N_CLR_UNION.QDEC_LATCH_N_CLR_CELLS.LATCH_N_CLR = 0x01;
      qdec_available_data = true;
      return HAL_QDEC_STATUS_OK;
    }
  // }
  return HAL_QDEC_STATUS_ERROR;
}

static int16_t dat_Sum = 0;
static void qdec_data_handler(int16_t new_data, int16_t *output_data)
{
  dat_Sum += new_data;
  if ((dat_Sum & 0x1) == 0)
  {
    *output_data =  (dat_Sum>>1);
    dat_Sum = 0;
    return;
  }
  return ;
}

hal_qdec_status_t hal_qdec_get_data(int16_t *data)
{
  int16_t temp_data;
  if (qdec_available_data == false)
  {
    return HAL_QDEC_STATUS_ERROR;
  }

  if (qdec_mode == HAL_QDEC_ZSUM_MODE)
  {
    volatile uint16_t fifo_data = qdec_register->QDEC_Z_INFO_UNION.QDEC_Z_INFO_CELLS.Z_SUM;
    qdec_available_data = false;
    if (g_first_data_flag)
    {
      fifo_data = 0;
      g_first_data_flag = false;
    }

    if (0x200 & fifo_data)
    {
      temp_data = (int16_t)(fifo_data | 0xFC00);
    }
    else
    {
      temp_data = (int16_t)(fifo_data & 0x3FF);
    }
  }
  else
  {
    volatile uint16_t fifo_data = qdec_register->QDEC_Z_INFO_UNION.QDEC_Z_INFO_CELLS.Z_CNT;
    qdec_available_data = false;
    if (g_first_data_flag)
    {
      fifo_data = 0;
      g_first_data_flag = false;
    }
    if (0x100 & fifo_data)
    {
      temp_data = (int16_t)(fifo_data | 0xFC00);
    }
    else
    {
      temp_data = (int16_t)(fifo_data & 0x3FF);
    }
  }
  qdec_data_handler(temp_data,data);
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_enable_hw_sel(hal_qdec_sel_group_setting_t group)
{
  if(group > HAL_QDEC_SELECT_GROUP_B)
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }
  /*enable HW_SEL_EN, detec z ,hw auto change to setting group*/
  qdec_register->QDEC_SEL_GROUP_UNION.QDEC_SEL_GROUP_CELLS.HW_SEL_GROUP = group;
  qdec_register->QDEC_SEL_GROUP_UNION.QDEC_SEL_GROUP_CELLS.HW_SEL_EN = 0x1;
  /*push qdec cfg to qdec hw internal reg*/
  qdec_register->QDEC_CON_UNION.QDEC_CON_CELLS.SW_RELOAD = 0x01;
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_disable_hw_sel(void)
{
  qdec_register->QDEC_SEL_GROUP_UNION.QDEC_SEL_GROUP_CELLS.HW_SEL_EN = 0x0;
  /*push qdec cfg to qdec hw internal reg*/
  qdec_register->QDEC_CON_UNION.QDEC_CON_CELLS.SW_RELOAD = 0x01;
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_sw_sel_group(hal_qdec_sel_group_setting_t group)
{
  if(group > HAL_QDEC_SELECT_GROUP_B)
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }
  qdec_register->QDEC_SEL_GROUP_UNION.QDEC_SEL_GROUP_CELLS.SEL_GROUP = group;
  /*push qdec cfg to qdec hw internal reg*/
  qdec_register->QDEC_CON_UNION.QDEC_CON_CELLS.SW_RELOAD = 0x01;
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_select_to_group_a(void)
{
  hal_qdec_status_t ret;
  ret = hal_qdec_disable_hw_sel();
  if (ret != HAL_QDEC_STATUS_OK)
  {
    return HAL_QDEC_STATUS_ERROR;
  }

  ret = hal_qdec_sw_sel_group(HAL_QDEC_SELECT_GROUP_A);
  if (ret != HAL_QDEC_STATUS_OK)
  {
    return HAL_QDEC_STATUS_ERROR;
  }

  if (qdec_mode == HAL_QDEC_ZSUM_MODE)
  {
    qdec_register->QDEC_IRQ_ENABLE_UNION.QDEC_IRQ_ENABLE_CELLS.IRQ_ENABLE_Z_SUM = 0x0;
    qdec_register->QDEC_WKUP_ENABLE_UNION.QDEC_WKUP_ENABLE_CELLS.WKUP_ENABLE_Z_SUM = 0x0;
  }
  else
  {
    qdec_register->QDEC_IRQ_ENABLE_UNION.QDEC_IRQ_ENABLE_CELLS.IRQ_ENABLE_Z_CNT = 0x0;
    qdec_register->QDEC_WKUP_ENABLE_UNION.QDEC_WKUP_ENABLE_CELLS.WKUP_ENABLE_Z_CNT = 0x0;
  }
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_select_to_group_b(void)
{
  hal_qdec_status_t ret;
  ret = hal_qdec_enable_hw_sel(HAL_QDEC_SELECT_GROUP_A);
  if (ret != HAL_QDEC_STATUS_OK)
  {
    return HAL_QDEC_STATUS_ERROR;
  }

  ret = hal_qdec_sw_sel_group(HAL_QDEC_SELECT_GROUP_B);
  if (ret != HAL_QDEC_STATUS_OK)
  {
    return HAL_QDEC_STATUS_ERROR;
  }

  if (qdec_mode == HAL_QDEC_ZSUM_MODE)
  {
    qdec_register->QDEC_IRQ_ENABLE_UNION.QDEC_IRQ_ENABLE_CELLS.IRQ_ENABLE_Z_SUM = 0x01;
    qdec_register->QDEC_WKUP_ENABLE_UNION.QDEC_WKUP_ENABLE_CELLS.WKUP_ENABLE_Z_SUM = 0x1;
  }
  else
  {
    qdec_register->QDEC_IRQ_ENABLE_UNION.QDEC_IRQ_ENABLE_CELLS.IRQ_ENABLE_Z_CNT = 0x1;
    qdec_register->QDEC_WKUP_ENABLE_UNION.QDEC_WKUP_ENABLE_CELLS.WKUP_ENABLE_Z_CNT = 0x1;
  }
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_select_to_idle_status(void)
{
  // if (qdec_status != QDEC_STATUS_RUNNING)
  // {
  //   return HAL_QDEC_STATUS_ERROR;
  // }
  hal_qdec_status_t ret;
  ret = hal_qdec_select_to_group_b();
  if (ret != HAL_QDEC_STATUS_OK)
  {
    return HAL_QDEC_STATUS_ERROR;
  }
  g_qdec_mode_status = HAL_QDEC_LED_IDLE_MDOE;
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_select_to_active_status(void)
{
  // if (qdec_status != QDEC_STATUS_RUNNING)
  // {
  //   return HAL_QDEC_STATUS_ERROR;
  // }

  hal_qdec_status_t ret;
  ret = hal_qdec_select_to_group_a();
  if (ret != HAL_QDEC_STATUS_OK)
  {
    return HAL_QDEC_STATUS_ERROR;
  }
  g_qdec_mode_status = HAL_QDEC_LED_ACTIVE_MDOE;
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_enable_irq(hal_qdec_irq_type_t irq_type)
{
  if (irq_type == QDEC_IRQ_Z_SUM)
  {
    qdec_register->QDEC_IRQ_ENABLE_UNION.QDEC_IRQ_ENABLE_CELLS.IRQ_ENABLE_Z_SUM = 0x01;
    qdec_register->QDEC_WKUP_ENABLE_UNION.QDEC_WKUP_ENABLE_CELLS.WKUP_ENABLE_Z_SUM = 0x1;
  }
  else if (irq_type == QDEC_IRQ_Z_CNT)
  {
    qdec_register->QDEC_IRQ_ENABLE_UNION.QDEC_IRQ_ENABLE_CELLS.IRQ_ENABLE_Z_CNT = 0x1;
    qdec_register->QDEC_WKUP_ENABLE_UNION.QDEC_WKUP_ENABLE_CELLS.WKUP_ENABLE_Z_CNT = 0x1;
  }
  else if (irq_type == QDEC_IRQ_DATA_READY)
  {
    qdec_register->QDEC_IRQ_ENABLE_UNION.QDEC_IRQ_ENABLE_CELLS.IRQ_ENABLE_DATA_RDY = 0x1;
  }
  else
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_disable_irq(hal_qdec_irq_type_t irq_type)
{
  if (irq_type == QDEC_IRQ_Z_SUM)
  {
    qdec_register->QDEC_IRQ_ENABLE_UNION.QDEC_IRQ_ENABLE_CELLS.IRQ_ENABLE_Z_SUM = 0x0;
    qdec_register->QDEC_WKUP_ENABLE_UNION.QDEC_WKUP_ENABLE_CELLS.WKUP_ENABLE_Z_SUM = 0x0;
  }
  else if (irq_type == QDEC_IRQ_Z_CNT)
  {
    qdec_register->QDEC_IRQ_ENABLE_UNION.QDEC_IRQ_ENABLE_CELLS.IRQ_ENABLE_Z_CNT = 0x0;
    qdec_register->QDEC_WKUP_ENABLE_UNION.QDEC_WKUP_ENABLE_CELLS.WKUP_ENABLE_Z_CNT = 0x0;
  }
  else if (irq_type == QDEC_IRQ_DATA_READY)
  {
    qdec_register->QDEC_IRQ_ENABLE_UNION.QDEC_IRQ_ENABLE_CELLS.IRQ_ENABLE_DATA_RDY = 0x0;
  }
  else
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_latch_status_is_busy(bool *hw_latch_status)
{
  uint8_t latch_status;
  volatile uint8_t data_ready_irq_status = qdec_register->QDEC_IRQ_ENABLE_UNION.QDEC_IRQ_ENABLE_CELLS.IRQ_ENABLE_DATA_RDY;
  if(data_ready_irq_status == IRQ_ENABLE)
  {
    return HAL_QDEC_STATUS_ERROR;
  }

  latch_status = qdec_register->QDEC_LATCH_N_CLR_UNION.QDEC_LATCH_N_CLR_CELLS.LATCH_STATUS;
  if (latch_status == 0x1)
  {
    *hw_latch_status=false;
  }
  else
  {
    *hw_latch_status=true;
  }
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_runnig_config_group_para(hal_qdec_sel_group_setting_t group_id, hal_qdec_group_config_t group_config)
{
  if (group_id > HAL_QDEC_SELECT_GROUP_B)
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }

  hal_qdec_status_t ret;
  ret = qdec_group_config_para_check(group_config);
  if (ret != HAL_QDEC_STATUS_OK)
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }

  if(group_id == HAL_QDEC_SELECT_GROUP_A)
  {
    qdec_register->QDEC_SAMPLE_CON_A_UNION.QDEC_SAMPLE_CON_A_CELLS.SMP_PERIOD_A = group_config.smp_period;
    qdec_register->QDEC_SAMPLE_CON_A_UNION.QDEC_SAMPLE_CON_A_CELLS.LED_PERIOD_A = group_config.led_period;
    qdec_register->QDEC_SAMPLE_CON_A_UNION.QDEC_SAMPLE_CON_A_CELLS.DBC_COUNT_A = group_config.dbc_count;
    g_qdec_cfg.group_a_cfg = group_config;
  }else{
    qdec_register->QDEC_SAMPLE_CON_B_UNION.QDEC_SAMPLE_CON_B_CELLS.SMP_PERIOD_B = group_config.smp_period;
    qdec_register->QDEC_SAMPLE_CON_B_UNION.QDEC_SAMPLE_CON_B_CELLS.LED_PERIOD_B = group_config.led_period;
    qdec_register->QDEC_SAMPLE_CON_B_UNION.QDEC_SAMPLE_CON_B_CELLS.DBC_COUNT_B = group_config.dbc_count;
    g_qdec_cfg.group_b_cfg = group_config;
  }

  qdec_register->QDEC_CON_UNION.QDEC_CON_CELLS.SW_RELOAD = 0x01;
  // qdec_register->QDEC_SEL_GROUP_UNION.QDEC_SEL_GROUP_CELLS.SEL_GROUP = group_id;
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_data_getting_type_set(hal_qdec_data_getting_type_t qdec_data_getting_type)
{
  hal_qdec_status_t ret;
  if (qdec_data_getting_type == HAL_QDEC_READ_DATA_BY_IRQ)
  {
    ret = hal_qdec_enable_irq(QDEC_IRQ_DATA_READY);
    if (ret != HAL_QDEC_STATUS_OK)
    {
      return HAL_QDEC_STATUS_ERROR;
    }
  }
  else if (qdec_data_getting_type == HAL_QDEC_READ_DATA_BY_NEXT_CYCLE)
  {
    ret = hal_qdec_disable_irq(QDEC_IRQ_DATA_READY);
    if (ret != HAL_QDEC_STATUS_OK)
    {
      return HAL_QDEC_STATUS_ERROR;
    }
  }
  else
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_get_config_group_para(hal_qdec_sel_group_setting_t group_id, hal_qdec_group_config_t *group_config)
{
  if (group_id > HAL_QDEC_SELECT_GROUP_B)
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }

  if(group_id == HAL_QDEC_SELECT_GROUP_A)
  {
    *group_config = g_qdec_cfg.group_a_cfg;
  }else{
    *group_config = g_qdec_cfg.group_b_cfg;
  }
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_mode_status_t hal_qdec_get_mode_status()
{
  return g_qdec_mode_status;
}

hal_qdec_status_t hal_qdec_get_irq_status(hal_qdec_irq_type_t irq_type , hal_qdec_irq_status_t *irq_status)
{
  if (irq_type == QDEC_IRQ_Z_SUM)
  {
    *irq_status = qdec_register->QDEC_IRQ_ENABLE_UNION.QDEC_IRQ_ENABLE_CELLS.IRQ_ENABLE_Z_SUM;
  }
  else if (irq_type == QDEC_IRQ_Z_CNT)
  {
    *irq_status = qdec_register->QDEC_IRQ_ENABLE_UNION.QDEC_IRQ_ENABLE_CELLS.IRQ_ENABLE_Z_CNT;
  }
  else if (irq_type == QDEC_IRQ_DATA_READY)
  {
    *irq_status = qdec_register->QDEC_IRQ_ENABLE_UNION.QDEC_IRQ_ENABLE_CELLS.IRQ_ENABLE_DATA_RDY;
  }else
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_set_z_sum_threshold(uint16_t threshold)
{
  if (threshold > Z_SUM_THR_MAX)
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }
  g_qdec_cfg.z_sum_thr = threshold;
  qdec_register->QDEC_SAMPLE_THR_UNION.QDEC_SAMPLE_THR_CELLS.Z_SUM_THR = g_qdec_cfg.z_sum_thr;
  /*push qdec cfg to qdec hw internal reg*/
  qdec_register->QDEC_CON_UNION.QDEC_CON_CELLS.SW_RELOAD = 0x01;
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_get_z_sum_threshold(uint16_t *threshold)
{
  uint32_t z_sum_thr;
  if (threshold == NULL)
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }

  z_sum_thr = qdec_register->QDEC_SAMPLE_THR_UNION.QDEC_SAMPLE_THR_CELLS.Z_SUM_THR;
  if(z_sum_thr != g_qdec_cfg.z_sum_thr)
  {
    //assert(0);
    return HAL_QDEC_STATUS_ERROR;
  }
  *threshold = z_sum_thr;
  return HAL_QDEC_STATUS_OK;
}

hal_qdec_status_t hal_qdec_get_hw_sel_cfg(hal_qdec_irq_status_t *hw_sel_status, hal_qdec_sel_group_setting_t *group)
{
  if((hw_sel_status == NULL)||(group == NULL))
  {
    return HAL_QDEC_INVALID_PARAMETER;
  }
  uint8_t hw_sel_en_reg = qdec_register->QDEC_SEL_GROUP_UNION.QDEC_SEL_GROUP_CELLS.HW_SEL_EN;
  if(hw_sel_en_reg ==0x0)
  {
    *hw_sel_status = IRQ_DISABLE;
  }else{
    *hw_sel_status = IRQ_ENABLE;
  }
  uint8_t hw_sel_goup_reg = qdec_register->QDEC_SEL_GROUP_UNION.QDEC_SEL_GROUP_CELLS.HW_SEL_GROUP;
  if(hw_sel_goup_reg ==0x0)
  {
    *group = HAL_QDEC_SELECT_GROUP_A;
  }else{
    *group = HAL_QDEC_SELECT_GROUP_B;
  }
  return HAL_QDEC_STATUS_OK;
}

#endif /* HAL_QDEC_MODULE_ENABLED */
