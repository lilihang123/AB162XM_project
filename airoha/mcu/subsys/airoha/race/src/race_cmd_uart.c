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
#ifdef AIR_BTD_IC_PREMIUM_G1
#include "race_cmd_feature.h"
#include "race_cmd.h"
#include "race_xport.h"
#include "race_util.h"

#ifdef RACE_UART_CMD_ENABLE
#include "race_cmd_uart.h"
#include "hal_uart.h"
#include "hal_uart_internal.h"
#include "hal.h"
#include "mux.h"

extern bool g_uart_disable_irq[];

hal_uart_port_t uart_port;

#ifdef RACE_UART_HQA
#define UART_VFIFO_SIZE  2048
#define UART_USER_BUFFER_SIZE  1024
ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN static uint8_t g_rx_vfifo_buffer[UART_VFIFO_SIZE];
ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN static uint8_t g_tx_vfifo_buffer[UART_VFIFO_SIZE];

uint8_t rcv_buffer[UART_USER_BUFFER_SIZE] = {0x55};
uint8_t send_buffer[UART_USER_BUFFER_SIZE] = {0x55};

void race_uart_dma_callback(hal_uart_callback_event_t status, void *user_data)
{
    if (status == HAL_UART_EVENT_READY_TO_WRITE) {
        LOG_INF("race irq occured: ready to write!!");
    } else if (status == HAL_UART_EVENT_READY_TO_READ) {
        LOG_INF("race irq occured: ready to read!!");
        hal_uart_receive_dma(uart_port, rcv_buffer, 512);
    } else if (status == HAL_UART_EVENT_TRANSMISSION_DONE) {
        LOG_INF("race irq occured: TRANSMISSION_DONE!!");
        hal_uart_send_dma(uart_port, send_buffer, 512);
    }

}

void *uart_send_data(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t  uart_port;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    uint32_t i = 0;
    hal_uart_config_t uart_config;
    hal_uart_dma_config_t dma_config;

    // uint32_t actual_baudrate;
    // UART_REGISTER_T *uartx;

    CMD *pCmd = (CMD *)pCmdMsg;
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_UART_CMD_SET,
                                      sizeof(RSP),
                                      channel_id);

    if (pEvt != NULL) {
        for(i=0; i<UART_USER_BUFFER_SIZE; i++) {
            send_buffer[i] = 0x55;
        }

        uart_port = (hal_uart_port_t)pCmd->uart_port;

        g_uart_disable_irq[uart_port] = false;

        uart_config.baudrate    = HAL_UART_BAUDRATE_3000000;
        uart_config.parity      = HAL_UART_PARITY_NONE;
        uart_config.stop_bit    = HAL_UART_STOP_BIT_1;
        uart_config.word_length = HAL_UART_WORD_LENGTH_8;
        dma_config.receive_vfifo_alert_size     = 20;
        dma_config.receive_vfifo_buffer         = g_rx_vfifo_buffer;
        dma_config.receive_vfifo_buffer_size    = UART_VFIFO_SIZE;
        dma_config.receive_vfifo_threshold_size = (UART_VFIFO_SIZE*4)/5;
        dma_config.send_vfifo_buffer            = g_tx_vfifo_buffer;
        dma_config.send_vfifo_buffer_size       = UART_VFIFO_SIZE;
        dma_config.send_vfifo_threshold_size    = (UART_VFIFO_SIZE*1)/5;
        hal_uart_deinit(uart_port);
        hal_uart_init(uart_port, &uart_config);
        // uart_set_baudrate(uartx, actual_baudrate);
        hal_uart_set_dma(uart_port, &dma_config);
        hal_uart_register_callback(uart_port, race_uart_dma_callback, NULL);
        LOG_INF("race UART init done");
        LOG_INF("race UART dma send start");
        hal_uart_send_dma(uart_port, send_buffer, 512);
    }

    return pEvt;
}
#endif
extern void system_disable_all_log(void);
extern void system_disable_uart_to_save_power(void);
void *uart_race_deinit_cmd(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t  uart_port;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    CMD *pCmd = (CMD *)pCmdMsg;
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_UART_CMD_SET,
                                      sizeof(RSP),
                                      channel_id);

    if (pEvt != NULL) {
        uart_port = (hal_uart_port_t)pCmd->uart_port;
        system_disable_all_log();
        system_disable_uart_to_save_power();
        g_uart_disable_irq[uart_port] = false;
        hal_uart_deinit(uart_port);
        LOG_INF("race UART deinit done");
    }

    return pEvt;
}
void *RACE_CmdHandler_uart(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    (void)length;

    LOG_INF("RACE_CmdHandler_uart, type[0x%X], race_id[0x%X], channel_id[%d]",
                     pCmdMsg->hdr.type, pCmdMsg->hdr.id, channel_id);

    if (pCmdMsg->hdr.type == RACE_TYPE_COMMAND) {
        switch (pCmdMsg->hdr.id) {
#ifdef RACE_UART_HQA
            case RACE_UART_CMD_SET: //0x5020
                LOG_INF("race UART HQA start");
                return uart_send_data((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), channel_id);
                break;
#endif
            case RACE_UART_DEINIT_CMD: //0x5021
                LOG_INF("race UART deinit start");
                return uart_race_deinit_cmd((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), channel_id);
                break;
        }
    }

    return NULL;
}

