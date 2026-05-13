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

#if defined(AIR_EXCEPTION_HANDLER_ENABLE)

/* Includes ------------------------------------------------------------------*/
// #include "hal_resource_assignment.h"
#include <zephyr/irq.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/types.h>
#include <stddef.h>
#include <sys/types.h>
#include <zephyr/device.h>

#ifdef AIR_NVKEY_ENABLE
#include "nvkey.h"
#include "nvkey_id_def.h"
#endif

#include "hal_mpu.h"
#include "exception_handler.h"
#include "exception_config.h"
#include "exception_portable.h"
#include "hal_gpt.h"

#if (EXCEPTION_SLAVES_TOTAL > 0)
#include "hal_hw_semaphore.h"
#include "hal_ccni_config.h"
#endif

#ifdef MTK_NVDM_ENABLE
#include "nvkey.h"
#include "nvkey_id_list.h"
#endif

#ifdef AIR_ICE_DEBUG_ENABLE
#include "hal_ice_debug.h"
#endif

#ifdef HAL_RTC_MODULE_ENABLED
#include "hal_rtc.h"
#endif
#if defined(AIR_LOGGING_ENABLE)
#include "air_logging.h"
#endif
#ifdef HAL_WDT_MODULE_ENABLED
#include "hal_wdt.h"
#include "hal_define.h"
#endif

#ifdef AIR_BOOTREASON_CHECK_ENABLE
#include "bootreason_check.h"
#endif

#include "hal_gpt.h"
#include "hal_platform.h"
#include "hal.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if defined(AIR_LOGGING_ENABLE)
log_create_module(exception, PRINT_LEVEL_INFO);
#endif
static uint32_t exception_wdt_mode = 0;

/* Public variables ----------------------------------------------------------*/
// extern uint8_t ccm_exception_ns_info[];
// uint32_t HW_SYSRAM_PRIVATE_MEMORY_NS_EXCEPTION_INFO_START_PORT = (uint32_t)(&ccm_exception_ns_info[0]);
extern unsigned int __text_region_start[];
extern unsigned int __text_region_end[];
extern unsigned int  _image_ram_start[];
extern unsigned int  _image_ram_end[];

/* exception dump memory regions in region_init.c */
const memory_region_type memory_regions[] = {
    // {"ram", (unsigned int *)(TCM_BASE), (unsigned int *)(TCM_BASE + TCM_LENGTH), 1},
    // {"btram", (unsigned int *)(BT_SYSRAM_BASE), (unsigned int *)(BT_SYSRAM_BASE + BT_SYSRAM_LENGTH), 1},
    {"text", __text_region_start, __text_region_end, 1},
    {"image_ram", _image_ram_start, _image_ram_end, 1},
    {"scs", (unsigned int *)SCS_BASE, (unsigned int *)(SCS_BASE + 0x1000), 1},
    // {"dwt", (unsigned int *)(DWT_BASE), (unsigned int *)(DWT_BASE + 0x1000), 1},
    HAL_DUMP_PERIPHERAL_REGISTER
    {0}
};

/* exception dump after disable cache, region name must be start with string <non-cacheable> */
const memory_region_type memory_regions_ex[] = {
    {"non_cache_text", __text_region_start, __text_region_end, 1},
    // {"non_cache_cache_setting",(unsigned int *)(CMSYS_L1CACHE_BASE          ),   (unsigned int *)(CMSYS_L1CACHE_BASE   + CMSYS_L1CACHE_SIZE         ),  1},
    // {"cache_memory", (unsigned int *)0x04200000, (unsigned int *)0x04204000, 1},
    {0}
};
/* Private functions ---------------------------------------------------------*/
extern uint32_t exception_get_reason();

/* Public functions ----------------------------------------------------------*/
#if (EXCEPTION_SLAVES_TOTAL > 0)
extern hal_hw_semaphore_status_t hw_semaphore_take(hal_hw_semaphore_id_t id);
extern hal_hw_semaphore_status_t hw_semaphore_give(hal_hw_semaphore_id_t id);


/******************************************************************************/
/*            exception_hw_semaphore_take                        */
/******************************************************************************/
int32_t exception_hw_semaphore_take()
{
    return hw_semaphore_take(EXCEPTION_HW_SEMAPHORE);
}

