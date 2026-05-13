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

#ifndef _EXCEPTION_HANDLER_H_
#define _EXCEPTION_HANDLER_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(AIR_EXCEPTION_HANDLER_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "stdarg.h"
#include <stdint.h>
#include <string.h>
#include "exception_nvkey_struct.h"
#include "exception_config.h"

/* Public define -------------------------------------------------------------*/
#define DISABLE_MEMDUMP_MAGIC                           0xdeadbeef
#define DISABLE_WHILELOOP_MAGIC                         0xdeadaaaa

#define EXCEPTION_WDT_INTERRUPT                         0xdeadbbbb
#define EXCEPTION_WDT_RESET                             0xdeadcccc

#define EXCEPTION_MEMDUMP_NODUMP                        0x01
#define EXCEPTION_MEMDUMP_TEXT                          0x02
#define EXCEPTION_MEMDUMP_BINARY                        0x04
#define EXCEPTION_MEMDUMP_MINIDUMP                      0x08
#define MASK_IRQ_TOO_LONG_ASSERT                        0x10
#define EXCEPTION_DUMP_DISABLE_WHILELOOP                0x20
#define EXCEPTION_DUMMY_BIT                             0x80

#if (EXCEPTION_MEMDUMP_MODE == EXCEPTION_MEMDUMP_MINIDUMP)
extern int printf_dummy(const char *message, ...);
extern int msgid_dummy(uint8_t cpu_id, const char *message, uint32_t arg_cnt, ...);
#define platform_printf                                 printf_dummy
#define exception_printf                                printf_dummy
#define exception_msgid                                 msgid_dummy
extern void log_dump_exception_data(const uint8_t *data, uint32_t size);

#elif (EXCEPTION_MEMDUMP_MODE & EXCEPTION_MEMDUMP_TEXT)
extern int log_print_exception_log(const char *message, ...);
extern void log_print_exception_msgid_log(uint8_t cpu_id, const char *message, uint32_t arg_cnt, ...);
#define platform_printf                                 printf
#define exception_printf                                log_print_exception_log
#define exception_msgid                                 EXCEPTION_MSGID_DEFAULT

#elif (EXCEPTION_MEMDUMP_MODE & EXCEPTION_MEMDUMP_BINARY)
extern int log_print_exception_log(const char *message, ...);
#if defined(CONFIG_MCUBOOT) && !defined(AIR_LOGGING_ENABLE)
#define log_print_exception_msgid_log(cpu_id, message, arg_cnt, ...) log_print_exception_log(message, ##__VA_ARGS__)
#else
extern void log_print_exception_msgid_log(uint8_t cpu_id, const char *message, uint32_t arg_cnt, ...);
#endif
extern void log_dump_exception_data(const uint8_t *data, uint32_t size);
#define platform_printf                                 printf
#define exception_printf                                log_print_exception_log
#define exception_msgid                                 log_print_exception_msgid_log

#else
#define platform_printf                                 printf
#define exception_printf                                printf
#define exception_msgid                                 EXCEPTION_MSGID_DEFAULT
#endif /* EXCEPTION_MEMDUMP_MODE */


#if (EXCEPTION_MEMDUMP_MODE & EXCEPTION_MEMDUMP_MINIDUMP)
typedef struct {
    uint8_t header[10];
    uint32_t text_index;
    uint32_t binary_index;
} exception_minidump_race_t;
typedef struct {
    exception_minidump_race_t race;
    uint32_t start_address;
    uint32_t write_address;
    uint32_t cell_size;
    uint32_t pkt_size;
} exception_minidump_context_t;

typedef struct {
    uint32_t address;
    uint32_t size;
} exception_minidump_region_t;

typedef struct {
    uint32_t is_match;
    uint32_t overflow_address;
} exception_minidump_overflow_t;

typedef struct {
    uint32_t is_valid;
    const char *expr;
    const char *file;
    uint32_t line;
} exception_minidump_assert_t;

typedef struct {
    uint32_t core_num;
    uint32_t core_size[1 + EXCEPTION_SLAVES_TOTAL];
    uint32_t length;
    char name[20];
    uint32_t reason;
    exception_minidump_assert_t assert_info;
    exception_minidump_overflow_t overflow_info;
    uint32_t context_size;
    exception_minidump_region_t regions[20];
    uint32_t data_checksum;
} exception_minidump_header_t;
#endif /* EXCEPTION_MEMDUMP_MODE */

/* Public typedef ------------------------------------------------------------*/
typedef enum {
    EXCEPTION_STATUS_ERROR = 0,
    EXCEPTION_STATUS_OK = 1
} exception_status_t;

typedef enum {
    EXCEPTION_TEXT = 0,
    EXCEPTION_BINARY = 1
} exception_log_type_t;

typedef struct {
    uint32_t is_valid;
    const char *expr;
    const char *file;
    uint32_t line;
    const char *string;
} assert_expr_t;

typedef struct {
    char *region_name;
    unsigned int *start_address;
    unsigned int *end_address;
    unsigned int is_dumped;
} memory_region_type;

typedef void (*f_exception_callback_t)(void);

typedef struct {
    f_exception_callback_t init_cb;
    f_exception_callback_t dump_cb;
} exception_config_type;

typedef enum {
    EXCEPTION_SLAVE_STATUS_ERROR = -1,
    EXCEPTION_SLAVE_STATUS_IDLE = 0,
    EXCEPTION_SLAVE_STATUS_READY = 1,
    EXCEPTION_SLAVE_STATUS_FINISH = 2
} exception_slave_status_t;


typedef enum {
    EXCEPTION_DUMP_NONE,
    EXCEPTION_DUMP_TEXT,
    EXCEPTION_DUMP_BINARY,
    EXCEPTION_DUMP_REGION_INFO,
} exception_dump_type_t;

typedef int (*exception_log_printf_t)(const char *fmt, ...);
typedef int (*exception_memory_dump_t)(const uint8_t *data, uint32_t size);

typedef struct {
    exception_log_printf_t exception_log_printf;
    exception_memory_dump_t exception_memory_dump;
} exception_dump_ops_t;

typedef struct {
#if (EXCEPTION_MEMDUMP_MODE & EXCEPTION_MEMDUMP_MINIDUMP)
    exception_minidump_context_t *ctx;/*Only for minidump */
#endif
    exception_dump_ops_t ops;
    uint32_t dump_len_limit;
    uint32_t dump_len_current;
    uint32_t dump_type;
} exception_dump_t;

extern exception_dump_t exception_mini_dump;
extern exception_dump_t exception_binary_dump;

uint32_t exception_dump_regions(exception_dump_t *dump, const memory_region_type *regions, uint32_t regions_count, exception_dump_type_t dump_type);

typedef void (*f_exception_slave_alert_callback_t)(void);
typedef exception_slave_status_t (*f_exception_slave_checkstatus_callback_t)(void);
typedef void (*f_exception_slave_dump_callback_t)(exception_dump_t *exception_dump);
typedef void (*f_exception_slave_forceddump_callback_t)(void);
typedef struct {
    const char *slave_name;
    f_exception_slave_alert_callback_t slave_alert;
    f_exception_slave_checkstatus_callback_t slave_checkstatus;
    f_exception_slave_dump_callback_t slave_dump;
    f_exception_slave_forceddump_callback_t slave_forceddump;
    unsigned int is_dump;
} exception_slaves_dump_t;
// #define EXC_DEBUG
#ifdef EXC_DEBUG
#define exc_log(_message,...)       exception_printf(_message,##__VA_ARGS__)
#else
#define exc_log(_message,...)
#endif

/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
void exception_feed_wdt(void);
void exception_enable_wdt_reset(void);
void exception_enable_wdt_interrupt(void);
void exception_get_assert_expr(const char **expr, const char **file, int *line);
void platform_assert(const char *expr, const char *file, int line);
void light_assert(const char *expr, const char *file, int line);
void light_assert_ex(const char *msg);
void exception_dump_config(int flag);
void exception_reboot(void);
exception_status_t exception_register_callbacks(exception_config_type *cb);
exception_status_t exception_register_regions(memory_region_type *region);

int exception_get_disable_all_log_flag(void);
int exception_get_wdt_reset_mode_flag(void);
int exception_get_advanced_power_save_flag(void);

#if (EXCEPTION_MEMDUMP_MODE & EXCEPTION_MEMDUMP_MINIDUMP)
exception_status_t exception_minidump_region_query_info(uint32_t index, uint32_t *address, uint32_t *length);
exception_status_t exception_minidump_region_query_count(uint32_t *count);
exception_status_t exception_minidump_region_query_latest_index(uint32_t *index);
exception_status_t exception_minidump_get_header_info(uint32_t address, uint8_t **header_address, uint32_t *size);
exception_status_t exception_minidump_get_assert_info(uint32_t address, char **file, uint32_t *line);
exception_status_t exception_minidump_get_context_info(uint32_t address, uint8_t **context_address, uint32_t *size);
exception_status_t exception_minidump_get_stack_info(uint32_t address, uint8_t **stack_address, uint32_t *size);
exception_status_t exception_minidump_check_not_duplicated(void);
#endif /* EXCEPTION_MEMDUMP_MODE */

#endif /* AIR_EXCEPTION_HANDLER_ENABLE */

#ifdef __cplusplus
}
#endif

#endif /* _EXCEPTION_HANDLER_H_ */
