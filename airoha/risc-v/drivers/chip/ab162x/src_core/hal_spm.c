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

#include "stdio.h"
#include "stdint.h"

#if defined(HAL_SLEEP_MANAGER_ENABLED)

/* Includes ------------------------------------------------------------------*/
#include "syslog.h"
#include "hal_spm.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_internal.h"

#include "hal_rtc.h"
#include "hal_nvic.h"


extern uint32_t  sleep_sw_gpt_handle_rtc;

int spm_init(void)
{
    int result = 0;

    spm_unmask_wakeup_source(HAL_SLEEP_MANAGER_WAKEUP_SOURCE_ALL);
    spm_mask_wakeup_source(HAL_SLEEP_MANAGER_WAKEUP_SOURCE_EINT);
    spm_mask_wakeup_source(HAL_SLEEP_MANAGER_WAKEUP_SOURCE_I3C0);
    spm_mask_wakeup_source(HAL_SLEEP_MANAGER_WAKEUP_SOURCE_USB_32K_RES);
    spm_mask_wakeup_source(HAL_SLEEP_MANAGER_WAKEUP_SOURCE_BT_TIMER);
    spm_mask_wakeup_source(HAL_SLEEP_MANAGER_WAKEUP_SOURCE_QDEC);
    spm_mask_wakeup_source(HAL_SLEEP_MANAGER_WAKEUP_SOURCE_RAMBOZ);
    LOG_MSGID_I(common, "[SLP] *SPM_CFG_IBEX_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n", 2,(uint32_t)SPM_CFG_IBEX_WAKEUP_SOURCE_MASK, *SPM_CFG_IBEX_WAKEUP_SOURCE_MASK);

    return (result);
}

void spm_mask_wakeup_source(uint32_t wakeup_source)
{
    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);

    if (wakeup_source == HAL_SLEEP_MANAGER_WAKEUP_SOURCE_ALL) {
        *SPM_CFG_IBEX_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    } else {
        *SPM_CFG_IBEX_WAKEUP_SOURCE_MASK |= (0x1 << wakeup_source);
    }

    hal_nvic_restore_interrupt_mask(mask);
}

void spm_unmask_wakeup_source(uint32_t wakeup_source)
{
    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);

    if (wakeup_source == HAL_SLEEP_MANAGER_WAKEUP_SOURCE_ALL) {
        *SPM_CFG_IBEX_WAKEUP_SOURCE_MASK = 0x0;
    } else {
        *SPM_CFG_IBEX_WAKEUP_SOURCE_MASK &= ~(0x1 << wakeup_source);
    }

    hal_nvic_restore_interrupt_mask(mask);
}

