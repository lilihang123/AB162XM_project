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


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "air_chip.h"
#include "hal_platform.h"


#if IS_ENABLED(CONFIG_AIR_BSP_EXTERNAL_SERIAL_FLASH_ENABLED)
#include "hal_spi_master.h"
#include "bsp_flash.h"
#include "bsp_external_flash.h"
#include "bsp_external_flash_utils.h"

#include "hal_gpio.h"
#endif /* IS_ENABLED(CONFIG_AIR_BSP_EXTERNAL_SERIAL_FLASH_ENABLED) */



#if IS_ENABLED(CONFIG_AIR_BSP_EXTERNAL_SERIAL_FLASH_ENABLED)
const bsp_external_flash_cfg_t bsp_external_flash_cfg[CONFIG_AIR_BSP_EXTERNAL_SERIAL_FLASH_NUM] = {
    /* 0x0C00_0000, 64MB, SPIM 2( high speed ) */
    {
        .spi_port = HAL_SPI_MASTER_2,
        .spi_freq_in_MHz = 39,
        .logic_addr_cfg = 0x0C000000,
    },
    /* 0x0200_0000, 4MB, SPIM 1 */
    {
        .spi_port = HAL_SPI_MASTER_1,
        .spi_freq_in_MHz = 16,
        .logic_addr_cfg = 0x02000000,
    },
};

void bsp_external_flash_function_enable(uint32_t logic_addr_cfg)
{
    /* It needs to be override according to the actual GPIO configuration of the project */
    switch(logic_addr_cfg)
    {
        case 0x0C000000:
            hal_gpio_clear_high_impedance(HAL_GPIO_34);
            hal_pinmux_set_function(HAL_GPIO_34, HAL_GPIO_34_SPI_MST2_HS_CS0);
            hal_gpio_set_direction(HAL_GPIO_34, HAL_GPIO_DIRECTION_OUTPUT);

            hal_gpio_clear_high_impedance(HAL_GPIO_35);
            hal_pinmux_set_function(HAL_GPIO_35, HAL_GPIO_35_SPI_MST2_HS_MOSI);
            hal_gpio_set_direction(HAL_GPIO_35, HAL_GPIO_DIRECTION_OUTPUT);

            hal_gpio_clear_high_impedance(HAL_GPIO_36);
            hal_pinmux_set_function(HAL_GPIO_36, HAL_GPIO_36_SPI_MST2_HS_MISO);
            hal_gpio_set_direction(HAL_GPIO_36, HAL_GPIO_DIRECTION_OUTPUT);

            hal_gpio_clear_high_impedance(HAL_GPIO_37);
            hal_pinmux_set_function(HAL_GPIO_37, HAL_GPIO_37_SPI_MST2_HS_SCK);
            hal_gpio_set_direction(HAL_GPIO_37, HAL_GPIO_DIRECTION_OUTPUT);
            break;
        case 0x02000000:
            hal_gpio_clear_high_impedance(HAL_GPIO_44);
            hal_pinmux_set_function(HAL_GPIO_44, HAL_GPIO_44_SPI_MST1_SCK);
            hal_gpio_set_direction(HAL_GPIO_44, HAL_GPIO_DIRECTION_OUTPUT);

            hal_gpio_clear_high_impedance(HAL_GPIO_45);
            hal_pinmux_set_function(HAL_GPIO_45, HAL_GPIO_45_SPI_MST1_MOSI);
            hal_gpio_set_direction(HAL_GPIO_45, HAL_GPIO_DIRECTION_OUTPUT);

            hal_gpio_clear_high_impedance(HAL_GPIO_46);
            hal_pinmux_set_function(HAL_GPIO_46, HAL_GPIO_46_SPI_MST1_MISO);
            hal_gpio_set_direction(HAL_GPIO_46, HAL_GPIO_DIRECTION_OUTPUT);

            hal_gpio_clear_high_impedance(HAL_GPIO_47);
            hal_pinmux_set_function(HAL_GPIO_47, HAL_GPIO_47_SPI_MST1_CS0);
            hal_gpio_set_direction(HAL_GPIO_47, HAL_GPIO_DIRECTION_OUTPUT);
            break;
        default:
            printk("[BSP External Flash] invalid logic_addr_cfg 0x%08X which not matched with bsp_external_flash_cfg",
                (unsigned int)logic_addr_cfg
            );
            __ASSERT_NO_MSG(0);
            break;
    }
}


void bsp_external_flash_function_disable(uint32_t logic_addr_cfg)
{
    /* It needs to be override according to the actual GPIO configuration of the project */
    switch(logic_addr_cfg)
    {
        case 0x0C000000:
            hal_pinmux_set_function(HAL_GPIO_34, HAL_GPIO_34_GPIO34);
            hal_gpio_set_direction(HAL_GPIO_34, HAL_GPIO_DIRECTION_INPUT);
            hal_gpio_set_high_impedance(HAL_GPIO_34);

            hal_pinmux_set_function(HAL_GPIO_35, HAL_GPIO_35_GPIO35);
            hal_gpio_set_direction(HAL_GPIO_35, HAL_GPIO_DIRECTION_INPUT);
            hal_gpio_set_high_impedance(HAL_GPIO_35);

            hal_pinmux_set_function(HAL_GPIO_36, HAL_GPIO_36_GPIO36);
            hal_gpio_set_direction(HAL_GPIO_36, HAL_GPIO_DIRECTION_INPUT);
            hal_gpio_set_high_impedance(HAL_GPIO_36);

            hal_pinmux_set_function(HAL_GPIO_37, HAL_GPIO_37_GPIO37);
            hal_gpio_set_direction(HAL_GPIO_37, HAL_GPIO_DIRECTION_INPUT);
            hal_gpio_set_high_impedance(HAL_GPIO_37);
            break;
        case 0x02000000:
            hal_pinmux_set_function(HAL_GPIO_44, HAL_GPIO_44_GPIO44);
            hal_gpio_set_direction(HAL_GPIO_44, HAL_GPIO_DIRECTION_INPUT);
            hal_gpio_set_high_impedance(HAL_GPIO_44);

            hal_pinmux_set_function(HAL_GPIO_45, HAL_GPIO_45_GPIO45);
            hal_gpio_set_direction(HAL_GPIO_45, HAL_GPIO_DIRECTION_INPUT);
            hal_gpio_set_high_impedance(HAL_GPIO_45);

            hal_pinmux_set_function(HAL_GPIO_46, HAL_GPIO_46_GPIO46);
            hal_gpio_set_direction(HAL_GPIO_46, HAL_GPIO_DIRECTION_INPUT);
            hal_gpio_set_high_impedance(HAL_GPIO_46);

            hal_pinmux_set_function(HAL_GPIO_47, HAL_GPIO_47_GPIO47);
            hal_gpio_set_direction(HAL_GPIO_47, HAL_GPIO_DIRECTION_INPUT);
            hal_gpio_set_high_impedance(HAL_GPIO_47);

            break;
        default:
            printk("[BSP External Flash] invalid logic_addr_cfg 0x%08X which not matched with bsp_external_flash_cfg",
                (unsigned int)logic_addr_cfg
            );
            __ASSERT_NO_MSG(0);
            break;
    }
}


#endif /* IS_ENABLED(CONFIG_AIR_BSP_EXTERNAL_SERIAL_FLASH_ENABLED) */