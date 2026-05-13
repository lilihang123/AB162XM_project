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

#include "hal_ccni_config.h"
#include "hal_mpu.h"
#include "exception_handler.h"
#include "exception_config.h"
#include "exception_portable.h"
#include "hal_gpt.h"

#if (EXCEPTION_SLAVES_TOTAL > 0)
#include "hal_hw_semaphore.h"
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

#include "hal_gpt.h"
#include "hal_platform.h"
#include "hal.h"
#include "hal_core_status.h"

#if defined(AIR_LOGGING_ENABLE)
log_create_module(exception, PRINT_LEVEL_INFO);
#endif

#ifdef HAL_CCNI_MODULE_ENABLED
#include "hal_ccni_config.h"
#endif

#ifdef AIR_BOOTREASON_CHECK_ENABLE
#include "bootreason_check.h"
#endif

#ifdef AIR_FOTA_ENABLE
#include "fota_multi_info.h"
#endif

#ifdef AIR_BYPASS_SYSLOG_WITH_LOG_FLOW_ENABLE
#include "hal_cross_core_config.h"
#endif

#ifdef HAL_CCNI_MODULE_ENABLED
#define EXCEPTION_EVENT_TO_RISCV_0             IRQGEN_MCU2RISCV_EVENT16
#endif

/* External functions ---------------------------------------------------------*/
extern void wdt_exception_config_internal_use(uint32_t seconds);
extern uint32_t exception_get_reason();
extern uint8_t syslog_port_get_uart_log(void);
extern void log_global_turn_off(void);
#ifdef AIR_BYPASS_SYSLOG_WITH_LOG_FLOW_ENABLE
extern void mux_clear_sw_wptr(uint8_t port_index);
#endif
/* External variables ----------------------------------------------------------*/
extern unsigned int __text_region_start[];
extern unsigned int __text_region_end[];
// extern uint8_t ccm_exception_ns_info[];
extern exception_config_mode_t exception_config_mode;

/* Private variables ----------------------------------------------------------*/
static uint32_t exception_wdt_mode = 0;

/* Public variables ----------------------------------------------------------*/
// uint32_t HW_SYSRAM_PRIVATE_MEMORY_NS_EXCEPTION_INFO_START_PORT = (uint32_t)(&ccm_exception_ns_info[0]);
extern unsigned int _image_ram_start[];
extern unsigned int _image_ram_end[];
extern unsigned int _bt_sysram_end[];

/* exception dump memory regions in region_init.c */
const memory_region_type memory_regions[] = {
    {"image_ram", (unsigned int *)(_image_ram_start), (unsigned int *)(_image_ram_end), 1},
    {"btram", (unsigned int *)(BT_SYSRAM_BASE), (unsigned int *)(_bt_sysram_end), 1},
    {"text", __text_region_start, __text_region_end, 1},
    {"scs", (unsigned int *)SCS_BASE, (unsigned int *)(SCS_BASE + 0x1000), 1},
    {"dwt", (unsigned int *)(DWT_BASE), (unsigned int *)(DWT_BASE + 0x1000), 1},
#if CONFIG_AIR_NVKEY_ENABLE
    {"storage", (unsigned int*)(STORAGE_PARTITION_BASE), (unsigned int*)(STORAGE_PARTITION_END), 1},
#endif
    HAL_DUMP_PERIPHERAL_REGISTER
    {0}
};

/* exception dump after disable cache, region name must be start with string <non-cacheable> */
const memory_region_type memory_regions_ex[] = {
    {"non_cache_text", __text_region_start, __text_region_end, 1}, \
    {"non_cache_cache_setting",(unsigned int *)(CMSYS_L1CACHE_BASE          ),   (unsigned int *)(CMSYS_L1CACHE_BASE   + CMSYS_L1CACHE_SIZE         ),  1}, \
    {"cache_memory", (unsigned int *)0x04200000, (unsigned int *)0x04204000, 1},
    {0}
};

/* no dump region in minidump, must exist at least one element even if NULL. */
const char * minidump_region_filter[] = {
    "text",
    "non_cache_text",
    NULL
};

