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

// #if defined()

/* Includes ------------------------------------------------------------------*/

#include "sys_init.h"
#include "rv_application.h"
#include "rv_hid_app.h"


#include "hal_spm.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_internal.h"
#include "hal_gpt_internal.h"
#include "rv_ccni.h"

#ifdef AIR_ONLINE_SWLA_ENABLE
#include "swla.h"
#endif


log_create_module(rv_main, PRINT_LEVEL_INFO);


/* Private define ------------------------------------------------------------*/
#define MAIN_LOOP_PRINT_INTERVAL 5000000


/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t ref_time = 0;
/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

bool main__check_time_passed(uint32_t ref_time, uint32_t duration)
{
    uint32_t curr_time;
    uint32_t time_delta;

    GPT_GET_FREE_RUN_COUNT_US(curr_time);
    hal_gpt_get_duration_count(ref_time, curr_time, &time_delta);

    if( time_delta >= duration){
        return true;
    }
    else {
        return false;
    }
}

void main__sleep_process()
{
    uint32_t irq_mask;
    /* enter sleep flow */
    hal_nvic_save_and_set_interrupt_mask(&irq_mask);
    SWLA_START(label_sleep);
    hal_sleep_manager_riscv_sleep_routine();
    SWLA_STOP(label_sleep);
    hal_nvic_restore_interrupt_mask(irq_mask);

#ifdef AIR_ONLINE_SWLA_ENABLE
    /* No RTOS project, need call tx hook function */
    OnlineSwlaPendableFunction();
#endif
}

int main(int argc, char **argv)
{
    system_init();
    LOG_MSGID_I(rv_main, "================ iBEX Main =============== ", 0);

    rv_ccni__init();
    rv_hid_app__init();

    while (1)
    {
        if (main__check_time_passed(ref_time , MAIN_LOOP_PRINT_INTERVAL) == true){
            hal_gpt_get_free_run_count( HAL_GPT_CLOCK_SOURCE_1M , &ref_time );
            LOG_MSGID_I(rv_main, " RISC-V Main Loop,  ref_time = %d ", 1, ref_time);
        }

        DBG_PING_L(DBG_SIGNAL_MAIN_LOOP);
        //main__sleep_process();
        DBG_PING_H(DBG_SIGNAL_MAIN_LOOP);
    }
    return 0;
}

// #endif /*  */
