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
#if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP) || defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#ifndef _KEY_REMAP_QUEUE_H_
#define _KEY_REMAP_QUEUE_H_

#if defined(CONFIG_AIR_KEY_REMAP_FRONTEND_CM33) || defined(AIR_KEY_REMAP_FRONTEND_RISCV)
#include "riscv_hid_express.h"
#endif

#include "stdio.h"
#include "stdint.h"
#include "hid_common.h"
#include <assert.h>
#if defined(CORE_MCU)
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#endif

#define REMAP_BUFFER_SIZE                                               (1<<2)  /** The size of the buffer used to store the mouse z1 info, it should be a power of 2 */
#define REMAP_BUFFER_SIZE_MASK                         (REMAP_BUFFER_SIZE - 1)  /** The mask of the buffer size  */

#define RISCV_HID_LOG_ENA

#ifdef RISCV_HID_LOG_ENA
#define HID_DBG_LOG(module, message, arg_cnt, ...)        LOG_MSGID_I(module, message, arg_cnt, ##__VA_ARGS__ )
#else 
#define HID_DBG_LOG(module, message, arg_cnt, ...)  
#endif

#if defined (CONFIG_LOG) && defined(CORE_MCU)
#define REMAP_LOGI(module_name, format, ...)   \
        LOG_INF("[common-i]["module_name"]" format, ## __VA_ARGS__)
#else
#define REMAP_LOGI(module_name, format, ...)   \
        printk(" [i-" module_name"] "format, ## __VA_ARGS__)
#endif

#define LSB 0x000000FF

typedef enum {
    R_MS_KEY_Z,       /** Mouse key and Z1 */
    R_KB_STD,         /** Keyboard standard key */
    R_KB_CONSUMBER,   /** Keyboard consumer key */
    R_GC_KEY,         /** Game controller key */
    R_GC_LT,          /** Game controller LT */
    R_GC_RT,          /** Game controller RT */
}T_R_ITEM_TYPE_E;

typedef struct {
    // uint32_t type;
    // uint32_t items[2];                      /** The key value  */
    T_REMAP_VALUES_S data;
    uint32_t ready;
}T_REMAP_KEY_INFO_S;

typedef struct {
    T_REMAP_KEY_INFO_S    buffer[REMAP_BUFFER_SIZE];      /** The queue buffer of remap values */
    uint32_t              buf_head;                       /** The head index of the queue buffer. It stand for the next position to be pushed into the queue  */
    uint32_t              buf_tail;                       /** The tail index of the queue buffer. It stand for the next position to be popped from the queue  */
}T_REMAP_QUEUE_CTRL_S;

typedef struct {
    uint8_t msg;
    T_REMAP_QUEUE_CTRL_S* ptr;
}__attribute__((__packed__)) T_REMAP_QUEUE_PTR_S;

#if defined(CONFIG_AIR_KEY_REMAP_FRONTEND_CM33) || defined(AIR_KEY_REMAP_FRONTEND_RISCV)
void key_remap_queue_init(T_REMAP_QUEUE_CTRL_S *Kr_q_Ctrl);
void key_remap_queue_pop(T_REMAP_QUEUE_CTRL_S *Kr_q_Ctrl, void *outgoing_data);
#endif /* CONFIG_AIR_KEY_REMAP_FRONTEND_CM33, AIR_KEY_REMAP_FRONTEND_RISCV */

#if defined(CONFIG_AIR_KEY_REMAP_BACKEND_CM33) || defined(AIR_KEY_REMAP_BACKEND_RISCV)
void key_remap_queue_push(T_REMAP_QUEUE_CTRL_S *Kr_q_Ctrl, T_REMAP_VALUES_S *outgoing_data, uint32_t key_status);
#endif /* CONFIG_AIR_KEY_REMAP_BACKEND_CM33, AIR_KEY_REMAP_BACKEND_RISCV */

#if defined(AIR_PRODUCT_TYPE_MOUSE) && defined(AIR_KEY_REMAP_FRONTEND_RISCV)
void key_remap_xy_push(uint32_t x, uint32_t y);
void key_remap_xy_pop(T_OUTGOING_VALUES_S *outgoing_data);
#endif /* AIR_PRODUCT_TYPE_MOUSE, AIR_KEY_REMAP_FRONTEND_RISCV */
#endif /* _KEY_REMAP_QUEUE_H_ */
#endif /* AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP, CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */