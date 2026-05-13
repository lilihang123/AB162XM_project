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
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
 * RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
 * TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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

#if CONFIG_AIR_BDM_ENABLE

#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <zephyr/devicetree.h>
#include <zephyr/types.h>
#include <stddef.h>
#include <sys/types.h>
#include <zephyr/device.h>

#include "air_chip.h"

#include "bdm.h"
#include "hal_flash.h"
#include "hal_nvic.h"
#include "hal_nvic_internal.h"
#include "memory_attribute.h"

#include "air_logging.h"

#define BDM_MAGIC_FLAG                           (uint32_t)0x404D4442
#define BDM_VERSION                              (uint8_t)0x01

typedef enum {
    bdm_data_spare = 0xFE,
    bdm_data_writing = 0xFC,
    bdm_data_valid = 0xF8,
    bdm_data_erasing = 0xF0,
    bdm_data_erased = 0xFF,
} bdm_hdr_status_t;


#define BDM_HEADER_RESERVED_BYTES                10
typedef struct {
    uint32_t magic;
    uint32_t erase_count;
    uint16_t id;
    uint16_t block_num;
    uint32_t sequence_num;
    uint32_t size;
    uint8_t status;
    uint8_t version;
    uint8_t __reserved[BDM_HEADER_RESERVED_BYTES];
} bdm_header_t;

#define BDM_HEADER_MAGIC_OFFSET                  offsetof(bdm_header_t, magic)
#define BDM_HEADER_ERASE_COUNT_OFFSET            offsetof(bdm_header_t, erase_count)
#define BDM_HEADER_ID_OFFSET                     offsetof(bdm_header_t, id)
#define BDM_HEADER_BLOCK_NUMBER_OFFSET           offsetof(bdm_header_t, block_num)
#define BDM_HEADER_SEQUENCE_NUMBER_OFFSET        offsetof(bdm_header_t, sequence_num)
#define BDM_HEADER_DATA_ITEM_SIZE_OFFSET         offsetof(bdm_header_t, size)
#define BDM_HEADER_STATUS_OFFSET                 offsetof(bdm_header_t, status)
#define BDM_HEADER_VERSION_SIZE_OFFSET           offsetof(bdm_header_t, version)

typedef struct {
    const id_size_mapping_t *p_map;
    uint32_t addr;
    uint16_t curr_flash_op_id;      /* used as busy flag */
    uint8_t init_done;
    uint8_t __RESERVED;
    uint32_t sequence_num;
    uint32_t valid_item_num;
    uint64_t erase_count_total;
} bdm_ctrl_t;

static bdm_ctrl_t s_bdm_ctrl;

static bdm_status_t bdm_internal_find_data_item(uint16_t id, uint32_t *o_addr)
{
    uint32_t addr = s_bdm_ctrl.addr;
    const id_size_mapping_t *p_map = s_bdm_ctrl.p_map;
    bdm_status_t status = BDM_ID_NOT_FOUND;
    while((p_map->id != BDM_END_ID) && (p_map->block_num != BDM_END_BLOCK_NUM)){
        if(p_map->id == id){
            status = BDM_SUCCESS;
            *o_addr = addr;
        }

        if((status == BDM_SUCCESS) || (BDM_INVALID_OP_PARAM == status)){
            break;
        }
        addr += 4096*p_map->block_num;
        p_map += 1;
    }
    return status;
}

static void construct_spare_bdm_header(uint32_t addr, bdm_header_t *hdr)
{
    hdr->magic = BDM_MAGIC_FLAG;
    hdr->sequence_num = s_bdm_ctrl.sequence_num;
    ++s_bdm_ctrl.sequence_num;
    hdr->size = 0xFFFFFFFF;
    hdr->status = (uint8_t)bdm_data_spare;
    hdr->version = BDM_VERSION;

    memset(hdr->__reserved, 0xFF, BDM_HEADER_RESERVED_BYTES);
    hal_flash_write(addr, (const uint8_t*)hdr, sizeof(bdm_header_t));
    printk("[BDM] make spare bdm header of 0x%04X at 0x%08X", hdr->id, addr);
}

static bool validity_bdm_header(const bdm_header_t *hdr)
{
    if((hdr->magic != BDM_MAGIC_FLAG) || \
       (hdr->erase_count == 0xFFFFFFFF) || \
       (hdr->sequence_num == 0xFFFFFFFF) || \
       (hdr->size == 0xFFFFFFFF) || \
       (hdr->status == 0xFF)
    ){
        return false;
    }
    if((hdr->magic == BDM_MAGIC_FLAG) && \
       (hdr->status == (uint8_t)bdm_data_valid)
    ){
        return true;
    }
    return false;
}

static uint32_t calc_avg_erase_count(void)
{
    if(s_bdm_ctrl.valid_item_num != 0){
        return s_bdm_ctrl.erase_count_total/s_bdm_ctrl.valid_item_num;
    }
    return 0;
}

static uint32_t calc_checksum(uint32_t addr, uint32_t item_len)
{
    uint8_t bdm_hdr_sum = 0x00;
    uint32_t user_data_sum = 0x0;
    uint32_t idx, offset;
    for(idx = 0; idx < sizeof(bdm_header_t); idx++){
        bdm_hdr_sum += *(uint8_t*)(addr + idx);
    }
    offset = 0;
    while(item_len >= 4){
        user_data_sum += *(uint32_t*)(addr + offset);
        offset += 4;
        item_len -= 4;
    }
    while(item_len > 0){
        user_data_sum += *(uint8_t*)(addr + offset);
        offset += 1;
        item_len -= 1;
    }

    return (user_data_sum & 0x00FFFFFF) | (bdm_hdr_sum << 24);
}

static void erase_and_construct_bdm_header(uint32_t addr, uint16_t id, uint16_t block_num)
{
    uint32_t data, begin_addr;
    bdm_header_t hdr;
    hal_flash_status_t flash_op_status;
    hal_flash_block_t block_type;

    begin_addr = addr;
    memcpy((void*)&hdr, (void*)addr, sizeof(bdm_header_t));

    if(hdr.magic == BDM_MAGIC_FLAG ){
        ++hdr.erase_count;
    } else {
        hdr.erase_count = calc_avg_erase_count();
    }
    hdr.id = id;
    hdr.block_num = block_num;

    while(block_num){
        if((!(addr % 0x10000)) && (block_num >= 16)){
            block_type = HAL_FLASH_BLOCK_64K;
            data = 64;
        } else if((!(addr % 0x8000)) && (block_num >= 8)){
            block_type = HAL_FLASH_BLOCK_32K;
            data = 32;
        } else {
            block_type = HAL_FLASH_BLOCK_4K;
            data = 4;
        }

        printk("[BDM] erase flash with addr: 0x%08X, size: %dKB", addr, data);
        flash_op_status = hal_flash_erase(addr, block_type);
        if(HAL_FLASH_STATUS_OK != flash_op_status){
            printk("[BDM] erase flash with addr: 0x%08X, block: %d error", addr, block_type);
        }

        switch(block_type){
            case  HAL_FLASH_BLOCK_4K:
                addr += 0x1000;
                block_num -= 1;
                break;
            case HAL_FLASH_BLOCK_32K:
                addr += 0x8000;
                block_num -= 8;
                break;
            case HAL_FLASH_BLOCK_64K:
                addr += 0x10000;
                block_num -= 16;
                break;
        }
    }

    construct_spare_bdm_header(begin_addr, &hdr);
}


