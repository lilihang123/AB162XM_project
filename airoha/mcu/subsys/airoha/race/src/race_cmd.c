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


#include "race_cmd_feature.h"
#include <zephyr/logging/log_core.h>
#include <zephyr/logging/log.h>
#include "race_util.h"
#include "stdint.h"
#include "hal_uart.h"
 #include "race_cmd.h"
#include "race_xport.h"
#include "race_core.h"
#include "race_cmd_nvkey.h"
#include "race_cmd_storage.h"
#include "race_cmd_fota.h"
#include "race_cmd_uart.h"
#include "race_cmd_crystal_trim.h"
#include "race_fota_util.h"
#ifdef AIR_BTD_IC_PREMIUM_G1
#include "race_cmd_system.h"
#include "race_cmd_offline_dump.h"
#include "race_cmd_gpio.h"
#include "race_cmd_pwm.h"
 #include "race_cmd_i2c_master.h"
#include "race_cmd_i3c_master.h"
#include "race_cmd_spi_master.h"
#include "race_cmd_aioadc.h"
#include "race_cmd_key_event.h"
#include "race_cmd_audio.h"
#endif
#include <string.h>
#include <stdio.h>
#ifdef RACE_BT_ENABLE
#include "race_bt.h"
#endif
#ifdef RACE_CLOCK_CMD_ENABLE
#include "race_cmd_clock.h"
#endif
#ifdef RACE_SLEEP_CONTROL_ENABLE
#include "race_cmd_sleep_control.h"
#endif /* RACE_SLEEP_CONTROL_ENABLE */
#ifdef RACE_WDT_CMD_ENABLE
#include "race_cmd_wdt.h"
#endif
#ifdef RACE_AUXADC_CMD_ENABLE
#include "race_cmd_auxadc.h"
#endif /* RACE_AUXADC_CMD_ENABLE */
#include "race_cmd_register.h"
#include "race_cmd_mainbin_dfu.h"
#include "air_logging.h"
#include "race_cmd_factory_mode.h"
#if CONFIG_AIR_RACE_RELAY_CMD_ENABLE
#include "race_cmd_relay_cmd_bt.h"
#endif

#define thisMOD "race_cmd"
#define thisMODULE race_cmd
LOG_MODULE_REGISTER(thisMODULE);


/* This range is reserved for customer use. */
#define RACE_ID_CUSTOM_BEGIN 0x0000
#define RACE_ID_CUSTOM_END 0x01FF

#ifdef AIR_RACE_SET_FACTORY_MODE
#define RACE_ID_FACTORY_MODE_BEGIN 0x0F93
#define RACE_ID_FACTORY_MODE_END 0x0F93
#endif

#define RACE_ID_FOTA_BEGIN 0x1C00
#ifdef AIR_FOTA_SRC_ENABLE
#define RACE_ID_FOTA_END 0x1C50
#else
#define RACE_ID_FOTA_END 0x1C1F
#endif

#define RACE_ID_GET_BDADDR_BEGIN 0x0CD5
#define RACE_ID_GET_BDADDR_END 0x0CD5

#define RACE_ID_GET_BATTERY_BEGIN 0x0CD6
#define RACE_ID_GET_BATTERY_END 0x0CD6

#define RACE_ID_NVKEY_BEGIN 0x0A00
#define RACE_ID_NVKEY_END 0x0AFF

#define RACE_ID_BLUETOOTH_BEGIN 0x3072
#define RACE_ID_BLUETOOTH_END 0x3075

#define RACE_ID_STORAGE_BEGIN  0x0400
#define RACE_ID_STORAGE_END  0x0433

#define RACE_ID_RG_RW_BEGIN 0x1680
#define RACE_ID_RG_RW_END 0x16ff

#define RACE_ID_2WIRE_RG_RW_BEGIN 0x0210
#define RACE_ID_2WIRE_RG_RW_END 0x0211

#ifdef RACE_SPI_MASTER_CMD_ENABLE
#define RACE_ID_SPI_MASTER_BEGIN 0x5000
#define RACE_ID_SPI_MASTER_END 0x5004
#endif

#ifdef RACE_I2C_MASTER_CMD_ENABLE
#define RACE_ID_I2C_MASTER_BEGIN 0x5008
#define RACE_ID_I2C_MASTER_END 0x5009
#endif

#ifdef RACE_I3C_MASTER_CMD_ENABLE
#define RACE_ID_I3C_MASTER_BEGIN 0x5010
#define RACE_ID_I3C_MASTER_END   0x5014
#endif

#ifdef RACE_UART_CMD_ENABLE
#define RACE_ID_UART_BEGIN 0x5020
#define RACE_ID_UART_END 0x5025
#endif

#ifdef AIR_BTD_IC_PREMIUM_G1
#ifdef RACE_AIOADC_CMD_ENABLE
#define RACE_ID_AIOADC_BEGIN 0x307D
#define RACE_ID_AIOADC_END 0x3080
#endif
#elif defined(AIR_BTD_IC_MANDATORY_G1)
#ifdef RACE_AUXADC_CMD_ENABLE
#define RACE_ID_AUXADC_BEGIN    0x307D
#define RACE_ID_AUXADC_END    0x307F
#endif
#endif

#ifdef RACE_KEY_EVENT_CMD_ENABLE
#define RACE_ID_KEY_EVENT_BEGIN 0x1100
#define RACE_ID_KEY_EVENT_END 0x1101
#endif

#ifdef RACE_OFFLINE_DUMP_CMD_ENABLE
#define RACE_ID_OFFLINE_DUMP_BEGIN 0x1E03
#define RACE_ID_OFFLINE_DUMP_END 0x1E07
#define RACE_ID_OFFLINE_DUMP_2_BEGIN 0x1E10
#define RACE_ID_OFFLINE_DUMP_2_END 0x1E1F
#endif

#ifdef RACE_PWM_CMD_ENABLE
#define RACE_ID_PWM_BEGIN 0x307C
#define RACE_ID_PWM_END 0x307C
#endif

#define RACE_ID_SYSTEM_BEGIN 0x0200
#define RACE_ID_SYSTEM_END 0x020A

#define RACE_ID_REG_I2C_CONTROL_BEGIN 0x020E
#define RACE_ID_REG_I2C_CONTROL_END 0x020F

#ifdef RACE_CLOCK_CMD_ENABLE
#define RACE_ID_CLOCK_BEGIN  _RACE_ID_CLOCK_BEGIN
#define RACE_ID_CLOCK_END    _RACE_ID_CLOCK_END
#endif

#ifdef RACE_CRYSTAL_TRIM_CMD_ENABLE
#define RACE_ID_CRYSTAL_TRIM_BEGIN  0x3076
#define RACE_ID_CRYSTAL_TRIM_END    0x3076
#endif

#ifdef RACE_SLEEP_CONTROL_ENABLE
#define RACE_ID_SLEEP_CONTROL_BEGIN 0x0220
#define RACE_ID_SLEEP_CONTROL_END 0x0221
#endif /* RACE_SLEEP_CONTROL_ENABLE */

#ifdef RACE_GPIO_CMD_ENABLE
#define RACE_ID_GPIO_BEGIN  0x30E6
#define RACE_ID_GPIO_END    0x30E7
#endif

#ifdef RACE_AUDIO_RACE_CMD_ENABLE
#define RACE_ID_AUDIO_BEGIN  0x3113
#define RACE_ID_AUDIO_END    0x3115
#endif

#if CONFIG_AIR_RACE_RELAY_CMD_ENABLE
#define RACE_ID_RELAY_BEGIN 0X0D00
#define RACE_ID_RELAY_END 0x0D02
#endif
#ifdef AIR_BTD_IC_MANDATORY_G1
__attribute__((weak)) void *RACE_CmdHandler_air_internal_group1(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    UNUSED(pCmdMsg);
    UNUSED(length);
    UNUSED(channel_id);
    return NULL;
}
#endif

