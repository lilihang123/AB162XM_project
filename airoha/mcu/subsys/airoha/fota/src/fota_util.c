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
#include <stdio.h>
#include "fota_util.h"
#include "fota_multi_info_util.h"
#include "fota_multi_info.h"
#include "fota_signature.h"
#include "fota_flash.h"
#include "hal_wdt.h"
#include "bsp_flash.h"
#include "hal_nvic.h"

#define SLOT_IAMGE_HEADER_LENGTH 512
#define SLOT_HEADER_LENGTH   32
#define SLOT_TAIL_TLV_LENGTH 4


bool fota_flash_read(uint32_t start_address, uint8_t *data, uint32_t length)
{
    hal_flash_status_t ret = hal_flash_read(start_address, data, length);
    if (ret != HAL_FLASH_STATUS_OK) {
        return false;
    } else {
        return true;
    }
}

bool fota_flash_erase(uint32_t start_address, hal_flash_block_t block_size)
{
#if defined(CONFIG_AIR_RACE_ERASE_IRQ_DISABLE)
    uint32_t saved_mask;
    hal_nvic_save_and_set_interrupt_mask(&saved_mask);
#endif
    hal_flash_status_t ret = hal_flash_erase(start_address, block_size);
#if defined(CONFIG_AIR_RACE_ERASE_IRQ_DISABLE)
    hal_nvic_restore_interrupt_mask(saved_mask);
#endif
    if (ret != HAL_FLASH_STATUS_OK) {
        return false;
    } else {
        return true;
    }
}

bool fota_flash_write(uint32_t start_address, uint8_t *data, uint32_t length)
{
    hal_flash_status_t ret = hal_flash_write(start_address, data, length);
    if (ret != HAL_FLASH_STATUS_OK) {
        return false;
    } else {
        return true;
    }
}

FOTA_ERRCODE fota_flash_erase_partition(partition_id_t id)
{
    hal_flash_block_t block_type = 0;
    uint32_t eraseLength = 0;
    partition_status_t p_status;
    uint32_t startEraseAddr;
    uint32_t eraseSize;

    p_status = partition_get_begin_address(id, &startEraseAddr);
    if (PARTITION_OP_OK != p_status) {
        printk("FOTA get partition address fail");
        return FOTA_ERRCODE_FAIL;
    }

    p_status = partition_get_length(id, &eraseSize);
    if (PARTITION_OP_OK != p_status) {
        printk("FOTA get partition length fail");
        return FOTA_ERRCODE_FAIL;
    }

    while (eraseSize)
    {
#if CONFIG_AIR_WDT
        hal_wdt_feed (HAL_WDT_FEED_MAGIC);
#endif
        block_type = HAL_FLASH_BLOCK_4K;
        eraseLength = FOTA_DATA_SIZE_4KB;

        if (eraseSize < FOTA_DATA_SIZE_4KB)
        {
            printk("Not 4K align with eraseSize:%d left.", eraseSize);
            eraseSize = FOTA_DATA_SIZE_4KB;
        }

        if (eraseSize >= FOTA_DATA_SIZE_64KB)
        {
            if(startEraseAddr % FOTA_DATA_SIZE_64KB == 0)
            {
                block_type = HAL_FLASH_BLOCK_64K;
                eraseLength = FOTA_DATA_SIZE_64KB;
            }
            else if (startEraseAddr % FOTA_DATA_SIZE_32KB == 0)
            {
                block_type = HAL_FLASH_BLOCK_32K;
                eraseLength = FOTA_DATA_SIZE_32KB;
            }
        }
        else if (eraseSize >= FOTA_DATA_SIZE_32KB)
        {
            if(startEraseAddr % FOTA_DATA_SIZE_32KB == 0)
            {
                block_type = HAL_FLASH_BLOCK_32K;
                eraseLength = FOTA_DATA_SIZE_32KB;
            }
        }

        if (bsp_flash_erase(startEraseAddr, block_type) != BSP_FLASH_STATUS_OK)
        {
            return FOTA_ERRCODE_FAIL;
        }

        startEraseAddr += eraseLength;
        eraseSize      -= eraseLength;
    }
    return FOTA_ERRCODE_SUCCESS;
}

