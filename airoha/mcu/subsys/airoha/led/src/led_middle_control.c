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

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hal.h"
#include "led_middle_control.h"
#include "led_control_style_cfg.h"
#include "bsp_led.h"
/***************************************** Private variable********************************************/
static  uint32_t                g_immediately_enable = false;
static  led_pattern_record_t    history_record[LED_NUM_MAX][LED_PATTERN_NONE];
static  led_middle_info_t       led_middle_info[LED_NUM_MAX];

#define     GET_CURRENT_PATTERN(x)               led_middle_control_get_active_pattern(x)

#if 0
#define log_led_middle_info(fmt, cnt, ...)     log_hal_msgid_info("[hal][rtc] " fmt, cnt, ##__VA_ARGS__)
#define log_led_middle_warning(fmt, cnt, ...)  log_hal_msgid_warning("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#define log_led_middle_error(fmt, cnt, ...)    log_hal_msgid_error("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#else
#define log_led_middle_info(fmt, cnt, ...)     printk(fmt, ##__VA_ARGS__)
#define log_led_middle_warning(fmt, cnt, ...)  printk(fmt, ##__VA_ARGS__)
#define log_led_middle_error(fmt, cnt, ...)    printk(fmt, ##__VA_ARGS__)
#endif

led_pattern_type_t  led_middle_control_get_active_pattern(led_num_t led_num);

static  void    led_control_printf(one_led_style_t *p_style)
{
    log_led_middle_info("[middle][led] led      on/off :%d\r\n", 1, p_style->onoff);
    log_led_middle_info("[middle][led] t0              :%d\r\n", 1, p_style->t0);
    log_led_middle_info("[middle][led] t1 rising       :%d\r\n", 1, p_style->t1_rising);
    log_led_middle_info("[middle][led] t1 lightest     :%d\r\n", 1, p_style->t1_lightest);
    log_led_middle_info("[middle][led] t2 falling      :%d\r\n", 1, p_style->t2_falling);
    log_led_middle_info("[middle][led] t2 darkest      :%d\r\n", 1, p_style->t2_darkest);
    log_led_middle_info("[middle][led] t3              :%d\r\n", 1, p_style->t3);
    log_led_middle_info("[middle][led] t1t2   repeat   :%d\r\n", 1, p_style->repeat_t1t2);
    log_led_middle_info("[middle][led] extend repeat   :%d\r\n", 1, p_style->repeat_ext);
    log_led_middle_info("[middle][led] brightness      :%d\r\n", 1, p_style->brightness);
    log_led_middle_info("[middle][led] start brightness:%d\r\n", 1, p_style->start_brightness);
    log_led_middle_info("[middle][led] end brightness  :%d\r\n", 1, p_style->end_brightness);
}

static void  led_control_isr(void *user_data){
    led_style_config_t *p_style =(led_style_config_t *) user_data;
    led_middle_status_t status;
    status = led_middle_control_disable(p_style->led_num,p_style->pattern,false);
    if(status == LED_MIDDLE_STATUS_OK_DONE){
        if(led_middle_info[p_style->led_num].call_back != NULL){
            led_middle_info[p_style->led_num].call_back(led_middle_info[p_style->led_num].user_data);
        }
    }
}


static void  led_control_enable(led_style_config_t   *p_style,bool force_option)
{
    uint8_t    led_pattern = 0;
    if (led_style_config_sys_mode() == LED_SYSTEM_MODE_LP_TEST) {
        log_led_middle_error("[middle][led] system in lowpower test mode\r\n", 0);
        return;
    }
    if (p_style == NULL) {
        log_led_middle_error("[middle][led] led_control_enable() input arg is null\r\n", 0);
        return;
    }
    log_led_middle_info("[middle][led] led nums %d\r\n", 1, p_style->led_num);
    led_pattern      = p_style->led_setting->onoff;
    log_led_middle_info("############# Led %d style setting #############\r\n", 1, p_style->led_num);
    led_control_printf(p_style->led_setting);
    if (led_pattern == LED_OFF) {
        bsp_led_disable(p_style->led_num);
    } else if (led_pattern == LED_ON) {
        bsp_led_disable(p_style->led_num);
        if(!force_option){
            bsp_led_register_isr(p_style->led_num,led_control_isr,p_style);
        }
        bsp_led_enable(p_style->led_num, p_style->led_setting);
    }
}

static  void    led_control_disable(led_num_t led_num)
{
    if (led_style_config_sys_mode() == LED_SYSTEM_MODE_LP_TEST) {
        log_led_middle_error("[middle][led(%d)] system in lowpower test mode\r\n", 1, led_num);
        return;
    }
    bsp_led_disable(led_num);
}


static  bool    led_control_is_need_enable(led_num_t led_num, led_pattern_type_t pattern, uint8_t style_no)
{
    led_pattern_type_t              curren_pattern;

    curren_pattern = GET_CURRENT_PATTERN(led_num);

    if (pattern == curren_pattern && history_record[led_num][pattern].enable == true && history_record[led_num][pattern].style_no == style_no) {
        return false;
    } else {
        return true;
    }
}

static  bool    led_control_is_twinkle_mode(led_style_config_t *config)
{
    if (config == NULL) {
        return true;
    }
    if (config->led_setting->onoff == 1 && (config->led_setting->t1_rising+config->led_setting->t1_lightest) > 0 && (config->led_setting->t2_falling+config->led_setting->t2_darkest) > 0) {
        return true;
    }
    return false;
}

