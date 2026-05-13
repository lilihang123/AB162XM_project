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
#ifdef AIR_BTD_IC_PREMIUM_G1
#include "race_cmd_feature.h"
#include "race_cmd.h"
#include "race_xport.h"
#include "race_util.h"

#ifdef RACE_CRYSTAL_TRIM_CMD_ENABLE

#define TRIM_TIME_MAX(x)  ((x)*1000)

#if defined(HAL_UART_MODULE_ENABLED)

#include "hal_gpt.h"
#include "hal_uart.h"
#include "hal_uart_internal.h"
#include "hal_wdt.h"
#include "hal_platform.h"
#include "race_cmd_crystal_trim.h"
#include "mux.h"
#include "hal.h"
// #include "log.h"
#include <zephyr/bluetooth/bluetooth.h>

extern hal_uart_status_t   hal_uart_ext_get_uart_config(hal_uart_port_t uart_port, hal_uart_config_t  *uart_config, hal_uart_dma_config_t *dma_config, uint32_t *callback);
extern bool                hal_uart_ext_is_dma_mode(hal_uart_port_t uart_port);
extern hal_uart_status_t   hal_uart_ext_set_baudrate(hal_uart_port_t uart_port, uint32_t baudrate);
extern void                mux_restore_callback();  //reset mux software pointer
extern mux_status_t        mux_control(mux_port_t port, mux_ctrl_cmd_t command, mux_ctrl_para_t *para);

// atci_status_t              atci_cmd_hdlr_crystal_trim(atci_parse_cmd_param_t *parse_cmd);

/* Private variable declare  */
static  volatile    bool    flg_timeout   = false;
static const  uint8_t       chr_pattern[] = {0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55};


bool  send_pattern_char(uint8_t port, uint32_t baudrate, uint32_t timeout_s)
{
    hal_uart_config_t  orig_uart_config = {0};
    hal_uart_dma_config_t orig_dma_config = {0};
    uint32_t orig_uart_callback = 0;

    uint32_t start_time, end_time, during_time;
    flg_timeout = false;
    LOG_INF("trim Port:%d,Baudrate:%d,timeout:%dms\r\n", (int)port, (int)baudrate, (int)timeout_s);

    if (hal_uart_ext_get_uart_config(port, &orig_uart_config, &orig_dma_config, &orig_uart_callback) != HAL_UART_STATUS_OK) {
        orig_uart_config.baudrate = HAL_UART_BAUDRATE_38400;
        orig_uart_config.parity   = HAL_UART_PARITY_NONE;
        orig_uart_config.stop_bit = HAL_UART_STOP_BIT_1;
        orig_uart_config.word_length = HAL_UART_WORD_LENGTH_8;
        LOG_INF("trim uart %d not initialized!", port);
        hal_uart_init(port, &orig_uart_config);
        hal_uart_ext_set_baudrate(port, baudrate);
        hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &start_time);
        while (flg_timeout == false) {
            hal_uart_send_polling(port, (const uint8_t *)chr_pattern, sizeof(chr_pattern));
            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &end_time);
            hal_gpt_get_duration_count(start_time, end_time, &during_time);
            if (during_time > TRIM_TIME_MAX(timeout_s)) {
                flg_timeout = true;
            }
        }
        hal_uart_deinit(port);
    } else {
        LOG_INF("trim uart %d initialized!", port);
        __disable_irq();
        if (hal_uart_ext_is_dma_mode(port) == true) {
            LOG_INF("trim uart %d in dma mode!", port);
            /*Set a signal frequency,Baud rate is twice the frequency*/
            mux_control((mux_port_t)port, MUX_CMD_CLEAN, NULL);
            hal_uart_ext_set_baudrate(port, baudrate);
            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &start_time);
            while (flg_timeout == false) {
                hal_uart_send_dma(port, (const uint8_t *)chr_pattern, sizeof(chr_pattern));
                hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &end_time);
                hal_gpt_get_duration_count(start_time, end_time, &during_time);
                if (during_time > TRIM_TIME_MAX(timeout_s)) {
                    flg_timeout = true;
                }
            }
        } else {
            LOG_INF("trim uart %d in fifo mode!", port);
            hal_uart_ext_set_baudrate(port, baudrate);
            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &start_time);
            while (flg_timeout == false) {
                hal_uart_send_polling(port, (const uint8_t *)chr_pattern, sizeof(chr_pattern));
                hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &end_time);
                hal_gpt_get_duration_count(start_time, end_time, &during_time);
                if (during_time > TRIM_TIME_MAX(timeout_s)) {
                    flg_timeout = true;
                }
            }
        }
        /*Set a signal frequency,Baud rate is twice the frequency*/
        mux_control((mux_port_t)port, MUX_CMD_CLEAN, NULL);
        hal_uart_deinit(port);
        hal_uart_init(port, &orig_uart_config);
        hal_uart_set_dma(port, &orig_dma_config);
        hal_uart_register_callback(port, (hal_uart_callback_t)orig_uart_callback, (void *)(intptr_t)port);
        hal_uart_set_software_flowcontrol(port, 0x11, 0x13, 0x77);
        mux_restore_callback(port);
        __enable_irq();

    }
    LOG_INF("start_time=%d end_time=%d,during_time=%d", start_time, end_time, during_time);

    return true;
}


void *RACE_CmdHandler_race_crystal_trim(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t port;
        uint32_t baudrate;
        uint16_t timeout_ms;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    CMD *pCmd = (CMD *)pCmdMsg;
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_CRYSTAL_TRIM_TRIGGER,
                                      sizeof(RSP),
                                      channel_id);

    // LOG_INF("uart port:%d baudrate:%d timeout_ms:%d",
    //                 pCmd->port,
    //                 pCmd->baudrate,
    //                 pCmd->timeout_ms);

    if (pEvt != NULL) {
        send_pattern_char(pCmd->port, pCmd->baudrate, pCmd->timeout_ms);
    }

    return pEvt;
}

void *RACE_CmdHandler_crystal_trim(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    (void)length;

    LOG_INF("RACE_CmdHandler_crystal_trim, type[0x%X], race_id[0x%X], channel_id[%d]",
                     pCmdMsg->hdr.type, pCmdMsg->hdr.id, channel_id);

    if (pCmdMsg->hdr.type == RACE_TYPE_COMMAND) {
        switch (pCmdMsg->hdr.id) {
            case RACE_CRYSTAL_TRIM_TRIGGER: //0x3076
            {
                #if defined (CONFIG_BT_PERIPHERAL)
                // workaround : stop ADV to avod command too late problem
                LOG_INF("RACE_CRYSTAL_TRIM_TRIGGER bt_le_adv_stop");
                bt_le_adv_stop();
                #endif

                return RACE_CmdHandler_race_crystal_trim((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), channel_id);
            }

            default:
                break;
        }
    }

    return NULL;
}

#endif   /* HAL_UART_MODULE_ENABLED */

#endif  /* RACE_CRYSTAL_TRIM_CMD_ENABLE */
#elif defined (AIR_BTD_IC_MANDATORY_G1)

#include "race_cmd_feature.h"
#include "race_cmd.h"
#include "race_xport.h"
#include "race_util.h"

#ifdef RACE_CRYSTAL_TRIM_CMD_ENABLE

#define TRIM_TIME_MAX(x)  ((x)*1000)

#if defined(HAL_UART_MODULE_ENABLED)

#include "hal_gpt.h"
#include "hal_uart.h"
#include "hal_uart_internal.h"
#include "hal_wdt.h"
#include "hal_platform.h"
#include "race_cmd_crystal_trim.h"
#include "mux.h"
#include "hal.h"
// #include "log.h"
extern void                mux_restore_callback();  //reset mux software pointer
extern mux_status_t        mux_control(mux_port_t port, mux_ctrl_cmd_t command, mux_ctrl_para_t *para);

// atci_status_t              atci_cmd_hdlr_crystal_trim(atci_parse_cmd_param_t *parse_cmd);

