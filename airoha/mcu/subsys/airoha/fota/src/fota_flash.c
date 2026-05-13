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

#include "fota_util.h"
#include "fota_multi_info.h"
#include "fota_flash.h"
#include "fota_multi_info_util.h"


fota_flash_partition_info *g_flash_partition_info = NULL; /* This variable stores the flash partition information. */
FotaStorageType g_flash_storage_type = InternalFlash; /* This variable indicates the flash type of the FOTA partition. */

void fota_flash_set_storage_type(FotaStorageType storage_type)
{
    if (InternalFlash == storage_type ||
        ExternalFlash == storage_type) {
        g_flash_storage_type = storage_type;
    }
}

FotaStorageType fota_flash_get_storage_type(void)
{
    return g_flash_storage_type;
}

void fota_init_flash(void)
{
    /* Initialize the internal flash. */
    fota_flash_init(TRUE);
    /* Initialize the external flash. */
    fota_flash_init(FALSE);

    /* Set the flash partition information. */
    fota_flash_config_init(&g_flash_partition_info);

#if FOTA_STORE_IN_EXTERNAL_FLASH
    fota_flash_set_storage_type(ExternalFlash);
#else
    fota_flash_set_storage_type(InternalFlash);
#endif

    fota_multi_info_sector_init();
}

FOTA_ERRCODE fota_flash_get_slot_info(FotaStorageType *storage_type, uint32_t *slot_address, uint32_t *length)
{
    partition_status_t p_status;

    if (!storage_type || !slot_address || !length) {
        printk("fota_flash_get_slot_info INVALID_PARAMETER");
        return FOTA_ERRCODE_INVALID_PARAMETER;
    }

    *storage_type = fota_flash_get_storage_type();
    printk("Storage Type: %d\n", *storage_type);
#ifdef CONFIG_AIR_DUAL_BANK_FOTA_ENABLE
    p_status = partition_get_begin_address(PARTITION_MCU_B, slot_address);
#else
    p_status = partition_get_begin_address(PARTITION_FOTA, slot_address);
#endif
    if (PARTITION_OP_OK != p_status) {
        printk("FOTA get slot bedin_address fail");
        return FOTA_ERRCODE_FAIL;
    }
    printk("Slot Address: 0x%08X\n", *slot_address);
    // *slot_address = *slot_address & 0x00FFFFFF;
#ifdef CONFIG_AIR_DUAL_BANK_FOTA_ENABLE
    p_status = partition_get_length(PARTITION_MCU_B, length);
#else
    p_status = partition_get_length(PARTITION_FOTA, length);
#endif
    if (PARTITION_OP_OK != p_status) {
        printk("FOTA get slot length fail");
        return FOTA_ERRCODE_FAIL;
    }
    printk("Slot Length: %u\n", *length);

    return FOTA_ERRCODE_SUCCESS;
}

