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

#include "hal_ccni.h"

#ifdef HAL_CCNI_MODULE_ENABLED

#if defined(CORE_MCU)
#include "air_chip.h"
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/sys/__assert.h>
#include "hal_log.h"
#endif /* defined(CORE_MCU) */

#include "hal_memview.h"
#include "hal_ccni_config.h"
#include "hal_cross_core_config.h"
#include "memory_attribute.h"
#include "hal_nvic.h"
#include "hal_gpt.h"
#include "air_chip.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CCNI_MASK_OFFSET                    (offsetof(CCNI_REGISTER_T, MASK))
#define CCNI_SET_OFFSET                     (offsetof(CCNI_REGISTER_T, SET))
#define CCNI_CLR_OFFSET                     (offsetof(CCNI_REGISTER_T, CLR))
#define CCNI_STATUS_OFFSET                  (offsetof(CCNI_REGISTER_T, STATUS))

#define MAX_CCNI_RETRY_TIME                 (0xFFFFFFFF)
#define CCNI_RETRY_COUNT                    (3)
#define CCNI_RETRY_DURATION_US              (20)

#define CCNI_CCM_CORE_OFFSET                (CCM_CCNI_LEN/CCNI_CORE_NUMS)

#define CCNI_EVENT_MASK                     (0x1)
#define CCNI_EVENT_UNMASK                   (0x0)
#define CCNI_EVENT_CLEAR                    (0x1)

/* all 32 bits, write 1 clear */
#define CCNI_REG_EVENTS_CLEAR               (0xFFFFFFFF)
#define CCNI_REG_EVENTS_MASK                CCNI_REG_EVENTS_CLEAR

#define CCNI_MSG_BASE                       (CROSS_CORE_MEM_VARIABLE(ccni))

#if defined(CORE_MCU)
#define CCNI_RECEIVER                   RISCV2MCU_CCNI
#define CCNI_SENDER                     MCU2RISCV_CCNI
#else
#define CCNI_RECEIVER                   MCU2RISCV_CCNI
#define CCNI_SENDER                     RISCV2MCU_CCNI
#define __ASSERT(expr, msg)             \
                { \
                    if(!(expr)){ \
                        __asm__("j ."); \
                    } \
                }
#endif /* defined(CORE_MCU) */

static void ccni_irq_handler(hal_nvic_irq_t irq);

static hal_ccni_status_t s_ccni_init_status = HAL_CCNI_STATUS_NO_INIT;

/* hal_ccni_event_t => uint32_t
 * 1 byte SRC CORE | 1 byte DEST CORE | 2 bytes EVENT IDX
 * hal_ccni_core_t
 *
 *  For MCU2RISCV_CCNI:
 *    Sender: !!! MCU !!!
 *        Register(RW): MCU2RISCV_CCNI->SET
 *    Receiver: !!! Ibex !!!
 *        Register(RW): MCU2RISCV_CCNI->MASK
 *        Register(RW): MCU2RISCV_CCNI->CLR
 *        Register(R):  MCU2RISCV_CCNI->STATUS
 *
 *  For RISCV2MCU_CCNI:
 *    Sender: !!! Ibex !!!
 *        Register(RW): RISCV2MCU_CCNI->SET
 *    Receiver: !!! MCU !!!
 *        Register(RW): RISCV2MCU_CCNI->MASK
 *        Register(RW): RISCV2MCU_CCNI->CLR
 *        Register(R):  RISCV2MCU_CCNI->STATUS
 *
 */


hal_ccni_status_t hal_ccni_init(void)
{
    if (s_ccni_init_status == HAL_CCNI_STATUS_NO_INIT) {
#if defined(CORE_MCU)
        //clear all event when at MCU side and unmask all
        MCU2RISCV_CCNI->MASK = CCNI_REG_EVENTS_MASK;
        RISCV2MCU_CCNI->MASK = CCNI_REG_EVENTS_MASK;
        MCU2RISCV_CCNI->CLR = CCNI_REG_EVENTS_CLEAR;
        RISCV2MCU_CCNI->CLR = CCNI_REG_EVENTS_CLEAR;
        MCU2RISCV_CCNI->MASK = 0;
        RISCV2MCU_CCNI->MASK = 0;
        hal_nvic_register_isr_handler(RISCV_IRQ_GEN_IRQn, ccni_irq_handler);
        hal_nvic_enable_irq(RISCV_IRQ_GEN_IRQn);
#else
        hal_nvic_register_isr_handler(IRQ_GEN_IRQn, ccni_irq_handler);
        hal_nvic_enable_irq(IRQ_GEN_IRQn);
#endif
        return HAL_CCNI_STATUS_OK;
    } else {
        return s_ccni_init_status;
    }
}
#ifdef CONFIG_AIR_BYPASS_FLASH_RETURN_READY_ENABLE
void air_mpu_flash_access_check_entry(hal_nvic_irq_t irq_number, hal_ccni_event_t ccni_event);
void air_mpu_flash_access_check_exit(hal_nvic_irq_t irq_number);
#endif
extern const hal_ccni_function_t ccni_callback[HAL_CCNI_EVENT_MAX];
static void ccni_irq_handler(hal_nvic_irq_t irq)
{
    uint32_t i;
    uint32_t event;
    uint8_t *p_share_memory;
    uint32_t irq_event;

    (void)irq;
    irq_event = CCNI_RECEIVER->STATUS;
    for (i = 0; i < HAL_CCNI_EVENT_MAX; i++) {
        if (irq_event & (1 << i)) {
            if ((CCNI_RECEIVER->MASK) & (1 << i)) {
                continue;
            }
#ifdef CONFIG_AIR_BYPASS_FLASH_RETURN_READY_ENABLE
            air_mpu_flash_access_check_entry(RISCV_IRQ_GEN_IRQn, i);
#endif

#if defined(CORE_MCU)
            /* event from riscv to mcu, so that the ISR will be called */
            event = i | CCNI_EVENT_SRC_RISCV | CCNI_EVENT_DST_MCU;
#else
            /* event from mcu to riscv, so that the ISR will be called */
            event = i | CCNI_EVENT_SRC_MCU | CCNI_EVENT_DST_RISCV;
#endif
            hal_ccni_mask_event(event);
            __ASSERT(ccni_callback[i] != NULL, "CCNI Event Callback Not Ready");
            if (ccni_callback[i]) {
                if (i < HAL_CCNI_SUPPORT_MSG_MAX) {
                    /* the message needs to be written by the sender to the shared memory of the receiver */
#if defined(CORE_MCU)
                    p_share_memory = (uint8_t *)CCNI_MSG_BASE + (HAL_CCNI_CORE_MCU - 1) * CCNI_CCM_CORE_OFFSET + i * sizeof(hal_ccni_message_t);
#else
                    p_share_memory = (uint8_t *)CCNI_MSG_BASE + (HAL_CCNI_CORE_RISCV - 1) * CCNI_CCM_CORE_OFFSET + i * sizeof(hal_ccni_message_t);
#endif
                    ccni_callback[i](event, (hal_ccni_message_t *)p_share_memory);
                } else {
                    ccni_callback[i](event, NULL);
                }
            }
            hal_ccni_clear_event(event);
            hal_ccni_unmask_event(event);
#ifdef CONFIG_AIR_BYPASS_FLASH_RETURN_READY_ENABLE
            air_mpu_flash_access_check_exit(RISCV_IRQ_GEN_IRQn);
#endif
        }
    }
}


hal_ccni_status_t hal_ccni_query_event_status(hal_ccni_event_t event, uint32_t *data)
{
    hal_ccni_status_t status = HAL_CCNI_STATUS_OK;
    uint32_t mask;
    uint32_t src_core, dst_core, event_index;

    src_core = ((event & CCNI_EVENT_SRC_MASK) >> CCNI_EVENT_SRC_OFFSET);
    dst_core = ((event & CCNI_EVENT_DST_MASK) >> CCNI_EVENT_DST_OFFSET);
    event_index = event & CCNI_EVENT_IDX_MASK;

    if ((data == NULL) || \
        ((event & CCNI_EVENT_SRC_MASK) == ((event & CCNI_EVENT_DST_MASK) << 8)) || \
        (((event & CCNI_EVENT_IDX_MASK) >= HAL_CCNI_EVENT_MAX)) || \
        ((src_core < HAL_CCNI_CORE_START) || (src_core >= HAL_CCNI_CORE_END)) || \
        ((dst_core < HAL_CCNI_CORE_START) || (dst_core >= HAL_CCNI_CORE_END)) \
       ) {
        /* In the case of the following exceptions, HAL_CCNI_STATUS_INVALID_PARAMETER is returned.
         * 1. The data pointer used as the output value is NULL.
         * 2. The source and destination cores cannot be the same.
         * 3. The number of events cannot exceed expectations.
         * 4 & 5. The source or destination core does not exist.
         */
        return HAL_CCNI_STATUS_INVALID_PARAMETER;
    }

    hal_nvic_save_and_set_interrupt_mask(&mask);
    switch (dst_core) {
        case HAL_CCNI_CORE_MCU:
            *data = ((RISCV2MCU_CCNI->STATUS) & (1 << event_index)) ? HAL_CCNI_EVENT_STATUS_BUSY : HAL_CCNI_EVENT_STATUS_IDLE;
            break;
        case HAL_CCNI_CORE_RISCV:
            *data = ((MCU2RISCV_CCNI->STATUS) & (1 << event_index)) ? HAL_CCNI_EVENT_STATUS_BUSY : HAL_CCNI_EVENT_STATUS_IDLE;
            break;
    }
    hal_nvic_restore_interrupt_mask(mask);
    return status;
}

/**
 * @brief This function trigger an an interrupt of the destination processor.
 * @param[in] event is the interrupt name
 * @param[in] message is optional
 * @param[in] retry_time is retry time
 * @return status of the operation
 */
hal_ccni_status_t hal_ccni_set_event_with_retry(hal_ccni_event_t event, hal_ccni_message_t *message, uint32_t retry_time)
{
    hal_ccni_status_t status = HAL_CCNI_STATUS_OK;
    uint32_t mask;
    uint32_t *p_share_memory;
    uint32_t event_index;
    uint32_t timeout = 0;

    event_index = (event & CCNI_EVENT_IDX_MASK);
    if (
        /* CCNI only allows the current core to send events
         * (and message, is supported and with parameters) to others core. */
#if defined(CORE_MCU)
        (CCNI_EVENT_SRC_MCU != (event & CCNI_EVENT_SRC_MASK))  ||
        (CCNI_EVENT_DST_RISCV != (event & CCNI_EVENT_DST_MASK)) ||
#else
        (CCNI_EVENT_SRC_RISCV != (event & CCNI_EVENT_SRC_MASK)) ||
        (CCNI_EVENT_DST_MCU != (event & CCNI_EVENT_DST_MASK))  ||
#endif
        ((event & CCNI_EVENT_SRC_MASK) == ((event & CCNI_EVENT_DST_MASK) << 8)) || \
        ((HAL_CCNI_SUPPORT_MSG_MAX <= event_index) && (message != NULL))
    ) {
        return HAL_CCNI_STATUS_INVALID_PARAMETER;
    }

    hal_nvic_save_and_set_interrupt_mask(&mask);

    /* retry & timeout */
    while (1) {
        if (((CCNI_SENDER->STATUS) & (1 << event_index)) == HAL_CCNI_EVENT_STATUS_IDLE) {
            break;
        } else {
            if (0 == retry_time) {
                timeout = 1;
                break;
            } else {
                retry_time--;
                hal_gpt_delay_us(CCNI_RETRY_DURATION_US);
            }
        }
    }
    if (timeout) {
        hal_nvic_restore_interrupt_mask(mask);
        return HAL_CCNI_STATUS_BUSY;
    }

    if (event_index < HAL_CCNI_SUPPORT_MSG_MAX) {
#if defined(CORE_MCU)
        /* send msg to riscv */
        p_share_memory = (uint32_t *)((uint8_t *)CCNI_MSG_BASE + (HAL_CCNI_CORE_RISCV - 1) * CCNI_CCM_CORE_OFFSET);
#else
        /* send msg to mcu */
        p_share_memory = (uint32_t *)((uint8_t *)CCNI_MSG_BASE + (HAL_CCNI_CORE_MCU - 1) * CCNI_CCM_CORE_OFFSET);
#endif
        p_share_memory[event_index * 2] = message->data[0];
        p_share_memory[event_index * 2 + 1] = message->data[1];
    }

    (CCNI_SENDER->SET) |= (1 << event_index);
    hal_nvic_restore_interrupt_mask(mask);
    return status;
}

