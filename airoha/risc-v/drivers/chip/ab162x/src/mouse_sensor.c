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

#include "mouse_sensor.h"
#include "hal_spi_sensor.h"
#include "hal_cross_core_config.h"
#include "memory_attribute.h"
#include "hal_nvic.h"

#define SPI_PORT HAL_SPI_MASTER_0
#define MAX_BURST_SIZE 12
uint8_t workround_flag;
uint32_t is_lifted = 0;


ATTR_ALIGN(16) uint8_t burst_reg = 0x16;
static mouse_burst_data_t * mouse_burst_data = (mouse_burst_data_t *)CROSS_CORE_MEM_VARIABLE(spi_sensor);
int mouse_sensor_burst_read(uint8_t burst_size){
    // int ret;
    // if(burst_size > MAX_BURST_SIZE){
    //     return -8;
    // }
    if(mouse_burst_data->init_flag == false){
        return MOUSE_SENSOR_STATUS_NOT_INIT;
    }
    if(mouse_burst_data->burst_flag == 0){
        return MOUSE_SENSOR_STATUS_NOT_SET_BURST;
    }
    hal_spi_master_restore_address_advanced(SPI_PORT,&burst_reg,(uint8_t *)&(mouse_burst_data->reserved));
    hal_spi_master_trigger_start(SPI_PORT, true);  //trig start
    // if(mouse_burst_data->burst_flag == 0) {
        // uint8_t size = burst_size+1;
        // hal_spi_master_send_and_receive_config_t spi_send_and_receive_config;
        // spi_send_and_receive_config.receive_length = size;
        // spi_send_and_receive_config.send_length = 1;
        // spi_send_and_receive_config.send_data = &burst_reg;
        // spi_send_and_receive_config.receive_buffer = (uint8_t *)&(mouse_burst_data->reserved);
        // ret = hal_spi_master_send_and_receive_dma_advanced(SPI_PORT, &spi_send_and_receive_config,true);   //not start
        // if(ret != HAL_SPI_MASTER_STATUS_OK)
        // {
        //     return -ret;
        // }
        // hal_nvic_save_and_set_interrupt_mask(&mask);
        // mouse_burst_data->burst_flag = false;
        // hal_nvic_restore_interrupt_mask(mask);
    // }
    // else{
    //     hal_spi_master_trigger_start(SPI_PORT, true);  //trig start
    //     LOG_MSGID_I(sensor, "mouse_sensor_burst_read 3333",0);
    // }
    return MOUSE_SENSOR_STATUS_OK;
}
/* exception event not need message */
void CCNI_DEF_HANDLER(20)(hal_ccni_event_t event, hal_ccni_message_t *msg)
{
    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    workround_flag = 0;
    hal_nvic_restore_interrupt_mask(mask);
}
void mouse_sensor_send_report_to_CM33(hal_ccni_message_t* msg)
{
    hal_ccni_set_event(IRQGEN_RISCV2MCU_EVENT15, NULL);
}

int mouse_sensor_get_data(int16_t *data_x,int16_t *data_y){
    uint32_t mask;
    if(mouse_burst_data->init_flag == false){
        return MOUSE_SENSOR_STATUS_NOT_INIT;
    }

    is_lifted = mouse_burst_data->Motion_data & 0x08;

    if((mouse_burst_data->observation_data  != 0xB7)  && (mouse_burst_data->observation_data  != 0xBF) ){
        if(workround_flag == 0){
            hal_nvic_save_and_set_interrupt_mask(&mask);
            workround_flag = 1;
            hal_nvic_restore_interrupt_mask(mask);
            mouse_sensor_send_report_to_CM33(NULL);
        }
        return MOUSE_SENSOR_STATUS_READ_DATA_FAILED;
    }

    *data_x = (int16_t)(mouse_burst_data->x_low);
    *data_x |= (mouse_burst_data->x_high << 8);

    *data_y = (int16_t)(mouse_burst_data->y_low);
    *data_y |= (mouse_burst_data->y_high << 8);

    return MOUSE_SENSOR_STATUS_OK;
}

int mouse_sensor_register_callback(hal_spi_master_callback_t callback,void *user_data){
    return hal_spi_master_register_callback(SPI_PORT,callback,user_data);
}

int mouse_sensor_is_lifted()
{
    return is_lifted;
}