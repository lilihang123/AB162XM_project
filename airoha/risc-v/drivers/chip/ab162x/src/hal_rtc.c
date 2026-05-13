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


#include "hal_rtc.h"
#include "hal_rtc_internal.h"
#include "hal_nvic.h"
#include "syslog.h"
#ifdef HAL_RTC_MODULE_ENABLED

RTC_TIMER_REGISTER_T *rtc_base = (RTC_TIMER_REGISTER_T *)RTC_BASE;

rtc_context_t g_rtc_context[HAL_RTC_TIMER_MAX];
sw_rtc_context_t sw_rtc_context;
sw_rtc_user_type_t sw_rtc;
uint16_t rtc_unit = 1;   //resoultion 1ms
MinHeap* heap;
hal_rtc_time_t init_time={0,0,0,1,1,1,2024,0};


void rtc_reset_default_timer(hal_rtc_timer_port_t rtc_timer_port)
{
    if(rtc_timer_port != HAL_RTC_TIMER_2){
        rtc_base->rtc_config[rtc_timer_port].rtc_irq_en.field.IRQEN0 = 0;  /* disable interrupt */
        rtc_base->rtc_config[rtc_timer_port].rtc_con.word = 0;  /* reset con */
        rtc_base->rtc_config[rtc_timer_port].rtc_clr.word = 1; /* clear counter value */
        while (!(rtc_base->rtc_t_clrsta.word & (1 << rtc_timer_port)));
        rtc_base->rtc_config[rtc_timer_port].rtc_irq_ack.word = 1; /* clear interrupt status */
        rtc_base->rtc_config[rtc_timer_port].rtc_compare.word = 0xffffffff;       /* set max threshold value */
        while (!(rtc_base->rtc_t_wcompsta.word  & (1 << rtc_timer_port)));
    }else{
        rtc_base->rtc_ao_config.rtc_irq_en.field.IRQEN0 = 0;  /* disable interrupt */
        rtc_base->rtc_ao_config.rtc_con.word = 0;  /* reset con */
        rtc_base->rtc_ao_config.rtc_clr.word = 1; /* clear counter value */
        while (!(rtc_base->rtc_ao_t_clrsta.word & 1));
        rtc_base->rtc_ao_config.rtc_irq_ack.word = 1; /* clear interrupt status */
        rtc_base->rtc_ao_config.rtc_compare.word = 0xffffffff;       /* set max threshold value */
        while (!(rtc_base->rtc_ao_t_wcompsta.word  & 1));
    }
}


hal_rtc_status_t hal_rtc_timer_init(hal_rtc_timer_port_t rtc_timer_port)
{
    if(rtc_timer_port == HAL_RISCV_RTC_TIME){
        return HAL_RTC_STATUS_ERROR_PORT;
    }

    if ((g_rtc_context[rtc_timer_port].running_status == HAL_RTC_RUNNING) || (g_rtc_context[rtc_timer_port].has_initilized == true)) {
        return HAL_RTC_STATUS_ERROR;
    }
    /*set structure to 0 */
    memset(&g_rtc_context[rtc_timer_port], 0, sizeof(rtc_context_t));
    if(rtc_timer_port != HAL_RTC_TIMER_2){
        rtc_base->rtc_config[rtc_timer_port].rtc_con.field.SW_CG0 = 1;
        rtc_base->rtc_t_irqmask1.word    &= ~(1 << rtc_timer_port); //RISCV IRQ enable
        rtc_base->rtc_t_wakeupmask1.word &= ~(1 << rtc_timer_port); //RISCV wakeup enable
        /*disable interrutp*/
        rtc_base->rtc_config[rtc_timer_port].rtc_irq_en.field.IRQEN0 = 0;
    }else{
        rtc_base->rtc_ao_config.rtc_con.field.SW_CG0 = 1;
        rtc_base->rtc_ao_t_irqmask1.word    &= ~(1); //RISCV IRQ enable
        rtc_base->rtc_ao_t_wakeupmask1.word &= ~(1); //RISCV wakeup enable
        /*disable interrutp*/
        rtc_base->rtc_ao_config.rtc_irq_en.field.IRQEN0 = 0;
    }

#ifdef RTC_DEBUG_LOG
    log_hal_msgid_info("[RTC%d] init OK\r\n", 1, (int)rtc_timer_port);
#endif
    /*set flag respect this port has initlized */
    g_rtc_context[rtc_timer_port].has_initilized = true;
    return HAL_RTC_STATUS_OK;
}

