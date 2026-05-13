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

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)

/* Includes ------------------------------------------------------------------*/
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/drivers/sensor.h>
#include "air_usb.h"
#include "air_usb_hid.h"
// #include "hal_gpt.h"
// #include "hal_gpt_internal.h"
#include "hal_ccni.h"
#include "hal_ccni_config.h"
#include "hal_usb.h"
#include "hal_usb_internal.h"
#include "hal_gpio.h"
#include "hal_eint_internal.h"
#include "hal_gpio_internal.h"
#include "hal_dvfs.h"
#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)
#include "custom_protocol.h"
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE) */
#include "memory_attribute.h"
#include "hid_common.h"
#include "hal_spi_master.h"
#include "hal_gpio.h"
#include "hid_game_controller.h"
#include "hid_scenario_USB_mode.h"
#include "hal_gpt.h"
#include <math.h>
#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#include "key_remap_backend.h"
#endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */

/* Private define ------------------------------------------------------------*/
#define thisMODULE  Game_Controller
#define thisMOD    "Game_Controller"
LOG_MODULE_REGISTER(thisMODULE);

// #define TRIGGER_DEBUG
// #define TRIGGER_AVERAGE_SMOOTHING
#define TRIGGER_AVERAGE_SMOOTHING_CNT 16

#define JOYSTICK_FAKE_DATA_NUMBER 8000
#define PI 3.14159265358979323846

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ATTR_ALIGN(16) uint8_t spi_dummy_write_reg = 0xff;
ATTR_ALIGN(16) uint8_t spi_dummy_read_reg = 0xff;
joystick_adc_parameter_t joystick_calibration[GAME_CONTROLLER_JOYSTICK_NUM_MAX];
trigger_adc_parameter_t trigger_calibration[GAME_CONTROLLER_TRIGGER_NUM_MAX];
hid_game_controller_report_callback hid_game_controller_usb_cb = NULL;
bool game_controller_fake_data_enable;
uint8_t game_controller_fake_data_pattern;
uint8_t game_controller_fake_data_rounds;
uint16_t game_controller_fake_data_joystick_idx;
uint16_t game_controller_fake_data_trigger_idx;
uint32_t game_controlle_expand_button;
#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
uint8_t left_sensitivity = 100;
uint8_t right_sensitivity = 100;
#endif
#if defined(TRIGGER_AVERAGE_SMOOTHING)
uint8_t trigger_average_cnt;
uint32_t trigger_lt_record[TRIGGER_AVERAGE_SMOOTHING_CNT];
uint32_t trigger_rt_record[TRIGGER_AVERAGE_SMOOTHING_CNT];
#endif

/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
ATTR_TEXT_IN_TCM int game_controller_joystick_get_data(uint32_t *x, uint32_t *y, uint32_t *z, uint32_t *rz)
{
    /* unsigned 12bit -> unsigned 16bit */
    *y  = hid_common->hid.adc.saradc_data.channel_data[0]<<4;
    *x  = hid_common->hid.adc.saradc_data.channel_data[1]<<4;
    *rz  = hid_common->hid.adc.saradc_data.channel_data[2]<<4;
    *z = hid_common->hid.adc.saradc_data.channel_data[3]<<4;

    return 0;
}

#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
ATTR_TEXT_IN_TCM int32_t game_controller_joystick_process_sensitivity(game_controller_sensitivity_direction_t sensitivity, int32_t in_value)
{
    int32_t sensitivity_value = JOYSTICK_DEFAULT_SENSITIVITY;

    if (sensitivity == GAME_CONTROLLER_LEFT_SENSITIVITY) {
        sensitivity_value = left_sensitivity;
    } 
    else if (sensitivity == GAME_CONTROLLER_RIGHT_SENSITIVITY) {
        sensitivity_value = right_sensitivity;
    }

    if (sensitivity_value != JOYSTICK_DEFAULT_SENSITIVITY) {
        return (int32_t)((float)in_value * ((float)sensitivity_value / (float)JOYSTICK_DEFAULT_SENSITIVITY));
    }
    return in_value;
}
#endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */

ATTR_TEXT_IN_TCM int32_t game_controller_joystick_process_data_common_ex(game_controller_joystick_num_t joystick_num, uint32_t in_value, game_controller_sensitivity_direction_t sensitivity)
{
    int32_t temp;
    int32_t range;

    if (in_value > joystick_calibration[joystick_num].zero_value)
    {
        range = joystick_calibration[joystick_num].max - joystick_calibration[joystick_num].zero_value;
        temp = in_value - joystick_calibration[joystick_num].zero_value;
        if (temp > range)
        {
            temp = range;
        }
        temp = (int32_t)(((float)temp / range) * JOYSTICK_HALF_RANGE_VALUE);
        #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
        temp = game_controller_joystick_process_sensitivity(sensitivity, temp);
        #endif
    }
    else 
    {
        range = joystick_calibration[joystick_num].min - joystick_calibration[joystick_num].zero_value;
        temp = in_value - joystick_calibration[joystick_num].zero_value;
        if (temp < range)
        {
            temp = range;
        }
        temp = (int32_t)(((float)temp / range) * JOYSTICK_HALF_RANGE_VALUE);
        #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
        temp = game_controller_joystick_process_sensitivity(sensitivity, temp);
        #endif
        temp = -temp;
    }

    return temp;
}

ATTR_TEXT_IN_TCM void game_controller_joystick_process_data_common(game_controller_joystick_num_t joystick_num_1, uint32_t in_value_1, 
                                                                        game_controller_joystick_num_t joystick_num_2, uint32_t in_value_2,
                                                                        uint32_t *out_value_1, uint32_t *out_value_2, game_controller_sensitivity_direction_t sensitivity)
{
    *out_value_1 = game_controller_joystick_process_data_common_ex(joystick_num_1, in_value_1, sensitivity);
    *out_value_2 = game_controller_joystick_process_data_common_ex(joystick_num_2, in_value_2, sensitivity);

    if ((in_value_1 > joystick_calibration[joystick_num_1].zero_deadzone_min_value) && 
        (in_value_1 < joystick_calibration[joystick_num_1].zero_deadzone_max_value) &&
        (in_value_2 > joystick_calibration[joystick_num_2].zero_deadzone_min_value) &&
        (in_value_2 < joystick_calibration[joystick_num_2].zero_deadzone_max_value)) {
        *out_value_1 = 0;
        *out_value_2 = 0;
    }
}

ATTR_TEXT_IN_TCM int game_controller_joystick_process_data(uint32_t in_x, uint32_t in_y, uint32_t in_z, uint32_t in_rz, uint32_t *out_x, uint32_t *out_y, uint32_t *out_z, uint32_t *out_rz)
{
    int32_t x_temp;
    int32_t y_temp;
    int32_t z_temp;
    int32_t rz_temp;

    if (!game_controller_fake_data_enable)
    {
        /* output normal data */
        game_controller_joystick_process_data_common(GAME_CONTROLLER_JOYSTICK_X, in_x, GAME_CONTROLLER_JOYSTICK_Y, in_y, &x_temp, &y_temp, GAME_CONTROLLER_LEFT_SENSITIVITY);
        *out_x = JOYSTICK_0_LEVEL_VALUE + x_temp;
        *out_y = JOYSTICK_0_LEVEL_VALUE + y_temp;
        game_controller_joystick_process_data_common(GAME_CONTROLLER_JOYSTICK_Z, in_z, GAME_CONTROLLER_JOYSTICK_RZ, in_rz, &z_temp, &rz_temp, GAME_CONTROLLER_RIGHT_SENSITIVITY);
        *out_z = JOYSTICK_0_LEVEL_VALUE + z_temp;
        *out_rz = JOYSTICK_0_LEVEL_VALUE + rz_temp;
    }
    else
    {
        /* output fake data */
        double theta = 2.0 * PI * game_controller_fake_data_joystick_idx / JOYSTICK_FAKE_DATA_NUMBER;
        x_temp = (int32_t)(JOYSTICK_0_LEVEL_VALUE + JOYSTICK_HALF_RANGE_VALUE * cos(theta));
        y_temp = (int32_t)(JOYSTICK_0_LEVEL_VALUE + JOYSTICK_HALF_RANGE_VALUE * sin(theta));
        *out_x = x_temp;
        *out_y = y_temp;
        *out_z = x_temp;
        *out_rz = y_temp;
        game_controller_fake_data_joystick_idx++;
        if (game_controller_fake_data_joystick_idx >= JOYSTICK_FAKE_DATA_NUMBER)
        {
            game_controller_fake_data_joystick_idx = 0;
        }
    }

    /*  delay 50 us for customer alogorithm */
    // hal_gpt_delay_us(50);
    return 0;
}

