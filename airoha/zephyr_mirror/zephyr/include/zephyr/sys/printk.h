/* printk.h - low-level debug output */

/*
 * Copyright (c) 2010-2012, 2014 Wind River Systems, Inc.
 * Copyright (c) 2026 Airoha Technology Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Modifications:
2026-03-13 by Airoha - re-define printk macro.
*/

#ifndef ZEPHYR_INCLUDE_SYS_PRINTK_H_
#define ZEPHYR_INCLUDE_SYS_PRINTK_H_

#include <zephyr/toolchain.h>
#include <stddef.h>
#include <stdarg.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 * @brief Print kernel debugging message.
 *
 * This routine prints a kernel debugging message to the system console.
 * Output is send immediately, without any mutual exclusion or buffering.
 *
 * A basic set of conversion specifier characters are supported:
 *   - signed decimal: \%d, \%i
 *   - unsigned decimal: \%u
 *   - unsigned hexadecimal: \%x (\%X is treated as \%x)
 *   - pointer: \%p
 *   - string: \%s
 *   - character: \%c
 *   - percent: \%\%
 *
 * Field width (with or without leading zeroes) is supported.
 * Length attributes h, hh, l, ll and z are supported. However, integral
 * values with %lld and %lli are only printed if they fit in a long
 * otherwise 'ERR' is printed. Full 64-bit values may be printed with %llx.
 * Flags and precision attributes are not supported.
 *
 * @param fmt Format string.
 * @param ... Optional list of format arguments.
 */
#ifdef CONFIG_PRINTK

#if defined(AIR_LOGGING_ENABLE)
#include "air_logging.h"
#include "memory_attribute.h"
extern __printf_like(1, 0) void vprintk(const char *fmt, va_list ap);
extern void airoha_printk(const char *fmt, uint32_t arg_cnt, ...);
#if !defined(__cplusplus)
#define printk(fmt, ...) \
do { \
	__attribute__((__section__(".log_strings"))) static const char _fmt[] = fmt; \
	airoha_printk(_fmt, COUNT_ARGS(__VA_ARGS__), ##__VA_ARGS__); \
} while(0)
#else
#define EXPAND_CONCAT(x, y)    x##y
#define EXP_AT_LINE(name, line) EXPAND_CONCAT(name##_at_line_, line)
#define printk(fmt, ...) do { \
	static const char EXP_AT_LINE(_fmt, __LINE__)[] ATTR_DATA_DECLARE(".log_string") = fmt; \
	airoha_printk(EXP_AT_LINE(_fmt, __LINE__), COUNT_ARGS(__VA_ARGS__), ##__VA_ARGS__); \
} while(0)
#endif
#else
extern __printf_like(1, 2) void printk(const char *fmt, ...);
extern __printf_like(1, 0) void vprintk(const char *fmt, va_list ap);
#endif

#else
static inline __printf_like(1, 2) void printk(const char *fmt, ...)
{
	ARG_UNUSED(fmt);
}

static inline __printf_like(1, 0) void vprintk(const char *fmt, va_list ap)
{
	ARG_UNUSED(fmt);
	ARG_UNUSED(ap);
}
#endif

#ifdef CONFIG_PICOLIBC

#include <stdio.h>

#define snprintk(...) snprintf(__VA_ARGS__)
#define vsnprintk(str, size, fmt, ap) vsnprintf(str, size, fmt, ap)

#else

__printf_like(3, 4) int snprintk(char *str, size_t size,
					const char *fmt, ...);
__printf_like(3, 0) int vsnprintk(char *str, size_t size,
					  const char *fmt, va_list ap);

#endif

#ifdef __cplusplus
}
#endif

#endif
