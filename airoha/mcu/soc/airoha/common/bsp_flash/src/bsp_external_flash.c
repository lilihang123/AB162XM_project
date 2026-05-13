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
#include <zephyr/irq.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/types.h>
#include <zephyr/device.h>
#include <zephyr/sys/util.h>
#include <sys/types.h>

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* hal includes */
#include "hal_spi_master.h"
#include "hal_log.h"
#include "hal_gpt.h"
#include "bsp_external_flash.h"
#include "bsp_external_flash_utils.h"
#include "memory_attribute.h"

#ifdef BSP_EXTERNAL_SERIAL_FLASH_ENABLED

bsp_external_flash_control_block_t bef_ctx[BEF_CTX_SIZE];

/* HAL_SPI_MAXIMUM_POLLING_TRANSACTION_SIZE includes the sent CMD size and received data size
 *  so it can receive 32 - 5 (read cmd + 4 byte address support)
 */
#define SPI_EXT_FLASH_MAX_READ_SIZE_WITH_POLLING  (HAL_SPI_MAXIMUM_POLLING_TRANSACTION_SIZE - 5)
const static uint32_t nor_flash_page_sizes[] = { 256 };
const static flash_device_info_t support_flash_list[] = {
    {
        .name = "W25Q51RV",                         .jedec_id = 0x00EF4020,
        .n_pages = 64 * 1024 * 4,                   .page_size_idx = 0,     /* means 256 bytes */
        .addr_mode = FOUR_BYTES_ADDRESS_MODE,
        .frd_cmd = FAST_READ_WITH_4_BYTE_ADDR_MODE,
        .frd_delay = 8,
        .wd_cmd = SPI_WRITE_WITH_4_BYTE_ADDR_MODE,
        .wd_delay = 0,
        .polling_data_offset = 6,
        .dma_data_off = 6,
    },
    {
        .name = "W25Q32RV",                         .jedec_id = 0x00EF4016,
        .n_pages = 4 * 1024 * 4,                    .page_size_idx = 0,     /* means 256 bytes */
        .addr_mode = THREE_BYTES_ADDRESS_MODE,
        .frd_cmd = FAST_READ,
        .frd_delay = 8,
        .wd_cmd = SPI_WRITE,
        .wd_delay = 0,
        .polling_data_offset = 5,
        .dma_data_off = 5,
    },
};


uint32_t get_flash_size(uint32_t cfg_idx)
{
    uint32_t size;
    if ((cfg_idx < BEF_CTX_SIZE) && \
        (bef_ctx[cfg_idx].p_dev != NULL))
    {
        __ASSERT_NO_MSG(bef_ctx[cfg_idx].p_dev->page_size_idx < sizeof(nor_flash_page_sizes));
        size = nor_flash_page_sizes[bef_ctx[cfg_idx].p_dev->page_size_idx] * bef_ctx[cfg_idx].p_dev->n_pages;
    } else {
        size = 0;
    }
    return size;
}


ATTR_WEAK_SYMBOL void bsp_external_flash_function_enable(uint32_t logic_addr_cfg)
{
    ARG_UNUSED(logic_addr_cfg);
}

ATTR_WEAK_SYMBOL void bsp_external_flash_function_disable(uint32_t logic_addr_cfg)
{
    ARG_UNUSED(logic_addr_cfg);
}


void bsp_external_flash_enable(uint32_t logic_addr_cfg)
{
    /* It needs to be override according to the actual GPIO configuration of the project */
    bsp_external_flash_function_enable(logic_addr_cfg);
}

void bsp_external_flash_disable(uint32_t logic_addr_cfg)
{
    /* It needs to be override according to the actual GPIO configuration of the project */
    bsp_external_flash_function_disable(logic_addr_cfg);
}


