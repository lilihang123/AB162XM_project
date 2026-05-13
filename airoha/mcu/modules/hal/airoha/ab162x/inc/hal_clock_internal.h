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

#ifndef __HAL_CLOCK_INTERNAL_H__
#define __HAL_CLOCK_INTERNAL_H__

#include "hal_clock.h"

#ifdef HAL_CLOCK_MODULE_ENABLED
#include "hal_clock_platform.h"

#ifndef CLOCK_COSIM
#include <assert.h>
#include "memory_attribute.h"
#include "hal_nvic_internal.h"

#include "autoconf.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * General definition
 *****************************************************************************/
#if defined(CONFIG_AIR_FPGA_ENV_ENABLE) && !defined(FPGA_ENV)
#define FPGA_ENV
#endif

#ifndef FPGA_ENV
#if defined(CONFIG_MCUBOOT) && !defined(__EXT_BOOTLOADER__)
#define __EXT_BOOTLOADER__
#endif
#if defined(AIR_DOWNLOAD_AGENT) && !defined(__EXT_DA__)
#define __EXT_DA__
#endif
#endif /* !FPGA_ENV */

#define CLK_LPOSC_MUX_INIT_RUN_DFS_HIGH

#ifdef CLOCK_COSIM
  #ifdef FPGA_ENV
    #undef FPGA_ENV
  #endif
  #ifdef __EXT_BOOTLOADER__
    #undef __EXT_BOOTLOADER__
  #endif
  #ifdef __EXT_DA__
    #undef __EXT_DA__
  #endif

  #define ATTR_TEXT_IN_TCM
  #define ATTR_RWDATA_IN_TCM
  #define ATTR_RODATA_IN_TCM
  #define ATTR_ZIDATA_IN_TCM
  #define ATTR_TEXT_IN_SYSRAM
  #define ATTR_RODATA_IN_SYSRAM

  #define static

  #ifdef assert
    #undef assert
    #define assert(x)
  #endif

  extern void hal_gpt_delay_us(uint32_t us);
  extern void MDM_TM_STR(const char *str);
  extern void MDM_TM_PRINTF(const char *fmt,...);

#else /* !CLOCK_COSIM */
  //#define CLOCK_BRINGUP_VER
  #ifdef CLOCK_BRINGUP_VER
    //#define BRINGUP_BOOTLOADER_RUN_XO  /* for debug only */
  #endif
#endif

#ifndef DCXO_HZ
#define DCXO_HZ                            32000000  /* 32 MHz */
#endif
#ifndef DCXO_KHZ
#define DCXO_KHZ                           32000     /* 32 MHz */
#endif

/*****************************************************************************
 * CG
 *****************************************************************************/
/* ------ Range ------ */
#define HAL_CLOCK_CG_XO_PDN_PD_BEGIN       HAL_CLOCK_CG_AUXADC
#define HAL_CLOCK_CG_XO_PDN_PD_END         HAL_CLOCK_CG_AUXADC

#define HAL_CLOCK_CG_XO_PDN_AO0_BEGIN      HAL_CLOCK_CG_PWM_DMA_0
#define HAL_CLOCK_CG_XO_PDN_AO0_END        HAL_CLOCK_CG_PMU_1M

#define HAL_CLOCK_CG_XO_PDN_AO1_BEGIN      HAL_CLOCK_CG_FAST_DMA_1
#define HAL_CLOCK_CG_XO_PDN_AO1_END        HAL_CLOCK_CG_SEC_MON_AO

#define HAL_CLOCK_CG_XO_PDN_TOP0_BEGIN     HAL_CLOCK_CG_SPIMST0
#define HAL_CLOCK_CG_XO_PDN_TOP0_END       HAL_CLOCK_CG_BT_MAC

#define HAL_CLOCK_CG_XO_PDN_TOP1_BEGIN     HAL_CLOCK_CG_CMSYS_BUS
#define HAL_CLOCK_CG_XO_PDN_TOP1_END       HAL_CLOCK_CG_OSC_HS_D4

#define HAL_CLOCK_CG_PDN_PD_BEGIN          HAL_CLOCK_CG_AUXADC_SRAM
#define HAL_CLOCK_CG_PDN_PD_END            HAL_CLOCK_CG_USB_DMA

#define HAL_CLOCK_CG_PDN_TOP_BEGIN         HAL_CLOCK_CG_CMSYS_ROM
#define HAL_CLOCK_CG_PDN_TOP_END           HAL_CLOCK_CG_CMSYS_ROM

/* ------ Alias ------ */
#define HAL_CLOCK_CG_PWM_DMA0              HAL_CLOCK_CG_PWM_DMA_0
#define HAL_CLOCK_CG_PWM_DMA1              HAL_CLOCK_CG_PWM_DMA_1
#define HAL_CLOCK_CG_PWM_0                 HAL_CLOCK_CG_PWM_DMA_0
#define HAL_CLOCK_CG_PWM_1                 HAL_CLOCK_CG_PWM_DMA_1
#define HAL_CLOCK_CG_PWM0                  HAL_CLOCK_CG_PWM_DMA_0
#define HAL_CLOCK_CG_PWM1                  HAL_CLOCK_CG_PWM_DMA_1
#define HAL_CLOCK_CG_PWM2                  HAL_CLOCK_CG_PWM_2
#define HAL_CLOCK_CG_PWM3                  HAL_CLOCK_CG_PWM_3
#define HAL_CLOCK_CG_PWM4                  HAL_CLOCK_CG_PWM_4
#define HAL_CLOCK_CG_UART_0                HAL_CLOCK_CG_UART0
#define HAL_CLOCK_CG_UART_1                HAL_CLOCK_CG_UART1
#define HAL_CLOCK_CG_UART_2                HAL_CLOCK_CG_UART2
#define HAL_CLOCK_CG_UART_DMA_0            HAL_CLOCK_CG_UART_DMA0
#define HAL_CLOCK_CG_UART_DMA_1            HAL_CLOCK_CG_UART_DMA1
#define HAL_CLOCK_CG_UART_DMA_2            HAL_CLOCK_CG_UART_DMA2
#define HAL_CLOCK_CG_I3C_0                 HAL_CLOCK_CG_I3C0
#define HAL_CLOCK_CG_I3C_1                 HAL_CLOCK_CG_I3C1
#define HAL_CLOCK_CG_I3C_DMA_0             HAL_CLOCK_CG_I3C_DMA0
#define HAL_CLOCK_CG_I3C_DMA_1             HAL_CLOCK_CG_I3C_DMA1
#define HAL_CLOCK_CG_SPIMST_0              HAL_CLOCK_CG_SPIMST0
#define HAL_CLOCK_CG_SPIMST_1              HAL_CLOCK_CG_SPIMST1
#define HAL_CLOCK_CG_SPIMST_2              HAL_CLOCK_CG_SPIMST2
#define HAL_CLOCK_CG_FAST_DMA0             HAL_CLOCK_CG_FAST_DMA_0
#define HAL_CLOCK_CG_FAST_DMA1             HAL_CLOCK_CG_FAST_DMA_1
#define HAL_CLOCK_CG_AUD_ENGINE_BUS        HAL_CLOCK_CG_AUD_ENGINE

/*****************************************************************************
 * enum or struct
 *****************************************************************************/
typedef struct {
    uint32_t  lposc_khz;

    uint32_t  lposc_hopping_range_x10000;
    uint32_t  lposc_re_k_period_ms;

    uint8_t   lposc_hs_div;
    uint8_t   lposc_ls_div;
    uint8_t   lposc_hopping_timer_us_once;
    uint8_t   lposc_hopping_jump_code_once;

    uint8_t   dvfs_sys_cfg;

    bool      lposc_hopping_enable;
    bool      lposc_re_k_periodically_enable;
    bool      dcm_enable;
} hal_clk_cfg_t;

typedef enum {
    XO_CK,
    RTC_CK,
    PAD_SOC_REF_CK,
    CHOP_CK,
    EOSC_F32K,
    DCXO_F32K,
    XOSC_F32K,
    PAD_REF_CK
} ref_clock_t;

