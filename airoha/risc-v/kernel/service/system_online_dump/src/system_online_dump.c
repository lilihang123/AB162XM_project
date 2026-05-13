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

#include "string.h"
#include "syslog.h"
#include "system_online_dump.h"
#include "swla.h"
#include "hal_nvic.h"
#include "hal_ccni.h"
#include "hal_ccni_config.h"

/* Private typedef -----------------------------------------------------------*/
typedef struct {
    uint8_t *p_buf;     /**<  MUX buffer start address*/
    uint32_t buf_size;  /**<  MUX buffer lenght*/
} mux_buffer_t;

/* Private define ------------------------------------------------------------*/
log_create_module(system_online_dsp, PRINT_LEVEL_INFO);

/* Private macro -------------------------------------------------------------*/
#define AIR_MAX_CPU_NUMBER                      (2)
#define CURRENT_CORE_ID                         (1)     /* RISC-V core */
#define SYSTEM_INFO_RESPONSE_BUFFER_MAX_LEN     (512)

/* Private variables ---------------------------------------------------------*/

sys_task_info_t sys_task_info[1] = {
    /* 0  */ {0, 0, "main"},
};

/* Private functions ---------------------------------------------------------*/
extern uint32_t port_syslog_send(uint32_t id, bool drop_flag, mux_buffer_t *p_buf_info);

#ifdef AIR_ONLINE_SWLA_ENABLE

void System_Info_Dump(system_online_dump_id_t feature_id, uint8_t cpu_id, uint8_t version, uint16_t seq, uint16_t drop_count, uint8_t *p_buf, uint32_t buf_size)
{
    uint32_t ret_len = 0;
    system_online_dump_header_t system_info_header;
    uint8_t *system_buffer_array[3];
    uint32_t system_buffer_length_array[2];

    /* feature id is invalid */
    if (feature_id >= SYSTEM_ONLINE_DUMP_ID_MAX) {
        return;
    }

    if ((cpu_id >= AIR_MAX_CPU_NUMBER) && (cpu_id != 0xFF)) {
        return;
    }

    if ((p_buf != NULL) && (buf_size != 0)) {
        system_info_header.cpu_id = cpu_id;
        system_info_header.feature_id = feature_id;
        system_info_header.pack_seq_num = seq;
        system_info_header.rc_drop_count = drop_count;
        system_info_header.version = version;

        system_buffer_array[0] = (uint8_t*)&system_info_header;
        system_buffer_length_array[0] = sizeof(system_online_dump_header_t);
        system_buffer_array[1] = p_buf;
        system_buffer_length_array[1] = buf_size;
        system_buffer_array[2] = NULL;

        LOG_TLVDUMP_I(system_online_dsp, LOG_TYPE_SYSTEM_INFO, system_buffer_array, system_buffer_length_array, ret_len);
        if (ret_len == 0) {
            LOG_MSGID_E(system_online_dsp, "system online dump fail. feature id:%d seq:%d p_buf:0x%08x buf_size:%d",
                                                            4, feature_id, seq, p_buf, buf_size);
        }
    }
}

void ccni_dump_sysinfo(uint32_t func_id)
{
    uint32_t res_len, name_len = 0;
    uint8_t current_index = 0, max_index = 0;
    uint8_t *p_data, *p_index;
    mux_buffer_t tx_buf[3];
    uint32_t tx_size = 0;
    uint8_t res_buffer[SYSTEM_INFO_RESPONSE_BUFFER_MAX_LEN];

    LOG_MSGID_I(system_online_dsp, "This is ccni event dump sysinfo. function_id:%d ", 1, func_id);

    p_data = (uint8_t *)res_buffer;
    p_index = p_data;   // record buffer pointer
    res_len = 0;        // init response length
    /* filling header info */
    *p_data++ = CURRENT_CORE_ID;
    *p_data++ = func_id;
    res_len += 2;
    /* filling data info */
    if (func_id == 0) {
        /* race + [[index + priority + len] + str] + [[index + priority + len] + str] ... */
        max_index = sizeof(sys_task_info) / sizeof(sys_task_info_t);
        for (current_index = 0; current_index < max_index; current_index++) {
            name_len = strlen(sys_task_info[current_index].name);
            res_len  += name_len + 3;  // total data len
            if (res_len > SYSTEM_INFO_RESPONSE_BUFFER_MAX_LEN) {
                res_len -= (name_len + 3);
                LOG_MSGID_W(system_online_dsp, "[system info] dump task task, buffer overflow", 0);
                break;
            }
            *p_data++ = sys_task_info[current_index].number;                        // task_index
            *p_data++ = sys_task_info[current_index].priority;                      // task_priority
            *p_data++ = name_len;                                                   // task name length
            strncpy((char *)p_data, sys_task_info[current_index].name, name_len);   // task name string
            p_data += name_len;
        }
    } else if (func_id == 1) { /* irq info */
        /* race + [[index + priority + len] + str] + [[index + priority + len] + str] ... */
        max_index = IRQ_NUMBER_MAX;
        for (current_index = 0; current_index < IRQ_NUMBER_MAX; current_index++) {
            if (irq_info[current_index].name != NULL) {
                name_len = strlen(irq_info[current_index].name);
                if ((res_len + (name_len + 3)) >= SYSTEM_INFO_RESPONSE_BUFFER_MAX_LEN) {
                    LOG_MSGID_W(system_online_dsp, "[system info] dump irq mapping, buffer overflow", 0);
                    break;
                }
                res_len  += name_len + 3;                                           // total data len++
                *p_data++ = irq_info[current_index].index;                          // irq index
                *p_data++ = irq_info[current_index].priority;                       // irq priority
                *p_data++ = name_len;                                               // irq name length
                strncpy((char *)p_data, irq_info[current_index].name, name_len);    // irq name string
                p_data += name_len;
            }
        }
    } else if (func_id == 2) { /* label info */
        /* race + [[index + priority + len] + str] + [[index + priority + len] + str] ... */
        max_index = swla_user_label_array_count;
        for (current_index = 0; current_index < max_index; current_index++) {
            name_len = strlen(swla_user_label_info[current_index].name);
            if ((res_len + (name_len + 3)) >= SYSTEM_INFO_RESPONSE_BUFFER_MAX_LEN) {
                LOG_MSGID_W(system_online_dsp, "[system info] dump user label mapping, buffer overflow", 0);
                break;
            }
            res_len  += name_len + 3;                                                       // total data len++
            *p_data++ = swla_user_label_info[current_index].index;                          // label index
            *p_data++ = 0x00;                                                               // label priority. (reserve)
            *p_data++ = name_len;                                                           // label name length
            strncpy((char *)p_data, swla_user_label_info[current_index].name, name_len);    // label name string
            p_data += name_len;
        }
    } else {
        current_index = 0;
        max_index = 0;
    }

    LOG_MSGID_W(system_online_dsp, "[system info] func_id:%d loop query info done, response_len:%d, index:%d max_index:%d", 4, func_id, res_len, current_index, max_index);

    tx_buf[1].p_buf = p_index;
    tx_buf[1].buf_size = res_len;
    tx_buf[2].p_buf = NULL;
    tx_size = port_syslog_send(0x0F1B, true, tx_buf);
    LOG_MSGID_W(system_online_dsp, "[system info] tx_size:%d", 1, tx_size);
}

#else

void ccni_dump_sysinfo(uint32_t func_id)
{
    LOG_MSGID_W(system_online_dsp, "Please enable RISC-V AIR_ONLINE_SWLA_ENABLE first. function_id:%d ", 1, func_id);
}

#endif

void CCNI_DEF_HANDLER(15)(hal_ccni_event_t event, hal_ccni_message_t *msg)
{
    system_ccni_sub_event_id_t sub_id;
    hal_ccni_status_t status;

    (void) sub_id;
    (void) status;

    if (NULL != msg) {
        sub_id = (system_ccni_sub_event_id_t)(((hal_ccni_message_t *)msg)->data[0]);
        LOG_MSGID_I(system_online_dsp, "dsp_system_event_handler msg[0]:0x%x msg[1]:0x%x sub_id:%d", 3, 
                                            (uint32_t)(((hal_ccni_message_t *)msg)->data[0]),
                                            (uint32_t)(((hal_ccni_message_t *)msg)->data[1]),
                                            sub_id);
        switch (sub_id) {
            case SYSTEM_CCNI_SUB_EVENT_SWLA: {
            } break;

            case SYSTEM_CCNI_SUB_EVENT_SYSINFO: {
                uint32_t func_id = (uint32_t)(((hal_ccni_message_t *)msg)->data[1]);
                ccni_dump_sysinfo(func_id);
            } break;

            default: {
            } break;
        }
    }
}