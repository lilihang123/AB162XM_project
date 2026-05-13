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



/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stdint.h"
#include "syslog.h"
#include "hal_sleep_manager_internal.h"
#include "hal_sleep_manager.h"
#include "hal_spm.h"
#include "hal_nvic.h"

#if defined(HAL_SLEEP_MANAGER_ENABLED)

/* Private define ------------------------------------------------------------*/
#define BOOT_SLAVE_VECT_REG 0x422E0010
#define BOOT_SLAVE_SECLET_REG 0x422E0014

#define sleep_management_backup_context() \
{ \
    asm volatile (  "csrrw x0, mscratch, x10\n" \
                    "la x10, sleep_management_context\n" \
                    /* save x1 - x9, x12 - x15 */ \
                    "sw x1, 0(x10)\n" \
                    "sw x2, 4(x10)\n" \
                    "sw x3, 8(x10)\n" \
                    "sw x4, 12(x10)\n" \
                    "sw x5, 16(x10)\n" \
                    "sw x6, 20(x10)\n" \
                    "sw x7, 24(x10)\n" \
                    "sw x8, 28(x10)\n" \
                    "sw x9, 32(x10)\n" \
                    "sw x12, 44(x10)\n" \
                    "sw x13, 48(x10)\n" \
                    "sw x14, 52(x10)\n" \
                    "sw x15, 56(x10)\n" \
                    /* save x11 */ \
                    "sw x11, 40(x10)\n" \
                    /* save mtvec */ \
                    "csrrs x11, mtvec, x0\n" \
                    "sw x11, 68(x10)\n" \
                    /* save mstatus */ \
                    "csrrs x11, mstatus, x0\n" \
                    "sw x11, 60(x10)\n" \
                    /* save mie */ \
                    "csrrs x11, mie, x0\n" \
                    "sw x11, 64(x10)\n" \
                    /* save x10 */ \
                    "csrrs x11, mscratch, x0\n" \
                    "sw x11, 36(x10)\n" \
                    ); \
} \

#define sleep_management_restore_context() \
{ \
    asm volatile (  "la x10, sleep_management_context\n" \
                    /* restore x1 - x9, x12 - x15 */ \
                    "lw x1, 0(x10)\n" \
                    "lw x2, 4(x10)\n" \
                    "lw x3, 8(x10)\n" \
                    "lw x4, 12(x10)\n" \
                    "lw x5, 16(x10)\n" \
                    "lw x6, 20(x10)\n" \
                    "lw x7, 24(x10)\n" \
                    "lw x8, 28(x10)\n" \
                    "lw x9, 32(x10)\n" \
                    "lw x11, 40(x10)\n" \
                    "lw x12, 44(x10)\n" \
                    "lw x13, 48(x10)\n" \
                    "lw x14, 52(x10)\n" \
                    "lw x15, 56(x10)\n" \
                    /* restore mtvec */ \
                    "lw x11, 68(x10)\n" \
                    "csrrw x0, mtvec, x11\n" \
                    /* restore mstatus */ \
                    "lw x11, 60(x10)\n" \
                    "csrrw x0, mstatus, x11\n" \
                    /* restore mie */ \
                    "lw x11, 64(x10)\n" \
                    "csrrw x0, mie, x11\n" \
                    /* restore x11 */ \
                    "lw x11, 40(x10)\n" \
                    /* restore x10 */ \
                    "lw x10, 36(x10)\n" \
                    ); \
} \


/* Private typedef -----------------------------------------------------------*/
typedef struct {
    uint32_t x1;
    uint32_t x2;
    uint32_t x3;
    uint32_t x4;
    uint32_t x5;
    uint32_t x6;
    uint32_t x7;
    uint32_t x8;
    uint32_t x9;
    uint32_t x10;
    uint32_t x11;
    uint32_t x12;
    uint32_t x13;
    uint32_t x14;
    uint32_t x15;
    uint32_t mstatus;
    uint32_t mie;
    uint32_t mtvec;
} sleep_context_t;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static sleep_management_handle_t sleep_management_handle = {
    .lock_sleep_request = 0,
    .user_handle_resoure = 0,
    .user_handle_count = 0
};
sleep_context_t sleep_management_context;
uint32_t sleep_management_mask;
static sleep_management_suspend_callback_func_t    suspend_callback_func_table      [SLEEP_BACKUP_RESTORE_MODULE_MAX];
static sleep_management_resume_callback_func_t     resume_callback_func_table       [SLEEP_BACKUP_RESTORE_MODULE_MAX];
static sleep_management_suspend_callback_func_t    suspend_user_callback_func_table [SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX];
static sleep_management_resume_callback_func_t     resume_user_callback_func_table  [SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX];
static uint32_t suspend_user_register_count = 0, resume_user_register_count = 0;
/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

