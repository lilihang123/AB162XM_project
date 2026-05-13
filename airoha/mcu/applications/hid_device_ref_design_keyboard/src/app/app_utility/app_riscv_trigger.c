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
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
 * RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
 * TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>

#include "hid_common.h"
#include "app_scenario.h"
#include "app_riscv_trigger.h"

#if IS_ENABLED(CONFIG_AIR_HW_KEYSCAN)
#include "hal_hw_keyscan.h"
#endif

#if IS_ENABLED(CONFIG_AIR_SPIM)
#include "hal_spi_master.h"
#endif

#include "memory_attribute.h"
#include "hal_cross_core_config.h"

#define thisMODULE riscv_trig
#define thisMOD    "riscv_trig"

LOG_MODULE_REGISTER(thisMODULE);


/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
static void app_riscv_trigger___trigger_selector(bool triggered_by_bt);


/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/



/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/



/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
static bool app_riscv_trigger___evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state* event = (struct evt_app_state*)evt_header;

    switch(event->app_state)
    {
        case APP_STATE_DISCONNECTED:
        {
            app_riscv_trigger___trigger_selector(false);
        }
        break;

        case APP_STATE_CONNECT_PREPARING:
        {
            uint8_t curr_mode = app_scenario_get_scenario_type();
            if (HID_SCENARIO_USB_MODE == curr_mode ){
                app_riscv_trigger___trigger_selector(false);
            }
            else {
                app_riscv_trigger___trigger_selector(true);
#if IS_ENABLED(CONFIG_AIR_HW_KEYSCAN)
                app_scenario_config_bt_trigger_type(TRIGGER_TYPE_KEY_SCAN);
#elif IS_ENABLED(CONFIG_AIR_SPIM)
                app_scenario_config_bt_trigger_type(TRIGGER_TYPE_SPI);
#else
                #error "Please specify bt trigger type"
#endif
            }

            APP_LOGI(thisMOD,"app_riscv_trigger___evt_app_state  event->app_state = 0x%x, curr_mode = %d " , event->app_state, curr_mode );
        }
        break;

        default:
        break;
    }
    return AF_TRAVERSE_NEXT;
}


void app_riscv_trigger__init_peripheral(void)
{
#if IS_ENABLED(CONFIG_AIR_HW_KEYSCAN)
    #if defined(CONFIG_AIR_KEYBOARD_M607)
        /* init hw keyscan at RISC-V side */
    #else
        #error "Please implement deinit function of hw keyscan"
    #endif
#elif IS_ENABLED(CONFIG_AIR_SPIM)
    hal_spi_master_config_t spi_config;
    hal_spi_master_status_t spi_ret = 0;
    static ATTR_ALIGN(16) uint8_t spi_dummy_write_reg = 0x0;
    static ATTR_ALIGN(16) uint8_t spi_dummy_read_reg = 0xff;

    spi_config.bit_order = HAL_SPI_MASTER_MSB_FIRST;
    spi_config.slave_port = HAL_SPI_MASTER_SLAVE_0;
    spi_config.clock_frequency = 8000000;
    /* CPOL = 0 & CPHA = 0 */
    spi_config.phase = HAL_SPI_MASTER_CLOCK_PHASE0;
    spi_config.polarity = HAL_SPI_MASTER_CLOCK_POLARITY0;
    spi_ret = hal_spi_master_init(HAL_SPI_MASTER_0, &spi_config);

    if (HAL_SPI_MASTER_STATUS_OK != spi_ret) {
        LOG_INF(thisMOD" bt_hw_trigger_enable spi init failed, ret: %d.", spi_ret);
    }
    spi_ret = hal_spi_master_set_clear_data(HAL_SPI_MASTER_0,1,1,true);
    if (HAL_SPI_MASTER_STATUS_OK != spi_ret) {
        LOG_INF(thisMOD" hal_spi_master_set_clear_data failed, ret: %d.", spi_ret);
    }

    hal_spi_master_send_and_receive_config_t spim_cfg;
    spim_cfg.receive_length = 1;
    spim_cfg.send_length = 1;
    spim_cfg.send_data = &spi_dummy_write_reg;
    spim_cfg.receive_buffer = &spi_dummy_read_reg;
    spi_ret = hal_spi_master_send_and_receive_dma_advanced(HAL_SPI_MASTER_0, &spim_cfg, false);   //not start
    if (HAL_SPI_MASTER_STATUS_OK != spi_ret) {
        LOG_INF(thisMOD" hal_spi_master_send_and_receive_dma_advanced failed, ret: %d.", spi_ret);
    }
    spi_ret = hal_spi_enable_nvic_irq(HAL_SPI_MASTER_0, false);
    if (HAL_SPI_MASTER_STATUS_OK != spi_ret) {
        LOG_INF(thisMOD" hal_spi_enable_nvic_irq failed, ret: %d.", spi_ret);
    }
    spi_ret = hal_spi_master_set_bt_enable(HAL_SPI_MASTER_0, true);
    if (HAL_SPI_MASTER_STATUS_OK != spi_ret) {
        LOG_INF(thisMOD" hal_spi_master_set_bt_enable failed, ret: %d.", spi_ret);
    }
    LOG_INF(thisMOD" bt_hw_trigger_enable for AIR_KEYBOARD_M607.");
#else
    #error "Unknown peripheral trigger configuration"
#endif /* IS_ENABLED(CONFIG_AIR_SPIM) */

#if defined(CONFIG_AIR_KEYBOARD_M607)
    /* Because calling hal_spi_master_init on the RISC-V side returns 0,
     * but the clock of SPI master doesn't actually turn on, it can be properly
     * initialized with assistance from the MCU side.
     */
    {
        hal_spi_master_config_t communication_spi_config;
        hal_spi_master_status_t communication_spi_ret = 0;

        communication_spi_config.bit_order = HAL_SPI_MASTER_MSB_FIRST;
        communication_spi_config.slave_port = HAL_SPI_MASTER_SLAVE_0;
        communication_spi_config.clock_frequency = 8000000;
        /* CPOL = 0 & CPHA = 0 */
        communication_spi_config.phase = HAL_SPI_MASTER_CLOCK_PHASE0;
        communication_spi_config.polarity = HAL_SPI_MASTER_CLOCK_POLARITY0;
        communication_spi_ret = hal_spi_master_init(HAL_SPI_MASTER_1, &communication_spi_config);
        __ASSERT_NO_MSG((communication_spi_ret == HAL_SPI_MASTER_STATUS_OK));
    }
#endif
}


void app_riscv_trigger__deinit_peripheral(void)
{
#if IS_ENABLED(CONFIG_AIR_HW_KEYSCAN)
    #if defined(CONFIG_AIR_KEYBOARD_M607)
        /* deinit hw keyscan at RISC-V side */
    #else
        #error "Please implement deinit function of hw keyscan"
    #endif
#elif IS_ENABLED(CONFIG_AIR_SPIM)
    hal_spi_master_set_bt_enable(HAL_SPI_MASTER_0, false);
    hal_spi_master_deinit(HAL_SPI_MASTER_0);
#else
    #error "Unknown peripheral trigger configuration"
#endif /* IS_ENABLED(CONFIG_AIR_SPIM) */

#if defined(CONFIG_AIR_KEYBOARD_M607)
    hal_spi_master_deinit(HAL_SPI_MASTER_1);
#endif
}

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
void app_riscv_trigger___trigger_selector(bool triggered_by_bt)
{
    APP_LOGI(thisMOD, "app_riscv_trigger___trigger_selector  triggered_by_bt = 0x%x  " , triggered_by_bt);

    if (triggered_by_bt){
        app_riscv_trigger__init_peripheral();
        hid_common_set_hid_exp_flag(FLAG_BIT_SENSOR_READY);
    }
    else {
        app_riscv_trigger__deinit_peripheral();
        hid_common_clear_hid_exp_flag(FLAG_BIT_SENSOR_READY);
    }
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/




/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_app_state, app_riscv_trigger___evt_app_state);

/*=============================================================================*/

