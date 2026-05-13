/* Copyright Statement:
 *
 * (C) 2026  Airoha Technology Corp. All rights reserved.
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


#define _BL_FOTA_UTIL_C_

#include "fota_flash.h"
#include "fota_util.h"
#include "bl_fota_util.h"
#include "bl_fota_def.h"
#include "bsp_flash.h"
#include "fota_multi_info.h"

U32 g_fota_data_end_address = 0;

bool bl_gen_each_4k_target_addr_table()
{
    U32 count, offset;

    for (U32 i = 0; i < g_number_of_movers; ++i)
    {
        count = g_movers[i].length / 0x1000 + (g_movers[i].length % 0x1000 ? 1 : 0);
        printk("length:%d, count:%d", g_movers[i].length, count);
        offset = 0;

        for (U32 j = 0; j < count; ++j)
        {
            if (BL_FOTA_4K_TARGET_TABLE_MAX_SIZE <= g_fota_data_4k_target_table_size)
            {
                return false;
            }
            g_fota_data_4k_target_table[g_fota_data_4k_target_table_size] = g_movers[i].destination_address + offset;
            offset += 0x1000;

            ++g_fota_data_4k_target_table_size;
        }

        printk("g_fota_data_4k_target_table[%d]-addr:%x, g_fota_data_4k_target_table[%d]-addr:%x",
                    g_fota_data_4k_target_table_size - count,
                    g_fota_data_4k_target_table[g_fota_data_4k_target_table_size - count],
                    g_fota_data_4k_target_table_size - 1,
                    g_fota_data_4k_target_table[g_fota_data_4k_target_table_size - 1]);
    }
    return true;
}


bool bl_fota_is_mover_info_valid(void)
{
    U32 tmp_addr_dst = 0, len = 0, remainder = 0, tmp_addr_src = 0;
    int i, j;

#ifdef AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
    U32 partable2_adddress = lp_index_get_begin_address(LAYOUT_PARTITION_1, PARTITION_ERASE_BACKUP);
    U32 partable2_phy_adddress = partable2_adddress & (~HAL_FLASH_BASE_ADDRESS);
    bool partition_table_fota_en = false;

    for (i = 0; i < g_number_of_movers; i++)
    {
        printk("mover[%d] dst_addr: 0x%x", i, g_movers[i].destination_address);
        if(g_movers[i].destination_address == partable2_phy_adddress)
        {
            partition_table_fota_en = true;
            printk("bl_fota_is_mover_info_valid: partition table update en");
        }
    }
#endif


    /* destination_address Bubble sort */
    for (i = g_number_of_movers; i > 1; i--)
    {
        for (j = 1; j < i; j++)
        {
            if (g_movers[j - 1].destination_address > g_movers[j].destination_address)
            {
                tmp_addr_src = g_movers[j - 1].source_address;
                tmp_addr_dst = g_movers[j - 1].destination_address;
                len = g_movers[j - 1].length;

                g_movers[j - 1].source_address = g_movers[j].source_address;
                g_movers[j - 1].destination_address = g_movers[j].destination_address;
                g_movers[j - 1].length = g_movers[j].length;

                g_movers[j].source_address = tmp_addr_src;
                g_movers[j].destination_address = tmp_addr_dst;
                g_movers[j].length = len;
            }
        }
    }

#ifdef AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
    // if partion table needs to be fota, the flash region check is no need
    if(partition_table_fota_en == false)
    {
#endif
    /* Check destination_address overlap and address range. */
    for (i = g_number_of_movers - 1; i > 0; i--)
    {
        //len = ((g_movers[i - 1].length >> 12) << 12);
        len = g_movers[i - 1].length & 0xFFFFF000;
        remainder = g_movers[i - 1].length > len ? 0x1000 : 0;
        len = len + remainder;
        if (g_movers[i - 1].destination_address + len > g_movers[i].destination_address ||
            !fota_flash_is_addr_range_valid(g_movers[i - 1].destination_address, len))
        {
            printk("destination_address check failed. i:%d", i - 1);
            return false;
        }
    }

    len = g_movers[g_number_of_movers - 1].length & 0xFFFFF000;
    remainder = g_movers[g_number_of_movers - 1].length > len ? 0x1000 : 0;
    len = len + remainder;
    if (!fota_flash_is_addr_range_valid(g_movers[g_number_of_movers - 1].destination_address, len))
    {
        printk("destination_address check failed. i:%d", g_number_of_movers - 1);
        return false;
    }
#ifdef AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
    }
