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

#if defined(AIR_SHARE_BUFFER_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include "share_buffer.h"
#include "hal_nvic.h"
#include "assert.h"

/* Private define ------------------------------------------------------------*/
#define HwSemRetryTimes 50000

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define SHARE_BUFFER_ENTER_CRITICAL_AREA(mask, sem_id) \
do { \
    hal_nvic_save_and_set_interrupt_mask(&mask); \
    share_buffer_hw_semaphore_take(sem_id); \
} while (0)

#define SHARE_BUFFER_EXIT_CRITICAL_AREA(mask, sem_id) \
do { \
    share_buffer_hw_semaphore_give(sem_id); \
    hal_nvic_restore_interrupt_mask(mask); \
} while (0)

/* Private variables ---------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
extern hal_hw_semaphore_status_t hw_semaphore_take_special(hal_hw_semaphore_id_t id);
extern hal_hw_semaphore_status_t hw_semaphore_give_special(hal_hw_semaphore_id_t id);

void share_buffer_hw_semaphore_take(hal_hw_semaphore_id_t hw_sem_id)
{
    uint32_t take_times = 0;

    /* Add hw semaphore to avoid multi-core access */
    while (1) {
        if (HAL_HW_SEMAPHORE_STATUS_OK == hw_semaphore_take_special(hw_sem_id)) {
            break;
        }
        take_times++;
        if (take_times > HwSemRetryTimes) {
            assert(0);
        }
    }
}

void share_buffer_hw_semaphore_give(hal_hw_semaphore_id_t hw_sem_id)
{
    if (HAL_HW_SEMAPHORE_STATUS_OK != hw_semaphore_give_special(hw_sem_id)) {
        assert(0);
    }
}

/* Public functions ----------------------------------------------------------*/
share_buffer_status_t share_buffer_init(share_buffer_type_t type, share_buffer_info_t *share_buffer_info, share_buffer_parameter_t *share_buffer_parameter)
{
    share_buffer_status_t ret = SHARE_BUFFER_STATUS_ERROR;
    uint32_t mask;

    switch (type)
    {
        case SHARE_BUFFER_RING_4B_ALIGNED:
        case SHARE_BUFFER_RING:
            SHARE_BUFFER_ENTER_CRITICAL_AREA(mask, share_buffer_parameter->hw_sem_id);

            share_buffer_info->type = type;
            share_buffer_info->info.ring.base_addr = share_buffer_parameter->param.ring.space.base_addr;
            share_buffer_info->info.ring.length = share_buffer_parameter->param.ring.space.end_addr - share_buffer_parameter->param.ring.space.base_addr;
            share_buffer_info->info.ring.write_ptr = share_buffer_parameter->param.ring.space.base_addr;
            share_buffer_info->info.ring.read_ptr = share_buffer_parameter->param.ring.space.base_addr;
            share_buffer_info->is_full = false;

            SHARE_BUFFER_EXIT_CRITICAL_AREA(mask, share_buffer_parameter->hw_sem_id);

            ret = SHARE_BUFFER_STATUS_OK;
            break;

        default:
            break;
    }

    return ret;
}

share_buffer_status_t share_buffer_get_write_pointer(share_buffer_info_t *share_buffer_info, uint8_t hw_sem_id, uint32_t *write_ptr, bool *is_full)
{
    share_buffer_status_t ret = SHARE_BUFFER_STATUS_ERROR;
    uint32_t mask;

    switch (share_buffer_info->type)
    {
        case SHARE_BUFFER_RING_4B_ALIGNED:
        case SHARE_BUFFER_RING:
            SHARE_BUFFER_ENTER_CRITICAL_AREA(mask, hw_sem_id);

            *write_ptr = (uint32_t)(share_buffer_info->info.ring.write_ptr);
            *is_full = share_buffer_info->is_full;

            SHARE_BUFFER_EXIT_CRITICAL_AREA(mask, hw_sem_id);

            ret = SHARE_BUFFER_STATUS_OK;
            break;

        default:
            break;
    }

    return ret;
}

share_buffer_status_t share_buffer_set_write_pointer(share_buffer_info_t *share_buffer_info, uint8_t hw_sem_id, uint32_t write_ptr, bool *is_full)
{
    share_buffer_status_t ret = SHARE_BUFFER_STATUS_ERROR;
    uint32_t mask;

    switch (share_buffer_info->type)
    {
        case SHARE_BUFFER_RING_4B_ALIGNED:
        case SHARE_BUFFER_RING:
            SHARE_BUFFER_ENTER_CRITICAL_AREA(mask, hw_sem_id);

            share_buffer_info->info.ring.write_ptr = write_ptr;
            if (write_ptr == share_buffer_info->info.ring.read_ptr)
            {
                share_buffer_info->is_full = true;
                *is_full = true;
            }
            else
            {
                *is_full = false;
            }

            SHARE_BUFFER_EXIT_CRITICAL_AREA(mask, hw_sem_id);

            ret = SHARE_BUFFER_STATUS_OK;
            break;

        default:
            break;
    }

    return ret;
}

share_buffer_status_t share_buffer_get_read_pointer(share_buffer_info_t *share_buffer_info, uint8_t hw_sem_id, uint32_t *read_ptr, bool *is_empty)
{
    share_buffer_status_t ret = SHARE_BUFFER_STATUS_ERROR;
    uint32_t mask;

    switch (share_buffer_info->type)
    {
        case SHARE_BUFFER_RING_4B_ALIGNED:
        case SHARE_BUFFER_RING:
            SHARE_BUFFER_ENTER_CRITICAL_AREA(mask, hw_sem_id);

            *read_ptr = share_buffer_info->info.ring.read_ptr;
            if ((*read_ptr == share_buffer_info->info.ring.write_ptr) && (share_buffer_info->is_full != true))
            {
                *is_empty = true;
            }
            else
            {
                *is_empty = false;
            }

            SHARE_BUFFER_EXIT_CRITICAL_AREA(mask, hw_sem_id);

            ret = SHARE_BUFFER_STATUS_OK;
            break;

        default:
            break;
    }

    return ret;
}

share_buffer_status_t share_buffer_set_read_pointer(share_buffer_info_t *share_buffer_info, uint8_t hw_sem_id, uint32_t read_ptr, bool *is_empty)
{
    share_buffer_status_t ret = SHARE_BUFFER_STATUS_ERROR;
    uint32_t mask;

    switch (share_buffer_info->type)
    {
        case SHARE_BUFFER_RING_4B_ALIGNED:
        case SHARE_BUFFER_RING:
            SHARE_BUFFER_ENTER_CRITICAL_AREA(mask, hw_sem_id);

            share_buffer_info->info.ring.read_ptr = read_ptr;
            share_buffer_info->is_full = false;
            if (read_ptr == share_buffer_info->info.ring.write_ptr)
            {
                *is_empty = true;
            }
            else
            {
                *is_empty = false;
            }

            SHARE_BUFFER_EXIT_CRITICAL_AREA(mask, hw_sem_id);

            ret = SHARE_BUFFER_STATUS_OK;
            break;

        default:
            break;
    }

    return ret;
}

share_buffer_status_t share_buffer_get_base_address(share_buffer_info_t *share_buffer_info, uint8_t hw_sem_id, uint32_t *base_addr)
{
    share_buffer_status_t ret = SHARE_BUFFER_STATUS_ERROR;
    uint32_t mask;

    switch (share_buffer_info->type)
    {
        case SHARE_BUFFER_RING_4B_ALIGNED:
        case SHARE_BUFFER_RING:
            SHARE_BUFFER_ENTER_CRITICAL_AREA(mask, hw_sem_id);

            *base_addr= share_buffer_info->info.ring.base_addr;

            SHARE_BUFFER_EXIT_CRITICAL_AREA(mask, hw_sem_id);

            ret = SHARE_BUFFER_STATUS_OK;
            break;

        default:
            break;
    }

    return ret;
}

share_buffer_status_t share_buffer_get_end_address(share_buffer_info_t *share_buffer_info, uint8_t hw_sem_id, uint32_t *end_addr)
{
    share_buffer_status_t ret = SHARE_BUFFER_STATUS_ERROR;
    uint32_t mask;

    switch (share_buffer_info->type)
    {
        case SHARE_BUFFER_RING_4B_ALIGNED:
        case SHARE_BUFFER_RING:
            SHARE_BUFFER_ENTER_CRITICAL_AREA(mask, hw_sem_id);

            *end_addr= share_buffer_info->info.ring.base_addr + share_buffer_info->info.ring.length;

            SHARE_BUFFER_EXIT_CRITICAL_AREA(mask, hw_sem_id);

            ret = SHARE_BUFFER_STATUS_OK;
            break;

        default:
            break;
    }

    return ret;
}

