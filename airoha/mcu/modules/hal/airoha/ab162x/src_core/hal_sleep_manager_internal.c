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

#include "hal_sleep_manager.h"
#include "hal_sleep_manager_internal.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef HAL_SLEEP_MANAGER_ENABLED
#include <stdio.h>
#include <string.h>
#include "hal_log.h"
#include "memory_attribute.h"
#include "hal_nvic.h"
#include "hal_nvic_internal.h"
#include "soc.h"
#include "hal_pmu.h"
#include "hal_rtc_internal.h"
#if defined(AIR_LOGGING_ENABLE)
#include "air_logging.h"
#endif

#ifndef __UBL__
#include "assert.h"
#else
#define assert(expr) log_hal_msgid_error("assert\r\n", 0)
#endif

#include "hal_cache_internal.h"
#include "hal_flash_sf.h"
#include "hal_clock_internal.h"
#include "hal_gpt.h"
#include "hal_mpu_internal.h"
#include "hal_clock.h"
#include "hal_clock_platform.h"

#if defined(AIR_PD_DOMAIN_CONTROL_ENABLE)
#include "pd_domain_control.h"
#endif /* AIR_PD_DOMAIN_CONTROL_ENABLE */

#if defined(AIR_RAM_BLOCKS_CONTROL_ENABLE)
#include "ram_blocks_control.h"
#endif /* AIR_RAM_BLOCKS_CONTROL_ENABLE */

#ifndef log_debug
#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
extern uint32_t eint_get_event(uint32_t index);
#define log_debug(_message,...) printf(_message, ##__VA_ARGS__)
#else
#define log_debug(_message,...)
#endif
#endif

#define SKIP_UART_BACKUP_RESTORE 0

#ifdef AIR_LOGGING_ENABLE
log_create_module(SLEEP_MANAGER, PRINT_LEVEL_INFO);
#define SLEEP_MANAGER_LOG_E(fmt,cnt,arg...)          LOG_E(SLEEP_MANAGER,fmt,cnt,##arg)
#define SLEEP_MANAGER_MSGID_I(fmt,cnt,arg...)        LOG_MSGID_I(SLEEP_MANAGER,fmt,cnt,##arg)
#define SLEEP_MANAGER_MSGID_W(fmt,cnt,arg...)        LOG_MSGID_W(SLEEP_MANAGER,fmt,cnt,##arg)
#define SLEEP_MANAGER_MSGID_E(fmt,cnt,arg...)        LOG_MSGID_E(SLEEP_MANAGER,fmt,cnt,##arg)
#else
#define SLEEP_MANAGER_LOG_I(fmt,cnt,arg...)
#define SLEEP_MANAGER_LOG_W(fmt,cnt,arg...)
#define SLEEP_MANAGER_LOG_E(fmt,cnt,arg...)
#define SLEEP_MANAGER_MSGID_I(fmt,cnt,arg...)
#define SLEEP_MANAGER_MSGID_W(fmt,cnt,arg...)
#define SLEEP_MANAGER_MSGID_E(fmt,cnt,arg...)
#endif


#ifndef SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
static sleep_management_handle_t sleep_management_handle = {
    .lock_sleep_request = 0,
    .user_handle_resource = 0,
    .user_handle_count = 0
};
static sleep_management_extslp_handle_t sleep_management_extslp_handle = {
    .lock_extslp_request = 0,
    .user_handle_resource = 0,
    .user_handle_count = 0
};
static sleep_management_idle_handle_t sleep_management_idle_handle = {
    .lock_idle_request = 0,
    .user_handle_resource = 0,
    .user_handle_count = 0
};
#endif

static sleep_management_suspend_callback_func_t    suspend_ns_callback_func_table               [SLEEP_BACKUP_RESTORE_MODULE_MAX];
static sleep_management_suspend_callback_func_t    suspend_secure_callback_func_table           [SLEEP_BACKUP_RESTORE_MODULE_MAX];
static sleep_management_suspend_callback_func_t    suspend_all_secure_callback_func_table       [SLEEP_BACKUP_RESTORE_MODULE_MAX];
static sleep_management_suspend_callback_func_t    suspend_infra_pd_callback_func_table         [INFRA_PD_BACKUP_RESTORE_MODULE_MAX];

static sleep_management_resume_callback_func_t     resume_ns_callback_func_table                [SLEEP_BACKUP_RESTORE_MODULE_MAX];
static sleep_management_resume_callback_func_t     resume_secure_callback_func_table            [SLEEP_BACKUP_RESTORE_MODULE_MAX];
static sleep_management_resume_callback_func_t     resume_all_secure_callback_func_table        [SLEEP_BACKUP_RESTORE_MODULE_MAX];
static sleep_management_resume_callback_func_t     resume_infra_pd_callback_func_table          [INFRA_PD_BACKUP_RESTORE_MODULE_MAX];

static sleep_management_suspend_callback_func_t    suspend_user_ns_callback_func_table          [SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX];
static sleep_management_suspend_callback_func_t    suspend_user_secure_callback_func_table      [SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX];
static sleep_management_suspend_callback_func_t    suspend_user_all_secure_callback_func_table  [SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX];
static sleep_management_suspend_callback_func_t    suspend_user_infra_pd_callback_func_table    [SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX];

static sleep_management_resume_callback_func_t     resume_user_ns_callback_func_table           [SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX];
static sleep_management_resume_callback_func_t     resume_user_secure_callback_func_table       [SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX];
static sleep_management_resume_callback_func_t     resume_user_all_secure_callback_func_table   [SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX];
static sleep_management_resume_callback_func_t     resume_user_infra_pd_callback_func_table     [SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX];

static uint32_t suspend_user_register_count_ns = 0, resume_user_register_count_ns = 0;
static uint32_t suspend_user_register_count_in_secure = 0, resume_user_register_count_in_secure = 0;
static uint32_t suspend_user_all_secure_register_count = 0, resume_user_all_secure_register_count = 0;
static uint32_t suspend_user_infra_pd_register_count = 0, resume_user_infra_pd_register_count = 0;

ATTR_ZIDATA_IN_TCM volatile uint32_t wakeup_source_status;
ATTR_ZIDATA_IN_TCM volatile uint32_t temp_reg;
//ATTR_ZIDATA_IN_TCM volatile CMCFG_BOOT_VECTOR0_T Vector0_backup;
ATTR_ZIDATA_IN_TCM volatile uint32_t Vector0_backup;
ATTR_ZIDATA_IN_TCM volatile uint32_t origin_msp_bak_reg, origin_psp_bak_reg, backup_return_address;
ATTR_ZIDATA_IN_TCM volatile uint32_t origin_msplim_bak_reg, origin_psplim_bak_reg;
ATTR_ZIDATA_IN_TCM volatile CPU_CORE_BAKEUP_REG_T  cpu_core_reg ;
ATTR_ZIDATA_IN_TCM volatile nvic_sleep_backup_register_t nvic_backup_register;
ATTR_ZIDATA_IN_TCM volatile FPU_BAKEUP_REG_T  fpu_reg;
ATTR_ZIDATA_IN_TCM volatile CM33_SYS_CTRL_BAKEUP_REG_T  cm33_sys_ctrl_reg;
extern ATTR_ZIDATA_IN_TCM volatile uint32_t infra_pd_force_on_status;

#if (defined (AIR_CPU_IN_SECURITY_MODE))
ATTR_ZIDATA_IN_TCM volatile uint32_t origin_msp_bak_reg_ns, origin_psp_bak_reg_ns, backup_return_address_ns;
ATTR_ZIDATA_IN_TCM volatile uint32_t origin_msplim_bak_reg_ns, origin_psplim_bak_reg_ns;
ATTR_ZIDATA_IN_TCM volatile CPU_CORE_BAKEUP_REG_NS_T  cpu_core_reg_ns;
ATTR_ZIDATA_IN_TCM volatile nvic_sleep_backup_register_ns_t nvic_backup_register_ns;
ATTR_ZIDATA_IN_TCM volatile  CM33_SYS_CTRL_BAKEUP_REG_NS_T cm33_sys_ctrl_reg_ns;
#endif
ATTR_ZIDATA_IN_TCM volatile uint32_t sysram_illegal_access_con_0, sysram_illegal_access_con_1;

/* ATTR_ZIDATA_IN_TCM is Zero initialization data.
 * If date is no initial value, use ATTR_ZIDATA_IN_TCM.
 * If not, use ATTR_RWDATA_IN_TCM.
 */
ATTR_ZIDATA_IN_TCM static volatile uint32_t* curr_register_addr;
ATTR_ZIDATA_IN_TCM static volatile uint32_t backup_restore_register_count;
ATTR_ZIDATA_IN_TCM static volatile ao_backup_status_t ao_backup_status[SLEEP_MANAGEMENT_AO_BACKUP_MAX];
ATTR_ZIDATA_IN_TCM static volatile uint32_t ao_backup_restore_space[AO_BACKUP_SPACE_LENGTH];
ATTR_ZIDATA_IN_TCM static volatile uint32_t infra_pd_resource_control;
ATTR_ZIDATA_IN_TCM static volatile bool infra_pd_ready_flag;
ATTR_ZIDATA_IN_TCM volatile bool slp_wakeup_dump_flag;
sleep_management_status_t sleep_management_status = {0xFFFFFFFF, 0xFFFFFFFF, 0, 0};

uint32_t nvic_test(int32_t IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((NVIC->ISPR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}
#ifdef CONFIG_SPM_LPHQA_DEBUG
extern ATTR_TEXT_IN_TCM_RETENTION void SF_DAL_DEV_Enter_DPD(void);
#endif

static bool sleep_management_sf_dpd_is_allowed = true;
static bool sleep_management_backup_restore_is_allowed = true;

void sleep_management_SF_DPD_ctrl(bool enable)
{
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sleep_management_sf_dpd_is_allowed = enable;
    hal_nvic_restore_interrupt_mask(mask);

    printk("[SLP] sleep_management_SF_DPD_ctrl: %d\r\n", sleep_management_sf_dpd_is_allowed);
}

void sleep_management_backup_restore_ctrl(bool enable)
{
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sleep_management_backup_restore_is_allowed = enable;
    hal_nvic_restore_interrupt_mask(mask);

    printk("[SLP] sleep_management_backup_restore_ctrl: %d\r\n",  sleep_management_backup_restore_is_allowed);
}

void sleep_management_init(void)
{
    /* AO backup/restore initialization */
    *AO_BACKUP_RESTORE_SPACE = (uintptr_t)ao_backup_restore_space;
    *BACKUP_FORMAT_TABLE_START = BACKUP_FORMAT_REGISTER_START;
    *FIRST_BACKUP_FORMAT_REGISTER = BACKUP_FORMAT_REGISTER_END;
    curr_register_addr = FIRST_BACKUP_FORMAT_REGISTER;
    backup_restore_register_count = 0;
    printk("[SLP] ao_backup_restore_space: 0x%x, AO_BACKUP_RESTORE_SPACE: 0x%x, AO_BACKUP_MAX_ADDR: 0x%x\r\n", (uint32_t)ao_backup_restore_space, *AO_BACKUP_RESTORE_SPACE, AO_BACKUP_MAX_ADDR);
    printk("[SLP] BACKUP_FORMAT_TABLE_START address: 0x%x, value: 0x%x\r\n", (uint32_t)BACKUP_FORMAT_TABLE_START, *BACKUP_FORMAT_TABLE_START);
    printk("[SLP] FIRST_BACKUP_FORMAT_REGISTER address: 0x%x, value: 0x%x\r\n", (uint32_t)FIRST_BACKUP_FORMAT_REGISTER, *FIRST_BACKUP_FORMAT_REGISTER);
    printk("[SLP] curr_register_addr address: 0x%x, value: 0x%x\r\n", (uint32_t)curr_register_addr, *curr_register_addr);
    printk("[SLP] backup_restore_register_count: %d\r\n", backup_restore_register_count);
    
    const struct {
        uint8_t id;
        uint32_t base;
        uint32_t end;
    } ao_configs[] = {
        { SLEEP_MANAGEMENT_AO_BACKUP_MCU_CFG,  0x422E0000, 0x422E0018 },
        { SLEEP_MANAGEMENT_AO_BACKUP_TOP_MISC, 0x42010000, 0x42010024 },
        { SLEEP_MANAGEMENT_AO_BACKUP_SPM,      0x42120000, 0x42120094 },
        { SLEEP_MANAGEMENT_AO_BACKUP_SPM_CFG,  0x42130000, 0x421300E8 },
        { SLEEP_MANAGEMENT_AO_BACKUP_GPIO,     0x420B0000, 0x420B0044 }
    };

    for (uint8_t i = 0; i < (uint8_t)(sizeof(ao_configs) / sizeof(ao_configs[0])); i++) {
        ao_backup_format_table_t reg_entry = {
            .module_base_addr = ao_configs[i].base,
            .module_end_addr = ao_configs[i].end,
            .module_backup_enable = 0x1
        };
        sleep_management_register_infra_ao_backup_restore(ao_configs[i].id, &reg_entry);
    }

    /* All INFRA_PD module default request INFRA_PD on */
    infra_pd_ready_flag = true;
    // infra_pd_resource_control = (0x1 << INFRA_PD_MODULE_MAX) - 1;
    printk("[SLP] infra_pd_resource_control: 0x%x\r\n", infra_pd_resource_control);
}

#if     defined (__GNUC__)      //GCC disable compiler optimize
__attribute__((optimize("O0")))
#elif   defined (__ICCARM__)    //IAR disable compiler optimize
#pragma optimize=none
#elif   defined (__CC_ARM)      //MDK disable compiler optimize
#pragma push
#pragma diag_suppress 1267
#pragma O0
#endif

ATTR_TEXT_IN_TCM_RETENTION void sleep_management_enter_deep_sleep(hal_sleep_mode_t mode)
{
    uint32_t irq_mask1, irq_mask2;

#ifdef SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
    printk("only enter wfi!!");
    __asm volatile("dsb");
    __asm volatile("wfi");
    __asm volatile("isb");
#else /* CM33_SLEEP_DISABLE */

    /* Set CM33 SLEEPDEEP bits */
    SCB->SCR = SCB->SCR | 0x4;

    /* Set HW_MISC_1[0]=1 (AO domain & no backup/restore RG)
     * Check if wakeup from Ext SLP mode.
     * Cache backup restore would check this flag.
     */
    TOP_MISC_CFG_1->hw_misc1_1.word |= 0x1;
    // printk("[SLP] TOP_MISC_CFG_1->hw_misc1_1(0x%08x)=0x%08x\r\n", (uint32_t)&(TOP_MISC_CFG_1->hw_misc1_1.word), TOP_MISC_CFG_1->hw_misc1_1.word);

    SPM_SET_CMSYS_SW_STATE(0x3);

    /* Set Boot Slave, (AB162X) MCU_CFG_PRI->cmcfg_boot_from_slv */
    *CMCFG_BOOT_FROM_SLV = 0x1;

    /* Peripheral driver backup callback function */
    if (sleep_management_backup_restore_is_allowed)
    {
#ifdef AIR_LIMIT_TZ_ENABLE
        sleep_management_secure_suspend_callback();
#else /* All In Secure Environment */
        sleep_management_all_secure_suspend_callback();
#endif
    }

#ifdef UART_SLEEP_TRIGGER_ENABLED
    uart_enter_sleep_config_eint();
#endif

    SPM_SET_CMSYS_SW_STATE(0x4);

    /* Backup CMSYS register */
    deep_sleep_cmsys_backup();

#if defined(AIR_RAM_BLOCKS_CONTROL_ENABLE)
    /* power down non-retention ram blocks for better power saving */
    /* Note: it must be run before pd domain off */
    ram_blocks_control_enter_extend_sleep();
#endif /* AIR_RAM_BLOCKS_CONTROL_ENABLE */

#if defined(AIR_PD_DOMAIN_CONTROL_ENABLE)
    pd_domain_control_enter_sleep(INFRA_PD_MODULE_SLEEP_MANAGER);
#endif /* AIR_PD_DOMAIN_CONTROL_ENABLE */

    /* Enable SPM IRQ and clear pending bits */
    // hal_nvic_enable_irq(SPM_IRQn);
    // hal_nvic_clear_pending_irq(SPM_IRQn);

    /* General register backup */
    __CPU_STACK_POINT_BACKUP(origin_psp_bak_reg, origin_msp_bak_reg);

#if (defined (AIR_CPU_IN_SECURITY_MODE)) /* build-in SECURE WORLD */
    __CPU_STACK_POINT_BACKUP_NS(origin_psp_bak_reg_ns, origin_msp_bak_reg_ns);
#endif

    __CPU_STACK_POINT_LIMIT_BACKUP(origin_psplim_bak_reg, origin_msplim_bak_reg);

#if (defined (AIR_CPU_IN_SECURITY_MODE))
    __CPU_STACK_POINT_LIMIT_BACKUP_NS(origin_psplim_bak_reg_ns, origin_msplim_bak_reg_ns);
#endif

    /* Backup BootVector0 Stack Address */
    Vector0_backup = *CMCFG_BOOT_VECTOR0;     //boot vector 0(boot slave stack point)

    /* Backup MSP Address */
#if (defined (__GNUC__) || defined (__ICCARM__))
    __asm volatile("push {r0-r12, lr}");
    __asm volatile("mov %0, sp" : "=r"(temp_reg));
#elif defined (__CC_ARM)
    __PUSH_CPU_REG();
    __BACKUP_SP(temp_reg);
#endif

    *CMCFG_BOOT_VECTOR0 = temp_reg;   //Current stack is psp, write psp value to VECTOR0(MSP Address)
    
    if (*SPM_CFG_CMSYS_WAKEUP_SOURCE_STA_IN_B == 0) {
        sleep_management_status.abort_sleep = 1;

        SPM_SET_CMSYS_SW_STATE(0x9);
    } else {

        SPM_SET_CMSYS_SW_STATE(0x5);

        /* Enter Deep Sleep */
        temp_reg = (uint32_t)CMCFG_BOOT_VECTOR1;     //CMCFG_BOOT_VECTOR1 Address

#ifdef HAL_CACHE_MODULE_ENABLED
        CACHE_STATUS_BACKUP();
#endif

        SPM_SET_CMSYS_SW_STATE(0x6);

        __ENTER_DEEP_SLEEP(temp_reg);
        // printk("[wakeup1]*SPM_CFG_CMSYS_WAKEUP_SOURCE_STA(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_CMSYS_WAKEUP_SOURCE_STA, *SPM_CFG_CMSYS_WAKEUP_SOURCE_STA);

#ifdef HAL_CACHE_MODULE_ENABLED
        CACHE_STATUS_RESTORE();
#endif

        /* POP CPU Reg R0-R12 */
        __POP_CPU_REG();

        SPM_SET_CMSYS_SW_STATE(0x7);

    }

    /* Get wakeup source */
    sleep_management_status.wakeup_source = *SPM_CFG_CMSYS_WAKEUP_SOURCE_STA;
    sleep_management_status.wkup_from_extslp = *SPM_CFG_SPM_CFG_DUMMY_REG_A;
    // printk("[wakeup]*SPM_CFG_CMSYS_WAKEUP_SOURCE_STA(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_CMSYS_WAKEUP_SOURCE_STA, *SPM_CFG_CMSYS_WAKEUP_SOURCE_STA);

    /* Restore MSP */
    temp_reg = (uint32_t)&origin_msp_bak_reg;
    __MSP_RESTORE(temp_reg);

    temp_reg = (uint32_t)&origin_msplim_bak_reg;
    __MSPLIM_RESTORE(temp_reg);

#if (defined (AIR_CPU_IN_SECURITY_MODE))
    /* Restore MSP_NS */
    temp_reg = (uint32_t)&origin_msp_bak_reg_ns;
    __MSP_RESTORE_NS(temp_reg);

    temp_reg = (uint32_t)&origin_msplim_bak_reg_ns;
    __MSPLIM_RESTORE_NS(temp_reg);
#endif

    /* Switch stack point to PSP */
    __SWITCH_TO_PSP_STACK_POINT();

    /* Restore PSP */
    temp_reg = (uint32_t)&origin_psp_bak_reg;
    __PSP_RESTORE(temp_reg);

    temp_reg = (uint32_t)&origin_psplim_bak_reg;
    __PSPLIM_RESTORE(temp_reg);

#if (defined (AIR_CPU_IN_SECURITY_MODE)) /* build-in secure world */
    /* Restore PSP_NS */
    temp_reg = (uint32_t)&origin_psp_bak_reg_ns;
    __PSP_RESTORE_NS(temp_reg);
    temp_reg = (uint32_t)&origin_psplim_bak_reg_ns;
    __PSPLIM_RESTORE_NS(temp_reg);
#endif

    /* Restore Core register - CONTROL */
    temp_reg = (uint32_t)&cpu_core_reg.CONTROL;
    __CPU_CORE_CONTROL_REG_RESTORE(temp_reg);

#if (defined (AIR_CPU_IN_SECURITY_MODE))
    /* Restore Core register - CONTROL_NS */
    temp_reg = (uint32_t)&cpu_core_reg_ns.CONTROL_NS;
    __CPU_CORE_CONTROL_REG_RESTORE_NS(temp_reg);
#endif

    /* Restore boot Vector */
    *CMCFG_BOOT_FROM_SLV = 0x0;    /* RG read only */
    *CMCFG_BOOT_VECTOR0 = Vector0_backup;

    /* Restore CMSYS register */
    deep_sleep_cmsys_restore();

    /* Clear CM4 Deep Sleep bits */
    //*CM33_SYSTEM_CONTROL = *CM33_SYSTEM_CONTROL & (~0x4);
    SCB->SCR = SCB->SCR & (~0x4);

    /* Clear SPM wakeup event (CMSYS pwr on information) */
    //printk("[1]*SPM_CFG_PCM_SW_INT_STATE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_PCM_SW_INT_STATE, *SPM_CFG_PCM_SW_INT_STATE);
    *SPM_CFG_PCM_SW_INT_CLEAR = 1;

    SPM_SET_CMSYS_SW_STATE(0x8);

#if defined(AIR_PD_DOMAIN_CONTROL_ENABLE)
    pd_domain_control_exit_sleep(INFRA_PD_MODULE_SLEEP_MANAGER);
#endif /* AIR_PD_DOMAIN_CONTROL_ENABLE */

    SPM_SET_CMSYS_SW_STATE(0x9);

#if defined(AIR_RAM_BLOCKS_CONTROL_ENABLE)
    /* power on non-retention ram blocks and reinit them */
    /* Note: it must be run after pd domain on */
    ram_blocks_control_exit_extend_sleep();
#endif /* AIR_RAM_BLOCKS_CONTROL_ENABLE */

    SPM_SET_CMSYS_SW_STATE(0xA);

    /* mpu restore after non-retention region re-init */
#ifdef HAL_MPU_MODULE_ENABLED
    mpu_status_restore();
#endif

    SPM_SET_CMSYS_SW_STATE(0xB);

    /* Peripheral driver restore callback function */
    if (sleep_management_backup_restore_is_allowed)
    {
#ifdef AIR_LIMIT_TZ_ENABLE
        sleep_management_secure_resume_callback();
#else /* All In Secure Environment */
        sleep_management_all_secure_resume_callback();
#endif
    }

    SPM_SET_CMSYS_SW_STATE(0xC);

    if(slp_wakeup_dump_flag){
        /* Dump debug information */
        printk("[SLP][wakeup] Ext_SLP_Flag = 0x%x", sleep_management_status.wkup_from_extslp);
        printk("[SLP][wakeup]*SPM_CFG_CMSYS_REQ_EXT_SLP(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CMSYS_REQ_EXT_SLP, *SPM_CFG_CMSYS_REQ_EXT_SLP);
        printk("[SLP][wakeup]*SPM_CFG_RISCV_REQ_EXT_SLP(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_RISCV_REQ_EXT_SLP, *SPM_CFG_RISCV_REQ_EXT_SLP);
        printk("[SLP][wakeup]*SPM_CFG_CONN_REQ_EXT_SLP(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CONN_REQ_EXT_SLP, *SPM_CFG_CONN_REQ_EXT_SLP);
        printk("[SLP][wakeup] deep sleep exit, wakeup source = 0x%08x", sleep_management_status.wakeup_source);
        hal_nvic_get_pending_irq_by_mask(&irq_mask1, &irq_mask2);
        printk("[SLP][wakeup][IRQ Pending] irq_mask[0:31]=0x%08x, irq_mask[32:63]=0x%08x\r\n", irq_mask1, irq_mask2);
    }

    *SPM_CFG_SPM_CFG_DUMMY_REG_A &= ~0x100; // clear ext slp flag bit
    
    SPM_SET_CMSYS_SW_STATE(0xD);

#endif

}

#ifndef AIR_CPU_IN_SECURITY_MODE
ATTR_NSC_TEXT void sleep_management_enter_deep_sleep_in_secure(hal_sleep_mode_t mode)
{

    sleep_management_enter_deep_sleep(HAL_SLEEP_MODE_SLEEP);
    /* SAU restore */
    sau_init();

    /* Config irq to NS world */
    for (int i = 0; i < (16 * 32); i++) {
        NVIC_SetTargetState(i);
    }
    NVIC_ClearTargetState(GPT_SEC_IRQn);
}
#endif

#if     defined (__GNUC__)
#elif   defined (__CC_ARM)
#pragma pop
#endif

/* deep_sleep_cmsys_backup need to define as inline function*/
ATTR_TEXT_IN_TCM_RETENTION void deep_sleep_cmsys_backup(void)
{
    uint32_t i;
    /* backup CPU core registers */
    /* include NS world register */
    temp_reg = (unsigned int)&cpu_core_reg;
    __CPU_CORE_REG_BACKUP(temp_reg);

#if (defined (AIR_CPU_IN_SECURITY_MODE))
    temp_reg = (unsigned int)&cpu_core_reg_ns;
    __CPU_CORE_REG_BACKUP_NS(temp_reg);
#endif

    /* NVIC backup */
    /* If LimitedTZ, must determine the security of IRQn first.
    Then backup & disable IRQn */
    nvic_backup_register.nvic_iser = NVIC->ISER[0];
    nvic_backup_register.nvic_iser1 = NVIC->ISER[1];
    nvic_backup_register.nvic_iser2 = NVIC->ISER[2];
    for (i = 0; i < SAVE_PRIORITY_GROUP; i++) {
        nvic_backup_register.nvic_ip[i] = NVIC->IPR[i];
        hal_nvic_disable_irq(i);
    }
#if (defined (AIR_CPU_IN_SECURITY_MODE))
    nvic_backup_register_ns.nvic_iser = NVIC_NS->ISER[0];
    nvic_backup_register_ns.nvic_iser1 = NVIC_NS->ISER[1];
    nvic_backup_register_ns.nvic_iser2 = NVIC_NS->ISER[2];
    for (i = 0; i < SAVE_PRIORITY_GROUP; i++) {
        nvic_backup_register_ns.nvic_ip[i] = NVIC_NS->IPR[i];
    }
#endif

    /* mpu backcp */
#ifdef HAL_MPU_MODULE_ENABLED
    mpu_status_save();
#endif

    /* fpu backup */
    fpu_reg.FPCCR = FPU->FPCCR;
    fpu_reg.FPCAR = FPU->FPCAR;

    /* CM33 system control registers backup */
    cm33_sys_ctrl_reg.ACTLR = SCnSCB->ACTLR;
    cm33_sys_ctrl_reg.VTOR = SCB->VTOR;
    cm33_sys_ctrl_reg.SCR = SCB->SCR;
    cm33_sys_ctrl_reg.CCR = SCB->CCR;

    cm33_sys_ctrl_reg.SHP[0] = SCB->SHPR[0]; /* MemMange */
    cm33_sys_ctrl_reg.SHP[1] = SCB->SHPR[1]; /* BusFault */
    cm33_sys_ctrl_reg.SHP[2] = SCB->SHPR[2]; /* UsageFault */
    cm33_sys_ctrl_reg.SHP[7] = SCB->SHPR[7]; /* SVCall */
    cm33_sys_ctrl_reg.SHP[8] = SCB->SHPR[8]; /* DebugMonitor */
    cm33_sys_ctrl_reg.SHP[10] = SCB->SHPR[10]; /* PendSV */
    cm33_sys_ctrl_reg.SHP[11] = SCB->SHPR[11]; /* SysTick */

    cm33_sys_ctrl_reg.SHCSR = SCB->SHCSR;
    cm33_sys_ctrl_reg.CPACR = SCB->CPACR;
    cm33_sys_ctrl_reg.NSACR = SCB->NSACR; /* Not banked S/NS */

#if (defined (AIR_CPU_IN_SECURITY_MODE))
    cm33_sys_ctrl_reg_ns.ACTLR = SCnSCB_NS->ACTLR;
    cm33_sys_ctrl_reg_ns.VTOR = SCB_NS->VTOR;
    cm33_sys_ctrl_reg_ns.SCR = SCB_NS->SCR;
    cm33_sys_ctrl_reg_ns.CCR = SCB_NS->CCR;


    cm33_sys_ctrl_reg_ns.SHP[0] = SCB_NS->SHPR[0]; /* MemMange */
    cm33_sys_ctrl_reg_ns.SHP[1] = SCB_NS->SHPR[1]; /* BusFault */
    cm33_sys_ctrl_reg_ns.SHP[2] = SCB_NS->SHPR[2]; /* UsageFault */
    cm33_sys_ctrl_reg_ns.SHP[7] = SCB_NS->SHPR[7]; /* SVCall */
    cm33_sys_ctrl_reg_ns.SHP[8] = SCB_NS->SHPR[8]; /* DebugMonitor */
    cm33_sys_ctrl_reg_ns.SHP[10] = SCB_NS->SHPR[10]; /* PendSV */
    cm33_sys_ctrl_reg_ns.SHP[11] = SCB_NS->SHPR[11]; /* SysTick */

    cm33_sys_ctrl_reg_ns.SHCSR = SCB_NS->SHCSR;
    cm33_sys_ctrl_reg_ns.CPACR = SCB_NS->CPACR;
    /*todo:none-security world  CM4 DWT register backup */
    /*
    cm33_sys_ctrl_reg_ns.DHCSR = CoreDebug->DHCSR;
    cm33_sys_ctrl_reg_ns.DEMCR = CoreDebug->DEMCR;
    cm33_sys_ctrl_reg_ns.COMP0 = DWT->COMP0;
    cm33_sys_ctrl_reg_ns.FUNCTION0 = DWT->FUNCTION0;
    cm33_sys_ctrl_reg_ns.COMP1 = DWT->COMP1;
    cm33_sys_ctrl_reg_ns.FUNCTION1 = DWT->FUNCTION1;
    cm33_sys_ctrl_reg_ns.COMP2 = DWT->COMP2;
    cm33_sys_ctrl_reg_ns.FUNCTION2 = DWT->FUNCTION2;
    cm33_sys_ctrl_reg_ns.COMP3 = DWT->COMP3;
    cm33_sys_ctrl_reg_ns.FUNCTION3 = DWT->FUNCTION3;
    */

#endif
    /* CM4 DWT register backup */
    cm33_sys_ctrl_reg.DHCSR = CoreDebug->DHCSR;
    cm33_sys_ctrl_reg.DEMCR = CoreDebug->DEMCR;
    cm33_sys_ctrl_reg.COMP0 = DWT->COMP0;
    cm33_sys_ctrl_reg.FUNCTION0 = DWT->FUNCTION0;
    cm33_sys_ctrl_reg.COMP1 = DWT->COMP1;
    cm33_sys_ctrl_reg.FUNCTION1 = DWT->FUNCTION1;
    cm33_sys_ctrl_reg.COMP2 = DWT->COMP2;
    cm33_sys_ctrl_reg.FUNCTION2 = DWT->FUNCTION2;
    cm33_sys_ctrl_reg.COMP3 = DWT->COMP3;
    cm33_sys_ctrl_reg.FUNCTION3 = DWT->FUNCTION3;
}

/* deep_sleep_cmsys_restore need to define as inline function */
ATTR_TEXT_IN_TCM_RETENTION void deep_sleep_cmsys_restore(void)
{
    uint32_t i;

    /* CM33 system control registers restore */
    SCnSCB->ACTLR = cm33_sys_ctrl_reg.ACTLR;
    SCB->VTOR = cm33_sys_ctrl_reg.VTOR;
    SCB->SCR = cm33_sys_ctrl_reg.SCR;
    SCB->CCR = cm33_sys_ctrl_reg.CCR;
    SCB->SHPR[0] = cm33_sys_ctrl_reg.SHP[0]; /* MemMange */
    SCB->SHPR[1] = cm33_sys_ctrl_reg.SHP[1]; /* BusFault */
    SCB->SHPR[2] = cm33_sys_ctrl_reg.SHP[2]; /* UsageFault */
    SCB->SHPR[7] = cm33_sys_ctrl_reg.SHP[7]; /* SVCall */
    SCB->SHPR[8] = cm33_sys_ctrl_reg.SHP[8]; /* DebugMonitor */
    SCB->SHPR[10] = cm33_sys_ctrl_reg.SHP[10]; /* PendSV */
    SCB->SHPR[11] = cm33_sys_ctrl_reg.SHP[11]; /* SysTick */
    SCB->SHCSR = cm33_sys_ctrl_reg.SHCSR;
    SCB->CPACR = cm33_sys_ctrl_reg.CPACR;
    SCB->NSACR = cm33_sys_ctrl_reg.NSACR; /* Not banked S/NS */
#if (defined (AIR_CPU_IN_SECURITY_MODE))
    SCnSCB_NS->ACTLR = cm33_sys_ctrl_reg.ACTLR;
    SCB_NS->VTOR = cm33_sys_ctrl_reg_ns.VTOR;
    SCB_NS->SCR = cm33_sys_ctrl_reg_ns.SCR;
    SCB_NS->CCR = cm33_sys_ctrl_reg_ns.CCR;
    SCB_NS->SHPR[0] = cm33_sys_ctrl_reg_ns.SHP[0]; /* MemMange */
    SCB_NS->SHPR[1] = cm33_sys_ctrl_reg_ns.SHP[1]; /* BusFault */
    SCB_NS->SHPR[2] = cm33_sys_ctrl_reg_ns.SHP[2]; /* UsageFault */
    SCB_NS->SHPR[7] = cm33_sys_ctrl_reg_ns.SHP[7]; /* SVCall */
    SCB_NS->SHPR[8] = cm33_sys_ctrl_reg_ns.SHP[8]; /* DebugMonitor */
    SCB_NS->SHPR[10] = cm33_sys_ctrl_reg_ns.SHP[10]; /* PendSV */
    SCB_NS->SHPR[11] = cm33_sys_ctrl_reg_ns.SHP[11]; /* SysTick */
    SCB_NS->SHCSR = cm33_sys_ctrl_reg_ns.SHCSR;
    SCB_NS->CPACR = cm33_sys_ctrl_reg_ns.CPACR;
    /*todo:none-security world  CM4 DWT register backup */
    /*
    CoreDebug->DHCSR = cm33_sys_ctrl_reg_ns.DHCSR;
    CoreDebug->DEMCR = cm33_sys_ctrl_reg.DEMCR;
    DWT->COMP0 = cm33_sys_ctrl_reg_ns.COMP0;
    DWT->FUNCTION0 = cm33_sys_ctrl_reg_ns.FUNCTION0;
    DWT->COMP1 = cm33_sys_ctrl_reg_ns.COMP1;
    DWT->FUNCTION1 = cm33_sys_ctrl_reg_ns.FUNCTION1;
    DWT->COMP2 = cm33_sys_ctrl_reg_ns.COMP2;
    DWT->FUNCTION2 = cm33_sys_ctrl_reg_ns.FUNCTION2;
    DWT->COMP3 = cm33_sys_ctrl_reg_ns.COMP3;
    DWT->FUNCTION3 = cm33_sys_ctrl_reg_ns.FUNCTION3;
    */

#endif
    /* CM4 DWT register backup */
    CoreDebug->DHCSR = cm33_sys_ctrl_reg.DHCSR;
    CoreDebug->DEMCR = cm33_sys_ctrl_reg.DEMCR;
    DWT->COMP0 = cm33_sys_ctrl_reg.COMP0;
    DWT->FUNCTION0 = cm33_sys_ctrl_reg.FUNCTION0;
    DWT->COMP1 = cm33_sys_ctrl_reg.COMP1;
    DWT->FUNCTION1 = cm33_sys_ctrl_reg.FUNCTION1;
    DWT->COMP2 = cm33_sys_ctrl_reg.COMP2;
    DWT->FUNCTION2 = cm33_sys_ctrl_reg.FUNCTION2;
    DWT->COMP3 = cm33_sys_ctrl_reg.COMP3;
    DWT->FUNCTION3 = cm33_sys_ctrl_reg.FUNCTION3;

    /* fpu restore */
    /* TODO: need review */
    FPU->FPCCR = fpu_reg.FPCCR;
    FPU->FPCAR = fpu_reg.FPCAR;

    /* restore CPU core registers */
    temp_reg = (unsigned int)&cpu_core_reg;
    __CPU_CORE_REG_RESTORE(temp_reg);
#if (defined (AIR_CPU_IN_SECURITY_MODE))
    temp_reg = (unsigned int)&cpu_core_reg_ns;
    __CPU_CORE_REG_RESTORE_NS(temp_reg);
#endif

    /* NVIC restore */
    for (i = 0; i < SAVE_PRIORITY_GROUP; i++) {
        NVIC->IPR[i] = nvic_backup_register.nvic_ip[i];
    }
    NVIC->ISER[0] = nvic_backup_register.nvic_iser;
    NVIC->ISER[1] = nvic_backup_register.nvic_iser1;
    NVIC->ISER[2] = nvic_backup_register.nvic_iser2;
#if (defined (AIR_CPU_IN_SECURITY_MODE))
    for (i = 0; i < SAVE_PRIORITY_GROUP; i++) {
        NVIC_NS->IPR[i] = nvic_backup_register_ns.nvic_ip[i];
    }
    NVIC_NS->ISER[0] = nvic_backup_register_ns.nvic_iser;
    NVIC_NS->ISER[1] = nvic_backup_register_ns.nvic_iser1;
    NVIC_NS->ISER[2] = nvic_backup_register_ns.nvic_iser2;
#endif
}

uint32_t sleep_management_register_infra_ao_backup_restore(sleep_management_ao_backup_restore_module_t module, ao_backup_format_table_t *module_backup_format){

    printk("Module: %d enter infra_ao_backup_restore_register\r\n", module);

	volatile uint32_t* register_addr;
	uint32_t module_base_addr = module_backup_format->module_base_addr;
	uint32_t module_end_addr = module_backup_format->module_end_addr;
	uint32_t module_backup_enable = module_backup_format->module_backup_enable;
    uint32_t module_backup_len;
	uint32_t temp_register_value = 0x0;
	uint32_t register_value = 0x0;
	uint32_t next_register_addr;

    //printk("[AO][Register0] module_base_addr(0x%08x)=0x%08x\r\n",(uint32_t)module_base_addr, module_base_addr);
    //printk("[AO][Register0] module_end_addr(0x%08x)=0x%08x\r\n",(uint32_t)module_end_addr, module_end_addr);
    //printk("[AO][Register0] module_backup_enable(0x%08x)=0x%08x\r\n",(uint32_t)module_backup_enable, module_backup_enable);


	//printk("[AO][Register0] curr_register_addr(0x%08x)=0x%08x\r\n",(uint32_t)curr_register_addr, *curr_register_addr);
	module_backup_len = (uint32_t)(((module_end_addr - module_base_addr)/4) + 1);
    next_register_addr = (uint32_t)curr_register_addr + (uint32_t)((module_backup_len+1)*4);
    //printk("[AO][Register] next_register_addr(0x%08x)=0x%08x\r\n",(uint32_t)next_register_addr, next_register_addr);

	if(module_backup_len >= 255 ){
		//assert
		return (BACKUP_FORMAT_REGISTER_ERROR);
	}

	if(next_register_addr >= AO_BACKUP_MAX_ADDR){
		//assert
		return (BACKUP_FORMAT_REGISTER_ERROR);
	}
	
	/* TODO: assert at point 5.*/

    //printk("[AO][Register1] backup_restore_register_count(0x%08x)=0x%d\r\n",(uint32_t)backup_restore_register_count, backup_restore_register_count);

    /* Check module register status.
     */
    if(ao_backup_status[module].ao_backup_register == 0x0){
        
        backup_restore_register_count++;
        if(*curr_register_addr == BACKUP_FORMAT_REGISTER_END){
        
            register_addr = curr_register_addr;

        	/* Bit[15:0]=IP_BASE_ADDR, Bit[23:16]=IP_BACKUP_LEN, Bit[24]=IP_BACKUP_EN
        	 */
        	/* IP_BASE_ADDR */
        	temp_register_value = (module_base_addr >> 16);
        	register_value &= ~(0xFFFF << IP_BASE_ADDR_START_BIT);
        	register_value |= (temp_register_value << IP_BASE_ADDR_START_BIT);

        	/* IP_BACKUP_LEN */
        	temp_register_value = module_backup_len;
        	register_value &= ~(0xFF << IP_BACKUP_LEN_START_BIT);
        	register_value |= (temp_register_value << IP_BACKUP_LEN_START_BIT);

        	/* IP_BACKUP_EN */
        	temp_register_value = module_backup_enable;
        	register_value &= ~(0x1 << IP_BACKUP_EN_START_BIT);
        	register_value |= (temp_register_value << IP_BACKUP_EN_START_BIT);

            *register_addr = register_value;
            ao_backup_status[module].ao_backup_value = register_value;
            ao_backup_status[module].ao_backup_addr = (uint32_t)register_addr;
            ao_backup_status[module].ao_backup_register = BACKUP_FORMAT_REGISTER_FINISH;

            /* Check module_backup_enable initial value
             */
            if(module_backup_enable == AO_BACKUP_RESTORE_ENABLE){
                ao_backup_status[module].enable_count++;
            }

        }else{
            printk("[SLP][AO][Register] *curr_register_addr(0x%08x)=0x%08x is ERROR!!!\r\n", (uint32_t)curr_register_addr, *curr_register_addr);
        	//assert
        	return (BACKUP_FORMAT_REGISTER_ERROR);
        }
        
    }else{
        printk("[SLP][AO][Register] module(%d) have already been registered!!!\r\n", module);
        //assert
        return BACKUP_FORMAT_REGISTER_ERROR;
    }

    //printk("[AO][Register2.1] ao_backup_status[%d].ao_backup_value=0x%08x\r\n", module, ao_backup_status[module].ao_backup_value);
    //printk("[AO][Register2.1] ao_backup_status[%d].ao_backup_addr=0x%08x\r\n", module, ao_backup_status[module].ao_backup_addr);
    //printk("[AO][Register2.1] ao_backup_status[%d].ao_backup_register=0x%08x\r\n", module, ao_backup_status[module].ao_backup_register);
    //printk("[AO][Register2.1] ao_backup_status[%d].enable_count=0x%08x\r\n", module, ao_backup_status[module].enable_count);
    //printk("[AO][Register2] module_backup_len(0x%08x)=0x%08x\r\n",(uint32_t)module_backup_len, module_backup_len);
    //printk("[AO][Register2] module_base_addr(0x%08x)=0x%08x\r\n",(uint32_t)module_base_addr, module_base_addr);
    //printk("[AO][Register2] module_backup_enable(0x%08x)=0x%08x\r\n",(uint32_t)module_backup_enable, module_backup_enable);
    //printk("[AO][Register2] *register_addr(0x%08x)=0x%08x\r\n",(uint32_t)register_addr, *register_addr);
    //printk("[AO][Register2] register_value(0x%08x)=0x%08x\r\n",(uint32_t)register_value, register_value);

    //printk("[AO][Register2] curr_register_addr=0x%08x\r\n", (uint32_t)curr_register_addr);
    curr_register_addr = (volatile uint32_t*)next_register_addr;
    *curr_register_addr = BACKUP_FORMAT_REGISTER_END;

    //printk("[AO][Register3] next_register_addr(0x%08x)=0x%08x\r\n",(uint32_t)next_register_addr, next_register_addr);


    return BACKUP_FORMAT_REGISTER_FINISH;
}

uint32_t sleep_management_infra_ao_backup_restore(sleep_management_ao_backup_restore_module_t module, sleep_management_ao_backup_restore_type_t enable){
    
    if(ao_backup_status[module].ao_backup_register != BACKUP_FORMAT_REGISTER_FINISH){
        //assert
        return (BACKUP_FORMAT_REGISTER_ERROR);
    }

    if(enable == AO_BACKUP_RESTORE_ENABLE){
        /* Enable AO Backup Restore */
        if(ao_backup_status[module].enable_count++ == 0){
            ao_backup_status[module].ao_backup_value |= (0x1 << IP_BACKUP_EN_START_BIT);
            *(volatile uint32_t*)(ao_backup_status[module].ao_backup_addr) = ao_backup_status[module].ao_backup_value;

            //printk("[SLP][AO][Enable] ao_backup_status[%d].ao_backup_addr(0x%08x)=0x%08x\r\n", module, (uint32_t)ao_backup_status[module].ao_backup_addr, *(volatile uint32_t*)(ao_backup_status[module].ao_backup_addr));
            //printk("[SLP][AO][Enable] ao_backup_status[%d].enable_count(0x%x)=%d\r\n", module, (uint32_t)ao_backup_status[module].ao_backup_register, (ao_backup_status[module].enable_count));
        }

        if(ao_backup_status[module].enable_count >= 0xFF){
            printk("[SLP][AO][Enable] ao_backup_status[%d].enable_count=%d is overflow!!!\r\n", module, ao_backup_status[module].enable_count);
            //assert
            return BACKUP_FORMAT_REGISTER_ERROR;
        }

    }else{
        /* Disable AO Backup Restore */
        if(ao_backup_status[module].enable_count <= 0){
            printk("[SLP][AO][Disable] ao_backup_status[%d].enable_count=%d is underflow!!!\r\n", module, ao_backup_status[module].enable_count);
            //assert
            return BACKUP_FORMAT_REGISTER_ERROR;
        }

        if(--ao_backup_status[module].enable_count == 0){
            ao_backup_status[module].ao_backup_value &= ~(0x1 << IP_BACKUP_EN_START_BIT);
            *(volatile uint32_t*)(ao_backup_status[module].ao_backup_addr) = ao_backup_status[module].ao_backup_value;

            //printk("[SLP][AO][Disable] ao_backup_status[%d].ao_backup_addr(0x%08x)=0x%08x\r\n", module, (uint32_t)ao_backup_status[module].ao_backup_addr, *(volatile uint32_t*)(ao_backup_status[module].ao_backup_addr));
            //printk("[SLP][AO][Disable] ao_backup_status[%d].enable_count(0x%x)=%d\r\n", module, (uint32_t)ao_backup_status[module].ao_backup_register, (ao_backup_status[module].enable_count));

        }
    }

    //printk("[SLP][AO][B/R] ao_backup_status[%d].ao_backup_addr(0x%08x)=0x%08x\r\n", module, (uint32_t)ao_backup_status[module].ao_backup_addr, *(volatile uint32_t*)(ao_backup_status[module].ao_backup_addr));
    //printk("[SLP][AO][B/R] ao_backup_status[%d].enable_count(0x%x)=%d\r\n", module, (uint32_t)ao_backup_status[module].ao_backup_register, (ao_backup_status[module].enable_count));

    return ao_backup_status[module].enable_count;
}

ATTR_TEXT_IN_TCM_RETENTION void sleep_management_infra_pd_enter_sleep(sleep_management_infra_pd_module_t infra_pd_module)
{
    uint32_t mask;

    if(infra_pd_force_on_status != 0){
        return;
    }

    hal_nvic_save_and_set_interrupt_mask(&mask);

    if (infra_pd_module >= INFRA_PD_MODULE_MAX) {
        hal_nvic_restore_interrupt_mask(mask);
        log_hal_msgid_error("[SLP]unsupported INFRA_PD module\r\n", 0);
        return;
    }

    /* INFRA_PD resource control */
    infra_pd_resource_control &= ~(1UL << infra_pd_module);

    /* Check current INFRA_PD power status and usage */
    if (!infra_pd_ready_flag || (infra_pd_resource_control != 0)) {
        hal_nvic_restore_interrupt_mask(mask);
        // printk("[SLP] spm_mtcmos_infra_pd is already off\r\n");
        return;
    }

    /* Check SPM INFRA_PD ON status */
    if ((*SPM_CFG_PCM_SW_INT_STATE & 0x100) != 0) {
        /* Error!! SPM INFRA_PD ON status not cleared */
        assert(0);
    }

    /* Check INFRA_PD IRQ status & Mask all INFRA_PD IRQ */

    /* Backup INFRA_PD modules */
    sleep_management_infra_pd_suspend_callback();

    if (sleep_management_sf_dpd_is_allowed)
    {
        /* SF enter DPD */
        SF_DAL_DEV_Enter_DPD();
    }
    else
    {
        /* Only backup sfc registers, not let flash device enter DPD */
        SF_DAL_DEV_Backup();
    }
    hal_clock_sfc_ctrl(false); /* turn off sfc clock */


    /* RISCV CG off for INFRAPD_PROT_EN & INFRAPD_PROT_RDY.
     * DO not need backup/restore. Because RISCV CG is always off (clk on).
     * Confirm with CLK owner & Bus DE.
     */
    (*XO_PDN_TOP_CLRD0__XO_PDN_TOP_CLRD0) |= (1UL << 22);

    /* INFRA_PD MTCMOS off */
    *SPM_CFG_INFRA_DEEP_SLEEP = 0x1;

    /* mark INFRA_PD as not ready */
    infra_pd_ready_flag = false;

    hal_nvic_restore_interrupt_mask(mask);
}

ATTR_TEXT_IN_TCM_RETENTION void sleep_management_infra_pd_exit_sleep(sleep_management_infra_pd_module_t infra_pd_module)
{
    uint32_t mask=0;

    if(infra_pd_force_on_status != 0){
        return;
    }

    hal_nvic_save_and_set_interrupt_mask(&mask);

    if (infra_pd_module >= INFRA_PD_MODULE_MAX) {
        hal_nvic_restore_interrupt_mask(mask);
        log_hal_msgid_error("[SLP]unsupported INFRA_PD module\r\n", 0);
        return;
    }

    /* INFRA_PD resource control */
    infra_pd_resource_control |= (0x1 << infra_pd_module);

    /* Check current INFRA_PD ready status */
    if (infra_pd_ready_flag) {
        hal_nvic_restore_interrupt_mask(mask);
        // printk("[SLP] spm_mtcmos_infra_pd is already on\r\n");
        return;
    }

    /* Check SPM INFRA_PD ON status and wakeup source mask */
    if (((*SPM_CFG_PCM_SW_INT_STATE & 0x100) == 0x100) || ((*SPM_CFG_INFRA_WAKEUP_SOURCE_MASK & (0x1 << HAL_SPM_INFRA_WAKEUP_SOURCE_SPM_SW_WAKEUP)) != 0)) {
        /* Error!! SPM INFRA_PD ON status not cleared or SW triggering wakeup source not unmasked */
        assert(0);
    }

    /* RISCV CG off for INFRAPD_PROT_EN & INFRAPD_PROT_RDY.
     * DO not need backup/restore. Because RISCV CG is always off (clk on).
     * Confirm with CLK owner & Bus DE.
     */
    (*XO_PDN_TOP_CLRD0__XO_PDN_TOP_CLRD0) |= (0x1 << 22);

    /* Trigger INFRA_PD SW wakeup event */
    *SPM_CFG_INFRA_WAKEUP_EVENT = 0x1;

    /* Wait for INFRA_PD wakeup */
    while ((*SPM_CFG_PCM_SW_INT_STATE & 0x100) != 0x100);

    /* Clear INFRA_PD wakeup event */
    *SPM_CFG_PCM_SW_INT_CLEAR_INFRA = 0x1;

    /* Wait for SPM INFRA_PD ON status cleared */
    while ((*SPM_CFG_PCM_SW_INT_STATE & 0x100) == 0x100);

    hal_clock_sfc_ctrl(true); /* turn on sfc clock */
    
    if (sleep_management_sf_dpd_is_allowed)
    {
        /* SF leave DPD */
        SF_DAL_DEV_Leave_DPD();
    }
    else
    {
        /* Only restore sfc registers,do not nedd to let flash device exit DPD */
        SF_DAL_DEV_Restore();
    }

    /* Restore INFRA_PD modules */
    sleep_management_infra_pd_resume_callback();

    /* Unmask all INFRA_PD IRQ */

    /* mark INFRA_PD as ready */
    infra_pd_ready_flag = true;

    hal_nvic_restore_interrupt_mask(mask);
}

void sleep_management_register_infra_pd_suspend_callback(sleep_management_infra_pd_backup_restore_module_t module, sleep_management_suspend_callback_t callback, void *data)
{   
    printk("[SLP][Suspend] register_infra_pd module: %d", module);
    if (module == INFRA_PD_BACKUP_RESTORE_USER) {
        if (suspend_user_infra_pd_register_count < SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX) {
            suspend_user_infra_pd_callback_func_table[suspend_user_infra_pd_register_count].func        = callback;
            suspend_user_infra_pd_callback_func_table[suspend_user_infra_pd_register_count].data        = data;
            suspend_user_infra_pd_callback_func_table[suspend_user_infra_pd_register_count].init_status = SLEEP_MANAGEMENT_INITIALIZED;
            suspend_user_infra_pd_register_count++;
        } else {
            // log_hal_msgid_error("[SLP]register suspend callback function overflow\r\n", 0);
            assert(0);
        }
    } else {
        suspend_infra_pd_callback_func_table[module].func        = callback;
        suspend_infra_pd_callback_func_table[module].data        = data;
        suspend_infra_pd_callback_func_table[module].init_status = SLEEP_MANAGEMENT_INITIALIZED;
    }
}

void sleep_management_register_infra_pd_resume_callback(sleep_management_infra_pd_backup_restore_module_t module, sleep_management_resume_callback_t callback, void *data)
{   
    printk("[SLP][Resumes] register_infra_pd module: %d", module);
    if (module == INFRA_PD_BACKUP_RESTORE_USER) {
        if (resume_user_infra_pd_register_count < SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX) {
            resume_user_infra_pd_callback_func_table[resume_user_infra_pd_register_count].func        = callback;
            resume_user_infra_pd_callback_func_table[resume_user_infra_pd_register_count].data        = data;
            resume_user_infra_pd_callback_func_table[resume_user_infra_pd_register_count].init_status = SLEEP_MANAGEMENT_INITIALIZED;
            resume_user_infra_pd_register_count++;
        } else {
            // log_hal_msgid_error("[SLP]register secure resume callback function overflow\r\n", 0);
            assert(0);
        }
    } else {
        resume_infra_pd_callback_func_table[module].func = callback;
        resume_infra_pd_callback_func_table[module].data = data;
        resume_infra_pd_callback_func_table[module].init_status = SLEEP_MANAGEMENT_INITIALIZED;
    }
}

ATTR_TEXT_IN_TCM_RETENTION void sleep_management_infra_pd_suspend_callback(void)
{
    static uint32_t i;

    for (i = 0; i < INFRA_PD_BACKUP_RESTORE_MODULE_MAX; i++) {
        if (suspend_infra_pd_callback_func_table[i].init_status == SLEEP_MANAGEMENT_INITIALIZED) {

// #ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
//             sleep_management_debug_backup_restore_fun_timelog(0, 0, i);
// #endif
            suspend_infra_pd_callback_func_table[i].func(suspend_infra_pd_callback_func_table[i].data);

// #ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
//             sleep_management_debug_backup_restore_fun_timelog(0, 1, i);
// #endif
        }
    }

    for (i = 0; i < SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX; i++) {
        if (suspend_user_infra_pd_callback_func_table[i].init_status == SLEEP_MANAGEMENT_INITIALIZED) {

// #ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
//             sleep_management_debug_backup_restore_fun_timelog(1, 0, i + SLEEP_BACKUP_RESTORE_MODULE_MAX);
// #endif
            suspend_user_infra_pd_callback_func_table[i].func(suspend_user_infra_pd_callback_func_table[i].data);

// #ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
//             sleep_management_debug_backup_restore_fun_timelog(1, 1, i + SLEEP_BACKUP_RESTORE_MODULE_MAX);
// #endif
        }
    }
}

ATTR_TEXT_IN_TCM_RETENTION void sleep_management_infra_pd_resume_callback(void)
{
    static uint32_t i;

    for (i = 0; i < INFRA_PD_BACKUP_RESTORE_MODULE_MAX; i++) {
        if (resume_infra_pd_callback_func_table[i].init_status == SLEEP_MANAGEMENT_INITIALIZED) {

// #ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
//             sleep_management_debug_backup_restore_fun_timelog(1, 0, i);
// #endif
            resume_infra_pd_callback_func_table[i].func(resume_infra_pd_callback_func_table[i].data);

// #ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
//             sleep_management_debug_backup_restore_fun_timelog(1, 1, i);
// #endif
        }
    }

    for (i = 0; i < SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX; i++) {
        if (resume_user_infra_pd_callback_func_table[i].init_status == SLEEP_MANAGEMENT_INITIALIZED) {

// #ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
//             sleep_management_debug_backup_restore_fun_timelog(1, 0, i + SLEEP_BACKUP_RESTORE_MODULE_MAX);
// #endif
            resume_user_infra_pd_callback_func_table[i].func(resume_user_infra_pd_callback_func_table[i].data);

// #ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
//             sleep_management_debug_backup_restore_fun_timelog(1, 1, i + SLEEP_BACKUP_RESTORE_MODULE_MAX);
// #endif
        }
    }
}
/*-------------------------------------------------------------------*/

void sleep_management_register_suspend_ns_callback(sleep_management_backup_restore_module_t module, sleep_management_suspend_callback_t callback, void *data)
{
    if (module == SLEEP_BACKUP_RESTORE_USER) {
        if (suspend_user_register_count_ns < SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX) {
            suspend_user_ns_callback_func_table[suspend_user_register_count_ns].func        = callback;
            suspend_user_ns_callback_func_table[suspend_user_register_count_ns].data        = data;
            suspend_user_ns_callback_func_table[suspend_user_register_count_ns].init_status = SLEEP_MANAGEMENT_INITIALIZED;
            suspend_user_register_count_ns++;
        } else {
            log_hal_msgid_error("[SLP]register suspend ns callback function overflow\r\n", 0);
            assert(0);
        }
    } else {
        suspend_ns_callback_func_table[module].func        = callback;
        suspend_ns_callback_func_table[module].data        = data;
        suspend_ns_callback_func_table[module].init_status = SLEEP_MANAGEMENT_INITIALIZED;
    }
}

void sleep_management_register_suspend_secure_callback(sleep_management_backup_restore_module_t module, sleep_management_suspend_callback_t callback, void *data)
{
    if (module == SLEEP_BACKUP_RESTORE_USER) {
        if (suspend_user_register_count_in_secure < SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX) {
            suspend_user_secure_callback_func_table[suspend_user_register_count_in_secure].func        = callback;
            suspend_user_secure_callback_func_table[suspend_user_register_count_in_secure].data        = data;
            suspend_user_secure_callback_func_table[suspend_user_register_count_in_secure].init_status = SLEEP_MANAGEMENT_INITIALIZED;
            suspend_user_register_count_in_secure++;
        } else {
            log_hal_msgid_error("[SLP]register suspend callback function overflow\r\n", 0);
            assert(0);
        }
    } else {
        suspend_secure_callback_func_table[module].func        = callback;
        suspend_secure_callback_func_table[module].data        = data;
        suspend_secure_callback_func_table[module].init_status = SLEEP_MANAGEMENT_INITIALIZED;
    }
}

void sleep_management_register_all_secure_suspend_callback(sleep_management_backup_restore_module_t module, sleep_management_suspend_callback_t callback, void *data)
{
    if (module == SLEEP_BACKUP_RESTORE_USER) {
        if (suspend_user_all_secure_register_count < SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX) {
            suspend_user_all_secure_callback_func_table[suspend_user_all_secure_register_count].func        = callback;
            suspend_user_all_secure_callback_func_table[suspend_user_all_secure_register_count].data        = data;
            suspend_user_all_secure_callback_func_table[suspend_user_all_secure_register_count].init_status = SLEEP_MANAGEMENT_INITIALIZED;
            suspend_user_all_secure_register_count++;
        } else {
            log_hal_msgid_error("[SLP]register suspend callback function overflow\r\n", 0);
            assert(0);
        }
    } else {
        suspend_all_secure_callback_func_table[module].func        = callback;
        suspend_all_secure_callback_func_table[module].data        = data;
        suspend_all_secure_callback_func_table[module].init_status = SLEEP_MANAGEMENT_INITIALIZED;
    }
}


void sleep_management_register_resume_ns_callback(sleep_management_backup_restore_module_t module, sleep_management_resume_callback_t callback, void *data)
{
    if (module == SLEEP_BACKUP_RESTORE_USER) {
        if (resume_user_register_count_ns < SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX) {
            resume_user_ns_callback_func_table[resume_user_register_count_ns].func        = callback;
            resume_user_ns_callback_func_table[resume_user_register_count_ns].data        = data;
            resume_user_ns_callback_func_table[resume_user_register_count_ns].init_status = SLEEP_MANAGEMENT_INITIALIZED;
            resume_user_register_count_ns++;
        } else {
            log_hal_msgid_error("[SLP]register resume ns callback function overflow\r\n", 0);
            assert(0);
        }
    } else {
        resume_ns_callback_func_table[module].func = callback;
        resume_ns_callback_func_table[module].data = data;
        resume_ns_callback_func_table[module].init_status = SLEEP_MANAGEMENT_INITIALIZED;
    }
}


void sleep_management_register_resume_secure_callback(sleep_management_backup_restore_module_t module, sleep_management_resume_callback_t callback, void *data)
{
    if (module == SLEEP_BACKUP_RESTORE_USER) {
        if (resume_user_register_count_in_secure < SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX) {
            resume_user_secure_callback_func_table[resume_user_register_count_in_secure].func        = callback;
            resume_user_secure_callback_func_table[resume_user_register_count_in_secure].data        = data;
            resume_user_secure_callback_func_table[resume_user_register_count_in_secure].init_status = SLEEP_MANAGEMENT_INITIALIZED;
            resume_user_register_count_in_secure++;
        } else {
            log_hal_msgid_error("[SLP]register secure resume callback function overflow\r\n", 0);
            assert(0);
        }
    } else {
        resume_secure_callback_func_table[module].func = callback;
        resume_secure_callback_func_table[module].data = data;
        resume_secure_callback_func_table[module].init_status = SLEEP_MANAGEMENT_INITIALIZED;
    }
}

void sleep_management_register_all_secure_resume_callback(sleep_management_backup_restore_module_t module, sleep_management_resume_callback_t callback, void *data)
{
    if (module == SLEEP_BACKUP_RESTORE_USER) {
        if (resume_user_all_secure_register_count < SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX) {
            resume_user_all_secure_callback_func_table[resume_user_all_secure_register_count].func        = callback;
            resume_user_all_secure_callback_func_table[resume_user_all_secure_register_count].data        = data;
            resume_user_all_secure_callback_func_table[resume_user_all_secure_register_count].init_status = SLEEP_MANAGEMENT_INITIALIZED;
            resume_user_all_secure_register_count++;
        } else {
            log_hal_msgid_error("[SLP]register secure resume callback function overflow\r\n", 0);
            assert(0);
        }
    } else {
        resume_all_secure_callback_func_table[module].func = callback;
        resume_all_secure_callback_func_table[module].data = data;
        resume_all_secure_callback_func_table[module].init_status = SLEEP_MANAGEMENT_INITIALIZED;
    }
}

#if (defined AIR_LIMIT_TZ_ENABLE)
ATTR_TEXT_IN_TCM_RETENTION void sleep_management_ns_suspend_callback()
{
    static uint32_t i;

    for (i = 0; i < SLEEP_BACKUP_RESTORE_MODULE_MAX; i++) {
        if (suspend_ns_callback_func_table[i].init_status == SLEEP_MANAGEMENT_INITIALIZED) {

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(0, 0, i);
#endif

#if SKIP_UART_BACKUP_RESTORE == 1
            if (i != SLEEP_BACKUP_RESTORE_UART) {
                suspend_ns_callback_func_table[i].func(suspend_ns_callback_func_table[i].data);
            }
#else
            suspend_ns_callback_func_table[i].func(suspend_ns_callback_func_table[i].data);
#endif

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(0, 1, i);
#endif
        }
    }

    for (i = 0; i < SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX; i++) {
        if (suspend_user_ns_callback_func_table[i].init_status == SLEEP_MANAGEMENT_INITIALIZED) {

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 0, i + SLEEP_BACKUP_RESTORE_MODULE_MAX);
#endif

            suspend_user_ns_callback_func_table[i].func(suspend_user_ns_callback_func_table[i].data);

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 1, i + SLEEP_BACKUP_RESTORE_MODULE_MAX);
#endif
        }
    }
}

ATTR_TEXT_IN_TCM_RETENTION void sleep_management_secure_suspend_callback()
{
    static uint32_t i;

    for (i = 0; i < SLEEP_BACKUP_RESTORE_MODULE_MAX; i++) {
        if (suspend_secure_callback_func_table[i].init_status == SLEEP_MANAGEMENT_INITIALIZED) {

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(0, 0, i);
#endif

#if SKIP_UART_BACKUP_RESTORE == 1
            if (i != SLEEP_BACKUP_RESTORE_UART) {
                suspend_secure_callback_func_table[i].func(suspend_secure_callback_func_table[i].data);
            }
#else
            suspend_secure_callback_func_table[i].func(suspend_secure_callback_func_table[i].data);
#endif

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(0, 1, i);
#endif
        }
    }

    for (i = 0; i < SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX; i++) {
        if (suspend_user_secure_callback_func_table[i].init_status == SLEEP_MANAGEMENT_INITIALIZED) {

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 0, i + SLEEP_BACKUP_RESTORE_MODULE_MAX);
#endif

            suspend_user_secure_callback_func_table[i].func(suspend_user_secure_callback_func_table[i].data);

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 1, i + SLEEP_BACKUP_RESTORE_MODULE_MAX);
#endif
        }
    }
}
#else
ATTR_TEXT_IN_TCM_RETENTION void sleep_management_all_secure_suspend_callback()
{
    static uint32_t i;

    for (i = 0; i < SLEEP_BACKUP_RESTORE_MODULE_MAX; i++) {
        if (suspend_all_secure_callback_func_table[i].init_status == SLEEP_MANAGEMENT_INITIALIZED) {

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(0, 0, i);
#endif

#if SKIP_UART_BACKUP_RESTORE == 1
            if (i != SLEEP_BACKUP_RESTORE_UART) {
                suspend_all_secure_callback_func_table[i].func(suspend_all_secure_callback_func_table[i].data);
            }
#else
            suspend_all_secure_callback_func_table[i].func(suspend_all_secure_callback_func_table[i].data);
#endif

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(0, 1, i);
#endif
        }
    }

    for (i = 0; i < SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX; i++) {
        if (suspend_user_all_secure_callback_func_table[i].init_status == SLEEP_MANAGEMENT_INITIALIZED) {

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 0, i + SLEEP_BACKUP_RESTORE_MODULE_MAX);
#endif

            suspend_user_all_secure_callback_func_table[i].func(suspend_user_all_secure_callback_func_table[i].data);

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 1, i + SLEEP_BACKUP_RESTORE_MODULE_MAX);
#endif
        }
    }
}
#endif

