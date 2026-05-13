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

#ifndef __HAL_SPM_H__
#define __HAL_SPM_H__
#include "hal_sleep_manager.h"
//#include "hal_sleep_manager_platform.h"
//#include "hal_clock_platform.h"
#include "air_chip.h"

#ifdef HAL_SLEEP_MANAGER_ENABLED

#ifdef __cplusplus
extern "C" {
#endif

//#include "hal.h"
#include <stdint.h>


// #define SPM_DVT_TEST

#define INFRA_MISC_CFG 0x422F0000

#define CMSYS_PROT_EN                                                                               (volatile uint32_t*)(INFRA_MISC_CFG + 0x0040 )
#define CMSYS_PROT_RDY                                                                              (volatile uint32_t*)(INFRA_MISC_CFG + 0x0044 )
#define CONNSYS_OFF_PROT_EN                                                                         (volatile uint32_t*)(INFRA_MISC_CFG + 0x0050 )
#define CONNSYS_OFF_PROT_RDY                                                                        (volatile uint32_t*)(INFRA_MISC_CFG + 0x0054 )
#define ZB_TOP_PROT_EN                                                                              (volatile uint32_t*)(INFRA_MISC_CFG + 0x0058 )
#define ZB_TOP_PROT_RDY                                                                             (volatile uint32_t*)(INFRA_MISC_CFG + 0x005C )
#define AUDIO_SYS_TOP_PROT_EN                                                                       (volatile uint32_t*)(INFRA_MISC_CFG + 0x0060 )
#define AUDIO_SYS_TOP_PROT_RDY                                                                      (volatile uint32_t*)(INFRA_MISC_CFG + 0x0064 )
#define INFRAPD_PROT_EN                                                                             (volatile uint32_t*)(INFRA_MISC_CFG + 0x0070 )
#define INFRAPD_PROT_RDY                                                                            (volatile uint32_t*)(INFRA_MISC_CFG + 0x0074 )
#define PERISYS_PROT_EN                                                                             (volatile uint32_t*)(INFRA_MISC_CFG + 0x0078 )
#define PERISYS_PROT_RDY                                                                            (volatile uint32_t*)(INFRA_MISC_CFG + 0x007C )

#define MCU_CFG_PRI_BASE_BASE 0x422E0000

#define CMCFG_BOOT_VECTOR0                                                                          (volatile uint32_t*)(MCU_CFG_PRI_BASE + 0x0000)
#define CMCFG_BOOT_VECTOR1                                                                          (volatile uint32_t*)(MCU_CFG_PRI_BASE + 0x0004)
#define CMCFG_BOOT_FROM_SLV                                                                         (volatile uint32_t*)(MCU_CFG_PRI_BASE + 0x0008)
#define RISCV_CFG_BOOT_VECTOR                                                                        (volatile uint32_t*)(MCU_CFG_PRI_BASE + 0x0010)
#define RISCV_CFG_BOOT_VECTOR_SELECT                                                                 (volatile uint32_t*)(MCU_CFG_PRI_BASE + 0x0014)
#define RISCV_DEEP_SLEEP                                                                             (volatile uint32_t*)(MCU_CFG_PRI_BASE + 0x0018)
#define RISCV_PC                                                                                     (volatile uint32_t*)(MCU_CFG_PRI_BASE + 0x001C)

#define CKSYS_XO_CRTL 0x42040000

#define XO_PDN_TOP_SETD0                                                                            (volatile uint32_t*)( CKSYS_XO_CRTL + 0xb70)
#define XO_PDN_TOP_CLRD0                                                                            (volatile uint32_t*)( CKSYS_XO_CRTL + 0xb80)

/* RTC_DIG_MISC_BASE is defined in air_chip.h */
#define RTCSYS_PWR_CTRL                                                                             (volatile uint32_t*)(RTC_DIG_MISC_BASE + 0x48)

#define HAL_SPM_DEEBUG_ENABLE
#ifdef  HAL_SPM_DEEBUG_ENABLE
#define log_hal_debug(_message,...)                printf(_message, ##__VA_ARGS__)
#define SPM_SET_CMSYS_SW_STATE(x)                   *(SPM_TOP_STATE_STATUS) = (x + 0x80)
#else
#define log_hal_debug(_message,...)
#define SPM_SET_CMSYS_SW_STATE(x)
#endif

int spm_init(void);

typedef enum {
    SPM_MTCMOS_AUDIO_SYS       = 0,
    SPM_MTCMOS_CONN_TOP_OFF    = 1,
    SPM_MTCMOS_CONN_ZIGBEE     = 2,
    SPM_MTCMOS_PERISYS         = 3,
    SPM_MTCMOS_RTCSYS          = 4,
    SPM_MTCMOS_MAX
} spm_mtcmos_type_t;

typedef enum {
    CMSYS_FORCE_ON                     = 0,
    INFRA_PD_FORCE_ON                  = 8,
    CONN_TOP_OFF_FORCE_ON              = 24,
} spm_mtcmos_force_on_t;

typedef enum {
    SPM_SLP_REQUEST                    = 0,
    SPM_SARADC_REQUEST                 = 1,
    SPM_FORCE_ON_REQUEST_MAX
} spm_mtcmos_force_on_request_t;

typedef enum {
    SPM_MTCMOS_PWR_DISABLE  = 0,
    SPM_MTCMOS_PWR_ENABLE   = 1,
    SPM_MTCMOS_PWR_ERROR   = 0xFFFFFFFF
} spm_mtcmos_ctrl_t;

typedef enum {
    SPM_DISABLE  = 0,
    SPM_ENABLE   = 1
} spm_ctrl_t;

typedef enum {
    SPM_STATE1      = 0,
    SPM_STATE2      = 1,
    SPM_STATE3      = 2,
    SPM_STATE4      = 3,
    SPM_STATE6      = 5,
    SPM_STATE7      = 6,
    SPM_STATE_MAX   = 7
} spm_sleep_state_t;

//TODO
typedef enum {
    SPM_AUDIO_REQUEST   = 0,
    SPM_PMIC_REQUEST    = 1,
    SPM_ISINK_REQUEST   = 2,
    SPM_I2S_CLK_OUTPUT  = 3,
    SPM_RTC             = 4,
    SPM_REQUEST_MAX     = 5,
} spm_request_t;

typedef enum {
    SPM_LPOSC_RDY       = 1,
    SPM_XO_RDY          = 2
} spm_clk_rdy_t;

typedef enum {
    SPM_IRRX_FLAG            = 0,
    SPM_PERI_CONTROL_FLAG    = 1,
    SPM_FLAG_MAX             = 2,
} spm_flag_t;

int spm_init(void);
uint32_t spm_control_mtcmos(spm_mtcmos_type_t mtcmos, spm_mtcmos_ctrl_t ctrl);
void spm_control_mtcmos_internal(spm_mtcmos_type_t mtcmos, spm_mtcmos_ctrl_t ctrl);
void spm_mtcmos_default_init(void);

void subsys_sram_all_power_down(void);
void subsys_sram_all_power_on(void);
void subsys_sram_all_retention(void);

void infra_irtx_sram_power_down(void);
void infra_irtx_sram_retention(void);
void infra_irtx_sram_power_on(void);
void perisys_usb_sram_power_down(void);
void perisys_usb_sram_retention(void);
void perisys_usb_sram_power_on(void);
void audio_memif_sram_power_down(void);
void audio_memif_sram_retention(void);
void audio_memif_sram_power_on(void);
void cmsys_rom_0_sram_power_down(void);
void cmsys_rom_0_sram_power_on(void);
void cmsys_rom_1_sram_power_down(void);
void cmsys_rom_1_sram_power_on(void);
void cmsys_tcm2k_0_sram_power_down(void);
void cmsys_tcm2k_0_sram_retention(void);
void cmsys_tcm2k_0_sram_power_on(void);
void cmsys_tcm2k_1_sram_power_down(void);
void cmsys_tcm2k_1_sram_retention(void);
void cmsys_tcm2k_1_sram_power_on(void);
void cmsys_tcm2k_2_sram_power_down(void);
void cmsys_tcm2k_2_sram_retention(void);
void cmsys_tcm2k_2_sram_power_on(void);
void cmsys_tcm2k_3_sram_power_down(void);
void cmsys_tcm2k_3_sram_retention(void);
void cmsys_tcm2k_3_sram_power_on(void);
void cmsys_tcm4k_0_sram_power_down(void);
void cmsys_tcm4k_0_sram_retention(void);
void cmsys_tcm4k_0_sram_power_on(void);
void cmsys_tcm4k_1_sram_power_down(void);
void cmsys_tcm4k_1_sram_retention(void);
void cmsys_tcm4k_1_sram_power_on(void);

void sysram_5_1_force_off(void);
void sysram_5_1_power_down(void);
void sysram_5_0_force_off(void);
void sysram_5_0_power_down(void);
void sysram_4_1_force_off(void);
void sysram_4_1_power_down(void);
void sysram_4_0_force_off(void);
void sysram_4_0_power_down(void);
void sysram_3_3_force_off(void);
void sysram_3_3_power_down(void);
void sysram_3_2_force_off(void);
void sysram_3_2_power_down(void);
void sysram_3_1_force_off(void);
void sysram_3_1_power_down(void);
void sysram_3_0_force_off(void);
void sysram_3_0_power_down(void);
void sysram_2_3_force_off(void);
void sysram_2_3_power_down(void);
void sysram_2_2_force_off(void);
void sysram_2_2_power_down(void);
void sysram_2_1_force_off(void);
void sysram_2_1_power_down(void);
void sysram_2_0_force_off(void);
void sysram_2_0_power_down(void);
void sysram_1_3_force_off(void);
void sysram_1_3_power_down(void);
void sysram_1_2_force_off(void);
void sysram_1_2_power_down(void);
void sysram_1_1_force_off(void);
void sysram_1_1_power_down(void);
void sysram_1_0_force_off(void);
void sysram_1_0_power_down(void);
void sysram_0_3_force_off(void);
void sysram_0_3_power_down(void);
void sysram_0_2_force_off(void);
void sysram_0_2_power_down(void);
void sysram_0_1_force_off(void);
void sysram_0_1_power_down(void);
void sysram_0_0_force_off(void);
void sysram_0_0_power_down(void);
void sysram_5_1_force_on(void);
void sysram_5_1_power_on(void);
void sysram_5_0_force_on(void);
void sysram_5_0_power_on(void);
void sysram_4_1_force_on(void);
void sysram_4_1_power_on(void);
void sysram_4_0_force_on(void);
void sysram_4_0_power_on(void);
void sysram_3_3_force_on(void);
void sysram_3_3_power_on(void);
void sysram_3_2_force_on(void);
void sysram_3_2_power_on(void);
void sysram_3_1_force_on(void);
void sysram_3_1_power_on(void);
void sysram_3_0_force_on(void);
void sysram_3_0_power_on(void);
void sysram_2_3_force_on(void);
void sysram_2_3_power_on(void);
void sysram_2_2_force_on(void);
void sysram_2_2_power_on(void);
void sysram_2_1_force_on(void);
void sysram_2_1_power_on(void);
void sysram_2_0_force_on(void);
void sysram_2_0_power_on(void);
void sysram_1_3_force_on(void);
void sysram_1_3_power_on(void);
void sysram_1_2_force_on(void);
void sysram_1_2_power_on(void);
void sysram_1_1_force_on(void);
void sysram_1_1_power_on(void);
void sysram_1_0_force_on(void);
void sysram_1_0_power_on(void);
void sysram_0_3_force_on(void);
void sysram_0_3_power_on(void);
void sysram_0_2_force_on(void);
void sysram_0_2_power_on(void);
void sysram_0_1_force_on(void);
void sysram_0_1_power_on(void);
void sysram_0_0_force_on(void);
void sysram_0_0_power_on(void);

void sysram_force_off_unused_ram(uint32_t used_ram_start_addr, uint32_t used_ram_end_addr);
void sysram_power_down_ram(uint32_t start_addr, uint32_t end_addr);
void sysram_power_on_ram(uint32_t start_addr, uint32_t end_addr);

void sysram_bt_sram_force_off(void);
void sysram_bt_sram_power_down(void);
void sysram_bt_sram_force_on(void);
void sysram_bt_sram_power_on(void);
void sysram_riscv_0_sram_force_off(void);
void sysram_riscv_0_sram_power_down(void);
void sysram_riscv_0_sram_power_on(void);
void sysram_riscv_0_sram_force_on(void);
void sysram_riscv_1_sram_force_off(void);
void sysram_riscv_1_sram_power_down(void);
void sysram_riscv_1_sram_power_on(void);
void sysram_riscv_1_sram_force_on(void);


void sysram_0_0_force_power_down(void);
void sysram_0_1_force_power_down(void);
void sysram_0_2_force_power_down(void);
void sysram_0_3_force_power_down(void);
void sysram_1_0_force_power_down(void);
void sysram_1_1_force_power_down(void);
void sysram_1_2_force_power_down(void);
void sysram_1_3_force_power_down(void);
void sysram_2_0_force_power_down(void);
void sysram_2_1_force_power_down(void);
void sysram_2_2_force_power_down(void);
void sysram_2_3_force_power_down(void);
void sysram_3_0_force_power_down(void);
void sysram_3_1_force_power_down(void);
void sysram_3_2_force_power_down(void);
void sysram_3_3_force_power_down(void);
void sysram_4_0_force_power_down(void);
void sysram_4_1_force_power_down(void);
void sysram_5_0_force_power_down(void);
void sysram_5_1_force_power_down(void);

void sysram_0_0_force_power_on(void);
void sysram_0_1_force_power_on(void);
void sysram_0_2_force_power_on(void);
void sysram_0_3_force_power_on(void);
void sysram_1_0_force_power_on(void);
void sysram_1_1_force_power_on(void);
void sysram_1_2_force_power_on(void);
void sysram_1_3_force_power_on(void);
void sysram_2_0_force_power_on(void);
void sysram_2_1_force_power_on(void);
void sysram_2_2_force_power_on(void);
void sysram_2_3_force_power_on(void);
void sysram_3_0_force_power_on(void);
void sysram_3_1_force_power_on(void);
void sysram_3_2_force_power_on(void);
void sysram_3_3_force_power_on(void);
void sysram_4_0_force_power_on(void);
void sysram_4_1_force_power_on(void);
void sysram_5_0_force_power_on(void);
void sysram_5_1_force_power_on(void);

void sysram_0_0_enter_non_retention(void);
void sysram_0_1_enter_non_retention(void);
void sysram_0_2_enter_non_retention(void);
void sysram_0_3_enter_non_retention(void);
void sysram_1_0_enter_non_retention(void);
void sysram_1_1_enter_non_retention(void);
void sysram_1_2_enter_non_retention(void);
void sysram_1_3_enter_non_retention(void);
void sysram_2_0_enter_non_retention(void);
void sysram_2_1_enter_non_retention(void);
void sysram_2_2_enter_non_retention(void);
void sysram_2_3_enter_non_retention(void);
void sysram_3_0_enter_non_retention(void);
void sysram_3_1_enter_non_retention(void);
void sysram_3_2_enter_non_retention(void);
void sysram_3_3_enter_non_retention(void);
void sysram_4_0_enter_non_retention(void);
void sysram_4_1_enter_non_retention(void);
void sysram_5_0_enter_non_retention(void);
void sysram_5_1_enter_non_retention(void);

void riscv_sram_all_power_down(void);
void riscv_sram_all_power_on(void);
void bt_sram_all_power_down(void);
void spm_bt_sram_16k_power_down(void);
void spm_bt_sram_16k_power_on(void);

#ifdef SPM_DVT_TEST
void spm_fpga_mtcmos_all_on(void);
#endif

#if 0
void infra_control_dvt(void);
void sleep_control_enter_slp(void);
void sleep_control_enter_ext_slp(void);
#endif

void spm_mask_wakeup_source(volatile uint32_t *wakeup_source_mask_rg, uint32_t wakeup_source);
void spm_unmask_wakeup_source(volatile uint32_t *wakeup_source_mask_rg, uint32_t wakeup_source);
void spm_audio_lowpower_setting(spm_sleep_state_t sleep_state, spm_ctrl_t enable);
int spm_latency_time_checking(void);
bool spm_get_clock_ready(spm_clk_rdy_t spm_clk_rdy);
void spm_enter_usb_suspend(void);
void spm_leave_usb_suspend(void);
void spm_bt_enter_standby_stage(void);
void spm_bt_leave_standby_stage(void);
void spm_mtcmos_force_on(spm_mtcmos_force_on_t processor, spm_ctrl_t enable);
void spm_mtcmos_force_on_infra_pd(spm_mtcmos_force_on_request_t request_handle, spm_ctrl_t enable);

void spm_debug_io(unsigned int debug_bus);
void spm_check_debug_bus(void);
void spm_force_sleep_state(spm_request_t user, spm_sleep_state_t state, spm_ctrl_t enable);

void HW_GPT_callback(void);
void spm_dvt_test_case_select(void);

#ifdef __cplusplus
}
#endif

#endif
#endif