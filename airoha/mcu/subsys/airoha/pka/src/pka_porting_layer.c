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


#include "air_chip.h"
#include <zephyr/kernel.h>

#include <zephyr/sys/atomic.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/sys/__assert.h>

#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/buf.h>

#if KERNELVERSION == 0x3030000
#include <zephyr/bluetooth/hci_err.h>
#elif KERNELVERSION >= 0x3070000
#include <zephyr/bluetooth/hci_types.h>
#else
#error "Unkown supported kernel version"
#endif

//#include <zephyr/drivers/bluetooth/hci_driver.h>
#include "pka_porting_layer.h"
#include "hal_nvic.h"
#include "hal_dvfs.h"
#include "hal_pmu.h"
#include "hal_gpt.h"        /* add for hal_gpt functions */
#include "hal_flash_disk_internal.h"        /* add for hal_flash_otp functions */
#include "hal_sleep_manager.h"   /* add for connsys sleep functions */
#include "hal_sleep_manager_internal.h"   /* add for connsys sleep functions */
#include "hal_spm.h"             /* add for connsys sleep functions */
#include "avm_external.h"       /* add for bt_pikachu_lib functions */
#include "hal_riscv_ctl.h"      /* add for hal wfi functions */
#include "hal_wdt.h"            /* add for hal wfi functions */
#include <stdlib.h>
#include "memory_attribute.h"
#ifdef AIR_SWLA_ENABLE
#include "swla.h"
#endif

static struct k_thread pka_dm2l_thread;
static K_KERNEL_STACK_DEFINE(dm2l_thread_stack, CONFIG_BT_PKA_DM2L_STACK_SIZE);
static struct k_sem pka_dm2l_thread_sem;

#if defined(AIR_LOGGING_ENABLE)
log_create_module(LOG_DM2L, PRINT_LEVEL_INFO);
log_create_module(LOG_LC, PRINT_LEVEL_INFO);
log_create_module(LOG_COMMON, PRINT_LEVEL_INFO);
#endif
extern int ram_blocks_control_bt_rw_data_non_retention_reinit(void);
extern int ram_blocks_control_bt_zi_data_non_retention_reinit(void);

void pka_dcxo_mode(uint8_t mode)
{
    PKA_DBG("");
    //dcxo_lp_mode(DCXO_NORMAL_MODE);
}

ATTR_TEXT_IN_TCM const char *pka_os_get_task_name(void)
{
    return k_thread_name_get(&pka_dm2l_thread);
}

#if 0
ATTR_TEXT_IN_TCM void pka_os_task_resume(void *taskHandle)
{
    PKA_DBG("");
    //vTaskResume(taskHandle);
}


ATTR_TEXT_IN_TCM uint32_t  pka_os_task_resume_from_isr(void *taskHandle)
{
    PKA_DBG("");
    return 0;//xTaskResumeFromISR(taskHandle);
}
#endif

ATTR_TEXT_IN_TCM void pka_os_yield_from_isr(void)
{
    PKA_DBG("");
    //portYIELD_FROM_ISR(true);
}

ATTR_TEXT_IN_TCM uint32_t pka_os_is_run_in_isr(void)
{
    PKA_DBG("");
#if 0
    if (HAL_NVIC_QUERY_EXCEPTION_NUMBER > 0) {
        /* is ISR context */
        return true;
    } else {
        /* is Task context */
        return false;
    }
#endif
    return 0;
}

#define MAX_DPC_TIMERS  (10)

struct k_timer dpc_timers[MAX_DPC_TIMERS];
void *dpc_timer_handle[MAX_DPC_TIMERS] = {0};

ATTR_TEXT_IN_TCM void *pka_os_get_timer_id(void *xTimer)
{
    uint32_t i;

    for (i = 0; i < MAX_DPC_TIMERS; i++) {
        if (&dpc_timers[i] == xTimer) {
            return dpc_timer_handle[i];
        }
    }

    return NULL;
}

ATTR_TEXT_IN_TCM void pka_os_clear_all_timers(void)
{
    uint32_t i;

    for (i = 0; i < MAX_DPC_TIMERS; i++) {
        if (dpc_timer_handle[i]) {
            k_timer_stop((struct k_timer *)(&dpc_timers[i]));
            dpc_timer_handle[i] = NULL;
        }
    }
}

ATTR_TEXT_IN_TCM void pka_os_cancel_timer(void *xTimer)
{
    uint32_t i;

    for (i = 0; i < MAX_DPC_TIMERS; i++) {
        if (&dpc_timers[i] == xTimer) {
            k_timer_stop((struct k_timer *)xTimer);
            dpc_timer_handle[i] = NULL;
            return;
        }
    }
}

ATTR_TEXT_IN_TCM void *pka_os_create_timer(const char *const pcTimerName, void *const pvTimerID, void *pxCallbackFunction)
{
    uint32_t i;

    for (i = 0; i < MAX_DPC_TIMERS; i++) {
        if (dpc_timer_handle[i] == NULL) {
            dpc_timer_handle[i] = pvTimerID;

            // dpc_timers[i] is assigned to dpc_timer_handle[i]
            k_timer_init(&dpc_timers[i], pxCallbackFunction, NULL);

            return (void*)&dpc_timers[i];
        }
    }

    return NULL;
}

ATTR_TEXT_IN_TCM void pka_os_start_timer(void *xTimer, uint32_t xTimerPeriodInMs)
{
    k_timer_start((struct k_timer *)xTimer, K_MSEC(xTimerPeriodInMs), K_NO_WAIT);
}

ATTR_TEXT_IN_TCM void pka_os_task_suspend(void *taskHandle)
{
    PKA_DBG("");
    // k_thread_suspend(&pka_dm2l_thread);
    k_sem_take(&pka_dm2l_thread_sem, K_FOREVER);
    //vTaskSuspend(taskHandle);
}

ATTR_TEXT_IN_TCM void pka_os_task_notify_wait(uint32_t  ulBitsToClearOnEntry, uint32_t  ulBitsToClearOnExit, uint32_t  *pulNotificationValue)
{
    PKA_DBG("");
    // k_thread_suspend(&pka_dm2l_thread);
    k_sem_take(&pka_dm2l_thread_sem, K_FOREVER);
    //xTaskNotifyWait(ulBitsToClearOnEntry, ulBitsToClearOnExit, pulNotificationValue, portMAX_DELAY);
}

ATTR_TEXT_IN_TCM void pka_os_task_notify_from_isr(void *xTaskToNotify, uint32_t  ulValue, uint32_t eAction, unsigned int *pxHigherPriorityTaskWoken)
{
    PKA_DBG("");
    // k_thread_resume(&pka_dm2l_thread);
    k_sem_give(&pka_dm2l_thread_sem);
    //xTaskNotifyFromISR(xTaskToNotify, ulValue, eAction, (BaseType_t*)pxHigherPriorityTaskWoken);
}

ATTR_TEXT_IN_TCM void pka_os_task_notify(void *xTaskToNotify, uint32_t ulValue, uint32_t eAction)
{
    PKA_DBG("");
    // k_thread_resume(&pka_dm2l_thread);
    k_sem_give(&pka_dm2l_thread_sem);
    //xTaskNotify(xTaskToNotify, ulValue, eAction);
}



void *pka_os_semaphore_init()
{
    PKA_DBG("");
    //return xSemaphoreCreateRecursiveMutex();
    return NULL;
}



ATTR_TEXT_IN_TCM void pka_os_semaphore_take(void *pSemaphore)
{
    PKA_DBG("");
#if 0
    if (xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED) {
        return;
    }

//   if(port_OsStart)
    {
        xSemaphoreTakeRecursive(pSemaphore, portMAX_DELAY);
    }
}

ATTR_TEXT_IN_TCM void pka_os_semaphore_give(void *pSemaphore)
{
    if (xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED) {
        return;
    }


    //if(port_OsStart)
    {
        xSemaphoreGiveRecursive(pSemaphore);
    }
#endif
}


void pka_os_task_create(void* fTaskEntry, const char *const taskName, uint32_t  stackSize, void *const pParameters, uint8_t  taskPriority, void *taskHandle)
{
    PKA_DBG("%s", taskName);
    //xTaskCreate(fTaskEntry, taskName, stackSize, pParameters, taskPriority, taskHandle);
    k_sem_init(&pka_dm2l_thread_sem, 0, 1);
    k_thread_create(
            &pka_dm2l_thread,
            dm2l_thread_stack,
            K_KERNEL_STACK_SIZEOF(dm2l_thread_stack),
            fTaskEntry,
            NULL,
            NULL,
            NULL,
            K_PRIO_COOP(CONFIG_BT_PKA_DM2L_PRIO),
            0,
            K_FOREVER);
    k_thread_name_set(&pka_dm2l_thread, taskName);
    k_thread_start(&pka_dm2l_thread);
}


ATTR_TEXT_IN_TCM uint32_t  pka_os_get_interrupt_mask(void)
{
    uint32_t  nvic_mask = 0;
    hal_nvic_save_and_set_interrupt_mask(&nvic_mask);
    return nvic_mask;
}

ATTR_TEXT_IN_TCM void pka_os_restore_interrupt_mask(uint32_t  nvic_mask)
{
    hal_nvic_restore_interrupt_mask(nvic_mask);
}

ATTR_TEXT_IN_TCM uint32_t pka_gpt_get_current_time(void)
{
    //PKA_DBG("");
    uint32_t cur_time = 0;

    //hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &cur_time);

    return cur_time;
}

void pka_os_register_bt_interrupt(bt_isr_t intr_handler)
{
    PKA_DBG("");
    hal_nvic_register_isr_handler(BT_IRQn, (hal_nvic_isr_t)intr_handler);
}

void pka_os_register_bt_timer_interrupt(void* intr_handler)
{
    PKA_DBG("");
    hal_nvic_register_isr_handler(BT_TIMER_IRQn, (hal_nvic_isr_t)intr_handler);
}

void pka_os_enable_bt_and_timer_interrupt()
{
    PKA_DBG("");
    hal_nvic_enable_irq(BT_IRQn);
    hal_nvic_enable_irq(BT_TIMER_IRQn);
}

void pka_os_disable_bt_and_timer_interrupt()
{
    PKA_DBG("");
    hal_nvic_disable_irq(BT_IRQn);
    hal_nvic_disable_irq(BT_TIMER_IRQn);
}

uint32_t pka_os_get_lm_task_priority(void)
{
    return CONFIG_BT_PKA_DM2L_PRIO;
    //return TASK_PRIORITY_SOFT_REALTIME;
}

uint32_t pka_os_get_lc_task_priority(void)
{
    PKA_DBG("");
    return 0;//TASK_PRIORITY_BT_CMD_TASK;
}
uint32_t pka_os_get_lc_process_task_priority(void)
{
    PKA_DBG("");
    return 0;//TASK_PRIORITY_BT_ROUTINE_TASK;
}


volatile uint32_t nvic_iser0 = 0;
volatile uint32_t nvic_iser1 = 0;
#define NVIC_BT_IRQS_MASK (0x0f)
#define NVIC_32_BIT_REG_MASK (0x1f)

/*Disable all irq except BT irq.*/
ATTR_TEXT_IN_TCM void pka_disable_all_irq_except_bt(void)
{
    PKA_DBG("");
#if 0
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    nvic_iser0 = NVIC->ISER[0];
    nvic_iser1 = NVIC->ISER[1];

    NVIC->ICER[0] = nvic_iser0;
    NVIC->ICER[1] = nvic_iser1 & (~(NVIC_BT_IRQS_MASK << (BT_IRQn & NVIC_32_BIT_REG_MASK)));
    hal_nvic_restore_interrupt_mask(mask);
#endif
}

