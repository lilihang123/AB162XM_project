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

#define DT_DRV_COMPAT airoha_air_trng

#include <errno.h>
#include <stddef.h>
#include <sys/types.h>

#ifdef FPGA_ENV
#include <stdlib.h>
#endif

#include <zephyr/irq.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/types.h>
#include <zephyr/device.h>
#include <zephyr/sys_clock.h>
#include <zephyr/spinlock.h>
#include <zephyr/sys/__assert.h>

#include "air_chip.h"

#if KERNELVERSION == 0x3030000
#include <zephyr/random/rand32.h>
#elif KERNELVERSION >= 0x3070000
#include <zephyr/random/random.h>
#else
#error "Unkown supported kernel version"
#endif

#include "hal_trng.h"
#include "hal_trng_internal.h"
#include "hal_hw_semaphore.h"
#include "hal_uart.h"
#include "hal_gpio.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_internal.h"

#include "hal_cross_core_config.h"
#include "memory_attribute.h"
#include <zephyr/drivers/entropy.h>

#ifdef HAL_SLEEP_MANAGER_ENABLED
#include "hal_sleep_manager_platform.h"
#endif

#define AIR_TRNG_DT_NODE                        DT_NODELABEL(trng)

#define AIR_TRNG_VON_NEUMANN_EXTRACTOR          DT_PROP(AIR_TRNG_DT_NODE, von_neumann_extractor)
#define AIR_TRNG_RING_OSCILLATOR_COMBINATION    DT_PROP(AIR_TRNG_DT_NODE, ring_oscillator_combination)

struct entropy_air_trng_data {
#ifdef CONFIG_MULTITHREADING
	struct k_sem lock;
#endif
    uint32_t timeout;
    bool von_neumann_extractor;
    uint32_t ring_oscillator_combination;
};

uint32_t z_impl_sys_rand32_get(void)
{
    int status = -EIO;
    uint32_t value = 0xDEADBEEF;
    status = z_impl_sys_csrand_get(&value, sizeof(value));
    printk("z_impl_sys_rand32_get was called and return %d and result 0x%08X\r\n", status, (unsigned int)value);
    return value;
}

void z_impl_sys_rand_get(void *dst, size_t len)
{
    z_impl_sys_csrand_get(dst, len);
}

/* The Zephyr has Random Number Generation module, but OpenThread requires entropy functions. */
#if IS_ENABLED(CONFIG_AIR_ENTROPY_ENABLE)
static int s_trng_get_random_number_buffer_blocking(void *dst, size_t len)
#else
int z_impl_sys_csrand_get(void *dst, size_t len)
#endif
{
    volatile uint32_t generate_data;

    if(dst == NULL){
        printk("invalid parameter 0x%08X %d", (unsigned int)dst, len);
        return -EINVAL;
    }

    while (0 < len) {
#if IS_ENABLED(CONFIG_AIR_ENTROPY_ENABLE)
        generate_data = trng_get_random_data();
#else
        generate_data = rand();
#endif
        if (generate_data == 0) {
            return  -EIO;
        } else {
            if (4 <= len) {
                *(uint32_t*)dst = generate_data;
                dst = (void*)((uint8_t*)dst + 4);
                len -= 4;
            }
            else {
                while (0 < len) {
                    *(uint8_t*)dst = (generate_data & 0xff);
                    dst = (void*)((uint8_t*)dst + 1);
                    generate_data = generate_data >> 8;
                    len--;
                }
            }
        }
    }

    return 0;
}


#if IS_ENABLED(CONFIG_AIR_ENTROPY_ENABLE)
#if 0
#define HQA_STACK_SIZE          2048
struct k_work hqa_work;
struct k_timer hqa_timer;
K_THREAD_STACK_DEFINE(hqa_thread_stack1, HQA_STACK_SIZE);
struct k_thread hqa_thread_data1;

struct entropy_test_data {
    uint32_t timeout;
    bool von_neumann_extractor;
    uint32_t ring_oscillator_combination;
};
struct entropy_test_data pattern[] = {
                                      {0xfff, false, 0x00},         //0
                                      {0xfff, true, 0x00},          //1
                                      {0xfff, false, 0x01},         //2
                                      {0xfff, false, 0x02},         //3
                                      {0xfff, false, 0x3a},         //4
                                      {0xfff, false, 0x03},         //5
                                      {0xfff, false, 0x3b},         //6
                                      {0xfff, false, 0x3c},         //7
                                      {0xfff, false, 0x7f},         //8
                                      {0xfff, true, 0x01},      //9
                                      {0xfff, true, 0x02},      //10
                                      {0xfff, true, 0x3a},      //11
                                      {0xfff, true, 0x03},      //12
                                      {0xfff, true, 0x3b},      //13
                                      {0xfff, true, 0x3c},      //14
                                      {0xfff, true, 0x7f}};     //15
void uart_init(void)
{
    hal_pinmux_set_function(17, 6);
    hal_gpio_set_direction(17, HAL_GPIO_DIRECTION_OUTPUT);
    hal_gpio_disable_pull(17);

    hal_pinmux_set_function(18, 6);
    hal_gpio_set_direction(18, HAL_GPIO_DIRECTION_INPUT);
    hal_gpio_disable_pull(18);

    hal_uart_config_t uart_config;
	uart_config.baudrate    = HAL_UART_BAUDRATE_115200;  //HAL_UART_BAUDRATE_921600
	uart_config.parity      = HAL_UART_PARITY_NONE;
	uart_config.stop_bit    = HAL_UART_STOP_BIT_1;
	uart_config.word_length = HAL_UART_WORD_LENGTH_8;
	hal_uart_init(HAL_UART_1, &uart_config);

}

void free_run_task(void* p1, void* p2, void* p3)
{
    #if 1
    const struct device *const entropy = DEVICE_DT_GET_OR_NULL(DT_CHOSEN(zephyr_entropy));
    //uart_init();
    printk("[TRNG] free_run_task start");
    if (entropy)
    {
        struct entropy_air_trng_data *data = NULL;
        uint8_t trng_data[256] = {0};
        uint8_t i;
        data = entropy->data;

        for(;;){
            data->timeout = pattern[15].timeout;
            data->von_neumann_extractor = pattern[15].von_neumann_extractor;
            data->ring_oscillator_combination = pattern[15].ring_oscillator_combination;
            entropy_get_entropy(entropy, trng_data, 256);
            for (i = 0; i < 256; i++)
                printk("[TRNG] Entropy data[%d]: %02x", i, trng_data[i]);

        }
    }
    else
    {
        printk("[TRNG] free_run_task hold");
        __asm__("b .");
    }
    
    #endif
}

void entropy_task(void* p1, void* p2, void* p3)
{
    #if 1
    const struct device *const entropy = DEVICE_DT_GET_OR_NULL(DT_CHOSEN(zephyr_entropy));
    //uart_init();
    printk("[TRNG] random_task start");
    if (entropy)
    {
        struct entropy_air_trng_data *data = NULL;
        uint32_t trng_data = 0;
        int8_t ret = 0;
        //int16_t start_cmd = 0xff5a;
        uint8_t i = 0;
        uint8_t pat_size = sizeof(pattern) / sizeof(struct entropy_test_data);
        data = entropy->data;

        for(;;){
            data->timeout = pattern[i].timeout;
            data->von_neumann_extractor = pattern[i].von_neumann_extractor;
            data->ring_oscillator_combination = pattern[i].ring_oscillator_combination;
            ret = entropy_get_entropy(entropy, (uint8_t*)&trng_data, sizeof(trng_data));
            printk("[TRNG] Entropy data[%d]: %08x ret = %d", i, trng_data, ret);
            i++;
            i = i % pat_size;
        }
    }
    else
    {
        printk("[TRNG] random_task hold");
        __asm__("b .");
    }
    
    #endif
}