/******************************************************************************/
/*            exception_hw_semaphore_give                        */
/******************************************************************************/
int32_t exception_hw_semaphore_give()
{
    return hw_semaphore_give(EXCEPTION_HW_SEMAPHORE);
}

#endif

/******************************************************************************/
/*            exception_core_status_read                        */
/******************************************************************************/
int exception_core_status_read(void)
{
#if 0
    if (HAL_CORE_EXCEPTION == hal_core_status_read(HAL_CORE_MCU)) {
        return 0;
    } else {
        return -1;
    }
#else
    return -1;
#endif
}

/******************************************************************************/
/*            exception_rtc_set_data                        */
/******************************************************************************/
int exception_rtc_set_data(uint16_t offset, const char *buf, uint16_t len)
{
#ifdef HAL_RTC_MODULE_ENABLED
    return hal_rtc_set_data(offset, buf, len);
#else
    return 0;
#endif
}

#if EXCEPTION_SLAVES_TOTAL > 0
/******************************************************************************/
/*            exception_ccni_query_event_status                        */
/******************************************************************************/
int  exception_ccni_query_event_status(uint32_t  event, uint32_t *data)
{
    return hal_ccni_query_event_status(event, data);
}
#endif

void exception_bootreason_set_flag_assert_reset(void)
{
#ifdef AIR_BOOTREASON_CHECK_ENABLE
    bootreason_set_flag_assert_reset();
#endif
}
void exception_bootreason_set_flag_exception_reset(void)
{
#ifdef AIR_BOOTREASON_CHECK_ENABLE
    bootreason_set_flag_exception_reset();
#endif
}

void exception_esc_flash_return_ready(void)
{
#if defined(HAL_ESC_MODULE_ENABLED) && defined(ESC_FLASH_ENABLE)
    /* todo: need feature option to decide compile or not */
    Flash_ReturnReady();
#endif
}

/* The following code need to be removed, when AIR logging ready!! */
#if !defined(AIR_LOGGING_ENABLE)
#include "hal_uart.h"
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/* Public define -------------------------------------------------------------*/
/* RACE HEAD */
#define RACE_HEAD_CHANNEL_BYTE                  0x05
/* RACE TYPE */
#define RACE_TYPE_CMD_WITH_RESPONCE             0x5A
#define RACE_TYPE_RESPONCE                      0x5B
#define RACE_TYPE_CMD_WITHOUT_RESPONCE          0x5C
#define RACE_TYPE_NOTIFICATION                  0x5D
/* RACE PROTOCOL ID */
#define RACE_PROTOCAL_SYSLOG_BEGIN              (0x0F00 | 0x10)
#define RACE_PROTOCAL_EXCEPTION_STRING_LOG      (0x0F00 | 0x12)
#define RACE_PROTOCAL_EXCEPTION_BINARY_LOG      (0x0F00 | 0x13)
#define RACE_PROTOCAL_ACTIVE_ASSERT             (0x0F00 | 0x14)
#define RACE_PROTOCAL_QUERY_VERSION_BUILDTIME   (0x0F00 | 0x15)
#define RACE_PROTOCAL_GET_LOG_FILTER_INFO       (0x0F00 | 0x16)
#define RACE_PROTOCAL_SET_LOG_FILTER_INFO       (0x0F00 | 0x17)
#define RACE_PROTOCAL_SAVE_LOG_SETTING          (0x0F00 | 0x18)
#define RACE_PROTOCAL_QUERY_CPU_FILTER_INFO     (0x0F00 | 0x19)
#define RACE_PROTOCAL_SET_CPU_FILTER_INFO       (0x0F00 | 0x20)
#define RACE_PROTOCAL_EXCEPTION_MSGID           (0x0F00 | 0x1A)
#define RACE_PROTOCAL_QUERY_SYSTEM_INFO         (0x0F00 | 0x1B)
#define RACE_PROTOCAL_TLV_LOG                   (0x0F00 | 0x00)
#define RACE_PROTOCAL_STRING_LOG                (0x0F00 | 0x40)
#define RACE_PROTOCAL_MSGID_LOG                 (0x0F00 | 0x41)
#define RACE_PROTOCAL_MSGID_LOG_WITH_STR        (0x0F00 | 0x42)
#define RACE_PROTOCAL_SYSLOG_END                (0x0F00 | 0x4F)
#define RACE_PROTOCAL_TLV_DUMP_LOG              (0x0F00)
#define RACE_PROTOCAL_ATCI_BEGIN                (0x0F92)
#define RACE_PROTOCAL_ATCI_END                  (0x0F92)
#define PORT_SYSLOG_MAX_ONE_LOG_SIZE (320)
#define PORT_SYSLOG_MAX_ONE_PLAIN_LOG_SIZE (128)
#define MAX_EXCEPTION_DATA_LENGTH 1024

