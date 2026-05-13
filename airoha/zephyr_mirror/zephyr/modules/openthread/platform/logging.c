/*
 * Copyright (c) 2018 - 2020 Nordic Semiconductor ASA
 * Copyright (c) 2026 Airoha Technology Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 
/* Modifications:
2026-03-12 by Airoha - Airoha logging implementation
*/

#include <zephyr/kernel.h>
#include <stdarg.h>
#include <stdio.h>
#include <openthread/platform/logging.h>
#include "openthread-core-zephyr-config.h"
#if defined(AIR_LOGGING_ENABLE)
#include "air_logging.h"
#endif
#define LOG_MODULE_NAME net_openthread
#define LOG_LEVEL LOG_LEVEL_DBG
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

#include "platform-zephyr.h"

/* Convert OT log level to zephyr log level. */
static inline int log_translate(otLogLevel aLogLevel)
{
	switch (aLogLevel) {
	case OT_LOG_LEVEL_NONE:
	case OT_LOG_LEVEL_CRIT:
		return LOG_LEVEL_ERR;
	case OT_LOG_LEVEL_WARN:
		return LOG_LEVEL_WRN;
	case OT_LOG_LEVEL_NOTE:
	case OT_LOG_LEVEL_INFO:
		return LOG_LEVEL_INF;
	case OT_LOG_LEVEL_DEBG:
		return LOG_LEVEL_DBG;
	default:
		break;
	}

	return -1;
}

void otPlatLog(otLogLevel aLogLevel, otLogRegion aLogRegion, const char *aFormat, ...)
{
	ARG_UNUSED(aLogRegion);

#if defined(CONFIG_LOG)
	int level = log_translate(aLogLevel);
	va_list param_list;

	if (level < 0) {
		return;
	}

	va_start(param_list, aFormat);
#if defined(AIR_LOGGING_ENABLE)
	string_log_handler(	NULL,
						NULL,
						0,
						level,
						aFormat,
						param_list,
						NULL,
						0);
#else
	log_generic(level, aFormat, param_list);
#endif
	va_end(param_list);
#else
	ARG_UNUSED(aLogLevel);
	ARG_UNUSED(aFormat);
#endif

}

