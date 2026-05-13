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

#ifdef HAL_SARADC_MODULE_ENABLED
#include "hal_saradc.h"
#include "hal_platform.h"
#include "hal_gpt.h"
#include "syslog.h"
#include "memory_attribute.h"

float saradc_vref_real = 1.396, saradc_oe = -0.0002, saradc_ge = -0.0002;

hal_adc_status_t hal_saradc_set_mode(hal_saradc_data_rate_t data_rate, hal_saradc_measure_mode_t measure_mode)
{
    switch (measure_mode) {
        case (HAL_SARADC_MEASURE_SE_MODE):
            //SE mode
            *((volatile uint32_t *)(0x42080084)) = 0x10;
            *((volatile uint32_t *)(0x42080088)) = 0x0;
            break;
        case (HAL_SARADC_MEASURE_DIV_MODE):
            //DIV mode
            *((volatile uint32_t *)(0x42080084)) = 0x10;
            *((volatile uint32_t *)(0x42080088)) = 0x4000;
            break;
        case (HAL_SARADC_MEASURE_DIFF_MODE):
            //DIFF mode
            *((volatile uint32_t *)(0x42080084)) = 0x4010;
            *((volatile uint32_t *)(0x42080088)) = 0x0;
            break;
        default:
            return HAL_ADC_STATUS_INVALID_PARAMETER;
            break;
    }

    switch (data_rate) {
        case (HAL_SARADC_DATA_RATE_HS_MODE):
            //HS mode
            ADC->AUXADC_DIV_CON = 0x0;
            *((volatile uint32_t *)(0x42080084)) = 0x21;
            if (measure_mode == HAL_SARADC_MEASURE_DIFF_MODE) {
                *((volatile uint32_t *)(0x42080084)) = 0x4021;
            } else {
                *((volatile uint32_t *)(0x42080084)) = 0x21;
            }
            *((volatile uint32_t *)(0x4208008C)) = 0x140;
            break;
        case (HAL_SARADC_DATA_RATE_MS_MODE):
            //MS mode
            ADC->AUXADC_DIV_CON = 0x1;
            *((volatile uint32_t *)(0x42080084)) = 0x11;
            *((volatile uint32_t *)(0x42080084)) = 0x11;
            *((volatile uint32_t *)(0x4208008C)) = 0x0;
            break;
        case (HAL_SARADC_DATA_RATE_LS_MODE):
            //LS mode
            ADC->AUXADC_DIV_CON = 0x5;
            *((volatile uint32_t *)(0x42080084)) = 0x10;
            *((volatile uint32_t *)(0x42080084)) = 0x30;
            *((volatile uint32_t *)(0x4208008C)) = 0x0;
            break;
        default:
            return HAL_ADC_STATUS_INVALID_PARAMETER;
            break;
    }
    // log_hal_msgid_info("0x42080084 value:%x", 0, *((volatile uint32_t *)(0x42080084)));
    return HAL_ADC_STATUS_OK;
}

hal_adc_status_t hal_saradc_enable()
{
    // if (HAL_CLOCK_STATUS_OK != hal_clock_enable(HAL_CLOCK_CG_AUXADC)) {
    //     //log_hal_msgid_error("[ADC] Clock enable failed!", 0);
    //     return HAL_ADC_STATUS_ERROR;
    // }
    /* Enable ADC analog power */
    ADC->MACRO_CON2_UNION.MACRO_CON2 |= MACRO_CON2_RG_AUXADC_LDO_EN_MASK;
    hal_gpt_delay_us(50);
    ADC->ANA_EN_CON_UNION.ANA_EN_CON = 0x101;
    hal_gpt_delay_us(50);
    *((volatile uint32_t *)(0x42080084)) = 0x121;
    return HAL_ADC_STATUS_OK;
}

hal_adc_status_t hal_saradc_disable()
{
    /* Disable AUXADC */
    ADC->ANA_EN_CON_UNION.ANA_EN_CON = 0;
    /* Disable VA28_LDO */
    ADC->MACRO_CON2_UNION.MACRO_CON2 = 0;
    // if (HAL_CLOCK_STATUS_OK != hal_clock_disable(HAL_CLOCK_CG_AUXADC)) {
    //     //log_hal_msgid_error("[ADC] Clock disable failed!", 0);
    //     return HAL_ADC_STATUS_ERROR;
    // }
    return HAL_ADC_STATUS_OK;
}

hal_adc_status_t hal_saradc_set_gpio_mode(uint32_t channel_mask, hal_saradc_gpio_mode_t mode)
{
    uint32_t temp = 0;
    (void)temp;
    for (uint8_t ch = 0; ch < HAL_SARADC_CHANNEL_GPIO_MAX; ch++) {
        if (channel_mask & (1 << ch)) {
            if (ch <= 11) {
                temp = ch + 26;
            } else {
                temp = ch + 28;
            }
            if (mode == HAL_SARADC_GPIO_ANALOG_MODE) {
                // hal_gpio_set_analog_mode(temp);
            } else {
                // hal_gpio_clear_analog_mode(temp);
            }
        }
    }
    return HAL_ADC_STATUS_OK;
}

