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
#include "argb_middle_control.h"
#include "argb_control_style_cfg.h"
#include "bsp_argb.h"
#include "nvkey.h"
#include "zephyr/kernel.h"
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
/***************************************** Private variable********************************************/


static  argb_middle_info_t       argb_middle_info;
static  uint8_t                  argb_occupy;
static  uint8_t                 real_time_argb_start;
static  argb_nvkey_t             argb_nvkey;

#define ARGB_NVKEY_OFFSET (4)
#define NVKEY_MAX_SIZE (512)
#define ARGB_ONE_SIZE (300)
uint8_t flash_repeat;
uint16_t gobal_offset;
uint16_t nvkey_id;

#define     GET_CURRENT_PATTERN(x)               rgb_middle_control_get_active_pattern(x)

#if 0
#define log_rgb_middle_info(fmt, cnt, ...)     log_hal_msgid_info("[hal][rtc] " fmt, cnt, ##__VA_ARGS__)
#define log_rgb_middle_warning(fmt, cnt, ...)  log_hal_msgid_warning("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#define log_rgb_middle_error(fmt, cnt, ...)    log_hal_msgid_error("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#else
#define log_rgb_middle_info(fmt, cnt, ...)     printk(fmt, ##__VA_ARGS__)
#define log_rgb_middle_warning(fmt, cnt, ...)  printk(fmt, ##__VA_ARGS__)
#define log_rgb_middle_error(fmt, cnt, ...)    printk(fmt, ##__VA_ARGS__)
#endif

uint8_t max_list_node_num = CONFIG_AIR_ARGB_PRIORITY_LEVEL_NUM;

void    argb_control_printf(argb_style_config_t *p_style)
{
    log_rgb_middle_info("[middle][argb] argb run type :%d\r\n", 1, p_style->type);
    log_rgb_middle_info("[middle][argb] argb pattern  :%d\r\n", 1, p_style->pattern);
}

/* Function to load NVKEY data */
static int argb_load_nvkey_data(uint16_t id, uint16_t offset, uint16_t size, uint8_t *buf)
{
    uint16_t remain = size;
    uint16_t addr = ARGB_NVKEY_OFFSET + offset;
    uint16_t buf_off = 0;
    uint8_t *nvkey_buf = k_malloc(NVKEY_MAX_SIZE);
    if (!nvkey_buf) {
        return -1;
    }
    while (remain > 0) {
        uint8_t id_idx = addr / NVKEY_MAX_SIZE;
        uint16_t id_off = addr % NVKEY_MAX_SIZE;
        uint16_t left_off = NVKEY_MAX_SIZE - id_off;
        if (left_off > remain) {
            left_off = remain;
        }
        uint32_t size = NVKEY_MAX_SIZE ;
        int ret = nvkey_read_data(id + id_idx, nvkey_buf, &size);
        if (ret != 0) {
            k_free(nvkey_buf);
            return -1;
        }
        memcpy(buf + buf_off, nvkey_buf + id_off, left_off);
        addr += left_off;
        buf_off += left_off;
        remain -= left_off;
    }
    k_free(nvkey_buf);
    return 0;
}


static void  argb_control_isr(void *user_data)
{
    argb_style_config_t *p_style = (argb_style_config_t *) user_data;
    argb_middle_status_t status;
    status = argb_middle_control_disable(p_style->type, p_style->pattern, false);
    if (status == ARGB_MIDDLE_STATUS_OK) {
        if (argb_middle_info.call_back != NULL) {
            argb_middle_info.call_back(argb_middle_info.user_data);
        }
    }
}

static  bool  g_argb_enable = false;

void  argb_control_enable()
{
    bsp_argb_enable();
    g_argb_enable = true;
}

void  argb_control_disable()
{
    bsp_argb_disable();
    g_argb_enable = false;
}

void pack_argb_data_to_align(uint8_t *data_input, uint8_t num, uint32_t  *data_output)
{
    /* This function packs ARGB data into 32-bit aligned format */
    for(uint8_t i = 0; i < num; i++)
    {
        data_output[i] = ((uint32_t)data_input[i * 3] << 16) | ((uint32_t)data_input[i * 3 + 1] << 8) | ((uint32_t)data_input[i * 3 + 2] << 0);
    }
}


