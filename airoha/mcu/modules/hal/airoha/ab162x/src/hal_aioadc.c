/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
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

#ifdef HAL_AIOADC_MODULE_ENABLED

#include <stdio.h>
#include "hal_pmu.h"
#include "hal_gpt.h"
#include "hal_gpt_internal.h"
#include "hal_gpio.h"
#include "hal_gpio_internal.h"
#include "hal_nvic.h"
#include "hal_nvic_internal.h"
#include "hal_saradc_internal.h"


#include "hal_flash.h"
#include "hal_flash_opt.h"
#include "hal_flash_disk_internal.h"

#include "hal_clock.h"

#include "hal_aioadc.h"

#define AIOADC_READ(addr)                  *((volatile uint32_t *)(addr))
#define AIOADC_WRITE(addr, val)            *((volatile uint32_t *)(addr)) = val

static const hal_clock_cg_id aio_clock_cg = HAL_CLOCK_CG_AIO;

static uint32_t aioadc_get_trim_data_adress(hal_aioadc_mode_sel_t aioadc_mode);
// static void aioadc_debug_signal()
// {
//     /*debug singnal*/
//     hal_pinmux_status_t ret;
//     *(volatile uint32_t *)(0x4007009c) = (0x00000201);
//     *(volatile uint32_t *)(0x422f0030) = (0x00000400);
//     *(volatile uint32_t *)(0x42010108) = (0x00000014);
//     ret = hal_pinmux_set_function(18, 13);
//     if (ret != HAL_PINMUX_STATUS_OK)
//     {
//         printk("hal_pinmux_set_function failed\n");
//     }
//     ret = hal_pinmux_set_function(19, 13);
//     if (ret != HAL_PINMUX_STATUS_OK)
//     {
//         printk("hal_pinmux_set_function failed\n");
//     }
//     ret = hal_pinmux_set_function(20, 13);
//     if (ret != HAL_PINMUX_STATUS_OK)
//     {
//         printk("hal_pinmux_set_function failed\n");
//     }
//     ret = hal_pinmux_set_function(21, 13);
//     if (ret != HAL_PINMUX_STATUS_OK)
//     {
//         printk("hal_pinmux_set_function failed\n");
//     }
//     ret = hal_pinmux_set_function(22, 13);
//     if (ret != HAL_PINMUX_STATUS_OK)
//     {
//         printk("hal_pinmux_set_function failed\n");
//     }
//     ret = hal_pinmux_set_function(23, 13);
//     if (ret != HAL_PINMUX_STATUS_OK)
//     {
//         printk("hal_pinmux_set_function failed\n");
//     }
// }

hal_aioadc_status_t hal_tmepsensor_init(void);

static void aioadc_mode_sel(hal_aioadc_ch_en_t aioadc_ch,hal_aioadc_mode_sel_t aioadc_mode)
{
    printk("aio_adc mode = %d\n", aioadc_mode);
    switch (aioadc_mode)
    {
    /*se mode*/
    case HAL_AIOADC_MODE_SE_0:
        AIOADC_WRITE(0x42080030,0x00000111);
        AIOADC_WRITE(0x42080030,0x00000113);
        AIOADC_WRITE(0x42080034,0x00005010);
        AIOADC_WRITE(0x42080038,0x00008310);
        AIOADC_WRITE(0x4208003c,0x00000001);
        AIOADC_WRITE(0x42080040,0x00002510);
        break;
    case HAL_AIOADC_MODE_SE_1:
        AIOADC_WRITE(0x42080030,0x00000111);
        AIOADC_WRITE(0x42080034,0x00004030);
        AIOADC_WRITE(0x42080038,0x00000370);
        AIOADC_WRITE(0x42080030,0x00000113);
        AIOADC_WRITE(0x42080034,0x00004030);
        AIOADC_WRITE(0x42080038,0x00008320);
        AIOADC_WRITE(0x4208003c,0x00000001);
        AIOADC_WRITE(0x42080040,0x00002510);
        break;
    case HAL_AIOADC_MODE_SE_2:
        AIOADC_WRITE(0x42080030,0x00000111);
        AIOADC_WRITE(0x42080034,0x000020f0);
        AIOADC_WRITE(0x42080038,0x00000360);
        AIOADC_WRITE(0x4208003c,0x00000009);
        AIOADC_WRITE(0x42080030,0x00000113);
        AIOADC_WRITE(0x42080034,0x000020f0);
        AIOADC_WRITE(0x42080038,0x00008320);
        AIOADC_WRITE(0x4208003c,0x00000009);
        AIOADC_WRITE(0x42080040,0x00002510);
        break;
    case HAL_AIOADC_MODE_SE_3:
        AIOADC_WRITE(0x42080030,0x00000111);
        AIOADC_WRITE(0x42080034,0x000013f0);
        AIOADC_WRITE(0x42080038,0x00000360);
        AIOADC_WRITE(0x4208003c,0x00000009);
        AIOADC_WRITE(0x42080030,0x00000113);

        AIOADC_WRITE(0x42080034,0x000013f0);
        AIOADC_WRITE(0x42080038,0x00008320);
        AIOADC_WRITE(0x4208003c,0x00000009);
        AIOADC_WRITE(0x42080040,0x00002510);
        break;
    case HAL_AIOADC_MODE_SE_4:
        AIOADC_WRITE(0x42080030,0x00000111);
        AIOADC_WRITE(0x42080034,0x00000ff0);
        AIOADC_WRITE(0x42080038,0x00000360);
        AIOADC_WRITE(0x4208003c,0x00000009);
        AIOADC_WRITE(0x42080030,0x00000113);
        AIOADC_WRITE(0x42080034,0x00000ff0);
        AIOADC_WRITE(0x42080038,0x00008320);
        AIOADC_WRITE(0x4208003c,0x00000009);
        AIOADC_WRITE(0x42080040,0x00002510);
        break;
    /*diff mode*/
    case HAL_AIOADC_MODE_DIFF_0:
        AIOADC_WRITE(0x42080030,0x00001911);
        if(aioadc_ch == HAL_AIOADC_CH_1)
        {
            AIOADC_WRITE(0x42080030,0x00000a19);
        }else
        {
           AIOADC_WRITE(0x42080030,0x00001a19); 
        }
        AIOADC_WRITE(0x42080034,0x00000000);
        AIOADC_WRITE(0x42080038,0x00000350);
        AIOADC_WRITE(0x4208003c,0x00000001);
        AIOADC_WRITE(0x42080040,0x00002510);
        printk("debug-HAL_AIOADC_MODE_DIFF_0");


        break;
    case HAL_AIOADC_MODE_DIFF_1:
        AIOADC_WRITE(0x42080030,0x00001911);
        if(aioadc_ch == HAL_AIOADC_CH_1)
        {
            AIOADC_WRITE(0x42080030,0x00000819);
        }else
        {
           AIOADC_WRITE(0x42080030,0x00001819); 
        }
        AIOADC_WRITE(0x42080034,0x00000000);
        AIOADC_WRITE(0x42080038,0x00000360);
        AIOADC_WRITE(0x4208003c,0x00000001);
        AIOADC_WRITE(0x42080040,0x00002510);
        break;
    case HAL_AIOADC_MODE_DIFF_2:
        AIOADC_WRITE(0x42080030,0x00001911);
        if(aioadc_ch == HAL_AIOADC_CH_1)
        {
            AIOADC_WRITE(0x42080030,0x00000819);
        }else
        {
           AIOADC_WRITE(0x42080030,0x00001819); 
        }
        AIOADC_WRITE(0x42080034,0x00000020);
        AIOADC_WRITE(0x42080038,0x00000360);
        AIOADC_WRITE(0x4208003c,0x00000009);
        AIOADC_WRITE(0x42080040,0x00002510);
        break;
    case HAL_AIOADC_MODE_DIFF_3:
        AIOADC_WRITE(0x42080030,0x00001911);
        if(aioadc_ch == HAL_AIOADC_CH_1)
        {
            AIOADC_WRITE(0x42080030,0x00000819);
        }else
        {
           AIOADC_WRITE(0x42080030,0x00001819); 
        }
        AIOADC_WRITE(0x42080034,0x00000060);
        AIOADC_WRITE(0x42080038,0x00000360);
        AIOADC_WRITE(0x4208003c,0x00000009);
        AIOADC_WRITE(0x42080040,0x00002510);
        break;
    case HAL_AIOADC_MODE_DIFF_4:
        AIOADC_WRITE(0x42080030,0x00001911);
        if(aioadc_ch == HAL_AIOADC_CH_1)
        {
            AIOADC_WRITE(0x42080030,0x00000819);
        }else
        {
           AIOADC_WRITE(0x42080030,0x00001819); 
        }
        AIOADC_WRITE(0x42080034,0x000000e0);
        AIOADC_WRITE(0x42080038,0x00000360);
        AIOADC_WRITE(0x4208003c,0x00000009);
        AIOADC_WRITE(0x42080040,0x00002510);
        break;
    case HAL_AIOADC_MODE_VBAT:
        AIOADC_WRITE(0x42080030,0x00000111);
        AIOADC_WRITE(0x42080030,0x00000511);
        AIOADC_WRITE(0x42080034,0x00005012);
        AIOADC_WRITE(0x42080038,0x00008310);
        AIOADC_WRITE(0x4208003c,0x00000001);
        AIOADC_WRITE(0x42080040,0x00002510);
        break;
    default:
        printk("aio_adc mode error = %d\n", aioadc_mode);
        break;
    }
}

static uint32_t aioadc_get_ch_mask(hal_aioadc_ch_en_t aioadc_ch)
{
    return (0x1 << aioadc_ch);
}

