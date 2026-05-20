/* Copyright Statement:
 *
 * (C) 2024  Airoha Technology Corp. All rights reserved.
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
/*
 * SPDX-License-Identifier: Apache-2.0
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

#include <hal_qdec.h>
#include <qdec_airoha.h>
#include <zephyr/logging/log.h>
#include <zephyr/irq.h>

#define DT_DRV_COMPAT airoha_air_qdec

struct qdec_airoha_pin
{
    uint8_t pina;
    uint8_t pinb;
};

struct qdec_airoha_cfg
{
    hal_qdec_config_t qdec_conifg;
    struct qdec_airoha_pin qdec_pin;
#if IS_ENABLED(CONFIG_AIR_PINCTRL)
    const struct pinctrl_dev_config *pincfg;
#endif
};

struct qdec_airoha_data
{
    sensor_trigger_handler_t irq_cb;
    void *irq_cb_data;
};

static int qdec_airoha_sample_fetch(const struct device *dev,
                                    enum sensor_channel chan)
{
    switch (chan)
    {
    case SENSOR_CHAN_ALL:
    case SENSOR_CHAN_ROTATION:
    case SENSOR_CHAN_POS_DZ:
        hal_qdec_set_latch_clear();
        break;

    default:
        return -ENOTSUP;
    }

    return 0;
}

static int qdec_airoha_channel_get(const struct device *dev,
                                   enum sensor_channel chan,
                                   struct sensor_value *val)
{
    int16_t qdec_data = 0;
    hal_qdec_get_data(&qdec_data);
    switch (chan)
    {
    case SENSOR_CHAN_POS_DZ:
    case SENSOR_CHAN_ROTATION:
        val->val1 = (int32_t)qdec_data;
        break;

    default:
        return -ENOTSUP;
    }
    return 0;
}

static sensor_trigger_handler_t g_qdec_handler = NULL;
static void qdec_callback_handler(uint8_t irq_type)
{
    const struct device *qdec_dev= device_get_binding(DT_NODE_FULL_NAME(DT_NODELABEL(qdec)));
    if (g_qdec_handler != NULL)
    {
        if (irq_type == QDEC_IRQ_Z_CNT)
        {
            hal_qdec_disable_irq(QDEC_IRQ_Z_CNT);
            struct sensor_trigger trigger = {
                .type = SENSOR_TRIG_MOTION,
                .chan = SENSOR_CHAN_POS_DZ};
            g_qdec_handler(qdec_dev, &trigger);
        }
        else if (irq_type == QDEC_IRQ_Z_SUM)
        {
            hal_qdec_disable_irq(QDEC_IRQ_Z_SUM);
            struct sensor_trigger trigger = {
                .type = SENSOR_TRIG_MOTION,
                .chan = SENSOR_CHAN_POS_DZ};
            g_qdec_handler(qdec_dev, &trigger);
        }
        else if (irq_type == QDEC_IRQ_DATA_READY)
        {
            struct sensor_trigger trigger = {
                .type = SENSOR_TRIG_DATA_READY,
                .chan = SENSOR_CHAN_POS_DZ};
            g_qdec_handler(qdec_dev, &trigger);
        }
    }
}

static int qdec_airoha_trigger_set(const struct device *dev,
                                     const struct sensor_trigger *trig,
                                     sensor_trigger_handler_t handler)
{
    if (handler == NULL)
    {
        return -ENOTSUP;
    }
    /*set callback function*/
    g_qdec_handler = handler;

    hal_qdec_register_callback(qdec_callback_handler);
    if (trig->type == SENSOR_TRIG_DATA_READY)
    {
        hal_qdec_enable_irq(QDEC_IRQ_DATA_READY);
    }
    if (trig->type == SENSOR_TRIG_MOTION)
    {
        hal_qdec_enable_irq(QDEC_IRQ_Z_SUM);
    }

    return 0;
}

static int qdec_airoha_set_mode_status(const struct device *dev,int32_t val)
{   
    hal_qdec_status_t ret;
    if((val != HAL_QDEC_LED_ACTIVE_MDOE)&&(val != HAL_QDEC_LED_IDLE_MDOE))
    {
        return -ENOTSUP;
    }
    if(val == HAL_QDEC_LED_ACTIVE_MDOE)
    {   
        ret = hal_qdec_select_to_active_status();
        if(ret != HAL_QDEC_STATUS_OK)
        {
            return -ENOTSUP;
        }
    }else if(val == HAL_QDEC_LED_IDLE_MDOE)
    {
        ret = hal_qdec_select_to_idle_status();
        if(ret != HAL_QDEC_STATUS_OK)
        {
            return -ENOTSUP;
        }
    }
    return 0;
}

static int qdec_airoha_a_group_setting(const struct device *dev,const struct sensor_value *val)
{   
    hal_qdec_status_t ret;
    uint16_t smp_period = (uint16_t)((val->val1)&0xff);
    uint8_t led_period = (uint8_t)((val->val2)>>8)&0xff;
    uint8_t dbc_count = (uint8_t)((val->val2)&0xff);
    hal_qdec_group_config_t group_config = {
        .smp_period = smp_period,
        .led_period = led_period,
        .dbc_count = dbc_count
    };
    ret = hal_qdec_runnig_config_group_para(HAL_QDEC_SELECT_GROUP_A,group_config);
    if (ret != HAL_QDEC_STATUS_OK)
    {
        return -ENOTSUP;
    }
    return 0;
}

static int qdec_airoha_b_group_setting(const struct device *dev,const struct sensor_value *val)
{   
    hal_qdec_status_t ret;
    uint16_t smp_period = (uint16_t)((val->val1)&0xff);
    uint8_t led_period = (uint8_t)((val->val2)>>8)&0xff;
    uint8_t dbc_count = (uint8_t)((val->val2)&0xff);
    hal_qdec_group_config_t group_config = {
        .smp_period = smp_period,
        .led_period = led_period,
        .dbc_count = dbc_count
    };
    ret = hal_qdec_runnig_config_group_para(HAL_QDEC_SELECT_GROUP_B,group_config);
    if (ret != HAL_QDEC_STATUS_OK)
    {
        return -ENOTSUP;
    }
    return 0;
}

static int qdec_airoha_irq_setting(const struct device *dev, hal_qdec_irq_type_t irq_type, int32_t val)
{   
    hal_qdec_status_t ret;
    if((val != IRQ_ENABLE)&&(val != IRQ_DISABLE))
    {
        return -ENOTSUP;
    }
    if(val == IRQ_ENABLE)
    {
        if(irq_type == QDEC_IRQ_DATA_READY)
        {
            ret = hal_qdec_enable_irq(QDEC_IRQ_DATA_READY);
            if (ret != HAL_QDEC_STATUS_OK)
            {
                return -ENOTSUP;
            }
        }else if(irq_type == QDEC_IRQ_Z_SUM)
        {
            ret = hal_qdec_enable_irq(QDEC_IRQ_Z_SUM);
            if (ret != HAL_QDEC_STATUS_OK)
            {
                return -ENOTSUP;
            }
        }else
        {
            return -ENOTSUP;
        }
    }else
    {
        if(irq_type == QDEC_IRQ_DATA_READY)
        {
            ret = hal_qdec_disable_irq(QDEC_IRQ_DATA_READY);
            if (ret != HAL_QDEC_STATUS_OK)
            {
                return -ENOTSUP;
            }
        }else if(irq_type == QDEC_IRQ_Z_SUM)
        {
            ret = hal_qdec_disable_irq(QDEC_IRQ_Z_SUM);
            if (ret != HAL_QDEC_STATUS_OK)
            {
                return -ENOTSUP;
            }
        }else
        {
            return -ENOTSUP;
        } 
    }
    return 0;
}
static int qdec_airoha_z_sum_irq_cfg(const struct device *dev, const struct sensor_value *val)
{
    hal_qdec_status_t ret;
    if(((val->val1) != IRQ_ENABLE)&&((val->val1) != IRQ_DISABLE))
    {
        return -ENOTSUP;
    }
    if((val->val1) == IRQ_ENABLE)
    {   
        uint16_t z_sum_threshold = (val->val2);
        ret = hal_qdec_set_z_sum_threshold(z_sum_threshold);
        if (ret != HAL_QDEC_STATUS_OK)
        { 
            return -ENOTSUP;
        }
        ret = hal_qdec_enable_irq(QDEC_IRQ_Z_SUM);
        if (ret != HAL_QDEC_STATUS_OK)
        {
            return -ENOTSUP;
        }
    }else
    {
        ret = hal_qdec_disable_irq(QDEC_IRQ_Z_SUM);
        if (ret != HAL_QDEC_STATUS_OK)
        {
            return -ENOTSUP;
        }
    }
    return 0;
}

