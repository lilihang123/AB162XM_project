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

#ifdef AIR_PARTITION_ENABLE

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <zephyr/types.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>
#include <zephyr/storage/flash_map.h>

#include "air_chip.h"
#include "partition.h"
#include "memory_attribute.h"

#define DT_DRV_COMPAT airoha_air_flash_partitions
#define PARTITION_ID_MAP_AIROHA(part)               \
    { DT_FIXED_PARTITION_ID(part), DT_PROP(part, id) },

#define FOREACH_PARTITION_AIR(n) DT_FOREACH_CHILD(DT_DRV_INST(n), PARTITION_ID_MAP_AIROHA)
static const uint32_t partition_id_map[][2] = {
    DT_INST_FOREACH_STATUS_OKAY(FOREACH_PARTITION_AIR)
};

#if CONFIG_FLASH_MAP_LABELS
#define FLASH_AREA_FOO(part)                            \
    {.fa_id = DT_FIXED_PARTITION_ID(part),                    \
     .fa_off = DT_REG_ADDR(part),                        \
     .fa_dev = DEVICE_DT_GET_OR_NULL(DT_MTD_FROM_FIXED_PARTITION(part)),    \
     .fa_size = DT_REG_SIZE(part),                        \
     .fa_label = DT_PROP_OR(part, label, NULL),    },
#else
#define FLASH_AREA_FOO(part)                            \
    {.fa_id = DT_FIXED_PARTITION_ID(part),                    \
     .fa_off = DT_REG_ADDR(part),                        \
     .fa_dev = DEVICE_DT_GET_OR_NULL(DT_MTD_FROM_FIXED_PARTITION(part)),    \
     .fa_size = DT_REG_SIZE(part), },
#endif

#define FOREACH_PARTITION(n) DT_FOREACH_CHILD(DT_DRV_INST(n), FLASH_AREA_FOO)


const struct flash_area default_flash_map_in_dts[] = {
    DT_INST_FOREACH_STATUS_OKAY(FOREACH_PARTITION)
};

#define PARTITION_NUM_IN_DTS (ARRAY_SIZE(default_flash_map_in_dts))

/* we want to flash map not only from device tree but also from partition table */
struct flash_area flash_partitions[16];
static_assert(PARTITION_NUM_IN_DTS <= 16);

void __wrap_flash_area_foreach(flash_area_cb_t user_cb, void *user_data)
{
    ARG_UNUSED(user_cb);
    ARG_UNUSED(user_data);
}

int __wrap_flash_area_open(uint8_t id, const struct flash_area **fap)
{
    uint32_t idx;
    for (idx = 0; idx < PARTITION_NUM_IN_DTS; idx++) {
        if (flash_partitions[idx].fa_id == id) {
            *fap = &flash_partitions[idx];
            return 0;
        }
    }
    return -ENOENT;
}

static uint32_t s_partition_nums = 0;
void partition_info_update(uint32_t idx, const partition_item_t* p_item)
{
    uint32_t partition_idx;
    (void)idx;
    const struct device *flash_dev = device_get_binding(DEVICE_DT_NAME(DT_NODELABEL(flash_controller)));
    for(partition_idx = 0; partition_idx < PARTITION_NUM_IN_DTS; partition_idx++){
        if((uint8_t)(p_item->id) == partition_id_map[partition_idx][1]){
            flash_partitions[partition_idx].fa_off = (off_t)p_item->address - SFC_GENERIC_FLASH_BANK_MASK;
            flash_partitions[partition_idx].fa_dev = flash_dev;
            flash_partitions[partition_idx].fa_size = (size_t)p_item->length;
        #if CONFIG_FLASH_MAP_LABELS
            flash_partitions[partition_idx].fa_label = (const char *)p_item->name;
        #endif
            break;
        }
    }
    s_partition_nums = idx + 1;
}

void partition_info_prepare(void)
{
    memcpy((void*)&flash_partitions[0], (void*)&default_flash_map_in_dts[0], sizeof(default_flash_map_in_dts));
}

#endif /* AIR_PARTITION_ENABLE */
