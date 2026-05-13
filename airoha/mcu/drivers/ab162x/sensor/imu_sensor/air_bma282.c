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
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "air_bma282.h"
#include "hal_platform.h"
#include "air_imu_sensor_internal.h"

#define BMA282_DEFAULT_SUSPEND_MODE

static uint8_t    s_i2c_devaddr = 0;
static float      s_imu_accl_coef = 0;
static uint8_t    s_det_succ = 0;
static uint8_t    s_i2c_port = 0;
static uint8_t    s_init_st = 0;
static air_imu_sensor_accel_range_t s_accl_range = 0;
static air_imu_sensor_callback_t    s_call_back; 
static void                        *s_user_data = 0;

static int air_i2c_bus_init(uint8_t port, hal_i2c_config_t *pconfig)
{
    hal_i2c_config_t config;
    hal_i2c_status_t status = 0;

    s_i2c_port = port;
    hal_i2c_master_deinit(s_i2c_port);
    config.frequency = HAL_I2C_FREQUENCY_400K;
    status = hal_i2c_master_init(s_i2c_port, &config);
    return status;
}

static int air_i2c_bus_deinit()
{
    hal_i2c_master_deinit(s_i2c_port);
    return 0;
}

static int air_register_read(uint8_t addr, uint8_t *data_m, uint8_t len)
{
    hal_i2c_send_to_receive_config_t snd_rcv_config;
    hal_i2c_status_t status = 0;

    snd_rcv_config.receive_buffer = data_m;
    snd_rcv_config.receive_length = len;
    snd_rcv_config.send_data = &addr;
    snd_rcv_config.send_length = 1;
    snd_rcv_config.slave_address = s_i2c_devaddr;
    status = hal_i2c_master_send_to_receive_polling(s_i2c_port, &snd_rcv_config);
    if (status != 0) {
        log_imu_error("[imu][bma282] air_register_read error:%d\r\n", 1, status);
    }
    return status;
}

static int air_register_write(uint8_t addr, uint8_t data_m)
{
    uint8_t data[2];
    hal_i2c_status_t status = 0;

    data[0] = addr;
    data[1] = data_m;

    status = hal_i2c_master_send_polling(s_i2c_port, s_i2c_devaddr, data, 2);
    if (status != 0) {
        log_imu_error("[imu][bma282] air_register_write error:%d\r\n", 1, status);
    }
    return status; 
}

static int air_register_mask_write(uint8_t addr,uint8_t mask,uint8_t data)
{
    int res =0;
    uint8_t tmp_data;

    res = air_register_read(addr, (uint8_t *)&tmp_data, 1);
    if(res){
        return res;
    }
    tmp_data &=~mask;
    tmp_data |= (data & mask);
    res = air_register_write(addr, tmp_data);
    return res;
}


static void air_dump_register()
{
    uint8_t i, data_r[32];

    log_imu_info("------------------Dump Start---------------------\r\n", 0);
    int colum = 4;
    for(i = 0; i < 0x40; ) {
        air_register_read(i, (uint8_t *)&data_r, colum);
        log_imu_info("[%02X-%02X] : %02X %02X %02X %02X", 6, i, (i + colum -1) , data_r[i], data_r[i + 1], data_r[i + 2], data_r[i + 3]);
        i += colum;
    }
    log_imu_info("------------------Dump End-----------------------\r\n", 0);
}

static int bma282_convert_odr(air_imu_sensor_output_data_rate_t  odr)
{
    int res = 0;
    switch(odr) {
        case AIR_IMU_SENSOR_ODR_16HZ:  res =  9; break;
        case AIR_IMU_SENSOR_ODR_32HZ:  res = 10; break;
        case AIR_IMU_SENSOR_ODR_64HZ:  res = 11; break;
        case AIR_IMU_SENSOR_ODR_125HZ: res = 12; break;
        case AIR_IMU_SENSOR_ODR_250HZ: res = 13; break;
        case AIR_IMU_SENSOR_ODR_500HZ: res = 14; break;
        default: odr = 0;
    }
    return res;
}

/////////////////////////////////////////////Public API /////////////////////////////////////////////////////////////