/* Index definitions of Every MUX (clock_mux_sel_id) */
/* Used when Select a Target index in a MUX          */
typedef enum {
    /* MUX: CLK_SYS_SEL */
    MUX_SYS_IDX_XO                   = 0,
    MUX_SYS_IDX_OSC_26M              = 1,
    MUX_SYS_IDX_OSC_LS               = 2,
    MUX_SYS_IDX_OSC_HS               = 3,
    MUX_SYS_IDX_OSC_HS_D2            = 4,
    MUX_SYS_IDX_OSC_D3               = 5,

    /* MUX: CLK_IBEX_SEL */
    MUX_IBEX_IDX_XO                  = 0,
    MUX_IBEX_IDX_XO_DBL              = 1,
    MUX_IBEX_IDX_OSC_26M             = 2,
    MUX_IBEX_IDX_OSC_LS              = 3,

    /* MUX: CLK_SFC_SEL */
    MUX_SFC_IDX_XO                   = 0,
    MUX_SFC_IDX_OSC_26M              = 1,
    MUX_SFC_IDX_OSC_HS               = 2,
    MUX_SFC_IDX_OSC_HS_D2            = 3,
    MUX_SFC_IDX_OSC_D3               = 4,

    /* MUX: CLK_ESC_SEL */
    MUX_ESC_IDX_XO                   = 0,
    MUX_ESC_IDX_OSC_26M              = 1,
    MUX_ESC_IDX_OSC_HS_D2            = 2,
    MUX_ESC_IDX_OSC_HS_D4            = 3,

    /* MUX: CLK_SPIMST0_SEL */
    /* MUX: CLK_SPIMST1_SEL */
    MUX_SPIMST01_IDX_XO              = 0,
    MUX_SPIMST01_IDX_OSC_26M         = 1,

    /* MUX: CLK_SPIMST2_SEL */
    MUX_SPIMST2_IDX_XO               = 0,
    MUX_SPIMST2_IDX_OSC_26M          = 1,
    MUX_SPIMST2_IDX_OSC_HS           = 2,
    MUX_SPIMST2_IDX_OSC_HS_D2        = 3,

    /* MUX: CLK_SPISLV_SEL */
    MUX_SPISLV_IDX_XO                = 0,
    MUX_SPISLV_IDX_OSC_26M           = 1,
    MUX_SPISLV_IDX_OSC_LS_D2         = 2,

    /* MUX: CLK_I3C_SEL */
    MUX_I3C_IDX_XO                   = 0,
    MUX_I3C_IDX_OSC_26M              = 1,
    MUX_I3C_IDX_OSC_D3               = 2,

    /* MUX: CLK_USB_SEL */
    MUX_USB_IDX_XO                   = 0,
    MUX_USB_IDX_XO_DBL               = 1,
    MUX_USB_IDX_OSC_26M              = 2,
    MUX_USB_IDX_OSC_LS               = 3,

    /* MUX: CLK_AUD_ENGINE_SEL */
    MUX_AUD_ENGINE_IDX_XO            = 0,
    MUX_AUD_ENGINE_IDX_OSC_26M       = 1,

    /* MUX: CLK_AUD_BUS_SEL */
    MUX_AUD_BUS_IDX_XO               = 0,
    MUX_AUD_BUS_IDX_OSC_26M          = 1,

    /* MUX: CLK_BT_HOP_SEL */
    MUX_BT_HOP_IDX_XO                = 0,
    MUX_BT_HOP_IDX_OSC_26M           = 1,
    MUX_BT_HOP_IDX_OSC_HS            = 2,
    MUX_BT_HOP_IDX_OSC_HS_D2         = 3,

    /* MUX: CLK_BT_MAC_SEL */
    MUX_BT_MAC_IDX_XO                = 0,
    MUX_BT_MAC_IDX_XO_DBL            = 1,

    /* MUX: CLK_UART0_SEL */
    /* MUX: CLK_UART1_SEL */
    /* MUX: CLK_UART2_SEL */
    MUX_UART_IDX_XO                  = 0,
    MUX_UART_IDX_OSC_26M             = 1,

    /* MUX: CLK_GPT_BCLK_SEL */
    /* MUX: CLK_OSGPT_BCLK_SEL */
    /* MUX: CLK_SEC_GPT_BCLK_SEL */
    MUX_GPT_BCLK_IDX_XO_HALF         = 0,
    MUX_GPT_BCLK_IDX_OSC_26M_HALF    = 1,

    /* MUX: CLK_DCXO_PWR_CTRL_SEL */
    /* MUX: CLK_DCXO_DIG_MACRO_SEL */
    MUX_DCXO_IDX_EOSC                = 0,
    MUX_DCXO_IDX_RTC                 = 1,

    /* MUX: CLK_IRTX_SEL */
    MUX_IRTX_IDX_XO                  = 0,
    MUX_IRTX_IDX_OSC_26M             = 1,
    MUX_IRTX_IDX_OSC_HS              = 2,
    MUX_IRTX_IDX_OSC_D3              = 3,

    /* MUX: CLK_IRRX_BCLK_SEL */
    MUX_IRRX_BCLK_IDX_XO             = 0,
    MUX_IRRX_BCLK_IDX_OSC_26M        = 1,

    /* MUX: CLK_OSC_26M_SEL */
    MUX_OSC_26M_IDX_OSC_LS           = 0,
    MUX_OSC_26M_IDX_OSC_LS_D2        = 1,

    /* MUX: CLK_RGU_32K_SEL */
    MUX_RGU_32K_IDX_EOSC             = 0,
    MUX_RGU_32K_IDX_RTC              = 1,

    /* MUX: CLK_SLOW_BUS_SEL */
    MUX_SLOW_BUS_IDX_XO              = 0,
    MUX_SLOW_BUS_IDX_OSC_26M         = 1,

    /* MUX: CLK_PWM0_SEL */
    /* MUX: CLK_PWM1_SEL */
    /* MUX: CLK_PWM2_SEL */
    /* MUX: CLK_PWM3_SEL */
    /* MUX: CLK_PWM4_SEL */
    MUX_PWM_IDX_XO                   = 0,
    MUX_PWM_IDX_RTC                  = 1,
    MUX_PWM_IDX_OSC_26M              = 2,
    MUX_PWM_IDX_OSC_LS               = 3,
} clk_mux_sel_idx_t;