led_pattern_type_t  led_middle_control_get_active_pattern(led_num_t led_num)
{
    if (true == history_record[led_num][LED_PATTERN_FILTER].enable) {
        return LED_PATTERN_FILTER;
    } else if (true == history_record[led_num][LED_PATTERN_FG].enable) {
        return LED_PATTERN_FG;
    } else if (true == history_record[led_num][LED_PATTERN_BG].enable) {
        return LED_PATTERN_BG;
    }
    return LED_PATTERN_NONE;
}


led_middle_status_t    led_middle_control_enable(led_num_t led_num,  led_pattern_type_t pattern, uint8_t  style_no, bool force_option){

    led_pattern_type_t              curren_pattern;
    led_style_config_t             *p_style;
    uint32_t                        irq_status;
    bool                            is_need_enable;
    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    is_need_enable = led_control_is_need_enable(led_num,pattern, style_no);
    /* If force is true, setting pattern immediately */
    if (force_option) {
        g_immediately_enable = true;
        hal_nvic_restore_interrupt_mask(irq_status);
        goto led_setting;
    }
    /* Record pattern */
    history_record[led_num][pattern].enable  = true;
    history_record[led_num][pattern].pattern = pattern;
    history_record[led_num][pattern].style_no = style_no;
    hal_nvic_restore_interrupt_mask(irq_status);

    /* Get current exist high priority pattern */
    curren_pattern = GET_CURRENT_PATTERN(led_num);

    /* Need change pattern? */
    if (curren_pattern < LED_PATTERN_NONE) {
        if (pattern < curren_pattern) {
            log_led_middle_error("[middle][led(%d)] pattern(%d) lower than current(%d)\r\n", 3, led_num, pattern, curren_pattern);
            return LED_MIDDLE_STATUS_OK_LOW_PATTERN;
        }
    }
    led_setting:
        log_led_middle_info("[middle][led(%d)] enable parttern %d, style %d\r\n", 3, led_num, pattern, style_no);
        p_style =  led_style_config_read(led_num, pattern, style_no);
        if (p_style == NULL) {
            log_led_middle_error("[middle][led(%d)] style not exist in nvdm & rom\r\n", 1, led_num);
            return LED_MIDDLE_STATUS_ERROR;
        }
        /* If new pattern equal previou pattern & led is always on or off, then no need update led hw */
        if (is_need_enable || led_control_is_twinkle_mode(p_style)) {
            led_control_enable(p_style, force_option);
        }
    return  LED_MIDDLE_STATUS_OK;
}

led_middle_status_t    led_middle_control_disable(led_num_t led_num, led_pattern_type_t  pattern, bool force_option)
{
    led_pattern_type_t  curren_pattern;
    uint32_t            irq_status;
    led_style_config_t    *p_style = NULL;

    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    /* If force_disable is true, need switch pattern */
    if (force_option) {
        g_immediately_enable = false;
    } else {
        /* Check setting pattern priority */
        curren_pattern = GET_CURRENT_PATTERN(led_num);
        history_record[led_num][pattern].enable = false;
        if (pattern < curren_pattern) {
            hal_nvic_restore_interrupt_mask(irq_status);
            log_led_middle_info("[middle][led(%d)] pattern(%d) priority low than current(%d)\r\n", 3, led_num, pattern, curren_pattern);
            return LED_MIDDLE_STATUS_OK_LOW_PATTERN;
        }
    }
    hal_nvic_restore_interrupt_mask(irq_status);

    if (g_immediately_enable) {
        return LED_MIDDLE_STATUS_OK;
    }
    curren_pattern = GET_CURRENT_PATTERN(led_num);
    if (curren_pattern < LED_PATTERN_NONE) {
        /* Get low priorty pattern setting and enable */
        p_style = led_style_config_read(led_num, history_record[led_num][curren_pattern].pattern, history_record[led_num][curren_pattern].style_no);
        led_control_enable(p_style, 0);
        log_led_middle_info("[middle][led(%d)] pattern %d be activated(style %d), by disable pattern %d one\r\n", 4,
                         led_num,
                         history_record[led_num][curren_pattern].pattern,
                         history_record[led_num][curren_pattern].style_no,
                         pattern);
    } else {
        log_led_middle_info("[middle][led(%d)] no active pattern, led will be turn off \r\n", 1,led_num);
        led_control_disable(led_num);
        return LED_MIDDLE_STATUS_OK_DONE;
    }
    return LED_MIDDLE_STATUS_OK;
}

led_middle_status_t    led_middle_get_running_status(led_num_t led_num, led_middle_running_status_t *running_status){
    led_pattern_type_t  curren_pattern;
    uint32_t            irq_status;
    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    curren_pattern = GET_CURRENT_PATTERN(led_num);
    hal_nvic_restore_interrupt_mask(irq_status);
    if(LED_PATTERN_NONE==curren_pattern){
        *running_status = LED_MIDDLE_IDLE;
    }else{
        *running_status = LED_MIDDLE_RUNNING;
    }
    return LED_MIDDLE_STATUS_OK;
}
led_middle_status_t led_middle_register_callback(led_num_t led_num,led_middle_callback_t callback, void  *user_data){
    uint32_t            irq_status;
    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    led_middle_info[led_num].call_back = callback;
    led_middle_info[led_num].user_data = user_data;
    hal_nvic_restore_interrupt_mask(irq_status);
    return LED_MIDDLE_STATUS_OK;
}