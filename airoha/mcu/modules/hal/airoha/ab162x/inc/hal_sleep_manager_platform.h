/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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

#include "hal_platform.h"

#ifndef __HAL_SLEEP_MANAGER_PLATFORM_H__
#define __HAL_SLEEP_MANAGER_PLATFORM_H__

#ifdef HAL_SLEEP_MANAGER_ENABLED

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    SLEEP_LOCK_TRNG                        = 0,
    SLEEP_LOCK_DMA                         = 1,
    SLEEP_LOCK_IRTX                        = 2,
    SLEEP_LOCK_IRRX                        = 3,
    SLEEP_LOCK_AIO                         = 4,
    //SLEEP_LOCK_ESC                         = 9,
    SLEEP_LOCK_SPI_MST0                    = 5,
    SLEEP_LOCK_SPI_MST1                    = 6,
    SLEEP_LOCK_SPI_MST2                    = 7,
    SLEEP_LOCK_SPI_SLV                     = 8,
    SLEEP_LOCK_DCXO                        = 9,
    SLEEP_LOCK_I3C1                        = 10,
    SLEEP_LOCK_I3C0                        = 11,
    SLEEP_LOCK_USB                         = 12,    /* Handle lock, enter pure idle */
    SLEEP_LOCK_UART0                       = 13,
    SLEEP_LOCK_UART1                       = 14,
    SLEEP_LOCK_UART2                       = 15,
    SLEEP_LOCK_BT_CONTROLLER               = 16,    /* Handle lock, enter pure idle */
    SLEEP_LOCK_RACE_CMD                    = 17,
    SLEEP_LOCK_APP                         = 18,
    SLEEP_LOCK_APP_PURE                    = 19,    /* Handle lock, enter pure idle */
    SLEEP_LOCK_PWM_DMA0                    = 20,
    SLEEP_LOCK_PWM_DMA1                    = 21,
    SLEEP_LOCK_USER_START_ID               = 22,
    SLEEP_LOCK_INVALID_ID                  = 0xFF
} sleep_management_lock_request_t;

typedef enum {
    SLEEP_LOCK_EXTEND_SECURITY_PD          = 0,
    SLEEP_LOCK_EXTEND_AESOTF               = 1,
    SLEEP_LOCK_EXTEND_ESC_AESOTF           = 2,
    SLEEP_LOCK_EXTEND_TRNG                 = 3,
    SLEEP_LOCK_EXTEND_DMA                  = 4,
    SLEEP_LOCK_EXTEND_IRTX                 = 5,
    SLEEP_LOCK_EXTEND_IRRX                 = 6,
    SLEEP_LOCK_EXTEND_AIO                  = 7,
    SLEEP_LOCK_EXTEND_FLASH                = 8,
    SLEEP_LOCK_EXTEND_ESC                  = 9,
    SLEEP_LOCK_EXTEND_SPI_MST2             = 10,
    SLEEP_LOCK_EXTEND_SPI_SLV              = 11,
    SLEEP_LOCK_EXTEND_DCXO                 = 12,
    SLEEP_LOCK_EXTEND_SAR_ADC              = 13,
    SLEEP_LOCK_EXTEND_I3C1                 = 14,
    SLEEP_LOCK_EXTEND_I3C1_DMA             = 15,
    SLEEP_LOCK_EXTEND_USB                  = 16,
    SLEEP_LOCK_EXTEND_APP                  = 17,
    SLEEP_LOCK_EXTEND_USER_START_ID        = 18,
    SLEEP_LOCK_EXTEND_INVALID_ID           = 0xFF
} sleep_management_lock_extend_request_t;

typedef enum {
    SLEEP_LOCK_TICKLESS_IDLE_APP                  = 0,
    SLEEP_LOCK_TICKLESS_IDLE_USER_START_ID        = 1,
    SLEEP_LOCK_TICKLESS_IDLE_INVALID_ID           = 0xFF
} sleep_management_lock_tickless_idle_request_t;

typedef enum {
    SLEEP_BACKUP_RESTORE_UART              = 0,    /* Temporary reserved for UART_VDMA restore */
    SLEEP_BACKUP_RESTORE_SPI_MST0          = 1,    /* Temporary reserved for build pass */
    SLEEP_BACKUP_RESTORE_SPI_MST1          = 2,    /* Temporary reserved for build pass */
    SLEEP_BACKUP_RESTORE_SPI_MST2          = 3,    /* Temporary reserved for build pass */
    SLEEP_BACKUP_RESTORE_APP               = 4,
    SLEEP_BACKUP_RESTORE_VRF_BUCK_SWITCH   = 5,
    SLEEP_BACKUP_RESTORE_MODULE_MAX        = 6,
    SLEEP_BACKUP_RESTORE_USER              = 7
} sleep_management_backup_restore_module_t;

typedef enum {
    INFRA_PD_BACKUP_RESTORE_AESOTF         = 0,
    INFRA_PD_BACKUP_RESTORE_ESC_AESOTF     = 1,
    INFRA_PD_BACKUP_RESTORE_FLASH          = 2,
    INFRA_PD_BACKUP_RESTORE_ESC            = 3,
    INFRA_PD_BACKUP_RESTORE_SPIMST_2       = 4,
    INFRA_PD_BACKUP_RESTORE_SPI_SLV        = 5,
    INFRA_PD_BACKUP_RESTORE_I3C1           = 6,
    INFRA_PD_BACKUP_RESTORE_SAR_ADC        = 7,
    INFRA_PD_BACKUP_RESTORE_MODULE_MAX     = 8,
    INFRA_PD_BACKUP_RESTORE_USER           = 9
} sleep_management_infra_pd_backup_restore_module_t;

#define SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX 8
#define DEEP_SLEEP_GPT HAL_GPT_0

typedef enum {
    INFRA_PD_MODULE_SECURITY_PD            = 0,
    INFRA_PD_MODULE_AESOTF                 = 1,
    INFRA_PD_MODULE_ESC_AESOTF             = 2,
    INFRA_PD_MODULE_TRNG                   = 3,
    INFRA_PD_MODULE_DMA                    = 4,
    INFRA_PD_MODULE_IRTX                   = 5,
    INFRA_PD_MODULE_IRRX                   = 6,
    INFRA_PD_MODULE_AIO                    = 7,
    INFRA_PD_MODULE_FLASH                  = 8,
    INFRA_PD_MODULE_ESC                    = 9,
    INFRA_PD_MODULE_SPI_MST2               = 10,
    INFRA_PD_MODULE_SPI_SLV                = 11,
    INFRA_PD_MODULE_DCXO                   = 12,
    INFRA_PD_MODULE_SAR_ADC                = 13,
    INFRA_PD_MODULE_I3C1                   = 14,
    INFRA_PD_MODULE_I3C1_DMA               = 15,
    INFRA_PD_MODULE_USB                    = 16,
    INFRA_PD_MODULE_SLEEP_MANAGER          = 17,
    INFRA_PD_MODULE_MAX                    = 18
} sleep_management_infra_pd_module_t;

#ifdef __cplusplus
}
#endif

#endif /* HAL_SLEEP_MANAGER_ENABLED */
#endif

