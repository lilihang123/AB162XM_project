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
// #include "race_noti.h"
// #include "race_lpcomm_ps_noti.h"
// #include "memory_attribute.h"

#ifdef RACE_SPI_MASTER_CMD_ENABLE
#include "race_cmd_spi_master.h"
#include "hal.h"
#include "race_xport.h"

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

#define RACE_SPI_MASTER_SEND_MAX_LEN    50
#define RACE_SPI_MASTER_RECEIVE_MAX_LEN 100

// static SemaphoreHandle_t g_race_spi_master_semaphore = NULL;
static struct k_sem g_race_spi_master_semaphore;
static volatile uint32_t g_race_spi_master_err_flag = 0;
static ATTR_ZIDATA_IN_NONCACHED_RAM_16BYTE_ALIGN uint8_t send_buffer[RACE_SPI_MASTER_SEND_MAX_LEN];
static ATTR_ZIDATA_IN_NONCACHED_RAM_16BYTE_ALIGN uint8_t receive_buff[RACE_SPI_MASTER_RECEIVE_MAX_LEN];

void race_spi_master_callback(hal_spi_master_callback_event_t event, void *user_data)
{
    // BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    if (HAL_SPI_MASTER_EVENT_SEND_FINISHED == event) {
        LOG_INF("Race SPI master send done", 0);
        g_race_spi_master_err_flag = 0;
    } else if (HAL_SPI_MASTER_EVENT_RECEIVE_FINISHED == event) {
        LOG_INF("Race SPI master receive done", 0);
        g_race_spi_master_err_flag = 0;
    } else if (HAL_SPI_MASTER_NO_BUSY_FUNCTION_ERROR == event) {
        // Error handler;
        g_race_spi_master_err_flag = 1;
        LOG_INF("Race SPI master race_spi_master_callback ERROR!!!", 0);
    }
    // xSemaphoreGiveFromISR(g_race_spi_master_semaphore, &xHigherPriorityTaskWoken);
    k_sem_give(&g_race_spi_master_semaphore);
}


void *spi_master_send_and_receive(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    uint32_t i;
    typedef struct { // for import parameter
        RACE_COMMON_HDR_STRU Hdr;
        uint8_t spi_master_port;
        hal_spi_master_config_t spi_config;
        hal_spi_master_advanced_config_t spi_advanced_config;
        hal_spi_master_non_single_config_t spi_non_single_config;
        hal_spi_master_chip_select_timing_t chip_select_timing;
        hal_spi_master_deassert_t deassert;
        uint32_t receive_length;
        uint32_t send_length;
        uint8_t send_data[0];
    } PACKED *PTR_THIS_RACE_CMD_STRU;
    PTR_THIS_RACE_CMD_STRU pThisCmd = (PTR_THIS_RACE_CMD_STRU)pCmdMsg;

    typedef struct {// for export parameter
        uint8_t  status;
        uint8_t receive_data[RACE_SPI_MASTER_RECEIVE_MAX_LEN];
    } PACKED RSP;
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_CMD_SPI_MASTER_SEND_AND_RECEIVE,
                                      pThisCmd->receive_length + 1,
                                      channel_id);
    if ((pThisCmd->receive_length >= RACE_SPI_MASTER_RECEIVE_MAX_LEN) || (pThisCmd->send_length >= RACE_SPI_MASTER_SEND_MAX_LEN)) {
        LOG_INF("Race SPI master parameter check error,len too long!!", 0);
        return (void *)pEvt;
    }
    g_race_spi_master_err_flag = 0;
    if (pEvt) {
        // if (g_race_spi_master_semaphore == NULL) {
        //     g_race_spi_master_semaphore = xSemaphoreCreateBinary();
        // }
        // if (g_race_spi_master_semaphore == NULL) {
        //     assert(0);
        // }
        if(k_sem_init(&g_race_spi_master_semaphore,0,1) != 0 ) {
            assert(0);
        }
        hal_spi_send_and_receive_config_ex_no_busy_t spi_send_and_receive_config_ex_no_busy;
        LOG_INF("race_cmdhdl_spi_master_send_and_receive: spi master port:%d,clock freq:%d,slave port:%d,order:%d,pola:%d,phase:%d,rx len:%d,tx len:%d mode=%d\
        dummy_bits=%d command_bytes=%d byte_order=%d chip_polarity=%d get_tick=%d sample_select=%d setp_count=%d hold_count=%d idle_count=%d deassert=%d", 19, pThisCmd->spi_master_port,
                         pThisCmd->spi_config.clock_frequency,
                         pThisCmd->spi_config.slave_port,
                         pThisCmd->spi_config.bit_order,
                         pThisCmd->spi_config.polarity,
                         pThisCmd->spi_config.phase,
                         pThisCmd->receive_length,
                         pThisCmd->send_length,
                         pThisCmd->spi_non_single_config.mode,
                         pThisCmd->spi_non_single_config.dummy_bits,
                         pThisCmd->spi_non_single_config.command_bytes,
                         pThisCmd->spi_advanced_config.byte_order,
                         pThisCmd->spi_advanced_config.chip_polarity,
                         pThisCmd->spi_advanced_config.get_tick,
                         pThisCmd->spi_advanced_config.sample_select,
                         pThisCmd->chip_select_timing.chip_select_setup_count,
                         pThisCmd->chip_select_timing.chip_select_hold_count,
                         pThisCmd->chip_select_timing.chip_select_idle_count,
                         pThisCmd->deassert);

        spi_send_and_receive_config_ex_no_busy.spi_config.bit_order = pThisCmd->spi_config.bit_order;
        spi_send_and_receive_config_ex_no_busy.spi_config.clock_frequency = pThisCmd->spi_config.clock_frequency;
        spi_send_and_receive_config_ex_no_busy.spi_config.phase = pThisCmd->spi_config.phase;
        spi_send_and_receive_config_ex_no_busy.spi_config.polarity = pThisCmd->spi_config.polarity;
        spi_send_and_receive_config_ex_no_busy.spi_config.slave_port = pThisCmd->spi_config.slave_port;
        spi_send_and_receive_config_ex_no_busy.spi_advanced_config.byte_order = pThisCmd->spi_advanced_config.byte_order;
        spi_send_and_receive_config_ex_no_busy.spi_advanced_config.chip_polarity = pThisCmd->spi_advanced_config.chip_polarity;
        spi_send_and_receive_config_ex_no_busy.spi_advanced_config.get_tick = pThisCmd->spi_advanced_config.get_tick;
        spi_send_and_receive_config_ex_no_busy.spi_advanced_config.sample_select = pThisCmd->spi_advanced_config.sample_select;
        spi_send_and_receive_config_ex_no_busy.spi_non_single_config.mode = pThisCmd->spi_non_single_config.mode;
        spi_send_and_receive_config_ex_no_busy.spi_non_single_config.dummy_bits = pThisCmd->spi_non_single_config.dummy_bits;
        spi_send_and_receive_config_ex_no_busy.spi_non_single_config.command_bytes = pThisCmd->spi_non_single_config.command_bytes;
        spi_send_and_receive_config_ex_no_busy.chip_select_timing.chip_select_setup_count = pThisCmd->chip_select_timing.chip_select_setup_count;
        spi_send_and_receive_config_ex_no_busy.chip_select_timing.chip_select_hold_count = pThisCmd->chip_select_timing.chip_select_hold_count;
        spi_send_and_receive_config_ex_no_busy.chip_select_timing.chip_select_idle_count = pThisCmd->chip_select_timing.chip_select_idle_count;
        spi_send_and_receive_config_ex_no_busy.deassert = pThisCmd->deassert;
        for (i = 0; i < pThisCmd->send_length; i++) {
            send_buffer[i] = pThisCmd->send_data[i];
        }

        spi_send_and_receive_config_ex_no_busy.spi_callback = race_spi_master_callback;
        spi_send_and_receive_config_ex_no_busy.spi_send_and_receive_config_ex.receive_buffer = receive_buff;
        spi_send_and_receive_config_ex_no_busy.spi_send_and_receive_config_ex.receive_length = pThisCmd->receive_length;
        spi_send_and_receive_config_ex_no_busy.spi_send_and_receive_config_ex.send_data = send_buffer;
        spi_send_and_receive_config_ex_no_busy.spi_send_and_receive_config_ex.send_length = pThisCmd->send_length;
        spi_send_and_receive_config_ex_no_busy.user_data = NULL;

        hal_spi_master_status_t status;
        // Send and receive data simultaneously.
        status = hal_spi_master_send_and_receive_dma_no_busy(pThisCmd->spi_master_port, &spi_send_and_receive_config_ex_no_busy);
        if (HAL_SPI_MASTER_STATUS_OK != status) {
            // Error handler;
            pEvt->status = status;//
            LOG_INF("Race SPI master send and receive error!!!status:%d", 1, status);
            return (void *)pEvt;
        }
        LOG_INF("Race SPI master waiting for send and receive done~~~", 0);
        // if (xSemaphoreTake(g_race_spi_master_semaphore, portMAX_DELAY) == pdTRUE) {
        if (k_sem_take(&g_race_spi_master_semaphore, K_FOREVER) == 0) {
            if (g_race_spi_master_err_flag == 1) {
                pEvt->status = 1;//
                LOG_INF("Race SPI master send and receive fail!!!g_race_spi_master_err_flag = 1", 0);
                return (void *)pEvt;
            }
            for (i = 0; i < pThisCmd->receive_length; i++) {
                pEvt->receive_data[i] = receive_buff[i];
                LOG_INF("Race SPI master receive data:0x%x", 1, (uint8_t)receive_buff[i]);
            }
            pEvt->status = 0;
            LOG_INF("Race SPI master send and receive success", 0);
        } else {
            pEvt->status = 1;//
            LOG_INF("Race SPI master send and receive fail!!!", 0);
        }
    }
    return (void *)pEvt;
}

