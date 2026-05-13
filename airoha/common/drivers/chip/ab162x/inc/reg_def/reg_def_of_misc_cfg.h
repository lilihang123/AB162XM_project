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

#ifndef __MISC_CFG_REG_DEFINITION_H__
#define __MISC_CFG_REG_DEFINITION_H__


#include <stdint.h>


/* structure type of top_misc_cfg */
/* rf hde delsel hv */
typedef union {
    struct {
        __IO uint32_t rf_hde_delsel_hv                :19;    /* bits:0-18, Recommended EMA, Read/Write Assist Settings for 0.9V RF_HDE-type SRAM */
        __I  uint32_t __reserved_00                   :13;
    } field;
    __IO uint32_t word;
} RF_HDE_DELSEL_HV_T;

#define RF_HDE_DELSEL_HV_RF_HDE_DELSEL_HV_OFFSET                         (0U)
#define RF_HDE_DELSEL_HV_RF_HDE_DELSEL_HV_MASK                           (0x7FFFFU << RF_HDE_DELSEL_HV_RF_HDE_DELSEL_HV_OFFSET)


/* rf hde delsel lv */
typedef union {
    struct {
        __IO uint32_t rf_hde_delsel_lv                :19;    /* bits:0-18, Recommended EMA, Read/Write Assist Settings for 0.8V RF_HDE-type SRAM */
        __I  uint32_t __reserved_00                   :13;
    } field;
    __IO uint32_t word;
} RF_HDE_DELSEL_LV_T;

#define RF_HDE_DELSEL_LV_RF_HDE_DELSEL_LV_OFFSET                         (0U)
#define RF_HDE_DELSEL_LV_RF_HDE_DELSEL_LV_MASK                           (0x7FFFFU << RF_HDE_DELSEL_LV_RF_HDE_DELSEL_LV_OFFSET)


/* rf uhde delsel hv */
typedef union {
    struct {
        __IO uint32_t rf_uhde_delsel_hv               :19;    /* bits:0-18, Recommended EMA, Read/Write Assist Settings for 0.9V RF_UHDE-type SRAM */
        __I  uint32_t __reserved_00                   :13;
    } field;
    __IO uint32_t word;
} RF_UHDE_DELSEL_HV_T;

#define RF_UHDE_DELSEL_HV_RF_UHDE_DELSEL_HV_OFFSET                       (0U)
#define RF_UHDE_DELSEL_HV_RF_UHDE_DELSEL_HV_MASK                         (0x7FFFFU << RF_UHDE_DELSEL_HV_RF_UHDE_DELSEL_HV_OFFSET)


/* rf uhde delsel lv */
typedef union {
    struct {
        __IO uint32_t rf_uhde_delsel_lv               :19;    /* bits:0-18, Recommended EMA, Read/Write Assist Settings for 0.8V RF_UHDE-type SRAM */
        __I  uint32_t __reserved_00                   :13;
    } field;
    __IO uint32_t word;
} RF_UHDE_DELSEL_LV_T;

#define RF_UHDE_DELSEL_LV_RF_UHDE_DELSEL_LV_OFFSET                       (0U)
#define RF_UHDE_DELSEL_LV_RF_UHDE_DELSEL_LV_MASK                         (0x7FFFFU << RF_UHDE_DELSEL_LV_RF_UHDE_DELSEL_LV_OFFSET)


/* hde sram delsel hv */
typedef union {
    struct {
        __IO uint32_t sram_hde_delsel_hv              :19;    /* bits:0-18, Recommended EMA, Read/Write Assist Settings for 0.9V SRAM_HDE-type SRAM */
        __I  uint32_t __reserved_00                   :13;
    } field;
    __IO uint32_t word;
} SRAM_HDE_DELSEL_HV_T;

#define SRAM_HDE_DELSEL_HV_SRAM_HDE_DELSEL_HV_OFFSET                     (0U)
#define SRAM_HDE_DELSEL_HV_SRAM_HDE_DELSEL_HV_MASK                       (0x7FFFFU << SRAM_HDE_DELSEL_HV_SRAM_HDE_DELSEL_HV_OFFSET)


/* hde sram delsel lv */
typedef union {
    struct {
        __IO uint32_t sram_hde_delsel_lv              :19;    /* bits:0-18, Recommended EMA, Read/Write Assist Settings for 0.8V SRAM_HDE-type SRAM */
        __I  uint32_t __reserved_00                   :13;
    } field;
    __IO uint32_t word;
} SRAM_HDE_DELSEL_LV_T;

#define SRAM_HDE_DELSEL_LV_SRAM_HDE_DELSEL_LV_OFFSET                     (0U)
#define SRAM_HDE_DELSEL_LV_SRAM_HDE_DELSEL_LV_MASK                       (0x7FFFFU << SRAM_HDE_DELSEL_LV_SRAM_HDE_DELSEL_LV_OFFSET)


/* uhde sram delsel hv */
typedef union {
    struct {
        __IO uint32_t sram_uhde_delsel_hv             :19;    /* bits:0-18, Recommended EMA, Read/Write Assist Settings for 0.9V SRAM_UHDE-type SRAM */
        __I  uint32_t __reserved_00                   :13;
    } field;
    __IO uint32_t word;
} SRAM_UHDE_DELSEL_HV_T;

#define SRAM_UHDE_DELSEL_HV_SRAM_UHDE_DELSEL_HV_OFFSET                   (0U)
#define SRAM_UHDE_DELSEL_HV_SRAM_UHDE_DELSEL_HV_MASK                     (0x7FFFFU << SRAM_UHDE_DELSEL_HV_SRAM_UHDE_DELSEL_HV_OFFSET)


/* uhde sram delsel lv */
typedef union {
    struct {
        __IO uint32_t sram_uhde_delsel_lv             :19;    /* bits:0-18, Recommended EMA, Read/Write Assist Settings for 0.8V SRAM_UHDE-type SRAM */
        __I  uint32_t __reserved_00                   :13;
    } field;
    __IO uint32_t word;
} SRAM_UHDE_DELSEL_LV_T;

#define SRAM_UHDE_DELSEL_LV_SRAM_UHDE_DELSEL_LV_OFFSET                   (0U)
#define SRAM_UHDE_DELSEL_LV_SRAM_UHDE_DELSEL_LV_MASK                     (0x7FFFFU << SRAM_UHDE_DELSEL_LV_SRAM_UHDE_DELSEL_LV_OFFSET)