hal_rtc_status_t hal_rtc_timer_deinit(hal_rtc_timer_port_t rtc_timer_port)
{
    if(rtc_timer_port == HAL_RISCV_RTC_TIME){
        return HAL_RTC_STATUS_ERROR_PORT;
    }
    if (g_rtc_context[rtc_timer_port].running_status == HAL_RTC_RUNNING) {
        return HAL_RTC_STATUS_ERROR;
    }
        /* set structure to 0 */
    memset(&g_rtc_context[rtc_timer_port], 0, sizeof(rtc_context_t));

    /* set flag indicate this port has deinitlized */
    g_rtc_context[rtc_timer_port].has_initilized = false;

    rtc_base->rtc_t_irqmask1.word  |= (1 << rtc_timer_port); //DSP IRQ disable
    rtc_reset_default_timer(rtc_timer_port);
 
#ifdef RTC_DEBUG_LOG
    log_hal_msgid_info("[RTC%d] deinit OK\r\n", 1, (int)rtc_timer_port);
#endif
    return HAL_RTC_STATUS_OK;
}
hal_rtc_status_t hal_rtc_enable_time(void){
    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    if(g_rtc_context[HAL_RISCV_RTC_TIME].has_initilized == false) {
        memset(&sw_rtc_context, 0, sizeof(sw_rtc_context_t));
        if(HAL_RISCV_RTC_TIME == 2){
            rtc_base->rtc_ao_config.rtc_con.field.SW_CG0 = 0;  /* enable clock */
            rtc_base->rtc_ao_t_irqmask1.word    &= ~(1); //CM4 IRQ enable
            rtc_base->rtc_ao_t_wakeupmask1.word &= ~(1); //CM4 wakeup enable
            rtc_base->rtc_ao_config.rtc_clk.field.CLK0 =RTC_CLOCK_32KHZ; /* clk*/
            rtc_base->rtc_ao_config.rtc_con.field.MODE0 = 2; //FREERUN_I MODE
            rtc_base->rtc_ao_config.rtc_clr.word = 1; /* clear counter value */
            while (!(rtc_base->rtc_ao_t_clrsta.word & 1));
            rtc_base->rtc_ao_config.rtc_irq_ack.word = 1; /* clear interrupt status */
            rtc_base->rtc_ao_config.rtc_compare.word = 0xFFFFFFFF;       /* set overflow IRQ */
            while (!(rtc_base->rtc_ao_t_wcompsta.word  & 1 ));
            rtc_base->rtc_ao_config.rtc_irq_en.field.IRQEN0 = 1;  /* enable interrupt */
            rtc_base->rtc_ao_config.rtc_con.field.EN0 = 1;  /* enable */
        }
        else{
            rtc_base->rtc_config[HAL_RISCV_RTC_TIME].rtc_con.field.SW_CG0 = 0;  /* enable clock */
            rtc_base->rtc_t_irqmask1.word    &= ~(1 << HAL_RISCV_RTC_TIME); //CM4 IRQ enable
            rtc_base->rtc_t_wakeupmask1.word &= ~(1 << HAL_RISCV_RTC_TIME); //CM4 wakeup enable
            rtc_base->rtc_config[HAL_RISCV_RTC_TIME].rtc_clk.field.CLK0 = RTC_CLOCK_32KHZ; /* clk*/
            rtc_base->rtc_config[HAL_RISCV_RTC_TIME].rtc_con.field.MODE0 = 2; //FREERUN_I MODE
            rtc_base->rtc_config[HAL_RISCV_RTC_TIME].rtc_clr.word = 1; /* clear counter value */
            while (!(rtc_base->rtc_t_clrsta.word & (1 << HAL_RISCV_RTC_TIME)));
            rtc_base->rtc_config[HAL_RISCV_RTC_TIME].rtc_irq_ack.word = 1; /* clear interrupt status */
            rtc_base->rtc_config[HAL_RISCV_RTC_TIME].rtc_compare.word = 0xFFFFFFFF;       /* set overflow IRQ */
            while (!(rtc_base->rtc_t_wcompsta.word  & (1 << HAL_RISCV_RTC_TIME)));
            rtc_base->rtc_config[HAL_RISCV_RTC_TIME].rtc_irq_en.field.IRQEN0 = 1;  /* enable interrupt */
            rtc_base->rtc_config[HAL_RISCV_RTC_TIME].rtc_con.field.EN0 = 1;  /* enable */
        }
        g_rtc_context[HAL_RISCV_RTC_TIME].callback_context.callback  = (hal_rtc_time_callback_t)sw_rtc_callback;
        sw_rtc = SW_RTC_NOT_USER;
        g_rtc_context[HAL_RISCV_RTC_TIME].callback_context.user_data = &sw_rtc;
        rtc_nvic_register();
        g_rtc_context[HAL_RISCV_RTC_TIME].has_initilized = true;
    }
    hal_nvic_restore_interrupt_mask(mask);
    return HAL_RTC_STATUS_OK;
}

hal_rtc_status_t hal_rtc_disable_time(void){
    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    if(g_rtc_context[HAL_RISCV_RTC_TIME].has_initilized == true) {
        freeMinHeap(heap);
        memset(&g_rtc_context[HAL_RISCV_RTC_TIME], 0, sizeof(rtc_context_t));
        memset(&sw_rtc_context, 0, sizeof(sw_rtc_context_t));
        rtc_reset_default_timer(HAL_RISCV_RTC_TIME);
        g_rtc_context[HAL_RISCV_RTC_TIME].has_initilized = false;
    }
    hal_nvic_restore_interrupt_mask(mask);
    return HAL_RTC_STATUS_OK;
}

