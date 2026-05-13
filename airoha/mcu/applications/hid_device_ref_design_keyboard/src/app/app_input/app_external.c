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

#if CONFIG_AIR_KEYBOARD_M607

#include <stdint.h>
#include <zephyr/drivers/gpio.h>

#include "hal_wdt.h"
#include "hal_eint.h"
#include "hal_eint_internal.h"
#include "hal_gpio.h"
#include "hal_gpio_internal.h"

#include "af_events_declaration.h"
#include "app_pin_config_parser.h"
#include "app_state.h"
#include "hid_common.h"
#include "application.h"

#define thisMODULE      external
#define thisMOD         "external"

LOG_MODULE_REGISTER(thisMODULE);

/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
static void app_external_enter_low_power(void);
static void app_external_exit_low_power(void);


/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/


/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/
void app_external__eint_callback(void *user_data)
{
    struct evt_active_status* event = create_evt_active_status();
    if (event){
        event->active = true;
        event->type = KEY_WAKEUP;
        AF_EVT_SUBMIT(event);
        hal_eint_unmask(MCU_TO_RF_IO);
    }
}


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
static bool app_external__evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state* event = (struct evt_app_state*)evt_header;
    APP_LOGI(thisMOD,"app_external__evt_app_state event->app_state = 0x%x " , event->app_state );

    switch(event->app_state)
    {
        case APP_STATE_USB_ACTIVE:
        case APP_STATE_BT_CONNECTED_ACTIVE:
        case APP_STATE_2_4G_CONNECTED_ACTIVE:
        {
        }
        break;

        case APP_STATE_STANDBY:
        {
            /* set mcu_to_rf as EINT for waking up from standby */
            app_external_enter_low_power();
        }
        break;

        case APP_STATE_USB_SUSPEND:
        case APP_STATE_DISCONNECTED:
        {
        }
        break;

        case APP_STATE_TEST:
        {
        }
        break;

        case APP_STATE_CONNECT_PREPARING:
        {
        }
        break;

        default:
        break;
    }

    return AF_TRAVERSE_NEXT;
}


static bool app_external__evt_active_status(const struct af_evt_header *evt_header)
{
    struct evt_active_status* event = (struct evt_active_status*)evt_header;
    APP_LOGI(thisMOD,"app_external__evt_active_status, active = %d, type = %d", event->active, event->type);
    uint32_t app_state = app_state_current_state();

    if((event->active == false) && \
        (app_state == APP_STATE_2_4G_CONNECTED_ACTIVE || \
        app_state == APP_STATE_BT_CONNECTED_ACTIVE))
    {
        ;
    }
    else if((event->active == true) && (app_state == APP_STATE_STANDBY))
    {
        switch(event->type)
        {
            case MOTION_SENSOR_WAKEUP:
            case WHEEL_WAKEUP:
            case KEY_WAKEUP:
            {
                app_external_exit_low_power();
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
static void app_external_enter_low_power(void)
{
    APP_LOGI(thisMOD,"app_external_enter_low_power");
    hal_pinmux_set_function(MCU_TO_RF_IO, HAL_GPIO_32_EINT32);

    hal_eint_mask(MCU_TO_RF_EINT);
    hal_eint_config_t eint_cfg;
    eint_cfg.trigger_mode = HAL_EINT_EDGE_FALLING;
    eint_cfg.debounce_time = 0;
    hal_eint_init(MCU_TO_RF_EINT, &eint_cfg);
    hal_eint_register_callback(MCU_TO_RF_EINT, app_external__eint_callback, NULL);
    hal_eint_unmask(MCU_TO_RF_EINT);
    hal_eint_enable(MCU_TO_RF_EINT);
    hal_eint_ext_sleep_set_debounce_time(MCU_TO_RF_EINT, 0);

    hal_gpio_wakeup_extend_sleep_config(MCU_TO_RF_IO);
}

static void app_external_exit_low_power(void)
{
    APP_LOGI(thisMOD,"app_external_exit_low_power");
    hal_gpio_wakeup_extend_sleep_clear(MCU_TO_RF_IO);
    hal_eint_disable(MCU_TO_RF_EINT);
    hal_pinmux_set_function(MCU_TO_RF_IO, HAL_GPIO_32_GPIO32);
    hal_gpio_set_direction(MCU_TO_RF_IO, HAL_GPIO_DIRECTION_INPUT);
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/

/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_app_state, app_external__evt_app_state);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_active_status, app_external__evt_active_status);
/*=============================================================================*/


#endif /* CONFIG_AIR_KEYBOARD_M607 */