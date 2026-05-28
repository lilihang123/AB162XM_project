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


#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include "app_wheel.h"
#include "app_usb_port.h"

#if defined (CONFIG_AIR_QDEC)
#include "qdec_airoha.h"
#endif

#if defined (CONFIG_AIR_COMP_WHEEL)
#include "hal_comparator.h"
#endif

#include "hal_gpio.h"
#include "hal_qdec.h"
#include "hal_eint_internal.h"

#include "app_state.h"
#include "app_battery.h"
#include "app_ccni.h"

#define thisMODULE wheel
#define thisMOD    "wheel"
#define ENC_POWER_EN_PIN 29
#define WHEEL_ON   0
#define WHEEL_OFF  1
LOG_MODULE_REGISTER(thisMODULE);
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
void app_wheel_init();
void app_wheel_enter_idle();
void app_wheel_enter_active();
//static void app_wheel_check();

static void app_wheel_get_sensor_pos_dz();
static void app_wheel__disable_eint_in_low_power();
static void app_wheel_enter_low_power_set_wakeup();
static void app_wheel_exit_low_power();

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
typedef enum{
    APP_WHEEL_STATE_NORMAL,
    APP_WHEEL_STATE_LOW_POWER
}T_APP_WHEEL_STATE;


#if defined (CONFIG_AIR_QDEC)
const static struct device *dev;
#endif
uint8_t  app_wheel_state = APP_WHEEL_STATE_NORMAL;
/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/
#if defined (CONFIG_AIR_SUPPORT_IR_COMP) || defined (CONFIG_AIR_QDEC)
static void app_wheel__announce_wheel_wakeup_event()
{
    struct evt_active_status* event = create_evt_active_status();
    if (event){
        event->active = true;
        event->type = WHEEL_WAKEUP;
        AF_EVT_SUBMIT(event);
    }
}
#endif

#if defined (CONFIG_AIR_QDEC)
void qdec_irq_callback()
{
    #if defined (AIR_SWLA_ENABLE)
    HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_app_wheel_wakeup, SWLA_DIRECTION_START);
    #endif

    APP_LOGI(thisMOD,"qdec_irq_callback");
    app_wheel__announce_wheel_wakeup_event();

    /* Latch clear hw data reg */
    sensor_sample_fetch(dev);

    #if defined (AIR_SWLA_ENABLE)
    HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_app_wheel_wakeup, SWLA_DIRECTION_STOP);
    #endif
}
#endif

/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
static bool app_wheel_evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state* event = (struct evt_app_state*)evt_header;
    APP_LOGI(thisMOD,"app_wheel_evt_app_state , event->app_state = %d \n ", event->app_state);

    switch (event->app_state)
    {
        case APP_STATE_CONNECT_PREPARING:
        {
            #if defined (CONFIG_AIR_COMP_WHEEL)
                hal_comp_trim_data_config();
            #endif
        }
        break;


        case APP_STATE_BT_PAIRING:
        case APP_STATE_2_4G_PAIRING:
        case APP_STATE_BT_RECONNECT:
        case APP_STATE_2_4G_RECONNECT:
        {
            #if defined(CONFIG_AIR_APP_STANDBY_WAKEUP_BY_WHEEL)
            int16_t number;
            int32_t z1;
            hal_qdec_get_data(&number);

            #if defined(CONFIG_AIR_HID_QDEC_DIR_REVERSE)
            z1 = -(int32_t)number;
            #else
            z1 = (int32_t)number;
            #endif

            APP_LOGI(thisMOD,"app_wheel_enter_active z1= %d \n ", z1);
            app_ccni_send_key_data_to_RISC_V_queue(1, z1);
            #endif

            app_wheel_enter_active();
        }
        break;

        case APP_STATE_STANDBY:
        {
            #if defined (CONFIG_AIR_APP_STANDBY_WITH_ADAPTOR_RGB)
            if(app_usb_port__get_usb_plug_status() != APP_USB_PLUG_OUT)
            {

            }
            else
            #endif
            {
                app_wheel_get_sensor_pos_dz();
                app_wheel_enter_idle();
                app_wheel_enter_low_power_set_wakeup();
                bool power_ok = app_battery__get_battery_power();
                if(!power_ok){
                    app_wheel__disable_eint_in_low_power();
                }
            }
        }
        break;

        case APP_STATE_USB_SUSPEND:
        {
            app_wheel_get_sensor_pos_dz();
            app_wheel_enter_idle();
        }
        break;

        default:
        break;
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_wheel_evt_conn_req(const struct af_evt_header *evt_header)
{
    struct evt_conn_req* event = (struct evt_conn_req*)evt_header;
    APP_LOGI(thisMOD,"app_wheel_evt_conn_req , cmd = %d", event->cmd);

    switch(event->cmd)
    {
        case CONN_REQ_ACTIVE:
        case CONN_REQ_ACTIVE_USB:
        {
            app_wheel_enter_active();
        }
        break;

        case CONN_REQ_IDLE_1:
        {
            app_wheel_enter_idle();
        }
        break;

        default:
        break;
    }

    return AF_TRAVERSE_NEXT;
}

#if defined (CONFIG_AIR_SUPPORT_IR_COMP)
static bool app_wheel_evt_riscv_wheel_status(const struct af_evt_header *evt_header)
{
    struct evt_riscv_wheel_status* event = (struct evt_riscv_wheel_status*)evt_header;
    APP_LOGI(thisMOD,"app_wheel_evt_riscv_wheel_status , wheel_status = %d", event->wheel_status);

    app_wheel__announce_wheel_wakeup_event();
    return AF_TRAVERSE_NEXT;
}
#endif

static bool app_wheel_evt_active_status(const struct af_evt_header *evt_header)
{
    struct evt_active_status* event = (struct evt_active_status*)evt_header;
    APP_LOGI(thisMOD,"app_wheel_evt_active_status, active = %d, type = %d", event->active, event->type);

    if(event->active && app_state_current_state() == APP_STATE_STANDBY)
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
                app_wheel_exit_low_power();
                break;
            }
            default:{
                break;
            }
        }
    }

    return AF_TRAVERSE_NEXT;
}

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
void app_wheel_enter_active()
{
    #if defined (CONFIG_AIR_QDEC)
    int ret;
    struct sensor_value attr_val_set = {false, 0};
    ret = sensor_attr_set(dev, SENSOR_CHAN_POS_DZ, QDEC_MODE_STATUS, &attr_val_set);
    APP_LOGI(thisMOD,"qdec_attr_set QDEC_MODE_STATUS = %d, ret = %d", attr_val_set.val1, ret);

    attr_val_set.val1 = false;
    attr_val_set.val2 = 0x2;
    ret = sensor_attr_set(dev, SENSOR_CHAN_POS_DZ, QDEC_Z_SUM_IRQ_CFG, &attr_val_set);
    APP_LOGI(thisMOD, "qdec_attr_set, z sum 1:enable/0:disable = %d, value = %d, ret = %d", attr_val_set.val1, attr_val_set.val2, ret);
    #endif
} 

void app_wheel_enter_idle()
{
    #if defined (CONFIG_AIR_QDEC)
    int ret;
    struct sensor_trigger trig = {
        .type = SENSOR_TRIG_MOTION,
        .chan = SENSOR_CHAN_POS_DZ,
    };

    ret = sensor_trigger_set(dev ,&trig, qdec_irq_callback);
    if (ret != 0)
    {
        APP_LOGI(thisMOD, "Failed to sensor_trigger_set (%d)\n", ret);
    }

    struct sensor_value attr_val_set = {true, 0};
    ret = sensor_attr_set(dev, SENSOR_CHAN_POS_DZ, QDEC_MODE_STATUS, &attr_val_set);
    APP_LOGI(thisMOD,"qdec_attr_set QDEC_MODE_STATUS = %d, ret = %d", attr_val_set.val1, ret);

    attr_val_set.val1 = true;
    attr_val_set.val2 = 0x1;
    ret = sensor_attr_set(dev,SENSOR_CHAN_POS_DZ, QDEC_Z_SUM_IRQ_CFG, &attr_val_set);
    APP_LOGI(thisMOD,"qdec_attr_set, z sum 1:enable/0:disable = %d, value = %d, ret = %d", attr_val_set.val1, attr_val_set.val2, ret);

    #endif
}

static void app_wheel_get_sensor_pos_dz()
{
    #if defined (CONFIG_AIR_QDEC)
    /* When pairing or reconnect timeout need to get value */
    int rc;
    struct sensor_value val;
    rc = sensor_channel_get(dev, SENSOR_CHAN_POS_DZ, &val);
    //APP_LOGI(thisMOD,"wheel data = %d", val.val1);
    #endif
    return;
}

static void app_wheel__disable_eint_in_low_power()
{
    #if defined (HAL_QDEC_MODULE_ENABLED) && !defined(CONFIG_AIR_M21_SAMPLE)
    hal_eint_disable(M_WHEEL_0);
    hal_eint_disable(M_WHEEL_1);
    #endif /* CONFIG_AIR_M21_SAMPLE */
    return;
}

static void app_wheel_enter_low_power_set_wakeup()
{
    // TODO: should be moved to middleware
    #if defined(CONFIG_AIR_APP_STANDBY_WAKEUP_BY_WHEEL)
    *(volatile uint32_t *)(0x421300e0) |= (1<<0);
    *(volatile uint32_t *)(0x421300e0) |= (1<<1);
    *(volatile uint32_t *)(0x42104038) |= (1<<0);
    *(volatile uint32_t *)(0x42104038) |= (1<<1);
    #endif

    if(app_wheel_state != APP_WHEEL_STATE_LOW_POWER)
    {
        APP_LOGI(thisMOD,"app_wheel_enter_low_power_set_wakeup");
        extern hal_gpio_status_t hal_gpio_wakeup_extend_sleep_config(hal_gpio_pin_t gpio_pin);
        #ifdef HAL_QDEC_MODULE_ENABLED
        #if !defined(CONFIG_AIR_APP_STANDBY_WAKEUP_BY_WHEEL)
        hal_qdec_enter_eint_mode(qdec_irq_callback);
        hal_qdec_backup();
        hal_qdec_disable();
        hal_gpio_wakeup_extend_sleep_config(M_WHEEL_0);
        hal_gpio_wakeup_extend_sleep_config(M_WHEEL_1);
        #endif /* CONFIG_AIR_APP_STANDBY_WAKEUP_BY_WHEEL */
        #endif
        app_wheel_state = APP_WHEEL_STATE_LOW_POWER;
    }

    return;
}

