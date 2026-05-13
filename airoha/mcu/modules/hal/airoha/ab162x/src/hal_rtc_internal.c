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
#include <stdlib.h>
#include "hal_rtc.h"
#include "hal_gpio.h"
#include "hal_gpio_internal.h"
#include "hal_rtc_internal.h"
#include "hal_clock_internal.h"
#include "hal_gpt.h"
#include "hal_nvic_internal.h"
#include <zephyr/kernel.h>
#ifdef HAL_RTC_MODULE_ENABLED
extern RTC_TIMER_REGISTER_T *rtc_base;
extern rtc_context_t g_rtc_context[HAL_RTC_TIMER_MAX];
extern sw_rtc_context_t sw_rtc_context;
extern MinHeap* heap;
extern hal_rtc_time_t init_time;
uint32_t g_sw_rtc_running_note = (HAL_SW_RTC_MAX_USERS+1);
static const int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
uint32_t sw_rtc_overflow=0x55550000;
extern sw_rtc_user_type_t sw_rtc;
#define MILLISECONDS_PER_SECOND 1000
#define SECONDS_PER_MINUTE 60
#define MINUTES_PER_HOUR   60
#define HOURS_PER_DAY      24
#define WEEK_PER_DAY      24
#define RTC_IRQ_NUM 21

