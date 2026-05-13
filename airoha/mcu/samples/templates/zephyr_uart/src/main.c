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
#include <zephyr/drivers/uart.h>
#include <stdio.h>
#include <string.h>
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

struct uart_config uart_cfg = {
	.baudrate = 9600,
	.parity = UART_CFG_PARITY_NONE,
	.stop_bits = UART_CFG_STOP_BITS_1,
	.flow_ctrl = UART_CFG_FLOW_CTRL_NONE,
	.data_bits = UART_CFG_DATA_BITS_8,
};

static char tx_buf[256];
static char rx_buf[256];

const struct device *uart_dev = DEVICE_DT_GET(DT_NODELABEL(uart2));

void print_uart(char *buf)
{
	int msg_len = strlen(buf);

	for (int i = 0; i < msg_len; i++) {
		uart_poll_out(uart_dev, buf[i]);
	}
}

void recv_str(const struct device *uart, char *str)
{
	char *head = str;
	char c;

	while (!uart_poll_in(uart, &c)) {
		*head++ = c;
	}
	*head = '\0';
}

void serial_cb(const struct device *dev, void *user_data)
{

    uint32_t size;

    if (!uart_irq_update(uart_dev)) {
        return;
    }

    if (uart_irq_rx_ready(uart_dev))
    {
        printk("UART RX ready\r\n");
        size = uart_fifo_read(uart_dev, rx_buf, 256);
        printk("UART RX %d bytes\r\n", size);
		for (int i = 0; i < size; i++) {
			printk("%c", rx_buf[i]);
		}
        memcpy(tx_buf, rx_buf, size);
		memset(rx_buf, 0, 256);
        printk("init rx_buf");
        for (int i = 0; i < size; i++) {
            printk("%c", rx_buf[i]);
        }
    }

    if (uart_irq_tx_ready(uart_dev)) {
        int length = strlen(tx_buf);
        printk("UART TX byte size %d", length);
        if (length) {
            uart_fifo_fill(uart_dev, tx_buf, length);
            memset(tx_buf, 0, 256);
        }
    }
}

void zephyr_uart_api_test(void)
{
    printk("zephyr_uart_api_test\r\n");

    if (!device_is_ready(uart_dev)) {
        return;
    }
    /* configure interrupt and callback to receive data */
    int ret = uart_irq_callback_user_data_set(uart_dev, serial_cb, NULL);

    if (ret < 0) {
        if (ret == -ENOTSUP) {
            printk("Interrupt-driven UART API support not enabled\n");
        } else if (ret == -ENOSYS) {
            printk("UART device does not support interrupt-driven API\n");
        } else {
            printk("Error setting UART callback: %d\n", ret);
        }
        return;
    }
    uart_irq_rx_enable(uart_dev);
    uart_irq_tx_enable(uart_dev);
}

void feed_watch_dog(void);

int main(void)
{
    printk("single thread environment with board %s\n", CONFIG_BOARD);
	int rc = uart_configure(uart_dev, &uart_cfg);
	if (rc) {
		printk("Could not configure device %s", uart_dev->name);
	}
	zephyr_uart_api_test();

    for(;;){
        /*the poll mode of uart is used here*/
        // recv_str(uart_dev, rx_buf);
        // int size = strlen(rx_buf);
        // if (size) {
        //     memcpy(tx_buf, rx_buf, size);
        // }

        // int length = strlen(tx_buf);
		// // uart_poll_out(uart_dev, 0x5a);
        // printk("Transmitting  bytes\n");

        // if (length) {
        //     printk("Transmitting %d bytes\n", length);
        //     for (int i = 0; i < length; i++) {
        //         printk("%c", tx_buf[i]);
        //     }
        //     print_uart(tx_buf);
        //     memset(tx_buf, 0, length);
        // }
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