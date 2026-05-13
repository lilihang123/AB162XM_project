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

// #ifdef HAL_COMP_WHEEL_MODULE_ENABLED
#include "comp_wheel.h"
#include "syslog.h"
#include "hal_gpio.h"

log_create_module(comp_wheel, PRINT_LEVEL_INFO);
static volatile risvc_comp_wheel_info_t comp_wheel_encoder;
static uint8_t current_state;
static uint8_t last_current_state;
static uint8_t g_comp1_vup_rladder_value;
static uint8_t g_comp1_vdn_rladder_value;
static uint8_t g_comp2_vup_rladder_value;
static uint8_t g_comp2_vdn_rladder_value;
static uint8_t g_last_pina_state;
static uint8_t g_last_pinb_state;

static void comp_wheel_comp1_config(hal_comp_gpio_cfg_t gpio_pin,uint8_t vup,uint8_t vdn)
{
    hal_comparator_cfg_t comp_cfg={
        .comp_port = HAL_COMP_1,
        .mode = HAL_COMP_SE_MODE_REF_ON_NM_MODE,
        .input_gpio = gpio_pin,
        .ref_in_gpio = HAL_GPIO_SEL_NO,
        .internal_ref_cfg = HAL_COMPARATOR_INT_REFF_ON_CP1_VDD_CP2_VDD,
        .ref_sel = HAL_REF_V_SEL_RLADDER,
        .ladder_ref_sel = HAL_LADDER_REF_V_SEL_REF_ON_IN,
        .vup_rladder_value = vup,
        .vdn_rladder_value = vdn,
    };
    g_comp1_vup_rladder_value = vup;
    g_comp1_vdn_rladder_value = vdn;
    hal_comparator_analog_comp1_init(&comp_cfg);
}

static void comp_wheel_comp2_config(hal_comp_gpio_cfg_t gpio_pin,uint8_t vup,uint8_t vdn)
{
    hal_comparator_cfg_t comp_cfg={
        .comp_port = HAL_COMP_2,
        .mode = HAL_COMP_SE_MODE_REF_ON_NM_MODE,
        .input_gpio = gpio_pin,
        .ref_in_gpio = HAL_GPIO_SEL_NO,
        .internal_ref_cfg = HAL_COMPARATOR_INT_REFF_ON_CP1_VDD_CP2_VDD,
        .ref_sel = HAL_REF_V_SEL_RLADDER,
        .ladder_ref_sel = HAL_LADDER_REF_V_SEL_REF_ON_IN,
        .vup_rladder_value = vup,
        .vdn_rladder_value = vdn,
    };
    g_comp2_vup_rladder_value = vup;
    g_comp2_vdn_rladder_value = vdn;
    hal_comparator_analog_comp2_init(&comp_cfg);
}

static int32_t comp_wheel_encoder_update_position(uint8_t current_state)
{
    comp_wheel_encoder.pc_state <<= 2;
    comp_wheel_encoder.pc_state |= (current_state & 0x3);
    comp_wheel_encoder.pc_state &= 0xF;

    switch (comp_wheel_encoder.pc_state)
    {
    case 0xd:
    case 0x4:
    case 0x2:
    case 0xb:

    case 0xe:
    case 0x8:
    case 0x1:
    case 0x7:
        comp_wheel_encoder.dpc_state <<= 4;
        comp_wheel_encoder.dpc_state |= (comp_wheel_encoder.pc_state & 0xF);
        comp_wheel_encoder.dpc_state &= 0xFF;

        switch (comp_wheel_encoder.dpc_state)
        {
        case 0xe8:
        case 0x17:
                comp_wheel_encoder.relative_position++;
            break;
        case 0xd4:
        case 0x2b:
                comp_wheel_encoder.relative_position--;
            break;
        default:
            return -1;
        }
        break;
    default:
        return -2;
    }
    return 0;
}

static void comp_wheel_encoder_process_event(void)
{
    if(comp_wheel_encoder.relative_position == 0)
    {
        return;
    }

    if(comp_wheel_encoder.callback != NULL)
    {
        comp_wheel_encoder.callback(comp_wheel_encoder.relative_position);
        comp_wheel_encoder.relative_position = 0;
    }
}

void comp_set_pmu_strup_rg(uint8_t bank, uint16_t data)
{
    *((volatile unsigned int *)(0x42108008)) = 0x01000000 | data | bank << 16;
}

uint16_t comp_get_pmu_strup_rg(uint8_t bank)
{
    uint16_t data = 0;
    *((volatile unsigned int *)(0x42108008)) = 0x00000000 | bank << 16;
    data = *((volatile unsigned short *)(0x4210800C));
    return data;
}

