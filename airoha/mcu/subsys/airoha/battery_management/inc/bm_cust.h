/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
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

#ifndef __BM_CUST_H__
#define __BM_CUST_H__

#include "bm_ext.h"

typedef enum {
    BM_VBAT                     = 0,     /* battery voltage (mV) */
    BM_SOC                      = 1,     /* battery capacity (mAH) */
    BM_TEMP                     = 2,     /* temperature. (degree C) */
    BM_CHG_EXIST                = 3,     /* charger existence status. */
    BM_CHG_STA                  = 4,     /* charger state. */
    BM_CHG_EN_STA               = 5,     /* charger enable state (is charging). */
    BM_CHG_CURR                 = 6,     /* charging current. (mA) */
    BM_SD_BAT                   = 7,     /* shutdown battery voltage (mV) */
    BM_FULL_BAT                 = 8,     /* full battery voltage (mV) */
    BM_PNZCV                    = 9,     /* power on zero circuit voltage (mV) */
    BM_INFO_MAX,                         /* info max number. */
} bm_info_idx_t;

typedef struct {
    uint16_t vbat;
    uint8_t soc;
    int16_t temp;
    bool chg_exist;
    uint8_t chg_sta;
    bool chg_en_sta;
    uint16_t chg_curr;
    uint16_t sd_bat;
    uint16_t full_bat;
    uint16_t pnzcv;
} PACKED bm_info_t;

/* function */
void bm_get_vbat(void);
void bm_get_soc(void);
void bm_get_temp(void);
void bm_get_chg_exist(void);
void bm_get_chg_sta(void);
void bm_get_chg_en_sta(void);
void bm_get_chg_curr(void);
void bm_chg_enable(bool en);

void bm_chg_eoc_cb(void);
void bm_timer_to_cb(void);

/* common */
void bm_update_info(void);
int32_t bm_get_info(bm_info_idx_t info_idx);
void bm_dump_info(void);
void bm_work_handler(struct k_work *work);
void bm_cust_init(void);

#endif /* __BM_CUST_H__ */

