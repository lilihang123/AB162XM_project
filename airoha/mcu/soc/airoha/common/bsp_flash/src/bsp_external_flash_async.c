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


#include <zephyr/irq.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/types.h>
#include <zephyr/device.h>
#include <sys/types.h>

/* zephyr/lib/libc/minimal/include/errno.h */
#include <errno.h>

#include "air_chip.h"
#include "hal_gpt.h"
#include "hal_spi_master.h"
#include "bsp_external_flash.h"
#include "bsp_external_flash_utils.h"


#ifdef AIR_BSP_EXTERNAL_SERIAL_FLASH_ASYNC_ENABLE

#define BEF_ASYNC_TASK_STACK_SIZE 1024

/* bsp external flash async fifo definition */
typedef struct {
    void *fifo_reserved;
    bsp_external_flash_callback_t cb;
    bsp_external_flash_async_operation_t type;
    uint32_t address;
    void *data;
    union {
        uint32_t length;
        block_size_type_t type;
    } size_union;
    void *user_data;
} bef_async_info_t;

K_THREAD_STACK_DEFINE(bef_async_area, BEF_ASYNC_TASK_STACK_SIZE);
struct k_thread bef_async;
struct k_fifo bef_async_request;
bef_async_info_t *bef_async_curr_req = NULL;
uint32_t bef_async_req_count[3] = { 0, 0, 0 };

void bef_async_process(void *p1, void *p2, void *p3);

void bsp_external_flash_work_q_init(void)
{
    if(0x0 == bef_async.base.thread_state){
        k_fifo_init(&bef_async_request);
        (void*)k_thread_create(
            &bef_async,
            bef_async_area,
            BEF_ASYNC_TASK_STACK_SIZE,
            bef_async_process, NULL, NULL, NULL,
            K_LOWEST_APPLICATION_THREAD_PRIO - 1,
            K_ESSENTIAL,
            K_FOREVER);
        k_thread_name_set(&bef_async, "bef_async");
        k_thread_start(&bef_async);
    }
}

bsp_external_flash_status_t bsp_external_flash_read_async(uint32_t address, \
        uint8_t *buffer, uint32_t length, \
        bsp_external_flash_callback_t flash_async_cb, \
        void *user_data)
{
    bef_async_info_t *p_info = k_malloc(sizeof(bef_async_info_t));
    if(p_info){
        p_info->cb = flash_async_cb;
        p_info->type = FLASH_ASYNC_OPERATION_READ;
        p_info->address = address;
        p_info->data = buffer;
        p_info->size_union.length = length;
        p_info->user_data = user_data;
        k_fifo_put(&bef_async_request, p_info);
        bef_async_req_count[FLASH_ASYNC_OPERATION_READ - FLASH_ASYNC_OPERATION_SPECIAL - 1]++;
        return EXTERNAL_FLASH_STATUS_OK;
    } else {
        return EXTERNAL_FLASH_STATUS_ERROR;
    }
}

bsp_external_flash_status_t bsp_external_flash_write_async(uint32_t address, \
        uint8_t *data, int32_t length, \
        bsp_external_flash_callback_t flash_async_cb, \
        void *user_data)
{
    bef_async_info_t *p_info = k_malloc(sizeof(bef_async_info_t));
    if(p_info){
        p_info->cb = flash_async_cb;
        p_info->type = FLASH_ASYNC_OPERATION_WRITE;
        p_info->address = address;
        p_info->data = data;
        p_info->size_union.length = length;
        p_info->user_data = user_data;
        k_fifo_put(&bef_async_request, p_info);
        bef_async_req_count[FLASH_ASYNC_OPERATION_WRITE - FLASH_ASYNC_OPERATION_SPECIAL - 1]++;
        return EXTERNAL_FLASH_STATUS_OK;
    } else {
        return EXTERNAL_FLASH_STATUS_ERROR;
    }
}

bsp_external_flash_status_t bsp_external_flash_erase_async(uint32_t address, \
        block_size_type_t block_size, \
        bsp_external_flash_callback_t flash_async_cb, \
        void *user_data)
{
    bef_async_info_t *p_info = k_malloc(sizeof(bef_async_info_t));
    if(p_info){
        p_info->cb = flash_async_cb;
        p_info->type = FLASH_ASYNC_OPERATION_ERASE;
        p_info->address = address;
        p_info->data = NULL;
        p_info->size_union.type = block_size;
        p_info->user_data = user_data;
        k_fifo_put(&bef_async_request, p_info);
        bef_async_req_count[FLASH_ASYNC_OPERATION_ERASE - FLASH_ASYNC_OPERATION_SPECIAL - 1]++;
        return EXTERNAL_FLASH_STATUS_OK;
    } else {
        return EXTERNAL_FLASH_STATUS_ERROR;
    }
}


void bef_async_process(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    uint32_t length = 0;
    bsp_external_flash_status_t op_res = EXTERNAL_FLASH_STATUS_ERROR;

    for(;;) {
        bef_async_curr_req = k_fifo_get(&bef_async_request, K_FOREVER);
        /* handle bef async request */
        switch(bef_async_curr_req->type)
        {
            case FLASH_ASYNC_OPERATION_ERASE:
                op_res = bsp_external_flash_erase_internal(
                    bef_async_curr_req->address,
                    bef_async_curr_req->size_union.type,
                    false);
                const uint32_t length_map_table[] = { 0x1000, 0x8000, 0x10000 };
                if((bef_async_curr_req->size_union.type >= FLASH_BLOCK_4K) &&
                   (bef_async_curr_req->size_union.type <= FLASH_BLOCK_64K))
                {
                    length = length_map_table[bef_async_curr_req->size_union.type];
                } else {
                    printk("invalid erase type(%d) in bsp external flash async request", bef_async_curr_req->size_union.type);
                    length = 0xDEADBEEF;
                }
                bef_async_req_count[FLASH_ASYNC_OPERATION_ERASE - FLASH_ASYNC_OPERATION_SPECIAL - 1]--;
                break;
            case FLASH_ASYNC_OPERATION_WRITE:
                op_res = bsp_external_flash_write_internal(
                    bef_async_curr_req->address,
                    (uint8_t *)(bef_async_curr_req->data),
                    (int32_t)(bef_async_curr_req->size_union.length),
                    false);
                length = bef_async_curr_req->size_union.length;
                bef_async_req_count[FLASH_ASYNC_OPERATION_WRITE - FLASH_ASYNC_OPERATION_SPECIAL - 1]--;
                break;
            case FLASH_ASYNC_OPERATION_READ:
                op_res = bsp_external_flash_read_internal(
                    bef_async_curr_req->address,
                    (uint8_t *)(bef_async_curr_req->data),
                    (int32_t)(bef_async_curr_req->size_union.length),
                    false);
                length = bef_async_curr_req->size_union.length;
                bef_async_req_count[FLASH_ASYNC_OPERATION_READ - FLASH_ASYNC_OPERATION_SPECIAL - 1]--;
                break;
            default:
                printk("invalid bsp external flash async request");
                break;
        }

        if(bef_async_curr_req->cb){
            bef_async_curr_req->cb(
                bef_async_curr_req->type,
                bef_async_curr_req->address,
                length,
                op_res,
                bef_async_curr_req->user_data
            );
        }

        k_free(bef_async_curr_req);
        bef_async_curr_req = NULL;
        k_yield();
    }
}

#endif /* AIR_BSP_EXTERNAL_SERIAL_FLASH_ASYNC_ENABLE */