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
#define DT_DRV_COMPAT awinic_aw95124
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pinctrl_soc.h>
#include "hal_gpt.h"
#include "hal_nvic.h"
#include "air_chip.h"
#include "hal_gpio.h"
#include "hal_i2c_master_internal.h"
#include "hal_i2c_master.h"
#include "hal_eint.h"
#include "io_expander.h"
#include "memory_attribute.h"

#if 0
#define log_epd_sensor_info(fmt, cnt, ...)     log_hal_msgid_info("[hal][rtc] " fmt, cnt, ##__VA_ARGS__)
#define log_epd_sensor_warning(fmt, cnt, ...)  log_hal_msgid_warning("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#define log_epd_sensor_error(fmt, cnt, ...)    log_hal_msgid_error("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#else
#define log_io_expander_sensor_info(fmt, cnt, ...)     printk(fmt, ##__VA_ARGS__)
#define log_io_expander_sensor_warning(fmt, cnt, ...)  printk(fmt, ##__VA_ARGS__)
#define log_io_expander_sensor_error(fmt, cnt, ...)    printk(fmt, ##__VA_ARGS__)
#endif
#define PIN_UNCONFIGURED 0xFF
/*irq_type_record*/
static uint8_t irq_trig_high[MAX_BANK];
static uint8_t irq_trig_low[MAX_BANK];
static uint8_t irq_trig_edge[MAX_BANK];

/*aw95124_register_init*/
static uint8_t aw_reg_init[] = {
	/* reg, data */
	0x40, 0x00,
	0x41, 0x00,
	0x42, 0x00,
	0x43, 0x00,
	0x44, 0x00,
	0x45, 0x00,
	0x4C, 0xFF,
	0x4D, 0x00,
	0x4E, 0x00,
	0x50, 0xFF,
	0x54, 0x00,
	0x51, 0x00,
	0x52, 0x00,
	0x5C, 0x00,
};

struct aw951xx_irq_work_context {
    struct k_work aw951xx_irq_work;
    const struct device *dev;
};

struct io_expander_sensor_data {
    bool init_flag;
    struct k_work *aw951xx_debounce_work;
};

struct io_expander_sensor_config {
    uint32_t frequency;
    uint8_t i2c_port_num;
    uint8_t rst_pin;
    uint8_t irq_pin;
    uint8_t i2c_addr;
};
hal_i2c_send_to_receive_config_ex_no_busy_t io_expander_i2c_no_busy_config;


static int  io_expander_init(const struct device *dev);
static int  io_expander_deinit(const struct device *dev);


static void aw951xx_eint_handler(void *data)
{
    hal_eint_mask(0);
    struct io_expander_sensor_data *sensor_data = (struct io_expander_sensor_data *)data;
    // log_io_expander_sensor_info("[IO_EXPANDER][AW951XX]aw951xx_eint_handler called",0);
    k_work_submit(sensor_data->aw951xx_debounce_work);
}

static void i2c_irq_callback(uint8_t slave_address,hal_i2c_callback_event_t event,void *user_data)
{
    volatile bool *flag = (volatile bool*)user_data;
    // log_io_expander_sensor_info("[IO_EXPANDER][AW951XX]i2c_irq_callback flag = %d",1,*flag);
    *flag = false;
}
static int aw951xx_i2c_write(const struct device *dev, uint8_t reg, uint8_t value)
{
    int ret;
    const struct io_expander_sensor_config *config = dev->config;
    ATTR_ALIGN(4) uint8_t data[2] = {reg, value};
    volatile bool i2c_write_flag_l = false;
    // return hal_i2c_master_send_polling(config->i2c_port_num, config->i2c_addr, data, sizeof(data));
    io_expander_i2c_no_busy_config.i2c_send_to_receive_config_ex.receive_buffer = NULL;
    io_expander_i2c_no_busy_config.i2c_send_to_receive_config_ex.receive_bytes_in_one_packet = 0;
    io_expander_i2c_no_busy_config.i2c_send_to_receive_config_ex.receive_packet_length = 0;
    io_expander_i2c_no_busy_config.i2c_send_to_receive_config_ex.send_data = data;
    io_expander_i2c_no_busy_config.i2c_send_to_receive_config_ex.send_bytes_in_one_packet = 2;
    io_expander_i2c_no_busy_config.i2c_send_to_receive_config_ex.send_packet_length = 1;
    io_expander_i2c_no_busy_config.user_data = (void*)&i2c_write_flag_l;
    i2c_write_flag_l = true;
    ret = hal_i2c_master_send_to_receive_dma_ex_none_blocking(config->i2c_port_num, &io_expander_i2c_no_busy_config);
    if (ret != 0) {
        return ret;
    }
    do
    {
    } while (i2c_write_flag_l == true);
    return ret;

}

