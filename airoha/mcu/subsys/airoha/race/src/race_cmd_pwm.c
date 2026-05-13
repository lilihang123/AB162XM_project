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

#ifdef RACE_PWM_CMD_ENABLE
#include "race_cmd_pwm.h"
#include "hal_pwm.h"
#include "hal.h"
#include "mux.h"

void *RACE_CmdHandler_pwm_set_info(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t  pwm_channel;
        uint8_t  clock_source;
        uint32_t frequency;
        uint8_t  duty;
        uint8_t polarity;
        uint8_t onoff;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;
    hal_pwm_status_t status = 0;
    CMD *pCmd = (CMD *)pCmdMsg;
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_PWM_CMD_SET,
                                      sizeof(RSP),
                                      channel_id);

    if (pEvt != NULL) {
        if(pCmd->onoff){
            status = hal_pwm_init((hal_pwm_channel_t)pCmd->pwm_channel, pCmd->clock_source);
            if(status != 0){
                pEvt->status = 1;
            }
            status = hal_pwm_set_polarity((hal_pwm_channel_t)pCmd->pwm_channel, pCmd->polarity);
            if(status != 0){
                pEvt->status = 2;
            }
            status = hal_pwm_set_frequency_and_duty((hal_pwm_channel_t)pCmd->pwm_channel, pCmd->clock_source,pCmd->frequency,(float)(pCmd->duty)/100.0f);
            if(status != 0){
                pEvt->status = 3;
            }
            status = hal_pwm_start((hal_pwm_channel_t)pCmd->pwm_channel);
            if(status != 0){
                pEvt->status = 4;
            }
        }else{
            status = hal_pwm_stop((hal_pwm_channel_t)pCmd->pwm_channel);
            if(status != 0){
                pEvt->status = 1;
            }
            status = hal_pwm_deinit((hal_pwm_channel_t)pCmd->pwm_channel);
            if(status != 0){
                pEvt->status = 2;
            }
        }
    }
    return pEvt;
}



void *RACE_CmdHandler_pwm(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    (void)length;

    LOG_INF("RACE_CmdHandler_pwm, type[0x%X], race_id[0x%X], channel_id[%d]",
                     pCmdMsg->hdr.type, pCmdMsg->hdr.id, channel_id);

    if (pCmdMsg->hdr.type == RACE_TYPE_COMMAND) {
        switch (pCmdMsg->hdr.id) {
            case RACE_PWM_CMD_SET: //0x30E7
                return RACE_CmdHandler_pwm_set_info((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), channel_id);
            default:
                break;
        }
    }

    return NULL;
}

#endif /* RACE_GPIO_CMD_ENABLE */
#endif
