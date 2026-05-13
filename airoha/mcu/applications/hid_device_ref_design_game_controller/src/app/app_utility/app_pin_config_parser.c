
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

#include "app_pin_config_parser.h"
#include "hal_gpio.h"



#define thisMODULE app_pin_cfg
#define thisMOD    "app_pin_cfg"
LOG_MODULE_REGISTER(thisMODULE);

#if defined(CONFIG_AIR_APP_PIN_USAGE_LIST)
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/


/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/



/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/


/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static void app_pin_config_parser_output_pin_handle(uint8_t gpio_id, T_GPIO_CONFIG_S * gpio_cfg, T_GPIO_PIN_USAGE_LIST_S* usage_list)
{
    APP_LOGI(thisMOD, "app_pinmux_mgr_gpio_parser gpio_%d usage = 0x%X, parameter = 0x%02X ",gpio_id,  gpio_cfg->usage, gpio_cfg->parameter);

    switch(gpio_cfg->usage)
    {
        case APP_PINMUX_USAGE_OUTPUT_LED_SINGLE_0:
        {
            usage_list->data.single_led.led_0 = gpio_id;
            usage_list->ctrl.single_led_ptr = &usage_list->data.single_led;
        }
        break;

        case APP_PINMUX_USAGE_OUTPUT_LED_SINGLE_1:
        {
            usage_list->data.single_led.led_1 = gpio_id;
            usage_list->ctrl.single_led_ptr = &usage_list->data.single_led;
        }
        break;

        case APP_PINMUX_USAGE_OUTPUT_LED_SINGLE_2:
        {
            usage_list->data.single_led.led_2 = gpio_id;
            usage_list->ctrl.single_led_ptr = &usage_list->data.single_led;
        }
        break;

        case APP_PINMUX_USAGE_OUTPUT_LED_RGB_0:
        case APP_PINMUX_USAGE_OUTPUT_LED_RGB_1:
        case APP_PINMUX_USAGE_OUTPUT_LED_RGB_2:
        break;

        case APP_PINMUX_USAGE_OUTPUT_IR_PD_CTRL:
        {
            usage_list->data.output_ctrl.irpt_ena_pin.id = gpio_id;
            usage_list->data.output_ctrl.irpt_ena_pin.para =gpio_cfg->parameter;
        }
        break;

        case APP_PINMUX_USAGE_OUTPUT_SCROLL_EN_CTRL:
        {
            usage_list->data.output_ctrl.scroll_ena_pin.id = gpio_id;
            usage_list->data.output_ctrl.scroll_ena_pin.para =gpio_cfg->parameter;
        }
        break;

        case APP_PINMUX_USAGE_OUTPUT_FUEL_GUAGE_CTRL:
        {
            usage_list->data.output_ctrl.fuel_gauge_pin.id = gpio_id;
            usage_list->data.output_ctrl.fuel_gauge_pin.para =gpio_cfg->parameter;
        }
        break;

        case APP_PINMUX_USAGE_OUTPUT_SENSOR_NRESET_CTRL:
        {
            usage_list->data.output_ctrl.sensor_nreset_pin.id = gpio_id;
            usage_list->data.output_ctrl.sensor_nreset_pin.para =gpio_cfg->parameter;
        }
        break;

        case APP_PINMUX_USAGE_OUTPUT_CHARGE_ENA_CTRL:
        {
            usage_list->data.output_ctrl.charge_ena_pin.id = gpio_id;
            usage_list->data.output_ctrl.charge_ena_pin.para =gpio_cfg->parameter;
        }
        break;

        case APP_PINMUX_USAGE_OUTPUT_LED_POWER_CTRL:
        {
            usage_list->data.output_ctrl.led_power_ctrl_pin.id = gpio_id;
            usage_list->data.output_ctrl.led_power_ctrl_pin.para =gpio_cfg->parameter;
        }
        break;

        case APP_PINMUX_USAGE_OUTPUT_IR_PD_CTRL_2:
        {
            usage_list->data.output_ctrl.irpt_ena_pin2.id = gpio_id;
            usage_list->data.output_ctrl.irpt_ena_pin2.para =gpio_cfg->parameter;
        }
        break;


        case APP_PINMUX_USAGE_OUTPUT_DEBUG_SPI_CB_SIGNAL:
        {
            usage_list->data.device_dbg.spi_cb = gpio_id;
            usage_list->ctrl.device_dbg_ptr = &usage_list->data.device_dbg;
        }
        break;

        case APP_PINMUX_USAGE_OUTPUT_DEBUG_LATCH_REPORT_SIGNAL:
        {
            usage_list->data.device_dbg.latch_report = gpio_id;
            usage_list->ctrl.device_dbg_ptr = &usage_list->data.device_dbg;
        }
        break;

        case APP_PINMUX_USAGE_OUTPUT_DEBUG_TX_NACK:
        {
            usage_list->data.device_dbg.tx_nack = gpio_id;
            usage_list->ctrl.device_dbg_ptr = &usage_list->data.device_dbg;
        }
        break;

        case APP_PINMUX_USAGE_OUTPUT_DEBUG_DEBUG_1:
        {
            usage_list->data.device_dbg.dbg_1 = gpio_id;
            usage_list->ctrl.device_dbg_ptr = &usage_list->data.device_dbg;
        }
        break;

        case APP_PINMUX_USAGE_OUTPUT_DEBUG_DEBUG_2:
        {
            usage_list->data.device_dbg.dbg_2 = gpio_id;
            usage_list->ctrl.device_dbg_ptr = &usage_list->data.device_dbg;
        }
        break;

        case APP_PINMUX_USAGE_OUTPUT_DEBUG_DEBUG_3:
        {
            usage_list->data.device_dbg.dbg_3 = gpio_id;
            usage_list->ctrl.device_dbg_ptr = &usage_list->data.device_dbg;
        }
        break;

        case APP_PINMUX_USAGE_OUTPUT_DEBUG_USB_TX_SIGNAL:
        {
            usage_list->data.usb_dbg.usb_tx = gpio_id;
            usage_list->ctrl.usb_dbg_ptr = &usage_list->data.usb_dbg;
        }
        break;

        case APP_PINMUX_USAGE_OUTPUT_DEBUG_USB_TX_DONE_SIGNAL:
        {
            usage_list->data.usb_dbg.usb_tx_done = gpio_id;
            usage_list->ctrl.usb_dbg_ptr = &usage_list->data.usb_dbg;
        }
        break;

        case APP_PINMUX_USAGE_OUTPUT_DEBUG_USB_SOF_SIGNAL:
        {
            usage_list->data.usb_dbg.usb_sof = gpio_id;
            usage_list->ctrl.usb_dbg_ptr = &usage_list->data.usb_dbg;
        }
        break;
    }
}

