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
#include "key_remap_queue.h"

/* Includes ------------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define thisMODULE kr_q
#define thisMOD    "kr_q"

#if defined(CORE_MCU)
LOG_MODULE_REGISTER(thisMODULE);
#else
log_create_module(kr_q, PRINT_LEVEL_INFO);
#endif
/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
#if defined(AIR_PRODUCT_TYPE_MOUSE)
typedef struct {
    uint32_t x;
    uint32_t y;
}T_REMAP_XY_IFNO_S;

typedef struct {
    T_REMAP_XY_IFNO_S val[2];
    uint32_t active;
}T_REMAP_XY_BUF_S;

T_REMAP_XY_BUF_S Kr_xy_buf;
#endif

/* Public variables ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
#if defined(CONFIG_AIR_KEY_REMAP_BACKEND_CM33) || defined(AIR_KEY_REMAP_BACKEND_RISCV)
static bool key_remap_queue_is_full(T_REMAP_QUEUE_CTRL_S *Kr_q_Ctrl) 
{
    return ((Kr_q_Ctrl->buf_head + 1) & REMAP_BUFFER_SIZE_MASK) == Kr_q_Ctrl->buf_tail;
}
#endif

#if defined(CONFIG_AIR_KEY_REMAP_FRONTEND_CM33) || defined(AIR_KEY_REMAP_FRONTEND_RISCV)
static bool key_remap_queue_is_empty(T_REMAP_QUEUE_CTRL_S *Kr_q_Ctrl) 
{
    return Kr_q_Ctrl->buf_head == Kr_q_Ctrl->buf_tail;
}

/* Private functions ---------------------------------------------------------*/
void key_remap_queue_init(T_REMAP_QUEUE_CTRL_S *Kr_q_Ctrl) 
{
    memset(Kr_q_Ctrl, 0, sizeof(T_REMAP_QUEUE_CTRL_S));
    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    memset(&Kr_xy_buf, 0, sizeof(T_REMAP_XY_BUF_S));
    #endif
}

#if defined(AIR_PRODUCT_TYPE_MOUSE)
void key_remap_xy_push(uint32_t x, uint32_t y)
{
    uint32_t active = Kr_xy_buf.active;
    Kr_xy_buf.val[!active].x = x;
    Kr_xy_buf.val[!active].y = y;
    Kr_xy_buf.active = !active;
}

void key_remap_xy_pop(T_OUTGOING_VALUES_S *outgoing_data)
{
    if(Kr_xy_buf.val[Kr_xy_buf.active].x || Kr_xy_buf.val[Kr_xy_buf.active].y)
    {
        outgoing_data->x += Kr_xy_buf.val[Kr_xy_buf.active].x;
        outgoing_data->y += Kr_xy_buf.val[Kr_xy_buf.active].y;
        Kr_xy_buf.val[Kr_xy_buf.active].x = 0;
        Kr_xy_buf.val[Kr_xy_buf.active].y = 0;
        outgoing_data->kb_std[1] |= MOUSE_XY_MACRO_BIT;
    }
}
#endif

void key_remap_queue_pop(T_REMAP_QUEUE_CTRL_S *Kr_q_Ctrl, void *outgoing_data)
{
    T_OUTGOING_VALUES_S * outgoing = (T_OUTGOING_VALUES_S *)outgoing_data;

    if(!key_remap_queue_is_empty(Kr_q_Ctrl))
    {
        T_REMAP_KEY_INFO_S *key_remap_info = &Kr_q_Ctrl->buffer[(Kr_q_Ctrl->buf_tail + 1) & REMAP_BUFFER_SIZE_MASK];
        T_REMAP_VALUES_S *outgoing_key_info = &(key_remap_info->data);

        if(key_remap_info->ready)
        {
            #if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
            outgoing->k.word |= outgoing_key_info->gc_k;
            if(outgoing_key_info->gc_lt)
            {
                outgoing->lt |= outgoing_key_info->gc_lt;
                outgoing->k.word |= LT_KEY_BIT;
            }
            if(outgoing_key_info->gc_rt)
            {
                outgoing->lt |= outgoing_key_info->gc_rt;
                outgoing->k.word |= RT_KEY_BIT;
            }
            #endif

            outgoing->kb_std[0] = outgoing_key_info->kb_std[0];

            #if defined(AIR_PRODUCT_TYPE_MOUSE)
            outgoing->k |= outgoing_key_info->ms_k;
            outgoing->kb_std[1] |= outgoing_key_info->kb_std[1];
            #if defined(AIR_WHEEL_REMAP)
            if(outgoing_key_info->ms_z1)
            {
                outgoing->z1 += outgoing_key_info->ms_z1;
                outgoing_key_info->ms_z1 = 0;
            }
            #endif /* AIR_WHEEL_REMAP */
            #else
            outgoing->ms_k = outgoing_key_info->ms_k;
            outgoing->kb_std[1] = outgoing_key_info->kb_std[1];
            #endif /* AIR_PRODUCT_TYPE_MOUSE */

            outgoing->kb_consumer = outgoing_key_info->kb_consumer;

            Kr_q_Ctrl->buf_tail = (Kr_q_Ctrl->buf_tail + 1) & REMAP_BUFFER_SIZE_MASK;
            key_remap_info->ready = false;
        }
    }
}
#endif /* CONFIG_AIR_KEY_REMAP_FRONTEND_CM33, AIR_KEY_REMAP_FRONTEND_RISCV */

#if defined(CONFIG_AIR_KEY_REMAP_BACKEND_CM33) || defined(AIR_KEY_REMAP_BACKEND_RISCV)
#if defined(CONFIG_AIR_KEY_REMAP_BACKEND_CM33)
ATTR_TEXT_IN_TCM
#endif
void key_remap_queue_push(T_REMAP_QUEUE_CTRL_S *Kr_q_Ctrl, T_REMAP_VALUES_S *outgoing_data, uint32_t key_status)
{
    if (key_remap_queue_is_full(Kr_q_Ctrl)) {
        // REMAP_LOGI(thisMOD, "key_remap_queue_push - Queue is full");
        return;
    }

    Kr_q_Ctrl->buf_head = (Kr_q_Ctrl->buf_head + 1) & REMAP_BUFFER_SIZE_MASK;
    T_REMAP_KEY_INFO_S *key_remap_info = &Kr_q_Ctrl->buffer[Kr_q_Ctrl->buf_head];
    T_REMAP_VALUES_S *key_info_write = &(key_remap_info->data);

    #if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    key_info_write->gc_k = outgoing_data->gc_k;
    key_info_write->gc_lt = outgoing_data->gc_lt;
    key_info_write->gc_rt = outgoing_data->gc_rt;
    #endif

    key_info_write->ms_k = outgoing_data->ms_k;
    key_info_write->ms_z1 = outgoing_data->ms_z1;

    /* Check kb std value */
    key_info_write->kb_std[0] = outgoing_data->kb_std[0];
    key_info_write->kb_std[1] = outgoing_data->kb_std[1];

    /* Check kb consumer value */
    key_info_write->kb_consumer = outgoing_data->kb_consumer;
    key_remap_info->ready = true;
}
#endif /* CONFIG_AIR_KEY_REMAP_BACKEND_CM33, AIR_KEY_REMAP_BACKEND_RISCV */
#endif /* AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP , CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */