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

#ifdef AIR_ONLINE_SWLA_ENABLE

#include "swla.h"
#include "system_online_dump.h"
#include "syslog.h"
#include "hal_nvic.h"
#include "hal_gpt.h"
#include "hal_gpt_internal.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SWLA_TIMER_EXPIRE_TIME          (5000)  /* 5000ms */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
log_create_module(swla, PRINT_LEVEL_INFO);

/* Private functions ---------------------------------------------------------*/
void port_swla_init_region_info(uint32_t base, uint32_t len)
{
    LOG_MSGID_E(swla, "####SWLA enabled[0x%08X,0x%08X]####\r\n", 2, base, len);
}

bool port_swla_get_gpt_timer_handle(uint32_t *handle)
{
    hal_gpt_status_t status;
    status = hal_gpt_sw_get_timer(handle);
    if (status != HAL_GPT_STATUS_OK) {
        LOG_MSGID_E(swla, "hal_gpt_sw_get_timer fail, status = %d\r\n", status);
        return false;
    }
    return true;
}

bool port_swla_gpt_timer_start(uint32_t handle, swla_callback_t callback)
{
    hal_gpt_status_t status;

    if (handle == 0) {
        return false;
    }

    status = hal_gpt_sw_start_timer_ms(handle, SWLA_TIMER_EXPIRE_TIME, callback, NULL);
    if (status != HAL_GPT_STATUS_OK) {
        LOG_MSGID_E(swla, "hal_gpt_sw_start_timer_ms fail, status = %d handle:0x%08x\r\n", 2, status, handle);
        return false;
    }
    return true;
}

#endif
