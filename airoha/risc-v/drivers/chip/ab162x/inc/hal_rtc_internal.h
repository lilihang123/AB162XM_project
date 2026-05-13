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
#include "exception_handler.h"

#define SW_RTC_HANDLE_MAGIC_NUMBER 0xAAAA0000         /* SW RTC magic handle  number */
#define SW_RTC_HANDLE_TO_INDEX(handle) (handle & 0xFFFF)  /* Get SW RTC index accord to handle */
#define HAL_SW_RTC_MAX_USERS 5

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
    timeout_elements_t *timeout_elements;
    int *user_index;
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
hal_rtc_status_t rtc_get_time_change(hal_rtc_time_t *get_time,hal_rtc_time_t time,uint64_t count);
hal_rtc_status_t rtc_get_time(hal_rtc_time_t *time);
uint32_t hal_rtc_get_current(hal_rtc_timer_port_t port);
uint64_t rtc_time_diff(const hal_rtc_time_t *time);

#ifdef __cplusplus
}
#endif

#endif /*End HAL_RTC_MODULE_ENABLED*/
#endif /*End _HAL_RTC_INTERNAL_H_*/
