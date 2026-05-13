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
#include "hal_rtc_internal.h"
#include "hal_gpt.h"
#include "hal_nvic.h"
#include "syslog.h"
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
#define RTC_IRQ_NUM 19

timeout_elements_t timeout_elements_array[HAL_SW_RTC_MAX_USERS+1];
int user_index_array[HAL_SW_RTC_MAX_USERS+1];
MinHeap heap_array={timeout_elements_array,user_index_array,0,0};
MinHeap* createMinHeap(int capacity){
    heap = &heap_array;
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
    return;
}

int getKey(MinHeap* heap){
    if(heap == NULL){
        return -1;
    }
    for(int i =0;i< heap->capacity;i++){
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
        // printk("heap is full\n");
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
        // printk("heap is empty");
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
            if(i != HAL_MCU_RTC_TIME){
                rtc_base->rtc_config[i].rtc_irq_ack.field.IRQACK0 = 1;
                if (g_rtc_context[i].callback_context.callback != NULL) {
                    g_rtc_context[i].callback_context.callback(g_rtc_context[i].callback_context.user_data);
                }
            }
        }
    }
    if((rtc_base->rtc_ao_config.rtc_irq_sta.field.IRQSTA0) && (rtc_base->rtc_ao_config.rtc_irq_en.field.IRQEN0)){
        if(HAL_RTC_TIMER_2 != HAL_MCU_RTC_TIME){
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
    if(port == HAL_RISCV_RTC_TIME){
        hal_nvic_save_and_set_interrupt_mask(&mask);
        if(HAL_RISCV_RTC_TIME == 2){
            rtc_base->rtc_ao_config.rtc_compare.word = next_expired_count;       /* set overflow IRQ */
            while (!(rtc_base->rtc_ao_t_wcompsta.word & 1 ));
        }else{
            rtc_base->rtc_config[HAL_RISCV_RTC_TIME].rtc_compare.word = next_expired_count;       /* set overflow IRQ */
            while (!(rtc_base->rtc_t_wcompsta.word & (1 << HAL_RISCV_RTC_TIME)));
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
    // rtc_base->rtc_t_irqmask1.word    &= ~(1 << port); //CM4 IRQ enable
    // rtc_base->rtc_t_wakeupmask1.word &= ~(1 << port); //CM4 wakeup enable
    // rtc_base->rtc_config[port].rtc_irq_en.field.IRQEN0 = 1;  /* enable interrupt */

}
uint64_t rtc_convert_ms_to_32k_count(uint64_t ms)
{
// #ifdef HAL_RTC_MODULE_ENABLED
//     uint32_t tick_per_second = 32768, temp = 0;

//     hal_rtc_get_f32k_frequency(&tick_per_second);
//     temp = ms * (tick_per_second / 1000) + (ms * (tick_per_second % 1000))/1000;

//     return temp;
// #else
    return ((uint64_t)(ms * 32 + (7 * ms) / 10 + (6 * ms) / 100 + (8 * ms) / 1000));
// #endif
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
        current_count = hal_rtc_get_current(HAL_RISCV_RTC_TIME);
        next_timeout = getMin(heap);
        if(next_timeout.user_id != -1){
            hal_nvic_save_and_set_interrupt_mask(&mask);//re-start again
            if((next_timeout.status == SW_RTC_NOTE_STATUS_OF_RUNING) && compare_special(sw_rtc_context.current_overflow,current_count,next_timeout.expire_overflow,next_timeout.expire_count) ==1){
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
                    clear_rtc_and_restart_hw_rtc(next_timeout.expire_count, HAL_RISCV_RTC_TIME);
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
        int id = getKey(heap);                                                                            //add  overflow IRQ;
        if(id == -1){
            while(1);
        }
        timeout_elements_t overflow_timeout;
        sw_rtc = SW_RTC_WITH_USER;
        g_rtc_context[HAL_RISCV_RTC_TIME].callback_context.user_data = &sw_rtc;
        overflow_timeout.user_id = id;
        overflow_timeout.expire_count = 0xFFFFFFFF;
        overflow_timeout.expire_overflow = sw_rtc_context.current_overflow;
        overflow_timeout.status = SW_RTC_NOTE_STATUS_OF_RUNING;
        overflow_timeout.callback = NULL;
        overflow_timeout.user_data = (void*)&sw_rtc_overflow;
        insert(heap,overflow_timeout);
        sw_rtc_context.sw_start_first = true;
    }
    current_count = hal_rtc_get_current(HAL_RISCV_RTC_TIME);
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
        // air_assert(0);
        while(1);
    }
    g_sw_rtc_running_note = next_timeout.user_id ;
    clear_rtc_and_restart_hw_rtc(next_timeout.expire_count, HAL_RISCV_RTC_TIME); // restart the rtc.
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
    // current_count = hal_rtc_get_current(HAL_RISCV_RTC_TIME);
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
        clear_rtc_and_restart_hw_rtc(next_timeout.expire_count, HAL_RISCV_RTC_TIME); // restart the rtc.
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
    int user_index = heap->user_index[index];
    current_count = hal_rtc_get_current(HAL_RISCV_RTC_TIME);
    expire_count = heap->timeout_elements[user_index].expire_count;
    expire_overflow = heap->timeout_elements[user_index].expire_overflow;
    remain_count = (expire_overflow<<32 | expire_count) - (current_overflow_cal << 32 | current_count);
    *remain_time  = (remain_count >> 15)*1000 + ((remain_count % 32768) * 1000 + 16384) / 32768;
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

uint32_t hal_rtc_get_current(hal_rtc_timer_port_t port){
    if(port != 2){
        return rtc_base->rtc_config[port].rtc_count.word;
    }else{
        return rtc_base->rtc_ao_config.rtc_count.word;
    }

}

hal_rtc_status_t rtc_get_time_change(hal_rtc_time_t *get_time,hal_rtc_time_t time,uint64_t count){

    uint64_t count_ms = (count >> 15)*1000 + ((count % 32768) * 1000 + 16384) / 32768;
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

hal_rtc_status_t rtc_get_time(hal_rtc_time_t *time) {
    if (time == NULL) {
        return HAL_RTC_STATUS_ERROR;
    }
    uint64_t count = 0;
    uint32_t current_count = hal_rtc_get_current(HAL_RISCV_RTC_TIME);

    if(current_count >= sw_rtc_context.timer_count){
        uint64_t current_overflow_cal = (sw_rtc_context.current_overflow-sw_rtc_context.timer_overflow);
        count = (current_overflow_cal << 32) |(current_count-sw_rtc_context.timer_count);
    }else{
        if(sw_rtc_context.current_overflow< (sw_rtc_context.timer_overflow +1)){
           return HAL_RTC_STATUS_ERROR; 
        }
        uint64_t current_overflow_cal = (sw_rtc_context.current_overflow-sw_rtc_context.timer_overflow -1);
        count = (current_overflow_cal << 32) |(0xFFFFFFFF- current_count+sw_rtc_context.timer_count);
    }
    return rtc_get_time_change(time,init_time,(uint64_t)count);
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

#endif //HAL_RTC_MODULE_ENABLED


