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

#ifndef __FOTA_FLASH_H__
#define __FOTA_FLASH_H__
#include "fota_platform.h"
#include "fota_util.h"

#ifdef ROM_BASE
#define FLASH_CONFIG_BASE    (ROM_BASE)
#else
#define FLASH_CONFIG_BASE    (BL_BASE)
#endif

typedef enum {
    FLASH_PARTITION_TYPE_PARTITION_TABLE,
    FLASH_PARTITION_TYPE_SECURITY_HEADER1,
    FLASH_PARTITION_TYPE_SECURITY_HEADER2,
    FLASH_PARTITION_TYPE_BOOTLOADER,
    FLASH_PARTITION_TYPE_N9,
    FLASH_PARTITION_TYPE_CM4_FW,
    FLASH_PARTITION_TYPE_DSP0,
    FLASH_PARTITION_TYPE_DSP1,
    FLASH_PARTITION_TYPE_RESVD,
    FLASH_PARTITION_TYPE_NVDM,
    FLASH_PARTITION_TYPE_FOTA,
    FLASH_PARTITION_TYPE_FOTA_EXT,
    FLASH_PARTITION_TYPE_ROFS,
    FLASH_PARTITION_TYPE_FS,
    FLASH_PARTITION_TYPE_GNSS_CONFIG,
    FLASH_PARTITION_TYPE_LM_GVA,
    FLASH_PARTITION_TYPE_LM_AMA,
    FLASH_PARTITION_TYPE_LM,
    FLASH_PARTITION_TYPE_ANC_FW,
    FLASH_PARTITION_TYPE_ANC_FW_TUNE,
    FLASH_PARTITION_TYPE_GRAMMAR_MODEL1,
    FLASH_PARTITION_TYPE_GRAMMAR_MODEL2,
    FLASH_PARTITION_TYPE_MIC_DATA_RECORD,
    FLASH_PARTITION_TYPE_NVDM_OU,

    FLASH_PARTITION_TYPE_MAX = 0xFF
} flash_partition_type_enum;

/**
 * @brief A structure to record the flash partition information.
 */

#ifdef AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
typedef struct {
    partition_t partition_type; /**< the flash partition type. */
    uint32_t LoadAddressLow; /**< the low bytes of the start address of the flash partition. It is a relative address with 0x0 for the start address of the flash. */
    uint32_t BinaryLengthLow; /**< the low bytes of the length of the flash partition. */
    bool is_external; /**< a boolean to record if the flash partition is in the external flash or not. */
} PACKED fota_flash_partition_info;
#else
typedef struct {
    flash_partition_type_enum partition_type; /**< the flash partition type. */
    uint32_t LoadAddressHigh; /**< the high bytes of the start address of the flash partition. It is reserved for MSDC the address space of which may be larger than 4GB. */
    uint32_t LoadAddressLow; /**< the low bytes of the start address of the flash partition. It is a relative address with 0x0 for the start address of the flash. */
    uint32_t BinaryLengthHigh; /**< the high bytes of the length of the flash partition. It is reserved for MSDC the address space of which may be larger than 4GB. */
    uint32_t BinaryLengthLow; /**< the low bytes of the length of the flash partition. */
    bool is_external; /**< a boolean to record if the flash partition is in the external flash or not. */
} PACKED fota_flash_partition_info;
#endif

// #ifdef BL_FOTA_ENABLE
/**
 * @brief Function for checking if the address range defined by the input parameters is valid or not. If the whole address range is within
 * one of the updatable flash partitions defined in g_flash_partition_info or the whole of it is not in any flash partition defined in
 * g_flash_partition_info with FOTA_SUPPORT_MEMORY_LAYOUT_MODIFICATION defined or it represents an extenal flash address range,
 * it is considered to be valid. Otherwise, it is not valid.
 * @param[in] addr The start address of the address range.
 * @param[in] length The length of the address range in bytes.
 * @return TRUE succeed; FALSE, fail.
 */
bool fota_flash_is_addr_range_valid(uint32_t addr, uint32_t length);
// #endif /* BL_FOTA_ENABLE */

/**
 * @brief Function for the flash initialization.
 * @param[in] is_int It indicates the flash type of the flash to be initialized. TRUE, the internal flash. FALSE, the external flash.
 * @return FOTA_ERRCODE_SUCCESS, succeed. Other values, fail.
 */
FOTA_ERRCODE fota_flash_init(bool is_int);

/**
 * @brief This function initializes the flash configuration based on the memory layout.
 * @param[out] partition_info The variable to store the flash partition information.
 * @return TRUE, succeed. False, fail.
 */
bool fota_flash_config_init(fota_flash_partition_info **partition_info);

#ifdef AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
fota_flash_partition_info *fota_flash_get_partition_info(partition_t partition_type);
#else
fota_flash_partition_info *fota_flash_get_partition_info(flash_partition_type_enum partition_type);
#endif
FOTA_ERRCODE fota_flash_get_fota_partition_info(FotaStorageType *storage_type, uint32_t *fota_address, uint32_t *length);
#ifdef AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
FOTA_ERRCODE fota_flash_get_fota_info_partition_info(FotaStorageType *storage_type, uint32_t *fota_info_address, uint32_t *length);
#endif

FotaStorageType fota_flash_get_storage_type(void);

FOTA_ERRCODE fota_flash_get_slot_info(FotaStorageType *storage_type, uint32_t *slot_address, uint32_t *length);

#endif /* __FOTA_FLASH_H__ */