static int qdec_airoha_hw_sel_cfg(const struct device *dev, const struct sensor_value *val)
{
    if(((val->val1) != IRQ_ENABLE)&&((val->val1) != IRQ_DISABLE))
    {
        return -ENOTSUP;
    }
    if(((val->val2) != HAL_QDEC_SELECT_GROUP_A)&&((val->val2) != HAL_QDEC_SELECT_GROUP_B))
    {
        return -ENOTSUP;
    }

    if((val->val1) == IRQ_ENABLE)
    {   
        if((val->val2) == HAL_QDEC_SELECT_GROUP_A)
        {
            hal_qdec_enable_hw_sel(HAL_QDEC_SELECT_GROUP_A);
        }else{
            hal_qdec_enable_hw_sel(HAL_QDEC_SELECT_GROUP_B);
        }
    }else
    {
        hal_qdec_disable_hw_sel();
    }
    return 0;
}

static int qdec_airoha_attr_set(const struct device *dev,enum sensor_channel chan,
                            enum sensor_attribute attr,
                            const struct sensor_value *val){
    int ret;
    switch((uint32_t)attr){
        case QDEC_MODE_STATUS:
            ret = qdec_airoha_set_mode_status(dev,val->val1);
        break;
        case QDEC_A_GROUP_CFG:
            ret = qdec_airoha_a_group_setting(dev,val);
        break;
        case QDEC_B_GROUP_CFG:
            ret = qdec_airoha_b_group_setting(dev,val);
        break;
        case QDEC_DATA_READY_IRQ:
            ret = qdec_airoha_irq_setting(dev, QDEC_IRQ_DATA_READY, val->val1);
        break;
        case QDEC_Z_SUM_IRQ_CFG:
            ret = qdec_airoha_z_sum_irq_cfg(dev, val);
        break;
        case QDEC_HW_SEL_CFG:
            ret = qdec_airoha_hw_sel_cfg(dev,val);
        break;
        default:
        return -ENOTSUP;
    }
    return ret;
}

static int qdec_airoha_get_mode_status(const struct device *dev,struct sensor_value *val)
{   
    hal_qdec_mode_status_t ret;
    ret= hal_qdec_get_mode_status();
    (val->val1) = (int32_t)(ret);
    return 0;
}

static int qdec_airoha_get_a_group_setting(const struct device *dev,struct sensor_value *val)
{   
    hal_qdec_status_t ret;
    hal_qdec_group_config_t group_config;
    ret = hal_qdec_get_config_group_para(HAL_QDEC_SELECT_GROUP_A,&group_config);
    if (ret != HAL_QDEC_STATUS_OK)
    {
        return -ENOTSUP;
    }
    (val->val1) =(int32_t)(group_config.smp_period);
    (val->val2) =(int32_t)((group_config.led_period<<8)+(group_config.dbc_count));
    return 0;
}

static int qdec_airoha_get_b_group_setting(const struct device *dev,struct sensor_value *val)
{   
    hal_qdec_status_t ret;
    hal_qdec_group_config_t group_config;
    ret = hal_qdec_get_config_group_para(HAL_QDEC_SELECT_GROUP_B,&group_config);
    if (ret != HAL_QDEC_STATUS_OK)
    {
        return -ENOTSUP;
    }
    (val->val1) =(int32_t)(group_config.smp_period);
    (val->val2) =(int32_t)((group_config.led_period<<8)+(group_config.dbc_count));
    return 0;
}

static int qdec_airoha_get_irq_setting(const struct device *dev, hal_qdec_irq_type_t irq_type, struct sensor_value *val)
{
    hal_qdec_status_t ret;
    hal_qdec_irq_status_t irq_status;
    if(irq_type == QDEC_IRQ_DATA_READY)
    {
        ret = hal_qdec_get_irq_status(QDEC_IRQ_DATA_READY, &irq_status);
        if (ret != HAL_QDEC_STATUS_OK)
        {
            return -ENOTSUP;
        }
        (val->val1) = (int32_t)(irq_status);
    }else if(irq_type == QDEC_IRQ_Z_SUM){
        ret = hal_qdec_get_irq_status(QDEC_IRQ_DATA_READY, &irq_status);
        if (ret != HAL_QDEC_STATUS_OK)
        {
            return -ENOTSUP;
        }
        (val->val1) = (int32_t)(irq_status);
    }else{
        return -ENOTSUP;
    }
    return 0;
}

static int qdec_airoha_get_z_sum_irq_cfg(const struct device *dev, struct sensor_value *val)
{
    hal_qdec_status_t ret;
    hal_qdec_irq_status_t z_sum_irq_status;
    ret = hal_qdec_get_irq_status(QDEC_IRQ_Z_SUM, &z_sum_irq_status);
    if (ret != HAL_QDEC_STATUS_OK)
    {
        return -ENOTSUP;
    }
    val->val1 = (int32_t)z_sum_irq_status;
    uint16_t z_sum_thr;
    ret = hal_qdec_get_z_sum_threshold(&z_sum_thr);
    if (ret != HAL_QDEC_STATUS_OK)
    {
        return -ENOTSUP;
    }
    val->val2 = (int32_t)z_sum_thr;
    return 0;
}

static int qdec_airoha_get_hw_sel_cfg(const struct device *dev, struct sensor_value *val)
{    
    hal_qdec_status_t ret;
    hal_qdec_irq_status_t hw_sel_irq_status;
    hal_qdec_sel_group_setting_t group;
    ret = hal_qdec_get_hw_sel_cfg(&hw_sel_irq_status,&group);
    if (ret != HAL_QDEC_STATUS_OK)
    {
        return -ENOTSUP;
    }
    val->val1 = (int32_t)hw_sel_irq_status;
    val->val2 = (int32_t)group;
    return 0;
}

static int qdec_airoha_get_hw_latch_status(const struct device *dev, struct sensor_value *val)
{
    bool hw_latch_busy;
    hal_qdec_status_t ret;
    ret = hal_qdec_latch_status_is_busy(&hw_latch_busy);
    if (ret != HAL_QDEC_STATUS_OK)
    {
        return -ENOTSUP;
    }

    if(hw_latch_busy)
    {
        val->val1 = (int32_t)(0x0);
    }else
    {
        val->val1 = (int32_t)(0x1);
    }
    return 0;
}

static int qdec_airoha_attr_get(const struct device *dev,enum sensor_channel chan,
                            enum sensor_attribute attr,
                            struct sensor_value *val){
    int ret = 0;
    switch((uint32_t)attr){
        case QDEC_MODE_STATUS:
            ret = qdec_airoha_get_mode_status(dev,val);
        break;
        case QDEC_A_GROUP_CFG:
            ret = qdec_airoha_get_a_group_setting(dev,val);
        break;
        case QDEC_B_GROUP_CFG:
            ret = qdec_airoha_get_b_group_setting(dev,val);
        break;
        case QDEC_DATA_READY_IRQ:
            ret = qdec_airoha_get_irq_setting(dev, QDEC_IRQ_DATA_READY, val);
        break;
        case QDEC_Z_SUM_IRQ_CFG:
            ret = qdec_airoha_get_z_sum_irq_cfg(dev, val);
        break;
        case QDEC_HW_SEL_CFG:
            ret = qdec_airoha_get_hw_sel_cfg(dev,val);
        break;
        case QDEC_HW_LATCH_STATUS:
            ret = qdec_airoha_get_hw_latch_status(dev,val);
        break;
        default:
        return -ENOTSUP;
    }
    return ret;
}


// static void qdec_airoha_gpio_ctrl(bool enable)
// {
//     /*pinmux*/
//     return;
// }

static int qdec_airoha_init(const struct device *dev)
{
    // qdec_airoha_gpio_ctrl(0);

#if IS_ENABLED(CONFIG_AIR_PINCTRL)
    const struct qdec_airoha_cfg *cfg = dev->config;
    if (cfg->pincfg) {
        int ret = pinctrl_apply_state(cfg->pincfg, PINCTRL_STATE_DEFAULT);
        if (ret < 0) {
            return ret;
        }
    }
#endif

    hal_qdec_config_t qdec_test_config = (((struct qdec_airoha_cfg *)(dev->config))->qdec_conifg);
    hal_qdec_deinit();
    hal_qdec_init(&qdec_test_config);
    hal_qdec_enable();
    return 0;
}

static const struct sensor_driver_api qdec_airoha_driver_api = {
    .attr_set = qdec_airoha_attr_set,
    .attr_get = qdec_airoha_attr_get,
    .sample_fetch = qdec_airoha_sample_fetch,
    .channel_get = qdec_airoha_channel_get,
    .trigger_set = qdec_airoha_trigger_set, 
};

#define QDEC_AIROHA_DEVICE(id)         \
                                    \
    PINCTRL_DT_INST_DEFINE(id);                             \
    static struct qdec_airoha_cfg qdec_airoha_p##id##_cfg = {                   \
        .qdec_conifg = {                                                        \
            .led_force_off = (uint8_t)DT_INST_PROP(id, led_force_off),          \
            .led_active_output = (uint8_t)DT_INST_PROP(id, led_active_output),  \
            .z_sum_thr = (uint16_t)DT_INST_PROP(id, z_sum_thr),                 \
            .group_a_cfg = {                                                    \
                .smp_period = (uint16_t)DT_INST_PROP(id, smp_period_a),         \
                .led_period = (uint8_t)DT_INST_PROP(id, led_period_a),          \
                .dbc_count = (uint8_t)DT_INST_PROP(id, dbc_count_a),            \
            },                                                                  \
            .group_b_cfg = {                                                    \
                .smp_period = (uint16_t)DT_INST_PROP(id, smp_period_b),         \
                .led_period = (uint8_t)DT_INST_PROP(id, led_period_b),          \
                .dbc_count = (uint8_t)DT_INST_PROP(id, dbc_count_b),            \
            },                                                                  \
            .pina_pin = (uint8_t)DT_INST_PROP(id, pina),                        \
            .pinb_pin = (uint8_t)DT_INST_PROP(id, pinb),                        \
            .led_pin = (uint8_t)DT_INST_PROP(id, pin_led),                      \
        },                                                                      \
        .qdec_pin = {                                                           \
            .pina = (uint8_t)DT_INST_PROP(id, pina),                            \
            .pinb = (uint8_t)DT_INST_PROP(id, pinb),                            \
        },                                                                      \
        .pincfg = PINCTRL_DT_INST_DEV_CONFIG_GET(id),                           \
    };                                                                          \
                                                                                \
    static struct qdec_airoha_data qdec_airoha_p##id##_data = {                 \
        .irq_cb = NULL,                                                         \
        .irq_cb_data = NULL,                                                    \
    };                                                                          \
\
DEVICE_DT_INST_DEFINE(id,\
                      qdec_airoha_init,\
                      NULL,\
                      &qdec_airoha_p##id##_data,\
                      &qdec_airoha_p##id##_cfg,\
                      PRE_KERNEL_2, \
                      91, \
                      &qdec_airoha_driver_api);

DT_INST_FOREACH_STATUS_OKAY(QDEC_AIROHA_DEVICE);