void sleep_management_enter_sleep(void)
{
    /* enter sleep */
    asm volatile ( /* enter sleep */
                    "wfi\n"
                    /* exit sleep */
                    "nop\n"
                );
}

void sleep_management_enter_deep_sleep(void)
{
    (void)sleep_management_context;
    uint32_t mie_value, mip_value, mstatus_value;

    /* disable interrupts and backup mstatus.mie */
    hal_nvic_save_and_set_interrupt_mask(&sleep_management_mask);
    /* send sleep request to SPM */
    SPM_SET_RISCV_SW_STATE(0x1);
    sleep_management_suspend_callback();
    SPM_SET_RISCV_SW_STATE(0x2);
    *IBEX_DEEP_SLEEP |= 0x100;
    SPM_SET_RISCV_SW_STATE(0x3);
    /* backup context */
    sleep_management_backup_context();

    asm volatile ("csrr %0, mie" : "=r" (mie_value));  /* mie: riscv irq_number ENABLE status */ 
    asm volatile ("csrr %0, mip" : "=r" (mip_value));  /* mip: riscv irq_number PENDING status */ 
    asm volatile ("csrr %0, mstatus" : "=r" (mstatus_value)); /* mstatus: riscv irq DISABLE/ENABLE status */
    // LOG_MSGID_I(common, "[SLP] dsp mstatus = 0x%08x, mie = 0x%08x, mip=0x%08x",3 , mstatus_value, mie_value,  mip_value);

    /* Must not add any code here */
    /* enter sleep */
    asm volatile (  /* set boot_slave to the next insturction after wfi */
                    "li x10, %0\n"
                    "li x11, 0x3\n"
                    "sw x11, 4(x10)\n"
                    "la x11, 1f\n"
                    "sw x11, 0(x10)\n"
                    /* synchronize the instruction and data streams  */
                    "fence.i\n"
                    /* enter sleep */
                    "wfi\n"
                    /* exit sleep */
                    "1:"
                    "nop\n"
                    : :"i"(BOOT_SLAVE_VECT_REG)
                );
    /* Must not add any code here */
    asm volatile ("csrr %0, mie" : "=r" (mie_value));  /* mie: riscv irq_number ENABLE status */ 
    asm volatile ("csrr %0, mip" : "=r" (mip_value));  /* mip: riscv irq_number PENDING status */ 
    asm volatile ("csrr %0, mstatus" : "=r" (mstatus_value)); /* mstatus: riscv irq DISABLE/ENABLE status */ 
    /* restore context */
    sleep_management_restore_context();
    SPM_SET_RISCV_SW_STATE(0x4);
    *IBEX_DEEP_SLEEP &= ~0x100;
    sleep_management_resume_callback();
    SPM_SET_RISCV_SW_STATE(0x5);
    LOG_MSGID_I(common, "[SLP] dsp deep sleep exit, wakeup source = 0x%08x",1 , *SPM_CFG_RISCV_WAKEUP_SOURCE_STA);
    LOG_MSGID_I(common, "[SLP][wakeup] dsp mstatus = 0x%08x, mie = 0x%08x, mip=0x%08x",3 , mstatus_value, mie_value,  mip_value);
    // LOG_MSGID_I(common, "[SLP][enterSLP] *SPM_CFG_IBEX_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n", 2,(uint32_t)SPM_CFG_IBEX_WAKEUP_SOURCE_MASK, *SPM_CFG_IBEX_WAKEUP_SOURCE_MASK);

    /* restore mstatus.mie */
    hal_nvic_restore_interrupt_mask(sleep_management_mask);
    SPM_SET_RISCV_SW_STATE(0x6);
}

