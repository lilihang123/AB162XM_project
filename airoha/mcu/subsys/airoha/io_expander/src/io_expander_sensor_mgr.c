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
 #ifdef CONFIG_IO_EXPANDER_AW95124
#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include "io_expander_sensor_mgr.h"
#include "hid_common.h"
#include "hid_scenario_service.h"
#include "hid_scenario_service_internal.h"
#include "hal_eint.h"
/******************************************************************************/
/*  macro                                                                     */
/******************************************************************************/
#define thisMOD    "io_expander_msmgr"
#define thisMODULE io_expander_msmgr
#define IO_EXPANDER_MAX_IO_NUM 24
// #define IO_EXPANDER_MGR_DEBUG_EN
LOG_MODULE_REGISTER(thisMODULE);
/******************************************************************************/
/*  typedef                                                                   */
/******************************************************************************/
struct io_expander_debounce_context_s{
    struct         k_work_delayable dwork;    // delayed work for debounce
    uint8_t        pin_num;                   // pin number to be debounced
    uint8_t        default_state;             // default state of the pin
    uint8_t        last_state;                // last state of the pin
    uint8_t        debounce_time;             // debounce interval in ms
    bool           is_debouncing;             // flag to indicate if debouncing is in progress
};

struct io_expander_pin_config_s {
    struct io_expander_debounce_context_s debounce_ctxs[IO_EXPANDER_MAX_IO_NUM];
    uint32_t                            io_expander_keys_bitmap;
    uint32_t                            all_pin_last_state;
    uint32_t                            all_pin_current_state;
};
/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
const struct device * dev_hdl_sensor = NULL;
struct k_work io_expander_work;
struct k_work_delayable io_expander_error_work;
// struct io_expander_debounce_context io_expander_debounce_ctxs[IO_EXPANDER_MAX_IO_NUM];// debounce context for each pin
struct  io_expander_pin_config_s io_expander_pin_config;
uint8_t key_map[] = {0, 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
/******************************************************************************/
/* callback function                                                        */
/******************************************************************************/
void (*io_expander_pin_state_transaction)(uint32_t *keys) = NULL;// function pointer to the callback function

int io_expander_mgr_register_callback(sw_debounce_io_epxander_callback_t callback)
{
    if(callback == NULL){
        return -1;
    }
    io_expander_pin_state_transaction = callback;
    return 0;
}


#ifdef IO_EXPANDER_MGR_DEBUG_EN
#define BUTTON_MAX_NUM (sizeof(key_map) / sizeof(key_map[0]))
void button_data_parse(uint8_t button_data)
{
    switch (button_data){
        case BUTTON_M1:
            DBG_LOGI(thisMOD, "BUTTON_M1 pressed");
            break;
        case BUTTON_M2:
            DBG_LOGI(thisMOD, "BUTTON_M2 pressed");
            break;
        case BUTTON_M3:
            DBG_LOGI(thisMOD, "BUTTON_M3 pressed");
            break;
        case BUTTON_M4:
            DBG_LOGI(thisMOD, "BUTTON_M4 pressed");
            break;
        case BUTTON_M5:
            DBG_LOGI(thisMOD, "BUTTON_M5 pressed");
            break;
        case BUTTON_M6:
            DBG_LOGI(thisMOD, "BUTTON_M6 pressed");
            break;
        case BUTTON_G1:
            DBG_LOGI(thisMOD, "BUTTON_G1 pressed");
            break;
        case BUTTON_G2:
            DBG_LOGI(thisMOD, "BUTTON_G2 pressed");
            break;
        case BUTTON_G3:
            DBG_LOGI(thisMOD, "BUTTON_G3 pressed");
            break;
        case BUTTON_G4:
            DBG_LOGI(thisMOD, "BUTTON_G4 pressed");
            break;
        case BUTTON_G5:
            DBG_LOGI(thisMOD, "BUTTON_G5 pressed");
            break;
        case BUTTON_PAIRING:
            DBG_LOGI(thisMOD, "BUTTON_PAIRING pressed");
            break;
        case BUTTON_VIEW:
            DBG_LOGI(thisMOD, "BUTTON_VIEW pressed");
            break;
        case BUTTON_VLED_EN:
            DBG_LOGI(thisMOD, "BUTTON_VLED_EN pressed");
            break;
        case BUTTON_MENU:
            DBG_LOGI(thisMOD, "BUTTON_MENU pressed");
            break;
        case BUTTON_LT_MODE:
            DBG_LOGI(thisMOD, "BUTTON_LT_MODE pressed");
            break;
        case BUTTON_RT_MODE:
            DBG_LOGI(thisMOD, "BUTTON_RT_MODE pressed");
            break;
        default:
            DBG_LOGI(thisMOD, "Unknown button pressed");
    }
}
#endif

static void io_expander_error_work_handler(struct k_work *work)
{
    io_expander_mgr_deinit();
    DBG_LOGI(thisMOD, "Error occurred, deinit IO expander");
    io_expander_mgr_init();
    DBG_LOGI(thisMOD, "Reinit IO expander after error");
}

static void io_expander_debounce_dwork_handler(struct k_work *work)
{
    // struct k_work_delayable *dwork = k_work_delayable_from_work(work);
    struct sensor_value val = {0, 0};
    int ret = sensor_attr_get(dev_hdl_sensor, IO_EXPANDER_CHAN_DEVICE_DATA, IO_EXPANDER_ATTR_ALL_INPUT, &val);
    if (ret != 0) {
        DBG_LOGI(thisMOD, "Failed to get all input status in io_expander_work_handler, ret = %d", ret);
        k_work_reschedule(&io_expander_error_work, K_NO_WAIT);
        return;
    }
    struct io_expander_debounce_context_s *debounce_context = CONTAINER_OF(work, struct io_expander_debounce_context_s, dwork.work);
    io_expander_pin_config.all_pin_current_state = val.val1;
    uint8_t pin_num = debounce_context->pin_num;

    if(((io_expander_pin_config.io_expander_keys_bitmap>>pin_num) & 0x01) != 1){
        return;
    }

    if(io_expander_pin_config.debounce_ctxs[pin_num].is_debouncing != true)
    {
        return;
    }

    if((io_expander_pin_config.debounce_ctxs[pin_num].last_state != ((io_expander_pin_config.all_pin_current_state>>pin_num) & 0x01)))
    {
        DBG_LOGI(thisMOD, "Debounce failed io_expander_pin %d state not changed,all_pin_current_state = %x", pin_num, io_expander_pin_config.all_pin_current_state);
        io_expander_pin_config.debounce_ctxs[pin_num].last_state = (io_expander_pin_config.all_pin_current_state>>pin_num) & 0x01;
        io_expander_pin_config.debounce_ctxs[pin_num].is_debouncing = false;
        return;
    }

    io_expander_pin_config.debounce_ctxs[pin_num].is_debouncing = false;
    if(io_expander_pin_config.debounce_ctxs[pin_num].last_state == 0){
        io_expander_pin_config.all_pin_last_state &= ~(1 << pin_num);
    }else{
        io_expander_pin_config.all_pin_last_state |= 1 << pin_num;
    }
    // Call the callback function with the stable state
    if(io_expander_pin_state_transaction)
    {
        io_expander_pin_state_transaction(&io_expander_pin_config.all_pin_last_state);
    }
    DBG_LOGI(thisMOD, "Debounce completed io_expander_pin %d changed to %d,all_pin_last_state = %x", pin_num,
        ((io_expander_pin_config.all_pin_current_state>>pin_num) & 0x01),
        io_expander_pin_config.all_pin_last_state);
    #ifdef IO_EXPANDER_MGR_DEBUG_EN
    io_expander_mgr_get_all_interrupt_status();

    button_data_parse(pin_num);
    #endif
}


static void io_expander_work_handler(struct k_work *work)
{
    struct sensor_value val = {0, 0};
    int ret = sensor_attr_get(dev_hdl_sensor, IO_EXPANDER_CHAN_DEVICE_DATA, IO_EXPANDER_ATTR_ALL_INPUT, &val);
    if (ret != 0) {
        DBG_LOGI(thisMOD, "Failed to get all input status in io_expander_work_handler, ret = %d", ret);
        k_work_reschedule(&io_expander_error_work, K_NO_WAIT);
        hal_eint_unmask(0);
        return;
    }
    io_expander_pin_config.all_pin_current_state = val.val1;
    for(int i = 0; i < IO_EXPANDER_MAX_IO_NUM; i++){

        if(((io_expander_pin_config.io_expander_keys_bitmap>>i) & 0x01) != 1){
            continue;
        }

        if((io_expander_pin_config.debounce_ctxs[i].last_state == ((io_expander_pin_config.all_pin_current_state>>i) & 0x01))){
            continue;
        }

        DBG_LOGI(thisMOD, " io_expander_pin %d state %d changed to %d,debounce time = %d,all_pin_current_state = %x", i,
            io_expander_pin_config.debounce_ctxs[i].last_state,
            ((io_expander_pin_config.all_pin_current_state>>i) & 0x01),
            io_expander_pin_config.debounce_ctxs[i].debounce_time,
            io_expander_pin_config.all_pin_current_state);
        io_expander_pin_config.debounce_ctxs[i].last_state = (io_expander_pin_config.all_pin_current_state>>i) & 0x01;
        io_expander_pin_config.debounce_ctxs[i].is_debouncing = true;
        // Start the delayed work
        k_work_reschedule(&io_expander_pin_config.debounce_ctxs[i].dwork,
                           K_MSEC(io_expander_pin_config.debounce_ctxs[i].debounce_time));
        // DBG_LOGI(thisMOD, "Debounce work handler called, last_all_pin_state: %x", io_expander_pin_config.all_pin_last_state);
    }
    hal_eint_unmask(0);
}

void io_expander_mgr_debounce_set(uint8_t pin_num, uint8_t debounce_time, uint8_t default_state)
{
    if (pin_num >= IO_EXPANDER_MAX_IO_NUM) {
        DBG_LOGI(thisMOD, "Invalid pin number %u", pin_num);
        return;
    }
    io_expander_pin_config.io_expander_keys_bitmap |= (1 << pin_num);
    DBG_LOGI(thisMOD, "bitmap: 0x%x", io_expander_pin_config.io_expander_keys_bitmap);
    io_expander_pin_config.debounce_ctxs[pin_num].debounce_time = debounce_time;
    io_expander_pin_config.debounce_ctxs[pin_num].default_state = default_state;
    io_expander_pin_config.debounce_ctxs[pin_num].pin_num = pin_num;
    if(default_state == 1)
    {
        io_expander_pin_config.all_pin_last_state |= (1 << pin_num);
    }else{
        io_expander_pin_config.all_pin_last_state &= ~(1 << pin_num);
    }

    io_expander_pin_config.debounce_ctxs[pin_num].last_state = default_state;
    io_expander_pin_config.debounce_ctxs[pin_num].is_debouncing = false;
    k_work_init_delayable(&io_expander_pin_config.debounce_ctxs[pin_num].dwork, io_expander_debounce_dwork_handler);
}

uint32_t io_expander_mgr_get_all_input_status(void)
{
    return io_expander_pin_config.all_pin_last_state;
}

uint32_t io_expander_mgr_get_all_interrupt_status(void)
{
    struct sensor_value val = {0, 0};
    uint32_t io_expander_ints = 0;
    int ret = sensor_attr_get(dev_hdl_sensor, IO_EXPANDER_CHAN_DEVICE_DATA, IO_EXPANDER_ATTR_ALL_INTS, &val);
    if(ret != 0)
    {
        k_work_reschedule(&io_expander_error_work, K_NO_WAIT);
    }
    io_expander_ints = val.val1;
    DBG_LOGI(thisMOD,"io_expander all interrupt status = 0x%04x", io_expander_ints);
    ret = sensor_attr_get(dev_hdl_sensor, IO_EXPANDER_CHAN_DEVICE_DATA, IO_EXPANDER_ATTR_ALL_INPUT, &val);
    if(ret != 0)
    {
        k_work_reschedule(&io_expander_error_work, K_NO_WAIT);
    }
    DBG_LOGI(thisMOD,"io_expander all input status = 0x%04x", val.val1);
    return io_expander_ints;
}

int io_expander_mgr_pin_config_set(uint32_t pin_num, void* config){
    struct sensor_value val = {0, 0};
    int ret_attr1 = 0;
    val.val1 = pin_num;
    val.val2 = (int32_t)config;
    ret_attr1 = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, IO_EXPANDER_ATTR_PIN_CONFIG, &val);
    if (ret_attr1 != 0) {
        DBG_LOGI(thisMOD,"io_expander_mgr_pin_config failed, ret_attr1 = %d", ret_attr1);
        return ret_attr1;
    }
    return ret_attr1;
}

int io_expander_mgr_pin_irq_type_config_set(uint32_t pin_num, uint32_t irq_type){
    struct sensor_value val = {0, 0};
    int ret_attr1 = 0;
    val.val1 = pin_num;
    val.val2 = irq_type;
    ret_attr1 = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, IO_EXPANDER_ATTR_PIN_IRQ_TYPE_CONFIG, &val);
    if (ret_attr1 != 0) {
        DBG_LOGI(thisMOD,"io_expander_mgr_pin_irq_type_config failed, ret_attr1 = %d", ret_attr1);
        return ret_attr1;
    }
    return ret_attr1;
}

int io_expander_mgr_pin_irq_enable_set(uint32_t pin_num, bool enable){
    struct sensor_value val = {0, 0};
    int ret_attr1 = 0;
    val.val1 = pin_num;
    val.val2 = enable;
    ret_attr1 = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, IO_EXPANDER_ATTR_PIN_IRQ_ENABLE, &val);
    if (ret_attr1 != 0) {
        DBG_LOGI(thisMOD,"io_expander_mgr_pin_irq_enable_set failed, ret_attr1 = %d", ret_attr1);
        return ret_attr1;
    }
    return ret_attr1;
}

int io_expander_mgr_pin_dir_input_set(uint32_t pin_num){
    struct sensor_value val = {0, 0};
    int ret_attr1 = 0;
    val.val1 = pin_num;
    ret_attr1 = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, IO_EXPANDER_ATTR_PIN_DIR_INPUT, &val);
    if (ret_attr1 != 0) {
        DBG_LOGI(thisMOD,"io_expander_mgr_pin_dir_input_set failed, ret_attr1 = %d", ret_attr1);
        return ret_attr1;
    }
    return ret_attr1;
}