MinHeap* createMinHeap(int capacity){
    MinHeap* heap = (MinHeap*)k_malloc(sizeof(MinHeap));
    if(!heap) {
        return NULL;
    }
    heap->timeout_elements = (timeout_elements_t*)k_malloc(capacity*sizeof(timeout_elements_t));
    if(!heap->timeout_elements)
    {
        k_free(heap);
        heap = NULL;
        return NULL;
    }
    heap->user_index = (int*)k_malloc(capacity*sizeof(int));
    if(!heap->user_index){
        k_free(heap->timeout_elements);
        k_free(heap);
        heap = NULL;
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
    for(int i = 0;i<capacity;i++){
        heap->timeout_elements[i].user_id = i;
        heap->timeout_elements[i].expire_count = 0xFFFFFFFF;
        heap->timeout_elements[i].expire_overflow=0xFF;
        heap->timeout_elements[i].callback = NULL;
        heap->timeout_elements[i].user_data = NULL;
        heap->timeout_elements[i].status = SW_RTC_NOTE_STATUS_OF_FREE;
        heap->user_index[i] = i;
    }
    return heap;
}

void freeMinHeap(MinHeap* heap){
    if(heap){
        k_free(heap->user_index);
        k_free(heap->timeout_elements);
        k_free(heap);
        heap = NULL;
    }
}

int getKey(MinHeap* heap){
    if(heap == NULL){
        return -1;
    }
    for(int i =0;i<heap->capacity;i++){
        if(heap->timeout_elements[i].status == SW_RTC_NOTE_STATUS_OF_FREE){
            heap->timeout_elements[i].status = SW_RTC_NOTE_STATUS_OF_ALLOC;
            heap->user_index[heap->timeout_elements[i].user_id] = i;
            heap->size++;
            return heap->timeout_elements[i].user_id;
        }
    }
    return -1;
}

void swap(timeout_elements_t *x, timeout_elements_t *y){
    timeout_elements_t temp = *x;
    *x = *y;
    *y = temp;
    int temp_id = heap->user_index[x->user_id];
    heap->user_index[x->user_id] = heap->user_index[y->user_id];
    heap->user_index[y->user_id] = temp_id;
}

int compare_special(const uint8_t x_expire_overflow,const uint32_t x_expire_count,const uint8_t y_expire_overflow,const uint32_t y_expire_count){
    if(x_expire_overflow != y_expire_overflow){
        return x_expire_overflow < y_expire_overflow ? -1:1;
    }else{
        return x_expire_count < y_expire_count ? -1:1;
    }
}


int compare(const timeout_elements_t *x, const timeout_elements_t *y){
    if(x->status != y->status){
        if(x->status == SW_RTC_NOTE_STATUS_OF_RUNING) return -1;
        else if(y->status == SW_RTC_NOTE_STATUS_OF_RUNING) return 1;
        else{
            return compare_special(x->expire_overflow,x->expire_count,y->expire_overflow,y->expire_count);
        }
    }
    else{
        return compare_special(x->expire_overflow,x->expire_count,y->expire_overflow,y->expire_count);
    }
}
void heapup(MinHeap* heap, uint8_t i){
    int Parent;
    while(i > 0){
        Parent = (i -1)/2;
        if(compare(&heap->timeout_elements[i],&heap->timeout_elements[Parent]) < 0){
            swap(&heap->timeout_elements[i],&heap->timeout_elements[Parent]);
            i = Parent;
        }else{
            break;
        }
    }
}

void heapdown(MinHeap* heap, uint8_t i){
    int smallest = i;
    int leftChild =2*i+1;
    int rightChild =2*i+2;
    if(leftChild < heap->size && compare(&heap->timeout_elements[leftChild],&heap->timeout_elements[smallest]) < 0){
        smallest = leftChild;
    }
    if(rightChild < heap->size && compare(&heap->timeout_elements[rightChild],&heap->timeout_elements[smallest]) < 0){
        smallest = rightChild;
    }
    if(smallest != i){
        swap(&heap->timeout_elements[i],&heap->timeout_elements[smallest]);
        heapdown(heap,smallest);
    }
}
void statusChangeHeap(MinHeap* heap,int id,sw_rtc_note_status_t status){
    if(heap == NULL){
        return;
    }
    int index = heap->user_index[id];
    sw_rtc_note_status_t old_status ;
    old_status = heap->timeout_elements[index].status;
    if(old_status == status){
        return;
    }
    if(old_status == SW_RTC_NOTE_STATUS_OF_FREE){
        return;
    }
    heap->timeout_elements[index].status=status;
    if(status == SW_RTC_NOTE_STATUS_OF_RUNING){
        heapup(heap,index);
    }else if(old_status == SW_RTC_NOTE_STATUS_OF_RUNING){
        heapdown(heap,index);
    }else if(status == SW_RTC_NOTE_STATUS_OF_FREE){
        heap->size--;
    }
}

int statusGetHeap(MinHeap* heap,int id,sw_rtc_note_status_t *status){
    if(heap == NULL){
        return -1;
    }
    int index = heap->user_index[id];
    *status= heap->timeout_elements[index].status;
    return 0;

}

void insert(MinHeap* heap, timeout_elements_t value){
    if(heap == NULL){
        return;
    }
    if(heap->size ==  heap->capacity){
        printk("heap is full\n");
        return;
    }
    int index = heap->user_index[value.user_id];
    heap->timeout_elements[index] = value;
    heapdown(heap,index);
    heapup(heap,index);
}

timeout_elements_t getMin(MinHeap* heap){
    timeout_elements_t min = {.user_id = -1};
    if(heap == NULL){
        return min;
    }
    if(heap->size <= 0){
        printk("heap is empty");
        return min;
    }
    if(heap->timeout_elements[0].status == SW_RTC_NOTE_STATUS_OF_RUNING){
        return heap->timeout_elements[0];
    }else{
        // printk("not running \r\n");
        return min;
    }
}
timeout_elements_t extractMin(MinHeap *heap){
    timeout_elements_t timeout = getMin(heap);
    if(timeout.user_id == -1){
        return timeout;
    }
    int index = heap->user_index[timeout.user_id];
    timeout.status = SW_RTC_NOTE_STATUS_OF_FREE;
    // heap->timeout_elements[index] = heap->timeout_elements[heap->size - 1];
    heap->size--;
    heapdown(heap,index);
    // heapup(heap,index);
    return timeout;
}

int deleteKey(MinHeap* heap,int32_t key){
    if(heap == NULL){
        return -1;
    }
    int index = heap->user_index[key];
    heap->timeout_elements[index].status = SW_RTC_NOTE_STATUS_OF_FREE;
    heap->size--;
    heapdown(heap,index);
    // heapup(heap,index);
    return 0;
}

void rtc_callback(hal_nvic_irq_t irq_number)
{
    for(int i=0;i<2;i++){
        if((rtc_base->rtc_config[i].rtc_irq_sta.field.IRQSTA0) && (rtc_base->rtc_config[i].rtc_irq_en.field.IRQEN0)){
            if(i != HAL_RISCV_RTC_TIME){
                rtc_base->rtc_config[i].rtc_irq_ack.field.IRQACK0 = 1;
                if (g_rtc_context[i].callback_context.callback != NULL) {
                    g_rtc_context[i].callback_context.callback(g_rtc_context[i].callback_context.user_data);
                }
            }
        }
    }
    if((rtc_base->rtc_ao_config.rtc_irq_sta.field.IRQSTA0) && (rtc_base->rtc_ao_config.rtc_irq_en.field.IRQEN0)){
        if(HAL_RTC_TIMER_2 != HAL_RISCV_RTC_TIME){
            rtc_base->rtc_ao_config.rtc_irq_ack.field.IRQACK0 = 1;
            if (g_rtc_context[2].callback_context.callback != NULL) {
                g_rtc_context[2].callback_context.callback(g_rtc_context[2].callback_context.user_data);
            }
        }
    }
}
void rtc_nvic_register(void){
    static bool is_init = false;
    if (is_init == false) {
        hal_nvic_disable_irq(RTC_IRQ_NUM);
        hal_nvic_register_isr_handler(RTC_IRQ_NUM, rtc_callback);
        hal_nvic_enable_irq(RTC_IRQ_NUM);
        is_init = true;
    }
}
void clear_rtc_and_restart_hw_rtc(uint32_t next_expired_count, hal_rtc_timer_port_t port)
{
    uint32_t mask;
    if(port == HAL_MCU_RTC_TIME){
        hal_nvic_save_and_set_interrupt_mask(&mask);
        if(HAL_MCU_RTC_TIME == 2){
            rtc_base->rtc_ao_config.rtc_compare.word = next_expired_count;       /* set overflow IRQ */
            while (!(rtc_base->rtc_ao_t_wcompsta.word & 1 ));
        }else{
            rtc_base->rtc_config[HAL_MCU_RTC_TIME].rtc_compare.word = next_expired_count;       /* set overflow IRQ */
            while (!(rtc_base->rtc_t_wcompsta.word & (1 << HAL_MCU_RTC_TIME)));
        }
        hal_nvic_restore_interrupt_mask(mask);
    }
    return;
    // rtc_base->rtc_config[port].rtc_con.field.SW_CG0 = 0;  /* enable clock */
    // rtc_base->rtc_config[port].rtc_irq_en.field.IRQEN0 = 0;  /* enable interrupt */
    // rtc_base->rtc_config[port].rtc_con.field.EN0 = 0;  /* disable */
    // rtc_base->rtc_config[port].rtc_clk.field.CLK0 = RTC_DIVIDE_32 | RTC_CLOCK_32KHZ; /* clk*/

    // rtc_base->rtc_config[port].rtc_irq_ack.word = 1; /* clear interrupt status */
    // rtc_base->rtc_config[port].rtc_clr.word = 1; /* clear counter value */
    // while (!(rtc_base->rtc_t_clrsta.word & (1 << port)));
    // rtc_base->rtc_config[port].rtc_con.field.MODE0 = 2; //FREERUN_I MODE
    // rtc_base->rtc_config[port].rtc_con.field.EN0 = 1;  /* enable */
    // rtc_base->rtc_t_irqmask0.word    &= ~(1 << port); //CM4 IRQ enable
    // rtc_base->rtc_t_wakeupmask0.word &= ~(1 << port); //CM4 wakeup enable
    // rtc_base->rtc_config[port].rtc_irq_en.field.IRQEN0 = 1;  /* enable interrupt */

}
static uint32_t rtc_get_32k_frequency(void){
    uint32_t tick_per_second = 32768;
    tick_per_second = rtc_get_f32k_frequency();
    return tick_per_second;
}


uint64_t rtc_convert_ms_to_32k_count(uint64_t ms)
{
    uint32_t tick_per_second = rtc_get_32k_frequency();
    return (uint64_t)(ms * (tick_per_second / 1000) + (ms * (tick_per_second % 1000))/1000);
}

// uint64_t rtc_convert_count_to_32k_ms(uint64_t count)
// {
//     uint32_t tick_per_second = 32768;
//     uint32_t freq_meter_data = hal_clock_freq_meter_data(RTC_CK, xo_ck, 99);
//     tick_per_second = (((uint64_t)DCXO_HZ) * (99 + 1)) / freq_meter_data;
//     uint64_t ms =  (uint64_t)(count/tick_per_second * 1000 + ((count % tick_per_second * 1000+rem)/tick_per_second));
//     rem = (count % tick_per_second * 1000+rem) % tick_per_second;
//     return ms;
// }

uint64_t rem;
uint64_t rtc_convert_count_to_32k_ms(uint64_t count,uint32_t freq)
{
    uint64_t ms =  (uint64_t)(count/freq * 1000 + ((count % freq * 1000+rem)/freq));
    rem = (count % freq * 1000+rem) % freq;
    return ms;
}

void sw_rtc_callback(sw_rtc_user_type_t *sw_rtc_type)
{
    uint32_t mask, current_count = 0;
    timeout_elements_t next_timeout;
    hal_rtc_time_callback_t temp_callback;
    void *temp_user_data;
    g_sw_rtc_running_note= (HAL_SW_RTC_MAX_USERS+1);    /*assigned a global variable to check if any irq are coming in after running callback  */
    if(*sw_rtc_type == SW_RTC_NOT_USER){                             /*not user start rtc timer  */
        sw_rtc_context.current_overflow++;
        hal_gpt_delay_ms(1);
    }
    else{
        uint32_t expired_flag;
        Reget_current_count:
        expired_flag = false;
        current_count = rtc_get_current(HAL_MCU_RTC_TIME);
        next_timeout = getMin(heap);
        if(next_timeout.user_id != -1){
            hal_nvic_save_and_set_interrupt_mask(&mask);//re-start again
            if((next_timeout.status == SW_RTC_NOTE_STATUS_OF_RUNING) && (compare_special(sw_rtc_context.current_overflow,current_count,next_timeout.expire_overflow,next_timeout.expire_count) ==1)){
                    temp_callback = next_timeout.callback;
                    temp_user_data = next_timeout.user_data;
                    expired_flag = true;
                    if((temp_user_data != NULL) &&(*(uint32_t *)temp_user_data == 0x55550000)){
                        sw_rtc_context.current_overflow++;
                        next_timeout.expire_overflow++;
                        hal_gpt_delay_ms(1);                         //delay 1ms,avoid sencond IRQ;
                        hal_nvic_restore_interrupt_mask(mask);
                    }else{
                        statusChangeHeap(heap,next_timeout.user_id,SW_RTC_NOTE_STATUS_OF_ALLOC);
                        hal_nvic_restore_interrupt_mask(mask);
                        if(temp_callback != NULL)temp_callback(temp_user_data);
                    }
            }else{
                hal_nvic_restore_interrupt_mask(mask);
            }
            if (expired_flag == true) {
                goto Reget_current_count;
            }
            hal_nvic_save_and_set_interrupt_mask(&mask);
            if(g_sw_rtc_running_note == (HAL_SW_RTC_MAX_USERS+1)){
                next_timeout = getMin(heap);
                if(next_timeout.user_id != -1){
                    clear_rtc_and_restart_hw_rtc(next_timeout.expire_count, HAL_MCU_RTC_TIME);
                    g_sw_rtc_running_note = next_timeout.user_id; // update the running index
                }
            }
            hal_nvic_restore_interrupt_mask(mask);
        }
    }
}
hal_rtc_status_t sw_rtc_timer_start(uint32_t handle, uint64_t timeout_elements_time_ms, hal_rtc_time_callback_t callback, void *user_data)
{
    uint32_t index = SW_RTC_HANDLE_TO_INDEX(handle);
    uint32_t current_count = 0, expire_count, expire_overflow,mask;
    uint64_t absolute_count;
    sw_rtc_note_status_t status;
    timeout_elements_t timeout,next_timeout;
    if (callback == NULL) {
        return HAL_RTC_STATUS_INVALID_PARAM;
    }
    if ((handle & SW_RTC_HANDLE_MAGIC_NUMBER) != SW_RTC_HANDLE_MAGIC_NUMBER) {
        return HAL_RTC_STATUS_INVALID_PARAM;
    }
    if(sw_rtc_context.sw_start_first == false){
        int id = getKey(heap);                                                                       //add  overflow IRQ;
        if(id == -1){
            assert(0);
        }
        timeout_elements_t overflow_timeout;
        sw_rtc = SW_RTC_WITH_USER;
        g_rtc_context[HAL_MCU_RTC_TIME].callback_context.user_data = &sw_rtc;
        overflow_timeout.user_id = id;
        overflow_timeout.expire_count = 0xFFFFFFFF;
        overflow_timeout.expire_overflow = sw_rtc_context.current_overflow;
        overflow_timeout.status = SW_RTC_NOTE_STATUS_OF_RUNING;
        overflow_timeout.callback = NULL;
        overflow_timeout.user_data = (void*)&sw_rtc_overflow;
        insert(heap,overflow_timeout);
        sw_rtc_context.sw_start_first = true;
    }
    current_count = rtc_get_current(HAL_MCU_RTC_TIME);
    absolute_count = rtc_convert_ms_to_32k_count(timeout_elements_time_ms)+current_count;
    expire_overflow = (uint8_t)((uint8_t)(absolute_count>>32 & 0xFF) + sw_rtc_context.current_overflow);
    expire_count = (uint32_t)(absolute_count);
    /* step1: check this notes_rtc_timer status whether is SW_RTC_NOTE_STATUS_OF_ALLOC*/
    hal_nvic_save_and_set_interrupt_mask(&mask);
    statusGetHeap(heap,index,&status);
    if(status != SW_RTC_NOTE_STATUS_OF_ALLOC){
        hal_nvic_restore_interrupt_mask(mask);
        return HAL_RTC_STATUS_ERROR;
    }
    /*step2: push the note to global variables  */
    timeout.user_id = index;
    timeout.expire_count = expire_count;
    timeout.expire_overflow = expire_overflow;
    timeout.status = SW_RTC_NOTE_STATUS_OF_RUNING;
    timeout.callback = callback;
    timeout.user_data = user_data;
    /* step3: find the next expire timer  and re-start the rtc*/
    insert(heap,timeout);
    next_timeout = getMin(heap);
    if(next_timeout.user_id == -1){
        assert(0);
    }
    g_sw_rtc_running_note = next_timeout.user_id;
    clear_rtc_and_restart_hw_rtc(next_timeout.expire_count, HAL_MCU_RTC_TIME); // restart the rtc.
    hal_nvic_restore_interrupt_mask(mask);
    return HAL_RTC_STATUS_OK;
}

hal_rtc_status_t sw_rtc_timer_stop(uint32_t handle)
{
    uint32_t mask;
    // uint32_t current_count = 0;
    timeout_elements_t next_timeout;
    sw_rtc_note_status_t status;
    uint32_t index = SW_RTC_HANDLE_TO_INDEX(handle);
    // current_count = rtc_get_current(HAL_MCU_RTC_TIME);
    if ((handle & SW_RTC_HANDLE_MAGIC_NUMBER) != SW_RTC_HANDLE_MAGIC_NUMBER) {
        return HAL_RTC_STATUS_INVALID_PARAM;
    }
    hal_nvic_save_and_set_interrupt_mask(&mask);
    statusGetHeap(heap,index,&status);
    if(status != SW_RTC_NOTE_STATUS_OF_RUNING){
        hal_nvic_restore_interrupt_mask(mask);
        return HAL_RTC_STATUS_ERROR;
    }
    // int user_index = heap->user_index[index];
    statusChangeHeap(heap,index,SW_RTC_NOTE_STATUS_OF_ALLOC);
    next_timeout = getMin(heap);
    if(next_timeout.user_id == -1){
        g_sw_rtc_running_note = (HAL_SW_RTC_MAX_USERS+1);
        hal_nvic_restore_interrupt_mask(mask);
        return HAL_RTC_STATUS_OK;
    }
    if(g_sw_rtc_running_note != next_timeout.user_id){
        clear_rtc_and_restart_hw_rtc(next_timeout.expire_count, HAL_MCU_RTC_TIME); // restart the rtc.
        g_sw_rtc_running_note = next_timeout.user_id;
    }
    hal_nvic_restore_interrupt_mask(mask);
    return HAL_RTC_STATUS_OK;

}

hal_rtc_status_t sw_rtc_get_remaining_time(uint32_t handle, uint64_t *remain_time)
{
    uint32_t index = SW_RTC_HANDLE_TO_INDEX(handle);
    uint32_t mask;
    uint32_t current_count = 0,expire_count =0;
    uint64_t expire_overflow =0;
    uint64_t remain_count =0;
    uint64_t current_overflow_cal = sw_rtc_context.current_overflow;
    sw_rtc_note_status_t status;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    statusGetHeap(heap,index,&status);
    if(status != SW_RTC_NOTE_STATUS_OF_RUNING){
        hal_nvic_restore_interrupt_mask(mask);
        return HAL_RTC_STATUS_ERROR;
    }
    uint32_t tick_per_second = rtc_get_32k_frequency();
    int user_index = heap->user_index[index];
    current_count = rtc_get_current(HAL_MCU_RTC_TIME);
    expire_count = heap->timeout_elements[user_index].expire_count;
    expire_overflow = heap->timeout_elements[user_index].expire_overflow;
    remain_count = (expire_overflow<<32 | expire_count) - (current_overflow_cal << 32 | current_count);
    *remain_time  = rtc_convert_count_to_32k_ms(remain_count,tick_per_second);
    hal_nvic_restore_interrupt_mask(mask);
    return HAL_RTC_STATUS_OK;
}


static int isLeapYear(int rtc_year) {
    return (rtc_year % 4 == 0 && rtc_year % 100 != 0) || (rtc_year % 400 == 0);
}

static int getDaysInMonth(int rtc_year, int rtc_mon) {
    if (rtc_mon == 2 && isLeapYear(rtc_year)) {
        return 29;
    } else {
        return daysInMonth[rtc_mon- 1];
    }
}

static int daysInYear(int year) {
    return isLeapYear(year) ? 366:365;
}

uint32_t rtc_get_current(hal_rtc_timer_port_t port){
    if(port != 2){
        return rtc_base->rtc_config[port].rtc_count.word;
    }else{
        return rtc_base->rtc_ao_config.rtc_count.word;
    }
}

hal_rtc_status_t rtc_ms_change_time(hal_rtc_time_t *get_time,hal_rtc_time_t time,uint64_t count_ms){
    get_time->rtc_milli_sec =  (uint16_t)((count_ms+time.rtc_milli_sec) % MILLISECONDS_PER_SECOND);
    uint64_t secondsToAdd = (count_ms+time.rtc_milli_sec) / MILLISECONDS_PER_SECOND;
    get_time->rtc_sec = (uint8_t)((time.rtc_sec+secondsToAdd) % SECONDS_PER_MINUTE);
    uint64_t minToAdd = (time.rtc_sec+secondsToAdd) / SECONDS_PER_MINUTE;
    get_time->rtc_min = (uint8_t)((time.rtc_min+minToAdd) % MINUTES_PER_HOUR);
    uint64_t hourToAdd = (time.rtc_min+minToAdd) / MINUTES_PER_HOUR;
    get_time->rtc_hour = (uint8_t)((time.rtc_hour+hourToAdd) % HOURS_PER_DAY);
    uint64_t dayToAdd = (time.rtc_hour+hourToAdd) / HOURS_PER_DAY;
    dayToAdd += time.rtc_day;
    get_time->rtc_mon = time.rtc_mon;
    get_time->rtc_year = time.rtc_year;
    while(dayToAdd > getDaysInMonth(get_time->rtc_year, get_time->rtc_mon)) {
        dayToAdd -= getDaysInMonth(get_time->rtc_year, get_time->rtc_mon);
        get_time->rtc_mon++;
        if(get_time->rtc_mon > 12) {
            get_time->rtc_year++;
            get_time->rtc_mon = 1;
        }
    }
    get_time->rtc_day = (uint8_t)dayToAdd;
    get_time->rtc_week = get_time->rtc_day % 7;
    return HAL_RTC_STATUS_OK;
}


// hal_rtc_status_t rtc_get_time_change(hal_rtc_time_t *get_time,hal_rtc_time_t time,uint64_t count,uint32_t freq){


//     get_time->rtc_milli_sec =  (uint16_t)((count_ms+time.rtc_milli_sec) % MILLISECONDS_PER_SECOND);
//     uint64_t secondsToAdd = (count_ms+time.rtc_milli_sec) / MILLISECONDS_PER_SECOND; 
//     get_time->rtc_sec = (uint8_t)((time.rtc_sec+secondsToAdd) % SECONDS_PER_MINUTE);
//     uint64_t minToAdd = (time.rtc_sec+secondsToAdd) / SECONDS_PER_MINUTE; 
//     get_time->rtc_min = (uint8_t)((time.rtc_min+minToAdd) % MINUTES_PER_HOUR);
//     uint64_t hourToAdd = (time.rtc_min+minToAdd) / MINUTES_PER_HOUR; 
//     get_time->rtc_hour = (uint8_t)((time.rtc_hour+hourToAdd) % HOURS_PER_DAY);
//     uint64_t dayToAdd = (time.rtc_hour+hourToAdd) / HOURS_PER_DAY; 
//     dayToAdd += time.rtc_day;
//     get_time->rtc_mon = time.rtc_mon;
//     get_time->rtc_year = time.rtc_year;
//     while(dayToAdd > getDaysInMonth(get_time->rtc_year, get_time->rtc_mon)) {
//         dayToAdd -= getDaysInMonth(get_time->rtc_year, get_time->rtc_mon);
//         get_time->rtc_mon++;
//         if(get_time->rtc_mon > 12) {
//             get_time->rtc_year++;
//             get_time->rtc_mon = 1;
//         }
//     }
//     get_time->rtc_day = (uint8_t)dayToAdd;
//     get_time->rtc_week = get_time->rtc_day % 7;
//     hal_rtc_set_time(get_time);
//     // printk("get:%d %d %d \r\n",get_time->rtc_milli_sec,(uint32_t)count_ms,time.rtc_milli_sec);
//     return HAL_RTC_STATUS_OK;
// }

hal_rtc_status_t rtc_get_time(hal_rtc_time_t *time) {
    if (time == NULL) {
        return HAL_RTC_STATUS_ERROR;
    }
    uint64_t count = 0;
    uint32_t tick_per_second = rtc_get_32k_frequency();
    uint32_t current_count = rtc_get_current(HAL_MCU_RTC_TIME);
    if(current_count >= sw_rtc_context.timer_count){
        uint64_t current_overflow_cal = (sw_rtc_context.current_overflow-sw_rtc_context.timer_overflow);
        count = (current_overflow_cal << 32) |(current_count-sw_rtc_context.timer_count);
    }else{
        if(sw_rtc_context.current_overflow < (sw_rtc_context.timer_overflow +1)){
            return HAL_RTC_STATUS_ERROR;
        }
        uint64_t current_overflow_cal = (sw_rtc_context.current_overflow-sw_rtc_context.timer_overflow -1);
        count = (current_overflow_cal << 32) |(0xFFFFFFFF- current_count+sw_rtc_context.timer_count);
    }
    uint64_t count_ms = rtc_convert_count_to_32k_ms(count,tick_per_second);               //count convert ms
    rtc_ms_change_time(time,init_time,count_ms);
    hal_rtc_set_time(time);
    return HAL_RTC_STATUS_OK;
}

uint64_t rtc_time_diff(const hal_rtc_time_t *time){
    uint64_t total_ms = 0;
    for(int y = 1970;y<time->rtc_year;y++){
        total_ms += daysInYear(y)*HOURS_PER_DAY*MINUTES_PER_HOUR*SECONDS_PER_MINUTE*MILLISECONDS_PER_SECOND;
    }
    for(int m = 0;m<time->rtc_mon;m++){
        total_ms += daysInMonth[m]*HOURS_PER_DAY*MINUTES_PER_HOUR*SECONDS_PER_MINUTE*MILLISECONDS_PER_SECOND;
        if(m == 1 && isLeapYear(time->rtc_year)){
            total_ms += HOURS_PER_DAY*MINUTES_PER_HOUR*SECONDS_PER_MINUTE*MILLISECONDS_PER_SECOND;   //29
        }
    }
    total_ms += (time->rtc_day-1)*HOURS_PER_DAY*MINUTES_PER_HOUR*SECONDS_PER_MINUTE*MILLISECONDS_PER_SECOND;
    total_ms += (time->rtc_hour)*MINUTES_PER_HOUR*SECONDS_PER_MINUTE*MILLISECONDS_PER_SECOND;
    total_ms += (time->rtc_min)*SECONDS_PER_MINUTE*MILLISECONDS_PER_SECOND;
    total_ms += (time->rtc_sec)*MILLISECONDS_PER_SECOND;
    total_ms += (time->rtc_milli_sec);
    return total_ms;
}

/************************************************ RTC 32K ************************************************************/
#include <stdio.h>
#include <stdbool.h> // for bool
#include "hal_gpt.h" // for HAL GPT functions
#include "hal_clock_internal.h"
#include "hal_log.h"


#if 0
#define log_rtc_info(fmt, cnt, ...)     log_hal_msgid_info("[hal][rtc] " fmt, cnt, ##__VA_ARGS__)
#define log_rtc_warning(fmt, cnt, ...)  log_hal_msgid_warning("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#define log_rtc_error(fmt, cnt, ...)    log_hal_msgid_error("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#else
#define log_rtc_info(fmt, cnt, ...)     printk("[RTC] "fmt, ##__VA_ARGS__)
#define log_rtc_warning(fmt, cnt, ...)  printk("[RTC] "fmt, ##__VA_ARGS__)
#define log_rtc_error(fmt, cnt, ...)    printk("[RTC] "fmt, ##__VA_ARGS__)
#endif

#define HAL_RTC_PRIVATE_DATA_ADDR   (&g_rtc_private_data)

static  rtc_private_parameter_t g_rtc_private_data = {0};

void rtc_32k_eosc_control(bool eosc_on);
void rtc_32k_xosc_control(bool xosc_on);
void rtc_32k_dcxo_control(bool dcxo_on);
int is_eosc_on();
int is_xosc_on();
int is_dcxo_on();

#define RTC_32K_BASE 0x42105000
static RTC_32K_REGISTER_T *rtc_32k_register = (RTC_32K_REGISTER_T*)RTC_32K_BASE;
#undef printks
#ifndef printks
#define printks printk
#endif

void dump_rtc_registers(const char * label) {
    static uint32_t index = 0;
    if (label) {
        printks("[RTC] =========================%d Dumping RTC Registers: [%s]=======================\n", index, label);
    } else {
        printks("[RTC] =========================%d Dumping RTC Registers=========================\n", index);
    }
    index++;
    uint32_t value;
#if RTC_DEBUG
    #define PRINT_FIELD(reg, field, mask, shift) \
        log_rtc_info("  " #field ": 0x%x\n", 1, ((reg) >> (shift)) & ((1 << (mask)) - 1))
#else
    #define PRINT_FIELD(reg, field, mask, shift)
#endif
    value = (uint32_t)rtc_32k_register->RTC_OSC32CON0;
    log_rtc_info("RTC_OSC32CON0 : 0x%08X\n", 1, value);
    PRINT_FIELD(value, RG_EOSC1_CHOP_EN, 1, 0);
    PRINT_FIELD(value, RG_EOSC1_CALI, 5, 1);
    PRINT_FIELD(value, RG_EOSC1_FST_EN, 2, 6);
    PRINT_FIELD(value, RG_EOSC1_LPD_BIAS_RDY, 1, 8);
    PRINT_FIELD(value, RG_EOSC1_LPD_EN, 1, 9);
    PRINT_FIELD(value, RG_EOSC1_LPD_RST, 1, 10);
    PRINT_FIELD(value, RG_EOSC1_STR_ENB, 1, 11);
    PRINT_FIELD(value, RG_EOSC1_VCT_EN, 1, 12);
    PRINT_FIELD(value, RG_EOSC2_BIAS_CT0, 1, 16);
    PRINT_FIELD(value, RG_EOSC2_BIAS_CT1, 1, 17);
    PRINT_FIELD(value, RG_EOSC2_BIAS_DN, 2, 18);
    PRINT_FIELD(value, RG_EOSC2_CALI, 5, 20);
    PRINT_FIELD(value, RG_EOSC2_FREQ_CT0, 1, 25);
    PRINT_FIELD(value, RG_EOSC2_FREQ_CT1, 1, 26);
    PRINT_FIELD(value, RG_EOSC_EN, 1, 27);

    value = (uint32_t)rtc_32k_register->RTC_OSC32CON1;
    log_rtc_info("RTC_OSC32CON1 : 0x%08X\n", 1, value);
    PRINT_FIELD(value, RG_QI_XOSC_PWDB, 1, 0);
    PRINT_FIELD(value, RG_XOSC_AMP_EN, 1, 1);
    PRINT_FIELD(value, RG_XOSC_CALI, 4, 2);
    PRINT_FIELD(value, RG_XOSC_CGM_LP_EN, 1, 6);
    PRINT_FIELD(value, RG_XOSC_CGM_STR_ENB, 1, 7);
    PRINT_FIELD(value, RG_XOSC_LPMODEB, 1, 8);
    PRINT_FIELD(value, RG_XOSC_SW_EN, 1, 9);
    PRINT_FIELD(value, RG_XOSC_AC_ON, 1, 10);
    PRINT_FIELD(value, RG_XOSC_CAP, 3, 11);
    PRINT_FIELD(value, RG_XOSC_DMY, 4, 14);
    PRINT_FIELD(value, RG_XOSC_DMY_EN, 1, 18);
    PRINT_FIELD(value, RG_RFB_BYPASS, 1, 19);
    PRINT_FIELD(value, RG_XOSC_ULP_EN, 1, 20);

    value = (uint32_t)rtc_32k_register->RTC_OSC32CON2;
    log_rtc_info("RTC_OSC32CON2 : 0x%08X\n", 1, value);
    PRINT_FIELD(value, RTC_REV, 16, 0);
    PRINT_FIELD(value, F32K_SEL, 2, 16);
    PRINT_FIELD(value, RTCSYS_32K_SEL, 1, 24);

    value = (uint32_t)rtc_32k_register->RTC_DEBUG_CON;
    log_rtc_info("RTC_DEBUG_CON : 0x%08X\n", 1, value);
    PRINT_FIELD(value, RTC_DEBUG_MON_SEL, 4, 0);
    PRINT_FIELD(value, RTC_DEBUG_MON_EN, 1, 8);
    PRINT_FIELD(value, RTC_DEBUG_OUT, 16, 16);

    value = (uint32_t)rtc_32k_register->RTC_SPAR_REG;
    log_rtc_info("RTC_SPAR_REG : 0x%08X\n", 1, value);
    PRINT_FIELD(value, RTC_SPAR_REG_0, 16, 0);
    PRINT_FIELD(value, RTC_SPAR_REG_1, 16, 16);

    value = (uint32_t)rtc_32k_register->RTC_SPAR0;
    log_rtc_info("RTC_SPAR0 : 0x%08X\n", 1, value);
    PRINT_FIELD(value, RTC_SRAR_0_0, 16, 0);
    PRINT_FIELD(value, RTC_SPAR_0_1, 16, 16);

    value = (uint32_t)rtc_32k_register->RTC_SPAR1;
    log_rtc_info("RTC_SPAR1 : 0x%08X\n", 1, value);
    PRINT_FIELD(value, RTC_SRAR_1_0, 16, 0);
    PRINT_FIELD(value, RTC_SPAR_1_1, 16, 16);

    value = (uint32_t)rtc_32k_register->RTC_SPAR2;
    log_rtc_info("RTC_SPAR2 : 0x%08X\n", 1, value);
    PRINT_FIELD(value, RTC_SRAR_2_0, 16, 0);
    PRINT_FIELD(value, RTC_SPAR_2_1, 16, 16);

    value = (uint32_t)rtc_32k_register->RTC_SYS32K_CG_CON;
    log_rtc_info("RTC_SYS32K_CG_CON : 0x%08X\n", 1, value);
    PRINT_FIELD(value, rtcsys_cg_con_0_led_32k, 1, 0);
    PRINT_FIELD(value, rtcsys_cg_con_1_qdec_32k, 1, 1);
    PRINT_FIELD(value, rtcsys_cg_con_2_ramboz_32k, 1, 2);
    PRINT_FIELD(value, rtcsys_cg_con_3_rtctimer_32k, 1, 3);
    PRINT_FIELD(value, rtcsys_cg_con_4_rtcsys_bt_counter, 1, 4);
    PRINT_FIELD(value, rtcsys_cg_con_5_rsv, 3, 5);
    log_rtc_info("32K source is 0x%x", 1, rtc_get_current_32k_source());
}

uint32_t rtc_measure_32k_with_windows(uint32_t ref_clk, uint32_t winset)
{
    // 1 RTC_CK,
    // 4 EOSC_F32K,
    // 5 DCXO_F32K,
    // 6 XOSC_F32K,
    uint32_t freq_meter_data = hal_clock_freq_meter_data(ref_clk, xo_ck, winset);
    uint32_t ref_hz = (((uint64_t)DCXO_HZ) * (winset + 1)) / freq_meter_data;
    //log_rtc_warning("winset=%u freq_meter_data=%u ref_hz=%u ref_clk=%u", 3, winset, freq_meter_data, ref_hz, ref_clk);
    return ref_hz;
}

uint32_t rtc_measure_32k(uint32_t ref_clk)
{
    uint32_t winset = hal_clock_fqmtr_winset_estimate(32768, DCXO_HZ);
    return rtc_measure_32k_with_windows(ref_clk, winset);
}

uint32_t rtc_get_eosc32_calibration(uint32_t target_32k_freq)
{
    uint32_t    value          = 0;
    uint8_t     eosc_cali      = 0;
    int         low_eosccali   = 0x00;
    int         high_eosccali  = 0x1f;
    uint32_t    medium_eosccali = 0;
    uint32_t    low_frequency  = 0;
    uint32_t    high_frequency = 0;
    uint32_t    medium_frequency = 0;

    /*//set eosc freq to the highest*/
    rtc_32k_register->RTC_OSC32CON[0] &= ~ (RTC_OSC32CON0_EOSC1_CALI_MASK | RTC_OSC32CON0_EOSC2_CALI_MASK);

    high_frequency = rtc_measure_32k_with_windows(EOSC_F32K, 99);
    if (high_frequency <= target_32k_freq) {
        log_rtc_error("high_freq(%u) <= %u, xosccali = %u \r\n", 2, (unsigned int)high_frequency, (unsigned int)target_32k_freq, (unsigned int)low_eosccali);
        return eosc_cali;
    }
    //set eosc freq to the lowest
    rtc_32k_register->RTC_OSC32CON[0] |= (high_eosccali << RTC_OSC32CON0_EOSC1_CALI_OFFSET) | (high_eosccali << RTC_OSC32CON0_EOSC2_CALI_OFFSET);
    value = rtc_32k_register->RTC_OSC32CON[0];
    low_frequency = rtc_measure_32k_with_windows(EOSC_F32K, 99);

    if (low_frequency >= target_32k_freq) {
        log_rtc_error("low_freq(%u) >= %d, xosccali = %d \r\n", 2, (unsigned int)low_frequency, target_32k_freq, (unsigned int)high_eosccali);
        return eosc_cali;
    }
    #define __ABS__(x) ((x)<0? -(x) :(x))
    while (__ABS__(high_eosccali - low_eosccali) > 1) {
        medium_eosccali = (low_eosccali + high_eosccali) / 2;
        value = (value & ~(RTC_OSC32CON0_EOSC1_CALI_MASK | RTC_OSC32CON0_EOSC2_CALI_MASK)) | (medium_eosccali << RTC_OSC32CON0_EOSC1_CALI_OFFSET) | (medium_eosccali << RTC_OSC32CON0_EOSC2_CALI_OFFSET);
        rtc_32k_register->RTC_OSC32CON[0] = value;
        medium_frequency = rtc_measure_32k_with_windows(EOSC_F32K, 99);
        log_rtc_info("eosc cali(%d) -> frequency(%d), target(%d) \r\n", 3, (int) medium_eosccali, (int)medium_frequency, (int)target_32k_freq);
        if (medium_frequency > target_32k_freq) {
            low_eosccali = medium_eosccali;
            low_frequency = rtc_measure_32k_with_windows(EOSC_F32K, 99);
        } else if (medium_frequency < target_32k_freq) {
            high_eosccali = medium_eosccali;
            high_frequency = rtc_measure_32k_with_windows(EOSC_F32K, 99);
        } else {
            log_rtc_info("eosc cali value = %d \r\n", 1, (int) medium_eosccali);
            eosc_cali = medium_eosccali;
            break;
        }
    }
    log_rtc_info("eosc cali(%d) -> frequency(%d), target(%d) \r\n", 3, (int) medium_eosccali, (int)medium_frequency, (int)target_32k_freq);

    /*get more accuratly value*/
    if (__ABS__(target_32k_freq - low_frequency) < __ABS__(high_frequency - target_32k_freq)) {
        medium_eosccali = (high_eosccali);
    } else {
        medium_eosccali = (low_eosccali);
    }
    value = (value & ~(RTC_OSC32CON0_EOSC1_CALI_MASK | RTC_OSC32CON0_EOSC2_CALI_MASK)) | (medium_eosccali << RTC_OSC32CON0_EOSC1_CALI_OFFSET) | (medium_eosccali << RTC_OSC32CON0_EOSC2_CALI_OFFSET);
    rtc_32k_register->RTC_OSC32CON[0] = value;
    eosc_cali = medium_eosccali;

    log_rtc_info("rtc eosc cali value = %d, frequency %d ,target %d osc32con0=0x%x", 4, \
        (unsigned int) eosc_cali, (unsigned int) rtc_measure_32k_with_windows(EOSC_F32K, 99), (int)target_32k_freq, value);
    return eosc_cali;
}

static void rtc_sys32k_update(void)
{
    rtc_private_parameter_t *config = HAL_RTC_PRIVATE_DATA_ADDR;
    config->freq_f32k = (uint32_t) rtc_measure_32k_with_windows(RTC_CK, RTC_FREQ_MESURE_WINDOW);
    config->freq_eosc = (uint32_t) rtc_measure_32k_with_windows(EOSC_F32K, RTC_FREQ_MESURE_WINDOW);
    config->freq_xosc = (uint32_t) rtc_measure_32k_with_windows(XOSC_F32K, RTC_FREQ_MESURE_WINDOW);
    log_rtc_info("RTC_CLK(%d),EOSC(%d),XOSC(%d), DCXO(%d)",  4, config->freq_f32k, config->freq_eosc, config->freq_xosc, (int)rtc_measure_32k_with_windows(DCXO_F32K, RTC_FREQ_MESURE_WINDOW));
}
void rtc_init_32k(void)
{
    rtc_private_parameter_t *config = HAL_RTC_PRIVATE_DATA_ADDR;

#if 0
    uint32_t value;
    //default:0x954102B
    value =  rtc_32k_register->RTC_OSC32CON[0];
    value &= ~ (RTC_OSC32CON0_EOSC1_CALI_MASK | RTC_OSC32CON0_EOSC2_CALI_MASK | RTC_OSC32CON0_EOSC2_BIAS_DN_MASK | RTC_OSC32CON0_EOSC1_FST_EN_MASK);
    value |= (0x15 << RTC_OSC32CON0_EOSC1_CALI_OFFSET) | (0x15 << RTC_OSC32CON0_EOSC2_CALI_OFFSET) | (0x1 << RTC_OSC32CON0_EOSC2_BIAS_DN_OFFSET) | \
            RTC_OSC32CON0_EOSC1_CHOP_EN_MASK | RTC_OSC32CON0_EOSC1_VCT_EN_MASK | RTC_OSC32CON0_EOSC_EN_MASK;
    rtc_32k_register->RTC_OSC32CON[0] = value;

    //default: 0x5C7AA
    value =  rtc_32k_register->RTC_OSC32CON[1];
    value &= ~ (RTC_OSC32CON1_XOSC_CALI_MASK | RTC_OSC32CON1_XOSC_CAP_MASK | RTC_OSC32CON1_XOSC_DMY_MASK);
    value |= (0xA << RTC_OSC32CON1_XOSC_CALI_OFFSET) | (0x7 << RTC_OSC32CON1_XOSC_DMY_OFFSET) | RTC_OSC32CON1_XOSC_AMP_EN_MASK | RTC_OSC32CON1_XOSC_CGM_STR_ENB_MASK\
            RTC_OSC32CON1_XOSC_LPMODEB_MASK | RTC_OSC32CON1_XOSC_SW_EN_MASK | RTC_OSC32CON1_XOSC_AC_ON_MASK | RTC_OSC32CON1_RFB_BYPASS_MASK;
    rtc_32k_register->RTC_OSC32CON[1] = value;

    //default: 0x10000
    RTC_OSC32CON2_F32K_SEL_MASK
    value =  rtc_32k_register->RTC_OSC32CON[0];
    value &= ~RTC_OSC32CON2_F32K_SEL_MASK;
    value |= (RTC_OSC32CON2_F32K_SEL_EOSC << RTC_OSC32CON2_F32K_SEL_OFFSET);
    rtc_32k_register->RTC_OSC32CON[2] = value;
#else
    rtc_32k_register->RTC_OSC32CON0 &= ~RTC_OSC32CON0_EOSC2_BIAS_DN_MASK;
    log_rtc_info("RTC_OSC32CON[0]=0x%x, RTC_OSC32CON[1]=0x%x, RTC_OSC32CON[2]=0x%x", 3,
        rtc_32k_register->RTC_OSC32CON[0], rtc_32k_register->RTC_OSC32CON[1], rtc_32k_register->RTC_OSC32CON[2]);
#endif

    log_rtc_info("Boot on with RTC32K source=0x%x [b00:DCXO, b01:EOSC, b10:DCXO, b11:XOSC]", 1, rtc_get_current_32k_source());

    if (is_eosc_on()) {
        config->cali_eosc = rtc_get_eosc32_calibration(32768);
    }
    rtc_sys32k_update();
    config->rtc_init_done = true;
}

uint32_t rtc_get_f32k_frequency(void)
{
    rtc_private_parameter_t *config = HAL_RTC_PRIVATE_DATA_ADDR;
    int sys32k_diff = (int)(config->freq_f32k - 32768);
    if (config->rtc_init_done) {
        if ((sys32k_diff < -1000) || (sys32k_diff > 1000)) {
            config->freq_f32k = (uint32_t) rtc_measure_32k_with_windows(RTC_CK, RTC_FREQ_MESURE_WINDOW);
        }
        return config->freq_f32k;
    } else {
        return (uint32_t) rtc_measure_32k_with_windows(RTC_CK, RTC_FREQ_MESURE_WINDOW);
    }
}

#define RTC_CURRENT_32K() ((rtc_32k_register->RTC_OSC32CON2 & RTC_OSC32CON2_F32K_SEL_MASK) >> RTC_OSC32CON2_F32K_SEL_OFFSET)

#define RTC_32K_SELECT_EOSC()   do {\
    uint32_t value = rtc_32k_register->RTC_OSC32CON2;\
    value = (value & ~(RTC_OSC32CON2_F32K_SEL_MASK)) | RTC_OSC32CON2_F32K_SEL_EOSC_MASK;\
    rtc_32k_register->RTC_OSC32CON2 = value;\
} while (0)

#define RTC_32K_SELECT_XOSC()   do {\
    uint32_t value = rtc_32k_register->RTC_OSC32CON2;\
    value = (value & ~(RTC_OSC32CON2_F32K_SEL_MASK)) | RTC_OSC32CON2_F32K_SEL_XOSC_MASK;\
    rtc_32k_register->RTC_OSC32CON2 = value;\
} while (0)

#define RTC_32K_SELECT_DCXO_AO_EOSC()   do {\
    uint32_t value = rtc_32k_register->RTC_OSC32CON2;\
    value = (value & ~(RTC_OSC32CON2_F32K_SEL_MASK)) | RTC_OSC32CON2_F32K_SEL_DCXO_AO_EOSC_MASK;\
    rtc_32k_register->RTC_OSC32CON2 = value;\
} while (0)

#define RTC_32K_SELECT_DCXO_AO_XOSC()   do {\
    uint32_t value = rtc_32k_register->RTC_OSC32CON2;\
    value = (value & ~(RTC_OSC32CON2_F32K_SEL_MASK)) | RTC_OSC32CON2_F32K_SEL_DCXO_AO_XOSC_MASK;\
    rtc_32k_register->RTC_OSC32CON2 = value;\
} while (0)

#define RTC_SYS32K_SELECT_AO32K() do {\
    rtc_32k_register->RTC_OSC32CON2 &= ~(RTC_OSC32CON2_SYS32K_SRC_SEL_MASK);\
} while (0)
#define RTC_SYS32K_SELECT_F32K() do {\
    rtc_32k_register->RTC_OSC32CON2 |= (RTC_OSC32CON2_SYS32K_SRC_SEL_MASK);\
} while (0)

