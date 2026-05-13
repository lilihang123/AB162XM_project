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

#ifndef __HAL_COMPARATOR_H__
#define __HAL_COMPARATOR_H__
#include "hal_platform.h"
#include "hal_eint.h"
#include "hal_eint_internal.h"

#define COMP_READ(addr)                  *((volatile uint32_t *)(addr))
#define COMP_WRITE(addr, val)            *((volatile uint32_t *)(addr)) = val

/*ref seeting*/
#define COMP_REF_REG 0x42108008

/*comp1 active*/
#define COMP1_REG 0x42108008
#define COMP1_ACTIVE_MODE_EXTERNAL_GPIO_SEL_OFFSET (0)
#define COMP1_ACTIVE_MODE_INPUT_GPIO_SEL_OFFSET (8)
#define COMP1_ACTIVE_MODE_COMP1_REF_SEL_OFFSET (12)
#define COMP1_ACTIVE_MODE_COMP1_REF_RLADDER_INPUT_SEL_OFFSET (14)
#define COMP1_ACTIVE_MODE_COMP1_RLADDER_VUP_SEL_OFFSET (0)
#define COMP1_ACTIVE_MODE_COMP1_RLADDER_VDN_SEL_OFFSET (8)

/*comp2  active*/
#define COMP2_REG 0x42080060
#define COMP2_ACTIVE_MODE_EXTERNAL_GPIO_SEL_OFFSET (4)
#define COMP2_ACTIVE_MODE_INPUT_GPIO_SEL_OFFSET (0)
#define COMP2_ACTIVE_MODE_COMP2_REF_SEL_OFFSET (4)
#define COMP2_ACTIVE_MODE_COMP2_REF_LADDER_INPUT_SEL_OFFSET (8)
#define COMP2_ACTIVE_MODE_COMP2_RLADDER_VUP_SEL_OFFSET (8)
#define COMP2_ACTIVE_MODE_COMP2_RLADDER_VDN_SEL_OFFSET (0)

/*comp1 lpcomp mode*/
#define LPCOMP1_INT_REF1_OPEN_OFFSET (3)
#define LPCOMP1_INT_REF1_ON (0x1 << (LPCOMP1_INT_REF1_OPEN_OFFSET))
#define LPCOMP1_INT_REF1_OFF (0x0 << (LPCOMP1_INT_REF1_OPEN_OFFSET))
#define LPCOMP_EXTERNAL_GPIO_SEL_OFFSET (0)
#define LPCOMP_INPUT_GPIO_SEL_OFFSET (8)
#define LPCOMP_REF_SEL_OFFSET (12)
#define LPCOMP_MODE_RLADDER_VTH_SEL_OFFSET (0)

/** @brief  This enum define the API return type.  */
typedef enum
{
    HAL_COMPARATOR_STATUS_INVALID_PARAMETER = -2,
    HAL_COMPARATOR_STATUS_ERROR = -1,
    HAL_COMPARATOR_STATUS_OK = 0
} hal_comparator_status_t;

typedef enum
{
    HAL_COMPARATOR_INT_REFF_ON_CP1_1_2_CP2_1_2,
    HAL_COMPARATOR_INT_REFF_ON_CP1_1_8_CP2_1_2,
    HAL_COMPARATOR_INT_REFF_ON_CP1_2_4_CP2_1_2,
    HAL_COMPARATOR_INT_REFF_ON_CP1_VDD_CP2_1_2,
    HAL_COMPARATOR_INT_REFF_ON_CP1_1_2_CP2_1_8,
    HAL_COMPARATOR_INT_REFF_ON_CP1_1_8_CP2_1_8,
    HAL_COMPARATOR_INT_REFF_ON_CP1_2_4_CP2_1_8,
    HAL_COMPARATOR_INT_REFF_ON_CP1_VDD_CP2_1_8,
    HAL_COMPARATOR_INT_REFF_ON_CP1_1_2_CP2_2_4,
    HAL_COMPARATOR_INT_REFF_ON_CP1_1_8_CP2_2_4,
    HAL_COMPARATOR_INT_REFF_ON_CP1_2_4_CP2_2_4,
    HAL_COMPARATOR_INT_REFF_ON_CP1_VDD_CP2_2_4,
    HAL_COMPARATOR_INT_REFF_ON_CP1_1_2_CP2_VDD,
    HAL_COMPARATOR_INT_REFF_ON_CP1_1_8_CP2_VDD,
    HAL_COMPARATOR_INT_REFF_ON_CP1_2_4_CP2_VDD,
    HAL_COMPARATOR_INT_REFF_ON_CP1_VDD_CP2_VDD,
    HAL_COMPARATOR_INT_REFF_MAX
} hal_comparator_inter_ref_cfg_t;

