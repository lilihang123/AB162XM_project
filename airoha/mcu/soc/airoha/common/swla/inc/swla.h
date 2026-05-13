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

#ifndef __SWLA_H__
#define __SWLA_H__

#include <stdint.h>
#include <stdbool.h>

#define SWLA_VERSION        (2)

/* HEAD magic number 0<N<16 (4bit) */
#define SWLA_MSGIC_HEAD_1B  (1)
#define SWLA_MSGIC_HEAD_2B  (2)
#define SWLA_MSGIC_HEAD_3B  (3)
#define SWLA_MSGIC_HEAD_4B  (4)
#define SWLA_MSGIC_HEAD_5B  (5)
#define SWLA_MSGIC_HEAD_6B  (6)
#define SWLA_MSGIC_HEAD_7B  (7)
#define SWLA_MSGIC_HEAD_8B  (8)

typedef enum {
    SWLA_TYPE_TASK = 0,
    SWLA_TYPE_IRQ,
    SWLA_TYPE_LABEL,
    SWLA_TYPE_RESERVE,
    SWLA_TYPE_MAX = 4,
} SWLA_TYPE_t;

typedef enum {
    SWLA_DIRECTION_START = 0,
    SWLA_DIRECTION_STOP,
    SWLA_DIRECTION_LABEL,
    SWLA_DIRECTION_RESERVE,
    SWLA_DIRECTION_MAX = 4,
} SWLA_ACTION_t;

typedef struct {
    uint8_t index;
    const char *name;
} __attribute__((packed)) SWLA_USERLABEL_INFO_t;


// ################# step-2, add customeized HCLA label start #################
typedef enum {
    label_dpm = 0,
    label_wfi,
    label_msk,
    label_excp,
    label_app_evt_dispatcher,
    label_gesture,
    label_app_wheel_wakeup,
    label_app_sensor_wakeup,    
    label_app_exit_low_power,
    label_app_bt_connecting,
    label_app_10,
    label_app_11,
    label_usb_tx_send,

    SWLA_LABEL_MAX_ID = 0xFF,
} SWLA_USERLABEL_ID_t;
// ################# step-2, add customeized HCLA label end #################

typedef enum SWLA_CONTROL_T {
    SA_DISABLE = 0x0,
    SA_ENABLE = 0x1,
} SA_CONTROL_t;

typedef struct SWLA_IMAGE_HEADER_1 {
    uint8_t xMainVer;
    uint8_t xSubVer;
    uint16_t xImageHeaderLen;
    uint16_t xMainDescLen; //?
    uint16_t xAddonDescLen; //?
    uint8_t xMode;
    uint8_t xCoreID;
    uint8_t res1[2];
    uint32_t xMDsysUS;//MDSys US
    uint8_t xPlatformName[16];
    uint8_t xFlavormName[32];
} SA_IMAGE_HEADER1;

typedef struct SWLA_IMAGE_HEADER_2 {
    uint32_t xStartPosition;
    uint32_t xCurPosition;
    uint32_t xBufLen;
    uint32_t xWrapCount;
} SA_IMAGE_HEADER2;


typedef struct SWLA_NODE_T {
    uint8_t data;
} __attribute__((packed)) SA_NODE_t;

/* for exception polling send */
typedef struct {
    uint8_t *p_buf;
    uint32_t buf_size;
} swla_buffer_t;

typedef struct {
    uint32_t seq_number;
    swla_buffer_t buffer[2];
} swla_buffer_dump_info_t;

#ifdef __cplusplus
extern "C" {
#endif

/* SWLA */
void SLA_Enable(void);
bool SLA_Is_Enable(void);
void SLA_Control(SA_CONTROL_t xOperation);
void SLA_MemoryCallbackInit(void);
void SLA_get_region(uint32_t *pxBase, uint32_t *pxLen);
void HCLA_RamLogging_V2(SWLA_TYPE_t type, uint8_t ID, SWLA_ACTION_t xAction);
void online_swla_init(void);

#ifdef __cplusplus
}
#endif

/* HCLA */
extern const SWLA_USERLABEL_INFO_t swla_user_label_info[];
extern const uint8_t swla_user_label_array_count;
extern bool g_online_swla_enable;

void swla_cycle_online_dump(void);
bool swla_query_exception_buffer_info(swla_buffer_t *p_buf_info, uint32_t *p_seq);

/* porting layer function */
extern uint32_t port_swla_query_max_cpu_number(void);
extern uint32_t port_swla_query_package_header_size(void);
extern bool port_swla_online_mode_is_enable(void);
extern void port_swla_dump_package(uint8_t version, uint16_t seq, uint16_t drop_count, uint8_t *p_buf, uint32_t buf_size);
extern void port_swla_trigger_dump(void);

#endif /* __SWLA_H__ */

