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

#include "hal_dvfs.h"

#ifdef HAL_DVFS_MODULE_ENABLED
#include "hal_dvfs_internal.h"

#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>
#if IS_ENABLED(CONFIG_AIR_DAEMON_WORKQUEUE_ENABLE)
#include "air_daemon_work_q.h"
#endif

#if defined(__EXT_BOOTLOADER__) || defined(__EXT_DA__) || defined(FPGA_ENV) || !defined(CONFIG_MULTITHREADING)
#define _DVFS_DISABLED_
#define dvfs_prt_info(msg, cnt, ...)
#define dvfs_prt_warn(msg, cnt, ...)
#define dvfs_prt_err(msg, cnt, ...)
#else
//#include "syslog.h"
//#define dvfs_prt_info(msg, cnt, ...)             log_hal_msgid_info("[DVFS] "msg, cnt, ##__VA_ARGS__)
//#define dvfs_prt_warn(msg, cnt, ...)             log_hal_msgid_warning("[DVFS] "msg, cnt, ##__VA_ARGS__)
//#define dvfs_prt_err(msg, cnt, ...)              log_hal_msgid_error("[DVFS] "msg, cnt, ##__VA_ARGS__)
#define dvfs_prt_info(msg, cnt, ...)             printk("[DVFS] "msg"\r\n", ##__VA_ARGS__)
#define dvfs_prt_warn(msg, cnt, ...)             printk("[DVFS] "msg"\r\n", ##__VA_ARGS__)
#define dvfs_prt_err(msg, cnt, ...)              printk("[DVFS] "msg"\r\n", ##__VA_ARGS__)
#endif

#define dvfs_force_prt_info(msg, cnt, ...)       printk("[DVFS] "msg"\r\n", ##__VA_ARGS__)

/* -------------------------------------------------------------------------- */
#define DVFS_OPP_REF_CNT_MAX           32  /* Max lock count(times) of one OPP */

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
#ifndef _DVFS_DISABLED_
  #define DVFS_INIT_HV_4_A_WHILE
  #define HAL_DVFS_MEASURE_CRITICAL_SECTION_TIME_BY_GPT
  //#define DEBUG_MEASURE_BY_GPIO
  //#define DEBUG_TEST
  //#define HQA_TEST
#endif

#ifdef HAL_DVFS_MEASURE_CRITICAL_SECTION_TIME_BY_GPT
#include "hal_gpt_internal.h"
ATTR_ZIDATA_IN_TCM uint32_t dvfs_critical_time_start, dvfs_critical_time_end;
#endif /* HAL_DVFS_MEASURE_CRITICAL_SECTION_TIME_BY_GPT */

#ifdef DEBUG_MEASURE_BY_GPIO
#define DEBUG_GPIO_TRANS     6
#define DEBUG_GPIO_CLK       17
#define DEBUG_GPIO_PMU       18
extern void _gpio_set_mode(uint8_t pin_num, uint32_t mode);
extern void _gpio_set_dir_output(uint8_t pin_num);
extern void _gpio_output(uint8_t pin_num, uint8_t output_data);
#endif /* DEBUG_MEASURE_BY_GPIO */

#ifdef DEBUG_TEST
#include <stdlib.h>
#define DEBUG_STACK_SIZE          1024
#define DEBUG_THREAD_PRIORITY     5
#define DEBUG_THREAD_BASE_TIME    50
#define DEBUG_THREAD_ADD_TIME_MAX 100
//#define DEBUG_THREAD3_ENABLED
K_THREAD_STACK_DEFINE(debug_thread_stack1, DEBUG_STACK_SIZE);
K_THREAD_STACK_DEFINE(debug_thread_stack2, DEBUG_STACK_SIZE);
struct k_thread debug_thread_data1, debug_thread_data2;
#ifdef DEBUG_THREAD3_ENABLED
K_THREAD_STACK_DEFINE(debug_thread_stack3, DEBUG_STACK_SIZE);
struct k_thread debug_thread_data3;
#endif
struct k_work debug_work;
struct k_timer debug_timer;
#endif /* DEBUG_TEST */

#ifdef HQA_TEST
#include <stdlib.h>
#define HQA_STACK_SIZE          1024
#define HQA_THREAD_PRIORITY    (CONFIG_NUM_PREEMPT_PRIORITIES - 2)
#define HQA_THREAD_SWITCH_TIME  1000
K_THREAD_STACK_DEFINE(hqa_thread_stack1, HQA_STACK_SIZE);
struct k_thread hqa_thread_data1;
struct k_work hqa_work;
struct k_timer hqa_timer;
#endif /* HQA_TEST */

uint32_t dvfs_cpu_khz_tbl[HAL_DVFS_FRQ_MAX];
ATTR_ZIDATA_IN_TCM uint8_t dvfs_opp_ref_cnt[HAL_DVFS_OPP_TTL]; /* default all 0 */
ATTR_ZIDATA_IN_TCM uint8_t dvfs_sys_cfg;

/* -------------------------------------------------------------------------- */
ATTR_RWDATA_IN_TCM uint8_t dvfs_opp_vcore_cur = HAL_DVFS_VCORE_HIGH; /* HW default */
ATTR_RWDATA_IN_TCM uint8_t dvfs_opp_frq_cur;

typedef union {
    struct {
        uint8_t  vcore :4;
        uint8_t  frq   :4;
    } b;
    uint8_t val;
} dvfs_vcore_frq_t;