ATTR_TEXT_IN_TCM void pka_restore_all_irq_except_bt(void)
{
    PKA_DBG("");
#if 0
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    NVIC->ISER[0] = nvic_iser0;
    NVIC->ISER[1] = NVIC->ISER[1] | (nvic_iser1 & (~(NVIC_BT_IRQS_MASK << (BT_IRQn & NVIC_32_BIT_REG_MASK))));
    nvic_iser0 = 0;
    nvic_iser1 = 0;
    hal_nvic_restore_interrupt_mask(mask);
#endif

}

#if (1)
void pka_os_register_zb_interrupt(void* intr_handler)
{
    hal_nvic_register_isr_handler(ZIGBEE_IRQn, (hal_nvic_isr_t)intr_handler);
}

void pka_os_enable_zb_interrupt()
{
    hal_nvic_enable_irq(ZIGBEE_IRQn);
}

void pka_os_disable_zb_interrupt()
{
    hal_nvic_disable_irq(ZIGBEE_IRQn);
}
#endif

int uECC_random(uint8_t *dest, unsigned size)
{
    PKA_DBG("");
#if 0
    uint32_t random_seed, i;
    uint32_t words = size / 4;
    uint32_t remain = (size - (words * 4));
    for (i = 0; i < words; i++) {
        if (hal_trng_get_generated_random_number(&random_seed) == HAL_TRNG_STATUS_OK) {
            *((uint32_t *)dest + i) = random_seed;
        } else {
            return 0;
        }
    }

    if (hal_trng_get_generated_random_number(&random_seed) == HAL_TRNG_STATUS_OK) {
        for (i = 0; i < remain; i++) {
            dest[4 * words + i] = (random_seed >> (8 * i)) & 0xFF;
        }
        return 1;
    } else {
        return 0;
    }
#endif
    return 0;
}



void pka_uECC_p192_compute_public_key(uint8_t *privatekey, uint8_t *publickey)
{
    PKA_DBG("");
    //using this API to generate random private key and public key
    //uECC_set_rng(&uECC_random);
    //uECC_make_key(publickey, privatekey, uECC_secp192r1());
}

void pka_uECC_p192_shared_secret(uint8_t *remotePublicKey, uint8_t *privatekey, uint8_t *DHKey)
{
    PKA_DBG("");
    /* big endian input */
    //uECC_shared_secret(remotePublicKey, privatekey, DHKey, uECC_secp192r1());
}

int8_t pka_hal_gpt_delay_us(uint32_t us)
{
    return hal_gpt_delay_us(us);
}

void pka_hal_gpt_get_duration_count(uint32_t start_count, uint32_t end_count, uint32_t *duration_count)
{
    PKA_DBG("");
    //hal_gpt_get_duration_count( start_count,  end_count, duration_count);
    return;
}


uint32_t pka_hal_gpt_get_free_run_count_1M(void)
{
#if 1
    uint32_t count = 0;
    int32_t ret = 0;

    ret = (int32_t)hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &count);

    if (ret < 0) {
        return 0;
    } else {
        return count;
    }
#endif
    return 0;
}


uint32_t pka_hal_gpt_get_free_run_count_32K(void)
{
    PKA_DBG("");
#if 0
    uint32_t count = 0;
    int32_t ret = 0;

    ret = (int32_t)hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &count);

    if (ret < 0) {
        return 0;
    } else {
        return count;
    }
#endif
    return 0;
}


void pka_uECC_p256_compute_public_key(uint8_t *privatekey, uint8_t *publickey)
{
    PKA_DBG("");
    //using this API to generate random private key and public key
    //uECC_set_rng(&uECC_random);
    //uECC_make_key(publickey, privatekey, uECC_secp256r1());
}

void pka_uECC_p256_shared_secret(uint8_t *remotePublicKey, uint8_t *privatekey, uint8_t *DHKey)
{
    PKA_DBG("");
    /* big endian input */
    //uECC_shared_secret(remotePublicKey, privatekey, DHKey, uECC_secp256r1());
}

#ifdef MBEDTLS_CONFIG_FILE
#include "mbedtls/md.h"
#include "mbedtls/sha256.h"
#endif

void pka_external_hmac_sha256(uint8_t *input, uint8_t ilen, uint8_t *key, uint8_t keylen, uint8_t *output)
{
    PKA_DBG("");
#ifdef MBEDTLS_CONFIG_FILE
    /* big endian input */
    mbedtls_md_hmac(mbedtls_md_info_from_type(MBEDTLS_MD_SHA256),
                    key, keylen, input, ilen, output);
#endif
}

void pka_external_sha256(uint8_t *input, uint8_t ilen, uint8_t *output)
{
    PKA_DBG("");
#ifdef MBEDTLS_CONFIG_FILE
    mbedtls_sha256(input, ilen, output, 0);
#endif
}

void pka_dvfs_lock_control_SpeedUpTo208M(uint8_t lock)
{
    PKA_DBG("");
#ifdef HAL_DVFS_MODULE_ENABLED
#ifdef AIR_BTA_IC_PREMIUM_G3
    //hal_dvfs_lock_control(HAL_DVFS_OPP_HIGH, lock); //High speed is not support 2021/10/18
#else
    //hal_dvfs_lock_control(HAL_DVFS_HIGH_SPEED_208M, lock);
#endif
#endif
}

void pka_dvfs_lock_control_SpeedUpTo104M(uint8_t lock)
{
    PKA_DBG("");
#ifdef HAL_DVFS_MODULE_ENABLED
#ifdef AIR_BTA_IC_PREMIUM_G3
    //hal_dvfs_lock_control(HAL_DVFS_OPP_MID, lock);
#else
    //hal_dvfs_lock_control(HAL_DVFS_FULL_SPEED_104M, lock);
#endif
#endif
}