#if 0
void spm_dvt_test_case_deep_sleep()
{
    uint32_t mask, ret_status;
    //uint32_t spm_irq;

    //for (int i = 0; i < 53; i++) {
    //    if (hal_nvic_get_pending_irq(i) == 1) {
    //        //LOG_MSGID_I("pending_irq:%d\r\n", 1, i);
    //        LOG_MSGID_I("pending_irq:%d\r\n", i);
    //        hal_nvic_clear_pending_irq(i);
    //    }
    //}

    //*SPM_CFG_IGNORE_CPU_ACTIVE = 0x0;    //IGNORE IBEX/INFRA/CONN ACTIVE

    //hal_nvic_disable_irq(12);

    //*SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    //*SPM_CFG_INFRA_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    //*SPM_CFG_IBEX_WAKEUP_SOURCE_MASK = 0xFFFFFEFF;
    //*SPM_CFG_CONN_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    LOG_MSGID_I(common, "*SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n", 2,(uint32_t)SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, *SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK);
    LOG_MSGID_I(common, "*SPM_CFG_INFRA_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n", 2,(uint32_t)SPM_CFG_INFRA_WAKEUP_SOURCE_MASK, *SPM_CFG_INFRA_WAKEUP_SOURCE_MASK);
    LOG_MSGID_I(common, "*SPM_CFG_IBEX_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n", 2,(uint32_t)SPM_CFG_IBEX_WAKEUP_SOURCE_MASK, *SPM_CFG_IBEX_WAKEUP_SOURCE_MASK);
    LOG_MSGID_I(common, "*SPM_CFG_CONN_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n", 2,(uint32_t)SPM_CFG_CONN_WAKEUP_SOURCE_MASK, *SPM_CFG_CONN_WAKEUP_SOURCE_MASK);
    *SPM_CFG_IGNORE_CPU_ACTIVE = 0x1000100;    //IGNORE IBEX/INFRA/CONN ACTIVE
    LOG_MSGID_I(common,"*SPM_CFG_IGNORE_CPU_ACTIVE(0x%08x)=0x%08x\r\n", 2,(uint32_t)SPM_CFG_IGNORE_CPU_ACTIVE, *SPM_CFG_IGNORE_CPU_ACTIVE);
    //*IBEX_DEEP_SLEEP = 0xFFFFFFFF;
    LOG_MSGID_I(common,"*IBEX_DEEP_SLEEP(0x%08x)=0x%08x\r\n", 2, (uint32_t)IBEX_DEEP_SLEEP, *IBEX_DEEP_SLEEP);


    ret_status = hal_rtc_enable_time();
    LOG_MSGID_I(common,"[rtc][enable]ret_status=%d \r\n",1, ret_status);
#if !defined(AIR_LOGGING_ENABLE)
    (void)ret_status;    /* fix build error in cosim project */
#endif
    if (hal_rtc_alarm_get_handle(&sleep_sw_gpt_handle_rtc) != HAL_RTC_STATUS_OK) {
        LOG_MSGID_I(common,"ERROR : Extended Sleep RTC Init Fail", 0);
    }

    /* IBEX/CMSYS/CONN Ext SLP Flag */
    //*SPM_CFG_CMSYS_REQ_EXT_SLP = 0xFFFFFFFF;
    //*SPM_CFG_IBEX_REQ_EXT_SLP = 0xFFFFFFFF;
    //*SPM_CFG_CONN_REQ_EXT_SLP = 0xFFFFFFFF;

    LOG_MSGID_I(common, "*SPM_CFG_CMSYS_REQ_EXT_SLP(0x%08x)=0x%08x\r\n", 2,(uint32_t)SPM_CFG_CMSYS_REQ_EXT_SLP, *SPM_CFG_CMSYS_REQ_EXT_SLP);
    LOG_MSGID_I(common, "*SPM_CFG_IBEX_REQ_EXT_SLP(0x%08x)=0x%08x\r\n", 2,(uint32_t)SPM_CFG_IBEX_REQ_EXT_SLP, *SPM_CFG_IBEX_REQ_EXT_SLP);
    LOG_MSGID_I(common, "*SPM_CFG_CONN_REQ_EXT_SLP(0x%08x)=0x%08x\r\n", 2,(uint32_t)SPM_CFG_CONN_REQ_EXT_SLP, *SPM_CFG_CONN_REQ_EXT_SLP);
    
    LOG_MSGID_I(common, "Enter SLP\r\n",0);

    //hal_sleep_manager_set_sleep_time( 2000); //5s
    hal_sleep_manager_set_sleep_time_rtc(5000);

    //while(1);

    while(1){
        //*SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND = 0;        //for sleep test, need BT or Audio Control.
        //*SPM_TOP_STATE_STATUS = 0xE2;
        LOG_MSGID_I(common,"SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND(0x%08x)=0x%x \r\n",2, (uint32_t)SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND, *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND);
        hal_nvic_save_and_set_interrupt_mask(&mask);
        //*SPM_TOP_STATE_STATUS = 0xE3;
        *SPM_CFG_IGNORE_CPU_ACTIVE = 0x1000100; /* need to backup/restore */
        *IBEX_DEEP_SLEEP = 0xFFFFFFFF;
        LOG_MSGID_I(common,"*IBEX_DEEP_SLEEP(0x%08x)=0x%08x\r\n", 2, (uint32_t)IBEX_DEEP_SLEEP, *IBEX_DEEP_SLEEP);

        //hal_nvic_clear_pending_irq(22); //GPT_TIMER

        //sleep_management_enter_deep_sleep(0);
        //*SPM_TOP_STATE_STATUS = 0xEE;
        hal_nvic_restore_interrupt_mask(mask);
        //*SPM_TOP_STATE_STATUS = 0xEF;
        //*SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND = 0x101;    //for sleep test, need BT or Audio Control.
        //*SPM_TOP_STATE_STATUS = 0xE1;
    }
}

void sleep_control_riscv_enter_slp(bool slp_mode)
{
    uint32_t mask, ret_status;

    spm_mask_wakeup_source(HAL_SLEEP_MANAGER_WAKEUP_SOURCE_ALL);
    spm_unmask_wakeup_source(HAL_SLEEP_MANAGER_WAKEUP_SOURCE_RTC_TIMER);

    LOG_MSGID_I(common, "*SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n", 2,(uint32_t)SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, *SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK);
    LOG_MSGID_I(common, "*SPM_CFG_INFRA_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n", 2,(uint32_t)SPM_CFG_INFRA_WAKEUP_SOURCE_MASK, *SPM_CFG_INFRA_WAKEUP_SOURCE_MASK);
    LOG_MSGID_I(common, "*SPM_CFG_IBEX_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n", 2,(uint32_t)SPM_CFG_IBEX_WAKEUP_SOURCE_MASK, *SPM_CFG_IBEX_WAKEUP_SOURCE_MASK);
    LOG_MSGID_I(common, "*SPM_CFG_CONN_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n", 2,(uint32_t)SPM_CFG_CONN_WAKEUP_SOURCE_MASK, *SPM_CFG_CONN_WAKEUP_SOURCE_MASK);
    *SPM_CFG_IGNORE_CPU_ACTIVE = 0x01000000;    //IGNORE IBEX/INFRA/CONN ACTIVE
    LOG_MSGID_I(common,"*SPM_CFG_IGNORE_CPU_ACTIVE(0x%08x)=0x%08x\r\n", 2,(uint32_t)SPM_CFG_IGNORE_CPU_ACTIVE, *SPM_CFG_IGNORE_CPU_ACTIVE);
    //*IBEX_DEEP_SLEEP = 0xFFFFFFFF;
    LOG_MSGID_I(common,"*IBEX_DEEP_SLEEP(0x%08x)=0x%08x\r\n", 2, (uint32_t)IBEX_DEEP_SLEEP, *IBEX_DEEP_SLEEP);


    ret_status = hal_rtc_enable_time();
    LOG_MSGID_I(common,"[rtc][enable]ret_status=%d \r\n",1, ret_status);
#if !defined(AIR_LOGGING_ENABLE)
    (void)ret_status;    /* fix build error in cosim project */
#endif
    if (hal_rtc_alarm_get_handle(&sleep_sw_gpt_handle_rtc) != HAL_RTC_STATUS_OK) {
        LOG_MSGID_I(common,"ERROR : Extended Sleep RTC Init Fail", 0);
    }

    *SPM_CFG_IBEX_REQ_EXT_SLP = 0x1;

    LOG_MSGID_I(common, "*SPM_CFG_CMSYS_REQ_EXT_SLP(0x%08x)=0x%08x\r\n", 2,(uint32_t)SPM_CFG_CMSYS_REQ_EXT_SLP, *SPM_CFG_CMSYS_REQ_EXT_SLP);
    LOG_MSGID_I(common, "*SPM_CFG_IBEX_REQ_EXT_SLP(0x%08x)=0x%08x\r\n", 2,(uint32_t)SPM_CFG_IBEX_REQ_EXT_SLP, *SPM_CFG_IBEX_REQ_EXT_SLP);
    LOG_MSGID_I(common, "*SPM_CFG_CONN_REQ_EXT_SLP(0x%08x)=0x%08x\r\n", 2,(uint32_t)SPM_CFG_CONN_REQ_EXT_SLP, *SPM_CFG_CONN_REQ_EXT_SLP);
    
    LOG_MSGID_I(common, "Riscv Enter SLP\r\n",0);

    //hal_sleep_manager_set_sleep_time( 2000); //5s
    hal_sleep_manager_set_sleep_time_rtc(4000);

    // while(1){
        //*SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND = 0;        //for sleep test, need BT or Audio Control.
        LOG_MSGID_I(common,"SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND(0x%08x)=0x%x \r\n",2, (uint32_t)SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND, *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND);
        hal_nvic_save_and_set_interrupt_mask(&mask);
        //*SPM_TOP_STATE_STATUS = 0xE3;

        sleep_management_enter_deep_sleep();

        // *IBEX_DEEP_SLEEP = 0xFFFFFFFF;
        // LOG_MSGID_I(common,"*IBEX_DEEP_SLEEP(0x%08x)=0x%08x\r\n", 2, (uint32_t)IBEX_DEEP_SLEEP, *IBEX_DEEP_SLEEP);

        //hal_nvic_clear_pending_irq(22); //GPT_TIMER
        //*SPM_TOP_STATE_STATUS = 0xEE;
        hal_nvic_restore_interrupt_mask(mask);
        //*SPM_TOP_STATE_STATUS = 0xEF;
        //*SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND = 0x101;    //for sleep test, need BT or Audio Control.
        //*SPM_TOP_STATE_STATUS = 0xE1;
    // }
}

#endif

#ifdef AIR_RISCV_COREMARK_ENABLE
void race_sleep_control_enter_coremark(void)
{
  
    LOG_MSGID_I(riscv_m, "Enter Coremark !!!", 0);

    // /* IBEX DEEP SLEEP */
    // *RISCV_DEEP_SLEEP = 0xFFFFFFFF;
    // LOG_MSGID_I("*RISCV_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)RISCV_DEEP_SLEEP, *RISCV_DEEP_SLEEP);

    //hal_sleep_manager_set_sleep_time(5000000); //5s
    // hal_sleep_manager_set_sleep_time_rtc(5000); //5s
    while(1){

        //hal_nvic_clear_pending_irq(22); //GPT_TIMER

        // __asm volatile("csrrc x0, mstatus, 0x8"); // disable interrupt
        LOG_MSGID_I(riscv_m, "[SLP] RiscV Enter IDLE !!!", 0);

        for (int i = 0; i < IRQ_NUMBER_MAX; i++) {
            
            if(i != 28){ /* only ccni enable, BTD-3523 */
                hal_nvic_disable_irq(i);
            }
            // if (hal_nvic_get_pending_irq(i) == 1) {
              // printf("pending_irq:%d\r\n", i);
                // hal_nvic_clear_pending_irq(i);
                // *SPM_CFG_SW_DBG_STATE_STATUS = i;
            // }
        }

        while(1){
            // hal_sleep_manager_enter_sleep_mode(HAL_SLEEP_MODE_IDLE);
            sleep_management_enter_deep_sleep();
        }
        while(1);
    }
}
#endif

#endif /* HAL_SLEEP_MANAGER_ENABLED */
