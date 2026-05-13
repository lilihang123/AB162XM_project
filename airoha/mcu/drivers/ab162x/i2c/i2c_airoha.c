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
/*
 * SPDX-License-Identifier: Apache-2.0
 */
#define DT_DRV_COMPAT airoha_air_i2c

#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <zephyr/drivers/i2c.h>
#include "hal_i2c_master.h"
#include "hal_gpt.h"
#include <zephyr/logging/log.h>
#include "air_chip.h"

typedef struct{
    struct device *user_dev;
    i2c_callback_t cb;
    void *userdata;
}i2c_callback_info_t;

struct i2c_airoha_data {
        uint32_t data;
        uint32_t dma_count;
        uint32_t config;
        i2c_callback_info_t i2c_callback_info;
};

struct i2c_airoha_config {
        uint32_t frequency;
        uint8_t port_num;
};

void i2c_callback(uint8_t slave_address, hal_i2c_callback_event_t event, void *user_data){
    i2c_callback_info_t temp_i2c_callback = *(i2c_callback_info_t *)user_data;
    temp_i2c_callback.cb(temp_i2c_callback.user_dev, event, temp_i2c_callback.userdata);
    struct i2c_airoha_data *dev_data =  (temp_i2c_callback.user_dev)->data;
    const struct i2c_airoha_config *dev_config =  (temp_i2c_callback.user_dev)->config;
    dev_data->dma_count-- ;
    if(dev_data->dma_count == 0){
        hal_i2c_master_deinit(dev_config->port_num);
    }
}

uint8_t *write_buffer= NULL;
uint8_t write_length = 0;
uint8_t *receive_buffer = NULL;
uint8_t receive_length=0;