bool fota_flash_is_addr_range_valid(uint32_t addr, uint32_t length)
{
    uint32_t i = 0;
#ifdef FOTA_SUPPORT_MEMORY_LAYOUT_MODIFICATION
    fota_flash_partition_info *partition_info = NULL;
    bool recorded_addr_range = FALSE; /* The variable indicates if the address range accesses any partition in g_flash_partition_info. */
#endif

#ifdef FOTA_EXTERNAL_FLASH_SUPPORT
    if (SPI_SERIAL_FLASH_ADDRESS & addr) {
        /* Return true if the address range is in the external flash. */
        if (length) {
            return TRUE;
        }

        return FALSE;
    }
#endif

    if (FLASH_CONFIG_BASE != (addr & 0xFF000000) &&
        0 != (addr & 0xFF000000)) {
        printk("Invalid address range. addr:%x len:%x", addr, length);
        return FALSE;
    }

    if (FLASH_CONFIG_BASE == (addr & 0xFF000000)) {
        //FOTA_LOG_MSGID_I("addr:%x with the address base.", 1, addr);
        addr -= FLASH_CONFIG_BASE;
    }

#ifdef FOTA_SUPPORT_MEMORY_LAYOUT_MODIFICATION
    /* Return false if the address range includes any non-updatable partition. */
#if defined(MTK_SECURE_BOOT_ENABLE)
#ifdef AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
    partition_info = fota_flash_get_partition_info(PARTITION_SECURITY_HEADER);
#else
    partition_info = fota_flash_get_partition_info(FLASH_PARTITION_TYPE_SECURITY_HEADER1);
#endif
    if (partition_info &&
        !(addr >= partition_info->LoadAddressLow + partition_info->BinaryLengthLow ||
          addr + length <= partition_info->LoadAddressLow)) {
        printk("Invalid address range. addr:%x len:%x", addr, length);
        return FALSE;
    }
#endif
#ifdef AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
    partition_info = fota_flash_get_partition_info(PARTITION_BL);
#else
    partition_info = fota_flash_get_partition_info(FLASH_PARTITION_TYPE_BOOTLOADER);
#endif
    if (partition_info &&
        !(addr >= partition_info->LoadAddressLow + partition_info->BinaryLengthLow ||
          addr + length <= partition_info->LoadAddressLow)) {
        printk("Invalid address range. addr:%x len:%x", addr, length);
        return FALSE;
    }
#endif

    while (g_flash_partition_info &&
#ifdef AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
           PARTITION_TABLE_ITEM_MAX != g_flash_partition_info[i].partition_type) {
#else
           FLASH_PARTITION_TYPE_MAX != g_flash_partition_info[i].partition_type) {
#endif
#ifdef FOTA_SUPPORT_MEMORY_LAYOUT_MODIFICATION
        if (!recorded_addr_range &&
            !(addr >= g_flash_partition_info[i].LoadAddressLow + g_flash_partition_info[i].BinaryLengthLow ||
              addr + length <= g_flash_partition_info[i].LoadAddressLow)) {
            recorded_addr_range = TRUE;
        }
#endif

        if (addr >= g_flash_partition_info[i].LoadAddressLow &&
            (addr + length <= g_flash_partition_info[i].LoadAddressLow + g_flash_partition_info[i].BinaryLengthLow)) {
            return TRUE;
        }
        i++;
    }

#ifdef FOTA_SUPPORT_MEMORY_LAYOUT_MODIFICATION
    /* Return true if the address range does not access any partition in g_flash_partition_info. */
    if (!recorded_addr_range) {
        printk("Not recorded address range. addr:%x len:%x", addr, length);
        return TRUE;
    }
#endif

    printk("Invalid address range. addr:%x len:%x", addr, length);
    return FALSE;
}

#ifdef AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
fota_flash_partition_info *fota_flash_get_partition_info(partition_t partition_type)
#else
fota_flash_partition_info *fota_flash_get_partition_info(flash_partition_type_enum partition_type)
#endif
{
    uint32_t i = 0;

    while (g_flash_partition_info &&
#ifdef AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
           PARTITION_TABLE_ITEM_MAX != g_flash_partition_info[i].partition_type &&
#else
           FLASH_PARTITION_TYPE_MAX != g_flash_partition_info[i].partition_type &&
#endif
           partition_type != g_flash_partition_info[i].partition_type) {
        i++;
    }

    if (g_flash_partition_info && partition_type == g_flash_partition_info[i].partition_type) {
        //FOTA_LOG_MSGID_I("Found, partition_type:%d", 1, partition_type);
        return g_flash_partition_info + i;
    }

    printk("Not Found, partition_type:%d", partition_type);

    return NULL;
}

FOTA_ERRCODE fota_flash_init(bool is_int)
{
    FOTA_ERRCODE ret = FOTA_ERRCODE_FAIL;
    static bool is_hal_inited = FALSE;

    if (is_int) {
        if (!is_hal_inited) {
            ret = HAL_FLASH_STATUS_OK == hal_flash_init() ? FOTA_ERRCODE_SUCCESS : FOTA_ERRCODE_FAIL;
            is_hal_inited = TRUE;
        } else {
            ret = FOTA_ERRCODE_SUCCESS;
        }
    } else {
#ifdef FOTA_EXTERNAL_FLASH_SUPPORT
        /* Do not care about the return value because another task may have initialized the SPI external flash and the SPI external
         * flash only supports the 'init-deinit-init' flow.
         */
        ret = bsp_flash_init();
        //FOTA_LOG_MSGID_I("bsp_flash_init() ret:%d", 1, ret);
        ret = FOTA_ERRCODE_SUCCESS;
#else
        ret = FOTA_ERRCODE_UNSUPPORTED;
#endif
    }

    return ret;
}
