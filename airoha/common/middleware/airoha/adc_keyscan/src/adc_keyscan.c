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

#if defined(AIR_ADC_KEYSCAN_ENABLE)

#include "adc_keyscan.h"
#include "hal_ccni.h"

#define ADC_KEYSCAN_DEBUG_LOG_ENABLE
// #define USB_SOF_SLOW_ENABLE
/*mcu*/
#if defined(CORE_MCU)
#include "hal_clock.h"
#include "hal_saradc_internal.h"
#include "hal_clock_internal.h"
#include "air_chip.h"
#include "hal_platform.h"
#include "hal_hw_keyscan.h"
#include "hal_cross_core_config.h"
#include "memory_attribute.h"
#include "pka.h"
#endif/*CORE_MCU*/

#if defined(CORE_RISCV)
#include "hal_saradc.h"
#include "syslog.h"
#include "hal_hw_keyscan.h"
#include "hal_gpio.h"
#include "hal_nvic.h"
#include "hal_cross_core_config.h"
#include "hal_ccni.h"
#include "hal_ccni_config.h"
#endif/*CORE_RISCV*/
/*riscv*/

#define RISCV_CCNI_EVENT_TO_CM33    IRQGEN_RISCV2MCU_EVENT3

#if defined(CORE_MCU)
#if !IS_ENABLED(CONFIG_MCUBOOT) && !defined(AIR_DOWNLOAD_AGENT)
volatile sw_keyscan_data_buf_info_t *sw_keyscan_data_buf =  (sw_keyscan_data_buf_info_t *)CROSS_CORE_MEM_VARIABLE(adc_keyscan_buf_info);
volatile sw_keyscan_info_t *sw_keyscan_info =  (sw_keyscan_info_t *)CROSS_CORE_MEM_VARIABLE(adc_keyscan_cfg_info);
#endif

static sw_keyscan_keybit_data_t g_temp_data;
static uint32_t V_threshold;
ATTR_TEXT_IN_TCM void sw_keyscan_mcu_trigger_dummy_irq(void)
{
#ifdef USB_SOF_SLOW_ENABLE
    static uint32_t test_num;
    if((test_num%8)==0)
    {
        hal_hw_keyscan_sw_trigger();
    }
    test_num++;
#else
    if(sw_keyscan_data_buf->write_data_index != 0)
    {
        return;
    }
    hal_hw_keyscan_sw_trigger();
#endif
}

adc_keyscan_status_t sw_keyscan_mcu_init(sw_keyscan_cfg_t *cfg_info)
{
    extern void hal_usb_lock_sleep(void);
    hal_usb_lock_sleep();
    if(cfg_info == NULL)
    {
        sw_keyscan_info->init_flag = true;
        return ADC_KEYSCAN_INVALID_PARAMETER;
    }
    sw_keyscan_info->row_gpio_num = cfg_info ->row_gpio_num;
    sw_keyscan_info->row_gpio_map[0] = cfg_info ->row_gpio_map[0];
    sw_keyscan_info->row_gpio_map[1] = cfg_info ->row_gpio_map[1];
    sw_keyscan_info->row_gpio_map[2] = cfg_info ->row_gpio_map[2];
    sw_keyscan_info->mux_en_gpio = cfg_info ->mux_en_gpio;
    sw_keyscan_info->mux_max_index = cfg_info ->mux_max_index;
    sw_keyscan_info->mux_trigger_index = cfg_info ->mux_trigger_index;
    sw_keyscan_info->v_threshold = cfg_info ->v_threshold;
    sw_keyscan_info->init_flag = true;
    sw_keyscan_data_buf->write_data_index=0;
    sw_keyscan_data_buf->read_data_index=0;
    hal_adc_init();
    hal_clock_enable(HAL_CLOCK_CG_FAST_DMA0);
    hal_saradc_read_calibration(HAL_SARADC_MEASURE_DIV_MODE);
    hal_saradc_get_calibration_voltage_mV(HAL_SARADC_MEASURE_DIV_MODE,sw_keyscan_info->v_threshold,&V_threshold);
    
#ifdef ADC_KEYSCAN_DEBUG_LOG_ENABLE
    printk("sw_keyscan_info = %x",(uint32_t)sw_keyscan_info);
    printk("sw_keyscan_data_buf = %x",(uint32_t)sw_keyscan_data_buf);
    printk("sw_keyscan_mcu_init step1/2 ok");
    printk("sw_keyscan_mcu_init.....mcu freq:%d,ibex index: %d\r\n", get_curr_cpu_freq_hz(),clock_mux_cur_sel(CLK_IBEX_SEL));
    printk("sw_keyscan_V_threshold = %dmv",V_threshold);
#endif
    return ADC_KEYSCAN_STATUS_OK;
}