typedef enum {
    DCXO_LP_MODE,
    DCXO_NORMAL_MODE,
    DCXO_LPM = DCXO_LP_MODE,
    DCXO_FPM = DCXO_NORMAL_MODE
} dcxo_mode_t;

typedef enum {
    DCXO_FPM_LOCK_ATC,
    DCXO_FPM_LOCK_RACE,
    DCXO_FPM_LOCK_BT,
    DCXO_FPM_LOCK_USB,
    DCXO_FPM_LOCK_TEST,
    DCXO_FPM_LOCK_MAX
} dcxo_fpm_lock_src_t;

typedef enum {
    DCXO_FPM_UNLOCK,
    DCXO_FPM_LOCK
} dcxo_fpm_lock_op_t;

typedef enum {
    CLK_DCM_SFC,
    CLK_DCM_ESC,
    CLK_DCM_SLOW_BUS,
    CLK_DCM_FAST_BUS,
    CLK_DCM_CMSYS,
    CLK_DCM_MEMSYS,   /* TCM */
    CLK_DCM_BT_MAC,
    CLK_DCM_MAX
} clk_dcm_t;

typedef enum {  /* 6 bits */
    DCM_DIV_64 = 0x00,
    DCM_DIV_32 = 0x01,
    DCM_DIV_16 = 0x02,
    DCM_DIV_8  = 0x04,
    DCM_DIV_4  = 0x08,
    DCM_DIV_2  = 0x10,
    DCM_DIV_1  = 0x20
} clk_dcm_div_t;

typedef enum {  /* Freq = XO/(2*(SEL+1)) */
    CLK_ABBCK200K_BGR,
    CLK_ABBCK200K_AIO,
    CLK_AUD01ADC,
    CLK_ABB_GEN_MAX
} clk_abb_gen_t;

typedef enum {
    CLK_BT_RX_ADC_OFF,  /* Initial State */
    CLK_BT_RX_ADC_DEFAULT = CLK_BT_RX_ADC_OFF,
    CLK_BT_RX_ADC_32M,  /* DBL disabled for RX ADC 32M when none uses DBL */
    CLK_BT_RX_ADC_64M,  /* DBL disabled for RX ADC 64M when none uses DBL */
    CLK_BT_RX_ADC_AUTO, /* DBL enabled */
    CLK_BT_RX_ADC_MAX
} clk_bt_rx_adc_t;

/*****************************************************************************
 * DVFS definition
 *****************************************************************************/
enum {
    AIR_DVFS_SYS_CFG_NORMAL,
    AIR_DVFS_SYS_CFG_BASE_MID,
    AIR_DVFS_SYS_CFG_FIX_HIGH
};

typedef enum {
    HAL_DVFS_VCORE_MID,
    HAL_DVFS_VCORE_HIGH,
    HAL_DVFS_VCORE_MAX
} hal_dvfs_vcore_t;

typedef enum {
    HAL_DVFS_FRQ_LOW,
    HAL_DVFS_FRQ_MID,
    HAL_DVFS_FRQ_HIGH,
    HAL_DVFS_FRQ_MAX
} hal_dvfs_frq_t;

/*****************************************************************************
 * DVT
 *****************************************************************************/