void sleep_management_register_suspend_callback(sleep_management_backup_restore_module_t module, sleep_management_suspend_callback_t callback, void *data)
{
    if (module == SLEEP_BACKUP_RESTORE_USER) {
        if (suspend_user_register_count < SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX) {
            suspend_user_callback_func_table[suspend_user_register_count].func        = callback;
            suspend_user_callback_func_table[suspend_user_register_count].data        = data;
            suspend_user_callback_func_table[suspend_user_register_count].init_status = SLEEP_MANAGEMENT_INITIALIZED;
            suspend_user_register_count++;
        } else {
            LOG_MSGID_E(common,"register suspend callback function overflow\r\n", 0);
        }
    } else {
        suspend_callback_func_table[module].func        = callback;
        suspend_callback_func_table[module].data        = data;
        suspend_callback_func_table[module].init_status = SLEEP_MANAGEMENT_INITIALIZED;
    }
}

void sleep_management_register_resume_callback(sleep_management_backup_restore_module_t module, sleep_management_resume_callback_t callback, void *data)
{
    if (module == SLEEP_BACKUP_RESTORE_USER) {
        if (resume_user_register_count < SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX) {
            resume_user_callback_func_table[resume_user_register_count].func        = callback;
            resume_user_callback_func_table[resume_user_register_count].data        = data;
            resume_user_callback_func_table[resume_user_register_count].init_status = SLEEP_MANAGEMENT_INITIALIZED;
            resume_user_register_count++;
        } else {
            LOG_MSGID_E(common,"register resume callback function overflow\r\n", 0);
        }
    } else {
        resume_callback_func_table[module].func = callback;
        resume_callback_func_table[module].data = data;
        resume_callback_func_table[module].init_status = SLEEP_MANAGEMENT_INITIALIZED;
    }
}

void sleep_management_suspend_callback()
{
    static uint32_t i;

    for (i = 0; i < SLEEP_BACKUP_RESTORE_MODULE_MAX; i++) {
        if (suspend_callback_func_table[i].init_status == SLEEP_MANAGEMENT_INITIALIZED) {

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(0, 0, i);
#endif

            suspend_callback_func_table[i].func(suspend_callback_func_table[i].data);

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(0, 1, i);
#endif
        }
    }

    for (i = 0; i < SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX; i++) {
        if (suspend_user_callback_func_table[i].init_status == SLEEP_MANAGEMENT_INITIALIZED) {

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 0, i + SLEEP_BACKUP_RESTORE_MODULE_MAX);
#endif

            suspend_user_callback_func_table[i].func(suspend_user_callback_func_table[i].data);

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 1, i + SLEEP_BACKUP_RESTORE_MODULE_MAX);
#endif
        }
    }
}

void sleep_management_resume_callback()
{
    static uint32_t i;

    for (i = 0; i < SLEEP_BACKUP_RESTORE_MODULE_MAX; i++) {
        if (resume_callback_func_table[i].init_status == SLEEP_MANAGEMENT_INITIALIZED) {

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 0, i);
#endif
            resume_callback_func_table[i].func(resume_callback_func_table[i].data);

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 1, i);
#endif
        }
    }

    for (i = 0; i < SLEEP_BACKUP_RESTORE_USER_CALLBACK_FUNC_MAX; i++) {
        if (resume_user_callback_func_table[i].init_status == SLEEP_MANAGEMENT_INITIALIZED) {

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 0, i + SLEEP_BACKUP_RESTORE_MODULE_MAX);
#endif

            resume_user_callback_func_table[i].func(resume_user_callback_func_table[i].data);

#ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
            sleep_management_debug_backup_restore_fun_timelog(1, 1, i + SLEEP_BACKUP_RESTORE_MODULE_MAX);
#endif
        }
    }
}

