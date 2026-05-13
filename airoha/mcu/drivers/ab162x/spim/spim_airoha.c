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

#define DT_DRV_COMPAT airoha_air_spim

#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <errno.h>
#include <zephyr/drivers/spi.h>
#include "hal_spi_master.h"
#include "air_chip.h"

#define  SPI_MASTER_INPUT_CLOCK_FREQUENCY 104000000

typedef struct{
    struct device *user_dev;
    spi_callback_t cb;
    void *userdata;
}spim_callback_info_t;

struct spim_airoha_data {
    uint32_t data;
    spim_callback_info_t spim_callback_info;
    // struct spi_context ctx;
};


struct spim_airoha_config {
    SPIM_REGISTER_T *base;
    uint32_t frequency;
    uint8_t port_num;
};

void spim_callback(hal_spi_master_callback_event_t event, void *user_data){
    spim_callback_info_t temp_spim_callback = *(spim_callback_info_t *)user_data;
    temp_spim_callback.cb(temp_spim_callback.user_dev, event, temp_spim_callback.userdata);
    const struct spim_airoha_config *dev_config =  (temp_spim_callback.user_dev)->config;
    hal_spi_master_deinit(dev_config->port_num);
}

static int spim_airoha_config(const struct device *dev,const struct spi_config *config){
    struct spim_airoha_data *dev_data = dev->data;
    const struct spim_airoha_config *dev_config = dev->config;
    hal_spi_master_config_t spi_config;
    hal_spi_master_mode_t mode;
    uint32_t frequency;
    if((config->frequency)>(SPI_MASTER_INPUT_CLOCK_FREQUENCY/2)){
        frequency = dev_data->data;
    }
    else{
        frequency = config->frequency;
    }
    spi_config.clock_frequency = frequency;
    if(SPI_MODE_GET(config->operation) & SPI_MODE_CPOL){
        spi_config.polarity = HAL_SPI_MASTER_CLOCK_POLARITY1;
    }else{
        spi_config.polarity = HAL_SPI_MASTER_CLOCK_POLARITY0;
    }
    if(SPI_MODE_GET(config->operation) & SPI_MODE_CPHA){
        spi_config.phase = HAL_SPI_MASTER_CLOCK_PHASE1;
    }else{
        spi_config.phase = HAL_SPI_MASTER_CLOCK_PHASE0;
    }
    if(((config->operation) & SPI_TRANSFER_LSB) & SPI_TRANSFER_LSB){
        spi_config.bit_order = HAL_SPI_MASTER_LSB_FIRST;
    }else{
        spi_config.bit_order = HAL_SPI_MASTER_MSB_FIRST;
    }
    if(((config->operation) & SPI_LINES_MASK) & SPI_LINES_SINGLE){
        mode = HAL_SPI_MASTER_SINGLE_MODE;
    }else if(((config->operation) & SPI_LINES_MASK)  & SPI_LINES_DUAL){
        mode = HAL_SPI_MASTER_DUAL_MODE;

    }else if(((config->operation) & SPI_LINES_MASK)  & SPI_LINES_QUAD){
        mode = HAL_SPI_MASTER_QUAD_MODE;
    }else if(((config->operation) & SPI_LINES_MASK)  & SPI_LINES_OCTAL){
        printk("\r\n %d not support  SPI_LINES_OCTAL MODE\r\n",dev_config->port_num);
        return -EIO;
    }
    else{
        mode = HAL_SPI_MASTER_SINGLE_MODE;
    }

    if(config->slave == 0){
        spi_config.slave_port = HAL_SPI_MASTER_SLAVE_0;
    }else if(config->slave == 1){
        spi_config.slave_port = HAL_SPI_MASTER_SLAVE_1;
    }else if(config->slave == 2){
        spi_config.slave_port = HAL_SPI_MASTER_SLAVE_2;
    }else if(config->slave == 3){
        spi_config.slave_port = HAL_SPI_MASTER_SLAVE_3;
    }else{
        spi_config.slave_port = HAL_SPI_MASTER_SLAVE_0;
    }
    hal_spi_master_init(dev_config->port_num,&spi_config);
    hal_spi_master_set_mode (dev_config->port_num,mode);
    return 0;
}


