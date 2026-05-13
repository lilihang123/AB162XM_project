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

// #ifdef AIR_RGB_ENABLE

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// #include "nvkey.h"
// #include "hal.h"
#include "bsp_rgb.h"
#include "rgb_control_style_cfg.h"
// #include "nvkey_id_list.h"
// #include "syslog.h"



//#define     RGB_CONFIG_DEBUG_EN
#define     RGB_MIDDLE_RD_BUFF_SZ  1024

#ifdef     RGB_CONFIG_DEBUG_EN
#define     log_rgb_cfg_info(fmt, cnt, ...)   log_rgb_info(fmt, cnt, ##__VA_ARGS__)
#else
#define     log_rgb_cfg_info(...)
#endif
#define     log_rgb_cfg_error(fmt, cnt, ...)  log_rgb_error(fmt, cnt, ##__VA_ARGS__)


log_create_module(rgb_log, PRINT_LEVEL_INFO);
/*****************************************Private variable********************************************************/
static bool                 g_rgbcfg_in_nvdm = false;
static rgb_style_config_t   g_current_style[CONFIG_AIR_RGB_NUM];
static uint8_t              *g_pnvdm_mem  = NULL;
static uint8_t              g_sys_mode   = RGB_SYSTEM_MODE_NORMAL;

/* default value for app rgb, when no configure data in NVDM */
__attribute__((weak)) one_rgb_style_t   rgb_default_pattern_setting[] = {
    /* t0,  t1_rising   t1_lightest     t2_falling     t2_darkest  t3   repeat_t1t2  repeat_ext  brightness  start_brightness  end_brightness  onoff*/
    /* no.0  Constant on */
    {
        { 0,       0,      10000,              0,             0,       0,       1,          100,        125,          0,                 0,        RGB_ON },
        { 0,       0,      10000,              0,             0,       0,       1,          100,        125,          0,                 0,        RGB_ON },
        { 0,       0,      10000,              0,             0,       0,       1,          100,        125,          0,                 0,        RGB_ON },
    },
    /* no.1  1-time flash */
    {
        { 0,     200,        100,            200,             0,    2500,       1,          255,        150,          0,                 0,        RGB_ON },
        { 0,     200,        100,            200,             0,    2500,       1,          255,        150,          0,                 0,        RGB_ON },
        { 0,     200,        100,            200,             0,    2500,       1,          255,        150,          0,                 0,        RGB_ON },
    },
    /* no.2  2-times flash  */
    {
        { 0,     200,        100,            200,           500,       0,       2,            1,        150,          0,                 0,        RGB_ON },
        { 0,     200,        100,            200,           500,       0,       2,            1,        150,          0,                 0,        RGB_ON },
        { 0,     200,        100,            200,           500,       0,       2,            1,        150,          0,                 0,        RGB_ON },
    },
    /* no.3  Continuous 2-times flash */
    {
        { 0,     200,        100,            200,           500,    1000,       2,          255,        150,          0,                 0,        RGB_ON },
        { 0,     200,        100,            200,           500,    1000,       2,          255,        150,          0,                 0,        RGB_ON },
        { 0,     200,        100,            200,           500,    1000,       2,          255,        150,          0,                 0,        RGB_ON },
    },
    /* no.4  Continuous slow breathing light */
    {
        { 0,     500,        500,            500,             0,       0,      10,          255,        150,          0,                 0,        RGB_ON },
        { 0,     500,        500,            500,             0,       0,      10,          255,        150,          0,                 0,        RGB_ON },
        { 0,     500,        500,            500,             0,       0,      10,          255,        150,          0,                 0,        RGB_ON },
    },
    /* no.5  Continuous quick flash */
    {
        { 0,     200,        100,              0,           200,       0,      10,          255,        150,          0,                 0,        RGB_ON },
        { 0,     200,        100,              0,           200,       0,      10,          255,        150,          0,                 0,        RGB_ON },
        { 0,     200,        100,              0,           200,       0,      10,          255,        150,          0,                 0,        RGB_ON },
    },
    /* no.6  1-time quick flash */
    {
        { 0,     200,        100,              0,           200,       0,       1,            1,        150,          0,                 0,        RGB_ON },
        { 0,     200,        100,              0,           200,       0,       1,            1,        150,          0,                 0,        RGB_ON },
        { 0,     200,        100,              0,           200,       0,       1,            1,        150,          0,                 0,        RGB_ON },
    },
    /* no.7  2-times quick flash */
    {
        { 0,     200,        100,              0,           200,       0,       2,            1,        150,          0,                 0,        RGB_ON },
        { 0,     200,        100,              0,           200,       0,       2,            1,        150,          0,                 0,        RGB_ON },
        { 0,     200,        100,              0,           200,       0,       2,            1,        150,          0,                 0,        RGB_ON },
    },
    /* no.8  No light (0.5s)*/
    {
        { 0,       0,          0,              0,             0,     500,       1,            1,          0,          0,                 0,        RGB_ON },
        { 0,       0,          0,              0,             0,     500,       1,            1,          0,          0,                 0,        RGB_ON },
        { 0,       0,          0,              0,             0,     500,       1,            1,          0,          0,                 0,        RGB_ON },
    },
    /* no.9  No light (1s)*/
    {
        { 0,       0,          0,              0,             0,    1000,       1,            1,          0,          0,                 0,        RGB_ON },
        { 0,       0,          0,              0,             0,    1000,       1,            1,          0,          0,                 0,        RGB_ON },
        { 0,       0,          0,              0,             0,    1000,       1,            1,          0,          0,                 0,        RGB_ON },
    },
};