/* Private variable declare  */
static  volatile    bool    flg_timeout   = false;
// static const  uint8_t       chr_pattern[] = {0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55};
extern hal_uart_status_t uart_backup_register(hal_uart_port_t uart_port);
extern hal_uart_status_t uart_restore_register(hal_uart_port_t uart_port);

#ifdef UART_DEBUG
#include "hal_gpio.h"
static uint8_t  g_uart_response_buf[512];
static uint8_t ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN rx_vfifo_buffer[4];
static uint8_t ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN tx_vfifo_buffer[4];

uint32_t    dvt_cmd_send(uint8_t *pbuf, uint32_t size)
{
    uint32_t  txlen = 0;
    // printk("send length %d", size);
    while(1){
        if(txlen < size){
            txlen = hal_uart_send_polling(HAL_UART_1, pbuf, size);
        }else {
            break;
        }
    }
    return txlen;
}
#endif

bool  send_pattern_char(uint8_t port, uint32_t baudrate, uint32_t timeout_s)
{
    hal_uart_config_t  trim_uart_config = {0};
    // hal_uart_dma_config_t orig_dma_config = {0};
    // uint32_t orig_uart_callback = 0;

    uint32_t start_time, end_time, during_time;
    flg_timeout = false;
    printk("trim Port:%d,Baudrate:%d,timeout:%dms\r\n", (int)port, (int)baudrate, (int)timeout_s);
    uart_backup_register(port);
    if ( hal_uart_set_baudrate(port, HAL_UART_BAUDRATE_62500) != HAL_UART_STATUS_OK) {
        trim_uart_config.baudrate = HAL_UART_BAUDRATE_62500;
        trim_uart_config.parity   = HAL_UART_PARITY_NONE;
        trim_uart_config.stop_bit = HAL_UART_STOP_BIT_1;
        trim_uart_config.word_length = HAL_UART_WORD_LENGTH_8;
        printk("trim uart %d not initialized!", port);
        hal_uart_init(port, &trim_uart_config);
        hal_uart_set_baudrate(port, HAL_UART_BAUDRATE_62500);
        hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &start_time);
        while (flg_timeout == false) {
            hal_uart_TxXtalTrimMode(port, true);
            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &end_time);
            hal_gpt_get_duration_count(start_time, end_time, &during_time);
            if (during_time > TRIM_TIME_MAX(timeout_s)) {
                flg_timeout = true;
                hal_uart_TxXtalTrimMode(port, false);
            }
        }
        hal_uart_deinit(port);
#ifdef UART_DEBUG
        snprintf(g_uart_response_buf, 512, "uart deinit success!");
        dvt_cmd_send(g_uart_response_buf, strlen(g_uart_response_buf));
#endif
    } else {
        printk("trim uart %d initialized!", port);
        __disable_irq();
        /*Set a signal frequency,Baud rate is twice the frequency*/
        // mux_control((mux_port_t)port, MUX_CMD_CLEAN, NULL);
        hal_uart_set_baudrate(port, HAL_UART_BAUDRATE_62500);
        hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &start_time);
        while (flg_timeout == false) {
            hal_uart_TxXtalTrimMode(port, true);
            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &end_time);
            hal_gpt_get_duration_count(start_time, end_time, &during_time);
            if (during_time > TRIM_TIME_MAX(timeout_s)) {
                flg_timeout = true;
                hal_uart_TxXtalTrimMode(port, false);
            }
        }
        /*Set a signal frequency,Baud rate is twice the frequency*/
        uart_restore_register(port);
        __enable_irq();
#ifdef UART_DEBUG
        snprintf(g_uart_response_buf, 512, "uart init success!");
        dvt_cmd_send(g_uart_response_buf, strlen(g_uart_response_buf));
#endif
    }
    printk("start_time=%d end_time=%d,during_time=%d", start_time, end_time, during_time);
#ifdef UART_DEBUG
        // uart_restore_register(HAL_UART_0);
        for(uint8_t i=0 ; i < 17 ; i++){
            uint32_t uart_addr = 0x4000f000 + 0x4 * i;
            snprintf(g_uart_response_buf, 512, "uart trim reg addr: 0x%x, value: 0x%x\r\n",uart_addr,*(volatile uint32_t *)(uart_addr));
            dvt_cmd_send(g_uart_response_buf, strlen(g_uart_response_buf));
            memset(g_uart_response_buf, 0, sizeof(g_uart_response_buf));
        }
