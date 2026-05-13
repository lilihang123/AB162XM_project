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

#ifdef AIR_BTD_IC_PREMIUM_G1

#include "race_cmd_feature.h"
#include "race_cmd.h"
// #include "race_lpcomm_trans.h"
// #include "race_lpcomm_util.h"
// #include "race_lpcomm_msg_struct.h"
// #include "race_lpcomm_conn.h"
#include "race_noti.h"
// #include "race_lpcomm_ps_noti.h"

#include "race_cmd_i2c_master.h"
#include "hal.h"
#include "race_xport.h"
#include "memory_attribute.h"

#ifdef RACE_I2C_MASTER_CMD_ENABLE
////////////////////////////////////////////////////////////////////////////////
// Constant Definitions ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// TYPE DEFINITIONS ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Global Variables ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// FUNCTION DECLARATIONS ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define RACE_I2C_MASTER_SEND_MAX_LEN    50
#define RACE_I2C_MASTER_RECEIVE_MAX_LEN 50
// #define RACE_I2C_DEBUG_LOG_ENABLE
// #ifdef RACE_I2C_DEBUG_LOG_ENABLE
//     #define LOG_INF(fmt,cnt,arg...) RACE_LOG_MSGID_I(fmt,cnt,##arg)
// #else
//     #define LOG_INF(fmt,cnt,arg...)
// #endif

static struct k_sem g_race_i2c_master_semaphore;
// static SemaphoreHandle_t g_race_i2c_master_semaphore = NULL;
static volatile uint32_t g_race_i2c_master_err_flag = 0;

static ATTR_ZIDATA_IN_NONCACHED_RAM_16BYTE_ALIGN uint8_t send_buffer[RACE_I2C_MASTER_SEND_MAX_LEN];
static ATTR_ZIDATA_IN_NONCACHED_RAM_16BYTE_ALIGN uint8_t receive_buff[RACE_I2C_MASTER_RECEIVE_MAX_LEN];


void race_i2c_master_callback(uint8_t slave_address, hal_i2c_callback_event_t event, void *user_data)
{
    // long xHigherPriorityTaskWoken = 0;
    if (HAL_I2C_EVENT_SUCCESS == event) {
        LOG_INF("Race I2C master send done");
        g_race_i2c_master_err_flag = 0;

    } else if (HAL_I2C_EVENT_NACK_ERROR == event) {
        LOG_INF("Race I2C master HAL_I2C_EVENT_NACK_ERROR ERROR!!!");
        g_race_i2c_master_err_flag = 1;
    } else if (HAL_I2C_EVENT_TIMEOUT_ERROR == event) {
        LOG_INF("Race I2C master HAL_I2C_EVENT_TIMEOUT_ERROR ERROR!!!");
        g_race_i2c_master_err_flag = 1;
    } else if (HAL_I2C_EVENT_ACK_ERROR == event) {
        // Error handler;
        LOG_INF("Race I2C master HAL_I2C_EVENT_ACK_ERROR ERROR!!!");
        g_race_i2c_master_err_flag = 1;
    }
    k_sem_give(&g_race_i2c_master_semaphore);
    // xSemaphoreGiveFromISR(g_race_i2c_master_semaphore, &xHigherPriorityTaskWoken);
}


void *i2c_master_send_and_receive(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    uint32_t i;
    typedef struct { // for import parameter
        RACE_COMMON_HDR_STRU Hdr;
        uint8_t i2c_master_port;
        hal_i2c_config_t i2c_config;
        uint8_t slave_address;                     /**<  The slave device address. */
        uint32_t receive_packet_length;            /**<  The receive packet length. */
        uint32_t receive_bytes_in_one_packet;      /**<  The number of bytes in one packet. */
        uint32_t send_packet_length;               /**<  The send packet length. */
        uint32_t send_bytes_in_one_packet;         /**<  The number of bytes in one packet. */
        uint8_t send_data[0];
    } PACKED *PTR_THIS_RACE_CMD_STRU;
    PTR_THIS_RACE_CMD_STRU pThisCmd = (PTR_THIS_RACE_CMD_STRU)pCmdMsg;

    typedef struct {// for export parameter
        uint8_t  status;
        uint8_t receive_data[RACE_I2C_MASTER_RECEIVE_MAX_LEN];
    } PACKED RSP;
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_CMD_I2C_MASTER_SEND_AND_RECEIVE,
                                      pThisCmd->receive_bytes_in_one_packet * pThisCmd->receive_packet_length + 1,
                                      channel_id);

    uint32_t send_total = pThisCmd->send_bytes_in_one_packet * pThisCmd->send_packet_length;
    uint32_t receive_total = pThisCmd->receive_bytes_in_one_packet * pThisCmd->receive_packet_length;
    if ((receive_total >= RACE_I2C_MASTER_RECEIVE_MAX_LEN) ||
        (send_total >= RACE_I2C_MASTER_SEND_MAX_LEN)) {
        LOG_INF("Race I2C master parameter check error,len too long!!");
        return (void *)pEvt;
    }
    g_race_i2c_master_err_flag = 0;
    if (pEvt) {
        if (pThisCmd->i2c_master_port > 0xF) {
            LOG_INF("race_cmdhdl_i2c_master_send_to_receive: i2c master port:%d, slave addr:0x%x, Rx %d bytes in one packet, Tx %d bytes in one packet",
                            (pThisCmd->i2c_master_port & 0xF),
                            pThisCmd->slave_address,
                            pThisCmd->receive_bytes_in_one_packet,
                            pThisCmd->send_bytes_in_one_packet);
            hal_i2c_send_to_receive_config_t i2c_send_to_receive_config;
            i2c_send_to_receive_config.slave_address = pThisCmd->slave_address;
            i2c_send_to_receive_config.send_data = send_buffer;
            i2c_send_to_receive_config.send_length = pThisCmd->send_bytes_in_one_packet;
            i2c_send_to_receive_config.receive_buffer = receive_buff;
            i2c_send_to_receive_config.receive_length = pThisCmd->receive_bytes_in_one_packet;
            hal_i2c_status_t status;
            status = hal_i2c_master_send_to_receive_polling((pThisCmd->i2c_master_port & 0xF), &i2c_send_to_receive_config);
            if (HAL_I2C_STATUS_OK != status) {
                // Error handler;
                pEvt->status = status;//
                LOG_INF("Race I2C master send to receive poll error!!!status:%d", status);
                return (void *)pEvt;
            }
            for (i = 0; i < pThisCmd->receive_bytes_in_one_packet; i++) {
                    pEvt->receive_data[i] = receive_buff[i];
                    LOG_INF("Race I2C master receive data:0x%x", (uint8_t)receive_buff[i]);
                }
                pEvt->status = 0;
                LOG_INF("Race I2C master send to receive poll success");
        } else {
            // if (g_race_i2c_master_semaphore == NULL) {
            //     g_race_i2c_master_semaphore = xSemaphoreCreateBinary();
            // }
            // if (g_race_i2c_master_semaphore == NULL) {
            //     assert(0);
            // }
            if(k_sem_init(&g_race_i2c_master_semaphore,0,1) != 0 ){
                assert(0);
            }
            hal_i2c_send_to_receive_config_ex_no_busy_t i2c_send_to_receive_config_no_busy_ex;
            LOG_INF("race_cmdhdl_i2c_master_send_and_receive: i2c master port:%d,clock freq:%d,slave addr:%d,Rx packet len:%d,Rx %d bytes in one packet,Tx packet len:%d,Tx %d bytes in one packet",
                            pThisCmd->i2c_master_port,
                            pThisCmd->i2c_config.frequency,
                            pThisCmd->slave_address,
                            pThisCmd->receive_packet_length,
                            pThisCmd->receive_bytes_in_one_packet,
                            pThisCmd->send_packet_length,
                            pThisCmd->send_bytes_in_one_packet);

            i2c_send_to_receive_config_no_busy_ex.i2c_config.frequency = pThisCmd->i2c_config.frequency;
            i2c_send_to_receive_config_no_busy_ex.i2c_send_to_receive_config_ex.slave_address = pThisCmd->slave_address;
            i2c_send_to_receive_config_no_busy_ex.i2c_send_to_receive_config_ex.receive_packet_length = pThisCmd->receive_packet_length;
            i2c_send_to_receive_config_no_busy_ex.i2c_send_to_receive_config_ex.receive_bytes_in_one_packet = pThisCmd->receive_bytes_in_one_packet;
            i2c_send_to_receive_config_no_busy_ex.i2c_send_to_receive_config_ex.send_packet_length = pThisCmd->send_packet_length;
            i2c_send_to_receive_config_no_busy_ex.i2c_send_to_receive_config_ex.send_bytes_in_one_packet = pThisCmd->send_bytes_in_one_packet;

            i2c_send_to_receive_config_no_busy_ex.i2c_send_to_receive_config_ex.receive_buffer = receive_buff;
            i2c_send_to_receive_config_no_busy_ex.i2c_send_to_receive_config_ex.send_data = send_buffer;
            i2c_send_to_receive_config_no_busy_ex.i2c_callback = race_i2c_master_callback;
            i2c_send_to_receive_config_no_busy_ex.user_data = NULL;

        /* Copy send data to the send buffer */
        memcpy(send_buffer, pThisCmd->send_data, send_total);

            hal_i2c_status_t status;
            // Send and receive data simultaneously.
            status = hal_i2c_master_send_to_receive_dma_ex_none_blocking(pThisCmd->i2c_master_port, &i2c_send_to_receive_config_no_busy_ex);
            if (HAL_I2C_STATUS_OK != status) {
                // Error handler;
                pEvt->status = status;//
                LOG_INF("Race I2C master send and receive error!!!status:%d", status);
                return (void *)pEvt;
            }
            LOG_INF("Race I2C master waiting for send and receive done~~~");
            // if (xSemaphoreTake(g_race_i2c_master_semaphore, portMAX_DELAY) == 1) {
            if (k_sem_take(&g_race_i2c_master_semaphore, K_FOREVER) == 0) {
                if (g_race_i2c_master_err_flag == 1) {
                    pEvt->status = 1;//
                    LOG_INF("Race I2C master send and receive fail!!!g_race_i2c_master_err_flag = 1");
                    return (void *)pEvt;

                }
            for (i = 0; i < receive_total; i++) {
                    pEvt->receive_data[i] = receive_buff[i];
                    LOG_INF("Race I2C master receive data:0x%x", (uint8_t)receive_buff[i]);
                }
                pEvt->status = 0;
                LOG_INF("Race I2C master send and receive success");
            } else {
                pEvt->status = 1;//
                LOG_INF("Race I2C master send and receive fail!!!");
            }
        }
    }
    return (void *)pEvt;
}

#define RACE_I2C_MASTER_HQA_SEND_MAX_LEN    50
ATTR_RWDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN uint8_t hqa_send_data[RACE_I2C_MASTER_HQA_SEND_MAX_LEN] = {0x5A};

void i2c_master_callback(uint8_t slave_address, hal_i2c_callback_event_t event, void *user_data)
{
    LOG_INF("race I2C master enter callback");
    if(HAL_I2C_EVENT_ACK_ERROR == event) {
        //ACK error handler;
    } else if(HAL_I2C_EVENT_NACK_ERROR == event) {
        //NACK error handler;
    } else if(HAL_I2C_EVENT_TIMEOUT_ERROR == event) {
        // Timeout handler;
    } else if(HAL_I2C_EVENT_SUCCESS == event) {
        LOG_INF("race I2C master send done");
        hal_i2c_master_send_dma(0, 0, hqa_send_data, RACE_I2C_MASTER_HQA_SEND_MAX_LEN);
    }
}


void *i2c_master_send_hqa(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    uint32_t user_data;
    typedef struct { // for import parameter
        RACE_COMMON_HDR_STRU Hdr;
        uint8_t i2c_master_port;
    } PACKED *PTR_THIS_RACE_CMD_STRU;
    PTR_THIS_RACE_CMD_STRU pThisCmd = (PTR_THIS_RACE_CMD_STRU)pCmdMsg;

    typedef struct {// for export parameter
        uint8_t  status;
    } PACKED RSP;

    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_CMD_I2C_MASTER_SEND,
                                      sizeof(RSP),
                                      channel_id);

    if (pEvt) {
        if(k_sem_init(&g_race_i2c_master_semaphore,0,1) != 0 ){
            assert(0);
        }

        hal_i2c_config_t i2c_config;
        i2c_config.frequency = HAL_I2C_FREQUENCY_2M8;  //3.25M

        // hal_pinmux_set_function(34, 7);    //I2C0_SCL
        // hal_pinmux_set_function(35, 7);    //I2C0_SDA
        // hal_gpio_pull_up(34);
        // hal_gpio_pull_up(35);
        // hal_gpio_set_capacitance(34, HAL_GPIO_CAPACITANCE_3);
        // hal_gpio_set_capacitance(35, HAL_GPIO_CAPACITANCE_3);
        // hal_gpio_set_slew_rate(34);
        // hal_gpio_set_slew_rate(35);

        LOG_INF("race I2C pinmux config done!!");

        memset(hqa_send_data, 0xAA, RACE_I2C_MASTER_HQA_SEND_MAX_LEN);

        hal_i2c_master_init(pThisCmd->i2c_master_port, &i2c_config);
        hal_i2c_master_register_callback(pThisCmd->i2c_master_port, i2c_master_callback, (void *) &user_data);
        LOG_INF("race I2C init done!!");
        LOG_INF("race I2C dma send data start!!");
        hal_i2c_master_send_dma(pThisCmd->i2c_master_port, 0, hqa_send_data, RACE_I2C_MASTER_HQA_SEND_MAX_LEN);

    }

    return pEvt;
}


void *RACE_CmdHandler_i2c_master_send_and_receive(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    LOG_INF("RACE_CmdHandler_i2c_master_send_and_receive pCmdMsg->hdr.id = %d",(int)pCmdMsg->hdr.id);

    switch (pCmdMsg->hdr.id) {
        case RACE_CMD_I2C_MASTER_SEND_AND_RECEIVE: { //0x5008
            return i2c_master_send_and_receive((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);
        }
        break;

        case RACE_CMD_I2C_MASTER_SEND: { //0x5009
            LOG_INF("race I2C HQA start");
            return i2c_master_send_hqa((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);
        }
        break;

        default:
            break;
    }

    return NULL;
}

#endif
#endif