uint32_t aioadc_get_ch_data_reg_mask(hal_aioadc_ch_en_t aioadc_ch)
{
    // printk("aio_adc_ch_en,open_channel-%d", aioadc_ch);
    uint32_t aioadc_data_reg_mask=0x40070000;
    switch (aioadc_ch)
    {
    case HAL_AIOADC_CH_0:
        aioadc_data_reg_mask = (0x40070000);
        break;
    case HAL_AIOADC_CH_1:
        aioadc_data_reg_mask = (0x40070000 + 0x4);
        break;
    case HAL_AIOADC_CH_2:
        aioadc_data_reg_mask = (0x40070000 + 0x8);
        break;
    case HAL_AIOADC_CH_3:
        aioadc_data_reg_mask = (0x40070000 + 0xc);
        break;
    case HAL_AIOADC_CH_4:
        aioadc_data_reg_mask = (0x40070000 + 0x10);
        break;
    case HAL_AIOADC_CH_5:
        aioadc_data_reg_mask = (0x40070000 + 0x14);
        break;
    case HAL_AIOADC_CH_6:
        aioadc_data_reg_mask = (0x40070000 + 0x18);
        break;
    case HAL_AIOADC_CH_7:
        aioadc_data_reg_mask = (0x40070000 + 0x1c);
        break;
    case HAL_AIOADC_CH_8:
        aioadc_data_reg_mask = (0x40070000 + 0x20);
        break;
    case HAL_AIOADC_CH_9:
        aioadc_data_reg_mask = (0x40070000 + 0x24);
        break;
    default:
        printk("aio_adc_ch para : error");
        break;
    }
    // printk("aio_adc_ch_en,aioadc_data_reg_mask-%x", aioadc_data_reg_mask);
    return aioadc_data_reg_mask;
}

static void aioadc_off_seq(void)
{
    AIOADC_WRITE(0x42080004,0x00001043);
    AIOADC_WRITE(0x42080004,0x00000043);

    AIOADC_WRITE(0x4208000c,0x00000010);
    AIOADC_WRITE(0x4208000c,0x00000010);
    AIOADC_WRITE(0x4208000c,0x00000010);

    AIOADC_WRITE(0x42080018,0x00000015);

    AIOADC_WRITE(0x4208001c,0x00000010);
    AIOADC_WRITE(0x4208001c,0x00000001);

    AIOADC_WRITE(0x42080004,0x00000042);
    AIOADC_WRITE(0x42080004,0x00000002);
    AIOADC_WRITE(0x42080004,0x00000000);

    AIOADC_WRITE(0x42080030,0x00000000);//aio setting
    AIOADC_WRITE(0x42080034,0x00000000);
    AIOADC_WRITE(0x42080038,0x00000000);
    AIOADC_WRITE(0x42080040,0x00000000);
    AIOADC_WRITE(0x4208003c,0x00000000);

    AIOADC_WRITE(0x42080024,0x00000004);
    AIOADC_WRITE(0x42080024,0x00000000);

    AIOADC_WRITE(0x4208000c,0x00000000);

    AIOADC_WRITE(0x40070094,0x00000000);// Dig CLK off

    AIOADC_WRITE(0x42080054,0x00000000);// temp sensor setting
    // AIOADC_WRITE(0x4208005c,0x00000000);// bandgap core setting
    // AIOADC_WRITE(0x42080048,0x00000000);
    hal_saradc_sdadc_common_setting_internal(false);
}

static void digital_top(void)
{
    // AIOADC_WRITE(0x420302a0,0x00000000);

    // AIOADC_WRITE(0x42040b20,0xffffffff);
    // AIOADC_WRITE(0x42040b50,0xffffffff);
    // AIOADC_WRITE(0x42040bb0,0xffffffff);
    // AIOADC_WRITE(0x42040b80,0xffffffff);

    // AIOADC_WRITE(0x422d0320,0xffffffff);
    // AIOADC_WRITE(0x422d0350,0xffffffff);
    // AIOADC_WRITE(0x422d0380,0xffffffff);

    // AIOADC_WRITE(0x42130150,0x00000016);
    // AIOADC_WRITE(0x42130150,0x0000001e);

    // AIOADC_WRITE(0x421301d8,0x00000000);

    // AIOADC_WRITE(0x42130150,0x0000000e);
    // AIOADC_WRITE(0x42130150,0x0000001e);
    // AIOADC_WRITE(0x42130150,0x0000001c);
    // AIOADC_WRITE(0x42130150,0x0000001d);

    // AIOADC_WRITE(0x421301d8,0x01000000);

    // AIOADC_WRITE(0x42130150,0x0000000d);

    // AIOADC_WRITE(0x422f0060,0x00000000);
    // AIOADC_WRITE(0xc0000000,0x20c04000);

    /*open aio clock cg*/
    if (hal_clock_is_enabled(aio_clock_cg) != true) {
        if (HAL_CLOCK_STATUS_OK != hal_clock_enable(aio_clock_cg)) {
            printk("aio_clock_cg enable failed!\r\n");
        }
    }
    /*infra pd: enable when cmsys on*/
}

