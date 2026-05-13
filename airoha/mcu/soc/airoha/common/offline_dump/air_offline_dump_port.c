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

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <string.h>

#ifdef AIR_OFFLINE_DUMP_ENABLE

#include "partition.h"
#include "offline_dump.h"
#include "race_cmd_feature.h"
#include "hal_core_status.h"

#ifdef AIR_FOTA_ENABLE
#include "fota_flash.h"
#endif

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define OFFLINE_FOTA_HEAD_RESERVE        (SERIAL_FLASH_BLOCK_SIZE)
#define OFFLINE_FOTA_TAIL_RESERVE        (SERIAL_FLASH_BLOCK_SIZE)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t offline_dump_region_address = 0x0;
uint32_t offline_dump_region_size = 0x0;
uint32_t offline_dump_enable_magic = 0x0;
/* Private functions ---------------------------------------------------------*/

/*
    PARTITION_MCU_B
    PARTITION_FOTA
*/
uint32_t offline_dump_query_region_address(void)
{
    uint32_t FOTA_address;
    partition_status_t p_status = PARTITION_OP_ERROR;

    if (offline_dump_region_address == 0) {
#ifdef CONFIG_AIR_DUAL_BANK_FOTA_ENABLE
        p_status = partition_get_begin_address(PARTITION_MCU_B, &FOTA_address);
#else
        p_status = partition_get_begin_address(PARTITION_FOTA, &FOTA_address);
#endif
        if (p_status != PARTITION_OP_OK) {
            return 0;
        }
        offline_dump_region_address = FOTA_address + OFFLINE_FOTA_HEAD_RESERVE;
    }

    return offline_dump_region_address;
}

uint32_t offline_dump_query_region_reserve(void)
{
    uint32_t FOTA_length;
    partition_status_t p_status = PARTITION_OP_ERROR;

    if (offline_dump_region_size == 0) {
#ifdef CONFIG_AIR_DUAL_BANK_FOTA_ENABLE
        p_status = partition_get_length(PARTITION_MCU_B, &FOTA_length);
#else
        p_status = partition_get_length(PARTITION_FOTA, &FOTA_length);
#endif
        if (p_status != PARTITION_OP_OK) {
            return 0;
        }

        if ((FOTA_length == 0x0) || (FOTA_length < (OFFLINE_FOTA_HEAD_RESERVE + OFFLINE_FOTA_TAIL_RESERVE))) {
            return 0x0;
        }
        offline_dump_region_size = FOTA_length - OFFLINE_FOTA_HEAD_RESERVE - OFFLINE_FOTA_TAIL_RESERVE;
    }

    return offline_dump_region_size;
}

bool is_exception_mode(void)
{
    if (HAL_CORE_EXCEPTION == hal_core_status_read(HAL_CORE_MCU)) {
        return true;
    }

    return false;
}

#if defined(AIR_FOTA_ENABLE) && defined(RACE_FOTA_CMD_ENABLE)
#include "race_fota.h"
bool offline_dump_region_is_busy(void)
{
    /* global enable flag, magic number = "OPEN" */
    if (offline_dump_enable_magic != 0x4F50454E) {
        return true;
    }

    /* fota busy flag */
#if ( OFFLINE_DUMP_SHARE_WITH_FOTA_REGION == 1 )
    static bool exception_debug_flag = false;    /* exception printf once */
    if (race_fota_is_busy() == true) {
        if (is_exception_mode() == true) {
            if (exception_debug_flag == false) {
                exception_debug_flag = true;
                log_print_exception_log("[offline_dump] FOTA ongoing, dump first priority");
            }
            return false;
        } else {
            LOG_MSGID_E(offline_dump, "[offline_dump] FOTA ongoing, region busy", 0);
        }
        return true;
    }
#endif

    return false;
}
#else
bool offline_dump_region_is_busy(void)
{
    return false;
}
#endif

bool offline_dump_query_region_info(uint8_t region_type, uint32_t *base_address, uint32_t *region_size, uint32_t *cell_size)
{
    /* parameter error */
    if ((base_address == NULL) || (region_size == NULL) || (cell_size == NULL)) {
        return false;
    }

    if ((OFFLINE_DUMP_ADDRESS == 0x0) || (OFFLINE_DUMP_ADDRESS == 0xFFFFFFFF)) {
        return false;
    }

    /* region config error, total region head reserve 4k and tail reserve 4k for FOTA */
    if ((OFFLINE_DUMP_RESERVE < (OFFLINE_REGION_EXCEPTION_LOG_REGION_SIZE)) ||
        (OFFLINE_DUMP_RESERVE < (OFFLINE_REGION_MINI_DUMP_REGION_SIZE)) ||
        (OFFLINE_DUMP_RESERVE < (SERIAL_FLASH_BLOCK_SIZE * 2))) {
            return false;
    }

    if (OFFLINE_DUMP_RESERVE < (OFFLINE_REGION_EXCEPTION_LOG_REGION_SIZE + OFFLINE_REGION_MINI_DUMP_REGION_SIZE)) {
        return false;
    }

    /* lib code, marco define can't dynamic adjust region size */
    if (region_type == OFFLINE_REGION_EXCEPTION_LOG) {
        *base_address   = (uint32_t)OFFLINE_REGION_EXCEPTION_LOG_BASE_ADDR;
        *region_size    = (uint32_t)OFFLINE_REGION_EXCEPTION_LOG_REGION_SIZE;
        *cell_size      = (uint32_t)OFFLINE_REGION_EXCEPTION_LOG_CELL_SIZE;
    } else if (region_type == OFFLINE_REGION_MINI_DUMP) {
        *base_address   = (uint32_t)OFFLINE_REGION_MINI_DUMP_BASE_ADDR;
        *region_size    = (uint32_t)OFFLINE_REGION_MINI_DUMP_REGION_SIZE;
        *cell_size      = (uint32_t)OFFLINE_REGION_MINI_DUMP_CELL_SIZE;
    } else {
        return false;
    }

    return true;
}
#endif /* AIR_OFFLINE_DUMP_ENABLE */

/* Public functions ----------------------------------------------------------*/

#if KERNELVERSION == 0x3030000
static int offline_dump_enable_init(const struct device *dev)
#elif KERNELVERSION >= 0x3070000
static int offline_dump_enable_init(void)
#else
#error "Unkown supported kernel version"
#endif
{
#ifdef AIR_OFFLINE_DUMP_ENABLE

    /* exception init before offline dump init */
    extern exception_config_mode_t exception_config_mode;
    if (exception_config_mode.exception_mode_t.exception_minidump == true) {
        /* magic value for offline dump enable */
        offline_dump_enable_magic = 0x4F50454E;
        LOG_MSGID_I(offline_dump, "offline dump enable", 0);
    } else {
        LOG_MSGID_I(offline_dump, "offline dump disable, must enable minidump first!", 0);
    }

#ifdef CONFIG_AIR_DUAL_BANK_FOTA_ENABLE
    LOG_MSGID_I(offline_dump, "offline_dump share PARTITION_MCU_B, region address: 0x%08x, region reserve: 0x%08x\n", 2,
            offline_dump_query_region_address(), offline_dump_query_region_reserve());
#else
    LOG_MSGID_I(offline_dump, "offline_dump share PARTITION_FOTA, region address: 0x%08x, region reserve: 0x%08x\n", 2,
            offline_dump_query_region_address(), offline_dump_query_region_reserve());
#endif

    /* region init */
    offline_dump_region_init();

#endif /* AIR_OFFLINE_DUMP_ENABLE */

    return 0;
}

SYS_INIT(offline_dump_enable_init, CONFIG_OFFLINE_DUMP_INIT_LEVEL, CONFIG_OFFLINE_DUMP_INIT_PRIORITY);