#if !defined(FPGA_ENV) && !defined(__EXT_BOOTLOADER__) && !defined(__EXT_DA__) && !defined(CLOCK_COSIM)
  //#define _CLOCK_DVT_
#endif

#ifdef _CLOCK_DVT_
void clk_dvt_entry(void);
//#define DVT_GPIO_TOGGLE
//#define DVT_FQMTR_SRC_CLK_FIXED_FREQ
//#define DVT_FQMTR_SRC_CLK_MUX
//#define DVT_OTHER_CLK_MUX
//#define DVT_FQMTR_SRC_CLK_CHOP
//#define DVT_CLKO
#define DVT_DCM
//#define DVT_ABB_CLK_GEN
//#define DVT_FQMTR_MON_OUT
//#define DVT_HOPPING
//#define DVT_DCXO_WAKEUP
//#define DVT_DCXO_32K
//#define DVT_TEST
#endif /* _CLOCK_DVT_ */

/******************************************************************************
 * Common use
 ******************************************************************************/
#define UNUSED_PARAMETER(x) ((void)(x))

#define _U8_B0_              0x01
#define _U8_B1_              0x02
#define _U8_B2_              0x04
#define _U8_B3_              0x08
#define _U8_B4_              0x10
#define _U8_B5_              0x20
#define _U8_B6_              0x40
#define _U8_B7_              0x80

#define _U16_B0_             0x0001
#define _U16_B1_             0x0002
#define _U16_B2_             0x0004
#define _U16_B3_             0x0008
#define _U16_B4_             0x0010
#define _U16_B5_             0x0020
#define _U16_B6_             0x0040
#define _U16_B7_             0x0080
#define _U16_B8_             0x0100
#define _U16_B9_             0x0200
#define _U16_B10_            0x0400
#define _U16_B11_            0x0800
#define _U16_B12_            0x1000
#define _U16_B13_            0x2000
#define _U16_B14_            0x4000
#define _U16_B15_            0x8000

#define _U32_B0_             0x00000001
#define _U32_B1_             0x00000002
#define _U32_B2_             0x00000004
#define _U32_B3_             0x00000008
#define _U32_B4_             0x00000010
#define _U32_B5_             0x00000020
#define _U32_B6_             0x00000040
#define _U32_B7_             0x00000080
#define _U32_B8_             0x00000100
#define _U32_B9_             0x00000200
#define _U32_B10_            0x00000400
#define _U32_B11_            0x00000800
#define _U32_B12_            0x00001000
#define _U32_B13_            0x00002000
#define _U32_B14_            0x00004000
#define _U32_B15_            0x00008000
#define _U32_B16_            0x00010000
#define _U32_B17_            0x00020000
#define _U32_B18_            0x00040000
#define _U32_B19_            0x00080000
#define _U32_B20_            0x00100000
#define _U32_B21_            0x00200000
#define _U32_B22_            0x00400000
#define _U32_B23_            0x00800000
#define _U32_B24_            0x01000000
#define _U32_B25_            0x02000000
#define _U32_B26_            0x04000000
#define _U32_B27_            0x08000000
#define _U32_B28_            0x10000000
#define _U32_B29_            0x20000000
#define _U32_B30_            0x40000000
#define _U32_B31_            0x80000000

/*****************************************************************************
 * Function prototype
 *****************************************************************************/