ATTR_TEXT_IN_TCM int game_controller_joystick_save_data(uint32_t x, uint32_t y, uint32_t z, uint32_t rz)
{
    hid_common->hid.x  = x;
    hid_common->hid.y  = y;
    hid_common->hid.z  = z;
    hid_common->hid.rz = rz;

    return 0;
}

ATTR_TEXT_IN_TCM int game_controller_trigger_get_data(uint32_t *lt, uint32_t *rt)
{
    /* unsigned 12bit -> unsigned 16bit */
    *lt = hid_common->hid.adc.saradc_data.channel_data[4]<<4;
    *rt = hid_common->hid.adc.saradc_data.channel_data[5]<<4;

#if defined(TRIGGER_AVERAGE_SMOOTHING)
    uint32_t i;
    uint32_t avgerage_lt=0;
    uint32_t avgerage_rt=0;
    trigger_lt_record[trigger_average_cnt] = *lt;
    trigger_rt_record[trigger_average_cnt] = *rt;
    for (i = 0; i < TRIGGER_AVERAGE_SMOOTHING_CNT; i++)
    {
        avgerage_lt += trigger_lt_record[i];
        avgerage_rt += trigger_rt_record[i];
    }
    avgerage_lt = avgerage_lt / TRIGGER_AVERAGE_SMOOTHING_CNT;
    avgerage_rt = avgerage_rt / TRIGGER_AVERAGE_SMOOTHING_CNT;
    trigger_average_cnt++;
    if (trigger_average_cnt >= TRIGGER_AVERAGE_SMOOTHING_CNT)
    {
        trigger_average_cnt = 0;
    }
    *lt = avgerage_lt;
    *rt = avgerage_rt;
#endif

    return 0;
}

ATTR_TEXT_IN_TCM uint32_t game_controller_trigger_process_data_common(game_controller_trigger_num_t trigger_num, uint32_t in_value)
{
    uint32_t temp;
    uint32_t range = trigger_calibration[trigger_num].max - trigger_calibration[trigger_num].min;

    if (trigger_calibration[trigger_num].direction == GAME_CONTROLLER_TRIGGER_DIRECTION_FORWARD)
    {
        if (in_value > trigger_calibration[trigger_num].zero_deadzone_value)
        {
            temp = in_value - trigger_calibration[trigger_num].min;
            if (temp > range)
            {
                temp = range;
            }
            temp = (uint32_t)(((float)temp / range) * TRIGGER_RANGE_VALUE);
        }
        else
        {
            temp = 0;
        }
    }
    else
    {
        if (in_value < trigger_calibration[trigger_num].zero_deadzone_value)
        {
            temp = trigger_calibration[trigger_num].max - in_value;
            if (temp > range)
            {
                temp = range;
            }
            temp = (uint32_t)(((float)temp / range) * TRIGGER_RANGE_VALUE);
        }
        else
        {
            temp = 0;
        }
    }

    return temp;
}

ATTR_TEXT_IN_TCM int game_controller_trigger_process_data(uint32_t in_lt, uint32_t in_rt, uint32_t *out_lt, uint32_t *out_rt)
{
    if (!game_controller_fake_data_enable)
    {
        /* output normal data */
        *out_lt = game_controller_trigger_process_data_common(GAME_CONTROLLER_TRIGGER_L, in_lt);
        *out_rt = game_controller_trigger_process_data_common(GAME_CONTROLLER_TRIGGER_R, in_rt);
    }
    else
    {
        /* output fake data */
        *out_lt = game_controller_fake_data_trigger_idx<<6;
        *out_rt = game_controller_fake_data_trigger_idx<<6;
        game_controller_fake_data_trigger_idx++;
        if (game_controller_fake_data_trigger_idx >= 1024)
        {
            game_controller_fake_data_trigger_idx = 0;
        }
    }

    return 0;
}

ATTR_TEXT_IN_TCM int game_controller_trigger_save_data(uint32_t lt, uint32_t rt)
{
    gpio_data_in_mask_t gpio_data_in_mask_temp;
    hal_eint_get_debounce_out_value_by_mask(&gpio_data_in_mask_temp.register0, &gpio_data_in_mask_temp.register1);
    // gpio : 0  is pressed , 1 is released
    // key : 1  is pressed , 0 is released
    // uint32_t all_gpio_status_1 = ~gpio_data_in_mask_temp.register0;
    /* Expand IO17: LT_MODE, IO18: RT_MODE */
    if ((game_controlle_expand_button & (1 << 17)) == 0) {
        /* unsigned 16bit -> unsigned 10bit */
        hid_common->hid.lt = lt>>6;
    } else {
        /* GPIO17: LT SW*/
        // hid_common->hid.lt = (all_gpio_status_1 & (1 << 17)) ? 1023 : 0;
    }

    if ((game_controlle_expand_button & (1 << 18)) == 0) {
        /* unsigned 16bit -> unsigned 10bit */
        hid_common->hid.rt = rt>>6;
    } else {
        /* GPIO23: RT SW*/
        // hid_common->hid.rt = (all_gpio_status_1 & (1 << 23)) ? 1023 : 0;
    }

    return 0;
}

ATTR_TEXT_IN_TCM void CCNI_DEF_HANDLER(5)(hal_ccni_event_t event, hal_ccni_message_t *msg)
{
    uint32_t hid_flags = hid_common->hid.flags;
    if((USB_PLUG_STATUS_CHECK(hid_flags) == USB_PLUG_OUT) && (SLIDE_SWITCH_POSITION(hid_flags) == SS_MODE_OFF)){
        return;
    }
    #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    uint32_t key_status = 0;
    #endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */

    if(msg)
    {
        hid_flags = msg->data[0];
    #if defined(CONFIG_AIR_USB_EARLY_WAKEUP_CM33)
        if(USB_DATA_GO(hid_flags)){
            if(hid_game_controller_usb_cb){
                DBG_PING_H(DBG_SIGNAL_DEBUG_2);
                DBG_PING_L(DBG_SIGNAL_DEBUG_2);
                hid_game_controller_usb_cb();
            }
        }
    #endif
    #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
        key_status = msg->data[1];
    #endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */
    }

    DBG_PING_H(DBG_SIGNAL_LATCH_REPORT);
    uint32_t x,y,z,rz,lt,rt;
    uint32_t out_x,out_y,out_z,out_rz,out_lt,out_rt;

    // hal_gpio_set_output(HAL_GPIO_40, HAL_GPIO_DATA_HIGH);

    /* joystick process */
    game_controller_joystick_get_data(&x, &y, &z, &rz);
    game_controller_joystick_process_data(x, y, z, rz, &out_x, &out_y, &out_z, &out_rz);
    game_controller_joystick_save_data(out_x, out_y, out_z, out_rz);

    /* trigger process */
    game_controller_trigger_get_data(&lt, &rt);
    game_controller_trigger_process_data(lt, rt, &out_lt, &out_rt);
    game_controller_trigger_save_data(out_lt, out_rt);
    DBG_PING_L(DBG_SIGNAL_LATCH_REPORT);

    /* Note: this delay is reserved for the customer to implement their own algorithm */
    hal_gpt_delay_us(30);

#ifdef TRIGGER_DEBUG
    LOG_INF(thisMOD" Trigger ADC Data = [0x%08x:0x%08x], Result Data = [0x%08x:0x%08x].", lt, rt, out_lt, out_rt);
#endif /* TRIGGER_DEBUG */

    #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    if(!BT_DATA_GO(hid_flags))
    {
        /* Key remap backend process */
        key_remap_update_key_status(key_status);
        key_remap_backend_process();
    }
    #endif

    // hal_gpio_set_output(HAL_GPIO_40, HAL_GPIO_DATA_LOW);
}

