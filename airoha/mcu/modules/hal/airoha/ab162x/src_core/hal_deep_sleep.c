/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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

#ifdef HAL_DEEP_SLEEP_MODULE_ENABLED

#include "hal_deep_sleep.h"
#include "hal_pmu.h"
#include "hal_gpt.h"

static hal_deep_sleep_handler_t deep_sleep_handlers[DEEP_SLEEP_HANDLER_TABLE_MAX_NUM];
static uint8_t g_deep_sleep_handler_count = 0;

hal_deep_sleep_t hal_deep_sleep_entry_handler_register(hal_deep_sleep_handler_t deep_sleep_handler)
{
    uint8_t handler_index = deep_sleep_handler.handler_index;
    hal_deep_sleep_driver_handler_t deep_sleep_driver_handler = deep_sleep_handler.deep_sleep_driver_handler;
    if (deep_sleep_driver_handler == NULL)
    {
        return HAL_DEEP_SLEEP_ERROR_PARAMETER;
    }

    if (handler_index >= DEEP_SLEEP_HANDLER_TABLE_MAX_NUM)
    {
        return HAL_DEEP_SLEEP_ERROR_PARAMETER;
    }
    deep_sleep_handlers[handler_index].handler_index = handler_index;
    deep_sleep_handlers[handler_index].deep_sleep_driver_handler = deep_sleep_driver_handler;
    return HAL_DEEP_SLEEP_OK;
}
void hal_enter_deep_sleep_app_handler(void)
{
    uint16_t i = 0;
    for (i = 0; i < g_deep_sleep_handler_count; i++)
    {
        if(deep_sleep_handlers[i].deep_sleep_driver_handler != NULL)
        {
            printk("hal_enter_deep_sleep_app_handler-run index %d handler\r\n", i);
            deep_sleep_handlers[i].deep_sleep_driver_handler();
        }
    }
}

void hal_deep_sleep_routine(void)
{
    printk("hal_deep_sleep_routine\r\n");
    hal_gpt_delay_ms(100);
    /*run app handler*/
    hal_enter_deep_sleep_app_handler();

    /*spm enter deep sleep*/
    pmu_power_off_sequence(PMU_DEEPSLP);
}


hal_deep_sleep_t hal_deep_sleep_get_handler_index(uint8_t *output_handler_index)
{
    if(g_deep_sleep_handler_count >= (DEEP_SLEEP_HANDLER_TABLE_MAX_NUM))
    {
        return HAL_DEEP_SLEEP_ERROR;
    }
    *output_handler_index = g_deep_sleep_handler_count;
    printk("hal_deep_sleep_get_handler_index-return index =%d\r\n",g_deep_sleep_handler_count);
    g_deep_sleep_handler_count++;
    return HAL_DEEP_SLEEP_OK;
}



#endif /*HAL_DEEP_SLEEP_MODULE_ENABLED*/