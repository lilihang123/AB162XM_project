/* Copyright Statement:
 *
 * (C) 2021  Airoha Technology Corp. All rights reserved.
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
//#include "ab_printf_hook.h" // include header file for logging new API
#include "hal.h"
#include "hal_eint_internal.h"
#include "hal_platform.h"
#include "air_imu_sensor.h"
#include "air_imu_sensor_internal.h"

#define AIR_IMU_SENSOR_BMA282_ENABLED

#ifdef AIR_IMU_SENSOR_BMA282_ENABLED
#include "air_bma282.h"
#endif
 static uint8_t s_imu_eint_num = 0;

const air_imu_sensor_function_table_t  s_imu_vendor_func_table[IMU_VENDOR_ID_MAX] =
{
/*BMA282 accel sensor function list*/
#ifdef AIR_IMU_SENSOR_BMA282_ENABLED
    {air_bma282_init, air_bma282_deinit, air_bma282_config, air_bma282_get_framecnt, air_bma282_get_data, air_bma282_ioctl, air_bma282_eint_handle},
#else
    {0,0,0,0,0,0,0},
#endif
};


static void air_imu_sensor_eintx_handler(void *user_data)
{
    uint32_t handle = (uint32_t)user_data;
    int vendor = 0;

    vendor = IMU_SENSOR_GET_VENDOR(handle);
    if (vendor >= IMU_VENDOR_ID_MAX) {
        log_imu_error("[imu][sensor] air_imu_sensor_eintx_handler fail: err vendor", 0);
        return;
    }
    s_imu_vendor_func_table[vendor].imu_eint_handle(handle);
    hal_eint_unmask(s_imu_eint_num);
    log_imu_info("[imu][sensor] air_imu_sensor_eintx_handler: triggered", 0);
}

air_imu_sensor_handle_t air_imu_sensor_init(air_imu_sensor_vendor_id_t vendor, air_imu_sensor_init_config_t *config)
{
    uint32_t handle = 0;
    int      ret = 0;

    if (config == NULL || vendor >= IMU_VENDOR_ID_MAX) {
        log_imu_error("[imu][sensor] air_imu_sensor_init: err para", 0);
        return 0;
    }
    /*set handle*/
    IMU_SENSOR_SET_MAGICID(handle,  IMU_SENSOR_MAGIC_ID);
    IMU_SENSOR_SET_VENDOR(handle,   vendor);
    IMU_SENSOR_SET_BUS_TYPE(handle, config->bus_type);
    IMU_SENSOR_SET_BUS_PORT(handle, config->bus_port);
    IMU_SENSOR_SET_EINT_NUM(handle, config->eint_num);

    ret = s_imu_vendor_func_table[vendor].imu_init(handle, config);
    if (ret != 0) {
        log_imu_error("[imu][sensor] air_imu_sensor_init: failed, sensor init error(%d)", 1, (unsigned int) ret);
        return 0;
    }
    if (config->call_back != 0) {
        log_imu_info("[imu][sensor] air_imu_sensor_init: init eint", 0);
        s_imu_eint_num = config->eint_num;
        hal_eint_init(config->eint_num, &config->eint_config);
        hal_eint_enable(config->eint_num);
        hal_eint_register_callback(config->eint_num, air_imu_sensor_eintx_handler, (void *)handle);
        hal_eint_unmask(config->eint_num);
    }
    log_imu_info("[imu][sensor] air_imu_sensor_init: succ: vendor %d, eint num %d", 2, (int)vendor, (int)config->eint_num);
    return (air_imu_sensor_handle_t) handle;
}

int  air_imu_sensor_deinit(air_imu_sensor_handle_t handle)
{
    int vendor = 0;
    int ret = 0;
    uint8_t  magic = 0;

    vendor = IMU_SENSOR_GET_VENDOR(handle);
    magic  = IMU_SENSOR_GET_MAGICID(handle);
    if (vendor >= IMU_VENDOR_ID_MAX || magic != IMU_SENSOR_MAGIC_ID) {
        log_imu_error("[imu][sensor] air_imu_sensor_deinit: err vendor", 0);
        return -1;
    }
    ret = s_imu_vendor_func_table[vendor].imu_deinit(handle);
    return ret;
}

int  air_imu_sensor_config(air_imu_sensor_handle_t handle, air_imu_sensor_config_t *config)
{
    uint8_t  vendor = 0;
    int      ret = 0;
    uint8_t  magic = 0;
    uint8_t  eint_num = 0;

    eint_num = IMU_SENSOR_GET_EINT_NUM(handle);
    vendor = IMU_SENSOR_GET_VENDOR(handle);
    magic  = IMU_SENSOR_GET_MAGICID(handle);
    if (vendor >= IMU_VENDOR_ID_MAX || magic != IMU_SENSOR_MAGIC_ID) {
        log_imu_error("[imu][sensor] air_imu_sensor_config: err handle(%x)\r\n", 1, (unsigned int)handle);
        return -1;
    }
    if (config == NULL) {
        log_imu_error("[imu][sensor] air_imu_sensor_config fail: null para\r\n", 0);
        return -2;
    }
    ret = s_imu_vendor_func_table[vendor].imu_config(handle, config);
    hal_eint_unmask(eint_num);

    return ret;
}

int  air_imu_get_frame_cnt(air_imu_sensor_handle_t handle)
{
    uint8_t  vendor = 0;
    int      ret = 0;
    uint8_t  magic = 0;

    vendor = IMU_SENSOR_GET_VENDOR(handle);
    magic  = IMU_SENSOR_GET_MAGICID(handle);
    if (vendor >= IMU_VENDOR_ID_MAX || magic != IMU_SENSOR_MAGIC_ID) {
        log_imu_error("[imu][sensor] air_imu_get_frame_cnt: err handle(%x)\r\n", 1, (unsigned int)handle);
        return -1;
    }
    ret = s_imu_vendor_func_table[vendor].imu_frame_cnt(handle);

    return ret;
}

int  air_imu_get_data(air_imu_sensor_handle_t handle, air_imu_sensor_frame_data_t *frame_buff, uint32_t frame_buff_sz)
{
    uint8_t  vendor = 0;
    uint8_t  magic = 0;
    int      ret = 0;

    vendor = IMU_SENSOR_GET_VENDOR(handle);
    magic  = IMU_SENSOR_GET_MAGICID(handle);
    if (vendor >= IMU_VENDOR_ID_MAX || magic != IMU_SENSOR_MAGIC_ID) {
        log_imu_error("[imu][sensor] air_imu_get_data: err handle(0x%x)\r\n", 1, (unsigned int)handle);
        return -1;
    }
    if (frame_buff == NULL || frame_buff_sz == 0) {
        log_imu_error("[imu][sensor] air_imu_get_data fail: null para\r\n", 0);
        return -2;
    }

    ret = s_imu_vendor_func_table[vendor].imu_get_data(handle, frame_buff, frame_buff_sz);

    return ret;
}

int  air_imu_sensor_ioctl(air_imu_sensor_handle_t handle, air_imu_sensor_command_t cmd, int parameter)
{
    uint8_t  vendor = 0;
    int      ret = 0;
    uint8_t  magic = 0;

    vendor = IMU_SENSOR_GET_VENDOR(handle);
    magic  = IMU_SENSOR_GET_MAGICID(handle);
    if (vendor >= IMU_VENDOR_ID_MAX || magic != IMU_SENSOR_MAGIC_ID) {
        log_imu_error("[imu][sensor] air_imu_sensor_ioctl: err handle(0x%x)\r\n", 1, (unsigned int)handle);
        return -1;
    }
    ret = s_imu_vendor_func_table[vendor].imu_ioctl(handle, cmd, parameter);

    return ret;
}

