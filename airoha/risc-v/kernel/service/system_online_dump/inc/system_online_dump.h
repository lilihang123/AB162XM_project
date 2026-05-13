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

#ifndef __SYSTEM_ONLINE_DUMP_H__
#define __SYSTEM_ONLINE_DUMP_H__

#include <stdint.h>

/*****************************************************************************
 * enum or struct
 *****************************************************************************/
typedef enum {
    SYSTEM_ONLINE_DUMP_SWLA = 0,

    SYSTEM_ONLINE_DUMP_ID_MAX = 0xFF,
} system_online_dump_id_t;

typedef struct {
    uint8_t cpu_id;
    uint8_t feature_id;
    uint16_t pack_seq_num;
    uint16_t rc_drop_count;
    uint8_t version;
    uint8_t reserve;
} __attribute__((packed)) system_online_dump_header_t;

/**
 * @enum system_ccni_sub_event_id_t
 * @brief Enumerates the sub-event IDs for system events.
 *
 * This enum is used to define unique identifiers for different 
 * sub-events within the system, facilitating event handling and management.
 */
typedef enum {
    SYSTEM_CCNI_SUB_EVENT_SWLA = 0,
    SYSTEM_CCNI_SUB_EVENT_SYSINFO = 1,
    SYSTEM_CCNI_SUB_EVENT_MAX = 0xFFFFFFFF,
} system_ccni_sub_event_id_t;

typedef struct {
    uint8_t number;
    int8_t priority;
    char name[16];
} __attribute__((packed)) sys_task_info_t;

/*****************************************************************************
 * function prototype or extern variable
 *****************************************************************************/
void System_Info_Dump(system_online_dump_id_t feature_id, uint8_t cpu_id, uint8_t version, uint16_t seq, uint16_t drop_count, uint8_t *p_buf, uint32_t buf_size);

#endif
