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

#ifndef _AIR_IMU_SENSOR_H_
#define _AIR_IMU_SENSOR_H_
#include "hal_i2c_master.h"
#include "hal_spi_master.h"
#include "hal_platform.h"
#include "hal_eint.h"


typedef enum {
    IMU_VENDOR_ID_BMA282 = 0,
    IMU_VENDOR_ID_MAX
} air_imu_sensor_vendor_id_t;

typedef   uint32_t air_imu_sensor_handle_t;

typedef enum {
    IMU_SENSOR_EVENT_DATA_READY = 0,
    IMU_SENSOR_EVENT_ACTIVE_INTERRUPT,
} air_imu_sensor_event_t;

/** @brief This defines the callback function prototype. */
typedef void (*air_imu_sensor_callback_t)(uint32_t handle, air_imu_sensor_event_t event, uint32_t parameter,void *user_data);

/** @brief This enum defines the axis sensor bus type. */
typedef enum {
    AIR_IMU_SENSOR_BUS_TYPE_I2C = 0,    /**< use I2C bus to communicate with sensor*/
    AIR_IMU_SENSOR_BUS_TYPE_SPI,        /**< use SPI bus to communicate with sensor*/
    AIR_IMU_SENSOR_BUS_TYPE_MAX         /**< the maximum value of bus type.*/
} air_imu_sensor_bus_type_t;


/** @brief This union defines the bus configurations*/
typedef union {
#ifdef HAL_I2C_MASTER_MODULE_ENABLED
    hal_i2c_config_t             i2c_config;    /**< I2C configurations*/
#endif
#ifdef HAL_SPI_MASTER_MODULE_ENABLED
    hal_spi_master_config_t      spi_config;    /**< SPI configurations*/
#endif
} air_imu_sensor_bus_config_t;


typedef struct {
    air_imu_sensor_bus_type_t           bus_type;       /**< bus type of sensor */
    uint8_t                             bus_port;       /**< bus port number */
    air_imu_sensor_bus_config_t         bus_config;     /**< bus configuration */
    hal_gpio_pin_t                      eint_num;       /**< interrupt pin number */
    hal_eint_config_t                   eint_config;     /**< interrupt configuration */
    air_imu_sensor_callback_t           call_back;      /**< callback function to be called when interrupt occurs */
    void                                *user_data;     /**< user data to be passed to callback */
} air_imu_sensor_init_config_t;

/** @brief This enum defines the axis sensor output data rate. */
typedef enum {
    AIR_IMU_SENSOR_ODR_1HZ = 0,     /**<multi axis band width config output data rate with 1hz*/
    AIR_IMU_SENSOR_ODR_2HZ,         /**<multi axis band width config output data rate with 2hz*/
    AIR_IMU_SENSOR_ODR_4HZ,         /**<multi axis band width config output data rate with 4hz*/
    AIR_IMU_SENSOR_ODR_8HZ,         /**<multi axis band width config output data rate with 8hz*/
    AIR_IMU_SENSOR_ODR_16HZ,        /**<multi axis band width config output data rate with 16hz*/
    AIR_IMU_SENSOR_ODR_32HZ,        /**<multi axis band width config output data rate with 32hz*/
    AIR_IMU_SENSOR_ODR_64HZ,        /**<multi axis band width config output data rate with 64hz*/
    AIR_IMU_SENSOR_ODR_125HZ,       /**<multi axis band width config output data rate with 125hz*/
    AIR_IMU_SENSOR_ODR_250HZ,       /**<multi axis band width config output data rate with 250hz*/
    AIR_IMU_SENSOR_ODR_500HZ,       /**<multi axis band width config output data rate with 500hz*/
    AIR_IMU_SENSOR_ODR_1000HZ,      /**<multi axis band width config output data rate with 1000hz*/
} air_imu_sensor_output_data_rate_t;