argb_middle_status_t    argb_middle_control_enable(uint8_t effect_type, uint8_t level, uint8_t repeat, uint8_t  *data_index, bool nvkey_option)
{
    log_rgb_middle_info("[middle][argb] argb_middle_control_enable type: %d, pattern: %d, repeat:%d, data_index:0x%x, nvkey_option:%d, addr:0x%x\r\n", 5, effect_type, level, repeat, *data_index, nvkey_option, data_index);
    argb_style_config_t *p_config;
    p_config = k_malloc(sizeof(argb_style_config_t));
    /* Get current config */
    p_config->type = effect_type;
    p_config->pattern = level;
    p_config->repeat = repeat;
    p_config->argb_data = data_index;

    /* ARGB init , config argb setting*/
    if (g_argb_enable == false) {
        argb_control_enable();
    }
    uint8_t current_level = level;
    /* Need change pattern */
    if (level < max_list_node_num) {
        if (level < current_level) {
            log_rgb_middle_error("[middle][argb] pattern(%d) lower than current(%d)\r\n", 2, level, current_level);
            return ARGB_MIDDLE_STATUS_ERROR;
        }
    } else {
        log_rgb_middle_error("[middle][argb] pattern(%d) higher than max(%d)\r", 2, level, max_list_node_num);
        return ARGB_MIDDLE_STATUS_ERROR;
    }
    bsp_argb_realtime_config(p_config);
    k_free(p_config);
    return  ARGB_MIDDLE_STATUS_OK;
}

argb_middle_status_t    argb_middle_control_realtime_enable(uint8_t interval, argb_style_config_t *cfg)
{
    uint32_t irq_status;
    if (argb_occupy == argb_occupy_none) {
        argb_style_config_t             *p_style;
        p_style = argb_style_config_read(argb_occupy_realtime, 0, 0);
        bsp_argb_register_isr(argb_control_isr, p_style);  //init
        bsp_argb_status_t status = bsp_argb_realtime_enable(cfg, interval);
        if (status == BSP_ARGB_STATUS_ERROR) {
            return ARGB_MIDDLE_STATUS_ERROR;
        } else {
            hal_nvic_save_and_set_interrupt_mask(&irq_status);
            argb_occupy = argb_occupy_realtime;
            hal_nvic_restore_interrupt_mask(irq_status);
        }
    }
    bsp_argb_status_t ret;
    // bsp_argb_realtime_config(cfg);

    if (real_time_argb_start == false) {
        bsp_argb_status_t status = bsp_argb_realtime_start();
        if (status == BSP_ARGB_STATUS_ERROR) {
            return ARGB_MIDDLE_STATUS_ERROR;
        } else {
            hal_nvic_save_and_set_interrupt_mask(&irq_status);
            real_time_argb_start = true;
            hal_nvic_restore_interrupt_mask(irq_status);
        }
    }
    return ret;
}


static argb_middle_status_t  argb_middle_control_flash_enable_internal(uint8_t rgb_num, uint16_t id, bool continued)
{
    uint16_t rgb_size = argb_nvkey.argb_size | (argb_nvkey.argb_size_remain << 8);
    if (argb_nvkey.argb_size == 0) {
        return ARGB_MIDDLE_STATUS_ERROR;
    }
    // log_rgb_middle_error("[middle][argb] argb_middle_control_flash_enable_internal gobal_offset size: %d,rgb_size:%d \r\n", 3, rgb_num, gobal_offset[rgb_num], rgb_size);
    if (gobal_offset < rgb_size) {
        uint16_t read_size = (gobal_offset + ARGB_ONE_SIZE <= rgb_size) ? ARGB_ONE_SIZE : (rgb_size - gobal_offset);
        if (read_size % 3 != 0) {
            read_size -= (read_size % 3);
        }
        if (argb_nvkey.argb_data != NULL) {
            k_free(argb_nvkey.argb_data);
            argb_nvkey.argb_data = NULL;
        }
        argb_nvkey.argb_data = k_malloc(read_size);
        if (!argb_nvkey.argb_data) {
            return ARGB_MIDDLE_STATUS_ERROR;
        }
        if (argb_load_nvkey_data(id, gobal_offset, read_size, argb_nvkey.argb_data) != 0) {
            // log_rgb_middle_error("[middle][argb] argb_middle_control_flash_enable_internal argb_load_nvkey_data size: %d,rgb_size:%d \r\n", 3, rgb_num, gobal_offset[rgb_num], rgb_size);
            // k_free(argb_nvkey[rgb_num].rgb_data);
            // argb_nvkey[rgb_num].rgb_data = NULL;
            return ARGB_MIDDLE_STATUS_ERROR;
        }
        gobal_offset += ARGB_ONE_SIZE;
        if (continued == false) {
            // bsp_argb_enable(argb_nvkey.argb_data);
        } else {
            // bsp_argb_enable(argb_nvkey.argb_data);
        }
        log_rgb_middle_error("[middle][argb] argb_middle_control_flash_enable_internal argb_load_nvkey_data size: %d,rgb_size:%d, rgb_interval:%d \r\n", 4, rgb_num, gobal_offset, rgb_size, argb_nvkey.argb_interval);
    } else {
        return ARGB_MIDDLE_STATUS_OK;
    }
    return ARGB_MIDDLE_STATUS_OK;
}

