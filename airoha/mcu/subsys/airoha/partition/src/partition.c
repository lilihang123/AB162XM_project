/* Copyright Statement:
 *
 * (C) 2020  Airoha Technology Corp. All rights reserved.
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

#ifdef AIR_PARTITION_ENABLE

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <zephyr/types.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/sys/printk.h>

#include "air_chip.h"
#include "partition.h"
#include "memory_attribute.h"


#define PARTITION_AVOID_NOT_USED_BUILD_ERROR(x)         (void)x
#define PARTITION_ITEM_SIZE                             ((uint32_t)sizeof(partition_item_t))

/* Use special characters to indicate the end of the scan. */
#define DUMMY_END_VALUE                                 0x444E4559             /* "YEND" */


typedef enum {
    partition_info_id,
    partition_info_attribute,
    partition_info_logic_address,
    partition_info_length,
} partition_info_t;

extern void partition_info_update(uint32_t idx, const partition_item_t* p_item);
extern void partition_info_prepare(void);
partition_status_t partition_init(void)
{
    const partition_item_t *p_item = NULL;
    uint32_t partition_idx = 0;
    partition_info_prepare();

    printk("partition_id    attr            address          length\r\n");
    for (uint32_t addr = PARTITION_TABLE_BASE;
        addr < PARTITION_TABLE_END;
        addr += PARTITION_ITEM_SIZE)
    {
        p_item = (const partition_item_t *)addr;
        if (((*(volatile uint32_t *)(addr)) == (uint32_t)PARTITION_DUMMY_END) &&
            ((*(volatile uint32_t *)(addr + 4U)) == (uint32_t)DUMMY_END_VALUE)
        ) {
            break;
        } else {
            PARTITION_AVOID_NOT_USED_BUILD_ERROR(p_item);
            printk("0x%08X      0x%08X      0x%08X       0x%08X\r\n", p_item->id, p_item->attribute.value, p_item->address, p_item->length);
            partition_info_update(partition_idx, p_item);
            partition_idx++;
        }
    }
    return PARTITION_OP_OK;
}


static const partition_item_t* find_target_partition(partition_id_t id)
{
    const partition_item_t *p_item = NULL;
    for (uint32_t addr = PARTITION_TABLE_BASE;
        addr < PARTITION_TABLE_END;
        addr += PARTITION_ITEM_SIZE)
    {
        p_item = (const partition_item_t *)addr;
        if(p_item->id == id){
            break;
        }
    }
    return p_item;
}


static partition_status_t partition_get_info(partition_id_t id, partition_info_t type, uint32_t *value)
{
    const partition_item_t* p_item;
    if(value == NULL){
        return PARTITION_OP_INVALID_PARAMETER;
    }

    p_item = find_target_partition(id);
    if(p_item){
        *value = *((uint32_t*)(&(p_item->id)) + type);
        return PARTITION_OP_OK;
    } else {
        return PARTITION_OP_NOT_EXIST;
    }
}


partition_status_t partition_get_length(partition_id_t id, uint32_t *value)
{
    return partition_get_info(id, partition_info_length, value);
}


partition_status_t partition_get_begin_address(partition_id_t id, uint32_t *value)
{
    return partition_get_info(id, partition_info_logic_address, value);
}


const uint32_t read_only_partitions[][2] = {
    { PARTITION_TABLE_BASE,             PARTITION_TABLE_END },
    { FACTORY_DATA_PARTITION_BASE,      FACTORY_DATA_PARTITION_END },
    { BOOT_PARTITION_BASE,              BOOT_PARTITION_END },
    { CODE_PARTITION_BASE,              CODE_PARTITION_END },
};
#define READ_ONLY_PARTITIONS_SIZE    (sizeof(read_only_partitions)/(sizeof(uint32_t)*2))
partition_status_t partition_is_readonly(uint32_t logic_addr, uint32_t len, bool *p_ro_var)
{
    uint32_t start, end, idx, partition_start = 0, partition_end = 0;
    start = logic_addr;
    end = start + len;

    if (p_ro_var == NULL){
        printk("[Partition] invalid p_ro_var");
        return PARTITION_OP_INVALID_PARAMETER;
    }
    if ((start >= ROM_END) || (start > end)) {
        printk("[Partition] logic_addr: 0x%08X, length: 0x%08X, ROM_BASE: 0x%08X, ROM_END: 0x%08X, start: 0x%08X, end: 0x%08X(%d, %d)\r\n",
            (unsigned int)logic_addr,
            (unsigned int)len,
            (unsigned int)ROM_BASE,
            (unsigned int)ROM_END,
            (unsigned int)start,
            (unsigned int)end,
            (int)(start >= ROM_END),
            (int)(start > end)
        );
        *p_ro_var = true;
        return PARTITION_OP_INVALID_PARAMETER;
    }

    *p_ro_var = false;
    for (idx = 0; idx < READ_ONLY_PARTITIONS_SIZE; idx++) {
        partition_start = read_only_partitions[idx][0];
        partition_end = read_only_partitions[idx][1];
        if (((start >= partition_start) && (start < partition_end)) ||
            ((end > partition_start) && (end < partition_end))) {
            *p_ro_var = true;
            printk("[Partition] { %08x, %08x } in read-only partition { %08x, %08x }\r\n",
                (unsigned int)start,
                (unsigned int)end,
                (unsigned int)partition_start,
                (unsigned int)partition_end
            );
            break;
        }
    }
    return PARTITION_OP_OK;
}

#if defined(CONFIG_FLASH_BOOTING) || defined(CONFIG_MCUBOOT)
#if KERNELVERSION == 0x3030000
static int partition_table_init_fn(const struct device *dev)
{
    ARG_UNUSED(dev);
#elif KERNELVERSION >= 0x3070000
static int partition_table_init_fn(void)
{
#else
#error "Unkown supported kernel version"
#endif
    return partition_init();
}

SYS_INIT(partition_table_init_fn, CONFIG_PARTITION_TABLE_INIT_LEVEL, CONFIG_PARTITION_TABLE_INIT_PRIORITY);
#endif

#endif /* AIR_PARTITION_ENABLE */
