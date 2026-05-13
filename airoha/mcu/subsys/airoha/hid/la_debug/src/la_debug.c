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

#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>



#include "la_debug.h"
#include "hal_gpio.h"

#if defined (CONFIG_AIR_HID_DEBUG_PIN) ||  defined (CONFIG_AIR_HID_CP_DEBUG_GPIO)





#define thisMODULE  logic_ana_dbg
#define thisMOD    "logic_ana_dbg"
LOG_MODULE_REGISTER(thisMODULE);


#if defined(CONFIG_LOG)
#define DBG_LOGI(module_name, format, ...)   \
        LOG_INF("[srv-i]["module_name"]" format, ## __VA_ARGS__)

#else
#define DBG_LOGI(module_name, format, ...)   \
        printk("[I]["module_name"]"format, ## __VA_ARGS__)
#endif


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
static void la_debug_bt_dbg_scenario_config(uint8_t bt_dbg_scenario, uint16_t bt_dbg_invert)
{
    #define DBG_PING_SWAP           0x117
    #define REG_BT_DBG_SCENARIO     (*(volatile uint32_t *)0xa0010214)
    #define REG_BT_DBG_PIN_SWAP     (*(volatile uint32_t *)0x42010108)

    if (!bt_dbg_scenario) {
        return;
    }

    DBG_LOGI(thisMOD, "la_debug_bt_dbg_scenario_config, bt_dbg_scenario = %d, bt_dbg_invert = %d"
            , bt_dbg_scenario
            , bt_dbg_invert
        );

    REG_BT_DBG_SCENARIO = bt_dbg_scenario;

    if (bt_dbg_invert) {
        REG_BT_DBG_PIN_SWAP = DBG_PING_SWAP;
    }
}

static void la_debug_gpio_draw_id(uint8_t  pin_id, uint8_t pull_low_count, uint8_t pull_low_delay)
{
    uint8_t cnt;
    uint8_t delay_cnt;

    for (cnt = 0; cnt < pull_low_count; cnt++)
    {
        LA_DBG_PING_H(pin_id);

        for (delay_cnt = pull_low_delay; delay_cnt > 0; delay_cnt--)
        {
            // delay
            LA_DBG_PING_H(pin_id);
        }
        LA_DBG_PING_L(pin_id);
    }
}

static inline void debug_log_gpio_mode(void)
{
    DBG_LOGI(thisMOD, "REG_GPIO_MODE [23_16]= 0x%08X, [15_08]= 0x%08X, [07_00]= 0x%08X",
             (unsigned int)(*(volatile uint32_t*)0x420b0038),
             (unsigned int)(*(volatile uint32_t*)0x420b0034),
             (unsigned int)(*(volatile uint32_t*)0x420b0030));

    DBG_LOGI(thisMOD, "REG_GPIO_MODE [47_40]= 0x%08X, [39_32]= 0x%08X, [31_24]= 0x%08X",
             (unsigned int)(*(volatile uint32_t*)0x420b0044),
             (unsigned int)(*(volatile uint32_t*)0x420b0040),
             (unsigned int)(*(volatile uint32_t*)0x420b003C));
}


static void la_debug_gpio_config(const T_LA_DEBUG_CFG_S* pin_list, uint8_t pin_list_num)
{
    int8_t idx;
    uint8_t pin;

    debug_log_gpio_mode();

    for (idx = pin_list_num - 1; idx >= 0; idx--)
    {
        pin = pin_list[idx].pin_id;
        DBG_LOGI(thisMOD, "la_debug_gpio_config pin_%02d fun = 0x%02d", pin, pin_list[idx].pin_mux_fun);

        hal_gpio_init(pin);
        hal_pinmux_set_function(pin, PINMUX_FUN_GPIO);
        hal_gpio_set_direction(pin, HAL_GPIO_DIRECTION_OUTPUT);
        hal_gpio_set_output(pin, HAL_GPIO_DATA_LOW);

        la_debug_gpio_draw_id(pin, (pin / 10), 4);
        la_debug_gpio_draw_id(pin, ((pin % 10) / 5), 2);
        la_debug_gpio_draw_id(pin, ((pin % 5) + 1), 0);

        if (pin_list[idx].pin_mux_fun != PINMUX_FUN_GPIO)
        {
            hal_pinmux_set_function(pin, pin_list[idx].pin_mux_fun);
        }
    }

    debug_log_gpio_mode();
}



/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
void la_debug_init(const T_LA_DEBUG_CFG_S* pin_list, uint8_t pin_list_num, uint8_t bt_dbg_scenario, uint16_t bt_dbg_invert)
{
    la_debug_gpio_config(pin_list, pin_list_num);

    la_debug_bt_dbg_scenario_config(bt_dbg_scenario,bt_dbg_invert);
}







#endif // CONFIG_AIR_HID_DEBUG_PIN
