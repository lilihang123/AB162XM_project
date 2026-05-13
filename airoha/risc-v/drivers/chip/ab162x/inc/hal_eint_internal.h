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

#ifndef __HAL_EINT_INTERNAL_H__
#define __HAL_EINT_INTERNAL_H__

#ifdef HAL_EINT_MODULE_ENABLED
#include "hal_nvic.h"
#include "hal_eint.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct {
    void (*eint_callback)(void *user_data);
    void *user_data;
} eint_function_t;

typedef enum {
    EINT_MASK = 1,
    EINT_UNMASK = 2,
    EINT_INACTIVE = 3,
    EINT_ACTIVE = 4,
} eint_status_t;

typedef enum {
    EINT_NOT_INIT = 0,
    EINT_INIT = 1,
    EINT_DEINIT = 2,
} eint_driver_status_t;

typedef enum {
    EINT_DOMAIN_DISABLE = 0,
    EINT_DOMAIN_ENABLE  = 1
} eint_domain_status_t;

typedef enum {
    EINT_COUNTER_CLK_32k = 0,
    EINT_COUNTER_CLK_26M = 1
} eint_counter_clock_t;

typedef enum {
    EINT_COUNTER_NUMBER_0 = 0,
    EINT_COUNTER_NUMBER_1 = 1,
    EINT_COUNTER_NUMBER_2 = 2,
    EINT_COUNTER_NUMBER_3 = 3,
    EINT_COUNTER_NUMBER_4 = 4,
    EINT_COUNTER_NUMBER_5 = 5,
    EINT_COUNTER_NUMBER_6 = 6,
    EINT_COUNTER_NUMBER_7 = 7,
    EINT_COUNTER_NUMBER_8 = 8,
    EINT_COUNTER_NUMBER_9 = 9,
    EINT_COUNTER_NUMBER_MUX
} eint_counter_number_t;


#ifdef AIR_CPU_IN_SECURITY_MODE
#define EINT_IRQ_NUM                 EINT_SEC_IRQn
#else
#define EINT_IRQ_NUM                 EINT_IRQn
#endif

#define EINT_GROUP_MAX_NUMBER  (32)

#define EINT_CON_PRESCALER_32KHZ    (0x00000000)
#define EINT_CON_PRESCALER_16KHZ    (0x00000001)
#define EINT_CON_PRESCALER_8KHZ     (0x00000002)
#define EINT_CON_PRESCALER_4KHZ     (0x00000003)
#define EINT_CON_PRESCALER_2KHZ     (0x00000004)
#define EINT_CON_PRESCALER_1KHZ     (0x00000005)
#define EINT_CON_PRESCALER_512HZ    (0x00000006)
#define EINT_CON_PRESCALER_256HZ    (0x00000007)
#define EINT_CON_DBC_ENABLE         (0x01)
#define EINT_CON_DBC_DISABLE        (0x00)
#define EINT_CON_RSTD_BC_MASK       (0x01)

#define EINT_WAKE_EVENT_EN          (0xFFFFFFFF)
#define EINT_WAKE_EVENT_DIS         (0xFFFFFFFF)

#define EINT_TIME_MS_TO_COUNT(time_ms, unit)   (((time_ms*unit)+500)/1000)  //round off calculation

/********* varible extern *************/
extern EINT_REGISTER_T *EINT_REGISTER;
#define EINT_DBC_OUT_REG_VALUE(reg_num)   ((uint32_t)(EINT_REGISTER->EINT_DBC_OUT[reg_num])) 
extern eint_function_t eint_function_table[HAL_EINT_NUMBER_MAX];
extern bool eint_firq_enable[HAL_EINT_NUMBER_MAX];
extern uint8_t g_debounce[HAL_EINT_NUMBER_MAX];
/******** funtion extern **************/
// hal_eint_status_t eint_mask_wakeup_source(hal_eint_number_t eint_number);
// hal_eint_status_t eint_unmask_wakeup_source(hal_eint_number_t eint_number);
void eint_ack_wakeup_event(uint32_t eint_number);
void eint_ack_interrupt(uint32_t eint_number);
uint32_t eint_get_status(uint32_t index);
uint32_t eint_get_event(uint32_t index);
uint32_t eint_caculate_debounce_time(uint32_t ms);
hal_eint_status_t hal_eint_ext_sleep_set_debounce_time(hal_eint_number_t eint_number, uint32_t time_ms);
void hal_eint_isr(uint8_t index);
#ifdef HAL_EINT_FEATURE_MUX_MAPPING
hal_eint_status_t hal_eint_set_mux_mapping(hal_eint_number_t eint_number, hal_gpio_pin_t gpio_number);
hal_eint_status_t hal_eint_get_mux_mapping(hal_eint_number_t eint_number, hal_gpio_pin_t *gpio_number);
#endif

#ifndef HAL_EINT_FEATURE_TIMESTAMP_COUNT
#define HAL_EINT_FEATURE_TIMESTAMP_COUNT
#endif

#ifdef HAL_EINT_FEATURE_TIMESTAMP_COUNT
hal_eint_status_t hal_eint_counter_enable(void);
hal_eint_status_t hal_eint_counter_disable(void);
hal_eint_status_t hal_eint_set_counter_clock(eint_counter_clock_t counter_clock);
hal_eint_status_t hal_eint_set_counter_number(hal_eint_number_t eint_number, eint_counter_number_t counter_number);
uint32_t hal_eint_get_counter_value(eint_counter_number_t counter_number);
uint32_t hal_eint_get_free_counter_value(void);

#endif

void hal_eint_enable(uint32_t eint_number);
void hal_eint_disable(uint32_t eint_number);
void hal_eint_debonnce_config(uint32_t eint_number,uint8_t debounce);

void hal_eint_get_debounce_out_value_by_mask(uint32_t *value1,uint32_t *value2);
#ifdef __cplusplus
}
#endif

#endif /* HAL_EINT_MODULE_ENABLED */

#endif /* __HAL_EINT_INTERNAL_H__ */