static void app_pin_config_parser_input_pin_handle(uint8_t gpio_id, T_GPIO_CONFIG_S * gpio_cfg, T_GPIO_PIN_USAGE_LIST_S* usage_list)
{
    APP_LOGI(thisMOD, "app_pin_config_parser_input_pin_handle gpio_%d usage = 0x%X, usage_list = 0x%08X ",gpio_id,  gpio_cfg->usage, usage_list);

    switch(gpio_cfg->usage)
    {
        #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE)
        case APP_PINMUX_USAGE_EINT_MOUSE_L_KEY:
        {
            usage_list->data.key_list.l_key = gpio_id;
            usage_list->ctrl.key_list_ptr = &usage_list->data.key_list;
        }
        break;

        case APP_PINMUX_USAGE_EINT_MOUSE_R_KEY:
        {
            usage_list->data.key_list.r_key = gpio_id;
            usage_list->ctrl.key_list_ptr = &usage_list->data.key_list;
        }
        break;

        case APP_PINMUX_USAGE_EINT_MOUSE_M_KEY:
        {
            usage_list->data.key_list.m_key = gpio_id;
            usage_list->ctrl.key_list_ptr = &usage_list->data.key_list;
        }
        break;

        case APP_PINMUX_USAGE_EINT_MOUSE_FW_KEY:
        {
            usage_list->data.key_list.fw_key = gpio_id;
            usage_list->ctrl.key_list_ptr = &usage_list->data.key_list;
        }
        break;

        case APP_PINMUX_USAGE_EINT_MOUSE_BW_KEY:
        {
            usage_list->data.key_list.bw_key = gpio_id;
            usage_list->ctrl.key_list_ptr = &usage_list->data.key_list;
        }
        break;

        case APP_PINMUX_USAGE_EINT_MOUSE_DPI_KEY:
        {
            usage_list->data.key_list.dpi_key = gpio_id;
            usage_list->ctrl.key_list_ptr = &usage_list->data.key_list;
        }
        break;

        case APP_PINMUX_USAGE_EINT_MOUSE_REPORT_RATE_CHANGE_KEY:
        {
            usage_list->data.key_list.rr_key = gpio_id;
            usage_list->ctrl.key_list_ptr = &usage_list->data.key_list;
        }
        break;

        case APP_PINMUX_USAGE_EINT_MOUSE_MOTION_PIN:
        {
            usage_list->data.motion_sensor.motion_pin = gpio_id;
            usage_list->ctrl.motion_sensor_ptr = &usage_list->data.motion_sensor;
        }
        break;

        case APP_PINMUX_USAGE_EINT_MOUSE_BT_MODE_KEY:
        {
            usage_list->data.slide_switch.ss_bt_mode = gpio_id;
            usage_list->ctrl.slide_switch_ptr = &usage_list->data.slide_switch;
        }
        break;

        case APP_PINMUX_USAGE_EINT_MOUSE_2_4G_MODE_KEY:
        {
            usage_list->data.slide_switch.ss_2_4G_mode = gpio_id;
            usage_list->ctrl.slide_switch_ptr = &usage_list->data.slide_switch;
        }
        break;
        #endif

        default:
        break;
    }
}