FOTA_ERRCODE fota_slot_version_read(uint8_t *version, uint8_t ver_size, uint8_t slot_number)
{
#ifdef CONFIG_AIR_DUAL_BANK_FOTA_ENABLE
    partition_id_t partition = (slot_number == 0) ? PARTITION_MCU : PARTITION_MCU_B;
#else
    partition_id_t partition = (slot_number == 0) ? PARTITION_MCU : PARTITION_FOTA;
#endif
    partition_status_t p_status = PARTITION_OP_ERROR;
    uint32_t partition_address;

    if (!version || !ver_size || ver_size < strlen(FOTA_DEFAULT_VERSION)) {
        return FOTA_ERRCODE_INVALID_PARAMETER;
    }

    p_status = partition_get_begin_address(partition, &partition_address);
    if (PARTITION_OP_OK != p_status) {
        printk("FOTA get ota info fail");
        return FOTA_ERRCODE_FAIL;
    }

    uint8_t buffer[ver_size];
    memcpy(buffer, (void *)(partition_address + FOTA_VERSION_START_OFFSET), ver_size);
    int ret = snprintf(version, ver_size + 1, "v%d.%d.%d", buffer[0], buffer[1], buffer[2]);
    if (ret < 0 || ret > (ver_size + 1)){
        printk("[FOTA] read version fail");
        return FOTA_ERRCODE_FAIL;
    }
    return FOTA_ERRCODE_SUCCESS;
}

fota_integrity_check_type_enum fota_slot_signature_get_hash_type(uint16_t it_type)
{
    switch(it_type){
        case IMAGE_TLV_SHA256:
            return FOTA_INTEGRITY_CHECK_TYPE_SHA256;
        default:
            return FOTA_HASH_TYPE_MAX;
    }
}

#ifdef AIR_DUAL_BANK_FOTA_ENABLE
FOTA_ERRCODE fota_slot_parser_header_and_tail_info(uint32_t slot_address,
                                                   fota_integrity_check_type_enum *integrity_check_type,
                                                   uint32_t *signature_start_address,
                                                   uint32_t *data_start_address,
                                                   uint32_t *data_length)
{
    int ret = FOTA_ERRCODE_FAIL;
    uint8_t buffer[SLOT_HEADER_LENGTH + 2 * SLOT_TAIL_TLV_LENGTH];
    slot_header *slot_header_info = NULL;
    slot_tlv_info *slot_tail_info = NULL;
    slot_tlv *tlv_info = NULL;

    ret = fota_flash_read(slot_address, buffer, SLOT_HEADER_LENGTH);
    if(ret != true){
        printk("fota_flash_read ret:%d, address:%p, buffer:%p, length:%u\n",
            ret, (void *)slot_address, (void *)buffer, SLOT_HEADER_LENGTH);
        return ret;
    }

    slot_header_info = (slot_header *)buffer;
    *data_start_address = slot_address;
    *data_length = slot_header_info->ih_img_size + slot_header_info->ih_hdr_size;

    //check the tail magic number
    printk("slot 1 tail address: %x\n", *data_start_address + *data_length);
    ret = fota_flash_read(*data_start_address + *data_length, buffer + SLOT_HEADER_LENGTH, 2 * SLOT_TAIL_TLV_LENGTH);
    if(ret != true){
        return ret;
    }

    slot_tail_info = (slot_tlv_info *)(buffer + SLOT_HEADER_LENGTH);
    if(slot_tail_info->it_magic != IMAGE_TLV_INFO_MAGIC){
        printk("it_magic != IMAGE_TLV_INFO_MAGIC, it_magic: 0x%X\n", slot_tail_info->it_magic);
        return FOTA_ERRCODE_FAIL;
    }
    //read the integrity type
    tlv_info = (slot_tlv *)(buffer + SLOT_HEADER_LENGTH + SLOT_TAIL_TLV_LENGTH);
    *integrity_check_type = fota_slot_signature_get_hash_type(tlv_info->it_type);
    *signature_start_address = *data_start_address + *data_length + sizeof(slot_tlv_info) + sizeof(slot_tlv);
    printk("Integrity Type: %d, Signature Start Address: %x, Data Start Address: %x, Data Length: %u\n", *integrity_check_type, *signature_start_address, *data_start_address, *data_length);

    return FOTA_ERRCODE_SUCCESS;
}
#endif /* AIR_DUAL_BANK_FOTA_ENABLE */

