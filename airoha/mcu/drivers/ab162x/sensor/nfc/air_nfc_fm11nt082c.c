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

#include "air_nfc_fm11nt082c.h"

//#define NFC_I2C_DMA_ENABLED

#ifdef NFC_I2C_DMA_ENABLED
#define FM11_BLOCK_SIZE       16
#else
#define FM11_BLOCK_SIZE       4
#endif
#define FM11_PAGE_SEQ_NUM     0x0000
#define FM11_PAGE_USER_CFG    0x0390
#define FM11_PAGE_USER_DATA   0x0010

#define log_nfc_info(_message, cnt, ...)    log_hal_msgid_info("[sensor][nfc] " _message,cnt,    ##__VA_ARGS__)
#define log_nfc_warn(_message, cnt, ...)    log_hal_msgid_warning("[sensor][nfc] " _message,cnt, ##__VA_ARGS__)
#define log_nfc_error(_message,cnt, ...)    log_hal_msgid_error("[sensor][nfc] " _message,cnt,   ##__VA_ARGS__)


static uint8_t s_i2cm_port    = 0;
static uint8_t s_i2cm_devaddr = 0x57;
static uint8_t s_i2c_frequency = 0;
static uint8_t s_eint_num = 0;
static nfc_user_callback_t s_eint_callback = NULL;
static void *s_user_data = NULL;
static uint32_t s_init_tick = 0;


static int air_i2cm_init()
{
#ifndef NFC_I2C_DMA_ENABLED
    hal_i2c_config_t config;

    config.frequency = s_i2c_frequency;
    hal_i2c_master_init(s_i2cm_port, &config);
#endif
    return 0;
}

#ifdef NFC_I2C_DMA_ENABLED
ATTR_RWDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN static uint8_t s_rx_dma_buff[32]={0};
ATTR_RWDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN static uint8_t s_tx_dma_buff[32]={0};

void  nfc_i2cm_callback(uint8_t slave_address, hal_i2c_callback_event_t event, void *user_data)
{

}

static int air_i2cm_dma_transfer_data(uint8_t *tx_buff, uint32_t tx_len, uint8_t *rx_buff, uint32_t rx_len)
{
    hal_i2c_send_to_receive_config_ex_no_busy_t  i2cm_config;
    hal_i2c_status_t status = 0;
    hal_i2c_running_status_t running_status;

    memcpy(s_tx_dma_buff, tx_buff, tx_len);
    i2cm_config.i2c_callback = nfc_i2cm_callback;
    i2cm_config.user_data = NULL;
    i2cm_config.i2c_config.frequency = s_i2c_frequency;
    i2cm_config.i2c_send_to_receive_config_ex.slave_address = s_i2cm_devaddr;
    i2cm_config.i2c_send_to_receive_config_ex.receive_buffer = s_rx_dma_buff;
    i2cm_config.i2c_send_to_receive_config_ex.send_data = s_tx_dma_buff;
    i2cm_config.i2c_send_to_receive_config_ex.receive_bytes_in_one_packet = rx_len;
    i2cm_config.i2c_send_to_receive_config_ex.send_bytes_in_one_packet = tx_len;
    i2cm_config.i2c_send_to_receive_config_ex.receive_packet_length = 1;
    i2cm_config.i2c_send_to_receive_config_ex.send_packet_length = 1;

    status = hal_i2c_master_send_to_receive_dma_ex_none_blocking(s_i2cm_port, &i2cm_config);
    if (status != HAL_I2C_STATUS_OK) {
        log_nfc_error("air_i2cm_dma_transfer_data: error %d", 1, status);
        return status;
    }

    while(1) {
        hal_i2c_master_get_running_status(s_i2cm_port, &running_status);
        if(running_status.running_status == HAL_I2C_STATUS_IDLE) {
            break;
        }
    }
    if (rx_len != 0) {
        memcpy(rx_buff, s_rx_dma_buff, rx_len);
    }
    return 0;
}
#endif


static int air_i2cm_send_data(uint16_t page_addr, uint8_t *tx_buff, uint16_t tx_len)
{
    hal_i2c_status_t status;
    uint8_t temp_buff[32];

    if (tx_buff == NULL || tx_len > FM11_BLOCK_SIZE) {
        return HAL_I2C_STATUS_INVALID_PARAMETER;
    }
    temp_buff[0] = (page_addr >> 8) & 0xFF;
    temp_buff[1] = page_addr & 0xFF;
    memcpy(&temp_buff[2], tx_buff, tx_len);

#ifdef NFC_I2C_DMA_ENABLED
    status = air_i2cm_dma_transfer_data(temp_buff, tx_len + 2, NULL, 0);
    if(status != HAL_I2C_STATUS_OK) {
        log_nfc_error("air_i2cm_send_data, dma error %d", 1, status);
        return status;
    }
#else
    status = hal_i2c_master_send_polling(s_i2cm_port, s_i2cm_devaddr, temp_buff, tx_len + 2);
    if(status != HAL_I2C_STATUS_OK) {
        log_nfc_error("air_i2cm_send_data, polling error %d", 1, status);
        return status;
    }
#endif
    return tx_len;
}