air_imu_sensor_handle_t  air_bma282_init(air_imu_sensor_handle_t handle, air_imu_sensor_init_config_t *config)
{
    int i =0, j = 0;
    uint8_t chipid = 0;
    uint8_t port = 0;
    uint8_t device_addrs[] = DEV_ADDRESS_LIST;

    s_call_back = config->call_back;
    s_user_data = config->user_data; 
    port = IMU_SENSOR_GET_BUS_PORT(handle);
    if (s_init_st == 0) {
        air_i2c_bus_init(port, &config->bus_config.i2c_config);
        s_init_st = 1;
    }

    /* detect sensor device */
    for (j = 0; j < sizeof(device_addrs); j++) {
        s_i2c_devaddr = device_addrs[j];
        for ( i = 0; i < 3; i++) {
            air_register_read(BMA282_REG_CHIP_ID, (uint8_t *) &chipid, 1);
            if (chipid == DEV_CHIP_ID) {
                s_det_succ = 1;
                break;
            }
        }
        if (s_det_succ == 1) {
            break;
        }
    }

    /* reset imu sensor & config INT signal latch time*/
    if (s_det_succ == 1) {
        // reset imu sensor
        air_register_write(BMA282_REG_SOFTRESET, 0xB6);
        log_imu_info("[imu][bma282] detect sensor succ, dev addr:%x, chip id: %x\r\n", s_i2c_devaddr, chipid);
        hal_gpt_delay_ms(80);

        /*config INT latch 250us*/
        air_register_mask_write(BMA282_REG_INT_RST_LATCH, 0x0F, 0x09);
    } else {
        log_imu_error("[imu][bma282] detect sensor fail, chip id is %x\r\n", data_m); 
    }
    if (s_det_succ == 1) {
        return 0;
    } else {
        return -1;
    }
}




int air_bma282_config(air_imu_sensor_handle_t handle, air_imu_sensor_config_t *config)
{
    int res = 0;
    uint8_t pwr_mode = IMU_SENSOR_POWER_MODE_SUSPEND;
    uint8_t temp = 0;

    if (config->enable_bits & AIR_IMU_SENSOR_ACCEL_ENABLE) {
        
        s_accl_range = config->accel_range;
        switch(s_accl_range) {
            case AIR_IMU_SENSOR_ACCEL_RANGE_2G:  temp = 3;  s_imu_accl_coef = 0.224f;break;
            case AIR_IMU_SENSOR_ACCEL_RANGE_4G:  temp = 5;  s_imu_accl_coef = 0.488f;break;
            case AIR_IMU_SENSOR_ACCEL_RANGE_8G:  temp = 8;  s_imu_accl_coef = 0.977f;break;
            case AIR_IMU_SENSOR_ACCEL_RANGE_16G: temp = 12; s_imu_accl_coef = 1.953f;break;
            default: temp = 3; break;
        }
        /*config accel range*/
        res |= air_register_write(BMA282_REG_PMU_RANGE, temp);

        /*config accel bw*/
        temp = bma282_convert_odr(config->sensor_odr); /*filer bandwidth:62.5Hz */
        res |= air_register_write(BMA282_REG_PMU_BW, temp);

#ifdef BMA282_DEFAULT_SUSPEND_MODE
        /*config sensor power mode to suspend*/
        temp = (0x1 << 7);
        res |= air_register_write(BMA282_REG_PMU_LPW, temp);
#endif
        /* config sensor output data rate */
        if (config->sensor_odr < AIR_IMU_SENSOR_ODR_8HZ) {
            return -1;
        }
        temp = (config->sensor_odr - AIR_IMU_SENSOR_ODR_8HZ) + 8;
        res |= air_register_write(BMA282_REG_PMU_BW, temp);

        /* config INT PIN control */
        temp = (0x1 << 2) | 0x1; /*pushpull, active high*/
        res |= air_register_write(BMA282_REG_INT_OUT_CTRL, temp);

        temp = (0x1 << 6); /* enable orient detect*/
        res |= air_register_write(BMA282_REG_INT_EN_0, temp);

        temp = (0x1 << 6); /* map orient detect to int1*/
        res |= air_register_write(BMA282_REG_INT_MAP_0, temp);

        temp = (0x1 << 6) | 8;/* gen orien irq & set orient angle(0~44)*/
        res |= air_register_write(BMA282_REG_INT_11, temp);

        /*config fifo */
        temp = (0x00 << 5) | (0x00); /*fifo_mode(bit5~6):0x0 bypass fifo,0x2 stream; fifo_data(bit0~1):0x0 xyz*/
        res |= air_register_write(BMA282_REG_FIFO_CONFIG_1, temp);
    } else {
        pwr_mode = IMU_SENSOR_POWER_MODE_SUSPEND;
        /* enter suspend mode */
        temp = (0x1 << 7);
        res |= air_register_write(BMA282_REG_PMU_LPW, temp);
    }

    air_dump_register();

    hal_gpt_delay_ms(50);
    return res;
}


int air_bma282_get_framecnt(air_imu_sensor_handle_t handle)
{
    uint8_t r_data = 0;
 
    air_register_read(BMA282_REG_FIFO_STATUS, (uint8_t *)&r_data, 1);
    return (r_data & 0x3F);
}