ATTR_TEXT_IN_TCM void pka_hal_nvic_save_and_set_interrupt_mask_special(uint32_t *mask)
{
    //PKA_DBG("");
    hal_nvic_save_and_set_interrupt_mask_special(mask);
}

ATTR_TEXT_IN_TCM void pka_hal_nvic_restore_interrupt_mask_special(uint32_t mask)
{
    //PKA_DBG("");
    hal_nvic_restore_interrupt_mask_special(mask);
}

void pka_llcp_print(uint8_t *lmp_log_buffer_array, uint32_t *lmp_log_buffer_length_array, uint32_t ret_len)
{
#if defined(AIR_LOGGING_ENABLE)
    LOG_TLVDUMP_I(LOG_COMMON, LOG_TYPE_BT_LMP_LLCP_DATA, lmp_log_buffer_array, lmp_log_buffer_length_array, ret_len);
#endif
}

#ifdef AIR_BT_CODEC_BLE_ENABLED
#include "bt_sink_srv_ami.h"



uint32_t pka_Send_LEAudio_PlayInfo_ToDSP(uint32_t Address)
{
    PKA_DBG("");
#if 0
    bt_sink_srv_am_feature_t feature_param;
    ble_init_play_info_t *play_info;

    LOG_MSGID_I(common, "[BLE] pka_Send_LEAudio_PlayInfo_ToDSP enter", 0);

    play_info = (ble_init_play_info_t *)Address;
    LOG_MSGID_I(common, "[BLE] play_info->iso_interval %d", 1, play_info->iso_interval);
    LOG_MSGID_I(common, "[BLE] play_info->dl_timestamp_clk %d", 1, play_info->dl_timestamp_clk);
    LOG_MSGID_I(common, "[BLE] play_info->dl_timestamp_phase %d", 1, play_info->dl_timestamp_phase);
    LOG_MSGID_I(common, "[BLE] play_info->dl_retransmission_window_clk %d", 1, play_info->dl_retransmission_window_clk);
    LOG_MSGID_I(common, "[BLE] play_info->dl_retransmission_window_phase %d", 1, play_info->dl_retransmission_window_phase);
    LOG_MSGID_I(common, "[BLE] play_info->dl_ft %d", 1, play_info->dl_ft);
    LOG_MSGID_I(common, "[BLE] play_info->dl_packet_counter %d", 1, play_info->dl_packet_counter);
    LOG_MSGID_I(common, "[BLE] play_info->ul_timestamp %d", 1, play_info->ul_timestamp);
    LOG_MSGID_I(common, "[BLE] play_info->ul_ft %d", 1, play_info->ul_ft);
    LOG_MSGID_I(common, "[BLE] play_info->ul_packet_counter %d", 1, play_info->ul_packet_counter);

    feature_param.type_mask = AM_BLE;
    feature_param.feature_param.ble_param.event = BLE_FEATURE_EVENT_PLAY_INFO;
    feature_param.feature_param.ble_param.param.play_info = *(ble_init_play_info_t *)Address;

    return am_audio_set_feature_ISR(FEATURE_NO_NEED_ID, &feature_param);
#endif
}
#else
uint32_t pka_Send_LEAudio_PlayInfo_ToDSP(uint32_t Address)
{
    PKA_DBG("");
    return 0xFF;
}
#endif //end of #ifdef AIR_BT_CODEC_BLE_ENABLED

ATTR_TEXT_IN_TCM uint32_t pka_hal_ccni_mask_event(uint32_t event)
{
    PKA_DBG("");
    return 0;//hal_ccni_mask_event(event);
}

ATTR_TEXT_IN_TCM uint32_t pka_hal_ccni_clear_event(uint32_t event)
{
    PKA_DBG("");
    return 0;//hal_ccni_clear_event(event);
}

ATTR_TEXT_IN_TCM uint32_t pka_hal_ccni_unmask_event(uint32_t event)
{
    PKA_DBG("");
    return 0;//hal_ccni_unmask_event(event);
}

ATTR_TEXT_IN_TCM uint32_t pka_hal_ccni_set_event(uint32_t event, void *message)
{
    PKA_DBG("");
    return 0;//hal_ccni_set_event(CCNI_EVENT_SRC_CM4 | CCNI_EVENT_DST_DSP0 | event, message);
}

ATTR_TEXT_IN_TCM uint32_t pka_hal_ccni_TriggerDongleEncode(void *message)
{
    PKA_DBG("");
    return 0;//hal_ccni_set_event(CCNI_CM4_TO_DSP0_AUDIO_TRANSMITTER, message);
}
#if (AIR_BT_ULTRA_LOW_LATENCY_ENABLE)
extern void LC_ULL_DataEncodeRdy(uint32_t event, uint32_t *pMsg);

ATTR_TEXT_IN_TCM void bt_controller_receive_ull_encode_started_msg_from_dsp0(hal_ccni_event_t event, void *msg)
{
    PKA_DBG("");
    LC_ULL_DataEncodeRdy(event, msg);
}

#include "bt_sink_srv_ami.h"

ATTR_TEXT_IN_TCM  void pka_set_ull_play_en(uint32_t seq_no, uint32_t bt_clk)
{
    PKA_DBG("");
#if 0
    bt_sink_srv_am_feature_t feature_param;
    feature_param.type_mask = AM_AUDIO_BT_SET_PLAY_EN;
    feature_param.feature_param.play_en_param.sequence_number = seq_no;
    feature_param.feature_param.play_en_param.bt_clock = bt_clk;
    am_audio_set_feature_ISR(FEATURE_NO_NEED_ID, &feature_param);
#endif

    //hal_audio_set_a2dp_play_en(seq_no, bt_clk);
}

#endif

#include "hal_hw_semaphore.h"
#define HwSemRetryTimes 50000

volatile uint32_t int_mask;
ATTR_TEXT_IN_TCM  void pka_HWSemaphoreTake(void)
{
#if 1
    // uint32_t int_mask;
    uint32_t take_times = 0;

    /* Add hw semaphore to avoid multi-core access */
    while (++take_times) {
        if (HAL_HW_SEMAPHORE_STATUS_OK == hal_hw_semaphore_take(4)) {
            break;
        }

        if (take_times > HwSemRetryTimes) {
            //error handling
            PKA_ASSERT(0);
        }
    }
#endif
}

ATTR_TEXT_IN_TCM  void pka_HWSemaphoreGive(void)
{
#if 1
    // uint32_t int_mask;
    if (HAL_HW_SEMAPHORE_STATUS_OK != hal_hw_semaphore_give(4)) {
        //error handling
        PKA_ASSERT(0);
    }
#endif
}
void pka_rtc_switch_to_dcxo(uint8_t enable)
{
    PKA_DBG("");
    //hal_rtc_switch_to_dcxo(HAL_RTC_CLOCK_USER_CONSYS, enable);
}

uint8_t pka_is_dcxo_normal_mode(void)
{
    PKA_DBG("");
#if 0
    if((__get_dcxo_26m_fpm()==1)&&(__get_dcxo_26m_en()==1)){
        return TRUE;
    }else{
        return FALSE;
    }
#endif
    return 0;
}

uint8_t pka_get_dcxo_26m_fpm(void){
    PKA_DBG("");
    return 0;//__get_dcxo_26m_fpm();
}

uint8_t pka_get_dcxo_26m_en(void){
    PKA_DBG("");
    return 0;//__get_dcxo_26m_en();
}

uint8_t pka_Get_EDR_Security_Connection_Enable(uint8_t Address[6], uint8_t Cod[3], uint8_t LMP_Version)
{
    PKA_DBG("");
#if 0
    printf("Security_Connection:cod = %x,%x,%x", Cod[0], Cod[1], Cod[2]);
    printf("Security_Connection:LMP_Version = %d", LMP_Version);
    if(
#ifdef MTK_AWS_MCE_ENABLE
        !bt_device_manager_is_paired(Address) && (Cod[1] & (0x01 << 6)) &&
#endif
        !(LMP_Version < 12)){
        printf("Security_Connection,return true");
        return true;
    }
    printf("Security_Connection,return false");
#endif
    return false;
}

