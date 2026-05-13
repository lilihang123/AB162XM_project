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


#include <zephyr/irq.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/types.h>
#include <zephyr/device.h>
#include <sys/types.h>

/* zephyr/lib/libc/minimal/include/errno.h */
#include <errno.h>

#include "air_chip.h"
#include "hal_gpt.h"
#include "hal_spi_master.h"
#include "bsp_external_flash.h"
#include "bsp_external_flash_utils.h"


#ifdef BSP_EXTERNAL_SERIAL_FLASH_ENABLED
#if IS_ENABLED(CONFIG_MULTITHREADING)

void* bsp_flash_mutex_creat(void)
{
    void *p_mutex = k_malloc(sizeof(struct k_mutex));
    __ASSERT_NO_MSG(p_mutex != NULL);
    k_mutex_init(p_mutex);
    return p_mutex;
}

void bsp_flash_mutex_lock(void *p_mutex)
{
    k_mutex_lock(p_mutex, K_FOREVER);
}

void bsp_flash_mutex_unlock(void *p_mutex)
{
    k_mutex_unlock(p_mutex);
}

void bsp_flash_mutex_delete(void *p_mutex)
{
    __ASSERT_NO_MSG(p_mutex != NULL);
    k_mutex_init(p_mutex);
    k_free(p_mutex);
}

#else
void* bsp_flash_mutex_creat(void)
{
    return NULL;
}
void bsp_flash_mutex_lock(void *p_mutex)
{
    ARG_UNUSED(p_mutex);
    __ASSERT_NO_MSG(bsp_curr_is_in_task());
}
void bsp_flash_mutex_unlock(void *p_mutex)
{
    ARG_UNUSED(p_mutex);
    __ASSERT_NO_MSG(bsp_curr_is_in_task());
}
void bsp_flash_mutex_delete(void *p_mutex)
{
    ARG_UNUSED(p_mutex);
    __ASSERT_NO_MSG(bsp_curr_is_in_task());
}
#endif /* IS_ENABLED(CONFIG_MULTITHREADING) */

bool bsp_curr_is_in_task(void)
{
    return !k_is_in_isr();
}


uint32_t reflect_cfg_idx(uint32_t logic_addr)
{
    uint32_t idx = 0xDEADBEEF;
    const bsp_external_flash_cfg_t *p_cfg = NULL;
    for(idx = 0; idx < BEF_CTX_SIZE; idx++){
        p_cfg = &bsp_external_flash_cfg[idx];
        if((p_cfg->logic_addr_cfg & logic_addr) == (p_cfg->logic_addr_cfg)){
            break;
        }
    }
    __ASSERT_NO_MSG(idx != 0xDEADBEEF);
    return idx;
}


flash_status_t read_status_register(uint32_t cfg_idx, uint32_t command, uint8_t *sr_status)
{
    int32_t status = FLASH_NOT_INIT;
    uint8_t *cmd = &(bef_ctx[cfg_idx].cmd_buffer[0]);
    uint8_t buff[2] = {0, 0};
    uint32_t cmd_indx;
    hal_spi_master_send_and_receive_config_t spi_send_and_receive_config;
    hal_spi_master_port_t port = bsp_external_flash_cfg[cfg_idx].spi_port;

    if (bef_ctx[cfg_idx].init != FLASH_INIT) {
        return status;
    }

    cmd_indx = 0;
    cmd[cmd_indx++] = (uint8_t)command;
    spi_send_and_receive_config.receive_buffer = buff;
    spi_send_and_receive_config.send_data = cmd;
    spi_send_and_receive_config.send_length = cmd_indx;
    spi_send_and_receive_config.receive_length = spi_send_and_receive_config.send_length + 0x1;
    //should mind: status is at buffer[cmd_indx] for SPI driver
    status = hal_spi_master_send_and_receive_polling(port, &spi_send_and_receive_config);

    if (HAL_SPI_MASTER_STATUS_OK != status) {
        //log_hal_msgid_error("hal_spi_master_send_polling fail\n", 0);
        return FLASH_BUSY;
    }
    *sr_status = buff[cmd_indx];
    return status;
}

flash_status_t write_status_register(uint32_t cfg_idx, uint32_t command, uint8_t sr)
{
    int32_t status = FLASH_NOT_INIT;
    uint8_t *cmd = &(bef_ctx[cfg_idx].cmd_buffer[0]);
    uint32_t cmd_indx;
    hal_spi_master_port_t port = bsp_external_flash_cfg[cfg_idx].spi_port;

    if (bef_ctx[cfg_idx].init != FLASH_INIT) {
        return status;
    }

    cmd_indx = 0;
    cmd[cmd_indx++] = (uint8_t)command;
    cmd[cmd_indx++] = sr;
    status = hal_spi_master_send_polling(port, cmd, cmd_indx);

    if (HAL_SPI_MASTER_STATUS_OK != status) {
        //log_hal_msgid_error("hal_spi_master_send_polling fail\n", 0);
        return FLASH_BUSY;
    }
    return FLASH_STATUS_IDLE;
}

flash_status_t write_status_register_2(uint32_t cfg_idx, uint32_t command, uint8_t sr, uint8_t sr2)
{
    int32_t status = FLASH_NOT_INIT;
    uint8_t *cmd = &(bef_ctx[cfg_idx].cmd_buffer[0]);
    uint32_t cmd_indx;
    hal_spi_master_port_t port = bsp_external_flash_cfg[cfg_idx].spi_port;

    if (bef_ctx[cfg_idx].init != FLASH_INIT) {
        return status;
    }

    cmd_indx = 0;
    cmd[cmd_indx++] = (uint8_t)command;
    cmd[cmd_indx++] = sr;
    cmd[cmd_indx++] = sr2;
    status = hal_spi_master_send_polling(port, cmd, cmd_indx);

    if (HAL_SPI_MASTER_STATUS_OK != status) {
        //log_hal_msgid_error("hal_spi_master_send_polling fail\n", 0);
        return FLASH_BUSY;
    }
    return FLASH_STATUS_IDLE;
}

bsp_external_flash_status_t bsp_external_flash_get_rdid(uint32_t cfg_idx, uint8_t *buffer)
{
    int32_t status = FLASH_NOT_INIT;
    uint8_t *cmd = &(bef_ctx[cfg_idx].cmd_buffer[0]);
    hal_spi_master_send_and_receive_config_t spi_send_and_receive_config;
    uint32_t cmd_indx;
    hal_spi_master_port_t port = bsp_external_flash_cfg[cfg_idx].spi_port;

    if (wait_flash_ready(cfg_idx, 1)) {
        return EXTERNAL_FLASH_STATUS_BUSY;
    }

    cmd_indx = 0;
    cmd[cmd_indx++] = READ_RDID;
    spi_send_and_receive_config.receive_buffer = buffer;
    spi_send_and_receive_config.send_data = cmd;
    spi_send_and_receive_config.send_length = cmd_indx;
    spi_send_and_receive_config.receive_length = spi_send_and_receive_config.send_length + 0x3;

    printk("[BSP External Flash] r_buffer: 0x%08X, send_data: 0x%08X, send_len: %d, r_len: %d",
        (unsigned int)buffer,
        (unsigned int)cmd,
        (int)cmd_indx,
        (int)spi_send_and_receive_config.send_length + 0x3
    );
    status = hal_spi_master_send_and_receive_polling(port, &spi_send_and_receive_config);

    if (HAL_SPI_MASTER_STATUS_OK != status) {
        return EXTERNAL_FLASH_STATUS_ERROR;
    }

    if (FLASH_STATUS_BUSY == wait_flash_ready(cfg_idx, 1)) {
        return EXTERNAL_FLASH_STATUS_BUSY;
    }
    return EXTERNAL_FLASH_STATUS_OK;
}


bsp_external_flash_status_t spi_flash_read_polling(uint32_t cfg_idx, uint32_t address, uint8_t *buffer, uint32_t length)
{
    int32_t status = FLASH_NOT_INIT;
    uint8_t *cmd = &(bef_ctx[cfg_idx].cmd_buffer[0]);
    uint32_t cmd_indx;
    hal_spi_master_send_and_receive_config_t spi_send_and_receive_config;
    hal_spi_master_port_t port = bsp_external_flash_cfg[cfg_idx].spi_port;

    cmd_indx = 0;
    /* 1,should not use 0x03 to read as max SPI frequency is 52Mhz;
       2,should not use 0xEB as SPI doesn't support 1+4+4 mode.
       3,should use 0x0B (fast read) or 0x6B (Quad read);
       4,use polling mode if read length is less than 32-4/5 bytes
       5,can't use 0xeb for winbond flash,which is 1 + 4 + 4 */
    cmd[cmd_indx++] = bef_ctx[cfg_idx].p_dev->frd_cmd;
    if(bef_ctx[cfg_idx].p_dev->addr_mode == THREE_BYTES_ADDRESS_MODE){
        cmd[cmd_indx++] = address >> 16;  // 1: 3 byte address
        cmd[cmd_indx++] = address >> 8;   // 2: 3 byte address
        cmd[cmd_indx++] = address;        // 3: 3 byte address
    } else if (bef_ctx[cfg_idx].p_dev->addr_mode == FOUR_BYTES_ADDRESS_MODE){
        cmd[cmd_indx++] = address >> 24;  // 1: 4 byte address
        cmd[cmd_indx++] = address >> 16;  // 2: 4 byte address
        cmd[cmd_indx++] = address >> 8;   // 3: 4 byte address
        cmd[cmd_indx++] = address;        // 4: 4 byte address
    } else {
        __ASSERT_NO_MSG(0);
    }

    if (bef_ctx[cfg_idx].p_dev->frd_delay == 8) {
        //need add dummy cycle for fast read
        cmd[cmd_indx++] = 0;
    } else {
        //call hal_spi_master_set_dummy_bits to set delay bits if dummy is not byte alignement;
        //delay_bit : 0 ~ 15 bits
        hal_spi_master_set_dummy_bits(port, bef_ctx[cfg_idx].p_dev->frd_delay);
    }

    spi_send_and_receive_config.receive_buffer = buffer;
    spi_send_and_receive_config.send_data = cmd;
    spi_send_and_receive_config.send_length = cmd_indx;
    spi_send_and_receive_config.receive_length = spi_send_and_receive_config.send_length + length;

    status = hal_spi_master_send_and_receive_polling(port, &spi_send_and_receive_config);
    if (HAL_SPI_MASTER_STATUS_OK != status) {
        //log_hal_msgid_error("hal_spi_master_send_polling fail -01 status = 0x%x \r\n", 1, status);
    }

    return EXTERNAL_FLASH_STATUS_OK;
}

/*
    buffer should be 4 bytes alignment and non_cacheable
*/
bsp_external_flash_status_t spi_flash_read_dma(uint32_t cfg_idx, uint32_t address, uint8_t *buffer, uint32_t length)
{
    int32_t status = FLASH_NOT_INIT;
    uint8_t *cmd = &(bef_ctx[cfg_idx].cmd_buffer[0]);
    uint32_t cmd_indx;
    hal_spi_master_send_and_receive_config_t spi_send_and_receive_config;
    hal_spi_master_port_t port = bsp_external_flash_cfg[cfg_idx].spi_port;

    cmd_indx = 0;
    cmd[cmd_indx++] = bef_ctx[cfg_idx].p_dev->frd_cmd;
    if(bef_ctx[cfg_idx].p_dev->addr_mode == THREE_BYTES_ADDRESS_MODE){
        cmd[cmd_indx++] = address >> 16;  // 1: 3 byte address
        cmd[cmd_indx++] = address >> 8;   // 2: 3 byte address
        cmd[cmd_indx++] = address;        // 3: 3 byte address
    } else if (bef_ctx[cfg_idx].p_dev->addr_mode == FOUR_BYTES_ADDRESS_MODE){
        cmd[cmd_indx++] = address >> 24;  // 1: 4 byte address
        cmd[cmd_indx++] = address >> 16;  // 2: 4 byte address
        cmd[cmd_indx++] = address >> 8;   // 3: 4 byte address
        cmd[cmd_indx++] = address;        // 4: 4 byte address
    } else {
        __ASSERT_NO_MSG(0);
    }

    if (bef_ctx[cfg_idx].p_dev->frd_delay == 8) {
        cmd[cmd_indx++] = 0x0;
    } else {
        hal_spi_master_set_dummy_bits(port, bef_ctx[cfg_idx].p_dev->frd_delay);
    }

    spi_send_and_receive_config.receive_buffer = buffer;
    spi_send_and_receive_config.send_data = cmd;
    spi_send_and_receive_config.send_length = cmd_indx;
    spi_send_and_receive_config.receive_length = spi_send_and_receive_config.send_length + length;

    hal_spi_master_set_command_bytes(port, cmd_indx);
    status = hal_spi_master_send_and_receive_dma_blocking(port, &spi_send_and_receive_config);

    //reset to default, command is 1 byte.
    hal_spi_master_set_command_bytes(port, 1);
    //reset spi mode to single mode
    hal_spi_master_set_mode(port, HAL_SPI_MASTER_SINGLE_MODE);
    return EXTERNAL_FLASH_STATUS_OK;
}


bsp_external_flash_status_t spi_flash_write_polling(uint32_t cfg_idx, uint32_t address, uint8_t *data, int32_t length)
{
    int32_t status = FLASH_NOT_INIT;
    uint8_t *buffer = &(bef_ctx[cfg_idx].non_cache_buffer[0]);;
    uint32_t cmd_indx;
    int32_t len = length;
    hal_spi_master_port_t port = bsp_external_flash_cfg[cfg_idx].spi_port;

    //write enable
    buffer[0] = WRITE_ENABLE;
    if (HAL_SPI_MASTER_STATUS_OK != hal_spi_master_send_polling(port, buffer, 1)) {
        //log_hal_msgid_error("\r\n hal_spi_master_send_polling fail\r\n", 0);
    }

    //write with polling
    cmd_indx = 0;
    buffer[cmd_indx++] = bef_ctx[cfg_idx].p_dev->wd_cmd;
    if(bef_ctx[cfg_idx].p_dev->addr_mode == THREE_BYTES_ADDRESS_MODE){
        buffer[cmd_indx++] = address >> 16;  // 1: 3 byte address
        buffer[cmd_indx++] = address >> 8;   // 2: 3 byte address
        buffer[cmd_indx++] = address;        // 3: 3 byte address
    } else if (bef_ctx[cfg_idx].p_dev->addr_mode == FOUR_BYTES_ADDRESS_MODE){
        buffer[cmd_indx++] = address >> 24;  // 1: 4 byte address
        buffer[cmd_indx++] = address >> 16;  // 2: 4 byte address
        buffer[cmd_indx++] = address >> 8;   // 3: 4 byte address
        buffer[cmd_indx++] = address;        // 4: 4 byte address
    } else {
        __ASSERT_NO_MSG(0);
    }
    memcpy(&buffer[cmd_indx], data, len);

    //if szie is less than 32bytes, it's not neccessory to disable interrupt
    status = hal_spi_master_send_polling(port, buffer, (len + cmd_indx));

    if (wait_flash_ready(cfg_idx, 1)) {
        return EXTERNAL_FLASH_STATUS_ERROR;
    }
    return EXTERNAL_FLASH_STATUS_OK;
}


/*
    buffer should be 4 bytes alignment and non_cacheable
*/
int32_t spi_flash_write_dma(uint32_t cfg_idx, uint32_t address, uint8_t *data, int32_t length)
{
    int32_t status = FLASH_NOT_INIT;
    uint8_t *buffer = &(bef_ctx[cfg_idx].non_cache_buffer[0]);;
    uint32_t cmd_indx;
    hal_spi_master_port_t port = bsp_external_flash_cfg[cfg_idx].spi_port;

    //write enable
    buffer[0] = WRITE_ENABLE;
    if (HAL_SPI_MASTER_STATUS_OK != hal_spi_master_send_polling(port, buffer, 1)) {
        printk("[BSP External Flash] hal_spi_master_send_polling fail\r\n");
        return status;
    }

    cmd_indx = 0;
    buffer[cmd_indx++] = bef_ctx[cfg_idx].p_dev->wd_cmd;
   if(bef_ctx[cfg_idx].p_dev->addr_mode == THREE_BYTES_ADDRESS_MODE){
        buffer[cmd_indx++] = address >> 16;  // 1: 3 byte address
        buffer[cmd_indx++] = address >> 8;   // 2: 3 byte address
        buffer[cmd_indx++] = address;        // 3: 3 byte address
    } else if (bef_ctx[cfg_idx].p_dev->addr_mode == FOUR_BYTES_ADDRESS_MODE){
        buffer[cmd_indx++] = address >> 24;  // 1: 4 byte address
        buffer[cmd_indx++] = address >> 16;  // 2: 4 byte address
        buffer[cmd_indx++] = address >> 8;   // 3: 4 byte address
        buffer[cmd_indx++] = address;        // 4: 4 byte address
    } else {
        __ASSERT_NO_MSG(0);
    }

    memcpy(&buffer[cmd_indx], data, length);
    hal_spi_master_set_command_bytes(port, cmd_indx); // cmd + add
    status = hal_spi_master_send_dma_blocking(port, buffer, (length + cmd_indx));
    if (status != HAL_SPI_MASTER_STATUS_OK) {
        printk("[BSP External Flash] fail reason: %d\r\n", status);
        return status;
    }

    //should wait device ready
    wait_flash_ready(cfg_idx, 2);
    hal_spi_master_set_command_bytes(port, 1);
    return EXTERNAL_FLASH_STATUS_OK;
}


flash_status_t spi_external_flash_get_status(uint32_t cfg_idx)
{
    uint8_t sr;

    if (bef_ctx[cfg_idx].init != FLASH_INIT) {
        return FLASH_NOT_INIT;
    }

    read_status_register(cfg_idx, READ_SR, &sr);
    if ((sr & FLASH_BUSY) == FLASH_BUSY) {
        return FLASH_STATUS_BUSY;
    }
    return FLASH_STATUS_IDLE;
}


flash_status_t wait_flash_ready(uint32_t cfg_idx, uint32_t ms)
{
    uint32_t count = 0;
    int32_t status = FLASH_NOT_INIT;

    if (bef_ctx[cfg_idx].init != FLASH_INIT) {
        return status;
    }

    while (1) {
        if ((spi_external_flash_get_status(cfg_idx) & FLASH_BUSY) == FLASH_BUSY) {
            hal_gpt_delay_us(500);
            count++;
            if (count > ((ms + 1) * 1000)) {
                //log_hal_msgid_error("\r\n Flash is busy over time!!! \r\n", 0);
                return FLASH_STATUS_BUSY;
            }
        } else {
            return FLASH_STATUS_IDLE;
        }
    }
}

#endif /* BSP_EXTERNAL_SERIAL_FLASH_ENABLED */