int air_bma282_get_data(air_imu_sensor_handle_t handle, air_imu_sensor_frame_data_t *frame_buff, uint32_t frame_buff_sz)
{
    uint8_t r_data[6] = {0};
    int temp = 0;
    int sign = 1;
    air_register_read(BMA282_REG_ACC_X_LSB, (uint8_t *)r_data, 6);
    if (r_data[0] & 0x1) {
        sign = (r_data[1] & 0x80)?(0xFFFFE000):(0);
        temp = (r_data[0] & 0xFF) >> 2; 
        temp |= ((r_data[1] & 0x7F) << 6);
        temp |= sign;
        frame_buff[0].accel_data.x = temp * s_imu_accl_coef;

        sign = (r_data[3] & 0x80)?(0xFFFFE000):(0);
        temp = (r_data[2] & 0xFF) >> 2; 
        temp |= ((r_data[3] & 0x7F) << 6);
        temp |= sign;
        frame_buff[0].accel_data.y = temp * s_imu_accl_coef;

        sign = (r_data[5] & 0x80)?(0xFFFFE000):(0);
        temp = (r_data[4] & 0xFF) >> 2; 
        temp |= ((r_data[5] & 0x7F) << 6);
        temp |= sign;
        frame_buff[0].accel_data.z = temp * s_imu_accl_coef;
        return 1;
    } else {
        return 0;
    }
}


int  air_bma282_ioctl(air_imu_sensor_handle_t handle, air_imu_sensor_command_t command, int parameter)
{
    int result = 0;
    uint8_t w_data = 0;

    switch(command) {
        case IMU_SENSOR_CMD_SET_POWER_MODE: {

            air_register_read(BMA282_REG_PMU_LPW, (uint8_t *)&w_data, 1);
            w_data &= ~(0xE0);
            switch (parameter) {
                case IMU_SENSOR_POWER_MODE_NORMAL:
                    w_data = (0 << 5);
                    break;
                case IMU_SENSOR_POWER_MODE_LOWPOWER:
                    w_data = (2 << 5);
                    break;
                case IMU_SENSOR_POWER_MODE_SUSPEND:
                    w_data = (4 << 5);
                    break;
                default: return 0;
            }
            air_register_write(BMA282_REG_PMU_LPW, w_data);
            hal_gpt_delay_ms(50);
            log_imu_info("[imu][bma282] air_bma282_ioctl: set power mode to %d\r\n", 1, (parameter & 0x3));
        } break;

        case IMU_SENSOR_CMD_SET_ACTIVE_THRE: {
            uint8_t w_data = (0x1 << 6) | (parameter & 0x3F);/* gen orien irq & set orient angle(0~44)*/
            air_register_write(BMA282_REG_INT_11, w_data);
            log_imu_info("[imu][bma282] air_bma282_ioctl: set active threshold to %d\r\n", 1, (parameter & 0xff));
        } break;

        case  IMU_SENSOR_CMD_SET_ACTIVE_DUR: {
            //air_register_write(NSA_REG_ACTIVE_DURATION, (parameter & 0xF));
            log_imu_info("[imu][bma282] air_bma282_ioctl: set active dur to %d\r\n", 1, (parameter & 0x3));
        } break;
        case IMU_SENSOR_CMD_DUMP_REGISTER:{
            air_dump_register(parameter);
        } break;

        case IMU_SENSOR_CMD_READ_REGISTER: {
            uint8_t reg_val = 0;
            air_register_read((parameter & 0xFF), (uint8_t *)&reg_val, 1);
            result = reg_val;
        } break;
        case IMU_SENSOR_CMD_ENABLE_INT2:{
            if (parameter) {
                w_data = (0x1 << 6); /* enable map orient detect to int2*/
                air_register_write(BMA282_REG_INT_MAP_2, w_data);
            } else {
                w_data = 0;          /* disable map orient detect to int2*/
                air_register_write(BMA282_REG_INT_MAP_2, w_data);
            }

        } break;
    }
    return result;
}

int  air_bma282_deinit(air_imu_sensor_handle_t handle)
{
    if(s_init_st == 1) {
        /* disable accel */
        /* enter deep suspend mode */
        uint8_t w_data = 0x1 << 5;
        air_register_write(BMA282_REG_PMU_LPW, w_data);
        air_i2c_bus_deinit();
    }
    s_init_st = 0;
    return 0;
}

int air_bma282_eint_handle(air_imu_sensor_handle_t handle)
{
    if(s_call_back != NULL) {
        s_call_back(handle, IMU_SENSOR_EVENT_ACTIVE_INTERRUPT, 0, s_user_data);
    }
    return 0;
}