bsp_external_flash_status_t bsp_external_flash_init(void)
{
    //flash reset command
    uint8_t reset_cmd[2] = {EANBLE_RESET, RESET_DEVICE};
    hal_spi_master_config_t spi_config;
    hal_spi_master_advanced_config_t advanced_config;
    uint32_t bef_idx;

    for(bef_idx = 0; bef_idx < BEF_CTX_SIZE; bef_idx++){
        if (bef_ctx[bef_idx].init == FLASH_INIT) {
            printk("[BSP External Flash] %d", __LINE__);
            return EXTERNAL_FLASH_STATUS_OK;
        }

        bsp_external_flash_enable(bsp_external_flash_cfg[bef_idx].logic_addr_cfg);

        //configure the right SPI
        spi_config.bit_order = HAL_SPI_MASTER_MSB_FIRST;
        spi_config.slave_port = HAL_SPI_MASTER_SLAVE_0;
        spi_config.clock_frequency = bsp_external_flash_cfg[bef_idx].spi_freq_in_MHz * 1000000;
        spi_config.phase = HAL_SPI_MASTER_CLOCK_PHASE0;
        spi_config.polarity = HAL_SPI_MASTER_CLOCK_POLARITY0;
        hal_spi_master_deinit(bsp_external_flash_cfg[bef_idx].spi_port);
        printk("[BSP External Flash] spi port %d", bsp_external_flash_cfg[bef_idx].spi_port);
        if (HAL_SPI_MASTER_STATUS_OK != hal_spi_master_init(bsp_external_flash_cfg[bef_idx].spi_port, &spi_config)) {
            printk("[BSP External Flash] %d", __LINE__);
            return EXTERNAL_FLASH_STATUS_ERROR;
        }

        advanced_config.byte_order = HAL_SPI_MASTER_LITTLE_ENDIAN;
        advanced_config.chip_polarity = HAL_SPI_MASTER_CHIP_SELECT_LOW;
        advanced_config.get_tick = HAL_SPI_MASTER_GET_TICK_DELAY1;
        advanced_config.sample_select = HAL_SPI_MASTER_SAMPLE_POSITIVE;  //default setting
        if (HAL_SPI_MASTER_STATUS_OK != hal_spi_master_set_advanced_config(bsp_external_flash_cfg[bef_idx].spi_port, &advanced_config)) {
            printk("[BSP External Flash] %d", __LINE__);
            return EXTERNAL_FLASH_STATUS_ERROR;
        }

        //hal_spi_master_set_macro_selection(bsp_external_flash_cfg[bef_idx].spi_port,HAL_SPI_MASTER_MACRO_GROUP_B);
        if (HAL_SPI_MASTER_STATUS_OK != hal_spi_master_send_polling(bsp_external_flash_cfg[bef_idx].spi_port, reset_cmd, 2)) {
            printk("[BSP External Flash] %d", __LINE__);
            return EXTERNAL_FLASH_STATUS_ERROR;
        }

        bef_ctx[bef_idx].busy = false;
        k_mutex_init(&(bef_ctx[bef_idx].mutex));
        bef_ctx[bef_idx].init = FLASH_INIT;
        {
            uint8_t flash_id[4];
            uint8_t i;
            uint32_t jedecid;
            hal_gpt_delay_ms(50);
            printk("[BSP External Flash] %d", __LINE__);
            bsp_external_flash_get_rdid(bef_idx, flash_id);
            printk("[BSP_EXTERNAL_FLASH] flash id: %x, %x, %x \r\n", flash_id[1], flash_id[2], flash_id[3]);

            jedecid = (flash_id[1] << 16) | (flash_id[2] << 8) | flash_id[3];
            for (i = 0; i < (sizeof(support_flash_list) / sizeof(support_flash_list[0])); i++) {
                if (support_flash_list[i].jedec_id == jedecid) {
                    bef_ctx[bef_idx].p_dev = &support_flash_list[i];
                    break;
                }
            }

            if (bef_ctx[bef_idx].p_dev == NULL) {
                printk("[BSP External Flash] %d", __LINE__);
                return EXTERNAL_FLASH_ERROR_NOT_FOUND_DEVICE;
            } else {
                if(bef_ctx[bef_idx].p_dev->addr_mode == THREE_BYTES_ADDRESS_MODE){
                    ;       /* nothing special */
                } else if (bef_ctx[bef_idx].p_dev->addr_mode == FOUR_BYTES_ADDRESS_MODE){
                    /* enter 4 byte address mode */
                    uint8_t enter_4_byte_addr_mode = ENTER_4_BYTE_ADDR_MODE;
                    uint8_t status_reg_3 = 0;
                    hal_spi_master_send_polling(bsp_external_flash_cfg[bef_idx].spi_port, &enter_4_byte_addr_mode, 1);
                    read_status_register(bef_idx, READ_SR_3, &status_reg_3);
                    printk("[BSP External Flash] status register 3: 0x%08X", (unsigned int)status_reg_3);
                } else {
                    __ASSERT_NO_MSG(0);
                }
            }
        }
    }
#if defined(AIR_BSP_EXTERNAL_SERIAL_FLASH_ASYNC_ENABLE)
    extern void bsp_external_flash_work_q_init(void);
    bsp_external_flash_work_q_init();
#endif /* defined(AIR_BSP_EXTERNAL_SERIAL_FLASH_ASYNC_ENABLE) */
    return EXTERNAL_FLASH_STATUS_OK;
}

/*
   should do de-initiation when not use it
*/
bsp_external_flash_status_t bsp_external_flash_deinit(void)
{
    int32_t status = FLASH_NOT_INIT;
    uint32_t bef_idx;

    for(bef_idx = 0; bef_idx < BEF_CTX_SIZE; bef_idx++){
        if (bef_ctx[bef_idx].init != FLASH_INIT) {
            status = EXTERNAL_FLASH_STATUS_NOT_INIT;
            printk("[BSP External Flash] EXTERNAL_FLASH_STATUS_NOT_INIT at line %d", __LINE__);
            continue;
        }

        /* De-init spi master */
        status = hal_spi_master_deinit(bsp_external_flash_cfg[bef_idx].spi_port);
        bef_ctx[bef_idx].init = FLASH_NOT_INIT;
        bef_ctx[bef_idx].busy = false;
        __ASSERT_NO_MSG(bef_ctx[bef_idx].mutex.lock_count == 0);
        __ASSERT_NO_MSG(bef_ctx[bef_idx].mutex.owner == NULL);

        bsp_external_flash_disable(bsp_external_flash_cfg[bef_idx].logic_addr_cfg);
    }
    return status;
}

bsp_external_flash_status_t bsp_external_flash_read_internal(uint32_t address, uint8_t *buffer, uint32_t length, bool blocking)
{
    int32_t status = FLASH_NOT_INIT;
    uint8_t *data = NULL;
    uint32_t read_length = 0;
    uint32_t data_length = length;
    uint32_t dev_capacity;
    uint32_t bef_idx = reflect_cfg_idx(address);
    if ((length == 0) || (buffer == NULL)) {
        printk("[BSP External Flash] %d", __LINE__);
        return EXTERNAL_FLASH_WRONG_PARAMETER;
    }
    if (bef_ctx[bef_idx].init != FLASH_INIT) {
        printk("[BSP External Flash] %d", __LINE__);
        return EXTERNAL_FLASH_STATUS_NOT_INIT;
    }

    data = &(bef_ctx[bef_idx].non_cache_buffer[0]);

    if(bef_ctx[bef_idx].p_dev->addr_mode == THREE_BYTES_ADDRESS_MODE){
        address &= ADDRESS_MASK_3_BYTES;
    } else if (bef_ctx[bef_idx].p_dev->addr_mode == FOUR_BYTES_ADDRESS_MODE){
        address -= bsp_external_flash_cfg[bef_idx].logic_addr_cfg;
    } else {
        __ASSERT_NO_MSG(0);
    }

    dev_capacity = get_flash_size(bef_idx);
    printk("[BSP External Flash] device capacity is %d KB", dev_capacity/0x400);

    if (address >= dev_capacity || address + length > dev_capacity) {
        printk("[BSP External Flash] %d", __LINE__);
        return EXTERNAL_FLASH_ERROR_WRONG_ADDRESS;
    }

    if (wait_flash_ready(bef_idx, 1)) {
        printk("[BSP External Flash] %d", __LINE__);
        return EXTERNAL_FLASH_STATUS_ERROR;
    }

    k_mutex_lock(&(bef_ctx[bef_idx].mutex), K_FOREVER);
    bef_ctx[bef_idx].busy = true;

    if ((data_length + bef_ctx[bef_idx].p_dev->polling_data_offset) <= SPI_EXT_FLASH_MAX_READ_SIZE_WITH_POLLING) {
        status = spi_flash_read_polling(bef_idx, address, data, data_length);
        // please should mind: data is start from cmd+addr+1
        memcpy(buffer, &data[bef_ctx[bef_idx].p_dev->polling_data_offset], data_length);
        printk("[BSP External Flash] %d", __LINE__);
        bef_ctx[bef_idx].busy = false;
        k_mutex_unlock(&(bef_ctx[bef_idx].mutex));
        return status;
    }

    while (data_length > FLASH_DADA_MAX_LENGTH) {
        read_length = FLASH_DADA_MAX_LENGTH;
        printk("[BSP External Flash] not run to here");
        spi_flash_read_dma(bef_idx, address, data, read_length);
        memcpy(buffer, &data[bef_ctx[bef_idx].p_dev->dma_data_off], read_length);
        buffer = buffer + read_length;
        address = address + read_length;
        data_length = data_length - read_length;
    }

    read_length = data_length;
    printk("[BSP External Flash] address: 0x%08X, data: 0x%08X, length: %d",
        (unsigned int)address,
        (unsigned int)data,
        (unsigned int)data_length
    );
    status = spi_flash_read_dma(bef_idx, address, data, data_length);
    __ASSERT_NO_MSG(status == 0);
    memcpy(buffer, &data[bef_ctx[bef_idx].p_dev->dma_data_off], data_length);

    bef_ctx[bef_idx].busy = false;
    k_mutex_unlock(&(bef_ctx[bef_idx].mutex));
    printk("[BSP External Flash] %d", __LINE__);
    return EXTERNAL_FLASH_STATUS_OK;
}


/**
 * @brief This function read data from serial flash.
 * @param[in] address:  read address.
 * @param[in] buffer: buffer for read data
 * @param[in] length: read data length
 */
bsp_external_flash_status_t bsp_external_flash_read(uint32_t address, uint8_t *buffer, uint32_t length)
{
    return bsp_external_flash_read_internal(address, buffer, length, true);
}


bsp_external_flash_status_t bsp_external_flash_write_internal(uint32_t address, uint8_t *data, int32_t length, bool blocking)
{
    int32_t status = FLASH_NOT_INIT;
    uint8_t *buffer = data;
    uint32_t write_length;
    uint32_t page_offset;
    int32_t len = length;
    uint32_t addr = address;
    uint32_t dev_capacity;
    uint32_t bef_idx = reflect_cfg_idx(address);
    if (bef_ctx[bef_idx].init != FLASH_INIT) {
        printk("[BSP External Flash] %d", __LINE__);
        return EXTERNAL_FLASH_STATUS_NOT_INIT;
    }
    if (length == 0 || data == NULL) {
        printk("[BSP External Flash] %d", __LINE__);
        return EXTERNAL_FLASH_WRONG_PARAMETER;
    }
    if (wait_flash_ready(bef_idx, 2)) {
        printk("[BSP External Flash] %d", __LINE__);
        return status;
    }

    if(bef_ctx[bef_idx].p_dev->addr_mode == THREE_BYTES_ADDRESS_MODE){
        address = address & ADDRESS_MASK_3_BYTES;
    } else if (bef_ctx[bef_idx].p_dev->addr_mode == FOUR_BYTES_ADDRESS_MODE){
        address -= bsp_external_flash_cfg[bef_idx].logic_addr_cfg;
    } else {
        __ASSERT_NO_MSG(0);
    }

    dev_capacity = get_flash_size(bef_idx);
    if (address >= dev_capacity || address + length > dev_capacity) {
        printk("[BSP External Flash] %d", __LINE__);
        return EXTERNAL_FLASH_ERROR_WRONG_ADDRESS;
    }

    printk("[BSP External Flash] write: address = 0x%x ,len= %d \r\n", address, length);

    k_mutex_lock(&(bef_ctx[bef_idx].mutex), K_FOREVER);
    bef_ctx[bef_idx].busy = true;

    page_offset = address % WRITE_BUFFER_SIZE;
    while (len > 0) {
        write_length = MIN(len, (WRITE_BUFFER_SIZE - page_offset));
        page_offset = 0;
        if ((write_length + 4) <= SPI_EXT_FLASH_MAX_READ_SIZE_WITH_POLLING) {
            status = spi_flash_write_polling(bef_idx, addr, buffer, write_length);
            if (status != EXTERNAL_FLASH_STATUS_OK) {
                printk("[BSP External Flash] %d", __LINE__);
                bef_ctx[bef_idx].busy = false;
                k_mutex_unlock(&(bef_ctx[bef_idx].mutex));
                return EXTERNAL_FLASH_STATUS_ERROR;
            }
        } else {
            status = spi_flash_write_dma(bef_idx, addr, buffer, write_length);
            if (status != EXTERNAL_FLASH_STATUS_OK) {
                printk("[BSP External Flash] %d, status: %d", __LINE__, status);
                bef_ctx[bef_idx].busy = false;
                k_mutex_unlock(&(bef_ctx[bef_idx].mutex));
                return EXTERNAL_FLASH_STATUS_ERROR;
            }
        }
        buffer += write_length;
        addr += write_length;
        len -= write_length;
    }
    bef_ctx[bef_idx].busy = false;
    k_mutex_unlock(&(bef_ctx[bef_idx].mutex));
    printk("[BSP External Flash] %d", __LINE__);
    return EXTERNAL_FLASH_STATUS_OK;
}

/**
 * @brief This function write data to serial flash.
 * @param[in] address:  write address.
 * @param[in] data: write data
 * @param[in] length: write data length
 */
bsp_external_flash_status_t bsp_external_flash_write(uint32_t address, uint8_t *data, int32_t length)
{
    return bsp_external_flash_write_internal(address, data, length, true);
}


bsp_external_flash_status_t bsp_external_flash_erase_internal(uint32_t address, block_size_type_t block_size, bool blocking)
{
    int32_t status = FLASH_NOT_INIT;
    uint8_t *cmd = NULL;
    uint32_t cmd_indx;
    uint32_t dev_capacity;
    uint32_t bef_idx = reflect_cfg_idx(address);
    uint32_t original_address = address;
    uint32_t erase_size;
    if (bef_ctx[bef_idx].init != FLASH_INIT) {
        return EXTERNAL_FLASH_STATUS_NOT_INIT;
    }
    if (block_size < FLASH_BLOCK_4K || block_size > FLASH_CHIP_ERASE) {
        return (status = EXTERNAL_FLASH_WRONG_PARAMETER);
    }
    if (wait_flash_ready(bef_idx, 2)) {
        return EXTERNAL_FLASH_STATUS_BUSY;
    }

    cmd = &(bef_ctx[reflect_cfg_idx(address)].cmd_buffer[0]);

    if(bef_ctx[bef_idx].p_dev->addr_mode == THREE_BYTES_ADDRESS_MODE){
        address = address & ADDRESS_MASK_3_BYTES;
    } else if (bef_ctx[bef_idx].p_dev->addr_mode == FOUR_BYTES_ADDRESS_MODE){
        address -= bsp_external_flash_cfg[bef_idx].logic_addr_cfg;
    } else {
        __ASSERT_NO_MSG(0);
    }

    dev_capacity = get_flash_size(bef_idx);
    if (address >= dev_capacity) {
        printk("[BSP External Flash] erase: address = %d, dev_capacity = 0x%x \r\n", address, dev_capacity);
        return EXTERNAL_FLASH_ERROR_WRONG_ADDRESS;
    }

    cmd_indx = 0;
    cmd[cmd_indx++] = WRITE_ENABLE;
    if (HAL_SPI_MASTER_STATUS_OK != hal_spi_master_send_polling(bsp_external_flash_cfg[bef_idx].spi_port, cmd, cmd_indx)) {
        return EXTERNAL_FLASH_STATUS_ERROR;
    }

    printk("[BSP External Flash] original_address: 0x%08X, offset: 0x%08X, type: %d",
        (unsigned int)original_address,
        (unsigned int)address,
        (unsigned int)block_size
    );
    k_mutex_lock(&(bef_ctx[bef_idx].mutex), K_FOREVER);
    bef_ctx[bef_idx].busy = true;

    wait_flash_ready(bef_idx, 1);
    cmd_indx = 0;
    if (block_size == FLASH_CHIP_ERASE) {
        cmd[cmd_indx++] = CHIP_ERASE;   // CHIP ERASE  0X60 OR 0XC7
        if (HAL_SPI_MASTER_STATUS_OK != hal_spi_master_send_polling(bsp_external_flash_cfg[bef_idx].spi_port, cmd, cmd_indx)) {
            bef_ctx[bef_idx].busy = false;
            k_mutex_unlock(&(bef_ctx[bef_idx].mutex));
            return EXTERNAL_FLASH_STATUS_ERROR;
        }
    } else {
        cmd_indx = 0;
        if (block_size == FLASH_BLOCK_4K) {
            cmd[cmd_indx++] = SECTOR_4K_ERASE;   // SECTOR 4K ERASE
            erase_size = 0x1000;
        } else if (block_size == FLASH_BLOCK_32K) {
            cmd[cmd_indx++] = BLOCK_32K_ERASE;   // BLOCK 32K ERASE
            erase_size = 0x8000;
        } else if (block_size == FLASH_BLOCK_64K) {
            cmd[cmd_indx++] = BLOCK_64K_ERASE;   // BLOCK 64K ERASE
            erase_size = 0x10000;
        }
        /* address of erase operating should be aligned with erase size
         * ex. erase 64KB at 0x123456 => ERROR
         *     erase 64KB at 0x120000 => VALID
         */
        __ASSERT_NO_MSG((address % erase_size) == 0);

        if(bef_ctx[bef_idx].p_dev->addr_mode == THREE_BYTES_ADDRESS_MODE){
            cmd[cmd_indx++] = address >> 16;  // 1: 3 byte address
            cmd[cmd_indx++] = address >> 8;   // 2: 3 byte address
            cmd[cmd_indx++] = address;        // 3: 3 byte address
        } else if (bef_ctx[bef_idx].p_dev->addr_mode == FOUR_BYTES_ADDRESS_MODE){
            cmd[cmd_indx++] = address >> 24;  // 1: 4 byte address
            cmd[cmd_indx++] = address >> 16;  // 2: 4 byte address
            cmd[cmd_indx++] = address >> 8;   // 3: 4 byte address
            cmd[cmd_indx++] = address;        // 4: 4 byte address
        } else {
            __ASSERT_NO_MSG(0);
        }
        status = hal_spi_master_send_polling(bsp_external_flash_cfg[bef_idx].spi_port, cmd, cmd_indx);
        if (HAL_SPI_MASTER_STATUS_OK != status) {
            bef_ctx[bef_idx].busy = false;
            k_mutex_unlock(&(bef_ctx[bef_idx].mutex));
            return EXTERNAL_FLASH_STATUS_ERROR;
        }
    }

    //Wait flash erase finished
    if (wait_flash_ready(bef_idx, 1000) == FLASH_STATUS_IDLE) {
        bef_ctx[bef_idx].busy = false;
        k_mutex_unlock(&(bef_ctx[bef_idx].mutex));
        return EXTERNAL_FLASH_STATUS_OK;
    }
    bef_ctx[bef_idx].busy = false;
    k_mutex_unlock(&(bef_ctx[bef_idx].mutex));
    return EXTERNAL_FLASH_STATUS_ERROR;
}

/**
 * @brief This function erase the serial flash with sector, block or chip .
 * @param[in] address: erase start address.
 * @param[in] block_size: erase block size
 * @return
 */
bsp_external_flash_status_t bsp_external_flash_erase(uint32_t address, block_size_type_t block_size)
{
    return bsp_external_flash_erase_internal(address, block_size, true);
}
#endif //BSP_EXTERNAL_SERIAL_FLASH_ENABLED