FOTA_ERRCODE fota_flash_get_fota_partition_info(FotaStorageType *storage_type, uint32_t *fota_address, uint32_t *length)
{
    fota_flash_partition_info *partition_info = NULL;
#ifdef AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
    partition_t partition_type = PARTITION_TABLE_ITEM_MAX;
#else
    flash_partition_type_enum partition_type = FLASH_PARTITION_TYPE_MAX;
#endif
    if (!storage_type || !fota_address || !length) {
        return FOTA_ERRCODE_INVALID_PARAMETER;
    }

    *storage_type = fota_flash_get_storage_type();

    if (InternalFlash == *storage_type) {
#ifdef AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
        partition_type = PARTITION_FOTA;
#else
        partition_type = FLASH_PARTITION_TYPE_FOTA;
#endif
    }
#ifdef FOTA_EXTERNAL_FLASH_SUPPORT
    else if (ExternalFlash == *storage_type) {
#ifdef AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
        partition_type = PARTITION_VIRTUAL_FOTA_EXT;
#else
        partition_type = FLASH_PARTITION_TYPE_FOTA_EXT;
#endif
    }
#endif
    else {
        return FOTA_ERRCODE_UNSUPPORTED;
    }

    partition_info = fota_flash_get_partition_info(partition_type);
    if (!partition_info) {
        return FOTA_ERRCODE_FAIL;
    }

    *fota_address = partition_info->LoadAddressLow;
    *length = partition_info->BinaryLengthLow;
    return FOTA_ERRCODE_SUCCESS;
}
#ifdef AIR_DUAL_BANK_FOTA_ENABLE
FOTA_ERRCODE fota_slot_get_integrity_check_info(fota_integrity_check_type_enum *integrity_check_type,
                                                uint32_t *signature_start_address,
                                                uint32_t *data_start_address,
                                                uint32_t *data_length,
                                                FotaStorageType *storage_type)
{
    FOTA_ERRCODE ret = FOTA_ERRCODE_FAIL;
    uint32_t selected_slot_address = 0, selected_slot_length = 0;

    if (!integrity_check_type || !signature_start_address ||
        !data_start_address ||!data_length || !storage_type)
    {
        return FOTA_ERRCODE_INVALID_PARAMETER;
    }

    ret = fota_flash_get_slot_info(storage_type, &selected_slot_address, &selected_slot_length);
    if(ret != FOTA_ERRCODE_SUCCESS){
        printk("fota_flash_get_slot_info ret:%d", ret);
        return ret;
    }

    ret = fota_slot_parser_header_and_tail_info(selected_slot_address, integrity_check_type, signature_start_address, data_start_address, data_length);
    return ret;
}
#else
FOTA_ERRCODE fota_slot_get_integrity_check_info(fota_integrity_check_type_enum *integrity_check_type,
                                                uint32_t *signature_start_address,
                                                uint32_t *data_start_address,
                                                uint32_t *data_length,
                                                FotaStorageType *storage_type)
{
#define BUFFER_SIZE 32
    uint32_t fota_header_address = 0;
    int32_t ret = FOTA_ERRCODE_FAIL;
    uint16_t tlv_type = 0, tlv_length = 0;
    uint8_t buffer[BUFFER_SIZE] = {0};
    FOTA_BASIC_INFO *pHeader_info = NULL;

    printk("fota_slot_get_integrity_check_info");
    if (!integrity_check_type || !signature_start_address || !data_start_address ||
        !data_length || !storage_type) {
        printk("Invalid parameter");
        return FOTA_ERRCODE_INVALID_PARAMETER;
    }

    *integrity_check_type = FOTA_INTEGRITY_CHECK_TYPE_MAX;
    *storage_type = Invalid;

    ret = fota_flash_get_slot_info(storage_type, signature_start_address, data_length);
    if (FOTA_ERRCODE_SUCCESS != ret) {
        printk("fota_flash_get_slot_info failed");
        return ret;
    }

    /* The structure of the FOTA package is the signature, the FOTA header and the FOTA data. */
    fota_header_address = *signature_start_address + SIGNATURE_SIZE;
    printk("fota_header_address :%x", fota_header_address);

    do {
        /* The format of the TLV information is type, length and value. */
        /* Read the type of the TLV information. */
        ret = fota_flash_read(fota_header_address,
                              (uint8_t *)&tlv_type,
                              sizeof(tlv_type));
        if (true != ret || INVALID_TLV_VALUE == tlv_type) {
            ret = FOTA_ERRCODE_READ_FOTA_HEADER_FAIL;
            break;
        }
        printk("Read the type of the TLV information ret:%x, tlv_type:%x", ret, tlv_type);

        /* Read the length of the TLV information. */
        fota_header_address += sizeof(tlv_type);
        ret = fota_flash_read(fota_header_address,
                              (uint8_t *)&tlv_length,
                              sizeof(tlv_length));
        if (true != ret || 0 == tlv_length) {
            ret = FOTA_ERRCODE_READ_FOTA_HEADER_FAIL;
            break;
        }
        printk("Read the length of the TLV information ret:%x, tlv_length:%x", ret, tlv_length);

        /* Read the value of the TLV information. */
        fota_header_address += sizeof(tlv_length);
        if (tlv_type == FOTA_HEADER_TLV_BASIC_INFO) {
            ret = fota_flash_read(fota_header_address,
                                  buffer,
                                  tlv_length);
            if (true != ret) {
                break;
            }
            printk("Read the value of the TLV information ret:%x", ret);
            for (int i = 0; i < BUFFER_SIZE; i++) {
                printk("buffer[%d]: %02x ", i, buffer[i]);
            }

            pHeader_info = (FOTA_BASIC_INFO *)buffer;
#ifdef AIR_FOTA_ECDSA_ENABLE
            *integrity_check_type = FOTA_INTEGRITY_CHECK_TYPE_ECDSA384;
#else
            *integrity_check_type = pHeader_info->integrity_check_type;
#endif
            *data_start_address = *signature_start_address + SIGNATURE_SIZE;
            *data_length = FOTA_HEADER_OCCUPIED_SIZE - SIGNATURE_SIZE + pHeader_info->fota_data_length;
            printk("sig_type:%d sig_addr:%x data_addr:%x data_len:%x", *integrity_check_type,
                             *signature_start_address, *data_start_address, *data_length);
            return FOTA_ERRCODE_SUCCESS;
        }
        fota_header_address += tlv_length;
    } while (fota_header_address < *signature_start_address + FOTA_HEADER_OCCUPIED_SIZE);

    if (fota_header_address >= *signature_start_address + FOTA_HEADER_OCCUPIED_SIZE) {
        ret = FOTA_ERRCODE_OUT_OF_RANGE;
    }

    printk("fota_get_integrity_check_info ret:%d", ret);
    return ret;
}
#endif /* AIR_DUAL_BANK_FOTA_ENABLE */
FOTA_ERRCODE fota_get_integrity_check_info(fota_integrity_check_type_enum *integrity_check_type,
                                           uint32_t *signature_start_address,
                                           uint32_t *data_start_address,
                                           uint32_t *data_length,
                                           FotaStorageType *storage_type)
{
#define BUFFER_SIZE 32
    uint32_t fota_header_address = 0;
    int32_t ret = FOTA_ERRCODE_FAIL;
    bool is_int = TRUE;
    uint16_t tlv_type = 0, tlv_length = 0;
    uint8_t buffer[BUFFER_SIZE] = {0};
    FOTA_BASIC_INFO *pHeader_info = NULL;

    if (!integrity_check_type || !signature_start_address || !data_start_address ||
        !data_length || !storage_type) {
        return FOTA_ERRCODE_INVALID_PARAMETER;
    }

    *integrity_check_type = FOTA_INTEGRITY_CHECK_TYPE_MAX;
    *storage_type = Invalid;

    ret = fota_flash_get_fota_partition_info(storage_type,
                                             signature_start_address,
                                             data_length);
    if (FOTA_ERRCODE_SUCCESS != ret) {
        return ret;
    }

    /* The structure of the FOTA package is the signature, the FOTA header and the FOTA data. */
    fota_header_address = *signature_start_address + SIGNATURE_SIZE;
    is_int = (InternalFlash == *storage_type);

    do {
        /* The format of the TLV information is type, length and value. */
        /* Read the type of the TLV information. */
        ret = fota_flash_read(fota_header_address,
                              (uint8_t *)&tlv_type,
                              sizeof(tlv_type));
        if (true != ret || INVALID_TLV_VALUE == tlv_type) {
            ret = FOTA_ERRCODE_READ_FOTA_HEADER_FAIL;
            break;
        }

        /* Read the length of the TLV information. */
        fota_header_address += sizeof(tlv_type);
        ret = fota_flash_read(fota_header_address,
                              (uint8_t *)&tlv_length,
                              sizeof(tlv_length));
        if (true != ret || 0 == tlv_length) {
            ret = FOTA_ERRCODE_READ_FOTA_HEADER_FAIL;
            break;
        }

        /* Read the value of the TLV information. */
        fota_header_address += sizeof(tlv_length);
        if (tlv_type == FOTA_HEADER_TLV_BASIC_INFO) {
            ret = fota_flash_read(fota_header_address,
                                  buffer,
                                  tlv_length);
            if (true != ret) {
                break;
            }

            pHeader_info = (FOTA_BASIC_INFO *)buffer;
#ifdef AIR_FOTA_ECDSA_ENABLE
            *integrity_check_type = FOTA_INTEGRITY_CHECK_TYPE_ECDSA384;
#else
            *integrity_check_type = pHeader_info->integrity_check_type;
#endif
            *data_start_address = *signature_start_address + SIGNATURE_SIZE;
            *data_length = FOTA_HEADER_OCCUPIED_SIZE - SIGNATURE_SIZE + pHeader_info->fota_data_length;
            printk("sig_type:%d sig_addr:%x data_addr:%x data_len:%x", *integrity_check_type,
                             *signature_start_address, *data_start_address, *data_length);
            return FOTA_ERRCODE_SUCCESS;
        }
        fota_header_address += tlv_length;
    } while (fota_header_address < *signature_start_address + FOTA_HEADER_OCCUPIED_SIZE);

    if (fota_header_address >= *signature_start_address + FOTA_HEADER_OCCUPIED_SIZE) {
        ret = FOTA_ERRCODE_OUT_OF_RANGE;
    }

    printk("fota_get_integrity_check_info ret:%d", ret);
    return ret;
}