/******************************************Public Function**********************************************/

// void    rgb_style_config_deinit()
// {
//     if (g_rgbcfg_in_nvdm) {
//         vPortFree(g_pnvdm_mem);
//         g_rgbcfg_in_nvdm = false;
//     }
// }


// void    rgb_style_config_init()
// {
//     nvkey_status_t  status;
//     uint32_t        size    = RGB_MIDDLE_RD_BUFF_SZ;
//     uint32_t        unit_sz = 0;
//     uint8_t        *temp  = NULL;
//     uint32_t        tsize = 1;
//     /* If have initialized, then return */
//     if (g_rgbcfg_in_nvdm) {
//         return;
//     }
//     nvdm_init();
//     memset(&g_current_style, 0, sizeof(g_current_style));
//     temp = (uint8_t *)pvPortMalloc(RGB_MIDDLE_RD_BUFF_SZ);
//     if (temp == NULL) {
//         log_rgb_cfg_error("[rgb][cfg] rgb style config init,malloc read buf fail\r\n", 0);
//         goto error_2;
//     }
//     /* Read rgb parttern */
//     status = nvkey_read_data(NVID_RGB_MIDDLE_PATTERN, temp, &size);
//     if (status != NVKEY_STATUS_OK) {
//         log_rgb_cfg_error("[rgb][cfg] read rgb setting from nvdm fairgb(%d)\r\n", 1, status);
//         goto error_2;
//     }
//     /* Read system mode */
//     status = nvkey_read_data(NVID_APP_SYSTEM_MODE_SETTING, &g_sys_mode, &tsize);
//     if (status != NVKEY_STATUS_OK) {
//         log_rgb_cfg_error("[rgb][cfg] read system mode from nvdm fairgb(%d)\r\n", 1, status);
//         g_sys_mode = RGB_SYSTEM_MODE_NORMAL;
//     }
//     /* Check data is valid */
//     unit_sz = sizeof(one_led_style_t);
//     if (size == 0 || (size - 1) % unit_sz != 0) {
//         log_rgb_cfg_error("[rgb][cfg] read nvdm data size invalid(%d,expect %d*n)\r\n", 2, (int)size, (int)unit_sz);
//         goto error_2;;
//     }
//     /* Adapter buffer to smaller one */
//     g_pnvdm_mem = (uint8_t *)pvPortMalloc(size + 5);
//     if (g_pnvdm_mem == NULL) {
//         log_rgb_cfg_error("[rgb][cfg] rgb style config init,malloc cfg buf fail\r\n", 0);
//         goto error_1;
//     }
//     memcpy(g_pnvdm_mem, temp, size);
//     vPortFree(temp);
//     g_rgbcfg_in_nvdm = true;
//     log_rgb_cfg_error("[rgb][cfg] read nvdm succ, size %d\r\n", 1, size);
//     return;

// error_1:
//     vPortFree(g_pnvdm_mem);
// error_2:
//     vPortFree(temp);
// }


rgb_style_config_t    *rgb_style_config_read(uint8_t rgb_num, rgb_run_type_t type, uint8_t    pattern, uint8_t  style_no)
{
    one_rgb_style_t *pstyle = NULL;
    if (type == rgb_occupy_rgb) {
        if (g_rgbcfg_in_nvdm == true) {
            pstyle = (one_rgb_style_t *)&g_pnvdm_mem[1];
            g_current_style[rgb_num].rgb_setting = pstyle;
        } else {
            g_current_style[rgb_num].rgb_setting = &rgb_default_pattern_setting[style_no];
        }
        g_current_style[rgb_num].pattern = pattern;
    } else {                                               //real_time && flash
        g_current_style[rgb_num].rgb_setting = NULL;
        g_current_style[rgb_num].pattern = 0;
    }
    g_current_style[rgb_num].rgb_num = rgb_num;
    g_current_style[rgb_num].type = type;
    return &g_current_style[rgb_num];
}

uint8_t rgb_style_config_sys_mode()
{
    return g_sys_mode;
}

// #endif
