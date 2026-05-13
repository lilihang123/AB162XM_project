/* Copyright Statement:
 *
 * (C) 2023  Airoha Technology Corp. All rights reserved.
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


#include "nvkey.h"
#include "air_chip.h"
#include "nvkey_internal.h"

#if IS_ENABLED(CONFIG_SETTINGS) && \
    IS_ENABLED(CONFIG_SETTINGS_NVS) && \
    IS_ENABLED(CONFIG_NVS)

#include <zephyr/kernel.h>
#include <zephyr/fs/nvs.h>
#include <settings/settings_nvs.h>
#include <zephyr/settings/settings.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/storage/flash_map.h>

#if IS_ENABLED(CONFIG_AIR_NVKEY_ASYNC_ENABLE)

#include "air_daemon_work_q.h"

nvkey_async_ctl_t g_nvkey_async_ctl = {
    .list = {
        .head = &(g_nvkey_async_ctl.list),
        .tail = &(g_nvkey_async_ctl.list),
    },
    .p_ongoing = NULL,
    .req_num = 0,
};

nvkey_status_t nvkey_read_data(uint16_t id, uint8_t *buffer, uint32_t *size)
{
    struct nvs_fs* fs = nvkey_judge_paratition(id);
    ssize_t rd_size;
    if(fs == NULL){
        printk("ERROR because of NULL fs.\r\n");
        return NVKEY_STATUS_ERROR;
    }
    /* read from async nvkey data */
    uint32_t irq_flag = arch_irq_lock();
    sys_dnode_t *p_node = NULL;
    nvkey_async_write_t *p_async_req = NULL;
    SYS_DLIST_FOR_EACH_NODE((&(g_nvkey_async_ctl.list)), p_node) {
        p_async_req = (nvkey_async_write_t*)p_node;
        if(p_async_req->id == id){
            rd_size = ((*size) > p_async_req->size) ? (p_async_req->size) : (*size);
            memcpy(buffer, p_async_req->data, rd_size);
            *size = rd_size;
            arch_irq_unlock(irq_flag);
            return NVKEY_STATUS_OK;
        }
    }
    arch_irq_unlock(irq_flag);
    /* read from async nvkey data */

    /* read from nvkey data on flash memory */
    rd_size = nvs_read(fs, id, (void *)buffer, (size_t)(*size));
    if(rd_size < 0){
        *size = 0;
        return rd_size;
    }
    *size = (uint32_t)rd_size;
    /* read from nvkey data on flash memory */
    return NVKEY_STATUS_OK;
}

void nvkey_async_work_handler(struct k_work *work);
K_WORK_DEFINE(nvkey_async_work, nvkey_async_work_handler);

void nvkey_async_work_handler(struct k_work *work)
{
    uint32_t irq_flag = arch_irq_lock();
    __ASSERT_NO_MSG((g_nvkey_async_ctl.req_num > 0) && (g_nvkey_async_ctl.p_ongoing == NULL));
    /* mark ongoing */
    g_nvkey_async_ctl.p_ongoing = (nvkey_async_write_t*)(sys_dlist_peek_head(&(g_nvkey_async_ctl.list)));
    arch_irq_unlock(irq_flag);

    /* do nvkey write */
    nvkey_status_t op_ret = nvkey_write_data(
        g_nvkey_async_ctl.p_ongoing->id,
        g_nvkey_async_ctl.p_ongoing->data,
        (uint32_t)(g_nvkey_async_ctl.p_ongoing->size)
    );
    if(g_nvkey_async_ctl.p_ongoing->callback != NULL){
        g_nvkey_async_ctl.p_ongoing->callback(
            op_ret,
            (void*)(g_nvkey_async_ctl.p_ongoing->user_cb_data)
        );
    }

    irq_flag = arch_irq_lock();
    __ASSERT_NO_MSG((g_nvkey_async_ctl.req_num > 0) && (g_nvkey_async_ctl.p_ongoing != NULL));
    sys_dlist_remove(&(g_nvkey_async_ctl.p_ongoing->node));
    k_free((void*)(g_nvkey_async_ctl.p_ongoing));
    g_nvkey_async_ctl.p_ongoing = NULL;
    g_nvkey_async_ctl.req_num--;
    printk("[NVKey Async] async write request number is %d in nvkey_async_work_handler, work flags = 0x%08X", \
        (int)(g_nvkey_async_ctl.req_num),
        (unsigned int)(nvkey_async_work.flags)
    );
    if(g_nvkey_async_ctl.req_num > 0){
        int submit_result = air_daemon_wq_work_submit(work);
        /* confirm work was submitted correctly */
        __ASSERT_NO_MSG(submit_result == 2);
        printk("[NVKey Async] async write request number is %d in nvkey_async_work_handler after submit, work flags = 0x%08X", \
            (int)(g_nvkey_async_ctl.req_num),
            (unsigned int)(nvkey_async_work.flags)
        );
    }
    arch_irq_unlock(irq_flag);
}