void fota_dvfs_lock(void)
{
#ifdef HAL_DVFS_MODULE_ENABLED
    hal_dvfs_lock_control(HAL_DVFS_OPP_HIGH, HAL_DVFS_LOCK);
#endif
}


void fota_dvfs_unlock(void)
{
#ifdef HAL_DVFS_MODULE_ENABLED
    hal_dvfs_lock_control(HAL_DVFS_OPP_HIGH, HAL_DVFS_UNLOCK);
#endif
}

FOTA_ERRCODE fota_sha256_generate(unsigned char sha256[32], uint32_t data_addr, uint32_t data_length, bool is_int)
{
    FotaStorageType storage_type = is_int ? InternalFlash : ExternalFlash;
    FOTA_ERRCODE ret = FOTA_ERRCODE_FAIL;

    ret = fota_hash_sha_generate(FOTA_HASH_TYPE_SHA256, sha256, 32, data_addr, data_length, storage_type);

    printk("fota_hash_sha_generate ret:%d", ret);
    return ret;
}

FOTA_ERRCODE fota_check_fota_package_integrity(FotaStorageType storage_type)
{
    FOTA_ERRCODE ret = FOTA_ERRCODE_FAIL;
    fota_integrity_check_type_enum integrity_check_type = FOTA_INTEGRITY_CHECK_TYPE_MAX;
    uint32_t signature_address = 0;
    uint32_t data_address = 0;
    uint32_t data_length = 0;
    unsigned char *hash = NULL, *signature = NULL;
    fota_hash_type_enum hash_type = FOTA_HASH_TYPE_MAX;
#ifdef FOTA_BL_ENABLE
    uint8_t hash_array[FOTA_HASH_MAX_SIZE] = {0};
    uint8_t signature_array[FOTA_SIGNATURE_MAX_SIZE] = {0};
#endif

    ret = fota_get_integrity_check_info(&integrity_check_type,
                                        &signature_address,
                                        &data_address,
                                        &data_length,
                                        &storage_type);
    if (FOTA_ERRCODE_SUCCESS != ret) {
        printk("fota_check_fota_package_integrity: get integrity check info failed, ret=%d", ret);
        return ret;
    }

    hash_type = fota_signature_get_hash_type(integrity_check_type);
    //FOTA_LOG_MSGID_D("hash_type:%d", 1, hash_type);
    if (FOTA_HASH_TYPE_MAX == hash_type) {
        printk("fota_check_fota_package_integrity: invalid hash type");
        return FOTA_ERRCODE_FAIL;
    }

#ifndef FOTA_BL_ENABLE
    hash = k_malloc(FOTA_HASH_MAX_SIZE);
    if (!hash) {
        printk("fota_check_fota_package_integrity: malloc hash failed");
        return FOTA_ERRCODE_NOT_ENOUGH_MEMORY;
    }

    signature = k_malloc(FOTA_SIGNATURE_MAX_SIZE);
    if (!signature) {
        k_free(hash);
        printk("fota_check_fota_package_integrity: malloc signature failed");
        return FOTA_ERRCODE_NOT_ENOUGH_MEMORY;
    }
#else
    hash = &hash_array[0];
    signature = &signature_array[0];
#endif

    ret = fota_flash_read(signature_address, signature, FOTA_SIGNATURE_MAX_SIZE);
    if (true != ret) {
#ifndef FOTA_BL_ENABLE
        k_free(hash);
        k_free(signature);
#endif
        printk("fota_check_fota_package_integrity: read signature failed, ret=%d", ret);
        return ret;
    }

    fota_dvfs_lock();
    ret = fota_hash_generate(hash_type, hash, FOTA_HASH_MAX_SIZE, data_address, data_length, storage_type);
    if (FOTA_ERRCODE_SUCCESS != ret) {
#ifndef FOTA_BL_ENABLE
        k_free(hash);
        k_free(signature);
#endif
        fota_dvfs_unlock();
        printk("fota_check_fota_package_integrity: generate hash failed, ret=%d", ret);
        return ret;
    }

    ret = fota_signature_verify(integrity_check_type,
                                signature,
                                FOTA_SIGNATURE_MAX_SIZE,
                                hash,
                                FOTA_HASH_MAX_SIZE);
    //FOTA_LOG_MSGID_I("fota_signature_verify:%d", 1, ret);
    fota_dvfs_unlock();

#ifndef FOTA_BL_ENABLE
    k_free(hash);
    k_free(signature);
#endif

    if (FOTA_ERRCODE_SUCCESS == ret) {
        printk("fota_check_fota_package_integrity:package integrity pass");
#ifndef FOTA_BL_ENABLE
        /* Write the integrity check result into the multiple information sector. */
        ret = fota_dl_integrity_res_write(FOTA_DL_INTEGRITY_RES_VAL_PASS);
#endif
    } else {
        /* Do nothing. Allow to check the integrity multiple times until it passes. */
    }
    printk("fota_check_fota_package_integrity: return ret=%d", ret);
    return ret;
}

void fota_device_reboot(void)
{
#if CONFIG_AIR_WDT
    hal_wdt_status_t ret;
    ret = hal_wdt_software_reset();
    if (HAL_WDT_STATUS_OK != ret) {
        printk("fota_device_reboot() ret:%d", ret);
    }
#endif
}

static FOTA_ERRCODE fota_parse_version_in_header(uint8_t *buffer, uint8_t buf_size)
{
    uint16_t tlv_type, tlv_length;
    uint32_t fota_partition_start_address, length, curr_addr;
    FotaStorageType flash_type;

    //FOTA_LOG_MSGID_I("start parser header", 0);
    if (!buffer || !buf_size) {
        return FOTA_ERRCODE_INVALID_PARAMETER;
    }

    if (fota_flash_get_fota_partition_info(&flash_type, &fota_partition_start_address, &length) != FOTA_ERRCODE_SUCCESS) {
        printk("Read record length in Bisc info failed.");
        return FOTA_ERRCODE_FAIL;
    }

    /* Point to the type of the first TLV information. */
    curr_addr = fota_partition_start_address + SIGNATURE_SIZE;

    do {
        if (fota_flash_read(curr_addr, (uint8_t *)&tlv_type, 2) != true) {
            printk("Read record length in Bisc info failed.");
            return FOTA_ERRCODE_FAIL;
        }

        /* Point to the length of the TLV information. */
        curr_addr += 2;
        if (fota_flash_read(curr_addr, (uint8_t *)&tlv_length, 2) != true) {
            printk("Read record length in Bisc info failed.");
            return FOTA_ERRCODE_FAIL;
        }

        //FOTA_LOG_MSGID_I("cur_addr:%lx, tlv_type:%x, tlv_length:%d", 3, curr_addr, tlv_type, tlv_length);
        /* Point to the data of the TLV information. */
        curr_addr += 2;

        if (FOTA_HEADER_TLV_VERSION_INFO == tlv_type) {

            if (tlv_length > FOTA_VERSION_MAX_SIZE || tlv_length > buf_size) {
                return FOTA_ERRCODE_FAIL;
            }

            if (fota_flash_read(curr_addr, buffer, tlv_length) != true) {
                return FOTA_ERRCODE_FAIL;
            }

            buffer[tlv_length - 1] = '\0';

            printk("read finish tlv_length:%x", tlv_length);

            return FOTA_ERRCODE_SUCCESS;
        }

        /* Point to the next TLV information. */
        curr_addr += tlv_length;
    } while (INVALID_TLV_VALUE != tlv_type);
    return FOTA_ERRCODE_FAIL;
}


