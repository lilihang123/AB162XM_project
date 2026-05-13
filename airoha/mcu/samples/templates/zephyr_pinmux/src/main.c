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

#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pinctrl.h>
#include <errno.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/irq.h>
#include <soc.h>
#include <zephyr/drivers/gpio/gpio_utils.h>
#include "air_chip.h"
#include "hal_platform.h"
#include "hal_gpio.h"
#include "hal_gpio_internal.h"
#include "hal_eint.h"
#include <zephyr/sys/printk.h>



#if defined(HAL_GPT_MODULE_ENABLED)
#include "hal_gpt.h"
#endif

#include "memory_attribute.h"
#include "autoconf.h"

#ifdef CONFIG_AIR_WDT
#include "wdt_airoha.h"
#endif

gpio_state_t state;
hal_eint_status_t status;
hal_eint_config_t eint_config;
void feed_watch_dog(void);

const pinctrl_soc_pin_t pin_config[7]={
    {7,0,0,0,0,1,1,0,0,0,0},
    {8,0,0,0,0,1,0,0,0,0,0},
    {23,0,0,0,0,0,0,0,0,0,0},
    {10,0,0,0,1,0,0,0,0,0,0},
    {11,0,0,1,0,0,0,0,0,0,0},
    {12,2,0,0,0,0,0,0,0,0,0},
    {24,12,0,0,0,0,0,0,0,0,0},
};

 void eint_callback()
{
    hal_eint_mask(HAL_EINT_NUMBER_24);
    printk("eint_24:hello\n");
    hal_eint_unmask(HAL_EINT_NUMBER_24);
}


void delay(int i)
{
    while(i)
    i--;
}
 static void run_pinmux_test(const pinctrl_soc_pin_t *pin_config)
 {
   pinctrl_configure_pins(pin_config, 7, 0);

   gpio_get_state(HAL_GPIO_7,&state);
   printk("gpio_7_state");
   printk("%d",state.dir);
   printk("%d",state.dout);
   gpio_get_state(HAL_GPIO_8,&state);
   printk("gpio_8_state");
   printk("%d",state.dir);
   printk("%d",state.dout);
   gpio_get_state(HAL_GPIO_23,&state);
   printk("gpio_23_state");
   printk("%d",state.dir);
   printk("%d",state.din);
   gpio_get_state(HAL_GPIO_10,&state);
   printk("gpio_10_state");
   printk("%d",state.dir);
   printk("%d",state.pull_type);
   gpio_get_state(HAL_GPIO_11,&state);
   printk("gpio_11_state");
   printk("%d",state.dir);
   printk("%d",state.pull_type);
   gpio_get_state(HAL_GPIO_12,&state);
   printk("gpio_12_state");
   printk("%d",state.mode);
   gpio_get_state(HAL_GPIO_24,&state);
   printk("gpio_24_state");
   printk("%d",state.mode);

 }


int main(void)
{
   void eint_callback();
   printk("helloworld");
   run_pinmux_test(pin_config);

   printk("eint_24_init");

   hal_eint_mask(HAL_EINT_NUMBER_24);

   eint_config.trigger_mode = HAL_EINT_LEVEL_HIGH;
   eint_config.debounce_time = 30;
    status = hal_eint_init(HAL_EINT_NUMBER_24,&eint_config);
   if(status!=HAL_EINT_STATUS_OK)
   {
       printk("eint_24_init failed");
       return -1;
   }
    status= hal_eint_register_callback(HAL_EINT_NUMBER_24,eint_callback,NULL);
    if(status!=HAL_EINT_STATUS_OK)
    {
        printk("eint_24_register_callback failed");
       return -1;
    }
    hal_eint_mask(HAL_EINT_NUMBER_24);
    if (HAL_EINT_STATUS_OK !=  hal_eint_set_trigger_mode(HAL_EINT_NUMBER_24,HAL_EINT_EDGE_RISING))
    {
        printk("eint_24_set_trigger_err");
        return -1;

    }
       if (HAL_EINT_STATUS_OK !=  hal_eint_set_debounce_time(HAL_EINT_NUMBER_24, 30))
    {
      printk("eint_24_set_Debounce_err");
      return -1;
    }
      hal_eint_unmask(HAL_EINT_NUMBER_24);
    for(;;){
        gpio_get_state(HAL_GPIO_23,&state);
        delay(10000);
        printk("gpio23_din:%d",state.din);


#if defined(HAL_GPT_MODULE_ENABLED)
        hal_gpt_delay_ms(3000);
#else
        uint32_t count = 0x5A5A5A5A;
        while(count--){
            __asm__("mov r0, r0");
        }
#endif
        feed_watch_dog();
    }
    return 0;
}

void feed_watch_dog(void)
{
#ifdef CONFIG_AIR_WDT
    const struct device *wdt_dev = \
        device_get_binding(DT_NODE_FULL_NAME(DT_NODELABEL(wdt0)));
    if(wdt_dev != NULL){
        int wdt_ch = ((wdt_air_data_t*)(wdt_dev->data))->m_channel;
        printk("[wdt] wdt_feed was called with dev: 0x%08X and channel %d\r\n", (unsigned int)wdt_dev, wdt_ch);
        wdt_feed(wdt_dev, wdt_ch);
    }
#endif
}