const RACE_HANDLER race_handlers[] = {
#ifdef AIR_BTD_IC_MANDATORY_G1
    {RACE_ID_AIR_INTERNAL_GROUP1_BEGIN, RACE_ID_AIR_INTERNAL_GROUP1_END, RACE_CmdHandler_air_internal_group1},
#endif

#ifdef RACE_NVKEY_CMD_ENABLE
    {RACE_ID_NVKEY_BEGIN, RACE_ID_NVKEY_END, RACE_CmdHandler_NVKEY},
#endif
#ifdef RACE_UART_CMD_ENABLE
    {RACE_ID_UART_BEGIN, RACE_ID_UART_END, RACE_CmdHandler_uart},
#endif
    {RACE_ID_MB_DFU_BEGIN, RACE_ID_MB_DFU_END, race_cmd_handler_mb_dfu},
#ifdef RACE_CLOCK_CMD_ENABLE
    {RACE_ID_CLOCK_BEGIN, RACE_ID_CLOCK_END, RACE_CmdHandler_clock},
#endif
#ifdef RACE_CRYSTAL_TRIM_CMD_ENABLE
    {RACE_ID_CRYSTAL_TRIM_BEGIN, RACE_ID_CRYSTAL_TRIM_END,  RACE_CmdHandler_crystal_trim},
#endif
#ifdef RACE_SLEEP_CONTROL_ENABLE
    {RACE_ID_SLEEP_CONTROL_BEGIN, RACE_ID_SLEEP_CONTROL_END, RACE_CmdHandler_sleep_control},
#endif /* RACE_SLEEP_CONTROL_ENABLE */
#ifdef AIR_RACE_SET_FACTORY_MODE
    {RACE_ID_FACTORY_MODE_BEGIN, RACE_ID_FACTORY_MODE_END, RACE_CmdHandler_Factory_Mode},
#endif
#ifdef RACE_BT_ENABLE
    {RACE_ID_GET_BDADDR_BEGIN, RACE_ID_GET_BDADDR_END, RACE_CmdHandler_BLUETOOTH},
    {RACE_ID_BLUETOOTH_BEGIN, RACE_ID_BLUETOOTH_END, RACE_CmdHandler_BLUETOOTH},
#endif

#ifdef AIR_BTD_IC_MANDATORY_G1
#ifdef RACE_AUXADC_CMD_ENABLE
    {RACE_ID_AUXADC_BEGIN, RACE_ID_AUXADC_END, RACE_CmdHandler_auxadc},
#endif
#endif
#if CONFIG_AIR_RACE_RELAY_CMD_ENABLE
    {RACE_ID_RELAY_BEGIN, RACE_ID_RELAY_END, RACE_CmdHandler_RELAY_RACE_CMD_BT},
#endif

#ifdef RACE_FOTA_CMD_ENABLE
    {RACE_ID_FOTA_BEGIN, RACE_ID_FOTA_END, RACE_CmdHandler_FOTA},
    {RACE_ID_GET_BATTERY_BEGIN, RACE_ID_GET_BATTERY_END, RACE_CmdHandler_FOTA},
#endif

#ifdef RACE_STORAGE_CMD_ENABLE
    {RACE_ID_STORAGE_BEGIN, RACE_ID_STORAGE_END, race_cmdhdl_storage},
#endif
#ifdef AIR_BTD_IC_PREMIUM_G1
#ifdef RACE_RG_READ_WRITE_ENABLE
    {RACE_ID_RG_RW_BEGIN, RACE_ID_RG_RW_END, RACE_CmdHandler_RG_read_write},
    {RACE_ID_2WIRE_RG_RW_BEGIN, RACE_ID_2WIRE_RG_RW_END, RACE_CmdHandler_2wire_RG_read_write},
#endif
#ifdef RACE_I2C_MASTER_CMD_ENABLE
    {RACE_ID_I2C_MASTER_BEGIN, RACE_ID_I2C_MASTER_END, RACE_CmdHandler_i2c_master_send_and_receive},
#endif
#ifdef RACE_I3C_MASTER_CMD_ENABLE
    {RACE_ID_I3C_MASTER_BEGIN, RACE_ID_I3C_MASTER_END, RACE_CmdHandler_i3c_master},
#endif
#ifdef RACE_SPI_MASTER_CMD_ENABLE
    {RACE_ID_SPI_MASTER_BEGIN, RACE_ID_SPI_MASTER_END, RACE_CmdHandler_spi_master_send_and_receive},
#endif

#ifdef RACE_AIOADC_CMD_ENABLE
    {RACE_ID_AIOADC_BEGIN, RACE_ID_AIOADC_END, RACE_CmdHandler_aioadc},
#endif

#ifdef RACE_KEY_EVENT_CMD_ENABLE
    {RACE_ID_KEY_EVENT_BEGIN, RACE_ID_KEY_EVENT_END, RACE_CmdHandler_key_event},
#endif

#ifdef RACE_PWM_CMD_ENABLE
    {RACE_ID_PWM_BEGIN, RACE_ID_PWM_END, RACE_CmdHandler_pwm},
#endif
    {RACE_ID_SYSTEM_BEGIN, RACE_ID_SYSTEM_END, RACE_CmdHandler_System},
    {RACE_ID_REG_I2C_CONTROL_BEGIN, RACE_ID_REG_I2C_CONTROL_END, RACE_CmdHandler_System},
#ifdef RACE_OFFLINE_DUMP_CMD_ENABLE
    {RACE_ID_OFFLINE_DUMP_BEGIN, RACE_ID_OFFLINE_DUMP_END, RACE_CmdHandler_Offline_Dump},
    {RACE_ID_OFFLINE_DUMP_2_BEGIN, RACE_ID_OFFLINE_DUMP_2_END, RACE_CmdHandler_Offline_Dump},
#endif
#ifdef RACE_GPIO_CMD_ENABLE
    {RACE_ID_GPIO_BEGIN, RACE_ID_GPIO_END,  RACE_CmdHandler_gpio},
#endif
#ifdef RACE_AUDIO_RACE_CMD_ENABLE
    {RACE_ID_AUDIO_BEGIN, RACE_ID_AUDIO_END,  RACE_CmdHandler_audio},
#endif
#endif
};