/* Public functions ----------------------------------------------------------*/
int game_controller_bt_hw_trigger_enable(void)
{
#if defined(CONFIG_AIR_HW_KEYSCAN)
            /*bt trigger mode enable*/
        *(volatile uint32_t *)(0x42020038) = (0x0);
#else
    hal_spi_master_config_t spi_config;
    int ret = 0;

    spi_config.bit_order = HAL_SPI_MASTER_MSB_FIRST;
    spi_config.slave_port = HAL_SPI_MASTER_SLAVE_0;
    spi_config.clock_frequency = 8000000;
    spi_config.phase = HAL_SPI_MASTER_CLOCK_PHASE1;
    spi_config.polarity = HAL_SPI_MASTER_CLOCK_POLARITY1;
    ret = hal_spi_master_init(HAL_SPI_MASTER_0, &spi_config);
    if (HAL_SPI_MASTER_STATUS_OK != ret) {
        LOG_INF(thisMOD" bt_hw_trigger_enable spi init failed, ret: %d.", ret);
    }
    hal_spi_master_set_clear_data(HAL_SPI_MASTER_0,1,1,true);

    hal_spi_master_send_and_receive_config_t spi_send_and_receive_config;
    spi_send_and_receive_config.receive_length = 1;
    spi_send_and_receive_config.send_length = 1;
    spi_send_and_receive_config.send_data = &spi_dummy_write_reg;
    spi_send_and_receive_config.receive_buffer = &spi_dummy_write_reg;
    hal_spi_master_send_and_receive_dma_advanced(HAL_SPI_MASTER_0, &spi_send_and_receive_config,false);   //not start
    hal_spi_master_set_bt_enable(HAL_SPI_MASTER_0, true);
#endif
    LOG_INF(thisMOD" bt_hw_trigger_enable.");

    return 0;
}

int game_controller_bt_hw_trigger_disable(void)
{
#if defined(CONFIG_AIR_HW_KEYSCAN)
    /*sw trigger mode enable*/
    *(volatile uint32_t *)(0x42020038) = (0x1);
#else
    game_controller_bt_hw_trigger_enable();
    hal_spi_master_status_t ret = HAL_SPI_MASTER_STATUS_OK;
    ret |= hal_spi_master_set_bt_enable(HAL_SPI_MASTER_0, false);  //disable BT trigger
    if(HAL_SPI_MASTER_STATUS_OK != ret){
        LOG_INF(thisMOD, "usb_spi_trigger_enable failed, pls check!!!!!");
    }
#endif
    LOG_INF(thisMOD" game_controller_bt_hw_trigger_disable.");
    return 0;
}

ATTR_TEXT_IN_TCM int game_controller_bt_hw_trigger_read(void)
{
#if defined(CONFIG_AIR_HW_KEYSCAN)
    *(volatile uint32_t *)(0x4202003c) = (0x1);//sw trigger scan once
#else
    hal_spi_master_restore_address_advanced(HAL_SPI_MASTER_0,&spi_dummy_write_reg,&spi_dummy_write_reg);
    hal_spi_master_status_t ret = hal_spi_master_trigger_start(HAL_SPI_MASTER_0, true);  //trig start
    if (HAL_SPI_MASTER_STATUS_OK != ret) {
        LOG_INF(thisMOD" game_controller_bt_hw_trigger_read failed, ret: %d.", ret);
        return 1;
    }
#endif
    return 0;
}

joystick_adc_parameter_t *game_controller_joystick_get_calibration_value(game_controller_joystick_num_t joystick_num)
{
    if (joystick_num >= GAME_CONTROLLER_JOYSTICK_NUM_MAX)
    {
        return NULL;
    }

    return &joystick_calibration[joystick_num];
}

void game_controller_joystick_update_calibration_value(game_controller_joystick_num_t joystick_num,
                                                        uint32_t min, uint32_t max, uint32_t zero_value,
                                                        uint32_t zero_deadzone_min_value, uint32_t zero_deadzone_max_value)
{
    if (joystick_num >= GAME_CONTROLLER_JOYSTICK_NUM_MAX)
    {
        return;
    }

    joystick_calibration[joystick_num].min = min;
    joystick_calibration[joystick_num].max = max;
    joystick_calibration[joystick_num].zero_value = zero_value;
    joystick_calibration[joystick_num].zero_deadzone_min_value = zero_deadzone_min_value;
    joystick_calibration[joystick_num].zero_deadzone_max_value = zero_deadzone_max_value;

    LOG_INF(thisMOD" joystick-%d calibration value, min=%u, max=%u, zero=%u, deadzone_min=%u, deadzone_max=%u.", joystick_num,
                                                    joystick_calibration[joystick_num].min,
                                                    joystick_calibration[joystick_num].max,
                                                    joystick_calibration[joystick_num].zero_value,
                                                    joystick_calibration[joystick_num].zero_deadzone_min_value,
                                                    joystick_calibration[joystick_num].zero_deadzone_max_value);
}

trigger_adc_parameter_t *game_controller_trigger_get_calibration_value(game_controller_trigger_num_t trigger_num)
{
    if (trigger_num >= GAME_CONTROLLER_TRIGGER_NUM_MAX)
    {
        return NULL;
    }

    return &trigger_calibration[trigger_num];
}

void game_controller_trigger_update_calibration_value(game_controller_trigger_num_t trigger_num, game_controller_trigger_direction_t direction,
                                                        uint32_t min, uint32_t max, uint32_t zero_deadzone_value)
{
    if (trigger_num >= GAME_CONTROLLER_TRIGGER_NUM_MAX)
    {
        return;
    }

    trigger_calibration[trigger_num].direction = direction;
    trigger_calibration[trigger_num].min = min;
    trigger_calibration[trigger_num].max = max;
    trigger_calibration[trigger_num].zero_deadzone_value = zero_deadzone_value;

    LOG_INF(thisMOD" trigger-%d calibration value, direction=%u, min=%u, max=%u, deadzone=%u.", trigger_num,
                                                    trigger_calibration[trigger_num].direction,
                                                    trigger_calibration[trigger_num].min,
                                                    trigger_calibration[trigger_num].max,
                                                    trigger_calibration[trigger_num].zero_deadzone_value);
}

void game_controller_set_expand_button(uint32_t *key)
{
    // LOG_INF(thisMOD" game_controller_set_expand_button, key = 0x%x ", *key);
    game_controlle_expand_button = ~(*key);
}

bool game_controller_usb_register(hid_game_controller_report_callback cb)
{
    LOG_INF(thisMOD" game_controller_usb_register_callbacks, cb = 0x%x " ,cb);
    if(!cb){
        return 1;
    }
    hid_game_controller_usb_cb = cb;
    return 0;
}

void game_controller_fake_data_control(bool enable, uint8_t pattern, uint8_t rounds)
{
    game_controller_fake_data_enable = enable;
    game_controller_fake_data_pattern = pattern;
    game_controller_fake_data_rounds = rounds;

    if (!game_controller_fake_data_enable)
    {
        /* reset state machine */
        game_controller_fake_data_joystick_idx = 0;
        game_controller_fake_data_trigger_idx = 0;
    }

    LOG_INF(thisMOD" game_controller_fake_data_control, enable = %u, pattern = %u, rounds = %u",
            game_controller_fake_data_enable,
            game_controller_fake_data_pattern,
            game_controller_fake_data_rounds);
}

#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
ATTR_TEXT_IN_TCM void game_controller_set_sensitivity(uint8_t direction, uint8_t value)
{
    LOG_INF(thisMOD" game_controller_set_sensitivity, direction = %u, value = %u", direction, value);
    if(direction == GAME_CONTROLLER_LEFT_SENSITIVITY)
    {
        // Left joystick sensitivity
        left_sensitivity = value;
    }
    else if(direction == GAME_CONTROLLER_RIGHT_SENSITIVITY)
    {
        // Right joystick sensitivity
        right_sensitivity = value;
    }
}
#endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */

#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */
