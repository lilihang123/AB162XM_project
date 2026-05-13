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
#ifndef _AIR_BMA282_H_
#define _AIR_BMA282_H_
#include "air_imu_sensor.h"

#define DEV_CHIP_ID             (0xFB)
#define DEV_ADDRESS_LIST        {0x18, 0x19}

typedef enum {
    BMA282_REG_CHIP_ID      = 0x00,
    BMA282_REG_ACC_X_LSB    = 0x02,
    BMA282_REG_ACC_X_MSB    = 0x03,
    BMA282_REG_ACC_Y_LSB    = 0x04,
    BMA282_REG_ACC_Y_MSB    = 0x05,
    BMA282_REG_ACC_Z_LSB    = 0x06,
    BMA282_REG_ACC_Z_MSB    = 0x07,
    BMA282_REG_TEMPERATURE  = 0x08,
    BMA282_REG_INT_STATUS_0 = 0x09,
    BMA282_REG_INT_STATUS_1 = 0x0A,
    BMA282_REG_INT_STATUS_2 = 0x0B,
    BMA282_REG_INT_STATUS_3 = 0x0C,
    BMA282_REG_FIFO_STATUS  = 0x0E,
    BMA282_REG_PMU_RANGE    = 0x0F,
    BMA282_REG_PMU_BW       = 0x10,
    BMA282_REG_PMU_LPW      = 0x11,
    BMA282_REG_PMU_LOWPOWER = 0x12,
    BMA282_REG_ACC_HBW      = 0x13,
    BMA282_REG_SOFTRESET    = 0x14,
    BMA282_REG_INT_EN_0     = 0x16,
    BMA282_REG_INT_EN_1     = 0x17,
    BMA282_REG_INT_EN_2     = 0x18,
    BMA282_REG_INT_MAP_0    = 0x19,
    BMA282_REG_INT_MAP_1    = 0x1A,
    BMA282_REG_INT_MAP_2    = 0x1B,
    BMA282_REG_INT_SRC      = 0x1E,
    BMA282_REG_INT_OUT_CTRL = 0x20,
    BMA282_REG_INT_RST_LATCH= 0x21,
    BMA282_REG_INT_0        = 0x22,
    BMA282_REG_INT_1        = 0x23,
    BMA282_REG_INT_2        = 0x24,
    BMA282_REG_INT_3        = 0x25,
    BMA282_REG_INT_4        = 0x26,
    BMA282_REG_INT_5        = 0x27,
    BMA282_REG_INT_6        = 0x28,
    BMA282_REG_INT_7        = 0x29,
    BMA282_REG_INT_8        = 0x2A,
    BMA282_REG_INT_9        = 0x2B,
    BMA282_REG_INT_10       = 0x2C,
    BMA282_REG_INT_11       = 0x2D,
    BMA282_REG_INT_12       = 0x2E,
    BMA282_REG_INT_13       = 0x2F,
    BMA282_REG_FIFO_CONFIG_0= 0x30,
    BMA282_REG_SELF_TEST    = 0x32,
    BMA282_REG_TRG_NVM_CTRL = 0x33,
    BMA282_REG_BGW_SPI3_WDT = 0x34,
    BMA282_REG_OFC_CTRL     = 0x36,
    BMA282_REG_OFC_SETTING  = 0x37,
    BMA282_REG_OFC_OFFSET_X = 0x38,
    BMA282_REG_OFC_OFFSET_Y = 0x39,
    BMA282_REG_OFC_OFFSET_Z = 0x3A,
    BMA282_REG_TRIM_GP0     = 0x3B,
    BMA282_REG_TRIM_GP1     = 0x3C,
    BMA282_REG_FIFO_CONFIG_1= 0x3E,
    BMA282_REG_FIFO_DATA    = 0x3F
} bma282_reg_t;

int air_bma282_eint_handle(air_imu_sensor_handle_t handle);
air_imu_sensor_handle_t  air_bma282_init(air_imu_sensor_handle_t handle, air_imu_sensor_init_config_t *config);
int air_bma282_deinit(air_imu_sensor_handle_t handle);
int air_bma282_config(air_imu_sensor_handle_t handle, air_imu_sensor_config_t *config);
int air_bma282_get_framecnt(air_imu_sensor_handle_t handle);
int air_bma282_ioctl(air_imu_sensor_handle_t handle, air_imu_sensor_command_t command, int parameter);
int air_bma282_get_data(air_imu_sensor_handle_t handle, air_imu_sensor_frame_data_t *frame_buff, uint32_t frame_buff_sz);


#endif