typedef struct {
    uint8_t *p_buf;     /**<  MUX buffer start address*/
    uint32_t buf_size;  /**<  MUX buffer lenght*/
} mux_buffer_t;

typedef struct {
    uint8_t     race_pktId;
    uint8_t     race_type;
    uint16_t    race_length;
    uint16_t    race_id;
} __attribute__((packed)) syslog_race_t;

volatile uint32_t g_syslog_port = HAL_UART_0;
static volatile uint32_t g_exception_string_log_count = 0;
static volatile uint32_t g_exception_binary_log_count = 0;

/* TCM is mainly for Optimize log printing time */
ATTR_TEXT_IN_TCM uint32_t port_syslog_send(uint32_t id, bool drop_flag, mux_buffer_t *p_buf_info)
{
    uint8_t race_header[sizeof(syslog_race_t)];
    uint32_t i, total_size = 0;
    uint32_t counter;

    p_buf_info[0].p_buf = race_header;
    p_buf_info[0].buf_size = sizeof(syslog_race_t);

    for (i = 0; p_buf_info[i].p_buf != NULL; i++) {
        total_size += p_buf_info[i].buf_size;
    }
    counter = i;

    /* Insert the race header here */
    syslog_race_t *p_head_race = (syslog_race_t*)&race_header[0];
    p_head_race->race_pktId     = RACE_HEAD_CHANNEL_BYTE;
    p_head_race->race_type      = RACE_TYPE_NOTIFICATION;
    p_head_race->race_length    = total_size - 4;
    p_head_race->race_id        = id;

    /*send the payload */
    hal_uart_send_polling(g_syslog_port, race_header, 6);
    for (i = 1; p_buf_info[i].p_buf != NULL; i++) {
        hal_uart_send_polling(g_syslog_port, p_buf_info[i].p_buf, p_buf_info[i].buf_size);
    }

    return total_size;

}

int log_print_exception_log(const char *message, ...)
{
    /* race + exc_count + string + NULL */
    mux_buffer_t log_buf_info[4];
    va_list list;
    int32_t log_size;
    char frame_header[PORT_SYSLOG_MAX_ONE_PLAIN_LOG_SIZE];

    va_start(list, message);

    log_size = vsnprintf(frame_header, sizeof(frame_header), message, list);
    if (log_size < 0) {
        va_end(list);
        return 0;
    }
    if ((uint32_t)log_size >= sizeof(frame_header)) {
        log_size = sizeof(frame_header) - 1;
    }

    va_end(list);

    log_buf_info[1].p_buf = (uint8_t *)&g_exception_string_log_count;
    log_buf_info[1].buf_size = 4;
    log_buf_info[2].p_buf = (uint8_t*)frame_header;
    log_buf_info[2].buf_size = log_size;
    log_buf_info[3].p_buf = NULL;

    port_syslog_send(RACE_PROTOCAL_EXCEPTION_STRING_LOG, false, log_buf_info);

    g_exception_string_log_count++;

    return log_size;
}


void log_dump_exception_data(const uint8_t *data, uint32_t size)
{
    uint8_t exception_temp_buffer[MAX_EXCEPTION_DATA_LENGTH] = {0};

    /* race + exc_count + [data * 1] + NULL */
    mux_buffer_t log_buf_info[4];
    uint8_t *curr_data;
    uint32_t curr_size;

    uint8_t *pbuffer;

    uint32_t ram_start = RAM_BASE;
    uint32_t ram_end = RAM_BASE + RAM_LENGTH;

    curr_data = (uint8_t *)data;
    while (size > 0) {
        if (size >= MAX_EXCEPTION_DATA_LENGTH) {
            curr_size = MAX_EXCEPTION_DATA_LENGTH;
            size -= MAX_EXCEPTION_DATA_LENGTH;
        } else {
            curr_size = size;
            size = 0;
        }

        if (((uint32_t)curr_data >= ram_start) && ((uint32_t)curr_data < ram_end)) {
            pbuffer = curr_data;
        } else {
            pbuffer = exception_temp_buffer;
            memcpy(pbuffer, curr_data, curr_size);
        }
        log_buf_info[1].p_buf = (uint8_t *)&g_exception_binary_log_count;
        log_buf_info[1].buf_size = 4;
        log_buf_info[2].p_buf = pbuffer;
        log_buf_info[2].buf_size = curr_size;
        log_buf_info[3].p_buf = NULL;
        port_syslog_send(RACE_PROTOCAL_EXCEPTION_BINARY_LOG, false, log_buf_info);
        curr_data += curr_size;
        g_exception_binary_log_count++;
    }
}

void exception_syslog_callback(void)
{

    hal_uart_config_t uart_config;

    hal_uart_deinit(g_syslog_port);
    uart_config.baudrate = HAL_UART_BAUDRATE_3000000;
    uart_config.parity = HAL_UART_PARITY_NONE;
    uart_config.stop_bit = HAL_UART_STOP_BIT_1;
    uart_config.word_length = HAL_UART_WORD_LENGTH_8;
    hal_uart_init(g_syslog_port, &uart_config);
#ifndef MTK_DEBUG_PLAIN_LOG_ENABLE
    hal_uart_set_software_flowcontrol(g_syslog_port, 0x11, 0x13, 0x77);
#endif
}
#endif
/* The above code need to be removed, when AIR logging ready!! */

/******************************************************************************/
/*            exception_dump_config_init                        */
/******************************************************************************/
int exception_dump_config_init(void)
{
#if defined(AIR_NVKEY_ENABLE)
    extern exception_config_mode_t exception_config_mode;
    nvkey_status_t nvkey_status = NVKEY_STATUS_OK;

    uint32_t size = 4;
    LOG_MSGID_I(exception, "[Dump config]:0x%x\r\n", 1, (unsigned int)exception_config_mode.exception_mode);

    /* get user's exception dump configuartion */
    nvkey_status = nvkey_read_data(NVID_SYS_EXP_DUMP_MODE, (uint8_t *)&exception_config_mode.exception_mode, &size);
    if (NVKEY_STATUS_OK != nvkey_status) {
        LOG_MSGID_I(exception, "exception dump init fail because read nvkey fail,ret = %d\r\n", 1, nvkey_status);
    }

    LOG_MSGID_I(exception, "exception_nodump:%d\r\n", 1, exception_config_mode.exception_mode_t.exception_nodump);
    LOG_MSGID_I(exception, "exception_fulldump_text:%d\r\n", 1, exception_config_mode.exception_mode_t.exception_fulldump_text);
    LOG_MSGID_I(exception, "exception_fulldump_binary:%d\r\n", 1, exception_config_mode.exception_mode_t.exception_fulldump_binary);
    LOG_MSGID_I(exception, "exception_minidump:%d\r\n", 1, exception_config_mode.exception_mode_t.exception_minidump);
    LOG_MSGID_I(exception, "mask_irq_check_assert:%d\r\n", 1, exception_config_mode.exception_mode_t.mask_irq_check_assert);
    LOG_MSGID_I(exception, "reset_after_dump:%d\r\n", 1, exception_config_mode.exception_mode_t.reset_after_dump);
    LOG_MSGID_I(exception, "wdt_reset_mode:%d\r\n", 1, exception_config_mode.exception_mode_t.wdt_reset_mode);
    LOG_MSGID_I(exception, "systemhang_pmic_mode:%d\r\n", 1, exception_config_mode.exception_mode_t.systemhang_pmic_mode);
    LOG_MSGID_I(exception, "[Dump config]:0x%x\r\n", 1, (unsigned int)exception_config_mode.exception_mode);

    return nvkey_status;
#else
    return 0;
#endif
}

/******************************************************************************
 *  Name: exception_dump_config_init
 ******************************************************************************/
SYS_INIT(exception_dump_config_init, CONFIG_EXCEPTION_DUMP_INIT_LEVEL, CONFIG_EXCEPTION_DUMP_INIT_PRIORITY);

