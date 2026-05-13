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

#include <stdbool.h>
#if defined(AIR_PD_DOMAIN_CONTROL_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include "assert.h"
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include "hal_nvic.h"
#if defined(AIR_RAM_BLOCKS_CONTROL_ENABLE)
#include "ram_blocks_control.h"
#endif
#include "memory_attribute.h"
#include "soc.h"
#include "hal_sleep_manager_internal.h"

/* Private define ------------------------------------------------------------*/
#define thisMODULE pd_domain_control
LOG_MODULE_REGISTER(thisMODULE);

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static bool pd_domain_force_on;
static bool pd_domain_auto_on;
static bool pd_domain_is_off;

static uint32_t pd_domain_special_irq_flag[(CONFIG_NUM_IRQS+31)/32];

/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
int pd_domain_control_special_irq_set(hal_nvic_irq_t irq_number)
{
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    pd_domain_special_irq_flag[irq_number>>5] |= (0x1 << (irq_number - ((irq_number>>5)<<5)));
    hal_nvic_restore_interrupt_mask(mask);
    return 0;
}

int pd_domain_control_special_irq_clear(hal_nvic_irq_t irq_number)
{
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    pd_domain_special_irq_flag[irq_number>>5] &= ~(0x1 << (irq_number - ((irq_number>>5)<<5)));
    hal_nvic_restore_interrupt_mask(mask);
    return 0;
}

ATTR_TEXT_IN_TCM int pd_domain_control_special_irq_check(hal_nvic_irq_t irq_number)
{
    /* return pd_domain_special_irq_flag[irq_num/32].bit[irq_num%32] status,
       not use any multiplication,division and modules opeations for better performance */
    return (pd_domain_special_irq_flag[irq_number>>5] & (0x1 << (irq_number - ((irq_number>>5)<<5))));
}

ATTR_TEXT_IN_TCM int pd_domain_control_force_on_disable(void)
{
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    pd_domain_force_on = false;
    hal_nvic_restore_interrupt_mask(mask);

    return 0;
}

ATTR_TEXT_IN_TCM int pd_domain_control_force_on_enable(void)
{
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    if (pd_domain_is_off)
    {
        /* TODO: power on PD Domain */

        /* TODO: disable MPU protection for flash access */

        /* update state */
        pd_domain_is_off = false;
    }
    pd_domain_force_on = true;
    hal_nvic_restore_interrupt_mask(mask);

    return 0;
}

ATTR_TEXT_IN_TCM int pd_domain_control_auto_off(void)
{
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    if ((!pd_domain_is_off) && (!pd_domain_force_on))
    {
        /* TODO: enable MPU protection for flash access */

        /* TODO: power off PD Domain */

        /* update state */
        pd_domain_is_off = true;
        pd_domain_auto_on = false;
    }
    hal_nvic_restore_interrupt_mask(mask);

    return 0;
}

ATTR_TEXT_IN_TCM_RETENTION int pd_domain_control_auto_on(void)
{
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    if (pd_domain_is_off)
    {
        /* TODO: power on PD Domain */

        /* TODO: disable MPU protection for flash access */

        /* update state */
        pd_domain_is_off = false;
        pd_domain_auto_on = true;
    }
    hal_nvic_restore_interrupt_mask(mask);

    return 0;
}

int pd_domain_control_sfc_dpd_disable(void)
{
    sleep_management_SF_DPD_ctrl(false);
    printk("[pd_domain_control] pd domain control sfc dpd disable, LR: 0x%x \r\n", (uint32_t)__builtin_return_address(0));
    return 0;
}

int pd_domain_control_sfc_dpd_enable(void)
{
    sleep_management_SF_DPD_ctrl(true);
    printk("[pd_domain_control] pd domain control sfc dpd enable, LR: 0x%x \r\n", (uint32_t)__builtin_return_address(0));
    return 0;
}

ATTR_TEXT_IN_TCM_RETENTION int pd_domain_control_enter_sleep(sleep_management_infra_pd_module_t infra_pd_module)
{
    sleep_management_infra_pd_enter_sleep(infra_pd_module);
    return 0;
}

ATTR_TEXT_IN_TCM_RETENTION int pd_domain_control_exit_sleep(sleep_management_infra_pd_module_t infra_pd_module)
{
    sleep_management_infra_pd_exit_sleep(infra_pd_module);
    return 0;
}

int pd_domain_control_init(void)
{
    pd_domain_force_on = false;
    pd_domain_auto_on = false;
    pd_domain_is_off = false;

    LOG_INF("[pd_domain_control] init done.");

    return 0;
}

SYS_INIT(pd_domain_control_init, CONFIG_PD_DOMAIN_CONTROL_INIT_LEVEL, CONFIG_PD_DOMAIN_CONTROL_INIT_PRIORITY);

#endif /* AIR_PD_DOMAIN_CONTROL_ENABLE */
