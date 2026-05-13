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

#ifdef HAL_DCXO_MODULE_ENABLED
#include <stdlib.h>
#include "hal_clock_internal.h"

#include <zephyr/sys/printk.h>

#ifdef CONFIG_AIR_NVKEY_ENABLE
#include "nvkey.h"
#include "hal_dcxo_nvkey_struct.h"
#endif

#ifdef HAL_SECURITY_OTP_FEATURE_ENABLE
#include "hal_flash_disk_internal.h"
#endif

#if defined(__EXT_BOOTLOADER__) || defined(__EXT_DA__) || defined(FPGA_ENV)
#define dcxo_prt_info(msg, cnt, ...)
#define dcxo_prt_warn(msg, cnt, ...)
#define dcxo_prt_err(msg, cnt, ...)
#else
//#include "syslog.h"
//#define dcxo_prt_info(msg, cnt, ...)             log_hal_msgid_info("[DCXO] "msg, cnt, ##__VA_ARGS__)
//#define dcxo_prt_warn(msg, cnt, ...)             log_hal_msgid_warning("[DCXO] "msg, cnt, ##__VA_ARGS__)
//#define dcxo_prt_err(msg, cnt, ...)              log_hal_msgid_error("[DCXO] "msg, cnt, ##__VA_ARGS__)
#define dcxo_prt_info(msg, cnt, ...)             printk("[DCXO] "msg"\r\n", ##__VA_ARGS__)
#define dcxo_prt_warn(msg, cnt, ...)             printk("[DCXO] "msg"\r\n", ##__VA_ARGS__)
#define dcxo_prt_err(msg, cnt, ...)              printk("[DCXO] "msg"\r\n", ##__VA_ARGS__)
#endif

#define dcxo_force_prt_info(msg, cnt, ...)       printk("[DCXO] "msg"\r\n", ##__VA_ARGS__)

/* -------------------------------------------------------------------------- */
/* CAPID: 9 bits */
#define CAPID_MAX      511
#define CAPID_MASK     0x1FF

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
dcxo_mode_t dcxo_cur_pwr_mode_general_setting = DCXO_FPM;
uint8_t dcxo_fpm_lock_src = 0; /* default 0 */

/* -------------------------------------------------------------------------- */
ATTR_TEXT_IN_TCM void dcxo_update_fpm_capid(uint16_t capid)
{
    *RTC_DCXO_CON2__DCXO_CDAC_RDY = capid;    /* FPM Capid */
    PTF_DCXO_CTUNE_LPM.DCXO_CDAC_LPM = capid; /* also update LPM Capid */
}

/* Alias: hal_dcxo_get_capid_rg */
uint32_t get_capid_rg(void)
{
    return *RTC_DCXO_CON2__DCXO_CDAC_RDY;
}

/* Alias: hal_dcxo_set_capid_rg */
void set_capid_rg(uint32_t capid_val)
{
    dcxo_update_fpm_capid(capid_val);
}

/* Alias: hal_dcxo_get_capid_nvkey */
uint32_t get_capid_nvdm(void)
{
    uint32_t capid = 0;

#ifdef CONFIG_AIR_NVKEY_ENABLE
    uint8_t nvkey[4] = {0};
    uint32_t size = sizeof(xo_info_t);
    nvkey_status_t status = nvkey_read_data(NVID_CAL_XO_CAPID, nvkey, &size);

    if(status == NVKEY_STATUS_OK) {
        dcxo_prt_info("Read NVID_CAL_XO_CAPID %02X%02X%02X%02X", 4, nvkey[0], nvkey[1], nvkey[2], nvkey[3]);
        capid = (((xo_info_t *)nvkey)->cap_value) & CAPID_MASK;
    }
    else {
        dcxo_prt_err("nvkey_read_data(NVID_CAL_XO_CAPID) fail %d", 1, status);
    }
#endif
    return capid;
}

/* Alias: hal_dcxo_set_capid_nvkey */
int set_capid_nvdm(uint32_t capid_val)
{
#ifdef CONFIG_AIR_NVKEY_ENABLE
    uint8_t nvkey[4] = {0};
    uint32_t size = sizeof(xo_info_t);
    nvkey_status_t status = nvkey_read_data(NVID_CAL_XO_CAPID, nvkey, &size);

    if(status == NVKEY_STATUS_OK) {
        (((xo_info_t *)nvkey)->cap_value) = capid_val & CAPID_MASK;
        status = nvkey_write_data(NVID_CAL_XO_CAPID, nvkey, size);
        if(status == NVKEY_STATUS_OK) {
            dcxo_prt_info("Write NVID_CAL_XO_CAPID %02X%02X%02X%02X", 4, nvkey[0], nvkey[1], nvkey[2], nvkey[3]);
        }
        else {
            dcxo_prt_err("nvkey_write_data(NVID_CAL_XO_CAPID) fail %d", 1, status);
        }
    }
    else {
        dcxo_prt_err("nvkey_read_data(NVID_CAL_XO_CAPID) fail %d", 1, status);
    }
    return (int)status;
#else
    UNUSED_PARAMETER(capid_val);
    return 0;
#endif
}

/*
void set_capid(void)
{
    if(dcxo_capid) {
        *DCXO_PCON6__DCXO_CAPID_EFUSE = dcxo_capid;
        *DCXO_PCON6__DCXO_CAPID_EFUSE_SEL = 1;
    }
}

uint32_t get_capid(void)
{
    return dcxo_capid;
}
*/

/* Alias: hal_dcxo_32k_ctrl */
void dcxo_32k_ctrl(uint8_t dcxo32k_en)
{
    *DCXO_PCON5__DCXO32K_EN = dcxo32k_en;
}

bool hal_dcxo_32k_is_enabled(void)
{
    return *DCXO_PCON5__DCXO32K_EN;
}

ATTR_TEXT_IN_TCM void dcxo_set_pwr_mode(dcxo_mode_t mode)
{
    *DCXO_PCON5__EN_32M_FPM = mode;
    *DCXO_PCON5__BT_32M_EN = mode;
    dcxo_cur_pwr_mode_general_setting = mode;
}

/* Alias: hal_dcxo_get_pwr_mode */
dcxo_mode_t dcxo_current_mode(void)
{
    if(*DCXO_PCON5__EN_32M_FPM || *DCXO_PCON5__BT_32M_EN) {
        return DCXO_FPM;
    }
    return DCXO_LPM;
}

/* Alias: hal_dcxo_set_pwr_mode */
ATTR_TEXT_IN_TCM void dcxo_lp_mode(dcxo_mode_t mode)
{
    if((mode == DCXO_LPM) && dcxo_fpm_lock_src) {
        mode = DCXO_FPM;
    }
    dcxo_set_pwr_mode(mode);
}

void set_dcxo_mode_4testonly(dcxo_mode_t mode)
{
    dcxo_lp_mode(mode);
}

/* Full Power Mode Lock/Unlock */
void hal_dcxo_fpm_lock_ctrl(dcxo_fpm_lock_src_t lock_src, dcxo_fpm_lock_op_t lock_op)
{
    if(lock_src >= DCXO_FPM_LOCK_MAX) {
        return;
    }

#if !defined(__EXT_BOOTLOADER__) && !defined(__EXT_DA__)
    uint32_t irq_mask = 0;
    hal_nvic_save_and_set_interrupt_mask(&irq_mask);
    /* ================ Critical Section Start ======================== */
#endif

    if(lock_op == DCXO_FPM_LOCK) {
        dcxo_fpm_lock_src |= (1 << lock_src);
    }
    else { /* DCXO_FPM_UNLOCK */
        dcxo_fpm_lock_src &= ~(1 << lock_src);
    }

#if !defined(__EXT_BOOTLOADER__) && !defined(__EXT_DA__)
    /* ================ Critical Section End ======================== */
    hal_nvic_restore_interrupt_mask(irq_mask);
#endif

    dcxo_mode_t mode = DCXO_FPM;
    if(!dcxo_fpm_lock_src) {
        mode = dcxo_cur_pwr_mode_general_setting;
    }
    *DCXO_PCON5__EN_32M_FPM = mode;
    *DCXO_PCON5__BT_32M_EN = mode;
    dcxo_prt_info("FPM Lock Ctrl %d, %d, CurSrc %x, Mode %d", 4, lock_src, lock_op, dcxo_fpm_lock_src, mode);
}

