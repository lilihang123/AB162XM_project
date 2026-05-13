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
/* Airoha restricted information */

#include "race_cmd_feature.h"
#ifdef AIR_RACE_SET_FACTORY_MODE
#include "race_xport.h"
#include "race_cmd.h"
#include "race_cmd_factory_mode.h"
#include "race_util.h"
void* RACE_CmdHandler_Factory_Mode(ptr_race_pkt_t pRaceHeaderCmd, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        uint8_t status;
    } PACKED RSP;

    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t mode;
    } PACKED CMD;

    CMD *pcmd = (CMD *)pRaceHeaderCmd;
    LOG_INF("race factory mod:%x, channel_id:%x", pcmd->mode, channel_id);

    if (!RACE_PORT_IS_UART(channel_id)) {
        LOG_INF("race channel id wrong");
        return NULL;
    }

    if (pRaceHeaderCmd->hdr.type == RACE_TYPE_COMMAND) {
        RSP *pEvt = RACE_ClaimPacket(RACE_TYPE_RESPONSE, pRaceHeaderCmd->hdr.id, sizeof(RSP), channel_id);
        if (pEvt) {
            if (pcmd->mode == 0x31 || pcmd->mode == 0x30) {
                race_set_factory_mode(pcmd->mode);
                pEvt->status = RACE_ERRCODE_SUCCESS;
            } else {
                pEvt->status = RACE_ERRCODE_FAIL;
            }

        }
        return pEvt;
    }

    return NULL;
}
#endif