static void comp_wheel_init_imp(hal_comp_gpio_cfg_t up_pin,hal_comp_gpio_cfg_t down_pin)
{
    hal_comparator_analog_power_on();
    hal_comparator_analog_int_ref_on(HAL_COMPARATOR_INT_REFF_ON_CP1_VDD_CP2_VDD);
    comp_wheel_comp1_config(up_pin,48,16);
    comp_wheel_comp2_config(down_pin,48,16);

    /*close pmu comp irq*/
    comp_set_pmu_strup_rg(33, 0x3); // clear comp irq
}

static void comp_wheel_get_pin_value()
{
    /*get comp1 output status*/
    uint8_t pina_state;
    pina_state = (uint8_t)((comp_get_pmu_strup_rg(0x3B) >> (10)) & (0x01));
    comp_wheel_encoder.pina_state = pina_state;

    if(pina_state != g_last_pina_state)
    {
        if(pina_state == 0)
        {
            COMP_WRITE(COMP1_REG,( (0x01170000) | ((g_comp1_vup_rladder_value) << COMP1_ACTIVE_MODE_COMP1_RLADDER_VDN_SEL_OFFSET)));
        }else
        {
            COMP_WRITE(COMP1_REG,( (0x01170000) | ((g_comp1_vdn_rladder_value) << COMP1_ACTIVE_MODE_COMP1_RLADDER_VDN_SEL_OFFSET)));
        }
    }
    g_last_pina_state = pina_state;

    /*get comp2 output status*/
    uint8_t pinb_state;
    pinb_state  = (uint8_t)((*(volatile uint32_t *)(0x42140314)>>(22))&(0x1));
    if(pinb_state == 0x1)
    {
        comp_wheel_encoder.pinb_state = 0x0;
    }else{
        comp_wheel_encoder.pinb_state = 0x1;
    }

    if(pinb_state != g_last_pinb_state)
    {
        uint32_t vup_mask ;
        uint32_t vdn_mask;
        vup_mask = ((g_comp2_vup_rladder_value) << COMP2_ACTIVE_MODE_COMP2_RLADDER_VUP_SEL_OFFSET);
        if(pinb_state == 0)
        {
            vdn_mask = ((g_comp2_vdn_rladder_value) << COMP2_ACTIVE_MODE_COMP2_RLADDER_VDN_SEL_OFFSET);
        }else
        {
            vdn_mask = ((g_comp2_vup_rladder_value) << COMP2_ACTIVE_MODE_COMP2_RLADDER_VDN_SEL_OFFSET);
        }
        //note comp2-enit output is converse
        COMP_WRITE(COMP2_REG + 0xc,( (vup_mask | vdn_mask)));
    }
    g_last_pinb_state = pinb_state;
    current_state = (((comp_wheel_encoder.pinb_state << 1) | comp_wheel_encoder.pina_state));
    if(current_state != last_current_state)
    {
        comp_wheel_encoder_update_position(current_state);
    }
    last_current_state = current_state ;
}

static void comp_wheel_enable()
{
    /*comp1 disable*/
    hal_comp1_enable();
    hal_comp2_enable();
}

static void comp_wheel_disable()
{
    /*comp1 disable*/
    hal_comp1_disable();
    hal_comp2_disable();
}

static void comp_wheel_encoder_imp(void)
{
    comp_wheel_encoder_process_event();
}

void comp_wheel_scan_once(uint16_t delay_us)
{
    hal_gpio_set_output(comp_wheel_encoder.pin_led,HAL_GPIO_DATA_HIGH);
    comp_wheel_enable();
    hal_gpt_delay_us(delay_us);
    comp_wheel_get_pin_value();
    hal_gpio_set_output(comp_wheel_encoder.pin_led,HAL_GPIO_DATA_LOW);
    comp_wheel_encoder_imp();
    comp_wheel_disable();
}

riscv_comp_wheel_status_t comp_wheel_init(riscv_comp_wheel_config_t *config , riscv_comp_wheel_callback_t callback)
{
    if((config->pin_led) > HAL_GPIO_MAX)
    {
        return COMP_WHEEL_STATUS_ERROR_INVALID_PARAMETER;
    }

    if((config->up_pin) > HAL_GPIO_SEL_MAX)
    {
        return COMP_WHEEL_STATUS_ERROR_INVALID_PARAMETER;
    }

    if((config->down_pin) > HAL_GPIO_SEL_MAX)
    {
        return COMP_WHEEL_STATUS_ERROR_INVALID_PARAMETER;
    }

    comp_wheel_encoder.pin_led = config->pin_led;
    comp_wheel_encoder.pina = config->up_pin;
    comp_wheel_encoder.pinb = config->down_pin;
    comp_wheel_encoder.callback = callback;

    comp_wheel_init_imp(comp_wheel_encoder.pina,comp_wheel_encoder.pinb);
    return COMP_WHEEL_STATUS_OK;
}

void comp_wheel_deinit(void)
{
    hal_comparator_deinit();
}

// #endif/*HAL_COMP_WHEEL_MODULE_ENABLED*/