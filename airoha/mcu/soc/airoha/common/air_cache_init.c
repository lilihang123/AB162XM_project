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

#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/logging/log.h>

#include "air_chip.h"


#ifdef HAL_CACHE_MODULE_ENABLED
#include "hal_cache.h"

#if defined(AIR_BTD_IC_PREMIUM_G1)
/* Max region number is 16 */
const hal_cache_region_config_t cacheable_region[] = {
    /* cacheable address, cacheable size(both MUST be 4k bytes aligned) */
    /* airoha/mcu/soc/airoha/ab162x/soc.h (zephyr_code_partition)
     * case 1: mcuboot partition
     * case 2: firmware_a partition
     * case 3: firmware_b partition
     */
    { CODE_PARTITION_BASE, CODE_PARTITION_LENGTH },
};

uint32_t get_cacheable_region_num(void)
{
    return sizeof(cacheable_region) / sizeof(cacheable_region[0]);
}
#endif /* defined(AIR_BTD_IC_PREMIUM_G1) */

#if KERNELVERSION == 0x3030000
static int air_cache_init(const struct device *dev)
{
    ARG_UNUSED(dev);
#elif KERNELVERSION >= 0x3070000
static int air_cache_init(void)
{
#else
#error "Unkown supported kernel version"
#endif

    hal_cache_size_t cache_size;
#if defined(AIR_BTD_IC_PREMIUM_G1)
    hal_cache_region_t region, region_number;

    region_number = (hal_cache_region_t)get_cacheable_region_num();
#endif

#if defined(DVT_CACHE)
    extern void cache_dump_registers(void);
    cache_dump_registers();
#endif

    hal_cache_init();

    switch(CONFIG_AIR_CACHE_MEMORY_SIZE){
        case 0:
        {
            cache_size = HAL_CACHE_SIZE_0KB;
            return 0;
        }
            break;
#if defined(AIR_BTD_IC_MANDATORY_G1)
        case 8192:
        {
            cache_size = HAL_CACHE_SIZE_8KB;
        }
            break;
#endif /* defined(AIR_BTD_IC_MANDATORY_G1) */
#if defined(AIR_BTD_IC_PREMIUM_G1)
        case 16384:
        {
            cache_size = HAL_CACHE_SIZE_16KB;
        }
            break;
#endif /* defined(AIR_BTD_IC_PREMIUM_G1) */
        default:
            cache_size = HAL_CACHE_SIZE_0KB;
            return 1;
            break;
    }

    hal_cache_set_size(cache_size);

#if defined(AIR_BTD_IC_PREMIUM_G1)
    for (region = HAL_CACHE_REGION_0; region < region_number; region++) {
        hal_cache_region_config(region, &cacheable_region[region]);
        printk("cachable region %d, [0x%08X, 0x%08X]\r\n", region,\
            cacheable_region[region].cache_region_address,\
            cacheable_region[region].cache_region_address+\
            cacheable_region[region].cache_region_size
            );
        hal_cache_region_enable(region);
    }
    for (; region < HAL_CACHE_REGION_MAX; region++) {
        hal_cache_region_disable(region);
    }
#endif /* defined(AIR_BTD_IC_PREMIUM_G1) */

    hal_cache_enable();
    return 0;
}

#if IS_ENABLED(CONFIG_AIR_CACHE)
SYS_INIT(air_cache_init, CONFIG_CACHE_INIT_LEVEL, CONFIG_CACHE_INIT_PRIORITY);
#endif

#endif /* HAL_CACHE_MODULE_ENABLED */

