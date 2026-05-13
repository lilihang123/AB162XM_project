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

// #if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stdint.h"
#include "syslog.h"
#include "hal_gpt.h"
#include "sys_init.h"
#include "rv_application.h"
#include "riscv_ccni.h"
#include "riscv_peripheral_sampling.h"
#include "riscv_hid_express.h"
#include "pka.h"
#include "hal_nvic.h"
#include "hal_spm.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_internal.h"
#include "riscv_game_controller_key.h"
#include "riscv_joystick_and_trigger.h"
#ifdef AIR_ONLINE_SWLA_ENABLE
#include "swla.h"
#endif

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define thisMODULE iMain
#define thisMOD    "iMain"
log_create_module(riscv_m, PRINT_LEVEL_INFO);

/* Private variables ---------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
int timeout_counter = 0;

/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
extern void hid_express_gaming_debug();

int main(int argc, char **argv)
{
    system_init();
    LOG_MSGID_I(riscv_m, "================ iBEX Main =============== ", 0);
    // print_feature_info();
    
    peripheral_sampling_init();
    riscv_app_ccin_init();

    extern void rv_sleep_lock_request(uint32_t lock);
    rv_sleep_lock_request(true);

    while (1)
    {
        uint32_t irq_mask;

        #if defined(AIR_DEBUG_POLLING_LOG)
        peripheral_sampling_debug_print();
        hid_express_debug_print();
        #endif

        //DBG_PING_L(DBG_SIGNAL_MAIN_LOOP);
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
        //DBG_PING_H(DBG_SIGNAL_MAIN_LOOP);
    }
    return 0;

}

// #endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */
