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

#ifdef RACE_AIOADC_CMD_ENABLE
#include "hal.h"
#include "mux.h"
#include "hal_aioadc.h"
#include "race_cmd_aioadc.h"

#include "hal_gpio.h"
#include "hal_gpio_internal.h"
#if defined(AIR_GM10P_ENABLE) || defined(CONFIG_AIR_GAS_GAUGE)
#include "battery_temperature.h"
#endif

void *RACE_CmdHandler_aioadc_get_temp_sensor(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint8_t channel_id)
{
    typedef struct {
        uint8_t  status;
        int16_t temperature;
        int16_t adc_data;
        int16_t opt_data;
    } PACKED RSP;

    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_AIOADC_CMD_GET_TEMP_SENSOR,
                                      sizeof(RSP),
                                      channel_id);
    if(pEvt!=NULL)
    {
        LOG_INF("race sd adc HQA tempsensor");
        hal_aioadc_init(HAL_AIOADC_CH_0,HAL_AIOADC_MODE_TEMP_SENSOR,NULL);

        /*pinmux set adc function*/
        hal_pinmux_set_function(25,11);
        printk("0x420d0030==%08X:\n", *(volatile uint32_t *)(0x420d0030));

        int16_t adc_data;
        int16_t opt_data;
        int16_t temp_data;
        hal_aioadc_get_tempsensor(HAL_AIOADC_CH_0,&adc_data,&opt_data,&temp_data);
        pEvt->status = 0;
        pEvt->temperature = temp_data;
        pEvt->adc_data = adc_data;
        pEvt->opt_data = opt_data;
        printk("tempsensor mode data= %d ,adc_data=%d ,opt_data = %d \r\n",temp_data,adc_data,opt_data);
        hal_aioadc_deinit();
    }
    return pEvt;
}

void *RACE_CmdHandler_aioadc_get_adc_value(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t  adc_ch;
    } PACKED CMD;

    typedef struct {
        uint8_t  status;
        uint8_t  adc_ch;
        int16_t  adc_data;
    } PACKED RSP;

    CMD *pCmd = (CMD *)pCmdMsg;
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_AIOADC_CMD_GET_ADC,
                                      sizeof(RSP),
                                      channel_id);
    if(pEvt!=NULL)
    {
        LOG_INF("race sd adc get adc");
        hal_aioadc_ch_en_t adc_ch = (hal_aioadc_ch_en_t)pCmd->adc_ch;
        hal_aioadc_init(adc_ch,HAL_AIOADC_MODE_SE_0,NULL);

        /*pinmux set adc function*/
        hal_pinmux_set_function((25+adc_ch),11);
        printk("0x420d0030==%08X:\n", *(volatile uint32_t *)(0x420d0030));

        /*for debug*/
        // hal_aioadc_get_voltage(adc_ch,HAL_AIOADC_MODE_SE_0);

        int16_t adc_data;
        adc_data = hal_aioadc_read_data_polling(adc_ch);
        pEvt->status = 0;
        pEvt->adc_ch = adc_ch;
        pEvt->adc_data = adc_data;
        printk("race get adc_ch=%d ,adc_data=%d\r\n",adc_ch,adc_data);
        hal_aioadc_deinit();
    }
    return pEvt;
}

void *RACE_CmdHandler_aioadc_get_vbat(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint8_t channel_id)
{
    typedef struct {
        uint8_t  status;
        int16_t  vbat;
    } PACKED RSP;

    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_AIOADC_CMD_GET_VBAT,
                                      sizeof(RSP),
                                      channel_id);
    if(pEvt!=NULL)
    {
        LOG_INF("race sd adc get vbat");
        hal_aioadc_init(HAL_AIOADC_CH_0,HAL_AIOADC_MODE_VBAT,NULL);

        /*pinmux set adc function*/
        hal_pinmux_set_function((25),11);
        printk("0x420d0030==%08X:\n", *(volatile uint32_t *)(0x420d0030));

        int16_t vbat_data;
        vbat_data = hal_aioadc_get_voltage(HAL_AIOADC_CH_0,HAL_AIOADC_MODE_VBAT);
        pEvt->status = 0;
        pEvt->vbat = vbat_data;
        printk("race get vbat_data=%d\r\n",vbat_data);
        hal_aioadc_deinit();
    }
    return pEvt;
}

#if defined(AIR_GM10P_ENABLE) || defined(CONFIG_AIR_GAS_GAUGE)
void *RACE_CmdHandler_system_temperature(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint8_t channel_id)
{
    // Your implementation here
    // 05 5a 03 00 80 30 00
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t  adc_ch;
    } PACKED CMD;

    typedef struct {
        uint8_t  status;
        uint8_t  adc_ch;
        int16_t  temprature_data;
    } PACKED RSP;

    int16_t temprature = 0;
    CMD *pCmd = (CMD *)pCmdMsg;
    hal_aioadc_ch_en_t adc_ch = (hal_aioadc_ch_en_t)pCmd->adc_ch;
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_AIOADC_CMD_GET_SYS_TEMPERATURE,
                                      sizeof(RSP),
                                      channel_id);
    enGetBatteryTempReturn ret = battery_get_temperature(&temprature, adc_ch);
    if(!ret)
    {
        pEvt->status = 0;
    }
    else
    {
        pEvt->status = 1;
    }
    pEvt->adc_ch = adc_ch;
    pEvt->temprature_data = temprature;
    return pEvt;
}
#endif

void *RACE_CmdHandler_aioadc(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    (void)length;

    LOG_INF("RACE_CmdHandler_aioadc, type[0x%X], race_id[0x%X], channel_id[%d]",
                     pCmdMsg->hdr.type, pCmdMsg->hdr.id, channel_id);

    if (pCmdMsg->hdr.type == RACE_TYPE_COMMAND) {
        switch (pCmdMsg->hdr.id) {
            case RACE_AIOADC_CMD_GET_TEMP_SENSOR: //0x307D
                return RACE_CmdHandler_aioadc_get_temp_sensor((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), channel_id);
            case RACE_AIOADC_CMD_GET_ADC: //0x307E
                return RACE_CmdHandler_aioadc_get_adc_value((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), channel_id);
            case RACE_AIOADC_CMD_GET_VBAT: //0x307F
                return RACE_CmdHandler_aioadc_get_vbat((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), channel_id);
#if defined(AIR_GM10P_ENABLE) || defined(CONFIG_AIR_GAS_GAUGE)
            case RACE_AIOADC_CMD_GET_SYS_TEMPERATURE: //0x3080
                return RACE_CmdHandler_system_temperature((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), channel_id);
#endif
            default:
                break;
        }
    }

    return NULL;
}

#endif /* RACE_AIOADC_CMD_ENABLE */
#endif