/******************************************************************************/
/*            exception_feed_wdt                              */
/******************************************************************************/
void exception_feed_wdt(void)
{
#ifdef HAL_WDT_MODULE_ENABLED
    hal_wdt_feed(HAL_WDT_FEED_MAGIC);
#endif
}

/******************************************************************************/
/*            exception_disable_cache                              */
/******************************************************************************/
void exception_disable_cache(void)
{
#ifdef HAL_CACHE_MODULE_ENABLED
    hal_cache_disable();
#endif
}

void exception_disable_mpu(void)
{
#ifdef HAL_MPU_MODULE_ENABLED
    hal_mpu_disable();
#endif
}

/******************************************************************************/
/*            exception_enable_wdt_reset                               */
/******************************************************************************/
void exception_enable_wdt_reset(void)
{
#ifdef HAL_WDT_MODULE_ENABLED

    extern void    wdt_exception_config_internal_use(uint32_t seconds);
    /* config wdt as reset mode and timeout is 90s */
    wdt_exception_config_internal_use(90);

    extern exception_config_mode_t exception_config_mode;
    if (exception_config_mode.exception_mode_t.systemhang_pmic_mode) {
        exception_printf("[exception]:WDT reset config as PMIC mode");
        extern void wdt_set_pmu_mask(uint32_t enable);
        wdt_set_pmu_mask(TRUE);

    }
#endif
    exception_wdt_mode = EXCEPTION_WDT_RESET;
}

/******************************************************************************/
/*            exception_disable_wdt_reset                        */
/******************************************************************************/
void exception_disable_wdt_reset(void)
{
#ifdef HAL_WDT_MODULE_ENABLED
    if (exception_wdt_mode == EXCEPTION_WDT_RESET) {
        hal_wdt_disable(HAL_WDT_DISABLE_MAGIC);
    }
#endif
}

/******************************************************************************/
/*            exception_enable_wdt_interrupt                        */
/******************************************************************************/
void exception_enable_wdt_interrupt(void)
{
    if ((exception_wdt_mode != EXCEPTION_WDT_INTERRUPT) && (exception_get_reason() != 2)) {
#ifdef HAL_WDT_MODULE_ENABLED
        hal_wdt_config_t wdt_config;
        wdt_config.mode = HAL_WDT_MODE_INTERRUPT;
        wdt_config.seconds = 30;
        hal_wdt_disable(HAL_WDT_DISABLE_MAGIC);
        hal_wdt_init(&wdt_config);
        hal_wdt_enable(HAL_WDT_ENABLE_MAGIC);
#endif
        exception_wdt_mode = EXCEPTION_WDT_INTERRUPT;
    }
}

/******************************************************************************/
/*            Exception's Reboot Functions                                    */
/******************************************************************************/
void exception_reboot(void)
{
#ifdef HAL_WDT_MODULE_ENABLED
    extern exception_config_mode_t exception_config_mode;

    /* latch pc feature enable, wdt need config as warm reset*/
    if (exception_config_mode.exception_mode_t.systemhang_pmic_mode) {
        hal_wdt_config_t wdt_config;
        wdt_config.mode = HAL_WDT_MODE_RESET;
        wdt_config.seconds = 3;
        hal_wdt_disable(HAL_WDT_DISABLE_MAGIC);
        hal_wdt_init(&wdt_config);
        hal_wdt_enable(HAL_WDT_ENABLE_MAGIC);
        if (exception_config_mode.exception_mode_t.systemhang_pmic_mode) {
            extern void wdt_set_pmu_mask(uint32_t enable);
            /* config wdt as warm reset */
            wdt_set_pmu_mask(TRUE);
        }

        while (1);
    } else {
        /* directly reset, cold reset*/
        hal_wdt_software_reset();
        /* never run into there */
        while (1);
    }

#endif
    return;
}

/******************************************************************************/
/*            exception_mpu_setting                        */
/******************************************************************************/
__attribute__((__section__(".exception_code")))  void exception_mpu_setting(void)
{
#ifdef HAL_MPU_MODULE_ENABLED
    hal_mpu_region_disable(HAL_MPU_REGION_0);
#endif
}

/******************************************************************************/
/*            exception_ice_debug_is_enable                        */
/******************************************************************************/
bool exception_ice_debug_is_enable(void)
{
    return false;
}
void exception_ice_debug_test(void)
{

}

#endif /* AIR_EXCEPTION_HANDLER_ENABLE */