/**
 * @brief The function gets the FOTA package release version. If it fails to read the version both from the multiple information
 * sector and from NVDM, FOTA_DEFAULT_VERSION will be returned.
 * @param[in] buffer A buffer to store the version string.
 * @param[in] buf_size The size of the buffer.
 * @return FOTA_ERRCODE_SUCCESS succeed; otherwise, fail.
 */
static FOTA_ERRCODE fota_stored_version_get(uint8_t *buffer, uint8_t buf_size)
{
    FOTA_ERRCODE ret = fota_version_read(buffer, buf_size);
    int32_t default_version_len = strlen(FOTA_DEFAULT_VERSION);

    if (FOTA_ERRCODE_UNINITIALIZED == ret) {
        if (buf_size >= default_version_len + 1) {
            memcpy(buffer, FOTA_DEFAULT_VERSION, default_version_len);
            ret = FOTA_ERRCODE_SUCCESS;
        } else {
            ret = FOTA_ERRCODE_INVALID_PARAMETER;
        }
    }

    return ret;
}

static FOTA_ERRCODE fota_stored_version_set(uint8_t *version, uint8_t version_len)
{
    return fota_version_write(version, version_len);
}

FOTA_ERRCODE fota_version_get(uint8_t *buffer, uint8_t buf_size, fota_version_type_enum version_type)
{
    if (FOTA_VERSION_TYPE_STORED == version_type) {
        return fota_stored_version_get(buffer, buf_size);
    } else if (FOTA_VERSION_TYPE_PACKAGE == version_type) {
        return fota_parse_version_in_header(buffer, buf_size);
    }

    return FOTA_ERRCODE_FAIL;
}

