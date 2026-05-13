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

#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <zephyr/drivers/sensor.h>
#include <zephyr/pm/device.h>
#include <zephyr/drivers/pinctrl.h>
#include <soc.h>

#include <hal_ramboz.h>

#include <zephyr/logging/log.h>
#include <zephyr/irq.h>

#define DT_DRV_COMPAT airoha_air_ramboz

struct ramboz_airoha_pin
{
    uint8_t pin_led;
    uint8_t pinb_mcu_ctrl;
};

struct ramboz_airoha_cfg
{
    hal_ramboz_config_t ramboz_conifg;
    struct ramboz_airoha_pin ramboz_pin;
};

struct ramboz_airoha_data
{
    sensor_trigger_handler_t irq_cb;
    void *irq_cb_data;
};

static int ramboz_airoha_sample_fetch(const struct device *dev,
                                      enum sensor_channel chan)
{
    switch (chan)
    {
    case SENSOR_CHAN_ALL:
    case SENSOR_CHAN_ROTATION:
    case SENSOR_CHAN_POS_DZ:
        hal_ramboz_set_latch_clear();
        break;

    default:
        return -ENOTSUP;
    }

    return 0;
}

static int ramboz_airoha_channel_get(const struct device *dev,
                                     enum sensor_channel chan,
                                     struct sensor_value *val)
{
    int16_t ramboz_data = 0;
    hal_ramboz_get_data(&ramboz_data);
    switch (chan)
    {
    case SENSOR_CHAN_POS_DZ:
    case SENSOR_CHAN_ROTATION:
        val->val1 = (int32_t)ramboz_data;
        val->val2 = 0;
        break;

    default:
        return -ENOTSUP;
    }
    return 0;
}

static sensor_trigger_handler_t g_ramboz_handler = NULL;
static void ramboz_callback_handler(uint8_t irq_type)
{
    const struct device *ramboz_dev= device_get_binding(DT_NODE_FULL_NAME(DT_NODELABEL(ramboz)));
    if (g_ramboz_handler != NULL)
    {
        if (irq_type == HAL_RAMBOZ_IRQ_Z_CNT)
        {
            hal_ramboz_disable_irq(HAL_RAMBOZ_IRQ_Z_CNT);
            struct sensor_trigger trigger = {
                .type = SENSOR_TRIG_MOTION,
                .chan = SENSOR_CHAN_POS_DZ};
            g_ramboz_handler(ramboz_dev, &trigger);
        }
        else if (irq_type == HAL_RAMBOZ_IRQ_RAMBO_CNT)
        {
            hal_ramboz_disable_irq(HAL_RAMBOZ_IRQ_RAMBO_CNT);
            struct sensor_trigger trigger = {
                .type = SENSOR_TRIG_MOTION,
                .chan = SENSOR_CHAN_POS_DZ};
            g_ramboz_handler(ramboz_dev, &trigger);
        }
        else if (irq_type == HAL_RAMBOZ_IRQ_DATA_READY)
        {
            struct sensor_trigger trigger = {
                .type = SENSOR_TRIG_DATA_READY,
                .chan = SENSOR_CHAN_POS_DZ};
            g_ramboz_handler(ramboz_dev, &trigger);
        }
    }
}

static int ramboz_airoha_trigger_set(const struct device *dev,
                                     const struct sensor_trigger *trig,
                                     sensor_trigger_handler_t handler)
{
    if (handler == NULL)
    {
        return -ENOTSUP;
    }

    /*set callback function*/
    g_ramboz_handler = handler;

    hal_ramboz_register_callback(ramboz_callback_handler);
    if (trig->type == SENSOR_TRIG_DATA_READY)
    {
        hal_ramboz_enable_irq(HAL_RAMBOZ_IRQ_DATA_READY);
    }
    if (trig->type == SENSOR_TRIG_MOTION)
    {
        hal_ramboz_enable_irq(HAL_RAMBOZ_IRQ_Z_CNT);
    }

    return 0;
}

// static void ramboz_airoha_gpio_ctrl(bool enable)
// {
//     /*pinmux*/
//     return;
// }

static int ramboz_airoha_init(const struct device *dev)
{
    // ramboz_airoha_gpio_ctrl(0);

    hal_ramboz_config_t ramboz_test_config = (((struct ramboz_airoha_cfg *)(dev->config))->ramboz_conifg);
    hal_ramboz_init(&ramboz_test_config);
    hal_ramboz_enable();
    return 0;
}

static const struct sensor_driver_api ramboz_airoha_driver_api = {
    .sample_fetch = ramboz_airoha_sample_fetch,
    .channel_get = ramboz_airoha_channel_get,
    .trigger_set = ramboz_airoha_trigger_set,
};

#define RAMBOZ_AIROHA_DEVICE(id)                                                  \
                                                                                  \
    static struct ramboz_airoha_cfg ramboz_airoha_p##id##_cfg = {                 \
        .ramboz_conifg = {                                                        \
            .direction = (uint8_t)DT_INST_PROP(id, direction),                    \
            .mode = (uint8_t)DT_INST_PROP(id, mode),                              \
            .filter_period = (uint16_t)DT_INST_PROP(id, filter_period),           \
            .fast_sample_period = (uint16_t)DT_INST_PROP(id, fast_sample_period), \
            .slow_sample_period = (uint8_t)DT_INST_PROP(id, slow_sample_period),  \
            .fast_roll_period = (uint8_t)DT_INST_PROP(id, fast_roll_period),      \
        },                                                                        \
        .ramboz_pin = {                                                           \
            .pin_led = (uint8_t)DT_INST_PROP(id, pin_led),                        \
            .pinb_mcu_ctrl = (uint8_t)DT_INST_PROP(id, pin_mcu_ctrl),             \
        },                                                                        \
    };                                                                            \
                                                                                  \
    static struct ramboz_airoha_data ramboz_airoha_p##id##_data = {               \
        .irq_cb = NULL,                                                           \
        .irq_cb_data = NULL,                                                      \
    };                                                                            \
                                                                                  \
    DEVICE_DT_INST_DEFINE(id,                                                     \
                          ramboz_airoha_init,                                     \
                          NULL,                                                   \
                          &ramboz_airoha_p##id##_data,                            \
                          &ramboz_airoha_p##id##_cfg,                             \
                          PRE_KERNEL_2,                                           \
                          91,                                                     \
                          &ramboz_airoha_driver_api);

DT_INST_FOREACH_STATUS_OKAY(RAMBOZ_AIROHA_DEVICE);