uint8_t hal_dcxo_fpm_lock_get_src(void)
{
    return dcxo_fpm_lock_src;
}

void hal_dcxo_init(void)
{
    dcxo_prt_info("hal_dcxo_init", 0);

#ifndef FPGA_ENV
    *DCXO_PCON0__GSM_DCXO_CTL_EN = 1;  /* Enable baseband control */
    *DCXO_PCON1__EXT_DCXO_CTL_EN = 1;  /* Enable external control */
#endif

    /* Update Capid from NvKey */
    uint16_t capid_nvkey = get_capid_nvdm();
    if(capid_nvkey) { /* Get capid nvkey successfully */
        dcxo_update_fpm_capid(capid_nvkey);
    }

#ifndef FPGA_ENV
    dcxo_force_prt_info("CAPID RG %d", 1, get_capid_rg());

    /* (FPM ISEL: DCXO_CORE_ISEL_RDY) is HW fixed, just needs to update (LPM ISEL: DCXO_CORE_ISEL_LPM) once */
    PTF_DCXO_CORE_ISEL_LPM.DCXO_CORE_ISEL_LPM = *RTC_DCXO_CON1__DCXO_CORE_ISEL_RDY;

#ifdef HAL_SECURITY_OTP_FEATURE_ENABLE
    /* Update VREF_SEL and DCXO_LDO_VREF_SEL from OTP */
    /* [Addr7]bit6: RF FT K flag, [Addr8]bit4~0: DA_VREF_SEL_18, [Addr9]bit3~0: RG_DCXO_LDO_VREF_SEL */
    uint8_t otp_bank0_addr7_data[3];
    if(hal_flash_otp_read(7, otp_bank0_addr7_data, 3) == HAL_FLASH_STATUS_OK) {
        dcxo_prt_info("otp_bank0_addr7_data: 0x%02X, 0x%02X, 0x%02X", 3, otp_bank0_addr7_data[0], otp_bank0_addr7_data[1], otp_bank0_addr7_data[2]);
        if(!(otp_bank0_addr7_data[0] & _U8_B6_)) {                              /* bit[6]:   RF FT K flag = 0? */
            *RTC_DCXO_CON3__VREF_SEL = otp_bank0_addr7_data[1] & 0x1F;          /* bit[4:0]: DA_VREF_SEL_18 */
            *RTC_DCXO_CON3__DCXO_LDO_VREF_SEL = otp_bank0_addr7_data[2] & 0x0F; /* bit[3:0]: RG_DCXO_LDO_VREF_SEL */
        }
        else {
            dcxo_prt_err("RF FT K flag=1", 0);
        }
    }
    else {
        dcxo_prt_err("hal_flash_otp_read fail", 0);
    }
#endif

    *RTC_DCXO_CON0__RFLDO_RDY_CNT = 1;
    *RTC_DCXO_CON0__DCXO_BB_RDY_CNT = 0;

    /* Sleep -> Wakeup, delay count for 32M ready */
//    *RTC_DCXO_CON0__DCXO_RDY_CNT = 0;  /* When DCXO 32K used */
    *RTC_DCXO_CON0__DCXO_RDY_CNT = 7;    /* When DCXO 32K unused, 7T = 7 x (1/32768) ~= 213.6us */

    *DCXO_CFG_RST__DCXO_CFG_SW_RSTB = 1; /* DCXO CFG won't be reset when sleep (for RX ADC Clock) */
    PTF_DCXO_RG3.RG_RFLDO_VSEL = 1;  /* 0.88v */

    /* Calibrate DCXO DBL, enable and switch some clock mux using it */
    dcxo_force_prt_info("DBL Calibrate", 0);
    *RTC_DCXO_CON4__DBL_64M_EN = 0;
    hal_clock_dcxo_dbl_calibrate();
    *RTC_DCXO_CON4__DBL_64M_EN = 1;
    //dcxo_force_prt_info("DCXO_DBL_OUT0 0x%08X", 1, PT_DCXO_DBL_OUT0->value);
    //dcxo_force_prt_info("DCXO_DBL_OUT1 0x%08X", 1, PT_DCXO_DBL_OUT1->value);
    //dcxo_force_prt_info("DCXO_DBL_MISC0 0x%08X", 1, *DCXO_DBL_MISC0__DCXO_DBL_MISC0);
#if defined(__EXT_BOOTLOADER__) || defined(__EXT_DA__)
    hal_clock_mux_sel(CLK_USB_SEL, MUX_USB_IDX_XO_DBL);
#else
    hal_clock_mux_init(true);
#endif

#if defined(__EXT_BOOTLOADER__) || defined(__EXT_DA__)
    dcxo_force_prt_info("Info: SYS %d KHz, SFC %d KHz, Vcore %d mv", 3, hal_clock_get_freq_meter(hf_fsys_ck, 10000), hal_clock_get_freq_meter(hf_fsfc_ck, 10000), hal_clock_get_vcore_mv());
#else
    hal_clock_register_infra_ao_backup_restore();
#endif
#endif /* !FPGA_ENV */
}

#ifndef FPGA_ENV
/*
void hal_dcxo_dbl_ctrl(bool enable)
{
    *RTC_DCXO_CON4__DBL_64M_EN = enable;
}

bool hal_dcxo_dbl_is_enabled(void)
{
    return *RTC_DCXO_CON4__DBL_64M_EN;
}
*/
/* === Monitor select: dcxo_debug_10 ===            order of signal on
  ----------------------------------------------------------------------
    DEBUGMON7 (GPIO 7+16N=7,17,39)   osc_rdy                5
    DEBUGMON6 (GPIO 6+16N=6,16,38)   DCXO_DELAY             4
    DEBUGMON4 (GPIO 4+16N=4,27,36)   EN_RF_LDO              3
    DEBUGMON3 (GPIO 3+16N=3,26,35)   EN_BB                  3
    DEBUGMON2 (GPIO 2+16N=2,31,34)   EN_BG                  2
    DEBUGMON0 (GPIO 0+16N=0,29,32)   md_srclkena_f32k       1
*/
void hal_dcxo_dbg_monitor_ctrl(bool enable, uint8_t select)
{
    if(enable) {
        *TOP_DEBUG_CTRL__TOP_DEBUG_CTRL = 5;
        *DCXO_DEBUG0__DCXO_DEBUG_SEL = select;
        hal_clock_enable(HAL_CLOCK_CG_CKSYS_DEBUG_DIS);
    }
    else {
        *TOP_DEBUG_CTRL__TOP_DEBUG_CTRL = 0;
        *DCXO_DEBUG0__DCXO_DEBUG_SEL = 0;
        hal_clock_disable(HAL_CLOCK_CG_CKSYS_DEBUG_DIS);
    }
    *DCXO_DEBUG0__DCXO_DEBUG_EN = enable;
}
#endif /* !FPGA_ENV */

/*****************************************************************************
 * RACE command
 *****************************************************************************/
#if defined(AIR_RACE_CMD_ENABLE) && !defined(FPGA_ENV)
#include "race_cmd_feature.h"
#ifdef RACE_CLOCK_CMD_ENABLE
#include "race_cmd_clock.h"

/* "Toggle Mode Periodically" Time Interval: 2ms ~ 10s */
#define DCXO_TOGGLE_MODE_TIME_INV_MS_MIN  2
#define DCXO_TOGGLE_MODE_TIME_INV_MS_MAX  10000

#define DCXO_GPT_PORT                     HAL_GPT_0
#define DCXO_RPT_TIMER_2TARGET_CAPID_US   30

dcxo_mode_t dcxo_cur_mode = DCXO_NORMAL_MODE;
uint16_t dcxo_target_capid;

void dcxo_toggle_mode(void *user_data)
{
    UNUSED_PARAMETER(user_data);
    dcxo_cur_mode ^= 1;
    set_dcxo_mode_4testonly(dcxo_cur_mode);
}

void dcxo_fpm_step2target_capid(void *user_data)
{
    UNUSED_PARAMETER(user_data);
    if(*RTC_DCXO_CON2__DCXO_CDAC_RDY < dcxo_target_capid) {
        (*RTC_DCXO_CON2__DCXO_CDAC_RDY) ++;
    }
    else if(*RTC_DCXO_CON2__DCXO_CDAC_RDY > dcxo_target_capid) {
        (*RTC_DCXO_CON2__DCXO_CDAC_RDY) --;
    }
    else {
        hal_gpt_stop_timer(DCXO_GPT_PORT);
        hal_gpt_deinit(DCXO_GPT_PORT);
        dcxo_prt_info("dcxo_fpm_step2target_capid %d done (RG_CAPID %d)", 2, dcxo_target_capid, *RTC_DCXO_CON2__DCXO_CDAC_RDY);
    }
}

/* RACE DCXO Sub Command */
#define DCXO_RACE_COMMAND_SLIM
enum {
    DCXO_SUB_CMD_GET_MODE         = 0, /* CMD: 05 5A 03 00 C1 02 00           RSP: 05 5B 04 00 C1 02 00 00/01 */
    DCXO_SUB_CMD_SET_MODE         = 1, /* CMD: 05 5A 04 00 C1 02 01 00/01     RSP: 05 5B 04 00 C1 02 01 00    */
    DCXO_SUB_CMD_TOGGLE_MODE      = 2, /* CMD: 05 5A 05 00 C1 02 02 TT TT     RSP: 05 5B 04 00 C1 02 02 00/01 */
    DCXO_SUB_CMD_STEP_CAPID       = 3, /* CMD: 05 5A 05 00 C1 02 03 PP PP     RSP: 05 5B 04 00 C1 02 03 00/01 */
    DCXO_SUB_CMD_STOP_TIMER       = 4, /* CMD: 05 5A 03 00 C1 02 04           RSP: 05 5B 04 00 C1 02 04 00    */
    DCXO_SUB_CMD_GET_FPM_LOCK_SRC = 5, /* CMD: 05 5A 03 00 C1 02 05           RSP: 05 5B 04 00 C1 02 05 SS    */
    DCXO_SUB_CMD_SET_FPM_LOCK_SRC = 6, /* CMD: 05 5A 05 00 C1 02 06 SS 00/01  RSP: 05 5B 04 00 C1 02 06 00    */
#ifndef DCXO_RACE_COMMAND_SLIM
    DCXO_SUB_CMD_GET_32K          = 7, /* CMD: 05 5A 03 00 C1 02 07           RSP: 05 5B 04 00 C1 02 07 00/01 */
    DCXO_SUB_CMD_SET_32K          = 8  /* CMD: 05 5A 04 00 C1 02 08 00/01     RSP: 05 5B 04 00 C1 02 08 00    */
#endif
};

void hal_dcxo_deinit_gpt_port(void)
{
    hal_gpt_running_status_t gpt_running_status;

    if (hal_gpt_get_running_status(DCXO_GPT_PORT, &gpt_running_status) == HAL_GPT_STATUS_OK) {
        if (gpt_running_status == HAL_GPT_RUNNING) {
            hal_gpt_stop_timer(DCXO_GPT_PORT);
        }
        hal_gpt_deinit(DCXO_GPT_PORT);
    }
}

void *hal_dcxo_race_handler(ptr_race_pkt_t pCmdMsg, uint8_t channel_id)
{
    uint8_t *pPayload = pCmdMsg->payload;
    uint8_t  sub_cmd = pPayload[0];
    bool     data_len_err = false, mem_alloc_fail = false;
    void    *pRtnPayload = NULL;
    uint16_t data_len = pCmdMsg->hdr.length - 2; /* not count RACE ID */
    uint16_t wTemp;
    uint8_t  i, bTemp;
    dcxo_mode_t pwr_mode;

    if (data_len) {
        switch (sub_cmd) {
            case DCXO_SUB_CMD_GET_MODE:
                race_clk_log_info("DCXO_GET_MODE", 0);
                pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                    (uint8_t)RACE_TYPE_RESPONSE,
                                                    (uint16_t)RACE_ID_DCXO,
                                                    (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                    channel_id);
                if (pRtnPayload) {
                    pwr_mode = dcxo_current_mode();
                    ((race_clk_common_uint8_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                    ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)pwr_mode;
                    race_clk_log_info("DCXO mode %d", 1, pwr_mode);
                }
                else {
                    mem_alloc_fail = true;
                }
                break;
            case DCXO_SUB_CMD_SET_MODE:
                if (data_len >= 2) {
                    pwr_mode = pPayload[1];
                    race_clk_log_info("DCXO_SET_MODE %d", 1, pwr_mode);
                    if (pwr_mode <= DCXO_NORMAL_MODE) {
                        pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                            (uint8_t)RACE_TYPE_RESPONSE,
                                                            (uint16_t)RACE_ID_DCXO,
                                                            (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                            channel_id);
                        if (pRtnPayload) {
                            set_dcxo_mode_4testonly(pwr_mode);
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_SUCCESS;
                            race_clk_log_info("DCXO mode %d", 1, dcxo_current_mode());
                        }
                        else {
                            mem_alloc_fail = true;
                        }
                    }
                    else {
                        race_clk_log_err("Invalid DCXO mode value", 0);
                    }
                }
                else {
                    data_len_err = true;
                }
                break;
            case DCXO_SUB_CMD_TOGGLE_MODE:
                if (data_len >= 3) {
                    wTemp = *(uint16_t *)&pPayload[1];
                    race_clk_log_info("DCXO_TOGGLE_MODE %d", 1, wTemp);
                    if ((wTemp >= DCXO_TOGGLE_MODE_TIME_INV_MS_MIN) && (wTemp <= DCXO_TOGGLE_MODE_TIME_INV_MS_MAX)) {
                        pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                            (uint8_t)RACE_TYPE_RESPONSE,
                                                            (uint16_t)RACE_ID_DCXO,
                                                            (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                            channel_id);
                        if (pRtnPayload) {
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                            hal_dcxo_deinit_gpt_port();
                            if (hal_gpt_init(DCXO_GPT_PORT) == HAL_GPT_STATUS_OK) {
                                ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_SUCCESS;
                                dcxo_cur_mode = DCXO_NORMAL_MODE;
                                set_dcxo_mode_4testonly(dcxo_cur_mode);
                                hal_gpt_register_callback(DCXO_GPT_PORT, dcxo_toggle_mode, NULL);
                                hal_gpt_start_timer_ms(DCXO_GPT_PORT, wTemp, HAL_GPT_TIMER_TYPE_REPEAT);
                                race_clk_log_info("DCXO mode toggle per %dms", 1, wTemp);
                            }
                            else {
                                ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_FAIL;
                                race_clk_log_err("GPT init fail", 0);
                            }
                        }
                        else {
                            mem_alloc_fail = true;
                        }
                    }
                    else {
                        race_clk_log_err("Invalid toggle ms timer value", 0);
                    }
                }
                else {
                    data_len_err = true;
                }
                break;
            case DCXO_SUB_CMD_STEP_CAPID:
                if (data_len >= 3) {
                    wTemp = *(uint16_t *)&pPayload[1];
                    race_clk_log_info("DCXO_STEP_CAPID %d", 1, wTemp);
                    if (wTemp <= CAPID_MAX) {
                        pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                            (uint8_t)RACE_TYPE_RESPONSE,
                                                            (uint16_t)RACE_ID_DCXO,
                                                            (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                            channel_id);
                        if (pRtnPayload) {
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                            hal_dcxo_deinit_gpt_port();
                            if (hal_gpt_init(DCXO_GPT_PORT) == HAL_GPT_STATUS_OK) {
                                ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_SUCCESS;
                                dcxo_cur_mode = DCXO_NORMAL_MODE;
                                set_dcxo_mode_4testonly(dcxo_cur_mode);
                                dcxo_target_capid = wTemp;
                                race_clk_log_info("DCXO start step to target capid %d", 1, dcxo_target_capid);
                                hal_gpt_register_callback(DCXO_GPT_PORT, dcxo_fpm_step2target_capid, NULL);
                                hal_gpt_start_timer_us(DCXO_GPT_PORT, DCXO_RPT_TIMER_2TARGET_CAPID_US, HAL_GPT_TIMER_TYPE_REPEAT);
                            }
                            else {
                                ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_FAIL;
                                race_clk_log_err("GPT init fail", 0);
                            }
                        }
                        else {
                            mem_alloc_fail = true;
                        }
                    }
                    else {
                        race_clk_log_err("Invalid capid value", 0);
                    }
                }
                else {
                    data_len_err = true;
                }
                break;
            case DCXO_SUB_CMD_STOP_TIMER:
                race_clk_log_info("DCXO_STOP_TIMER", 0);
                pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                    (uint8_t)RACE_TYPE_RESPONSE,
                                                    (uint16_t)RACE_ID_DCXO,
                                                    (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                    channel_id);
                if (pRtnPayload) {
                    ((race_clk_common_uint8_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                    ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_SUCCESS;
                    hal_dcxo_deinit_gpt_port();
                    dcxo_cur_mode = DCXO_NORMAL_MODE;
                    set_dcxo_mode_4testonly(dcxo_cur_mode);
                    race_clk_log_info("DCXO mode toggle or step capid timer stop", 0);
                }
                else {
                    mem_alloc_fail = true;
                }
                break;
            case DCXO_SUB_CMD_GET_FPM_LOCK_SRC:
                race_clk_log_info("DCXO_GET_FPM_LOCK_SRC", 0);
                pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                    (uint8_t)RACE_TYPE_RESPONSE,
                                                    (uint16_t)RACE_ID_DCXO,
                                                    (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                    channel_id);
                if (pRtnPayload) {
                    bTemp = hal_dcxo_fpm_lock_get_src();
                    ((race_clk_common_uint8_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                    ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = bTemp;
                    race_clk_log_info("DCXO FPM lock src 0x%02X", 1, bTemp);
                }
                else {
                    mem_alloc_fail = true;
                }
                break;
            case DCXO_SUB_CMD_SET_FPM_LOCK_SRC:
                if (data_len >= 3) {
                    i = pPayload[1];
                    bTemp = pPayload[2];
                    race_clk_log_info("SET_FPM_LOCK_SRC %d, %d", 2, i, bTemp);
                    if ((i < DCXO_FPM_LOCK_MAX) && (bTemp <= DCXO_FPM_LOCK)) {
                        pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                            (uint8_t)RACE_TYPE_RESPONSE,
                                                            (uint16_t)RACE_ID_DCXO,
                                                            (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                            channel_id);
                        if (pRtnPayload) {
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                            hal_dcxo_fpm_lock_ctrl(i, bTemp);
                        }
                        else {
                            mem_alloc_fail = true;
                        }
                    }
                    else {
                        race_clk_log_err("Invalid FPM lock src index or ctrl", 0);
                    }
                }
                else {
                    data_len_err = true;
                }
                break;

#ifndef DCXO_RACE_COMMAND_SLIM
                case DCXO_SUB_CMD_GET_32K:
                race_clk_log_info("DCXO_GET_32K", 0);
                pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                    (uint8_t)RACE_TYPE_RESPONSE,
                                                    (uint16_t)RACE_ID_DCXO,
                                                    (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                    channel_id);
                if (pRtnPayload) {
                    bTemp = hal_dcxo_32k_is_enabled();
                    ((race_clk_common_uint8_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                    ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = bTemp;
                    race_clk_log_info("DCXO 32K %d", 1, bTemp);
                }
                else {
                    mem_alloc_fail = true;
                }
                break;
            case DCXO_SUB_CMD_SET_32K:
                if (data_len >= 2) {
                    bTemp = pPayload[1];
                    race_clk_log_info("DCXO_SET_32K %d", 1, bTemp);
                    if (bTemp <= 1) {
                        pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                            (uint8_t)RACE_TYPE_RESPONSE,
                                                            (uint16_t)RACE_ID_DCXO,
                                                            (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                            channel_id);
                        if (pRtnPayload) {
                            dcxo_32k_ctrl(bTemp);
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_SUCCESS;
                        }
                        else {
                            mem_alloc_fail = true;
                        }
                    }
                    else {
                        race_clk_log_err("Invalid DCXO 32K ctrl", 0);
                    }
                }
                else {
                    data_len_err = true;
                }
                break;
#endif /* !DCXO_RACE_COMMAND_SLIM */

            default:
                race_clk_log_err("DCXO sub_cmd 0x%02X not supported", 1, sub_cmd);
                break;
        }
    }
    else {
        data_len_err = true;
    }
    if (data_len_err) {
        race_clk_log_err("DCXO data_len %d error", 1, data_len);
    }
    if (mem_alloc_fail) {
        race_clk_log_err("DCXO mem alloc fail", 0);
    }
    return pRtnPayload;
}
#endif /* RACE_CLOCK_CMD_ENABLE */
#endif /* AIR_RACE_CMD_ENABLE && !FPGA_ENV */

#endif /* HAL_DCXO_MODULE_ENABLED */

