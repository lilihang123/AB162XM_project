
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
#define DT_DRV_COMPAT pixart_paw3395

#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pinctrl_soc.h>
#include "hal_spi_master.h"
#include "hal_gpt.h"
#include "hal_nvic.h"
#include "air_chip.h"
#include "hal_gpio.h"
#include "mouse_sensor.h"
#include "memory_attribute.h"

#include "hal_spi_sensor.h"
#include "hal_cross_core_config.h"


#if 0
#define log_mouse_sensor_info(fmt, cnt, ...)     log_hal_msgid_info("[hal][rtc] " fmt, cnt, ##__VA_ARGS__)
#define log_mouse_sensor_warning(fmt, cnt, ...)  log_hal_msgid_warning("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#define log_mouse_sensor_error(fmt, cnt, ...)    log_hal_msgid_error("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#else
#define log_mouse_sensor_info(fmt, cnt, ...)     printk(fmt, ##__VA_ARGS__)
#define log_mouse_sensor_warning(fmt, cnt, ...)  printk(fmt, ##__VA_ARGS__)
#define log_mouse_sensor_error(fmt, cnt, ...)    printk(fmt, ##__VA_ARGS__)
#endif

static mouse_burst_data_t * mouse_burst_data = (mouse_burst_data_t *)CROSS_CORE_MEM_VARIABLE(spi_sensor);
static int mouse_sensor_set_bt_trig(const struct device *dev,bool bt_trig);

struct mouse_sensor_data{
    uint8_t  xy_direction;
    uint8_t  lod;
    uint8_t  mode;
    bool     rest_mode;
    bool     motion_sync;
    bool     angle_snap;
    bool     ripple_control;
    uint16_t cpi;
    uint16_t cpi_x;
    uint16_t cpi_y;
    uint16_t rest1_period_time;
    uint16_t rest2_period_time;
    uint16_t rest3_period_time;
    uint32_t run_downshift_time;
    uint32_t rest1_downshift_time;
    uint32_t rest2_downshift_time;
    uint8_t setting_flag;
    bool    delay_config;
    bool    bt_trigger;
    bool    force;
    bool    reinit;
};

struct mouse_sensor_config {
    uint32_t frequency;
    uint16_t cs_pin;
    uint8_t port_num;
    uint8_t xy_direction;
    uint8_t lod;
    uint16_t cpi;
    uint8_t mode;
    bool     rest_mode;
    bool     motion_sync;
    bool     angle_snap;
    bool     ripple_control;
    uint16_t rest1_period_time;
    uint16_t rest2_period_time;
    uint16_t rest3_period_time;
};

#define    MOUSE_SENSOR_Product_ID                   0x00
#define    MOUSE_SENSOR_Revision_ID                  0x01
#define    MOUSE_SENSOR_Motion                       0x02
#define    MOUSE_SENSOR_Delta_X_L                    0x03
#define    MOUSE_SENSOR_Delta_X_H                    0x04
#define    MOUSE_SENSOR_Delta_Y_L                    0x05
#define    MOUSE_SENSOR_Delta_Y_H                    0x06
#define    MOUSE_SENSOR_SQUAL                        0x07
#define    MOUSE_SENSOR_Raw_Data_Sum                 0x08
#define    MOUSE_SENSOR_Maximum_Raw_data             0x09
#define    MOUSE_SENSOR_Minimum_Raw_data             0x0A
#define    MOUSE_SENSOR_Shutter_Lower                0x0B
#define    MOUSE_SENSOR_Shutter_Upper                0x0C
#define    MOUSE_SENSOR_Chip_Observation             0x15
#define    MOUSE_SENSOR_Burst_Motion_Read            0x16
#define    MOUSE_SENSOR_Power_Up_Reset               0x3A
#define    MOUSE_SENSOR_Shutdown                     0x3B
#define    MOUSE_SENSOR_Performance                  0x40
#define    MOUSE_SENSOR_Resolution                   0x47
#define    MOUSE_SENSOR_Resolution_X_Low             0x48
#define    MOUSE_SENSOR_Resolution_X_High            0x49
#define    MOUSE_SENSOR_Resolution_Y_Low             0x4A
#define    MOUSE_SENSOR_Resolution_Y_High            0x4B
#define    MOUSE_SENSOR_Angle_Snap                   0x56
#define    MOUSE_SENSOR_Raw_Data_Grab                0x58
#define    MOUSE_SENSOR_Raw_Data_Grab_Status         0x59
#define    MOUSE_SENSOR_Ripple_Control               0x5A
#define    MOUSE_SENSOR_Axis_Control                 0x5B
#define    MOUSE_SENSOR_Motion_Ctrl                  0x5C
#define    MOUSE_SENSOR_Inv_Product_ID               0x5F
#define    MOUSE_SENSOR_Run_DownShift                0x77
#define    MOUSE_SENSOR_Rest1_Period                 0x78
#define    MOUSE_SENSOR_Rest1_DownShift              0x79
#define    MOUSE_SENSOR_Rest2_Period                 0x7A
#define    MOUSE_SENSOR_Rest2_DownShift              0x7B
#define    MOUSE_SENSOR_Rest3_Period                 0x7C
#define    MOUSE_SENSOR_Run_DownShift_Mult           0x7D
#define    MOUSE_SENSOR_Rest_DownShift_Mult          0x7E

#define MAX_BURST_SIZE  12

ATTR_ALIGN(16) uint8_t burst_reg = MOUSE_SENSOR_Burst_Motion_Read;
uint32_t global_init_left_time;
const uint8_t download_data[] = { 0x07,0x41,0x00,0x80,0x0E,0x0D,0x1B,0xE8,0xD5,0x14,0xBC,0x74,0x20,0x00,0x0E,0x05,0x04,0x06,0x40,0x40,0xCA,0xE8,0xEA,0x31,0x64,0xB8,0x0F,0x02,0x2A,0x26,0x06,0x70,0x60,0x04,0x02,0x11,0x01,
                                  0x51,0x07,0x10,0x32,0x00,0x08,0x4F,0x09,0x1F,0x1F,0x03,0x03,0x1F,0x1F,0x03,0x03,0x1F,0x1F,0x04,0x20,0x20,0x0C,0x07,0x07,0x0A,0x14,0x14,0x19,0x14,0x30,0x03,0x0B,0x0A,0x02,0x15,0x02,0x02,
                                  0x91,0x0A,0x0C,0x10,0x0C,0x40,0x25,0x18,0x14,0x0A,0x00,0x2D,0x0C,0x1A,0x0D,0x1E,0x05,0x0F,0x0D,0xDD,0x03,0x49,0x00,0x5B,0x00,0x64,0x00,0xA5,0x02,0x29,0x47,0x81,0x40,0xDC,0x07,0x00,0x08,
                                  0xDC,0x07,0x00,0x08,0x10,0xD0,0x00,0x63,0x00,0x63,0x00,0x54,0x10,0x4F,0x01,0x40,0x60,0x06,0x13,0x0F,0x01,0x9C,0x00,0x02,0x70,0x01};

const uint8_t download_reg[]  = { 0x7F,0x40,0x7F,0x40,0x7F,0x55,0x56,0x57,0x58,0x7F,0x42,0x43,0x4B,0x4D,0x53,0x7F,0x44,0x4D,0x51,0x53,0x55,0x5A,0x5B,0x61,0x62,0x6D,0x6E,0x70,0x4A,0x60,0x7F,0x6D,0x6E,0x6F,0x53,0x55,0x7A,
                                  0x7D,0x7F,0x41,0x42,0x43,0x7F,0x71,0x7F,0x62,0x63,0x65,0x66,0x67,0x68,0x69,0x6A,0x6C,0x6D,0x51,0x53,0x54,0x71,0x72,0x73,0x7F,0x4A,0x4C,0x55,0x7F,0x4B,0x4C,0x61,0x62,0x63,0x7F,0x4C,0x56,
                                  0x41,0x4D,0x7F,0x4A,0x4B,0x4C,0x41,0x55,0x56,0x49,0x42,0x43,0x44,0x54,0x5A,0x5F,0x5B,0x5E,0x7F,0x48,0x4F,0x52,0x51,0x54,0x53,0x56,0x55,0x58,0x57,0x5A,0x5B,0x5C,0x5D,0x71,0x70,0x73,0x72,
                                  0x75,0x74,0x77,0x76,0x7F,0x4C,0x7F,0x4F,0x4E,0x52,0x51,0x54,0x5A,0x77,0x47,0x5B,0x64,0x65,0x66,0x67,0x78,0x79,0x40,0x55,0x23,0x22};

const uint8_t corded_data[] = {0x05,0x40,0x40,0x31,0x0F,0x07,0x2F,0x00,0x0D,0x12,0xDB,0x12,0xDC,0x12,0xEA,0x15,0x2D,0x00,0x55};
const uint8_t corded_reg[] = {0x7F,0x51,0x53,0x61,0x6E,0x7F,0x42,0x43,0x7F,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x7F,0x54};
const uint8_t office_data[] = {0x05,0x28,0x30,0x3B,0x1F,0x07,0x32,0x00,0x0D,0x00,0x49,0x00,0x5B,0x00,0x64,0x02,0xA5,0x00,0x52,0x0A,0x0F};
const uint8_t lp_data[] = {0x05,0x40,0x40,0x3B,0x1F,0x07,0x32,0x00,0x0D,0x00,0x49,0x00,0x5B,0x00,0x64,0x02,0xA5,0x00,0x54,0x01,0x9C};
const uint8_t hp_data[] = {0x05,0x40,0x40,0x31,0x0F,0x07,0x32,0x00,0x0D,0x00,0x49,0x00,0x5B,0x00,0x64,0x02,0xA5,0x00,0x54,0x01,0x9C};
const uint8_t other_mode_reg[] = {0x7F,0x51,0x53,0x61,0x6E,0x7F,0x42,0x43,0x7F,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x7F,0x54,0x78,0x79};

static int mouse_sensor_sensor_init_workround(const struct device *dev);
static int mouse_sensor_reinit(const struct device *dev);

void mouse_sensor_callback(hal_spi_master_callback_event_t event, void *user_data){

    if(HAL_SPI_MASTER_EVENT_RECEIVE_FINISHED == event){
        if(mouse_burst_data->data_ready_handler != NULL){
            struct sensor_trigger trig = {
                .type = SENSOR_TRIG_DATA_READY,
                .chan = SENSOR_CHAN_ALL,
            };
            mouse_burst_data->data_ready_handler(DEVICE_DT_INST_GET(0), &trig);
        }
    }
}
static void spi_delay_config(const struct device *dev,bool delay_config){
    uint32_t mask;
    const struct mouse_sensor_config *dev_config = dev->config;
    struct mouse_sensor_data *dev_data = dev->data;
    if(dev_data->delay_config != delay_config){
        if(delay_config == false){
            hal_spi_master_set_delay_cnt(dev_config->port_num,0,0,false);
        }else{
            hal_spi_master_set_delay_cnt(dev_config->port_num,64,0,false);
        }
        hal_nvic_save_and_set_interrupt_mask(&mask);
        dev_data->delay_config = delay_config;
        hal_nvic_restore_interrupt_mask(mask);
    }
}

static int  mouse_sensor_write(const struct device *dev,uint8_t address,uint8_t data)
{
    int ret;
    uint32_t mask;
    const struct mouse_sensor_config *dev_config = dev->config;
    struct mouse_sensor_data *dev_data = dev->data;
    uint8_t buf[2];
    buf[0] = address | (1 << 7);
    buf[1] = data;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    dev_data->setting_flag++;
    hal_nvic_restore_interrupt_mask(mask);
    spi_delay_config(dev,false);
    mouse_sensor_set_bt_trig(dev,false);
    ret=hal_spi_master_send_polling(dev_config->port_num,buf,sizeof(buf));
    if(ret != HAL_SPI_MASTER_STATUS_OK)
    {
        log_mouse_sensor_error("[MOUSE][3395] spi master send error:%d address:%x", 2,ret,address);
        return -EIO;
    }
    hal_nvic_save_and_set_interrupt_mask(&mask);
    mouse_burst_data->burst_flag = false;
    dev_data->setting_flag--;
    hal_nvic_restore_interrupt_mask(mask);
    return 0;
}

static int  mouse_sensor_read(const struct device *dev,uint8_t address,uint8_t *data)
{
    int ret;
    uint32_t mask;
    const struct mouse_sensor_config *dev_config = dev->config;
    struct mouse_sensor_data *dev_data = dev->data;
    hal_spi_master_send_and_receive_config_t spi_send_and_receive_config;
    uint8_t receive_buf[2];
    spi_send_and_receive_config.receive_length = 2;
    spi_send_and_receive_config.send_length = 1;
    spi_send_and_receive_config.send_data = &address;
    spi_send_and_receive_config.receive_buffer = receive_buf;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    dev_data->setting_flag++;
    hal_nvic_restore_interrupt_mask(mask);
    mouse_sensor_set_bt_trig(dev,false);
    spi_delay_config(dev,true);
    ret = hal_spi_master_send_and_receive_polling(dev_config->port_num, &spi_send_and_receive_config);
    if(ret != HAL_SPI_MASTER_STATUS_OK)
    {
        log_mouse_sensor_error("[MOUSE][3395] spi master read error:%d address:%x", 2,ret,address);
        return -EIO;
    }
    *data = receive_buf[1];
    hal_nvic_save_and_set_interrupt_mask(&mask);
    mouse_burst_data->burst_flag = false;
    dev_data->setting_flag--;
    hal_nvic_restore_interrupt_mask(mask);
    return 0;
}

ATTR_TEXT_IN_TCM static int mouse_sensor_burst_read(const struct device *dev,uint8_t burst_size,bool is_start){

    int ret;
    uint32_t mask;
    const struct mouse_sensor_config *dev_config = dev->config;
    struct mouse_sensor_data *dev_data = dev->data;
    if(burst_size > MAX_BURST_SIZE){
        return -EINVAL;
    }
    if(dev_data->setting_flag != 0){
        return -EBUSY;
    }
    spi_delay_config(dev,true);
    if((is_start == false) || ((is_start == true) && (mouse_burst_data->burst_flag == false))){  //is_start false is bt trigger.other manual trigger, first need set spi
        uint8_t size = burst_size+1;
        hal_spi_master_send_and_receive_config_t spi_send_and_receive_config;
        spi_send_and_receive_config.receive_length = size;
        spi_send_and_receive_config.send_length = 1;
        spi_send_and_receive_config.send_data = &burst_reg;
        spi_send_and_receive_config.receive_buffer = (uint8_t *)&(mouse_burst_data->reserved);
        ret = hal_spi_master_send_and_receive_dma_advanced(dev_config->port_num, &spi_send_and_receive_config,false);   //not start
        if(ret != HAL_SPI_MASTER_STATUS_OK)
        {
            log_mouse_sensor_error("[MOUSE][3395] spi master burst read error:%d", 1,ret);
            return -EIO;
        }
        hal_nvic_save_and_set_interrupt_mask(&mask);
        mouse_burst_data->burst_flag = true;
        hal_nvic_restore_interrupt_mask(mask);
    }
    if(is_start){
        hal_spi_master_restore_address_advanced(dev_config->port_num,&burst_reg,(uint8_t *)&(mouse_burst_data->reserved));
        hal_spi_master_trigger_start(dev_config->port_num, true);  //trig start
    }
    return 0;
}

static int  mouse_sensor_clear_data(const struct device *dev,uint8_t count)
{
    int ret;
    uint32_t mask;
    const struct mouse_sensor_config *dev_config = dev->config;
    struct mouse_sensor_data *dev_data = dev->data;
    hal_spi_master_send_and_receive_config_t spi_send_and_receive_config;
    uint8_t receive_buf[8];
    spi_send_and_receive_config.receive_length = 8;
    spi_send_and_receive_config.send_length = 1;
    spi_send_and_receive_config.send_data = &burst_reg;
    spi_send_and_receive_config.receive_buffer = receive_buf;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    dev_data->setting_flag++;
    hal_nvic_restore_interrupt_mask(mask);
    mouse_sensor_set_bt_trig(dev,false);
    spi_delay_config(dev,true);
    for(int i = 0;i < count;i++){
        ret = hal_spi_master_send_and_receive_polling(dev_config->port_num, &spi_send_and_receive_config);
        if(ret != HAL_SPI_MASTER_STATUS_OK)
        {
            log_mouse_sensor_error("[MOUSE][3395] spi master clear data error:%d", 1,ret);
            return -EIO;
        }
    }
    hal_nvic_save_and_set_interrupt_mask(&mask);
    mouse_burst_data->burst_flag = false;
    dev_data->setting_flag--;
    hal_nvic_restore_interrupt_mask(mask);
    if((receive_buf[2] != 0xB7) && (receive_buf[2] != 0xBF)){
        mouse_sensor_reinit(dev);
    }
    return 0;
}

static int mouse_sensor_sensor_get_spi_status(const struct device *dev,struct sensor_value *val){
    const struct mouse_sensor_config *dev_config = dev->config;
    int ret =0;
    if(mouse_burst_data->init_flag != true){
        return -EBUSY;
    }
    hal_spi_master_running_status_t status;
    ret = hal_spi_master_get_running_status(dev_config->port_num ,&status);
    if(ret != 0){
        return -EPERM;
    }
    val->val1 = status;
    return 0;
}

static int mouse_sensor_set_bt_trig(const struct device *dev,bool bt_trig){
    int ret;
    uint32_t mask;
    const struct mouse_sensor_config *dev_config = dev->config;
    struct mouse_sensor_data *dev_data = dev->data;
    if(dev_data->bt_trigger == bt_trig){
        return 0;
    }
    struct sensor_value val={1,1};
    if(bt_trig == false){
        hal_spi_master_set_bt_enable(dev_config->port_num,false);       //disable BT trigger
        while(val.val1 != 0){
            mouse_sensor_sensor_get_spi_status(dev,&val);
        }
    }
    else{
        ret = mouse_sensor_burst_read(dev,6,false);    //set spi burst read reg,not start
        if(ret != HAL_SPI_MASTER_STATUS_OK){
            log_mouse_sensor_error("[MOUSE][3395] spi bt trigger set error :%d", 1, bt_trig);
            return -EIO;
        }
        hal_spi_master_set_bt_enable(dev_config->port_num,true);           //enable BT trigger
    }
    hal_nvic_save_and_set_interrupt_mask(&mask);
    dev_data->bt_trigger = bt_trig;
    hal_nvic_restore_interrupt_mask(mask);
    log_mouse_sensor_info("[MOUSE][3395] spi bt trigger set success :%d", 1, bt_trig);
    return 0;
}

static int mouse_sensor_srom_download(const struct device *dev){
    int ret=0,i;
    uint8_t data = 0;
    for(i=0;i<sizeof(download_data);i++){
        ret|=mouse_sensor_write(dev,download_reg[i],download_data[i]);
    }
    hal_gpt_delay_ms(1);
    if(ret != 0){
        log_mouse_sensor_error("[MOUSE][3395] srom load failed1 ", 0);
        return -EIO;
    }
    for (i = 0; i < 60; i++)
    {
        ret |= mouse_sensor_read(dev,0x6C,&data);
        hal_gpt_delay_ms(1);
        if(data == 0x80){
            break;
        }
    }
    if(i == 60){
        log_mouse_sensor_error("[MOUSE][3395] srom load failed2 ", 0);
        ret |= mouse_sensor_write(dev,0x7F,0x14);
        ret |= mouse_sensor_write(dev,0x6C,0x00);
        ret |= mouse_sensor_write(dev,0x7F,0x00);
        // return int_ERROR;
    }
    ret |= mouse_sensor_write(dev,0x22,0x00);
    ret |= mouse_sensor_write(dev,0x55,0x00);
    ret |= mouse_sensor_write(dev,0x7F,0x07);
    ret |= mouse_sensor_write(dev,0x40,0x40);
    ret |= mouse_sensor_write(dev,0x7F,0x00);
    return ret;
}

static void mouse_sensor_cs_pin_reset(const struct device *dev)
{
    const struct mouse_sensor_config *dev_config = dev->config;
    if(dev_config->cs_pin == 0){
        log_mouse_sensor_error("[MOUSE][3950] sensor cs pin number not setting", 0);
        return;
    }
    uint8_t pin_number =  AIROHA_GET_PIN_NUM(dev_config->cs_pin);
    uint8_t pin_func =  AIROHA_GET_PIN_ALT_FUNC(dev_config->cs_pin);
    log_mouse_sensor_info("[MOUSE][3950] cs_pin_reset: pin_number = %d, pin_func = %d",2,pin_number,pin_func);
    hal_pinmux_set_function(pin_number,0);
    hal_gpio_set_direction(pin_number,1);
    hal_gpio_set_output(pin_number,1);
    hal_gpt_delay_ms(1);
    hal_gpio_set_output(pin_number,0);
    hal_pinmux_set_function(pin_number,pin_func);
    return;
}