static void abb_poweron(hal_aioadc_mode_sel_t aioadc_mode)
{

    // AIOADC_WRITE(0x42080048,0x00004401);
    // AIOADC_WRITE(0x4208004c,0x0000070f);
    // AIOADC_WRITE(0x42080050,0x0000040f);
    // AIOADC_WRITE(0x4208005c,0x00000041);
    hal_saradc_sdadc_common_setting_internal(true);

    if(aioadc_mode == HAL_AIOADC_MODE_TEMP_SENSOR)
    {
        // AIOADC_WRITE(0x42080054,0x00002201);
    }

    AIOADC_WRITE(0x4208007c,0x00000011);
    AIOADC_WRITE(0x4208000c,0x00000010);
    hal_gpt_delay_us(100);
    AIOADC_WRITE(0x42080024,0x00000001);
    AIOADC_WRITE(0x42080024,0x00000001);
    AIOADC_WRITE(0x42080024,0x00000005);
    AIOADC_WRITE(0x42080024,0x00000005);
    AIOADC_WRITE(0x42080024,0x00000005);

    AIOADC_WRITE(0x42080008,0x00000001);
    AIOADC_WRITE(0x42080008,0x00000001);
    AIOADC_WRITE(0x42080008,0x00000005);

    AIOADC_WRITE(0x4208000c,0x00000010);
    AIOADC_WRITE(0x4208000c,0x00000010);
    AIOADC_WRITE(0x4208000c,0x00000010);

    AIOADC_WRITE(0x42080008,0x00000005);
    AIOADC_WRITE(0x42080008,0x00000000);
    AIOADC_WRITE(0x42080008,0x00000000);
}

static void aio_setting(hal_aioadc_mode_sel_t aioadc_mode)
{
    switch (aioadc_mode)
    {
    case HAL_AIOADC_MODE_VBAT:
        AIOADC_WRITE(0x42080030,0x00000113);
        AIOADC_WRITE(0x42080034,0x00005010);
        AIOADC_WRITE(0x42080038,0x00000330);
        AIOADC_WRITE(0x4208003c,0x00000001);
        AIOADC_WRITE(0x42080040,0x00002410);
        break;
    // case HAL_AIOADC_MODE_RFCAL:
    //     AIOADC_WRITE(0x42080030,0x00000511);
    //     AIOADC_WRITE(0x42080034,0x00005010);
    //     AIOADC_WRITE(0x42080038,0x00000310);
    //     AIOADC_WRITE(0x4208003c,0x00000001);
    //     AIOADC_WRITE(0x42080040,0x00002510);
    //     break;
    // case HAL_AIOADC_MODE_PMU_ATST:
    //     AIOADC_WRITE(0x42080030,0x00000511);
    //     AIOADC_WRITE(0x42080034,0x00005011);
    //     AIOADC_WRITE(0x42080038,0x00000310);
    //     AIOADC_WRITE(0x4208003c,0x00000001);
    //     AIOADC_WRITE(0x42080040,0x00002510);
    //     break;
    case HAL_AIOADC_MODE_TEMP_SENSOR:
        AIOADC_WRITE(0x42080030,0x00000000);
        AIOADC_WRITE(0x42080034,0x00000000);
        AIOADC_WRITE(0x42080038,0x00000000);
        AIOADC_WRITE(0x4208003c,0x00000000);
        AIOADC_WRITE(0x42080040,0x00000000);
        break;     
    default:
        AIOADC_WRITE(0x42080030,0x00000113);
        AIOADC_WRITE(0x42080034,0x00005010);
        AIOADC_WRITE(0x42080038,0x00000330);
        AIOADC_WRITE(0x4208003c,0x00000001);
        AIOADC_WRITE(0x42080040,0x00002410);
        break;
    }
}

static void pga_setting(void)
{
    AIOADC_WRITE(0x42080004,0x00000000);
    AIOADC_WRITE(0x42080004,0x00000002);
    AIOADC_WRITE(0x42080004,0x00000002);
    AIOADC_WRITE(0x42080004,0x00000042);
    AIOADC_WRITE(0x42080004,0x00000000);
    AIOADC_WRITE(0x42080004,0x00000001);

    AIOADC_WRITE(0x4208000c,0x00000010);
    AIOADC_WRITE(0x42080010,0x0000f000);
}

static void aioadc_setting(void)
{
    AIOADC_WRITE(0x4208000c,0x00000010);
    AIOADC_WRITE(0x4208000c,0x00000010);
    AIOADC_WRITE(0x4208000c,0x00000010);

    AIOADC_WRITE(0x4208001c,0x00000001);
    AIOADC_WRITE(0x4208000c,0x00000010);
    AIOADC_WRITE(0x42080018,0x00000015);
    AIOADC_WRITE(0x4208001c,0x00000001);
    AIOADC_WRITE(0x42080004,0x00001001);

    AIOADC_WRITE(0x42080004,0x00005009);
}

static void aioadc_dig_setting(hal_aioadc_ch_en_t aioadc_ch,hal_aioadc_config_t *aioadc_cfg)
{
    /*aio adc ch setting*/
    AIOADC->AIO_ADC_CON4_UNION.AIO_ADC_CON4_CELLS.aio_clk_dig_en = 1;

    uint32_t ch_en_mask = aioadc_get_ch_mask(aioadc_ch);
    AIOADC->AIO_ADC_CON1 = ch_en_mask;

    AIOADC->AIO_ADC_CON0_UNION.AIO_ADC_CON0_CELLS.aio_adc_avg_sel = aioadc_cfg->adc_avg_sel;
    AIOADC->AIO_ADC_CON0_UNION.AIO_ADC_CON0_CELLS.aio_adc_avg_shift_sel = aioadc_cfg->adc_avg_shift_sel;
    AIOADC->AIO_ADC_CON0_UNION.AIO_ADC_CON0_CELLS.aio_adc_rst_dly = aioadc_cfg->adc_rst_dly;
    AIOADC->AIO_ADC_CON0_UNION.AIO_ADC_CON0_CELLS.aio_adc_sw_ch_dly = aioadc_cfg->adc_sw_ch_dly;

    /*aio adc mode setting*/
    AIOADC_WRITE(0x42080030,0x00001911);
    AIOADC_WRITE(0x42080034,0x00005010);
    AIOADC_WRITE(0x42080038,0x00000350);
    AIOADC_WRITE(0x4208003c,0x00000001);
    AIOADC_WRITE(0x42080040,0x00000410);
}

static void aioadc_auenc_con_setting(void)
{
    /*pga atst off-check*/
    AIOADC_WRITE(0x42080008,0x00000001);
    AIOADC_WRITE(0x42080018,0x00000029);
    AIOADC_WRITE(0x42080010,0x0000f200);
    AIOADC_WRITE(0x4208000c,0x00001410);
    AIOADC_WRITE(0x42080004,0x00005001);
}

static void OTP_check_aio_adc_trim_value(uint32_t otp_address, uint32_t *out_gain, uint32_t *out_offset)
{
    uint8_t data[5];
    uint32_t temp_value, flag, gain, offset;
    hal_flash_otp_read(otp_address, data, 5);
    flag = data[0];
    temp_value = (uint32_t)(data[1] << 24) | (data[2] << 16) | (data[3] << 8) | (data[4]);
    gain = (temp_value & 0xFFFF);
    offset = ((temp_value & 0xFFFF0000) >> 16);
    printk("aio_adc_address%d flag= 0x%x  ,gain= 0x%x, offset= 0x%x\r\n", otp_address, flag, gain, offset);
    *out_gain = gain;
    *out_offset = offset;
}

void aioadc_reg_check()
{
    printk("AIOADC==%x\r\n", (uint32_t)(AIOADC_REGISTER_T *)(AIOADC));
    printk("AIO_ADC_EN_UNION==%x\r\n",(uint32_t)( &(AIOADC->AIO_ADC_EN_UNION)));
    printk("AIO_ADC_CON0_UNION==%x\r\n", (uint32_t)&(AIOADC->AIO_ADC_CON0_UNION));
    printk("AIO_ADC_CON1==%x\r\n", (uint32_t)&(AIOADC->AIO_ADC_CON1));
    printk("AIO_ADC_CON2==%x\r\n", (uint32_t)&(AIOADC->AIO_ADC_CON2));
    printk("AIO_ADC_CON3==%x\r\n", (uint32_t)&(AIOADC->AIO_ADC_CON3));
    printk("AIO_ADC_CON4_UNION==%x\r\n", (uint32_t)&(AIOADC->AIO_ADC_CON4_UNION));
    printk("AIO_ADC_CON5==%x\r\n", (uint32_t)&(AIOADC->AIO_ADC_CON5));
    printk("AIO_ADC_DEBUG_UNION==%x\r\n", (uint32_t)&(AIOADC->AIO_ADC_DEBUG_UNION));
    printk("AIO_ADC_CON6_UNION==%x\r\n", (uint32_t)&(AIOADC->AIO_ADC_CON6_UNION));
    printk("AIO_ADC_MAN0_UNION==%x\r\n", (uint32_t)&(AIOADC->AIO_ADC_MAN0_UNION));
    printk("AIO_ADC_MAN1==%x\r\n", (uint32_t)&(AIOADC->AIO_ADC_MAN1));
    printk("AIO_ADC_MAN_SEL_UNION==%x\r\n", (uint32_t)&(AIOADC->AIO_ADC_MAN_SEL_UNION));
}


