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

#ifndef __BM_CORE_H__
#define __BM_CORE_H__

#include <stdint.h>
#include <stdbool.h>
#include "hal_pmu.h"
#include "hal_pmu_platform.h"
#include "hal_pmu_cal.h"

#ifndef PACKED
#define PACKED  __attribute__((packed))
#endif

typedef enum {
    BM_OFF = 0,
    BM_ON  = 1,
} bm_operate_t;

typedef enum {
    BM_STATUS_INVALID_PARAMETER = -1,    /* An invalid parameter. */
    BM_STATUS_ERROR             =  0,    /* An error occurred during the function call. */
    BM_STATUS_OK                =  1     /* The function call was successful. */
} bm_status_t;

typedef enum {
    BM_CB_VBAT              = 0,
    BM_CB_SOC               = 1,
    BM_CB_TEMP              = 2,
    BM_CB_CHG_EXIST         = 3,
    BM_CB_CHG_STA           = 4,
    BM_CB_CHG_EN_STA        = 5,
    BM_CB_CHG_CURR          = 6,
    BM_CB_CHG_IN            = 7,
    BM_CB_CHG_OUT           = 8,
    BM_CB_CHG_EOC           = 9,
    BM_CB_TIMER_TO          = 10,
    BM_CB_MAX,
} bm_cb_t;

typedef enum{
    BM_USER_APP              = 0,
    BM_USER_CUST             = 1,
    BM_USER_MAX,
} bm_user_t;

typedef struct {
    void (*bm_callback)(void *user_data);
} bm_func_t;

typedef void (*bm_callback_t)(void *user_data);

extern bm_func_t bm_cb_func[BM_CB_MAX][BM_USER_MAX];


/* common */
void bm_assert(void);
bm_status_t bm_register_callback(bm_cb_t bm_cb, bm_callback_t callback, bm_user_t user);
bm_status_t bm_deregister_callback(bm_cb_t bm_cb, bm_user_t user);
void bm_timer_start(uint32_t bm_timer_ms);
void bm_timer_stop(void);
void bm_init(void);

#endif /* __BM_CORE_H__ */

