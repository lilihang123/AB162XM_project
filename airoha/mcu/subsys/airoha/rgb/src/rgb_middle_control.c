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
#include "rgb_middle_control.h"
#include "rgb_control_style_cfg.h"
#include "bsp_rgb.h"
#include "nvkey.h"
/***************************************** Private variable********************************************/
static  uint32_t                        g_immediately_enable = false;

static  rgb_middle_info_t       rgb_middle_info[CONFIG_AIR_RGB_NUM];
static  uint8_t                 rgb_occupy[CONFIG_AIR_RGB_NUM];
// static  uint8_t                 rgb_run_type[CONFIG_AIR_RGB_NUM];
static  uint8_t                 real_time_rgb_start[CONFIG_AIR_RGB_NUM];
static  rgb_nvkey_t             rgb_nvkey[CONFIG_AIR_RGB_NUM];

#define RGB_NVKEY_OFFSET (4)
#define NVKEY_MAX_SIZE (512)
#define RGB_ONE_SIZE (300)
uint8_t flash_repeat[CONFIG_AIR_RGB_NUM];
uint16_t gobal_offset[CONFIG_AIR_RGB_NUM];
uint16_t nvkey_id[CONFIG_AIR_RGB_NUM];

#if 0
#define log_rgb_middle_info(fmt, cnt, ...)     log_hal_msgid_info("[hal][rtc] " fmt, cnt, ##__VA_ARGS__)
#define log_rgb_middle_warning(fmt, cnt, ...)  log_hal_msgid_warning("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#define log_rgb_middle_error(fmt, cnt, ...)    log_hal_msgid_error("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#else
#define log_rgb_middle_info(fmt, cnt, ...)     printk(fmt, ##__VA_ARGS__)
#define log_rgb_middle_warning(fmt, cnt, ...)  printk(fmt, ##__VA_ARGS__)
#define log_rgb_middle_error(fmt, cnt, ...)    printk(fmt, ##__VA_ARGS__)
#endif

void    rgb_control_printf(rgb_one_led_style_t *p_style)
{
    log_rgb_middle_info("[middle][rgb] rgb      on/off :%d\r\n", 1, p_style->onoff);
    log_rgb_middle_info("[middle][rgb] t0              :%d\r\n", 1, p_style->t0);
    log_rgb_middle_info("[middle][rgb] t1 rising       :%d\r\n", 1, p_style->t1_rising);
    log_rgb_middle_info("[middle][rgb] t1 lightest     :%d\r\n", 1, p_style->t1_lightest);
    log_rgb_middle_info("[middle][rgb] t2 falling      :%d\r\n", 1, p_style->t2_falling);
    log_rgb_middle_info("[middle][rgb] t2 darkest      :%d\r\n", 1, p_style->t2_darkest);
    log_rgb_middle_info("[middle][rgb] t3              :%d\r\n", 1, p_style->t3);
    log_rgb_middle_info("[middle][rgb] t1t2   repeat   :%d\r\n", 1, p_style->repeat_t1t2);
    log_rgb_middle_info("[middle][rgb] extend repeat   :%d\r\n", 1, p_style->repeat_ext);
    log_rgb_middle_info("[middle][rgb] brightness      :%d\r\n", 1, p_style->brightness);
    log_rgb_middle_info("[middle][rgb] start brightness:%d\r\n", 1, p_style->start_brightness);
    log_rgb_middle_info("[middle][rgb] end brightness  :%d\r\n", 1, p_style->end_brightness);
}

uint8_t max_list_node_num = CONFIG_AIR_RGB_PRIORITY_LEVEL_NUM;

// struct for light node
typedef struct LightEffectNode {
    uint8_t priority;  // rgb level
    rgb_run_type_t run_type; // rgb type
    rgb_pattern_data_t effect_info;  // rgb effect info
    struct LightEffectNode *next;  // pointer to next node
} LightEffectNode;

// struct for rgb
typedef struct  {
    LightEffectNode *effects;  // rgb effects
    uint8_t current_num;
} RGB_Light_t;

static RGB_Light_t rgb_lights[CONFIG_AIR_RGB_NUM];
// insert rgb info list priority from high to low
void insert_rgb_info_for_list(RGB_Light_t *light, uint8_t priority, rgb_pattern_data_t effect_info, rgb_run_type_t run_type)
{
    if (light->current_num >= max_list_node_num) {
        printk("Rgb info effect list oversize, insert fail.\n");
        return;
    }
    // find same priority node
    LightEffectNode *current = light->effects;
    LightEffectNode *prev = NULL;

    // find node
    while (current != NULL && current->priority != priority) {
        prev = current;
        current = current->next;
    }
    if (current != NULL) {
#ifdef CONFIG_AIR_RGB_EFFECT_OVERWRITE
        // overwrite effect
        current->effect_info = effect_info;
        current->run_type = run_type;
        printk("Rgb info effect with priority %d overwrite.\r\n", priority);
#else
        printk("Rgb info effect with priority %d already exist, insert fail.\r\n", priority);
#endif
        return;
    }

    // create node
    LightEffectNode *new_node = (LightEffectNode *)k_malloc(sizeof(LightEffectNode));
    new_node->priority = priority;
    new_node->effect_info = effect_info;
    new_node->run_type = run_type;
    new_node->next = NULL;

    // insert node
    if (light->effects == NULL || light->effects->priority < priority) {
        // insert header
        new_node->next = light->effects;
        light->effects = new_node;
    } else {
        // for loop node
        LightEffectNode *current = light->effects;
        while (current->next != NULL && current->next->priority >= priority) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    light->current_num++;
}

// free the select rgb info
void delete_rgb_info(RGB_Light_t *light, uint8_t priority)
{
    if (light->current_num == 0) {
        printk("Cannot delete effect. No effects to delete for this light.\n");
        return;
    }

    LightEffectNode *current = light->effects;
    LightEffectNode *prev = NULL;

    // find node
    while (current != NULL && current->priority != priority) {
        prev = current;
        current = current->next;
    }

    // remove node
    if (current != NULL) {
        if (prev == NULL) {
            light->effects = current->next;
        } else {
            prev->next = current->next;
        }
        k_free(current);
        light->current_num--;
    } else {
        printk("Effects with priority %d does not exist for this light.\n", priority);
    }
}

// search_rgb_info_list_for_current
uint8_t get_rgb_info_list_for_current_priority(RGB_Light_t *light)
{
    if (light->effects != NULL) {
        printk("get Playing effect with priority: %d\n", light->effects->priority);
        return light->effects->priority;
    } else {
        printk("No effects priority to play.\n");
        return 0;
    }
}

uint8_t get_rgb_info_list_for_current_type(RGB_Light_t *light)
{
    if (light->effects != NULL) {
        printk("get Playing effect with type: %d\n", light->effects->run_type);
        return light->effects->run_type;
    } else {
        printk("No effects type to play.\n");
        return 0;
    }
}

// rgb_pattern_data_t get_rgb_info_list_for_current_info(RGB_Light_t *light)
// {
//     if (light->effects != NULL) {
//         printk("get Playing effect with info: %d\n", light->effects->effect_info);
//         return light->effects->effect_info;
//     } else {
//         printk("No effects info to play.\n");
//         return NULL;
//     }
// }

uint8_t rgb_middle_get_rgb_info_list_for_current_priority(uint8_t rgb_num)
{
    uint8_t current_priority = get_rgb_info_list_for_current_priority(&rgb_lights[rgb_num]);
    return current_priority;
}
uint8_t rgb_middle_get_rgb_info_list_for_current_type(uint8_t rgb_num)
{
    uint8_t current_type = get_rgb_info_list_for_current_type(&rgb_lights[rgb_num]);
    return current_type;
}

LightEffectNode *get_rgb_info_list_for_current_node(RGB_Light_t *light)
{
    if(light->effects != NULL){
        printk("[middle][rgb]get Playing effect with info,run type:%d, priority:%d, index: %d\n, internal :%d",light->effects->run_type, light->effects->priority, light->effects->effect_info.index,light->effects->effect_info.interval);
    }
    return light->effects;
}

// free rgb info list
void free_rgb_light_effects(RGB_Light_t *light)
{
    LightEffectNode *current = light->effects;
    while (current != NULL) {
        LightEffectNode *next = current->next;
        k_free(current);
        current = next;
    }
    light->effects = NULL;
    light->current_num = 0;
}

static void  rgb_control_isr(void *user_data)
{
    rgb_style_config_t *p_style = (rgb_style_config_t *) user_data;
    rgb_middle_status_t status;
    status = rgb_middle_control_disable(p_style->rgb_num, p_style->type, p_style->pattern, false);
    if (status == RGB_MIDDLE_STATUS_OK_DONE || status == RGB_MIDDLE_STATUS_OK) {
        if (rgb_middle_info[p_style->rgb_num].call_back != NULL) {
            rgb_middle_info[p_style->rgb_num].call_back(rgb_middle_info[p_style->rgb_num].user_data);
        }
    }
}


static void  rgb_control_enable(rgb_style_config_t   *p_style, bool force_option)
{
    uint8_t    rgb_pattern = 0;
    if (rgb_style_config_sys_mode() == RGB_SYSTEM_MODE_LP_TEST) {
        log_rgb_middle_error("[middle][rgb] system in lowpower test mode\r\n", 0);
        return;
    }
    if (p_style == NULL) {
        log_rgb_middle_error("[middle][rgb] rgb_control_enable() input arg is null\r\n", 0);
        return;
    }
    log_rgb_middle_info("[middle][rgb] rgb nums %d\r\n", 1, p_style->rgb_num);
    rgb_pattern      = p_style->rgb_setting->rgb_r.onoff;
    // log_rgb_middle_info("############# RGB %d_R style setting #############\r\n", 1, p_style->rgb_num);
    // rgb_control_printf(&(p_style->rgb_setting->rgb_r));
    // log_rgb_middle_info("############# RGB %d_G style setting #############\r\n", 1, p_style->rgb_num);
    // rgb_control_printf(&(p_style->rgb_setting->rgb_g));
    // log_rgb_middle_info("############# RGB %d_B style setting #############\r\n", 1, p_style->rgb_num);
    // rgb_control_printf(&(p_style->rgb_setting->rgb_b));
    if (p_style->rgb_setting->rgb_r.onoff == RGB_OFF && p_style->rgb_setting->rgb_g.onoff == RGB_OFF && p_style->rgb_setting->rgb_b.onoff == RGB_OFF) {
        bsp_rgb_disable(p_style->rgb_num);
    } else {
        rgb_one_led_style_t *r_rgb = NULL;
        rgb_one_led_style_t *g_rgb = NULL;
        rgb_one_led_style_t *b_rgb = NULL;
        if (p_style->rgb_setting->rgb_r.onoff == RGB_ON) {
            r_rgb = &(p_style->rgb_setting->rgb_r);
        }
        if (p_style->rgb_setting->rgb_g.onoff == RGB_ON) {
            g_rgb = &(p_style->rgb_setting->rgb_g);
        }
        if (p_style->rgb_setting->rgb_b.onoff == RGB_ON) {
            b_rgb = &(p_style->rgb_setting->rgb_b);
        }
        bsp_rgb_disable(p_style->rgb_num);
        if (!force_option) {
            bsp_rgb_register_isr(p_style->rgb_num, rgb_control_isr, p_style);
        }
        bsp_rgb_enable(p_style->rgb_num, r_rgb, g_rgb, b_rgb);
    }

}

static  void    rgb_control_disable(uint8_t rgb_num)
{
    if (rgb_style_config_sys_mode() == RGB_SYSTEM_MODE_LP_TEST) {
        log_rgb_middle_error("[middle][rgb(%d)] system in lowpower test mode\r\n", 1, rgb_num);
        return;
    }
    bsp_rgb_disable(rgb_num);
}


static  bool    rgb_control_is_need_enable(uint8_t rgb_num, rgb_pattern_type_t pattern, uint8_t style_no)
{
    uint8_t current_priority = get_rgb_info_list_for_current_priority(&rgb_lights[rgb_num]);
    if (pattern == current_priority) {
        return true;
    } else {
        return false;
    }
}

static  bool    rgb_control_is_twinkle_mode(rgb_style_config_t *config)
{
    if (config == NULL) {
        return true;
    }
    // if (config->rgb_setting->rgb_r.onoff == 1 && (config->rgb_setting->t1_rising+config->rgb_setting->t1_lightest) > 0 && (config->rgb_setting->t2_falling+config->rgb_setting->t2_darkest) > 0) {
    //     return true;
    // }
    return false;
}


rgb_middle_status_t    rgb_middle_control_enable(uint8_t rgb_num,  uint8_t pattern, uint8_t  style_no, bool force_option)
{

    rgb_style_config_t             *p_style;
    uint32_t                        irq_status;
    bool                            is_need_enable;
    if ((rgb_occupy[rgb_num] != rgb_occupy_none) && (rgb_occupy[rgb_num] != rgb_occupy_rgb)) {
        log_rgb_middle_error("[middle][rgb(%d)] rgb is other %d mode\r\n", 2, rgb_num, rgb_occupy[rgb_num]);
        return RGB_MIDDLE_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    is_need_enable = rgb_control_is_need_enable(rgb_num, pattern, style_no);
    /* If force is true, setting pattern immediately */
    if (force_option) {
        g_immediately_enable = true;
        hal_nvic_restore_interrupt_mask(irq_status);
        goto rgb_setting;
    }
    /* Record pattern */
    rgb_pattern_data_t data_config;
    data_config.index = style_no;
    insert_rgb_info_for_list(&rgb_lights[rgb_num], pattern, data_config, rgb_occupy_rgb);
    rgb_occupy[rgb_num] = rgb_occupy_rgb;
    hal_nvic_restore_interrupt_mask(irq_status);

    /* Get current exist high priority pattern */
    uint8_t current_priority = get_rgb_info_list_for_current_priority(&rgb_lights[rgb_num]);

    /* Need change pattern? */
    if (current_priority < max_list_node_num) {
        if (pattern < current_priority) {
            log_rgb_middle_error("[middle][rgb(%d)] pattern(%d) lower than current(%d)\r\n", 3, rgb_num, pattern, current_priority);
            return RGB_MIDDLE_STATUS_OK_LOW_PATTERN;
        }
    }
rgb_setting:
    log_rgb_middle_info("[middle][rgb(%d)] enable parttern %d, style %d\r\n", 3, rgb_num, pattern, style_no);
    p_style =  rgb_style_config_read(rgb_num, rgb_occupy_rgb, pattern, style_no);
    if (p_style == NULL) {
        log_rgb_middle_error("[middle][rgb(%d)] style not exist in nvdm & rom\r\n", 1, rgb_num);
        return RGB_MIDDLE_STATUS_ERROR;
    }
    /* If new pattern equal previou pattern & rgb is always on or off, then no need update rgb hw */
    if (is_need_enable || rgb_control_is_twinkle_mode(p_style)) {
        rgb_control_enable(p_style, force_option);
    }
    return  RGB_MIDDLE_STATUS_OK;
}

static  bool  g_realtime_enable = false;

int    rgb_middle_control_realtime_enable(uint8_t rgb_num, uint8_t interval, uint8_t *cfg_r, uint8_t *cfg_g, uint8_t *cfg_b)
{
    uint32_t                       irq_status;
    if ((rgb_occupy[rgb_num] != rgb_occupy_none) && (rgb_occupy[rgb_num] != rgb_occupy_realtime_rgb)) {
        log_rgb_middle_error("[middle][rgb(%d)] realtime rgb is other %d mode\r\n", 2, rgb_num, rgb_occupy[rgb_num]);
        return RGB_MIDDLE_STATUS_ERROR;
    }
#ifdef RGB_REAL_TIME_FIFO
    if (g_realtime_enable == false) {
#endif
        rgb_style_config_t             *p_style;
        p_style = rgb_style_config_read(rgb_num, rgb_occupy_realtime_rgb, 0, 0);
        bsp_rgb_register_isr(rgb_num, rgb_control_isr, p_style);  //init
        bsp_rgb_status_t status = bsp_rgb_realtime_enable(rgb_num, interval);
        if (status == BSP_RGB_STATUS_ERROR) {
            return RGB_MIDDLE_STATUS_ERROR;
        } else {
            hal_nvic_save_and_set_interrupt_mask(&irq_status);
            rgb_occupy[rgb_num] = rgb_occupy_realtime_rgb;
            hal_nvic_restore_interrupt_mask(irq_status);
        }
#ifdef RGB_REAL_TIME_FIFO
        g_realtime_enable = true;
    }
#endif
    // log_rgb_middle_error("[middle][rgb(%d)] realtime rgb color R: 0x%x, G: 0x%x, B: 0x%x config\r\n", 4,rgb_num, *cfg_r, *cfg_g, *cfg_b);
    int ret = bsp_rgb_realtime_config(rgb_num, cfg_r, cfg_g, cfg_b);
#ifdef RGB_REAL_TIME_FIFO
    if ((ret >= CONFIG_AIR_REAL_TIME_RGB_MINI_COUNT) && (real_time_rgb_start[rgb_num] == false)) {
#endif
#ifdef RGB_REAL_TIME_ACK
    if (real_time_rgb_start[rgb_num] == false) {
#endif
        bsp_rgb_status_t status = bsp_rgb_realtime_start(rgb_num);
        if (status == BSP_RGB_STATUS_ERROR) {
            return RGB_MIDDLE_STATUS_ERROR;
        } else {
            hal_nvic_save_and_set_interrupt_mask(&irq_status);
            real_time_rgb_start[rgb_num] = true;
            hal_nvic_restore_interrupt_mask(irq_status);
        }
    }
    return ret;
}

static int rgb_load_nvkey_data(uint16_t id, uint16_t offset, uint16_t size, uint8_t *buf)
{
    uint16_t remain = size;
    uint16_t addr = RGB_NVKEY_OFFSET + offset;
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


static rgb_middle_status_t  rgb_middle_control_flash_enable_internal(uint8_t rgb_num, uint16_t id, bool continued)
{
    uint16_t rgb_size = rgb_nvkey[rgb_num].rgb_size | (rgb_nvkey[rgb_num].rgb_size2 << 8);
    if (rgb_nvkey[rgb_num].rgb_size == 0) {
        return RGB_MIDDLE_STATUS_ERROR;
    }
    // log_rgb_middle_error("[middle][rgb(%d)] rgb_middle_control_flash_enable_internal gobal_offset size: %d,rgb_size:%d,continued:%d  \r\n", 4, rgb_num, gobal_offset[rgb_num], rgb_size ,continued);
    if (gobal_offset[rgb_num] < rgb_size) {
        uint16_t read_size = (gobal_offset[rgb_num] + RGB_ONE_SIZE <= rgb_size) ? RGB_ONE_SIZE : (rgb_size - gobal_offset[rgb_num]);
        if (read_size % 3 != 0) {
            read_size -= (read_size % 3);
        }
        if (rgb_nvkey[rgb_num].rgb_data != NULL) {
            k_free(rgb_nvkey[rgb_num].rgb_data);
            rgb_nvkey[rgb_num].rgb_data = NULL;
        }
        rgb_nvkey[rgb_num].rgb_data = k_malloc(read_size);
        if (!rgb_nvkey[rgb_num].rgb_data) {
            return RGB_MIDDLE_STATUS_ERROR;
        }
        if (rgb_load_nvkey_data(id, gobal_offset[rgb_num], read_size, rgb_nvkey[rgb_num].rgb_data) != 0) {
            // log_rgb_middle_error("[middle][rgb(%d)] rgb_middle_control_flash_enable_internal rgb_load_nvkey_data size: %d,rgb_size:%d \r\n", 3, rgb_num, gobal_offset[rgb_num], rgb_size);
            // k_free(rgb_nvkey[rgb_num].rgb_data);
            // rgb_nvkey[rgb_num].rgb_data = NULL;
            return RGB_MIDDLE_STATUS_ERROR;
        }
        gobal_offset[rgb_num] += RGB_ONE_SIZE;
        if (continued == false) {
            bsp_rgb_flash_enable(rgb_num, rgb_nvkey[rgb_num].rgb_data, rgb_nvkey[rgb_num].rgb_interval, read_size, 1);
            bsp_rgb_flash_config_left_size(rgb_num);
        } else {
            bsp_rgb_flash_continued_enable(rgb_num, rgb_nvkey[rgb_num].rgb_data, read_size);
        }
    } else {
        return RGB_MIDDLE_FLASH_DONE;
    }
    return RGB_MIDDLE_STATUS_OK;
}

static void  rgb_middle_control_flash_isr(void *user_data)
{
    rgb_style_config_t *p_style = (rgb_style_config_t *) user_data;
restart:
    rgb_middle_status_t status = rgb_middle_control_flash_enable_internal(p_style->rgb_num, nvkey_id[p_style->rgb_num], true);
    if (status == RGB_MIDDLE_FLASH_DONE) {
        if (flash_repeat[p_style->rgb_num] != 0) {
            if (flash_repeat[p_style->rgb_num] != 255) {
                flash_repeat[p_style->rgb_num]--;
            }
            gobal_offset[p_style->rgb_num] = 0;
            goto restart;
        } else {
            status = rgb_middle_control_disable(p_style->rgb_num, p_style->type, p_style->pattern, false);
            if (status == RGB_MIDDLE_STATUS_OK_DONE) {
                if (rgb_middle_info[p_style->rgb_num].call_back != NULL) {
                    rgb_middle_info[p_style->rgb_num].call_back(rgb_middle_info[p_style->rgb_num].user_data);
                }
            }
        }
    } else if (status == RGB_MIDDLE_STATUS_ERROR) {
        rgb_middle_control_disable(p_style->rgb_num, p_style->type, p_style->pattern, false);
    }
}

rgb_middle_status_t    rgb_middle_control_flash_enable(uint8_t rgb_num, uint16_t id, uint8_t repeat)
{
    // log_rgb_middle_error("[middle][rgb(%d)] rgb_middle_control_flash_enable repeat: %d\n", 2, rgb_num, repeat);
    uint32_t            irq_status;
    rgb_style_config_t  *p_style;
    rgb_middle_status_t rgb_status;
    if ((rgb_occupy[rgb_num] != rgb_occupy_none) && (rgb_occupy[rgb_num] != rgb_occupy_flash_rgb)) {
        log_rgb_middle_error("[middle][rgb(%d)] flash rgb is other %d moder\n", 2, rgb_num, rgb_occupy[rgb_num]);
        return RGB_MIDDLE_STATUS_ERROR;
    }
    // if(rgb_occupy[rgb_num] == rgb_occupy_flash_rgb){
    // rgb_middle_control_disable(rgb_num,rgb_occupy_flash_rgb,RGB_PATTERN_NONE,false);
    // }
    uint32_t size = RGB_NVKEY_OFFSET ;
    nvkey_read_data(id, (uint8_t *)&rgb_nvkey[rgb_num], &size);
    uint16_t rgb_size = rgb_nvkey[rgb_num].rgb_size | (rgb_nvkey[rgb_num].rgb_size2 << 8);
    if (rgb_size == 0) {
        log_rgb_middle_error("[middle][rgb(%d)] flash rgb nvkey size is NULL\n", 1, rgb_num);
        return RGB_MIDDLE_STATUS_ERROR;
    }
    p_style = rgb_style_config_read(rgb_num, rgb_occupy_flash_rgb, 0, 0);
    bsp_rgb_register_isr(rgb_num, rgb_middle_control_flash_isr, p_style);  //register callback
    rgb_status = rgb_middle_control_flash_enable_internal(rgb_num, id, false);
    // log_rgb_middle_error("[middle][rgb(%d)] rgb_middle_control_flash_enable_internal status: %d\n", 2, rgb_num, rgb_status);
    if (rgb_status == RGB_MIDDLE_STATUS_OK) {
        hal_nvic_save_and_set_interrupt_mask(&irq_status);
        flash_repeat[rgb_num] = repeat;
        nvkey_id[rgb_num]   = id;
        rgb_occupy[rgb_num] = rgb_occupy_flash_rgb;
        hal_nvic_restore_interrupt_mask(irq_status);
    }
    return rgb_status;
}

rgb_middle_status_t    rgb_middle_get_running_status(uint8_t rgb_num, rgb_middle_running_status_t *running_status)
{
    uint32_t            irq_status;
    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    hal_nvic_restore_interrupt_mask(irq_status);
    if (rgb_occupy[rgb_num] == rgb_occupy_none) {
        *running_status = RGB_MIDDLE_IDLE;
    } else {
        *running_status = RGB_MIDDLE_RUNNING;
    }
    return RGB_MIDDLE_STATUS_OK;
}

rgb_middle_status_t rgb_middle_register_callback(uint8_t rgb_num, rgb_middle_callback_t callback, void  *user_data)
{
    uint32_t            irq_status;
    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    rgb_middle_info[rgb_num].call_back = callback;
    rgb_middle_info[rgb_num].user_data = user_data;
    hal_nvic_restore_interrupt_mask(irq_status);
    return RGB_MIDDLE_STATUS_OK;
}

rgb_middle_status_t    rgb_middle_control_disable_all(uint8_t rgb_num)
{
    if (rgb_num > CONFIG_AIR_RGB_NUM) {
        printk("Cannot disable rgb effect. rgb current num > config num.\n");
        return RGB_MIDDLE_STATUS_ERROR;
    }
    free_rgb_light_effects(&rgb_lights[rgb_num]);
    rgb_control_disable(rgb_num);
    uint32_t  irq_status;
    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    g_realtime_enable = false;
    rgb_occupy[rgb_num] = rgb_occupy_none;
    real_time_rgb_start[rgb_num] = false;
    k_free(rgb_nvkey[rgb_num].rgb_data);
    rgb_nvkey[rgb_num].rgb_data = NULL;
    gobal_offset[rgb_num] = 0;
    hal_nvic_restore_interrupt_mask(irq_status);
    return RGB_MIDDLE_STATUS_OK;
}

rgb_middle_status_t rgb_middle_control_enable_for_node(uint8_t rgb_num, rgb_pattern_data_t data_config, uint8_t pattern, rgb_run_type_t run_type)
{
    log_rgb_middle_error("[middle][rgb(%d)] rgb_middle_control_enable_for_node,current pattern:%d, current type: %d, rgb_occupy[rgb_num]:%d\n", 4, rgb_num, pattern, run_type, rgb_occupy[rgb_num]);
    if (rgb_occupy[rgb_num] != rgb_occupy_none && pattern == RGB_PATTERN_BG && run_type == rgb_occupy_realtime_rgb) {
        return RGB_MIDDLE_STATUS_ERROR;
    }

    LightEffectNode *play_effect;
    play_effect = get_rgb_info_list_for_current_node(&rgb_lights[rgb_num]);
    if (play_effect != NULL && play_effect->run_type != run_type) {
        rgb_middle_control_disable(rgb_num, play_effect->run_type, play_effect->priority, true);
    }
    if (play_effect != NULL && play_effect->run_type == run_type && play_effect->priority == pattern && play_effect->run_type == rgb_occupy_flash_rgb) {
        rgb_middle_control_disable(rgb_num, play_effect->run_type, play_effect->priority, false);
    }
    insert_rgb_info_for_list(&rgb_lights[rgb_num], pattern, data_config, run_type);
    play_effect = get_rgb_info_list_for_current_node(&rgb_lights[rgb_num]);
    if (play_effect == NULL) {
        return RGB_MIDDLE_STATUS_ERROR;
    }
    rgb_occupy[rgb_num] = play_effect->run_type;
    rgb_middle_status_t rgb_status;
    switch (play_effect->run_type) {
        case rgb_occupy_rgb:
            rgb_status = rgb_middle_control_enable(rgb_num, play_effect->priority, play_effect->effect_info.index, false);
            break;
        case rgb_occupy_flash_rgb:
            rgb_status = rgb_middle_control_flash_enable(rgb_num, play_effect->effect_info.index, play_effect->effect_info.interval);
            break;
        case rgb_occupy_realtime_rgb:
            rgb_status = rgb_middle_control_realtime_enable(rgb_num, play_effect->effect_info.interval, play_effect->effect_info.cfg_r, play_effect->effect_info.cfg_g, play_effect->effect_info.cfg_b);
            break;
        default:
            rgb_status = RGB_MIDDLE_STATUS_ERROR;
            break;
    }
    return rgb_status;
}

rgb_middle_status_t    rgb_middle_control_disable(uint8_t rgb_num, rgb_run_type_t type, uint8_t  pattern, bool force_option)
{
    log_rgb_middle_error("[middle][rgb(%d)] rgb disable,current pattern:%d, current type %d, rgb_occupy[rgb_num]: %d\n", 4, rgb_num, pattern, type, rgb_occupy[rgb_num]);
    uint32_t            irq_status;
    if (rgb_occupy[rgb_num] != type) {
        log_rgb_middle_error("[middle][rgb(%d)] rgb disable error,current mode:%d, disable mode %d\n", 3, rgb_num, rgb_occupy[rgb_num], type);
        return RGB_MIDDLE_STATUS_ERROR;
    }
    LightEffectNode *play_effect;
    play_effect = get_rgb_info_list_for_current_node(&rgb_lights[rgb_num]);
    if(play_effect == NULL){
        return RGB_MIDDLE_STATUS_OK;
    }

    if (rgb_occupy[rgb_num] == rgb_occupy_rgb) {
        rgb_style_config_t    *p_style = NULL;
        hal_nvic_save_and_set_interrupt_mask(&irq_status);
        // If force_disable is true, need switch pattern
        if (force_option) {
            g_immediately_enable = false;
            hal_nvic_restore_interrupt_mask(irq_status);
            rgb_control_disable(rgb_num);
            return RGB_MIDDLE_STATUS_OK;
        } else {
            // Check setting pattern priority
            delete_rgb_info(&rgb_lights[rgb_num], pattern);
            log_rgb_middle_error("[middle][rgb(%d)] normal rgb disable, pattern:%d, current pattern %d\n", 3, rgb_num, pattern, play_effect->priority);
            if (pattern < play_effect->priority) {
                hal_nvic_restore_interrupt_mask(irq_status);
                log_rgb_middle_info("[middle][rgb(%d)] pattern(%d) priority low than current(%d)\r\n", 3, rgb_num, pattern, play_effect->priority);
                return RGB_MIDDLE_STATUS_OK_LOW_PATTERN;
            }
        }
        hal_nvic_restore_interrupt_mask(irq_status);
        if (g_immediately_enable) {
            return RGB_MIDDLE_STATUS_OK;
        }
        play_effect = get_rgb_info_list_for_current_node(&rgb_lights[rgb_num]);

        if (play_effect != NULL && play_effect->priority < max_list_node_num && play_effect->run_type == rgb_occupy_rgb) {
            // Get low priorty pattern setting and enable
            p_style = rgb_style_config_read(rgb_num, rgb_occupy_rgb, play_effect->priority, play_effect->effect_info.index);
            rgb_control_enable(p_style, 0);
            log_rgb_middle_info("[middle][rgb(%d)] after play normal, normal pattern %d be activated(style %d, type %d), by disable pattern %d\r\n", 5,
                                rgb_num,
                                play_effect->priority,
                                play_effect->effect_info.index,
                                play_effect->run_type,
                                pattern);
            return RGB_MIDDLE_STATUS_OK;
        } else if (play_effect != NULL && play_effect->priority < max_list_node_num && play_effect->run_type == rgb_occupy_flash_rgb) {
            // Get low priorty pattern setting and enable
            log_rgb_middle_info("[middle][rgb(%d)] after play normal, flash pattern %d be activated(style %d, type %d), by disable pattern %d\r\n", 5,
                                rgb_num,
                                play_effect->priority,
                                play_effect->effect_info.index,
                                play_effect->run_type,
                                pattern);
            rgb_control_disable(rgb_num);
            k_free(rgb_nvkey[rgb_num].rgb_data);
            rgb_nvkey[rgb_num].rgb_data = NULL;
            gobal_offset[rgb_num] = 0;
            rgb_occupy[rgb_num] = rgb_occupy_flash_rgb;
            rgb_middle_control_flash_enable(rgb_num, play_effect->effect_info.index, play_effect->effect_info.interval);
            return RGB_MIDDLE_STATUS_OK;
        } else {
            log_rgb_middle_info("[middle][rgb(%d)] no active pattern, normal rgb will be turn off \r\n", 1, rgb_num);
            rgb_control_disable(rgb_num);
        }
    } else if (rgb_occupy[rgb_num] == rgb_occupy_flash_rgb) {
        // If force_disable is true, need switch pattern
        hal_nvic_save_and_set_interrupt_mask(&irq_status);
        if (force_option) {
            g_immediately_enable = false;
            hal_nvic_restore_interrupt_mask(irq_status);
            rgb_control_disable(rgb_num);
            return RGB_MIDDLE_STATUS_OK;
        } else {
            // Check setting pattern priority
            delete_rgb_info(&rgb_lights[rgb_num], pattern);
            log_rgb_middle_info("[middle][rgb(%d)] flash rgb disable, pattern(%d), current(%d)\r\n", 3, rgb_num, pattern, play_effect->priority);
            if (pattern < play_effect->priority) {
                hal_nvic_restore_interrupt_mask(irq_status);
                log_rgb_middle_info("[middle][rgb(%d)] pattern(%d) priority low than current(%d)\r\n", 3, rgb_num, pattern, play_effect->priority);
                return RGB_MIDDLE_STATUS_OK_LOW_PATTERN;
            }
        }
        hal_nvic_restore_interrupt_mask(irq_status);
        play_effect = get_rgb_info_list_for_current_node(&rgb_lights[rgb_num]);
        // log_rgb_middle_info("[middle][rgb(%d)] mode:%d pattern, flash rgb will be turn off \r\n", 2, rgb_num, rgb_occupy[rgb_num]);
        if (play_effect != NULL && play_effect->priority < max_list_node_num && play_effect->run_type == rgb_occupy_flash_rgb) {
            // log_rgb_middle_info("[middle][rgb(%d)] curren_pattern:%d pattern, flash rgb after play \r\n", 2, rgb_num, curren_pattern);
            // Get low priorty pattern setting and enable
            rgb_middle_control_flash_enable(rgb_num, play_effect->effect_info.index, play_effect->effect_info.interval);
            log_rgb_middle_info("[middle][rgb(%d)] after play flash, pattern %d be activated(style %d, type %d), by disable pattern %d one\r\n", 5,
                                rgb_num,
                                play_effect->priority,
                                play_effect->effect_info.index,
                                play_effect->run_type,
                                pattern);
            return RGB_MIDDLE_STATUS_OK;
        } else {
            log_rgb_middle_info("[middle][rgb(%d)] mode:%d pattern, flash rgb will be turn off \r\n", 2, rgb_num, rgb_occupy[rgb_num]);
            rgb_control_disable(rgb_num);
            k_free(rgb_nvkey[rgb_num].rgb_data);
            rgb_nvkey[rgb_num].rgb_data = NULL;
        }
    } else if (rgb_occupy[rgb_num] == rgb_occupy_realtime_rgb) {
        if(pattern == 0){
            pattern = 15;
            log_rgb_middle_info("[middle][rgb(%d)] mode:%d pattern, real time rgb fifo empty, rgb will be turn off \r\n", 3, rgb_num, rgb_occupy[rgb_num], pattern);
        }
        delete_rgb_info(&rgb_lights[rgb_num], pattern);
        log_rgb_middle_info("[middle][rgb(%d)] mode:%d pattern:%d real time rgb will be turn off \r\n", 3, rgb_num, rgb_occupy[rgb_num], pattern);
        g_realtime_enable = false;
        real_time_rgb_start[rgb_num] = false;
        play_effect = get_rgb_info_list_for_current_node(&rgb_lights[rgb_num]);
        if (play_effect != NULL && play_effect->run_type == rgb_occupy_flash_rgb) {
            log_rgb_middle_info("[middle][rgb(%d)] after play real time, flash current pattern %d,current type %d be activated(style %d), by disable pattern %d one\r\n", 6,
                                rgb_num,
                                play_effect->priority,
                                play_effect->run_type,
                                play_effect->effect_info.index,
                                pattern);
            rgb_control_disable(rgb_num);
            k_free(rgb_nvkey[rgb_num].rgb_data);
            rgb_nvkey[rgb_num].rgb_data = NULL;
            gobal_offset[rgb_num] = 0;
            rgb_occupy[rgb_num] = rgb_occupy_flash_rgb;
            rgb_middle_control_flash_enable(rgb_num, play_effect->effect_info.index, play_effect->effect_info.interval);
            rgb_occupy[rgb_num] = rgb_occupy_flash_rgb;
            return RGB_MIDDLE_STATUS_OK;
        } else if (play_effect != NULL && play_effect->run_type == rgb_occupy_rgb) {
            log_rgb_middle_info("[middle][rgb(%d)] after play real time, normal current pattern %d, type %d be activated(style %d), by disable pattern %d one\r\n", 6,
                                rgb_num,
                                play_effect->priority,
                                play_effect->run_type,
                                play_effect->effect_info.index,
                                pattern);
            rgb_style_config_t    *p_style = NULL;
            p_style = rgb_style_config_read(rgb_num, rgb_occupy_rgb, play_effect->priority, play_effect->effect_info.index);
            rgb_control_enable(p_style, 0);
            rgb_occupy[rgb_num] = rgb_occupy_rgb;
            return RGB_MIDDLE_STATUS_OK;
        }
        rgb_control_disable(rgb_num);
        g_realtime_enable = false;
    }

    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    g_realtime_enable = false;
    real_time_rgb_start[rgb_num] = false;
    rgb_occupy[rgb_num] = rgb_occupy_none;
    k_free(rgb_nvkey[rgb_num].rgb_data);
    rgb_nvkey[rgb_num].rgb_data = NULL;
    gobal_offset[rgb_num] = 0;
    hal_nvic_restore_interrupt_mask(irq_status);
    return RGB_MIDDLE_STATUS_OK_DONE;
}