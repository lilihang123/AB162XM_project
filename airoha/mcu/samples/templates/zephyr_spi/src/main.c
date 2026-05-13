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

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app, LOG_LEVEL_INF);

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/drivers/spi.h>
#include "hal_spi_master.h"
#include "hal_spi_master_internal.h"
#include "hal_spi_slave.h"
#include "hal_spi_slave_internal.h"
#include "hal_clock.h"

#include <stdint.h>
#include "hal_gpio.h"


#include "air_chip.h"
#include "hal_platform.h"

#if defined(HAL_GPT_MODULE_ENABLED)
#include "hal_gpt.h"
#endif

#include "memory_attribute.h"
#include "autoconf.h"

#ifdef CONFIG_AIR_WDT
#include "wdt_airoha.h"
#endif

uint8_t spi_port = 0;
ATTR_RWDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN  uint8_t tx_bufe[20] = {0x01, 0x01, 0x02, 0x03,0xff};
ATTR_RWDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN  uint8_t rx_bufe[20]={0};
ATTR_RWDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN  uint16_t m_tx_bufe[10] = {0x01, 0x01, 0x02, 0x03,0xff};
ATTR_RWDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN  uint16_t m_rx_bufe[10]={0};

hal_spi_slave_status_t s_status;
hal_spi_master_status_t m_status;

#define SPIBB_NODE	DT_NODELABEL(spibb0)
#define SPI_PIN_CLK 37
#define SPI_PIN_MOSI 35
#define SPI_PIN_MISO 36
#define SPI_PIN_CSN 34

/*
 * writes 5 9bit words, you can check the output with a logic analyzer
 */

 void test_spi_function(const struct device *dev,struct spi_cs_control *cs)
 {
	struct spi_config config;
 	config.frequency = 1000000;
 	config.operation = SPI_OP_MODE_MASTER;
 	config.slave = 0;
 	config.cs = *cs;

    // int buff[1] = {0xa55aa55a};
    m_tx_bufe[0] = 0xa5;
    m_tx_bufe[1] = 0x5a;
 	int len =sizeof(m_tx_bufe);

 	struct spi_buf tx_buf = { .buf = m_tx_bufe, .len = len };
	struct spi_buf_set tx_bufs = { .buffers =&tx_buf, .count = 1 };

 	int ret = spi_write(dev, &config, &tx_bufs);

 	printf("basic_write_9bit_words; ret: %d\n", ret);

 }

 void test_basic_write_9bit_words(const struct device *dev,
 				 struct spi_cs_control *cs)
 {
    printk("-------------------------------");
	struct spi_config config;

 	config.frequency = 1000000;
 	config.operation = SPI_OP_MODE_MASTER| SPI_WORD_SET(9);
 	config.slave = 0;
 	config.cs = *cs;

	uint16_t buf[5] = { 0x0101, 0x00ff, 0x00a5, 0x0000, 0x0102};
	for(int i=0;i<5;i++)
	{
	m_tx_bufe[i]=buf[i];
	}
	int len = 5 * sizeof(buf[0]);

 	struct spi_buf tx_buf = { .buf = m_tx_bufe, .len = len};
	struct spi_buf_set tx_bufs = { .buffers = &tx_buf, .count = 1 };

 	int ret = spi_write(dev, &config, &tx_bufs);

 	printk("basic_write_9bit_words; ret: %d\n", ret);
 	printk(" wrote %04x %04x %04x %04x %04x\n",
		buf[0], buf[1], buf[2], buf[3], buf[4]);
 }

 /*
 * A more complicated xfer, sends two words, then sends and receives another
  * 3 words. Connect MOSI to MISO to test read
 */
//  void test_9bit(const struct device *dev,
//  				struct spi_cs_control *cs)
// {
// 	struct spi_config config;

//  	config.frequency =  1000000;
//  	config.operation = SPI_OP_MODE_MASTER | SPI_WORD_SET(9);
//  	config.slave = 0;
//  	config.cs = *cs;

// 	uint16_t buff[5] = { 0x0101, 0x0102, 0x0003, 0x0004, 0x0105};
// 	for(int i=0;i<5;i++)
// 	{
// 	m_tx_bufe[i]=buff[i];
// 	}
// 	const int stride = sizeof(buff[0]);

// struct spi_buf tx_buf[1] = {
// 		{.buf = m_tx_bufe, .len = (2) * stride},
//  		//{.buf = m_tx_bufe + (2), .len = (datacount - 2)*stride},
//  	};


// struct spi_buf_set tx_set = { .buffers = tx_buf, .count = 1 };
// int ret = spi_transceive(dev, &config, &tx_set, NULL);
// printk("9bit_loopback_partial; ret: %d\n", ret);

// }
 void test_9bit_loopback_partial(const struct device *dev,
 				struct spi_cs_control *cs)
 {
	printk("-------------------------------");
	struct spi_config config;

 	config.frequency =  1000000;
 	config.operation = SPI_OP_MODE_MASTER | SPI_WORD_SET(9);
 	config.slave = 0;
 	config.cs = *cs;

 	enum { datacount = 5 };
 	uint16_t buff[datacount] = { 0x0101, 0x0102, 0x0003, 0x0004, 0x0105};

	for(int i=0;i<5;i++)
	{
	m_tx_bufe[i]=buff[i];
	}

	const int stride = sizeof(buff[0]);

	struct spi_buf tx_buf[2] = {
		{.buf = m_tx_bufe, .len = (2) * stride},
 		{.buf = m_tx_bufe + (4), .len = (datacount - 2)*stride},
 	};
	printk("code buf:%x",(unsigned int)m_tx_bufe);
    printk("code_rxbuf:%x",(unsigned int)m_rx_bufe);
	struct spi_buf rx_buf[2] = {
 		{.buf = m_rx_bufe, .len = (2) * stride},
 		{.buf = m_rx_bufe + (4), .len = (datacount - 2) * stride},
 	};

 	struct spi_buf_set tx_set = { .buffers = tx_buf, .count = 2 };
 	struct spi_buf_set rx_set = { .buffers = rx_buf, .count = 2 };

 	int ret = spi_transceive(dev, &config, &tx_set, &rx_set);

 	printk("9bit_loopback_partial; ret: %d\n", ret);
 	printk(" tx (i)  : %04x %04x\n", m_tx_bufe[0],m_tx_bufe[1]);
 	printk(" tx (ii) : %04x %04x %04x\n", m_tx_bufe[2], m_tx_bufe[3], m_tx_bufe[4]);
 	printk(" rx (ii) : %04x %04x %04x\n", m_rx_bufe[0], m_rx_bufe[1], m_rx_bufe[2]);
 }

 /*
  * Tests 8 bit transfer at higher frequency, at this frequency there won't be
  * any busy waits between clock edges, the rate is limited by gpio calls etc.
  */
 void test_8bit_xfer(const struct device *dev, struct spi_cs_control *cs)
 {
 	struct spi_config config;

	 printk("-------------------------------");
	config.frequency = 1000000;
 	config.operation = SPI_OP_MODE_MASTER| SPI_WORD_SET(8) ;
	config.slave = 0;
	config.cs = *cs;

	enum { datacount = 5 };
 	uint8_t buff[datacount] = { 0x01, 0x02, 0x03, 0x04, 0x05};
	uint8_t rxdata[datacount];

	struct spi_buf tx_buf[1]= {
 		{.buf = buff, .len = 5},
	};
 	struct spi_buf rx_buf[1] = {
 		{.buf = rxdata, .len = 5},
	};

 	struct spi_buf_set tx_set = { .buffers = tx_buf, .count = 1 };
 	struct spi_buf_set rx_set = { .buffers = rx_buf, .count = 1 };

 	int ret = spi_transceive(dev, &config, &tx_set, &rx_set);

 	printk("8bit_loopback_partial; ret: %d\n", ret);
 	printk(" tx (i)  : %02x %02x %02x %02x %02x\n",
 	       buff[0], buff[1], buff[2], buff[3], buff[4]);
 	printk(" rx (i)  : %02x %02x %02x %02x %02x\n",
	       rxdata[0], rxdata[1], rxdata[2], rxdata[3], rxdata[4]);
}

void feed_watch_dog(void);

int main(void)
{
	const struct device *const dev = DEVICE_DT_GET(DT_NODELABEL(spim1));

	if (!device_is_ready(dev)) {
		printk("%s: device not ready.\n", dev->name);
		return 0;
	}
	 struct spi_cs_control ctrl =(struct spi_cs_control) {
         .gpio = SPI_CS_GPIOS_DT_SPEC_GET(DT_NODELABEL(spim1)),
         .delay = 2,
	 };

    hal_spi_master_config_t m_spi_config;

        m_spi_config.clock_frequency = 1000000;
        m_spi_config.bit_order =0 ;
        m_spi_config.polarity  = 0;
        m_spi_config.phase     = 0;
        m_spi_config.slave_port= 0;

	hal_spi_master_send_and_receive_config_t m_config;
	m_config.send_data = (uint8_t *)m_tx_bufe;
	m_config.send_length = 20;
	m_config.receive_length = 20;
	m_config.receive_buffer =(uint8_t*)m_rx_bufe;

	 printk("cc txbuf:%x",(unsigned int)m_tx_bufe);
	 printk("cc rxbuf:%x",(unsigned int) m_rx_bufe);

	m_status = hal_spi_master_init(1, &m_spi_config);


	hal_gpio_init(SPI_PIN_CLK);
	hal_gpio_init(SPI_PIN_MOSI);
	hal_gpio_init(SPI_PIN_MISO);
	hal_gpio_init(SPI_PIN_CSN);
	hal_pinmux_set_function(SPI_PIN_CLK,5);
	hal_pinmux_set_function(SPI_PIN_MOSI,5);
	hal_pinmux_set_function(SPI_PIN_MISO,5);
	hal_pinmux_set_function(SPI_PIN_CSN,5);


	hal_spi_slave_config_t spi_config;
	spi_config.bit_order=HAL_SPI_SLAVE_LSB_FIRST;
	spi_config.phase=HAL_SPI_SLAVE_CLOCK_PHASE0;
	spi_config.polarity=HAL_SPI_SLAVE_CLOCK_POLARITY0;
	spi_config.timeout_threshold=100;

	s_status = hal_spi_slave_init(spi_port,&spi_config);
	if(s_status!=0)
		printk("init err");

	hal_spi_slave_vfifo_config_t slave_config;
	slave_config.tx_buffer=tx_bufe;
	slave_config.rx_buffer=rx_bufe;
	slave_config.tx_buffer_size=20;
	slave_config.rx_buffer_size=20;
	slave_config.tx_threshold=0;
	slave_config.rx_threshold=0;
	s_status = hal_spi_slave_set_vfifo(spi_port,&slave_config);
	if(s_status!=0)
		printk("set_vfifo err");

	uint32_t size;

	for(;;) {

		//m_status =hal_spi_master_send_dma_blocking(1, m_tx_bufe,sizeof(m_tx_bufe));
		// if(m_status!=0)
		// printk(" receive errrrr:%d,",m_status);
		// size= hal_spi_slave_send_vfifo(spi_port,tx_bufe,sizeof(tx_bufe));
		// printk("send :%d",size);
		// printk("%x",m_rx_bufe[0]);
		// printk("%x",m_rx_bufe[1]);

		//test_spi_function(dev,&ctrl);
		//test_basic_write_9bit_words(dev, &ctrl);
		//m_status =hal_spi_master_send_and_receive_dma_blocking(1, &m_config);


		//########test_basic_write_9bit_words##############
		test_basic_write_9bit_words(dev, &ctrl);
		size= hal_spi_slave_receive_vfifo(spi_port,rx_bufe,sizeof(rx_bufe));
		printk("receive:%d",size);
		printk("%x",rx_bufe[0]);
		printk("%x",rx_bufe[1]);



		//########test_9bit_loopback_partial##############test_9bit_loopback_partial slave can send once and master receive once.master send many times
		// size= hal_spi_slave_send_vfifo(spi_port,tx_bufe,sizeof(tx_bufe));
		// printk("send :%d",size);
		// test_9bit_loopback_partial(dev, &ctrl);
		// size= hal_spi_slave_receive_vfifo(spi_port,rx_bufe,sizeof(rx_bufe));
		// printk("receive:%d",size);
		// printk("%x",rx_bufe[0]);
		// printk("%x",rx_bufe[1]);

		//########test_8bit_xfer############## test_8bit_xfer slave can send once and master receive once.master send many times.
		// size= hal_spi_slave_send_vfifo(spi_port,tx_bufe,sizeof(tx_bufe));
		// printk("send :%d",size);
	    // test_8bit_xfer(dev, &ctrl);
		// size= hal_spi_slave_receive_vfifo(spi_port,rx_bufe,sizeof(rx_bufe));
		// printk("receive:%d",size);
		// printk("%x",rx_bufe[0]);
		// printk("%x",rx_bufe[1]);

		// printk("cccccccccccccccccccc");
		// k_sleep(K_MSEC(1000));
		// printk("0x400B0058 = %x, 0x400B005C=%x", *((volatile uint32_t *)0x400B0058), *((volatile uint32_t *)0x400B005C));
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