void nocld0_hp_set(void)
{
    *(volatile uint32_t*)0x42108008 = 0x0138ABCD;
    *(volatile uint32_t*)0x42108008 = 0x0109C110;
    *(volatile uint32_t*)0x42108008 = 0x01380000;
}

// set RG_NoCLD0_HP = 0 for low power consume
void nocld0_hp_clear(void)
{
    *(volatile uint32_t*)0x42108008 = 0x0138ABCD;
    *(volatile uint32_t*)0x42108008 = 0x0109C100;
    *(volatile uint32_t*)0x42108008 = 0x01380000;
}

bool nocld0_hp_check(void)
{
    bool is_nocld0_hp_set = false;
    *(volatile uint32_t*)0x42108008 = 0x0138ABCD;
    *(volatile uint32_t*)0x42108008 = 0x0009C100;
    is_nocld0_hp_set = (*(volatile uint32_t*)0x4210800C & (1 << 4)) == (1 << 4);
    *(volatile uint32_t*)0x42108008 = 0x01380000;
    return is_nocld0_hp_set;
}

// Timer callback function for switching to XOSC
/**
 * @brief Timer callback function for switching to XOSC.
 *
 * This function is called when the timer expires to switch to XOSC.
 * It performs the switch to XOSC and disables EOSC after a short delay.
 *
 * @param user_data User data passed to the callback function (not used).
 */
void rtc_switch_to_xosc_callback(void* user_data) {
    uint32_t timer_handle = (uint32_t)user_data;
    if (timer_handle) {
        hal_gpt_sw_free_timer(timer_handle);
    }
    RTC_32K_SELECT_XOSC();
    // wait at least 300us
    hal_gpt_delay_us(400); // Wait for 300 microseconds
    log_rtc_info("Switching to XOSC\n", 0);
    rtc_sys32k_update();
    // turn off eosc
    rtc_32k_eosc_control(false);
    // wait at least 1ms
    hal_gpt_delay_us(1100);

    // set RG_NoCLD0_HP = 0 for low power consume
    nocld0_hp_clear();
}

#ifdef RTC_SWITCH_XOSC_USE_GPT_TIMER
// Set up a timer to call the callback function after 1.5 seconds
/**
 * @brief Set up a timer to call the callback function after 1.5 seconds.
 *
 * This function sets up a GPT timer to call the rtc_switch_to_xosc_callback function
 * after 1.5 seconds. It uses the HAL GPT API to create and start the timer.
 */
void rtc_setup_xosc_timer() {
    uint32_t timer_handle;
    hal_gpt_status_t status;

    status = hal_gpt_sw_get_timer(&timer_handle);
    if (status != HAL_GPT_STATUS_OK) {
        log_rtc_info("Failed to get GPT timer handle\n", 0);
        return;
    }

    status = hal_gpt_sw_start_timer_ms(timer_handle, 1400, rtc_switch_to_xosc_callback, (void*)timer_handle);
    if (status != HAL_GPT_STATUS_OK) {
        log_rtc_info("Failed to start GPT timer\n", 0);
        return;
    }
}
#else
/**
 * @brief Use delay as a placeholder for the timer.
 *
 * This function uses hal_gpt_delay_us to wait for 1.5 seconds and then calls
 * the rtc_switch_to_xosc_callback function. It is used as a placeholder until the
 * GPT timer is ready.
 */
void rtc_setup_xosc_timer() {
    log_rtc_info("Using delay instead of timer\n", 0);
    // step6. wait at least 1.3s
    hal_gpt_delay_ms(1400);
    rtc_switch_to_xosc_callback(NULL);
}
#endif

// Switch to target clock source
/**
 * @brief Switch to the target clock source.
 *
 * This function switches the current 32K clock source to the specified target clock source.
 * It handles the necessary delays and control signals to ensure a smooth transition.
 *
 * @param target_32k The target clock source to switch to.
 *
 * The function handles the following cases:
 * - EOSC to DCXO: Switch directly to DCXO, keeping EOSC on.
 * - EOSC to XOSC: Initialize XOSC, wait for 1.5 seconds, switch to XOSC, wait for 300 microseconds, then disable EOSC.
 * - XOSC to EOSC: Enable EOSC if not already on, wait for 500 microseconds, switch to EOSC, wait for 300 microseconds, then disable XOSC.
 * - XOSC to DCXO: Switch directly to DCXO, keeping XOSC on.
 * - DCXO to EOSC: Enable EOSC if not already on, wait for 500 microseconds, switch to EOSC, wait for 300 microseconds, then disable XOSC and DCXO.
 * - DCXO to XOSC: Enable XOSC if not already on, wait for 1.5 seconds, switch to XOSC, wait for 300 microseconds, then disable EOSC and DCXO.
 */
hal_rtc_status_t hal_rtc_switch_32k_source(hal_rtc_osc32k_mode_t target_32k)
{
    uint32_t current_32k = RTC_CURRENT_32K();/*b00:DCXO, b01:EOSC, b10:DCXO, b11:XOSC*/

    static const hal_rtc_osc32k_mode_t rtc_osc32k_mode[] = {
        HAL_RTC_OSC32K_DCXO_MODE,
        HAL_RTC_OSC32K_EOSC_MODE,
        HAL_RTC_OSC32K_DCXO_MODE,
        HAL_RTC_OSC32K_XOSC_MODE
    };

    if (rtc_osc32k_mode[current_32k] == target_32k) {
        log_rtc_info("Current clock source [0x%x] is already the target\n", 1, current_32k);
    }

    switch (current_32k) {
        case RTC_OSC32CON2_F32K_SEL_EOSC:
            if (target_32k == HAL_RTC_OSC32K_DCXO_MODE) {
                // EOSC to DCXO: Switch directly to DCXO, keeping EOSC on
                log_rtc_info("Switching to DCXO from EOSC, EOSC must remain on\n", 0);
                if (!is_dcxo_on()) {
                    rtc_32k_dcxo_control(true);
                }
                RTC_32K_SELECT_DCXO_AO_EOSC();
            } else if (target_32k == HAL_RTC_OSC32K_XOSC_MODE) {
                log_rtc_info("Switching to XOSC from EOSC", 0);
                rtc_32k_xosc_control(true);
                rtc_setup_xosc_timer(); // Set up the timer to switch to XOSC
            } else if (target_32k == HAL_RTC_OSC32K_EOSC_MODE) {
                log_rtc_info("Already EOSC, just set low power configs ", 0);
                if (!is_eosc_on()) {
                    rtc_32k_eosc_control(true);
                    hal_gpt_delay_us(500); // Wait for 500 microseconds
                }
                RTC_32K_SELECT_EOSC();
                // set RG_NoCLD0_HP = 0 for low power consume
                nocld0_hp_clear();
            }
            break;

        case RTC_OSC32CON2_F32K_SEL_XOSC:
            if (target_32k == HAL_RTC_OSC32K_EOSC_MODE) {
                // XOSC to EOSC: Enable EOSC if not already on, wait for 500 microseconds, switch to EOSC, wait for 300 microseconds, then disable XOSC
                if (!is_eosc_on()) {
                    rtc_32k_eosc_control(true);
                    hal_gpt_delay_us(500); // Wait for 500 microseconds
                }
                log_rtc_info("Switching to EOSC from XOSC\n", 0);
                RTC_32K_SELECT_EOSC();
                hal_gpt_delay_us(300); // Wait for 300 microseconds
                // set RG_NoCLD0_HP = 0 for low power consume
                nocld0_hp_clear();
                rtc_32k_xosc_control(false);
            } else if (target_32k == HAL_RTC_OSC32K_DCXO_MODE) {
                // XOSC to DCXO: Switch directly to DCXO, keeping XOSC on
                log_rtc_info("Switching to DCXO from XOSC, XOSC must remain on\n", 0);
                if (!is_dcxo_on()) {
                    rtc_32k_dcxo_control(true);
                }
                RTC_32K_SELECT_DCXO_AO_XOSC();
                rtc_32k_eosc_control(false);
            }
            break;

        case RTC_OSC32CON2_F32K_SEL_DCXO_AO_EOSC:
        case RTC_OSC32CON2_F32K_SEL_DCXO_AO_XOSC:
            if (target_32k == HAL_RTC_OSC32K_EOSC_MODE) {
                // DCXO to EOSC: Enable EOSC if not already on, wait for 500 microseconds, switch to EOSC, wait for 300 microseconds, then disable XOSC and DCXO
                if (!is_eosc_on()) {
                    rtc_32k_eosc_control(true);
                    hal_gpt_delay_us(500); // Wait for 500 microseconds
                }
                log_rtc_info("Switching to EOSC from DCXO\n", 0);
                RTC_32K_SELECT_EOSC();
                hal_gpt_delay_us(300); // Wait for 300 microseconds
                // set RG_NoCLD0_HP = 0 for low power consume
                nocld0_hp_clear();
                rtc_32k_dcxo_control(false);
            } else if (target_32k == HAL_RTC_OSC32K_XOSC_MODE) {
                // DCXO to XOSC: Enable XOSC if not already on, wait for 1.5 seconds, switch to XOSC, wait for 300 microseconds, then disable EOSC and DCXO
                log_rtc_info("Switching to XOSC from DCXO\n", 0);
                if (!is_xosc_on()) {
                    rtc_32k_xosc_control(true);
                    rtc_setup_xosc_timer(); // Set up the timer to switch to XOSC after 1.5 seconds
                } else {
                    rtc_switch_to_xosc_callback(NULL); // Directly call the callback if XOSC is already on
                }
                rtc_32k_eosc_control(false);
                rtc_32k_dcxo_control(false);
            }
            break;
    }
#ifdef RTC_SYS32K_USE_F32K
    RTC_SYS32K_SELECT_F32K();
#else
    RTC_SYS32K_SELECT_AO32K();
#endif
    hal_gpt_delay_ms(1);
    //xosc delay setup, update f32k in xosc setuu callback
    if (target_32k != HAL_RTC_OSC32K_XOSC_MODE) {
        rtc_sys32k_update();
    }
    return HAL_RTC_STATUS_OK;
}