#if EXCEPTION_SLAVES_TOTAL > 0
extern void exception_dump_riscv_0(exception_dump_t *exception_dump);
void exception_alert_riscv_0(void);
void exception_forceddump_riscv_0(void);
exception_slave_status_t exception_check_status_riscv_0(void);
int  exception_ccni_query_event_status(uint32_t  event, uint32_t *data);

/* exception slaves' status */
exception_slave_status_t exceptionSlaveStatus[EXCEPTION_SLAVES_TOTAL] = {0};

/* exception slaves' configurations */
const exception_slaves_dump_t exceptionSlavesDump[EXCEPTION_SLAVES_TOTAL] = {
    {
        .slave_name = "riscv0",
        .slave_alert = exception_alert_riscv_0,
        .slave_checkstatus = exception_check_status_riscv_0,
        .slave_dump = exception_dump_riscv_0,
        .slave_forceddump = exception_forceddump_riscv_0,
        .is_dump = 1
    },
    // {0, 0, 0, 0, 0, 0}
};

#endif


/* Public functions ----------------------------------------------------------*/
#if (EXCEPTION_SLAVES_TOTAL > 0)
extern hal_hw_semaphore_status_t hw_semaphore_take(hal_hw_semaphore_id_t id);
extern hal_hw_semaphore_status_t hw_semaphore_give(hal_hw_semaphore_id_t id);
#endif


/******************************************************************************
 *  Name: exception_hw_semaphore_take
 ******************************************************************************/
#if (EXCEPTION_SLAVES_TOTAL > 0)
int32_t exception_hw_semaphore_take()
{
    return hw_semaphore_take(EXCEPTION_HW_SEMAPHORE);
}

/******************************************************************************
 *  Name: exception_hw_semaphore_give
 ******************************************************************************/
int32_t exception_hw_semaphore_give()
{
    return hw_semaphore_give(EXCEPTION_HW_SEMAPHORE);
}

#endif

/******************************************************************************
 *  Name: exception_core_status_read
 ******************************************************************************/
int exception_core_status_read()
{
#ifndef CONFIG_MCUBOOT
    if (HAL_CORE_EXCEPTION == hal_core_status_read(HAL_CORE_MCU)) {
        return 0;
    } else {
        return -1;
    }
#else
    return -1;
#endif
}

/******************************************************************************
 *  Name: exception_gpt_delay_ms
 ******************************************************************************/
int exception_gpt_delay_ms(uint32_t ms)
{
    return hal_gpt_delay_ms(ms);
}

/******************************************************************************
 *  Name: exception_disable_mpu
 ******************************************************************************/
void  exception_disable_mpu(void)
{
#ifdef HAL_MPU_MODULE_ENABLED
    hal_mpu_disable();
#endif
}

/******************************************************************************
 *  Name: exception_gpt_get_free_run_count
 ******************************************************************************/
void exception_gpt_get_free_run_count(uint32_t clock_source, uint32_t *count)
{
    if (clock_source == HAL_GPT_CLOCK_SOURCE_32K) {
        hal_gpt_get_free_run_count(clock_source, count);
    } else {
        hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, count);
    }
}

/******************************************************************************
 *  Name: exception_rtc_set_data
 ******************************************************************************/
int exception_rtc_set_data(uint16_t offset, const char *buf, uint16_t len)
{
#ifdef HAL_RTC_MODULE_ENABLED
    return hal_rtc_set_data(offset, buf, len);
#else
    return 0;
#endif
}

/******************************************************************************
 *  Name: exception_gpt_get_duration_count
 ******************************************************************************/
int  exception_gpt_get_duration_count(uint32_t start_count, uint32_t end_count, uint32_t *duration_count)
{
    return hal_gpt_get_duration_count(start_count, end_count, duration_count);
}
/******************************************************************************
*  Name: exception_ccni_query_event_status
******************************************************************************/
int  exception_ccni_query_event_status(uint32_t  event, uint32_t *data)
{
#ifdef HAL_CCNI_MODULE_ENABLED
    return hal_ccni_query_event_status(event, data);
#else
    (void)event;
    (void)data;
    return -1;
#endif
}
void system_advanced_power_save(void)
{
    for (hal_uart_port_t uart_port=HAL_UART_0; uart_port<HAL_UART_MAX; uart_port++) {
        hal_uart_deinit((uart_port));
    }
}

