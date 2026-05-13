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

#ifdef HAL_COMPARATOR_MODULE_ENABLED
#include "hal_comparator.h"

#include "hal_eint.h"
#include "hal_eint_internal.h"

#include "hal_gpt.h"
#include "hal_gpt_internal.h"

#include "hal_gpio.h"
#include "hal_gpio_internal.h"

static const uint32_t internal_ref_cfg_value[HAL_COMPARATOR_INT_REFF_MAX] = {
    0x01130007,//INT_REFF_ON_CP1_1_2_CP2_1_2
    0x01130017,//INT_REFF_ON_CP1_1_8_CP2_1_2
    0x01130027,//INT_REFF_ON_CP1_2_4_CP2_1_2
    0x01130037,//INT_REFF_ON_CP1_VDD_CP2_1_2
    0x01130047,//INT_REFF_ON_CP1_1_2_CP2_1_8
    0x01130057,//INT_REFF_ON_CP1_1_8_CP2_1_8
    0x01130067,//INT_REFF_ON_CP1_2_4_CP2_1_8
    0x01130077,//INT_REFF_ON_CP1_VDD_CP2_1_8
    0x01130087,//INT_REFF_ON_CP1_1_2_CP2_2_4
    0x01130097,//INT_REFF_ON_CP1_1_8_CP2_2_4
    0x011300a7,//INT_REFF_ON_CP1_2_4_CP2_2_4
    0x011300b7,//INT_REFF_ON_CP1_VDD_CP2_2_4
    0x011300c7,//INT_REFF_ON_CP1_1_2_CP2_VDD
    0x011300d7,//INT_REFF_ON_CP1_1_8_CP2_VDD
    0x011300e7,//INT_REFF_ON_CP1_2_4_CP2_VDD
    0x011300f7 //INT_REFF_ON_CP1_VDD_CP2_VDD
};

static const uint32_t comp_1_mode_cfg_value[HAL_COMP_MODE_MAX] = {
    0x01153003,//HAL_COMP_SE_MODE_REF_ON_LS_MODE
    0x01153203,//HAL_COMP_SE_MODE_REF_ON_NM_MODE
    0x01153603,//HAL_COMP_SE_MODE_REF_ON_HS_MODE
    0x01153001,//HAL_COMP_SE_MODE_REF_OFF_LS_MODE
    0x01153201,//HAL_COMP_SE_MODE_REF_OFF_NM_MODE
    0x01153601,//HAL_COMP_SE_MODE_REF_OFF_HS_MODE
    0x01151003,//HAL_COMP_DIFF_MODE_REF_ON_LS_MODE
    0x01151203,//HAL_COMP_DIFF_MODE_REF_ON_NM_MODE
    0x01151603,//HAL_COMP_DIFF_MODE_REF_ON_HS_MODE
    0x01151001,//HAL_COMP_DIFF_MODE_REF_OFF_LS_MODE
    0x01151201,//HAL_COMP_DIFF_MODE_REF_OFF_NM_MODE
    0x01151601,//HAL_COMP_DIFF_MODE_REF_OFF_HS_MODE
};

static const uint32_t comp_2_mode_cfg_value[HAL_COMP_MODE_MAX] = {
    0x00001003,//HAL_COMP_SE_MODE_REF_ON_LS_MODE
    0x00001203,//HAL_COMP_SE_MODE_REF_ON_NM_MODE
    0x00001603,//HAL_COMP_SE_MODE_REF_ON_HS_MODE
    0x00001001,//HAL_COMP_SE_MODE_REF_OFF_LS_MODE
    0x00001201,//HAL_COMP_SE_MODE_REF_OFF_NM_MODE
    0x00001601,//HAL_COMP_SE_MODE_REF_OFF_HS_MODE

    0x00001003,//HAL_COMP_DIFF_MODE_REF_ON_LS_MODE
    0x00001203,//HAL_COMP_DIFF_MODE_REF_ON_NM_MODE
    0x00001603,//HAL_COMP_DIFF_MODE_REF_ON_HS_MODE
    0x00001001,//HAL_COMP_DIFF_MODE_REF_OFF_LS_MODE
    0x00001201,//HAL_COMP_DIFF_MODE_REF_OFF_NM_MODE
    0x00001601,//HAL_COMP_DIFF_MODE_REF_OFF_HS_MODE
};

hal_comparator_callback_t g_comp1_callabck;
hal_comparator_callback_t g_comp2_callabck;
hal_comparator_callback_t g_comp_lp_callabck;
// static bool trim_flag = false;

void hal_comparator_analog_power_on(void)
{
    /*power on default*/
    COMP_WRITE(COMP_REF_REG,0x01120953);
}

void hal_comparator_analog_power_off(void)
{
    /*power off default*/
    COMP_WRITE(COMP_REF_REG,0x01120000);
}

void hal_comparator_analog_reset(void)
{
    /*disable V2l*/
    COMP_WRITE(COMP_REF_REG,0x01130000);
    /*disable and rst cp1*/
    COMP_WRITE(COMP1_REG,0x01150000);
    /*rst cp1 setting*/
    COMP_WRITE(COMP1_REG,0x01160000);
    /*rst cp1 setting*/
    COMP_WRITE(COMP1_REG,0x01170000);
    /*rst cp1 setting*/
    COMP_WRITE(COMP1_REG,0x01180000);

    /*disable and rst cp1*/
    COMP_WRITE(COMP2_REG,0x00000000);
    /*rst cp1 setting*/
    COMP_WRITE((COMP2_REG+0x4),0x00000000);
    /*rst cp1 setting*/
    COMP_WRITE((COMP2_REG+0x8),0x00000000);
    /*rst cp1 setting*/
    COMP_WRITE((COMP2_REG+0xc),0x00000000);
}

void hal_comparator_analog_int_ref_on(hal_comparator_inter_ref_cfg_t internal_ref_cfg)
{
    /*cmp1&cmp2 ref setting*/
    uint32_t ref_val = internal_ref_cfg_value[internal_ref_cfg];
    COMP_WRITE(COMP_REF_REG,(ref_val));
}

uint32_t g_comp1_mode_reg_value = 0;
void hal_comparator_analog_comp1_init(hal_comparator_cfg_t *comp_cfg)
{
    /*enable ref on &&current setting*/
    uint32_t comp1_mode_value = comp_1_mode_cfg_value[comp_cfg->mode];
    COMP_WRITE(COMP1_REG,(comp1_mode_value));
    g_comp1_mode_reg_value = comp1_mode_value;
    /*ref setting*/
    uint32_t input_gpio_mask = ((comp_cfg->input_gpio) <<(COMP1_ACTIVE_MODE_INPUT_GPIO_SEL_OFFSET));
    uint32_t ref_in_gpio_mask = ((comp_cfg->ref_in_gpio) <<(COMP1_ACTIVE_MODE_EXTERNAL_GPIO_SEL_OFFSET));
    uint32_t ref_sel_mask = ((comp_cfg->ref_sel) <<(COMP1_ACTIVE_MODE_COMP1_REF_SEL_OFFSET));
    uint32_t ladder_ref_sel_mask =((comp_cfg->ladder_ref_sel) <<(COMP1_ACTIVE_MODE_COMP1_REF_RLADDER_INPUT_SEL_OFFSET));

    /*lpcomp mode sel->set 0*/
    if((comp_cfg->mode)>HAL_COMP_SE_MODE_MAX)
    {
        uint32_t ref_in_mask = (0x01160070 | input_gpio_mask|ref_in_gpio_mask|ref_sel_mask|ladder_ref_sel_mask);
        COMP_WRITE(COMP1_REG,(ref_in_mask));

        uint8_t rladder_value = comp_cfg->vup_rladder_value;
        COMP_WRITE(COMP1_REG,(0x01170000));
        COMP_WRITE(COMP1_REG,(0x01180000 | ((rladder_value) << COMP1_ACTIVE_MODE_COMP1_RLADDER_VUP_SEL_OFFSET)));
    }else
    {
        uint32_t ref_in_mask = (0x01160000 | input_gpio_mask|ref_in_gpio_mask|ref_sel_mask|ladder_ref_sel_mask);
        COMP_WRITE(COMP1_REG,(ref_in_mask));
        /*VUP &&VDN setting*/
        uint8_t rladder_value_vup = comp_cfg->vup_rladder_value;
        uint8_t rladder_value_vdn = comp_cfg->vdn_rladder_value;
        COMP_WRITE(COMP1_REG,( (0x01170000) | ((rladder_value_vdn) << COMP1_ACTIVE_MODE_COMP1_RLADDER_VDN_SEL_OFFSET)));
        COMP_WRITE(COMP1_REG,(0x01180000 | ((rladder_value_vup) << COMP1_ACTIVE_MODE_COMP1_RLADDER_VUP_SEL_OFFSET)));
    }
}

hal_comparator_status_t comparator_para_check(hal_comparator_cfg_t *comp_cfg)
{
    if( ((comp_cfg->comp_port) >HAL_COMP_MAX)||
        ((comp_cfg->mode) >HAL_COMP_MODE_MAX)||
        ((comp_cfg->input_gpio) >HAL_GPIO_SEL_MAX)||
        ((comp_cfg->internal_ref_cfg) >HAL_COMPARATOR_INT_REFF_MAX))
    {
        return HAL_COMPARATOR_STATUS_INVALID_PARAMETER;
    }

    if( ((comp_cfg->vup_rladder_value) >0x3f)||
        ((comp_cfg->vdn_rladder_value) >0x3f))
    {
        return HAL_COMPARATOR_STATUS_INVALID_PARAMETER;
    }
    return HAL_COMPARATOR_STATUS_OK;
}
uint32_t g_comp2_mode_reg_value = 0;
void hal_comparator_analog_comp2_init(hal_comparator_cfg_t *comp_cfg)
{
    /*enable ref on && mode setting*/
    uint32_t comp2_mode_value = comp_2_mode_cfg_value[comp_cfg->mode];
    uint32_t ref_in_gpio_mask=((0x00003100) | ((comp_cfg->ref_in_gpio) <<(COMP2_ACTIVE_MODE_EXTERNAL_GPIO_SEL_OFFSET)));
    uint32_t input_gpio_mask = ((comp_cfg->input_gpio) <<(COMP2_ACTIVE_MODE_INPUT_GPIO_SEL_OFFSET));
    uint32_t ref_sel_mask = ((comp_cfg->ref_sel) <<(COMP2_ACTIVE_MODE_COMP2_REF_SEL_OFFSET));
    uint32_t ladder_ref_sel_mask =((comp_cfg->ladder_ref_sel) <<(COMP2_ACTIVE_MODE_COMP2_REF_LADDER_INPUT_SEL_OFFSET));
    uint32_t ref_in_mask = (input_gpio_mask | ref_sel_mask | ladder_ref_sel_mask);

    COMP_WRITE(COMP2_REG,comp2_mode_value);
    g_comp2_mode_reg_value = comp2_mode_value;

    if((comp_cfg->mode)>HAL_COMP_SE_MODE_MAX)
    {
        COMP_WRITE((COMP2_REG + 0x4),(ref_in_gpio_mask));
        /*ref_in_mask setting*/
        COMP_WRITE((COMP2_REG + 0x8),(ref_in_mask));
        /*ladder vup sel*/
        uint32_t vup_mask = ((comp_cfg -> vup_rladder_value) << COMP2_ACTIVE_MODE_COMP2_RLADDER_VUP_SEL_OFFSET);
        COMP_WRITE((COMP2_REG + 0xc),(vup_mask));
    }else
    {
        ref_in_gpio_mask = (0x00000001 | ((comp_cfg->ref_in_gpio) <<(COMP2_ACTIVE_MODE_EXTERNAL_GPIO_SEL_OFFSET)));
        COMP_WRITE((COMP2_REG + 0x4),(ref_in_gpio_mask));

        uint32_t ref_sel_mask = ((HAL_REF_V_SEL_RLADDER) <<(COMP2_ACTIVE_MODE_COMP2_REF_SEL_OFFSET));
        uint32_t ref_in_mask = (input_gpio_mask | ref_sel_mask | ladder_ref_sel_mask);
        COMP_WRITE((COMP2_REG + 0x8),(ref_in_mask));

        /*ladder vup/vdn sel*/
        uint32_t vup_mask = ((comp_cfg -> vup_rladder_value) << COMP2_ACTIVE_MODE_COMP2_RLADDER_VUP_SEL_OFFSET);
        uint32_t vdn_mask = ((comp_cfg -> vdn_rladder_value) << COMP2_ACTIVE_MODE_COMP2_RLADDER_VDN_SEL_OFFSET);
        COMP_WRITE((COMP2_REG + 0xc),(vup_mask | vdn_mask));
    }
}

hal_comparator_status_t hal_comparator_comp2_init(hal_comparator_cfg_t *comp_cfg, hal_comparator_callback_t comp2_callback)
{
    hal_comparator_analog_power_on();
    hal_comparator_analog_int_ref_on(comp_cfg->internal_ref_cfg);
    hal_comparator_analog_comp2_init(comp_cfg);
    return HAL_COMPARATOR_STATUS_OK;
}

hal_comparator_status_t hal_comparator_comp1_init(hal_comparator_cfg_t *comp_cfg, hal_comparator_callback_t comp1_callback)
{
    hal_comparator_analog_power_on();
    hal_comparator_analog_int_ref_on(comp_cfg->internal_ref_cfg);
    hal_comparator_analog_comp1_init(comp_cfg);
    return HAL_COMPARATOR_STATUS_OK;
}

void hal_comparator_deinit()
{
    hal_comparator_analog_reset();
    hal_comparator_analog_power_off();
}

void hal_comp1_enable(void)
{
    uint32_t enable_value = (g_comp1_mode_reg_value | (1 << 0));
    COMP_WRITE(COMP1_REG,(enable_value));
}

void hal_comp1_disable()
{
    uint32_t disable_value = (g_comp1_mode_reg_value & (~(1 << 0)));
    COMP_WRITE(COMP1_REG,(disable_value));
}

void hal_comp2_enable(void)
{
    uint32_t enable_value = (g_comp2_mode_reg_value | (1 << 0));
    COMP_WRITE(COMP2_REG,enable_value);
}

void hal_comp2_disable()
{
    uint32_t disable_value = (g_comp2_mode_reg_value & (~(1 << 0)));
    COMP_WRITE(COMP2_REG,disable_value);
}


#endif /*HAL_COMPARATOR_MODULE_ENABLED*/