/* sram delsel selection */
typedef union {
    struct {
        __IO uint32_t sram_delsel_sel                 :1;    /* bits:0-0, DELSEL selection 0: 0.9V 1: 0.8V */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} SRAM_DELSEL_SEL_T;

#define SRAM_DELSEL_SEL_SRAM_DELSEL_SEL_OFFSET                           (0U)
#define SRAM_DELSEL_SEL_SRAM_DELSEL_SEL_MASK                             (0x1U << SRAM_DELSEL_SEL_SRAM_DELSEL_SEL_OFFSET)


/* Hardware misc. register */
typedef union {
    struct {
        __IO uint32_t HW_MISC0                        :16;    /* bits:0-15, reserved */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} HW_MISC0_T;

#define HW_MISC0_HW_MISC0_OFFSET                                         (0U)
#define HW_MISC0_HW_MISC0_MASK                                           (0xFFFFU << HW_MISC0_HW_MISC0_OFFSET)


/* Hardware misc. register */
typedef union {
    struct {
        __IO uint32_t HW_MISC1                        :16;    /* bits:0-15, reserved */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} HW_MISC1_T;

#define HW_MISC1_HW_MISC1_OFFSET                                         (0U)
#define HW_MISC1_HW_MISC1_MASK                                           (0xFFFFU << HW_MISC1_HW_MISC1_OFFSET)


/* Hardware misc. register */
typedef union {
    struct {
        __IO uint32_t HW_MISC2                        :16;    /* bits:0-15, reserved */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} HW_MISC2_T;

#define HW_MISC2_HW_MISC2_OFFSET                                         (0U)
#define HW_MISC2_HW_MISC2_MASK                                           (0xFFFFU << HW_MISC2_HW_MISC2_OFFSET)


/* Hardware misc. register */
typedef union {
    struct {
        __IO uint32_t HW_MISC3                        :16;    /* bits:0-15, reserved */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} HW_MISC3_T;

#define HW_MISC3_HW_MISC3_OFFSET                                         (0U)
#define HW_MISC3_HW_MISC3_MASK                                           (0xFFFFU << HW_MISC3_HW_MISC3_OFFSET)


/* software misc. registers */
typedef union {
    struct {
        __IO uint32_t SW_MISC0                        :16;    /* bits:0-15, reserved */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} SW_MISC0_T;

#define SW_MISC0_SW_MISC0_OFFSET                                         (0U)
#define SW_MISC0_SW_MISC0_MASK                                           (0xFFFFU << SW_MISC0_SW_MISC0_OFFSET)


/* BROM control signal */
typedef union {
    struct {
        __IO uint32_t BROM_MISC0                      :16;    /* bits:0-15, reserved */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} BROM_MISC0_T;

#define BROM_MISC0_BROM_MISC0_OFFSET                                     (0U)
#define BROM_MISC0_BROM_MISC0_MASK                                       (0xFFFFU << BROM_MISC0_BROM_MISC0_OFFSET)


/* system bonding and trapping information */
typedef union {
    struct {
        __I  uint32_t SYSTEM_INFO                     :32;    /* bits:0-31, bit[0]: 1 means usb charger is plug-in bit[1]: 1 means chip is trapping to SLT mode bit[7:2]: reserved bit[9:8]: bond_pkg_type0/ bond_pkg_type1 bit[15:12]: trapping mode at TESTMODE(Reserved) bit[20]: 1 means chip is at testmode */
    } field;
    __IO uint32_t word;
} SYSTEM_INFOD_T;

#define SYSTEM_INFOD_SYSTEM_INFO_OFFSET                                  (0U)
#define SYSTEM_INFOD_SYSTEM_INFO_MASK                                    (0xFFFFFFFFU << SYSTEM_INFOD_SYSTEM_INFO_OFFSET)


/* debug signals */
typedef union {
    struct {
        __I  uint32_t TOP_DEBUG_MON                   :16;    /* bits:0-15, reserved */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} TOP_DEBUG_MON_T;

#define TOP_DEBUG_MON_TOP_DEBUG_MON_OFFSET                               (0U)
#define TOP_DEBUG_MON_TOP_DEBUG_MON_MASK                                 (0xFFFFU << TOP_DEBUG_MON_TOP_DEBUG_MON_OFFSET)


/* top debug mux control */
typedef union {
    struct {
        __IO uint32_t TOP_DEBUG_CTRL                  :16;    /* bits:0-15, reserved */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} TOP_DEBUG_CTRL_T;

#define TOP_DEBUG_CTRL_TOP_DEBUG_CTRL_OFFSET                             (0U)
#define TOP_DEBUG_CTRL_TOP_DEBUG_CTRL_MASK                               (0xFFFFU << TOP_DEBUG_CTRL_TOP_DEBUG_CTRL_OFFSET)


/* test normal mode trapping registers */
typedef union {
    struct {
        __IO uint32_t TOP_TRAP_REG_CTRL               :8;    /* bits:0-7, Test normal mode trapping in testmode */
        __IO uint32_t TOP_NM_TRAP_DUMMY_MASK          :1;    /* bits:8-8, keep dummy trapping circuit */
        __I  uint32_t __reserved_00                   :23;
    } field;
    __IO uint32_t word;
} TOP_TRAP_REG_CTRL_T;

#define TOP_TRAP_REG_CTRL_TOP_TRAP_REG_CTRL_OFFSET                       (0U)
#define TOP_TRAP_REG_CTRL_TOP_TRAP_REG_CTRL_MASK                         (0xFFU << TOP_TRAP_REG_CTRL_TOP_TRAP_REG_CTRL_OFFSET)
#define TOP_TRAP_REG_CTRL_TOP_NM_TRAP_DUMMY_MASK_OFFSET                  (8U)
#define TOP_TRAP_REG_CTRL_TOP_NM_TRAP_DUMMY_MASK_MASK                    (0x1U << TOP_TRAP_REG_CTRL_TOP_NM_TRAP_DUMMY_MASK_OFFSET)


/* select the SF PAD at slt/dfunc mode */
typedef union {
    struct {
        __IO uint32_t sfc_slt_sel                     :1;    /* bits:0-0, select the SLT/dfunc SF pad or SIP pad */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} SFC_SLT_SEL_T;

#define SFC_SLT_SEL_SFC_SLT_SEL_OFFSET                                   (0U)
#define SFC_SLT_SEL_SFC_SLT_SEL_MASK                                     (0x1U << SFC_SLT_SEL_SFC_SLT_SEL_OFFSET)


/* slt mode pins exit */
typedef union {
    struct {
        __IO uint32_t exit_slt_mode                   :1;    /* bits:0-0, exit SLT_MODE trapping feature and switch to normal gpio pin mux */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} EXIT_SLT_MODE_T;

#define EXIT_SLT_MODE_EXIT_SLT_MODE_OFFSET                               (0U)
#define EXIT_SLT_MODE_EXIT_SLT_MODE_MASK                                 (0x1U << EXIT_SLT_MODE_EXIT_SLT_MODE_OFFSET)


/* USB control */
typedef union {
    struct {
        __IO uint32_t usb_i2c_mode                    :1;    /* bits:0-0, empty description */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} USB_CTRL_T;

#define USB_CTRL_USB_I2C_MODE_OFFSET                                     (0U)
#define USB_CTRL_USB_I2C_MODE_MASK                                       (0x1U << USB_CTRL_USB_I2C_MODE_OFFSET)


/* test mode control */
typedef union {
    struct {
        __IO uint32_t tm_ctrl                         :16;    /* bits:0-15, Bit[1]: tiu_8bit_mode Bit[0]: test_norm_sel; increase IOMUX ATPG coverage Bit[8]: UPLL_24M_CK_SEL, set 0: Direct Pass, set 1: Enable by Glitch-free Design Bit[9]: UPLL_24M_CLK_EN, set 0: CLK off, set 1: CLK on bit[14]: USB DPHY */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} TM_CTRL_T;

#define TM_CTRL_TM_CTRL_OFFSET                                           (0U)
#define TM_CTRL_TM_CTRL_MASK                                             (0xFFFFU << TM_CTRL_TM_CTRL_OFFSET)


/* test mode clock monitor */
typedef union {
    struct {
        __IO uint32_t tm_ctrl_clock_mon               :16;    /* bits:0-15, Bit[0]: 3: ROSC 2: OCC 1: pad_ck 0: pad_soc_ck */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} TM_CTRL_CK_MON_T;

#define TM_CTRL_CK_MON_TM_CTRL_CLOCK_MON_OFFSET                          (0U)
#define TM_CTRL_CK_MON_TM_CTRL_CLOCK_MON_MASK                            (0xFFFFU << TM_CTRL_CK_MON_TM_CTRL_CLOCK_MON_OFFSET)


/* tmbist control */
typedef union {
    struct {
        __IO uint32_t cr_tmbist_jtag_ctrl             :4;    /* bits:0-3, tmbist 4 pin bit0: jtag_ck bit1: jtag_rst_b bit2: jtag_tms bit3: jtag_tdi */
        __I  uint32_t __reserved_00                   :4;
        __IO uint32_t cr_tmbist_jtag_mode             :1;    /* bits:8-8, sw control for tmbist */
        __I  uint32_t __reserved_01                   :23;
    } field;
    __IO uint32_t word;
} TMBIST_CTRL_T;

#define TMBIST_CTRL_CR_TMBIST_JTAG_CTRL_OFFSET                           (0U)
#define TMBIST_CTRL_CR_TMBIST_JTAG_CTRL_MASK                             (0xFU << TMBIST_CTRL_CR_TMBIST_JTAG_CTRL_OFFSET)
#define TMBIST_CTRL_CR_TMBIST_JTAG_MODE_OFFSET                           (8U)
#define TMBIST_CTRL_CR_TMBIST_JTAG_MODE_MASK                             (0x1U << TMBIST_CTRL_CR_TMBIST_JTAG_MODE_OFFSET)


/* SF IO config registers */
typedef union {
    struct {
        __IO uint32_t SFIO_CFG_WP                     :32;    /* bits:0-31, Bit[17]: IES, set 1: enable pad input, set 0: disable pad input Bit[16]: SMT Bit[15:12]: TDSEL_3, TDSEL_2, TDSEL_2, TDSEL_1 Bit[11:6]: RDSEL_5, RDSEL_4, RDSEL_3, RDSEL_2, RDSEL_1, RDSEL_0 Bit[5]: PUPD, set 0: pull up, set 1: pull down Bit[4]: R1 Bit[3]: R0 Bit[2]: E8 Bit[1]: E4 Bit[0]: E2 */
    } field;
    __IO uint32_t word;
} SFIO_CFG_WP_T;

#define SFIO_CFG_WP_SFIO_CFG_WP_OFFSET                                   (0U)
#define SFIO_CFG_WP_SFIO_CFG_WP_MASK                                     (0xFFFFFFFFU << SFIO_CFG_WP_SFIO_CFG_WP_OFFSET)


/* SF IO config registers */
typedef union {
    struct {
        __IO uint32_t SFIO_CFG_CS                     :32;    /* bits:0-31, Bit[17]: IES, set 1: enable pad input, set 0: disable pad input Bit[16]: SMT Bit[15:12]: TDSEL_3, TDSEL_2, TDSEL_2, TDSEL_1 Bit[11:6]: RDSEL_5, RDSEL_4, RDSEL_3, RDSEL_2, RDSEL_1, RDSEL_0 Bit[5]: PUPD, set 0: pull up, set 1: pull down Bit[4]: R1 Bit[3]: R0 Bit[2]: E8 Bit[1]: E4 Bit[0]: E2 */
    } field;
    __IO uint32_t word;
} SFIO_CFG_CS_T;

#define SFIO_CFG_CS_SFIO_CFG_CS_OFFSET                                   (0U)
#define SFIO_CFG_CS_SFIO_CFG_CS_MASK                                     (0xFFFFFFFFU << SFIO_CFG_CS_SFIO_CFG_CS_OFFSET)


/* SF IO config registers */
typedef union {
    struct {
        __IO uint32_t SFIO_CFG_CK                     :32;    /* bits:0-31, Bit[17]: IES, set 1: enable pad input, set 0: disable pad input Bit[16]: SMT Bit[15:12]: TDSEL_3, TDSEL_2, TDSEL_2, TDSEL_1 Bit[11:6]: RDSEL_5, RDSEL_4, RDSEL_3, RDSEL_2, RDSEL_1, RDSEL_0 Bit[5]: PUPD, set 0: pull up, set 1: pull down Bit[4]: R1 Bit[3]: R0 Bit[2]: E8 Bit[1]: E4 Bit[0]: E2 */
    } field;
    __IO uint32_t word;
} SFIO_CFG_CK_T;

#define SFIO_CFG_CK_SFIO_CFG_CK_OFFSET                                   (0U)
#define SFIO_CFG_CK_SFIO_CFG_CK_MASK                                     (0xFFFFFFFFU << SFIO_CFG_CK_SFIO_CFG_CK_OFFSET)


/* SF IO config registers */
typedef union {
    struct {
        __IO uint32_t SFIO_CFG_IN                     :32;    /* bits:0-31, Bit[17]: IES, set 1: enable pad input, set 0: disable pad input Bit[16]: SMT Bit[15:12]: TDSEL_3, TDSEL_2, TDSEL_2, TDSEL_1 Bit[11:6]: RDSEL_5, RDSEL_4, RDSEL_3, RDSEL_2, RDSEL_1, RDSEL_0 Bit[5]: PUPD, set 0: pull up, set 1: pull down Bit[4]: R1 Bit[3]: R0 Bit[2]: E8 Bit[1]: E4 Bit[0]: E2 */
    } field;
    __IO uint32_t word;
} SFIO_CFG_IN_T;

#define SFIO_CFG_IN_SFIO_CFG_IN_OFFSET                                   (0U)
#define SFIO_CFG_IN_SFIO_CFG_IN_MASK                                     (0xFFFFFFFFU << SFIO_CFG_IN_SFIO_CFG_IN_OFFSET)


/* SF IO config registers */
typedef union {
    struct {
        __IO uint32_t SFIO_CFG_OUT                    :32;    /* bits:0-31, Bit[17]: IES, set 1: enable pad input, set 0: disable pad input Bit[16]: SMT Bit[15:12]: TDSEL_3, TDSEL_2, TDSEL_2, TDSEL_1 Bit[11:6]: RDSEL_5, RDSEL_4, RDSEL_3, RDSEL_2, RDSEL_1, RDSEL_0 Bit[5]: PUPD, set 0: pull up, set 1: pull down Bit[4]: R1 Bit[3]: R0 Bit[2]: E8 Bit[1]: E4 Bit[0]: E2 */
    } field;
    __IO uint32_t word;
} SFIO_CFG_OUT_T;

#define SFIO_CFG_OUT_SFIO_CFG_OUT_OFFSET                                 (0U)
#define SFIO_CFG_OUT_SFIO_CFG_OUT_MASK                                   (0xFFFFFFFFU << SFIO_CFG_OUT_SFIO_CFG_OUT_OFFSET)


/* SF IO config registers */
typedef union {
    struct {
        __IO uint32_t SFIO_CFG_HOLD                   :32;    /* bits:0-31, Bit[17]: IES, set 1: enable pad input, set 0: disable pad input Bit[16]: SMT Bit[15:12]: TDSEL_3, TDSEL_2, TDSEL_2, TDSEL_1 Bit[11:6]: RDSEL_5, RDSEL_4, RDSEL_3, RDSEL_2, RDSEL_1, RDSEL_0 Bit[5]: PUPD, set 0: pull up, set 1: pull down Bit[4]: R1 Bit[3]: R0 Bit[2]: E8 Bit[1]: E4 Bit[0]: E2 */
    } field;
    __IO uint32_t word;
} SFIO_CFG_HOLD_T;

#define SFIO_CFG_HOLD_SFIO_CFG_HOLD_OFFSET                               (0U)
#define SFIO_CFG_HOLD_SFIO_CFG_HOLD_MASK                                 (0xFFFFFFFFU << SFIO_CFG_HOLD_SFIO_CFG_HOLD_OFFSET)


/* VBUS_DET */
typedef union {
    struct {
        __I  uint32_t vbus_detect_staus               :1;    /* bits:0-0, pmic charge detect status */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} VBUS_DET_T;

#define VBUS_DET_VBUS_DETECT_STAUS_OFFSET                                (0U)
#define VBUS_DET_VBUS_DETECT_STAUS_MASK                                  (0x1U << VBUS_DET_VBUS_DETECT_STAUS_OFFSET)


/* ABB_CLK_GEN_CFG_0 */
typedef union {
    struct {
        __IO uint32_t hpbuf_chop_clk100k_90deg_div_en :1;    /* bits:0-0, Enable divider */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t hpbuf_chop_clk100k_90deg_div_chg:1;    /* bits:8-8, Toggle the bit to update the divider ratio */
        __I  uint32_t __reserved_01                   :7;
        __IO uint32_t hpbuf_chop_clk100k_90deg_div_sel:11;    /* bits:16-26, Select the divider ratio 0: 13M/1 1: 13M/2 2: 13M/3 2047: 13M/2048 */
        __I  uint32_t __reserved_02                   :5;
    } field;
    __IO uint32_t word;
} ABB_CLK_GEN_CFG_0_T;

#define ABB_CLK_GEN_CFG_0_HPBUF_CHOP_CLK100K_90DEG_DIV_EN_OFFSET         (0U)
#define ABB_CLK_GEN_CFG_0_HPBUF_CHOP_CLK100K_90DEG_DIV_EN_MASK           (0x1U << ABB_CLK_GEN_CFG_0_HPBUF_CHOP_CLK100K_90DEG_DIV_EN_OFFSET)
#define ABB_CLK_GEN_CFG_0_HPBUF_CHOP_CLK100K_90DEG_DIV_CHG_OFFSET        (8U)
#define ABB_CLK_GEN_CFG_0_HPBUF_CHOP_CLK100K_90DEG_DIV_CHG_MASK          (0x1U << ABB_CLK_GEN_CFG_0_HPBUF_CHOP_CLK100K_90DEG_DIV_CHG_OFFSET)
#define ABB_CLK_GEN_CFG_0_HPBUF_CHOP_CLK100K_90DEG_DIV_SEL_OFFSET        (16U)
#define ABB_CLK_GEN_CFG_0_HPBUF_CHOP_CLK100K_90DEG_DIV_SEL_MASK          (0x7FFU << ABB_CLK_GEN_CFG_0_HPBUF_CHOP_CLK100K_90DEG_DIV_SEL_OFFSET)


/* ABB_CLK_GEN_CFG_1 */
typedef union {
    struct {
        __IO uint32_t ck100k_div_en                   :1;    /* bits:0-0, Enable divider */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t ck100k_div_chg                  :1;    /* bits:8-8, Toggle the bit to update the divider ratio */
        __I  uint32_t __reserved_01                   :7;
        __IO uint32_t ck100k_div_sel                  :11;    /* bits:16-26, Select the divider ratio 0: 13M/1 1: 13M/2 2: 13M/3 2047: 13M/2048 */
        __I  uint32_t __reserved_02                   :5;
    } field;
    __IO uint32_t word;
} ABB_CLK_GEN_CFG_1_T;

#define ABB_CLK_GEN_CFG_1_CK100K_DIV_EN_OFFSET                           (0U)
#define ABB_CLK_GEN_CFG_1_CK100K_DIV_EN_MASK                             (0x1U << ABB_CLK_GEN_CFG_1_CK100K_DIV_EN_OFFSET)
#define ABB_CLK_GEN_CFG_1_CK100K_DIV_CHG_OFFSET                          (8U)
#define ABB_CLK_GEN_CFG_1_CK100K_DIV_CHG_MASK                            (0x1U << ABB_CLK_GEN_CFG_1_CK100K_DIV_CHG_OFFSET)
#define ABB_CLK_GEN_CFG_1_CK100K_DIV_SEL_OFFSET                          (16U)
#define ABB_CLK_GEN_CFG_1_CK100K_DIV_SEL_MASK                            (0x7FFU << ABB_CLK_GEN_CFG_1_CK100K_DIV_SEL_OFFSET)


/* ABB_CLK_GEN_CFG_2 */
typedef union {
    struct {
        __I  uint32_t hpbuf_chop_clk100k_90deg_div_rdy:1;    /* bits:0-0, clock output ready */
        __I  uint32_t __reserved_00                   :7;
        __I  uint32_t ck100k_div_rdy                  :1;    /* bits:8-8, clock output ready */
        __I  uint32_t __reserved_01                   :7;
        __IO uint32_t hpbuf_chop_clk100k_90deg_div_swrst:1;    /* bits:16-16, software reset */
        __I  uint32_t __reserved_02                   :7;
        __IO uint32_t ck100k_div_swrst                :1;    /* bits:24-24, software reset */
        __I  uint32_t __reserved_03                   :7;
    } field;
    __IO uint32_t word;
} ABB_CLK_GEN_CFG_2_T;

#define ABB_CLK_GEN_CFG_2_HPBUF_CHOP_CLK100K_90DEG_DIV_RDY_OFFSET        (0U)
#define ABB_CLK_GEN_CFG_2_HPBUF_CHOP_CLK100K_90DEG_DIV_RDY_MASK          (0x1U << ABB_CLK_GEN_CFG_2_HPBUF_CHOP_CLK100K_90DEG_DIV_RDY_OFFSET)
#define ABB_CLK_GEN_CFG_2_CK100K_DIV_RDY_OFFSET                          (8U)
#define ABB_CLK_GEN_CFG_2_CK100K_DIV_RDY_MASK                            (0x1U << ABB_CLK_GEN_CFG_2_CK100K_DIV_RDY_OFFSET)
#define ABB_CLK_GEN_CFG_2_HPBUF_CHOP_CLK100K_90DEG_DIV_SWRST_OFFSET      (16U)
#define ABB_CLK_GEN_CFG_2_HPBUF_CHOP_CLK100K_90DEG_DIV_SWRST_MASK        (0x1U << ABB_CLK_GEN_CFG_2_HPBUF_CHOP_CLK100K_90DEG_DIV_SWRST_OFFSET)
#define ABB_CLK_GEN_CFG_2_CK100K_DIV_SWRST_OFFSET                        (24U)
#define ABB_CLK_GEN_CFG_2_CK100K_DIV_SWRST_MASK                          (0x1U << ABB_CLK_GEN_CFG_2_CK100K_DIV_SWRST_OFFSET)


/* ABB_CLK_GEN_CFG_3 */
typedef union {
    struct {
        __IO uint32_t aud01adc_test_sel               :1;    /* bits:0-0, select normal/test clock */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t aud23adc_test_sel               :1;    /* bits:8-8, select normal/test clock */
        __I  uint32_t __reserved_01                   :7;
        __IO uint32_t dbg_clk_out_en                  :1;    /* bits:16-16, enable debug clock out */
        __I  uint32_t __reserved_02                   :15;
    } field;
    __IO uint32_t word;
} ABB_CLK_GEN_CFG_3_T;

#define ABB_CLK_GEN_CFG_3_AUD01ADC_TEST_SEL_OFFSET                       (0U)
#define ABB_CLK_GEN_CFG_3_AUD01ADC_TEST_SEL_MASK                         (0x1U << ABB_CLK_GEN_CFG_3_AUD01ADC_TEST_SEL_OFFSET)
#define ABB_CLK_GEN_CFG_3_AUD23ADC_TEST_SEL_OFFSET                       (8U)
#define ABB_CLK_GEN_CFG_3_AUD23ADC_TEST_SEL_MASK                         (0x1U << ABB_CLK_GEN_CFG_3_AUD23ADC_TEST_SEL_OFFSET)
#define ABB_CLK_GEN_CFG_3_DBG_CLK_OUT_EN_OFFSET                          (16U)
#define ABB_CLK_GEN_CFG_3_DBG_CLK_OUT_EN_MASK                            (0x1U << ABB_CLK_GEN_CFG_3_DBG_CLK_OUT_EN_OFFSET)


/* SPI bypass mode */
typedef union {
    struct {
        __IO uint32_t SPI_BYPASS_EN                   :1;    /* bits:0-0, bypass mode enable 0: disable 1: enable */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t SPI_BYPASS_MST_SEL              :2;    /* bits:8-9, master select 2'd0: bypass to SPIMST0 2'd1: bypass to SPIMST1 2'd2: bypass to SPIMST2 2'd3: no effect */
        __I  uint32_t __reserved_01                   :6;
        __IO uint32_t SPI_BYPASS_CS_EN                :4;    /* bits:16-19, Bit[19]: enable CS3 Bit[18]: enable CS2 Bit[17]: enable CS1 Bit[16]: enable CS0 0: disable 1: enable */
        __I  uint32_t __reserved_02                   :4;
        __IO uint32_t SPI_BYPASS_OE                   :4;    /* bits:24-27, Bit[27]: SIO3 IO direction Bit[26]: SIO2 IO direction Bit[25]: MISO IO direction Bit[24]: MOSI IO direction 0: input 1: output */
        __I  uint32_t __reserved_03                   :4;
    } field;
    __IO uint32_t word;
} SPI_BYPASS_T;

#define SPI_BYPASS_SPI_BYPASS_EN_OFFSET                                  (0U)
#define SPI_BYPASS_SPI_BYPASS_EN_MASK                                    (0x1U << SPI_BYPASS_SPI_BYPASS_EN_OFFSET)
#define SPI_BYPASS_SPI_BYPASS_MST_SEL_OFFSET                             (8U)
#define SPI_BYPASS_SPI_BYPASS_MST_SEL_MASK                               (0x3U << SPI_BYPASS_SPI_BYPASS_MST_SEL_OFFSET)
#define SPI_BYPASS_SPI_BYPASS_CS_EN_OFFSET                               (16U)
#define SPI_BYPASS_SPI_BYPASS_CS_EN_MASK                                 (0xFU << SPI_BYPASS_SPI_BYPASS_CS_EN_OFFSET)
#define SPI_BYPASS_SPI_BYPASS_OE_OFFSET                                  (24U)
#define SPI_BYPASS_SPI_BYPASS_OE_MASK                                    (0xFU << SPI_BYPASS_SPI_BYPASS_OE_OFFSET)


/* SW_IRQ_0 */
typedef union {
    struct {
        __IO uint32_t sw_irq_0_trig                   :1;    /* bits:0-0, empty description */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t sw_irq_0_sta                    :1;    /* bits:8-8, Software interrupt status. Write 1 to clear interrupt. */
        __I  uint32_t __reserved_01                   :23;
    } field;
    __IO uint32_t word;
} SW_IRQ_0_T;

#define SW_IRQ_0_SW_IRQ_0_TRIG_OFFSET                                    (0U)
#define SW_IRQ_0_SW_IRQ_0_TRIG_MASK                                      (0x1U << SW_IRQ_0_SW_IRQ_0_TRIG_OFFSET)
#define SW_IRQ_0_SW_IRQ_0_STA_OFFSET                                     (8U)
#define SW_IRQ_0_SW_IRQ_0_STA_MASK                                       (0x1U << SW_IRQ_0_SW_IRQ_0_STA_OFFSET)


/* SW_IRQ_1 */
typedef union {
    struct {
        __IO uint32_t sw_irq_1_trig                   :1;    /* bits:0-0, empty description */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t sw_irq_1_sta                    :1;    /* bits:8-8, Software interrupt status. Write 1 to clear interrupt. */
        __I  uint32_t __reserved_01                   :23;
    } field;
    __IO uint32_t word;
} SW_IRQ_1_T;

#define SW_IRQ_1_SW_IRQ_1_TRIG_OFFSET                                    (0U)
#define SW_IRQ_1_SW_IRQ_1_TRIG_MASK                                      (0x1U << SW_IRQ_1_SW_IRQ_1_TRIG_OFFSET)
#define SW_IRQ_1_SW_IRQ_1_STA_OFFSET                                     (8U)
#define SW_IRQ_1_SW_IRQ_1_STA_MASK                                       (0x1U << SW_IRQ_1_SW_IRQ_1_STA_OFFSET)


typedef struct {
    RF_HDE_DELSEL_HV_T                               rf_hde_delsel_hv; /* offset: 0x00000000, rf hde delsel hv */
    RF_HDE_DELSEL_LV_T                               rf_hde_delsel_lv; /* offset: 0x00000004, rf hde delsel lv */
    RF_UHDE_DELSEL_HV_T                             rf_uhde_delsel_hv; /* offset: 0x00000008, rf uhde delsel hv */
    RF_UHDE_DELSEL_LV_T                             rf_uhde_delsel_lv; /* offset: 0x0000000C, rf uhde delsel lv */
    SRAM_HDE_DELSEL_HV_T                           sram_hde_delsel_hv; /* offset: 0x00000010, hde sram delsel hv */
    SRAM_HDE_DELSEL_LV_T                           sram_hde_delsel_lv; /* offset: 0x00000014, hde sram delsel lv */
    SRAM_UHDE_DELSEL_HV_T                         sram_uhde_delsel_hv; /* offset: 0x00000018, uhde sram delsel hv */
    SRAM_UHDE_DELSEL_LV_T                         sram_uhde_delsel_lv; /* offset: 0x0000001C, uhde sram delsel lv */
    SRAM_DELSEL_SEL_T                                 sram_delsel_sel; /* offset: 0x00000020, sram delsel selection */
    uint32_t                                         __reserved_00[3]; /* offset: 0x00000024, padding size: 0x0000000C */
    HW_MISC0_T                                               hw_misc0; /* offset: 0x00000030, Hardware misc. register */
    HW_MISC1_T                                               hw_misc1; /* offset: 0x00000034, Hardware misc. register */
    HW_MISC2_T                                               hw_misc2; /* offset: 0x00000038, Hardware misc. register */
    HW_MISC3_T                                               hw_misc3; /* offset: 0x0000003C, Hardware misc. register */
    SW_MISC0_T                                               sw_misc0; /* offset: 0x00000040, software misc. registers */
    BROM_MISC0_T                                           brom_misc0; /* offset: 0x00000044, BROM control signal */
    uint32_t                                        __reserved_01[46]; /* offset: 0x00000048, padding size: 0x000000B8 */
    SYSTEM_INFOD_T                                       system_infod; /* offset: 0x00000100, system bonding and trapping information */
    TOP_DEBUG_MON_T                                     top_debug_mon; /* offset: 0x00000104, debug signals */
    TOP_DEBUG_CTRL_T                                   top_debug_ctrl; /* offset: 0x00000108, top debug mux control */
    TOP_TRAP_REG_CTRL_T                             top_trap_reg_ctrl; /* offset: 0x0000010C, test normal mode trapping registers */
    SFC_SLT_SEL_T                                         sfc_slt_sel; /* offset: 0x00000110, select the SF PAD at slt/dfunc mode */
    EXIT_SLT_MODE_T                                     exit_slt_mode; /* offset: 0x00000114, slt mode pins exit */
    USB_CTRL_T                                               usb_ctrl; /* offset: 0x00000118, USB control */
    uint32_t                                         __reserved_02[1]; /* offset: 0x0000011C, padding size: 0x00000004 */
    TM_CTRL_T                                                 tm_ctrl; /* offset: 0x00000120, test mode control */
    TM_CTRL_CK_MON_T                                   tm_ctrl_ck_mon; /* offset: 0x00000124, test mode clock monitor */
    TMBIST_CTRL_T                                         tmbist_ctrl; /* offset: 0x00000128, tmbist control */
    uint32_t                                        __reserved_03[53]; /* offset: 0x0000012C, padding size: 0x000000D4 */
    SFIO_CFG_WP_T                                         sfio_cfg_wp; /* offset: 0x00000200, SF IO config registers */
    SFIO_CFG_CS_T                                         sfio_cfg_cs; /* offset: 0x00000204, SF IO config registers */
    SFIO_CFG_CK_T                                         sfio_cfg_ck; /* offset: 0x00000208, SF IO config registers */
    SFIO_CFG_IN_T                                         sfio_cfg_in; /* offset: 0x0000020C, SF IO config registers */
    SFIO_CFG_OUT_T                                       sfio_cfg_out; /* offset: 0x00000210, SF IO config registers */
    SFIO_CFG_HOLD_T                                     sfio_cfg_hold; /* offset: 0x00000214, SF IO config registers */
    uint32_t                                        __reserved_04[58]; /* offset: 0x00000218, padding size: 0x000000E8 */
    VBUS_DET_T                                               vbus_det; /* offset: 0x00000300, VBUS_DET */
    uint32_t                                        __reserved_05[63]; /* offset: 0x00000304, padding size: 0x000000FC */
    ABB_CLK_GEN_CFG_0_T                             abb_clk_gen_cfg_0; /* offset: 0x00000400, ABB_CLK_GEN_CFG_0 */
    ABB_CLK_GEN_CFG_1_T                             abb_clk_gen_cfg_1; /* offset: 0x00000404, ABB_CLK_GEN_CFG_1 */
    ABB_CLK_GEN_CFG_2_T                             abb_clk_gen_cfg_2; /* offset: 0x00000408, ABB_CLK_GEN_CFG_2 */
    ABB_CLK_GEN_CFG_3_T                             abb_clk_gen_cfg_3; /* offset: 0x0000040C, ABB_CLK_GEN_CFG_3 */
    uint32_t                                        __reserved_06[60]; /* offset: 0x00000410, padding size: 0x000000F0 */
    SPI_BYPASS_T                                           spi_bypass; /* offset: 0x00000500, SPI bypass mode */
    uint32_t                                        __reserved_07[63]; /* offset: 0x00000504, padding size: 0x000000FC */
    SW_IRQ_0_T                                               sw_irq_0; /* offset: 0x00000600, SW_IRQ_0 */
    SW_IRQ_1_T                                               sw_irq_1; /* offset: 0x00000604, SW_IRQ_1 */
} TOP_MISC_CFG_REGISTER_T;
#define TOP_MISC_CFG    ((TOP_MISC_CFG_T *)TOP_MISC_CFG_BASE)


/* structure type of TOP_MISC_1_CFG */
/* Hardware misc. register */
typedef union {
    struct {
        __IO uint32_t HW_MISC0                        :16;    /* bits:0-15, Reserved for these 3 bits Bit[0] :set 1 to inverse pmu  goto_sleep signals  Bit[1]: keep dummy trapping circuit Bit[2]: set 1 to ummask conn2pmu_force_buck_pwm */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} HW_MISC1_0_T;

#define HW_MISC1_0_HW_MISC0_OFFSET                                       (0U)
#define HW_MISC1_0_HW_MISC0_MASK                                         (0xFFFFU << HW_MISC1_0_HW_MISC0_OFFSET)


/* Hardware misc. register */
typedef union {
    struct {
        __IO uint32_t HW_MISC1                        :16;    /* bits:0-15, reserved */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} HW_MISC1_1_T;

#define HW_MISC1_1_HW_MISC1_OFFSET                                       (0U)
#define HW_MISC1_1_HW_MISC1_MASK                                         (0xFFFFU << HW_MISC1_1_HW_MISC1_OFFSET)


/* Hardware misc. register */
typedef union {
    struct {
        __IO uint32_t HW_MISC2                        :16;    /* bits:0-15, reserved */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} HW_MISC1_2_T;

#define HW_MISC1_2_HW_MISC2_OFFSET                                       (0U)
#define HW_MISC1_2_HW_MISC2_MASK                                         (0xFFFFU << HW_MISC1_2_HW_MISC2_OFFSET)


/* Hardware misc. register */
typedef union {
    struct {
        __IO uint32_t HW_MISC3                        :16;    /* bits:0-15, reserved */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} HW_MISC1_3_T;

#define HW_MISC1_3_HW_MISC3_OFFSET                                       (0U)
#define HW_MISC1_3_HW_MISC3_MASK                                         (0xFFFFU << HW_MISC1_3_HW_MISC3_OFFSET)


/* software misc. registers */
typedef union {
    struct {
        __IO uint32_t SW_MISC0                        :16;    /* bits:0-15, reserved */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} SW_MISC1_0_T;

#define SW_MISC1_0_SW_MISC0_OFFSET                                       (0U)
#define SW_MISC1_0_SW_MISC0_MASK                                         (0xFFFFU << SW_MISC1_0_SW_MISC0_OFFSET)


/* BROM control signal */
typedef union {
    struct {
        __IO uint32_t BROM_MISC0                      :16;    /* bits:0-15, reserved */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} BROM_MISC1_0_T;

#define BROM_MISC1_0_BROM_MISC0_OFFSET                                   (0U)
#define BROM_MISC1_0_BROM_MISC0_MASK                                     (0xFFFFU << BROM_MISC1_0_BROM_MISC0_OFFSET)


/* SW_IRQ1_0 */
typedef union {
    struct {
        __IO uint32_t sw_irq1_0_trig                  :1;    /* bits:0-0, empty description */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t sw_irq1_0_sta                   :1;    /* bits:8-8, Software interrupt status. Write 1 to clear interrupt. */
        __I  uint32_t __reserved_01                   :23;
    } field;
    __IO uint32_t word;
} SW_IRQ1_0_T;

#define SW_IRQ1_0_SW_IRQ1_0_TRIG_OFFSET                                  (0U)
#define SW_IRQ1_0_SW_IRQ1_0_TRIG_MASK                                    (0x1U << SW_IRQ1_0_SW_IRQ1_0_TRIG_OFFSET)
#define SW_IRQ1_0_SW_IRQ1_0_STA_OFFSET                                   (8U)
#define SW_IRQ1_0_SW_IRQ1_0_STA_MASK                                     (0x1U << SW_IRQ1_0_SW_IRQ1_0_STA_OFFSET)


/* SW_IRQ1_1 */
typedef union {
    struct {
        __IO uint32_t sw_irq1_1_trig                  :1;    /* bits:0-0, empty description */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t sw_irq1_1_sta                   :1;    /* bits:8-8, Software interrupt status. Write 1 to clear interrupt. */
        __I  uint32_t __reserved_01                   :23;
    } field;
    __IO uint32_t word;
} SW_IRQ1_1_T;

#define SW_IRQ1_1_SW_IRQ1_1_TRIG_OFFSET                                  (0U)
#define SW_IRQ1_1_SW_IRQ1_1_TRIG_MASK                                    (0x1U << SW_IRQ1_1_SW_IRQ1_1_TRIG_OFFSET)
#define SW_IRQ1_1_SW_IRQ1_1_STA_OFFSET                                   (8U)
#define SW_IRQ1_1_SW_IRQ1_1_STA_MASK                                     (0x1U << SW_IRQ1_1_SW_IRQ1_1_STA_OFFSET)


typedef struct {
    uint32_t                                        __reserved_00[12]; /* offset: 0x00000000, padding size: 0x00000030 */
    HW_MISC1_0_T                                           hw_misc1_0; /* offset: 0x00000030, Hardware misc. register */
    HW_MISC1_1_T                                           hw_misc1_1; /* offset: 0x00000034, Hardware misc. register */
    HW_MISC1_2_T                                           hw_misc1_2; /* offset: 0x00000038, Hardware misc. register */
    HW_MISC1_3_T                                           hw_misc1_3; /* offset: 0x0000003C, Hardware misc. register */
    SW_MISC1_0_T                                           sw_misc1_0; /* offset: 0x00000040, software misc. registers */
    BROM_MISC1_0_T                                       brom_misc1_0; /* offset: 0x00000044, BROM control signal */
    uint32_t                                       __reserved_01[366]; /* offset: 0x00000048, padding size: 0x000005B8 */
    SW_IRQ1_0_T                                             sw_irq1_0; /* offset: 0x00000600, SW_IRQ1_0 */
    SW_IRQ1_1_T                                             sw_irq1_1; /* offset: 0x00000604, SW_IRQ1_1 */
} TOP_MISC_CFG_1_REGISTER_T;
#define TOP_MISC_CFG_1    ((TOP_MISC_CFG_1_REGISTER_T *)TOP_MISC_CFG_1_BASE)


/* structure type of abb_cfg */
/* ABB Control Register 0 */
typedef union {
    struct {
        __IO uint32_t RG_ABB_RSV18                    :8;    /* bits:0-7, 1.8V domain reserved RG for ABB */
        __IO uint32_t RG_ABB_RSV33                    :8;    /* bits:8-15, 3.3V domain reserved RG for ABB */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} RG_ABB_TOP_0_T;

#define RG_ABB_TOP_0_RG_ABB_RSV18_OFFSET                                 (0U)
#define RG_ABB_TOP_0_RG_ABB_RSV18_MASK                                   (0xFFU << RG_ABB_TOP_0_RG_ABB_RSV18_OFFSET)
#define RG_ABB_TOP_0_RG_ABB_RSV33_OFFSET                                 (8U)
#define RG_ABB_TOP_0_RG_ABB_RSV33_MASK                                   (0xFFU << RG_ABB_TOP_0_RG_ABB_RSV33_OFFSET)


/* AUENC Control Register 0 */
typedef union {
    struct {
        __IO uint32_t RG_AUDPREAMPLON                 :1;    /* bits:0-0, Audio CH01 L preamplifier enable 0 disable 1 enable */
        __IO uint32_t RG_AUD_ACC_EN                   :1;    /* bits:1-1, Audio CH01 L ACC couple input 1 AC couple input 0 DC couple input */
        __I  uint32_t __reserved_00                   :1;
        __IO uint32_t RG_AUDPREAMPLPGATEST            :1;    /* bits:3-3, Audio CH01 L preamplifier PGA test enable 0 disable 1 enable */
        __IO uint32_t RG_AUDPREAMP_LP_RSV             :2;    /* bits:4-5, Audio CH01 L preamplifier PGA DC output voltage scale */
        __IO uint32_t RG_AUDPREAMPLINPUTSEL           :2;    /* bits:6-7, Audio CH01  L preamplifier input selection:  (00) None, (01) AIN0, (10) AIN1, (11)  AIN2. */
        __IO uint32_t RG_AUDPREAMPLGAIN               :4;    /* bits:8-11, Audio CH01 L preamplifier gain adjust:  (0000) 0dB, (0001)3dB, (0010) 6dB (0011) 9dB, (0100) 12dB, (0101) 15dB, (0110) 18dB, (0111) 24dB, (1000) 30dB, (1001) 36dB */
        __IO uint32_t RG_AUDADCLPWRUP                 :1;    /* bits:12-12, Audio CH01  L ADC power up 0 Power down. 1 Power on. */
        __IO uint32_t RG_AUDADCLINPUTSEL              :2;    /* bits:13-14, Audio CH01  L ADC input selection:  (00) Idle, (01) AIN0, (10) Left Preamplifier, (11) Idle */
        __IO uint32_t RG_AUDPGA_ACC20K_EN             :1;    /* bits:15-15, Enable  CH01 20K input */
        __I  uint32_t __reserved_01                   :16;
    } field;
    __IO uint32_t word;
} RG_AUENC_CON_0_T;

#define RG_AUENC_CON_0_RG_AUDPREAMPLON_OFFSET                            (0U)
#define RG_AUENC_CON_0_RG_AUDPREAMPLON_MASK                              (0x1U << RG_AUENC_CON_0_RG_AUDPREAMPLON_OFFSET)
#define RG_AUENC_CON_0_RG_AUD_ACC_EN_OFFSET                              (1U)
#define RG_AUENC_CON_0_RG_AUD_ACC_EN_MASK                                (0x1U << RG_AUENC_CON_0_RG_AUD_ACC_EN_OFFSET)
#define RG_AUENC_CON_0_RG_AUDPREAMPLPGATEST_OFFSET                       (3U)
#define RG_AUENC_CON_0_RG_AUDPREAMPLPGATEST_MASK                         (0x1U << RG_AUENC_CON_0_RG_AUDPREAMPLPGATEST_OFFSET)
#define RG_AUENC_CON_0_RG_AUDPREAMP_LP_RSV_OFFSET                        (4U)
#define RG_AUENC_CON_0_RG_AUDPREAMP_LP_RSV_MASK                          (0x3U << RG_AUENC_CON_0_RG_AUDPREAMP_LP_RSV_OFFSET)
#define RG_AUENC_CON_0_RG_AUDPREAMPLINPUTSEL_OFFSET                      (6U)
#define RG_AUENC_CON_0_RG_AUDPREAMPLINPUTSEL_MASK                        (0x3U << RG_AUENC_CON_0_RG_AUDPREAMPLINPUTSEL_OFFSET)
#define RG_AUENC_CON_0_RG_AUDPREAMPLGAIN_OFFSET                          (8U)
#define RG_AUENC_CON_0_RG_AUDPREAMPLGAIN_MASK                            (0xFU << RG_AUENC_CON_0_RG_AUDPREAMPLGAIN_OFFSET)
#define RG_AUENC_CON_0_RG_AUDADCLPWRUP_OFFSET                            (12U)
#define RG_AUENC_CON_0_RG_AUDADCLPWRUP_MASK                              (0x1U << RG_AUENC_CON_0_RG_AUDADCLPWRUP_OFFSET)
#define RG_AUENC_CON_0_RG_AUDADCLINPUTSEL_OFFSET                         (13U)
#define RG_AUENC_CON_0_RG_AUDADCLINPUTSEL_MASK                           (0x3U << RG_AUENC_CON_0_RG_AUDADCLINPUTSEL_OFFSET)
#define RG_AUENC_CON_0_RG_AUDPGA_ACC20K_EN_OFFSET                        (15U)
#define RG_AUENC_CON_0_RG_AUDPGA_ACC20K_EN_MASK                          (0x1U << RG_AUENC_CON_0_RG_AUDPGA_ACC20K_EN_OFFSET)


/* AUENC Control Register 1 */
typedef union {
    struct {
        __IO uint32_t RG_AUDULHALFBIAS                :1;    /* bits:0-0, Audio  CH01  uplink halfbias enable  0 normal 1 enable */
        __IO uint32_t RG_AUDPREAMPLP1EN               :1;    /* bits:1-1, Audio  CH01  preamplifier PGA low power mode 1 0 disable 1 enable */
        __IO uint32_t RG_IPB_LP_EN                    :1;    /* bits:2-2, ADC IDACBIAS OP2 LP enable */
        __IO uint32_t RG_AUDADC1STSTAGELPEN           :1;    /* bits:3-3, Audio  CH01  ADC 1st Stage low power enable  0 normal 1 enable */
        __IO uint32_t RG_AUDADC2NDSTAGELPEN           :1;    /* bits:4-4, Audio  CH01  ADC 2nd & 3rd low power enable  0 normal 1 enable */
        __IO uint32_t RG_EN_FLASHLOWLEVEL             :1;    /* bits:5-5, Audio  CH01  ADC flash low power enable  0 normal 1 enable */
        __IO uint32_t RG_AUDPREAMPIDDTEST             :2;    /* bits:6-7, Audio  CH01  preamplifier Idd adjust bits 00: 100%  01: 75%  10: 125%  11: 150% */
        __IO uint32_t RG_AUDADC1STSTAGEIDDTEST        :2;    /* bits:8-9, Audio  CH01  ADC 1st Stage Idd adjust bits 00: 100%  01: 80%  10: 120%  11: 140% */
        __IO uint32_t RG_AUDADC2NDSTAGEIDDTEST        :2;    /* bits:10-11, Audio CH01 ADC FBDAC 0.25FS enable  0 8MHz clock in, 4MHz data out 1 4MHz clock in, 2MHz data out */
        __IO uint32_t RG_AUDADCREFBUFIDDTEST          :2;    /* bits:12-13, Audio  CH01  ADC reference buffer Idd current test selection 00: 100%  01: 80%  10: 120%  11: 140% */
        __IO uint32_t RG_AUDADCFLASHIDDTEST           :2;    /* bits:14-15, Audio  CH01  ADC flash Idd current test selection 00: 100%  01: 80%  10: 120%  11: 140% */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} RG_AUENC_CON_1_T;

#define RG_AUENC_CON_1_RG_AUDULHALFBIAS_OFFSET                           (0U)
#define RG_AUENC_CON_1_RG_AUDULHALFBIAS_MASK                             (0x1U << RG_AUENC_CON_1_RG_AUDULHALFBIAS_OFFSET)
#define RG_AUENC_CON_1_RG_AUDPREAMPLP1EN_OFFSET                          (1U)
#define RG_AUENC_CON_1_RG_AUDPREAMPLP1EN_MASK                            (0x1U << RG_AUENC_CON_1_RG_AUDPREAMPLP1EN_OFFSET)
#define RG_AUENC_CON_1_RG_IPB_LP_EN_OFFSET                               (2U)
#define RG_AUENC_CON_1_RG_IPB_LP_EN_MASK                                 (0x1U << RG_AUENC_CON_1_RG_IPB_LP_EN_OFFSET)
#define RG_AUENC_CON_1_RG_AUDADC1STSTAGELPEN_OFFSET                      (3U)
#define RG_AUENC_CON_1_RG_AUDADC1STSTAGELPEN_MASK                        (0x1U << RG_AUENC_CON_1_RG_AUDADC1STSTAGELPEN_OFFSET)
#define RG_AUENC_CON_1_RG_AUDADC2NDSTAGELPEN_OFFSET                      (4U)
#define RG_AUENC_CON_1_RG_AUDADC2NDSTAGELPEN_MASK                        (0x1U << RG_AUENC_CON_1_RG_AUDADC2NDSTAGELPEN_OFFSET)
#define RG_AUENC_CON_1_RG_EN_FLASHLOWLEVEL_OFFSET                        (5U)
#define RG_AUENC_CON_1_RG_EN_FLASHLOWLEVEL_MASK                          (0x1U << RG_AUENC_CON_1_RG_EN_FLASHLOWLEVEL_OFFSET)
#define RG_AUENC_CON_1_RG_AUDPREAMPIDDTEST_OFFSET                        (6U)
#define RG_AUENC_CON_1_RG_AUDPREAMPIDDTEST_MASK                          (0x3U << RG_AUENC_CON_1_RG_AUDPREAMPIDDTEST_OFFSET)
#define RG_AUENC_CON_1_RG_AUDADC1STSTAGEIDDTEST_OFFSET                   (8U)
#define RG_AUENC_CON_1_RG_AUDADC1STSTAGEIDDTEST_MASK                     (0x3U << RG_AUENC_CON_1_RG_AUDADC1STSTAGEIDDTEST_OFFSET)
#define RG_AUENC_CON_1_RG_AUDADC2NDSTAGEIDDTEST_OFFSET                   (10U)
#define RG_AUENC_CON_1_RG_AUDADC2NDSTAGEIDDTEST_MASK                     (0x3U << RG_AUENC_CON_1_RG_AUDADC2NDSTAGEIDDTEST_OFFSET)
#define RG_AUENC_CON_1_RG_AUDADCREFBUFIDDTEST_OFFSET                     (12U)
#define RG_AUENC_CON_1_RG_AUDADCREFBUFIDDTEST_MASK                       (0x3U << RG_AUENC_CON_1_RG_AUDADCREFBUFIDDTEST_OFFSET)
#define RG_AUENC_CON_1_RG_AUDADCFLASHIDDTEST_OFFSET                      (14U)
#define RG_AUENC_CON_1_RG_AUDADCFLASHIDDTEST_MASK                        (0x3U << RG_AUENC_CON_1_RG_AUDADCFLASHIDDTEST_OFFSET)


/* AUENC Control Register 2 */
typedef union {
    struct {
        __IO uint32_t RG_AUDADCCLKSEL                 :2;    /* bits:0-1, Audio  CH01  ADC clock source 00 8M (default) 01 4M 10 16M 11 None */
        __IO uint32_t RG_AUDADCCLKSOURCE              :2;    /* bits:2-3, Audio  CH01  ADC clock source 00 32MHz from CLKSQ  01 32MHz from CLKSQ test 10 None 11 None */
        __IO uint32_t RG_AUDADC_16MCK_EN              :1;    /* bits:4-4, enable CH01 clock from DL CLKSQ to UL */
        __IO uint32_t RG_AUDADCDAC0P25FS              :1;    /* bits:5-5, Audio CH01 ADC FBDAC 0.25FS enable  0 8MHz clock in, 4MHz data out 1 4MHz clock in, 2MHz data out */
        __IO uint32_t RG_AUDPGAL_ACCFS                :1;    /* bits:6-6, Audio CH01 PGA ACC fast settle */
        __IO uint32_t RG_AUDPREAMP_LOWPEN1            :1;    /* bits:7-7, Audio CH01 PGA Enable for 1/3 current setting */
        __IO uint32_t RG_AUDPREAMP_LOWPEN2            :1;    /* bits:8-8, Audio CH01 PGA Enable for 1/4 current setting */
        __IO uint32_t RG_AUDPREAMP_LOWPEN_ORIGIN      :1;    /* bits:9-9, Enable for 4u current setting */
        __IO uint32_t RG_AUDPREAMP_IN_IMP_EN          :2;    /* bits:10-11, PGA Input Pair Tail Current Boost 00 Disable 01 Itail Size X 1.5 10 Itail Size X 2 11 Itail Size X 2.5 (I x 2.5) */
        __IO uint32_t RG_AUDPREAMP_CM_IMP_EN          :2;    /* bits:12-13, PGA CMFB Tail Current Boost 00 Disable 01 CMFB Itail Size X 1.5 (I x 1.5) 10 CMFB Itail Size X 2 (I x 2) 11 CMFB Itail Size X 2.5 (I x 2.5) */
        __IO uint32_t RG_AUDADC1STSTAGESDENB          :1;    /* bits:14-14, Audio CH01 ADC 1st stage source degenerate enableb 0 Enable 1 Disable */
        __IO uint32_t RG_AUDADC2NDSTAGERESET          :1;    /* bits:15-15, Audio CH01 ADC 2nd stage reset 0 normal 1 Reset */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} RG_AUENC_CON_2_T;

#define RG_AUENC_CON_2_RG_AUDADCCLKSEL_OFFSET                            (0U)
#define RG_AUENC_CON_2_RG_AUDADCCLKSEL_MASK                              (0x3U << RG_AUENC_CON_2_RG_AUDADCCLKSEL_OFFSET)
#define RG_AUENC_CON_2_RG_AUDADCCLKSOURCE_OFFSET                         (2U)
#define RG_AUENC_CON_2_RG_AUDADCCLKSOURCE_MASK                           (0x3U << RG_AUENC_CON_2_RG_AUDADCCLKSOURCE_OFFSET)
#define RG_AUENC_CON_2_RG_AUDADC_16MCK_EN_OFFSET                         (4U)
#define RG_AUENC_CON_2_RG_AUDADC_16MCK_EN_MASK                           (0x1U << RG_AUENC_CON_2_RG_AUDADC_16MCK_EN_OFFSET)
#define RG_AUENC_CON_2_RG_AUDADCDAC0P25FS_OFFSET                         (5U)
#define RG_AUENC_CON_2_RG_AUDADCDAC0P25FS_MASK                           (0x1U << RG_AUENC_CON_2_RG_AUDADCDAC0P25FS_OFFSET)
#define RG_AUENC_CON_2_RG_AUDPGAL_ACCFS_OFFSET                           (6U)
#define RG_AUENC_CON_2_RG_AUDPGAL_ACCFS_MASK                             (0x1U << RG_AUENC_CON_2_RG_AUDPGAL_ACCFS_OFFSET)
#define RG_AUENC_CON_2_RG_AUDPREAMP_LOWPEN1_OFFSET                       (7U)
#define RG_AUENC_CON_2_RG_AUDPREAMP_LOWPEN1_MASK                         (0x1U << RG_AUENC_CON_2_RG_AUDPREAMP_LOWPEN1_OFFSET)
#define RG_AUENC_CON_2_RG_AUDPREAMP_LOWPEN2_OFFSET                       (8U)
#define RG_AUENC_CON_2_RG_AUDPREAMP_LOWPEN2_MASK                         (0x1U << RG_AUENC_CON_2_RG_AUDPREAMP_LOWPEN2_OFFSET)
#define RG_AUENC_CON_2_RG_AUDPREAMP_LOWPEN_ORIGIN_OFFSET                 (9U)
#define RG_AUENC_CON_2_RG_AUDPREAMP_LOWPEN_ORIGIN_MASK                   (0x1U << RG_AUENC_CON_2_RG_AUDPREAMP_LOWPEN_ORIGIN_OFFSET)
#define RG_AUENC_CON_2_RG_AUDPREAMP_IN_IMP_EN_OFFSET                     (10U)
#define RG_AUENC_CON_2_RG_AUDPREAMP_IN_IMP_EN_MASK                       (0x3U << RG_AUENC_CON_2_RG_AUDPREAMP_IN_IMP_EN_OFFSET)
#define RG_AUENC_CON_2_RG_AUDPREAMP_CM_IMP_EN_OFFSET                     (12U)
#define RG_AUENC_CON_2_RG_AUDPREAMP_CM_IMP_EN_MASK                       (0x3U << RG_AUENC_CON_2_RG_AUDPREAMP_CM_IMP_EN_OFFSET)
#define RG_AUENC_CON_2_RG_AUDADC1STSTAGESDENB_OFFSET                     (14U)
#define RG_AUENC_CON_2_RG_AUDADC1STSTAGESDENB_MASK                       (0x1U << RG_AUENC_CON_2_RG_AUDADC1STSTAGESDENB_OFFSET)
#define RG_AUENC_CON_2_RG_AUDADC2NDSTAGERESET_OFFSET                     (15U)
#define RG_AUENC_CON_2_RG_AUDADC2NDSTAGERESET_MASK                       (0x1U << RG_AUENC_CON_2_RG_AUDADC2NDSTAGERESET_OFFSET)


/* AUENC Control Register 3 */
typedef union {
    struct {
        __IO uint32_t RG_AUDADC3RDSTAGERESET          :1;    /* bits:0-0, Audio CH01 ADC 3rd stage reset 0 normal 1 Reset */
        __IO uint32_t RG_AUDADCFSRESET                :1;    /* bits:1-1, Audio CH01 encoder FS reset block model selection */
        __IO uint32_t RG_AUDADCWIDECM                 :1;    /* bits:2-2, Audio CH01 ADC wide common mode enable 0 normal 1 enable */
        __IO uint32_t RG_AUDADCNOPATEST               :1;    /* bits:3-3, Audio CH01 ADC no preamp test 0 Normal ADC Gain 1 6dB ADC Gain */
        __IO uint32_t RG_AUD01ADCBYPASS               :1;    /* bits:4-4, Audio CH01 ADC input resistor bypass enable 0 disable 1 enable */
        __IO uint32_t RG_AUDADCFFBYPASS               :1;    /* bits:5-5, Audio CH01 ADC feed forward bypass 0 no bypass, allow feedforward coefficient to pass signal to ADC flash 1 bypass, don't allow ADC i/p signal to feedforward flash */
        __IO uint32_t RG_AUDADCDACFBCURRENT           :1;    /* bits:6-6, Audio CH01 ADC feedback coefficient */
        __IO uint32_t RG_AUDADCDACIDDTEST             :2;    /* bits:7-8, Audio CH01 ADC-DAC Idd current test selfection 00 Normal 11 -20% DAC f/b current */
        __IO uint32_t RG_AUDADCDACNRZ                 :1;    /* bits:9-9, Audio CH01 ADC DAC in non return to zero mode 0 RZ mode (2I) 1 NRZ mod (I) */
        __IO uint32_t RG_AUDADCNODEM                  :1;    /* bits:10-10, Audio CH01 ADC DEM test */
        __IO uint32_t RG_AUDADCDACTEST                :1;    /* bits:11-11, Audio CH01 ADC DAC test 0 disable 1 enables the data in RG_AUDADCTESTDATA[15:0] to be passed to the DAC */
        __IO uint32_t RG_AUDPREAMP_THD                :4;    /* bits:12-15, PGA output driving select 0000: m=2 0001: m=4 0011: m=6 0111: m=8 1111: m=10 */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} RG_AUENC_CON_3_T;

#define RG_AUENC_CON_3_RG_AUDADC3RDSTAGERESET_OFFSET                     (0U)
#define RG_AUENC_CON_3_RG_AUDADC3RDSTAGERESET_MASK                       (0x1U << RG_AUENC_CON_3_RG_AUDADC3RDSTAGERESET_OFFSET)
#define RG_AUENC_CON_3_RG_AUDADCFSRESET_OFFSET                           (1U)
#define RG_AUENC_CON_3_RG_AUDADCFSRESET_MASK                             (0x1U << RG_AUENC_CON_3_RG_AUDADCFSRESET_OFFSET)
#define RG_AUENC_CON_3_RG_AUDADCWIDECM_OFFSET                            (2U)
#define RG_AUENC_CON_3_RG_AUDADCWIDECM_MASK                              (0x1U << RG_AUENC_CON_3_RG_AUDADCWIDECM_OFFSET)
#define RG_AUENC_CON_3_RG_AUDADCNOPATEST_OFFSET                          (3U)
#define RG_AUENC_CON_3_RG_AUDADCNOPATEST_MASK                            (0x1U << RG_AUENC_CON_3_RG_AUDADCNOPATEST_OFFSET)
#define RG_AUENC_CON_3_RG_AUD01ADCBYPASS_OFFSET                          (4U)
#define RG_AUENC_CON_3_RG_AUD01ADCBYPASS_MASK                            (0x1U << RG_AUENC_CON_3_RG_AUD01ADCBYPASS_OFFSET)
#define RG_AUENC_CON_3_RG_AUDADCFFBYPASS_OFFSET                          (5U)
#define RG_AUENC_CON_3_RG_AUDADCFFBYPASS_MASK                            (0x1U << RG_AUENC_CON_3_RG_AUDADCFFBYPASS_OFFSET)
#define RG_AUENC_CON_3_RG_AUDADCDACFBCURRENT_OFFSET                      (6U)
#define RG_AUENC_CON_3_RG_AUDADCDACFBCURRENT_MASK                        (0x1U << RG_AUENC_CON_3_RG_AUDADCDACFBCURRENT_OFFSET)
#define RG_AUENC_CON_3_RG_AUDADCDACIDDTEST_OFFSET                        (7U)
#define RG_AUENC_CON_3_RG_AUDADCDACIDDTEST_MASK                          (0x3U << RG_AUENC_CON_3_RG_AUDADCDACIDDTEST_OFFSET)
#define RG_AUENC_CON_3_RG_AUDADCDACNRZ_OFFSET                            (9U)
#define RG_AUENC_CON_3_RG_AUDADCDACNRZ_MASK                              (0x1U << RG_AUENC_CON_3_RG_AUDADCDACNRZ_OFFSET)
#define RG_AUENC_CON_3_RG_AUDADCNODEM_OFFSET                             (10U)
#define RG_AUENC_CON_3_RG_AUDADCNODEM_MASK                               (0x1U << RG_AUENC_CON_3_RG_AUDADCNODEM_OFFSET)
#define RG_AUENC_CON_3_RG_AUDADCDACTEST_OFFSET                           (11U)
#define RG_AUENC_CON_3_RG_AUDADCDACTEST_MASK                             (0x1U << RG_AUENC_CON_3_RG_AUDADCDACTEST_OFFSET)
#define RG_AUENC_CON_3_RG_AUDPREAMP_THD_OFFSET                           (12U)
#define RG_AUENC_CON_3_RG_AUDPREAMP_THD_MASK                             (0xFU << RG_AUENC_CON_3_RG_AUDPREAMP_THD_OFFSET)


/* AUENC Control Register 4 */
typedef union {
    struct {
        __IO uint32_t RG_AUDADCTESTDATA               :16;    /* bits:0-15, Audio CH01 ADC test data bits Audio ADC test data bits for both phases of DRTZ DAC. Can enable any current source you choose. */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} RG_AUENC_CON_4_T;

#define RG_AUENC_CON_4_RG_AUDADCTESTDATA_OFFSET                          (0U)
#define RG_AUENC_CON_4_RG_AUDADCTESTDATA_MASK                            (0xFFFFU << RG_AUENC_CON_4_RG_AUDADCTESTDATA_OFFSET)


/* AUENC Control Register 5 */
typedef union {
    struct {
        __IO uint32_t RG_AUDRCTUNEL                   :5;    /* bits:0-4, Audio CH01 L ADC RC tuned value See RG_AUDRCTUNELSE */
        __IO uint32_t RG_AUDRCTUNELSEL                :1;    /* bits:5-5, Audio CH01 L ADC RC tuning select 0 Use auto cal tune bits 1 use RG_AUDRCTUNEL[4:0] */
        __I  uint32_t __reserved_00                   :8;
        __IO uint32_t RG_AUDADCSYNCCLK_INV            :1;    /* bits:14-14, Audio CH01 R ADC SYNCCLK INV */
        __IO uint32_t RG_AUDADCCLKRATEQUARTER         :1;    /* bits:15-15, Audio CH01 clk reset signal for VOW mode& 16M CLK High performance mode/ Normal mode: 0 VOW mode with 4M CLK: 0 VOW mode with 16M CLK: 1 */
        __I  uint32_t __reserved_01                   :16;
    } field;
    __IO uint32_t word;
} RG_AUENC_CON_5_T;

#define RG_AUENC_CON_5_RG_AUDRCTUNEL_OFFSET                              (0U)
#define RG_AUENC_CON_5_RG_AUDRCTUNEL_MASK                                (0x1FU << RG_AUENC_CON_5_RG_AUDRCTUNEL_OFFSET)
#define RG_AUENC_CON_5_RG_AUDRCTUNELSEL_OFFSET                           (5U)
#define RG_AUENC_CON_5_RG_AUDRCTUNELSEL_MASK                             (0x1U << RG_AUENC_CON_5_RG_AUDRCTUNELSEL_OFFSET)
#define RG_AUENC_CON_5_RG_AUDADCSYNCCLK_INV_OFFSET                       (14U)
#define RG_AUENC_CON_5_RG_AUDADCSYNCCLK_INV_MASK                         (0x1U << RG_AUENC_CON_5_RG_AUDADCSYNCCLK_INV_OFFSET)
#define RG_AUENC_CON_5_RG_AUDADCCLKRATEQUARTER_OFFSET                    (15U)
#define RG_AUENC_CON_5_RG_AUDADCCLKRATEQUARTER_MASK                      (0x1U << RG_AUENC_CON_5_RG_AUDADCCLKRATEQUARTER_OFFSET)


/* AUENC Control Register 6 */
typedef union {
    struct {
        __IO uint32_t RG_AUDADCCLKHALFRST             :1;    /* bits:0-0, Audio CH01 clk enable signal for low power mode& 16M CLK VOW High performance mode: 0 Normal mode: 1 VOW mode with 45M CLK: 0 VOW mode with 16M CLK: 1 */
        __IO uint32_t RG_AUDADCCLKRATEHALF            :1;    /* bits:1-1, Audio CH01 clk reset signal for low power mode High performance mode: 0 Normal mode: 1 VOW mode with 4M CLK: 0 VOW mode with 16M CLK: 0 */
        __IO uint32_t RG_EN_VREF0P9                   :1;    /* bits:2-2, Audio CH01 AUDENC XO VOW Clock 32M enable from LFOSC 0: disable 1: enable */
        __IO uint32_t RG_CM_REFGENSEL                 :1;    /* bits:3-3, Audio CH01  uplink common voltage setection 0 Default 1 Setection */
        __IO uint32_t RG_AUDADC_FROM_GPIO             :1;    /* bits:4-4, Audio CH01 ADC clock source  0 from DL 1 from GPIO */
        __IO uint32_t RG_DCCVCMBUFLPMODSEL            :1;    /* bits:5-5, Audio CH01  preamplifier PGA DCC VCM buffer LP MODSEL */
        __IO uint32_t RG_DCCVCMBUFLPSWEN              :1;    /* bits:6-6, Audio CH01 preamplifier PGA DCC VCM buffer SW EN */
        __IO uint32_t RG_CM01STBENH                   :1;    /* bits:7-7, Audio CH01 PGA common mode STB enhancement */
        __IO uint32_t RG_AUDSPAREVA25                 :4;    /* bits:8-11, Audio CH01 RG_AUDSPAREVA25[3:0] */
        __IO uint32_t RG_AUDSPAREVA12                 :4;    /* bits:12-15, Audio CH01 RG_AUDSPAREVA12[3:0] */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} RG_AUENC_CON_6_T;

#define RG_AUENC_CON_6_RG_AUDADCCLKHALFRST_OFFSET                        (0U)
#define RG_AUENC_CON_6_RG_AUDADCCLKHALFRST_MASK                          (0x1U << RG_AUENC_CON_6_RG_AUDADCCLKHALFRST_OFFSET)
#define RG_AUENC_CON_6_RG_AUDADCCLKRATEHALF_OFFSET                       (1U)
#define RG_AUENC_CON_6_RG_AUDADCCLKRATEHALF_MASK                         (0x1U << RG_AUENC_CON_6_RG_AUDADCCLKRATEHALF_OFFSET)
#define RG_AUENC_CON_6_RG_EN_VREF0P9_OFFSET                              (2U)
#define RG_AUENC_CON_6_RG_EN_VREF0P9_MASK                                (0x1U << RG_AUENC_CON_6_RG_EN_VREF0P9_OFFSET)
#define RG_AUENC_CON_6_RG_CM_REFGENSEL_OFFSET                            (3U)
#define RG_AUENC_CON_6_RG_CM_REFGENSEL_MASK                              (0x1U << RG_AUENC_CON_6_RG_CM_REFGENSEL_OFFSET)
#define RG_AUENC_CON_6_RG_AUDADC_FROM_GPIO_OFFSET                        (4U)
#define RG_AUENC_CON_6_RG_AUDADC_FROM_GPIO_MASK                          (0x1U << RG_AUENC_CON_6_RG_AUDADC_FROM_GPIO_OFFSET)
#define RG_AUENC_CON_6_RG_DCCVCMBUFLPMODSEL_OFFSET                       (5U)
#define RG_AUENC_CON_6_RG_DCCVCMBUFLPMODSEL_MASK                         (0x1U << RG_AUENC_CON_6_RG_DCCVCMBUFLPMODSEL_OFFSET)
#define RG_AUENC_CON_6_RG_DCCVCMBUFLPSWEN_OFFSET                         (6U)
#define RG_AUENC_CON_6_RG_DCCVCMBUFLPSWEN_MASK                           (0x1U << RG_AUENC_CON_6_RG_DCCVCMBUFLPSWEN_OFFSET)
#define RG_AUENC_CON_6_RG_CM01STBENH_OFFSET                              (7U)
#define RG_AUENC_CON_6_RG_CM01STBENH_MASK                                (0x1U << RG_AUENC_CON_6_RG_CM01STBENH_OFFSET)
#define RG_AUENC_CON_6_RG_AUDSPAREVA25_OFFSET                            (8U)
#define RG_AUENC_CON_6_RG_AUDSPAREVA25_MASK                              (0xFU << RG_AUENC_CON_6_RG_AUDSPAREVA25_OFFSET)
#define RG_AUENC_CON_6_RG_AUDSPAREVA12_OFFSET                            (12U)
#define RG_AUENC_CON_6_RG_AUDSPAREVA12_MASK                              (0xFU << RG_AUENC_CON_6_RG_AUDSPAREVA12_OFFSET)


/* AUENC Control Register 7 */
typedef union {
    struct {
        __IO uint32_t RG_AUDENCSPAREVA25              :8;    /* bits:0-7, Audio CH01 RG_AUDENCSPAREVA25[7:0] */
        __IO uint32_t RG_AUDENCSPAREVA12              :8;    /* bits:8-15, Audio CH01 RG_AUDENCSPAREVA12[7:0] */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} RG_AUENC_CON_7_T;

#define RG_AUENC_CON_7_RG_AUDENCSPAREVA25_OFFSET                         (0U)
#define RG_AUENC_CON_7_RG_AUDENCSPAREVA25_MASK                           (0xFFU << RG_AUENC_CON_7_RG_AUDENCSPAREVA25_OFFSET)
#define RG_AUENC_CON_7_RG_AUDENCSPAREVA12_OFFSET                         (8U)
#define RG_AUENC_CON_7_RG_AUDENCSPAREVA12_MASK                           (0xFFU << RG_AUENC_CON_7_RG_AUDENCSPAREVA12_OFFSET)


/* AUENC Control Register 8 */
typedef union {
    struct {
        __IO uint32_t RG_LCLDO_ENC_EN                 :1;    /* bits:0-0, Enable for LCLDO_ENC */
        __IO uint32_t RG_LCLDO_PDDIS_EN               :1;    /* bits:1-1, LCLDO Power Down Discharge Enable */
        __IO uint32_t RG_LCLDO_TBST_EN                :1;    /* bits:2-2, LCLDO Transient Boost Enable */
        __IO uint32_t RG_LCLDO_ENC_REMOTE_SENSE       :1;    /* bits:3-3, LCLDO Remote sense function selection, 0: local sense, 1: remote sense */
        __IO uint32_t RG_LCLDO_PDD_TEST               :1;    /* bits:4-4, LCLDO Power Down Disable Test */
        __I  uint32_t __reserved_00                   :27;
    } field;
    __IO uint32_t word;
} RG_AUENC_CON_8_T;

#define RG_AUENC_CON_8_RG_LCLDO_ENC_EN_OFFSET                            (0U)
#define RG_AUENC_CON_8_RG_LCLDO_ENC_EN_MASK                              (0x1U << RG_AUENC_CON_8_RG_LCLDO_ENC_EN_OFFSET)
#define RG_AUENC_CON_8_RG_LCLDO_PDDIS_EN_OFFSET                          (1U)
#define RG_AUENC_CON_8_RG_LCLDO_PDDIS_EN_MASK                            (0x1U << RG_AUENC_CON_8_RG_LCLDO_PDDIS_EN_OFFSET)
#define RG_AUENC_CON_8_RG_LCLDO_TBST_EN_OFFSET                           (2U)
#define RG_AUENC_CON_8_RG_LCLDO_TBST_EN_MASK                             (0x1U << RG_AUENC_CON_8_RG_LCLDO_TBST_EN_OFFSET)
#define RG_AUENC_CON_8_RG_LCLDO_ENC_REMOTE_SENSE_OFFSET                  (3U)
#define RG_AUENC_CON_8_RG_LCLDO_ENC_REMOTE_SENSE_MASK                    (0x1U << RG_AUENC_CON_8_RG_LCLDO_ENC_REMOTE_SENSE_OFFSET)
#define RG_AUENC_CON_8_RG_LCLDO_PDD_TEST_OFFSET                          (4U)
#define RG_AUENC_CON_8_RG_LCLDO_PDD_TEST_MASK                            (0x1U << RG_AUENC_CON_8_RG_LCLDO_PDD_TEST_OFFSET)


/* AUENC Control Register 9 */
typedef union {
    struct {
        __IO uint32_t RG_UL_ATST                      :8;    /* bits:0-7, ATST control */
        __I  uint32_t __reserved_00                   :24;
    } field;
    __IO uint32_t word;
} RG_AUENC_CON_9_T;

#define RG_AUENC_CON_9_RG_UL_ATST_OFFSET                                 (0U)
#define RG_AUENC_CON_9_RG_UL_ATST_MASK                                   (0xFFU << RG_AUENC_CON_9_RG_UL_ATST_OFFSET)


/* AUENC Control Register 11 */
typedef union {
    struct {
        __IO uint32_t RG_AIO_R_MODE_EN                :1;    /* bits:0-0, AIO mode resistor type enable 0: disable 1: enable */
        __IO uint32_t RG_AIO_SC_MODE_EN               :1;    /* bits:1-1, AIO mode switch cap type enable 0: disable 1: enable */
        __IO uint32_t RG_MIC_MODE_EN                  :1;    /* bits:2-2, MIC mode enable */
        __IO uint32_t RG_AIO_DIFF_EN                  :1;    /* bits:3-3, AIO mode differential mode enable 0: single-end 1: differential */
        __IO uint32_t RG_AIO_RIN_SEL                  :2;    /* bits:4-5, AIO mode resistor type input resistance selection 00:500K 01:1M 10:1.5M 11:inf(open) */
        __IO uint32_t RG_AIO_RTEMP_SEL                :2;    /* bits:6-7, AIO mode temperature sensor resistance selection 00:50K */
        __IO uint32_t RG_PGA_CHOP_EN                  :1;    /* bits:8-8, PGA chopper enable */
        __IO uint32_t RG_AIO_RTB_SHORT_EN             :1;    /* bits:9-9, AIO mode resistor type gain selection 1: when (differential=1) + (gain=0.5) 0: else */
        __IO uint32_t RG_AIO_MUX_INTERNAL_EN          :1;    /* bits:10-10, AIO MUX internal path enable 0: disable 1: enable */
        __IO uint32_t RG_AIO_SC_C_SEL                 :5;    /* bits:11-15, AIO mode switch cap type gain selection 5'b00000:forbidden 5'b00001:gain=0.5 5'b00011:gain=1 5'b00111:gain=2 5'b01111:gain=3 5'b11111:gain=4 */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} RG_AUENC_CON_11_T;

#define RG_AUENC_CON_11_RG_AIO_R_MODE_EN_OFFSET                          (0U)
#define RG_AUENC_CON_11_RG_AIO_R_MODE_EN_MASK                            (0x1U << RG_AUENC_CON_11_RG_AIO_R_MODE_EN_OFFSET)
#define RG_AUENC_CON_11_RG_AIO_SC_MODE_EN_OFFSET                         (1U)
#define RG_AUENC_CON_11_RG_AIO_SC_MODE_EN_MASK                           (0x1U << RG_AUENC_CON_11_RG_AIO_SC_MODE_EN_OFFSET)
#define RG_AUENC_CON_11_RG_MIC_MODE_EN_OFFSET                            (2U)
#define RG_AUENC_CON_11_RG_MIC_MODE_EN_MASK                              (0x1U << RG_AUENC_CON_11_RG_MIC_MODE_EN_OFFSET)
#define RG_AUENC_CON_11_RG_AIO_DIFF_EN_OFFSET                            (3U)
#define RG_AUENC_CON_11_RG_AIO_DIFF_EN_MASK                              (0x1U << RG_AUENC_CON_11_RG_AIO_DIFF_EN_OFFSET)
#define RG_AUENC_CON_11_RG_AIO_RIN_SEL_OFFSET                            (4U)
#define RG_AUENC_CON_11_RG_AIO_RIN_SEL_MASK                              (0x3U << RG_AUENC_CON_11_RG_AIO_RIN_SEL_OFFSET)
#define RG_AUENC_CON_11_RG_AIO_RTEMP_SEL_OFFSET                          (6U)
#define RG_AUENC_CON_11_RG_AIO_RTEMP_SEL_MASK                            (0x3U << RG_AUENC_CON_11_RG_AIO_RTEMP_SEL_OFFSET)
#define RG_AUENC_CON_11_RG_PGA_CHOP_EN_OFFSET                            (8U)
#define RG_AUENC_CON_11_RG_PGA_CHOP_EN_MASK                              (0x1U << RG_AUENC_CON_11_RG_PGA_CHOP_EN_OFFSET)
#define RG_AUENC_CON_11_RG_AIO_RTB_SHORT_EN_OFFSET                       (9U)
#define RG_AUENC_CON_11_RG_AIO_RTB_SHORT_EN_MASK                         (0x1U << RG_AUENC_CON_11_RG_AIO_RTB_SHORT_EN_OFFSET)
#define RG_AUENC_CON_11_RG_AIO_MUX_INTERNAL_EN_OFFSET                    (10U)
#define RG_AUENC_CON_11_RG_AIO_MUX_INTERNAL_EN_MASK                      (0x1U << RG_AUENC_CON_11_RG_AIO_MUX_INTERNAL_EN_OFFSET)
#define RG_AUENC_CON_11_RG_AIO_SC_C_SEL_OFFSET                           (11U)
#define RG_AUENC_CON_11_RG_AIO_SC_C_SEL_MASK                             (0x1FU << RG_AUENC_CON_11_RG_AIO_SC_C_SEL_OFFSET)


/* AUENC Control Register 12 */
typedef union {
    struct {
        __IO uint32_t RG_AIO_MUX_INTERNAL             :4;    /* bits:0-3, AIO internal path channel selection 4'b0000:CH_INTERNAL<0> 4'b0001:CH_INTERNAL<1> etc. */
        __IO uint32_t RG_AIO_VIN_BUF_EN               :1;    /* bits:4-4, AIO mode VIN buffer enable 0: disable 1: enable */
        __IO uint32_t RG_AIO_RTB_SEL                  :7;    /* bits:5-11, AIO mode resistor type gain selection Single-end: 7'b0000000=7'd0:gain=0.5 7'b0000001=7'd1:gain=1 7'b0000111=7'd7:gain=2 7'b0011111=7'd31:gain=3 7'b1111111=7'd127:gain=4 Differential: 7'b0000000=7'd0:gain=0.5 7'b0000000=7'd0:gain=1 7'b0000001=7'd1:gain=2 7'b0000011=7'd3:gain=3 7'b0000111=7'd7:gain=4 */
        __IO uint32_t RG_AIO_VIN_BUF_RSEL             :4;    /* bits:12-15, AIO mode VIN buffer R ladder selection 4'b0000:1.6V 4'b0001:0.9V 4'b0010:0.85V 4'b0011:0.45V 4'b0100:0.3V 4'b0101:0.225V */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} RG_AUENC_CON_12_T;

#define RG_AUENC_CON_12_RG_AIO_MUX_INTERNAL_OFFSET                       (0U)
#define RG_AUENC_CON_12_RG_AIO_MUX_INTERNAL_MASK                         (0xFU << RG_AUENC_CON_12_RG_AIO_MUX_INTERNAL_OFFSET)
#define RG_AUENC_CON_12_RG_AIO_VIN_BUF_EN_OFFSET                         (4U)
#define RG_AUENC_CON_12_RG_AIO_VIN_BUF_EN_MASK                           (0x1U << RG_AUENC_CON_12_RG_AIO_VIN_BUF_EN_OFFSET)
#define RG_AUENC_CON_12_RG_AIO_RTB_SEL_OFFSET                            (5U)
#define RG_AUENC_CON_12_RG_AIO_RTB_SEL_MASK                              (0x7FU << RG_AUENC_CON_12_RG_AIO_RTB_SEL_OFFSET)
#define RG_AUENC_CON_12_RG_AIO_VIN_BUF_RSEL_OFFSET                       (12U)
#define RG_AUENC_CON_12_RG_AIO_VIN_BUF_RSEL_MASK                         (0xFU << RG_AUENC_CON_12_RG_AIO_VIN_BUF_RSEL_OFFSET)


/* AUENC Control Register 13 */
typedef union {
    struct {
        __IO uint32_t RG_AIO_SC_CLK_DIV               :4;    /* bits:0-3, AIO mode switch cap clock divider ctrl 4'b0000:CLK/1 4'b0001:CLK/2 4'b0010:CLK/4 4'b0011:CLK/8 4'b0100:CLK/16 4'b0101:CLK/32 */
        __IO uint32_t RG_AIO_RVCMI_EN                 :1;    /* bits:4-4, AIO mode resistor type PGA input pull low resistance enable 0: disable 1: enable */
        __IO uint32_t RG_AIO_TB_BUF_EN                :1;    /* bits:5-5, AIO mode resistor type T-Bridge buffer enable 0: disable 1: enable */
        __IO uint32_t RG_AIO_SC_CVCMI_EN              :1;    /* bits:6-6, AIO mode switch cap type PGA input pull low capacitor enable 0: disable 1: enable */
        __I  uint32_t __reserved_00                   :1;
        __IO uint32_t RG_AIO_TB_BUF_RSEL              :4;    /* bits:8-11, AIO mode T-Bridge buffer R ladder selection 4'b0000:1.6V 4'b0001:0.9V 4'b0010:0.85V 4'b0011:0.45V 4'b0100:0.3V 4'b0101:0.225V */
        __IO uint32_t RG_AIO_VINBUF_ATST_EN           :1;    /* bits:12-12, ATST for VIN buffer output voltage 0: disable 1: enable */
        __IO uint32_t RG_AIO_TBBUF_ATST_EN            :1;    /* bits:13-13, ATST for T-Bridge buffer output voltage 0: disable 1: enable */
        __I  uint32_t __reserved_01                   :18;
    } field;
    __IO uint32_t word;
} RG_AUENC_CON_13_T;

#define RG_AUENC_CON_13_RG_AIO_SC_CLK_DIV_OFFSET                         (0U)
#define RG_AUENC_CON_13_RG_AIO_SC_CLK_DIV_MASK                           (0xFU << RG_AUENC_CON_13_RG_AIO_SC_CLK_DIV_OFFSET)
#define RG_AUENC_CON_13_RG_AIO_RVCMI_EN_OFFSET                           (4U)
#define RG_AUENC_CON_13_RG_AIO_RVCMI_EN_MASK                             (0x1U << RG_AUENC_CON_13_RG_AIO_RVCMI_EN_OFFSET)
#define RG_AUENC_CON_13_RG_AIO_TB_BUF_EN_OFFSET                          (5U)
#define RG_AUENC_CON_13_RG_AIO_TB_BUF_EN_MASK                            (0x1U << RG_AUENC_CON_13_RG_AIO_TB_BUF_EN_OFFSET)
#define RG_AUENC_CON_13_RG_AIO_SC_CVCMI_EN_OFFSET                        (6U)
#define RG_AUENC_CON_13_RG_AIO_SC_CVCMI_EN_MASK                          (0x1U << RG_AUENC_CON_13_RG_AIO_SC_CVCMI_EN_OFFSET)
#define RG_AUENC_CON_13_RG_AIO_TB_BUF_RSEL_OFFSET                        (8U)
#define RG_AUENC_CON_13_RG_AIO_TB_BUF_RSEL_MASK                          (0xFU << RG_AUENC_CON_13_RG_AIO_TB_BUF_RSEL_OFFSET)
#define RG_AUENC_CON_13_RG_AIO_VINBUF_ATST_EN_OFFSET                     (12U)
#define RG_AUENC_CON_13_RG_AIO_VINBUF_ATST_EN_MASK                       (0x1U << RG_AUENC_CON_13_RG_AIO_VINBUF_ATST_EN_OFFSET)
#define RG_AUENC_CON_13_RG_AIO_TBBUF_ATST_EN_OFFSET                      (13U)
#define RG_AUENC_CON_13_RG_AIO_TBBUF_ATST_EN_MASK                        (0x1U << RG_AUENC_CON_13_RG_AIO_TBBUF_ATST_EN_OFFSET)


/* AUENC Control Register 14 */
typedef union {
    struct {
        __IO uint32_t RG_PGA_CM_EN                    :2;    /* bits:0-1, PGA Miller Compensation  0: 2.1pF (MIC Mode) 1: 4.22pF (AIO Mode) */
        __IO uint32_t RG_PGA_RM_EN                    :2;    /* bits:2-3, PGA Zero Compensation  0: 10.5ohm (MIC Mode) 1: 36Kohm (AIO Mode) */
        __I  uint32_t __reserved_00                   :28;
    } field;
    __IO uint32_t word;
} RG_AUENC_CON_14_T;

#define RG_AUENC_CON_14_RG_PGA_CM_EN_OFFSET                              (0U)
#define RG_AUENC_CON_14_RG_PGA_CM_EN_MASK                                (0x3U << RG_AUENC_CON_14_RG_PGA_CM_EN_OFFSET)
#define RG_AUENC_CON_14_RG_PGA_RM_EN_OFFSET                              (2U)
#define RG_AUENC_CON_14_RG_PGA_RM_EN_MASK                                (0x3U << RG_AUENC_CON_14_RG_PGA_RM_EN_OFFSET)


/* AUENC Control Register 15 */
typedef union {
    struct {
        __IO uint32_t RG_AIO_RSV                      :16;    /* bits:0-15, AIO mode reserved pin */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} RG_AUENC_CON_15_T;

#define RG_AUENC_CON_15_RG_AIO_RSV_OFFSET                                (0U)
#define RG_AUENC_CON_15_RG_AIO_RSV_MASK                                  (0xFFFFU << RG_AUENC_CON_15_RG_AIO_RSV_OFFSET)


/* AUENC Control Register 16 */
typedef union {
    struct {
        __I  uint32_t RGS_AUDRCTUNEREAD               :5;    /* bits:0-4, Audio L RC tune read data */
        __I  uint32_t __reserved_00                   :27;
    } field;
    __IO uint32_t word;
} RG_AUENC_CON_16_T;

#define RG_AUENC_CON_16_RGS_AUDRCTUNEREAD_OFFSET                         (0U)
#define RG_AUENC_CON_16_RGS_AUDRCTUNEREAD_MASK                           (0x1FU << RG_AUENC_CON_16_RGS_AUDRCTUNEREAD_OFFSET)


/* TENSOR Control Register 0 */
typedef union {
    struct {
        __IO uint32_t RG_TEMP_BGR_EN                  :1;    /* bits:0-0, Bandgap Core Enable 1'b0 : disable 1'b1 : enable */
        __I  uint32_t __reserved_00                   :3;
        __IO uint32_t RG_TEMP_CK200K_BGR_CHOP_EN      :1;    /* bits:4-4, Bandgap Core Chopper Enable 1'b0 : disable 1'b1 : enable */
        __I  uint32_t __reserved_01                   :3;
        __IO uint32_t RG_TEMP_BGR_R1_SEL              :3;    /* bits:8-10, Bandgap Core R1 Sel ; IPTAT=VTln(n)/R1 ; Option for PTAT Current Slope Normal=[4]=7.2K ; 1step = 450ohm */
        __I  uint32_t __reserved_02                   :1;
        __IO uint32_t RG_TEMP_BGR_RE0_SEL             :3;    /* bits:12-14, Bandgap Core RE0 Sel ; ICTAT=VBE0/RE0 ; Option for CTAT Current Slope Normal=[4]=142.2K ; 1step = 7.2Kohm */
        __I  uint32_t __reserved_03                   :17;
    } field;
    __IO uint32_t word;
} RG_TENSOR_CON_0_T;

#define RG_TENSOR_CON_0_RG_TEMP_BGR_EN_OFFSET                            (0U)
#define RG_TENSOR_CON_0_RG_TEMP_BGR_EN_MASK                              (0x1U << RG_TENSOR_CON_0_RG_TEMP_BGR_EN_OFFSET)
#define RG_TENSOR_CON_0_RG_TEMP_CK200K_BGR_CHOP_EN_OFFSET                (4U)
#define RG_TENSOR_CON_0_RG_TEMP_CK200K_BGR_CHOP_EN_MASK                  (0x1U << RG_TENSOR_CON_0_RG_TEMP_CK200K_BGR_CHOP_EN_OFFSET)
#define RG_TENSOR_CON_0_RG_TEMP_BGR_R1_SEL_OFFSET                        (8U)
#define RG_TENSOR_CON_0_RG_TEMP_BGR_R1_SEL_MASK                          (0x7U << RG_TENSOR_CON_0_RG_TEMP_BGR_R1_SEL_OFFSET)
#define RG_TENSOR_CON_0_RG_TEMP_BGR_RE0_SEL_OFFSET                       (12U)
#define RG_TENSOR_CON_0_RG_TEMP_BGR_RE0_SEL_MASK                         (0x7U << RG_TENSOR_CON_0_RG_TEMP_BGR_RE0_SEL_OFFSET)


/* TENSOR Control Register 1 */
typedef union {
    struct {
        __IO uint32_t RG_TEMP_VREF_AIO_SEL            :5;    /* bits:0-4, Bandgap Core VREF_AIO Sel From 950mV - 175mV ; 1 step=25mV */
        __I  uint32_t __reserved_00                   :3;
        __IO uint32_t RG_TEMP_VBG1P0V_COMP_SEL        :5;    /* bits:8-12, Bandgap Core COMP_1P0V Sel Normal[15]=1000mV ;1step = 5mV ; From 1080mV ~ 925mV */
        __I  uint32_t __reserved_01                   :19;
    } field;
    __IO uint32_t word;
} RG_TENSOR_CON_1_T;

#define RG_TENSOR_CON_1_RG_TEMP_VREF_AIO_SEL_OFFSET                      (0U)
#define RG_TENSOR_CON_1_RG_TEMP_VREF_AIO_SEL_MASK                        (0x1FU << RG_TENSOR_CON_1_RG_TEMP_VREF_AIO_SEL_OFFSET)
#define RG_TENSOR_CON_1_RG_TEMP_VBG1P0V_COMP_SEL_OFFSET                  (8U)
#define RG_TENSOR_CON_1_RG_TEMP_VBG1P0V_COMP_SEL_MASK                    (0x1FU << RG_TENSOR_CON_1_RG_TEMP_VBG1P0V_COMP_SEL_OFFSET)


/* TENSOR Control Register 2 */
typedef union {
    struct {
        __IO uint32_t RG_TEMP_VBG0P6V_AUD_SEL         :5;    /* bits:0-4, Bandgap Core AUDENC_0P6V Sel Normal[15]=600mV ;1step = 5mV ; From 680mV ~ 525mV */
        __I  uint32_t __reserved_00                   :3;
        __IO uint32_t RG_TEMP_VBG0P8V_AUD_SEL         :5;    /* bits:8-12, Bandgap Core AUDENC_0P8V Sel Normal[15]=600mV ;1step = 5mV ; From 880mV ~ 725mV */
        __I  uint32_t __reserved_01                   :19;
    } field;
    __IO uint32_t word;
} RG_TENSOR_CON_2_T;

#define RG_TENSOR_CON_2_RG_TEMP_VBG0P6V_AUD_SEL_OFFSET                   (0U)
#define RG_TENSOR_CON_2_RG_TEMP_VBG0P6V_AUD_SEL_MASK                     (0x1FU << RG_TENSOR_CON_2_RG_TEMP_VBG0P6V_AUD_SEL_OFFSET)
#define RG_TENSOR_CON_2_RG_TEMP_VBG0P8V_AUD_SEL_OFFSET                   (8U)
#define RG_TENSOR_CON_2_RG_TEMP_VBG0P8V_AUD_SEL_MASK                     (0x1FU << RG_TENSOR_CON_2_RG_TEMP_VBG0P8V_AUD_SEL_OFFSET)


/* TENSOR Control Register 3 */
typedef union {
    struct {
        __IO uint32_t RG_TEMP_TS_EN                   :1;    /* bits:0-0, Temperature Sensor Enable 1'b0 : disable 1'b1 : enable */
        __I  uint32_t __reserved_00                   :3;
        __IO uint32_t RG_TEMP_TS_PTAT_ONLY            :1;    /* bits:4-4, Temperature Sensor PTAT Parts Only 1'b0 : disable 1'b1 : enable */
        __I  uint32_t __reserved_01                   :3;
        __IO uint32_t RG_TEMP_TS_CTAT_SEL             :2;    /* bits:8-9, Temperature Sensor CTAT Current Sel Normal[2]=10uA ; 1step=2.5uA; [0]=5uA;[1]=7.5uA;[2]=10uA;[3]=12.5uA */
        __I  uint32_t __reserved_02                   :2;
        __IO uint32_t RG_TEMP_TS_PTAT_SEL             :2;    /* bits:12-13, Temperature Sensor PTAT Current Sel Normal[2]=10uA ; 1step=2.5uA; [0]=5uA;[1]=7.5uA;[2]=10uA;[3]=12.5uA */
        __I  uint32_t __reserved_03                   :18;
    } field;
    __IO uint32_t word;
} RG_TENSOR_CON_3_T;

#define RG_TENSOR_CON_3_RG_TEMP_TS_EN_OFFSET                             (0U)
#define RG_TENSOR_CON_3_RG_TEMP_TS_EN_MASK                               (0x1U << RG_TENSOR_CON_3_RG_TEMP_TS_EN_OFFSET)
#define RG_TENSOR_CON_3_RG_TEMP_TS_PTAT_ONLY_OFFSET                      (4U)
#define RG_TENSOR_CON_3_RG_TEMP_TS_PTAT_ONLY_MASK                        (0x1U << RG_TENSOR_CON_3_RG_TEMP_TS_PTAT_ONLY_OFFSET)
#define RG_TENSOR_CON_3_RG_TEMP_TS_CTAT_SEL_OFFSET                       (8U)
#define RG_TENSOR_CON_3_RG_TEMP_TS_CTAT_SEL_MASK                         (0x3U << RG_TENSOR_CON_3_RG_TEMP_TS_CTAT_SEL_OFFSET)
#define RG_TENSOR_CON_3_RG_TEMP_TS_PTAT_SEL_OFFSET                       (12U)
#define RG_TENSOR_CON_3_RG_TEMP_TS_PTAT_SEL_MASK                         (0x3U << RG_TENSOR_CON_3_RG_TEMP_TS_PTAT_SEL_OFFSET)


/* TENSOR Control Register 4 */
typedef union {
    struct {
        __IO uint32_t RG_TEMP_ATST_SEL                :4;    /* bits:0-3, ATST Sel [0/x/x/x]=disable [1/0/0/0]=QS_VBGR1P0_COMP [1/0/0/1]=QS_VBGR0P8_AUDENC [1/0/1/0]=QS_VBGR0P6_AUDENC [1/0/1/1]=QS_VBGR0P6_V2I [1/1/0/0]=QS_IPTAT_5U [1/1/0/1]=QS_ICTAT_5U [1/1/1/0]=QS_IBIAS_GLBV2I_1U [1/1/1/1]=NA */
        __I  uint32_t __reserved_00                   :4;
        __IO uint32_t RG_TEMP_RSV0                    :8;    /* bits:8-15, empty description */
        __I  uint32_t __reserved_01                   :16;
    } field;
    __IO uint32_t word;
} RG_TENSOR_CON_4_T;

#define RG_TENSOR_CON_4_RG_TEMP_ATST_SEL_OFFSET                          (0U)
#define RG_TENSOR_CON_4_RG_TEMP_ATST_SEL_MASK                            (0xFU << RG_TENSOR_CON_4_RG_TEMP_ATST_SEL_OFFSET)
#define RG_TENSOR_CON_4_RG_TEMP_RSV0_OFFSET                              (8U)
#define RG_TENSOR_CON_4_RG_TEMP_RSV0_MASK                                (0xFFU << RG_TENSOR_CON_4_RG_TEMP_RSV0_OFFSET)


/* TENSOR Control Register 5 */
typedef union {
    struct {
        __IO uint32_t RG_TEMP_GLBV2I_PWRUP            :1;    /* bits:0-0, GLBV2I POWER UP  0 : Disable 1 : Enable */
        __I  uint32_t __reserved_00                   :3;
        __IO uint32_t RG_TEMP_GLBV2I_RSEL             :3;    /* bits:4-6, GLBV2I Output Current Adjustment 000 : 1uA+20% 001 : 1uA+15% 010 : 1uA+10% 011 : 1uA+5% 100 : 1uA 101 : 1uA-5% 110 : 1uA-10% 111 : 1uA-15% */
        __I  uint32_t __reserved_01                   :1;
        __IO uint32_t RG_TEMP_GLBV2I_SELFBIAS_RSEL    :3;    /* bits:8-10, GLBV2I Output Current Adjustment 000 : 5.54uA 001 : 5.03uA 010 : 4.62uA 011 : 4.29uA 100 : 4.01uA 101 : 3.78uA 110 : 3.6uA 111 : 3.51uA */
        __I  uint32_t __reserved_02                   :21;
    } field;
    __IO uint32_t word;
} RG_TENSOR_CON_5_T;

#define RG_TENSOR_CON_5_RG_TEMP_GLBV2I_PWRUP_OFFSET                      (0U)
#define RG_TENSOR_CON_5_RG_TEMP_GLBV2I_PWRUP_MASK                        (0x1U << RG_TENSOR_CON_5_RG_TEMP_GLBV2I_PWRUP_OFFSET)
#define RG_TENSOR_CON_5_RG_TEMP_GLBV2I_RSEL_OFFSET                       (4U)
#define RG_TENSOR_CON_5_RG_TEMP_GLBV2I_RSEL_MASK                         (0x7U << RG_TENSOR_CON_5_RG_TEMP_GLBV2I_RSEL_OFFSET)
#define RG_TENSOR_CON_5_RG_TEMP_GLBV2I_SELFBIAS_RSEL_OFFSET              (8U)
#define RG_TENSOR_CON_5_RG_TEMP_GLBV2I_SELFBIAS_RSEL_MASK                (0x7U << RG_TENSOR_CON_5_RG_TEMP_GLBV2I_SELFBIAS_RSEL_OFFSET)


/* COMP Control Register 0 */
typedef union {
    struct {
        __IO uint32_t RG_CP2_OP_EN                    :1;    /* bits:0-0, Comparator core enable 1'b0 : disable 1'b1 : enable */
        __IO uint32_t RG_CP2_UGB_EN                   :1;    /* bits:1-1, Unit gain buffer enable 1'b0 : disable 1'b1 : enable */
        __IO uint32_t RG_CP2_IREF_SEL                 :1;    /* bits:2-2, CP2 current source select 1'b0:from Constant Gm 1'b1:from V2I */
        __I  uint32_t __reserved_00                   :1;
        __IO uint32_t RG_CP2_LP_ISEL                  :2;    /* bits:4-5, LPCOMP mode current source  2'b00:0nA / 1step:50nA Default:2'b01 */
        __I  uint32_t __reserved_01                   :2;
        __IO uint32_t RG_CP2_AT_ISEL                  :3;    /* bits:8-10, Active mode current source  3'b000:300nA / 1step:250nA LS:3'b000 / NM:3'b010 / HS:3'b110 */
        __I  uint32_t __reserved_02                   :1;
        __IO uint32_t RG_CP2_ACTIVE_MODE_EN           :1;    /* bits:12-12, Active mode enable 1'b0 : disable 1'b1 : enable */
        __I  uint32_t __reserved_03                   :19;
    } field;
    __IO uint32_t word;
} RG_COMP_CON_0_T;

#define RG_COMP_CON_0_RG_CP2_OP_EN_OFFSET                                (0U)
#define RG_COMP_CON_0_RG_CP2_OP_EN_MASK                                  (0x1U << RG_COMP_CON_0_RG_CP2_OP_EN_OFFSET)
#define RG_COMP_CON_0_RG_CP2_UGB_EN_OFFSET                               (1U)
#define RG_COMP_CON_0_RG_CP2_UGB_EN_MASK                                 (0x1U << RG_COMP_CON_0_RG_CP2_UGB_EN_OFFSET)
#define RG_COMP_CON_0_RG_CP2_IREF_SEL_OFFSET                             (2U)
#define RG_COMP_CON_0_RG_CP2_IREF_SEL_MASK                               (0x1U << RG_COMP_CON_0_RG_CP2_IREF_SEL_OFFSET)
#define RG_COMP_CON_0_RG_CP2_LP_ISEL_OFFSET                              (4U)
#define RG_COMP_CON_0_RG_CP2_LP_ISEL_MASK                                (0x3U << RG_COMP_CON_0_RG_CP2_LP_ISEL_OFFSET)
#define RG_COMP_CON_0_RG_CP2_AT_ISEL_OFFSET                              (8U)
#define RG_COMP_CON_0_RG_CP2_AT_ISEL_MASK                                (0x7U << RG_COMP_CON_0_RG_CP2_AT_ISEL_OFFSET)
#define RG_COMP_CON_0_RG_CP2_ACTIVE_MODE_EN_OFFSET                       (12U)
#define RG_COMP_CON_0_RG_CP2_ACTIVE_MODE_EN_MASK                         (0x1U << RG_COMP_CON_0_RG_CP2_ACTIVE_MODE_EN_OFFSET)


/* COMP Control Register 1 */
typedef union {
    struct {
        __IO uint32_t RG_CP2_MODE                     :1;    /* bits:0-0, Mode select 1'b0 : differential mode 1'b1 : singel end mode */
        __I  uint32_t __reserved_00                   :3;
        __IO uint32_t RG_CP2_EXTREFSEL                :4;    /* bits:4-7, external reference select (from GPIO) 4'b0000 :  GPIO25 4'b0001 :  GPIO26 4'b0010 :  GPIO27 4'b0011 :  GPIO28 4'b0100 :  GPIO29 4'b0101 :  GPIO30 4'b0110 :  GPIO31 4'b0111 :  GPIO32 4'b1000 :  GPIO33 4'b1001 :  GPIO34 other : GND */
        __IO uint32_t RG_CP2_HYST_EN                  :1;    /* bits:8-8, Hysteresis enable 1'b0 : disable 1'b1 : enable */
        __I  uint32_t __reserved_01                   :3;
        __IO uint32_t RG_CP2_HYST_SEL                 :3;    /* bits:12-14, Hysteresis select  3b'000:30mV/1step:10mV */
        __I  uint32_t __reserved_02                   :17;
    } field;
    __IO uint32_t word;
} RG_COMP_CON_1_T;

#define RG_COMP_CON_1_RG_CP2_MODE_OFFSET                                 (0U)
#define RG_COMP_CON_1_RG_CP2_MODE_MASK                                   (0x1U << RG_COMP_CON_1_RG_CP2_MODE_OFFSET)
#define RG_COMP_CON_1_RG_CP2_EXTREFSEL_OFFSET                            (4U)
#define RG_COMP_CON_1_RG_CP2_EXTREFSEL_MASK                              (0xFU << RG_COMP_CON_1_RG_CP2_EXTREFSEL_OFFSET)
#define RG_COMP_CON_1_RG_CP2_HYST_EN_OFFSET                              (8U)
#define RG_COMP_CON_1_RG_CP2_HYST_EN_MASK                                (0x1U << RG_COMP_CON_1_RG_CP2_HYST_EN_OFFSET)
#define RG_COMP_CON_1_RG_CP2_HYST_SEL_OFFSET                             (12U)
#define RG_COMP_CON_1_RG_CP2_HYST_SEL_MASK                               (0x7U << RG_COMP_CON_1_RG_CP2_HYST_SEL_OFFSET)


/* COMP Control Register 2 */
typedef union {
    struct {
        __IO uint32_t RG_CP2_PSEL                     :4;    /* bits:0-3, Input signal select(from GPIO) 4'b0000 :  GPIO25 4'b0001 :  GPIO26 4'b0010 :  GPIO27 4'b0011 :  GPIO28 4'b0100 :  GPIO29 4'b0101 :  GPIO30 4'b0110 :  GPIO31 4'b0111 :  GPIO32 4'b1000 :  GPIO33 4'b1001 :  GPIO34 other : GND */
        __IO uint32_t RG_CP2_REFSEL                   :2;    /* bits:4-5, internal referenct select to differential mode 2'b00:Rladder VUP voltage 2'b01:Unit gain buffer output 2'b10:GPIO_reference 2'b11:LP_Rladder voltage */
        __I  uint32_t __reserved_00                   :2;
        __IO uint32_t RG_CP2_RL_REFSEL                :2;    /* bits:8-9, internal referenct select to Rladder/LPRladder 2'b00:AVSS 2'b01:Unit gain buffer output 2'b10:GPIO_reference 2'b11:AVDD */
        __I  uint32_t __reserved_01                   :22;
    } field;
    __IO uint32_t word;
} RG_COMP_CON_2_T;

#define RG_COMP_CON_2_RG_CP2_PSEL_OFFSET                                 (0U)
#define RG_COMP_CON_2_RG_CP2_PSEL_MASK                                   (0xFU << RG_COMP_CON_2_RG_CP2_PSEL_OFFSET)
#define RG_COMP_CON_2_RG_CP2_REFSEL_OFFSET                               (4U)
#define RG_COMP_CON_2_RG_CP2_REFSEL_MASK                                 (0x3U << RG_COMP_CON_2_RG_CP2_REFSEL_OFFSET)
#define RG_COMP_CON_2_RG_CP2_RL_REFSEL_OFFSET                            (8U)
#define RG_COMP_CON_2_RG_CP2_RL_REFSEL_MASK                              (0x3U << RG_COMP_CON_2_RG_CP2_RL_REFSEL_OFFSET)


/* COMP Control Register 3 */
typedef union {
    struct {
        __IO uint32_t RG_CP2_THDOWN                   :6;    /* bits:0-5, Active mode Rladder Vth_down select (1step:Vref/64 ) */
        __I  uint32_t __reserved_00                   :2;
        __IO uint32_t RG_CP2_THUP                     :6;    /* bits:8-13, Active mode Rladder Vth_up select (1step:Vref/64 ) */
        __I  uint32_t __reserved_01                   :18;
    } field;
    __IO uint32_t word;
} RG_COMP_CON_3_T;

#define RG_COMP_CON_3_RG_CP2_THDOWN_OFFSET                               (0U)
#define RG_COMP_CON_3_RG_CP2_THDOWN_MASK                                 (0x3FU << RG_COMP_CON_3_RG_CP2_THDOWN_OFFSET)
#define RG_COMP_CON_3_RG_CP2_THUP_OFFSET                                 (8U)
#define RG_COMP_CON_3_RG_CP2_THUP_MASK                                   (0x3FU << RG_COMP_CON_3_RG_CP2_THUP_OFFSET)


/* COMP Control Register 4 */
typedef union {
    struct {
        __IO uint32_t RG_CP_ATST_EN                   :1;    /* bits:0-0, ATST MUX enable 1'b0 : disable 1'b1 : enable */
        __I  uint32_t __reserved_00                   :3;
        __IO uint32_t RG_CP_ATST_SEL                  :2;    /* bits:4-5, Constant Gm start up leakage select 2'b00:UGB1 2'b01:UGB2 2'b10:V2I_I_3U 2'b11:Constant Gm_I_1U */
        __I  uint32_t __reserved_01                   :2;
        __IO uint32_t RG_CP_RSV                       :8;    /* bits:8-15, empty description */
        __I  uint32_t __reserved_02                   :16;
    } field;
    __IO uint32_t word;
} RG_COMP_CON_4_T;

#define RG_COMP_CON_4_RG_CP_ATST_EN_OFFSET                               (0U)
#define RG_COMP_CON_4_RG_CP_ATST_EN_MASK                                 (0x1U << RG_COMP_CON_4_RG_CP_ATST_EN_OFFSET)
#define RG_COMP_CON_4_RG_CP_ATST_SEL_OFFSET                              (4U)
#define RG_COMP_CON_4_RG_CP_ATST_SEL_MASK                                (0x3U << RG_COMP_CON_4_RG_CP_ATST_SEL_OFFSET)
#define RG_COMP_CON_4_RG_CP_RSV_OFFSET                                   (8U)
#define RG_COMP_CON_4_RG_CP_RSV_MASK                                     (0xFFU << RG_COMP_CON_4_RG_CP_RSV_OFFSET)


/* ATST Control Register 0 */
typedef union {
    struct {
        __IO uint32_t RG_ATST1_BUF_BIAS_EN            :1;    /* bits:0-0, ATST1 TMBUF bias enable 0: disable 1: enable */
        __I  uint32_t __reserved_00                   :3;
        __IO uint32_t RG_ATST1_BUF_ISEL               :2;    /* bits:4-5, ATST1 TMBUF Isel 00:5uA 01:3.3uA 10:2.5uA(default) 11:2uA if ATST disable, need to set 2'b00, avoid leakage */
        __I  uint32_t __reserved_01                   :2;
        __IO uint32_t RG_ATST1_EN                     :1;    /* bits:8-8, ATST1 input Tswitch enable 0: all disable 1: enable (Tswitch en from ATST1_sel) */
        __IO uint32_t RG_ATST1_BUF_NIN_EN             :1;    /* bits:9-9, ATST1 TMBUF Ninput type enable 0: disable 1: enable */
        __IO uint32_t RG_ATST1_BUF_PIN_EN             :1;    /* bits:10-10, ATST1 TMBUF Pinput type enable 0: disable 1: enable */
        __I  uint32_t __reserved_02                   :1;
        __IO uint32_t RG_ATST1_SEL                    :3;    /* bits:12-14, ATST1 input signal sel */
        __I  uint32_t __reserved_03                   :17;
    } field;
    __IO uint32_t word;
} RG_ATST_CON_0_T;

#define RG_ATST_CON_0_RG_ATST1_BUF_BIAS_EN_OFFSET                        (0U)
#define RG_ATST_CON_0_RG_ATST1_BUF_BIAS_EN_MASK                          (0x1U << RG_ATST_CON_0_RG_ATST1_BUF_BIAS_EN_OFFSET)
#define RG_ATST_CON_0_RG_ATST1_BUF_ISEL_OFFSET                           (4U)
#define RG_ATST_CON_0_RG_ATST1_BUF_ISEL_MASK                             (0x3U << RG_ATST_CON_0_RG_ATST1_BUF_ISEL_OFFSET)
#define RG_ATST_CON_0_RG_ATST1_EN_OFFSET                                 (8U)
#define RG_ATST_CON_0_RG_ATST1_EN_MASK                                   (0x1U << RG_ATST_CON_0_RG_ATST1_EN_OFFSET)
#define RG_ATST_CON_0_RG_ATST1_BUF_NIN_EN_OFFSET                         (9U)
#define RG_ATST_CON_0_RG_ATST1_BUF_NIN_EN_MASK                           (0x1U << RG_ATST_CON_0_RG_ATST1_BUF_NIN_EN_OFFSET)
#define RG_ATST_CON_0_RG_ATST1_BUF_PIN_EN_OFFSET                         (10U)
#define RG_ATST_CON_0_RG_ATST1_BUF_PIN_EN_MASK                           (0x1U << RG_ATST_CON_0_RG_ATST1_BUF_PIN_EN_OFFSET)
#define RG_ATST_CON_0_RG_ATST1_SEL_OFFSET                                (12U)
#define RG_ATST_CON_0_RG_ATST1_SEL_MASK                                  (0x7U << RG_ATST_CON_0_RG_ATST1_SEL_OFFSET)


/* ATST Control Register 1 */
typedef union {
    struct {
        __IO uint32_t RG_ATST2_EN                     :1;    /* bits:0-0, ATST2 input Tswitch enable 0: all disable 1: enable (Tswitch en from ATST1_sel) */
        __I  uint32_t __reserved_00                   :3;
        __IO uint32_t RG_ATST2_SEL                    :3;    /* bits:4-6, ATST2 input signal sel */
        __I  uint32_t __reserved_01                   :1;
        __IO uint32_t RG_ATST_RSV                     :2;    /* bits:8-9, reserve pin */
        __I  uint32_t __reserved_02                   :22;
    } field;
    __IO uint32_t word;
} RG_ATST_CON_1_T;

#define RG_ATST_CON_1_RG_ATST2_EN_OFFSET                                 (0U)
#define RG_ATST_CON_1_RG_ATST2_EN_MASK                                   (0x1U << RG_ATST_CON_1_RG_ATST2_EN_OFFSET)
#define RG_ATST_CON_1_RG_ATST2_SEL_OFFSET                                (4U)
#define RG_ATST_CON_1_RG_ATST2_SEL_MASK                                  (0x7U << RG_ATST_CON_1_RG_ATST2_SEL_OFFSET)
#define RG_ATST_CON_1_RG_ATST_RSV_OFFSET                                 (8U)
#define RG_ATST_CON_1_RG_ATST_RSV_MASK                                   (0x3U << RG_ATST_CON_1_RG_ATST_RSV_OFFSET)


/* CKGEN Control Register 0 */
typedef union {
    struct {
        __IO uint32_t RG_CKGEN_AUDADC_CK_EN           :1;    /* bits:0-0, AUDADC CLK EN 0: disable 1: enable */
        __I  uint32_t __reserved_00                   :3;
        __IO uint32_t RG_CKGEN_AUDADC_CKDIV_RSTB      :1;    /* bits:4-4, AUDADC CLK RSTB */
        __I  uint32_t __reserved_01                   :3;
        __IO uint32_t RG_CKGEN_AUDADC_CKINV_SEL       :1;    /* bits:8-8, 0: wo INV 1: wi INV */
        __I  uint32_t __reserved_02                   :3;
        __IO uint32_t RG_CKGEN_AUDADC_CKDIV_SEL       :2;    /* bits:12-13, 2'b00 = /2(default) 2'b01 = /4 2'b10 = /8 2'b11 = /1 */
        __I  uint32_t __reserved_03                   :18;
    } field;
    __IO uint32_t word;
} RG_CKGEN_CON_0_T;

#define RG_CKGEN_CON_0_RG_CKGEN_AUDADC_CK_EN_OFFSET                      (0U)
#define RG_CKGEN_CON_0_RG_CKGEN_AUDADC_CK_EN_MASK                        (0x1U << RG_CKGEN_CON_0_RG_CKGEN_AUDADC_CK_EN_OFFSET)
#define RG_CKGEN_CON_0_RG_CKGEN_AUDADC_CKDIV_RSTB_OFFSET                 (4U)
#define RG_CKGEN_CON_0_RG_CKGEN_AUDADC_CKDIV_RSTB_MASK                   (0x1U << RG_CKGEN_CON_0_RG_CKGEN_AUDADC_CKDIV_RSTB_OFFSET)
#define RG_CKGEN_CON_0_RG_CKGEN_AUDADC_CKINV_SEL_OFFSET                  (8U)
#define RG_CKGEN_CON_0_RG_CKGEN_AUDADC_CKINV_SEL_MASK                    (0x1U << RG_CKGEN_CON_0_RG_CKGEN_AUDADC_CKINV_SEL_OFFSET)
#define RG_CKGEN_CON_0_RG_CKGEN_AUDADC_CKDIV_SEL_OFFSET                  (12U)
#define RG_CKGEN_CON_0_RG_CKGEN_AUDADC_CKDIV_SEL_MASK                    (0x3U << RG_CKGEN_CON_0_RG_CKGEN_AUDADC_CKDIV_SEL_OFFSET)


/* CKGEN Control Register 1 */
typedef union {
    struct {
        __IO uint32_t RG_CKGEN_LSCK_EN                :1;    /* bits:0-0, DVDD divider input CLK EN 0: disable 1: enable */
        __I  uint32_t __reserved_00                   :3;
        __IO uint32_t RG_CKGEN_LSCK_DIV_RSTB          :1;    /* bits:4-4, DVDD divider RSTB */
        __I  uint32_t __reserved_01                   :3;
        __IO uint32_t RG_CKGEN_BGR_CK_EN              :1;    /* bits:8-8, BGR CLK EN 0: disable 1: enable */
        __IO uint32_t RG_CKGEN_BGR_CLK_SEL            :1;    /* bits:9-9, BGR CLK from  DIG freqeucny divider or internal divider 0: internal 1: DA_ABBCK200K_BGR */
        __IO uint32_t RG_CKGEN_BGR_CK_SEL             :2;    /* bits:10-11, 2'b00 = 62K 2'b01 = 125K 2'b10 = 250K(default) 2'b11 = 500K */
        __IO uint32_t RG_CKGEN_AIO_CK_EN              :1;    /* bits:12-12, AIO CLK EN 0: disable 1: enable */
        __IO uint32_t RG_CKGEN_AIO_CLK_SEL            :1;    /* bits:13-13, AIO CLK from DIG freqeucny divider or internal divider 0: internal 1: DA_ABBCK200K_AIO */
        __IO uint32_t RG_CKGEN_AIO_CK_SEL             :2;    /* bits:14-15, 2'b00 = 125K 2'b01 = 250K(default) 2'b10 = 500K 2'b11 = 1M */
        __I  uint32_t __reserved_02                   :16;
    } field;
    __IO uint32_t word;
} RG_CKGEN_CON_1_T;

#define RG_CKGEN_CON_1_RG_CKGEN_LSCK_EN_OFFSET                           (0U)
#define RG_CKGEN_CON_1_RG_CKGEN_LSCK_EN_MASK                             (0x1U << RG_CKGEN_CON_1_RG_CKGEN_LSCK_EN_OFFSET)
#define RG_CKGEN_CON_1_RG_CKGEN_LSCK_DIV_RSTB_OFFSET                     (4U)
#define RG_CKGEN_CON_1_RG_CKGEN_LSCK_DIV_RSTB_MASK                       (0x1U << RG_CKGEN_CON_1_RG_CKGEN_LSCK_DIV_RSTB_OFFSET)
#define RG_CKGEN_CON_1_RG_CKGEN_BGR_CK_EN_OFFSET                         (8U)
#define RG_CKGEN_CON_1_RG_CKGEN_BGR_CK_EN_MASK                           (0x1U << RG_CKGEN_CON_1_RG_CKGEN_BGR_CK_EN_OFFSET)
#define RG_CKGEN_CON_1_RG_CKGEN_BGR_CLK_SEL_OFFSET                       (9U)
#define RG_CKGEN_CON_1_RG_CKGEN_BGR_CLK_SEL_MASK                         (0x1U << RG_CKGEN_CON_1_RG_CKGEN_BGR_CLK_SEL_OFFSET)
#define RG_CKGEN_CON_1_RG_CKGEN_BGR_CK_SEL_OFFSET                        (10U)
#define RG_CKGEN_CON_1_RG_CKGEN_BGR_CK_SEL_MASK                          (0x3U << RG_CKGEN_CON_1_RG_CKGEN_BGR_CK_SEL_OFFSET)
#define RG_CKGEN_CON_1_RG_CKGEN_AIO_CK_EN_OFFSET                         (12U)
#define RG_CKGEN_CON_1_RG_CKGEN_AIO_CK_EN_MASK                           (0x1U << RG_CKGEN_CON_1_RG_CKGEN_AIO_CK_EN_OFFSET)
#define RG_CKGEN_CON_1_RG_CKGEN_AIO_CLK_SEL_OFFSET                       (13U)
#define RG_CKGEN_CON_1_RG_CKGEN_AIO_CLK_SEL_MASK                         (0x1U << RG_CKGEN_CON_1_RG_CKGEN_AIO_CLK_SEL_OFFSET)
#define RG_CKGEN_CON_1_RG_CKGEN_AIO_CK_SEL_OFFSET                        (14U)
#define RG_CKGEN_CON_1_RG_CKGEN_AIO_CK_SEL_MASK                          (0x3U << RG_CKGEN_CON_1_RG_CKGEN_AIO_CK_SEL_OFFSET)


typedef struct {
    RG_ABB_TOP_0_T                                       rg_abb_top_0; /* offset: 0x00000000, ABB Control Register 0 */
    RG_AUENC_CON_0_T                                   rg_auenc_con_0; /* offset: 0x00000004, AUENC Control Register 0 */
    RG_AUENC_CON_1_T                                   rg_auenc_con_1; /* offset: 0x00000008, AUENC Control Register 1 */
    RG_AUENC_CON_2_T                                   rg_auenc_con_2; /* offset: 0x0000000C, AUENC Control Register 2 */
    RG_AUENC_CON_3_T                                   rg_auenc_con_3; /* offset: 0x00000010, AUENC Control Register 3 */
    RG_AUENC_CON_4_T                                   rg_auenc_con_4; /* offset: 0x00000014, AUENC Control Register 4 */
    RG_AUENC_CON_5_T                                   rg_auenc_con_5; /* offset: 0x00000018, AUENC Control Register 5 */
    RG_AUENC_CON_6_T                                   rg_auenc_con_6; /* offset: 0x0000001C, AUENC Control Register 6 */
    RG_AUENC_CON_7_T                                   rg_auenc_con_7; /* offset: 0x00000020, AUENC Control Register 7 */
    RG_AUENC_CON_8_T                                   rg_auenc_con_8; /* offset: 0x00000024, AUENC Control Register 8 */
    RG_AUENC_CON_9_T                                   rg_auenc_con_9; /* offset: 0x00000028, AUENC Control Register 9 */
    uint32_t                                         __reserved_00[1]; /* offset: 0x0000002C, padding size: 0x00000004 */
    RG_AUENC_CON_11_T                                 rg_auenc_con_11; /* offset: 0x00000030, AUENC Control Register 11 */
    RG_AUENC_CON_12_T                                 rg_auenc_con_12; /* offset: 0x00000034, AUENC Control Register 12 */
    RG_AUENC_CON_13_T                                 rg_auenc_con_13; /* offset: 0x00000038, AUENC Control Register 13 */
    RG_AUENC_CON_14_T                                 rg_auenc_con_14; /* offset: 0x0000003C, AUENC Control Register 14 */
    RG_AUENC_CON_15_T                                 rg_auenc_con_15; /* offset: 0x00000040, AUENC Control Register 15 */
    RG_AUENC_CON_16_T                                 rg_auenc_con_16; /* offset: 0x00000044, AUENC Control Register 16 */
    RG_TENSOR_CON_0_T                                 rg_tensor_con_0; /* offset: 0x00000048, TENSOR Control Register 0 */
    RG_TENSOR_CON_1_T                                 rg_tensor_con_1; /* offset: 0x0000004C, TENSOR Control Register 1 */
    RG_TENSOR_CON_2_T                                 rg_tensor_con_2; /* offset: 0x00000050, TENSOR Control Register 2 */
    RG_TENSOR_CON_3_T                                 rg_tensor_con_3; /* offset: 0x00000054, TENSOR Control Register 3 */
    RG_TENSOR_CON_4_T                                 rg_tensor_con_4; /* offset: 0x00000058, TENSOR Control Register 4 */
    RG_TENSOR_CON_5_T                                 rg_tensor_con_5; /* offset: 0x0000005C, TENSOR Control Register 5 */
    RG_COMP_CON_0_T                                     rg_comp_con_0; /* offset: 0x00000060, COMP Control Register 0 */
    RG_COMP_CON_1_T                                     rg_comp_con_1; /* offset: 0x00000064, COMP Control Register 1 */
    RG_COMP_CON_2_T                                     rg_comp_con_2; /* offset: 0x00000068, COMP Control Register 2 */
    RG_COMP_CON_3_T                                     rg_comp_con_3; /* offset: 0x0000006C, COMP Control Register 3 */
    RG_COMP_CON_4_T                                     rg_comp_con_4; /* offset: 0x00000070, COMP Control Register 4 */
    RG_ATST_CON_0_T                                     rg_atst_con_0; /* offset: 0x00000074, ATST Control Register 0 */
    RG_ATST_CON_1_T                                     rg_atst_con_1; /* offset: 0x00000078, ATST Control Register 1 */
    RG_CKGEN_CON_0_T                                   rg_ckgen_con_0; /* offset: 0x0000007C, CKGEN Control Register 0 */
    RG_CKGEN_CON_1_T                                   rg_ckgen_con_1; /* offset: 0x00000080, CKGEN Control Register 1 */
} ABB_CFG_REGISTER_T;
#define ABB_CFG    ((ABB_CFG_REGISTER_T *)ABB_CFG_BASE)


/* CM33 boot vector 0 */
typedef union {
    struct {
        __IO uint32_t CM33_BOOT_VECTOR0               :32;    /* bits:0-31, Once CM33 reset is deassert, CM33 will fetch CMCFG_BOOT_VECTOR0 & CMCFG_BOOT_VECTOR1 when CMCFG_BOOT_FROM_SLV = 1 [31:0]: CM33 MSP value */
    } field;
    __IO uint32_t word;
} CMCFG_BOOT_VECTOR0_T;

#define CMCFG_BOOT_VECTOR0_CM33_BOOT_VECTOR0_OFFSET                      (0U)
#define CMCFG_BOOT_VECTOR0_CM33_BOOT_VECTOR0_MASK                        (0xFFFFFFFFU << CMCFG_BOOT_VECTOR0_CM33_BOOT_VECTOR0_OFFSET)


/* CM33 boot vector1 */
typedef union {
    struct {
        __IO uint32_t CM33_BOOT_VECTOR1               :32;    /* bits:0-31, Once CM33 reset is deassert, CM33 will fetch CMCFG_BOOT_VECTOR0 & CMCFG_BOOT_VECTOR1 when CMCFG_BOOT_FROM_SLV = 1 [31:0]: reset handler address for example: 32'h04100001 (boot rom),  32'h04008001 (CM33 TCM) */
    } field;
    __IO uint32_t word;
} CMCFG_BOOT_VECTOR1_T;

#define CMCFG_BOOT_VECTOR1_CM33_BOOT_VECTOR1_OFFSET                      (0U)
#define CMCFG_BOOT_VECTOR1_CM33_BOOT_VECTOR1_MASK                        (0xFFFFFFFFU << CMCFG_BOOT_VECTOR1_CM33_BOOT_VECTOR1_OFFSET)


/* CM33 boot from slave */
typedef union {
    struct {
        __IO uint32_t CM33_BOOT_FROM_SLV              :1;    /* bits:0-0, Once CM33 reset is de-assert, indicate which device is CM33 boot from 0: Do not support 1: Boot from boot slave */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} CMCFG_BOOT_FROM_SLV_T;

#define CMCFG_BOOT_FROM_SLV_CM33_BOOT_FROM_SLV_OFFSET                    (0U)
#define CMCFG_BOOT_FROM_SLV_CM33_BOOT_FROM_SLV_MASK                      (0x1U << CMCFG_BOOT_FROM_SLV_CM33_BOOT_FROM_SLV_OFFSET)


/* RISCV boot vector */
typedef union {
    struct {
        __IO uint32_t RISCV_BOOT_VECTOR                :32;    /* bits:0-31, Once RISCV reset is deassert, RISCV will fetch RISCV_CFG_BOOT_VECTOR [31:0]: DSP boot slave value */
    } field;
    __IO uint32_t word;
} RISCV_CFG_BOOT_VECTOR_T;

#define RISCV_CFG_BOOT_VECTOR_RISCV_BOOT_VECTOR_OFFSET                     (0U)
#define RISCV_CFG_BOOT_VECTOR_RISCV_BOOT_VECTOR_MASK                       (0xFFFFFFFFU << RISCV_CFG_BOOT_VECTOR_RISCV_BOOT_VECTOR_OFFSET)


/* RISCV boot vector select */
typedef union {
    struct {
        __IO uint32_t RISCV_BOOT_VECTOR_SELECT         :2;    /* bits:0-1, Once RISCV reset is de-assert, indicate which device is RISCV boot from 0: Boot from RISCV IRAM (0x80010000) 1: Boot from boot slave value + 0x80, 3: Boot from boot slave value */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} RISCV_CFG_BOOT_VECTOR_SELECT_T;

#define RISCV_CFG_BOOT_VECTOR_SELECT_RISCV_BOOT_VECTOR_SELECT_OFFSET       (0U)
#define RISCV_CFG_BOOT_VECTOR_SELECT_RISCV_BOOT_VECTOR_SELECT_MASK         (0x1U << RISCV_CFG_BOOT_VECTOR_SELECT_RISCV_BOOT_VECTOR_SELECT_OFFSET)


/* RISCV deep sleep */
typedef union {
    struct {
        __I  uint32_t RISCV_DEEP_SLEEP                 :1;    /* bits:0-0, RISCV enter sleep (WFI) 0: RISCV active 1: RISCV enter sleep */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} RISCV_DEEP_SLEEP_T;

#define RISCV_DEEP_SLEEP_RISCV_DEEP_SLEEP_OFFSET                           (0U)
#define RISCV_DEEP_SLEEP_RISCV_DEEP_SLEEP_MASK                             (0x1U << RISCV_DEEP_SLEEP_RISCV_DEEP_SLEEP_OFFSET)


/* RISCV program counter */
typedef union {
    struct {
        __I  uint32_t RISCV_PC                         :32;    /* bits:0-31, RISCV current program counter */
    } field;
    __IO uint32_t word;
} RISCV_PC_T;

#define RISCV_PC_RISCV_PC_OFFSET                                           (0U)
#define RISCV_PC_RISCV_PC_MASK                                             (0xFFFFFFFFU << RISCV_PC_RISCV_PC_OFFSET)


/* dummy rw */
typedef union {
    struct {
        __IO uint32_t DUMMY_RW                        :32;    /* bits:0-31, empty description */
    } field;
    __IO uint32_t word;
} DUMMY_RW_T;

#define DUMMY_RW_DUMMY_RW_OFFSET                                         (0U)
#define DUMMY_RW_DUMMY_RW_MASK                                           (0xFFFFFFFFU << DUMMY_RW_DUMMY_RW_OFFSET)


/* dummy ro */
typedef union {
    struct {
        __I  uint32_t DUMMY_RO                        :32;    /* bits:0-31, empty description */
    } field;
    __IO uint32_t word;
} DUMMY_RO_T;

#define DUMMY_RO_DUMMY_RO_OFFSET                                         (0U)
#define DUMMY_RO_DUMMY_RO_MASK                                           (0xFFFFFFFFU << DUMMY_RO_DUMMY_RO_OFFSET)


typedef struct {
    CMCFG_BOOT_VECTOR0_T                           cmcfg_boot_vector0; /* offset: 0x00000000, CM33 boot vector 0 */
    CMCFG_BOOT_VECTOR1_T                           cmcfg_boot_vector1; /* offset: 0x00000004, CM33 boot vector1 */
    CMCFG_BOOT_FROM_SLV_T                         cmcfg_boot_from_slv; /* offset: 0x00000008, CM33 boot from slave */
    uint32_t                                         __reserved_00[1]; /* offset: 0x0000000C, padding size: 0x00000004 */
    RISCV_CFG_BOOT_VECTOR_T                       riscv_cfg_boot_vector; /* offset: 0x00000010, RISCV boot vector */
    RISCV_CFG_BOOT_VECTOR_SELECT_T         riscv_cfg_boot_vector_select; /* offset: 0x00000014, RISCV boot vector select */
    RISCV_DEEP_SLEEP_T                                 riscv_deep_sleep; /* offset: 0x00000018, RISCV deep sleep */
    RISCV_PC_T                                                 riscv_pc; /* offset: 0x0000001C, RISCV program counter */
    DUMMY_RW_T                                               dummy_rw; /* offset: 0x00000020, dummy rw */
    DUMMY_RO_T                                               dummy_ro; /* offset: 0x00000024, dummy ro */
} MCU_CFG_PRI_REGISTER_T;
#define MCU_CFG_PRI    ((volatile MCU_CFG_PRI_REGISTER_T *)MCU_CFG_PRI_BASE)


#endif /* __MISC_CFG_REG_DEFINITION_H__ */