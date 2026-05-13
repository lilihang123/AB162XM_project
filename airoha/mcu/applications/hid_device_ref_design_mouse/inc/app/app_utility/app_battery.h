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

#ifndef __APP_BATTERY_H__
#define __APP_BATTERY_H__

#include "application.h"

/* Public typedef ------------------------------------------------------------*/
typedef struct {
    uint16_t vbat;
    uint8_t soc;
    uint8_t chg_state;
    uint8_t chg_en_sta;
    uint8_t chg_exist;
    uint8_t power_status;
    uint8_t init_flag;
} T_APP_BATTERY_INFO_S;

typedef enum {
    APP_BAT_VBAT = 0,
    APP_BAT_SOC,
    //APP_BAT_TEMP,
    APP_BAT_CHG_EXIST,
    APP_BAT_CHG_STA,
    APP_BAT_CHG_EN_STA,
    //APP_BAT_CHG_CURR,
    APP_BAT_CHG_IN,
    APP_BAT_CHG_OUT,
    APP_BAT_CHG_EOC,
    APP_BAT_TIMER_TO,
    APP_BAT_CHECK_LOW_BAT,
    APP_BAT_MAX,
} T_APP_BATTERY_EVT_E;

/* Public functions ----------------------------------------------------------*/
bool app_battery_init();
bool app_battery__get_battery_power();
uint8_t app_battery__get_battery_level();
uint8_t app_battery__get_bat_charge_status();
bool app_battery__check_bat_charge_and_power_on();

#if defined(AIR_BATTERY_MANAGEMENT_ENABLE)
bool app_battery__get_bat_charge_exist();
void app_battery_test_soc();
#endif /* _AIR_BATTERY_MANAGEMENT_ENABLE_ */


#endif