#endif

    /* source_address Bubble sort */
    for (i = g_number_of_movers; i > 1; i--)
    {
        for (j = 1; j < i; j++)
        {
            if (g_movers[j - 1].source_address > g_movers[j].source_address)
            {
                tmp_addr_src = g_movers[j - 1].source_address;
                tmp_addr_dst = g_movers[j - 1].destination_address;
                len = g_movers[j - 1].length;

                g_movers[j - 1].source_address = g_movers[j].source_address;
                g_movers[j - 1].destination_address = g_movers[j].destination_address;
                g_movers[j - 1].length = g_movers[j].length;

                g_movers[j].source_address = tmp_addr_src;
                g_movers[j].destination_address = tmp_addr_dst;
                g_movers[j].length = len;
            }
        }
    }

    if (None == g_compression_type)
    {
        /* Check source_address overlap and address range. */
        if (g_movers[0].source_address < g_fota_data_start_address - g_fota_partition_start_address ||
        (g_movers[g_number_of_movers - 1].source_address + g_movers[g_number_of_movers - 1].length >
         g_fota_data_start_address - g_fota_partition_start_address + g_fota_data_length))
        {
            printk("source_address check failed. i:%d", g_number_of_movers - 1);
            return false;
        }

        for (i = g_number_of_movers - 1; i > 0; i--)
        {
            if (g_movers[i - 1].source_address + g_movers[i - 1].length > g_movers[i].source_address)
            {
                printk("source_address check failed. i:%d", i - 1);
                return false;
            }
        }
    }

    printk("mover info is valid");

    return true;
}



BOOL bl_fota_get_next_tlv(U32 addr, U32 length, U16 *tlv_type, U16 *tlv_length)
{
    U16 curr_type;
    U16 curr_length;

    if (length < sizeof(*tlv_type) + sizeof(*tlv_length)) {
        printk("FOTA data extends beyond partition");
        return false;
    }

    if (bsp_flash_read(addr, (U8 *)&curr_type, sizeof(curr_type)) != BSP_FLASH_STATUS_OK) {
        printk("Read record type in FOTA header failed: %x", addr);
        return false;
    }
    // See if we have finished parsing the TLVs
    if (curr_type == INVALID_TLV_VALUE) {
        return false;
    }

    addr += sizeof(curr_type);
    if (bsp_flash_read(addr, (U8 *)&curr_length, sizeof(curr_length)) != BSP_FLASH_STATUS_OK) {
        printk("Read record length in FOTA header failed: %x", addr);
        return false;
    }

    length -= sizeof(curr_type) + sizeof(curr_length);
    if (length < curr_length) {
        printk("FOTA record extends beyond partition, addr:%x type:%x length:%d remaining:%d",
                   addr, curr_type, curr_length, length);
        return false;
    }

    *tlv_type = curr_type;
    *tlv_length = curr_length;

    return true;
}


BOOL bl_fota_init(VOID)
{
    FotaStorageType storage_type;
    U32 length;

    if (fota_flash_get_fota_partition_info(&storage_type, (uint32_t *)&g_fota_partition_start_address, (uint32_t *)&length) != FOTA_ERRCODE_SUCCESS)
    {
        return false;
    }

    if( storage_type == ExternalFlash)
    {
#ifdef BSP_EXTERNAL_SERIAL_FLASH_ENABLED
        g_fota_partition_start_address |= SPI_SERIAL_FLASH_ADDRESS;
#else
        printk("External flash is not supported!");
        return false;
#endif
    }
    printk("g_fota_partition_start_address[%x]",g_fota_partition_start_address);


    U32 curr_addr = g_fota_partition_start_address + SIGNATURE_SIZE; // skip signature

    /* fota length do not include last 4K byte */
    length -= 0x1000;
    g_fota_partition_length = length;

    U16 tlv_type;
    U16 tlv_length;
#define TLV_BUFFER_SIZE 256
    U8 temp[TLV_BUFFER_SIZE];

    bool is_basic_info_found   = false;
    bool is_mover_info_found   = false;
    bool is_version_info_found = false;
    bool is_nvdm_change_found = false;

    for (;bl_fota_get_next_tlv(curr_addr, length, &tlv_type, &tlv_length); curr_addr += tlv_length) {

        // point curr_addr to the address of the TLV data
        curr_addr += sizeof(tlv_type) + sizeof(tlv_length);


        // adjust length to account for this TLV record
        length -= sizeof(tlv_type) + sizeof(tlv_length) + tlv_length;

        if (tlv_type == FOTA_HEADER_TLV_BASIC_INFO) {
            printk("TLV_BASIC_INFO process");
            if (is_basic_info_found) {
                printk("multiple basic info records found, invalid!");
                return false;
            }

            if (tlv_length != sizeof(FOTA_BASIC_INFO)) {
                printk("wrong tlv_length:%d, should be=%d", tlv_length, sizeof(FOTA_BASIC_INFO));
                return false;
            }

            if (bsp_flash_read(curr_addr, &temp[0], sizeof(FOTA_BASIC_INFO)) != BSP_FLASH_STATUS_OK) {
                printk("read FOTA basic info. failed.");
                return false;
            }
            FOTA_BASIC_INFO *p_basic_info = (FOTA_BASIC_INFO *)temp;
            g_compression_type = p_basic_info->compression_type; // record compression type for further using
            // TODO: is the fota_data_start_address a relative address?
            g_fota_data_start_address = g_fota_partition_start_address + p_basic_info->fota_data_start_address;
            g_fota_data_length = p_basic_info->fota_data_length;
            g_fota_data_end_address = g_fota_data_start_address + g_fota_data_length;

            if (!fota_flash_is_addr_range_valid(g_fota_data_start_address, g_fota_data_length)) {
                printk("invalid address range in data: [%x, %d]", g_fota_data_start_address, g_fota_data_length);
                return false;
            }
            is_basic_info_found = true;
        } else if (tlv_type == FOTA_HEADER_TLV_MOVER_INFO) {
            FOTA_MOVER_INFO *p_mover_info = NULL;

            printk("TLV_MOVER_INFO process");
            if (is_mover_info_found) {
                printk("multiple mover records found, invalid!");
                return false;
            }

            if (bsp_flash_read(curr_addr, &temp[0], sizeof(FOTA_MOVER_INFO)) != BSP_FLASH_STATUS_OK) {
                printk("read FOTA mover info. failed.");
                return false;
            }
            p_mover_info = (FOTA_MOVER_INFO *)temp;
            g_number_of_movers = p_mover_info->number_of_movers;
            if (g_number_of_movers > BL_FOTA_MAX_MOVERS) {
                printk("too many movers=%d", g_number_of_movers);
                return false;
            }


            if (tlv_length != sizeof(p_mover_info->number_of_movers) + g_number_of_movers * sizeof(FOTA_MOVER_TRIPLET)) {
                printk("wrong tlv_length:%d, should be=%d", tlv_length,
                           sizeof(p_mover_info->number_of_movers) + g_number_of_movers * sizeof(FOTA_MOVER_TRIPLET));
                return false;
            }
            if (bsp_flash_read(curr_addr + sizeof(FOTA_MOVER_INFO), (U8 *)(&g_movers[0]), tlv_length - sizeof(FOTA_MOVER_INFO)) != BSP_FLASH_STATUS_OK) {
                printk("read FOTA movers failed.");
                return false;
            }

            is_mover_info_found = true;
        } else if (tlv_type == FOTA_HEADER_TLV_INTEGRITY_VERIFY_INFO) {
            U32 sha_number;

            printk("sha info process");
            if (g_is_sha_info_found) {
                printk("multiple SHA info records found, invalid!");
                return false;
            }
            if (bsp_flash_read(curr_addr, (U8 *)&sha_number, sizeof(sha_number)) != BSP_FLASH_STATUS_OK) {
                printk("read sha info info. failed.");
                return false;
            }

            if (g_number_of_movers != sha_number) {
                printk("g_number_of_movers:%x, sha_number:%x", g_number_of_movers, sha_number);
                return false;
            }

            if (tlv_length != sizeof(sha_number) + sha_number * BL_FOTA_SHA256_HASH_SIZE__BYTES) {
                printk("wrong tlv_length:%d, should be=%d", tlv_length,
                           sizeof(sha_number) + sha_number * BL_FOTA_SHA256_HASH_SIZE__BYTES);
                return false;
            }
            g_sha_info_start_address = curr_addr + sizeof(sha_number);

            printk("g_sha_info_start_address:%x", g_sha_info_start_address);

            g_is_sha_info_found = true;
        } else if (tlv_type == FOTA_HEADER_TLV_VERSION_INFO) {
            U32 tmpLength = tlv_length;
            printk("fota version process");

            if (is_version_info_found) {
                printk("multiple fota version records found, invalid!");
                return false;
            }
            if (tmpLength > FOTA_VERSION_MAX_SIZE) {
                printk("fota version size is not correct: length = %d", tmpLength);
                tmpLength = FOTA_VERSION_MAX_SIZE - 1;
            }

            if (bsp_flash_read(curr_addr, version, tmpLength) != BSP_FLASH_STATUS_OK) {
                printk("read version info failed!");
                return false;
            }

            versionLength = tmpLength;

            version[tmpLength-1] = '\0';

            printk("fota version :%s, version_len: %x", version, versionLength);

            is_version_info_found = true;
        } else if (tlv_type == 0xF0) {
            U32 data = 0;

            printk("fota nvdm incompatible flag found. tlv_length:%d", tlv_length);

            if (bsp_flash_read(curr_addr, (U8 *)&data, tlv_length) != BSP_FLASH_STATUS_OK) {
                printk("read nvdm incompatible flag failed!");
                continue;
            }

            printk("fota nvdm incompatible data = %x", data);

            if (data == 0x1) {
                fota_nvdm_incompatible_flag_set();
            }

            is_nvdm_change_found = true;
        } else {
            printk("Unknown FOTA TLV type value: %x", tlv_type);
        }
    }

    printk("is_basic_info_found:%x, is_mover_info_found:%x is_sha_info_found:%x is_version_info_found:%x is_nvdm_change_found:%x",
               is_basic_info_found,
               is_mover_info_found,
               g_is_sha_info_found,
               is_version_info_found,
               is_nvdm_change_found);

    return is_basic_info_found && is_mover_info_found && g_is_sha_info_found && is_version_info_found;
}

