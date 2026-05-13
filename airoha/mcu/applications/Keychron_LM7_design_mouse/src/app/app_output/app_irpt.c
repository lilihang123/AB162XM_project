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


#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>

#include "app_irpt.h"
#include "hal_gpio.h"
#include "la_debug.h"
#include "hal_led.h"

#if defined(CONFIG_AIR_SUPPORT_IRPT_LR_KEY)
#if defined(CONFIG_AIR_M21_SAMPLE)
#define IR_ENABLE_PIN  23   // default L
#define SCROLL_EN_PIN  24   // default L
#define FUEL_GAUGE_PIN  47    // default L
#define SENSOR_NRESET_PIN  17  // default H
#define CHARGE_ENA_PIN     34  // default L
#define LED_PWR_CTRL_PIN   35 // default L

#define LED_R   44 // default L
#define LED_G   45 // default L
#define LED_B   46 // default L

#else
#define IR_ENABLE_PIN               47   // default Low
#define IR_ENABLE_PIN_LED_0          0  // LED 0 (gpio 47)
#define IR_LED_ON_TIME              60  // us
#define IR_LED_OFF_TIME           1000  // us

#endif

#define thisMODULE irpt
#define thisMOD    "irpt"

LOG_MODULE_REGISTER(thisMODULE);



/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/


/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
typedef struct {
    uint8_t pin_id;
    uint8_t level;
}T_GPIO_OUTPUT_CONFIG_S;


#if defined(CONFIG_AIR_M21_SAMPLE)
const T_GPIO_OUTPUT_CONFIG_S app_irpt_pins[] =
{
    {IR_ENABLE_PIN, 0},
    {SCROLL_EN_PIN, 0},
    {FUEL_GAUGE_PIN, 0},
    {SENSOR_NRESET_PIN, 1},
    {CHARGE_ENA_PIN, 0},
    {LED_PWR_CTRL_PIN, 0},
    {LED_R, 0},
    {LED_G, 0},
    {LED_B, 0},
};
#else

const T_GPIO_OUTPUT_CONFIG_S app_irpt_pins[] =
{
    {IR_ENABLE_PIN, 0},
};
#endif

#if defined (CONFIG_AIR_APP_STANDBY_WAKEUP_BY_IRPT_KEY)
void app_irpt__rtc_led_ctrl(bool enable);

#endif


typedef struct {
    bool rtc_led_initilized;
}T_IRPT_CTRL_S;


T_IRPT_CTRL_S  irpt;

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
#if defined (CONFIG_AIR_APP_STANDBY_WAKEUP_BY_IRPT_KEY)
static bool app_irpt__evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state* event = (struct evt_app_state*)evt_header;
    APP_LOGI(thisMOD,"app_irpt__evt_app_state, app_state = %d", event->app_state);

    switch(event->app_state)
    {
        case APP_STATE_STANDBY:
        {
            app_irpt__rtc_led_ctrl(true);
        }
        break;

        case APP_STATE_CONNECT_PREPARING:
        {
            app_irpt__rtc_led_ctrl(false);
        }
        break;
    }

    return AF_TRAVERSE_NEXT;
}
#endif

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
#if defined (CONFIG_AIR_APP_STANDBY_WAKEUP_BY_IRPT_KEY)
void app_irpt__rtc_led_ctrl(bool enable)
{
    APP_LOGI(thisMOD, "app_irpt__rtc_led_ctrl enable = %d, rtc_led_initilized = %d", enable, irpt.rtc_led_initilized);

    if (enable && (irpt.rtc_led_initilized == false)){
        irpt.rtc_led_initilized = true;
        hal_pinmux_set_function(IR_ENABLE_PIN, HAL_GPIO_47_RTC_LED0);
        hal_led_init(IR_ENABLE_PIN_LED_0);
        hal_led_configure_for_irpt(IR_ENABLE_PIN_LED_0, IR_LED_ON_TIME, IR_LED_OFF_TIME);
        hal_led_start(0);
    }
    else if ((enable == false ) && irpt.rtc_led_initilized){
        irpt.rtc_led_initilized = false;
        hal_led_stop(IR_ENABLE_PIN_LED_0);
        hal_led_deinit(IR_ENABLE_PIN_LED_0);
        hal_pinmux_set_function(IR_ENABLE_PIN, 0);
    }
    else {

    }
}
#endif

void app_irpt_configure_gpio(const T_GPIO_OUTPUT_CONFIG_S * pin_list, uint8_t pin_list_num )
{
    int8_t idx ;

    for (idx = pin_list_num-1; idx >= 0; idx--)
    {
        APP_LOGI(thisMOD, "app_irpt_configure_gpio pin_%02d = %d", pin_list[idx].pin_id, pin_list[idx].level);

        hal_gpio_init(pin_list[idx].pin_id);
        hal_pinmux_set_function(pin_list[idx].pin_id, 0);
        hal_gpio_set_direction(pin_list[idx].pin_id, HAL_GPIO_DIRECTION_OUTPUT);
        hal_gpio_set_output(pin_list[idx].pin_id, pin_list[idx].level);
    }
}
#endif

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
void app_irpt_init()
{
    #if defined(CONFIG_AIR_SUPPORT_IRPT_LR_KEY)
    app_irpt_configure_gpio(app_irpt_pins, sizeof(app_irpt_pins) / sizeof(T_GPIO_OUTPUT_CONFIG_S));

    T_OUTPUT_CTRL_PIN_INFO_S irpt_cfg = {
        .id = IR_ENABLE_PIN,
        .para = 0x00, // default L
    };

    hid_common_set_app_para(PARA_TYPE_IRPT_CTRL, (uint8_t*)&irpt_cfg, sizeof(T_OUTPUT_CTRL_PIN_INFO_S));

    APP_LOGI(thisMOD, "app_irpt_init = %d", IR_ENABLE_PIN);
    APP_LOGI(thisMOD, "REG_GPIO_MODE [23_16]= 0x%08X, [15_08]= 0x%08X, [07_00]= 0x%08X", (unsigned int)(*(volatile uint32_t*)0x420b0038) , (unsigned int)(*(volatile uint32_t*)0x420b0034), (unsigned int)(*(volatile uint32_t*)0x420b0030));
    APP_LOGI(thisMOD, "REG_GPIO_MODE [47_40]= 0x%08X, [39_32]= 0x%08X, [31_24]= 0x%08X", (unsigned int)(*(volatile uint32_t*)0x420b0044), (unsigned int)(*(volatile uint32_t*)0x420b0040), (unsigned int)(*(volatile uint32_t*)0x420b003C));
    #endif
}





/*============================Application Framework============================*/
#if defined (CONFIG_AIR_APP_STANDBY_WAKEUP_BY_IRPT_KEY)
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_app_state, app_irpt__evt_app_state);
#endif

/*=============================================================================*/

