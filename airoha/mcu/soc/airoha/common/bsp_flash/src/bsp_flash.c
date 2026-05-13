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

/* Includes ------------------------------------------------------------------*/
#ifdef BSP_SERIAL_FLASH_ENABLED

#include <zephyr/irq.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/types.h>
#include <sys/types.h>
#include <zephyr/device.h>

/* zephyr/lib/libc/minimal/include/errno.h */
#include <errno.h>

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/* hal includes */
#include "hal.h"
#include "hal_log.h"
#include "bsp_flash.h"

#ifdef BSP_EXTERNAL_SERIAL_FLASH_ENABLED
#include "bsp_external_flash.h"
#include "bsp_external_flash_utils.h"
#endif

#ifdef HAL_ESC_MODULE_ENABLED
#include "hal_esc.h"
#include "hal_esc_internal.h"
#endif

/* use the most significant byte to identify flash device */
#define IDENTIFY_DEVICE_MASK  0xFF000000

/* Because the firmware upgrade scenario involves mixing BSP & HAL flash APIs,
 * a temporary workaround was implemented.
 */
#define SPECIAL_ID_FOR_INTERNAL_FLASH 0x00000000

bsp_flash_status_t bsp_flash_init(void)
{
    bsp_flash_status_t result = BSP_FLASH_STATUS_OK;
    hal_flash_init();

#ifdef BSP_EXTERNAL_SERIAL_FLASH_ENABLED
    result = (bsp_flash_status_t)bsp_external_flash_init();
#endif
    return result;
}

bsp_flash_status_t bsp_flash_read(uint32_t address, uint8_t *buffer, uint32_t length)
{
    bsp_flash_status_t result = BSP_FLASH_STATUS_OK;

    if (((IDENTIFY_DEVICE_MASK & address) == FLASH_MEMORY_BASE) ||
        ((IDENTIFY_DEVICE_MASK & address) == SPECIAL_ID_FOR_INTERNAL_FLASH)
    ){
        result = (bsp_flash_status_t)hal_flash_read(address, buffer, length);
    }
    else {
#ifdef BSP_EXTERNAL_SERIAL_FLASH_ENABLED
        result = (bsp_flash_status_t)bsp_external_flash_read(address, buffer, length);
#else
        result = BSP_FLASH_STATUS_ERROR;
#endif
    }
    return result;
}


bsp_flash_status_t bsp_flash_erase(uint32_t address, bsp_block_size_type_t block_size)
{
    bsp_flash_status_t result = BSP_FLASH_STATUS_OK;

    if (((IDENTIFY_DEVICE_MASK & address) == FLASH_MEMORY_BASE) ||
        ((IDENTIFY_DEVICE_MASK & address) == SPECIAL_ID_FOR_INTERNAL_FLASH)
    ){
        result = (bsp_flash_status_t)hal_flash_erase(address, (hal_flash_block_t)block_size);
    }
    else {
#ifdef BSP_EXTERNAL_SERIAL_FLASH_ENABLED
        result = (bsp_flash_status_t)bsp_external_flash_erase(address, (hal_flash_block_t)block_size);
#else
        result = BSP_FLASH_STATUS_ERROR;
#endif
    }
    return result;
}

bsp_flash_status_t bsp_flash_write(uint32_t address, uint8_t *data, int32_t length)
{
    bsp_flash_status_t result = BSP_FLASH_STATUS_OK;

    if (((IDENTIFY_DEVICE_MASK & address) == FLASH_MEMORY_BASE) ||
        ((IDENTIFY_DEVICE_MASK & address) == SPECIAL_ID_FOR_INTERNAL_FLASH)
    ){
        result = (bsp_flash_status_t)hal_flash_write(address, data, length);
    }
    else {
#ifdef BSP_EXTERNAL_SERIAL_FLASH_ENABLED
        result = (bsp_flash_status_t)bsp_external_flash_write(address, data, length);
#else
        result = BSP_FLASH_STATUS_ERROR;
#endif
    }
    return result;
}

bsp_flash_status_t bsp_flash_deinit(void)
{
#ifdef BSP_EXTERNAL_SERIAL_FLASH_ENABLED
    bsp_external_flash_deinit();
#endif
    return BSP_FLASH_STATUS_OK;
}

#endif//BSP_SERIAL_FLASH_ENABLED