static int mouse_sensor_poweron(const struct device *dev){
    int i,ret =0;
    uint8_t data = 0,count=0;
    uint32_t init_left_time = global_init_left_time;
    uint32_t init_time = 0;
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K,&(global_init_left_time));
    hal_gpt_get_duration_count(init_left_time,global_init_left_time,&init_time);
    uint32_t init_time_ms = init_time / 32 ;
    if(init_time_ms < 50){
        hal_gpt_delay_ms(50 - init_time_ms);
    }
    mouse_sensor_cs_pin_reset(dev);
    ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Power_Up_Reset, 0x5A);
    hal_gpt_delay_ms(5);
    for (i = 0; i < 5; i++){
        ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Product_ID,&data);
        if(data == 0x51){
            break;
        }
    }
    if(i == 5){
        log_mouse_sensor_error("[MOUSE][3395] sensor not connected ", 0);
        return -EIO;
    }

    while(1){
        if(count == 10){
            return -EIO;
        }
        if(mouse_sensor_srom_download(dev) == 0){
            break;
        }
        count++;
    }
    ret |= mouse_sensor_read(dev,0x2,&data);
    ret |= mouse_sensor_read(dev,0x3,&data);
    ret |= mouse_sensor_read(dev,0x4,&data);
    ret |= mouse_sensor_read(dev,0x5,&data);
    ret |= mouse_sensor_read(dev,0x6,&data);
    log_mouse_sensor_info("[MOUSE][3395] sensor power on success ", 0);
    return ret;
}
static int mouse_sensor_Corded_GamingMode(const struct device *dev){

    int ret=0,i;
    for(i =0;i<sizeof(corded_data);i++){
        ret |= mouse_sensor_write(dev,corded_reg[i],corded_data[i]);
    }
    ret |= mouse_sensor_write(dev,0x40,0x83);
    return ret;
}

static int mouse_sensor_OfficeMode(const struct device *dev){

    int ret=0,i;
    uint8_t data = 0;
    for(i =0;i<sizeof(office_data);i++){
        ret |= mouse_sensor_write(dev,other_mode_reg[i],office_data[i]);
    }
    ret |= mouse_sensor_read(dev,0x40,&data);
    ret |= mouse_sensor_write(dev,0x40,((data & 0xFC)|0x82));
    return ret;
}

static int mouse_sensor_Low_Power_Mode(const struct device *dev){

    int ret=0,i;
    uint8_t data = 0;
    for(i =0;i<sizeof(lp_data);i++){
        ret |= mouse_sensor_write(dev,other_mode_reg[i],lp_data[i]);
    }
    ret |= mouse_sensor_read(dev,0x40,&data);
    ret |= mouse_sensor_write(dev,0x40,((data & 0xFC)|0x81));
    return ret;
}

static int mouse_sensor_High_Performance_Mode(const struct device *dev){

    int ret=0,i;
    uint8_t data = 0;
    for(i =0;i<sizeof(hp_data);i++){
        ret |= mouse_sensor_write(dev,other_mode_reg[i],hp_data[i]);
    }
    ret |= mouse_sensor_read(dev,0x40,&data);
    ret |= mouse_sensor_write(dev,0x40,((data & 0xFC)|0x80));
    return ret;
}
static int mouse_sensor_LiftCutOff_setting1mm(const struct device *dev){

    int ret=0;
    uint8_t data = 0;
    ret |= mouse_sensor_write(dev,0x7F,0x0C);
    ret |= mouse_sensor_read(dev,0x4E,&data);
    ret |= mouse_sensor_write(dev,0x7F,0x00);
    ret |= mouse_sensor_write(dev,0x7F,0x0C);
    ret |= mouse_sensor_write(dev,0x4E,(data & 0xFC));
    ret |= mouse_sensor_write(dev,0x7F,0x00);
    return ret;
}

static int mouse_sensor_LiftCutOff_setting2mm(const struct device *dev){

    int ret = 0;
    uint8_t data = 0;
    ret |= mouse_sensor_write(dev,0x7F,0x0C);
    ret |= mouse_sensor_read(dev,0x4E,&data);
    ret |= mouse_sensor_write(dev,0x7F,0x00);
    ret |= mouse_sensor_write(dev,0x7F,0x0C);
    ret |= mouse_sensor_write(dev,0x4E,(data & 0xFC)|(0x02));
    ret |= mouse_sensor_write(dev,0x7F,0x00);
    return ret;
}

static int mouse_sensor_liftCutOff_setting(const struct device *dev,uint8_t lift,bool force){
    int ret =0;
    uint32_t mask;
    struct mouse_sensor_data *dev_data = dev->data;
    if((dev_data->lod == lift) && (force == false)){
        return ret;
    }
    if(lift == lift_cut_off_1mm){
        ret |= mouse_sensor_LiftCutOff_setting1mm(dev);
    }else if(lift == lift_cut_off_2mm){
        ret |= mouse_sensor_LiftCutOff_setting2mm(dev);
    }
    else{
        log_mouse_sensor_error("[MOUSE][3395] sensor set LOD failed,setting:%d", 1, lift);
        return -EINVAL;
    }
    if(ret == 0) {
        hal_nvic_save_and_set_interrupt_mask(&mask);
        dev_data->lod = lift;
        hal_nvic_restore_interrupt_mask(mask);
    }
    log_mouse_sensor_info("[MOUSE][3395] sensor set LOD success,setting:%d", 1, lift);
    return ret;
}

static int mouse_sensor_read_liftCutOff_setting(const struct device *dev,uint8_t *lift){
    int ret =0;
    uint8_t data = 0;
    ret |= mouse_sensor_write(dev,0x7F,0x0C);
    ret |= mouse_sensor_read(dev,0x4E,&data);
    ret |= mouse_sensor_write(dev,0x7F,0x00);
    if(ret == 0) {
        if((data & 0x3) == 0) *lift = lift_cut_off_1mm;
        else if((data & 0x3) == 2) *lift = lift_cut_off_2mm;
    }
    return ret;
}
// static int mouse_sensor_get_lift_cut_off(const struct device *dev,lift_cut_off *set){
//     int ret;
//     uint8_t data = 0;
//     ret = mouse_sensor_write(dev,0x7F,0x0C);
//     ret |= mouse_sensor_read(dev,0x4E,&data);
//     ret |= mouse_sensor_write(dev,0x7F,0x00);
//     if((data & 0x03) == 0x00){
//         *set = lift_cut_off_1mm;
//     }
//     else if((data & 0x03) == 0x02){
//         *set = lift_cut_off_2mm;
//     }
//     else{
//         printf("\r\nPAW 3395 LiftCutOff get fail\r\n");
//     }
//     return 0;
// }

static int mouse_sensor_rest_mode(const struct device *dev,bool status,bool force){

    uint8_t data = 0;
    int ret=0;
    uint32_t mask;
    struct mouse_sensor_data *dev_data = dev->data;
    if((dev_data->rest_mode == status)&& (force == false)){
        return ret;
    }
    ret  |= mouse_sensor_read(dev,0x40,&data);
    if(status == false){
        data |= 0x80;
    }
    else{
        data &= ~0x80;
    }
    ret |= mouse_sensor_write(dev,0x40,data);
    if(ret == 0) {
        hal_nvic_save_and_set_interrupt_mask(&mask);
        dev_data->rest_mode = status;
        hal_nvic_restore_interrupt_mask(mask);
    }
    log_mouse_sensor_info("[MOUSE][3395] sensor set rest mode success,setting:%d", 1, status);
    return ret;
}

static int mouse_sensor_read_rest_mode(const struct device *dev,bool *status){

    uint8_t data = 0;
    int ret=0;
    ret  |= mouse_sensor_read(dev,0x40,&data);
    if(ret == 0){
        if(data >> 7 & 0x1){
            *status = false;
        }else{
            *status = true;
        }
    }
    return ret;
}

static int mouse_sensor_cpi(const struct device *dev,uint32_t cpi,cpi_setting setting,bool force)
{
    uint32_t value;
    uint8_t data = 0;
    uint8_t High = 0;
    uint8_t Low = 0;
    int8_t ret = 0;
    uint32_t mask;
    struct mouse_sensor_data *dev_data = dev->data;
    if(cpi > 26000){
        printf("\r\nMOUSE_SENSOR cpi write too big :%d\r\n",cpi);
        return -EINVAL;
    }
    if(force == false){
        if((cpi_both_setting == setting) && (dev_data->cpi == cpi) ){
            return ret;
        }
        if((cpi_x_setting == setting) && (dev_data->cpi_x == cpi) ){
            return ret;
        }
        if((cpi_y_setting == setting) && (dev_data->cpi_y == cpi) ){
            return ret;
        }
    }
    value = (cpi / 50)-1;
    High= (value / 256);
    Low= (value % 256);
    if((cpi_x_setting == setting) || (cpi_both_setting == setting)){
        ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Resolution_X_Low, Low);
        ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Resolution_X_High, High);
    }
    if((cpi_y_setting == setting) || (cpi_both_setting == setting)){
        ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Resolution_Y_Low, Low);
        ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Resolution_Y_High, High);
    }
    ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Resolution, 0x1);                          //updata resolution setting
    if(cpi >= 9000){
        ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Ripple_Control, &data);
        ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Ripple_Control,(data|0x80));
        if(ret == 0) {
            hal_nvic_save_and_set_interrupt_mask(&mask);
            dev_data->ripple_control = 1;                        //enable ripple control
            hal_nvic_restore_interrupt_mask(mask);
        }
    }
    if(ret == 0) {
        hal_nvic_save_and_set_interrupt_mask(&mask);
        if(cpi_both_setting == setting){
            dev_data->cpi = cpi;
            dev_data->cpi_x = cpi;
            dev_data->cpi_y = cpi;
        }
        if(cpi_x_setting == setting){
            dev_data->cpi_x = cpi;
        }
        if(cpi_y_setting == setting){
            dev_data->cpi_y = cpi;
        }
        hal_nvic_restore_interrupt_mask(mask);
    }
    log_mouse_sensor_info("[MOUSE][3395] sensor set cpi success,cpi:%d,setting:%d", 2, cpi,setting);
    return ret;
}


static int mouse_sensor_read_cpi(const struct device *dev,cpi_setting setting,int32_t *cpi)
{
    uint8_t High_x,Low_x,High_y,Low_y;
    int8_t ret = 0;
    if((cpi_both_setting == cpi_x_setting) || (cpi_both_setting == setting)){
        ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Resolution_X_Low, &Low_x);
        ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Resolution_X_High, &High_x);
    }
    if((cpi_both_setting == cpi_y_setting) || (cpi_both_setting == setting)){
        ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Resolution_Y_Low, &Low_y);
        ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Resolution_Y_High, &High_y);
    }
    if(ret == 0) {
        if((cpi_both_setting == setting) && (Low_x == Low_y) && (High_x == High_y)){
            *cpi = (((High_x << 8) + Low_x +1) * 50);
        }else if(cpi_both_setting == cpi_x_setting){
            *cpi = (((High_x << 8) + Low_x +1) * 50);
        }else if(cpi_both_setting == cpi_y_setting){
            *cpi = (((High_y << 8) + Low_y +1) * 50);
        }else{
            return -EINVAL;
        }
    }
    return ret;
}

static int mouse_sensor_xy_direction(const struct device *dev,mouse_degree degree,bool force)
{
    int ret = 0;
    uint32_t mask;
    struct mouse_sensor_data *dev_data = dev->data;
    if((dev_data->xy_direction == degree) && (force == false)){
        return ret;
    }
    switch(degree){
        case Swap_XY:
            ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Axis_Control, 0x80);
            break;
        case INV_Y:
            ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Axis_Control, 0x40);
            break;
        case INV_X:
            ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Axis_Control, 0x20);
            break;
        case INV_XY:
            ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Axis_Control, 0x60);
            break;
        case INV_X_AND_Swap_XY:
            ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Axis_Control, 0xA0);
            break;
        case INV_Y_AND_Swap_XY:
            ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Axis_Control, 0xC0);
            break;
        case INV_XY_AND_Swap_XY:
            ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Axis_Control, 0xE0);
            break;
        case NOT_INV_AND_NOT_SWAP:
            ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Axis_Control, 0x00);
            break;
        case NO_DIRECTION_ADJUSTMENT:
            break;
        default:
            // printf("error para\r\n");
            return -EINVAL;
    }
    if(ret == 0) {
        hal_nvic_save_and_set_interrupt_mask(&mask);
        dev_data->xy_direction = degree;
        hal_nvic_restore_interrupt_mask(mask);
    }
    log_mouse_sensor_info("[MOUSE][3395] sensor set xy direction success,setting:%d", 1, degree);
    return ret;
}

static int mouse_sensor_read_xy_direction(const struct device *dev,mouse_degree *degree)
{
    uint8_t value;
    int8_t ret;
    ret = mouse_sensor_read(dev,MOUSE_SENSOR_Axis_Control, &value);
    switch(value)
    {
        case 0x80: *degree = Swap_XY;
            break;
        case 0x60: *degree = INV_XY;
            break;
        case 0x40: *degree = INV_Y;
            break;
        case 0x20: *degree = INV_X;
            break;
        case 0xA0: *degree = INV_X_AND_Swap_XY;
            break;
        case 0xC0: *degree = INV_Y_AND_Swap_XY;
            break;
        case 0xE0: *degree = INV_XY_AND_Swap_XY;
            break;
        case 0x00: *degree = NOT_INV_AND_NOT_SWAP;
            break;
        default:
            return -EINVAL;
    }
    return ret;
}

static int mouse_sensor_config_rest_reg(const struct device *dev,mouse_rest_reg reg,uint8_t value)
{
    uint8_t data = 0;
    int ret = 0;
    switch (reg){
        case Run_DownShift:
            if((value >= 1 ) && (value <= 255 )){
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Run_DownShift, value);
                break;
            }
            else{
                return -EINVAL;
            }
        case Rest1_Period:
            if((value >= 1 ) && (value <= 255 )){
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Rest1_Period, value);
                break;
            }
            else{
                return -EINVAL;
            }
        case Rest1_DownShift:
            if((value >= 1 ) && (value <= 255 )){
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Rest1_DownShift, value);
                break;
            }
            else{
                return -EINVAL;
            }
        case Rest2_Period:
            if((value >= 1 ) && (value <= 255 )){
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Rest2_Period, value);
                break;
            }
            else{
                return -EINVAL;
            }
        case Rest2_DownShift:
            if((value >= 1 ) && (value <= 255 )){
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Rest2_DownShift, value);
                break;
            }
            else{
                return -EINVAL;
            }
        case Rest3_Period:
            if((value >= 1 ) && (value <= 255 )){
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Rest3_Period, value);
                break;
            }
            else{
                return -EINVAL;
            }
        case Run_DownShift_Mult:
            if((value >= 0 ) && (value <= 10 )){
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Run_DownShift_Mult, value);
                break;
            }
            else{
                return -EINVAL;
            }
        case Rest1_DownShift_Mult:
            if((value >= 0 ) && (value <= 7 )){
                ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Rest_DownShift_Mult, &data);
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Rest_DownShift_Mult, ((data & 0xF8) | value ));
                break;
            }
            else{
                return -EINVAL;
            }
        case Rest2_DownShift_Mult:
            if((value >= 0 ) && (value <= 7 )){
                ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Rest_DownShift_Mult, &data);
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Rest_DownShift_Mult, ((data & 0x8F)|(value << 4)));
                break;
            }
            else{
                return -EINVAL;
            }
        default:
            return -EINVAL;
    }
    return ret;
}


static int mouse_sensor_read_rest_reg(const struct device *dev,mouse_rest_reg reg,uint8_t *value)
{
    uint8_t data = 0;
    int ret = 0;
    switch (reg){
        case Run_DownShift:
                return mouse_sensor_read(dev,MOUSE_SENSOR_Run_DownShift, value);
        case Rest1_Period:
                return mouse_sensor_read(dev,MOUSE_SENSOR_Rest1_Period, value);
        case Rest1_DownShift:
                return mouse_sensor_read(dev,MOUSE_SENSOR_Rest1_DownShift, value);
        case Rest2_Period:
                return mouse_sensor_read(dev,MOUSE_SENSOR_Rest2_Period, value);
        case Rest2_DownShift:
                return mouse_sensor_read(dev,MOUSE_SENSOR_Rest2_DownShift, value);
        case Rest3_Period:
                return mouse_sensor_read(dev,MOUSE_SENSOR_Rest3_Period, value);
        case Run_DownShift_Mult:
                return mouse_sensor_read(dev,MOUSE_SENSOR_Run_DownShift_Mult, value);
        case Rest1_DownShift_Mult:
                ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Rest_DownShift_Mult, &data);
                if(ret == 0){
                    *value = data & 0x7;
                }
                else{
                    return -EINVAL;
                }
                break;
        case Rest2_DownShift_Mult:
                ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Rest_DownShift_Mult, &data);
                if(ret == 0){
                    *value = (data >> 4) & 0x7;
                }
                else{
                    return -EINVAL;
                }
                break;
        default:
            return -EINVAL;
    }
    return ret;
}
static int mouse_sensor_config_period_time(const struct device *dev,mouse_period_time rate,uint16_t value_ms,bool force){

    int ret = 0;
    uint8_t value;
    uint32_t mask;
    struct mouse_sensor_data *dev_data = dev->data;
    switch (rate){
        case Rest1_Period_time:
            if((dev_data->rest1_period_time == value_ms) && (force == false)){
                return ret;
            }
            value = value_ms;
            ret |= mouse_sensor_config_rest_reg(dev,Rest1_Period,value);
            if(ret == 0){
                hal_nvic_save_and_set_interrupt_mask(&mask);
                dev_data->rest1_period_time = value_ms;
                hal_nvic_restore_interrupt_mask(mask);
            }
            break;
        case Rest2_Period_time:
            if((dev_data->rest2_period_time == value_ms) && (force == false)){
                return ret;
            }
            value = value_ms / 4;
            ret |= mouse_sensor_config_rest_reg(dev,Rest2_Period,value);
            if(ret == 0){
                hal_nvic_save_and_set_interrupt_mask(&mask);
                dev_data->rest2_period_time = value_ms;
                hal_nvic_restore_interrupt_mask(mask);
            }
            break;

        case Rest3_Period_time:
            if((dev_data->rest3_period_time == value_ms) && (force == false)){
                return ret;
            }
            value = value_ms / 8;
            ret |= mouse_sensor_config_rest_reg(dev,Rest3_Period,value);
            if(ret == 0){
                hal_nvic_save_and_set_interrupt_mask(&mask);
                dev_data->rest3_period_time = value_ms;
                hal_nvic_restore_interrupt_mask(mask);
            }
            break;
        default:
            log_mouse_sensor_error("[MOUSE][3395] sensor config period time failed,setting:%d,time:%d", 2, rate,value_ms);
            return -EIO;
    }
    return 0;
}

static int mouse_sensor_read_period_time(const struct device *dev,mouse_period_time rate,uint16_t *value_ms){

    int ret = 0;
    uint8_t value;
    switch (rate){
        case Rest1_Period_time:
            ret |= mouse_sensor_read_rest_reg(dev,Rest1_Period,&value);
            if(ret == 0){
                *value_ms = value;
            }else{
                return -EIO;
            }
            break;
        case Rest2_Period_time:
            ret |= mouse_sensor_read_rest_reg(dev,Rest2_Period,&value);
            if(ret == 0){
                *value_ms = value * 4;
            }else{
                return -EIO;
            }
            break;

        case Rest3_Period_time:
            ret |= mouse_sensor_read_rest_reg(dev,Rest3_Period,&value);
            if(ret == 0){
                *value_ms = value * 8;
            }else{
                return -EIO;
            }
            break;
        default:
            log_mouse_sensor_error("[MOUSE][3395] sensor read period time failed,setting:%d,time:%d", 2, rate,value_ms);
            return -EIO;
    }
    return 0;
}
static int mouse_sensor_config_time(const struct device *dev,mouse_rest_time rate,const struct sensor_value *val,bool force)
{
    uint8_t period;
    uint32_t data;
    int ret = 0;
    uint32_t mask;
    struct mouse_sensor_data *dev_data = dev->data;
    uint32_t value1 = (uint32_t)val->val1,value2=(uint32_t)val->val2;
    uint32_t value_ms = ((value2 << 16) | value1);
    switch (rate){
        case Run_DownShift_time:
            if((dev_data->run_downshift_time == value_ms)&&(force == false)){
                return 0;
            }
            data = value_ms*20;
            if(data < 256){
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Run_DownShift_Mult,0);//set mult 2
                data = data/2;
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Run_DownShift,data);
            }else if(data > 65535){
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Run_DownShift_Mult,10);//set mult 2048
                data = data/2048;
                if(data > 255){
                    data = 255;
                }
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Run_DownShift,data);
            }else{
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Run_DownShift_Mult,7);//set default mult 256
                data = data/256;
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Run_DownShift,data);
            }
            if(ret == 0){
                hal_nvic_save_and_set_interrupt_mask(&mask);
                dev_data->run_downshift_time = value_ms;
                hal_nvic_restore_interrupt_mask(mask);
            }else{
                return -EIO;
            }
            break;
        case Rest1_DownShift_time:
            ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Rest1_Period,&period);
            for(int i=0;i<5;i++){
                if(period != 0){
                    break;
                }else{
                    ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Rest1_Period,&period);
                }
            }
            if(period == 0){
                log_mouse_sensor_error("[MOUSE][3395] sensor read rest1 period error,period:%d", 1, period);
                mouse_sensor_reinit(dev);
                return -EIO;
            }
            data = value_ms/period;
            if(data< 256){
                ret |= mouse_sensor_config_rest_reg(dev,Rest1_DownShift_Mult,0); //set mult 2
                data = data/2;
                if(data == 0){
                    data = 1;
                }
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Rest1_DownShift,data);
            }else if(data > 16384){
                ret |= mouse_sensor_config_rest_reg(dev,Rest1_DownShift_Mult,7); //set mult 256
                data = data/256;
                if(data > 255){
                    data = 255;
                }
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Rest1_DownShift,data);
            }else{
                ret |= mouse_sensor_config_rest_reg(dev,Rest1_DownShift_Mult,5); //set mult 64
                data = data/64;
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Rest1_DownShift,data);
            }
            if(ret == 0){
                hal_nvic_save_and_set_interrupt_mask(&mask);
                dev_data->rest1_downshift_time = value_ms;
                hal_nvic_restore_interrupt_mask(mask);
            }else{
                return -EIO;
            }
            break;
        case Rest2_DownShift_time:
            ret |=mouse_sensor_read(dev,MOUSE_SENSOR_Rest2_Period,&period);
            for(int i=0;i<5;i++){
                if(period != 0){
                    break;
                }else{
                    ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Rest2_Period,&period);
                }
            }
            if(period == 0){
                log_mouse_sensor_error("[MOUSE][3395] sensor read rest2 period error,period:%d", 1, period);
                mouse_sensor_reinit(dev);
                return -EIO;
            }
            data = value_ms/period/4;
            if(data< 256){
                ret |=mouse_sensor_config_rest_reg(dev,Rest2_DownShift_Mult,0); //set mult 2
                data = data/2;
                if(data == 0){
                    data = 1;
                }
                ret |=mouse_sensor_write(dev,MOUSE_SENSOR_Rest2_DownShift,data);
            }else if(data > 16384){
                ret |=mouse_sensor_config_rest_reg(dev,Rest2_DownShift_Mult,7); //set mult 256
                data = data/256;
                if(data > 255){
                    data = 255;
                }
                ret |=mouse_sensor_write(dev,MOUSE_SENSOR_Rest2_DownShift,data);
            }else{
                ret |=mouse_sensor_config_rest_reg(dev,Rest2_DownShift_Mult,5); //set mult 64
                data = data/64;
                ret |=mouse_sensor_write(dev,MOUSE_SENSOR_Rest2_DownShift,data);
            }
            if(ret == 0){
                hal_nvic_save_and_set_interrupt_mask(&mask);
                dev_data->rest2_downshift_time = value_ms;
                hal_nvic_restore_interrupt_mask(mask);
            }else{
                return -EIO;
            }
            break;
        default:
            log_mouse_sensor_error("[MOUSE][3395] sensor config time failed,setting:%d", 1, rate);
            return -EIO;
    }
    return 0;
}