/**
 * @brief Control the EOSC clock source.
 *
 * This function enables or disables the EOSC clock source based on the input parameter.
 *
 * @param eosc_on If true, enable EOSC. If false, disable EOSC.
 */
void rtc_32k_eosc_control(bool eosc_on) {
    if (eosc_on) {
        log_rtc_info("EOSC enabled\n", 0);
        rtc_32k_register->RTC_OSC32CON0 |= RTC_OSC32CON0_EOSC_EN_MASK;
    } else {
        log_rtc_info("EOSC disabled\n", 0);
        rtc_32k_register->RTC_OSC32CON0 &= ~RTC_OSC32CON0_EOSC_EN_MASK;
    }
}

/**
 * @brief Control the XOSC clock source.
 *
 * This function enables or disables the XOSC clock source based on the input parameter.
 *
 * @param xosc_on If true, enable XOSC. If false, disable XOSC.
 */
void rtc_32k_xosc_control(bool xosc_on)
{
    if (xosc_on) {
        if (!nocld0_hp_check()) {
            nocld0_hp_set();
            log_rtc_info("set nocld0_hp for xosc init\n", 0);
            hal_gpt_delay_us(100);
        }
        /*1. set f32k=XOSC(xosc_on, eosc_off, dcxo_off)*/
        // XOSC initial setting :
        // step1. set GPIO23(XIN) & GPIO24(XOUT) to analog mode
        hal_gpio_set_analog_mode(HAL_GPIO_23);
        hal_gpio_set_analog_mode(HAL_GPIO_24);
        // step2. set RG_QI_XOSC_PWDB = 1
        // rtc_32k_register->RTC_OSC32CON1 |= RTC_OSC32CON1_XOSC_QI_PWDB_MASK;
        rtc_32k_register->RTC_OSC32CON1 = 0x1F927;
        // step3. wait at least 700ms
        hal_gpt_delay_ms(800);
        // step4. XOSC LPM
        rtc_32k_register->RTC_OSC32CON1 = 0x1F867;
        // step5. set PMU_DIG_MISC0[0] = 1, XOSC IO will fix to analog mode
        #define PMU_DIG_MISC0 0x42108058
        *(volatile uint32_t*)PMU_DIG_MISC0 |= 0x1;
    } else {
        // 1. Clear GPIO23(XIN) & GPIO24(XOUT) analog mode
        hal_gpio_clear_analog_mode(HAL_GPIO_23);
        hal_gpio_clear_analog_mode(HAL_GPIO_24);
        // 2. set PMU_DIG_MISC0[0] = 0, XOSC IO will not fix to analog mode
        #define PMU_DIG_MISC0 0x42108058
        *(volatile uint32_t*)PMU_DIG_MISC0 &= ~0x1;
        // 3. power off xosc
        rtc_32k_register->RTC_OSC32CON1 &= ~RTC_OSC32CON1_XOSC_QI_PWDB_MASK;
        log_rtc_info("XOSC disabled\n", 0);
    }
}

/**
 * @brief Control the DCXO clock source.
 *
 * This function enables or disables the DCXO clock source based on the input parameter.
 *
 * @param dcxo_on If true, enable DCXO. If false, disable DCXO.
 */
void rtc_32k_dcxo_control(bool dcxo_on) {
    if (dcxo_on) {
        // Enable DCXO
        hal_dcxo_32k_ctrl(true);
        log_rtc_info("DCXO enabled\n", 0);
    } else {
        // Disable DCXO
        hal_dcxo_32k_ctrl(false);
        log_rtc_info("DCXO disabled\n", 0);
    }
}

/**
 * @brief Check if the EOSC clock source is on.
 *
 * This function checks if the EOSC clock source is currently on.
 *
 * @return 1 if EOSC is on, 0 otherwise.
 */
int is_eosc_on() {
    // Check if EOSC is on
    int is_on = rtc_32k_register->RTC_OSC32CON0 & RTC_OSC32CON0_EOSC_EN_MASK ? 1 : 0;
    log_rtc_info("Checking if EOSC is on:%d\n", 1, is_on);
    return is_on; // Return 1 if EOSC is on, 0 otherwise
}

/**
 * @brief Check if the XOSC clock source is on.
 *
 * This function checks if the XOSC clock source is currently on.
 *
 * @return 1 if XOSC is on, 0 otherwise.
 */
int is_xosc_on() {
    // Check if XOSC is on
    int is_on = rtc_32k_register->RTC_OSC32CON1 & RTC_OSC32CON1_XOSC_QI_PWDB_MASK ? 1 : 0;
    log_rtc_info("Checking if XOSC is on:%d\n", 1, is_on);
    return is_on; // Return 1 if XOSC is on, 0 otherwise
}

/**
 * @brief Check if the DCXO clock source is on.
 *
 * This function checks if the DCXO clock source is currently on.
 *
 * @return 1 if DCXO is on, 0 otherwise.
 */
int is_dcxo_on() {
    // Check if DCXO is on
    int is_on = hal_dcxo_32k_is_enabled();
    log_rtc_info("Checking if DCXO is on:%d\n", 1, is_on);
    return is_on;// Return 1 if DCXO is on, 0 otherwise
}


void rtc_debug_control(uint32_t debug_sel)
{
    //TOP_DEBUG_CTRL
    *(volatile uint32_t *)0x42010108 = 0x1C;
    //RTC_DEBUG_EN
    *(volatile uint32_t *)0x42107038 = 0x0001;

    rtc_32k_register->RTC_DEBUG_CON = RTC_DEBUG_CON_DBG_EN_MASK|(debug_sel&0xF);
}

uint32_t rtc_get_current_32k_source(void)
{
    return RTC_CURRENT_32K();/*b00:DCXO, b01:EOSC, b10:DCXO, b11:XOSC*/
}

void hal_rtc_output_32k_to_gpio(uint8_t pin, uint8_t pin_func, uint32_t debug_sel)
{
    rtc_debug_control(debug_sel);
    hal_gpio_disable_pull(pin);
    hal_pinmux_set_function(pin, pin_func);
}

void rtc_access_retention_regs(uint32_t offset, uint8_t *buff, uint32_t size, uint8_t is_write)
{
    for (uint32_t i = 0; i < size; i++) {
        uint32_t reg_index = (offset + i) >> 2;
        uint32_t byte_index = (offset + i) & 3;
        uint32_t reg_value = rtc_32k_register->RTC_SPAR[reg_index];

        if (is_write) {
            reg_value &= ~(0xFF << (byte_index << 3));
            reg_value |= (buff[i] << (byte_index << 3));
            rtc_32k_register->RTC_SPAR[reg_index] = reg_value;
        } else {
            buff[i] = (reg_value >> (byte_index << 3)) & 0xFF;
        }
    }
}


#endif //HAL_RTC_MODULE_ENABLED