static int aw951xx_i2c_read(const struct device *dev, uint8_t reg, uint8_t *value)
{
    int ret;
    const struct io_expander_sensor_config *config = dev->config;
    ATTR_ALIGN(4) uint8_t reg_data = reg;
    ATTR_ALIGN(4) uint8_t rx_data;
    volatile bool i2c_receive_flag_l = false;
    io_expander_i2c_no_busy_config.i2c_send_to_receive_config_ex.receive_buffer = &rx_data;
    io_expander_i2c_no_busy_config.i2c_send_to_receive_config_ex.receive_bytes_in_one_packet = 1;
    io_expander_i2c_no_busy_config.i2c_send_to_receive_config_ex.receive_packet_length = 1;
    io_expander_i2c_no_busy_config.i2c_send_to_receive_config_ex.send_data = &reg_data;
    io_expander_i2c_no_busy_config.i2c_send_to_receive_config_ex.send_bytes_in_one_packet = 1;
    io_expander_i2c_no_busy_config.i2c_send_to_receive_config_ex.send_packet_length = 1;
    io_expander_i2c_no_busy_config.user_data = (void*)&i2c_receive_flag_l;
    i2c_receive_flag_l = true;
    ret = hal_i2c_master_send_to_receive_dma_ex_none_blocking(config->i2c_port_num, &io_expander_i2c_no_busy_config);
    if (ret != 0) {
        return ret;
    }
    do
    {
    } while (i2c_receive_flag_l == true);
    *value = rx_data;
    return ret;
}

static int aw951xx_update_bits(const struct device *dev, uint8_t reg_addr, uint8_t mask, uint8_t reg_data)
{
    uint8_t reg_val;
    int ret;

    ret = aw951xx_i2c_read(dev, reg_addr, &reg_val);
    if (ret != 0) {
        return ret;
    }

    reg_val = (reg_val & ~mask) | (reg_data & mask);

    return aw951xx_i2c_write(dev, reg_addr, reg_val);
}

static int aw951xx_enable_interrupt(const struct device *dev, bool enable)// add api
{
    const struct io_expander_sensor_config *config = dev->config;
    struct io_expander_sensor_data *data = dev->data;
    hal_eint_status_t status;
    if (enable) {
        // Configure EINT
        hal_eint_config_t eint_config;
        eint_config.trigger_mode = HAL_EINT_LEVEL_LOW;
        eint_config.debounce_time = 0;
        status = hal_eint_init(config->irq_pin, &eint_config);
        if (status != HAL_EINT_STATUS_OK) {
            log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]EINT init failed: %d", 1, status);
            return -EIO;
        }
        status = hal_eint_register_callback(config->irq_pin, aw951xx_eint_handler, data);
        if (status != HAL_EINT_STATUS_OK) {
            log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]EINT callback register failed: %d", 1, status);
            return -EIO;
        }
        status = hal_eint_unmask(config->irq_pin);
        if (status != HAL_EINT_STATUS_OK) {
            log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]EINT unmask failed: %d", 1, status);
            return -EIO;
        }
        log_io_expander_sensor_info("[IO_EXPANDER][AW951XX]EINT callback registered successfully", 0);
    } else {
        // Disable interrupt
        status = hal_eint_deinit(config->irq_pin);
        if (status != HAL_EINT_STATUS_OK) {
            log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]Failed to mask EINT", 0);
            return -EIO;
        }
    }

    return 0;
}

static int aw951xx_hw_reset(const struct device *dev)
{
    const struct io_expander_sensor_config *config = dev->config;
    if (config->rst_pin == PIN_UNCONFIGURED) {
        log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]aw95124 Reset pin not configured",0);
        return AW_ERR;
    }
    hal_gpio_set_output(config->rst_pin, HAL_GPIO_DATA_HIGH);
    hal_gpt_delay_ms(1);
    hal_gpio_set_output(config->rst_pin, HAL_GPIO_DATA_LOW);
    hal_gpt_delay_ms(1);
    hal_gpio_set_output(config->rst_pin, HAL_GPIO_DATA_HIGH);
    hal_gpt_delay_ms(1);
    log_io_expander_sensor_info("[IO_EXPANDER][AW951XX]aw95124 HW Reset done",0);
    return AW_OK;
}

static int aw951xx_sw_reset(const struct device *dev)
{
    return aw951xx_i2c_write(dev, AW951XX_SOFT_RSTN_REG, AW951XX_RESET);
}

static int aw951xx_read_chipid(const struct device *dev)
{
	uint8_t cnt = 0;
	uint8_t chipid = 0;
	int ret;

	while (cnt < AW951XX_READ_CHIPID_RETRIES) {
		ret = aw951xx_i2c_read(dev, AW951XX_CHIPID_REG, &chipid);
		if (ret == AW_OK) {
			switch (chipid) {
			case AW95124QNR:
				log_io_expander_sensor_info("[IO_EXPANDER][AW951XX]AW95124QNR chip",0);
				return AW_OK;
			case AW95124FOR:
				log_io_expander_sensor_info("[IO_EXPANDER][AW951XX]AW95124FOR chip",0);
				return AW_OK;
			default:
				log_io_expander_sensor_info("[IO_EXPANDER][AW951XX]chip is unsupported device! chipid is 0x%x", 1, chipid);
				continue;
			}
		}
		cnt++;
	}

	return -AW_ERR;
}

static int aw951xx_chip_init(const struct device *dev)
{
    int ret = 0;
	for (int i = 0; i < sizeof(aw_reg_init); i = i + 2) {
		ret = aw951xx_i2c_write(dev, aw_reg_init[i], aw_reg_init[i + 1]);
		if (ret != AW_OK)
			return ret;
	}
    return AW_OK;
}


static int aw951xx_gpio_pull(const struct device *dev, uint8_t gpio_num,enum aw951xx_gpio_pull pull)
{
    int ret = 0;
    uint8_t port = gpio_num / BANK_SZ;
    uint8_t pin = gpio_num % BANK_SZ;
    uint8_t mask = 1 << pin;

    // Configure pull enable
    if (pull != AW951XX_GPIO_PULL_DISABLE) {
        ret = aw951xx_update_bits(dev, AW951XX_P0PE_REG + port,
                                  mask, mask);
        if (ret != AW_OK)
            return ret;
    } else {
        ret = aw951xx_update_bits(dev, AW951XX_P0PE_REG + port,
                                  mask, 0);
        if (ret != AW_OK)
            return ret;
    }

    // Configure pull mode
    if (pull == AW951XX_GPIO_PULL_UP) {
        ret = aw951xx_update_bits(dev, AW951XX_P0PMD_REG + port,
                                  mask, mask);
    } else if (pull == AW951XX_GPIO_PULL_DOWN) {
        ret = aw951xx_update_bits(dev, AW951XX_P0PMD_REG + port,
                                  mask, 0);
    }
    if (ret != AW_OK)
        return ret;

    return ret;
}

static int aw951xx_gpio_config(const struct device *dev, uint8_t gpio_num,
                        enum aw951xx_gpio_dir dir,
                        enum aw951xx_gpio_drive drive,
                        enum aw951xx_gpio_pull pull)
{
    int ret;
    uint8_t port = gpio_num / BANK_SZ;
    uint8_t pin = gpio_num % BANK_SZ;
    uint8_t mask = 1 << pin;
    // Configure direction
    if(dir == AW951XX_GPIO_INPUT)
    {
        log_io_expander_sensor_info( "[IO_EXPANDER][AW951XX] GPIO_DIRECTION_INPUT: gpio_num: %d",1,gpio_num);
    }else{
        log_io_expander_sensor_info( "[IO_EXPANDER][AW951XX] GPIO_DIRECTION_OUTPUT: gpio_num: %d",1, gpio_num);
    }

    ret = aw951xx_update_bits(dev, AW951XX_P0OEN_REG + port,
                              mask,
                              dir ? mask : 0);
    if (ret != AW_OK)
        return ret;

    // Configure pull enable
    if (pull != AW951XX_GPIO_PULL_DISABLE) {
        ret = aw951xx_update_bits(dev, AW951XX_P0PE_REG + port,
                                  mask, mask);
        if (ret != AW_OK)
            return ret;
    } else {
        ret = aw951xx_update_bits(dev, AW951XX_P0PE_REG + port,
                                  mask, 0);
        if (ret != AW_OK)
            return ret;
    }

    // Configure pull mode
    if (pull == AW951XX_GPIO_PULL_UP) {
        ret = aw951xx_update_bits(dev, AW951XX_P0PMD_REG + port,
                                  mask, mask);
    } else if (pull == AW951XX_GPIO_PULL_DOWN) {
        ret = aw951xx_update_bits(dev, AW951XX_P0PMD_REG + port,
                                  mask, 0);
    }
    if (ret != AW_OK)
        return ret;

    // Configure output mode
    ret = aw951xx_update_bits(dev, AW951XX_P0DSR1_REG + gpio_num / DRIVER_LEVEL_BANK_SZ,
                              0x03 << ((gpio_num % DRIVER_LEVEL_BANK_SZ) * 2),
                              (drive & 0x03) << ((gpio_num % DRIVER_LEVEL_BANK_SZ) * 2));
    return ret;
}

static void aw951xx_irq_set_type(const struct device *dev, uint8_t gpio, uint8_t type)
{
	uint8_t port = gpio / BANK_SZ;
	uint8_t mask = 1 << (gpio % BANK_SZ);
    // struct io_expander_sensor_data *dev_data = dev->data;
	if (type == AW951XX_INI_TRIGGER_HIGH)
		irq_trig_high[port] |= mask;
	else
		irq_trig_high[port] &= ~mask;

	if (type == AW951XX_INI_TRIGGER_LOW)
		irq_trig_low[port] |= mask;
	else
	    irq_trig_low[port] &= ~mask;

	if (type == AW951XX_INI_TRIGGER_RISING || type == AW951XX_INI_TRIGGER_FALLING ||
			type == AW951XX_INI_TRIGGER_DUAL_EDGE)
		irq_trig_edge[port] |= mask;
	else
		irq_trig_edge[port] &= ~mask;

	// log_io_expander_sensor_info("[IO_EXPANDER][AW951XX]irq_num = %lu, irq_trig_high[%d] = 0x%02X, irq_trig_low[%d] = 0x%02X\n",5,
	// 			gpio, port, irq_trig_high[port],
	// 			port, irq_trig_low[port]);
	log_io_expander_sensor_info("[IO_EXPANDER][AW951XX]irq_trig_edge[%d] = 0x%02X", 2,
			port, irq_trig_edge[port]);
}