void hal_clock_dump_cfg(void);
void hal_clock_init_cfg(hal_clk_cfg_t *pt_cfg);
void hal_clock_all_on(void);
uint32_t hal_clock_get_cmsys_freq_hz_by_mux_idx(uint8_t mux_idx);
uint32_t get_curr_cpu_freq_hz(void);
uint8_t clock_mux_cur_sel(clock_mux_sel_id mux_id);
hal_clock_status_t clock_mux_sel(clock_mux_sel_id mux_id, uint32_t mux_sel);
uint32_t hal_clock_freq_meter_data(ref_clock_t ref_clk, hal_src_clock src_clk, uint32_t winset);
uint32_t hal_clock_fqmtr_winset_estimate(uint32_t ref_clk_hz, uint32_t src_clk_hz);
uint32_t hal_clock_get_freq_from_fqmtr_data(uint32_t ref_clk_freq, uint32_t src_clk_fqmtr_data, uint32_t winset);
void clock_dump_info(void);
uint32_t hal_clock_get_lposc_hs_khz(void);
uint32_t hal_clock_get_lposc_ls_khz(void);
uint32_t hal_clock_get_lposc_d3_khz(void);
uint32_t hal_clock_get_lposc_hs_hz(void);
uint32_t hal_clock_get_lposc_ls_hz(void);
uint32_t hal_clock_get_lposc_d3_hz(void);
uint8_t hal_clock_dvfs_get_sys_cfg(void);
uint8_t hal_clock_dvfs_get_cmsys_mux_idx(hal_dvfs_frq_t frq);
void hal_clock_dvfs_switch(hal_dvfs_frq_t frq);
void hal_clock_dvfs_transitive_stage(void);
void hal_clock_sfc_mux_sel_tcm(uint8_t mux_idx);
void hal_clock_chop_ck(bool enable, uint16_t divide_val);
bool hal_clock_out_by_gpio(uint8_t gpio_num, uint8_t clko_sel);
void hal_clock_dcm_enable(clk_dcm_t dcm);
void hal_clock_dcm_disable(clk_dcm_t dcm);
void hal_clock_dcm_ctrl_all(bool enable);
void hal_clock_dcm_primary_div_set(clk_dcm_div_t div);
uint8_t hal_clock_dcm_primary_div_get(void);
void hal_clock_abb_clk_gen_enable(clk_abb_gen_t abb_clk, uint16_t divide_val);
void hal_clock_abb_clk_gen_disable(clk_abb_gen_t abb_clk);
hal_clock_status_t hal_clock_set_lposc_khz(uint32_t khz);
void hal_clock_mux_init(bool IsSrcDBL);
void hal_clock_dcxo_dbl_calibrate(void);
uint16_t hal_clock_get_vcore_mv(void);
clk_bt_rx_adc_t hal_clock_bt_rx_adc_get(void);
hal_clock_status_t hal_clock_bt_rx_adc_set(clk_bt_rx_adc_t rx_adc);
void hal_clock_register_infra_ao_backup_restore(void);
hal_clock_status_t hal_clock_dcxo_dbl64m_re_k(void);
hal_clock_status_t hal_clock_lposc_recali_ctrl(bool start);
void hal_clock_sfc_ctrl(bool enable);

#define hal_clock_get_curr_cpu_freq_hz get_curr_cpu_freq_hz
#define hal_clock_mux_cur_sel          clock_mux_cur_sel
#define hal_clock_mux_sel              clock_mux_sel
#define hal_clock_dump_info            clock_dump_info

#ifdef HAL_DCXO_MODULE_ENABLED
dcxo_mode_t dcxo_current_mode(void);
void dcxo_lp_mode(dcxo_mode_t mode);
uint32_t get_capid_rg(void);
void set_capid_rg(uint32_t capid_val);
uint32_t get_capid_nvdm(void);
int set_capid_nvdm(uint32_t capid_val);
void dcxo_32k_ctrl(uint8_t dcxo32k_en);
bool hal_dcxo_32k_is_enabled(void);
void hal_dcxo_fpm_lock_ctrl(dcxo_fpm_lock_src_t lock_src, dcxo_fpm_lock_op_t lock_op);
uint8_t hal_dcxo_fpm_lock_get_src(void);
//void hal_dcxo_dbl_ctrl(bool enable);
//bool hal_dcxo_dbl_is_enabled(void);
void hal_dcxo_dbg_monitor_ctrl(bool enable, uint8_t select);

#define hal_dcxo_get_pwr_mode          dcxo_current_mode
#define hal_dcxo_set_pwr_mode          dcxo_lp_mode
#define hal_dcxo_get_capid_rg          get_capid_rg
#define hal_dcxo_set_capid_rg          set_capid_rg
#define hal_dcxo_get_capid_nvkey       get_capid_nvdm
#define hal_dcxo_set_capid_nvkey       set_capid_nvdm
#define hal_dcxo_32k_ctrl              dcxo_32k_ctrl
#endif /* HAL_DCXO_MODULE_ENABLED */

#ifdef HAL_DVFS_MODULE_ENABLED
dvfs_frequency_t hal_dvfs_get_cur_sys_opp(void);
hal_dvfs_vcore_t hal_dvfs_get_cur_vcore(void);
hal_dvfs_frq_t hal_dvfs_get_cur_frq(void);
#endif /* HAL_DVFS_MODULE_ENABLED */

#ifdef __cplusplus
}
#endif

#endif /* HAL_CLOCK_MODULE_ENABLED */
#endif /* __HAL_CLOCK_INTERNAL_H__ */

