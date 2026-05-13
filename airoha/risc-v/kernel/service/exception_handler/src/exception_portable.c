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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include "stdio.h"
#include "stdint.h"
#include <stdbool.h>
#include "exception_portable.h"
#include "assert.h"
#include "hal_hw_semaphore.h"
#include "hal_ccni.h"
#include "hal_gpt.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define EXCEPTION_HW_SEMAPHORE                  HW_SEMAPHORE_EXCEPTION
#define EXCEPTION_EVENT_TO_MASTER               IRQGEN_RISCV2MCU_EVENT16
#define EXCEPTION_EVENT_FROM_MASTER             IRQGEN_MCU2RISCV_EVENT16

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: CCNI_DEF_HANDLER
 *
 * Description:
 *   When master send exception ccni event, it will call this function.
 *
 ****************************************************************************/
 
void CCNI_DEF_HANDLER(16)(hal_ccni_event_t event, hal_ccni_message_t *msg)
{
    static volatile bool exception_triggered_flag = true;
    ATTR_LOG_STRING exp[] = "Triggered";
    ATTR_LOG_STRING file[] = __FILE__;
    light_assert(exp, file, __LINE__);
    (void) event;
    (void) msg;
    (void) exception_triggered_flag;
}

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: exc_port_alert_other_cores
 *
 * Description:
 *   Send ccni to master to handle exception.
 *
 ****************************************************************************/

void exc_port_alert_other_cores(void)
{
    /* just for fixing coverity issue */
    hal_ccni_set_event(EXCEPTION_EVENT_TO_MASTER, NULL);
}

/****************************************************************************
 * Name: exc_port_gpt_get_free_run_1M_count
 *
 * Description:
 *   Get 1M gpt free run count.
 *
 ****************************************************************************/

void exc_port_gpt_get_free_run_1M_count(uint32_t *count)
{
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, count);
}

/****************************************************************************
 * Name: exc_port_gpt_get_free_run_32K_count
 *
 * Description:
 *   Get 32K gpt free run count.
 *
 ****************************************************************************/

void exc_port_gpt_get_free_run_32K_count(uint32_t *count)
{
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, count);
}

/****************************************************************************
 * Name: exc_port_core_status_update
 *
 * Description:
 *   Update exception core status.
 *
 ****************************************************************************/

void exc_port_core_status_update(void)
{
    return;
}

/****************************************************************************
 * Name: exc_port_ccni_clear_event
 *
 * Description:
 *   Clear event from master.
 *
 ****************************************************************************/

int exc_port_ccni_clear_event(void)
{
    return hal_ccni_clear_event(EXCEPTION_EVENT_FROM_MASTER);
}

/****************************************************************************
 * Name: exc_port_ccni_query_event_status
 *
 * Description:
 *   Query the event status from the master core.
 *
 ****************************************************************************/

int exc_port_ccni_query_event_status(void)
{
    uint32_t master_status = HAL_CCNI_EVENT_STATUS_IDLE;
    while (master_status != HAL_CCNI_EVENT_STATUS_BUSY) {
        hal_ccni_query_event_status(EXCEPTION_EVENT_FROM_MASTER, &master_status);
    }
    return 0;

}


