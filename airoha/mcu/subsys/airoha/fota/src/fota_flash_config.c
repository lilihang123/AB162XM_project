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

/**
 * File: fota_flash_config.c
 *
 * Description: This file obtains the memory layout from the partition table.
 *
 * Note: See doc/Airoha_IoT_SDK_Firmware_Update_Developers_Guide.pdf for more detail.
 *
 */


#include "fota_flash.h"
#if FOTA_STORE_IN_EXTERNAL_FLASH
#include "bsp_flash.h"
#endif
#include "fota_platform.h"

#ifdef AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
#ifndef CONFIG_AIR_FOTA_UPGRADE_ENABLE
#include <stdio.h>
#include <stdlib.h>
#endif
#include "fota_multi_info.h"
#ifdef CONFIG_AIR_FOTA_UPGRADE_ENABLE
#define FOTA_MAX_PARTITION_ITEMS    PARTITION_TABLE_ITEM_MAX
static fota_flash_partition_info s_flash_table[FOTA_MAX_PARTITION_ITEMS]; // bootloader need use array
#endif

bool fota_flash_config_init(fota_flash_partition_info **partition_info)
{
    if (!partition_info || *partition_info) {
        return false;
    }

    uint32_t total_partition_number = 0, i = 0;
    lp_status status = LAYOUT_PARTITION_OK;

    uint8_t partion_table = LAYOUT_PARTITION_2; //LAYOUT_PARTITION_1 or LAYOUT_PARTITION_2
    uint32_t start_address = 0, length = 0;
#ifdef CONFIG_AIR_FOTA_UPGRADE_ENABLE
    uint16_t part_state = 0;asd
    fota_parttable2_state_read(&part_state);
    /*partition table2 is ok*/
    if (0xFFFE != part_state) {
        partion_table = LAYOUT_PARTITION_2;
    } else {
        partion_table = LAYOUT_PARTITION_1;
    }
    printk("part_state = %x, partion_table = %x", part_state, partion_table);
#endif

    partition_t index = PARTITION_SECURITY_HEADER;
    status = lp_index_get_numbers_of_partition(partion_table, &total_partition_number);
    if (LAYOUT_PARTITION_OK != status) {
        printk("fota_flash_config_init error,get partition fail");
        return false;
    }
#ifndef CONFIG_AIR_FOTA_UPGRADE_ENABLE
    //FOTA_LOG_MSGID_I("total_partition_number = %x",1,total_partition_number);
#endif
    if (0 == total_partition_number) {
        printk("fota_flash_config_init error,total_partition_number is 0");
        return false;
    }
#ifdef CONFIG_AIR_FOTA_UPGRADE_ENABLE
    for (i = 0; i < total_partition_number; i++) {
        while (index <= PARTITION_TABLE_ITEM_MAX) {
            status = lp_index_get_begin_address_and_length(partion_table, index, &start_address, &length);

            if (LAYOUT_PARTITION_OK == status) {
                s_flash_table[i].partition_type = index;
                s_flash_table[i].LoadAddressLow = start_address & (~HAL_FLASH_BASE_ADDRESS);
                s_flash_table[i].BinaryLengthLow = length;
                //FOTA_LOG_MSGID_I("s_flash_table-partition_type[%d]:%x,start_address:%x,length:%dk,index = %x",5,i,s_flash_table[i].partition_type,start_address ,s_flash_table[i].BinaryLengthLow/1024,index);
                index ++;
                break;
            } else {
                index ++;
            }
        }
    }

#if FOTA_STORE_IN_EXTERNAL_FLASH
    s_flash_table[i].LoadAddressLow = FOTA_EXT_RESERVED_BASE_DEFAULT & (~SPI_SERIAL_ADDRESS);
    s_flash_table[i].partition_type = PARTITION_VIRTUAL_FOTA_EXT;
    s_flash_table[i].BinaryLengthLow = FOTA_EXT_RESERVED_LENGTH_DEFAULT;

    s_flash_table[i + 1].partition_type = PARTITION_TABLE_ITEM_MAX;
#else
    s_flash_table[i].partition_type = PARTITION_TABLE_ITEM_MAX;
#endif
    *partition_info = s_flash_table;
#else
    fota_flash_partition_info *f_flash_table = NULL;
    /* main bin need use heap*/
    f_flash_table = (fota_flash_partition_info*)malloc((total_partition_number + 2) * sizeof(fota_flash_partition_info));

    printk("malloc size = %d", (total_partition_number + 2) * sizeof(fota_flash_partition_info));

    if (!f_flash_table) {
        printk("s_flash_table malloc fail");
        return false;
    }

    memset(f_flash_table, 0, (total_partition_number + 2) * sizeof(fota_flash_partition_info));

    for (i = 0; i < total_partition_number; i++) {
        while (index <= PARTITION_TABLE_ITEM_MAX) {
            status = lp_index_get_begin_address_and_length(partion_table, index, &start_address, &length);

            if (LAYOUT_PARTITION_OK == status) {
                f_flash_table[i].partition_type = index;
                f_flash_table[i].LoadAddressLow = start_address & (~HAL_FLASH_BASE_ADDRESS);
                f_flash_table[i].BinaryLengthLow = length;
                printk("f_flash_table-partition_type[%d]:%x,LoadAddressLow:%x,BinaryLengthLow:%x,index = %x,start_address:%x",i,f_flash_table[i].partition_type,f_flash_table[i].LoadAddressLow ,f_flash_table[i].BinaryLengthLow,index,start_address);
                index ++;
                break;
            } else {
                index ++;
            }
        }
    }
#if FOTA_STORE_IN_EXTERNAL_FLASH
    f_flash_table[i].LoadAddressLow = FOTA_EXT_RESERVED_BASE_DEFAULT & (~SPI_SERIAL_ADDRESS);
    f_flash_table[i].partition_type = PARTITION_VIRTUAL_FOTA_EXT;
    f_flash_table[i].BinaryLengthLow = FOTA_EXT_RESERVED_LENGTH_DEFAULT;

    f_flash_table[i + 1].partition_type = PARTITION_TABLE_ITEM_MAX;
#else
    f_flash_table[i].partition_type = PARTITION_TABLE_ITEM_MAX;
#endif
    *partition_info = f_flash_table;
#endif
    return true;
}

FOTA_ERRCODE fota_flash_config_fota_partition_in_external_flash(uint32_t start_address, uint32_t length)
{
#if FOTA_STORE_IN_EXTERNAL_FLASH
    uint32_t i = 0;

    if (!length) {
        return FOTA_ERRCODE_INVALID_PARAMETER;
    }

    printk("FOTA ext. flash start_address:%x", start_address);

    while (PARTITION_TABLE_ITEM_MAX != s_flash_table[i].partition_type) {
        if (PARTITION_VIRTUAL_FOTA_EXT == s_flash_table[i].partition_type) {
            s_flash_table[i].LoadAddressLow = start_address & (~SPI_SERIAL_FLASH_ADDRESS);
            s_flash_table[i].BinaryLengthLow = length;
            return FOTA_ERRCODE_SUCCESS;
        }
        i++;
    }

    return FOTA_ERRCODE_FAIL;
#else
    return FOTA_ERRCODE_UNSUPPORTED;
#endif
}

#else
/* The variable stores the flash partition information. It only stores the information of the FOTA partition and the partitons which can be updated by FOTA. */
static fota_flash_partition_info s_flash_table[] = {
#ifdef CONFIG_AIR_FOTA_UPGRADE_ENABLE
    {
        .partition_type = FLASH_PARTITION_TYPE_CM4_FW,
        .LoadAddressHigh = 0,
        .LoadAddressLow = 0,
        .BinaryLengthHigh = 0,
        .BinaryLengthLow = 0,
        .is_external = FALSE
    },
#endif /* CONFIG_AIR_FOTA_UPGRADE_ENABLE */
    {
        .partition_type = FLASH_PARTITION_TYPE_FOTA,
        .LoadAddressHigh = 0,
        .LoadAddressLow = 0,
        .BinaryLengthHigh = 0,
        .BinaryLengthLow = 0,  /* The last block of fota temp partition is reserved for triggered flag & update info */
        .is_external = FALSE
    },

    {
        .partition_type = FLASH_PARTITION_TYPE_MAX,
        .LoadAddressHigh = 0,
        .LoadAddressLow = 0,
        .BinaryLengthHigh = 0,
        .BinaryLengthLow = 0,
        .is_external = FALSE
    }
};


bool fota_flash_config_init(fota_flash_partition_info **partition_info)
{
    int i = 0;

    if (!partition_info || *partition_info) {
        return false;
    }


    while (FLASH_PARTITION_TYPE_MAX != s_flash_table[i].partition_type) {
        switch (s_flash_table[i].partition_type) {
#ifdef CONFIG_AIR_FOTA_UPGRADE_ENABLE
            case FLASH_PARTITION_TYPE_CM4_FW: {
                uint32_t CM4_address, CM4_length;
                partition_status_t p_status = PARTITION_OP_ERROR;

                p_status = partition_get_begin_address(PARTITION_MCU, &CM4_address);
                if (PARTITION_OP_OK != p_status) {
                    printk("get partition begin address fail, partition_type:%x", PARTITION_MCU);
                    break;
                }
                s_flash_table[i].LoadAddressLow = CM4_address - FLASH_CONFIG_BASE;

                p_status = partition_get_length(PARTITION_MCU, &CM4_length);
                if (PARTITION_OP_OK != p_status) {
                    printk("get partition length fail, partition_type:%x", PARTITION_MCU);
                    break;
                }
                s_flash_table[i].BinaryLengthLow = CM4_length;
                break;
            }
#endif /* CONFIG_AIR_FOTA_UPGRADE_ENABLE */

            case FLASH_PARTITION_TYPE_FOTA: {
                uint32_t FOTA_address, FOTA_length;
                partition_status_t p_status = PARTITION_OP_ERROR;
#ifdef CONFIG_AIR_DUAL_BANK_FOTA_ENABLE
                p_status = partition_get_begin_address(PARTITION_MCU_B, &FOTA_address);
#else
                p_status = partition_get_begin_address(PARTITION_FOTA, &FOTA_address);
#endif
                if (PARTITION_OP_OK != p_status) {
                    printk("get partition begin address fail, partition_type:%x", PARTITION_MCU_B);
                    break;
                }
                s_flash_table[i].LoadAddressLow = FOTA_address - FLASH_CONFIG_BASE;
#ifdef CONFIG_AIR_DUAL_BANK_FOTA_ENABLE
                p_status = partition_get_length(PARTITION_MCU_B, &FOTA_length);
#else
                p_status = partition_get_length(PARTITION_FOTA, &FOTA_length);
#endif
                if (PARTITION_OP_OK != p_status) {
                    printk("get partition length fail, partition_type:%x", PARTITION_MCU_B);
                    break;
                }
                s_flash_table[i].BinaryLengthLow = FOTA_length;
                break;
            }

#ifdef FOTA_EXT_RESERVED_BASE_DEFAULT
            case FLASH_PARTITION_TYPE_FOTA_EXT: {
#if FOTA_STORE_IN_EXTERNAL_FLASH
                s_flash_table[i].LoadAddressLow = FOTA_EXT_RESERVED_BASE_DEFAULT & (~SPI_SERIAL_FLASH_ADDRESS);
#else
                s_flash_table[i].LoadAddressLow = FOTA_EXT_RESERVED_BASE_DEFAULT;
#endif
                s_flash_table[i].BinaryLengthLow = FOTA_EXT_RESERVED_LENGTH_DEFAULT;
                break;
            }
#endif

            default: {
                printk("Unknown partition type:%d", s_flash_table[i].partition_type);
                return false;
            }
        }
        i++;
    }

    *partition_info = s_flash_table;
    return true;
}


FOTA_ERRCODE fota_flash_config_fota_partition_in_external_flash(uint32_t start_address,
                                                                uint32_t length)
{
#if FOTA_STORE_IN_EXTERNAL_FLASH
    uint32_t i = 0;

    if (!length) {
        return FOTA_ERRCODE_INVALID_PARAMETER;
    }

    //FOTA_LOG_MSGID_I("FOTA ext. flash start_address:%x", 1, start_address);

    while (FLASH_PARTITION_TYPE_MAX != s_flash_table[i].partition_type) {
        if (FLASH_PARTITION_TYPE_FOTA_EXT == s_flash_table[i].partition_type) {
            s_flash_table[i].LoadAddressLow = start_address & (~SPI_SERIAL_FLASH_ADDRESS);
            s_flash_table[i].BinaryLengthLow = length;
            return FOTA_ERRCODE_SUCCESS;
        }
        i++;
    }

    return FOTA_ERRCODE_FAIL;
#else
    return FOTA_ERRCODE_UNSUPPORTED;
#endif
}
#endif
