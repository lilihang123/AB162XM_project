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
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWRGBGES AND AGREES
 * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWRGBGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.
 */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hal.h"
#include "bsp_argb.h"
#include "zephyr/kernel.h"
#include <zephyr/devicetree.h>
#include <zephyr/device.h>

#include "hal_gpio.h"
#include "hal_gpio_internal.h"
#include "hal_argb_internal.h"
static bool argb_init = false;
argb_para_t argb_para;

#define PR_WAKE_VAL     1
#define DMA_ST_VAL_DIFF 4

#define GET_ARGB_PARAMETER(node_id) \
    do {  \
        argb_para.gpio_channel  = DT_PROP(node_id, argb_channel);  \
        argb_para.one_h_value   = DT_PROP(node_id, one_h_value);  \
        argb_para.one_l_value   = DT_PROP(node_id, one_l_value);  \
        argb_para.zero_h_value  = DT_PROP(node_id, zero_h_value);  \
        argb_para.zero_l_value  = DT_PROP(node_id, zero_l_value);  \
        argb_para.reset_value   = DT_PROP(node_id, reset_value);  \
        argb_para.pat_cnt       = DT_PROP(node_id, pat_cnt);  \
        argb_para.bit_nonrev    = DT_PROP(node_id, bit_nonrev);  \
        argb_para.ed_big        = DT_PROP(node_id, ed_big);  \
        argb_para.nonalign      = DT_PROP(node_id, nonalign);  \
        argb_para.auto_timer_val    = DT_PROP(node_id, auto_timer_val);  \
        argb_para.dma_start_val     = DT_PROP(node_id, dma_start_val);  \
        argb_para.pre_wake_val      = DT_PROP(node_id, pre_wake_val);  \
    } while(0);  \

static bsp_argb_status_t argb_para_set(bool auto_mode)
{
    GET_ARGB_PARAMETER(DT_NODELABEL(argb));
    hal_argb_setting setting;
    // printk("[bsp][argb] gpio channel: %d, one_h_value:%d\r\n", argb_para.gpio_channel, argb_para.one_h_value);
    setting.timing.one_l_value  = argb_para.one_h_value ;
    setting.timing.one_h_value  = argb_para.one_l_value ;
    setting.timing.zero_l_value = argb_para.zero_h_value;
    setting.timing.zero_h_value = argb_para.zero_l_value;
    setting.timing.reset_value  = argb_para.reset_value ;
    setting.num                 = argb_para.pat_cnt;

    if (argb_para.nonalign == 1) {
        setting.endian_big      = argb_para.ed_big;
    } else {
        return BSP_ARGB_STATUS_ERROR_INVALID_PARAMETER;
    }
    setting.nonalign            = argb_para.nonalign;

    hal_argb_dma_timing_setting dma_setting;
    if (auto_mode) {
        dma_setting.auto_timer_value = argb_para.auto_timer_val ;
        dma_setting.dma_start_vaule = argb_para.dma_start_val;
        dma_setting.pre_wake_value = argb_para.pre_wake_val;
    }

    hal_argb_init_for_middle(&setting, &dma_setting);
    return BSP_ARGB_STATUS_OK;
}

bsp_argb_status_t bsp_argb_enable(void)
{
    int status = 0;
    uint32_t irq_status;
    if (argb_init == true) {
        return BSP_ARGB_STATUS_OK;
    }
    status = argb_para_set(false);
    if (status != BSP_ARGB_STATUS_OK) {
        return BSP_ARGB_STATUS_ERROR;
    }
    hal_middle_argb_register_callback(argb_para.callback, argb_para.user_data);

    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    argb_init = true;
    hal_nvic_restore_interrupt_mask(irq_status);
    return BSP_ARGB_STATUS_OK;
}


bsp_argb_status_t bsp_argb_realtime_config(argb_style_config_t *p_config)
{
    uint32_t data_size;
    if (argb_para.nonalign) {
        data_size = argb_para.pat_cnt * 3;  /* 每灯3字节紧凑排列 */
    } else {
        // data_size = argb_para.pat_cnt * 4;
        return BSP_ARGB_STATUS_ERROR;
    }
    // uint32_t dma_bytes = ((data_size + 3) / 4) * 4; /* DMA实际按4B word对齐传输 */
    // printk("[bsp][argb] repeat=%d data_size=%d dma_bytes=%d addr=0x%x type=%d\r\n", p_config->repeat, data_size, dma_bytes, (unsigned int)p_config->argb_data, p_config->type);
    // printk("[bsp][argb] DMA buf: ");
    // for (uint32_t i = 0; i < dma_bytes; i++)
    //     printk("%02X ", ((uint8_t*)p_config->argb_data)[i]);
    // printk("\r\n");
    int ret = hal_argb_config_data_mdoe_for_middle(p_config->repeat, data_size, p_config->argb_data, p_config->type);
    ret |= hal_middle_argb_start();
    if (ret < 0) {
        return BSP_ARGB_STATUS_ERROR;
    }
    return ret;
}

bsp_argb_status_t bsp_argb_realtime_start(void)
{
    int status = 0;
    status = hal_middle_argb_start();
    if (status != 0) {
        return BSP_ARGB_STATUS_ERROR;
    }
    return BSP_ARGB_STATUS_OK;
}


bsp_argb_status_t bsp_argb_disable(void)
{
    int status = 0;
    uint32_t irq_status;
    if (argb_init == false) {
        return BSP_ARGB_STATUS_OK;
    }
    status = hal_middle_argb_deinit();
    if (status != 0) {
        return BSP_ARGB_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    argb_init = false;
    hal_nvic_restore_interrupt_mask(irq_status);
    return BSP_ARGB_STATUS_OK;
}


bsp_argb_status_t bsp_argb_register_isr(bsp_argb_callback_t callback, void *user_data)
{
    uint32_t save_mask;
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    argb_para.callback = callback;
    argb_para.user_data = user_data;
    hal_nvic_restore_interrupt_mask(save_mask);
    return BSP_ARGB_STATUS_OK;
}

// bsp_argb_status_t bsp_argb_realtime_enable(argb_style_config_t *cfg, uint8_t interval)
// {
//     int status;
//     (void)interval;

//     printk("[bsp][argb] realtime_enable: argb_init=%d\r\n", argb_init);

//     /* Init hardware if not already done */
//     if (argb_init == false) {
//         status = argb_para_set(true);
//         printk("[bsp][argb] argb_para_set ret=%d\r\n", status);
//         if (status != BSP_ARGB_STATUS_OK) {
//             return BSP_ARGB_STATUS_ERROR;
//         }
//         hal_middle_argb_register_callback(argb_para.callback, argb_para.user_data);
//     }

//     printk("[bsp][argb] calling realtime_config, argb_data=%p\r\n", cfg->argb_data);
//     status = bsp_argb_realtime_config(cfg);
//     printk("[bsp][argb] realtime_config ret=%d\r\n", status);
//     if (status != BSP_ARGB_STATUS_OK) {
//         return BSP_ARGB_STATUS_ERROR;
//     }

//     uint32_t irq_status;
//     hal_nvic_save_and_set_interrupt_mask(&irq_status);
//     argb_init = true;
//     hal_nvic_restore_interrupt_mask(irq_status);

//     return BSP_ARGB_STATUS_OK;
// }