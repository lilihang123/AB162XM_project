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

/* Includes ------------------------------------------------------------------*/
#include "hal_platform.h"
#include "hal_core_status.h"
#include "memory_attribute.h"
#include "hal_cross_core_config.h"

#if defined(AIR_SOC_CROSS_CORE_MEMORY_ENABLE)

#if defined(CORE_MCU)

#if defined(AIR_LOGGING_ENABLE)
#include "air_logging.h"

#define LOG_LEVEL LOG_LEVEL_DEBUG
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(core_status);
#else
#define LOG_WRN(...)
#endif

#include <zephyr/init.h>
#elif defined(CORE_RISCV)
#include "syslog.h"
#else
#endif


#define CORE_STATUS                       (hal_core_status_t*)(CROSS_CORE_MEM_VARIABLE(core_status))

ATTR_TEXT_IN_TCM hal_core_status_t hal_core_status_read(hal_core_id_t id)
{
    if (id >= HAL_CORE_MAX) {
        return HAL_CORE_ERROR;
    } else {
        return *(CORE_STATUS + id);
    }
}


hal_core_status_t hal_core_status_write(hal_core_id_t id, hal_core_status_t status)
{
    if (id >= HAL_CORE_MAX) {
        return HAL_CORE_ERROR;
    }

#if defined(CORE_MCU)
    if (id != HAL_CORE_MCU) {
        LOG_WRN("cross core operation: %d => %d", id, status);
    }
#elif defined(CORE_RISCV)
    if (id != HAL_CORE_RISCV) {
        LOG_MSGID_W(common, "cross core operation: %d => %d", 2, id, status);
    }
#else
#error "Must be define this is which Core"
#endif

    *(CORE_STATUS + id) = status;
    return status;

}



#if defined(CORE_MCU)
static int mark_mcu_booting(void)
{
    hal_core_status_write(HAL_CORE_MCU, HAL_CORE_INIT);
    return 0;
}

static int mark_mcu_active(void)
{
    hal_core_status_write(HAL_CORE_MCU, HAL_CORE_ACTIVE);
    return 0;
}

SYS_INIT(mark_mcu_booting, CONFIG_CORE_STATUS_BOOT_INIT_LEVEL, CONFIG_CORE_STATUS_BOOT_INIT_PRIORITY);
SYS_INIT(mark_mcu_active, CONFIG_CORE_STATUS_ACTIVE_INIT_LEVEL, CONFIG_CORE_STATUS_ACTIVE_INIT_PRIORITY);
#endif /* defined(CORE_MCU) */

#endif /* defined(AIR_SOC_CROSS_CORE_MEMORY_ENABLE) */