#include "hal_gpio.h"
int16_t hal_aioadc_read_data_polling(hal_aioadc_ch_en_t aioadc_ch)
{
    // aioadc_reg_check();
    /*set pulse*/
    AIOADC->AIO_ADC_EN_UNION.AIO_ADC_EN_CELLS.aio_adc_en_pluse = 1;

    uint8_t aio_adc_busy = 0xff;
    aio_adc_busy = AIOADC->AIO_ADC_EN_UNION.AIO_ADC_EN_CELLS.aio_adc_busy;


    while ((aio_adc_busy))
    {
        aio_adc_busy = AIOADC->AIO_ADC_EN_UNION.AIO_ADC_EN_CELLS.aio_adc_busy;
    };

    int16_t aio_data = 0;
    uint32_t aioadc_ch_data_reg_mask = aioadc_get_ch_data_reg_mask(aioadc_ch);
    aio_data = (*(volatile uint32_t *)(aioadc_ch_data_reg_mask)&0xffff);
    printk("aio_adc_data(%x): %d\n", aioadc_ch_data_reg_mask, aio_data);
    return aio_data;
}

hal_aioadc_callback_t g_callabck;
hal_aioadc_ch_en_t g_callabck_ch;
hal_aioadc_mode_sel_t g_aioadc_mode;
void aio_adc_Isr(void)
{
    AIOADC->AIO_ADC_CON3 = 1;//clear irq 

    uint32_t gain = 0;
    uint32_t offset = 0;
    int16_t aio_data = 0;
    int32_t v_bat = 0xffffffff;

    uint32_t aioadc_ch_data_reg_mask = aioadc_get_ch_data_reg_mask(g_callabck_ch);
    aio_data = (*(volatile uint32_t *)(aioadc_ch_data_reg_mask)&0xffff);

    uint32_t aioadc_trim_data_adress = aioadc_get_trim_data_adress(g_aioadc_mode);
    OTP_check_aio_adc_trim_value(aioadc_trim_data_adress, &gain, &offset);
    gain = (int16_t)(gain);
    offset = (int16_t)(offset);
    int16_t temp_data = (aio_data - offset);
    if ((temp_data & 0x8000))
    {
        v_bat = 0;
    }
    else
    {
        v_bat = ((((int32_t)(temp_data)) * 1000) / gain);
    }

    if(g_callabck != NULL)
    {
        g_callabck(aio_data,v_bat);
    }
}

hal_aioadc_status_t hal_aioadc_read_data_by_irq(hal_aioadc_ch_en_t aioadc_ch,hal_aioadc_callback_t callback)
{
    aioadc_reg_check();
    hal_nvic_status_t nvic_status;
    /*register calllback ISR*/
    g_callabck = callback;
    g_callabck_ch = aioadc_ch;

    nvic_status = hal_nvic_register_isr_handler(AIO_IRQn, (void *)aio_adc_Isr);
    if (nvic_status != HAL_NVIC_STATUS_OK)
    {
        return HAL_AIOADC_STATUS_ERROR;
    }
    hal_nvic_enable_irq(AIO_IRQn);
    AIOADC->AIO_ADC_CON2 = 1;//enbale irq
    /*set pulse*/
    AIOADC->AIO_ADC_EN_UNION.AIO_ADC_EN_CELLS.aio_adc_en_pluse = 1;
    return HAL_AIOADC_STATUS_OK;
}

static uint32_t aioadc_get_trim_data_adress(hal_aioadc_mode_sel_t aioadc_mode)
{
    uint32_t aioadc_trim_data_adress = 0;
    switch (aioadc_mode)
    { /*se mode*/
    case HAL_AIOADC_MODE_SE_0:
        aioadc_trim_data_adress = 37;
        break;
    case HAL_AIOADC_MODE_SE_1:
        aioadc_trim_data_adress = 42;
        break;
    case HAL_AIOADC_MODE_SE_2:
        aioadc_trim_data_adress = 47;
        break;
    case HAL_AIOADC_MODE_SE_3:
        aioadc_trim_data_adress = 52;
        break;
    case HAL_AIOADC_MODE_SE_4:
        aioadc_trim_data_adress = 57;
        break;
    /*diff mode*/
    case HAL_AIOADC_MODE_DIFF_0:
        aioadc_trim_data_adress = 62;
        break;
    case HAL_AIOADC_MODE_DIFF_1:
        aioadc_trim_data_adress = 67;
        break;
    case HAL_AIOADC_MODE_DIFF_2:
        aioadc_trim_data_adress = 72;
        break;
    case HAL_AIOADC_MODE_DIFF_3:
        aioadc_trim_data_adress = 77;
        break;
    case HAL_AIOADC_MODE_DIFF_4:
        aioadc_trim_data_adress = 82;
        break;
    /*inter vbat mode*/
    case HAL_AIOADC_MODE_VBAT:
        aioadc_trim_data_adress = 37;
        break; 
    default:
        printk("aio_adc_mode error = %d\n", aioadc_mode);
        break;
    }
    return  aioadc_trim_data_adress;
}

