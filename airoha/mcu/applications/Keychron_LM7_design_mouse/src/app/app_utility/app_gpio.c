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

#include "app_gpio.h"
#include "app_ccni.h"
#include "hal_gpio.h"



#define thisMODULE gpio
#define thisMOD    "gpio"

LOG_MODULE_REGISTER(thisMODULE);


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
#if defined(CONFIG_AIR_APP_PIN_USAGE_LIST)
void app_gpio_configure_output(uint8_t pin_id, uint8_t level )
{  
    APP_LOGI(thisMOD, "app_gpio_configure_output XXX pin_%02d = %d", pin_id, level);

    hal_gpio_init(pin_id);
    hal_pinmux_set_function(pin_id, 0);
    hal_gpio_set_direction(pin_id, HAL_GPIO_DIRECTION_OUTPUT);
    hal_gpio_set_output(pin_id, level);        
}
#endif


/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
void app_gpio_init(T_GPIO_PIN_USAGE_LIST_S * pin_usage_list)
{
    APP_LOGI(thisMOD, "app_gpio_init");

    #if defined(CONFIG_AIR_APP_PIN_USAGE_LIST)
    T_OUTPUT_CTRL_PIN_INFO_S* ctrl_pin_ptr = (T_OUTPUT_CTRL_PIN_INFO_S*)&pin_usage_list->data.output_ctrl.irpt_ena_pin; 
    for (uint8_t idx = 0; idx < sizeof(T_OUTPUT_CTRL_PIN_S)/sizeof(T_OUTPUT_CTRL_PIN_INFO_S); idx++){
        if (ctrl_pin_ptr[idx].id != GPIO_UNDEFINE ){
            app_gpio_configure_output(ctrl_pin_ptr[idx].id, ctrl_pin_ptr[idx].para & 0x01);


            APP_LOGI(thisMOD, "app_gpio_init  usage[%d]  set gpio_%d, level = 0x%02X"
                , idx
                , ctrl_pin_ptr[idx].id
                , ctrl_pin_ptr[idx].para & 0x01
            );
        }
    }

    hid_common_set_app_para(PARA_TYPE_IRPT_CTRL, (uint8_t*)&pin_usage_list->data.output_ctrl.irpt_ena_pin, sizeof(T_OUTPUT_CTRL_PIN_INFO_S));
    hid_common_set_app_para(PARA_TYPE_SCROLL_CTRL, (uint8_t*)&pin_usage_list->data.output_ctrl.scroll_ena_pin, sizeof(T_OUTPUT_CTRL_PIN_INFO_S));
    #endif
}





/*============================Application Framework============================*/

/*=============================================================================*/

