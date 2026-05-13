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

#ifdef RACE_KEY_EVENT_CMD_ENABLE
#include "hal.h"
#include "mux.h"
#include "race_cmd_key_event.h"
#include "hal_wdt.h"


/* SLEEP CONTROL RACE CMD */
enum {
    KEY_EVENT_POWER_OFF = 0x18,              /* CMD: 05 5A 04 00 01 11 18 00 */
    KEY_EVENT_REBOOT = 0x19,                 /* CMD: 05 5A 04 00 01 11 19 00 */
};

static void *RACE_CmdHandler_key_event_reboot(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint8_t channel_id)
{
    typedef struct {
        uint8_t  status;
    } PACKED RSP;

    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      KEY_EVENT_REBOOT,
                                      sizeof(RSP),
                                      channel_id);

    if (pEvt != NULL) {
        printk("RACE_CmdHandler_key_event_reboot\r\n");
        pEvt->status = 0;
        hal_wdt_software_reset();
    }

    return pEvt;
}

void *RACE_CmdHandler_key_event(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    (void)length;

    LOG_INF("RACE_CmdHandler_key_event, type[0x%X], race_id[0x%X], channel_id[%d]",
                     pCmdMsg->hdr.type, pCmdMsg->hdr.id, channel_id);

    switch (pCmdMsg->payload[0]) {
        case KEY_EVENT_POWER_OFF:
            /* CMD: 05 5A 04 00 01 11 18 00 */
            LOG_ERR("KEY_EVENT_POWER_OFF RACE CMD not implemented", 0);
            break;
        case KEY_EVENT_REBOOT:
            /* CMD: 05 5A 04 00 01 11 19 00 */
            return RACE_CmdHandler_key_event_reboot((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), channel_id);
        default:
            LOG_ERR("Unknown key event RACE CMD", 0);
            break;
    }

    return NULL;
}

#endif /* RACE_KEY_EVENT_CMD_ENABLE */
#endif