static int aw951xx_update_trigger(const struct device *dev, uint8_t gpio_num, uint32_t trigger_type)
{
	int ret = 0;
	uint32_t trigger_val = 0;
    uint8_t port = gpio_num / TRIG_MODE_BANK_SZ;
    uint8_t pin = gpio_num % TRIG_MODE_BANK_SZ;
    // uint8_t mask = 0x03 << pin;
	switch (trigger_type) {
	case AW951XX_INI_TRIGGER_RISING:
		trigger_val = 1;
		break;
	case AW951XX_INI_TRIGGER_FALLING:
		trigger_val = 2;
		break;
	case AW951XX_INI_TRIGGER_DUAL_EDGE:
		trigger_val = 3;
		break;
	case AW951XX_INI_TRIGGER_HIGH:
	case AW951XX_INI_TRIGGER_LOW:
	default:
		trigger_val = 0;
	}

	ret = aw951xx_update_bits( dev,
				AW951XX_P0EDGE1_REG + port,
				0x03 << (pin * 2),
				(trigger_val & 0x03) << (pin * 2));
	if (ret != AW_OK)
		return ret;

	aw951xx_irq_set_type(dev, gpio_num, trigger_type);

	return ret;
}

static int aw951xx_irq_enable(const struct device *dev, uint8_t gpio_num, bool enable)
{
    uint8_t port = gpio_num / BANK_SZ;
    uint8_t pin = gpio_num % BANK_SZ;
    uint8_t mask = 1 << pin;
    int ret;
	ret = aw951xx_update_bits(dev,
		AW951XX_P0LE_REG + port,
		mask, 
        enable ? mask : 0);
	if (ret != AW_OK)
		return ret;
    // Enable/disable interrupt mask
    return aw951xx_update_bits(dev, AW951XX_P0MSK_REG + port,
                               mask,
                               enable ? 0 : mask);
}

static int aw951xx_gpio_direction_input(const struct device *dev, uint8_t gpio_num)
{
    uint8_t port = gpio_num / BANK_SZ;
    uint8_t pin = gpio_num % BANK_SZ;
    uint8_t mask = 1 << pin;
	if (dev == NULL) {
		log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]AW951XX dev ERROR!!",0);
		return -AW_ERR;
	}
    log_io_expander_sensor_info( "[IO_EXPANDER][AW951XX] GPIO_DIRECTION_INPUT: gpio_num: %d",1,
			 gpio_num);
	return aw951xx_update_bits(dev,
				AW951XX_P0OEN_REG + port,
				mask, mask);
}

static int aw951xx_gpio_direction_output(const struct device *dev, uint8_t gpio_num, int value)
{
	int ret = 0;
    uint8_t port = gpio_num / BANK_SZ;
    uint8_t pin = gpio_num % BANK_SZ;
    uint8_t mask = 1 << pin;
	if (dev == NULL) {
		log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]AW951XX dev ERROR!!",0);
		return -AW_ERR;
	}

	log_io_expander_sensor_info( "[IO_EXPANDER][AW951XX] GPIO_DIRECTION_OUTPUT: gpio_num: %d, value: %d",2,
			 gpio_num, value);
	/* set direction */
	ret = aw951xx_update_bits(dev,
				AW951XX_P0OEN_REG + port,
				mask, 0);
	if (ret != AW_OK)
		return ret;
	/* then output level */
	return aw951xx_update_bits(dev,
				AW951XX_P0DO_REG + port,
				mask,
				value ? mask : 0);
}

static int aw951xx_gpio_set_value(const struct device *dev, uint32_t gpio_num, uint32_t value)
{
	if (dev == NULL) {
		log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]AW951XX dev ERROR!!",0);
		return -AW_ERR;
	}

	log_io_expander_sensor_info( "[IO_EXPANDER][AW951XX]AW951XX set gpio num:%d, val:%d", 2, gpio_num, value);

	return aw951xx_update_bits(dev,
				AW951XX_P0DO_REG + gpio_num / BANK_SZ,
				1 << (gpio_num % BANK_SZ),
				value ? (1 << (gpio_num % BANK_SZ)) : 0);
}

static int aw951xx_get_all_input_status(const struct device *dev, uint32_t *input_status)
{
	uint8_t input_b0;
	uint8_t input_b1;
	uint8_t input_b2;
	int ret;

	ret = aw951xx_i2c_read(dev, AW951XX_P0DI_REG, &input_b0);
	if (ret != AW_OK)
	{
		return ret;
	}
	ret = aw951xx_i2c_read(dev, AW951XX_P1DI_REG, &input_b1);
	if (ret != AW_OK)
	{
		return ret;
	}
	ret = aw951xx_i2c_read(dev, AW951XX_P2DI_REG, &input_b2);
	if (ret != AW_OK)
	{
		return ret;
	}

	*input_status = ((input_b2<<16) | (input_b1<<8) | (input_b0));

	return AW_OK;
}

static int aw951xx_get_all_interrupt_status(const struct device *dev, uint32_t *interrupt_status)
{
    int ret;
	uint8_t intstatus_b0;
	uint8_t intstatus_b1;
	uint8_t intstatus_b2;
	ret = aw951xx_i2c_read(dev, AW951XX_P0INST_REG, &intstatus_b0);
	if (ret != AW_OK)
	{
		return ret;
	}
	ret = aw951xx_i2c_read(dev, AW951XX_P1INST_REG, &intstatus_b1);
	if (ret != AW_OK)
	{
		return ret;
	}
	ret = aw951xx_i2c_read(dev, AW951XX_P2INST_REG, &intstatus_b2);
	if (ret != AW_OK)
	{
		return ret;
	}

	*interrupt_status = ((intstatus_b0<<16) | (intstatus_b1<<8) | (intstatus_b2));

	return AW_OK;
}

