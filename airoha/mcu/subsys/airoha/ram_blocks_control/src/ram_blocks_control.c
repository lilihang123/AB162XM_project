/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
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

#if defined(AIR_RAM_BLOCKS_CONTROL_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include "assert.h"
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include "hal_nvic.h"
#include "ram_blocks_control.h"
#include "memory_attribute.h"
#include "hal_spm.h"

/* Private define ------------------------------------------------------------*/
#define thisMODULE ram_blocks_control
LOG_MODULE_REGISTER(thisMODULE);

#define RAM_BLOCK_SIZE_UINT             (32*1024)
#define RAM_SIZE                        (384*1024)

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t ram_blocks_non_retention_count;
static bool ram_blocks_non_retention_off;
static void *s_threads_stack_backup;

/* Public variables ----------------------------------------------------------*/
extern uint32_t _ram_non_retention_start;
extern uint32_t _tcm_text_end;
extern uint32_t _tcm_text_load;
extern uint32_t _tcm_rw_data_non_retention_load;
extern uint32_t _tcm_rw_data_non_retention_start;
extern uint32_t _tcm_rw_data_non_retention_end;
extern uint32_t _tcm_zi_data_non_retention_start;
extern uint32_t _tcm_zi_data_non_retention_end;
extern uint32_t _ram_non_retention_end;
extern uint32_t _image_ram_start;
extern uint32_t _image_ram_end;

extern uint32_t _tcm_rw_bt_data_non_retention_load;
extern uint32_t _tcm_rw_bt_data_non_retention_start;
extern uint32_t _tcm_rw_bt_data_non_retention_end;
extern uint32_t _tcm_zi_bt_data_non_retention_start;
extern uint32_t _tcm_zi_bt_data_non_retention_end;



/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
int ram_blocks_control_bt_rw_data_non_retention_reinit(void)
{
    uint32_t load = (uint32_t)(&_tcm_rw_bt_data_non_retention_load);
    uint32_t start = (uint32_t)(&_tcm_rw_bt_data_non_retention_start);
    uint32_t end = (uint32_t)(&_tcm_rw_bt_data_non_retention_end);
    size_t size = end - start;
    memcpy((void*)start, (void*)load, size);
    return 0;
}

int ram_blocks_control_bt_zi_data_non_retention_reinit(void)
{
    uint32_t start = (uint32_t)(&_tcm_zi_bt_data_non_retention_start);
    uint32_t end = (uint32_t)(&_tcm_zi_bt_data_non_retention_end);
    size_t size = end - start;
    memset((void*)start, 0, size);
    return 0;
}



int ram_blocks_control_non_retention_blocks_extend_sleep_off_prohibit(void)
{
    uint32_t mask;
    uint8_t count;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    ram_blocks_non_retention_count++;
    assert(ram_blocks_non_retention_count > 0);
    ram_blocks_non_retention_off = false;
    count = ram_blocks_non_retention_count;
    hal_nvic_restore_interrupt_mask(mask);

    LOG_INF("[ram_blocks_control] probihit non retention blocks extend-sleep off, count %u, LR 0x%x", count, (uint32_t)__builtin_return_address(0));

    return 0;
}

int ram_blocks_control_non_retention_blocks_extend_sleep_off_allow(void)
{
    uint32_t mask;
    uint8_t count;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    if (ram_blocks_non_retention_count > 0)
    {
        ram_blocks_non_retention_count--;
    }
    if (ram_blocks_non_retention_count == 0)
    {
        ram_blocks_non_retention_off = true;
    }
    count = ram_blocks_non_retention_count;
    hal_nvic_restore_interrupt_mask(mask);

    LOG_INF("[ram_blocks_control] allow non retention blocks extend-sleep off, count %u, LR 0x%x", count, (uint32_t)__builtin_return_address(0));

    return 0;
}

_Static_assert(IS_ENABLED(CONFIG_THREAD_STACK_INFO) == 1, \
    "Backup thread stacks depends on CONFIG_THREAD_STACK_INFO, please configure it properly.");

static bool is_idle_thread(const struct k_thread *thread)
{
    extern struct k_thread z_idle_threads[CONFIG_MP_MAX_NUM_CPUS];

    uint32_t idx;
    for(idx = 0; idx < CONFIG_MP_MAX_NUM_CPUS; idx++){
        if(thread == &z_idle_threads[idx]){
            return true;
        }
    }
    return false;
}

static void update_total_stack_size(const struct k_thread *thread, void *user_data)
{
    uint32_t *p_size = (uint32_t*)user_data;
    uint32_t stack_end, psp, used_stack_size;
    if(!is_idle_thread(thread)){
        stack_end = (uint32_t)(thread->stack_info.start) + thread->stack_info.size;
        psp = thread->callee_saved.psp;
        assert(psp < stack_end);
        used_stack_size = stack_end - psp;
        *p_size += used_stack_size;

        // LOG_INF("thread( %c%c%c%c%c%c%c%c ) with used stack size %d bytes",
        //     thread->name[0],
        //     thread->name[1],
        //     thread->name[2],
        //     thread->name[3],
        //     thread->name[4],
        //     thread->name[5],
        //     thread->name[6],
        //     thread->name[7],
        //     (int)used_stack_size
        // );
    }
}