adc_keyscan_status_t sw_keyscan_mcu_register_callback(adc_keyscan_callback_t callback)
{
    if(callback == NULL)
    {
        return ADC_KEYSCAN_INVALID_PARAMETER;
    }

    if(sw_keyscan_info->callback != NULL)
    {
        printk("sw_keyscan_mcu_register_callback failed, callback already registered");
        return ADC_KEYSCAN_STATUS_ERROR;
    }else{
        sw_keyscan_info->callback = callback;
        printk("sw_keyscan_mcu_register_callback ok");
    }
    return ADC_KEYSCAN_STATUS_OK;
}

void sw_keyscan_mcu_deinit(void)
{
    hal_adc_deinit();
    printk("sw_keyscan_mcu_init");
}

ATTR_TEXT_IN_TCM void sw_keyscan_mcu_process(sw_keyscan_keybit_data_t *output_data)
{
    int j;
    #if defined(ADC_RAW_DATA_LOG)
    print_count++;
    if (print_count > 1000){
        print_count=0;
    }
    printk("=============ADC RAW DATA=============\n");
    #endif

    /*process one pack data*/
    while(sw_keyscan_data_buf->read_data_index < sw_keyscan_info->mux_max_index)
    {
        while((sw_keyscan_data_buf->write_data_index > sw_keyscan_data_buf->read_data_index))
        {
            /*check adc value -> key pressed*/
            for(j = 0;j<16;j++)
            {
                if(sw_keyscan_data_buf->mux_row_data[sw_keyscan_data_buf->read_data_index].adc_data[j] < sw_keyscan_info->v_threshold)
                {
                    output_data->keyid_bit[sw_keyscan_data_buf->read_data_index] |=(1<<j);
                }else
                {
                    output_data->keyid_bit[sw_keyscan_data_buf->read_data_index] &=~(1<<j);
                }
            }

            #if defined(ADC_RAW_DATA_LOG)
            if (print_count > 1000){
                printk("sw_keyscan_mcu_init adc_data[%d][0-7] = %d, %d, %d, %d,   %d, %d, %d, %d"
                    , sw_keyscan_data_buf->read_data_index
                    , sw_keyscan_data_buf->mux_row_data[sw_keyscan_data_buf->read_data_index].adc_data[0]
                    , sw_keyscan_data_buf->mux_row_data[sw_keyscan_data_buf->read_data_index].adc_data[1]
                    , sw_keyscan_data_buf->mux_row_data[sw_keyscan_data_buf->read_data_index].adc_data[2]
                    , sw_keyscan_data_buf->mux_row_data[sw_keyscan_data_buf->read_data_index].adc_data[3]
                    , sw_keyscan_data_buf->mux_row_data[sw_keyscan_data_buf->read_data_index].adc_data[4]
                    , sw_keyscan_data_buf->mux_row_data[sw_keyscan_data_buf->read_data_index].adc_data[5]
                    , sw_keyscan_data_buf->mux_row_data[sw_keyscan_data_buf->read_data_index].adc_data[6]
                    , sw_keyscan_data_buf->mux_row_data[sw_keyscan_data_buf->read_data_index].adc_data[7]
                );

                printk("sw_keyscan_mcu_init adc_data[%d][8-15] = %d, %d, %d, %d,   %d, %d, %d, %d"
                    , sw_keyscan_data_buf->read_data_index
                    , sw_keyscan_data_buf->mux_row_data[sw_keyscan_data_buf->read_data_index].adc_data[0]
                    , sw_keyscan_data_buf->mux_row_data[sw_keyscan_data_buf->read_data_index].adc_data[1]
                    , sw_keyscan_data_buf->mux_row_data[sw_keyscan_data_buf->read_data_index].adc_data[2]
                    , sw_keyscan_data_buf->mux_row_data[sw_keyscan_data_buf->read_data_index].adc_data[3]
                    , sw_keyscan_data_buf->mux_row_data[sw_keyscan_data_buf->read_data_index].adc_data[4]
                    , sw_keyscan_data_buf->mux_row_data[sw_keyscan_data_buf->read_data_index].adc_data[5]
                    , sw_keyscan_data_buf->mux_row_data[sw_keyscan_data_buf->read_data_index].adc_data[6]
                    , sw_keyscan_data_buf->mux_row_data[sw_keyscan_data_buf->read_data_index].adc_data[7]
                );
            }
            #endif

            sw_keyscan_data_buf->read_data_index++;
        }
    }

    if(sw_keyscan_info->callback != NULL)
    {
        sw_keyscan_info->callback(output_data);
    }
    sw_keyscan_data_buf->write_data_index=0;
    sw_keyscan_data_buf->read_data_index=0;
}

ATTR_TEXT_IN_TCM void CCNI_DEF_HANDLER(11)(hal_ccni_event_t event, hal_ccni_message_t *msg)
{
    sw_keyscan_mcu_process(&(g_temp_data));
}

#if 0
ATTR_TEXT_IN_TCM void hw_keyscan_irq_callback(uint32_t *keys, uint8_t one_packet_valid_num, uint8_t total_key_num, bool is_ghost_happen)
{
    pka_share_callback_type_t type;
    uint32_t tx_cnt;
    pka_spi_callback_pre_process(&type, &tx_cnt);
    extern void keyboard_send_report_gaming_mode(void);
    keyboard_send_report_gaming_mode();
    pka_spi_callback_post_process();
}
#endif

void sw_keyscan_bt_trigger_control(bool is_enable)
{
    #if 0
    hal_hw_keyscan_status_t ret;
    #endif

    #define BT_BASE_ADDR 0xa0010000

    /* enable keyscan setting */
    if (is_enable)
    {
        /* enable bt setting */
        // *((volatile uint32_t *) (BT_BASE_ADDR + 0x7A8)) = 0;
        // *((volatile uint32_t *) (BT_BASE_ADDR + 0x7A4)) = (*((volatile uint32_t *) (BT_BASE_ADDR + 0x08)) + 1000);
        // *((volatile uint32_t *) (BT_BASE_ADDR + 0x7BC)) = 0;
        // *((volatile uint32_t *) (BT_BASE_ADDR + 0x7C0)) = 2000;
        // *((volatile uint32_t *) (BT_BASE_ADDR + 0x7D4)) = 0;
        // *((volatile uint32_t *) (BT_BASE_ADDR + 0x7D8)) = 0;
        // *((volatile uint32_t *) (BT_BASE_ADDR + 0x7A0)) &= ~(0x7);
        // *((volatile uint32_t *) (BT_BASE_ADDR + 0x7A0)) |= 0x1;
        *(volatile uint32_t *)(0x42020038) = (0x0);//keyscan disable sw trigger mode
        #if 0
        // extern void hw_keyscan_dummy_Isr(void);
        hal_nvic_register_isr_handler(KEYSCAN_IRQn, (void *)hw_keyscan_dummy_Isr);
        ret = hal_hw_keyscan_register_callback((hal_hw_keyscan_callback_t)hw_keyscan_irq_callback);
        hal_nvic_enable_irq(KEYSCAN_IRQn);
        printk("hal_hw_keyscan_register_callback ret=%d", ret);
        #endif
    }
    else
    {
        *(volatile uint32_t *)(0x42020038) = (0x1);//keyscan enable sw trigger mode
        #if 0
        ret = hal_hw_keyscan_register_callback(NULL);
        hal_nvic_disable_irq(KEYSCAN_IRQn);
        printk("hal_hw_keyscan_register_callback ret=%d", ret);
        #endif
    }
    printk("sw_keyscan_mcu_bt_trigger_control: %d\r\n", is_enable);
}

