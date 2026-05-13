
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

#ifndef __BT_CON_PORTING_H__
#define __BT_CON_PORTING_H__

#include <zephyr/kernel.h>
#include <stdint.h>
#include "tinycrypt/ecc.h"
#include "memory_attribute.h"
#include "hal_gpio_internal.h"
#include "hal_clock_internal.h"
#include "hal_flash.h"
#include "hal_spm.h"

#ifdef AIR_LOGGING_ENABLE
#include "air_logging.h"
#endif

#define ATTR_LOG_STRING      __attribute__ ((__section__(".log_string"))) static const char
//#define ATTR_TEXT_IN_TCM

#if CONFIG_BT_PKA_LIB_COSIM
#include "cosim_mdm.h"
#define PKA_DBG(fmt, ...) MDM_TM_PRINTF("%s (%p): " fmt, __func__, k_current_get(), ##__VA_ARGS__)
#define PKA_ASSERT(fmt, ...) MDM_InstTestFail()

#define LOG_MSG_I(log_type, msg, argc, ...)    \
do{ \
    MDM_TM_PRINTF(msg, ## __VA_ARGS__);\
}while(0)

#define LOG_MSG_D(log_type, msg, argc, ...)    \
do{ \
    MDM_TM_PRINTF(msg, ## __VA_ARGS__);\
}while(0)

#define LOG_MSG_W(log_type, msg, argc, ...)    \
do{ \
    MDM_TM_PRINTF(msg, ## __VA_ARGS__);\
}while(0)

#define LOG_MSG_E(log_type, msg, argc, ...)    \
do{ \
    MDM_TM_PRINTF(msg, ## __VA_ARGS__);\
}while(0)

#define DUMP_MSG_I(log_type, data, length, msg, ...)    \
do{ \
    MDM_TM_DUMP(data, length); \
}while(0)

#else
//#define PKA_DBG(fmt, ...) printk("%s (%p): " fmt, __func__, k_current_get(), ##__VA_ARGS__)
#define PKA_DBG(fmt, ...)

#undef _STRIZE
#define STRIZE(x) #x
#define _STRIZE(x) STRIZE(x)

#define PKA_ASSERT( x ) \
do{ \
    if (!(x)) { \
        *(uint32_t volatile*)0xA0010344 |= 2; \
        ATTR_LOG_STRING msg[] =  #x" ," "file: "__FILE__", line: "_STRIZE(__LINE__); \
        extern void light_assert_ex(const char *msg); \
        light_assert_ex(msg); \
    } \
}while (0)
//#define PKA_ASSERT(fmt, ...) __ASSERT(0, "%s %s %d", fmt, ##__VA_ARGS__)
//#define PKA_ASSERT(fmt, ...) __ASSERT(0, fmt, ...)

#if defined(AIR_LOGGING_ENABLE)
#define LOG_MSG_I(log_type, msg, argc, ...)    \
    LOG_MSGID_I(log_type, msg, argc, ##__VA_ARGS__)
#define LOG_MSG_D(log_type, msg, argc, ...)    \
do{ \
}while(0)
#define LOG_MSG_W(log_type, msg, argc, ...)    \
    LOG_MSGID_W(log_type, msg, argc, ##__VA_ARGS__)
#define LOG_MSG_E(log_type, msg, argc, ...)    \
    LOG_MSGID_E(log_type, msg, argc, ##__VA_ARGS__)

#define DUMP_MSG_I(log_type, data, length, msg, ...)    \
do{ \
    extern log_control_block_t log_control_block_##log_type; \
    LOG_HEXDUMP_I(&log_control_block_##log_type, msg, data, length, ##__VA_ARGS__); \
}while(0)

#else //AIR_LOGGING_ENABLE
#define LOG_MSG_I(log_type, msg, argc, ...)    \
do{ \
}while(0)

#define LOG_MSG_D(log_type, msg, argc, ...)    \
do{ \
}while(0)

#define LOG_MSG_W(log_type, msg, argc, ...)    \
do{ \
}while(0)

#define LOG_MSG_E(log_type, msg, argc, ...)    \
do{ \
printk(msg, ## __VA_ARGS__);\
}while(0)

#define DUMP_MSG_I(log_type, data, length, msg, ...)    \
do{ \
}while(0)
#endif //AIR_LOGGING_ENABLE
#endif

#define bt_pka_log_msgid_i(log_type, msg, argc, ...) \
do{ \
}while(0)
#define bt_pka_log_msgid_d(log_type, msg, argc, ...) \
do{ \
}while(0)
#define bt_pka_log_msgid_w(log_type, msg, argc, ...) \
do{ \
}while(0)
#define bt_pka_log_msgid_e(log_type, msg, argc, ...) \
do{ \
}while(0)

#ifdef HAL_CLOCK_MODULE_ENABLED
// hop clock to 78M
#define pka_hal_clock_mux_sel_hop_high() clock_mux_sel(CLK_BT_HOP_SEL, MUX_BT_HOP_IDX_OSC_HS_D2)
// mac clock to 64M
#define pka_hal_clock_mux_sel_mac_high() clock_mux_sel(CLK_BT_MAC_SEL, MUX_BT_MAC_IDX_XO_DBL)
// hop clock to 32M
#define pka_hal_clock_mux_sel_hop_low() clock_mux_sel(CLK_BT_HOP_SEL, MUX_BT_HOP_IDX_XO)
// // mac clock to 32M
#define pka_hal_clock_mux_sel_mac_low() clock_mux_sel(CLK_BT_MAC_SEL, MUX_BT_MAC_IDX_XO)
#define pka_hal_clock_bt_rx_adc_set_high() \
       {hal_clock_bt_rx_adc_set(CLK_BT_RX_ADC_AUTO);}
#define pka_hal_clock_bt_rx_adc_set_low() \
       {hal_clock_bt_rx_adc_set(CLK_BT_RX_ADC_32M);}
#define pka_set_vref_dcxo_sel(value) (DCXO_CFG->BGCORE_CTRL1_b.VREF_DCXO_SEL = value)
#define pka_set_vref_v2i_sel(value) (DCXO_CFG->BGCORE_CTRL0_b.VREF_V2I_SEL = value)
#else
#define pka_hal_clock_mux_sel_157x()
#define pka_hal_clock_mux_sel()
#define pka_set_vref_dcxo_sel(value)
#define pka_set_vref_v2i_sel(value)
#endif

typedef enum {
    LOG_DM2L,
    LOG_LC,
    LOG_COMMON,
    LOG_NUM
} pka_log_type_t;

typedef enum {
    PKA_DCXO_LP_MODE     = 0,//DCXO_LP_MODE = 0,
    PKA_DCXO_NORMAL_MODE = 1,//DCXO_NORMAL_MODE = 1,

} pka_dcxo_mode_t;

typedef enum {
    xNoAction = 0,              /* Notify the task without updating its notify value. */
    xSetBits,                   /* Set bits in the task's notification value. */
    xIncrement,                 /* Increment the task's notification value. */
    xSetValueWithOverwrite,     /* Set the task's notification value to a specific value even if the previous value has not yet been read by the task. */
    xSetValueWithoutOverwrite   /* Set the task's notification value if the previous value has been read by the task. */
} xNotifyAction;

typedef void (*pTimerCallBack)(void *ExpiredTimer);
typedef void (*pTaskFun)(void);
typedef void (*bt_isr_t)(uint32_t irq_number);

#define STATIC_ASSERT(COND,MSG) typedef char static_assertion_##MSG[(!!(COND))*2-1]
#define COMPILE_TIME_ASSERT4(X,MSG,L) STATIC_ASSERT(X,MSG##L)
#define COMPILE_TIME_ASSERT3(X,MSG,L) COMPILE_TIME_ASSERT4(X,MSG,_at_line_##L)
#define COMPILE_TIME_ASSERT2(X,MSG,L) COMPILE_TIME_ASSERT3(X,MSG,L)
#define COMPILE_TIME_ASSERT(X,MSG)    COMPILE_TIME_ASSERT2(X,MSG,__LINE__)

void pka_dcxo_mode(uint8_t mode);

const char *pka_os_get_task_name(void);

void pka_os_task_resume(void *taskHandle);

uint32_t  pka_os_task_resume_from_isr(void *taskHandle);

void *pka_os_get_timer_id(void *xTimer);

void pka_os_clear_all_timers(void);

void pka_os_cancel_timer(void *xTimer);

void *pka_os_create_timer(const char * const pcTimerName, void * const pvTimerID, void *pxCallbackFunction);

void pka_os_start_timer(void *xTimer, const uint32_t xTimerPeriodInMs);

void pka_os_task_suspend(void *taskHandle);

void pka_os_task_notify_wait(uint32_t  ulBitsToClearOnEntry, uint32_t  ulBitsToClearOnExit, uint32_t  *pulNotificationValue);

void pka_os_task_notify_from_isr(void* xTaskToNotify, uint32_t ulValue, uint32_t eAction, unsigned int *pxHigherPriorityTaskWoken);

void pka_os_task_notify(void *xTaskToNotify, uint32_t ulValue, uint32_t eAction);

void *pka_os_semaphore_init();

void pka_os_semaphore_take(void *pSemaphore);

void pka_os_semaphore_give(void *pSemaphore);

//void pka_os_task_create(TaskFunction_t fTaskEntry, const char * const taskName, uint32_t  stackSize, void * const pParameters, uint8_t  taskPriority, void* taskHandle);

uint32_t  pka_os_get_interrupt_mask(void);

void pka_os_restore_interrupt_mask(uint32_t  nvic_mask);

uint32_t pka_gpt_get_current_time(void);

void pka_hal_gpt_get_duration_count(uint32_t start_count, uint32_t end_count, uint32_t *duration_count);

uint32_t pka_hal_gpt_get_free_run_count_32K(void);

uint32_t pka_hal_gpt_get_free_run_count_1M(void);

void pka_os_register_bt_interrupt(bt_isr_t intr_handler);

void pka_os_register_bt_timer_interrupt(void* intr_handler);

void pka_os_enable_bt_and_timer_interrupt();

void pka_os_disable_bt_and_timer_interrupt();

void pka_os_yield_from_isr(void);

uint32_t pka_os_is_run_in_isr(void);

#if (1)
void pka_os_register_zb_interrupt(void* intr_handler);
void pka_os_enable_zb_interrupt();
void pka_os_disable_zb_interrupt();
#endif


uint32_t pka_os_get_lm_task_priority(void);

uint32_t pka_os_get_lc_task_priority(void);

uint32_t pka_os_get_lc_process_task_priority(void);


void pka_disable_all_irq_except_bt(void);


void pka_restore_all_irq_except_bt(void);

/* big endian input, output */
void pka_uECC_p192_compute_public_key(uint8_t *privatekey, uint8_t *publicKey);

void pka_uECC_p192_shared_secret(uint8_t *remotePublicKey, uint8_t *privatekey, uint8_t *DHKey);

void pka_uECC_p256_compute_public_key(uint8_t *privatekey, uint8_t *publicKey);

void pka_uECC_p256_shared_secret(uint8_t *remotePublicKey, uint8_t *privatekey, uint8_t *DHKey);

int8_t pka_hal_gpt_delay_us(uint32_t us);

void pka_external_hmac_sha256(uint8_t *input, uint8_t ilen, uint8_t *key, uint8_t keylen, uint8_t *output);

void pka_external_sha256(uint8_t *input, uint8_t ilen, uint8_t *output);

void pka_dvfs_lock_control_SpeedUpTo208M(uint8_t lock);

void pka_dvfs_lock_control_SpeedUpTo104M(uint8_t lock);

uint8_t pka_Get_EDR_Security_Connection_Enable(uint8_t Address[6], uint8_t Cod[3], uint8_t LMP_Version);

/* Attributes can only be added when defining a function, not when declaring it. */
void pka_hal_nvic_save_and_set_interrupt_mask_special(uint32_t *mask);

void pka_hal_nvic_restore_interrupt_mask_special(uint32_t mask);

void pka_hid_data_forward_callback_register(void* fHidMsCB);
void pka_hid_data_forward_callback_register_kb(void* fHidKbCB);


typedef union {
    uint32_t next;
    struct {
        uint16_t block_size;
        uint16_t block_num;
    } block_info;
} sub_info_t;

typedef struct {
    uint32_t start_addr;       // start address of N9-DSP share buffer
    uint32_t read_offset;      // read pointer of N9-DSP share buffer
    uint32_t write_offset;     // write pointer of N9-DSP share buffer
    sub_info_t sub_info;       // next read position in buf for DSP
    uint32_t sampling_rate;    // for AWS clock skew
    uint32_t length;           // total length of N9-DSP share buffer
    uint8_t  bBufferIsFull;    // buffer full flag, when N9 find there is no free buffer for putting a packet,
                               // set this flag = 1, DSP will reset this flag when data be taken by DSP
    uint8_t  notify_count;     // notify count
    int32_t  drift_comp_val;   // long term drift compensation value
    uint32_t anchor_clk;       // long term drift anchor clk
    uint32_t asi_base;         // As coming packet size in BLE/ULL UL
    uint32_t asi_cur;          // As CRC init in BLE DL , and apply coming packet size time in BLE/ULL UL
} n9_dsp_share_info_t, *n9_dsp_share_info_ptr;

typedef struct {
    uint32_t StartAddr;       // start address of share buffer
    uint16_t ReadIndex;  // read pointer of share buffer  : DSP monitor
    uint16_t WriteIndex; // write pointer of share buffer : Controller monitor
    uint32_t SampleRate; // sample rate for clock skew counting
    uint16_t MemBlkSize; // block length for each frame
    uint16_t MemBlkNum;  // number of block for frame usage
    uint32_t DbgInfoAddr; // start address of controller packet address table
    uint16_t FrameSampleNum;  // DSP notify audio
    uint16_t codec_type;      // Codec information
    uint16_t codec_config;    // Codec config information
    uint16_t NotifyCount;  // notify count of DSP notify controller not to sleep
    uint32_t ForwarderAddr; // forwarder buffer address
    uint32_t SinkLatency; // a2dp sink latency
    uint8_t role;//partner or agent
    char    rssi;//Received Signal Strength Indication
    uint8_t local_asi_en;//enable local asi or not
    uint8_t reserved; // reserved
} avm_share_buf_info_t, *avm_share_buf_info_ptr;

typedef struct {
    uint32_t iso_interval; /* Unit with BT clock (312.5us) */
    uint32_t dl_timestamp_clk; /* Unit with BT clock (312.5us), indicate the first anchor of DL */
    uint32_t dl_retransmission_window_clk; /* Unit with BT clock (312.5us), valid bit[27:2] */
    uint16_t dl_timestamp_phase; /* Unit with 0.5us, valid value: 0~2499 */
    uint16_t dl_retransmission_window_phase; /* Unit with 0.5us, valid value: 0~2499 */
    uint8_t  dl_ft;
    uint8_t  dl_packet_counter; /* ISO DL packet counter & 0xFF */
    uint8_t  ul_ft;
    uint8_t  ul_packet_counter; /* ISO UL packet counter & 0xFF */
    uint32_t ul_timestamp; /* Unit with BT clock (312.5us), indicate the first anchor of UL */
    uint32_t ISOAnchorClk;
    uint16_t ISOAnchorPhase;
    uint32_t ul_avm_info_addr;
    uint32_t dl_avm_info_addr;
} ble_init_play_info_t;


uint32_t pka_Send_LEAudio_PlayInfo_ToDSP(uint32_t Address);

void pka_rtc_switch_to_dcxo(uint8_t enable);

void pka_hal_bt_clock_enable(void);

uint8_t pka_is_dcxo_normal_mode(void);

uint8_t pka_get_dcxo_26m_fpm(void);

uint8_t pka_get_dcxo_26m_en(void);

void pmu_enable_power(uint8_t pmu_pdm, uint8_t operate);
void pmu_set_vpa_voltage(uint8_t oper);
uint8_t pka_get_sleep_handle_idx(uint8_t isA2dp);
uint32_t pka_hal_flash_otp_read(uint32_t start_address, uint8_t *buffer, uint32_t length);

void pka_spm_unmask_cmsys_wakeup_src(void);
void pka_spm_unmask_connsys_wakeup_src(void);
void pka_spm_mask_connsys_wakeup_src(void);
void pka_spm_direct_power_on_connsys(void);
void pka_spm_direct_power_off_connsys(void);
uint32_t pka_get_spm_slp_guard_time(void);
bool pka_hal_slp_lock_mcu_slp(void);
bool pka_hal_slp_unlock_mcu_slp(void);
void pka_hal_slp_lock_conn_ext_slp(void);
void pka_hal_slp_unlock_conn_ext_slp(void);
void pka_register_dump_callback(void* cb);
void pka_spm_control_mtcmos_zigbee_on(void);
void pka_spm_control_wfi_le(void);
void pka_spm_control_wfi_zb(void);
void pka_ram_blocks_control_bt_non_retention_ram_reinit(void);
void pka_spm_mask_cmsys_slp_wakeup_bt_wakeup_src(void);
//void pka_hal_mac_clock_out_by_gpio(void);
void pka_hal_dvfs_lock_control_lock(void);
void pka_hal_dvfs_lock_control_unlock(void);
void pka_hal_pmu_set_rftx_idx(uint8_t rftx_idx);
uint8_t pka_hal_pmu_get_rftx_idx(void);
#endif