uint8_t sleep_management_get_lock_handle(const char *handle_name)
{
    uint8_t index = 0;
    uint8_t i;
    uint32_t mask, name_len;

    for (index = 0 ; index < SLEEP_LOCK_HANDLE_USER_MAX; index++) {
        hal_nvic_save_and_set_interrupt_mask(&mask);

        if (((sleep_management_handle.user_handle_resoure >> index) & 0x01) == 0) {

            sleep_management_handle.user_handle_resoure |= (1 << index);
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
                LOG_MSGID_E(common,"sleep handle name error\r\n", 0);
                // assert(0);
            }
            for (i = 0; i < name_len; i++) {
                if ((sleep_management_handle.user_handle_name[index][i] <= 0x20) || (sleep_management_handle.user_handle_name[index][i] >= 0x7E)) {
                    LOG_MSGID_E(common,"sleep handle name error\r\n", 0);
                    // assert(0);
                }
            }
            break;
        } else {
            hal_nvic_restore_interrupt_mask(mask);
        }
    }

    //LOG_MSGID_I(common,"sleep handle name : %s\r\n", 1, &sleep_management_handle.user_handle_name[index][0]);
    if (index >= SLEEP_LOCK_HANDLE_USER_MAX) {
        LOG_MSGID_E(common,"cannot get sleep handle\r\n", 0);
        // assert(0);
        return (SLEEP_LOCK_INVALID_ID);
    }

    index += SLEEP_LOCK_USER_START_ID;

    return (index);
}

void sleep_management_release_lock_handle(uint8_t handle_index)
{
    uint32_t mask;
    /*  check handle index range */
    if ((handle_index >= SLEEP_LOCK_HANDLE_MAX) || (handle_index < SLEEP_LOCK_USER_START_ID)) {
        LOG_MSGID_E(common,"sleep handle index error\r\n", 0);
        return;
    }

    handle_index -= SLEEP_LOCK_USER_START_ID;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    if (((sleep_management_handle.user_handle_resoure >> handle_index) & 0x01) == 1) {
        sleep_management_handle.user_handle_count--;
        sleep_management_handle.user_handle_resoure &= ~(1 << handle_index);
        memset(&sleep_management_handle.user_handle_name[handle_index][0], 0, SLEEP_HANDLE_NAME_LEN);
    } else {
        LOG_MSGID_W(common,"sleep handle already release \r\n", 0);
    }
    hal_nvic_restore_interrupt_mask(mask);

    return;
}

void sleep_management_lock_sleep(sleep_management_lock_sleep_t lock, uint8_t handle_index)
{
    uint32_t mask;
    uint64_t shift = 1;

    if (handle_index >= SLEEP_LOCK_HANDLE_MAX) {
        LOG_MSGID_E(common,"sleep handle index error\r\n", 0);
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
            LOG_MSGID_W(common,"sleep handle=%d,lock sleep count full \r\n", 1, handle_index);
            if (handle_index >= SLEEP_LOCK_USER_START_ID) {
                LOG_MSGID_W(common,"sleep handle=%s\r\n", 1, sleep_management_handle.user_handle_name[(handle_index - SLEEP_LOCK_USER_START_ID)]);
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
            LOG_MSGID_W(common,"sleep handle=%d,lock sleep has already released \r\n", 1, handle_index);
            if (handle_index >= SLEEP_LOCK_USER_START_ID) {
                LOG_MSGID_W(common,"sleep handle=%s", 1, sleep_management_handle.user_handle_name[(handle_index - SLEEP_LOCK_USER_START_ID)]);
            }
        }
    }
    //LOG_MSGID_I(common,"[SLP]lock sleep handle=0x%x, lock index=0x%x, lock_sleep_request=0x%x", 3, lock, handle_index, sleep_management_handle.lock_sleep_request);

    return;
}

bool sleep_management_check_sleep_locks(void)
{
    bool lock = true;
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

    return lock;
}

bool sleep_management_check_handle_status(uint8_t handle_index)
{
    bool lock = false;

    /*  check handle index range */
    if ((handle_index >= SLEEP_LOCK_HANDLE_MAX)) {
        LOG_MSGID_E(common,"sleep handle index error\r\n", 0);
        return false;
    }

    if (((sleep_management_handle.lock_sleep_request >> (handle_index)) & 0x01) == 1) {
        lock = true;
        return lock;
    } else {
        lock = false;
        return lock;
    }

    return lock;
}

uint64_t sleep_management_get_lock_sleep_request_info(void)
{
    return sleep_management_handle.lock_sleep_request;
}

uint64_t sleep_management_get_lock_sleep_handle_list(void)
{
    uint8_t i;
    uint64_t lock_sleep_request = sleep_management_handle.lock_sleep_request;
    uint64_t mask = 1;

    LOG_MSGID_I(common,"lock sleep handle list : \r\n", 0);
    for (i = 0; i < SLEEP_LOCK_HANDLE_MAX; i++) {
        if (lock_sleep_request & (mask << i)) {
            LOG_MSGID_I(common,"index of sleep handle = %d\r\n", 1, i);
            if (i >= SLEEP_LOCK_USER_START_ID) {
                LOG_MSGID_I(common,"sleep handle = %s\r\n", 1, sleep_management_handle.user_handle_name[i - SLEEP_LOCK_USER_START_ID]);
            }
        }
    }
    return lock_sleep_request;
}

uint8_t sleep_management_get_lock_extslp_handle(const char *handle_name)
{
    uint8_t index = 0;


// #ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
//     uint8_t i;
//     uint32_t mask, name_len;

//     for (index = 0 ; index < SLEEP_LOCK_HANDLE_USER_MAX; index++) {
//         hal_nvic_save_and_set_interrupt_mask(&mask);

//         if (((sleep_management_handle.user_handle_resoure >> index) & 0x01) == 0) {

//             sleep_management_handle.user_handle_resoure |= (1 << index);
//             sleep_management_handle.user_handle_count++;

//             hal_nvic_restore_interrupt_mask(mask);

//             memset(&sleep_management_handle.user_handle_name[index][0], 0, SLEEP_HANDLE_NAME_LEN);
//             name_len = strlen(handle_name);

//             if (name_len >= SLEEP_HANDLE_NAME_LEN) {
//                 name_len = SLEEP_HANDLE_NAME_LEN - 1;
//             }
//             memcpy(&sleep_management_handle.user_handle_name[index][0], handle_name, name_len);

//             /* Check handle name */
//             if (name_len == 0) {
//                 log_hal_msgid_error("[Sleep Management]sleep handle name error\r\n", 0);
//                 assert(0);
//             }
//             for (i = 0; i < name_len; i++) {
//                 if ((sleep_management_handle.user_handle_name[index][i] <= 0x20) || (sleep_management_handle.user_handle_name[index][i] >= 0x7E)) {
//                     log_hal_msgid_error("[Sleep Management]sleep handle name error\r\n", 0);
//                     assert(0);
//                 }
//             }
//             break;
//         } else {
//             hal_nvic_restore_interrupt_mask(mask);
//         }
//     }

//     //log_hal_msgid_info("[Sleep Management]sleep handle name : %s\r\n", 1, &sleep_management_handle.user_handle_name[index][0]);
//     if (index >= SLEEP_LOCK_HANDLE_USER_MAX) {
//         log_hal_msgid_error("[Sleep Management]cannot get sleep handle\r\n", 0);
//         assert(0);
//         return (SLEEP_LOCK_INVALID_ID);
//     }

//     index += SLEEP_LOCK_USER_START_ID;
// #endif

    return (index);
}

void sleep_management_release_lock_extslp_handle(uint8_t handle_index)
{
// #ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
//     uint32_t mask;
//     /*  check handle index range */
//     if ((handle_index >= SLEEP_LOCK_HANDLE_MAX) || (handle_index < SLEEP_LOCK_USER_START_ID)) {
//         log_hal_msgid_error("[Sleep Management]sleep handle index error\r\n", 0);
//         return;
//     }

//     handle_index -= SLEEP_LOCK_USER_START_ID;

//     hal_nvic_save_and_set_interrupt_mask(&mask);
//     if (((sleep_management_handle.user_handle_resoure >> handle_index) & 0x01) == 1) {
//         sleep_management_handle.user_handle_count--;
//         sleep_management_handle.user_handle_resoure &= ~(1 << handle_index);
//         memset(&sleep_management_handle.user_handle_name[handle_index][0], 0, SLEEP_HANDLE_NAME_LEN);
//     } else {
//         log_hal_msgid_warning("[Sleep Management]sleep handle already release \r\n", 0);
//     }
//     hal_nvic_restore_interrupt_mask(mask);
// #endif
    return;
}

void sleep_management_lock_extslp(sleep_management_lock_extslp_t lock, uint8_t handle_index)
{
// #ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
//     uint32_t mask;
//     uint64_t shift = 1;

//     if (handle_index >= SLEEP_LOCK_HANDLE_MAX) {
//         log_hal_msgid_error("[Sleep Management]sleep handle index error\r\n", 0);
//         return;
//     }

//     if (lock == LOCK_SLEEP) {
//         /* Lock sleep request */
//         hal_nvic_save_and_set_interrupt_mask(&mask);
//         if (sleep_management_handle.lock_sleep_request_count[handle_index] < 0xFF) {
//             sleep_management_handle.lock_sleep_request_count[handle_index]++;
//             shift <<= handle_index;
//             sleep_management_handle.lock_sleep_request |= shift;

//         }
//         hal_nvic_restore_interrupt_mask(mask);
// #ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
//         sleep_management_debug_lock_sleep_timelog(lock, handle_index);
// #endif
//         if (sleep_management_handle.lock_sleep_request_count[handle_index] == 0xFF) {
//             if (handle_index < SLEEP_LOCK_USER_START_ID) {
//                 log_hal_msgid_warning("[Sleep Management]sleep handle=%d,lock sleep count full \r\n", 1, handle_index);
//             } else {
//                 SLEEP_MANAGER_MSGID_W("[Sleep Management]sleep handle=%d, lock sleep count full\r\n", 1, handle_index);
//                 SLEEP_MANAGER_LOG_W("[Sleep Management]sleep handle=%s\r\n", sleep_management_handle.user_handle_name[(handle_index - SLEEP_LOCK_USER_START_ID)]);
//             }
//         }

//     } else {
//         /* Unlock sleep request */
//         hal_nvic_save_and_set_interrupt_mask(&mask);
//         if (sleep_management_handle.lock_sleep_request_count[handle_index] > 0) {
//             sleep_management_handle.lock_sleep_request_count[handle_index]--;
//             if (sleep_management_handle.lock_sleep_request_count[handle_index] == 0) {
//                 shift <<= handle_index;
//                 sleep_management_handle.lock_sleep_request &= ~shift;

// #ifdef  SLEEP_MANAGEMENT_DEBUG_ENABLE
//                 sleep_management_debug_lock_sleep_timelog(lock, handle_index);
// #endif
//             }
//             hal_nvic_restore_interrupt_mask(mask);
//         } else {
//             hal_nvic_restore_interrupt_mask(mask);
//             if (handle_index < SLEEP_LOCK_USER_START_ID) {
//                 log_hal_msgid_warning("[Sleep Management]sleep handle=%d,lock sleep has already released \r\n", 1, handle_index);
//             } else {
//                 SLEEP_MANAGER_MSGID_W("[Sleep Management]sleep handle=%d, lock sleep has already released\r\n", 1, handle_index);
//                 SLEEP_MANAGER_LOG_W("[Sleep Management]sleep handle=%s", sleep_management_handle.user_handle_name[(handle_index - SLEEP_LOCK_USER_START_ID)]);
//             }
//         }
//     }
//     //SLEEP_MANAGER_MSGID_I("[Sleep Management] lock sleep handle=0x%x, lock index=0x%x, lock_sleep_request=0x%x", 3, lock, handle_index, sleep_management_handle.lock_sleep_request);
// #endif
    return;
}

bool sleep_management_check_extslp_locks(void)
{
    bool lock = false;

// #ifndef  SLEEP_MANAGEMENT_CM33_SLEEP_DISABLE
//     uint32_t mask;
//     uint64_t sleep_handle_mask = 1;

//     sleep_handle_mask <<= (SLEEP_LOCK_HANDLE_MAX - 1);
//     sleep_handle_mask -= 1;

//     hal_nvic_save_and_set_interrupt_mask(&mask);
//     if ((sleep_management_handle.lock_sleep_request & sleep_handle_mask) == 0) {
//         lock = false;
//     } else {
//         lock = true;
//     }
//     hal_nvic_restore_interrupt_mask(mask);
// #endif
    return lock;
}

bool sleep_management_check_request_extslp_status()
{
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    bool lock = (0x1 & *SPM_CFG_IBEX_REQ_EXT_SLP);
    hal_nvic_restore_interrupt_mask(mask);

    return lock;
}

#endif /* HAL_SLEEP_MANAGER_ENABLED */
