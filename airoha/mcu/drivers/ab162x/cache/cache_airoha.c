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

#define DT_DRV_COMPAT airoha_air_cache

#include <zephyr/drivers/cache.h>
#include <errno.h>

#include "hal_cache.h"
#include "hal_cache_internal.h"

void cache_data_enable(void)
{
    hal_cache_enable();
}

void cache_data_disable(void)
{
    hal_cache_disable();
}

int cache_data_flush_all(void)
{
    return (int)hal_cache_flush_all_cache_lines();
}

int cache_data_invd_all(void)
{
    return (int)hal_cache_invalidate_all_cache_lines();
}

int cache_data_flush_and_invd_all(void)
{
    return (int)hal_cache_invalidate_all_cache_lines();
}


int cache_data_flush_range(void *addr, size_t size)
{
    return (int)hal_cache_flush_multiple_cache_lines((uint32_t)addr, (uint32_t)size);
}

int cache_data_invd_range(void *addr, size_t size)
{
    return (int)hal_cache_invalidate_multiple_cache_lines((uint32_t)addr, (uint32_t)size);
}

int cache_data_flush_and_invd_range(void *addr, size_t size)
{
    hal_cache_flush_multiple_cache_lines((uint32_t)addr, (uint32_t)size);
    hal_cache_invalidate_multiple_cache_lines((uint32_t)addr, (uint32_t)size);
    return 0;
}

void cache_instr_enable(void)
{
    hal_cache_enable();
}

void cache_instr_disable(void)
{
    hal_cache_disable();
}

int cache_instr_flush_all(void)
{
    return (int)hal_cache_flush_all_cache_lines();
}

int cache_instr_invd_all(void)
{
    return (int)hal_cache_invalidate_all_cache_lines();
}

int cache_instr_flush_and_invd_all(void)
{
    return (int)hal_cache_invalidate_all_cache_lines();
}

int cache_instr_flush_range(void *addr, size_t size)
{
    return (int)hal_cache_flush_multiple_cache_lines((uint32_t)addr, (uint32_t)size);
}

int cache_instr_invd_range(void *addr, size_t size)
{
    return (int)hal_cache_invalidate_multiple_cache_lines((uint32_t)addr, (uint32_t)size);
}

int cache_instr_flush_and_invd_range(void *addr, size_t size)
{
    hal_cache_flush_multiple_cache_lines((uint32_t)addr, (uint32_t)size);
    hal_cache_invalidate_multiple_cache_lines((uint32_t)addr, (uint32_t)size);
    return 0;
}