#endif

    return true;
}


void *RACE_CmdHandler_race_crystal_trim(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t port;
        uint32_t baudrate;
        uint16_t timeout_ms;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    CMD *pCmd = (CMD *)pCmdMsg;
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_CRYSTAL_TRIM_TRIGGER,
                                      sizeof(RSP),
                                      channel_id);

    printk("uart port:%d baudrate:%d timeout_ms:%d",
                    pCmd->port,
                    pCmd->baudrate,
                    pCmd->timeout_ms);

    if (pEvt != NULL) {
        send_pattern_char(pCmd->port, pCmd->baudrate, pCmd->timeout_ms);
    }

    return pEvt;
}

void *RACE_CmdHandler_crystal_trim(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    (void)length;

    printk("RACE_CmdHandler_crystal_trim, type[0x%X], race_id[0x%X], channel_id[%d]",
                     pCmdMsg->hdr.type, pCmdMsg->hdr.id, channel_id);
#ifdef UART_DEBUG
#define     HQA_CMD_PORT        HAL_UART_1
#define     HQA_CMD_RX_PIN      HAL_GPIO_24
#define     HQA_CMD_RX_MODE     6
#define     HQA_CMD_TX_PIN      HAL_GPIO_23
#define     HQA_CMD_TX_MODE     6
        hal_pinmux_set_function(HQA_CMD_RX_PIN, HQA_CMD_RX_MODE);
        hal_pinmux_set_function(HQA_CMD_TX_PIN, HQA_CMD_TX_MODE);
        hal_gpio_disable_pull(HQA_CMD_TX_PIN);
        hal_gpio_pull_up(HQA_CMD_RX_PIN);
        hal_uart_deinit(HAL_UART_1);
        hal_uart_config_t uart_config;
        uart_config.baudrate = HAL_UART_BAUDRATE_921600;
        uart_config.parity = HAL_UART_PARITY_NONE;
        uart_config.stop_bit = HAL_UART_STOP_BIT_1;
        uart_config.word_length = HAL_UART_WORD_LENGTH_8;
        hal_uart_init(HAL_UART_1, &uart_config);

        hal_uart_dma_config_t dma_config;
        dma_config.receive_vfifo_alert_size = 50;
        dma_config.receive_vfifo_buffer = rx_vfifo_buffer;
        dma_config.receive_vfifo_buffer_size = 512;
        dma_config.receive_vfifo_threshold_size = 128;
        dma_config.send_vfifo_buffer = tx_vfifo_buffer;
        dma_config.send_vfifo_buffer_size = 512;
        dma_config.send_vfifo_threshold_size = 51;
        hal_uart_set_dma(HAL_UART_1, &dma_config);
        hal_uart_set_software_flowcontrol(HAL_UART_1, 0x11, 0x13, 0x77);

        for(uint8_t i=0 ; i < 17 ; i++){
            uint32_t uart_addr = 0x4000f000 + 0x4 * i;
            snprintf(g_uart_response_buf, 512, "uart log reg addr: 0x%x, value: 0x%x\r\n",uart_addr,*(volatile uint32_t *)(uart_addr));
            dvt_cmd_send(g_uart_response_buf, strlen(g_uart_response_buf));
            memset(g_uart_response_buf, 0, sizeof(g_uart_response_buf));
        }
#endif
    if (pCmdMsg->hdr.type == RACE_TYPE_COMMAND) {
        switch (pCmdMsg->hdr.id) {
            case RACE_CRYSTAL_TRIM_TRIGGER: //0x3076
                return RACE_CmdHandler_race_crystal_trim((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), channel_id);
            default:
                break;
        }
    }

    return NULL;
}

#endif   /* HAL_UART_MODULE_ENABLED */

#endif  /* RACE_CRYSTAL_TRIM_CMD_ENABLE */

#endif
