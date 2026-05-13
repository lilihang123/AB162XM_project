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

#include "hal_adc.h"
#include "hal_saradc_internal.h"

#if defined(HAL_ADC_MODULE_ENABLED) || defined(HAL_AIOADC_MODULE_ENABLED)
#include "hal_nvic.h"
#include "hal_nvic_internal.h"
uint8_t saradc_sdadc_common_use_count = 0;
void hal_saradc_sdadc_common_setting_internal(bool enable)
{
    uint32_t save_mask;
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    if (enable) {
        saradc_sdadc_common_use_count++;
        if (saradc_sdadc_common_use_count == 1) {
            /* BG enable */
            *((volatile uint32_t *)(0x42080048)) = 0x4401;
            /* VREF switch1 enable */
            *((volatile uint32_t *)(0x4208004C)) = 0x70F;
            /* VREF switch2 enable */
            *((volatile uint32_t *)(0x42080050)) = 0x40F;
            /* GLB enable */
            *((volatile uint32_t *)(0x4208005C)) = 0x41;
        }
    } else {
        if (saradc_sdadc_common_use_count >= 1) {
            saradc_sdadc_common_use_count--;
            if (saradc_sdadc_common_use_count == 0) {
                /* BG disable */
                *((volatile uint32_t *)(0x42080048)) = 0;
                /* GLB disable */
                *((volatile uint32_t *)(0x4208005C)) = 0;
            }
        }
    }
    hal_nvic_restore_interrupt_mask(save_mask);
}
#endif

#ifdef HAL_ADC_MODULE_ENABLED

#include "hal_clock.h"
#include "hal_log.h"
#include "hal_flash_disk_internal.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_internal.h"
#include "hal_gpio_internal.h"
#include "hal_gpt.h"
#include "hal_clock_internal.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAL_SLEEP_MANAGER_ENABLED
typedef struct {
    uint32_t    MACRO_CON2;
    uint32_t    ANA_EN_CON;
    uint32_t    ACD_FUNC_MODE_CTL;
    uint32_t    AUXADC_SPL_CON;
    uint32_t    AUXADC_DIV_CON;
} hal_saradc_backup_restore_rg_t;
volatile static hal_saradc_backup_restore_rg_t g_saradc_backup_restore_rg;

void adc_backup_all_register(void);
void adc_restore_all_register(void);
#endif

//#define ADC_DEBUG_LOG
#ifdef ADC_DEBUG_LOG
#include "syslog.h"
log_create_module(ADC_MODULE, PRINT_LEVEL_INFO);
#define ADC_DEBUG_INF(_message,arg_cnt,...)  LOG_MSGID_I(ADC_MODULE,_message,arg_cnt,##__VA_ARGS__)
#else
#define ADC_DEBUG_INF(_message,arg_cnt,...)
#endif

float saradc_vref_real, saradc_oe, saradc_ge;

uint32_t g_adc_raw_data[HAL_SARADC_CHANNEL_GPIO_MAX] = {0};
volatile uint32_t adc_resource_control = 0;

/**
 * @brief Initializes the ADC (Analog-to-Digital Converter) module.
 *
 * This function prepares the ADC hardware for operation. It should
 * be called before using any other ADC-related APIs to ensure proper setup.
 * The initialization includes configuring registers, enabling clocks,
 * and preparing the hardware for data conversion.
 *
 * @return hal_adc_status_t
 *         This API returns a status code indicating the result of the
 *         initialization process. Possible return values are as follows:
 *
 *         - HAL_ADC_STATUS_OK (0): Initialization was successful.
 *         - HAL_ADC_STATUS_ERROR (-1): An error occurred during initialization.
 *         - HAL_ADC_STATUS_ERROR_CHANNEL (-2): The specified ADC channel is invalid.
 *         - HAL_ADC_STATUS_ERROR_BUSY (-3): The ADC module is currently busy.
 *         - HAL_ADC_STATUS_INVALID_PARAMETER (-4): Invalid parameter passed to the initialization function.
 *
 * Ensure the parameters used in this and subsequent ADC functions are valid
 * to avoid errors like HAL_ADC_STATUS_INVALID_PARAMETER or HAL_ADC_STATUS_ERROR_CHANNEL.
 */
hal_adc_status_t hal_adc_init(void)
{
    uint32_t int_mask;
#ifdef HAL_SLEEP_MANAGER_ENABLED
    /* SARADC BACKUP RESTORE */
    sleep_management_register_infra_pd_suspend_callback(INFRA_PD_BACKUP_RESTORE_SAR_ADC, (sleep_management_suspend_callback_t)adc_backup_all_register, NULL);
    sleep_management_register_infra_pd_resume_callback(INFRA_PD_BACKUP_RESTORE_SAR_ADC, (sleep_management_resume_callback_t)adc_restore_all_register, NULL);
#endif /*HAL_SLEEP_MANAGER_ENABLED*/

    /* For multi user usage */
    hal_nvic_save_and_set_interrupt_mask(&int_mask);
    adc_resource_control++;
    if (adc_resource_control > 1) {
        hal_nvic_restore_interrupt_mask(int_mask);
        return HAL_ADC_STATUS_OK;
    }
    hal_nvic_restore_interrupt_mask(int_mask);
    hal_saradc_init(HAL_SARADC_DATA_RATE_HS_MODE, HAL_SARADC_MEASURE_DIV_MODE);
    return HAL_ADC_STATUS_OK;
}

