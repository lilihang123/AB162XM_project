/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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
#include "hal_nvic.h"
#include "hal_clock_internal.h"
#include "hal_log.h"
#include "hal_pmu.h"

#ifdef __cplusplus
extern "C" {
#endif

GPIO_BASE_REGISTER_T *gpio_base = (GPIO_BASE_REGISTER_T *)(GPIO_BASE);
GPIO_CFG0_REGISTER_T *gpio_cfg0 = (GPIO_CFG0_REGISTER_T *)(IO_CFG_0_BASE);
GPIO_CFG1_REGISTER_T *gpio_cfg1 = (GPIO_CFG1_REGISTER_T *)(IO_CFG_1_BASE);

void hal_gpio_contrler_debug(uint32_t reg_num ,uint32_t index_num)
{   
    //set debug pin to low
    gpio_base->GPIO_DOUT_CLR[reg_num] = (GPIO_REG_ONE_BIT_SET_CLR << index_num);
    //set debug pin to high
    gpio_base->GPIO_DOUT_SET[reg_num] = (GPIO_REG_ONE_BIT_SET_CLR << index_num);
    //set degug pin to low
    gpio_base->GPIO_DOUT_CLR[reg_num] = (GPIO_REG_ONE_BIT_SET_CLR << index_num);
}

hal_gpio_status_t hal_gpio_driver_init()
{
    //This register can filter out the jitter signal of the line. It is recommended to open
    gpio_cfg0->GPIO_SMT.SET = (0x7FFFF);
    gpio_cfg1->GPIO_SMT.SET = (0x1FFFFF);
#ifdef HAL_PMU_MODULE_ENABLED
    pmu_pinmux_init();
#endif/*HAL_PMU_MODULE_ENABLED*/
    return HAL_GPIO_STATUS_OK;
}

hal_gpio_status_t hal_gpio_init(hal_gpio_pin_t gpio_pin)
{
    (void)gpio_pin;
    return HAL_GPIO_STATUS_OK;
}

hal_gpio_status_t hal_gpio_deinit(hal_gpio_pin_t gpio_pin)
{
    (void)gpio_pin;
    return HAL_GPIO_STATUS_OK;
}

hal_gpio_status_t hal_gpio_set_direction(hal_gpio_pin_t gpio_pin, hal_gpio_direction_t gpio_direction)
{
    uint32_t reg_num;
    uint32_t index_num;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    reg_num   = gpio_pin / GPIO_DIR_REG_CTRL_PIN_NUM;
    index_num = gpio_pin % GPIO_DIR_REG_CTRL_PIN_NUM;

    if (gpio_direction == HAL_GPIO_DIRECTION_INPUT) {
        gpio_base->GPIO_DIR_CLR[reg_num] = (GPIO_REG_ONE_BIT_SET_CLR << index_num);
    } else {
        gpio_base->GPIO_DIR_SET[reg_num] = (GPIO_REG_ONE_BIT_SET_CLR << index_num);
    }

    return HAL_GPIO_STATUS_OK;

}

hal_gpio_status_t hal_gpio_get_direction(hal_gpio_pin_t gpio_pin, hal_gpio_direction_t *gpio_direction)
{
    uint32_t reg_num;
    uint32_t index_num;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    if (NULL == gpio_direction) {
        return HAL_GPIO_STATUS_INVALID_PARAMETER;
    }

    reg_num   = gpio_pin / GPIO_DIR_REG_CTRL_PIN_NUM;
    index_num = gpio_pin % GPIO_DIR_REG_CTRL_PIN_NUM;

    if (gpio_base->GPIO_DIR[reg_num] & (GPIO_REG_ONE_BIT_SET_CLR << index_num)) {
        *gpio_direction = HAL_GPIO_DIRECTION_OUTPUT;
    } else {
        *gpio_direction = HAL_GPIO_DIRECTION_INPUT;
    }

    return HAL_GPIO_STATUS_OK;
}

bool pmu_in_signal_function_check(hal_gpio_pin_t gpio_pin, uint8_t function_index)
{
    uint32_t valid_mask = 0;

    switch (function_index) {
        case GPIO_PMU_MODE1:
            valid_mask = (1 << HAL_GPIO_0) | (1 << HAL_GPIO_1) |
                         (1 << HAL_GPIO_4) | (1 << HAL_GPIO_23) |
                         (1 << HAL_GPIO_24)| (1 << HAL_GPIO_25);
            break;
        case GPIO_PMU_MODE2:
            valid_mask = (1 << HAL_GPIO_1) | (1 << HAL_GPIO_4) |
                         (1 << HAL_GPIO_23)| (1 << HAL_GPIO_24);
            break;
        default:
            return false;
    }

    return (valid_mask & (1 << gpio_pin)) != 0;
}

bool g_cfg_function_check(hal_gpio_pin_t gpio_pin, uint8_t function_index)
{
    switch (function_index)
    {
        case GPIO_AUX_MODE11:
            // Allowed pins for GPIO_AUX_MODE11.
            return (((gpio_pin >= HAL_GPIO_25) && (gpio_pin <= HAL_GPIO_37)) || ((gpio_pin >= HAL_GPIO_40) && (gpio_pin <= HAL_GPIO_43)));
        case GPIO_PMU_MODE3:
            // Valid range for GPIO_PMU_MODE3: HAL_GPIO_23 to HAL_GPIO_34.
            return ((gpio_pin >= HAL_GPIO_23) && (gpio_pin <= HAL_GPIO_34));
        default:
            return false;
    }
}

hal_gpio_status_t hal_gpio_set_analog_mode(hal_gpio_pin_t gpio_pin)
{
    uint8_t  shift;
    uint32_t io_cfg_base;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;
    shift = (gpio_pin <= 22) ? gpio_pin : (gpio_pin - 23);

    GPIO_REG32(io_cfg_base + 0x30 + GPIO_CLR_ADDR) = 1 << shift;   //G_CFG RG

    return HAL_GPIO_STATUS_OK;
}

hal_gpio_status_t hal_gpio_clear_analog_mode(hal_gpio_pin_t gpio_pin)
{
    uint8_t  shift;
    uint32_t io_cfg_base;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;
    shift = (gpio_pin <= 22) ? gpio_pin : (gpio_pin - 23);

    GPIO_REG32(io_cfg_base + 0x30 + GPIO_SET_ADDR) = 1 << shift;   //G_CFG RG

    return HAL_GPIO_STATUS_OK;
}

hal_gpio_status_t hal_gpio_set_rtc_in_en(hal_gpio_pin_t gpio_pin)
{
    uint8_t  bit_shift;
    uint32_t io_cfg_base;
    uint8_t  reg_shift;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;
    bit_shift = (gpio_pin <= 22) ? gpio_pin : (gpio_pin - 23);
    reg_shift = (gpio_pin <= 22) ? 0xE0 : 0xF0;

    GPIO_REG32(io_cfg_base + reg_shift + GPIO_SET_ADDR) = 1 << bit_shift;

    return HAL_GPIO_STATUS_OK;
}

hal_gpio_status_t hal_gpio_clear_rtc_in_en(hal_gpio_pin_t gpio_pin)
{
    uint8_t  bit_shift;
    uint32_t io_cfg_base;
    uint8_t  reg_shift;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;
    bit_shift = (gpio_pin <= 22) ? gpio_pin : (gpio_pin - 23);
    reg_shift = (gpio_pin <= 22) ? 0xE0 : 0xF0;

    GPIO_REG32(io_cfg_base + reg_shift + GPIO_CLR_ADDR) = 1 << bit_shift;

    return HAL_GPIO_STATUS_OK;
}

hal_pinmux_status_t hal_pinmux_set_function(hal_gpio_pin_t gpio_pin, uint8_t function_index)
{
    uint8_t reg_num;
    uint8_t remainder;
    uint8_t  shift;
    uint32_t io_cfg_base;

    printk("[pinmux] pin=%d mode=%d\r\n", gpio_pin, function_index);

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_PINMUX_STATUS_ERROR_PORT;
    }

    /* check whether the function index is right as one function is corresponding to 4 bits of oen pin */
    if (function_index > GPIO_MODE_MAX_NUMBER) {
        return HAL_PINMUX_STATUS_INVALID_FUNCTION;
    }
	
	io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;

    /* protect the configuration to prevent possible interrupt */
    if(function_index <= GPIO_AUX_MODE_MAX_NUMBER) {
        /* get the register number corresponding to the pin as one register can control 8 pins*/
        reg_num = gpio_pin / GPIO_MODE_REG_CTRL_PIN_NUM;
        /* get the bit offset within the register as one register can control 8 pins*/
        remainder = gpio_pin % GPIO_MODE_REG_CTRL_PIN_NUM;

        gpio_base->GPIO_MODE_CLR[reg_num] = (0xF << (remainder * GPIO_MODE_FUNCTION_CTRL_BITS));
        gpio_base->GPIO_MODE_SET[reg_num] = (function_index << (remainder * GPIO_MODE_FUNCTION_CTRL_BITS));

        /* clear gpio pmu function*/
        shift = gpio_cfg_table[gpio_pin].rtc_gpio_mode_reg_shift;
        if (shift != 0xFF) {
            GPIO_REG32((io_cfg_base + gpio_cfg_table[gpio_pin].rtc_gpio_mode_reg) + GPIO_CLR_ADDR) = (0x3) << shift;
        }

        /* clear rtc in en*/
        hal_gpio_clear_rtc_in_en(gpio_pin);

    } else {
        if (pmu_in_signal_function_check(gpio_pin, function_index)) {
            hal_gpio_set_rtc_in_en(gpio_pin); 
        }
        shift = gpio_cfg_table[gpio_pin].rtc_gpio_mode_reg_shift;
        /* switch to digital mode for leakage, ADC driver change it to analog mode. */
        if (shift != 0xFF) {
            if ((function_index == GPIO_PMU_MODE2) &&
                (gpio_pin == HAL_GPIO_35 || gpio_pin == HAL_GPIO_36 ||
                 gpio_pin == HAL_GPIO_37 || gpio_pin == HAL_GPIO_39))
            {
                GPIO_REG32((IO_CFG_1_BASE + gpio_cfg_table[gpio_pin].rtc_gpio_mode_reg) + GPIO_CLR_ADDR) = (0x3) << shift;
                GPIO_REG32((IO_CFG_1_BASE + gpio_cfg_table[gpio_pin].rtc_gpio_mode_reg) + GPIO_SET_ADDR) = (0x1) << shift;
            } else {
                GPIO_REG32((io_cfg_base + gpio_cfg_table[gpio_pin].rtc_gpio_mode_reg) + GPIO_CLR_ADDR) = (0x3) << shift;
                GPIO_REG32((io_cfg_base + gpio_cfg_table[gpio_pin].rtc_gpio_mode_reg) + GPIO_SET_ADDR) = (function_index - GPIO_AUX_MODE_MAX_NUMBER) << shift;
            }
        }
    }

    if (g_cfg_function_check(gpio_pin, function_index)) {
        hal_gpio_set_analog_mode(gpio_pin);
    }else{
        /* switch to digital mode for leakage, ADC driver change it to analog mode. */  
        hal_gpio_clear_analog_mode(gpio_pin);
    }

    return HAL_PINMUX_STATUS_OK;
}