int16_t hal_aioadc_get_voltage(hal_aioadc_ch_en_t aioadc_ch,hal_aioadc_mode_sel_t aioadc_mode)
{
    uint32_t gain = 0;
    uint32_t offset = 0;
    int16_t aio_data = 0;
    int32_t v_bat = 0xffffffff;

    aio_data = hal_aioadc_read_data_polling(aioadc_ch);

    uint32_t aioadc_trim_data_adress = aioadc_get_trim_data_adress(aioadc_mode);
    OTP_check_aio_adc_trim_value(aioadc_trim_data_adress, &gain, &offset);
    gain = (int16_t)(gain);
    offset = (int16_t)(offset);
    printk("aio_adc gain: %d\n", gain);
    printk("aio_adc offset: %d\n", offset);

    int16_t temp_data = (aio_data - offset);
    if ((temp_data & 0x8000))
    {
        v_bat = 0;
    }
    else
    {
        v_bat = ((((int32_t)(temp_data)) * 1000) / gain);
    }

    switch(aioadc_mode)
    {
        case HAL_AIOADC_MODE_DIFF_0:
            v_bat = v_bat-1800;
            break;
        case HAL_AIOADC_MODE_DIFF_1:
            v_bat = v_bat-900;
            break;
        case HAL_AIOADC_MODE_DIFF_2:
            v_bat = v_bat-450;
            break;
        case HAL_AIOADC_MODE_DIFF_3:
            v_bat = v_bat-300;
            break;
        case HAL_AIOADC_MODE_DIFF_4:
            v_bat = v_bat-225;
            break;
        default:
            break;
    }
    printk("aio_adc v_bat: %d\n", v_bat);
    return v_bat;
}

static hal_aioadc_status_t hal_aioadc_para_check(hal_aioadc_ch_en_t aioadc_ch,hal_aioadc_mode_sel_t aioadc_mode)
{
    if(aioadc_ch >= HAL_AIOADC_CH_MAX)
    {
        return HAL_AIOADC_STATUS_ERROR_PARAMETER;
    }

    if(aioadc_mode >= HAL_AIOADC_MODE_MAX)
    {
        return HAL_AIOADC_STATUS_ERROR_PARAMETER;
    }

    if(aioadc_mode == HAL_AIOADC_MODE_VBAT||
    // aioadc_mode == HAL_AIOADC_MODE_RFCAL||
    // aioadc_mode == HAL_AIOADC_MODE_PMU_ATST||
    aioadc_mode == HAL_AIOADC_MODE_TEMP_SENSOR
    ){
        if(aioadc_ch != HAL_AIOADC_CH_0)
        {
            return HAL_AIOADC_STATUS_ERROR_PARAMETER;
        }
    }

    if(aioadc_mode == HAL_AIOADC_MODE_DIFF_0||
    aioadc_mode == HAL_AIOADC_MODE_DIFF_1||
    aioadc_mode == HAL_AIOADC_MODE_DIFF_2||
    aioadc_mode == HAL_AIOADC_MODE_DIFF_3||
    aioadc_mode == HAL_AIOADC_MODE_DIFF_3
    )
    {
        if((aioadc_ch != HAL_AIOADC_CH_1)&&(aioadc_ch == HAL_AIOADC_CH_3))
        {
            return HAL_AIOADC_STATUS_ERROR_PARAMETER;
        }
    }

    return HAL_AIOADC_STATUS_OK;
}


hal_aioadc_status_t aioadc_init(hal_aioadc_ch_en_t aioadc_ch,hal_aioadc_mode_sel_t aioadc_mode,hal_aioadc_config_t *aioadc_cfg)
{   
    hal_aioadc_status_t ret;
    ret = hal_aioadc_para_check(aioadc_ch,aioadc_mode);
    if(ret!= HAL_AIOADC_STATUS_OK)
    {
        return HAL_AIOADC_STATUS_ERROR_PARAMETER;
    }

    if(aioadc_mode == HAL_AIOADC_MODE_TEMP_SENSOR)
    {
        hal_tmepsensor_init();
    }
    else{
        // aioadc_off_seq();
        digital_top();
        abb_poweron(aioadc_mode);
        aio_setting(aioadc_mode);
        pga_setting();
        aioadc_setting();
        aioadc_dig_setting(aioadc_ch,aioadc_cfg);
        aioadc_auenc_con_setting();
        aioadc_mode_sel(aioadc_ch,aioadc_mode);
    }
    
    hal_gpt_delay_ms(1);
    return HAL_AIOADC_STATUS_OK;
}

