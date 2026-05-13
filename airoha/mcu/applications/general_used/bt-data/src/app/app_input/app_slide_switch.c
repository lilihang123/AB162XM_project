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

#if defined (CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH)
#include <stdint.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>

#include "app_slide_switch.h"
#include "app_state.h"
#include "app_usb_port.h"
#include "app_battery.h"
#include "app_button.h"
#include "app_pin_config_structs.h"
#include "hal_gpio.h"
#include "hal_eint_internal.h"

#define thisMOD    "ss"
#define thisMODULE   ss
LOG_MODULE_REGISTER(thisMODULE);

#define USE_ZEPHYR_API  false

/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
#if USE_ZEPHYR_API
static const struct device* app_slide_switch_get_device(uint8_t pin);
#endif
void app_ss__check_mode_timer_cb(struct k_timer *timer_id);
static void app_slide_switch_timer_init();
void app_slide_switch__check_switch_mode_status(const struct device *dev, struct gpio_callback *cb, gpio_port_pins_t pins);

void app_ss_configure_gpio(uint8_t pin_number, struct gpio_callback *gp_cb);
void app_slide_switch__get_init_ss_type();
static void app_slide_switch__change_slide_switch_position(uint8_t mode);
static void app_slide_switch_enter_low_power_set_wakeup();
static void app_slide_switch_exit_low_power();
static void app_slide_switch__announce_ss_wakeup_event();
static bool app_slide_switch_check_ss_mode(uint8_t pins, hal_gpio_data_t gpio_level);
static void app_slide_switch_set_hid_flag();

/* timers defined ------------------------------------------------------------*/
K_TIMER_DEFINE(check_mode_timer, app_ss__check_mode_timer_cb, NULL);

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
typedef struct {
    struct gpio_callback cb;
    bool high_active;
    uint8_t gpio;
} app_slide_switch_info_t;

#if USE_ZEPHYR_API
const static struct device *gpio_dev0 = NULL;
const static struct device *gpio_dev1 = NULL;
#endif

struct gpio_callback ss_bt_mode_cb;
struct gpio_callback ss_gaming_mode_cb;

app_slide_switch_info_t ss_bt_handler = {
#if defined(CONFIG_AIR_SLIDE_SWITCH_BT_MODE_PIN_HIGH_ACTIVE)
    .gpio = CONFIG_AIR_SLIDE_SWITCH_BT_MODE_PIN,
    .high_active = CONFIG_AIR_SLIDE_SWITCH_BT_MODE_PIN_HIGH_ACTIVE
#else
    .gpio = CONFIG_AIR_SLIDE_SWITCH_BT_MODE_PIN,
    .high_active = 0
#endif
};

app_slide_switch_info_t ss_gaming_handler = {
#if defined(CONFIG_AIR_SLIDE_SWITCH_GAMING_PIN_HIGH_ACTIVE)
    .gpio = CONFIG_AIR_SLIDE_SWITCH_GAMING_MODE_PIN,
    .high_active = CONFIG_AIR_SLIDE_SWITCH_GAMING_PIN_HIGH_ACTIVE
#else
    .gpio = CONFIG_AIR_SLIDE_SWITCH_GAMING_MODE_PIN,
    .high_active = 0
#endif
};

uint32_t app_ss_gpio_pin = 0;
uint8_t app_ss_mode = SS_MODE_NONE;
uint8_t app_ss_low_power_state = 0; //0:NORMAL_MODE, 1:LOW_POWER_MODE

#define SS_DEBOUNCE_WITH_USB      10  //ms
#define SS_DEBOUNCE_WITHOUT_USB    1  //ms
#define SS_DEBOUNCE_EXTEND_SLEEP   0  //ms
uint8_t ss_debounce = SS_DEBOUNCE_WITHOUT_USB;

#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
bool app_ss_suspend_resume = false;
#endif
/******************************************************************************/
/* callback function                                                        */
/******************************************************************************/
void app_ss__check_mode_timer_cb(struct k_timer *timer_id)
{
    uint8_t new_pins = 0;

    #if USE_ZEPHYR_API
    while (app_ss_gpio_pin >>= 1){
        new_pins++;
    };

    const struct device* dev = app_slide_switch_get_device(new_pins);
    int gpio_level = 0;
    if (dev) {
        gpio_level = gpio_pin_get_raw(dev, new_pins);
    } else {
        APP_LOGI(thisMOD, "app_slide_switch_get_device fail!!");
    }

    bool is_bt = (new_pins == (ss_bt_handler.gpio % 32));
    bool is_gaming = (new_pins == (ss_gaming_handler.gpio % 32));
    if ((ss_bt_handler.gpio >= 32 && is_bt) ||
        (ss_gaming_handler.gpio >= 32 && is_gaming)) {
        new_pins += 32;
    }
    #else
    new_pins = app_ss_gpio_pin;
    hal_gpio_data_t gpio_level;
    hal_gpio_get_input(new_pins, &gpio_level);
    #endif
    APP_LOGI(thisMOD,"app_ss__check_mode_timer_cb, new_pins = %d, gpio_level = %d", new_pins, gpio_level);

    bool ret = app_slide_switch_check_ss_mode(new_pins, gpio_level);
    if(ret){
        return;
    }

    app_slide_switch_set_hid_flag();

    switch(app_ss_mode)
    {
        case SS_MODE_2_4G:
        {
            APP_LOGI(thisMOD,"Change to SS_MODE_2_4GAMING");
            app_slide_switch__change_slide_switch_position(SLIDE_SWITCH_POS_GAMING);
            break;
        }
        case SS_MODE_BT:
        {
            APP_LOGI(thisMOD, "Change to SS_MODE_BT");
            app_slide_switch__change_slide_switch_position(SLIDE_SWITCH_POS_BT);
            break;
        }
        case SS_MODE_OFF:
        {
            APP_LOGI(thisMOD,"Change to SS_MODE_OFF");
            app_slide_switch__change_slide_switch_position(SLIDE_SWITCH_POS_OFF);
            break;
        }
        default: {
            break;
        }
    }
}

void app_slide_switch__check_switch_mode_status(const struct device *dev, struct gpio_callback *cb, gpio_port_pins_t pins)
{
    app_ss_gpio_pin = pins;
    APP_LOGI(thisMOD, "app_slide_switch__check_switch_mode_status, pin = n, 2^n = %d", app_ss_gpio_pin);

    uint32_t state = app_state_current_state();
    if((state == APP_STATE_STANDBY)
        #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
        || (state == APP_STATE_2_4G_RECONNECT_RESUME_WAIT)
        #endif
    ){
        app_ss__check_mode_timer_cb(&check_mode_timer);
    }
    else{
        k_timer_stop(&check_mode_timer);
        k_timer_start(&check_mode_timer, K_MSEC(500) , K_NO_WAIT);
    }
}

void app_slide_switch__get_ss_type(uint8_t *ss_type)
{
    *ss_type =  app_ss_mode;
    APP_LOGI(thisMOD, "app_slide_switch__get_ss_type, ss_type = %d", *ss_type);
}

void slide_switch_eint_callback(void *id)
{
    app_ss_gpio_pin = *(uint8_t*)id;
    APP_LOGI(thisMOD, "slide_switch_eint_callback, id = 0x%X, ss_debounce = %d", app_ss_gpio_pin, ss_debounce);

#if defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    if(app_usb_port__get_usb_plug_status()){
        k_timer_stop(&check_mode_timer);
        k_timer_start(&check_mode_timer, K_MSEC(500) , K_NO_WAIT);
    } else {
        app_ss__check_mode_timer_cb(&check_mode_timer);
    }
#else
    uint32_t state = app_state_current_state();
    if(state == APP_STATE_STANDBY
        #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
        || (state == APP_STATE_2_4G_RECONNECT_RESUME_WAIT)
        #endif /* CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE */
    ){
        app_ss__check_mode_timer_cb(&check_mode_timer);
    }
    else{
        k_timer_stop(&check_mode_timer);
        k_timer_start(&check_mode_timer, K_MSEC(500) , K_NO_WAIT);
    }
#endif
}

/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
static bool app_slide_switch_evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state* event = (struct evt_app_state*)evt_header;
    APP_LOGI(thisMOD,"app_slide_switch_evt_app_state , event->app_state = %d \n ", event->app_state);

    switch (event->app_state)
    {
        #if defined(CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE)
        case APP_STATE_2_4G_CONNECTED_ACTIVE:
        {
            if(app_ss_suspend_resume)
            {
                app_slide_switch_exit_low_power();
                app_ss_suspend_resume = false;
            }
        }
        break;
        #endif /* CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE */

        #if defined(CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE)
        case APP_STATE_2_4G_RECONNECT_RESUME_WAIT:
        {
            app_ss_suspend_resume = true;
        }
        #endif /* CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE */
        case APP_STATE_STANDBY:
        {
            bool power_ok = app_battery__get_battery_power();
            if(!power_ok){
                break;
            }
            app_slide_switch_enter_low_power_set_wakeup();
        }
        break;

        default:
        break;
    }
    return AF_TRAVERSE_NEXT;
}

static bool app_slide_switch_evt_active_status(const struct af_evt_header *evt_header)
{
    struct evt_active_status* event = (struct evt_active_status*)evt_header;
    APP_LOGI(thisMOD,"app_slide_switch_evt_active_status, active = %d, type = %d", event->active, event->type);
    uint32_t app_state = app_state_current_state();

    if(event->active && ((app_state == APP_STATE_STANDBY)
            #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
            || (app_state == APP_STATE_2_4G_RECONNECT_RESUME_WAIT)
            #endif
    ))
    {
        switch(event->type)
        {
            case MOTION_SENSOR_WAKEUP:
            case WHEEL_WAKEUP:
            case KEY_WAKEUP:
            #if defined (CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH)
            case SLIDE_SWITCH_WAKEUP:
            #endif
            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
            case USB_PLUG_WAKEUP:
            #endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/
            {
                app_slide_switch_exit_low_power();
                #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
                if(app_ss_suspend_resume == true)
                {
                    app_ss_suspend_resume = false;
                }
                #endif
                break;
            }
            default:{
                break;
            }
        }
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_slide_switch_evt_usb_status(const struct af_evt_header *evt_header)
{
    struct evt_usb_status* event = (struct evt_usb_status*)evt_header;
    APP_LOGI(thisMOD,"app_slide_switch_evt_usb_status, status = %d, ss_debounce = %d", event->status, ss_debounce);

    switch(event->status)
    {
        case USB_STATUS_PLUGGED_OUT:
        {
            if(ss_debounce != SS_DEBOUNCE_WITHOUT_USB) {
                ss_debounce = SS_DEBOUNCE_WITHOUT_USB;
                hal_eint_set_debounce_time(ss_bt_handler.gpio, ss_debounce);
                hal_eint_set_debounce_time(ss_gaming_handler.gpio, ss_debounce);
            }
            break;
        }
        case USB_STATUS_PLUGGED_IN:
        {
            if(ss_debounce != SS_DEBOUNCE_WITH_USB) {
                ss_debounce = SS_DEBOUNCE_WITH_USB;
                hal_eint_set_debounce_time(ss_bt_handler.gpio, ss_debounce);
                hal_eint_set_debounce_time(ss_gaming_handler.gpio, ss_debounce);
            }
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
#if USE_ZEPHYR_API
static const struct device* app_slide_switch_get_device(uint8_t pin)
{
    uint8_t is_gpio_bt = ((ss_bt_handler.gpio % 32) == (pin % 32));
    uint8_t is_gpio_gaming = ((ss_gaming_handler.gpio % 32) == (pin % 32));

    if (is_gpio_bt){
        return (ss_bt_handler.gpio < 32) ? gpio_dev0 : gpio_dev1;
    }
    else if (is_gpio_gaming){
        return (ss_gaming_handler.gpio < 32) ? gpio_dev0 : gpio_dev1;
    }

    return NULL;
}
#endif

static void app_slide_switch_timer_init()
{
    k_timer_init(&check_mode_timer, app_ss__check_mode_timer_cb, NULL);
}

bool app_ss_gpio_init(T_SLIDE_SWITCH_PIN_S *slide_switch_ptr)
{
    APP_LOGI(thisMOD, "app_ss_gpio_init start");

    #if USE_ZEPHYR_API
    if(ss_bt_handler.gpio < 32 || ss_gaming_handler.gpio < 32)
    {
        gpio_dev0 = device_get_binding(DEVICE_DT_NAME(DT_NODELABEL(gpio0)));
        if (gpio_dev0 == NULL) {
            APP_LOGI(thisMOD, "Failed to bind gpio_dev0");
        }
    }
    if(ss_bt_handler.gpio >= 32 || ss_gaming_handler.gpio >= 32)
    {
        gpio_dev1 = device_get_binding(DEVICE_DT_NAME(DT_NODELABEL(gpio32)));
        if (gpio_dev1 == NULL) {
            APP_LOGI(thisMOD, "Failed to bind gpio_dev1");
        }
    }
    #endif

    #if defined(CONFIG_AIR_APP_PIN_USAGE_LIST)
    void configure_handler(app_slide_switch_info_t *handler, uint8_t pin, struct gpio_callback cb) {
        handler->cb = cb;
        handler->gpio = pin;
        app_ss_configure_gpio(pin, &handler->cb);
    }
    #else
    void configure_handler(app_slide_switch_info_t *handler, struct gpio_callback cb) {
        handler->cb = cb;
        app_ss_configure_gpio(handler->gpio, &handler->cb);
    }
    #endif /* CONFIG_AIR_APP_PIN_USAGE_LIST */

    #if defined(CONFIG_AIR_APP_PIN_USAGE_LIST)
    if (slide_switch_ptr)
    {
        APP_LOGI(thisMOD, "slide_switch_ptr->ss_bt_mode = %d, slide_switch_ptr->ss_2_4G_mode = %d",
                slide_switch_ptr->ss_bt_mode, slide_switch_ptr->ss_2_4G_mode);

        configure_handler(&ss_bt_handler, slide_switch_ptr->ss_bt_mode, ss_bt_mode_cb);
        configure_handler(&ss_gaming_handler, slide_switch_ptr->ss_2_4G_mode, ss_bt_mode_cb);
    }
    else
    #else
    {
        APP_LOGI(thisMOD, "ss_bt_handler.gpio = %d, ss_gaming_handler.gpio = %d", ss_bt_handler.gpio, ss_gaming_handler.gpio);
        if (ss_bt_handler.gpio == ss_gaming_handler.gpio)
        {
            if(ss_bt_handler.high_active ^ ss_gaming_handler.high_active){
                if(ss_bt_handler.high_active){
                    configure_handler(&ss_bt_handler, ss_bt_mode_cb);
                }
                else{
                    configure_handler(&ss_gaming_handler, ss_gaming_mode_cb);
                }
            }
            else{
                assert(0 && "If ss controled by 1 gpio, need to set just one pin as high active !");
            }
        }
        else
        {
            if((ss_bt_handler.high_active ^ ss_gaming_handler.high_active) == 0 && !ss_bt_handler.high_active){
                configure_handler(&ss_bt_handler, ss_bt_mode_cb);
                configure_handler(&ss_gaming_handler, ss_gaming_mode_cb);
            }
            else{
                assert(0 && "If ss controled by 2 gpios, need to set two active level low!");
            }
        }
    }
    #endif /* CONFIG_AIR_APP_PIN_USAGE_LIST */

    app_slide_switch__get_init_ss_type();

    return (app_ss_mode == 0);
}

void app_ss_configure_gpio(uint8_t pin_number, struct gpio_callback *gpio_cb)
{
    #if USE_ZEPHYR_API
    const struct device* dev = app_slide_switch_get_device(pin_number);
    if (dev) {
        gpio_pin_interrupt_configure(dev, (pin_number % 32), GPIO_INT_ENABLE | GPIO_INT_MODE_EDGE | GPIO_INT_TRIG_BOTH);
    } else {
        APP_LOGE(thisMOD, "app_ss_configure_gpio: device not found for pin %d", pin_number);
        return;
    }
    gpio_init_callback(gpio_cb, app_slide_switch__check_switch_mode_status, BIT(pin_number % 32));
    int ret = gpio_add_callback(dev, gpio_cb);
    if(ret){
        APP_LOGE(thisMOD, "app_ss_gpio_init, gpio %d with error, ret = %d", pin_number, ret);
    }
    else{
        APP_LOGI(thisMOD, "app_ss_gpio_init, gpio %d, cb = 0x%x ok!!!", pin_number, gpio_cb);
    }
    #else

    hal_eint_status_t ret_log[3];
    hal_eint_config_t eint_config;
    eint_config.trigger_mode = HAL_EINT_EDGE_FALLING_AND_RISING;
    eint_config.debounce_time = SS_DEBOUNCE_WITHOUT_USB;

    ret_log[0] = hal_eint_init(pin_number, &eint_config);
    if(pin_number == ss_bt_handler.gpio){
        ret_log[1] = hal_eint_register_callback(pin_number, slide_switch_eint_callback, (void*)&ss_bt_handler.gpio);
    }
    else{
        ret_log[1] = hal_eint_register_callback(pin_number, slide_switch_eint_callback, (void*)&ss_gaming_handler.gpio);
    }

    hal_eint_enable(pin_number);
    ret_log[2] = hal_eint_unmask(pin_number);

    APP_LOGI(thisMOD, "hal_eint_init = %d, hal_eint_register_callback = %d, hal_eint_unmask = %d"
        , ret_log[0]
        , ret_log[1]
        , ret_log[2]
        );
    #endif
}

void app_slide_switch__get_init_ss_type()
{
    int gpio_level_bt = 0;
    int gpio_level_gaming = 0;

    #if USE_ZEPHYR_API
    const struct device* dev_bt = app_slide_switch_get_device(ss_bt_handler.gpio);
    gpio_level_bt = dev_bt ? gpio_pin_get_raw(dev_bt, ss_bt_handler.gpio % 32) : -1;

    const struct device* dev_gaming = app_slide_switch_get_device(ss_gaming_handler.gpio);
    gpio_level_gaming = dev_gaming ? gpio_pin_get_raw(dev_gaming, ss_gaming_handler.gpio % 32) : -1;
    #else
    hal_gpio_data_t bt_level;
    hal_gpio_get_input(ss_bt_handler.gpio, &bt_level);
    gpio_level_bt = bt_level;

    hal_gpio_data_t gaming_level;
    hal_gpio_get_input(ss_gaming_handler.gpio, &gaming_level);
    gpio_level_gaming = gaming_level;
    #endif

    APP_LOGI(thisMOD, "gpio_level bt = %d, gaming = %d", gpio_level_bt, gpio_level_gaming);
    if(gpio_level_bt < 0 || gpio_level_gaming < 0)
    {
        APP_LOGE(thisMOD, "gpio_pin_get_raw fail!!!");
        return;
    }

    /* Map gpio levels to a bit status:
        if bt_active_hign = n:  0/1 -> SS_MODE_BT/ SS_MODE_2_4G
        if bt_active_hign = y:  1/0 -> SS_MODE_BT/ SS_MODE_2_4G

    Map gpio levels to a 2-bit status(bt/gaming):
        if both active_high = n  /     active_high = y
            0/0 -> SS_MODE_NONE  / 0/0 -> SS_MODE_OFF
            0/1 -> SS_MODE_BT    / 0/1 -> SS_MODE_2_4G
            1/0 -> SS_MODE_2_4G  / 1/0 -> SS_MODE_BT
            1/1 -> SS_MODE_OFF   / 1/1 -> SS_MODE_NONE
    */

    int status = ((gpio_level_bt != 0) << 1) | (gpio_level_gaming != 0);
    const int *mode_lookup;
    static const int lookup_bt[4] = {SS_MODE_NONE, SS_MODE_BT, SS_MODE_2_4G, SS_MODE_OFF};
    static const int lookup_gaming[4] = {SS_MODE_OFF, SS_MODE_2_4G, SS_MODE_BT, SS_MODE_NONE};

    if (ss_bt_handler.high_active) {
        mode_lookup = lookup_gaming;
    }
    else {
        mode_lookup = lookup_bt;
    }
    app_ss_mode = mode_lookup[status];

    APP_LOGI(thisMOD, "app_slide_switch__get_init_ss_type, ss_type = %d", app_ss_mode);
}

static void app_slide_switch__announce_usb_status_event(uint8_t status)
{
    struct evt_usb_status* event = create_evt_usb_status();
    if(event) {
        event->status = status;
        AF_EVT_SUBMIT(event);
    }
}

static void app_slide_switch__change_slide_switch_position(uint8_t mode)
{
    APP_LOGI(thisMOD,"app_slide_switch__change_slide_switch_position, mode = %d", mode);
    #if defined (CONFIG_AIR_USB_PLUG_AND_PLAY)
    if(app_state_check(TYPE_IN_USB_STATES)){
        APP_LOGI(thisMOD,"You plugged in the USB, cannot change mode, because of CONFIG_AIR_USB_PLUG_AND_PLAY=y", mode);
        return;
    }
    #endif /* _CONFIG_AIR_USB_PLUG_AND_PLAY_ */

    if(mode == SLIDE_SWITCH_POS_OFF){
        goto _switch_pos;
    }
    #if defined(CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF)
    else if(app_button_get_power_off_status())
    {
        if(app_state_check(TYPE_IN_USB_STATES)){
            goto _switch_pos;
        }
        else if(app_usb_port__get_usb_plug_status()){
            app_slide_switch__announce_usb_status_event(USB_STATUS_READY_TO_DISABLE);
        }
        return;
    }
    #else
    else {
        app_slide_switch__announce_usb_status_event(USB_STATUS_READY_TO_DISABLE);
    }
    #endif /* CONFIG_AIR_SUPPORT_BTN_POWER_ON_OFF */

    uint8_t app_state = app_state_current_state();
    if((app_state == APP_STATE_STANDBY)
        #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
        || (app_state == APP_STATE_2_4G_RECONNECT_RESUME_WAIT)
        #endif /* CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE */
    ){
        app_slide_switch__announce_ss_wakeup_event();
    }

_switch_pos:
    struct evt_slide_switch_status* event = create_evt_slide_switch_status();

    if (event)
    {
        event->position = mode;
        AF_EVT_SUBMIT(event);
    }
}

static void app_slide_switch__announce_ss_wakeup_event()
{
    struct evt_active_status* event = create_evt_active_status();
    if (event){
        event->active = true;
        event->type = SLIDE_SWITCH_WAKEUP;
        AF_EVT_SUBMIT(event);
    }
}

static void app_slide_switch_enter_low_power_set_wakeup()
{
    APP_LOGI(thisMOD,"app_slide_switch_enter_low_power_set_wakeup, low_power_state = %d", app_ss_low_power_state);
    if(!app_ss_low_power_state)
    {
        extern hal_gpio_status_t hal_gpio_wakeup_extend_sleep_config(hal_gpio_pin_t gpio_pin);
        hal_gpio_wakeup_extend_sleep_config(ss_bt_handler.gpio);
        hal_gpio_wakeup_extend_sleep_config(ss_gaming_handler.gpio);
        ss_debounce = SS_DEBOUNCE_EXTEND_SLEEP;
        hal_eint_set_debounce_time(ss_bt_handler.gpio, ss_debounce);
        hal_eint_set_debounce_time(ss_gaming_handler.gpio, ss_debounce);
        APP_LOGI(thisMOD,"app_slide_switch_enter_low_power_set_wakeup, hal_eint_set_debounce_time = %d", ss_debounce);
        app_ss_low_power_state = 1;
    }
    APP_LOGI(thisMOD,"[EINT_STA]= 0x%08X, [EINT_STA1]= 0x%08X", (unsigned int)(*(volatile uint32_t*)0x42140300), (unsigned int)(*(volatile uint32_t*)0x42140304));
    APP_LOGI(thisMOD,"[EINT_MASK]= 0x%08X, [EINT_MASK1]= 0x%08X", (unsigned int)(*(volatile uint32_t*)0x42140114), (unsigned int)(*(volatile uint32_t*)0x42140118));
    APP_LOGI(thisMOD,"[EINT_WAKEUP_MASK]= 0x%08X, [EINT_WAKEUP_MASK1]= 0x%08X", (unsigned int)(*(volatile uint32_t*)0x4214011C), (unsigned int)(*(volatile uint32_t*)0x42140120));
    APP_LOGI(thisMOD,"[RTC_IN_EN0]= 0x%08X, [RTC_IN_EN1]= 0x%08X", (unsigned int)(*(volatile uint32_t*)0x420C00E0), (unsigned int)(*(volatile uint32_t*)0x420D00F0));
}

static void app_slide_switch_exit_low_power()
{
    APP_LOGI(thisMOD,"app_slide_switch_exit_low_power, low_power_state = %d", app_ss_low_power_state);
    if(app_ss_low_power_state)
    {
        extern hal_gpio_status_t hal_gpio_wakeup_extend_sleep_clear(hal_gpio_pin_t gpio_pin);
        hal_gpio_wakeup_extend_sleep_clear(ss_bt_handler.gpio);
        hal_gpio_wakeup_extend_sleep_clear(ss_gaming_handler.gpio);
        if(app_usb_port__get_usb_plug_status()){
            ss_debounce = SS_DEBOUNCE_WITH_USB;
        } else{
            #ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
            uint32_t state = app_state_current_state();
            if((state == APP_STATE_2_4G_RECONNECT_RESUME_WAIT)){
                ss_debounce = SS_DEBOUNCE_EXTEND_SLEEP;
            } else
            #endif /* CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE */
            {
                ss_debounce = SS_DEBOUNCE_WITHOUT_USB;
            }
        }
        hal_eint_set_debounce_time(ss_bt_handler.gpio, ss_debounce);
        hal_eint_set_debounce_time(ss_gaming_handler.gpio, ss_debounce);
        APP_LOGI(thisMOD,"app_slide_switch_exit_low_power, hal_eint_set_debounce_time = %d", ss_debounce);
        app_ss_low_power_state = 0;
    }
}

static bool app_slide_switch_check_ss_mode(uint8_t pins, hal_gpio_data_t gpio_level)
{
    bool is_bt = (pins == ss_bt_handler.gpio);
    bool is_gm = (pins == ss_gaming_handler.gpio);

    // 1 GPIO case
    if(ss_bt_handler.gpio == ss_gaming_handler.gpio)
    {
        if((gpio_level == 0 && is_bt && ss_bt_handler.high_active == 0) ||
            (gpio_level == 1 && is_gm && ss_gaming_handler.high_active)) {
            app_ss_mode = SS_MODE_BT;
        }
        else if((gpio_level == 0 && is_gm && ss_gaming_handler.high_active == 0) ||
                (gpio_level == 1 && is_bt && ss_bt_handler.high_active)) {
            app_ss_mode = SS_MODE_2_4G;
        }
        return 0;
    }

    // 2 GPIO case
    bool is_active_high = ss_bt_handler.high_active;
    bool switch_in = is_active_high ? gpio_level : !gpio_level;

    if (switch_in)
    {
        if(is_bt){
            app_ss_mode = SS_MODE_BT;
        }
        else if(is_gm){
            app_ss_mode = SS_MODE_2_4G;
        }
        else
        {
            APP_LOGI(thisMOD, "gpio_level = %d, pins = %d", gpio_level, pins);
            return 1;
        }
    }
    else
    {
        if(!app_state_check(TYPE_IN_USB_STATES)){
            app_ss_mode = SS_MODE_OFF;
        }
        else
        {
            APP_LOGI(thisMOD, "Already in USB state in check_switch_mode_status");
            return 1;
        }
    }
    return 0;
}

static void app_slide_switch_set_hid_flag()
{
    switch(app_ss_mode)
    {
        case SS_MODE_2_4G:  //3
        {
            hid_common_set_hid_exp_flag(FLAG_BIT_SLIDE_SWITCH_POS);
            hid_common_set_hid_exp_flag(FLAG_BIT2_SLIDE_SWITCH_POS);
            break;
        }
        case SS_MODE_BT:  //2
        {
            hid_common_clear_hid_exp_flag(FLAG_BIT_SLIDE_SWITCH_POS);
            hid_common_set_hid_exp_flag(FLAG_BIT2_SLIDE_SWITCH_POS);
            break;
        }
        case SS_MODE_OFF:  //1
        {
            hid_common_set_hid_exp_flag(FLAG_BIT_SLIDE_SWITCH_POS);
            hid_common_clear_hid_exp_flag(FLAG_BIT2_SLIDE_SWITCH_POS);
            break;
        }
        default: {
            break;
        }
    }
    APP_LOGI(thisMOD, "app_slide_switch_set_hid_flag = %d", SLIDE_SWITCH_POSITION(hid_common->hid.flags));
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
uint8_t app_slide_switch_init(T_SLIDE_SWITCH_PIN_S * slide_switch_pin_ptr)
{
    static uint8_t init_flag = 1;
    if(init_flag)
    {
        app_slide_switch_timer_init();

        T_SLIDE_SWITCH_PIN_S *slide_switch_ptr = slide_switch_pin_ptr;
        int ret = app_ss_gpio_init(slide_switch_ptr);

        if(ret){
            APP_LOGE(thisMOD, "app_ss_gpio_init with error, ret = %d", ret);
        }

        APP_LOGI(thisMOD, "app_ss_gpio_init ok");
        init_flag = 0;
    }

    return app_ss_mode;
}

/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_active_status, app_slide_switch_evt_active_status);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_app_state, app_slide_switch_evt_app_state);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_usb_status, app_slide_switch_evt_usb_status);

/*=============================================================================*/

#endif /* _CONFIG_AIR_TRIPLE_MODE_SLIDE_SWITCH_ */