static int air_i2cm_recv_data(uint16_t page_addr, uint8_t *rx_buff, uint16_t rx_len)
{
    hal_i2c_status_t status;
    uint8_t tmp_buff[4];

    if (rx_buff == NULL || rx_len > FM11_BLOCK_SIZE) {
        return HAL_I2C_STATUS_INVALID_PARAMETER;
    }
    tmp_buff[0] = (page_addr >> 8) & 0xFF;
    tmp_buff[1] = page_addr & 0xFF;
#ifdef NFC_I2C_DMA_ENABLED
    status = air_i2cm_dma_transfer_data(tmp_buff, 2, rx_buff, rx_len);
    if(status != HAL_I2C_STATUS_OK) {
        log_nfc_error("air_i2cm_recv_data, dma error %d", 1, status);
        return status;
    }
#else
    hal_i2c_send_to_receive_config_t config;

    config.receive_length = rx_len;
    config.send_length = 2;
    config.receive_buffer = rx_buff;
    config.send_data = tmp_buff;
    config.slave_address = s_i2cm_devaddr;

    status = hal_i2c_master_send_to_receive_polling(s_i2cm_port, &config);
    if(status != HAL_I2C_STATUS_OK) {
        log_nfc_error("air_i2cm_recv_data, polling error %d", 1, status);
        return status;
    }
#endif
    return rx_len;
}

static void air_eint_callback(void *user_data)
{
    log_nfc_info("fm11 eint irq triggered!!", 0);
    s_eint_callback(s_user_data);
    hal_eint_unmask(s_eint_num);
}


int  fm11_init(fm11_init_config_t  *config)
{
    uint8_t tag_cfg_buff[4] = {0x98, 0x80, 0x01};
    uint8_t buff[4];
    int res = 0;

#ifndef NFC_I2C_DMA_ENABLED
    printk("------------fm11_init: i2c polling mode");
#else
    printk("------------fm11_init: i2c DMA mode");
#endif

    /* platform init*/
    if (config->callback != NULL) {
        hal_eint_config_t eint_config;

        s_eint_callback = config->callback;
        s_user_data     = config->user_data;
        s_eint_num = config->eint_num; 
        eint_config.trigger_mode = config->eint_mode;
        eint_config.debounce_time = 0;
        hal_eint_init(config->eint_num, &eint_config);
        hal_eint_register_callback(config->eint_num, air_eint_callback, NULL);
        hal_eint_unmask(config->eint_num);
    }
    s_i2cm_port = config->i2c_port;
    s_i2c_frequency = config->i2c_frequency;
    air_i2cm_init();

    /* detect FM11 device */
    res = air_i2cm_recv_data(0x0000, buff, 4);
    if (res < 0) {
        log_nfc_error("fm11_init, bus err 1:%x", 1, res);
        return res;
    }
    if (buff[0] == 0x1D) {
        log_nfc_info("fm11_init, detect dev succ", 0);
    } else {
        log_nfc_error("fm11_init, detect dev fail:%x", 1, buff[0]);
        return -1;
    }

    /* configure FM11NT082C */
    tag_cfg_buff[3] = ~(tag_cfg_buff[0] ^ tag_cfg_buff[1] ^ tag_cfg_buff[2]);
    res = air_i2cm_send_data(FM11_PAGE_USER_CFG, tag_cfg_buff, 4);
    if (res < 0) {
        log_nfc_error("fm11_init, bus err 2:%x", 1, res);
        return res;
    }
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &s_init_tick);
    return 0;
}

int  fm11_deinit()
{
    return 0;
}

int fm11_write_user_data(uint8_t *tx_buff, uint16_t tx_len)
{
    uint16_t page_addr;
    uint32_t loop_cnt, remain_cnt, cur_tick = 0, dur_tick;
    int i = 0, res = 0, offset = 0;

    log_nfc_error("fm11_write_user_data, write %d byte to nfc", 1, tx_len);
    if(tx_buff == NULL || tx_len >= 888) {
        return -1;
    }

    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &cur_tick);
    hal_gpt_get_duration_count(s_init_tick, cur_tick, &dur_tick);
    if(dur_tick < 300){
        hal_gpt_delay_ms(10);
    }
    loop_cnt = tx_len / FM11_BLOCK_SIZE;
    remain_cnt = tx_len % FM11_BLOCK_SIZE;
    page_addr = FM11_PAGE_USER_DATA;
    for (i = 0; i < loop_cnt; i++) {
        offset = i * FM11_BLOCK_SIZE;
        res = air_i2cm_send_data(page_addr, &tx_buff[offset], FM11_BLOCK_SIZE);
        if (res < 0) {
            log_nfc_error("fm11_write_user_data, bus err 1:%x", 1, res);
            return res;
        }
        page_addr += FM11_BLOCK_SIZE;

        hal_gpt_delay_ms(5);
        //k_sleep(K_MSEC(5));
    }
    offset += FM11_BLOCK_SIZE;
    if (remain_cnt) {
        res = air_i2cm_send_data(page_addr, &tx_buff[offset], 4);
        if (res < 0) {
            log_nfc_error("fm11_write_user_data, bus err 2:%x", 1, res);
            return res;
        }
    }
    return tx_len;
}