static int mouse_sensor_read_config_time(const struct device *dev,mouse_rest_time rate,struct sensor_value *val){

    int ret = 0;
    uint16_t period_time = 0;
    uint8_t downshift = 0;
    uint8_t downshift_mult = 0;
    uint32_t value_ms = 0;
    switch (rate){
        case Run_DownShift_time:
            ret |= mouse_sensor_read_rest_reg(dev,Run_DownShift,&downshift);
            ret |= mouse_sensor_read_rest_reg(dev,Run_DownShift_Mult,&downshift_mult);
            if(ret == 0){
                value_ms = downshift*(1<<(downshift_mult+1))/20;
                val->val1 = (value_ms & 0xFFFF);
                val->val2 = ((value_ms>>16)&0xFFFF);
            }
            else{
                return -EIO;
            }
        break;
        case Rest1_DownShift_time:
            ret |= mouse_sensor_read_period_time(dev,Rest1_Period_time,&period_time);
            ret |= mouse_sensor_read_rest_reg(dev,Rest1_DownShift,&downshift);
            ret |= mouse_sensor_read_rest_reg(dev,Rest1_DownShift_Mult,&downshift_mult);
            if(ret == 0){
                value_ms = period_time*downshift*(1<<(downshift_mult+1));
                val->val1 = (value_ms & 0xFFFF);
                val->val2 = ((value_ms>>16)&0xFFFF);
            }
            else{
                return -EIO;
            }
        break;
        case Rest2_DownShift_time:
            ret |= mouse_sensor_read_period_time(dev,Rest2_Period_time,&period_time);
            ret |= mouse_sensor_read_rest_reg(dev,Rest2_DownShift,&downshift);
            ret |= mouse_sensor_read_rest_reg(dev,Rest2_DownShift_Mult,&downshift_mult);
            if(ret == 0){
                value_ms = period_time*downshift*(1<<(downshift_mult+1));
                val->val1 = (value_ms & 0xFFFF);
                val->val2 = ((value_ms>>16)&0xFFFF);
            }
            else{
                return -EIO;
            }
        break;
        default:
            log_mouse_sensor_error("[MOUSE][3395] sensor read time failed,setting:%d", 1, rate);
            return -EIO;
    }
    return -EIO;
}

static int mouse_sensor_function_setting(const struct device *dev,mouse_function function ,bool state ,bool force){

    uint8_t data = 0;
    int ret =0;
    uint32_t mask;
    struct mouse_sensor_data *dev_data = dev->data;
    switch (function){
        case Motion_sync:
        {
            if((dev_data->motion_sync == state) && (force == false)){
                return ret;
            }
            if(state){
                ret |= mouse_sensor_write(dev,0x7F, 0x0D);
                ret |= mouse_sensor_write(dev,0x48, 0xDD);
                ret |= mouse_sensor_write(dev,0x7F, 0x00);
            }else{
                ret |= mouse_sensor_write(dev,0x7F, 0x0D);
                ret |= mouse_sensor_write(dev,0x48, 0xDC);
                ret |= mouse_sensor_write(dev,0x7F, 0x00);
            }
            if(ret == 0){
                hal_nvic_save_and_set_interrupt_mask(&mask);
                dev_data->motion_sync = state;
                hal_nvic_restore_interrupt_mask(mask);
            }
        }break;
        case Ripple_control:
        {   if((dev_data->ripple_control == state) && (force == false)){
                return ret;
            }
            if((dev_data->cpi > 9000) && (state== false)){
                return -EINVAL;
            }
            if(state){
                ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Ripple_Control, &data);
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Ripple_Control, (data|0x80));
            }else{
                ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Ripple_Control, &data);
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Ripple_Control, (data & 0x7F));
            }
            if(ret == 0){
                hal_nvic_save_and_set_interrupt_mask(&mask);
                dev_data->ripple_control = state;
                hal_nvic_restore_interrupt_mask(mask);
            }
        }break;
        case Angle_Snap:
        {   if((dev_data->angle_snap == state) && (force == false)){
                return ret;
            }
            if(state){
                ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Angle_Snap, &data);
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Angle_Snap, (data|0x80));
            }else{
                ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Angle_Snap, &data);
                ret |= mouse_sensor_write(dev,MOUSE_SENSOR_Angle_Snap, (data & 0x7F));
            }
            if(ret == 0){
                hal_nvic_save_and_set_interrupt_mask(&mask);
                dev_data->angle_snap = state;
                hal_nvic_restore_interrupt_mask(mask);
            }
        }break;
        default:
            log_mouse_sensor_error("[MOUSE][3395] sensor set function failed,setting:%d,status:%d", 2, function,state);
            return -EINVAL;
    }
    log_mouse_sensor_info("[MOUSE][3395] sensor set function success,setting:%d,status:%d", 2, function,state);
    return ret;
}


static int mouse_sensor_read_function_setting(const struct device *dev,mouse_function function ,bool *state){

    uint8_t data = 0;
    int ret =0;
    switch (function){
        case Motion_sync:
                ret |= mouse_sensor_write(dev,0x7F, 0x0D);
                ret |= mouse_sensor_read(dev,0x48, &data);
                ret |= mouse_sensor_write(dev,0x7F, 0x00);
                if(ret == 0){
                    *state = (bool)(data & 0x1);
                }
                else{
                    return -EINVAL;
                }
            break;
        case Ripple_control:
                ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Ripple_Control, &data);
                if(ret == 0){
                    *state = (bool)((data >> 7) & 0x1);
                }
                else{
                    return -EINVAL;
                }
            break;
        case Angle_Snap:
                ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Angle_Snap, &data);
                if(ret == 0){
                    *state = (bool)((data >> 7) & 0x1);
                }
                else{
                    return -EINVAL;
                }
            break;
        default:
            return -EINVAL;
    }
    return ret;
}

static int mouse_sensor_mode_setting(const struct device *dev,mouse_mode mode,bool force){
    int ret=0;
    uint32_t mask;
    struct mouse_sensor_data *dev_data = dev->data;
    struct sensor_value val;
    if((dev_data->mode == mode) &&(force == false)){
        return ret;
    }
    if(mode == corded_gaming_mode){
        ret |= mouse_sensor_Corded_GamingMode(dev);
    }else if(mode == high_performance_mode){
        ret |= mouse_sensor_High_Performance_Mode(dev);
    }else if(mode == low_power_mode){
        ret |= mouse_sensor_Low_Power_Mode(dev);
    }else if(mode == office_mode){
        ret |= mouse_sensor_OfficeMode(dev);
    }
    else{
        log_mouse_sensor_error("[MOUSE][3395] sensor set mode failed,setting:%d", 1, mode);
        return -EIO;
    }
    if(ret == 0){
        hal_nvic_save_and_set_interrupt_mask(&mask);
        dev_data->mode = mode;
        hal_nvic_restore_interrupt_mask(mask);
        mouse_sensor_rest_mode(dev,dev_data->rest_mode,true);
        mouse_sensor_config_period_time(dev,Rest1_Period_time,dev_data->rest1_period_time,true);
        val.val1 = (int32_t)(dev_data->rest1_downshift_time & 0xFFFF);
        val.val2 = (int32_t)((dev_data->rest1_downshift_time>>16)&0xFFFF);
        mouse_sensor_config_time(dev,Rest1_DownShift_time,&val,true);
    }
    log_mouse_sensor_info("[MOUSE][3395] sensor set mode success,setting:%d", 1, mode);
    return ret;
}

static int mouse_sensor_read_mode_setting(const struct device *dev,mouse_mode *mode){
    int ret=0;
    uint8_t data = 0;
    ret |= mouse_sensor_read(dev,0x40,&data);
    data = data & 0x3;
    if(ret == 0) *mode = data;
    return ret;
}

static int mouse_sensor_init_spi(const struct device *dev){
    const struct mouse_sensor_config *dev_config = dev->config;
    hal_spi_master_config_t spi_config;
    int ret = 0;
    spi_config.bit_order = HAL_SPI_MASTER_MSB_FIRST;
    spi_config.slave_port = HAL_SPI_MASTER_SLAVE_0;
    spi_config.clock_frequency = dev_config->frequency;
    spi_config.phase = HAL_SPI_MASTER_CLOCK_PHASE1;
    spi_config.polarity = HAL_SPI_MASTER_CLOCK_POLARITY1;
    ret = hal_spi_master_init(dev_config->port_num, &spi_config);
    if (HAL_SPI_MASTER_STATUS_OK != ret) {
        log_mouse_sensor_error("[MOUSE][3395] sensor init spi failed,ret:%d", 1, ret);
        return -EIO;
    }
    hal_spi_master_set_clear_data(dev_config->port_num,1,1,true);
    return 0;
}

