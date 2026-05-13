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

#include <zephyr/logging/log.h>
#include <string.h>
#include "hal_nvic.h"
#include "hal_nvic_internal.h"
#include "hal_core_status.h"
#include "system_online_dump.h"

#ifdef HAL_CCNI_MODULE_ENABLED
#include "hal_ccni.h"
#include "hal_ccni_config.h"
#endif

#ifdef AIR_MUX_ENABLE
#include "mux.h"
#include "mux_port_common.h"
#endif

#ifdef AIR_SWLA_ENABLE
#include "swla.h"
#endif

#if IS_ENABLED(CONFIG_AIR_LOGGING_ENABLE)
#include "air_logging.h"
#endif

#if IS_ENABLED(CONFIG_AIR_LOGGING_ENABLE)
log_create_module(system_online_mcu, PRINT_LEVEL_INFO);
#endif

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#if IS_ENABLED(CONFIG_AIR_LOGGING_ENABLE)
#define SYS_DUMP_LOG(_message,...)             LOG_INF("[system_dump] "_message,##__VA_ARGS__)
#else
#define SYS_DUMP_LOG(_message,...)             printk("[system_dump] "_message,##__VA_ARGS__)
#endif

/* Private macro -------------------------------------------------------------*/
#define PORT_SYSLOG_DUMP_SYSTEM_INFO_MAX_LEN        (0x400) // 1K
#define CCNI_MCU_TO_RISCV_SYSTEM_EVENT              IRQGEN_MCU2RISCV_EVENT15

/* Private variables ---------------------------------------------------------*/
extern sys_task_info_t sys_task_info[];
extern uint32_t g_uxTaskNumber;

/* Private functions ---------------------------------------------------------*/
extern uint32_t port_syslog_send(uint32_t id, bool drop_flag, mux_buffer_t *p_buf_info);

/* Public functions ----------------------------------------------------------*/
uint32_t port_system_online_dump_query_max_cpu_number(void)
{
#ifdef AIR_MUX_ENABLE
    return AIR_MAX_CPU_NUMBER;
#else
    return 1; /* only mcu core */
#endif
}

/* PC tool command resopnse, dump task/irq/label info */
void system_port_dump_sysinfo(uint32_t cpu_id, uint32_t func_id)
{
    uint32_t res_len, name_len = 0;
    uint8_t current_index = 0, max_index = 0;
    uint8_t *p_data, *p_index;
    mux_buffer_t tx_buf[3];
    uint32_t tx_size = 0;

#ifdef HAL_CCNI_MODULE_ENABLED
    hal_ccni_message_t hal_system_info_ccni_message;
#endif

    // 05 5A 04 00 1B 0F <00>    <00>
    //                   cpu_id  func_id(task/isr/label)
    SYS_DUMP_LOG("[system info] pc tool command, query pc tool command cpu:%d id:%d ", cpu_id, func_id);

    /* check cpu_id */
    if (cpu_id >= AIR_MAX_CPU_NUMBER) {
        return;
    }

    /* check func_id */
    if (func_id >= 3) {
        return;
    }

    /* other core send package by itself, so we need send ccni */
    if (cpu_id != GET_CURRENT_CPU_ID()) {
#ifdef HAL_CCNI_MODULE_ENABLED
        hal_system_info_ccni_message.data[0] = SYSTEM_CCNI_SUB_EVENT_SYSINFO;
        hal_system_info_ccni_message.data[1] = func_id;
        hal_core_status_t riscv_status = hal_core_status_read(HAL_CORE_RISCV);
        if (cpu_id == 1) {
            if ((riscv_status == HAL_CORE_ACTIVE) || (riscv_status == HAL_CORE_SLEEP)) {
                if (HAL_CCNI_STATUS_OK != hal_ccni_set_event(CCNI_MCU_TO_RISCV_SYSTEM_EVENT, &hal_system_info_ccni_message)) {
                    SYS_DUMP_LOG("[system info] pc tool command, mcu send ccni to RISC-V fail!!!\r\n");
                }
            } else {
                SYS_DUMP_LOG("[system info] pc tool command, error, RISC-V core status:%d r\n", riscv_status);
            }
        }
#else
        SYS_DUMP_LOG("[system info] pc tool command, must enable ccni module r\n");
#endif
        return ;
    }

    p_data = (uint8_t *)k_malloc(PORT_SYSLOG_DUMP_SYSTEM_INFO_MAX_LEN);
    if (p_data == NULL) {
        return;
    }
    memset(p_data, 0, PORT_SYSLOG_DUMP_SYSTEM_INFO_MAX_LEN);

    p_index = p_data;   // record buffer pointer
    res_len = 0;        // init response length

    /* filling header info */
    *p_data++ = GET_CURRENT_CPU_ID();
    *p_data++ = func_id;
    res_len += 2;

    /* filling data info */
    switch (func_id) {
        case 0:  /* task info */
            /* race + [[index + priority + len] + str] + [[index + priority + len] + str] ... */
            __ASSERT(g_uxTaskNumber != 0, "no task info.");
            max_index = g_uxTaskNumber;
            for (current_index = 0; current_index < max_index; current_index++) {
                name_len = strlen(sys_task_info[current_index].name);
                if ((res_len + (name_len + 3)) > PORT_SYSLOG_DUMP_SYSTEM_INFO_MAX_LEN) {
                    SYS_DUMP_LOG("[system info] pc tool command, dump task task, buffer overflow");
                    break;
                }
                res_len += name_len + 3;
                *p_data++ = sys_task_info[current_index].number;                          // task_index
                *p_data++ = sys_task_info[current_index].priority;                        // task_priority
                *p_data++ = name_len;                                                     // task name length
                strncpy((char *)p_data, sys_task_info[current_index].name, name_len);     // task name string
                p_data += name_len;
            }
            break;
        case 1:  /* irq info */
            /* race + [[index + priority + len] + str] + [[index + priority + len] + str] ... */
            max_index = IRQ_NUMBER_MAX;
            for (current_index = 0; current_index < IRQ_NUMBER_MAX; current_index++) {
                name_len = strlen(irq_info[current_index].name);
                if ((res_len + (name_len + 3)) >= PORT_SYSLOG_DUMP_SYSTEM_INFO_MAX_LEN) {
                    SYS_DUMP_LOG("[system info] pc tool command, dump irq mapping, buffer overflow");
                    break;
                }
                res_len  += name_len + 3;                                           // total data len++
                *p_data++ = irq_info[current_index].index;                          // irq index
                *p_data++ = irq_info[current_index].priority;                       // irq priority
                *p_data++ = name_len;                                               // irq name length
                strncpy((char *)p_data, irq_info[current_index].name, name_len);    // irq name string
                p_data += name_len;
            }
            break;
#ifdef AIR_SWLA_ENABLE
        case 2:  /* label info */
            /* race + [[index + priority + len] + str] + [[index + priority + len] + str] ... */
            max_index = swla_user_label_array_count;
            for (current_index = 0; current_index < max_index; current_index++) {
                name_len = strlen(swla_user_label_info[current_index].name);
                if ((res_len + (name_len + 3)) >= PORT_SYSLOG_DUMP_SYSTEM_INFO_MAX_LEN) {
                    SYS_DUMP_LOG("[system info] pc tool command, dump user label mapping, buffer overflow");
                    break;
                }
                res_len  += name_len + 3;                                                       // total data len++
                *p_data++ = swla_user_label_info[current_index].index;                          // label index
                *p_data++ = 0x0;                                                                // label priority. (reserve)
                *p_data++ = name_len;                                                           // label name length
                strncpy((char *)p_data, swla_user_label_info[current_index].name, name_len);    // label name string
                p_data += name_len;
            }
            break;
#endif
        default:
            current_index = 0;
            max_index = 0;
            break;
    }

    SYS_DUMP_LOG("[system info] pc tool command, func_id:%d loop query info done, response_len:%d, index:%d max_index:%d", func_id, res_len, current_index, max_index);

    tx_buf[1].p_buf = p_index;
    tx_buf[1].buf_size = res_len;
    tx_buf[2].p_buf = NULL;
    tx_size = port_syslog_send(0x0F1B, true, tx_buf);

    SYS_DUMP_LOG("[system info] pc tool command, tx size:%d", tx_size);

    k_free(p_index);
}

