/* Copyright Statement:
 *
 * (C) 2021  Airoha Technology Corp. All rights reserved.
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

#include "hal_gpio.h"

#ifdef HAL_GPIO_MODULE_ENABLED
#include "hal_gpio_internal.h"
#include "hal_log.h"

const hal_gpio_cfg_reg_t gpio_cfg_table[] = {
//DRV_REG shift  RTC_GPIO_MODE_REG  shift 
{ 0x00,     0 ,    0xF0,            0    }, //HAL_GPIO_0
{ 0x00,     2 ,    0xF0,            2    }, //HAL_GPIO_1
{ 0x00,     4 ,    0XFF,            0XFF }, //HAL_GPIO_2
{ 0x00,     6 ,    0XFF,            0XFF }, //HAL_GPIO_3
{ 0x00,     8 ,    0xF0,            8    }, //HAL_GPIO_4
{ 0x00,     10,    0xF0,            10   }, //HAL_GPIO_5
{ 0x00,     12,    0xF0,            12   }, //HAL_GPIO_6
{ 0x00,     14,    0xF0,            14   }, //HAL_GPIO_7
{ 0x00,     16,    0xF0,            16   }, //HAL_GPIO_8
{ 0x00,     18,    0XFF,            0XFF }, //HAL_GPIO_9
{ 0x00,     20,    0XFF,            0XFF }, //HAL_GPIO_10
{ 0x00,     22,    0XFF,            0XFF }, //HAL_GPIO_11
{ 0x00,     24,    0XFF,            0XFF }, //HAL_GPIO_12
{ 0x00,     26,    0XFF,            0XFF }, //HAL_GPIO_13
{ 0x00,     28,    0XFF,            0XFF }, //HAL_GPIO_14
{ 0x00,     30,    0XFF,            0XFF }, //HAL_GPIO_15
{ 0x10,     0 ,    0XFF,            0XFF }, //HAL_GPIO_16
{ 0x10,     2 ,    0x0100,          2    }, //HAL_GPIO_17
{ 0x10,     4 ,    0x0100,          4    }, //HAL_GPIO_18
{ 0x10,     6 ,    0x0100,          6    }, //HAL_GPIO_19
{ 0x10,     8 ,    0x0100,          8    }, //HAL_GPIO_20
{ 0x10,     10,    0x0100,          10   }, //HAL_GPIO_21
{ 0x10,     12,    0x0100,          12   }, //HAL_GPIO_22
{ 0x00,     0 ,    0x0100,          0    }, //HAL_GPIO_23
{ 0x00,     2 ,    0x0100,          2    }, //HAL_GPIO_24
{ 0x00,     4 ,    0x0100,          4    }, //HAL_GPIO_25
{ 0x00,     6 ,    0x0100,          6    }, //HAL_GPIO_26
{ 0x00,     8 ,    0x0100,          8    }, //HAL_GPIO_27
{ 0x00,     10,    0x0100,          10   }, //HAL_GPIO_28
{ 0x00,     12,    0x0100,          12   }, //HAL_GPIO_29
{ 0x00,     14,    0x0100,          14   }, //HAL_GPIO_30
{ 0x00,     16,    0x0100,          16   }, //HAL_GPIO_31
{ 0x00,     18,    0x0100,          18   }, //HAL_GPIO_32
{ 0x00,     20,    0x0100,          20   }, //HAL_GPIO_33
{ 0x00,     22,    0x0100,          22   }, //HAL_GPIO_34
{ 0x00,     24,    0x0100,          24   }, //HAL_GPIO_35
{ 0x00,     26,    0x0100,          26   }, //HAL_GPIO_36
{ 0x00,     28,    0x0100,          28   }, //HAL_GPIO_37
{ 0x00,     30,    0x0100,          30   }, //HAL_GPIO_38
{ 0x10,     0 ,    0x0110,          0    }, //HAL_GPIO_39
{ 0x10,     2 ,    0XFF,            0XFF }, //HAL_GPIO_40
{ 0x10,     4 ,    0XFF,            0XFF }, //HAL_GPIO_41
{ 0x10,     6 ,    0XFF,            0XFF }, //HAL_GPIO_42
{ 0x10,     8 ,    0XFF,            0XFF }, //HAL_GPIO_43
{ 0x10,     10,    0x0110,          10   }, //HAL_GPIO_44
{ 0x10,     12,    0x0110,          12   }, //HAL_GPIO_45
{ 0x10,     14,    0x0110,          14   }, //HAL_GPIO_46
{ 0x10,     16,    0x0110,          16   }  //HAL_GPIO_47
};

typedef struct {
    uint16_t temp;
    gpio_pull_type_t pull;
} pull_map_t;

static const pull_map_t pull_map[] = {
    {0x00,   GPIO_NO_PULL},
    {0x10,   GPIO_PU_R},
    {0x01,   GPIO_PD_R},
    {0x101,  GPIO_PD_R0},
    {0x1001, GPIO_PD_R1},
    {0x1101, GPIO_PD_R0_R1},
    {0x110,  GPIO_PU_R0},
    {0x1010, GPIO_PU_R1},
    {0x1110, GPIO_PU_R0_R1},
    {0x11,   GPIO_PUPD_ERR},
};

void gpio_get_state(hal_gpio_pin_t gpio_pin, gpio_state_t *gpio_state)
{
    uint32_t mode;
    uint32_t dir;
    uint32_t din;
    uint32_t dout;
    uint32_t pu;
    uint32_t pd;
    uint32_t pupd;
    uint32_t r0;
    uint32_t r1;
    uint32_t rsel;
    uint32_t io_cfg_base;
    uint8_t j;

    gpio_pull_type_t pull_type;
    uint32_t temp;
    uint8_t  shift;
    uint32_t reg_index;
    uint32_t bit_index;
    hal_gpio_driving_current_t driving_value = 0;

    reg_index = gpio_pin / 8;
    bit_index = (gpio_pin % 8) * 4;
    mode = (gpio_base->GPIO_MODE[reg_index] >> (bit_index) & 0xf);

    reg_index = gpio_pin / 32;
    bit_index = gpio_pin % 32;
    dir  = (gpio_base->GPIO_DIR[reg_index] >> (bit_index) & 0x1);
    din  = (gpio_base->GPIO_DIN[reg_index] >> (bit_index) & 0x1);
    dout = (gpio_base->GPIO_DOUT[reg_index] >> (bit_index) & 0x1);

    pu = 0xf;
    pd = 0xf;
    pupd = 0xf;
    r0   = 0xf;
    r1   = 0xf;

    shift = 0xff;
    pull_type = GPIO_PUPD_ERR;

    io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;
    shift = (gpio_pin <= 22) ? gpio_pin : (gpio_pin - 23);

    pu = (GPIO_REG32(io_cfg_base + 0x70) >> shift) & 0x01;
    pd = (GPIO_REG32(io_cfg_base + 0x50) >> shift) & 0x01;

    temp = (pu << 4) + pd;
    if((gpio_pin == 4) || (gpio_pin == 5) || (gpio_pin == 38) || (gpio_pin == 39)) {
        shift = ((gpio_pin == 4) || (gpio_pin == 38)) ? 0 : 2;     //gpio4/5/38/39
        rsel = (GPIO_REG32(io_cfg_base + 0x80)  >> shift) & 0x3;
        temp |= ((rsel & 0x1) << 8 | ((rsel >> 1) & 0x1) << 12);
    }

    for (j = 0; j < 10; j++) {
        if (temp == pull_map[j].temp) {
            pull_type = pull_map[j].pull;
            break;
        }
    }

    hal_gpio_get_driving_current((hal_gpio_pin_t)gpio_pin, &driving_value);

    gpio_state->mode = mode;
    gpio_state->dir  = dir;
    gpio_state->din  = din;
    gpio_state->dout = dout;
    gpio_state->pull_type = pull_type;
    gpio_state->current_type = (uint8_t)driving_value;

    //log_hal_msgid_info("GPIO%d, mode=%d, %s, din=%d, dout=%d, %s\r\n",6, gpio_pin, mode, direct[dir], din,dout,pull_state[pull_type]);
}

#endif