ATTR_TEXT_IN_TCM static int mouse_sensor_data_read(const struct device *dev,enum sensor_channel chan){
    int ret =0;
    if(chan == SENSOR_CHAN_ALL){
        return mouse_sensor_burst_read(dev,6,true);
    }else if(chan == SENSOR_CHAN_POS_DX){
        ret = mouse_sensor_read(dev,MOUSE_SENSOR_Resolution_X_Low,&(mouse_burst_data->x_low));
        ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Resolution_X_High,&(mouse_burst_data->x_high));
        if(ret == 0 ){
            return 0;
        }else{
            return -EIO;
        }
    }else if(chan == SENSOR_CHAN_POS_DY){
        ret = mouse_sensor_read(dev,MOUSE_SENSOR_Resolution_Y_Low,&(mouse_burst_data->y_low));
        ret |= mouse_sensor_read(dev,MOUSE_SENSOR_Resolution_Y_High,&(mouse_burst_data->y_high));
        if(ret == 0 ){
            return 0;
        }else{
            return -EIO;
        }
    }else{
        return -EIO;
    }
}

static int mouse_sensor_sensor_init(const struct device *dev)
{
    uint32_t mask;
    // *(volatile uint32_t *)0x42040B80 = 0xFFFFFFFF;
    const struct mouse_sensor_config *dev_config = dev->config;
    struct mouse_sensor_data *dev_data = dev->data;
    dev_data->force = true;
    if(mouse_burst_data->init_flag == true){
        return -EBUSY;
    }
    if((dev_config->frequency) >  8000000){
        log_mouse_sensor_error("[MOUSE][3395] sensor spi master frequency is %d over 8M\n",1,dev_config->frequency);
        return -EIO;
    }
    if(0 != mouse_sensor_init_spi(dev)){
         return -EIO;
    }
    if(0 != mouse_sensor_poweron(dev)){
        return -EIO;
    }
    if(0 != mouse_sensor_mode_setting(dev,dev_data->mode,dev_data->force)){
        return -EIO;
    }
    if(0 != mouse_sensor_cpi(dev,dev_data->cpi,cpi_both_setting,dev_data->force)){
        return -EIO;
    }
    if(0 != mouse_sensor_liftCutOff_setting(dev,dev_data->lod,dev_data->force)){
        return -EIO;
    }
    if(0 != mouse_sensor_xy_direction(dev,dev_data->xy_direction,dev_data->force)){
        return -EIO;
    }
    // if(0 != mouse_sensor_rest_mode(dev,dev_data->rest_mode,dev_data->force)){    // mode setting instead rest mode
    //     return -EIO;
    // }
    if(0 != mouse_sensor_function_setting(dev,Motion_sync,dev_data->motion_sync,dev_data->force)){
        return -EIO;
    }
    if(0 != mouse_sensor_function_setting(dev,Ripple_control,dev_data->ripple_control,dev_data->force)){
        return -EIO;
    }
    if(0 != mouse_sensor_function_setting(dev,Angle_Snap,dev_data->angle_snap,dev_data->force)){
        return -EIO;
    }
    if(0 != mouse_sensor_config_period_time(dev,Rest1_Period_time,dev_data->rest1_period_time,dev_data->force)){ // mode setting instead rest1 time setting
        return -EIO;
    }
    if(0 != mouse_sensor_config_period_time(dev,Rest2_Period_time,dev_data->rest2_period_time,dev_data->force)){
        return -EIO;
    }
    if(0 != mouse_sensor_config_period_time(dev,Rest3_Period_time,dev_data->rest3_period_time,dev_data->force)){
        return -EIO;
    }
    struct sensor_value value_run_downshift_time;
    value_run_downshift_time.val1 = (dev_data->run_downshift_time & 0xFFFF);
    value_run_downshift_time.val2 = (dev_data->run_downshift_time>>16 & 0xFFFF);
    if(0 != mouse_sensor_config_time(dev,Run_DownShift_time,&value_run_downshift_time,dev_data->force)){
        return -EIO;
    }
    struct sensor_value value_rest1_downshift_time;
    value_rest1_downshift_time.val1 = (dev_data->rest1_downshift_time & 0xFFFF);
    value_rest1_downshift_time.val2 = (dev_data->rest1_downshift_time>>16 & 0xFFFF);
    if(0 != mouse_sensor_config_time(dev,Rest1_DownShift_time,&value_rest1_downshift_time,dev_data->force)){
        return -EIO;
    }
    struct sensor_value value_rest2_downshift_time;
    value_rest2_downshift_time.val1 = (dev_data->rest2_downshift_time & 0xFFFF);
    value_rest2_downshift_time.val2 = ((dev_data->rest2_downshift_time>>16) & 0xFFFF);
    if(0 != mouse_sensor_config_time(dev,Rest2_DownShift_time,&value_rest2_downshift_time,dev_data->force)){
        return -EIO;
    }
    hal_nvic_save_and_set_interrupt_mask(&mask);
    mouse_burst_data->init_flag = true;
    dev_data->force = false;
    hal_nvic_restore_interrupt_mask(mask);
    log_mouse_sensor_info("[MOUSE][3395] sensor init success\n",0);
    return 0;
}

static int mouse_sensor_reinit(const struct device *dev){
    uint32_t mask;
    struct mouse_sensor_data *dev_data = dev->data;
    if(dev_data->reinit == true){
       return -EBUSY;
    }
    hal_nvic_save_and_set_interrupt_mask(&mask);
    mouse_burst_data->init_flag = false;
    dev_data->reinit = true;
    hal_nvic_restore_interrupt_mask(mask);
    bool bt_trigger = dev_data->bt_trigger;
    mouse_sensor_sensor_init_workround(dev);
    mouse_sensor_set_bt_trig(dev,bt_trigger);
    hal_nvic_save_and_set_interrupt_mask(&mask);
    dev_data->reinit = false;
    hal_nvic_restore_interrupt_mask(mask);
    return 0;
}

static int mouse_sensor_sensor_init_workround(const struct device *dev)
{
    uint32_t mask;
    log_mouse_sensor_info("[MOUSE][3395] sensor init workround\n",0);
    struct mouse_sensor_data *dev_data = dev->data;
    if(0 != mouse_sensor_poweron(dev)){
        return -EIO;
    }
    if(0 != mouse_sensor_mode_setting(dev,dev_data->mode,true)){
        return -EIO;
    }
    if(0 != mouse_sensor_cpi(dev,dev_data->cpi,cpi_both_setting,true)){
        return -EIO;
    }
    if(0 != mouse_sensor_liftCutOff_setting(dev,dev_data->lod,true)){
        return -EIO;
    }
    if(0 != mouse_sensor_xy_direction(dev,dev_data->xy_direction,true)){
        return -EIO;
    }
    // if(0 != mouse_sensor_rest_mode(dev,dev_data->rest_mode,dev_data->force)){    // mode setting instead rest mode
    //     return -EIO;
    // }
    if(0 != mouse_sensor_function_setting(dev,Motion_sync,dev_data->motion_sync,true)){
        return -EIO;
    }
    // if(0 != mouse_sensor_function_setting(dev,Ripple_control,dev_data->ripple_control,dev_data->force)){
    //     return -EIO;
    // }
    if(0 != mouse_sensor_function_setting(dev,Angle_Snap,dev_data->angle_snap,true)){
        return -EIO;
    }
    if(0 != mouse_sensor_config_period_time(dev,Rest1_Period_time,dev_data->rest1_period_time,dev_data->force)){ // mode setting instead rest1 time setting
        return -EIO;
    }
    if(0 != mouse_sensor_config_period_time(dev,Rest2_Period_time,dev_data->rest2_period_time,true)){
        return -EIO;
    }
    if(0 != mouse_sensor_config_period_time(dev,Rest3_Period_time,dev_data->rest3_period_time,true)){
        return -EIO;
    }
    struct sensor_value value_run_downshift_time;
    value_run_downshift_time.val1 = (dev_data->run_downshift_time & 0xFFFF);
    value_run_downshift_time.val2 = (dev_data->run_downshift_time>>16 & 0xFFFF);
    if(0 != mouse_sensor_config_time(dev,Run_DownShift_time,&value_run_downshift_time,true)){
        return -EIO;
    }
    struct sensor_value value_rest1_downshift_time;
    value_rest1_downshift_time.val1 = (dev_data->rest1_downshift_time & 0xFFFF);
    value_rest1_downshift_time.val2 = (dev_data->rest1_downshift_time>>16 & 0xFFFF);
    if(0 != mouse_sensor_config_time(dev,Rest1_DownShift_time,&value_rest1_downshift_time,true)){
        return -EIO;
    }
    struct sensor_value value_rest2_downshift_time;
    value_rest2_downshift_time.val1 = (dev_data->rest2_downshift_time & 0xFFFF);
    value_rest2_downshift_time.val2 = ((dev_data->rest2_downshift_time>>16) & 0xFFFF);
    if(0 != mouse_sensor_config_time(dev,Rest2_DownShift_time,&value_rest2_downshift_time,true)){
        return -EIO;
    }
    hal_nvic_save_and_set_interrupt_mask(&mask);
    mouse_burst_data->init_flag = true;
    hal_nvic_restore_interrupt_mask(mask);
    hal_ccni_set_event(IRQGEN_MCU2RISCV_EVENT20, NULL);
    log_mouse_sensor_info("[MOUSE][3395] sensor workround init success\n",0);
    return 0;
}

static int mouse_sensor_sensor_deinit(const struct device *dev)
{
    uint32_t mask;
    const struct mouse_sensor_config *dev_config = dev->config;
    int ret =0;
    if(mouse_burst_data->init_flag != true){
        log_mouse_sensor_error("[MOUSE][3395] sensor deinit failed,not init\n",0);
        return -EBUSY;
    }
    ret = mouse_sensor_write(dev,MOUSE_SENSOR_Shutdown, 0xB6);
    if(ret != 0) {
        mouse_burst_data->init_flag = true;
        return -EIO;
    }
    hal_nvic_save_and_set_interrupt_mask(&mask);
    mouse_burst_data->init_flag = false;
    hal_nvic_restore_interrupt_mask(mask);
    ret = hal_spi_master_deinit(dev_config->port_num);
    if(ret != 0){
        return -EPERM;
    }
    log_mouse_sensor_error("[MOUSE][3395] sensor deinit success\n",0);
	return 0;
}

static int mouse_sensor_sensor_enable_nvic_irq(const struct device *dev,bool enable){
    const struct mouse_sensor_config *dev_config = dev->config;
    int ret =0;
    if(mouse_burst_data->init_flag != true){
        return -EBUSY;
    }
    ret = hal_spi_enable_nvic_irq(dev_config->port_num ,enable);
    if(ret != 0){
        return -EPERM;
    }
    return 0;
}

static int mouse_sensor_attr_set(const struct device *dev,enum sensor_channel chan,
                            enum sensor_attribute attr,
                            const struct sensor_value *val){
    int ret;
    if(mouse_burst_data->init_flag != true){
        if((uint32_t)attr == MOUSE_SENSOR_ATTR_INIT){
            return mouse_sensor_sensor_init(dev);
        }else{
            log_mouse_sensor_error("[MOUSE][3395] sensor attr set failed, not init, attr:%d\n",1,attr);
            return -EBUSY;
        }
    }
    switch((uint32_t)attr){
        case MOUSE_SENSOR_ATTR_XY_DIRECTION:
            ret = mouse_sensor_xy_direction(dev,val->val1,false);
        break;
        case MOUSE_SENSOR_ATTR_CPI:
            ret = mouse_sensor_cpi(dev,val->val1,cpi_both_setting,false);
        break;
        case MOUSE_SENSOR_ATTR_CPI_X:
            ret = mouse_sensor_cpi(dev,val->val1,cpi_x_setting,false);
        break;
        case MOUSE_SENSOR_ATTR_CPI_Y:
            ret = mouse_sensor_cpi(dev,val->val1,cpi_y_setting,false);
        break;
        case MOUSE_SENSOR_ATTR_LOD:
            ret = mouse_sensor_liftCutOff_setting(dev,val->val1,false);
        break;
        case MOUSE_SENSOR_ATTR_MODE_SET:
            ret = mouse_sensor_mode_setting(dev,val->val1,false);
        break;
        case MOUSE_SENSOR_ATTR_REST_MODE:
            ret = mouse_sensor_rest_mode(dev,val->val1,false);
        break;
        case MOUSE_SENSOR_ATTR_MOTION_SYNC:
            ret = mouse_sensor_function_setting(dev,Motion_sync, val->val1,false);
        break;
        case MOUSE_SENSOR_ATTR_RIPPLE_CONTROL:
            ret = mouse_sensor_function_setting(dev,Ripple_control, val->val1,false);
        break;
        case MOUSE_SENSOR_ATTR_ANGLE_SNAP:
            ret = mouse_sensor_function_setting(dev,Angle_Snap, val->val1,false);
        break;
        case MOUSE_SENSOR_ATTR_RUN_DOWNSHIFT_REG:
            ret = mouse_sensor_config_rest_reg(dev,Run_DownShift, val->val1);
        break;
        case MOUSE_SENSOR_ATTR_REST1_DOWNSHIFT_REG:
            ret = mouse_sensor_config_rest_reg(dev,Rest1_DownShift, val->val1);
        break;
        case MOUSE_SENSOR_ATTR_REST2_DOWNSHIFT_REG:
            ret = mouse_sensor_config_rest_reg(dev,Rest2_DownShift, val->val1);
        break;
        case MOUSE_SENSOR_ATTR_RUN_DOWNSHIFT_MULT_REG:
            ret = mouse_sensor_config_rest_reg(dev,Run_DownShift_Mult, val->val1);
        break;
        case MOUSE_SENSOR_ATTR_REST1_DOWNSHIFT_MULT_REG:
            ret = mouse_sensor_config_rest_reg(dev,Rest1_DownShift_Mult, val->val1);
        break;
        case MOUSE_SENSOR_ATTR_REST2_DOWNSHIFT_MULT_REG:
            ret = mouse_sensor_config_rest_reg(dev,Rest2_DownShift_Mult, val->val1);
        break;
        case MOUSE_SENSOR_ATTR_REST1_PERIOD_TIME:
            ret = mouse_sensor_config_period_time(dev,Rest1_Period_time, val->val1,false);
        break;
        case MOUSE_SENSOR_ATTR_REST2_PERIOD_TIME:
            ret = mouse_sensor_config_period_time(dev,Rest2_Period_time, val->val1,false);
        break;
        case MOUSE_SENSOR_ATTR_REST3_PERIOD_TIME:
            ret = mouse_sensor_config_period_time(dev,Rest3_Period_time, val->val1,false);
        break;
        case MOUSE_SENSOR_ATTR_RUN_DOWNSHIFT_TIME:
            ret = mouse_sensor_config_time(dev,Run_DownShift_time,val,false);
        break;
        case MOUSE_SENSOR_ATTR_REST1_DOWNSHIFT_TIME:
            ret = mouse_sensor_config_time(dev,Rest1_DownShift_time, val,false);
        break;
        case MOUSE_SENSOR_ATTR_REST2_DOWNSHIFT_TIME:
            ret = mouse_sensor_config_time(dev,Rest2_DownShift_time, val,false);
        break;
        case MOUSE_SENSOR_ATTR_BT_TRIGGER:
            ret = mouse_sensor_set_bt_trig(dev,val->val1);
        break;
        case MOUSE_SENSOR_ATTR_DEINIT:
            ret = mouse_sensor_sensor_deinit(dev);
        break;
        case MOUSE_SENSOR_ATTR_CLEAR_DATA:
            ret = mouse_sensor_clear_data(dev,val->val1);
        break;
        case MOUSE_SENSOR_ATTR_SPI_NVIC_IRQ:
            ret = mouse_sensor_sensor_enable_nvic_irq(dev,val->val1);
        break;
        case MOUSE_SENSOR_ATTR_REINIT:
            ret = mouse_sensor_reinit(dev);
        default:
        return -ENOTSUP;
    }
    return ret;
}



static int mouse_sensor_attr_get(const struct device *dev,enum sensor_channel chan,
                            enum sensor_attribute attr,
                            struct sensor_value *val){
    struct mouse_sensor_data *dev_data = dev->data;
    int ret = 0;
    if(mouse_burst_data->init_flag != true){
            log_mouse_sensor_error("[MOUSE][3395] sensor attr get failed, not init,attr:%d\n",attr);
            return -EBUSY;
    }
    switch((uint32_t)attr){
        case MOUSE_SENSOR_ATTR_XY_DIRECTION:
            if((uint32_t)chan == MOUSE_SENSOR_CHAN_RAM_DATA){
                val->val1 = (int32_t)(dev_data->xy_direction);
            }else{
                mouse_degree degree = 0;
                ret = mouse_sensor_read_xy_direction(dev,&degree);
                if(ret == 0)val->val1 = (int32_t)degree;
            }
        break;
        case MOUSE_SENSOR_ATTR_CPI:
            if((uint32_t)chan ==MOUSE_SENSOR_CHAN_RAM_DATA){
                val->val1 = (int32_t)(dev_data->cpi);
            }else{
                ret = mouse_sensor_read_cpi(dev,cpi_both_setting,&(val->val1));
            }
        break;
        case MOUSE_SENSOR_ATTR_CPI_X:
            if((uint32_t)chan ==MOUSE_SENSOR_CHAN_RAM_DATA){
                val->val1 = (int32_t)(dev_data->cpi_x);
            }else{
                ret = mouse_sensor_read_cpi(dev,cpi_x_setting,&(val->val1));
            }
        break;        
        case MOUSE_SENSOR_ATTR_CPI_Y:
            if((uint32_t)chan ==MOUSE_SENSOR_CHAN_RAM_DATA){
                val->val1 = (int32_t)(dev_data->cpi_x);
            }else{
                ret = mouse_sensor_read_cpi(dev,cpi_y_setting,&(val->val1));
            }
        break;
        case MOUSE_SENSOR_ATTR_LOD:
            if((uint32_t)chan ==MOUSE_SENSOR_CHAN_RAM_DATA){
                val->val1 = (int32_t)(dev_data->lod);
            }else{
                uint8_t lod = 0;
                ret = mouse_sensor_read_liftCutOff_setting(dev,&lod);
                if(ret == 0)val->val1 = (int32_t)lod;
            }
        break;
        case MOUSE_SENSOR_ATTR_MODE_SET:
            if((uint32_t)chan ==MOUSE_SENSOR_CHAN_RAM_DATA){
                val->val1 = (int32_t)(dev_data->mode);
            }else{
                mouse_mode mode = 0;
                ret = mouse_sensor_read_mode_setting(dev,&mode);
                if(ret == 0)val->val1 = (int32_t)mode;
            }
        break;
        case MOUSE_SENSOR_ATTR_REST_MODE:
            if((uint32_t)chan ==MOUSE_SENSOR_CHAN_RAM_DATA){
                val->val1 = (int32_t)(dev_data->rest_mode);
            }else{
                bool rest_mode = 0;
                ret = mouse_sensor_read_rest_mode(dev,&rest_mode);
                if(ret == 0)val->val1 = (int32_t)rest_mode;
            }
        break;
        case MOUSE_SENSOR_ATTR_MOTION_SYNC:
            if((uint32_t)chan ==MOUSE_SENSOR_CHAN_RAM_DATA){
                val->val1 = (int32_t)(dev_data->motion_sync);
            }else{
                bool motion_sync = 0;
                ret = mouse_sensor_read_function_setting(dev,Motion_sync,&motion_sync);
                if(ret == 0)val->val1 = (int32_t)motion_sync;
            }
        break;
        case MOUSE_SENSOR_ATTR_RIPPLE_CONTROL:
            if((uint32_t)chan ==MOUSE_SENSOR_CHAN_RAM_DATA){
                val->val1 = (int32_t)(dev_data->ripple_control);
            }else{
                bool ripple_control = 0;
                ret = mouse_sensor_read_function_setting(dev,Ripple_control,&ripple_control);
                if(ret == 0)val->val1 = (int32_t)ripple_control;
            }
        break;
        case MOUSE_SENSOR_ATTR_ANGLE_SNAP:
            if((uint32_t)chan ==MOUSE_SENSOR_CHAN_RAM_DATA){
                val->val1 = (int32_t)(dev_data->angle_snap);
            }else{
                bool angle_snap = 0;
                ret = mouse_sensor_read_function_setting(dev,Angle_Snap,&angle_snap);
                if(ret == 0)val->val1 = (int32_t)angle_snap;
            }
        break;
        case MOUSE_SENSOR_ATTR_RUN_DOWNSHIFT_REG:
            if((uint32_t)chan ==MOUSE_SENSOR_CHAN_RAM_DATA){
                return -EINVAL;
            }else{
                uint8_t run_downshift = 0;
                ret = mouse_sensor_read_rest_reg(dev,Run_DownShift,&run_downshift);
                if(ret == 0)val->val1 = (int32_t)run_downshift;
            }
        break;
        case MOUSE_SENSOR_ATTR_REST1_DOWNSHIFT_REG:
            if((uint32_t)chan ==MOUSE_SENSOR_CHAN_RAM_DATA){
                return -EINVAL;
            }else{
                uint8_t rest1_downshift = 0;
                ret = mouse_sensor_read_rest_reg(dev,Rest1_DownShift,&rest1_downshift);
                if(ret == 0)val->val1 = (int32_t)rest1_downshift;
            }
        break;
        case MOUSE_SENSOR_ATTR_REST2_DOWNSHIFT_REG:
            if((uint32_t)chan ==MOUSE_SENSOR_CHAN_RAM_DATA){
                return -EINVAL;
            }else{
                uint8_t rest2_downshift = 0;
                ret = mouse_sensor_read_rest_reg(dev,Rest2_DownShift,&rest2_downshift);
                if(ret == 0)val->val1 = (int32_t)rest2_downshift;
            }
        break;
        case MOUSE_SENSOR_ATTR_RUN_DOWNSHIFT_MULT_REG:
            if((uint32_t)chan ==MOUSE_SENSOR_CHAN_RAM_DATA){
                return -EINVAL;
            }else{
                uint8_t run_downshift_mult = 0;
                ret = mouse_sensor_read_rest_reg(dev,Run_DownShift_Mult,&run_downshift_mult);
                if(ret == 0)val->val1 = (int32_t)run_downshift_mult;
            }
        break;
        case MOUSE_SENSOR_ATTR_REST1_DOWNSHIFT_MULT_REG:
            if((uint32_t)chan ==MOUSE_SENSOR_CHAN_RAM_DATA){
                return -EINVAL;
            }else{
                uint8_t rest1_downshift_mult = 0;
                ret = mouse_sensor_read_rest_reg(dev,Rest1_DownShift_Mult,&rest1_downshift_mult);
                if(ret == 0)val->val1 = (int32_t)rest1_downshift_mult;
            }
        break;
        case MOUSE_SENSOR_ATTR_REST2_DOWNSHIFT_MULT_REG:
            if((uint32_t)chan ==MOUSE_SENSOR_CHAN_RAM_DATA){
                return -EINVAL;
            }else{
                uint8_t rest2_downshift_mult = 0;
                ret = mouse_sensor_read_rest_reg(dev,Rest2_DownShift_Mult,&rest2_downshift_mult);
                if(ret == 0)val->val1 = (int32_t)rest2_downshift_mult;
            }
        break;
        case MOUSE_SENSOR_ATTR_REST1_PERIOD_TIME:
            if((uint32_t)chan ==MOUSE_SENSOR_CHAN_RAM_DATA){
                val->val1 = (int32_t)(dev_data->rest1_period_time);
            }else{
                uint16_t rest1_period_time = 0;
                ret = mouse_sensor_read_period_time(dev,Rest1_Period_time,&rest1_period_time);
                if(ret == 0)val->val1 = (int32_t)rest1_period_time;
            }
        break;
        case MOUSE_SENSOR_ATTR_REST2_PERIOD_TIME:
            if((uint32_t)chan ==MOUSE_SENSOR_CHAN_RAM_DATA){
                val->val1 = (int32_t)(dev_data->rest2_period_time);
            }else{
                uint16_t rest2_period_time = 0;
                ret = mouse_sensor_read_period_time(dev,Rest2_Period_time, &rest2_period_time);
                if(ret == 0)val->val1 = (int32_t)rest2_period_time;
        }
        break;
        case MOUSE_SENSOR_ATTR_REST3_PERIOD_TIME:
            if((uint32_t)chan ==MOUSE_SENSOR_CHAN_RAM_DATA){
                val->val1 = (int32_t)(dev_data->rest3_period_time);
            }else{
                uint16_t rest3_period_time = 0;
                ret = mouse_sensor_read_period_time(dev,Rest3_Period_time, &rest3_period_time);
                if(ret == 0)val->val1 = (int32_t)rest3_period_time;
        }
        break;
        case MOUSE_SENSOR_ATTR_RUN_DOWNSHIFT_TIME:
            if((uint32_t)chan ==MOUSE_SENSOR_CHAN_RAM_DATA){
                uint32_t value_ms = dev_data->run_downshift_time;
                val->val1 = (int32_t)(value_ms & 0xFFFF);
                val->val2 = (int32_t)((value_ms>>16)&0xFFFF);
            }else{
                ret = mouse_sensor_read_config_time(dev,Run_DownShift_time, val);
            }
        break;
        case MOUSE_SENSOR_ATTR_REST1_DOWNSHIFT_TIME:
            if((uint32_t)chan == MOUSE_SENSOR_CHAN_RAM_DATA){
                uint32_t value_ms = dev_data->rest1_downshift_time;
                val->val1 = (int32_t)(value_ms & 0xFFFF);
                val->val2 = (int32_t)((value_ms>>16)&0xFFFF);
            }else{
                ret = mouse_sensor_read_config_time(dev,Rest1_DownShift_time, val);
            }
        break;
        case MOUSE_SENSOR_ATTR_REST2_DOWNSHIFT_TIME:
            if((uint32_t)chan ==MOUSE_SENSOR_CHAN_RAM_DATA){
                uint32_t value_ms = dev_data->rest2_downshift_time;
                val->val1 = (int32_t)(value_ms & 0xFFFF);
                val->val2 = (int32_t)((value_ms>>16)&0xFFFF);
            }else{
                ret = mouse_sensor_read_config_time(dev,Rest2_DownShift_time, val);
            }
        break;
        case MOUSE_SENSOR_ATTR_BT_TRIGGER:
            if(dev_data->bt_trigger == false)val->val1 = 0;
            else val->val1 = 1;
        break;
        case MOUSE_SENSOR_ATTR_DEINIT:
            if(mouse_burst_data->init_flag == false)val->val1 = 1;
            else val->val1 = 0;
        break;
        case MOUSE_SENSOR_ATTR_INIT:
            if(mouse_burst_data->init_flag == true)val->val1 = 1;
            else val->val1 = 0;
        break;
        case MOUSE_SENSOR_ATTR_SPI_STATUS:
            ret = mouse_sensor_sensor_get_spi_status(dev,val);
        break;
        default:
        return -ENOTSUP;
    }
    return ret;
}