static void configure_aw95124_gpios(const struct device *dev)
{
    uint8_t i = 0;
    /* M1 - M6  0~5 */
    for(i = 0; i < 6; i++) {
        aw951xx_gpio_config(dev, i, AW951XX_GPIO_INPUT, AW951XX_GPIO_DRIVE_1X, AW951XX_GPIO_PULL_UP);
        aw951xx_update_trigger(dev, i, AW951XX_INI_TRIGGER_DUAL_EDGE);
        aw951xx_irq_enable(dev, i, true);
    }

    /* G1 - G5  8~12 */
    for(i = 8; i <= 12; i++)
    {
        aw951xx_gpio_config(dev, i, AW951XX_GPIO_INPUT, AW951XX_GPIO_DRIVE_1X, AW951XX_GPIO_PULL_UP);
        aw951xx_update_trigger(dev, i, AW951XX_INI_TRIGGER_DUAL_EDGE);
        aw951xx_irq_enable(dev, i, true);
    }

    /* PAIRING :13  VIEW :14  MENU :16  LT Mode :17  RT Mode :18  */
    for(i = 13; i <= 14; i++) {
        aw951xx_gpio_config(dev, i, AW951XX_GPIO_INPUT, AW951XX_GPIO_DRIVE_1X, AW951XX_GPIO_PULL_UP);
        aw951xx_update_trigger(dev, i, AW951XX_INI_TRIGGER_DUAL_EDGE);
        aw951xx_irq_enable(dev, i, true);
    }
    for(i = 16; i <= 18; i++) {
        aw951xx_gpio_config(dev, i, AW951XX_GPIO_INPUT, AW951XX_GPIO_DRIVE_1X, AW951XX_GPIO_PULL_UP);
        aw951xx_update_trigger(dev, i, AW951XX_INI_TRIGGER_DUAL_EDGE);
        aw951xx_irq_enable(dev, i, true);
    }

    // uint8_t edge_mask = 0;
    // for ( i = 0; i < 6; i++)
    // {
    //     aw951xx_i2c_read(dev, AW951XX_P0EDGE1_REG+i, &edge_mask);
    //     log_io_expander_sensor_info("[IO_EXPANDER][AW951XX] P%d edge mask: 0x%x",2, i, edge_mask);
    //     if(i<3){
    //        aw951xx_i2c_read(dev, AW951XX_P0LE_REG+i, &edge_mask);
    //        log_io_expander_sensor_info("[IO_EXPANDER][AW951XX] P%d LE: 0x%x",2, i, edge_mask);
    //        aw951xx_i2c_read(dev, AW951XX_P0MSK_REG+i, &edge_mask);
    //        log_io_expander_sensor_info("[IO_EXPANDER][AW951XX] P%d mask: 0x%x",2, i, edge_mask);
    //     }
    // }

    /* Output pins */
    const uint8_t output_pins[] = {15, 19, 20, 21, 22, 23};//15:VLED_EN, 19:MOTOR_EN, 20:TMR_EN, 21:STM_VDD_EN, 22:LED_EN 23:BTA_DETECT_ON_OFF
    for (i = 0; i < sizeof(output_pins)/sizeof(output_pins[0]); i++) {
        aw951xx_irq_enable(dev, output_pins[i], false);
        aw951xx_gpio_config(dev, output_pins[i], AW951XX_GPIO_OUTPUT, AW951XX_GPIO_DRIVE_1X, AW951XX_GPIO_PULL_UP);
        if(output_pins[i] == 22||output_pins[i] == 23){
            aw951xx_gpio_set_value(dev, output_pins[i], 0);
        }else{
            aw951xx_gpio_set_value(dev, output_pins[i], 1);
        }
    }
}


// static int aw951xx_gpio_get_direction(const struct device *dev, uint32_t gpio_num, enum aw951xx_gpio_dir *dir)
// {
//     uint8_t port = gpio_num / BANK_SZ;
//     uint8_t pin = gpio_num % BANK_SZ;
//     uint8_t reg_val;
//     int ret;

//     ret = aw951xx_i2c_read(dev, AW951XX_P0OEN_REG + port, &reg_val);
//     if (ret != AW_OK)
//         return ret;

//     *dir = (reg_val & (1 << pin)) ? AW951XX_GPIO_INPUT : AW951XX_GPIO_OUTPUT;
//     return AW_OK;
// }



