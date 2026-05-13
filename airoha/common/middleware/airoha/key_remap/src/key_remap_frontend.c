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

#if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#if defined(CONFIG_AIR_KEY_REMAP_FRONTEND_CM33) || defined(AIR_KEY_REMAP_FRONTEND_RISCV)
/* Includes ------------------------------------------------------------------*/
#include "key_remap_frontend.h"
#if defined(AIR_PRODUCT_TYPE_MOUSE)
#include "key_remap_backend.h"
#elif defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
#include "hal_ccni.h"
#include "hal_ccni_config.h"
#endif /* AIR_PRODUCT_TYPE_MOUSE */
#include "hid_common.h"
/* Private define ------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
#if defined(AIR_PRODUCT_TYPE_MOUSE)
#define MASK_KEY_BIT                  M_KEY_BIT_DPI | M_KEY_BIT_RR | M_KEY_BIT_PAIRING /* Didn't need to send */
#endif /* AIR_PRODUCT_TYPE_MOUSE */
/* Private macro -------------------------------------------------------------*/
log_create_module(kr_frontend, PRINT_LEVEL_INFO);
#define APP_CCNI_EVENT_TO_CM33    IRQGEN_RISCV2MCU_EVENT3
/* Private variables ---------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef struct {
    #if defined (AIR_FN_KEY_ENABLE)
    uint32_t fn_key;
    #endif
    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    uint32_t key_remap_enable;
    #elif defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    uint32_t key_remap_enable[2]; /* [0] for 32 buttons, [1] for linear LT, RT key remap*/
    uint32_t new_key[2];
    #endif
}T_KEY_REMAP_FRONTEND_CTRL_S;

static T_KEY_REMAP_FRONTEND_CTRL_S kr_ctrl = {0};
T_REMAP_QUEUE_CTRL_S Kr_q_Ctrl;
T_HID_KEY_REMAP_FRONTEND_S key_setting[KEY_NUMBER];
/* Public variables ----------------------------------------------------------*/
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
extern uint32_t lt_digital;
extern uint32_t rt_digital;
#endif
/* Private functions ---------------------------------------------------------*/
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
static void key_remap_send_queue_ccni(T_REMAP_QUEUE_CTRL_S *Kr_q_Ctrl)
{
    T_REMAP_QUEUE_PTR_S payload;
    payload.msg = HID_CCNI_MSG_KEY_REMAP_QUEUE;
    payload.ptr = Kr_q_Ctrl;
    hal_ccni_message_t msg;
    // hal_ccni_status_t status;

    memcpy((uint8_t*)msg.data, (uint8_t*)&payload, sizeof(T_REMAP_QUEUE_PTR_S));

    hal_ccni_set_event(APP_CCNI_EVENT_TO_CM33, &msg);

    // HID_DBG_LOG(kr_frontend, "key_remap_send_queue_ccni = %x %x", 2, Kr_q_Ctrl, payload.ptr);
}
#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */

#if defined(AIR_PRODUCT_TYPE_MOUSE)
void key_remap_frontend_process_xy(T_OUTGOING_VALUES_S *outgoing)
{
    key_remap_xy_pop(outgoing);
}

void key_remap_frontend_process(T_OUTGOING_VALUES_S *outgoing)
{
    uint32_t new_key = outgoing->k;
    uint32_t erase_bit = (kr_ctrl.key_remap_enable | MASK_KEY_BIT) & new_key;
    #if defined(AIR_FN_KEY_ENABLE)
    uint32_t fn_key_is_pressed  = (new_key & kr_ctrl.fn_key) == kr_ctrl.fn_key;
    #endif
    #if defined(AIR_WHEEL_REMAP)
    int new_z1 = outgoing->z1;
    #endif

    /* Erase pressed remap key*/
    if(erase_bit)
    {
        outgoing->k &= ~erase_bit;
    }

    #if defined(AIR_WHEEL_REMAP)
    #if defined (AIR_FN_KEY_ENABLE)
    /* Fn key has press and wheel has value, erase wheel */
    if((((kr_ctrl.key_remap_enable & WHEEL_UP_BIT) != 0) && (new_z1 > 0))||
    (((kr_ctrl.key_remap_enable & WHEEL_DOWN_BIT) != 0) && (new_z1 < 0)) || (fn_key_is_pressed && kr_ctrl.fn_key))
    #else
    /* Remap wheel has value, erase wheel */
    if((((kr_ctrl.key_remap_enable & WHEEL_UP_BIT) != 0) && (new_z1 > 0))||
    (((kr_ctrl.key_remap_enable & WHEEL_DOWN_BIT) != 0) && (new_z1 < 0)))
    #endif
    {
        outgoing->z1 = 0;
    }
    #endif

    /* If has remap key, update outgoing report */
    key_remap_queue_pop(&Kr_q_Ctrl, outgoing);
}
#elif defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
void key_remap_frontend_process(T_OUTGOING_VALUES_S *outgoing)
{
    uint32_t enable_bit = kr_ctrl.key_remap_enable[0];
    uint32_t new_key = outgoing->k.word & enable_bit;

    if (enable_bit & new_key)
    {
        outgoing->k.word &= ~enable_bit;
    }

    /* Check LT mode */
    if(lt_digital)
    {
        /* non-Linear */
        if (enable_bit & LT_KEY_BIT)
        {
            outgoing->lt = 0;
        }
    }

    /* Check RT mode */
    if(rt_digital)
    {
        /* non-Linear */
        if (enable_bit & RT_KEY_BIT)
        {
            outgoing->rt = 0;
        }
    }

    key_remap_queue_pop(&Kr_q_Ctrl, outgoing);
}
#endif

void key_remap_frontend_setting_update()
{
    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    kr_ctrl.key_remap_enable = hid_common->app.key_remap_enable;
    #elif defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    kr_ctrl.key_remap_enable[0] = hid_common->app.key_remap_enable[0];
    #endif

    for(uint32_t i = 0; i < KEY_NUMBER; i++)
    {
        hid_common_get_frontend_key_remap_data(&key_setting[i], i);
    }
}

void key_remap_frontend_init()
{
    memset(&kr_ctrl, 0, sizeof(kr_ctrl));
    key_remap_queue_init(&Kr_q_Ctrl);

    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    key_remap_set_queue(&Kr_q_Ctrl);
    #elif defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    key_remap_send_queue_ccni(&Kr_q_Ctrl);
    #endif

    #if defined(AIR_FN_KEY_ENABLE)
    kr_ctrl.fn_key = hid_common->app.key_remap_fn_key;
    // HID_DBG_LOG(remap_frontend, "kr_ctrl.fn_key = %x", 1, kr_ctrl.fn_key);
    #endif
    key_remap_frontend_setting_update();
}
#endif /* CONFIG_AIR_KEY_REMAP_FRONTEND_CM33, AIR_KEY_REMAP_FRONTEND_RISCV */
#endif /* AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */