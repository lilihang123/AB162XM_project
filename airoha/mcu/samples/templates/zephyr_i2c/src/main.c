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
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>

#include "air_chip.h"
#include "hal_platform.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "hal_i2c_master.h"
#include "hal_gpio.h"
#include "hal_gpt.h"

#if defined(HAL_GPT_MODULE_ENABLED)
#include "hal_gpt.h"
#endif

#include "memory_attribute.h"
#include "autoconf.h"

#ifdef CONFIG_AIR_WDT
#include "wdt_airoha.h"
#endif

void feed_watch_dog(void);

static ATTR_RWDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN uint8_t i2c_tx_buff[10]={0x0f,0x01,0x02,0x03,0x04};
static ATTR_RWDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN uint8_t i2c_rx_buff[10]={0};

uint8_t  i2c_port=0;
uint16_t slv_addr= 0x6B;
uint8_t freq = HAL_I2C_FREQUENCY_400K;
hal_i2c_config_t i2c_config;
hal_i2c_status_t status;

int main(void)
{

hal_pinmux_set_function(34,HAL_GPIO_34_I2C0_SCL);
hal_pinmux_set_function(35,HAL_GPIO_35_I2C0_SDA);

hal_gpio_pull_up(34);
hal_gpio_pull_up(35);

hal_i2c_send_to_receive_config_t i2c_send_to_receive_config;
i2c_send_to_receive_config.slave_address=slv_addr;
i2c_send_to_receive_config.send_data=i2c_tx_buff;
i2c_send_to_receive_config.send_length=sizeof(i2c_tx_buff);
i2c_send_to_receive_config.receive_buffer=i2c_rx_buff;
i2c_send_to_receive_config.receive_length=sizeof(i2c_rx_buff);

i2c_config.frequency = freq;
status = hal_i2c_master_init(i2c_port, &i2c_config);
printk("init status %d \r\n",status);

for(;;){

hal_i2c_master_send_to_receive_polling(i2c_port,&i2c_send_to_receive_config);
printk("rx buf:%x",i2c_rx_buff[0]);

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