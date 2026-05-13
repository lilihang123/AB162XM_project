/* Copyright Statement:
 *
 * (C) 2020  Airoha Technology Corp. All rights reserved.
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

#ifdef RACE_OFFLINE_DUMP_CMD_ENABLE
#include "hal.h"
#include "race_util.h"
#include "offline_dump.h"
#include "race_cmd_offline_dump.h"

////////////////////////////////////////////////////////////////////////////////
// FUNCTION DECLARATIONS ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void *RACE_QUERY_OFFLINE_DUMP_REGION_INFO_HDR(ptr_race_pkt_t pCmdMsg, uint8_t channel_id)
{
    offline_dump_status_t ret;
    uint32_t region_idenx;
    uint32_t min_seq, max_seq;
    typedef struct {
        race_pkt_t Hdr;
        uint8_t  region_type;
    } PACKED THIS_RACE_CMD_STRU;

    typedef struct {
        uint8_t  status;
        uint8_t  region_type;
        uint32_t res_min_seq;
        uint32_t res_max_seq;
    } PACKED RSP;

    THIS_RACE_CMD_STRU *pThisCmd = (THIS_RACE_CMD_STRU *)pCmdMsg;
    RSP *pEvt = RACE_ClaimPacket(RACE_TYPE_RESPONSE, pCmdMsg->hdr.id, sizeof(RSP), channel_id);
    if (pEvt == NULL) {
        return (void *)pEvt;
    }

    region_idenx = pThisCmd->region_type;
    pEvt->region_type       = region_idenx;
    pEvt->res_min_seq       = 0;
    pEvt->res_max_seq       = 0;

    /* region type check */
    if (region_idenx >= OFFLINE_REGION_MAX) {
        pEvt->status = RACE_ERRCODE_FAIL;
        return (void *)pEvt;
    }

    ret = offline_dump_region_query_seq_range(region_idenx, &min_seq, &max_seq);
    if (ret != OFFLINE_STATUS_OK) {
        pEvt->status = RACE_ERRCODE_FAIL;
    } else {
        pEvt->status            = RACE_ERRCODE_SUCCESS;
        pEvt->region_type       = region_idenx;
        pEvt->res_min_seq       = min_seq;
        pEvt->res_max_seq       = max_seq;
    }
    LOG_INF("OFFLINE DUMP: query_seq_range ret:%d [0:pass other:fail] type:%d min:%d max:%d",
                        ret, pEvt->region_type, pEvt->res_min_seq, pEvt->res_max_seq);

    return (void *)pEvt;
}

void *RACE_QUERY_OFFLINE_DUMP_REGION_ADDRESS_HDR(ptr_race_pkt_t pCmdMsg, uint8_t channel_id)
{
    offline_dump_status_t ret;
    uint32_t region_idenx;
    uint32_t min_seq, max_seq, current_seq;
    uint32_t start_addr, total_length;
    typedef struct {
        race_pkt_t Hdr;
        uint8_t  region_type;
        uint32_t dump_idenx;
    } PACKED THIS_RACE_CMD_STRU;

    typedef struct {
        uint8_t  status;
        uint8_t  region_type;
        uint32_t block_length;
        uint32_t dump_address;
    } PACKED RSP;

    THIS_RACE_CMD_STRU *pThisCmd = (THIS_RACE_CMD_STRU *)pCmdMsg;
    RSP *pEvt = RACE_ClaimPacket(RACE_TYPE_RESPONSE, pCmdMsg->hdr.id, sizeof(RSP), channel_id);
    if (pEvt == NULL) {
        return (void *)pEvt;
    }

    region_idenx = pThisCmd->region_type;
    pEvt->region_type       = region_idenx;
    pEvt->block_length      = 0x0;
    pEvt->dump_address      = 0x0;

    /* region type check */
    if (region_idenx >= OFFLINE_REGION_MAX) {
        pEvt->status = RACE_ERRCODE_FAIL;
        return (void *)pEvt;
    }

    ret = offline_dump_region_query_seq_range(region_idenx, &min_seq, &max_seq);
    if (ret != OFFLINE_STATUS_OK) {
        pEvt->status = RACE_ERRCODE_FAIL;
        return (void *)pEvt;
    }

    if ((pThisCmd->dump_idenx > max_seq) || (pThisCmd->dump_idenx < min_seq)) {
        pEvt->status = RACE_ERRCODE_FAIL;
        return (void *)pEvt;
    } else {
        current_seq = pThisCmd->dump_idenx;
    }

    ret = offline_dump_region_query_by_seq(region_idenx, current_seq, &start_addr, &total_length);
    if (ret == OFFLINE_STATUS_OK) {
        pEvt->status            = RACE_ERRCODE_SUCCESS;
        pEvt->region_type       = region_idenx;
        pEvt->block_length      = total_length;
        pEvt->dump_address      = start_addr;
    } else {
        pEvt->status = RACE_ERRCODE_FAIL;
    }
    LOG_INF("OFFLINE DUMP: query_by_seq ret:%d [0:pass other:fail] type:%d length:%d address:0x%08x",
                        ret, pEvt->region_type, pEvt->block_length, pEvt->dump_address);

    return (void *)pEvt;
}