ATTR_TEXT_IN_TCM static int mouse_sensor_sample_fetch(const struct device *dev, enum sensor_channel chan){
    if(mouse_burst_data->init_flag != true){
        log_mouse_sensor_error("[MOUSE][3395] sensor sample fetch failed, not init\n",0);
        return -EBUSY;
    }
    return mouse_sensor_data_read(dev,chan);
}

static int mouse_sensor_channel_get(const struct device *dev, enum sensor_channel chan,
                               struct sensor_value *val)
{
    if(mouse_burst_data->init_flag != true){
        log_mouse_sensor_error("[MOUSE][3395] sensor channel get failed, not init\n",0);
        return -EBUSY;
    }
    switch (chan) {
        case SENSOR_CHAN_POS_DX:
            val->val1 = (int16_t)(mouse_burst_data->x_low)|(mouse_burst_data->x_high << 8);
            val->val2 = 0;
            break;

        case SENSOR_CHAN_POS_DY:
            val->val1 = (int16_t)(mouse_burst_data->y_low)|(mouse_burst_data->y_high << 8);
            val->val2 = 0;
            break;

        default:
            return -ENOTSUP;
	}
    return 0;
}

static int mouse_sensor_trigger_set(const struct device *dev,
                               const struct sensor_trigger *trig,
                               sensor_trigger_handler_t handler){
    const struct mouse_sensor_config *dev_config = dev->config;
    if(trig->type == SENSOR_TRIG_DATA_READY){
        hal_spi_master_register_callback(dev_config->port_num,mouse_sensor_callback,NULL);
        mouse_burst_data->data_ready_handler = handler;
    }
    return 0;
}

static int mouse_sensor_preinit(void)
{
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K,&(global_init_left_time));
	return 0;
}

static int mouse_sensor_init(const struct device *dev)
{
    const struct mouse_sensor_config *dev_config = dev->config;
    struct mouse_sensor_data *dev_data = dev->data;
    dev_data->lod = dev_config->lod;
    dev_data->cpi = dev_config->cpi;
    dev_data->cpi_x = dev_config->cpi;
    dev_data->cpi_y = dev_config->cpi;
    dev_data->mode = dev_config->mode;
    dev_data->xy_direction = dev_config->xy_direction;
    dev_data->rest_mode = dev_config->rest_mode;
    dev_data->motion_sync = dev_config->motion_sync;
    dev_data->angle_snap = dev_config->angle_snap;
    dev_data->ripple_control = dev_config->ripple_control;
    dev_data->rest1_period_time = dev_config->rest1_period_time;
    dev_data->rest2_period_time = dev_config->rest2_period_time;
    dev_data->rest3_period_time = dev_config->rest3_period_time;
    dev_data->run_downshift_time = 1;
    dev_data->rest1_downshift_time = 20000;
    dev_data->rest2_downshift_time = 570000;
    dev_data->force = true;
	return mouse_sensor_attr_set(dev,SENSOR_CHAN_ALL,MOUSE_SENSOR_ATTR_INIT,NULL);
}
static const struct sensor_driver_api mouse_sensor_driver_api = {
    .attr_set = mouse_sensor_attr_set,
    .attr_get = mouse_sensor_attr_get,
    .trigger_set = mouse_sensor_trigger_set,
    .sample_fetch = mouse_sensor_sample_fetch,
    .channel_get = mouse_sensor_channel_get,
};


#define	PAW3395_PIXART_DEVICE(id)						\
                   \
static struct mouse_sensor_data paw3395_p##id##_data;		\
									\
static const struct mouse_sensor_config paw3395_p##id##_config = {		\
	.frequency = DT_PROP(DT_PARENT(DT_DRV_INST(id)), frequency),		\
    .cs_pin = (DT_PROP_BY_IDX(DT_PARENT(DT_DRV_INST(id)), cs_pin,0)<<AIROHA_PIN_NUM_POS) | \
    (DT_PROP_BY_IDX(DT_PARENT(DT_DRV_INST(id)), cs_pin,1)<<AIROHA_ALT_FUNC_POS),		\
	.port_num = DT_PROP(DT_PARENT(DT_DRV_INST(id)), port),		\
    .lod = DT_ENUM_IDX(DT_DRV_INST(id), lod),	\
    .cpi = DT_PROP(DT_DRV_INST(id), cpi), \
    .mode = DT_ENUM_IDX(DT_DRV_INST(id), mode), \
    .xy_direction = DT_ENUM_IDX(DT_DRV_INST(id), xy_direction), \
    .rest_mode = DT_PROP(DT_DRV_INST(id), rest_mode), \
    .motion_sync = DT_PROP(DT_DRV_INST(id), motion_sync), \
    .angle_snap = DT_PROP(DT_DRV_INST(id), angle_snap), \
    .ripple_control = DT_PROP(DT_DRV_INST(id), ripple_control), \
    .rest1_period_time = DT_PROP(DT_DRV_INST(id), rest1_period_time), \
    .rest2_period_time = DT_PROP(DT_DRV_INST(id), rest2_period_time), \
    .rest3_period_time = DT_PROP(DT_DRV_INST(id), rest3_period_time), \
};									\
									\
DEVICE_DT_INST_DEFINE(id,						\
	    mouse_sensor_init,						\
	    NULL,							\
	    &paw3395_p##id##_data,					\
	    &paw3395_p##id##_config, 					\
	    CONFIG_MOUSE_SENSOR_INIT_LEVEL, CONFIG_MOUSE_SENSOR_INIT_PRIORITY, &mouse_sensor_driver_api);\

SYS_INIT(mouse_sensor_preinit,CONFIG_MOUSE_SENSOR_PREINIT_LEVEL,CONFIG_MOUSE_SENSOR_PREINIT_PRIORITY); \

DT_INST_FOREACH_STATUS_OKAY(PAW3395_PIXART_DEVICE)