hal_aioadc_status_t hal_aioadc_init(hal_aioadc_ch_en_t aioadc_ch,hal_aioadc_mode_sel_t aioadc_mode,hal_aioadc_config_t *aioadc_cfg)
{
    hal_aioadc_status_t ret;
    if(aioadc_cfg == NULL)
    {
        hal_aioadc_config_t dealut_aioadc_cfg={
            .adc_avg_sel = HAL_AIOADC_AVG_8192T,
            .adc_avg_shift_sel = HAL_AIOADC_AVG_SHIFT_1_16,
            .adc_rst_dly = HAL_AIOADC_RST_DLY_256T,
            .adc_sw_ch_dly = HAL_AIOADC_SW_CH_DLY_16T,
        };
        ret = aioadc_init(aioadc_ch,aioadc_mode,&dealut_aioadc_cfg);
    }else{
        ret = aioadc_init(aioadc_ch,aioadc_mode,aioadc_cfg);
    }

    if(ret != HAL_AIOADC_STATUS_OK)
    {
        return HAL_AIOADC_STATUS_ERROR_PARAMETER;
    }
    return HAL_AIOADC_STATUS_OK;
}

void hal_aioadc_deinit(void)
{
    aioadc_off_seq();
    /*close aio clock cg*/
    if (hal_clock_is_enabled(aio_clock_cg) == true) {
        if (HAL_CLOCK_STATUS_OK != hal_clock_disable(aio_clock_cg)) {
            printk("aio_clock_cg disable failed!\r\n");
        }
    }
}


hal_aioadc_status_t hal_tmepsensor_init(void)
{
    // aioadc_off_seq();
    digital_top();
    abb_poweron(HAL_AIOADC_MODE_TEMP_SENSOR);

    /*aio setting*/
    aio_setting(HAL_AIOADC_MODE_TEMP_SENSOR);

    /*fga setting*/
    AIOADC_WRITE(0x42080004,0x00000000);
    AIOADC_WRITE(0x42080004,0x00000001);
    AIOADC_WRITE(0x4208000c,0x00000010);
    AIOADC_WRITE(0x42080010,0x0000F000);

    /*ADC setting*/
    AIOADC_WRITE(0x4208000c,0x00000010);
    AIOADC_WRITE(0x4208000c,0x00000010);
    AIOADC_WRITE(0x4208000c,0x00000010);

    AIOADC_WRITE(0x4208001c,0x00000001);
    AIOADC_WRITE(0x4208000c,0x00000010);
    AIOADC_WRITE(0x42080018,0x00000015);
    AIOADC_WRITE(0x4208001c,0x00000001);

    AIOADC_WRITE(0x42080008,0x00000001);//change
    AIOADC_WRITE(0x42080018,0x00000029);//change
    AIOADC_WRITE(0x42080010,0x00000200);//change

    /*temp sensor on*/
    AIOADC_WRITE(0x4208003c,0x00000000);
    AIOADC_WRITE(0x42080040,0x00000011);
    AIOADC_WRITE(0x42080004,0x00005001);
    hal_gpt_delay_ms(1);
    AIOADC_WRITE(0x42080054,0x00002201);

    AIOADC_WRITE(0x40070094,0x00000001);
    AIOADC_WRITE(0x40070088,0x00000001);
    AIOADC_WRITE(0x40070084,0x050F0F0E);

    // hal_gpt_delay_ms(1);

    return HAL_AIOADC_STATUS_OK;
}

static void OTP_check_aio_adc_tempsensor_trim_value(uint32_t otp_address, int16_t *out_offset)
{
    uint8_t data[5];
    int16_t flag,offset;
    hal_flash_otp_read(otp_address, data, 5);
    flag = data[0];
    offset = (int16_t) ((data[2] << 8) | (data[3] << 0) );
    // printk("tempsensor :aio_adc_address%d ,flag = 0x%x,offset = 0x%x\r\n", otp_address, flag, offset);
    *out_offset = offset;
}

hal_aioadc_status_t hal_aioadc_get_tempsensor(hal_aioadc_ch_en_t aioadc_ch,int16_t *output_adc_data,int16_t *output_opt_offset,int16_t *output_temp_data)
{
    int16_t offset = 0;
    int16_t aio_data = 0;

    aio_data = hal_aioadc_read_data_polling(aioadc_ch);
    *output_adc_data = aio_data;

    /*otp get data*/
    uint32_t aioadc_trim_data_adress = 102;
    OTP_check_aio_adc_tempsensor_trim_value(aioadc_trim_data_adress, &offset);
    *output_opt_offset = offset;
    // printk("tempsensor->aio_adc offset: %d\n", offset);
    aio_data = aio_data + (-550 - offset);
    int16_t tempsensor_data =(int16_t) (40 + ((int32_t)aio_data*100)/4466);
    *output_temp_data = tempsensor_data;
    // printk("tempsensor: %d \n", tempsensor_data);

    return HAL_AIOADC_STATUS_OK;
}


#endif /* HAL_AIOADC_MODULE_ENABLED */

