/* Copyright Statement:
 *
 * (C) 2024  Airoha Technology Corp. All rights reserved.
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
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
 * RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
 * TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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


#include <stdint.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>

#include "app_race_cmd.h"
#include "hid_race_cmd.h"
#include "hid_race_cmd_mouse.h"
#include "hid_race_cmd_keyboard.h"
#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#include "app_key_remap.h"
#endif
#include "app_rgb.h"

#include "hal_uart_internal.h"
#include "race_port_uart.h"

#define thisMODULE app_race_cmd
#define thisMOD    "app_race_cmd"
LOG_MODULE_REGISTER(thisMODULE);
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
#if defined(CONFIG_AIR_KEYBOARD_M607)
/* m607 special uart porting */
const mux_port_setting_t g_race_uart_default_setting = {
    .tx_buffer_size = RACE_MUX_UART_TX_BUFFER_SIZE,
    .rx_buffer_size = RACE_MUX_UART_RX_BUFFER_SIZE,
    .dev_setting.uart.uart_config.baudrate = HAL_UART_BAUDRATE_3000000,
    .dev_setting.uart.uart_config.word_length = HAL_UART_WORD_LENGTH_8,
    .dev_setting.uart.uart_config.stop_bit    = HAL_UART_STOP_BIT_1,
    .dev_setting.uart.uart_config.parity      = HAL_UART_PARITY_EVEN,
    .dev_setting.uart.flowcontrol_type        = MUX_UART_SW_FLOWCONTROL,
};
#endif /* defined(CONFIG_AIR_KEYBOARD_M607) */

#define RACE_CMD_SET_SUCCESS 0
#define SETTING_COUNT_MAX 5
uint8_t setting_cnt = 0;

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/
static void hid_app_race_cmd_req_handler(uint16_t race_cmd_id, uint8_t *para, uint16_t length)
{
    APP_LOGI(thisMOD, "hid_app_race_cmd_req_handler race_cmd_id = %x", race_cmd_id);

    struct evt_race_cmd_req* event = create_evt_race_cmd_req();
    // APP_LOGI(thisMOD, "[ALLOC]request, 0, event = %x, size = %d", event, sizeof(struct evt_race_cmd_req));

    if (event){
        event->cmd = race_cmd_id;
        event->len = length;

        switch(race_cmd_id)
        {
            case RACE_CMD_SET_REPORT_RATE:
            {
                event->RR.value = *(uint16_t*)para;
            }
            break;

            case RACE_CMD_SET_RGB:
            {
                event->RGB.rgb_setting = para[0];
                event->RGB.rgb_num = para[1];
                event->RGB.rgb_count = para[2];
                event->RGB.rgb_interval = para[3];
                // printk("event->len = %d, event->rgb_count = %d", event->len, event->RGB.rgb_count);

                if(event->RGB.rgb_count){
                    uint16_t len = event->RGB.rgb_count*3;
                    event->RGB.rgb_color = (uint8_t *)k_malloc(len);
                    memcpy(event->RGB.rgb_color, para + 4, len);
                    // printk("len = %d", len);
                }

                APP_LOGI(thisMOD,"app_race_cmd_evt, RACE_CMD_SET_RGB, setting = 0x%X, num = 0x%X, count = 0x%X, interval = 0x%X",
                                                                event->RGB.rgb_setting, event->RGB.rgb_num, event->RGB.rgb_count, event->RGB.rgb_interval);
            }
            break;

            case RACE_CMD_ENABLE_KEY_EVENT:
            {
                event->ENABLE_KEY_EVNET.event_id = *para;
            }
            break;

            default:{
                break;
            }
        }
        AF_EVT_SUBMIT(event);
    }
}