static int i2c_airoha_transfer_set(const struct device *dev,
                                  struct i2c_msg *msgs,
                                  uint8_t num_msgs, uint16_t addr,bool dma){

        struct i2c_airoha_data *dev_data = dev->data;
        const struct i2c_airoha_config *dev_config = dev->config;
        hal_i2c_config_t  config;
        hal_i2c_status_t init = 0;
        hal_i2c_status_t tranfer = 0;
        uint32_t frequency;
        frequency = dev_data->data;
        switch(frequency){
        case 50000:
            config.frequency = HAL_I2C_FREQUENCY_50K;
            break;
        case 100000:
            config.frequency = HAL_I2C_FREQUENCY_100K;
            break;
        case 200000:
            config.frequency = HAL_I2C_FREQUENCY_200K;
            break;
        case 300000:
            config.frequency = HAL_I2C_FREQUENCY_300K;
            break;
        case 400000:
            config.frequency = HAL_I2C_FREQUENCY_400K;
            break;
        case 1000000:
            config.frequency = HAL_I2C_FREQUENCY_1M;
            break;
        case 2000000:
            config.frequency = HAL_I2C_FREQUENCY_2M;
            break;
        case 2500000:
            config.frequency = HAL_I2C_FREQUENCY_2M5;
            break;
        case 2800000:
            config.frequency = HAL_I2C_FREQUENCY_2M8;
            break;
        case 3400000:
            config.frequency = HAL_I2C_FREQUENCY_3M;
            break;
        default:
            config.frequency = HAL_I2C_FREQUENCY_400K;
                break;
        }
        init =  hal_i2c_master_init(dev_config->port_num, &config);
        if((init == HAL_I2C_STATUS_OK)||(init == HAL_I2C_STATUS_ERROR)){
            int i = 0;
            for(i = 0;i<num_msgs;i++){
                if((msgs[i].flags & (I2C_MSG_RW_MASK)) ==  I2C_MSG_WRITE){
                    if((msgs[i].flags & (I2C_MSG_STOP)) == I2C_MSG_STOP){
                            uint8_t *new_write_buffer  = k_realloc(write_buffer,write_length+msgs[i].len);
                            if(new_write_buffer == NULL){
                                if(write_buffer != NULL)k_free(write_buffer);
                            }
                            write_buffer = new_write_buffer;
                            memcpy(write_buffer+write_length,msgs[i].buf,msgs[i].len);
                            write_length += msgs[i].len;
                            hal_i2c_send_to_receive_config_t i2c_send_to_receive_config;
                            i2c_send_to_receive_config.slave_address = addr;
                            i2c_send_to_receive_config.send_data = write_buffer;
                            i2c_send_to_receive_config.send_length = write_length;
                            i2c_send_to_receive_config.receive_buffer =receive_buffer;
                            i2c_send_to_receive_config.receive_length = receive_length;
                            if(dma){
                                tranfer = hal_i2c_master_send_to_receive_dma(dev_config->port_num,&i2c_send_to_receive_config);
                            }else{
                                tranfer = hal_i2c_master_send_to_receive_polling(dev_config->port_num,&i2c_send_to_receive_config);
                            }
                            if(write_buffer != NULL)k_free(write_buffer);
                            if(receive_buffer != NULL)k_free(receive_buffer);
                            write_buffer = NULL;
                            receive_buffer = NULL;
                            write_length = 0;
                            receive_length = 0;
                    }else{
                        uint8_t *new_write_buffer = k_realloc(write_buffer,write_length+msgs[i].len);
                        if(new_write_buffer == NULL){
                            if(write_buffer != NULL)k_free(write_buffer);
                        }
                        write_buffer = new_write_buffer;
                        memcpy(write_buffer+write_length,msgs[i].buf,msgs[i].len);
                        write_length += msgs[i].len;
                    }
                }
                if((msgs[i].flags & (I2C_MSG_RW_MASK)) == I2C_MSG_READ){
                    if((msgs[i].flags & (I2C_MSG_STOP)) == I2C_MSG_STOP){
                        uint8_t *new_receive_buffer = k_realloc(receive_buffer,receive_length+msgs[i].len);
                        if(new_receive_buffer == NULL){
                            if(receive_buffer != NULL)k_free(receive_buffer);
                        }
                        receive_buffer = new_receive_buffer;
                        receive_length += msgs[i].len;
                        hal_i2c_send_to_receive_config_t i2c_send_to_receive_config;
                        i2c_send_to_receive_config.slave_address = addr;
                        i2c_send_to_receive_config.send_data = write_buffer;
                        i2c_send_to_receive_config.send_length = write_length;
                        i2c_send_to_receive_config.receive_buffer =receive_buffer;
                        i2c_send_to_receive_config.receive_length = receive_length;
                        if(dma){
                            tranfer = hal_i2c_master_send_to_receive_dma(dev_config->port_num,&i2c_send_to_receive_config);
                        }else{
                            tranfer = hal_i2c_master_send_to_receive_polling(dev_config->port_num,&i2c_send_to_receive_config);
                        }
                        memcpy(msgs[i].buf,receive_buffer+receive_length-msgs[i].len,msgs[i].len);
                        if(write_buffer != NULL)k_free(write_buffer);
                        if(receive_buffer != NULL)k_free(receive_buffer);
                        write_buffer = NULL;
                        receive_buffer = NULL;
                        write_length = 0;
                        receive_length = 0;
                    }else{
                        uint8_t *new_receive_buffer = k_realloc(receive_buffer,receive_length+msgs[i].len);
                        if(new_receive_buffer == NULL){
                            k_free(receive_buffer);
                        }
                        receive_buffer = new_receive_buffer;
                        receive_length += msgs[i].len;
                    }
                }
            }
        }else{
            return -EINVAL;
        }
        return tranfer;
}

static int i2c_airoha_transfer(const struct device *dev,
                                  struct i2c_msg *msgs,
                                  uint8_t num_msgs, uint16_t addr)
{
    int ret = i2c_airoha_transfer_set(dev,msgs, num_msgs,addr,false);
    const struct i2c_airoha_config *dev_config = dev->config;
    if(ret == 0){
        return hal_i2c_master_deinit(dev_config->port_num);
    }else{
        return ret;
    }
}

#ifdef CONFIG_I2C_CALLBACK
static int i2c_airoha_transfer_cb (const struct device *dev,
                 struct i2c_msg *msgs,
                 uint8_t num_msgs,
                 uint16_t addr,
                 i2c_callback_t cb,
                 void *userdata){
    const struct i2c_airoha_config *dev_config = dev->config;
    struct i2c_airoha_data *dev_data = dev->data;
    dev_data->i2c_callback_info.user_dev = (struct device *)dev;
    dev_data->i2c_callback_info.cb = cb;
    dev_data->i2c_callback_info.userdata = userdata;
    hal_i2c_master_register_callback(dev_config->port_num,i2c_callback, &(dev_data->i2c_callback_info));
    int ret = i2c_airoha_transfer_set(dev,msgs, num_msgs,addr,true);
    if(ret == 0)dev_data->dma_count++;
    return ret;
}
#endif

static int i2c_airoha_configure(const struct device *dev,
                   uint32_t i2c_config)
{
    const struct i2c_airoha_config *dev_config = dev->config;
    struct i2c_airoha_data *dev_data = dev->data;
    uint32_t frequency;
    if (I2C_ADDR_10_BITS & i2c_config) {
        return -EINVAL;
    }
    switch (I2C_SPEED_GET(i2c_config)) {
    case I2C_SPEED_STANDARD:
        frequency = 100000;
        break;
    case I2C_SPEED_FAST:
        frequency = 400000;
        break;
    case I2C_SPEED_FAST_PLUS:
        frequency = 1000000;
        break;
    case I2C_SPEED_HIGH:
        frequency = 3400000;
        break;
    default:
        return -EINVAL;
    }
    if (frequency != dev_config->frequency) {
        dev_data->data =frequency;
        hal_i2c_master_deinit(dev_config->port_num);
        hal_i2c_config_t config;
        switch(frequency){
        case 50000:
            config.frequency = HAL_I2C_FREQUENCY_50K;
            break;
        case 100000:
            config.frequency = HAL_I2C_FREQUENCY_100K;
            break;
        case 200000:
            config.frequency = HAL_I2C_FREQUENCY_200K;
            break;
        case 300000:
            config.frequency = HAL_I2C_FREQUENCY_300K;
            break;
        case 400000:
            config.frequency = HAL_I2C_FREQUENCY_400K;
            break;
        case 1000000:
            config.frequency = HAL_I2C_FREQUENCY_1M;
            break;
        case 2000000:
            config.frequency = HAL_I2C_FREQUENCY_2M;
            break;
        case 2500000:
            config.frequency = HAL_I2C_FREQUENCY_2M5;
            break;
        case 2800000:
            config.frequency = HAL_I2C_FREQUENCY_2M8;
            break;
        case 3400000:
            config.frequency = HAL_I2C_FREQUENCY_3M;
            break;
        default:
            config.frequency = HAL_I2C_FREQUENCY_400K;
            break;

        }
        hal_i2c_master_init(dev_config->port_num, &config);
        dev_data->config = i2c_config;
        return 0;
    }
    return 0;
}
static int i2c_airoha_get_config(const struct device *dev,
                   uint32_t *dev_config){

    struct i2c_airoha_data *dev_data = dev->data;
    *dev_config = dev_data->config;
    return 0;
}
static int i2c_airoha_recover_bus(const struct device *dev)
{
    return 0;
}

static int i2c_init(const struct device *dev)
{
    const struct i2c_airoha_config *dev_config = dev->config;
    if((dev_config->frequency) >  3400000){
        return -EIO;
    }
    return 0;
}

static const struct i2c_driver_api i2c_airoha_driver_api = {
    .configure   = i2c_airoha_configure,
    .get_config  = i2c_airoha_get_config,
    .transfer    = i2c_airoha_transfer,
    .recover_bus = i2c_airoha_recover_bus,
#ifdef CONFIG_I2C_CALLBACK
    .transfer_cb = i2c_airoha_transfer_cb,
#endif
};



#define    I2C_AIROHA_DEVICE(id)                        \
                                    \
static struct i2c_airoha_data i2c_airoha_p##id##_data;        \
                                    \
static const struct i2c_airoha_config i2c_airoha_p##id##_config = {        \
    .frequency = DT_INST_PROP(id, frequency),        \
    .port_num = DT_INST_PROP(id, port),        \
};                                    \
                                    \
DEVICE_DT_INST_DEFINE(id,                        \
        i2c_init,                        \
        NULL,                            \
        &i2c_airoha_p##id##_data,                    \
        &i2c_airoha_p##id##_config,                     \
        CONFIG_I2C_INIT_LEVEL, CONFIG_I2C_INIT_PRIORITY, &i2c_airoha_driver_api);

DT_INST_FOREACH_STATUS_OKAY(I2C_AIROHA_DEVICE)