static int aw951xx_and_i2c_init(const struct device *dev)
{
    const struct io_expander_sensor_config *config = dev->config;
    struct io_expander_sensor_data *dev_data = dev->data;
    int ret;
    io_expander_i2c_no_busy_config.i2c_config.frequency = config->frequency;
    io_expander_i2c_no_busy_config.i2c_send_to_receive_config_ex.slave_address = config->i2c_addr;
    io_expander_i2c_no_busy_config.i2c_callback = i2c_irq_callback;
    io_expander_i2c_no_busy_config.user_data = NULL;
    log_io_expander_sensor_info("[IO_EXPANDER][AW951XX]reset_pin: %d, irq_pin: %d, i2c_addr: %d, i2c_port_num: %d, frequency: %d", 5,
        config->rst_pin, config->irq_pin, config->i2c_addr, config->i2c_port_num, config->frequency);
    switch (config->frequency){
        #if defined(AIR_BTD_IC_PREMIUM_G1)
        case 50000:
            io_expander_i2c_no_busy_config.i2c_config.frequency = HAL_I2C_FREQUENCY_50K;
            break;
        case 100000:
            io_expander_i2c_no_busy_config.i2c_config.frequency = HAL_I2C_FREQUENCY_100K;
            break;
        case 200000:
            io_expander_i2c_no_busy_config.i2c_config.frequency = HAL_I2C_FREQUENCY_200K;
            break;
        case 300000:
            io_expander_i2c_no_busy_config.i2c_config.frequency = HAL_I2C_FREQUENCY_300K;
            break;
        case 400000:
            io_expander_i2c_no_busy_config.i2c_config.frequency = HAL_I2C_FREQUENCY_400K;
            break;
        case 722000:
            io_expander_i2c_no_busy_config.i2c_config.frequency = HAL_I2C_FREQUENCY_722K;
            break;
        case 1000000:
            io_expander_i2c_no_busy_config.i2c_config.frequency = HAL_I2C_FREQUENCY_1M;
            break;
            #ifdef HAL_I2C_MASTER_FEATURE_HIGH_SPEED
            case 2000000:
                io_expander_i2c_no_busy_config.i2c_config.frequency = HAL_I2C_FREQUENCY_2M;
                break;
            case 3000000:
                io_expander_i2c_no_busy_config.i2c_config.frequency = HAL_I2C_FREQUENCY_3M;
                break;
            case 2500000:
                io_expander_i2c_no_busy_config.i2c_config.frequency = HAL_I2C_FREQUENCY_2M5;
                break;
            case 2800000:
                io_expander_i2c_no_busy_config.i2c_config.frequency = HAL_I2C_FREQUENCY_2M8;
                break;
            #endif
    #endif
        #if defined(AIR_BTD_IC_MANDATORY_G1)
        case 100000:
            io_expander_i2c_no_busy_config.i2c_config.frequency = HAL_I2C_FREQUENCY_100K;
            break;
        case 400000:
            io_expander_i2c_no_busy_config.i2c_config.frequency = HAL_I2C_FREQUENCY_400K;
            break;
        case 800000:
            io_expander_i2c_no_busy_config.i2c_config.frequency = HAL_I2C_FREQUENCY_800K;
            break;
        case 1000000:
            io_expander_i2c_no_busy_config.i2c_config.frequency = HAL_I2C_FREQUENCY_1M;
        break;
        #endif
        default:
            log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]Invalid I2C frequency", 0);
            return -EINVAL;
    }


    /* hardware reset start */
    ret = aw951xx_hw_reset(dev);
    if(ret != 0){
        log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]Failed to HW reset AW95124",0);
        return ret;
    }
    /* hardware reset end */

    /* software reset start */
    ret = aw951xx_sw_reset(dev);
    if(ret != 0){
        log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]Failed to SW reset AW95124",0);
        return ret;
    }
    log_io_expander_sensor_info("[IO_EXPANDER][AW951XX]SW reset AW95124 successfully",0);
    /* software reset end */

    /* read_chipid start */
    ret = aw951xx_read_chipid(dev);
    if(ret != 0){
        log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]Failed to read chip ID of AW95124",0);
        return ret;
    }
    /* read_chipid end */

    /* chip init start */
    ret = aw951xx_chip_init(dev);
    if(ret != 0){
        log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]Failed to initialize chip AW95124",0);
        return ret;
    }
    log_io_expander_sensor_info("[IO_EXPANDER][AW951XX]AW95124 chip initialized successfully",0);
    /* chip init end */

    /* Configure GPIOs start*/
    configure_aw95124_gpios(dev);// add io config api
    /* Configure GPIOs end*/

    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    dev_data->init_flag = true;
    hal_nvic_restore_interrupt_mask(mask);

    /*Configure interrupt pin start*/
    if (config->irq_pin != PIN_UNCONFIGURED) {
        // Enable interrupt
        ret = aw951xx_enable_interrupt(dev, true);
        if (ret != 0) {
            log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]Failed to enable interrupt", 0);
            return ret;
        }
    }
    /*Configure interrupt pin end*/
    log_io_expander_sensor_info("[IO_EXPANDER][AW951XX]AW95124 driver initialized successfully",0);
    return 0;
}


static int aw951xx_and_i2c_deinit(const struct device *dev)
{
    uint32_t mask;
    int ret = 0;
    const struct io_expander_sensor_config *config = dev->config;
    struct io_expander_sensor_data *dev_data = dev->data;
    // Disable interrupt
    hal_eint_status_t status;
    status = hal_eint_deinit(config->irq_pin);
    if (status != HAL_EINT_STATUS_OK) {
        log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]Failed to mask EINT", 0);
        return -EIO;
    }
    hal_nvic_save_and_set_interrupt_mask(&mask);
    dev_data->init_flag = false;
    hal_nvic_restore_interrupt_mask(mask);
    hal_gpio_set_output(config->rst_pin, HAL_GPIO_DATA_LOW);
    hal_gpt_delay_ms(1);
    hal_gpio_set_output(config->rst_pin, HAL_GPIO_DATA_HIGH);
    hal_gpt_delay_ms(1);
    hal_gpio_set_output(config->rst_pin, HAL_GPIO_DATA_LOW);
    log_io_expander_sensor_info("[IO_EXPANDER][AW951XX]  deinit success",0);
    return ret;
}

