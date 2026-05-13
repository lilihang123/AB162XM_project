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

#ifdef HAL_QDEC_MODULE_ENABLED

#include <stdint.h>
#include <stdbool.h>
#include "air_chip.h"

#define Z_SUM_THR_MAX 0x1ff
#define Z_CNT_THR_MAX 0xff

#define SAMPLE_PERIOD_MAX 0x1ff
#define LED_PERIOD_MAX 0xf
#define DBC_COUNT_MAX 0x1f

typedef enum
{
  HAL_QDEC_LED_ACTIVE_MDOE = 0x00, /**< active mode  */
  HAL_QDEC_LED_IDLE_MDOE = 0x01 /**<  idle  mode   */
} hal_qdec_mode_status_t;

typedef enum
{
  HAL_QDEC_LED_LOW_ACTIVE = 0x00, /**< led low active   */
  HAL_QDEC_LED_HIGH_ACTIVE = 0x01 /**< led high active     */
} hal_qdec_led_active_value_setting_t;

typedef enum
{
  HAL_QDEC_DIV_OF_Z_COUNT_1_2 = 0x00, /**< set z count =z_sum/2    */
  HAL_QDEC_DIV_OF_Z_COUNT_1_4 = 0x01 /**< set z count =z_sum/4   */
} hal_qdec_z_div_setting_t;

typedef enum
{
  HAL_QDEC_SELECT_GROUP_A = 0x00, /**< select group a reg setting for qdec  */
  HAL_QDEC_SELECT_GROUP_B = 0x01 /**< select group b reg setting for qdec  */
} hal_qdec_sel_group_setting_t;

typedef enum
{
  HAL_QDEC_LED_NO_EFFECT = 0x00, /**< led open  */
  HAL_QDEC_LED_FORCE_OFF = 0x01 /**< led always close  */
} hal_qdec_led_setting_t;

typedef enum
{
  HAL_QDEC_READ_DATA_BY_IRQ= 0x00, /**< for low RR:read data by irq  */
  HAL_QDEC_READ_DATA_BY_NEXT_CYCLE = 0x01 /**< for high RR:read data by next cycle  */
} hal_qdec_data_getting_type_t;

typedef enum
{
  HAL_QDEC_ZSUM_MODE= 0x00, /**< data report sum */
  HAL_QDEC_ZCNT_MODE = 0x01 /**< data report z cnt :(zsum/zdiv)  */
} hal_qdec_mode_t;

/** @brief This enum defines qdec status */
typedef enum
{
  HAL_QDEC_STATUS_ERROR = -2,      /**< A keypad function error. */
  HAL_QDEC_INVALID_PARAMETER = -1, /**< An invalid parameter. */
  HAL_QDEC_STATUS_OK = 0           /**< No error occurred during the function call. */
} hal_qdec_status_t;

typedef enum {
    QDEC_STATUS_UNINITIALIZED,
    QDEC_STATUS_INITIALIZED,
    QDEC_STATUS_RUNNING
} hal_qdec_hw_status_t;

typedef enum {
    QDEC_IRQ_DATA_READY=0x1,
    QDEC_IRQ_Z_CNT=0x2,
    QDEC_IRQ_Z_SUM=0x4
} hal_qdec_irq_type_t;

typedef enum {
   IRQ_DISABLE   = 0x0,                                         
   IRQ_ENABLE  = 0x1                                         
} hal_qdec_irq_status_t;

typedef struct
{
  uint16_t smp_period;
  uint8_t led_period;
  uint8_t dbc_count;
} hal_qdec_group_config_t;

typedef struct
{
  uint8_t pina_pin;
  uint8_t pinb_pin;
  uint8_t led_pin;
  hal_qdec_led_setting_t led_force_off;
  hal_qdec_led_active_value_setting_t led_active_output;
  uint16_t z_sum_thr;
  hal_qdec_group_config_t group_a_cfg;
  hal_qdec_group_config_t group_b_cfg;
} hal_qdec_config_t;

// typedef void (*hal_qdec_callback_t)(uint8_t direction, int16_t number);
typedef void (*hal_qdec_callback_t)(uint8_t irq_type);


hal_qdec_status_t hal_qdec_init(hal_qdec_config_t *qdec);
hal_qdec_status_t hal_qdec_deinit(void);

hal_qdec_status_t hal_qdec_enable(void);
hal_qdec_status_t hal_qdec_disable(void);

hal_qdec_status_t hal_qdec_enable_irq(hal_qdec_irq_type_t irq_type);
hal_qdec_status_t hal_qdec_disable_irq(hal_qdec_irq_type_t irq_type);

hal_qdec_status_t hal_qdec_register_callback(hal_qdec_callback_t callback);

hal_qdec_status_t hal_qdec_zcnt_mode_set(hal_qdec_z_div_setting_t z_div, uint16_t z_cnt_thr);
hal_qdec_status_t hal_qdec_data_getting_type_set(hal_qdec_data_getting_type_t qdec_data_getting_type);

hal_qdec_status_t hal_qdec_set_latch_clear(void);
hal_qdec_status_t hal_qdec_get_data(int16_t *data);

hal_qdec_status_t hal_qdec_enable_hw_sel(hal_qdec_sel_group_setting_t group);
hal_qdec_status_t hal_qdec_disable_hw_sel(void);

hal_qdec_status_t hal_qdec_sw_sel_group(hal_qdec_sel_group_setting_t group);

hal_qdec_status_t hal_qdec_select_to_idle_status(void);
hal_qdec_status_t hal_qdec_select_to_active_status(void);

hal_qdec_status_t hal_qdec_latch_status_is_busy(bool *hw_latch_status);
hal_qdec_status_t hal_qdec_runnig_config_group_para(hal_qdec_sel_group_setting_t group_id, hal_qdec_group_config_t group_config);
hal_qdec_status_t hal_qdec_get_config_group_para(hal_qdec_sel_group_setting_t group_id, hal_qdec_group_config_t *group_config);

hal_qdec_mode_status_t hal_qdec_get_mode_status();
hal_qdec_status_t hal_qdec_get_irq_status(hal_qdec_irq_type_t irq_type , hal_qdec_irq_status_t *irq_status);
hal_qdec_status_t hal_qdec_set_z_sum_threshold(uint16_t threshold);
hal_qdec_status_t hal_qdec_get_z_sum_threshold(uint16_t *threshold);
hal_qdec_status_t hal_qdec_get_hw_sel_cfg(hal_qdec_irq_status_t *hw_sel_status, hal_qdec_sel_group_setting_t *group);


#endif /* HAL_QDEC_MODULE_ENABLED */