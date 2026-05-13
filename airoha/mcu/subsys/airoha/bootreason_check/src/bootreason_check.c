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
#include <stdint.h>

#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include "air_chip.h"
#include "hal_rtc.h"
#include "hal_pmu.h"
#include "hal_log.h"
#include "bootreason_check.h"

#ifdef AIR_BOOTREASON_CHECK_ENABLE

#define log_boot_reason(msg, cnt, ...) printk("[BOOTREASON] "msg"\r\n", ##__VA_ARGS__)
static bootreason_reason_t bootreason_lastreason = BOOTREASON_MAX;
int16_t pmu_power_on_reason = -1;
int16_t pmu_power_off_reason = -1;

/*Bank 39~42 not reset by WDT(cold&warm reset), data keep when enter ext-sleep mode. */
#define BOOTREASON_BANK_START 39
#define BOOTREASON_BANK_END 42
#define BOOTREASON_FLAG_BANK 39
#define BYTES_PER_REGISTER 2
#define MAX_REGISTERS 4
#define MAX_BYTES ((BOOTREASON_BANK_END - BOOTREASON_BANK_START + 1) * BYTES_PER_REGISTER)

void bootreason_set_data(uint32_t offset, const char *buf, uint32_t len)
{
    if (buf == NULL || len == 0 || offset + len > MAX_BYTES) {
        log_boot_reason("[bootreason_set_data] Invalid parameters: buf=%p, len=%d, offset=%d", 3, buf, len, offset);
        return;
    }
    pmu_strup_rg_unlock();

    for (uint32_t i = 0; i < len; ++i) {
        uint8_t bank = (offset + i) / BYTES_PER_REGISTER + BOOTREASON_BANK_START;
        uint8_t byte_offset = (offset + i) % BYTES_PER_REGISTER;
        uint16_t data = pmu_get_strup_rg(bank);

        if (byte_offset == 0) {
            //low byte
            data = (data & 0xFF00) | (buf[i] & 0x00FF);
        } else {
            //high byte
            data = (data & 0x00FF) | ((buf[i] << 8) & 0xFF00);
        }

        pmu_set_strup_rg(bank, data);
    }

    pmu_strup_rg_lock();
}

void bootreason_get_data(uint32_t offset, char *buf, uint32_t len)
{
    if (buf == NULL || len == 0 || offset + len > MAX_BYTES) {
        log_boot_reason("[bootreason_set_data] Invalid parameters: buf=%p, len=%d, offset=%d", 3, buf, len, offset);
        return;
    }
    pmu_strup_rg_unlock();
    for (uint32_t i = 0; i < len; ++i) {
        uint8_t bank = (offset + i) / BYTES_PER_REGISTER + BOOTREASON_BANK_START;
        uint8_t byte_offset = (offset + i) % BYTES_PER_REGISTER;
        uint16_t data = pmu_get_strup_rg(bank);

        if (byte_offset == 0) {
            //low byte
            buf[i] = data & 0x00FF;
        } else {
            //high byte
            buf[i] = (data >> 8) & 0x00FF;
        }
    }
    pmu_strup_rg_lock();
}

#define bootreason_get_flags(flags, nbytes) bootreason_get_data(BOOTREASON_FLAG_OFFSET, flags, nbytes)
bootreason_status_t bootreason_check_wdt_timeout_reset(void)
{
    uint8_t reason = 0x0;

    reason = pmu_get_power_off_reason();
    if (reason == BOOTREASON_WDT_TIMEOUT_RESET_FLAG) {
        return BOOTREASON_STATUS_OK;
    }

    return BOOTREASON_STATUS_ERROR;
}

bootreason_status_t bootreason_check_normal_power_on(void)
{
    uint8_t reason = 0x0;

    reason = pmu_get_power_off_reason();
    if ((reason == BOOTREASON_POWER_ON_FLAG) ||
        (reason == BOOTREASON_RESETPIN_RESET_FLAG) ||
        (reason == BOOTREASON_FIRST_POWER_ON_FLAG) ||
        (reason == BOOTREASON_LONG_PRESS_RESET_FLAG)) {
        return BOOTREASON_STATUS_OK;
    }

    return BOOTREASON_STATUS_ERROR;
}

/* Private functions ---------------------------------------------------------*/
static bootreason_reason_t bootreason_get_boot_reason(void)
{
    uint8_t reason = 0x0;

    /* get bootreason first byte */
    bootreason_get_flags((char *)&reason, 1);

    /* Check if assert happens */
    if (reason & BOOTREASON_ASSERT_RESET_FLAG) {
        return BOOTREASON_ASSERT;
    }

    /* Check if other exception happens */
    if (reason & BOOTREASON_EXCEPTION_RESET_FLAG) {
        /* check if xoff  happens */
        if (reason & BOOTREASON_XOFF_RESET_FLAG) {
            return BOOTREASON_XOFF_RESET;
        } else {
            return BOOTREASON_EXCEPTION;
        }
    }

    /* Check if WDT Software reset happens */
    if (reason & BOOTREASON_WDT_SW_RESET_FLAG) {
        return BOOTREASON_WATCHDOG_RESET;
    }

    /* Check if Soft reset happens */
    if (reason & BOOTREASON_SOFT_RESET_FLAG) {
        return BOOTREASON_SOFT_RESET;
    }

#ifdef HAL_PMU_MODULE_ENABLED
    /* check if WDT timeout reset happens */
    if (bootreason_check_wdt_timeout_reset() == BOOTREASON_STATUS_OK) {
        /* Check if WDT timeout reset happens in sleep flow */
        if (reason & BOOTREASON_SLEEP_ENTER_FLAG) {
            return BOOTREASON_SLEEPERROR;
        }

        /* other WDT tiemout */
        return BOOTREASON_WATCHDOG;
    }


    /* Check the last power off reason */
    if (bootreason_check_normal_power_on() == BOOTREASON_STATUS_OK) {
        return BOOTREASON_NORMAL;
    }
#endif
    return BOOTREASON_UNKNOWN;
}

static void bootreason_set_flags(char usr_flag, bool is_set)
{
    uint16_t flag = (uint16_t)BOOTREASON_INIT_FLAG;

    if (usr_flag == 0) {
        /* clear reserved bootreason flags */
        flag = 0x0;
    } else {
        /* clear bootreason flags */
        if (is_set) {
            flag |= usr_flag << 8;
        } else {
            flag &= (~usr_flag) << 8;
        }
    }

    bootreason_set_data(BOOTREASON_FLAG_OFFSET, (const char *)&flag, 2);
}

void bootreason_set_reboot_owner(uint32_t owner, uint32_t mode)
{
    bootreason_set_data(BOOTREASON_REBOOT_OWNER_OFFSET, (const char *)&owner, 2);
    if (mode == BOOTREASON_REBOOT_MODE_WDT_RESET) {
        bootreason_set_flag_wdt_sw_reset();
    }
}

static inline void bootreason_clear_flags(void)
{
    bootreason_set_flags(0, 1);
}

/* Public functions ----------------------------------------------------------*/
void bootreason_set_flag_exception_reset(void)
{
    bootreason_set_flags(BOOTREASON_EXCEPTION_RESET_FLAG, 1);
}

void bootreason_set_flag_assert_reset(void)
{
    bootreason_set_flags(BOOTREASON_ASSERT_RESET_FLAG, 1);
}

void bootreason_set_flag_wdt_sw_reset(void)
{
    bootreason_set_flags(BOOTREASON_WDT_SW_RESET_FLAG, 1);
}

void bootreason_set_flag_soft_reset(void)
{
    bootreason_set_flags(BOOTREASON_SOFT_RESET_FLAG, 1);
}

void bootreason_set_flag_xoff_reset(void)
{
    bootreason_set_flags(BOOTREASON_XOFF_RESET_FLAG, 1);
}

void bootreason_set_flag_enter_sleep(void)
{
    bootreason_set_flags(BOOTREASON_SLEEP_ENTER_FLAG, 1);
}

void bootreason_clear_flag_exit_sleep(void)
{
    bootreason_set_flags(BOOTREASON_SLEEP_ENTER_FLAG, 0);
}


void bootreason_init(void)
{
    char flag[BOOTREASON_FLAG_BYTES] = {0};

#ifdef HAL_PMU_MODULE_ENABLED

    pmu_power_on_reason = (int16_t)pmu_get_power_on_reason();
    pmu_power_off_reason = (int16_t)pmu_get_power_off_reason();

    log_boot_reason("[PMU PWR OFF]:%d\r\n", 1, (int)pmu_power_off_reason);
    log_boot_reason("[PMU PWR ON ]:%d\r\n", 1, (int)pmu_power_on_reason);

    /* get bootreason */
    bootreason_lastreason = bootreason_get_boot_reason();
    log_boot_reason("[Boot Reason]:%d\r\n", 1, bootreason_lastreason);

#else
#error "Bootreason may need porting."
#endif  //HAL_PMU_MODULE_ENABLED


    /* get bootreason first byte */
    bootreason_get_flags((char *)&flag, BOOTREASON_FLAG_BYTES);

    /* reset bootreason flags */
    bootreason_clear_flags();

    log_boot_reason("[Boot Reason Flag]:0x%02x%02x\r\n", 2, flag[1], flag[0]);
}


bootreason_status_t bootreason_get_reason(bootreason_reason_t *reason)
{
    if (bootreason_lastreason < BOOTREASON_MAX) {
        /* bootreason_init has been called */
        *reason = bootreason_lastreason;
    } else {
        /* bootreason_init has not been called */
        *reason = bootreason_get_boot_reason();
    }

    return BOOTREASON_STATUS_OK;
}

bootreason_status_t bootreason_get_info(bootreason_info_t *info)
{
    bootreason_status_t ret = BOOTREASON_STATUS_OK;
    bootreason_reason_t lastreason;
#if (EXCEPTION_MEMDUMP_MODE & EXCEPTION_MEMDUMP_MINIDUMP)
    uint32_t dump_index = 0;
    uint32_t dump_addr, dump_len = 0;
#endif /* EXCEPTION_MEMDUMP_MODE */

    /* info init */
    memset(info, 0, sizeof(bootreason_info_t));

    /* get boot reason */
    bootreason_get_reason(&lastreason);

    /* check boot reason */
    switch (lastreason) {
        case BOOTREASON_UNKNOWN:
        case BOOTREASON_NORMAL:
        case BOOTREASON_ASSERT:
        case BOOTREASON_EXCEPTION:
        case BOOTREASON_WATCHDOG:
        case BOOTREASON_SLEEPERROR:
#if (EXCEPTION_MEMDUMP_MODE & EXCEPTION_MEMDUMP_MINIDUMP)
            if (EXCEPTION_STATUS_OK != exception_minidump_region_query_latest_index(&dump_index)) {
                log_boot_reason("exception_minidump_region_query_latest_index error !!!\r\n", 0);
                ret = BOOTREASON_STATUS_ERROR;
                break;
            }

            if (EXCEPTION_STATUS_OK != exception_minidump_region_query_info(dump_index,
                                                                            &dump_addr,
                                                                            &dump_len)) {
                log_boot_reason("exception_minidump_region_query_info error !!!\r\n", 0);
                ret = BOOTREASON_STATUS_ERROR;
                break;
            }

            info->custom.data = (uint8_t *)dump_addr;
            info->custom.len  = dump_len;
            break;
#endif /* EXCEPTION_MEMDUMP_MODE */
        default:
            ret = BOOTREASON_STATUS_ERROR;
            break;
    }

    /* update info */
    info->reason = lastreason;

    return ret;
}

#if KERNELVERSION == 0x3030000
static int bootreason_module_init(const struct device *dev)
{
    ARG_UNUSED(dev);
#elif KERNELVERSION >= 0x3070000
static int bootreason_module_init(void)
{
#else
#error "Unkown supported kernel version"
#endif
#if !defined(AIR_DOWNLOAD_AGENT) && !defined(CONFIG_MCUBOOT)
    bootreason_init();
#endif
    return 0;
}

SYS_INIT(bootreason_module_init, CONFIG_BOOT_REASON_INIT_LEVEL, CONFIG_BOOT_REASON_INIT_PRIORITY);
#endif // AIR_BOOTREASON_CHECK_ENABLE