ATTR_RODATA_IN_TCM dvfs_vcore_frq_t dvfs_opp_vcore_frq_map_tbl[HAL_DVFS_OPP_TTL] =
{
    { .b.vcore = HAL_DVFS_VCORE_MID,   .b.frq = HAL_DVFS_FRQ_LOW  }, /* HAL_DVFS_OPP_LOW */
    { .b.vcore = HAL_DVFS_VCORE_MID,   .b.frq = HAL_DVFS_FRQ_MID  }, /* HAL_DVFS_OPP_MID */
    { .b.vcore = HAL_DVFS_VCORE_HIGH,  .b.frq = HAL_DVFS_FRQ_HIGH }, /* HAL_DVFS_OPP_HIGH */
    { .b.vcore = HAL_DVFS_VCORE_HIGH,  .b.frq = HAL_DVFS_FRQ_LOW  }  /* HAL_DVS_VCORE_HIGH */
};

/* -------------------------------------------------------------------------- */
#if !defined(_DVFS_DISABLED_) && !defined(HAL_DVFS_MASK_IRQ)
typedef struct {
    struct k_work work;
    uint32_t caller_addr;
    dvfs_frequency_t freq_idx;
    hal_dvfs_lock_parameter_t lock;
    uint8_t ring_buf_idx;
} dvfs_kwork_t;

#define DVFS_KWORK_RING_BUF_NUM    4

ATTR_ZIDATA_IN_TCM dvfs_kwork_t dvfs_kwork[DVFS_KWORK_RING_BUF_NUM];
ATTR_ZIDATA_IN_TCM uint8_t dvfs_kwork_ring_buf_write_idx, dvfs_kwork_ring_buf_ttl;

ATTR_ZIDATA_IN_TCM struct k_mutex dvfs_mutex;
#endif /* !_DVFS_DISABLED_ && !HAL_DVFS_MASK_IRQ */

/* -------------------------------------------------------------------------- */
#define RG_SRAM_DELSEL_SEL     *((volatile uint8_t *)0x42108042) /* PMU_DIG_CTRL12__SRAM_DELSEL_VOL */
#define SRAM_DELSEL_VOL_0p8V    1
#define SRAM_DELSEL_VOL_0p9V    0
#define SRAM_DELSEL_VOL_LOW     SRAM_DELSEL_VOL_0p8V
#define SRAM_DELSEL_VOL_HIGH    SRAM_DELSEL_VOL_0p9V

extern void pmu_volt_ctrl(hal_dvfs_vcore_t dvfs_sel);

#ifndef _DVFS_DISABLED_
/* -------------------------------------------------------------------------- */
typedef union {
    uint8_t value;
    struct {
        uint8_t init_hv_4_a_while        :1;
        uint8_t reserved                 :7;
    } b;
} T_DVFS_FLAG;

static T_DVFS_FLAG dvfs_flg;

/* -------------------------------------------------------------------------- */
ATTR_TEXT_IN_TCM void dvfs_switch(hal_dvfs_vcore_t vcore_next, hal_dvfs_frq_t frq_next)
{
    if((dvfs_opp_vcore_cur == vcore_next) && (dvfs_opp_frq_cur == frq_next)) {
        return;
    }
    if(dvfs_opp_vcore_cur != vcore_next) {    /* Vcore changed */
        if(dvfs_opp_frq_cur > HAL_DVFS_FRQ_LOW) { /* > 52MHz */
          #ifdef DEBUG_MEASURE_BY_GPIO
            _gpio_output(DEBUG_GPIO_TRANS, 1);
          #endif
            hal_clock_dvfs_transitive_stage();
          #ifdef DEBUG_MEASURE_BY_GPIO
            _gpio_output(DEBUG_GPIO_TRANS, 0);
          #endif
        }
        if(dvfs_opp_vcore_cur > vcore_next) { /* Vcore down */
            RG_SRAM_DELSEL_SEL = SRAM_DELSEL_VOL_LOW;
          #ifdef DEBUG_MEASURE_BY_GPIO
            _gpio_output(DEBUG_GPIO_CLK, 1);
          #endif
            hal_clock_dvfs_switch(frq_next);
          #ifdef DEBUG_MEASURE_BY_GPIO
            _gpio_output(DEBUG_GPIO_CLK, 0);
          #endif
          #ifdef DEBUG_MEASURE_BY_GPIO
            _gpio_output(DEBUG_GPIO_PMU, 1);
          #endif
            pmu_volt_ctrl(vcore_next);
          #ifdef DEBUG_MEASURE_BY_GPIO
            _gpio_output(DEBUG_GPIO_PMU, 0);
          #endif
        }
        else { /* Vcore up */
          #ifdef DEBUG_MEASURE_BY_GPIO
            _gpio_output(DEBUG_GPIO_PMU, 1);
          #endif
            pmu_volt_ctrl(vcore_next);
          #ifdef DEBUG_MEASURE_BY_GPIO
            _gpio_output(DEBUG_GPIO_PMU, 0);
          #endif
            RG_SRAM_DELSEL_SEL = SRAM_DELSEL_VOL_HIGH;
          #ifdef DEBUG_MEASURE_BY_GPIO
            _gpio_output(DEBUG_GPIO_CLK, 1);
          #endif
            hal_clock_dvfs_switch(frq_next);
          #ifdef DEBUG_MEASURE_BY_GPIO
            _gpio_output(DEBUG_GPIO_CLK, 0);
          #endif
        }
    }
    else { /* Vcore unchanged, Frequency changed */
        hal_clock_dvfs_switch(frq_next);
    }
    dvfs_opp_vcore_cur = vcore_next;
    dvfs_opp_frq_cur = frq_next;
}

