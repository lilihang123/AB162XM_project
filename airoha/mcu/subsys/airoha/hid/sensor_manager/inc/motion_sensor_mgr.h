/* Copyright Statement:
 *
 * (C) 2024  Airoha Technology Corp. All rights reserved.
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
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
 * RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
 * TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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
 
#if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE)
#ifndef __MOTION_SENSOR_MGR_H__
#define __MOTION_SENSOR_MGR_H__

#include <zephyr/drivers/gpio.h>

#define MAX_DPI_COUNT 5
#define MOUSE_MOTION_INT 18

typedef enum{
    SENSOR_LOD,
    SENSOR_MOTION_SYNC,
    SENSOR_ANGLE_SNAP,
    SENSOR_RIPPLE_CONTROL,
}T_MOTION_ATTRIBUTE_E;

typedef struct {
    uint8_t dpi_loop_stage_range;           /* 1 ~ MAX_DPI_COUNT */
    uint8_t dpi_curr_idx;                   /* 0 ~ MAX_DPI_COUNT-1 */
    #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
    uint16_t x_dpi_settings[MAX_DPI_COUNT];
    uint16_t y_dpi_settings[MAX_DPI_COUNT];
    #else
    uint16_t dpi_settings[MAX_DPI_COUNT];
    #endif
}T_DPI_CONFIG_S;

typedef struct {
    uint8_t dpi_idx;
    #if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
    uint16_t x_dpi_value;
    uint16_t y_dpi_value;
    #else
    uint16_t dpi_value;
    #endif
}T_DPI_STATUS_S;

typedef void (* msmgr_motion_isr_callback)(const struct device *dev, struct gpio_callback *cb, gpio_port_pins_t pins);

void msmgr_dpi_config_init(const T_DPI_CONFIG_S *dpi_cfg, uint8_t profile_idx, uint16_t report_rate, uint8_t link_mode);
void msmgr_init(msmgr_motion_isr_callback motion_pin_isr_cb);
void msmgr_clear_sensor_data();
void msmgr_bt_trigger_enable();
void msmgr_keep_high_fps(bool enable);
void msmgr_mode_setting(uint8_t link_mode, uint16_t report_rate);
void msmgr_downshift_time_config(uint32_t rest1_downshift_time, uint32_t rest2_downshift_time);
void msmgr_motion_sync_config(uint8_t link_mode, uint16_t report_rate);
void msmgr_motion_isr_disable();
void msmgr_enter_low_power_set_wakeup();
void msmgr_exit_low_power();
uint32_t msmgr_motion_pin_mask();

void msmgr_off_mode();      // Power Consumption : 0. power cut
void msmgr_parking_mode(msmgr_motion_isr_callback motion_pin_isr_cb);  // Power Consumption : very low. Motion wake up only
void msmgr_rest_mode();     // Power Consumption : low. Rest mode
void msmgr_standby_mode();     // Power Consumption : low. Rest mode
void msmgr_driving_mode(uint8_t mode, uint16_t report_rate);  // Power Consumption : high. working
void msmgr_get_sensor_attr();
void msmgr_print_sensor_ram_attr();
void msmgr_reinit();


#if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
void msmgr_dpi_change(uint8_t type, uint16_t x_value, uint16_t y_value);
uint8_t msmgr_get_dpi_value(uint8_t *loop_stage_range, uint8_t *curr_idx, uint16_t *x_dpi_value_array, uint16_t *y_dpi_value_array);
uint8_t msmgr_set_dpi_value(uint8_t idx, uint16_t x_dpi_value, uint16_t y_dpi_value);
#else
void msmgr_dpi_change(uint8_t type, uint16_t value);
uint8_t msmgr_get_dpi_value(uint8_t *loop_stage_range, uint8_t *curr_idx, uint16_t *dpi_value_array);
uint8_t msmgr_set_dpi_value(uint8_t idx, uint16_t dpi_value);
#endif

uint8_t msmgr_set_current_dpi(uint8_t idx);
uint8_t msmgr_set_dpi_stage_range(uint8_t stage_range);
uint8_t msmgr_set_attr_config(T_MOTION_ATTRIBUTE_E attr_type, uint8_t attr_value, uint8_t link_mode, uint16_t report_rate);
uint8_t msmgr_get_attr_config(T_MOTION_ATTRIBUTE_E attr_type);
uint8_t msmgr_reload_sensor_attr(uint8_t profile_idx, bool restore, uint16_t report_rate, uint8_t link_mode);
void msmgr_get_current_dpi_status(T_DPI_STATUS_S* ret_cfg);

#if defined(CONFIG_AIR_DPI_SWITCH_FROM_DEFAULT)
uint8_t msmgr_get_shortcut_dpi_default_stage();
uint8_t msmgr_set_shortcut_dpi_default_stage(uint8_t stage);
#endif
#endif
#endif