static int spim_airoha_transceive_cb_ex(const struct device *dev,
                const struct spi_config *config,
                const struct spi_buf_set *tx_bufs,
                const struct spi_buf_set *rx_bufs,
                spi_callback_t cb,
                void *userdata)
{
    struct spim_airoha_data *dev_data = dev->data;
    const struct spim_airoha_config *dev_config = dev->config;
    hal_spi_master_send_and_receive_config_t spi_send_and_receive_config;
    spim_airoha_config(dev,config);
    size_t tx_count = 0;
    size_t rx_count = 0;
    const struct spi_buf *tx = NULL;
    const struct spi_buf *rx = NULL;

    if (tx_bufs) {
        tx = tx_bufs->buffers;
        tx_count = tx_bufs->count;
    }
    if (rx_bufs) {
        rx = rx_bufs->buffers;
        rx_count = rx_bufs->count;
    }
    size_t max_count =  (tx_count > rx_count) ? tx_count : rx_count;
    if(cb != NULL){
        max_count = max_count - 1;
        const struct spim_airoha_config *dev_config = dev->config;
        dev_data->spim_callback_info.user_dev = (struct device *)dev;
        dev_data->spim_callback_info.cb = cb;
        dev_data->spim_callback_info.userdata = userdata;
        hal_spi_master_register_callback(dev_config->port_num,spim_callback, &(dev_data->spim_callback_info));
    }
    for (uint8_t i=0; i< max_count; i++) {
        if(rx_count){
            if(tx_count != 0){
                spi_send_and_receive_config.send_length = tx->len;
                spi_send_and_receive_config.send_data = tx->buf;
                tx_count--;
                tx++;
            }else{
                spi_send_and_receive_config.send_length = 0;
                spi_send_and_receive_config.send_data = NULL;
            }
            spi_send_and_receive_config.receive_length =rx->len;
            spi_send_and_receive_config.receive_buffer = rx->buf;
            rx_count--;
            rx++;
            hal_spi_master_send_and_receive_dma_blocking(dev_config->port_num, &spi_send_and_receive_config);
        }
        else if(tx_count){
            hal_spi_master_send_dma_blocking(dev_config->port_num,tx->buf,tx->len);
            tx_count--;
            tx++;
        }
    }
    if(cb != NULL){
        if(rx_count){
            if(tx_count != 0){
                spi_send_and_receive_config.send_length = tx->len;
                spi_send_and_receive_config.send_data = tx->buf;
                tx_count--;
                tx++;
            }else{
                spi_send_and_receive_config.send_length = 0;
                spi_send_and_receive_config.send_data = NULL;
            }
            spi_send_and_receive_config.receive_length =rx->len;
            spi_send_and_receive_config.receive_buffer = rx->buf;
            rx_count--;
            rx++;
            hal_spi_master_send_and_receive_dma(dev_config->port_num, &spi_send_and_receive_config);
        }
        else if(tx_count){
            hal_spi_master_send_dma(dev_config->port_num,tx->buf,tx->len);
            tx_count--;
            tx++;
        }
    }else{
        hal_spi_master_deinit(dev_config->port_num);
    }
    return 0;
}

static int spim_airoha_transceive(const struct device *dev,
                const struct spi_config *config,
                const struct spi_buf_set *tx_bufs,
                const struct spi_buf_set *rx_bufs){

    return spim_airoha_transceive_cb_ex(dev,config,tx_bufs,rx_bufs,NULL,NULL);

}



#ifdef CONFIG_SPI_ASYNC
static int    spim_airoha_transceive_async(const struct device *dev,
                                        const struct spi_config *config,
                                        const struct spi_buf_set *tx_bufs,
                                        const struct spi_buf_set *rx_bufs,
                                        spi_callback_t cb,
                                        void *userdata)
{
    return spim_airoha_transceive_cb_ex(dev,config,tx_bufs,rx_bufs,cb,userdata);
}
#endif /* CONFIG_SPI_ASYNC */

static int spim_airoha_transceive_release(const struct device *dev,
                 const struct spi_config *config)
{

    return 0;
    // struct spim_airoha_data *dev_data = dev->data;

    // spi_context_unlock_unconditionally(&dev_data->ctx);
}

static int spim_init(const struct device *dev)
{

    const struct spim_airoha_config *dev_config = dev->config;
    if((dev_config->frequency) >  (SPI_MASTER_INPUT_CLOCK_FREQUENCY/2)){
        return -EIO;
    }
    return 0;
}

static const struct spi_driver_api spim_airoha_driver_api = {
    .transceive = spim_airoha_transceive,
#ifdef CONFIG_SPI_ASYNC
    .transceive_async = spim_airoha_transceive_async,
#endif /* CONFIG_SPI_ASYNC */
    .release = spim_airoha_transceive_release,
};



#define    SPIM_AIROHA_DEVICE(id)                        \
                                    \
static struct spim_airoha_data spim_airoha_p##id##_data;        \
                                    \
static const struct spim_airoha_config spim_airoha_p##id##_config = {        \
    .base = (SPIM_REGISTER_T *)DT_INST_REG_ADDR(id),   \
    .frequency = DT_INST_PROP(id, frequency),        \
    .port_num = DT_INST_PROP(id, port),        \
};                                    \
                                    \
DEVICE_DT_INST_DEFINE(id,                        \
        spim_init,                        \
        NULL,                            \
        &spim_airoha_p##id##_data,                    \
        &spim_airoha_p##id##_config,                     \
        CONFIG_SPIM_INIT_LEVEL, CONFIG_SPIM_INIT_PRIORITY, &spim_airoha_driver_api);

DT_INST_FOREACH_STATUS_OKAY(SPIM_AIROHA_DEVICE)