/**
 * @brief Deinitializes the ADC module.
 *
 * This function disables and deinitializes the ADC (Analog-to-Digital Converter) hardware
 * module, freeing up any resources associated with it. It should be called when the ADC
 * is no longer needed to release the resources properly.
 *
 * @return hal_adc_status_t
 *         - HAL_ADC_STATUS_OK: Operation successful.
 */

hal_adc_status_t hal_adc_deinit(void)
{
    uint32_t int_mask;
    /* For multi user usage */
    hal_nvic_save_and_set_interrupt_mask(&int_mask);
    adc_resource_control--;
    if (adc_resource_control == 0) {
        hal_nvic_restore_interrupt_mask(int_mask);
        hal_saradc_deinit();
        return HAL_ADC_STATUS_OK;
    }
    hal_nvic_restore_interrupt_mask(int_mask);
    return HAL_ADC_STATUS_OK;
}
volatile uint32_t adc_get_data_resource[HAL_SARADC_CHANNEL_GPIO_MAX];
static volatile uint32_t adc_polling_count = 0;
static volatile uint8_t adc_average_status = 0;

/**
 * @brief Reads ADC data from the specified channel using polling.
 *
 * This function performs an analog-to-digital conversion on the specified ADC channel and
 * retrieves the converted digital data. The operation uses a polling mechanism to wait for
 * the conversion to complete. It stores the result in the variable pointed to by the 'data' parameter.
 *
 * @param[in] channel The ADC channel to read from, of type 'hal_adc_channel_t', indicating
 *                    which hardware channel to use for conversion.
 * @param[out] data   Pointer to a 'uint32_t' variable where the converted digital data will be stored.
 *
 * @return hal_adc_status_t
 *         - HAL_ADC_STATUS_OK: Data was successfully read.
 *         - HAL_ADC_STATUS_ERROR_CHANNEL: The specified channel number is incorrect or not supported.
 *         - HAL_ADC_STATUS_ERROR_BUSY: The ADC is busy with a previous operation and cannot process new requests.
 *         - HAL_ADC_STATUS_INVALID_PARAMETER: One or more parameters provided to the function are invalid.
 */
hal_adc_status_t hal_adc_get_data_polling(hal_adc_channel_t channel, uint32_t *data)
{

    uint32_t times = 0;
    uint32_t temp_data = 0;
    uint32_t int_mask;

    /* Channel is invalid */
    if (channel >= HAL_SARADC_CHANNEL_GPIO_MAX) {
        printk("[ADC] Invalid channel: %d.", channel);
        return HAL_ADC_STATUS_ERROR_CHANNEL;
    }

    /* Parameter check */
    if (data == NULL) {
        printk("[ADC] Invalid parameter.");
        return HAL_ADC_STATUS_INVALID_PARAMETER;
    }

    /* Avoid mixing polling mode and average mode */
    hal_nvic_save_and_set_interrupt_mask(&int_mask);
    if (adc_average_status == 0) {
        adc_polling_count++;
    } else {
        hal_nvic_restore_interrupt_mask(int_mask);
        printk("[ADC][Poll] Busy.");
        return HAL_ADC_STATUS_ERROR_BUSY;
    }
    /* adc gpio default as DGPIO,so,need to switch it to AGPIO,otherwise adc will not work. */
    if (adc_get_data_resource[channel] == 0) {
        if (channel <= 11) {
            hal_gpio_set_analog_mode(channel + 26);
        } else {
            hal_gpio_set_analog_mode(channel + 28);
        }
    }
    adc_get_data_resource[channel]++;
    hal_nvic_restore_interrupt_mask(int_mask);

    for (times = 0; times < 8; times++) {

        hal_nvic_save_and_set_interrupt_mask(&int_mask);
        /* Disable the corresponding region */
        ADC->AUXADC_CON1 = 0;
        /* Start auxadc */
        ADC->AUXADC_CON1 = (1 << (uint16_t)channel);

        /* Wait until the module status is idle */
        while (ADC->AUXADC_CON3_UNION.AUXADC_CON3_CELLS.ADC_STAT & AUXADC_CON3_ADC_STA_MASK);

        /* Retrieve data for corresponding channel */
        temp_data += ADC->AUXADC_DATA[channel];

        hal_nvic_restore_interrupt_mask(int_mask);

    }

    hal_nvic_save_and_set_interrupt_mask(&int_mask);
    adc_polling_count--;
    adc_get_data_resource[channel]--;
    if (adc_get_data_resource[channel] == 0) {
        /* Switch GPIO to digital mode after sample done */
        if(channel <= 11) {
            hal_gpio_clear_analog_mode(channel + 26);
        } else {
            hal_gpio_clear_analog_mode(channel + 28);
        }
    }
    hal_nvic_restore_interrupt_mask(int_mask);
    /* Take the average over 8 times */
    g_adc_raw_data[channel] = temp_data >> 3;

    *data = (temp_data >> 3);

    ADC_DEBUG_INF("Debug [ADC][Poll] channel %d, data %d", 2, channel, *data);
    return HAL_ADC_STATUS_OK;
}

