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
#include "bsp_argb.h"
#include "argb_control_style_cfg.h"
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

static argb_style_config_t   g_current_style;


uint8_t test_style_1[20] = {
    10,
    10,
    20,
    20,
    30,
    30,
    40,
    40,
    50,
    50,
    60,
    60,
    70,
    70,
    80,
    80,
    90,
    90,
    100,
    100,
};


/******************************************Public Function**********************************************/

argb_style_config_t    *argb_style_config_read(uint8_t type, uint8_t  pattern, uint8_t  repeat)
{
    if (type == argb_occupy_normal) {
        g_current_style.pattern = pattern;
        g_current_style.repeat = repeat;
    } else {                                               //real_time && flash
        g_current_style.repeat = 0;
        g_current_style.pattern = 0;
    }
    g_current_style.type = type;
    return &g_current_style;
}


// #endif