static void  argb_middle_control_flash_isr(void *user_data)
{
    // argb_style_config_t *p_style = (argb_style_config_t *) user_data;
    // argb_middle_status_t status = argb_middle_control_flash_enable_internal(p_style, nvkey_id, true);
    // log_rgb_middle_error("[middle][argb] argb_middle_control_flash_isr status : %d \r\n", 1, status);
}

argb_middle_status_t    argb_middle_control_flash_enable(uint8_t rgb_num, uint16_t id, uint8_t repeat)
{
    // log_rgb_middle_error("[middle][argb] rgb_middle_control_flash_enable repeat: %d\n", 2, rgb_num, repeat);
    uint32_t            irq_status;
    argb_style_config_t  *p_style;
    argb_middle_status_t rgb_status;
    if ((argb_occupy != argb_occupy_none) && (argb_occupy != argb_occupy_normal)) {
        log_rgb_middle_error("[middle][argb] flash rgb is other %d moder\n", 2, rgb_num, argb_occupy);
        return ARGB_MIDDLE_STATUS_ERROR;
    }

    uint32_t size = ARGB_NVKEY_OFFSET ;
    nvkey_read_data(id, (uint8_t *)&argb_nvkey, &size);
    uint16_t rgb_size = argb_nvkey.argb_size | (argb_nvkey.argb_size_remain << 8);
    if (rgb_size == 0) {
        log_rgb_middle_error("[middle][argb] flash rgb nvkey size is NULL\n", 1, rgb_num);
        return ARGB_MIDDLE_STATUS_ERROR;
    }
    p_style = argb_style_config_read(argb_occupy_normal, 0, 0);
    bsp_argb_register_isr(argb_middle_control_flash_isr, p_style);  //register callback
    rgb_status = argb_middle_control_flash_enable_internal(rgb_num, id, false);
    // log_rgb_middle_error("[middle][argb] argb_middle_control_flash_enable_internal status: %d\n", 2, rgb_num, rgb_status);
    if (rgb_status == ARGB_MIDDLE_STATUS_OK) {
        hal_nvic_save_and_set_interrupt_mask(&irq_status);
        nvkey_id   = id;
        argb_occupy = argb_occupy_normal;
        hal_nvic_restore_interrupt_mask(irq_status);
    }
    return rgb_status;
}

argb_middle_status_t    argb_middle_control_disable(argb_run_type_t type, uint8_t  pattern, bool force_option)
{
    bsp_argb_disable();
    return ARGB_MIDDLE_STATUS_OK;
}

argb_middle_status_t argb_middle_register_callback(argb_middle_callback_t callback, void  *user_data)
{
    uint32_t            irq_status;
    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    argb_middle_info.call_back = callback;
    argb_middle_info.user_data = user_data;
    hal_nvic_restore_interrupt_mask(irq_status);
    return ARGB_MIDDLE_STATUS_OK;
}

argb_middle_status_t argb_middle_control_enable_for_node(argb_pattern_data_t data_config, uint8_t pattern, argb_run_type_t run_type)
{
    log_rgb_middle_error("[middle][argb] argb_middle_control_enable_for_node,current pattern:%d, current type: %d, argb_occupy:%d\n", 3, pattern, run_type, argb_occupy);
    if (argb_occupy != argb_occupy_none && run_type == argb_occupy_realtime) {
        return ARGB_MIDDLE_STATUS_ERROR;
    }
    argb_middle_status_t rgb_status;

    return rgb_status;
}