enum {
    RACE_CMD_SPIM_OPT_MODE_NORMAL = 0,
    RACE_CMD_SPIM_OPT_MODE_DESENSE= 1,
};

////////////////////////////////////////////////////////////////////////////


#define RACE_CMD_SPIM_RX_SIZE   8192
#define RACE_CMD_SPIM_TX_SIZE   8192

static uint32_t s_spim_desense_loop = 0;
static uint8_t  s_spim_port = 0;
static hal_spi_master_send_and_receive_config_t s_spi_snd_rcv_config;

static ATTR_ZIDATA_IN_NONCACHED_RAM_16BYTE_ALIGN uint8_t spim_rx_buff[RACE_CMD_SPIM_RX_SIZE];
static ATTR_ZIDATA_IN_NONCACHED_RAM_16BYTE_ALIGN uint8_t spim_tx_buff[RACE_CMD_SPIM_TX_SIZE];

#ifdef HAL_SPI_SLAVE_MODULE_ENABLED
hal_spi_slave_vfifo_config_t                    s_spislv_vfifo_config;
static ATTR_ZIDATA_IN_NONCACHED_RAM_16BYTE_ALIGN uint8_t spis_rx_buff[RACE_CMD_SPIM_TX_SIZE];
static ATTR_ZIDATA_IN_NONCACHED_RAM_16BYTE_ALIGN uint8_t spis_tx_buff[RACE_CMD_SPIM_RX_SIZE];
#endif


void race_cmd_spim_dma_callback(hal_spi_master_callback_event_t event, void *user_data)
{
    static bool irq_trigger = 0;
    static int  spim_prt_cnt = 0;

    if (irq_trigger == 0) {
        LOG_INF("race_cmd_spim_dma_callback: event(%d)!!!", event);
        irq_trigger = 1;
    }
#if 1
    hal_spi_master_status_t status = 0;
    if(event == HAL_SPI_MASTER_EVENT_SEND_FINISHED || event == HAL_SPI_MASTER_EVENT_RECEIVE_FINISHED) {
        if (s_spim_desense_loop) {
            if (s_spi_snd_rcv_config.receive_length > 0) {
                status = hal_spi_master_send_and_receive_dma(s_spim_port, &s_spi_snd_rcv_config);
            } else {
                status = hal_spi_master_send_dma(s_spim_port, s_spi_snd_rcv_config.send_data, s_spi_snd_rcv_config.send_length);
            }
            if(status != HAL_SPI_MASTER_STATUS_OK) {
                LOG_INF("race_cmd_spim_dma_callback: send or recv dma fail(%d)!!!", 1, status);
            }
        }
    } else {
        LOG_INF("race_cmd_spim_dma_callback: err event(%d)!!!", event);
    }

    if((spim_prt_cnt++) % 1000 == 0) {
        LOG_INF("race_cmd_spim_dma_callback: master event 0x%x, data 0x%x!!!", event, spim_rx_buff[0]);
    }
    spim_prt_cnt++;
#endif
}

#ifdef HAL_SPI_SLAVE_MODULE_ENABLED
static int      print_cnt = 0;
static uint8_t  s_tmp_rx_buff[8192];
static uint8_t  s_tmp_tx_buff[8192];
void race_cmd_spis_dir_mode_callback(hal_spi_slave_transaction_status_t status,void *user_data)
{
    uint32_t rx_len = 0;
    switch(status.interrupt_status) {
        case HAL_SPI_SLAVE_EVENT_RX_DMA_FULL :{
            rx_len = hal_spi_slave_get_vfifo_available_data_bytes(0);
            hal_spi_slave_receive_vfifo(0, s_tmp_rx_buff, rx_len);
        } break;
        case HAL_SPI_SLAVE_EVENT_TX_DMA_EMPTY: {
            hal_spi_slave_send_vfifo(0, s_tmp_tx_buff, sizeof(s_tmp_tx_buff));
        } break;
        default: break;
    }
    if((print_cnt++) % 1000 == 0) {
        LOG_INF("race_cmd_spis_dir_mode_callback: slave event 0x%x, data 0x%x!!!", status.interrupt_status, s_tmp_rx_buff[0]);
    }
}
#endif


void *race_cmd_spim_control(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct { // for import parameter
        RACE_COMMON_HDR_STRU Hdr;
        uint8_t ctrl_cmd;
        uint8_t spim_port;
        uint8_t spim_mode;
        uint8_t spim_ncs;
        hal_spi_master_config_t spi_config;
        uint32_t receive_length;
        uint32_t send_length;
        uint8_t  send_data[1];
    }PACKED RACE_CMD_SPIM_PKT_T;

    typedef struct {// for export parameter
        uint8_t  status;
        uint8_t  errno;
        uint8_t receive_data[RACE_SPI_MASTER_RECEIVE_MAX_LEN];
    } PACKED RACE_CMD_SPIM_DMA_RSP_T;

    hal_spi_master_config_t init_config;


    RACE_CMD_SPIM_PKT_T  *pPktSpim = (RACE_CMD_SPIM_PKT_T *)pCmdMsg;
    hal_spi_master_status_t status = 0;
    RACE_CMD_SPIM_DMA_RSP_T *pEvt = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_CMD_SPI_MASTER_CONTROL,
                                      pPktSpim->receive_length + 1,
                                      channel_id);

    hal_spi_master_deinit(pPktSpim->spim_port);

    LOG_INF("race_cmd_spim_control: sizeof(RACE_CMD_SPIM_PKT_T) = %d, sizeof(hal_spi_master_config_t) = %d, sizeof(header)=%d",
            sizeof(RACE_CMD_SPIM_PKT_T),
            sizeof(hal_spi_master_config_t),
            sizeof(RACE_COMMON_HDR_STRU)
        );
    s_spim_port = pPktSpim->spim_port;
    init_config.clock_frequency = pPktSpim->spi_config.clock_frequency;
    init_config.bit_order = pPktSpim->spi_config.bit_order;
    init_config.phase = pPktSpim->spi_config.phase;
    init_config.polarity = pPktSpim->spi_config.polarity;
    init_config.slave_port = pPktSpim->spi_config.slave_port;


#ifdef HAL_SPI_SLAVE_MODULE_ENABLED
	hal_spi_slave_config_t  slv_init_config;
    hal_spi_slave_status_t  slv_status;

    slv_init_config.bit_order = pPktSpim->spi_config.bit_order;
    slv_init_config.phase     = pPktSpim->spi_config.phase;
    slv_init_config.polarity  = pPktSpim->spi_config.polarity;
    slv_init_config.timeout_threshold = 0xFFFF;

    memset(spis_tx_buff,  0x55, sizeof(spis_tx_buff));
    memset(s_tmp_tx_buff, 0x55, sizeof(s_tmp_tx_buff));
    s_spislv_vfifo_config.rx_buffer = spis_rx_buff;
    s_spislv_vfifo_config.rx_buffer_size = RACE_CMD_SPIM_TX_SIZE;
    s_spislv_vfifo_config.rx_threshold = pPktSpim->send_length;
    s_spislv_vfifo_config.transfer_type = HAL_SPI_SLAVE_DMA_TRANSFER_TYPE_SINGLE_BYTE;
    s_spislv_vfifo_config.tx_buffer = spis_tx_buff;
    s_spislv_vfifo_config.tx_buffer_size = RACE_CMD_SPIM_RX_SIZE;
    s_spislv_vfifo_config.tx_threshold = pPktSpim->receive_length;


    slv_status = hal_spi_slave_init(0, &slv_init_config);
    if(slv_status != HAL_SPI_SLAVE_STATUS_OK) {
        LOG_INF("race_cmd_spim_control: spis init fail:%d", slv_status);
    }
    //hal_spi_slave_set_transfer_type(0, pPktSpim->spim_mode);

    slv_status = hal_spi_slave_set_vfifo(0, &s_spislv_vfifo_config);
    if(slv_status != HAL_SPI_SLAVE_STATUS_OK) {
        LOG_INF("race_cmd_spim_control: spis set vfifo fail:%d", slv_status);
    }
    slv_status = hal_spi_slave_send_vfifo(0, s_tmp_tx_buff, sizeof(s_tmp_tx_buff));
    if(slv_status != HAL_SPI_SLAVE_STATUS_OK) {
        LOG_INF("race_cmd_spim_control: spis snd vfifo fail:%d", slv_status);
    }
    slv_status = hal_spi_slave_register_callback(0, race_cmd_spis_dir_mode_callback, NULL);
    if(slv_status != HAL_SPI_SLAVE_STATUS_OK) {
        LOG_INF("race_cmd_spim_control: spis reg callback fail:%d", slv_status);
    }
#endif
    LOG_INF("race_cmd_spim_control: spim init -> port(%d), mode(%d), freq(%d), msb(%d), pha(%d), pol(%d), ncs(%d)",
                pPktSpim->spim_port,
                pPktSpim->spim_mode,
                pPktSpim->spi_config.clock_frequency,
                pPktSpim->spi_config.bit_order,
                pPktSpim->spi_config.phase,
                pPktSpim->spi_config.polarity,
                pPktSpim->spi_config.slave_port
    );
    LOG_INF("race_cmd_spim_control: spim config -> user_cmd(%d), send_length(%d), receive_length(%d)",
                pPktSpim->ctrl_cmd,
                pPktSpim->send_length,
                pPktSpim->receive_length
    );
    pEvt->errno  = 0;
    pEvt->status = 0;
    if (pPktSpim->send_length > RACE_CMD_SPIM_TX_SIZE || pPktSpim->receive_length > RACE_CMD_SPIM_RX_SIZE){
        pEvt->status = -1;
        pEvt->errno  = 0;
        return pEvt;
    }

    uint8_t patten = 0;
    switch(pPktSpim->spim_mode) {
        case 0:
        case 1: patten = 0x55; break;
        case 2: patten = 0x66; break;
        case 3: patten = 0x0F; break;
    }

    if (pPktSpim->ctrl_cmd == RACE_CMD_SPIM_OPT_MODE_DESENSE) {
        memset(spim_tx_buff, patten, sizeof(spim_tx_buff));
        s_spim_desense_loop = 1;
    } else if(pPktSpim->ctrl_cmd == RACE_CMD_SPIM_OPT_MODE_NORMAL) {
        memcpy(spim_tx_buff, &pPktSpim->send_data[0], pPktSpim->send_length);
        s_spim_desense_loop = 0;
    }

    s_spi_snd_rcv_config.receive_buffer = spim_rx_buff;
    s_spi_snd_rcv_config.send_data      = spim_tx_buff;
    s_spi_snd_rcv_config.receive_length = pPktSpim->receive_length;
    s_spi_snd_rcv_config.send_length    = pPktSpim->send_length;


    do {
        status = hal_spi_master_init(pPktSpim->spim_port, &init_config);
        if(status != HAL_SPI_MASTER_STATUS_OK) {
            pEvt->status = status;
            pEvt->errno  = 1;
            LOG_INF("race_cmd_spim_control: init fail -> status(%d)", status);
            break;
        }

        status = hal_spi_master_set_mode(pPktSpim->spim_port, pPktSpim->spim_mode);
        if(status != HAL_SPI_MASTER_STATUS_OK) {
            pEvt->status = status;
            pEvt->errno  = 2;
            LOG_INF("race_cmd_spim_control: set mode fail -> status(%d)", status);
            break;

        }

        status = hal_spi_master_register_callback(pPktSpim->spim_port, race_cmd_spim_dma_callback, NULL);
        if(status != HAL_SPI_MASTER_STATUS_OK) {
            pEvt->status = status;
            pEvt->errno  = 3;
            LOG_INF("race_cmd_spim_control: register fail -> status(%d)", status);
            break;

        }

        if (s_spi_snd_rcv_config.receive_length > 0) {
            status = hal_spi_master_send_and_receive_dma(pPktSpim->spim_port, &s_spi_snd_rcv_config);
        } else {
            status = hal_spi_master_send_dma(pPktSpim->spim_port, s_spi_snd_rcv_config.send_data, s_spi_snd_rcv_config.send_length);
        }
        if(status != HAL_SPI_MASTER_STATUS_OK) {
            pEvt->status = status;
            pEvt->errno  = 4;
             LOG_INF("race_cmd_spim_control: snd or recv fail -> status(%d)", status);
        }
    }while(0);
    LOG_INF("race_cmd_spim_control: result -> status(%d), errno(%d)", pEvt->status, pEvt->errno);

    return pEvt;
}




void *RACE_CmdHandler_spi_master_send_and_receive(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    switch (pCmdMsg->hdr.id) {
        case RACE_CMD_SPI_MASTER_SEND_AND_RECEIVE: { //0x5000
            return spi_master_send_and_receive((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);
        }
        break;
        case RACE_CMD_SPI_MASTER_CONTROL: {
            race_cmd_spim_control(pCmdMsg, length, channel_id);
        } break;
        default:
            break;
    }

    return NULL;
}

#endif  /* RACE_SPI_MASTER_CMD_ENABLE */
#endif