#if (defined AIR_LIMIT_TZ_ENABLE)
ATTR_TEXT_IN_TCM_RETENTION void sleep_management_ns_resume_callback()
{
    static uint32_t i;

    for (i = 0; i < SLEEP_BACKUP_RESTORE_MODULE_MAX; i++) {
        if (resume_ns_callback_func_table[i].init_status == SLEEP_MANAGEMENT_INITIALIZED) {

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 0, i);
#endif

#if SKIP_UART_BACKUP_RESTORE == 1
            if (i != SLEEP_BACKUP_RESTORE_UART) {
                resume_ns_callback_func_table[i].func(resume_ns_callback_func_table[i].data);
            }
#else
            resume_ns_callback_func_table[i].func(resume_ns_callback_func_table[i].data);
#endif

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 1, i);
#endif
        }
    }

    for (i = 0; i < SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX; i++) {
        if (resume_user_ns_callback_func_table[i].init_status == SLEEP_MANAGEMENT_INITIALIZED) {

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 0, i + SLEEP_BACKUP_RESTORE_MODULE_MAX);
#endif

            resume_user_ns_callback_func_table[i].func(resume_user_ns_callback_func_table[i].data);

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 1, i + SLEEP_BACKUP_RESTORE_MODULE_MAX);
#endif
        }
    }
}