ATTR_TEXT_IN_TCM void dvfs_enter_critical_section(dvfs_frequency_t freq_idx, hal_dvfs_lock_parameter_t lock)
{
#ifdef HAL_DVFS_MASK_IRQ
    uint32_t irq_mask = 0;
    hal_nvic_save_and_set_interrupt_mask_special(&irq_mask);
#else
    //dvfs_prt_info("mutex_lock count %d ......", 1, dvfs_mutex.lock_count);
    k_mutex_lock(&dvfs_mutex, K_FOREVER);
#endif
    /* ================ Critical Section Start ======================== */
#ifdef HAL_DVFS_MEASURE_CRITICAL_SECTION_TIME_BY_GPT
    //dvfs_critical_time_start = GPT(HAL_GPT_US_PORT)->GPT_COUNT;
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &dvfs_critical_time_start);
#endif

    /* Increase/Decrease OPP reference count */
    if(lock == HAL_DVFS_LOCK) {
        dvfs_opp_ref_cnt[freq_idx] ++;
    }
    else { /* HAL_DVFS_UNLOCK */
        dvfs_opp_ref_cnt[freq_idx] --;
    }

    /* Find the locked max Vcore and Frq */
    uint8_t max_vcore = 0, max_frq = 0;
    for(uint8_t i=0; i<HAL_DVFS_OPP_TTL; i++) {
        if(dvfs_opp_ref_cnt[i]) {
            if(dvfs_opp_vcore_frq_map_tbl[i].b.vcore > max_vcore) {
                max_vcore = dvfs_opp_vcore_frq_map_tbl[i].b.vcore;
            }
            if(dvfs_opp_vcore_frq_map_tbl[i].b.frq > max_frq) {
                max_frq = dvfs_opp_vcore_frq_map_tbl[i].b.frq;
            }
        }
    }
    dvfs_switch(max_vcore, max_frq);

#ifdef HAL_DVFS_MEASURE_CRITICAL_SECTION_TIME_BY_GPT
    //dvfs_critical_time_end = GPT(HAL_GPT_US_PORT)->GPT_COUNT;
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &dvfs_critical_time_end);
#endif
    /* ================ Critical Section End ======================== */
#ifdef HAL_DVFS_MASK_IRQ
    hal_nvic_restore_interrupt_mask_special(irq_mask);
#else
    //dvfs_prt_info("mutex_unlock", 0);
    k_mutex_unlock(&dvfs_mutex);
#endif
#ifdef HAL_DVFS_MEASURE_CRITICAL_SECTION_TIME_BY_GPT
    dvfs_prt_info("Switch Time: %dus", 1, dvfs_critical_time_end - dvfs_critical_time_start);
#endif
}

ATTR_TEXT_IN_TCM void dvfs_done_print(dvfs_frequency_t freq_idx, hal_dvfs_lock_parameter_t lock, uint32_t caller_addr)
{
    if(lock == HAL_DVFS_LOCK) {
        dvfs_prt_info("Lock Done: Opp %d, Caller 0x%08X, RefCnt %d %d %d %d, Vcore %d (%dmv), Frq %d, CpuKHz %d", 10,
                       freq_idx, caller_addr, dvfs_opp_ref_cnt[0], dvfs_opp_ref_cnt[1], dvfs_opp_ref_cnt[2], dvfs_opp_ref_cnt[3],
                       dvfs_opp_vcore_cur, hal_clock_get_vcore_mv(), dvfs_opp_frq_cur, dvfs_cpu_khz_tbl[dvfs_opp_frq_cur]);
    }
    else {
        dvfs_prt_info("Unlock Done: Opp %d, Caller 0x%08X, RefCnt %d %d %d %d, Vcore %d (%dmv), Frq %d, CpuKHz %d", 10,
                       freq_idx, caller_addr, dvfs_opp_ref_cnt[0], dvfs_opp_ref_cnt[1], dvfs_opp_ref_cnt[2], dvfs_opp_ref_cnt[3],
                       dvfs_opp_vcore_cur, hal_clock_get_vcore_mv(), dvfs_opp_frq_cur, dvfs_cpu_khz_tbl[dvfs_opp_frq_cur]);
    }
}

#ifndef HAL_DVFS_MASK_IRQ
ATTR_TEXT_IN_TCM void dvfs_kwork_handler(struct k_work *active_work)
{
    dvfs_kwork_t *pkwork = CONTAINER_OF(active_work, dvfs_kwork_t, work);

    dvfs_enter_critical_section(pkwork->freq_idx, pkwork->lock);
    dvfs_done_print(pkwork->freq_idx, pkwork->lock, pkwork->caller_addr);
    dvfs_kwork_ring_buf_ttl --;
    //dvfs_prt_info("RbIdx %d, Ttl %d", 2, pkwork->ring_buf_idx, dvfs_kwork_ring_buf_ttl);
}

ATTR_TEXT_IN_TCM bool dvfs_submit_work_queue(dvfs_frequency_t freq_idx, hal_dvfs_lock_parameter_t lock, uint32_t caller_addr)
{
    if(dvfs_kwork_ring_buf_ttl == DVFS_KWORK_RING_BUF_NUM) {
        dvfs_prt_err("dvfs_submit_work_queue(%d,%d,0x%08X) No free RB", 3, freq_idx, lock, caller_addr);
        return false;
    }

    uint32_t irq_mask = 0;
    hal_nvic_save_and_set_interrupt_mask(&irq_mask);
    /* ================ Critical Section Start ======================== */
    dvfs_kwork[dvfs_kwork_ring_buf_write_idx].freq_idx = freq_idx;
    dvfs_kwork[dvfs_kwork_ring_buf_write_idx].lock = lock;
    dvfs_kwork[dvfs_kwork_ring_buf_write_idx].caller_addr = caller_addr;
    dvfs_kwork[dvfs_kwork_ring_buf_write_idx].ring_buf_idx = dvfs_kwork_ring_buf_write_idx;

    uint8_t idx = dvfs_kwork_ring_buf_write_idx;

    dvfs_kwork_ring_buf_ttl ++;
    dvfs_kwork_ring_buf_write_idx ++;
    if(dvfs_kwork_ring_buf_write_idx == DVFS_KWORK_RING_BUF_NUM) {
        dvfs_kwork_ring_buf_write_idx = 0;
    }
    /* ================ Critical Section End ======================== */
    hal_nvic_restore_interrupt_mask(irq_mask);

    /* Should be -ENODEV=-19 that means "No such device" (the queue has not been started), or use k_is_pre_kernel() to check */
#if IS_ENABLED(CONFIG_AIR_DAEMON_WORKQUEUE_ENABLE)
    int result = air_daemon_wq_work_submit(&(dvfs_kwork[idx].work)); /* Submit to daemon work queue */
#else
    int result = k_work_submit(&(dvfs_kwork[idx].work)); /* Submit to system work queue */
#endif
    if(result < 0) {
        dvfs_prt_info("Kwork Submit result %d (work queue not stated)", 1, result);
        int result = k_work_cancel(&(dvfs_kwork[idx].work));
        dvfs_prt_info("Kwork Cancel result %d", 1, result);

        dvfs_kwork_ring_buf_ttl --;
        if(dvfs_kwork_ring_buf_write_idx == 0) {  /* should not happen */
            dvfs_kwork_ring_buf_write_idx = DVFS_KWORK_RING_BUF_NUM - 1;
        }
        else {
            dvfs_kwork_ring_buf_write_idx --;
        }

        dvfs_enter_critical_section(freq_idx, lock);
        dvfs_done_print(freq_idx, lock, caller_addr);
    }
    return true;
}
#endif /* !HAL_DVFS_MASK_IRQ */
#endif /* !_DVFS_DISABLED_ */

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* return KHz */
inline uint32_t hal_dvfs_get_cpu_frequency(void)
{
#ifdef _DVFS_DISABLED_
    return DCXO_KHZ;
#else
    return dvfs_cpu_khz_tbl[dvfs_opp_frq_cur];
#endif
}

dvfs_frequency_t hal_dvfs_get_cur_sys_opp(void)
{
#ifndef _DVFS_DISABLED_
    dvfs_vcore_frq_t vcore_frq_cur;

    vcore_frq_cur.b.vcore = dvfs_opp_vcore_cur;
    vcore_frq_cur.b.frq = dvfs_opp_frq_cur;
    for(uint8_t i=0; i<HAL_DVFS_OPP_NUM; i++) {
        if(vcore_frq_cur.val == dvfs_opp_vcore_frq_map_tbl[i].val) {
            return i;
        }
    }
    if(dvfs_opp_vcore_cur == HAL_DVFS_VCORE_HIGH) {
        return HAL_DVS_VCORE_HIGH;
    }
#endif /* !_DVFS_DISABLED_ */
    return 0;
}

inline hal_dvfs_frq_t hal_dvfs_get_cur_frq(void)
{
#ifdef _DVFS_DISABLED_
    return 0;
#else
    return dvfs_opp_frq_cur;
#endif
}

inline hal_dvfs_vcore_t hal_dvfs_get_cur_vcore(void)
{
#ifdef _DVFS_DISABLED_
    return 0;
#else
    return dvfs_opp_vcore_cur;
#endif
}

void dvfs_debug_dump(void)
{
#ifndef _DVFS_DISABLED_
    dvfs_prt_info("SysCfg %d, CpuKHz %d %d %d, RefCnt %d %d %d %d, Vcore %d (%dmv), Frq %d, CurCpuKHz %d", 12,
                   dvfs_sys_cfg, dvfs_cpu_khz_tbl[0], dvfs_cpu_khz_tbl[1], dvfs_cpu_khz_tbl[2],
                   dvfs_opp_ref_cnt[0], dvfs_opp_ref_cnt[1], dvfs_opp_ref_cnt[2], dvfs_opp_ref_cnt[3],
                   dvfs_opp_vcore_cur, hal_clock_get_vcore_mv(), dvfs_opp_frq_cur, dvfs_cpu_khz_tbl[dvfs_opp_frq_cur]);
#endif
}

#ifdef DEBUG_TEST
void debug_thread_entry1(void *p1, void *p2, void *p3)
{
    UNUSED_PARAMETER(p1);
    UNUSED_PARAMETER(p2);
    UNUSED_PARAMETER(p3);

    uint32_t tm, delay;
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &tm);
    srand(tm);

    bool lock = true;

    while (1) {
        delay = rand() % DEBUG_THREAD_ADD_TIME_MAX + DEBUG_THREAD_BASE_TIME;
        dvfs_prt_info("thread1: %d", 1, delay);
        k_sleep(K_MSEC(delay));

        hal_dvfs_lock_control(HAL_DVFS_OPP_MID, lock? HAL_DVFS_LOCK:HAL_DVFS_UNLOCK);
        if(lock) {
            lock = false;
        }
        else {
            lock = true;
        }
        k_sleep(K_MSEC(DEBUG_THREAD_BASE_TIME));
    }
}

