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
#ifndef __AIR_IMU_SENSOR_INTERNAL_H__
#define __AIR_IMU_SENSOR_INTERNAL_H__
#include <stdint.h>
#include "hal.h"
#include "hal_platform.h"
#include "air_imu_sensor.h"

#define log_imu_info(_message, cnt, ...)    log_hal_msgid_info("[sensor][nfc] " _message,cnt,    ##__VA_ARGS__)
#define log_imu_warn(_message, cnt, ...)    log_hal_msgid_warning("[sensor][nfc] " _message,cnt, ##__VA_ARGS__)
#define log_imu_error(_message,cnt, ...)    log_hal_msgid_error("[sensor][nfc] " _message,cnt,   ##__VA_ARGS__)

#define        IMU_SENSOR_MAGIC_ID              0x47
#define        IMU_SENSOR_MAGICID_OFS           24
#define        IMU_SENSOR_BUS_TYPE_OFS          20
#define        IMU_SENSOR_BUS_PORT_OFS          16
#define        IMU_SENSOR_VENDOR_OFS            12
#define        IMU_SENSOR_USER_ID_OFS           8
#define        IMU_SENSOR_EINT_NUM_OFS          0

#define        IMU_SENSOR_GET_MAGICID(handle)           ((handle >> IMU_SENSOR_MAGICID_OFS)  & 0xFF)
#define        IMU_SENSOR_GET_BUS_TYPE(handle)          ((handle >> IMU_SENSOR_BUS_TYPE_OFS) & 0xF)
#define        IMU_SENSOR_GET_BUS_PORT(handle)          ((handle >> IMU_SENSOR_BUS_PORT_OFS) & 0xF)
#define        IMU_SENSOR_GET_VENDOR(handle)            ((handle >> IMU_SENSOR_VENDOR_OFS)   & 0xF)
#define        IMU_SENSOR_GET_USER_ID(handle)           ((handle >> IMU_SENSOR_USER_ID_OFS)  & 0xF)
#define        IMU_SENSOR_GET_EINT_NUM(handle)          ((handle >> IMU_SENSOR_EINT_NUM_OFS)  & 0xFF)

#define        IMU_SENSOR_SET_MAGICID(handle, type)     (handle |= ((type   & 0xFF) << IMU_SENSOR_MAGICID_OFS))
#define        IMU_SENSOR_SET_BUS_TYPE(handle, type)    (handle |= ((type   & 0xF) << IMU_SENSOR_BUS_TYPE_OFS))
#define        IMU_SENSOR_SET_BUS_PORT(handle, port)    (handle |= ((port   & 0xF) << IMU_SENSOR_BUS_PORT_OFS))
#define        IMU_SENSOR_SET_VENDOR(handle, vendor)    (handle |= ((vendor & 0xF) << IMU_SENSOR_VENDOR_OFS))
#define        IMU_SENSOR_SET_USER_ID(handle, user)     (handle |= ((user   & 0xF) << IMU_SENSOR_USER_ID_OFS))
#define        IMU_SENSOR_SET_EINT_NUM(handle, user)    (handle |= ((user   & 0xFF) << IMU_SENSOR_EINT_NUM_OFS))



typedef air_imu_sensor_handle_t (*func_imu_init_t)(air_imu_sensor_handle_t handle, air_imu_sensor_init_config_t *config);
typedef int (*func_imu_deinit_t)(air_imu_sensor_handle_t handle);
typedef int (*func_imu_config_t)(air_imu_sensor_handle_t handle, air_imu_sensor_config_t *config);
typedef int (*func_imu_get_frame_cnt_t)(air_imu_sensor_handle_t handle);
typedef int (*func_imu_get_data_t)(air_imu_sensor_handle_t handle, air_imu_sensor_frame_data_t *frame_buff, uint32_t frame_buff_sz);
typedef int (*func_imu_ioctl_t)(air_imu_sensor_handle_t handle, air_imu_sensor_command_t cmd, int parameter);
typedef int (*func_imu_eint_t)(air_imu_sensor_handle_t handle);
typedef struct {
    func_imu_init_t             imu_init;
    func_imu_deinit_t           imu_deinit;
    func_imu_config_t           imu_config;
    func_imu_get_frame_cnt_t    imu_frame_cnt;
    func_imu_get_data_t         imu_get_data;
    func_imu_ioctl_t            imu_ioctl;
    func_imu_eint_t             imu_eint_handle;
} air_imu_sensor_function_table_t;


#endif