static int  io_expander_enter_low_power(const struct device *dev)
{
    const struct io_expander_sensor_config *config = dev->config;
    // if (config->rst_pin == 0xFF) {
    //     log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]aw95124 Reset pin not configured",0);
    //     return AW_ERR;
    // }
    // int ret = 0;
    // Disable interrupt
    hal_eint_status_t status;
    status = hal_eint_deinit(config->irq_pin);
    if (status != HAL_EINT_STATUS_OK) {
        log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]Failed to mask EINT", 0);
        return -EIO;
    }
    log_io_expander_sensor_info("[IO_EXPANDER][AW951XX] io_expander_enter_low_power",0);
    return status;
    // hal_gpio_set_output(config->rst_pin, HAL_GPIO_DATA_LOW);
    // hal_gpt_delay_ms(1);
    // hal_gpio_set_output(config->rst_pin, HAL_GPIO_DATA_HIGH);
    // hal_gpt_delay_ms(1);
    // hal_gpio_set_output(config->rst_pin, HAL_GPIO_DATA_LOW);
    // return ret;



    // hal_eint_disable(config->irq_pin);
    // return 0;
}

static int  io_expander_exit_low_power(const struct device *dev)
{
    const struct io_expander_sensor_config *config = dev->config;
    struct io_expander_sensor_data *data = dev->data;
    hal_eint_status_t status;
    hal_eint_config_t eint_config;
    eint_config.trigger_mode = HAL_EINT_LEVEL_LOW;
    eint_config.debounce_time = 0;
    status = hal_eint_init(config->irq_pin, &eint_config);
    if (status != HAL_EINT_STATUS_OK) {
        log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]EINT init failed: %d", 1, status);
        return -EIO;
    }
    status = hal_eint_register_callback(config->irq_pin, aw951xx_eint_handler, data);
    if (status != HAL_EINT_STATUS_OK) {
        log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]EINT callback register failed: %d", 1, status);
        return -EIO;
    }
    status = hal_eint_unmask(config->irq_pin);
    if (status != HAL_EINT_STATUS_OK) {
        log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]EINT unmask failed: %d", 1, status);
        return -EIO;
    }
    log_io_expander_sensor_info("[IO_EXPANDER][AW951XX]EINT callback register success,io_expander_exit_low_power",0);
    uint32_t input_status;
    if(aw951xx_get_all_input_status(dev,&input_status))///clear interrupt status
    {
        log_io_expander_sensor_error("[IO_EXPANDER][AW951XX]Get input status failed",0);
    }
    return status;

    // const struct io_expander_sensor_config *config = dev->config;
    // // return io_expander_init(dev);
    // hal_eint_enable(config->irq_pin);
    // return 0;

    // return io_expander_init(dev);

}

static int  io_expander_init(const struct device *dev)
{
    return aw951xx_and_i2c_init(dev);
}

static int  io_expander_deinit(const struct device *dev)
{

    return aw951xx_and_i2c_deinit(dev);
}

static int  io_expander_pin_config(const struct device *dev,int pin_num, io_expander_pin_config_t* config)
{
    int ret = 0;
    ret = aw951xx_gpio_config(dev, pin_num, config->pin_dir, config->pin_driver, config->pin_pull);
    if(ret != 0){
        log_io_expander_sensor_error("[IO_EXPANDER][AW951XX] Failed to configure pin %d, error: %d",2, pin_num, ret);
        return ret;
    }
    if(config->pin_irq_en != 0){
        ret = aw951xx_update_trigger(dev, pin_num, config->pin_irq_type);
        if(ret != 0){
            log_io_expander_sensor_error("[IO_EXPANDER][AW951XX] Failed to update trigger for pin %d, error: %d",2, pin_num, ret);
        }
        ret = aw951xx_irq_enable(dev, pin_num, true);
        if(ret != 0){
            log_io_expander_sensor_error("[IO_EXPANDER][AW951XX] Failed to irq enable for pin %d, error: %d",2, pin_num, ret);
        }
    }
    log_io_expander_sensor_info("[IO_EXPANDER][AW951XX] Successfully configured pin %d",2, pin_num);
    return ret;
}

// static int  io_expander_irq_type_set(const struct device *dev,int pin_num, int irq_type)
// {
//     int ret = 0;
//     ret = aw951xx_update_trigger(dev, pin_num, irq_type);
//     return ret;
// }

// static int io_expander_irq_enable(const struct device *dev, int pin_num, int irq_enable)
// {
//     int ret = 0;
//     ret = aw951xx_irq_enable(dev, pin_num, irq_enable);
//     return ret;
// }

// io_expander_pin_value_set(const struct device *dev, uint32_t gpio_num, int value)
// {
//     int ret = 0;
//     ret = aw951xx_gpio_set_value(dev, gpio_num, value);
//     return ret;
// }

static int io_expander_attr_set(const struct device *dev, enum sensor_channel chan,
                            enum sensor_attribute attr,
                            const struct sensor_value *val)
{
    int ret = 0;
    struct io_expander_sensor_data *dev_data = dev->data;
    if (!dev_data->init_flag) {
        if ((uint32_t)attr == IO_EXPANDER_ATTR_INIT) {
            dev_data->aw951xx_debounce_work = (struct k_work*)(val->val1);
            log_io_expander_sensor_info("[IO_EXPANDER][AW951XX] dev_data->aw951xx_debounce_work = %x",1,
                dev_data->aw951xx_debounce_work);
            return io_expander_init(dev);
        } else {
            log_io_expander_sensor_error("[IO_EXPANDER][AW951XX] Set attr failed: not initialized, attr:%d", 1, attr);
            return -EBUSY;
        }
    }
    switch((uint32_t)attr){
        case IO_EXPANDER_ATTR_PIN_CONFIG:
            ret = io_expander_pin_config(dev,val->val1,(io_expander_pin_config_t *)val->val2);
        break;
        case IO_EXPANDER_ATTR_PIN_IRQ_TYPE_CONFIG:
            ret = aw951xx_update_trigger(dev,val->val1,val->val2);
        break;
        case IO_EXPANDER_ATTR_PIN_IRQ_ENABLE:
            ret = aw951xx_irq_enable(dev, val->val1,val->val2);
        break;
        case IO_EXPANDER_ATTR_PIN_DIR_INPUT:
            ret = aw951xx_gpio_direction_input(dev, val->val1);
        break;
        case IO_EXPANDER_ATTR_PIN_DIR_OUTPUT:
            ret = aw951xx_gpio_direction_output(dev, val->val1,val->val2);
        break;
        case IO_EXPANDER_ATTR_PIN_PULL_SET:
            ret = aw951xx_gpio_pull(dev, val->val1, val->val2);
        break;
        case IO_EXPANDER_ATTR_PIN_VALUE_SET:
            ret = aw951xx_gpio_set_value(dev, val->val1, val->val2);
        break;
        case IO_EXPANDER_ATTR_ENTER_LOW_POWER:
            ret = io_expander_enter_low_power(dev);
        break;
        case IO_EXPANDER_ATTR_EXIT_LOW_POWER:
            ret = io_expander_exit_low_power(dev);
        break;
        case IO_EXPANDER_ATTR_DEINIT:
            ret = io_expander_deinit(dev);
        break;
    }
    return ret;
}

static int io_expander_attr_get(const struct device *dev, enum sensor_channel chan,
                            enum sensor_attribute attr,
                            struct sensor_value *val)
{
    struct io_expander_sensor_data *dev_data = dev->data;
    int ret = 0;
    if (!dev_data->init_flag) {
            log_io_expander_sensor_error("[IO_EXPANDER][AW951XX] sensor attr get failed, not init,attr:%d",attr);
            return -EBUSY;
    }
    switch((uint32_t)attr){
        case IO_EXPANDER_ATTR_ALL_INPUT:
            if((uint32_t)chan == IO_EXPANDER_CHAN_RAM_DATA){
                log_io_expander_sensor_error("[IO_EXPANDER][AW951XX] sensor attr get failed, all_input_status need to read from hardware",0);
            }else{
                ret = aw951xx_get_all_input_status(dev,&(val->val1));
            }
            break;
        case IO_EXPANDER_ATTR_ALL_INTS:
            if((uint32_t)chan == IO_EXPANDER_CHAN_RAM_DATA){
                log_io_expander_sensor_error("[IO_EXPANDER][AW951XX] sensor attr get failed, all_interrupt_status need to read from hardware",0);
            }else{
                ret = aw951xx_get_all_interrupt_status(dev,&(val->val1));
            }
            break;

    }
    return ret;
}

static int aw951xx_sensor_init(const struct device *dev)
{
    struct io_expander_sensor_data *dev_data = dev->data;
    dev_data->init_flag = false;
    return 0;
}
static const struct sensor_driver_api aw951xx_driver_api = {
    .attr_set = io_expander_attr_set,
    .attr_get = io_expander_attr_get,
};

#define AW95124_DEVICE(id) \
static struct io_expander_sensor_data aw95124_p##id##_data; \
\
static const struct io_expander_sensor_config aw95124_p##id##_config = { \
    .frequency    = DT_PROP(DT_PARENT(DT_DRV_INST(id)), frequency),		\
    .i2c_port_num = DT_PROP(DT_PARENT(DT_DRV_INST(id)), port),		\
    .rst_pin      = DT_PROP(DT_DRV_INST(id), reset_pin), \
    .irq_pin      = DT_PROP(DT_DRV_INST(id), irq_pin), \
    .i2c_addr     = DT_PROP(DT_DRV_INST(id), i2c_addr), \
}; \
    \
DEVICE_DT_INST_DEFINE(id, \
                    aw951xx_sensor_init, \
                    NULL, \
                    &aw95124_p##id##_data, \
                    &aw95124_p##id##_config, \
                    CONFIG_IO_EXPANDER_SENSOR_INIT_LEVEL, \
                    CONFIG_IO_EXPANDER_SENSOR_INIT_PRIORITY, \
                    &aw951xx_driver_api);

DT_INST_FOREACH_STATUS_OKAY(AW95124_DEVICE)