#ifdef HAL_ADC_SUPPORT_AVERAGE_ENABLE
/**
 * @brief Get the average ADC data for a specified channel.
 *
 * This function calculates the average of ADC data samples for a given channel and stores it in the provided memory location.
 *
 * @param channel The ADC channel from which to read the average data. It should be of type 'hal_adc_channel_t'.
 * @param average_num The number of samples to be used for calculating the average. It should be of type 'hal_adc_average_t'.
 * @param[out] data Pointer to a variable where the averaged data will be stored. It must be a valid pointer to a 'uint32_t'.
 *
 * @return hal_adc_status_t
 *         - HAL_ADC_STATUS_OK: Data was successfully read.
 *         - HAL_ADC_STATUS_ERROR_CHANNEL: The specified channel number is incorrect or not supported.
 *         - HAL_ADC_STATUS_ERROR_BUSY: The ADC is busy with a previous operation and cannot process new requests.
 *         - HAL_ADC_STATUS_INVALID_PARAMETER: One or more parameters provided to the function are invalid.
 */
hal_adc_status_t hal_adc_get_average_data(hal_adc_channel_t channel, hal_adc_average_t average_num, uint32_t *data)
{
    uint32_t int_mask;
    /* Channel is invalid */
    if (channel >= HAL_SARADC_CHANNEL_GPIO_MAX) {
        log_hal_msgid_error("[ADC] Invalid channel: %d.", 1, channel);
        return HAL_ADC_STATUS_ERROR_CHANNEL;
    }

    /* Parameter check */
    if (data == NULL) {
        log_hal_msgid_error("[ADC] Invalid parameter.", 0);
        return HAL_ADC_STATUS_INVALID_PARAMETER;
    }

    if (average_num >= HAL_ADC_AVERAGE_MAX) {
        log_hal_msgid_error("[ADC] Invalid parameter.", 0);
        return HAL_ADC_STATUS_INVALID_PARAMETER;
    }

    /* Avoid mixing polling mode and average mode */
    hal_nvic_save_and_set_interrupt_mask(&int_mask);
    if (adc_average_status == 0 && adc_polling_count == 0) {
        adc_average_status = 1;
    } else {
        hal_nvic_restore_interrupt_mask(int_mask);
        log_hal_msgid_warning("[ADC][Aver] Busy.", 0);
        return HAL_ADC_STATUS_ERROR_BUSY;
    }
    hal_nvic_restore_interrupt_mask(int_mask);

    /* adc gpio default as DGPIO,so,need to switch it to AGPIO,otherwise adc will not work. */
    if (channel <= 11) {
        hal_gpio_set_analog_mode(channel + 26);
    } else {
        hal_gpio_set_analog_mode(channel + 28);
    }
    /* Disable the corresponding channel */
    ADC->AUXADC_CON1 = 0;

    /* Enable auto average */
    ADC->AUXADC_CON4_UNION.AUXADC_CON4 |= (1 << 8);

    /* Set average number */
    ADC->AUXADC_AVG_NUM = average_num;

    /* Start auxadc */
    ADC->AUXADC_CON1 = (1 << (uint16_t)channel);

    /* Wait until the module status is ready */
    while (ADC->AUXADC_AVG_READY == 0);

    /* Retrieve data for corresponding channel */
    *data = ADC->AUXADC_AVG_DATA >> 3;

    // *((volatile uint32_t *)(0x420E0074)) |= (1 << channel);
    if (channel <= 11) {
        hal_gpio_clear_analog_mode(channel + 26);
    } else {
        hal_gpio_clear_analog_mode(channel + 28);
    }

    /* when data ready flag set */
    /* Disable auto average */
    //ADC->AUXADC_CON4 &= ~(1 << 8);
    adc_average_status = 0;
    ADC_DEBUG_INF("Debug [ADC][Aver] channel %d, data %d", 2, channel, *data);
    return HAL_ADC_STATUS_OK;
}

#endif /*HAL_ADC_SUPPORT_AVERAGE_ENABLE */
/**
 * @brief Configure the SAR ADC's data rate and measurement mode.
 *
 * This function sets the operational modes of the Successive Approximation Register (SAR) ADC by specifying the data rate
 * and measurement mode to be used during conversions. The configuration directly impacts the sampling speed and measurement behavior.
 *
 * @param data_rate Specifies the data rate for the SAR ADC operation. The available options are:
 *        - HAL_SARADC_DATA_RATE_HS_MODE: High-speed mode
 *        - HAL_SARADC_DATA_RATE_LS_MODE: Low-speed mode
 *
 * @param measure_mode Specifies the measurement mode for the SAR ADC. The available options are:
 *        - HAL_SARADC_MEASURE_SE_MODE: Single-ended measurement mode
 *        - HAL_SARADC_MEASURE_DIV_MODE: Divided measurement mode
 *        - HAL_SARADC_MEASURE_DIFF_MODE: Differential measurement mode
 *
 * @return The status result of the configuration operation as type 'hal_adc_status_t'. Possible return values may include:
 *         - HAL_ADC_STATUS_OK: Configuration successful.
 *         - HAL_ADC_STATUS_INVALID_PARAMETER: One or more parameters provided to the function are invalid.
 */
hal_adc_status_t hal_saradc_set_mode(hal_saradc_data_rate_t data_rate, hal_saradc_measure_mode_t measure_mode)
{
    switch (measure_mode) {
        case (HAL_SARADC_MEASURE_SE_MODE):
            //SE mode
            *((volatile uint32_t *)(0x42080084)) = 0x10;
            *((volatile uint32_t *)(0x42080088)) = 0x0;
            break;
        case (HAL_SARADC_MEASURE_DIV_MODE):
            //DIV mode
            *((volatile uint32_t *)(0x42080084)) = 0x10;
            *((volatile uint32_t *)(0x42080088)) = 0x4000;
            break;
        case (HAL_SARADC_MEASURE_DIFF_MODE):
            //DIFF mode
            *((volatile uint32_t *)(0x42080084)) = 0x4010;
            *((volatile uint32_t *)(0x42080088)) = 0x0;
            break;
        default:
            return HAL_ADC_STATUS_INVALID_PARAMETER;
            break;
    }

    switch (data_rate) {
        case (HAL_SARADC_DATA_RATE_HS_MODE):
            //HS mode
            ADC->AUXADC_DIV_CON = 0x0;
            *((volatile uint32_t *)(0x42080084)) = 0x21;
            if (measure_mode == HAL_SARADC_MEASURE_DIFF_MODE) {
                *((volatile uint32_t *)(0x42080084)) = 0x4021;
            } else {
                *((volatile uint32_t *)(0x42080084)) = 0x21;
            }
            *((volatile uint32_t *)(0x4208008C)) = 0x140;
            break;
        case (HAL_SARADC_DATA_RATE_MS_MODE):
            //MS mode
            ADC->AUXADC_DIV_CON = 0x1;
            *((volatile uint32_t *)(0x42080084)) = 0x11;
            *((volatile uint32_t *)(0x42080084)) = 0x11;
            *((volatile uint32_t *)(0x4208008C)) = 0x0;
            break;
        case (HAL_SARADC_DATA_RATE_LS_MODE):
            //LS mode
            ADC->AUXADC_DIV_CON = 0x5;
            *((volatile uint32_t *)(0x42080084)) = 0x10;
            *((volatile uint32_t *)(0x42080084)) = 0x30;
            *((volatile uint32_t *)(0x4208008C)) = 0x0;
            break;
        default:
            return HAL_ADC_STATUS_INVALID_PARAMETER;
            break;
    }
    // log_hal_msgid_info("0x42080084 value:%x", 0, *((volatile uint32_t *)(0x42080084)));
    return HAL_ADC_STATUS_OK;
}

const uint32_t mode_otp_address[HAL_SARADC_MEASURE_MAX] = {0x6B, 0x70, 0x75};
/**
 * @brief Read the calibration data for a specified SAR ADC measurement mode.
 *
 * This function retrieves the calibration constants used for adjusting the ADC readings to compensate for hardware variances
 * in the selected measurement mode. This ensures that the ADC provides accurate and reliable measurements under different conditions.
 *
 * @param measure_mode Specifies the measurement mode for which the calibration data is to be read. The available options are:
 *        - HAL_SARADC_MEASURE_SE_MODE: Single-ended measurement mode
 *        - HAL_SARADC_MEASURE_DIV_MODE: Divided measurement mode
 *        - HAL_SARADC_MEASURE_DIFF_MODE: Differential measurement mode
 *
 * @return The status of the calibration read operation, returned as a value of type 'hal_adc_status_t'. Possible return values may include:
 *         - HAL_ADC_STATUS_OK: Calibration data read successfully.
 */
hal_adc_status_t hal_saradc_read_calibration(hal_saradc_measure_mode_t measure_mode)
{
    uint8_t effuse_data[5];
    uint32_t temp_value, flag, gain, offset, sar_reserved, value_vref;
    hal_flash_otp_read(mode_otp_address[measure_mode], effuse_data, 5);
    flag = effuse_data[0];
    temp_value = (uint32_t)(effuse_data[1] << 24) | (effuse_data[2] << 16)|(effuse_data[3] << 8) | effuse_data[4];
    gain = temp_value & 0x3ff;
    offset = (temp_value >> 10) & 0x1ff;
    sar_reserved = (temp_value >> 19) & 0x1fff;
    value_vref = (temp_value >> 19) & 0x7ff;
    saradc_vref_real = (float)(((float)value_vref/1000.0f));
    saradc_oe = ((float)((float)offset - 128.0f)/4096.0f);
    saradc_ge = ((float)((float)gain -256.0f)/4096.0f);

    printk("SARADC vref_real:%d, oe:%d, ge:%d", (int)(saradc_vref_real*1000), (int32_t)((float)saradc_oe*10000.0f), (int32_t)((float)saradc_ge*10000.0f));
    // printk("saradc flag:0x%x, saradc:0x%x, offset:%x, gain:%x\r\n", flag, temp_value, offset, gain);
    return HAL_ADC_STATUS_OK;
}

/**
 * @brief Enable the SAR ADC.
 *
 * This function turns on the Successive Approximation Register (SAR) ADC module, making it ready to perform analog-to-digital
 * conversions. It is typically a prerequisite step before configuring modes or performing any conversion readings.
 *
 * @return The status of the enable operation, returned as a value of type 'hal_adc_status_t'. Possible return values may include:
 *         - HAL_ADC_STATUS_OK: SAR ADC enabled successfully.
 */
hal_adc_status_t hal_saradc_enable()
{
    if (HAL_CLOCK_STATUS_OK != hal_clock_enable(HAL_CLOCK_CG_AUXADC)) {
        //log_hal_msgid_error("[ADC] Clock enable failed!", 0);
        return HAL_ADC_STATUS_ERROR;
    }
    /* Enable ADC analog power */
    ADC->MACRO_CON2_UNION.MACRO_CON2 |= MACRO_CON2_RG_AUXADC_LDO_EN_MASK;
    hal_gpt_delay_us(50);
    ADC->ANA_EN_CON_UNION.ANA_EN_CON = 0x101;
    hal_gpt_delay_us(50);
    *((volatile uint32_t *)(0x42080084)) = 0x121;
    return HAL_ADC_STATUS_OK;
}

/**
 * @brief Disable the SAR ADC.
 *
 * This function turns off the Successive Approximation Register (SAR) ADC module, stopping any ongoing conversions and
 * reducing power consumption. It is typically called when the ADC is no longer needed to free resources and optimize system performance.
 *
 * @return The status of the disable operation, returned as a value of type 'hal_adc_status_t'. Possible return values may include:
 *         - HAL_ADC_STATUS_OK: SAR ADC disabled successfully.
 */
hal_adc_status_t hal_saradc_disable()
{
    /* Disable AUXADC */
    ADC->ANA_EN_CON_UNION.ANA_EN_CON = 0;
    /* Disable VA28_LDO */
    ADC->MACRO_CON2_UNION.MACRO_CON2 = 0;
    if (HAL_CLOCK_STATUS_OK != hal_clock_disable(HAL_CLOCK_CG_AUXADC)) {
        //log_hal_msgid_error("[ADC] Clock disable failed!", 0);
        return HAL_ADC_STATUS_ERROR;
    }
    return HAL_ADC_STATUS_OK;
}

/**
 * @brief Configure the GPIO mode for specified ADC channels.
 *
 * This function sets the mode of specific GPIO pins associated with the SAR ADC based on the provided channel mask.
 * The GPIO pins can be configured for either digital or analog input, depending on the application requirements.
 *
 * @param channel_mask A bitmask specifying which ADC channels' GPIO modes are to be set. Each bit represents a channel.
 *                     For example, if you want to configure channels 0 and 2, the mask would be 0b0101.
 * @param mode Specifies the desired mode for the GPIO. The available options are:
 *        - HAL_SARADC_GPIO_DIGITAL_MODE: Configure the GPIO for digital operation.
 *        - HAL_SARADC_GPIO_ANALOG_MODE: Configure the GPIO for analog operation.
 *
 * @return The status of the GPIO mode configuration operation, returned as a value of type 'hal_adc_status_t'.
 *         Possible return values may include:
 *         - HAL_ADC_STATUS_OK: GPIO mode set successfully.
 */
hal_adc_status_t hal_saradc_set_gpio_mode(uint32_t channel_mask, hal_saradc_gpio_mode_t mode)
{
    uint32_t temp = 0;
    for (uint8_t ch = 0; ch < HAL_SARADC_CHANNEL_GPIO_MAX; ch++) {
        if (channel_mask & (1 << ch)) {
            if (ch <= 11) {
                temp = ch + 26;
            } else {
                temp = ch + 28;
            }
            if (mode == HAL_SARADC_GPIO_ANALOG_MODE) {
                hal_gpio_set_analog_mode(temp);
            } else {
                hal_gpio_clear_analog_mode(temp);
            }
        }
    }
    return HAL_ADC_STATUS_OK;
}

/**
 * @brief Retrieve ADC data immediately from the specified SAR ADC channels.
 *
 * This function reads and retrieves the most recent raw ADC data directly from the selected SAR ADC channels. The data is
 * stored in the provided structure, where it contains both the channel mask and corresponding channel data.
 *
 * @param[out] saradc_data Pointer to a 'hal_saradc_data_t' structure. The structure will be populated with:
 *        - 'channel_mask': A bitmask representing which ADC channels have the data available.
 *        - 'channel_data': An array containing the raw ADC values for each channel, indexed by channel number.
 *                          Unused entries are undefined if the corresponding channel is not set in the mask.
 *
 * @return The status of the get-data operation, returned as a value of type 'hal_adc_status_t'. Possible return values include:
 *         - HAL_ADC_STATUS_OK: Data retrieved successfully.
 */
hal_adc_status_t hal_saradc_get_data_immediately(hal_saradc_data_t *saradc_data)
{
    ADC->AUXADC_CON1 = 0x0;// clear all channel
    ADC->AUXADC_CON1 = saradc_data->channel_mask;//trigger all channel
    while (ADC->AUXADC_CON3_UNION.AUXADC_CON3_CELLS.ADC_STAT & AUXADC_CON3_ADC_STA_MASK);
    for (uint8_t ch = 0; ch < 32; ch++) {
        if (saradc_data->channel_mask & (1 << ch)) {
            saradc_data->channel_data[ch] = ADC->AUXADC_DATA[ch];
        }
    }
    return HAL_ADC_STATUS_OK;
}

/**
 * @brief Get the averaged ADC data.
 *
 * This function retrieves the averaged data from the SAR ADC.
 *
 * @param[in] saradc_data  Pointer to a 'hal_saradc_data_t' structure where the ADC data will be stored.
 * @param[in] average_num  Average number of samples to compute, defined by 'hal_adc_average_t'.
 *
 * @return Returns a status code of type 'hal_adc_status_t' indicating the success or failure of the operation.
 *         Possible return values are:
 *         - HAL_ADC_STATUS_OK: Operation was successful and data is available.
 */
hal_adc_status_t hal_saradc_get_data_average(hal_saradc_data_t *saradc_data, hal_adc_average_t average_num)
{
    ADC->AUXADC_AVG_NUM = average_num;// Set average number
    ADC->AUXADC_CON1 = 0x0;// clear all channel
    for (uint8_t ch = 0; ch < 32; ch++) {
        if (saradc_data->channel_mask & (1 << ch)) {
            // ADC->AUXADC_CON1 = 0x0;// clear all channel
            ADC->AUXADC_CON4_UNION.AUXADC_CON4 |= (1 << 8);// Enable auto average
            ADC->AUXADC_CON1 = 0x1 << ch;// trigger channel
            while (ADC->AUXADC_AVG_READY == 0);
        }
    }
    for (uint8_t ch = 0; ch < 32; ch++) {
        if (saradc_data->channel_mask & (1 << ch)) {
            saradc_data->channel_data[ch] = ADC->AVG_DATA[ch] >> 3;
        }
    }
    return HAL_ADC_STATUS_OK;
}

/**
 * @brief Convert raw ADC data to calibrated voltage in millivolts (mV) for a specified measurement mode.
 *
 * This function utilizes calibration data to adjust the raw ADC readings and provides a calibrated voltage value
 * in millivolts for the given SAR ADC measurement mode.
 *
 * @param measure_mode Specifies the measurement mode being used. The available options are:
 *        - HAL_SARADC_MEASURE_SE_MODE: Single-ended measurement mode.
 *        - HAL_SARADC_MEASURE_DIV_MODE: Divided measurement mode.
 *        - HAL_SARADC_MEASURE_DIFF_MODE: Differential measurement mode.
 *
 * @param raw_data The raw ADC data obtained from the selected measurement mode.
 *
 * @param[out] cal_voltage_mV Pointer to a 'uint32_t' where the calibrated voltage in millivolts will be stored.
 *
 * @return The status of the voltage calibration operation, returned as a value of type 'hal_adc_status_t'. Possible return values may include:
 *         - HAL_ADC_STATUS_OK: Voltage calculated successfully.
 */
hal_adc_status_t hal_saradc_get_calibration_voltage_mV(hal_saradc_measure_mode_t measure_mode, uint32_t raw_data, uint32_t *cal_voltage_mV)
{
    float mV = 0;
    mV = (((float)(raw_data)/4096.0f) - saradc_oe) * (saradc_vref_real / (1.0f + saradc_ge));
    switch (measure_mode) {
        case (HAL_SARADC_MEASURE_SE_MODE):
            //SE mode
            *cal_voltage_mV = (uint32_t)(mV * 1000.0f);
            break;
        case (HAL_SARADC_MEASURE_DIV_MODE):
            //DIV mode
            *cal_voltage_mV = (uint32_t)((mV / 0.375f) * 1000.0f);
            break;
        case (HAL_SARADC_MEASURE_DIFF_MODE):
            //DIFF mode
            *cal_voltage_mV = (uint32_t)((mV - 0.7f) * 2000.0f);
            break;
        default:
            return HAL_ADC_STATUS_INVALID_PARAMETER;
            break;
    }
    return HAL_ADC_STATUS_OK;
}

/**
 * @brief Initialize the SAR ADC with specified data rate and measurement mode.
 *
 * This function sets up the Successive Approximation Register (SAR) ADC with the desired configuration parameters,
 * including both the data rate for conversions and the measurement mode. It prepares the ADC for subsequent operations.
 *
 * @param data_rate Specifies the data rate for the SAR ADC operation. The available options are:
 *        - HAL_SARADC_DATA_RATE_HS_MODE: High-speed mode
 *        - HAL_SARADC_DATA_RATE_LS_MODE: Low-speed mode
 *
 * @param measure_mode Specifies the measurement mode for the SAR ADC. The available options are:
 *        - HAL_SARADC_MEASURE_SE_MODE: Single-ended measurement mode
 *        - HAL_SARADC_MEASURE_DIV_MODE: Divided measurement mode
 *        - HAL_SARADC_MEASURE_DIFF_MODE: Differential measurement mode
 *
 * @return The status of the initialization operation, returned as a value of type 'hal_adc_status_t'. Possible return values may include:
 *         - HAL_ADC_STATUS_OK: Initialization successful.
 */
hal_adc_status_t hal_saradc_init(hal_saradc_data_rate_t data_rate, hal_saradc_measure_mode_t measure_mode)
{
    /* Read the calibration data */
    hal_saradc_read_calibration(measure_mode);
    /* Configure the SAR ADC's data rate and measurement mode */
    hal_saradc_set_mode(data_rate, measure_mode);
    hal_saradc_sdadc_common_setting_internal(true);
    /* CLK MUX selection */
    *((volatile uint32_t *)(0x420302A0)) = 0x0;
    /* ADC sampling selection */
    ADC->AUXADC_SPL_CON = 0x2;
    /* Bus clock switch to 32M */
    clock_mux_sel(CLK_SLOW_BUS_SEL, MUX_SLOW_BUS_IDX_XO);
    /* Enable the SARADC */
    hal_saradc_enable();
    //set debug clk out 32M OFF
    *((volatile uint32_t *)(0x42010108)) = 0x3;
    /* ACD function mode selection */
    ADC->ACD_FUNC_MODE_CTL = 0x1;
    /* SOFT RESET */
    ADC->AUXADC_CON3_UNION.AUXADC_CON3 = 0x100;
    ADC->AUXADC_CON3_UNION.AUXADC_CON3 = 0x0;
    return HAL_ADC_STATUS_OK;
}

/**
 * @brief Deinitialize the SAR ADC.
 *
 * This function disables and resets the Successive Approximation Register (SAR) ADC module, releasing any resources
 * that were allocated during initialization. It is typically used when the ADC is no longer needed to ensure optimal
 * power usage and system performance.
 *
 * @return The status of the deinitialization operation, returned as a value of type 'hal_adc_status_t'. Possible return values may include:
 *         - HAL_ADC_STATUS_OK: Deinitialization successful.
 */
hal_adc_status_t hal_saradc_deinit()
{
    clock_mux_sel(CLK_SLOW_BUS_SEL, MUX_SLOW_BUS_IDX_OSC_26M);
    hal_saradc_sdadc_common_setting_internal(false);
    hal_saradc_disable();
    return HAL_ADC_STATUS_OK;
}

#ifdef HAL_SLEEP_MANAGER_ENABLED
/**
 * @brief Backup ADC-related registers.
 *
 * This function saves the current state of ADC-related hardware registers.
 */
void adc_backup_all_register(void)
{
    g_saradc_backup_restore_rg.MACRO_CON2 = ADC->MACRO_CON2_UNION.MACRO_CON2;
    g_saradc_backup_restore_rg.ANA_EN_CON = ADC->ANA_EN_CON_UNION.ANA_EN_CON;
    g_saradc_backup_restore_rg.ACD_FUNC_MODE_CTL = ADC->ACD_FUNC_MODE_CTL;
    g_saradc_backup_restore_rg.AUXADC_SPL_CON = ADC->AUXADC_SPL_CON;
    g_saradc_backup_restore_rg.AUXADC_DIV_CON = ADC->AUXADC_DIV_CON;
}
/**
 * @brief Restore ADC-related registers from backup.
 *
 * This function restores the state of ADC-related hardware registers from a previously saved backup.
 */
void adc_restore_all_register(void)
{
    ADC->MACRO_CON2_UNION.MACRO_CON2 = g_saradc_backup_restore_rg.MACRO_CON2;
    ADC->ANA_EN_CON_UNION.ANA_EN_CON = g_saradc_backup_restore_rg.ANA_EN_CON;
    ADC->ACD_FUNC_MODE_CTL = g_saradc_backup_restore_rg.ACD_FUNC_MODE_CTL;
    ADC->AUXADC_SPL_CON = g_saradc_backup_restore_rg.AUXADC_SPL_CON;
    ADC->AUXADC_DIV_CON = g_saradc_backup_restore_rg.AUXADC_DIV_CON;
    if (saradc_sdadc_common_use_count != 0) {
        /* BG enable */
        *((volatile uint32_t *)(0x42080048)) = 0x4401;
        /* VREF switch1 enable */
        *((volatile uint32_t *)(0x4208004C)) = 0x70F;
        /* VREF switch2 enable */
        *((volatile uint32_t *)(0x42080050)) = 0x40F;
        /* GLB enable */
        *((volatile uint32_t *)(0x4208005C)) = 0x41;
    }
}
#endif

#ifdef HAL_ADC_CALIBRATION_ENABLE
/**
 * @brief Convert raw ADC data to calibrated data using pre-defined calibration settings.
 *
 * This function applies calibration adjustments to the given raw ADC data and provides the corrected (calibrated) data.
 *
 * @param raw_data The raw ADC data obtained from an ADC read operation.
 *
 * @param[out] cal_data Pointer to a 'uint32_t' where the calibrated ADC data will be stored. The caller must ensure
 *                      this pointer is valid before calling the function.
 *
 * @return The status of the calibration operation, returned as a value of type 'hal_adc_status_t'. Possible return values include:
 *         - HAL_ADC_STATUS_OK: Calibration successful.
 */