/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
#if defined(CONFIG_AIR_KEYBOARD_M607)
static void * app_race_cmd_handler(ptr_race_pkt_t pRaceHeaderCmd, uint16_t length, uint8_t channel_id)
{
    uint8_t race_cmd_type = pRaceHeaderCmd->hdr.type;
    uint16_t race_cmd_id = pRaceHeaderCmd->hdr.id;
    void *p_result = NULL;

    APP_LOGI(thisMOD, "app_race_cmd_handler type = 0x%X, id = 0x%X", race_cmd_type, race_cmd_id);

    if ((race_cmd_type == RACE_TYPE_COMMAND) || \
        (race_cmd_type == RACE_TYPE_COMMAND_WITHOUT_RSP)) {
        switch (race_cmd_id){
            case APP_RACE_CMD_ID_MODE_SWITCH:
                /* need to implement */
                typedef struct {
                    RACE_COMMON_HDR_STRU cmdhdr;
                    uint8_t  kb_mode;
                    uint8_t  crc_value;
                } PACKED CMD;
                CMD* p_cmd = (CMD*)pRaceHeaderCmd;
                struct evt_race_mode_switch* event = create_evt_race_mode_switch();
                event->kb_mode = p_cmd->kb_mode;
                event->crc_value = p_cmd->crc_value;
                p_result = NULL;
                AF_EVT_SUBMIT(event);
                break;
            case APP_RACE_CMD_ID_POWER_OFF_REQUEST:
                /* need to implement */
                p_result = NULL;
                break;
            case APP_RACE_CMD_ID_QUERY_READY:
                /* need to implement */
                p_result = NULL;
                break;
            case APP_RACE_CMD_ID_LOW_POWER_REQUEST:
                /* need to implement */
                p_result = NULL;
                break;
            default:
                APP_LOGE(thisMOD, "Unknown command ID: 0x%X", race_cmd_id);
                break;
        }
    } else if ((race_cmd_type == RACE_TYPE_RESPONSE) || \
       (race_cmd_type == RACE_TYPE_NOTIFICATION)) {
        ;
    } else {
        APP_LOGE(thisMOD, "Unknown command type: 0x%X", race_cmd_type);
    }
    return p_result;
}
#endif /* defined(CONFIG_AIR_KEYBOARD_M607) */

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static bool app_race_cmd_evt_rsp_for_rgb(const struct af_evt_header *evt_header)
{
    struct evt_race_cmd_rsp_for_rgb* event = (struct evt_race_cmd_rsp_for_rgb*)evt_header;
    APP_LOGI(thisMOD,"evt_race_cmd_rsp_for_rgb , cmd = %x", event->cmd);

    switch(event->cmd)
    {
        case RACE_CMD_SET_RGB:
        {
            hid_race_set_rgb_rsp(event->status);
            break;
        }

        default:{
            break;
        }
    }
    return AF_TRAVERSE_NEXT;
}

static bool app_race_cmd_evt_rsp(const struct af_evt_header *evt_header)
{
    struct evt_race_cmd_rsp* event = (struct evt_race_cmd_rsp*)evt_header;
    APP_LOGI(thisMOD,"app_race_cmd_evt_rsp , cmd = %x", event->cmd);

    switch(event->cmd)
    {
        case RACE_CMD_SET_REPORT_RATE:
        {
            hid_race_set_report_rate_rsp(event->RR.result);
        }
        break;

        case RACE_CMD_GET_REPORT_RATE:
        {
            hid_race_get_report_rate_rsp(event->RR.result);
        }
        break;

        case RACE_CMD_SET_RGB:
        {
            hid_race_set_rgb_rsp(event->OTHERS.status);
        }
        break;
        case RACE_CMD_ENABLE_KEY_EVENT:
        {
            hid_race_enable_key_event_rsp(event->OTHERS.status);
        }
        break;

        case APP_RACE_CMD_ID_MODE_SWITCH:
        {
            hid_race_kb_set_mode_switch_rsp(event->MODE_SWITCH.status);
        }
        break;

        default:{
            break;
        }
    }
    return AF_TRAVERSE_NEXT;
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
void app_race_cmd_init(void)
{
    uint8_t ret = hid_race_cmd_init(hid_app_race_cmd_req_handler);
    if(ret){
        APP_LOGE(thisMOD, "hid_race_cmd_init fail");
    }

#if defined(CONFIG_AIR_KEYBOARD_M607)
    RACE_HANDLER handler;
    race_status_t race_ret;

    handler.id_start = APP_RACE_CMD_ID_BEGIN;
    handler.id_end = APP_RACE_CMD_ID_END;
    handler.handler = app_race_cmd_handler;
    race_ret = RACE_Register_Handler(&handler);
    if (RACE_STATUS_OK != race_ret) {
        APP_LOGE(thisMOD, " RACE_Register_Handler err = %d", race_ret);
    }
#endif /* defined(CONFIG_AIR_KEYBOARD_M607) */
}

/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_race_cmd_rsp, app_race_cmd_evt_rsp);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_race_cmd_rsp_for_rgb, app_race_cmd_evt_rsp_for_rgb);
#if defined(CONFIG_AIR_KEYBOARD_M607)
// AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_race_cmd_rsp_for_mode_switch, app_race_cmd_evt_rsp_for_mode_switch);
// AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_race_cmd_req, app_mode_switch__evt_race_cmd_req);

#endif /* defined(CONFIG_AIR_KEYBOARD_M607) */
/*=============================================================================*/