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

#ifndef _SYSLOG_PORTABLE_H_
#define _SYSLOG_PORTABLE_H_

#if defined(AIR_LOGGING_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "mux.h"

/* Public define -------------------------------------------------------------*/
/* RACE HEAD */
#define RACE_HEAD_CHANNEL_BYTE                  0x05
/* RACE TYPE */
#define RACE_TYPE_CMD_WITH_RESPONCE             0x5A
#define RACE_TYPE_RESPONCE                      0x5B
#define RACE_TYPE_CMD_WITHOUT_RESPONCE          0x5C
#define RACE_TYPE_NOTIFICATION                  0x5D
/* RACE PROTOCOL ID */
#define RACE_PROTOCAL_SYSLOG_BEGIN              (0x0F00 | 0x10)
#define RACE_PROTOCAL_EXCEPTION_STRING_LOG      (0x0F00 | 0x12)
#define RACE_PROTOCAL_EXCEPTION_BINARY_LOG      (0x0F00 | 0x13)
#define RACE_PROTOCAL_ACTIVE_ASSERT             (0x0F00 | 0x14)
#define RACE_PROTOCAL_QUERY_VERSION_BUILDTIME   (0x0F00 | 0x15)
#define RACE_PROTOCAL_GET_LOG_FILTER_INFO       (0x0F00 | 0x16)
#define RACE_PROTOCAL_SET_LOG_FILTER_INFO       (0x0F00 | 0x17)
#define RACE_PROTOCAL_SAVE_LOG_SETTING          (0x0F00 | 0x18)
#define RACE_PROTOCAL_QUERY_CPU_FILTER_INFO     (0x0F00 | 0x19)
#define RACE_PROTOCAL_SET_CPU_FILTER_INFO       (0x0F00 | 0x20)
#define RACE_PROTOCAL_EXCEPTION_MSGID           (0x0F00 | 0x1A)
#define RACE_PROTOCAL_QUERY_SYSTEM_INFO         (0x0F00 | 0x1B)
#define RACE_PROTOCAL_TLV_LOG                   (0x0F00 | 0x00)
#define RACE_PROTOCAL_STRING_LOG                (0x0F00 | 0x40)
#define RACE_PROTOCAL_MSGID_LOG                 (0x0F00 | 0x41)
#define RACE_PROTOCAL_MSGID_LOG_WITH_STR        (0x0F00 | 0x42)
#define RACE_PROTOCAL_SYSLOG_END                (0x0F00 | 0x4F)
#define RACE_PROTOCAL_TLV_DUMP_LOG              (0x0F00)
#define RACE_PROTOCAL_ATCI_BEGIN                (0x0F92)
#define RACE_PROTOCAL_ATCI_END                  (0x0F92)

/* share syslog variable define */
#ifdef AIR_BTD_IC_PREMIUM_G1
#define PORT_SYSLOG_MAX_CPU_NUMBER (16)
#define AIR_MAX_CPUS_NUMBER    (2)
#else
#define PORT_SYSLOG_MAX_CPU_NUMBER (1)
#define AIR_MAX_CPUS_NUMBER    (1)
#endif

#define SYSLOG_NVKEY_MAGIC_NUMBER   0x5A

/*re-porting part. */
/* module and filter define */
#define PORT_SYSLOG_MODULE_FILTER_TOTAL_NUMBER 200
#define PORT_SYSLOG_MODULE_FILTER_STATUS_SIZE (PORT_SYSLOG_MAX_CPU_NUMBER * 2 + PORT_SYSLOG_MODULE_FILTER_TOTAL_NUMBER)
#define PORT_SYSLOG_MAX_MODULE_FILTER_STATUS_SIZE (PORT_SYSLOG_MAX_CPU_NUMBER * 2 + PORT_SYSLOG_MODULE_FILTER_TOTAL_NUMBER)
#define SYSLOG_NVKEY_MAGIC_NUMBER   0x5A

typedef struct{
uint32_t uart_port;
uint32_t baudrate;
uint32_t parity;
uint32_t stop_bits;
uint32_t data_bits;
}syslog_port_dts_config_t;

typedef struct {
    uint32_t handle; // mux handle
    uint32_t init_phase;
    uint32_t sequence[2];
    uint32_t drop_count[2];
    uint8_t cpu_log_switch[PORT_SYSLOG_MAX_CPU_NUMBER];
    uint8_t cpu_log_print_level[PORT_SYSLOG_MAX_CPU_NUMBER];
#ifdef AIR_BTD_IC_PREMIUM_G1
    uint8_t cpu_module_filter_status[PORT_SYSLOG_MAX_MODULE_FILTER_STATUS_SIZE]; /* log filter setting read from NVDM to let per-cpu do initialization with it's log filter array. */
    void *cpu_module_filter[PORT_SYSLOG_MAX_CPU_NUMBER]; /* Init to per-cpu's log filter array when per-cpu call log_set_filter() in it's init phase. */
#endif
} syslog_share_variable_t;

/* Public typedef ------------------------------------------------------------*/
typedef enum {
    SYSLOG_NVKEY_STATUS_OK = 0,
    SYSLOG_NVKEY_STATUS_ERROR,
    SYSLOG_NVKEY_STATUS_INVALID,
} log_nvkey_status_t;


typedef struct {
    uint8_t cpu_id;
    uint8_t module_number;
} cpu_module_filter_info_t;

typedef struct {
    uint8_t *p_buf;     /**<  syslog buffer start address*/
    uint32_t buf_size;  /**<  syslog buffer lenght*/
} syslog_buffer_t;

/*add a new 0XF009 nvkey to store the log cpu info*/
typedef struct {
    uint8_t cpu_log_switch: 4;
    uint8_t cpu_log_level: 4;
} cpu_filter_info_t;

typedef struct {
    cpu_filter_info_t cpu_log_filter_info[PORT_SYSLOG_MAX_CPU_NUMBER];
    uint8_t magic_number;
} syslog_nvkey_cpu_filter_t;


typedef struct {
    struct {
        uint8_t port: 7;
        uint8_t dump_enable: 1;
    } syslog_port;
    struct {
        uint8_t cpu0_level: 2;
        uint8_t cpu1_level: 2;
        uint8_t cpu0_switch: 2;
        uint8_t cpu1_switch: 2;
    } syslog_level;
    struct {
        uint8_t high_br_enable: 2;
        uint8_t reserve: 6;
    } baudrate;
    uint8_t magic_number;
} syslog_nvkey_cfg_t;

typedef struct {
    cpu_module_filter_info_t syslog_module_filter_number[PORT_SYSLOG_MAX_CPU_NUMBER];
    uint8_t syslog_module_filter_status[PORT_SYSLOG_MODULE_FILTER_TOTAL_NUMBER];
} cpu_module_filter_status_t;

typedef struct {
    uint8_t syslog_module_filter_magic;
    cpu_module_filter_status_t cpu_module_filter_status;
} syslog_nvkey_module_filter_t;


/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
//extern bool syslog_port_mux_exception_init(uint32_t handle);
//extern uint32_t port_syslog_send(uint32_t id, bool drop_flag, syslog_buffer_t *p_buf_info);
log_nvkey_status_t syslog_port_form_nvkey_init(uint32_t *port);
bool syslog_port_read_setting(char *name, uint8_t *p_setting, uint32_t size);
void log_global_turn_off(void);
bool filter_module_config_save(void);
bool filter_cpu_config_save(void);
#endif /* AIR_LOGGING_ENABLE */

#endif /* _SYSLOG_PORTABLE_H_ */