static void app_pin_config_parser(T_DYNAMIC_PINMUX_CONFIG_S * config, T_GPIO_PIN_USAGE_LIST_S* usage_list)
{
    APP_LOGI(thisMOD, "app_pinmux_mgr_parser config = 0x%X, usage_list = 0x%08X ", config,  usage_list);

    int8_t idx;

    for (idx = MAX_PIN_NUMBER-1; idx>=0; idx--)
    {
        switch(config->gpio[idx].fun_type)
        {
            case APP_PINMUX_FUNC_GPIO_OUTPUT:
            {
                app_pin_config_parser_output_pin_handle(idx, &config->gpio[idx], usage_list);
            }
            break;

            case APP_PINMUX_FUNC_MUTI_FUN_1:
            case APP_PINMUX_FUNC_MUTI_FUN_2:
            case APP_PINMUX_FUNC_MUTI_FUN_3:
            case APP_PINMUX_FUNC_MUTI_FUN_4:
            case APP_PINMUX_FUNC_MUTI_FUN_5:
            case APP_PINMUX_FUNC_MUTI_FUN_6:
            case APP_PINMUX_FUNC_MUTI_FUN_7:
            break;

            case APP_PINMUX_FUNC_PWM:
            break;

            case APP_PINMUX_FUNC_KEY_MATRIX:
            case APP_PINMUX_FUNC_MUTI_FUN_10:
            case APP_PINMUX_FUNC_MUTI_FUN_11:
            break;

            case APP_PINMUX_FUNC_EINT:
            {
                app_pin_config_parser_input_pin_handle(idx, &config->gpio[idx], usage_list);
            }
            break;

            case APP_PINMUX_FUNC_HW_DEBUG:
            {
                usage_list->data.hw_dbg_pin[usage_list->ctrl.hw_dbg_pin_num] = idx;
                usage_list->ctrl.hw_dbg_pin_num++;
            }
            break;

            case APP_PINMUX_FUNC_MUTI_FUN_14:
            case APP_PINMUX_FUNC_MUTI_FUN_15:
            case APP_PINMUX_FUNC_MUTI_FUN_16:
            {

            }
            break;

            default:
            break;
        }
    }
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
void app_pin_config_parser_print(T_GPIO_PIN_USAGE_LIST_S* usage_list)
{
    #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE)
    if (usage_list->ctrl.key_list_ptr){
    APP_LOGI(thisMOD, "key_list L=%d, R=%d, M=%d, FW=%d, BW=%d, DPI=%d, RR=%d, "
        ,usage_list->ctrl.key_list_ptr->l_key
        ,usage_list->ctrl.key_list_ptr->r_key
        ,usage_list->ctrl.key_list_ptr->m_key
        ,usage_list->ctrl.key_list_ptr->fw_key
        ,usage_list->ctrl.key_list_ptr->bw_key
        ,usage_list->ctrl.key_list_ptr->dpi_key
        ,usage_list->ctrl.key_list_ptr->rr_key
        );
    }
    #endif

    if (usage_list->ctrl.single_led_ptr){
        APP_LOGI(thisMOD, "single_led %02d-%02d-%02d"
            ,usage_list->ctrl.single_led_ptr->led_0
            ,usage_list->ctrl.single_led_ptr->led_1
            ,usage_list->ctrl.single_led_ptr->led_2
            );
    }

    if (usage_list->ctrl.slide_switch_ptr){
        APP_LOGI(thisMOD, "slide_switch bt=%d, 2_4G=%d "
            ,usage_list->ctrl.slide_switch_ptr->ss_bt_mode
            ,usage_list->ctrl.slide_switch_ptr->ss_2_4G_mode
            );
    }

    if (usage_list->ctrl.hw_dbg_pin_ptr){
        APP_LOGI(thisMOD, "hw_dbg_pin [%d~0]=0x%08X-%08X-%08X-%08X "
            ,usage_list->ctrl.hw_dbg_pin_num
            ,*(uint32_t*)&usage_list->ctrl.hw_dbg_pin_ptr[12]
            ,*(uint32_t*)&usage_list->ctrl.hw_dbg_pin_ptr[8]
            ,*(uint32_t*)&usage_list->ctrl.hw_dbg_pin_ptr[4]
            ,*(uint32_t*)&usage_list->ctrl.hw_dbg_pin_ptr[0]
            );
    }

    if (usage_list->ctrl.device_dbg_ptr){
        APP_LOGI(thisMOD, "device_dbg, spi_cb=%02d, latch_report=%d, tx_nack=%02d, dbg_1=%02d, dbg_2=%02d, dbg_3=%02d"
            ,usage_list->ctrl.device_dbg_ptr->spi_cb
            ,usage_list->ctrl.device_dbg_ptr->latch_report
            ,usage_list->ctrl.device_dbg_ptr->tx_nack
            ,usage_list->ctrl.device_dbg_ptr->dbg_1
            ,usage_list->ctrl.device_dbg_ptr->dbg_2
            ,usage_list->ctrl.device_dbg_ptr->dbg_3
            );
    }

    if (usage_list->ctrl.usb_dbg_ptr){
        APP_LOGI(thisMOD, "device_dbg, usb_tx=%02d, usb_tx_done=%02d, usb_sof=%02d"
            ,usage_list->ctrl.usb_dbg_ptr->usb_tx
            ,usage_list->ctrl.usb_dbg_ptr->usb_tx_done
            ,usage_list->ctrl.usb_dbg_ptr->usb_sof
            );
    }

    T_OUTPUT_CTRL_PIN_INFO_S* ctrl_pin_ptr = (T_OUTPUT_CTRL_PIN_INFO_S*)&usage_list->data.output_ctrl.irpt_ena_pin;
    for (uint8_t idx = 0; idx < sizeof(T_OUTPUT_CTRL_PIN_S)/sizeof(T_OUTPUT_CTRL_PIN_INFO_S); idx++){
        if (ctrl_pin_ptr[idx].id != GPIO_UNDEFINE ){
            APP_LOGI(thisMOD, "output_ctrl[%d] gpio = %d, parameter = 0x%02X"
                , idx
                , ctrl_pin_ptr[idx].id
                , ctrl_pin_ptr[idx].para
            );
        }
    }
}
#endif

void app_pin_config_parser_init(T_GPIO_PIN_USAGE_LIST_S * usage_list)
{
    APP_LOGI(thisMOD, "app_pin_config_parser_init");

    memset(&usage_list->data, GPIO_UNDEFINE , sizeof(T_GPIO_PIN_USAGE_LIST_DATA_S));
    memset(&usage_list->ctrl, 0 , sizeof(T_GPIO_PIN_USAGE_LIST_CTRL_S));
    #if defined(CONFIG_AIR_APP_PIN_USAGE_LIST)
    T_DYNAMIC_PINMUX_CONFIG_S pin_config;
    if (app_nvkey_read_data(NVID_DYNAMIC_PINMUX_CONFIG, (uint8_t*)&pin_config, sizeof(T_DYNAMIC_PINMUX_CONFIG_S))){

        APP_LOGI(thisMOD, "pin_config.ver = 0x%x, enable = %d "
            , pin_config.ver
            , pin_config.enable
            );

        if (pin_config.enable) {
            app_pin_config_parser(&pin_config, usage_list);
            app_pin_config_parser_print(usage_list);
        }
    }
    #endif
}