hal_rtc_status_t hal_rtc_alarm_get_handle(uint32_t *handle)
{
    uint32_t i, mask;
    if(g_rtc_context[HAL_RISCV_RTC_TIME].has_initilized == false) {
        return HAL_RTC_STATUS_ERROR;
    }
    if (handle == NULL) {
        return HAL_RTC_STATUS_INVALID_PARAM;
    }
    if(sw_rtc_context.creat_heap == false){                                                                             //add  overflow IRQ;
        heap = createMinHeap(HAL_SW_RTC_MAX_USERS+1);
        if(heap == NULL){
            return HAL_RTC_STATUS_ERROR;
        }
        sw_rtc_context.creat_heap = true;
    }
    if(heap->size == HAL_SW_RTC_MAX_USERS){
        return HAL_RTC_STATUS_ERROR_PORT_USE_FULL;
    }
    hal_nvic_save_and_set_interrupt_mask(&mask);
    i=getKey(heap);
    if(i == -1){
        hal_nvic_restore_interrupt_mask(mask);
        return HAL_RTC_STATUS_ERROR;
    }
    *handle = i | SW_RTC_HANDLE_MAGIC_NUMBER;
    hal_nvic_restore_interrupt_mask(mask);
    return HAL_RTC_STATUS_OK;
}

hal_rtc_status_t hal_rtc_alarm_free_handle(uint32_t handle)
{
    uint32_t mask;
    sw_rtc_note_status_t status = SW_RTC_NOTE_STATUS_OF_FREE;
    if ((handle & SW_RTC_HANDLE_MAGIC_NUMBER) != SW_RTC_HANDLE_MAGIC_NUMBER) {
        return HAL_RTC_STATUS_INVALID_PARAM;
    }
    if(sw_rtc_context.creat_heap != true){
        return HAL_RTC_STATUS_ERROR;
    }
    uint32_t index = SW_RTC_HANDLE_TO_INDEX(handle);
    statusGetHeap(heap,index,&status);
    if(status != SW_RTC_NOTE_STATUS_OF_ALLOC){
        return HAL_RTC_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&mask);
    statusChangeHeap(heap,index,SW_RTC_NOTE_STATUS_OF_FREE);
    hal_nvic_restore_interrupt_mask(mask);
    return HAL_RTC_STATUS_OK;
}



hal_rtc_status_t hal_rtc_set_alarm_ms(uint32_t handle, uint64_t timeout_time_ms, hal_rtc_time_callback_t callback, void *user_data)
{
    if(sw_rtc_context.creat_heap != true){
        return HAL_RTC_STATUS_ERROR;
    }
    return sw_rtc_timer_start(handle,timeout_time_ms,callback,user_data);
}

hal_rtc_status_t hal_rtc_stop_alarm(uint32_t handle)
{
    if(sw_rtc_context.creat_heap != true){
        return HAL_RTC_STATUS_ERROR;
    }
    return sw_rtc_timer_stop(handle);
}

hal_rtc_status_t hal_rtc_set_alarm(uint32_t handle, const hal_rtc_time_t *time, hal_rtc_time_callback_t callback, void *user_data)
{
    uint64_t timeout_time_ms = rtc_time_diff(time);
    hal_rtc_time_t current_time;
    hal_rtc_get_time(&current_time);
    uint64_t current_time_ms = rtc_time_diff(&current_time);
    if(timeout_time_ms<current_time_ms){
        return HAL_RTC_STATUS_INVALID_PARAM;
    }else{
        timeout_time_ms = timeout_time_ms - current_time_ms;
    }
    return hal_rtc_set_alarm_ms(handle,timeout_time_ms,callback,user_data);
}

hal_rtc_status_t hal_rtc_get_alarm_ms(uint32_t handle, uint64_t *remain_time){
    if(sw_rtc_context.creat_heap != true){
        return HAL_RTC_STATUS_ERROR;
    }
    return sw_rtc_get_remaining_time(handle, remain_time);
}
hal_rtc_status_t hal_rtc_set_time(const hal_rtc_time_t *time){
    uint32_t mask;
    memcpy(&init_time,time,sizeof(hal_rtc_time_t));
    hal_nvic_save_and_set_interrupt_mask(&mask);
    sw_rtc_context.timer_count = hal_rtc_get_current(HAL_RISCV_RTC_TIME);
    sw_rtc_context.timer_overflow = sw_rtc_context.current_overflow;
    hal_nvic_restore_interrupt_mask(mask);
    return HAL_RTC_STATUS_OK;
}

hal_rtc_status_t hal_rtc_get_time(hal_rtc_time_t *time) {
    hal_rtc_status_t status;
    status = rtc_get_time(time);
    return status;
}

hal_rtc_status_t hal_rtc_get_alarm(uint32_t handle, hal_rtc_time_t *time){
    uint64_t remain_time;
    hal_rtc_status_t status;
    status = sw_rtc_get_remaining_time(handle, &remain_time);
    if(status != HAL_RTC_STATUS_OK){
        return status;
    }
    hal_rtc_time_t time0;
    memset(&time0,0,sizeof(time0));
    return rtc_get_time_change(time,time0,remain_time);
}

#endif //HAL_RTC_MODULE_ENABLED