bdm_status_t ab_bdm_init(uint32_t addr, const id_size_mapping_t *table)
{
    bdm_status_t status = BDM_ID_NOT_FOUND;
    const bdm_header_t *p_hdr;
    uint32_t bdm_addr;
    const id_size_mapping_t *p_iter;

    if((s_bdm_ctrl.init_done == 1) || (table == NULL) || (addr % 0x1000)){
        return BDM_INVALID_OP_PARAM;
    }

    s_bdm_ctrl.addr = addr;
    s_bdm_ctrl.p_map = table;
    s_bdm_ctrl.sequence_num = 0;
    s_bdm_ctrl.valid_item_num = 0;
    s_bdm_ctrl.erase_count_total = 0;
    s_bdm_ctrl.curr_flash_op_id = BDM_END_ID;

    p_iter = s_bdm_ctrl.p_map;
    while((p_iter->id != BDM_END_ID) && (p_iter->block_num != BDM_END_BLOCK_NUM)){
        status = bdm_internal_find_data_item(p_iter->id, &bdm_addr);
        p_hdr = (const bdm_header_t*)bdm_addr;
        if(true == validity_bdm_header(p_hdr)){
            ++s_bdm_ctrl.valid_item_num;
            s_bdm_ctrl.erase_count_total += p_hdr->erase_count;
            if(s_bdm_ctrl.sequence_num < p_hdr->sequence_num){
                s_bdm_ctrl.sequence_num = p_hdr->sequence_num;
            }
        }
        p_iter += 1;
    }
    printk("[BDM] sequence number: 0x%08X", s_bdm_ctrl.sequence_num);
    printk("[BDM] valid item number: %lu", s_bdm_ctrl.valid_item_num);
    // printk("[BDM] total erase count: %llx", s_bdm_ctrl.erase_count_total);
    printk("[BDM] total erase count: 0x%08X%08X", (uint32_t)(s_bdm_ctrl.erase_count_total >> 32), (uint32_t)(s_bdm_ctrl.erase_count_total));

    p_iter = s_bdm_ctrl.p_map;
    while((p_iter->id != BDM_END_ID) && (p_iter->block_num != BDM_END_BLOCK_NUM)){
        status = bdm_internal_find_data_item(p_iter->id, &bdm_addr);
        if(status != BDM_SUCCESS){
            printk("[BDM] find id(0x%04X) return %d", p_iter->id, status);
            continue;
        }
        p_hdr = (const bdm_header_t*)bdm_addr;
        printk("[BDM] bdm header address: 0x%08X, id: 0x%04X", bdm_addr, p_hdr->id);
        if(p_hdr->magic != BDM_MAGIC_FLAG){
            printk("[BDM] construct spare header because of magic is wrong", 0 );
            erase_and_construct_bdm_header(bdm_addr, p_iter->id, p_iter->block_num);
        } else {
            switch(p_hdr->status){
                case bdm_data_spare:
                    break;
                case bdm_data_valid:
                    break;
                case bdm_data_erasing:
                case bdm_data_writing:
                case bdm_data_erased:
                    /* fall through */
                    printk("[BDM] construct spare header because of status is wrong", p_hdr->status);
                    erase_and_construct_bdm_header(bdm_addr, p_iter->id, p_iter->block_num);
                    break;
            }
        }
        p_iter += 1;
        printk("", 0 );
    }
    s_bdm_ctrl.init_done = 1;
    return BDM_SUCCESS;
}

bdm_status_t ab_bdm_write(uint16_t id, uint32_t offset, const uint8_t* src_buff, uint32_t len, int flags)
{
    uint32_t addr, data;
    uint16_t block_num;
    uint32_t irq_mask;
    bdm_status_t status = BDM_ID_NOT_FOUND;

    if(src_buff == NULL){
        return BDM_INVALID_OP_PARAM;
    }
    hal_nvic_save_and_set_interrupt_mask(&irq_mask);
    if(s_bdm_ctrl.init_done != 1){
        hal_nvic_restore_interrupt_mask(irq_mask);
        return BDM_NOT_INITED;
    }
    if(BDM_END_ID != s_bdm_ctrl.curr_flash_op_id){
        hal_nvic_restore_interrupt_mask(irq_mask);
        return BDM_BUSY;
    }
    hal_nvic_restore_interrupt_mask(irq_mask);

    status = bdm_internal_find_data_item(id, &addr);
    if(BDM_SUCCESS == status){
        block_num = ((bdm_header_t*)addr)->block_num;
        __ASSERT_NO_MSG(block_num != 0);
        data = 4096*block_num - sizeof(bdm_header_t) + 4;
        if((offset + len) >= data){
            printk("[BDM] %u out of range %u", (offset + len), data);
            __ASSERT_NO_MSG(0);
            return BDM_INVALID_OP_PARAM;
        }
        s_bdm_ctrl.curr_flash_op_id = id;
        if(((bdm_header_t*)addr)->status != (uint8_t)bdm_data_writing){
            printk("[BDM] mark writing of 0x%04X at 0x%08X, current status is 0x%02X", id, addr + BDM_HEADER_STATUS_OFFSET, ((bdm_header_t*)addr)->status);

            /* mark writing */
            data = (uint8_t)bdm_data_writing;
            hal_flash_write(addr + BDM_HEADER_STATUS_OFFSET, (const uint8_t*)(&data), 1);
        }

        // extern void print_bdm_header_information(void);
        // print_bdm_header_information();

        printk("[BDM] writing data: 0x%04X 0x%08X 0x%08x 0x%08x", id, addr + sizeof(bdm_header_t) + offset, src_buff, len);
        hal_flash_write(addr + sizeof(bdm_header_t) + offset, (const uint8_t*)(src_buff), len);

        if(flags & BDM_FLAG_FINISH_WRITE){
            data = offset + len;
            printk("[BDM] 0x%04X total %u bytes", id, data);
            hal_flash_write(addr + BDM_HEADER_DATA_ITEM_SIZE_OFFSET, (const uint8_t*)(&data), 4);

            data = calc_checksum(addr, sizeof(bdm_header_t) + offset + len);
            printk("[BDM] write checksum(0x%08X) at 0x%08X", data, addr + sizeof(bdm_header_t) + offset + len);
            hal_flash_write(addr + sizeof(bdm_header_t) + offset + len, (const uint8_t*)(&data), 4);

            printk("[BDM] mark valid of 0x%04X at 0x%08X", id, addr + BDM_HEADER_STATUS_OFFSET);
            /* mark bdm_data_valid */
            data = (uint8_t)bdm_data_valid;
            hal_flash_write(addr + BDM_HEADER_STATUS_OFFSET, (const uint8_t*)(&data), 1);
        }
        s_bdm_ctrl.curr_flash_op_id = BDM_END_ID;
        return BDM_SUCCESS;
    }
    return status;
}

bdm_status_t ab_bdm_read(uint16_t id, uint32_t offset, uint8_t* dst_buff, uint32_t len)
{
    uint32_t addr;
    uint32_t irq_mask;
    bdm_status_t status = BDM_ID_NOT_FOUND;
    if(dst_buff == NULL){
        return BDM_INVALID_OP_PARAM;
    }
    hal_nvic_save_and_set_interrupt_mask(&irq_mask);
    if(s_bdm_ctrl.init_done != 1){
        hal_nvic_restore_interrupt_mask(irq_mask);
        return BDM_NOT_INITED;
    }

    if(id == s_bdm_ctrl.curr_flash_op_id){
        hal_nvic_restore_interrupt_mask(irq_mask);
        return BDM_BUSY;
    }

    status = bdm_internal_find_data_item(id, &addr);
    if(BDM_SUCCESS == status){
        if((((bdm_header_t*)addr)->status == (uint8_t)bdm_data_valid) &&
           (((bdm_header_t*)addr)->magic == BDM_MAGIC_FLAG) &&
           (((bdm_header_t*)addr)->id == id)
        ){
            if(((bdm_header_t*)addr)->size >= (offset + len)){
                addr = addr + sizeof(bdm_header_t) + offset;
                memcpy(dst_buff, (void*)(addr), len);
                hal_nvic_restore_interrupt_mask(irq_mask);
                return BDM_SUCCESS;
            } else {
                status = BDM_INVALID_OP_PARAM;
            }
        } else {
            status = BDM_ID_NOT_FOUND;
        }
    }
    hal_nvic_restore_interrupt_mask(irq_mask);
    return status;
}


bdm_status_t ab_bdm_delete(uint16_t id)
{
    uint32_t addr, data;
    uint16_t block_num;
    uint32_t irq_mask;
    bdm_status_t status = BDM_ID_NOT_FOUND;
    bdm_header_t hdr;

    hal_nvic_save_and_set_interrupt_mask(&irq_mask);
    if(s_bdm_ctrl.init_done != 1){
        hal_nvic_restore_interrupt_mask(irq_mask);
        return BDM_NOT_INITED;
    }

    if(BDM_END_ID != s_bdm_ctrl.curr_flash_op_id){
        hal_nvic_restore_interrupt_mask(irq_mask);
        return BDM_BUSY;
    }
    hal_nvic_restore_interrupt_mask(irq_mask);

    status = bdm_internal_find_data_item(id, &addr);
    if(BDM_SUCCESS == status){
        printk("[BDM] addr is %p", addr);

        memcpy((void*)&hdr, (void*)addr, sizeof(bdm_header_t));
        block_num = hdr.block_num;
        printk("[BDM] block_num: %d", block_num);
        if((((bdm_header_t*)addr)->status == (uint8_t)bdm_data_spare) &&
           (((bdm_header_t*)addr)->magic == BDM_MAGIC_FLAG)
        ){
            /* already deleted, return success */
            return BDM_SUCCESS;
        }
        if((((bdm_header_t*)addr)->status != (uint8_t)bdm_data_valid) &&
           (((bdm_header_t*)addr)->magic == BDM_MAGIC_FLAG)
        ){
            /* not allow delete operation when status is not valid */
            return BDM_INVALID_OP_PARAM;
        }
        s_bdm_ctrl.curr_flash_op_id = id;
        /* mark erasing and copy bdm header */
        printk("[BDM] mark erasing of 0x%04X at 0x%08X", id, addr + BDM_HEADER_STATUS_OFFSET);
        data = (uint8_t)bdm_data_erasing;
        hal_flash_write(addr + BDM_HEADER_STATUS_OFFSET, (const uint8_t*)(&data), 1);

        erase_and_construct_bdm_header(addr, hdr.id, hdr.block_num);
        s_bdm_ctrl.curr_flash_op_id = BDM_END_ID;
    }
    return status;
}


bdm_status_t ab_bdm_query(uint16_t id, bdm_info_t type, uint32_t* property)
{
    uint32_t addr;
    uint32_t irq_mask;
    bdm_status_t status = BDM_ID_NOT_FOUND;
    if(property == NULL){
        return BDM_INVALID_OP_PARAM;
    }
    hal_nvic_save_and_set_interrupt_mask(&irq_mask);
    if(s_bdm_ctrl.init_done != 1){
        hal_nvic_restore_interrupt_mask(irq_mask);
        return BDM_NOT_INITED;
    }

    if(BDM_END_ID != s_bdm_ctrl.curr_flash_op_id){
        hal_nvic_restore_interrupt_mask(irq_mask);
        return BDM_BUSY;
    }
    hal_nvic_restore_interrupt_mask(irq_mask);

    status = bdm_internal_find_data_item(id, &addr);
    if(BDM_SUCCESS == status){
        if(validity_bdm_header((const bdm_header_t *)addr) == false){
            return BDM_ID_NOT_FOUND;
        }
        switch(type) {
            case BDM_ERASE_COUNT:
                *property = ((bdm_header_t*)addr)->erase_count;
                break;
            case BDM_BLOCK_NUMBER:
                *property = ((bdm_header_t*)addr)->block_num;
                break;
            case BDM_SEQUENCE_NUMBER:
                *property = ((bdm_header_t*)addr)->sequence_num;
                break;
            case BDM_DATA_ITEM_SIZE:
                *property = ((bdm_header_t*)addr)->size;
                break;
            default:
                status = BDM_INVALID_OP_PARAM;
                break;
        }
    }
    return status;
}

#endif /* CONFIG_AIR_BDM_ENABLE */

