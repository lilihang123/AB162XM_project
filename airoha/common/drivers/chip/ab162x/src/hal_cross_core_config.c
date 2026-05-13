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

#include "hal_cross_core_config.h"

#include "memory_attribute.h"
#if defined(AIR_SHARE_BUFFER_ENABLE)
#include "share_buffer.h"
#endif /* AIR_SHARE_BUFFER_ENABLE */
#if defined(AIR_EXCEPTION_HANDLER_ENABLE)
#include "exception_handler.h"
#endif /* AIR_EXCEPTION_HANDLER_ENABLE */

#ifdef __cplusplus
extern "C" {
#endif

#if defined(AIR_SOC_CROSS_CORE_MEMORY_ENABLE)

CROSS_CORE_MEM_DEFINE(ccni, CCM_CCNI_LEN);

CROSS_CORE_MEM_DEFINE(core_status, CCM_CORE_STATUS_LEN);

ATTR_ALIGN(16) CROSS_CORE_MEM_DEFINE(spi_sensor, 16);
#ifdef AIR_KEYBOARD_M607
ATTR_ALIGN(16) CROSS_CORE_MEM_DEFINE(spi_tx_data, 16);
#endif

CROSS_CORE_MEM_DEFINE(syslog_uart_para, CCM_SYSLOG_PARA_LEN);

CROSS_CORE_MEM_DEFINE(eint_count, EINT_TIMESTAMP_LEN);

#if defined(AIR_ADC_KEYSCAN_ENABLE)
CROSS_CORE_MEM_DEFINE(adc_keyscan_buf_info, CCM_ADC_KEYSCAN_DATA_BUF_LEN);
CROSS_CORE_MEM_DEFINE(adc_keyscan_cfg_info, CCM_ADC_KEYSCAN_INFO_LEN);
#endif

#if defined(AIR_LOGGING_ENABLE)
CROSS_CORE_MEM_DEFINE(syslog, (0x168)); /* multi domain info 4B + share buffer info + 8K syslog buffer */
CROSS_CORE_MEM_DEFINE(sw_verno_str, (0x90)); /* version str */
CROSS_CORE_MEM_DEFINE(build_date_time_str, (0x90)); /* build time str */

#if defined(CORE_RISCV)
#include "syslog.h"
log_create_module(common, PRINT_LEVEL_INFO);
#endif
#endif /* AIR_LOGGING_ENABLE */

#if defined(AIR_EXCEPTION_HANDLER_ENABLE)
ATTR_ALIGN(4) CROSS_CORE_MEM_DEFINE(exception_risc_v_0, CCM_EXCEPTION_RISCV_SHARE_MEM_LEN_0);
// ATTR_ALIGN(4) CROSS_CORE_MEM_DEFINE(exception_ns_info, 0x100);
#endif /* AIR_EXCEPTION_HANDLER_ENABLE */

#if defined(AIR_PKA_SHARE_ENABLE)
CROSS_CORE_MEM_DEFINE(pka_share, sizeof(pka_share_info));
#endif

#if defined(AIR_HID_COMMON_MEMORY)
CROSS_CORE_MEM_DEFINE(hid_common_para, sizeof(hid_common_info));
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
CROSS_CORE_MEM_DEFINE(trigger_mode_status, sizeof(T_TRIGGER_MODE_S));
#endif
#endif

#if defined(AIR_MUX_ENABLE)
//#ifndef MTK_SINGLE_CPU_ENV
CROSS_CORE_MEM_DEFINE(mux, 0x200);
//#endif /* not defined(MTK_SINGLE_CPU_ENV) */
#endif /* defined(AIR_MUX_ENABLE) */
#if defined(AIR_BYPASS_SYSLOG_WITH_LOG_FLOW_ENABLE)
CROSS_CORE_MEM_DEFINE(disable_all_log, 1);
#endif
#endif /* defined(AIR_SOC_CROSS_CORE_MEMORY_ENABLE) */

#ifdef __cplusplus
}
#endif


