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

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <errno.h>
#include <zephyr/sys/math_extras.h>
#include <zephyr/sys/sys_heap.h>
#include <zephyr/sys/dlist.h>
#include <zephyr/types.h>
#include <zephyr/sys/util.h>

/* zephyr/lib/heap/heap.h */
#include "heap.h"

#include "memory_attribute.h"
#include "air_allocation_zephyr.h"

#define FREE_PTR_WORD_IDX_IN_CHUNK_UNIT 1
_Static_assert(CHUNK_UNIT == 8, "chunk_unit_t size may error, please check");
_Static_assert(FREE_PREV == 2, "chunk_unit_t structure may changed, please check");

#define AIR_HEAP_DBG_INFO_SIZE (sizeof(air_heap_used_info_t))
#define AIR_HEAP_DBG_INFO_CHUNK_SIZE (AIR_HEAP_DBG_INFO_SIZE/CHUNK_UNIT)

#define CHUNK_SIZE_SHIFT_BITS 17

#define AIR_HEAP_DBG_INFO_DEFAULT_RELEASER              0xDEADBEEF

_Static_assert(AIR_HEAP_DBG_INFO_SIZE % CHUNK_UNIT == 0, "air_heap_used_info_t should be multiple times of chunk_unit_t");

/* The linker will provide these symbols, but requires
 * explicit prototype hints for compiler to avoid
 * implicitly compilation warnings.
 * Heap APIs from zephyr/include/zephyr/kernel.h
 */
void __real_k_free(void *ptr);
void *__real_k_aligned_alloc(size_t align, size_t size);
void *__real_k_malloc(size_t size);
void *__real_k_calloc(size_t nmemb, size_t size);
void *__real_k_realloc(void *ptr, size_t size);

extern char kheap__system_heap[];

sys_dlist_t g_air_heap_used_list = SYS_DLIST_STATIC_INIT(&g_air_heap_used_list);

ATTR_WEAK_SYMBOL void application_alloc_failed_hook(void)
{
    __ASSERT(0, "memory allocation failed, please check heap usage/CONFIG_HEAP_MEM_POOL_SIZE/CONFIG_HEAP_MEM_POOL_ADD_SIZE* symbols");
}

// void air_heap_used_info_foreach(air_heap_used_info_cb_t fn, void *user_data)
// {
//     __ASSERT_NO_MSG(fn != NULL);
//     sys_dnode_t *p_info = NULL;

//     uint32_t irq_flag = arch_irq_lock();
//     SYS_DLIST_FOR_EACH_NODE((&g_air_heap_used_list), p_info) {
//         fn((const air_heap_used_info_t *)p_info, user_data);
//     }
//     arch_irq_unlock(irq_flag);
// }

static air_heap_used_info_t *calc_heap_info_by_buffer_ptr(void *ptr)
{
    char *p_temp = (char *)(ptr);
    uint32_t* p_chunk_record = (uint32_t *)((char*)ptr - CHUNK_UNIT);

    // printk("[Heap] p_chunk_record addr: 0x%08X, p_chunk_record: 0x%08X, p_temp: 0x%08X",
    //     (unsigned int)p_chunk_record,
    //     (unsigned int)(*p_chunk_record),
    //     (unsigned int)p_temp
    // );
    p_temp += (CHUNK_UNIT)*( \
        (p_chunk_record[0] >> CHUNK_SIZE_SHIFT_BITS) - \
        AIR_HEAP_DBG_INFO_CHUNK_SIZE - 1);

    // printk("[Heap] p_info: 0x%08X", (unsigned int)p_temp);
    return (air_heap_used_info_t *)p_temp;
}

// void print_heap_used_info(
//     const air_heap_used_info_t *ptr,
//     void *user_data
// )
// {
//     printk("[Heap] p_info addr: 0x%08X, allocator: 0x%08X, releaser: 0x%08X",
//         (unsigned int)ptr,
//         (unsigned int)ptr->allocator,
//         (unsigned int)ptr->releaser
//     );
//     ARG_UNUSED(user_data);

//     __ASSERT_NO_MSG(ptr->releaser == AIR_HEAP_DBG_INFO_DEFAULT_RELEASER);
// }

void* __wrap_k_malloc(size_t size)
{
    uint32_t reg_lr = (uint32_t)__builtin_return_address(0);
#ifndef K_HEAP_MEM_POOL_SIZE
    __ASSERT_NO_MSG(size < CONFIG_HEAP_MEM_POOL_SIZE);
#else
    __ASSERT_NO_MSG(size < K_HEAP_MEM_POOL_SIZE);
#endif

    /* !!! NOTE !!!
     * Because k_malloc and k_aligned_alloc are compiling in the same C file,
     * their calling relationship can't be wrapped.
     * 1. user call k_malloc, it was wrapper by call __wrap_k_malloc
     * 2. __wrap_k_malloc add size and then call __real_k_malloc(origin k_malloc)
     * 3. __real_k_malloc(origin k_malloc) call __real_k_aligned_alloc(origin k_aligned_alloc)
     *    rather than __wrap_k_aligned_alloc
     * The True call flows are:
     *   k_malloc -> __wrap_k_malloc -> __real_k_malloc -> __real_k_aligned_alloc
     * but our expectation is:
     *   k_malloc -> __wrap_k_malloc -> __real_k_malloc -> __wrap_k_aligned_alloc
     */

    size_t real_size = size + AIR_HEAP_DBG_INFO_SIZE;
    void *p_mem = __real_k_malloc(real_size);
    if(p_mem){
        uint32_t irq_flag = arch_irq_lock();
        air_heap_used_info_t *p_info = calc_heap_info_by_buffer_ptr(p_mem);
        sys_dnode_init(&(p_info->node));
        sys_dlist_append(&g_air_heap_used_list, &(p_info->node));
        p_info->allocator = reg_lr;
        p_info->releaser = AIR_HEAP_DBG_INFO_DEFAULT_RELEASER;
        // air_heap_used_info_foreach(print_heap_used_info, NULL);
        arch_irq_unlock(irq_flag);

        // printk("[Heap] 0x%08X allocated %d bytes(real_size %d) from 0x%08X",
        //     (unsigned int)reg_lr,
        //     size,
        //     real_size,
        //     (unsigned int)p_mem
        // );
    } else {
        application_alloc_failed_hook();
    }
    return p_mem;
}


void *__wrap_k_aligned_alloc(size_t alignment, size_t size)
{
    uint32_t reg_lr = (uint32_t)__builtin_return_address(0);
#ifndef K_HEAP_MEM_POOL_SIZE
    __ASSERT_NO_MSG(size < CONFIG_HEAP_MEM_POOL_SIZE);
#else
    __ASSERT_NO_MSG(size < K_HEAP_MEM_POOL_SIZE);
#endif

    size_t real_size = size + AIR_HEAP_DBG_INFO_SIZE;
    void *p_mem = __real_k_aligned_alloc(alignment, real_size);
    if(p_mem){
        uint32_t irq_flag = arch_irq_lock();
        air_heap_used_info_t *p_info = calc_heap_info_by_buffer_ptr(p_mem);
        sys_dnode_init(&(p_info->node));
        sys_dlist_append(&g_air_heap_used_list, &(p_info->node));
        p_info->allocator = reg_lr;
        p_info->releaser = AIR_HEAP_DBG_INFO_DEFAULT_RELEASER;
        // air_heap_used_info_foreach(print_heap_used_info, NULL);
        arch_irq_unlock(irq_flag);

        // printk("[Heap] 0x%08X allocated %d bytes(real_size %d) from 0x%08X with alignment %d",
        //     (unsigned int)reg_lr,
        //     size,
        //     real_size,
        //     (unsigned int)p_mem,
        //     alignment
        // );
    } else {
        application_alloc_failed_hook();
    }
    return p_mem;
}


void *__wrap_k_calloc(size_t nmemb, size_t size)
{
    uint32_t reg_lr = (uint32_t)__builtin_return_address(0);

    size_t bounds;
    if (size_mul_overflow(nmemb, size, &bounds)) {
        return NULL;
    }
    __ASSERT_NO_MSG(bounds < CONFIG_HEAP_MEM_POOL_SIZE);

    if (size_add_overflow(bounds, AIR_HEAP_DBG_INFO_SIZE, &bounds)){
        return NULL;
    }
#ifndef K_HEAP_MEM_POOL_SIZE
    __ASSERT_NO_MSG(bounds < CONFIG_HEAP_MEM_POOL_SIZE);
#else
    __ASSERT_NO_MSG(bounds < K_HEAP_MEM_POOL_SIZE);
#endif

    /* NOTE: __wrap_k_malloc will added size */
    // void *p_mem = __wrap_k_malloc(bounds);
    void *p_mem = __real_k_malloc(bounds);

    if(p_mem){
        (void*)memset(p_mem, 0, bounds);

        uint32_t irq_flag = arch_irq_lock();
        air_heap_used_info_t *p_info = calc_heap_info_by_buffer_ptr(p_mem);
        sys_dnode_init(&(p_info->node));
        sys_dlist_append(&g_air_heap_used_list, &(p_info->node));
        /* update the real allocator */
        p_info->allocator = reg_lr;
        p_info->releaser = AIR_HEAP_DBG_INFO_DEFAULT_RELEASER;
        // air_heap_used_info_foreach(print_heap_used_info, NULL);
        arch_irq_unlock(irq_flag);

        // printk("[Heap] 0x%08X allocated %d bytes from 0x%08X with %dx%d",
        //     (unsigned int)reg_lr,
        //     bounds,
        //     (unsigned int)p_mem,
        //     nmemb,
        //     size
        // );
    } else {
        application_alloc_failed_hook();
    }
    return p_mem;
}


void *__wrap_k_realloc(void *ptr, size_t size)
{
    uint32_t reg_lr = (uint32_t)__builtin_return_address(0);
#ifndef K_HEAP_MEM_POOL_SIZE
    __ASSERT_NO_MSG(size < CONFIG_HEAP_MEM_POOL_SIZE);
#else
    __ASSERT_NO_MSG(size < K_HEAP_MEM_POOL_SIZE);
#endif

    uint32_t irq_flag;
    size_t real_size = size + AIR_HEAP_DBG_INFO_SIZE;
    void *p_mem;
    air_heap_used_info_t *p_origin_info = NULL;

    if(ptr != NULL){
        irq_flag = arch_irq_lock();
        p_origin_info = calc_heap_info_by_buffer_ptr(ptr);
        arch_irq_unlock(irq_flag);
    }

    p_mem = __real_k_realloc(ptr, real_size);
    if(p_mem){
        irq_flag = arch_irq_lock();
        if(p_mem == ptr){
            /* case of return the original pointer, just modify the zephyr heap record */
            if(p_origin_info->releaser == AIR_HEAP_DBG_INFO_DEFAULT_RELEASER){
                sys_dlist_remove(&(p_origin_info->node));
                p_origin_info->releaser = reg_lr;
            } else {
                /* case 1: wrapper function & non-wrapper function was used together
                 * case 2: memory corruption happened
                 */
                __ASSERT_NO_MSG(0);
            }
        }

        air_heap_used_info_t *p_info = calc_heap_info_by_buffer_ptr(p_mem);
        sys_dnode_init(&(p_info->node));
        sys_dlist_append(&g_air_heap_used_list, &(p_info->node));
        p_info->allocator = reg_lr;
        p_info->releaser = AIR_HEAP_DBG_INFO_DEFAULT_RELEASER;
        // air_heap_used_info_foreach(print_heap_used_info, NULL);
        arch_irq_unlock(irq_flag);

        // printk("[Heap] 0x%08X re-allocated %d bytes(real_size %d) from 0x%08X, original 0x%08X",
        //     (unsigned int)reg_lr,
        //     size,
        //     real_size,
        //     (unsigned int)p_mem,
        //     (unsigned int)ptr
        // );
    } else {
        application_alloc_failed_hook();
    }
    return p_mem;
}


void __wrap_k_free(void *ptr)
{
    uint32_t reg_lr = (uint32_t)__builtin_return_address(0);
    uint32_t addr = (uint32_t)ptr;

    // printk("[Heap] 0x%08X want to free memory from 0x%08X",
    //     (unsigned int)reg_lr,
    //     (unsigned int)ptr
    // );

    if (!ptr){
        /* align C standard behavior */
        return;
    }

    /* check validity of input parameter */
    if((addr >= (uint32_t)kheap__system_heap) && \
       (addr < ((uint32_t)kheap__system_heap + CONFIG_HEAP_MEM_POOL_SIZE))
    ){
        uint32_t irq_flag = arch_irq_lock();
        air_heap_used_info_t *p_info = calc_heap_info_by_buffer_ptr(ptr);
        // printk("[Heap][Free] p_info addr: 0x%08X, allocator: 0x%08X, releaser: 0x%08X",
        //     (unsigned int)p_info,
        //     (unsigned int)p_info->allocator,
        //     (unsigned int)p_info->releaser
        // );
        // air_heap_used_info_foreach(print_heap_used_info, NULL);
        if(p_info->releaser == AIR_HEAP_DBG_INFO_DEFAULT_RELEASER){
            sys_dlist_remove(&(p_info->node));
            p_info->releaser = reg_lr;
        } else {
            /* case 1: wrapper function & non-wrapper function was used together
             * case 2: memory corruption happened
             */
            __ASSERT_NO_MSG(0);
        }
        // printk("[Heap][Free] p_info addr: 0x%08X, allocator: 0x%08X, releaser: 0x%08X",
        //     (unsigned int)p_info,
        //     (unsigned int)p_info->allocator,
        //     (unsigned int)p_info->releaser
        // );
        arch_irq_unlock(irq_flag);
    } else {
        /* not NULL and not valid zephyr heap buffer */
        __ASSERT_NO_MSG(0);
    }

    __real_k_free(ptr);
    // printk("[Heap] 0x%08X free memory from 0x%08X finished",
    //     (unsigned int)reg_lr,
    //     (unsigned int)ptr
    // );
}
