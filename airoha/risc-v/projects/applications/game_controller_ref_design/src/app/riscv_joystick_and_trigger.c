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

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stdint.h"
#include "syslog.h"
#include "riscv_ccni.h"
#include "riscv_peripheral_sampling.h"
#include "pka_share.h"
#include "pka.h"
#include "hal_gpio_internal.h"
#include "hal_eint_internal.h"
#include "hal_gpt.h"
#include "hid_common.h"
#include "hal_saradc.h"
#include "hal_ccni.h"
#include "riscv_joystick_and_trigger.h"


log_create_module(riscv_joystick, PRINT_LEVEL_INFO);
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static bool joystick_and_trigger_filter_duplicate_flag = false;

/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
int32_t riscv_game_controller_joystick_and_trigger_early_handle(void)
{
    return 0;
}

int32_t riscv_game_controller_joystick_and_trigger_common_para_update(void)
{
    return 0;
}

int32_t riscv_joystick_and_trigger_get_raw_data(void)
{
    /* read adc value into the share memory */
    #if 1
    hal_saradc_get_data_immediately(&(hid_common->hid.adc.saradc_data));
    #else
    hid_common->hid.x = 0x0001;
    hid_common->hid.y = 0x0002;
    hid_common->hid.z = 0x0003;
    hid_common->hid.rz = 0x0004;
    #endif
    return 0;
}

int32_t riscv_joystick_and_trigger_do_calculations(T_OUTGOING_VALUES_S* outgoing)
{
    hal_ccni_message_t ccni_msg = {0};
    extern hal_ccni_status_t hal_ccni_set_event_with_retry(hal_ccni_event_t event, hal_ccni_message_t *message, uint32_t retry_time);
    ccni_msg.data[0] = hid_express_get_hid_flag();
    #if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    extern uint32_t riscv_game_controller_keys_get_polling_key_status(void);
    uint32_t key_status = riscv_game_controller_keys_get_polling_key_status();
    ccni_msg.data[1] = key_status;
    #endif

    /* trigger CM33 to do calcluations */
    hal_ccni_set_event_with_retry(IRQGEN_RISCV2MCU_EVENT5, &ccni_msg, 0);
    return 0;
}

int32_t riscv_joystick_and_trigger_get_calculated_data(uint32_t *x, uint32_t *y, uint32_t *z, uint32_t *rz, uint32_t *lt, uint32_t *rt)
{
    /* read finial joystick value form share memory */
    *x  = hid_common->hid.x;
    *y  = hid_common->hid.y;
    *z  = hid_common->hid.z;
    *rz = hid_common->hid.rz;

    /* read finial trigger value form share memory */
    *lt = hid_common->hid.lt;
    *rt = hid_common->hid.rt;

    return 0;
}

void riscv_joystick_and_trigger_reset_filter_duplicate(void)
{
    joystick_and_trigger_filter_duplicate_flag = false;
}

bool riscv_joystick_and_trigger_check_filter_duplicate(T_OUTGOING_VALUES_S* outgoing)
{
    bool ret = true;
    bool lt_filter = false;/* 0: normal data, 1:duplicated data */
    bool rt_filter = false;
    if (joystick_and_trigger_filter_duplicate_flag)
    {
        if (lt_is_digital()) {
            lt_filter = true;
        } else {
            lt_filter = (outgoing->lt == outgoing->last_lt) ? true : false;
        }
        if (rt_is_digital()) {
            rt_filter = true;
        } else {
            rt_filter = (outgoing->rt == outgoing->last_rt) ? true : false;
        }
        if (lt_filter && rt_filter
            && (outgoing->x == JOYSTICK_0_LEVEL_VALUE)  && (outgoing->last_x == JOYSTICK_0_LEVEL_VALUE)
            && (outgoing->y == JOYSTICK_0_LEVEL_VALUE)  && (outgoing->last_y == JOYSTICK_0_LEVEL_VALUE)
            && (outgoing->z == JOYSTICK_0_LEVEL_VALUE)  && (outgoing->last_z == JOYSTICK_0_LEVEL_VALUE)
            && (outgoing->rz == JOYSTICK_0_LEVEL_VALUE) && (outgoing->last_rz == JOYSTICK_0_LEVEL_VALUE)
            )
        {
            /* if the triggers are not presssed
            and the joysitcks are not used,
            the data is duplicated */
            ret = false;
        }
    }
    else
    {
        joystick_and_trigger_filter_duplicate_flag = true;
    }
    // LOG_MSGID_I(riscv_joystick," check_filter_duplicate:ret: %d. lt:%x %x. rt: %x %x. x:%x %x. y:%x %x", 9, ret,
    //                             outgoing->lt, outgoing->last_lt,
    //                             outgoing->rt, outgoing->last_rt,
    //                             outgoing->x, outgoing->last_x,
    //                             outgoing->y, outgoing->last_y);
    return ret;
}

void riscv_joystick_and_trigger_update_filter_duplicate(T_OUTGOING_VALUES_S* outgoing)
{
    joystick_and_trigger_filter_duplicate_flag = true;
}

void riscv_joystick_and_trigger_init(void)
{
#if 0
    hal_saradc_init(HAL_SARADC_DATA_RATE_HS_MODE,HAL_SARADC_MEASURE_DIV_MODE);
    hal_saradc_set_gpio_mode(hid_common->hid.adc.saradc_data.channel_mask, HAL_SARADC_GPIO_ANALOG_MODE);
#endif
    T_OUTGOING_VALUES_S *outgoing = hid_express_get_outgoing_data();
    outgoing->last_lt = 0;
    outgoing->last_rt = 0;
    outgoing->last_x = JOYSTICK_0_LEVEL_VALUE;
    outgoing->last_y = JOYSTICK_0_LEVEL_VALUE;
    outgoing->last_z = JOYSTICK_0_LEVEL_VALUE;
    outgoing->last_rz = JOYSTICK_0_LEVEL_VALUE;
    riscv_joystick_and_trigger_reset_filter_duplicate();
}

void riscv_joystick_and_trigger_deinit(void)
{
#if 0
    hal_saradc_deinit();
#endif

    riscv_joystick_and_trigger_reset_filter_duplicate();
}
#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */
