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

#include <stdint.h>
#include <stdbool.h>

#include "hal_memview.h"
#include "exception_handler.h"

#define        HAL_MEMVIEW_ALLOW_CONVERT       0x1
#define        HAL_MEMVIEW_NOT_ALLOW_CONVERT   0x0

#if !defined(__EXT_BOOTLOADER__) && !defined(__EXT_DA__)

/* Check Infrasys address */
#define        INFRA_TCM_BEGIN              0x04000000
#define        INFRA_TCM_END                0x04060000

#define        INFRA_BT_SRAM_BEGIN          0x04060000
#define        INFRA_BT_SRAM_END            0x04064000

#define        INFRA_ROM_BEGIN              0x08000000
#define        INFRA_ROM_END                0x08100000

#define        INFRA_RISCV_SRAM_BEGIN        0x84064000
#define        INFRA_RISCV_SRAM_END          0x8406A000

/* Obtain the return address of caller from link register */
#define        GET_LR(x)                    x=(uint32_t)__builtin_return_address(0);    (void)x


static uint32_t check_infra_address(uint32_t addr)
{
    if( ((addr >= INFRA_TCM_BEGIN) && (addr < INFRA_TCM_END))
        || ((addr >= INFRA_ROM_BEGIN) && (addr < INFRA_ROM_END))
        || ((addr >= INFRA_BT_SRAM_BEGIN) && (addr < INFRA_BT_SRAM_END))
        || ((addr >= INFRA_RISCV_SRAM_BEGIN) && (addr < INFRA_RISCV_SRAM_END))
    ){
        return 0;       /* valid address */
    }
    return 1;
}


// air_assert(false, "[memview] Infra address range check fail 0x%08X! Caller is 0x%08X", x, lr);
#define CHECK_INFRA_ADDR(x) { \
    uint32_t res = check_infra_address(x); \
    if(res != 0){ \
        air_assert(false);\
    }\
}

#else /* defined(__EXT_BOOTLOADER__) || !defined(__EXT_DA__) */

#define        CHECK_INFRA_ADDR(x)        (void)x
#define        GET_LR(x)                  (void)x

#endif /* !defined(__EXT_BOOTLOADER__) &&  !defined(__EXT_DA__) */


static uint32_t allow_convert_check(uint32_t addr)
{
    if (
        ((INFRA_TCM_BEGIN <= addr) && (addr < INFRA_TCM_END)) ||
        ((INFRA_ROM_BEGIN <= addr) && (addr < INFRA_ROM_END))
    ) {
        return HAL_MEMVIEW_NOT_ALLOW_CONVERT;
    }
    return HAL_MEMVIEW_ALLOW_CONVERT;
}
/* Ibex convert to infrasys (physical) */
uint32_t hal_memview_riscv_to_infrasys(uint32_t mcu_address)
{
    uint32_t infrasys_address = 0;
    uint32_t lr;
    GET_LR(lr);
    if (allow_convert_check(mcu_address) == HAL_MEMVIEW_NOT_ALLOW_CONVERT) {
        return mcu_address;
    }
    infrasys_address = mcu_address;
    CHECK_INFRA_ADDR(infrasys_address);
    return infrasys_address;
}


/* infrasys(physical) convert to Ibex */
uint32_t hal_memview_infrasys_to_riscv(uint32_t infrasys_address)
{
    uint32_t mcu_address = 0;
    uint32_t lr;
    GET_LR(lr);

    CHECK_INFRA_ADDR(infrasys_address);
    mcu_address = infrasys_address;

    return mcu_address;
}