/**
 * @brief This function trigger an an interrupt of the destination processor.
 * @param[in] event is the interrupt name
 * @param[in] message is optional
 */
hal_ccni_status_t hal_ccni_set_event(hal_ccni_event_t event, hal_ccni_message_t *message)
{
    return hal_ccni_set_event_with_retry(event, message, MAX_CCNI_RETRY_TIME);
}



static hal_ccni_status_t ccni_write_register(hal_ccni_event_t event, uint32_t register_offset, uint32_t value)
{
    uint32_t reg_addr, mask;
    uint32_t src_core, dst_core, event_idx;

    src_core = ((event & CCNI_EVENT_SRC_MASK) >> CCNI_EVENT_SRC_OFFSET);
    dst_core = ((event & CCNI_EVENT_DST_MASK) >> CCNI_EVENT_DST_OFFSET);
    event_idx = event & CCNI_EVENT_IDX_MASK;

    if ((event_idx >= HAL_CCNI_EVENT_MAX) || \
        (src_core == dst_core) || \
        ((src_core < HAL_CCNI_CORE_START) || (src_core >= HAL_CCNI_CORE_END)) || \
        ((dst_core < HAL_CCNI_CORE_START) || (dst_core >= HAL_CCNI_CORE_END)) \
       ) {
        return HAL_CCNI_STATUS_INVALID_PARAMETER;
    }

    reg_addr = (uint32_t)CCNI_RECEIVER + register_offset;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    if (value == 0x1) {
        (*(volatile uint32_t *)reg_addr) |= (0x1 << event_idx);
    } else {
        (*(volatile uint32_t *)reg_addr) &= (~(0x1 << event_idx));
    }
    hal_nvic_restore_interrupt_mask(mask);
    return HAL_CCNI_STATUS_OK;
}

hal_ccni_status_t hal_ccni_clear_event(hal_ccni_event_t event)
{
    return ccni_write_register(event, CCNI_CLR_OFFSET, CCNI_EVENT_CLEAR);
}

hal_ccni_status_t hal_ccni_mask_event(hal_ccni_event_t event)
{
    return ccni_write_register(event, CCNI_MASK_OFFSET, CCNI_EVENT_MASK);
}

hal_ccni_status_t hal_ccni_unmask_event(hal_ccni_event_t event)
{
    return ccni_write_register(event, CCNI_MASK_OFFSET, CCNI_EVENT_UNMASK);
}

hal_ccni_status_t hal_ccni_deinit(void)
{
    return HAL_CCNI_STATUS_OK;
}

#if defined(CORE_MCU)

#if KERNELVERSION == 0x3030000
static int ccni_init(const struct device *dev)
{
    ARG_UNUSED(dev);
#elif KERNELVERSION >= 0x3070000
static int ccni_init(void) {
#else
#error "Unkown supported kernel version"
#endif
    return hal_ccni_init();
}

SYS_INIT(ccni_init, CONFIG_CCNI_INIT_LEVEL, CONFIG_CCNI_INIT_PRIORITY);
#endif /* defined(CORE_MCU) */

#ifdef __cplusplus
}
#endif

#endif /* HAL_CCNI_MODULE_ENABLED */