ATTR_TEXT_IN_TCM_RETENTION void sleep_management_secure_resume_callback()
{
    static uint32_t i;

    for (i = 0; i < SLEEP_BACKUP_RESTORE_MODULE_MAX; i++) {
        if (resume_secure_callback_func_table[i].init_status == SLEEP_MANAGEMENT_INITIALIZED) {

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 0, i);
#endif

#if SKIP_UART_BACKUP_RESTORE == 1
            if (i != SLEEP_BACKUP_RESTORE_UART) {
                resume_secure_callback_func_table[i].func(resume_secure_callback_func_table[i].data);
            }
#else
            resume_secure_callback_func_table[i].func(resume_secure_callback_func_table[i].data);
#endif

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 1, i);
#endif
        }
    }

    for (i = 0; i < SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX; i++) {
        if (resume_user_secure_callback_func_table[i].init_status == SLEEP_MANAGEMENT_INITIALIZED) {

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 0, i + SLEEP_BACKUP_RESTORE_MODULE_MAX);
#endif

            resume_user_secure_callback_func_table[i].func(resume_user_secure_callback_func_table[i].data);

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 1, i + SLEEP_BACKUP_RESTORE_MODULE_MAX);
#endif
        }
    }
}
#else
ATTR_TEXT_IN_TCM_RETENTION void sleep_management_all_secure_resume_callback()
{
    static uint32_t i;

    for (i = 0; i < SLEEP_BACKUP_RESTORE_MODULE_MAX; i++) {
        if (resume_all_secure_callback_func_table[i].init_status == SLEEP_MANAGEMENT_INITIALIZED) {

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 0, i);
#endif

#if SKIP_UART_BACKUP_RESTORE == 1
            if (i != SLEEP_BACKUP_RESTORE_UART) {
                resume_all_secure_callback_func_table[i].func(resume_all_secure_callback_func_table[i].data);
            }
#else
            resume_all_secure_callback_func_table[i].func(resume_all_secure_callback_func_table[i].data);
#endif

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 1, i);
#endif
        }
    }

    for (i = 0; i < SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX; i++) {
        if (resume_user_all_secure_callback_func_table[i].init_status == SLEEP_MANAGEMENT_INITIALIZED) {

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 0, i + SLEEP_BACKUP_RESTORE_MODULE_MAX);
#endif

            resume_user_all_secure_callback_func_table[i].func(resume_user_all_secure_callback_func_table[i].data);

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 1, i + SLEEP_BACKUP_RESTORE_MODULE_MAX);
#endif
        }
    }
}
#endif

uint8_t sleep_management_get_lock_handle(const char *handle_name)
{
    uint8_t index = 0;


#ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
    uint8_t i;
    uint32_t mask, name_len;

    for (index = 0 ; index < SLEEP_LOCK_HANDLE_USER_MAX; index++) {
        hal_nvic_save_and_set_interrupt_mask(&mask);

        if (((sleep_management_handle.user_handle_resource >> index) & 0x01) == 0) {

            sleep_management_handle.user_handle_resource |= (1 << index);
            sleep_management_handle.user_handle_count++;

            hal_nvic_restore_interrupt_mask(mask);

            memset(&sleep_management_handle.user_handle_name[index][0], 0, SLEEP_HANDLE_NAME_LEN);
            name_len = strlen(handle_name);

            if (name_len >= SLEEP_HANDLE_NAME_LEN) {
                name_len = SLEEP_HANDLE_NAME_LEN - 1;
            }
            memcpy(&sleep_management_handle.user_handle_name[index][0], handle_name, name_len);

            /* Check handle name */
            if (name_len == 0) {
                log_hal_msgid_error("[SLP]sleep handle name error\r\n", 0);
                assert(0);
            }
            for (i = 0; i < name_len; i++) {
                if ((sleep_management_handle.user_handle_name[index][i] <= 0x20) || (sleep_management_handle.user_handle_name[index][i] >= 0x7E)) {
                    log_hal_msgid_error("[SLP]sleep handle name error\r\n", 0);
                    assert(0);
                }
            }
            break;
        } else {
            hal_nvic_restore_interrupt_mask(mask);
        }
    }

    //log_hal_msgid_info("[SLP]sleep handle name : %s\r\n", 1, &sleep_management_handle.user_handle_name[index][0]);
#if defined(AIR_LOGGING_ENABLE)
    print_module_log(NULL, NULL, 1, PRINT_LEVEL_INFO,"[SLP] slp handle name(%d) : %s\r\n", (index+SLEEP_LOCK_USER_START_ID), &sleep_management_handle.user_handle_name[index][0]);
#endif

    if (index >= SLEEP_LOCK_HANDLE_USER_MAX) {
        log_hal_msgid_error("[SLP]cannot get sleep handle\r\n", 0);
        assert(0);
        return (SLEEP_LOCK_INVALID_ID);
    }

    index += SLEEP_LOCK_USER_START_ID;
#endif

    return (index);
}

void sleep_management_release_lock_handle(uint8_t handle_index)
{
#ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
    uint32_t mask;
    /*  check handle index range */
    if ((handle_index >= SLEEP_LOCK_HANDLE_MAX) || (handle_index < SLEEP_LOCK_USER_START_ID)) {
        log_hal_msgid_error("[SLP]sleep handle index error\r\n", 0);
        return;
    }

    handle_index -= SLEEP_LOCK_USER_START_ID;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    if (((sleep_management_handle.user_handle_resource >> handle_index) & 0x01) == 1) {
        sleep_management_handle.user_handle_count--;
        sleep_management_handle.user_handle_resource &= ~(1 << handle_index);
        memset(&sleep_management_handle.user_handle_name[handle_index][0], 0, SLEEP_HANDLE_NAME_LEN);
    } else {
        log_hal_msgid_warning("[SLP]sleep handle(%d) already release \r\n", 1, (handle_index+SLEEP_LOCK_USER_START_ID));
    }
    hal_nvic_restore_interrupt_mask(mask);
#endif
}

ATTR_TEXT_IN_TCM_RETENTION void sleep_management_lock_sleep(sleep_management_lock_sleep_t lock, uint8_t handle_index)
{
#ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
    uint32_t mask;
    uint64_t shift = 1;

    if (handle_index >= SLEEP_LOCK_HANDLE_MAX) {
        log_hal_msgid_error("[SLP]sleep handle index error\r\n", 0);
        return;
    }

    if (lock == LOCK_SLEEP) {
        /* Lock sleep request */
        hal_nvic_save_and_set_interrupt_mask(&mask);
        if (sleep_management_handle.lock_sleep_request_count[handle_index] < 0xFF) {
            sleep_management_handle.lock_sleep_request_count[handle_index]++;
            shift <<= handle_index;
            sleep_management_handle.lock_sleep_request |= shift;

        }
        hal_nvic_restore_interrupt_mask(mask);
#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
        sleep_management_debug_lock_sleep_timelog(lock, handle_index);
#endif
        if (sleep_management_handle.lock_sleep_request_count[handle_index] == 0xFF) {
            SLEEP_MANAGER_MSGID_W("[SLP]sleep handle=%d,lock sleep count full \r\n", 1, handle_index);
            if (handle_index >= SLEEP_LOCK_USER_START_ID) {
            #if defined(AIR_LOGGING_ENABLE)
                print_module_log(NULL, NULL, 1, PRINT_LEVEL_INFO,"[SLP]sleep handle = %s\r\n", &sleep_management_handle.user_handle_name[(handle_index - SLEEP_LOCK_USER_START_ID)][0]);
            #endif
            }
        }

    } else {
        /* Unlock sleep request */
        hal_nvic_save_and_set_interrupt_mask(&mask);
        if (sleep_management_handle.lock_sleep_request_count[handle_index] > 0) {
            sleep_management_handle.lock_sleep_request_count[handle_index]--;
            if (sleep_management_handle.lock_sleep_request_count[handle_index] == 0) {
                shift <<= handle_index;
                sleep_management_handle.lock_sleep_request &= ~shift;

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
                sleep_management_debug_lock_sleep_timelog(lock, handle_index);
#endif
            }
            hal_nvic_restore_interrupt_mask(mask);
        } else {
            hal_nvic_restore_interrupt_mask(mask);
            SLEEP_MANAGER_MSGID_W("[SLP]sleep handle=%d has already unlock sleep \r\n", 1, handle_index);
            if (handle_index >= SLEEP_LOCK_USER_START_ID) {
            #if defined(AIR_LOGGING_ENABLE)
                print_module_log(NULL, NULL, 1, PRINT_LEVEL_INFO,"[SLP] sleep handle = %s\r\n", &sleep_management_handle.user_handle_name[(handle_index - SLEEP_LOCK_USER_START_ID)][0]);
            #endif
            }
        }
    }
    // SLEEP_MANAGER_MSGID_I("[SLP] lock sleep handle=0x%x, lock index=%d, lock_sleep_request=0x%x", 3, lock, handle_index, sleep_management_handle.lock_sleep_request);
#endif

}

bool sleep_management_check_sleep_locks(void)
{
    bool lock = true;

#ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
    uint32_t mask;
    uint64_t sleep_handle_mask = 1;

    sleep_handle_mask <<= (SLEEP_LOCK_HANDLE_MAX - 1);
    sleep_handle_mask -= 1;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    if ((sleep_management_handle.lock_sleep_request & sleep_handle_mask) == 0) {
        lock = false;
    } else {
        lock = true;
    }
    hal_nvic_restore_interrupt_mask(mask);
#endif
    return lock;
}

bool sleep_management_check_handle_status(uint8_t handle_index)
{
    bool lock = false;

#ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
    /*  check handle index range */
    if ((handle_index >= SLEEP_LOCK_HANDLE_MAX)) {
        log_hal_msgid_error("[SLP]sleep handle index error\r\n", 0);
        return false;
    }

    if (((sleep_management_handle.lock_sleep_request >> (handle_index)) & 0x01) == 1) {
        lock = true;
        return lock;
    } else {
        lock = false;
        return lock;
    }
#endif
    return lock;
}

uint64_t sleep_management_get_lock_sleep_request_info(void)
{
#ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
    return sleep_management_handle.lock_sleep_request;
#else
    return 0xFFFFFFFF; /* Disable CMSYS enter sleep, all modules lock sleep */
#endif
}

uint64_t sleep_management_get_lock_sleep_handle_list(void)
{
#ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
    uint8_t i;
    uint64_t lock_sleep_request = sleep_management_handle.lock_sleep_request;
    uint64_t mask = 1;

    printk("[SLP] lock sleep handle list : \r\n");
    printk("[SLP] lock_sleep_request = 0x%x\r\n", (uint32_t)lock_sleep_request);
    for (i = 0; i < SLEEP_LOCK_HANDLE_MAX; i++) {
        if (lock_sleep_request & (mask << i)) {
            printk("[SLP] index of sleep handle = %d\r\n", i);
            if (i >= SLEEP_LOCK_USER_START_ID) {
                // printk("[SLP] sleep handle = %s\r\n", &sleep_management_handle.user_handle_name[i - SLEEP_LOCK_USER_START_ID][0]);
            #if defined(AIR_LOGGING_ENABLE)
                print_module_log(NULL, NULL, 1, PRINT_LEVEL_INFO,"[SLP] sleep handle = %s\r\n", &sleep_management_handle.user_handle_name[i - SLEEP_LOCK_USER_START_ID][0]);
            #endif
            }
        }
    }
    return lock_sleep_request;
#else
    return 0xFFFFFFF; /* Disable sleep management handle, all modules lock sleep */
#endif
}

uint8_t sleep_management_get_lock_idle_handle(const char *handle_name)
{
    uint8_t index = 0;
    uint8_t i;
    uint32_t mask, name_len;

#ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
    for (index = 0 ; index < SLEEP_LOCK_TICKLESS_IDLE_HANDLE_USER_MAX; index++) {
        hal_nvic_save_and_set_interrupt_mask(&mask);

        if (((sleep_management_idle_handle.user_handle_resource >> index) & 0x01) == 0) {

            sleep_management_idle_handle.user_handle_resource |= (1 << index);
            sleep_management_idle_handle.user_handle_count++;

            hal_nvic_restore_interrupt_mask(mask);

            memset(&sleep_management_idle_handle.user_handle_name[index][0], 0, SLEEP_HANDLE_NAME_LEN);
            name_len = strlen(handle_name);

            if (name_len >= SLEEP_HANDLE_NAME_LEN) {
                name_len = SLEEP_HANDLE_NAME_LEN - 1;
            }
            memcpy(&sleep_management_idle_handle.user_handle_name[index][0], handle_name, name_len);

            /* Check handle name */
            if (name_len == 0) {
                // log_hal_msgid_error("[SLP]idle handle name error\r\n", 0);
                assert(0);
            }
            for (i = 0; i < name_len; i++) {
                if ((sleep_management_idle_handle.user_handle_name[index][i] <= 0x20) || (sleep_management_idle_handle.user_handle_name[index][i] >= 0x7E)) {
                    // log_hal_msgid_error("[SLP]idle handle name error\r\n", 0);
                    assert(0);
                }
            }
            break;
        } else {
            hal_nvic_restore_interrupt_mask(mask);
        }
    }

    //log_hal_msgid_info("[SLP]idle handle name : %s\r\n", 1, &sleep_management_idle_handle.user_handle_name[index][0]);
#if defined(AIR_LOGGING_ENABLE)
    print_module_log(NULL, NULL, 1, PRINT_LEVEL_INFO,"[SLP] idle handle name(%d) = %s\r\n",(index+SLEEP_LOCK_TICKLESS_IDLE_USER_START_ID), &sleep_management_idle_handle.user_handle_name[index][0]);
#endif
    if (index >= SLEEP_LOCK_TICKLESS_IDLE_HANDLE_USER_MAX) {
        log_hal_msgid_error("[SLP]cannot get idle handle\r\n", 0);
        assert(0);
        return (SLEEP_LOCK_TICKLESS_IDLE_INVALID_ID);
    }

    index += SLEEP_LOCK_TICKLESS_IDLE_USER_START_ID;
#endif

    return (index);
}

void sleep_management_release_lock_idle_handle(uint8_t handle_index)
{
#ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
    uint32_t mask;
    /*  check handle index range */
    if ((handle_index >= (SLEEP_LOCK_TICKLESS_IDLE_HANDLE_USER_MAX + SLEEP_LOCK_TICKLESS_IDLE_USER_START_ID)) || (handle_index < SLEEP_LOCK_TICKLESS_IDLE_USER_START_ID)) {
        log_hal_msgid_error("[SLP]idle handle index error\r\n", 0);
        return;
    }

    handle_index -= SLEEP_LOCK_TICKLESS_IDLE_USER_START_ID;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    if (((sleep_management_idle_handle.user_handle_resource >> handle_index) & 0x01) == 1) {
        sleep_management_idle_handle.user_handle_count--;
        sleep_management_idle_handle.user_handle_resource &= ~(1 << handle_index);
        memset(&sleep_management_idle_handle.user_handle_name[handle_index][0], 0, SLEEP_HANDLE_NAME_LEN);
    } else {
        log_hal_msgid_warning("[SLP]idle handle(%d) already release \r\n", 1, (handle_index+SLEEP_LOCK_TICKLESS_IDLE_USER_START_ID));
    }
    hal_nvic_restore_interrupt_mask(mask);
#endif
}

void sleep_management_lock_idle(sleep_management_lock_idle_t lock, uint8_t handle_index)
{
    uint32_t mask;
    uint64_t shift = 1;

    if (handle_index >= (SLEEP_LOCK_TICKLESS_IDLE_HANDLE_USER_MAX + SLEEP_LOCK_TICKLESS_IDLE_USER_START_ID)) {
        log_hal_msgid_error("[SLP]idle handle index error\r\n", 0);
        return;
    }

    if (lock == LOCK_TICKLESS_IDLE) {
        /* Lock idle request */
        hal_nvic_save_and_set_interrupt_mask(&mask);
        if (sleep_management_idle_handle.lock_idle_request_count[handle_index] < 0xFF) {
            sleep_management_idle_handle.lock_idle_request_count[handle_index]++;
            shift <<= handle_index;
            sleep_management_idle_handle.lock_idle_request |= shift;

        }
        hal_nvic_restore_interrupt_mask(mask);
#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
        sleep_management_debug_lock_sleep_timelog(lock, handle_index);
#endif
        if (sleep_management_idle_handle.lock_idle_request_count[handle_index] == 0xFF) {
            SLEEP_MANAGER_MSGID_W("[SLP]idle handle=%d, lock idle count full\r\n", 1, handle_index);
            if (handle_index >= SLEEP_LOCK_TICKLESS_IDLE_HANDLE_USER_MAX) {
            #if defined(AIR_LOGGING_ENABLE)
                print_module_log(NULL, NULL, 1, PRINT_LEVEL_INFO,"[SLP] idle handle = %s\r\n", &sleep_management_idle_handle.user_handle_name[(handle_index - SLEEP_LOCK_TICKLESS_IDLE_HANDLE_USER_MAX)][0]);
            #endif
            }
        }

    } else {
        /* Unlock idle request */
        hal_nvic_save_and_set_interrupt_mask(&mask);
        if (sleep_management_idle_handle.lock_idle_request_count[handle_index] > 0) {
            sleep_management_idle_handle.lock_idle_request_count[handle_index]--;
            if (sleep_management_idle_handle.lock_idle_request_count[handle_index] == 0) {
                shift <<= handle_index;
                sleep_management_idle_handle.lock_idle_request &= ~shift;

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
                sleep_management_debug_lock_sleep_timelog(lock, handle_index);
#endif
            }
            hal_nvic_restore_interrupt_mask(mask);
        } else {
            hal_nvic_restore_interrupt_mask(mask);
            SLEEP_MANAGER_MSGID_W("[SLP]idle handle=%d has already unlock idle \r\n", 1, handle_index);
            if (handle_index >= SLEEP_LOCK_TICKLESS_IDLE_USER_START_ID) {
            #if defined(AIR_LOGGING_ENABLE)
                print_module_log(NULL, NULL, 1, PRINT_LEVEL_INFO,"[SLP] idle handle = %s\r\n", &sleep_management_idle_handle.user_handle_name[(handle_index - SLEEP_LOCK_TICKLESS_IDLE_USER_START_ID)][0]);
            #endif
            }
        }
    }
    // SLEEP_MANAGER_MSGID_I("[SLP] idle handle=0x%x, lock index=%d, lock_idle_request=0x%x", 3, lock, handle_index, sleep_management_idle_handle.lock_idle_request);
}

bool sleep_management_check_idle_locks(void)
{
    bool lock = true;
    uint32_t mask;
    uint64_t idle_handle_mask = 1;

    idle_handle_mask <<= (SLEEP_LOCK_HANDLE_MAX - 1);
    idle_handle_mask -= 1;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    if ((sleep_management_idle_handle.lock_idle_request & idle_handle_mask) == 0) {
        lock = false;
    } else {
        lock = true;
    }
    hal_nvic_restore_interrupt_mask(mask);

    return lock;
}

uint64_t sleep_management_get_lock_idle_request_info(void)
{
#ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
    return sleep_management_idle_handle.lock_idle_request;
#else
    return 0xFFFFFFFF;
#endif
}

uint64_t sleep_management_get_lock_idle_handle_list(void)
{
    uint8_t i;
    uint64_t lock_idle_request = sleep_management_idle_handle.lock_idle_request;
    uint64_t mask = 1;

    printk("[SLP] lock idle handle list : \r\n");
    printk("[SLP] lock_idle_request = 0x%x \r\n", (uint32_t)lock_idle_request);
    for (i = 0; i < SLEEP_LOCK_HANDLE_MAX; i++) {
        if (lock_idle_request & (mask << i)) {
            printk("[SLP] index of idle handle = %d\r\n", i);
            // SLEEP_MANAGER_LOG_I("[SLP] idle handle = %s\r\n", sleep_management_idle_handle.user_handle_name[i]);
            if (i >= SLEEP_LOCK_TICKLESS_IDLE_USER_START_ID) {
                // printk("[SLP] sleep handle = %s\r\n", &sleep_management_handle.user_handle_name[i - SLEEP_LOCK_USER_START_ID][0]);
            #if defined(AIR_LOGGING_ENABLE)
                print_module_log(NULL, NULL, 1, PRINT_LEVEL_INFO,"[SLP] idle handle = %s\r\n", &sleep_management_idle_handle.user_handle_name[i][0]);
            #endif
            }
        }
    }
    return lock_idle_request;
}

uint8_t sleep_management_get_lock_extslp_handle(const char *handle_name)
{
    uint8_t index = 0;

#ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
    uint8_t i;
    uint32_t mask, name_len;

    for (index = 0 ; index < SLEEP_LOCK_EXTEND_HANDLE_USER_MAX; index++) {
        hal_nvic_save_and_set_interrupt_mask(&mask);

        if (((sleep_management_extslp_handle.user_handle_resource >> index) & 0x01) == 0) {

            sleep_management_extslp_handle.user_handle_resource |= (1 << index);
            sleep_management_extslp_handle.user_handle_count++;

            hal_nvic_restore_interrupt_mask(mask);

            memset(&sleep_management_extslp_handle.user_handle_name[index][0], 0, SLEEP_HANDLE_NAME_LEN);
            name_len = strlen(handle_name);

            if (name_len >= SLEEP_HANDLE_NAME_LEN) {
                name_len = SLEEP_HANDLE_NAME_LEN - 1;
            }
            memcpy(&sleep_management_extslp_handle.user_handle_name[index][0], handle_name, name_len);

            /* Check handle name */
            if (name_len == 0) {
                // log_hal_msgid_error("[SLP]extslp handle name error\r\n", 0);
                assert(0);
            }
            for (i = 0; i < name_len; i++) {
                if ((sleep_management_extslp_handle.user_handle_name[index][i] <= 0x20) || (sleep_management_extslp_handle.user_handle_name[index][i] >= 0x7E)) {
                    // log_hal_msgid_error("[SLP]extslp handle name error\r\n", 0);
                    assert(0);
                }
            }
            break;
        } else {
            hal_nvic_restore_interrupt_mask(mask);
        }
    }

    //log_hal_msgid_info("[SLP]extslp handle name : %s\r\n", 1, &sleep_management_extslp_handle.user_handle_name[index][0]);
#if defined(AIR_LOGGING_ENABLE)
    print_module_log(NULL, NULL, 1, PRINT_LEVEL_INFO,"[SLP] extslp handle name(%d) : %s\r\n",(index + SLEEP_LOCK_EXTEND_USER_START_ID), &sleep_management_extslp_handle.user_handle_name[index][0]);
#endif

    if (index >= SLEEP_LOCK_EXTEND_HANDLE_USER_MAX) {
        log_hal_msgid_error("[SLP]cannot get extslp handle\r\n", 0);
        assert(0);
        return (SLEEP_LOCK_EXTEND_INVALID_ID);
    }

    index += SLEEP_LOCK_EXTEND_USER_START_ID;
#endif

    return (index);
}

void sleep_management_release_lock_extslp_handle(uint8_t handle_index)
{
#ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
    uint32_t mask;
    /*  check handle index range */
    if ((handle_index >= SLEEP_LOCK_HANDLE_MAX) || (handle_index < SLEEP_LOCK_EXTEND_USER_START_ID)) {
        log_hal_msgid_error("[SLP]extslp handle index error\r\n", 0);
        return;
    }

    handle_index -= SLEEP_LOCK_EXTEND_USER_START_ID;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    if (((sleep_management_extslp_handle.user_handle_resource >> handle_index) & 0x01) == 1) {
        sleep_management_extslp_handle.user_handle_count--;
        sleep_management_extslp_handle.user_handle_resource &= ~(1 << handle_index);
        memset(&sleep_management_extslp_handle.user_handle_name[handle_index][0], 0, SLEEP_HANDLE_NAME_LEN);
    } else {
        log_hal_msgid_warning("[SLP]extslp handle(%d) already release \r\n", 1, (handle_index+SLEEP_LOCK_EXTEND_USER_START_ID));
    }
    hal_nvic_restore_interrupt_mask(mask);
#endif
}

