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

#ifdef HAL_RAMBOZ_MODULE_ENABLED

#include <stdint.h>
#include "air_chip.h"
#include <stdbool.h>

#define FILTER_PERIOD_MAX 0xF
#define FAST_SAMPLE_PERIOD_MAX 0xFFF
#define SLOW_SAMPLE_PERIOD_MAX 0xFFF
#define FAST_ROLL_PERIOD_MAX 0xFFF

typedef enum
{
  HAL_RAMBOZ_DIRECTION_0 = 0x0,  /**< ramboz direction :01-->rambo_cnt+1  */
  HAL_RAMBOZ_DIRECTION_1 = 0x1   /**< ramboz direction :10-->rambo_cnt+1  */
} hal_ramboz_direction_t;

typedef enum
{
  HAL_RAMBOZ_MODE_8CNT = 0x0,  /**< 8 rambo_cnt ->1 z count */
  HAL_RAMBOZ_MODE_5CNT = 0x1   /**< 5 rambo_cnt ->1 z count */
} hal_ramboz_mode_t;

typedef enum
{
  HAL_RAMBOZ_FAST_SAMPLE = 0x0,  /**< 8 rambo_cnt ->1 z count */
  HAL_RAMBOZ_SLOW_SAMPLE = 0x1   /**< 5 rambo_cnt ->1 z count */
} hal_ramboz_sample_mode_t;

typedef enum
{
  HAL_RAMBOZ_READ_DATA_BY_IRQ= 0x0, /**< for low RR:read data by irq  */
  HAL_RAMBOZ_READ_DATA_BY_NEXT_CYCLE = 0x1 /**< for high RR:read data by next cycle */
} hal_ramboz_data_getting_type_t;

typedef struct
{
  hal_ramboz_direction_t direction;
  hal_ramboz_mode_t mode;
  uint8_t filter_period;
  uint16_t fast_sample_period;
  uint16_t slow_sample_period;
  uint16_t fast_roll_period;
} hal_ramboz_config_t;

typedef enum
{
  HAL_RAMBOZ_STATUS_ERROR = -2,      /**< A keypad function error. */
  HAL_RAMBOZ_INVALID_PARAMETER = -1, /**< An invalid parameter. */
  HAL_RAMBOZ_STATUS_OK = 0           /**< No error occurred during the function call. */
} hal_ramboz_status_t;

typedef enum {
    RAMBOZ_STATUS_UNINITIALIZED,
    RAMBOZ_STATUS_INITIALIZED,
    RAMBOZ_STATUS_RUNNING
} hal_ramboz_hw_status_t;

typedef enum
{
  HAL_RAMBOZ_IRQ_Z_CNT = 0,      
  HAL_RAMBOZ_IRQ_RAMBO_CNT = 1, 
  HAL_RAMBOZ_IRQ_DATA_READY = 2        
} hal_ramboz_irq_type_t;

typedef enum
{
  HAL_RAMBOZ_WAKEUP_EVENT_Z_CNT = 0,      /**< A keypad function error. */
  HAL_RAMBOZ_WAKEUP_EVENT_RAMBO_CNT = 1, /**< An invalid parameter. */
} hal_ramboz_wakeup_event_type_t;

// typedef void (*hal_ramboz_callback_t)(uint8_t direction, int16_t number);
typedef void (*hal_ramboz_callback_t)(uint8_t irq_type);

hal_ramboz_status_t hal_ramboz_init(hal_ramboz_config_t *ramboz_cfg);
hal_ramboz_status_t hal_ramboz_deinit(void);
hal_ramboz_status_t hal_ramboz_enable_irq(hal_ramboz_irq_type_t irq_type);
hal_ramboz_status_t hal_ramboz_disable_irq(hal_ramboz_irq_type_t irq_type);
hal_ramboz_status_t hal_ramboz_enable(void);
hal_ramboz_status_t hal_ramboz_disable(void);
hal_ramboz_status_t hal_ramboz_register_callback(hal_ramboz_callback_t callback);
hal_ramboz_status_t hal_ramboz_set_latch_clear();
hal_ramboz_status_t hal_ramboz_get_data(int16_t *data);
hal_ramboz_status_t hw_ramboz_data_getting_type_set(hal_ramboz_data_getting_type_t ramboz_data_getting_type);
hal_ramboz_status_t hw_ramboz_data_sample_mode_set(hal_ramboz_sample_mode_t ramboz_sample_mode);
hal_ramboz_status_t hal_ramboz_enable_wakeup_event(hal_ramboz_wakeup_event_type_t wakeup_event_type);
hal_ramboz_status_t hal_ramboz_disable_wakeup_event(hal_ramboz_wakeup_event_type_t wakeup_event_type);
#endif /* HAL_RAMBOZ_MODULE_ENABLED */