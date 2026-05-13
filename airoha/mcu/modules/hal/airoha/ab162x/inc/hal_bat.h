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

#ifndef __HAL_BAT_H__
#define __HAL_BAT_H__

#include "hal_platform.h"
#include "autoconf.h"

#ifndef PACKED
#define PACKED  __attribute__((packed))
#endif

typedef enum {
    BAT_DET_DISABLE             = 0,
    BAT_DET_INT_VBAT            = 1,
    BAT_DET_EXT_GPIO            = 2,
} bat_det_type_t;

typedef struct {
    uint16_t volt;
    uint16_t rsv;
} PACKED bat_stru_t;

//0x2020
typedef struct {
    uint8_t kflag;
    uint8_t sel;
    uint16_t adc_ctrl;
    uint16_t adc_pin;
    uint16_t settle_time;
    uint16_t r6215;
    uint16_t r6217;
    uint16_t rsv[15];
} PACKED bat_adc_t;

//0x2021
typedef struct {
    uint8_t kflag;
    bat_stru_t full_bat;
    bat_stru_t rsv2;
    bat_stru_t sd_bat;
    bat_stru_t vbat[18];
} PACKED bat_volt_t;

typedef enum {
    BAT_STATUS_INVALID_PARAMETER  = -1,     /* bat error invalid parameter */
    BAT_STATUS_ERROR              = 0,      /* bat undefined error */
    BAT_STATUS_SUCCESS            = 1       /* bat function ok */
}bat_status_t;

typedef enum {
    BAT_OFF                       = 0,
    BAT_ON                        = 1,
} bat_operate_t;

typedef enum {
    BAT_CB_VBAT                   = 0,
    BAT_CB_TEMP                   = 1,
    BAT_CB_MAX                    = 2,
} bat_cb_t;

typedef enum{
    BAT_USER_PMU                  = 0,
    BAT_USER_BM                   = 1,
    BAT_USER_APP                  = 2,
    BAT_USER_MAX                  = 3,
} bat_user_t;

typedef struct {
    void (*bat_callback)(void *user_data);
} bat_func_t;

typedef void (*bat_callback_t)(void *user_data);
extern bat_func_t bat_cb_func[BAT_CB_MAX][BAT_USER_MAX];

/* BAT COMMON */
void bat_assert(void);
int32_t bat_round(int32_t val1, int32_t val2);
uint16_t bat_lerp(uint16_t volt1, uint16_t adc1, uint16_t volt2, uint16_t adc2, uint16_t volt);

/* BAT API */
uint16_t bat_get_vbat(void);
uint8_t bat_get_soc(uint16_t vbat);
uint16_t bat_get_sd_bat(void);
uint16_t bat_get_full_bat(void);
void bat_get_pnzcv(void);

/* BAT INIT */
void bat_init(void);

/* BAT INFO */

#endif /* __HAL_BAT_H__ */
