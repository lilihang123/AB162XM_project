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


#include <stddef.h>
#include "LZMA_decoder.h"
#include "bl_fota_def.h"
#include "bl_fota_util.h"
#include "fota_util.h"
#include "fota_flash.h"
#include "fota_multi_info.h"
#include "hal_wdt.h"
#include "bsp_flash.h"
#include "hal_aes.h"
#include "bl_fota_flash_ctrl.h"

////////////////////////////////////////////////////////////////////////////////
// EXTERN///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Definition///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


#define FOTA_WRITE_READ_LENGTH  (1024)

/* SzAlloc() was called twice. One is to alloc 15980 bytes and the other is to alloc dictory_size bytes.
  * level  dictory_size
  * 0       16K
  * 1       64K
  * 2       256K
  */
/* LZMA level=1, when AES is enabled, TCM rans out if level 1 is used. */
//#define LZMA_MALLOC_BUFFER_SIZE  (80 * 1024)
/* LZMA level=0 */
#define LZMA_MALLOC_BUFFER_SIZE  (32 * 1024)
U8 g_lzma_malloc_buffer[LZMA_MALLOC_BUFFER_SIZE];

static void *SzAlloc(ISzAllocPtr p, size_t size)
{
    UNUSED(p);
    static size_t nUsed = 0;
    void *addr = NULL;

   nUsed += size;

   addr = (void*)(&(g_lzma_malloc_buffer[nUsed - size]));
   printk("SzAlloc nUsed:%d size:%d addr:%x", nUsed, size, addr);
   return addr;
}

static void SzFree(ISzAllocPtr p, void *address)
{
    UNUSED(p);
    UNUSED(address);

    printk("SzFree addr:%x", address);
 return;
}

static ISzAlloc g_Alloc = { SzAlloc, SzFree };

#define IN_BUF_SIZE 0x100
#define OUT_BUF_SIZE 0x1000
__attribute__ ((__aligned__(4)))U8 inBuf[IN_BUF_SIZE];
__attribute__ ((__aligned__(4)))U8 outBuf[OUT_BUF_SIZE];

#ifdef FOTA_UPGRADE_AES_SUPPORT
__attribute__ ((__aligned__(4)))U8 inAesBuf[IN_BUF_SIZE] = {0};
U8 g_aes_key[]={0xf,0xe,0xd,0xc,0xb,0xa,9,8,7,6,5,4,3,2,1,0};
U8 g_aes_iv[]={'c','7','8','2','d','c','4','c','0','9','8','c','6','6','c','b'};
#endif

U8 eraseFlag;

DFU_ERRCODE bl_fota_lzma_decompress(U32 src_addr, U32 srcLen)
{
    U32 unpackSize;  // current unpacked data size
    int i;
    SRes res = SZ_OK;
    int err = DFU_ERR_SUCCESS;
    U32 srcIdx = IN_BUF_SIZE;  // index of the un-read data in src_addr
    U32 data_4k_index = 0;

    CLzmaDec state;
    unsigned char header[LZMA_PROPS_SIZE + 8];

#ifdef AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
    U32 partable2_adddress = lp_index_get_begin_address(LAYOUT_PARTITION_1, PARTITION_ERASE_BACKUP);
    U32 partable2_phy_adddress = partable2_adddress & (~HAL_FLASH_BASE_ADDRESS);
#endif


    printk("lzma start");

#ifdef FOTA_UPGRADE_AES_SUPPORT

    if (Lzma_Aes == g_compression_type)
    {
        printk("AES init");
    }
#endif

#ifdef FOTA_UPGRADE_AES_SUPPORT
    if (Lzma_Aes == g_compression_type)
    {
        err = bsp_flash_read(src_addr, inAesBuf, sizeof(inAesBuf));
    }
    else
    {
        err = bsp_flash_read(src_addr, inBuf, sizeof(inBuf));
    }
#else
    err = bsp_flash_read(src_addr, inBuf, sizeof(inBuf));
#endif

    if (BSP_FLASH_STATUS_OK != err)
    {
        return DFU_ERR_FLASH_CTRL_NVRAM_PAGE_READ_FAIL;
    }
    printk("count:1 Read one page to inBuf (256 bytes)");

#ifdef FOTA_UPGRADE_AES_SUPPORT
    if (Lzma_Aes == g_compression_type)
    {
        hal_aes_buffer_t aes_input;
        hal_aes_buffer_t aes_output;
        hal_aes_buffer_t aes_key;
        aes_input.length = sizeof(inAesBuf);
        aes_input.buffer = inAesBuf;
        aes_output.length = sizeof(inBuf);
        aes_output.buffer = inBuf;
        aes_key.length = sizeof(g_aes_key);
        aes_key.buffer = g_aes_key;
        err = hal_aes_cbc_decrypt(&aes_output, &aes_input, &aes_key, g_aes_iv);
        if (HAL_AES_STATUS_OK != err)
        {
            printk("AES decrypt failed. err:%d", err);
            return DFU_ERR_AES_DECRYPT_FAIL;
        }
    }
#endif

    for (unsigned int g = 0; g < sizeof(header); ++g)
    {
        header[g] = inBuf[g];
        printk("header[%d]:%x", g, header[g]);
    }

    unpackSize = 0;

    /* size in header is 8 bytes, but we use 4 bytes only */
    for (i = 0; i < 4; ++i)
    {
        unsigned char b = header[LZMA_PROPS_SIZE + i];
        unpackSize += (U32)b << (i * 8);
    }

    printk("fota_package unpackSize:%d", unpackSize);

    LzmaDec_Construct(&state);
    res = LzmaDec_Allocate(&state, header, LZMA_PROPS_SIZE, &g_Alloc);
    if (res != SZ_OK)
    {
        printk("LzmaDec_Allocate() failed res:%d", res);
        return DFU_ERR_AES_DECRYPT_FAIL;
    }

    {
        // inSize:
        // inPos:         // inPos: used size in inBuffer.
        // outPos: used size in outBuffer.
        // inSize: size of each segment of source data (0 bytes < 1 segment <= IN_BUF_SIZE bytes).
        size_t inPos = 13, inSize = IN_BUF_SIZE, outPos = 0;
        size_t count = 1;
        LzmaDec_Init(&state);

        for (;;)
        {
            /* reset wdt dog timer every loop*/
            hal_wdt_feed (HAL_WDT_FEED_MAGIC);

            /* 1 segment of source data has been processed completely. */
            if (inPos == inSize)
            {
                // read one page to inBuf (256 bytes)
#ifdef FOTA_UPGRADE_AES_SUPPORT
                if (Lzma_Aes == g_compression_type)
                {
                    err = bsp_flash_read(src_addr + srcIdx, inAesBuf, sizeof(inAesBuf));
                }
                else
                {
                    err = bsp_flash_read(src_addr + srcIdx, inBuf, sizeof(inBuf));
                }
#else
                err = bsp_flash_read(src_addr + srcIdx, inBuf, sizeof(inBuf));
#endif
                if (FOTA_ERRCODE_SUCCESS != err)
                {
                    printk("fota_flash_read() failed err:%d", err);
                    err = DFU_ERR_FLASH_CTRL_NVRAM_PAGE_READ_FAIL;
                    break;
                }

#ifdef FOTA_UPGRADE_AES_SUPPORT
                if (Lzma_Aes == g_compression_type)
                {
                    hal_aes_buffer_t aes_input;
                    hal_aes_buffer_t aes_output;
                    hal_aes_buffer_t aes_key;
                    aes_input.length  = sizeof(inAesBuf);
                    aes_input.buffer  = inAesBuf;
                    aes_output.length = sizeof(inBuf);
                    aes_output.buffer = inBuf;
                    aes_key.length    = sizeof(g_aes_key);
                    aes_key.buffer    = g_aes_key;
                    err = hal_aes_cbc_decrypt(&aes_output, &aes_input, &aes_key, g_aes_iv);
                    /* Loop time: 256 / 16 = 16 */
                    if (HAL_AES_STATUS_OK != err)
                    {
                        printk("AES decrypt failed. err:%d", err);
                        err = DFU_ERR_AES_DECRYPT_FAIL;
                        break;
                    }
                }
#endif
                inSize = IN_BUF_SIZE;
                if (srcIdx + IN_BUF_SIZE > srcLen)
                {
                    inSize = srcLen - srcIdx;
                }

                inPos = 0;
                srcIdx += inSize;
            }

            // inProcessed: un-decompressed data size in each segment of source data.
            SizeT inProcessed = inSize - inPos;

            // outProcessed: unused space size in outBuf.
            SizeT outProcessed = OUT_BUF_SIZE - outPos;
            ELzmaFinishMode finishMode = LZMA_FINISH_ANY;
            ELzmaStatus status;

            if (outProcessed > unpackSize)
            {
                outProcessed = (SizeT)unpackSize;
                finishMode = LZMA_FINISH_END;
            }

            res = LzmaDec_DecodeToBuf(&state, outBuf + outPos, &outProcessed,
                                      inBuf + inPos, &inProcessed, finishMode, &status);
            if (res != SZ_OK)
            {
                printk("LzmaDec_DecodeToBuf failed. res:%d", res);
                return DFU_ERR_AES_IV_NOT_MATCH;
            }

            if (inProcessed == 0 && outProcessed == 0)
            {
                if (status != LZMA_STATUS_FINISHED_WITH_MARK)
                {
                    res = SZ_ERROR_DATA;
                    printk("LzmaDec status error. status:%d res:%d", status, res);
                }
                break;
            }

            inPos += (UInt32)inProcessed;
            outPos += outProcessed;
            unpackSize -= outProcessed;


            // Write the decompressed data into the Flash when the size of the decompressed data reaches 4K.
            if (outPos == OUT_BUF_SIZE)
            {
                U32 target_address = g_fota_data_4k_target_table[data_4k_index];

                if(eraseFlag == FALSE)
                {
                    for (U32 i = 0; i < g_number_of_movers; ++i)
                    {
                        U32 targetAddr  = g_movers[i].destination_address;
                        U32 totalLength = g_movers[i].length;

#ifdef  AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
                        if(targetAddr == partable2_phy_adddress)
                        {
                            fota_clear_parttable2_state();
                            fota_parttable2_state_write(FOTA_PART_STATE_UPDATING_PARTABLE2);
                            printk("partition table2 fota, state:%x, target_addr:%x", FOTA_PART_STATE_UPDATING_PARTABLE2, target_address);
                            printk("erase partition table2");
                            DFU_ERRCODE dfu_err_code = bl_fota_flash_erase(target_address, 0x1000);
                            if (dfu_err_code != DFU_ERR_SUCCESS)
                            {
                                printk("Erase flash failed. data_4k_index:%d, addr:%x, err:%d", data_4k_index, target_address, dfu_err_code);
                                return DFU_ERR_MOVE_DATA_ERASE_FAIL;
                            }
                        }
                        else
                        {
#endif
                            while(totalLength)
                            {
                                U32 eraseLength = totalLength;

                                /* erase 256K once*/
                                if(totalLength > 0x40000)
                                {
                                    eraseLength = 0x40000;
                                }

                                DFU_ERRCODE dfu_err_code = bl_fota_flash_erase(targetAddr, eraseLength);

                                targetAddr  += eraseLength;
                                totalLength -= eraseLength;

                                if (dfu_err_code != DFU_ERR_SUCCESS)
                                {
                                    printk("Erase flash failed. data_4k_index:%d, addr:%x, err:%d", data_4k_index, target_address, dfu_err_code);
                                    return DFU_ERR_MOVE_DATA_ERASE_FAIL;
                                }
                            }
#ifdef  AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
                         }
#endif
                    }
                    eraseFlag = TRUE;
                }

                U32 page_count = 0x1000 / 0x100;
                U32 offset = 0;
                printk("Count = %d , Write %d bytes decompressed data into Flash address %x ",count, OUT_BUF_SIZE, target_address);
                count++;
                {
                    for (U32 z = 0; z < page_count; ++z)
                    {
                        err = bsp_flash_write(target_address + offset, outBuf + offset, 256);

                        if(err != BSP_FLASH_STATUS_OK)
                        {
                            printk("err=%d count=%d offset=%d Address=%x",err,count,offset,target_address + offset);
                        }

                        offset += 0x100;
                    }
                }
                outPos = 0;
                ++data_4k_index;
            }

            if (unpackSize == 0)
            {
                printk("unpackSize is 0 now. All compressed data has been processed");
                break;
            }
        }
    }

    /* fota integrity check */
    if(g_is_sha_info_found == TRUE)
    {
        for (U32 i = 0; i < g_number_of_movers; ++i)
        {
            U8 oriSHA[BL_FOTA_SHA256_HASH_SIZE__BYTES];
            U8 sha256[BL_FOTA_SHA256_HASH_SIZE__BYTES];
            U32 is_int;

            memset(oriSHA,0,sizeof(oriSHA));
            memset(sha256,0,sizeof(sha256));

#ifdef BSP_EXTERNAL_SERIAL_FLASH_ENABLED
            /* decide internel or external flash */
            if(!(g_movers[i].destination_address & SPI_SERIAL_FLASH_ADDRESS))
#endif
            {
                is_int = 1;
            }
#ifdef BSP_EXTERNAL_SERIAL_FLASH_ENABLED
            else
            {
                is_int = 0;
            }
#endif

            err = fota_sha256_generate((unsigned char*)sha256, g_movers[i].destination_address, g_movers[i].length , is_int);
            if(err != DFU_ERR_SUCCESS)
            {
                printk("sha 256 generate fail :%d, addr:%x, len:%d",err, g_movers[i].destination_address, g_movers[i].length);
                break;
            }

            bsp_flash_read(g_sha_info_start_address + sizeof(oriSHA)*i, (uint8_t *)oriSHA, sizeof(oriSHA));

            if (memcmp(oriSHA ,sha256 ,sizeof(sha256)))
            {
                printk("sha number not match, mover:%d", i);

                for(U32 j = 0; j < BL_FOTA_SHA256_HASH_SIZE__BYTES; j += sizeof(uint32_t))
                {
                    printk("gen_sha[%d]=%u", j, *(uint32_t *)&sha256[j]);
                }

                for(U32 j = 0; j < BL_FOTA_SHA256_HASH_SIZE__BYTES; j += sizeof(uint32_t))
                {
                    printk("ori_sha[%d]=%u", j, *(uint32_t *)&oriSHA[j]);
                }

                err = DFU_ERR_SHA_MATCH_FAIL;
                break;
            }
        }
    }

    LzmaDec_Free(&state, &g_Alloc);

    printk("err:%d res:%d", err, res);

    if (DFU_ERR_SUCCESS == err && SZ_OK != res)
    {
        err = DFU_ERR_FAIL;
    }

    return err;
}

DFU_ERRCODE bl_fota_move_data(VOID)
{
    U32 i;
    DFU_ERRCODE err_code;
    BOOL ret = FALSE;
    uint32_t src_addr = 0, dst_addr = 0, total_written_len = 0, written_len = FOTA_WRITE_READ_LENGTH;

    printk("bl_fota_move_data");
    if (g_fota_partition_start_address == 0) // impossible address
    {
        printk("FOTA partition start address is 0");
        return DFU_ERR_INVALID_FOTA_ADDR;
    }

    if (!bl_fota_is_mover_info_valid())
    {
        printk("mover is not valid");
        return DFU_ERR_MOVER_INVALID;
    }

    printk("g_compression_type = %d",g_compression_type);

    if (Lzma == g_compression_type || Lzma_Aes == g_compression_type)
    {
        ret = bl_gen_each_4k_target_addr_table();
        if (!ret)
        {
            printk("Failed to generate each_4k_target_addr_table");
            return DFU_ERR_FLASH_SIZE_NOT_MATCH;
        }

        return bl_fota_lzma_decompress(g_fota_data_start_address, g_fota_data_length);
    }

    for (i = 0; i < g_number_of_movers; ++i)
    {
        dst_addr = g_movers[i].destination_address;

        err_code = bl_fota_flash_erase(dst_addr, g_movers[i].length);
        if (err_code != DFU_ERR_SUCCESS)
        {
            return err_code;
        }

        err_code = bl_fota_flash_verify_erase(dst_addr, g_movers[i].length);
        if (err_code != DFU_ERR_SUCCESS)
        {
            return err_code;
        }

        src_addr = g_fota_partition_start_address + g_movers[i].source_address;

        total_written_len = 0;
        written_len = FOTA_WRITE_READ_LENGTH;

        while (g_movers[i].length && total_written_len < g_movers[i].length)
        {
            if (FOTA_WRITE_READ_LENGTH > (g_movers[i].length - total_written_len))
            {
                written_len = g_movers[i].length - total_written_len;
            }

            if (BSP_FLASH_STATUS_OK != bsp_flash_read(src_addr, outBuf, written_len))
            {
                return DFU_ERR_FLASH_CTRL_NVRAM_PAGE_READ_FAIL;
            }

            if (BSP_FLASH_STATUS_OK != bsp_flash_write(dst_addr, outBuf, written_len))
            {
                return DFU_ERR_FLASH_CTRL_NVRAM_PAGE_WRITE_FAIL;
            }

            if (DFU_ERR_SUCCESS != bl_fota_flash_verify_data(dst_addr, outBuf, written_len))
            {
                return err_code;
            }

            total_written_len += written_len;
            printk("src_addr:%x, dst_addr:%x, total_written_len:%d, written_len:%d", src_addr, dst_addr, total_written_len, written_len);
            src_addr += written_len;
            dst_addr += written_len;

        }
    }

    return DFU_ERR_SUCCESS;
}

#ifdef AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE

uint8_t bl_fota_partition_table_init(void)
{
    lp_status lp1_status;
    lp_status lp2_status;
    uint16_t part_state = FOTA_PART_STATE_INITIAL;
    uint8_t status = DFU_ERR_SUCCESS;

    lp1_status = lp_index_init(LAYOUT_PARTITION_1);
    printk("init partition table1, state: %x", lp1_status);
    if(lp1_status != LAYOUT_PARTITION_OK)
    {
        printk("partition table1 init fail: %d", lp1_status);
        status = DFU_ERR_LP1_INIT_FAIL;
        return status;
    }

    //Check Partition Table FOTA State
    fota_parttable2_state_read(&part_state);
    printk("part_state: %x", part_state);
    if(part_state != FOTA_PART_STATE_UPDATING_PARTABLE2)
    {
        lp2_status = lp_index_init(LAYOUT_PARTITION_2);
        printk("init partition table1, state: %x", lp2_status);
        if(lp2_status != LAYOUT_PARTITION_OK)
        {
            printk("partition table2 init fail: %d", lp2_status);
            status = DFU_ERR_LP2_INIT_FAIL;
            return status;
        }
    }
    return status;
}

#endif

void bl_fota_process (void)
{
    DFU_ERRCODE err_code = DFU_ERR_FAIL;
    uint16_t state;
    uint32_t eraseLength;
    uint32_t result;
#ifdef AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
    uint16_t part_state = FOTA_PART_STATE_INITIAL;
#endif

    printk("%s", __FUNCTION__);

#ifdef AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
    uint8_t partable_status = bl_fota_partition_table_init();
    if(partable_status != DFU_ERR_SUCCESS)
    {
        printk( "bl_fota_partition_table_init fail: %x\r\n", partable_status);
    }
    else
    {
        printk( "bl_fota_partition_table_init pass: %x\r\n", partable_status);
    }
#endif


    fota_init_flash();
#if FOTA_STORE_IN_EXTERNAL_FLASH
    fota_flash_config_fota_partition_in_external_flash(FOTA_EXT_RESERVED_BASE_DEFAULT,
                                                       FOTA_EXT_RESERVED_LENGTH_DEFAULT);
#endif

    err_code = fota_state_read(&state);
    if(err_code != DFU_ERR_SUCCESS)
    {
        printk("FOTA state read error");
    }

    if (state == FOTA_STATE_LOADER_START_DATA_MOVING)
    {
    }
    else if (state == FOTA_STATE_LOADER_ERASE_PACKAGE)
    {
        printk("FOTA erase package not finish");

        FotaStorageType storage_type;
        U32 length;

        if (fota_flash_get_slot_info(&storage_type, (uint32_t *)&g_fota_partition_start_address, (uint32_t *)&length) != FOTA_ERRCODE_SUCCESS)
        {
            return;
        }

        if( storage_type == ExternalFlash)
        {
#ifdef BSP_EXTERNAL_SERIAL_FLASH_ENABLED
            g_fota_partition_start_address |= SPI_SERIAL_FLASH_ADDRESS;
#else
            printk("External flash is not supported!");
            return;
#endif
        }

        /* erase all partition */
        bl_fota_flash_erase((U32)g_fota_partition_start_address, length - 0x1000);

        goto fota_OK;
    }
    else
    {
        int flag = fota_upgrade_flag_is_set();

        if (flag == 0)
        {
            printk("upgrade_flag is not set.");
            return;
        }
    }

    printk("Begin FOTA upgrade");

    if (fota_check_fota_package_integrity(!FOTA_FLASH_TYPE) != FOTA_ERRCODE_SUCCESS)
    {
        printk("Integrity Check fail");

        result = FOTA_STATE_LOADER_PACKAGE_NG;

        goto fota_fail;
    }

    if (!bl_fota_init())
    {
        printk("bl_fota_init fail");

        result = FOTA_STATE_LOADER_PACKAGE_NG;

        goto fota_fail;
    }

    fota_state_write(FOTA_STATE_LOADER_START_DATA_MOVING);

    err_code = bl_fota_move_data();

    if (err_code != DFU_ERR_SUCCESS)
    {
        printk("bl_fota_move_data() failed. err:%x", err_code);

        if(err_code == DFU_ERR_AES_IV_NOT_MATCH ||
           err_code == DFU_ERR_AES_DECRYPT_FAIL ||
           err_code == DFU_ERR_MOVER_INVALID    ||
           err_code == DFU_ERR_FLASH_SIZE_NOT_MATCH)
        {
            result = FOTA_STATE_LOADER_PACKAGE_NG;
        }
        else
        {
            result = FOTA_STATE_LOADER_DATA_MOVING_FAIL;
        }

        goto fota_fail;
    }

    hal_wdt_feed (HAL_WDT_FEED_MAGIC);

    /* set fota version*/
    FOTA_ERRCODE tmp_status = fota_version_set(version, versionLength, FOTA_VERSION_TYPE_STORED);
    if(tmp_status != FOTA_ERRCODE_SUCCESS)
    {
        printk("fota_version_set:%x, fota version :%s, versionLength: %x", tmp_status, version, versionLength);
    }

    /* go to erase package state */
    fota_state_write(FOTA_STATE_LOADER_ERASE_PACKAGE);

    eraseLength = g_fota_data_start_address - g_fota_partition_start_address + g_fota_data_length;

    /* erase fota package */
    bl_fota_flash_erase((U32)g_fota_partition_start_address, eraseLength);

fota_OK:

    printk("FOTA upgrade complete");

    result = FOTA_STATE_LOADER_COMPLETE_DATA_MOVING;
#ifdef AIR_FOTA_MEMORY_LAYOUT_CHANGE_ENABLE
    fota_parttable2_state_read(&part_state);
    if(part_state == FOTA_PART_STATE_UPDATING_PARTABLE2)
    {
        fota_parttable2_state_write(FOTA_PART_STATE_COMPLETE_PARTABLE2);
    }
#endif

fota_fail:

    if(result == FOTA_STATE_LOADER_PACKAGE_NG || result == FOTA_STATE_LOADER_COMPLETE_DATA_MOVING)
    {
        fota_upgrade_flag_clear();
    }

    fota_state_write(result);

    fota_device_reboot();
}