static bool race_cmd_id_in_black_list(uint16_t id)
{
    if (((id) >= RACE_ID_SYSTEM_BEGIN && (id) <= RACE_ID_SYSTEM_END)
        || ((id) >= RACE_ID_REG_I2C_CONTROL_BEGIN && (id) <= RACE_ID_REG_I2C_CONTROL_END)
#ifdef RACE_CLOCK_CMD_ENABLE
        || ((id) >= RACE_ID_CLOCK_BEGIN && (id) <= RACE_ID_CLOCK_END)
#endif
#ifdef RACE_AUDIO_RACE_CMD_ENABLE
        || ((id) >= RACE_ID_AUDIO_BEGIN && (id) <= RACE_ID_AUDIO_END)
#endif
#ifdef RACE_SPI_MASTER_CMD_ENABLE
        || ((id) >= RACE_ID_SPI_MASTER_BEGIN && (id) <= RACE_ID_SPI_MASTER_END)
#endif
#ifdef RACE_I3C_MASTER_CMD_ENABLE
        || ((id) >= RACE_ID_I3C_MASTER_BEGIN && (id) <= RACE_ID_I3C_MASTER_END)
#endif
#ifdef RACE_UART_CMD_ENABLE
        || ((id) >= RACE_ID_UART_BEGIN && (id) <= RACE_ID_UART_BEGIN)
#endif
#ifdef RACE_CRYSTAL_TRIM_CMD_ENABLE
        || ((id) >= RACE_ID_CRYSTAL_TRIM_BEGIN && (id) <= RACE_ID_CRYSTAL_TRIM_END)
#endif
#ifdef RACE_GPIO_CMD_ENABLE
        || ((id) >= RACE_ID_GPIO_BEGIN && (id) <= RACE_ID_GPIO_END)
#endif
#ifdef RACE_I2C_MASTER_CMD_ENABLE
        || ((id) >= RACE_ID_I2C_MASTER_BEGIN && (id) <= RACE_ID_I2C_MASTER_END)
#endif
#ifdef RACE_PWM_CMD_ENABLE
        || ((id) >= RACE_ID_PWM_BEGIN && (id) <= RACE_ID_PWM_END)
#endif
        || ((id) >= RACE_ID_RG_RW_BEGIN && (id) <= RACE_ID_RG_RW_END)
        || ((id) >= RACE_ID_2WIRE_RG_RW_BEGIN && (id) <= RACE_ID_2WIRE_RG_RW_END)
#ifdef RACE_AIOADC_CMD_ENABLE
        || ((id) >= RACE_ID_AIOADC_BEGIN && (id) <= RACE_ID_AIOADC_END
#if defined(AIR_GM10P_ENABLE) || defined(CONFIG_AIR_GAS_GAUGE)
            && ((id) != RACE_AIOADC_CMD_GET_SYS_TEMPERATURE)
#endif
            )
#endif
        ) {
        return true;
    }
    return false;
}