void *RACE_GET_EXCEPTION_LOG_HDR(ptr_race_pkt_t pCmdMsg, uint8_t channel_id)
{
    typedef struct {
        uint8_t  status;
        uint32_t data_length;
        uint32_t data_address;
    } PACKED RSP;

    offline_dump_status_t ret;
    uint32_t min_seq = 0, max_seq = 0;
    uint32_t start_addr = 0, total_length = 0;

    RSP *pEvt = RACE_ClaimPacket(RACE_TYPE_RESPONSE, pCmdMsg->hdr.id, sizeof(RSP), channel_id);
    if (pEvt) {
        ret = offline_dump_region_query_seq_range(OFFLINE_REGION_EXCEPTION_LOG, &min_seq, &max_seq);
        LOG_INF("Offline dump: query ret:%d [0:pass other:fail] min:%d max:%d", ret, min_seq, max_seq);
#ifdef MTK_MINIDUMP_ENABLE
        {
            uint32_t minidump_seq = 0;
            exception_status_t minidump_qurey_status;
            minidump_qurey_status = exception_minidump_region_query_latest_index(&minidump_seq);
            LOG_INF("Offline dump: mini ret:%d [0:pass other:fail] min:%d max:%d", minidump_qurey_status, minidump_seq);
            if (minidump_qurey_status == EXCEPTION_STATUS_OK) {
                minidump_seq = minidump_seq - 1;
                if (minidump_seq >= min_seq && minidump_seq <= max_seq) {
                    max_seq = minidump_seq;
                }
            }
        }
#endif
        if (ret == OFFLINE_STATUS_OK) {
            offline_dump_region_query_by_seq(OFFLINE_REGION_EXCEPTION_LOG, max_seq, &start_addr, &total_length);
            pEvt->status        = RACE_ERRCODE_SUCCESS;
            pEvt->data_address  = start_addr;
            pEvt->data_length   = total_length;
            LOG_INF("Offline dump: dump max_seq:%d start_addr:%d len:%d", max_seq, start_addr, total_length);
        } else {
            pEvt->status        = RACE_ERRCODE_FAIL;
            pEvt->data_address  = 0;
            pEvt->data_length   = 0;
        }
        LOG_INF("OFFLINE DUMP: dump max_seq:%d start_addr:%d len:%d", max_seq, start_addr, total_length);
    }

    return (void *)pEvt;
}

void *RACE_OFFLINE_SET_UNIX_TIME_HDR(ptr_race_pkt_t pCmdMsg, uint8_t channel_id)
{
    typedef struct {
        race_pkt_t Hdr;
        uint32_t  set_unix_time;
    } PACKED THIS_RACE_CMD_STRU;

    typedef struct {
        uint8_t  status;
        uint32_t read_unix_time;
    } PACKED RSP;

    THIS_RACE_CMD_STRU *pThisCmd = (THIS_RACE_CMD_STRU *)pCmdMsg;
    RSP *pEvt = RACE_ClaimPacket(RACE_TYPE_RESPONSE, pCmdMsg->hdr.id, sizeof(RSP), channel_id);

    if (pEvt) {
        LOG_INF("RACE_OFFLINE_SET_UNIX_TIME_HDR Epoch Time[%d] !!! ", pThisCmd->set_unix_time);
        if (offline_dump_set_rtc_time_unix(pThisCmd->set_unix_time) == true) {
            pEvt->status = RACE_ERRCODE_SUCCESS;
            pEvt->read_unix_time = pThisCmd->set_unix_time;
        } else {
            pEvt->status = RACE_ERRCODE_FAIL;
            pEvt->read_unix_time = 0;
        }
    }

    return (void *)pEvt;
}

void *RACE_CmdHandler_Offline_Dump(ptr_race_pkt_t pRaceHeaderCmd, uint16_t Length, uint8_t channel_id)
{
    LOG_INF("RACE_CmdHandler_Offline_Dump, cmd[0x%x], ch[%d]", pRaceHeaderCmd->hdr.id, channel_id);

    void *ptr = NULL;
    switch (pRaceHeaderCmd->hdr.id) {
        case RACE_QUERY_OFFLINE_DUMP_REGION_INFO: { //0x1E04
            ptr = RACE_QUERY_OFFLINE_DUMP_REGION_INFO_HDR(pRaceHeaderCmd, channel_id);
        } break;

        case RACE_QUERY_OFFLINE_DUMP_REGION_ADDRESS: { //0x1E05
            ptr = RACE_QUERY_OFFLINE_DUMP_REGION_ADDRESS_HDR(pRaceHeaderCmd, channel_id);
        } break;

        case RACE_BOOTREASON_OFFLINE_LOG_GET: { //0x1E06
            ptr = RACE_GET_EXCEPTION_LOG_HDR(pRaceHeaderCmd, channel_id);
        } break;

        case RACE_ID_OFFLINE_ASSERT: { //0x1E07
            /* Stop HWMAC */
            *(volatile uint32_t*)0xA0010344 |= 2;
            assert(0);
        } break;

        case RACE_OFFLINE_SET_UNIX_TIME: { //0x1E16
            ptr = RACE_OFFLINE_SET_UNIX_TIME_HDR(pRaceHeaderCmd, channel_id);
        } break;

        default: {
            LOG_ERR("unknown system race cmd, cmd_id[0x%X]", pRaceHeaderCmd->hdr.id);
        } break;
    }
    return ptr;
}

#endif /* RACE_OFFLINE_DUMP_CMD_ENABLE */
#endif
