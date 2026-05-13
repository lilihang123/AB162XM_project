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

#if defined(HAL_SLEEP_MANAGER_ENABLED)
/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stdint.h"
#include "syslog.h"

#include "hal_rtc.h"
#include "hal_spm.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_internal.h"
// #define  sleep_rtc

#if sleep_rtc
uint32_t  sleep_sw_gpt_handle_rtc;
void hal_sleep_manager_sw_gpt_callback_rtc(void);


uint32_t hal_sleep_manager_set_sleep_time_rtc(uint32_t sleep_time_ms)
{
    hal_rtc_status_t    ret_status;
     LOG_MSGID_I(common,"[IBEX] Create RTC timer\r\n", 0);
    //ret_status = hal_rtc_enable_time();
    //printk("[rtc][enable]ret_status=%d \r\n", ret_status);

    //ret_status = hal_rtc_alarm_get_handle(&sleep_sw_gpt_handle_rtc);
    //printk("[Get][timer]ret_status=%d \r\n", ret_status);

    //hal_gpt_sw_stop_timer_ms(sleep_sw_gpt_handle); /* hal_gpt_sw_start_timer_ms clk souce = 32k, fpga no 32k */
    //ret_status = hal_gpt_sw_start_timer_ms(sleep_sw_gpt_handle, sleep_time_ms, (hal_gpt_callback_t)hal_sleep_manager_sw_gpt_callback, NULL);
    
    hal_rtc_stop_alarm(sleep_sw_gpt_handle_rtc); /* hal_gpt_sw_start_timer_ms clk souce = 32M*/
    ret_status = hal_rtc_set_alarm_ms(sleep_sw_gpt_handle_rtc, sleep_time_ms, (hal_rtc_time_callback_t)hal_sleep_manager_sw_gpt_callback_rtc, NULL);
    
    if (ret_status != HAL_RTC_STATUS_OK) {
        LOG_MSGID_I(common,"ERROR : Deep Sleep GPT Start Fail %d", 1, ret_status);
        return 0;
    }

    return 1;
}


void hal_sleep_manager_sw_gpt_callback_rtc()
{   
    //*SPM_TOP_STATE_STATUS = 0xA0;
    LOG_MSGID_I(common,"[IBEX] hal_sleep_manager_sw_gpt_callback_rtc\r\n", 0);
    //hal_gpt_sw_stop_timer_ms(sleep_sw_gpt_handle); /* stop timer clear gpt irq */
    hal_rtc_stop_alarm(sleep_sw_gpt_handle_rtc); /* stop timer clear gpt irq */

    hal_sleep_manager_set_sleep_time_rtc(2000);
    //hal_sleep_manager_set_sleep_time(10000);
    //*SPM_TOP_STATE_STATUS = 0xA1;
}
#endif

uint8_t hal_sleep_manager_set_sleep_handle(const char *handle_name)
{
#ifndef AIR_SLEEP_MANAGER_LIGHT_MODE_ENABLE
    uint8_t index;
    index = sleep_management_get_lock_handle(handle_name);
#else
    uint8_t index = 0;
#endif
    return index;
}

hal_sleep_manager_status_t hal_sleep_manager_lock_sleep(uint8_t handle_index)
{
#ifndef AIR_SLEEP_MANAGER_LIGHT_MODE_ENABLE
    sleep_management_lock_sleep(LOCK_SLEEP, handle_index);
#endif
    return HAL_SLEEP_MANAGER_OK;
}

hal_sleep_manager_status_t hal_sleep_manager_unlock_sleep(uint8_t handle_index)
{
#ifndef AIR_SLEEP_MANAGER_LIGHT_MODE_ENABLE
    sleep_management_lock_sleep(UNLOCK_SLEEP, handle_index);
#endif
    return HAL_SLEEP_MANAGER_OK;
}

hal_sleep_manager_status_t hal_sleep_manager_release_sleep_handle(uint8_t handle_index)
{
#ifndef AIR_SLEEP_MANAGER_LIGHT_MODE_ENABLE
    if (hal_sleep_manager_get_lock_status() & (1 << handle_index)) {
        LOG_MSGID_E(common,"handle %d is currently holding a lock, cannot release\n", 1, handle_index);
        return HAL_SLEEP_MANAGER_ERROR;
    }
    sleep_management_release_lock_handle(handle_index);
#endif
    return HAL_SLEEP_MANAGER_OK;
}

uint32_t hal_sleep_manager_get_lock_status(void)
{
#ifndef AIR_SLEEP_MANAGER_LIGHT_MODE_ENABLE
    return sleep_management_get_lock_sleep_request_info();
#else
    return 0;
#endif
}

bool hal_sleep_manager_is_sleep_locked(void)
{
#ifndef AIR_SLEEP_MANAGER_LIGHT_MODE_ENABLE
    return sleep_management_check_sleep_locks();
#else
    return false;
#endif
}

bool hal_sleep_manager_is_sleep_handle_alive(uint8_t handle_index)
{
#ifndef AIR_SLEEP_MANAGER_LIGHT_MODE_ENABLE
    return sleep_management_check_handle_status(handle_index);
#else
    return false;
#endif
}

void hal_sleep_manager_riscv_sleep_routine(void){
#ifndef AIR_SLEEP_MANAGER_LIGHT_MODE_ENABLE
    if(hal_sleep_manager_is_sleep_locked() == true){
    // if(1){
        sleep_management_enter_sleep();
    }else{
        sleep_management_enter_deep_sleep();
    }
#else
    sleep_management_enter_sleep();
#endif
}

uint8_t sleep_manager_handle;
hal_sleep_manager_status_t hal_sleep_manager_init()
{
    spm_init();

    sleep_manager_handle = hal_sleep_manager_set_sleep_handle("slp");
    // hal_sleep_manager_lock_sleep(sleep_manager_handle);

    #if sleep_rtc
    hal_rtc_status_t ret_status;
    LOG_MSGID_I(common,"[SLP] Create RTC timer\r\n", 0);
    ret_status = hal_rtc_enable_time();
    LOG_MSGID_I(common, "[SLP] RTC enable ret_status=%d \r\n", 1, ret_status);

    if (hal_rtc_alarm_get_handle(&sleep_sw_gpt_handle_rtc) != HAL_RTC_STATUS_OK) {
        LOG_MSGID_E(common, "ERROR : Extended Sleep RTC Init Fail", 0);
        return HAL_SLEEP_MANAGER_ERROR;
    }
    #endif
    return HAL_SLEEP_MANAGER_OK;
}

#endif /* HAL_SLEEP_MANAGER_ENABLED */