uint8_t hal_gpio_get_pinmux_function(hal_gpio_pin_t gpio_pin)
{
    uint8_t reg_num;
    uint8_t index_num;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return 0xff;
    }

    reg_num   = gpio_pin / GPIO_MODE_REG_CTRL_PIN_NUM;
    index_num = gpio_pin % GPIO_MODE_REG_CTRL_PIN_NUM;

    return ((gpio_base->GPIO_MODE[reg_num] >> (index_num * GPIO_MODE_FUNCTION_CTRL_BITS)) & 0xf);
}

hal_gpio_status_t hal_gpio_get_input(hal_gpio_pin_t gpio_pin, hal_gpio_data_t *gpio_data)
{
    uint32_t reg_num;
    uint32_t index_num;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    if (NULL == gpio_data) {
        return HAL_GPIO_STATUS_INVALID_PARAMETER;
    }

    reg_num   = gpio_pin / GPIO_DIN_REG_CTRL_PIN_NUM;
    index_num = gpio_pin % GPIO_DIN_REG_CTRL_PIN_NUM;

    if (gpio_base->GPIO_DIN[reg_num] & (GPIO_REG_ONE_BIT_SET_CLR << index_num)) {
        *gpio_data = HAL_GPIO_DATA_HIGH;
    } else {
        *gpio_data = HAL_GPIO_DATA_LOW;
    }

    return HAL_GPIO_STATUS_OK;

}