static nvkey_status_t nvkey_submit_async_req(
    uint16_t id,
    const uint8_t *buffer,
    uint32_t size,
    const nvkey_user_callback_t callback,
    const void *user_data,
    bool crypt)
{
    nvkey_async_write_t *p_async_req = (nvkey_async_write_t*)k_malloc(size + sizeof(nvkey_async_write_t));
    if(p_async_req){
        sys_dnode_init(&(p_async_req->node));
        p_async_req->callback = callback;
        p_async_req->user_cb_data = user_data;
        p_async_req->id = id;
        p_async_req->size = (uint16_t)size;
        if(crypt){
            /* option as "NVS" */
            nvkey_port_encrypt_data(buffer, size, p_async_req->data, p_async_req->size, 0x4E5653);
        } else {
            memcpy(p_async_req->data, buffer, p_async_req->size);
        }
    }
    /* NULL => fail
     * others => success
     */
    if(p_async_req){
        uint32_t irq_flag = arch_irq_lock();
        sys_dlist_append(&(g_nvkey_async_ctl.list), &(p_async_req->node));
        printk("[NVKey Async] async write request number is %d in nvkey_submit_async_req, work flags = 0x%08X", \
            (int)(g_nvkey_async_ctl.req_num),
            (unsigned int)(nvkey_async_work.flags)
        );
        /* trigger nvkey_async work */
        if(g_nvkey_async_ctl.req_num == 0){
            int submit_result = air_daemon_wq_work_submit(&nvkey_async_work);
            /* confirm work was submitted correctly */
            __ASSERT_NO_MSG(submit_result == 1);
            printk("[NVKey Async] async write request number is %d in nvkey_submit_async_req after submit, work flags = 0x%08X", \
                (int)(g_nvkey_async_ctl.req_num),
                (unsigned int)(nvkey_async_work.flags)
            );
        }
        g_nvkey_async_ctl.req_num++;
        arch_irq_unlock(irq_flag);
        return NVKEY_STATUS_OK;
    } else {
        return NVKEY_STATUS_MALLOC_ERROR;
    }
}

nvkey_status_t nvkey_write_data_non_blocking(
    uint16_t id,
    const uint8_t *buffer,
    uint32_t size,
    const nvkey_user_callback_t callback,
    const void *user_data)
{
    return nvkey_submit_async_req(id, buffer, size, callback, user_data, false);
}

nvkey_status_t nvkey_write_data_non_blocking_crypt(
    uint16_t id,
    const uint8_t *buffer,
    uint32_t size,
    const nvkey_user_callback_t callback,
    const void *user_data)
{
    return nvkey_submit_async_req(id, buffer, size, callback, user_data, true);
}


#endif  /* IS_ENABLED(CONFIG_AIR_NVKEY_ASYNC_ENABLE) */

#endif /* IS_ENABLED(CONFIG_SETTINGS) &&
    IS_ENABLED(CONFIG_SETTINGS_NVS) &&
    IS_ENABLED(CONFIG_NVS) */