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

#ifndef _HAL_RTC_INTERNAL_H_
#define _HAL_RTC_INTERNAL_H_
#include "air_chip.h"

#ifdef  HAL_RTC_MODULE_ENABLED
#ifdef __cplusplus
extern "C" {
#endif
//#include "hal.h"
#include "hal_rtc.h"
#include "assert.h"

#define SW_RTC_HANDLE_MAGIC_NUMBER 0xAAAA0000         /* SW RTC magic handle  number */
#define SW_RTC_HANDLE_TO_INDEX(handle) (handle & 0xFFFF)  /* Get SW RTC index accord to handle */
#define HAL_SW_RTC_MAX_USERS 4
#define HAL_RISCV_RTC_TIME   HAL_RTC_TIMER_1
#define HAL_MCU_RTC_TIME   HAL_RTC_TIMER_2
#define RTC_CLOCK_32KHZ         (0x10)

typedef enum {
    RTC_DIVIDE_1  = 0,
    RTC_DIVIDE_2  = 1,
    RTC_DIVIDE_3  = 2,
    RTC_DIVIDE_4  = 3 ,
    RTC_DIVIDE_5  = 4,
    RTC_DIVIDE_6  = 5,
    RTC_DIVIDE_7  = 6,
    RTC_DIVIDE_8  = 7,
    RTC_DIVIDE_9  = 8,
    RTC_DIVIDE_10 = 9,
    RTC_DIVIDE_11 = 10,
    RTC_DIVIDE_12 = 11,
    RTC_DIVIDE_13 = 12,
    RTC_DIVIDE_16 = 13,
    RTC_DIVIDE_32 = 14,
    RTC_DIVIDE_64 = 15
} rtc_clock_divide_t;

typedef enum{
    SW_RTC_NOTE_STATUS_OF_FREE = 0, 
    SW_RTC_NOTE_STATUS_OF_ALLOC,
    SW_RTC_NOTE_STATUS_OF_RUNING,
}sw_rtc_note_status_t;

typedef enum{
    SW_RTC_NOT_USER = 0, 
    SW_RTC_WITH_USER,
}sw_rtc_user_type_t;

typedef struct {
    hal_rtc_time_callback_t callback;
    void *user_data;
} rtc_callback_context_t;


typedef struct {
    hal_rtc_running_status_t running_status;
    rtc_callback_context_t   callback_context;
    bool                     has_initilized;
} rtc_context_t;

typedef struct timeout_elements_t{
    int32_t user_id;
    uint32_t expire_count;
    uint8_t expire_overflow;
    sw_rtc_note_status_t   status;
    hal_rtc_time_callback_t callback;
    void *user_data;
}timeout_elements_t;

typedef struct {
    timeout_elements_t* timeout_elements;
    int* user_index;
    int8_t capacity;
    int8_t size;
}MinHeap;

typedef struct{
    uint8_t  current_overflow;
    uint8_t  timer_overflow;
    bool     creat_heap;
    bool     sw_start_first;
    uint32_t timer_count;
}sw_rtc_context_t;

MinHeap* createMinHeap(int capacity);
int getKey(MinHeap* heap);
void statusChangeHeap(MinHeap* heap,int id,sw_rtc_note_status_t status);
int statusGetHeap(MinHeap* heap,int id,sw_rtc_note_status_t *status);
void insert(MinHeap* heap, timeout_elements_t value);
void freeMinHeap(MinHeap* heap);
timeout_elements_t getMin(MinHeap* heap);
timeout_elements_t extractMin(MinHeap *heap);
void sw_rtc_callback(sw_rtc_user_type_t *sw_rtc_type);
void rtc_nvic_register(void);
hal_rtc_status_t sw_rtc_timer_start(uint32_t handle, uint64_t timeout_elements_time_ms, hal_rtc_time_callback_t callback, void *user_data);
hal_rtc_status_t sw_rtc_timer_stop(uint32_t handle);
hal_rtc_status_t sw_rtc_get_remaining_time(uint32_t handle, uint64_t *remain_time);
hal_rtc_status_t rtc_ms_change_time(hal_rtc_time_t *get_time,hal_rtc_time_t time,uint64_t count_ms);
hal_rtc_status_t rtc_get_time(hal_rtc_time_t *time);
uint32_t rtc_get_current(hal_rtc_timer_port_t port);
uint64_t rtc_time_diff(const hal_rtc_time_t *time);

#define RTC_DEBUG   0

#define RTC_SWITCH_XOSC_USE_GPT_TIMER

// Default EOSC32K, uncomment one of the AIR_SYS32K_CLOCK_SOURCE_XOSC or AIR_SYS32K_CLOCK_SOURCE_DCXO to select 32k source
// #define AIR_SYS32K_CLOCK_SOURCE_XOSC
// #define AIR_SYS32K_CLOCK_SOURCE_DCXO

#if !defined(AIR_SYS32K_CLOCK_SOURCE_XOSC) && !defined(AIR_SYS32K_CLOCK_SOURCE_DCXO)
/* if define RTC_HQA_ENABLE, 32k source is controlled by RTC_HQA_32K_SWITCH_PIN_0 and RTC_HQA_32K_SWITCH_PIN_1 */
// #define RTC_HQA_ENABLE

#ifdef RTC_HQA_ENABLE
/* (PIN_1 << 1)|PIN_0 -> b00:EOSC32K b01:XOSC32K b10:DCXO32K b11:EOSC32K */
#define RTC_HQA_32K_SWITCH_PIN_0 HAL_GPIO_19
#define RTC_HQA_32K_SWITCH_PIN_1 HAL_GPIO_20
#endif //RTC_HQA_ENABLE
#endif //!defined(AIR_SYS32K_CLOCK_SOURCE_XOSC) && !defined(AIR_SYS32K_CLOCK_SOURCE_DCXO)

#define RTC_FREQ_MESURE_WINDOW 99

/* RTC SYS32K use F32K Source (EOSC or XOSC or DCXO). default AO32K Source (XOSC or EOSC)
 * uncomment RTC_SYS32K_USE_F32K to use F32K source
 */
// #define RTC_SYS32K_USE_F32K


typedef struct {
    uint32_t   cali_eosc;
    uint32_t   freq_f32k;
    uint32_t   freq_eosc;
    uint32_t   freq_xosc;

    uint8_t    sel_clk;
    bool rtc_init_done;
} rtc_private_parameter_t;

typedef enum {
    HAL_RTC_OSC32K_EOSC_MODE = 0,
    HAL_RTC_OSC32K_DCXO_MODE = 1,
    HAL_RTC_OSC32K_XOSC_MODE = 2,
    HAL_RTC_OSC32K_F32K_MODE = 3,
} hal_rtc_osc32k_mode_t;

void rtc_access_retention_regs(uint32_t offset, uint8_t *buff, uint32_t size, uint8_t is_write);

static inline void rtc_set_retention_reg(uint32_t offset, uint8_t data)
{
    rtc_access_retention_regs(offset, &data, 1, 1);
}

static inline void rtc_get_retention_reg(uint32_t offset, uint8_t *data)
{
    rtc_access_retention_regs(offset, data, 1, 0);
}

static inline void rtc_get_retention_regs(uint32_t offset, uint8_t *buff, uint32_t size)
{
    rtc_access_retention_regs(offset, buff, size, 0);
}

static inline void rtc_set_retention_regs(uint32_t offset, const uint8_t *buff, uint32_t size)
{
    rtc_access_retention_regs(offset, (uint8_t *)buff, size, 1);
}

void rtc_init_32k(void);
void dump_rtc_registers(const char * label);
hal_rtc_status_t hal_rtc_switch_32k_source(hal_rtc_osc32k_mode_t mode);
uint32_t rtc_measure_32k_with_windows(uint32_t ref_clk, uint32_t winset);
uint32_t rtc_get_f32k_frequency(void);
uint32_t rtc_get_current_32k_source(void);
#ifdef __cplusplus
}
#endif

#endif /*End HAL_RTC_MODULE_ENABLED*/
#endif /*End _HAL_RTC_INTERNAL_H_*/