int io_expander_mgr_pin_dir_output_set(uint32_t pin_num, uint32_t value){
    struct sensor_value val = {0, 0};
    int ret_attr1 = 0;
    val.val1 = pin_num;
    val.val2 = value;
    ret_attr1 = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, IO_EXPANDER_ATTR_PIN_DIR_OUTPUT, &val);
    if (ret_attr1 != 0) {
        DBG_LOGI(thisMOD,"io_expander_mgr_pin_dir_output_set  failed, ret_attr1 = %d", ret_attr1);
        return ret_attr1;
    }
    return ret_attr1;
}

int io_expander_mgr_pin_pull_set(uint32_t pin_num, uint32_t pull){
    struct sensor_value val = {0, 0};
    int ret_attr1 = 0;
    val.val1 = pin_num;
    val.val2 = pull;
    ret_attr1 = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, IO_EXPANDER_ATTR_PIN_PULL_SET, &val);
    if (ret_attr1 != 0) {
        DBG_LOGI(thisMOD,"io_expander_mgr_pin_pull_set failed, ret_attr1 = %d", ret_attr1);
        return ret_attr1;
    }
    return ret_attr1;
}

int io_expander_mgr_pin_value_set(uint32_t pin_num, uint32_t value){
    struct sensor_value val = {0, 0};
    int ret_attr1 = 0;
    val.val1 = pin_num;
    val.val2 = value;
    ret_attr1 = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, IO_EXPANDER_ATTR_PIN_VALUE_SET, &val);
    if (ret_attr1 != 0) {
        DBG_LOGI(thisMOD,"io_expander_mgr_pin_value_set failed, ret_attr1 = %d", ret_attr1);
        return ret_attr1;
    }
    DBG_LOGI(thisMOD,"io_expander_mgr_pin_value_set success, pin_num = %d, value = %d", pin_num, value);
    return ret_attr1;
}

