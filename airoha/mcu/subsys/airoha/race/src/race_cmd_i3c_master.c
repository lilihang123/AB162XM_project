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

#ifdef RACE_I3C_MASTER_CMD_ENABLE
#include "race_cmd_i3c_master.h"
#include "hal.h"
#include "mux.h"
#include "hal_i3c_master.h"

////////////////////////////////////////////////////////////////////////////////
// Constant Definitions ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define RACE_I3C_MASTER_TX_LEN          10240
#define RACE_I3C_MASTER_RX_LEN          256

////////////////////////////////////////////////////////////////////////////////
// TYPE DEFINITIONS ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
typedef struct {
        uint8_t loop;
        uint8_t type;
        uint8_t port;
        uint8_t da_addr;
        uint32_t fs_speed;
        uint32_t hs_speed;
        uint32_t recv_length;
        uint32_t send_length;
} race_cmd_i3cm_config_t;

////////////////////////////////////////////////////////////////////////////////
// Global Variables ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
static ATTR_ZIDATA_IN_NONCACHED_RAM_16BYTE_ALIGN uint8_t i3cm_tx_buffer[RACE_I3C_MASTER_TX_LEN];
static ATTR_ZIDATA_IN_NONCACHED_RAM_16BYTE_ALIGN uint8_t i3cm_rx_buffer[RACE_I3C_MASTER_RX_LEN];
static race_cmd_i3cm_config_t   s_i3cm_config;
////////////////////////////////////////////////////////////////////////////////
// FUNCTION DECLARATIONS ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void race_i3c_master_callback(hal_i3c_master_port_t i3c_port,uint8_t slave_address, hal_i3c_master_callback_event_t event, void *user_data)
{
    LOG_INF("race cmd i3c master: irq triggered, event %d", event);

    if (event == HAL_I3C_EVENT_SUCCESS) {
        if (s_i3cm_config.loop) {
            hal_i3c_master_status_t status;
            hal_i3c_master_transfer_config_t trans_config;

            trans_config.trans_type = s_i3cm_config.type;
            trans_config.recv_size  = s_i3cm_config.recv_length;
            trans_config.send_size  = s_i3cm_config.send_length;
            trans_config.slave_addr = s_i3cm_config.da_addr;

            trans_config.recv_buff  = i3cm_rx_buffer;
            trans_config.send_buff  = i3cm_tx_buffer;

            status = hal_i3c_master_transfer(s_i3cm_config.port, &trans_config);
            if (status != HAL_I3C_MASTER_STATUS_OK) {
                LOG_INF("race cmd i3c master: init err %d", status);
            }
        }
    }
}


void *i3c_master_send_and_receive(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct { // for import parameter
        RACE_COMMON_HDR_STRU hdr;
        uint8_t cmd;
        uint8_t port;
        uint8_t da_addr;
        uint32_t fs_speed;
        uint32_t hs_speed;
        uint32_t recv_length;
        uint32_t send_length;
        uint8_t send_data[2];
    } PACKED *PTR_THIS_RACE_CMD_STRU;

    typedef struct {// for export parameter
        int8_t  status;
        uint8_t receive_data[RACE_I3C_MASTER_RX_LEN];
    } PACKED RSP;

    PTR_THIS_RACE_CMD_STRU pThisCmd = (PTR_THIS_RACE_CMD_STRU)pCmdMsg;

    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_CMD_I3C_MASTER_SEND_AND_RECEIVE,
                                      pThisCmd->recv_length,
                                      channel_id);

    LOG_INF("race_cmd_i3cm: cmd(%d), port(%d), da(0x%x), fs(%d), hs(%d),rcv_sz(%d), snd_sz(%d)",
        pThisCmd->cmd,
        pThisCmd->port,
        pThisCmd->da_addr,
        pThisCmd->fs_speed,
        pThisCmd->hs_speed,
        pThisCmd->recv_length,
        pThisCmd->send_length
    );

    if (pThisCmd->recv_length > RACE_I3C_MASTER_RX_LEN || pThisCmd->send_length > RACE_I3C_MASTER_TX_LEN) {
        LOG_INF("race cmd i3c rx or tx len error,limit is rx(%d), tx(%x)", RACE_I3C_MASTER_RX_LEN, RACE_I3C_MASTER_TX_LEN);
        pEvt->status = -1;
        return (void *)pEvt;
    }


    s_i3cm_config.port       =  pThisCmd->port;
    s_i3cm_config.da_addr    =  pThisCmd->da_addr;
    s_i3cm_config.fs_speed   =  pThisCmd->fs_speed;
    s_i3cm_config.hs_speed   =  pThisCmd->hs_speed;
    s_i3cm_config.recv_length=  pThisCmd->recv_length;
    s_i3cm_config.send_length=  pThisCmd->send_length;

    switch(pThisCmd->cmd) {
        case 0: {
            s_i3cm_config.loop = 0;
            memcpy(i3cm_tx_buffer, pThisCmd->send_data, pThisCmd->send_length);
        } break;
        /*only for desense*/
        case 1: {
            s_i3cm_config.loop = 1;
            memset(i3cm_tx_buffer, 0x55, pThisCmd->send_length);
            s_i3cm_config.recv_length = 0;
        } break;

        default:{
            pEvt->status = -1;
            return pEvt;
        } break;
    }
    if(s_i3cm_config.recv_length != 0 && s_i3cm_config.send_length != 0) {
        s_i3cm_config.type = HAL_I3C_MASTER_TRANSFER_TYPE_SEND_TO_RECEIVE;
    } else if (s_i3cm_config.recv_length != 0) {
        s_i3cm_config.type = HAL_I3C_MASTER_TRANSFER_TYPE_RECEIVE;
    } else if (s_i3cm_config.send_length != 0) {
        s_i3cm_config.type = HAL_I3C_MASTER_TRANSFER_TYPE_SEND;
    } else {
        LOG_INF("race cmd i3c rx and tx len error,length is 0");
        pEvt->status = -1;
    }


    if (pEvt) {
        hal_i3c_master_status_t status;
        hal_i3c_master_config_t init_config;
        uint8_t i3c_port = pThisCmd->port;
        hal_i3c_master_transfer_config_t trans_config;

        init_config.mode = HAL_I3C_MASTER_WORKING_MODE_I3C;
        init_config.fast_speed_khz = s_i3cm_config.fs_speed;
        init_config.high_speed_khz = s_i3cm_config.hs_speed;
        init_config.map_pid_da_config = NULL;
        init_config.map_pid_da_sz = 0;
        init_config.call_back = race_i3c_master_callback;
        init_config.user_data = NULL;

        status = hal_i3c_master_init(i3c_port, &init_config);
        if (status != HAL_I3C_MASTER_STATUS_OK) {
            LOG_INF("race cmd i3c master: init err %d", status);
        }
        trans_config.trans_type = s_i3cm_config.type;
        trans_config.recv_buff  = i3cm_rx_buffer;
        trans_config.recv_size  = s_i3cm_config.recv_length;
        trans_config.send_buff  = i3cm_tx_buffer;
        trans_config.send_size  = s_i3cm_config.send_length;
        trans_config.slave_addr = s_i3cm_config.da_addr;

        status = hal_i3c_master_transfer(i3c_port, &trans_config);
        if (status != HAL_I3C_MASTER_STATUS_OK) {
            LOG_INF("race cmd i3c master: transfer err %d", status);
        }

    }
    return (void *)pEvt;
}

void *RACE_CmdHandler_i3c_master(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    LOG_INF("RACE_CmdHandler_i3c_master_send_and_receive,pCmdMsg->hdr.id = %d",(int)pCmdMsg->hdr.id);

    switch (pCmdMsg->hdr.id) {
        case RACE_CMD_I3C_MASTER_SEND_AND_RECEIVE: { //0x5010
            return i3c_master_send_and_receive(pCmdMsg, length, channel_id);
        }
        break;

        default:
            break;
    }

    return NULL;
}

#endif /* RACE_I3C_MASTER_CMD_ENABLE */
#endif