share_buffer_status_t share_buffer_malloc(share_buffer_info_t *share_buffer_info, share_buffer_parameter_t *share_buffer_parameter, uint32_t init_size, uint8_t init_value)
{
    share_buffer_status_t ret = SHARE_BUFFER_STATUS_ERROR;
    uint32_t mask;

    switch (share_buffer_info->type)
    {
        case SHARE_BUFFER_RING_4B_ALIGNED:
            /* in 4byte aligned case, block size should be 4B aligned */
            if ((share_buffer_parameter->param.ring.block.block_size & 0x3) != 0)
            {
                share_buffer_parameter->param.ring.block.block_size = (share_buffer_parameter->param.ring.block.block_size & 0xfffffffc) + 4;
            }
        case SHARE_BUFFER_RING:
            SHARE_BUFFER_ENTER_CRITICAL_AREA(mask, share_buffer_parameter->hw_sem_id);

            /* update write offset if space is enough */
            // share_buffer_ring_info_t ring_info;
            // memcpy(&ring_info, share_buffer_info, sizeof(share_buffer_ring_info_t)); // for better performace, copy setting to the local
            if (share_buffer_info->is_full)
            {
                share_buffer_parameter->param.ring.mem_info.total_free_size = 0;
            }
            else if (share_buffer_info->info.ring.write_ptr >= share_buffer_info->info.ring.read_ptr)
            {
                share_buffer_parameter->param.ring.mem_info.total_free_size = share_buffer_info->info.ring.length - (share_buffer_info->info.ring.write_ptr - share_buffer_info->info.ring.read_ptr);
            }
            else
            {
                share_buffer_parameter->param.ring.mem_info.total_free_size = share_buffer_info->info.ring.read_ptr - share_buffer_info->info.ring.write_ptr;
            }
            if ((share_buffer_parameter->param.ring.mem_info.total_free_size >= share_buffer_parameter->param.ring.block.block_size) && (share_buffer_parameter->param.ring.block.block_size != 0))
            {
                /* update write offset */
                share_buffer_parameter->param.ring.space.base_addr = share_buffer_info->info.ring.base_addr;
                share_buffer_parameter->param.ring.space.end_addr = share_buffer_info->info.ring.base_addr + share_buffer_info->info.ring.length;
                share_buffer_parameter->param.ring.block.block_start_addr = share_buffer_info->info.ring.write_ptr;
                share_buffer_parameter->param.ring.block.block_end_addr = share_buffer_info->info.ring.write_ptr + share_buffer_parameter->param.ring.block.block_size;
                if (share_buffer_parameter->param.ring.block.block_end_addr >= share_buffer_parameter->param.ring.space.end_addr)
                {
                    share_buffer_parameter->param.ring.block.block_end_addr = share_buffer_parameter->param.ring.block.block_end_addr - share_buffer_parameter->param.ring.space.end_addr + share_buffer_info->info.ring.base_addr;
                }
                if (share_buffer_parameter->param.ring.block.block_end_addr == share_buffer_info->info.ring.read_ptr)
                {
                    share_buffer_info->is_full = true;
                }
                share_buffer_info->info.ring.write_ptr = share_buffer_parameter->param.ring.block.block_end_addr;

                /* init block if need */
                if (init_size <= share_buffer_parameter->param.ring.block.block_size)
                {
                    if (share_buffer_parameter->param.ring.block.block_start_addr < share_buffer_parameter->param.ring.block.block_end_addr)
                    {
                        memset((void *)(share_buffer_parameter->param.ring.block.block_start_addr), init_value, init_size);
                    }
                    else
                    {
                        if ((share_buffer_parameter->param.ring.block.block_start_addr + init_size) <= share_buffer_parameter->param.ring.space.end_addr)
                        {
                            memset((void *)(share_buffer_parameter->param.ring.block.block_start_addr), init_value, init_size);
                        }
                        else
                        {
                            memset((void *)(share_buffer_parameter->param.ring.block.block_start_addr), init_value, share_buffer_parameter->param.ring.space.end_addr-share_buffer_parameter->param.ring.block.block_start_addr);
                            memset((void *)(share_buffer_parameter->param.ring.space.base_addr), init_value, init_size-(share_buffer_parameter->param.ring.space.end_addr-share_buffer_parameter->param.ring.block.block_start_addr));
                        }
                    }
                }

                share_buffer_parameter->param.ring.mem_info.total_free_size -= share_buffer_parameter->param.ring.block.block_size;

                ret = SHARE_BUFFER_STATUS_OK;
            }

            SHARE_BUFFER_EXIT_CRITICAL_AREA(mask, share_buffer_parameter->hw_sem_id);
            break;

        default:
            break;
    }

    return ret;
}