hal_adc_status_t hal_saradc_get_data_immediately(hal_saradc_data_t *saradc_data)
{
    ADC->AUXADC_CON1 = 0x0;// clear all channel
    ADC->AUXADC_CON1 = saradc_data->channel_mask;//trigger all channel
    while (ADC->AUXADC_CON3_UNION.AUXADC_CON3_CELLS.ADC_STAT & AUXADC_CON3_ADC_STA_MASK);
    for (uint8_t ch = 0; ch < 32; ch++) {
        if (saradc_data->channel_mask & (1 << ch)) {
            saradc_data->channel_data[ch] = ADC->AUXADC_DATA[ch];
        }
    }
    return HAL_ADC_STATUS_OK;
}

hal_adc_status_t hal_saradc_get_data_average(hal_saradc_data_t *saradc_data, hal_adc_average_t average_num)
{
    ADC->AUXADC_AVG_NUM = average_num;// Set average number
    ADC->AUXADC_CON1 = 0x0;// clear all channel
    for (uint8_t ch = 0; ch < 32; ch++) {
        if (saradc_data->channel_mask & (1 << ch)) {
            ADC->AUXADC_CON4_UNION.AUXADC_CON4 |= (1 << 8);// Enable auto average
            ADC->AUXADC_CON1 = 0x1 << ch;// trigger channel
            while (ADC->AUXADC_AVG_READY == 0);
        }
    }
    for (uint8_t ch = 0; ch < 32; ch++) {
        if (saradc_data->channel_mask & (1 << ch)) {
            saradc_data->channel_data[ch] = ADC->AVG_DATA[ch] >> 3;
        }
    }
    return HAL_ADC_STATUS_OK;
}

#include "hal_clock.h"
#include "hal_clock_internal.h"
#include "hal_gpio_internal.h"
#include "hal_gpio.h"

#define SW_DMA_CHANNEL_NUMBER       (0)
#define SW_DMA_CHANNEL_CLOCK_CG     HAL_CLOCK_CG_FAST_DMA0
#define SW_DMA_CHANNEL_REG_BASE     ((GDMA_REGISTER_T *)(SW_DMA_GLB_REG_BASE + ((1 + SW_DMA_CHANNEL_NUMBER) * 0x100)))
#define SW_DMA_GLB_REG_BASE         (DMA_0_BASE)
#define HAL_SW_DMA_WORD             2
#define HAL_SW_DMA_4_BEAT_BURST     0x2
// #define GPIO_DOUT_REG_CTRL_PIN_NUM          32      /*  pin munber controlled by output data register is 32  */
// #define GPIO_REG_ONE_BIT_SET_CLR            0x1

DMA_REGISTER_GLOABL_T *const g_sw_dma_reg_global_table = (DMA_REGISTER_GLOABL_T*)SW_DMA_GLB_REG_BASE;
GDMA_REGISTER_T *const g_sw_dma_reg = SW_DMA_CHANNEL_REG_BASE;
// GPIO_BASE_REGISTER_T *gpio_base = (GPIO_BASE_REGISTER_T *)(GPIO_BASE);

hal_adc_status_t hal_saradc_dma_init()
{
    //mcu side open clock cg
    // hal_clock_enable(SW_DMA_CHANNEL_CLOCK_CG);

    //sw dma init

    g_sw_dma_reg_global_table->RG_GLB_CLK_SET = (DMA_GLB_IRQ_CFG_BIT_MASK(SW_DMA_CHANNEL_NUMBER));
    g_sw_dma_reg_global_table->RG_GLB_CPU0_INT_SET = (DMA_GLB_IRQ_CFG_BIT_MASK(SW_DMA_CHANNEL_NUMBER));

    g_sw_dma_reg->GDMA_SRC = 0;
    g_sw_dma_reg->GDMA_DST = 0;
    g_sw_dma_reg->GDMA_WPPT = 0;
    g_sw_dma_reg->GDMA_WPTO = 0;
    g_sw_dma_reg->GDMA_CON_UNION.GDMA_CON = 0;
    g_sw_dma_reg->GDMA_START = 0;
    g_sw_dma_reg->GDMA_LIMITER = 0x0;
    g_sw_dma_reg->GDMA_ACKINT = GDMA_ACKINT_BIT_MASK;
    g_sw_dma_reg->GDMA_COUNT = 0x10;
    g_sw_dma_reg->GDMA_SRC = (uint32_t)(&ADC->AUXADC_DATA[0]);
    g_sw_dma_reg->GDMA_CON_UNION.GDMA_CON = (1) | (1 << 1) | (0 << 3);
    g_sw_dma_reg->GDMA_CON_UNION.GDMA_CON |= (HAL_SW_DMA_WORD << 8);
    g_sw_dma_reg->GDMA_CON_UNION.GDMA_CON |= (HAL_SW_DMA_4_BEAT_BURST << 18);
    g_sw_dma_reg->GDMA_CON_UNION.GDMA_CON |= (0 << 24);
    // clear all channel
    ADC->AUXADC_CON1 = 0x0;
    return HAL_ADC_STATUS_OK;
}

hal_adc_status_t hal_saradc_get_data_immediately_for_special(volatile uint32_t *dest_address, uint32_t channel_mask, hal_saradc_special_gpio_cfg_t gpio_cfg, uint8_t mux_max_index)
{
    if( gpio_cfg.mux_index == 0){
        //trigger channel
        ADC->AUXADC_CON1 = channel_mask & 0xFFFF;
    }

    // clear dma & stop dma
    g_sw_dma_reg->GDMA_START = 0;

    // set dma des
    g_sw_dma_reg->GDMA_DST = (uint32_t)dest_address;
    //query adc 
    while (ADC->AUXADC_CON3_UNION.AUXADC_CON3_CELLS.ADC_STAT & AUXADC_CON3_ADC_STA_MASK);

    // start dma
    g_sw_dma_reg->GDMA_START = 1 << 15;

    // clear all channel
    ADC->AUXADC_CON1 = 0x0;

    uint32_t reg_num;
    uint32_t index_num;
    int i = 0;
    for(i = 0;i<3;i++)
    {
        uint8_t gpio_pin = gpio_cfg.gpio_pin[i];
        uint8_t gpio_data = ((gpio_cfg.mux_index) >> i) & 0x1;//row i gpio level;
        // set gpio
        reg_num   = gpio_pin >> 5;
        index_num = gpio_pin & 0x1f;

        if (gpio_data) {
            gpio_base->GPIO_DOUT_SET[reg_num] = (GPIO_REG_ONE_BIT_SET_CLR << index_num);
        } else {
            gpio_base->GPIO_DOUT_CLR[reg_num] = (GPIO_REG_ONE_BIT_SET_CLR << index_num);
        }
    }
    // query dma
    while((g_sw_dma_reg_global_table->RG_GLB_STA) & DMA_GLB_RUNNING_BIT_MASK(SW_DMA_CHANNEL_NUMBER));

    if(gpio_cfg.mux_index != (mux_max_index-1)){
        ADC->AUXADC_CON1 = channel_mask & 0xFFFF;
    }

    return HAL_ADC_STATUS_OK;
}

hal_adc_status_t hal_saradc_get_calibration_voltage_mV(hal_saradc_measure_mode_t measure_mode, uint32_t raw_data, uint32_t *cal_voltage_mV)
{
    float mV = 0;
    mV = (((float)(raw_data)/4096.0f) - saradc_oe) * (saradc_vref_real / (1.0f + saradc_ge));
    switch (measure_mode) {
        case (HAL_SARADC_MEASURE_SE_MODE):
            //SE mode
            *cal_voltage_mV = (uint32_t)(mV * 1000.0f);
            break;
        case (HAL_SARADC_MEASURE_DIV_MODE):
            //DIV mode
            *cal_voltage_mV = (uint32_t)((mV / 0.375f) * 1000.0f);
            break;
        case (HAL_SARADC_MEASURE_DIFF_MODE):
            //DIFF mode
            *cal_voltage_mV = (uint32_t)((mV - 0.7f) * 2000.0f);
            break;
        default:
            return HAL_ADC_STATUS_INVALID_PARAMETER;
            break;
    }
    return HAL_ADC_STATUS_OK;
}

hal_adc_status_t hal_saradc_init(hal_saradc_data_rate_t data_rate, hal_saradc_measure_mode_t measure_mode)
{
    hal_saradc_set_mode(data_rate, measure_mode);
    //setting BG EN 4
    *((volatile uint32_t *)(0x42080048)) = 0x4401;
    *((volatile uint32_t *)(0x4208004C)) = 0x70F;
    *((volatile uint32_t *)(0x42080050)) = 0x40F;
    *((volatile uint32_t *)(0x4208005C)) = 0x41;
    //ADC config setting
    *((volatile uint32_t *)(0x420302A0)) = 0x0;
    ADC->AUXADC_SPL_CON = 0x2;
    /* bus clock switch to 32M*/
    // clock_mux_sel(CLK_SLOW_BUS_SEL, MUX_SLOW_BUS_IDX_XO);
    hal_saradc_enable();
    //set debug clk out 32M OFF
    *((volatile uint32_t *)(0x42010108)) = 0x3;
    ADC->ACD_FUNC_MODE_CTL = 0x1;
    return HAL_ADC_STATUS_OK;
}

hal_adc_status_t hal_saradc_deinit()
{
    // clock_mux_sel(CLK_SLOW_BUS_SEL, MUX_SLOW_BUS_IDX_OSC_26M);
    hal_saradc_disable();
    return HAL_ADC_STATUS_OK;
}

#endif