// uint32_t backup_threads = 0;
// uint32_t restore_threads = 0;
static void backup_thread_stack(const struct k_thread *thread, void *user_data)
{
    char *p_dest = *((char**)user_data);
    uint32_t stack_end, psp, used_stack_size;
    if(!is_idle_thread(thread)){
        stack_end = (uint32_t)(thread->stack_info.start) + thread->stack_info.size;
        psp = thread->callee_saved.psp;
        assert(psp < stack_end);
        used_stack_size = stack_end - psp;

        // LOG_INF("backup thread( %c%c%c%c%c%c%c%c ) stack from 0x%08X to 0x%08X with length %d bytes",
        //     thread->name[0],
        //     thread->name[1],
        //     thread->name[2],
        //     thread->name[3],
        //     thread->name[4],
        //     thread->name[5],
        //     thread->name[6],
        //     thread->name[7],
        //     (unsigned int)psp,
        //     (unsigned int)p_dest,
        //     (int)used_stack_size
        // );
        // backup_threads++;
        memcpy((void*)p_dest, (void*)(psp), used_stack_size);
        *((char**)user_data) = p_dest + used_stack_size;
    }
}

static void restore_thread_stack(const struct k_thread *thread, void *user_data)
{
    char *p_src = *((char**)user_data);
    uint32_t stack_end, psp, used_stack_size;
    if(!is_idle_thread(thread)){
        stack_end = (uint32_t)(thread->stack_info.start) + thread->stack_info.size;
        psp = thread->callee_saved.psp;
        assert(psp < stack_end);
        used_stack_size = stack_end - psp;
        // LOG_INF("restore thread( %c%c%c%c%c%c%c%c ) stack from 0x%08X to 0x%08X with length %d bytes",
        //     thread->name[0],
        //     thread->name[1],
        //     thread->name[2],
        //     thread->name[3],
        //     thread->name[4],
        //     thread->name[5],
        //     thread->name[6],
        //     thread->name[7],
        //     (unsigned int)p_src,
        //     (unsigned int)psp,
        //     (int)used_stack_size
        // );
        // restore_threads++;
        memcpy((void*)(psp), (void*)p_src, used_stack_size);
        *((char**)user_data) = p_src + used_stack_size;
    }
}

/* Must be placed before PD Domain power down */
int ram_blocks_control_enter_extend_sleep(void)
{
    if (ram_blocks_non_retention_off)
    {
        /* Step 1: backup thread stacks into heap */
        uint32_t calc_stack_size_need_backup = 0;
        void *p_thread_stack_store_dest;
        k_thread_foreach(update_total_stack_size, (void*)(&calc_stack_size_need_backup));
        // LOG_INF("[ram_blocks_control] need %d bytes for backup thread stacks except idle", calc_stack_size_need_backup);
        s_threads_stack_backup = k_malloc(calc_stack_size_need_backup);
        assert(s_threads_stack_backup != NULL);
        p_thread_stack_store_dest = s_threads_stack_backup;
        k_thread_foreach(backup_thread_stack, (void*)(&p_thread_stack_store_dest));

        /* Step 2: power off the non-retention ram blocks */
        sysram_power_down_ram((uint32_t)&_ram_non_retention_start, (uint32_t)&_ram_non_retention_end);
    }

    return 0;
}

/* Must be placed after PD Domain power on */
int ram_blocks_control_exit_extend_sleep(void)
{
    if (ram_blocks_non_retention_off)
    {
        /* Step 1: power on the non-retention ram blocks */
        sysram_power_on_ram((uint32_t)&_ram_non_retention_start, (uint32_t)&_ram_non_retention_end);
        /* Step 2: power on PD domain for access flash(it will be done by sleep SW flow) */
        /* Step 3: reinit non-retention ram blocks */
        memcpy((void *)((uint32_t)&_ram_non_retention_start), (void *)((uint32_t)&_tcm_text_load), ((uint32_t)&_tcm_text_end) - ((uint32_t)&_ram_non_retention_start));
        memcpy((void *)((uint32_t)&_tcm_rw_data_non_retention_start), (void *)((uint32_t)&_tcm_rw_data_non_retention_load), ((uint32_t)&_tcm_rw_data_non_retention_end) - ((uint32_t)&_tcm_rw_data_non_retention_start));
        memset((void *)((uint32_t)&_tcm_zi_data_non_retention_start), 0, ((uint32_t)&_tcm_zi_data_non_retention_end) - ((uint32_t)&_tcm_zi_data_non_retention_start));

        /* Step 4: restore thread stacks from heap */
        assert(s_threads_stack_backup != NULL);
        void *p_thread_stack_restore_src = s_threads_stack_backup;
        k_thread_foreach(restore_thread_stack, (void*)(&p_thread_stack_restore_src));
        k_free(s_threads_stack_backup);
        s_threads_stack_backup = NULL;
    }

    return 0;
}

int ram_blocks_control_init(void)
{
    // uint32_t ram_used_size = ((uint32_t)&_image_ram_start) - ((uint32_t)&_image_ram_end);
    // uint32_t ram_used_block_num = (ram_used_size + RAM_BLOCK_SIZE_UINT - 1) / RAM_BLOCK_SIZE_UINT;

    LOG_INF("[ram_blocks_control] init start, ram start addr = 0x%x, ram end addr = 0x%x, non-retention ram start addr = 0x%x, non-retention ram end addr = 0x%x",
            (uint32_t)&_image_ram_start,
            (uint32_t)&_image_ram_end,
            (uint32_t)&_ram_non_retention_start,
            (uint32_t)&_ram_non_retention_end);

    /* power off(force off) the unused ram blocks */
    sysram_force_off_unused_ram((uint32_t)&_image_ram_start, (uint32_t)&_ram_non_retention_end);

    /* default prohibit non-retention ram block sleep off */
    ram_blocks_non_retention_off = false;

    LOG_INF("[ram_blocks_control] init done.");

    return 0;
}

SYS_INIT(ram_blocks_control_init, CONFIG_RAM_BLOCKS_CONTROL_INIT_LEVEL, CONFIG_RAM_BLOCKS_CONTROL_INIT_PRIORITY);

#endif /* AIR_RAM_BLOCKS_CONTROL_ENABLE */
