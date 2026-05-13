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

#ifdef RACE_GPIO_CMD_ENABLE
#include "race_cmd_gpio.h"
#include "hal_gpio.h"
#include "hal_gpio_internal.h"
#include "hal.h"
#include "mux.h"


void *RACE_CmdHandler_gpio_get_info(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t  gpio_num;
    } PACKED CMD;

    typedef struct {
        uint8_t gpio_num;
        uint8_t gpio_mode;
        uint8_t gpio_dir;          /*0:input   1:output*/
        uint8_t gpio_dout;         /*0:low   1:high*/
        uint8_t gpio_pull_type;    /*0:disable pull  1:pull up   2:pull down  */
        uint8_t gpio_driving;
        uint8_t gpio_din;          /*0:low   1:high*/
    } PACKED RSP;

    gpio_state_t gpio_state;

    CMD *pCmd = (CMD *)pCmdMsg;
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_GPIO_CMD_GET,
                                      sizeof(RSP),
                                      channel_id);

    if (pEvt != NULL) {
        gpio_get_state((hal_gpio_pin_t)pCmd->gpio_num, &gpio_state);
        pEvt->gpio_num       = pCmd->gpio_num;
        pEvt->gpio_mode      = gpio_state.mode;
        pEvt->gpio_dir       = gpio_state.dir;
        pEvt->gpio_dout      = gpio_state.dout;
        pEvt->gpio_pull_type = gpio_state.pull_type;
        pEvt->gpio_driving   = gpio_state.current_type;
        pEvt->gpio_din       = gpio_state.din;
    }

    return pEvt;
}


void *RACE_CmdHandler_gpio_set_info(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t gpio_num;
        uint8_t gpio_mode;
        uint8_t gpio_dir;         /*0:input   1:output*/
        uint8_t gpio_dout;        /*0:low     1:high*/
        uint8_t gpio_pull_type;   /*0:disable pull  1:pull up   2:pull down */
        uint8_t gpio_driving;
    } PACKED CMD;

    typedef struct {
        uint8_t gpio_num;
        uint8_t gpio_mode;
        uint8_t gpio_dir;         /*0:input   1:output*/
        uint8_t gpio_dout;        /*0:low   1:high*/
        uint8_t gpio_pull_type;   /*0:disable pull  1:pull up   2:pull down  */
        uint8_t gpio_driving;
        uint8_t gpio_din;         /*0:low   1:high*/
    } PACKED RSP;

    gpio_state_t gpio_state;

    CMD *pCmd = (CMD *)pCmdMsg;
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_GPIO_CMD_SET,
                                      sizeof(RSP),
                                      channel_id);

    if (pEvt != NULL) {
        hal_pinmux_set_function((hal_gpio_pin_t)pCmd->gpio_num, pCmd->gpio_mode);
        hal_gpio_set_direction((hal_gpio_pin_t)pCmd->gpio_num, pCmd->gpio_dir);
        hal_gpio_set_output((hal_gpio_pin_t)pCmd->gpio_num, (hal_gpio_data_t)pCmd->gpio_dout);

        switch (pCmd->gpio_pull_type) {
            case 0:
                hal_gpio_disable_pull((hal_gpio_pin_t)pCmd->gpio_num);
                break;
            case 1:
                hal_gpio_pull_up((hal_gpio_pin_t)pCmd->gpio_num);
                break;
            case 2:
                hal_gpio_pull_down((hal_gpio_pin_t)pCmd->gpio_num);
                break;
            default:
                break;
        }

        hal_gpio_set_driving_current((hal_gpio_pin_t)pCmd->gpio_num, (hal_gpio_driving_current_t)pCmd->gpio_driving);

        gpio_get_state((hal_gpio_pin_t)pCmd->gpio_num, &gpio_state);
        pEvt->gpio_num       = pCmd->gpio_num;
        pEvt->gpio_mode      = gpio_state.mode;
        pEvt->gpio_dir       = gpio_state.dir;
        pEvt->gpio_dout      = gpio_state.dout;
        pEvt->gpio_pull_type = gpio_state.pull_type;
        pEvt->gpio_driving   = gpio_state.current_type;
        pEvt->gpio_din       = gpio_state.din;
    }

    return pEvt;
}



void *RACE_CmdHandler_gpio(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    (void)length;

    LOG_INF("RACE_CmdHandler_gpio, type[0x%X], race_id[0x%X], channel_id[%d]",
                     pCmdMsg->hdr.type, pCmdMsg->hdr.id, channel_id);

    if (pCmdMsg->hdr.type == RACE_TYPE_COMMAND) {
        switch (pCmdMsg->hdr.id) {
            case RACE_GPIO_CMD_GET: //0x30E6
                return RACE_CmdHandler_gpio_get_info((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), channel_id);
            case RACE_GPIO_CMD_SET: //0x30E7
                return RACE_CmdHandler_gpio_set_info((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), channel_id);
            default:
                break;
        }
    }

    return NULL;
}

#endif /* RACE_GPIO_CMD_ENABLE */
#endif
