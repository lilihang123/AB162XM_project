/* Copyright Statement:
 *
 * (C) 2024  Airoha Technology Corp. All rights reserved.
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
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
 * RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
 * TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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
 

#ifndef __APP_RGB_H__
#define __APP_RGB_H__

/* Includes ------------------------------------------------------------------*/
#include "application.h"

/* Public macro --------------------------------------------------------------*/
#if defined(CONFIG_AIR_RGB_NUM)
    #define APP_RGB_COLOR (3 * CONFIG_AIR_RGB_NUM)
    #define APP_RGB_DATA  CONFIG_AIR_RGB_NUM)
#else
    #define APP_RGB_COLOR  3
    #define APP_RGB_DATA   1
#endif

#if defined(CONFIG_AIR_REAL_TIME_RGB_MINI_COUNT)
    #define APP_RGB_MINI_COUNT  (CONFIG_AIR_REAL_TIME_RGB_MINI_COUNT)
    #define APP_RGB_MAX_COUNT   10
#else
    #define APP_RGB_MINI_COUNT  3
    #define APP_RGB_MAX_COUNT   10
#endif

#define TEST_FLASH         0

/* Public typedef ------------------------------------------------------------*/
typedef struct {
    uint8_t setting;
    uint8_t num;
    uint8_t interval;
    uint8_t count;
    uint8_t color[APP_RGB_COLOR];  //3*n
} __attribute__((__packed__)) T_SET_RGB_INFO_S;

typedef enum {
	APP_RGB_CONTINUE = 0x00,
	APP_RGB_START = 0x80,
	APP_RGB_STOP = 0xFF
} app_rgb_action_t;

/* Public variables ----------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void app_rgb_init();






#endif