void hqa_kwork_handler(struct k_work *work)
{
    UNUSED_PARAMETER(work);
#if 0
    k_tid_t hqa_thread_id1 = k_thread_create(&hqa_thread_data1, hqa_thread_stack1, HQA_STACK_SIZE,
        entropy_task, NULL, NULL, NULL, 0, 0, K_NO_WAIT);
    k_thread_start(hqa_thread_id1);
    printk("[TRNG] entropy_task create.");
#else
    k_tid_t hqa_thread_id1 = k_thread_create(&hqa_thread_data1, hqa_thread_stack1, HQA_STACK_SIZE,
        free_run_task, NULL, NULL, NULL, 0, 0, K_NO_WAIT);
    k_thread_start(hqa_thread_id1);
    printk("[TRNG] entropy_task create.");
#endif
}

void hqa_timer_expiry_fn(struct k_timer *timer)
{
    UNUSED_PARAMETER(timer);
    k_work_submit(&hqa_work); /* Submit to system work queue */
}
#endif
static int entropy_airoha_init(const struct device *dev)
{
    ARG_UNUSED(dev);
#if 0
    k_work_init(&hqa_work, hqa_kwork_handler);
    k_timer_init(&hqa_timer, hqa_timer_expiry_fn, NULL);
    k_timer_start(&hqa_timer, K_MSEC(3000), Z_TIMEOUT_NO_WAIT);
#endif
    printk("[TRNG] entropy_airoha_init .\r\n");
    return 0;
}

static int entropy_airoha_get_entropy(const struct device *dev, uint8_t *buf, uint16_t len)
{
    int ret;
    struct entropy_air_trng_data *data = dev->data;
    //printk("[TRNG] entropy_airoha_get_entropy .");

#ifdef HAL_HW_SEMAPHORE_MODULE_ENABLED
    if (HAL_HW_SEMAPHORE_STATUS_OK != hal_hw_semaphore_take(HW_SEMAPHORE_TRNG)) {
        printk("[TRNG] Using by other core.");
        return -EIO;
    }
#endif

#ifdef CONFIG_MULTITHREADING
    k_sem_take(&data->lock, K_FOREVER);
#endif

    trng_init();
#ifdef HAL_SLEEP_MANAGER_ENABLED
    hal_sleep_manager_lock_sleep(SLEEP_LOCK_TRNG);
#endif
    trng_config_timeout_limit(data->timeout);
    von_neumann_extractor(data->von_neumann_extractor);
    trng_enable_mode_combination(data->ring_oscillator_combination);

    if (len < 5)
        trng_start();
    else
        trng_start_freerun();

    ret = s_trng_get_random_number_buffer_blocking((void*)buf, (size_t)len);

    if (len < 5)
        trng_stop();
    else
        trng_stop_freerun();

#ifdef HAL_SLEEP_MANAGER_ENABLED
    hal_sleep_manager_unlock_sleep(SLEEP_LOCK_TRNG);
#endif
    trng_deinit();

#ifdef CONFIG_MULTITHREADING
    k_sem_give(&data->lock);
#endif

#ifdef HAL_HW_SEMAPHORE_MODULE_ENABLED
    if (HAL_HW_SEMAPHORE_STATUS_OK != hal_hw_semaphore_give(HW_SEMAPHORE_TRNG)) {
        printk("[TRNG] do not give HW semaphore .");
    }
#endif

    return ret;
}

static struct entropy_air_trng_data air_trng_data = {
#ifdef CONFIG_MULTITHREADING
	.lock = Z_SEM_INITIALIZER(air_trng_data.lock, 1, 1),
#endif
    .timeout = 0xFFF,
    .von_neumann_extractor = AIR_TRNG_VON_NEUMANN_EXTRACTOR,
    .ring_oscillator_combination = AIR_TRNG_RING_OSCILLATOR_COMBINATION,
};
static const struct entropy_driver_api entropy_airoha_api_funcs = {
    .get_entropy = entropy_airoha_get_entropy,
    /* not support get_entropy_isr because there is not data ready callback */
};

DEVICE_DT_INST_DEFINE(0,
    entropy_airoha_init, NULL, &air_trng_data, NULL,
    CONFIG_TRNG_INIT_LEVEL, CONFIG_TRNG_INIT_PRIORITY,
    &entropy_airoha_api_funcs);
#endif