/*******************************************************************************/
/*                      Global Variables                                      */
/*******************************************************************************/
//static Handler app_race_handler = NULL;
static uint32_t g_race_registered_table_number;
static RACE_HANDLER g_race_cm4_general_hdlr_tables[RACE_MAX_GNENERAL_TABLE_NUM];

void *RACE_ClaimPacket(uint8_t race_type, uint16_t race_id, uint16_t dat_len, uint8_t channel_id)
{
    race_send_pkt_t *pPacket = NULL;
    pPacket = (race_send_pkt_t *)race_mem_alloc(sizeof(race_send_pkt_t) + dat_len);
    //RACE_LOG_MSGID_I("RACE_ClaimPacket, race_type[0x%X], race_id[0x%X], dat_len[%d], channel_id[%d], pPacket[0x%X]", 5,
    //                 race_type, race_id, dat_len, channel_id, pPacket);

    if (pPacket != NULL) {
        pPacket->channel_id = channel_id;
        pPacket->length = sizeof(RACE_COMMON_HDR_STRU) + dat_len;
        pPacket->offset = 6;//OS_OFFSET_OF(RACE_IPC_STRU, payload);
        pPacket->reserve = 0xCC;

        pPacket->race_data.hdr.pktId.value = 0x05;
        pPacket->race_data.hdr.type = race_type;
        pPacket->race_data.hdr.length = sizeof(uint16_t) + dat_len;
        pPacket->race_data.hdr.id = race_id;

        return pPacket->race_data.payload;
    } else {
        return NULL;
    }
}

void *RACE_ClaimPacketAppID(uint8_t app_id, uint8_t race_type, uint16_t race_id, uint16_t dat_len, uint8_t channel_id)
{
    race_send_pkt_t *pPacket = NULL;
    pPacket = (race_send_pkt_t *)race_mem_alloc(sizeof(race_send_pkt_t) + dat_len);
    //RACE_LOG_MSGID_I("RACE_ClaimPacketAppID, race_type[0x%X], race_id[0x%X], dat_len[%d], channel_id[%d], pPacket[0x%X]", 5,
    //                 race_type, race_id, dat_len, channel_id, pPacket);

    if (pPacket != NULL) {
        pPacket->channel_id = channel_id;
        pPacket->length = sizeof(RACE_COMMON_HDR_STRU) + dat_len;
        pPacket->offset = 6;//OS_OFFSET_OF(RACE_IPC_STRU, payload);
        pPacket->reserve = 0xCC;

        pPacket->race_data.hdr.pktId.value = ((app_id << 4) | 0x05);
        pPacket->race_data.hdr.type = race_type;
        pPacket->race_data.hdr.length = sizeof(uint16_t) + dat_len;
        pPacket->race_data.hdr.id = race_id;

        return pPacket->race_data.payload;
    } else {
        return NULL;
    }
}


/* Input the pointer returned by RACE_ClaimPacket() or RACE_ClaimPacketAppID() */
void RACE_FreePacket(void *data)
{
    race_send_pkt_t *send_pkt = NULL;

    /* Convert payload pointer to the pointer points to the begining of the whole package. */
    send_pkt = race_pointer_cnv_pkt_to_send_pkt(data);

    //RACE_LOG_MSGID_I("RACE_FreePacket, send_pkt[0x%X]", 1, send_pkt);
    race_mem_free(send_pkt);
}

race_status_t RACE_Register_Handler(RACE_HANDLER *pHandler)
{
    if (g_race_registered_table_number == RACE_MAX_GNENERAL_TABLE_NUM) {
        return RACE_STATUS_REGISTRATION_FAILURE;
    } else if (!pHandler) {
        return RACE_STATUS_ERROR;
    }

    memcpy(&g_race_cm4_general_hdlr_tables[g_race_registered_table_number], pHandler, sizeof(RACE_HANDLER));
    g_race_registered_table_number++;

    return RACE_STATUS_OK;
}

#if (RACE_DEBUG_PRINT_ENABLE)
static uint8_t race_cmd_handle;
void race_dump_data(const uint8_t *data, int len, const char *log_msg)
{
    int real_len = len > 25 ? 25 : len;
    LOG_HEXDUMP_I(&race_cmd_handle, log_msg, data, real_len);
}

void race_dump(const uint8_t *data, race_debug_type_enum type)
{
    const char *str_log[RACE_DBG_MAX] = {
        "CMD",
        "EVT",
        "EVT_APP",
        "IF_RELAY",
        "FLUSH"};
    int length = (data[3] << 8) + data[2] + 4;
    if (type >= RACE_DBG_MAX) {
        return ;
    }
    race_dump_data(data, length, str_log[type]);
}
#endif


