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
#include "hal_gpt.h"
#include "hal_gpio.h"
#include "hal_rtc_internal.h"
#include "hal_nvic_internal.h"
#include "hal_clock_internal.h"
#ifdef HAL_RTC_MODULE_ENABLED

#ifdef HAL_SLEEP_MANAGER_ENABLED
#include "hal_spm.h"
#endif
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
    if(rtc_timer_port == HAL_MCU_RTC_TIME){
        return HAL_RTC_STATUS_ERROR_PORT;
    }

    if ((g_rtc_context[rtc_timer_port].running_status == HAL_RTC_RUNNING) || (g_rtc_context[rtc_timer_port].has_initilized == true)) {
        return HAL_RTC_STATUS_ERROR;
    }
#ifdef HAL_SLEEP_MANAGER_ENABLED
    spm_control_mtcmos(SPM_MTCMOS_RTCSYS, SPM_MTCMOS_PWR_ENABLE);
#endif
    /*set structure to 0 */
    memset(&g_rtc_context[rtc_timer_port], 0, sizeof(rtc_context_t));
    if(rtc_timer_port != HAL_RTC_TIMER_2){
        rtc_base->rtc_config[rtc_timer_port].rtc_con.field.SW_CG0 = 1;
        rtc_base->rtc_t_irqmask0.word    &= ~(1 << rtc_timer_port); //RISCV IRQ enable
        rtc_base->rtc_t_wakeupmask0.word &= ~(1 << rtc_timer_port); //RISCV wakeup enable
        /*disable interrutp*/
        rtc_base->rtc_config[rtc_timer_port].rtc_irq_en.field.IRQEN0 = 0;
    }else{
        rtc_base->rtc_ao_config.rtc_con.field.SW_CG0 = 1;
        rtc_base->rtc_ao_t_irqmask0.word    &= ~(1); //RISCV IRQ enable
        rtc_base->rtc_ao_t_wakeupmask0.word &= ~(1); //RISCV wakeup enable
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
    if(rtc_timer_port == HAL_MCU_RTC_TIME){
        return HAL_RTC_STATUS_ERROR_PORT;
    }
    if (g_rtc_context[rtc_timer_port].running_status == HAL_RTC_RUNNING) {
        return HAL_RTC_STATUS_ERROR;
    }
        /* set structure to 0 */
    memset(&g_rtc_context[rtc_timer_port], 0, sizeof(rtc_context_t));

    /* set flag indicate this port has deinitlized */
    g_rtc_context[rtc_timer_port].has_initilized = false;

    rtc_base->rtc_t_irqmask0.word  |= (1 << rtc_timer_port); //CM4 IRQ disable
    rtc_reset_default_timer(rtc_timer_port);
#ifdef HAL_SLEEP_MANAGER_ENABLED
    spm_control_mtcmos(SPM_MTCMOS_RTCSYS, SPM_MTCMOS_PWR_DISABLE);
#endif

#ifdef RTC_DEBUG_LOG
    log_hal_msgid_info("[RTC%d] deinit OK\r\n", 1, (int)rtc_timer_port);
#endif
    return HAL_RTC_STATUS_OK;
}
hal_rtc_status_t hal_rtc_enable_time(void){
    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    if(g_rtc_context[HAL_MCU_RTC_TIME].has_initilized == false) {
        memset(&sw_rtc_context, 0, sizeof(sw_rtc_context_t));
        if(HAL_MCU_RTC_TIME == 2){
            rtc_base->rtc_ao_config.rtc_con.field.SW_CG0 = 0;  /* enable clock */
            rtc_base->rtc_ao_t_irqmask0.word    &= ~(1); //CM4 IRQ enable
            rtc_base->rtc_ao_t_wakeupmask0.word &= ~(1); //CM4 wakeup enable
            rtc_base->rtc_ao_config.rtc_clk.field.CLK0 =  RTC_CLOCK_32KHZ; /* clk*/
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
            rtc_base->rtc_config[HAL_MCU_RTC_TIME].rtc_con.field.SW_CG0 = 0;  /* enable clock */
            rtc_base->rtc_t_irqmask0.word    &= ~(1 << HAL_MCU_RTC_TIME); //CM4 IRQ enable
            rtc_base->rtc_t_wakeupmask0.word &= ~(1 << HAL_MCU_RTC_TIME); //CM4 wakeup enable
            rtc_base->rtc_config[HAL_MCU_RTC_TIME].rtc_clk.field.CLK0 = RTC_CLOCK_32KHZ; /* clk*/
            rtc_base->rtc_config[HAL_MCU_RTC_TIME].rtc_con.field.MODE0 = 2; //FREERUN_I MODE
            rtc_base->rtc_config[HAL_MCU_RTC_TIME].rtc_clr.word = 1; /* clear counter value */
            while (!(rtc_base->rtc_t_clrsta.word & (1 << HAL_MCU_RTC_TIME)));
            rtc_base->rtc_config[HAL_MCU_RTC_TIME].rtc_irq_ack.word = 1; /* clear interrupt status */
            rtc_base->rtc_config[HAL_MCU_RTC_TIME].rtc_compare.word = 0xFFFFFFFF;       /* set overflow IRQ */
            while (!(rtc_base->rtc_t_wcompsta.word  & (1 << HAL_MCU_RTC_TIME)));
            rtc_base->rtc_config[HAL_MCU_RTC_TIME].rtc_irq_en.field.IRQEN0 = 1;  /* enable interrupt */
            rtc_base->rtc_config[HAL_MCU_RTC_TIME].rtc_con.field.EN0 = 1;  /* enable */
        }
        g_rtc_context[HAL_MCU_RTC_TIME].callback_context.callback  = (hal_rtc_time_callback_t)sw_rtc_callback;
        sw_rtc = SW_RTC_NOT_USER;
        g_rtc_context[HAL_MCU_RTC_TIME].callback_context.user_data = &sw_rtc;
        rtc_nvic_register();
        g_rtc_context[HAL_MCU_RTC_TIME].has_initilized = true;
    }
    hal_nvic_restore_interrupt_mask(mask);
    return HAL_RTC_STATUS_OK;
}

