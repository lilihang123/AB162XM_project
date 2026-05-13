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
#include "hal_pmu.h"

#include "hal_eint.h"
#include "hal_eint_internal.h"

#include "hal_gpt.h"
#include "hal_gpt_internal.h"

#include "hal_gpio.h"
#include "hal_gpio_internal.h"

#include "hal_flash_opt.h"
#include "hal_flash_disk_internal.h"

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
uint32_t g_comp1_mode_reg_value = 0;
uint32_t g_comp2_mode_reg_value = 0;

void hal_comparator_analog_power_on(void)
{
    /*power on default*/
    COMP_WRITE(COMP_REF_REG,0x01120953);
    //printk("COMP_WRITE(COMP_REF_REG,0x01120953)");
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

void OTP_check_comp_trim(uint32_t otp_address, uint32_t *data_trim)
{
    uint8_t data[5];
    hal_flash_otp_read(otp_address, data, 5);
    // uint8_t flag = data[0];
    // uint8_t trim_en = data[1];
    uint8_t data_12 = data[2];
    uint8_t data_18 = data[3];
    uint8_t data_24 = data[4];
    *data_trim = ((data_12 << 4) | (data_18 << 8) | (data_24 << 12));
    //printk("flag = %x,trim_en = %x,trim_data_1_2 = %x,trim_data_1_8 = %x,trim_data_2_4 = %x,trim_data_trim = %x", flag, trim_en, data_12, data_18, data_24, *data_trim);
}

void hal_comparator_analog_int_ref_on(hal_comparator_inter_ref_cfg_t internal_ref_cfg)
{
    /*cmp1&cmp2 ref setting*/
    uint32_t ref_val = internal_ref_cfg_value[internal_ref_cfg];
    COMP_WRITE(COMP_REF_REG,(ref_val));
    //printk("hal_comparator_analog_int_ref_on  *(volatile uint32_t *)(%08X) =0x%08X",COMP_REF_REG, ref_val);
}

void hal_comparator_analog_comp1_init(hal_comparator_cfg_t *comp_cfg)
{
    /*enable ref on &&current setting*/
    uint32_t comp1_mode_value = comp_1_mode_cfg_value[comp_cfg->mode];
    COMP_WRITE(COMP1_REG,(comp1_mode_value));
    // printk("hal_comparator_analog_comp1_init  --*(volatile uint32_t *)(%08X)=0x%08X", COMP1_REG,(comp1_mode_value));
    g_comp1_mode_reg_value = comp1_mode_value;
    /*ref setting*/
    uint32_t input_gpio_mask = ((comp_cfg->input_gpio) <<(COMP1_ACTIVE_MODE_INPUT_GPIO_SEL_OFFSET));
    uint32_t ref_in_gpio_mask = ((comp_cfg->ref_in_gpio) <<(COMP1_ACTIVE_MODE_EXTERNAL_GPIO_SEL_OFFSET));
    uint32_t ref_sel_mask = ((comp_cfg->ref_sel) <<(COMP1_ACTIVE_MODE_COMP1_REF_SEL_OFFSET));
    uint32_t ladder_ref_sel_mask =((comp_cfg->ladder_ref_sel) <<(COMP1_ACTIVE_MODE_COMP1_REF_RLADDER_INPUT_SEL_OFFSET));


    // printk("hal_comparator_analog_comp1_init  --input_gpio_mask=0x%08X", input_gpio_mask);
    // printk("hal_comparator_analog_comp1_init  --ref_in_gpio_mask=0x%08X", ref_in_gpio_mask);
    // printk("hal_comparator_analog_comp1_init  --ref_sel_mask=0x%08X", ref_sel_mask);
    // printk("hal_comparator_analog_comp1_init  --ladder_ref_sel_mask=0x%08X", ladder_ref_sel_mask);

    /*lpcomp mode sel->set 0*/
    if((comp_cfg->mode)>HAL_COMP_SE_MODE_MAX)
    {
        uint32_t ref_in_mask = (0x01160070 | input_gpio_mask|ref_in_gpio_mask|ref_sel_mask|ladder_ref_sel_mask);
        COMP_WRITE(COMP1_REG,(ref_in_mask));
        // printk("hal_comparator_analog_comp1_init  --*(volatile uint32_t *)(%08X)=0x%08X", COMP1_REG,(ref_in_mask));

        uint8_t rladder_value = comp_cfg->vup_rladder_value;
        // printk("hal_comparator_analog_comp1_init  --rladder_value=%d", rladder_value);
        COMP_WRITE(COMP1_REG,(0x01170000));
        // printk("hal_comparator_analog_comp1_init  --*(volatile uint32_t *)(%08X)=0x%08X", COMP1_REG,(0x01170000));
        COMP_WRITE(COMP1_REG,(0x01180000 | ((rladder_value) << COMP1_ACTIVE_MODE_COMP1_RLADDER_VUP_SEL_OFFSET)));
        // printk("hal_comparator_analog_comp1_init  --*(volatile uint32_t *)(%08X)=0x%08X", COMP1_REG,((0x01180000 | (rladder_value << COMP1_ACTIVE_MODE_COMP1_RLADDER_VUP_SEL_OFFSET))));
    }else
    {
        uint32_t ref_in_mask = (0x01160000 | input_gpio_mask|ref_in_gpio_mask|ref_sel_mask|ladder_ref_sel_mask);
        COMP_WRITE(COMP1_REG,(ref_in_mask));
        // printk("hal_comparator_analog_comp1_init  --*(volatile uint32_t *)(%08X)=0x%08X", COMP1_REG,(ref_in_mask));
        /*VUP &&VDN setting*/
        uint8_t rladder_value_vup = comp_cfg->vup_rladder_value;
        uint8_t rladder_value_vdn = comp_cfg->vdn_rladder_value;
        // printk("hal_comparator_analog_comp1_init  --rladder_value_vup=%d", rladder_value_vup);
        // printk("hal_comparator_analog_comp1_init  --rladder_value_vdn=%d", rladder_value_vdn);
        COMP_WRITE(COMP1_REG,( (0x01170000) | ((rladder_value_vdn) << COMP1_ACTIVE_MODE_COMP1_RLADDER_VDN_SEL_OFFSET)));
        // printk("hal_comparator_analog_comp1_init  --*(volatile uint32_t *)(%08X)=0x%08X", COMP1_REG,((0x01170000) | (rladder_value_vdn << COMP1_ACTIVE_MODE_COMP1_RLADDER_VDN_SEL_OFFSET)));
        COMP_WRITE(COMP1_REG,(0x01180000 | ((rladder_value_vup) << COMP1_ACTIVE_MODE_COMP1_RLADDER_VUP_SEL_OFFSET)));
        // printk("hal_comparator_analog_comp1_init  --*(volatile uint32_t *)(%08X)=0x%08X", COMP1_REG,((0x01180000 | (rladder_value_vup << COMP1_ACTIVE_MODE_COMP1_RLADDER_VUP_SEL_OFFSET))));
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

    if(comp_cfg->comp_port != HAL_COMP_LP)
    {
        if((comp_cfg->vup_rladder_value) >0x3f)
        {
            return HAL_COMPARATOR_STATUS_INVALID_PARAMETER;
        }
        if((comp_cfg->vdn_rladder_value) >0x3f)
        {
            return HAL_COMPARATOR_STATUS_INVALID_PARAMETER;
        }
    }else
    {
        if((comp_cfg->vup_rladder_value) >0xf)
        {
            return HAL_COMPARATOR_STATUS_INVALID_PARAMETER;
        }  
    }
    return HAL_COMPARATOR_STATUS_OK;
}

void hal_comparator_analog_comp2_init(hal_comparator_cfg_t *comp_cfg)
{
    /*enable ref on && mode setting*/
    uint32_t comp2_mode_value = comp_2_mode_cfg_value[comp_cfg->mode];
    uint32_t ref_in_gpio_mask=((0x00003100) | ((comp_cfg->ref_in_gpio) <<(COMP2_ACTIVE_MODE_EXTERNAL_GPIO_SEL_OFFSET)));
    uint32_t input_gpio_mask = ((comp_cfg->input_gpio) <<(COMP2_ACTIVE_MODE_INPUT_GPIO_SEL_OFFSET));
    uint32_t ref_sel_mask = ((comp_cfg->ref_sel) <<(COMP2_ACTIVE_MODE_COMP2_REF_SEL_OFFSET));
    uint32_t ladder_ref_sel_mask =((comp_cfg->ladder_ref_sel) <<(COMP2_ACTIVE_MODE_COMP2_REF_LADDER_INPUT_SEL_OFFSET));
    uint32_t ref_in_mask = (input_gpio_mask | ref_sel_mask | ladder_ref_sel_mask);

    //printk("comparator_analog_comp2_diff_mode_init  --comp2_mode_value=0x%08X", comp2_mode_value);
    //printk("comparator_analog_comp2_diff_mode_init  --ref_in_gpio_mask=0x%08X", ref_in_gpio_mask);
    //printk("comparator_analog_comp2_diff_mode_init  --input_gpio_mask=0x%08X", input_gpio_mask);
    //printk("comparator_analog_comp2_diff_mode_init  --ref_sel_mask=0x%08X", ref_sel_mask);
    //printk("comparator_analog_comp2_diff_mode_init  --ladder_ref_sel_mask=0x%08X", ladder_ref_sel_mask);
    //printk("comparator_analog_comp2_diff_mode_init  --ref_in_mask=0x%08X", ref_in_mask);   

    COMP_WRITE(COMP2_REG,comp2_mode_value);
    g_comp2_mode_reg_value = comp2_mode_value;
    //printk("comparator_analog_comp2_diff_mode_init  --%08X=0x%08X", COMP2_REG,comp2_mode_value); 

    if((comp_cfg->mode)>HAL_COMP_SE_MODE_MAX)
    {
        COMP_WRITE((COMP2_REG + 0x4),(ref_in_gpio_mask));
        //printk("comparator_analog_comp2_diff_mode_init  --%08X=0x%08X", (COMP2_REG + 0x4),ref_in_gpio_mask); 
        /*ref_in_mask setting*/
        COMP_WRITE((COMP2_REG + 0x8),(ref_in_mask));
        //printk("comparator_analog_comp2_diff_mode_init  --%08X=0x%08X", (COMP2_REG + 0x8),ref_in_mask);
        /*ladder vup sel*/
        uint32_t vup_mask = ((comp_cfg -> vup_rladder_value) << COMP2_ACTIVE_MODE_COMP2_RLADDER_VUP_SEL_OFFSET);
        COMP_WRITE((COMP2_REG + 0xc),(vup_mask));
        //printk("comparator_analog_comp2_diff_mode_init  --%08X=0x%08X", (COMP2_REG + 0xc),vup_mask);
    }else
    {
        ref_in_gpio_mask = (0x00000001 | ((comp_cfg->ref_in_gpio) <<(COMP2_ACTIVE_MODE_EXTERNAL_GPIO_SEL_OFFSET)));
        COMP_WRITE((COMP2_REG + 0x4),(ref_in_gpio_mask));
        //printk("comparator_analog_comp2_diff_mode_init  --%08X=0x%08X", (COMP2_REG + 0x4),ref_in_gpio_mask); 

        uint32_t ref_sel_mask = ((HAL_REF_V_SEL_RLADDER) <<(COMP2_ACTIVE_MODE_COMP2_REF_SEL_OFFSET));
        uint32_t ref_in_mask = (input_gpio_mask | ref_sel_mask | ladder_ref_sel_mask);
        //printk("comparator_analog_comp2_diff_mode_init  --ref_sel_mask=0x%08X", ref_sel_mask);
        //printk("comparator_analog_comp2_diff_mode_init  --ref_in_mask=0x%08X", ref_in_mask);
        COMP_WRITE((COMP2_REG + 0x8),(ref_in_mask));
        //printk("comparator_analog_comp2_diff_mode_init  --%08X=0x%08X", (COMP2_REG + 0x8),ref_in_mask);

        /*ladder vup/vdn sel*/
        uint32_t vup_mask = ((comp_cfg -> vup_rladder_value) << COMP2_ACTIVE_MODE_COMP2_RLADDER_VUP_SEL_OFFSET);
        uint32_t vdn_mask = ((comp_cfg -> vdn_rladder_value) << COMP2_ACTIVE_MODE_COMP2_RLADDER_VDN_SEL_OFFSET);
        //printk("comparator_analog_comp2_diff_mode_init  --vup_mask=0x%08X", vup_mask);
        //printk("comparator_analog_comp2_diff_mode_init  --vdn_mask=0x%08X", vdn_mask);
        COMP_WRITE((COMP2_REG + 0xc),(vup_mask | vdn_mask));
        //printk("comparator_analog_comp2_diff_mode_init  --%08X=0x%08X", (COMP2_REG + 0xc),(vup_mask | vdn_mask));
    }
}

void hal_comparator_analog_lpcomp_init(hal_comparator_cfg_t *comp_cfg)
{
    if((comp_cfg->ref_sel) == HAL_REF_V_SEL_LP_RLADDER)
    {
        COMP_WRITE(COMP1_REG,(0x01120957 | LPCOMP1_INT_REF1_ON));
        //printk("hal_comparator_analog_lpcomp_init  --%08X=0x%08X", (COMP1_REG),((0x01120957 | LPCOMP1_INT_REF1_ON)));
    }
    else
    {
        COMP_WRITE(COMP1_REG,(0x01120957 | LPCOMP1_INT_REF1_OFF));
        //printk("hal_comparator_analog_lpcomp_init  --%08X=0x%08X", (COMP1_REG),((0x01120957 | LPCOMP1_INT_REF1_OFF)));
    }

    /*lpcomp setting*/
    COMP_WRITE(COMP1_REG,(0x01150011));
    //printk("hal_comparator_analog_lpcomp_init  --%08X=0x%08X", (COMP1_REG),(0x01150011));

    /*ref setting*/
    uint32_t ref_in_gpio_mask = ((comp_cfg->ref_in_gpio) << (LPCOMP_EXTERNAL_GPIO_SEL_OFFSET));
    uint32_t input_gpio_mask =((comp_cfg->input_gpio) << (LPCOMP_INPUT_GPIO_SEL_OFFSET));
    uint32_t ref_sel_mask = ((comp_cfg->ref_sel) <<(LPCOMP_REF_SEL_OFFSET));
    uint32_t ref_in_mask = (input_gpio_mask | ref_in_gpio_mask | ref_sel_mask);
    COMP_WRITE(COMP1_REG,(0x01160070 | ref_in_mask));
    //printk("hal_comparator_analog_lpcomp_init  --%08X=0x%08X", (COMP1_REG),((0x01160070 | ref_in_mask))); 

    /*lpcomp mode ref sel*/
    COMP_WRITE(COMP1_REG,((0x01170000) | ((comp_cfg -> vup_rladder_value)  << LPCOMP_MODE_RLADDER_VTH_SEL_OFFSET)));
    //printk("hal_comparator_analog_lpcomp_init  --%08X=0x%08X", (COMP1_REG),((0x01170000) | ((comp_cfg -> vup_rladder_value)  << LPCOMP_MODE_RLADDER_VTH_SEL_OFFSET)));
}

void comparator_comp2_eint_callback(void)
{
    if (g_comp2_callabck == NULL)
    {
        return;
    }
    g_comp2_callabck();
    hal_eint_unmask(HAL_EINT_LPCOMP);
}

hal_comparator_status_t hal_comparator_comp2_init(hal_comparator_cfg_t *comp_cfg, hal_comparator_callback_t comp2_callback)
{
    hal_eint_config_t comp2_eint_config;
    comp2_eint_config.trigger_mode = HAL_EINT_EDGE_FALLING_AND_RISING;
    hal_eint_status_t ret;

    hal_comparator_analog_power_on();
    hal_comparator_analog_int_ref_on(comp_cfg->internal_ref_cfg);
    hal_comp_trim_data_config();
    hal_comparator_analog_comp2_init(comp_cfg);

    ret = hal_eint_init(HAL_EINT_LPCOMP, &comp2_eint_config);
    if (ret != HAL_EINT_STATUS_OK)
    {
        return HAL_COMPARATOR_STATUS_INVALID_PARAMETER;
    }

    ret = hal_eint_register_callback(HAL_EINT_LPCOMP, (hal_eint_callback_t)comparator_comp2_eint_callback, NULL);
    if (ret != HAL_EINT_STATUS_OK)
    {
        return HAL_COMPARATOR_STATUS_INVALID_PARAMETER;
    }

    g_comp2_callabck = comp2_callback;
    hal_eint_enable(HAL_EINT_LPCOMP);
    ret = hal_eint_unmask(HAL_EINT_LPCOMP);
    if (ret != HAL_EINT_STATUS_OK)
    {
        return HAL_COMPARATOR_STATUS_INVALID_PARAMETER;
    }

    return HAL_COMPARATOR_STATUS_OK;
}

void comparator_comp1_pmu_init()
{
    // pmu_set_strup_rg(31, 0x3); // eint pmu irq set to cm33 enable
    pmu_set_strup_rg(38, 0x3); // eint mask
    pmu_set_strup_rg(34, 0x3); // eint mask
}

void comparator_comp1_eint_callback(void)
{
    if (g_comp1_callabck == NULL)
    {
        return;
    }
    g_comp1_callabck();
}

hal_comparator_status_t hal_comparator_comp1_init(hal_comparator_cfg_t *comp_cfg, hal_comparator_callback_t comp1_callback)
{
    hal_comparator_analog_power_on();
    hal_comparator_analog_int_ref_on(comp_cfg->internal_ref_cfg);
    hal_comp_trim_data_config();
    hal_comparator_analog_comp1_init(comp_cfg);

    g_comp1_callabck = comp1_callback;
    comparator_comp1_pmu_init();
    pmu_status_t ret;
    ret = pmu_register_callback(PMU_CB_CP_F, (pmu_callback_t)comparator_comp1_eint_callback, PMU_USER_COMP);
    if(ret != PMU_STATUS_SUCCESS)
    {
        //printk("pmu_register_callback-PMU_CB_CP_F failed\n");
    }
    ret = pmu_register_callback(PMU_CB_CP_R, (pmu_callback_t)comparator_comp1_eint_callback, PMU_USER_COMP);
    if(ret != PMU_STATUS_SUCCESS)
    {
        //printk("pmu_register_callback-PMU_CB_CP_R failed\n");
    }
    return HAL_COMPARATOR_STATUS_OK;
}

void comparator_comp_lp_eint_callback(void)
{
    if (g_comp_lp_callabck == NULL)
    {
        return;
    }
    g_comp_lp_callabck();
}

hal_comparator_status_t hal_comparator_comp_lp_init(hal_comparator_cfg_t *comp_cfg,hal_comparator_callback_t comp_lp_callback)
{
    hal_comparator_analog_power_on();
    hal_comparator_analog_lpcomp_init(comp_cfg);
    g_comp_lp_callabck = comp_lp_callback;
    comparator_comp1_pmu_init();
    pmu_status_t ret;
    ret = pmu_register_callback(PMU_CB_CP_F, (pmu_callback_t)comparator_comp_lp_eint_callback, PMU_USER_COMP);
    if(ret != PMU_STATUS_SUCCESS)
    {
        //printk("pmu_register_callback-PMU_CB_CP_F failed\n");
    }
    ret = pmu_register_callback(PMU_CB_CP_R, (pmu_callback_t)comparator_comp_lp_eint_callback, PMU_USER_COMP);
    if(ret != PMU_STATUS_SUCCESS)
    {
        //printk("pmu_register_callback-PMU_CB_CP_R failed\n");
    }
    return HAL_COMPARATOR_STATUS_OK;
}

hal_comparator_status_t hal_comparator_comp_init(hal_comparator_cfg_t *comp_cfg, hal_comparator_callback_t comp_callback)
{
    if(comp_cfg == NULL||comp_callback == NULL)
    {
        return HAL_COMPARATOR_STATUS_INVALID_PARAMETER;
    }

    hal_comparator_status_t ret;
    ret = comparator_para_check(comp_cfg);
    if (ret != HAL_COMPARATOR_STATUS_OK)
    {
        return HAL_COMPARATOR_STATUS_INVALID_PARAMETER;
    }

    switch(comp_cfg->comp_port)
    {
        case HAL_COMP_1:
            return hal_comparator_comp1_init(comp_cfg,comp_callback);
        case HAL_COMP_2:
            return hal_comparator_comp2_init(comp_cfg,comp_callback);
        case HAL_COMP_LP:
            return hal_comparator_comp_lp_init(comp_cfg,comp_callback);
        default:
            return HAL_COMPARATOR_STATUS_INVALID_PARAMETER;
    }
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
    // printk("hal_comp1_enable  --*(volatile uint32_t *)(%08X)=0x%08X", COMP1_REG,(enable_value));
}

void hal_comp1_disable()
{
    uint32_t disable_value = (g_comp1_mode_reg_value & (~(1 << 0)));
    COMP_WRITE(COMP1_REG,(disable_value));
    // printk("hal_comp1_disable(%08X)=0x%08X", COMP1_REG,(disable_value));
}

void hal_comp2_enable(void)
{
    uint32_t enable_value = (g_comp2_mode_reg_value | (1 << 0));
    COMP_WRITE(COMP2_REG,enable_value);
    // printk("hal_comp2_enable  --*(volatile uint32_t *)(%08X)=0x%08X", COMP2_REG,(enable_value));
}

void hal_comp2_disable()
{
    uint32_t disable_value = (g_comp2_mode_reg_value & (~(1 << 0)));
    COMP_WRITE(COMP2_REG,disable_value);
    // printk("hal_comp2_disable(%08X)=0x%08X", COMP2_REG,(disable_value));
}

void hal_comp_trim_data_config()
{
    uint32_t trim_data;
    OTP_check_comp_trim(87, &trim_data);
    COMP_WRITE(COMP_REF_REG,((0x01140007) | trim_data));
    printk("hal_comparator_analog_int_ref_on  --*(volatile uint32_t *)(%08X)=0x%08X", COMP_REF_REG,((0x01140007) | trim_data));
}

#endif /*HAL_COMPARATOR_MODULE_ENABLED*/