void debug_thread_entry2(void *p1, void *p2, void *p3)
{
    UNUSED_PARAMETER(p1);
    UNUSED_PARAMETER(p2);
    UNUSED_PARAMETER(p3);

    uint32_t tm, delay;
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &tm);
    srand(tm);

    bool lock = true;

    while (1) {
        delay = rand() % DEBUG_THREAD_ADD_TIME_MAX + DEBUG_THREAD_BASE_TIME;
        dvfs_prt_info("thread2: %d", 1, delay);
        k_sleep(K_MSEC(delay));

        hal_dvfs_lock_control(HAL_DVFS_OPP_HIGH, lock? HAL_DVFS_LOCK:HAL_DVFS_UNLOCK);
        if(lock) {
            lock = false;
        }
        else {
            lock = true;
        }
        k_sleep(K_MSEC(DEBUG_THREAD_BASE_TIME));
    }
}

#ifdef DEBUG_THREAD3_ENABLED
void debug_thread_entry3(void *p1, void *p2, void *p3)
{
    UNUSED_PARAMETER(p1);
    UNUSED_PARAMETER(p2);
    UNUSED_PARAMETER(p3);

    uint32_t tm, delay;
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &tm);
    srand(tm);

    bool lock = true;

    while (1) {
        delay = rand() % DEBUG_THREAD_ADD_TIME_MAX + DEBUG_THREAD_BASE_TIME;
        dvfs_prt_info("thread3: %d", 1, delay);
        k_sleep(K_MSEC(delay));

        hal_dvfs_lock_control(HAL_DVS_VCORE_HIGH, lock? HAL_DVFS_LOCK:HAL_DVFS_UNLOCK);
        if(lock) {
            lock = false;
        }
        else {
            lock = true;
        }
        k_sleep(K_MSEC(DEBUG_THREAD_BASE_TIME));
    }
}
#endif /* DEBUG_THREAD3_ENABLED */

void debug_kwork_handler(struct k_work *work)
{
    UNUSED_PARAMETER(work);

    k_tid_t debug_thread_id1 = k_thread_create(&debug_thread_data1, debug_thread_stack1, DEBUG_STACK_SIZE,
        debug_thread_entry1, NULL, NULL, NULL, DEBUG_THREAD_PRIORITY, 0, K_NO_WAIT);
    k_tid_t debug_thread_id2 = k_thread_create(&debug_thread_data2, debug_thread_stack2, DEBUG_STACK_SIZE,
        debug_thread_entry2, NULL, NULL, NULL, DEBUG_THREAD_PRIORITY, 0, K_NO_WAIT);
    k_thread_start(debug_thread_id1);
    k_thread_start(debug_thread_id2);
#ifdef DEBUG_THREAD3_ENABLED
    k_tid_t debug_thread_id3 = k_thread_create(&debug_thread_data3, debug_thread_stack3, DEBUG_STACK_SIZE,
        debug_thread_entry3, NULL, NULL, NULL, DEBUG_THREAD_PRIORITY, 0, K_NO_WAIT);
    k_thread_start(debug_thread_id3);
#endif
}

void debug_timer_expiry_fn(struct k_timer *timer)
{
    UNUSED_PARAMETER(timer);
#if IS_ENABLED(CONFIG_AIR_DAEMON_WORKQUEUE_ENABLE)
    air_daemon_wq_work_submit(&debug_work); /* Submit to daemon work queue */
#else
    k_work_submit(&debug_work); /* Submit to system work queue */
#endif
}
#endif /* DEBUG_TEST */

#ifdef HQA_TEST
void hqa_thread_entry1(void *p1, void *p2, void *p3)
{
    UNUSED_PARAMETER(p1);
    UNUSED_PARAMETER(p2);
    UNUSED_PARAMETER(p3);

    bool lock = true;

    while (1) {
        hal_dvfs_lock_control(HAL_DVFS_OPP_HIGH, lock? HAL_DVFS_LOCK:HAL_DVFS_UNLOCK);
        if(lock) {
            lock = false;
        }
        else {
            lock = true;
        }
        k_sleep(K_MSEC(HQA_THREAD_SWITCH_TIME));
    }
}

void hqa_kwork_handler(struct k_work *work)
{
    UNUSED_PARAMETER(work);

    k_tid_t hqa_thread_id1 = k_thread_create(&hqa_thread_data1, hqa_thread_stack1, HQA_STACK_SIZE,
        hqa_thread_entry1, NULL, NULL, NULL, HQA_THREAD_PRIORITY, 0, K_NO_WAIT);
    k_thread_start(hqa_thread_id1);
}

void hqa_timer_expiry_fn(struct k_timer *timer)
{
    UNUSED_PARAMETER(timer);
#if IS_ENABLED(CONFIG_AIR_DAEMON_WORKQUEUE_ENABLE)
    air_daemon_wq_work_submit(&hqa_work); /* Submit to daemon work queue */
#else
    k_work_submit(&hqa_work); /* Submit to system work queue */
#endif
}
#endif /* HQA_TEST */

hal_dvfs_status_t hal_dvfs_init(void)
{
    dvfs_prt_info("hal_dvfs_init", 0);

#ifndef _DVFS_DISABLED_
    dvfs_flg.value = 0;
    dvfs_sys_cfg = hal_clock_dvfs_get_sys_cfg();
    for(uint8_t i=0; i<HAL_DVFS_FRQ_MAX; i++) {
        dvfs_cpu_khz_tbl[i] = hal_clock_get_cmsys_freq_hz_by_mux_idx(hal_clock_dvfs_get_cmsys_mux_idx(i)) / 1000;
    }

    /* Check initial CLK_SYS_SEL mux selection from init_clk_mux_tbl in hal_clock.c */
    if(clock_mux_cur_sel(CLK_SYS_SEL) == hal_clock_dvfs_get_cmsys_mux_idx(HAL_DVFS_FRQ_HIGH)) {
        dvfs_opp_frq_cur = HAL_DVFS_FRQ_HIGH;
    }
    else {
        dvfs_opp_frq_cur = HAL_DVFS_FRQ_MID;
    }

    /* Lock the first OPP */
    uint8_t opp = HAL_DVFS_OPP_MID;
    if(dvfs_sys_cfg == AIR_DVFS_SYS_CFG_FIX_HIGH) {
        opp = HAL_DVFS_OPP_HIGH;
    }
    //else if(dvfs_sys_cfg == AIR_DVFS_SYS_CFG_BASE_MID) {
    //    opp = HAL_DVFS_OPP_MID;
    //}
    dvfs_opp_ref_cnt[HAL_DVFS_OPP_LOW] = 1;
    dvfs_opp_ref_cnt[opp] = 1;
#ifdef DVFS_INIT_HV_4_A_WHILE
    if(opp != HAL_DVFS_OPP_HIGH) {
        opp = HAL_DVFS_OPP_HIGH;
        dvfs_opp_ref_cnt[HAL_DVFS_OPP_HIGH] = 1;
        dvfs_flg.b.init_hv_4_a_while = 1;
        dvfs_prt_info("Lock init HV", 0);
    }
#endif
    dvfs_switch(dvfs_opp_vcore_frq_map_tbl[opp].b.vcore, dvfs_opp_vcore_frq_map_tbl[opp].b.frq);
    dvfs_prt_info("Lock 1st OPP %d, SYS %d KHz, Vcore %d mv", 3, opp, hal_dvfs_get_cpu_frequency(), hal_clock_get_vcore_mv());

#ifdef HAL_DVFS_MASK_IRQ
    dvfs_prt_info("HAL_DVFS_MASK_IRQ defined", 0);
#else
    for(opp=0; opp<DVFS_KWORK_RING_BUF_NUM; opp++) { /* reuse opp */
        k_work_init(&(dvfs_kwork[opp].work), dvfs_kwork_handler);
    }
    k_mutex_init(&dvfs_mutex);
#endif

#ifdef DEBUG_MEASURE_BY_GPIO
    _gpio_set_mode(DEBUG_GPIO_TRANS, 0);
    _gpio_set_mode(DEBUG_GPIO_CLK, 0);
    _gpio_set_mode(DEBUG_GPIO_PMU, 0);
    _gpio_set_dir_output(DEBUG_GPIO_TRANS);
    _gpio_set_dir_output(DEBUG_GPIO_CLK);
    _gpio_set_dir_output(DEBUG_GPIO_PMU);
    _gpio_output(DEBUG_GPIO_TRANS, 0);
    _gpio_output(DEBUG_GPIO_CLK, 0);
    _gpio_output(DEBUG_GPIO_PMU, 0);
#endif /* DEBUG_MEASURE_BY_GPIO */

#ifdef DEBUG_TEST
    k_work_init(&debug_work, debug_kwork_handler);
    k_timer_init(&debug_timer, debug_timer_expiry_fn, NULL);
    k_timer_start(&debug_timer, K_MSEC(3000), Z_TIMEOUT_NO_WAIT);
#endif /* DEBUG_TEST */

#ifdef HQA_TEST
    k_work_init(&hqa_work, hqa_kwork_handler);
    k_timer_init(&hqa_timer, hqa_timer_expiry_fn, NULL);
    k_timer_start(&hqa_timer, K_MSEC(3000), Z_TIMEOUT_NO_WAIT);
#endif /* HQA_TEST */

    //hal_dvfs_lock_control(HAL_DVFS_OPP_HV, HAL_DVFS_LOCK); /* for test only */

#else /* !_DVFS_DISABLED_ */
    dvfs_force_prt_info("Function Disabled", 0);
#endif
    return HAL_DVFS_STATUS_OK;
}

ATTR_TEXT_IN_TCM hal_dvfs_status_t hal_dvfs_lock_control(dvfs_frequency_t freq_idx, hal_dvfs_lock_parameter_t lock)
{
#ifdef _DVFS_DISABLED_
    UNUSED_PARAMETER(freq_idx);
    UNUSED_PARAMETER(lock);
#else
    uint32_t xLinkRegAddr = (uint32_t)__builtin_return_address(0);

    if((freq_idx >= HAL_DVFS_OPP_TTL) || (lock > HAL_DVFS_LOCK)) {
        dvfs_prt_err("LockCtrl INVALID_PARAM(%d,%d), Caller 0x%08X", 3, freq_idx, lock, xLinkRegAddr);
        return HAL_DVFS_STATUS_INVALID_PARAM;
    }

    if(dvfs_sys_cfg == AIR_DVFS_SYS_CFG_FIX_HIGH) {
        dvfs_prt_warn("LockCtrl inhibited because CFG_FIX_HIGH, Caller 0x%08X", 1, xLinkRegAddr);
        return HAL_DVFS_STATUS_NOT_PERMITTED;
    }
    else if((dvfs_sys_cfg == AIR_DVFS_SYS_CFG_BASE_MID) && (freq_idx == HAL_DVFS_OPP_LOW)) {
        dvfs_prt_warn("LockCtrl inhibited because CFG_BASE_MID, Caller 0x%08X", 1, xLinkRegAddr);
        return HAL_DVFS_STATUS_NOT_PERMITTED;
    }

    /* Unbalanced check */
    if(lock == HAL_DVFS_LOCK) {
        if(dvfs_opp_ref_cnt[freq_idx] >= DVFS_OPP_REF_CNT_MAX) {
            dvfs_prt_err("Lock: RefCnt Max %d: Opp %d, Caller 0x%08X", 3, DVFS_OPP_REF_CNT_MAX, freq_idx, xLinkRegAddr);
            assert(0);
            return HAL_DVFS_STATUS_ERROR;
        }
    }
    else { /* HAL_DVFS_UNLOCK */
        if(!dvfs_opp_ref_cnt[freq_idx]) {
            dvfs_prt_err("Unlock: RefCnt 0: Opp %d, Caller 0x%08X", 2, freq_idx, xLinkRegAddr);
            assert(0);
            return HAL_DVFS_STATUS_ERROR;
        }
    }

    if(lock == HAL_DVFS_LOCK) {
        dvfs_prt_info("Lock Start: Opp %d, Caller 0x%08X", 2, freq_idx, xLinkRegAddr);
    }
    else {
        dvfs_prt_info("Unlock Start: Opp %d, Caller 0x%08X", 2, freq_idx, xLinkRegAddr);
    }

#ifdef HAL_DVFS_MASK_IRQ
    dvfs_enter_critical_section(freq_idx, lock);
    dvfs_done_print(freq_idx, lock, xLinkRegAddr);
#else
    if(k_is_in_isr()) {  /* can't use mutex */
        dvfs_prt_warn("Caller 0x%08X from ISR", 1, xLinkRegAddr);
        if(!dvfs_submit_work_queue(freq_idx, lock, xLinkRegAddr)) {
            assert(0);
            return HAL_DVFS_STATUS_ERROR;
        }
    }
    else {
        dvfs_enter_critical_section(freq_idx, lock);
        dvfs_done_print(freq_idx, lock, xLinkRegAddr);
    }
#endif

#endif /* !_DVFS_DISABLED_ */
    return HAL_DVFS_STATUS_OK;
}

void hal_dvfs_init_end(void)
{
    dvfs_prt_info("hal_dvfs_init_end", 0);

#ifdef DVFS_INIT_HV_4_A_WHILE
    if(dvfs_flg.b.init_hv_4_a_while) {
        hal_dvfs_lock_control(HAL_DVFS_OPP_HV, HAL_DVFS_UNLOCK);
        dvfs_prt_info("Unlock init HV done", 0);
    }
#endif
}

/*****************************************************************************
 * RACE command
 *****************************************************************************/
#if defined(AIR_RACE_CMD_ENABLE) && !defined(FPGA_ENV)
#include "race_cmd_feature.h"
#ifdef RACE_CLOCK_CMD_ENABLE
#include "race_cmd_clock.h"

/* RACE DVFS Sub Command */
#define DVFS_RACE_COMMAND_SLIM
enum {
    DVFS_SUB_CMD_GET_CUR_MCU_KHZ = 0,  /* CMD: 05 5A 03 00 C2 02 00         RSP: 05 5B 07 00 C2 02 00 XX XX XX XX        */
#ifndef DVFS_RACE_COMMAND_SLIM
    DVFS_SUB_CMD_GET_MCU_KHZ_TBL = 1, /* CMD: 05 5A 03 00 C2 02 01         RSP: 05 5B XX 00 C2 02 01 SS XX XX XX XX ... */
    DVFS_SUB_CMD_GET_CUR_OPP     = 2, /* CMD: 05 5A 03 00 C2 02 02         RSP: 05 5B 04 00 C2 02 02 XX                 */
#endif
    DVFS_SUB_CMD_OPP_LOCK_CTRL   = 3, /* CMD: 05 5A 05 00 C2 02 03 PP LL   RSP: 05 5B 04 00 C2 02 03 00/03              */
#ifndef DVFS_RACE_COMMAND_SLIM
    DVFS_SUB_CMD_GET_VCORE_MV    = 4, /* CMD: 05 5A 03 00 C2 02 04         RSP: 05 5B 04 00 C2 02 04 XX XX              */
#endif
    DVFS_SUB_CMD_DUMP_LOG = 0xFF       /* CMD: 05 5A 03 00 C2 02 FF         RSP: 05 5B 04 00 C2 02 FF 00                 */
};

typedef struct {
    uint8_t  sub_cmd;
    uint8_t  tbl_size;
    uint32_t khz_tbl[HAL_DVFS_OPP_NUM];
} PACKED race_dvfs_mcu_khz_tbl_t;