hal_rtc_status_t hal_rtc_disable_time(void){
    
    if(getKey(heap) != -1){
        return HAL_RTC_STATUS_OK;
    }
    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    if(g_rtc_context[HAL_MCU_RTC_TIME].has_initilized == true) {
        freeMinHeap(heap);
        sw_rtc_context.creat_heap = false;
        memset(&g_rtc_context[HAL_MCU_RTC_TIME], 0, sizeof(rtc_context_t));
        memset(&sw_rtc_context, 0, sizeof(sw_rtc_context_t));
        rtc_reset_default_timer(HAL_MCU_RTC_TIME);
        g_rtc_context[HAL_MCU_RTC_TIME].has_initilized = false;
    }
    hal_nvic_restore_interrupt_mask(mask);
    return HAL_RTC_STATUS_OK;
}

hal_rtc_status_t hal_rtc_alarm_get_handle(uint32_t *handle)
{
    uint32_t i, mask;
    if(g_rtc_context[HAL_MCU_RTC_TIME].has_initilized == false) {
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
    sw_rtc_context.timer_count = rtc_get_current(HAL_MCU_RTC_TIME);
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
    return rtc_ms_change_time(time,time0,remain_time);
}

uint32_t hal_rtc_get_current(hal_rtc_timer_port_t port){
    if(g_rtc_context[HAL_MCU_RTC_TIME].has_initilized == false) {
        hal_rtc_enable_time();
    }
    return rtc_get_current(port);
}

hal_rtc_status_t hal_rtc_init(void)
{
#if !defined(AIR_DOWNLOAD_AGENT) && !defined(CONFIG_MCUBOOT)
    rtc_init_32k();

#if defined(AIR_SYS32K_CLOCK_SOURCE_XOSC)
    hal_rtc_switch_32k_source(HAL_RTC_OSC32K_XOSC_MODE);
#elif defined(AIR_SYS32K_CLOCK_SOURCE_DCXO)
    hal_rtc_switch_32k_source(HAL_RTC_OSC32K_DCXO_MODE);
#elif !defined(RTC_HQA_ENABLE)
    hal_rtc_switch_32k_source(HAL_RTC_OSC32K_EOSC_MODE);
#endif

#ifdef RTC_HQA_ENABLE
    hal_gpio_data_t gpio_data_0;
    hal_gpio_data_t gpio_data_1;
    hal_pinmux_set_function(RTC_HQA_32K_SWITCH_PIN_0, 0);
    hal_gpio_set_direction(RTC_HQA_32K_SWITCH_PIN_0, 0);
    hal_gpio_pull_up(RTC_HQA_32K_SWITCH_PIN_0);
    hal_pinmux_set_function(RTC_HQA_32K_SWITCH_PIN_1, 0);
    hal_gpio_set_direction(RTC_HQA_32K_SWITCH_PIN_1, 0);
    hal_gpio_pull_up(RTC_HQA_32K_SWITCH_PIN_1);

    hal_gpio_get_input(RTC_HQA_32K_SWITCH_PIN_0, &gpio_data_0);
    hal_gpio_get_input(RTC_HQA_32K_SWITCH_PIN_1, &gpio_data_1);
    uint32_t sel_32k = (gpio_data_0| (gpio_data_1 << 1)) & 0x3;
    switch(sel_32k) {
    case 0x00:
    case 0x03://eosc32k
        hal_rtc_switch_32k_source(HAL_RTC_OSC32K_EOSC_MODE);
        break;
    case 0x01:
        hal_rtc_switch_32k_source(HAL_RTC_OSC32K_XOSC_MODE);
        break;
    case 0x02:
        hal_rtc_switch_32k_source(HAL_RTC_OSC32K_DCXO_MODE);
        break;
    }

#endif

    dump_rtc_registers(NULL);

    hal_gpt_delay_ms(1);
#endif
    return HAL_RTC_STATUS_OK;
}

hal_rtc_status_t hal_rtc_get_f32k_frequency(uint32_t *frequency)
{
    if (frequency) {
        *frequency = rtc_get_f32k_frequency();
        return HAL_RTC_STATUS_OK;
    } else {
        return HAL_RTC_STATUS_ERROR;
    }
}

uint32_t hal_rtc_measure_32k_with_windows(hal_rtc_osc32k_mode_t osc32k_mode, uint32_t winset)
{
    uint32_t ref_clk[] = {EOSC_F32K, DCXO_F32K, XOSC_F32K, RTC_CK};
    return rtc_measure_32k_with_windows(ref_clk[osc32k_mode], winset);
}

/**
 * @brief Save data to the RTC spare register.
 *
 * This function allows saving user-defined data to the RTC spare registers. The data is saved starting
 * from a specified offset. The function checks for valid input parameters and ensures that the write operation
 * does not exceed the maximum allowed backup byte number.
 *
 * @param[in] offset The offset within the RTC spare registers where the data write should begin.
 * @param[in] buf Pointer to the buffer containing the data to be written to the RTC spare registers.
 * @param[in] len The length of the data to be written, in bytes.
 *
 * @return hal_rtc_status_t Returns HAL_RTC_STATUS_OK if the data was successfully written,
 *         otherwise returns HAL_RTC_STATUS_ERROR if the input parameters are invalid or the write operation
 *         would exceed the maximum backup byte size.
 */
hal_rtc_status_t hal_rtc_set_data(uint16_t offset, const char *buf, uint16_t len)
{
    if (buf == NULL || len == 0 || (offset + len) > HAL_RTC_BACKUP_BYTE_NUM_MAX) {
        return HAL_RTC_STATUS_ERROR;
    }

    rtc_set_retention_regs(offset, (uint8_t *)buf, len);

    return HAL_RTC_STATUS_OK;
}

/**
 * @brief Retrieve data from the RTC spare register.
 *
 * This function reads user-defined data from the RTC spare registers starting from a specified offset.
 * It checks for valid input parameters and ensures that the read operation does not exceed the maximum
 * allowed backup byte number.
 *
 * @param[in] offset The offset within the RTC spare registers from where the data read should begin.
 * @param[out] buf Pointer to the buffer where the read data will be stored.
 * @param[in] len The length of the data to be read, in bytes.
 *
 * @return hal_rtc_status_t Returns HAL_RTC_STATUS_OK if the data was successfully read,
 *         otherwise returns HAL_RTC_STATUS_ERROR if the input parameters are invalid or the read operation
 *         would exceed the maximum backup byte size.
 */
hal_rtc_status_t hal_rtc_get_data(uint16_t offset, char *buf, uint16_t len)
{
    if (buf == NULL || len == 0 || (offset + len) > HAL_RTC_BACKUP_BYTE_NUM_MAX) {
        return HAL_RTC_STATUS_ERROR;
    }

    rtc_get_retention_regs(offset, (uint8_t *)buf, len);

    return HAL_RTC_STATUS_OK;
}

hal_rtc_status_t hal_rtc_clear_data(uint16_t offset, uint16_t len)
{
    uint8_t buf[HAL_RTC_BACKUP_BYTE_NUM_MAX] = {0};

    if (len == 0 || (offset + len) > HAL_RTC_BACKUP_BYTE_NUM_MAX) {
        return HAL_RTC_STATUS_ERROR;
    }

    rtc_set_retention_regs(offset, (uint8_t *)buf, len);

    return HAL_RTC_STATUS_OK;
}

#endif //HAL_RTC_MODULE_ENABLED