typedef enum
{
    HAL_COMP_SE_MODE_REF_ON_LS_MODE,
    HAL_COMP_SE_MODE_REF_ON_NM_MODE,
    HAL_COMP_SE_MODE_REF_ON_HS_MODE,
    HAL_COMP_SE_MODE_REF_OFF_LS_MODE,
    HAL_COMP_SE_MODE_REF_OFF_NM_MODE,
    HAL_COMP_SE_MODE_REF_OFF_HS_MODE,
    HAL_COMP_SE_MODE_MAX = HAL_COMP_SE_MODE_REF_OFF_HS_MODE,

    HAL_COMP_DIFF_MODE_REF_ON_LS_MODE,
    HAL_COMP_DIFF_MODE_REF_ON_NM_MODE,
    HAL_COMP_DIFF_MODE_REF_ON_HS_MODE,
    HAL_COMP_DIFF_MODE_REF_OFF_LS_MODE,
    HAL_COMP_DIFF_MODE_REF_OFF_NM_MODE,
    HAL_COMP_DIFF_MODE_REF_OFF_HS_MODE,
    HAL_COMP_MODE_MAX
} hal_comp_mode_cfg_t;

typedef enum
{
    HAL_GPIO_SEL_NO,
    HAL_GPIO_SEL_GPIO25,
    HAL_GPIO_SEL_GPIO26,
    HAL_GPIO_SEL_GPIO27,
    HAL_GPIO_SEL_GPIO28,
    HAL_GPIO_SEL_GPIO29,
    HAL_GPIO_SEL_GPIO30,
    HAL_GPIO_SEL_GPIO31,
    HAL_GPIO_SEL_GPIO32,
    HAL_GPIO_SEL_GPIO33,
    HAL_GPIO_SEL_GPIO34,
    HAL_GPIO_SEL_MAX
}hal_comp_gpio_cfg_t;

typedef enum
{
    HAL_REF_V_SEL_RLADDER = 0,
    HAL_REF_V_SEL_INTERNAL_REF_IN = 1,
    HAL_REF_V_SEL_GPIO_IN = 2,
    HAL_REF_V_SEL_LP_RLADDER = 3
}hal_comp_ref_in_cfg_t;

typedef enum
{
    HAL_LADDER_REF_V_SEL_AVSS =0,
    HAL_LADDER_REF_V_SEL_REF_ON_IN = 1,
    HAL_LADDER_REF_V_SEL_GPIO_IN = 2,
    HAL_LADDER_REF_V_SEL_VDD =3
}hal_comp_ref_ladder_in_cfg_t;

typedef enum
{
    HAL_COMP_1 = 0,
    HAL_COMP_2 = 1,
    HAL_COMP_LP = 2,
    HAL_COMP_MAX = HAL_COMP_LP,
}hal_comp_port_t;

typedef struct
{
    hal_comp_port_t comp_port;
    hal_comp_mode_cfg_t mode;
    hal_comp_gpio_cfg_t input_gpio;
    hal_comp_gpio_cfg_t ref_in_gpio;
    hal_comparator_inter_ref_cfg_t internal_ref_cfg;
    hal_comp_ref_in_cfg_t ref_sel;
    hal_comp_ref_ladder_in_cfg_t ladder_ref_sel;
    uint8_t vup_rladder_value;  //0~63-> input ref =(value+1/64) Vref
    uint8_t vdn_rladder_value;  //0~63-> input ref =(value+1/64) Vref
} hal_comparator_cfg_t;

typedef void (*hal_comparator_callback_t)(void);
/*api*/
void hal_comparator_analog_power_on(void);
void hal_comparator_analog_power_off(void);
void hal_comparator_analog_reset(void);
void hal_comparator_analog_int_ref_on(hal_comparator_inter_ref_cfg_t internal_ref_cfg);

void hal_comparator_analog_comp1_init(hal_comparator_cfg_t *comp_cfg);
void hal_comparator_analog_comp2_init(hal_comparator_cfg_t *comp_cfg);
void hal_comparator_analog_lpcomp_init(hal_comparator_cfg_t *comp_cfg);

hal_comparator_status_t hal_comparator_comp1_init(hal_comparator_cfg_t *comp_cfg, hal_comparator_callback_t comp1_callback);
hal_comparator_status_t hal_comparator_comp2_init(hal_comparator_cfg_t *comp_cfg, hal_comparator_callback_t comp2_callback);
void hal_comparator_deinit();

void hal_comp1_enable(void);
void hal_comp1_disable(void);
void hal_comp2_enable(void);
void hal_comp2_disable(void);
#endif /*__HAL_COMPARATOR_H__*/