/** @brief This enum defines the accel axis sensor range. */
typedef enum {
    AIR_IMU_SENSOR_ACCEL_RANGE_2G = 0,          /**<multi axis accelerator range config 2G*/
    AIR_IMU_SENSOR_ACCEL_RANGE_4G,              /**<multi axis accelerator range config 4G*/
    AIR_IMU_SENSOR_ACCEL_RANGE_8G,              /**<multi axis accelerator range config 8G*/
    AIR_IMU_SENSOR_ACCEL_RANGE_16G,             /**<multi axis accelerator range config 16G*/
} air_imu_sensor_accel_range_t;

/** @brief This enum defines the gyro axis sensor range. */
typedef enum {
    AIR_IMU_SENSOR_GYRO_RANGE_2000_DEG_SEC = 0,    /**<multi axis gyro range config 2000D*/
    AIR_IMU_SENSOR_GYRO_RANGE_1000_DEG_SEC,        /**<multi axis gyro range config 1000D*/
    AIR_IMU_SENSOR_GYRO_RANGE_500_DEG_SEC,         /**<multi axis gyro range config 500D*/
    AIR_IMU_SENSOR_GYRO_RANGE_250_DEG_SEC,         /**<multi axis gyro range config 250D*/
    AIR_IMU_SENSOR_GYRO_RANGE_125_DEG_SEC,         /**<multi axis gyro range config 125D*/
} air_imu_sensor_gyro_range_t;

/** @brief This enum defines the axis sensor type. */
typedef enum {
    AIR_IMU_SENSOR_ACCEL_ENABLE = 1,         /**< enable accel sensor */
    AIR_IMU_SENSOR_GYRO_ENABLE  = 2,    /**< enable gyro sensor */
    AIR_IMU_SENSOR_MAG_ENABLE   = 4,    /**< enable mag sensor */
    AIR_IMU_SENSOR_DISABLE_ALL  = 0,    /**< disable all sensors */
} air_imu_sensor_enable_t;


typedef struct {
    air_imu_sensor_enable_t             enable_bits;
    air_imu_sensor_accel_range_t        accel_range;
    air_imu_sensor_gyro_range_t         gyro_range;
    air_imu_sensor_output_data_rate_t   sensor_odr;
    int                                 frame_threshold;
} air_imu_sensor_config_t;


typedef struct {
    int x;
    int y;
    int z;
} air_imu_sensor_data_item_t;


typedef struct {
    float system_time;
    float sensor_time;
    float temperature;
    air_imu_sensor_data_item_t  accel_data;
    air_imu_sensor_data_item_t  gyro_data;
} air_imu_sensor_frame_data_t;



typedef  enum {
  IMU_SENSOR_POWER_MODE_NORMAL = 0,
  IMU_SENSOR_POWER_MODE_LOWPOWER,
  IMU_SENSOR_POWER_MODE_SUSPEND,
} air_imu_sensor_power_mode_t;

typedef enum {
  IMU_SENSOR_CMD_SET_POWER_MODE = 0,
  IMU_SENSOR_CMD_SET_ACTIVE_THRE,
  IMU_SENSOR_CMD_SET_ACTIVE_DUR,
  IMU_SENSOR_CMD_DUMP_REGISTER,
  IMU_SENSOR_CMD_READ_REGISTER,
  IMU_SENSOR_CMD_ENABLE_INT2
} air_imu_sensor_command_t;



air_imu_sensor_handle_t air_imu_sensor_init(air_imu_sensor_vendor_id_t vendor, air_imu_sensor_init_config_t *config);

int  air_imu_sensor_deinit(air_imu_sensor_handle_t handle);

int  air_imu_sensor_config(air_imu_sensor_handle_t handle, air_imu_sensor_config_t *config);

int  air_imu_get_frame_cnt(air_imu_sensor_handle_t handle);

int  air_imu_get_data(air_imu_sensor_handle_t handle, air_imu_sensor_frame_data_t *frame_buff, uint32_t frame_buff_sz);

int  air_imu_sensor_ioctl(air_imu_sensor_handle_t handle, air_imu_sensor_command_t cmd, int parameter);




#endif

