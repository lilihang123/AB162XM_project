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
#define DT_DRV_COMPAT airoha_air_gpio

#include <string.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/gpio/gpio_utils.h>
#include <hal_gpio.h>
#include <hal_eint.h>
#include <hal_eint_internal.h>
#include <hal_gpio_internal.h>

#if IS_ENABLED(CONFIG_AIR_PINCTRL)
#include <zephyr/drivers/pinctrl.h>
#endif

struct gpio_airoha_data {
    /* gpio_driver_data needs to be first */
    struct gpio_driver_data common;

    sys_slist_t callbacks;
};
extern hal_gpio_status_t hal_gpio_get_input_port(int port, uint32_t *value);
extern hal_gpio_status_t hal_gpio_set_output_port(int port, uint32_t mask,uint32_t value);
extern hal_gpio_status_t hal_gpio_set_output_toggle(int port, uint32_t mask);
struct gpio_airoha_cfg {
    /* gpio_driver_config needs to be first */
    struct gpio_driver_config common;
    uint32_t debounce_time;
    uint8_t port_num;
#if IS_ENABLED(CONFIG_AIR_PINCTRL)
    const struct pinctrl_dev_config *pincfg;
#endif
};
extern uint8_t g_debounce[HAL_EINT_NUMBER_MAX];

typedef struct {
    struct device        *user_port;
    struct gpio_callback *call_back;
} airoha_eint_info_t;

airoha_eint_info_t eint_info[HAL_EINT_NUMBER_MAX];

void gpio_airoha_callback(void *user_data){
    airoha_eint_info_t eint_info =  *(airoha_eint_info_t *)user_data;
    if(eint_info.call_back->handler != NULL){
        eint_info.call_back->handler(eint_info.user_port,eint_info.call_back,eint_info.call_back->pin_mask);
    }
}


static inline struct gpio_airoha_data *get_port_data(const struct device *port)
{
    return port->data;
}

static inline const struct gpio_airoha_cfg *get_port_cfg(const struct device *port)
{
    return port->config;
}

static int gpio_airoha_pin_configure(const struct device *port, gpio_pin_t pin,
                   gpio_flags_t flags)
{
    if(flags & GPIO_INPUT){
        hal_gpio_set_direction(pin,HAL_GPIO_DIRECTION_INPUT);
    }
    if(flags & GPIO_OUTPUT){
        hal_gpio_set_direction(pin,HAL_GPIO_DIRECTION_OUTPUT);
    }
    if(flags & GPIO_OUTPUT_INIT_LOW){
        hal_gpio_set_output(pin,HAL_GPIO_DATA_LOW);
    }
    if(flags & GPIO_OUTPUT_INIT_HIGH){
        hal_gpio_set_output(pin,HAL_GPIO_DATA_HIGH);
    }
    if(flags & GPIO_PULL_UP){
        hal_gpio_pull_up(pin);
    }
    if(flags & GPIO_PULL_DOWN){
        hal_gpio_pull_down(pin);
    }
    return 0;
}

static int gpio_airoha_port_get_raw(const struct device *port,
                  gpio_port_value_t *value)
{
    uint8_t port_number = get_port_cfg(port)->port_num ;
    hal_gpio_get_input_port(port_number,value);
    return 0;
}

static int gpio_airoha_port_set_masked_raw(const struct device *port,
                     gpio_port_pins_t mask,
                     gpio_port_value_t value)
{

    uint8_t port_number = get_port_cfg(port)->port_num ;
    hal_gpio_set_output_port(port_number,mask,value);
    return 0;
}

static int gpio_airoha_port_set_bits_raw(const struct device *port,
                       gpio_port_pins_t mask)
{
    uint8_t port_number = get_port_cfg(port)->port_num ;
    hal_gpio_set_output_port(port_number,mask,1);
    return 0;
}

static int gpio_airoha_port_clear_bits_raw(const struct device *port,
                     gpio_port_pins_t mask)
{
    uint8_t port_number = get_port_cfg(port)->port_num ;
    hal_gpio_set_output_port(port_number,mask,0);
    return 0;
}

static int gpio_airoha_port_toggle_bits(const struct device *port,
                      gpio_port_pins_t mask)
{

    uint8_t port_number = get_port_cfg(port)->port_num;
    hal_gpio_set_output_toggle(port_number,mask);
    return 0;
}

static int gpio_airoha_pin_interrupt_configure(const struct device *port,
                         gpio_pin_t pin,
                         enum gpio_int_mode mode,
                         enum gpio_int_trig trig)
{
    uint8_t port_number = get_port_cfg(port)->port_num;
    uint8_t pin_num = port_number*32+pin;
    if(mode  == GPIO_INT_MODE_DISABLED){
        hal_eint_deinit(pin_num);
        hal_pinmux_set_function(pin_num,0);
    }
    else{
        uint32_t time = g_debounce[pin_num];
        hal_eint_config_t eint_config;
        eint_config.debounce_time = time;
        if((mode == GPIO_INT_MODE_LEVEL) && (trig  == GPIO_INT_TRIG_LOW)){
            eint_config.trigger_mode = HAL_EINT_LEVEL_LOW;
        }
        if((mode == GPIO_INT_MODE_LEVEL) && (trig  == GPIO_INT_TRIG_HIGH)){

            eint_config.trigger_mode = HAL_EINT_LEVEL_HIGH;
        }
        if((mode == GPIO_INT_MODE_EDGE) && (trig  == GPIO_INT_TRIG_LOW)){
            eint_config.trigger_mode = HAL_EINT_EDGE_FALLING;
        }
        if((mode == GPIO_INT_MODE_EDGE) && (trig  == GPIO_INT_TRIG_HIGH)){
            eint_config.trigger_mode = HAL_EINT_EDGE_RISING;
        }
        if((mode == GPIO_INT_MODE_EDGE) && (trig  == GPIO_INT_TRIG_BOTH)){
            eint_config.trigger_mode = HAL_EINT_EDGE_FALLING_AND_RISING;
        }
        hal_pinmux_set_function(pin_num,12);                //eint mode 12
        hal_eint_mask(pin_num);
        hal_eint_enable(pin_num);
        hal_eint_init(pin_num,&eint_config);
    }
    return 0;
}

static int gpio_airoha_manage_callback(const struct device *port,
                     struct gpio_callback *callback,
                     bool set)
{
    uint8_t port_number = get_port_cfg(port)->port_num;
    for(int i=0;i<=31;i++){
        if(callback->pin_mask & (1<<i)){
            uint8_t pin_num = i+port_number*32;
            eint_info[pin_num].call_back =  callback;
            eint_info[pin_num].user_port = (struct device *)port;
            hal_eint_register_callback(pin_num,gpio_airoha_callback,&eint_info[pin_num]);
            hal_eint_unmask(pin_num);
        }
    }
    return 0;
}

#if IS_ENABLED(CONFIG_AIR_PINCTRL)
void pinctrl_state_change(const struct device *port,uint8_t status){
    const struct gpio_airoha_cfg *dev_config = port->config;
    pinctrl_apply_state(dev_config->pincfg, status);
}
#endif

static int gpio_airoha_init(const struct device *port)
{
    // GPIO_BASE_REGISTER_T *base_reg = get_port_cfg(port)->base;
    // GPIO_CFG0_REGISTER_T *cfg0_reg = get_port_cfg(port)->cfg0;
    // GPIO_CFG1_REGISTER_T *cfg1_reg = get_port_cfg(port)->cfg1;
    // EINT_REGISTER_T *eint_reg = get_port_cfg(port)->eint_base;
    // hal_gpio_set_address(base_reg,cfg0_reg,cfg1_reg);
    // hal_eint_set_address(eint_reg);
    hal_gpio_driver_init();
#if IS_ENABLED(CONFIG_AIR_PINCTRL)
    const struct gpio_airoha_cfg *dev_config = port->config;
    pinctrl_apply_state(dev_config->pincfg, PINCTRL_STATE_DEFAULT);
#endif
    return 0;
}

static const struct gpio_driver_api gpio_airoha_drv_api_funcs = {
    .pin_configure = gpio_airoha_pin_configure,
    .port_get_raw = gpio_airoha_port_get_raw,
    .port_set_masked_raw = gpio_airoha_port_set_masked_raw,
    .port_set_bits_raw = gpio_airoha_port_set_bits_raw,
    .port_clear_bits_raw = gpio_airoha_port_clear_bits_raw,
    .port_toggle_bits = gpio_airoha_port_toggle_bits,
    .pin_interrupt_configure = gpio_airoha_pin_interrupt_configure,
    .manage_callback = gpio_airoha_manage_callback,
};

/* Device instantiation is done with node labels because 'port_num' is
 * the peripheral number by SoC numbering. We therefore cannot use
 * DT_INST APIs here without wider changes.
 */
#if IS_ENABLED(CONFIG_AIR_PINCTRL)
    #define GPIO_AIROHA_DEVICE(id)                        \
                                                \
        PINCTRL_DT_INST_DEFINE(id);				\
                                                \
        static const struct gpio_airoha_cfg gpio_airoha_p##id##_cfg = {    \
            .common = {                        \
                .port_pin_mask =                \
                GPIO_PORT_PIN_MASK_FROM_DT_INST(id),        \
            }, \
            .port_num = DT_INST_PROP(id, port),        \
            .debounce_time = DT_INST_PROP(id, debounce),        \
            .pincfg = PINCTRL_DT_INST_DEV_CONFIG_GET(id),    \
        };                                \
                                        \
        static struct gpio_airoha_data gpio_airoha_p##id##_data;        \
                                        \
        DEVICE_DT_INST_DEFINE(id, gpio_airoha_init,            \
                NULL,                        \
                &gpio_airoha_p##id##_data,            \
                &gpio_airoha_p##id##_cfg,            \
                CONFIG_GPIO_INIT_LEVEL,                    \
                CONFIG_GPIO_INIT_PRIORITY,            \
                &gpio_airoha_drv_api_funcs);
#else
    #define GPIO_AIROHA_DEVICE(id)                        \
    static const struct gpio_airoha_cfg gpio_airoha_p##id##_cfg = {    \
        .common = {                        \
            .port_pin_mask =                \
            GPIO_PORT_PIN_MASK_FROM_DT_INST(id),        \
        }, \
        .port_num = DT_INST_PROP(id, port),        \
        .debounce_time = DT_INST_PROP(id, debounce),        \
    };                                \
                                    \
    static struct gpio_airoha_data gpio_airoha_p##id##_data;        \
                                    \
    DEVICE_DT_INST_DEFINE(id, gpio_airoha_init,            \
             NULL,                        \
             &gpio_airoha_p##id##_data,            \
             &gpio_airoha_p##id##_cfg,            \
             CONFIG_GPIO_INIT_LEVEL,                    \
             CONFIG_GPIO_INIT_PRIORITY,            \
             &gpio_airoha_drv_api_funcs);
#endif


DT_INST_FOREACH_STATUS_OKAY(GPIO_AIROHA_DEVICE)

