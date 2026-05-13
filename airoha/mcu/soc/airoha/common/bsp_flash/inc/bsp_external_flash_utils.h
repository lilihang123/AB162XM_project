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


#ifndef __BSP_FLASH_UTILS_H__
#define __BSP_FLASH_UTILS_H__

#include <stdbool.h>
#include <assert.h>

#include <zephyr/kernel.h>

#include "memory_attribute.h"

#include "hal_platform.h"
#include "bsp_external_flash.h"

#ifdef BSP_EXTERNAL_SERIAL_FLASH_ENABLED

//Quad program should be 256 byte one time
#define WRITE_BUFFER_SIZE     (0x100)
#define FLASH_DADA_MAX_LENGTH (0x1000)

#define FLASH_BUSY      (0x1)
#define FLASH_INIT      (2)
#define FLASH_NOT_INIT  (-1)

#define ADDRESS_MASK_3_BYTES        (0x00FFFFFF)

#define COMMAND_LENGTH    (0x8)

typedef enum {
    FLASH_STATUS_IDLE = 0,
    FLASH_STATUS_BUSY = 1,
} flash_status_t;

typedef struct {
    const char *name;
    uint32_t jedec_id;
    uint32_t n_pages;
    uint8_t page_size_idx;     /* idx of page size array, save memory */
    /* 0 => 3 bytes address
     * 1 => 4 bytes address
     */
    uint8_t addr_mode;
    uint8_t frd_cmd;     //fast read
    uint8_t frd_delay;   //fast read delay
    uint8_t wd_cmd;      //write
    uint8_t wd_delay;    //write delay
    uint8_t polling_data_offset;      //Delay cycles(includes command) for polling read
    uint8_t dma_data_off;    //Delay cycles(includes command) for DAM read
} flash_device_info_t;

typedef struct {
    /* To avoid deadlock issues, a mutex is needed to control mutually exclusive
     * access to the external flash instance.
     */
    struct k_mutex mutex;
    bool busy;
    int8_t init;
    const flash_device_info_t *p_dev;
    ATTR_ALIGN(16) uint8_t cmd_buffer[COMMAND_LENGTH];
    ATTR_ALIGN(16) uint8_t non_cache_buffer[FLASH_DADA_MAX_LENGTH + COMMAND_LENGTH];
} bsp_external_flash_control_block_t;

extern const bsp_external_flash_cfg_t bsp_external_flash_cfg[CONFIG_AIR_BSP_EXTERNAL_SERIAL_FLASH_NUM];
#define BEF_CTX_SIZE CONFIG_AIR_BSP_EXTERNAL_SERIAL_FLASH_NUM
extern bsp_external_flash_control_block_t bef_ctx[BEF_CTX_SIZE];
static_assert(CONFIG_AIR_BSP_EXTERNAL_SERIAL_FLASH_NUM < HAL_SPI_MASTER_MAX, \
    "Please check SPI port number and definition of CONFIG_AIR_BSP_EXTERNAL_SERIAL_FLASH_NUM");
/* the next is command set definition, please make sure the  */

#define THREE_BYTES_ADDRESS_MODE                    3
#define FOUR_BYTES_ADDRESS_MODE                     4

#define READ_SR                                     (0x05)
#define WRITE_SR                                    (0x01)
#define READ_SR_3                                   (0x15)
#define WRITE_SR_3                                  (0x11)
#define WRITE_ENABLE                                (0x06)
#define READ_RDID                                   (0x9F)
#define FAST_READ                                   (0x0B)
#define FAST_READ_WITH_4_BYTE_ADDR_MODE             (0x0C)
#define SPI_WRITE                                   (0x02)
#define SPI_WRITE_WITH_4_BYTE_ADDR_MODE             (0x12)
#define SECTOR_4K_ERASE                             (0x20)
#define BLOCK_32K_ERASE                             (0x52)
#define BLOCK_64K_ERASE                             (0xD8)
#define CHIP_ERASE                                  (0xC7)
#define EANBLE_RESET                                (0x66)
#define RESET_DEVICE                                (0x99)
#define ENTER_4_BYTE_ADDR_MODE                      (0xB7)
#define EXIT_4_BYTE_ADDR_MODE                       (0xE9)

void* bsp_flash_mutex_creat(void);

void bsp_flash_mutex_lock(void *p_mutex);

void bsp_flash_mutex_unlock(void *p_mutex);

void bsp_flash_mutex_delete(void *p_mutex);

bool bsp_curr_is_in_task(void);

uint32_t reflect_cfg_idx(uint32_t logic_addr);

flash_status_t read_status_register(uint32_t cfg_idx, uint32_t command, uint8_t *sr_status);

flash_status_t write_status_register(uint32_t cfg_idx, uint32_t command, uint8_t sr);

flash_status_t write_status_register_2(uint32_t cfg_idx, uint32_t command, uint8_t sr, uint8_t sr2);

bsp_external_flash_status_t bsp_external_flash_get_rdid(uint32_t cfg_idx, uint8_t *buffer);

bsp_external_flash_status_t spi_flash_read_polling(uint32_t cfg_idx, uint32_t address, uint8_t *buffer, uint32_t length);

bsp_external_flash_status_t spi_flash_read_dma(uint32_t cfg_idx, uint32_t address, uint8_t *buffer, uint32_t length);

bsp_external_flash_status_t spi_flash_write_polling(uint32_t cfg_idx, uint32_t address, uint8_t *data, int32_t length);

int32_t spi_flash_write_dma(uint32_t cfg_idx, uint32_t address, uint8_t *data, int32_t length);

flash_status_t spi_external_flash_get_status(uint32_t cfg_idx);

flash_status_t wait_flash_ready(uint32_t cfg_idx, uint32_t ms);

bsp_external_flash_status_t bsp_external_flash_read_internal(uint32_t address, uint8_t *buffer, uint32_t length, bool blocking);
bsp_external_flash_status_t bsp_external_flash_write_internal(uint32_t address, uint8_t *data, int32_t length, bool blocking);
bsp_external_flash_status_t bsp_external_flash_erase_internal(uint32_t address, block_size_type_t block_size, bool blocking);

#endif //BSP_EXTERNAL_SERIAL_FLASH_ENABLED

#endif /* __BSP_FLASH_UTILS_H__ */