static void app_wheel_exit_low_power()
{
    if(app_wheel_state != APP_WHEEL_STATE_NORMAL)
    {
        APP_LOGI(thisMOD,"app_wheel_exit_low_power");
        extern hal_gpio_status_t hal_gpio_wakeup_extend_sleep_clear(hal_gpio_pin_t gpio_pin);
        #ifdef HAL_QDEC_MODULE_ENABLED
        #if !defined(CONFIG_AIR_APP_STANDBY_WAKEUP_BY_WHEEL)
        hal_qdec_exit_eint_mode();
        hal_qdec_enable();
        hal_qdec_restore();
        hal_gpio_wakeup_extend_sleep_clear(M_WHEEL_0);
        hal_gpio_wakeup_extend_sleep_clear(M_WHEEL_1);
        extern hal_gpio_status_t hal_gpio_set_rtc_in_en(hal_gpio_pin_t gpio_pin);
        hal_gpio_set_rtc_in_en(M_WHEEL_0);
        hal_gpio_set_rtc_in_en(M_WHEEL_1);
        #endif /* CONFIG_AIR_APP_STANDBY_WAKEUP_BY_WHEEL */
        #endif
        app_wheel_state = APP_WHEEL_STATE_NORMAL;
    }
    return;
}

#if 0
static void app_wheel_check()
{
    struct sensor_value attr_val_get;
    int ret;
    attr_val_get.val1 = 0;
    attr_val_get.val2 = 0;
    ret = sensor_attr_get(dev,SENSOR_CHAN_POS_DZ,QDEC_MODE_STATUS, &attr_val_get);
    if(ret != 0)
    {
        APP_LOGI(thisMOD,"zephyr get failed");
    }
    APP_LOGI(thisMOD,"attr_val_get,hw mode 0:active/1:idle = %d",attr_val_get.val1);

    attr_val_get.val1=0;
    attr_val_get.val2=0;
    ret = sensor_attr_get(dev,SENSOR_CHAN_POS_DZ,QDEC_Z_SUM_IRQ_CFG, &attr_val_get);
    if(ret != 0)
    {
    	APP_LOGI(thisMOD,"zephyr get failed");
    }
    APP_LOGI(thisMOD,"attr_val_get,z sum 1:enable/0:disable = %d, value = %d", attr_val_get.val1, attr_val_get.val2);
}
#endif


/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
void app_wheel_init()
{
    app_wheel_state = APP_WHEEL_STATE_NORMAL;

    /* LM7: ENC_POWER_EN (GPIO29)  active LOW */
    hal_gpio_init(ENC_POWER_EN_PIN);
    hal_pinmux_set_function(ENC_POWER_EN_PIN, 0);
    hal_gpio_set_direction(ENC_POWER_EN_PIN, HAL_GPIO_DIRECTION_OUTPUT);
    hal_gpio_set_output(ENC_POWER_EN_PIN, WHEEL_ON);
    APP_LOGI(thisMOD,"ENC_POWER_EN GPIO_%d set LOW (encoder power ON)", ENC_POWER_EN_PIN);

    #if defined (CONFIG_AIR_QDEC)
        dev = device_get_binding(DT_NODE_FULL_NAME(DT_NODELABEL(qdec)));
        if (!device_is_ready(dev)) {
            APP_LOGI(thisMOD,"Qdec device is not ready");
        }
        APP_LOGI(thisMOD,"app_wheel_init");

        struct sensor_value attr_val_set = {false, 0};
        int ret = sensor_attr_set(dev, SENSOR_CHAN_POS_DZ, QDEC_MODE_STATUS, &attr_val_set);

        APP_LOGI(thisMOD,"qdec_attr_set QDEC_MODE_STATUS = %d", ret);

    #elif defined (CONFIG_AIR_COMP_WHEEL)
        hal_comp_trim_data_config();
    #endif

    #if defined(CONFIG_AIR_HID_QDEC_DIR_REVERSE)
    APP_LOGI(thisMOD,"app_wheel_init CONFIG_AIR_HID_QDEC_DIR_REVERSE is true ");
    hid_common_set_app_feature(APP_FEATURE_QDEC_DIRECTION_REVERSE);
    #endif
}


/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_app_state, app_wheel_evt_app_state);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_active_status, app_wheel_evt_active_status);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_conn_req, app_wheel_evt_conn_req);

#if defined (CONFIG_AIR_SUPPORT_IR_COMP)
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_riscv_wheel_status, app_wheel_evt_riscv_wheel_status);
#endif
/*=============================================================================*/