#endif/*CORE_MCU*/

#if defined(CORE_RISCV)
/*riscv*/
volatile sw_keyscan_data_buf_info_t *g_sw_keyscan_data_buf =  (sw_keyscan_data_buf_info_t *)CROSS_CORE_MEM_VARIABLE(adc_keyscan_buf_info);
volatile sw_keyscan_info_t *g_sw_keyscan_info =  (sw_keyscan_info_t *)CROSS_CORE_MEM_VARIABLE(adc_keyscan_cfg_info);
static hal_saradc_special_gpio_cfg_t g_gpio_cfg;
static sw_keyscan_info_t g_riscv_cfg_info;

#ifdef ADC_KEYSCAN_DEBUG_LOG_ENABLE
log_create_module(risvc_sw_keyscan, PRINT_LEVEL_INFO);
#endif

void dummy_irq_callback()
{
    sw_keyscan_riscv_scan_once();
}

void sw_keyscan_hw_keyscan_init(void)
{
    hal_hw_keyscan_config_t keyscan_test_config = {
        .mode = HAL_HW_KEYSCAN_SW_TRIGGER,
        .swich_time = HAL_HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_2T,
        .rate = HAL_HW_KEYSCAN_RATE_32KRR,
        .debounce_en = false,
        .release_debounce = 0,
        .press_debounce = 0,
        .row_num = 1,
        .col_num = 1,
        .row = {HAL_GPIO_26},
        .col = {HAL_GPIO_27},
        .keyboard_type = HAL_HW_KEYSCAN_TYPE_GAMING_KB_MECH,
        .col_in_setting = HAL_HW_KEYSCAN_IO_SETING_HIGH_ACTIVE,
    };
    hal_hw_keyscan_status_t ret;
    ret = hal_hw_keyscan_init(&keyscan_test_config);
    if(ret!= HAL_HW_KEYSCAN_STATUS_OK)
    {
#ifdef ADC_KEYSCAN_DEBUG_LOG_ENABLE
        LOG_MSGID_I(risvc_sw_keyscan, "hal_hw_keyscan_init failed-%d", 1,ret);
#endif
    }

    ret = hal_hw_keyscan_register_callback((hal_hw_keyscan_callback_t)dummy_irq_callback);
    if(ret!= HAL_HW_KEYSCAN_STATUS_OK)
    {
#ifdef ADC_KEYSCAN_DEBUG_LOG_ENABLE
        LOG_MSGID_I(risvc_sw_keyscan, "hal_hw_keyscan_register_callback failed-%d", 1,ret);
#endif
    }

    ret = hal_hw_keyscan_enable();
    if(ret!= HAL_HW_KEYSCAN_STATUS_OK)
    {
#ifdef ADC_KEYSCAN_DEBUG_LOG_ENABLE
        LOG_MSGID_I(risvc_sw_keyscan, "hal_hw_keyscan_enable failed-%d", 1,ret);
#endif
    }
}

void sw_keyscan_riscv_init(void)
{
    sw_keyscan_hw_keyscan_init();
    hal_adc_status_t state;
    state = hal_saradc_dma_init();
    if(state != HAL_ADC_STATUS_OK)
    {
#ifdef ADC_KEYSCAN_DEBUG_LOG_ENABLE
        LOG_MSGID_I(risvc_sw_keyscan, "hal_saradc_dma_init failed", 0);
#endif
    }

    hal_saradc_init(HAL_SARADC_DATA_RATE_HS_MODE,HAL_SARADC_MEASURE_DIV_MODE);
    hal_saradc_set_gpio_mode(0xffff,HAL_SARADC_GPIO_ANALOG_MODE);

    while(!(g_sw_keyscan_info->init_flag));
    g_gpio_cfg.gpio_pin[0] = g_sw_keyscan_info->row_gpio_map[0];
    g_gpio_cfg.gpio_pin[1] = g_sw_keyscan_info->row_gpio_map[1];
    g_gpio_cfg.gpio_pin[2] = g_sw_keyscan_info->row_gpio_map[2];
    g_riscv_cfg_info.mux_en_gpio = g_sw_keyscan_info->mux_en_gpio;
    g_gpio_cfg.mux_index = 0;

    g_riscv_cfg_info.row_gpio_num = g_sw_keyscan_info->row_gpio_num;
    g_riscv_cfg_info.mux_max_index = g_sw_keyscan_info->mux_max_index;
    g_riscv_cfg_info.mux_trigger_index = g_sw_keyscan_info->mux_trigger_index;

#ifdef ADC_KEYSCAN_DEBUG_LOG_ENABLE
    LOG_MSGID_I(risvc_sw_keyscan,"g_sw_keyscan_data_buf = %x",1,(uint32_t)g_sw_keyscan_data_buf);
    LOG_MSGID_I(risvc_sw_keyscan,"g_sw_keyscan_info = %x",1,(uint32_t)g_sw_keyscan_info);
    LOG_MSGID_I(risvc_sw_keyscan,"g_gpio_cfg.gpio_pin[0] = %d",1,g_gpio_cfg.gpio_pin[0]);
    LOG_MSGID_I(risvc_sw_keyscan,"g_gpio_cfg.gpio_pin[1] = %d",1,g_gpio_cfg.gpio_pin[1]);
    LOG_MSGID_I(risvc_sw_keyscan,"g_gpio_cfg.gpio_pin[2] = %d",1,g_gpio_cfg.gpio_pin[2]);
    LOG_MSGID_I(risvc_sw_keyscan, "sw_keyscan_riscv_init step2/2 ok", 0);
#endif
}

void sw_keyscan_riscv_deinit(void)
{
    hal_saradc_deinit();
}

void sw_keyscan_riscv_get_data(void)
{
    if(g_sw_keyscan_data_buf->write_data_index != 0)
    {
        return;
    }

    int i=0;
    for(i=0;i<g_riscv_cfg_info.mux_max_index;i++)
    {
        g_gpio_cfg.mux_index=i;
        hal_saradc_get_data_immediately_for_special(g_sw_keyscan_data_buf->mux_row_data[i].adc_data,0xffff,g_gpio_cfg,g_riscv_cfg_info.mux_max_index);
        g_sw_keyscan_data_buf->write_data_index++;
        if(i == g_riscv_cfg_info.mux_trigger_index)
        {
            /*muc to riscv data address*/
            hal_ccni_event_t event = IRQGEN_RISCV2MCU_EVENT11;
            hal_ccni_set_event(event,NULL);
        }
        /*for mux en pin control*/
        if(i == 0)
        {
            hal_gpio_set_output(g_riscv_cfg_info.mux_en_gpio,0);
        }else if(i == 4)
        {
            hal_gpio_set_output(g_riscv_cfg_info.mux_en_gpio,1);
        }
    }

}

hal_ccni_status_t sw_keyscan_rv_ccni__send_to_CM33()
{
    hal_ccni_message_t msg;

    msg.data[0] = HID_CCNI_MSG_ADC_SCAN_START;

    return hal_ccni_set_event(RISCV_CCNI_EVENT_TO_CM33, &msg);
}

void sw_keyscan_riscv_scan_once(void)
{
    sw_keyscan_rv_ccni__send_to_CM33();
    sw_keyscan_riscv_get_data();
}

#endif/*CORE_RISCV*/
#endif /* AIR_ADC_KEYSCAN_ENABLE */