FOTA_ERRCODE fota_version_set(uint8_t *version, uint8_t version_len, fota_version_type_enum version_type)
{
    if (FOTA_VERSION_TYPE_STORED == version_type) {
        return fota_stored_version_set(version, version_len);
    } else if (FOTA_VERSION_TYPE_PACKAGE == version_type) {
        return FOTA_ERRCODE_UNSUPPORTED;
    }

    return FOTA_ERRCODE_FAIL;
}

FOTA_ERRCODE fota_check_fota_partition_is_erased(FotaStorageType storage_type)
{
#ifndef BL_FOTA_ENABLE
#define BUFFER_SIZE 32
    uint32_t OTA_START_ADDR, length;
    FotaStorageType real_storage_type;
    FOTA_ERRCODE err = FOTA_ERRCODE_FAIL;
    err = fota_flash_get_slot_info(&real_storage_type, &OTA_START_ADDR, &length);

    if (FOTA_ERRCODE_SUCCESS != err || storage_type != real_storage_type) {
        //FOTA_LOG_MSGID_E("fota_check_fota_partition_is_erased:read fota partition info fail!", 0);
        return err;
    }
#ifdef CONFIG_AIR_DUAL_BANK_FOTA_ENABLE
    uint32_t magic_number;
    if (true != fota_flash_read(OTA_START_ADDR, (uint8_t*)&magic_number, sizeof(magic_number))) {
        return FOTA_ERRCODE_READ_FOTA_DATA_FAIL;
    }
    if (magic_number == IMAGE_MAGIC) {
        return FOTA_ERRCODE_FAIL;
    }
#else
    uint8_t buffer[BUFFER_SIZE];
    uint8_t tlv_buffer[4];
    uint32_t curr_addr;
    uint8_t i;

    curr_addr = OTA_START_ADDR + SIGNATURE_SIZE;
    if (FOTA_ERRCODE_SUCCESS != fota_flash_read(OTA_START_ADDR, &buffer[0], sizeof(buffer)) ||
        FOTA_ERRCODE_SUCCESS != fota_flash_read(curr_addr, &tlv_buffer[0], sizeof(tlv_buffer))) {
        //FOTA_LOG_MSGID_E("fota_check_fota_partition_is_erased:read flash fail!", 0);
        return FOTA_ERRCODE_READ_FOTA_DATA_FAIL;
    }

    if(tlv_buffer[0] == 0x11 && tlv_buffer[1] == 0x00 && tlv_buffer[2] == 0x0a && tlv_buffer[3] == 0x00) {
        for (i = 0; i < BUFFER_SIZE ; i++) {
            if (0xff != buffer[i]) {
                return FOTA_ERRCODE_FAIL;
            }
        }
    }
#endif
#endif
    return FOTA_ERRCODE_SUCCESS;
}