void pka_hal_bt_clock_enable(void)
{
    hal_clock_enable(HAL_CLOCK_CG_BT_HOP);
    hal_clock_enable(HAL_CLOCK_CG_BT_MAC_CONN);
    hal_clock_enable(HAL_CLOCK_CG_BT_MAC);
}
void pka_hal_bt_clock_disable(void)
{
    hal_clock_disable(HAL_CLOCK_CG_BT_HOP);
    hal_clock_disable(HAL_CLOCK_CG_BT_MAC_CONN);
    hal_clock_disable(HAL_CLOCK_CG_BT_MAC);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
void pka_assert(void)
{
    *(uint32_t volatile*)0xA0010344 |= 2; // stop hwmac
    PKA_ASSERT(0);
}
uint32_t bt_mm_get_total_free_size()
{
    return 0;
}
#endif

#if !defined(HAL_SLEEP_MANAGER_ENABLED)
uint32_t hal_sleep_manager_lock_sleep(uint8_t handle_index)
{
    PKA_DBG("");
    return 0;
}


uint32_t hal_sleep_manager_unlock_sleep(uint8_t handle_index)
{
    PKA_DBG("");
    return 0;
}
#endif


#if 0
uint32_t spm_latency_time_checking()
{
    PKA_DBG("");
    return 0;
}


uint32_t uECC_secp256r1()
{
    return 0;
}

uint32_t uECC_shared_secret(const uint8_t *public_key,
                            const uint8_t *private_key,
                            uint8_t *secret,
                            uint32_t curve)
{
    return 0;
}

int uECC_compute_public_key(const uint8_t *private_key, uint8_t *public_key, uint32_t curve)
{
    return 0;
}
#endif

void bt_os_layer_reverse_public_key(uint8_t *src_dst, uint32_t length)
{
    uint32_t i = 0, j;
    uint8_t temp_key;

    j = length - 1;
    while (i < j) {
        temp_key = src_dst[i];
        src_dst[i] = src_dst[j];
        src_dst[j] = temp_key;
        i++;
        j--;
    }
}

uint8_t bt_os_layer_validate_public_key(const uint8_t *public_key, uint8_t is_P256)
{
    PKA_DBG("");
    //uECC_Curve curve = is_P256 ? uECC_secp256r1() : uECC_secp192r1();
    /* uECC need Little Endian input, so need reverse the public_key. */
    if (is_P256) {/* P256, Gx, Gy is 256 bits. */
#if 0//uECC_VLI_NATIVE_LITTLE_ENDIAN != 0
        uint32_t key_len = (uint32_t)(256 / 8);
        bt_os_layer_reverse_public_key((uint8_t *)public_key, key_len);
        bt_os_layer_reverse_public_key((uint8_t *)public_key + key_len, key_len);
#endif
        return (uECC_valid_public_key(public_key, uECC_secp256r1()) == 0);
    } else {
        return 0;
    }
}

void pmu_enable_power(uint8_t pmu_pdm, uint8_t operate)
{
    PKA_DBG("");
}

void pmu_set_vpa_voltage(uint8_t oper)
{
    PKA_DBG("");
}

uint8_t pka_get_sleep_handle_idx(uint8_t isA2dp)
{
    PKA_DBG("");
#if 0
    if (isA2dp) {
        return SLEEP_LOCK_BT_CONTROLLER_A2DP;
    }
    else {
        return SLEEP_LOCK_BT_CONTROLLER;
    }
#else
return 0;
#endif
}

uint32_t pka_hal_flash_otp_read(uint32_t start_address, uint8_t *buffer, uint32_t length)
{
#if CONFIG_BT_PKA_LIB_COSIM
    return 0;
#else
    return hal_flash_otp_read(start_address, buffer, length);
#endif
}

void usb_hid_bt_callback(uint8_t * data, uint16_t len)
{
}

extern char* bt_pikachu_plugin_lib_lastest_commit(void);
void pka_print_lib_info()
{
    char* lib_ver = bt_pikachu_lib_verno();
    char* pkap_commit = bt_pikachu_plugin_lib_lastest_commit();
    char* pka_commit = bt_pikachu_lib_lastest_commit();

    LOG_MSG_I(LOG_COMMON, "bt_pikachu_lib_verno date = %c%c%c%c/%c%c/%c%c %c%c:%c%c:%c%c ", 14
        , lib_ver[0]
        , lib_ver[1]
        , lib_ver[2]
        , lib_ver[3]
        , lib_ver[4]
        , lib_ver[5]
        , lib_ver[6]
        , lib_ver[7]
        , lib_ver[8]
        , lib_ver[9]
        , lib_ver[10]
        , lib_ver[11]
        , lib_ver[12]
        , lib_ver[13]
        );

    LOG_MSG_I(LOG_COMMON, "bt_pikachu_plugin_lib_lastest_commit = %c%c%c%c%c%c%c", 7
        , pkap_commit[0]
        , pkap_commit[1]
        , pkap_commit[2]
        , pkap_commit[3]
        , pkap_commit[4]
        , pkap_commit[5]
        , pkap_commit[6]
        );
    LOG_MSG_I(LOG_COMMON, "bt_pikachu_lib_lastest_commit = %c%c%c%c%c%c%c", 7
        , pka_commit[0]
        , pka_commit[1]
        , pka_commit[2]
        , pka_commit[3]
        , pka_commit[4]
        , pka_commit[5]
        , pka_commit[6]
        );
}

extern void LC_LE_AIRHID_HidDataForwardCallBackRegister(void* fHidMsCB);
extern void LC_LE_AIRHID_HidDataForwardCallBackRegister_KB(void* fHidKbCB);


void pka_hid_data_forward_callback_register(void* fHidMsCB)
{
    LC_LE_AIRHID_HidDataForwardCallBackRegister(fHidMsCB);
}

void pka_hid_data_forward_callback_register_kb(void* fHidKbCB)
{
    LC_LE_AIRHID_HidDataForwardCallBackRegister_KB(fHidKbCB);
}

/*------------------------------------------------------------------------------------------------/
 $                                                                                                $
 $  CONNSYS sleep related API by HAL_SPM and HAL_SLEEP_MANAGER
 $                                                                                                $
 -------------------------------------------------------------------------------------------------*/

 /**************************************************************************
  *
  * Function :- pka_spm_direct_power_on_connsys
  *
  * Input : N/A
  *
  * Output : N/A
  *
  * Description: unmask connsys wakeup src for connsys
 **************************************************************************/
 void pka_spm_direct_power_on_connsys(void)
 {
     spm_bt_leave_standby_stage();
 }

 /**************************************************************************
  *
  * Function :- pka_spm_direct_power_off_connsys
  *
  * Input : N/A
  *
  * Output : N/A
  *
  * Description: unmask connsys wakeup src for connsys
 **************************************************************************/
 void pka_spm_direct_power_off_connsys(void)
 {
     spm_bt_enter_standby_stage();
 }

 /**************************************************************************
 *
 * Function :- pka_spm_unmask_cmsys_wakeup_src
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description: unmask connsys wakeup src for cmsys
**************************************************************************/
void pka_spm_unmask_cmsys_wakeup_src(void)
{
    spm_unmask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_CONNSYS_BT_TIMER);
    spm_unmask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_CONNSYS_ZB_TIMER);
    spm_unmask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_CONNSYS_BT_INT);
    spm_unmask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_CONNSYS_ZB_INT);
}

 /**************************************************************************
 *
 * Function :- pka_spm_mask_cmsys_slp_wakeup_bt_wakeup_src
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description: unmask connsys wakeup src for cmsys
**************************************************************************/
void pka_spm_mask_cmsys_slp_wakeup_bt_wakeup_src(void)
{
    spm_mask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_BT_TIMER);
}

/**************************************************************************
 *
 * Function :- pka_spm_unmask_connsys_wakeup_src
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description: unmask connsys wakeup src for connsys
**************************************************************************/
void pka_spm_unmask_connsys_wakeup_src(void)
{
    spm_unmask_wakeup_source(SPM_CFG_CONN_WAKEUP_SOURCE_MASK,  HAL_SPM_CONN_WAKEUP_SOURCE_BT_TIMER);
}

/**************************************************************************
 *
 * Function :- pka_spm_mask_connsys_wakeup_src
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description: unmask connsys wakeup src for connsys
**************************************************************************/
void pka_spm_mask_connsys_wakeup_src(void)
{
    spm_mask_wakeup_source(SPM_CFG_CONN_WAKEUP_SOURCE_MASK,  HAL_SPM_CONN_WAKEUP_SOURCE_BT_TIMER);
}

/**************************************************************************
 *
 * Function :- pka_get_spm_slp_guard_time
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description: get spm slp guard time
**************************************************************************/
uint32_t pka_get_spm_slp_guard_time(void)
{
    return spm_latency_time_checking();
}

/**************************************************************************
 *
 * Function :- pka_hal_riscv_stop
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description: ibex stop
**************************************************************************/
bool pka_hal_riscv_stop(void)
{
#if CONFIG_BT_PKA_LIB
    return hal_riscv_stop();
#else
    return false;
#endif
}

/**************************************************************************
 *
 * Function :- pka_spm_control_mtcmos_zigbee_on
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description: power on zigbee
**************************************************************************/
void pka_spm_control_mtcmos_zigbee_on(void)
{
    spm_control_mtcmos(SPM_MTCMOS_CONN_ZIGBEE, SPM_MTCMOS_PWR_ENABLE);
}

/**************************************************************************
 *
 * Function :- pka_spm_control_mtcmos_zigbee_off
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description: power off zigbee
**************************************************************************/
void pka_spm_control_mtcmos_zigbee_off(void)
{
    spm_control_mtcmos(SPM_MTCMOS_CONN_ZIGBEE, SPM_MTCMOS_PWR_DISABLE);
}

/**************************************************************************
 *
 * Function :- pka_spm_control_mtcmos_audiosys_off
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description: power off audiosys
**************************************************************************/
void pka_spm_control_mtcmos_audiosys_off(void)
{
    spm_control_mtcmos(SPM_MTCMOS_AUDIO_SYS, SPM_MTCMOS_PWR_DISABLE);
}
/**************************************************************************
 *
 * Function :- pka_spm_control_mtcmos_perisys_off
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description: power off perisys
**************************************************************************/
void pka_spm_control_mtcmos_perisys_off(void)
{
    spm_control_mtcmos(SPM_MTCMOS_PERISYS, SPM_MTCMOS_PWR_DISABLE);
}

/**************************************************************************
 *
 * Function :- pka_spm_control_mtcmos_rtcsys_off
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description: power off rtcsys
**************************************************************************/
void pka_spm_control_mtcmos_rtcsys_off(void)
{
    spm_control_mtcmos(SPM_MTCMOS_RTCSYS, SPM_MTCMOS_PWR_DISABLE);
}

/**************************************************************************
 *
 * Function :- pka_hal_slp_lock_mcu_slp
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description: get spm slp guard time
**************************************************************************/
ATTR_TEXT_IN_TCM bool pka_hal_slp_lock_mcu_slp(void)
{
    sleep_management_lock_sleep(LOCK_SLEEP, SLEEP_LOCK_BT_CONTROLLER);
    return true;
}

/**************************************************************************
 *
 * Function :- pka_hal_slp_unlock_mcu_slp
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description: get spm slp guard time
**************************************************************************/
ATTR_TEXT_IN_TCM bool pka_hal_slp_unlock_mcu_slp(void)
{
    sleep_management_lock_sleep(UNLOCK_SLEEP, SLEEP_LOCK_BT_CONTROLLER);
    return false;
}

/**************************************************************************
 *
 * Function :- pka_hal_log_global_turn_off
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description: disable uart and turn off log
**************************************************************************/
void pka_hal_log_global_turn_off(void)
{
    extern void log_global_turn_off(void);
    log_global_turn_off();
    hal_uart_deinit(HAL_UART_0);
    hal_uart_deinit(HAL_UART_1);
    hal_uart_deinit(HAL_UART_2);
}



/**************************************************************************
 *
 * Function :- pka_hal_slp_cmsys_pwr_down
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description: CMSYS power down
**************************************************************************/
void pka_hal_slp_cmsys_pwr_down(void)
{

    pka_hal_log_global_turn_off();

    uint8_t i;
    for (i = 0; i < IRQ_NUMBER_MAX; i++) {
        if (hal_nvic_get_pending_irq(i) == 1) {
            hal_nvic_clear_pending_irq(i);
        }
    }

    for (i = 0; i < IRQ_NUMBER_MAX; i++) {
        if (hal_nvic_get_pending_irq(i) == 1) {
            hal_nvic_clear_pending_irq(i);
        }
    }
    *SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    hal_sleep_manager_enter_sleep_mode(HAL_SLEEP_MODE_SLEEP);
}

/**************************************************************************
 *
 * Function :- pka_hal_slp_cmsys_wfi
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description: CMSYS enters WFI
**************************************************************************/
void pka_hal_slp_cmsys_wfi(void)
{
    hal_sleep_manager_enter_sleep_mode(HAL_SLEEP_MODE_IDLE);
}

/**************************************************************************
 *
 * Function :- pka_ram_blocks_control_bt_non_retention_ram_reinit
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description: reinit bt non retention rw/zi data on sysram
**************************************************************************/
void pka_ram_blocks_control_bt_non_retention_ram_reinit(void)
{
#if defined(AIR_RAM_BLOCKS_CONTROL_ENABLE)
    ram_blocks_control_bt_rw_data_non_retention_reinit();
    ram_blocks_control_bt_zi_data_non_retention_reinit();
#endif
}

/**************************************************************************
 *
 * Function :- pka_hal_slp_lock_ext_slp
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description: get spm slp guard time
**************************************************************************/
ATTR_TEXT_IN_TCM void pka_hal_slp_lock_conn_ext_slp(void)
{
    sleep_management_conn_lock_extslp(0x0);
    return;
}

/**************************************************************************
 *
 * Function :- pka_hal_slp_unlock_ext_slp
 *
 * Input : N/A
 *
 * Output : N/A
 *
 * Description: get spm slp guard time
**************************************************************************/
ATTR_TEXT_IN_TCM void pka_hal_slp_unlock_conn_ext_slp(void)
{
    sleep_management_conn_lock_extslp(0xf);
    return;
}

void pka_register_dump_callback(void* cb)
{
    exception_config_type callback_config;

    /* register callback to exception flow to dump hwmac rgs */
    callback_config.init_cb = (f_exception_callback_t)cb;
    callback_config.dump_cb = NULL;

    exception_register_callbacks(&callback_config);
}

#if 0
void pka_hal_mac_clock_out_by_gpio(void)
{
    extern bool hal_clock_out_by_gpio(uint8_t gpio_num, uint8_t clko_sel);

    hal_clock_dcm_ctrl_all(true);
    *TOP_DEBUG_CTRL__TOP_DEBUG_CTRL = 7;  // Select cksys_mon_out1[15:0]
    hal_clock_enable(HAL_CLOCK_CG_CKSYS_DEBUG_DIS);  // Enable Debug monitor
    hal_clock_out_by_gpio(6, 13);  // Measure GPIO6 for BT_MAC/2
    LOG_MSG_I(LOG_COMMON, "clock out by gpio", 0);
}
#endif

#if CONFIG_BT_PKA_LIB_COSIM
void pka_hal_clock_mux_sel_cmsys_high()
{
    // LPOSC Calibration

	*RTC_LPOSC_CON2__LPOSC_RBANK_CALI = 0x29;

	*RTC_LPOSC_CON2__LPOSC_RBANK_FT = 0x1A;

	// LPOSC Enable

	*RTC_LPOSC_CON2__LPOSC_RBANK_FT = 0;

	*RTC_LPOSC_CON2__LPOSC_RBANK_CALI = 0x28;

	*RTC_LPOSC_CON2__LPOSC_BIAS_SEL = 0x25;

	*RTC_LPOSC_CON2__LPOSC_CBANK_SEL = 0x0D;

	*RTC_LPOSC_CON3__LPOSC_HFOSC_HS_SEL = 0; /* default DIV2 */

	*RTC_LPOSC_CON3__LPOSC_HFOSC_LS_SEL = 1; /* default DIV6 */

	*CLKSQ_CON1__DA_LPOSC_EN = 1;

	hal_gpt_delay_us(5);

	*RTC_LPOSC_CON1__LPOSC_HFOSC_LS_EN = 1;

	*RTC_LPOSC_CON1__LPOSC_HFOSC_HS_EN = 1;

	*RTC_LPOSC_CON0__LPOSC_DIV3_CK_EN = 1;

	*RTC_LPOSC_CON0__LPOSC_DIV48_CK_EN = 1;

	hal_gpt_delay_us(15);

	*CLKSQ_CON1__RG_LPOSC_LS_RDY = 1;

	*CLKSQ_CON1__RG_LPOSC_HS_RDY = 1;

	*CLKSQ_CON1__RG_LPOSC_DIV3_RDY = 1;

	// Switch SYS clock to 156M

	volatile uint8_t *p_sel = NULL;

    volatile uint8_t *p_force_on = NULL;

    volatile uint8_t *p_chg = NULL;

    volatile uint8_t *p_chg_ok = NULL;

	p_sel = RTC_LPOSC_CON4__CLK_SYS_SEL;

	p_force_on = CKSYS_CLK_FORCE_ON_0__CLK_SYS_FORCE_ON;

	p_chg = CKSYS_CLK_UPDATE_0__CHG_SYS;

	p_chg_ok = CKSYS_CLK_UPDATE_STATUS_0__CHG_SYS_OK;

	*p_force_on = 1;

	*p_sel = 3;  // 156M

	*p_chg = 1;

	while(*p_chg);

	while(*p_chg_ok);

	*p_force_on = 0;

}
#endif

void pka_spm_control_wfi_le(void) {
    /* RISCV Stop */
    pka_hal_riscv_stop();

    /* MTCMOS Pwr Off */
    pka_spm_control_mtcmos_audiosys_off();
    pka_spm_control_mtcmos_perisys_off();
    pka_spm_control_mtcmos_rtcsys_off();
    pka_spm_control_mtcmos_zigbee_off();
#ifdef HAL_WDT_MODULE_ENABLED
    hal_wdt_disable(HAL_WDT_DISABLE_MAGIC);
#endif
    /* CMSYS Pwr Off */
    pka_hal_slp_cmsys_pwr_down();
}

void pka_spm_control_wfi_zb(void) {
    /* RISCV Stop */
    pka_hal_riscv_stop();

    /* MTCMOS Pwr Off */
    pka_spm_control_mtcmos_audiosys_off();
    pka_spm_control_mtcmos_perisys_off();
    pka_spm_control_mtcmos_rtcsys_off();

    /* MTCMOS Zigbee On */
    pka_spm_control_mtcmos_zigbee_on();
#ifdef HAL_WDT_MODULE_ENABLED
	hal_wdt_disable(HAL_WDT_DISABLE_MAGIC);
#endif
    /* CMSYS Pwr Off */
    pka_hal_slp_cmsys_pwr_down();
}

#define LABEL_BASE (6)
void pka_hcla_start(uint8_t label)
{
#ifdef AIR_SWLA_ENABLE
    HCLA_RamLogging_V2(SWLA_TYPE_LABEL, LABEL_BASE + label, SWLA_DIRECTION_START);
#endif
    return;
}

void pka_hcla_stop(uint8_t label)
{
#ifdef AIR_SWLA_ENABLE
    HCLA_RamLogging_V2(SWLA_TYPE_LABEL, LABEL_BASE + label, SWLA_DIRECTION_STOP);
#endif
    return;
}

void pka_hcla_label(uint8_t label)
{
#ifdef AIR_SWLA_ENABLE
    HCLA_RamLogging_V2(SWLA_TYPE_LABEL, LABEL_BASE + label, SWLA_DIRECTION_LABEL);
#endif
    return;
}

#if CONFIG_BT_PKA_LIB
extern pmu_rftx_idx_t pmu_rftx_idx;
#endif
void pka_hal_dvfs_lock_control_lock(void)
{
#if CONFIG_BT_PKA_LIB
    hal_dvfs_lock_control(HAL_DVFS_OPP_HIGH, HAL_DVFS_LOCK);
#endif
}
void pka_hal_dvfs_lock_control_unlock(void)
{
#if CONFIG_BT_PKA_LIB
    hal_dvfs_lock_control(HAL_DVFS_OPP_HIGH, HAL_DVFS_UNLOCK);
#endif
}
void pka_hal_pmu_set_rftx_idx(uint8_t rftx_idx)
{
#if CONFIG_BT_PKA_LIB
    pmu_rftx_idx = rftx_idx;
    pmu_volt_init(HAL_DVFS_VCORE_HIGH);
#endif
}

uint8_t pka_hal_pmu_get_rftx_idx(void)
{
#if CONFIG_BT_PKA_LIB
    return (uint8_t)pmu_rftx_idx;
#else
    return 0;
#endif
}