share_buffer_status_t share_buffer_free(share_buffer_info_t *share_buffer_info, share_buffer_parameter_t *share_buffer_parameter)
{
    share_buffer_status_t ret = SHARE_BUFFER_STATUS_ERROR;
    uint32_t mask;

    switch (share_buffer_info->type)
    {
        case SHARE_BUFFER_RING_4B_ALIGNED:
            /* in 4byte aligned case, block size should be 4B aligned */
            if ((share_buffer_parameter->param.ring.block.block_size & 0x3) != 0)
            {
                share_buffer_parameter->param.ring.block.block_size = (share_buffer_parameter->param.ring.block.block_size & 0xfffffffc) + 4;
            }
        case SHARE_BUFFER_RING:
            SHARE_BUFFER_ENTER_CRITICAL_AREA(mask, share_buffer_parameter->hw_sem_id);

            /* update read offset if space is enough */
            // share_buffer_ring_info_t ring_info;
            // memcpy(&ring_info, share_buffer_info, sizeof(share_buffer_ring_info_t)); // for better performace, copy setting to the local
            if (share_buffer_info->is_full)
            {
                share_buffer_parameter->param.ring.mem_info.total_used_size = share_buffer_info->info.ring.length;
            }
            else if (share_buffer_info->info.ring.write_ptr > share_buffer_info->info.ring.read_ptr)
            {
                share_buffer_parameter->param.ring.mem_info.total_used_size = share_buffer_info->info.ring.write_ptr - share_buffer_info->info.ring.read_ptr;
            }
            else
            {
                share_buffer_parameter->param.ring.mem_info.total_used_size = share_buffer_info->info.ring.length - (share_buffer_info->info.ring.read_ptr - share_buffer_info->info.ring.write_ptr);
            }
            if ((share_buffer_parameter->param.ring.mem_info.total_used_size >= share_buffer_parameter->param.ring.block.block_size) && (share_buffer_parameter->param.ring.block.block_size != 0))
            {
                /* update read offset */
                share_buffer_parameter->param.ring.space.base_addr = share_buffer_info->info.ring.base_addr;
                share_buffer_parameter->param.ring.space.end_addr = share_buffer_info->info.ring.base_addr + share_buffer_info->info.ring.length;
                share_buffer_parameter->param.ring.block.block_start_addr = share_buffer_info->info.ring.read_ptr;
                share_buffer_parameter->param.ring.block.block_end_addr = share_buffer_info->info.ring.read_ptr + share_buffer_parameter->param.ring.block.block_size;
                if (share_buffer_parameter->param.ring.block.block_end_addr >= share_buffer_parameter->param.ring.space.end_addr)
                {
                    share_buffer_parameter->param.ring.block.block_end_addr = share_buffer_parameter->param.ring.block.block_end_addr - share_buffer_parameter->param.ring.space.end_addr + share_buffer_info->info.ring.base_addr;
                }
                share_buffer_info->info.ring.read_ptr = share_buffer_parameter->param.ring.block.block_end_addr;
                if (share_buffer_info->is_full)
                {
                    share_buffer_info->is_full = false;
                }

                share_buffer_parameter->param.ring.mem_info.total_used_size -= share_buffer_parameter->param.ring.block.block_size;

                ret = SHARE_BUFFER_STATUS_OK;
            }

            SHARE_BUFFER_EXIT_CRITICAL_AREA(mask, share_buffer_parameter->hw_sem_id);
            break;

        default:
            break;
    }
    return ret;
}

share_buffer_status_t share_buffer_query_used_space(share_buffer_info_t *share_buffer_info, share_buffer_parameter_t *share_buffer_parameter)
{
    share_buffer_status_t ret = SHARE_BUFFER_STATUS_ERROR;
    uint32_t mask;

    switch (share_buffer_info->type)
    {
        case SHARE_BUFFER_RING:
        case SHARE_BUFFER_RING_4B_ALIGNED:
            SHARE_BUFFER_ENTER_CRITICAL_AREA(mask, share_buffer_parameter->hw_sem_id);

            // share_buffer_ring_info_t ring_info;
            // memcpy(&ring_info, share_buffer_info, sizeof(share_buffer_ring_info_t)); // for better performace, copy setting to the local
            if (share_buffer_info->is_full)
            {
                share_buffer_parameter->param.ring.mem_info.total_used_size = share_buffer_info->info.ring.length;
            }
            else if (share_buffer_info->info.ring.write_ptr > share_buffer_info->info.ring.read_ptr)
            {
                share_buffer_parameter->param.ring.mem_info.total_used_size = share_buffer_info->info.ring.write_ptr - share_buffer_info->info.ring.read_ptr;
            }
            else
            {
                share_buffer_parameter->param.ring.mem_info.total_used_size = share_buffer_info->info.ring.length - (share_buffer_info->info.ring.read_ptr - share_buffer_info->info.ring.write_ptr);
            }

            SHARE_BUFFER_EXIT_CRITICAL_AREA(mask, share_buffer_parameter->hw_sem_id);

            ret = SHARE_BUFFER_STATUS_OK;
            break;

        default:
            break;
    }

    return ret;
}

share_buffer_status_t share_buffer_query_free_space(share_buffer_info_t *share_buffer_info, share_buffer_parameter_t *share_buffer_parameter)
{
    share_buffer_status_t ret = SHARE_BUFFER_STATUS_ERROR;
    uint32_t mask;

    switch (share_buffer_info->type)
    {
        case SHARE_BUFFER_RING:
        case SHARE_BUFFER_RING_4B_ALIGNED:
            SHARE_BUFFER_ENTER_CRITICAL_AREA(mask, share_buffer_parameter->hw_sem_id);

            // share_buffer_ring_info_t ring_info;
            // memcpy(&ring_info, share_buffer_info, sizeof(share_buffer_ring_info_t)); // for better performace, copy setting to the local
            if (share_buffer_info->is_full)
            {
                share_buffer_parameter->param.ring.mem_info.total_free_size = 0;
            }
            else if (share_buffer_info->info.ring.write_ptr >= share_buffer_info->info.ring.read_ptr)
            {
                share_buffer_parameter->param.ring.mem_info.total_free_size = share_buffer_info->info.ring.length - (share_buffer_info->info.ring.write_ptr - share_buffer_info->info.ring.read_ptr);
            }
            else
            {
                share_buffer_parameter->param.ring.mem_info.total_free_size = share_buffer_info->info.ring.read_ptr - share_buffer_info->info.ring.write_ptr;
            }

            SHARE_BUFFER_EXIT_CRITICAL_AREA(mask, share_buffer_parameter->hw_sem_id);

            ret = SHARE_BUFFER_STATUS_OK;
            break;

        default:
            break;
    }

    return ret;
}

share_buffer_status_t share_buffer_query_next_block(share_buffer_info_t *share_buffer_info, share_buffer_parameter_t *share_buffer_parameter)
{
    share_buffer_status_t ret = SHARE_BUFFER_STATUS_ERROR;
    uint32_t mask;

    switch (share_buffer_info->type)
    {
        case SHARE_BUFFER_RING_4B_ALIGNED:
        case SHARE_BUFFER_RING:
            SHARE_BUFFER_ENTER_CRITICAL_AREA(mask, share_buffer_parameter->hw_sem_id);

            // share_buffer_ring_info_t ring_info;
            // memcpy(&ring_info, share_buffer_info, sizeof(share_buffer_ring_info_t)); // for better performace, copy setting to the local
            if (share_buffer_info->is_full)
            {
                share_buffer_parameter->param.ring.block.block_size = share_buffer_info->info.ring.length;
            }
            else if (share_buffer_info->info.ring.write_ptr > share_buffer_info->info.ring.read_ptr)
            {
                share_buffer_parameter->param.ring.block.block_size = share_buffer_info->info.ring.write_ptr - share_buffer_info->info.ring.read_ptr;
            }
            else
            {
                share_buffer_parameter->param.ring.block.block_size = share_buffer_info->info.ring.length - (share_buffer_info->info.ring.read_ptr - share_buffer_info->info.ring.write_ptr);
            }
            if (share_buffer_parameter->param.ring.block.block_size != 0)
            {
                share_buffer_parameter->param.ring.block.block_start_addr = share_buffer_info->info.ring.read_ptr;
                share_buffer_parameter->param.ring.block.block_end_addr = share_buffer_info->info.ring.write_ptr;
            }
            else
            {
                share_buffer_parameter->param.ring.block.block_start_addr = 0;
                share_buffer_parameter->param.ring.block.block_end_addr = 0;
            }

            SHARE_BUFFER_EXIT_CRITICAL_AREA(mask, share_buffer_parameter->hw_sem_id);

            ret = SHARE_BUFFER_STATUS_OK;
            break;

        default:
            break;
    }

    return ret;
}

share_buffer_status_t share_buffer_write(share_buffer_info_t *share_buffer_info, void *des, void *src, uint32_t size)
{
    share_buffer_status_t ret = SHARE_BUFFER_STATUS_ERROR;

    switch (share_buffer_info->type)
    {
        case SHARE_BUFFER_RING_4B_ALIGNED:
        case SHARE_BUFFER_RING:
            // share_buffer_ring_info_t ring_info;
            // memcpy(&ring_info, share_buffer_info, sizeof(share_buffer_ring_info_t)); // for better performace, copy setting to the local
            if (((uint32_t)des < share_buffer_info->info.ring.base_addr) || ((uint32_t)des >= (share_buffer_info->info.ring.base_addr + share_buffer_info->info.ring.length)) || (size > share_buffer_info->info.ring.length))
            {
                assert(0);
            }
            if (((uint32_t)des+size) <= (share_buffer_info->info.ring.base_addr + share_buffer_info->info.ring.length))
            {
                memcpy(des, src, size);
            }
            else
            {
                uint32_t size_temp = ((uint32_t)des+size) - (share_buffer_info->info.ring.base_addr + share_buffer_info->info.ring.length);
                memcpy(des, src, size-size_temp);
                memcpy((void *)(share_buffer_info->info.ring.base_addr), (void *)((uint32_t)src+size-size_temp), size_temp);
            }

            ret = SHARE_BUFFER_STATUS_OK;
            break;

        default:
            break;
    }

    return ret;
}

share_buffer_status_t share_buffer_read(share_buffer_info_t *share_buffer_info, void *des, void *src, uint32_t size)
{
    share_buffer_status_t ret = SHARE_BUFFER_STATUS_ERROR;

    switch (share_buffer_info->type)
    {
        case SHARE_BUFFER_RING_4B_ALIGNED:
        case SHARE_BUFFER_RING:
            // share_buffer_ring_info_t ring_info;
            // memcpy(&ring_info, share_buffer_info, sizeof(share_buffer_ring_info_t)); // for better performace, copy setting to the local
            if (((uint32_t)src < share_buffer_info->info.ring.base_addr) || ((uint32_t)src >= (share_buffer_info->info.ring.base_addr + share_buffer_info->info.ring.length)) || (size > share_buffer_info->info.ring.length))
            {
                assert(0);
            }
            if (((uint32_t)src+size) <= (share_buffer_info->info.ring.base_addr + share_buffer_info->info.ring.length))
            {
                memcpy(des, src, size);
            }
            else
            {
                uint32_t size_temp = ((uint32_t)src+size) - (share_buffer_info->info.ring.base_addr + share_buffer_info->info.ring.length);
                memcpy(des, src, size-size_temp);
                memcpy((void *)(share_buffer_info->info.ring.base_addr), (void *)((uint32_t)src+size-size_temp), size_temp);
            }

            ret = SHARE_BUFFER_STATUS_OK;
            break;

        default:
            break;
    }

    return ret;
}

#endif /* AIR_SHARE_BUFFER_ENABLE) */