void *hal_dvfs_race_handler(ptr_race_pkt_t pCmdMsg, uint8_t channel_id)
{
    uint8_t *pPayload = pCmdMsg->payload;
    uint8_t  i, sub_cmd = pPayload[0];
    bool     data_len_err = false, mem_alloc_fail = false;
    void    *pRtnPayload = NULL;
    uint16_t data_len = pCmdMsg->hdr.length - 2; /* not count RACE ID */
#ifndef DVFS_RACE_COMMAND_SLIM
    uint16_t w;
#endif
    uint32_t dwTemp;
    dvfs_frequency_t opp;
    hal_dvfs_status_t dvfs_status;

    if (data_len) {
        switch (sub_cmd) {
            case DVFS_SUB_CMD_GET_CUR_MCU_KHZ:
                race_clk_log_info("DVFS_GET_CUR_MCU_KHZ", 0);
                pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                    (uint8_t)RACE_TYPE_RESPONSE,
                                                    (uint16_t)RACE_ID_DVFS,
                                                    (uint16_t)sizeof(race_clk_common_uint32_val_only_t),
                                                    channel_id);
                if (pRtnPayload) {
                    dwTemp = hal_dvfs_get_cpu_frequency();
                    ((race_clk_common_uint32_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                    ((race_clk_common_uint32_val_only_t *)pRtnPayload)->val = dwTemp;
                    race_clk_log_info("CUR MCU KHZ %d", 1, dwTemp);
                }
                else {
                    mem_alloc_fail = true;
                }
                break;

#ifndef DVFS_RACE_COMMAND_SLIM
            case DVFS_SUB_CMD_GET_MCU_KHZ_TBL:
                race_clk_log_info("DVFS_GET_MCU_KHZ_TBL", 0);
                pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                    (uint8_t)RACE_TYPE_RESPONSE,
                                                    (uint16_t)RACE_ID_DVFS,
                                                    (uint16_t)sizeof(race_dvfs_mcu_khz_tbl_t),
                                                    channel_id);
                if (pRtnPayload) {
                    ((race_dvfs_mcu_khz_tbl_t *)pRtnPayload)->sub_cmd = sub_cmd;
                    ((race_dvfs_mcu_khz_tbl_t *)pRtnPayload)->tbl_size = HAL_DVFS_OPP_NUM;
                    for (i=0; i<HAL_DVFS_OPP_NUM; i++) {
                        ((race_dvfs_mcu_khz_tbl_t *)pRtnPayload)->khz_tbl[i] = dvfs_cpu_khz_tbl[i];
                        race_clk_log_info("MCU KHZ TBL[%d] %d", 2, i, dvfs_cpu_khz_tbl[i]);
                    }
                }
                else {
                    mem_alloc_fail = true;
                }
                break;
            case DVFS_SUB_CMD_GET_CUR_OPP:
                race_clk_log_info("DVFS_GET_CUR_OPP", 0);
                pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                    (uint8_t)RACE_TYPE_RESPONSE,
                                                    (uint16_t)RACE_ID_DVFS,
                                                    (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                    channel_id);
                if (pRtnPayload) {
                    i = hal_dvfs_get_cur_sys_opp();
                    ((race_clk_common_uint8_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                    ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = i;
                    race_clk_log_info("CUR OPP %d", 1, i);
                }
                else {
                    mem_alloc_fail = true;
                }
                break;
#endif /* !DVFS_RACE_COMMAND_SLIM */

            case DVFS_SUB_CMD_OPP_LOCK_CTRL:
                if (data_len >= 3) {
                    opp = pPayload[1];
                    i = pPayload[2];
                    race_clk_log_info("DVFS_OPP_LOCK_CTRL %d %d", 2, opp, i);
                    if ((opp < HAL_DVFS_OPP_TTL) && (i <= HAL_DVFS_LOCK)) {
                        pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                            (uint8_t)RACE_TYPE_RESPONSE,
                                                            (uint16_t)RACE_ID_DVFS,
                                                            (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                            channel_id);
                        if (pRtnPayload) {
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
#ifdef _DVFS_DISABLED_
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_NOT_SUPPORT;
#else
                            dvfs_status = hal_dvfs_lock_control(opp, i);
                            if (dvfs_status == HAL_DVFS_STATUS_OK) {
                                ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_SUCCESS;
                                race_clk_log_info("Cur OPP %d", 1, hal_dvfs_get_cur_sys_opp());
                            }
                            else {
                                race_clk_log_err("OPP lock control fail %d", 1, dvfs_status);
                                ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_PARAMETER_ERROR;
                            }
#endif
                        }
                        else {
                            mem_alloc_fail = true;
                        }
                    }
                    else {
                        race_clk_log_err("Invalid OPP/LOCK value", 0);
                    }
                }
                else {
                    data_len_err = true;
                }
                break;

#ifndef DVFS_RACE_COMMAND_SLIM
            case DVFS_SUB_CMD_GET_VCORE_MV:
                race_clk_log_info("DVFS_GET_VCORE_MV", 0);
                pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                    (uint8_t)RACE_TYPE_RESPONSE,
                                                    (uint16_t)RACE_ID_DVFS,
                                                    (uint16_t)sizeof(race_clk_common_uint16_val_only_t),
                                                    channel_id);
                if (pRtnPayload) {
                    w = hal_clock_get_vcore_mv();
                    ((race_clk_common_uint16_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                    ((race_clk_common_uint16_val_only_t *)pRtnPayload)->val = w;
                    race_clk_log_info("Vcore %d mv", 1, w);
                }
                else {
                    mem_alloc_fail = true;
                }
                break;
#endif /* !DVFS_RACE_COMMAND_SLIM */

            case DVFS_SUB_CMD_DUMP_LOG:
                race_clk_log_info("DVFS_DUMP_LOG", 0);
                pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                    (uint8_t)RACE_TYPE_RESPONSE,
                                                    (uint16_t)RACE_ID_DVFS,
                                                    (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                    channel_id);
                if (pRtnPayload) {
                    ((race_clk_common_uint8_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                    ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_SUCCESS;
                    dvfs_debug_dump();
                }
                else {
                    mem_alloc_fail = true;
                }
                break;

            default:
                race_clk_log_err("DVFS sub_cmd 0x%02X not supported", 1, sub_cmd);
                break;
        }
    }
    else {
        data_len_err = true;
    }
    if (data_len_err) {
        race_clk_log_err("DVFS data_len %d error", 1, data_len);
    }
    if (mem_alloc_fail) {
        race_clk_log_err("DVFS mem alloc fail", 0);
    }
    return pRtnPayload;
}
#endif /* RACE_CLOCK_CMD_ENABLE */
#endif /* AIR_RACE_CMD_ENABLE && !FPGA_ENV */

#endif /* HAL_DVFS_MODULE_ENABLED */