hal_adc_status_t hal_adc_get_calibration_data(uint32_t raw_data, uint32_t  *cal_data)
{
    if (NULL == cal_data) {
        return HAL_ADC_STATUS_INVALID_PARAMETER;
    }
    *cal_data = (((float)(raw_data)/4096.0f) - saradc_oe) * (saradc_vref_real / (1.0f + saradc_ge)) / saradc_vref_real * 4096.0f;
    return HAL_ADC_STATUS_OK;
}

/**
 * @brief Convert raw ADC data to a calibrated voltage value.
 *
 * This function adjusts the provided raw ADC data using calibration constants to produce a calibrated voltage value.
 *
 * @param raw_data The raw ADC data obtained from an ADC conversion process.
 *
 * @param[out] cal_voltage Pointer to a 'uint32_t' where the calibrated voltage will be stored. This pointer must be valid, and
 *                         the memory should be allocated by the caller prior to invoking the function.
 *
 * @return The status of the voltage calibration operation, returned as a value of type 'hal_adc_status_t'. Possible return values include:
 *         - HAL_ADC_STATUS_OK: Voltage calibration successful.
 */
hal_adc_status_t hal_adc_get_calibration_voltage(uint32_t raw_data, uint32_t *cal_voltage)
{
    if (NULL == cal_voltage) {
        return HAL_ADC_STATUS_INVALID_PARAMETER;
    }

    /* unit is mv */
    hal_saradc_get_calibration_voltage_mV(HAL_SARADC_MEASURE_DIV_MODE, raw_data, cal_voltage);
    return HAL_ADC_STATUS_OK;
}

/**
 * @brief Convert calibrated voltage (mV) to raw ADC data (reverse of hal_saradc_get_calibration_voltage_mV()).
 *
 * @param measure_mode Specifies the measurement mode being used.
 * @param cal_voltage_mV Calibrated voltage in millivolts (mV).
 * @param[out] raw_data Pointer to a 'uint32_t' where the raw ADC data will be stored.
 *
 * @return hal_adc_status_t
 *         - HAL_ADC_STATUS_OK: Conversion successful.
 *         - HAL_ADC_STATUS_INVALID_PARAMETER: raw_data is NULL or measure_mode invalid.
 */
hal_adc_status_t hal_adc_get_raw_data_by_calibration_voltage(hal_saradc_measure_mode_t measure_mode,
                                                             uint32_t cal_voltage_mV,
                                                             uint32_t *raw_data)
{
    float mV = 0.0f;
    float raw_f = 0.0f;

    if (raw_data == NULL) {
        return HAL_ADC_STATUS_INVALID_PARAMETER;
    }

    /* Convert mV back to internal voltage (the 'mV' variable in hal_saradc_get_calibration_voltage_mV is in volts). */
    switch (measure_mode) {
        case (HAL_SARADC_MEASURE_SE_MODE):
            /* cal_voltage_mV = mV * 1000 */
            mV = ((float)cal_voltage_mV) / 1000.0f;
            break;

        case (HAL_SARADC_MEASURE_DIV_MODE):
            /* cal_voltage_mV = (mV / 0.375) * 1000  =>  mV = cal_voltage_mV * 0.375 / 1000 */
            mV = (((float)cal_voltage_mV) * 0.375f) / 1000.0f;
            break;

        case (HAL_SARADC_MEASURE_DIFF_MODE):
            /* cal_voltage_mV = (mV - 0.7) * 2000  =>  mV = cal_voltage_mV / 2000 + 0.7 */
            mV = (((float)cal_voltage_mV) / 2000.0f) + 0.7f;
            break;

        default:
            return HAL_ADC_STATUS_INVALID_PARAMETER;
    }

    /* Reverse of:
     * mV = ((raw/4096) - oe) * (vref_real / (1 + ge))
     * => raw = 4096 * (oe + mV * (1 + ge) / vref_real)
     */
    raw_f = 4096.0f * (saradc_oe + (mV * (1.0f + saradc_ge) / saradc_vref_real));
    *raw_data = (uint32_t)(raw_f + 0.5f);

    return HAL_ADC_STATUS_OK;
}

#endif /* HAL_ADC_CALIBRATION_ENABLE */

#ifdef ADC_DEBUG_LOG
/**
 * @brief Dump the current values of all ADC-related registers for debugging purposes.
 *
 * This function outputs or logs the current state of all hardware registers associated with the ADC module. It is typically
 * used for debugging and diagnostic purposes to analyze register states and verify configurations during development and testing.
 */
void    adc_dump_register()
{
    log_hal_warning("===================== ADC Dump(0x%x) =====================", ADC);
    log_hal_warning("AUXADC_CON1:(%x), AUXADC_CON3:(%x), AUXADC_CON4:(%x),\
                    MACRO_CON2:(%x), ANA_EN_CON:(%x), AUXADC_AVG_NUM:(%x)", \
                    ADC->AUXADC_CON1, ADC->AUXADC_CON3_UNION.AUXADC_CON3, ADC->AUXADC_CON4, \
                    ADC->MACRO_CON2, ADC->ANA_EN_CON, ADC->AUXADC_AVG_NUM);
}
#endif

#ifdef __cplusplus
}
#endif

#endif /* HAL_ADC_MODULE_ENABLED */

