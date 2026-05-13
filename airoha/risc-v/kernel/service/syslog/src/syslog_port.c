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
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
 * RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
 * TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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

/* Includes ------------------------------------------------------------------*/
#include "syslog.h"
#include "hal_nvic.h"
#include "assert.h"
#include "hal_hw_semaphore.h"
#ifdef AIR_BYPASS_SYSLOG_WITH_LOG_FLOW_ENABLE
#include "memory_attribute.h"
#include "hal_cross_core_config.h"
#endif

extern int32_t hal_nvic_query_exception_number(void);
extern hal_hw_semaphore_status_t hw_semaphore_take_special(hal_hw_semaphore_id_t id);
extern hal_hw_semaphore_status_t hw_semaphore_give_special(hal_hw_semaphore_id_t id);
bool syslog_port_check_in_isr_handler(void){
#ifdef AIR_DISABLE_IRQ_LOG_ENABLE
    if(hal_nvic_query_exception_number() != 0)
    {
        return true;
    }else{
        return false;
    }
#else
    return false;
#endif
}

void log_hw_semaphore_take(hal_hw_semaphore_id_t hw_sem_id,uint32_t *mask)
{

    /* Add hw semaphore to avoid multi-core access */
    while (1) {
#ifndef AIR_DISABLE_IRQ_LOG_ENABLE
        hal_nvic_save_and_set_interrupt_mask(mask);
#endif
        if (hw_semaphore_take_special(hw_sem_id) == HAL_HW_SEMAPHORE_STATUS_OK) {
            break;
        }
#ifndef AIR_DISABLE_IRQ_LOG_ENABLE
        hal_nvic_restore_interrupt_mask(*mask);
#endif
    }

}

void log_hw_semaphore_give(hal_hw_semaphore_id_t hw_sem_id,uint32_t mask)
{
    if (HAL_HW_SEMAPHORE_STATUS_OK != hw_semaphore_give_special(hw_sem_id)) {
        assert(0);
    }

#ifndef AIR_DISABLE_IRQ_LOG_ENABLE
    hal_nvic_restore_interrupt_mask(mask);
#endif
}



#ifdef AIR_BYPASS_SYSLOG_WITH_LOG_FLOW_ENABLE

ATTR_TEXT_IN_TCM int exception_get_disable_all_log_flag(void)
{
    return (int)ccm_disable_all_log[0];
}
#endif