void sleep_management_lock_extslp(sleep_management_lock_extslp_t lock, uint8_t handle_index)
{
#ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
    uint32_t mask;
    uint64_t shift = 1;

    if (handle_index >= SLEEP_LOCK_HANDLE_MAX) {
        log_hal_msgid_error("[SLP]extslp handle index error\r\n", 0);
        return;
    }

    if (lock == LOCK_EXTSLP) {
        /* Lock extslp request */
        hal_nvic_save_and_set_interrupt_mask(&mask);
        if (sleep_management_extslp_handle.lock_extslp_request_count[handle_index] < 0xFF) {
            sleep_management_extslp_handle.lock_extslp_request_count[handle_index]++;
            shift <<= handle_index;
            sleep_management_extslp_handle.lock_extslp_request |= shift;
            *SPM_CFG_CMSYS_REQ_EXT_SLP = 0x0;
        }
        hal_nvic_restore_interrupt_mask(mask);
#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
        sleep_management_debug_lock_sleep_timelog(lock, handle_index);
#endif
        if (sleep_management_extslp_handle.lock_extslp_request_count[handle_index] == 0xFF) {
            SLEEP_MANAGER_MSGID_W("[SLP]extslp handle=%d, lock extslp count full\r\n", 1, handle_index);
            if (handle_index >= SLEEP_LOCK_EXTEND_USER_START_ID) {
            #if defined(AIR_LOGGING_ENABLE)
                print_module_log(NULL, NULL, 1, PRINT_LEVEL_INFO,"[SLP] extslp handle = %s\r\n", &sleep_management_extslp_handle.user_handle_name[(handle_index - SLEEP_LOCK_EXTEND_USER_START_ID)][0]);
            #endif
            }
        }

    } else {
        /* Unlock extslp request */
        hal_nvic_save_and_set_interrupt_mask(&mask);
        if (sleep_management_extslp_handle.lock_extslp_request_count[handle_index] > 0) {
            sleep_management_extslp_handle.lock_extslp_request_count[handle_index]--;
            if (sleep_management_extslp_handle.lock_extslp_request_count[handle_index] == 0) {
                shift <<= handle_index;
                sleep_management_extslp_handle.lock_extslp_request &= ~shift;
                if (!sleep_management_check_extslp_locks()) {
                    *SPM_CFG_CMSYS_REQ_EXT_SLP = 0x1;
                }
#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
                sleep_management_debug_lock_sleep_timelog(lock, handle_index);
#endif
            }
            hal_nvic_restore_interrupt_mask(mask);
        } else {
            hal_nvic_restore_interrupt_mask(mask);
            SLEEP_MANAGER_MSGID_W("[SLP]extslp handle=%d has already unlock extslp \r\n", 1, handle_index);
            if (handle_index >= SLEEP_LOCK_EXTEND_USER_START_ID) {
            #if defined(AIR_LOGGING_ENABLE)
                print_module_log(NULL, NULL, 1, PRINT_LEVEL_INFO,"[SLP] extslp handle = %s\r\n", &sleep_management_extslp_handle.user_handle_name[(handle_index - SLEEP_LOCK_EXTEND_USER_START_ID)][0]);
            #endif
            }
        }
    }
    // SLEEP_MANAGER_MSGID_I("[SLP] lock extslp handle=0x%x, lock index=%d, lock_extslp_request=0x%x", 3, lock, handle_index, sleep_management_extslp_handle.lock_extslp_request);
#endif
}

bool sleep_management_check_extslp_locks(void)
{
    bool lock = true;

#ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
    uint32_t mask;
    uint64_t extslp_handle_mask = 1;

    extslp_handle_mask <<= (SLEEP_LOCK_HANDLE_MAX - 1);
    extslp_handle_mask -= 1;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    if ((sleep_management_extslp_handle.lock_extslp_request & extslp_handle_mask) == 0) {
        lock = false;
    } else {
        lock = true;
    }
    hal_nvic_restore_interrupt_mask(mask);
#endif
    return lock;
}

uint64_t sleep_management_get_lock_extslp_request_info(void)
{
#ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
    return sleep_management_extslp_handle.lock_extslp_request;
#else
    return 0xFFFFFFFF; /* Disable CMSYS enter sleep, all modules lock extslp */
#endif
}

uint64_t sleep_management_get_lock_extslp_handle_list(void)
{
#ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
    uint8_t i;
    uint64_t lock_extslp_request = sleep_management_extslp_handle.lock_extslp_request;
    uint64_t mask = 1;

    printk("[SLP] lock extslp handle list : \r\n");
    printk("[SLP] lock_extslp_request = 0x%x\r\n",(uint32_t) lock_extslp_request);
    for (i = 0; i < SLEEP_LOCK_HANDLE_MAX; i++) {
        if (lock_extslp_request & (mask << i)) {
            printk("[SLP] index of extslp handle = %d\r\n", i);
            if (i >= SLEEP_LOCK_EXTEND_USER_START_ID) {
                // SLEEP_MANAGER_LOG_I("[SLP] extslp handle = %s\r\n", sleep_management_extslp_handle.user_handle_name[i - SLEEP_LOCK_EXTEND_USER_START_ID]);
            #if defined(AIR_LOGGING_ENABLE)
                print_module_log(NULL, NULL, 1, PRINT_LEVEL_INFO,"[SLP] extslp handle = %s\r\n", &sleep_management_extslp_handle.user_handle_name[i - SLEEP_LOCK_EXTEND_USER_START_ID][0]);
            #endif
            }
        }
    }
    return lock_extslp_request;
#else
    return 0xFFFFFFF; /* Disable SLP handle, all modules lock extend sleep */
#endif
}

bool sleep_management_check_cmsys_request_extslp_status(void)
{
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    bool lock = (0x1 & *SPM_CFG_CMSYS_REQ_EXT_SLP);
    hal_nvic_restore_interrupt_mask(mask);

    return lock;
}

bool sleep_management_check_conn_request_extslp_status(void)
{
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    bool lock = (0x1 & *SPM_CFG_CONN_REQ_EXT_SLP);
    hal_nvic_restore_interrupt_mask(mask);

    return lock;
}

void sleep_management_conn_lock_extslp(sleep_management_lock_extslp_t lock)
{
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *SPM_CFG_CONN_REQ_EXT_SLP = lock;
    hal_nvic_restore_interrupt_mask(mask);
}


#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
#include "hal_gpt.h"
#define CLOCK_SOURCE_32K_FREQ   32.768
uint32_t sleep_handle_total_lock_sleep_time[SLEEP_LOCK_HANDLE_MAX];
uint32_t sleep_handle_total_lock_sleep_count[SLEEP_LOCK_HANDLE_MAX];
uint32_t sleep_backup_fun_time[SLEEP_BACKUP_RESTORE_MODULE_MAX + SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX];
uint32_t sleep_restore_fun_time[SLEEP_BACKUP_RESTORE_MODULE_MAX + SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX];

void sleep_management_debug_lock_sleep_timelog(sleep_management_lock_sleep_t lock, uint8_t handle_index)
{
#ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
    static uint32_t lock_sleep_time[SLEEP_LOCK_HANDLE_MAX], unlock_sleep_time;

    if (lock == LOCK_SLEEP) {
        if (sleep_management_handle.lock_sleep_request_count[handle_index] == 1) {
            #ifdef HAL_RTC_MODULE_ENABLED
            lock_sleep_time[handle_index] = hal_rtc_get_current(HAL_MCU_RTC_TIME); /* Get rtc 32k count */
            #endif
        }
        sleep_handle_total_lock_sleep_count[handle_index]++;
    } else {
        #ifdef HAL_RTC_MODULE_ENABLED
        unlock_sleep_time = hal_rtc_get_current(HAL_MCU_RTC_TIME); /* Get rtc 32k count */
        #endif

        if (unlock_sleep_time >= lock_sleep_time[handle_index]) {
            sleep_handle_total_lock_sleep_time[handle_index] += unlock_sleep_time - lock_sleep_time[handle_index];
        } else {
            sleep_handle_total_lock_sleep_time[handle_index] += unlock_sleep_time + (0xFFFFFFFF - lock_sleep_time[handle_index]);
        }
    }
#endif
}

void sleep_management_debug_backup_restore_fun_timelog(uint32_t type, uint32_t order, uint32_t callback)
{
    static  uint32_t enter, exit;

    if (order == 0) {
        #ifdef HAL_RTC_MODULE_ENABLED
        enter = hal_rtc_get_current(HAL_MCU_RTC_TIME); /* Get rtc 32k count */
        #endif
    } else {
        #ifdef HAL_RTC_MODULE_ENABLED
        exit = hal_rtc_get_current(HAL_MCU_RTC_TIME); /* Get rtc 32k count */
        #endif
        if (exit >= enter) {
            exit = exit - enter;
        } else {
            exit = exit + (0xFFFFFFFF - enter);
        }
        if (type == 0) {
            sleep_backup_fun_time[callback] = exit;
        } else {
            sleep_restore_fun_time[callback] = exit;
        }
    }

}

void sleep_management_debug_dump_lock_sleep_time(void)
{
#ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
    uint32_t i;
    double lock_time;

    log_hal_msgid_info("\r\ndump lock sleep time : \r\n", 0);
    for (i = 0; i < SLEEP_LOCK_HANDLE_MAX; i++) {
        if (sleep_handle_total_lock_sleep_count[i] > 0) {
            if (i < SLEEP_LOCK_USER_START_ID) {
                sleep_management_dump_sleep_handle_name(i);
            } else {
                log_hal_msgid_info("sleep handle=%d,%s\r\n", 2, (int)i, (char *)&sleep_management_handle.user_handle_name[i - SLEEP_LOCK_USER_START_ID][0]);
            #if defined(AIR_LOGGING_ENABLE)
                print_module_log(NULL, NULL, 1, PRINT_LEVEL_INFO,"[SLP] sleep handle = %s\r\n", &&sleep_management_handle.user_handle_name[i - SLEEP_LOCK_USER_START_ID][0]);
            #endif
            }
            log_hal_msgid_info("count : %d\r\n", 1, (int)sleep_handle_total_lock_sleep_count[i]);

            lock_time = ((double)sleep_handle_total_lock_sleep_time[i]);
            lock_time = (lock_time) / CLOCK_SOURCE_32K_FREQ;
            if (lock_time < 1) {
                log_hal_msgid_info("total lock time : %d us,%d\r\n", 2, (int)lock_time * 1000, (int)sleep_handle_total_lock_sleep_time[i]);
            } else if (lock_time >= 1) {
                log_hal_msgid_info("total lock time : %d ms,%d\r\n", 2, (int)lock_time, (int)sleep_handle_total_lock_sleep_time[i]);
            }
            log_hal_msgid_info("\r\n", 0);
        }
    }
#endif
}

void sleep_management_debug_reset_lock_sleep_time(void)
{
    uint32_t i;

    for (i = 0; i < SLEEP_LOCK_HANDLE_MAX; i++) {
        sleep_handle_total_lock_sleep_time[i] = 0;
        sleep_handle_total_lock_sleep_count[i] = 0;
    }
}

void sleep_management_debug_dump_backup_restore_time(void)
{
    uint32_t i;
    double time;

    log_hal_msgid_info("\r\ndump backup restore function execute time : \r\n", 0);
    for (i = 0; i < SLEEP_BACKUP_RESTORE_MODULE_MAX; i++) {
        time = (((double)sleep_backup_fun_time[i] * 1000) / CLOCK_SOURCE_32K_FREQ);
        log_hal_msgid_info("backup fun[%d]  : %d us,%d\r\n", 3, (int)i, (int)time, (int)sleep_backup_fun_time[i]);

        time = (((double)sleep_restore_fun_time[i] * 1000) / CLOCK_SOURCE_32K_FREQ);
        log_hal_msgid_info("restore fun[%d] : %d us,%d\r\n", 3, (int)i, (int)time, (int)sleep_restore_fun_time[i]);
    }
}

void sleep_management_dump_wakeup_source(uint32_t eint_num1, uint32_t eint_num2)
{
    if (sleep_management_status.wakeup_source == 0xFFFFFFFF) {
        // printk("No pass through sleep/wakeup\r\n");
        return;
    }

    if (sleep_management_status.abort_sleep != 0) {
        printk("[Sleep]Abort Deep Sleep\r\n");
        sleep_management_status.abort_sleep = 0;
    }

    printk("===============Wakeup from Deep Sleep===============\r\n", 0);
    printk("[SLP]WAKEUP_SOURCE = 0x%x\r\n", sleep_management_status.wakeup_source);
    if ((sleep_management_status.wakeup_source & (0x1 << HAL_SLEEP_MANAGER_WAKEUP_SOURCE_EINT)) == 0) {
        printk("[SLP]WAKEUP_SOURCE EINT 0 to 31 = 0x%x\r\n", eint_num1);
        printk("[SLP]WAKEUP_SOURCE EINT 32 to 55 = 0x%x\r\n", eint_num2);
    }
    sleep_management_status.wakeup_source = 0xFFFFFFFF;
}

#endif

#endif