hal_gpio_status_t hal_gpio_set_output(hal_gpio_pin_t gpio_pin, hal_gpio_data_t gpio_data)
{
    uint32_t reg_num;
    uint32_t index_num;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    reg_num   = gpio_pin / GPIO_DOUT_REG_CTRL_PIN_NUM;
    index_num = gpio_pin % GPIO_DOUT_REG_CTRL_PIN_NUM;

    if (gpio_data==HAL_GPIO_DATA_HIGH) {
        gpio_base->GPIO_DOUT_SET[reg_num] = (GPIO_REG_ONE_BIT_SET_CLR << index_num);
    } else {
        gpio_base->GPIO_DOUT_CLR[reg_num] = (GPIO_REG_ONE_BIT_SET_CLR << index_num);
    }

    return HAL_GPIO_STATUS_OK;
}


hal_gpio_status_t hal_gpio_get_output(hal_gpio_pin_t gpio_pin, hal_gpio_data_t *gpio_data)
{
    uint32_t reg_num;
    uint32_t index_num;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    if (NULL == gpio_data) {
        return HAL_GPIO_STATUS_INVALID_PARAMETER;
    }

    reg_num   = gpio_pin / GPIO_DOUT_REG_CTRL_PIN_NUM;
    index_num = gpio_pin % GPIO_DOUT_REG_CTRL_PIN_NUM;

    if (gpio_base->GPIO_DOUT[reg_num] & (GPIO_REG_ONE_BIT_SET_CLR << index_num)) {
        *gpio_data = HAL_GPIO_DATA_HIGH;
    } else {
        *gpio_data = HAL_GPIO_DATA_LOW;
    }

    return HAL_GPIO_STATUS_OK;

}

hal_gpio_status_t hal_gpio_toggle_pin(hal_gpio_pin_t gpio_pin)
{

    uint32_t reg_num = 0;
    uint32_t index_num = 0;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    reg_num   = gpio_pin / GPIO_DOUT_REG_CTRL_PIN_NUM;
    index_num = gpio_pin % GPIO_DOUT_REG_CTRL_PIN_NUM;

    if (gpio_base->GPIO_DOUT[reg_num] & (GPIO_REG_ONE_BIT_SET_CLR << index_num)) {

        gpio_base->GPIO_DOUT_CLR[reg_num] = (GPIO_REG_ONE_BIT_SET_CLR << index_num);
    } else {
        gpio_base->GPIO_DOUT_SET[reg_num] = (GPIO_REG_ONE_BIT_SET_CLR << index_num);
    }

    return HAL_GPIO_STATUS_OK;
}

hal_gpio_status_t hal_gpio_get_input_port(int port, uint32_t *value)
{
    *value=gpio_base->GPIO_DIN[port];
    return HAL_GPIO_STATUS_OK;
}

hal_gpio_status_t hal_gpio_set_output_port(int port, uint32_t mask,uint32_t value)
{
    if (value) {
        gpio_base->GPIO_DOUT_SET[port] = mask;
    } else {
        gpio_base->GPIO_DOUT_CLR[port] = mask;
    }
    return HAL_GPIO_STATUS_OK;
}

hal_gpio_status_t hal_gpio_set_output_toggle(int port, uint32_t mask)
{
    uint32_t value;
    value = gpio_base->GPIO_DOUT[port];
    gpio_base->GPIO_DOUT_SET[port]= value ^ mask;
    return HAL_GPIO_STATUS_OK;

}

hal_gpio_status_t hal_gpio_set_rsel_register(hal_gpio_pin_t gpio_pin, uint8_t gpio_rsel0, uint8_t gpio_rsel1)
{
    uint8_t rsel_shift;
    uint32_t io_cfg_base;
    uint8_t  shift_addr[2] = {GPIO_CLR_ADDR, GPIO_SET_ADDR};

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;
    rsel_shift = ((gpio_pin == 4) || (gpio_pin == 38)) ? 0 : 2;     //gpio 4/5/38/39

    GPIO_REG32(io_cfg_base + 0x80 + shift_addr[gpio_rsel0 ? 1 : 0]) = 1 << rsel_shift;
    GPIO_REG32(io_cfg_base + 0x80 + shift_addr[gpio_rsel1 ? 1 : 0]) = 1 << rsel_shift;

    return HAL_GPIO_STATUS_OK;
}

hal_gpio_status_t hal_gpio_set_pu4p7k_register(hal_gpio_pin_t gpio_pin, uint8_t gpio_pu4p7k)
{
    uint8_t pu4p7k_shift = 0;
    uint32_t io_cfg_base;
    uint8_t  shift_addr[2] = {GPIO_CLR_ADDR, GPIO_SET_ADDR};

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;
    if(gpio_pin < 4){
        pu4p7k_shift = gpio_pin;
    }else if(gpio_pin >= 6 && gpio_pin <= 22){
        pu4p7k_shift = gpio_pin - 2;
    }else if(gpio_pin >= 23 && gpio_pin <= 37){
        pu4p7k_shift = gpio_pin - 23;
    }else if(gpio_pin >= 40 && gpio_pin <= 47){
        pu4p7k_shift = gpio_pin - 25;
    }

    GPIO_REG32(io_cfg_base + 0x60 + shift_addr[gpio_pu4p7k ? 1 : 0])  = 1 << pu4p7k_shift;
    return HAL_GPIO_STATUS_OK;
}
hal_gpio_status_t hal_gpio_pull_up(hal_gpio_pin_t gpio_pin)
{
    uint8_t  shift;
    uint32_t io_cfg_base;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;
    shift = (gpio_pin <= 22) ? gpio_pin : (gpio_pin - 23);

    GPIO_REG32(io_cfg_base + 0x50 + GPIO_CLR_ADDR) = 1 << shift;   //PD
    GPIO_REG32(io_cfg_base + 0x70 + GPIO_SET_ADDR) = 1 << shift;   //PU

    return HAL_GPIO_STATUS_OK;
}

hal_gpio_status_t hal_gpio_pull_down(hal_gpio_pin_t gpio_pin)
{
    uint8_t  shift;
    uint32_t io_cfg_base;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;
    shift = (gpio_pin <= 22) ? gpio_pin : (gpio_pin - 23);

    GPIO_REG32(io_cfg_base + 0x70 + GPIO_CLR_ADDR) = 1 << shift;   //PU
    GPIO_REG32(io_cfg_base + 0x50 + GPIO_SET_ADDR) = 1 << shift;   //PD

    return HAL_GPIO_STATUS_OK;
}



hal_gpio_status_t hal_gpio_disable_pull(hal_gpio_pin_t gpio_pin)
{
    uint8_t  shift;
    uint32_t io_cfg_base;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;
    shift = (gpio_pin <= 22) ? gpio_pin : (gpio_pin - 23);

    GPIO_REG32(io_cfg_base + 0x70 + GPIO_CLR_ADDR) = 1 << shift;   //PU
    GPIO_REG32(io_cfg_base + 0x50 + GPIO_CLR_ADDR) = 1 << shift;   //PD

    return HAL_GPIO_STATUS_OK;
}

#ifdef HAL_GPIO_FEATURE_CLOCKOUT
hal_gpio_status_t hal_gpio_set_clockout(hal_gpio_clock_t gpio_clock_num, hal_gpio_clock_mode_t clock_mode)
{
    if (gpio_clock_num >= HAL_GPIO_CLOCK_MAX) {
        return HAL_GPIO_STATUS_INVALID_PARAMETER;
    }

    switch (gpio_clock_num) {
        case HAL_GPIO_CLOCK_0:
            GPIO_CLKO_CTRL_A_REG.CLK_MODE0 = clock_mode;
            break;
        case HAL_GPIO_CLOCK_1:
            GPIO_CLKO_CTRL_A_REG.CLK_MODE1 = clock_mode;
            break;
        case HAL_GPIO_CLOCK_2:
            GPIO_CLKO_CTRL_A_REG.CLK_MODE2 = clock_mode;
            break;
        case HAL_GPIO_CLOCK_3:
            GPIO_CLKO_CTRL_A_REG.CLK_MODE3 = clock_mode;
            break;
        default:
            break;
    }

    return HAL_GPIO_STATUS_OK;
}
#endif

#ifdef HAL_GPIO_FEATURE_SET_SCHMITT
hal_gpio_status_t hal_gpio_set_schmitt(hal_gpio_pin_t gpio_pin)
{
    uint8_t  shift;
    uint32_t io_cfg_base;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;
    shift = (gpio_pin <= 22) ? gpio_pin : (gpio_pin - 23);

    GPIO_REG32(io_cfg_base + 0x90 + GPIO_SET_ADDR) = 1 << shift;   //SMT RG

    return HAL_GPIO_STATUS_OK;
}

hal_gpio_status_t hal_gpio_clear_schmitt(hal_gpio_pin_t gpio_pin)
{
    uint8_t  shift;
    uint32_t io_cfg_base;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;
    shift = (gpio_pin <= 22) ? gpio_pin : (gpio_pin - 23);

    GPIO_REG32(io_cfg_base + 0x90 + GPIO_CLR_ADDR) = 1 << shift;   //SMT RG

    return HAL_GPIO_STATUS_OK;
}
#endif

#ifdef HAL_GPIO_FEATURE_SET_SLEW_RATE
hal_gpio_status_t hal_gpio_set_slew_rate(hal_gpio_pin_t gpio_pin)
{
    uint8_t  shift;
    uint32_t io_cfg_base;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;
    shift = (gpio_pin <= 22) ? gpio_pin : (gpio_pin - 23);

    GPIO_REG32(io_cfg_base + 0xA0 + GPIO_SET_ADDR) = 1 << shift;   //SR RG

    return HAL_GPIO_STATUS_OK;
}

hal_gpio_status_t hal_gpio_clear_slew_rate(hal_gpio_pin_t gpio_pin)
{
    uint8_t  shift;
    uint32_t io_cfg_base;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;
    shift = (gpio_pin <= 22) ? gpio_pin : (gpio_pin - 23);

    GPIO_REG32(io_cfg_base + 0xA0 + GPIO_CLR_ADDR) = 1 << shift;   //SR RG

    return HAL_GPIO_STATUS_OK;
}
#endif

#ifdef HAL_GPIO_FEATURE_HIGH_Z
hal_gpio_status_t hal_gpio_set_high_impedance(hal_gpio_pin_t gpio_pin)
{
    hal_pinmux_status_t ret1;
    hal_gpio_status_t   ret2;
    uint8_t shift;
    uint32_t io_cfg_base;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    /* set GPIO mode of pin */
    ret1 = hal_pinmux_set_function(gpio_pin, 0);
    if (ret1 != HAL_PINMUX_STATUS_OK) {
        return HAL_GPIO_STATUS_ERROR;
    }

    /* set input direction of pin */
    ret2 = hal_gpio_set_direction(gpio_pin, HAL_GPIO_DIRECTION_INPUT);
    if (ret2 != HAL_GPIO_STATUS_OK) {
        return ret2;
    }

    io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;
    shift = (gpio_pin <= 22) ? gpio_pin : (gpio_pin - 23);

    GPIO_REG32(io_cfg_base + 0x40 + GPIO_CLR_ADDR) = 1 << shift;   //IES RG

    /* disable pull function of pin */
    ret2 = hal_gpio_disable_pull(gpio_pin);
    if (ret2 != HAL_GPIO_STATUS_OK) {
        return ret2;
    }

    return HAL_GPIO_STATUS_OK;
}


hal_gpio_status_t hal_gpio_clear_high_impedance(hal_gpio_pin_t gpio_pin)
{

    hal_pinmux_status_t ret1;
    hal_gpio_status_t   ret2;
    uint8_t shift;
    uint32_t io_cfg_base;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    /* set GPIO mode of pin. */
    ret1 = hal_pinmux_set_function(gpio_pin, 0);
    if (ret1 != HAL_PINMUX_STATUS_OK) {
        return HAL_GPIO_STATUS_ERROR;
    }

    /* set input direction of pin. */
    ret2 = hal_gpio_set_direction(gpio_pin, HAL_GPIO_DIRECTION_INPUT);
    if (ret2 != HAL_GPIO_STATUS_OK) {
        return ret2;
    }

    /* Enable input buffer enable function of pin */
    io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;
    shift = (gpio_pin <= 22) ? gpio_pin : (gpio_pin - 23);

    GPIO_REG32(io_cfg_base + 0x40 + GPIO_SET_ADDR) = 1 << shift;   //IES RG

    /* enable pull down of pin. */
    ret2 = hal_gpio_pull_down(gpio_pin);
    if (ret2 != HAL_GPIO_STATUS_OK) {
        return ret2;
    }

    return HAL_GPIO_STATUS_OK;
}
#endif

#ifdef HAL_GPIO_FEATURE_SET_CAPACITANCE
hal_gpio_status_t hal_gpio_set_capacitance(hal_gpio_pin_t gpio_pin, hal_gpio_capacitance_t cap)
{
    uint8_t  shift;
    uint32_t io_cfg_base;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }
    if (cap >= HAL_GPIO_CAPACITANCE_MAX) {
        return HAL_GPIO_STATUS_INVALID_PARAMETER;
    }

    io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;
    shift = ((gpio_pin == 4) || (gpio_pin == 38)) ? 0 : 4;     //gpio4/5/38/39

    GPIO_REG32(io_cfg_base + 0x20 + GPIO_CLR_ADDR) = GPIO_REG_THREE_BIT_SET_CLR << shift;   //EH RG
    GPIO_REG32(io_cfg_base + 0x20 + GPIO_SET_ADDR) = ((cap << 1) | 0x1)  << shift;   //EH RG

    return HAL_GPIO_STATUS_OK;
}

hal_gpio_status_t hal_gpio_clear_capacitance(hal_gpio_pin_t gpio_pin)
{
    uint8_t  shift;
    uint32_t io_cfg_base;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;
    shift = ((gpio_pin == 4) || (gpio_pin == 38)) ? 0 : 4;     //gpio4/5/38/39

    GPIO_REG32(io_cfg_base + 0x20 + GPIO_CLR_ADDR) = GPIO_REG_THREE_BIT_SET_CLR << shift;   //EH RG

    return HAL_GPIO_STATUS_OK;
}
#endif

#ifdef HAL_GPIO_FEATURE_SET_DRIVING
hal_gpio_status_t hal_gpio_set_driving_current(hal_gpio_pin_t gpio_pin, hal_gpio_driving_current_t driving)
{
    uint32_t mask;
    uint8_t  shift;
    uint32_t temp;
    uint32_t io_cfg_base;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }
    if (driving >= HAL_GPIO_DRIVING_CURRENT_MAX) {
        return HAL_GPIO_STATUS_INVALID_PARAMETER;
    }

    io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;
    shift = gpio_cfg_table[gpio_pin].drv_shift;

    hal_nvic_save_and_set_interrupt_mask(&mask);

    temp = GPIO_REG32(io_cfg_base + gpio_cfg_table[gpio_pin].drv_reg);
    temp &= ~(GPIO_REG_THREE_BIT_SET_CLR << shift);
    temp |= (driving << shift);
    GPIO_REG32(io_cfg_base + gpio_cfg_table[gpio_pin].drv_reg) = temp;

    hal_nvic_restore_interrupt_mask(mask);

    return HAL_GPIO_STATUS_OK;
}


hal_gpio_status_t hal_gpio_get_driving_current(hal_gpio_pin_t gpio_pin, hal_gpio_driving_current_t *driving)
{
    uint32_t mask;
    uint8_t  shift;
    uint32_t temp;
    uint32_t io_cfg_base;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    io_cfg_base = (gpio_pin <= 22) ? IO_CFG_0_BASE : IO_CFG_1_BASE;
    shift = gpio_cfg_table[gpio_pin].drv_shift;

    hal_nvic_save_and_set_interrupt_mask(&mask);

    temp = GPIO_REG32(io_cfg_base + gpio_cfg_table[gpio_pin].drv_reg);
    temp = (temp >> shift) & GPIO_REG_THREE_BIT_SET_CLR;

    *driving = (hal_gpio_driving_current_t)(temp);

    hal_nvic_restore_interrupt_mask(mask);

    return HAL_GPIO_STATUS_OK;

}
#endif

hal_gpio_status_t hal_gpio_get_input_by_mask(gpio_data_in_mask_t *inout_data_mask)
{   
    uint32_t mask;
    if (NULL == inout_data_mask) {
        return HAL_GPIO_STATUS_INVALID_PARAMETER;
    }

    hal_nvic_save_and_set_interrupt_mask(&mask);
    inout_data_mask->register0 = gpio_base->GPIO_DIN[0];
    inout_data_mask->register1 = gpio_base->GPIO_DIN[1];
    hal_nvic_restore_interrupt_mask(mask);

    return HAL_GPIO_STATUS_OK;
}

#ifdef HAL_SLEEP_MANAGER_ENABLED
hal_gpio_status_t hal_gpio_wakeup_extend_sleep_config(hal_gpio_pin_t gpio_pin)
{
    uint16_t pmu_eint_value;
    uint8_t  reg_num;
    uint8_t  index_num;
    uint16_t temp;
    uint16_t mask_temp;
    uint32_t mask;

    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    /*RTC_ENABLE*/
    hal_gpio_set_rtc_in_en(gpio_pin);

    /*config pmu eint failing egdge*/
    reg_num   = gpio_pin / 8;
    index_num = gpio_pin % 8;

    hal_nvic_save_and_set_interrupt_mask(&mask);

    pmu_eint_value = 0x2 << (index_num * 2);
    mask_temp = ~(0x3 << (index_num * 2));
    temp = pmu_get_strup_rg((25 + reg_num));
    temp &= mask_temp;
    temp |= pmu_eint_value;
    pmu_set_strup_rg((25 + reg_num), temp); 

    hal_nvic_restore_interrupt_mask(mask);

    /*clear all eint irq  spm config */
    pmu_set_strup_rg(35, 0xFFFF);
    pmu_set_strup_rg(36, 0xFFFF);
    pmu_set_strup_rg(37, 0xFFFF);

    if(gpio_pin <= 22) {
        *(volatile uint32_t *)(0x421300e0) |= (1 << gpio_pin);
    } else {
        *(volatile uint32_t *)(0x421300e4) |= (1 << (gpio_pin - 23));
    }

    return HAL_GPIO_STATUS_OK;
}


hal_gpio_status_t hal_gpio_wakeup_extend_sleep_clear(hal_gpio_pin_t gpio_pin)
{
    if (gpio_pin >= HAL_GPIO_MAX) {
        return HAL_GPIO_STATUS_ERROR_PIN;
    }

    /* clear RTC_ENABLE*/
    hal_gpio_clear_rtc_in_en(gpio_pin);

    if(gpio_pin <= 22) {
        *(volatile uint32_t *)(0x421300e0) &= ~(1 << gpio_pin);
    } else {
        *(volatile uint32_t *)(0x421300e4) &= ~(1 << (gpio_pin - 23));
    }

    return HAL_GPIO_STATUS_OK;

}
#endif




#ifdef __cplusplus
}
#endif

#endif  /* HAL_GPIO_MODULE_ENABLED */

