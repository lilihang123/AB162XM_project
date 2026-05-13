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

#include "hal.h"

#ifdef HAL_CLOCK_MODULE_ENABLED
#include <stdio.h>
#include <string.h>
#include "hal_clock_internal.h"

#ifndef CLOCK_COSIM
#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>
#if IS_ENABLED(CONFIG_AIR_DAEMON_WORKQUEUE_ENABLE)
#include "air_daemon_work_q.h"
#endif
#ifdef HAL_SLEEP_MANAGER_ENABLED
#include "hal_sleep_manager_internal.h"
#endif
#endif

#if defined(__EXT_BOOTLOADER__)
#define clk_prt_info(msg, cnt, ...)
#define clk_prt_warn(msg, cnt, ...)
#define clk_prt_err(msg, cnt, ...)
#elif defined(__EXT_DA__) || defined(FPGA_ENV) || defined(CLOCK_COSIM)
#define clk_prt_info(msg, cnt, ...)
#define clk_prt_warn(msg, cnt, ...)
#define clk_prt_err(msg, cnt, ...)
#else
//#include "syslog.h"
//#define clk_prt_info(msg, cnt, ...)              log_hal_msgid_info("[HAL_CLK] "msg, cnt, ##__VA_ARGS__)
//#define clk_prt_warn(msg, cnt, ...)              log_hal_msgid_warning("[HAL_CLK] "msg, cnt, ##__VA_ARGS__)
//#define clk_prt_err(msg, cnt, ...)               log_hal_msgid_error("[HAL_CLK] "msg, cnt, ##__VA_ARGS__)
#define clk_prt_info(msg, cnt, ...)              printk("[HAL_CLK] "msg"\r\n", ##__VA_ARGS__)
#define clk_prt_warn(msg, cnt, ...)              printk("[HAL_CLK] "msg"\r\n", ##__VA_ARGS__)
#define clk_prt_err(msg, cnt, ...)               printk("[HAL_CLK] "msg"\r\n", ##__VA_ARGS__)
#endif

#define clk_force_prt_info(msg, cnt, ...)        printk("[HAL_CLK] "msg"\r\n", ##__VA_ARGS__)

/*****************************************************************************
 * Debug or test definition
 *****************************************************************************/
#if 0 // for !FPGA_ENV test only
  #ifdef FPGA_ENV
    #undef FPGA_ENV
  #endif
#endif

/*****************************************************************************
 * Default definition of configuration
 *****************************************************************************/
#define DEFAULT_LPOSC_KHZ                        312000    /* 312 MHz */
#define DEFAULT_LPOSC_DESENSE_SUPPRESS_KHZ       299250    /* 299.25 MHz */

#define LPOSC_HS_DIV2                            2  /* 312/2  = 156 MHz,  299.25/2  = 149.625  MHz */
#define LPOSC_HS_DIV3                            3  /* 312/3  = 104 MHz,  299.25/3  =  99.75   MHz */
#define LPOSC_HS_DIV4                            4  /* 312/4  =  78 MHz,  299.25/4  =  74.8125 MHz */

#define LPOSC_LS_DIV6                            6  /* 312/6  =  52 MHz,  299.25/6  =  49.875  MHz */
#define LPOSC_LS_DIV12                           12 /* 312/12 =  26 MHz,  299.25/12 =  24.9375 MHz */

#define DEFAULT_LPOSC_HS_DIV                     LPOSC_HS_DIV2
#define DEFAULT_LPOSC_LS_DIV                     LPOSC_LS_DIV6

#if 0
#define DEFAULT_LPOSC_DESENSE_SUPPRESS           true
#else
#define DEFAULT_LPOSC_DESENSE_SUPPRESS           false
#endif

#define DEFAULT_LPOSC_HOPPING_ENABLE             false
#define DEFAULT_LPOSC_HOPPING_RANGE_X10000       1050  /* examples: 800=8%, 1050=10.5% */
#define DEFAULT_LPOSC_HOPPING_TIMER_US_ONCE      3     /* 3, 4, 5, 6 */
#define DEFAULT_LPOSC_HOPPING_JUMP_CODE_ONCE     4     /* 1, 2, 4, 8 */

#define DEFAULT_LOPSC_RE_K_PERIODICALLY_ENABLE   true
#define DEFAULT_LOPSC_RE_K_PERIOD_MS             60000
#define DEFAULT_DCM_ENABLE                       true

hal_clk_cfg_t g_clk_cfg =
{
#if DEFAULT_LPOSC_DESENSE_SUPPRESS
    .lposc_khz = DEFAULT_LPOSC_DESENSE_SUPPRESS_KHZ,
#else
    .lposc_khz = DEFAULT_LPOSC_KHZ,
#endif
    .lposc_hs_div = DEFAULT_LPOSC_HS_DIV,
    .lposc_ls_div = DEFAULT_LPOSC_LS_DIV,

    .lposc_hopping_enable = DEFAULT_LPOSC_HOPPING_ENABLE,
    .lposc_hopping_range_x10000 = DEFAULT_LPOSC_HOPPING_RANGE_X10000,
    .lposc_hopping_timer_us_once = DEFAULT_LPOSC_HOPPING_TIMER_US_ONCE,
    .lposc_hopping_jump_code_once = DEFAULT_LPOSC_HOPPING_JUMP_CODE_ONCE,

    .lposc_re_k_periodically_enable = DEFAULT_LOPSC_RE_K_PERIODICALLY_ENABLE,
    .lposc_re_k_period_ms = DEFAULT_LOPSC_RE_K_PERIOD_MS,
    .dcm_enable = DEFAULT_DCM_ENABLE,

    .dvfs_sys_cfg = AIR_DVFS_SYS_CFG_NORMAL
};

typedef enum {
    LPOSC_K_CALI,
    LPOSC_K_FT
} lposc_k_val_t;

/*****************************************************************************
 * General definition
 *****************************************************************************/
#define DCXO_DBL_HZ                              64000000  /* 64 MHz */
#define DCXO_DBL_KHZ                             64000     /* 64 MHz */

#define PSEUDO_MUX_TTL                          (CLK_MUX_SEL_PSEUDO_END - CLK_MUX_SEL_PSEUDO_BEGIN + 1)
#define PSEUDO_CG_TTL                           (HAL_CLOCK_CG_PSEUDO_END - HAL_CLOCK_CG_PSEUDO_BEGIN + 1)

#define PWM_CG_MULTI_CTRL_REQUEST_BIT_MASK       0x0000001F  /* 5 PWM Channels, bit[4:0] */

#define MUX_ID_DUMMY_END                         TOTAL_MUX_CNT
#define MUX_IDX_DUMMY                            0xFF

#define INFRA_AO_BACKUP_RESTORE_SIZE_CKSYS       0x60
#define INFRA_AO_BACKUP_RESTORE_SIZE_CKSYS_XO    0x34
#define INFRA_AO_BACKUP_RESTORE_SIZE_MIXEDSYS_D  0x20
#define INFRA_AO_BACKUP_RESTORE_SIZE_CKSYS_BUS   0x38

typedef enum {
    CG_REQUEST_STATUS,
    CG_REQUEST_CLEAR,
    CG_REQUEST_SET,

    CLK_REQ_ENABLE = CG_REQUEST_CLEAR,
    CLK_REQ_DISABLE = CG_REQUEST_SET
} cg_request_t;

typedef enum {
    CG_CLR__CLK_ON,
    CG_SET__CLK_OFF
} cg_state_t;

typedef union {
    uint8_t value;
    struct {
        uint8_t xo_dbl                              :1;
        uint8_t osc_hs_d2                           :1;
        uint8_t osc_hs_d4                           :1;
        uint8_t osc_ls_d2                           :1;
        uint8_t osc_hs                              :1;
        uint8_t osc                                 :1;
        uint8_t reserved                            :2;
    } b;
} T_CLK_RESOURCE_CHK;

typedef union {
#if 0
    uint32_t value;
    struct {
        uint32_t from_clock_enable_to_clock_mux_sel :1;
        uint32_t lposc_recali_flow_prohibit         :1;
        uint32_t lposc_recali_changing_frq          :1;
        uint32_t reserved                           :29;
    } b;
#else
    uint8_t value;
    struct {
        uint8_t from_clock_enable_to_clock_mux_sel  :1;
        uint8_t lposc_recali_initialized            :1;
        uint8_t lposc_recali_dump_info_1st_time     :1;
        //uint8_t lposc_recali_flow_prohibit          :1;
        uint8_t lposc_recali_changing_frq           :1;
        uint8_t lposc_recali_timer_active           :1;
        //uint8_t bt_mac_recover2dbl                  :1;
        uint8_t reserved                            :3;
    } b;
#endif
} T_CLK_FLAG;

#ifndef FPGA_ENV
static uint8_t pseudo_mux_tbl[PSEUDO_MUX_TTL];
static cg_state_t pseudo_cg_tbl[PSEUDO_CG_TTL];
static T_CLK_FLAG clk_flg;
static clk_bt_rx_adc_t clk_bt_rx_adc;

ATTR_RODATA_IN_TCM static hal_clock_cg_id clk_always_on_cg_tbl[] = {
    HAL_CLOCK_CG_CMSYS_BUS, HAL_CLOCK_CG_MEM_BUS,
    HAL_CLOCK_CG_IBEX,
    HAL_CLOCK_CG_OSTIMER,
    HAL_CLOCK_CG_SFC,
    HAL_CLOCK_CG_SPM_PCLK, HAL_CLOCK_CG_SPM_BCLK_CM33, HAL_CLOCK_CG_SPM_DIV, HAL_CLOCK_CG_SPM_SYS,
    HAL_CLOCK_CG_PMU_1M,

    HAL_CLOCK_CG_DUMMY_END
};

/* -------------------------------------------------------------------------- */
typedef struct {
    uint8_t  mux_id;
    uint8_t  mux_sel;
} clk_mux_sel_t;

/* IRTX is set to XO, so doesn't need */
const clk_mux_sel_t init_clk_mux_tbl[] =
{
#if defined(CLK_LPOSC_MUX_INIT_RUN_DFS_HIGH) || defined(__EXT_DA__)
    { .mux_id = CLK_SYS_SEL,         .mux_sel = MUX_SYS_IDX_OSC_HS        },
    { .mux_id = CLK_IBEX_SEL,        .mux_sel = MUX_IBEX_IDX_XO_DBL       },
#else
    { .mux_id = CLK_SYS_SEL,         .mux_sel = MUX_SYS_IDX_OSC_HS_D2     },
    { .mux_id = CLK_IBEX_SEL,        .mux_sel = MUX_IBEX_IDX_OSC_LS       },
#endif
    { .mux_id = CLK_SFC_SEL,         .mux_sel = MUX_SFC_IDX_OSC_D3        },
    { .mux_id = CLK_ESC_SEL,         .mux_sel = MUX_ESC_IDX_OSC_HS_D4     },
    { .mux_id = CLK_SPIMST2_SEL,     .mux_sel = MUX_SPIMST2_IDX_OSC_HS_D2 },
    { .mux_id = CLK_I3C_SEL,         .mux_sel = MUX_I3C_IDX_OSC_D3        },
    { .mux_id = CLK_USB_SEL,         .mux_sel = MUX_USB_IDX_XO_DBL        },
    { .mux_id = CLK_BT_HOP_SEL,      .mux_sel = MUX_BT_HOP_IDX_OSC_HS_D2  },
    { .mux_id = CLK_BT_MAC_SEL,      .mux_sel = MUX_BT_MAC_IDX_XO_DBL     },
    { .mux_id = CLK_SLOW_BUS_SEL,    .mux_sel = MUX_SLOW_BUS_IDX_OSC_26M  },

    { .mux_id = MUX_ID_DUMMY_END,    .mux_sel = 0                         }
};

ATTR_RODATA_IN_TCM uint8_t dvfs_clk_sys_mux_idx[HAL_DVFS_FRQ_MAX] =
{
    MUX_SYS_IDX_XO,        /* HAL_DVFS_FRQ_LOW */
    MUX_SYS_IDX_OSC_HS_D2, /* HAL_DVFS_FRQ_MID */
    MUX_SYS_IDX_OSC_HS     /* HAL_DVFS_FRQ_HIGH */
};

ATTR_RODATA_IN_TCM uint8_t dvfs_clk_ibex_mux_idx[HAL_DVFS_FRQ_MAX] =
{
    MUX_IBEX_IDX_XO,       /* HAL_DVFS_FRQ_LOW */
    MUX_IBEX_IDX_OSC_LS,   /* HAL_DVFS_FRQ_MID */
    MUX_IBEX_IDX_XO_DBL    /* HAL_DVFS_FRQ_HIGH */
};

ATTR_RODATA_IN_TCM clk_mux_sel_t dvfs_clk_other_mux_idx[] =
{
    { .mux_id = CLK_SFC_SEL,         .mux_sel = MUX_SFC_IDX_OSC_D3        },
    { .mux_id = CLK_ESC_SEL,         .mux_sel = MUX_ESC_IDX_OSC_HS_D4     },
    { .mux_id = CLK_SPIMST2_SEL,     .mux_sel = MUX_SPIMST2_IDX_OSC_HS_D2 },
    { .mux_id = CLK_I3C_SEL,         .mux_sel = MUX_I3C_IDX_OSC_D3        },
    { .mux_id = CLK_BT_HOP_SEL,      .mux_sel = MUX_BT_HOP_IDX_OSC_HS_D2  },
    { .mux_id = CLK_SLOW_BUS_SEL,    .mux_sel = MUX_SLOW_BUS_IDX_OSC_26M  },

    { .mux_id = MUX_ID_DUMMY_END,    .mux_sel = 0                         }
};

/* -------------------------------------------------------------------------- */
#if !defined(CLOCK_COSIM) && defined(CONFIG_MULTITHREADING)
//#define LPOSC_RECALI_4HQA

#define LPOSC_RECALI_1ST_INTERVAL_MS        3000
#define LPOSC_RECALI_CHANGING_INV_MS        500
#define LPOSC_RECALI_HQA_INTERVAL_MS        500

#define LPOSC_RECALI_EXPECT_FQMTR_DATA      6000
#define LPOSC_RG_FT_MAX                     0x1F  /* 5 bits */
#define RTC_LPOSC_CON2_ADDR               ((volatile uint32_t *)(RM_RTC_DIG_MISC_BASE+0x0008))
#define LPOSC_RECALI_ROUND_K_TIMES_MAX      10  /* K times each round */
#define LPOSC_RECALI_ASSERT_ROUND_MAX       10  /* Assert when N rounds K fail continuously */
#define LPOSC_RECALI_MONITOR_PRINT_MS_MAX   60000

uint32_t lposc_recali_winset;
uint32_t lposc_recali_target_data;
uint32_t lposc_recali_data_upper_bound;
uint32_t lposc_recali_data_lower_bound;
uint32_t lposc_recali_timer_ms;
uint32_t lposc_recali_gpt_timer_handle;
uint8_t lposc_recali_assert_round_ttl;
uint8_t lposc_recali_monitor_print_times_ttl, lposc_recali_monitor_print_times_max;
struct k_work lposc_recali_work;

void lposc_recali_timer_expiry_fn(void *user_data);
#endif /* !CLOCK_COSIM && CONFIG_MULTITHREADING */

/* -------------------------------------------------------------------------- */
#if 0
#if !defined(__EXT_BOOTLOADER__) && !defined(__EXT_DA__) && !defined(CLOCK_COSIM) && !defined(CLOCK_BRINGUP_VER) && !defined(_CLOCK_DVT_) && defined(CONFIG_MULTITHREADING)
//#define DCXO_DBL64M_RE_K_PERIODICALLY

#ifdef DCXO_DBL64M_RE_K_PERIODICALLY
#define DCXO_DBL64M_RE_K_INTERVAL_MS        60000
struct k_work dcxo_dbl64m_re_k_work;
struct k_timer dcxo_dbl64m_re_k_timer;
#endif /* DCXO_DBL64M_RE_K_PERIODICALLY */
#endif

#endif /* !__EXT_BOOTLOADER__ && !__EXT_DA__ && !CLOCK_COSIM && !CLOCK_BRINGUP_VER && !_CLOCK_DVT_ && CONFIG_MULTITHREADING */

#endif /* !FPGA_ENV */

/*****************************************************************************
 * Clock mux table
 *****************************************************************************/
#define MUX_SEL_NUM    6

typedef enum {
    MUX_NONE,
    MUX_XO,
    MUX_XO_DBL,   /* DCXO doubler */
    MUX_OSC_HS,   /* LPOSC high speed */
    MUX_OSC_LS,   /* LPOSC low speed */
    MUX_OSC_D3,   /* LPOSC divided by 3 */
    MUX_OSC_26M,
    MUX_RTC,
    MUX_EOSC
} mux_src_t;

typedef enum {
    MUX_DIV_NONE,
    MUX_DIV_D2,
    MUX_DIV_D4
} mux_div_t;

enum {
    MUX_NOT_ALLOW,
    MUX_ALLOW
};

typedef struct {
    mux_src_t  src    :4;
    mux_div_t  div    :3;
    uint8_t    allow  :1;
} mux_sel_t;

typedef enum {
    PHYSICAL_N_TO_1_MUX,
    PHYSICAL_SIMPLE_MUX,
    PSEUDO_MUX
} mux_type_t;

typedef enum {
    PHYSICAL_CG,
    PSEUDO_CG
} cg_type_t;

typedef struct {
    mux_type_t  mux_type  :2;
    cg_type_t   cg_type   :1;
    uint8_t     reserved  :5;
} mux_other_t;

typedef struct {
    mux_sel_t          sel[MUX_SEL_NUM];
    mux_other_t        other;
    volatile uint8_t  *p_sel_rg;
    hal_clock_cg_id    cg_id;
} __attribute__((packed)) mux_info_t;

#ifndef FPGA_ENV
ATTR_RODATA_IN_TCM static mux_info_t mux_tbl[TOTAL_MUX_CNT] = {
    { /* MUX: CLK_SYS_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_OSC_LS,  .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 2 */
            { .src = MUX_OSC_HS,  .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 3 */
            { .src = MUX_OSC_HS,  .div = MUX_DIV_D2,   .allow = MUX_ALLOW     }, /* 4 */
            { .src = MUX_OSC_D3,  .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_N_TO_1_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = RTC_LPOSC_CON4__CLK_SYS_SEL,
        .cg_id = HAL_CLOCK_CG_CMSYS_BUS
    },
    { /* MUX: CLK_IBEX_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_XO_DBL,  .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 2 */
            { .src = MUX_OSC_LS,  .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_N_TO_1_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CKSYS_CLK_CFG_0__CLK_IBEX_SEL,
        .cg_id = HAL_CLOCK_CG_IBEX
    },
    { /* MUX: CLK_SFC_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_OSC_HS,  .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 2 */
            { .src = MUX_OSC_HS,  .div = MUX_DIV_D2,   .allow = MUX_ALLOW     }, /* 3 */
            { .src = MUX_OSC_D3,  .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_N_TO_1_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CKSYS_CLK_CFG_0__CLK_SFC_SEL,
        .cg_id = HAL_CLOCK_CG_SFC
    },
    { /* MUX: CLK_ESC_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_OSC_HS,  .div = MUX_DIV_D2,   .allow = MUX_ALLOW     }, /* 2 */
            { .src = MUX_OSC_HS,  .div = MUX_DIV_D4,   .allow = MUX_ALLOW     }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_N_TO_1_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CKSYS_CLK_CFG_0__CLK_ESC_SEL,
        .cg_id = HAL_CLOCK_CG_ESC
    },
    { /* MUX: CLK_SPIMST0_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 2 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_SIMPLE_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CKSYS_CLK_CFG_1__CLK_SPIMST0_SEL,
        .cg_id = HAL_CLOCK_CG_SPIMST0
    },
    { /* MUX: CLK_SPIMST1_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 2 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_SIMPLE_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CKSYS_CLK_CFG_1__CLK_SPIMST1_SEL,
        .cg_id = HAL_CLOCK_CG_SPIMST1
    },
    { /* MUX: CLK_SPIMST2_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_OSC_HS,  .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 2 */
            { .src = MUX_OSC_HS,  .div = MUX_DIV_D2,   .allow = MUX_ALLOW     }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_N_TO_1_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CKSYS_CLK_CFG_1__CLK_SPIMST2_SEL,
        .cg_id = HAL_CLOCK_CG_SPIMST2
    },
    { /* MUX: CLK_SPISLV_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_OSC_LS,  .div = MUX_DIV_D2,   .allow = MUX_ALLOW     }, /* 2 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_N_TO_1_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CKSYS_CLK_CFG_1__CLK_SPISLV_SEL,
        .cg_id = HAL_CLOCK_CG_SPISLV
    },
    { /* MUX: CLK_I3C_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_OSC_D3,  .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 2 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_N_TO_1_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CKSYS_CLK_CFG_2__CLK_I3C_SEL,
        .cg_id = HAL_CLOCK_CG_I3C
    },
    { /* MUX: CLK_USB_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_XO_DBL,  .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 2 */
            { .src = MUX_OSC_LS,  .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_N_TO_1_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CKSYS_CLK_CFG_2__CLK_USB_SEL,
        .cg_id = HAL_CLOCK_CG_USB
    },
    { /* MUX: CLK_AUD_ENGINE_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 2 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_SIMPLE_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CKSYS_CLK_CFG_3__CLK_AUD_ENGINE_SEL,
        .cg_id = HAL_CLOCK_CG_AUD_ENGINE
    },
    { /* MUX: CLK_AUD_BUS_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 2 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_N_TO_1_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CKSYS_CLK_CFG_2__CLK_AUD_INTBUS_SEL,
        .cg_id = HAL_CLOCK_CG_AUD_INTBUS
    },
    { /* MUX: CLK_BT_HOP_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_OSC_HS,  .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 2 */
            { .src = MUX_OSC_HS,  .div = MUX_DIV_D2,   .allow = MUX_ALLOW     }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_N_TO_1_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CKSYS_CLK_CFG_2__CLK_BT_HOP_SEL,
        .cg_id = HAL_CLOCK_CG_BT_HOP
    },
    { /* MUX: CLK_BT_MAC_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_XO_DBL,  .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 2 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_SIMPLE_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CKSYS_CLK_CFG_3__CLK_BT_MAC_SEL,
        .cg_id = HAL_CLOCK_CG_BT_MAC
    },
    { /* MUX: CLK_UART0_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 2 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_SIMPLE_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CLOCK_SEL0__RG_UART0_BCLK_SEL,
        .cg_id = HAL_CLOCK_CG_UART0
    },
    { /* MUX: CLK_UART1_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 2 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_SIMPLE_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CLOCK_SEL0__RG_UART1_BCLK_SEL,
        .cg_id = HAL_CLOCK_CG_UART1
    },
    { /* MUX: CLK_UART2_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 2 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_SIMPLE_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CLOCK_SEL0__RG_UART2_BCLK_SEL,
        .cg_id = HAL_CLOCK_CG_UART2
    },
    { /* MUX: CLK_GPT_BCLK_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 2 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_SIMPLE_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CLOCK_SEL1__RG_GPT_BCLK_SEL,
        .cg_id = HAL_CLOCK_CG_GPTIMER
    },
    { /* MUX: CLK_OSGPT_BCLK_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 2 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_SIMPLE_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CLOCK_SEL1__RG_OSGPT_BCLK_SEL,
        .cg_id = HAL_CLOCK_CG_OSTIMER
    },
    { /* MUX: CLK_SEC_GPT_BCLK_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 2 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_SIMPLE_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CLOCK_SEL1__RG_SEC_GPT_BCLK_SEL,
        .cg_id = HAL_CLOCK_CG_GPTIMER_SEC
    },
    { /* MUX: CLK_DCXO_PWR_CTRL_SEL */
        .sel = {
            { .src = MUX_EOSC,    .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_RTC,     .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 2 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_SIMPLE_MUX, .cg_type = PSEUDO_CG },
        .p_sel_rg = CKSYS_CLK_CFG_4__CLK_DCXO_PWR_CTRL_SEL,
        .cg_id = HAL_CLOCK_CG_PSEUDO_DCXO_PWR_CTRL
    },
    { /* MUX: CLK_DCXO_DIG_MACRO_SEL */
        .sel = {
            { .src = MUX_EOSC,    .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_RTC,     .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 2 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_SIMPLE_MUX, .cg_type = PSEUDO_CG },
        .p_sel_rg = CKSYS_CLK_CFG_4__CLK_DCXO_DIG_MACRO_SEL,
        .cg_id = HAL_CLOCK_CG_PSEUDO_DCXO_DIG_MACRO
    },
    { /* MUX: CLK_IRTX_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_OSC_HS,  .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 2 */
            { .src = MUX_OSC_D3,  .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_N_TO_1_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CKSYS_CLK_CFG_3__CLK_IRTX_SEL,
        .cg_id = HAL_CLOCK_CG_IRTX
    },
    { /* MUX: CLK_IRRX_BCLK_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 2 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_SIMPLE_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = CLOCK_SEL0__RG_IRRX_BCLK_SEL,
        .cg_id = HAL_CLOCK_CG_IRRX
    },
    { /* MUX: CLK_OSC_26M_SEL */
        .sel = {
            { .src = MUX_OSC_LS,  .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_LS,  .div = MUX_DIV_D2,   .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 2 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_SIMPLE_MUX, .cg_type = PSEUDO_CG },
        .p_sel_rg = RTC_LPOSC_CON4__CLK_OSC_26M_SEL,
        .cg_id = HAL_CLOCK_CG_PSUEDO_OSC_26M
    },
    { /* MUX: CLK_RGU_32K_SEL */
        .sel = {
            { .src = MUX_EOSC,    .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_RTC,     .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 2 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_SIMPLE_MUX, .cg_type = PSEUDO_CG },
        .p_sel_rg = CKSYS_CLK_CFG_4__CLK_RGU_32K_SEL,
        .cg_id = HAL_CLOCK_CG_PSEUDO_RGU_32K
    },
    { /* MUX: CLK_SLOW_BUS_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 2 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PHYSICAL_SIMPLE_MUX, .cg_type = PSEUDO_CG },
        .p_sel_rg = RTC_LPOSC_CON4__CLK_SLOW_BUS_SEL,
        .cg_id = HAL_CLOCK_CG_PSEUDO_SLOW_BUS
    },
    { /* MUX: CLK_PWM0_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_RTC,     .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 2 */
            { .src = MUX_OSC_LS,  .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PSEUDO_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = NULL,
        .cg_id = HAL_CLOCK_CG_PWM0
    },
    { /* MUX: CLK_PWM1_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_RTC,     .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 2 */
            { .src = MUX_OSC_LS,  .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PSEUDO_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = NULL,
        .cg_id = HAL_CLOCK_CG_PWM1
    },
    { /* MUX: CLK_PWM2_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_RTC,     .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 2 */
            { .src = MUX_OSC_LS,  .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PSEUDO_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = NULL,
        .cg_id = HAL_CLOCK_CG_PWM2
    },
    { /* MUX: CLK_PWM3_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_RTC,     .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 2 */
            { .src = MUX_OSC_LS,  .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PSEUDO_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = NULL,
        .cg_id = HAL_CLOCK_CG_PWM3
    },
    { /* MUX: CLK_PWM4_SEL */
        .sel = {
            { .src = MUX_XO,      .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 0 */
            { .src = MUX_RTC,     .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 1 */
            { .src = MUX_OSC_26M, .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 2 */
            { .src = MUX_OSC_LS,  .div = MUX_DIV_NONE, .allow = MUX_ALLOW     }, /* 3 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }, /* 4 */
            { .src = MUX_NONE,    .div = MUX_DIV_NONE, .allow = MUX_NOT_ALLOW }  /* 5 */
        },
        .other = { .mux_type = PSEUDO_MUX, .cg_type = PHYSICAL_CG },
        .p_sel_rg = NULL,
        .cg_id = HAL_CLOCK_CG_PWM4
    }
};
#endif /* !FPGA_ENV */

/*****************************************************************************
 * Simple GPIO API
 *****************************************************************************/
#ifndef GPIO_BASE
#define GPIO_BASE                                0x420B0000
#endif
#define _GPIO_BASE_                              GPIO_BASE
#define RG_ADDR_GPIO_DIR_SET                    (_GPIO_BASE_ + 0x0110) /* Set Output Direction (1 bit for each) */
#define RG_ADDR_GPIO_DOUT_SET                   (_GPIO_BASE_ + 0x0140) /* Set Output Data = 1 (1 bit for each) */
#define RG_ADDR_GPIO_DOUT_CLR                   (_GPIO_BASE_ + 0x0150) /* Set Output Data = 0 (1 bit for each) */
#define RG_ADDR_GPIO_MODE_SET                   (_GPIO_BASE_ + 0x0200) /* Set Auxiliary Mode (4 bits for each) */
#define RG_ADDR_GPIO_MODE_CLR                   (_GPIO_BASE_ + 0x0300) /* Clear Auxiliary Mode (4 bits for each) */
#define GPIO_AUX_FUN_DEBUGMON                    13

void _gpio_set_mode(uint8_t pin_num, uint32_t mode)
{
    uint32_t reg_offset, idx_offset;
    volatile uint32_t *pRegSet, *pRegClr;

    reg_offset = pin_num / 8;
    idx_offset = (pin_num % 8) * 4;
    pRegSet = (volatile uint32_t *)(RG_ADDR_GPIO_MODE_SET + reg_offset*4);
    pRegClr = (volatile uint32_t *)(RG_ADDR_GPIO_MODE_CLR + reg_offset*4);
    *pRegClr = (0xF << idx_offset);
    *pRegSet = (mode << idx_offset);
#ifdef _CLOCK_DVT_
    clk_prt_info("gpio_set_mode: RgClr *0x%08X = 0x%08X, RgSet *0x%08X = 0x%08X", 4, pRegClr, 0xF<<idx_offset, pRegSet, mode<<idx_offset);
#endif
}

void _gpio_set_dir_output(uint8_t pin_num)
{
    uint32_t reg_offset, idx_offset;
    volatile uint32_t *pReg;

    reg_offset = pin_num / 32;
    idx_offset = pin_num % 32;
    pReg = (volatile uint32_t *)(RG_ADDR_GPIO_DIR_SET + reg_offset*4);
    *pReg = (1 << idx_offset);
}

ATTR_TEXT_IN_TCM void _gpio_output(uint8_t pin_num, uint8_t output_data)
{
    uint32_t reg_offset, idx_offset;
    volatile uint32_t *pReg;

    reg_offset = pin_num / 32;
    idx_offset = pin_num % 32;
    if(output_data) {               /* output 1 */
        pReg = (volatile uint32_t *)(RG_ADDR_GPIO_DOUT_SET + reg_offset*4);
    }
    else {                          /* output 0 */
        pReg = (volatile uint32_t *)(RG_ADDR_GPIO_DOUT_CLR + reg_offset*4);
    }
    *pReg = (1 << idx_offset);
}

/*****************************************************************************
 * API for !FPGA_ENV only
 *****************************************************************************/
#ifndef FPGA_ENV
ATTR_TEXT_IN_TCM static void hal_clock_bt_mac_mux_set_idx(clk_mux_sel_idx_t sel, bool write_connsys_rg)
{
/*
When Controller wants to write connsys rg by itself:
64M -> 32M, Controller writes connsys rg and then call clock_mux_sel
32M -> 64M, Controller calls clock_mux_sel and then writes connsys rg
*/
#if 1  /* Connsys control flow */
    if(write_connsys_rg) {
        if(sel == MUX_BT_MAC_IDX_XO) {
            if((*(volatile uint32_t *)0xA0010218) & _U32_B30_) {
                *(volatile uint32_t *)0xA0010338 = 31;
                (*(volatile uint32_t *)0xA0010218) &= ~_U32_B30_;
            }
        }
        else if(sel == MUX_BT_MAC_IDX_XO_DBL) {
            if(!((*(volatile uint32_t *)0xA0010218) & _U32_B30_)) {
                *(volatile uint32_t *)0xA0010338 = 63;
                (*(volatile uint32_t *)0xA0010218) |= _U32_B30_;
            }
        }
    }
    if(sel <= MUX_BT_MAC_IDX_XO_DBL) {
        *(mux_tbl[CLK_BT_MAC_SEL].p_sel_rg) = sel;  /* also set this RG for resource disable */
    }
#else  /* Force control by Cksys (useless) */
    bool can_set = false;

    if(sel == MUX_BT_MAC_IDX_XO) {
        if(*(mux_tbl[CLK_BT_MAC_SEL].p_sel_rg) == MUX_BT_MAC_IDX_XO_DBL) {
            can_set = true;
        }
    }
    else if(sel == MUX_BT_MAC_IDX_XO_DBL) {
        if(*(mux_tbl[CLK_BT_MAC_SEL].p_sel_rg) == MUX_BT_MAC_IDX_XO) {
            can_set = true;
        }
    }
    if(can_set) {
        (*CKSYS_MISC_0__CKSYS_REG_SPARE) |= _U16_B15_;
        *(mux_tbl[CLK_BT_MAC_SEL].p_sel_rg) = sel;
        (*CKSYS_MISC_0__CKSYS_REG_SPARE) &= ~_U16_B15_;
    }
#endif
}

ATTR_TEXT_IN_TCM static uint8_t hal_clock_bt_mac_mux_get_idx(bool read_connsys_rg)
{
#if 1  /* Connsys control flow */
    if(read_connsys_rg) {
        if((*(volatile uint32_t *)0xA0010218) & _U32_B30_) {
            return MUX_BT_MAC_IDX_XO_DBL;
        }
    }
    else {
        return *(mux_tbl[CLK_BT_MAC_SEL].p_sel_rg);
    }
    return MUX_BT_MAC_IDX_XO;
#else  /* Force control by Cksys (useless) */
    return *(mux_tbl[CLK_BT_MAC_SEL].p_sel_rg);
#endif
}

ATTR_TEXT_IN_TCM static void hal_clock_bt_rx_adc_set_rg(clk_bt_rx_adc_t rx_adc)
{
    if(rx_adc == CLK_BT_RX_ADC_32M) {
        PT_DBL_MAN_SEL0->value = 0x6DE;
        PT_DBL_MAN0->value = 1;
        PT_DBL_MAN0->value = 0x121;
    }
    else if(rx_adc == CLK_BT_RX_ADC_64M) {
        PT_DBL_MAN_SEL0->value = 0x6CE;
        PT_DBL_MAN0->value = 1;
        PT_DBL_MAN0->value = 0x131;
    }
    else {  /* Set RG default */
        PT_DBL_MAN_SEL0->value = 0x7FF;
        PT_DBL_MAN0->value = 0;
    }
}

ATTR_TEXT_IN_TCM static void clock_switch_n_to_1_mux(clock_mux_sel_id mux_id, clk_mux_sel_idx_t target_sel)
{
    volatile uint8_t *p_sel = mux_tbl[mux_id].p_sel_rg;
    volatile uint8_t *p_force_on = NULL;
    volatile uint8_t *p_chg = NULL;
    volatile uint8_t *p_chg_ok = NULL;

    switch(mux_id) {
        case CLK_SYS_SEL:
            p_force_on = CKSYS_CLK_FORCE_ON_0__CLK_SYS_FORCE_ON;
            p_chg = CKSYS_CLK_UPDATE_0__CHG_SYS;
            p_chg_ok = CKSYS_CLK_UPDATE_STATUS_0__CHG_SYS_OK;
            break;

        case CLK_IBEX_SEL:
            p_force_on = CKSYS_CLK_FORCE_ON_0__CLK_IBEX_FORCE_ON;
            p_chg = CKSYS_CLK_UPDATE_0__CHG_IBEX;
            p_chg_ok = CKSYS_CLK_UPDATE_STATUS_0__CHG_IBEX_OK;
            break;

        case CLK_SFC_SEL:
            p_force_on = CKSYS_CLK_FORCE_ON_0__CLK_SFC_FORCE_ON;
            p_chg = CKSYS_CLK_UPDATE_0__CHG_SFC;
            p_chg_ok = CKSYS_CLK_UPDATE_STATUS_0__CHG_SFC_OK;
            break;

        case CLK_ESC_SEL:
            p_force_on = CKSYS_CLK_FORCE_ON_0__CLK_ESC_FORCE_ON;
            p_chg = CKSYS_CLK_UPDATE_0__CHG_ESC;
            p_chg_ok = CKSYS_CLK_UPDATE_STATUS_0__CHG_ESC_OK;
            break;

        case CLK_SPIMST2_SEL:
            p_force_on = CKSYS_CLK_FORCE_ON_1__CLK_SPIMST2_FORCE_ON;
            p_chg = CKSYS_CLK_UPDATE_1__CHG_SPIMST2;
            p_chg_ok = CKSYS_CLK_UPDATE_STATUS_1__CHG_SPIMST2_OK;
            break;

        case CLK_SPISLV_SEL:
            p_force_on = CKSYS_CLK_FORCE_ON_1__CLK_SPISLV_FORCE_ON;
            p_chg = CKSYS_CLK_UPDATE_1__CHG_SPISLV;
            p_chg_ok = CKSYS_CLK_UPDATE_STATUS_1__CHG_SPISLV_OK;
            break;

        case CLK_I3C_SEL:
            p_force_on = CKSYS_CLK_FORCE_ON_2__CLK_I3C_FORCE_ON;
            p_chg = CKSYS_CLK_UPDATE_2__CHG_I3C;
            p_chg_ok = CKSYS_CLK_UPDATE_STATUS_2__CHG_I3C_OK;
            break;

        case CLK_USB_SEL:
            p_force_on = CKSYS_CLK_FORCE_ON_2__CLK_USB_FORCE_ON;
            p_chg = CKSYS_CLK_UPDATE_2__CHG_USB;
            p_chg_ok = CKSYS_CLK_UPDATE_STATUS_2__CHG_USB_OK;
            break;

        case CLK_AUD_BUS_SEL:
            p_force_on = CKSYS_CLK_FORCE_ON_2__CLK_AUD_INTBUS_FORCE_ON;
            p_chg = CKSYS_CLK_UPDATE_2__CHG_AUD_INTBUS;
            p_chg_ok = CKSYS_CLK_UPDATE_STATUS_2__CHG_AUD_INTBUS_OK;
            break;

        case CLK_BT_HOP_SEL:
            p_force_on = CKSYS_CLK_FORCE_ON_2__CLK_BT_HOP_FORCE_ON;
            p_chg = CKSYS_CLK_UPDATE_2__CHG_BT_HOP;
            p_chg_ok = CKSYS_CLK_UPDATE_STATUS_2__CHG_BT_HOP_OK;
            break;

        case CLK_IRTX_SEL:
            p_force_on = CKSYS_CLK_FORCE_ON_3__CLK_IRTX_FORCE_ON;
            p_chg = CKSYS_CLK_UPDATE_3__CHG_IRTX;
            p_chg_ok = CKSYS_CLK_UPDATE_STATUS_3__CHG_IRTX_OK;
            break;

        default:
            return;
    }

    *p_force_on = 1;
    *p_sel = target_sel;
    *p_chg = 1;
    while(*p_chg);
    while(*p_chg_ok);
    *p_force_on = 0;
}

ATTR_TEXT_IN_TCM static void clock_top_mux_ctrl(clock_mux_sel_id mux_id, clk_mux_sel_idx_t target_sel)
{
    volatile uint8_t *p_sel = mux_tbl[mux_id].p_sel_rg; /* not for PSEUDO_MUX */

    if(mux_tbl[mux_id].other.mux_type != PSEUDO_MUX) {
        if(*p_sel == target_sel) { /* No Change */
            return;
        }
    }
    if(mux_tbl[mux_id].other.mux_type == PHYSICAL_N_TO_1_MUX) {
        clock_switch_n_to_1_mux(mux_id, target_sel);
    }
    else if(mux_tbl[mux_id].other.mux_type == PHYSICAL_SIMPLE_MUX) {
        if(mux_id == CLK_BT_MAC_SEL) {
            hal_clock_bt_mac_mux_set_idx(target_sel, false);
        }
        else {
            *p_sel = target_sel;
        }
        hal_gpt_delay_us(1);
    }
    else { /* PSEUDO_MUX */
        pseudo_mux_tbl[mux_id - CLK_MUX_SEL_PSEUDO_BEGIN] = target_sel;
    }
}

/* Check if specified cg_id has a corresponding mux that need processing
 * return a negative value: no corresponding mux
 * return a non-negative value: has corresponding mux (returns its corresponding mux_id)
 */
ATTR_TEXT_IN_TCM static int32_t clock_check_cg_in_mux(hal_clock_cg_id cg_id)
{
    /* Check if the clock_id has a corresponding mux that need to be switched
     * If one exists -> call mux_sel to trigger clock source/divider enable etc..
     */
    for(uint8_t mux_id=0; mux_id<TOTAL_MUX_CNT; mux_id++) {
        if(mux_tbl[mux_id].cg_id == cg_id) {
            return mux_id;
        }
    }
    return HAL_CLOCK_STATUS_INVALID_PARAMETER;
}

/* request type
 * CG_REQUEST_STATUS: return CG_CLR__CLK_ON, CG_SET__CLK_OFF, HAL_CLOCK_STATUS_INVALID_PARAMETER
 * CG_REQUEST_CLEAR : return HAL_CLOCK_STATUS_OK, HAL_CLOCK_STATUS_INVALID_PARAMETER
 * CG_REQUEST_SET   : return HAL_CLOCK_STATUS_OK, HAL_CLOCK_STATUS_ERROR, HAL_CLOCK_STATUS_INVALID_PARAMETER
 * others           : return HAL_CLOCK_STATUS_INVALID_PARAMETER
 */
ATTR_TEXT_IN_TCM static int32_t clock_physical_cg_ctrl(hal_clock_cg_id clock_id, cg_request_t request)
{
    volatile uint32_t *con_addr = NULL, *set_addr = NULL, *clr_addr = NULL;
    uint32_t bit_idx = clock_id & 0x1F;

    /* Set pointer to CG reg ptr */
    if((clock_id >= HAL_CLOCK_CG_XO_PDN_PD_BEGIN) && (clock_id <= HAL_CLOCK_CG_XO_PDN_PD_END)) {
        con_addr = XO_PDN_PD_COND0__XO_PDN_PD_COND0;
        set_addr = XO_PDN_PD_SETD0__XO_PDN_PD_SETD0;
        clr_addr = XO_PDN_PD_CLRD0__XO_PDN_PD_CLRD0;
    }
    else if((clock_id >= HAL_CLOCK_CG_XO_PDN_AO0_BEGIN) && (clock_id <= HAL_CLOCK_CG_XO_PDN_AO0_END)) {
        con_addr = XO_PDN_AO_COND0__XO_PDN_AO_COND0;
        set_addr = XO_PDN_AO_SETD0__XO_PDN_AO_SETD0;
        clr_addr = XO_PDN_AO_CLRD0__XO_PDN_AO_CLRD0;
    }
    else if((clock_id >= HAL_CLOCK_CG_XO_PDN_AO1_BEGIN) && (clock_id <= HAL_CLOCK_CG_XO_PDN_AO1_END)) {
        con_addr = XO_PDN_AO_COND1__XO_PDN_AO_COND1;
        set_addr = XO_PDN_AO_SETD1__XO_PDN_AO_SETD1;
        clr_addr = XO_PDN_AO_CLRD1__XO_PDN_AO_CLRD1;
    }
    else if((clock_id >= HAL_CLOCK_CG_XO_PDN_TOP0_BEGIN) && (clock_id <= HAL_CLOCK_CG_XO_PDN_TOP0_END)) {
        con_addr = XO_PDN_TOP_COND0__XO_PDN_TOP_COND0;
        set_addr = XO_PDN_TOP_SETD0__XO_PDN_TOP_SETD0;
        clr_addr = XO_PDN_TOP_CLRD0__XO_PDN_TOP_CLRD0;
    }
    else if((clock_id >= HAL_CLOCK_CG_XO_PDN_TOP1_BEGIN) && (clock_id <= HAL_CLOCK_CG_XO_PDN_TOP1_END)) {
        con_addr = XO_PDN_TOP_COND1__XO_PDN_TOP_COND1;
        set_addr = XO_PDN_TOP_SETD1__XO_PDN_TOP_SETD1;
        clr_addr = XO_PDN_TOP_CLRD1__XO_PDN_TOP_CLRD1;
    }
    else if((clock_id >= HAL_CLOCK_CG_PDN_PD_BEGIN) && (clock_id <= HAL_CLOCK_CG_PDN_PD_END)) {
        con_addr = PDN_PD_COND0__PDN_PD_COND0;
        set_addr = PDN_PD_SETD0__PDN_PD_SETD0;
        clr_addr = PDN_PD_CLRD0__PDN_PD_CLRD0;
    }
    else if((clock_id >= HAL_CLOCK_CG_PDN_TOP_BEGIN) && (clock_id <= HAL_CLOCK_CG_PDN_TOP_END)) {
        con_addr = PDN_TOP_COND0__PDN_TOP_COND0;
        set_addr = PDN_TOP_SETD0__PDN_TOP_SETD0;
        clr_addr = PDN_TOP_CLRD0__PDN_TOP_CLRD0;
    }
    else {
        return HAL_CLOCK_STATUS_INVALID_PARAMETER;
    }

    if(request == CG_REQUEST_STATUS) {
        return ((*con_addr >> bit_idx) & 0x01); /* status (return cg bit directly) */
    }
    else if(request == CG_REQUEST_CLEAR) {
        *clr_addr = (1 << bit_idx); /* cg clear (clock on) */
    }
    else if(request == CG_REQUEST_SET) {
        uint8_t idx = 0;

        do {
            if(clock_id == clk_always_on_cg_tbl[idx]) { /* do not allow disabling of the CG in the table */
                return HAL_CLOCK_STATUS_ERROR;
            }
        }
        while(clk_always_on_cg_tbl[++idx] != HAL_CLOCK_CG_DUMMY_END);

        *set_addr = (1 << bit_idx); /* cg set (clock off) */
    }
    else {
        return HAL_CLOCK_STATUS_INVALID_PARAMETER;
    }
    return HAL_CLOCK_STATUS_OK;
}

void clock_cg_init(void)
{
    struct cg_init_stat {
        uint8_t cg_id;
        uint8_t stat;
    };

    const struct cg_init_stat cg_init_tbl[] = {
        /* CKSYS_XO_CLK     0x42040000 -----------------------------------------------------
         * XO_PDN_PD_COND0  + 0x000,  Default: 0x0000FFFF
         * XO_PDN_PD_SETD0  + 0xB10
         * XO_PDN_PD_CLRD0  + 0xB20
         * --------------------------------------------------------------------------------- */
        /* --- HW default disabled --- */

        /* --- HW default enabled --- */
        /* bit 17, RG_SW_AUXADC_CG */
            { .cg_id = HAL_CLOCK_CG_AUXADC,            .stat = CLK_REQ_DISABLE },

        /* CKSYS_XO_CLK     0x42040000 -----------------------------------------------------
         * XO_PDN_AO_COND0  + 0x004,  Default: 0x0000FFFF
         * XO_PDN_AO_SETD0  + 0xB40
         * XO_PDN_AO_CLRD0  + 0xB50
         * --------------------------------------------------------------------------------- */
        /* --- HW default disabled --- */
        /* bit 0 , RG_SW_PWM_DMA_0_CG */
        /* bit 1 , RG_SW_PWM_DMA_1_CG */
        /* bit 2 , RG_SW_PWM_2_CG */
        /* bit 3 , RG_SW_PWM_3_CG */
        /* bit 4 , RG_SW_PWM_4_CG */
        /* bit 5 , RG_SW_ARGB_BCLK_CG */
        /* bit 7 , RG_SW_UART1_CG */
        /* bit 8 , RG_SW_UART2_CG */
        /* bit 9 , RG_SW_UART_DMA0_CG */
        /* bit 10, RG_SW_UART_DMA1_CG */
        /* bit 11, RG_SW_UART_DMA2_CG */
        /* bit 12, RG_SW_I3C0_CG */
        /* bit 13, RG_SW_I3C_DMA0_CG */
        /* bit 15, RG_GLB_CON_DEBUG_DIS_CG */

        /* --- HW default enabled --- */
        /* bit 16, RG_SW_SPM_PCLK_CG */
        /* bit 17, RG_SW_SPM_BCLK_CM33_CG */
        /* bit 19, RG_SW_SPM_DIV_CG */
        /* bit 21, RG_SW_SPM_SYS_CG */
        /* bit 23, RG_SW_OSTIMER_CG */
        /* bit 24, RG_SW_GPTIMER_CG */
        /* bit 25, RG_SW_GPTIMER_SEC_CG */
        /* bit 26, RG_SW_SECURITY_AO_CG */
        /* bit 27, RG_SW_KEY_SCAN_BCLK_CG */
            { .cg_id = HAL_CLOCK_CG_KEY_SCAN_BCLK,     .stat = CLK_REQ_DISABLE },
        /* bit 28, RG_SW_KEY_SCAN_F2M_CG */
            { .cg_id = HAL_CLOCK_CG_KEY_SCAN_F2M,      .stat = CLK_REQ_DISABLE },
        /* bit 29, RG_SW_UART0_CG */
        /* bit 30, RG_SW_PMU_1M_CG */

        /* CKSYS_XO_CLK     0x42040000 -----------------------------------------------------
         * XO_PDN_AO_COND1  + 0x008,  Default: 0x0000FFFF
         * XO_PDN_AO_SETD1  + 0xB44
         * XO_PDN_AO_CLRD1  + 0xB54
         * --------------------------------------------------------------------------------- */
        /* --- HW default disabled --- */
        /* bit 0 , RG_SW_FAST_DMA_1_CG */
        /* bit 1 , RG_SW_SPIMST0_BUS_CG */
        /* bit 2 , RG_SW_SPIMST1_BUS_CG */
        /* bit 14, RG_SW_BUS_ERR_AO_CG */
        /* bit 15, RG_SW_SEC_MON_AO_CG */

        /* --- HW default enabled --- */

        /* CKSYS_XO_CLK      0x42040000 -----------------------------------------------------
         * XO_PDN_TOP_COND0  + 0x00C,  Default: 0x0000FFFF
         * XO_PDN_TOP_SETD0  + 0xB70
         * XO_PDN_TOP_CLRD0  + 0xB80
         * --------------------------------------------------------------------------------- */
        /* --- HW default disabled --- */
        /* bit 0 , RG_SW_SPIMST0_CG */
        /* bit 1 , RG_SW_SPIMST1_CG */
        /* bit 2 , RG_SW_SPIMST2_CG */
        /* bit 4 , RG_SW_I3C_CG */
        /* bit 5 , RG_SW_BT_HOP_CG */
        /* bit 6 , RG_SW_BT_MAC_CONN_CG */
        /* bit 10, RG_SW_IRTX_CG */
        /* bit 12, RG_SW_AUD_TEST_CG */
        /* bit 13, RG_SEC_MON_TOP_CG */
        /* bit 14, RG_SW_BUS_ERR_TOP_CG */
        /* bit 15, RG_CKSYS_DEBUG_DIS_CG */

        /* --- HW default enabled --- */
        /* bit 17, RG_SW_SFC_CG */
        /* bit 18, RG_SW_ESC_CG */
            { .cg_id = HAL_CLOCK_CG_ESC,               .stat = CLK_REQ_DISABLE },
        /* bit 19, RG_SW_SPISLV_CG */
            { .cg_id = HAL_CLOCK_CG_SPISLV,            .stat = CLK_REQ_DISABLE },
#ifndef __EXT_DA__
        /* bit 20, RG_SW_USB_CG */
            { .cg_id = HAL_CLOCK_CG_USB,               .stat = CLK_REQ_DISABLE },
#endif
        /* bit 21, RG_SW_AUD_INTBUS_CG */
            { .cg_id = HAL_CLOCK_CG_AUD_INTBUS,        .stat = CLK_REQ_DISABLE },
        /* bit 22, RG_SW_IBEX_CG */
        /* bit 23, RG_SW_SEJ_CG */
        /* bit 25, RG_SW_EFUSE_CG */
        /* bit 26, RG_SW_BT_MAC_CG */

        /* CKSYS_XO_CLK      0x42040000 -----------------------------------------------------
         * XO_PDN_TOP_COND1  + 0x010,  Default: 0x0000FFFF
         * XO_PDN_TOP_SETD1  + 0xBA0
         * XO_PDN_TOP_CLRD1  + 0xBB0
         * --------------------------------------------------------------------------------- */
        /* --- HW default disabled --- */

        /* --- HW default enabled --- */
        /* bit 16, RG_SW_CMSYS_BUS_CG */
        /* bit 17, RG_SW_MEM_BUS_CG */
        /* bit 18, RG_SW_CONN_BUS_CG */
        /* bit 24, RG_SW_AUD_ENGINE_CG */
            { .cg_id = HAL_CLOCK_CG_AUD_ENGINE,        .stat = CLK_REQ_DISABLE },
        /* bit 29, RG_SW_OSC_LS_D2_CG */
        /* bit 30, RG_SW_OSC_HS_D2_CG */
        /* bit 31, RG_SW_OSC_HS_D4_CG */

        /* CKSYS_BUS_CLK   0x422D0000 -----------------------------------------------------
         * PDN_PD_COND0    + 0x020,  Default: 0x0000FFFF
         * PDN_PD_SETD0    + 0x310
         * PDN_PD_CLRD0    + 0x320
         * --------------------------------------------------------------------------------- */
        /* --- HW default disabled --- */
        /* bit 0 , RG_SW_AUXADC_SRAM_CG */
        /* bit 1 , RG_SW_FAST_DMA_0_CG */
        /* bit 4 , RG_SW_SPIMST2_BUS_CG */
        /* bit 5 , RG_SW_I3C1_CG */
        /* bit 6 , RG_SW_I3C_DMA1_CG */
        /* bit 9 , RG_SW_TRNG_CG */
        /* bit 10, RG_SW_SPISLV_BUS_CG */
        /* bit 11, RG_SW_IRRX_CG */
        /* bit 12, RG_SW_IRRX_BUS_CG */
        /* bit 13, RG_SW_AIO_CG */
        /* bit 14, RG_SW_BUS_ERR_CG */
        /* bit 15, RG_SW_SEC_MON_CG */

        /* --- HW default enabled --- */
        /* bit 18, RG_SW_AESOTF_CG */
            { .cg_id = HAL_CLOCK_CG_AESOTF,            .stat = CLK_REQ_DISABLE },
        /* bit 19, RG_SW_AESOTF_ESC_CG */
            { .cg_id = HAL_CLOCK_CG_AESOTF_ESC,        .stat = CLK_REQ_DISABLE },
#ifndef __EXT_DA__
        /* bit 20, RG_SW_CRYPTO_CG */
            { .cg_id = HAL_CLOCK_CG_CRYPTO,            .stat = CLK_REQ_DISABLE },
        /* bit 23, RG_SW_USB_BUS_CG */
            { .cg_id = HAL_CLOCK_CG_USB_BUS,           .stat = CLK_REQ_DISABLE },
        /* bit 24, RG_SW_USB_DMA_CG */
            { .cg_id = HAL_CLOCK_CG_USB_DMA,           .stat = CLK_REQ_DISABLE },
#endif

        /* CKSYS_BUS_CLK   0x422D0000 -----------------------------------------------------
         * PDN_AO_COND0    + 0x024,  Default: 0x0000FFFF
         * PDN_AO_SETD0    + 0x340
         * PDN_AO_CLRD0    + 0x350
         * --------------------------------------------------------------------------------- */
        /* --- HW default disabled --- */

        /* --- HW default enabled --- */

        /* CKSYS_BUS_CLK   0x422D0000 -----------------------------------------------------
         * PDN_TOP_COND0   + 0x028,  Default: 0x0000FFFF
         * PDN_TOP_SETD0   + 0x370
         * PDN_TOP_CLRD0   + 0x380
         * --------------------------------------------------------------------------------- */
        /* --- HW default disabled --- */

        /* --- HW default enabled --- */
        /* bit 16, RG_SW_CMSYS_ROM_CG */
    };

    uint8_t idx, tbl_size = sizeof(cg_init_tbl) / sizeof(cg_init_tbl[0]);
    for(idx=0; idx<tbl_size; idx++) {
        clock_physical_cg_ctrl(cg_init_tbl[idx].cg_id, cg_init_tbl[idx].stat);
    }
}

/* Estimate winset setting (currently returns accuracy of 0.04%) target winset value
 * Function is currently designed for DCXO as reference clk
 * (winset + 1)          data
 * ------------ = ------------------
 *   Ref Clk        Src Clk (target)
 */
uint32_t fqmtr_winset_estimate(uint32_t target_freq_hz)
{
    return hal_clock_fqmtr_winset_estimate(DCXO_HZ, target_freq_hz);
}

static void lposc_k_val(lposc_k_val_t k_val_type, uint32_t target_khz)
{
    volatile uint8_t *pRg_k_val;
    uint32_t fqmtr_khz, winset, target_hz = target_khz * 1000;
    uint8_t  i, kval;
    hal_src_clock src_clk;

    if(k_val_type == LPOSC_K_CALI) {
        pRg_k_val = RTC_LPOSC_CON2__LPOSC_RBANK_CALI;
    *RTC_LPOSC_CON2__LPOSC_RBANK_FT = 0;
        src_clk = AD_HFOSC_D3_CLK;
        target_hz /= 3;
        target_khz /= 3;
    i = 0x20;  /* 6 bits, set MSB=1 in advance */
        }
    else {  /* LPOSC_K_FT */
        pRg_k_val = RTC_LPOSC_CON2__LPOSC_RBANK_FT;
        src_clk = AD_HFOSC_HS;
    i = 0x10;  /* 5 bits, set MSB=1 in advance */
    }

    kval = i;
    winset = fqmtr_winset_estimate(target_hz);
    do {
        *CLKSQ_CON1__RG_LPOSC_DIV3_RDY = 0;
        *CLKSQ_CON1__RG_LPOSC_LS_RDY = 0;
        *CLKSQ_CON1__RG_LPOSC_HS_RDY = 0;
        *pRg_k_val = kval;
        hal_gpt_delay_us(20);
        *CLKSQ_CON1__RG_LPOSC_DIV3_RDY = 1;
        *CLKSQ_CON1__RG_LPOSC_LS_RDY = 1;
        *CLKSQ_CON1__RG_LPOSC_HS_RDY = 1;

        fqmtr_khz = hal_clock_get_freq_meter(src_clk, winset);
        if(fqmtr_khz >= target_khz) {
            kval -= i; /* Current bit =0 */
        }
        i >>= 1;       /* Next lower bit */
        kval += i;     /* Set next lower bit =1 in advance, if i!=0 */
    } while(i);
    *pRg_k_val = kval;
}

void lposc_calibrate(uint32_t lposc_khz_cali, uint32_t lposc_hs_khz_ft)
{
    lposc_k_val(LPOSC_K_CALI, lposc_khz_cali);
    lposc_k_val(LPOSC_K_FT, lposc_hs_khz_ft);
}

void lposc_enable(bool blReEnable)
{
    if(*CLKSQ_CON1__DA_LPOSC_EN == 0) {
        if(!blReEnable) {
            *RTC_LPOSC_CON2__LPOSC_RBANK_FT = 0;
            *RTC_LPOSC_CON2__LPOSC_RBANK_CALI = 0x28;
            *RTC_LPOSC_CON2__LPOSC_BIAS_SEL = 0x25;
            *RTC_LPOSC_CON2__LPOSC_CBANK_SEL = 0x0D;

            /* Set LPOSC LS divider */
            if(g_clk_cfg.lposc_ls_div == LPOSC_LS_DIV12) {
                *RTC_LPOSC_CON3__LPOSC_HFOSC_LS_SEL = 2;
            }
            else {
                *RTC_LPOSC_CON3__LPOSC_HFOSC_LS_SEL = 1; /* default DIV6 */
            }

            /* Set LPOSC HS divider */
            if(g_clk_cfg.lposc_hs_div == LPOSC_HS_DIV3) {
                *RTC_LPOSC_CON3__LPOSC_HFOSC_HS_SEL = 1;
            }
            else if(g_clk_cfg.lposc_hs_div == LPOSC_HS_DIV4) {
                *RTC_LPOSC_CON3__LPOSC_HFOSC_HS_SEL = 2;
            }
            else {
                *RTC_LPOSC_CON3__LPOSC_HFOSC_HS_SEL = 0; /* default DIV2 (also HW default) */
            }
        }
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

        /* Allow SPM to control clock on/off, must enable LPOSC before setting */
        *CLKSQ_CON0__BP_PLL_DLY = 0;
        *CLKSQ_CON0__LPOSC_EN_SEL = 0; /* Only works when HFOSC_SSC_SYNCK clock exists */

        /* for OSC_26M */
        clock_physical_cg_ctrl(HAL_CLOCK_CG_OSC_LS_D2, CLK_REQ_ENABLE);
        pseudo_cg_tbl[HAL_CLOCK_CG_PSUEDO_OSC_26M-HAL_CLOCK_CG_PSEUDO_BEGIN] = CG_CLR__CLK_ON;

        clk_prt_info("lposc_enable", 0);
    }
}

void lposc_disable(void)
{
    if(*CLKSQ_CON1__DA_LPOSC_EN) {
        clk_prt_info("lposc_disable", 0);
        *CLKSQ_CON1__RG_LPOSC_LS_RDY = 0;
        *CLKSQ_CON1__RG_LPOSC_HS_RDY = 0;
        *CLKSQ_CON1__RG_LPOSC_DIV3_RDY = 0;
        *RTC_LPOSC_CON0__LPOSC_DIV48_CK_EN = 0;
        *RTC_LPOSC_CON1__LPOSC_HFOSC_LS_EN = 0;
        *RTC_LPOSC_CON1__LPOSC_HFOSC_HS_EN = 0;
        *RTC_LPOSC_CON0__LPOSC_DIV3_CK_EN = 0;
        *CLKSQ_CON1__DA_LPOSC_EN = 0;

        /* Disallow SPM to control clock on/off */
        *CLKSQ_CON0__BP_PLL_DLY = 1;
        *CLKSQ_CON0__LPOSC_EN_SEL = 1;
    }
}

ATTR_TEXT_IN_TCM void hal_clock_dcxo_dbl_calibrate(void)
{
    uint32_t _DA_DCXO_REFDBL_DELAY, _DA_DCXO_REFDCC_DUTY_0P5, _DA_DCXO_REFDBL_POLARITY, _DA_DCXO_REFDBL_DUTY, dwTemp;

    /* --- Step1: Turn on DBL PW SW to RF_LDO_VOUT bypass mode --- */
    PT_DCXO_RG5->value |= _U32_B2_;    /* RG_DCXO_DBL_RSV[2]=1, DBL's RF_LDO_VOUT PW SW on */
    PT_DCXO_RG5->value |= _U32_B1_;    /* RG_DCXO_DBL_RSV[1]=1, RF_LDO_VOUT to RO SW on */
    PT_DCXO_RG5->value &= ~_U32_B0_;   /* RG_DCXO_DBL_RSV[0]=0, DCXO LDO SW off */
    hal_gpt_delay_us(10);              /* Wait for voltage settle */

    /* --- Step2: DCXO DBL CAL 1 --- */
    PTF_DBL_CFG2.REFDBL_DCC_PD_WAIT_SEL = 3;      /* Apply majority rule and increase calibration time */
    PTF_DBL_CFG2.REFDBL_PD_MODE_SEL = 1;
    PTF_DBL_MAN_SEL0.DBL_EN_MAN_SEL = 0;          /* DBL control set to manual mode */
    PTF_DBL_MAN_SEL0.DCXO_REFDBL_EN_MAN_SEL = 0;
    PTF_DBL_MAN_SEL0.DCXO_CLK_DIG_EN_MAN_SEL = 0;
    PTF_DBL_MAN0.DBL_EN_MAN = 1;                  /* Manual enable REFDBL_EN, CLK_DIG_EN, DBL_EN */
    PTF_DBL_MAN0.DCXO_REFDBL_EN_MAN = 1;
    PTF_DBL_MAN0.DCXO_CLK_DIG_EN_MAN = 1;
    *DCXO_PCON8__DBL_64M_EN = 1;                  /* DBL CAL enable */
    hal_gpt_delay_us(10);                         /* Wait for DBL calibration */

    /* Read calibration code and store result */
    _DA_DCXO_REFDBL_DELAY = PTF_DCXO_DBL_OUT1.DA_DCXO_REFDBL_DELAY;
    _DA_DCXO_REFDCC_DUTY_0P5 = PTF_DCXO_DBL_OUT1.DA_DCXO_REFDCC_DUTY_0P5;
    _DA_DCXO_REFDBL_POLARITY = PTF_DCXO_DBL_OUT1.DA_DCXO_REFDBL_POLARITY;
    //clk_force_prt_info("DCXO_DBL_OUT1 0x%08X", 1, PT_DCXO_DBL_OUT1->value);

    *DCXO_PCON8__DBL_64M_EN = 0;       /* DBL CAL disable */

    /* Manual disable REFDBL_EN, CLK_DIG_EN */
    PTF_DBL_MAN0.DCXO_REFDBL_EN_MAN = 0;
    PTF_DBL_MAN0.DCXO_CLK_DIG_EN_MAN = 0;

    /* --- Step3: Switch to DCXO LDO mode --- */
    PT_DCXO_RG5->value &= ~_U32_B2_;   /* RG_DCXO_DBL_RSV[2]=0, DBL's RF_LDO_VOUT PW SW off */
    PT_DCXO_RG5->value &= ~_U32_B1_;   /* RG_DCXO_DBL_RSV[1]=0, RF_LDO_VOUT to RO SW off */
    PT_DCXO_RG5->value |= _U32_B0_;    /* RG_DCXO_DBL_RSV[0]=1, DCXO LDO SW on */
    hal_gpt_delay_us(10);              /* Wait for voltage settle */

    /* --- Step4: DCXO DBL CAL 2 --- */
    //PTF_DBL_MAN0.DBL_EN_MAN = 1;       /* Manual enable REFDBL_EN, CLK_DIG_EN, DBL_EN */
    PTF_DBL_MAN0.DCXO_REFDBL_EN_MAN = 1;
    PTF_DBL_MAN0.DCXO_CLK_DIG_EN_MAN = 1;
    *DCXO_PCON8__DBL_64M_EN = 1;       /* DBL CAL enable */
    hal_gpt_delay_us(10);              /* Wait for DBL calibration */

    /* Read calibration code and store result */
    _DA_DCXO_REFDBL_DUTY = PTF_DCXO_DBL_OUT0.DA_DCXO_REFDBL_DUTY;
    //clk_force_prt_info("DCXO_DBL_OUT0 0x%08X", 1, PT_DCXO_DBL_OUT0->value);

    /* Write calibration result to top misc */
    (*DCXO_DBL_MISC0__DCXO_DBL_MISC0) &= 0xFFE00000;  /* Clear bit[20:0] */
    dwTemp = (_DA_DCXO_REFDBL_DUTY << 9) |            /* bit[20:9] */
             (_DA_DCXO_REFDBL_DELAY << 2) |           /* bit[8:2] */
             (_DA_DCXO_REFDCC_DUTY_0P5 << 1) |        /* bit[1] */
              _DA_DCXO_REFDBL_POLARITY;               /* bit[0] */
    (*DCXO_DBL_MISC0__DCXO_DBL_MISC0) |= dwTemp;
    (*DCXO_DBL_MISC0__DCXO_DBL_MISC0) |= _U32_B21_;   /* Calibration result update done */

    /* --- Step5: Return to original registers --- */
    *DCXO_PCON8__DBL_64M_EN = 0;                      /* DBL CAL disable */
    PTF_DBL_MAN0.DBL_EN_MAN = 0;                      /* Manual disable REFDBL_EN, CLK_DIG_EN, DBL_EN */
    PTF_DBL_MAN0.DCXO_REFDBL_EN_MAN = 0;
    PTF_DBL_MAN0.DCXO_CLK_DIG_EN_MAN = 0;
    PTF_DBL_MAN_SEL0.DBL_EN_MAN_SEL = 1;              /* DBL control set to normal mode */
    PTF_DBL_MAN_SEL0.DCXO_REFDBL_EN_MAN_SEL = 1;
    PTF_DBL_MAN_SEL0.DCXO_CLK_DIG_EN_MAN_SEL = 1;
    PTF_DBL_MAN_SEL0.DCXO_REFDBL_DCC_FINISH_MAN_SEL = 1;
    //clk_force_prt_info("DCXO_DBL_OUT0 0x%08X", 1, PT_DCXO_DBL_OUT0->value);
}

ATTR_TEXT_IN_TCM static void clock_src_ctrl(mux_src_t src_id, bool enable)
{
    if((src_id >= MUX_OSC_HS) && (src_id <= MUX_OSC_26M)) {
        if(enable) {
            lposc_enable(true);
        }
        else {
            lposc_disable();
        }
    }
    else if(src_id == MUX_XO_DBL) {
        bool blChanged = false;
        if(enable) {
            if(*RTC_DCXO_CON4__DBL_64M_EN == 0) {
                blChanged = true;
            }
        }
        else {
            if(*RTC_DCXO_CON4__DBL_64M_EN) {
                blChanged = true;
            }
        }
        if(blChanged) {
            if(enable) {
                *RTC_DCXO_CON4__DBL_64M_EN = 1;
                hal_clock_bt_rx_adc_set_rg(CLK_BT_RX_ADC_DEFAULT);
            }
            else {
                if((clk_bt_rx_adc==CLK_BT_RX_ADC_32M) || (clk_bt_rx_adc==CLK_BT_RX_ADC_64M)) {
                    hal_clock_bt_rx_adc_set_rg(clk_bt_rx_adc);
                }
                *RTC_DCXO_CON4__DBL_64M_EN = 0;
            }
        }
    }
    /*
    else if(src_id == MUX_OSC_HS) {
        if(enable) {
            if(*RTC_LPOSC_CON1__LPOSC_HFOSC_HS_EN == 0) {
                *RTC_LPOSC_CON1__LPOSC_HFOSC_HS_EN = 1;
                hal_gpt_delay_us(15);
                *CLKSQ_CON1__RG_LPOSC_HS_RDY = 1;
            }
        }
        else {
            if(*RTC_LPOSC_CON1__LPOSC_HFOSC_HS_EN) {
                *CLKSQ_CON1__RG_LPOSC_HS_RDY = 0;
                *RTC_LPOSC_CON1__LPOSC_HFOSC_HS_EN = 0;
            }
        }
    }
    */
}

ATTR_TEXT_IN_TCM static void clock_src_div_ctrl(mux_src_t src_id, mux_div_t div, bool enable)
{
    if(src_id == MUX_OSC_HS) {
        if(div == MUX_DIV_D2) {
            if(enable) {
                if(clock_physical_cg_ctrl(HAL_CLOCK_CG_OSC_HS_D2, CG_REQUEST_STATUS) == CG_SET__CLK_OFF) {
                    clock_physical_cg_ctrl(HAL_CLOCK_CG_OSC_HS_D2, CLK_REQ_ENABLE);
                }
            }
            else {
                if(clock_physical_cg_ctrl(HAL_CLOCK_CG_OSC_HS_D2, CG_REQUEST_STATUS) == CG_CLR__CLK_ON) {
                    clock_physical_cg_ctrl(HAL_CLOCK_CG_OSC_HS_D2, CLK_REQ_DISABLE);
                }
            }
        }
        else if(div == MUX_DIV_D4) {
            if(enable) {
                if(clock_physical_cg_ctrl(HAL_CLOCK_CG_OSC_HS_D4, CG_REQUEST_STATUS) == CG_SET__CLK_OFF) {
                    clock_physical_cg_ctrl(HAL_CLOCK_CG_OSC_HS_D4, CLK_REQ_ENABLE);
                }
            }
            else {
                if(clock_physical_cg_ctrl(HAL_CLOCK_CG_OSC_HS_D4, CG_REQUEST_STATUS) == CG_CLR__CLK_ON) {
                    clock_physical_cg_ctrl(HAL_CLOCK_CG_OSC_HS_D4, CLK_REQ_DISABLE);
                }
            }
        }
    }
    else if(src_id == MUX_OSC_LS) {
        if(div == MUX_DIV_D2) {
            if(enable) {
                if(clock_physical_cg_ctrl(HAL_CLOCK_CG_OSC_LS_D2, CG_REQUEST_STATUS) == CG_SET__CLK_OFF) {
                    clock_physical_cg_ctrl(HAL_CLOCK_CG_OSC_LS_D2, CLK_REQ_ENABLE);
                }
            }
            else {
                if(clock_physical_cg_ctrl(HAL_CLOCK_CG_OSC_LS_D2, CG_REQUEST_STATUS) == CG_CLR__CLK_ON) {
                    clock_physical_cg_ctrl(HAL_CLOCK_CG_OSC_LS_D2, CLK_REQ_DISABLE);
                }
            }
        }
    }
}

ATTR_TEXT_IN_TCM static void clock_enable_resource_before_mux_switch(clock_mux_sel_id mux_id, clk_mux_sel_idx_t next_mux_sel)
{
    /* N-to-1 mux requires both original, and next clock source/dividers both be enabled */
    if(mux_tbl[mux_id].other.mux_type == PHYSICAL_N_TO_1_MUX) {
        /* enable current clock source, divider */
        uint8_t cur_mux_sel = *(mux_tbl[mux_id].p_sel_rg);
        clock_src_ctrl(mux_tbl[mux_id].sel[cur_mux_sel].src, true);
        clock_src_div_ctrl(mux_tbl[mux_id].sel[cur_mux_sel].src, mux_tbl[mux_id].sel[cur_mux_sel].div, true);
    }

    /* enable next clock source, divider */
    clock_src_ctrl(mux_tbl[mux_id].sel[next_mux_sel].src, true);
    clock_src_div_ctrl(mux_tbl[mux_id].sel[next_mux_sel].src, mux_tbl[mux_id].sel[next_mux_sel].div, true);

    if(mux_tbl[mux_id].other.cg_type == PSEUDO_CG) {
        /* nobody actually calls enable/disable psuedo_cg
         * just used as an indication whether or not clock resource need to be enable/disabled during post process
         * (PSUEDO CG is set to on(clock disabled by default), and will maintain on status for now)
         */
        if((mux_tbl[mux_id].cg_id >= HAL_CLOCK_CG_PSEUDO_BEGIN) && (mux_tbl[mux_id].cg_id <= HAL_CLOCK_CG_PSEUDO_END)) {
            pseudo_cg_tbl[mux_tbl[mux_id].cg_id-HAL_CLOCK_CG_PSEUDO_BEGIN] = CG_CLR__CLK_ON;
        }
        else {
            clk_prt_err("Unknown pseudo cg_id %d", 1, mux_tbl[mux_id].cg_id);
        }
    }
}

/* Disable unused resources clock source/divider */
ATTR_TEXT_IN_TCM static void clock_disable_resource_after_mux_switch(void)
{
    T_CLK_RESOURCE_CHK res_chk;
    mux_src_t mux_src;
    uint8_t mux_id, mux_sel;

    res_chk.value = 0;

    for(mux_id=0; mux_id<TOTAL_MUX_CNT; mux_id++) {
        if(mux_tbl[mux_id].other.mux_type == PSEUDO_MUX) {
            if((mux_id >= CLK_MUX_SEL_PSEUDO_BEGIN) && ((mux_id-CLK_MUX_SEL_PSEUDO_BEGIN) < PSEUDO_MUX_TTL)) {
                mux_sel = pseudo_mux_tbl[mux_id-CLK_MUX_SEL_PSEUDO_BEGIN];
            }
            else {
                continue;
            }
        }
        else {
            mux_sel = *(mux_tbl[mux_id].p_sel_rg);
        }

        if(hal_clock_is_enabled(mux_tbl[mux_id].cg_id)) {
            mux_src = mux_tbl[mux_id].sel[mux_sel].src;
            if(mux_src == MUX_XO_DBL) {
                res_chk.b.xo_dbl = 1;
            }
            else if(mux_src == MUX_OSC_HS) {
                res_chk.b.osc_hs = 1;
                if(mux_tbl[mux_id].sel[mux_sel].div == MUX_DIV_D2) {
                    res_chk.b.osc_hs_d2 = 1;
                }
                else if(mux_tbl[mux_id].sel[mux_sel].div == MUX_DIV_D4) {
                    res_chk.b.osc_hs_d4 = 1;
                }
            }
            else if(mux_src == MUX_OSC_LS) {
                if(mux_tbl[mux_id].sel[mux_sel].div == MUX_DIV_D2) {
                    res_chk.b.osc_ls_d2 = 1;
                }
            }

            if((mux_src >= MUX_OSC_HS) && (mux_src <= MUX_OSC_26M)) {
                res_chk.b.osc = 1;
            }
        }
    }

    if(!res_chk.b.xo_dbl) {
        clock_src_ctrl(MUX_XO_DBL, false);
    }
    if(!res_chk.b.osc) {
        clock_src_ctrl(MUX_OSC_HS, false); /* to disable LPOSC */
    }
    //if(!res_chk.b.osc_hs) {
    //    clock_src_ctrl(MUX_OSC_HS, false);
    //}

    if(!res_chk.b.osc_hs_d2) {
        clock_src_div_ctrl(MUX_OSC_HS, MUX_DIV_D2, false);
    }
    if(!res_chk.b.osc_hs_d4) {
        clock_src_div_ctrl(MUX_OSC_HS, MUX_DIV_D4, false);
    }
    if(!res_chk.b.osc_ls_d2) {
        clock_src_div_ctrl(MUX_OSC_LS, MUX_DIV_D2, false);
    }
}

uint8_t hal_clock_dvfs_get_sys_cfg(void)
{
    return g_clk_cfg.dvfs_sys_cfg;
}

uint8_t hal_clock_dvfs_get_cmsys_mux_idx(hal_dvfs_frq_t frq)
{
    return dvfs_clk_sys_mux_idx[frq];
}

ATTR_TEXT_IN_TCM void hal_clock_dvfs_enable_src_and_siwtch(clock_mux_sel_id mux_id, uint8_t sel)
{
    clock_enable_resource_before_mux_switch(mux_id, sel);
    clock_top_mux_ctrl(mux_id, sel);
}

ATTR_TEXT_IN_TCM void hal_clock_dvfs_switch(hal_dvfs_frq_t frq)
{
    if(frq < HAL_DVFS_FRQ_MAX) {
        uint8_t mux_idx = 0, mux_sel;

        hal_clock_dvfs_enable_src_and_siwtch(CLK_SYS_SEL, dvfs_clk_sys_mux_idx[frq]);
        hal_clock_dvfs_enable_src_and_siwtch(CLK_IBEX_SEL, dvfs_clk_ibex_mux_idx[frq]);
        do {
            if(frq == HAL_DVFS_FRQ_LOW) {
                mux_sel = 0;
            }
            else {
                mux_sel = dvfs_clk_other_mux_idx[mux_idx].mux_sel;
            }
            hal_clock_dvfs_enable_src_and_siwtch(dvfs_clk_other_mux_idx[mux_idx].mux_id, mux_sel);
        } while(dvfs_clk_other_mux_idx[++mux_idx].mux_id != MUX_ID_DUMMY_END);

        /*if(clk_flg.b.bt_mac_recover2dbl) {
            hal_clock_bt_mac_mux_set_idx(MUX_BT_MAC_IDX_XO_DBL);
            clk_flg.b.bt_mac_recover2dbl = 0;
        }*/

        if(frq == HAL_DVFS_FRQ_LOW) {
            pseudo_cg_tbl[HAL_CLOCK_CG_PSUEDO_OSC_26M-HAL_CLOCK_CG_PSEUDO_BEGIN] = CG_SET__CLK_OFF;
        }
        clock_disable_resource_after_mux_switch();
    }
}

/* Switch some clocks to lower frequency (<= 52 MHz) */
ATTR_TEXT_IN_TCM void hal_clock_dvfs_transitive_stage(void)
{
    /*if(hal_clock_bt_mac_mux_get_idx() == MUX_BT_MAC_IDX_XO_DBL) {
        clk_flg.b.bt_mac_recover2dbl = 1;
        hal_clock_bt_mac_mux_set_idx(MUX_BT_MAC_IDX_XO);
    }*/

    clock_top_mux_ctrl(CLK_SYS_SEL, MUX_SYS_IDX_XO);
}

uint32_t hal_clock_get_lposc_hs_khz(void)
{
    return g_clk_cfg.lposc_khz / g_clk_cfg.lposc_hs_div;
}

uint32_t hal_clock_get_lposc_ls_khz(void)
{
    return g_clk_cfg.lposc_khz / g_clk_cfg.lposc_ls_div;
}

uint32_t hal_clock_get_lposc_d3_khz(void)
{
    return g_clk_cfg.lposc_khz / 3;
}

uint32_t hal_clock_get_lposc_hs_hz(void)
{
    return (g_clk_cfg.lposc_khz * 1000) / g_clk_cfg.lposc_hs_div;
}

uint32_t hal_clock_get_lposc_ls_hz(void)
{
    return (g_clk_cfg.lposc_khz * 1000) / g_clk_cfg.lposc_ls_div;
}

uint32_t hal_clock_get_lposc_d3_hz(void)
{
    return (g_clk_cfg.lposc_khz * 1000) / 3;
}

/* REF Clock is XO */
uint32_t clock_get_src_freq_hz(hal_src_clock src_clk, uint32_t winset)
{
    uint32_t freq_meter_data = hal_clock_freq_meter_data(XO_CK, src_clk, winset);
    uint32_t src_hz = (((uint64_t)DCXO_HZ) * freq_meter_data) / (winset + 1);
    return src_hz;
}

/* REF Clock is XO */
uint32_t clock_get_src_freq_khz(hal_src_clock src_clk, uint32_t winset)
{
    return clock_get_src_freq_hz(src_clk, winset) / 1000;
}

void hal_clock_dcm_enable(clk_dcm_t dcm)
{
    switch(dcm) {
        case CLK_DCM_SFC:
            *SFC_DCM_CON_0__RG_SFC_DCM_DBC_NUM = 0xFF;
            *SFC_DCM_CON_0__RG_SFC_DCM_DBC_EN = 1;
            *SFC_DCM_CON_1__RG_SFC_CLKOFF_EN = 1;
            *SFC_DCM_CON_0__RG_SFC_DCM_APB_SEL = 6;
            (*SFC_DCM_CON_1__RG_SFC_DCM_APB_TOG) ^= 1; /* Toggle bit */
            break;
        case CLK_DCM_ESC:
            *ESC_DCM_CON_0__RG_ESC_DCM_DBC_NUM = 0xFF;
            *ESC_DCM_CON_0__RG_ESC_DCM_DBC_EN = 1;
            *ESC_DCM_CON_1__RG_ESC_CLKOFF_EN = 1;
            *ESC_DCM_CON_0__RG_ESC_DCM_APB_SEL = 6;
            (*ESC_DCM_CON_1__RG_ESC_DCM_APB_TOG) ^= 1; /* Toggle bit */
            break;
        case CLK_DCM_SLOW_BUS:
            // *XO_DCM_CON_0__RG_XO_SFSEL = DCM_DIV_16;
            *XO_DCM_CON_0__RG_XO_DCM_DBC_NUM = 2;
            *XO_DCM_CON_0__RG_XO_DCM_DBC_EN = 1;
            *XO_DCM_CON_1__RG_XO_CLKSLOW_EN = 1;
            *XO_DCM_CON_1__RG_XO_CLKOFF_EN = 1;
            *XO_DCM_CON_0__RG_XO_PLLCK_SEL = 1;
            break;
        case CLK_DCM_FAST_BUS:
            // *BUS_DCM_CON_0__RG_BUS_SFSEL = DCM_DIV_64;
            *BUS_DCM_CON_0__RG_BUS_DCM_DBC_NUM = 2;
            *BUS_DCM_CON_0__RG_BUS_DCM_DBC_EN = 1;
            *BUS_DCM_CON_1__RG_BUS_CLKSLOW_EN = 1;
            *BUS_DCM_CON_1__RG_BUS_CLKOFF_EN = 1;
            *BUS_DCM_CON_0__RG_BUS_PLLCK_SEL = 1;
            break;
        case CLK_DCM_CMSYS:
            *CMSYS_DCM_CON_0__RG_CM_SFSEL = DCM_DIV_64;
            *CMSYS_DCM_CON_1__RG_CM_CLKSLOW_EN = 1;
            *CMSYS_DCM_CON_0__RG_CM_PLLCK_SEL = 1;
            break;
        case CLK_DCM_MEMSYS:
            // *MEMSYS_DCM_CON_0__RG_MEMSYS_SFSEL = DCM_DIV_64;
            // *MEMSYS_DCM_CON_0__RG_MEMSYS_DCM_DBC_NUM = 0x1F;
            // *MEMSYS_DCM_CON_0__RG_MEMSYS_DCM_DBC_EN = 1;
            *MEMSYS_DCM_CON_1__RG_MEMSYS_CLKOFF_EN = 1;
            *MEMSYS_DCM_CON_0__RG_MEMSYS_PLLCK_SEL = 1;
            break;
        case CLK_DCM_BT_MAC:
            *BT_DCM_CON_0__RG_BT_SFSEL = DCM_DIV_32;
            *BT_DCM_CON_0__RG_BT_DCM_DBC_NUM = 2;
            *BT_DCM_CON_0__RG_BT_DCM_DBC_EN = 1;
            *BT_DCM_CON_1__RG_BT_CLKSLOW_EN = 1;
            *BT_DCM_CON_1__RG_BT_CLKOFF_EN = 1;
            *BT_DCM_CON_0__RG_BT_PLLCK_SEL = 1;
            break;
        default:
            return;
    }
    hal_gpt_delay_us(1);
}

void hal_clock_dcm_disable(clk_dcm_t dcm)
{
    switch(dcm) {
        case CLK_DCM_SFC:
            *SFC_DCM_CON_0__RG_SFC_DCM_DBC_EN = 0;
            *SFC_DCM_CON_1__RG_SFC_CLKOFF_EN = 0;
            *SFC_DCM_CON_0__RG_SFC_DCM_APB_SEL = 6;
            (*SFC_DCM_CON_1__RG_SFC_DCM_APB_TOG) ^= 1; /* Toggle bit */
            break;
        case CLK_DCM_ESC:
            *ESC_DCM_CON_0__RG_ESC_DCM_DBC_EN = 0;
            *ESC_DCM_CON_1__RG_ESC_CLKOFF_EN = 0;
            *ESC_DCM_CON_0__RG_ESC_DCM_APB_SEL = 6;
            (*ESC_DCM_CON_1__RG_ESC_DCM_APB_TOG) ^= 1; /* Toggle bit */
            break;
        case CLK_DCM_SLOW_BUS:
            *XO_DCM_CON_0__RG_XO_PLLCK_SEL = 0;
            *XO_DCM_CON_1__RG_XO_CLKSLOW_EN = 0;
            *XO_DCM_CON_1__RG_XO_CLKOFF_EN = 0;
            break;
        case CLK_DCM_FAST_BUS:
            *BUS_DCM_CON_0__RG_BUS_PLLCK_SEL = 0;
            *BUS_DCM_CON_1__RG_BUS_CLKSLOW_EN = 0;
            *BUS_DCM_CON_1__RG_BUS_CLKOFF_EN = 0;
            break;
        case CLK_DCM_CMSYS:
            *CMSYS_DCM_CON_0__RG_CM_PLLCK_SEL = 0;
            *CMSYS_DCM_CON_1__RG_CM_CLKSLOW_EN = 0;
            break;
        case CLK_DCM_MEMSYS:
            *MEMSYS_DCM_CON_0__RG_MEMSYS_PLLCK_SEL = 0;
            *MEMSYS_DCM_CON_1__RG_MEMSYS_CLKOFF_EN = 0;
            break;
        case CLK_DCM_BT_MAC:
            *BT_DCM_CON_0__RG_BT_PLLCK_SEL = 0;
            *BT_DCM_CON_0__RG_BT_DCM_DBC_EN = 0;
            *BT_DCM_CON_1__RG_BT_CLKSLOW_EN = 0;
            *BT_DCM_CON_1__RG_BT_CLKOFF_EN = 0;
            break;
        default:
            return;
    }
    hal_gpt_delay_us(1);
}

/* Top DCM Primary: CM33/BUS divider */
void hal_clock_dcm_primary_div_set(clk_dcm_div_t div)
{
    *SYS_FREE_DCM_CON__RG_SYS_FREE_FSEL0 = div;
    (*SYS_FREE_DCM_CON__RG_SYS_FSEL_UPDATE) ^= 1;  /* Toggle bit */
    clk_prt_info("DCM primary set div_rg %d, get div %d", 2, div, hal_clock_dcm_primary_div_get());
}

/* return 1, 2, 4, 8, 16, 32, 64 */
uint8_t hal_clock_dcm_primary_div_get(void)
{
    uint8_t rg_div = *SYS_FREE_DCM_CON__RG_SYS_FREE_FSEL0;

    if(rg_div) {
        return 64 / (rg_div << 1);
    }
    return 64;
}

/* sfc clock switch api in TCM (special case usage only!) */
ATTR_TEXT_IN_TCM void hal_clock_sfc_mux_sel_tcm(uint8_t mux_idx)
{
#ifndef CLOCK_COSIM
    uint32_t irq_mask = 0;
    hal_nvic_save_and_set_interrupt_mask(&irq_mask);
    /* ================ Critical Section Start ======================== */
#endif

    *CKSYS_CLK_FORCE_ON_0__CLK_SFC_FORCE_ON = 1;
    *CKSYS_CLK_CFG_0__CLK_SFC_SEL = mux_idx;
    *CKSYS_CLK_UPDATE_0__CHG_SFC = 1;
    while (*CKSYS_CLK_UPDATE_0__CHG_SFC);
    while (*CKSYS_CLK_UPDATE_STATUS_0__CHG_SFC_OK);
    *CKSYS_CLK_FORCE_ON_0__CLK_SFC_FORCE_ON = 0;

#ifndef CLOCK_COSIM
    /* ================ Critical Section End ======================== */
    hal_nvic_restore_interrupt_mask(irq_mask);
#endif
}

void hal_clock_chop_ck(bool enable, uint16_t divide_val)
{
    if(enable) {
        if(divide_val > 2047) {
            divide_val = 2047;
        }
        *CKSYS_CLK_DIV_0__CHOP_DIV_SEL = divide_val; /* XO/(2*(SEL+1)) */
        (*CKSYS_CLK_DIV_0__CHOP_DIV_CHG) ^= 1;       /* Toggle bit */
        *CKSYS_CLK_DIV_0__CHOP_DIV_EN = 1;
        hal_gpt_delay_us(384); /* wait 3 x f_chop_ck clock for stable */
    }
    else {
        *CKSYS_CLK_DIV_0__CHOP_DIV_EN = 0;
    }
}

bool hal_clock_out_by_gpio(uint8_t gpio_num, uint8_t clko_sel)
{
    if((gpio_num==6) || (gpio_num==17) || (gpio_num==18))
    {
        uint8_t aux_func = 5;
        volatile uint8_t *pClkoMode = GPIO_CLKO_CTRL_A__CLKO_MODE0;

        switch(gpio_num)
        {
            case 6:
                pClkoMode = GPIO_CLKO_CTRL_A__CLKO_MODE2;
                aux_func = 7;
                break;
            case 18:
                pClkoMode = GPIO_CLKO_CTRL_A__CLKO_MODE1;
                break;
            default:
                break;
        }

        _gpio_set_mode(gpio_num, aux_func);
        *pClkoMode = clko_sel;
#ifdef _CLOCK_DVT_
        clk_prt_info("clock_out_by_gpio: *0x%08X = 0x%08X", 2, RM_CKSYS_BASE+0x0058, *((volatile uint32_t *)(RM_CKSYS_BASE+0x0058)));
#endif
        return true;
    }
    return false;
}

void hal_clock_abb_clk_gen_enable(clk_abb_gen_t abb_clk, uint16_t divide_val)
{
    if (divide_val > 2047) {
        divide_val = 2047;
    }
    switch (abb_clk) {  /* XO/(2*(SEL+1)) */
        case CLK_ABBCK200K_BGR:
            *ABB_CLK_GEN_CFG_0__ABBCK200K_BGR_DIV_CHG = 0;
            while (*ABB_CLK_GEN_CFG_3__ABBCK200K_BGR_DIV_RDY);
            *ABB_CLK_GEN_CFG_0__ABBCK200K_BGR_DIV_EN = 1;
            *ABB_CLK_GEN_CFG_0__ABBCK200K_BGR_DIV_SEL = divide_val;
            *ABB_CLK_GEN_CFG_0__ABBCK200K_BGR_DIV_CHG = 1;
            while (!(*ABB_CLK_GEN_CFG_3__ABBCK200K_BGR_DIV_RDY));
            break;
        case CLK_ABBCK200K_AIO:
            *ABB_CLK_GEN_CFG_1__ABBCK200K_AIO_DIV_CHG = 0;
            while (*ABB_CLK_GEN_CFG_3__ABBCK200K_AIO_DIV_RDY);
            *ABB_CLK_GEN_CFG_1__ABBCK200K_AIO_DIV_EN = 1;
            *ABB_CLK_GEN_CFG_1__ABBCK200K_AIO_DIV_SEL = divide_val;
            *ABB_CLK_GEN_CFG_1__ABBCK200K_AIO_DIV_CHG = 1;
            while (!(*ABB_CLK_GEN_CFG_3__ABBCK200K_AIO_DIV_RDY));
            break;
        case CLK_AUD01ADC:
            *ABB_CLK_GEN_CFG_2__AUD01ADC_CLK_DIV_CHG = 0;
            while (*ABB_CLK_GEN_CFG_4__AUD01ADC_CLK_DIV_RDY);
            *ABB_CLK_GEN_CFG_2__AUD01ADC_CLK_DIV_EN = 1;
            *ABB_CLK_GEN_CFG_2__AUD01ADC_CLK_DIV_SEL = divide_val;
            *ABB_CLK_GEN_CFG_2__AUD01ADC_CLK_DIV_CHG = 1;
            while (!(*ABB_CLK_GEN_CFG_4__AUD01ADC_CLK_DIV_RDY));
            break;
        default:
            break;
    }
}

void hal_clock_abb_clk_gen_disable(clk_abb_gen_t abb_clk)
{
    switch (abb_clk) {
        case CLK_ABBCK200K_BGR:
            *ABB_CLK_GEN_CFG_0__ABBCK200K_BGR_DIV_CHG = 0;
            while (*ABB_CLK_GEN_CFG_3__ABBCK200K_BGR_DIV_RDY);
            *ABB_CLK_GEN_CFG_0__ABBCK200K_BGR_DIV_EN = 0;
            break;
        case CLK_ABBCK200K_AIO:
            *ABB_CLK_GEN_CFG_1__ABBCK200K_AIO_DIV_CHG = 0;
            while (*ABB_CLK_GEN_CFG_3__ABBCK200K_AIO_DIV_RDY);
            *ABB_CLK_GEN_CFG_1__ABBCK200K_AIO_DIV_EN = 0;
            break;
        case CLK_AUD01ADC:
            *ABB_CLK_GEN_CFG_2__AUD01ADC_CLK_DIV_CHG = 0;
            while (*ABB_CLK_GEN_CFG_4__AUD01ADC_CLK_DIV_RDY);
            *ABB_CLK_GEN_CFG_2__AUD01ADC_CLK_DIV_EN = 0;
            break;
        default:
            break;
    }
}

void lposc_hopping_test(void)
{
    enum {
        LPOSC_HOP_MAX = 0,
        LPOSC_HOP_MID,
        LPOSC_HOP_MIN,
        LPOSC_HOP_CNT
    };

    // lposc_khz and lposc_hs_khz
    uint32_t lposc_khz_k_tbl[2];
    uint32_t lposc_khz_hop_tbl[2][LPOSC_HOP_CNT];

    uint32_t cali_reg_val[LPOSC_HOP_CNT], ft_reg_val[LPOSC_HOP_CNT];
    uint32_t lposc_fhset;
    uint8_t  i;

#ifdef __EXT_BOOTLOADER__
    printk("hop range %d, timer_us %d, jump_code %d\r\n", g_clk_cfg.lposc_hopping_range_x10000, g_clk_cfg.lposc_hopping_timer_us_once, g_clk_cfg.lposc_hopping_jump_code_once);
#endif

    lposc_khz_k_tbl[0] = g_clk_cfg.lposc_khz;
    lposc_khz_k_tbl[1] = hal_clock_get_lposc_hs_khz();
    for(i=0; i<2; i++) {
        lposc_khz_hop_tbl[i][LPOSC_HOP_MAX] = lposc_khz_k_tbl[i];
        lposc_khz_hop_tbl[i][LPOSC_HOP_MID] = (lposc_khz_k_tbl[i] * (10000 - (g_clk_cfg.lposc_hopping_range_x10000 / 2))) / 10000;
        lposc_khz_hop_tbl[i][LPOSC_HOP_MIN] = (lposc_khz_k_tbl[i] * (10000 - g_clk_cfg.lposc_hopping_range_x10000)) / 10000;
    }

    /* Find cali, ft register values for freqs MAX, MID, MIN */
    for(i=0; i<LPOSC_HOP_CNT; i++) {
        lposc_calibrate(lposc_khz_hop_tbl[0][i], lposc_khz_hop_tbl[1][i]); /* retrieve target calibration KHz */
        cali_reg_val[i] = *RTC_LPOSC_CON2__LPOSC_RBANK_CALI;
        ft_reg_val[i] = *RTC_LPOSC_CON2__LPOSC_RBANK_FT;
#ifdef __EXT_BOOTLOADER__
        printk("hop[0][%d] %d, [1][%d] %d, CALI %02X, FT %02X\r\n", i, lposc_khz_hop_tbl[0][i], i, lposc_khz_hop_tbl[1][i], cali_reg_val[i], ft_reg_val[i]);
#endif
    }

    /* ---------------------------------------------------------------------- */
    /* First move the cursor to LPOSC_FRQ FAST */
    lposc_fhset = (cali_reg_val[LPOSC_HOP_MAX] << 5) + ft_reg_val[LPOSC_HOP_MAX];
    *SSC1_CON4__LPOSC_FHSET = lposc_fhset;
    *SSC1_CON0__LPOSC_SFSTR_EN = 1;
    *SSC1_CON1__LPOSC_SFSTR_DTS = 0;    // 3us each time
    *SSC1_CON1__LPOSC_SFSTR_DYS = 3;    // 8 code each time
    (*SSC1_CON4__LPOSC_FREQ_STR) ^= 1;  // Toggle this bit

    hal_gpt_delay_us(330);
    /* Enable the cursor to take over control instead of RG_HFOSC_CALI/FT */
    *SSC1_CON0__LPOSC_FHCTL_EN = 1;

    /* ---------------------------------------------------------------------- */
    /* First move the cursor to LPOSC_FRQ - 4% slowly */
    lposc_fhset = (cali_reg_val[LPOSC_HOP_MID] << 5) + ft_reg_val[LPOSC_HOP_MID];
    *SSC1_CON4__LPOSC_FHSET = lposc_fhset;
    *SSC1_CON0__LPOSC_SFSTR_EN = 1;
    *SSC1_CON1__LPOSC_SFSTR_DTS = 0;    // 3us each time
    *SSC1_CON1__LPOSC_SFSTR_DYS = 2;    // 4 code each time
    (*SSC1_CON4__LPOSC_FREQ_STR) ^= 1;  // Toggle this bit

    hal_gpt_delay_us(80);

    /* ---------------------------------------------------------------------- */
    /* Select hopping upper boundary and lower boundary */
    *SSC1_CON1__LPOSC_FRSSC_DTS = g_clk_cfg.lposc_hopping_timer_us_once - 3;  // ? us each time (3,4,5,6)
    i = 3;
    if(g_clk_cfg.lposc_hopping_jump_code_once < 8) {
        i = g_clk_cfg.lposc_hopping_jump_code_once / 2;
    }
    *SSC1_CON1__LPOSC_FRSSC_DYS = i;  // ? code each time (1,2,4,8)
#ifdef __EXT_BOOTLOADER__
    printk("hop FRSSC_DTS %d, FRSSC_DYS %d\r\n", *SSC1_CON1__LPOSC_FRSSC_DTS, *SSC1_CON1__LPOSC_FRSSC_DYS);
#endif
    *SSC1_CON3__LPOSC_FRSSC_UPLMT = ((cali_reg_val[LPOSC_HOP_MAX] - cali_reg_val[LPOSC_HOP_MID]) << 5) + ft_reg_val[LPOSC_HOP_MAX] - ft_reg_val[LPOSC_HOP_MID];
    *SSC1_CON3__LPOSC_FRSSC_DNLMT = ((cali_reg_val[LPOSC_HOP_MID] - cali_reg_val[LPOSC_HOP_MIN]) << 5) + ft_reg_val[LPOSC_HOP_MID] - ft_reg_val[LPOSC_HOP_MIN];
    *SSC1_CON0__LPOSC_FRSSC_EN = 1;
}

#if !defined(CLOCK_COSIM) && defined(CONFIG_MULTITHREADING)
void lposc_recali_print_kval(void)
{
    clk_prt_info("CALI 0x%02X, FT 0x%02X", 2, *RTC_LPOSC_CON2__LPOSC_RBANK_CALI, *RTC_LPOSC_CON2__LPOSC_RBANK_FT);
}

/* function for LPOSC calibration fine tune (+-1) */
void lposc_recali_fine_tune(bool ft_add_one)
{
    uint32_t ft = *RTC_LPOSC_CON2__LPOSC_RBANK_FT;
    uint32_t cali = *RTC_LPOSC_CON2__LPOSC_RBANK_CALI;
    uint32_t combined_rg_mask = (*RTC_LPOSC_CON2_ADDR) & 0xFFFF0000; /* [13:8] CALI, [4:0] FT */

    if (ft_add_one) {  /* FT +1 */
        if (ft == LPOSC_RG_FT_MAX) {
            ft = 0;
            cali ++;
        }
        else {
            ft ++;
        }
    }
    else {  /* FT -1 */
        if (ft == 0) {
            ft = LPOSC_RG_FT_MAX;
            cali --;
        }
        else {
            ft --;
        }
    }

    /* LPOSC register CALI, FT needs to be written to RG at the same time
     * to avoid abrupt frequency change when both cali, ft fields are changed
     */
    *RTC_LPOSC_CON2_ADDR = combined_rg_mask | (cali << 8) | ft;
}

void lposc_recali_calculate_by_target_lposc(bool short_variation)
{
    uint32_t lposc_variation_data;
    uint32_t lposc_target_khz = hal_clock_get_lposc_d3_khz(); /* AD_HFOSC_D3_CLK */
    float variation = 0.0025f;

    lposc_recali_winset = (uint32_t)(((float)LPOSC_RECALI_EXPECT_FQMTR_DATA * DCXO_KHZ) / lposc_target_khz - 0.5f);
    lposc_recali_target_data = (uint32_t)(((float)(lposc_recali_winset + 1) * lposc_target_khz) / DCXO_KHZ);

#ifdef LPOSC_RECALI_4HQA
    variation = 0.0006f;
#else
    if(short_variation) {
        variation = 0.0006f;
    }
#endif
    lposc_variation_data = (uint32_t)(((float)lposc_recali_target_data + 0.5f) * variation);

    lposc_recali_data_upper_bound = lposc_recali_target_data + lposc_variation_data + 2;
    lposc_recali_data_lower_bound = lposc_recali_target_data - lposc_variation_data - 2;
}

void lposc_recali_check_changing_frq(void)
{
    if(clk_flg.b.lposc_recali_changing_frq) {
        clk_flg.b.lposc_recali_changing_frq = 0;
        clk_prt_info("LPOSC changed to %d KHz done, FQMTR D3 %d KHz", 2, g_clk_cfg.lposc_khz, hal_clock_get_freq_meter(AD_HFOSC_D3_CLK, lposc_recali_winset));
        lposc_recali_calculate_by_target_lposc(false);
        clk_prt_info("winset %d, LB %d, center %d, UB %d", 4, lposc_recali_winset, lposc_recali_data_lower_bound, lposc_recali_target_data, lposc_recali_data_upper_bound);
#ifdef LPOSC_RECALI_4HQA
        lposc_recali_timer_ms = LPOSC_RECALI_HQA_INTERVAL_MS;
#else
        lposc_recali_timer_ms = g_clk_cfg.lposc_re_k_period_ms;
#endif
    }
}

void lposc_recali_in_valid_range_print(uint32_t fqmtr_data)
{
    bool print = false;

#ifdef LPOSC_RECALI_4HQA
    print = true;
#else
    if(clk_flg.b.lposc_recali_changing_frq) {
        print = true;
    }
#endif

    if(!print) {
        lposc_recali_monitor_print_times_ttl ++;
        if(lposc_recali_monitor_print_times_ttl >= lposc_recali_monitor_print_times_max) {
            lposc_recali_monitor_print_times_ttl = 0;
            print = true;
        }
    }
    if(print) {
        clk_prt_info("LPOSC fqmtr_data %d OK, CALI 0x%02X, FT 0x%02X", 3, fqmtr_data, *RTC_LPOSC_CON2__LPOSC_RBANK_CALI, *RTC_LPOSC_CON2__LPOSC_RBANK_FT);
    }
}

void lposc_recali_flow(void)
{
    uint32_t fqmtr_data;
    uint8_t k_times;
    bool k_pass = false;

    for(k_times=0; k_times<LPOSC_RECALI_ROUND_K_TIMES_MAX; k_times++) {
        if(*CLKSQ_CON1__DA_LPOSC_EN) {
            fqmtr_data = hal_clock_freq_meter_data(XO_CK, AD_HFOSC_D3_CLK, lposc_recali_winset);
            if(fqmtr_data < lposc_recali_data_lower_bound) {  /* Too slow */
                lposc_recali_fine_tune(true);
                clk_prt_info("LPOSC fqmtr_data %d < LB %d, K[%d]+: CALI 0x%02X, FT 0x%02X", 5, fqmtr_data, lposc_recali_data_lower_bound, k_times+1, *RTC_LPOSC_CON2__LPOSC_RBANK_CALI, *RTC_LPOSC_CON2__LPOSC_RBANK_FT);
                lposc_recali_monitor_print_times_ttl = lposc_recali_monitor_print_times_max;
            }
            else if(fqmtr_data > lposc_recali_data_upper_bound) {  /* Too fast */
                lposc_recali_fine_tune(false);
                clk_prt_info("LPOSC fqmtr_data %d > UB %d, K[%d]-: CALI 0x%02X, FT 0x%02X", 5, fqmtr_data, lposc_recali_data_upper_bound, k_times+1, *RTC_LPOSC_CON2__LPOSC_RBANK_CALI, *RTC_LPOSC_CON2__LPOSC_RBANK_FT);
                lposc_recali_monitor_print_times_ttl = lposc_recali_monitor_print_times_max;
            }
            else { /* In valid range */
                lposc_recali_in_valid_range_print(fqmtr_data);
                k_pass = true;
                lposc_recali_assert_round_ttl = 0;
                lposc_recali_check_changing_frq();
                break;
            }
        }
        else {
            clk_prt_err("LPOSC not enabled", 0);
            return;
        }
    }

    if(!k_pass) {
        if(*CLKSQ_CON1__DA_LPOSC_EN) {
            /* Result of the last time K */
            fqmtr_data = hal_clock_freq_meter_data(XO_CK, AD_HFOSC_D3_CLK, lposc_recali_winset);
            if(fqmtr_data < lposc_recali_data_lower_bound) {  /* Too slow */
                clk_prt_info("LPOSC fqmtr_data %d < LB %d", 2, fqmtr_data, lposc_recali_data_lower_bound);
            }
            else if(fqmtr_data > lposc_recali_data_upper_bound) {  /* Too fast */
                clk_prt_info("LPOSC fqmtr_data %d > UB %d", 2, fqmtr_data, lposc_recali_data_upper_bound);
            }
            else { /* In valid range */
                lposc_recali_in_valid_range_print(fqmtr_data);
                k_pass = true;
                lposc_recali_assert_round_ttl = 0;
                lposc_recali_check_changing_frq();
            }

            if(!k_pass) {
                lposc_recali_assert_round_ttl ++;
                clk_prt_err("LPOSC K round %d fail", 1, lposc_recali_assert_round_ttl);
                if(lposc_recali_assert_round_ttl == LPOSC_RECALI_ASSERT_ROUND_MAX) {
                    assert(0);
                }
            }
        }
        else {
            clk_prt_err("LPOSC not enabled", 0);
        }
    }
}

void lposc_recali_kwork_handler(struct k_work *work)
{
    UNUSED_PARAMETER(work);

    if(!clk_flg.b.lposc_recali_dump_info_1st_time) {
        clk_flg.b.lposc_recali_dump_info_1st_time = 1;
        hal_clock_dump_info();
        clk_prt_info("LPOSC Info: CALI 0x%02X, FT 0x%02X, winset %d, LB %d, center %d, UB %d, PrnTmsMax %d", 7,
            *RTC_LPOSC_CON2__LPOSC_RBANK_CALI, *RTC_LPOSC_CON2__LPOSC_RBANK_FT, lposc_recali_winset,
            lposc_recali_data_lower_bound, lposc_recali_target_data, lposc_recali_data_upper_bound, lposc_recali_monitor_print_times_max);
    }

    if(*CLKSQ_CON1__DA_LPOSC_EN && clk_flg.b.lposc_recali_timer_active) {
        lposc_recali_flow();

#ifdef LPOSC_RECALI_4HQA
        clk_prt_info("SFC %d kHz", 1, hal_clock_get_freq_meter(hf_fsfc_ck, 10000));
#endif
    }
    if(clk_flg.b.lposc_recali_timer_active) {
        hal_gpt_sw_start_timer_ms(lposc_recali_gpt_timer_handle, lposc_recali_timer_ms, lposc_recali_timer_expiry_fn, NULL);
    }
    //clk_prt_info("AD_HFOSC_HS %d KHz", 1, hal_clock_get_freq_meter(AD_HFOSC_HS, 10000));  /* for test only */
}

void lposc_recali_timer_expiry_fn(void *user_data)
{
    UNUSED_PARAMETER(user_data);

#if IS_ENABLED(CONFIG_AIR_DAEMON_WORKQUEUE_ENABLE)
  #if 1
    air_daemon_wq_work_submit(&lposc_recali_work); /* Submit to daemon work queue */
  #else
    int result = air_daemon_wq_work_submit(&lposc_recali_work); /* Submit to daemon work queue */
    if(result < 0) {
        clk_prt_err("Submit result %d (work queue not stated)", 1, result);
        result = k_work_cancel(&lposc_recali_work);
        clk_prt_info("Cancel result %d", 1, result);
    }
  #endif
#else
  #if 1
    k_work_submit(&lposc_recali_work); /* Submit to system work queue */
  #else
    int result = k_work_submit(&lposc_recali_work); /* Submit to system work queue */
    if(result < 0) {
        clk_prt_err("Submit result %d (work queue not stated)", 1, result);
        result = k_work_cancel(&lposc_recali_work);
        clk_prt_info("Cancel result %d", 1, result);
    }
  #endif
#endif
}

void lposc_recali_init(void)
{
    lposc_recali_calculate_by_target_lposc(false);

#ifdef LPOSC_RECALI_4HQA
    lposc_recali_timer_ms = LPOSC_RECALI_HQA_INTERVAL_MS;
#else
    lposc_recali_timer_ms = g_clk_cfg.lposc_re_k_period_ms;
#endif
    lposc_recali_monitor_print_times_max = LPOSC_RECALI_MONITOR_PRINT_MS_MAX / g_clk_cfg.lposc_re_k_period_ms;

    k_work_init(&lposc_recali_work, lposc_recali_kwork_handler);

    if(HAL_GPT_STATUS_OK == hal_gpt_sw_get_timer(&lposc_recali_gpt_timer_handle)) {
        hal_gpt_sw_start_timer_us(lposc_recali_gpt_timer_handle, LPOSC_RECALI_1ST_INTERVAL_MS*1000, lposc_recali_timer_expiry_fn, NULL);
    }
    clk_flg.b.lposc_recali_timer_active = true;
    clk_flg.b.lposc_recali_initialized = true;
}
#endif /* !CLOCK_COSIM && CONFIG_MULTITHREADING */

void clock_lposc_mux_init(void)
{
    /* Enable and calibrate LPOSC */
    lposc_enable(false);
    lposc_calibrate(g_clk_cfg.lposc_khz, hal_clock_get_lposc_hs_khz());

#ifdef DVT_HOPPING
    g_clk_cfg.lposc_hopping_enable = true;
    //g_clk_cfg.lposc_hopping_range_x10000 = 800;  // 8%
    //g_clk_cfg.lposc_hopping_timer_us_once = 3;
    //g_clk_cfg.lposc_hopping_jump_code_once = 8;
#endif
    if(g_clk_cfg.lposc_hopping_enable) {
        lposc_hopping_test();
    }

    /* Make sure OSC_26M is 26M */
    if(g_clk_cfg.lposc_ls_div == LPOSC_LS_DIV6) {
        clock_enable_resource_before_mux_switch(CLK_OSC_26M_SEL, MUX_OSC_26M_IDX_OSC_LS_D2);
        clock_top_mux_ctrl(CLK_OSC_26M_SEL, MUX_OSC_26M_IDX_OSC_LS_D2);
    }

    hal_clock_mux_init(false);
}

void hal_clock_mux_init(bool IsSrcDBL)
{
    uint8_t idx = 0, mux_id, mux_sel;

    do {
        mux_id = init_clk_mux_tbl[idx].mux_id;
        mux_sel = init_clk_mux_tbl[idx].mux_sel;
        if((IsSrcDBL && (mux_tbl[mux_id].sel[mux_sel].src == MUX_XO_DBL)) ||
           (!IsSrcDBL && (mux_tbl[mux_id].sel[mux_sel].src != MUX_XO_DBL))) {
            clock_enable_resource_before_mux_switch(mux_id, mux_sel);
            clock_top_mux_ctrl(mux_id, mux_sel);
        }
    } while(init_clk_mux_tbl[++idx].mux_id != MUX_ID_DUMMY_END);

    clock_disable_resource_after_mux_switch();
}

/* Alias: hal_clock_dump_info */
void clock_dump_info(void)
{
    hal_clock_dump_cfg();

#ifdef CLOCK_COSIM
    MDM_TM_PRINTF("AD_HFOSCS: HS %d, LS %d, D3_CLK %d, SSC_SYNCK %d - AD_64M_DBB_CK %d - RTC %d",
                   hal_clock_get_freq_meter(AD_HFOSC_HS, 10000), hal_clock_get_freq_meter(AD_HFOSC_LS, 10000), hal_clock_get_freq_meter(AD_HFOSC_D3_CLK, 10000),
                   hal_clock_get_freq_meter(AD_HFOSC_SSC_SYNCK, 10000), hal_clock_get_freq_meter(AD_64M_DBB_CK, 10000), hal_clock_get_freq_meter(rtc_ck, 10000));
    MDM_TM_PRINTF("AD_CLKO_UPLL: TEST_DIG %d, FB %d, REF %d",
                   hal_clock_get_freq_meter(AD_CLKO_UPLL_TEST_DIG, 10000), hal_clock_get_freq_meter(AD_CLKO_UPLL_FB, 10000), hal_clock_get_freq_meter(AD_CLKO_UPLL_REF, 10000));
    MDM_TM_PRINTF("SYS[%d] %d, IBEX[%d] %d, SFC[%d] %d, ESC[%d] %d",
                   clock_mux_cur_sel(CLK_SYS_SEL), hal_clock_get_freq_meter(hf_fsys_ck, 10000),
                   clock_mux_cur_sel(CLK_IBEX_SEL), hal_clock_get_freq_meter(f_fibex_ck, 10000),
                   clock_mux_cur_sel(CLK_SFC_SEL), hal_clock_get_freq_meter(hf_fsfc_ck, 10000),
                   clock_mux_cur_sel(CLK_ESC_SEL), hal_clock_get_freq_meter(f_fesc_ck, 10000));
    MDM_TM_PRINTF("SPI: MST0[%d] %d, MST1[%d] %d, MST2[%d] %d, SLV[%d] %d",
                   clock_mux_cur_sel(CLK_SPIMST0_SEL), hal_clock_get_freq_meter(f_fspimst0_ck, 10000),
                   clock_mux_cur_sel(CLK_SPIMST1_SEL), hal_clock_get_freq_meter(f_fspimst1_ck, 10000),
                   clock_mux_cur_sel(CLK_SPIMST2_SEL), hal_clock_get_freq_meter(f_fspimst2_ck, 10000),
                   clock_mux_cur_sel(CLK_SPISLV_SEL), hal_clock_get_freq_meter(f_fspislv_ck, 10000));
    MDM_TM_PRINTF("USB[%d] %d, I3C[%d] %d, AUD_BUS[%d] %d, AUD_ENG[%d] %d",
                   clock_mux_cur_sel(CLK_USB_SEL), hal_clock_get_freq_meter(f_fusb_ck, 10000),
                   clock_mux_cur_sel(CLK_I3C_SEL), hal_clock_get_freq_meter(hf_fi3c_ck, 10000),
                   clock_mux_cur_sel(CLK_AUD_BUS_SEL), hal_clock_get_freq_meter(f_faud_intbus_ck, 10000),
                   clock_mux_cur_sel(CLK_AUD_ENGINE_SEL), hal_clock_get_freq_meter(f_faud_engine_ck, 10000));
    MDM_TM_PRINTF("BT_HOP[%d] %d, IRTX[%d] %d, SLOW_BUS[%d] %d, OSC_26M[%d] %d",
                   clock_mux_cur_sel(CLK_BT_HOP_SEL), hal_clock_get_freq_meter(f_fbt_hop_ck, 10000),
                   clock_mux_cur_sel(CLK_IRTX_SEL), hal_clock_get_freq_meter(hf_firtx_ck, 10000),
                   clock_mux_cur_sel(CLK_SLOW_BUS_SEL), hal_clock_get_freq_meter(f_fslow_bus_ck, 10000),
                   clock_mux_cur_sel(CLK_OSC_26M_SEL), hal_clock_get_freq_meter(f_fosc_26m_ck, 10000));
    MDM_TM_PRINTF("UART[%d,%d,%d] PWM[%d,%d,%d,%d,%d]",
                   clock_mux_cur_sel(CLK_UART0_SEL), clock_mux_cur_sel(CLK_UART1_SEL), clock_mux_cur_sel(CLK_UART2_SEL),
                   clock_mux_cur_sel(CLK_PWM0_SEL), clock_mux_cur_sel(CLK_PWM1_SEL), clock_mux_cur_sel(CLK_PWM2_SEL),
                   clock_mux_cur_sel(CLK_PWM3_SEL), clock_mux_cur_sel(CLK_PWM4_SEL));
    MDM_TM_PRINTF("GPT[%d], OS_GPT[%d], SEC_GPT[%d], IRRX[%d], DCXO_PWR_CTRL[%d], DCXO_DIG_MACRO[%d], BT_MAC[%d], RGU_32K[%d]",
                   clock_mux_cur_sel(CLK_GPT_BCLK_SEL), clock_mux_cur_sel(CLK_OSGPT_BCLK_SEL), clock_mux_cur_sel(CLK_SEC_GPT_BCLK_SEL),
                   clock_mux_cur_sel(CLK_IRRX_BCLK_SEL), clock_mux_cur_sel(CLK_DCXO_PWR_CTRL_SEL), clock_mux_cur_sel(CLK_DCXO_DIG_MACRO_SEL),
                   clock_mux_cur_sel(CLK_BT_MAC_SEL), clock_mux_cur_sel(CLK_RGU_32K_SEL));

    MDM_TM_PRINTF("PWMck[%d,%d,%d,%d,%d]",
                   hal_clock_is_enabled(HAL_CLOCK_CG_PWM_DMA_0), hal_clock_is_enabled(HAL_CLOCK_CG_PWM_DMA_1), hal_clock_is_enabled(HAL_CLOCK_CG_PWM_2),
                   hal_clock_is_enabled(HAL_CLOCK_CG_PWM_3), hal_clock_is_enabled(HAL_CLOCK_CG_PWM_4));
    MDM_TM_PRINTF("UARTck[%d,%d,%d], DMA[%d,%d,%d]",
                   hal_clock_is_enabled(HAL_CLOCK_CG_UART0), hal_clock_is_enabled(HAL_CLOCK_CG_UART1), hal_clock_is_enabled(HAL_CLOCK_CG_UART2),
                   hal_clock_is_enabled(HAL_CLOCK_CG_UART_DMA0), hal_clock_is_enabled(HAL_CLOCK_CG_UART_DMA1), hal_clock_is_enabled(HAL_CLOCK_CG_UART_DMA2));
    MDM_TM_PRINTF("SPIMck[%d,%d,%d], BUS[%d,%d,%d], SPISckBUS[%d,%d]",
                   hal_clock_is_enabled(HAL_CLOCK_CG_SPIMST0), hal_clock_is_enabled(HAL_CLOCK_CG_SPIMST1), hal_clock_is_enabled(HAL_CLOCK_CG_SPIMST2),
                   hal_clock_is_enabled(HAL_CLOCK_CG_SPIMST0_BUS), hal_clock_is_enabled(HAL_CLOCK_CG_SPIMST1_BUS), hal_clock_is_enabled(HAL_CLOCK_CG_SPIMST2_BUS),
                   hal_clock_is_enabled(HAL_CLOCK_CG_SPISLV), hal_clock_is_enabled(HAL_CLOCK_CG_SPISLV_BUS));
    MDM_TM_PRINTF("I3Cck[%d][%d,%d], DMA[%d,%d]",
                   hal_clock_is_enabled(HAL_CLOCK_CG_I3C), hal_clock_is_enabled(HAL_CLOCK_CG_I3C0), hal_clock_is_enabled(HAL_CLOCK_CG_I3C1),
                   hal_clock_is_enabled(HAL_CLOCK_CG_I3C_DMA0), hal_clock_is_enabled(HAL_CLOCK_CG_I3C_DMA1));
    MDM_TM_PRINTF("SPMck: PCLK[%d], BCLK_CM33[%d], DIV[%d], SYS[%d]",
                   hal_clock_is_enabled(HAL_CLOCK_CG_SPM_PCLK), hal_clock_is_enabled(HAL_CLOCK_CG_SPM_BCLK_CM33), hal_clock_is_enabled(HAL_CLOCK_CG_SPM_DIV),
                   hal_clock_is_enabled(HAL_CLOCK_CG_SPM_SYS));
    MDM_TM_PRINTF("USBck[%d], BUS[%d], DMA[%d] - GPTck[%d], SEC[%d], OS[%d]",
                   hal_clock_is_enabled(HAL_CLOCK_CG_USB), hal_clock_is_enabled(HAL_CLOCK_CG_USB_BUS), hal_clock_is_enabled(HAL_CLOCK_CG_USB_DMA),
                   hal_clock_is_enabled(HAL_CLOCK_CG_GPTIMER), hal_clock_is_enabled(HAL_CLOCK_CG_GPTIMER_SEC), hal_clock_is_enabled(HAL_CLOCK_CG_OSTIMER));
    MDM_TM_PRINTF("SEC_MONck[%d], AO[%d], TOP[%d], SECURITY_AO[%d]",
                   hal_clock_is_enabled(HAL_CLOCK_CG_SEC_MON), hal_clock_is_enabled(HAL_CLOCK_CG_SEC_MON_AO), hal_clock_is_enabled(HAL_CLOCK_CG_SEC_MON_TOP),
                   hal_clock_is_enabled(HAL_CLOCK_CG_SECURITY_AO));
    MDM_TM_PRINTF("OSCck: LS_D2[%d], HS_D2[%d], HS_D4[%d] - IRck: TX[%d], RX[%d], RX_BUS[%d]",
                   hal_clock_is_enabled(HAL_CLOCK_CG_OSC_LS_D2), hal_clock_is_enabled(HAL_CLOCK_CG_OSC_HS_D2), hal_clock_is_enabled(HAL_CLOCK_CG_OSC_HS_D4),
                   hal_clock_is_enabled(HAL_CLOCK_CG_IRTX), hal_clock_is_enabled(HAL_CLOCK_CG_IRRX), hal_clock_is_enabled(HAL_CLOCK_CG_IRRX_BUS));
    MDM_TM_PRINTF("AESOTFck[%d], ESC[%d], CRYPTO[%d] - KEY_SCANck: BCLK[%d], F2M[%d] - FAST_DMAck[%d,%d]",
                   hal_clock_is_enabled(HAL_CLOCK_CG_AESOTF), hal_clock_is_enabled(HAL_CLOCK_CG_AESOTF_ESC), hal_clock_is_enabled(HAL_CLOCK_CG_CRYPTO),
                   hal_clock_is_enabled(HAL_CLOCK_CG_KEY_SCAN_BCLK), hal_clock_is_enabled(HAL_CLOCK_CG_KEY_SCAN_F2M), hal_clock_is_enabled(HAL_CLOCK_CG_FAST_DMA_0),
                   hal_clock_is_enabled(HAL_CLOCK_CG_FAST_DMA_1));
    MDM_TM_PRINTF("BTck: HOP[%d], MAC[%d], MAC_CONN[%d] - AUDck: INTBUS[%d], ENGINE[%d], TEST[%d]",
                   hal_clock_is_enabled(HAL_CLOCK_CG_BT_HOP), hal_clock_is_enabled(HAL_CLOCK_CG_BT_MAC), hal_clock_is_enabled(HAL_CLOCK_CG_BT_MAC_CONN),
                   hal_clock_is_enabled(HAL_CLOCK_CG_AUD_INTBUS), hal_clock_is_enabled(HAL_CLOCK_CG_AUD_ENGINE), hal_clock_is_enabled(HAL_CLOCK_CG_AUD_TEST));
    MDM_TM_PRINTF("BUS_ERRck[%d], AO[%d], TOP[%d] - AUXADCck[%d], SRAM[%d] - CMSYSck: BUS[%d], ROM[%d]",
                   hal_clock_is_enabled(HAL_CLOCK_CG_BUS_ERR), hal_clock_is_enabled(HAL_CLOCK_CG_BUS_ERR_AO), hal_clock_is_enabled(HAL_CLOCK_CG_BUS_ERR_TOP),
                   hal_clock_is_enabled(HAL_CLOCK_CG_AUXADC), hal_clock_is_enabled(HAL_CLOCK_CG_AUXADC_SRAM), hal_clock_is_enabled(HAL_CLOCK_CG_CMSYS_BUS),
                   hal_clock_is_enabled(HAL_CLOCK_CG_CMSYS_ROM));
    MDM_TM_PRINTF("SFCck[%d], ESCck[%d], IBEXck[%d], MEM_BUSck[%d], CONN_BUSck[%d], SEJck[%d], EFUSEck[%d], AIOck[%d]",
                   hal_clock_is_enabled(HAL_CLOCK_CG_SFC), hal_clock_is_enabled(HAL_CLOCK_CG_ESC), hal_clock_is_enabled(HAL_CLOCK_CG_IBEX),
                   hal_clock_is_enabled(HAL_CLOCK_CG_MEM_BUS), hal_clock_is_enabled(HAL_CLOCK_CG_CONN_BUS), hal_clock_is_enabled(HAL_CLOCK_CG_SEJ),
                   hal_clock_is_enabled(HAL_CLOCK_CG_EFUSE), hal_clock_is_enabled(HAL_CLOCK_CG_AIO));
    MDM_TM_PRINTF("CKSYS_DEBUG_DISck[%d], GLB_CON_DEBUG_DISck[%d], ARGB_BCLKck[%d], PMU_1Mck[%d], TRNGck[%d]",
                   hal_clock_is_enabled(HAL_CLOCK_CG_CKSYS_DEBUG_DIS), hal_clock_is_enabled(HAL_CLOCK_CG_GLB_CON_DEBUG_DIS), hal_clock_is_enabled(HAL_CLOCK_CG_ARGB_BCLK),
                   hal_clock_is_enabled(HAL_CLOCK_CG_PMU_1M), hal_clock_is_enabled(HAL_CLOCK_CG_TRNG));
    MDM_TM_PRINTF("PSUEDOck: OSC_26M[%d], DCXO_PWR_CTRL[%d], DCXO_DIG_MACRO[%d], RGU_32K[%d], SLOW_BUS[%d]",
                   hal_clock_is_enabled(HAL_CLOCK_CG_PSUEDO_OSC_26M), hal_clock_is_enabled(HAL_CLOCK_CG_PSEUDO_DCXO_PWR_CTRL), hal_clock_is_enabled(HAL_CLOCK_CG_PSEUDO_DCXO_DIG_MACRO),
                   hal_clock_is_enabled(HAL_CLOCK_CG_PSEUDO_RGU_32K), hal_clock_is_enabled(HAL_CLOCK_CG_PSEUDO_SLOW_BUS));

#else /* !CLOCK_COSIM */
    clk_prt_info("AD_HFOSCS: HS %d, LS %d, D3_CLK %d, SSC_SYNCK %d - AD_64M_DBB_CK %d - RTC %d", 6,
                  hal_clock_get_freq_meter(AD_HFOSC_HS, 10000), hal_clock_get_freq_meter(AD_HFOSC_LS, 10000), hal_clock_get_freq_meter(AD_HFOSC_D3_CLK, 10000),
                  hal_clock_get_freq_meter(AD_HFOSC_SSC_SYNCK, 10000), hal_clock_get_freq_meter(AD_64M_DBB_CK, 10000), hal_clock_get_freq_meter(rtc_ck, 10000));
    clk_prt_info("AD_CLKO_UPLL: TEST_DIG %d, FB %d, REF %d", 3,
                  hal_clock_get_freq_meter(AD_CLKO_UPLL_TEST_DIG, 10000), hal_clock_get_freq_meter(AD_CLKO_UPLL_FB, 10000), hal_clock_get_freq_meter(AD_CLKO_UPLL_REF, 10000));
    clk_prt_info("SYS[%d] %d (dcm_primary_div %d), IBEX[%d] %d, SFC[%d] %d, ESC[%d] %d", 9,
                  clock_mux_cur_sel(CLK_SYS_SEL), hal_clock_get_freq_meter(hf_fsys_ck, 10000), hal_clock_dcm_primary_div_get(),
                  clock_mux_cur_sel(CLK_IBEX_SEL), hal_clock_get_freq_meter(f_fibex_ck, 10000),
                  clock_mux_cur_sel(CLK_SFC_SEL), hal_clock_get_freq_meter(hf_fsfc_ck, 10000),
                  clock_mux_cur_sel(CLK_ESC_SEL), hal_clock_get_freq_meter(f_fesc_ck, 10000));
    clk_prt_info("SPI: MST0[%d] %d, MST1[%d] %d, MST2[%d] %d, SLV[%d] %d", 8,
                  clock_mux_cur_sel(CLK_SPIMST0_SEL), hal_clock_get_freq_meter(f_fspimst0_ck, 10000),
                  clock_mux_cur_sel(CLK_SPIMST1_SEL), hal_clock_get_freq_meter(f_fspimst1_ck, 10000),
                  clock_mux_cur_sel(CLK_SPIMST2_SEL), hal_clock_get_freq_meter(f_fspimst2_ck, 10000),
                  clock_mux_cur_sel(CLK_SPISLV_SEL), hal_clock_get_freq_meter(f_fspislv_ck, 10000));
    clk_prt_info("USB[%d] %d, I3C[%d] %d, AUD_BUS[%d] %d, AUD_ENG[%d] %d", 8,
                  clock_mux_cur_sel(CLK_USB_SEL), hal_clock_get_freq_meter(f_fusb_ck, 10000),
                  clock_mux_cur_sel(CLK_I3C_SEL), hal_clock_get_freq_meter(hf_fi3c_ck, 10000),
                  clock_mux_cur_sel(CLK_AUD_BUS_SEL), hal_clock_get_freq_meter(f_faud_intbus_ck, 10000),
                  clock_mux_cur_sel(CLK_AUD_ENGINE_SEL), hal_clock_get_freq_meter(f_faud_engine_ck, 10000));
    clk_prt_info("BT_HOP[%d] %d, IRTX[%d] %d, SLOW_BUS[%d] %d, OSC_26M[%d] %d", 8,
                  clock_mux_cur_sel(CLK_BT_HOP_SEL), hal_clock_get_freq_meter(f_fbt_hop_ck, 10000),
                  clock_mux_cur_sel(CLK_IRTX_SEL), hal_clock_get_freq_meter(hf_firtx_ck, 10000),
                  clock_mux_cur_sel(CLK_SLOW_BUS_SEL), hal_clock_get_freq_meter(f_fslow_bus_ck, 10000),
                  clock_mux_cur_sel(CLK_OSC_26M_SEL), hal_clock_get_freq_meter(f_fosc_26m_ck, 10000));
    clk_prt_info("UART[%d,%d,%d] PWM[%d,%d,%d,%d,%d]", 8,
                  clock_mux_cur_sel(CLK_UART0_SEL), clock_mux_cur_sel(CLK_UART1_SEL), clock_mux_cur_sel(CLK_UART2_SEL),
                  clock_mux_cur_sel(CLK_PWM0_SEL), clock_mux_cur_sel(CLK_PWM1_SEL), clock_mux_cur_sel(CLK_PWM2_SEL),
                  clock_mux_cur_sel(CLK_PWM3_SEL), clock_mux_cur_sel(CLK_PWM4_SEL));
    clk_prt_info("GPT[%d], OS_GPT[%d], SEC_GPT[%d], IRRX[%d], DCXO_PWR_CTRL[%d], DCXO_DIG_MACRO[%d], BT_MAC[%d], RGU_32K[%d]", 8,
                  clock_mux_cur_sel(CLK_GPT_BCLK_SEL), clock_mux_cur_sel(CLK_OSGPT_BCLK_SEL), clock_mux_cur_sel(CLK_SEC_GPT_BCLK_SEL),
                  clock_mux_cur_sel(CLK_IRRX_BCLK_SEL), clock_mux_cur_sel(CLK_DCXO_PWR_CTRL_SEL), clock_mux_cur_sel(CLK_DCXO_DIG_MACRO_SEL),
                  clock_mux_cur_sel(CLK_BT_MAC_SEL), clock_mux_cur_sel(CLK_RGU_32K_SEL));

    clk_prt_info("PWMck[%d,%d,%d,%d,%d]", 5,
                  hal_clock_is_enabled(HAL_CLOCK_CG_PWM_DMA_0), hal_clock_is_enabled(HAL_CLOCK_CG_PWM_DMA_1), hal_clock_is_enabled(HAL_CLOCK_CG_PWM_2),
                  hal_clock_is_enabled(HAL_CLOCK_CG_PWM_3), hal_clock_is_enabled(HAL_CLOCK_CG_PWM_4));
    clk_prt_info("UARTck[%d,%d,%d], DMA[%d,%d,%d]", 6,
                  hal_clock_is_enabled(HAL_CLOCK_CG_UART0), hal_clock_is_enabled(HAL_CLOCK_CG_UART1), hal_clock_is_enabled(HAL_CLOCK_CG_UART2),
                  hal_clock_is_enabled(HAL_CLOCK_CG_UART_DMA0), hal_clock_is_enabled(HAL_CLOCK_CG_UART_DMA1), hal_clock_is_enabled(HAL_CLOCK_CG_UART_DMA2));
    clk_prt_info("SPIMck[%d,%d,%d], BUS[%d,%d,%d], SPISckBUS[%d,%d]", 8,
                  hal_clock_is_enabled(HAL_CLOCK_CG_SPIMST0), hal_clock_is_enabled(HAL_CLOCK_CG_SPIMST1), hal_clock_is_enabled(HAL_CLOCK_CG_SPIMST2),
                  hal_clock_is_enabled(HAL_CLOCK_CG_SPIMST0_BUS), hal_clock_is_enabled(HAL_CLOCK_CG_SPIMST1_BUS), hal_clock_is_enabled(HAL_CLOCK_CG_SPIMST2_BUS),
                  hal_clock_is_enabled(HAL_CLOCK_CG_SPISLV), hal_clock_is_enabled(HAL_CLOCK_CG_SPISLV_BUS));
    clk_prt_info("I3Cck[%d][%d,%d], DMA[%d,%d]", 5,
                  hal_clock_is_enabled(HAL_CLOCK_CG_I3C), hal_clock_is_enabled(HAL_CLOCK_CG_I3C0), hal_clock_is_enabled(HAL_CLOCK_CG_I3C1),
                  hal_clock_is_enabled(HAL_CLOCK_CG_I3C_DMA0), hal_clock_is_enabled(HAL_CLOCK_CG_I3C_DMA1));
    clk_prt_info("SPMck: PCLK[%d], BCLK_CM33[%d], DIV[%d], SYS[%d]", 4,
                  hal_clock_is_enabled(HAL_CLOCK_CG_SPM_PCLK), hal_clock_is_enabled(HAL_CLOCK_CG_SPM_BCLK_CM33), hal_clock_is_enabled(HAL_CLOCK_CG_SPM_DIV),
                  hal_clock_is_enabled(HAL_CLOCK_CG_SPM_SYS));
    clk_prt_info("USBck[%d], BUS[%d], DMA[%d] - GPTck[%d], SEC[%d], OS[%d]", 6,
                  hal_clock_is_enabled(HAL_CLOCK_CG_USB), hal_clock_is_enabled(HAL_CLOCK_CG_USB_BUS), hal_clock_is_enabled(HAL_CLOCK_CG_USB_DMA),
                  hal_clock_is_enabled(HAL_CLOCK_CG_GPTIMER), hal_clock_is_enabled(HAL_CLOCK_CG_GPTIMER_SEC), hal_clock_is_enabled(HAL_CLOCK_CG_OSTIMER));
    clk_prt_info("SEC_MONck[%d], AO[%d], TOP[%d], SECURITY_AO[%d]", 4,
                  hal_clock_is_enabled(HAL_CLOCK_CG_SEC_MON), hal_clock_is_enabled(HAL_CLOCK_CG_SEC_MON_AO), hal_clock_is_enabled(HAL_CLOCK_CG_SEC_MON_TOP),
                  hal_clock_is_enabled(HAL_CLOCK_CG_SECURITY_AO));
    clk_prt_info("OSCck: LS_D2[%d], HS_D2[%d], HS_D4[%d] - IRck: TX[%d], RX[%d], RX_BUS[%d]", 6,
                  hal_clock_is_enabled(HAL_CLOCK_CG_OSC_LS_D2), hal_clock_is_enabled(HAL_CLOCK_CG_OSC_HS_D2), hal_clock_is_enabled(HAL_CLOCK_CG_OSC_HS_D4),
                  hal_clock_is_enabled(HAL_CLOCK_CG_IRTX), hal_clock_is_enabled(HAL_CLOCK_CG_IRRX), hal_clock_is_enabled(HAL_CLOCK_CG_IRRX_BUS));
    clk_prt_info("AESOTFck[%d], ESC[%d], CRYPTO[%d] - KEY_SCANck: BCLK[%d], F2M[%d] - FAST_DMAck[%d,%d]", 7,
                  hal_clock_is_enabled(HAL_CLOCK_CG_AESOTF), hal_clock_is_enabled(HAL_CLOCK_CG_AESOTF_ESC), hal_clock_is_enabled(HAL_CLOCK_CG_CRYPTO),
                  hal_clock_is_enabled(HAL_CLOCK_CG_KEY_SCAN_BCLK), hal_clock_is_enabled(HAL_CLOCK_CG_KEY_SCAN_F2M), hal_clock_is_enabled(HAL_CLOCK_CG_FAST_DMA_0),
                  hal_clock_is_enabled(HAL_CLOCK_CG_FAST_DMA_1));
    clk_prt_info("BTck: HOP[%d], MAC[%d], MAC_CONN[%d] - AUDck: INTBUS[%d], ENGINE[%d], TEST[%d]", 6,
                  hal_clock_is_enabled(HAL_CLOCK_CG_BT_HOP), hal_clock_is_enabled(HAL_CLOCK_CG_BT_MAC), hal_clock_is_enabled(HAL_CLOCK_CG_BT_MAC_CONN),
                  hal_clock_is_enabled(HAL_CLOCK_CG_AUD_INTBUS), hal_clock_is_enabled(HAL_CLOCK_CG_AUD_ENGINE), hal_clock_is_enabled(HAL_CLOCK_CG_AUD_TEST));
    clk_prt_info("BUS_ERRck[%d], AO[%d], TOP[%d] - AUXADCck[%d], SRAM[%d] - CMSYSck: BUS[%d], ROM[%d]", 7,
                  hal_clock_is_enabled(HAL_CLOCK_CG_BUS_ERR), hal_clock_is_enabled(HAL_CLOCK_CG_BUS_ERR_AO), hal_clock_is_enabled(HAL_CLOCK_CG_BUS_ERR_TOP),
                  hal_clock_is_enabled(HAL_CLOCK_CG_AUXADC), hal_clock_is_enabled(HAL_CLOCK_CG_AUXADC_SRAM), hal_clock_is_enabled(HAL_CLOCK_CG_CMSYS_BUS),
                  hal_clock_is_enabled(HAL_CLOCK_CG_CMSYS_ROM));
    clk_prt_info("SFCck[%d], ESCck[%d], IBEXck[%d], MEM_BUSck[%d], CONN_BUSck[%d], SEJck[%d], EFUSEck[%d], AIOck[%d]", 8,
                  hal_clock_is_enabled(HAL_CLOCK_CG_SFC), hal_clock_is_enabled(HAL_CLOCK_CG_ESC), hal_clock_is_enabled(HAL_CLOCK_CG_IBEX),
                  hal_clock_is_enabled(HAL_CLOCK_CG_MEM_BUS), hal_clock_is_enabled(HAL_CLOCK_CG_CONN_BUS), hal_clock_is_enabled(HAL_CLOCK_CG_SEJ),
                  hal_clock_is_enabled(HAL_CLOCK_CG_EFUSE), hal_clock_is_enabled(HAL_CLOCK_CG_AIO));
    clk_prt_info("CKSYS_DEBUG_DISck[%d], GLB_CON_DEBUG_DISck[%d], ARGB_BCLKck[%d], PMU_1Mck[%d], TRNGck[%d]", 5,
                  hal_clock_is_enabled(HAL_CLOCK_CG_CKSYS_DEBUG_DIS), hal_clock_is_enabled(HAL_CLOCK_CG_GLB_CON_DEBUG_DIS), hal_clock_is_enabled(HAL_CLOCK_CG_ARGB_BCLK),
                  hal_clock_is_enabled(HAL_CLOCK_CG_PMU_1M), hal_clock_is_enabled(HAL_CLOCK_CG_TRNG));
    clk_prt_info("PSUEDOck: OSC_26M[%d], DCXO_PWR_CTRL[%d], DCXO_DIG_MACRO[%d], RGU_32K[%d], SLOW_BUS[%d]", 5,
                  hal_clock_is_enabled(HAL_CLOCK_CG_PSUEDO_OSC_26M), hal_clock_is_enabled(HAL_CLOCK_CG_PSEUDO_DCXO_PWR_CTRL), hal_clock_is_enabled(HAL_CLOCK_CG_PSEUDO_DCXO_DIG_MACRO),
                  hal_clock_is_enabled(HAL_CLOCK_CG_PSEUDO_RGU_32K), hal_clock_is_enabled(HAL_CLOCK_CG_PSEUDO_SLOW_BUS));
#endif /* !CLOCK_COSIM */
}

#if 0
#ifdef DCXO_DBL64M_RE_K_PERIODICALLY
#define DCXO_DBL64M_RE_K_BM_IBEX          _U8_B0_
#define DCXO_DBL64M_RE_K_BM_USB           _U8_B1_
#define DCXO_DBL64M_RE_K_BM_BT_MAC        _U8_B2_

//#define DCXO_DBL64M_RE_K_MEASURE_BY_GPIO
#ifdef DCXO_DBL64M_RE_K_MEASURE_BY_GPIO
#define DCXO_DBL64M_RE_K_MEASURE_GPIO      6
#endif

ATTR_TEXT_IN_TCM void dcxo_dbl64m_re_k_kwork_handler(struct k_work *work)
{
    UNUSED_PARAMETER(work);

#ifdef DCXO_DBL64M_RE_K_MEASURE_BY_GPIO
    _gpio_set_mode(DCXO_DBL64M_RE_K_MEASURE_GPIO, 0);
    _gpio_set_dir_output(DCXO_DBL64M_RE_K_MEASURE_GPIO);
    _gpio_output(DCXO_DBL64M_RE_K_MEASURE_GPIO, 0);
    hal_clock_enable(HAL_CLOCK_CG_USB);
    hal_clock_bt_mac_mux_set_idx(MUX_BT_MAC_IDX_XO_DBL);
#endif

    uint8_t k_bm = 0;

    if(*(mux_tbl[CLK_IBEX_SEL].p_sel_rg) == MUX_IBEX_IDX_XO_DBL) {
        k_bm |= DCXO_DBL64M_RE_K_BM_IBEX;
    }
    if(hal_clock_is_enabled(HAL_CLOCK_CG_USB) && (*(mux_tbl[CLK_USB_SEL].p_sel_rg) == MUX_USB_IDX_XO_DBL)) {
        k_bm |= DCXO_DBL64M_RE_K_BM_USB;
    }
    if(hal_clock_bt_mac_mux_get_idx() == MUX_BT_MAC_IDX_XO_DBL) {
        k_bm |= DCXO_DBL64M_RE_K_BM_BT_MAC;
    }

    if(k_bm) {
        clk_prt_info("DBL64M RE-K BM 0x%02X", 1, k_bm);
#ifdef DCXO_DBL64M_RE_K_MEASURE_BY_GPIO
        _gpio_output(DCXO_DBL64M_RE_K_MEASURE_GPIO, 1);
#endif
        /* Switch to non-DBL64M clock temporarily */
        if(k_bm & DCXO_DBL64M_RE_K_BM_IBEX) {
            clock_top_mux_ctrl(CLK_IBEX_SEL, MUX_IBEX_IDX_OSC_LS); // 52 MHz
        }
        if(k_bm & DCXO_DBL64M_RE_K_BM_USB) {
            clock_top_mux_ctrl(CLK_USB_SEL, MUX_USB_IDX_OSC_LS); // 52 MHz
        }
        if(k_bm & DCXO_DBL64M_RE_K_BM_BT_MAC) {
            hal_clock_bt_mac_mux_set_idx(MUX_BT_MAC_IDX_XO); // 32 MHz
        }

        *RTC_DCXO_CON4__DBL_64M_EN = 0;
        hal_clock_dcxo_dbl_calibrate();
        *RTC_DCXO_CON4__DBL_64M_EN = 1;

        /* Switch back to DBL64M clock */
        if(k_bm & DCXO_DBL64M_RE_K_BM_IBEX) {
            clock_top_mux_ctrl(CLK_IBEX_SEL, MUX_IBEX_IDX_XO_DBL);
        }
        if(k_bm & DCXO_DBL64M_RE_K_BM_USB) {
            clock_top_mux_ctrl(CLK_USB_SEL, MUX_USB_IDX_XO_DBL);
        }
        if(k_bm & DCXO_DBL64M_RE_K_BM_BT_MAC) {
            hal_clock_bt_mac_mux_set_idx(MUX_BT_MAC_IDX_XO_DBL);
        }
#ifdef DCXO_DBL64M_RE_K_MEASURE_BY_GPIO
        _gpio_output(DCXO_DBL64M_RE_K_MEASURE_GPIO, 0); /* Maximum ~141us when SYS clock 78 MHz */
#endif
    }

    k_timer_start(&dcxo_dbl64m_re_k_timer, K_MSEC(DCXO_DBL64M_RE_K_INTERVAL_MS), Z_TIMEOUT_NO_WAIT);
}

void dcxo_dbl64m_re_k_timer_expiry_fn(struct k_timer *timer)
{
    UNUSED_PARAMETER(timer);

#if IS_ENABLED(CONFIG_AIR_DAEMON_WORKQUEUE_ENABLE)
  #if 1
    air_daemon_wq_work_submit(&dcxo_dbl64m_re_k_work); /* Submit to daemon work queue */
  #else
    int result = air_daemon_wq_work_submit(&dcxo_dbl64m_re_k_work); /* Submit to daemon work queue */
    if(result < 0) {
        clk_prt_err("Submit result %d (work queue not stated)", 1, result);
        result = k_work_cancel(&dcxo_dbl64m_re_k_work);
        clk_prt_info("Cancel result %d", 1, result);
    }
  #endif
#else
  #if 1
    k_work_submit(&dcxo_dbl64m_re_k_work); /* Submit to system work queue */
  #else
    int result = k_work_submit(&dcxo_dbl64m_re_k_work); /* Submit to system work queue */
    if(result < 0) {
        clk_prt_err("Submit result %d (work queue not stated)", 1, result);
        result = k_work_cancel(&dcxo_dbl64m_re_k_work);
        clk_prt_info("Cancel result %d", 1, result);
    }
  #endif
#endif
}

void dcxo_dbl64m_re_k_init(void)
{
    k_work_init(&dcxo_dbl64m_re_k_work, dcxo_dbl64m_re_k_kwork_handler);

    k_timer_init(&dcxo_dbl64m_re_k_timer, dcxo_dbl64m_re_k_timer_expiry_fn, NULL);
    k_timer_start(&dcxo_dbl64m_re_k_timer, K_MSEC(DCXO_DBL64M_RE_K_INTERVAL_MS), Z_TIMEOUT_NO_WAIT);
}
#endif /* DCXO_DBL64M_RE_K_PERIODICALLY */
#endif

void hal_clock_register_infra_ao_backup_restore(void)
{
#ifdef HAL_SLEEP_MANAGER_ENABLED
    ao_backup_format_table_t cksys, cksys_xo, mixedsys_d, cksys_bus, dcxo_cfg;

    cksys.module_base_addr = RM_CKSYS_BASE;
    cksys.module_end_addr = RM_CKSYS_BASE + INFRA_AO_BACKUP_RESTORE_SIZE_CKSYS;
    cksys.module_backup_enable = 1;

    cksys_xo.module_base_addr = RM_CKSYS_XO_CLK_BASE;
    cksys_xo.module_end_addr = RM_CKSYS_XO_CLK_BASE + INFRA_AO_BACKUP_RESTORE_SIZE_CKSYS_XO;
    cksys_xo.module_backup_enable = 1;

    mixedsys_d.module_base_addr = RM_MIXEDSYS_D_BASE;
    mixedsys_d.module_end_addr = RM_MIXEDSYS_D_BASE + INFRA_AO_BACKUP_RESTORE_SIZE_MIXEDSYS_D;
    mixedsys_d.module_backup_enable = 1;

    cksys_bus.module_base_addr = RM_CKSYS_BUS_CLK_BASE;
    cksys_bus.module_end_addr = RM_CKSYS_BUS_CLK_BASE + INFRA_AO_BACKUP_RESTORE_SIZE_CKSYS_BUS;
    cksys_bus.module_backup_enable = 1;

    dcxo_cfg.module_base_addr = RM_DCXO_CFG_BASE + 0x98;       /* DCXO_RG3 */
    dcxo_cfg.module_end_addr = dcxo_cfg.module_base_addr + 4;  /* only 1 RG */
    dcxo_cfg.module_backup_enable = 1;

    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_CKSYS, &cksys);
    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_CKSYS_XO_CLK, &cksys_xo);
    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_MIXED, &mixedsys_d);
    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_CKSYS_BUS_CLK, &cksys_bus);
    sleep_management_register_infra_ao_backup_restore(SLEEP_MANAGEMENT_AO_BACKUP_DCXO_CFG, &dcxo_cfg);
#endif /* HAL_SLEEP_MANAGER_ENABLED */
}

ATTR_TEXT_IN_TCM hal_clock_status_t hal_clock_dcxo_dbl64m_re_k(void)
{
#if !defined(FPGA_ENV) && !defined(__EXT_BOOTLOADER__) && !defined(__EXT_DA__) && !defined(CLOCK_COSIM)
#ifdef HAL_DVFS_MODULE_ENABLED
    if(hal_dvfs_get_cur_vcore() == HAL_DVFS_VCORE_HIGH) {
        return HAL_CLOCK_STATUS_ERROR;
    }
#endif

    if(hal_clock_is_enabled(HAL_CLOCK_CG_USB)) {
        return HAL_CLOCK_STATUS_ERROR;
    }

    /* Critical Section Time: 229us */
    uint32_t irq_mask = 0;
    hal_nvic_save_and_set_interrupt_mask_special(&irq_mask);
    /* ================ Critical Section Start ======================== */

    uint8_t k_bm = 0;

    if(*(mux_tbl[CLK_IBEX_SEL].p_sel_rg) == MUX_IBEX_IDX_XO_DBL) {
        k_bm |= _U8_B0_;
        clock_top_mux_ctrl(CLK_IBEX_SEL, MUX_IBEX_IDX_OSC_LS);
    }

    if(hal_clock_bt_mac_mux_get_idx(false) == MUX_BT_MAC_IDX_XO_DBL) {
        k_bm |= _U8_B1_;
        hal_clock_bt_mac_mux_set_idx(MUX_BT_MAC_IDX_XO, true);
    }

    if(*RTC_DCXO_CON4__DBL_64M_EN) {
        k_bm |= _U8_B2_;
        *RTC_DCXO_CON4__DBL_64M_EN = 0;
    }
    hal_clock_dcxo_dbl_calibrate();  /* must turn off DBL before calibration */
    if(k_bm & _U8_B2_) {
        *RTC_DCXO_CON4__DBL_64M_EN = 1;
    }

    if(k_bm & _U8_B1_) {
        hal_clock_bt_mac_mux_set_idx(MUX_BT_MAC_IDX_XO_DBL, true);
    }

    if(k_bm & _U8_B0_) {
        clock_top_mux_ctrl(CLK_IBEX_SEL, MUX_IBEX_IDX_XO_DBL);
    }

    /* ================ Critical Section End ======================== */
    hal_nvic_restore_interrupt_mask_special(irq_mask);
#endif /* !defined(FPGA_ENV) && !defined(__EXT_BOOTLOADER__) && !defined(__EXT_DA__) && !defined(CLOCK_COSIM) */
    return HAL_CLOCK_STATUS_OK;
}

hal_clock_status_t hal_clock_lposc_recali_ctrl(bool start)
{
#if !defined(FPGA_ENV) && !defined(__EXT_BOOTLOADER__) && !defined(__EXT_DA__) && !defined(CLOCK_COSIM) && defined(CONFIG_MULTITHREADING)
    if(clk_flg.b.lposc_recali_initialized) {
        if(start) {  /* Restart timer of LPOSC in-use K */
            if(!clk_flg.b.lposc_recali_timer_active) {
                clk_prt_info("lposc_recali_timer restart %dms", 1, lposc_recali_timer_ms);
                hal_gpt_sw_start_timer_ms(lposc_recali_gpt_timer_handle, lposc_recali_timer_ms, lposc_recali_timer_expiry_fn, NULL);
                clk_flg.b.lposc_recali_timer_active = true;
            }
        }
        else {  /* Stop timer of LPOSC in-use K */
            if(clk_flg.b.lposc_recali_timer_active) {
                clk_prt_info("lposc_recali_timer stop", 0);
                hal_gpt_sw_stop_timer_ms(lposc_recali_gpt_timer_handle);
                clk_flg.b.lposc_recali_timer_active = false;
            }
        }
    }
    else {
        return HAL_CLOCK_STATUS_UNINITIALIZED;
    }
    return HAL_CLOCK_STATUS_OK;
#else /* !defined(FPGA_ENV) && !defined(__EXT_BOOTLOADER__) && !defined(__EXT_DA__) && !defined(CLOCK_COSIM) && defined(CONFIG_MULTITHREADING) */
    return HAL_CLOCK_STATUS_UNINITIALIZED;
#endif
}

bool hal_clock_test(uint8_t p1, uint32_t p2)
{
    uint8_t p2_byte0 = (uint8_t)p2;
    uint8_t p2_byte1 = (uint8_t)(p2 >> 8);
    bool  blTemp;

    switch(p1)
    {
        case 0x00:  /* Start(1) or Stop(0) LPOSC in-use K by p2 bit0 */
            hal_clock_lposc_recali_ctrl(p2_byte0 & _U8_B0_);
            break;
        case 0x01:  /* Output frequency meter source clock to GPIO 25 */
            hal_clock_lposc_recali_ctrl(false);
            *TOP_DEBUG_CTRL__TOP_DEBUG_CTRL = 6;  // Select cksys_mon_out0[15:0]
            //*TOP_DEBUG_CTRL__TOP_DEBUG_CTRL = 7;  // Select cksys_mon_out1[15:0]
            //clk_prt_info("TOP_DEBUG_CTRL *0x%08X = 0x%04X", 2, RM_TOP_MISC_CFG_BASE+0x0108, *TOP_DEBUG_CTRL__TOP_DEBUG_CTRL);
            clock_physical_cg_ctrl(HAL_CLOCK_CG_CKSYS_DEBUG_DIS, CG_REQUEST_CLEAR);  // Enable Debug monitor
            //clk_prt_info("Clear CG_CKSYS_DEBUG_DIS *0x%08X = 0x%08X", 2, RM_CKSYS_XO_CLK_BASE+0x0B80, _U32_B15_);
            //hal_clock_freq_meter_data(XO_CK, (uint8_t)p2, 10000);  // Choose a source clock -> GPIO clock out
            *CKSYS_TST_SEL_1__TST_SEL_1 = p2_byte0;
            //clk_prt_info("CKSYS_TST_SEL_1__TST_SEL_1 *0x%08X = 0x%08X", 2, RM_CKSYS_BASE+0x0224, *CKSYS_TST_SEL_1__TST_SEL_1);
            _gpio_set_mode(25, GPIO_AUX_FUN_DEBUGMON);  /* cksys_mon_out0[15] or cksys_mon_out1[15]: mon_fqmtr_ck, DEBUGMON15, GPIO 15,25,47 */
            //clk_prt_info("Output frq meter src %d to GPIO 25", 1, (uint8_t)p2);
            /* === Write RG ===
            {0x42010108,0x00000006}
            {0x42040B80,0x00008000}
            {0x42030224,0x00000007}
            {0x420B030C,0x000000F0}
            {0x420B020C,0x000000D0}
            */
            break;
        case 0x02:  /* DCM on/off */
            blTemp = p2_byte1 & _U8_B0_;  // Control DCM on/off by p2 bit8
            if(p2_byte0 >= CLK_DCM_MAX) {  // Control all DCM
                hal_clock_dcm_ctrl_all(blTemp);
                clk_prt_info("dcm_all %d", 1, blTemp);
            }
            else {  // Control single DCM
                if(blTemp) {
                    hal_clock_dcm_enable(p2_byte0);
                }
                else {
                    hal_clock_dcm_disable(p2_byte0);
                }
                clk_prt_info("dcm[%d] %d", 2, p2_byte0, blTemp);
            }
            break;
        case 0x03:  /* Set Connsys RG for BT MAC 32M or 64M by p2 bit0 */
            hal_clock_bt_mac_mux_set_idx(p2_byte0 & _U8_B0_, true);
            break;
        case 0x04:  /* Set TOP DCM Primary divider by p2 bit[5:0] */
            hal_clock_dcm_primary_div_set(p2_byte0 & 0x3F);
            break;

#ifdef CONFIG_MULTITHREADING
        case 0x05:  /* Set LPOSC frequency KHz by p2 */
            clk_prt_info("Set LPOSC KHz %d", 1, p2);
            hal_clock_set_lposc_khz(p2);
            break;
#endif

        default:
            return false;
    }
    return true;
}
#endif /* !FPGA_ENV */

/*****************************************************************************
 * Public API
 *****************************************************************************/
void hal_clock_dump_cfg(void)
{
#ifdef CLOCK_COSIM
    MDM_TM_PRINTF("osc_khz=%d, osc_hs_div=%d, osc_ls_div=%d, osc_hopping_enable=%d, osc_hopping_range_x10000=%d",
                  g_clk_cfg.lposc_khz, g_clk_cfg.lposc_hs_div, g_clk_cfg.lposc_ls_div, g_clk_cfg.lposc_hopping_enable, g_clk_cfg.lposc_hopping_range_x10000);
    MDM_TM_PRINTF("osc_hopping_timer_us_once=%d, osc_hopping_jump_code_once=%d, osc_re_k_periodically_enable=%d, osc_re_k_period_ms=%d, dcm_enable=%d, dvfs_sys_cfg=%d",
                  g_clk_cfg.lposc_hopping_timer_us_once, g_clk_cfg.lposc_hopping_jump_code_once, g_clk_cfg.lposc_re_k_periodically_enable, g_clk_cfg.lposc_re_k_period_ms, g_clk_cfg.dcm_enable, g_clk_cfg.dvfs_sys_cfg);
#else
    clk_prt_info("osc_khz=%d, osc_hs_div=%d, osc_ls_div=%d, osc_hopping_enable=%d, osc_re_k_periodically_enable=%d, osc_re_k_period_ms=%d, dcm_enable=%d, dvfs_sys_cfg=%d", 8,
                  g_clk_cfg.lposc_khz, g_clk_cfg.lposc_hs_div, g_clk_cfg.lposc_ls_div, g_clk_cfg.lposc_hopping_enable,
                  g_clk_cfg.lposc_re_k_periodically_enable, g_clk_cfg.lposc_re_k_period_ms, g_clk_cfg.dcm_enable, g_clk_cfg.dvfs_sys_cfg);
#endif
}

void hal_clock_init_cfg(hal_clk_cfg_t *pt_cfg)
{
    memcpy(&g_clk_cfg, pt_cfg, sizeof(g_clk_cfg));
    hal_clock_init();
}

void hal_clock_all_on(void)
{
    /* All Clock On */
    *XO_PDN_PD_CLRD0__XO_PDN_PD_CLRD0 = 0xFFFFFFFF;
    *XO_PDN_AO_CLRD0__XO_PDN_AO_CLRD0 = 0xFFFFFFFF;
    *XO_PDN_AO_CLRD1__XO_PDN_AO_CLRD1 = 0xFFFFFFFF;
    *XO_PDN_TOP_CLRD0__XO_PDN_TOP_CLRD0 = 0xFFFFFFFF;
    *XO_PDN_TOP_CLRD1__XO_PDN_TOP_CLRD1 = 0xFFFFFFFF;
    *PDN_PD_CLRD0__PDN_PD_CLRD0 = 0xFFFFFFFF;
    *PDN_AO_CLRD0__PDN_AO_CLRD0 = 0xFFFFFFFF;
    *PDN_TOP_CLRD0__PDN_TOP_CLRD0 = 0xFFFFFFFF;
}

hal_clock_status_t hal_clock_init(void)
{
#if defined(FPGA_ENV) || defined(CLOCK_BRINGUP_VER) || defined(CLOCK_COSIM)
    hal_clock_all_on();
#else
    clock_cg_init(); /* Actual CG init settings */
#endif

#ifndef FPGA_ENV
    for(uint8_t i=0; i<PSEUDO_CG_TTL; i++) {
        pseudo_cg_tbl[i] = CG_SET__CLK_OFF; /* initialize non-zero values */
    }
    clk_flg.value = 0;

  #ifdef __EXT_BOOTLOADER__
    #ifndef BRINGUP_BOOTLOADER_RUN_XO
      #ifdef CLK_LPOSC_MUX_INIT_RUN_DFS_HIGH
        g_clk_cfg.dvfs_sys_cfg = AIR_DVFS_SYS_CFG_FIX_HIGH;
      #endif
        clock_lposc_mux_init();
    #endif
  #elif defined(__EXT_DA__)
    g_clk_cfg.dvfs_sys_cfg = AIR_DVFS_SYS_CFG_FIX_HIGH;
    clock_lposc_mux_init();
  #elif defined(CLOCK_COSIM)
    for(uint8_t i=0; i<PSEUDO_MUX_TTL; i++) {
        pseudo_mux_tbl[i] = 0;
    }
    clock_lposc_mux_init();
  #else  /* ------------ mainbin ------------ */
    if(*CLKSQ_CON1__DA_LPOSC_EN == 0) { /* for safety, must run this api once */
        clock_lposc_mux_init();
    }
    if(*SSC1_CON0__LPOSC_FRSSC_EN) {
        g_clk_cfg.lposc_hopping_enable = true; /* LPOSC Hopping should be enabled in Bootloader */
    }

    /* Enable some pseudo CG for safety */
    pseudo_cg_tbl[HAL_CLOCK_CG_PSUEDO_OSC_26M-HAL_CLOCK_CG_PSEUDO_BEGIN] = CG_CLR__CLK_ON; /* for LPOSC LS D2 enable */
    pseudo_cg_tbl[HAL_CLOCK_CG_PSEUDO_SLOW_BUS-HAL_CLOCK_CG_PSEUDO_BEGIN] = CG_CLR__CLK_ON;

    #if !defined(CLOCK_BRINGUP_VER) && !defined(_CLOCK_DVT_) && defined(CONFIG_MULTITHREADING)
      hal_clock_dcm_ctrl_all(g_clk_cfg.dcm_enable);
      if(g_clk_cfg.lposc_re_k_periodically_enable && !g_clk_cfg.lposc_hopping_enable) {
          lposc_recali_init();
      }
    #endif
    //#ifdef DCXO_DBL64M_RE_K_PERIODICALLY
    //  dcxo_dbl64m_re_k_init();
    //#endif
  #endif /* ------------ mainbin ------------ */
#endif /* !FPGA_ENV */
    return HAL_CLOCK_STATUS_OK;
}

#if !defined(FPGA_ENV) && !defined(__EXT_BOOTLOADER__) && !defined(__EXT_DA__) && !defined(CLOCK_COSIM)
/* Some modules related clock(s) must be on when RG restored from extended-sleep (set 0 to force on after restore) */
ATTR_TEXT_IN_TCM static void clock_set_ext_slp_wakup_cg(hal_clock_cg_id clock_id)
{
    // Only check some CGs
    if((clock_id == HAL_CLOCK_CG_SPIMST0) || (clock_id == HAL_CLOCK_CG_SPIMST1) || (clock_id == HAL_CLOCK_CG_SPIMST2)) {
        /* Default All 0xFFFFFFFF */
        uint32_t XO_PDN_AO_WAKUP1 = 0xFFFFFFFF, XO_PDN_TOP_WAKUP0 = 0xFFFFFFFF, PDN_PD_WAKUP0 = 0xFFFFFFFF;

        if(clock_physical_cg_ctrl(HAL_CLOCK_CG_SPIMST0, CG_REQUEST_STATUS) == CG_CLR__CLK_ON) {
            XO_PDN_TOP_WAKUP0 &= ~_U32_B0_;  /* SPIMST0 */
            XO_PDN_AO_WAKUP1 &= ~_U32_B1_;   /* SPIMST0_BUS */
        }
        if(clock_physical_cg_ctrl(HAL_CLOCK_CG_SPIMST1, CG_REQUEST_STATUS) == CG_CLR__CLK_ON) {
            XO_PDN_TOP_WAKUP0 &= ~_U32_B1_;  /* SPIMST1 */
            XO_PDN_AO_WAKUP1 &= ~_U32_B2_;   /* SPIMST1_BUS */
        }
        if(clock_physical_cg_ctrl(HAL_CLOCK_CG_SPIMST2, CG_REQUEST_STATUS) == CG_CLR__CLK_ON) {
            XO_PDN_TOP_WAKUP0 &= ~_U32_B2_;  /* SPIMST2 */
            PDN_PD_WAKUP0 &= ~_U32_B4_;      /* SPIMST2_BUS */
        }

        *XO_PDN_AO_WAKUP1__XO_PDN_AO_WAKUP1 = XO_PDN_AO_WAKUP1;
        *XO_PDN_TOP_WAKUP0__XO_PDN_TOP_WAKUP0 = XO_PDN_TOP_WAKUP0;
        *PDN_PD_WAKUP0__PDN_PD_WAKUP0 = PDN_PD_WAKUP0;
        //clk_prt_info("XO_PDN_AO_WAKUP1 0x%08X, XO_PDN_TOP_WAKUP0 0x%08X, PDN_PD_WAKUP0 0x%08X", 3, *XO_PDN_AO_WAKUP1__XO_PDN_AO_WAKUP1, *XO_PDN_TOP_WAKUP0__XO_PDN_TOP_WAKUP0, *PDN_PD_WAKUP0__PDN_PD_WAKUP0);
    }
}
#endif

ATTR_TEXT_IN_TCM hal_clock_status_t hal_clock_enable(hal_clock_cg_id clock_id)
{
#ifdef FPGA_ENV
    return HAL_CLOCK_STATUS_OK;
#else
    if((clock_id >= HAL_CLOCK_CG_PSEUDO_BEGIN) && (clock_id <= HAL_CLOCK_CG_PSEUDO_END)) {
        pseudo_cg_tbl[clock_id-HAL_CLOCK_CG_PSEUDO_BEGIN] = CG_CLR__CLK_ON;
    }
    else if(clock_id & HAL_CLOCK_CG_PWM_MULTI_CTRL) {
        *XO_PDN_AO_CLRD0__XO_PDN_AO_CLRD0 = clock_id & PWM_CG_MULTI_CTRL_REQUEST_BIT_MASK;
    }
    else {
        hal_clock_status_t status = clock_physical_cg_ctrl(clock_id, CG_REQUEST_CLEAR);
        if(status != HAL_CLOCK_STATUS_OK) {
            return status;
        }
      #if !defined(__EXT_BOOTLOADER__) && !defined(__EXT_DA__) && !defined(CLOCK_COSIM)
        else {
            clock_set_ext_slp_wakup_cg(clock_id);
        }
      #endif
    }

    int32_t clock_mux_idx = clock_check_cg_in_mux(clock_id);
    if(clock_mux_idx >= 0) {
        clk_flg.b.from_clock_enable_to_clock_mux_sel = 1;

        /* Clock on, check if any clock resource needs to be enabled */
        clock_mux_sel_id mux_id = clock_mux_idx;
        clock_mux_sel(mux_id, clock_mux_cur_sel(mux_id));

        clk_flg.b.from_clock_enable_to_clock_mux_sel = 0;
    }
    return HAL_CLOCK_STATUS_OK;
#endif /* !FPGA_ENV */
}

ATTR_TEXT_IN_TCM hal_clock_status_t hal_clock_disable(hal_clock_cg_id clock_id)
{
#ifdef FPGA_ENV
    return HAL_CLOCK_STATUS_OK;
#else
    if((clock_id >= HAL_CLOCK_CG_PSEUDO_BEGIN) && (clock_id <= HAL_CLOCK_CG_PSEUDO_END)) {
        pseudo_cg_tbl[clock_id-HAL_CLOCK_CG_PSEUDO_BEGIN] = CG_SET__CLK_OFF;
    }
    else if(clock_id & HAL_CLOCK_CG_PWM_MULTI_CTRL) {
        *XO_PDN_AO_SETD0__XO_PDN_AO_SETD0 = clock_id & PWM_CG_MULTI_CTRL_REQUEST_BIT_MASK;
    }
    else {
        hal_clock_status_t status = clock_physical_cg_ctrl(clock_id, CG_REQUEST_SET);
        if(status != HAL_CLOCK_STATUS_OK) {
            return status;
        }
      #if !defined(__EXT_BOOTLOADER__) && !defined(__EXT_DA__) && !defined(CLOCK_COSIM)
        else {
            clock_set_ext_slp_wakup_cg(clock_id);
        }
      #endif
    }

    if(clock_check_cg_in_mux(clock_id) >= 0) {
      #if !defined(__EXT_BOOTLOADER__) && !defined(__EXT_DA__) && !defined(CLOCK_COSIM)
        uint32_t irq_mask = 0;
        hal_nvic_save_and_set_interrupt_mask_special(&irq_mask);
        /* ================ Critical Section Start ======================== */
      #endif

        /* Clock off, check if any clock resource needs to be disabled */
        clock_disable_resource_after_mux_switch();

      #if !defined(__EXT_BOOTLOADER__) && !defined(__EXT_DA__) && !defined(CLOCK_COSIM)
        /* ================ Critical Section End ======================== */
        hal_nvic_restore_interrupt_mask_special(irq_mask);
      #endif
    }
    return HAL_CLOCK_STATUS_OK;
#endif /* !FPGA_ENV */
}

bool hal_clock_is_enabled(hal_clock_cg_id clock_id)
{
#if defined(FPGA_ENV) || defined(CLOCK_BRINGUP_VER) || defined(CLOCK_COSIM)
    return true;
#else
    if((clock_id >= HAL_CLOCK_CG_PSEUDO_BEGIN) && (clock_id <= HAL_CLOCK_CG_PSEUDO_END)) {
        return (pseudo_cg_tbl[clock_id-HAL_CLOCK_CG_PSEUDO_BEGIN] == CG_CLR__CLK_ON);
    }
    else {
        if(clock_physical_cg_ctrl(clock_id, CG_REQUEST_STATUS) == CG_CLR__CLK_ON) {
            return true;
        }
    }
    return false;
#endif
}

uint32_t hal_clock_get_cmsys_freq_hz_by_mux_idx(uint8_t mux_idx)
{
#ifdef FPGA_ENV
    UNUSED_PARAMETER(mux_idx);
    return DCXO_HZ;
#else
    uint32_t sys_freq = 0;

    switch(mux_idx) {
        case MUX_SYS_IDX_XO:
            sys_freq = DCXO_HZ;
            break;
        case MUX_SYS_IDX_OSC_26M:
            sys_freq = (g_clk_cfg.lposc_khz * 1000) / 12;
            break;
        case MUX_SYS_IDX_OSC_LS:
            sys_freq = hal_clock_get_lposc_ls_hz();
            break;
        case MUX_SYS_IDX_OSC_HS:
            sys_freq = hal_clock_get_lposc_hs_hz();
            break;
        case MUX_SYS_IDX_OSC_HS_D2:
            sys_freq = hal_clock_get_lposc_hs_hz() / 2;
            break;
        case MUX_SYS_IDX_OSC_D3:
            sys_freq = hal_clock_get_lposc_d3_hz();
            break;
        default:
            break;
    }
    return (sys_freq / hal_clock_dcm_primary_div_get());
#endif
}

/* Alias: hal_clock_get_curr_cpu_freq_hz */
uint32_t get_curr_cpu_freq_hz(void)
{
#ifdef FPGA_ENV
    return DCXO_HZ;
#else
    uint8_t cur_sel = *(mux_tbl[CLK_SYS_SEL].p_sel_rg);
    return hal_clock_get_cmsys_freq_hz_by_mux_idx(cur_sel);
#endif /* !FPGA_ENV */
}

/* Alias: hal_clock_mux_cur_sel */
uint8_t clock_mux_cur_sel(clock_mux_sel_id mux_id)
{
#ifdef FPGA_ENV
    return 0;
#else
    uint8_t cur_sel = 0;

    if(mux_id < TOTAL_MUX_CNT) {
        if(mux_tbl[mux_id].other.mux_type == PSEUDO_MUX) {
            cur_sel = pseudo_mux_tbl[mux_id-CLK_MUX_SEL_PSEUDO_BEGIN];
        }
        else {
            if(mux_id == CLK_BT_MAC_SEL) {
                cur_sel = hal_clock_bt_mac_mux_get_idx(false);
            }
            else {
                cur_sel = *(mux_tbl[mux_id].p_sel_rg);
            }
        }
    }
    else {
        clk_prt_err("clock_mux_cur_sel(%d) INVALID_PARAMETER, Caller 0x%08X", 2, mux_id, (uint32_t)__builtin_return_address(0));
    }
    return cur_sel;
#endif /* !FPGA_ENV */
}

/* Alias: hal_clock_mux_sel */
/* Refer to clk_mux_sel_idx_t for parameter mux_sel */
ATTR_TEXT_IN_TCM hal_clock_status_t clock_mux_sel(clock_mux_sel_id mux_id, uint32_t mux_sel)
{
#ifdef FPGA_ENV
    return HAL_CLOCK_STATUS_OK;
#else
    bool can_print_log = true;

  #ifdef CLOCK_COSIM
    MDM_TM_PRINTF("clock_mux_sel(%d,%d)", mux_id, mux_sel);
  #endif

    if(clk_flg.b.from_clock_enable_to_clock_mux_sel) {  /* from hal_clock_enable, don't print log */
        can_print_log = false;
    }
  #ifndef _CLOCK_DVT_
    else {
        clk_prt_info("clock_mux_sel(%d,%d), Caller 0x%08X", 3, mux_id, mux_sel, (uint32_t)__builtin_return_address(0));
    }
  #endif

    if((mux_id >= TOTAL_MUX_CNT) || (mux_sel >= MUX_SEL_NUM) ||
       ((mux_sel < MUX_SEL_NUM) && (mux_tbl[mux_id].sel[mux_sel].src == MUX_NONE))) {
        if(can_print_log) {
            clk_prt_err("clock_mux_sel(%d,%d) INVALID_PARAM, Caller 0x%08X", 3, mux_id, mux_sel, (uint32_t)__builtin_return_address(0));
        }
        return HAL_CLOCK_STATUS_INVALID_PARAMETER;
    }

  #ifndef _CLOCK_DVT_  /* Need to check if next mux is allowed for switching */
    if(mux_tbl[mux_id].sel[mux_sel].allow == MUX_NOT_ALLOW) {
      #ifdef CLOCK_COSIM
        MDM_TM_STR("MUX_NOT_ALLOW");
      #else
        if(can_print_log) {
            clk_prt_err("clock_mux_sel(%d,%d) NOT_ALLOW, Caller 0x%08X", 3, mux_id, mux_sel, (uint32_t)__builtin_return_address(0));
        }
      #endif
        return HAL_CLOCK_STATUS_INVALID_PARAMETER;
    }
  #endif

  #if !defined(__EXT_BOOTLOADER__) && !defined(__EXT_DA__) && !defined(CLOCK_COSIM)
    uint32_t irq_mask = 0;
    hal_nvic_save_and_set_interrupt_mask_special(&irq_mask);
    /* ================ Critical Section Start ======================== */
  #endif

    clock_enable_resource_before_mux_switch(mux_id, mux_sel);
    clock_top_mux_ctrl(mux_id, mux_sel);
    clock_disable_resource_after_mux_switch();

  #if !defined(__EXT_BOOTLOADER__) && !defined(__EXT_DA__) && !defined(CLOCK_COSIM)
    /* ================ Critical Section End ======================== */
    hal_nvic_restore_interrupt_mask_special(irq_mask);
  #endif

    return HAL_CLOCK_STATUS_OK;
#endif /* !FPGA_ENV */
}

ATTR_TEXT_IN_TCM uint16_t hal_clock_get_vcore_mv(void)
{
    uint8_t rg_val = *(volatile uint8_t *) 0x42108040; /* VCORE_VSEL_NORM */
    uint16_t vcore_mv = rg_val;

    vcore_mv *= 5;    /* 5mv for each code */
    vcore_mv += 540;  /* base mv */
    return vcore_mv;
}

uint32_t hal_clock_freq_meter_data(ref_clock_t ref_clk, hal_src_clock src_clk, uint32_t winset)
{
#ifdef FPGA_ENV
    return 0;
#else
  #if !defined(__EXT_BOOTLOADER__) && !defined(__EXT_DA__) && !defined(CLOCK_COSIM)
    uint32_t irq_mask = 0;
    hal_nvic_save_and_set_interrupt_mask(&irq_mask);
    /* ================ Critical Section Start ======================== */
  #endif

    /* Reset FQMTR history */
    *PLL_ABIST_FQMTR_CON1__FQMTR_EN = 0;
    *PLL_ABIST_FQMTR_CON1__FQMTR_RST = 1;
    *PLL_ABIST_FQMTR_CON1__FQMTR_RST = 0;

    /* Setting FQMTR clock source and timing window */
    uint32_t temp = *CKSYS_TST_SEL_1__TST_SEL_1;
    temp &= 0xFFFF0000; /* only update byte[1:0] */
    temp += ((ref_clk << 8) + src_clk);
    *CKSYS_TST_SEL_1__TST_SEL_1 = temp;
    *PLL_ABIST_FQMTR_CON0__FQMTR_WINSET = winset;

    /* FQMTR support maximum 156M at 0.9V, and 104M at 0.8V */
    *PLL_ABIST_FQMTR_CON2__FQMTR_CLKDIV_EN = 0;
    if(hal_clock_get_vcore_mv() < 850) { /* should be ~0.8v */
        if((src_clk == AD_HFOSC_HS) ||
           ((src_clk == hf_fsys_ck) && (*(mux_tbl[CLK_SYS_SEL].p_sel_rg) == MUX_SYS_IDX_OSC_HS)) ||
           ((src_clk == hf_firtx_ck) && (*(mux_tbl[CLK_IRTX_SEL].p_sel_rg) == MUX_IRTX_IDX_OSC_HS))) {
            *PLL_ABIST_FQMTR_CON2__FQMTR_CLKDIV = 0;   /* 0:div2, 1:div4, 2:div8, 3:div16 */
            *PLL_ABIST_FQMTR_CON2__FQMTR_CLKDIV_EN = 1;
        }
    }

    /* Enable FQMTR */
    *PLL_ABIST_FQMTR_CON1__FQMTR_EN = 1;

  #if !defined(__EXT_BOOTLOADER__) && !defined(__EXT_DA__) && !defined(CLOCK_COSIM)
    /* ================ Critical Section End ======================== */
    hal_nvic_restore_interrupt_mask(irq_mask);
  #endif

    /* Wait FQMTR start (at least 3T ref_clk) */
    uint32_t delay_time = 5;

    /* 1T of 32K = 1 / 32768 = 30.52us, add some tolerance */
    if (ref_clk != XO_CK) {
        delay_time = 200;
    }
    hal_gpt_delay_us(delay_time);

    while(*PLL_ABIST_FQMTR_CON1__PLL_ABIST_FQMTR_CON1 & _U16_B7_);

    temp = *PLL_ABIST_FQMTR_DATA__FQMTR_DATA;

    if(*PLL_ABIST_FQMTR_CON2__FQMTR_CLKDIV_EN) {
        temp <<= 1;  // x 2
    }
    return temp;
#endif /* !FPGA_ENV */
}

/* return source clock KHz by fixed reference clock DCXO */
uint32_t hal_clock_get_freq_meter(hal_src_clock clock_src_id, uint32_t winset)
{
#ifdef FPGA_ENV
    return 0;
#else
    return clock_get_src_freq_khz(clock_src_id, winset);
#endif /* !FPGA_ENV */
}

uint32_t hal_clock_fqmtr_winset_estimate(uint32_t ref_clk_hz, uint32_t src_clk_hz)
{
#ifdef FPGA_ENV
    return 0;
#else
    uint32_t winset;
    /* data 10000: targets fqmtr to give a frequency measurement accuracy of 4/10000 = 0.04% */
    uint32_t data = 10000;
    /* typecasted to 64 bit uint (to avoid multiplication overflow) */
    winset = (((uint64_t)ref_clk_hz) * data) / src_clk_hz;
    winset--;

    /* check winset range (21 bits) for safety */
    if(winset > 2097151) {
        /* data 400: targets fqmtr to give an frequency measurement accuracy of 4/400 = 1% */
        data = 400;
        winset = (((uint64_t)ref_clk_hz) * data) / src_clk_hz;
        winset--;
    }
    return winset;
#endif
}

uint32_t hal_clock_get_freq_from_fqmtr_data(uint32_t ref_clk_freq, uint32_t src_clk_fqmtr_data, uint32_t winset)
{
#ifdef FPGA_ENV
    return 0;
#else
    return (((uint64_t)ref_clk_freq) * src_clk_fqmtr_data) / (winset + 1);
#endif
}

void hal_clock_dcm_ctrl_all(bool enable)
{
#ifdef FPGA_ENV
    UNUSED_PARAMETER(enable);
#else
    for(clk_dcm_t i=0; i<CLK_DCM_MAX; i++) {
        if(enable) {
            hal_clock_dcm_enable(i);
        }
        else {
            hal_clock_dcm_disable(i);
        }
    }
#endif
}

#ifdef CONFIG_MULTITHREADING
hal_clock_status_t hal_clock_set_lposc_khz(uint32_t khz)
{
#ifdef FPGA_ENV
    UNUSED_PARAMETER(khz);
#else
    if(g_clk_cfg.lposc_re_k_periodically_enable && !g_clk_cfg.lposc_hopping_enable && (khz >= 250000) && (khz <= DEFAULT_LPOSC_KHZ)) {
        clk_prt_info("hal_clock_set_lposc_khz %d", 1, khz);
        g_clk_cfg.lposc_khz = khz;
        lposc_recali_calculate_by_target_lposc(true);
        clk_prt_info("winset %d, LB %d, center %d, UB %d", 4, lposc_recali_winset, lposc_recali_data_lower_bound, lposc_recali_target_data, lposc_recali_data_upper_bound);
        lposc_recali_timer_ms = LPOSC_RECALI_CHANGING_INV_MS;
        clk_flg.b.lposc_recali_changing_frq = 1;
        return HAL_CLOCK_STATUS_OK;
    }
    else {
        clk_prt_err("hal_clock_set_lposc_khz fail", 0);
    }
#endif
    return HAL_CLOCK_STATUS_ERROR;
}
#endif /* CONFIG_MULTITHREADING */

ATTR_TEXT_IN_TCM clk_bt_rx_adc_t hal_clock_bt_rx_adc_get(void)
{
#ifdef FPGA_ENV
    return 0;
#else
    return clk_bt_rx_adc;
#endif
}

/* BT RX ADC extra settings in DCXO CFG */
ATTR_TEXT_IN_TCM hal_clock_status_t hal_clock_bt_rx_adc_set(clk_bt_rx_adc_t rx_adc)
{
#ifdef FPGA_ENV
    return HAL_CLOCK_STATUS_OK;
#else
    if(rx_adc >= CLK_BT_RX_ADC_MAX) {
        return HAL_CLOCK_STATUS_INVALID_PARAMETER;
    }

    /* Critical Section Time: 12us */
  #if !defined(__EXT_BOOTLOADER__) && !defined(__EXT_DA__) && !defined(CLOCK_COSIM)
    uint32_t irq_mask = 0;
    hal_nvic_save_and_set_interrupt_mask(&irq_mask);
    /* ================ Critical Section Start ======================== */
  #endif

    clk_bt_rx_adc = rx_adc;
    if(hal_clock_is_enabled(HAL_CLOCK_CG_USB) || (*(mux_tbl[CLK_IBEX_SEL].p_sel_rg) == MUX_IBEX_IDX_XO_DBL)) {
        rx_adc = CLK_BT_RX_ADC_DEFAULT;
    }
    hal_clock_bt_rx_adc_set_rg(rx_adc);

  #if !defined(__EXT_BOOTLOADER__) && !defined(__EXT_DA__) && !defined(CLOCK_COSIM)
    /* ================ Critical Section End ======================== */
    hal_nvic_restore_interrupt_mask(irq_mask);
  #endif
    return HAL_CLOCK_STATUS_OK;
#endif /* !FPGA_ENV */
}

ATTR_TEXT_IN_TCM_RETENTION void hal_clock_sfc_ctrl(bool enable)
{
    if(enable) {
        (*XO_PDN_TOP_CLRD0__XO_PDN_TOP_CLRD0) |= _U32_B17_;
    }
    else {
        (*XO_PDN_TOP_SETD0__XO_PDN_TOP_SETD0) |= _U32_B17_;
    }
}

/*****************************************************************************
 * RACE command
 *****************************************************************************/
#if defined(AIR_RACE_CMD_ENABLE) && !defined(FPGA_ENV)
#include "race_cmd_feature.h"
#ifdef RACE_CLOCK_CMD_ENABLE
#include "race_cmd_clock.h"

/* RACE Clock Sub Command */
enum {
    CLK_SUB_CMD_GET_MUX_IDX = 0,   /* CMD: 05 5A 04 00 C3 02 00 MM               RSP: 05 5B 04 00 C3 02 00 XX          */
    CLK_SUB_CMD_SET_MUX_IDX   = 1, /* CMD: 05 5A 05 00 C3 02 01 MM XX            RSP: 05 5B 04 00 C3 02 01 00/03       */
    CLK_SUB_CMD_GET_CLK_STE   = 2, /* CMD: 05 5A 04 00 C3 02 02 KK               RSP: 05 5B 04 00 C3 02 02 00/01       */
    CLK_SUB_CMD_SET_CLK_STE   = 3, /* CMD: 05 5A 05 00 C3 02 03 KK XX            RSP: 05 5B 04 00 C3 02 03 00/03       */
    CLK_SUB_CMD_METER         = 4, /* CMD: 05 5A 04 00 C3 02 04 SS               RSP: 05 5B 07 00 C3 02 04 XX XX XX XX */
    CLK_SUB_CMD_CLKO          = 5, /* CMD: 05 5A 05 00 C3 02 05 PP SS            RSP: 05 5B 04 00 C3 02 05 00/03       */
//    CLK_SUB_CMD_FREF          = 6, /* CMD: 05 5A 03 00 C3 02 06                  RSP: 05 5B 04 00 C3 02 06 00/02       */

#if 0//def CONFIG_MULTITHREADING
    CLK_SUB_CMD_SET_LPOSC_FRQ = 7, /* CMD: 05 5A 08 00 C3 02 07 PP QQ QQ QQ QQ   RSP: 05 5B 04 00 C3 02 07 00/02       */
#endif

    CLK_SUB_CMD_TEST = 0xFE,       /* CMD: 05 5A 08 00 C3 02 FE XX YY YY YY YY   RSP: 05 5B 04 00 C3 02 FE 00/02       */
    CLK_SUB_CMD_DUMP_LOG = 0xFF    /* CMD: 05 5A 03 00 C3 02 FF                  RSP: 05 5B 04 00 C3 02 FF 00          */
};

void *hal_clock_race_handler(ptr_race_pkt_t pCmdMsg, uint8_t channel_id)
{
    uint8_t *pPayload = pCmdMsg->payload;
    uint8_t  i, bTemp, sub_cmd = pPayload[0];
    bool     data_len_err = false, mem_alloc_fail = false;
    void    *pRtnPayload = NULL;
    uint16_t data_len = pCmdMsg->hdr.length - 2; /* not count RACE ID */
    uint32_t dwTemp;
    hal_clock_status_t clock_status;

    if (data_len) {
        switch (sub_cmd) {
            case CLK_SUB_CMD_GET_MUX_IDX:
                if (data_len >= 2) {
                    bTemp = pPayload[1];
                    race_clk_log_info("CLK_GET_MUX_IDX %d", 1, bTemp);
                    if (bTemp <= TOTAL_MUX_CNT) {
                        pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                            (uint8_t)RACE_TYPE_RESPONSE,
                                                            (uint16_t)RACE_ID_CLOCK,
                                                            (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                            channel_id);
                        if (pRtnPayload) {
                            i = clock_mux_cur_sel(bTemp);
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = i;
                            race_clk_log_info("MUX[%d] IDX %d", 2, bTemp, i);
                        }
                        else {
                            mem_alloc_fail = true;
                        }
                    }
                    else {
                        race_clk_log_err("Invalid MUX ID value", 0);
                    }
                }
                else {
                    data_len_err = true;
                }
                break;
            case CLK_SUB_CMD_SET_MUX_IDX:
                if (data_len >= 3) {
                    bTemp = pPayload[1];
                    i = pPayload[2];
                    race_clk_log_info("CLK_SET_MUX_IDX %d %d", 2, bTemp, i);
                    if ((bTemp < TOTAL_MUX_CNT) && (i < MUX_SEL_NUM)) {
                        pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                            (uint8_t)RACE_TYPE_RESPONSE,
                                                            (uint16_t)RACE_ID_CLOCK,
                                                            (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                            channel_id);
                        if (pRtnPayload) {
                            clock_status = clock_mux_sel(bTemp, i);
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                            if (clock_status == HAL_CLOCK_STATUS_OK) {
                                ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_SUCCESS;
                                race_clk_log_info("MUX[%d] IDX %d", 2, bTemp, clock_mux_cur_sel(bTemp));
                            }
                            else {
                                race_clk_log_err("Set clock mux index fail %d", 1, clock_status);
                                ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_PARAMETER_ERROR;
                            }
                        }
                        else {
                            mem_alloc_fail = true;
                        }
                    }
                    else {
                        race_clk_log_err("Invalid MUX ID/IDX value", 0);
                    }
                }
                else {
                    data_len_err = true;
                }
                break;
            case CLK_SUB_CMD_GET_CLK_STE:
                if (data_len >= 2) {
                    bTemp = pPayload[1];
                    race_clk_log_info("CLK_GET_CLK_STE %d", 1, bTemp);
                    pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                        (uint8_t)RACE_TYPE_RESPONSE,
                                                        (uint16_t)RACE_ID_CLOCK,
                                                        (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                        channel_id);
                    if (pRtnPayload) {
                        i = (uint8_t)hal_clock_is_enabled(bTemp);
                        ((race_clk_common_uint8_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                        ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = i;
                        race_clk_log_info("Clock(%d) %d", 2, bTemp, i);
                    }
                    else {
                        mem_alloc_fail = true;
                    }
                }
                else {
                    data_len_err = true;
                }
                break;
            case CLK_SUB_CMD_SET_CLK_STE:
                if (data_len >= 3) {
                    bTemp = pPayload[1];
                    i = pPayload[2];
                    race_clk_log_info("CLK_SET_CLK_STE %d %d", 2, bTemp, i);
                    pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                        (uint8_t)RACE_TYPE_RESPONSE,
                                                        (uint16_t)RACE_ID_CLOCK,
                                                        (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                        channel_id);
                    if (pRtnPayload) {
                        if (i) {
                            clock_status = hal_clock_enable(bTemp);
                        }
                        else {
                            clock_status = hal_clock_disable(bTemp);
                        }
                        ((race_clk_common_uint8_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                        if (clock_status == HAL_CLOCK_STATUS_OK) {
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_SUCCESS;
                            race_clk_log_info("CLK[%d] %d", 2, bTemp, hal_clock_is_enabled(bTemp));
                        }
                        else {
                            race_clk_log_err("Set clock state fail %d", 1, clock_status);
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_PARAMETER_ERROR;
                        }
                    }
                    else {
                        mem_alloc_fail = true;
                    }
                }
                else {
                    data_len_err = true;
                }
                break;
            case CLK_SUB_CMD_METER:
                if (data_len >= 2) {
                    bTemp = pPayload[1];
                    race_clk_log_info("CLK_METER %d", 1, bTemp);
                    pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                        (uint8_t)RACE_TYPE_RESPONSE,
                                                        (uint16_t)RACE_ID_CLOCK,
                                                        (uint16_t)sizeof(race_clk_common_uint32_val_only_t),
                                                        channel_id);
                    if (pRtnPayload) {
                        dwTemp = clock_get_src_freq_hz(bTemp, 10000);
                        ((race_clk_common_uint32_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                        ((race_clk_common_uint32_val_only_t *)pRtnPayload)->val = dwTemp;
                        race_clk_log_info("Meter(%d) %d", 2, bTemp, dwTemp);
                    }
                    else {
                        mem_alloc_fail = true;
                    }
                }
                else {
                    data_len_err = true;
                }
                break;
            case CLK_SUB_CMD_CLKO:
                if (data_len >= 3) {
                    bTemp = pPayload[1];
                    i = pPayload[2];
                    race_clk_log_info("CLK_CLKO %d %d", 2, bTemp, i);
                    pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                        (uint8_t)RACE_TYPE_RESPONSE,
                                                        (uint16_t)RACE_ID_CLOCK,
                                                        (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                        channel_id);
                    if (pRtnPayload) {
                        ((race_clk_common_uint8_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                      #if 0
                        hal_clock_out_by_gpio(bTemp, i);
                        ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_SUCCESS;
                      #else
                        if (hal_clock_out_by_gpio(bTemp, i)) {
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_SUCCESS;
                        }
                        else {
                            race_clk_log_err("Clock out setting error", 0);
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_PARAMETER_ERROR;
                        }
                      #endif
                    }
                    else {
                        mem_alloc_fail = true;
                    }
                }
                else {
                    data_len_err = true;
                }
                break;

#if 0
            case CLK_SUB_CMD_FREF:
                race_clk_log_info("CLK_FREF", 0);
                pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                    (uint8_t)RACE_TYPE_RESPONSE,
                                                    (uint16_t)RACE_ID_CLOCK,
                                                    (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                    channel_id);
                if (pRtnPayload) {
                    ((race_clk_common_uint32_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                  #if 0
                    ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_SUCCESS;
                    // run FREF output
                  #else
                    ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_NOT_SUPPORT;
                  #endif
                }
                else {
                    mem_alloc_fail = true;
                }
                break;
#endif

#if 0//def CONFIG_MULTITHREADING
            case CLK_SUB_CMD_SET_LPOSC_FRQ:
                if (data_len >= 6) {
                    i = pPayload[1];
                    dwTemp = *(uint32_t *)&pPayload[2];
                    race_clk_log_info("SET_LPOSC_FRQ %d %d", 2, i, dwTemp);
                    pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                        (uint8_t)RACE_TYPE_RESPONSE,
                                                        (uint16_t)RACE_ID_CLOCK,
                                                        (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                        channel_id);
                    if (pRtnPayload) {
                        ((race_clk_common_uint32_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                        if (hal_clock_set_lposc_khz(dwTemp) == HAL_CLOCK_STATUS_OK) {
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_SUCCESS;
                        }
                        else {
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_NOT_SUPPORT;
                        }
                    }
                    else {
                        mem_alloc_fail = true;
                    }
                }
                else {
                    data_len_err = true;
                }
                break;
#endif /* CONFIG_MULTITHREADING */

            case CLK_SUB_CMD_TEST:
                if (data_len >= 6) {
                    i = pPayload[1];
                    dwTemp = *(uint32_t *)&pPayload[2];
                    race_clk_log_info("CLK_TEST 0x%02X 0x%08X", 2, i, dwTemp);
                    pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                        (uint8_t)RACE_TYPE_RESPONSE,
                                                        (uint16_t)RACE_ID_CLOCK,
                                                        (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                        channel_id);
                    if (pRtnPayload) {
                        ((race_clk_common_uint32_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                        if (hal_clock_test(i, dwTemp)) {
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_SUCCESS;
                        }
                        else {
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_NOT_SUPPORT;
                        }
                    }
                    else {
                        mem_alloc_fail = true;
                    }
                }
                else {
                    data_len_err = true;
                }
                break;

            case CLK_SUB_CMD_DUMP_LOG:
                race_clk_log_info("CLK_DUMP_LOG", 0);
                pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                    (uint8_t)RACE_TYPE_RESPONSE,
                                                    (uint16_t)RACE_ID_CLOCK,
                                                    (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                    channel_id);
                if (pRtnPayload) {
                    ((race_clk_common_uint8_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                    ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_SUCCESS;
                    clock_dump_info();
                }
                else {
                    mem_alloc_fail = true;
                }
                break;

            default:
                race_clk_log_err("CLK sub_cmd 0x%02X not supported", 1, sub_cmd);
                break;
        }
    }
    else {
        data_len_err = true;
    }
    if (data_len_err) {
        race_clk_log_err("CLK data_len %d error", 1, data_len);
    }
    if (mem_alloc_fail) {
        race_clk_log_err("CLK mem alloc fail", 0);
    }
    return pRtnPayload;
}
#endif /* RACE_CLOCK_CMD_ENABLE */
#endif /* AIR_RACE_CMD_ENABLE && !FPGA_ENV */

/*****************************************************************************
 * DVT
 *****************************************************************************/
#ifdef _CLOCK_DVT_
#define clk_dvt_log_info(msg, ...)   printk("[CLK_DVT] "msg"\r\n", ##__VA_ARGS__)
// ---------------------------------------------------------------------------
#ifdef DVT_GPIO_TOGGLE
void clk_dvt_GPIO_TOGGLE(void)
{
    clk_dvt_log_info("GPIO_TOGGLE");

    uint8_t  baTestIO[] = { 29, 34, 35, 36, 38, 39 };

    uint8_t  i, pinTtl = (uint8_t)sizeof(baTestIO);
    uint32_t wRunTimesMax = 100000;

    for(i=0; i<pinTtl; i++) {
        _gpio_set_mode(baTestIO[i], 0);
        _gpio_set_dir_output(baTestIO[i]);
    }
    while(wRunTimesMax--)
    {
        for(i=0; i<pinTtl; i++) {
            _gpio_output(baTestIO[i], 1);
        }
        hal_gpt_delay_us(10);

        for(i=0; i<pinTtl; i++) {
            _gpio_output(baTestIO[i], 0);
        }
        hal_gpt_delay_us(10);
    }
}
#endif /* DVT_GPIO_TOGGLE */

// ----------------------------------------------------------------------------
void clk_dvt_get_freq_diff_str(uint32_t freq_correct, uint32_t freq_measure, char *pStr)
{
    if(freq_correct == freq_measure) {
        strcpy(pStr, "0ppm");
    }
    else {
        uint64_t diff, ppm;
        uint32_t _integer;
        uint16_t _decimal;
        char     sign = '-';

        if(freq_measure > freq_correct) {
            diff = (uint64_t)(freq_measure - freq_correct);
            sign = '+';
        }
        else {
            diff = (uint64_t)(freq_correct - freq_measure);
        }
        ppm = diff * 1000000000 / ((uint64_t)freq_correct);

        _integer = (uint32_t)(ppm / 1000);
        _decimal = (uint16_t)(ppm % 1000);
        if((_decimal % 10) >= 5) {
            _decimal += 10;
        }
        _decimal /= 10;

        sprintf(pStr, "%c%u.%02dppm", sign, _integer, (uint8_t)_decimal);
    }
}

/* reture sign char '+' or '-' */
char clk_dvt_get_freq_diff_ppm(uint32_t freq_correct, uint32_t freq_measure, uint32_t *pRtnPpmInteger, uint8_t *pRtnPpmDecimal)
{
    char sign = ' ';

    *pRtnPpmInteger = 0;
    *pRtnPpmDecimal = 0;

    if(freq_correct != freq_measure) {
        uint64_t diff, ppm;
        uint32_t _integer;
        uint16_t _decimal;

        if(freq_measure > freq_correct) {
            diff = (uint64_t)(freq_measure - freq_correct);
            sign = '+';
        }
        else {
            diff = (uint64_t)(freq_correct - freq_measure);
            sign = '-';
        }
        ppm = diff * 1000000000 / ((uint64_t)freq_correct);

        _integer = (uint32_t)(ppm / 1000);
        _decimal = (uint16_t)(ppm % 1000);
        if((_decimal % 10) >= 5) {
            _decimal += 10;
        }
        _decimal /= 10;

        *pRtnPpmInteger = _integer;
        *pRtnPpmDecimal = (uint8_t)_decimal;
    }
    return sign;
}

// ---------------------------------------------------------------------------
#ifdef DVT_FQMTR_SRC_CLK_FIXED_FREQ
struct fqmtr_src_clk_fixed_freq {  /* without MUX */
    char           name[36];
    hal_src_clock  clk_id;
};
const struct fqmtr_src_clk_fixed_freq fqmtr_src_clk_fixed_freq_tbl[] = {
    { .name = "AD_32M_DBB_1P2",     .clk_id = AD_32M_DBB_1P2     },
    { .name = "xo_ck",              .clk_id = xo_ck              },
    { .name = "AD_64M_DBB_CK",      .clk_id = AD_64M_DBB_CK      },
    { .name = "AD_32M_DBB_1P2_",    .clk_id = AD_32M_DBB_1P2_    },
    { .name = "AD_HFOSC_HS",        .clk_id = AD_HFOSC_HS        },
    { .name = "AD_HFOSC_LS",        .clk_id = AD_HFOSC_LS        },
    { .name = "AD_HFOSC_D3_CLK",    .clk_id = AD_HFOSC_D3_CLK    },
    { .name = "AD_HFOSC_SSC_SYNCK", .clk_id = AD_HFOSC_SSC_SYNCK },
    { .name = "rtc_ck",             .clk_id = rtc_ck             },
    { .name = "f_fosc_26m_ck",      .clk_id = f_fosc_26m_ck      },  /* Check if the current selection is 26M */
    { .name = "",                   .clk_id = 0                  }
};

void clk_dvt_FQMTR_SRC_CLK_FIXED_FREQ(void)
{
    clk_dvt_log_info("FQMTR_SRC_CLK_FIXED_FREQ");

    uint8_t  i = 0;
    uint32_t freq, winset, freq_measure;
    //char     disp_buf[16];

    char PpmSign;
    uint8_t PpmDecimal;
    uint32_t PpmInteger;

    do {
        switch(fqmtr_src_clk_fixed_freq_tbl[i].clk_id) {
            case AD_32M_DBB_1P2:
            case xo_ck:
            case AD_32M_DBB_1P2_:
                freq = DCXO_HZ;
                break;
            case AD_64M_DBB_CK:
                freq = DCXO_DBL_HZ;
                break;
            case AD_HFOSC_HS:
                freq = hal_clock_get_lposc_hs_hz();
                break;
            case AD_HFOSC_LS:
                freq = hal_clock_get_lposc_ls_hz();
                break;
            case AD_HFOSC_D3_CLK:
                freq = hal_clock_get_lposc_d3_hz();
                break;
            case AD_HFOSC_SSC_SYNCK:
                freq = (g_clk_cfg.lposc_khz * 1000) / 48;
                break;
            case rtc_ck:
                freq = 32768;
                break;
            case f_fosc_26m_ck:
                freq = (g_clk_cfg.lposc_khz * 1000) / 12;
                break;

            default:
                freq = 0;
                return;
        }
        winset = fqmtr_winset_estimate(freq);
        freq_measure = clock_get_src_freq_hz(fqmtr_src_clk_fixed_freq_tbl[i].clk_id, winset);
        //clk_dvt_get_freq_diff_str(freq, freq_measure, disp_buf);
        //clk_dvt_log_info("%s: Fsrc %lu, winset %lu, freq_measure %lu, %s", fqmtr_src_clk_fixed_freq_tbl[i].name, freq, winset, freq_measure, disp_buf);

        PpmSign = clk_dvt_get_freq_diff_ppm(freq, freq_measure, &PpmInteger, &PpmDecimal);
        switch(fqmtr_src_clk_fixed_freq_tbl[i].clk_id) {
            case AD_32M_DBB_1P2:
                clk_dvt_log_info("AD_32M_DBB_1P2: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                break;
            case xo_ck:
                clk_dvt_log_info("xo_ck: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                break;
            case AD_64M_DBB_CK:
                clk_dvt_log_info("AD_64M_DBB_CK: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                break;
            case AD_32M_DBB_1P2_:
                clk_dvt_log_info("AD_32M_DBB_1P2_: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                break;
            case AD_HFOSC_HS:
                clk_dvt_log_info("AD_HFOSC_HS: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                break;
            case AD_HFOSC_LS:
                clk_dvt_log_info("AD_HFOSC_LS: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                break;
            case AD_HFOSC_D3_CLK:
                clk_dvt_log_info("AD_HFOSC_D3_CLK: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                break;
            case AD_HFOSC_SSC_SYNCK:
                clk_dvt_log_info("AD_HFOSC_SSC_SYNCK: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                break;
            case rtc_ck:
                clk_dvt_log_info("rtc_ck: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                break;
            case f_fosc_26m_ck:
                clk_dvt_log_info("f_fosc_26m_ck: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                break;
            default:
                break;
        }
    } while(fqmtr_src_clk_fixed_freq_tbl[++i].clk_id);
}
#endif /* DVT_FQMTR_SRC_CLK_FIXED_FREQ */

// ----------------------------------------------------------------------------
enum {  /* Clock Source and Divider */
    CSD_XO,
    CSD_XO_HALF,
    CSD_XO_DBL,
    CSD_O_HS,
    CSD_O_HS_D2,
    CSD_O_HS_D4,
    CSD_O_LS,
    CSD_O_LS_D2,
    CSD_O_D3,
    CSD_O_26,
    CSD_O_26_HALF,
    CSD_EOSC,
    CSD_RTC
};

uint32_t clk_dvt_get_csd_hz(uint8_t csd)
{
    uint32_t freq = 0;

    switch(csd) {
        case CSD_XO:
            freq = DCXO_HZ;
            break;
        case CSD_XO_HALF:
            freq = DCXO_HZ / 2;
            break;
        case CSD_XO_DBL:
            freq = DCXO_DBL_HZ;
            break;
        case CSD_O_HS:
            freq = hal_clock_get_lposc_hs_hz();
            break;
        case CSD_O_HS_D2:
            freq = hal_clock_get_lposc_hs_hz() / 2;
            break;
        case CSD_O_HS_D4:
            freq = hal_clock_get_lposc_hs_hz() / 4;
            break;
        case CSD_O_LS:
            freq = hal_clock_get_lposc_ls_hz();
            break;
        case CSD_O_LS_D2:
            freq = hal_clock_get_lposc_ls_hz() / 2;
            break;
        case CSD_O_D3:
            freq = hal_clock_get_lposc_d3_hz();
            break;
        case CSD_O_26:
            freq = (g_clk_cfg.lposc_khz * 1000) / 12;
            break;
        case CSD_O_26_HALF:
            freq = (g_clk_cfg.lposc_khz * 1000) / 24;
            break;
        case CSD_EOSC:
        case CSD_RTC:
            freq = 32768;
            break;

        default:
            break;
    }
    return freq;
}

// ---------------------------------------------------------------------------
#ifdef DVT_FQMTR_SRC_CLK_MUX
struct fqmtr_src_clk_mux {  /* with MUX */
    char              name[36];
    hal_src_clock     clk_id;
    clock_mux_sel_id  mux_id;
    uint8_t           mux_sel;
    uint8_t           csd;  /* Clock Source and Divider */
};

const struct fqmtr_src_clk_mux fqmtr_src_clk_mux_tbl[] = {
    { .name = "hf_fsys_ck[0]XO",           .clk_id = hf_fsys_ck,       .mux_id = CLK_SYS_SEL,        .mux_sel = 0, .csd = CSD_XO         },
    { .name = "hf_fsys_ck[1]O_26",         .clk_id = hf_fsys_ck,       .mux_id = CLK_SYS_SEL,        .mux_sel = 1, .csd = CSD_O_26       },
    { .name = "hf_fsys_ck[2]O_LS",         .clk_id = hf_fsys_ck,       .mux_id = CLK_SYS_SEL,        .mux_sel = 2, .csd = CSD_O_LS       },
    { .name = "hf_fsys_ck[3]O_HS",         .clk_id = hf_fsys_ck,       .mux_id = CLK_SYS_SEL,        .mux_sel = 3, .csd = CSD_O_HS       },
    { .name = "hf_fsys_ck[4]O_HS_D2",      .clk_id = hf_fsys_ck,       .mux_id = CLK_SYS_SEL,        .mux_sel = 4, .csd = CSD_O_HS_D2    },
    { .name = "hf_fsys_ck[5]O_D3",         .clk_id = hf_fsys_ck,       .mux_id = CLK_SYS_SEL,        .mux_sel = 5, .csd = CSD_O_D3       },

    { .name = "f_fibex_ck[0]XO",           .clk_id = f_fibex_ck,       .mux_id = CLK_IBEX_SEL,       .mux_sel = 0, .csd = CSD_XO         },
    { .name = "f_fibex_ck[1]XO_DBL",       .clk_id = f_fibex_ck,       .mux_id = CLK_IBEX_SEL,       .mux_sel = 1, .csd = CSD_XO_DBL     },
    { .name = "f_fibex_ck[2]O_26",         .clk_id = f_fibex_ck,       .mux_id = CLK_IBEX_SEL,       .mux_sel = 2, .csd = CSD_O_26       },
    { .name = "f_fibex_ck[3]O_LS",         .clk_id = f_fibex_ck,       .mux_id = CLK_IBEX_SEL,       .mux_sel = 3, .csd = CSD_O_LS       },

    { .name = "hf_fsfc_ck[0]XO",           .clk_id = hf_fsfc_ck,       .mux_id = CLK_SFC_SEL,        .mux_sel = 0, .csd = CSD_XO         },
    { .name = "hf_fsfc_ck[1]O_26",         .clk_id = hf_fsfc_ck,       .mux_id = CLK_SFC_SEL,        .mux_sel = 1, .csd = CSD_O_26       },
    { .name = "hf_fsfc_ck[3]O_HS_D2",      .clk_id = hf_fsfc_ck,       .mux_id = CLK_SFC_SEL,        .mux_sel = 3, .csd = CSD_O_HS_D2    },
    { .name = "hf_fsfc_ck[4]O_D3",         .clk_id = hf_fsfc_ck,       .mux_id = CLK_SFC_SEL,        .mux_sel = 4, .csd = CSD_O_D3       },

    { .name = "f_fesc_ck[0]XO",            .clk_id = f_fesc_ck,        .mux_id = CLK_ESC_SEL,        .mux_sel = 0, .csd = CSD_XO         },
    { .name = "f_fesc_ck[1]O_26",          .clk_id = f_fesc_ck,        .mux_id = CLK_ESC_SEL,        .mux_sel = 1, .csd = CSD_O_26       },
    { .name = "f_fesc_ck[2]O_HS_D2",       .clk_id = f_fesc_ck,        .mux_id = CLK_ESC_SEL,        .mux_sel = 2, .csd = CSD_O_HS_D2    },
    { .name = "f_fesc_ck[3]O_HS_D4",       .clk_id = f_fesc_ck,        .mux_id = CLK_ESC_SEL,        .mux_sel = 3, .csd = CSD_O_HS_D4    },

    { .name = "f_fspimst0_ck[0]XO",        .clk_id = f_fspimst0_ck,    .mux_id = CLK_SPIMST0_SEL,    .mux_sel = 0, .csd = CSD_XO         },
    { .name = "f_fspimst0_ck[1]O_26",      .clk_id = f_fspimst0_ck,    .mux_id = CLK_SPIMST0_SEL,    .mux_sel = 1, .csd = CSD_O_26       },

    { .name = "f_fspimst1_ck[0]XO",        .clk_id = f_fspimst1_ck,    .mux_id = CLK_SPIMST1_SEL,    .mux_sel = 0, .csd = CSD_XO         },
    { .name = "f_fspimst1_ck[1]O_26",      .clk_id = f_fspimst1_ck,    .mux_id = CLK_SPIMST1_SEL,    .mux_sel = 1, .csd = CSD_O_26       },

    { .name = "f_fspimst2_ck[0]XO",        .clk_id = f_fspimst2_ck,    .mux_id = CLK_SPIMST2_SEL,    .mux_sel = 0, .csd = CSD_XO         },
    { .name = "f_fspimst2_ck[1]O_26",      .clk_id = f_fspimst2_ck,    .mux_id = CLK_SPIMST2_SEL,    .mux_sel = 1, .csd = CSD_O_26       },
    { .name = "f_fspimst2_ck[3]O_HS_D2",   .clk_id = f_fspimst2_ck,    .mux_id = CLK_SPIMST2_SEL,    .mux_sel = 3, .csd = CSD_O_HS_D2    },

    { .name = "f_fspislv_ck[0]XO",         .clk_id = f_fspislv_ck,     .mux_id = CLK_SPISLV_SEL,     .mux_sel = 0, .csd = CSD_XO         },
    { .name = "f_fspislv_ck[1]O_26",       .clk_id = f_fspislv_ck,     .mux_id = CLK_SPISLV_SEL,     .mux_sel = 1, .csd = CSD_O_26       },
    { .name = "f_fspislv_ck[2]O_LS_D2",    .clk_id = f_fspislv_ck,     .mux_id = CLK_SPISLV_SEL,     .mux_sel = 2, .csd = CSD_O_LS_D2    },

    { .name = "f_fusb_ck[0]XO",            .clk_id = f_fusb_ck,        .mux_id = CLK_USB_SEL,        .mux_sel = 0, .csd = CSD_XO         },
    { .name = "f_fusb_ck[1]XO_DBL",        .clk_id = f_fusb_ck,        .mux_id = CLK_USB_SEL,        .mux_sel = 1, .csd = CSD_XO_DBL     },
    { .name = "f_fusb_ck[2]O_26",          .clk_id = f_fusb_ck,        .mux_id = CLK_USB_SEL,        .mux_sel = 2, .csd = CSD_O_26       },
    { .name = "f_fusb_ck[3]O_LS",          .clk_id = f_fusb_ck,        .mux_id = CLK_USB_SEL,        .mux_sel = 3, .csd = CSD_O_LS       },

    { .name = "hf_fi3c_ck[0]XO",           .clk_id = hf_fi3c_ck,       .mux_id = CLK_I3C_SEL,        .mux_sel = 0, .csd = CSD_XO         },
    { .name = "hf_fi3c_ck[1]O_26",         .clk_id = hf_fi3c_ck,       .mux_id = CLK_I3C_SEL,        .mux_sel = 1, .csd = CSD_O_26       },
    { .name = "hf_fi3c_ck[2]O_D3",         .clk_id = hf_fi3c_ck,       .mux_id = CLK_I3C_SEL,        .mux_sel = 2, .csd = CSD_O_D3       },

    { .name = "f_fbt_hop_ck[0]XO",         .clk_id = f_fbt_hop_ck,     .mux_id = CLK_BT_HOP_SEL,     .mux_sel = 0, .csd = CSD_XO         },
    { .name = "f_fbt_hop_ck[1]O_26",       .clk_id = f_fbt_hop_ck,     .mux_id = CLK_BT_HOP_SEL,     .mux_sel = 1, .csd = CSD_O_26       },
    { .name = "f_fbt_hop_ck[3]O_HS_D2",    .clk_id = f_fbt_hop_ck,     .mux_id = CLK_BT_HOP_SEL,     .mux_sel = 3, .csd = CSD_O_HS_D2    },

    { .name = "f_faud_engine_ck[0]XO",     .clk_id = f_faud_engine_ck, .mux_id = CLK_AUD_ENGINE_SEL, .mux_sel = 0, .csd = CSD_XO         },
    { .name = "f_faud_engine_ck[1]O_26",   .clk_id = f_faud_engine_ck, .mux_id = CLK_AUD_ENGINE_SEL, .mux_sel = 1, .csd = CSD_O_26       },

    { .name = "f_faud_intbus_ck[0]XO",     .clk_id = f_faud_intbus_ck, .mux_id = CLK_AUD_BUS_SEL,    .mux_sel = 0, .csd = CSD_XO         },
    { .name = "f_faud_intbus_ck[1]O_26",   .clk_id = f_faud_intbus_ck, .mux_id = CLK_AUD_BUS_SEL,    .mux_sel = 1, .csd = CSD_O_26       },

    { .name = "hf_firtx_ck[0]XO",          .clk_id = hf_firtx_ck,      .mux_id = CLK_IRTX_SEL,       .mux_sel = 0, .csd = CSD_XO         },
    { .name = "hf_firtx_ck[1]O_26",        .clk_id = hf_firtx_ck,      .mux_id = CLK_IRTX_SEL,       .mux_sel = 1, .csd = CSD_O_26       },
    { .name = "hf_firtx_ck[2]O_HS",        .clk_id = hf_firtx_ck,      .mux_id = CLK_IRTX_SEL,       .mux_sel = 2, .csd = CSD_O_HS       },
    { .name = "hf_firtx_ck[3]O_D3",        .clk_id = hf_firtx_ck,      .mux_id = CLK_IRTX_SEL,       .mux_sel = 3, .csd = CSD_O_D3       },

    { .name = "f_fslow_bus_ck[0]XO",       .clk_id = f_fslow_bus_ck,   .mux_id = CLK_SLOW_BUS_SEL,   .mux_sel = 0, .csd = CSD_XO         },
    { .name = "f_fslow_bus_ck[1]O_26",     .clk_id = f_fslow_bus_ck,   .mux_id = CLK_SLOW_BUS_SEL,   .mux_sel = 1, .csd = CSD_O_26       },

    { .name = "f_fosc_26m_ck[0]O_LS",      .clk_id = f_fosc_26m_ck,    .mux_id = CLK_OSC_26M_SEL,    .mux_sel = 0, .csd = CSD_O_LS       },
    { .name = "f_fosc_26m_ck[1]O_LS_D2",   .clk_id = f_fosc_26m_ck,    .mux_id = CLK_OSC_26M_SEL,    .mux_sel = 1, .csd = CSD_O_LS_D2    },

    { .name = "",                          .clk_id = 0,                .mux_id = 0,                  .mux_sel = 0, .csd = 0              }
};

void clk_dvt_FQMTR_SRC_CLK_MUX(void)
{
    clk_dvt_log_info("FQMTR_SRC_CLK_MUX");

    uint8_t  i = 0;
    uint32_t freq, winset, freq_measure;
    //char     disp_buf[16];

    char PpmSign;
    uint8_t PpmDecimal;
    uint32_t PpmInteger;

    do {
        freq = clk_dvt_get_csd_hz(fqmtr_src_clk_mux_tbl[i].csd);
        winset = fqmtr_winset_estimate(freq);
        clock_mux_sel(fqmtr_src_clk_mux_tbl[i].mux_id, fqmtr_src_clk_mux_tbl[i].mux_sel);
        freq_measure = clock_get_src_freq_hz(fqmtr_src_clk_mux_tbl[i].clk_id, winset);
        //clk_dvt_get_freq_diff_str(freq, freq_measure, disp_buf);
        //clk_dvt_log_info("%s: Fsrc %lu, winset %lu, freq_measure %lu, %s", fqmtr_src_clk_mux_tbl[i].name, freq, winset, freq_measure, disp_buf);

        PpmSign = clk_dvt_get_freq_diff_ppm(freq, freq_measure, &PpmInteger, &PpmDecimal);
        switch(fqmtr_src_clk_mux_tbl[i].clk_id) {
            case hf_fsys_ck:
                switch(fqmtr_src_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("hf_fsys_ck[0]XO: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 1:
                        clk_dvt_log_info("hf_fsys_ck[1]O_26: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 2:
                        clk_dvt_log_info("hf_fsys_ck[2]O_LS: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 3:
                        clk_dvt_log_info("hf_fsys_ck[3]O_HS: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 4:
                        clk_dvt_log_info("hf_fsys_ck[4]O_HS_D2: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 5:
                        clk_dvt_log_info("hf_fsys_ck[5]O_D3: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    default:
                        break;
                }
                break;
            case f_fibex_ck:
                switch(fqmtr_src_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("f_fibex_ck[0]XO: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 1:
                        clk_dvt_log_info("f_fibex_ck[1]XO_DBL: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 2:
                        clk_dvt_log_info("f_fibex_ck[2]O_26: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 3:
                        clk_dvt_log_info("f_fibex_ck[3]O_LS: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    default:
                        break;
                }
                break;
            case hf_fsfc_ck:
                switch(fqmtr_src_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("hf_fsfc_ck[0]XO: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 1:
                        clk_dvt_log_info("hf_fsfc_ck[1]O_26: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 3:
                        clk_dvt_log_info("hf_fsfc_ck[3]O_HS_D2: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 4:
                        clk_dvt_log_info("hf_fsfc_ck[4]O_D3: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    default:
                        break;
                }
                break;
            case f_fesc_ck:
                switch(fqmtr_src_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("f_fesc_ck[0]XO: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 1:
                        clk_dvt_log_info("f_fesc_ck[1]O_26: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 2:
                        clk_dvt_log_info("f_fesc_ck[2]O_HS_D2: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 3:
                        clk_dvt_log_info("f_fesc_ck[3]O_HS_D4: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    default:
                        break;
                }
                break;
            case f_fspimst0_ck:
                switch(fqmtr_src_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("f_fspimst0_ck[0]XO: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 1:
                        clk_dvt_log_info("f_fspimst0_ck[1]O_26: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    default:
                        break;
                }
                break;
            case f_fspimst1_ck:
                switch(fqmtr_src_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("f_fspimst1_ck[0]XO: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 1:
                        clk_dvt_log_info("f_fspimst1_ck[1]O_26: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    default:
                        break;
                }
                break;
            case f_fspimst2_ck:
                switch(fqmtr_src_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("f_fspimst2_ck[0]XO: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 1:
                        clk_dvt_log_info("f_fspimst2_ck[1]O_26: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 3:
                        clk_dvt_log_info("f_fspimst2_ck[3]O_HS_D2: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    default:
                        break;
                }
                break;
            case f_fspislv_ck:
                switch(fqmtr_src_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("f_fspislv_ck[0]XO: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 1:
                        clk_dvt_log_info("f_fspislv_ck[1]O_26: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 2:
                        clk_dvt_log_info("f_fspislv_ck[2]O_LS_D2: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    default:
                        break;
                }
                break;
            case f_fusb_ck:
                switch(fqmtr_src_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("f_fusb_ck[0]XO: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 1:
                        clk_dvt_log_info("f_fusb_ck[1]XO_DBL: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 2:
                        clk_dvt_log_info("f_fusb_ck[2]O_26: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 3:
                        clk_dvt_log_info("f_fusb_ck[3]O_LS: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    default:
                        break;
                }
                break;
            case hf_fi3c_ck:
                switch(fqmtr_src_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("hf_fi3c_ck[0]XO: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 1:
                        clk_dvt_log_info("hf_fi3c_ck[1]O_26: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 2:
                        clk_dvt_log_info("hf_fi3c_ck[2]O_D3: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    default:
                        break;
                }
                break;
            case f_fbt_hop_ck:
                switch(fqmtr_src_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("f_fbt_hop_ck[0]XO: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 1:
                        clk_dvt_log_info("f_fbt_hop_ck[1]O_26: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 3:
                        clk_dvt_log_info("f_fbt_hop_ck[3]O_HS_D2: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    default:
                        break;
                }
                break;
            case f_faud_engine_ck:
                switch(fqmtr_src_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("f_faud_engine_ck[0]XO: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 1:
                        clk_dvt_log_info("f_faud_engine_ck[1]O_26: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    default:
                        break;
                }
                break;
            case f_faud_intbus_ck:
                switch(fqmtr_src_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("f_faud_intbus_ck[0]XO: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 1:
                        clk_dvt_log_info("f_faud_intbus_ck[1]O_26: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    default:
                        break;
                }
                break;
            case hf_firtx_ck:
                switch(fqmtr_src_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("hf_firtx_ck[0]XO: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 1:
                        clk_dvt_log_info("hf_firtx_ck[1]O_26: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 2:
                        clk_dvt_log_info("hf_firtx_ck[2]O_HS: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 3:
                        clk_dvt_log_info("hf_firtx_ck[3]O_D3: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    default:
                        break;
                }
                break;
            case f_fslow_bus_ck:
                switch(fqmtr_src_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("f_fslow_bus_ck[0]XO: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 1:
                        clk_dvt_log_info("f_fslow_bus_ck[1]O_26: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    default:
                        break;
                }
                break;
            case f_fosc_26m_ck:
                switch(fqmtr_src_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("f_fosc_26m_ck[0]O_LS: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    case 1:
                        clk_dvt_log_info("f_fosc_26m_ck[1]O_LS_D2: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    } while(fqmtr_src_clk_mux_tbl[++i].clk_id);
}
#endif /* DVT_FQMTR_SRC_CLK_MUX */

// ---------------------------------------------------------------------------
#ifdef DVT_OTHER_CLK_MUX
struct other_clk_mux {  /* No Clock Source defined or PSEUDO_MUX */
    char              name[36];
    clock_mux_sel_id  mux_id;
    uint8_t           mux_sel;
    uint8_t           csd;  /* Clock Source and Divider */
};

const struct other_clk_mux other_clk_mux_tbl[] = {
    { .name = "CLK_GPT_BCLK_SEL[0]XO_HALF",       .mux_id = CLK_GPT_BCLK_SEL,       .mux_sel = 0, .csd = CSD_XO_HALF    },
    { .name = "CLK_GPT_BCLK_SEL[1]O_26_HALF",     .mux_id = CLK_GPT_BCLK_SEL,       .mux_sel = 1, .csd = CSD_O_26_HALF  },

    { .name = "CLK_OSGPT_BCLK_SEL[0]XO_HALF",     .mux_id = CLK_OSGPT_BCLK_SEL,     .mux_sel = 0, .csd = CSD_XO_HALF    },
    { .name = "CLK_OSGPT_BCLK_SEL[1]O_26_HALF",   .mux_id = CLK_OSGPT_BCLK_SEL,     .mux_sel = 1, .csd = CSD_O_26_HALF  },

    { .name = "CLK_SEC_GPT_BCLK_SEL[0]XO_HALF",   .mux_id = CLK_SEC_GPT_BCLK_SEL,   .mux_sel = 0, .csd = CSD_XO_HALF    },
    { .name = "CLK_SEC_GPT_BCLK_SEL[1]O_26_HALF", .mux_id = CLK_SEC_GPT_BCLK_SEL,   .mux_sel = 1, .csd = CSD_O_26_HALF  },

    { .name = "CLK_BT_MAC_SEL[0]XO",              .mux_id = CLK_BT_MAC_SEL,         .mux_sel = 0, .csd = CSD_XO         },
    { .name = "CLK_BT_MAC_SEL[1]XO_DBL",          .mux_id = CLK_BT_MAC_SEL,         .mux_sel = 1, .csd = CSD_XO_DBL     },

    { .name = "CLK_IRRX_BCLK_SEL[0]XO",           .mux_id = CLK_IRRX_BCLK_SEL,      .mux_sel = 0, .csd = CSD_XO         },
    { .name = "CLK_IRRX_BCLK_SEL[1]O_26",         .mux_id = CLK_IRRX_BCLK_SEL,      .mux_sel = 1, .csd = CSD_O_26       },

    { .name = "CLK_RGU_32K_SEL[0]EOSC",           .mux_id = CLK_RGU_32K_SEL,        .mux_sel = 0, .csd = CSD_EOSC       },
    { .name = "CLK_RGU_32K_SEL[1]RTC",            .mux_id = CLK_RGU_32K_SEL,        .mux_sel = 1, .csd = CSD_RTC        },

    { .name = "CLK_DCXO_PWR_CTRL_SEL[0]EOSC",     .mux_id = CLK_DCXO_PWR_CTRL_SEL,  .mux_sel = 0, .csd = CSD_EOSC       },
    { .name = "CLK_DCXO_PWR_CTRL_SEL[1]RTC",      .mux_id = CLK_DCXO_PWR_CTRL_SEL,  .mux_sel = 1, .csd = CSD_RTC        },

    { .name = "CLK_DCXO_DIG_MACRO_SEL[0]EOSC",    .mux_id = CLK_DCXO_DIG_MACRO_SEL, .mux_sel = 0, .csd = CSD_EOSC       },
    { .name = "CLK_DCXO_DIG_MACRO_SEL[1]RTC",     .mux_id = CLK_DCXO_DIG_MACRO_SEL, .mux_sel = 1, .csd = CSD_RTC        },

    { .name = "CLK_UART1_SEL[0]XO",               .mux_id = CLK_UART1_SEL,          .mux_sel = 0, .csd = CSD_XO         },
    { .name = "CLK_UART1_SEL[1]O_26",             .mux_id = CLK_UART1_SEL,          .mux_sel = 1, .csd = CSD_O_26       },

    { .name = "CLK_UART2_SEL[0]XO",               .mux_id = CLK_UART2_SEL,          .mux_sel = 0, .csd = CSD_XO         },
    { .name = "CLK_UART2_SEL[1]O_26",             .mux_id = CLK_UART2_SEL,          .mux_sel = 1, .csd = CSD_O_26       },

    { .name = "CLK_UART0_SEL[1]O_26",             .mux_id = CLK_UART0_SEL,          .mux_sel = 1, .csd = CSD_O_26       },
    { .name = "CLK_UART0_SEL[0]XO",               .mux_id = CLK_UART0_SEL,          .mux_sel = 0, .csd = CSD_XO         },

    { .name = "",                                 .mux_id = 0xFF,                   .mux_sel = 0, .csd = 0              }
};

void clk_dvt_OTHER_CLK_MUX(void)
{
    clk_dvt_log_info("OTHER_CLK_MUX");

    uint32_t freq;
    uint8_t  i = 0;

    do {
        freq = clk_dvt_get_csd_hz(other_clk_mux_tbl[i].csd);
        clock_mux_sel(other_clk_mux_tbl[i].mux_id, other_clk_mux_tbl[i].mux_sel);
        //clk_dvt_log_info("%s: Sel %d, Fsrc %lu", other_clk_mux_tbl[i].name, *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);

        switch(other_clk_mux_tbl[i].mux_id) {
            case CLK_GPT_BCLK_SEL:
                switch(other_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("CLK_GPT_BCLK_SEL[0]XO_HALF: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    case 1:
                        clk_dvt_log_info("CLK_GPT_BCLK_SEL[1]O_26_HALF: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    default:
                        break;
                }
                break;
            case CLK_OSGPT_BCLK_SEL:
                switch(other_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("CLK_OSGPT_BCLK_SEL[0]XO_HALF: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    case 1:
                        clk_dvt_log_info("CLK_OSGPT_BCLK_SEL[1]O_26_HALF: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    default:
                        break;
                }
                break;
            case CLK_SEC_GPT_BCLK_SEL:
                switch(other_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("CLK_SEC_GPT_BCLK_SEL[0]XO_HALF: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    case 1:
                        clk_dvt_log_info("CLK_SEC_GPT_BCLK_SEL[1]O_26_HALF: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    default:
                        break;
                }
                break;
            case CLK_BT_MAC_SEL:
                switch(other_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("CLK_BT_MAC_SEL[0]XO: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    case 1:
                        clk_dvt_log_info("CLK_BT_MAC_SEL[1]XO_DBL: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    default:
                        break;
                }
                break;
            case CLK_IRRX_BCLK_SEL:
                switch(other_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("CLK_IRRX_BCLK_SEL[0]XO: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    case 1:
                        clk_dvt_log_info("CLK_IRRX_BCLK_SEL[1]O_26: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    default:
                        break;
                }
                break;
            case CLK_RGU_32K_SEL:
                switch(other_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("CLK_RGU_32K_SEL[0]EOSC: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    case 1:
                        clk_dvt_log_info("CLK_RGU_32K_SEL[1]RTC: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    default:
                        break;
                }
                break;
            case CLK_DCXO_PWR_CTRL_SEL:
                switch(other_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("CLK_DCXO_PWR_CTRL_SEL[0]EOSC: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    case 1:
                        clk_dvt_log_info("CLK_DCXO_PWR_CTRL_SEL[1]RTC: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    default:
                        break;
                }
                break;
            case CLK_DCXO_DIG_MACRO_SEL:
                switch(other_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("CLK_DCXO_DIG_MACRO_SEL[0]EOSC: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    case 1:
                        clk_dvt_log_info("CLK_DCXO_DIG_MACRO_SEL[1]RTC: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    default:
                        break;
                }
                break;
            case CLK_UART1_SEL:
                switch(other_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("CLK_UART1_SEL[0]XO: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    case 1:
                        clk_dvt_log_info("CLK_UART1_SEL[1]O_26: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    default:
                        break;
                }
                break;
            case CLK_UART2_SEL:
                switch(other_clk_mux_tbl[i].mux_sel) {
                    case 0:
                        clk_dvt_log_info("CLK_UART2_SEL[0]XO: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    case 1:
                        clk_dvt_log_info("CLK_UART2_SEL[1]O_26: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    default:
                        break;
                }
                break;
            case CLK_UART0_SEL:
                switch(other_clk_mux_tbl[i].mux_sel) {
                    case 1:
                        clk_dvt_log_info("CLK_UART0_SEL[1]O_26: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    case 0:
                        clk_dvt_log_info("CLK_UART0_SEL[0]XO: Sel %d, Fsrc %lu", *(mux_tbl[other_clk_mux_tbl[i].mux_id].p_sel_rg), freq);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    } while(other_clk_mux_tbl[++i].mux_id != 0xFF);
}
#endif /* DVT_OTHER_CLK_MUX */

// ---------------------------------------------------------------------------
#ifdef DVT_FQMTR_SRC_CLK_CHOP
void clk_dvt_FQMTR_SRC_CLK_CHOP(void)
{
    clk_dvt_log_info("FQMTR_SRC_CLK_CHOP");

    uint8_t  i;
    uint32_t freq, winset, freq_measure;
    //char     disp_buf[16];
    const uint16_t waStep[3] = { 0, 1023, 2047 };

    char PpmSign;
    uint8_t PpmDecimal;
    uint32_t PpmInteger;

    // Exception if too many
    for(i=0; i<3; i++) {
        hal_clock_chop_ck(true, waStep[i]);  // XO/(2*(SEL+1))

        freq = DCXO_HZ;
        freq /= ((waStep[i]+1)<<1);
        winset = fqmtr_winset_estimate(freq);
        freq_measure = clock_get_src_freq_hz(f_chop_ck, winset);
        //clk_dvt_get_freq_diff_str(freq, freq_measure, disp_buf);

        //clk_dvt_log_info("f_chop_ck[%u]: Fsrc %lu, winset %lu, freq_measure %lu, %s", waStep[i], freq, winset, freq_measure, disp_buf);

        PpmSign = clk_dvt_get_freq_diff_ppm(freq, freq_measure, &PpmInteger, &PpmDecimal);
        clk_dvt_log_info("f_chop_ck[%u]: Fsrc %lu, winset %lu, freq_measure %lu, %c%u.%02dppm", waStep[i], freq, winset, freq_measure, PpmSign, PpmInteger, PpmDecimal);
    }
    hal_clock_chop_ck(false, 0);
}
#endif /* DVT_FQMTR_SRC_CLK_CHOP */

// ---------------------------------------------------------------------------
#ifdef DVT_CLKO
void clk_dvt_CLKO(void)
{
    clk_dvt_log_info("CLKO");

    /* GPIO with CLKO: 6, 17, 18 */
#if 0
    hal_clock_out_by_gpio(6, 1);   /* f_frtc_clkout_ck */
    hal_clock_out_by_gpio(17, 2);  /* f_fxo_ck         */
    hal_clock_out_by_gpio(18, 3);  /* f_fxo_d2_ck      */
#endif
#if 0
    hal_clock_out_by_gpio(6, 4);   /* f_fosc_26m_ck    */
    hal_clock_out_by_gpio(17, 5);  /* f_fosc_13m_ck    */
    hal_clock_out_by_gpio(18, 6);  /* f_fosc_ls_ck     */
#endif
#if 1
    hal_clock_out_by_gpio(6, 7);   /* f_fosc_hs_d4_ck   */

    uint32_t freq = DCXO_HZ;
    uint8_t i = 0; /* XO / (2x(i+1))*/
    hal_clock_chop_ck(true, i);    /* set chop as XO/2  */
    freq /= ((i+1)<<1);
    uint32_t winset = fqmtr_winset_estimate(freq);
    uint32_t freq_measure = clock_get_src_freq_hz(f_chop_ck, winset);
    clk_dvt_log_info("f_chop_ck[%d]: Fsrc %lu, winset %lu, freq_measure %lu", i, freq, winset, freq_measure);
    hal_clock_out_by_gpio(17, 8);  /* f_chop_ck         */
#endif
}
#endif /* DVT_CLKO */

// ---------------------------------------------------------------------------
#ifdef DVT_DCM
void clk_dvt_DCM(void)
{
    clk_dvt_log_info("DCM");

    /* GPIO with CLKO: 6, 17, 18

     CLKO Select              Active(MHz)    DCM(MHz)   Idle Signal    cksys_mon_out1[15:0]   Idle GPIO      Note
    --------------------------------------------------------------------------------------------------------------------------
      15  cm_ck_div4            fcm/4       Active/64   cm_ck_idle      bit 1  (DEBUGMON1)     1,30,33
      14  tcm_ck_hclk_ck        fsys/2          0       tcm_ck_idle     bit 5  (DEBUGMON3)     5,28,37
      13  f_fbt_mac_mclk_ck     fbt_mac/2   Active/32   bt_mac_ck_idle  bit 3  (DEBUGMON5)     3,26,35
      12  f_fslow_bus_hclk_ck   fslow_bus/2     0       xo_clk_idle     bit 13 (DEBUGMON13)    13,23,45
      11  hf_fbus_hclk_ck       fsys/2          0       bus_clk_idle    bit 11 (DEBUGMON11)    11,21,43
      10  hf_fesc_phy_hclk_ck   fesc/2          0       esc_idle        bit 9  (DEBUGMON9)     9,19,41
       9  hf_fsfc_phy_hclk_ck   fsfc/2          0       sfc_idle        bit 7  (DEBUGMON7)     7,17,39
    */

    hal_clock_dcm_ctrl_all(true);
    *TOP_DEBUG_CTRL__TOP_DEBUG_CTRL = 7;  // Select cksys_mon_out1[15:0]
    clk_dvt_log_info("TOP_DEBUG_CTRL *0x%08X = 0x%04X", RM_TOP_MISC_CFG_BASE+0x0108, *TOP_DEBUG_CTRL__TOP_DEBUG_CTRL);
    clock_physical_cg_ctrl(HAL_CLOCK_CG_CKSYS_DEBUG_DIS, CG_REQUEST_CLEAR);  // Enable Debug monitor
    clk_dvt_log_info("Clear CG_CKSYS_DEBUG_DIS *0x%08X = 0x%08X", RM_CKSYS_XO_CLK_BASE+0x0B80, _U32_B15_);

    uint8_t clko_pin = 6;
 
  #if 0  /* cm_ck_div4 */
    clk_dvt_log_info("cm_ck_div4");
    hal_clock_out_by_gpio(clko_pin, 15);
    _gpio_set_mode(1, GPIO_AUX_FUN_DEBUGMON);  /* cm_ck_idle */

    /* === Write RG ===
    {0x42010108,0x00000007}
    {0x42040B80,0x00008000}
    {0x420B0300,0x0F000000}
    {0x420B0200,0x07000000}
    {0x42030058,0x000F0000}
    {0x420B0300,0x000000F0}
    {0x420B0200,0x000000D0}
    */
  #endif

  #if 1  /* tcm_ck_hclk_ck */
    clk_dvt_log_info("tcm_ck_hclk_ck");
    hal_clock_out_by_gpio(clko_pin, 14);
    _gpio_set_mode(5, GPIO_AUX_FUN_DEBUGMON);  /* tcm_ck_idle */

    /* === Write RG ===
    {0x42010108,0x00000007}
    {0x42040B80,0x00008000}
    {0x420B0300,0x0F000000}
    {0x420B0200,0x07000000}
    {0x42030058,0x000E0000}
    {0x420B0300,0x00F00000}
    {0x420B0200,0x00D00000}
    {0x420C0008,0x00003C00} // Clear GPIO5 and GPIO6 driving current settings
    */
  #endif

  #if 0  /* f_fbt_mac_mclk_ck */
    clk_dvt_log_info("f_fbt_mac_mclk_ck");
    hal_clock_out_by_gpio(clko_pin, 13);
    _gpio_set_mode(35, GPIO_AUX_FUN_DEBUGMON);  /* bt_mac_ck_idle */
  #endif

  #if 0  /* f_fslow_bus_hclk_ck */
    clk_dvt_log_info("f_fslow_bus_hclk_ck");
    hal_clock_out_by_gpio(clko_pin, 12);
    _gpio_set_mode(23, GPIO_AUX_FUN_DEBUGMON);  /* xo_clk_idle */
  #endif

  #if 0  /* hf_fbus_hclk_ck */
    clk_dvt_log_info("hf_fbus_hclk_ck");
    hal_clock_out_by_gpio(clko_pin, 11);
    _gpio_set_mode(21, GPIO_AUX_FUN_DEBUGMON);  /* bus_clk_idle */
  #endif

  #if 0  /* hf_fesc_phy_hclk_ck */
    clk_dvt_log_info("hf_fesc_phy_hclk_ck");
    _gpio_set_mode(17, 1);
    _gpio_set_mode(18, 1);
    _gpio_set_mode(19, 1);
    _gpio_set_mode(20, 1);
    _gpio_set_mode(21, 1);
    _gpio_set_mode(22, 1);
    hal_esc_init();
    *ESC_DCM_CON_0__RG_ESC_DCM_DBC_NUM = 2;  // Modify Debounce Number for Easy Measurement
    hal_clock_out_by_gpio(clko_pin, 10);
    //_gpio_set_mode(19, GPIO_AUX_FUN_DEBUGMON);  /* esc_idle */
    (*TOP_DEBUG_CTRL__TOP_DEBUG_CTRL) |= _U16_B8_;  /* Swap DEBUGMON[7:0] and [15:8] */
    clk_dvt_log_info("TOP_DEBUG_CTRL *0x%08X = 0x%04X", RM_TOP_MISC_CFG_BASE+0x0108, *TOP_DEBUG_CTRL__TOP_DEBUG_CTRL);
    _gpio_set_mode(29, GPIO_AUX_FUN_DEBUGMON);  /* esc_clk_idle */

    uint32_t esc_base_addr = 0x7000000;
    uint32_t value = 0xAA55AA55, addr;
    for(uint32_t i=0; i<100000; i++) {
        addr = esc_base_addr + i * 4;
        clk_dvt_log_info("ESC Read 0x%08X = 0x%08X", addr, *(volatile uint32_t *)addr);
        *(volatile uint32_t *)addr = value;
        clk_dvt_log_info("ESC Write 0x%08X = 0x%08X", addr, value);
        value ++;
        clk_dvt_log_info("ESC Read 0x%08X = 0x%08X", addr, *(volatile uint32_t *)addr);
        hal_gpt_delay_ms(1);
    }
  #endif

  #if 0  /* hf_fsfc_phy_hclk_ck */
    clk_dvt_log_info("hf_fsfc_phy_hclk_ck");
    *SFC_DCM_CON_0__RG_SFC_DCM_DBC_NUM = 2;  // Modify Debounce Number for Easy Measurement
    clk_dvt_log_info("*0x%08X = 0x%08X", RM_CKSYS_BASE+0x0010, *(volatile uint32_t *)(RM_CKSYS_BASE+0x0010));
    hal_clock_out_by_gpio(clko_pin, 9);
    _gpio_set_mode(17, GPIO_AUX_FUN_DEBUGMON);  /* sfc_idle */

    /* === Write RG ===
    {0x42010108,0x00000007}
    {0x42040B80,0x00008000}
    {0x42030010,0x06010200}
    {0x420B0300,0x0F000000}
    {0x420B0200,0x07000000}
    {0x42030058,0x00090000}
    {0x420B0308,0x000000F0}
    {0x420B0208,0x000000D0}
    */
  #endif
}
#endif /* DVT_DCM */

// ---------------------------------------------------------------------------
#ifdef DVT_ABB_CLK_GEN
void clk_dvt_ABB_CLK_GEN(void)
{
    clk_dvt_log_info("ABB_CLK_GEN");

    /*                       abb_clk_gen_debug_mon[]     GPIO
      ----------------------------------------------------------------
        CLK_ABBCK200K_BGR        0 (DEBUGMON0)          0,29,32
        CLK_ABBCK200K_AIO        1 (DEBUGMON1)          1,30,33
        CLK_AUD01ADC             2 (DEBUGMON2)          2,31,34
    */
    uint8_t baGpioNum[] = { 29, 1, 34 };

    *TOP_DEBUG_CTRL__TOP_DEBUG_CTRL = 8;  // Select abb_clk_gen_debug_mon[15:0]
    clock_physical_cg_ctrl(HAL_CLOCK_CG_CKSYS_DEBUG_DIS, CG_REQUEST_CLEAR);  // Enable Debug monitor
    *ABB_CLK_GEN_CFG_4__DBG_CLK_OUT_EN = 1;

    //uint16_t divider = 0;     // XO / (2 x (1+0)) = 16 MHz
    //uint16_t divider = 1023;  // XO / (2 x (1+1023)) = 15.625 KHz
    uint16_t divider = 2047;  // XO / (2 x (1+2047)) = 7.8125 KHz

    for(uint8_t idx=0; idx<CLK_ABB_GEN_MAX; idx++) {
        _gpio_set_mode(baGpioNum[idx], GPIO_AUX_FUN_DEBUGMON);
        hal_clock_abb_clk_gen_enable(idx, divider);
    }
}
#endif /* DVT_ABB_CLK_GEN */

// ---------------------------------------------------------------------------
#ifdef DVT_FQMTR_MON_OUT
void clk_dvt_FQMTR_MON_OUT(void)
{
    clk_dvt_log_info("FQMTR_MON_OUT");

    *TOP_DEBUG_CTRL__TOP_DEBUG_CTRL = 6;  // Select cksys_mon_out0[15:0]
    //*TOP_DEBUG_CTRL__TOP_DEBUG_CTRL = 7;  // Select cksys_mon_out1[15:0]
    clock_physical_cg_ctrl(HAL_CLOCK_CG_CKSYS_DEBUG_DIS, CG_REQUEST_CLEAR);  // Enable Debug monitor

    *CKSYS_TST_SEL_1__TST_SEL_1 = AD_64M_DBB_CK;

    _gpio_set_mode(25, GPIO_AUX_FUN_DEBUGMON);  /* cksys_mon_out0[15] or cksys_mon_out1[15]: mon_fqmtr_ck, DEBUGMON15, GPIO 15,25,47 */
    while(1);
}
#endif /* DVT_FQMTR_MON_OUT */

// ---------------------------------------------------------------------------
#ifdef DVT_HOPPING
void clk_dvt_HOPPING(void)
{
    clk_dvt_log_info("HOPPING");
#if 0
    hal_clock_out_by_gpio(17, 6);  /* f_fosc_ls_ck */
#else
    *TOP_DEBUG_CTRL__TOP_DEBUG_CTRL = 6;  // Select cksys_mon_out0[15:0]
    clock_physical_cg_ctrl(HAL_CLOCK_CG_CKSYS_DEBUG_DIS, CG_REQUEST_CLEAR);  // Enable Debug monitor
    hal_clock_freq_meter_data(XO_CK, AD_HFOSC_HS, fqmtr_winset_estimate(156000000));  // Choose a source clock -> GPIO clock out
    _gpio_set_mode(25, GPIO_AUX_FUN_DEBUGMON);  /* cksys_mon_out0[15] or cksys_mon_out1[15]: mon_fqmtr_ck, DEBUGMON15, GPIO 15,25,47 */
#endif
}
#endif /* DVT_HOPPING */

// ---------------------------------------------------------------------------
#ifdef DVT_DCXO_WAKEUP
void clk_dvt_DCXO_WAKEUP(void)
{
    clk_dvt_log_info("DCXO_WAKEUP");

    /* === Monitor select: dcxo_debug_10 ===       order of signal on
      ----------------------------------------------------------------
        DEBUGMON7 (GPIO 7,17,39)   osc_rdy                5
        DEBUGMON6 (GPIO 6,16,38)   DCXO_DELAY             4
        DEBUGMON4 (GPIO 4,27,36)   EN_RF_LDO              3
        DEBUGMON3 (GPIO 3,26,35)   EN_BB                  3
        DEBUGMON2 (GPIO 2,31,34)   EN_BG                  2
        DEBUGMON0 (GPIO 0,29,32)   md_srclkena_f32k       1
    */
    hal_dcxo_32k_ctrl(true);
    clk_dvt_log_info("DCXO32K_EN *0x%08X = 0x%08X", RM_DCXO_PWR_CTRL_BASE+0x0014, *((volatile uint32_t *)(RM_DCXO_PWR_CTRL_BASE+0x0014)));
    hal_dcxo_dbg_monitor_ctrl(true, 10);
    clk_dvt_log_info("TOP_DEBUG_CTRL *0x%08X = 0x%04X", RM_TOP_MISC_CFG_BASE+0x0108, *TOP_DEBUG_CTRL__TOP_DEBUG_CTRL);
    clk_dvt_log_info("Clear CG_CKSYS_DEBUG_DIS *0x%08X = 0x%08X", RM_CKSYS_XO_CLK_BASE+0x0B80, _U32_B15_);
    clk_dvt_log_info("DCXO_DEBUG *0x%08X = 0x%08X", RM_DCXO_PWR_CTRL_BASE+0x0100, *((volatile uint32_t *)(RM_DCXO_PWR_CTRL_BASE+0x0100)));

    _gpio_set_mode(39, GPIO_AUX_FUN_DEBUGMON);  /* osc_rdy */
    _gpio_set_mode(38, GPIO_AUX_FUN_DEBUGMON);  /* DCXO_DELAY */
    _gpio_set_mode(36, GPIO_AUX_FUN_DEBUGMON);  /* EN_RF_LDO */
    _gpio_set_mode(35, GPIO_AUX_FUN_DEBUGMON);  /* EN_BB */
    _gpio_set_mode(34, GPIO_AUX_FUN_DEBUGMON);  /* EN_BG */
    _gpio_set_mode(29, GPIO_AUX_FUN_DEBUGMON);  /* md_srclkena_f32k */

    /* === Write RG ===
    {0x42060014,0x00010101}  DCXO 32K Enabled
    {0x42060014,0x00000101}  DCXO 32K Disabled
    {0x42010108,0x00000005}
    {0x42040B80,0x00008000}
    {0x42060100,0x000A0001}
    {0x420B0310,0xF0000000}
    {0x420B0210,0xD0000000}
    {0x420B0310,0x0F000000}
    {0x420B0210,0x0D000000}
    {0x420B0310,0x000F0000}
    {0x420B0210,0x000D0000}
    {0x420B0310,0x0000F000}
    {0x420B0210,0x0000D000}
    {0x420B0310,0x00000F00}
    {0x420B0210,0x00000D00}
    {0x420B030C,0x00F00000}
    {0x420B020C,0x00D00000}
    */
}
#endif /* DVT_DCXO_WAKEUP */

// ---------------------------------------------------------------------------
#ifdef DVT_DCXO_32K
void clk_dvt_DCXO_32K(void)
{
    clk_dvt_log_info("DCXO_32K");

    hal_dcxo_32k_ctrl(true);

    uint32_t winset = hal_clock_fqmtr_winset_estimate(32768, DCXO_HZ);
    uint32_t freq_meter_data = hal_clock_freq_meter_data(DCXO_F32K, xo_ck, winset);
    uint32_t ref_hz = (((uint64_t)DCXO_HZ) * (winset + 1)) / freq_meter_data;
    //char     disp_buf[16];

    //clk_dvt_get_freq_diff_str(32768, ref_hz, disp_buf);
    //clk_dvt_log_info("Fref 32768, winset %lu, freq_measure %lu, %s", winset, ref_hz, disp_buf);

    char PpmSign;
    uint8_t PpmDecimal;
    uint32_t PpmInteger;

    PpmSign = clk_dvt_get_freq_diff_ppm(32768, ref_hz, &PpmInteger, &PpmDecimal);
    if(freq_meter_data) {
        clk_dvt_log_info("DCXO32K enable %d, Fref 32768, winset %lu, freq_meter_data %lu, ref_hz_measure %lu, %c%u.%02dppm", *DCXO_PCON5__DCXO32K_EN, winset, freq_meter_data, ref_hz, PpmSign, PpmInteger, PpmDecimal);
    }
    else {
        clk_dvt_log_info("DCXO32K enable %d, Fref 32768, winset %lu, freq_meter_data 0", *DCXO_PCON5__DCXO32K_EN, winset);
    }

    freq_meter_data = hal_clock_freq_meter_data(EOSC_F32K, xo_ck, winset);
    ref_hz = (((uint64_t)DCXO_HZ) * (winset + 1)) / freq_meter_data;
    PpmSign = clk_dvt_get_freq_diff_ppm(32768, ref_hz, &PpmInteger, &PpmDecimal);
    if(freq_meter_data) {
        clk_dvt_log_info("EOSC_F32K: Fref 32768, winset %lu, freq_meter_data %lu, ref_hz_measure %lu, %c%u.%02dppm", winset, freq_meter_data, ref_hz, PpmSign, PpmInteger, PpmDecimal);
    }
    else {
        clk_dvt_log_info("EOSC_F32K: Fref 32768, winset %lu, freq_meter_data 0", winset);
    }

    freq_meter_data = hal_clock_freq_meter_data(XOSC_F32K, xo_ck, winset);
    ref_hz = (((uint64_t)DCXO_HZ) * (winset + 1)) / freq_meter_data;
    PpmSign = clk_dvt_get_freq_diff_ppm(32768, ref_hz, &PpmInteger, &PpmDecimal);
    if(freq_meter_data) {
        clk_dvt_log_info("XOSC_F32K: Fref 32768, winset %lu, freq_meter_data %lu, ref_hz_measure %lu, %c%u.%02dppm", winset, freq_meter_data, ref_hz, PpmSign, PpmInteger, PpmDecimal);
    }
    else {
        clk_dvt_log_info("XOSC_F32K: Fref 32768, winset %lu, freq_meter_data 0", winset);
    }
}
#endif /* DVT_DCXO_32K */

// ---------------------------------------------------------------------------
#ifdef DVT_TEST
void clk_dvt_TEST(void)
{
    clk_dvt_log_info("TEST");

    *TOP_DEBUG_CTRL__TOP_DEBUG_CTRL = 5;
    *DCXO_DEBUG0__DCXO_DEBUG_SEL = 2;
    *DCXO_DEBUG0__DCXO_DEBUG_EN = 1;
    clk_dvt_log_info("TOP_DEBUG_CTRL *0x%08X = 0x%04X", RM_TOP_MISC_CFG_BASE+0x0108, *TOP_DEBUG_CTRL__TOP_DEBUG_CTRL);
    clock_physical_cg_ctrl(HAL_CLOCK_CG_CKSYS_DEBUG_DIS, CG_REQUEST_CLEAR);  // Enable Debug monitor
    clk_dvt_log_info("Clear CG_CKSYS_DEBUG_DIS *0x%08X = 0x%08X", RM_CKSYS_XO_CLK_BASE+0x0B80, _U32_B15_);
    clk_dvt_log_info("DCXO_DEBUG *0x%08X = 0x%08X", RM_DCXO_PWR_CTRL_BASE+0x0100, *((volatile uint32_t *)(RM_DCXO_PWR_CTRL_BASE+0x0100)));

    _gpio_set_mode(6, GPIO_AUX_FUN_DEBUGMON);  /* debug_f32k_ck */

    /* === Write RG ===
    {0x42010108,0x00000005}
    {0x42040B80,0x00008000}
    {0x42060100,0x00020001}
    {0x420B0300,0x0F000000}
    {0x420B0200,0x0D000000}
    */
}
#endif /* DVT_TEST */

// ---------------------------------------------------------------------------
void clk_dvt_entry(void)
{
    clk_dvt_log_info("clk_dvt_entry()");
    hal_clock_all_on();

#ifdef DVT_GPIO_TOGGLE
    clk_dvt_GPIO_TOGGLE();
#endif
#ifdef DVT_FQMTR_SRC_CLK_FIXED_FREQ
    clk_dvt_FQMTR_SRC_CLK_FIXED_FREQ();
#endif
#ifdef DVT_FQMTR_SRC_CLK_MUX
    clk_dvt_FQMTR_SRC_CLK_MUX();
#endif
#ifdef DVT_OTHER_CLK_MUX
    clk_dvt_OTHER_CLK_MUX();
#endif
#ifdef DVT_FQMTR_SRC_CLK_CHOP
    clk_dvt_FQMTR_SRC_CLK_CHOP();
#endif
#ifdef DVT_CLKO
    clk_dvt_CLKO();
#endif
#ifdef DVT_DCM
    clk_dvt_DCM();
#endif
#ifdef DVT_ABB_CLK_GEN
    clk_dvt_ABB_CLK_GEN();
#endif
#ifdef DVT_FQMTR_MON_OUT
    clk_dvt_FQMTR_MON_OUT();
#endif
#ifdef DVT_HOPPING
    clk_dvt_HOPPING();
#endif
#ifdef DVT_DCXO_WAKEUP
    clk_dvt_DCXO_WAKEUP();
#endif
#ifdef DVT_DCXO_32K
    clk_dvt_DCXO_32K();
#endif
#ifdef DVT_TEST
    clk_dvt_TEST();
#endif
}
#endif /* _CLOCK_DVT_ */

#endif /* HAL_CLOCK_MODULE_ENABLED */