#endif /* RACE_GPIO_CMD_ENABLE */
#elif defined (AIR_BTD_IC_MANDATORY_G1)

#include "race_cmd_feature.h"
#include "race_cmd.h"
#include "race_xport.h"
#include "race_util.h"

#ifdef RACE_UART_CMD_ENABLE
#include "race_cmd_uart.h"
#include "hal_uart.h"
#include "hal_uart_internal.h"
#include "hal.h"
#include "mux.h"

extern bool g_uart_disable_irq[];

hal_uart_port_t uart_port;

// #define RACE_UART_HQA

#ifdef RACE_UART_HQA
#define UART_VFIFO_SIZE  2048
#define UART_USER_BUFFER_SIZE  1024
ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN static uint8_t g_rx_vfifo_buffer[UART_VFIFO_SIZE];
ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN static uint8_t g_tx_vfifo_buffer[UART_VFIFO_SIZE];

uint8_t rcv_buffer[UART_USER_BUFFER_SIZE] = {0x55};
uint8_t send_buffer[UART_USER_BUFFER_SIZE] = {0x55};

void race_uart_dma_callback(hal_uart_callback_event_t status, void *user_data)
{
    if (status == HAL_UART_EVENT_READY_TO_WRITE) {
        // LOG_INF("race irq occured: ready to write!!");
        uart_send_pdma(uart_port, send_buffer, 512);
    } else if (status == HAL_UART_EVENT_READY_TO_READ) {
        // LOG_INF("race irq occured: ready to read!!");
        hal_uart_receive_polling(uart_port, rcv_buffer, 512);
    } else if (status == HAL_UART_EVENT_TRANSMISSION_DONE) {
        // LOG_INF("race irq occured: TRANSMISSION_DONE!!");
    }
}

void *uart_send_data_hqa(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t  uart_port;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    uint32_t i = 0;
    hal_uart_config_t uart_config;
    hal_uart_dma_config_t dma_config;

    // uint32_t actual_baudrate;
    // UART_REGISTER_T *uartx;

    CMD *pCmd = (CMD *)pCmdMsg;
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_UART_CMD_SET,
                                      sizeof(RSP),
                                      channel_id);

    if (pEvt != NULL) {
        for(i=0; i<UART_USER_BUFFER_SIZE; i++) {
            send_buffer[i] = 0x55;
        }

        uart_port = (hal_uart_port_t)pCmd->uart_port;

        g_uart_disable_irq[uart_port] = false;

        uart_config.baudrate    = HAL_UART_BAUDRATE_3000000;
        uart_config.parity      = HAL_UART_PARITY_NONE;
        uart_config.stop_bit    = HAL_UART_STOP_BIT_1;
        uart_config.word_length = HAL_UART_WORD_LENGTH_8;
        dma_config.receive_vfifo_alert_size     = 20;
        dma_config.receive_vfifo_buffer         = g_rx_vfifo_buffer;
        dma_config.receive_vfifo_buffer_size    = UART_VFIFO_SIZE;
        dma_config.receive_vfifo_threshold_size = (UART_VFIFO_SIZE*4)/5;
        hal_uart_deinit(uart_port);
        hal_uart_init(uart_port, &uart_config);
        // uart_set_baudrate(uartx, actual_baudrate);
        hal_uart_set_dma(uart_port, &dma_config);
        hal_uart_register_callback(uart_port, race_uart_dma_callback, NULL);
        LOG_INF("race UART init done");
        LOG_INF("race UART dma send start");
        uart_send_pdma(uart_port, send_buffer, 512);
    }

    return pEvt;
}
#endif
void *uart_race_deinit_cmd(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t  uart_port;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    CMD *pCmd = (CMD *)pCmdMsg;
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_UART_CMD_SET,
                                      sizeof(RSP),
                                      channel_id);

    if (pEvt != NULL) {
        uart_port = (hal_uart_port_t)pCmd->uart_port;
        g_uart_disable_irq[uart_port] = false;
        hal_uart_deinit(uart_port);
        LOG_INF("race UART deinit done");
    }

    return pEvt;
}
void *RACE_CmdHandler_uart(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    (void)length;

    LOG_INF("RACE_CmdHandler_uart, type[0x%X], race_id[0x%X], channel_id[%d]",
                     pCmdMsg->hdr.type, pCmdMsg->hdr.id, channel_id);

    if (pCmdMsg->hdr.type == RACE_TYPE_COMMAND) {
        switch (pCmdMsg->hdr.id) {
#ifdef RACE_UART_HQA
            case RACE_UART_CMD_SET: //0x5020
                LOG_INF("race UART HQA start");
                return uart_send_data_hqa((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), channel_id);
                break;
#endif
            case RACE_UART_DEINIT_CMD: //0x5021
                LOG_INF("race UART deinit start");
                return uart_race_deinit_cmd((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), channel_id);
                break;
        }
    }

    return NULL;
}

#endif /* RACE_GPIO_CMD_ENABLE */
#endif