int io_expander_mgr_enter_low_power(void)
{
    struct sensor_value val = {0, 0};
    int ret_attr1 = 0;
    ret_attr1 = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, IO_EXPANDER_ATTR_ENTER_LOW_POWER, &val);
    if (ret_attr1 != 0) {
        DBG_LOGI(thisMOD,"io_expander_mgr_enter_low_power failed, ret_attr1 = %d", ret_attr1);
        return ret_attr1;
    }
    DBG_LOGI(thisMOD,"io_expander_mgr_enter_low_power success, ret_attr1 = %d", ret_attr1);
    return ret_attr1;
}

int io_expander_mgr_exit_low_power(void)
{
    struct sensor_value val = {0, 0};
    int ret_attr1 = 0;
    ret_attr1 = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, IO_EXPANDER_ATTR_EXIT_LOW_POWER, &val);
    if (ret_attr1 != 0) {
        DBG_LOGI(thisMOD,"io_expander_mgr_exit_low_power failed, ret_attr1 = %d", ret_attr1);
        return ret_attr1;
    }
    DBG_LOGI(thisMOD,"io_expander_mgr_exit_low_power success, ret_attr1 = %d", ret_attr1);
    return ret_attr1;
}

void io_expander_mgr_init(void)
{
    #if defined(CONFIG_IO_EXPANDER_AW95124)
    dev_hdl_sensor = DEVICE_DT_GET(DT_NODELABEL(aw95124));
    if (dev_hdl_sensor == NULL) {
        DBG_LOGI(thisMOD, "Failed to get device aw95124");
        k_work_reschedule(&io_expander_error_work, K_NO_WAIT);
        return;
    }
    DBG_LOGI(thisMOD,"io_expander_mgr_init aw95124, dev_hdl_sensor = %x", *(uint32_t*)dev_hdl_sensor);
    #else
    #endif
    k_work_init(&io_expander_work, io_expander_work_handler);
    k_work_init_delayable(&io_expander_error_work, io_expander_error_work_handler);
    struct sensor_value val = {(int)(&io_expander_work), 0};
    DBG_LOGI(thisMOD,"SENSOR_STATE_INIT, &io_expander_work = %x", val.val1);
    int ret_attr1 = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, IO_EXPANDER_ATTR_INIT, &val);
    DBG_LOGI(thisMOD,"SENSOR_STATE_INIT, ret_attr1 = %d", ret_attr1);
    if(ret_attr1 != 0)
    {
        k_work_reschedule(&io_expander_error_work, K_NO_WAIT);
    }
    ret_attr1 = sensor_attr_get(dev_hdl_sensor, IO_EXPANDER_CHAN_DEVICE_DATA, IO_EXPANDER_ATTR_ALL_INPUT, &val);
    if(ret_attr1 != 0)
    {
        k_work_reschedule(&io_expander_error_work, K_NO_WAIT);
    }
    io_expander_pin_config.all_pin_last_state = val.val1;
    for(int i = 0; i < sizeof(key_map)/sizeof(key_map[0]); i++){
        io_expander_mgr_debounce_set(key_map[i],25,(val.val1>>key_map[i])&0x01);
    }
    DBG_LOGI(thisMOD,"io_expander_initial_pin_status = 0x%04X", io_expander_pin_config.all_pin_last_state);

}

void io_expander_mgr_deinit(void)
{
    if (dev_hdl_sensor == NULL){
        DBG_LOGI(thisMOD,"[HID]SENSOR_STATE_DEINIT, dev_hdl_sensor is NULL");
    }
    struct sensor_value val = {0, 0};
    int ret_attr1 = sensor_attr_set(dev_hdl_sensor, SENSOR_CHAN_ALL, IO_EXPANDER_ATTR_DEINIT, &val);
    DBG_LOGI(thisMOD,"[HID]SENSOR_STATE_DEINIT, ret_attr1 = %d", ret_attr1);
}
#endif //CONFIG_IO_EXPANDER_AW95124