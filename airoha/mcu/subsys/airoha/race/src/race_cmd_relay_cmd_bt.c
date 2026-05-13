/* Copyright Statement:
 *
 * (C) 2026  Airoha Technology Corp. All rights reserved.
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


#include "race_cmd_feature.h"
#include "race_cmd_relay_cmd_bt.h"
//#include "race_cmd_bluetooth.h"
//#include "bt_connection_manager_internal.h"
//#include "stdio.h"
#include "race_util.h"
#include "race_xport.h"
#include "race_bt.h"
#include "race_timer.h"
#include "race_cmd.h"
#include "race_event.h"
#if CONFIG_AIR_RACE_RELAY_CMD_ENABLE
typedef struct {
    uint8_t channel_id;
    uint8_t relay_type;
    race_pkt_t cmd;
} PACKED race_ralay_bt_packet_t;

uint8_t g_race_bt_relay_channel = 0xff;

bt_addr_t g_bt_addr = {0};


#define RACE_RELAT_BT_CHANNEL     (uint8_t)RACE_SERIAL_PORT_TYPE_BLE
static void race_relay_bt_callback(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id);

bool race_relay_send_bt(race_pkt_t *race_pkt, uint16_t length, uint8_t channel_id, uint8_t relay_type)
{
    race_ralay_bt_packet_t *relay_data = NULL;
    bool ret = false;

    LOG_INF("[relay_cmd] race_relay_send_bt, race_id 0x%04X, length %d, channel %d, relay_type %d",
            race_pkt->hdr.id, length, channel_id, relay_type);

    if (length != race_pkt->hdr.length + 4) {
        LOG_INF("[relay_cmd] race_relay_send_bt, length(%d) != 4 + hdr.len(%d)", length, race_pkt->hdr.length);
        return false;
    }

    relay_data = (race_ralay_bt_packet_t *)RACE_ClaimPacket(RACE_TYPE_COMMAND_WITHOUT_RSP,
                                                            RACE_CMDRELAY_RELAY,
                                                            length + 2,
                                                            g_race_bt_relay_channel);
    if (relay_data == NULL) {
        LOG_INF("[relay_cmd] race_relay_send_bt, alloc fail");
        return false;
    }

    relay_data->channel_id = channel_id;
    relay_data->relay_type = relay_type;
    memcpy(&(relay_data->cmd), race_pkt, length);
    if (race_flush_packet((uint8_t *)relay_data, g_race_bt_relay_channel) == RACE_STATUS_OK) {
        ret = true;
    }

    return ret;
}

static void race_cmd_relay_bt_req_hdlr(race_pkt_t *pMsg, uint8_t channel)
{
    //uint8_t channel_id = g_race_bt_relay_channel;//agent and partner
    //uint8_t channel_id = RACE_CHANNEL_ID_SET_RELAY_CMD_FLAG(g_race_bt_relay_channel);
    uint8_t channel_id = RACE_CHANNEL_ID_SET_RELAY_CMD_FLAG(channel);
    LOG_INF("race_debug race_cmd_relay_bt_req_hdlr channel:%x, channel_id:%x", channel, channel_id);
    race_send_pkt_t *pEvt = RACE_CmdHandler(pMsg, channel_id);

    if(pEvt) {
        race_relay_send_bt(&pEvt->race_data, pEvt->length, channel, RACE_CMD_RSP_FROM_PARTNER);
        race_mem_free(pEvt);
    }
}

static void race_cmd_relay_bt_rsp_hdlr(race_pkt_t *pMsg, uint8_t channel)
{
    race_status_t ret = RACE_STATUS_OK;
    typedef struct {
        //uint8_t dst_type;
        //uint8_t dst_id;
        uint8_t addr[6];
        race_pkt_t race_cmd_rsp;
    } PACKED RSP;
    LOG_INF("race_debug race_cmd_relay_bt_rsp_hdlr channel:%x", channel);
    channel = RACE_CHANNEL_ID_CLEAR_RELAY_CMD_FLAG(channel);
    RSP *rsp = RACE_ClaimPacketAppID(pMsg->hdr.pktId.field.app_id,
                     RACE_TYPE_NOTIFICATION,
                     RACE_CMDRELAY_PASS_TO_DST,
                     (sizeof(RSP) + pMsg->hdr.length - 2),
                     channel);
    if (rsp != NULL) {
        memcpy(rsp->addr, g_bt_addr.val, sizeof(g_bt_addr));
        //rsp->dst_type = RACE_RELAY_CHANNEL_TYPE_BT;
        //rsp->dst_id = RACE_RELAY_CHANNEL_ID_BLE;
        memcpy(&(rsp->race_cmd_rsp.hdr), &(pMsg->hdr), RACE_CMD_HDR_LEN);
        memcpy(rsp->race_cmd_rsp.payload, pMsg->payload, pMsg->hdr.length - 2);
        LOG_INF("[relay_cmd][relay_dbg] agent flush relay rsp id: 0x%04X, len:%d\n", pMsg->hdr.id, pMsg->hdr.length);

        if (pMsg->hdr.length < 890) {
            ret = race_flush_packet((void *)rsp, channel);
            if (ret != RACE_STATUS_OK) {
                LOG_INF("[relay_cmd] agent flush relay rsp FAIL \n");
            }
        } else {
            race_send_pkt_t* pSndPkt;
            uint32_t port_handle, ret_size, size;
            uint8_t *ptr;
            pSndPkt = race_pointer_cnv_pkt_to_send_pkt((void *)rsp);
            port_handle = race_get_port_handle_by_channel_id(channel);
            ret_size = race_port_send_data(port_handle, (uint8_t*)&pSndPkt->race_data, pSndPkt->length);

            size = pSndPkt->length;
            ptr = (uint8_t*)&pSndPkt->race_data;
            size -= ret_size;
            ptr += ret_size;
            while(size > 0) {
                ret_size = race_port_send_data(port_handle, ptr, size);
                size -= ret_size;
                ptr += ret_size;
            }
            race_mem_free(pSndPkt);
        }
    } else {
        LOG_INF("[relay_cmd] race_cmd_relay_rsp_hdlr malloc FAIL \n");
    }
}

void race_cmd_relay_bt_relay_msg_process(race_general_msg_t *msg)
{
    race_ralay_bt_packet_t *packet = (race_ralay_bt_packet_t *)msg->msg_data;

    LOG_INF("[relay_cmd] race_relay_process, race_id 0x%04X, channel %d, type %d, race_len %d",
            packet->cmd.hdr.id, packet->channel_id, packet->relay_type, packet->cmd.hdr.length);

    if (msg == NULL || msg->msg_data == NULL) {
        LOG_INF("[relay_cmd] race_relay_process, data null");
        return;
    }

    if (packet->relay_type == RACE_CMD_RELAY_FROM_AGENT) {
        race_cmd_relay_bt_req_hdlr(&(packet->cmd), packet->channel_id);
    } else if (packet->relay_type == RACE_CMD_RSP_FROM_PARTNER) {
        race_cmd_relay_bt_rsp_hdlr(&(packet->cmd), packet->channel_id);
    }

    race_mem_free(msg->msg_data);
}

static void* RACE_CmdHandler_relay_bt_query_state(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        uint8_t channel_type;
        uint8_t channel_id;
    }PACKED RSP;

    RSP *pEvt = RACE_ClaimPacket((uint8_t)RACE_TYPE_RESPONSE,
                                      (uint16_t)RACE_CMDRELAY_GET_AVA_DST,
                                      (uint16_t)sizeof(RSP),
                                      channel_id);

    if (pEvt) {
        pEvt->channel_type = RACE_RELAY_CHANNEL_TYPE_BT;
        pEvt->channel_id = RACE_RELAY_CHANNEL_ID_BLE;
    }
    return pEvt;
}

static void* RACE_CmdHandler_relay_bt_pass_to_dst(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    uint16_t data_len;

    typedef struct {
        RACE_COMMON_HDR_STRU hdr;
        //uint8_t dst_type;
        //uint8_t dst_id;
        uint8_t addr[6];
        race_pkt_t sub_race_cmd;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    //uint8_t data[6];
    CMD *pCmd = (CMD *)pCmdMsg;

    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                 RACE_TYPE_RESPONSE,
                                 RACE_CMDRELAY_PASS_TO_DST,
                                 sizeof(RSP),
                                 channel_id);

    //race_recipient_type_enum recipient_type = race_recipient_type_convt(pCmd->recipient);
    memset(g_bt_addr.val, 0, sizeof(g_bt_addr));
    LOG_INF("race_debug addr:%x,%x,%x,%x,%x,%x",pCmd->addr[0], pCmd->addr[1],pCmd->addr[2],pCmd->addr[3],pCmd->addr[4],pCmd->addr[5]);
    memcpy(g_bt_addr.val, pCmd->addr, sizeof(g_bt_addr));
    g_race_bt_relay_channel = race_get_channel_id_by_conn_address(&g_bt_addr);
    LOG_INF("race_debug g_race_bt_relay_channel  = %x", g_race_bt_relay_channel);
    if (pEvt != NULL) {
        bool ret = FALSE;

        data_len = pCmd->hdr.length - 8;/*race id length 2 bytes + 6 bytes addr*/
        ret = race_relay_send_bt(&(pCmd->sub_race_cmd), data_len, channel_id, RACE_CMD_RELAY_FROM_AGENT);

        pEvt->status = ret ? RACE_ERRCODE_SUCCESS : RACE_ERRCODE_FAIL;
    }
    return pEvt;
}


void* RACE_CmdHandler_RELAY_RACE_CMD_BT(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    LOG_INF("RACE_CmdHandler_RELAY_RACE_CMD, type[0x%X], id[0x%X]", pCmdMsg->hdr.type, pCmdMsg->hdr.id);

    if (pCmdMsg->hdr.type == RACE_TYPE_COMMAND ||
        pCmdMsg->hdr.type == RACE_TYPE_COMMAND_WITHOUT_RSP) {

        switch (pCmdMsg->hdr.id) {
            case RACE_CMDRELAY_GET_AVA_DST:
               return  RACE_CmdHandler_relay_bt_query_state((PTR_RACE_COMMON_HDR_STRU)&(pCmdMsg->hdr), length, channel_id);
            case RACE_CMDRELAY_PASS_TO_DST:
                return RACE_CmdHandler_relay_bt_pass_to_dst((PTR_RACE_COMMON_HDR_STRU)pCmdMsg , length, channel_id);
            case RACE_CMDRELAY_RELAY:
                race_relay_bt_callback(pCmdMsg, length, channel_id);
                return NULL;
            default:
                break;
        }
    }
    return NULL;
}


static void race_relay_bt_callback(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    race_general_msg_t msg_queue_item;
    race_ralay_bt_packet_t *packet = (race_ralay_bt_packet_t *)pCmdMsg->payload;
    g_race_bt_relay_channel = channel_id;
    LOG_INF("race_debug race_relay_bt_callback g_race_bt_relay_channel:%x",g_race_bt_relay_channel);
    if (length != packet->cmd.hdr.length + 8) {
        LOG_INF("race_relay_bt_callback(), packet->cmd.hdr.length %d, len %d", packet->cmd.hdr.length, length);
        return;
    }

    msg_queue_item.dev_t = RACE_INVALID_PORT;
    msg_queue_item.msg_id = MSG_ID_RACE_LOCAL_RELAY_BT_RACE_CMD;
    msg_queue_item.msg_data = race_mem_alloc(pCmdMsg->hdr.length - 2);

    if (msg_queue_item.msg_data == NULL) {
        LOG_INF("race_relay_bt_callback, msg_data null");
        return;
    }
    memcpy(msg_queue_item.msg_data, pCmdMsg->payload, pCmdMsg->hdr.length - 2);
    race_send_msg(&msg_queue_item);

    return;
}
#endif