void exception_alert_riscv_0(void)
{
#ifdef HAL_CCNI_MODULE_ENABLED
    hal_ccni_status_t ret = hal_ccni_set_event(EXCEPTION_EVENT_TO_RISCV_0, NULL);
    if (0 != ret) {
        exception_printf("[exception]:mcu send ccni to riscv0 fail,ret = %d\r\n", ret);
    }
#endif
}

exception_slave_status_t exception_check_status_riscv_0(void)
{
#ifdef HAL_CCNI_MODULE_ENABLED
    uint32_t slave_status = 1;

    if (0 == exception_ccni_query_event_status(EXCEPTION_EVENT_TO_RISCV_0, &slave_status)) {
        if (slave_status == 0) {
            /* RISC-V is ready */
            return EXCEPTION_SLAVE_STATUS_READY;
        } else {
            /* RISC-V is not ready */
            return EXCEPTION_SLAVE_STATUS_IDLE;
        }
    }
#endif
    return EXCEPTION_SLAVE_STATUS_IDLE;
}

void exception_forceddump_riscv_0(void)
{
    hal_core_status_t core_status = hal_core_status_read(HAL_CORE_RISCV);
    if (core_status > HAL_CORE_OFF) {
        exception_enable_wdt_interrupt();
    } else {
        exception_printf("[exception]:force dump core status error:%d\r\n", core_status);
    }
}

void exception_core_status_update(void)
{
#ifndef CONFIG_MCUBOOT
    hal_core_status_write(HAL_CORE_MCU, HAL_CORE_EXCEPTION);
#endif
}

void exception_update_fota_status(void)
{

}

void exception_minidump_fota_status_clean(void)
{
    /* feed wdt to keep time for cleaning fota status */
    exception_feed_wdt();
#ifdef AIR_FOTA_ENABLE
    /* clean FOTA status to prevent FOTA upgrade after reboot */
    fota_state_write(0x0);
#endif
}


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

#if !defined(CONFIG_MCUBOOT) && defined(AIR_LOGGING_ENABLE)
__attribute__((weak)) void log_print_exception_msgid_log(uint8_t cpu_id, const char *message, uint32_t arg_cnt, ...)
{
    (void)cpu_id;
    (void)message;
    (void)arg_cnt;

}
#endif


/* The following code need to be removed, when AIR logging ready!! */
#if !defined(AIR_LOGGING_ENABLE)
#include "hal_uart.h"
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/* Public define -------------------------------------------------------------*/
/* RACE HEAD */
#define RACE_HEAD_CHANNEL_BYTE                  0x05
/* RACE TYPE */
#define RACE_TYPE_NOTIFICATION                  0x5D
/* RACE PROTOCOL ID */
#define RACE_PROTOCAL_SYSLOG_BEGIN              (0x0F00 | 0x10)
#define RACE_PROTOCAL_EXCEPTION_STRING_LOG      (0x0F00 | 0x12)
#define RACE_PROTOCAL_EXCEPTION_BINARY_LOG      (0x0F00 | 0x13)
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

static volatile uint32_t g_syslog_port = HAL_UART_0;
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
    /* race + exc_count + [data * 1] + NULL */
    mux_buffer_t log_buf_info[4];
    uint8_t *curr_data;
    uint32_t curr_size;

    uint8_t *pbuffer;

    curr_data = (uint8_t *)data;
    while (size > 0) {
        if (size >= MAX_EXCEPTION_DATA_LENGTH) {
            curr_size = MAX_EXCEPTION_DATA_LENGTH;
            size -= MAX_EXCEPTION_DATA_LENGTH;
        } else {
            curr_size = size;
            size = 0;
        }

        pbuffer = curr_data;

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
    uart_config.baudrate = HAL_UART_BAUDRATE_6000000;
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

void exception_wdt_warm_reset(void)
{
#ifdef HAL_WDT_MODULE_ENABLED
    extern void wdt_set_pmu_mask(uint32_t enable);
    wdt_set_pmu_mask(false); /* wdt always do cold reset, warm reset is configured by PMU */
    pmu_strup_rg_unlock();
    pmu_set_strup_rg_value(45, 0x1, 8, 0x0);
    pmu_get_strup_rg(45);
    pmu_strup_rg_lock();
#endif
}

/******************************************************************************
 *  Name: exception_dump_config_init
 ******************************************************************************/
int exception_dump_config_init(void)
{
#ifdef CONFIG_MCUBOOT
    printk("[Dump config]:0x%x\r\n", (unsigned int)exception_config_mode.exception_mode);
    return 0;
#else
    LOG_MSGID_I(exception, "[Dump config]:0x%x\r\n", 1, (unsigned int)exception_config_mode.exception_mode);
#if defined(AIR_NVKEY_ENABLE)
    nvkey_status_t nvkey_status = NVKEY_STATUS_OK;

    uint32_t size = 4;
    /* get user's exception dump configuartion */
    nvkey_status = nvkey_read_data(NVID_SYS_EXP_DUMP_MODE, (uint8_t *)&exception_config_mode.exception_mode, &size);
    if (NVKEY_STATUS_OK != nvkey_status) {
        LOG_MSGID_I(exception, "exception dump init fail because read nvkey fail,ret = %d\r\n", 1, nvkey_status);
    }
#endif //AIR_NVKEY_ENABLE
    LOG_MSGID_I(exception, "exception_nodump:%d\r\n", 1, exception_config_mode.exception_mode_t.exception_nodump);
    LOG_MSGID_I(exception, "exception_fulldump_text:%d\r\n", 1, exception_config_mode.exception_mode_t.exception_fulldump_text);
    LOG_MSGID_I(exception, "exception_fulldump_binary:%d\r\n", 1, exception_config_mode.exception_mode_t.exception_fulldump_binary);
    LOG_MSGID_I(exception, "exception_minidump:%d\r\n", 1, exception_config_mode.exception_mode_t.exception_minidump);
    LOG_MSGID_I(exception, "mask_irq_check_assert:%d\r\n", 1, exception_config_mode.exception_mode_t.mask_irq_check_assert);
    LOG_MSGID_I(exception, "reset_after_dump:%d\r\n", 1, exception_config_mode.exception_mode_t.reset_after_dump);
    LOG_MSGID_I(exception, "wdt_reset_mode:%d\r\n", 1, exception_config_mode.exception_mode_t.wdt_reset_mode);
    LOG_MSGID_I(exception, "wdt_reset_latch_pc:%d\r\n", 1, exception_config_mode.exception_mode_t.systemhang_pmic_mode);
    LOG_MSGID_I(exception, "disable_all_log:%d\r\n", 1, exception_config_mode.exception_mode_t.disable_all_log);
    LOG_MSGID_I(exception, "advanced_power_save:%d\r\n", 1, exception_config_mode.exception_mode_t.advanced_power_save);
    LOG_MSGID_I(exception, "[Dump config]:0x%x\r\n", 1, (unsigned int)exception_config_mode.exception_mode);

    if (exception_config_mode.exception_mode_t.disable_all_log){
#ifdef AIR_BYPASS_SYSLOG_WITH_LOG_FLOW_ENABLE
        mux_clear_sw_wptr(syslog_port_get_uart_log());
#endif
        log_global_turn_off();
    }
    if (exception_config_mode.exception_mode_t.advanced_power_save){
        system_advanced_power_save();
    }

    if (exception_config_mode.exception_mode_t.systemhang_pmic_mode) {
        exception_wdt_warm_reset();
    }
    if (exception_config_mode.exception_mode_t.wdt_reset_mode) {
#ifdef HAL_WDT_MODULE_ENABLED
        wdt_exception_config_internal_use(10);
#endif
    }
  return 0;
#endif
}

/* special for system lowpower */
void system_disable_all_log(void){
    exception_config_mode.exception_mode_t.disable_all_log = 1;
#ifdef AIR_BYPASS_SYSLOG_WITH_LOG_FLOW_ENABLE
    mux_clear_sw_wptr(syslog_port_get_uart_log());
#endif
    log_global_turn_off();
}

void system_disable_uart_to_save_power(void){
    exception_config_mode.exception_mode_t.advanced_power_save = 1;
    system_advanced_power_save();
}

void exception_set_enable_all_log_flag(void)
{
    exception_config_mode.exception_mode_t.disable_all_log = 0;
#if defined(AIR_BYPASS_SYSLOG_WITH_LOG_FLOW_ENABLE) && defined(AIR_SOC_CROSS_CORE_MEMORY_ENABLE)
    ccm_disable_all_log[0] = 0;
#endif
}

/******************************************************************************
 *  Name: exception_get_disable_all_log_flag
 ******************************************************************************/
int exception_get_disable_all_log_flag(void)
{
    return  exception_config_mode.exception_mode_t.disable_all_log;
}

int exception_get_wdt_reset_mode_flag(void)
{
    return  exception_config_mode.exception_mode_t.wdt_reset_mode;
}

int exception_get_advanced_power_save_flag(void)
{
    return  exception_config_mode.exception_mode_t.advanced_power_save;
}

/******************************************************************************
 *  Name: exception_dump_config_init
 ******************************************************************************/
SYS_INIT(exception_dump_config_init, CONFIG_EXCEPTION_DUMP_INIT_LEVEL, CONFIG_EXCEPTION_DUMP_INIT_PRIORITY);

/******************************************************************************
 *  Name: exception_feed_wdt
 ******************************************************************************/
void exception_feed_wdt(void)
{
#ifdef HAL_WDT_MODULE_ENABLED
    hal_wdt_feed(HAL_WDT_FEED_MAGIC);
#endif
}

/******************************************************************************
 *  Name: exception_disable_cache
 ******************************************************************************/
void exception_disable_cache(void)
{
    hal_cache_disable();
}

/******************************************************************************
 *  Name: exception_enable_wdt_reset
 ******************************************************************************/
void exception_enable_wdt_reset(void)
{
#ifdef HAL_WDT_MODULE_ENABLED

    /* config wdt as reset mode and timeout is 90s */
    wdt_exception_config_internal_use(90);

    extern exception_config_mode_t exception_config_mode;
    if (exception_config_mode.exception_mode_t.systemhang_pmic_mode) {
        exception_printf("[exception]:WDT reset config as PMIC mode");
        exception_wdt_warm_reset();
    }
#endif
    exception_wdt_mode = EXCEPTION_WDT_RESET;
}

/******************************************************************************
 *  Name: exception_disable_wdt_reset
 ******************************************************************************/
void exception_disable_wdt_reset(void)
{
#ifdef HAL_WDT_MODULE_ENABLED
    if (exception_wdt_mode == EXCEPTION_WDT_RESET) {
        hal_wdt_disable(HAL_WDT_DISABLE_MAGIC);
    }
#endif
}

/******************************************************************************
 *  Name: exception_enable_wdt_interrupt
 ******************************************************************************/
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

/******************************************************************************
 *  Name: exception_reboot
 ******************************************************************************/
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
        exception_wdt_warm_reset();
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

/******************************************************************************
 *  Name: exception_MPU_setting
 ******************************************************************************/
__attribute__((__section__(".exception_code")))  void exception_MPU_setting(void)
{
#ifdef HAL_MPU_MODULE_ENABLED
    hal_mpu_region_disable(HAL_MPU_REGION_0);
#endif
}

/******************************************************************************
 *  Name: exception_ice_debug_is_enable
 ******************************************************************************/
bool exception_ice_debug_is_enable(void)
{
    return false;
}
void exception_ice_debug_test(void)
{

}

#endif /* AIR_EXCEPTION_HANDLER_ENABLE */