void *RACE_CmdHandler(race_pkt_t *pMsg, uint8_t channel_id)
{
    uint32_t i;

    void *ptr = NULL;

    if (!pMsg) {
        return NULL;
    }
    LOG_INF("RACE_CmdHandler, type[0x%X], id[0x%X], app_id[%d]", pMsg->hdr.type, pMsg->hdr.id, pMsg->hdr.pktId.field.app_id);

#if (RACE_DEBUG_PRINT_ENABLE)
    race_dump((uint8_t *)pMsg, RACE_DBG_CMD);
#endif

    switch (pMsg->hdr.type) {
        case RACE_TYPE_RESPONSE:
        case RACE_TYPE_NOTIFICATION:
            if (race_get_port_type_by_channel_id(channel_id) == RACE_SERIAL_PORT_TYPE_UART) {
                break;
            }
        case RACE_TYPE_COMMAND:
        case RACE_TYPE_COMMAND_WITHOUT_RSP: {
            for (i = 0; i < sizeof(race_handlers) / sizeof(RACE_HANDLER); i++) {
                if (pMsg->hdr.id >= race_handlers[i].id_start && pMsg->hdr.id <= race_handlers[i].id_end) {

#ifdef AIR_FOTA_SRC_ENABLE
                LOG_INF("RACE_CmdHandler, id_start[0x%X], id_end[0x%X], msg_id[%X]"
                , race_handlers[i].id_start, race_handlers[i].id_end, pMsg->hdr.id);
#endif
#ifdef AIR_RACE_SET_FACTORY_MODE
                /*in end user mode, customer can not access some race cmd id */
                if (false == race_get_factory_mode()) {
                    if (race_cmd_id_in_black_list(pMsg->hdr.id)) {
                        LOG_INF("RACE cmd in black list, id[0x%x]", pMsg->hdr.id);
                        break;
                    }
                }
#else
                if (race_cmd_id_in_black_list(pMsg->hdr.id)) {
                    LOG_INF("RACE cmd in black list, id[0x%x]", pMsg->hdr.id);
                    break;
                }
#endif

#ifdef RACE_FOTA_CMD_ENABLE
                #ifdef AIR_FOTA_SRC_ENABLE
                    if (pMsg->hdr.type == RACE_TYPE_COMMAND || pMsg->hdr.type == RACE_TYPE_COMMAND_WITHOUT_RSP) {
                #endif
                        if (RACE_APP_ID_FOTA == pMsg->hdr.pktId.field.app_id) {
                            RACE_ERRCODE ret = race_fota_cmd_preprocess(pMsg->hdr.id,
                                                                        pMsg->hdr.type,
                                                                        channel_id);
                            if (RACE_ERRCODE_SUCCESS != ret) {
                                break;
                            }
                        }
                #ifdef AIR_FOTA_SRC_ENABLE
                    }
                #endif
#endif /* RACE_FOTA_CMD_ENABLE */
                    ptr = race_handlers[i].handler(pMsg, pMsg->hdr.length, channel_id);

                    if (ptr) {
                        ptr = (void *)race_pointer_cnv_pkt_to_send_pkt(ptr);
#if (RACE_DEBUG_PRINT_ENABLE)
                        race_pkt_t      *pret;
                        race_send_pkt_t *psend;
                        psend = (race_send_pkt_t *)ptr;
                        pret = &psend->race_data;
                        race_dump((uint8_t *)pret, RACE_DBG_EVT);
#endif
                    } else if (pMsg->hdr.type == RACE_TYPE_COMMAND) {
                        //RACE_LOG_MSGID_W("RACE_CmdHandler, evt ptr null, id[0x%x]", 1, pMsg->hdr.id);
                    }
                    break;
                }
            }
            if (i == sizeof(race_handlers) / sizeof(RACE_HANDLER)) { //not found
                for (i = 0; i < g_race_registered_table_number; i++) {
                    if (pMsg->hdr.id >= g_race_cm4_general_hdlr_tables[i].id_start && pMsg->hdr.id <= g_race_cm4_general_hdlr_tables[i].id_end) {

                        ptr = g_race_cm4_general_hdlr_tables[i].handler(pMsg, pMsg->hdr.length, channel_id);

                        if (ptr) {
                            ptr = (void *)race_pointer_cnv_pkt_to_send_pkt(ptr);
#if (RACE_DEBUG_PRINT_ENABLE)
                            race_pkt_t      *pret;
                            race_send_pkt_t *psend;
                            psend = (race_send_pkt_t *)ptr;
                            pret = &psend->race_data;
                            race_dump((uint8_t *)pret, RACE_DBG_EVT_APP);
#endif
                        }
                        break;
                    }
                }

                if (i == g_race_registered_table_number) {
                    // RACE_LOG_MSGID_E("RACE_CmdHandler, handler not found, id[0x%x]", 1, pMsg->hdr.id);
                }
            }
#if 0
            if (i == sizeof(race_handlers) / sizeof(RACE_HANDLER)) { //not found
                if (app_race_handler) {
                    RACE_Send2Handler(pMsg, app_race_handler);
                } else {
                    PTR_RACE_PAYLOAD_STRU payload;
                    uint8_t *cptr = RACE_ClaimPacket(RACE_TYPE_RESPONSE, pRaceHeaderCmd->id, sizeof(uint8_t), pMsg->channel_id);
                    cptr[0] = RACE_ERRCODE_NOT_SUPPORT;
                    //PTR_RACE_IPC_STRU packet;
                    payload = OS_CONTAINER_OF(cptr, RACE_PAYLOAD_STRU, param);
                    ptr = (void *)OS_CONTAINER_OF(payload, RACE_IPC_STRU, payload);
                }
            }
#endif
            break;
        }

        default: {
            break;
        }
    }

    // We should free the memory.
    //OSMEM_Put(pMsg);
    return ptr;
}

bool race_cmd_is_to_remote(race_pkt_t *pMsg)
{
    bool ret = false;

#if defined (AIR_DUAL_CHIP_MIXING_MODE_ROLE_SLAVE_ENABLE) || defined (AIR_DCHS_MODE_SLAVE_ENABLE)
    if (pMsg->hdr.id == 0x2c82 || pMsg->hdr.id == 0x2c83) {
        if ((pMsg->payload[0] == 0x00) || (pMsg->payload[0] == 0x01)) {
            //RACE_LOG_MSGID_I("race_cosys slave APP, id[0x%x], module[%d]", 2, pMsg->hdr.id, pMsg->payload[0]);
            ret = true;
        }
    }
#endif

    return ret;
}
