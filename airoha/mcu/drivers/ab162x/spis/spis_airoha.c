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

#define DT_DRV_COMPAT airoha_air_spis

#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <errno.h>
#include <zephyr/drivers/spi.h>
#include "hal_spi_slave.h"
#include "air_chip.h"

// #include <../drivers/spi/spi_context.h>
struct spis_airoha_data {
	uint32_t data;
	bool    initialized;
	// struct spi_context ctx;

};

struct spis_airoha_config {
	SPIS_REGISTER_T *base;
	uint8_t port_num;
};
static int spis_airoha_transceive(const struct device *dev,
				const struct spi_config *config,
				const struct spi_buf_set *tx_bufs,
				const struct spi_buf_set *rx_bufs)
{
	struct spis_airoha_data *dev_data = dev->data;
	const struct spis_airoha_config *dev_config = dev->config;
	// struct spi_context *ctx = &dev_data->ctx;
	hal_spi_slave_config_t spi_config;
	if(dev_data->initialized){
		hal_spi_slave_deinit(dev_config->port_num);
		dev_data->initialized = false;
	}
	if(SPI_MODE_GET(config->operation) & SPI_MODE_CPOL){
		spi_config.polarity = HAL_SPI_SLAVE_CLOCK_POLARITY1;
	}else{
		spi_config.polarity = HAL_SPI_SLAVE_CLOCK_POLARITY0;
	}
	if(SPI_MODE_GET(config->operation) & SPI_MODE_CPHA){
		spi_config.phase = HAL_SPI_SLAVE_CLOCK_PHASE1;
	}else{
		spi_config.phase = HAL_SPI_SLAVE_CLOCK_PHASE0;
	}
	if(((config->operation) & SPI_TRANSFER_LSB) & SPI_TRANSFER_LSB){
		spi_config.bit_order = HAL_SPI_SLAVE_LSB_FIRST;
	}else{
		spi_config.bit_order = HAL_SPI_SLAVE_MSB_FIRST;
	}
	spi_config.timeout_threshold = 0xFFFFFFFF;
	hal_spi_slave_init(dev_config->port_num,&spi_config);
	dev_data->initialized = true;
	return 0;
}
#ifdef CONFIG_SPI_ASYNC
static int 	spis_airoha_transceive_async(const struct device *dev,
							const struct spi_config *config,
							const struct spi_buf_set *tx_bufs,
							const struct spi_buf_set *rx_bufs,
							struct k_poll_signal *async){

	return 0;
}
#endif /* CONFIG_SPI_ASYNC */

static int spis_airoha_transceive_release(const struct device *dev,
			     const struct spi_config *config)
{

	return 0;
	// struct spis_airoha_data *dev_data = dev->data;

	// spi_context_unlock_unconditionally(&dev_data->ctx);
}

static int spis_init(const struct device *dev)
{

	// const struct spis_airoha_config *dev_config = dev->config;
	// hal_spis_set_address(dev_config->base,dev_config->port_num);

	return 0;
}

static const struct spi_driver_api spis_airoha_driver_api = {
	.transceive = spis_airoha_transceive,
#ifdef CONFIG_SPI_ASYNC
	.transceive_async = spis_airoha_transceive_async,
#endif /* CONFIG_SPI_ASYNC */
	.release = spis_airoha_transceive_release,
};



#define	SPIS_AIROHA_DEVICE(id)						\
									\
static struct spis_airoha_data spis_airoha_p##id##_data;		\
									\
static const struct spis_airoha_config spis_airoha_p##id##_config = {		\
    .base = (SPIS_REGISTER_T *)DT_INST_REG_ADDR(id),   \
	.port_num = DT_INST_PROP(id, port),		\
};									\
									\
DEVICE_DT_INST_DEFINE(id,						\
	    spis_init,						\
	    NULL,							\
	    &spis_airoha_p##id##_data,					\
	    &spis_airoha_p##id##_config, 					\
	    CONFIG_SPIS_INIT_LEVEL, CONFIG_SPIS_INIT_PRIORITY, &spis_airoha_driver_api);

DT_INST_FOREACH_STATUS_OKAY(SPIS_AIROHA_DEVICE)
