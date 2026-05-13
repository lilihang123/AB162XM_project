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

#ifndef __HAL_CROSS_CORE_CONFIG_H__
#define __HAL_CROSS_CORE_CONFIG_H__

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <assert.h>
#include "hal_eint_internal.h"

#ifdef HAL_HW_SEMAPHORE_MODULE_ENABLED
/**
 * @addtogroup HAL
 * @{
 * @addtogroup HW_SEMAPHORE
 * @{
 * @defgroup hal_hw_semaphore_define Define
 * @{
 */
#define HW_SEMAPHORE_SYSLOG                   0           /* @brief This macro defines the SEMAPHORE for SYSLOG. */
#define HW_SEMAPHORE_EXCEPTION                1           /* @brief This macro defines the SEMAPHORE for EXCEPTION. */
#define HW_SEMAPHORE_HB                       2           /* @brief This macro defines the SEMAPHORE for HB. */
#define HW_SEMAPHORE_AUDIO_SINK               3           /* @brief This macro defines the SEMAPHORE for AUDIO_SINK. */
#define HW_SEMAPHORE_DSP_CIRCULAR_BUFFER      4           /* @brief This macro defines the SEMAPHORE for CIRCULAR_BUFFER. */
#define HW_SEMAPHORE_DVFS                     5           /* @brief This macro defines the SEMAPHORE for DVFS. */
#define HW_SEMAPHORE_AUDIO_CM4_DSP0_PLAYBACK  6           /* @brief This macro defines the DSP0_PLAYBACK. */
#define HW_SEMAPHORE_SLEEP                    7           /* @brief This macro defines the SEMAPHORE for SLEEP. */
#define HW_SEMAPHORE_SYSLOG_WRAPER            8           /* @brief This macro defines the SEMAPHORE for syslog porting layer. */
#define HW_SEMAPHORE_MUX                      9           /* @brief This macro defines the SEMAPHORE for mux layer. */
#define HW_SEMAPHORE_TRNG                     10          /* @brief This macro defines the SEMAPHORE for TRNG. */
#define HW_SEMAPHORE_PMU                      11          /* @brief This macro defines the SEMAPHORE for PMU. */

/**
  * @}
  */

/**
 * @}
 * @}
 */

#endif

#ifdef HAL_CCNI_MODULE_ENABLED
/**
 * @addtogroup HAL
 * @{
 * @addtogroup HW_CCNI
 * @{
 * @defgroup hal_ccni_define Define
 * @{
 */
#define CCNI_EVENT_TEST                   0           /* @brief This macro defines the test event for ccni. */

/**
  * @}
  */

/**
 * @}
 * @}
 */
#endif /* HAL_CCNI_MODULE_ENABLED */


#define CROSS_CORE_CONS(MODULE)    ccm_ ##MODULE

#define CROSS_CORE_MEM_EXTERN(MODULE, LEN) \
            extern volatile uint8_t CROSS_CORE_CONS(MODULE)[LEN]

#define CROSS_CORE_MEM_VARIABLE(MODULE) \
            CROSS_CORE_CONS(MODULE)

#define CROSS_CORE_MEM_DEFINE(MODULE, LEN) \
            ATTR_SHARE_ZIDATA volatile uint8_t CROSS_CORE_CONS(MODULE)[LEN]


#include "hal_ccni_config.h"
#define CCM_CCNI_LEN                 (CCNI_CORE_NUMS*HAL_CCNI_SUPPORT_MSG_MAX*sizeof(hal_ccni_message_t))
#define CCM_CORE_STATUS_LEN          (CCNI_CORE_NUMS*sizeof(uint32_t))
#include "hal_uart_internal.h"
#define CCM_SYSLOG_PARA_LEN          (sizeof(uart_backup_para_for_log_t))

#if defined(AIR_EXCEPTION_HANDLER_ENABLE)
/*The size is related to exception_sharemem_riscv_t structure. */
#define CCM_EXCEPTION_RISCV_SHARE_MEM_LEN_0 396
#endif

#if defined(AIR_ADC_KEYSCAN_ENABLE)
#include "adc_keyscan.h"
#define CCM_ADC_KEYSCAN_DATA_BUF_LEN     (sizeof(sw_keyscan_data_buf_info_t))
#define CCM_ADC_KEYSCAN_INFO_LEN     (sizeof(sw_keyscan_info_t))
#endif

#define EINT_TIMESTAMP_LEN           (EINT_COUNTER_NUMBER_MUX*sizeof(uint32_t))

#if defined(AIR_SOC_CROSS_CORE_MEMORY_ENABLE)
CROSS_CORE_MEM_EXTERN(ccni, CCM_CCNI_LEN);

CROSS_CORE_MEM_EXTERN(core_status, CCM_CORE_STATUS_LEN);

CROSS_CORE_MEM_EXTERN(spi_sensor, 16);
#ifdef AIR_KEYBOARD_M607
CROSS_CORE_MEM_EXTERN(spi_tx_data, 16);
#endif

CROSS_CORE_MEM_EXTERN(syslog_uart_para, CCM_SYSLOG_PARA_LEN);

CROSS_CORE_MEM_EXTERN(eint_count, EINT_TIMESTAMP_LEN);

#if defined(AIR_ADC_KEYSCAN_ENABLE)
CROSS_CORE_MEM_EXTERN(adc_keyscan_buf_info, CCM_ADC_KEYSCAN_DATA_BUF_LEN);
CROSS_CORE_MEM_EXTERN(adc_keyscan_cfg_info, CCM_ADC_KEYSCAN_INFO_LEN);
#endif

#if defined(AIR_PKA_SHARE_ENABLE)
#include "pka_share.h"
CROSS_CORE_MEM_EXTERN(pka_share, sizeof(pka_share_info));
#endif

#if defined(AIR_HID_COMMON_MEMORY)
#include "hid_common.h"
CROSS_CORE_MEM_EXTERN(hid_common_para, sizeof(hid_common_info));
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
CROSS_CORE_MEM_EXTERN(trigger_mode_status, sizeof(T_TRIGGER_MODE_S));
#endif
#endif

#if defined(AIR_MUX_ENABLE)
//#ifndef MTK_SINGLE_CPU_ENV
//#include "mux_port_device.h"
CROSS_CORE_MEM_EXTERN(mux, 0x200);
//#endif /* not defined(MTK_SINGLE_CPU_ENV) */
#endif /* defined(AIR_MUX_ENABLE) */

#if defined(AIR_EXCEPTION_HANDLER_ENABLE)
CROSS_CORE_MEM_EXTERN(exception_risc_v_0, CCM_EXCEPTION_RISCV_SHARE_MEM_LEN_0);
#endif

#if defined(AIR_BYPASS_SYSLOG_WITH_LOG_FLOW_ENABLE)
CROSS_CORE_MEM_EXTERN(disable_all_log, 1);
#endif
#endif /* defined(AIR_SOC_CROSS_CORE_MEMORY_ENABLE) */


#endif    //__HAL_CROSS_CORE_CONFIG_H__
